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
/*         \file  EthTrcv_30_Tja1100_Int.h
 *        \brief  Ethernet transceiver driver internal header
 *
 *      \details  Header file containing the private function declarations of the Ethernet Transceiver driver
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
#if !defined (ETHTRCV_30_TJA1100_INT_H)
# define ETHTRCV_30_TJA1100_INT_H
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTrcv_30_Tja1100_IntDef.h"
# include "EthTrcv_30_Tja1100_Hw_Int.h"
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined(ETHTRCV_30_TJA1100_INT_LOCAL)                                                                              /* COV_ETHTRCV_COMPATIBILITY */
#  define ETHTRCV_30_TJA1100_INT_LOCAL                                static
# endif

# if !defined(ETHTRCV_30_TJA1100_INT_LOCAL_INLINE)                                                                       /* COV_ETHTRCV_COMPATIBILITY */
#  define ETHTRCV_30_TJA1100_INT_LOCAL_INLINE                         LOCAL_INLINE
# endif

# define ETHTRCV_30_TJA1100_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
/**********************************************************************************************************************
 *  LOCAL INLINE FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/***********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ReadSetBitMaskWrite()
 **********************************************************************************************************************/
/*! \brief         Function to set transceiver registers according to a bitmask.
 *  \details       This function is used to change the register value of a transceiver register according to a bitmask.
 *                 The bits set in the bitmask are also set in the register, the others are not changed.
 *  \param[in]     TrcvIdx  Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                          instances minus one.
 *  \param[in]     RegAddr  Address of the register to be changed
 *  \param[in]     BitMask  Bitmask in which the bits to be set in the register are set
 *  \return        RetVal   E_OK: Operation successful
 *                          E_NOT_OK: Operation not successful
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
    uint8 TrcvIdx,
    uint8 RegAddr,
    uint16 BitMask);

/***********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ReadClearBitMaskWrite()
 **********************************************************************************************************************/
/*! \brief         Function to clear transceiver registers according to a given bitmask.
 *  \details       This function is used to change the register value of a transceiver register according to a bitmask.
 *                 The bits set in the bitmask are cleared in the register.
 *  \param[in]     TrcvIdx  Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                          instances minus one.
 *  \param[in]     RegAddr  Address of the register to be changed
 *  \param[in]     BitMask  Bitmask in which the bits to be clear in the register are set
 *  \return        RetVal   E_OK: Operation successful
 *                          E_NOT_OK: Operation not successful
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
    uint8 TrcvIdx,
    uint8 RegAddr,
    uint16 BitMask);

/***********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ReadAndCompareToBitMask()
 **********************************************************************************************************************/
/*! \brief         Function to compare transceiver registers
 *  \details       This function is used to read a transceiver register and compare it with a bit mask. If the bits set
 *                 in the bitmask are also set in the register, the result is TRUE, otherwise FALSE.
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                            instances minus one.
 *  \param[in]     RegAddr    Address of the register to be compared
 *  \param[in]     BitMask    Bitmask in which the bits to compare with the register value are set
 *  \param[out]    ResultPtr  Valid pointer to the address where the result of the compare operation shall be stored
 *  \return        RetVal     E_OK: Operation successful
 *                            E_NOT_OK: Operation not successful
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE)  EthTrcv_30_Tja1100_ReadAndCompareToBitMask(
    uint8 TrcvIdx,
    uint8 RegAddr,
    uint16 BitMask,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) ResultPtr);

/***********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ReadSetBitMaskWriteCl45()
 **********************************************************************************************************************/
/*! \brief         Function to set IEEE 802.3 Clause 45 transceiver registers according to a bitmask.
 *  \details       This function is used to change the register value of a transceiver register according to a bitmask.
 *                 The bits set in the bitmask are also set in the register. The IEEE 802.3 Clause 45 registers are
 *                 accessed over the Clause 22 registers MMD ACCESS CONTROL and MMD ADDRESS DATA.
 *  \param[in]     TrcvIdx     Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                             instances minus one.
 *  \param[in]     DeviceAddr  Address of the MMD for which the register shall be accessed
 *  \param[in]     RegAddr     Address of the register to be changed
 *  \param[in]     BitMask     Bitmask in which the bits to be set in the register are set
 *  \return        RetVal      E_OK: Operation successful
 *                             E_NOT_OK: Operation not successful
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 */

ETHTRCV_30_TJA1100_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadSetBitMaskWriteCl45(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    uint16 BitMask);

/***********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ReadClearBitMaskWriteCl45()
 **********************************************************************************************************************/
/*! \brief         Function to clear IEEE 802.3 Clause 45 transceiver registers according to a bitmask.
 *  \details       This function is used to change the register value of a transceiver register according to a bitmask.
 *                 The bits set in the bitmask are cleared in the register. The IEEE 802.3 Clause 45 registers are
 *                 accessed over the Clause 22 registers MMD ACCESS CONTROL and MMD ADDRESS DATA.
 *  \param[in]     TrcvIdx     Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                             instances minus one.
 *  \param[in]     DeviceAddr  Address of the MMD for which the register shall be accessed
 *  \param[in]     RegAddr     Address of the register to be changed
 *  \param[in]     BitMask     Bitmask in which the bits to be clear in the register are set
 *  \return        RetVal      E_OK: Operation successful
 *                             E_NOT_OK: Operation not successful
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadClearBitMaskWriteCl45(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    uint16 BitMask);

/***********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ReadAndCompareToBitMaskCl45()
 **********************************************************************************************************************/
/*! \brief         Function to compare IEEE 802.3 Clause 45 transceiver registers to a given value.
 *  \details       This function is used to read a IEEE 802.3 Clause 45 transceiver register and compare it with a bit
 *                 mask. If the bits set in the bitmask are also set in the register, the result is TRUE, otherwise
 *                 FALSE.
 *  \param[in]     TrcvIdx     Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                             instances minus one.
 *  \param[in]     DeviceAddr  Address of the MMD for which the register shall be accessed
 *  \param[in]     RegAddr     Address of the register to be compared
 *  \param[in]     BitMask     Bitmask in which the bits to compare with the register value are set
 *  \param[out]    ResultPtr   Valid pointer to the address where the result of the compare operation shall be stored
 *  \return        RetVal      E_OK: Operation successful
 *                             E_NOT_OK: Operation not successful
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE)  EthTrcv_30_Tja1100_ReadAndCompareToBitMaskCl45(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    uint16 BitMask,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) ResultPtr);
/**********************************************************************************************************************
 *  GLOBAL INLINE FUNCTION DEFINITION
 *********************************************************************************************************************/
# if !defined(ETHTRCV_30_TJA1100_UNIT_TEST) /* COV_ETHTRCV_TEST_SUITE_UNIT_TESTS */
/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ReadSetBitMaskWrite
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_EthTrcv_30_Tja1100_3219 */
ETHTRCV_30_TJA1100_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
    uint8 TrcvIdx,
    uint8 RegAddr,
    uint16 BitMask)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16         regVal;
  Std_ReturnType retVal;

  /* #10 Read the specified transceiver register */
  retVal = EthTrcv_30_Tja1100_Internal_ReadTrcvReg(TrcvIdx, RegAddr, &regVal);                                          /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #20 Set the bits in the read register value according to the BitMask parameter */
  regVal |= BitMask;

  /* #30 Write the register value back */
  retVal |= EthTrcv_30_Tja1100_Internal_WriteTrcvReg(TrcvIdx, RegAddr, regVal);

  return retVal;
} /* EthTrcv_30_Tja1100_ReadSetBitMaskWrite() */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ReadClearBitMaskWrite
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_EthTrcv_30_Tja1100_3219 */
ETHTRCV_30_TJA1100_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
    uint8 TrcvIdx,
    uint8 RegAddr,
    uint16 BitMask)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16         regVal;
  Std_ReturnType retVal;

  /* #10 Read the specified transceiver register */
  retVal = EthTrcv_30_Tja1100_Internal_ReadTrcvReg(TrcvIdx, RegAddr, &regVal);                                          /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #20 Clear the bits in the read register value which are set in the BitMask parameter */
  regVal &= (uint16)(~BitMask);

  /* #30 Write the register value back */
  retVal |= EthTrcv_30_Tja1100_Internal_WriteTrcvReg(TrcvIdx, RegAddr, regVal);

  return retVal;
} /* EthTrcv_30_Tja1100_ReadSetBitMaskWrite() */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ReadAndCompareToBitMask
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_EthTrcv_30_Tja1100_3219 */
ETHTRCV_30_TJA1100_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadAndCompareToBitMask(
    uint8 TrcvIdx,
    uint8 RegAddr,
    uint16 BitMask,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) ResultPtr)
{
  uint16         regVal;
  Std_ReturnType retVal;

  /* #10 Read the specified transceiver register */
  retVal = EthTrcv_30_Tja1100_Internal_ReadTrcvReg(TrcvIdx, RegAddr, &regVal);                                          /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #20 All bits which are set in the BitMask parameter are also set in the read register value */
  if((regVal & BitMask) == BitMask)
  {
    /* #210 Return a positive result */
    *ResultPtr = TRUE;                                                                                                  /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }
  /* #30 Not all bits which are set in the BitMask parameter are set in the read register value */
  else
  {
    /* #310 Return a negative result */
    *ResultPtr = FALSE;                                                                                                 /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }
  return retVal;
} /* EthTrcv_30_Tja1100_ReadAndCompareToBitMask */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ReadSetBitMaskWriteCl45
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_EthTrcv_30_Tja1100_3219 */
ETHTRCV_30_TJA1100_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadSetBitMaskWriteCl45(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    uint16 BitMask)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16         regVal;
  Std_ReturnType retVal;

  /* #10 Read the specified transceiver register */
  retVal = EthTrcv_30_Tja1100_Internal_ReadCl45TrcvReg(TrcvIdx, DeviceAddr, RegAddr, &regVal);                          /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #20 Set the bits in the read register value according to the BitMask parameter */
  regVal |= BitMask;

  /* #30 Write the register value back */
  retVal |= EthTrcv_30_Tja1100_Internal_WriteCl45TrcvReg(TrcvIdx, DeviceAddr, RegAddr, regVal);

  return retVal;
} /* EthTrcv_30_Tja1100_ReadSetBitMaskWrite() */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ReadClearBitMaskWriteCl45
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_EthTrcv_30_Tja1100_3219 */
ETHTRCV_30_TJA1100_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadClearBitMaskWriteCl45(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    uint16 BitMask)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16         regVal;
  Std_ReturnType retVal;

  /* #10 Read the specified transceiver register */
  retVal = EthTrcv_30_Tja1100_Internal_ReadCl45TrcvReg(TrcvIdx, DeviceAddr, RegAddr, &regVal);                          /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #20 Clear the bits in the read register value which are set in the BitMask parameter */
  regVal &= (uint16)(~BitMask);

  /* #30 Write the register value back */
  retVal |= EthTrcv_30_Tja1100_Internal_WriteCl45TrcvReg(TrcvIdx, DeviceAddr, RegAddr, regVal);

  return retVal;
} /* EthTrcv_30_Tja1100_ReadSetBitMaskWrite() */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ReadAndCompareToBitMaskCl45
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_EthTrcv_30_Tja1100_3219 */
ETHTRCV_30_TJA1100_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadAndCompareToBitMaskCl45(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    uint16 BitMask,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) ResultPtr)
{
  uint16         regVal;
  Std_ReturnType retVal;

  /* #10 Read the specified transceiver register */
  retVal = EthTrcv_30_Tja1100_Internal_ReadCl45TrcvReg(TrcvIdx, DeviceAddr, RegAddr, &regVal);                          /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #20 All bits which are set in the BitMask parameter are also set in the read register value */
  if((regVal & BitMask) == BitMask)
  {
    /* #210 Return a positive result */
    *ResultPtr = TRUE;                                                                                                  /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }
  /* #30 Not all bits which are set in the BitMask parameter are set in the read register value */
  else
  {
    /* #310 Return a negative result */
    *ResultPtr = FALSE;                                                                                                 /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }
  return retVal;
} /* EthTrcv_30_Tja1100_ReadAndCompareToBitMask */
# endif /* ETHTRCV_30_TJA1100_UNIT_TEST */
# define ETHTRCV_30_TJA1100_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#endif /* ETHTRCV_30_TJA1100_INT_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Tja1100_Int.h
 *********************************************************************************************************************/
