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
 *         File:  IpBase_Ber.c
 *      Project:  MICROSAR ETH
 *    Component:  SysService_IpBase
 *       Module:  MICROSAR IP Base
 *    Generator:  None
 *
 *  Description:  Basic Encoding Rules implementation
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
#define IPBASE_BER_SOURCE

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
# error "Vendor specific version numbers of IpBase_Ber.c and IpBase.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/* IPBASE encoding constants */
# define IPBASE_BER_INFINITE_LEN                     ((uint8) 0u)   /*!< BER: infinite length encoding */
# define IPBASE_BER_MAX_LEN_U32                      ((uint8) 4u)   /*!< BER: max uint32 length encoding */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
/* IPBASE encoding extension check */
# define IPBASE_BER_IS_EXTENDED_LEN(len)  (0x80u & (len))                                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define IPBASE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  IpBase_BerCheckDepth
 *********************************************************************************************************************/
/*! \brief        BER depth check
 *  \details      Checks the depth of BER endoced data
 *  \param[in]    MaxDepth        maximum depth
 *  \param[in]    ElementDepth    element depth
 *  \return       IPBASE_E_OK     depth o.k.
 *  \return       IPBASE_E_NOT_OK element depth invalid, i.e. 0
 *  \return       IPBASE_E_MEM    depth exceeded
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \trace        CREQ-120247
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(IpBase_ReturnType) IpBase_BerCheckDepth(uint8 MaxDepth, uint8 ElementDepth);
/**********************************************************************************************************************
 *  IpBase_BerResetWorkspace
 *********************************************************************************************************************/
/*! \brief        BER reset workspace
 *  \details      Resets the workspace to default and inital values. DataPtr and DataSize are used as initial values.
 *  \param[in,out] WorkspacePtr   in: pointer to workspace, out: initialized workspace
 *  \param[in]     DataPtr        pointer to data
 *  \param[in]     DataSize       size of data [bytes]
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE for different Workspaces
 *  \trace        CREQ-120247
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(void) IpBase_BerResetWorkspace(
                                   IPBASE_CONSTP2VARAPPLDATA(IpBase_BerWorkspaceType) WorkspacePtr,
                                   IPBASE_P2CONSTAPPLDATA(uint8) DataPtr, uint32 DataSize);
/**********************************************************************************************************************
 *  IpBase_BerReadChapter
 *********************************************************************************************************************/
/*! \brief        BER read chapter
 *  \details      Reads one chapter, tries to find element within chapter
 *  \param[in,out] StackElementPtr in: pointer to stack element, out: pointer to found element
 *  \param[in]     ElementNr       searched element number of current chapter
 *  \param[in]     DataPtr         pointer to data
 *  \return       IPBASE_E_OK     chapter read
 *  \return       IPBASE_E_NOT_OK chapter end
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \trace        CREQ-120247
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(IpBase_ReturnType) IpBase_BerReadChapter(
                                   IPBASE_P2VARAPPLDATA(IpBase_BerStackElementType) StackElementPtr,
                                   IPBASE_P2CONSTAPPLDATA(uint8) DataPtr, uint8 ElementNr);
/**********************************************************************************************************************
 *  IpBase_BerSwitchChapter
 *********************************************************************************************************************/
/*! \brief         BER switch chapter
 *  \details       Switches to next chapter
 *  \param[in]     WorkspacePtr           pointer to workspace
 *  \param[in,out] StackElementPtrPtr     in: pointer to stack element pointer, out: element pointer of next chapter
 *  \param[in,out] DepthPtr               in: pointer to nesting depth, out: nesting depth of next chapter
 *  \return        IPBASE_E_OK            chapter switched
 *  \return        IPBASE_E_NOT_OK        document end
 *  \pre           Before calling the function the maximum depth has to be checked
 *  \context       TASK
 *  \reentrant     TRUE
 *  \trace         CREQ-120247
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(IpBase_ReturnType) IpBase_BerSwitchChapter(
                                   IPBASE_CONSTP2VARAPPLDATA(IpBase_BerWorkspaceType) WorkspacePtr,
                                   IPBASE_PP2VARAPPLDATA(IpBase_BerStackElementType) StackElementPtrPtr,
                                   IPBASE_P2VARAPPLDATA(uint8) DepthPtr);
/**********************************************************************************************************************
 *  IpBase_BerGetNextElement
 *********************************************************************************************************************/
/*! \brief         BER get next element
 *  \details       Gets the next element within chapter structure of the document
 *  \param[out]    Element       retrieved element
 *  \param[in]     ElementIdx    element index
 *  \param[in]     Block         block
 *  \param[in]     Data          data
 *  \return        IPBASE_E_OK     element retrieved
 *  \return        IPBASE_E_NOT_OK document end
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \trace         CREQ-120247
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(IpBase_ReturnType) IpBase_BerGetNextElement(
                                   IPBASE_CONSTP2VARAPPLDATA(IpBase_BerElementType) Element,
                                   uint32 ElementIdx,
                                   IPBASE_CONSTP2CONSTAPPLDATA(IpBase_BerBlockType) Block,
                                   IPBASE_CONSTP2CONSTAPPLDATA(uint8) Data);
/**********************************************************************************************************************
 *  IpBase_BerGetContentSize
 *********************************************************************************************************************/
/*! \brief         BER get content size
 *  \details       Gets the size of the current content
 *  \param[in]     SizeOfLen     content size length
 *  \param[in,out] ElementIdxPtr in: pointer with element index, out: pointer to start of data
 *  \param[in]     Data          data
 *  \return        length        content length [bytes]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \trace         CREQ-120247
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(uint32) IpBase_BerGetContentSize(uint8 SizeOfLen,
                                   IPBASE_CONSTP2VARAPPLDATA(uint32) ElementIdxPtr,
                                   IPBASE_CONSTP2CONSTAPPLDATA(uint8) Data);
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  IpBase_BerInitWorkspace
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_FUNCCODE(void) IpBase_BerInitWorkspace(IPBASE_CONSTP2VARAPPLDATA(IpBase_BerWorkspaceType) WorkspacePtr,
                                              IPBASE_CONSTP2VARAPPLDATA(IpBase_BerStackElementType) StackPtr,
                                              const uint8 Depth)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check WorkspacePtr, StackPtr for NULL pointer */
  if ( (WorkspacePtr == NULL_PTR) || (StackPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Initialize all data elements of workspace with defaults */
    WorkspacePtr->LastData     = NULL_PTR; /* SBSW_IPBASE_VALID_API_POINTER */
    WorkspacePtr->LastDataSize = 0u;       /* SBSW_IPBASE_VALID_API_POINTER */
    WorkspacePtr->Stack        = StackPtr; /* SBSW_IPBASE_VALID_API_POINTER */
    WorkspacePtr->CurrentDepth = 0u;       /* SBSW_IPBASE_VALID_API_POINTER */
    WorkspacePtr->MaxDepth     = Depth;    /* SBSW_IPBASE_VALID_API_POINTER */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #30 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_BER_INIT_WORKSPACE, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif
} /* IpBase_BerInitWorkspace() */
/**********************************************************************************************************************
 *  IpBase_BerGetElement
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
 *********************************************************************************************************************/
IPBASE_FUNCCODE(IpBase_ReturnType) IpBase_BerGetElement(IPBASE_CONSTP2VARAPPLDATA(IpBase_BerWorkspaceType) WorkspacePtr,
                                                        IPBASE_P2VARAPPLDATA(IpBase_BerElementType) ElementPtr,
                                                        IPBASE_P2CONSTAPPLDATA(uint8) ElementNrPtr,
                                                        const uint8 ElementDepth,
                                                        IPBASE_P2CONSTAPPLDATA(uint8) DataPtr,
                                                        const uint32 DataSize)
{
  /* ----- Local Variables ---------------------------------------------- */
  IpBase_ReturnType retVal = IPBASE_E_NOT_OK;
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check WorkspacePtr, ElementPtr, ElementNrPtr, ElementNrPtr for NULL pointer */
  if ( (WorkspacePtr == NULL_PTR) || (ElementPtr == NULL_PTR) || (ElementNrPtr == NULL_PTR) ||
       (DataPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Check workspace depth */
    retVal = IpBase_BerCheckDepth(WorkspacePtr->MaxDepth, ElementDepth);
    if ( retVal == IPBASE_E_OK )
    {
      IPBASE_P2VARAPPLDATA(IpBase_BerStackElementType) stackElementPtr;
      boolean         found = FALSE;
      uint8           depth;

      /* #30 Reset data elements of workspace */
      IpBase_BerResetWorkspace(WorkspacePtr, DataPtr, DataSize); /* SBSW_IPBASE_PASSING_API_POINTER */
      depth = (uint8) (WorkspacePtr->CurrentDepth - 1u);
      stackElementPtr = &WorkspacePtr->Stack[depth];
      while ( (retVal == IPBASE_E_OK) && (found == (boolean)FALSE) )
      { /* #40 Search for element in entire document */
        if ( ElementNrPtr[depth] == 0u )
        { /* #50 Invalid ElementNr found */
          retVal = IPBASE_E_NOT_OK;
        }
        else
        { /* #60 Search within chapter */
          retVal = IpBase_BerReadChapter(stackElementPtr, DataPtr, ElementNrPtr[depth]); /* SBSW_IPBASE_PASSING_API_POINTER */
        }
        if ( retVal != IPBASE_E_OK )
        {
          break;
        }
        if ( ElementDepth > WorkspacePtr->CurrentDepth )
        { /* #70 Proceed to next chapter */
          retVal = IpBase_BerSwitchChapter(WorkspacePtr, &stackElementPtr, &depth); /* SBSW_IPBASE_PASSING_API_POINTER */
        }
        else
        { /* #80 Searched element found */
          found = TRUE;
          *ElementPtr = stackElementPtr->CurrentElement; /* SBSW_IPBASE_VALID_API_POINTER */
        }
      }
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #90 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_BER_GET_ELEMENT, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_BerGetElement() */                                                                                          /* PRQA S 6060 */ /* MD_MSR_STPAR */
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  IpBase_BerCheckDepth
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(IpBase_ReturnType) IpBase_BerCheckDepth(uint8 MaxDepth, uint8 ElementDepth)
{
  /* ----- Local Variables ---------------------------------------------- */
  IpBase_ReturnType retVal = IPBASE_E_OK;

  /* ----- Implementation ----------------------------------------------- */
  if ( MaxDepth == 0u )
  { /* #10 Check max depth */
    retVal = IPBASE_E_MEM;
  }
  else if ( ElementDepth == 0u )
  { /* #20 Check element depth */
    retVal = IPBASE_E_NOT_OK;
  }
  else if ( MaxDepth < ElementDepth )
  { /* #30 Check max depth against element depth */
    retVal = IPBASE_E_MEM;
  }
  else
  { /* #40 Successful depth check */
  }

  return retVal;
} /* IpBase_BerCheckDepth() */
/**********************************************************************************************************************
 *  IpBase_BerResetWorkspace
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(void) IpBase_BerResetWorkspace(
                                     IPBASE_CONSTP2VARAPPLDATA(IpBase_BerWorkspaceType) WorkspacePtr,
                                     IPBASE_P2CONSTAPPLDATA(uint8) DataPtr, uint32 DataSize)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset all data elements of workspace */
  WorkspacePtr->LastData = DataPtr;                       /* SBSW_IPBASE_VALID_API_POINTER */
  WorkspacePtr->LastDataSize = DataSize;                  /* SBSW_IPBASE_VALID_API_POINTER */
  WorkspacePtr->CurrentDepth = 1u;                        /* SBSW_IPBASE_VALID_API_POINTER */
  WorkspacePtr->Stack[0u].CurrentBlock.Idx = 0u;          /* SBSW_IPBASE_VALID_API_POINTER */
  WorkspacePtr->Stack[0u].CurrentBlock.EndIdx = DataSize; /* SBSW_IPBASE_VALID_API_POINTER */
  WorkspacePtr->Stack[0u].CurrentIdx = 0u;                /* SBSW_IPBASE_VALID_API_POINTER */
  WorkspacePtr->Stack[0u].CurrentElementNr = 0u;          /* SBSW_IPBASE_VALID_API_POINTER */

} /* IpBase_BerResetWorkspace() */
/**********************************************************************************************************************
 *  IpBase_BerReadChapter
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(IpBase_ReturnType) IpBase_BerReadChapter(
                                            IPBASE_P2VARAPPLDATA(IpBase_BerStackElementType) StackElementPtr,
                                            IPBASE_P2CONSTAPPLDATA(uint8) DataPtr, uint8 ElementNr)
{
  /* ----- Local Variables ---------------------------------------------- */
  IpBase_ReturnType retVal = IPBASE_E_OK;

  /* ----- Implementation ----------------------------------------------- */
  while ( (retVal == IPBASE_E_OK) && (ElementNr > StackElementPtr->CurrentElementNr) )
  {
    if ( StackElementPtr->CurrentBlock.EndIdx <= StackElementPtr->CurrentIdx )
    { /* #10 Check if end of block is reached */
      retVal = IPBASE_E_NOT_OK;
    }
    else
    { /* #20 Read next element */
      retVal = IpBase_BerGetNextElement(&StackElementPtr->CurrentElement,
                                        StackElementPtr->CurrentIdx,
                                        &StackElementPtr->CurrentBlock, DataPtr); /* SBSW_IPBASE_BER_REFERENCE_OF_POINTER_ELEMENT */
      if ( retVal == IPBASE_E_OK )
      { /* #30 Increase element counters */
        StackElementPtr->CurrentElementNr++; /* SBSW_IPBASE_REFERENCE_OF_POINTER_ELEMENT */
        StackElementPtr->CurrentIdx = StackElementPtr->CurrentElement.EndIdx; /* SBSW_IPBASE_REFERENCE_OF_POINTER_ELEMENT */
      }
    }
  }

  return retVal;
} /* IpBase_BerReadChapter() */
/**********************************************************************************************************************
 *  IpBase_BerSwitchChapter
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(IpBase_ReturnType) IpBase_BerSwitchChapter(
                                            IPBASE_CONSTP2VARAPPLDATA(IpBase_BerWorkspaceType) WorkspacePtr,
                                            IPBASE_PP2VARAPPLDATA(IpBase_BerStackElementType) StackElementPtrPtr,
                                            IPBASE_P2VARAPPLDATA(uint8) DepthPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  IpBase_ReturnType retVal = IPBASE_E_OK;

  /* ----- Implementation ----------------------------------------------- */
  if ( IpBase_BerIsPrimitive((*StackElementPtrPtr)->CurrentElement.Type) )
  { /* #10 Check primitive element, cannot increase depth */
    retVal = IPBASE_E_NOT_OK;
  }
  else
  {
    IPBASE_P2VARAPPLDATA(IpBase_BerStackElementType) nextStackElementPtr;
    /* #20 Increase depth (switch chapter) */
    *DepthPtr = WorkspacePtr->CurrentDepth; /* alternative: Depth++; */ /* SBSW_IPBASE_VALID_API_POINTER */
    nextStackElementPtr = &WorkspacePtr->Stack[*DepthPtr];
    nextStackElementPtr->CurrentBlock.Idx    = (*StackElementPtrPtr)->CurrentElement.ContentIdx; /* SBSW_IPBASE_VALID_API_POINTER */
    nextStackElementPtr->CurrentBlock.EndIdx = (*StackElementPtrPtr)->CurrentElement.EndIdx; /* SBSW_IPBASE_VALID_API_POINTER */
    nextStackElementPtr->CurrentIdx = nextStackElementPtr->CurrentBlock.Idx; /* SBSW_IPBASE_VALID_API_POINTER */
    nextStackElementPtr->CurrentElementNr = 0u; /* SBSW_IPBASE_VALID_API_POINTER */
    *StackElementPtrPtr = nextStackElementPtr; /* SBSW_IPBASE_VALID_API_POINTER */
    WorkspacePtr->CurrentDepth++; /* SBSW_IPBASE_VALID_API_POINTER */
  }

  return retVal;
} /* IpBase_BerSwitchChapter() */

/**********************************************************************************************************************
 *  IpBase_BerGetNextElement
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(IpBase_ReturnType) IpBase_BerGetNextElement(
                                            IPBASE_CONSTP2VARAPPLDATA(IpBase_BerElementType) Element,
                                            uint32 ElementIdx,
                                            IPBASE_CONSTP2CONSTAPPLDATA(IpBase_BerBlockType) Block,
                                            IPBASE_CONSTP2CONSTAPPLDATA(uint8) Data)
{
  /* ----- Local Variables ---------------------------------------------- */
  IpBase_ReturnType retVal = IPBASE_E_BER_PARAM;
  uint32 contentSize;
  uint32 elmtIdxLoc = ElementIdx;
  uint8  sizeOfLen;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check element inside block no boundary crossing */
  if ( Block->EndIdx >= (elmtIdxLoc + 2u) )
  { /* #20 Read next element */
    Element->Idx = elmtIdxLoc; /* SBSW_IPBASE_VALID_API_POINTER */
    Element->Type = Data[elmtIdxLoc]; /* SBSW_IPBASE_VALID_API_POINTER */
    elmtIdxLoc++;
    sizeOfLen = Data[elmtIdxLoc];
    elmtIdxLoc++;

    /* #30 Evaluate length size */
    if ( IPBASE_BER_IS_EXTENDED_LEN(sizeOfLen) == 0u )
    {
      Element->EndIdx     = elmtIdxLoc + sizeOfLen; /* SBSW_IPBASE_VALID_API_POINTER */
      Element->ContentIdx = elmtIdxLoc; /* SBSW_IPBASE_VALID_API_POINTER */
      retVal = IPBASE_E_OK;
    }
    else
    {
      sizeOfLen = IpBase_BerSizeOfLength(sizeOfLen);

      if ( (Block->EndIdx >= (elmtIdxLoc + sizeOfLen)) &&
           (sizeOfLen <= IPBASE_BER_MAX_LEN_U32) && (sizeOfLen != IPBASE_BER_INFINITE_LEN) )
      { /* #40 Evaluate content size */
        contentSize = IpBase_BerGetContentSize(sizeOfLen, &elmtIdxLoc, Data); /* SBSW_IPBASE_PASSING_API_POINTER */
        Element->EndIdx = elmtIdxLoc + contentSize; /* SBSW_IPBASE_VALID_API_POINTER */
        if ( Block->EndIdx >= Element->EndIdx )
        { /* #50 Get element content */
          Element->ContentIdx = elmtIdxLoc; /* SBSW_IPBASE_VALID_API_POINTER */
          retVal = IPBASE_E_OK;
        }
      }
    }
  }

  return retVal;
} /* IpBase_BerGetNextElement */
/**********************************************************************************************************************
 *  IpBase_BerGetContentSize
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(uint32) IpBase_BerGetContentSize(uint8 SizeOfLen,
                                                              IPBASE_CONSTP2VARAPPLDATA(uint32) ElementIdxPtr,
                                                              IPBASE_CONSTP2CONSTAPPLDATA(uint8) Data)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 contentSize;

  /* ----- Implementation ----------------------------------------------- */
  if ( SizeOfLen == 1u )
  { /* #10 Handle 1 byte length encoding */
    contentSize = Data[*ElementIdxPtr];
    (*ElementIdxPtr)++; /* SBSW_IPBASE_VALID_API_POINTER */
  }
  else if ( SizeOfLen == 2u )
  { /* #20 Handle 2 bytes length encoding */
    contentSize = Data[*ElementIdxPtr];
    (*ElementIdxPtr)++; /* SBSW_IPBASE_VALID_API_POINTER */
    contentSize <<= 8u;
    contentSize |= Data[*ElementIdxPtr];
    (*ElementIdxPtr)++; /* SBSW_IPBASE_VALID_API_POINTER */
  }
  else if ( SizeOfLen == 3u )
  { /* #30 Handle 3 bytes length encoding */
    contentSize = Data[*ElementIdxPtr];
    (*ElementIdxPtr)++; /* SBSW_IPBASE_VALID_API_POINTER */
    contentSize <<= 8u;
    contentSize |= Data[*ElementIdxPtr];
    (*ElementIdxPtr)++; /* SBSW_IPBASE_VALID_API_POINTER */
    contentSize <<= 8u;
    contentSize |= Data[*ElementIdxPtr];
    (*ElementIdxPtr)++; /* SBSW_IPBASE_VALID_API_POINTER */
  }
  else
  { /* #40 Handle 4 bytes length encoding */
    contentSize = Data[*ElementIdxPtr];
    (*ElementIdxPtr)++; /* SBSW_IPBASE_VALID_API_POINTER */
    contentSize <<= 8u;
    contentSize |= Data[*ElementIdxPtr];
    (*ElementIdxPtr)++; /* SBSW_IPBASE_VALID_API_POINTER */
    contentSize <<= 8u;
    contentSize |= Data[*ElementIdxPtr];
    (*ElementIdxPtr)++; /* SBSW_IPBASE_VALID_API_POINTER */
    contentSize <<= 8u;
    contentSize |= Data[*ElementIdxPtr];
    (*ElementIdxPtr)++; /* SBSW_IPBASE_VALID_API_POINTER */
  }

  return contentSize;
} /* IpBase_BerGetContentSize */
# define IPBASE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  END OF FILE: IpBase_Ber.c
 *********************************************************************************************************************/
