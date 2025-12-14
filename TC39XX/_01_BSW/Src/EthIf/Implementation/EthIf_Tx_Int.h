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
/*!        \file  EthIf_Tx_Int.h
 *        \brief  EthIf Tx internal header file
 *
 *      \details  Provides access to types/functions/data of the sub-module Tx of EthIf only to be used internally,
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

#if !defined (ETHIF_TX_INT_H)
# define ETHIF_TX_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_Tx_Types_Int.h"

# include "EthIf.h"      /* access to DET error IDs */
# include "EthIf_Int.h"  /* access to components/utils shared with all EthIf modules */

/*********************************************************************************************************
 * Predefined file includes based on usage of other components/sub-modules within this sub-module
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to <User> resolved through EthIf_Lcfg.h -> no include needed */
/* Dependency to Eth resolved through EthIf_Lcfg.h -> no include needed */
# include "EthIf_Link_Int.h"
# include "EthIf_Stats_Int.h"
# include "EthIf_Utils_Int.h"
# include "EthIf_Mirror_Int.h"
# if ( ETHIF_FIREWALL_SUPPORT == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_CHECK_ON */
#  include "EthFw.h"
# endif

/*********************************************************************************************************
 * Predefined file includes based on usage of this sub-module by other components/sub-modules
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to <User> resolved through EthIf_Lcfg.h -> no include needed */
# include "EthIf_ZeroCopy_Types_Int.h"
# include "EthIf_EthCtrl_Types_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETHIF_TX_INT_LOCAL)                                                                                      /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_TX_INT_LOCAL static
# endif

# if !defined (ETHIF_TX_INT_LOCAL_INLINE)                                                                               /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_TX_INT_LOCAL_INLINE LOCAL_INLINE
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

# if !defined(ETHIF_UNIT_TEST)                                                                                          /* COV_ETHIF_UNIT_TEST */

# endif /* ETHIF_UNIT_TEST */

/**********************************************************************************************************************
 *  EthIf_Tx_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the EthIf Tx sub-module
 *  \details        -
 *  \pre            Configuration pointer must have been initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_Tx_Init( void );

/**********************************************************************************************************************
 *  EthIf_FinalizeTxBufferProvision
 *********************************************************************************************************************/
/*! \brief          Finalizes the tx buffer provision process
 *  \details        -
 *  \param[in]      ethIfCtrlIdx  EthIf controller the buffer provision is performed on
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      ethCtrlIdx    Eth controller the buffer provision is performed on
 *                                [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      frameType     EtherType the buffer provision is performed for
 *  \param[in]      priority      VLAN priority the frame shall be sent with
 *  \param[in]      bufIdx        Buffer index the frame is assigned to
 *                                [range: bufIdx <= EthIf_GetMaxTxBufForEthIfCtrl(ethIfCtrlIdx)]
 *  \param[in,out]  bufLenPtr     Length of the available payload:
 *                                [in] - length as provided by the driver
 *                                [out] - length changed with respect if data path is tagged or un-tagged
 *  \param[in,out]  bufPtr        Pointer to the payload:
 *                                [in] - pointer as provided by driver
 *                                [out] - pointer changed with respect if data path is tagged or un-tagged
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_FinalizeTxBufferProvision(
        EthIf_EthIfCtrlIterType                              ethIfCtrlIdx,
        EthIf_EthCtrlIterType                                ethCtrlIdx,
        Eth_FrameType                                        frameType,
        uint8                                                priority,
        uint8                                                bufIdx,
  P2VAR(uint16,                   AUTOMATIC, ETHIF_APPL_VAR) bufLenPtr,
  P2VAR(EthIf_FrameBufferPtrType, AUTOMATIC, ETHIF_APPL_VAR) bufPtr);

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_TX_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Tx_Int.h
 *********************************************************************************************************************/

