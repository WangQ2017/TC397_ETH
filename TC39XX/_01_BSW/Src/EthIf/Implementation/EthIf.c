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
/*!        \file  EthIf.c
 *        \brief  Ethernet Interface main source file
 *
 *      \details  Component to abstract the underlying Ethernet hardware for the upper layers to provide a generic
 *                interface to be used for controlling and communicate with the help of the Ethernet hardware
 *                provided by an ECU (Ethernet controller, Ethernet transceiver, Ethernet switch).
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

#define ETHIF_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1977
 *********************************************************************************************************/
#include "EthIf_EthCtrl_Int.h"
#include "EthIf_EthSwt_Int.h"
#include "EthIf_EthTrcv_Int.h"
#include "EthIf_Gw_Int.h"
#include "EthIf_Link_Int.h"
#include "EthIf_Mirror_Int.h"
#include "EthIf_Mode_Int.h"
#include "EthIf_Rx_Int.h"
#include "EthIf_Stats_Int.h"
#include "EthIf_Tx_Int.h"
#include "EthIf_Utils_Int.h"
#include "EthIf_ZeroCopy_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Check the version of EthIf header file */
/* \trace SPEC-2393557 */
#if (  (ETHIF_SW_MAJOR_VERSION != (15u)) \
    || (ETHIF_SW_MINOR_VERSION != (0u)) \
    || (ETHIF_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthIf.c and EthIf.h are inconsistent"
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

#if !defined (ETHIF_SOURCE_LOCAL)                                                                                       /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_SOURCE_LOCAL static
#endif

#if !defined (ETHIF_SOURCE_LOCAL_INLINE)                                                                                /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_SOURCE_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define ETHIF_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(EthIf_StateType, ETHIF_VAR_INIT)  EthIf_ModuleInitialized = ETHIF_STATE_UNINIT;

#define ETHIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define ETHIF_START_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

CONST(uint8, ETHIF_CONST) EthIf_BroadcastMac[ETH_PHYS_ADDR_LEN_BYTE] = { 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFF, 0xFFU }; /* PRQA S 1533 */ /* MD_EthIf_1533_BroadcastMac */

#define ETHIF_STOP_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL DATA
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
 *  EthIf_InitMemory
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_InitMemory( void )
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set module initialization state to UNINIT */
  EthIf_ModuleInitialized = ETHIF_STATE_UNINIT;
} /* EthIf_InitMemory() */

/**********************************************************************************************************************
 *  EthIf_Init
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
FUNC(void, ETHIF_CODE) EthIf_Init(
  P2CONST(EthIf_ConfigType, AUTOMATIC, ETHIF_INIT_DATA) CfgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  /* Check initialization state of the component */
  if (EthIf_ModuleInitialized != ETHIF_STATE_UNINIT)
  {
    errorId = ETHIF_E_INIT_FAILED;
  }
  /* #20 Check input parameters for plausibility */
  /* Check parameter 'ConfigPtr' */
  else if (CfgPtr == NULL_PTR)
  {
    /* \trace SPEC-2393577 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
#endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Set configuration pointer */
    EthIf_ConfigDataPtr = CfgPtr;

    /* #40 Initialize sub-modules */
    EthIf_EthCtrl_Init();
    EthIf_EthSwt_Init();
    EthIf_EthTrcv_Init();
    EthIf_Gw_Init();
    EthIf_Link_Init();
    EthIf_Mirror_Init();
    EthIf_Mode_Init();
    EthIf_Rx_Init();
    EthIf_Stats_Init();
    EthIf_Tx_Init();
    EthIf_Utils_Init();
    EthIf_ZeroCopy_Init();

    /* #50 Set module state to initialized */
    EthIf_ModuleInitialized = ETHIF_STATE_INIT; /* \trace SPEC-2393576 */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #60 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_INIT, errorId);
  }
#else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
} /* EthIf_Init() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if ( ETHIF_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  EthIf_GetVersionInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, ETHIF_APPL_VAR)  VersionInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check input parameters for plausibility */
  if( VersionInfoPtr == NULL_PTR )
  {
    /* \trace SPEC-2393650 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Retrieve version information */
    VersionInfoPtr->vendorID = ETHIF_VENDOR_ID;                                                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
    VersionInfoPtr->moduleID = ETHIF_MODULE_ID;                                                                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
    VersionInfoPtr->sw_major_version = ETHIF_SW_MAJOR_VERSION;                                                          /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
    VersionInfoPtr->sw_minor_version = ETHIF_SW_MINOR_VERSION;                                                          /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
    VersionInfoPtr->sw_patch_version = ETHIF_SW_PATCH_VERSION;                                                          /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_VERSION_INFO, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

} /* EthIf_GetVersionInfo() */
#endif /* ETHIF_VERSION_INFO_API */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* module specific MISRA deviations:

  MD_EthIf_310_Buffer:
    Reason:     Cast from Eth_DataType to uint8 for platform independent access to Ethernet buffer data.
    Risk:       Casting of pointers to uint8 elements without taking alignment into account may result
                in unaligned memory access exceptions on certain platforms.
    Prevention: Buffers passed to the function need to be 4 byte aligned and review check for aligned usage
                of buffer.

  MD_EthIf_311_Buffer:
    Reason:     Eth driver API is defined to get access to variable data. However the calling function is designed
                to not alter any data of the buffer but just pass it. Therefore it was decided to define the data
                in context of EthIf as const and cast it to its "real" type when calling the drivers' API.
    Risk:       Passing constant data that can't be accessed with write operations and therefore could result in
                an exception.
    Prevention: Covered by code review.

  MD_EthIf_3219:
    Reason:     This function is inlined and therefore it has to be implemented here. The function is not used
                by all implementation files which include this header file.
    Risk:       None.
    Prevention: None.

  MD_EthIf_3305_Buffer:
    Reason:     API of lower layer uses Eth_DataType as type of pointer to the data buffer and therefore the cast
                is needed to pass the data.
    Risk:       Risk of an unaligned memory access exception on certain platforms.
    Prevention: Covered by code review.

  MD_EthIf_3382:
    Reason:     AUTOSAR API passes the pointer to the payload portion relevant for the upper layer. EthIf however
                must pass the pointer to the Ethernet payload portion to the Ethernet driver and must therefore
                take the VLAN-tag (which is transparent for the upper layer) into account. This results in the need
                to adapt the pointer in case of a included Q-Tag by negative pointer arithmetic.
    Risk:       If upper layer passes a pointer to a payload embedded into an Ethernet frame not including a Q-Tag
                will result in passing a wrong pointer to the Ethernet driver.
    Prevention: Must be covered by code review/run time tests of upper layer.

  MD_EthIf_3415:
    Reason:     Optimization of evaluation of if condition. The function call shall only be done if first condition
                isn't true.
    Risk:       Because function doesn't alter any state of the module but is a second condition that must only be
                checked if the first one isn't fulfilled the lazy evaluation applied by the compiler has no effect.
    Prevention: No need for prevention.

  MD_EthIf_3673:
    Reason:     Type of parameter is specified by AUTOSAR and cannot be changed to const.
    Risk:       Caller of function isn't able to optimize memory usage by placing the respective variable in
                ROM.
    Prevention: No need for prevention.

  MD_EthIf_1336:
    Reason:     MCAL drivers might (dependent on their supported AUTOSAR version) use different identifiers. Therefore
                explicitly giving a function parameter identifier in the function pointer declaration was omitted.
    Risk:       None.
    Prevention: None.

  MD_EthIf_2991:
    Reason:     Configuration related condition that might be constant.To avoid configuration related handling here
                but do it only where needed the constant evaluation is accepted.
    Risk:       None.
    Prevention: None.

  MD_EthIf_2995:
    Reason:     Configuration related condition that might be constant.To avoid configuration related handling here
                but do it only where needed the constant evaluation is accepted.
    Risk:       None.
    Prevention: None.

  MD_EthIf_2985:
    Reason:     The return value of the previous function call is configuration dependent. There might be configurations
                where the call always evaluates to E_OK and therefore will result in a warning here. To omit configuration
                related handling here this warning is accepted.
    Risk:       None.
    Prevention: None.

  MD_EthIf_1533_BroadcastMac:
    Reason:     Constant is used by multiple functions but there might be the case, that it is only used once
                dependent on the configuration. However, to avoid configuraiton awareness here the constant is given
                as a public constant.
    Risk:       None.
    Prevention: Constant is only declared as external in the EthIf_Int.h internal header that isonly used by EthIf
                itself.
*/

/* COV_JUSTIFICATION_BEGIN

   \ID COV_ETHIF_LOCAL_INLINE
     \ACCEPT TX
     \REASON [MSR_COV_COMPATIBILITY]

   \ID COV_ETHIF_UNIT_TEST
     \ACCEPT TX
     \REASON Function definitions are only removed for unit testing with ceedling due to mock generation.

   \ID COV_ETHIF_SAFE_FEAT
     \ACCEPT TX
     \REASON Feature must be enabled for an ASIL qualified configuration. MSSV plugin ensures that feature is turned on.

   \ID COV_ETHIF_QM_FEAT_CHECK_ON
     \ACCEPT XF
     \ACCEPT XF xf xf
     \REASON QM feature must not be turned on for an ASIL qualified configuration. MSSV plugin ensures that feature is turned off.

   \ID COV_ETHIF_QM_FEAT_INNER
     \ACCEPT XX
     \REASON Feature that is encapsulated in a QM feature that is turned off for an ASIL qualified configuration.

   COV_JUSTIFICATION_END */

/* SBSW_JUSTIFICATION_BEGIN

   \ID SBSW_ETHIF_COMMON_CFG_PTR_INT_FCT_CALL_CONV
     \DESCRIPTION Access of variable through configuration pointer.
     \COUNTERMEASURE \N Accessing the variable through configuration pointer is only done when configuration pointer is
                        already initialized (as denoted as pre-condition in CDD).

   \ID SBSW_ETHIF_COMMON_CFG_PTR_INT_FCT_PREV_MODULE_INIT_CHECK
     \DESCRIPTION Access of variable through configuration pointer.
     \COUNTERMEASURE \R Accessing the variable through configuration pointer is only called after
                        callers have checked that module has been initialized, which indicates that configuration
                        pointer is valid.

   \ID SBSW_ETHIF_COMMON_CSL01
     \DESCRIPTION Access of generated data by usage of index defined by ComStackLib using ComStackLib.
     \COUNTERMEASURE \N [CM_ETHIF_CSL01]

   \ID SBSW_ETHIF_COMMON_CSL03
     \DESCRIPTION Access of generated data by usage of indirection index defined by ComStackLib using ComStackLib.
     \COUNTERMEASURE \N [CM_ETHIF_CSL03]

  \ID SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_WITH_PUB_PARAM_PTR_CSL03
     \DESCRIPTION Access of a mandatory function pointer of driver API abstraction using ComStackLib and passing a
                  parameter pointer of a public API.
     \COUNTERMEASURE \S [CM_ETHIF_FCT_PTR_CSL03]
                     \R [CM_ETHIF_PUB_PARAM_PTR_CHECK]

   \ID SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_WITH_REF_OF_STACK_VAR_PARAM_PTR_CSL03
     \DESCRIPTION Access of a mandatory function pointer of driver API abstraction using ComStackLib and passing a
                  parameter pointer generated by referencing a stack variable.
     \COUNTERMEASURE \S [CM_ETHIF_FCT_PTR_CSL03]
                        Parameter pointer doesn't need counter measure due to [CM_ETHIF_REF_OF_STACK_VAR]

   \ID SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_WITH_INT_PARAM_PTR_CSL03
     \DESCRIPTION Access of a mandatory function pointer of driver API abstraction using ComStackLib and passing a
                  parameter pointer provided during call of internal function.
     \COUNTERMEASURE \S [CM_ETHIF_FCT_PTR_CSL03]
                        Parameter pointer doesn't need counter measure due to [CM_ETHIF_CALLER_PARAM_PTR]

   \ID SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_CSL03
     \DESCRIPTION Access of a mandatory function pointer of driver API abstraction using ComStackLib.
     \COUNTERMEASURE \S [CM_ETHIF_FCT_PTR_CSL03]

   \ID SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03
     \DESCRIPTION Access of a optional function pointer of driver API abstraction using ComStackLib and passing a
                  parameter pointer of a public API.
     \COUNTERMEASURE \S [CM_ETHIF_FCT_PTR_CSL03]
                     \R [CM_ETHIF_FCT_PTR_OPT_CSL03]
                     \R [CM_ETHIF_PUB_PARAM_PTR_CHECK]

   \ID SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_INT_PARAM_PTR_CSL03
     \DESCRIPTION Access of a optional function pointer of driver API abstraction using ComStackLib and passing a
                  parameter pointer provided during call of internal function.
     \COUNTERMEASURE \S [CM_ETHIF_FCT_PTR_CSL03]
                     \R [CM_ETHIF_FCT_PTR_OPT_CSL03]
                        Parameter pointer doesn't need counter measure due to [CM_ETHIF_CALLER_PARAM_PTR]

   \ID SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_REF_OF_STACK_VAR_PARAM_PTR_CSL03
     \DESCRIPTION Access of a optional function pointer of driver API abstraction using ComStackLib and passing a
                  parameter pointer generated by referencing a stack variable.
     \COUNTERMEASURE \S [CM_ETHIF_FCT_PTR_CSL03]
                     \R [CM_ETHIF_FCT_PTR_OPT_CSL03]
                        Parameter pointer doesn't need counter measure due to [CM_ETHIF_REF_OF_STACK_VAR]

   \ID SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03
     \DESCRIPTION Access of optional function pointer of driver API abstraction using ComStackLib.
     \COUNTERMEASURE \S [CM_ETHIF_FCT_PTR_CSL03]
                     \R [CM_ETHIF_FCT_PTR_OPT_CSL03]

   \ID SBSW_ETHIF_USERAPI_FCT_PTR_CSL01
     \DESCRIPTION Access of a function pointer of user API abstraction using ComStackLib.
     \COUNTERMEASURE \S Index according to [CM_ETHIF_CSL01] used to resolve respective function-pointer,
                        signature of function used to define function-pointer checked by compiler and user must check
                        generated function-pointer according to SMI-8.

\ID SBSW_ETHIF_USERAPI_FCT_PTR_CSL03
     \DESCRIPTION Access of a function pointer of user API abstraction using ComStackLib.
     \COUNTERMEASURE \S [CM_ETHIF_FCT_PTR_CSL03]

   \ID SBSW_ETHIF_USERAPI_FCT_PTR_WITH_INT_PARAM_PTR_CSL03
     \DESCRIPTION Access of a function pointer of user API abstraction using ComStackLib and passing internal
                  parameter pointer.
     \COUNTERMEASURE \S [CM_ETHIF_FCT_PTR_CSL03]
                        Parameter pointer doesn't need counter measure due to [CM_ETHIF_CALLER_PARAM_PTR]

   \ID SBSW_ETHIF_USERAPI_FCT_PTR_WITH_PUB_PARAM_PTR_CSL03
     \DESCRIPTION Access of a function pointer of user API abstraction using ComStackLib and passing public
                  parameter pointer.
     \COUNTERMEASURE \S [CM_ETHIF_FCT_PTR_CSL03]
                     \R [CM_ETHIF_PUB_PARAM_PTR_CHECK]

   \ID SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE
     \DESCRIPTION Write access to an object referenced by a function parameter passed to a public API.
     \COUNTERMEASURE \R [CM_ETHIF_PUB_PARAM_PTR_CHECK]

   \ID SBSW_ETHIF_INT_FCT_IDX_PASS
     \DESCRIPTION Write access to data using index passed as function argument during call of an internal function.
     \COUNTERMEASURE \N Check for validity of a index with respect to the value range defined in CDD is done before the
                        function is called and the index is passed according to [CM_ETHIF_CSL01] or [CM_ETHIF_CSL03].

   \ID SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE
     \DESCRIPTION Write access to an object referenced by a function parameter passed to an internal function.
     \COUNTERMEASURE \N [CM_ETHIF_CALLER_PARAM_PTR]

   \ID SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS
     \DESCRIPTION Passing a pointer provided during a call to a function as parameter to an internal function.
     \COUNTERMEASURE \N [CM_ETHIF_CALLER_PARAM_PTR]

   \ID SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_PASS
     \DESCRIPTION Passing a pointer provided during a call to a public function as parameter to an internal function.
     \COUNTERMEASURE \R [CM_ETHIF_PUB_PARAM_PTR_CHECK]

   \ID SBSW_ETHIF_INT_FCT_PARAM_PTR_NULL_CSL_STRUCT_MEM_CSL03
     \DESCRIPTION The function passes a function parameter of type NULL pointer to a ComStackLib function that sets
                  a struct member of an element of an array.
     \COUNTERMEASURE \N NULL pointer is a valid value for the member and access is valid according to [CM_ETHIF_CSL03].

   \ID SBSW_ETHIF_INT_FCT_PARAM_PTR_CSL_STRUCT_MEM_CSL03
     \DESCRIPTION Usage of a pointer provided during a call to a function from a ComStackLib function that sets a struct
                  member of an element of an array.
     \COUNTERMEASURE \N [CM_ETHIF_CALLER_PARAM_PTR] and [CM_ETHIF_CSL03].

   \ID SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR
     \DESCRIPTION Passing a pointer provided during a call to a function and a pointer to a stack variable as parameter
                  to an internal function.
     \COUNTERMEASURE \N [CM_ETHIF_CALLER_PARAM_PTR] and [CM_ETHIF_REF_OF_STACK_VAR]

   \ID SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR
     \DESCRIPTION Passing a pointer provided during a call to a function and a pointer to a stack variable as parameter
                  to an internal function.
     \COUNTERMEASURE \R [CM_ETHIF_PUB_PARAM_PTR_CHECK]
                        Parameter pointer doesn't need counter measure due to [CM_ETHIF_REF_OF_STACK_VAR]

   \ID SBSW_ETHIF_REF_OF_STACK_VAR
     \DESCRIPTION Pointer to stack variable passed as function argument.
     \COUNTERMEASURE \N [CM_ETHIF_REF_OF_STACK_VAR]

   \ID SBSW_ETHIF_STACK_PARAM_PTR
     \DESCRIPTION Pointer located on stack with immediate value assignment passed to function.
     \COUNTERMEASURE \N Pointer is generated by allocating it on stack and immediatelly assigning a target to it.

   \ID SBSW_ETHIF_CONST_VAR_PTR
     \DESCRIPTION  Pointer to constant variable passed as function argument.
     \COUNTERMEASURE \N Constant and pointer to it are defined during compile/link.

   \ID SBSW_ETHIF_TX_BUF_PTR_PASS
     \DESCRIPTION Pointer to Ethernet transmission buffer is passed as function argument.
     \COUNTERMEASURE \R Check of return value of tranmission buffer provision API. Calling convention is that if API
                        returns BUF_REQ_OK the returned pointer is valid and can be used.

   \ID SBSW_ETHIF_VLAN_TAG_WRITE
     \DESCRIPTION Write access to an array passed as pointer to insert VLAN tag into Ethernet TX buffer over a range
                  of 4 byte.
     \COUNTERMEASURE \N [CM_ETHIF_CALLER_PARAM_PTR]

   \ID SBSW_ETHIF_PREPARE_VLAN_TAG_PTR_PASS
     \DESCRIPTION Passing parameter pointers for insertion of VLAN tag to EthIf_PrepareVlanTag().
     \COUNTERMEASURE \R It is ensured during TX buffer provision due to request of additional buffer length for
                        insertion of the VLAN tag that the Ethernet TX buffer returned by the driver has at least
                        these 4 bytes left at the position passed to insert the VLAN tag.
                        Parameter pointer doesn't need counter measure due to [CM_ETHIF_CALLER_PARAM_PTR]

   \ID SBSW_ETHIF_FRAME_ID_PTR_WRITE
     \DESCRIPTION Bytes-wise write access using pointer to a stack variable of type Eth_FrameIdType
     \COUNTERMEASURE \R Pointer is assigned to start address of the variable. Index and amount of bytes to be written
                        are derived by retrieving number of allocated bytes for a variable of type Eth_FrameIdType by
                        using the sizeof(EthFrameIdType) operator.

   \ID SBSW_ETHIF_TX_CONTEXT_IDX_CALL_CONV
     \DESCRIPTION Access to pointer retrieved through ComStackLib by using an index for the tx context elements which
                  is retrieved by calling EthIf_CalcTxCtxtIdx().
     \COUNTERMEASURE \R [CM_ETHIF_TX_CONTEX_IDX]

   \ID SBSW_ETHIF_TX_CONTEXT_IDX_CALL_CONV_AND_PARAM_PTR_PASS
     \DESCRIPTION Access to pointer retrieved through ComStackLib by using an index for the tx context elements which
                  is retrieved by calling EthIf_CalcTxCtxtIdx() and passing a parameter pointer.
     \COUNTERMEASURE \R [CM_ETHIF_TX_CONTEX_IDX]
                        Parameter pointer doesn't need counter measure due to [CM_ETHIF_CALLER_PARAM_PTR]

   \ID SBSW_ETHIF_TX_CONTEXT_FCT_CSL_MEM_PTR_PASS_WITH_FCT_PARAM_IDX
     \DESCRIPTION Passing of a pointer provided by the ComStackLib when accessing a tx context element with an given
                  index passed as function parameter to a function.
     \COUNTERMEASURE \R [CM_ETHIF_CALLER_IDX_RANGE_CDD] according to [CM_ETHIF_TX_CONTEX_IDX]

   \ID SBSW_ETHIF_CSL_STRUCT_MEM_PARAM_IDX_MEASUREMENT_DATA
     \DESCRIPTION Accessing a measurement data structure member from ComStackLib by a constant macro index.
     \COUNTERMEASURE \N [CM_ETHIF_MEASUREMENT_DATA_IDX]

   \ID SBSW_ETHIF_CSL_MEM_PTR_PASS_MEASUREMENT_DATA
     \DESCRIPTION Passing of a pointer provided by the ComStackLib when accessing a measurement data structure element.
     \COUNTERMEASURE \N [CM_ETHIF_MEASUREMENT_DATA_IDX]

   \ID SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_AND_CSL_MEM_PTR_PASS_MEASUREMENT_DATA
     \DESCRIPTION Passing a pointer provided during a call to a public function as parameter to an internal function
                  and passing of a pointer provided by the ComStackLib when accessing a measurement data structure
                  element.
     \COUNTERMEASURE \N For the public function parameter pass [CM_ETHIF_CALLER_PARAM_PTR]
                        For the pointer provided by CSL [CM_ETHIF_MEASUREMENT_DATA_IDX]

   \ID SBSW_ETHIF_CSL_PTR_WRITE_TX_CONTEXT_IDX_CALL_CONV
     \DESCRIPTION Write access to a pointer of a tx context element returned by ComStackLib with a index given by
                  EthIf_CalcTxCtxtIdx().
     \COUNTERMEASURE \R [CM_ETHIF_TX_CONTEX_IDX]

   \ID SBSW_ETHIF_CSL_PTR_WRITE_TX_CONTEXT_IDX_WITH_FCT_PARAM_IDX
     \DESCRIPTION Write access to a pointer of a tx context element returned by ComStackLib with an given index passed
                  as function parameter to a function.
     \COUNTERMEASURE \R [CM_ETHIF_CALLER_IDX_RANGE_CDD] according to [CM_ETHIF_TX_CONTEX_IDX]

   \ID SBSW_ETHIF_CSL_IDX_RET_BY_FCT
     \DESCRIPTION Access with a ComStackLib index returned by a function using ComStackLib.
     \COUNTERMEASURE \R Check result of API call to verify if index returned by API is allowed to be used.

   \ID SBSW_ETHIF_CSL_IDX_STORED
     \DESCRIPTION Access with a ComStackLib index stored in a variable.
     \COUNTERMEASURE \R Check for validity of the index was done before it was stored according to [CM_ETHIF_CSL01]
                        or [CM_ETHIF_CSL03]. Storage is always done before usage between the public API that is
                        called and the location the index is used for access by utilizing the respective Setter function.

   \ID SBSW_ETHIF_SWT_TS_TX_CTXT_PARAM_PTR_PASS
     \DESCRIPTION Passing a pointer stored in a switch timestamp tx context element to a function.
     \COUNTERMEASURE \R State of element where respective pointer is valid is checked before passing the pointer.

   \ID SBSW_ETHIF_NON_SAFE_REF_OF_ARRAY_ELEM
     \DESCRIPTION Pointer to array element passed as function argument.
     \COUNTERMEASURE \M MSSV plugin ensures that code isn't active in a SafeBSW environment by checking the precompile
                        switch encapsulating the code.

   SBSW_JUSTIFICATION_END */

/*

  \CM CM_ETHIF_CSL01 Qualified use-case CSL01 of ComStackLib.

  \CM CM_ETHIF_CSL03 Qualified use-case CSL03 of ComStackLib.

  \CM CM_ETHIF_FCT_PTR_CSL03 Index according to [CM_ETHIF_CSL03] used to resolve respective function-pointer,
                             signature of function used to define function-pointer checked by compiler and user must
                             check generated function-pointer according to SMI-8.

  \CM CM_ETHIF_FCT_PTR_OPT_CSL03 In addition to [CM_ETHIF_FCT_PTR_CSL03] the function pointer is checked for being not
                                 NULL pointer (what indicates that function isn't present) before calling the function
                                 by using the function pointer.

  \CM CM_ETHIF_PUB_PARAM_PTR_CHECK Parameter pointer provided to public API is checked for not being NULL pointer before
                                   usage.

  \CM CM_ETHIF_CALLER_PARAM_PTR The caller of the function passing the pointer to the other function ensures that the
                                pointer is valid according to functions CDD.

  \CM CM_ETHIF_CALLER_IDX_RANGE_CDD The caller of the function passing the index to the other function ensures that the
                                    index is within the range given in CDD.

  \CM CM_ETHIF_REF_OF_STACK_VAR Pointer is generated by referencing a stack variable by the address operator.

  \CM CM_ETHIF_TX_CONTEX_IDX Index returned by EthIf_CalcTxCtxtIdx() is always inbounds of array when the function is
                             called according to the range defintions for its parameters defined in the CDD. This check
                             is performed in call tree between the call to an respective EthIf public API and
                             EthIf_CalcTxCtxtIdx().

  \CM CM_ETHIF_MEASUREMENT_DATA_IDX Due to CSL limitation a workaround is applied to generate an array of size one for
                                    the measurement data structure. Therefore the index is fixed to 0 and defined as
                                    constant macro. According to C standard zero size array declarations are not
                                    allowed.
 */

/**********************************************************************************************************************
 *  END OF FILE: EthIf.c
 *********************************************************************************************************************/

