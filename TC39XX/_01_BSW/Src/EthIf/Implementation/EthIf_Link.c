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
/*!        \file  EthIf_Link.c
 *        \brief  EthIf Link public API source file
 *
 *      \details  Implementation of the public API of the sub-module Link of EthIf.
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

#define ETHIF_LINK_SOURCE

/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_Link.h"
#include "EthIf_Link_Cbk.h"
#include "EthIf_Link_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Msn header file */
#if (  (ETHIF_SW_MAJOR_VERSION != (15u)) \
    || (ETHIF_SW_MINOR_VERSION != (0u)) \
    || (ETHIF_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthIf_Link.c and EthIf.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (ETHIF_LINK_LOCAL)                                                                                         /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_LINK_LOCAL static
#endif

#if !defined (ETHIF_LINK_LOCAL_INLINE)                                                                                  /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_LINK_LOCAL_INLINE LOCAL_INLINE
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

/**********************************************************************************************************************
 *  EthIf_ProcessLinkStateChangeForAllEthIfCtrls
 *********************************************************************************************************************/
/*! \brief          Processes the link state changes for all EthIf controllers
 *  \details        This function checks for link state changes on all EthIf controllers and notifies the EthIf users
 *                  registered for a link state change notification about changes.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_ProcessLinkStateChangeForAllEthIfCtrls( void );

#if ( ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  EthIf_ProcessAllEthIfSwtPortGroupLinkStateChanges
 *********************************************************************************************************************/
/*! \brief          Processes the link state changes for all EthIf switch port groups
 *  \details        This function checks for link state changes on all EthIf switch port groups and notifies the BswM
 *                  about the change.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_ProcessAllEthIfSwtPortGroupLinkStateChanges( void );
#endif /* ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT */

/**********************************************************************************************************************
 *  EthIf_InitLinkCounts
 *********************************************************************************************************************/
/*! \brief          Initializes EthIf controller an EthIf switch port group link counts
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_InitLinkCounts( void );

#if ( ETHIF_ETHTRCV_USED == STD_ON )                                                                                    /* COV_ETHIF_SAFE_FEAT */
/**********************************************************************************************************************
 *  EthIf_PollTrcvLinks
 *********************************************************************************************************************/
/*! \brief          Poll the link state of Ethernet transceivers
 *  \details        This function polls the link state of the Ethernet transceivers by utilizing the respective
 *                  hardware driver.
 *  \pre            EthIf_DetectLinkStateChange() has to initialize all EthIf_EthIfCtrlLinkCnts to 0 before calling
 *                  EthIf_PollTrcvLinks() and EthIf_PollPortLinks().
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_PollTrcvLinks( void );
#endif /* ETHIF_ETHTRCV_USED */

#if ( ETHIF_ETHSWT_USED == STD_ON )
/**********************************************************************************************************************
 *  EthIf_PollPortLinks
 *********************************************************************************************************************/
/*! \brief          Poll the link state of Ethernet switch ports
 *  \details        This function polls the link state of the Ethernet switch ports by utilizing the respective
 *                  hardware driver.
 *  \pre            EthIf_DetectLinkStateChange() has to initialize all EthIf_EthIfCtrlLinkCnts to 0 before calling
 *                  EthIf_PollTrcvLinks() and EthIf_PollPortLinks().
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_PollPortLinks( void );

/**********************************************************************************************************************
 *  EthIf_PollPortGroupLinks
 *********************************************************************************************************************/
/*! \brief          Poll the link state of Ethernet switch port groups
 *  \details        This function polls the link state of the Ethernet switch port groups.
 *  \pre            EthIf_DetectLinkStateChange() has to initialize all EthIf_EthIfCtrlLinkCnts to 0 before calling
 *                  EthIf_PollPortLinks() and thereafter EthIf_PollPortGroupLinks().
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_PollPortGroupLinks( void );
#endif /* ETHIF_ETHSWT_USED */

/**********************************************************************************************************************
 *  EthIf_DetectLinkStateChangesOnEthIfCtrls
 *********************************************************************************************************************/
/*! \brief          Detects if a link change for the EthIf controllers has occurred
 *  \details        This functions detects if a link state change for the EthIf controllers has occurred.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_DetectLinkStateChangesOnEthIfCtrls( void );

#if ( ETHIF_ETHSWT_USED == STD_ON )
/**********************************************************************************************************************
 *  EthIf_DetectLinkStateChangesOnEthIfSwtPortGroups
 *********************************************************************************************************************/
/*! \brief          Detects if a link change for the EthIf switch port groups have occurred
 *  \details        This functions detects if a link state change for the EthIf switch port groups have occurred.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_DetectLinkStateChangesOnEthIfSwtPortGroups( void );
#endif /* ETHIF_ETHSWT_USED */

/**********************************************************************************************************************
 *  EthIf_DetectLinkStateChange
 *********************************************************************************************************************/
/*! \brief          Detects if a link change for the EthIf controllers has occurred
 *  \details        This functions detects if a link state change for the EthIf controllers has occurred.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_DetectLinkStateChange(void);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_ProcessLinkStateChangeForAllEthIfCtrls
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_ProcessLinkStateChangeForAllEthIfCtrls( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthIfCtrlIterType ethIfCtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check each EthIf controller for a link change */
  /* \trace SPEC-2393938 */
  for( ethIfCtrlIdx = 0;
       ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl();
       ethIfCtrlIdx++ )
  {
    EthIf_ProcessLinkStateChange(ethIfCtrlIdx);
  }
} /* EthIf_ProcessLinkStateChangeForAllEthIfCtrls() */

#if ( ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  EthIf_ProcessAllEthIfSwtPortGroupLinkStateChanges
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_ProcessAllEthIfSwtPortGroupLinkStateChanges( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_PortGroupIterType portGroupIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check each EthIf switch port group with semantic type independent for a link change */
  for( portGroupIdx = 0;
       portGroupIdx < EthIf_GetSizeOfPortGroup();
       portGroupIdx++ )
  {
    if ( EthIf_GetSemanticOfPortGroup(portGroupIdx) == ETHIF_PORTGROUP_SEMANTIC_INDEPENDENT_SEMANTICOFPORTGROUP )
    {
      EthIf_ProcessSwtPortGroupLinkStateChange(portGroupIdx);
    }
  }
} /* EthIf_ProcessAllEthIfSwtPortGroupLinkStateChanges() */
#endif /* ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT */

/**********************************************************************************************************************
 *  EthIf_InitLinkCounts
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_InitLinkCounts( void )
{
  EthIf_EthIfCtrlLinkCountIterType ethIfCtrlLinkCntIdx;
#if ( ETHIF_ETHSWT_USED == STD_ON )
  EthIf_PortGroupLinkCountIterType portGroupLinkCntIdx;
#endif /* ETHIF_ETHSWT_USED */

  /* #10 Initialize link counts of the EthIf controllers */
  for( ethIfCtrlLinkCntIdx = 0;
       ethIfCtrlLinkCntIdx < EthIf_GetSizeOfEthIfCtrlLinkCount();
       ethIfCtrlLinkCntIdx++ )
  {
    EthIf_SetEthIfCtrlLinkCount(ethIfCtrlLinkCntIdx, 0u);                                                               /* SBSW_ETHIF_COMMON_CSL01 */
  }

#if ( ETHIF_ETHSWT_USED == STD_ON )
  /* #20 Initialize link counts of EthIf switch port groups */
  for( portGroupLinkCntIdx = 0;
       portGroupLinkCntIdx < EthIf_GetSizeOfPortGroup();
       portGroupLinkCntIdx++ )
  {
    EthIf_SetPortGroupLinkCount(portGroupLinkCntIdx, 0u);                                                               /* SBSW_ETHIF_COMMON_CSL01 */
  }
#endif /* ETHIF_ETHSWT_USED */
} /* EthIf_InitLinkCounts() */

#if ( ETHIF_ETHTRCV_USED == STD_ON )                                                                                    /* COV_ETHIF_SAFE_FEAT */
/**********************************************************************************************************************
 *  EthIf_PollTrcvLinks
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_PollTrcvLinks( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthTrcvIterType ethTrcvIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For each transceiver */
  for( ethTrcvIdx = 0U;
       ethTrcvIdx < EthIf_GetSizeOfEthTrcv();
       ethTrcvIdx++ )
  {
    /* #100 If the transceiver is in state ACTIVE */
    if( EthIf_GetEthTrcvModeCnt(ethTrcvIdx) > 0U )
    {
      EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

      if( EthIf_GetGetLinkStateOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
      {
        EthTrcv_LinkStateType linkState;

        /* #1000 Retrieve the link and if link state is ACTIVE map it to the related EthIf controllers */
        if( EthIf_GetGetLinkStateOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(ethTrcvIdx),
                                                                   &linkState) == E_OK )                                /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_REF_OF_STACK_VAR_PARAM_PTR_CSL03 */
        {
          if( linkState == ETHTRCV_LINK_STATE_ACTIVE )
          {
            EthIf_EthIfCtrlOfEthTrcvIndIterType indIdx;

            for( indIdx = EthIf_GetEthIfCtrlOfEthTrcvIndStartIdxOfEthTrcv(ethTrcvIdx);
                 indIdx < EthIf_GetEthIfCtrlOfEthTrcvIndEndIdxOfEthTrcv(ethTrcvIdx);
                 indIdx++ )
            {
              EthIf_EthIfCtrlOfEthTrcvIndType ethIfCtrlIdx = EthIf_GetEthIfCtrlOfEthTrcvInd(indIdx);

              EthIf_IncEthIfCtrlLinkCount(ethIfCtrlIdx);                                                                /* SBSW_ETHIF_COMMON_CSL03 */
            }
          }
        }
      }
    }
  }
} /* EthIf_PollTrcvLinks() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHIF_ETHTRCV_USED */

#if ( ETHIF_ETHSWT_USED == STD_ON )
/**********************************************************************************************************************
 *  EthIf_PollPortLinks
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
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_PollPortLinks( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthSwtPortIterType portIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of mode and link state information) */
  EthIf_EnterExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 For each switch port */
  for( portIdx = 0U;
       portIdx < EthIf_GetSizeOfEthSwtPort();
       portIdx++ )
  {
    /* #200 If the switch port is in state ACTIVE */
    if( EthIf_GetEthSwtPortModeCnt(portIdx) > 0U )
    {
      EthTrcv_LinkStateType linkState;
      EthIf_EthSwtIdxOfEthSwtPortType ethSwtIdx = EthIf_GetEthSwtIdxOfEthSwtPort(portIdx);
      EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvApiIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(ethSwtIdx);

      /* #2000 Retrieve the link and if link state is ACTIVE map it to the related EthIf switch port groups */
      if( EthIf_GetGetLinkStateOfEthSwtDrvApi(ethSwtDrvApiIdx)((uint8)EthIf_GetSnvOfEthSwt(ethSwtIdx),
                                                               (uint8)EthIf_GetSnvOfEthSwtPort(portIdx),
                                                               &linkState) == E_OK )                                    /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_WITH_REF_OF_STACK_VAR_PARAM_PTR_CSL03 */
      {
        if( linkState == ETHTRCV_LINK_STATE_ACTIVE )
        {
          EthIf_PortGroupIndIterType indIdx;

          for( indIdx = EthIf_GetPortGroupIndStartIdxOfEthSwtPort(portIdx);
               indIdx < EthIf_GetPortGroupIndEndIdxOfEthSwtPort(portIdx);
               indIdx++ )
          {
            EthIf_PortGroupIndType portGroupIdx = EthIf_GetPortGroupInd(indIdx);

            EthIf_IncPortGroupLinkCount(portGroupIdx);                                                                  /* SBSW_ETHIF_COMMON_CSL03 */
          }
        }
      }
    }
  }

  /* #30 Leave exclusive area -> processing on elements finished */
  EthIf_ExitExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_PollPortLinks() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthIf_PollPortGroupLinks
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_PollPortGroupLinks( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_PortGroupIterType portGroupIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For each switch port group */
  for( portGroupIdx = 0U;
       portGroupIdx < EthIf_GetSizeOfPortGroup();
       portGroupIdx++ )
  {
    if ( (EthIf_GetSemanticOfPortGroup(portGroupIdx) == ETHIF_PORTGROUP_SEMANTIC_CONTROL_SEMANTICOFPORTGROUP) ||
         (EthIf_GetSemanticOfPortGroup(portGroupIdx) == ETHIF_PORTGROUP_SEMANTIC_LINK_INFO_SEMANTICOFPORTGROUP) )
    {
      if( EthIf_GetPortGroupLinkCount(portGroupIdx) >= EthIf_GetLinkAggrThresholdOfPortGroup(portGroupIdx) )
      {
        EthIf_EthIfCtrlOfPortGroupIndIterType indIdx;

        for( indIdx = EthIf_GetEthIfCtrlOfPortGroupIndStartIdxOfPortGroup(portGroupIdx);
             indIdx < EthIf_GetEthIfCtrlOfPortGroupIndEndIdxOfPortGroup(portGroupIdx);
             indIdx++ )
        {
          EthIf_EthIfCtrlOfPortGroupIndType ethIfCtrlIdx = EthIf_GetEthIfCtrlOfPortGroupInd(indIdx);

          EthIf_IncEthIfCtrlLinkCount(ethIfCtrlIdx);                                                                    /* SBSW_ETHIF_COMMON_CSL03 */
        }
      }
    }
  }
} /* EthIf_PollPortGroupLinks() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHIF_ETHSWT_USED */

/**********************************************************************************************************************
 *  EthIf_DetectLinkStateChangesOnEthIfCtrls
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
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_DetectLinkStateChangesOnEthIfCtrls( void )
{
  EthIf_EthIfCtrlIterType ethIfCtrlIdx;

  /* #10 Enter exclusive area (Reason: Ensure consistency of controller mode and link state information) */
  EthIf_EnterExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 For each EthIf controller */
  for( ethIfCtrlIdx = 0;
       ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl();
       ethIfCtrlIdx++ )
  {
    /* #200 If EthIf controller is ACTIVE */
    if( EthIf_GetEthIfCtrlMode(ethIfCtrlIdx) == ETH_MODE_ACTIVE )
    {
      /* #2000 If link is established for the needed amount of phy layer elements */
      if( EthIf_GetEthIfCtrlLinkCount(ethIfCtrlIdx) >= EthIf_GetLinkAggrThresholdOfEthIfCtrl(ethIfCtrlIdx) )
      {
        /* #20000 Issue a link state to UP if EthIf controller hasn't established a link before */
        if( EthIf_GetEthIfCtrlLinkState(ethIfCtrlIdx) != ETHIF_ETHIFCTRL_LINK_STATE_LINK )
        {
          /* issue a link up on the EthIf controller */
          EthIf_SetEthIfCtrlLinkState(ethIfCtrlIdx, ETHIF_ETHIFCTRL_LINK_STATE_LINK_CHANGE_UP);                         /* SBSW_ETHIF_COMMON_CSL01 */
        }
      }
      /* #2010 Otherwise (if link isn't established on the needed amount of phy layer elements) */
      else
      {
        /* #20100 Issue a link state to DOWN if EthIf controller has established a link before */
        if( EthIf_GetEthIfCtrlLinkState(ethIfCtrlIdx) != ETHIF_ETHIFCTRL_LINK_STATE_NO_LINK )
        {
          /* issue a link down on the EthIf controller */
          EthIf_SetEthIfCtrlLinkState(ethIfCtrlIdx, ETHIF_ETHIFCTRL_LINK_STATE_LINK_CHANGE_DOWN);                       /* SBSW_ETHIF_COMMON_CSL01 */
        }
      }
    }
  }

  /* #30 Leave exclusive area -> processing on elements finished */
  EthIf_ExitExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_DetectLinkStateChangesOnEthIfCtrls() */

#if ( ETHIF_ETHSWT_USED == STD_ON )
/**********************************************************************************************************************
 *  EthIf_DetectLinkStateChangesOnEthIfSwtPortGroups
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
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_DetectLinkStateChangesOnEthIfSwtPortGroups( void )
{
  EthIf_PortGroupIterType portGroupIdx;

  /* #10 Enter exclusive area (Reason: Ensure consistency of controller mode and link state information) */
  EthIf_EnterExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 For each EthIf switch port group */
  for( portGroupIdx = 0;
       portGroupIdx < EthIf_GetSizeOfPortGroup();
       portGroupIdx++ )
  {
    /* #200 If EthIf switch port group is active and of semantic type independent */
    if ( (EthIf_GetPortGroupMode(portGroupIdx) == ETHTRCV_MODE_ACTIVE) &&
         (EthIf_GetSemanticOfPortGroup(portGroupIdx) == ETHIF_PORTGROUP_SEMANTIC_INDEPENDENT_SEMANTICOFPORTGROUP) )
    {
      /* #2000 If link is established for the needed amount of phy layer elements */
      if( EthIf_GetPortGroupLinkCount(portGroupIdx) >= EthIf_GetLinkAggrThresholdOfPortGroup(portGroupIdx) )
      {
        /* amount of phy elements needed for a link is over or equal to the threshold */

        /* #20000 Issue a link state to UP if EthIf switch port group hasn't established a link before */
        if( EthIf_GetPortGroupLinkState(portGroupIdx) == ETHIF_PORTGROUP_LINK_STATE_NO_LINK )
        {
          /* issue a link up on the EthIf switch port group */
          EthIf_SetPortGroupLinkState(portGroupIdx, ETHIF_PORTGROUP_LINK_STATE_LINK_CHANGE_UP);                         /* SBSW_ETHIF_COMMON_CSL01 */
        }
      }
      /* #2010 Otherwise (if link isn't established on the needed amount of phy layer elements) */
      else
      {
        /* amount of phy elements needed for a link is under the threshold */

        /* #20100 Issue a link state to DOWN if EthIf switch port group has established a link before */
        if( EthIf_GetPortGroupLinkState(portGroupIdx) == ETHIF_PORTGROUP_LINK_STATE_LINK )
        {
          /* issue a link down on the EthIf switch port group */
          EthIf_SetPortGroupLinkState(portGroupIdx, ETHIF_PORTGROUP_LINK_STATE_LINK_CHANGE_DOWN);                       /* SBSW_ETHIF_COMMON_CSL01 */
        }
      }
    }
  }

  /* #30 Leave exclusive area -> processing on elements finished */
  EthIf_ExitExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_DetectLinkStateChangesOnEthIfSwtPortGroups() */
#endif /* ETHIF_ETHSWT_USED */

/**********************************************************************************************************************
 *  EthIf_DetectLinkStateChange
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_LINK_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_DetectLinkStateChange( void )
{
  /* #10 Trigger link counts initialization */
  EthIf_InitLinkCounts();

  /* #20 Trigger retrieval of the link states of all physical layer elements */
#if ( ETHIF_ETHTRCV_USED == STD_ON )                                                                                    /* COV_ETHIF_SAFE_FEAT */
  EthIf_PollTrcvLinks();
#endif /* ETHIF_ETHTRCV_USED */
#if ( ETHIF_ETHSWT_USED == STD_ON )
  EthIf_PollPortLinks();
  EthIf_PollPortGroupLinks();
#endif /* ETHIF_ETHSWT_USED */

  /* #30 Trigger detection of link state changes for EthIf controllers and EthIf switch port groups */
  EthIf_DetectLinkStateChangesOnEthIfCtrls();
#if ( ETHIF_ETHSWT_USED == STD_ON )
  EthIf_DetectLinkStateChangesOnEthIfSwtPortGroups();
#endif /* ETHIF_ETHSWT_USED */
} /* EthIf_DetectLinkStateChange() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_MainFunctionState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_MainFunctionState( void )
{
  /* #10 Check if module is initialized */
  if( EthIf_ModuleInitialized == ETHIF_STATE_INIT )
  {
    /* #100 Get all relevant links of transceivers and switch ports */
    EthIf_DetectLinkStateChange();

    /* #110 Process possible link changes */
    EthIf_ProcessLinkStateChangeForAllEthIfCtrls();

#if ( ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT == STD_ON )
    /* #120 Process possible link changes for EthIf switch port groups */
    EthIf_ProcessAllEthIfSwtPortGroupLinkStateChanges();
#endif /* ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT */
  }

#if ( ETHIF_ENABLE_SIGNAL_QUALITY_API == STD_ON )

  if( EthIf_GetSignalQualityDecoupleFreqCnt() == 0u )
  {
    EthIf_PollTrcvSignalQualities();
    EthIf_PollPortSignalQualities();
    EthIf_SetSignalQualityDecoupleFreqCnt(EthIf_GetSignalQualityChgMainReload());                                       /* SBSW_ETHIF_COMMON_CFG_PTR_INT_FCT_PREV_MODULE_INIT_CHECK */
  }
  /* Decrease polling frequency counter */
  EthIf_DecSignalQualityDecoupleFreqCnt();                                                                              /* SBSW_ETHIF_COMMON_CFG_PTR_INT_FCT_PREV_MODULE_INIT_CHECK */
#endif
} /* EthIf_MainFunctionState() */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Link.c
 *********************************************************************************************************************/

