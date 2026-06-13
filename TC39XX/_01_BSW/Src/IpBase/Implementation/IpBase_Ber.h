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
 *         File:  IpBase_Ber.h
 *      Project:  MICROSAR ETH
 *    Component:  SysService_IpBase
 *       Module:  MICROSAR IP Base
 *    Generator:  None
 *
 *  Description:  Basic Encoding Rules header
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
#if !defined (IPBASE_BER_H)
# define IPBASE_BER_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "IpBase_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 14 */ /* MD_MSR_FctLikeMacro */
#  define IpBase_BerSizeOfBlock(block)          ((block).EndIdx - (block).Idx)    /*!< BER block size calculation */
#  define IpBase_BerSizeOfElement(elt)          ((elt).EndIdx - (elt).Idx)        /*!< BER element size calculation */
#  define IpBase_BerSizeOfElementContent(elt)   ((elt).EndIdx - (elt).ContentIdx) /*!< BER content size calculation */
#  define IpBase_BerIsUniversal(tag)            (0x00u == (0xC0u & (tag)))        /*!< BER universal tag id */
#  define IpBase_BerIsApplication(tag)          (0x40u == (0xC0u & (tag)))        /*!< BER application tag id */
#  define IpBase_BerIsContext(tag)              (0x80u == (0xC0u & (tag)))        /*!< BER context tag id */
#  define IpBase_BerIsPrivate(tag)              (0xC0u == (0xC0u & (tag)))        /*!< BER private tag id */
#  define IpBase_BerIsConstructed(tag)          (0x20u == (0x20u & (tag)))        /*!< BER constructed tag id */
#  define IpBase_BerIsPrimitive(tag)            (0x00u == (0x20u & (tag)))        /*!< BER primitive tag id */
#  define IpBase_BerGetClass(tag)               ((0xC0u & (tag)) >> 6u)           /*!< BER get class from tag id */
#  define IpBase_BerGetPc(tag)                  ((0x20u & (tag)) >> 5u)           /*!< BER get PC (primitive/construced)
                                                                                           flag from tag id */
#  define IpBase_BerGetNumber(tag)              (0x1Fu & (tag))                   /*!< BER get number from tag id */
#  define IpBase_BerSizeOfLength(tag)           (0x7Fu & (tag))                   /*!< BER get size of length */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! This type is used to limit Basic Encoding Rules data block */
typedef struct
{
  uint32 Idx;          /*!< block index */
  uint32 EndIdx;       /*!< block end index */
} IpBase_BerBlockType;
/*! This type is used to describe Basic Encoding Rules element type */
typedef struct
{
  uint32 ContentIdx;  /*!< element content index */
  uint32 EndIdx;      /*!< element end index */
  uint32 Idx;         /*!< element index */
  uint8 Type;         /*!< element content type */
} IpBase_BerElementType;
/*! This type is used to describe Basic Encoding Rules generic data type */
typedef struct
{
  IPBASE_P2CONSTAPPLDATA(uint8) DataPtr;  /*!< element data pointer */
  uint32 DataSize;                        /*!< element data size */
} IpBase_BerDataType;
/*! This type is used to describe Basic Encoding Rules stack element data type */
typedef struct
{
  uint32 CurrentIdx;                      /*!< current read index */
  IpBase_BerBlockType CurrentBlock;       /*!< current block */
  IpBase_BerElementType CurrentElement;   /*!< currrent element */
  uint8 CurrentElementNr;                 /*!< current element number */
} IpBase_BerStackElementType;
/*! This type is used to describe Basic Encoding Rules stack workspace data type */
typedef struct
{
  uint32 LastDataSize;                    /*!< last data size */
  IPBASE_P2CONSTAPPLDATA(uint8) LastData; /*!< last data */
  IpBase_BerStackElementType * Stack;     /*!< stack pointer */
  uint8 CurrentDepth;                     /*!< current chapter depth */
  uint8 MaxDepth;                         /*!< max depth of nesting chapters */
} IpBase_BerWorkspaceType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  IpBase_BerInitWorkspace
 *********************************************************************************************************************/
/*! \brief         Initializes the ASN.1/BER parser workspace
 *  \details       Sets all members of workspace to default values or given parameter
 *  \param[in,out] Workspace      workspace to initialize
 *  \param[in]     Stack          stack to use
 *  \param[in]     Depth          depth of the stack
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE for different workspaces
 *  \synchronous   TRUE
 *  \trace         CREQ-120247
 *********************************************************************************************************************/
IPBASE_FUNCCODE(void) IpBase_BerInitWorkspace(IPBASE_CONSTP2VARAPPLDATA(IpBase_BerWorkspaceType) WorkspacePtr,
                                              IPBASE_CONSTP2VARAPPLDATA(IpBase_BerStackElementType) StackPtr,
                                              const uint8 Depth);
/**********************************************************************************************************************
 *  IpBase_BerGetElement
 *********************************************************************************************************************/
/*! \brief         Get an ASN.1/BER element
 *  \details       Get an ASN.1/BER element with a given number out of ASN.1/BER encoded data.
 *  \param[in,out] WorkspacePtr   internally used workspace (resets workspace data)
 *  \param[out]    ElementPtr     found element
 *  \param[in]     ElementNrPtr   searched element number (chapter.section.subsection. ...)
 *  \param[in]     ElementDepth   depth of the element (chapter = 1, chapter.section = 2, ...)
 *  \param[in]     DataPtr        data
 *  \param[in]     DataSize       size of the data
 *  \return        IPBASE_E_OK        element was found
 *  \return        IPBASE_E_NOT_OK    element was not found
 *  \return        IPBASE_E_INV_PARAM data is corrupt
 *  \return        IPBASE_E_MEM       memory limit was exceeded
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE for different workspaces
 *  \synchronous   TRUE
 *  \trace         CREQ-120247
 *********************************************************************************************************************/
IPBASE_FUNCCODE(IpBase_ReturnType) IpBase_BerGetElement(
                                     IPBASE_CONSTP2VARAPPLDATA(IpBase_BerWorkspaceType) WorkspacePtr,
                                     IPBASE_P2VARAPPLDATA(IpBase_BerElementType) ElementPtr,
                                     IPBASE_P2CONSTAPPLDATA(uint8) ElementNrPtr,
                                     const uint8 ElementDepth,
                                     IPBASE_P2CONSTAPPLDATA(uint8) DataPtr,
                                     const uint32 DataSize);
#endif
  /* IPBASE_BER_H */
/**********************************************************************************************************************
 *  END OF FILE: IpBase_Ber.h
 *********************************************************************************************************************/
