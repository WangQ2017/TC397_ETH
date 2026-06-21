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
/**        \file  DoIP_Types.h
 *        \brief  Diagnostic over Internet Protocol
 *
 *      \details  Header file for type definitions of Diagnostic over IP
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if ( !defined(DOIP_TYPES_H) )
# define DOIP_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "DoIP_Cfg.h"
# include "SoAd.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Invalid buffer length. */
# define DOIP_INV_BUF_LEN                       0u

/*! Unused parameter. */
# define DOIP_UNUSED_PARAM                      0u

/*! Number of vehicle identification responses. */
# define DOIP_IDENT_RES_NUM                     1u

/*! Physical address length in bytes. */
# define DOIP_PHYS_ADDR_LEN                     6u

/*! TCP transmission buffer max length in bytes. */
# define DOIP_TX_TCP_BUF_LEN_BYTE_TOTAL         21u

/*! TCP transmission buffer max length in bytes. */
# define DOIP_ALIVE_CHECK_WAIT_NEXT_MAIN        1u

/*! DoIP return value  pending. */
# define DOIP_E_PENDING                         0x10u

/*! IP address assignment triggers. */
# define DOIP_IPADDR_ASSIGN_TRIGGER_AUTOMATIC   0u
# define DOIP_IPADDR_ASSIGN_TRIGGER_MANUAL      1u

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Activation line type. */
typedef uint8 DoIP_ActivationLineType;
# define DOIP_ACTIVATION_LINE_INACTIVE                  0u
# define DOIP_ACTIVATION_LINE_ACTIVE                    1u

/*! UDP connection type. */
typedef uint8 DoIP_UdpConnectionType;
# define DOIP_UDP_CON_TYPE_BROADCAST                    0u
# define DOIP_UDP_CON_TYPE_UNICAST                      1u

/*! IP address request state type. */
typedef uint8 DoIP_IpAddrReqStateType;
# define DOIP_IP_ADDR_REQ_STATE_NONE                    0x00u
# define DOIP_IP_ADDR_REQ_STATE_REQUESTED               0x01u

/*! Routing activation state type. */
typedef uint8 DoIP_RoutActivStateType;
# define DOIP_ROUT_ACTIV_STATE_NONE                     0u
# define DOIP_ROUT_ACTIV_STATE_AUTH_PENDING             1u
# define DOIP_ROUT_ACTIV_STATE_CONF_PENDING             2u
# define DOIP_ROUT_ACTIV_STATE_ACTIVATED                3u

/*! IP address assignment type. */
typedef uint8 DoIP_IpAddrAssignmentTypeType;
# define DOIP_IPADDR_ASSIGN_TYPE_NONE                   0u
# define DOIP_IPADDR_ASSIGN_TYPE_STATIC                 1u
# define DOIP_IPADDR_ASSIGN_TYPE_LINKLOCAL_DOIP         2u
# define DOIP_IPADDR_ASSIGN_TYPE_DHCP                   3u
# define DOIP_IPADDR_ASSIGN_TYPE_LINKLOCAL              4u

/*! Power state type. */
typedef uint8 DoIP_PowerStateType; /* required by AUTOSAR but DoIP_PowerModeType would be a better */
typedef DoIP_PowerStateType DoIP_PowerModeType;
# define DOIP_POWER_MODE_NOT_READY                      0x00u
# define DOIP_POWER_MODE_READY                          0x01u
# define DOIP_POWER_MODE_NOT_SUPPORTED                  0x02u

/*! API type. */
typedef uint8 DoIP_ApiType;
# define DOIP_API_TYPE_TP                               0x00u
# define DOIP_API_TYPE_IF                               0x01u

/*! OEM payload type flags type. */
typedef uint8 DoIP_OemPayloadTypeFlagType;
# define DOIP_OEM_PAYLOAD_TYPE_FLAG_PROT_UDP            (uint8)0x00u
# define DOIP_OEM_PAYLOAD_TYPE_FLAG_PROT_TCP            (uint8)0x01u
# define DOIP_OEM_PAYLOAD_TYPE_FLAG_ROUT_NOT_ACTIV      (uint8)0x00u
# define DOIP_OEM_PAYLOAD_TYPE_FLAG_ROUT_ACTIV          (uint8)0x02u

/*! Measure counter type. */
typedef uint8 DoIP_Measure_DroppedPacketCounterType;
# define DOIP_MEASURE_DROPPED_PACKET_COUNTER_TCP        0x00u
# define DOIP_MEASURE_DROPPED_PACKET_COUNTER_UDP        0x01u

/*! Measure counter max value. */
# define DOIP_MEASURE_DROPPED_PACKET_COUNTER_MAX_VALUE  65535u

/*! Index to select specific measurement data. */
typedef uint8 DoIP_MeasurementIdxType;
# define DOIP_MEAS_DROP_TCP                             0x01u
# define DOIP_MEAS_DROP_UDP                             0x02u
# define DOIP_MEAS_ALL                                  0xFFu

/*! Measured dropped packets counter type. */
typedef uint32 DoIP_MeasurementDataType;

/*! State type. */
typedef uint8 DoIP_StateType;

/*! DHCP Vendor Option data iteration type. */
typedef uint8_least DoIP_DhcpIpAddrIterType;

/*! DHCP Vendor Option data. */
typedef struct
{
  SoAd_SockAddrInetXType DhcpIpAddr;
  boolean                IsAddedToList;
} DoIP_DhcpIpAddrDynType;

/*! Get VIN function pointer. */
typedef P2FUNC(Std_ReturnType, DOIP_CODE, DoIP_GetVinFctPtrType)(
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) Vin);

/*! Power Mode function pointer. */
typedef P2FUNC(Std_ReturnType, DOIP_CODE, DoIP_PowerModeFctPtrType)(
   P2VAR(DoIP_PowerModeType, AUTOMATIC, DOIP_APPL_VAR) PowerStateReady);

/*! Get GID function pointer. */
typedef P2FUNC(Std_ReturnType, DOIP_CODE, DoIP_GetGidFctPtrType)(
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) GroupId);

/*! Trigger GID sync function pointer. */
typedef P2FUNC(Std_ReturnType, DOIP_CODE, DoIP_TriggerGidSyncFctPtrType)(void);

/*! Shutdown finished function pointer. */
typedef P2FUNC(void, DOIP_CODE, DoIP_ShutdownFinishedFctPtrType)(void);

/*! Activation line state function pointer. */
typedef P2FUNC(void, DOIP_CODE, DoIP_ActivationLineStateFctPtrType)(
  CONSTP2VAR(DoIP_ActivationLineType, AUTOMATIC, DOIP_CONST) ActivationLineState);

/*! Authentification function pointer. */
typedef P2FUNC(Std_ReturnType, DOIP_CODE, DoIP_AuthFctPtrType)(
  P2VAR(boolean, AUTOMATIC, DOIP_APPL_VAR) Authentified,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) AuthenticationReqData,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) AuthenticationResData);

/*! Authentification with remote address function pointer. */
typedef P2FUNC(Std_ReturnType, DOIP_CODE, DoIP_AuthWithRemAddrFctPtrType)(
  P2VAR(boolean, AUTOMATIC, DOIP_APPL_VAR) Authentified,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) AuthenticationReqData,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) AuthenticationResData,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, DOIP_APPL_VAR) RemAddrPtr);

/*! Confirmation function pointer. */
typedef P2FUNC(Std_ReturnType, DOIP_CODE, DoIP_ConfFctPtrType)(
  P2VAR(boolean, AUTOMATIC, DOIP_APPL_VAR) Confirmed,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ConfirmationReqData,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ConfirmationResData);

/*! Confirmation with remote address function pointer. */
typedef P2FUNC(Std_ReturnType, DOIP_CODE, DoIP_ConfWithRemAddrFctPtrType)(
  P2VAR(boolean, AUTOMATIC, DOIP_APPL_VAR) Confirmed,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ConfirmationReqData,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ConfirmationResData,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, DOIP_APPL_VAR) RemAddrPtr);

/*! OEM payload type function pointer. */
typedef P2FUNC(Std_ReturnType, DOIP_CODE, DoIP_OemPayloadTypeFctPtrType)(
  uint16 RxPayloadType,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) RxUserData,
  DoIP_OemPayloadTypeFlagType Flags,
  P2VAR(uint16, AUTOMATIC, DOIP_CONST) TxPayloadType,
  P2VAR(PduInfoType, AUTOMATIC, DOIP_CONST) TxUserData);

/*! Verify target address function pointer. */
typedef P2FUNC(Std_ReturnType, DOIP_CODE, DoIP_VerifyTargetAddrFctPtrType)(
  uint16 TargetAddr);

/*! Verify Rx Pdu function pointer. */
typedef P2FUNC(Std_ReturnType, DOIP_CODE, DoIP_VerifyRxPduFctPtrType)(
  P2CONST(SoAd_SockAddrType, AUTOMATIC, DOIP_CONST) LocalAddrPtr,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, DOIP_CONST) RemoteAddrPtr,
  uint16 SourceAddr,
  uint16 TargetAddr,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr);

#endif /* !defined(DOIP_TYPES_H) */

/**********************************************************************************************************************
 *  END OF FILE: DoIP_Types.h
 *********************************************************************************************************************/
