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
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IpBase_Code.h
 *      Project:  MICROSAR ETH
 *    Component:  SysService_IpBase
 *       Module:  MICROSAR IP Base
 *    Generator:  None
 *
 *  Description:  En- and decoding header
 *
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
#if !defined (IPBASE_CODE_H)
# define IPBASE_CODE_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "IpBase_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define IPBASE_CODE_BASE64                               ((uint8) 0x01)  /*!< BASE64 encoding id */

# define IPBASE_CODE_BASE64_RAW_BLOCK_LEN                 ((uint8)  3u)   /*!< BASE64 block length before encoding */
# define IPBASE_CODE_BASE64_CODED_BLOCK_LEN               ((uint8)  4u)   /*!< BASE64 block length after encoding */

# define IPBASE_CODE_BASE64_ENC_BYTE0_1ST_6BITS_MASK    (0x3Fu)   /*!< BASE64 encoding bit mask for byte 0 
                                                                       (first 6 bits) */
# define IPBASE_CODE_BASE64_ENC_BYTE0_REM_2BITS_MASK    (0x30u)   /*!< BASE64 encoding bit mask for byte 0 
                                                                       (remaining 2 bits) */
# define IPBASE_CODE_BASE64_ENC_BYTE1_1ST_4BITS_MASK    (0x0Fu)   /*!< BASE64 encoding bit mask for byte 1 
                                                                       (first 4 bits) */
# define IPBASE_CODE_BASE64_ENC_BYTE1_REM_4BITS_MASK    (0x3Cu)   /*!< BASE64 encoding bit mask for byte 1 
                                                                       (reamining 4 bits) */
# define IPBASE_CODE_BASE64_ENC_BYTE2_1ST_2BITS_MASK    (0x03u)   /*!< BASE64 encoding bit mask for byte 2 
                                                                       (first 2 bits) */
# define IPBASE_CODE_BASE64_ENC_BYTE2_REM_6BITS_MASK    (0x3Fu)   /*!< BASE64 encoding bit mask for byte 2 
                                                                       (reamining 6 bits) */
# define IPBASE_CODE_BASE64_DEC_1ST_6BITS_MASK          (0xFCu)   /*!< BASE64 decoding bit mask for first 6 bits */
# define IPBASE_CODE_BASE64_DEC_REM_2BITS_MASK          (0x03u)   /*!< BASE64 decoding bit mask for remaining 2 bits */
# define IPBASE_CODE_BASE64_DEC_1ST_4BITS_MASK          (0xF0u)   /*!< BASE64 decoding bit mask for first 4 bits */
# define IPBASE_CODE_BASE64_DEC_REM_4BITS_MASK          (0x0Fu)   /*!< BASE64 decoding bit mask for remaining 4 bits */
# define IPBASE_CODE_BASE64_DEC_1ST_2BITS_MASK          (0xC0u)   /*!< BASE64 decoding bit mask for first 2 bits */
# define IPBASE_CODE_BASE64_DEC_REM_6BITS_MASK          (0x3Fu)   /*!< BASE64 decoding bit mask for remaining 6 bits */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  IpBase_Encode
 *********************************************************************************************************************/
/*! \brief        Encodes data
 *  \details      Encodes the given data using the specified code.
 *  \param[in]     Code           defines the code used for encoding
 *  \param[out]    TgtDataPtr     pointer for the encoded data
 *  \param[in]     SrcDataPtr     pointer to the raw data
 *  \param[in,out] TgtLenBytePtr  in: pointer with total target length, out: pointer for the encoded data length [bytes]
 *  \param[in]     SrcLenByte     raw data length in bytes
 *  \return        E_OK                 data encoded
 *  \return        E_NOT_OK             data code not be encoded
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        CREQ-120244
 *  \note         General encoding
 *********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_Encode(uint8 Code,
                                              IPBASE_P2VARAPPLDATA(uint8) TgtDataPtr,
                                              IPBASE_P2CONSTAPPLDATA(uint8) SrcDataPtr,
                                              IPBASE_P2VARAPPLDATA(uint32) TgtLenBytePtr,
                                              uint32 SrcLenByte);
/**********************************************************************************************************************
 *  IpBase_Decode
 *********************************************************************************************************************/
/*! \brief        Decodes data
 *  \details      Decodes the given data using the specified code.
 *  \param[in]     Code           defines the code used for decoding
 *  \param[out]    TgtDataPtr     pointer for the decoded data
 *  \param[in]     SrcDataPtr     pointer to the raw data
 *  \param[in,out] TgtLenBytePtr  in: pointer with total target length, out: pointer for the encoded data length [bytes]
 *  \param[in]     SrcLenByte     raw data length in bytes
 *  \return        E_OK                 data decoded
 *  \return        E_NOT_OK             data code could not be decoded
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        CREQ-120244
 *  \note         General decoding
 *********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_Decode(uint8 Code,
                                              IPBASE_P2VARAPPLDATA(uint8) TgtDataPtr,
                                              IPBASE_P2CONSTAPPLDATA(uint8) SrcDataPtr,
                                              IPBASE_P2VARAPPLDATA(uint32) TgtLenBytePtr,
                                              uint32 SrcLenByte);
#endif
  /* IPBASE_CODE_H */
/**********************************************************************************************************************
 *  END OF FILE: IpBase_Code.h
 *********************************************************************************************************************/
