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
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IpBase.c
 *      Project:  MICROSAR ETH
 *    Component:  SysService_IpBase
 *       Module:  MICROSAR IP Base
 *    Generator:  None
 *
 *  Description:  Implementation
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
#define IPBASE_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/*lint -e451 */ /* LD_IpBase_451 */
#include "IpBase.h"           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#include "IpBase_Priv.h"

/**********************************************************************************************************************
 *  CONSISTENCY CHECK
 *********************************************************************************************************************/
/* Check consistency of source and header file. */
#if ( (IPBASE_SW_MAJOR_VERSION != 04u) \
   || (IPBASE_SW_MINOR_VERSION != 00u) \
   || (IPBASE_SW_PATCH_VERSION != 07u) )
# error "Vendor specific version numbers of IpBase.c and IpBase.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#define IPBASE_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  IpBase_GetVersionInfo
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_FUNCCODE(void) IpBase_GetVersionInfo( IPBASE_P2VARAPPLDATA(Std_VersionInfoType) VersionInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check VersionInfoPtr for NULL pointer */
  if ( VersionInfoPtr == NULL_PTR )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Set vendor ID, module ID, major+minor+patch version */
    VersionInfoPtr->vendorID = (IPBASE_VENDOR_ID);                /* SBSW_IPBASE_GETVERSION_PARAM */
    VersionInfoPtr->moduleID = (IPBASE_MODULE_ID);                /* SBSW_IPBASE_GETVERSION_PARAM */
    VersionInfoPtr->sw_major_version = (IPBASE_SW_MAJOR_VERSION); /* SBSW_IPBASE_GETVERSION_PARAM */
    VersionInfoPtr->sw_minor_version = (IPBASE_SW_MINOR_VERSION); /* SBSW_IPBASE_GETVERSION_PARAM */
    VersionInfoPtr->sw_patch_version = (IPBASE_SW_PATCH_VERSION); /* SBSW_IPBASE_GETVERSION_PARAM */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #30 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_GET_VERSION_INFO, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif
} /* IpBase_GetVersionInfo() */

#define IPBASE_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:
 MD_IpBase_310_SockPtr:
      Reason:     Type cast for socket pointer
      Risk:       Memory Access violation
      Prevention: Covered by integration tests
 MD_IpBase_4391:
      Reason:     Type cast to wider type
      Risk:       Enlarged code size
      Prevention: Covered by code review
 MD_IpBase_3218:
      Reason:     Global static variable used in one function only
      Risk:       Variable may be used within unintended functions of the module
      Prevention: Covered by code review
 MD_IpBase_1039:
      Reason:     Array with dummy length of 1 for socket address
      Risk:       Variable may be used within the module
      Prevention: Covered by code review
 MD_IpBase_2981:
      Reason:     Redundant variable initialization
      Risk:       Small runtime impact
      Prevention: No mitigation
*/
/* Justification for module-specific PCLINT deviations:
 LD_IpBase_451:
      Reason:     AUTOSAR MemMap
      Risk:       Uncritical
      Prevention: Covered by code review
*/
/* SBSW_JUSTIFICATION_BEGIN
  \ID SBSW_IPBASE_GETVERSION_PARAM
    \DESCRIPTION      The IpBase_GetVersionInfo writes to the 'VersionInfoPtr' pointer parameter. It is checked against
                      NULL, but this does not guarantee that the referenced memory is valid.
    \COUNTERMEASURE   \N  Pointers passed to public IpBase APIs point to a valid memory range.
                          A general countermeasure is included in the safety manual.

  \ID SBSW_IPBASE_VALID_API_POINTER
    \DESCRIPTION      Write access to element which is passed as function argument.
    \COUNTERMEASURE   \N  It is assumed, that the input pointer is valid and the function only writes members of the
                          pointed struct.

  \ID SBSW_IPBASE_PASSING_API_POINTER
    \DESCRIPTION      Pointer is passed as function argument.
    \COUNTERMEASURE   \N  Pointer was passed as function argument and is used to call sub-function.
                          The validity of the pointer has to be ensured by the caller.

  \ID SBSW_IPBASE_API_ARGUMENT_IDX
    \DESCRIPTION      Access of array element with index given as function argument is not checked for validity.
    \COUNTERMEASURE   \N  The valid range of the function argument is defined at the function declaration and has to be
                          ensured by the calling function.

  \ID SBSW_IPBASE_API_ARGUMENT_LEN
    \DESCRIPTION      Access of array element with index limited by function argument is not checked for validity.
    \COUNTERMEASURE   \N  The valid limit of the function argument is defined at the function declaration and has to be
                          ensured by the calling function.

  \ID SBSW_IPBASE_REFERENCE_OF_VARIABLE
    \DESCRIPTION      Pointer to variable is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is generated by referencing a variable by the address operator.

  \ID SBSW_IPBASE_REFERENCE_OF_POINTER_ELEMENT
    \DESCRIPTION      Pointer is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is generated by referencing a member of a struct passed as reference function
                          argument. The validity of the function argument has to be ensured by the caller.

  \ID SBSW_IPBASE_BER_REFERENCE_OF_POINTER_ELEMENT
    \DESCRIPTION      Pointer is passed as function argument and used to parse BER document.
    \COUNTERMEASURE   \N  Pointer is generated by referencing a member of a struct passed as reference function
                          argument to parse BER document. The validity of the BER document has to be ensured by the
                          caller.

  \ID SBSW_IPBASE_API_ZERO_TERMINATED_STRING
    \DESCRIPTION      Access of an array element with index which is not checked for validity.
    \COUNTERMEASURE   \N  The string has to be terminated by '\0'. The string termination has to be ensured by the
                          caller.

  \ID SBSW_IPBASE_API_STRING_TARGET_FOR_DATA
    \DESCRIPTION      Access of an array element with index which is not checked for validity.
    \COUNTERMEASURE   \N  The string has to be large enough to store parameter limited number of characters.
                          The string length has to be ensured by the caller.

  \ID SBSW_IPBASE_INT_DIGIT_MAX
    \DESCRIPTION      Access of an array element with index which is not checked for validity.
    \COUNTERMEASURE   \N  The definition of IPBASE_INT_DIGIT_MAX has to be large enough to store all digits of uint32
                          parameter IntVal.

  \ID SBSW_IPBASE_FUNCTION_CALL
    \DESCRIPTION      Function is called.
    \COUNTERMEASURE   \N  The implementation passes all arguments into a function.
                          It has to be ensured that the called funtion provides the same or higher safety level as the
                          caller.

  \ID SBSW_IPBASE_BASE64_ENCODED_BLOCK_LEN
    \DESCRIPTION      Access of target data pointer with index is not checked for validity.
    \COUNTERMEASURE   \N  The valid size of the function argument is defined as IPBASE_CODE_BASE64_CODED_BLOCK_LEN and
                          has to be ensured by the calling function.

SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION
  \ID COV_IPBASE_BYTE_ORDER
    \ACCEPT   TX
    \ACCEPT   XF
    \REASON   Tests are executed on Windows thus the byte order can not be changed
END_COVERAGE_JUSTIFICATION */
/**********************************************************************************************************************
 *  END OF FILE: IpBase.c
 *********************************************************************************************************************/
