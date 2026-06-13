/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthIf_Mode_Int.c
 *        \brief  EthIf Mode internal source file
 *
 *      \details  Contains the definition of data and implementation of functions of the sub-module Mode of EthIf
 *                only to be used EthIf internal.
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

#define ETHIF_MODE_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_Mode_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define ETHIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_Mode_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_Mode_Init( void )
{
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx;
  EthIf_EthCtrlIterType    ethCtrlIdx;
#if ( ETHIF_ETHTRCV_USED == STD_ON )                                                                                    /* COV_ETHIF_SAFE_FEAT */
  EthIf_EthTrcvIterType    ethTrcvIdx;
#endif /* ETHIF_ETHTRCV_USED */
#if ( ETHIF_ETHSWT_USED == STD_ON )
  EthIf_EthSwtIterType     ethSwtIdx;
  EthIf_EthSwtPortIterType ethSwtPortIdx;
  EthIf_PortGroupIterType  portGroupIdx;
#endif /* ETHIF_ETHSWT_USED */

  /* #10 Initialize the parallel processing protection semaphores for EthIf_ControllerInit()
   *     and EthIf_SetControllerMode() */
  EthIf_SetInitLocked(FALSE);                                                                                           /* SBSW_ETHIF_COMMON_CFG_PTR_INT_FCT_CALL_CONV */
  EthIf_SetModeChangeLocked(FALSE);                                                                                     /* SBSW_ETHIF_COMMON_CFG_PTR_INT_FCT_CALL_CONV */

  /* #20 Initialize mode to DOWN and init state to UNINIT for each EthIf controller */
  for( ethIfCtrlIdx = 0;
       ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl();
       ethIfCtrlIdx++ )
  {
    EthIf_SetEthIfCtrlMode(ethIfCtrlIdx, ETH_MODE_DOWN);                                                                /* SBSW_ETHIF_COMMON_CSL01 */
    EthIf_SetEthIfCtrlInitState(ethIfCtrlIdx, ETHIF_ETHIFCTRL_INIT_STATE_UNINIT);                                       /* SBSW_ETHIF_COMMON_CSL01 */
  }

  /* #30 Initialize initialization and mode counts to 0 for each Ethernet controller */
  for( ethCtrlIdx = 0;
       ethCtrlIdx < EthIf_GetSizeOfEthCtrl();
       ethCtrlIdx++ )
  {
    EthIf_SetEthCtrlInitCnt(ethCtrlIdx, 0u);                                                                            /* SBSW_ETHIF_COMMON_CSL01 */
    EthIf_SetEthCtrlModeCnt(ethCtrlIdx, 0u);                                                                            /* SBSW_ETHIF_COMMON_CSL01 */
  }

#if ( ETHIF_ETHTRCV_USED == STD_ON )                                                                                    /* COV_ETHIF_SAFE_FEAT */
  /* #40 Initialize initialization and mode counts to 0 for each Ethernet transceiver */
  for( ethTrcvIdx = 0;
       ethTrcvIdx < EthIf_GetSizeOfEthTrcv();
       ethTrcvIdx++ )
  {
    EthIf_SetEthTrcvInitCnt(ethTrcvIdx, 0u);                                                                            /* SBSW_ETHIF_COMMON_CSL01 */
    EthIf_SetEthTrcvModeCnt(ethTrcvIdx, 0u);                                                                            /* SBSW_ETHIF_COMMON_CSL01 */
  }
#endif /* ETHIF_ETHTRCV_USED */

#if ( ETHIF_ETHSWT_USED == STD_ON )
  /* #50 Initialize initialization counts to 0 for each Ethernet switch */
  for( ethSwtIdx = 0;
       ethSwtIdx < EthIf_GetSizeOfEthSwt();
       ethSwtIdx++ )
  {
    EthIf_SetEthSwtInitCnt(ethSwtIdx, 0u);                                                                              /* SBSW_ETHIF_COMMON_CSL01 */
  }

  /* #60 Initialize mode counts to 0 for each Ethernet switch port */
  for( ethSwtPortIdx = 0;
       ethSwtPortIdx < EthIf_GetSizeOfEthSwtPort();
       ethSwtPortIdx++ )
  {
    EthIf_SetEthSwtPortModeCnt(ethSwtPortIdx, 0u);                                                                      /* SBSW_ETHIF_COMMON_CSL01 */
  }

  /* #70 Initialize mode counts to 0 for each EtheIf switch port group */
  for( portGroupIdx = 0;
       portGroupIdx < EthIf_GetSizeOfPortGroup();
       portGroupIdx++ )
  {
    EthIf_SetPortGroupMode(portGroupIdx, ETHTRCV_MODE_DOWN);                                                            /* SBSW_ETHIF_COMMON_CSL01 */
  }
#endif /* ETHIF_ETHSWT_USED */
} /* EthIf_Mode_Init() */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Mode_Int.c
 *********************************************************************************************************************/

