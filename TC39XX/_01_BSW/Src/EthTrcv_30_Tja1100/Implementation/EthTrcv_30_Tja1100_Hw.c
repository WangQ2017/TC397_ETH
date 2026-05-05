/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*         \file  EthTrcv_30_Tja1100_Hw.c
 *        \brief  Source file containing the core implementation of the Ethernet transceiver driver hardware access
 *                module
 *
 *      \details  The file EthTrcv_30_Tja1100_Hw.c is the source file which contains the hardware independent parts of
 *                the implementation of the Ethernet transceiver driver for hardware access.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK in the module's header file
 *********************************************************************************************************************/

#define ETHTRCV_30_TJA1100_HW_SOURCE
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTrcv_30_Tja1100_Int.h"
# include "EthTrcv_30_Tja1100.h"
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# define ETHTRCV_30_TJA1100_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
/**********************************************************************************************************************
 *  LOCAL FUNCTION DECLARATION
 *********************************************************************************************************************/
/***********************************************************************************************************************
 *  EthTrcv_30_Tja1100_SetCl45AddrReg()
 **********************************************************************************************************************/
/*! \brief         Function to set the address register for the next access in the MMD ACCESS DATA register
 *  \details       -
 *  \param[in]     TrcvIdx     Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                             instances minus one.
 *  \param[in]     DeviceAddr  Device address for the MMD
 *  \param[in]     RegAddr     Address of the register to be set
 *  \return        RetVal      E_OK: Operation successful
 *                             E_NOT_OK: Operation not successful
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_HW_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetCl45AddrReg(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr);
/**********************************************************************************************************************
 *  LOCAL FUNCTION DEFINITION
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_SetCl45AddrReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_HW_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetCl45AddrReg(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr)
{
  Std_ReturnType retVal;
  uint16         AddressOp       = (uint16)(ETHTRCV_30_TJA1100_CL45_ADDRESS_OP                + DeviceAddr);
  uint16         DataNoPostIncOp = (uint16)(ETHTRCV_30_TJA1100_CL45_DATA_NO_POST_INCREMENT_OP + DeviceAddr);

  /* #10 Write the value for an address operation into the MMD ACCESS CONTROL register */
  retVal = EthTrcv_30_Tja1100_Internal_WriteTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_CL45_MMD_ACCESS_CONTROL,
      AddressOp);

  /* #20 Write the address of the register to be accessed into the MMD ACCESS ADDRESS DATA register */
  retVal |= EthTrcv_30_Tja1100_Internal_WriteTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_CL45_MMD_ACCESS_ADDRESS_DATA,
      RegAddr);

  /* #30 Write the operation code for "Data no post increment" into the MMD ACCESS CONTROL register */
  retVal |= EthTrcv_30_Tja1100_Internal_WriteTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_CL45_MMD_ACCESS_CONTROL,
      DataNoPostIncOp);

  return retVal;
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTION DEFINITION
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_Internal_ReadTrcvReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
    uint8 TrcvIdx,
    uint8 RegAddr,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) RegValPtr)
{
  EthTrcv_30_Tja1100_AccessEntityFctsIdxOfEthTrcvType accessEntityFctsIdx;

  accessEntityFctsIdx = EthTrcv_30_Tja1100_GetAccessEntityFctsIdxOfEthTrcv(TrcvIdx);

  /* #10 Call the pre-transceiver read access callout if it is configured */
  if(EthTrcv_30_Tja1100_GetPreTrcvReadAccessCalloutOfUserAccessCallouts(ETHTRCV_30_TJA1100_USER_CALLOUT_IDX) != NULL_PTR)
  {
    EthTrcv_30_Tja1100_GetPreTrcvReadAccessCalloutOfUserAccessCallouts(ETHTRCV_30_TJA1100_USER_CALLOUT_IDX)(TrcvIdx);   /* SBSW_ETHTRCV_FCT_PTR_OPT_CSL01 */
  }

  /* #20 Read the specified transceiver register */
  return EthTrcv_30_Tja1100_GetReadTrcvRegOfAccessEntityFcts(accessEntityFctsIdx)(                                      /* SBSW_ETHTRCV_DRVAPI_FCT_PTR_PARAM_PTR_PASS_MAN_CSL03 */
      EthTrcv_30_Tja1100_GetAccessEntitySnvOfEthTrcv(TrcvIdx),
      EthTrcv_30_Tja1100_GetAddressingIdxOfEthTrcv(TrcvIdx),
      RegAddr,
      RegValPtr);
}

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_Internal_WriteTrcvReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_WriteTrcvReg(
    uint8 TrcvIdx,
    uint8 RegAddr,
    uint16 RegVal)
{
  EthTrcv_30_Tja1100_AccessEntityFctsIdxOfEthTrcvType accessEntityFctsIdx;

  accessEntityFctsIdx = EthTrcv_30_Tja1100_GetAccessEntityFctsIdxOfEthTrcv(TrcvIdx);

  /* #10 Call the pre-transceiver write access callout if it is configured */
  if(EthTrcv_30_Tja1100_GetPreTrcvWriteAccessCalloutOfUserAccessCallouts(ETHTRCV_30_TJA1100_USER_CALLOUT_IDX) != NULL_PTR)
  {
    EthTrcv_30_Tja1100_GetPreTrcvWriteAccessCalloutOfUserAccessCallouts(ETHTRCV_30_TJA1100_USER_CALLOUT_IDX)(TrcvIdx);  /* SBSW_ETHTRCV_FCT_PTR_OPT_CSL01 */
  }

  /* #20 Write the specified transceiver register */
  return EthTrcv_30_Tja1100_GetWriteTrcvRegOfAccessEntityFcts(accessEntityFctsIdx)(                                     /* SBSW_ETHTRCV_DRVAPI_FCT_PTR_MAN_CSL03 */
      EthTrcv_30_Tja1100_GetAccessEntitySnvOfEthTrcv(TrcvIdx),
      EthTrcv_30_Tja1100_GetAddressingIdxOfEthTrcv(TrcvIdx),
      RegAddr,
      RegVal);
}

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_Internal_ReadCl45TrcvReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_ReadCl45TrcvReg(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) RegValPtr)
{
  Std_ReturnType retVal;

  /* #10 Enter the exclusive area to protect the indirect register access sequence */
  ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Set the address register to the register address to be read from */
  retVal = EthTrcv_30_Tja1100_SetCl45AddrReg(TrcvIdx, DeviceAddr, RegAddr);

  /* #30 Read the register value from the prepared register */
  retVal |= EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_CL45_MMD_ACCESS_ADDRESS_DATA,
      RegValPtr);                                                                                                       /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_PASS */

  /* #40 Leave the previously entered exclusive area */
  ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
}

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_Internal_WriteCl45TrcvReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_WriteCl45TrcvReg(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    uint16 RegVal)
{
  Std_ReturnType retVal;

  /* #10 Enter the exclusive area to protect the indirect register access sequence */
  ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Set the address register to the register address to be written to */
  retVal = EthTrcv_30_Tja1100_SetCl45AddrReg(TrcvIdx, DeviceAddr, RegAddr);
  
  /* #30 Write the given value into the prepared register */
  retVal |= EthTrcv_30_Tja1100_Internal_WriteTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_CL45_MMD_ACCESS_ADDRESS_DATA,
      RegVal);

  /* #40 Leave the previously entered exclusive area */
  ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
}
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_ReadTrcvReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadTrcvReg(
    uint8 TrcvIdx,
    uint8 RegAddr,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) RegValPtr)
{
  /* ----- Local Variables ----------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks -------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(RegValPtr == NULL_PTR)
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_POINTER;
  }
  else
# endif
  {
    /* #20 Call the internal interface to read a transceiver register */
    retVal = EthTrcv_30_Tja1100_Internal_ReadTrcvReg(TrcvIdx, RegAddr, RegValPtr);                                      /* SBSW_ETHTRCV_INT_FCT_PUB_PARAM_PTR_PASS */
  }
  /* ----- Development Error Report --------------------------------------*/
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_READ_TRCV_REG, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
}

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_WriteTrcvReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_WriteTrcvReg(
    uint8 TrcvIdx,
    uint8 RegAddr,
    uint16 RegVal)
{
  /* ----- Local Variables ----------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks -------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else
# endif
  {
    /* #20 Call the internal interface to write a transceiver register */
    retVal = EthTrcv_30_Tja1100_Internal_WriteTrcvReg(TrcvIdx, RegAddr, RegVal);
  }
  /* ----- Development Error Report --------------------------------------*/
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_WRITE_TRCV_REG, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
}
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_ReadCl45TrcvReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadCl45TrcvReg(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) RegValPtr)
{
  /* ----- Local Variables ----------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks -------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(RegValPtr == NULL_PTR)
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_POINTER;
  }
  else
# endif
  {
    /* #20 Call the internal interface to read a Clause 45 transceiver register */
    retVal = EthTrcv_30_Tja1100_Internal_ReadCl45TrcvReg(TrcvIdx, DeviceAddr, RegAddr, RegValPtr);                      /* SBSW_ETHTRCV_INT_FCT_PUB_PARAM_PTR_PASS */
  }
  /* ----- Development Error Report --------------------------------------*/
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_READ_CL45_TRCV_REG, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
}

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_WriteCl45TrcvReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_WriteCl45TrcvReg(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    uint16 RegVal)
{
  /* ----- Local Variables ----------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks -------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else
# endif
  {

    /* #20 Call the internal interface to write a Clause 45 transceiver register */
    retVal = EthTrcv_30_Tja1100_Internal_WriteCl45TrcvReg(TrcvIdx, DeviceAddr, RegAddr, RegVal);
  }
  /* ----- Development Error Report --------------------------------------*/
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_WRITE_CL45_TRCV_REG, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
}

# define ETHTRCV_30_TJA1100_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
