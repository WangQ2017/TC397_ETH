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
/*!        \file  EthIf_EthSwt.c
 *        \brief  EthIf EthSwt public API source file
 *
 *      \details  Implementation of the public API of the sub-module EthSwt of EthIf.
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

#define ETHIF_ETHSWT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on and not to be changed without adaption of \trace  DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_EthSwt.h"
#include "EthIf_EthSwt_Cbk.h"
#include "EthIf_EthSwt_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Msn header file */
#if (  (ETHIF_SW_MAJOR_VERSION != (15u)) \
    || (ETHIF_SW_MINOR_VERSION != (0u)) \
    || (ETHIF_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthIf_EthSwt.c and EthIf.h are inconsistent"
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

#if !defined (ETHIF_ETHSWT_LOCAL)                                                                                       /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_ETHSWT_LOCAL                                           static
#endif

#if !defined (ETHIF_ETHSWT_LOCAL_INLINE)                                                                                /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_ETHSWT_LOCAL_INLINE                                    LOCAL_INLINE
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

#if ( ETHIF_ENABLE_SIGNAL_QUALITY_API == STD_ON )
/**********************************************************************************************************************
 *  EthIf_Internal_GetPortSignalQuality
 *********************************************************************************************************************/
/*! \brief          Prepare and get the signal quality of the switch port
 *  \details        Function checks the link state and of the switch port and forward the call to the function,
 *                  which will get the actual signal quality and update the list of the measured values
 *                  Reentrant for different Ethernet switch indexes and Ethernet Switch port indexes. Non reentrant for the same switchPortIdx.
 *  \param[in]      portIdx        Index of the port within the context of the Ethernet Interface
 *  \param[in]      switchIdx      Index of the switch within the context of the Ethernet Interface
 *  \param[in]      switchPortIdx  Index of the port within the context of the Ethernet Switch
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_ETHSWT_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_LINK_INLINE_CODE) EthIf_Internal_GetPortSignalQuality(
  EthIf_EthSwtPortIterType portIdx,
  uint8 switchIdx,
  uint8 switchPortIdx);

/**********************************************************************************************************************
 *  EthIf_Update_PortSignalQualityList
 *********************************************************************************************************************/
/*! \brief          Get the actual signal quality and update the list of the measured signal quality values of the
 *                  switch port
 *  \details        Function get the actual signal quality and updates the list of the measured signal qualities
 *                  values of the switch ports. The highest and lowest signal quality are updated depend on current
 *                  signal quality.
 *                  Reentrant for different Ethernet switch indexes and Ethernet Switch port indexes. Non reentrant for the same switchPortIdx.
 *  \param[in]      portIdx        Index of the port within the context of the Ethernet Interface
 *  \param[in]      switchIdx      Index of the switch within the context of the Ethernet Interface
 *  \param[in]      switchPortIdx  Index of the port within the context of the Ethernet Switch
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_ETHSWT_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_LINK_INLINE_CODE) EthIf_Update_PortSignalQualityList(
  EthIf_EthSwtPortIterType portIdx,
  uint8 switchIdx,
  uint8 switchPortIdx);

/**********************************************************************************************************************
 *  EthIf_Reset_PortSignalQualityList
 *********************************************************************************************************************/
/*! \brief          Reset the signal quality of the switch port
 *  \details        Function reset the signal quality of the switch port which stored in a list in
 *                  Ethernet interface. The highest signal quality will be set to 0. The current signal quality will
 *                  be set to 0xFFFFFFFF.
 *                  Reentrant for different portIdx. Non reentrant for the same portIdx.
 *  \param[in]      portIdx        Index of the switch port within the context of the Ethernet Interface.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_ETHSWT_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_Reset_PortSignalQualityList(
  EthIf_EthSwtPortIterType portIdx);

#endif /* ETHIF_ENABLE_SIGNAL_QUALITY_API */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_ENABLE_SIGNAL_QUALITY_API == STD_ON )
/**********************************************************************************************************************
 *  EthIf_Internal_GetPortSignalQuality
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
ETHIF_ETHSWT_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_LINK_INLINE_CODE) EthIf_Internal_GetPortSignalQuality(
  EthIf_EthSwtPortIterType portIdx,
  uint8 switchIdx,
  uint8 switchPortIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  EthTrcv_LinkStateType linkState;

  EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvApiIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(switchIdx);

  /* #10 Enter exclusive area (Reason: Ensure consistency of mode and link state information) */
  EthIf_EnterExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 If the switch port is in state ACTIVE */
  if( EthIf_GetEthSwtPortModeCnt(portIdx) > 0U )
  {
    if(EthIf_GetGetLinkStateOfEthSwtDrvApi(ethSwtDrvApiIdx) != NULL_PTR)
    {
      /* #2000 Get the link state of the port of the switch */
      if(EthIf_GetGetLinkStateOfEthSwtDrvApi(ethSwtDrvApiIdx)((uint8)EthIf_GetSnvOfEthSwt(switchIdx),                   /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_REF_OF_STACK_VAR_PARAM_PTR_CSL03 */
                                                               switchPortIdx,
                                                               &linkState) == E_OK)
      {
        /* #20000 If the link state is in state ACTIVE */
        if( linkState == ETHTRCV_LINK_STATE_ACTIVE )
        {
          retVal = EthIf_Update_PortSignalQualityList(portIdx, switchIdx, switchPortIdx);
        }
      }
    }
  }

  /* #30 Leave exclusive area -> processing on elements finished */
  EthIf_ExitExclusiveArea(SET_CTRL_MODE); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
}

/**********************************************************************************************************************
 *  EthIf_Update_PortSignalQualityList
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
ETHIF_ETHSWT_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_LINK_INLINE_CODE) EthIf_Update_PortSignalQualityList(
  EthIf_EthSwtPortIterType portIdx,
  uint8 switchIdx,
  uint8 switchPortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint32 actualPortSignalQuality = 0U;
  uint8 errorId = ETHIF_E_NO_ERROR;
  /* ----- Implementation ----------------------------------------------- */
  EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvApiIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(switchIdx);

  if (EthIf_GetGetPortSignalQualityOfEthSwtDrvApi(ethSwtDrvApiIdx) != NULL_PTR)
  {
    /* #100 Get the actual signal quality of the port */
    if (EthIf_GetGetPortSignalQualityOfEthSwtDrvApi(ethSwtDrvApiIdx)((uint8)EthIf_GetSnvOfEthSwt(switchIdx),            /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_REF_OF_STACK_VAR_PARAM_PTR_CSL03 */
                                                                              switchPortIdx,
                                                                              &actualPortSignalQuality) == E_OK)
    {
      /* #1000 Enter exclusive area (Reason: Ensure consistency of signal quality statistics) */
      EthIf_EnterExclusiveArea(SIGNAL_QUALITY); /* PRQA S 3109 */ /* MD_MSR_14.3 */

      /* #1010 Update the actual port signal quality, which is stored in Ethernet Interface */
      EthIf_GetPortSignalQualityResult(portIdx).ActualSignalQuality = actualPortSignalQuality;                          /* SBSW_ETHIF_INT_FCT_IDX_PASS */

      /* #1020 Update the maximal port signal quality, which is stored in Ethernet Interface */
      if (actualPortSignalQuality > EthIf_GetPortSignalQualityResult(portIdx).HighestSignalQuality)
      {
        EthIf_GetPortSignalQualityResult(portIdx).HighestSignalQuality = actualPortSignalQuality;                       /* SBSW_ETHIF_INT_FCT_IDX_PASS */
      }
      /* #1030 Update the minimal port signal quality, which is stored in Ethernet Interface */
      if (actualPortSignalQuality < EthIf_GetPortSignalQualityResult(portIdx).LowestSignalQuality)
      {
        EthIf_GetPortSignalQualityResult(portIdx).LowestSignalQuality = actualPortSignalQuality;                        /* SBSW_ETHIF_INT_FCT_IDX_PASS */
      }

      /* #1040 Leave exclusive area -> processing on elements finished */
      EthIf_ExitExclusiveArea(SIGNAL_QUALITY); /* PRQA S 3109 */ /* MD_MSR_14.3 */

      retVal = E_OK;
    }
  }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
  else
  {
    errorId = ETHIF_E_INV_DRIVER_API_CALL;
  }
# endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #20 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_SWITCH_PORT_SIGNAL_QUALITY, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
}

/**********************************************************************************************************************
 *  EthIf_Reset_PortSignalQualityList
 *********************************************************************************************************************/
/*!
 *Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_ETHSWT_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_Reset_PortSignalQualityList(
  EthIf_EthSwtPortIterType portIdx)
{
  /* #10 Enter exclusive area (Reason: Ensure consistency of signal quality statistics) */
  EthIf_EnterExclusiveArea(SIGNAL_QUALITY); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Reset the signal quality of the switch port */
  EthIf_GetPortSignalQualityResult(portIdx).ActualSignalQuality = 0U;                                                   /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  EthIf_GetPortSignalQualityResult(portIdx).HighestSignalQuality = 0U;                                                  /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  EthIf_GetPortSignalQualityResult(portIdx).LowestSignalQuality = LOWEST_PORT_SIGNAL_QUALITY_INIT;                      /* SBSW_ETHIF_INT_FCT_IDX_PASS */

  /* #30 Leave exclusive area -> processing on elements finished */
  EthIf_ExitExclusiveArea(SIGNAL_QUALITY); /* PRQA S 3109 */ /* MD_MSR_14.3 */
}

#endif /* ETHIF_ENABLE_SIGNAL_QUALITY_API */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_GET_PORT_MAC_ADDR_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_GetPortMacAddr
 **********************************************************************************************************************/
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetPortMacAddr(
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA)  MacAddrPtr,
    P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)   SwitchIdxPtr,
    P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)   PortIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393875 */
    /* \trace SPEC-2393877 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( MacAddrPtr == NULL_PTR )
  {
    /* \trace SPEC-2393876 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( SwitchIdxPtr == NULL_PTR )
  {
    /* \trace SPEC-2393876 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( PortIdxPtr == NULL_PTR )
  {
    /* \trace SPEC-2393876 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIterType ethSwtDrvIdx;

    /* #30 For each Ethernet switch driver managed by EthIf */
    for( ethSwtDrvIdx = 0u;
         ethSwtDrvIdx < EthIf_GetSizeOfEthSwtDrvApi();
         ethSwtDrvIdx++ )
    {
      /* #300 Check if driver provides the API */
      if( EthIf_GetGetPortMacAddrOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
      {
        /* #3000 Redirect call to the driver */
        /* \trace SPEC-2394044 */
        retVal = EthIf_GetGetPortMacAddrOfEthSwtDrvApi(ethSwtDrvIdx)(MacAddrPtr,
                                                                     SwitchIdxPtr,
                                                                     PortIdxPtr);                                       /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */

        /* #3010 Check if call to driver was successful -> port information found */
        if( retVal == E_OK )
        {
          EthIf_EthSwtIterType  ethIfSwtIdx;

          retVal = E_NOT_OK;

          /* #30100 Transform the switch index from the driver context to the EthIf context */
          /* search for a matching driver local switch index within the EthIf switch index search range */
          for( ethIfSwtIdx = EthIf_GetEthSwtStartIdxOfEthSwtDrv(ethSwtDrvIdx);
               ethIfSwtIdx < EthIf_GetEthSwtEndIdxOfEthSwtDrv(ethSwtDrvIdx);
               ethIfSwtIdx++ )
          {
            /* check if the driver context switch index matches */
            if( EthIf_GetSnvOfEthSwt(ethIfSwtIdx) == (*SwitchIdxPtr) )
            {
              (*SwitchIdxPtr) = (uint8)ethIfSwtIdx;                                                                     /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
              retVal = E_OK;
            }

            /* leave inner loop if tranformation to EthIf context was done */
            if( retVal == E_OK )
            {
              break;
            }
          }

          /* leave outer loop if transformation to EthIf context was done */
          if( retVal == E_OK )
          {
            break;
          }
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_PORT_MAC_ADDR, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetPortMacAddr() */ /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */
#endif /* ETHIF_GET_PORT_MAC_ADDR_API */

#if ( ETHIF_GET_ARL_TABLE_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_GetArlTable
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetArlTable(
        uint8                                            SwitchIdx,
  P2VAR(uint32,              AUTOMATIC, ETHIF_APPL_VAR)  LenPtr,
  P2VAR(EthSwt_MacVlanType,  AUTOMATIC, ETHIF_APPL_VAR)  ArlTablePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393880 */
    /* \trace SPEC-2393882 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt()  )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else if( LenPtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( ArlTablePtr == NULL_PTR )
  {
    /* \trace SPEC-2393881 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(SwitchIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetGetArlTableOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      /* \trace SPEC-2394046 */
      retVal = EthIf_GetGetArlTableOfEthSwtDrvApi(ethSwtDrvIdx)((uint8)EthIf_GetSnvOfEthSwt(SwitchIdx),
                                                                LenPtr,
                                                                ArlTablePtr);                                           /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_ARL_TABLE, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetArlTable() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHIF_GET_ARL_TABLE_API */

#if ( ETHIF_GET_BUFFER_LEVEL_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_GetBufferLevel
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetBufferLevel(
        uint8                                               SwitchIdx,
  P2VAR(EthSwt_BufferLevelType, AUTOMATIC, ETHIF_APPL_VAR)  SwitchBufferLevelPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393885 */
    /* \trace SPEC-2393887 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt()  )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else if( SwitchBufferLevelPtr == NULL_PTR )
  {
    /* \trace SPEC-2393886 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(SwitchIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetGetBufferLevelOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      /* \trace SPEC-2394048 */
      retVal = EthIf_GetGetBufferLevelOfEthSwtDrvApi(ethSwtDrvIdx)((uint8)EthIf_GetSnvOfEthSwt(SwitchIdx),
                                                                   SwitchBufferLevelPtr);                               /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_BUFFER_LEVEL, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetBufferLevel() */
#endif /* ETHIF_GET_BUFFER_LEVEL_API */

#if ( ETHIF_GET_DROP_COUNT_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_GetDropCount
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetDropCount(
        uint8                               SwitchIdx,
  P2VAR(uint16, AUTOMATIC, ETHIF_APPL_VAR)  LenPtr,
  P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR)  DropCountPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393890 */
    /* \trace SPEC-2393892 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt()  )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else if( LenPtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( DropCountPtr == NULL_PTR )
  {
    /* \trace SPEC-2393891 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(SwitchIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetGetDropCountOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      /* \trace SPEC-2394050 */
      retVal = EthIf_GetGetDropCountOfEthSwtDrvApi(ethSwtDrvIdx)((uint8)EthIf_GetSnvOfEthSwt(SwitchIdx),
                                                                 LenPtr,
                                                                 DropCountPtr);                                         /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_DROP_COUNT, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetDropCount() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHIF_GET_DROP_COUNT_API */

#if ( ETHIF_STORE_CONFIG_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_StoreConfiguration
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_StoreConfiguration(
  uint8  SwitchIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393895 */
    /* \trace SPEC-2393896 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt()  )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(SwitchIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetStoreConfigOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      retVal = EthIf_GetStoreConfigOfEthSwtDrvApi(ethSwtDrvIdx)((uint8)EthIf_GetSnvOfEthSwt(SwitchIdx));                /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_STORE_CONFIGURATION, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_StoreConfiguration() */
#endif /* ETHIF_STORE_CONFIG_API */

#if ( ETHIF_RESET_CONFIG_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_ResetConfiguration
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_ResetConfiguration(
  uint8  SwitchIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393899 */
    /* \trace SPEC-2393900 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt() )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(SwitchIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetResetConfigOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      retVal = EthIf_GetResetConfigOfEthSwtDrvApi(ethSwtDrvIdx)((uint8)EthIf_GetSnvOfEthSwt(SwitchIdx));                /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_RESET_CONFIGURATION, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_ResetConfiguration() */
#endif /* ETHIF_RESET_CONFIG_API */

#if ( ETHIF_SWITCH_UPDATE_MCAST_PORT_ASSIGN_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_SwitchUpdateMCastPortAssignment
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchUpdateMCastPortAssignment(
          uint8                              SwitchIdx,
          uint8                              PortIdx,
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA) MCastAddr,
          EthSwt_MCastPortAssignActionType   Action)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt()  )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else if( MCastAddr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( (Action != ETHSWT_MCAST_PORT_ASSIGN_ACTION_ADD)    &&
           (Action != ETHSWT_MCAST_PORT_ASSIGN_ACTION_REMOVE)    )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(SwitchIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetUpdateMCastPortAssignmentOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      retVal = EthIf_GetUpdateMCastPortAssignmentOfEthSwtDrvApi(ethSwtDrvIdx)((uint8)EthIf_GetSnvOfEthSwt(SwitchIdx),
                                                                              PortIdx,
                                                                              MCastAddr,
                                                                              Action);                                  /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SWITCH_UPDATE_MCAST_PORT_ASSIGNMENT, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_SwitchUpdateMCastPortAssignment() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHIF_SWITCH_UPDATE_MCAST_PORT_ASSIGN_API */

#if ( ETHIF_SWITCH_ENABLE_VLAN_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_SwitchEnableVlan
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchEnableVlan(
  uint8   SwitchIdx,
  uint8   PortIdx,
  uint16  VlanId,
  boolean Enable)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt()  )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(SwitchIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetEnableVlanOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      retVal = EthIf_GetEnableVlanOfEthSwtDrvApi(ethSwtDrvIdx)((uint8)EthIf_GetSnvOfEthSwt(SwitchIdx),
                                                               PortIdx,
                                                               VlanId,
                                                               Enable);                                                 /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SWITCH_ENABLE_VLAN, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_SwitchEnableVlan() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHIF_SWITCH_ENABLE_VLAN_API */

#if ( ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT == STD_ON )
/**********************************************************************************************************************
 * EthIf_SetSwitchMgmtInfo
 **********************************************************************************************************************/
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetSwitchMgmtInfo(
        uint8                                             CtrlIdx,
        Eth_BufIdxType                                    BufIdx,
  P2VAR(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_DATA)  MgmtInfoPtr) /* PRQA S 3673 */ /* MD_EthIf_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( BufIdx > EthIf_GetMaxTxBufIdxForEthIfCtrl(CtrlIdx) )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( MgmtInfoPtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(CtrlIdx);
    EthIf_TxContextIterType txCtxtIdx = EthIf_CalcTxCtxtIdx(ethCtrlIdx, BufIdx);

    /* #30 Check if tx buffer was acquired during EthIf_ProvideTxBuffer() and EthIf_Transmit() wasn't called yet */
    if ( (EthIf_IsValidOfTxContext(txCtxtIdx) == TRUE) &&
         (EthIf_GetEthIfCtrlIdxOfTxContext(txCtxtIdx) == CtrlIdx) )
    {
      /* #40 Check if driver provides the API */
      if( EthIf_IsEthSwtDrvApiUsedOfEthIfCtrl(CtrlIdx) == TRUE )
      {
        EthIf_EthSwtDrvApiIdxOfEthIfCtrlType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthIfCtrl(CtrlIdx);

        if( EthIf_GetSetSwtMgmtInfoOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
        {
          /* #400 Redirect call to the driver */
          retVal = EthIf_GetSetSwtMgmtInfoOfEthSwtDrvApi(ethSwtDrvIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                                       BufIdx,
                                                                       MgmtInfoPtr);                                    /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SET_SWITCH_MGMT_INFO, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_SetSwitchMgmtInfo() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
 *  EthIf_GetRxMgmtObject
 **********************************************************************************************************************/
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetRxMgmtObject(
        uint8                                                                               CtrlIdx,
  P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR)                                            DataPtr,
  P2VAR(P2VAR(EthSwt_MgmtObjectType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR) MgmtObjectPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( DataPtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( MgmtObjectPtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if driver provides the API */
    if( EthIf_IsEthSwtDrvApiUsedOfEthIfCtrl(CtrlIdx) == TRUE )
    {
      P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)  u8DataPtr;
      EthIf_EthSwtDrvApiIdxOfEthIfCtrlType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthIfCtrl(CtrlIdx);

      u8DataPtr = (P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR))DataPtr; /* PRQA S 0310 */ /* MD_EthIf_310_Buffer */

      /* #300 Adapt buffer pointer passed to driver depending on type of EthIf controller (un-tagged, tagged) */
      if( EthIf_GetTypeOfEthIfCtrl(CtrlIdx) != ETHIF_ETHIFCTRL_TYPE_PHYSICAL_TYPEOFETHIFCTRL )
      {
        u8DataPtr = &u8DataPtr[-((sint8)ETHIF_VLAN_TAG_LEN_BYTE)]; /* PRQA S 3382 */ /* MD_EthIf_3382 */
      }

      if( EthIf_GetGetRxMgmtObjectOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
      {
        EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(CtrlIdx);

        /* #310 Redirect call to the driver */
        /* PRQA S 0310, 3305 4 */ /* MD_EthIf_310_Buffer, MD_EthIf_3305_Buffer */
        retVal = EthIf_GetGetRxMgmtObjectOfEthSwtDrvApi(ethSwtDrvIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                                      (P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR))u8DataPtr,
                                                                      MgmtObjectPtr);                                   /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
      }
    }

# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_RX_MGMT_OBJECT, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetRxMgmtObject() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 * EthIf_GetTxMgmtObject
 **********************************************************************************************************************/
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetTxMgmtObject(
        uint8                                                                               CtrlIdx,
        Eth_BufIdxType                                                                      BufIdx,
  P2VAR(P2VAR(EthSwt_MgmtObjectType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR) MgmtObjectPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( BufIdx > EthIf_GetMaxTxBufIdxForEthIfCtrl(CtrlIdx) )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( MgmtObjectPtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(CtrlIdx);
    EthIf_TxContextIterType txCtxtIdx = EthIf_CalcTxCtxtIdx(ethCtrlIdx, BufIdx);

    /* #30 Check if tx buffer was acquired during EthIf_ProvideTxBuffer() and EthIf_Transmit() wasn't called yet */
    if ( (EthIf_IsValidOfTxContext(txCtxtIdx) == TRUE) &&
         (EthIf_GetEthIfCtrlIdxOfTxContext(txCtxtIdx) == CtrlIdx) )
    {
      /* #40 Check if driver provides the API */
      if( EthIf_IsEthSwtDrvApiUsedOfEthIfCtrl(CtrlIdx) == TRUE )
      {
        EthIf_EthSwtDrvApiIdxOfEthIfCtrlType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthIfCtrl(CtrlIdx);

        if( EthIf_GetGetTxMgmtObjectOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
        {
          /* #400 Redirect call to the driver */
          retVal = EthIf_GetGetTxMgmtObjectOfEthSwtDrvApi(ethSwtDrvIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                                        BufIdx,
                                                                        MgmtObjectPtr);                                 /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_TX_MGMT_OBJECT, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetTxMgmtObject() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

#endif /* ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT */

#if ( ETHIF_ETHSWT_TIME_STAMP_SUPPORT == STD_ON )
/**********************************************************************************************************************
 * EthIf_SwitchEnableTimeStamping
 **********************************************************************************************************************/
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchEnableTimeStamping(
        uint8                                            CtrlIdx,
        Eth_BufIdxType                                   BufIdx,
  P2VAR(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_VAR)  MgmtInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( BufIdx > EthIf_GetMaxTxBufIdxForEthIfCtrl(CtrlIdx) )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( MgmtInfo == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(CtrlIdx);
    EthIf_TxContextIterType txCtxtIdx = EthIf_CalcTxCtxtIdx(ethCtrlIdx, BufIdx);

    /* #30 Check if tx buffer was acquired during EthIf_ProvideTxBuffer() and EthIf_Transmit() wasn't called yet */
    if ( (EthIf_IsValidOfTxContext(txCtxtIdx) == TRUE) &&
         (EthIf_GetEthIfCtrlIdxOfTxContext(txCtxtIdx) == CtrlIdx) )
    {
      /* #40 Check if driver provides the API */
      if( EthIf_IsEthSwtDrvApiUsedOfEthIfCtrl(CtrlIdx) == TRUE )
      {
        EthIf_EthSwtDrvApiIdxOfEthIfCtrlType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthIfCtrl(CtrlIdx);

        if( EthIf_GetPortEnableTimeStampOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
        {
          /* #420 Redirect call to the driver */
          retVal = EthIf_GetPortEnableTimeStampOfEthSwtDrvApi(ethSwtDrvIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                                            BufIdx,
                                                                            MgmtInfo);                                  /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
        }
      }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
      else
      {
        errorId = ETHIF_E_INV_DRIVER_API_CALL;
      }
# endif /* ETHIF_DEV_ERROR_DETECT */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SWITCH_ENABLE_TIME_STAMPING, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_SwitchEnableEgressTimeStamp() */ /* PRQA S 6080, 6030 */ /* MD_MSR_STMIF, MD_MSR_STCYC */

/**********************************************************************************************************************
 * EthIf_SwitchSetCorrectionTime
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchSetCorrectionTime(
          uint8                                             EthIfSwtIdx,
  P2CONST(Eth_TimeIntDiffType, AUTOMATIC, ETHIF_APPL_DATA)  OffsetPtr,
  P2CONST(float64,             AUTOMATIC, ETHIF_APPL_DATA)  RateRatioPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( EthIfSwtIdx >= EthIf_GetSizeOfEthSwt() )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType swtDrvApiIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(EthIfSwtIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetSetCorrectionTimeOfEthSwtDrvApi(swtDrvApiIdx) != NULL_PTR )
    {
      /* #310 Redirect call to the driver */
      retVal = EthIf_GetSetCorrectionTimeOfEthSwtDrvApi(swtDrvApiIdx)((uint8)EthIf_GetSnvOfEthSwt(EthIfSwtIdx),
                                                                      OffsetPtr,
                                                                      RateRatioPtr);                                    /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SWITCH_SET_CORRECTION_TIME, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_SwitchSetCorrectionTime() */

/**********************************************************************************************************************
 * EthIf_StartSwitchQbvSchedule
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_StartSwitchQbvSchedule(
  uint8  EthIfSwtIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( EthIfSwtIdx >= EthIf_GetSizeOfEthSwt() )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType swtDrvApiIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(EthIfSwtIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetStartQbvScheduleOfEthSwtDrvApi(swtDrvApiIdx) != NULL_PTR )
    {
      /* #310 Redirect call to the driver */
      retVal = EthIf_GetStartQbvScheduleOfEthSwtDrvApi(swtDrvApiIdx)((uint8)EthIf_GetSnvOfEthSwt(EthIfSwtIdx));         /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_START_SWITCH_QBV_SCHEDULE, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_StartSwitchQbvSchedule() */

/**********************************************************************************************************************
 * EthIf_StopSwitchQbvSchedule
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_StopSwitchQbvSchedule(
  uint8  EthIfSwtIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( EthIfSwtIdx >= EthIf_GetSizeOfEthSwt() )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType swtDrvApiIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(EthIfSwtIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetStopQbvScheduleOfEthSwtDrvApi(swtDrvApiIdx) != NULL_PTR )
    {
      /* #310 Redirect call to the driver */
      retVal = EthIf_GetStopQbvScheduleOfEthSwtDrvApi(swtDrvApiIdx)((uint8)EthIf_GetSnvOfEthSwt(EthIfSwtIdx));          /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_STOP_SWITCH_QBV_SCHEDULE, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_StopSwitchQbvSchedule() */

#endif /* ETHIF_ETHSWT_TIME_STAMP_SUPPORT */

#if ( ETHIF_ENABLE_SIGNAL_QUALITY_API == STD_ON )
/**********************************************************************************************************************
*  EthIf_GetSwitchPortSignalQuality
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetSwitchPortSignalQuality(
        uint8 SwitchIdx,
        uint8 SwitchPortIdx,
  P2VAR(EthIf_SignalQualityResultType, AUTOMATIC, ETHIF_APPL_VAR) ResultPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthSwtPortIterType portIdx;
  Std_ReturnType retVal;
  uint8 errorId  = ETHIF_E_NO_ERROR;

# if (ETHIF_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
# endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt() )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else if ( ResultPtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Get the port index within the context of Ethernet interface */
    portIdx = EthIf_QueryForPortIndex(SwitchIdx, SwitchPortIdx);

    /* #40 Enter exclusive area (Reason: Ensure consistency of signal quality statistics) */
    EthIf_EnterExclusiveArea(SIGNAL_QUALITY); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #50 Get the port signal qualities */
    retVal = EthIf_Internal_GetPortSignalQuality(portIdx, SwitchIdx, SwitchPortIdx);

    if (retVal == E_OK){
      ResultPtr->ActualSignalQuality =
          EthIf_GetPortSignalQualityResult(portIdx).ActualSignalQuality;                                                 /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      ResultPtr->HighestSignalQuality =
          EthIf_GetPortSignalQualityResult(portIdx).HighestSignalQuality;                                                /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
      ResultPtr->LowestSignalQuality =
          EthIf_GetPortSignalQualityResult(portIdx).LowestSignalQuality;                                                 /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
    } else {
      EthIf_Reset_PortSignalQualityList(portIdx);
    }

    /* #60 Leave exclusive area -> processing on elements finished */
    EthIf_ExitExclusiveArea(SIGNAL_QUALITY); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #70 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_SWITCH_PORT_SIGNAL_QUALITY, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetSwitchPortSignalQuality() */

/**********************************************************************************************************************
*  EthIf_ClearSwitchPortSignalQuality
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_ClearSwitchPortSignalQuality(
  uint8 SwitchIdx,
  uint8 SwitchPortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthSwtPortIterType portIdx;
  Std_ReturnType retVal;
  uint8 errorId  = ETHIF_E_NO_ERROR;

# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                /* COV_ETHIF_SAFE_FEAT */
  retVal = E_NOT_OK;
# endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt() )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Get the port index within the context of Ethernet interface*/
    portIdx = EthIf_QueryForPortIndex(SwitchIdx, SwitchPortIdx);
    /* #300 Clear the port signal qualities which are stored in Ethernet interface*/
    EthIf_Reset_PortSignalQualityList(portIdx);
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_CLEAR_SWITCH_PORT_SIGNAL_QUALITY, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_ClearSwitchPortSignalQuality() */

/**********************************************************************************************************************
 *  EthIf_PollPortSignalQualities
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_PollPortSignalQualities( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthSwtPortIterType portIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For each switch port */
  for( portIdx = 0U;
       portIdx < EthIf_GetSizeOfEthSwtPort();
       portIdx++ )
  {
    /* #100 Get the port signal quality and store it in Ethernet interface*/
    if (EthIf_Internal_GetPortSignalQuality(portIdx, EthIf_GetEthSwtIdxOfEthSwtPort(portIdx), (uint8)EthIf_GetSnvOfEthSwtPort(portIdx)) == E_NOT_OK){
      /* #1000 If it fails, clear the switch port signal quality */
      EthIf_Reset_PortSignalQualityList(portIdx);
    }
  }
} /* EthIf_PollPortSignalQualities() */

/**********************************************************************************************************************
 *  EthIf_PortSignalQualityList_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_PortSignalQualityList_Init( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthSwtPortIterType portIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For each switch port */
  for( portIdx = 0U;
       portIdx < EthIf_GetSizeOfEthSwtPort();
       portIdx++ )
  {
    /* #100 Initialization of the signal quality of the switch port*/
    EthIf_Reset_PortSignalQualityList(portIdx);
  }
} /* EthIf_PortSignalQualityList_Init() */

/**********************************************************************************************************************
 *  EthIf_QueryForPortIndex
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(EthIf_EthSwtPortIterType, ETHIF_CODE) EthIf_QueryForPortIndex(
  uint8 switchIdx,
  uint8 switchPortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthSwtPortIterType portIdx;
  EthIf_EthSwtPortIterType queriedPortIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For each port index in the context of Ethernet interface */
  queriedPortIdx = EthIf_GetSizeOfEthSwtPort();

  for( portIdx = 0U;
           portIdx < EthIf_GetSizeOfEthSwtPort();
           portIdx++ )
  {
    /* #100 Check if switchIdx of the port matches the switchIdx required for */
    if ((uint8)EthIf_GetEthSwtIdxOfEthSwtPort(portIdx) == switchIdx)
    {
      /* #1000 Check if the switchPortIdx of the port matches the switchPortIdx required for*/
      if ((uint8)EthIf_GetSnvOfEthSwtPort(portIdx) == switchPortIdx)
      {
        /* #10000 Matched -> return port index within the context of Ethernet interface*/
        queriedPortIdx = portIdx;
        break;
      }
    }
  }

  return queriedPortIdx;
}

#endif /* ETHIF_ENABLE_SIGNAL_QUALITY_API */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_EthSwt.c
 *********************************************************************************************************************/

