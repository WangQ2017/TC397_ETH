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
/*!        \file  EthTSyn_Crc_Int.h
 *        \brief  EthTSyn internal header file for Crc handling
 *      \details  Contains all macros and function declarations used by the EthTSyn to handle Crc calculation and
 *                validation
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
#if !defined (ETHTSYN_CRC_INT_H)
# define ETHTSYN_CRC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_Cfg.h"

# if (ETHTSYN_CRC_SUPPORT == STD_ON)
#  include "EthTSyn_Types.h"

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
#  define ETHTSYN_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeTime0Crc
 *********************************************************************************************************************/
/*! \brief      Computes the uint8 Crc (CRC_TIME_0) for a TimeSecured FollowUp message.
 *  \details    -
 *  \param[in]  DataId          The DataId for the FollowUp
 *  \param[in]  Flags           The Flags determining which fields to use for the Crc calculation
 *  \param[in]  BufPtr          Pointer to the Ethernet reception/transmission buffer of the FollowUp message
 *  \return     The computed Crc (with the use Crc_CalculateCRC8H2F).
 *  \pre        For Tx: All Sub-Tlv information except the Crc itself are already copied to the Tx-Buffer
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeTime0Crc(
                  uint8   DataId,
                  uint8   Flags,
  ETHTSYN_P2CONST(uint8)  BufPtr);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeTime1Crc
 *********************************************************************************************************************/
/*! \brief      Computes the uint8 Crc (CRC_TIME_1) for a TimeSecured FollowUp message.
 *  \details    -
 *  \param[in]  DataId          The DataId for the FollowUp
 *  \param[in]  Flags           The Flags determining which fields to use for the Crc calculation
 *  \param[in]  BufPtr          Pointer to the Ethernet reception/transmission buffer of the FollowUp message
 *  \return     The computed Crc (with the use Crc_CalculateCRC8H2F).
 *  \pre        For Tx: All Sub-Tlv information except the Crc itself are already copied to the Tx-Buffer
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeTime1Crc(
                  uint8   DataId,
                  uint8   Flags,
  ETHTSYN_P2CONST(uint8)  BufPtr);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeStatusCrc
 *********************************************************************************************************************/
/*! \brief      Computes the uint8 Crc for a Status Secured FollowUp message.
 *  \details    -
 *  \param[in]  DataId               The DataId for the FollowUp
 *  \param[in]  BufPtr               Pointer to the Ethernet reception/transmission buffer of the FollowUp message
 *  \param[in]  StatusSecuredTlvOfs  Offset of the Statues Secured Sub-Tlv within the FollowUp message
 *  \return     The computed Crc (CRC_Status) (with the use Crc_CalculateCRC8H2F).
 *  \pre        For Tx: All Sub-Tlv information except the Crc itself are already copied to the Tx-Buffer
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeStatusCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  BufPtr,
                  uint32  StatusSecuredTlvOfs);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeUserDataCrc
 *********************************************************************************************************************/
/*! \brief      Computes the uint8 Crc for a UserData Secured FollowUp message.
 *  \details    -
 *  \param[in]  DataId                 The DataId for the FollowUp
 *  \param[in]  BufPtr                 Pointer to the Ethernet reception/transmission buffer of the FollowUp message
 *  \param[in]  UserDataSecuredTlvOfs  Offset of the UserData Secured Sub-Tlv within the FollowUp message
 *  \return     The computed Crc (CRC_UserData) (with the use Crc_CalculateCRC8H2F).
 *  \pre        For Tx: All Sub-Tlv information except the Crc itself are already copied to the Tx-Buffer
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeUserDataCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  BufPtr,
                  uint32  UserDataSecuredTlvOfs);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeOfsCrc
 *********************************************************************************************************************/
/*! \brief      Computes the uint8 Crc for a Ofs Secured FollowUp message.
 *  \details    -
 *  \param[in]  DataId            The DataId for the FollowUp
 *  \param[in]  BufPtr            Pointer to the Ethernet reception/transmission buffer of the FollowUp message
 *  \param[in]  OfsSecuredTlvPtr  Offset of the Ofs Secured Sub-Tlv within the FollowUp message
 *  \return     The computed Crc (CRC_OFS) (with the use Crc_CalculateCRC8H2F).
 *  \pre        For Tx: All Sub-Tlv information except the Crc itself are already copied to the Tx-Buffer
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeOfsCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  BufPtr,
                  uint32  OfsSecuredTlvOfs);

#  if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateSubTlvCrc
 *********************************************************************************************************************/
/*! \brief      Validates the Crc for the given Ar Sub-Tlv of the FollowUp.
 *  \details    Computes the expected Crc of the provided Sub-Tlv, if it is a secured Sub-Tlv, and validates the Crc
 *              value carried in the Sub-Tlv itself.
 *  \param[in]  DataId       The DataId for the FollowUp
 *  \param[in]  RxBufPtr     Pointer to the Ethernet reception buffer of the received FollowUp message
 *  \param[in]  ArSubTlvOfs  Offset of the Ar Sub-Tlv within the FollowUp message
 *  \return     TRUE - Crc is valid or Sub-Tlv without Crc was passed
 *  \return     False - Crc is invalid
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateSubTlvCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
                  uint32  ArSubTlvOfs);
#  endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

#  define ETHTSYN_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

# endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
#endif /* ETHTSYN_CRC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Crc_Int.h
 *********************************************************************************************************************/
