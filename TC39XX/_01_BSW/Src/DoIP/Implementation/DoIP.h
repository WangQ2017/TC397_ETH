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
/**        \file  DoIP.h
 *        \brief  Diagnostic over Internet Protocol
 *
 *      \details  Header file of Diagnostic over IP
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author      Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *   1.00.00  2013-10-18  vismda      -             Moved from SoAd
 *   1.00.01  2013-11-07  vismda      -             Issues in PduR_DoIP
 *            2013-11-18  vismda      ESCAN00071981 Diagnostic Message Ack/Nack with invalid length
 *            2013-11-18  vismda      ESCAN00071841 Issue: DoIP PduR Api and If
 *   1.01.00  2014-02-07  vismda      ESCAN00072620 DoIP module shall perform version check against DoIP version
 *            2014-02-07  vismda      ESCAN00072387 Compiler warning: inconsistent storage class specification for
 *                                                  DoIP_VReSetVehicleAnnounce
 *            2014-02-07  vismda      ESCAN00072329 Issue when sending generic header nack and alive check request
 *            2014-02-07  vismda      ESCAN00072323 DET in DoIP_SoAdTpCopyRxData
 *   1.01.01  2014-04-30  vismda      ESCAN00075331 Endless loop at TcpIp buffer wrap around
 *   1.02.00  2014-05-08  vismda      ESCAN00074362 DoIP does not send expected Generic Header Negative Acknowledge
 *            2014-05-09  vismda      ESCAN00074459 AR4-650: Support ChangeParameter without Confirmation
 *            2014-05-09  vismda      ESCAN00071915 AR4-619: Support the StartOfReception API (with the PduInfoType),
 *                                                  TxConfirmation and RxIndication according ASR4.1.2
 *            2014-05-14  vismda      ESCAN00074082 AR4-582: DoIP functionality to mirror request data in response data
 *            2014-06-13  vismda      ESCAN00076206 Local define for STATIC
 *   1.02.01  2014-06-20  visalr      ESCAN00076350 DoIP_Init: Signatures inconsistent in DoIP.c and DoIP.h
 *   1.02.02  2014-07-02  vismda      ESCAN00076643 No generic header negative acknowledge with error code 0x02
 *            2014-07-02  vismda      ESCAN00076645 Default Protocol Version 0xFF is not accepted
 *            2014-07-03  vismda      ESCAN00076712 No response to segmented TCP message
 *   1.03.00  2014-08-21  vismda      ESCAN00077970 Add DoIPGw support
 *   1.04.00  2014-07-22  vismda      ESCAN00071768 The EID in Vehicle Announcement messages has the invalid value
 *            2014-07-22  vismda      ESCAN00073293 Feature: Implement UDP zero copy for transmission
 *            2014-07-22  vismda      ESCAN00076651 Vehicle Identification Response sent before A_DoIP_Announce_Wait
 *            2014-09-18  vismda      ESCAN00078453 Wrong routing activation response SA when all sockets are
 *                                                  registered and active
 *            2014-09-19  vismda      ESCAN00078472 Same diagnostic message negative acknowledgement is sent
 *            2014-09-25  vismda      ESCAN00077694 Compiler warning: Several warnings when the component is compiled
 *                                                  with Visual Studio
 *            2014-09-25  vismda      ESCAN00073340 Extract DoIP from SoAd
 *            2014-09-25  vismda      ESCAN00078431 No alive check requests are sent
 *            2014-09-25  vismda      ESCAN00078446 No routing activation response code 0x03 is sent
 *            2014-09-26  vismda      ESCAN00078601 T_TCP_General_Inactivity timeout is not reset when ECU sends messages
 *            2014-09-30  vismda      ESCAN00078645 Wrong DET check in DoIP_SoAdTpCopyTxData
 *            2014-10-06  vismda      ESCAN00078770 Unexpected behavior if PduR_DoIPCopyRxData() returns BUFREQ_E_NOT_OK
 *            2014-10-06  vismda      ESCAN00078777 DoIP_CancelReceive() does not DET-check DoIPPduRRxId properly
 *            2014-10-16  vismda      ESCAN00078921 No routing activation response code 0x02
 *            2014-10-16  vismda      ESCAN00078975 EnableTxBeforeRx and Shutdown issues
 *            2014-10-16  vismda      ESCAN00078974 ECU shall discard DoIP payload types on wrong transport layer
 *            2014-10-24  vismda      ESCAN00078217 DoIP causes alignment exception on sending Vehicle Announcement
 *   1.05.00  2015-03-12  vismda      ESCAN00081759 Adjustments to support ASR 4.2.1 SoAd
 *   1.05.01  2015-04-28  vismda      ESCAN00082732 Parameter bufferSizePtr in PduR_SoAdTpCopyRxData not checked
 *   1.06.00  2015-07-10  vismda      ESCAN00079233 Incorrect behavior when ECU receives an empty diagnostic message
 *            2015-07-15  vismda      ESCAN00079880 Compiler error: DoIP_VCfgEId is undefined
 *            2015-07-15  vismda      ESCAN00079168 Call DoIP_SoAdTpCopyRxData() with invalid SduLength
 *            2015-07-16  vismda      ESCAN00079049 No communication after transmission cancellation
 *            2015-07-16  vismda      ESCAN00084033 Alignment exception on sending initial Vehicle Announcements
 *   1.06.01  2015-08-17  vismda      ESCAN00084562 MISRA/PClint warnings
 *   1.06.02  2015-11-05  vismda      ESCAN00086288 CoreException "misaligned access exception (MAE)" occurs
 *   2.00.00  2015-11-05  vismda      ESCAN00084454 Socket not closed after reception of Alive Check Response with
 *                                                  invalid logical address
 *            2015-11-20  vismda      ESCAN00085184 FEAT-10: Implementation of DoIP according to AR 4.2.1 [AR4-507]
 *   2.00.01  2016-02-04  vismda      ESCAN00088064 No Activation Line switch to active in case DHCP address only
 *   2.01.00  2016-02-16  vismda      ESCAN00088317 Vehicle Identification returned unexpected Further Action value
 *            2016-02-17  vismda      ESCAN00088344 Unexpected power mode if <User>_DoIPGetPowerModeStatus fails
 *            2016-02-17  vismda      ESCAN00088351 TCP socket closed on routing activation authentication callback
 *                                                  return value switch from DOIP_E_PENDING to E_OK
 *            2016-02-18  vismda      ESCAN00088393 Implement inactivity timer as specified in AUTOSAR
 *            2016-02-18  vismda      ESCAN00088393 No response to Routing Activation Request if confirmation is used
 *            2016-02-24  vismda      ESCAN00087700 FEAT-1698: Support UUDT on DoIP according to AR 4.2.2
 *            2016-02-25  vismda      ESCAN00087683 FEAT-1449: Release of FEAT-1253 (ETH Stack)
 *            2016-03-21  vismda      ESCAN00089003 Out-of-bounds access around DoIP_VSoAdRxPduId2SoConClosing[]
 *            2016-03-22  vismda      ESCAN00087995 Activation Line cannot be set to inactive
 *   2.01.01  2016-04-12  vismda      ESCAN00089407 Unexpected DET in DoIP_SoAdTpCopyTxData()
 *   2.02.00  2016-05-19  vismda      ESCAN00089429 Compiler warning: 'DoIP_VHandleGidSync' declared 'static' but never
 *                                                  defined
 *            2016-05-19  vismda      ESCAN00089348 FEAT-1820: DoIP: Improved Vehicle Announcement Handling
 *            2016-06-16  vismda      ESCAN00090504 Vehicle Announcement with unexpected GID caused by
 *                                                  misinterpretation of <User>_DoIPGetGidCallback return value
 *   3.00.00  2016-08-25  vismda      ESCAN00091628 DoIP discards first TCP DoIP message
 *            2016-09-05  vismda      FEATC-259     FEAT-1706: DoIP: Support call-outs for OEM-specific DoIP payload types
 *            2016-09-12  vismda      ESCAN00091842 No response to Routing Activation Request
 *            2016-10-14  vismda      ESCAN00092319 Missing support of required IP address assignment methods
 *            2016-10-20  vismda      FEATC-261     FEAT-1666: Adapted DoIP channel selection (DoIP address masking)
 *            2016-10-25  vismda      FEATC-256     FEAT-1816: Split MainFunctions to optimize gateway use-case
 *   3.00.01  2016-12-02  vismda      ESCAN00093151 Vehicle Identification Request with EID and invalid length is
 *                                                  responded with unexpected error code
 *   3.01.00  2017-01-09  vispcn      FEATC-940     FEAT-1824: Support a component-specific SafeBSW configuration switch
 *            2017-01-25  vismda      ESCAN00093714 Compiler error around DoIP_VRequestIpAddrAssignment()
 *            2017-01-29  vismda      ESCAN00093879 FEAT-2750: Support multiple testers on different VLANs
 *            2017-02-08  vismda      FEATC-1143    FEAT-2778: Support Buffer Size up to 128kB for FBL use case
 *   4.00.00  2017-04-11  vismda      ESCAN00094727 Timeout for consecutive vehicle announcements is equal to initial
 *                                                  timeout
 *            2017-05-08  vismda      STORYC-386    P3 CAD
 *   4.01.00  2017-05-22  vismda      STORYC-751    Support more than 255 DoIP Target Addresses
 *   4.02.00  2017-07-06  visjsb      STORYC-1203   DoIP: Callout for Diagnostic Firewall Use Case
 *   4.03.00  2017-07-13  visjsb      STORYC-387    P3 Implementation API Pattern
 *            2017-07-20  visjsb      ESCAN00095972 DoIP array index out of bounds
 *            2017-07-20  visjsb      STORYC-1476   P3 Cleanup Implementation
 *   4.04.00  2017-08-21  visjsb      STORYC-1795   P3 Code Refactoring / CDD Step 2
 *   5.00.00  2017-09-14  visjsb      STORYC-2314   P3 Code Refactoring / CDD Step 3
 *            2017-09-14  visjsb      ESCAN00096650 Vehicle Identification with unexpected "Further Action" value
 *   5.01.00  2018-01-31  visjsb      ESCAN00098028 Reception of unkown TCP payload type leads to endless loop.
 *            2018-01-31  visjsb      STORYC-4037   [ETH] Discontinue support for DoIP draft standards (DIS/FDIS)
 *   5.02.00  2018-02-23  visjsb      STORYC-4253   Support more than 255 DoIP Target Addresses per Routing Activation
 *   5.02.01  2018-04-11  vismda      ESCAN00098931 Routing Activation with valid activation type rejected
 *   6.00.00  2018-04-13  vismda      STORYC-3609   FEAT-3259 [ETH] Support IPv6 ActivationLine for DoIP
 *   6.01.00  2018-05-04  vismda      ESCAN00099141 DoIP connections are not opened after IP address gets lost
 *            2018-05-23  vismda      ESCAN00099122 Validation error: Assignment trigger has to be set to AUTOMATIC/MANUAL
 *            2018-07-19  visjsb      ESCAN00098363 Routing not activated until alive check timeout exceeds
 *   6.01.01  2018-08-21  visjsb      ESCAN00100455 DoIP send multiple Routing Activation Responses
 *   7.00.00  2018-08-24  visjsb      STORYC-396    SAFE Increase Test Depth
 *            2018-09-03  visjsb      ESCAN00100612 Routing Activation Response send OEM specific part with wrong length
 *            2018-09-03  visjsb      ESCAN00100614 Pdu size routing choose a wrong channel
 *            2018-10-15  visjsb      ESCAN00101014 DoIP target unreachable while target address bitmasking is used.
 *            2018-11-20  visjsb      ESCAN00101385 The best matching channel is not always found during pdu size routing.
 *            2019-02-01  visjsb      STORYC-6486   MISRA-C:2012 Compliance
 *            2019-03-18  visjsb      STORY-5903    Implement DHCP option field to be used for target IP addresses of DoIP
 *            2019-04-29  vistia      STORY-5904    Send vehicle announcements to dynamic target IP addresses
 *   7.01.00  2019-05-10  visjsb      STORY-12612   DoIP DHCP option for SAFE
 *            2019-05-28  visjsb      ESCAN00099828 No responses on multiple parallel diagnostic messages
 *            2019-06-19  visjsb      ESCAN00103465 No IF-PDU transmission is possible anymore
 *   8.00.00  2019-08-09  vistia      TCPIP-832     Introduce DoIP_GetAndResetMeasurementData()
 *   9.00.00  2019-11-12  vismda      SAA-108       Deny DoIP routing activation under certain conditions (AR-3349)
 *   9.00.01  2020-03-18  vismda      ESCAN00105163 Memory corruption on reception of routing activation request in
 *                                                  case of invalid configuration
 *            2020-03-25  vismda      ESCAN00105628 Vehicle Identification Request blocks UDP connections for other testers
 *   9.00.02  2020-09-29  visjsb      ESCAN00107425 Issues on changing PDU size dependent routing configuration
 *            2020-09-29  visjsb      ESCAN00107427 DoIP sends an unexpected VIN/GID status
 *            2020-09-29  visjsb      ESCAN00107429 Unexpected data forwarded after PDU reception verification
 *            2020-09-29  visjsb      ESCAN00107431 Vehicle announcement/identification response messages are not sent
 *            2020-10-01  jelsaesser  SAA-853       [DoIP] Update to QAC Helix
 *            2020-10-09  visjsb      SAA-1152      Recheck DoIP's API reentrance
 *   9.00.03  2021-01-04  visjsb      SAA-1436      [R25] ESCAN00108069: Issue on reception of DoIP messages with
 *                                                  header + payload length > 0xFFFFFFFF
 *            2021-01-04  visjsb      SAA-1251      [DoIP] Update version history to current template
 *            2021-01-14  visjsb      ESCAN00108298 Issues on reception of OEM specific payload type
 *********************************************************************************************************************/

#if ( !defined(DOIP_H) )
# define DOIP_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "ComStack_Types.h"
# include "DoIP_Lcfg.h"
# include "DoIP_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* DoIP ModuleId */
# define DOIP_VENDOR_ID                            30u  /* Vector Id */
# define DOIP_MODULE_ID                            173u /* DoIP Id */

/* DoIP supported Autosar version */
# define DOIP_AR_RELEASE_MAJOR_VERSION             4u
# define DOIP_AR_RELEASE_MINOR_VERSION             2u
# define DOIP_AR_RELEASE_PATCH_VERSION             2u

/* DoIP software version */
# define DOIP_SW_MAJOR_VERSION                     9u
# define DOIP_SW_MINOR_VERSION                     0u
# define DOIP_SW_PATCH_VERSION                     3u

/* DoIP AUTOSAR ServiceIds */
# define DOIP_SID_GET_VERSION_INFO                 0x00u
# define DOIP_SID_INIT                             0x01u
# define DOIP_SID_MAIN_FUNCTION                    0x02u
# define DOIP_SID_TP_TRANSMIT                      0x03u
# define DOIP_SID_TP_CANCEL_TRANSMIT               0x04u
# define DOIP_SID_TP_CANCEL_RECEIVE                0x05u
# define DOIP_SID_SO_CON_MODE_CHG                  0x0Bu
# define DOIP_SID_LOC_IP_ADDR_ASSIGN_CHG           0x0Cu
# define DOIP_SID_ACTIVATION_LINE_SWITCH           0x0Fu
# define DOIP_SID_IF_TX_CONFIRMATION               0x40u
# define DOIP_SID_IF_RX_INDICATION                 0x42u
# define DOIP_SID_TP_COPY_TX_DATA                  0x43u
# define DOIP_SID_TP_COPY_RX_DATA                  0x44u
# define DOIP_SID_TP_RX_INDICATION                 0x45u
# define DOIP_SID_TP_START_OF_RECEPTION            0x46u
# define DOIP_SID_TP_TX_CONFIRMATION               0x48u
# define DOIP_SID_IF_TRANSMIT                      0x49u
# define DOIP_SID_IF_CANCEL_TRANSMIT               0x4Au

/* DoIP Vector ServiceIds */
# define DOIP_SID_VACTIVATION_LINE_TO_ACTIVE       0xEBu
# define DOIP_SID_ENABLE_PDU_SIZE_ROUTING          0xECu
# define DOIP_SID_DISABLE_PDU_SIZE_ROUTING         0xEDu
# define DOIP_SID_VUDP_SINGLE_TRANSMIT             0xEEu
# define DOIP_SID_VTCP_TRANSMIT                    0xEFu
# define DOIP_SID_SHUTDOWN_FINISHED                0xF0u
# define DOIP_SID_DHCP_EVENT                       0xF1u
# define DOIP_SID_GET_RESET_MEASURE_DATA           0xF2u

/* DoIP AUTOSAR DET errors */
# define DOIP_E_UNINIT                             0x01u
# define DOIP_E_PARAM_POINTER                      0x02u
# define DOIP_E_INVALID_PDU_SDU_ID                 0x03u
# define DOIP_E_INVALID_PARAMETER                  0x04u
# define DOIP_E_INIT_FAILED                        0x05u

/* DoIP Vector DET errors */
# define DOIP_E_NO_ERROR                           0x00u /* use a value unequal to any error code */
# define DOIP_E_ACTIVATION_LINE                    0xECu
# define DOIP_E_SOAD_CALL_FAILED                   0xEDu
# define DOIP_E_UNEXPECTED_ASSIGNMENT              0xEEu
# define DOIP_E_NOBUFS                             0xEFu
# define DOIP_E_PDU_SIZE_ROUTING                   0xF0u
# define DOIP_E_SHUTDOWN_FINISHED                  0xF1u
# define DOIP_E_DHCP_EVENT                         0xF2u

/* DoIP states */
# define DOIP_STATE_UNINIT                         0x00u
# define DOIP_STATE_INIT                           0x01u
# define DOIP_STATE_SHUTDOWN                       0x02u

/* DoIP header types */
# define DOIP_HDR_TYPE_GEN_NACK                    0x0000u
# define DOIP_HDR_TYPE_VEHICLE_IDENT_REQ           0x0001u
# define DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_EID       0x0002u
# define DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_VIN       0x0003u
# define DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT        0x0004u
# define DOIP_HDR_TYPE_ROUT_ACTIV_REQ              0x0005u
# define DOIP_HDR_TYPE_ROUT_ACTIV_RES              0x0006u
# define DOIP_HDR_TYPE_ALIVE_CHECK_REQ             0x0007u
# define DOIP_HDR_TYPE_ALIVE_CHECK_RES             0x0008u
# define DOIP_HDR_TYPE_ENTITY_STATE_REQ            0x4001u
# define DOIP_HDR_TYPE_ENTITY_STATE_RES            0x4002u
# define DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_REQ    0x4003u
# define DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_RES    0x4004u
# define DOIP_HDR_TYPE_DIAG_REQ                    0x8001u
# define DOIP_HDR_TYPE_DIAG_ACK                    0x8002u
# define DOIP_HDR_TYPE_DIAG_NACK                   0x8003u
# define DOIP_HDR_TYPE_OEM_SPECIFIC                0xEEEEu
# define DOIP_HDR_TYPE_INVALID                     0xEFFFu

/* DoIP protocol versions */
# define DOIP_PROTOCOL_VERSION_2012                0x02u
# define DOIP_PROTOCOL_VERSION_DEFAULT             0xFFu

/* DoIP generic nack codes */
# define DOIP_GEN_NACK_FORMAT                      0x00u
# define DOIP_GEN_NACK_TYPE                        0x01u
# define DOIP_GEN_NACK_MAX_LEN                     0x02u
# define DOIP_GEN_NACK_OUT_OF_MEM                  0x03u
# define DOIP_GEN_NACK_INV_LEN                     0x04u
# define DOIP_GEN_NACK_OK                          0xFFu
# define DOIP_GEN_NACK_LEN_BYTE                    0x01u

/* DoIP routing activation nack codes */
# define DOIP_ROUT_ACTIV_RES_CODE_UNKNOWN_TESTER   0x00u
# define DOIP_ROUT_ACTIV_RES_CODE_SOCKETS_IN_USE   0x01u
# define DOIP_ROUT_ACTIV_RES_CODE_DIFFERENT_TESTER 0x02u
# define DOIP_ROUT_ACTIV_RES_CODE_ALREADY_ACTIV    0x03u
# define DOIP_ROUT_ACTIV_RES_CODE_MISSING_AUTHENT  0x04u
# define DOIP_ROUT_ACTIV_RES_CODE_CONFIRM_REJECTED 0x05u
# define DOIP_ROUT_ACTIV_RES_CODE_INV_ACTIV_TYPE   0x06u
# define DOIP_ROUT_ACTIV_RES_CODE_REQUIRE_SECURE   0x07u
# define DOIP_ROUT_ACTIV_RES_CODE_SUCCESS          0x10u
# define DOIP_ROUT_ACTIV_RES_CODE_CONFIRM_REQUIRED 0x11u

/* DoIP diagnostic request nack codes */
# define DOIP_DIAG_MSG_RES_CODE_ACK                0x00u
# define DOIP_DIAG_MSG_RES_CODE_UNKNOWN_SRC_ADDR   0x01u /* described in ISO/CD 13400 - not used */
# define DOIP_DIAG_MSG_RES_CODE_INVALID_SRC_ADDR   0x02u
# define DOIP_DIAG_MSG_RES_CODE_UNKNOWN_TGT_ADDR   0x03u
# define DOIP_DIAG_MSG_RES_CODE_MSG_TOO_LARGE      0x04u
# define DOIP_DIAG_MSG_RES_CODE_OUT_OF_MEMORY      0x05u
# define DOIP_DIAG_MSG_RES_CODE_TGT_UNREACHABLE    0x06u
# define DOIP_DIAG_MSG_RES_CODE_UNKNOWN_NETWORK    0x07u
# define DOIP_DIAG_MSG_RES_CODE_NETWORK_TRANSPROT  0x08u

/* DoIP diagnostic power mode ack codes */
# define DOIP_DIAG_POWER_MODE_RES_CODE_NOT_READY   0x00u
# define DOIP_DIAG_POWER_MODE_RES_CODE_READY       0x01u

/* DoIP DHCP vendor option data */
# define DOIP_DHCPVX_OPT_VENDOR_ENT_NUM_3210              3210u
# define DOIP_DHCPVX_OPT_VENDOR_BUF_MAX_LEN               72u /* max size to read/write of vendor class/opts - largest buffer is DHCPv6 vendor opts with 4 IPv6 addresses */
# define DOIP_DHCPVX_OPT_VENDOR_TABLE_SIZE                4u  /* up to 4 Ip addresses */
# define DOIP_DHCPVX_OPT_VENDOR_SUB_CODE                  1u  /* DoIP == 0x01u */
# define DOIP_DHCPV4_OPT_VENDOR_CLASS_OPT_CODE            124u
# define DOIP_DHCPV4_OPT_VENDOR_OPTS_OPT_CODE             125u
# define DOIP_DHCPV6_OPT_VENDOR_CLASS_OPT_CODE            16u
# define DOIP_DHCPV6_OPT_VENDOR_OPTS_OPT_CODE             17u
# define DOIP_DHCPV4_OPT_VENDOR_CLASS_MIN_LEN             5u  /* enterNum (4) + dataLen (1)*/
# define DOIP_DHCPV6_OPT_VENDOR_CLASS_MIN_LEN             4u  /* enterNum (4) */
# define DOIP_DHCPV4_OPT_VENDOR_OPTS_MIN_LEN              11u /* enterNum (4) + dataLen (1) + code (1) + len(1) + addrSize (4) */
# define DOIP_DHCPV6_OPT_VENDOR_OPTS_MIN_LEN              24u /* enterNum (4) +               code (2) + len(2) + addrSize (16) */
# define DOIP_DHCPV4_OPT_VENDOR_OPTS_SUB_OPT_LEN_OFFSET   6u  /* enterNum (4) + dataLen (1) + code (1) */
# define DOIP_DHCPV6_OPT_VENDOR_OPTS_SUB_OPT_LEN_OFFSET   6u  /* enterNum (4) +               code (2) */
# define DOIP_DHCPV4_OPT_VENDOR_OPTS_ADDR_OFFSET          7u  /* enterNum (4) + dataLen (1) + code (1) + len (1) */
# define DOIP_DHCPV6_OPT_VENDOR_OPTS_ADDR_OFFSET          8u  /* enterNum (4) +               code (2) + len (2) */
# define DOIP_DHCPV4_OPT_ADDR_SIZE                        4u
# define DOIP_DHCPV6_OPT_ADDR_SIZE                        16u

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define DOIP_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Pointer to the configuration. */
extern P2CONST(DoIP_ConfigType, DOIP_VAR_ZERO_INIT, DOIP_PBCFG) DoIP_ConfigDataPtr;

#define DOIP_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define DOIP_START_SEC_CODE
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  DoIP_InitMemory()
 *********************************************************************************************************************/
/*! \brief          Power-up memory initialization
 *  \details        Initializes component variables in *_INIT_* sections at power up.
 *  \pre            Module is uninitialized.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \note           Use this function in case these variables are not initialized by the startup code.
 *  \trace          DSGN-DoIPInitialization
 *********************************************************************************************************************/
FUNC(void, DOIP_CODE) DoIP_InitMemory(void);

/**********************************************************************************************************************
 *  DoIP_Init()
 *********************************************************************************************************************/
/*! \brief          Initializes component
 *  \details        Initializes all component variables and sets the component state to initialized. This service
 *                  initializes all global variables of the DoIP module. After return of this service the DoIP module
 *                  is operational.
 *  \param[in]      DoIPConfigPtr   Pointer to the configuration data of the DoIP module.
 *  \pre            Interrupts are disabled.
 *  \pre            Module is uninitialized.
 *  \pre            DoIP_InitMemory has been called unless DoIP_State is initialized by start-up code.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPInitialization
 *********************************************************************************************************************/
FUNC(void, DOIP_CODE) DoIP_Init(
  P2CONST(DoIP_ConfigType, AUTOMATIC, DOIP_CONST) DoIPConfigPtr);

# if ( DOIP_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  DoIP_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief          Returns the version information
 *  \details        Returns version information, vendor Id and AUTOSAR module Id of the component.
 *  \param[out]     versioninfo   Pointer to where to store the version information of this module. Parameter must not
 *                                be NULL.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_VERSION_INFO_API
 *  \trace          CREQ-125656
 *********************************************************************************************************************/
FUNC(void, DOIP_CODE) DoIP_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DOIP_APPL_VAR) versioninfo);
# endif /* DOIP_VERSION_INFO_API == STD_ON */

/**********************************************************************************************************************
 *  DoIP_TpTransmit()
 *********************************************************************************************************************/
/*! \brief          Requests transmission of a specific TP Pdu
 *  \details        This service is called to request the transfer data from the PduRouter to the SoAd. It is used to
 *                  indicate the transmission which will be performed by SoAd or in the DoIP_Mainfunction. Within the
 *                  provided DoIPPduRTxInfoPtr only SduLength is valid (no data)! If this function returns E_OK then
 *                  the SoAd module will raise a subsequent call to PduR_DoIPCopyTxData via DoIP_SoAdTpCopyRxData in
 *                  order to get the data to send.
 *  \param[in]      DoIPPduRTxId        DoIP unique identifier of the Pdu to be transmitted by the PduR.
 *  \param[in]      DoIPPduRTxInfoPtr   Tx Pdu information structure which contains the length of the DoIPTxMessage.
 *  \return         E_OK                The request has been accepted.
 *  \return         E_NOT_OK            The request has not been accepted, e.g. parameter check has failed or no
 *                                      resources are available for transmission.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE - Reentrant for different DoIPPduRTxIds. Non reentrant for the same DoIPPduRTxId.
 *  \synchronous    FALSE
 *  \trace          DSGN-DoIPDiagnosticMessageTpApiTransmission
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DOIP_CODE) DoIP_TpTransmit(
  PduIdType DoIPPduRTxId,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) DoIPPduRTxInfoPtr);

/**********************************************************************************************************************
 *  DoIP_TpCancelTransmit()
 *********************************************************************************************************************/
/*! \brief          Requests transmission cancellation of a specific TP Pdu
 *  \details        This service primitive is used to cancel the transfer of pending DoIPPduRTxIds. The connection is
 *                  identified by DoIPPduRTxId. If the function returns the cancellation is requested but not yet
 *                  performed.
 *  \param[in]      DoIPPduRTxId  DoIP unique identifier of the Pdu to be canceled by the PduR.
 *  \return         E_OK          Transmit cancellation request of the specified DoIPPduRTxId is accepted.
 *  \return         E_NOT_OK      The transmit cancellation request of the DoIPPduRTxId has been rejected.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \trace          DSGN-DoIPCancellationTpApiTransmission
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DOIP_CODE) DoIP_TpCancelTransmit(
  PduIdType DoIPPduRTxId);

/**********************************************************************************************************************
 *  DoIP_TpCancelReceive()
 *********************************************************************************************************************/
/*! \brief          Requests reception cancellation of a specific TP Pdu
 *  \details        By calling this API with the corresponding DoIPPduRRxId the currently ongoing data reception is
 *                  terminated immediately. If the function returns the cancellation is requested but not yet
 *                  performed.
 *  \param[in]      DoIPPduRRxId  DoIP unique identifier of the Pdu for which reception shall be canceled by the PduR.
 *  \return         E_OK          Reception was canceled successfully.
 *  \return         E_NOT_OK      Reception was not canceled.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \trace          DSGN-DoIPCancellationTpApiReception
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DOIP_CODE) DoIP_TpCancelReceive(
  PduIdType DoIPPduRRxId);

/**********************************************************************************************************************
 *  DoIP_IfTransmit()
 *********************************************************************************************************************/
/*! \brief          Requests transmission of a specific IF Pdu
 *  \details        -
 *  \param[in]      id        Identification of the IF Pdu.
 *  \param[in]      info      Length and pointer to the buffer of the IF Pdu.
 *  \return         E_OK      Request is accepted by the destination module.
 *  \return         E_NOT_OK  Request is not accepted by the destination module.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE - Reentrant for different ids. Non reentrant for the same id.
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPDiagnosticMessageIfApiTransmission
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DOIP_CODE) DoIP_IfTransmit(
  PduIdType id,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) info);

/**********************************************************************************************************************
 *  DoIP_IfCancelTransmit()
 *********************************************************************************************************************/
/*! \brief          Requests transmission cancellation of a specific IF Pdu
 *  \details        -
 *  \param[in]      id        Identification of the IF Pdu to be cancelled.
 *  \return         E_OK      Cancellation was executed successfully by the destination module.
 *  \return         E_NOT_OK  Cancellation was rejected by the destination module.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \trace          DSGN-DoIPCancellationIfApiTransmission
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DOIP_CODE) DoIP_IfCancelTransmit(
  PduIdType id);

/**********************************************************************************************************************
 *  DoIP_EnablePduSizeRouting()
 *********************************************************************************************************************/
/*! \brief          Activates the DoIP packet size dependent routing.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_SUPPORT_PDU_SIZE_ROUTING
 *  \trace          DSGN-DoIPPduSizeDependentRouting
 *********************************************************************************************************************/
FUNC(void, DOIP_CODE) DoIP_EnablePduSizeRouting(void);

/**********************************************************************************************************************
 *  DoIP_DisablePduSizeRouting()
 *********************************************************************************************************************/
/*! \brief          Deactivates the DoIP packet size dependent routing.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_SUPPORT_PDU_SIZE_ROUTING
 *  \trace          DSGN-DoIPPduSizeDependentRouting
 *********************************************************************************************************************/
FUNC(void, DOIP_CODE) DoIP_DisablePduSizeRouting(void);

/**********************************************************************************************************************
 *  DoIP_Shutdown()
 *********************************************************************************************************************/
/*! \brief          Shutdown of SoAd.
 *  \details        All sockets will be closed and modules change to special shutdown state.
 *  \return         E_OK                Shutdown request was accepted.
 *  \return         E_NOT_OK            Shutdown request was not accepted.
 *  \return         SOAD_E_INPROGRESS   Shutdown is in progress.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         DOIP_SUPPORT_SHUTDOWN
 *  \trace          DSGN-DoIPShutdown
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DOIP_CODE) DoIP_Shutdown(void);

# if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_GetAndResetMeasurementData()
 *********************************************************************************************************************/
/*! \brief          Gets and Resets(if requested) the dropped TCP/UDP packets counter.
 *  \details        Retrieve the dropped TCP/UDP packets counter value and if requested, reset the value.
 *  \param[in]      MeasurementIdx          The index to select specific measurement data.
 *                                          [range: DOIP_MEAS_DROP_TCP, DOIP_MEAS_DROP_UDP, DOIP_MEAS_ALL]
 *  \param[in]      MeasurementResetNeeded  Flag to indicate if the counter needs to be reset.
 *                                          [range: TRUE, FALSE]
 *  \param[in]      MeasurementDataPtr      Buffer where the value of the counter is to be copied into.
 *                                          [range: POINTER may be NULL_PTR]
 *  \return         E_OK                    The operations were successful.
 *  \return         E_NOT_OK                The operations failed.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_GET_RESET_MEASUREMENT_DATA
 *  \trace          DSGN-DoIPGetResetMeasureData
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DOIP_CODE) DoIP_GetAndResetMeasurementData(
  DoIP_MeasurementIdxType MeasurementIdx,
  boolean MeasurementResetNeeded,
  P2VAR(DoIP_MeasurementDataType, AUTOMATIC, DOIP_APPL_VAR) MeasurementDataPtr);
# endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

# define DOIP_STOP_SEC_CODE
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * \exclusivearea DOIP_EXCLUSIVE_AREA_0
 *  Ensures consistency while modifying SoCon-, Tx TCP queue-, Tx UDP list structs and global data.
 * \protects DoIP_Get/Is/SetSoConClosingOfConnectionDyn(), DoIP_Get/Is/SetSoConStateOfConnectionDyn(),
 *           DoIP_GetTxTcpMgtStart/EndIdxOfConnectionTcp(), DoIP_Get/Is/SetTxMgtQueIdxOfConnectionTcpDyn(),
 *           DoIP_Get/Is/SetTxMgtQueLvlOfConnectionTcpDyn(), DoIP_Get/Is/SetTxTpSessionActiveOfConnectionTcpDyn(),
 *           DoIP_Get/SetIpAddrOfIpAddrList(), DoIP_Is/SetTriggerVehAnnOfIpAddrList(),
 *           DoIP_Measure_DroppedTcpPacketsCounter, DoIP_Measure_DroppedUdpPacketsCounter,
 *           DoIP_Get/SetConnectionIdxOfTxUdpMgtList, DoIP_LocalAddrAssignedCounter.
 * \usedin   DoIP_Con_SoConOpen(), DoIP_TxTcp_Transmit(), DoIP_TxTcpQueue_Copy(), DoIP_TxTcpQueue_RemoveElement(),
 *           DoIP_TxTcpQueue_TransmitElement(), DoIP_Dhcp_UpdateLocalIpAddrList(),
 *           DoIP_Dhcp_HandleVehAnnounceTriggOfIpAddrList(), DoIP_Con_HandleLocalIpAddrAssignmentChg(),
 *           DoIP_Measure_GetAndResetDroppedPacketCounter(), DoIP_Measure_IncDroppedPacketCounterTcp,
 *           DoIP_Measure_IncDroppedPacketCounterUdp, DoIP_TxUdp_TransmitDelayed,
 *           DoIP_Con_HandleLocalIpAddrAssignmentChg.
 * \exclude  All functions provided by DoIP.
 * \length   LONG This exclusive area covers calls to several sub-functions.
 * \endexclusivearea
 */

#endif /* !defined(DOIP_H) */

/**********************************************************************************************************************
 *  END OF FILE: DoIP.h
 *********************************************************************************************************************/
