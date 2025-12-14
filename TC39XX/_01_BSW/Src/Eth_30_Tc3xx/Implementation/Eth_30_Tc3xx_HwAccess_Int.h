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
/*!        \file  Eth_30_Tc3xx_HwAccess_Int.h
 *        \brief  Register access sub-module of the Ethernet controller driver
 *
 *      \details  Provides abstraction in form of register access functions
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx.h
 *********************************************************************************************************************/

/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#if !defined (ETH_30_TC3XX_REG_ACCESS_INT_H)
# define ETH_30_TC3XX_REG_ACCESS_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx.h"
# include "Eth_30_Tc3xx_Lcfg.h"
# include "Eth_30_Tc3xx_LL_Regs.h"
# if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON) /* COV_ETH_PERIPHERAL_ACCESS */
#  include "Os.h"
# endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE) /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE                         LOCAL_INLINE
# endif /* ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
# define ETH_30_TC3XX_UINT8_MAX                                        (0xFFu)
# define ETH_30_TC3XX_UINT16_MAX                                       (0xFFFFu)
# define ETH_30_TC3XX_UINT32_MAX                                       (0xFFFFFFFFul)
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetRegBaseAddress
 *********************************************************************************************************************/
/*! \brief       Retrieves the register base address of the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      Register base address
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRegBaseAddress(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_CreateRegPtr
 *********************************************************************************************************************/
/*! \brief       Creates a pointer to the register addressed by the offset into the Ethernet controllers register space
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \return      Pointer to the register addressed
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_CreateRegPtr(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Write
 *********************************************************************************************************************/
/*! \brief       Writes the given value to the addressed register
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   regValue   Value to be written to the register
 *  \context     ANY
 *  \reentrant   TRUE for different registers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Write(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  regValue);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Write_Protected
 *********************************************************************************************************************/
/*! \brief       Writes the given value to the addressed register by using protected access method if necessary
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   regValue   Value to be written to the register
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different registers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Write_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  regValue);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Read
 *********************************************************************************************************************/
/*! \brief       Reads the value of the addressed register
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \return      Value of the register
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Read(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Read_Protected
 *********************************************************************************************************************/
/*! \brief       Reads the value of the addressed register by using protected access method if necessary
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \return      Value of the register
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Read_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ReadBits
 *********************************************************************************************************************/
/*! \brief       Reads the value of the addressed register and applies bit mask
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bit mask to apply on register value
 *  \return      Value of the register
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ReadBits(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ReadBits_Protected
 *********************************************************************************************************************/
/*! \brief       Reads the value of the addressed register by using protected access method if necessary and applies
 *               bit mask
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bit mask to apply on register value
 *  \return      Value of the register
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ReadBits_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_SetBitMask
 *********************************************************************************************************************/
/*! \brief       Sets the bits given by the bit mask in the addressed register
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bits to be set
 *  \context     ANY
 *  \reentrant   TRUE for different registers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_SetBitMask(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_SetBitMask_Protected
 *********************************************************************************************************************/
/*! \brief       Sets the bits given by the bit mask in the addressed register by using protected access method if
 *               necessary
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bits to be set
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different registers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_SetBitMask_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ClearBitMask
 *********************************************************************************************************************/
/*! \brief       Clears the bits given by the bit mask in the addressed register
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bits to be cleared
 *  \context     ANY
 *  \reentrant   TRUE for different registers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ClearBitMask(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ClearBitMask_Protected
 *********************************************************************************************************************/
/*! \brief       Clears the bits given by the bit mask in the addressed register by using protected access method if
 *               necessary
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bits to be cleared
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different registers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ClearBitMask_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_IsBitMaskSet
 *********************************************************************************************************************/
/*! \brief       Checks if all of the bits given by the bit mask are set in the addressed register
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bits to be checked for being set
 *  \return      FALSE - at least one bit of the bit mask isn't set in the register
 *  \return      TRUE - all bits of the bit mask are set in the register
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_IsBitMaskSet(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_IsBitMaskSet_Protected
 *********************************************************************************************************************/
/*! \brief       Checks if all of the bits given by the bit mask are set in the addressed register by using protected
 *               access method if necessary
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bits to be checked for being set
 *  \return      FALSE - at least one bit of the bit mask isn't set in the register
 *  \return      TRUE - all bits of the bit mask are set in the register
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_IsBitMaskSet_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask);

# ifndef ETH_30_TC3XX_UNIT_TEST /* COV_ETH_TEST_SUITE_UNIT_TESTS */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetRegBaseAddress
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegBaseAddrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRegBaseAddress(
  uint8 ctrlIdx)
{
  /* #10 Retrieve the configured register base address of the Ethernet controller */
  return Eth_30_Tc3xx_GetRegBaseAddrOfEthCtrlState(ctrlIdx);
} /* Eth_30_Tc3xx_GetRegBaseAddress() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_CreateRegPtr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_CreateRegPtr(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset)
{
  /* #10 Create a pointer to the register the caller wants to address within the register space of the Ethernet
   *     controller */
  /* PRQA S 0303 1 */ /* MD_Eth_30_Tc3xx_0303 */
  return (Eth_30_Tc3xx_RegPtrType)(Eth_30_Tc3xx_GetRegBaseAddress(ctrlIdx) + regOffset);
} /* Eth_30_Tc3xx_CreateRegPtr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Write
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Write(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  regValue)
{
  /* #10 Write the given value to the register at the given address offset */
  Eth_30_Tc3xx_RegPtrType reg = Eth_30_Tc3xx_CreateRegPtr(ctrlIdx, regOffset);
  (*reg) = regValue;                                                                                                    /* SBSW_ETH_30_TC3XX_REGISTER_ACCESS */
} /* Eth_30_Tc3xx_Reg_Write() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Write_Protected
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Write_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  regValue)
{
  /* #10 Write the given value to the register at the given address offset by using protected access method, if
   *     necessary */
#  if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON) /* COV_ETH_PERIPHERAL_ACCESS */
  osWritePeripheral32(Eth_30_Tc3xx_GetProtectedAreaIdOfEthCtrl(ctrlIdx),
                      (uint32)(Eth_30_Tc3xx_GetRegBaseAddress(ctrlIdx) + regOffset), regValue);
#  else
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffset, regValue);
#  endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */
} /* Eth_30_Tc3xx_Reg_Write_Protected() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Read
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Read(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset)
{
  /* #10 Read the value of the register at the given address offset and provide the result to the caller */
  Eth_30_Tc3xx_RegPtrType reg = Eth_30_Tc3xx_CreateRegPtr(ctrlIdx, regOffset);
  return (*reg);
} /* Eth_30_Tc3xx_Reg_Read() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Read_Protected
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Read_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset)
{
  /* #10 Read the value of the register at the given address offset and provide the result to the caller by using
   *     protected access method, if necessary */
#  if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON) /* COV_ETH_PERIPHERAL_ACCESS */
  return osReadPeripheral32(Eth_30_Tc3xx_GetProtectedAreaIdOfEthCtrl(ctrlIdx),
                            (uint32)(Eth_30_Tc3xx_GetRegBaseAddress(ctrlIdx) + regOffset));
#  else
  return Eth_30_Tc3xx_Reg_Read(ctrlIdx, regOffset);
#  endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */
} /* Eth_30_Tc3xx_Reg_Read_Protected() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ReadBits
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ReadBits(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
  /* #10 Read the value of the register at the given address offset, apply bit mask and provide the result to the
   *     caller */
  return (Eth_30_Tc3xx_Reg_Read(ctrlIdx, regOffset) & bitMask);
} /* Eth_30_Tc3xx_Reg_ReadBits() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ReadBits_Protected
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ReadBits_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
  /* #10 Read the value of the register at the given address offset, apply bit mask and provide the result to the
   *     caller by using protected access method, if necessary */
#  if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON) /* COV_ETH_PERIPHERAL_ACCESS */
  return (Eth_30_Tc3xx_Reg_Read_Protected(ctrlIdx, regOffset) & bitMask);
#  else
  return Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, regOffset, bitMask);
#  endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */
} /* Eth_30_Tc3xx_Reg_ReadBits_Protected() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_SetBitMask
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_SetBitMask(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
  /* #10 Set the given bit mask within the register at the given address offset */
  Eth_30_Tc3xx_RegPtrType reg = Eth_30_Tc3xx_CreateRegPtr(ctrlIdx, regOffset);
  (*reg) |= bitMask;                                                                                                    /* SBSW_ETH_30_TC3XX_REGISTER_ACCESS */
} /* Eth_30_Tc3xx_Reg_SetBitMask() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_SetBitMask_Protected
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_SetBitMask_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
  /* #10 Set the given bit mask within the register at the given address offset by using protected access method,
   *     if necessary */
#  if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON) /* COV_ETH_PERIPHERAL_ACCESS */
  osModifyPeripheral32(Eth_30_Tc3xx_GetProtectedAreaIdOfEthCtrl(ctrlIdx),
                        (Eth_30_Tc3xx_RegWidthType)(Eth_30_Tc3xx_GetRegBaseAddress(ctrlIdx) + regOffset),
                        (uint32)ETH_30_TC3XX_UINT32_MAX, (uint32)bitMask);
#  else
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, regOffset, bitMask);
#  endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */
} /* Eth_30_Tc3xx_Reg_SetBitMask_Protected() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ClearBitMask
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ClearBitMask(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
  /* #10 Clear the given bit mask within the register at the given address offset */
  Eth_30_Tc3xx_RegPtrType reg = Eth_30_Tc3xx_CreateRegPtr(ctrlIdx, regOffset);

  (*reg) = (*reg) & ~bitMask;                                                                                           /* SBSW_ETH_30_TC3XX_REGISTER_ACCESS */
} /* Eth_30_Tc3xx_Reg_ClearBitMask() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ClearBitMask_Protected
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ClearBitMask_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
  /* #10 Clear the given bit mask within the register at the given address offset by using protected access method,
   *     if necessary */
#  if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON) /* COV_ETH_PERIPHERAL_ACCESS */
  osModifyPeripheral32(Eth_30_Tc3xx_GetProtectedAreaIdOfEthCtrl(ctrlIdx),
                        (uint32)(Eth_30_Tc3xx_GetRegBaseAddress(ctrlIdx) + regOffset),
                       ~((uint32)bitMask), (uint32)0u);
#  else
  Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, regOffset, bitMask);
#  endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */
} /* Eth_30_Tc3xx_Reg_ClearBitMask_Protected() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_IsBitMaskSet
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_IsBitMaskSet(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
  boolean                result = FALSE;
  Eth_30_Tc3xx_RegPtrType reg    = Eth_30_Tc3xx_CreateRegPtr(ctrlIdx, regOffset);

  /* #10 If the given bit mask is set within the register at the given address offset */
  if( ((*reg) & bitMask) == bitMask )
  {
    /* #110 Return that the given bit mask is set */
    result = TRUE;
  }

  return result;
} /* Eth_30_Tc3xx_Reg_IsBitMaskSet() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_IsBitMaskSet_Protected
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_REG_ACCESS_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_IsBitMaskSet_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
  /* #10 If the given bit mask is set within the register at the given address offset and a protected access method
   *     needs to be used */
#  if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON) /* COV_ETH_PERIPHERAL_ACCESS */
  boolean               result = FALSE;
  Eth_30_Tc3xx_RegWidthType reg = osReadPeripheral32(Eth_30_Tc3xx_GetProtectedAreaIdOfEthCtrl(ctrlIdx),
                                                     (uint32)(Eth_30_Tc3xx_GetRegBaseAddress(ctrlIdx) + regOffset));

  /* #10 If the given bit mask is set within the register at the given address offset and a protected access method
   *     needs to be used */
  if ((reg & bitMask) == bitMask)
  {
    /* #110 Return that the given bit mask is set */
    result = TRUE;
  }

  return result;
#  else
  /* #20 If no protected access method is available, return the result of the internal interface to check if a bit mask
   *     is set in a register */
  return Eth_30_Tc3xx_Reg_IsBitMaskSet(ctrlIdx, regOffset, bitMask);
#  endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */
} /* Eth_30_Tc3xx_Reg_IsBitMaskSet_Protected() */

# endif /* ETH_30_TC3XX_UNIT_TEST */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETH_30_TC3XX_REG_ACCESS_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_HwAccess_Int.h
 *********************************************************************************************************************/
