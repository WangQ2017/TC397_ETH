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
/*!        \file  EthIf_Gw_Int.h
 *        \brief  EthIf Gw internal header file
 *
 *      \details  Provides access to types/functions/data of the sub-module Gw of EthIf only to be used internally,
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

#if !defined (ETHIF_GW_INT_H)
# define ETHIF_GW_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_Gw_Types_Int.h"

# include "EthIf.h"      /* access to DET error IDs */
# include "EthIf_Int.h"  /* access to components/utils shared with all EthIf modules */

/*********************************************************************************************************
 * Predefined file includes based on usage of other components/sub-modules within this sub-module
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
# include "EthIf_Tx_Int.h"
# include "EthIf_Mirror_Int.h"

/*********************************************************************************************************
 * Predefined file includes based on usage of this sub-module by other components/sub-modules
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
# include "EthIf_Rx_Types_Int.h"
# include "EthIf_Mode_Types_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETHIF_GW_INT_LOCAL)                                                                                      /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_GW_INT_LOCAL static
# endif

# if !defined (ETHIF_GW_INT_LOCAL_INLINE)                                                                               /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_GW_INT_LOCAL_INLINE LOCAL_INLINE
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

# if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_GATEWAY )                                                  /* COV_ETHIF_QM_FEAT_CHECK_ON */
/***********************************************************************************************************************
 *  EthIf_ManipulatePromiscuousMode
 **********************************************************************************************************************/
/*! \brief          Enables/disables the promiscouse mode of the Ethernet controller related to the EthIf controller in
 *                  in case EthIf controller is involved in traffic gateway.
 *  \details        Function enables/disables the promiscouse mode of the Ethernet controller related to the EthIf
 *                  controller if the EthIf controller is involved in a traffic gateway.
 *  \param[in]      ethIfCtrlIdx  EthIf Controller Index of gateway route source
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      filterAction  Action to be performed:
 *                                ETH_ADD_TO_FILTER - enables promiscous mode
 *                                ETH_REMOVE_FROM_FILTER - disables promiscous mode
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 **********************************************************************************************************************/
ETHIF_GW_INT_LOCAL_INLINE FUNC(void, ETHIF_GW_INLINE_CODE) EthIf_ManipulatePromiscuousMode( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx,
  Eth_FilterActionType     filterAction);
# endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

# if !defined(ETHIF_UNIT_TEST)                                                                                          /* COV_ETHIF_UNIT_TEST */
#  if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_GATEWAY )                                                 /* COV_ETHIF_QM_FEAT_CHECK_ON */
/***********************************************************************************************************************
 *  EthIf_ManipulatePromiscuousMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHIF_GW_INT_LOCAL_INLINE FUNC(void, ETHIF_GW_INLINE_CODE) EthIf_ManipulatePromiscuousMode( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx,
  Eth_FilterActionType     filterAction)
{
  /* ----- Local data declaration --------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if EthIf controller is involved in traffic gateway */
  if( EthIf_IsGatewayDestEthIfCtrlIdxUsedOfEthIfCtrl(ethIfCtrlIdx) == TRUE )
  {
    Std_ReturnType  retVal;

    /* #100 Apply promiscous mode change by calling the driver */
    retVal = EthIf_UpdatePhysAddrFilter((uint8)EthIf_GetSnvOfEthIfCtrl(ethIfCtrlIdx),
                                        EthIf_BroadcastMac,
                                        filterAction);                                                                  /* SBSW_ETHIF_CONST_VAR_PTR */

#   if ( ETHIF_DEV_ERROR_REPORT == STD_ON )                                                                             /* COV_ETHIF_QM_FEAT_INNER */
    if( retVal == E_NOT_OK )
    {
      /* Promiscous mode couldn't be enabled -> traffic gateway will not work */
      (void)Det_ReportError(ETHIF_MODULE_ID,
                            ETHIF_INSTANCE_ID_DET,
                            ETHIF_SID_GATEWAY_MANIPULATE_PROMISCOUS_MODE,
                            ETHIF_TRAFFIC_GATEWAY_E_MANIPULATE_PROMISCOUS_MODE);
    }
#   else
    ETHIF_DUMMY_STATEMENT(retVal); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#   endif /* ETHIF_DEV_ERROR_DETECT */
  }
} /* EthIf_ManipulatePromiscousMode() */
#  endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */
# endif /* ETHIF_UNIT_TEST */

# if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_GATEWAY )                                                  /* COV_ETHIF_QM_FEAT_CHECK_ON */
/***********************************************************************************************************************
 *  EthIf_GatewayTraffic
 **********************************************************************************************************************/
/*! \brief          Routes traffic to the destination EthIf controller if the source EthIf controller is
 *                  involved in a traffic gateway route
 *  \details        Function checks if the EthIf controller is involved in a traffic gateway route and, if this
 *                  is the case, allocates buffer and transmits the frame on the destination EthIf controller.
 *  \param[in]      srcEthIfCtrlIdx  EthIf Controller Index of gateway route source
 *                                   [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      srcFrameType     Frame type of gateway route source
 *  \param[in]      srcFrameLen      Frame length of gateway route source
 *  \param[in]      srcDataPtr       Pointer to the Ethernet payload data of gateway route source
 *  \return         FALSE - Source EthIf controller isn't involved in a gateway route\n
 *  \return         TRUE - Source EthIf controller is involved in a gateway route
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \trace          DSGN-EthIf22917
 **********************************************************************************************************************/
FUNC(boolean, ETHIF_CODE) EthIf_GatewayTraffic(
          EthIf_EthIfCtrlIterType                    srcEthIfCtrlIdx,
          Eth_FrameType                              srcFrameType,
          uint16                                     srcFrameLen,
  P2CONST(Eth_DataType, AUTOMATIC, ETHIF_APPL_DATA)  srcDataPtr);

# endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

/**********************************************************************************************************************
 *  EthIf_Gw_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the EthIf Gw sub-module
 *  \details        -
 *  \pre            Configuration pointer must have been initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_Gw_Init( void );

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_GW_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Gw_Int.h
 *********************************************************************************************************************/

