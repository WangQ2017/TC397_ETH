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
/*!        \file  EthIf_Link_Int.h
 *        \brief  EthIf Link internal header file
 *
 *      \details  Provides access to types/functions/data of the sub-module Link of EthIf only to be used internally,
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

#if !defined (ETHIF_LINK_INT_H)
# define ETHIF_LINK_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_Link_Types_Int.h"

# include "EthIf.h"      /* access to DET error IDs */
# include "EthIf_Int.h"  /* access to components/utils shared with all EthIf modules */

/*********************************************************************************************************
 * Predefined file includes based on usage of other components/sub-modules within this sub-module
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to <User> resolved through EthIf_Lcfg.h -> no include needed */
# include "EthSM.h"
# if( ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT == STD_ON )
#  include "BswM.h"
# endif

/*********************************************************************************************************
 * Predefined file includes based on usage of this sub-module by other components/sub-modules
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to EthTrcv resolved through EthIf_Lcfg.h -> no include needed */
/* Dependency to EthSwt resolved through EthIf_Lcfg.h -> no include needed */
# include "EthIf_Mode_Types_Int.h"
# include "EthIf_Tx_Types_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETHIF_LINK_INT_LOCAL)                                                                                    /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_LINK_INT_LOCAL static
# endif

# if !defined (ETHIF_LINK_INT_LOCAL_INLINE)                                                                             /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_LINK_INT_LOCAL_INLINE LOCAL_INLINE
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
 *  EthIf_ReportLinkStateChange
 *********************************************************************************************************************/
/*! \brief          Report a link state change to the users
 *  \details        This function reports the passed link state for an EthIf controller to the EthIf users.
 *  \param[in]      ethIfCtrlIdx  EthIf controller the link change shall be reported for
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      linkState     Link state to be reported
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_LINK_INT_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_ReportLinkStateChange( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx,
  EthTrcv_LinkStateType    linkState);

/**********************************************************************************************************************
 *  EthIf_ProcessLinkStateChange
 *********************************************************************************************************************/
/*! \brief          Processes the link state change for EthIf controller
 *  \details        This function checks for a link state change on the EthIf controller and notifies the EthIf users
 *                  registered for a link state change notification about the change.
 *  \param[in]      ethIfCtrlIdx  EthIf controller the link state change shall be processed for
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_LINK_INT_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_ProcessLinkStateChange( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx);

# if ( ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  EthIf_ProcessSwtPortGroupLinkStateChange
 *********************************************************************************************************************/
/*! \brief          Processes the link state changes for a EthIf switch port group
 *  \details        This function checks for a link state change on the EthIf switch port group and notifies the BswM
 *                  about the change.
 *  \param[in]      portGroupIdx  EthIf switch port group the link state change shall be processed for
 *                                [range: portGroupIdx < EthIf_GetSizeOfPortGroup()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_LINK_INT_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_ProcessSwtPortGroupLinkStateChange( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_PortGroupIterType  portGroupIdx);
# endif /* ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT */

# if !defined(ETHIF_UNIT_TEST)                                                                                          /* COV_ETHIF_UNIT_TEST */
/**********************************************************************************************************************
 *  EthIf_ReportLinkStateChange
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_LINK_INT_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_ReportLinkStateChange( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx,
  EthTrcv_LinkStateType    linkState)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_LinkStateChgIndicationsIterType linkChgCbkIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Report link state change to EthSM if state changes to ACTIVE */
  if( linkState == ETHTRCV_LINK_STATE_ACTIVE )
  {
    EthSM_VTrcvLinkStateChg((uint8)EthIf_GetSnvOfEthIfCtrl(ethIfCtrlIdx), linkState);
  }

  /* #20 Report link state change to users */
  for( linkChgCbkIdx = 0;
       linkChgCbkIdx < EthIf_GetSizeOfLinkStateChgIndications();
       linkChgCbkIdx++)
  {
    EthIf_GetLinkStateChgIndications(linkChgCbkIdx)((uint8)EthIf_GetSnvOfEthIfCtrl(ethIfCtrlIdx), linkState);           /* SBSW_ETHIF_USERAPI_FCT_PTR_CSL01 */
  }

  /* #30 Report link state change to EthSM if state changes to DOWN */
  if( linkState == ETHTRCV_LINK_STATE_DOWN )
  {
    EthSM_VTrcvLinkStateChg((uint8)EthIf_GetSnvOfEthIfCtrl(ethIfCtrlIdx), linkState);
  }
} /* EthIf_ReportLinkStateChange() */

/**********************************************************************************************************************
 *  EthIf_ProcessLinkStateChange
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
 */
ETHIF_LINK_INT_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_ProcessLinkStateChange( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of controller mode and link state information) */
  EthIf_EnterExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Check if a link state change to link active occurred on the EthIf Controller */
  if( EthIf_GetEthIfCtrlLinkState(ethIfCtrlIdx) == ETHIF_ETHIFCTRL_LINK_STATE_LINK_CHANGE_UP )
  {
    /* #200 Issue a link up for the EthIf Controller */
    EthIf_SetEthIfCtrlLinkState(ethIfCtrlIdx, ETHIF_ETHIFCTRL_LINK_STATE_LINK);                                         /* SBSW_ETHIF_INT_FCT_IDX_PASS */
    EthIf_ReportLinkStateChange(ethIfCtrlIdx, ETHTRCV_LINK_STATE_ACTIVE);
  }
  /* #30 Check if a link state change to link down occurred on the EthIf Controller */
  else if( EthIf_GetEthIfCtrlLinkState(ethIfCtrlIdx) == ETHIF_ETHIFCTRL_LINK_STATE_LINK_CHANGE_DOWN )
  {
    /* #300 Issue a link down for the EthIf Controller */
    EthIf_SetEthIfCtrlLinkState(ethIfCtrlIdx, ETHIF_ETHIFCTRL_LINK_STATE_NO_LINK);                                      /* SBSW_ETHIF_INT_FCT_IDX_PASS */
    EthIf_ReportLinkStateChange(ethIfCtrlIdx, ETHTRCV_LINK_STATE_DOWN);
  }
  else
  {
    /* no link change occurred */
  }

  /* #40 Leave exclusive area -> processing on elements finished */
  EthIf_ExitExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_ProcessLinkStateChange() */

#  if ( ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  EthIf_ProcessSwtPortGroupLinkStateChange
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
 */
ETHIF_LINK_INT_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_ProcessSwtPortGroupLinkStateChange( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_PortGroupIterType  portGroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of controller mode and link state information) */
  EthIf_EnterExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Check if a link state change to link active occurred on the EthIf switch port group */
  if( EthIf_GetPortGroupLinkState(portGroupIdx) == ETHIF_PORTGROUP_LINK_STATE_LINK_CHANGE_UP )
  {
    /* #200 Issue a link up for the EthIf switch port group */
    EthIf_SetPortGroupLinkState(portGroupIdx, ETHIF_PORTGROUP_LINK_STATE_LINK);                                         /* SBSW_ETHIF_INT_FCT_IDX_PASS */
    BswM_EthIf_PortGroupLinkStateChg((uint8)portGroupIdx, ETHTRCV_LINK_STATE_ACTIVE);
  }
  /* #30 Check if a link state change to link down occurred on the EthIf switch port group */
  else if( EthIf_GetPortGroupLinkState(portGroupIdx) == ETHIF_PORTGROUP_LINK_STATE_LINK_CHANGE_DOWN )
  {
    /* #300 Issue a link down for the EthIf switch port group */
    EthIf_SetPortGroupLinkState(portGroupIdx, ETHIF_PORTGROUP_LINK_STATE_NO_LINK);                                      /* SBSW_ETHIF_INT_FCT_IDX_PASS */
    BswM_EthIf_PortGroupLinkStateChg((uint8)portGroupIdx, ETHTRCV_LINK_STATE_DOWN);
  }
  else
  {
    /* no link change occurred */
  }

  /* #40 Leave exclusive area -> processing on elements finished */
  EthIf_ExitExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_ProcessSwtPortGroupLinkStateChange() */
#  endif /* ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT */
# endif /* ETHIF_UNIT_TEST */

/**********************************************************************************************************************
 *  EthIf_Link_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the EthIf Link sub-module
 *  \details        -
 *  \pre            Configuration pointer must have been initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_Link_Init( void );

/**********************************************************************************************************************
 *  EthIf_MainFunctionState
 *********************************************************************************************************************/
/*! \brief          Link state supervision Main Function
 *  \details        Main function to monitor link state changes of the managed hardware elements.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-EthIf22983
 *********************************************************************************************************************/
# if ( ETHIF_ENABLE_MAIN_FUNCTION_STATE == STD_ON )
/* Function declaration is provided by SchM */
# else
FUNC(void, ETHIF_CODE) EthIf_MainFunctionState( void );
# endif /* ETHIF_ENABLE_MAIN_FUNCTION_STATE */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_LINK_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Link_Int.h
 *********************************************************************************************************************/

