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
/*!        \file  EthIf_Mode.c
 *        \brief  EthIf Mode public API source file
 *
 *      \details  Implementation of the public API of the sub-module Mode of EthIf.
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

#define ETHIF_MODE_SOURCE

/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_Mode.h"
#include "EthIf_Mode_Cbk.h"
#include "EthIf_Mode_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Msn header file */
#if (  (ETHIF_SW_MAJOR_VERSION != (15u)) \
    || (ETHIF_SW_MINOR_VERSION != (0u)) \
    || (ETHIF_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthIf_Mode.c and EthIf.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Value defines the mode count that eventually leads to a mode DOWN request to the respective driver
 *  when a DOWN request is processed for an related EthIf controller. */
#define ETHIF_DRV_DOWN_REQUEST_MODE_CNT (1u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (ETHIF_MODE_LOCAL)                                                                                         /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_MODE_LOCAL static
#endif

#if !defined (ETHIF_MODE_LOCAL_INLINE)                                                                                  /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_MODE_LOCAL_INLINE LOCAL_INLINE
#endif

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

#if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                                /* COV_ETHIF_SAFE_FEAT */
/**********************************************************************************************************************
 *  EthIf_IsModeRequestPossible
 *********************************************************************************************************************/
/*! \brief          Checks if a mode request on the EthIf controller is possible.
 *  \details        Function checks if an additional mode request for the given target mode can be performed.
 *  \param[in]      ethIfCtrlIdx  EthIf controller index
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      trgtMode      Mode that the request is targeting for
 *  \return         TRUE - mode request can be processed
 *  \return         FALSE - mode request can not be processed
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(boolean, ETHIF_MODE_INLINE_CODE) EthIf_IsModeRequestPossible(
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx,
  Eth_ModeType             trgtMode);

# if ( ETHIF_ETHSWT_USED == STD_ON )
/**********************************************************************************************************************
 *  EthIf_IsModeRequestPossibleForEthIfSwtPortGroup
 *********************************************************************************************************************/
/*! \brief          Checks if a mode request on the EthIf switch port group is possible.
 *  \details        Function checks if an additional mode request for the given target mode can be performed.
 *  \param[in]      portGroupIdx  EthIf switch port group index
 *                                [range: portGroupIdx < EthIf_GetSizeOfPortGroup()]
 *  \param[in]      trgtMode      Mode that the request is targeting for
 *  \return         TRUE - mode request can be processed
 *  \return         FALSE - mode request can not be processed
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(boolean, ETHIF_MODE_INLINE_CODE) EthIf_IsModeRequestPossibleForEthIfSwtPortGroup(
  EthIf_PortGroupIterType  portGroupIdx,
  Eth_ModeType             trgtMode);
# endif /* ETHIF_ETHSWT_USED */
#endif /* ETHIF_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 *  EthIf_EnableEthCtrl
 *********************************************************************************************************************/
/*! \brief          Enables a Ethernet controller
 *  \details        -
 *  \param[in]      ethCtrlIdx  Eth controller that shall be enabled
 *                              [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \return         E_OK - Ethernet controller is already enabled or was enabled
 *  \return         E_NOT_OK - Ethernet controller couldn't be enabled
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_EnableEthCtrl(
  EthIf_EthCtrlIterType ethCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_TryEnableEthTrcv
 *********************************************************************************************************************/
/*! \brief          Tries to enable a Ethernet transceiver
 *  \details        Function checks if a Ethernet transceiver is mapped to the phyiscal layer elements of an EthIf
 *                  controller and if so enables it.
 *  \param[in]      physLayerModeElemsIdx  Physical layer elements of an EthIf controller
 *                                         [range: physLayerModeElemsIdx < EthIf_GetSizeOfPhysLayerModeElems()]
 *  \return         E_OK - Ethernet transceiver wasn't present, is already enabled or was enabled
 *  \return         E_NOT_OK - Ethernet transceiver couldn't be enabled
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_TryEnableEthTrcv(
  EthIf_PhysLayerModeElemsIterType  physLayerModeElemsIdx);

/**********************************************************************************************************************
 *  EthIf_TryEnableEthIfSwtPortGroup
 *********************************************************************************************************************/
/*! \brief          Tries to enable a EthIf switch port group
 *  \details        Function checks if a EthIf switch port group is mapped to the phyiscal layer elements of an EthIf
 *                  controller and if so enables it.
 *  \param[in]      physLayerModeElemsIdx  Physical layer elements of an EthIf controller
 *                                         [range: physLayerModeElemsIdx < EthIf_GetSizeOfPhysLayerModeElems()]
 *  \return         E_OK - EthIf switch port group wasn't present, is already enabled or was enabled
 *  \return         E_NOT_OK - EthIf switch port group couldn't be enabled
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_TryEnableEthIfSwtPortGroup(
  EthIf_PhysLayerModeElemsIterType  physLayerModeElemsIdx);

/**********************************************************************************************************************
 *  EthIf_UpdateEthIfCtrlStatesAfterActive
 *********************************************************************************************************************/
/*! \brief          Updates a EthIf controllers states after a successful ACTIVE request
 *  \details        -
 *  \param[in]      ethIfCtrlIdx  EthIf controller the states shall be updated for
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_UpdateEthIfCtrlStatesAfterActive(
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_UpdateEthCtrlStatesAfterActive
 *********************************************************************************************************************/
/*! \brief          Updates a Eth controllers states after a successful ACTIVE request
 *  \details        -
 *  \param[in]      ethCtrlIdx  Eth controller the states shall be updated for
 *                              [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_UpdateEthCtrlStatesAfterActive(
  EthIf_EthCtrlIterType  ethCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_TryUpdateEthTrcvStatesAfterActive
 *********************************************************************************************************************/
/*! \brief          Tries to update a Ethernet transceivers states after a successful ACTIVE request
 *  \details        Function checks if a Ethernet transceiver is mapped to the phyiscal layer elements of an EthIf
 *                  controller and if so updates its states.
 *  \param[in]      physLayerModeElemsIdx  Physical layer elements of an EthIf controller
 *                                         [range: physLayerModeElemsIdx < EthIf_GetSizeOfPhysLayerModeElems()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_TryUpdateEthTrcvStatesAfterActive(
  EthIf_PhysLayerModeElemsIterType  physLayerModeElemsIdx);

/**********************************************************************************************************************
 *  EthIf_TryUpdateEthIfSwtPortGroupStatesAfterActive
 *********************************************************************************************************************/
/*! \brief          Tries to update a EthIf switch port groups states after a successful ACTIVE request
 *  \details        Function checks if a EthIf switch port group is mapped to the phyiscal layer elements of an EthIf
 *                  controller and if so updates its states.
 *  \param[in]      physLayerModeElemsIdx  Physical layer elements of an EthIf controller
 *                                         [range: physLayerModeElemsIdx < EthIf_GetSizeOfPhysLayerModeElems()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_TryUpdateEthIfSwtPortGroupStatesAfterActive(
  EthIf_PhysLayerModeElemsIterType  physLayerModeElemsIdx);

/**********************************************************************************************************************
 *  EthIf_SetHardwareModeActive
 *********************************************************************************************************************/
/*! \brief          Sets the hardware to ACTIVE state
 *  \details        This functions sets the hardware elements mapped to the EthIf controller to state ACTIVE by utilizing
 *                  the respective driver.
 *  \param[in]      ethIfCtrlIdx  EthIf controller index
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \return         E_OK - success
 *  \return         E_NOT_OK - mode adaption wasn't possible
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_SetHardwareModeActive(
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_DisableEthCtrl
 *********************************************************************************************************************/
/*! \brief          Disables a Ethernet controller
 *  \details        -
 *  \param[in]      ethCtrlIdx  Eth controller that shall be disabled
 *                              [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \return         E_OK - Ethernet controller is still requested or was disabled
 *  \return         E_NOT_OK - Ethernet controller couldn't be disabled
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_DisableEthCtrl(
  EthIf_EthCtrlIterType  ethCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_TryDisableEthTrcv
 *********************************************************************************************************************/
/*! \brief          Tries to disable a Ethernet transceiver
 *  \details        Function checks if a Ethernet transceiver is mapped to the phyiscal layer elements of an EthIf
 *                  controller and if so disables it.
 *  \param[in]      physLayerModeElemsIdx  Physical layer elements of an EthIf controller
 *                                         [range: physLayerModeElemsIdx < EthIf_GetSizeOfPhysLayerModeElems()]
 *  \return         E_OK - Ethernet transceiver wasn't present, is still requested or was disabled
 *  \return         E_NOT_OK - Ethernet transceiver couldn't be disabled
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_TryDisableEthTrcv(
  EthIf_PhysLayerModeElemsIterType  physLayerModeElemsIdx);

/**********************************************************************************************************************
 *  EthIf_TryDisableEthIfSwtPortGroup
 *********************************************************************************************************************/
/*! \brief          Tries to disable a EthIf switch port group
 *  \details        Function checks if a EthIf switch port group is mapped to the phyiscal layer elements of an EthIf
 *                  controller and if so disables it.
 *  \param[in]      physLayerModeElemsIdx  Physical layer elements of an EthIf controller
 *                                         [range: physLayerModeElemsIdx < EthIf_GetSizeOfPhysLayerModeElems()]
 *  \return         E_OK - EthIf switch port group wasn't present or was enabled
 *  \return         E_NOT_OK - EthIf switch port group couldn't be disabled
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_TryDisableEthIfSwtPortGroup(
  EthIf_PhysLayerModeElemsIterType  physLayerModeElemsIdx);

/**********************************************************************************************************************
 *  EthIf_UpdateEthIfCtrlStatesAfterDown
 *********************************************************************************************************************/
/*! \brief          Updates a EthIf controllers states after a successful DOWN request
 *  \details        -
 *  \param[in]      ethIfCtrlIdx  EthIf controller the states shall be updated for
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_UpdateEthIfCtrlStatesAfterDown(
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_UpdateEthCtrlStatesAfterDown
 *********************************************************************************************************************/
/*! \brief          Updates a Eth controllers states after a successful DOWN request
 *  \details        -
 *  \param[in]      ethCtrlIdx  Eth controller the states shall be updated for
 *                              [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_UpdateEthCtrlStatesAfterDown(
  EthIf_EthCtrlIterType  ethCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_TryUpdateEthTrcvStatesAfterDown
 *********************************************************************************************************************/
/*! \brief          Tries to update a Ethernet transceivers states after a successful DOWN request
 *  \details        Function checks if a Ethernet transceiver is mapped to the phyiscal layer elements of an EthIf
 *                  controller and if so updates its states.
 *  \param[in]      physLayerModeElemsIdx  Physical layer elements of an EthIf controller
 *                                         [range: physLayerModeElemsIdx < EthIf_GetSizeOfPhysLayerModeElems()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_TryUpdateEthTrcvStatesAfterDown(
  EthIf_PhysLayerModeElemsIterType  physLayerInitElemsIdx);

/**********************************************************************************************************************
 *  EthIf_TryUpdateEthIfSwtPortGroupStatesAfterDown
 *********************************************************************************************************************/
/*! \brief          Tries to update a EthIf switch port groups states after a successful DOWN request
 *  \details        Function checks if a EthIf switch port group is mapped to the phyiscal layer elements of an EthIf
 *                  controller and if so updates its states.
 *  \param[in]      physLayerModeElemsIdx  Physical layer elements of an EthIf controller
 *                                         [range: physLayerModeElemsIdx < EthIf_GetSizeOfPhysLayerModeElems()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_TryUpdateEthIfSwtPortGroupStatesAfterDown(
  EthIf_PhysLayerModeElemsIterType  physLayerInitElemsIdx);

/**********************************************************************************************************************
 *  EthIf_SetHardwareModeDown
 *********************************************************************************************************************/
/*! \brief          Sets the hardware to DOWN state
 *  \details        This functions sets the hardware elements mapped to the EthIf controller to state DOWN by utilizing
 *                  the respective driver.
 *  \param[in]      ethIfCtrlIdx  EthIf controller index
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \return         E_OK - success
 *  \return         E_NOT_OK - mode adaption wasn't possible
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_SetHardwareModeDown(
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx);

#if ( ETHIF_ETHSWT_USED == STD_ON )
/**********************************************************************************************************************
 *  EthIf_SetEthIfSwtPortGroupMode
 *********************************************************************************************************************/
/*! \brief          Sets the Port Group Ports to ACTIVE or DOWN mode
 *  \details        This functions sets the hardware elements mapped to the EthIf controller to state ACTIVE by utilizing
 *                  the respective driver.
 *  \param[in]      portGroupIdx  EthIf switch port group index
 *                                [range: portGroupIdx < EthIf_GetSizeOfPortGroup()]
 *  \param[in]      trgtMode      Mode to set for the EthIf switch port group
 *                                ETHTRCV_MODE_DOWN - disable the port group
 *                                ETHTRCV_MODE_ACTIVE - enable the port group
 *  \return         E_OK - success
 *  \return         E_NOT_OK - mode adaption wasn't possible
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_SetEthIfSwtPortGroupMode(
  EthIf_PortGroupIterType  portGroupIdx,
  EthTrcv_ModeType         trgtMode);

/**********************************************************************************************************************
 *  EthIf_AdjustEthIfSwtPortGroupModeCount
 *********************************************************************************************************************/
/*! \brief          Increments or decrements the Port Group Ports mode counter values
 *  \details        This functions sets the hardware elements mapped to the EthIf controller to state ACTIVE by utilizing
 *                  the respective driver.
 *  \param[in]      portGroupIdx  EthIf switch port group index
 *                                [range: portGroupIdx < EthIf_GetSizeOfPortGroup()]
 *  \param[in]      trgtMode      Increment or decrement the Port Group Ports Mode counter values
 *                                ETHTRCV_MODE_DOWN - decrement the Port Group Ports Mode counter values
 *                                ETHTRCV_MODE_ACTIVE - increments the Port Group Ports Mode counter values
 *  \return         E_OK - success
 *  \return         E_NOT_OK - counter adjustment wasn't possible
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_AdjustEthIfSwtPortGroupModeCount(
  EthIf_PortGroupIterType  portGroupIdx,
  EthTrcv_ModeType         trgtMode);
#endif /* ETHIF_ETHSWT_USED */

/**********************************************************************************************************************
 *  EthIf_TryTakeInitSemaphore
 *********************************************************************************************************************/
/*! \brief          Tries to take the initialization protection semaphore
 *  \details        -
 *  \return         TRUE - semaphore taken
 *  \return         FALSE - semaphore already in use
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(boolean, ETHIF_MODE_INLINE_CODE) EthIf_TryTakeInitSemaphore( void );

/**********************************************************************************************************************
 *  EthIf_ReleaseInitSemaphore
 *********************************************************************************************************************/
/*! \brief          Releases the initialization protection semaphore
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_ReleaseInitSemaphore( void );

/**********************************************************************************************************************
 *  EthIf_TryTakeModeChangeSemaphore
 *********************************************************************************************************************/
/*! \brief          Tries to take the mode change protection semaphore
 *  \details        -
 *  \return         TRUE - semaphore taken
 *  \return         FALSE - semaphore already in use
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(boolean, ETHIF_MODE_INLINE_CODE) EthIf_TryTakeModeChangeSemaphore( void );

/**********************************************************************************************************************
 *  EthIf_ReleaseModeChangeSemaphore
 *********************************************************************************************************************/
/*! \brief          Releases the mode change protection semaphore
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_ReleaseModeChangeSemaphore( void );

/**********************************************************************************************************************
 *  EthIf_InitEthCtrl
 *********************************************************************************************************************/
/*! \brief          Initializes a Eth controller
 *  \details        -
 *  \param[in]      ethCtrlIdx  Eth controller that shall be initialized
 *                              [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      cfgIdx      Configuration index
 *  \return         E_OK - Eth controller was already initialized or initialization was performed
 *  \return         E_NOT_OK - Eth controller initialization failed
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_InitEthCtrl(
   EthIf_EthCtrlIterType ethCtrlIdx,
   uint8                 cfgIdx);

/**********************************************************************************************************************
 *  EthIf_TryInitEthTrcv
 *********************************************************************************************************************/
/*! \brief          Tries to initialize a Ethernet transceiver
 *  \details        Function checks if a Ethernet transceiver is mapped to the phyiscal layer elements of an EthIf
 *                  controller and if so initializes it.
 *  \param[in]      physLayerInitElemsIdx  Physical layer elements of an EthIf controller
 *                                         [range: physLayerInitElemsIdx < EthIf_GetSizeOfPhysLayerInitElems()]
 *  \param[in]      cfgIdx                 Configuration index
 *  \return         E_OK - Eth transceiver wasn't mapped, was already initialized or initialization was performed
 *  \return         E_NOT_OK - Eth transceiver initialization failed
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_TryInitEthTrcv(
  EthIf_PhysLayerInitElemsIterType physLayerInitElemsIdx,
  uint8                            cfgIdx);

/**********************************************************************************************************************
 *  EthIf_TryInitEthSwt
 *********************************************************************************************************************/
/*! \brief          Tries to initialize a Ethernet switch
 *  \details        Function checks if a Ethernet switch is mapped to the phyiscal layer elements of an EthIf
 *                  controller and if so initializes them.
 *  \param[in]      physLayerInitElemsIdx  Physical layer elements of an EthIf controller
 *                                         [range: physLayerInitElemsIdx < EthIf_GetSizeOfPhysLayerInitElems()]
 *  \param[in]      cfgIdx                 Configuration index
 *  \return         E_OK - Eth switch wasn't mapped, was already initialized or initialization was performed
 *  \return         E_NOT_OK - Eth switch initialization failed
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_TryInitEthSwt(
  EthIf_PhysLayerInitElemsIterType physLayerInitElemsIdx);

/**********************************************************************************************************************
 *  EthIf_UpdateEthIfCtrlStatesAfterInit
 *********************************************************************************************************************/
/*! \brief          Updates a EthIf controllers states after a successful initialization request
 *  \details        -
 *  \param[in]      ethIfCtrlIdx  EthIf controller the states shall be updated for
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_UpdateEthIfCtrlStatesAfterInit(
  EthIf_EthIfCtrlIterType ethIfCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_UpdateEthCtrlStatesAfterInit
 *********************************************************************************************************************/
/*! \brief          Updates a Eth controllers states after a successful initialization request
 *  \details        -
 *  \param[in]      ethCtrlIdx  Eth controller the states shall be updated for
 *                              [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_UpdateEthCtrlStatesAfterInit(
  EthIf_EthCtrlIterType ethCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_TryUpdateEthTrcvStatesAfterInit
 *********************************************************************************************************************/
/*! \brief          Tries to update a Ethernet transceivers states after a successful initialization request
 *  \details        Function checks if a Ethernet transceiver is mapped to the phyiscal layer elements of an EthIf
 *                  controller and if so updates its states.
 *  \param[in]      physLayerInitElemsIdx  Physical layer elements of an EthIf controller
 *                                         [range: physLayerInitElemsIdx < EthIf_GetSizeOfPhysLayerInitElems()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_TryUpdateEthTrcvStatesAfterInit(
  EthIf_PhysLayerInitElemsIterType physLayerInitElemsIdx);

/**********************************************************************************************************************
 *  EthIf_TryUpdateEthSwtStatesAfterInit
 *********************************************************************************************************************/
/*! \brief          Tries to update a Ethernet switches states after a successful initialization request
 *  \details        Function checks if a Ethernet switch is mapped to the phyiscal layer elements of an EthIf
 *                  controller and if so updates its states.
 *  \param[in]      physLayerInitElemsIdx  Physical layer elements of an EthIf controller
 *                                         [range: physLayerInitElemsIdx < EthIf_GetSizeOfPhysLayerInitElems()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_TryUpdateEthSwtStatesAfterInit(
  EthIf_PhysLayerInitElemsIterType physLayerInitElemsIdx);

/**********************************************************************************************************************
 *  EthIf_Internal_ControllerInit
 *********************************************************************************************************************/
/*! \brief          Initializes a EthIf controller
 *  \details        See EthIf_ControllerInit() for details.
 *  \param[in]      ethIfCtrlIdx  EthIf controller that shall be initialized
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      cfgIdx        Configuration index
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters or call interrupted pending operation
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_Internal_ControllerInit(
  uint8  ethIfCtrlIdx,
  uint8  cfgIdx);

/**********************************************************************************************************************
 *  EthIf_Internal_SetControllerMode
 *********************************************************************************************************************/
/*! \brief          Modifies the EthIf controller mode
 *  \details        See EthIf_SetControllerMode() for details.
 *  \param[in]      ethIfCtrlIdx   EthIf controller the mode shall be changed for
 *                                 [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      ctrlMode       Mode that shall be applied:
 *                                 ETH_MODE_DOWN - shut down the EthIf controller
 *                                 ETH_MODE_ACTIVE - activate the EthIf controller
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters or call interrupted pending operation
 *  \pre            EthIf_ControllerInit() was called for the respective EthIf controller before
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_Internal_SetControllerMode(
  uint8         ethIfCtrlIdx,
  Eth_ModeType  ctrlMode);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
/**********************************************************************************************************************
 *  EthIf_IsModeRequestPossible
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(boolean, ETHIF_MODE_INLINE_CODE) EthIf_IsModeRequestPossible(
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx,
  Eth_ModeType             trgtMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean                         result;
  EthIf_EthCtrlModeCntType        thresholdCnt;
  EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(ethIfCtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  result = TRUE;

  /* #10 Set the pass error criteria for possibility check dependent on the targeted mode */
  thresholdCnt = ETHIF_MIN_ETHCTRLMODECNT; /* for trgtMode == ETH_MODE_DOWN the threshold is 0 */

  if( trgtMode == ETH_MODE_ACTIVE )
  {
    thresholdCnt = ETHIF_MAX_ETHCTRLMODECNT;
  }

  /* #20 Check for the possibility to process the mode request */
  if( EthIf_GetEthCtrlModeCnt(ethCtrlIdx) == thresholdCnt )
  {
    result = FALSE;
  }
  else
  {
    EthIf_PhysLayerModeElemsIdxOfEthIfCtrlType physLayerModeElemsIdx = EthIf_GetPhysLayerModeElemsIdxOfEthIfCtrl(ethIfCtrlIdx);

# if (ETHIF_ETHTRCV_USED == STD_ON)                                                                                     /* COV_ETHIF_SAFE_FEAT */
    if( EthIf_IsEthTrcvUsedOfPhysLayerModeElems(physLayerModeElemsIdx) )
    {
      EthIf_EthTrcvIdxOfPhysLayerModeElemsType ethTrcvIdx = EthIf_GetEthTrcvIdxOfPhysLayerModeElems(physLayerModeElemsIdx);

      if( EthIf_GetEthTrcvModeCnt(ethTrcvIdx) == thresholdCnt )
      {
        result = FALSE;
      }
    }
# endif /* ETHIF_ETHTRCV_USED */
# if ( ETHIF_ETHSWT_USED == STD_ON )
    if( EthIf_IsPortGroupUsedOfPhysLayerModeElems(physLayerModeElemsIdx) )
    {
      EthIf_PortGroupIdxOfPhysLayerModeElemsType portGroupIdx = EthIf_GetPortGroupIdxOfPhysLayerModeElems(physLayerModeElemsIdx);
      result = EthIf_IsModeRequestPossibleForEthIfSwtPortGroup(portGroupIdx, trgtMode);
    }
# endif /* ETHIF_ETHSWT_USED */
  }

  return result;
} /* EthIf_IsModeRequestPossible() */

# if ( ETHIF_ETHSWT_USED == STD_ON )
/**********************************************************************************************************************
 *  EthIf_IsModeRequestPossibleForEthIfSwtPortGroup
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(boolean, ETHIF_MODE_INLINE_CODE) EthIf_IsModeRequestPossibleForEthIfSwtPortGroup(
  EthIf_PortGroupIterType  portGroupIdx,
  Eth_ModeType             trgtMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean                      result;
  EthIf_EthSwtPortModeCntType  thresholdCnt;

  /* ----- Implementation ----------------------------------------------- */
  result = TRUE;

  /* #10 Set the pass error criteria for possibility check dependent on the targeted mode */
  thresholdCnt = ETHIF_MIN_ETHSWTPORTMODECNT; /* for trgtMode == ETH_MODE_DOWN the threshold is 0 */

  if( trgtMode == ETHTRCV_MODE_ACTIVE )
  {
    thresholdCnt = ETHIF_MAX_ETHSWTPORTMODECNT;
  }

  /* #20 Check for the possibility to process the mode request */
  if( (EthIf_GetSemanticOfPortGroup(portGroupIdx) == ETHIF_PORTGROUP_SEMANTIC_CONTROL_SEMANTICOFPORTGROUP) ||
      (EthIf_GetSemanticOfPortGroup(portGroupIdx) == ETHIF_PORTGROUP_SEMANTIC_INDEPENDENT_SEMANTICOFPORTGROUP) )
  {
    EthIf_EthSwtPortIterType indIdx;

    /* #210 Enter exclusive area (Reason: Ensure consistency of mode and link state information) */
    EthIf_EnterExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    for( indIdx = EthIf_GetEthSwtPortIndStartIdxOfPortGroup(portGroupIdx);
         indIdx < EthIf_GetEthSwtPortIndEndIdxOfPortGroup(portGroupIdx);
         indIdx++ )
    {
      EthIf_EthSwtPortIndType ethSwtPortIdx = EthIf_GetEthSwtPortInd(indIdx);

      /* #2110 Check switch port mode counter */
      if( EthIf_GetEthSwtPortModeCnt(ethSwtPortIdx) == thresholdCnt )
      {
        result = FALSE;
        break;
      }
    }

    /* #220 Leave exclusive area -> processing on elements finished */
    EthIf_ExitExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

  return result;
} /* EthIf_IsModeRequestPossibleForEthIfSwtPortGroup() */
# endif /* ETHIF_ETHSWT_USED */
#endif /* ETHIF_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 *  EthIf_EnableEthCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_EnableEthCtrl(
  EthIf_EthCtrlIterType  ethCtrlIdx)
{
  Std_ReturnType retVal = E_OK;

  /* #10 Enable Ethernet Controller if no previous ACTIVE request for it was triggered */
  if( EthIf_GetEthCtrlModeCnt(ethCtrlIdx) == ETHIF_MIN_ETHCTRLMODECNT )
  {
    EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);
    /* call only when Ethernet Controller wasn't enabled before */
    /* \trace SPEC-2393587 */
    retVal = EthIf_GetSetCtrlModeOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                           ETH_MODE_ACTIVE);                                            /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_CSL03 */
  }

  return retVal;
} /* EthIf_EnableEthCtrl() */

/**********************************************************************************************************************
 *  EthIf_TryEnableEthTrcv
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_TryEnableEthTrcv(
  EthIf_PhysLayerModeElemsIterType  physLayerModeElemsIdx)
{
  Std_ReturnType retVal = E_OK;

#if (ETHIF_ETHTRCV_USED == STD_ON)                                                                                      /* COV_ETHIF_SAFE_FEAT */
    /* #10 Check if there is a Ethernet transceiver mapped to the EthIf controllers physical layer elements */
    if( EthIf_IsEthTrcvUsedOfPhysLayerModeElems(physLayerModeElemsIdx) == TRUE )
    {
      EthIf_EthTrcvIdxOfPhysLayerModeElemsType ethTrcvIdx = EthIf_GetEthTrcvIdxOfPhysLayerModeElems(physLayerModeElemsIdx);
      EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

      /* #100 Check if there was no ACTIVE request for the Ethernet transceiver before */
      if( EthIf_GetEthTrcvModeCnt(ethTrcvIdx) == ETHIF_MIN_ETHTRCVMODECNT )
      {
        /* #1000 Trigger enabling of the Ethernet transceiver by utilizing the driver */
        if( EthIf_GetSetTrcvModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
        {
          retVal = EthIf_GetSetTrcvModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(ethTrcvIdx),
                                                                         ETHTRCV_MODE_ACTIVE);                          /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
        }
      }
    }
    /* #20 Otherwise (if no EthTrcv used or already an ACTIVE request was pending) silently return the request without
     *     influencing the hardware */
#endif /* ETHIF_ETHTRCV_USED */

  return retVal;
} /* EthIf_TryEnableEthTrcv() */

/**********************************************************************************************************************
 *  EthIf_TryEnableEthIfSwtPortGroup
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_TryEnableEthIfSwtPortGroup(
  EthIf_PhysLayerModeElemsIterType  physLayerModeElemsIdx)
{
  Std_ReturnType retVal = E_OK;

#if (ETHIF_ETHSWT_USED == STD_ON)
  /* #10 Check if there is a EthIf switch port group mapped to the EthIf controllers physical layer elements */
  if( EthIf_IsPortGroupUsedOfPhysLayerModeElems(physLayerModeElemsIdx) == TRUE )
  {
    /* #100 Trigger enabling of the Ethernet transceiver by utilizing the driver */
    EthIf_PortGroupIdxOfPhysLayerModeElemsType portGroupIdx = EthIf_GetPortGroupIdxOfPhysLayerModeElems(physLayerModeElemsIdx);
    retVal = EthIf_SetEthIfSwtPortGroupMode(portGroupIdx, ETHTRCV_MODE_ACTIVE);
  }
#else
  ETHIF_DUMMY_STATEMENT(physLayerModeElemsIdx); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* ETHIF_ETHSWT_USED */
  /* #20 Otherwise (if no EthIf switch port group used) silently return the request without influencing the hardware */

  return retVal;
} /* EthIf_TryEnableEthIfSwtPortGroup() */

/**********************************************************************************************************************
 *  EthIf_UpdateEthIfCtrlStatesAfterActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_UpdateEthIfCtrlStatesAfterActive(
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx)
{
  /* #10 Set EthIf controller in active state */
  EthIf_SetEthIfCtrlMode(ethIfCtrlIdx, ETH_MODE_ACTIVE);                                                                /* SBSW_ETHIF_INT_FCT_IDX_PASS */
} /* EthIf_UpdateEthIfCtrlStatesAfterActive() */

/**********************************************************************************************************************
 *  EthIf_UpdateEthCtrlStatesAfterActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_UpdateEthCtrlStatesAfterActive(
  EthIf_EthCtrlIterType  ethCtrlIdx)
{
  /* #10 Update the amount of ACTIVE requests for the Ethernet Controller */
  EthIf_IncEthCtrlModeCnt(ethCtrlIdx);                                                                                  /* SBSW_ETHIF_INT_FCT_IDX_PASS */
} /* EthIf_UpdateEthCtrlStatesAfterActive() */

/**********************************************************************************************************************
 *  EthIf_TryUpdateEthTrcvStatesAfterActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_TryUpdateEthTrcvStatesAfterActive(
  EthIf_PhysLayerModeElemsIterType  physLayerModeElemsIdx)
{
#if (ETHIF_ETHTRCV_USED == STD_ON)                                                                                      /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check if there is a Ethernet transceiver mapped to the EthIf controllers physical layer elements */
  if( EthIf_IsEthTrcvUsedOfPhysLayerModeElems(physLayerModeElemsIdx) == TRUE )
  {
    EthIf_EthTrcvIdxOfPhysLayerModeElemsType ethTrcvIdx = EthIf_GetEthTrcvIdxOfPhysLayerModeElems(physLayerModeElemsIdx);
    EthIf_IncEthTrcvModeCnt(ethTrcvIdx);                                                                                /* SBSW_ETHIF_COMMON_CSL03 */
  }
#endif /* ETHIF_ETHTRCV_USED */
  /* #20 Otherwise (if no EthTrcv used) silently return */
} /* EthIf_TryUpdateEthTrcvStatesAfterActive() */

/**********************************************************************************************************************
 *  EthIf_TryUpdateEthIfSwtPortGroupStatesAfterActive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_TryUpdateEthIfSwtPortGroupStatesAfterActive(
  EthIf_PhysLayerModeElemsIterType  physLayerModeElemsIdx)
{
#if (ETHIF_ETHSWT_USED == STD_ON)
  /* #10 Check if there is a EthIf switch port group mapped to the EthIf controllers physical layer elements */
  if( EthIf_IsPortGroupUsedOfPhysLayerModeElems(physLayerModeElemsIdx) == TRUE )
  {
    /* #100 Trigger update of the amount of ACTIVE requests for the EthIf switch port group */
    EthIf_PortGroupIdxOfPhysLayerModeElemsType portGroupIdx = EthIf_GetPortGroupIdxOfPhysLayerModeElems(physLayerModeElemsIdx);
    EthIf_AdjustEthIfSwtPortGroupModeCount(portGroupIdx, ETHTRCV_MODE_ACTIVE);
  }
#else
  ETHIF_DUMMY_STATEMENT(physLayerModeElemsIdx); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* ETHIF_ETHSWT_USED */
  /* #20 Otherwise (if no EthIf switch port group used) silently return */
} /* EthIf_TryUpdateEthIfSwtPortGroupStatesAfterActive() */

/**********************************************************************************************************************
 *  EthIf_SetHardwareModeActive
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
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_SetHardwareModeActive(
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal;
  EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(ethIfCtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  retVal = EthIf_EnableEthCtrl(ethCtrlIdx);

  /* #20 If setting the mode for the Ethernet controller was successful */
  if( retVal == E_OK )
  {
    EthIf_PhysLayerModeElemsIdxOfEthIfCtrlType physLayerModeElemsIdx = EthIf_GetPhysLayerModeElemsIdxOfEthIfCtrl(ethIfCtrlIdx);

    retVal  = EthIf_TryEnableEthTrcv(physLayerModeElemsIdx);
    retVal |= EthIf_TryEnableEthIfSwtPortGroup(physLayerModeElemsIdx); /* PRQA S 2985 */ /* MD_EthIf_2985 */
  }

  /* #30 If setting the mode for the physical layer was successful */
  if( retVal == E_OK )
  {
    EthIf_PhysLayerModeElemsIdxOfEthIfCtrlType physLayerModeElemsIdx = EthIf_GetPhysLayerModeElemsIdxOfEthIfCtrl(ethIfCtrlIdx);

    EthIf_UpdateEthIfCtrlStatesAfterActive(ethIfCtrlIdx);
    EthIf_UpdateEthCtrlStatesAfterActive(ethCtrlIdx);
    EthIf_TryUpdateEthTrcvStatesAfterActive(physLayerModeElemsIdx); /*lint !e522 */
    EthIf_TryUpdateEthIfSwtPortGroupStatesAfterActive(physLayerModeElemsIdx); /*lint !e522 */
  }

  return retVal;
} /* EthIf_SetHardwareModeActive() */ /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthIf_DisableEthCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_DisableEthCtrl(
  EthIf_EthCtrlIterType  ethCtrlIdx)
{
  Std_ReturnType retVal = E_OK;

  /* #10 Check if there is only one ACTIVE request for the Ethernet controller left */
  if( EthIf_GetEthCtrlModeCnt(ethCtrlIdx) == ETHIF_DRV_DOWN_REQUEST_MODE_CNT )
  {
    /* #100 Trigger disabling of the Ethernet controller by utilizing the driver */
    EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);
    /* call only when one active mode for the Ethernet Controller is pending */
    /* \trace SPEC-2393587 */
    retVal = EthIf_GetSetCtrlModeOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                           ETH_MODE_DOWN);                                              /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_CSL03 */
  }
  /* #20 Otherwise silently return the request without influencing the hardware */

  return retVal;
} /* EthIf_DisableEthCtrl() */

/**********************************************************************************************************************
 *  EthIf_TryDisableEthTrcv
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_TryDisableEthTrcv(
  EthIf_PhysLayerModeElemsIterType  physLayerModeElemsIdx)
{
  Std_ReturnType retVal = E_OK;

#if (ETHIF_ETHTRCV_USED == STD_ON)                                                                                      /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check if there is a Ethernet transceiver mapped to the EthIf controllers physical layer elements */
  if( EthIf_IsEthTrcvUsedOfPhysLayerModeElems(physLayerModeElemsIdx) == TRUE )
  {
    EthIf_EthTrcvIdxOfPhysLayerModeElemsType ethTrcvIdx = EthIf_GetEthTrcvIdxOfPhysLayerModeElems(physLayerModeElemsIdx);

    /*  #100 Check if there is only one ACTIVE request for the Ethernet transceiver left */
    if( EthIf_GetEthTrcvModeCnt(ethTrcvIdx) == ETHIF_DRV_DOWN_REQUEST_MODE_CNT )
    {
      EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

      /* #1000 Trigger disabling of the Ethernet transceiver by utilizing the driver */
      if( EthIf_GetSetTrcvModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
      {
        retVal = EthIf_GetSetTrcvModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(ethTrcvIdx),
                                                                       ETHTRCV_MODE_DOWN);                              /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
      }
    }
  }
#endif /* ETHIF_ETHTRCV_USED */
  /* #20 Otherwise (if no EthTrcv used or still ACTIVE requests are pending) silently return the request
   *     without influencing the hardware */

  return retVal;
} /* EthIf_TryDisableEthTrcv() */

/**********************************************************************************************************************
 *  EthIf_TryDisableEthIfSwtPortGroup
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_TryDisableEthIfSwtPortGroup(
  EthIf_PhysLayerModeElemsIterType  physLayerModeElemsIdx)
{
  Std_ReturnType retVal = E_OK;

#if (ETHIF_ETHSWT_USED == STD_ON)
  /* #10 Check if there is a EthIf switch port group mapped to the EthIf controllers physical layer elements */
  if( EthIf_IsPortGroupUsedOfPhysLayerModeElems(physLayerModeElemsIdx) == TRUE )
  {
    /* #100 Trigger disabling of the EthIf switch port group */
    EthIf_PortGroupIdxOfPhysLayerModeElemsType portGroupIdx = EthIf_GetPortGroupIdxOfPhysLayerModeElems(physLayerModeElemsIdx);
    retVal = EthIf_SetEthIfSwtPortGroupMode(portGroupIdx, ETHTRCV_MODE_DOWN);
  }
#else
  ETHIF_DUMMY_STATEMENT(physLayerModeElemsIdx); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* ETHIF_ETHSWT_USED */
  /* #20 Otherwise (if no EthIf switch port group used) silently return the request */

  return retVal;
} /* EthIf_TryDisableEthIfSwtPortGroup() */

/**********************************************************************************************************************
 *  EthIf_UpdateEthIfCtrlStatesAfterDown
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_UpdateEthIfCtrlStatesAfterDown(
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx)
{
  /* #10 Enter exclusive area (Reason: Ensure consistency of controller mode and link state information) */
  EthIf_EnterExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Set EthIf controller mode to DOWN and state to UNINIT */
  EthIf_SetEthIfCtrlMode(ethIfCtrlIdx, ETH_MODE_DOWN);                                                                  /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  EthIf_SetEthIfCtrlInitState(ethIfCtrlIdx, ETHIF_ETHIFCTRL_INIT_STATE_UNINIT);                                         /* SBSW_ETHIF_INT_FCT_IDX_PASS */

  /* #30 Check if there was already a link established on the EthIf controller and if so issue a link DOWN by changing
   *     its state to LINK_CHANGE_DOWN */
  if( EthIf_GetEthIfCtrlLinkState(ethIfCtrlIdx) == ETHIF_ETHIFCTRL_LINK_STATE_LINK )
  {
    EthIf_SetEthIfCtrlLinkState(ethIfCtrlIdx, ETHIF_ETHIFCTRL_LINK_STATE_LINK_CHANGE_DOWN);                             /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  }

  /* #40 Leave exclusive area -> processing on elements finished */
  EthIf_ExitExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_UpdateEthIfCtrlStatesAfterDown() */

/**********************************************************************************************************************
 *  EthIf_UpdateEthCtrlStatesAfterDown
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_UpdateEthCtrlStatesAfterDown(
  EthIf_EthCtrlIterType  ethCtrlIdx)
{
  /* #10 Update the amount of ACTIVE requests for the Ethernet Controller */
  EthIf_DecEthCtrlModeCnt(ethCtrlIdx);                                                                                  /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  EthIf_DecEthCtrlInitCnt(ethCtrlIdx);                                                                                  /* SBSW_ETHIF_INT_FCT_IDX_PASS */
} /* EthIf_UpdateEthCtrlStatesAfterDown() */

/**********************************************************************************************************************
 *  EthIf_TryUpdateEthTrcvStatesAfterDown
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_TryUpdateEthTrcvStatesAfterDown(
  EthIf_PhysLayerModeElemsIterType  physLayerInitElemsIdx)
{
#if (ETHIF_ETHTRCV_USED == STD_ON)                                                                                      /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check if there is a Ethernet transceiver mapped to the EthIf controllers physical layer elements */
  if( EthIf_IsEthTrcvUsedOfPhysLayerModeElems(physLayerInitElemsIdx) == TRUE )
  {
    /* #100 Update the amount of ACTIVE request for the Ethernet transceiver */
    EthIf_EthTrcvIdxOfPhysLayerModeElemsType ethTrcvIdx = EthIf_GetEthTrcvIdxOfPhysLayerModeElems(physLayerInitElemsIdx);
    EthIf_DecEthTrcvModeCnt(ethTrcvIdx);                                                                                /* SBSW_ETHIF_COMMON_CSL03 */
    EthIf_DecEthTrcvInitCnt(ethTrcvIdx);                                                                                /* SBSW_ETHIF_COMMON_CSL03 */
  }
#endif /* ETHIF_ETHTRCV_USED */
  /* #20 Otherwise (if no EthTrcv used) silently return */

} /* EthIf_TryUpdateEthTrcvStatesAfterDown() */

/**********************************************************************************************************************
 *  EthIf_TryUpdateEthIfSwtPortGroupStatesAfterDown
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_TryUpdateEthIfSwtPortGroupStatesAfterDown(
  EthIf_PhysLayerModeElemsIterType  physLayerInitElemsIdx)
{

#if (ETHIF_ETHSWT_USED == STD_ON)
  /* #10 Check if there is a EthIf switch port group mapped to the EthIf controllers physical layer elements */
  if( EthIf_IsPortGroupUsedOfPhysLayerModeElems(physLayerInitElemsIdx) == TRUE )
  {
    /* #100 Trigger update of the amount of ACTIVE requests for the EthIf switch port group */
    EthIf_PortGroupIdxOfPhysLayerModeElemsType portGroupIdx = EthIf_GetPortGroupIdxOfPhysLayerModeElems(physLayerInitElemsIdx);
    EthIf_AdjustEthIfSwtPortGroupModeCount(portGroupIdx, ETHTRCV_MODE_DOWN);
  }

  /* #20 Check if there is a EthIf switch mapped to the EthIf controllers phyiscal layer elements */
  if( EthIf_IsEthSwtIndUsedOfPhysLayerInitElems(physLayerInitElemsIdx) == TRUE )
  {
    /* #200 Update the amount of ACTIVE requests for each EthIf switch mapped */
    EthIf_EthSwtIndIterType indIdx;

    for( indIdx = EthIf_GetEthSwtIndStartIdxOfPhysLayerInitElems(physLayerInitElemsIdx);
         indIdx < EthIf_GetEthSwtIndEndIdxOfPhysLayerInitElems(physLayerInitElemsIdx);
         indIdx++ )
    {
      EthIf_EthSwtIndType ethSwtIdx = EthIf_GetEthSwtInd(indIdx);
      EthIf_DecEthSwtInitCnt(ethSwtIdx);                                                                                /* SBSW_ETHIF_COMMON_CSL03 */
    }
  }
#else
  ETHIF_DUMMY_STATEMENT(physLayerInitElemsIdx); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* ETHIF_ETHSWT_USED */
  /* #30 Otherwise (if no EthIf switch port group used) silently return */

} /* EthIf_TryUpdateEthIfSwtPortGroupStatesAfterDown() */

/**********************************************************************************************************************
 *  EthIf_SetHardwareModeDown
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_SetHardwareModeDown(
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal;
  EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(ethIfCtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger disabeling of the Ethernet controller */
  retVal = EthIf_DisableEthCtrl(ethCtrlIdx);

  /* #20 Check if disabeling the Ethernet controller was successful */
  if( retVal == E_OK )
  {
    EthIf_PhysLayerModeElemsIdxOfEthIfCtrlType physLayerModeElemsIdx = EthIf_GetPhysLayerModeElemsIdxOfEthIfCtrl(ethIfCtrlIdx);

    /* #200 Trigger disableling of Ethernet transceiver and EthIf Switch Port Group */
    retVal  = EthIf_TryDisableEthTrcv(physLayerModeElemsIdx);
    retVal |= EthIf_TryDisableEthIfSwtPortGroup(physLayerModeElemsIdx); /* PRQA S 2985 */ /* MD_EthIf_2985 */
  }

  /* #30 Check if disabling of the hardware was successful */
  if( retVal == E_OK )
  {
    EthIf_PhysLayerInitElemsIdxOfEthIfCtrlType physLayerInitElemsIdx = EthIf_GetPhysLayerInitElemsIdxOfEthIfCtrl(ethIfCtrlIdx);

    /* #300 Trigger adaption of the related hardware intialization and mode states and counters */
    EthIf_UpdateEthIfCtrlStatesAfterDown(ethIfCtrlIdx);
    EthIf_UpdateEthCtrlStatesAfterDown(ethCtrlIdx);
    EthIf_TryUpdateEthTrcvStatesAfterDown(physLayerInitElemsIdx); /*lint !e522 */
    EthIf_TryUpdateEthIfSwtPortGroupStatesAfterDown(physLayerInitElemsIdx); /*lint !e522 */
  }

  return retVal;
} /* EthIf_SetHardwareModeDown() */

#if ( ETHIF_ETHSWT_USED == STD_ON )
/**********************************************************************************************************************
 *  EthIf_SetEthIfSwtPortGroupMode
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
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_SetEthIfSwtPortGroupMode(
  EthIf_PortGroupIterType  portGroupIdx,
  EthTrcv_ModeType         trgtMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if ethSwtPortGroup has semantic type link info */
  if( EthIf_GetSemanticOfPortGroup(portGroupIdx) == ETHIF_PORTGROUP_SEMANTIC_LINK_INFO_SEMANTICOFPORTGROUP )
  {
    retVal = E_OK;
  }
  /* #20 Check if ethSwtPortGroup has semantic type control or independent */
  else if( (EthIf_GetSemanticOfPortGroup(portGroupIdx) == ETHIF_PORTGROUP_SEMANTIC_CONTROL_SEMANTICOFPORTGROUP) ||
           (EthIf_GetSemanticOfPortGroup(portGroupIdx) == ETHIF_PORTGROUP_SEMANTIC_INDEPENDENT_SEMANTICOFPORTGROUP) )
  {
    /* #200 Check if action for ETHTRCV_MODE_ACTIVE should be done */
    if( trgtMode == ETHTRCV_MODE_ACTIVE )
    {
      EthIf_EthSwtPortIndIterType indIdx;

      /* #2000 Switch port mode to ETHTRCV_MODE_ACTIVE for each still inactive port of the ethSwtPortGroup */
      for( indIdx = EthIf_GetEthSwtPortIndStartIdxOfPortGroup(portGroupIdx);
           indIdx < EthIf_GetEthSwtPortIndEndIdxOfPortGroup(portGroupIdx);
           indIdx++ )
      {
        EthIf_EthSwtPortIndType portIdx = EthIf_GetEthSwtPortInd(indIdx);

        if( EthIf_GetEthSwtPortModeCnt(portIdx) == ETHIF_MIN_ETHSWTPORTMODECNT )
        {
          EthIf_EthSwtIdxOfEthSwtPortType ethSwtIdx = EthIf_GetEthSwtIdxOfEthSwtPort(portIdx);
          EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvApiIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(ethSwtIdx);

          retVal = EthIf_GetSetSwtPortModeOfEthSwtDrvApi(ethSwtDrvApiIdx)((uint8)EthIf_GetSnvOfEthSwt(ethSwtIdx),
                                                                          (uint8)EthIf_GetSnvOfEthSwtPort(portIdx),
                                                                          ETHTRCV_MODE_ACTIVE);                         /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_CSL03 */
        }
        else
        {
          retVal = E_OK;
        }

        if ( retVal != E_OK )
        {
          break;
        }
      }

      /* #2010 If switching of port mode was successful and port group semantic is independent set port group mode to ACTIVE */
      if( (retVal == E_OK) &&
          (EthIf_GetSemanticOfPortGroup(portGroupIdx) == ETHIF_PORTGROUP_SEMANTIC_INDEPENDENT_SEMANTICOFPORTGROUP) )
      {
        EthIf_SetPortGroupMode(portGroupIdx, ETHTRCV_MODE_ACTIVE);                                                      /* SBSW_ETHIF_INT_FCT_IDX_PASS */
      }
    }
    /* #300 Check if action for ETHTRCV_MODE_DOWN should be done */
    else
    {
      EthIf_EthSwtPortIndIterType indIdx;

      /* #3000 Switch port mode to ETHTRCV_MODE_DOWN for each still active port of the ethSwtPortGroup */
      for( indIdx = EthIf_GetEthSwtPortIndStartIdxOfPortGroup(portGroupIdx);
           indIdx < EthIf_GetEthSwtPortIndEndIdxOfPortGroup(portGroupIdx);
           indIdx++ )
      {
        EthIf_EthSwtPortIndType portIdx = EthIf_GetEthSwtPortInd(indIdx);

        if( EthIf_GetEthSwtPortModeCnt(portIdx) == ETHIF_DRV_DOWN_REQUEST_MODE_CNT )
        {
          EthIf_EthSwtIdxOfEthSwtPortType ethSwtIdx = EthIf_GetEthSwtIdxOfEthSwtPort(portIdx);
          EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvApiIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(ethSwtIdx);

          retVal = EthIf_GetSetSwtPortModeOfEthSwtDrvApi(ethSwtDrvApiIdx)((uint8)EthIf_GetSnvOfEthSwt(ethSwtIdx),
                                                                          (uint8)EthIf_GetSnvOfEthSwtPort(portIdx),
                                                                          ETHTRCV_MODE_DOWN);                           /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_CSL03 */
        }
        else
        {
          retVal = E_OK;
        }

        if ( retVal != E_OK )
        {
          break;
        }
      }

      /* #3010 If switching of port mode was successful and port group semantic is independent set port group mode to DOWN */
      if( (retVal == E_OK) &&
          (EthIf_GetSemanticOfPortGroup(portGroupIdx) == ETHIF_PORTGROUP_SEMANTIC_INDEPENDENT_SEMANTICOFPORTGROUP) )
      {
        /* #30110 Enter exclusive area (Reason: Ensure consistency of controller mode and link state information) */
        EthIf_EnterExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */

        /* #30120 Update mode and link state information */
        EthIf_SetPortGroupMode(portGroupIdx, ETHTRCV_MODE_DOWN);                                                        /* SBSW_ETHIF_INT_FCT_IDX_PASS */

        if( EthIf_GetPortGroupLinkState(portGroupIdx) == ETHIF_PORTGROUP_LINK_STATE_LINK )
        {
          EthIf_SetPortGroupLinkState(portGroupIdx, ETHIF_PORTGROUP_LINK_STATE_LINK_CHANGE_DOWN);                       /* SBSW_ETHIF_INT_FCT_IDX_PASS */
        }

        /* #30130 Leave exclusive area -> processing on elements finished */
        EthIf_ExitExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */
      }
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /* EthIf_SetEthIfSwtPortGroupMode() */ /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthIf_AdjustEthIfSwtPortGroupModeCount
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
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_AdjustEthIfSwtPortGroupModeCount(
  EthIf_PortGroupIterType  portGroupIdx,
  EthTrcv_ModeType         trgtMode)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of mode and link state information) */
  EthIf_EnterExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Check if EthIf switch port group is of semantic type control or independent */
  if( (EthIf_GetSemanticOfPortGroup(portGroupIdx) == ETHIF_PORTGROUP_SEMANTIC_CONTROL_SEMANTICOFPORTGROUP) ||
      (EthIf_GetSemanticOfPortGroup(portGroupIdx) == ETHIF_PORTGROUP_SEMANTIC_INDEPENDENT_SEMANTICOFPORTGROUP) )
  {
    /* #210 Check if action for ETHTRCV_MODE_ACTIVE should be done */
    if( trgtMode == ETHTRCV_MODE_ACTIVE )
    {
      EthIf_EthSwtPortIndIterType indIdx;

      /* #2100 Increment mode counter of each port in the ethSwtPortGroup */
      for( indIdx = EthIf_GetEthSwtPortIndStartIdxOfPortGroup(portGroupIdx);
           indIdx < EthIf_GetEthSwtPortIndEndIdxOfPortGroup(portGroupIdx);
           indIdx++ )
      {
        EthIf_EthSwtPortIndType portIdx = EthIf_GetEthSwtPortInd(indIdx);

        EthIf_IncEthSwtPortModeCnt(portIdx);                                                                            /* SBSW_ETHIF_COMMON_CSL03 */
      }
    }
    /* #220 Check if action for ETHTRCV_MODE_DOWN should be done */
    else
    {
      EthIf_EthSwtPortIndIterType indIdx;

      /* #2200 Decrement mode counter of each port in the ethSwtPortGroup */
      for( indIdx = EthIf_GetEthSwtPortIndStartIdxOfPortGroup(portGroupIdx);
           indIdx < EthIf_GetEthSwtPortIndEndIdxOfPortGroup(portGroupIdx);
           indIdx++ )
      {
        EthIf_EthSwtPortIndType portIdx = EthIf_GetEthSwtPortInd(indIdx);

        EthIf_DecEthSwtPortModeCnt(portIdx);                                                                            /* SBSW_ETHIF_COMMON_CSL03 */
      }
    }
  }

  /* #30 Leave exclusive area -> processing on elements finished */
  EthIf_ExitExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_AdjustEthIfSwtPortGroupModeCount() */
#endif /* ETHIF_ETHSWT_USED */

/**********************************************************************************************************************
 *  EthIf_TryTakeInitSemaphore
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(boolean, ETHIF_MODE_INLINE_CODE) EthIf_TryTakeInitSemaphore( void )
{
  boolean isTaken = FALSE;

  /* #10 Enter exclusive area (Reason: Check and take semaphore that protects the initialization from executing
   *                                   multiple hardware initialization processes in parallel) */
  EthIf_EnterExclusiveArea(CTRL_INIT); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Take initialization protection semaphore if not taken in other context */
  if( EthIf_IsInitLocked() == FALSE )
  {
    EthIf_SetInitLocked(TRUE);                                                                                          /* SBSW_ETHIF_COMMON_CFG_PTR_INT_FCT_PREV_MODULE_INIT_CHECK */
    isTaken = TRUE;
  }

  /* #30 Leave exclusive area */
  EthIf_ExitExclusiveArea(CTRL_INIT); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return isTaken;
} /* EthIf_TryTakeInitSemaphore() */

/**********************************************************************************************************************
 *  EthIf_ReleaseInitSemaphore
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_ReleaseInitSemaphore( void )
{
  /* #10 Return initialization protection semaphore */
  EthIf_SetInitLocked(FALSE);                                                                                           /* SBSW_ETHIF_COMMON_CFG_PTR_INT_FCT_PREV_MODULE_INIT_CHECK */
} /* EthIf_ReleaseInitSemaphore() */

/**********************************************************************************************************************
 *  EthIf_TryTakeModeChangeSemaphore
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(boolean, ETHIF_MODE_INLINE_CODE) EthIf_TryTakeModeChangeSemaphore( void )
{
  boolean isTaken = FALSE;

  /* #10 Enter exclusive area (Reason: Check and take semaphore that protects the mode change from executing
   *                                   multiple hardware mode change processes in parallel) */
  EthIf_EnterExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Take mode change protection semaphore if not taken in other context */
  if( EthIf_IsModeChangeLocked() == FALSE )
  {
    EthIf_SetModeChangeLocked(TRUE);                                                                                    /* SBSW_ETHIF_COMMON_CFG_PTR_INT_FCT_PREV_MODULE_INIT_CHECK */
    isTaken = TRUE;
  }

  /* #30 Leave exclusive area */
  EthIf_ExitExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return isTaken;
} /* EthIf_TryTakeModeChangeSemaphore() */

/**********************************************************************************************************************
 *  EthIf_ReleaseModeChangeSemaphore
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_ReleaseModeChangeSemaphore( void )
{
  /* #10 Return mode change protection semaphore */
  EthIf_SetModeChangeLocked(FALSE);                                                                                     /* SBSW_ETHIF_COMMON_CFG_PTR_INT_FCT_PREV_MODULE_INIT_CHECK */
} /* EthIf_ReleaseModeChangeSemaphore() */

/**********************************************************************************************************************
 *  EthIf_InitEthCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_InitEthCtrl(
   EthIf_EthCtrlIterType ethCtrlIdx,
   uint8                 cfgIdx)
{
  Std_ReturnType retVal = E_OK;

  /* #10 Check if Ethernet controller isn't already initialized */
  if( EthIf_GetEthCtrlInitCnt(ethCtrlIdx) == ETHIF_MIN_ETHCTRLINITCNT )
  {
    /* #100 Initialize Ethernet controller if needed by utilizing the Ethernet driver */
    EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);
    /* \trace SPEC-2393582 */
    retVal = EthIf_GetCtrlInitOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                        cfgIdx);                                                        /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_CSL03 */
  }
  /* #20 Otherwise silently return the request without influencing the hardware */

  return retVal;
} /* EthIf_InitEthCtrl() */

/**********************************************************************************************************************
 *  EthIf_TryInitEthTrcv
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_TryInitEthTrcv(
  EthIf_PhysLayerInitElemsIterType physLayerInitElemsIdx,
  uint8                            cfgIdx)
{
  Std_ReturnType retVal = E_OK;

#if (ETHIF_ETHTRCV_USED == STD_ON)                                                                                      /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check if there is a Ethernet transceiver mapped to the EthIf controllers physical layer elements */
  if( EthIf_IsEthTrcvUsedOfPhysLayerInitElems(physLayerInitElemsIdx) == TRUE )
  {
    EthIf_EthTrcvIdxOfPhysLayerInitElemsType ethTrcvIdx = EthIf_GetEthTrcvIdxOfPhysLayerInitElems(physLayerInitElemsIdx);

    /* #100 Check if the Ethernet transceiver isn't initialized yet */
    if( EthIf_GetEthTrcvInitCnt(ethTrcvIdx) == ETHIF_MIN_ETHTRCVINITCNT )
    {
      /* #1000 Trigger initialization of the Ethernet transceiver by utilizing the driver */
      EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

      retVal = EthIf_GetTrcvInitOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(ethTrcvIdx),
                                                                  cfgIdx);                                              /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_CSL03 */
    }
  }
  /* #20 Otherwise (if no EthTrcv used or already initialized) silently return the request without influencing the
   *     hardware */
#endif /* ETHIF_ETHTRCV_USED */

  return retVal;
} /* EthIf_TryInitEthTrcv() */

/**********************************************************************************************************************
 *  EthIf_TryInitEthSwt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_TryInitEthSwt(
  EthIf_PhysLayerInitElemsIterType physLayerInitElemsIdx)
{
  Std_ReturnType retVal = E_OK;

#if (ETHIF_ETHSWT_USED == STD_ON)
  /* #10 Check if there are Ethernet switches mapped to the EthIf controllers physical layer elements */
  if( EthIf_IsEthSwtIndUsedOfPhysLayerInitElems(physLayerInitElemsIdx) == TRUE )
  {
    EthIf_EthSwtIterType indIdx;

    for( indIdx = EthIf_GetEthSwtIndStartIdxOfPhysLayerInitElems(physLayerInitElemsIdx);
         indIdx < EthIf_GetEthSwtIndEndIdxOfPhysLayerInitElems(physLayerInitElemsIdx);
         indIdx++ )
    {
      EthIf_EthSwtIndType ethSwtIdx = EthIf_GetEthSwtInd(indIdx);
      /* #100 For each Ethernet switch check if it isn't initialized yet */
      if( EthIf_GetEthSwtInitCnt(ethSwtIdx) == ETHIF_MIN_ETHSWTINITCNT )
      {
        /* #1000 Trigger initialization of the Ethernet switch by utilizing the driver */
        EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvApiIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(ethSwtIdx);

        retVal |= EthIf_GetSwtInitOfEthSwtDrvApi(ethSwtDrvApiIdx)((uint8)EthIf_GetSnvOfEthSwt(ethSwtIdx));              /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_CSL03 */
      }
    }
  }
#else
  ETHIF_DUMMY_STATEMENT(physLayerInitElemsIdx); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* ETHIF_ETHSWT_USED */
  /* #20 Otherwise (if no EthSwt used or already initialized) silently return the request without influencing the
   *     hardware */

  return retVal;
} /* EthIf_TryInitEthSwt() */

/**********************************************************************************************************************
 *  EthIf_UpdateEthIfCtrlStatesAfterInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_UpdateEthIfCtrlStatesAfterInit(
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx)
{
  /* #10 Update EthIf controller init state */
  EthIf_SetEthIfCtrlInitState(ethIfCtrlIdx, ETHIF_ETHIFCTRL_INIT_STATE_INIT);                                           /* SBSW_ETHIF_INT_FCT_IDX_PASS */

  /* #20 Enter exclusive area (Reason: Pre-condition for calling EthIf_ClearTxStats()/EthIf_ClearRxStats()/
   * EthIf_ClearMeasurementData()) */
  EthIf_EnterExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #30 Clear statistic counters */
  EthIf_ClearTxStats(ethIfCtrlIdx);
  EthIf_ClearRxStats(ethIfCtrlIdx);
#if ( ETHIF_MEASUREMENT_DATA_SUPPORT == STD_ON )
  EthIf_ClearMeasurementData();
#endif /* ETHIF_MEASUREMENT_DATA_SUPPORT */

  /* #40 Leave exclusive area */
  EthIf_ExitExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_UpdateEthIfCtrlStatesAfterInit() */

/**********************************************************************************************************************
 *  EthIf_UpdateEthCtrlStatesAfterInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_UpdateEthCtrlStatesAfterInit(
  EthIf_EthCtrlIterType ethCtrlIdx)
{
  /* #10 Increase Eth Controller init count */
  EthIf_IncEthCtrlInitCnt(ethCtrlIdx);                                                                                  /* SBSW_ETHIF_INT_FCT_IDX_PASS */
} /* EthIf_UpdateEthCtrlStatesAfterInit() */

/**********************************************************************************************************************
 *  EthIf_TryUpdateEthTrcvStatesAfterInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_TryUpdateEthTrcvStatesAfterInit(
  EthIf_PhysLayerInitElemsIterType physLayerInitElemsIdx)
{
  /* increase all physical layer elements init count */
#if (ETHIF_ETHTRCV_USED == STD_ON)                                                                                      /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check if there is a Ethernet transceiver mapped to the EthIf controllers physical layer elements */
  if( EthIf_IsEthTrcvUsedOfPhysLayerInitElems(physLayerInitElemsIdx) == TRUE )
  {
    /* #100 Increase Ethernet transceiver init count */
    EthIf_EthTrcvIdxOfPhysLayerInitElemsType ethTrcvIdx = EthIf_GetEthTrcvIdxOfPhysLayerInitElems(physLayerInitElemsIdx);

    EthIf_IncEthTrcvInitCnt(ethTrcvIdx);                                                                                /* SBSW_ETHIF_COMMON_CSL03 */
  }
#endif /* ETHIF_ETHTRCV_USED */
} /* EthIf_TryUpdateEthTrcvStatesAfterInit() */

/**********************************************************************************************************************
 *  EthIf_TryUpdateEthSwtStatesAfterInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(void, ETHIF_MODE_INLINE_CODE) EthIf_TryUpdateEthSwtStatesAfterInit(
  EthIf_PhysLayerInitElemsIterType physLayerInitElemsIdx)
{
#if (ETHIF_ETHSWT_USED == STD_ON)
  /* #10 Check if there are Ethernet switches mapped to the EthIf controllers physical layer elements */
  if( EthIf_IsEthSwtIndUsedOfPhysLayerInitElems(physLayerInitElemsIdx) == TRUE )
  {
    EthIf_EthSwtIterType indIdx;

    /* #100 Increase init count for each Ethernet switch */
    for( indIdx = EthIf_GetEthSwtIndStartIdxOfPhysLayerInitElems(physLayerInitElemsIdx);
         indIdx < EthIf_GetEthSwtIndEndIdxOfPhysLayerInitElems(physLayerInitElemsIdx);
         indIdx++ )
    {
      EthIf_EthSwtIndType ethSwtIdx = EthIf_GetEthSwtInd(indIdx);
      EthIf_IncEthSwtInitCnt(ethSwtIdx);                                                                                /* SBSW_ETHIF_COMMON_CSL03 */
    }
  }
#else
  ETHIF_DUMMY_STATEMENT(physLayerInitElemsIdx); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* ETHIF_ETHSWT_USED */
} /* EthIf_TryUpdateEthSwtStatesAfterInit() */

/**********************************************************************************************************************
 *  EthIf_Internal_ControllerInit
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
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_Internal_ControllerInit(
  uint8  ethIfCtrlIdx,
  uint8  cfgIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  boolean isInitLocked = EthIf_TryTakeInitSemaphore();

  /* #10 Check if parallel initialization protection semaphore could be taken */
  if( isInitLocked == TRUE )
  {
    /* #100 Check if EthIf controller isn't initialized yet */
    if( EthIf_GetEthIfCtrlInitState(ethIfCtrlIdx) == ETHIF_ETHIFCTRL_INIT_STATE_UNINIT )
    {
      EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(ethIfCtrlIdx);

      /* #1000 Trigger Ethernet controller initialization */
      retVal = EthIf_InitEthCtrl(ethCtrlIdx, cfgIdx);

      if( retVal == E_OK )
      {
        /* #1010 Trigger Ethernet transceiver and Ethernet switch initialization */
        EthIf_PhysLayerInitElemsIdxOfEthIfCtrlType physLayerInitElemsIdx = EthIf_GetPhysLayerInitElemsIdxOfEthIfCtrl(ethIfCtrlIdx);

        retVal  = EthIf_TryInitEthTrcv(physLayerInitElemsIdx, cfgIdx);
        retVal |= EthIf_TryInitEthSwt(physLayerInitElemsIdx); /* PRQA S 2985 */ /* MD_EthIf_2985 */
      }
    }
    else
    {
      retVal = E_OK;
    }

    if( retVal == E_OK )
    {
      /* #1020 Update all states related to the EthIf controller and the hardware it abstracts */
      EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(ethIfCtrlIdx);
      EthIf_PhysLayerInitElemsIdxOfEthIfCtrlType physLayerInitElemsIdx = EthIf_GetPhysLayerInitElemsIdxOfEthIfCtrl(ethIfCtrlIdx);

      EthIf_UpdateEthIfCtrlStatesAfterInit(ethIfCtrlIdx);
      EthIf_UpdateEthCtrlStatesAfterInit(ethCtrlIdx);
      EthIf_TryUpdateEthTrcvStatesAfterInit(physLayerInitElemsIdx); /*lint !e522 */
      EthIf_TryUpdateEthSwtStatesAfterInit(physLayerInitElemsIdx); /*lint !e522 */
    }

    /* #110 Release parallel initialization protection semaphore */
    EthIf_ReleaseInitSemaphore();
  }

  return retVal;
} /* EthIf_Internal_ControllerInit() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthIf_Internal_SetControllerMode
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
 *
 */
ETHIF_MODE_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MODE_INLINE_CODE) EthIf_Internal_SetControllerMode(
  uint8         ethIfCtrlIdx,
  Eth_ModeType  ctrlMode)
{
  Std_ReturnType retVal = E_NOT_OK;
  boolean isModeChangeLocked = EthIf_TryTakeModeChangeSemaphore();

  /* #10 Check if parallel mode change protection semaphore could be taken */
  if( isModeChangeLocked == TRUE )
  {
    /* #100 Check if EthIf controller is initialized */
    if( EthIf_GetEthIfCtrlInitState(ethIfCtrlIdx) == ETHIF_ETHIFCTRL_INIT_STATE_INIT )
    {
      /* #1000 Check if there is a mode change request from DOWN to ACTIVE and if so trigger the change */
      if( (ctrlMode == ETH_MODE_ACTIVE) &&
          (EthIf_GetEthIfCtrlMode(ethIfCtrlIdx) == ETH_MODE_DOWN) )
      {
        retVal = EthIf_SetHardwareModeActive(ethIfCtrlIdx);
#if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_GATEWAY )                                                   /* COV_ETHIF_QM_FEAT_CHECK_ON */
        EthIf_ManipulatePromiscuousMode(ethIfCtrlIdx, ETH_ADD_TO_FILTER);
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */
      }
      /* #1010 Otherwise check if there is a mode change request from ACTIVE to DOWN and if so trigger the change */
      else if( (ctrlMode == ETH_MODE_DOWN) &&
               (EthIf_GetEthIfCtrlMode(ethIfCtrlIdx) == ETH_MODE_ACTIVE) )
      {
#if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_GATEWAY )                                                   /* COV_ETHIF_QM_FEAT_CHECK_ON */
        EthIf_ManipulatePromiscuousMode(ethIfCtrlIdx, ETH_REMOVE_FROM_FILTER);
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */
        retVal = EthIf_SetHardwareModeDown(ethIfCtrlIdx);
      }
      /* #1020 Otherwise (request wouldn't lead to a mode change) silently return the request */
      else
      {
        retVal = E_OK;
      }
    }

    /* #110 Release parallel mode change protection semaphore */
    EthIf_ReleaseModeChangeSemaphore();
  }
  /* #20 Otherwise (if semaphore couldn't be taken or EthIf controller isn't initialized) reject mode change request */

  /* #30 Check if there was a mode change to down and if so immediately process a link state change for the
   *     EthIf controller */
  if( (retVal == E_OK) &&
      (ctrlMode == ETH_MODE_DOWN) )
  {
    EthIf_ProcessLinkStateChange(ethIfCtrlIdx);
  }

  return retVal;
} /* EthIf_Internal_SetControllerMode() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_ControllerInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_ControllerInit(
  uint8  CtrlIdx,
  uint8  CfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal;
  uint8           errorId = ETHIF_E_NO_ERROR;

#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  retVal = E_NOT_OK;
#endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393583 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    /* \trace SPEC-2393584 */
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else
#endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* #30 Trigger EthIf controller initialization */
    retVal = EthIf_Internal_ControllerInit(CtrlIdx, CfgIdx);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_CONTROLLER_INIT, errorId);
  }
#else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* EthIf_ControllerInit() */ /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthIf_SetControllerMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetControllerMode(
  uint8         CtrlIdx,
  Eth_ModeType  CtrlMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal;
  uint8           errorId = ETHIF_E_NO_ERROR;

#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  retVal = E_NOT_OK;
#endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393588 */
    /* \trace SPEC-2393590 */
    /* \trace SPEC-2393604 */
    /* \trace SPEC-2393606 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    /* \trace SPEC-2393589 */
    /* \trace SPEC-2393605 */
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( (CtrlMode != ETH_MODE_ACTIVE) &&
           (CtrlMode != ETH_MODE_DOWN)      )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( EthIf_IsModeRequestPossible(CtrlIdx, CtrlMode) == FALSE )
  {
    errorId = ETHIF_E_INV_STATE;
  }
  else
#endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* #30 Trigger EthIf controller mode change */
    retVal = EthIf_Internal_SetControllerMode(CtrlIdx, CtrlMode);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SET_CONTROLLER_MODE, errorId);
  }
#else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* EthIf_SetControllerMode() */ /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthIf_GetControllerMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetControllerMode(
        uint8                                     CtrlIdx,
  P2VAR(Eth_ModeType, AUTOMATIC, ETHIF_APPL_VAR)  CtrlModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal;
  uint8           errorId = ETHIF_E_NO_ERROR;

#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  retVal = E_NOT_OK;
#endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393593 */
    /* \trace SPEC-2393596 */
    /* \trace SPEC-2393609 */
    /* \trace SPEC-2393612 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    /* \trace SPEC-2393594 */
    /* \trace SPEC-2393610 */
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( CtrlModePtr == NULL_PTR)
  {
    /* \trace SPEC-2393595 */
    /* \trace SPEC-2393611 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
#endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Retrieve the current EthIf controller mode and pass it to the caller */
    /* \trace SPEC-2393592 */
    /* \trace SPEC-2393608 */
    *CtrlModePtr = EthIf_GetEthIfCtrlMode(CtrlIdx);                                                                     /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_CONTROLLER_MODE, errorId);
  }
#else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* EthIf_GetControllerMode() */

#if ( ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  EthIf_SwitchPortGroupRequestMode
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
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchPortGroupRequestMode(
  EthIf_SwitchPortGroupIdxType PortGroupIdx,
  EthTrcv_ModeType PortMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  retVal = E_NOT_OK;
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393861 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( PortGroupIdx >= EthIf_GetSizeOfPortGroup() )
  {
    errorId = ETHIF_E_INV_PORT_GROUP_IDX;
  }
  else if ( EthIf_GetSemanticOfPortGroup(PortGroupIdx) != ETHIF_PORTGROUP_SEMANTIC_INDEPENDENT_SEMANTICOFPORTGROUP )
  {
    errorId = ETHIF_E_INV_PORT_GROUP_IDX;
  }
  else if( (PortMode != ETHTRCV_MODE_DOWN) &&
           (PortMode != ETHTRCV_MODE_ACTIVE) )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( EthIf_IsModeRequestPossibleForEthIfSwtPortGroup(PortGroupIdx, PortMode) == FALSE )
  {
    errorId = ETHIF_E_INV_STATE;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if a mode change to ACTIVE or DOWN has to be performed */
    if ( PortMode != EthIf_GetPortGroupMode(PortGroupIdx) )
    {
      /* #300 Switch mode of ports in Port Group with related PortGroupIdx */
      retVal = EthIf_SetEthIfSwtPortGroupMode(PortGroupIdx, PortMode);

      /* #310 Check if switching of mode for the Port Group Ports was successful */
      if ( retVal == E_OK )
      {
        /* #3000 Adjusting mode counter values of the ports in the Port Group */
        EthIf_AdjustEthIfSwtPortGroupModeCount(PortGroupIdx, PortMode);

        /* #3100 Check if requested mode was DOWN */
        if( PortMode == ETHTRCV_MODE_DOWN )
        {
          /* #31000 Immediately propagate the link state change to DOWN the upper layers */
          EthIf_ProcessSwtPortGroupLinkStateChange(PortGroupIdx);
        }
      }
    }
    else
    {
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SWITCH_PORT_GROUP_REQUEST_MODE, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_SwitchPortGroupRequestMode() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Mode.c
 *********************************************************************************************************************/

