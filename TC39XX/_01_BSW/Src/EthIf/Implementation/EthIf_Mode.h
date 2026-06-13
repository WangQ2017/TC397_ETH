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
/*!        \file  EthIf_Mode.h
 *        \brief  EthIf Mode public API header
 *
 *      \details  Provides access to the public API of the sub-module Mode of EthIf.
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

#if !defined (ETHIF_MODE_H)
# define ETHIF_MODE_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_Mode_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

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
 *  EthIf_ControllerInit
 *********************************************************************************************************************/
/*! \brief          Initializes a EthIf controller
 *  \details        Function initializes the EthIf controller addressed and redirects the call to the underlying
 *                  hardware drivers mapped to the EthIf controller.
 *  \param[in]      CtrlIdx  EthIf controller that shall be initialized
 *  \param[in]      CfgIdx   Configuration index
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters or call interrupted pending operation
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-2393581
 *  \trace          DSGN-EthIf22859
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_ControllerInit(
  uint8  CtrlIdx,
  uint8  CfgIdx);

/**********************************************************************************************************************
 *  EthIf_SetControllerMode
 *********************************************************************************************************************/
/*! \brief          Modifies the EthIf controller mode
 *  \details        Function alters the EthIf controller mode and redirects the call to the underlying hardware
 *                  drivers mapped to the EthIf controller.
 *  \param[in]      CtrlIdx   EthIf controller the mode shall be changed for
 *  \param[in]      CtrlMode  Mode that shall be applied:
 *                            ETH_MODE_DOWN - shut down the EthIf controller
 *                            ETH_MODE_ACTIVE - activate the EthIf controller
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters or call interrupted pending operation
 *  \pre            EthIf_ControllerInit() was called for the respective EthIf controller before
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-2393586, SPEC-2393602
 *  \trace          DSGN-EthIf22866
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetControllerMode(
  uint8         CtrlIdx,
  Eth_ModeType  CtrlMode);

/**********************************************************************************************************************
 *  EthIf_GetControllerMode
 *********************************************************************************************************************/
/*! \brief          Retrieves the EthIf controller mode
 *  \details        -
 *  \param[in]      CtrlIdx               EthIf controller index
 *  \param[out]     CtrlModePtr  Pointer to store the mode retrieved:
 *                               ETH_MODE_DOWN - EthIf controller is turned of
 *                               ETH_MODE_ACTIVE - EthIf controller is active
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-2393591, SPEC-2393607
 *  \trace          DSGN-EthIf22866
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetControllerMode(
        uint8                                     CtrlIdx,
  P2VAR(Eth_ModeType, AUTOMATIC, ETHIF_APPL_VAR)  CtrlModePtr);

# if ( ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  EthIf_SwitchPortGroupRequestMode
 *********************************************************************************************************************/
/*! \brief          Requests a mode for a EthIf switch port group
 *  \details        -
 *  \param[in]      PortGroupIdx  EthIf switch port group the mode shall be changed for
 *  \param[in]      PortMode              Request for the EthIfSwtPortGroup
 *                                     ETHTRCV_MODE_DOWN - disable the port group
 *                                     ETHTRCV_MODE_ACTIVE - enable the port group
 *  \return         E_OK - success
 *  \return         E_NOT_OK - port group mode could not be changed
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT
 *  \trace          SPEC-2954358
 *  \trace          DSGN-EthIf22999
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchPortGroupRequestMode(
  EthIf_SwitchPortGroupIdxType PortGroupIdx,
  EthTrcv_ModeType PortMode);
# endif /* ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_MODE_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Mode.h
 *********************************************************************************************************************/

