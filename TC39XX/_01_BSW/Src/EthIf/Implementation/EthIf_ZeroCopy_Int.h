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
/*!        \file  EthIf_ZeroCopy_Int.h
 *        \brief  EthIf ZeroCopy internal header file
 *
 *      \details  Provides access to types/functions/data of the sub-module ZeroCopy of EthIf only to be used internally,
 *                where functions are intended to be linked by linker.
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

#if !defined (ETHIF_ZEROCOPY_INT_H)
# define ETHIF_ZEROCOPY_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_ZeroCopy_Types_Int.h"

# include "EthIf.h"      /* access to DET error IDs */
# include "EthIf_Int.h"  /* access to components/utils shared with all EthIf modules */

/*********************************************************************************************************
 * Predefined file includes based on usage of other components/sub-modules within this sub-module
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to Eth resolved through EthIf_Lcfg.h -> no include needed */
# include "EthIf_Utils_Int.h"
# include "EthIf_Tx_Int.h"

/*********************************************************************************************************
 * Predefined file includes based on usage of this sub-module by other components/sub-modules
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to <User> resolved through EthIf_Lcfg.h -> no include needed */
/* Dependency to Eth resolved through EthIf_Lcfg.h -> no include needed */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETHIF_ZEROCOPY_INT_LOCAL)                                                                                /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_ZEROCOPY_INT_LOCAL static
# endif

# if !defined (ETHIF_ZEROCOPY_INT_LOCAL_INLINE)                                                                         /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_ZEROCOPY_INT_LOCAL_INLINE LOCAL_INLINE
# endif

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

# define ETHIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# if ( ETHIF_ENABLE_ZERO_COPY_EXTENSIONS == STD_ON )                                                                    /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_IsImplicitBufferReleaseNeeded
 *********************************************************************************************************************/
/*! \brief          Checks if a implicit buffer release is needed
 *  \details        This function checks if a implicit buffer release is needed for the frame received and designeted
 *                  for the given EthIf controller and EtherType.
 *  \param[in]      ethIfCtrlIdx  EthIf controller index
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      etherType     EtherType of the frame
 *  \return         FALSE - buffer must be explicitly released by upper layer
 *  \return         TRUE - buffer must implicitly released by EthIf
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_ZEROCOPY_INT_LOCAL_INLINE FUNC(boolean, ETHIF_ZEROCOPY_INLINE_CODE) EthIf_IsImplicitBufferReleaseNeeded( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx,
  Eth_FrameType            etherType);
# endif /* ETHIF_ENABLE_ZERO_COPY_EXTENSIONS */

# if !defined(ETHIF_UNIT_TEST)                                                                                          /* COV_ETHIF_UNIT_TEST */
#  if ( ETHIF_ENABLE_ZERO_COPY_EXTENSIONS == STD_ON )                                                                   /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_IsImplicitBufferReleaseNeeded
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHIF_ZEROCOPY_INT_LOCAL_INLINE FUNC(boolean, ETHIF_ZEROCOPY_INLINE_CODE) EthIf_IsImplicitBufferReleaseNeeded( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx,
  Eth_FrameType            etherType)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean      retVal;
  EthIf_ExplicitBufReleaseFilterIterType filterIdx;

  /* ----- Implementation ----------------------------------------------- */
  retVal = TRUE;

  /* #10 For each explicit buffer release filter rule */
  for( filterIdx = 0U;
       filterIdx < EthIf_GetSizeOfExplicitBufReleaseFilter();
       filterIdx++ )
  {
    /* #100 Check if filter rules' EthIf controller matches */
    if( EthIf_GetEthIfCtrlIdxOfExplicitBufReleaseFilter(filterIdx) == ethIfCtrlIdx )
    {
      boolean isUserFilterMatch = FALSE;

      /* #1000 Check if filter rules' EtherType matches or EtherType is a 'don't care' */
      if( EthIf_IsUserUsedOfExplicitBufReleaseFilter(filterIdx) == TRUE )
      {
        EthIf_UserIdxOfExplicitBufReleaseFilterType userIdx = EthIf_GetUserIdxOfExplicitBufReleaseFilter(filterIdx);
        if( EthIf_GetEtherTypeOfUser(userIdx) == etherType )
        {
          isUserFilterMatch = TRUE;
        }
      }
      else
      {
        isUserFilterMatch = TRUE;
      }

      /* #1100 Check if release of buffer is needed -> abort search */
      if( isUserFilterMatch == TRUE )
      {
        retVal = FALSE;
        break;
      }
    }
  }

  return retVal;
} /* EthIf_IsImplicitBufferReleaseNeeded() */
#  endif /* ETHIF_ENABLE_ZERO_COPY_EXTENSIONS */
# endif /* ETHIF_UNIT_TEST */

/**********************************************************************************************************************
 *  EthIf_ZeroCopy_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the EthIf ZeroCopy sub-module
 *  \details        -
 *  \pre            Configuration pointer must have been initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_ZeroCopy_Init( void );

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_ZEROCOPY_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_ZeroCopy_Int.h
 *********************************************************************************************************************/

