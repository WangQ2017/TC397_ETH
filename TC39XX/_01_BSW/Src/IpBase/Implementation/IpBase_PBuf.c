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
 *         File:  IpBase_PBuf.c
 *      Project:  MICROSAR ETH
 *    Component:  SysService_IpBase
 *       Module:  MICROSAR IP Base
 *    Generator:  None
 *
 *  Description:  PBuf API implementation
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
#define IPBASE_PBUF_SOURCE

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
# error "Vendor specific version numbers of IpBase_PBuf.c and IpBase.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define IPBASE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/***********************************************************************************************************************
 *  IpBase_FindStringInPbufHlp
 **********************************************************************************************************************/
/*! \brief         Find string in PBuf helper
 *  \details       Find a string in a PBuf actual search
 *  \param[in]     StrPtr                pointer to search string
 *  \param[in]     PbufPtr               pointer to PBuf struct
 *  \param[in,out] StrPosPtr             in: start index for search in PBuf, out: start index of string
 *  \param[in]     StrLen                length of the search string [byte]
 *  \return        E_OK                  string was found
 *  \return        E_NOT_OK              string was not found or API parameters are invalid
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \trace         CREQ-120249
 **********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(Std_ReturnType) IpBase_FindStringInPbufHlp(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                                                        IPBASE_P2CONSTAPPLDATA(IpBase_PbufType) PbufPtr,
                                                                        IPBASE_P2VARAPPLDATA(uint32) StrPosPtr,
                                                                        uint16 StrLen);
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  IpBase_StrCmpPBuf
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
 *
 *********************************************************************************************************************/
IPBASE_FUNCCODE(uint8) IpBase_StrCmpPBuf(IPBASE_PP2CONSTAPPLDATA(IpBase_PbufType) SrcPbufPtr,
                                         IPBASE_P2CONSTAPPLDATA(sint8) PatternPtr,
                                         IPBASE_P2VARAPPLDATA(uint16) CurByteIdxPtr,
                                         IPBASE_P2VARAPPLDATA(uint32) TotByteIdxPtr,
                                         IPBASE_P2VARAPPLDATA(uint32) RestLenBytePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 retVal  = IPBASE_CMP_NOT_EQUAL;
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (SrcPbufPtr == NULL_PTR) || (*SrcPbufPtr == NULL_PTR) || (PatternPtr == NULL_PTR) ||
       (CurByteIdxPtr == NULL_PTR) || (TotByteIdxPtr == NULL_PTR) || (RestLenBytePtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Scan for string through source buffer */
    uint16 curByteIdx = *CurByteIdxPtr;
    uint32 totByteIdx = *TotByteIdxPtr;
    uint32 patternByteIdx = 0u;
    uint32 srcBufTotLen = (*SrcPbufPtr)->totLen;
    IPBASE_P2CONSTAPPLDATA(IpBase_PbufType) curPbufPtr = *SrcPbufPtr;

    while ( (totByteIdx < srcBufTotLen) && (retVal != IPBASE_CMP_EQUAL) )
    {
      if ( (curPbufPtr->payload[curByteIdx] != (uint8) PatternPtr[patternByteIdx]) )
      { /* #30 Handle invalid pattern */
        *RestLenBytePtr = 0u; /* SBSW_IPBASE_VALID_API_POINTER */
        break;
      }
      curByteIdx++;
      totByteIdx++;
      patternByteIdx++;
      (*RestLenBytePtr)++; /* SBSW_IPBASE_VALID_API_POINTER */
      if ( PatternPtr[patternByteIdx] == IPBASE_END_OF_STRING )
      { /* #40 End of pattern string -> complete pattern found */
        *CurByteIdxPtr = curByteIdx; /* SBSW_IPBASE_VALID_API_POINTER */
        *TotByteIdxPtr = totByteIdx; /* SBSW_IPBASE_VALID_API_POINTER */
        *SrcPbufPtr    = curPbufPtr; /* SBSW_IPBASE_VALID_API_POINTER */
        retVal = IPBASE_CMP_EQUAL;
      }
      else if ( (totByteIdx < srcBufTotLen) && (curByteIdx >= curPbufPtr->len) )
      { /* #50 Switch to next buffer segment */
        curByteIdx = 0;
        curPbufPtr = &(curPbufPtr[1u]);
      }
      else
      { /* #60 Continue with next character */
      }
    }
    if ( retVal != IPBASE_CMP_EQUAL )
    {  /* #70 End of string -> no character or incomplete pattern found */
      *CurByteIdxPtr = curByteIdx; /* SBSW_IPBASE_VALID_API_POINTER */
      *TotByteIdxPtr = totByteIdx; /* SBSW_IPBASE_VALID_API_POINTER */
      *SrcPbufPtr    = curPbufPtr; /* SBSW_IPBASE_VALID_API_POINTER */
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #80 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_STR_CMP_PBUF, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_StrCmpPBuf() */
/**********************************************************************************************************************
 *  IpBase_IncPBuf
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_FUNCCODE(void) IpBase_IncPBuf(IPBASE_PP2VARAPPLDATA(IpBase_PbufType) PbufPtr,
                                     IPBASE_P2VARAPPLDATA(uint16) CurByteIdxPtr,
                                     IPBASE_P2VARAPPLDATA(uint32) TotByteIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (PbufPtr == NULL_PTR) || (*PbufPtr == NULL_PTR) || (CurByteIdxPtr == NULL_PTR) ||
       (TotByteIdxPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {

    /* ----- Implementation ----------------------------------------------- */
    /* #20 Check buffer length, do not increment idxs if end is reached */
    if ( (*TotByteIdxPtr) < (*PbufPtr)->totLen )
    {
      (*CurByteIdxPtr)++; /* SBSW_IPBASE_VALID_API_POINTER */
      (*TotByteIdxPtr)++; /* SBSW_IPBASE_VALID_API_POINTER */
      /* #30 Switch to next buffer segment (increment PBuf) */
      if ( ((*PbufPtr)->totLen > (*TotByteIdxPtr)) && ((*PbufPtr)->len <= (*CurByteIdxPtr)) )
      {
        (*CurByteIdxPtr) = 0u;       /* SBSW_IPBASE_VALID_API_POINTER */
        (*PbufPtr) = &((*PbufPtr)[1u]); /* SBSW_IPBASE_VALID_API_POINTER */
      }
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #40 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_INC_PBUF, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

} /* IpBase_IncPBuf() */
/***********************************************************************************************************************
 *  IpBase_CopyString2PbufAt
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_CopyString2PbufAt(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                                         uint16 StrLen,
                                                         IPBASE_P2CONSTAPPLDATA(IpBase_PbufType) PbufPtr,
                                                         uint32 StartPos)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (StrPtr == NULL_PTR) || (PbufPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  /* #20 Check for invalid param */
  else if (StartPos > (uint16)PbufPtr->totLen )
  {
    errorId = IPBASE_E_INV_PARAM;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint32 writePosAbs = 0u;   /* overall write position in PBuf -> 'Abs'olute position */
    uint32 writePosLoc;        /* write position in PBuf element -> 'Loc'al position */
    uint32 copiedLen = 0u;
    uint32 copyLen;
    uint32 copyBlockLen;
    IpBase_PbufType const *pBufElePtr = PbufPtr;

    /* #30 Go to start position in Pbuf */
    while ( StartPos >= (pBufElePtr->len + writePosAbs))
    { /* #40 StartPos not within current PBuf segment goto next segment */
      writePosAbs += pBufElePtr->len;
      pBufElePtr = &pBufElePtr[1u];
    }
    writePosLoc = StartPos - writePosAbs;

    /* #50 Limit length to minimum of string length and PBuf */
    copyLen = StrLen;
    if ( copyLen > (PbufPtr->totLen - StartPos) )
    {
      copyLen = PbufPtr->totLen - StartPos;
    }

    while ( copyLen > copiedLen )
    { /* #60 Copy data into PBuf element */
      copyBlockLen = pBufElePtr->len - writePosLoc;
      if ( copyBlockLen > (copyLen - copiedLen) )
      {
        copyBlockLen = copyLen - copiedLen;
      }
      /* PRQA S 314 2 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy((IPBASE_P2VARAPPLDATA(void))&pBufElePtr->payload[writePosLoc],       /* SBSW_IPBASE_PASSING_API_POINTER */
                 (IPBASE_P2CONSTAPPLDATA(void))(&StrPtr[copiedLen]), copyBlockLen);
      copiedLen += copyBlockLen;
      /* #70 Go to next PBuf element */
      writePosLoc = 0u;
      pBufElePtr = &pBufElePtr[1];
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #80 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_COPY_STR_TO_PBUF_AT, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return E_OK;
} /* IpBase_CopyString2PbufAt() */
/***********************************************************************************************************************
 *  IpBase_CopyPbuf2String
 **********************************************************************************************************************/
/*! Internal comment removed.
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
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_CopyPbuf2String(IPBASE_P2VARAPPLDATA(uint8) StrPtr,
                                                       IPBASE_P2CONSTAPPLDATA(IpBase_PbufType) PbufPtr,
                                                       uint16 StrLen, uint32 StartPos)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (StrPtr == NULL_PTR) || (PbufPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  /* #20 Check for invalid param */
  else if ( (StartPos + StrLen) > (uint16)PbufPtr->totLen )
  {
    errorId = IPBASE_E_INV_PARAM;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint16 strPos = 1u;
    uint32 readPosAbs = 0u;  /* overall read position in PBuf -> 'Abs'olute position */
    uint32 readPosLoc;       /* read position in PBuf element -> 'Loc'al position */
    const IpBase_PbufType *pBufElePtr = PbufPtr;

    /* #30 Go to start position in Pbuf */
    while ( StartPos >= (pBufElePtr->len + readPosAbs) )
    { /* #40 StartPos not within current PBuf segment goto next segment */
      readPosAbs += pBufElePtr->len;
      pBufElePtr = &pBufElePtr[1u];
    }
    readPosLoc = StartPos - readPosAbs;

    /* #50 Copy first byte */
    if ( StrLen > 0u )
    {
      StrPtr[0u] = pBufElePtr->payload[readPosLoc]; /* SBSW_IPBASE_VALID_API_POINTER */
      readPosLoc++;
    }

    /* #60 Copy remaining bytes */
    while ( strPos < StrLen )
    {
      if ( readPosLoc == pBufElePtr->len )
      { /* #70 Go to next PBuf segment */
        readPosLoc = 0u;
        pBufElePtr = &pBufElePtr[1u];
      }

      /* #80 Copy byte and inc position */
      StrPtr[strPos] = pBufElePtr->payload[readPosLoc]; /* SBSW_IPBASE_VALID_API_POINTER */
      strPos++;
      readPosLoc++;
    }
    retVal = E_OK;
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #90 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_COPY_PBUF_TO_STR, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_CopyPbuf2String() */
/***********************************************************************************************************************
 *  IpBase_FindStringInPbuf
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_FindStringInPbuf(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                                        IPBASE_P2CONSTAPPLDATA(IpBase_PbufType) PbufPtr,
                                                        uint16 StrLen, uint32 StartPos,
                                                        IPBASE_P2VARAPPLDATA(uint32) StrPosPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (StrPtr == NULL_PTR) || (PbufPtr == NULL_PTR)  || (StrPosPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else if ( (StrLen > PbufPtr->totLen) || (StartPos > (PbufPtr->totLen - StrLen)) )
  { /* #20 Check for invalid param */
    errorId = IPBASE_E_INV_PARAM;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Search for string in buffer (PBuf) */
    *StrPosPtr = StartPos; /* SBSW_IPBASE_VALID_API_POINTER */
    retVal = IpBase_FindStringInPbufHlp(StrPtr, PbufPtr, StrPosPtr, StrLen); /* SBSW_IPBASE_PASSING_API_POINTER */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #40 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_FIND_STR_IN_PBUF, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_FindStringInPbuf() */
/***********************************************************************************************************************
 *  IpBase_CheckStringInPbuf
 **********************************************************************************************************************/
/*! Internal comment removed.
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
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_CheckStringInPbuf(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                                         IPBASE_P2CONSTAPPLDATA(IpBase_PbufType) PbufPtr,
                                                         uint16 StrLen, uint32 StartPos)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal  = E_NOT_OK;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (StrPtr == NULL_PTR) || (PbufPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else if ( (StrLen > PbufPtr->totLen) || (StartPos > (PbufPtr->totLen - StrLen)) )
  { /* #20 Check for invalid param */
    errorId = IPBASE_E_INV_PARAM;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint16 locStrPos = 0u;
    uint32 readPosAbs = 0u;   /* overall read position in PBuf -> 'Abs'olute position */
    uint32 readPosLoc;        /* read position in PBuf element -> 'Loc'al position */
    IPBASE_P2CONSTAPPLDATA(IpBase_PbufType) pBufElePtr = (IPBASE_P2CONSTAPPLDATA(IpBase_PbufType)) PbufPtr;

    /* #30 Go to start position */
    while ( (pBufElePtr->len + readPosAbs) <= StartPos )
    { /* #40 StartPos not within current PBuf segment goto next segment */
      readPosAbs += pBufElePtr->len;
      pBufElePtr = &pBufElePtr[1u];
    }
    readPosLoc = StartPos - readPosAbs;

    while ( locStrPos < StrLen )
    { /* #50 Search string within buffer (PBuf) */
      if ( readPosLoc == pBufElePtr->len )
      { /* #60 End of segment, switch to next PBuf segment */
        readPosLoc = 0;
        pBufElePtr = &pBufElePtr[1u];
      }
      if ( pBufElePtr->payload[readPosLoc] != StrPtr[locStrPos] )
      { /* #70 Mismatch -> stop search */
        break;
      }

      /* #80 Character matches in search string -> go to next character */
      readPosLoc++;
      locStrPos++;

    }
    if ( locStrPos == StrLen )
    { /* #90 String found */
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #100 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CHK_STR_IN_PBUF, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_CheckStringInPbuf() */
/***********************************************************************************************************************
 *  IpBase_ReadByteInPbuf
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
IPBASE_FUNCCODE(Std_ReturnType) IpBase_ReadByteInPbuf(IPBASE_P2CONSTAPPLDATA(IpBase_PbufType) PbufPtr,
                                                      uint32 BytePos,
                                                      IPBASE_P2VARAPPLDATA(uint8) SingleBytePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for NULL pointer */
  if ( (PbufPtr == NULL_PTR) || (SingleBytePtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else if ( BytePos > PbufPtr->totLen )
  { /* #20 Check for invalid param */
    errorId = IPBASE_E_INV_PARAM;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint32 readPosAbs = 0u; /* overall read position in PBuf -> 'Abs'olute position */
    uint32 readPosLoc;      /* read position in PBuf element -> 'Loc'al position */
    IPBASE_P2CONSTAPPLDATA(IpBase_PbufType) pBufElePtr = (IPBASE_P2CONSTAPPLDATA(IpBase_PbufType)) PbufPtr;

    /* #30 Go to start position */
    while ( BytePos >= (pBufElePtr->len + readPosAbs) )
    { /* #40 StartPos not within current PBuf segment goto next segment */
      readPosAbs += pBufElePtr->len;
      pBufElePtr = &pBufElePtr[1u];
    }
    /* #50 Read byte */
    readPosLoc = BytePos - readPosAbs;
    *SingleBytePtr = pBufElePtr->payload[readPosLoc]; /* SBSW_IPBASE_VALID_API_POINTER */
    retVal = E_OK;
  }
  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #60 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_READ_BYTE_IN_PBUF, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_ReadByteInPbuf() */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  IpBase_FindStringInPbufHlp
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
 *
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(Std_ReturnType) IpBase_FindStringInPbufHlp(IPBASE_P2CONSTAPPLDATA(uint8) StrPtr,
                                                                        IPBASE_P2CONSTAPPLDATA(IpBase_PbufType) PbufPtr,
                                                                        IPBASE_P2VARAPPLDATA(uint32) StrPosPtr,
                                                                        uint16 StrLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal  = E_NOT_OK;
  uint32 readPosAbs = 0u;   /* overall read position in PBuf -> 'Abs'olute position */
  uint32 readPosLoc;        /* read position in PBuf element -> 'Loc'al position */
  boolean found   = FALSE;
  const IpBase_PbufType *pBufElePtr = PbufPtr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Go to start position in Pbuf */
  while ( (pBufElePtr->len + readPosAbs) <= *StrPosPtr )
  { /* #20 StartPos not within current PBuf segment goto next segment */
    readPosAbs += pBufElePtr->len;
    pBufElePtr = &pBufElePtr[1u];
  }
  readPosLoc = (*StrPosPtr) - readPosAbs;
  readPosAbs = (*StrPosPtr);
  while ( (readPosAbs <= (PbufPtr->totLen - StrLen)) && (found == (boolean)FALSE) )
  { /* #30 Global search (start pattern not found) */
    if(pBufElePtr->payload[readPosLoc] == StrPtr[0u])
    { /* #40 First character found, check following characters */
      uint16 strPos = 1u;
      uint32 strReadPosLoc = readPosLoc + 1u;
      IPBASE_P2CONSTAPPLDATA(IpBase_PbufType) locPbufElePtr = pBufElePtr;

      while ( strPos < StrLen )
      { /* #50 Local search (start pattern found) */
        if ( strReadPosLoc == locPbufElePtr->len )
        { /* #60 StartPos not within current PBuf segment goto next segment */
          strReadPosLoc = 0u;
          locPbufElePtr = &locPbufElePtr[1u];
        }
        if ( locPbufElePtr->payload[strReadPosLoc] != StrPtr[strPos] )
        { /* #70 Mismatch in local search -> return to search */
          readPosLoc++;
          break;
        }
        strReadPosLoc++;
        strPos++;
      }
      if ( strPos == StrLen )
      { /* #80 Complete string found */
        *StrPosPtr = readPosAbs;  /* SBSW_IPBASE_VALID_API_POINTER */
        found = TRUE;
        retVal = E_OK;
      }
    }
    else
    { /* #90 No match -> increment */
      readPosAbs++;
      readPosLoc++;
      if ( readPosLoc == pBufElePtr->len )
      {
        if ( readPosAbs < pBufElePtr->totLen )
        { /* #100 Go to next PBuf segment */
          pBufElePtr = &pBufElePtr[1u];
          readPosLoc = 0u;
        }
        else
        { /* #110 End of PBuf reached */
          retVal = E_NOT_OK;
        }
      }
    }
  }

  return retVal;
} /* IpBase_FindStringInPbufHlp() */

# define IPBASE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  END OF FILE: IpBase_PBuf.c
 *********************************************************************************************************************/
