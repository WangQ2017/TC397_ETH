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
 *         File:  IpBase_String.c
 *      Project:  MICROSAR ETH
 *    Component:  SysService_IpBase
 *       Module:  MICROSAR IP Base
 *    Generator:  None
 *
 *  Description:  String API implementation
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
#define IPBASE_STRING_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "IpBase.h"           /* PRQA S 3453 3 */ /* MD_MSR_FctLikeMacro */
#include "IpBase_Priv.h"

/**********************************************************************************************************************
 *  CONSISTENCY CHECK
 *********************************************************************************************************************/
/* Check consistency of source and header file. */
#if ( (IPBASE_SW_MAJOR_VERSION != 04u) \
   || (IPBASE_SW_MINOR_VERSION != 00u) \
   || (IPBASE_SW_PATCH_VERSION != 07u) )
# error "Vendor specific version numbers of IpBase_String.c and IpBase.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define IPBASE_STR_LOW_CASE_ASCII_OFF           (32u)   /*<! offset 'a' - 'A' for case insensitive comparison */
#define IPBASE_STR_UPP_CASE_ASCII_OFF           (55u)   /*<! offset 'A' for alphabetic letter comparison */
#define IPBASE_STR_INT_ASCII_OFF                (48u)   /*<! offset '0' for integer comparison */
#define IPBASE_STR_LOW_NIBBLE_BIT_MASK          (0x0Fu) /*<! bit mask to obtain low nibble */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define IPBASE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/***********************************************************************************************************************
 *  IpBase_ConvHexString2ArrayBaseHlp
 **********************************************************************************************************************/
/*! \brief         Convert hex string to array base
 *  \details       Convert an ASCII hex digit to a number
 *  \param[in]     Digit             digit to be converted
 *  \return        Number            number of digit
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \trace         CREQ-120249
 *  \note          Digit 'a' -> A, '8' -> 8
 **********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(uint8) IpBase_ConvHexString2ArrayBaseHlp(uint8 Digit);
/***********************************************************************************************************************
 *  IpBase_ConvStringHex2IntDynHlp
 **********************************************************************************************************************/
/*! \brief         Convert hex string to integer dynamic
 *  \details       Convert an ASCII string (hex values) to an integer with dynamic length
 *  \param[in,out] StrPtr            in: pointer to string, out: pointer to end of string
 *  \param[in,out] StrIntLenPtr      in: length of the integer [digits], out: length of string
 *  \param[out]    IntValPtr         pointer to integer number
 *  \return        E_OK              string could be converted to integer
 *  \return        E_NOT_OK          string could not be converted to integer
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \trace         CREQ-120249
 *  \note          Str '12', StrLen 2 -> 0x12. Str '12', StrLen 1 -> 0x1.
 **********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvStringHex2IntDynHlp(IPBASE_PP2CONSTAPPLDATA(uint8) StrPtr,
                                                                            IPBASE_P2VARAPPLDATA(uint8) StrIntLenPtr,
                                                                            IPBASE_P2VARAPPLDATA(uint32) IntValPtr);
/***********************************************************************************************************************
 *  IpBase_StrFindSubStrHlp
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
 *  \context       TASK
 *  \reentrant     TRUE
 *  \trace         CREQ-120249
 **********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(uint32) IpBase_StrFindSubStrHlp(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                                             IPBASE_P2CONSTAPPLDATA(uint8) SubStrPtr,
                                                             uint16 StrLen, uint16 SubStrLen);
/***********************************************************************************************************************
 *  IpBase_ConvString2SignedIntBaseHlp
 **********************************************************************************************************************/
/*! \brief         Convert string to signed integer
 *  \details       Convert an ASCII string (decimal values) to a signed integer.
 *  \param[in]     StrPtr                  pointer to string
 *  \param[in]     StrMaxLen               max length of the string [byte], length has to be 10 or less (uin32 limit)
 *  \return        -2147483646-+2147483647 string converted to integer
 *  \return        IPBASE_SLONG_MAX        string could not be converted to integer
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-120249
 *  \note          Str '12', StrMaxLen 2 -> 12. Str '12', StrMaxLen 1 -> 1. Str 'a' -> IPBASE_SLONG_MAX.
 *                 The memory addressed via string pointer has to be as large as given by string length parameter.
 **********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(sint32) IpBase_ConvString2SignedIntBaseHlp(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                                                        uint8 StrMaxLen);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  IpBase_StrCpy
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_FUNCCODE(uint16) IpBase_StrCpy(IPBASE_P2VARAPPLDATA(uint8) TgtPtr,
                                      IPBASE_P2CONSTAPPLDATA(uint8) SrcPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = IPBASE_E_NO_ERROR;
  uint16 byteIdx = 0u;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (TgtPtr == NULL_PTR) || (SrcPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Copy all string characters */
    while ( SrcPtr[byteIdx] != (uint8)'\0' )
    {
      TgtPtr[byteIdx] = SrcPtr[byteIdx]; /* SBSW_IPBASE_API_ZERO_TERMINATED_STRING */
      byteIdx++;
      if ( byteIdx == IPBASE_USHRT_MAX )
      {
        break; /* avoid overflow */
      }
    }
    TgtPtr[byteIdx] = (uint8)'\0'; /* SBSW_IPBASE_API_ZERO_TERMINATED_STRING */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #30 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_STR_COPY, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return byteIdx;
} /* IpBase_StrCpy() */
/**********************************************************************************************************************
 *  IpBase_StrCpyMaxLen
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_FUNCCODE(uint32) IpBase_StrCpyMaxLen(IPBASE_P2VARAPPLDATA(uint8) TgtPtr,
                                            IPBASE_P2CONSTAPPLDATA(uint8) SrcPtr, uint32 MaxLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8  errorId = IPBASE_E_NO_ERROR;
  uint32 byteIdx = 0u;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (TgtPtr == NULL_PTR) || (SrcPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Copy all string characters */
    while ( SrcPtr[byteIdx] != (uint8)'\0' )
    {
      TgtPtr[byteIdx] = SrcPtr[byteIdx]; /* SBSW_IPBASE_API_ZERO_TERMINATED_STRING */
      byteIdx++;
      if ( byteIdx == MaxLen )
      { /* #30 Check length limitation */
        break; /* avoid overflow */
      }
    }
    TgtPtr[byteIdx] = (uint8)'\0'; /* SBSW_IPBASE_API_ZERO_TERMINATED_STRING */
  }
  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #40 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_STR_COPY_MAX_LEN, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return byteIdx;
} /* IpBase_StrCpyMaxLen() */
/**********************************************************************************************************************
 *  IpBase_StrCmp
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_FUNCCODE(uint8) IpBase_StrCmp(IPBASE_P2CONSTAPPLDATA(uint8) Str1Ptr,
                                     IPBASE_P2CONSTAPPLDATA(uint8) Str2Ptr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8  retVal  = IPBASE_CMP_EQUAL;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (Str1Ptr == NULL_PTR) || (Str2Ptr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint32_least byteIdx = 0u;

    /* #20 Compare all string character */
    while ( (Str1Ptr[byteIdx] != (uint8)'\0') && (Str2Ptr[byteIdx] != (uint8)'\0') &&
            (retVal != IPBASE_CMP_NOT_EQUAL) )
    {
      if ( Str1Ptr[byteIdx] == Str2Ptr[byteIdx] )
      {
        byteIdx++;
      }
      else
      {
        retVal = IPBASE_CMP_NOT_EQUAL;
      }
      if ( byteIdx == IPBASE_USHRT_MAX )
      {
        retVal = IPBASE_CMP_NOT_EQUAL; /* avoid overflow */
      }
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #30 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_STR_CMP, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_StrCmp() */
/***********************************************************************************************************************
 *  IpBase_StrCmpLen
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(uint8) IpBase_StrCmpLen(IPBASE_P2CONSTAPPLDATA(uint8) Str1Ptr,
                                        IPBASE_P2CONSTAPPLDATA(uint8) Str2Ptr,
                                        uint16 StrLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8  retVal  = IPBASE_CMP_EQUAL;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (Str1Ptr == NULL_PTR) || (Str2Ptr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint16_least byteIdx;

    /* #20 Compare all string character limited by length limitation */
    for(byteIdx = 0u; byteIdx < StrLen; byteIdx++)
    {
      /* #30 Compare character */
      if(Str1Ptr[byteIdx] != Str2Ptr[byteIdx])
      {
        /* #40 Mismatch -> abort comparison */
        retVal = IPBASE_CMP_NOT_EQUAL;
        break;
      }
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #50 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_STR_CMP_LEN, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_StrCmpLen() */
/**********************************************************************************************************************
 *  IpBase_StrCmpNoCase
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_FUNCCODE(uint8) IpBase_StrCmpNoCase(IPBASE_P2CONSTAPPLDATA(uint8) Str1Ptr,
                                           IPBASE_P2CONSTAPPLDATA(uint8) Str2Ptr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8  retVal  = IPBASE_CMP_EQUAL;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (Str1Ptr == NULL_PTR) || (Str2Ptr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint16_least byteIdx = 0u;
    uint8        char1upCase;
    uint8        char2upCase;

    /* #20 Compare all string character */
    while ( ( Str1Ptr[byteIdx] != (uint8)'\0') && (Str2Ptr[byteIdx] != (uint8)'\0') &&
            (retVal != IPBASE_CMP_NOT_EQUAL) )
    { /* #30 Transform character to upper case if required */
      char1upCase = (((Str1Ptr[byteIdx] <= (uint8)'z') && (Str1Ptr[byteIdx] >= (uint8)'a')) ? \
                     (Str1Ptr[byteIdx] - (uint8)IPBASE_STR_LOW_CASE_ASCII_OFF) : Str1Ptr[byteIdx]);
      char2upCase = (((Str2Ptr[byteIdx] <= (uint8)'z') && (Str2Ptr[byteIdx] >= (uint8)'a')) ? \
                     (Str2Ptr[byteIdx] - (uint8)IPBASE_STR_LOW_CASE_ASCII_OFF) : Str2Ptr[byteIdx]);
      /* #40 Compare single string character */
      if ( char1upCase == char2upCase )
      {
        byteIdx++;
      }
      else
      { /* #50 Mismatch -> abort comparison */
        retVal = IPBASE_CMP_NOT_EQUAL;
      }
      if ( byteIdx == IPBASE_USHRT_MAX )
      { /* #60 Overflow -> abort comparison */
        retVal = IPBASE_CMP_NOT_EQUAL; /* avoid overflow */
      }
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #70 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_STR_CMP_NO_CASE, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_StrCmpNoCase() */
/***********************************************************************************************************************
 *  IpBase_StrCmpLenNoCase
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(uint8) IpBase_StrCmpLenNoCase(IPBASE_P2CONSTAPPLDATA(uint8) Str1Ptr,
                                              IPBASE_P2CONSTAPPLDATA(uint8) Str2Ptr,
                                              uint16 StrLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8  retVal  = IPBASE_CMP_EQUAL;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (Str1Ptr == NULL_PTR) || (Str2Ptr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint16_least byteIdx;
    uint8   char1upCase;
    uint8   char2upCase;

    /* #20 Compare all string character limited by length limitation */
    for(byteIdx = 0u; byteIdx < StrLen; byteIdx++)
    { /* #30 Transform character to upper case if required */
      char1upCase = (((Str1Ptr[byteIdx] <= (uint8)'z')&&((uint8)'a' <= Str1Ptr[byteIdx])) ? \
                     (Str1Ptr[byteIdx] - (uint8)IPBASE_STR_LOW_CASE_ASCII_OFF) : (Str1Ptr[byteIdx]));
      char2upCase = (((Str2Ptr[byteIdx] <= (uint8)'z')&&((uint8)'a' <= Str2Ptr[byteIdx])) ? \
                     (Str2Ptr[byteIdx] - (uint8)IPBASE_STR_LOW_CASE_ASCII_OFF) : (Str2Ptr[byteIdx]));
      /* #40 Compare single string character */
      if ( char1upCase != char2upCase )
      {
        /* #50 Mismatch -> abort comparison */
        retVal = IPBASE_CMP_NOT_EQUAL;
        break;
      }
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #60 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_STR_CMP_LEN_NO_CASE, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_StrCmpLenNoCase() */
/***********************************************************************************************************************
 *  IpBase_StrFindSubStr
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(uint32) IpBase_StrFindSubStr(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                            IPBASE_P2CONSTAPPLDATA(uint8) SubStrPtr,
                                            uint16 StrLen, uint16 SubStrLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 retVal = IPBASE_STR_LEN_INVALID;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer and valid length parameter */
  if ( (StrPtr == NULL_PTR) || (SubStrPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else if ( StrLen < SubStrLen )
  {
    errorId = IPBASE_E_INV_PARAM;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Find substring using helper function */
    retVal = IpBase_StrFindSubStrHlp(StrPtr, SubStrPtr, StrLen, SubStrLen); /* SBSW_IPBASE_PASSING_API_POINTER */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #30 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_STR_FIND_SUB_STR, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_StrFindSubStr() */
/***********************************************************************************************************************
 *  IpBase_StrLen
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(uint32) IpBase_StrLen(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                      uint32 MaxLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 retVal = MaxLen;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( StrPtr == NULL_PTR )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint32_least byteIdx;

    /* #20 Check all string character */
    for ( byteIdx = 0; byteIdx <= MaxLen; byteIdx++ )
    {
      /* #30 Check for end of string indication */
      if (StrPtr[byteIdx] == (uint8)'\0')
      {
        retVal = (uint32) byteIdx;
        break;
      }
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #40 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_STR_LEN, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_StrLen() */
/***********************************************************************************************************************
 *  IpBase_ConvInt2String
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvInt2String(uint32 IntVal,
                                                      IPBASE_PP2VARAPPLDATA(uint8) StrPtr,
                                                      IPBASE_P2VARAPPLDATA(uint8) StrLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (StrPtr == NULL_PTR) || (StrLenPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8  digit;
    uint8  pos = 0u;
    uint32 remIntVal = IntVal;
    IPBASE_P2VARAPPLDATA(uint8) intStrPtr;

    /* #20 Convert all digits */
    intStrPtr = *StrPtr;
    while(pos < *StrLenPtr)
    {
      digit = (uint8) (remIntVal % 10u);
      intStrPtr[*StrLenPtr - (pos + 1u)] = (uint8)(digit + IPBASE_STR_INT_ASCII_OFF); /* 0..9 */ /* SBSW_IPBASE_API_STRING_TARGET_FOR_DATA */
      remIntVal = remIntVal / 10u;
      pos++;

      if(remIntVal == 0u)
      { /* #30 All digits converted */
        *StrPtr = &(intStrPtr[*StrLenPtr - pos]); /* SBSW_IPBASE_VALID_API_POINTER */
        *StrLenPtr = pos; /* SBSW_IPBASE_VALID_API_POINTER */
        retVal = E_OK;
        break;
      }
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #40 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CONV_INT_TO_STR, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_ConvInt2String() */
/***********************************************************************************************************************
 *  IpBase_ConvInt2StringBase
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvInt2StringBase(uint32 IntVal,
                                                          IPBASE_P2VARAPPLDATA(uint8) StrPtr,
                                                          uint8 StrLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( StrPtr == NULL_PTR )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8 digits[IPBASE_INT_DIGIT_MAX];
    uint8_least  digPos = 0u;
    uint32 remIntVal = IntVal;

    /* #20 Scan all digits */
    if ( remIntVal == 0u )
    {
      digits[0] = 0u; /* SBSW_IPBASE_INT_DIGIT_MAX */
      digPos++;
    }
    else
    {
      while ( remIntVal > 0u )
      {
        digits[digPos] = (uint8) (remIntVal % 10u); /* SBSW_IPBASE_INT_DIGIT_MAX */
        remIntVal = remIntVal / 10u;
        digPos++;
      }
    }

    if ( digPos < StrLen )
    { /* #30 Convert all digits */
      uint8_least maxPos = digPos;
      uint8_least strPos;

      StrPtr[maxPos] = (uint8)'\0'; /* SBSW_IPBASE_API_STRING_TARGET_FOR_DATA */
      for ( strPos = 0u; strPos < maxPos; strPos++ )
      {
        digPos = maxPos - strPos - 1u;
        StrPtr[strPos] = (uint8)(digits[digPos] + IPBASE_STR_INT_ASCII_OFF); /* SBSW_IPBASE_API_STRING_TARGET_FOR_DATA */
      }

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #40 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CONV_INT_TO_STR_BASE, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_ConvInt2StringBase() */
/***********************************************************************************************************************
 *  IpBase_ConvArray2HexStringBase
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvArray2HexStringBase(IPBASE_P2CONSTAPPLDATA(uint8) ArrayPtr,
                                                               uint16 ArrayLen,
                                                               IPBASE_P2VARAPPLDATA(uint8) StrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (ArrayPtr == NULL_PTR) || (StrPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8  digit;
    uint16 arrayIdx = 0u;
    uint16 strIdx = 0u;

    /* #20 Scan array */
    while(arrayIdx < ArrayLen)
    { /* #30 Convert hex number */
      digit = ArrayPtr[arrayIdx]>>4u;
      if(digit < 10u)
      {
        StrPtr[strIdx] = (uint8)(digit + IPBASE_STR_INT_ASCII_OFF); /* 0..9 */ /* SBSW_IPBASE_API_STRING_TARGET_FOR_DATA */
      }
      else
      {
        StrPtr[strIdx] = (uint8)(digit + IPBASE_STR_UPP_CASE_ASCII_OFF); /* A..F */ /* SBSW_IPBASE_API_STRING_TARGET_FOR_DATA */
      }
      strIdx++;
      digit = (uint8) (ArrayPtr[arrayIdx]&0xFU);
      if(digit < 10u)
      {
        StrPtr[strIdx] = (uint8)(digit + IPBASE_STR_INT_ASCII_OFF); /* 0..9 */ /* SBSW_IPBASE_API_STRING_TARGET_FOR_DATA */
      }
      else
      {
        StrPtr[strIdx] = (uint8)(digit + IPBASE_STR_UPP_CASE_ASCII_OFF); /* A..F */ /* SBSW_IPBASE_API_STRING_TARGET_FOR_DATA */
      }
      strIdx++;
      arrayIdx++;
    }
    /* #40 Finalize string */
    if ( strIdx == 0u )
    {
      StrPtr[strIdx] = (uint8)'0'; /* SBSW_IPBASE_API_STRING_TARGET_FOR_DATA */
      strIdx++;
    }
    StrPtr[strIdx] = (uint8)'\0'; /* SBSW_IPBASE_API_STRING_TARGET_FOR_DATA */
    retVal = E_OK;
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #50 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CONV_ARRAY_TO_HEX_STR_BASE, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_ConvArray2HexStringBase() */
/***********************************************************************************************************************
 *  IpBase_ConvInt2StringFront
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvInt2StringFront(uint32 IntVal,
                                                           IPBASE_PP2VARAPPLDATA(uint8) StrPtr,
                                                           IPBASE_P2VARAPPLDATA(uint8) StrLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (StrPtr == NULL_PTR) || (StrLenPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8 digits[IPBASE_INT_DIGIT_MAX];
    uint8_least digPos = 0;
    uint32 remIntVal = IntVal;

    /* #20 Scan all digits */
    if ( remIntVal == 0u )
    {
      digits[0] = (uint8)0u; /* SBSW_IPBASE_INT_DIGIT_MAX */
      digPos++;
    }
    else
    {
      while ( remIntVal > 0u )
      {
        digits[digPos] = (uint8) (remIntVal % 10u); /* SBSW_IPBASE_INT_DIGIT_MAX */
        remIntVal = remIntVal / 10u;
        digPos++;
      }
    }

    if ( digPos <= *StrLenPtr )
    { /* #30 Convert all digits */
      uint8_least maxPos = digPos;
      uint8_least strPos;

      (*StrPtr)[maxPos] = (uint8)'\0'; /* SBSW_IPBASE_API_STRING_TARGET_FOR_DATA */
      for ( strPos = 0; strPos < maxPos; strPos++ )
      {
        digPos = maxPos - strPos - 1u;
        (*StrPtr)[strPos] = (uint8)(digits[digPos] + IPBASE_STR_INT_ASCII_OFF); /* SBSW_IPBASE_API_STRING_TARGET_FOR_DATA */
      }
      *StrLenPtr -= (uint8) maxPos;      /* SBSW_IPBASE_API_STRING_TARGET_FOR_DATA */
      *StrPtr    = &((*StrPtr)[maxPos]); /* SBSW_IPBASE_API_STRING_TARGET_FOR_DATA */
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #40 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CONV_INT_TO_STR_FRONT, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_ConvInt2StringFront() */
/***********************************************************************************************************************
 *  IpBase_ConvInt2HexString
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvInt2HexString(uint32 IntVal,
                                                         IPBASE_PP2VARAPPLDATA(uint8) StrPtr,
                                                         IPBASE_P2VARAPPLDATA(uint8) StrLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (StrPtr == NULL_PTR) || (StrLenPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8_least strPos = 0u;
    uint32 remIntVal = IntVal;
    IPBASE_P2VARAPPLDATA(uint8) intStrPtr;

    /* #20 Scan all characters */
    intStrPtr = (IPBASE_P2VARAPPLDATA(uint8)) *StrPtr;
    while( (strPos < *StrLenPtr) && (remIntVal != 0u) )
    { /* #30 Convert digit */
      uint8 digit = (uint8)(remIntVal & IPBASE_STR_LOW_NIBBLE_BIT_MASK);
      uint8_least intStrPos = *StrLenPtr - strPos - 1u;

      if(digit < 10u)
      {
        intStrPtr[intStrPos] = (uint8)(digit + IPBASE_STR_INT_ASCII_OFF); /* 0..9 */ /* SBSW_IPBASE_API_ARGUMENT_LEN */
      }
      else
      {
        intStrPtr[intStrPos] = (uint8)(digit + IPBASE_STR_UPP_CASE_ASCII_OFF); /* A..F (Hint: 'A'-10) */ /* SBSW_IPBASE_API_ARGUMENT_LEN */
      }

      remIntVal = remIntVal >> 4u;
      strPos++;
    }
    if(remIntVal == 0u)
    { /* #40 Finalize string */
      *StrPtr = &(intStrPtr[*StrLenPtr - strPos]); /* SBSW_IPBASE_VALID_API_POINTER */
      *StrLenPtr = (uint8) strPos; /* SBSW_IPBASE_VALID_API_POINTER */
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #50 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CONV_INT_TO_HEX_STR, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_ConvInt2HexString() */
/***********************************************************************************************************************
 *  IpBase_ConvString2Int
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvString2Int(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                                      uint8 StrLen,
                                                      IPBASE_P2VARAPPLDATA(uint32) IntValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer and invalid param */
  if ( (StrPtr == NULL_PTR) || (IntValPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else if(StrLen > IPBASE_INT_DIGIT_MAX)
  {
    errorId = IPBASE_E_INV_PARAM;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8_least  posA;
    uint32       locLen = 0u;

    /* #20 Scan all digits */
    for ( posA = 0; posA < StrLen; posA++ )
    { /* 0x30-0x39 represents '0'-'9' -> -'0' does not have to be coded */
      locLen *= (uint32)10u;
      locLen += (uint32)(StrPtr[posA] & IPBASE_STR_LOW_NIBBLE_BIT_MASK);                                                /* PRQA S 4391 */ /* MD_IpBase_4391 */
    }
    *IntValPtr = locLen; /* SBSW_IPBASE_VALID_API_POINTER */
    retVal = E_OK;
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #30 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CONV_STR_TO_INT, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_ConvString2Int() */
/***********************************************************************************************************************
 *  IpBase_ConvString2IntDyn
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvString2IntDyn(IPBASE_PP2CONSTAPPLDATA(uint8) StrPtr,
                                                         IPBASE_P2VARAPPLDATA(uint8) StrLenPtr,
                                                         IPBASE_P2VARAPPLDATA(uint32) IntValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (StrPtr == NULL_PTR) || (*StrPtr == NULL_PTR) || (StrLenPtr == NULL_PTR) || (IntValPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else if(*StrLenPtr > IPBASE_INT_DIGIT_MAX)
  {
    errorId = IPBASE_E_INV_PARAM;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8        digit;
    uint8_least  posA;
    uint32       locLen = 0u;

    /* #20 Scan all characters */
    for ( posA = 0; posA < *StrLenPtr; posA++ )
    {
      digit = (*StrPtr)[posA];
      if ( (digit < (uint8)'0') || (digit > (uint8)'9') )
      { /* #30 Found end of number */
        break;
      }
      locLen *= 10u;
      locLen += (uint32)(digit - (uint8)'0');                                                                           /* PRQA S 4391 */ /* MD_IpBase_4391 */
    }
    *StrLenPtr = (uint8) posA; /* SBSW_IPBASE_VALID_API_POINTER */
    *IntValPtr = locLen; /* SBSW_IPBASE_VALID_API_POINTER */
    *StrPtr    = &((*StrPtr)[posA]); /* SBSW_IPBASE_VALID_API_POINTER */
    retVal = E_OK;
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #40 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CONV_STR_TO_INT_DYN, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_ConvString2IntDyn() */
/***********************************************************************************************************************
 *  IpBase_ConvStringHex2Int
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvStringHex2Int(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr, uint8 StrLen,
                                                         IPBASE_P2VARAPPLDATA(uint32) IntValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer and invalid param */
  if ( (StrPtr == NULL_PTR) || (IntValPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else if(StrLen > IPBASE_HEX_INT_DIGIT_MAX)
  {
    errorId = IPBASE_E_INV_PARAM;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8_least  pos;
    uint32 intVal = 0u;

    /* #20 Scan all characters */
    for(pos = 0u; pos < StrLen; pos++)
    {
      /* #30 Convert ASCII character to integer */
      uint8 singleChar = StrPtr[pos];
      uint8 singleNumber;
      if(singleChar <= (uint8)0x39)
      {
        /* digit 0..9 */
        singleNumber = (uint8)(singleChar & IPBASE_STR_LOW_NIBBLE_BIT_MASK);
      }
      else
      {
        /* digit A..F */
        singleNumber = (uint8)((singleChar & IPBASE_STR_LOW_NIBBLE_BIT_MASK) + 9u);
      }
      intVal += ((uint32)(singleNumber)) << (4u * (uint8)(StrLen - pos - 1u));
    }
    *IntValPtr = intVal; /* SBSW_IPBASE_VALID_API_POINTER */
    retVal = E_OK;
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #40 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CONV_HEX_STR_TO_INT, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_ConvStringHex2Int() */
/***********************************************************************************************************************
 *  IpBase_ConvString2HexIntDyn
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
/* PRQA S 3673 1 */ /* MD_MSR_Rule8.13 */
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvStringHex2IntDyn(IPBASE_PP2CONSTAPPLDATA(uint8) StrPtr,
                                                            IPBASE_P2VARAPPLDATA(uint8) StrIntLenPtr,
                                                            IPBASE_P2VARAPPLDATA(uint32) IntValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (StrPtr == NULL_PTR) || (*StrPtr == NULL_PTR) || (StrIntLenPtr == NULL_PTR) || (IntValPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else if(*StrIntLenPtr > IPBASE_HEX_INT_DIGIT_MAX)
  {
    errorId = IPBASE_E_INV_PARAM;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Convert string helper */
    retVal = IpBase_ConvStringHex2IntDynHlp(StrPtr, StrIntLenPtr, IntValPtr); /* SBSW_IPBASE_PASSING_API_POINTER */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #30 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CONV_HEX_STR_TO_INT_DYN, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_ConvString2IntDyn() */
/***********************************************************************************************************************
 *  IpBase_ConvString2IntBase
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(uint32) IpBase_ConvString2IntBase(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                                  uint8 StrMaxLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8  errorId = IPBASE_E_NO_ERROR;
  uint32 locLen = 0u;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( StrPtr == NULL_PTR )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else if(StrMaxLen > IPBASE_INT_DIGIT_MAX)
  {
    errorId = IPBASE_E_INV_PARAM;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8        digit;
    uint8_least  posA;

    /* #20 Scan all characters */
    for ( posA = 0; posA < StrMaxLen; posA++ )
    {
      /* #30 Extract single digit */
      digit = (StrPtr)[posA];
      if ( (digit < (uint8)'0') || (digit > (uint8)'9') )
      { /* #40 Check for end of number and break if found */
        break;
      }
      locLen *= 10u;
      locLen += (uint32)(digit - (uint8)'0');                                                                           /* PRQA S 4391 */ /* MD_IpBase_4391 */
    }
    if ( posA == 0u )
    {
      locLen = IPBASE_ULONG_MAX;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #50 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CONV_STR_TO_INT_BASE, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return locLen;
} /* IpBase_ConvString2IntBase() */
/***********************************************************************************************************************
 *  IpBase_ConvString2SignedIntBase
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(sint32) IpBase_ConvString2SignedIntBase(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr, uint8 StrMaxLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8  errorId = IPBASE_E_NO_ERROR;
  sint32 retVal  = IPBASE_SLONG_MAX;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( StrPtr == NULL_PTR )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else if(StrMaxLen > IPBASE_INT_DIGIT_MAX)
  {
    errorId = IPBASE_E_INV_PARAM;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call conversion helper function */
    retVal = IpBase_ConvString2SignedIntBaseHlp(StrPtr, StrMaxLen); /* SBSW_IPBASE_PASSING_API_POINTER */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #30 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CONV_STR_TO_SIGNED_INT_BASE, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_ConvString2SignedIntBase() */
/***********************************************************************************************************************
 *  IpBase_ConvHexString2ArrayBase
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvHexString2ArrayBase(IPBASE_P2VARAPPLDATA(uint8) ArrayPtr,
                                                               uint16 ArrayLen,
                                                               IPBASE_CONSTP2CONSTAPPLDATA(uint8) StrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (ArrayPtr == NULL_PTR) || (StrPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint16_least arrayIdx;
    uint16_least strIdx = 0u;
    uint8  digit0 = 0u;
    uint8  digit1 = 0u;

    /* #20 Scan through array */
    for ( arrayIdx = 0; arrayIdx < ArrayLen; arrayIdx++ )
    {
      /* #30 Convert hex digit */
      if ( (digit0 != IPBASE_UCHAR_MAX) && (digit1 != IPBASE_UCHAR_MAX)  )
      {
        digit0 = IpBase_ConvHexString2ArrayBaseHlp(StrPtr[strIdx]);
        digit1 = IpBase_ConvHexString2ArrayBaseHlp(StrPtr[strIdx+1u]);
      }
      if ( (digit0 != IPBASE_UCHAR_MAX) && (digit1 != IPBASE_UCHAR_MAX)  )
      {
        ArrayPtr[arrayIdx] = (uint8)((digit0 << 4u) + digit1); /* SBSW_IPBASE_API_ARGUMENT_LEN */
      }
      else
      { /* #40 Fill up with 0 */
        ArrayPtr[arrayIdx] = 0u; /* SBSW_IPBASE_API_ARGUMENT_LEN */
      }
      strIdx += 2u;
    }
    retVal = E_OK;
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #50 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CONV_HEX_STR_TO_ARRAY_BASE, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_ConvString2SignedIntBase() */
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/***********************************************************************************************************************
 *  IpBase_StrFindSubStrHlp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(uint32) IpBase_StrFindSubStrHlp(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                                             IPBASE_P2CONSTAPPLDATA(uint8) SubStrPtr,
                                                             uint16 StrLen, uint16 SubStrLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32       retVal  = IPBASE_STR_LEN_INVALID;
  uint16_least readPos    = 0u;
  uint16       subReadPos = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compare all string character */
  while ( readPos < StrLen )
  {
    /* #20 Check single character */
    if( (subReadPos > 0u) && (StrPtr[readPos] != SubStrPtr[subReadPos]) )
    { /* #30 Unequal character found, restart sub string search with next character */
      readPos   = (readPos + 1u) - subReadPos;
      subReadPos = 0u;
    }
    if(StrPtr[readPos] == SubStrPtr[subReadPos])
    { /* #40 equal character found, continue sub string search */
      subReadPos++;
      if ( subReadPos == SubStrLen )
      { /* #50 Complete sub-string found */
        retVal = (uint32) ((readPos + 1u) - subReadPos);                                                                /* PRQA S 4391 */ /* MD_IpBase_4391 */
        break;
      }
    }
    readPos++;
  }

  return retVal;
} /* IpBase_StrFindSubStrHlp() */
/***********************************************************************************************************************
 *  IpBase_ConvString2IntDynHlp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(Std_ReturnType) IpBase_ConvStringHex2IntDynHlp(IPBASE_PP2CONSTAPPLDATA(uint8) StrPtr,
                                                                            IPBASE_P2VARAPPLDATA(uint8) StrIntLenPtr,
                                                                            IPBASE_P2VARAPPLDATA(uint32) IntValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8        digit;
  uint8_least  posA;
  uint32       locInt = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Scan all characters */
  for(posA = 0; posA < *StrIntLenPtr; posA++)
  {
    /* #20 Scan single character */
    digit = (*StrPtr)[posA];
    if ( (digit >= (uint8)'0')&&(digit <= (uint8)'9') )
    {
      digit -= (uint8)'0';
    }
    else if ( (digit >= (uint8)'A')&&(digit <= (uint8)'F') )
    {
      digit -= (uint8)('A' - 10u); /* i.e. digit = digit - 'A' + 10 */
    }
    else if ( (digit >= (uint8)'a') && (digit <= (uint8)'f') )
    {
      digit -= (uint8)('a' - 10u); /* i.e. digit = digit - 'a' + 10 */
    }
    else
    { /* end of number */
      break;
    }
    /* #30 Add single character to result */
    locInt <<= 4u; /* i.e. locInt = locInt * 16 */
    locInt += digit;
  }
  /* #40 Evaluate result */
  *StrIntLenPtr = (uint8) posA; /* SBSW_IPBASE_VALID_API_POINTER */
  *IntValPtr    = locInt; /* SBSW_IPBASE_VALID_API_POINTER */
  *StrPtr       = &((*StrPtr)[posA]); /* SBSW_IPBASE_VALID_API_POINTER */

  return E_OK;
} /* IpBase_ConvString2IntDynHlp() */
/***********************************************************************************************************************
 *  IpBase_ConvHexString2ArrayBaseHlp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(uint8) IpBase_ConvHexString2ArrayBaseHlp(uint8 Digit)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert single hex digit from string */
  if( (Digit >= (uint8)'0') && (Digit <= (uint8)'9') )
  {
    retVal = Digit - (uint8)'0'; /* 0..9 */
  }
  else if( (Digit >= (uint8)'a') && (Digit <= (uint8)'f') )
  {
    retVal = (Digit - (uint8)'a') + (uint8)10u; /* a..f */
  }
  else if( (Digit >= (uint8)'A') && (Digit <= (uint8)'F') )
  {
    retVal = (Digit - (uint8)'A') + (uint8)10u; /* A..F */
  }
  else
  { /* #20 Handle invalid digit */
    retVal = IPBASE_UCHAR_MAX;
  }

  return retVal;
} /* IpBase_ConvHexString2ArrayBaseHlp() */
/***********************************************************************************************************************
 *  IpBase_ConvString2SignedIntBaseHlp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(sint32) IpBase_ConvString2SignedIntBaseHlp(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                                                        uint8 StrMaxLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  sint32 retVal   = 0;

  /* ----- Implementation ----------------------------------------------- */
  uint8        digit;
  boolean      isSigned = FALSE;
  uint8_least  posA;

  /* #10 Scan all characters */
  for ( posA = 0; posA < StrMaxLen; posA++ )
  {
    /* #20 Convert digit */
    digit = (StrPtr)[posA];
    if ( (digit == (uint8)'-') && (posA == (uint8_least)0u) )
    { /* #30 Negative value found */
      isSigned = TRUE;
    }
    else
    {
      if ( (digit < (uint8)'0') || (digit > (uint8)'9') )
      { /* #40 End of number found */
        break;
      }
      retVal *= 10;
      retVal += (sint32)digit - (sint32)'0';
    }
  }
  /* #50 Evaluate result */
  if ( posA == (uint8_least)0u )
  {
    retVal = IPBASE_SLONG_MAX;
  }
  else if ( isSigned != (boolean)FALSE )
  {
    retVal = -retVal;
  }
  else
  { /* keep retVal as is */
  }

  return retVal;
} /* IpBase_ConvString2SignedIntBaseHlp() */
# define IPBASE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  END OF FILE: IpBase_String.c
 *********************************************************************************************************************/
