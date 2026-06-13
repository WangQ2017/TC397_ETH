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
/*!        \file  LdCom.h
 *        \brief  MICROSAR Efficient COM for Large Data
 *
 *      \details  Header
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Sebastian Waldvogel           visswa        Vector Informatik GmbH
 *  Florian Roehm                 visfrm        Vector Informatik GmbH
 *  Gunnar Meiss                  visms         Vector Informatik GmbH
 *  Sylvia Schlag                 visssg        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  1.00.00   2014-05-13  visswa  ESCAN00074101 AR4-665: Efficient COM for Large Data
 *  2.00.00   2016-01-25  visfrm  ESCAN00087729 FEAT-780: Release of FEAT-698 (Large Data COM) [AR4-987]
 *  2.00.01   2017-08-03  visms   ESCAN00096166 Compiler warning: LdCom_Init warning C4100: config : unreferenced formal parameter
 *  3.00.00   2018-05-15  visssg  STORYC-4404   MISRA-C:2012 LdCom
 *  3.01.00   2020-05-11  visfrm  COM-1543      Support Helix QAC 2019-2
 *********************************************************************************************************************/

#if !defined (LDCOM_H)
# define LDCOM_H
/**********************************************************************************************************************
 * MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* *INDENT-OFF* */
/* *INDENT-ON* */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "LdCom_Cfg.h"
# if(LDCOM_DEV_ERROR_REPORT == STD_ON)
#  include "Det.h"
# endif
# include "LdCom_Lcfg.h"
# include "LdCom_PBcfg.h"
# include "PduR_LdCom.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*!
  \defgroup  LdComIdentification LdCom Identification
  \brief  Vendor and module identification of this implementation.
  \{
*/
# define LDCOM_VENDOR_ID              30u              /**< the vendor ID of this implementation. */
# define LDCOM_MODULE_ID              49u              /**< the module ID of this implementation. */
/*!
  \}
*/

/*!
  \defgroup  LdComSWVersion LdCom version number
  \brief  Version number of this implementation.
  \{
*/
# define LDCOM_SW_MAJOR_VERSION       3u
# define LDCOM_SW_MINOR_VERSION       1u
# define LDCOM_SW_PATCH_VERSION       0u
/*!
  \}
*/

/*!
  \defgroup  LdComARReleaseVersion LdCom AUTOSAR release version number
  \brief  Version number of AUTOSAR release on which the appropriate implementation is based on.
  \{
*/
# define LDCOM_AR_RELEASE_MAJOR_VERSION       4u
# define LDCOM_AR_RELEASE_MINOR_VERSION       2u
# define LDCOM_AR_RELEASE_REVISION_VERSION    2u
/*!
  \}
*/

# define LDCOM_INSTANCE_ID_DET                   0u  /**< this code is used to detect that no error occurred. Det_ReportError() is not called.  */

/*!
  \defgroup ServiceIDs Service IDs
  \brief    Service IDs as reported to DET.
  \{
*/
# define LDCOM_SID_INIT                          0x01u  /**< API Service ID: LdCom_Init() */
# define LDCOM_SID_DE_INIT                       0x02u  /**< API Service ID: LdCom_DeInit() */
# define LDCOM_SID_GET_VERSION_INFO              0x03u  /**< API Service ID: LdCom_GetVersionInfo() */
# define LDCOM_SID_TRANSMIT                      0x05u  /**< API Service ID: LdCom_Transmit() */

/* Interface */
# define LDCOM_SID_RX_INDICATION                 0x42u  /**< API Service ID: LdCom_RxIndication() */
# define LDCOM_SID_TRIGGER_TRANSMIT              0x41u  /**< API Service ID: LdCom_TriggerTransmit() */
# define LDCOM_SID_TX_CONFIRMATION               0x40u  /**< API Service ID: LdCom_TxConfirmation() */

/* TP */
# define LDCOM_SID_COPY_TX_DATA                  0x43u  /**< API Service ID: LdCom_CopyTxData() */
# define LDCOM_SID_TP_TX_CONFIRMATION            0x48u  /**< API Service ID: LdCom_TpTxConfirmation() */
# define LDCOM_SID_START_OF_RECEPTION            0x46u  /**< API Service ID: LdCom_StartOfReception() */
# define LDCOM_SID_COPY_RX_DATA                  0x44u  /**< API Service ID: LdCom_CopyRxData() */
# define LDCOM_SID_TP_RX_INDICATION              0x45u  /**< API Service ID: LdCom_TpRxIndication() */
/*!
  \}
*/

/* ---- DET independent Error Codes ----- */
# define LDCOM_E_NO_ERROR                        0x00u

# if (LDCOM_DEV_ERROR_DETECT == STD_ON) /* COV_LDCOM_VAR_DEV_ERROR_DETECT */
/*!
  \defgroup DetErrorIDs DetError IDs
  \brief    Det Error IDs as reported to DET.
  \{
*/
#  define LDCOM_E_PARAM                          0x01u  /**< API service called with wrong parameter */
#  define LDCOM_E_UNINIT                         0x02u  /**< API service used without module initialization */
#  define LDCOM_E_PARAM_POINTER                  0x03u  /**< API service called with NULL_PTR as parameter */
#  define LDCOM_E_INVALID_PDU_SDU_ID             0x04u  /**< API service called with wrong Pdu ID */
#  define LDCOM_E_INVALID_SIGNAL_ID              0x05u  /**< API service called with wrong Signal ID */
/*!
  \}
*/
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
# define LDCOM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */
# if (LDCOM_USE_INIT_POINTER == STD_ON)
extern P2CONST(LdCom_ConfigType, LDCOM_VAR_ZERO_INIT, LDCOM_PBCFG) LdCom_ConfigDataPtr;
# endif
# define LDCOM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define LDCOM_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * LdCom_Init
 *********************************************************************************************************************/
/*! \brief         Initializes the LdCom.
 *  \details       Initialize all LdCom variables and sets the component state to initialized.
 *  \param[in]     config              NULL_PTR if LDCOM_USE_INIT_POINTER is STD_OFF.
 *                                     Pointer to the LdCom configuration data if LDCOM_USE_INIT_POINTER is STD_ON.
 *  \pre           Interrupts are disabled.
 *  \pre           Module is uninitialized.
 *  \pre           LdCom_InitMemory has been called unless module variables are initialized by start-up code.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          The function is used by the Ecu State Manager
 *  \warning       LdCom_Init() shall not pre-empt any LdCom function.
 *                 The rest of the system must guarantee that LdCom_Init() is not called in such a way.
 *  \trace         CREQ-106197
 *********************************************************************************************************************/
FUNC(void, LDCOM_CODE) LdCom_Init(P2CONST(LdCom_ConfigType, AUTOMATIC, LDCOM_PBCFG) config);

/**********************************************************************************************************************
 * LdCom_InitMemory()
 *********************************************************************************************************************/
/*! \brief         Power-up memory initialization of the LdCom.
 *  \details       Initializes LdCom variables in *_INIT_* sections at power up.
 *  \pre           LdCom is uninitialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          The function is used by the application.
 *  \trace         CREQ-106197
 *********************************************************************************************************************/
FUNC(void, LDCOM_CODE) LdCom_InitMemory(void);

/**********************************************************************************************************************
 * LdCom_DeInit()
 *********************************************************************************************************************/
/*! \brief         This service stops the LdCom. The module is put into an uninitialized state.
 *  \details       -
 *  \pre           LdCom_DeInit() shall not pre-empt any LdCom function.
 *                 The rest of the system must guarantee that LdCom_DeInit() is not called in such a way.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          The function is used by the application.
 *  \note          The function must not be interrupted by other administrative functions.
 *  \trace         CREQ-106198
 *********************************************************************************************************************/
FUNC(void, LDCOM_CODE) LdCom_DeInit(void);

# if (LDCOM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 * LdCom_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief         Returns the version information of the LdCom module.
 *  \details       Returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]    versioninfo Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        LDCOM_VERSION_INFO_API
 *  \trace         CREQ-106199
 *********************************************************************************************************************/
FUNC(void, LDCOM_CODE) LdCom_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, LDCOM_APPL_DATA) versioninfo);
# endif

/**********************************************************************************************************************
 * LdCom_Transmit()
 *********************************************************************************************************************/
/*! \brief         The function serves to request the transmission of an upper layer I-PDU/Signal.
 *                 LdCom evaluates the I-PDU/Signal handle and identifies the destination I-PDU.
 *                 The call is routed to the PduR module using the appropriate I-PDU handle of the PduR.
 *  \details       -
 *  \param[in]     Id                  ID of the LdCom I-PDU/Signal to be transmitted
 *  \param[in]     PduInfoPtr          Payload information of the I-PDU/Signal (data pointer and data length)
 *  \return        E_OK:               The request was accepted by the LdCom and by the destination layer.
 *                 E_NOT_OK:           The LdCom is not initialized
 *                                     or the ID is not valid
 *                                     or the ID is not forwarded in this predefined variant
 *                                     or the PduInfoPtr parameter is not valid
 *                                     or the request was not accepted by the destination module.
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \pre           -
 *  \note          The function is called by the lower layer.
 *  \trace         CREQ-106200, CREQ-108860
 **********************************************************************************************************************/
FUNC(Std_ReturnType, LDCOM_CODE) LdCom_Transmit(PduIdType Id, P2CONST(PduInfoType, AUTOMATIC, LDCOM_APPL_DATA) PduInfoPtr);

# define LDCOM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */
#endif /* LDCOM_H */

/**********************************************************************************************************************
  END OF FILE: LdCom.h
**********************************************************************************************************************/
