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
 *         File:  IpBase_Copy.h
 *      Project:  MICROSAR ETH
 *    Component:  SysService_IpBase
 *       Module:  MICROSAR IP Base
 *    Generator:  None
 *
 *  Description:  Copy API header
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
#if !defined (IPBASE_COPY_H)
# define IPBASE_COPY_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "IpBase_Types.h"
# include "vstdlib.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define IPBASE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  IpBase_Copy
 *********************************************************************************************************************/
/*! \brief        Copy data (memcpy)
 *  \details      Copy data alike memcpy
 *  \param[out]   TgtDataPtr            pointer for target data
 *  \param[in]    SrcDataPtr            pointer to source data
 *  \param[in]    LenByte               data length in bytes
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        CREQ-120245
 *********************************************************************************************************************/
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
# define IpBase_Copy(TgtDataPtr, SrcDataPtr, LenByte) \
           VStdMemCpy((TgtDataPtr), (SrcDataPtr), (LenByte))
/**********************************************************************************************************************
 *  IpBase_Fill
 *********************************************************************************************************************/
/*! \brief        Fill data (memset)
 *  \details      Fill memory with given pattern (memset)
 *  \param[out]   TgtDataPtr            pointer for target data
 *  \param[in]    Pattern               fill pattern
 *  \param[in]    LenByte               data length in bytes
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        CREQ-120245
 *********************************************************************************************************************/
/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
# define IpBase_Fill(TgtDataPtr, Pattern, LenByte) VStdMemSet((TgtDataPtr), (Pattern), (LenByte))

# define IPBASE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif
  /* IPBASE_COPY_H */
/**********************************************************************************************************************
 *  END OF FILE: IpBase_Copy.h
 *********************************************************************************************************************/
