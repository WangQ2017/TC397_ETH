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
/*!        \file  EthIf_Utils_Int.h
 *        \brief  EthIf Utils internal header file
 *
 *      \details  Provides access to types/functions/data of the sub-module Utils of EthIf only to be used internally,
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

#if !defined (ETHIF_UTILS_INT_H)
# define ETHIF_UTILS_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_Utils_Types_Int.h"

# include "EthIf.h"      /* access to DET error IDs */
# include "EthIf_Int.h"  /* access to components/utils shared with all EthIf modules */

/*********************************************************************************************************
 * Predefined file includes based on usage of other components/sub-modules within this sub-module
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* No dependency to other components/sub-modules */

/*********************************************************************************************************
 * Predefined file includes based on usage of this sub-module by other components/sub-modules
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
# include "EthIf_Rx_Types_Int.h"
# include "EthIf_Tx_Types_Int.h"
# include "EthIf_ZeroCopy_Types_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETHIF_UTILS_INT_LOCAL)                                                                                   /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_UTILS_INT_LOCAL static
# endif

# if !defined (ETHIF_UTILS_INT_LOCAL_INLINE)                                                                            /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_UTILS_INT_LOCAL_INLINE LOCAL_INLINE
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

/**********************************************************************************************************************
 *  EthIf_QueryForEthIfEthCtrl
 *********************************************************************************************************************/
/*! \brief          Queries for the EthIf  Eth controller
 *  \details        This function queries for the EthIf Eth controller by taking the symbolic name value of the
 *                  respective Ethernet controller.
 *  \param[in]      snvEth  Symbolic name value of the Ethernet controller
 *  \return         EthIf_GetSizeOfEthCtrl() - represents the first invalid EthIf Eth controller index
 *                                             -> no EthIf Eth controller found
 *  \return         other values - EthIf Eth controller index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_EthCtrlIterType, ETHIF_UTILS_INLINE_CODE) EthIf_QueryForEthIfEthCtrl( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  uint8  snvEth);

/**********************************************************************************************************************
 *  EthIf_QueryForEthIfController
 *********************************************************************************************************************/
/*! \brief          Queries for the EthIf controller
 *  \details        This function queries for the EthIf controller by taking the related Ethernet controller, information
 *                  if EthIf controller shall represent a non-tagged or tagged data path and in case of a tagged data path
 *                  by taking the VLAN ID.
 *  \param[in]      ethCtrlIdx  Ethernet controller index
 *  \param[in]      vlanId      VLAN ID that shall be used in case no VLAN is used ETHIF_INV_VLAN_ID
 *  \return         EthIf_GetSizeOfEthIfCtrl() - represents the first invalid EthIf controller index
 *                                               -> no EthIf controller found
 *  \return         other values - EthIf controller index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_EthIfCtrlIterType, ETHIF_UTILS_INLINE_CODE) EthIf_QueryForEthIfController( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthCtrlIterType  ethCtrlIdx,
  uint16                 vlanId);

/**********************************************************************************************************************
 *  EthIf_QueryForFrameOwner
 *********************************************************************************************************************/
/*! \brief          Queries for the owner of the EtherType
 *  \details        This function queries for the owner of the EtherType asked for.
 *  \param[in]      etherType   EtherType the owner shall be found for
 *  \return         EthIf_GetSizeOfUser() - represents the first invalid owner index
 *                                          -> no owner for EtherType found
 *  \return         other values - owner index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_UserIterType, ETHIF_UTILS_INLINE_CODE) EthIf_QueryForFrameOwner( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  Eth_FrameType etherType);

/**********************************************************************************************************************
 *  EthIf_GetMaxTxBufIdxForEthCtrl
 *********************************************************************************************************************/
/*! \brief          Returns the maximum allowed TX buffer index for a Ethernet controller
 *  \details        -
 *  \param[in]      ethCtrlIdx  Ethernet controller
 *                              [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \return         maximum buffer index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(uint8, ETHIF_UTILS_INLINE_CODE) EthIf_GetMaxTxBufIdxForEthCtrl( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthCtrlIterType  ethCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_GetMaxTxBufIdxForEthIfCtrl
 *********************************************************************************************************************/
/*! \brief          Returns the maximum allowed TX buffer index for a EthIf controller
 *  \details        -
 *  \param[in]      ethIfCtrlIdx  Ethernet controller
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \return         maximum buffer index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(uint8, ETHIF_UTILS_INLINE_CODE) EthIf_GetMaxTxBufIdxForEthIfCtrl( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_CalcTxCtxtIdx
 *********************************************************************************************************************/
/*! \brief          Calculates the index to access EthIf_TxContext array using ComStackLib
 *  \details        -
 *  \param[in]      ethCtrlIdx  Ethernet controller
 *                              [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      bufIdx      Ethernet TX buffer
 *                              [range: bufIdx <= EthIf_GetMaxTxBufIdxForEthCtrl(ethCtrlIdx)]
 *  \return         index for EthIf_TxContext array [range: 0 < EthIf_GetSizeOfTxContext()]
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_TxContextIterType, ETHIF_UTILS_INLINE_CODE) EthIf_CalcTxCtxtIdx( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthCtrlIterType  ethCtrlIdx,
  Eth_BufIdxType         bufIdx);

# if !defined(ETHIF_UNIT_TEST)                                                                                          /* COV_ETHIF_UNIT_TEST */
/**********************************************************************************************************************
 *  EthIf_QueryForEthIfEthCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_EthCtrlIterType, ETHIF_UTILS_INLINE_CODE) EthIf_QueryForEthIfEthCtrl( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  uint8  snvEth)
{
  EthIf_EthCtrlIterType ethCtrlIdx;
  EthIf_EthCtrlIterType queriedEthCtrlIdx = EthIf_GetSizeOfEthCtrl();

  /* #10 Query over all EthIf Eth controllers and check for a matching symbolic name value. If there is a match return
   *     the EthIf Eth controller index, otherwise return the first invalid index. */
  for( ethCtrlIdx = 0; ethCtrlIdx < EthIf_GetSizeOfEthCtrl(); ethCtrlIdx++ )
  {
    if( snvEth == EthIf_GetSnvOfEthCtrl(ethCtrlIdx) )
    {
      queriedEthCtrlIdx = ethCtrlIdx;
      break;
    }
  }

  return queriedEthCtrlIdx;
} /* EthIf_QueryForEthIfEthCtrl() */

/**********************************************************************************************************************
 *  EthIf_QueryForEthIfController
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_EthIfCtrlIterType, ETHIF_UTILS_INLINE_CODE) EthIf_QueryForEthIfController( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthCtrlIterType  ethCtrlIdx,
  uint16                 vlanId)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthIfCtrlIterType queriedEthIfCtrlIdx;
  EthIf_EthIfCtrlIterType ethIfCtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  queriedEthIfCtrlIdx = EthIf_GetSizeOfEthIfCtrl();

  /* #10 Query over all EthIf controllers and search for a matching Eth controller index and VLAN ID.
   *     If there is a match return the Eth controller index, otherwise return the first invalid index.*/
  for( ethIfCtrlIdx = 0;
       ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl();
       ethIfCtrlIdx++ )
  {
    if ( (EthIf_GetEthCtrlIdxOfEthIfCtrl(ethIfCtrlIdx) == ethCtrlIdx) &&
         (EthIf_GetVlanIdOfEthIfCtrl(ethIfCtrlIdx) == vlanId) )
    {
      queriedEthIfCtrlIdx = ethIfCtrlIdx;
      break;
    }
  }

  return queriedEthIfCtrlIdx;
} /* EthIf_QueryForEthIfController() */

/**********************************************************************************************************************
 *  EthIf_QueryForFrameOwner
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_UserIterType, ETHIF_UTILS_INLINE_CODE) EthIf_QueryForFrameOwner( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  Eth_FrameType etherType)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_UserIterType queriedOwnerIdx;
  EthIf_UserIterType userIdx;

  /* ----- Implementation ----------------------------------------------- */
  queriedOwnerIdx = EthIf_GetSizeOfUser();

  /* #10 For each owner */
  for( userIdx = 0u;
       userIdx < EthIf_GetSizeOfUser();
       userIdx++ )
  {
    /* #100 Check if EtherType of owner matches the EtherType queried for */
    if ( EthIf_GetEtherTypeOfUser(userIdx) == etherType )
    {
      /* #1000 EtherType matched -> owner found */
      queriedOwnerIdx = userIdx;
      break;
    }
  }

  return queriedOwnerIdx;
} /* EthIf_QueryForFrameOwner() */

/**********************************************************************************************************************
 *  EthIf_GetMaxTxBufIdxForEthCtrl
 *********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
*/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(uint8, ETHIF_UTILS_INLINE_CODE) EthIf_GetMaxTxBufIdxForEthCtrl( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthCtrlIterType  ethCtrlIdx)
{
  /* #10 Calculate the maximum allowed TX buffer index by the range defined for the TX buffers of the Ethernet controller
   *     by the EthIf_TxContext inderections mapped by ComStackLib. */
  return (uint8)(EthIf_GetTxContextEndIdxOfEthCtrl(ethCtrlIdx) - EthIf_GetTxContextStartIdxOfEthCtrl(ethCtrlIdx));
} /* EthIf_GetMaxTxBufIdxForEthCtrl */

/**********************************************************************************************************************
 *  EthIf_GetMaxTxBufIdxForEthIfCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(uint8, ETHIF_UTILS_INLINE_CODE) EthIf_GetMaxTxBufIdxForEthIfCtrl( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx)
{
  /* #10 Retrieve mapped Eth controller and trigger retrieval of maximum TX buffer index for it */
  return EthIf_GetMaxTxBufIdxForEthCtrl(EthIf_GetEthCtrlIdxOfEthIfCtrl(ethIfCtrlIdx));
} /* EthIf_GetMaxTxBufIdxForEthIfCtrl */

/**********************************************************************************************************************
 *  EthIf_CalcTxCtxtIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_TxContextIterType, ETHIF_UTILS_INLINE_CODE) EthIf_CalcTxCtxtIdx( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthCtrlIterType  ethCtrlIdx,
  Eth_BufIdxType         bufIdx)
{
  return EthIf_GetTxContextStartIdxOfEthCtrl(ethCtrlIdx) + (EthIf_TxContextIterType)bufIdx;
} /* EthIf_CalcTxCtxtIdx */
# endif /* ETHIF_UNIT_TEST */

/**********************************************************************************************************************
 *  EthIf_Utils_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the EthIf Utils sub-module
 *  \details        -
 *  \pre            Configuration pointer must have been initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_Utils_Init( void );

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_UTILS_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Utils_Int.h
 *********************************************************************************************************************/

