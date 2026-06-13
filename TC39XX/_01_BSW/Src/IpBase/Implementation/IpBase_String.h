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
 *         File:  IpBase_String.h
 *      Project:  MICROSAR ETH
 *    Component:  SysService_IpBase
 *       Module:  MICROSAR IP Base
 *    Generator:  None
 *
 *  Description:  String header
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
#if !defined (IPBASE_STRING_H)
# define IPBASE_STRING_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "IpBase_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#  define IPBASE_START_SEC_CODE
#  include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  IpBase_StrCpy
 *********************************************************************************************************************/
/*! \brief         String copy (limited to 0xFFFF maximum length)
 *  \details       String copy for zero terminated strings.
 *  \param[out]    TgtPtr            pointer for target string
 *  \param[in]     SrcPtr            pointer to source string
 *  \return        Number of copied bytes
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          The source string has to be terminated by '\0', the memory addressed by the target pointer has to 
 *                 be large enough to copy the entire string including the trailing '\0'.
 *                 Deprecated: Please switch to IpBase_StrCpyMaxLen
 *********************************************************************************************************************/
IPBASE_FUNCCODE(uint16) IpBase_StrCpy(IPBASE_P2VARAPPLDATA(uint8) TgtPtr,
                                      IPBASE_P2CONSTAPPLDATA(uint8) SrcPtr);
/**********************************************************************************************************************
 *  IpBase_StrCpyMaxLen
 *********************************************************************************************************************/
/*! \brief         String copy max length
 *  \details       String copy (zero terminated strings) with length limitation.
 *  \param[out]    TgtPtr            pointer for target string
 *  \param[in]     SrcPtr            pointer to source string
 *  \param[in]     MaxLen            maximum length
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          The source string has to be terminated by '\0', the memory addressed by the target pointer has to 
 *                 be as large as given by maximum length parameter.
 *********************************************************************************************************************/
IPBASE_FUNCCODE(uint32) IpBase_StrCpyMaxLen(IPBASE_P2VARAPPLDATA(uint8) TgtPtr,
                                            IPBASE_P2CONSTAPPLDATA(uint8) SrcPtr, uint32 MaxLen);
/**********************************************************************************************************************
 *  IpBase_StrCmp
 *********************************************************************************************************************/
/*! \brief         Compare strings (limited to 0xFFFF maximum length)
 *  \details       Compare 2 strings until end of the shorter string.
 *  \param[out]    Str1Ptr               pointer to first string
 *  \param[in]     Str2Ptr               pointer to second string
 *  \return        IPBASE_CMP_EQUAL      strings are equal
 *  \return        IPBASE_CMP_NOT_EQUAL  string pattern not found
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          The strings have to be terminated by '\0'. String subsets are accepted (i.e. "Hello"=="Hello World")
 *********************************************************************************************************************/
IPBASE_FUNCCODE(uint8) IpBase_StrCmp(IPBASE_P2CONSTAPPLDATA(uint8) Str1Ptr,
                                     IPBASE_P2CONSTAPPLDATA(uint8) Str2Ptr);
/***********************************************************************************************************************
 *  IpBase_StrCmpLen
 **********************************************************************************************************************/
/*! \brief         Compare strings
 *  \details       Compare 2 strings with limited length and without '\0' limitation.
 *  \param[in]     Str1Ptr               pointer to string 1
 *  \param[in]     Str2Ptr               pointer to string 2
 *  \param[in]     StrLen                length of the search string [byte]
 *  \return        IPBASE_CMP_EQUAL      strings are equal
 *  \return        IPBASE_CMP_NOT_EQUAL  strings are not equal, or other error condition occurred
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          The memory addressed has to be as large as given by string length parameter.
 **********************************************************************************************************************/
IPBASE_FUNCCODE(uint8) IpBase_StrCmpLen(IPBASE_P2CONSTAPPLDATA(uint8) Str1Ptr,
                                        IPBASE_P2CONSTAPPLDATA(uint8) Str2Ptr,
                                        uint16 StrLen);
/**********************************************************************************************************************
 *  IpBase_StrCmpNoCase
 *********************************************************************************************************************/
/*! \brief         Compare 2 strings ignore case (limited to 0xFFFF maximum length)
 *  \details       Compare 2 strings until end of the shorter string ignoring the case.
 *  \param[out]    Str1Ptr               pointer to first string
 *  \param[in]     Str2Ptr               pointer to second string
 *  \return        IPBASE_CMP_EQUAL      strings are equal
 *  \return        IPBASE_CMP_NOT_EQUAL  string pattern not found
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          The strings have to be terminated by '\0'. String subsets are accepted (i.e. "Hello"=="Hello World")
 *                 case is ignored (i.e. "Hello" == "HELLO").
 *********************************************************************************************************************/
IPBASE_FUNCCODE(uint8) IpBase_StrCmpNoCase(IPBASE_P2CONSTAPPLDATA(uint8) Str1Ptr,
                                           IPBASE_P2CONSTAPPLDATA(uint8) Str2Ptr);
/***********************************************************************************************************************
 *  IpBase_StrCmpLenNoCase
 **********************************************************************************************************************/
/*! \brief         Compare strings length ignore case
 *  \details       Compare 2 strings with limited length ignoring the case
 *  \param[in]     Str1Ptr               pointer to string 1
 *  \param[in]     Str2Ptr               pointer to string 2
 *  \param[in]     StrLen                length of the search string [byte]
 *  \return        IPBASE_CMP_EQUAL      strings are equal
 *  \return        IPBASE_CMP_NOT_EQUAL  strings are not equal, or other error condition occurred
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          String subsets are accepted (i.e. "Hello"=="Hello World") case is ignored (i.e. "Hello" == "HELLO").
 **********************************************************************************************************************/
IPBASE_FUNCCODE(uint8) IpBase_StrCmpLenNoCase(IPBASE_P2CONSTAPPLDATA(uint8) Str1Ptr,
                                              IPBASE_P2CONSTAPPLDATA(uint8) Str2Ptr,
                                              uint16 StrLen);
/***********************************************************************************************************************
 *  IpBase_StrFindSubStr
 **********************************************************************************************************************/
/*! \brief         Search for sub-string
 *  \details       Searches for the first occurrence of sub-string within a string (e.g. string "hello world",
 *                 sub-string "world")
 *  \param[in]     StrPtr               pointer to string
 *  \param[in]     SubStrPtr            pointer to sub string
 *  \param[in]     StrLen               length of the string [byte]
 *  \param[in]     SubStrLen            length of the sub string [byte]
 *  \return        PosByte              position in string where the sub-string starts
 *  \return        IPBASE_STR_LEN_INVALID sub-string not found or error
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          The memory addressed has to be as large as given by string length parameter.
 **********************************************************************************************************************/
IPBASE_FUNCCODE(uint32) IpBase_StrFindSubStr(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                             IPBASE_P2CONSTAPPLDATA(uint8) SubStrPtr,
                                             uint16 StrLen, uint16 SubStrLen);
/***********************************************************************************************************************
 *  IpBase_StrLen
 **********************************************************************************************************************/
/*! \brief         Get string length
 *  \details       Gets the length of the string.
 *  \param[in]     StrPtr                 pointer to string
 *  \param[in]     MaxLen                 maximum length of the search string [byte]
 *  \return        0..MaxLen-1            length of the string excluding the terminating '\0'
 *  \return        MaxLen                 if MaxLen is reached
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          The string has to be terminated by '\0', the memory addressed has to be as large as given by 
 *                 string length parameter.
 **********************************************************************************************************************/
IPBASE_FUNCCODE(uint32) IpBase_StrLen(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                      uint32 MaxLen);
/***********************************************************************************************************************
 *  IpBase_ConvInt2String
 **********************************************************************************************************************/
/*! \brief         Convert integer to string
 *  \details       Convert an integer number to an ASCII string (dec).
 *  \param[in]     IntVal            integer number
 *  \param[in,out] StrPtr            in: pointer to string, out: pointer to end of string
 *  \param[in,out] StrLenPtr         in: pointer to length of the string, out: pointer to length of read integer [byte]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          The memory addressed via string pointer has to be as large as given by string length parameter.
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvInt2String(uint32 IntVal,
                                                      IPBASE_PP2VARAPPLDATA(uint8) StrPtr,
                                                      IPBASE_P2VARAPPLDATA(uint8) StrLenPtr);
/***********************************************************************************************************************
 *  IpBase_ConvInt2HexString
 **********************************************************************************************************************/
/*! \brief         Convert integer to hex string
 *  \details       Convert an integer number to an ASCII string (hex).
 *  \param[in]     IntVal            integer number
 *  \param[in,out] StrPtr            in: pointer to string (hex coded), out: pointer to end of string
 *  \param[in,out] StrLenPtr         in: pointer to length of the string, out: pointer to length of read integer [byte]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          The memory addressed via string pointer has to be as large as given by string length parameter.
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvInt2HexString(uint32 IntVal,
                                                         IPBASE_PP2VARAPPLDATA(uint8) StrPtr,
                                                         IPBASE_P2VARAPPLDATA(uint8) StrLenPtr);
/***********************************************************************************************************************
 *  IpBase_ConvInt2StringBase
 **********************************************************************************************************************/
/*! \brief         Convert integer to string base conversion
 *  \details       Convert an integer number to an ASCII string (dec) without incrementing StrPtr but '\0' at end.
 *  \param[in]     IntVal            integer number
 *  \param[in]     StrPtr            pointer to string
 *  \param[in]     StrLen            length of the string [byte]
 *  \return        E_OK              integer converted
 *  \return        E_NOT_OK          integer conversion failed
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          The memory addressed via string pointer has to be as large as given by string length parameter.
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvInt2StringBase(uint32 IntVal,
                                                          IPBASE_P2VARAPPLDATA(uint8) StrPtr,
                                                          uint8 StrLen);
/***********************************************************************************************************************
 *  IpBase_ConvInt2StringFront
 **********************************************************************************************************************/
/*! \brief         Convert integer to string front
 *  \details       Convert an integer number to an ASCII string (dec) at front of string.
 *  \param[in]     IntVal            integer number
 *  \param[in,out] StrPtr            in: pointer to string, out: pointer to end of string
 *  \param[in,out] StrLenPtr         in: pointer to length of the string, out: pointer to length of read integer [byte]
 *  \return        E_OK              integer converted
 *  \return        E_NOT_OK          integer conversion failed
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          The memory addressed via string pointer has to be as large as given by string length parameter.
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvInt2StringFront(uint32 IntVal,
                                                           IPBASE_PP2VARAPPLDATA(uint8) StrPtr,
                                                           IPBASE_P2VARAPPLDATA(uint8) StrLenPtr);
/***********************************************************************************************************************
 *  IpBase_ConvArray2HexStringBase
 **********************************************************************************************************************/
/*! \brief         Convert array to string (hex) base
 *  \details       Convert an array number to an ASCII string (hex), omits leading '00'.
 *  \param[in]     ArrayPtr          pointer to array
 *  \param[in]     ArrayLen          array length [byte]
 *  \param[out]    StrPtr            pointer to start of converted string (has to provide (ArrayLen*2)+1 chars)
 *  \return        E_OK              array converted
 *  \return        E_NOT_OK          array conversion failed
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          Array [a0a1], ArrayLen 2 -> 'A0A1'. Array [00a1], ArrayLen 2 -> 'A1'.
 *                 The memory addressed via string pointer has to be large enough to store array length elements. The
 *                 memory addressed via array pointer has to be large enough to read out array length elements.
**********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvArray2HexStringBase(IPBASE_P2CONSTAPPLDATA(uint8) ArrayPtr,
                                                               uint16 ArrayLen,
                                                               IPBASE_P2VARAPPLDATA(uint8) StrPtr);
/***********************************************************************************************************************
 *  IpBase_ConvString2Int
 **********************************************************************************************************************/
/*! \brief         Convert string to integer
 *  \details       Convert an ASCII string (dec values) to an integer.
 *  \param[in]     StrPtr            pointer to string
 *  \param[in]     StrLen            length of the string [byte], length has to be 10 or less (uint32 limit)
 *  \param[out]    IntValPtr         pointer to integer number
 *  \return        E_OK              string could be converted to integer
 *  \return        E_NOT_OK          string could not be converted to integer
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          The memory addressed via string pointer has to be as large as given by string length parameter. The 
 *                 memory addressed via integer number pointer has to point to 4byte size integer (uint32). The string
 *                 content is not checked to contain valid integer numbers (i.e. 0-9).
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvString2Int(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr, uint8 StrLen,
                                                      IPBASE_P2VARAPPLDATA(uint32) IntValPtr);
/***********************************************************************************************************************
 *  IpBase_ConvString2IntDyn
 **********************************************************************************************************************/
/*! \brief         Convert string to integer dynamic
 *  \details       Convert an ASCII string (dec values) to an integer with dynamic length.
 *  \param[in]     StrPtr            pointer to string
 *  \param[in]     StrLen            length of the string [byte], length has to be 10 or less (uin32 limit)
 *  \param[out]    IntValPtr         pointer to integer number
 *  \return        E_OK              string could be converted to integer
 *  \return        E_NOT_OK          string could not be converted to integer
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          Str '12', StrLen 2 -> 12. Str '12', StrLen 1 -> 1.
 *                 The memory addressed via string pointer has to be as large as given by string length parameter. The 
 *                 memory addressed via integer number pointer has to point to 4byte size integer (uint32). 
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvString2IntDyn(IPBASE_PP2CONSTAPPLDATA(uint8) StrPtr,
                                                         IPBASE_P2VARAPPLDATA(uint8) StrLenPtr,
                                                         IPBASE_P2VARAPPLDATA(uint32) IntValPtr);
/***********************************************************************************************************************
 *  IpBase_ConvStringHex2Int
 **********************************************************************************************************************/
/*! \brief         Convert hex string to integer
 *  \details       Convert an ASCII string (hex values) to an integer.
 *  \param[in]     StrPtr            pointer to string
 *  \param[in]     StrLen            length of the string [byte], length has to be 8 or less (uint32 limit)
 *  \param[out]    IntValPtr         pointer to integer number
 *  \return        E_OK              string could be converted to integer
 *  \return        E_NOT_OK          string could not be converted to integer
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          Str 'a2', StrLen 2 -> 0xA2. Str 'a2', StrLen 1 -> 0xA.
 *                 The memory addressed via string pointer has to be as large as given by string length parameter. The 
 *                 memory addressed via integer number pointer has to point to 4byte size integer (uint32). The string
 *                 content is not checked to contain valid hexadecimal numbers (i.e. 0-9|A-F).
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvStringHex2Int(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr, uint8 StrLen,
                                                         IPBASE_P2VARAPPLDATA(uint32) IntValPtr);
/***********************************************************************************************************************
 *  IpBase_ConvStringHex2IntDyn
 **********************************************************************************************************************/
/*! \brief         Convert hex string to integer dynamic
 *  \details       Convert an ASCII string (hex values) to an integer with dynamic length.
 *  \param[in,out] StrPtr            in: pointer to string, out: pointer to end of string
 *  \param[in,out] StrIntLenPtr      in: length of the integer [digits], length has to be 8 or less (uint32 limit)
 *                                   out: length of the string [chars]
 *  \param[out]    IntValPtr         pointer to integer number
 *  \return        E_OK              string could be converted to integer
 *  \return        E_NOT_OK          string could not be converted to integer
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          Str '12', StrLen 2 -> 0x12. Str '12', StrLen 1 -> 0x1.
 *                 The memory addressed via string pointer has to be as large as given by string length parameter. The 
 *                 memory addressed via integer number pointer has to point to 4byte size integer (uint32). 
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvStringHex2IntDyn(IPBASE_PP2CONSTAPPLDATA(uint8) StrPtr,
                                                            IPBASE_P2VARAPPLDATA(uint8) StrIntLenPtr,
                                                            IPBASE_P2VARAPPLDATA(uint32) IntValPtr);
/***********************************************************************************************************************
 *  IpBase_ConvString2IntBase
 **********************************************************************************************************************/
/*! \brief         Convert string to integer base
 *  \details       Convert an ASCII string (dec values) to an integer.
 *  \param[in]     StrPtr            pointer to string
 *  \param[in]     StrMaxLen         max length of the string [byte], length has to be 10 or less (uint32 limit)
 *  \return        0-4294967295      string converted to integer
 *  \return        IPBASE_ULONG_MAX  string could not be converted to integer
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          Str '12', StrMaxLen 2 -> 12. Str '12', StrMaxLen 1 -> 1.
 *                 The memory addressed via string pointer has to be as large as given by string length parameter.
 **********************************************************************************************************************/
IPBASE_FUNCCODE(uint32) IpBase_ConvString2IntBase(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                                  uint8 StrMaxLen);
/***********************************************************************************************************************
 *  IpBase_ConvString2SignedIntBase
 **********************************************************************************************************************/
/*! \brief         Convert string to signed integer
 *  \details       Convert an ASCII string (decimal values) to a signed integer.
 *  \param[in]     StrPtr                  pointer to string
 *  \param[in]     StrMaxLen               max length of the string [byte], length has to be 10 or less (uin32 limit)
 *  \return        -2147483646-+2147483646 string converted to integer
 *  \return        IPBASE_SLONG_MAX        string could not be converted to integer
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          Str '12', StrMaxLen 2 -> 12. Str '12', StrMaxLen 1 -> 1. Str 'a' -> IPBASE_SLONG_MAX.
 *                 The memory addressed via string pointer has to be as large as given by string length parameter.
 **********************************************************************************************************************/
IPBASE_FUNCCODE(sint32) IpBase_ConvString2SignedIntBase(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                                        uint8 StrMaxLen);
/***********************************************************************************************************************
 *  IpBase_ConvHexString2ArrayBase
 **********************************************************************************************************************/
/*! \brief         Convert hex string to array base
 *  \details       Convert an ASCII hex string to an array number, omits leading '00'. Array is filled up with 0.
 *  \param[out]    ArrayPtr          pointer to array
 *  \param[in]     ArrayLen          array length [byte]
 *  \param[in]     StrPtr            pointer to string
 *  \return        E_OK              array converted
 *  \return        E_NOT_OK          array conversion failed
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          Array [a0a1], ArrayLen 2 -> 'A0A1'. Array [00a1], ArrayLen 2 -> 'A1'.
 *                 The memory addressed via array pointer has to be as large as given by array length parameter. The
 *                 memory addressed via string pointer has to be large enough for array length parameter characters.
**********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvHexString2ArrayBase(IPBASE_P2VARAPPLDATA(uint8) ArrayPtr,
                                                               uint16 ArrayLen,
                                                               IPBASE_CONSTP2CONSTAPPLDATA(uint8) StrPtr);
#  define IPBASE_STOP_SEC_CODE
#  include "MemMap.h"
#endif
  /* IPBASE_STRING_H */
/**********************************************************************************************************************
 *  END OF FILE: IpBase_String.h
 *********************************************************************************************************************/
