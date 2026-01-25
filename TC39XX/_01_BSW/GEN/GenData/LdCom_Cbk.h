/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: LdCom
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: LdCom_Cbk.h
 *   Generation Time: 2026-01-24 23:51:59
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * WARNING: This code has been generated with reduced-severity errors. 
 * The created output files contain errors that have been ignored. Usage of the created files can lead to unpredictable behavior of the embedded code.
 * Usage of the created files happens at own risk!
 * 
 * [Warning] Cfg00022 - Missing parameter value 
 * - [Reduced Severity due to User-Defined Parameter] The value of reference LdComSystemTemplateSignalRef is missing or empty.
 * Erroneous configuration elements:
 * /ActiveEcuC/LdCom/LdComConfig/LdComIPdu_EcuStateTx[0:LdComSystemTemplateSignalRef](value=) (DefRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComSystemTemplateSignalRef)
 * 
 * [Warning] Cfg00022 - Missing parameter value 
 * - [Reduced Severity due to User-Defined Parameter] The value of reference LdComSystemTemplateSignalRef is missing or empty.
 * Erroneous configuration elements:
 * /ActiveEcuC/LdCom/LdComConfig/LdComIPdu_SenStateTx[0:LdComSystemTemplateSignalRef](value=) (DefRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComSystemTemplateSignalRef)
 * 
 * [Warning] Cfg00022 - Missing parameter value 
 * - [Reduced Severity due to User-Defined Parameter] The value of reference LdComSystemTemplateSignalRef is missing or empty.
 * Erroneous configuration elements:
 * /ActiveEcuC/LdCom/LdComConfig/LdComIPdu_VechicleSpeedRx[0:LdComSystemTemplateSignalRef](value=) (DefRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComSystemTemplateSignalRef)
 * 
 * [Warning] Cfg00022 - Missing parameter value 
 * - [Reduced Severity due to User-Defined Parameter] The value of reference LdComSystemTemplateSignalRef is missing or empty.
 * Erroneous configuration elements:
 * /ActiveEcuC/LdCom/LdComConfig/LdComIPdu_VechicleStatusRx[0:LdComSystemTemplateSignalRef](value=) (DefRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComSystemTemplateSignalRef)
 *********************************************************************************************************************/

#if !defined (LDCOM_CBK_H)
# define LDCOM_CBK_H
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "LdCom_Cfg.h"

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
#define LDCOM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (LDCOM_COMMUNICATION_INTERFACE == STD_ON)
/**********************************************************************************************************************
 * LdCom_RxIndication()
 *********************************************************************************************************************/
/*! \brief         This function is called by the lower layer when an LdCom IF I-PDU has been received.
 *                 LdCom evaluates the I-PDU/Signal handle and identifies the destination Signal.
 *                 The call is routed to the upper layer module using the appropriate API.
 *  \param[in]     RxPduId             ID of the LdCom I-PDU/Signal that has been received.
 *  \param[in]     PduInfoPtr          Payload information of the received I-PDU/Signal
 *                                     (pointer to data and data length).
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \pre           -
 *  \note          The function is called by the lower layer.
 *  \config        LDCOM_COMMUNICATION_INTERFACE
 *  \trace         CREQ-106201
 *********************************************************************************************************************/
FUNC(void, LDCOM_CODE) LdCom_RxIndication(PduIdType RxPduId,
                                          P2CONST(PduInfoType, AUTOMATIC, LDCOM_APPL_DATA) PduInfoPtr);

# if (LDCOM_TX_CONFIRMATION_API == STD_ON)
/**********************************************************************************************************************
 * LdCom_TxConfirmation()
 *********************************************************************************************************************/
/*! \brief         This function is called by the lower layer after an Ldcom IF I-PDU has been transmitted.
 *                 LdCom evaluates the I-PDU/Signal handle and identifies the destination Signal.
 *                 The call is routed to the upper layer module using the appropriate API.
 *  \param[in]     TxPduId             ID of the LdCom I-PDU/Signal that has been transmitted.
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \pre           -
 *  \note          The function is called by the lower layer.
 *  \config        LDCOM_TX_CONFIRMATION_API, LDCOM_COMMUNICATION_INTERFACE
 *  \trace         CREQ-106200
 *********************************************************************************************************************/
FUNC(void, LDCOM_CODE) LdCom_TxConfirmation(PduIdType TxPduId);
# endif

# if (LDCOM_TRIGGER_TRANSMIT_API == STD_ON)
/**********************************************************************************************************************
 * LdCom_TriggerTransmit()
 *********************************************************************************************************************/
/*! \brief         This function is called by the lower layer when an LdCom IF I-PDU shall be transmitted.
 *                 LdCom evaluates the I-PDU/Signal handle and identifies the destination Signal.
 *                 The call is routed to the upper layer module using the appropriate API.
 *  \param[in]     TxPduId             ID of the LdCom I-PDU/Signal that is requested to be transmitted.
 *  \param[in,out] PduInfoPtr          Contains a pointer to a buffer (SduDataPtr) to where the SDU
                                       data shall be copied, and the available buffer size in SduLengh.
                                       On return, the service will indicate the length of the copied SDU
                                       data in SduLength.
 *  \return        E_OK:               The SDU has been copied and the SduLength indicates the number of copied bytes.
 *                 E_NOT_OK:           A Det error occurred and the SDU has not been copied and the SduLength has not
 *                                     been set.
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \pre           -
 *  \note          The function is called by the lower layer.
 *  \config        LDCOM_TRIGGER_TRANSMIT_API, LDCOM_COMMUNICATION_INTERFACE
 *  \trace         CREQ-106200
 *********************************************************************************************************************/
FUNC(Std_ReturnType, LDCOM_CODE) LdCom_TriggerTransmit(PduIdType TxPduId,
                                                       P2VAR(PduInfoType, AUTOMATIC, LDCOM_APPL_DATA) PduInfoPtr);
# endif
#endif

#if (LDCOM_TRANSPORT_PROTOCOL == STD_ON)
/**********************************************************************************************************************
 * LdCom_StartOfReception()
 *********************************************************************************************************************/
/*! \brief         This function is called by the lower layer to indicate the start of an incoming TP connection.
 *                 LdCom evaluates the I-PDU/Signal handle and identifies the destination Signal.
 *                 The call is routed to the upper layer module using the appropriate API.
 *  \param[in]     id                  ID of LdCom I-PDU/Signal that shall be received.
 *  \param[in]     info                Payload and MetaData information of the received I-PDU
 *                                     (pointer to data/MetaData and data length).
 *  \param[in]     TpSduLength         Total length of the TP I-PDU to be received.
 *  \param[out]    bufferSizePtr       The LdCom returns in this value the remaining TP buffer size to the lower layer.
 *  \return        BUFREQ_OK:          Connection has been accepted.
 *                                     RxBufferSizePtr indicates the available receive buffer.
 *                 BUFREQ_E_NOT_OK:    Connection has been rejected. RxBufferSizePtr remains unchanged.
 *                 BUFREQ_E_OVFL:      In case the related upper layer module has rejected the reception.
 *                 BUFREQ_E_BUSY:      The case the related upper layer module is currently busy.
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \pre           -
 *  \note          The function is called by the lower layer.
 *  \config        LDCOM_TRANSPORT_PROTOCOL
 *  \trace         CREQ-108861
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, LDCOM_CODE) LdCom_StartOfReception(PduIdType id,
                                                           P2CONST(PduInfoType, AUTOMATIC, LDCOM_APPL_DATA) info,
                                                           PduLengthType TpSduLength,
                                                           P2VAR(PduLengthType, AUTOMATIC, LDCOM_APPL_DATA) bufferSizePtr);

/**********************************************************************************************************************
 * LdCom_CopyRxData()
 *********************************************************************************************************************/
/*! \brief         This function is called by the lower layer once upon reception of each TP segment.
 *                 LdCom evaluates the I-PDU/Signal handle and identifies the destination Signal.
 *                 The call is routed to the upper layer module using the appropriate API.
 *  \param[in]     id                  ID of LdCom I-PDU/Signal that shall be received.
 *  \param[in]     info                Payload information of the received TP segment
 *                                     (pointer to data and data length).
 *  \param[out]    bufferSizePtr       Remaining receive buffer size after completion of this call.
 *  \return        BUFREQ_OK:          Data successfully copied.
 *                                     RxBufferSizePtr indicates the remaining receive buffer size.
 *                 BUFREQ_E_NOT_OK:    Data was not copied because an error occurred.
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \pre           -
 *  \note          The function is called by the lower layer.
 *  \config        LDCOM_TRANSPORT_PROTOCOL
 *  \trace         CREQ-108861
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, LDCOM_CODE) LdCom_CopyRxData(PduIdType id,
                                                     P2CONST(PduInfoType, AUTOMATIC, LDCOM_APPL_DATA) info,
                                                     P2VAR(PduLengthType, AUTOMATIC, LDCOM_APPL_DATA) bufferSizePtr);

/**********************************************************************************************************************
 * LdCom_TpRxIndication()
 *********************************************************************************************************************/
/*! \brief         This function is called by the lower layer after an LdCom TP I-PDU has been received.
 *                 LdCom evaluates the I-PDU/Signal handle and identifies the destination Signal.
 *                 The call is routed to the upper layer module using the appropriate API.
 *  \param[in]     id                  ID of LdCom I-PDU/Signal that has been received.
 *  \param[in]     result              Indicates the reception result of the TP I-PDU.
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \pre           -
 *  \note          The function is called by the lower layer.
 *  \config        LDCOM_TRANSPORT_PROTOCOL
 *  \trace         CREQ-108861
 *********************************************************************************************************************/
FUNC(void, LDCOM_CODE) LdCom_TpRxIndication(PduIdType id, Std_ReturnType result);

/**********************************************************************************************************************
 * LdCom_CopyTxData()
 *********************************************************************************************************************/
/*! \brief         This function is called by the lower layer once upon transmission of each TP segment.
 *                 LdCom evaluates the I-PDU/Signal handle and identifies the destination Signal.
 *                 The call is routed to the upper layer module using the appropriate API.
 *  \param[in]     id                  ID of LdCom I-PDU/Signal that shall be transmitted.
 *  \param[in,out] info                Provides the destination buffer and the number of bytes to be copied.
 *                                     An SduLength of 0 is possible in order to poll the available transmit data
 *                                     count. In this case no data has to be copied and SduDataPtr might be invalid.
 *  \param[in]     retry               This parameter is used to acknowledge transmitted data or to retransmit data
 *                                     after transmission problems.
 *  \param[out]    availableDataPtr    Remaining transmit buffer size after completion of this call.
 *  \return        BUFREQ_OK:          Data has been copied to the transmit buffer completely as requested.
 *                 BUFREQ_E_BUSY:      The transmission buffer is actually not available (implementation specific).
 *                 BUFREQ_E_NOT_OK:    Data has not been copied.
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \pre           -
 *  \note          The function is called by the lower layer.
 *  \config        LDCOM_TRANSPORT_PROTOCOL
 *  \trace         CREQ-108860
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, LDCOM_CODE) LdCom_CopyTxData(PduIdType id,
                                                     P2CONST(PduInfoType, AUTOMATIC, LDCOM_APPL_DATA) info,
                                                     P2VAR(RetryInfoType, AUTOMATIC, LDCOM_APPL_DATA) retry,
                                                     P2VAR(PduLengthType, AUTOMATIC, LDCOM_APPL_DATA) availableDataPtr);

/**********************************************************************************************************************
 * LdCom_TpTxConfirmation()
 *********************************************************************************************************************/
/*! \brief         This function is called by the lower layer after a TP I-PDU has been transmitted.
 *                 LdCom evaluates the I-PDU/Signal handle and identifies the destination Signal.
 *                 The call is routed to the upper layer module using the appropriate API.
 *  \param[in]     id                  ID of LdCom I-PDU/Signal that has been transmitted.
 *  \param[in]     result              Indicates the transmission result of the TP I-PDU.
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \pre           -
 *  \note          The function is called by the lower layer.
 *  \config        LDCOM_TRANSPORT_PROTOCOL
 *  \trace         CREQ-108860
 *********************************************************************************************************************/
FUNC(void, LDCOM_CODE) LdCom_TpTxConfirmation(PduIdType id, Std_ReturnType result);
#endif

#define LDCOM_STOP_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* LDCOM_CBK_H */
/**********************************************************************************************************************
 *  END OF FILE: LdCom_Cbk.h
 *********************************************************************************************************************/
