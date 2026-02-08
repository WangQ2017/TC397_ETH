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
/**        \file  DoIP.c
 *        \brief  Diagnostic over Internet Protocol
 *
 *      \details  Implementation file of Diagnostic over IP
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

#define DOIP_SOURCE

/**********************************************************************************************************************
 * LOCAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/

/* PRQA  S 1881 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA  S 4304 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA  S 4404 EOF */ /* MD_MSR_AutosarBoolean */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "DoIP.h" /* includes ComStack_Types.h */
#include "DoIP_Priv.h" /* includes SoAd.h */
#include "DoIP_Cbk.h"
#include "IpBase.h"
#include "PduR_DoIP.h"
#include "vstdlib.h"

#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check consistency of source and header file. */
#if ( (DOIP_SW_MAJOR_VERSION != 9u) || (DOIP_SW_MINOR_VERSION != 0u) || (DOIP_SW_PATCH_VERSION != 3u) )
# error "DoIP.c: Source and Header file are inconsistent!"
#endif /* (DOIP_SW_MAJOR_VERSION != 9u) || (DOIP_SW_MINOR_VERSION != 0u) || (DOIP_SW_PATCH_VERSION != 3u) */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#if ( !defined (DOIP_LOCAL) ) /* COV_DOIP_COMPATIBILITY */
# define DOIP_LOCAL static
#endif /* !defined (DOIP_LOCAL) */

#if ( !defined (DOIP_LOCAL_INLINE) ) /* COV_DOIP_COMPATIBILITY */
# define DOIP_LOCAL_INLINE LOCAL_INLINE
#endif /* !defined (DOIP_LOCAL_INLINE) */

#if ( DOIP_VIN_GID_SYNC == STD_ON )
# define DOIP_ACK_VEHICLE_IDENT_LEN_BYTE      33u
#else
# define DOIP_ACK_VEHICLE_IDENT_LEN_BYTE      32u
#endif /* DOIP_VIN_GID_SYNC == STD_ON */

#if ( DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE == STD_ON )
# define DOIP_ACK_ENTITY_STATE_LEN_BYTE       7u
#else
# define DOIP_ACK_ENTITY_STATE_LEN_BYTE       3u
#endif /* DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE == STD_ON */

#define DOIP_VIN_LEN_BYTE                     17u
#define DOIP_GID_LEN_BYTE                     6u
#define DOIP_EID_LEN_BYTE                     6u
#define DOIP_ADDR_LEN_BYTE                    2u
#define DOIP_ADDR_ANY                         ((uint16)0xFFFFu)
#define DOIP_GEN_HDR_LEN_BYTE                 8u
#define DOIP_GEN_HDR_TYPE_IDX                 2u
#define DOIP_GEN_HDR_NACK_CODE_LEN_BYTE       1u
#define DOIP_ROUT_ACTIV_REQ_MIN_LEN_BYTE      7u
#define DOIP_ROUT_ACTIV_REQ_MAX_LEN_BYTE      11u
#define DOIP_ROUT_ACTIV_REQ_TYPE_LEN_BYTE     1u
#define DOIP_ROUT_ACTIV_REQ_RSVD_LEN_BYTE     4u
#define DOIP_ROUT_ACTIV_REQ_OEM_LEN_BYTE      4u
#define DOIP_ROUT_ACTIV_ACK_MIN_LEN_BYTE      9u
#define DOIP_ROUT_ACTIV_ACK_MAX_LEN_BYTE      13u
#define DOIP_ROUT_ACTIV_ACK_OEM_LEN_BYTE      4u
#define DOIP_DIAG_HDR_LEN_BYTE                4u
#define DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE        4u
#define DOIP_DIAG_MSG_ACK_LEN_BYTE            5u

#define DOIP_HOST_NAME_MIN_SIZE               5u  /* Hostname option size minimum:              "DoIP-" */
#define DOIP_HOST_NAME_VIN_PREFIX_SIZE        8u  /* Hostname option size with VIN prefix only: "DoIP-VIN" */
#define DOIP_HOST_NAME_VIN_SIZE               25u /* Hostname option size with VIN:             "DoIP-VIN<VinValue>" */

#define DOIP_IF_API_ENABLED                   DOIP_IFTXBUF

#define DOIP_DHCP_IPADDRESS_LIST_MAX_SIZE     4u
#define DOIP_PORT_NUMBER                      13400u

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
#define DOIP_MIN(a, b)                        (((a) <= (b)) ? (a) : (b))

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define DOIP_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ( (DOIP_SUPPORT_SHUTDOWN == STD_ON) || (DOIP_DEV_ERROR_DETECT == STD_ON) ) /* COV_DOIP_SUPPORTED */
/*! Indicates current state of the module state machine (valid values: DOIP_STATE_*). */
DOIP_LOCAL VAR(DoIP_StateType, DOIP_VAR_ZERO_INIT) DoIP_State = DOIP_STATE_UNINIT;
#endif /* (DOIP_SUPPORT_SHUTDOWN == STD_ON) || (DOIP_DEV_ERROR_DETECT == STD_ON) */

#define DOIP_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*****************************************************/

#define DOIP_START_SEC_VAR_ZERO_INIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/*! Counter for the number of dropped TCP packets. */
DOIP_LOCAL VAR(DoIP_MeasurementDataType, DOIP_VAR_ZERO_INIT) DoIP_Measure_DroppedTcpPacketsCounter = 0u;

/*! Counter for the number of dropped UDP packets. */
DOIP_LOCAL VAR(DoIP_MeasurementDataType, DOIP_VAR_ZERO_INIT) DoIP_Measure_DroppedUdpPacketsCounter = 0u;
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

#define DOIP_STOP_SEC_VAR_ZERO_INIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*****************************************************/

#define DOIP_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Pointer to the configuration. */
P2CONST(DoIP_ConfigType, DOIP_VAR_ZERO_INIT, DOIP_PBCFG) DoIP_ConfigDataPtr = NULL_PTR;

#define DOIP_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*****************************************************/

#define DOIP_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
/*! Indicates current state of the activation line state (valid values: DOIP_ACTIVATION_LINE_*). */
DOIP_LOCAL VAR(DoIP_ActivationLineType, DOIP_VAR_NOINIT) DoIP_ActivationLineState;

/*! Indicates if activation line state changed to inactive. */
DOIP_LOCAL VAR(boolean, DOIP_VAR_NOINIT) DoIP_ActivationLineInactiveRequest;
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */

#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
/*! Indicates if Pdu size routing is enabled. */
DOIP_LOCAL VAR(boolean, DOIP_VAR_NOINIT) DoIP_IsPduSizeRoutingEnabled;
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */

#if ( DOIP_GID_SYNC_ENABLED == STD_ON )
/*! Indicates if GID is synchronised. */
DOIP_LOCAL VAR(boolean, DOIP_VAR_NOINIT) DoIP_GidInSync;
#endif /* DOIP_GID_SYNC_ENABLED == STD_ON */

#define DOIP_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*****************************************************/

#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ( DOIP_GID_SYNC_ENABLED == STD_ON )
/*! Number of connections with assigned local address. */
DOIP_LOCAL VAR(DoIP_SizeOfConnectionType, DOIP_VAR_NOINIT) DoIP_LocalAddrAssignedCounter;
#endif /* DOIP_GID_SYNC_ENABLED == STD_ON */

#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define DOIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  DoIP_Util_InitCons()
 *********************************************************************************************************************/
/*! \brief          Initializes all connections.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_InitCons(void);

/**********************************************************************************************************************
 *  DoIP_Util_InitChannels()
 *********************************************************************************************************************/
/*! \brief          Initializes all channels.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_InitChannels(void);

/**********************************************************************************************************************
 *  DoIP_Util_InitTesters()
 *********************************************************************************************************************/
/*! \brief          Initializes all testers.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_InitTesters(void);

/**********************************************************************************************************************
 *  DoIP_Util_InitLocalAddrs()
 *********************************************************************************************************************/
/*! \brief          Initializes all IP address assignments.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_InitLocalAddrs(void);

/**********************************************************************************************************************
 *  DoIP_Util_InitRoutActivHandlers()
 *********************************************************************************************************************/
/*! \brief          Initializes all routing activation handlers.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_InitRoutActivHandlers(void);

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Util_InitOemPayloadTypes()
 *********************************************************************************************************************/
/*! \brief          Initializes all OemPayloadTypes variables.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_OEM_PAYLOAD_TYPE_ENABLED
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_InitOemPayloadTypes(void);
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Util_ValidateConfig()
 *********************************************************************************************************************/
/*! \brief          Validates the module configuration.
 *  \details        -
 *  \param[in]      DoIPConfigPtr   Pointer to the configuration data of the DoIP module.
 *  \return         E_OK            Module configuration is valid.
 *  \return         E_NOT_OK        Module configuration is invalid.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_DEV_ERROR_DETECT
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Util_ValidateConfig(
  P2CONST(DoIP_ConfigType, AUTOMATIC, DOIP_CONST) DoIPConfigPtr);
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */

/**********************************************************************************************************************
 *  DoIP_Util_Init()
 *********************************************************************************************************************/
/*! \brief          Initializes the module data structures.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_Init(void);

/**********************************************************************************************************************
 *  DoIP_Util_FillGenHdr()
 *********************************************************************************************************************/
/*! \brief          Fills generic header data into buffer.
 *  \details        -
 *  \param[in]      HdrType       Header type.
 *                                [range: undefined]
 *  \param[in]      HdrLen        Header length.
 *                                [range: undefined]
 *  \param[out]     TgtBufferPtr  Pointer to target buffer.
 *                                [range: POINTER != NULL_PTR && DOIP_GEN_HDR_LEN_BYTE <= sizeof(POINTER)]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_FillGenHdr(
  uint16 HdrType,
  uint32 HdrLen,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr);

/**********************************************************************************************************************
 *  DoIP_Util_FillVin()
 *********************************************************************************************************************/
/*! \brief          Fills VIN data into buffer.
 *  \details        -
 *  \param[out]     TgtBufferPtr  Pointer to target buffer.
 *                                [range: POINTER != NULL_PTR && DOIP_VIN_LEN_BYTE <= sizeof(POINTER)]
 *  \return         E_OK          VIN successful written to buffer.
 *  \return         E_NOT_OK      VIN invalid pattern is written to buffer.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPRetrieveVin
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Util_FillVin(
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr);

/**********************************************************************************************************************
 *  DoIP_Util_FillLocalLogAddr()
 *********************************************************************************************************************/
/*! \brief          Fills logical address data into buffer.
 *  \details        -
 *  \param[out]     TgtBufferPtr  Pointer to target buffer.
 *                                [range: POINTER != NULL_PTR && DOIP_ADDR_LEN_BYTE <= sizeof(POINTER)]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_FillLocalLogAddr(
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr);

/**********************************************************************************************************************
 *  DoIP_Util_FillEid()
 *********************************************************************************************************************/
/*! \brief          Fills EID data into buffer.
 *  \details        -
 *  \param[out]     TgtBufferPtr    Pointer to target buffer.
 *                                  [range: POINTER != NULL_PTR && DOIP_EID_LEN_BYTE <= sizeof(POINTER)]
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \return         E_OK            Data successful written.
 *  \return         E_NOT_OK        Data not successful written.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPPhysicalAddressAsEid
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Util_FillEid(
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr,
  DoIP_SizeOfConnectionType ConnectionIdx);

/**********************************************************************************************************************
 *  DoIP_Util_FillGid()
 *********************************************************************************************************************/
/*! \brief          Fills GID data into buffer.
 *  \details        -
 *  \param[out]     TgtBufferPtr    Pointer to target buffer.
 *                                  [range: POINTER != NULL_PTR && DOIP_GID_LEN_BYTE <= sizeof(POINTER)]
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \return         E_OK            Data successful written.
 *  \return         E_NOT_OK        Data not successful written.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPRetrieveGid
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Util_FillGid(
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr,
  DoIP_SizeOfConnectionType ConnectionIdx);

#if ( !((DOIP_VIN_GID_MASTER == STD_ON ) && (DOIP_USE_EID_AS_GID == STD_ON)) )
/**********************************************************************************************************************
 *  DoIP_Util_FillGidOrInv()
 *********************************************************************************************************************/
/*! \brief          Fills GID or invalid data into buffer.
 *  \details        -
 *  \param[out]     TgtBufferPtr  Pointer to target buffer.
 *                                [range: POINTER != NULL_PTR && DOIP_GID_LEN_BYTE <= sizeof(POINTER)]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPRetrieveGid
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_FillGidOrInv(
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr);
#endif /* !((DOIP_VIN_GID_MASTER == STD_ON ) && (DOIP_USE_EID_AS_GID == STD_ON)) */

/**********************************************************************************************************************
 *  DoIP_Util_FillFurtherAction()
 *********************************************************************************************************************/
/*! \brief          Fills Central Security data into buffer.
 *  \details        -
 *  \param[out]     TgtBufferPtr  Pointer to target buffer.
 *                                [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_FillFurtherAction(
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr);

/**********************************************************************************************************************
 *  DoIP_Util_PutUInt16()
 *********************************************************************************************************************/
/*! \brief          Puts an uint16 into a byte buffer.
 *  \details        -
 *  \param[out]     Buffer  Target buffer.
 *                          [range: POINTER != NULL_PTR && (Offset + 2u) <= sizeof(POINTER)]
 *  \param[in]      Offset  Buffer write offset.
 *                          [range: undefined]
 *  \param[in]      Value   Value to put into buffer.
 *                          [range: undefined]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_Util_PutUInt16(
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) Buffer,
  uint32 Offset,
  uint16 Value);

/**********************************************************************************************************************
 *  DoIP_Util_PutUInt32()
 *********************************************************************************************************************/
/*! \brief          Puts an uint32 into a byte buffer.
 *  \details        -
 *  \param[out]     Buffer  Target buffer.
 *                          [range: POINTER != NULL_PTR && (Offset + 4u) <= sizeof(POINTER)]
 *  \param[in]      Offset  Buffer write offset.
 *                          [range: undefined]
 *  \param[in]      Value   Value to put into buffer.
 *                          [range: undefined]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_Util_PutUInt32(
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) Buffer,
  uint32 Offset,
  uint32 Value);

/**********************************************************************************************************************
 *  DoIP_Util_CheckBufferSizeAndModify()
 *********************************************************************************************************************/
/*! \brief          Saves the BufferSize in BufferSizePtr and modify it according to its data type size.
 *  \details        -
 *  \param[in]      BufferSize      Expected buffer size.
 *                                  [range: undefined]
 *  \param[in,out]  BufferSizePtr   Pointer to remaining size of message.
 *                                  [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_Util_CheckBufferSizeAndModify(
  uint32 BufferSize,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr);

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
# if ( DOIP_IPV6_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Util_CheckIpV6Addr()
 *********************************************************************************************************************/
/*! \brief          Validates the IPv6 address against the invalid IPv6 address types.
 *  \details        -
 *  \param[in]      IpAddr    IPv6 address.
 *                            [range: IPv6 address]
 *  \return         E_OK      IPv6 address is valid and as expected.
 *  \return         E_NOT_OK  Unexpected IPv6 address.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE 
 *  \synchronous    TRUE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS & DOIP_IPV6_ENABLED
 *********************************************************************************************************************/
DOIP_LOCAL_INLINE FUNC(Std_ReturnType, DOIP_CODE) DoIP_Util_CheckIpV6Addr(
  SoAd_SockAddrInetXType IpAddr);
# endif /* DOIP_IPV6_ENABLED == STD_ON */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
# if ( DOIP_IPV4_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Util_CheckIpV4Addr()
 *********************************************************************************************************************/
/*! \brief          Validates the IPv4 address against the invalid IPv4 address types.
 *  \details        -
 *  \param[in]      IpAddr    IPv4 address.
 *                            [range: IPv4 address]
 *  \return         E_OK      IPv4 address is valid and as expected.
 *  \return         E_NOT_OK  Unexpected IPv4 address.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS & DOIP_IPV4_ENABLED
 *********************************************************************************************************************/
DOIP_LOCAL_INLINE FUNC(Std_ReturnType, DOIP_CODE) DoIP_Util_CheckIpV4Addr(
  SoAd_SockAddrInetXType IpAddr);
# endif /* DOIP_IPV4_ENABLED == STD_ON */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Util_CompareIpAddr()
 *********************************************************************************************************************/
/*! \brief          Compares two IP addresses.
 *  \details        -
 *  \param[in]      Domain      IP domain (IPv4/v6).
 *                              [range: SOAD_AF_INET, SOAD_AF_INET6]
 *  \param[in]      IpAddrAPtr  Pointer to first IP address.
 *                              [range: IPv4/v6 address]
 *  \param[in]      IpAddrBPtr  Pointer to second IP address.
 *                              [range: IPv4/v6 address]
 *  \return         TRUE        IP addresses are equal.
 *  \return         FALSE       IP addresses are not equal.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS
 *********************************************************************************************************************/
DOIP_LOCAL_INLINE FUNC(boolean, DOIP_CODE) DoIP_Util_CompareIpAddr(
  SoAd_DomainType Domain,
  P2CONST(uint32, AUTOMATIC, DOIP_APPL_VAR) IpAddrAPtr,
  P2CONST(uint32, AUTOMATIC, DOIP_APPL_VAR) IpAddrBPtr);
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_GetLocalAddrIdxOfDhcpAssignmentByLocalIpAddrId()
 *********************************************************************************************************************/
/*! \brief          Checks that the local address is used by DoIP and that is has a DHCP assignment.
 *  \details        -
 *  \param[in]      LocalIpAddrId     TcpIp local address identifier.
 *                                    [range: undefined]
 *  \param[out]     LocalAddrIdxPtr   Pointer to the found DoIP LocalAddrIdx of the DoIP used local address or
 *                                    value of DoIP_GetSizeOfLocalAddr() if E_NOT_OK is returned.
 *                                    [range: POINTER != NULL_PTR]
 *  \return         E_OK              If local address is used by DoIP and has DHCP assignment.
 *  \return         E_NOT_OK          If local addresss is not used by DoIP or address has no DHCP assignment.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Dhcp_GetLocalAddrIdxOfDhcpAssignmentByLocalIpAddrId(
  SoAd_LocalAddrIdType LocalIpAddrId,
  P2VAR(DoIP_SizeOfLocalAddrType, AUTOMATIC, DOIP_APPL_VAR) LocalAddrIdxPtr);
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_PrepareVendorClassTxBuf()
 *********************************************************************************************************************/
/*! \brief          Writes DHCP vendor option data to buffer.
 *  \details        -
 *  \param[in]      OptionCode              Option code.
 *                                          [range: DOIP_DHCPV4_OPT_VENDOR_CLASS_OPT_CODE,
 *                                                  DOIP_DHCPV6_OPT_VENDOR_CLASS_OPT_CODE]
 *  \param[in,out]  OptionBufferLengthPtr   Pointer to the length of the option buffer
 *                                          (updated to length of option on return).
 *                                          [range: POINTER != NULL_PTR &&
 *                                          IPv4: *POINTER >= DOIP_DHCPV4_OPT_VENDOR_CLASS_MIN_LEN,
 *                                          IPv6: *POINTER >= DOIP_DHCPV6_OPT_VENDOR_CLASS_MIN_LEN]
 *  \param[out]     OptionBufferPtr         Pointer to option buffer to write the data.
 *                                          [range: POINTER != NULL_PTR && OptionBufferLength <= sizeof(POINTER)]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_PrepareVendorClassTxBuf(
  uint16 OptionCode,
  P2VAR(uint16, AUTOMATIC, DOIP_APPL_VAR) OptionBufferLengthPtr,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) OptionBufferPtr);
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_HandleVendorOptsOption()
 *********************************************************************************************************************/
/*! \brief          Processes received DHCP option (vendor opts).
 *  \details        -
 *  \param[in]      LocalAddrIdx        Local address index.
 *                                      [range: LocalAddrIdx < DoIP_GetSizeOfLocalAddr()]
 *  \param[in]      OptionCode          Option code.
 *                                      [range: DOIP_DHCPV4_OPT_VENDOR_OPTS_OPT_CODE,
 *                                              DOIP_DHCPV6_OPT_VENDOR_OPTS_OPT_CODE]
 *  \param[in]      OptionBufferLength  Length of the option buffer.
 *                                      [range: undefined]
 *  \param[in]      OptionBufferPtr     Pointer to option buffer to read the data from.
 *                                      [range: POINTER != NULL_PTR && OptionBufferLength <= sizeof(POINTER)]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_HandleVendorOptsOption(
  DoIP_SizeOfLocalAddrType LocalAddrIdx,
  uint16 OptionCode,
  uint16 OptionBufferLength,
  P2CONST(uint8, AUTOMATIC, DOIP_APPL_VAR) OptionBufferPtr);
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_ValidateVendorOptsRxBuf()
 *********************************************************************************************************************/
/*! \brief          Validates received DHCP vendor opts for correctness regarding RFC.
 *  \details        -
 *  \param[in]      OptionCode          Option code.
 *                                      [range: DOIP_DHCPV4_OPT_VENDOR_OPTS_OPT_CODE,
 *                                              DOIP_DHCPV6_OPT_VENDOR_OPTS_OPT_CODE]
 *  \param[in]      OptionBufferLength  Length of the option buffer.
 *                                      [range: undefined]
 *  \param[in]      OptionBufferPtr     Pointer to option buffer to read the data from.
 *                                      [range: POINTER != NULL_PTR && OptionBufferLength <= sizeof(POINTER)]
 *  \return         E_OK                Data are valid. OptionBufferLength/OptionBufferPtr fullfills the requirements
 *                                      of the DHCP option regarding OptionCode.
 *  \return         E_NOT_OK            Data are not valid.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Dhcp_ValidateVendorOptsRxBuf(
  uint16 OptionCode,
  uint16 OptionBufferLength,
  P2CONST(uint8, AUTOMATIC, DOIP_APPL_VAR) OptionBufferPtr);
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_HandleIpAddrListFromVendorOpts()
 *********************************************************************************************************************/
/*! \brief          Updates IP address list from DHCP vendor opts.
 *  \details        -
 *  \param[in]      LocalAddrIdx        Local address index.
 *                                      [range: LocalAddrIdx < DoIP_GetSizeOfLocalAddr()]
 *  \param[in]      OptionCode          Option code.
 *                                      [range: DOIP_DHCPV4_OPT_VENDOR_OPTS_OPT_CODE,
 *                                              DOIP_DHCPV6_OPT_VENDOR_OPTS_OPT_CODE]
 *  \param[in]      OptionBufferLength  Length of the option buffer.
 *                                      [range: IPv4: OptionBufferLength >= DOIP_DHCPV4_OPT_VENDOR_OPTS_MIN_LEN,
 *                                              IPv6: OptionBufferLength >= DOIP_DHCPV6_OPT_VENDOR_OPTS_MIN_LEN]
 *  \param[in]      OptionBufferPtr     Pointer to option buffer to read the data from.
 *                                      [range: POINTER != NULL_PTR && OptionBufferLength <= sizeof(POINTER)]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_HandleIpAddrListFromVendorOpts(
  DoIP_SizeOfLocalAddrType LocalAddrIdx,
  uint16 OptionCode,
  uint16 OptionBufferLength,
  P2CONST(uint8, AUTOMATIC, DOIP_APPL_VAR) OptionBufferPtr);
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_ReadAndFilterIpAddresses()
 *********************************************************************************************************************/
/*! \brief          Reads the DHCP supplied IP addresses from the buffer and filters them.
 *  \details        Reads, validates and filters IP addresses.
 *  \param[in]      OptionCode              Option code.
 *                                          [range: DOIP_DHCPV4_OPT_VENDOR_OPTS_OPT_CODE,
 *                                                  DOIP_DHCPV6_OPT_VENDOR_OPTS_OPT_CODE]
 *  \param[in]      OptionBufferLength      Length of the option buffer.
 *                                          [range: IPv4: OptionBufferLength >= DOIP_DHCPV4_OPT_VENDOR_OPTS_MIN_LEN,
 *                                                  IPv6: OptionBufferLength >= DOIP_DHCPV6_OPT_VENDOR_OPTS_MIN_LEN]
 *  \param[in]      OptionBufferPtr         Pointer to option buffer to read the data from.
 *                                          [range: POINTER != NULL_PTR && OptionBufferLength <= sizeof(POINTER)]
 *  \param[in,out]  VenOptIpAddrDynListPtr  Pointer to the list to copy valid DHCP supplied IP addresses to.
 *                                          [range: POINTER != NULL_PTR &&
 *                                                  DOIP_DHCP_IPADDRESS_LIST_MAX_SIZE == sizeof(POINTER)]
 *  \return         E_OK                    The VenOptIpAddrDynList contains at least one valid IP address.
 *  \return         E_NOT_OK                The VenOptIpAddrDynList contains no IP addresses.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Dhcp_ReadAndFilterIpAddresses(
  uint16 OptionCode,
  uint16 OptionBufferLength,
  P2CONST(uint8, AUTOMATIC, DOIP_APPL_VAR) OptionBufferPtr,
  P2VAR(DoIP_DhcpIpAddrDynType, AUTOMATIC, DOIP_APPL_VAR) VenOptIpAddrDynListPtr);
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_ValidateIpAddress()
 *********************************************************************************************************************/
/*! \brief          Validates the additional IP addresses received from the DHCP server.
 *  \details        Compares received address against local IP address, unspecified address and loopback address.
 *  \param[in]      IpAddr        The IP address received from DHCP server. 
 *                                [range: IPv4/v6 address]
 *  \return         E_OK          IP address is valid.
 *  \return         E_NOT_OK      IP address is not valid.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Dhcp_ValidateIpAddress(
  SoAd_SockAddrInetXType IpAddr);
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_CompareToLocalIpAddrList()
 *********************************************************************************************************************/
/*! \brief          Compares the received IP address from DHCP to the local address list and updates this info.
 *  \details        A flag is set in the dynamic list to indicate if the new address is same as a previously received
 *                  one.
 *  \param[in]      LocalAddrIdx            Local address index.
 *                                          [range: LocalAddrIdx < DoIP_GetSizeOfLocalAddr()]
 *  \param[in,out]  VenOptIpAddrDynListPtr  Pointer to the list that holds the valid DHCP supplied IP addresses and its
 *                                          info.
 *                                          [range: POINTER != NULL_PTR &&
 *                                                  DOIP_DHCP_IPADDRESS_LIST_MAX_SIZE == sizeof(POINTER)]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_CompareToLocalIpAddrList(
  DoIP_SizeOfLocalAddrType LocalAddrIdx,
  P2VAR(DoIP_DhcpIpAddrDynType, AUTOMATIC, DOIP_APPL_VAR) VenOptIpAddrDynListPtr);
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_UpdateLocalIpAddrList()
 *********************************************************************************************************************/
/*! \brief          Updates the local list of DHCP IP addresses.
 *  \details        Updates the IP address as well as enables vehicle announcement to new IP addresses.
 *  \param[in]      LocalAddrIdx            Local address index.
 *                                          [range: LocalAddrIdx < DoIP_GetSizeOfLocalAddr()]
 *  \param[in]      VenOptIpAddrDynListPtr  Pointer to the list that holds the valid DHCP supplied IP addresses and its
 *                                          info.
 *                                          [range: POINTER != NULL_PTR &&
 *                                                  DOIP_DHCP_IPADDRESS_LIST_MAX_SIZE == sizeof(POINTER)]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_UpdateLocalIpAddrList(
  DoIP_SizeOfLocalAddrType LocalAddrIdx,
  P2CONST(DoIP_DhcpIpAddrDynType, AUTOMATIC, DOIP_APPL_VAR) VenOptIpAddrDynListPtr);
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_ProcessIpAddrListToTriggerVehAnnouncements()
 *********************************************************************************************************************/
/*! \brief          This function triggers vehicle announcements for all local addresses to newly received DHCP Vendor
 *                  Option IP addresses.
 *  \details        -
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_ProcessIpAddrListToTriggerVehAnnouncements(void);
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_HandleVehAnnounceTriggOfIpAddrList()
 *********************************************************************************************************************/
/*! \brief          Handle triggerring of vehicle announcements to newly received DHCP Vendor Option IP addresses.
 *  \details        -
 *  \pre            -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DOIP_CONNECTION_TCP_UDP_TOTAL <= ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[in]      IpAddrListIdx   Index of the DoIP_IpAddrList for the Local address.
 *                                  [range: IpAddrListIdx < DoIP_GetSizeOfIpAddrList()]
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_HandleVehAnnounceTriggOfIpAddrList(
  DoIP_SizeOfConnectionType ConnectionIdx,
  DoIP_IpAddrListIterType IpAddrListIdx);
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

/**********************************************************************************************************************
 *  DoIP_Con_HandleSoConModeChg()
 *********************************************************************************************************************/
/*! \brief          Handles socket state change callback to online/offline.
 *  \details        Notification about a SoAd socket connection state change, e.g. socket connection gets online.
 *  \param[in]      SoConId         Socket connection index specifying the socket connection with the mode change.
 *                                  [range: undefined]
 *  \param[in]      Mode            New mode.
 *                                  [range: SOAD_SOCON_ONLINE, SOAD_SOCON_RECONNECT, SOAD_SOCON_OFFLINE]
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[out]     ErrorIdPtr      Pointer to DET error if one occurred.
 *                                  [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different SoConIds. Non reentrant for the same SoConId.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleSoConModeChg(
  SoAd_SoConIdType SoConId,
  SoAd_SoConModeType Mode,
  DoIP_SizeOfConnectionType ConnectionIdx,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr);

/**********************************************************************************************************************
 *  DoIP_Con_HandleOnlineSoConModeChg()
 *********************************************************************************************************************/
/*! \brief          Handles socket state change callback to online.
 *  \details        Notification about a SoAd socket connection state change, e.g. socket connection gets online.
 *  \param[in]      SoConId         Socket connection index specifying the socket connection with the mode change.
 *                                  [range: undefined]
 *  \param[in]      Mode            New mode.
 *                                  [range: SOAD_SOCON_ONLINE]
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[out]     ErrorIdPtr      Pointer to DET error if one occurred.
 *                                  [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different SoConIds/ConnectionIdxs. Non reentrant for the same
 *                          SoConId/ConnectionIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleOnlineSoConModeChg(
  SoAd_SoConIdType SoConId,
  SoAd_SoConModeType Mode,
  DoIP_SizeOfConnectionType ConnectionIdx,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr);

/**********************************************************************************************************************
 *  DoIP_Con_HandleOfflineSoConModeChg()
 *********************************************************************************************************************/
/*! \brief          Handles socket state change callback to offline.
 *  \details        Notification about a SoAd socket connection state change, e.g. socket connection gets online.
 *  \param[in]      Mode            New mode.
 *                                  [range: SOAD_SOCON_RECONNECT, SOAD_SOCON_OFFLINE]
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionIdxs. Non reentrant for the same ConnectionIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleOfflineSoConModeChg(
  SoAd_SoConModeType Mode,
  DoIP_SizeOfConnectionType ConnectionIdx);

/**********************************************************************************************************************
 *  DoIP_Con_HandleOfflineTcpSoConModeChg()
 *********************************************************************************************************************/
/*! \brief          Handles TCP socket state change callback to offline.
 *  \details        Notification about a SoAd socket connection state change, e.g. socket connection gets online.
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionTcpIdxs. Non reentrant for the same ConnectionTcpIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleOfflineTcpSoConModeChg(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx);

/**********************************************************************************************************************
 *  DoIP_Con_HandleOfflineTcpAliveCheckSoConModeChg()
 *********************************************************************************************************************/
/*! \brief          Handles alive checks on TCP socket state change callback to offline.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionTcpIdxs. Non reentrant for the same ConnectionTcpIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleOfflineTcpAliveCheckSoConModeChg(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx);

/**********************************************************************************************************************
 *  DoIP_Con_HandleOfflineUdpSoConModeChg()
 *********************************************************************************************************************/
/*! \brief          Handles UDP socket state change callback to offline.
 *  \details        Notification about a SoAd socket connection state change, e.g. socket connection gets online.
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionIdxs. Non reentrant for the same ConnectionIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleOfflineUdpSoConModeChg(
  DoIP_SizeOfConnectionType ConnectionIdx);

/**********************************************************************************************************************
 *  DoIP_Con_SoConInitAll()
 *********************************************************************************************************************/
/*! \brief          Initiates connections by extracting socket connection identifier from SoAd if not done before.
 *  \details        -
 *  \param[out]     ErrorIdPtr  Pointer to DET error if one occurred.
 *                              [range: POINTER != NULL_PTR]
 *  \return         E_OK        All socket connections are initialized or already initialized.
 *  \return         E_NOT_OK    Not all socket connections are initzialized.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Con_SoConInitAll(
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr);

/**********************************************************************************************************************
 *  DoIP_Con_SoConOpen()
 *********************************************************************************************************************/
/*! \brief          Opens a socket connection initially after IP address assignment.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_SoConOpen(
  DoIP_SizeOfConnectionType ConnectionIdx);

#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Con_SoConCloseAll()
 *********************************************************************************************************************/
/*! \brief          Closes all socket connections.
 *  \details        -
 *  \return         E_OK      All socket connections are already closed.
 *  \return         E_NOT_OK  Not all socket connections are closed. Closing is requested but not yet performed.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         DOIP_ACTIV_LINE_CALLBACK_ENABLED
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Con_SoConCloseAll(void);
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_Con_SoConClose()
 *********************************************************************************************************************/
/*! \brief          Closes single socket connection.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_SoConClose(
  DoIP_SizeOfConnectionType ConnectionIdx);

/**********************************************************************************************************************
 *  DoIP_Con_HandleLocalIpAddrAssignmentChg()
 *********************************************************************************************************************/
/*! \brief          Handles IP address assignment change callback.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[in]      State           State of IP address assignment.
 *                                  [range: SOAD_IPADDR_STATE_*]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleLocalIpAddrAssignmentChg(
  DoIP_SizeOfConnectionType ConnectionIdx,
  SoAd_IpAddrStateType State);

#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Con_RelAllIpAddrAssign()
 *********************************************************************************************************************/
/*! \brief          Releases all IP address assignments.
 *  \details        Iterate over all UDP connections and release IP address assignment on one UDP connection of each
 *                  local address and check if all local addresses are unassigned.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         DOIP_ACTIV_LINE_CALLBACK_ENABLED
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_RelAllIpAddrAssign(void);
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */

#if ( (DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON) && (DOIP_CONTROL_IP_ASSIGNMENT == STD_ON) )
/**********************************************************************************************************************
 *  DoIP_Con_RelIpAddrAssign()
 *********************************************************************************************************************/
/*! \brief          Releases single IP address assignment.
 *  \details        -
 *  \param[in]      LocalAddrIdx  Local address index.
 *                                [range: LocalAddrIdx < DoIP_GetSizeOfLocalAddr()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         DOIP_ACTIV_LINE_CALLBACK_ENABLED & DOIP_CONTROL_IP_ASSIGNMENT
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_RelIpAddrAssign(
  DoIP_SizeOfLocalAddrType LocalAddrIdx);
#endif /* (DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON) && (DOIP_CONTROL_IP_ASSIGNMENT == STD_ON) */

/**********************************************************************************************************************
 *  DoIP_Con_GetConnectionIdxBySoConId()
 *********************************************************************************************************************/
/*! \brief          Gets the connction index of a socket connection.
 *  \details        -
 *  \param[in]      SoConId         Socket connection identifier.
 *                                  [range: undefined]
 *  \param[out]     ConnectionIdx   Connection Index.
 *                                  [range: POINTER != NULL_PTR]
 *  \return         E_OK            Corresponding Connection found.
 *  \return         E_NOT_OK        Corresponding Connection not found.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Con_GetConnectionIdxBySoConId(
  SoAd_SoConIdType SoConId,
  P2VAR(DoIP_SizeOfConnectionType, AUTOMATIC, DOIP_APPL_VAR) ConnectionIdx);

/**********************************************************************************************************************
 *  DoIP_Con_HandleSoConStates()
 *********************************************************************************************************************/
/*! \brief          Handles socket connection states (i.e. reopens closed socket connections).
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE for TCP connections. TRUE for UDP connections.
 *  \synchronous    FALSE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleSoConStates(void);

#if ( (DOIP_CONTROL_IP_ASSIGNMENT == STD_ON) || (DOIP_IPADDR_ASSIGN_DHCP == STD_ON) )
/**********************************************************************************************************************
 *  DoIP_Con_HandleIpAddrAssignment()
 *********************************************************************************************************************/
/*! \brief          Handles IP address assignment requests and sets the DHCP hostname option.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         DOIP_CONTROL_IP_ASSIGNMENT & DOIP_IPADDR_ASSIGN_DHCP
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleIpAddrAssignment(void);
#endif /* (DOIP_CONTROL_IP_ASSIGNMENT == STD_ON) || (DOIP_IPADDR_ASSIGN_DHCP == STD_ON) */

#if ( DOIP_CONTROL_IP_ASSIGNMENT == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Con_ReqIpAddrAssign()
 *********************************************************************************************************************/
/*! \brief          Requests single IP address assignment and sets DHCP hostname option.
 *  \details        -
 *  \param[in]      LocalAddrIdx          Local address index.
 *                                        [range: LocalAddrIdx < DoIP_GetSizeOfLocalAddr()]
 *  \param[in]      IpAddrAssignmentIdx   IP address assignment index.
 *                                        [range: IpAddrAssignmentIdx < DoIP_GetSizeOfIpAddrAssignment()]
 *  \return         E_OK                  Address assignment is successfully requested.
 *  \return         E_NOT_OK              Address assignment request failed.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         DOIP_CONTROL_IP_ASSIGNMENT
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Con_ReqIpAddrAssign(
  DoIP_SizeOfLocalAddrType LocalAddrIdx,
  DoIP_SizeOfIpAddrAssignmentType IpAddrAssignmentIdx);
#endif /* DOIP_CONTROL_IP_ASSIGNMENT == STD_ON */

#if ( DOIP_IPADDR_ASSIGN_DHCP == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Con_SetDhcpHostname()
 *********************************************************************************************************************/
/*! \brief          Sets DHCP hostname option.
 *  \details        -
 *  \param[in]      LocalAddrIdx    Local address index.
 *                                  [range: LocalAddrIdx < DoIP_GetSizeOfLocalAddr()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         DOIP_IPADDR_ASSIGN_DHCP
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_SetDhcpHostname(
  DoIP_SizeOfLocalAddrType LocalAddrIdx);
#endif /* DOIP_IPADDR_ASSIGN_DHCP == STD_ON */

#if ( DOIP_GID_SYNC_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Con_HandleGidSync()
 *********************************************************************************************************************/
/*! \brief          Handles GID synchronization.
 *  \details        Wait until GID is provided by application.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_GID_SYNC_ENABLED
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleGidSync(void);
#endif /* DOIP_GID_SYNC_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_Con_HandleActLineStates()
 *********************************************************************************************************************/
/*! \brief          Handles activation line state in context of main function.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleActLineStates(void);

/**********************************************************************************************************************
 *  DoIP_Con_HandleActLineStateActive()
 *********************************************************************************************************************/
/*! \brief          Handles activation line state active in context of main function.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleActLineStateActive(void);

#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Con_HandleActLineStateInactive()
 *********************************************************************************************************************/
/*! \brief          Handles activation line state inactive in context of main function.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_ACTIV_LINE_CALLBACK_ENABLED
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleActLineStateInactive(void);
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleRxIndication()
 *********************************************************************************************************************/
/*! \brief          Handles receive indication callback for IF.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx <
 *                                  DOIP_CONNECTION_TCP_UDP_TOTAL]
 *  \param[in]      PduInfoPtr      Pointer to destination buffer and length to be copied.
 *                                  [range: POINTER != NULL_PTR && POINTER->SduDataPtr != NULL_PTR]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionIdxs. Non reentrant for the same ConnectionIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleRxIndication(
  DoIP_SizeOfConnectionType ConnectionIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  DoIP_RxUdp_CheckGenHdr()
 *********************************************************************************************************************/
/*! \brief          Checks generic header of received data.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx <
 *                                  DOIP_CONNECTION_TCP_UDP_TOTAL]
 *  \param[in]      PduInfoPtr      Pointer to destination buffer and length to be copied.
 *                                  [range: POINTER != NULL_PTR && POINTER->SduDataPtr != NULL_PTR]
 *  \param[out]     HdrLen          Header length.
 *                                  [range: POINTER != NULL_PTR]
 *  \param[in]      DataOffset      Data offset to read from PduInfoPtr.
 *                                  [range: DataOffset < sizeof(POINTER->SduDataPtr)]
 *  \return         E_OK            Header check passed.
 *  \return         E_NOT_OK        Header check failed.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionIdxs. Non reentrant for the same ConnectionIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxUdp_CheckGenHdr(
  DoIP_SizeOfConnectionType ConnectionIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(uint32, AUTOMATIC, DOIP_APPL_VAR) HdrLen,
  uint32 DataOffset);

/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleRxIndicationMessageTypes()
 *********************************************************************************************************************/
/*! \brief          Handles received message by there type.
 *  \details        If disabled, a Entity Status Request is handled as an unknown payload type
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx <
 *                                  DOIP_CONNECTION_TCP_UDP_TOTAL]
 *  \param[in]      PduInfoPtr      Pointer to destination buffer and length to be copied.
 *                                  [range: POINTER != NULL_PTR &&
 *                                          POINTER->SduDataPtr != NULL_PTR &&
 *                                          POINTER->SduLength >= DOIP_GEN_HDR_LEN_BYTE &&
 *                                          POINTER->SduLength == sizeof(POINTER->SduDataPtr)]
 *  \param[in]      DataOffset      Data offset to read from PduInfoPtr.
 *                                  [range: DataOffset <= sizeof(POINTER->SduDataPtr) - DOIP_GEN_HDR_LEN_BYTE]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionIdxs. Non reentrant for the same ConnectionIdx.
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPSupportISO13400-2
 *  \trace          DSGN-DoIPEntityStatus
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleRxIndicationMessageTypes(
  DoIP_SizeOfConnectionType ConnectionIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  uint32 DataOffset);

/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleVehicleIdentReq()
 *********************************************************************************************************************/
/*! \brief          Handles received Vehicle Ident Requests.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx <
 *                                  DOIP_CONNECTION_TCP_UDP_TOTAL]
 *  \param[in]      PduInfoPtr      Pointer to destination buffer and length to be copied.
 *                                  [range: POINTER != NULL_PTR &&
 *                                          POINTER->SduDataPtr != NULL_PTR &&
 *                                          POINTER->SduLength >= DOIP_GEN_HDR_LEN_BYTE &&
 *                                          POINTER->SduLength == sizeof(POINTER->SduDataPtr)]
 *  \param[in]      DataOffset      Data offset to read from PduInfoPtr.
 *                                  [range: DataOffset <= sizeof(POINTER->SduDataPtr) - DOIP_GEN_HDR_LEN_BYTE]
 *  \param[in]      CloseSocket     Indicates if a socket shall be closed after transmission.
 *                                  [range: TRUE, FALSE]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionIdxs. Non reentrant for the same ConnectionIdx.
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPSupportISO13400-2, DSGN-DoIPVehicleIdentification
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleVehicleIdentReq(
  DoIP_SizeOfConnectionType ConnectionIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  uint32 DataOffset,
  boolean CloseSocket);

/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleVehicleIdentReqVin()
 *********************************************************************************************************************/
/*! \brief          Handles received Vehicle Ident Requests with VIN.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx <
 *                                  DOIP_CONNECTION_TCP_UDP_TOTAL]
 *  \param[in]      PduInfoPtr      Pointer to destination buffer and length to be copied.
 *                                  [range: POINTER != NULL_PTR &&
 *                                          POINTER->SduDataPtr != NULL_PTR &&
 *                                          POINTER->SduLength >= DOIP_GEN_HDR_LEN_BYTE &&
 *                                          POINTER->SduLength == sizeof(POINTER->SduDataPtr)]
 *  \param[in]      DataOffset      Data offset to read from PduInfoPtr.
 *                                  [range: DataOffset <= sizeof(POINTER->SduDataPtr) - DOIP_GEN_HDR_LEN_BYTE]
 *  \param[in]      CloseSocket     Indicates if a socket shall be closed after transmission.
 *                                  [range: TRUE, FALSE]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionIdxs. Non reentrant for the same ConnectionIdx.
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPSupportISO13400-2, DSGN-DoIPVehicleIdentification
 *********************************************************************************************************************/
/* PRQA S 0779 5 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleVehicleIdentReqVin(
  DoIP_SizeOfConnectionType ConnectionIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  uint32 DataOffset,
  boolean CloseSocket);

#if ( DOIP_VEHICLE_IDENT_EID_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleVehicleIdentReqEid()
 *********************************************************************************************************************/
/*! \brief          Handles received Vehicle Ident Requests with EID.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx <
 *                                  DOIP_CONNECTION_TCP_UDP_TOTAL]
 *  \param[in]      PduInfoPtr      Pointer to destination buffer and length to be copied.
 *                                  [range: POINTER != NULL_PTR &&
 *                                          POINTER->SduDataPtr != NULL_PTR &&
 *                                          POINTER->SduLength >= DOIP_GEN_HDR_LEN_BYTE &&
 *                                          POINTER->SduLength == sizeof(POINTER->SduDataPtr)]
 *  \param[in]      DataOffset      Data offset to read from PduInfoPtr.
 *                                  [range: DataOffset <= sizeof(POINTER->SduDataPtr) - DOIP_GEN_HDR_LEN_BYTE]
 *  \param[in]      CloseSocket     Indicates if a socket shall be closed after transmission.
 *                                  [range: TRUE, FALSE]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionIdxs. Non reentrant for the same ConnectionIdx.
 *  \synchronous    TRUE
 *  \config         DOIP_VEHICLE_IDENT_EID_SUPPORT
 *  \trace          DSGN-DoIPSupportISO13400-2, DSGN-DoIPVehicleIdentification
 *********************************************************************************************************************/
/* PRQA S 0779 5 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleVehicleIdentReqEid(
  DoIP_SizeOfConnectionType ConnectionIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  uint32 DataOffset,
  boolean CloseSocket);
#endif /* DOIP_VEHICLE_IDENT_EID_SUPPORT == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleDiagPowerModeInfoReq()
 *********************************************************************************************************************/
/*! \brief          Handles received Diagnostic Power Mode Requests.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx <
 *                                  DOIP_CONNECTION_TCP_UDP_TOTAL]
 *  \param[in]      PduInfoPtr      Pointer to destination buffer and length to be copied.
 *                                  [range: POINTER != NULL_PTR &&
 *                                          POINTER->SduDataPtr != NULL_PTR &&
 *                                          POINTER->SduLength >= DOIP_GEN_HDR_LEN_BYTE &&
 *                                          POINTER->SduLength == sizeof(POINTER->SduDataPtr)]
 *  \param[in]      DataOffset      Data offset to read from PduInfoPtr.
 *                                  [range: DataOffset <= sizeof(POINTER->SduDataPtr) - DOIP_GEN_HDR_LEN_BYTE]
 *  \param[in]      CloseSocket     Indicates if a socket shall be closed after transmission.
 *                                  [range: TRUE, FALSE]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionIdxs. Non reentrant for the same ConnectionIdx.
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPDiagnosticPowerMode, DSGN-DoIPSupportISO13400-2, DSGN-DoIPNodeInformation
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleDiagPowerModeInfoReq(
  DoIP_SizeOfConnectionType ConnectionIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  uint32 DataOffset,
  boolean CloseSocket);

#if ( DOIP_ENTITY_STATE_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleEntityStateReq()
 *********************************************************************************************************************/
/*! \brief          Handles received Entity State Requests.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx <
 *                                  DOIP_CONNECTION_TCP_UDP_TOTAL]
 *  \param[in]      PduInfoPtr      Pointer to destination buffer and length to be copied.
 *                                  [range: POINTER != NULL_PTR &&
 *                                          POINTER->SduDataPtr != NULL_PTR &&
 *                                          POINTER->SduLength >= DOIP_GEN_HDR_LEN_BYTE &&
 *                                          POINTER->SduLength == sizeof(POINTER->SduDataPtr)]
 *  \param[in]      DataOffset      Data offset to read from PduInfoPtr.
 *                                  [range: DataOffset <= sizeof(POINTER->SduDataPtr) - DOIP_GEN_HDR_LEN_BYTE]
 *  \param[in]      CloseSocket     Indicates if a socket shall be closed after transmission.
 *                                  [range: TRUE, FALSE]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionIdxs. Non reentrant for the same ConnectionIdx.
 *  \synchronous    TRUE
 *  \config         DOIP_ENTITY_STATE_SUPPORT
 *  \trace          DSGN-DoIPSupportISO13400-2, DSGN-DoIPNodeInformation
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleEntityStateReq(
  DoIP_SizeOfConnectionType ConnectionIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  uint32 DataOffset,
  boolean CloseSocket);
#endif /* DOIP_ENTITY_STATE_SUPPORT == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleUnknownHdrType()
 *********************************************************************************************************************/
/*! \brief          Handles received messages with unknown header type.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx <
 *                                  DOIP_CONNECTION_TCP_UDP_TOTAL]
 *  \param[in]      PduInfoPtr      Pointer to destination buffer and length to be copied.
 *                                  [range: POINTER != NULL_PTR &&
 *                                          POINTER->SduDataPtr != NULL_PTR &&
 *                                          POINTER->SduLength >= DOIP_GEN_HDR_LEN_BYTE &&
 *                                          POINTER->SduLength == sizeof(POINTER->SduDataPtr)]
 *  \param[in]      DataOffset      Data offset to read from PduInfoPtr.
 *                                  [range: DataOffset <= sizeof(POINTER->SduDataPtr) - DOIP_GEN_HDR_LEN_BYTE]
 *  \param[in]      CloseSocket     Indicates if a socket shall be closed after transmission.
 *                                  [range: TRUE, FALSE]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionIdxs. Non reentrant for the same ConnectionIdx.
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPOemSpecificPayloadType
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleUnknownHdrType(
  DoIP_SizeOfConnectionType ConnectionIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  uint32 DataOffset,
  boolean CloseSocket);

/**********************************************************************************************************************
 *  DoIP_TxUdp_Transmit()
 *********************************************************************************************************************/
/*! \brief          Transmits UDP messages immediately or delayed.
 *  \details        Depending on message type the message is transmitted immediately or delayed. If transmit failed
 *                  message gets delayed by adding the transmit to the retry list.
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[in]      HdrType         Message header type.
 *                                  [range: DOIP_HDR_TYPE_* (but only DoIP TX UDP header types)]
 *  \param[in]      Param           Parameter depending on header type (e.g. negative acknowledge code).
 *                                  [range: undefined]
 *  \param[in]      CloseSocket     Indicates if a socket shall be closed after transmission.
 *                                  [range: TRUE, FALSE]
 *  \param[in]      RemoteAddress   Indicates the supposed remote address of this connection.
 *                                  [range: POINTER may be NULL_PTR]
 *  \return         E_OK            Transmission requested.
 *  \return         E_NOT_OK        Transmission request failed.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_Transmit(
  DoIP_SizeOfConnectionType ConnectionIdx,
  uint16 HdrType,
  uint16 Param,
  boolean CloseSocket,
  P2CONST(SoAd_SockAddrInetXType, AUTOMATIC, DOIP_APPL_VAR) RemoteAddress);

/**********************************************************************************************************************
 *  DoIP_TxUdp_TransmitImmediately()
 *********************************************************************************************************************/
/*! \brief          Transmits UDP messages immediately.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[in]      HdrType         Message header type.
 *                                  [range: DOIP_HDR_TYPE_* (but only DoIP TX UDP header types)]
 *  \param[in]      Param           Parameter depending on header type (e.g. negative acknowledge code).
 *                                  [range: undefined]
 *  \param[in]      CloseSocket     Indicates if a socket shall be closed after transmission.
 *                                  [range: TRUE, FALSE]
 *  \return         E_OK            Transmission requested.
 *  \return         E_NOT_OK        Transmission request failed.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_TransmitImmediately(
  DoIP_SizeOfConnectionType ConnectionIdx,
  uint16 HdrType,
  uint16 Param,
  boolean CloseSocket);

/**********************************************************************************************************************
 *  DoIP_TxUdp_TransmitDelayed()
 *********************************************************************************************************************/
/*! \brief          Transmits UDP messages delayed.
 *  \details        Stores transmission request for DoIP messages (UDP) in a retry list.
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[in]      HdrType         Message header type.
 *                                  [range: DOIP_HDR_TYPE_* (but only DoIP TX UDP header types)]
 *  \param[in]      Param           Parameter depending on header type (e.g. negative acknowledge code).
 *                                  [range: undefined]
 *  \param[in]      CloseSocket     Indicates if a socket shall be closed after transmission.
 *                                  [range: TRUE, FALSE]
 *  \param[in]      RemoteAddress   Indicates the supposed remote address of this connection.
 *                                  [range: POINTER may be NULL_PTR]
 *  \return         E_OK            Transmission requested.
 *  \return         E_NOT_OK        Transmission request failed.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_TransmitDelayed(
  DoIP_SizeOfConnectionType ConnectionIdx,
  uint16 HdrType,
  uint16 Param,
  boolean CloseSocket,
  P2CONST(SoAd_SockAddrInetXType, AUTOMATIC, DOIP_APPL_VAR) RemoteAddress);

/**********************************************************************************************************************
 *  DoIP_TxUdp_TransmitDelayedSetVehAnnSpecParams()
 *********************************************************************************************************************/
/*! \brief          Sets Vehicle Announcement and Vehicle Identification Response specific parameters in the UDP retry
 *                  list.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[in]      TxUdpListIdx    List index of handled entry.
 *                                  [range: TxUdpListIdx < DoIP_GetSizeOfTxUdpMgtList()]
 *  \param[in]      RemoteAddress   Indicates the supposed remote address of this connection.
 *                                  [range: POINTER may be NULL_PTR]
 *  \return         E_OK            Transmission requested.
 *  \return         E_NOT_OK        Transmission request failed.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxUdp_TransmitDelayedSetVehAnnSpecParams(
  DoIP_SizeOfConnectionType ConnectionIdx,
  DoIP_TxUdpMgtListIterType TxUdpListIdx,
  P2CONST(SoAd_SockAddrInetXType, AUTOMATIC, DOIP_APPL_VAR) RemoteAddress);

/**********************************************************************************************************************
 *  DoIP_TxUdp_SingleTransmit()
 *********************************************************************************************************************/
/*! \brief          Transmits single UDP messages immediately.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[in]      HdrType         Message header type.
 *                                  [range: DOIP_HDR_TYPE_* (but only DoIP TX UDP header types)]
 *  \param[in]      Param           Parameter depending on header type (e.g. negative acknowledge code).
 *                                  [range: undefined]
 *  \return         E_OK            Transmission requested.
 *  \return         E_NOT_OK        Transmission request failed.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_SingleTransmit(
  DoIP_SizeOfConnectionType ConnectionIdx,
  uint16 HdrType,
  uint16 Param);

/**********************************************************************************************************************
 *  DoIP_TxUdp_SingleTransmitGenNack()
 *********************************************************************************************************************/
/*! \brief          Transmits Generic Negative Acknowledge UDP messages immediately.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[in]      HdrType         Message header type.
 *                                  [range: DOIP_HDR_TYPE_* (but only DoIP TX UDP header types)]
 *  \param[in]      NackCode        Negative acknowledge code.
 *                                  [range: undefined]
 *  \return         E_OK            Transmission requested.
 *  \return         E_NOT_OK        Transmission request failed.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPSupportISO13400-2
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_SingleTransmitGenNack(
  DoIP_SizeOfConnectionType ConnectionIdx,
  uint16 HdrType,
  uint8 NackCode);

/**********************************************************************************************************************
 *  DoIP_TxUdp_SingleTransmitVehicleAnnounceAndIdentRes()
 *********************************************************************************************************************/
/*! \brief          Transmits Vehicle Announcements and Vehicle Identification Responses immediately.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \return         E_OK            Transmission requested.
 *  \return         E_NOT_OK        Transmission request failed.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPSupportISO13400-2, DSGN-DoIPVehicleIdentification
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_SingleTransmitVehicleAnnounceAndIdentRes(
  DoIP_SizeOfConnectionType ConnectionIdx);

/**********************************************************************************************************************
 *  DoIP_TxUdp_SingleTransmitDiagPowerModeInfoRes()
 *********************************************************************************************************************/
/*! \brief          Transmits Diagnostic Power Mode Info Response UDP messages immediately.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[in]      DiagPowerMode   Diagnostic Power Mode.
 *                                  [range: undefined]
 *  \return         E_OK            Transmission requested.
 *  \return         E_NOT_OK        Transmission request failed.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPSupportISO13400-2, DSGN-DoIPNodeInformation
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_SingleTransmitDiagPowerModeInfoRes(
  DoIP_SizeOfConnectionType ConnectionIdx,
  uint8 DiagPowerMode);

#if ( DOIP_ENTITY_STATE_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  DoIP_TxUdp_SingleTransmitEntityStateRes()
 *********************************************************************************************************************/
/*! \brief          Transmits Entity State Response UDP messages immediately.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \return         E_OK            Transmission requested.
 *  \return         E_NOT_OK        Transmission request failed.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_ENTITY_STATE_SUPPORT
 *  \trace          DSGN-DoIPSupportISO13400-2, DSGN-DoIPNodeInformation
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_SingleTransmitEntityStateRes(
  DoIP_SizeOfConnectionType ConnectionIdx);
#endif /* DOIP_ENTITY_STATE_SUPPORT == STD_ON */

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_TxUdp_SingleTransmitOemSpecific()
 *********************************************************************************************************************/
/*! \brief          Transmits OEM Specific UDP messages immediately.
 *  \details        -
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[in]      HdrTypeOem      OEM specific message header type.
 *                                  [range: undefined]
 *  \return         E_OK            Transmission requested.
 *  \return         E_NOT_OK        Transmission request failed.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_OEM_PAYLOAD_TYPE_ENABLED
 *  \trace          DSGN-DoIPSupportISO13400-2, DSGN-DoIPOemSpecificPayloadType
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_SingleTransmitOemSpecific(
  DoIP_SizeOfConnectionType ConnectionIdx,
  uint16 HdrTypeOem);
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_TxUdpList_CloseSocket()
 *********************************************************************************************************************/
/*! \brief          Handles socket connection closing considering remaining Tx UDP list entries if it is requested to
 *                  be closed already. If it is not requested to be closed already, parameter "CloseSocket" can be used
 *                  to request the closing of the socket.
 *  \details        -
 *  \param[in]      ConnectionIdx     Connection Index.
 *                                    [range: ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[in]      CloseSocket       Indicates if a socket shall be closed after transmission.
 *                                    [range: TRUE, FALSE]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxUdpList_CloseSocket(
  DoIP_SizeOfConnectionType ConnectionIdx,
  boolean CloseSocket);

/**********************************************************************************************************************
 *  DoIP_TxUdpList_HandleEntries()
 *********************************************************************************************************************/
/*! \brief          Handles pending Tx UDP list entries.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxUdpList_HandleEntries(void);

/**********************************************************************************************************************
 *  DoIP_TxUdpList_HandleEntriesVehicleAnnounceAndIdentRes()
 *********************************************************************************************************************/
/*! \brief          Handles pending Tx UDP list entries for Vehicle Announcements and Vehicle Identification Responses.
 *  \details        -
 *  \param[in]      TxUdpListIdx    List index of handled entry.
 *                                  [range: TxUdpListIdx < DoIP_GetSizeOfTxUdpMgtList()]
 *  \param[in]      ConnectionIdx   Connection Index.
 *                                  [range: ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxUdpList_HandleEntriesVehicleAnnounceAndIdentRes(
  DoIP_SizeOfTxUdpMgtListType TxUdpListIdx,
  DoIP_SizeOfConnectionType ConnectionIdx);

/**********************************************************************************************************************
 *  DoIP_TxUdpList_HandleEntriesOthers()
 *********************************************************************************************************************/
/*! \brief          Handles pending Tx UDP list entries for Generic Negative Acknowledge, Entity State Status and
 *                  Diagnostic Power Mode Responses.
 *  \details        -
 *  \param[in]      TxUdpListIdx      List index of handled entry.
 *                                    [range: TxUdpListIdx < DoIP_GetSizeOfTxUdpMgtList()]
 *  \param[in]      ConnectionIdx     Connection Index.
 *                                    [range: ConnectionIdx < DoIP_GetSizeOfConnection()]
 *  \param[out]     ReleaseListEntry  Indicates if entry is handled and can be released from list.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxUdpList_HandleEntriesOthers(
  DoIP_SizeOfTxUdpMgtListType TxUdpListIdx,
  DoIP_SizeOfConnectionType ConnectionIdx,
  P2VAR(boolean, AUTOMATIC, DOIP_APPL_VAR) ReleaseListEntry);

/**********************************************************************************************************************
 *  DoIP_TxTcp_Transmit()
 *********************************************************************************************************************/
/*! \brief          Requests a transmission of a TCP message.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      HdrType           Message header type.
 *                                    [range: DOIP_HDR_TYPE_* (but only DoIP TX TCP header types)]
 *  \param[in]      Param1            First parameter depending on header type.
 *                                    [range: undefined]
 *  \param[in]      Param2            Second parameter depending on header type.
 *                                    [range: undefined]
 *  \param[in]      Param3            Third parameter depending on header type.
 *                                    [range: undefined]
 *  \param[in]      DataPtr           Pointer to data depending on header type.
 *                                    [range: POINTER (may be NULL_PTR)]
 *  \param[in]      CloseSocket       Indicates if a socket shall be closed after transmission.
 *                                    [range: TRUE, FALSE]
 *  \return         E_OK              Request successful.
 *  \return         E_NOT_OK          Request failed.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxTcp_Transmit(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  uint16 HdrType,
  uint16 Param1,
  uint32 Param2,
  uint8  Param3,
  SduDataPtrType DataPtr,
  boolean CloseSocket);

/**********************************************************************************************************************
 *  DoIP_TxTcp_PrepareTransmit()
 *********************************************************************************************************************/
/*! \brief          Stores a transmit request for a message which is not ready yet.
 *  \details        In case of a received diagnostic message a corresponding negative acknowledge may be sent. If the
 *                  message is not yet received completely the transmission is prepared with this function but
 *                  performed when the message is received completely to append the diagnostic data to the negative
 *                  acknowledge message.
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      HdrType           Message header type.
 *                                    [range: DOIP_HDR_TYPE_* (but only DoIP TX TCP header types)]
 *  \param[in]      Param1            First parameter depending on header type.
 *                                    [range: undefined]
 *  \param[in]      Param2            Second parameter depending on header type.
 *                                    [range: undefined]
 *  \param[in]      Param3            Third parameter depending on header type.
 *                                    [range: undefined]
 *  \param[in]      CloseSocket       Indicates if a socket shall be closed after transmission.
 *                                    [range: TRUE, FALSE]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcp_PrepareTransmit(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  uint16 HdrType,
  uint16 Param1,
  uint32 Param2,
  uint8  Param3,
  boolean CloseSocket);

/**********************************************************************************************************************
 *  DoIP_TxTcp_FinishTransmit()
 *********************************************************************************************************************/
/*! \brief          Finish a pending transmission of a message which was requested by DoIP_TxTcp_PrepareTransmit().
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcp_FinishTransmit(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx);

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_Add()
 *********************************************************************************************************************/
/*! \brief          Adds a DoIP TCP message to Tx TCP queue
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      HdrType           Message header type.
 *                                    [range: DOIP_HDR_TYPE_* (but only DoIP TX TCP header types)]
 *  \param[in]      Param1            First parameter depending on header type.
 *                                    [range: undefined]
 *  \param[in]      Param2            Second parameter depending on header type.
 *                                    [range: undefined]
 *  \param[in]      Param3            Third parameter depending on header type.
 *                                    [range: undefined]
 *  \param[in]      DataPtr           Pointer to data depending on header type.
 *                                    [range: POINTER (may be NULL_PTR)]
 *  \return         E_OK              The DoIP TCP message could be added.
 *  \return         E_NOT_OK          The DoIP TCP message could not be added.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_Add(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  uint16 HdrType,
  uint16 Param1,
  uint32 Param2,
  uint8  Param3,
  SduDataPtrType DataPtr);

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddGenNack()
 *********************************************************************************************************************/
/*! \brief          Adds a DoIP TCP Generic Negative Acknowledge message to Tx TCP queue.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first free element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      NackCode          Negative acknowledge code.
 *                                    [range: undefined]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddGenNack(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  uint8 NackCode);

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddRoutingActivationRes()
 *********************************************************************************************************************/
/*! \brief          Adds a DoIP TCP Routing Activation Response message to Tx TCP queue.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first free element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      TesterAddr        Tester logical Address.
 *                                    [range: undefined]
 *  \param[in]      AckCode           Acknowledge code.
 *                                    [range: undefined]
 *  \param[in]      TesterIdx         Tester Index.
 *                                    [range: undefined]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddRoutingActivationRes(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  uint16 TesterAddr,
  uint8 AckCode,
  DoIP_SizeOfTesterType TesterIdx);

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddAliveCheckReq()
 *********************************************************************************************************************/
/*! \brief          Adds a DoIP TCP Alive Check Request message to Tx TCP queue.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first free element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddAliveCheckReq(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx);

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddDiagReq()
 *********************************************************************************************************************/
/*! \brief          Adds a DoIP TCP Diagnostic Reuqest message to Tx TCP queue.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first free element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      ChannelIdx        Channel Index.
 *                                    [range: undefined]
 *  \param[in]      Length            Pdu length.
 *                                    [range: undefined]
 *  \param[in]      DataPtr           Pointer to data.
 *                                    [range: POINTER (may be NULL_PTR)]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddDiagReq(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  DoIP_SizeOfChannelType ChannelIdx,
  PduLengthType Length,
  SduDataPtrType DataPtr);

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddDiagAck()
 *********************************************************************************************************************/
/*! \brief          Adds a DoIP TCP Diagnostic Positive Acknowledge message to Tx TCP queue.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first free element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      EcuAddr           ECU logical Address.
 *                                    [range: undefined]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddDiagAck(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  uint16 EcuAddr);

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddDiagNack()
 *********************************************************************************************************************/
/*! \brief          Adds a DoIP TCP Diagnostic Negative Acknowledge message to Tx TCP queue.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first free element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      EcuAddr           ECU logical Address.
 *                                    [range: undefined]
 *  \param[in]      TesterAddr        Tester logical Address.
 *                                    [range: undefined]
 *  \param[in]      NackCode          Negative acknowledge code.
 *                                    [range: undefined]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddDiagNack(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  uint16 EcuAddr,
  uint16 TesterAddr,
  uint8 NackCode);

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddOem()
 *********************************************************************************************************************/
/*! \brief          Adds a DoIP TCP OEM message to Tx TCP queue.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first free element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      HdrTypeOem        OEM message header type.
 *                                    [range: undefined]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_OEM_PAYLOAD_TYPE_ENABLED
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddOem(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  uint16 HdrTypeOem);
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_Copy()
 *********************************************************************************************************************/
/*! \brief          Copies buffer stored in first Tx TCP queue element to a target buffer.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to destination buffer and length to be copied.
 *                                    [range: POINTER != NULL_PTR, if POINTER->SduLength == 0 then POINTER->SduDataPtr
 *                                    may be NULL_PTR]
 *  \param[out]     AvailableDataPtr  Available transmission buffer size after data are copied to destination buffer.
 *                                    [range: POINTER != NULL_PTR]
 *  \return         BUFREQ_OK         Data has been copied sucessful.
 *  \return         BUFREQ_E_NOT_OK   Data has not been copied.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_Copy(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr);

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyHeader()
 *********************************************************************************************************************/
/*! \brief          Copies header stored in first Tx TCP queue element to a target buffer.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to destination buffer and length to be copied.
 *                                    [range: POINTER != NULL_PTR, if POINTER->SduLength == 0 then POINTER->SduDataPtr
 *                                    may be NULL_PTR]
 *  \param[out]     AvailableDataPtr  Available transmission buffer size after data are copied to destination buffer.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[out]     HdrCopied         Indicates if header is copied completely.
 *                                    [range: POINTER != NULL_PTR]
 *  \return         BUFREQ_OK         Data has been copied sucessful.
 *  \return         BUFREQ_E_NOT_OK   Data has not been copied.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_CopyHeader(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,
  P2VAR(boolean, AUTOMATIC, DOIP_APPL_VAR) HdrCopied);

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyData()
 *********************************************************************************************************************/
/*! \brief          Copies data stored in first Tx TCP queue element to a target buffer.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to destination buffer and length to be copied.
 *                                    [range: POINTER != NULL_PTR, if POINTER->SduLength == 0 then POINTER->SduDataPtr
 *                                    may be NULL_PTR]
 *  \param[out]     AvailableDataPtr  Available transmission buffer size after data are copied to destination buffer.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in]      HdrCopied         Indicates if header is copied completely.
 *                                    [range: TRUE, FALSE]
 *  \return         BUFREQ_OK         Data has been copied sucessful.
 *  \return         BUFREQ_E_NOT_OK   Data has not been copied.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_CopyData(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,
  boolean HdrCopied);

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyDiagReq()
 *********************************************************************************************************************/
/*! \brief          Copies diagnostic request stored in first Tx TCP queue element to a target buffer.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to destination buffer and length to be copied.
 *                                    [range: POINTER != NULL_PTR, if POINTER->SduLength == 0 then POINTER->SduDataPtr
 *                                    may be NULL_PTR]
 *  \param[out]     AvailableDataPtr  Available transmission buffer size after data are copied to destination buffer.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in]      HdrCopied         Indicates if header is copied completely.
 *                                    [range: TRUE, FALSE]
 *  \return         BUFREQ_OK         Data has been copied sucessful.
 *  \return         BUFREQ_E_NOT_OK   Data has not been copied.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_CopyDiagReq(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,
  boolean HdrCopied);

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyDiagReqTP()
 *********************************************************************************************************************/
/*! \brief          Copies TP diagnostic request stored in first Tx TCP queue element to a target buffer.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to destination buffer and length to be copied.
 *                                    [range: POINTER != NULL_PTR, if POINTER->SduLength == 0 then POINTER->SduDataPtr
 *                                    may be NULL_PTR]
 *  \param[out]     AvailableDataPtr  Available transmission buffer size after data are copied to destination buffer.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in]      HdrCopied         Indicates if header is copied completely.
 *                                    [range: TRUE, FALSE]
 *  \return         BUFREQ_OK         Data has been copied sucessful.
 *  \return         BUFREQ_E_NOT_OK   Data has not been copied.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 6 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_CopyDiagReqTP(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,
  boolean HdrCopied);

#if ( DOIP_IF_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyDiagReqIF()
 *********************************************************************************************************************/
/*! \brief          Copies IF diagnostic request stored in first Tx TCP queue element to a target buffer.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to destination buffer and length to be copied.
 *                                    [range: POINTER != NULL_PTR, if POINTER->SduLength == 0 then POINTER->SduDataPtr
 *                                    may be NULL_PTR]
 *  \param[out]     AvailableDataPtr  Available transmission buffer size after data are copied to destination buffer.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in]      HdrCopied         Indicates if header is copied completely.
 *                                    [range: TRUE, FALSE]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 6 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_CopyDiagReqIF(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,
  boolean HdrCopied);
#endif /* DOIP_IF_API_ENABLED == STD_ON */

#if ( DOIP_NACK_APPEND_REQ == STD_ON )
/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyDiagAck()
 *********************************************************************************************************************/
/*! \brief          Copies buffer stored in first Tx TCP queue element to a target buffer.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to destination buffer and length to be copied.
 *                                    [range: POINTER != NULL_PTR, if POINTER->SduLength == 0 then POINTER->SduDataPtr
 *                                    may be NULL_PTR]
 *  \param[out]     AvailableDataPtr  Available transmission buffer size after data are copied to destination buffer.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in]      HdrCopied         Indicates if header is copied completely.
 *                                    [range: TRUE, FALSE]
 *  \return         BUFREQ_OK         Data has been copied sucessful.
 *  \return         BUFREQ_E_NOT_OK   Data has not been copied.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_NACK_APPEND_REQ
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_CopyDiagAck(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,
  boolean HdrCopied);
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
# if ( DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u )
/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyOemSpecific()
 *********************************************************************************************************************/
/*! \brief          Copies buffer stored in first Tx TCP queue element to a target buffer.
 *  \details        -
 *  \param[in]      QueueIdx          Index of the first element in the Tx TCP queue.
 *                                    [range: QueueIdx < DoIP_GetSizeOfTxTcpMgt() &&
                                              QueueIdx < (DoIP_GetSizeOfTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
                                                          DoIP_GetSizeOfTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx))]
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to destination buffer and length to be copied.
 *                                    [range: POINTER != NULL_PTR, if POINTER->SduLength == 0 then POINTER->SduDataPtr
 *                                    may be NULL_PTR]
 *  \param[out]     AvailableDataPtr  Available transmission buffer size after data are copied to destination buffer.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in]      HdrCopied         Indicates if header is copied completely.
 *                                    [range: TRUE, FALSE]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_OEM_PAYLOAD_TYPE_ENABLED & DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_CopyOemSpecific(
  DoIP_SizeOfTxTcpMgtType QueueIdx,
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,
  boolean HdrCopied);
# endif /* DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u */
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_TransmitElement()
 *********************************************************************************************************************/
/*! \brief          Triggers transmission of Tx TCP queue.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_TransmitElement(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx);

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_RemoveElement()
 *********************************************************************************************************************/
/*! \brief          Removes first Tx TCP queue element (used to confirm transmission of element).
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      Result            Result of transmission.
 *                                    [range: E_OK, E_NOT_OK]
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_RemoveElement(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  Std_ReturnType Result);

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_HandleTransmit()
 *********************************************************************************************************************/
/*! \brief          Handles pending Tx TCP queue elements.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_HandleTransmit(void);

/**********************************************************************************************************************
 *  DoIP_RxTcpGen_CopyGenHdr()
 *********************************************************************************************************************/
/*! \brief          Copies Generic Header to header buffer.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to destination buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  ReadDataLenPtr    Pointer to data offset for read/write. Number of copied bytes will be added.
 *                                    [range: POINTER != NULL_PTR]
 *  \return         E_OK              Header (already) copied completely.
 *  \return         E_NOT_OK          Header not copied completely.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpGen_CopyGenHdr(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpGen_CopyDataToHeaderBuffer()
 *********************************************************************************************************************/
/*! \brief          Copies data to header buffer.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to source buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  ReadDataLenPtr    Pointer to data offset for read/write. Number of copied bytes will be added.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in]      BytesToCopy       Number of bytes to copy.
 *                                    [range: undefined]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpGen_CopyDataToHeaderBuffer(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr,
  uint32 BytesToCopy);

/**********************************************************************************************************************
 *  DoIP_RxTcp_HandleCopyRxData()
 *********************************************************************************************************************/
/*! \brief          Handles SoAd copy calles.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in,out]  PduInfoPtr        Pointer to source buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[out]     ErrorIdPtr        Pointer to DET error if one occurred.
 *                                    [range: POINTER != NULL_PTR]
 *  \return         BUFREQ_OK         Data copied successfully.
 *  \return         BUFREQ_E_NOT_OK   Data was not copied because an error occurred.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionTcpIdxs. Non reentrant for the same ConnectionTcpIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_RxTcp_HandleCopyRxData(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcp_HandleCopyRxDataCopy()
 *********************************************************************************************************************/
/*! \brief          Handles message copying.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in,out]  PduInfoPtr        Pointer to source buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[out]     ErrorIdPtr        Pointer to DET error if one occurred.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionTcpIdxs. Non reentrant for the same ConnectionTcpIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcp_HandleCopyRxDataCopy(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcp_HandleCopyRxDataCopyBody()
 *********************************************************************************************************************/
/*! \brief          Handles message body copying.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in,out]  PduInfoPtr        Pointer to source buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  ReadDataLenPtr    Pointer to data offset for read/write. Number of copied bytes will be added.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[out]     ErrorIdPtr        Pointer to DET error if one occurred.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionTcpIdxs. Non reentrant for the same ConnectionTcpIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 6 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcp_HandleCopyRxDataCopyBody(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr);

#if ( DOIP_NACK_APPEND_REQ == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcp_HandleCopyRxDataAppendNack()
 *********************************************************************************************************************/
/*! \brief          Handles copying of the Nack data.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in,out]  PduInfoPtr        Pointer to source buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  ReadDataLenPtr    Pointer to data offset for read/write. Number of copied bytes will be added.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionTcpIdxs. Non reentrant for the same ConnectionTcpIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcp_HandleCopyRxDataAppendNack(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2CONST(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr);
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleRoutingActivationReq()
 *********************************************************************************************************************/
/*! \brief          Processes Routing Activation Request messages.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to destination buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  ReadDataLenPtr    Pointer to data offset for read/write. Number of copied bytes will be added.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[out]     ErrorIdPtr        Pointer to DET error if one occurred.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPRoutingActivationAuthenticationConfirmation
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleRoutingActivationReq(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleCopiedRoutingActivationReq()
 *********************************************************************************************************************/
/*! \brief          Processes Routing Activation Request messages if copied to local buffer completely.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[out]     ErrorIdPtr        Pointer to DET error if one occurred.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleCopiedRoutingActivationReq(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleCopiedRoutingActivationReqOem()
 *********************************************************************************************************************/
/*! \brief          Processes OEM part of a Routing Activation Request message.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 2 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleCopiedRoutingActivationReqOem(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_CheckForRegisteredTester()
 *********************************************************************************************************************/
/*! \brief          Checks if a tester is already registered on the connection and if it is the same as in this routing
 *                  activation request.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      TesterIdx         Tester Index.
 *                                    [range: TesterIdx < DoIP_GetSizeOfTester()]
 *  \return         E_OK              Tester is already registered for this connection or not registered at all and at
 *                                    least one other TCP connection is left.
 *  \return         E_NOT_OK          Tester is registered to another connection or no other TCP connection is left.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_CheckForRegisteredTester(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  DoIP_SizeOfTesterType TesterIdx);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_GetRoutingActivationIdxByActivationType()
 *********************************************************************************************************************/
/*! \brief          Returns the routing activation index of a routing activation type for a specific tester or the
 *                  corresponding routing activation response in case no routing activation index could be found.
 *  \details        Considers the required security of the activation type and the security level of the socket.
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      TesterIdx         Tester Index.
 *                                    [range: TesterIdx < DoIP_GetSizeOfTester()]
 *  \param[in]      ActivationType    Activation type.
 *                                    [range: undefined]
 *  \param[out]     RoutActIdxPtr     Pointer to routing activation index.
 *                                    [range: IN:   POINTER != NULL_PTR,
 *                                            OUT:  RoutActIdxPtr <= DoIP_GetSizeOfRoutingActivation()]
 *  \param[out]     ResponseCodePtr   Pointer to response code.
 *                                    [range: IN:   POINTER != NULL_PTR,
 *                                            OUT:  DOIP_ROUT_ACTIV_RES_CODE_INV_ACTIV_TYPE,
 *                                                  DOIP_ROUT_ACTIV_RES_CODE_REQUIRE_SECURE]
 *  \return         E_OK              Routing activation index found/returned and response code is not set.
 *  \return         E_NOT_OK          Routing activation index not found/returned and response code is set.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPRoutingActivationSecurityRequirement
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_GetRoutingActivationIdxByActivationType(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  DoIP_SizeOfTesterType TesterIdx,
  uint8 ActivationType,
  P2VAR(DoIP_SizeOfRoutingActivationType, AUTOMATIC, DOIP_APPL_VAR) RoutActIdxPtr,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ResponseCodePtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_CheckConnectionNum()
 *********************************************************************************************************************/
/*! \brief          Checks if tester is not active on another connection and an additional connection is left. If there
 *                  is no free connection alive checks gets triggered.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      TesterAddr        Tester logical Address.
 *                                    [range: undefined]
 *  \param[out]     ErrorIdPtr        Pointer to DET error if one occurred.
 *                                    [range: POINTER != NULL_PTR]
 *  \return         E_OK              Tester is not active and an additional connection is left.
 *  \return         E_NOT_OK          Tester is active or no additional connection is left.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_CheckConnectionNum(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  uint16 TesterAddr,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_TriggerAliveCheckSingleConnection()
 *********************************************************************************************************************/
/*! \brief          Performs alive check a single connection with registered tester.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[out]     ErrorIdPtr        Pointer to DET error if one occurred.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 3 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_TriggerAliveCheckSingleConnection(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_TriggerAliveCheckAllConnections()
 *********************************************************************************************************************/
/*! \brief          Performs alive checks on all local address related connections with registered testers.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[out]     ErrorIdPtr        Pointer to DET error if one occurred.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 3 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_TriggerAliveCheckAllConnections(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_GetTesterIdxByTesterAddr()
 *********************************************************************************************************************/
/*! \brief          Gets the tester index of a tester address.
 *  \details        -
 *  \param[in]      TesterAddr  Tester logical address.
 *                              [range: undefined]
 *  \param[out]     TesterIdx   Tester index in configured tester array.
 *                              [range: POINTER != NULL_PTR]
 *  \return         E_OK        Tester index found.
 *  \return         E_NOT_OK    No tester index found.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_GetTesterIdxByTesterAddr(
  uint16 TesterAddr,
  P2VAR(DoIP_SizeOfTesterType, AUTOMATIC, DOIP_APPL_VAR) TesterIdx);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_GetConnectionIdxOfTesterAddr()
 *********************************************************************************************************************/
/*! \brief          Identifies a connection by tester address.
 *  \details        -
 *  \param[in]      TesterAddr  Tester logical address.
 *                              [range: undefined]
 *  \return         Connection TCP Index or DoIP_GetSizeOfConnectionTcp() if not tester was found.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(DoIP_SizeOfConnectionTcpType, DOIP_CODE) DoIP_RxTcpRout_GetConnectionIdxOfTesterAddr(
  uint16 TesterAddr);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_GetAvailableSockNum()
 *********************************************************************************************************************/
/*! \brief          Returns the number of available TCP_DATA sockets for the connection related connection group (i.e.
 *                  local port/IP address, socket connection group).
 *  \details        Since different local ports are used for secured and non-secured connections (or any other reason),
 *                  the connections are located in different socket connection groups. On each socket connection group
 *                  n+1 TCP_DATA sockets must be available to support the alive check mechanism to cleanup unused TCP
 *                  connections.
 *  \param[in]      ConnectionGroupIdx  Connection group index.
 *                                      [range: ConnectionGroupIdx < DoIP_GetSizeOfConnectionGroup()]
 *  \return         Number              Number of available TCP_DATA sockets.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(DoIP_ConnectionTcpIterType, DOIP_CODE) DoIP_RxTcpRout_GetAvailableSockNum(
  DoIP_SizeOfConnectionGroupType ConnectionGroupIdx);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_PerformRoutingActivation()
 *********************************************************************************************************************/
/*! \brief          Performs authentication and confirmation via OEM specific part and activates routing if successful.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \trace          DSGN-DoIPRoutingActivationAuthenticationConfirmation
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_PerformRoutingActivation(void);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_RegisterTester()
 *********************************************************************************************************************/
/*! \brief          Register authentified or confirmed tester.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      TesterIdx         Tester index in configured tester array.
 *                                    [range: TesterIdx <= DoIP_GetSizeOfTester()]
 *  \param[in]      TesterAddr        Logical target address.
 *                                    [range: undefined]
 *  \param[in]      RoutActIdx        Routing activation index.
 *                                    [range: RoutActIdx <= DoIP_GetSizeOfRoutingActivation()]
 *  \param[in]      NextState         Next routing activation state.
 *                                    [range: DOIP_ROUT_ACTIV_STATE_*]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_RegisterTester(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  DoIP_SizeOfTesterType TesterIdx,
  uint16 TesterAddr,
  DoIP_SizeOfRoutingActivationType RoutActIdx,
  DoIP_RoutActivStateType NextState);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_PerformRoutingActivationAuth()
 *********************************************************************************************************************/
/*! \brief          Performs routing activation authentication.
 *  \details        -
 *  \param[out]     NextStatePtr  Pointer to next routing activation state.
 *                                [range: POINTER != NULL_PTR]
 *  \return         E_OK          Authentication successfully performed.
 *  \return         E_NOT_OK      Authentication not successfully performed.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \trace          DSGN-DoIPRoutingActivationAuthenticationConfirmation
 *********************************************************************************************************************/
/* PRQA S 0779 2 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_PerformRoutingActivationAuth(
  P2VAR(DoIP_RoutActivStateType, AUTOMATIC, DOIP_APPL_VAR) NextStatePtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_PerformRoutingActivationConf()
 *********************************************************************************************************************/
/*! \brief          Performs routing activation confirmation.
 *  \details        -
 *  \param[in,out]  NextStatePtr  Indicates next state for main function retry handling.
 *                                [range: POINTER != NULL_PTR && *POINTER == DOIP_ROUT_ACTIV_STATE_*]
 *  \return         E_OK          Confirmation successfully performed.
 *  \return         E_NOT_OK      Confirmation not successfully performed.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \trace          DSGN-DoIPRoutingActivationAuthenticationConfirmation
 *********************************************************************************************************************/
/* PRQA S 0779 2 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_PerformRoutingActivationConf(
  P2VAR(DoIP_RoutActivStateType, AUTOMATIC, DOIP_APPL_VAR) NextStatePtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleRetryRoutingActivationAuthAndConf()
 *********************************************************************************************************************/
/*! \brief          Handles authentication and confirmation of routing activations dependent on the state.
 *  \details        Called in MainFunction after routing activation was processed in reception context
 *                  (DoIP_RxTcpRout_PerformRoutingActivation).
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPRoutingActivationAuthenticationConfirmation
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleRetryRoutingActivationAuthAndConf(void);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleAliveCheckTimeouts()
 *********************************************************************************************************************/
/*! \brief          Handles alive check DoIP protocol timeouts.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 1 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleAliveCheckTimeouts(void);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleAliveCheckTimeoutsSocketsClose()
 *********************************************************************************************************************/
/*! \brief          Closes sockets if alive check timeout occurred and no alive check response has been received on it.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 1 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleAliveCheckTimeoutsSocketsClose(void);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_CheckConnectionAvailablility()
 *********************************************************************************************************************/
/*! \brief          Checks if tester is not active on another connection and an additional connection is left. If there
 *                  is no free connection request gets discarded.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \return         E_OK              Tester is not active and an additional connection is left.
 *  \return         E_NOT_OK          Tester is active or no additional connection is left.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_CheckConnectionAvailablility(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx);

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleInactivityTimeouts()
 *********************************************************************************************************************/
/*! \brief          Handles inactivity DoIP protocol timeouts.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleInactivityTimeouts(void);

/**********************************************************************************************************************
 *  DoIP_RxTcpAlive_HandleAliveCheckRes()
 *********************************************************************************************************************/
/*! \brief          Processes Alive Check Response messages.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to source buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the alive check response.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  ReadDataLenPtr    Pointer to data offset for read/write. Number of copied bytes will be added.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpAlive_HandleAliveCheckRes(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpAlive_HandleCopiedAliveCheckRes()
 *********************************************************************************************************************/
/*! \brief          Processes copied Alive Check Response messages.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpAlive_HandleCopiedAliveCheckRes(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx);

/**********************************************************************************************************************
 *  DoIP_RxTcpAlive_RemoveAliveCheckFromRoutActHandler()
 *********************************************************************************************************************/
/*! \brief          Removes an alive check entry in alive check list of routing activation handler.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpAlive_RemoveAliveCheckFromRoutActHandler(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx);

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleDiagnosticMessage()
 *********************************************************************************************************************/
/*! \brief          Processes Diagnostic messages.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to destination buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  ReadDataLenPtr    Pointer to data offset for read/write. Number of copied bytes will be added.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpDiag_HandleDiagnosticMessage(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleValidDiagnosticMessage()
 *********************************************************************************************************************/
/*! \brief          Processes valid diagnostic message.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to source buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  ReadDataLenPtr    Pointer to data offset for read/write. Number of copied bytes will be added.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 5 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpDiag_HandleValidDiagnosticMessage(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_CopyLogicalAddr()
 *********************************************************************************************************************/
/*! \brief          Copies logical address of diagnostic message.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to source buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  ReadDataLenPtr    Pointer to data offset for read/write. Number of copied bytes will be added.
 *                                    [range: POINTER != NULL_PTR]
 *  \return         E_OK              Logical address (already) successfully copied.
 *  \return         E_NOT_OK          Logical address not successfully copied.
 *  \return         DOIP_E_PENDING    Logical address partly copied.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_CopyLogicalAddr(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleCopiedLogicalAddr()
 *********************************************************************************************************************/
/*! \brief          Handles copied logical address of diagnostic message.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \return         E_OK              Logical address valid.
 *  \return         E_NOT_OK          Logical address invalid.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_HandleCopiedLogicalAddr(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx);

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleTargetLogicalAddress()
 *********************************************************************************************************************/
/*! \brief          Handles target logical address of diagnostic message.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \return         E_OK              Logical address valid.
 *  \return         E_NOT_OK          Logical address invalid.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPForwardReceivedTargetAddressWithTargetAddressVerification
 *********************************************************************************************************************/
/* PRQA S 0779 2 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_HandleTargetLogicalAddress(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx);

#if ( DOIP_NACK_APPEND_REQ == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_AppendNackData()
 *********************************************************************************************************************/
/*! \brief          Appends Diagnostic data to Ack/Nack buffer.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to source buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  ReadDataLenPtr    Pointer to data offset for read/write. Number of copied bytes will be added.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_NACK_APPEND_REQ
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpDiag_AppendNackData(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,
  P2CONST(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr);
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_VerifyRxPdu()
 *********************************************************************************************************************/
/*! \brief          Verifies Rx Pdu and start reception. Check lenghts.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to source buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  ReadDataLenPtr    Pointer to data offset for read/write. Number of copied bytes will be added.
 *                                    [range: POINTER != NULL_PTR]
 *  \return         E_OK              Rx Pdu (already) successfully verified.
 *  \return         E_NOT_OK          Rx Pdu not successfully verified.
 *  \return         DOIP_E_PENDING    Rx Pdu verification pending or all data copied during this function call.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-DoIPPduReceptionVerification
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_VerifyRxPdu(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleCopiedVerifyRxPdu()
 *********************************************************************************************************************/
/*! \brief          Verifies Rx Pdu and start reception. Processes copied Rx Pdu.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      HdrLen            Header length.
 *                                    [range: HdrLen >= DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \return         E_OK              Rx Pdu (already) successfully verified.
 *  \return         E_NOT_OK          Rx Pdu not successfully verified.
 *  \return         DOIP_E_PENDING    Rx Pdu verification pending or all data copied during this function call.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_HandleCopiedVerifyRxPdu(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  uint32 HdrLen,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr);

#if ( (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_CopyVerifiedUserData()
 *********************************************************************************************************************/
/*! \brief          Copies verified user data.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in]      QueryBufSize      Indicates if buffer size has to be queried.
 *                                    [range: TRUE, FALSE]
 *  \return         E_OK              Verified user data (already) successfully copied.
 *  \return         E_NOT_OK          Verified user data not successfully copied.
 *  \return         DOIP_E_PENDING    Verified user data copy pending.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_VERIFY_RX_PDU_ENABLED & DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_CopyVerifiedUserData(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  boolean QueryBufSize);
#endif /* (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) */

#if ( (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleCopyVerifiedUserData()
 *********************************************************************************************************************/
/*! \brief          Handles copying verified user data.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      HdrLen            Header length.
 *                                    [range: HdrLen >= DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in]      QueryBufSize      Indicates if buffer size has to be queried.
 *                                    [range: TRUE, FALSE]
 *  \return         E_OK              Verified user data (already) successfully copied.
 *  \return         E_NOT_OK          Verified user data not successfully copied.
 *  \return         DOIP_E_PENDING    Verified user data copy pending.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_VERIFY_RX_PDU_ENABLED & DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_HandleCopyVerifiedUserData(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  uint32 HdrLen,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  boolean QueryBufSize);
#endif /* (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_CopyUserData()
 *********************************************************************************************************************/
/*! \brief          Copies user data.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to source buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  ReadDataLenPtr    Pointer to data offset for read/write. Number of copied bytes will be added.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpDiag_CopyUserData(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_CopyDataToPduR()
 *********************************************************************************************************************/
/*! \brief          Copies data to PduR.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  LocalPduInfoPtr   Pointer to local buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \return         E_OK              Data successfully copied.
 *  \return         E_NOT_OK          Data not successfully copied.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_CopyDataToPduR(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) LocalPduInfoPtr);

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutAct()
 *********************************************************************************************************************/
/*! \brief          Retrieves a channel by target address for a specific routing activation considering data length in
 *                  case of Pdu size routing.
 *  \details        -
 *  \param[in]      RoutActIdx      Routing activation index.
 *                                  [range: RoutActIdx < DoIP_GetSizeOfRoutingActivation()]
 *  \param[in]      TgtAddr         Logical target address.
 *                                  [range: undefined]
 *  \param[in]      DataLen         Data length.
 *                                  [range: 0 <= DataLen <= (DOIP_MAX_REQUEST_BYTES - DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE)]
 *  \param[in]      PduSizeRouting  Pdu size routing.
 *                                  [range: TRUE, FALSE]
 *  \return         Channel index or invalid channel index.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(DoIP_SizeOfChannelType, DOIP_CODE) DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutAct(
  DoIP_SizeOfRoutingActivationType RoutActIdx,
  uint16 TgtAddr,
  uint32 DataLen,
  boolean PduSizeRouting);

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutActUseBinSearch()
 *********************************************************************************************************************/
/*! \brief          Retrieves a channel by target address for a specific routing activation considering data length in
 *                  case of Pdu size routing use binary search.
 *  \details        -
 *  \param[in]      RoutActIdx      Routing activation index.
 *                                  [range: RoutActIdx < DoIP_GetSizeOfRoutingActivation()]
 *  \param[in]      TgtAddr         Logical target address.
 *                                  [range: undefined]
 *  \param[in]      DataLen         Data length.
 *                                  [range: 0 <= DataLen <= (DOIP_MAX_REQUEST_BYTES - DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE)]
 *  \param[in]      PduSizeRouting  Pdu size routing.
 *                                  [range: TRUE, FALSE]
 *  \return         Channel index or invalid channel index.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 4 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelType, DOIP_CODE) DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutActUseBinSearch(
  DoIP_SizeOfRoutingActivationType RoutActIdx,
  uint16 TgtAddr,
  uint32 DataLen,
  boolean PduSizeRouting);

#if ( DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutActUseIteration()
 *********************************************************************************************************************/
/*! \brief          Retrieves a channel by target address for a specific routing activation in case of bit masking use
 *                  iteration.
 *  \details        -
 *  \param[in]      RoutActIdx  Routing activation index.
 *                              [range: RoutActIdx < DoIP_GetSizeOfRoutingActivation()]
 *  \param[in]      TgtAddr     Logical target address.
 *                              [range: undefined]
 *  \return         Channel index or invalid channel index.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 3 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelType, DOIP_CODE) DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutActUseIteration(
  DoIP_SizeOfRoutingActivationType RoutActIdx,
  uint16 TgtAddr);
#endif /* DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_GetChannelByTgtAddr()
 *********************************************************************************************************************/
/*! \brief          Retrieves a channel by target address.
 *  \details        -
 *  \param[in]      TgtAddr   Logical target address.
 *                            [range: undefined]
 *  \return         Channel index or invalid channel index.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 2 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelType, DOIP_CODE) DoIP_RxTcpDiag_GetChannelByTgtAddr(
  uint16 TgtAddr);

#if ( DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_OFF )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_GetChannelByTgtAddrUseBinSearch()
 *********************************************************************************************************************/
/*! \brief          Retrieves a channel by target address use binary search.
 *  \details        -
 *  \param[in]      TgtAddr   Logical target address.
 *                            [range: undefined]
 *  \return         Channel index or invalid channel index.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 2 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelType, DOIP_CODE) DoIP_RxTcpDiag_GetChannelByTgtAddrUseBinSearch(
  uint16 TgtAddr);
#endif /* DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_OFF */

#if ( DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_GetChannelByTgtAddrUseIteration()
 *********************************************************************************************************************/
/*! \brief          Retrieves a channel by target address use iteration.
 *  \details        -
 *  \param[in]      TgtAddr   Logical target address.
 *                            [range: undefined]
 *  \return         Channel index or invalid channel index.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 0779 2 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelType, DOIP_CODE) DoIP_RxTcpDiag_GetChannelByTgtAddrUseIteration(
  uint16 TgtAddr);
#endif /* DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_SearchChannel()
 *********************************************************************************************************************/
/*! \brief          Searches a channel by target address for a specific routing activation.
 *  \details        A binary search is used to find the channel.
 *  \param[in]      RoutActIdx  Routing activation index.
 *                              [range: RoutActIdx < DoIP_GetSizeOfRoutingActivation()]
 *  \param[in]      TgtAddr     Logical target address.
 *                              [range: undefined]
 *  \return         Found channel indirection index.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(DoIP_SizeOfChannelIndType, DOIP_CODE) DoIP_RxTcpDiag_SearchChannel(
  DoIP_SizeOfRoutingActivationType RoutActIdx,
  uint16 TgtAddr);

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_CheckChannel()
 *********************************************************************************************************************/
/*! \brief          Checks for a better fitting channel by target address for a specific routing activation considering
 *                  data length in case of Pdu size routing.
 *  \details        -
 *  \param[in]      RoutActIdx      Routing activation index.
 *                                  [range: RoutActIdx < DoIP_GetSizeOfRoutingActivation()]
 *  \param[in]      TgtAddr         Logical target address.
 *                                  [range: undefined]
 *  \param[in]      DataLen         Data length.
 *                                  [range: 0 <= DataLen <= (DOIP_MAX_REQUEST_BYTES - DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE)]
 *  \param[in]      ChannelIndIdx   Found channel index to check.
 *                                  [range: ChannelIndIdx < DoIP_GetSizeOfChannelInd()]
 *  \param[in]      PduSizeRouting  Pdu size routing.
 *                                  [range: TRUE, FALSE]
 *  \return         Found channel indirectionindex.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(DoIP_SizeOfChannelIndType, DOIP_CODE) DoIP_RxTcpDiag_CheckChannel(
  DoIP_SizeOfRoutingActivationType RoutActIdx,
  uint16 TgtAddr,
  uint32 DataLen,
  DoIP_SizeOfChannelIndType ChannelIndIdx,
  boolean PduSizeRouting);

#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_SearchPduSizeRoutingGroupStartIndex()
 *********************************************************************************************************************/
/*! \brief          Searchs for the (left side) start index of the pdu size routing group with the same target address
 *                  on the same routing activation.
 *  \details        -
 *  \param[in]      RoutActIdx      Routing activation index.
 *                                  [range: RoutActIdx < DoIP_GetSizeOfRoutingActivation()]
 *  \param[in]      TgtAddr         Logical target address.
 *                                  [range: undefined]
 *  \param[in]      ChannelIndIdx   Found channel indirection index to check.
 *                                  [range: ChannelIndIdx < DoIP_GetSizeOfChannelInd()]
 *  \return         Found channel indirection start index of pdu size routing group.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_SUPPORT_PDU_SIZE_ROUTING
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(DoIP_SizeOfChannelIndType, DOIP_CODE) DoIP_RxTcpDiag_SearchPduSizeRoutingGroupStartIndex(
  DoIP_SizeOfRoutingActivationType RoutActIdx,
  uint16 TgtAddr,
  DoIP_SizeOfChannelIndType ChannelIndIdx);
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */

#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_SearchPduSizeRoutingGroupBestIndex()
 *********************************************************************************************************************/
/*! \brief          Searchs for the best matching channel by target address for a specific routing activation
 *                  considering data length. Teh search is performed from the (left side) start index to the right side.
 *  \details        -
 *  \param[in]      RoutActIdx          Routing activation index.
 *                                      [range: RoutActIdx < DoIP_GetSizeOfRoutingActivation()]
 *  \param[in]      TgtAddr             Logical target address.
 *                                      [range: undefined]
 *  \param[in]      DataLen             Data length.
 *                                      [range: 0 <= DataLen <= (DOIP_MAX_REQUEST_BYTES - DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE)]
 *  \param[in]      ChannelIndStartIdx  Found channel indirection start index to check.
 *                                      [range: ChannelIndIdx < DoIP_GetSizeOfChannelInd()]
 *  \param[in]      PduSizeRouting      Pdu size routing.
 *                                      [range: TRUE, FALSE]
 *  \return         Found channel indirection index of best matching channel.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_SUPPORT_PDU_SIZE_ROUTING
 *********************************************************************************************************************/
 /* PRQA S 0779 5 */ /* MD_MSR_Rule5.2_0779 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelIndType, DOIP_CODE) DoIP_RxTcpDiag_SearchPduSizeRoutingGroupBestIndex(
  DoIP_SizeOfRoutingActivationType RoutActIdx,
  uint16 TgtAddr,
  uint32 DataLen,
  DoIP_SizeOfChannelIndType ChannelIndStartIdx,
  boolean PduSizeRouting);
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */

#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_PduSizeRoutValidateChannel()
 *********************************************************************************************************************/
/*! \brief          Validates if a channel is the best fitting channel for a target address.
 *  \details        -
 *  \param[in]      ChannelIdx      Channel index.
 *                                  [range: ChannelIdx < DoIP_GetSizeOfChannel()]
 *  \param[in]      DataLen         Data length.
 *                                  [range: 0 <= DataLen <= (DOIP_MAX_REQUEST_BYTES - DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE)]
 *  \param[in,out]  BestMaxPduSize  Configured length of best matching channel up to now.
 *                                  [range: POINTER != NULL_PTR]
 *  \param[in]      PduSizeRouting  Pdu size routing.
 *                                  [range: TRUE, FALSE]
 *  \return         E_OK            Best matching channel (up to now).
 *  \return         E_NOT_OK        Channel does not match.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_SUPPORT_PDU_SIZE_ROUTING
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_PduSizeRoutValidateChannel(
  DoIP_SizeOfChannelType ChannelIdx,
  uint32 DataLen,
  P2VAR(DoIP_MaxPduSizeOfChannelType, AUTOMATIC, DOIP_APPL_VAR) BestMaxPduSize,
  boolean PduSizeRouting);
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */

#if ( (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleRetryCopyVerifiedUserData()
 *********************************************************************************************************************/
/*! \brief          Handles coping of verified user data.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_VERIFY_RX_PDU_ENABLED & DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpDiag_HandleRetryCopyVerifiedUserData(void);
#endif /* (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) */

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpOem_HandleOemPayloadTypes()
 *********************************************************************************************************************/
/*! \brief          Processes OEM specific messages.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Pointer to destination buffer and length.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  BufferSizePtr     Pointer to remaining size of the diagnostic message.
 *                                    [range: POINTER != NULL_PTR]
 *  \param[in,out]  ReadDataLenPtr    Pointer to data offset for read/write. Number of copied bytes will be added.
 *                                    [range: POINTER != NULL_PTR]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_OEM_PAYLOAD_TYPE_ENABLED
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpOem_HandleOemPayloadTypes(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr);
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
# if ( DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u )
/**********************************************************************************************************************
 *  DoIP_RxTcpOem_HandleCopiedOemPayloadTypes()
 *********************************************************************************************************************/
/*! \brief          Processes copied OEM specific messages.
 *  \details        -
 *  \param[in]      ConnectionTcpIdx  Connection Index.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_OEM_PAYLOAD_TYPE_ENABLED & DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpOem_HandleCopiedOemPayloadTypes(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx);
# endif /* DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u */
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_HandleTpTransmit()
 *********************************************************************************************************************/
/*! \brief          Handles transmission request of a specific TP Pdu
 *  \details        This service is called to request the transfer data from the PduRouter to the SoAd. It is used to
 *                  indicate the transmission which will be performed by SoAd or in the DoIP_Mainfunction. Within the
 *                  provided DoIPPduRTxInfoPtr only SduLength is valid (no data)! If this function returns E_OK then
 *                  the SoAd module will raise a subsequent call to PduR_DoIPCopyTxData via DoIP_SoAdTpCopyRxData in
 *                  order to get the data to send.
 *  \param[in]      DoIPPduRTxId        DoIP unique identifier of the Pdu to be transmitted by the PduR.
 *                                      [range: DoIPPduRTxId < DoIP_GetSizeOfPduRTxPduId()]
 *  \param[in]      DoIPPduRTxInfoPtr   Tx Pdu information structure which contains the length of the DoIPTxMessage.
 *                                      [range: POINTER != NULL_PTR && POINTER->SduLength > 0]
 *  \return         E_OK                The request has been accepted.
 *  \return         E_NOT_OK            The request has not been accepted, e.g. no resources are available for
 *                                      transmission.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE - Reentrant for different DoIPPduRTxIds. Non reentrant for the same DoIPPduRTxId.
 *  \synchronous    FALSE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_HandleTpTransmit(
  DoIP_SizeOfPduRTxPduIdType DoIPPduRTxId,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) DoIPPduRTxInfoPtr);

#if ( DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON )
/**********************************************************************************************************************
 *  DoIP_HandleTpCancelTransmit()
 *********************************************************************************************************************/
/*! \brief          Handles transmission request cancellation of a specific TP Pdu
 *  \details        This service primitive is used to cancel the transfer of pending DoIPPduRTxIds. The connection is
 *                  identified by DoIPPduRTxId. If the function returns the cancellation is requested but not yet
 *                  performed.
 *  \param[in]      DoIPPduRTxId  DoIP unique identifier of the Pdu to be canceled by the PduR.
 *                                [range: DoIPPduRTxId < DoIP_GetSizeOfPduRTxPduId()]
 *  \return         E_OK          Transmit cancellation request of the specified DoIPPduRTxId is accepted.
 *  \return         E_NOT_OK      The transmit cancellation request of the DoIPPduRTxId has been rejected.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_HandleTpCancelTransmit(
  DoIP_SizeOfPduRTxPduIdType DoIPPduRTxId);
#endif /* DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON */

#if ( DOIP_PROVIDE_CANCEL_RECEIVE_API == STD_ON )
/**********************************************************************************************************************
 *  DoIP_HandleTpCancelReceive()
 *********************************************************************************************************************/
/*! \brief          Handles reception cancellation request of a specific TP Pdu
 *  \details        By calling this API with the corresponding DoIPPduRRxId the currently ongoing data reception is
 *                  terminated immediately. If the function returns the cancellation is requested but not yet
 *                  performed.
 *  \param[in]      DoIPPduRRxId  DoIP unique identifier of the Pdu for which reception shall be canceled by the PduR.
 *                                [range: DoIPPduRRxId < DoIP_GetSizeOfPduRRxCancelPduId()]
 *  \return         E_OK          Reception was canceled successfully.
 *  \return         E_NOT_OK      Reception was not canceled.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_HandleTpCancelReceive(
  DoIP_SizeOfPduRRxCancelPduIdType DoIPPduRRxId);
#endif /* DOIP_PROVIDE_CANCEL_RECEIVE_API == STD_ON */

#if ( DOIP_IF_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_HandleIfTransmit()
 *********************************************************************************************************************/
/*! \brief          Handles transmission request of a specific IF Pdu
 *  \details        -
 *  \param[in]      PduRTxPduId   Identification of the IF Pdu.
 *                                [range: PduRTxPduId < DoIP_GetSizeOfPduRTxPduId()]
 *  \param[in]      PduInfoPtr    Length and pointer to the buffer of the IF Pdu.
 *                                [range: POINTER != NULL_PTR && POINTER->SduLength > 0]
 *  \return         E_OK          Request is accepted by the destination module.
 *  \return         E_NOT_OK      Request is not accepted by the destination module.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE - Reentrant for different ids. Non reentrant for the same id.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_HandleIfTransmit(
  DoIP_SizeOfPduRTxPduIdType PduRTxPduId,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr);
#endif /* DOIP_IF_API_ENABLED == STD_ON */

#if ( DOIP_IF_API_ENABLED == STD_ON )
# if ( DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON )
/**********************************************************************************************************************
 *  DoIP_HandleIfCancelTransmit()
 *********************************************************************************************************************/
/*! \brief          Handles transmission cancellation request of a specific IF Pdu
 *  \details        -
 *  \param[in]      PduRTxPduId   Identification of the IF Pdu to be cancelled.
 *                                [range: PduRTxPduId < DoIP_GetSizeOfPduRTxPduId()]
 *  \return         E_OK          Cancellation was executed successfully by the destination module.
 *  \return         E_NOT_OK      Cancellation was rejected by the destination module.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_HandleIfCancelTransmit(
  DoIP_SizeOfPduRTxPduIdType PduRTxPduId);
# endif /* DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON */
#endif /* DOIP_IF_API_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_HandleSoAdTpCopyTxData()
 *********************************************************************************************************************/
/*! \brief          Handles transmit data of a Pdu
 *  \details        This function is called to acquire the transmit data of an I-PDU segment (N-PDU). Each call to this
 *                  function provides the next part of the TP Pdu data. The size of the remaining data is written to
 *                  the position indicated by availableDataPtr.
 *  \param[in]      ConnectionTcpIdx  Identification of the transmitted TP Pdu.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      PduInfoPtr        Provides the destination buffer (SduDataPtr) and the number of bytes to be copied
 *                                    (SduLength). An SduLength of 0 can be used to query the current amount of
 *                                    available data in the upper layer module. In this case, the SduDataPtr may be a
 *                                    NULL_PTR.
 *                                    [range: POINTER != NULL_PTR, if POINTER->SduLength == 0 then POINTER->SduDataPtr
 *                                    may be NULL_PTR]
 *  \param[out]     AvailableDataPtr  Indicates the remaining number of bytes that are available in the upper layer
 *                                    module's Tx buffer.
 *                                    [range: POINTER != NULL_PTR]
 *  \return         BUFREQ_OK         Data has been copied to the transmit buffer completely as requested.
 *  \return         BUFREQ_E_NOT_OK   Data has not been copied. Request failed.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_HandleSoAdTpCopyTxData(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr);

/**********************************************************************************************************************
 *  DoIP_HandleSoAdTpTxConfirmation()
 *********************************************************************************************************************/
/*! \brief          Handles transmission of confirmation callback for TP
 *  \details        This function is called after the TP Pdu has been transmitted on its network, the result indicates
 *                  whether the transmission was successful or not.
 *  \param[in]      ConnectionTcpIdx  Identification of the transmitted TP Pdu.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \param[in]      Result            Result of the transmission of the TP Pdu.
 *                                    [range: E_OK, E_NOT_OK]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different ConnectionTcpIdxs. Non reentrant for the same ConnectionTcpIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_HandleSoAdTpTxConfirmation(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,
  Std_ReturnType Result);

/**********************************************************************************************************************
 *  DoIP_SoAdTpStartOfReception()
 *********************************************************************************************************************/
/*! \brief          Handles receive indication callback for TP
 *  \details        This function is called at the start of receiving an N-SDU. The N-SDU might be fragmented into
 *                  multiple N-PDUs or might consist of a single N-PDU.
 *  \param[in]      ConnectionTcpIdx  Identification of the TP Pdu.
 *                                    [range: ConnectionTcpIdx < DoIP_GetSizeOfConnectionTcp()]
 *  \return         BUFREQ_OK         Connection has been accepted. bufferSizePtr indicates the available receive
 *                                    buffer; reception is continued. If no buffer of the requested size is
 *                                    available, a receive buffer size of 0 shall be indicated by bufferSizePtr.
 *  \return         BUFREQ_E_NOT_OK   Connection has been rejected; reception is aborted. bufferSizePtr remains
 *                                    unchanged.
 *  \return         BUFREQ_E_OVFL     No buffer of the required length can be provided; reception is aborted.
 *                                    bufferSizePtr remains unchanged.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_HandleSoAdTpStartOfReception(
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx);

/**********************************************************************************************************************
 *  DoIP_HandleSoAdIfRxIndication()
 *********************************************************************************************************************/
/*! \brief          Handles receive indication callback for IF
 *  \details        Indication of a received IF Pdu from a lower layer communication interface module.
 *  \param[in]      ConnectionIdx   Id of the received IF Pdu.
 *                                  [range: DoIP_GetSizeOfConnectionTcp() <= ConnectionIdx < DOIP_CONNECTION_TCP_UDP_TOTAL]
 *  \param[in]      PduInfoPtr      Contains the length (SduLength) of the received IF Pdu and a pointer to a buffer
 *                                  (SduDataPtr) containing the IF Pdu.
 *                                  [range: POINTER != NULL_PTR && POINTER->SduDataPtr != NULL_PTR]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE - Reentrant for different RxPduIds. Non reentrant for the same RxPduId.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_HandleSoAdIfRxIndication(
  DoIP_SizeOfConnectionType ConnectionIdx,
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr);

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_HandleDhcpEvent()
 *********************************************************************************************************************/
/*! \brief          Handles DHCP event.
 *  \details        -
 *  \param[in]      LocalIpAddrId   IP address identifier.
 *                                  [range: undefined]
 *  \param[in]      Event           Indicates the received message type or the message type which will be send. 
 *                                  [range: SOAD_DHCP_EVENT_*]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \config         DOIP_DHCP_OPT_VENDOR_CLASS
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_HandleDhcpEvent(
  SoAd_LocalAddrIdType LocalIpAddrId,
  SoAd_DhcpEventType Event);
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Measure_InitDroppedPacketCounter()
 *********************************************************************************************************************/
/*! \brief          Initializes the count of dropped TCP/UDP packets to zero.
 *  \details        - 
 *  \pre            - 
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_GET_RESET_MEASUREMENT_DATA
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Measure_InitDroppedPacketCounter(void);
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Measure_IncDroppedPacketCounterTcp()
 *********************************************************************************************************************/
/*! \brief          Increments the count of dropped TCP packets.
 *  \details        - 
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_GET_RESET_MEASUREMENT_DATA
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Measure_IncDroppedPacketCounterTcp(void);
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Measure_IncDroppedPacketCounterUdp()
 *********************************************************************************************************************/
/*! \brief          Increments the count of dropped UDP packets.
 *  \details        - 
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_GET_RESET_MEASUREMENT_DATA
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Measure_IncDroppedPacketCounterUdp(void);
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Measure_IncDroppedPacketCounterType()
 *********************************************************************************************************************/
/*! \brief          Increments the count of dropped packets of the specified type.
 *  \details        -
 *  \param[in]      CounterType     The counter type to be incremented.
 *                                  [range: DOIP_MEASURE_DROPPED_PACKET_COUNTER_*]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_GET_RESET_MEASUREMENT_DATA
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Measure_IncDroppedPacketCounterType(
  DoIP_Measure_DroppedPacketCounterType CounterType);
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Measure_IncDroppedPacketCounter()
 *********************************************************************************************************************/
/*! \brief          Increments the count of dropped TCP/UDP packets.
 *  \details        -
 *  \param[in]      CounterType     The counter to be incremented.
 *                                  [range: DOIP_MEASURE_DROPPED_PACKET_COUNTER_*]
 *  \param[in]      HdrType         The NACK Header type.
 *                                  [range: undefined]
 *  \param[in]      NackType        The NACK type.
 *                                  [range: undefined]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         DOIP_GET_RESET_MEASUREMENT_DATA
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Measure_IncDroppedPacketCounter(
  DoIP_Measure_DroppedPacketCounterType CounterType,
  uint16 HdrType,
  uint8 NackType);
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Measure_GetAndResetDroppedPacketCounter()
 *********************************************************************************************************************/
/*! \brief          Gets and Resets(if requested) the dropped TCP/UDP packets counter.
 *  \details        Retrieve the dropped TCP/UDP packets counter value and if requested, reset the value.
 *  \param[in]      MeasurementIdx          The index to select specific measurement data.
 *                                          [range: undefined]
 *  \param[in]      MeasurementResetNeeded  Flag to indicate if the counter needs to be reset.
 *                                          [range: undefined]
 *  \param[in]      MeasurementDataPtr      Buffer where the value of the counter is to be copied into.
 *                                          [range: POINTER may be NULL_PTR]
 *  \pre            -
 *  \return         E_OK                    The operation was successful.
 *  \return         E_NOT_OK                The operation failed.                                    
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         DOIP_GET_RESET_MEASUREMENT_DATA
 *********************************************************************************************************************/
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Measure_GetAndResetDroppedPacketCounter(
  DoIP_MeasurementIdxType MeasurementIdx,
  boolean MeasurementResetNeeded,
  P2VAR(DoIP_MeasurementDataType, AUTOMATIC, DOIP_APPL_VAR) MeasurementDataPtr);
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  DoIP_Util_InitCons()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_InitCons(void)                                                              /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_ConnectionIterType connectionIdx;
  DoIP_TxUdpMgtListIterType txUdpMgtListIdx;
  DoIP_ConnectionTcpIterType connectionTcpIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize all connection data. */
  for ( connectionIdx = 0u;
        connectionIdx < DoIP_GetSizeOfConnection();
        connectionIdx++ )
  {
    DoIP_SetIpAddrStateOfConnectionDyn(connectionIdx, SOAD_IPADDR_STATE_UNASSIGNED);                                   /* SBSW_DOIP_CSL02 */
    DoIP_SetSoConIdOfConnectionDyn(connectionIdx, SOAD_INV_SO_CON_ID);                                                 /* SBSW_DOIP_CSL02 */
    DoIP_SetSoConStateOfConnectionDyn(connectionIdx, SOAD_SOCON_OFFLINE);                                              /* SBSW_DOIP_CSL02 */
    DoIP_SetSoConClosingOfConnectionDyn(connectionIdx, FALSE);                                                         /* SBSW_DOIP_CSL02 */
  }

  /* #20 Initialize all UDP management lists. */
  for ( txUdpMgtListIdx = 0u;
        txUdpMgtListIdx < DoIP_GetSizeOfTxUdpMgtList();
        txUdpMgtListIdx++ )
  {
    DoIP_SetConnectionIdxOfTxUdpMgtList(txUdpMgtListIdx, DoIP_GetSizeOfConnection());                                  /* SBSW_DOIP_CSL01 */
  }

  /* #30 Initialize all TCP connection data. */
  for ( connectionTcpIdx = 0u;
        connectionTcpIdx < DoIP_GetSizeOfConnectionTcp();
        connectionTcpIdx++ )
  {
    DoIP_TxTcpMgtIterType txTcpMgtIdx;

    DoIP_SetInactivCntOfConnectionTcpDyn(connectionTcpIdx, 0u);                                                        /* SBSW_DOIP_CSL02 */
    DoIP_SetSkipRxMsgOfConnectionTcpDyn(connectionTcpIdx, FALSE);                                                      /* SBSW_DOIP_CSL02 */
    DoIP_SetRxMsgOffsetOfConnectionTcpDyn(connectionTcpIdx, 0u);                                                       /* SBSW_DOIP_CSL02 */
    DoIP_SetTxBytesCopiedOfConnectionTcpDyn(connectionTcpIdx, 0u);                                                     /* SBSW_DOIP_CSL02 */
    DoIP_SetLastRxBufSizeOfConnectionTcpDyn(connectionTcpIdx, 0u);                                                     /* SBSW_DOIP_CSL02 */
    DoIP_SetLastTxBufSizeOfConnectionTcpDyn(connectionTcpIdx, 0u);                                                     /* SBSW_DOIP_CSL02 */
    DoIP_SetChannelRxLastIdxOfConnectionTcpDyn(connectionTcpIdx, DoIP_GetSizeOfChannel());                             /* SBSW_DOIP_CSL02 */
    DoIP_SetChannelRxActiveOfConnectionTcpDyn(connectionTcpIdx, FALSE);                                                /* SBSW_DOIP_CSL02 */
    DoIP_SetTxTcpMgtQueLvlOfConnectionTcpDyn(connectionTcpIdx, 0u);                                                    /* SBSW_DOIP_CSL02 */
    DoIP_SetTxTcpMgtQueIdxOfConnectionTcpDyn(connectionTcpIdx, 0u);                                                    /* SBSW_DOIP_CSL02 */
    DoIP_SetTxTpSessionActiveOfConnectionTcpDyn(connectionTcpIdx, FALSE);                                              /* SBSW_DOIP_CSL02 */
    DoIP_SetRxTpSessionActiveOfConnectionTcpDyn(connectionTcpIdx, FALSE);                                              /* SBSW_DOIP_CSL02 */
    DoIP_SetTpTxPreHdrTypeOfConnectionTcpDyn(connectionTcpIdx, DOIP_HDR_TYPE_INVALID);                                 /* SBSW_DOIP_CSL02 */
#if ( DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON )
    DoIP_SetTxTpCancelRequestedOfConnectionTcpDyn(connectionTcpIdx, FALSE);                                            /* SBSW_DOIP_CSL02 */
#endif /* DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON */
#if ( DOIP_PROVIDE_CANCEL_RECEIVE_API == STD_ON )
    DoIP_SetRxTpCancelRequestedOfConnectionTcpDyn(connectionTcpIdx, FALSE);                                            /* SBSW_DOIP_CSL02 */
#endif /* DOIP_PROVIDE_CANCEL_RECEIVE_API == STD_ON */
    DoIP_RxTcpRout_RegisterTester((DoIP_SizeOfConnectionTcpType)connectionTcpIdx, DoIP_GetSizeOfTester(),
      DOIP_ADDR_ANY, DoIP_GetSizeOfRoutingActivation(), DOIP_ROUT_ACTIV_STATE_NONE);

    /* #40 Initialize all TCP management queues. */
    for ( txTcpMgtIdx = DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(connectionTcpIdx);
          txTcpMgtIdx < DoIP_GetTxTcpMgtEndIdxOfConnectionTcp(connectionTcpIdx);
          txTcpMgtIdx++ )
    {
      DoIP_SetChannelIdxOfTxTcpMgtDyn(txTcpMgtIdx, DoIP_GetSizeOfChannel());                                           /* SBSW_DOIP_CSL02_CSL03 */
      DoIP_SetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx, 0u);                                                               /* SBSW_DOIP_CSL02_CSL03 */
    }

#if ( DOIP_VERIFY_RX_PDU_ENABLED == STD_ON )
    {
      SoAd_SockAddrInetXType ipAddr = { SOAD_AF_INVALID, 0u, { 0u } };

      DoIP_SetRemIpAddrOfConnectionTcpDyn(connectionTcpIdx, ipAddr);                                                   /* SBSW_DOIP_CSL02 */
      DoIP_SetLocIpAddrOfConnectionTcpDyn(connectionTcpIdx, ipAddr);                                                   /* SBSW_DOIP_CSL02 */
    }
#endif /* DOIP_VERIFY_RX_PDU_ENABLED == STD_ON */
  }
} /* DoIP_Util_InitCons() */

/**********************************************************************************************************************
 *  DoIP_Util_InitChannels()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_InitChannels(void)                                                          /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_ChannelIterType channelIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize all channel data. */
  for ( channelIdx = 0u;
        channelIdx < DoIP_GetSizeOfChannel();
        channelIdx++ )
  {
    DoIP_SetTxMsgLenOfChannelDyn(channelIdx, 0u);                                                                      /* SBSW_DOIP_CSL02 */
  }
} /* DoIP_Util_InitChannels() */

/**********************************************************************************************************************
 *  DoIP_Util_InitTesters()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_InitTesters(void)                                                           /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_TesterIterType testerIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize all tester data. */
  for ( testerIdx = 0u;
        testerIdx < DoIP_GetSizeOfTester();
        testerIdx++ )
  {
    DoIP_SetConnectionTcpIdxOfTesterDyn(testerIdx, DoIP_GetSizeOfConnectionTcp());                                     /* SBSW_DOIP_CSL02 */
#if ( DOIP_NACK_APPEND_REQ == STD_ON )
    DoIP_SetDiagNAckOffsetOfTesterDyn(testerIdx, 0u);                                                                  /* SBSW_DOIP_CSL02 */
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */
  }
} /* DoIP_Util_InitTesters() */

/**********************************************************************************************************************
 *  DoIP_Util_InitLocalAddrs()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_InitLocalAddrs(void)                                                        /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_IpAddrAssignmentIterType ipAddrAssignmentIdx;
#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
  const SoAd_SockAddrInetXType ipAddr = { SOAD_AF_INVALID, 0u, { 0u } };
  DoIP_ConnectionIterType      connectionIdx;
  DoIP_IpAddrListIterType      ipAddrListIdx;
  DoIP_SizeOfLocalAddrType     localAddrIdx;
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize all IP address assignment states. */
  for ( ipAddrAssignmentIdx = 0u;
        ipAddrAssignmentIdx < DoIP_GetSizeOfIpAddrAssignment();
        ipAddrAssignmentIdx++ )
  {
    DoIP_SetIpAddrReqStateOfIpAddrAssignmentDyn(ipAddrAssignmentIdx, DOIP_IP_ADDR_REQ_STATE_NONE);                     /* SBSW_DOIP_CSL02 */
  }

#if ( DOIP_GID_SYNC_ENABLED == STD_ON )
  /* #20 Reset number of connections with assigned local addresses. */
  DoIP_LocalAddrAssignedCounter = 0u;
#endif /* DOIP_GID_SYNC_ENABLED == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
  /* #30 Iterate over all DoIP Vehicle Announcement connections (if enabled). */
  for ( connectionIdx = DOIP_CONNECTION_TCP_UDP_TOTAL;
        connectionIdx < DoIP_GetSizeOfConnection();
        connectionIdx++ )
  {
    /* #40 Reset DHCP vendor option IP address list for connection related local address. */
    localAddrIdx = DoIP_GetLocalAddrIdxOfConnection(connectionIdx);
    for ( ipAddrListIdx = DoIP_GetIpAddrListStartIdxOfLocalAddr(localAddrIdx);
          ipAddrListIdx < DoIP_GetIpAddrListEndIdxOfLocalAddr(localAddrIdx);
          ipAddrListIdx++ )
    {
      DoIP_SetTriggerVehAnnOfIpAddrList(ipAddrListIdx, FALSE);                                                         /* SBSW_DOIP_CSL03_CSL01 */
      DoIP_SetIpAddrOfIpAddrList(ipAddrListIdx, ipAddr);                                                               /* SBSW_DOIP_CSL03_CSL01 */
    }
  }
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */
} /* DoIP_Util_InitLocalAddrs() */

/**********************************************************************************************************************
 *  DoIP_Util_InitRoutActivHandlers()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_InitRoutActivHandlers(void)                                                 /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_AliveCheckListIterType aliveCheckListIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize all routing activation handler lists. */
  for ( aliveCheckListIdx = 0u;
        aliveCheckListIdx < DoIP_GetSizeOfAliveCheckList();
        aliveCheckListIdx++ )
  {
    DoIP_SetConnectionTcpIdxOfAliveCheckList(aliveCheckListIdx, DoIP_GetSizeOfConnectionTcp());                        /* SBSW_DOIP_CSL01 */
  }

  /* #20 Initialize routing activation handler data. */
  DoIP_SetOemSpecReqOfRoutActivHandler(0u, 0u);                                                                        /* SBSW_DOIP_RoutActivHandler */
  DoIP_SetOemSpecResOfRoutActivHandler(0u, 0u);                                                                        /* SBSW_DOIP_RoutActivHandler */
  DoIP_SetOemSpecUsedOfRoutActivHandler(0u, FALSE);                                                                    /* SBSW_DOIP_RoutActivHandler */
  DoIP_SetRoutingActivationIdxOfRoutActivHandler(0u, DoIP_GetSizeOfRoutingActivation());                               /* SBSW_DOIP_RoutActivHandler */
  DoIP_SetTesterAddrOfRoutActivHandler(0u, DOIP_ADDR_ANY);                                                             /* SBSW_DOIP_RoutActivHandler */
  DoIP_SetTesterIdxOfRoutActivHandler(0u, DoIP_GetSizeOfTester());                                                     /* SBSW_DOIP_RoutActivHandler */
  DoIP_SetAliveCheckCntOfRoutActivHandler(0u, 0u);                                                                     /* SBSW_DOIP_RoutActivHandler */
  DoIP_SetAliveCheckElemNumOfRoutActivHandler(0u, 0u);                                                                 /* SBSW_DOIP_RoutActivHandler */
  DoIP_SetConnectionTcpIdxOfRoutActivHandler(0u, DoIP_GetSizeOfConnectionTcp());                                       /* SBSW_DOIP_RoutActivHandler */
} /* DoIP_Util_InitRoutActivHandlers() */

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Util_InitOemPayloadTypes()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_InitOemPayloadTypes(void)                                                   /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize OEM specific data (if enabled). */
# if ( DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u )
  DoIP_SetOemPayloadTypeTcpBufLen(0u);                                                                                 /* SBSW_DOIP_OemPayloadType */
  DoIP_SetOemPayloadTypeTcpBufIsTx(FALSE);                                                                             /* SBSW_DOIP_OemPayloadType */
  DoIP_SetOemPayloadTypeTcpBuf2Con(DoIP_GetSizeOfConnection());                                                        /* SBSW_DOIP_OemPayloadType */
# endif /* DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u */
  DoIP_SetOemPayloadTypeUdpBufLen(0u);                                                                                 /* SBSW_DOIP_OemPayloadType */
} /* DoIP_Util_InitOemPayloadTypes() */
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Util_ValidateConfig()
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
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Util_ValidateConfig(                                                   /* INTERNAL_NOTE_SBSW_OK */
  P2CONST(DoIP_ConfigType, AUTOMATIC, DOIP_CONST) DoIPConfigPtr)                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  P2CONST(DoIP_ConfigType, AUTOMATIC, DOIP_CONST) tmpConfigPtr;
  DoIP_RoutingActivationIterType routingActivationIndex;
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize configuration pointer temporary to enable the following checks. */
  tmpConfigPtr = DoIP_ConfigDataPtr;
  DoIP_ConfigDataPtr = DoIPConfigPtr;

  /* #20 Iterate over all configured routing activations to check the configuration of the OEM specific part. */
  for ( routingActivationIndex = 0u;
        routingActivationIndex < DoIP_GetSizeOfRoutingActivation();
        routingActivationIndex++ )
  {
    /* #30 Mark config as invalid if the confirmation length for the request exceeds the maximum size. */
    if ( DoIP_GetConfReqLengthOfRoutingActivation(routingActivationIndex) > DOIP_ROUT_ACTIV_REQ_OEM_LEN_BYTE )
    {
      retVal = E_NOT_OK;
    }
    /* #40 Mark config as invalid if the confirmation length for the response exceeds the maximum size otherwise. */
    else if ( DoIP_GetConfResLengthOfRoutingActivation(routingActivationIndex) > DOIP_ROUT_ACTIV_ACK_OEM_LEN_BYTE )
    {
      retVal = E_NOT_OK;
    }
    /* #50 Assume that OEM specific part is configured correctly otherwise. */
    else
    {
      /* Nothing to do. */
    }

    /* #60 Stop iteration if at least one OEM specific part is configured invalidly. */
    if ( retVal == E_NOT_OK )
    {
      break;
    }
  }

  /* #70 Revert configuration pointer. */
  DoIP_ConfigDataPtr = tmpConfigPtr;

  return retVal;
} /* DoIP_Util_ValidateConfig() */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */

/**********************************************************************************************************************
 *  DoIP_Util_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_Init(void)                                                                  /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the module data structures. */
  /* PRQA S 2987 5 */ /* MD_DoIP_Rule2.2_2987 */
  DoIP_Util_InitCons();
  DoIP_Util_InitChannels();
  DoIP_Util_InitTesters();
  DoIP_Util_InitLocalAddrs();
  DoIP_Util_InitRoutActivHandlers();
#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
  DoIP_Util_InitOemPayloadTypes();
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */
} /* DoIP_Util_Init() */

/**********************************************************************************************************************
 *  DoIP_Util_FillGenHdr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_FillGenHdr(                                                                 /* INTERNAL_NOTE_SBSW_OK */
  uint16 HdrType,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint32 HdrLen,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr)                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write data to target buffer. */
  /* header version */
  TgtBufferPtr[0u] = DOIP_PROTOCOL_VERSION_2012;                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  /* inverse header version */
  TgtBufferPtr[1u] = (uint8)(~TgtBufferPtr[0u]);                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  /* header type */
  DoIP_Util_PutUInt16(&TgtBufferPtr[2u], 0u, HdrType);                                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  /* header length */
  DoIP_Util_PutUInt32(&TgtBufferPtr[4u], 0u, HdrLen);                                                                  /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
} /* DoIP_Util_FillGenHdr() */

/**********************************************************************************************************************
 *  DoIP_Util_FillVin()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Util_FillVin(                                                          /* INTERNAL_NOTE_SBSW_OK */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr)                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 vinBuffer[DOIP_VIN_LEN_BYTE] = { 0u };

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy VIN to target buffer if VIN retieved sucessfully. */
  if ( DoIP_CallGetVinDirect(vinBuffer) == E_OK )                                                                      /* SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_FORWARD */
  {
    /* PRQA S 0310, 0314 1 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
    VStdLib_MemCpy(DOIP_A_P2VAR(void)&TgtBufferPtr[0u], DOIP_A_P2CONST(void)vinBuffer, DOIP_VIN_LEN_BYTE);             /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */

    retVal = E_OK;
  }
  else
  {
    uint8_least tgtBufferIdx;

    /* #20 Otherwise write invalid pattern to target buffer. */
    for ( tgtBufferIdx = 0u;
          tgtBufferIdx < DOIP_VIN_LEN_BYTE;
          tgtBufferIdx++ )
    {
      TgtBufferPtr[tgtBufferIdx] = DOIP_VIN_INV_PATTERN;                                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    }

    retVal = E_NOT_OK;
  }

  return retVal;
} /* DoIP_Util_FillVin() */

/**********************************************************************************************************************
 *  DoIP_Util_FillLocalLogAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_FillLocalLogAddr(                                                           /* INTERNAL_NOTE_SBSW_OK */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr)                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write logical address to target buffer. */
  DoIP_Util_PutUInt16(TgtBufferPtr, 0u, DOIP_ADDR);                                                                    /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
} /* DoIP_Util_FillLocalLogAddr() */

/**********************************************************************************************************************
 *  DoIP_Util_FillEid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 3206 3 */ /* MD_DoIP_3206 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Util_FillEid(                                                          /* INTERNAL_NOTE_SBSW_OK */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr,                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  DoIP_SizeOfConnectionType ConnectionIdx)                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
#if ( DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON )
  uint8 physAddrBuf[DOIP_PHYS_ADDR_LEN];
#endif /* DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON )
  /* #10 Copy mac address to target buffer if successfully received (if enabled). */
  if ( SoAd_GetPhysAddr(DoIP_GetSoConIdOfConnectionDyn(ConnectionIdx), &physAddrBuf[0u]) == E_OK )                     /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  {
    /* PRQA S 0310, 0314 1 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
    VStdLib_MemCpy(DOIP_A_P2VAR(void)&TgtBufferPtr[0u], DOIP_A_P2CONST(void)&physAddrBuf[0u], DOIP_PHYS_ADDR_LEN);     /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
  }
  else
  {
    retVal = E_NOT_OK;
  }
#else
  /* #20 Copy configured EID to target buffer (if enabled). */
  /* PRQA S 0310, 0314 1 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
  VStdLib_MemCpy(DOIP_A_P2VAR(void)&TgtBufferPtr[0u], DOIP_A_P2CONST(void)DoIP_GetAddrEId(0u), DOIP_PHYS_ADDR_LEN);    /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */

  DOIP_DUMMY_STATEMENT(ConnectionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON */

  return retVal;
} /* DoIP_Util_FillEid() */

/**********************************************************************************************************************
 *  DoIP_Util_FillGid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 3206 3 */ /* MD_DoIP_3206 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Util_FillGid(                                                          /* INTERNAL_NOTE_SBSW_OK */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr,                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  DoIP_SizeOfConnectionType ConnectionIdx)                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
#if ( (DOIP_VIN_GID_MASTER == STD_ON ) && (DOIP_USE_EID_AS_GID == STD_ON) )
  /* #10 Write EID to target buffer (if EID as GID enabled). */
  retVal = DoIP_Util_FillEid(TgtBufferPtr, ConnectionIdx);                                                             /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
#else
  /* #20 Write GID or invalid pattern to target buffer (if enabled). */
  DoIP_Util_FillGidOrInv(TgtBufferPtr);                                                                                /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */

  DOIP_DUMMY_STATEMENT(ConnectionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

  retVal = E_OK;
#endif /* (DOIP_VIN_GID_MASTER == STD_ON ) && (DOIP_USE_EID_AS_GID == STD_ON) */

  return retVal;
} /* DoIP_Util_FillGid() */

#if ( !((DOIP_VIN_GID_MASTER == STD_ON ) && (DOIP_USE_EID_AS_GID == STD_ON)) )
/**********************************************************************************************************************
 *  DoIP_Util_FillGidOrInv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_FillGidOrInv(                                                               /* INTERNAL_NOTE_SBSW_OK */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr)                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Implementation ----------------------------------------------- */
# if ( DOIP_GID_AVAILABLE == STD_ON )
  /* #10 Write configured GID to target buffer (if enabled). */
  /* PRQA S 0310, 0314 1 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
  VStdLib_MemCpy(DOIP_A_P2VAR(void)&TgtBufferPtr[0u], DOIP_A_P2CONST(void)DoIP_GetAddrGId(0u), DOIP_GID_LEN_BYTE);     /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
# else
  uint8 gidBuffer[DOIP_GID_LEN_BYTE] = { 0u };

  if ( DoIP_CallGetGidDirect(gidBuffer) == E_OK )                                                                      /* SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_FORWARD */
  {
    /* #20 Copy GID to target buffer if GID retieved sucessfully. */
    /* PRQA S 0310, 0314 1 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
    VStdLib_MemCpy(DOIP_A_P2VAR(void)&TgtBufferPtr[0u], DOIP_A_P2CONST(void)gidBuffer, DOIP_GID_LEN_BYTE);             /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
  }
  else
  {
    uint8_least tgtBufferIdx;

    /* #30 Otherwise write invalid pattern to target buffer. */
    for ( tgtBufferIdx = 0u;
          tgtBufferIdx < DOIP_GID_LEN_BYTE;
          tgtBufferIdx++ )
    {
      TgtBufferPtr[tgtBufferIdx] = DOIP_GID_INV_PATTERN;                                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    }
  }
# endif /* DOIP_GID_ENABLED == STD_ON */
} /* DoIP_Util_FillGidOrInv() */
#endif /* !((DOIP_VIN_GID_MASTER == STD_ON ) && (DOIP_USE_EID_AS_GID == STD_ON)) */

/**********************************************************************************************************************
 *  DoIP_Util_FillFurtherAction()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Util_FillFurtherAction(                                                          /* INTERNAL_NOTE_SBSW_OK */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) TgtBufferPtr)                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set further action byte to 0x00u. */
  TgtBufferPtr[0u] = 0x00u;                                                                                            /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
#if ( DOIP_TESTER_WITH_CEN_SEC_AVAILABLE == STD_ON )
  {
    DoIP_TesterIterType testerIdx;

    for ( testerIdx = 0u;
          testerIdx < DoIP_GetSizeOfTester();
          testerIdx++ )
    {
      /* #20 Iterate over all testers with central security (if enabled). */
      if ( DoIP_IsCentralSecurityOfTester(testerIdx) )
      {
        boolean furtherActionRequired = FALSE;
        const DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_GetConnectionTcpIdxOfTesterDyn(testerIdx);

        /* #30 Check if tester is unconnected. */
        if ( connectionTcpIdx == DoIP_GetSizeOfConnectionTcp() )
        {
          /* #40 Set further action byte to 0x10u. */
          furtherActionRequired = TRUE;
        }
        /* #50 Otherwise check if tester is not connected to routing activation number 0xE0u. */
        else
        {
          if ( DoIP_GetRoutingActivationNumOfRoutingActivation(
                 DoIP_GetRoutingActivationIdxOfConnectionTcpDyn(connectionTcpIdx)) != 0xE0u )
          {
            /* #60 Set further action byte to 0x10u. */
            furtherActionRequired = TRUE;
          }
        }

        if ( furtherActionRequired == TRUE )
        {
          TgtBufferPtr[0u] = 0x10u;                                                                                    /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
          break;
        }
      }
    }
  }
#endif /* DOIP_TESTER_WITH_CEN_SEC_AVAILABLE == STD_ON */
} /* DoIP_Util_FillFurtherAction() */

/**********************************************************************************************************************
 *  DoIP_Util_PutUInt16()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_Util_PutUInt16(                                                           /* INTERNAL_NOTE_SBSW_OK */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) Buffer,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  uint32 Offset,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint16 Value)                                                                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Put value into buffer. */
  (Buffer)[(Offset)     ] = (uint8)((uint16_least)(Value) >> 8u);                                                      /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  (Buffer)[(Offset) + 1u] = (uint8)((uint16_least)(Value));                                                            /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
} /* DoIP_Util_PutUInt16() */

/**********************************************************************************************************************
 *  DoIP_Util_PutUInt32()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_Util_PutUInt32(                                                           /* INTERNAL_NOTE_SBSW_OK */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) Buffer,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  uint32 Offset,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint32 Value)                                                                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Put value into buffer. */
  (Buffer)[(Offset)     ] = (uint8)((uint32_least)(Value) >> 24u);                                                     /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  (Buffer)[(Offset) + 1u] = (uint8)((uint32_least)(Value) >> 16u);                                                     /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  (Buffer)[(Offset) + 2u] = (uint8)((uint32_least)(Value) >> 8u);                                                      /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  (Buffer)[(Offset) + 3u] = (uint8)((uint32_least)(Value));                                                            /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
} /* DoIP_Util_PutUInt32() */

/**********************************************************************************************************************
 *  DoIP_Util_CheckBufferSizeAndModify()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL_INLINE FUNC(void, DOIP_CODE) DoIP_Util_CheckBufferSizeAndModify(                                            /* INTERNAL_NOTE_SBSW_OK */
  uint32 BufferSize,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr)                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if BufferSize exeedes PduLengthType size. */
#if ( DOIP_MAX_PDU_LENGTH != 0xFFFFFFFFUL )
  if ( BufferSize > DOIP_MAX_PDU_LENGTH )
  {
    /* #20 Use max PduLengthType size. */
    *BufferSizePtr = (PduLengthType)DOIP_MAX_PDU_LENGTH;                                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  }
  else
#endif /* DOIP_MAX_PDU_LENGTH != 0xFFFFFFFFUL */
  {
    /* #30 Use BufferSize size otherwise. */
    *BufferSizePtr = (PduLengthType)BufferSize;                                                                        /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  }
} /* DoIP_Util_CheckBufferSizeAndModify() */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
# if ( DOIP_IPV6_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Util_CheckIpV6Addr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL_INLINE FUNC(Std_ReturnType, DOIP_CODE) DoIP_Util_CheckIpV6Addr(                                             /* INTERNAL_NOTE_SBSW_OK */
  SoAd_SockAddrInetXType IpAddr)                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_SOCKADDR_STRUCT */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the IPv6 address is unspecified. */
  if ( DoIP_Util_CompareIpAddr(SOAD_AF_INET6, DOIP_A_P2CONST(uint32)(IpAddr.addr),                                     /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
        DOIP_A_P2CONST(uint32)(DoIP_IpV6AddrUnspecified.addr)) == FALSE )
  {
    /* #20 Check if the IPv6 address is the loopback address. */
    if ( DoIP_Util_CompareIpAddr(SOAD_AF_INET6, DOIP_A_P2CONST(uint32)(IpAddr.addr),                                   /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
          DOIP_A_P2CONST(uint32)(DoIP_IpV6AddrLoopback.addr)) == FALSE )
    {
      /* #30 Check if the IPv6 address is the multicast address. */
      if ( DoIP_Util_CompareIpAddr(SOAD_AF_INET6, DOIP_A_P2CONST(uint32)(IpAddr.addr),                                 /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
            DOIP_A_P2CONST(uint32)(DoIP_IpV6AddrMulticast.addr)) == FALSE )
      {
        retVal = E_OK;
      }
    }
  }
  return retVal;
} /* DoIP_Util_CheckIpV6Addr() */
# endif /* DOIP_IPV6_ENABLED == STD_ON */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
# if ( DOIP_IPV4_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Util_CheckIpV4Addr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL_INLINE FUNC(Std_ReturnType, DOIP_CODE) DoIP_Util_CheckIpV4Addr(                                             /* INTERNAL_NOTE_SBSW_OK */
  SoAd_SockAddrInetXType IpAddr)                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_SOCKADDR_STRUCT */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint32 ipAddrMasked = IpAddr.addr[0] & DOIP_8_BIT_NET_MASK;

  /* ----- Implementation ----------------------------------------------- */
  /*  #10 Check if the IPv4 address is unspecified. */
  if ( DoIP_Util_CompareIpAddr(SOAD_AF_INET, DOIP_A_P2CONST(uint32)(&ipAddrMasked),                                    /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
        DOIP_A_P2CONST(uint32)(DoIP_IpV4AddrUnspecifiedNetmask.addr)) == FALSE )
  {
    /* #20 Check if the IPv4 address is the loopback address. */
    if ( DoIP_Util_CompareIpAddr(SOAD_AF_INET, DOIP_A_P2CONST(uint32)(&ipAddrMasked),                                  /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
          DOIP_A_P2CONST(uint32)(DoIP_IpV4AddrLoopbackNetmask.addr)) == FALSE )
    {
      /* #30 Check if the IPv4 address is the broadcast address. */
      if ( DoIP_Util_CompareIpAddr(SOAD_AF_INET, DOIP_A_P2CONST(uint32)IpAddr.addr,                                    /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
            DOIP_A_P2CONST(uint32)(DoIP_IpV4AddrBroadcast.addr)) == FALSE )
      {
        retVal = E_OK;
      }
    }
  }
  return retVal;
} /* DoIP_Util_CheckIpV4Addr() */
# endif /* DOIP_IPV4_ENABLED == STD_ON */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Util_CompareIpAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 3206 4 */ /* MD_DoIP_3206 */
DOIP_LOCAL_INLINE FUNC(boolean, DOIP_CODE) DoIP_Util_CompareIpAddr(                                                    /* INTERNAL_NOTE_SBSW_OK */
  SoAd_DomainType Domain,                                                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  P2CONST(uint32, AUTOMATIC, DOIP_APPL_VAR) IpAddrAPtr,                                                                /* INTERNAL_NOTE_SBSW_DOIP_PARAM_SOCKADDR_STRUCT */
  P2CONST(uint32, AUTOMATIC, DOIP_APPL_VAR) IpAddrBPtr)                                                                /* INTERNAL_NOTE_SBSW_DOIP_PARAM_SOCKADDR_STRUCT */
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isMatching;

  /* ----- Implementation ----------------------------------------------- */
# if ( DOIP_IPV6_ENABLED == STD_ON )
#  if ( DOIP_IPV4_ENABLED == STD_ON )
  /* #10 Check if it is an IPv6 IP address (if enabled). */
  if ( Domain == SOAD_AF_INET6 )
#  endif /* DOIP_IPV4_ENABLED == STD_ON */
  {
    /* #20 Compare both IPv6 addresses. */
    if ( (IpAddrAPtr[0u] == IpAddrBPtr[0u]) &&
         (IpAddrAPtr[1u] == IpAddrBPtr[1u]) &&
         (IpAddrAPtr[2u] == IpAddrBPtr[2u]) &&
         (IpAddrAPtr[3u] == IpAddrBPtr[3u]) )
    {
      isMatching = TRUE;
    }
    else
    {
      isMatching = FALSE;
    }
  }
#  if ( DOIP_IPV4_ENABLED == STD_ON )
  else
#  else
  DOIP_DUMMY_STATEMENT(Domain); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* DOIP_IPV4_ENABLED == STD_ON */
# endif /* DOIP_IPV6_ENABLED == STD_ON */
# if ( DOIP_IPV4_ENABLED == STD_ON )
  {
    /* #30 Compare both IPv4 addresses. */
    if ( IpAddrAPtr[0u] == IpAddrBPtr[0u] )
    {
      isMatching = TRUE;
    }
    else
    {
      isMatching = FALSE;
    }
  }
#  if ( DOIP_IPV6_ENABLED == STD_OFF )
  DOIP_DUMMY_STATEMENT(Domain); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* DOIP_IPV6_ENABLED == STD_OFF */
# endif /* DOIP_IPV4_ENABLED == STD_ON */

  return isMatching;
} /* DoIP_Util_CompareIpAddr() */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_GetLocalAddrIdxOfDhcpAssignmentByLocalIpAddrId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Dhcp_GetLocalAddrIdxOfDhcpAssignmentByLocalIpAddrId(                   /* INTERNAL_NOTE_SBSW_OK */
  SoAd_LocalAddrIdType LocalIpAddrId,                                                                                  /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  P2VAR(DoIP_SizeOfLocalAddrType, AUTOMATIC, DOIP_APPL_VAR) LocalAddrIdxPtr)                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  DoIP_LocalAddrIterType localAddrIdx;
  DoIP_IpAddrAssignmentIterType ipAddrAssignmentIdx;

  /* ----- Implementation ----------------------------------------------- */
  *LocalAddrIdxPtr = DoIP_GetSizeOfLocalAddr();                                                                        /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */

  /* #10 Iterate over all local IP addresses. */
  for ( localAddrIdx = 0u;
        localAddrIdx < DoIP_GetSizeOfLocalAddr();
        localAddrIdx++ )
  {
    if ( DoIP_GetTcpIpLocalAddrIdOfLocalAddr(localAddrIdx) == LocalIpAddrId )
    {
      /* #20 Iterate over all related IP address assignments. */
      for ( ipAddrAssignmentIdx = DoIP_GetIpAddrAssignmentStartIdxOfLocalAddr(localAddrIdx);
            ipAddrAssignmentIdx < DoIP_GetIpAddrAssignmentEndIdxOfLocalAddr(localAddrIdx);
            ipAddrAssignmentIdx++ )
      {
        if ( DoIP_GetAssignmentTypeOfIpAddrAssignment(ipAddrAssignmentIdx) == DOIP_IPADDR_ASSIGN_TYPE_DHCP )
        {
          /* #30 Return found DoIP index if address has DHCP assignment. */
          *LocalAddrIdxPtr = (DoIP_SizeOfLocalAddrType)localAddrIdx;                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
          retVal = E_OK;
          break;
        }
      }
    }
    if ( retVal == E_OK )
    {
      break;
    }
  }

  return retVal;
} /* DoIP_Dhcp_GetLocalAddrIdxOfDhcpAssignmentByLocalIpAddrId() */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_PrepareVendorClassTxBuf()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 3206 4 */ /* MD_DoIP_3206 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_PrepareVendorClassTxBuf(                                                    /* INTERNAL_NOTE_SBSW_OK */
  uint16 OptionCode,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  P2VAR(uint16, AUTOMATIC, DOIP_APPL_VAR) OptionBufferLengthPtr,                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) OptionBufferPtr)                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 venEnterpriseNum = DOIP_DHCPVX_OPT_VENDOR_ENT_NUM_3210;

  /* ----- Implementation ----------------------------------------------- */
# if ( DOIP_IPV6_ENABLED == STD_ON )
#  if ( DOIP_IPV4_ENABLED == STD_ON )
  if ( OptionCode == DOIP_DHCPV6_OPT_VENDOR_CLASS_OPT_CODE )
#  endif /* DOIP_IPV4_ENABLED = STD_ON */
  {
    /* #10 Fill the option buffer with the data in case of DHCPv6 Option code (if enabled). */
    *OptionBufferLengthPtr = DOIP_DHCPV6_OPT_VENDOR_CLASS_MIN_LEN;                                                     /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    OptionBufferPtr[0u] = (uint8)(0u);                                                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    OptionBufferPtr[1u] = (uint8)(0u);                                                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    OptionBufferPtr[2u] = (uint8)(venEnterpriseNum >> 8u);                                                             /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    OptionBufferPtr[3u] = (uint8)(venEnterpriseNum);                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  }
#  if ( DOIP_IPV4_ENABLED == STD_ON )
  else
#  else
  DOIP_DUMMY_STATEMENT(OptionCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* DOIP_IPV4_ENABLED = STD_ON */
# endif /* DOIP_IPV6_ENABLED = STD_ON */
# if ( DOIP_IPV4_ENABLED == STD_ON )
  {
    /* #20 Fill the option buffer with the data in case of DHCPv4 Option code (if enabled). */
    *OptionBufferLengthPtr = DOIP_DHCPV4_OPT_VENDOR_CLASS_MIN_LEN;                                                     /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    OptionBufferPtr[0u] = (uint8)(0u);                                                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    OptionBufferPtr[1u] = (uint8)(0u);                                                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    OptionBufferPtr[2u] = (uint8)(venEnterpriseNum >> 8u);                                                             /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    OptionBufferPtr[3u] = (uint8)(venEnterpriseNum);                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    OptionBufferPtr[4u] = (uint8)(0u); /* Data Length = 0 */                                                           /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  }
#  if ( DOIP_IPV6_ENABLED == STD_OFF )
  DOIP_DUMMY_STATEMENT(OptionCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* DOIP_IPV6_ENABLED = STD_OFF */
# endif /* DOIP_IPV4_ENABLED = STD_ON */
} /* DoIP_Dhcp_PrepareVendorClassTxBuf() */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_HandleVendorOptsOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_HandleVendorOptsOption(                                                     /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfLocalAddrType LocalAddrIdx,                                                                               /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 OptionCode,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  uint16 OptionBufferLength,                                                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  P2CONST(uint8, AUTOMATIC, DOIP_APPL_VAR) OptionBufferPtr)                                                            /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Validate the received vendor option buffer data. */
  if ( DoIP_Dhcp_ValidateVendorOptsRxBuf(OptionCode, OptionBufferLength, OptionBufferPtr) == E_OK )                    /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  {
    /* #20 Process the IP address list received from DHCP. */
    DoIP_Dhcp_HandleIpAddrListFromVendorOpts(LocalAddrIdx, OptionCode, OptionBufferLength, OptionBufferPtr);           /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }
} /* DoIP_Util_HandleDhcpVendorOptsOption() */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_ValidateVendorOptsRxBuf()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3206 4 */ /* MD_DoIP_3206 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Dhcp_ValidateVendorOptsRxBuf(                                          /* INTERNAL_NOTE_SBSW_OK */
  uint16 OptionCode,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  uint16 OptionBufferLength,                                                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  P2CONST(uint8, AUTOMATIC, DOIP_APPL_VAR) OptionBufferPtr)                                                            /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint32         enterpriseNumber;
  uint16         optionDataCode;
  uint16         optionDataLen;
  uint16         bufIdx;
# if ( DOIP_IPV4_ENABLED == STD_ON )
  uint8          optionDataLenAll;
# endif /* DOIP_IPV4_ENABLED = STD_ON */

  /* ----- Implementation ----------------------------------------------- */
# if ( DOIP_IPV6_ENABLED == STD_ON )
#  if ( DOIP_IPV4_ENABLED == STD_ON )
  if ( OptionCode == DOIP_DHCPV6_OPT_VENDOR_OPTS_OPT_CODE )
#  endif /* DOIP_IPV4_ENABLED = STD_ON */
  {
    /* Option code is DHCPv6 type. */
    if ( OptionBufferLength >= (DOIP_DHCPV6_OPT_VENDOR_OPTS_MIN_LEN) )
    {
      /* #10 Read the buffer data if the buffer length meets the minimum value for DHCPv6 vendor option (if enabled). */
      bufIdx = 0u;
      IPBASE_GET_UINT32(OptionBufferPtr, bufIdx, enterpriseNumber);                                                    /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      bufIdx += 4u;
      /* enterprise specific data within the 'sub-option' */
      IPBASE_GET_UINT16(OptionBufferPtr, bufIdx, optionDataCode);                                                      /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      bufIdx += 2u;
      /* enterprise specific data within the 'sub-option' */
      IPBASE_GET_UINT16(OptionBufferPtr, bufIdx, optionDataLen);                                                       /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

      if ( /* Enterprise Number matches expected */
           (enterpriseNumber == DOIP_DHCPVX_OPT_VENDOR_ENT_NUM_3210) &&
           /* DHCP Vendor Option - 'sub-option' code matches DOIP 'sub-option' code regarding enterprise number */
           (optionDataCode == DOIP_DHCPVX_OPT_VENDOR_SUB_CODE) &&
           /* not more than 4 addresses */
           (optionDataLen <= (DOIP_DHCPV6_OPT_ADDR_SIZE * DOIP_DHCPVX_OPT_VENDOR_TABLE_SIZE)) &&
           /* at least one address */
           (optionDataLen >= (DOIP_DHCPV6_OPT_ADDR_SIZE)) &&
           /* no 'half' ip address is received */
           ((optionDataLen % DOIP_DHCPV6_OPT_ADDR_SIZE) == 0u) &&
           /* general length check of 'sub-option' length field to received overall length */
           /* 8u = enterNum (4u) within the option + code (2u) within the 'sub-option' + len (2u) within the 'sub-option' */
           (optionDataLen == (OptionBufferLength - 8u)) )
      {
        /* #20 Return E_OK if the data read agrees to the DHCPv6 vendor option format. */
        retVal = E_OK;
      }
    }
  }
#  if ( DOIP_IPV4_ENABLED == STD_ON )
  else
#  else
  DOIP_DUMMY_STATEMENT(OptionCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* DOIP_IPV4_ENABLED = STD_ON */
# endif /* DOIP_IPV6_ENABLED = STD_ON */
# if ( DOIP_IPV4_ENABLED == STD_ON )
  {
    /* Option code is DHCPv4 type. */
    if ( OptionBufferLength >= (DOIP_DHCPV4_OPT_VENDOR_OPTS_MIN_LEN) )
    {
      /* #30 Read the buffer data if the buffer length meets the minimum value for DHCPv4 vendor option (if enabled). */
      bufIdx = 0u;
      IPBASE_GET_UINT32(OptionBufferPtr, bufIdx, enterpriseNumber);                                                    /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      bufIdx += 4u;
      IPBASE_GET_UINT8(OptionBufferPtr, bufIdx, optionDataLenAll);                                                     /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      bufIdx += 1u;
      /* enterprise specific data within the 'sub-option' */
      IPBASE_GET_UINT8(OptionBufferPtr, bufIdx, optionDataCode);                                                       /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      bufIdx += 1u;
      /* enterprise specific data within the 'sub-option' */
      IPBASE_GET_UINT8(OptionBufferPtr, bufIdx, optionDataLen);                                                        /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

      if ( /* Enterprise Number matches expected */
           (enterpriseNumber == DOIP_DHCPVX_OPT_VENDOR_ENT_NUM_3210) &&
           /* DHCP Vendor Option - 'sub-option' code matches DOIP 'sub-option' code regarding enterprise number */
           (optionDataCode == DOIP_DHCPVX_OPT_VENDOR_SUB_CODE) &&
           /* not more than 4 addresses */
           (optionDataLen <= (DOIP_DHCPV4_OPT_ADDR_SIZE * DOIP_DHCPVX_OPT_VENDOR_TABLE_SIZE)) &&
           /* at least one address */
           (optionDataLen >= (DOIP_DHCPV4_OPT_ADDR_SIZE)) &&
           /* no 'half' ip address is received */
           ((optionDataLen % DOIP_DHCPV4_OPT_ADDR_SIZE) == 0u) &&
           /* vendor 'sub-option data' length is consistent */
           /* 2u = code (1u) within the 'sub-option' + len (1u) within the 'sub-option' */
           ((optionDataLen + 2u) == optionDataLenAll) &&
           /* general length check of 'sub-option' length field to received overall length */
           /* 5u = enterNum (4u) within the option + dataLen (1u) within the option */
           (optionDataLenAll == (OptionBufferLength - 5u)) )
      {
        /* #40 Return E_OK if the data read agrees to the DHCPv4 vendor option format. */
        retVal = E_OK;
      }
    }
  }
#  if ( DOIP_IPV6_ENABLED == STD_OFF )
  DOIP_DUMMY_STATEMENT(OptionCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* DOIP_IPV6_ENABLED = STD_OFF */
# endif /* DOIP_IPV4_ENABLED = STD_ON */

  return retVal;
} /* DoIP_Util_ValidateDhcpVendorOptsRxBuf() */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_HandleIpAddrListFromVendorOpts()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_HandleIpAddrListFromVendorOpts(                                             /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfLocalAddrType LocalAddrIdx,                                                                               /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 OptionCode,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  uint16 OptionBufferLength,                                                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_LENGTH */
  P2CONST(uint8, AUTOMATIC, DOIP_APPL_VAR) OptionBufferPtr)                                                            /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_DhcpIpAddrDynType venOptIpAddrDynList[DOIP_DHCP_IPADDRESS_LIST_MAX_SIZE];
  DoIP_DhcpIpAddrIterType venOptsAddrListIter;

  /* ----- Implementation ----------------------------------------------- */
  for ( venOptsAddrListIter = 0u;
        venOptsAddrListIter < DOIP_DHCP_IPADDRESS_LIST_MAX_SIZE;
        venOptsAddrListIter++ )
  {
    /* Initialize the list with invalid IP address type. */
    venOptIpAddrDynList[venOptsAddrListIter].DhcpIpAddr.domain = SOAD_AF_INVALID;                                      /* SBSW_DOIP_ARRAY_WRITE */
  }

  /* #10 Check if IP addresses supplied from DHCP can be read and filtered. */
  if ( DoIP_Dhcp_ReadAndFilterIpAddresses(OptionCode, OptionBufferLength, OptionBufferPtr,                             /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
        &venOptIpAddrDynList[0]) == E_OK )
  {
    /* #20 Compare the received IP addresses to the locally stored IP addresses. */
    DoIP_Dhcp_CompareToLocalIpAddrList(LocalAddrIdx, &venOptIpAddrDynList[0]);                                         /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

    /* #30 Update the local list with the new set of IP addresses. */
    DoIP_Dhcp_UpdateLocalIpAddrList(LocalAddrIdx, &venOptIpAddrDynList[0]);                                            /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  }
} /* DoIP_Util_HandleIpAddrListFromDhcpVendorOpts() */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_ReadAndFilterIpAddresses()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3206 5 */ /* MD_DoIP_3206 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Dhcp_ReadAndFilterIpAddresses(                                         /* INTERNAL_NOTE_SBSW_OK */
  uint16 OptionCode,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  uint16 OptionBufferLength,                                                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_LENGTH */
  P2CONST(uint8, AUTOMATIC, DOIP_APPL_VAR) OptionBufferPtr,                                                            /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(DoIP_DhcpIpAddrDynType, AUTOMATIC, DOIP_APPL_VAR) VenOptIpAddrDynListPtr)                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal = E_NOT_OK;
  SoAd_SockAddrInetXType  ipAddr = { SOAD_AF_INVALID, 0u, { 0u } };
  SoAd_SockAddrInetXType  venOptIpAddr = { SOAD_AF_INVALID, 0u, { 0u } };
  DoIP_DhcpIpAddrIterType venOptsAddrListIter = 0u;
  DoIP_DhcpIpAddrIterType ipAddrListIter;
  uint16                  dynAddrOffset;
  uint16                  addrSize;
  uint16                  staticAddrOffset;
  uint16                  optionDataLen;
  boolean                 isAddrRepeated;

  /* ----- Implementation ----------------------------------------------- */
  /* Initialize the DOIP port number - 13400. */
  ipAddr.port = IPBASE_HTON16(DOIP_PORT_NUMBER);

# if ( DOIP_IPV6_ENABLED == STD_ON )
#  if ( DOIP_IPV4_ENABLED == STD_ON )
  if ( OptionCode == DOIP_DHCPV6_OPT_VENDOR_OPTS_OPT_CODE )
#  endif /* DOIP_IPV4_ENABLED == STD_ON */
  {
    /* The optionDataLen field within the buffer was validated by DoIP_Dhcp_ValidateVendorOptsRxBuf() before. */
    IPBASE_GET_UINT16(OptionBufferPtr, DOIP_DHCPV6_OPT_VENDOR_OPTS_SUB_OPT_LEN_OFFSET, optionDataLen);                 /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
    staticAddrOffset = DOIP_DHCPV6_OPT_VENDOR_OPTS_ADDR_OFFSET;
    addrSize = DOIP_DHCPV6_OPT_ADDR_SIZE;
    venOptIpAddr.domain = SOAD_AF_INET6;
    ipAddr.domain = SOAD_AF_INET6;
  }
#  if ( DOIP_IPV4_ENABLED == STD_ON )
  else
#  else
  DOIP_DUMMY_STATEMENT(OptionCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* DOIP_IPV4_ENABLED == STD_ON */
# endif /* DOIP_IPV6_ENABLED == STD_ON */
# if ( DOIP_IPV4_ENABLED == STD_ON )
  {
    /* The optionDataLen field within the buffer was validated by DoIP_Dhcp_ValidateVendorOptsRxBuf() before. */
    IPBASE_GET_UINT8(OptionBufferPtr, DOIP_DHCPV4_OPT_VENDOR_OPTS_SUB_OPT_LEN_OFFSET, optionDataLen);                  /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
    staticAddrOffset = DOIP_DHCPV4_OPT_VENDOR_OPTS_ADDR_OFFSET;
    addrSize = DOIP_DHCPV4_OPT_ADDR_SIZE;
    venOptIpAddr.domain = SOAD_AF_INET;
    ipAddr.domain = SOAD_AF_INET;
  }
#  if ( DOIP_IPV6_ENABLED == STD_OFF )
  DOIP_DUMMY_STATEMENT(OptionCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* DOIP_IPV6_ENABLED = STD_OFF */
# endif /* DOIP_IPV4_ENABLED == STD_ON */

  /* #10 Iterate over the option buffer till the given buffer length, incrementing each time by the IP address size. */
  for ( dynAddrOffset = 0u;
        dynAddrOffset < optionDataLen;
        dynAddrOffset += addrSize )
  {
    /* Initialize the Vendor Options Dynamic IP Address List. */
    VenOptIpAddrDynListPtr[venOptsAddrListIter].DhcpIpAddr.port = ipAddr.port;                                         /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    VenOptIpAddrDynListPtr[venOptsAddrListIter].DhcpIpAddr.domain = ipAddr.domain;                                     /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */

    /* Retrieve the IP addresses from the buffer and store them in the temporary list. */
    /* PRQA S 0314 2 */ /* MD_MSR_VStdLibCopy */
    VStdLib_MemCpy(DOIP_A_P2VAR(void)venOptIpAddr.addr,                                                                /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
      DOIP_A_P2CONST(void)&OptionBufferPtr[staticAddrOffset + dynAddrOffset], addrSize);

    /* #20 Check if new IP Address provided by DHCP is valid. */
    if ( DoIP_Dhcp_ValidateIpAddress(venOptIpAddr) == E_OK )
    {
      /* Reset the flag for new the new address. */
      isAddrRepeated = FALSE;

      /* #30 Check if the IP address repeats in the DHCP supplied list. */
      for ( ipAddrListIter = 0u;
            ipAddrListIter < venOptsAddrListIter;
            ipAddrListIter++ )
      {
        if ( DoIP_Util_CompareIpAddr(ipAddr.domain, VenOptIpAddrDynListPtr[ipAddrListIter].DhcpIpAddr.addr,            /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
              venOptIpAddr.addr) == TRUE )
        {
          isAddrRepeated = TRUE;
          break;
        }
      }

      if ( isAddrRepeated == FALSE )
      {
        /* #40 Copy the IP address to the dynamic list of IP addresses. */
        /* PRQA S 0314 2 */ /* MD_MSR_VStdLibCopy */
        VStdLib_MemCpy(DOIP_A_P2VAR(void)VenOptIpAddrDynListPtr[venOptsAddrListIter].DhcpIpAddr.addr,                  /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
          DOIP_A_P2CONST(void)venOptIpAddr.addr, addrSize);

        /* Read the next DHCP address from the buffer. */
        venOptsAddrListIter++;
      }

      /* The received IP address list contains at least one valid IP address */
      retVal = E_OK;
    }
    else
    {
      /* Received DHCP IP address is not valid, overwrite the IP address in next loop */
    }
  }

  DOIP_DUMMY_STATEMENT(OptionBufferLength); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

  return retVal;
} /* DoIP_Dhcp_ReadAndFilterIpAddresses() */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_ValidateIpAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Dhcp_ValidateIpAddress(                                                /* INTERNAL_NOTE_SBSW_OK */
  SoAd_SockAddrInetXType IpAddr)                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_SOCKADDR_STRUCT */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType            retVal;
  uint8                     netmask = 0u;
  SoAd_SockAddrInetXType    localAddr = { SOAD_AF_INVALID, 0u, { 0u } };
  SoAd_SockAddrInetXType    defaultRouter = { SOAD_AF_INVALID, 0u, { 0u } };
  DoIP_ConnectionIterType   connectionIter;

  /* ----- Implementation ----------------------------------------------- */
# if ( DOIP_IPV6_ENABLED == STD_ON )
#  if ( DOIP_IPV4_ENABLED == STD_ON )
  if ( IpAddr.domain == SOAD_AF_INET6 )
#  endif /* DOIP_IPV4_ENABLED == STD_ON */
  {
    /* #10 Check if IPv6 address is an invalid address. */
    retVal = DoIP_Util_CheckIpV6Addr(IpAddr);
  }
#  if ( DOIP_IPV4_ENABLED == STD_ON )
  else
#  endif /* DOIP_IPV4_ENABLED == STD_ON */
# endif /* DOIP_IPV6_ENABLED == STD_ON */
# if ( DOIP_IPV4_ENABLED == STD_ON )
  {
    /* #20 Check if IPv4 address is an invalid address. */
    retVal = DoIP_Util_CheckIpV4Addr(IpAddr);
  }
# endif /* DOIP_IPV4_ENABLED == STD_ON */

  if ( retVal == E_OK )
  {
    for ( connectionIter = DOIP_CONNECTION_TCP_UDP_TOTAL;
          connectionIter < DoIP_GetSizeOfConnection();
          connectionIter++ )
    {
      /* PRQA S 0310 2 */ /* MD_DoIP_11.4 */
      if ( SoAd_GetLocalAddr(DoIP_GetSoConIdOfConnectionDyn(connectionIter), DOIP_A_P2VAR(SoAd_SockAddrType)&localAddr, /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
            &netmask, DOIP_A_P2VAR(SoAd_SockAddrType)&defaultRouter) == E_OK )
      {
        /* #30 Validate the received IP address against all DoIP related local IP addresses. */
        if ( DoIP_Util_CompareIpAddr(IpAddr.domain, IpAddr.addr, localAddr.addr) == TRUE )                             /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
        {
          /* The received address matches the local address; exit return E_NOT_OK */
          retVal = E_NOT_OK;
          break;
        }
      }
    }
  }
  return retVal;
} /* DoIP_Dhcp_ValidateIpAddress() */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_CompareToLocalIpAddrList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_CompareToLocalIpAddrList(                                                   /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfLocalAddrType LocalAddrIdx,                                                                               /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(DoIP_DhcpIpAddrDynType, AUTOMATIC, DOIP_APPL_VAR) VenOptIpAddrDynListPtr)                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_SOCKADDR_STRUCT */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_IpAddrListIterType ipAddrListIdx;
  DoIP_DhcpIpAddrIterType venOptsAddrListIter;

  /* ----- Implementation ----------------------------------------------- */
  for ( venOptsAddrListIter = 0u;
        venOptsAddrListIter < DOIP_DHCP_IPADDRESS_LIST_MAX_SIZE;
        venOptsAddrListIter++ )
  {
    /* #10 Iterate over all the received Vendor option IP address list until the ones with invalid address. */
    if ( VenOptIpAddrDynListPtr[venOptsAddrListIter].DhcpIpAddr.domain != SOAD_AF_INVALID )
    {
      /* Assumed no match ==> new DHCP address has to be added to the local list. */
      VenOptIpAddrDynListPtr[venOptsAddrListIter].IsAddedToList = FALSE;                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */

      for ( ipAddrListIdx = DoIP_GetIpAddrListStartIdxOfLocalAddr(LocalAddrIdx);
            ipAddrListIdx < DoIP_GetIpAddrListEndIdxOfLocalAddr(LocalAddrIdx);
            ipAddrListIdx++ )
      {
        /* #20 Compare the locally stored IP addresses with the Vendor option IP address received from DHCP. */
        if ( DoIP_Util_CompareIpAddr(DoIP_GetIpAddrOfIpAddrList(ipAddrListIdx).domain,                                 /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
              DoIP_GetIpAddrOfIpAddrList(ipAddrListIdx).addr,
              VenOptIpAddrDynListPtr[venOptsAddrListIter].DhcpIpAddr.addr) == TRUE )
        {
          /* #30 Mark that the received IP address already exists in the local IP address list. */
          VenOptIpAddrDynListPtr[venOptsAddrListIter].IsAddedToList = TRUE;                                            /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
          break;
        }
      }
    }
    else
    {
      /* Start of invalid addresses in the VenOptIpAddrDynList, hence skip the remaining. */
      break;
    }
  }
} /* DoIP_Dhcp_CompareToLocalIpAddrList() */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_UpdateLocalIpAddrList()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_UpdateLocalIpAddrList(                                                      /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfLocalAddrType LocalAddrIdx,                                                                               /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(DoIP_DhcpIpAddrDynType, AUTOMATIC, DOIP_APPL_VAR) VenOptIpAddrDynListPtr)                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_SOCKADDR_STRUCT */
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SockAddrInetXType unspecifiedAddress = { SOAD_AF_INVALID, 0u, { 0u } };
  DoIP_IpAddrListIterType ipAddrListIdx;
  DoIP_DhcpIpAddrIterType venOptsAddrListIter = 0u;

  /* ----- Implementation ----------------------------------------------- */
  DOIP_BEGIN_CRITICAL_SECTION();

  /* #10 Iterate over entire local vendor option IP address list. */
  for ( ipAddrListIdx = DoIP_GetIpAddrListStartIdxOfLocalAddr(LocalAddrIdx);
        ipAddrListIdx < DoIP_GetIpAddrListEndIdxOfLocalAddr(LocalAddrIdx);
        ipAddrListIdx++ )
  {
    /* #20 Check if corresponding IP address in received list is valid. */
    if ( VenOptIpAddrDynListPtr[venOptsAddrListIter].DhcpIpAddr.domain != SOAD_AF_INVALID  )
    {
      /* #30 Update the local IP address list entry with address from the received list. */
      DoIP_SetIpAddrOfIpAddrList(ipAddrListIdx, VenOptIpAddrDynListPtr[venOptsAddrListIter].DhcpIpAddr);               /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL03 */

      /* #40 Check if it is a newly received address. */
      if ( VenOptIpAddrDynListPtr[venOptsAddrListIter].IsAddedToList == FALSE )
      {
        /* #50 Mark entry to send vehicle announcements. */
        DoIP_SetTriggerVehAnnOfIpAddrList(ipAddrListIdx, TRUE);                                                        /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL03 */
      }
      venOptsAddrListIter++;
    }
    /* #60 Set local IP address list entry as invalid otherwise. */
    else
    {
      DoIP_SetIpAddrOfIpAddrList(ipAddrListIdx, unspecifiedAddress);                                                   /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL03 */
      DoIP_SetTriggerVehAnnOfIpAddrList(ipAddrListIdx, FALSE);                                                         /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL03 */
    }
  }

  DOIP_END_CRITICAL_SECTION();
} /* DoIP_Dhcp_UpdateLocalIpAddrList() */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_ProcessIpAddrListToTriggerVehAnnouncements()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_ProcessIpAddrListToTriggerVehAnnouncements(void)                            /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfConnectionType connectionIdx;
  DoIP_IpAddrListIterType   ipAddrListIdx;
  DoIP_SizeOfLocalAddrType  localAddrIdx;

  /* ----- Implementation ----------------------------------------------- */
  for ( connectionIdx = DOIP_CONNECTION_TCP_UDP_TOTAL;
        connectionIdx < DoIP_GetSizeOfConnection();
        connectionIdx++ )
  {
    /* #10 Iterate over all online socket connections (vehicle announcement) and whose IP addresses are assigned. */
    if ( (DoIP_GetSoConStateOfConnectionDyn(connectionIdx) == SOAD_SOCON_ONLINE) &&
         (DoIP_GetIpAddrStateOfConnectionDyn(connectionIdx) == SOAD_IPADDR_STATE_ASSIGNED) )
    {
      localAddrIdx = DoIP_GetLocalAddrIdxOfConnection(connectionIdx);
      for ( ipAddrListIdx = DoIP_GetIpAddrListStartIdxOfLocalAddr(localAddrIdx);
            ipAddrListIdx < DoIP_GetIpAddrListEndIdxOfLocalAddr(localAddrIdx);
            ipAddrListIdx++ )
      {
        /* #20 Handle vehicle announcements on connections. */
        DoIP_Dhcp_HandleVehAnnounceTriggOfIpAddrList(connectionIdx, ipAddrListIdx);
      }
    }
  }
} /* DoIP_Dhcp_ProcessIpAddrListToTriggerVehAnnouncements() */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Dhcp_HandleVehAnnounceTriggOfIpAddrList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Dhcp_HandleVehAnnounceTriggOfIpAddrList(                                         /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_IpAddrListIterType IpAddrListIdx)                                                                               /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SockAddrInetXType ipAddr;

  /* ----- Implementation ----------------------------------------------- */
  DOIP_BEGIN_CRITICAL_SECTION();

  /* #10 Check if the trigger is enabled for the DHCP provided IP address. */
  if ( DoIP_IsTriggerVehAnnOfIpAddrList(IpAddrListIdx) )
  {
    ipAddr = DoIP_GetIpAddrOfIpAddrList(IpAddrListIdx);

    /* #20 Transmit vehicle announcement and check if the transmission succeeds. */
    if ( DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT, DOIP_ANNOUNCE_NUM, FALSE,              /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
          &ipAddr) == E_OK )
    {
      /* #30 Reset the trigger only if the transmission succeeds. */
      DoIP_SetTriggerVehAnnOfIpAddrList(IpAddrListIdx, FALSE);                                                         /* SBSW_DOIP_PARAM_VALID_INDEX */
    }
  }

  DOIP_END_CRITICAL_SECTION();
} /* DoIP_Dhcp_HandleVehAnnounceTriggOfIpAddrList() */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

/**********************************************************************************************************************
 *  DoIP_Con_HandleSoConModeChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleSoConModeChg(                                                          /* INTERNAL_NOTE_SBSW_OK */
  SoAd_SoConIdType SoConId,                                                                                            /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  SoAd_SoConModeType Mode,                                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr)                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle socket connection mode change to online. */
  if ( Mode == SOAD_SOCON_ONLINE )
  {
    DoIP_Con_HandleOnlineSoConModeChg(SoConId, Mode, ConnectionIdx, ErrorIdPtr);                                       /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }
  /* #20 Handle socket connection mode change to offline or reconnect. */
  else
  {
    DoIP_Con_HandleOfflineSoConModeChg(Mode, ConnectionIdx);
  }
} /* DoIP_Con_HandleSoConModeChg() */

/**********************************************************************************************************************
 *  DoIP_Con_HandleOnlineSoConModeChg()
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
/* PRQA S 3206 5 */ /* MD_DoIP_3206 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleOnlineSoConModeChg(                                                    /* INTERNAL_NOTE_SBSW_OK */
  SoAd_SoConIdType SoConId,                                                                                            /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  SoAd_SoConModeType Mode,                                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr) /* PRQA S 3673 */ /* MD_DoIP_16.7 */                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if IP address is assigned. */
  if ( DoIP_GetIpAddrStateOfConnectionDyn(ConnectionIdx) == SOAD_IPADDR_STATE_ASSIGNED )
  {
    DoIP_SetSoConStateOfConnectionDyn(ConnectionIdx, Mode);                                                            /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    DoIP_SetSoConClosingOfConnectionDyn(ConnectionIdx, FALSE);                                                         /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

    /* #20 Check if connection is UDP and trigger vehicle announcement. */
    if ( ConnectionIdx >= DOIP_CONNECTION_TCP_UDP_TOTAL )
    {
      if ( DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT, DOIP_ANNOUNCE_NUM, FALSE,            /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
            NULL_PTR) != E_OK )
      { /* buffer overflow after socket connection setup should not happen */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
        /* #30 Set error if transmit failed (if enabled). */
        *ErrorIdPtr = DOIP_E_NOBUFS;                                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
#else
        /* nothing to do here */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
      }
    }
#if ( DOIP_VERIFY_RX_PDU_ENABLED == STD_ON )
    /* #40 Check if connection is TCP and save remote/local IP address (if enabled). */
    if ( ConnectionIdx < DoIP_GetSizeOfConnectionTcp() )
    {
      uint8 netmask = 0u;
      SoAd_SockAddrInetXType remIpAddr = { SOAD_AF_INVALID, 0u, { 0u } };
      SoAd_SockAddrInetXType locIpAddr = { SOAD_AF_INVALID, 0u, { 0u } };
      SoAd_SockAddrInetXType defaultRouter = { SOAD_AF_INVALID, 0u, { 0u } };

      /* PRQA S 0310 7 */ /* MD_DoIP_11.4 */
      (void)SoAd_GetRemoteAddr(SoConId, DOIP_A_P2VAR(SoAd_SockAddrType)&remIpAddr);                                    /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      (void)SoAd_GetLocalAddr (SoConId, DOIP_A_P2VAR(SoAd_SockAddrType)&locIpAddr,                                     /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
        &netmask, DOIP_A_P2VAR(SoAd_SockAddrType)&defaultRouter);

      DoIP_SetRemIpAddrOfConnectionTcpDyn((DoIP_SizeOfConnectionTcpType)ConnectionIdx, remIpAddr);                     /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
      DoIP_SetLocIpAddrOfConnectionTcpDyn((DoIP_SizeOfConnectionTcpType)ConnectionIdx, locIpAddr);                     /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    }
#else
    DOIP_DUMMY_STATEMENT(SoConId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_VERIFY_RX_PDU_ENABLED == STD_ON */
  }
  else
  {
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
    /* #50 Set error if unassigned (if enabled). */
    *ErrorIdPtr = DOIP_E_UNEXPECTED_ASSIGNMENT;                                                                        /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
#else
    /* nothing to do here */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  }

#if ( DOIP_DEV_ERROR_DETECT == STD_OFF )
  DOIP_DUMMY_STATEMENT(ErrorIdPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_DETECT == STD_OFF */
} /* DoIP_Con_HandleOnlineSoConModeChg() */

/**********************************************************************************************************************
 *  DoIP_Con_HandleOfflineSoConModeChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleOfflineSoConModeChg(                                                   /* INTERNAL_NOTE_SBSW_OK */
  SoAd_SoConModeType Mode,                                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  DoIP_SizeOfConnectionType ConnectionIdx)                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Implementation ----------------------------------------------- */
  /* Do not check current state since it might be reset on call to SoAd_CloseSoCon already. */
  DoIP_SetSoConStateOfConnectionDyn(ConnectionIdx, Mode);                                                              /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  DoIP_SetSoConClosingOfConnectionDyn(ConnectionIdx, FALSE);                                                           /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

  if ( ConnectionIdx < DoIP_GetSizeOfConnectionTcp() )
  {
    /* #10 Handle TCP socket connection mode change to offline or reconnect. */
    DoIP_Con_HandleOfflineTcpSoConModeChg(ConnectionIdx);
  }
  else
  {
    /* #20 Handle UDP socket connection mode change to offline or reconnect. */
    DoIP_Con_HandleOfflineUdpSoConModeChg(ConnectionIdx);
  }
} /* DoIP_Con_HandleOfflineSoConModeChg() */

/**********************************************************************************************************************
 *  DoIP_Con_HandleOfflineTcpSoConModeChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleOfflineTcpSoConModeChg(                                                /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset socket connection specific structs. */
  if ( testerIdx != DoIP_GetSizeOfTester() )
  {
    DoIP_SetConnectionTcpIdxOfTesterDyn(testerIdx, DoIP_GetSizeOfConnectionTcp());                                     /* SBSW_DOIP_RegisterTester */
#if ( DOIP_NACK_APPEND_REQ == STD_ON )
    DoIP_SetDiagNAckOffsetOfTesterDyn(testerIdx, 0u);                                                                  /* SBSW_DOIP_RegisterTester */
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */
  }

  DoIP_SetInactivCntOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                          /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  DoIP_SetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                         /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  DoIP_SetTxBytesCopiedOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  DoIP_SetTxTpSessionActiveOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                                /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  DoIP_SetRxTpSessionActiveOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                                /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  DoIP_SetSkipRxMsgOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                                        /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  DoIP_SetTpTxPreHdrTypeOfConnectionTcpDyn(ConnectionTcpIdx, DOIP_HDR_TYPE_INVALID);                                   /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
#if ( DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON )
  DoIP_SetTxTpCancelRequestedOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                              /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
#endif /* DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON */
#if ( DOIP_PROVIDE_CANCEL_RECEIVE_API == STD_ON )
  DoIP_SetRxTpCancelRequestedOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                              /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
#endif /* DOIP_PROVIDE_CANCEL_RECEIVE_API == STD_ON */
  DoIP_RxTcpRout_RegisterTester(ConnectionTcpIdx, DoIP_GetSizeOfTester(), DOIP_ADDR_ANY,
    DoIP_GetSizeOfRoutingActivation(), DOIP_ROUT_ACTIV_STATE_NONE);

  /* #20 Handle pending alive checks. */
  DoIP_Con_HandleOfflineTcpAliveCheckSoConModeChg(ConnectionTcpIdx);

  /* #30 Cancel ongoing reception if Rx channel is active. */
  if ( DoIP_IsChannelRxActiveOfConnectionTcpDyn(ConnectionTcpIdx) )
  {
    PduR_DoIPTpRxIndication(DoIP_GetPduRRxPduIdOfChannel(DoIP_GetChannelRxLastIdxOfConnectionTcpDyn(ConnectionTcpIdx)),
      E_NOT_OK);
    DoIP_SetChannelRxLastIdxOfConnectionTcpDyn(ConnectionTcpIdx, DoIP_GetSizeOfChannel());                             /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    DoIP_SetChannelRxActiveOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                                /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }

  /* #40 Remove all outstanding TCP transmissions from Tx queue. */
  while ( DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(ConnectionTcpIdx) > 0u )
  {
    DoIP_TxTcpQueue_RemoveElement(ConnectionTcpIdx, E_NOT_OK);
  }
} /* DoIP_Con_HandleOfflineTcpSoConModeChg() */

/**********************************************************************************************************************
 *  DoIP_Con_HandleOfflineTcpAliveCheckSoConModeChg()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleOfflineTcpAliveCheckSoConModeChg(                                      /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_GetConnectionTcpIdxOfRoutActivHandler(0u);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if routing activation handler is used. */
  if ( connectionTcpIdx != DoIP_GetSizeOfConnectionTcp() )
  {
    /* #20 Check if alive checks are pending. */
    if ( DoIP_GetAliveCheckElemNumOfRoutActivHandler(0u) > 0u )
    {
      DoIP_AliveCheckListIterType aliveCheckListIdx;

      for ( aliveCheckListIdx = 0u;
            aliveCheckListIdx < DoIP_GetSizeOfAliveCheckList();
            aliveCheckListIdx++ )
      {
        /* #30 Check if alive checks are pending for current connection and remove element from list. */
        if ( ConnectionTcpIdx == DoIP_GetConnectionTcpIdxOfAliveCheckList(aliveCheckListIdx) )
        {
          DoIP_SetConnectionTcpIdxOfAliveCheckList(aliveCheckListIdx, DoIP_GetSizeOfConnectionTcp());                  /* SBSW_DOIP_CSL01 */
          DoIP_DecAliveCheckElemNumOfRoutActivHandler(0u);                                                             /* SBSW_DOIP_RoutActivHandler */
          break;
        }
      }
    }

    /* #40 Check if no alive checks are pending anymore. */
    if ( DoIP_GetAliveCheckElemNumOfRoutActivHandler(0u) == 0u )
    {
      /* #50 Check if socket connection on which the routing activation request has been received is still online. */
      if ( DoIP_GetSoConStateOfConnectionDyn(connectionTcpIdx) == SOAD_SOCON_ONLINE )
      {
        /* #60 Trigger routing activation handling in next main function. */
        DoIP_SetAliveCheckCntOfRoutActivHandler(0u, DOIP_ALIVE_CHECK_WAIT_NEXT_MAIN);                                  /* SBSW_DOIP_RoutActivHandler */
      }
      /* #70 Release routing activation handler otherwise. */
      else
      {
        DoIP_SetConnectionTcpIdxOfRoutActivHandler(0u, DoIP_GetSizeOfConnectionTcp());                                 /* SBSW_DOIP_RoutActivHandler */
        DoIP_SetAliveCheckCntOfRoutActivHandler(0u, 0u);                                                               /* SBSW_DOIP_RoutActivHandler */
      }
    }
  }
} /* DoIP_Con_HandleOfflineTcpAliveCheckSoConModeChg() */

/**********************************************************************************************************************
 *  DoIP_Con_HandleOfflineUdpSoConModeChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleOfflineUdpSoConModeChg(                                                /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx)                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_TxUdpMgtListIterType txUdpMgtListIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over Tx UDP list. */
  for ( txUdpMgtListIdx = 0u;
        txUdpMgtListIdx < DoIP_GetSizeOfTxUdpMgtList();
        txUdpMgtListIdx++ )
  {
    /* #20 Invalidate UDP connection if element is in list. */
    if ( DoIP_GetConnectionIdxOfTxUdpMgtList(txUdpMgtListIdx) == ConnectionIdx )
    {
#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
      if ( DoIP_GetHdrTypeOfTxUdpMgtList(txUdpMgtListIdx) == DOIP_HDR_TYPE_OEM_SPECIFIC )
      {
        DoIP_SetOemPayloadTypeUdpBufLen(0u);                                                                           /* SBSW_DOIP_OemPayloadType */
      }
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

      DoIP_SetConnectionIdxOfTxUdpMgtList(txUdpMgtListIdx, DoIP_GetSizeOfConnection());                                /* SBSW_DOIP_CSL01 */
    }
  }
} /* DoIP_Con_HandleOfflineUdpSoConModeChg() */

/**********************************************************************************************************************
 *  DoIP_Con_SoConInitAll()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Con_SoConInitAll(                                                      /* INTERNAL_NOTE_SBSW_OK */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr) /* PRQA S 3673 */ /* MD_DoIP_16.7 */                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initiate whole socket connection struct if not done before. */
  if ( DoIP_GetSoConIdOfConnectionDyn(0u) == SOAD_INV_SO_CON_ID )
  {
    DoIP_ConnectionIterType connectionIdx;
    SoAd_SoConIdType soConId = 0u;

    /* #20 For all connections get socket connection identifier from SoAd. */
    for ( connectionIdx = 0u;
          connectionIdx < DoIP_GetSizeOfConnection();
          connectionIdx++ )
    {
      retVal |= SoAd_GetSoConId(DoIP_GetSoAdTxPduIdOfConnection(connectionIdx), &soConId);                             /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */

      /* #30 Save socket connection identifier if successfully received from SoAd. */
      if ( retVal == E_OK )
      {
        DoIP_SetSoConIdOfConnectionDyn(connectionIdx, soConId);                                                        /* SBSW_DOIP_CSL02 */
      }
      else
      {
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
        /* #40 Otherwise set error (if enabled). */
        *ErrorIdPtr = DOIP_E_SOAD_CALL_FAILED;                                                                         /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
#else
        DOIP_DUMMY_STATEMENT(ErrorIdPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
        break;
      }
    }
  }

  return retVal;
} /* DoIP_Con_SoConInitAll() */

/**********************************************************************************************************************
 *  DoIP_Con_SoConOpen()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_SoConOpen(                                                                   /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx)                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Implementation ----------------------------------------------- */
  DOIP_BEGIN_CRITICAL_SECTION();

  /* #10 Check if socket connection has to be opened. */
  if ( DoIP_GetSoConStateOfConnectionDyn(ConnectionIdx) == SOAD_SOCON_OFFLINE )
  {
    /* #20 Set socket connection state to reconnect to avoid multiple open requests and open socket connection. */
    DoIP_SetSoConStateOfConnectionDyn(ConnectionIdx, SOAD_SOCON_RECONNECT);                                            /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

    DOIP_END_CRITICAL_SECTION();

    (void)SoAd_OpenSoCon(DoIP_GetSoConIdOfConnectionDyn(ConnectionIdx));
  }
  else
  {
    DOIP_END_CRITICAL_SECTION();
  }
} /* DoIP_Con_SoConOpen() */

#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Con_SoConCloseAll()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Con_SoConCloseAll(void)                                                /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  DoIP_ConnectionIterType connectionIdx;

  /* ----- Implementation ----------------------------------------------- */
  for ( connectionIdx = 0u;
        connectionIdx < DoIP_GetSizeOfConnection();
        connectionIdx++ )
  {
    /* #10 Check for all socket connections if they are not yet closed. */
    if ( DoIP_GetSoConStateOfConnectionDyn(connectionIdx) != SOAD_SOCON_OFFLINE )
    {
      retVal = E_NOT_OK;

      /* #20 Check if socket connection has not yet been requested to close. */
      if ( !DoIP_IsSoConClosingOfConnectionDyn(connectionIdx) )
      {
        /* #30 Request closing of socket connection. */
        DoIP_SetSoConClosingOfConnectionDyn(connectionIdx, TRUE);                                                      /* SBSW_DOIP_CSL02 */
        DoIP_Con_SoConClose((DoIP_SizeOfConnectionType)connectionIdx);
      }
    }
  }

  return retVal;
} /* DoIP_Con_SoConCloseAll() */
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_Con_SoConClose()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_SoConClose(                                                                  /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx)                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Request closing of socket connection. */
  (void)SoAd_CloseSoCon(DoIP_GetSoConIdOfConnectionDyn(ConnectionIdx), TRUE);

  /* #20 Set state from reconnect to offline since it might be set to reconnect to avoid multiple open requests. */
  /* To set socket connection to offline here won't have side effects on the DoIP_SoConModeChg callback since socket
   * connection is reset there without checking current state. */
  if ( DoIP_GetSoConStateOfConnectionDyn(ConnectionIdx) == SOAD_SOCON_RECONNECT )
  {
    DoIP_SetSoConStateOfConnectionDyn(ConnectionIdx, SOAD_SOCON_OFFLINE);                                              /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }
} /* DoIP_Con_SoConClose() */

/**********************************************************************************************************************
 *  DoIP_Con_HandleLocalIpAddrAssignmentChg()
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
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleLocalIpAddrAssignmentChg(                                              /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  SoAd_IpAddrStateType State)                                                                                          /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfLocalAddrType localAddrIdx = DoIP_GetLocalAddrIdxOfConnection(ConnectionIdx);
#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
  const SoAd_SockAddrInetXType ipAddr = { SOAD_AF_INVALID, 0u, { 0u } };
  DoIP_IpAddrListIterType ipAddrListIdx;
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Store new assignment state. */
  DoIP_SetIpAddrStateOfConnectionDyn(ConnectionIdx, State);                                                            /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

  /* #20 Check if IP address assignment changed to unassigned. */
  if ( State == SOAD_IPADDR_STATE_UNASSIGNED )
  {
    DoIP_IpAddrAssignmentIterType ipAddrAssignmentIdx;

    /* #30 Iterate over all related IP address assignments. */
    for ( ipAddrAssignmentIdx = DoIP_GetIpAddrAssignmentStartIdxOfLocalAddr(localAddrIdx);
          ipAddrAssignmentIdx < DoIP_GetIpAddrAssignmentEndIdxOfLocalAddr(localAddrIdx);
          ipAddrAssignmentIdx++ )
    {
      /* #40 Reset IP address request state. */
      DoIP_SetIpAddrReqStateOfIpAddrAssignmentDyn(ipAddrAssignmentIdx, DOIP_IP_ADDR_REQ_STATE_NONE);                   /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL03 */
    }

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
    DOIP_BEGIN_CRITICAL_SECTION();

    /* #50 Iterate over related IP address list and reset IP addresses. */
    for ( ipAddrListIdx = DoIP_GetIpAddrListStartIdxOfLocalAddr(localAddrIdx);
          ipAddrListIdx < DoIP_GetIpAddrListEndIdxOfLocalAddr(localAddrIdx);
          ipAddrListIdx++ )
    {
      DoIP_SetTriggerVehAnnOfIpAddrList(ipAddrListIdx, FALSE);                                                         /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL03 */
      DoIP_SetIpAddrOfIpAddrList(ipAddrListIdx, ipAddr);                                                               /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL03 */
    }

    DOIP_END_CRITICAL_SECTION();
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

    /* #60 Request to close socket connection. */
    DoIP_Con_SoConClose(ConnectionIdx);

#if ( DOIP_GID_SYNC_ENABLED == STD_ON )
    /* #70 Reset GID sync state if all IP addresses are unassigned (if GID sync is configured). */
    /* Check value before decrement since IP address unassigned is reported even if it has not been assigned before. */
    DOIP_BEGIN_CRITICAL_SECTION(); /* protects DoIP_LocalAddrAssignedCounter */
    if ( DoIP_LocalAddrAssignedCounter > 0u )
    {
      DoIP_LocalAddrAssignedCounter--;
      if ( DoIP_LocalAddrAssignedCounter == 0u )
      {
        DoIP_GidInSync = FALSE;
      }
    }
    DOIP_END_CRITICAL_SECTION();
#endif /* DOIP_GID_SYNC_ENABLED == STD_ON */
  }
  /* #80 Check if IP address assignment changed to assigned otherwise. */
  else if ( State == SOAD_IPADDR_STATE_ASSIGNED )
  {
    /* #90 Request to open socket connection if activation line state is active. */
#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
    if ( DoIP_ActivationLineState == DOIP_ACTIVATION_LINE_ACTIVE )
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */
    {
      DoIP_Con_SoConOpen(ConnectionIdx);
    }

#if ( DOIP_GID_SYNC_ENABLED == STD_ON )
    /* #100 Increment number of connections with assigned local addresses (if GID sync is configured). */
    DOIP_BEGIN_CRITICAL_SECTION(); /* protects DoIP_LocalAddrAssignedCounter */
    DoIP_LocalAddrAssignedCounter++;
    DOIP_END_CRITICAL_SECTION();
#endif /* DOIP_GID_SYNC_ENABLED == STD_ON */
  }
  /* #110 Ignore assignment state change otherwise. */
  else
  {
    /* nothing to do here */
  }
} /* DoIP_Con_HandleLocalIpAddrAssignmentChg() */

#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Con_RelAllIpAddrAssign()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_RelAllIpAddrAssign(void)                                                     /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_LocalAddrIterType localAddrIdx;
  DoIP_IpAddrAssignmentIterType ipAddrAssignmentIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all local IP addresses. */
  for ( localAddrIdx = 0u;
        localAddrIdx < DoIP_GetSizeOfLocalAddr();
        localAddrIdx++ )
  {
    /* #20 Iterate over all related IP address assignments. */
    for ( ipAddrAssignmentIdx = DoIP_GetIpAddrAssignmentStartIdxOfLocalAddr(localAddrIdx);
          ipAddrAssignmentIdx < DoIP_GetIpAddrAssignmentEndIdxOfLocalAddr(localAddrIdx);
          ipAddrAssignmentIdx++ )
    {
# if ( DOIP_CONTROL_IP_ASSIGNMENT == STD_ON )
      /* #30 Release IP address assignment if IP address assignment control is enabled (if configured). */
      if ( DoIP_IsControlIpAssignmentOfIpAddrAssignment(ipAddrAssignmentIdx) )
      {
        /* May be called multiple times in case multiple IP address assignments are controlled by DoIP. */
        DoIP_Con_RelIpAddrAssign((DoIP_SizeOfLocalAddrType)localAddrIdx);
      }
# endif /* DOIP_CONTROL_IP_ASSIGNMENT == STD_ON */

      /* #40 Reset IP address assignment request state. */
      DoIP_SetIpAddrReqStateOfIpAddrAssignmentDyn(ipAddrAssignmentIdx, DOIP_IP_ADDR_REQ_STATE_NONE);                   /* SBSW_DOIP_CSL02_CSL03 */
    }
  }
} /* DoIP_Con_RelAllIpAddrAssign() */
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */

#if ( (DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON) && (DOIP_CONTROL_IP_ASSIGNMENT == STD_ON) )
/**********************************************************************************************************************
 *  DoIP_Con_RelIpAddrAssign()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_RelIpAddrAssign(                                                             /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfLocalAddrType LocalAddrIdx)                                                                               /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfConnectionType connectionIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get first local address related connection. */
  connectionIdx = DoIP_GetConnectionInd(DoIP_GetConnectionIndStartIdxOfLocalAddr(LocalAddrIdx));

  /* #20 Release IP address on related connection. */
  /* Ignore return value of function since there is nothing DoIP can do if release fails (retry doesn't make sense). */
  (void)SoAd_ReleaseIpAddrAssignment(DoIP_GetSoConIdOfConnectionDyn(connectionIdx));
} /* DoIP_Con_RelIpAddrAssign() */
#endif /* (DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON) && (DOIP_CONTROL_IP_ASSIGNMENT == STD_ON) */

/**********************************************************************************************************************
 *  DoIP_Con_GetConnectionIdxBySoConId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Con_GetConnectionIdxBySoConId(                                         /* INTERNAL_NOTE_SBSW_OK */
  SoAd_SoConIdType SoConId,                                                                                            /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  P2VAR(DoIP_SizeOfConnectionType, AUTOMATIC, DOIP_APPL_VAR) ConnectionIdx)                                            /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  DoIP_ConnectionIterType connectionIdx;

  /* ----- Implementation ----------------------------------------------- */
  *ConnectionIdx = DoIP_GetSizeOfConnection();                                                                         /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */

  if ( SoConId != SOAD_INV_SO_CON_ID )
  {
    for ( connectionIdx = 0u;
          connectionIdx < DoIP_GetSizeOfConnection();
          connectionIdx++ )
    {
      /* #10 Look up connection index for current socket connection identifier. */
      if ( SoConId == DoIP_GetSoConIdOfConnectionDyn(connectionIdx) )
      {
        *ConnectionIdx = (DoIP_SizeOfConnectionType)connectionIdx;                                                     /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
        retVal = E_OK;
        break;
      }
    }
  }

  return retVal;
} /* DoIP_Con_GetConnectionIdxBySoConId() */

/**********************************************************************************************************************
 *  DoIP_Con_HandleSoConStates()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleSoConStates(void)                                                      /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_ConnectionIterType connectionIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all connections. */
  for ( connectionIdx = 0u;
        connectionIdx < DoIP_GetSizeOfConnection();
        connectionIdx++ )
  {
    /* #20 Check if socket connection state is offline and IP address is assigned to open connection. */
    if ( (DoIP_GetSoConStateOfConnectionDyn(connectionIdx) == SOAD_SOCON_OFFLINE) &&
         (DoIP_GetIpAddrStateOfConnectionDyn(connectionIdx) == SOAD_IPADDR_STATE_ASSIGNED) )
    {
      /* #30 Set state to reconnect to avoid multiple open requests. */
      DoIP_SetSoConStateOfConnectionDyn(connectionIdx, SOAD_SOCON_RECONNECT);                                          /* SBSW_DOIP_CSL02 */

      /* #40 Request to open socket connection. */
      (void)SoAd_OpenSoCon(DoIP_GetSoConIdOfConnectionDyn(connectionIdx));
    }
  }
} /* DoIP_Con_HandleSoConStates() */

#if ( (DOIP_CONTROL_IP_ASSIGNMENT == STD_ON) || (DOIP_IPADDR_ASSIGN_DHCP == STD_ON) )
/**********************************************************************************************************************
 *  DoIP_Con_HandleIpAddrAssignment()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleIpAddrAssignment(void)                                                 /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_LocalAddrIterType localAddrIdx;
  DoIP_IpAddrAssignmentIterType ipAddrAssignmentIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all local addresses. */
  for ( localAddrIdx = 0u;
        localAddrIdx < DoIP_GetSizeOfLocalAddr();
        localAddrIdx++ )
  {
    /* #20 Iterate over all IP address assignments of the local address. */
    for ( ipAddrAssignmentIdx = DoIP_GetIpAddrAssignmentStartIdxOfLocalAddr(localAddrIdx);
          ipAddrAssignmentIdx < DoIP_GetIpAddrAssignmentEndIdxOfLocalAddr(localAddrIdx);
          ipAddrAssignmentIdx++ )
    {
      /* #30 Check if IP address assignment is not yet requested. */
      if ( DoIP_GetIpAddrReqStateOfIpAddrAssignmentDyn(ipAddrAssignmentIdx) == DOIP_IP_ADDR_REQ_STATE_NONE )
      {
        /* #40 Set IP address assignment to requested. */
        DoIP_SetIpAddrReqStateOfIpAddrAssignmentDyn(ipAddrAssignmentIdx, DOIP_IP_ADDR_REQ_STATE_REQUESTED);            /* SBSW_DOIP_CSL02_CSL03_CSL01 */

# if ( DOIP_IPADDR_ASSIGN_DHCP == STD_ON )
        /* #50 Overwrite DHCP hostname option (if configured). */
        if ( DoIP_GetAssignmentTypeOfIpAddrAssignment(ipAddrAssignmentIdx) == DOIP_IPADDR_ASSIGN_TYPE_DHCP )
        {
          DoIP_Con_SetDhcpHostname((DoIP_SizeOfLocalAddrType)localAddrIdx);
        }
# endif /* DOIP_IPADDR_ASSIGN_DHCP == STD_ON */

# if ( DOIP_CONTROL_IP_ASSIGNMENT == STD_ON )
        /* #60 Check if IP address assignment control is enabled (if configured). */
        if ( DoIP_IsControlIpAssignmentOfIpAddrAssignment(ipAddrAssignmentIdx) )
        {
          /* #70 Request IP address assignment. */
          Std_ReturnType retVal = DoIP_Con_ReqIpAddrAssign((DoIP_SizeOfLocalAddrType)localAddrIdx,
            (DoIP_SizeOfIpAddrAssignmentType)ipAddrAssignmentIdx);

          /* #80 Reset IP address assignment request state if request failed. */
          if ( retVal == E_NOT_OK )
          {
            DoIP_SetIpAddrReqStateOfIpAddrAssignmentDyn(ipAddrAssignmentIdx, DOIP_IP_ADDR_REQ_STATE_NONE);             /* SBSW_DOIP_CSL02_CSL03_CSL01 */
          }
        }
# endif /* DOIP_CONTROL_IP_ASSIGNMENT == STD_ON */
      }
    }
  }
} /* DoIP_Con_HandleIpAddrAssignment() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DOIP_CONTROL_IP_ASSIGNMENT == STD_ON) || (DOIP_IPADDR_ASSIGN_DHCP == STD_ON) */

#if ( DOIP_CONTROL_IP_ASSIGNMENT == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Con_ReqIpAddrAssign()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Con_ReqIpAddrAssign(                                                   /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfLocalAddrType LocalAddrIdx,                                                                               /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfIpAddrAssignmentType IpAddrAssignmentIdx)                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  DoIP_SizeOfConnectionType connectionIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get first connection related to local address. */
  connectionIdx = DoIP_GetConnectionInd(DoIP_GetConnectionIndStartIdxOfLocalAddr(LocalAddrIdx));

  /* #20 Request IP address assignment on the connection. */
  switch(DoIP_GetAssignmentTypeOfIpAddrAssignment(IpAddrAssignmentIdx))
  {
# if ( DOIP_IPADDR_ASSIGN_STATIC == STD_ON )
    case DOIP_IPADDR_ASSIGN_TYPE_STATIC:
    {
      SoAd_SockAddrInetXType localIpAddr = { SOAD_AF_INVALID, 0u, { 0u } };
      SoAd_SockAddrInetXType defaultRouter = { SOAD_AF_INVALID, 0u, { 0u } };

      localIpAddr.domain = DoIP_GetDomainTypeOfLocalAddr(LocalAddrIdx);
      defaultRouter.domain = DoIP_GetDomainTypeOfLocalAddr(LocalAddrIdx);

      /* PRQA S 0310 3 */ /* MD_DoIP_11.4 */
      retVal = SoAd_RequestIpAddrAssignment(DoIP_GetSoConIdOfConnectionDyn(connectionIdx),                             /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
        SOAD_IPADDR_ASSIGNMENT_STATIC, DOIP_A_P2VAR(SoAd_SockAddrType)&localIpAddr, 0u,
        DOIP_A_P2VAR(SoAd_SockAddrType)&defaultRouter);
      break;
    }
# endif /* DOIP_IPADDR_ASSIGN_STATIC == STD_ON */
# if ( DOIP_IPADDR_ASSIGN_LINKLOCAL_DOIP == STD_ON )
    case DOIP_IPADDR_ASSIGN_TYPE_LINKLOCAL_DOIP:
    {
      retVal = SoAd_RequestIpAddrAssignment(DoIP_GetSoConIdOfConnectionDyn(connectionIdx),                             /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        SOAD_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP, NULL_PTR, 0u, NULL_PTR);
      break;
    }
# endif /* DOIP_IPADDR_ASSIGN_LINKLOCAL_DOIP == STD_ON */
# if ( DOIP_IPADDR_ASSIGN_LINKLOCAL == STD_ON )
    case DOIP_IPADDR_ASSIGN_TYPE_LINKLOCAL:
    {
      retVal = SoAd_RequestIpAddrAssignment(DoIP_GetSoConIdOfConnectionDyn(connectionIdx),                             /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        SOAD_IPADDR_ASSIGNMENT_LINKLOCAL, NULL_PTR, 0u, NULL_PTR);
      break;
    }
# endif /* DOIP_IPADDR_ASSIGN_LINKLOCAL == STD_ON */
# if ( DOIP_IPADDR_ASSIGN_DHCP == STD_ON )
    case DOIP_IPADDR_ASSIGN_TYPE_DHCP:
    {
      retVal = SoAd_RequestIpAddrAssignment(DoIP_GetSoConIdOfConnectionDyn(connectionIdx),                             /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        SOAD_IPADDR_ASSIGNMENT_DHCP, NULL_PTR, 0u, NULL_PTR);
      break;
    }
# endif /* DOIP_IPADDR_ASSIGN_DHCP == STD_ON */
    default: /* COV_DOIP_DEFAULT_CASE */
    {
      /* nothing to do here */
      break;
    }
  }

  return retVal;
} /* DoIP_Con_ReqIpAddrAssign() */
#endif /* DOIP_CONTROL_IP_ASSIGNMENT == STD_ON */

#if ( DOIP_IPADDR_ASSIGN_DHCP == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Con_SetDhcpHostname()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_SetDhcpHostname(                                                             /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfLocalAddrType LocalAddrIdx)                                                                               /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get first connection related to local address. */
  const DoIP_SizeOfConnectionType connectionIdx = DoIP_GetConnectionInd(
    DoIP_GetConnectionIndStartIdxOfLocalAddr(LocalAddrIdx));

# if ( DOIP_DHCP_OPTION_VIN_USE_ENABLED == STD_ON )
  /* #20 Create hostname string with VIN (if configured). */
  /* PRQA S 0686 3 */ /* MD_DoIP_0686 */
  const uint8 hostNameSize = DOIP_HOST_NAME_VIN_SIZE;
  /* PRQA S 4414 1 */ /* MD_DoIP_ImplicitCharCast */
  uint8 hostName[DOIP_HOST_NAME_VIN_SIZE] = { 'D', 'o', 'I', 'P', '-', 'V', 'I', 'N' };

  if ( DoIP_CallGetVinDirect(&hostName[DOIP_HOST_NAME_VIN_PREFIX_SIZE]) != E_OK )                                      /* SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_FORWARD */
  {
    /* #30 Append VIN invalid pattern if VIN could not be retrieved from user. */
    uint8_least hostNameIdx;

    for ( hostNameIdx = (uint8)(DOIP_HOST_NAME_VIN_PREFIX_SIZE);
          hostNameIdx < DOIP_HOST_NAME_VIN_SIZE;
          hostNameIdx++ )
    {
      hostName[hostNameIdx] = DOIP_VIN_INV_PATTERN;                                                                    /* SBSW_DOIP_ARRAY_WRITE */
    }
  }
# else
  /* #40 Create minimum hostname string (otherwise). */
  const uint8 hostNameSize = DOIP_HOST_NAME_MIN_SIZE;
  /* PRQA S 4414 1 */ /* MD_DoIP_ImplicitCharCast */
  const uint8 hostName[DOIP_HOST_NAME_MIN_SIZE] = { 'D', 'o', 'I', 'P', '-' };
# endif /* DOIP_DHCP_OPTION_VIN_USE_ENABLED == STD_ON */

  /* #50 Overwrite DHCP hostname option on first related connection. */
  /* There is no handling specified in case hostname option could not be set. */
  (void)SoAd_WriteDhcpHostNameOption(DoIP_GetSoConIdOfConnectionDyn(connectionIdx), hostNameSize, hostName);           /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
} /* DoIP_Con_SetDhcpHostname() */
#endif /* DOIP_IPADDR_ASSIGN_DHCP == STD_ON */

#if ( DOIP_GID_SYNC_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Con_HandleGidSync()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleGidSync(void)                                                          /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if GID is out of sync. */
  if ( DoIP_GidInSync != TRUE )
  {
    /* #20 Trigger GID sync if at least one IP address is assigned. */
    if ( DoIP_LocalAddrAssignedCounter > 0u )
    {
      if ( DoIP_CallTriggerGidSyncDirect() == E_OK )                                                                   /* SBSW_DOIP_FUNCTION_POINTER_CALL */
      {
        DoIP_GidInSync = TRUE;
      }
    }
  }
} /* DoIP_Con_HandleGidSync() */
#endif /* DOIP_GID_SYNC_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_Con_HandleActLineStates()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleActLineStates(void)                                                    /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle activation line state active. */
#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
  if ( (DoIP_ActivationLineState == DOIP_ACTIVATION_LINE_ACTIVE) && (DoIP_ActivationLineInactiveRequest == FALSE) )
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */
  {
    DoIP_Con_HandleActLineStateActive();
  }
#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
  /* #20 Handle activation line state inactive. */
  else
  {
    DoIP_Con_HandleActLineStateInactive();
  }
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */
} /* DoIP_Con_HandleActLineStates() */

/**********************************************************************************************************************
 *  DoIP_Con_HandleActLineStateActive()
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
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleActLineStateActive(void)                                               /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Implementation ----------------------------------------------- */
#if ( (DOIP_CONTROL_IP_ASSIGNMENT == STD_ON) || (DOIP_IPADDR_ASSIGN_DHCP == STD_ON) )
  /* #10 Handle IP address assignments (if enabled). */
  DoIP_Con_HandleIpAddrAssignment();
#endif /* (DOIP_CONTROL_IP_ASSIGNMENT == STD_ON) || (DOIP_IPADDR_ASSIGN_DHCP == STD_ON) */

  /* #20 Handle SoCon states. */
  DoIP_Con_HandleSoConStates();

#if ( DOIP_GID_SYNC_ENABLED == STD_ON )
  /* #30 Handle GID sync state (if enabled). */
  DoIP_Con_HandleGidSync();
#endif /* DOIP_GID_SYNC_ENABLED == STD_ON */

  /* #40 Handle outstanding routing activation authentifications and confirmations. */
  DoIP_RxTcpRout_HandleRetryRoutingActivationAuthAndConf();

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
  /* #50 Handle outstanding vehicle announcement in DHCP IP Address List (if enabled). */
  DoIP_Dhcp_ProcessIpAddrListToTriggerVehAnnouncements();
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

  /* #60 Handle outstanding UDP actions. */
  DoIP_TxUdpList_HandleEntries();

#if ( (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) )
  /* #70 Copy outstanding user data (if enabled). */
  DoIP_RxTcpDiag_HandleRetryCopyVerifiedUserData();
#endif /* (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) */

  /* #80 Handle outstanding TCP actions. */
  DoIP_TxTcpQueue_HandleTransmit();

  /* #90 Handle timings. */
  DoIP_RxTcpRout_HandleAliveCheckTimeouts();
  DoIP_RxTcpRout_HandleInactivityTimeouts();
} /* DoIP_Con_HandleActLineStateActive() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Con_HandleActLineStateInactive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Con_HandleActLineStateInactive(void)                                             /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Release all IP address assignments if all socket connections could be closed. */
  if ( DoIP_Con_SoConCloseAll() == E_OK )
  {
    DoIP_Con_RelAllIpAddrAssign(); /* PRQA S 2987 */ /* MD_DoIP_Rule2.2_2987 */

    /* #20 Mark that activation line state has changed to inactive completely. */
    DoIP_ActivationLineInactiveRequest = FALSE;
  }
} /* DoIP_Con_HandleActLineStateInactive() */
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleRxIndication()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleRxIndication(                                                        /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr)                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint64 dataOffset = 0u;
  uint64 msgLength;
  uint32 srcHdrLen = 0u;
  uint8 reqCnt = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all DoIP messages in the UDP frame. */
  while ( PduInfoPtr->SduLength > dataOffset )
  {
    /* #20 Check if the DoIP message is valid. */
    if ( DoIP_RxUdp_CheckGenHdr(ConnectionIdx, PduInfoPtr, &srcHdrLen, (uint32)dataOffset) != E_OK )                   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    {
      break;
    }

    msgLength = (uint64)srcHdrLen + DOIP_GEN_HDR_LEN_BYTE;

    reqCnt++;
    /* #30 Check if the DoIP message count per UDP frame does exceeded the configured maximum. */
    if ( reqCnt > DOIP_MAX_UDP_REQ_PER_MSG )
    {
      /* #40 Check if current request is the last one and send general DoIP nack message for each DoIP request. */
      if ( msgLength == (PduInfoPtr->SduLength - dataOffset) )
      { /* It is the last DoIP request. */
        /* #50 Close socket after sending if there is no futher DoIP message and no configured UDP alive timeout. */
        if ( !DoIP_IsUdpAliveTimeoutOfLocalAddr(DoIP_GetLocalAddrIdxOfConnection(ConnectionIdx)) )
        {
          (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_OUT_OF_MEM, TRUE, NULL_PTR);  /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        }
        else
        {
          (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_OUT_OF_MEM, FALSE, NULL_PTR); /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        }
      }
      else
      { /* There are further DoIP requests. */
        (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_OUT_OF_MEM, FALSE, NULL_PTR);   /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      }
    }
    else
    {
      /* #60 Otherwise handle DoIP message. */
      DoIP_RxUdp_HandleRxIndicationMessageTypes(ConnectionIdx, PduInfoPtr, (uint32)dataOffset);                        /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */ /* INTERNAL_NOTE_SBSW_OK function is only called if pointer length is correct (DoIP_RxUdp_CheckGenHdr). */
    }

    dataOffset += msgLength;
  }
} /* DoIP_RxUdp_HandleRxIndication() */

/**********************************************************************************************************************
 *  DoIP_RxUdp_CheckGenHdr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxUdp_CheckGenHdr(                                                     /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(uint32, AUTOMATIC, DOIP_APPL_VAR) HdrLen,                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  uint32 DataOffset)                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 srcHdrVer;
  uint8 srcHdrInvVer;
  uint16 srcHdrType;
  uint32 hdrLen;
  uint32_least tmpDataOffset_least;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check message length and close socket connction if message is too short. */
  if ( (PduInfoPtr->SduLength - DataOffset) < DOIP_GEN_HDR_LEN_BYTE )
  {
    DoIP_Con_SoConClose(ConnectionIdx);
  }
  else
  {
    /* #20 Otherwise extract generic header data. */
    tmpDataOffset_least = (uint32_least)DataOffset;
    IPBASE_GET_UINT8 (PduInfoPtr->SduDataPtr, tmpDataOffset_least, srcHdrVer);                                         /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
    tmpDataOffset_least = (uint32_least)DataOffset + (uint32_least)1u;
    IPBASE_GET_UINT8 (PduInfoPtr->SduDataPtr, tmpDataOffset_least, srcHdrInvVer);                                      /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
    tmpDataOffset_least = (uint32_least)DataOffset + (uint32_least)2u;
    IPBASE_GET_UINT16(PduInfoPtr->SduDataPtr, tmpDataOffset_least, srcHdrType);                                        /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
    tmpDataOffset_least = (uint32_least)DataOffset + (uint32_least)4u;
    IPBASE_GET_UINT32(PduInfoPtr->SduDataPtr, tmpDataOffset_least, hdrLen);                                           /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
    *HdrLen = hdrLen;                                                                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */

    if ( (((uint8)srcHdrVer != DOIP_PROTOCOL_VERSION_2012) ||
          ((uint8)(~srcHdrInvVer) != DOIP_PROTOCOL_VERSION_2012)) &&
         (((uint8)srcHdrVer != DOIP_PROTOCOL_VERSION_DEFAULT) ||
          ((uint8)(~srcHdrInvVer) != DOIP_PROTOCOL_VERSION_DEFAULT) ||
          (srcHdrType < DOIP_HDR_TYPE_VEHICLE_IDENT_REQ) ||
          (srcHdrType > DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_VIN)) )
    {
      /* #30 Check header and send Nack for DoIP version missmatch. */
      (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_FORMAT, TRUE, NULL_PTR);          /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
    }
    else if ( ((uint64)hdrLen + DOIP_GEN_HDR_LEN_BYTE) > ((uint64)PduInfoPtr->SduLength - (uint64)DataOffset) )
    {
      /* #40 Check header and send Nack for DoIP for invalid header length. */
      (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, TRUE, NULL_PTR);         /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
    }
    else
    {
      retVal = E_OK;
    }
  }

  return retVal;
} /* DoIP_RxUdp_CheckGenHdr() */

/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleRxIndicationMessageTypes()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleRxIndicationMessageTypes(                                            /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  uint32 DataOffset)                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean closeSocket = FALSE;
  uint32 srcHdrLen;
  uint16 srcHdrType;
  uint32_least tmpDataOffset_least;

  /* ----- Implementation ----------------------------------------------- */
  tmpDataOffset_least = (uint32_least)DataOffset + (uint32_least)2u;
  IPBASE_GET_UINT16(PduInfoPtr->SduDataPtr, tmpDataOffset_least, srcHdrType);                                          /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  tmpDataOffset_least = (uint32_least)DataOffset + (uint32_least)4u;
  IPBASE_GET_UINT32(PduInfoPtr->SduDataPtr, tmpDataOffset_least, srcHdrLen);                                           /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  /* #10 Close socket after sending if there is no futher DoIP message and no configured UDP alive timeout. */
  if ( (srcHdrLen + DOIP_GEN_HDR_LEN_BYTE) == (PduInfoPtr->SduLength - DataOffset) )
  {
    if ( !DoIP_IsUdpAliveTimeoutOfLocalAddr(DoIP_GetLocalAddrIdxOfConnection(ConnectionIdx)) )
    {
      closeSocket = TRUE;
    }
  }

  /* #20 Handle message depending on there message type. */
  switch(srcHdrType)
  {
    case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ:
    {
      DoIP_RxUdp_HandleVehicleIdentReq(ConnectionIdx, PduInfoPtr, DataOffset, closeSocket);                            /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      break;
    }
    case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_VIN:
    {
      DoIP_RxUdp_HandleVehicleIdentReqVin(ConnectionIdx, PduInfoPtr, DataOffset, closeSocket);                         /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      break;
    }
#if ( DOIP_VEHICLE_IDENT_EID_SUPPORT == STD_ON )
    case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_EID:
    {
      DoIP_RxUdp_HandleVehicleIdentReqEid(ConnectionIdx, PduInfoPtr, DataOffset, closeSocket);                         /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      break;
    }
#endif /* DOIP_VEHICLE_IDENT_EID_SUPPORT == STD_ON */
    case DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_REQ:
    {
      DoIP_RxUdp_HandleDiagPowerModeInfoReq(ConnectionIdx, PduInfoPtr, DataOffset, closeSocket);                       /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      break;
    }
#if ( DOIP_ENTITY_STATE_SUPPORT == STD_ON )
    case DOIP_HDR_TYPE_ENTITY_STATE_REQ:
    {
      DoIP_RxUdp_HandleEntityStateReq(ConnectionIdx, PduInfoPtr, DataOffset, closeSocket);                             /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      break;
    }
#endif /* DOIP_ENTITY_STATE_SUPPORT == STD_ON */
    case DOIP_HDR_TYPE_GEN_NACK:
    case DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT:
    case DOIP_HDR_TYPE_ROUT_ACTIV_REQ:
    case DOIP_HDR_TYPE_ROUT_ACTIV_RES:
    case DOIP_HDR_TYPE_ALIVE_CHECK_REQ:
    case DOIP_HDR_TYPE_ALIVE_CHECK_RES:
    case DOIP_HDR_TYPE_ENTITY_STATE_RES:
    case DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_RES:
    case DOIP_HDR_TYPE_DIAG_REQ:
    case DOIP_HDR_TYPE_DIAG_ACK:
    case DOIP_HDR_TYPE_DIAG_NACK:
    { /* close socket if not relevant header type is received */
      DoIP_Con_SoConClose(ConnectionIdx);
      break;
    }
    default:
    { /* TxNack: unknown header type */
      DoIP_RxUdp_HandleUnknownHdrType(ConnectionIdx, PduInfoPtr, DataOffset, closeSocket);                             /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      break;
    }
  }
} /* DoIP_RxUdp_HandleRxIndicationMessageTypes() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleVehicleIdentReq()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleVehicleIdentReq(                                                     /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  uint32 DataOffset,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  boolean CloseSocket)                                                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 srcHdrLen;
  uint32_least tmpDataOffset_least;

  /* ----- Implementation ----------------------------------------------- */
  tmpDataOffset_least = (uint32_least)DataOffset + (uint32_least)4u;
  IPBASE_GET_UINT32(PduInfoPtr->SduDataPtr, tmpDataOffset_least, srcHdrLen);                                           /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  if ( srcHdrLen > DOIP_MAX_REQUEST_BYTES )
  {
    /* #10 Send Nack if max message length exceeded. */
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, CloseSocket, NULL_PTR);    /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  else if ( srcHdrLen != 0u )
  {
    /* #20 Send Nack if header length check failed. */
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, CloseSocket, NULL_PTR);    /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  else
  {
    /* #30 Otherwise send vehicle identification response. */
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT, DOIP_IDENT_RES_NUM, CloseSocket,      /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      NULL_PTR);
  }
} /* DoIP_RxUdp_HandleVehicleIdentReq() */

/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleVehicleIdentReqVin()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleVehicleIdentReqVin(                                                  /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  uint32 DataOffset,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  boolean CloseSocket)                                                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 srcHdrLen;
  uint32_least tmpDataOffset_least;

  /* ----- Implementation ----------------------------------------------- */
  tmpDataOffset_least = (uint32_least)DataOffset + (uint32_least)4u;
  IPBASE_GET_UINT32(PduInfoPtr->SduDataPtr, tmpDataOffset_least, srcHdrLen);                                           /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  /* #10 Send Nack if max message length exceeded. */
  if ( srcHdrLen > DOIP_MAX_REQUEST_BYTES )
  {
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, CloseSocket, NULL_PTR);    /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  /* #20 Send Nack if header length check failed otherwise. */
  else if ( srcHdrLen != DOIP_VIN_LEN_BYTE )
  {
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, CloseSocket, NULL_PTR);    /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  /* #30 Assume that request is valid otherwise. */
  else
  {
    boolean identOk = TRUE;
    uint8_least identIdx;
    uint32_least tmpIdentIdx;
    uint8 vinBuffer[DOIP_VIN_LEN_BYTE] = { 0u };

    /* #40 Compare VIN to retrieved VIN if VIN could successfully retrieved. */
    if ( DoIP_CallGetVinDirect(vinBuffer) == E_OK )                                                                    /* SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_FORWARD */
    {
      for ( identIdx = 0u;
            identIdx < DOIP_VIN_LEN_BYTE;
            identIdx++ )
      {
        tmpIdentIdx = (uint32_least)DataOffset + (uint32_least)DOIP_GEN_HDR_LEN_BYTE + (uint32_least)identIdx;
        if ( PduInfoPtr->SduDataPtr[tmpIdentIdx] != vinBuffer[identIdx] )
        {
          identOk = FALSE;
          break;
        }
      }
    }
    /* #50 Compare VIN to invalid pattern otherwise. */
    else
    {
      for ( identIdx = 0u;
            identIdx < DOIP_VIN_LEN_BYTE;
            identIdx++ )
      {
        tmpIdentIdx = (uint32_least)DataOffset + (uint32_least)DOIP_GEN_HDR_LEN_BYTE + (uint32_least)identIdx;
        if ( PduInfoPtr->SduDataPtr[tmpIdentIdx] != DOIP_VIN_INV_PATTERN )
        {
          identOk = FALSE;
          break;
        }
      }
    }

    /* #60 Send vehicle identification response if VIN check passed. */
    if ( identOk == TRUE )
    {
      (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT, DOIP_IDENT_RES_NUM, CloseSocket,    /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        NULL_PTR);
    }
    /* #70 Close socket if requested otherwise. */
    else
    {
      DoIP_TxUdpList_CloseSocket(ConnectionIdx, CloseSocket);
    }
  }
} /* DoIP_RxUdp_HandleVehicleIdentReqVin() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if ( DOIP_VEHICLE_IDENT_EID_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleVehicleIdentReqEid()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleVehicleIdentReqEid(                                                  /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  uint32 DataOffset,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  boolean CloseSocket)                                                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 srcHdrLen;
  uint32_least tmpDataOffset_least;

  /* ----- Implementation ----------------------------------------------- */
  tmpDataOffset_least = (uint32_least)DataOffset + (uint32_least)4u;
  IPBASE_GET_UINT32(PduInfoPtr->SduDataPtr, tmpDataOffset_least, srcHdrLen);                                           /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  /* #10 Send Nack if max message length exceeded. */
  if ( srcHdrLen > DOIP_MAX_REQUEST_BYTES )
  {
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, CloseSocket, NULL_PTR);    /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  /* #20 Send Nack if header length check failed otherwise. */
  else if ( srcHdrLen != DOIP_PHYS_ADDR_LEN )
  {
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, CloseSocket, NULL_PTR);    /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  /* #30 Assume that request is valid otherwise. */
  else
  {
    boolean identOk = TRUE;
    uint8_least identIdx;
    uint32_least tmpIdentIdx;

# if ( DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON )
    uint8 physAddrBuf[DOIP_PHYS_ADDR_LEN];

    /* #40 Get MAC address if MAC address is used for identification (if enabled). */
    if ( SoAd_GetPhysAddr(DoIP_GetSoConIdOfConnectionDyn(ConnectionIdx), &physAddrBuf[0u]) == E_OK )                   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    {
      /* #50 Compare retrieved MAC address with received data. */
      for ( identIdx = 0u;
            identIdx < DOIP_PHYS_ADDR_LEN;
            identIdx++ )
      {
        tmpIdentIdx = (uint32_least)DataOffset + (uint32_least)DOIP_GEN_HDR_LEN_BYTE + (uint32_least)identIdx;
        if ( PduInfoPtr->SduDataPtr[tmpIdentIdx] != physAddrBuf[identIdx] )
        {
          identOk = FALSE;
          break;
        }
      }
    }
    else
    {
      identOk = FALSE;
    }
# else
    /* #60 Compare configured EID with received data (otherwise). */
    for ( identIdx = 0u;
          identIdx < DOIP_PHYS_ADDR_LEN;
          identIdx++ )
    {
      tmpIdentIdx = (uint32_least)DataOffset + (uint32_least)DOIP_GEN_HDR_LEN_BYTE + (uint32_least)identIdx;
      if ( PduInfoPtr->SduDataPtr[tmpIdentIdx] != DoIP_GetEId(identIdx) )
      {
        identOk = FALSE;
        break;
      }
    }
# endif /* DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON */

    /* #70 Send vehicle identification response if EID check passed. */
    if ( identOk == TRUE )
    {
      (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT, DOIP_IDENT_RES_NUM, CloseSocket,    /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        NULL_PTR);
    }
    /* #80 Close socket if requested otherwise. */
    else
    {
      DoIP_TxUdpList_CloseSocket(ConnectionIdx, CloseSocket);
    }
  }
} /* DoIP_RxUdp_HandleVehicleIdentReqEid() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* DOIP_VEHICLE_IDENT_EID_SUPPORT == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleDiagPowerModeInfoReq()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleDiagPowerModeInfoReq(                                                /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  uint32 DataOffset,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  boolean CloseSocket)                                                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 srcHdrLen;
  uint32_least tmpDataOffset_least;

  /* ----- Implementation ----------------------------------------------- */
  tmpDataOffset_least = (uint32_least)DataOffset + (uint32_least)4u;
  IPBASE_GET_UINT32(PduInfoPtr->SduDataPtr, tmpDataOffset_least, srcHdrLen);                                           /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  if ( srcHdrLen > DOIP_MAX_REQUEST_BYTES )
  {
    /* #10 Send Nack if max message length exceeded. */
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, CloseSocket, NULL_PTR);    /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  else if ( srcHdrLen != 0u )
  {
    /* #20 Send Nack if header length check failed. */
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, CloseSocket, NULL_PTR);    /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  else
  {
    DoIP_PowerModeType diagPowerMode = DOIP_POWER_MODE_NOT_SUPPORTED;

    /* #30 Otherwise try to retrieve power mode. */
    if ( DoIP_CallPowerModeDirect(&diagPowerMode) == E_NOT_OK )                                                        /* SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_FORWARD */
    {
      diagPowerMode = DOIP_POWER_MODE_NOT_READY;
    }
    /* #40 Send diagnostic power mode response. */
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_RES, diagPowerMode, CloseSocket,       /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      NULL_PTR);
  }
} /* DoIP_RxUdp_HandleDiagPowerModeInfoReq() */

#if ( DOIP_ENTITY_STATE_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleEntityStateReq()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleEntityStateReq(                                                      /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  uint32 DataOffset,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  boolean CloseSocket)                                                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 srcHdrLen;
  uint32_least tmpDataOffset_least;

  /* ----- Implementation ----------------------------------------------- */
  tmpDataOffset_least = (uint32_least)DataOffset + (uint32_least)4u;
  IPBASE_GET_UINT32(PduInfoPtr->SduDataPtr, tmpDataOffset_least, srcHdrLen);                                           /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  if ( srcHdrLen > DOIP_MAX_REQUEST_BYTES )
  {
    /* #10 Send Nack if max message length exceeded. */
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, CloseSocket, NULL_PTR);    /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  else if ( srcHdrLen != 0u )
  {
    /* #20 Send Nack if header length check failed. */
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, CloseSocket, NULL_PTR);    /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  else
  {
    /* #30 Otherwise send entity state response. */
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_ENTITY_STATE_RES, DOIP_UNUSED_PARAM, CloseSocket,           /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      NULL_PTR);
  }
} /* DoIP_RxUdp_HandleEntityStateReq() */
#endif /* DOIP_ENTITY_STATE_SUPPORT == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxUdp_HandleUnknownHdrType()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxUdp_HandleUnknownHdrType(                                                      /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  uint32 DataOffset,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  boolean CloseSocket)                                                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
  /* ----- Local Variables ---------------------------------------------- */
  uint32 srcHdrLen;
  uint16 srcHdrType;
  PduInfoType rxUserData;
  uint32_least tmpDataOffset_least;

  /* ----- Implementation ----------------------------------------------- */
  tmpDataOffset_least = (uint32_least)DataOffset + (uint32_least)2u;
  IPBASE_GET_UINT16(PduInfoPtr->SduDataPtr, tmpDataOffset_least, srcHdrType);                                          /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  tmpDataOffset_least = (uint32_least)DataOffset + (uint32_least)4u;
  IPBASE_GET_UINT32(PduInfoPtr->SduDataPtr, tmpDataOffset_least, srcHdrLen);                                           /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  rxUserData.SduLength = (PduLengthType)srcHdrLen;
  /* #10 Check header length and set payload data. */
  if ( srcHdrLen == 0u )
  {
    rxUserData.SduDataPtr = NULL_PTR;
  }
  else
  {
    rxUserData.SduDataPtr = &PduInfoPtr->SduDataPtr[DataOffset + DOIP_GEN_HDR_LEN_BYTE];
  }

  /* #20 Check if Tx buffer is available. */
  if ( DoIP_GetOemPayloadTypeUdpBufLen() == 0u )
  {
    uint16 txHdrType = DOIP_HDR_TYPE_INVALID;
    PduInfoType txUserData;

    txUserData.SduDataPtr = DoIP_GetAddrOemPayloadTypeUdpBuf(DOIP_GEN_HDR_LEN_BYTE);
    txUserData.SduLength = DOIP_OEM_PAYLOAD_TYPE_UDP_BUF_SIZE;

    /* #30 Call user callback to forward message to upper layer. */
    if ( DoIP_CallOemPayloadTypeDirect(srcHdrType, &rxUserData, DOIP_OEM_PAYLOAD_TYPE_FLAG_PROT_UDP, &txHdrType,       /* SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_AND_CONST_POINTER_FORWARD */
          &txUserData) == E_NOT_OK )
    {
      /* #40 Send Nack if forwarding failed. */
      (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_TYPE, CloseSocket, NULL_PTR);     /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
    }
    else
    {
      /* #50 Otherwise send response if Tx plausibility check passed. */
      if ( txHdrType != DOIP_HDR_TYPE_INVALID )
      {
        if ( txUserData.SduLength <= DOIP_OEM_PAYLOAD_TYPE_UDP_BUF_SIZE )
        {
          DoIP_SetOemPayloadTypeUdpBufLen((uint16)(txUserData.SduLength + DOIP_GEN_HDR_LEN_BYTE));                     /* SBSW_DOIP_OemPayloadType */
          (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_OEM_SPECIFIC, txHdrType, CloseSocket, NULL_PTR);      /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        }
      }
    }
  }
  else
  {
    /* #60 Otherwise send Nack. */
    (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_OUT_OF_MEM, CloseSocket, NULL_PTR); /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
#else
  /* #70 Send general Nack (if OEM payload type not enabled). */
  DOIP_DUMMY_STATEMENT(PduInfoPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  DOIP_DUMMY_STATEMENT(DataOffset); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

  (void)DoIP_TxUdp_Transmit(ConnectionIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_TYPE, CloseSocket, NULL_PTR);         /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */
} /* DoIP_RxUdp_HandleUnknownHdrType() */

/**********************************************************************************************************************
 *  DoIP_TxUdp_Transmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_Transmit(                                                        /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 HdrType,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  uint16 Param,                                                                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  boolean CloseSocket,                                                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  P2CONST(SoAd_SockAddrInetXType, AUTOMATIC, DOIP_APPL_VAR) RemoteAddress)                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  retVal = DoIP_TxUdp_TransmitImmediately(ConnectionIdx, HdrType, Param, CloseSocket);

  /* #10 Queue element if message could not send immediately. */
  if ( retVal == E_NOT_OK )
  {
    retVal = DoIP_TxUdp_TransmitDelayed(ConnectionIdx, HdrType, Param, CloseSocket, RemoteAddress);                    /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  }

  return retVal;
} /* DoIP_TxUdp_Transmit() */

/**********************************************************************************************************************
 *  DoIP_TxUdp_TransmitImmediately()
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
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_TransmitImmediately(                                             /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 HdrType,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  uint16 Param,                                                                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  boolean CloseSocket)                                                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to send messages (expect vehicle announcements) immediately. */
  if ( HdrType != DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT )
  {
    retVal = DoIP_TxUdp_SingleTransmit(ConnectionIdx, HdrType, Param);
  }

  /* #20 Check if message has been sent immediately. */
  if ( retVal == E_OK )
  {
    boolean otherEntryFound = FALSE;
    DoIP_TxUdpMgtListIterType txUdpMgtListIdx;

    /* #30 check if response is pending for this socket connection. */
    for ( txUdpMgtListIdx = 0u;
          txUdpMgtListIdx < DoIP_GetSizeOfTxUdpMgtList();
          txUdpMgtListIdx++ )
    {
      if ( ConnectionIdx == DoIP_GetConnectionIdxOfTxUdpMgtList(txUdpMgtListIdx) )
      { /* response pending */
        otherEntryFound = TRUE;
        break;
      }
    }

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
    /* #40 Check if OEM specific payload type buffer has to be released (if enabled). */
    if ( HdrType == DOIP_HDR_TYPE_OEM_SPECIFIC )
    {
      DoIP_SetOemPayloadTypeUdpBufLen(0u);                                                                             /* SBSW_DOIP_OemPayloadType */
    }
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

    if ( otherEntryFound == FALSE )
    {
      /* #50 Close socket connection directly if there is no pending response and a close socket is indicated. */
      if ( CloseSocket == TRUE )
      {
        DoIP_Con_SoConClose(ConnectionIdx);
      }
    }
    else
    {
      /* #60 Mark socket connection for closing if there are pending elements in the list. */
      DoIP_SetSoConClosingOfConnectionDyn(ConnectionIdx,                                                               /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
        (boolean)(DoIP_IsSoConClosingOfConnectionDyn(ConnectionIdx) || (CloseSocket == TRUE)));
    }
  }

  return retVal;
} /* DoIP_TxUdp_TransmitImmediately() */

/**********************************************************************************************************************
 *  DoIP_TxUdp_TransmitDelayed()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_TransmitDelayed(                                                 /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 HdrType,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  uint16 Param,                                                                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  boolean CloseSocket,                                                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  P2CONST(SoAd_SockAddrInetXType, AUTOMATIC, DOIP_APPL_VAR) RemoteAddress)                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  DoIP_TxUdpMgtListIterType txUdpMgtListIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to find an empty list element. */
  DOIP_BEGIN_CRITICAL_SECTION(); /* protects ConnectionIdxOfTxUdpMgtList */
  for ( txUdpMgtListIdx = 0u;
        txUdpMgtListIdx < DoIP_GetSizeOfTxUdpMgtList();
        txUdpMgtListIdx++ )
  {
    if ( DoIP_GetConnectionIdxOfTxUdpMgtList(txUdpMgtListIdx) == DoIP_GetSizeOfConnection() )
    {
      /* #20 Write element in Tx queue if an empty list element was found. */
      DoIP_SetConnectionIdxOfTxUdpMgtList(txUdpMgtListIdx, ConnectionIdx);                                             /* SBSW_DOIP_CSL01 */
      DoIP_SetHdrTypeOfTxUdpMgtList(txUdpMgtListIdx, HdrType);                                                         /* SBSW_DOIP_CSL01 */
      DoIP_SetRetryAttemptOfTxUdpMgtList(txUdpMgtListIdx, DOIP_UDP_MAX_RETRY_CNT);                                     /* SBSW_DOIP_CSL01 */

      if ( HdrType == DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT )
      {
        /* #30 Write vehicle announcment message specific parameters. */
        DoIP_TxUdp_TransmitDelayedSetVehAnnSpecParams(ConnectionIdx, txUdpMgtListIdx, RemoteAddress);                  /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      }

      /* number of announcements, nack code, power mode, OEM specific header type... */
      DoIP_SetParam2OfTxUdpMgtList(txUdpMgtListIdx, Param);                                                            /* SBSW_DOIP_CSL01 */

      DoIP_SetSoConClosingOfConnectionDyn(ConnectionIdx,                                                               /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
        (boolean)(DoIP_IsSoConClosingOfConnectionDyn(ConnectionIdx) || (CloseSocket == TRUE)));

      retVal = E_OK;
      break;
    }
  }
  DOIP_END_CRITICAL_SECTION();

  return retVal;
} /* DoIP_TxUdp_TransmitDelayed() */

/**********************************************************************************************************************
 *  DoIP_TxUdp_TransmitDelayedSetVehAnnSpecParams()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3206 4 */ /* MD_DoIP_3206 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxUdp_TransmitDelayedSetVehAnnSpecParams(                                        /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_TxUdpMgtListIterType TxUdpListIdx,                                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(SoAd_SockAddrInetXType, AUTOMATIC, DOIP_APPL_VAR) RemoteAddress)                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the timer for vehicle announcement messages. */
  DoIP_SetParam1OfTxUdpMgtList(TxUdpListIdx, DOIP_ANNOUNCE_WAIT);                                                      /* SBSW_DOIP_PARAM_VALID_INDEX */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
  /* #20 Check if the remote address is already known. */
  if ( RemoteAddress != NULL_PTR )
  {
    /* #30 Set the remote address for Tx, if it is already known. */
    DoIP_SetRemoteAddrOfTxUdpMgtList(TxUdpListIdx, *RemoteAddress);                                                    /* SBSW_DOIP_PARAM_VALID_INDEX */
  }
  else
  {
    /* #40 Set the remote address for Tx to general broadcast, if it is unknown. */
# if ( DOIP_IPV6_ENABLED == STD_ON )
#  if ( DOIP_IPV4_ENABLED == STD_ON )
    if ( DoIP_GetDomainTypeOfLocalAddr(DoIP_GetLocalAddrIdxOfConnection(ConnectionIdx)) == SOAD_AF_INET6 )
#  endif /* DOIP_IPV4_ENABLED == STD_ON */
    {
      DoIP_SetRemoteAddrOfTxUdpMgtList(TxUdpListIdx, DoIP_IpV6AddrMulticast);                                          /* SBSW_DOIP_PARAM_VALID_INDEX */
    }
#  if ( DOIP_IPV4_ENABLED == STD_ON )
    else
#  else
    DOIP_DUMMY_STATEMENT(ConnectionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* DOIP_IPV4_ENABLED == STD_ON */
# endif /* DOIP_IPV6_ENABLED == STD_ON */
# if ( DOIP_IPV4_ENABLED == STD_ON )
    {
      DoIP_SetRemoteAddrOfTxUdpMgtList(TxUdpListIdx, DoIP_IpV4AddrBroadcast);                                          /* SBSW_DOIP_PARAM_VALID_INDEX */
    }
#  if ( DOIP_IPV6_ENABLED == STD_OFF )
    DOIP_DUMMY_STATEMENT(ConnectionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* DOIP_IPV6_ENABLED == STD_OFF */
# endif /* DOIP_IPV4_ENABLED == STD_ON */
  }
#else
  DOIP_DUMMY_STATEMENT(ConnectionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  DOIP_DUMMY_STATEMENT(RemoteAddress); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */
} /* DoIP_TxUdp_TransmitDelayedSetVehAnnSpecParams() */

/**********************************************************************************************************************
 *  DoIP_TxUdp_SingleTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_SingleTransmit(                                                  /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 HdrType,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  uint16 Param)                                                                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle transmit depending on their header type. */
  switch(HdrType)
  {
    case DOIP_HDR_TYPE_GEN_NACK:
    {
      retVal = DoIP_TxUdp_SingleTransmitGenNack(ConnectionIdx, HdrType, (uint8)Param);
      break;
    }
    case DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT:
    {
      retVal = DoIP_TxUdp_SingleTransmitVehicleAnnounceAndIdentRes(ConnectionIdx);
      break;
    }
    case DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_RES:
    {
      retVal = DoIP_TxUdp_SingleTransmitDiagPowerModeInfoRes(ConnectionIdx, (uint8)Param);
      break;
    }
#if ( DOIP_ENTITY_STATE_SUPPORT == STD_ON )
    case DOIP_HDR_TYPE_ENTITY_STATE_RES:
    {
      retVal = DoIP_TxUdp_SingleTransmitEntityStateRes(ConnectionIdx);
      break;
    }
#endif /* DOIP_ENTITY_STATE_SUPPORT == STD_ON */
#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
    case DOIP_HDR_TYPE_OEM_SPECIFIC:
    {
      retVal = DoIP_TxUdp_SingleTransmitOemSpecific(ConnectionIdx, Param);
      break;
    }
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */
    default:
    { /* function does not support this header type */
      /* invalid state */
      /* nothing to do here */
      break;
    }
  }

  return retVal;
} /* DoIP_TxUdp_SingleTransmit() */

/**********************************************************************************************************************
 *  DoIP_TxUdp_SingleTransmitGenNack()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_SingleTransmitGenNack(                                           /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 HdrType,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  uint8 NackCode)                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  PduInfoType msgStruct;
  uint8 data[9u] = { 0u };

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare message. */
  msgStruct.SduLength  = DOIP_GEN_HDR_LEN_BYTE + 1u;
  msgStruct.SduDataPtr = &data[0u];
  msgStruct.SduDataPtr[0u] = DOIP_PROTOCOL_VERSION_2012;                                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[1u] = (uint8)(~(msgStruct.SduDataPtr[0u]));                                                     /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  DoIP_Util_PutUInt16(&msgStruct.SduDataPtr[2u], 0u, HdrType);                                                         /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  msgStruct.SduDataPtr[4u] = 0u;                                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[5u] = 0u;                                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[6u] = 0u;                                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[7u] = 1u;                                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[8u] = NackCode;                                                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
  /* #20 Increment the count of received UDP packets dropped by DoIP. */
  DoIP_Measure_IncDroppedPacketCounter(DOIP_MEASURE_DROPPED_PACKET_COUNTER_UDP, HdrType, NackCode);
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

  /* #30 Send message. */
  retVal = SoAd_IfTransmit(DoIP_GetSoAdTxPduIdOfConnection(ConnectionIdx), &msgStruct);                                /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  return retVal;
} /* DoIP_TxUdp_SingleTransmitGenNack() */

/**********************************************************************************************************************
 *  DoIP_TxUdp_SingleTransmitVehicleAnnounceAndIdentRes()
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
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_SingleTransmitVehicleAnnounceAndIdentRes(                        /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx)                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  PduInfoType msgStruct;
  uint16 ackIdx = DOIP_GEN_HDR_LEN_BYTE;
  uint8 data[DOIP_GEN_HDR_LEN_BYTE + DOIP_ACK_VEHICLE_IDENT_LEN_BYTE];
#if ( (DOIP_VIN_GID_SYNC == STD_ON) && (DOIP_GID_SYNC_ENABLED == STD_ON) )
  Std_ReturnType retValVin;
#endif /* (DOIP_VIN_GID_SYNC == STD_ON) && (DOIP_GID_SYNC_ENABLED == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write VIN, logical address, EID, GID and central security to message buffer. */
  msgStruct.SduDataPtr = &data[0u];
  msgStruct.SduLength = DOIP_GEN_HDR_LEN_BYTE + DOIP_ACK_VEHICLE_IDENT_LEN_BYTE;
  /* fill VIN */
#if ( (DOIP_VIN_GID_SYNC == STD_ON) && (DOIP_GID_SYNC_ENABLED == STD_ON) )
  retValVin = DoIP_Util_FillVin(&data[ackIdx]);                                                                        /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
#else
  (void)DoIP_Util_FillVin(&data[ackIdx]);                                                                              /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
#endif /* (DOIP_VIN_GID_SYNC == STD_ON) && (DOIP_GID_SYNC_ENABLED == STD_ON) */
  ackIdx += DOIP_VIN_LEN_BYTE;
  /* fill Addr */
  DoIP_Util_FillLocalLogAddr(&data[ackIdx]);                                                                           /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  ackIdx += 2u;
  /* fill EID */
  retVal |= DoIP_Util_FillEid(&data[ackIdx], ConnectionIdx); /* PRQA S 2986 */ /* MD_DoIP_Rule2.2_2985_2986 */         /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  ackIdx += DOIP_EID_LEN_BYTE;
  /* fill GID */
  retVal |= DoIP_Util_FillGid(&data[ackIdx], ConnectionIdx); /* PRQA S 2985, 2986 */ /* MD_DoIP_Rule2.2_2985_2986 */   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  ackIdx += DOIP_GID_LEN_BYTE;
  /* fill Central Security */
  DoIP_Util_FillFurtherAction(&data[ackIdx]);                                                                          /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */

#if ( DOIP_VIN_GID_SYNC == STD_ON )
  /* #20 Write VinGidSync to message buffer (if enabled). */
  ackIdx++;
# if ( DOIP_GID_SYNC_ENABLED == STD_ON )
  if ( (retValVin != E_OK) && (DoIP_GidInSync != TRUE) )
  { /* VIN/GID sync not succcessful */
    data[ackIdx] = 0x10u;                                                                                              /* SBSW_DOIP_ARRAY_WRITE */
  }
  else
# endif /* DOIP_GID_SYNC_ENABLED == STD_ON */
  {
    data[ackIdx] = 0x00u;                                                                                              /* SBSW_DOIP_ARRAY_WRITE */
  }
#endif /* DOIP_VIN_GID_SYNC == STD_ON */

#if ( DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON )
  /* #30 Check return values (if enabled). */
  if ( retVal == E_OK )
#endif /* DOIP_USE_MAC_ADDR_FOR_IDENT == STD_ON */
  {
    /* #40 Write generic header to messag buffer. */
    DoIP_Util_FillGenHdr(DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT, DOIP_ACK_VEHICLE_IDENT_LEN_BYTE, &data[0u]);              /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */

    /* #50 Send message. */
    /* PRQA S 2986 1 */ /* MD_DoIP_Rule2.2_2985_2986 */
    retVal |= SoAd_IfTransmit(DoIP_GetSoAdTxPduIdOfConnection(ConnectionIdx), &msgStruct);                             /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  }

  return retVal;
} /* DoIP_TxUdp_SingleTransmitVehicleAnnounceAndIdentRes() */

/**********************************************************************************************************************
 *  DoIP_TxUdp_SingleTransmitDiagPowerModeInfoRes()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_SingleTransmitDiagPowerModeInfoRes(                              /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint8 DiagPowerMode)                                                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint16 hdrType = DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_RES;
  PduInfoType msgStruct;
  uint8 data[9u] = { 0u };

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare message. */
  msgStruct.SduLength  = DOIP_GEN_HDR_LEN_BYTE + 1u;
  msgStruct.SduDataPtr = &data[0u];
  msgStruct.SduDataPtr[0u] = DOIP_PROTOCOL_VERSION_2012;                                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[1u] = (uint8)(~(msgStruct.SduDataPtr[0u]));                                                     /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  DoIP_Util_PutUInt16(&msgStruct.SduDataPtr[2u], 0u, hdrType);                                                         /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  msgStruct.SduDataPtr[4u] = 0x00u;                                                                                    /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[5u] = 0x00u;                                                                                    /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[6u] = 0x00u;                                                                                    /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[7u] = 0x01u;                                                                                    /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[8u] = DiagPowerMode;                                                                            /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */

  /* #20 Send message. */
  retVal = SoAd_IfTransmit(DoIP_GetSoAdTxPduIdOfConnection(ConnectionIdx), &msgStruct);                                /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  return retVal;
} /* DoIP_TxUdp_SingleTransmitDiagPowerModeInfoRes() */

#if ( DOIP_ENTITY_STATE_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  DoIP_TxUdp_SingleTransmitEntityStateRes()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_SingleTransmitEntityStateRes(                                    /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx)                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  PduInfoType msgStruct;
  DoIP_ConnectionIterType connectionIdx;
# if ( DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE == STD_ON )
  uint8 data[15u] = { 0u };
# else
  uint8 data[11u] = { 0u };
# endif /* DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare message. */
  msgStruct.SduLength  = DOIP_GEN_HDR_LEN_BYTE + DOIP_ACK_ENTITY_STATE_LEN_BYTE;
  msgStruct.SduDataPtr = &data[0u];
  msgStruct.SduDataPtr[0u]  = DOIP_PROTOCOL_VERSION_2012;                                                              /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[1u]  = (uint8)(~(msgStruct.SduDataPtr[0u]));                                                    /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  DoIP_Util_PutUInt16(&msgStruct.SduDataPtr[2u], 0u, DOIP_HDR_TYPE_ENTITY_STATE_RES);                                  /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  msgStruct.SduDataPtr[4u]  = 0x00u;                                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[5u]  = 0x00u;                                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[6u]  = 0x00u;                                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[7u]  = DOIP_ACK_ENTITY_STATE_LEN_BYTE;                                                          /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[8u]  = DOIP_NODE_TYPE;                                                                          /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[9u]  = DoIP_GetSizeOfConnectionTcp() - DoIP_GetSizeOfConnectionGroup(); /* remove n+1 socket */ /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msgStruct.SduDataPtr[10u] = 0u;                                                                                      /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */

  /* #20 Count open TCP_DATA socket (of all addr). */
  for ( connectionIdx = 0u;
        connectionIdx < DoIP_GetSizeOfConnectionTcp();
        connectionIdx++ )
  {
    if ( DoIP_GetSoConStateOfConnectionDyn(connectionIdx) == SOAD_SOCON_ONLINE )
    {
      msgStruct.SduDataPtr[10u]++;                                                                                     /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    }
  }

# if ( DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE == STD_ON )
  /* #30 Write max data size to message buffer (if enabled). */
  DoIP_Util_PutUInt32(&msgStruct.SduDataPtr[11u], 0u, DOIP_MAX_REQUEST_BYTES);                                         /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
# endif /* DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE == STD_ON */

  /* #40 Send message. */
  retVal = SoAd_IfTransmit(DoIP_GetSoAdTxPduIdOfConnection(ConnectionIdx), &msgStruct);                                /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  return retVal;
} /* DoIP_TxUdp_SingleTransmitEntityStateRes() */
#endif /* DOIP_ENTITY_STATE_SUPPORT == STD_ON */

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_TxUdp_SingleTransmitOemSpecific()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxUdp_SingleTransmitOemSpecific(                                       /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 HdrTypeOem)                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  PduInfoType msgStruct;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add the generic header in front of the user data. */
  DoIP_Util_FillGenHdr(HdrTypeOem, ((uint32)DoIP_GetOemPayloadTypeUdpBufLen() - (uint32)DOIP_GEN_HDR_LEN_BYTE),        /* SBSW_DOIP_OemPayloadTypeUdpBuf */
    DoIP_GetAddrOemPayloadTypeUdpBuf(0u));

  /* #20 Prepare message. */
  msgStruct.SduDataPtr = DoIP_GetAddrOemPayloadTypeUdpBuf(0u);
  msgStruct.SduLength = DoIP_GetOemPayloadTypeUdpBufLen();

  /* #30 Send message. */
  retVal = SoAd_IfTransmit(DoIP_GetSoAdTxPduIdOfConnection(ConnectionIdx), &msgStruct);                                /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  return retVal;
} /* DoIP_TxUdp_SingleTransmitOemSpecific() */
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_TxUdpList_CloseSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxUdpList_CloseSocket(                                                           /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  boolean CloseSocket)                                                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_TxUdpMgtListIterType txUdpMgtListIdx;
  boolean otherEntryFound = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket connection shall be closed already or is requested to be closed now. */
  if ( DoIP_IsSoConClosingOfConnectionDyn(ConnectionIdx) || CloseSocket )
  {
    /* #20 Indicate that socket shall be closed after all pending Tx UDP list entries has been sent. */
    DoIP_SetSoConClosingOfConnectionDyn(ConnectionIdx, TRUE);                                                          /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

    /* #30 Check if other Tx UDP list entries for socket connection exist. */
    for ( txUdpMgtListIdx = 0u;
          txUdpMgtListIdx < DoIP_GetSizeOfTxUdpMgtList();
          txUdpMgtListIdx++ )
    {
      if ( ConnectionIdx == DoIP_GetConnectionIdxOfTxUdpMgtList(txUdpMgtListIdx) )
      {
        otherEntryFound = TRUE;
        break;
      }
    }

    /* #40 Close socket connection if no other entry exists. */
    if ( otherEntryFound == FALSE )
    {
      DoIP_Con_SoConClose(ConnectionIdx);
    }
  }
} /* DoIP_TxUdpList_CloseSocket() */

/**********************************************************************************************************************
 *  DoIP_TxUdpList_HandleEntries()
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
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxUdpList_HandleEntries(void)                                                    /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_TxUdpMgtListIterType txUdpMgtListIdx;

  /* ----- Implementation ----------------------------------------------- */
  for ( txUdpMgtListIdx = 0u;
        txUdpMgtListIdx < DoIP_GetSizeOfTxUdpMgtList();
        txUdpMgtListIdx++ )
  {
    const DoIP_SizeOfConnectionType connectionIdx = DoIP_GetConnectionIdxOfTxUdpMgtList(txUdpMgtListIdx);              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX_INC_INV */

    /* #10 Check if there are pending UDP messages. */
    if ( connectionIdx != DoIP_GetSizeOfConnection() )
    {
      boolean releaseListEntry = FALSE;

      /* #20 Check socket connection state and header type. */
      if ( DoIP_GetSoConStateOfConnectionDyn(connectionIdx) == SOAD_SOCON_ONLINE )
      {
        if ( DoIP_GetHdrTypeOfTxUdpMgtList(txUdpMgtListIdx) == DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT )
        {
          /* #30 Handle vehicle announcement and vehicle identification response. */
          DoIP_TxUdpList_HandleEntriesVehicleAnnounceAndIdentRes((DoIP_SizeOfTxUdpMgtListType)txUdpMgtListIdx,
            connectionIdx);
        }
        else
        {
          /* #40 Handle entity state status response, diagnostic power mode response, generic negative acknowledge. */
          /* #50 Mark entry for release if list reach max size or entry could be send. */
          DoIP_TxUdpList_HandleEntriesOthers((DoIP_SizeOfTxUdpMgtListType)txUdpMgtListIdx, connectionIdx,              /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
            &releaseListEntry);
        }
      }
      else
      {
        /* #60 Mark entry for release if socket connection is not online anymore. */
        releaseListEntry = TRUE;
      }

      /* #70 Check if entry is marked for release. */
      if ( releaseListEntry == TRUE )
      {
#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
        /* #80 Check if OEM specific payload type buffer has to be released. */
        if ( DoIP_GetHdrTypeOfTxUdpMgtList(txUdpMgtListIdx) == DOIP_HDR_TYPE_OEM_SPECIFIC )
        {
          DoIP_SetOemPayloadTypeUdpBufLen(0u);                                                                         /* SBSW_DOIP_OemPayloadType */
        }
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

        /* #90 Release entry and close socket. */
        DoIP_SetConnectionIdxOfTxUdpMgtList(txUdpMgtListIdx, DoIP_GetSizeOfConnection());                              /* SBSW_DOIP_CSL01 */
        DoIP_TxUdpList_CloseSocket(connectionIdx, FALSE);
      }
    }
  }
} /* DoIP_TxUdpList_HandleEntries() */

/**********************************************************************************************************************
 *  DoIP_TxUdpList_HandleEntriesVehicleAnnounceAndIdentRes()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxUdpList_HandleEntriesVehicleAnnounceAndIdentRes(                               /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxUdpMgtListType TxUdpListIdx,                                                                            /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionType ConnectionIdx)                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
  SoAd_SockAddrInetXType remAddressToAssign;
  Std_ReturnType retVal = E_OK;
#else
  Std_ReturnType retVal;
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
  DoIP_DecParam1OfTxUdpMgtList(TxUdpListIdx);                                                                          /* SBSW_DOIP_PARAM_VALID_INDEX */

  /* #10 Try to send vehicle announcement if announce interval timer is expired. */
  if ( DoIP_GetParam1OfTxUdpMgtList(TxUdpListIdx) == 0u )
  {
#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
    /* #20 Set Remote Address if it is a vehicle announcement connection. */
    if ( (ConnectionIdx <  DoIP_GetSizeOfConnection()) &&
         (ConnectionIdx >= DOIP_CONNECTION_TCP_UDP_TOTAL) )
    {
      remAddressToAssign = DoIP_GetRemoteAddrOfTxUdpMgtList(TxUdpListIdx);

      /* PRQA S 0310 2 */ /* MD_DoIP_11.4 */
      retVal = SoAd_SetRemoteAddr(DoIP_GetSoConIdOfConnectionDyn(ConnectionIdx),                                       /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
        DOIP_A_P2VAR(SoAd_SockAddrType)&remAddressToAssign);
    }

    if ( retVal == E_OK )
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */
    {
      /* #30 Try to send out the vehicle announcement. */
      retVal = DoIP_TxUdp_SingleTransmit(ConnectionIdx, DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT, DOIP_UNUSED_PARAM);
    }

    if ( retVal != E_OK )
    {
      /* #40 Requeue entry if transmission failed. */
      DoIP_IncParam1OfTxUdpMgtList(TxUdpListIdx);                                                                      /* SBSW_DOIP_PARAM_VALID_INDEX */
      DoIP_DecRetryAttemptOfTxUdpMgtList(TxUdpListIdx);                                                                /* SBSW_DOIP_PARAM_VALID_INDEX */
      if ( DoIP_GetRetryAttemptOfTxUdpMgtList(TxUdpListIdx) == 0u )
      {
        /* #50 Release entry if retry failed several times. */
        DoIP_SetConnectionIdxOfTxUdpMgtList(TxUdpListIdx, DoIP_GetSizeOfConnection());                                 /* SBSW_DOIP_PARAM_VALID_INDEX */
      }
    }
    else
    {
      DoIP_DecParam2OfTxUdpMgtList(TxUdpListIdx);                                                                      /* SBSW_DOIP_PARAM_VALID_INDEX */
      if ( DoIP_GetParam2OfTxUdpMgtList(TxUdpListIdx) > 0u )
      {
        /* #60 Otherwise reload announce interval timer if further vehicle announcement messages are pending. */
        DoIP_SetParam1OfTxUdpMgtList(TxUdpListIdx, DOIP_ANNOUNCE_INTERVAL);                                            /* SBSW_DOIP_PARAM_VALID_INDEX */
      }
      else
      {
        /* #70 Release entry and close socket if all pending messages for this entry are sent. */
        DoIP_SetConnectionIdxOfTxUdpMgtList(TxUdpListIdx, DoIP_GetSizeOfConnection());                                 /* SBSW_DOIP_PARAM_VALID_INDEX */
        if ( ConnectionIdx < DOIP_CONNECTION_TCP_UDP_TOTAL )
        {
          DoIP_TxUdpList_CloseSocket(ConnectionIdx, FALSE);
        }
      }
    }
  }
} /* DoIP_TxUdpList_HandleEntriesVehicleAnnounceAndIdentRes() */

/**********************************************************************************************************************
 *  DoIP_TxUdpList_HandleEntriesOthers()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxUdpList_HandleEntriesOthers(                                                   /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxUdpMgtListType TxUdpListIdx,                                                                            /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(boolean, AUTOMATIC, DOIP_APPL_VAR) ReleaseListEntry)                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to send message. */
  if ( DoIP_TxUdp_SingleTransmit(ConnectionIdx, DoIP_GetHdrTypeOfTxUdpMgtList(TxUdpListIdx),
        DoIP_GetParam2OfTxUdpMgtList(TxUdpListIdx)) != E_OK )
  {
    DoIP_DecRetryAttemptOfTxUdpMgtList(TxUdpListIdx);                                                                  /* SBSW_DOIP_PARAM_VALID_INDEX */
    if ( DoIP_GetRetryAttemptOfTxUdpMgtList(TxUdpListIdx) == 0u )
    {
      /* #20 Release entry if retry failed several times. */
      *ReleaseListEntry = TRUE;                                                                                        /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    }
  }
  else
  {
    /* #30 Release entry if successfully send. */
    *ReleaseListEntry = TRUE;                                                                                          /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  }
} /* DoIP_TxUdpList_HandleEntriesOthers() */

/**********************************************************************************************************************
 *  DoIP_TxTcp_Transmit()
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
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxTcp_Transmit(                                                        /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 HdrType,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  uint16 Param1,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint32 Param2,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint8  Param3,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  SduDataPtrType DataPtr,                                                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER */
  boolean CloseSocket)                                                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  DOIP_BEGIN_CRITICAL_SECTION();

  /* #10 Check if socket connection is online. */
  if ( DoIP_GetSoConStateOfConnectionDyn(ConnectionTcpIdx) == SOAD_SOCON_ONLINE )
  {
    /* #20 Check if socket connection shall stay active. */
    if ( !DoIP_IsSoConClosingOfConnectionDyn(ConnectionTcpIdx) )
    {
#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
      /* #30 Increment the count of received TCP packets dropped by DoIP. */
      DoIP_Measure_IncDroppedPacketCounter(DOIP_MEASURE_DROPPED_PACKET_COUNTER_TCP, HdrType, Param3);
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

      /* #40 Add element to Tx queue. */
      retVal = DoIP_TxTcpQueue_Add(ConnectionTcpIdx, HdrType, Param1, Param2, Param3, DataPtr);                        /* SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER_FORWARD */

      /* #50 Check if element was added successfully. */
      if ( retVal == E_OK )
      {
        if ( CloseSocket == TRUE )
        {
          /* #60 Mark socket for closing if close socket is indicated. */
          DoIP_SetSoConClosingOfConnectionDyn(ConnectionTcpIdx, TRUE);                                                 /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
        }

        DOIP_END_CRITICAL_SECTION();

        /* #70 Start transmission of Tx queue. */
        DoIP_TxTcpQueue_TransmitElement(ConnectionTcpIdx);
      }
      else
      {
        DOIP_END_CRITICAL_SECTION();

#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
        /* no memory in TxQueue available */
        errorId = DOIP_E_NOBUFS;
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
      }
    }
    else
    {
      DOIP_END_CRITICAL_SECTION();
    }
  }
  else
  {
    DOIP_END_CRITICAL_SECTION();
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_VTCP_TRANSMIT, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* DoIP_TxTcp_Transmit() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  DoIP_TxTcp_PrepareTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcp_PrepareTransmit(                                                           /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 HdrType,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  uint16 Param1,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint32 Param2,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint8  Param3,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  boolean CloseSocket)                                                                                                 /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Implementation ----------------------------------------------- */
  if ( DoIP_GetTpTxPreHdrTypeOfConnectionTcpDyn(ConnectionTcpIdx) == DOIP_HDR_TYPE_INVALID )
  {
    /* #10 Store transmission parameter if there are no pending prepare transmit request. */
    DoIP_SetTpTxPreHdrTypeOfConnectionTcpDyn(ConnectionTcpIdx, HdrType);                                               /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    DoIP_SetTpTxPreParam1OfConnectionTcpDyn(ConnectionTcpIdx, Param1);                                                 /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    DoIP_SetTpTxPreParam2OfConnectionTcpDyn(ConnectionTcpIdx, Param2);                                                 /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    DoIP_SetTpTxPreParam3OfConnectionTcpDyn(ConnectionTcpIdx, Param3);                                                 /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    DoIP_SetTpTxPreCloseSocketOfConnectionTcpDyn(ConnectionTcpIdx, CloseSocket);                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }
} /* DoIP_TxTcp_PrepareTransmit() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  DoIP_TxTcp_FinishTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcp_FinishTransmit(                                                            /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Implementation ----------------------------------------------- */
  if ( DoIP_GetTpTxPreHdrTypeOfConnectionTcpDyn(ConnectionTcpIdx) != DOIP_HDR_TYPE_INVALID )
  {
    /* #10 Transmit message if there is a pending transmit request. */
    (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx,                                                                        /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      DoIP_GetTpTxPreHdrTypeOfConnectionTcpDyn(ConnectionTcpIdx),
      DoIP_GetTpTxPreParam1OfConnectionTcpDyn(ConnectionTcpIdx),
      DoIP_GetTpTxPreParam2OfConnectionTcpDyn(ConnectionTcpIdx),
      DoIP_GetTpTxPreParam3OfConnectionTcpDyn(ConnectionTcpIdx),
      NULL_PTR,
      DoIP_GetTpTxPreCloseSocketOfConnectionTcpDyn(ConnectionTcpIdx));
    DoIP_SetTpTxPreHdrTypeOfConnectionTcpDyn(ConnectionTcpIdx, DOIP_HDR_TYPE_INVALID);                                 /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }
} /* DoIP_TxTcp_FinishTransmit() */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_Add()
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
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_Add(                                                        /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 HdrType,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  uint16 Param1,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint32 Param2,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint8  Param3,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  SduDataPtrType DataPtr)                                                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  DoIP_SizeOfTxTcpMgtType txTcpMgtQueIdx = DoIP_GetTxTcpMgtQueIdxOfConnectionTcpDyn(ConnectionTcpIdx);
  const DoIP_SizeOfTxTcpMgtType txTcpMgtQueLvl = DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(ConnectionTcpIdx);
  const DoIP_SizeOfTxTcpMgtType txTcpMgtSize = (DoIP_SizeOfTxTcpMgtType)(
    DoIP_GetTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Tx queue can handle this request. */
  if ( txTcpMgtQueLvl < txTcpMgtSize )
  {
    /* #20 Find next free entry in Tx queue. */
    if ( (txTcpMgtQueIdx + txTcpMgtQueLvl) >= txTcpMgtSize )
    {
      /* #30 Handle wrap around. */
      txTcpMgtQueIdx = (DoIP_SizeOfTxTcpMgtType)(txTcpMgtQueLvl - (txTcpMgtSize - txTcpMgtQueIdx));
    }
    else
    {
      txTcpMgtQueIdx = (DoIP_SizeOfTxTcpMgtType)(txTcpMgtQueIdx + txTcpMgtQueLvl);
    }

    /* #40 Add entry depending on there header type. */
    switch(HdrType)
    {
      case DOIP_HDR_TYPE_GEN_NACK:
      {
        DoIP_TxTcpQueue_AddGenNack(txTcpMgtQueIdx, ConnectionTcpIdx, (uint8)Param1);
        break;
      }
      case DOIP_HDR_TYPE_ROUT_ACTIV_RES:
      {
        DoIP_TxTcpQueue_AddRoutingActivationRes(txTcpMgtQueIdx, ConnectionTcpIdx, Param1, (uint8)Param2, Param3);
        break;
      }
      case DOIP_HDR_TYPE_ALIVE_CHECK_REQ:
      {
        DoIP_TxTcpQueue_AddAliveCheckReq(txTcpMgtQueIdx, ConnectionTcpIdx);
        break;
      }
      case DOIP_HDR_TYPE_DIAG_REQ:
      {
        /* Param2 can be casted to PduLengthType because it was a PduLengthType before. */
        DoIP_TxTcpQueue_AddDiagReq(txTcpMgtQueIdx, ConnectionTcpIdx, (DoIP_SizeOfChannelType)Param1,                   /* SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER_FORWARD */
          (PduLengthType)Param2, DataPtr);
        break;
      }
      case DOIP_HDR_TYPE_DIAG_ACK:
      {
        DoIP_TxTcpQueue_AddDiagAck(txTcpMgtQueIdx, ConnectionTcpIdx, Param1);
        break;
      }
      case DOIP_HDR_TYPE_DIAG_NACK:
      {
        DoIP_TxTcpQueue_AddDiagNack(txTcpMgtQueIdx, ConnectionTcpIdx, Param1, (uint16)Param2, Param3);
        break;
      }
#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
      case DOIP_HDR_TYPE_OEM_SPECIFIC:
      {
        DoIP_TxTcpQueue_AddOem(txTcpMgtQueIdx, ConnectionTcpIdx, Param1);
        break;
      }
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */
      default:
      { /* function does not support this header type */
        /* invalid state */
        /* nothing to do here */
        break;
      }
    }

    /* #50 Update Tx queue. */
    DoIP_IncTxTcpMgtQueLvlOfConnectionTcpDyn(ConnectionTcpIdx);                                                        /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

    retVal = E_OK;
  }

  return retVal;
} /* DoIP_TxTcpQueue_Add() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddGenNack()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddGenNack(                                                           /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint8 NackCode)                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
  DoIP_TxHdrBufType *txHdrBufPtr = DoIP_GetAddrTxHdrBuf(DoIP_GetTxHdrBufStartIdxOfTxTcpMgt(txTcpMgtIdx));
  PduInfoType *msg = DoIP_GetAddrMsgOfTxTcpMgtDyn(txTcpMgtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write DoIP header to Tx buffer. */
  DoIP_Util_FillGenHdr(DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_HDR_NACK_CODE_LEN_BYTE, txHdrBufPtr);                          /* SBSW_DOIP_TxHdrBuf_FORWARD */

  /* #20 Write nack code to Tx buffer. */
  txHdrBufPtr[DOIP_GEN_HDR_LEN_BYTE] = NackCode;                                                                       /* SBSW_DOIP_TxHdrBuf */

  /* #30 Set Tx management struct. */
  DoIP_SetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx, (DOIP_GEN_HDR_LEN_BYTE + DOIP_GEN_HDR_NACK_CODE_LEN_BYTE));            /* SBSW_DOIP_TxTcpMgt */
  msg->SduLength = DoIP_GetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx);                                                      /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msg->SduDataPtr = txHdrBufPtr;                                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
} /* DoIP_TxTcpQueue_AddGenNack() */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddRoutingActivationRes()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddRoutingActivationRes(                                              /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 TesterAddr,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint8 AckCode,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  DoIP_SizeOfTesterType TesterIdx)                                                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
  const DoIP_RoutingActivationIdxOfConnectionTcpDynType routActIdx =
    DoIP_GetRoutingActivationIdxOfConnectionTcpDyn(ConnectionTcpIdx);
  DoIP_TxHdrBufType *txHdrBufPtr = DoIP_GetAddrTxHdrBuf(DoIP_GetTxHdrBufStartIdxOfTxTcpMgt(txTcpMgtIdx));
  PduInfoType *msg = DoIP_GetAddrMsgOfTxTcpMgtDyn(txTcpMgtIdx);
  PduLengthType bufIdx = DOIP_GEN_HDR_LEN_BYTE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write DoIP header to Tx buffer. */
  DoIP_Util_PutUInt16(&txHdrBufPtr[bufIdx], 0u, TesterAddr);                                                           /* SBSW_DOIP_TxHdrBuf_FORWARD */
  bufIdx += DOIP_ADDR_LEN_BYTE;
  DoIP_Util_PutUInt16(&txHdrBufPtr[bufIdx], 0u, DOIP_ADDR);                                                            /* SBSW_DOIP_TxHdrBuf_FORWARD */
  bufIdx += DOIP_ADDR_LEN_BYTE;
  txHdrBufPtr[bufIdx] = AckCode;                                                                                       /* SBSW_DOIP_TxHdrBuf */
  bufIdx++;
  txHdrBufPtr[bufIdx] = 0u;                                                                                            /* SBSW_DOIP_TxHdrBuf */
  bufIdx++;
  txHdrBufPtr[bufIdx] = 0u;                                                                                            /* SBSW_DOIP_TxHdrBuf */
  bufIdx++;
  txHdrBufPtr[bufIdx] = 0u;                                                                                            /* SBSW_DOIP_TxHdrBuf */
  bufIdx++;
  txHdrBufPtr[bufIdx] = 0u;                                                                                            /* SBSW_DOIP_TxHdrBuf */
  bufIdx++;

  if ( TesterIdx == DoIP_GetSizeOfTester() )
  {
    /* #20 Fill generic header (without OEM specific data) if tester is unknown. */
    DoIP_Util_FillGenHdr(DOIP_HDR_TYPE_ROUT_ACTIV_RES, DOIP_ROUT_ACTIV_ACK_MIN_LEN_BYTE, txHdrBufPtr);                 /* SBSW_DOIP_TxHdrBuf_FORWARD */
  }
  else if ( routActIdx == DoIP_GetSizeOfRoutingActivation() )
  {
    /* #30 Otherwise fill generic header (without OEM specific data) if routing activation is unknown. */
    DoIP_Util_FillGenHdr(DOIP_HDR_TYPE_ROUT_ACTIV_RES, DOIP_ROUT_ACTIV_ACK_MIN_LEN_BYTE, txHdrBufPtr);                 /* SBSW_DOIP_TxHdrBuf_FORWARD */
  }
  else if ( ((DoIP_GetAuthResLengthOfRoutingActivation(routActIdx) == 0u) &&
             (DoIP_GetConfResLengthOfRoutingActivation(routActIdx) == 0u)) ||
             (DoIP_GetActivStateOfConnectionTcpDyn(ConnectionTcpIdx) != DOIP_ROUT_ACTIV_STATE_ACTIVATED) )
  {
    /* #40 Otherwise fill generic header (without OEM specific data) if routing activation is needed and pending. */
    DoIP_Util_FillGenHdr(DOIP_HDR_TYPE_ROUT_ACTIV_RES, DOIP_ROUT_ACTIV_ACK_MIN_LEN_BYTE, txHdrBufPtr);                 /* SBSW_DOIP_TxHdrBuf_FORWARD */
  }
  else if ( TesterAddr != DoIP_GetTesterAddrOfConnectionTcpDyn(ConnectionTcpIdx) )
  {
    /* #50 Otherwise fill generic header (without OEM specific data) if tester is different. */
    DoIP_Util_FillGenHdr(DOIP_HDR_TYPE_ROUT_ACTIV_RES, DOIP_ROUT_ACTIV_ACK_MIN_LEN_BYTE, txHdrBufPtr);                 /* SBSW_DOIP_TxHdrBuf_FORWARD */
  }
  else
  {
    uint32 oemSpecRes = DoIP_GetOemSpecResOfRoutActivHandler(0u);

    /* #60 Otherwise fill generic header with OEM specific data. */
    DoIP_Util_FillGenHdr(DOIP_HDR_TYPE_ROUT_ACTIV_RES, DOIP_ROUT_ACTIV_ACK_MAX_LEN_BYTE, txHdrBufPtr);                 /* SBSW_DOIP_TxHdrBuf_FORWARD */

    DoIP_Util_PutUInt32(&txHdrBufPtr[bufIdx], 0u, oemSpecRes);                                                         /* SBSW_DOIP_TxHdrBuf_FORWARD */
    bufIdx += 4u;
  }

  /* #70 Set Tx management struct. */
  DoIP_SetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx, bufIdx);                                                               /* SBSW_DOIP_TxTcpMgt */
  msg->SduLength = bufIdx;                                                                                             /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msg->SduDataPtr = txHdrBufPtr;                                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
} /* DoIP_TxTcpQueue_AddRoutingActivationRes() */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddAliveCheckReq()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddAliveCheckReq(                                                     /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
  DoIP_TxHdrBufType *txHdrBufPtr = DoIP_GetAddrTxHdrBuf(DoIP_GetTxHdrBufStartIdxOfTxTcpMgt(txTcpMgtIdx));
  PduInfoType *msg = DoIP_GetAddrMsgOfTxTcpMgtDyn(txTcpMgtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write DoIP header to Tx buffer. */
  DoIP_Util_FillGenHdr(DOIP_HDR_TYPE_ALIVE_CHECK_REQ, 0u, txHdrBufPtr);                                                /* SBSW_DOIP_TxHdrBuf_FORWARD */

  /* #20 Set Tx management struct. */
  DoIP_SetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx, DOIP_GEN_HDR_LEN_BYTE);                                                /* SBSW_DOIP_TxTcpMgt */
  msg->SduLength = DOIP_GEN_HDR_LEN_BYTE;                                                                              /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  msg->SduDataPtr = txHdrBufPtr;                                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
} /* DoIP_TxTcpQueue_AddAliveCheckReq() */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddDiagReq()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddDiagReq(                                                           /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfChannelType ChannelIdx,                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  PduLengthType Length,                                                                                                /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  SduDataPtrType DataPtr) /* PRQA S 3673 */ /* MD_DoIP_16.7 */                                                         /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_EcuAddrOfChannelType ecuAddr = DoIP_GetEcuAddrOfChannel(ChannelIdx);
  const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx);
  const DoIP_TesterAddrOfTesterType testerAddr = DoIP_GetTesterAddrOfTester(testerIdx);
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
  DoIP_TxHdrBufType *txHdrBufPtr = DoIP_GetAddrTxHdrBuf(DoIP_GetTxHdrBufStartIdxOfTxTcpMgt(txTcpMgtIdx));
  PduInfoType *msg = DoIP_GetAddrMsgOfTxTcpMgtDyn(txTcpMgtIdx);
  PduLengthType bufIdx = DOIP_GEN_HDR_LEN_BYTE;

  /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_IF_API_ENABLED == STD_ON )
  if ( DoIP_GetApiTypeOfChannel(ChannelIdx) == DOIP_API_TYPE_IF )
  {
    /* #10 Copy data to IF Tx buffer if API type is IF. */
    /* PRQA S 0310, 0314 2 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
    VStdLib_MemCpy(DOIP_A_P2VAR(void)DoIP_GetAddrIfTxBuf(DoIP_GetIfTxBufStartIdxOfChannel(ChannelIdx)),                /* SBSW_DOIP_IfTxBuf_AND_CONST_POINTER_FORWARD */
      DOIP_A_P2CONST(void)DataPtr, Length);
  }
#else
  DOIP_DUMMY_STATEMENT(DataPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_IF_API_ENABLED == STD_ON */

  /* #20 Write DoIP header to Tx buffer. */
  DoIP_Util_FillGenHdr(DOIP_HDR_TYPE_DIAG_REQ, (DOIP_DIAG_HDR_LEN_BYTE + (uint32)Length), txHdrBufPtr);                /* SBSW_DOIP_TxHdrBuf_FORWARD */

  DoIP_Util_PutUInt16(&txHdrBufPtr[bufIdx], 0u, ecuAddr);                                                              /* SBSW_DOIP_TxHdrBuf_FORWARD */
  bufIdx += DOIP_ADDR_LEN_BYTE;
#if ( DOIP_DEFAULT_TESTER_ENABLED == STD_ON )
  if ( testerAddr == DOIP_ADDR_ANY )
  {
    /* #30 Add tester default address to Tx buffer if default address is used (if enabeld). */
    const DoIP_TesterAddrOfConnectionTcpDynType testerAddrOfConnection =
      DoIP_GetTesterAddrOfConnectionTcpDyn(ConnectionTcpIdx);
    DoIP_Util_PutUInt16(&txHdrBufPtr[bufIdx], 0u, testerAddrOfConnection);                                             /* SBSW_DOIP_TxHdrBuf_FORWARD */
  }
  else
#endif /* DOIP_DEFAULT_TESTER_ENABLED == STD_ON */
  {
    /* #40 Otherwise add tester address to Tx buffer. */
    DoIP_Util_PutUInt16(&txHdrBufPtr[bufIdx], 0u, testerAddr);                                                         /* SBSW_DOIP_TxHdrBuf_FORWARD */
  }
  bufIdx += DOIP_ADDR_LEN_BYTE;

  /* #50 Set Tx management struct. */
  DoIP_SetChannelIdxOfTxTcpMgtDyn(txTcpMgtIdx, ChannelIdx);                                                            /* SBSW_DOIP_TxTcpMgt */
  DoIP_SetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx, bufIdx);                                                               /* SBSW_DOIP_TxTcpMgt */
  msg->SduLength = bufIdx + Length;                                                                                    /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
#if ( DOIP_IF_API_ENABLED == STD_ON )
  if ( DoIP_GetApiTypeOfChannel(ChannelIdx) == DOIP_API_TYPE_IF )
  {
    msg->SduDataPtr = DataPtr;                                                                                         /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  }
  else
#endif /* DOIP_IF_API_ENABLED == STD_ON */
  {
    msg->SduDataPtr = txHdrBufPtr;                                                                                     /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  }
} /* DoIP_TxTcpQueue_AddDiagReq() */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddDiagAck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddDiagAck(                                                           /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 EcuAddr)                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx);
  const DoIP_TesterAddrOfTesterType testerAddr = DoIP_GetTesterAddrOfTester(testerIdx);
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
#if ( DOIP_NACK_APPEND_REQ == STD_ON )
  const DoIP_DiagNAckOffsetOfTesterDynType diagNAckOffset = DoIP_GetDiagNAckOffsetOfTesterDyn(testerIdx);
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */
  DoIP_TxHdrBufType *txHdrBufPtr = DoIP_GetAddrTxHdrBuf(DoIP_GetTxHdrBufStartIdxOfTxTcpMgt(txTcpMgtIdx));
  PduInfoType *msg = DoIP_GetAddrMsgOfTxTcpMgtDyn(txTcpMgtIdx);
  PduLengthType bufIdx = DOIP_GEN_HDR_LEN_BYTE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write DoIP header with nack offset to Tx buffer. */
#if ( DOIP_NACK_APPEND_REQ == STD_ON )
  DoIP_Util_FillGenHdr(DOIP_HDR_TYPE_DIAG_ACK, DOIP_DIAG_MSG_ACK_LEN_BYTE + diagNAckOffset, txHdrBufPtr);              /* SBSW_DOIP_TxHdrBuf_FORWARD */
#else
  DoIP_Util_FillGenHdr(DOIP_HDR_TYPE_DIAG_ACK, DOIP_DIAG_MSG_ACK_LEN_BYTE, txHdrBufPtr);                               /* SBSW_DOIP_TxHdrBuf_FORWARD */
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */

  DoIP_Util_PutUInt16(&txHdrBufPtr[bufIdx], 0u, EcuAddr);                                                              /* SBSW_DOIP_TxHdrBuf_FORWARD */
  bufIdx += DOIP_ADDR_LEN_BYTE;
#if ( DOIP_DEFAULT_TESTER_ENABLED == STD_ON )
  if ( testerAddr == DOIP_ADDR_ANY )
  {
    /* #20 Add tester default address to Tx buffer if default address is used (if enabeld). */
    const DoIP_TesterAddrOfConnectionTcpDynType testerAddrOfConnection =
      DoIP_GetTesterAddrOfConnectionTcpDyn(ConnectionTcpIdx);
    DoIP_Util_PutUInt16(&txHdrBufPtr[bufIdx], 0u, testerAddrOfConnection);                                             /* SBSW_DOIP_TxHdrBuf_FORWARD */
  }
  else
#endif /* DOIP_DEFAULT_TESTER_ENABLED == STD_ON */
  {
    /* #30 Otherwise add tester address to Tx buffer. */
    DoIP_Util_PutUInt16(&txHdrBufPtr[bufIdx], 0u, testerAddr);                                                         /* SBSW_DOIP_TxHdrBuf_FORWARD */
  }
  bufIdx += DOIP_ADDR_LEN_BYTE;
  txHdrBufPtr[bufIdx] = DOIP_DIAG_MSG_RES_CODE_ACK;                                                                    /* SBSW_DOIP_TxHdrBuf */
  bufIdx++;

  /* #40 Set Tx management struct. */
  DoIP_SetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx, bufIdx);                                                               /* SBSW_DOIP_TxTcpMgt */
#if ( DOIP_NACK_APPEND_REQ == STD_ON )
  msg->SduLength = (PduLengthType)(bufIdx + diagNAckOffset);                                                           /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
#else
  msg->SduLength = bufIdx;                                                                                             /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */
  msg->SduDataPtr = txHdrBufPtr;                                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
} /* DoIP_TxTcpQueue_AddDiagAck() */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddDiagNack()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddDiagNack(                                                          /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 EcuAddr,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint16 TesterAddr,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint8 NackCode)                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
  DoIP_TxHdrBufType *txHdrBufPtr = DoIP_GetAddrTxHdrBuf(DoIP_GetTxHdrBufStartIdxOfTxTcpMgt(txTcpMgtIdx));
  PduInfoType *msg = DoIP_GetAddrMsgOfTxTcpMgtDyn(txTcpMgtIdx);
  PduLengthType bufIdx = DOIP_GEN_HDR_LEN_BYTE;
#if ( DOIP_NACK_APPEND_REQ == STD_ON )
  const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx);
  DoIP_DiagNAckOffsetOfTesterDynType diagNAckOffset;
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write DoIP header to Tx buffer. */
#if ( DOIP_NACK_APPEND_REQ == STD_ON )
  if ( testerIdx != DoIP_GetSizeOfTester() )
  {
    /* #15 Write DoIP header with nack offset to Tx buffer if tester is known (if enabled). */
    diagNAckOffset = DoIP_GetDiagNAckOffsetOfTesterDyn(testerIdx);
    DoIP_Util_FillGenHdr(DOIP_HDR_TYPE_DIAG_NACK, DOIP_DIAG_MSG_ACK_LEN_BYTE + diagNAckOffset, txHdrBufPtr);           /* SBSW_DOIP_TxHdrBuf_FORWARD */
  }
  else
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */
  {
    /* #20 Otherwise write DoIP header to Tx buffer. */
    DoIP_Util_FillGenHdr(DOIP_HDR_TYPE_DIAG_NACK, DOIP_DIAG_MSG_ACK_LEN_BYTE, txHdrBufPtr);                            /* SBSW_DOIP_TxHdrBuf_FORWARD */
  }

  DoIP_Util_PutUInt16(&txHdrBufPtr[bufIdx], 0u, EcuAddr);                                                              /* SBSW_DOIP_TxHdrBuf_FORWARD */
  bufIdx += DOIP_ADDR_LEN_BYTE;

  DoIP_Util_PutUInt16(&txHdrBufPtr[bufIdx], 0u, TesterAddr);                                                           /* SBSW_DOIP_TxHdrBuf_FORWARD */
  bufIdx += DOIP_ADDR_LEN_BYTE;

  txHdrBufPtr[bufIdx] = NackCode;                                                                                      /* SBSW_DOIP_TxHdrBuf */
  bufIdx += 1u;

  /* #30 Set Tx management struct. */
  DoIP_SetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx, bufIdx);                                                               /* SBSW_DOIP_TxTcpMgt */
#if ( DOIP_NACK_APPEND_REQ == STD_ON )
  if ( testerIdx != DoIP_GetSizeOfTester() )
  {
    /* #40 Send diagnostic message negative ack with user data if tester is known (if enabled). */
    diagNAckOffset = DoIP_GetDiagNAckOffsetOfTesterDyn(testerIdx);
    msg->SduLength = (PduLengthType)(bufIdx + diagNAckOffset);                                                         /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  }
  else
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */
  {
    /* #50 Otherwise send diagnostic message negative ack. */
    msg->SduLength = bufIdx;                                                                                           /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  }
  msg->SduDataPtr = txHdrBufPtr;                                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
} /* DoIP_TxTcpQueue_AddDiagNack() */

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_AddOem()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_AddOem(                                                               /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 HdrTypeOem)                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
  DoIP_TxHdrBufType *txHdrBufPtr = DoIP_GetAddrTxHdrBuf(DoIP_GetTxHdrBufStartIdxOfTxTcpMgt(txTcpMgtIdx));
  PduInfoType *msg = DoIP_GetAddrMsgOfTxTcpMgtDyn(txTcpMgtIdx);
# if ( DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u )
  const DoIP_OemPayloadTypeTcpBufLenType oemTcpBufLen = DoIP_GetOemPayloadTypeTcpBufLen();
# endif /* DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write DoIP header to Tx buffer. */
# if ( DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u )
  DoIP_Util_FillGenHdr(HdrTypeOem, oemTcpBufLen, txHdrBufPtr);                                                         /* SBSW_DOIP_TxHdrBuf_FORWARD */
# else
  DoIP_Util_FillGenHdr(HdrTypeOem, 0u, txHdrBufPtr);                                                                   /* SBSW_DOIP_TxHdrBuf_FORWARD */
# endif /* DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u */

  /* #20 Set Tx management struct. */
  DoIP_SetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx, DOIP_GEN_HDR_LEN_BYTE);                                                /* SBSW_DOIP_TxTcpMgt */
# if ( DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u )
  msg->SduLength = ((PduLengthType)DOIP_GEN_HDR_LEN_BYTE + (PduLengthType)oemTcpBufLen);                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
# else
  msg->SduLength = DOIP_GEN_HDR_LEN_BYTE;                                                                              /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
# endif /* DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u */
  msg->SduDataPtr = txHdrBufPtr;                                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
} /* DoIP_TxTcpQueue_AddOem() */
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_Copy()
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
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_Copy(                                                    /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr)                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  const DoIP_SizeOfTxTcpMgtType txTcpMgtQueIdx = DoIP_GetTxTcpMgtQueIdxOfConnectionTcpDyn(ConnectionTcpIdx);
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + txTcpMgtQueIdx);
  const DoIP_TxHdrBufLenOfTxTcpMgtDynType txHdrBufLen = DoIP_GetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx);
  const DoIP_TxBytesCopiedOfConnectionTcpDynType txBytesCopied =
    DoIP_GetTxBytesCopiedOfConnectionTcpDyn(ConnectionTcpIdx);
  const PduInfoType *msg = DoIP_GetAddrMsgOfTxTcpMgtDyn(txTcpMgtIdx);
  boolean hdrCopied = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  DOIP_BEGIN_CRITICAL_SECTION();

  /* #10 Check if TP session is online. */
  if ( !DoIP_IsTxTpSessionActiveOfConnectionTcpDyn(ConnectionTcpIdx) )
  { /* TP session is not online */
    /* nothing to do here */
  }
  else
#if ( DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON )
  /* #20 Check if TP is not canceled (if enabled). */
  if ( DoIP_IsTxTpCancelRequestedOfConnectionTcpDyn(ConnectionTcpIdx) )
  { /* TP cancellation is ongoing */
    /* nothing to do here */
  }
  else
#endif /* DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON */
  /* #30 Check length and if this is a subsequent call of CopyTxData. */
  if ( (PduInfoPtr->SduLength != 0u) &&
       (PduInfoPtr->SduLength > DoIP_GetLastTxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx)) )
  { /* unexpected length */
    /* nothing to do here */
  }
  else
  {
    if ( DoIP_GetActivStateOfConnectionTcpDyn(ConnectionTcpIdx) == DOIP_ROUT_ACTIV_STATE_ACTIVATED )
    {
      /* #40 Reset inactivity timer if routing activation is active. */
      DoIP_SetInactivCntOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                      /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    }

    if ( txBytesCopied < txHdrBufLen )
    {
      /* #50 Check if header is not yet copied. */
      retVal = DoIP_TxTcpQueue_CopyHeader(txTcpMgtQueIdx, ConnectionTcpIdx, PduInfoPtr, AvailableDataPtr, &hdrCopied); /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    }
    else
    {
      retVal = BUFREQ_OK;
    }

    if ( (retVal == BUFREQ_OK) &&
         (txHdrBufLen <= txBytesCopied) &&
         (txHdrBufLen < msg->SduLength) )
    {
      /* #60 Copy data if header was (already) copied successfuly and more data are available. */
      retVal = DoIP_TxTcpQueue_CopyData(txTcpMgtQueIdx, ConnectionTcpIdx, PduInfoPtr, AvailableDataPtr, hdrCopied);    /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    }
  }

  DOIP_END_CRITICAL_SECTION();

  return retVal;
} /* DoIP_TxTcpQueue_Copy() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyHeader()
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
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_CopyHeader(                                              /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(boolean, AUTOMATIC, DOIP_APPL_VAR) HdrCopied)                                                                  /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal = BUFREQ_OK;
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
  const DoIP_TxHdrBufLenOfTxTcpMgtDynType txHdrBufLen = DoIP_GetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx);
  const DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_GetConnectionTcpIdxOfRoutActivHandler(0u);
  DoIP_TxBytesCopiedOfConnectionTcpDynType txBytesCopied = DoIP_GetTxBytesCopiedOfConnectionTcpDyn(ConnectionTcpIdx);
  const DoIP_TxHdrBufType *txHdrBufPtr = DoIP_GetAddrTxHdrBuf(DoIP_GetTxHdrBufStartIdxOfTxTcpMgt(txTcpMgtIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if this is a subsequent call of CopyTxData. */
  if ( PduInfoPtr->SduLength != 0u )
  {
    /* #20 Check requested length. */
    if ( PduInfoPtr->SduLength <= ((PduLengthType)(txHdrBufLen - txBytesCopied)) )
    {
      /* #30 Copy requested number of bytes to target buffer if length is valid. */
      /* PRQA S 0310, 0314 1 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
      VStdLib_MemCpy(DOIP_A_P2VAR(void)PduInfoPtr->SduDataPtr, DOIP_A_P2CONST(void)&txHdrBufPtr[txBytesCopied],        /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
         PduInfoPtr->SduLength);

      txBytesCopied += PduInfoPtr->SduLength;
      DoIP_SetTxBytesCopiedOfConnectionTcpDyn(ConnectionTcpIdx, txBytesCopied);                                        /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

      /* #40 Check if header was copied completely. */
      if ( txBytesCopied == txHdrBufLen )
      {
        uint16 hdrType;

        IPBASE_GET_UINT16(&txHdrBufPtr[DOIP_GEN_HDR_TYPE_IDX], 0u, hdrType);                                           /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

        if ( (hdrType == DOIP_HDR_TYPE_ROUT_ACTIV_RES) && (connectionTcpIdx != DoIP_GetSizeOfConnectionTcp()) &&
             (DoIP_GetActivStateOfConnectionTcpDyn(connectionTcpIdx) != DOIP_ROUT_ACTIV_STATE_CONF_PENDING) )
        {
          /* #50 In case of confirmation a Routing Activation Response might be sent even if Routing Activation
           * is not finished. Release Routing Activation Handler in all other cases. */
          DoIP_SetConnectionTcpIdxOfRoutActivHandler(0u, DoIP_GetSizeOfConnectionTcp());                               /* SBSW_DOIP_RoutActivHandler */
          DoIP_SetAliveCheckCntOfRoutActivHandler(0u, 0u);                                                             /* SBSW_DOIP_RoutActivHandler */
        }

        *HdrCopied = TRUE;                                                                                             /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
      }
    }
    else
    { /* invalid length */
      retVal = BUFREQ_E_NOT_OK;
    }
  }

  if ( retVal == BUFREQ_OK )
  {
    /* #60 Set available data length if header was (already) copied successfully. */
    *AvailableDataPtr = (PduLengthType)(txHdrBufLen - txBytesCopied);                                                  /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    DoIP_SetLastTxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *AvailableDataPtr);                                      /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }

  return retVal;
} /* DoIP_TxTcpQueue_CopyHeader() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_CopyData(                                                /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  boolean HdrCopied)                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal;
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
  const DoIP_TxHdrBufType *txHdrBufPtr = DoIP_GetAddrTxHdrBuf(DoIP_GetTxHdrBufStartIdxOfTxTcpMgt(txTcpMgtIdx));
  uint16 hdrType;

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT16(&txHdrBufPtr[DOIP_GEN_HDR_TYPE_IDX], 0u, hdrType);                                                 /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  /* #10 Copy data depending on there header type. */
  switch(hdrType)
  {
    case DOIP_HDR_TYPE_DIAG_REQ:
    {
      retVal = DoIP_TxTcpQueue_CopyDiagReq(QueueIdx, ConnectionTcpIdx, PduInfoPtr, AvailableDataPtr, HdrCopied);       /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      break;
    }
#if ( DOIP_NACK_APPEND_REQ == STD_ON )
    case DOIP_HDR_TYPE_DIAG_ACK:
    case DOIP_HDR_TYPE_DIAG_NACK:
    {
      retVal = DoIP_TxTcpQueue_CopyDiagAck(QueueIdx, ConnectionTcpIdx, PduInfoPtr, AvailableDataPtr, HdrCopied);       /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      break;
    }
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */
    default:
    {
#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
# if ( DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u )
      DoIP_TxTcpQueue_CopyOemSpecific(QueueIdx, ConnectionTcpIdx, PduInfoPtr, AvailableDataPtr, HdrCopied);            /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      retVal = BUFREQ_OK;
# else
      retVal = BUFREQ_E_NOT_OK;
# endif /* DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u */
#else
      retVal = BUFREQ_E_NOT_OK;
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */
      break;
    }
  }

  return retVal;
} /* DoIP_TxTcpQueue_CopyData() */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyDiagReq()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_CopyDiagReq(                                             /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  boolean HdrCopied)                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal;
#if ( DOIP_IF_API_ENABLED == STD_ON )
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
#endif /* DOIP_IF_API_ENABLED == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy data depending on there API type. */
#if ( DOIP_IF_API_ENABLED == STD_ON )
  if ( DoIP_GetApiTypeOfChannel(DoIP_GetChannelIdxOfTxTcpMgtDyn(txTcpMgtIdx)) == DOIP_API_TYPE_IF )
  {
    DoIP_TxTcpQueue_CopyDiagReqIF(QueueIdx, ConnectionTcpIdx, PduInfoPtr, AvailableDataPtr, HdrCopied);                /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    retVal = BUFREQ_OK;
  }
  else
#endif /* DOIP_IF_API_ENABLED == STD_ON */
  {
    retVal = DoIP_TxTcpQueue_CopyDiagReqTP(QueueIdx, ConnectionTcpIdx, PduInfoPtr, AvailableDataPtr, HdrCopied);       /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }

  return retVal;
} /* DoIP_TxTcpQueue_CopyDiagReq() */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyDiagReqTP()
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
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_CopyDiagReqTP(                                           /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  boolean HdrCopied)                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal;
  P2VAR(PduInfoType, AUTOMATIC, AUTOMATIC) locPduInfoPtr = PduInfoPtr;
  PduInfoType locPduInfoStruct;
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
  const DoIP_TxBytesCopiedOfConnectionTcpDynType txBytesCopied =
    DoIP_GetTxBytesCopiedOfConnectionTcpDyn(ConnectionTcpIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Query available upper layer buffer if header was copied successfully. */
  if ( HdrCopied == TRUE )
  {
    locPduInfoStruct.SduLength = 0u;
    locPduInfoStruct.SduDataPtr = NULL_PTR;
    locPduInfoPtr = &locPduInfoStruct;
  }

  /* #20 Call upper layer CopyTxData function to query available buffer or copying. */
  retVal = PduR_DoIPTpCopyTxData(DoIP_GetPduRTxConfPduIdOfChannel(DoIP_GetChannelIdxOfTxTcpMgtDyn(txTcpMgtIdx)),       /* SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER_FORWARD */
    locPduInfoPtr, NULL_PTR, AvailableDataPtr);

  /* #30 Indicate failure if Tx queue has been modifed. */
  if ( DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(ConnectionTcpIdx) == 0u )
  {
    retVal = BUFREQ_E_NOT_OK;
  }

  if ( retVal == BUFREQ_OK )
  {
    /* #40 Update Tx management struct if buffer request was succesful. */
    DoIP_SetLastTxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *AvailableDataPtr);                                      /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    DoIP_SetTxBytesCopiedOfConnectionTcpDyn(ConnectionTcpIdx, (txBytesCopied + locPduInfoPtr->SduLength));             /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }
  else
  {
    /* #50 Close connection since generic header has already been sent if buffer request failed . */
    DoIP_SetSoConClosingOfConnectionDyn(ConnectionTcpIdx, TRUE);                                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    DoIP_Con_SoConClose((DoIP_SizeOfConnectionType)ConnectionTcpIdx);

    retVal = BUFREQ_E_NOT_OK;
  }

  return retVal;
} /* DoIP_TxTcpQueue_CopyDiagReqTP() */

#if ( DOIP_IF_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyDiagReqIF()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_CopyDiagReqIF(                                                        /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  boolean HdrCopied)                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
  DoIP_TxBytesCopiedOfConnectionTcpDynType txBytesCopied = DoIP_GetTxBytesCopiedOfConnectionTcpDyn(ConnectionTcpIdx);
  const PduInfoType *msg = DoIP_GetAddrMsgOfTxTcpMgtDyn(txTcpMgtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if header is not yet copied. */
  if ( (PduInfoPtr->SduLength != 0u) && (HdrCopied == FALSE) )
  {
    const PduLengthType bufIdx = (PduLengthType)(txBytesCopied - DoIP_GetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx));

    /* #20 Copy data from internal buffer to target buffer. */
    /* PRQA S 0310, 0314 1 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
    VStdLib_MemCpy(DOIP_A_P2VAR(void)PduInfoPtr->SduDataPtr, DOIP_A_P2CONST(void)&(DoIP_GetAddrIfTxBuf(                /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
      DoIP_GetIfTxBufStartIdxOfChannel(DoIP_GetChannelIdxOfTxTcpMgtDyn(txTcpMgtIdx))))[bufIdx],
      (uint32)PduInfoPtr->SduLength);

    txBytesCopied += PduInfoPtr->SduLength;
    DoIP_SetTxBytesCopiedOfConnectionTcpDyn(ConnectionTcpIdx, txBytesCopied);                                          /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }

  /* #30 Set available data length. */
  *AvailableDataPtr = (PduLengthType)(msg->SduLength - txBytesCopied);                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  DoIP_SetLastTxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *AvailableDataPtr);                                        /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
} /* DoIP_TxTcpQueue_CopyDiagReqIF() */
#endif /* DOIP_IF_API_ENABLED == STD_ON */

#if ( DOIP_NACK_APPEND_REQ == STD_ON )
/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyDiagAck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_TxTcpQueue_CopyDiagAck(                                             /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  boolean HdrCopied)                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal = BUFREQ_OK;
  const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx);
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
  DoIP_TxBytesCopiedOfConnectionTcpDynType txBytesCopied = DoIP_GetTxBytesCopiedOfConnectionTcpDyn(ConnectionTcpIdx);
  const PduInfoType *msg = DoIP_GetAddrMsgOfTxTcpMgtDyn(txTcpMgtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if header is not yet copied. */
  if ( (PduInfoPtr->SduLength != 0u) && (HdrCopied == FALSE) )
  {
    /* #20 Copy data from internal buffer to target buffer. */
    /* PRQA S 0310, 0314 1 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
    VStdLib_MemCpy(DOIP_A_P2VAR(void)PduInfoPtr->SduDataPtr, DOIP_A_P2CONST(void)DoIP_GetAddrDiagNAckBuf(              /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
      DoIP_GetDiagNAckBufStartIdxOfTester(testerIdx) +
      (txBytesCopied - DoIP_GetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx))), PduInfoPtr->SduLength);

    txBytesCopied += PduInfoPtr->SduLength;
    DoIP_SetTxBytesCopiedOfConnectionTcpDyn(ConnectionTcpIdx, txBytesCopied);                                          /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

    /* #30 Update control data structs if all data are copied to lower layer buffer. */
    if ( txBytesCopied == msg->SduLength )
    {
      DoIP_SetDiagNAckOffsetOfTesterDyn(testerIdx, 0u);                                                                /* SBSW_DOIP_RegisterTester */
    }
  }

  /* #40 Set available data length. */
  *AvailableDataPtr = (PduLengthType)(msg->SduLength - txBytesCopied);                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  DoIP_SetLastTxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *AvailableDataPtr);                                        /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

  return retVal;
} /* DoIP_TxTcpQueue_CopyDiagAck() */
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
# if ( DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u )
/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_CopyOemSpecific()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_CopyOemSpecific(                                                      /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfTxTcpMgtType QueueIdx,                                                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr,                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  boolean HdrCopied)                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + QueueIdx);
  DoIP_TxBytesCopiedOfConnectionTcpDynType txBytesCopied = DoIP_GetTxBytesCopiedOfConnectionTcpDyn(ConnectionTcpIdx);
  const PduInfoType *msg = DoIP_GetAddrMsgOfTxTcpMgtDyn(txTcpMgtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if header is not yet copied. */
  if ( (PduInfoPtr->SduLength != 0u) && (HdrCopied == FALSE) )
  {
    /* #20 Copy data from internal buffer to target buffer. */
    /* PRQA S 0310, 0314 2 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
    VStdLib_MemCpy(DOIP_A_P2VAR(void)PduInfoPtr->SduDataPtr, DOIP_A_P2CONST(void)DoIP_GetAddrOemPayloadTypeTcpBuf(     /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
      (txBytesCopied - DoIP_GetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx))), PduInfoPtr->SduLength);

    txBytesCopied += PduInfoPtr->SduLength;
    DoIP_SetTxBytesCopiedOfConnectionTcpDyn(ConnectionTcpIdx, txBytesCopied);                                          /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

    /* #30 Update control data structs if all data are copied to lower layer buffer. */
    if ( txBytesCopied == msg->SduLength )
    {
      DoIP_SetOemPayloadTypeTcpBufLen(0u);                                                                             /* SBSW_DOIP_OemPayloadType */
      DoIP_SetOemPayloadTypeTcpBufIsTx(FALSE);                                                                         /* SBSW_DOIP_OemPayloadType */
      DoIP_SetOemPayloadTypeTcpBuf2Con(DoIP_GetSizeOfConnection());                                                    /* SBSW_DOIP_OemPayloadType */
    }
  }

  /* #40 Set available data length. */
  *AvailableDataPtr = (PduLengthType)(msg->SduLength - txBytesCopied);                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  DoIP_SetLastTxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *AvailableDataPtr);                                        /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
} /* DoIP_TxTcpQueue_CopyOemSpecific() */
# endif /* DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u */
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_TransmitElement()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_TransmitElement(                                                      /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfTxTcpMgtType txTcpMgtQueIdx = DoIP_GetTxTcpMgtQueIdxOfConnectionTcpDyn(ConnectionTcpIdx);
  const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                               /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + txTcpMgtQueIdx);
  const PduInfoType *msg = DoIP_GetAddrMsgOfTxTcpMgtDyn(txTcpMgtIdx);

  /* ----- Implementation ----------------------------------------------- */
  DOIP_BEGIN_CRITICAL_SECTION();

  /* #10 Check if session is not yet active. */
  if ( !DoIP_IsTxTpSessionActiveOfConnectionTcpDyn(ConnectionTcpIdx) )
  {
    /* #20 Lock session since this function can be called reentrant. */
    DoIP_SetTxTpSessionActiveOfConnectionTcpDyn(ConnectionTcpIdx, TRUE);                                               /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

    /* #30 Check if there are pendig elements. */
    if ( DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(ConnectionTcpIdx) > 0u )
    {
      PduInfoType txTcpMgtMsg;

      txTcpMgtMsg.SduDataPtr = msg->SduDataPtr;
      txTcpMgtMsg.SduLength = msg->SduLength;

      DOIP_END_CRITICAL_SECTION();

      if ( SoAd_TpTransmit(DoIP_GetSoAdTxPduIdOfConnection(ConnectionTcpIdx), &txTcpMgtMsg) != E_OK )                  /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      {
        /* #40 Deaktivate session if transmission request failed. */
        DoIP_SetTxTpSessionActiveOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                          /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
      }
    }
    else
    {
      /* #50 Otherwise release lock. */
      DoIP_SetTxTpSessionActiveOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                            /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

      DOIP_END_CRITICAL_SECTION();
    }
  }
  else
  {
    DOIP_END_CRITICAL_SECTION();
  }
} /* DoIP_TxTcpQueue_TransmitElement() */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_RemoveElement()
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
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_RemoveElement(                                                        /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  Std_ReturnType Result)                                                                                               /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Implementation ----------------------------------------------- */
  DOIP_BEGIN_CRITICAL_SECTION();

  /* #10 Check if there are pendig elements. */
  if ( DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(ConnectionTcpIdx) > 0u )
  {
    const DoIP_SizeOfTxTcpMgtType txTcpMgtQueIdx = DoIP_GetTxTcpMgtQueIdxOfConnectionTcpDyn(ConnectionTcpIdx);
    const DoIP_SizeOfTxTcpMgtType txTcpMgtIdx = (DoIP_SizeOfTxTcpMgtType)(                                             /* INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt */
      DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx) + txTcpMgtQueIdx);
    const DoIP_SizeOfChannelType channelIdx = DoIP_GetChannelIdxOfTxTcpMgtDyn(txTcpMgtIdx);                            /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX_INC_INV */
    const DoIP_SizeOfTxTcpMgtType txTcpMgtSize = (DoIP_SizeOfTxTcpMgtType)(
      DoIP_GetTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
      DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx));

    /* #20 Reset Tx management structs. */
    DoIP_SetTxHdrBufLenOfTxTcpMgtDyn(txTcpMgtIdx, 0u);                                                                 /* SBSW_DOIP_TxTcpMgt */

    /* #30 Update Tx queue. */
    DoIP_DecTxTcpMgtQueLvlOfConnectionTcpDyn(ConnectionTcpIdx);                                                        /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    DoIP_IncTxTcpMgtQueIdxOfConnectionTcpDyn(ConnectionTcpIdx);                                                        /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    if ( DoIP_GetTxTcpMgtQueIdxOfConnectionTcpDyn(ConnectionTcpIdx) == txTcpMgtSize )
    {
      /* #40 Handle wrap around. */
      DoIP_SetTxTcpMgtQueIdxOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                  /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    }

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
# if ( DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u )
    /* #50 Release OEM specific payload type buffer (if enabled). */
    if ( DoIP_GetOemPayloadTypeTcpBuf2Con() == ConnectionTcpIdx )
    {
      DoIP_SetOemPayloadTypeTcpBufLen(0u);                                                                             /* SBSW_DOIP_OemPayloadType */
      DoIP_SetOemPayloadTypeTcpBufIsTx(FALSE);                                                                         /* SBSW_DOIP_OemPayloadType */
      DoIP_SetOemPayloadTypeTcpBuf2Con(DoIP_GetSizeOfConnection());                                                    /* SBSW_DOIP_OemPayloadType */
    }
# endif /* DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u */
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

    /* #60 Finish TP session. */
    DoIP_SetTxTpSessionActiveOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                              /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

    DoIP_SetTxBytesCopiedOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                     /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

    /* #70 Check if channel is valid. */
    if ( channelIdx != DoIP_GetSizeOfChannel() )
    {
      const DoIP_PduRTxConfPduIdOfChannelType txConfPduId = DoIP_GetPduRTxConfPduIdOfChannel(channelIdx);

      DoIP_SetTxMsgLenOfChannelDyn(channelIdx, 0u);                                                                    /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

      DoIP_SetChannelIdxOfTxTcpMgtDyn(txTcpMgtIdx, DoIP_GetSizeOfChannel());                                           /* SBSW_DOIP_TxTcpMgt */

      DOIP_END_CRITICAL_SECTION();

      /* #80 Call TxConfirmation depending on there API type. */
#if ( DOIP_IF_API_ENABLED == STD_ON )
      if ( DoIP_GetApiTypeOfChannel(channelIdx) == DOIP_API_TYPE_IF )
      {
        /* #90 Check if TxConfirmation is enabled for IF channel. */
        if ( txConfPduId != DOIP_NO_PDURTXCONFPDUIDOFCHANNEL )
        {
          PduR_DoIPIfTxConfirmation(txConfPduId);
        }
      }
      else
#endif /* DOIP_IF_API_ENABLED == STD_ON */
      {
        PduR_DoIPTpTxConfirmation(txConfPduId, Result);
      }
    }
    else
    {
      DOIP_END_CRITICAL_SECTION();
    }
  }
  else
  {
    DOIP_END_CRITICAL_SECTION();
  }
} /* DoIP_TxTcpQueue_RemoveElement() */

/**********************************************************************************************************************
 *  DoIP_TxTcpQueue_HandleTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_TxTcpQueue_HandleTransmit(void)                                                  /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_ConnectionTcpIterType connectionTcpIdx;

  /* ----- Implementation ----------------------------------------------- */
  for ( connectionTcpIdx = 0u;
        connectionTcpIdx < DoIP_GetSizeOfConnectionTcp();
        connectionTcpIdx++ )
  {
    /* #10 Check for all connections if there are online. */
    if ( DoIP_GetSoConStateOfConnectionDyn(connectionTcpIdx) == SOAD_SOCON_ONLINE )
    {
#if ( DOIP_TP_OPTIMIZED_ENABLED == STD_ON )
      uint8_least txIdx;

      /* #20 Handle configured number of transmission requests within one main function cycle (if enabled). */
      for ( txIdx = 0u;
            txIdx < DOIP_TCP_TX_QUEUE_PROCESS_LIMIT;
            txIdx++ )
#endif /* DOIP_TP_OPTIMIZED_ENABLED == STD_ON */
      {
        const DoIP_SizeOfTxTcpMgtType txTcpMgtQueLvl = DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(connectionTcpIdx);

        if ( txTcpMgtQueLvl > 0u )
        {
          /* #30 Try to transmit element if there are pending elements. */
          DoIP_TxTcpQueue_TransmitElement((DoIP_SizeOfConnectionTcpType)connectionTcpIdx);
        }

#if ( DOIP_TP_OPTIMIZED_ENABLED == STD_ON )
        if ( (DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(connectionTcpIdx) == 0u) ||
             (DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(connectionTcpIdx) == txTcpMgtQueLvl) )
        {
          /* #40 Break if queue is empty or queue level has not been changed (if enabled). */
          break;
        }
#endif /* DOIP_TP_OPTIMIZED_ENABLED == STD_ON */
      }
    }
  }
} /* DoIP_TxTcpQueue_HandleTransmit() */

/**********************************************************************************************************************
 *  DoIP_RxTcpGen_CopyGenHdr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpGen_CopyGenHdr(                                                   /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr)                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  DoIP_RxMsgOffsetOfConnectionTcpDynType rxMsgOffset = DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy generic header if not yet copied. */
  if ( rxMsgOffset < DOIP_GEN_HDR_LEN_BYTE )
  {
    const uint32 bytesToCopy = PduInfoPtr->SduLength;

    /* PRQA S 0310, 0314 2 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
    VStdLib_MemCpy(DOIP_A_P2VAR(void)DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx) +  /* SBSW_DOIP_RxHdrBuf_AND_CONST_POINTER_FORWARD */
      rxMsgOffset), DOIP_A_P2CONST(void)PduInfoPtr->SduDataPtr, bytesToCopy);

    rxMsgOffset += bytesToCopy;
    *ReadDataLenPtr += (PduLengthType)bytesToCopy;                                                                     /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    DoIP_SetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx, rxMsgOffset);                                              /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }

  /* #20 Check if generic header is received completly and set buffer size. */
  if ( rxMsgOffset >= DOIP_GEN_HDR_LEN_BYTE )
  {
    retVal = E_OK;
    *BufferSizePtr = 0u;                                                                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                         /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }
  else
  {
    *BufferSizePtr = (PduLengthType)(DOIP_GEN_HDR_LEN_BYTE - DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx)); /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                         /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }

  return retVal;
} /* DoIP_RxTcpGen_CopyGenHdr() */

/**********************************************************************************************************************
 *  DoIP_RxTcpGen_CopyDataToHeaderBuffer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpGen_CopyDataToHeaderBuffer(                                                 /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr,                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  uint32 BytesToCopy)                                                                                                  /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_RxMsgOffsetOfConnectionTcpDynType rxMsgOffset = DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx);
  uint32 tmpBytesToCopy = BytesToCopy;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check and set max bytes to copy. */
  if ( tmpBytesToCopy > ((uint32)(PduInfoPtr->SduLength) - (uint32)(*ReadDataLenPtr)) )
  {
    tmpBytesToCopy = ((uint32)(PduInfoPtr->SduLength) - (uint32)(*ReadDataLenPtr));
  }

  /* #20 Copy data to header buffer if there are bytes to copy. */
  if ( tmpBytesToCopy > 0u )
  {
    /* PRQA S 0310, 0314 2 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
    VStdLib_MemCpy(DOIP_A_P2VAR(void)DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx) +  /* SBSW_DOIP_RxHdrBuf_AND_CONST_POINTER_FORWARD */
      rxMsgOffset), DOIP_A_P2CONST(void)&PduInfoPtr->SduDataPtr[*ReadDataLenPtr], tmpBytesToCopy);

    *ReadDataLenPtr += (PduLengthType)tmpBytesToCopy;                                                                  /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    DoIP_SetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx, (rxMsgOffset + tmpBytesToCopy));                           /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }
} /* DoIP_RxTcpGen_CopyDataToHeaderBuffer() */

/**********************************************************************************************************************
 *  DoIP_RxTcp_HandleCopyRxData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_RxTcp_HandleCopyRxData(                                             /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr)                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  const DoIP_RxMsgOffsetOfConnectionTcpDynType rxMsgOffset = DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx);
#if ( DOIP_NACK_APPEND_REQ == STD_ON )
  const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx);
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check plausibility of all input parameters and states. */
#if ( DOIP_SUPPORT_SHUTDOWN == STD_ON )
  /* Check initialization state */
  /* with respect to SHUTDOWN state check DET only against UNINIT state and check callbacks against INIT state */
  if ( DoIP_State != DOIP_STATE_INIT )
  { /* DoIP_State is not INIT (it could be SHUTDOWN) */
    /* Continue if DoIP_State is shutdown (if enabled). */
    /* nothing to do here */
  }
  else
#endif /* DOIP_SUPPORT_SHUTDOWN == STD_ON */
  /* Check socket connection state */
  if ( DoIP_GetSoConStateOfConnectionDyn(ConnectionTcpIdx) != SOAD_SOCON_ONLINE )
  { /* socket connection is not online */
    /* nothing to do here */
  }
  /* Check TP session state */
  else if ( !DoIP_IsRxTpSessionActiveOfConnectionTcpDyn(ConnectionTcpIdx) )
  { /* TP session is not active */
    /* nothing to do here */
  }
  /* Check if socket connection is requested to be closed */
  else if ( DoIP_IsSoConClosingOfConnectionDyn(ConnectionTcpIdx) )
  { /* socket connection closing is requested - do not handle more than pending Rx data of message */
    *BufferSizePtr = 0u;                                                                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                     /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    retVal = BUFREQ_OK;
  }
#if ( DOIP_PROVIDE_CANCEL_RECEIVE_API == STD_ON )
  /* Check TP cancellation */
  else if ( DoIP_IsRxTpCancelRequestedOfConnectionTcpDyn(ConnectionTcpIdx) )
  { /* TP cancellation is ongoing */
    /* nothing to do here */
  }
#endif /* DOIP_PROVIDE_CANCEL_RECEIVE_API == STD_ON */
#if ( DOIP_NACK_APPEND_REQ == STD_ON )
  /* the feature to send previously received user data cannot be used if tester could not be determined */
  else if ( (testerIdx != DoIP_GetSizeOfTester()) && (rxMsgOffset == 0u) &&
            (DoIP_GetDiagNAckOffsetOfTesterDyn(testerIdx) > 0u) )
  { /* diagnostic message acknowledge is pending - do not accept new data until acknowledge is sent */
    *BufferSizePtr = 0u;                                                                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                     /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    retVal = BUFREQ_OK;
  }
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */
  /* SoAd queries Rx buffer size */
  else if ( (PduInfoPtr->SduLength == 0u) && (rxMsgOffset < DOIP_GEN_HDR_LEN_BYTE) )
  { /* generic header was not completely received */
    /* do only provide buffer for generic header */
    *BufferSizePtr = (PduLengthType)(DOIP_GEN_HDR_LEN_BYTE - rxMsgOffset);                                             /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                         /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    retVal = BUFREQ_OK;
  }
  /* SoAd has Rx data */
  else if ( (PduInfoPtr->SduLength != 0u) &&
            (PduInfoPtr->SduDataPtr == NULL_PTR) )
  {
    *ErrorIdPtr = DOIP_E_INVALID_PARAMETER;                                                                            /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    /* nothing to do here */
  }
  /* SoAd has Rx data AND check length */
  else if ( (PduInfoPtr->SduLength != 0u) &&
            (PduInfoPtr->SduLength > DoIP_GetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx)) )
  { /* unexpected length */
    /* nothing to do here */
  }
  else
  {
    /* #20 Process request.*/
    DoIP_RxTcp_HandleCopyRxDataCopy(ConnectionTcpIdx, PduInfoPtr, BufferSizePtr, ErrorIdPtr);                          /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    retVal = BUFREQ_OK;
  }

  return retVal;
} /* DoIP_RxTcp_HandleCopyRxData() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  DoIP_RxTcp_HandleCopyRxDataCopy()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcp_HandleCopyRxDataCopy(                                                      /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr)                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  PduLengthType readDataLen = 0u;
  const DoIP_SizeOfTxTcpMgtType txTcpMgtSize = (DoIP_SizeOfTxTcpMgtType)(
    DoIP_GetTxTcpMgtEndIdxOfConnectionTcp(ConnectionTcpIdx) -
    DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(ConnectionTcpIdx));
#if ( DOIP_TCP_RX_MULTI_MSG == STD_ON )
# if ( DOIP_NACK_APPEND_REQ == STD_ON )
  const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx);
# endif /* DOIP_NACK_APPEND_REQ == STD_ON */
#endif /* DOIP_TCP_RX_MULTI_MSG == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset inactivity timer if routing activation is active. */
  if ( DoIP_GetActivStateOfConnectionTcpDyn(ConnectionTcpIdx) == DOIP_ROUT_ACTIV_STATE_ACTIVATED )
  {
    DoIP_SetInactivCntOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                        /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }

  /* #20 Copy header data. */
  if ( DoIP_RxTcpGen_CopyGenHdr(ConnectionTcpIdx, PduInfoPtr, BufferSizePtr, &readDataLen) == E_OK )                   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  {
    /* #30 Copy payload data. */
    DoIP_RxTcp_HandleCopyRxDataCopyBody(ConnectionTcpIdx, PduInfoPtr, BufferSizePtr, &readDataLen, ErrorIdPtr);        /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }

  /* #40 Block buffer if message is not processed completely. */
  if ( DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx) == 0u )
  {
#if ( DOIP_TCP_RX_MULTI_MSG == STD_ON )
# if ( DOIP_NACK_APPEND_REQ == STD_ON )
    if ( testerIdx != DoIP_GetSizeOfTester() )
    {
      if ( DoIP_GetDiagNAckOffsetOfTesterDyn(testerIdx) > 0u )
      {
        /* #50 Do not accept new data until acknowledge is pending (if enabled). */
        *BufferSizePtr = 0u;                                                                                           /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
        DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                 /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
      }
    }
    else
# endif /* DOIP_NACK_APPEND_REQ == STD_ON */
    {
      /* #60 Provide buffer size for previously received user data if tester could be determined (if enabled). */
      *BufferSizePtr = DOIP_GEN_HDR_LEN_BYTE;                                                                          /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
      DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, DOIP_GEN_HDR_LEN_BYTE);                                /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    }
#else
    *BufferSizePtr = 0u;                                                                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                     /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
#endif /* DOIP_TCP_RX_MULTI_MSG == STD_ON */
  }
  else if ( DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(ConnectionTcpIdx) >= (txTcpMgtSize - 1u) )
  { /* high Tx queue fill level - slow down Rx path */
    *BufferSizePtr = 0u;                                                                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                     /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }
  else if ( (DoIP_GetActivStateOfConnectionTcpDyn(ConnectionTcpIdx) == DOIP_ROUT_ACTIV_STATE_AUTH_PENDING) ||
            (DoIP_GetActivStateOfConnectionTcpDyn(ConnectionTcpIdx) == DOIP_ROUT_ACTIV_STATE_CONF_PENDING) )
  { /* activation state is pending */
    /* stop reception until state changes */
    *BufferSizePtr = 0u;                                                                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                     /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }
  else
  {
    /* nothing to do here */
  }
} /* DoIP_RxTcp_HandleCopyRxDataCopy() */

/**********************************************************************************************************************
 *  DoIP_RxTcp_HandleCopyRxDataCopyBody()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcp_HandleCopyRxDataCopyBody(                                                  /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr,                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr)                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_RxMsgOffsetOfConnectionTcpDynType rxMsgOffset = DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx);
  const DoIP_RxHdrBufType *rxHdrBuf = DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx));
  uint8  hdrVer;
  uint8  hdrInvVer;
  uint16 hdrType;
  uint32 hdrLen;

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT8(rxHdrBuf, 0u, hdrVer);                                                                              /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  IPBASE_GET_UINT8(rxHdrBuf, 1u, hdrInvVer);                                                                           /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  /* #10 Send Nack if header pattern is invalid. */
  if ( ((uint8)(hdrVer) != DOIP_PROTOCOL_VERSION_2012) || ((uint8)(~hdrInvVer) != DOIP_PROTOCOL_VERSION_2012) )
  {
    (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_FORMAT, 0u, 0u, NULL_PTR, TRUE); /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  else
  {
    IPBASE_GET_UINT16(rxHdrBuf, 2u, hdrType);                                                                          /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
    IPBASE_GET_UINT32(rxHdrBuf, 4u, hdrLen);                                                                           /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

    /* #20 Otherwise check if routing activation is busy than process routing activation later. */
    if ( (hdrType == DOIP_HDR_TYPE_ROUT_ACTIV_REQ) &&
         (DoIP_GetConnectionTcpIdxOfRoutActivHandler(0u) != DoIP_GetSizeOfConnectionTcp()) )
    {
      *BufferSizePtr = 0u;                                                                                             /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
      DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                   /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    }
    else
    {
      const uint64 msgLength = (uint64)hdrLen + DOIP_GEN_HDR_LEN_BYTE;

      /* #30 Otherwise check if message shall be skipped. */
      if ( DoIP_IsSkipRxMsgOfConnectionTcpDyn(ConnectionTcpIdx) )
      {
#if ( DOIP_NACK_APPEND_REQ == STD_ON )
        /* #40 Append Nack data (if enabled). */
        DoIP_RxTcp_HandleCopyRxDataAppendNack(ConnectionTcpIdx, PduInfoPtr, ReadDataLenPtr);                           /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */
        if ( (msgLength - rxMsgOffset) > ((uint64)(PduInfoPtr->SduLength) - (uint64)(*ReadDataLenPtr)) )
        {
          /* #50 Wait until message is received completely. */
          uint32 bufSize = (uint32)(msgLength - rxMsgOffset);                                                          /* INTERNAL_NOTE_DOIP_CAST_HEADER_ALREADY_RECEIVED */
          rxMsgOffset += ((DoIP_RxMsgOffsetOfConnectionTcpDynType)(PduInfoPtr->SduLength) -
                          (DoIP_RxMsgOffsetOfConnectionTcpDynType)(*ReadDataLenPtr));
          DoIP_Util_CheckBufferSizeAndModify(bufSize, BufferSizePtr);                                                  /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
          *ReadDataLenPtr = (PduLengthType)PduInfoPtr->SduLength;                                                      /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
          DoIP_SetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx, rxMsgOffset);                                        /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
          DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                   /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
        }
        else
        {
          /* #60 Otherwise finish message. */
          DoIP_TxTcp_FinishTransmit(ConnectionTcpIdx);

          *BufferSizePtr = 0u;                                                                                         /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
          *ReadDataLenPtr = (PduLengthType)PduInfoPtr->SduLength;                                                      /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
          DoIP_SetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                 /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
          DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                               /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
          DoIP_SetSkipRxMsgOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                                /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
        }
      }
      else
      {
        /* #70 Otherwise handle message depending on there header type. */
        switch(hdrType)
        {
          case DOIP_HDR_TYPE_ROUT_ACTIV_REQ:
          {
            DoIP_RxTcpRout_HandleRoutingActivationReq(ConnectionTcpIdx, PduInfoPtr, BufferSizePtr, ReadDataLenPtr,     /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
              ErrorIdPtr);
            break;
          }
          case DOIP_HDR_TYPE_ALIVE_CHECK_RES:
          {
            DoIP_RxTcpAlive_HandleAliveCheckRes(ConnectionTcpIdx, PduInfoPtr, BufferSizePtr, ReadDataLenPtr);          /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
            break;
          }
          case DOIP_HDR_TYPE_DIAG_REQ:
          {
            DoIP_RxTcpDiag_HandleDiagnosticMessage(ConnectionTcpIdx, PduInfoPtr, BufferSizePtr, ReadDataLenPtr);       /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
            break;
          }
          case DOIP_HDR_TYPE_GEN_NACK:
          case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ:
#if ( DOIP_VEHICLE_IDENT_EID_SUPPORT == STD_ON )
          case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_EID:
#endif /* DOIP_VEHICLE_IDENT_EID_SUPPORT == STD_ON */
          case DOIP_HDR_TYPE_VEHICLE_IDENT_REQ_VIN:
          case DOIP_HDR_TYPE_VEHICLE_ANNOUNCEMENT:
          case DOIP_HDR_TYPE_ROUT_ACTIV_RES:
          case DOIP_HDR_TYPE_ALIVE_CHECK_REQ:
          case DOIP_HDR_TYPE_ENTITY_STATE_REQ:
          case DOIP_HDR_TYPE_ENTITY_STATE_RES:
          case DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_REQ:
          case DOIP_HDR_TYPE_DIAG_POWER_MODE_INFO_RES:
          case DOIP_HDR_TYPE_DIAG_ACK:
          case DOIP_HDR_TYPE_DIAG_NACK:
          { /* not relevant payload type */
            DoIP_SetSkipRxMsgOfConnectionTcpDyn(ConnectionTcpIdx, TRUE);                                               /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
            break;
          }
          default:
          { /* unknown payload type */
#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
            DoIP_RxTcpOem_HandleOemPayloadTypes(ConnectionTcpIdx, PduInfoPtr, BufferSizePtr, ReadDataLenPtr);          /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
#else
            /* Send error if payload type are unknown. */
            DoIP_SetSkipRxMsgOfConnectionTcpDyn(ConnectionTcpIdx, TRUE);                                               /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
            (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx,                                                                /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
              DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_TYPE, 0u, 0u, NULL_PTR, FALSE);
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */
            break;
          }
        }
      }

      /* #80 Set buffer size to receive entire message in next function call if message shall be skipped. */
      if ( DoIP_IsSkipRxMsgOfConnectionTcpDyn(ConnectionTcpIdx) )
      {
        uint32 bufSize = (uint32)(msgLength - DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx));                /* INTERNAL_NOTE_DOIP_CAST_HEADER_ALREADY_RECEIVED */
        DoIP_Util_CheckBufferSizeAndModify(bufSize, BufferSizePtr);                                                    /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
        DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                     /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
      }
    }
  }
} /* DoIP_RxTcp_HandleCopyRxDataCopyBody() */ /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#if ( DOIP_NACK_APPEND_REQ == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcp_HandleCopyRxDataAppendNack()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcp_HandleCopyRxDataAppendNack(                                                /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2CONST(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr)                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 hdrType;

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT16(DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx)), 2u, hdrType);     /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  /* #10 Check header type. */
  if ( hdrType == DOIP_HDR_TYPE_DIAG_REQ )
  {
    if ( (DoIP_GetTpTxPreHdrTypeOfConnectionTcpDyn(ConnectionTcpIdx) == DOIP_HDR_TYPE_DIAG_NACK) ||
         (DoIP_GetTpTxPreHdrTypeOfConnectionTcpDyn(ConnectionTcpIdx) == DOIP_HDR_TYPE_DIAG_ACK) )
    {
      DoIP_RxTcpDiag_AppendNackData(ConnectionTcpIdx, PduInfoPtr, ReadDataLenPtr);                                     /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
    }
  }
} /* DoIP_RxTcp_HandleCopyRxDataAppendNack() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleRoutingActivationReq()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleRoutingActivationReq(                                            /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr,                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr)                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 bytesToCopy;
  uint32 hdrLen;

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT32(DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx)), 4u, hdrLen);      /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  /* #10 Check message lengths and send nack. */
  if ( hdrLen > DOIP_MAX_REQUEST_BYTES )
  {
    DoIP_SetSkipRxMsgOfConnectionTcpDyn(ConnectionTcpIdx, TRUE);                                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, 0u, 0u, NULL_PTR,       /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      FALSE);
  }
  else if ( (hdrLen != (DOIP_ROUT_ACTIV_REQ_MIN_LEN_BYTE)) &&
            (hdrLen != (DOIP_ROUT_ACTIV_REQ_MIN_LEN_BYTE + DOIP_ROUT_ACTIV_REQ_OEM_LEN_BYTE)) )
  {
    (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, 0u, 0u, NULL_PTR, TRUE); /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  else
  {
    const uint64 msgLength = (uint64)hdrLen + DOIP_GEN_HDR_LEN_BYTE;

    bytesToCopy = (uint32)(msgLength - DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx));

    /* #20 Otherwise copy data to header buffer. */
    DoIP_RxTcpGen_CopyDataToHeaderBuffer(ConnectionTcpIdx, PduInfoPtr, ReadDataLenPtr, bytesToCopy);                   /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */

    if ( DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx) == msgLength )
    {
      /* #30 Handle message if message is now copied completely. */
      DoIP_RxTcpRout_HandleCopiedRoutingActivationReq(ConnectionTcpIdx, ErrorIdPtr);                                   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    }
    else
    {
      /* #40 Otherwise set buffer size to length of pending message part. */
      uint32 bufSize = (uint32)(msgLength - DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx));                  /* INTERNAL_NOTE_DOIP_CAST_HEADER_ALREADY_RECEIVED */
      DoIP_Util_CheckBufferSizeAndModify(bufSize, BufferSizePtr);                                                      /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    }
  }
} /* DoIP_RxTcpRout_HandleRoutingActivationReq() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleCopiedRoutingActivationReq()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleCopiedRoutingActivationReq(                                      /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr)                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfTesterType testerIdx = DoIP_GetSizeOfTester();
  DoIP_SizeOfRoutingActivationType routActIdx = DoIP_GetSizeOfRoutingActivation();
  const DoIP_RxHdrBufType *rxHdrBuf = DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx));
  uint16 testerAddr;
  uint8 activType;
  uint8 resCode = DOIP_ROUT_ACTIV_RES_CODE_INV_ACTIV_TYPE;

  /* ----- Implementation ----------------------------------------------- */
  DoIP_SetInactivCntOfConnectionTcpDyn(ConnectionTcpIdx, 0u);       /* reset inactivity timer */                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  DoIP_SetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx, 0u);      /* finish message */                               /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  DoIP_SetConnectionTcpIdxOfRoutActivHandler(0u, ConnectionTcpIdx); /* lock routing activation handler */              /* SBSW_DOIP_RoutActivHandler */

  IPBASE_GET_UINT16(rxHdrBuf, DOIP_GEN_HDR_LEN_BYTE, testerAddr);                                                      /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  IPBASE_GET_UINT8(rxHdrBuf, (DOIP_GEN_HDR_LEN_BYTE + DOIP_ADDR_LEN_BYTE), activType);                                 /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  /* #10 Send nack if no tester with received tester address is configured. */
  if ( DoIP_RxTcpRout_GetTesterIdxByTesterAddr(testerAddr, &testerIdx) == E_NOT_OK )                                   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  {
    (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_ROUT_ACTIV_RES, testerAddr,                              /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      DOIP_ROUT_ACTIV_RES_CODE_UNKNOWN_TESTER, testerIdx, NULL_PTR, TRUE);
  }
  /* #20 Otherwise send nack if another tester is active on connection. */
  else if ( DoIP_RxTcpRout_CheckForRegisteredTester(ConnectionTcpIdx, testerIdx) == E_NOT_OK )
  {
    (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_ROUT_ACTIV_RES, testerAddr,                              /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      DOIP_ROUT_ACTIV_RES_CODE_DIFFERENT_TESTER, testerIdx, NULL_PTR, TRUE);
  }
  /* #30 Otherwise send nack if no routing activation with received activation type is configured. */
  else if ( DoIP_RxTcpRout_GetRoutingActivationIdxByActivationType(ConnectionTcpIdx, testerIdx, activType,             /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    &routActIdx, &resCode) == E_NOT_OK )
  {
    (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_ROUT_ACTIV_RES, testerAddr,                              /* SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER_FORWARD */
      resCode, testerIdx, NULL_PTR, TRUE);
  }
  /* #40 Otherwise assume that the routing activation request is valid. */
  else
  {
    DoIP_SetTesterIdxOfRoutActivHandler(0u, testerIdx);                                                                /* SBSW_DOIP_RoutActivHandler */
    DoIP_SetTesterAddrOfRoutActivHandler(0u, testerAddr);                                                              /* SBSW_DOIP_RoutActivHandler */
    DoIP_SetRoutingActivationIdxOfRoutActivHandler(0u, routActIdx);                                                    /* SBSW_DOIP_RoutActivHandler */

    /* #50 Handle the OEM specific part. */
    DoIP_RxTcpRout_HandleCopiedRoutingActivationReqOem(ConnectionTcpIdx);

    /* #60 Check if there is a free connection for an additional tester and trigger alive check if not. */
    if ( DoIP_RxTcpRout_CheckConnectionNum(ConnectionTcpIdx, testerAddr, ErrorIdPtr) == E_OK )                         /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    {
      /* #70 Perform routing activation if an already or not yet activated tester is found. */
      DoIP_RxTcpRout_PerformRoutingActivation();
    }
  }
} /* DoIP_RxTcpRout_HandleCopiedRoutingActivationReq() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleCopiedRoutingActivationReqOem()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleCopiedRoutingActivationReqOem(                                   /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 hdrLen;
  uint32 oemSpecReq;
  const DoIP_RxHdrBufStartIdxOfConnectionTcpType rxHdrBufStartIdx =
    DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx);

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT32(DoIP_GetAddrRxHdrBuf(rxHdrBufStartIdx), 4u, hdrLen);                                               /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  /* #10 Check header length if the OEM specific part is available. */
  if ( hdrLen == DOIP_ROUT_ACTIV_REQ_MAX_LEN_BYTE )
  {
    /* #20 Initalize OEM specific part for response. */
    DoIP_SetOemSpecResOfRoutActivHandler(0u, 0u);                                                                      /* SBSW_DOIP_RoutActivHandler */

    /* #30 Store OEM specific part for request. */
    IPBASE_GET_UINT32(DoIP_GetAddrRxHdrBuf(rxHdrBufStartIdx + (DOIP_GEN_HDR_LEN_BYTE + 7u)), 0u, oemSpecReq);          /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

    DoIP_SetOemSpecReqOfRoutActivHandler(0u, oemSpecReq);                                                              /* SBSW_DOIP_RoutActivHandler */

    DoIP_SetOemSpecUsedOfRoutActivHandler(0u, TRUE);                                                                   /* SBSW_DOIP_RoutActivHandler */
  }
  else
  {
    DoIP_SetOemSpecUsedOfRoutActivHandler(0u, FALSE);                                                                  /* SBSW_DOIP_RoutActivHandler */
  }
} /* DoIP_RxTcpRout_HandleCopiedRoutingActivationReqOem() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_CheckForRegisteredTester()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_CheckForRegisteredTester(                                    /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfTesterType TesterIdx)                                                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there is an active tester. */
  if ( testerIdx != DoIP_GetSizeOfTester() )
  {
    /* #20 Check if there is an other active tester. */
    if ( testerIdx != TesterIdx )
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* DoIP_RxTcpRout_CheckForRegisteredTester() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_GetRoutingActivationIdxByActivationType()
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
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_GetRoutingActivationIdxByActivationType(                     /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfTesterType TesterIdx,                                                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint8 ActivationType,                                                                                                /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  P2VAR(DoIP_SizeOfRoutingActivationType, AUTOMATIC, DOIP_APPL_VAR) RoutActIdxPtr,                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ResponseCodePtr)                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  DoIP_RoutingActivationIndIterType routingActivationIndIdx;
  DoIP_SizeOfRoutingActivationType routingActivationIdxTmp;
  uint8 responseCode = DOIP_ROUT_ACTIV_RES_CODE_INV_ACTIV_TYPE;
  boolean stopIteration = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all routing activations of the requested tester. */
  for ( routingActivationIndIdx = DoIP_GetRoutingActivationIndStartIdxOfTester(TesterIdx);
    routingActivationIndIdx < DoIP_GetRoutingActivationIndEndIdxOfTester(TesterIdx);
    routingActivationIndIdx++ )
  {
    routingActivationIdxTmp = DoIP_GetRoutingActivationInd(routingActivationIndIdx);

    /* #20 Check if the routing activation number is equal to the received activation type. */
    if ( DoIP_GetRoutingActivationNumOfRoutingActivation(routingActivationIdxTmp) == ActivationType )
    {
      /* #30 Check if the connection is secured. */
      if ( DoIP_IsSecurityRequiredOfConnectionTcp(ConnectionTcpIdx) )
      {
        /* #40 Prepare to return the routing activation index. */
        *RoutActIdxPtr = routingActivationIdxTmp;                                                                      /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
        retVal = E_OK;

        /* #50 Indicate to stop iteration if routing activation requires security. */
        if ( DoIP_IsSecurityRequiredOfRoutingActivation(routingActivationIdxTmp) )
        {
          stopIteration = TRUE;
        }
      }
      /* #60 Otherwise handle the routing activation if connection is not secured. */
      else
      {
        /* #70 Store negative response code temporarily if routing activation requires a secured connection. */
        if ( DoIP_IsSecurityRequiredOfRoutingActivation(routingActivationIdxTmp) )
        {
          responseCode = DOIP_ROUT_ACTIV_RES_CODE_REQUIRE_SECURE;
        }
        /* #80 Otherwise prepare to return the routing activation index and indicate to stop iteration. */
        else
        {
          *RoutActIdxPtr = routingActivationIdxTmp;                                                                    /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
          retVal = E_OK;
          stopIteration = TRUE;
        }
      }
    }

    /* #90 Stop iteration if required. */
    if ( stopIteration == TRUE )
    {
      break;
    }
  }

  /* #100 Set the response code if no routing activation could be found. */
  if ( retVal == E_NOT_OK )
  {
    *ResponseCodePtr = responseCode;                                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  }

  return retVal;
} /* DoIP_RxTcpRout_GetRoutingActivationIdxByActivationType() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_CheckConnectionNum()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_CheckConnectionNum(                                          /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 TesterAddr,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr)                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_RxTcpRout_GetConnectionIdxOfTesterAddr(TesterAddr);

  /* ----- Implementation ----------------------------------------------- */
  if ( connectionTcpIdx == ConnectionTcpIdx )
  {
    /* #10 Check if tester is already connected. */
    retVal = E_OK;
  }
  else if ( connectionTcpIdx != DoIP_GetSizeOfConnectionTcp() )
  {
    /* #20 Trigger alive check on single connection if connection is in use. */
    DoIP_RxTcpRout_TriggerAliveCheckSingleConnection(connectionTcpIdx, ErrorIdPtr);                                    /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }
  else if ( DoIP_RxTcpRout_GetAvailableSockNum(DoIP_GetConnectionGroupIdxOfConnectionTcp(ConnectionTcpIdx)) == 0u )
  {
    /* #30 Trigger alive check on all connections if there is no free socket. */
    DoIP_RxTcpRout_TriggerAliveCheckAllConnections(ConnectionTcpIdx, ErrorIdPtr);                                      /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }
  else
  { /* tester is not active on a different socket and a TCP_DATA socket is available */
    retVal = E_OK;
  }

  return retVal;
} /* DoIP_RxTcpRout_CheckConnectionNum() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_TriggerAliveCheckSingleConnection()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_TriggerAliveCheckSingleConnection(                                     /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr) /* PRQA S 3673 */ /* MD_DoIP_16.7 */                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Implementation ----------------------------------------------- */
  if ( DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_ALIVE_CHECK_REQ, 0u, 0u, 0u, NULL_PTR, FALSE) == E_OK )     /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  {
    /* #10 Load alive check timer if alive check could be send. */
    DoIP_SetAliveCheckCntOfRoutActivHandler(0u, DOIP_ALIVE_CHECK_WAIT);                                                /* SBSW_DOIP_RoutActivHandler */
    DoIP_SetConnectionTcpIdxOfAliveCheckList(0u, ConnectionTcpIdx);                                                    /* SBSW_DOIP_AliveCheckList */
    DoIP_SetAliveCheckElemNumOfRoutActivHandler(0u, 1u);                                                               /* SBSW_DOIP_RoutActivHandler */
  }
  else
  {
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
    /* #20 Otherwise set error (if enabled). */
    *ErrorIdPtr = DOIP_E_NOBUFS;                                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
#else
    DOIP_DUMMY_STATEMENT(ErrorIdPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  }
} /* DoIP_RxTcpRout_TriggerAliveCheckSingleConnection() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_TriggerAliveCheckAllConnections()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_TriggerAliveCheckAllConnections(                                       /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(uint8, AUTOMATIC, DOIP_APPL_VAR) ErrorIdPtr) /* PRQA S 3673 */ /* MD_DoIP_16.7 */                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfAliveCheckListType aliveCheckListIdx = 0u;
  DoIP_ConnectionTcpIterType connectionTcpIdx;

  /* ----- Implementation ----------------------------------------------- */
  for ( connectionTcpIdx = 0u;
        connectionTcpIdx < DoIP_GetSizeOfConnectionTcp();
        connectionTcpIdx++ )
  {
    if ( (DoIP_GetLocalAddrIdxOfConnection(connectionTcpIdx) == DoIP_GetLocalAddrIdxOfConnection(ConnectionTcpIdx)) &&
         (DoIP_GetTesterIdxOfConnectionTcpDyn(connectionTcpIdx) != DoIP_GetSizeOfTester()) )
    {
      /* #10 Issue alive check for all valid sockets. */
      if ( DoIP_TxTcp_Transmit((DoIP_SizeOfConnectionType)connectionTcpIdx, DOIP_HDR_TYPE_ALIVE_CHECK_REQ, 0u, 0u, 0u, /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        NULL_PTR, FALSE) == E_OK )
      {
        DoIP_SetConnectionTcpIdxOfAliveCheckList(aliveCheckListIdx, (DoIP_SizeOfConnectionTcpType)connectionTcpIdx);   /* SBSW_DOIP_AliveCheckList */
        aliveCheckListIdx++;
      }
      else
      {
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
        /* #20 Indicate error (if enabled). */
        *ErrorIdPtr = DOIP_E_NOBUFS;                                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
#else
        DOIP_DUMMY_STATEMENT(ErrorIdPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
      }
    }
  }

  /* #30 Load alive check timer. */
  DoIP_SetAliveCheckCntOfRoutActivHandler(0u, DOIP_ALIVE_CHECK_WAIT);                                                  /* SBSW_DOIP_RoutActivHandler */
  /* #40 Set number of send alive checks. */
  DoIP_SetAliveCheckElemNumOfRoutActivHandler(0u, aliveCheckListIdx);                                                  /* SBSW_DOIP_RoutActivHandler */
} /* DoIP_RxTcpRout_TriggerAliveCheckAllConnections() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_GetTesterIdxByTesterAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_GetTesterIdxByTesterAddr(                                    /* INTERNAL_NOTE_SBSW_OK */
  uint16 TesterAddr,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  P2VAR(DoIP_SizeOfTesterType, AUTOMATIC, DOIP_APPL_VAR) TesterIdx)                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  DoIP_TesterIterType testerIdx;

  /* ----- Implementation ----------------------------------------------- */
  *TesterIdx = DoIP_GetSizeOfTester();                                                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */

  for ( testerIdx = 0u;
        testerIdx < DoIP_GetSizeOfTester();
        testerIdx++ )
  {
    /* #10 Look up testers index. */
    if ( DoIP_GetTesterAddrOfTester(testerIdx) == TesterAddr )
    {
      *TesterIdx = (DoIP_SizeOfTesterType)testerIdx;                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
      retVal = E_OK;
      break;
    }
  }

#if ( DOIP_DEFAULT_TESTER_ENABLED == STD_ON )
  /* #20 Check if no tester is found (if enabled). */
  if ( retVal == E_NOT_OK )
  {
    DoIP_SizeOfConnectionTcpType connectionTcpIdx =
      DoIP_GetConnectionTcpIdxOfTesterDyn(DoIP_GetTesterIdxOfDefaultTester(0u));

    /* #30 Check if default tester is not used or used with same address. */
    if ( (connectionTcpIdx == DoIP_GetSizeOfConnectionTcp()) ||
         (DoIP_GetTesterIdxOfConnectionTcpDyn(connectionTcpIdx) == DoIP_GetSizeOfTester()) ||
         (TesterAddr == DoIP_GetTesterAddrOfConnectionTcpDyn(connectionTcpIdx)) )
    {
      *TesterIdx = DoIP_GetTesterIdxOfDefaultTester(0u);                                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
      retVal = E_OK;
    }
  }
#endif /* DOIP_DEFAULT_TESTER_ENABLED == STD_ON */

  return retVal;
} /* DoIP_RxTcpRout_GetTesterIdxByTesterAddr() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_GetConnectionIdxOfTesterAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(DoIP_SizeOfConnectionTcpType, DOIP_CODE) DoIP_RxTcpRout_GetConnectionIdxOfTesterAddr(                  /* INTERNAL_NOTE_SBSW_OK */
  uint16 TesterAddr)                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_ConnectionTcpIterType connectionTcpIdx;
  DoIP_SizeOfConnectionTcpType retConnectionTcpIdx = DoIP_GetSizeOfConnectionTcp();

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Look up testers connection index. */
  for ( connectionTcpIdx = 0u;
        connectionTcpIdx < DoIP_GetSizeOfConnectionTcp();
        connectionTcpIdx++ )
  {
    if ( (DoIP_GetTesterIdxOfConnectionTcpDyn(connectionTcpIdx) != DoIP_GetSizeOfTester()) &&
         (DoIP_GetTesterAddrOfConnectionTcpDyn(connectionTcpIdx) == TesterAddr) )
    {
      retConnectionTcpIdx = (DoIP_SizeOfConnectionTcpType)connectionTcpIdx;
      break;
    }
  }

  return retConnectionTcpIdx;
} /* DoIP_RxTcpRout_GetConnectionIdxOfTesterAddr() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_GetAvailableSockNum()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(DoIP_ConnectionTcpIterType, DOIP_CODE) DoIP_RxTcpRout_GetAvailableSockNum(                             /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionGroupType ConnectionGroupIdx)                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_ConnectionTcpIterType usedSockNum = 0u;
  DoIP_ConnectionTcpIterType availableSockNum;
  DoIP_ConnectionTcpIndIterType connectionTcpIndIdx;
  DoIP_ConnectionTcpIndIterType maximumSockNum =
    ((DoIP_ConnectionTcpIndIterType)DoIP_GetConnectionTcpIndEndIdxOfConnectionGroup(ConnectionGroupIdx) -
     (DoIP_ConnectionTcpIndIterType)DoIP_GetConnectionTcpIndStartIdxOfConnectionGroup(ConnectionGroupIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all TCP connections related to the connection group. */
  for ( connectionTcpIndIdx = DoIP_GetConnectionTcpIndStartIdxOfConnectionGroup(ConnectionGroupIdx);
        connectionTcpIndIdx < DoIP_GetConnectionTcpIndEndIdxOfConnectionGroup(ConnectionGroupIdx);
        connectionTcpIndIdx++ )
  {
    /* #20 Increment the number of used connections if a tester is active on the connection. */
    if ( DoIP_GetTesterIdxOfConnectionTcpDyn(DoIP_GetConnectionTcpInd(connectionTcpIndIdx)) != DoIP_GetSizeOfTester() )
    {
      usedSockNum++;
    }
  }

  /* #30 Calculate number of available sockets dependent of the used connections. */
  /* PRQA S 2912 1 */ /* MD_DoIP_21.1_CFG */
  availableSockNum = (DoIP_ConnectionTcpIterType)((maximumSockNum - usedSockNum) - 1u);

  return availableSockNum;
} /* DoIP_RxTcpRout_GetAvailableSockNum() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_PerformRoutingActivation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_PerformRoutingActivation(void)                                         /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  const uint16 testerAddr = DoIP_GetTesterAddrOfRoutActivHandler(0u);
  const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfRoutActivHandler(0u);                                     /* INTERNAL_NOTE_SBSW_DOIP_RoutActivHandler_Data */
  const DoIP_SizeOfRoutingActivationType routActIdx = DoIP_GetRoutingActivationIdxOfRoutActivHandler(0u);              /* INTERNAL_NOTE_SBSW_DOIP_RoutActivHandler_Data */
  const DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_GetConnectionTcpIdxOfRoutActivHandler(0u);                /* INTERNAL_NOTE_SBSW_DOIP_RoutActivHandler_Data */
  DoIP_RoutActivStateType nextState = DOIP_ROUT_ACTIV_STATE_NONE;

  /* ----- Implementation ----------------------------------------------- */
  if ( !DoIP_IsOemSpecUsedOfRoutActivHandler(0u) &&
       ((DoIP_GetAuthReqLengthOfRoutingActivation(routActIdx) != 0u) ||
        (DoIP_GetConfReqLengthOfRoutingActivation(routActIdx) != 0u)) )
  {
    DoIP_SetActivStateOfConnectionTcpDyn(connectionTcpIdx, DOIP_ROUT_ACTIV_STATE_NONE);                                /* SBSW_DOIP_RoutActivHandler_Data */

    /* #10 Send error if OEM specific part is not received but required. */
    (void)DoIP_TxTcp_Transmit(connectionTcpIdx, DOIP_HDR_TYPE_ROUT_ACTIV_RES, testerAddr,                              /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      DOIP_ROUT_ACTIV_RES_CODE_MISSING_AUTHENT, testerIdx, NULL_PTR, FALSE);
  }
  else
  {
    /* #20 Otherwise call authentication callback (if configured). */
    if ( (DoIP_GetAuthFuncPtrOfRoutingActivation(routActIdx) != NULL_PTR) ||
         (DoIP_GetAuthWithRemAddrFuncPtrOfRoutingActivation(routActIdx) != NULL_PTR) )
    {
      retVal = DoIP_RxTcpRout_PerformRoutingActivationAuth(&nextState);                                                /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    }

    /* #30 Call confirmation callback (if configured). */
    if ( (retVal == E_OK) && (
           (DoIP_GetConfFuncPtrOfRoutingActivation(routActIdx) != NULL_PTR) ||
           (DoIP_GetConfWithRemAddrFuncPtrOfRoutingActivation(routActIdx) != NULL_PTR)) )
    {
      retVal = DoIP_RxTcpRout_PerformRoutingActivationConf(&nextState);                                                /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    }

    if ( retVal == E_OK )
    {
      /* #40 Register tester, activate route and send response if authentification and confirmation passed. */
      DoIP_RxTcpRout_RegisterTester(connectionTcpIdx, testerIdx, testerAddr, routActIdx,
        DOIP_ROUT_ACTIV_STATE_ACTIVATED);

      DoIP_SetInactivCntOfConnectionTcpDyn(connectionTcpIdx, 0u);                                                      /* SBSW_DOIP_RoutActivHandler_Data */

      DoIP_SetConnectionTcpIdxOfTesterDyn(testerIdx, connectionTcpIdx);                                                /* SBSW_DOIP_RoutActivHandler_Data */

      (void)DoIP_TxTcp_Transmit(connectionTcpIdx, DOIP_HDR_TYPE_ROUT_ACTIV_RES, testerAddr,                            /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        DOIP_ROUT_ACTIV_RES_CODE_SUCCESS, testerIdx, NULL_PTR, FALSE);
    }
  }
} /* DoIP_RxTcpRout_PerformRoutingActivation() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_RegisterTester()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_RegisterTester(                                                        /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  DoIP_SizeOfTesterType TesterIdx,                                                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX_INC_INV */
  uint16 TesterAddr,                                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  DoIP_SizeOfRoutingActivationType RoutActIdx,                                                                         /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX_INC_INV */
  DoIP_RoutActivStateType NextState)                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* #10 Save tester data. */
  DoIP_SetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx, TesterIdx);                                                    /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  DoIP_SetTesterAddrOfConnectionTcpDyn(ConnectionTcpIdx, TesterAddr);                                                  /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  DoIP_SetRoutingActivationIdxOfConnectionTcpDyn(ConnectionTcpIdx, RoutActIdx);                                        /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  DoIP_SetActivStateOfConnectionTcpDyn(ConnectionTcpIdx, NextState);                                                   /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
} /* DoIP_RxTcpRout_RegisterTester() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_PerformRoutingActivationAuth()
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
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_PerformRoutingActivationAuth(                                /* INTERNAL_NOTE_SBSW_OK */
  P2VAR(DoIP_RoutActivStateType, AUTOMATIC, DOIP_APPL_VAR) NextStatePtr)                                               /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  const uint16 testerAddr = DoIP_GetTesterAddrOfRoutActivHandler(0u);
  const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfRoutActivHandler(0u);                                     /* INTERNAL_NOTE_SBSW_DOIP_RoutActivHandler_Data */
  const DoIP_SizeOfRoutingActivationType routActIdx = DoIP_GetRoutingActivationIdxOfRoutActivHandler(0u);              /* INTERNAL_NOTE_SBSW_DOIP_RoutActivHandler_Data */
  const DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_GetConnectionTcpIdxOfRoutActivHandler(0u);                /* INTERNAL_NOTE_SBSW_DOIP_RoutActivHandler_Data */
  boolean authentified = FALSE;
  uint32 oemSpecReq32;
  uint32 oemSpecRes32;
  uint8 oemSpecReq[DOIP_ROUT_ACTIV_REQ_OEM_LEN_BYTE] = { 0u };
  uint8 oemSpecRes[DOIP_ROUT_ACTIV_ACK_OEM_LEN_BYTE] = { 0u };

  /* ----- Implementation ----------------------------------------------- */
  oemSpecReq32 = DoIP_GetOemSpecReqOfRoutActivHandler(0u);
  DoIP_Util_PutUInt32(oemSpecReq, 0u, oemSpecReq32);                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */

  oemSpecRes32 = DoIP_GetOemSpecResOfRoutActivHandler(0u);
  DoIP_Util_PutUInt32(oemSpecRes, 0u, oemSpecRes32);                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */

#if ( DOIP_ROUT_ACT_AUTH_REM_ADDR_ENABLED == STD_ON )
  if ( DoIP_IsAuthFuncWithRemAddrOfRoutingActivation(routActIdx) )
  {
    SoAd_SockAddrInetXType remAddr = { SOAD_AF_INVALID, 0u, { 0u } };

    /* #10 Try to get remote address for authentification (if enabled). */
    /* PRQA S 0310 2 */ /* MD_DoIP_11.4 */
    if ( SoAd_GetRemoteAddr(DoIP_GetSoConIdOfConnectionDyn(connectionTcpIdx),                                          /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
           DOIP_A_P2VAR(SoAd_SockAddrType)&remAddr) == E_OK )
    {
      /* #15 Call authentification with remote address on success (if enabled).*/
      /* PRQA S 0310 2 */ /* MD_DoIP_11.4 */
      retVal = DoIP_GetAuthWithRemAddrFuncPtrOfRoutingActivation(routActIdx)(&authentified, &oemSpecReq[0u],           /* SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_AND_CONST_POINTER_FORWARD */
        &oemSpecRes[0u], DOIP_A_P2CONST(SoAd_SockAddrType)&remAddr);
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }
  else
#endif /* DOIP_ROUT_ACT_AUTH_REM_ADDR_ENABLED == STD_ON */
  {
    /* #20 Otherwise call authentification without remote address. */
    /* PRQA S 0310 3 */ /* MD_DoIP_11.4 */
    retVal = DoIP_GetAuthFuncPtrOfRoutingActivation(routActIdx)(&authentified, &oemSpecReq[0u], &oemSpecRes[0u]);      /* SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_FORWARD */
  }

  IPBASE_GET_UINT32(&oemSpecReq[0u], 0u, oemSpecReq32);                                                                /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  DoIP_SetOemSpecReqOfRoutActivHandler(0u, oemSpecReq32);                                                              /* SBSW_DOIP_RoutActivHandler */

  IPBASE_GET_UINT32(&oemSpecRes[0u], 0u, oemSpecRes32);                                                                /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  DoIP_SetOemSpecResOfRoutActivHandler(0u, oemSpecRes32);                                                              /* SBSW_DOIP_RoutActivHandler */

  if ( retVal == E_NOT_OK )
  {
    /* #30 In case authentication failed send error. */
    DoIP_RxTcpRout_RegisterTester(connectionTcpIdx, testerIdx, testerAddr, routActIdx, DOIP_ROUT_ACTIV_STATE_NONE);

    (void)DoIP_TxTcp_Transmit(connectionTcpIdx, DOIP_HDR_TYPE_ROUT_ACTIV_RES, testerAddr,                              /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      DOIP_ROUT_ACTIV_RES_CODE_MISSING_AUTHENT, testerIdx, NULL_PTR, FALSE);
  }
  else if ( retVal == DOIP_E_PENDING )
  {
    /* #40 In case authentication pending set state pending. */
    DoIP_RxTcpRout_RegisterTester(connectionTcpIdx, testerIdx, testerAddr, routActIdx,
      DOIP_ROUT_ACTIV_STATE_AUTH_PENDING);
  }
  else
  {
    if ( authentified == TRUE )
    {
      /* Hint: Registration of tester is done for this case in the calling function. */
      /* #50 In case authentication passed activate route. */
      *NextStatePtr = DOIP_ROUT_ACTIV_STATE_ACTIVATED;                                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    }
    else
    {
      /* #60 Otherwise save state and send error response. */
      DoIP_RxTcpRout_RegisterTester(connectionTcpIdx, testerIdx, testerAddr, routActIdx, DOIP_ROUT_ACTIV_STATE_NONE);

      (void)DoIP_TxTcp_Transmit(connectionTcpIdx, DOIP_HDR_TYPE_ROUT_ACTIV_RES, testerAddr,                            /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        DOIP_ROUT_ACTIV_RES_CODE_MISSING_AUTHENT, testerIdx, NULL_PTR, FALSE);

      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* DoIP_RxTcpRout_PerformRoutingActivationAuth() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_PerformRoutingActivationConf()
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
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_PerformRoutingActivationConf(                                /* INTERNAL_NOTE_SBSW_OK */
  P2VAR(DoIP_RoutActivStateType, AUTOMATIC, DOIP_APPL_VAR) NextStatePtr)                                               /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  const uint16 testerAddr = DoIP_GetTesterAddrOfRoutActivHandler(0u);
  const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfRoutActivHandler(0u);                                     /* INTERNAL_NOTE_SBSW_DOIP_RoutActivHandler_Data */
  const DoIP_SizeOfRoutingActivationType routActIdx = DoIP_GetRoutingActivationIdxOfRoutActivHandler(0u);              /* INTERNAL_NOTE_SBSW_DOIP_RoutActivHandler_Data */
  const DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_GetConnectionTcpIdxOfRoutActivHandler(0u);                /* INTERNAL_NOTE_SBSW_DOIP_RoutActivHandler_Data */
  boolean confirmed = FALSE;
  uint32 oemSpecReq32;
  uint32 oemSpecRes32;
  uint8 oemSpecReq[DOIP_ROUT_ACTIV_REQ_OEM_LEN_BYTE] = { 0u };
  uint8 oemSpecRes[DOIP_ROUT_ACTIV_ACK_OEM_LEN_BYTE] = { 0u };
  uint8 offsetReq = 0u;
  uint8 offsetRes = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate request and response offset. */
  if ( DoIP_GetConfReqLengthOfRoutingActivation(routActIdx) > 0u )
  {
    offsetReq = (uint8)(DOIP_ROUT_ACTIV_REQ_OEM_LEN_BYTE - DoIP_GetConfReqLengthOfRoutingActivation(routActIdx));
  }
  if ( DoIP_GetConfResLengthOfRoutingActivation(routActIdx) > 0u )
  {
    offsetRes = (uint8)(DOIP_ROUT_ACTIV_ACK_OEM_LEN_BYTE - DoIP_GetConfResLengthOfRoutingActivation(routActIdx));
  }

  oemSpecReq32 = DoIP_GetOemSpecReqOfRoutActivHandler(0u);
  DoIP_Util_PutUInt32(oemSpecReq, 0u, oemSpecReq32);                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */

  oemSpecRes32 = DoIP_GetOemSpecResOfRoutActivHandler(0u);
  DoIP_Util_PutUInt32(oemSpecRes, 0u, oemSpecRes32);                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */

#if ( DOIP_ROUT_ACT_CONF_REM_ADDR_ENABLED == STD_ON )
  if ( DoIP_IsConfFuncWithRemAddrOfRoutingActivation(routActIdx) )
  {
    SoAd_SockAddrInetXType remAddr = { SOAD_AF_INVALID, 0u, { 0u } };

    /* #20 Try to get remote address for confirmation (if enabled). */
    /* PRQA S 0310 8 */ /* MD_DoIP_11.4 */
    if ( SoAd_GetRemoteAddr(DoIP_GetSoConIdOfConnectionDyn(connectionTcpIdx),                                          /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
           DOIP_A_P2VAR(SoAd_SockAddrType)&remAddr) == E_OK )
    {
      /* #25 Call confirmation with remote address on success (if enabled). */
      /* PRQA S 0313 2 */ /* MD_DoIP_11.1 */
      /* PRQA S 2842 2 */ /* MD_DoIP_21.1_IDX */
      retVal = DoIP_GetConfWithRemAddrFuncPtrOfRoutingActivation(routActIdx)                                           /* SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_AND_CONST_POINTER_FORWARD */
        (&confirmed, &oemSpecReq[offsetReq], &oemSpecRes[offsetRes], DOIP_A_P2CONST(SoAd_SockAddrType)&remAddr);
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }
  else
#endif /* DOIP_ROUT_ACT_CONF_REM_ADDR_ENABLED == STD_ON */
  {
    /* #30 Otherwise call confirmation without remote address. */
    /* PRQA S 2842 2 */ /* MD_DoIP_21.1_IDX */
    retVal = DoIP_GetConfFuncPtrOfRoutingActivation(routActIdx)                                                        /* SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_FORWARD */
      (&confirmed, &oemSpecReq[offsetReq], &oemSpecRes[offsetRes]);
  }

  IPBASE_GET_UINT32(&oemSpecReq[0u], 0u, oemSpecReq32);                                                                /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  DoIP_SetOemSpecReqOfRoutActivHandler(0u, oemSpecReq32);                                                              /* SBSW_DOIP_RoutActivHandler */

  IPBASE_GET_UINT32(&oemSpecRes[0u], 0u, oemSpecRes32);                                                                /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  DoIP_SetOemSpecResOfRoutActivHandler(0u, oemSpecRes32);                                                              /* SBSW_DOIP_RoutActivHandler */

  if ( retVal == E_NOT_OK )
  {
    /* #40 In case confirmation failed send error. */
    DoIP_RxTcpRout_RegisterTester(connectionTcpIdx, testerIdx, testerAddr, routActIdx, DOIP_ROUT_ACTIV_STATE_NONE);

    (void)DoIP_TxTcp_Transmit(connectionTcpIdx, DOIP_HDR_TYPE_ROUT_ACTIV_RES, testerAddr,                              /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      DOIP_ROUT_ACTIV_RES_CODE_CONFIRM_REJECTED, testerIdx, NULL_PTR, TRUE);
  }
  else if ( retVal == DOIP_E_PENDING )
  {
    /* #50 In case confirmation pending. */
    DoIP_RxTcpRout_RegisterTester(connectionTcpIdx, testerIdx, testerAddr, routActIdx,
      DoIP_GetActivStateOfConnectionTcpDyn(connectionTcpIdx));

    if ( *NextStatePtr == DOIP_ROUT_ACTIV_STATE_ACTIVATED )
    {
      DoIP_SetActivStateOfConnectionTcpDyn(connectionTcpIdx, DOIP_ROUT_ACTIV_STATE_CONF_PENDING);                      /* SBSW_DOIP_RoutActivHandler_Data */

      /* #60 Set state to confirmation pending and send response if authentication was performed in same context. */
      (void)DoIP_TxTcp_Transmit(connectionTcpIdx, DOIP_HDR_TYPE_ROUT_ACTIV_RES, testerAddr,                            /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        DOIP_ROUT_ACTIV_RES_CODE_CONFIRM_REQUIRED, testerIdx, NULL_PTR, FALSE);
    }
  }
  else
  {
    if ( confirmed == TRUE )
    {
      /* Hint: Registration of tester is done for this case in the calling function. */
      /* #70 In case confirmation passed activate route. */
      *NextStatePtr = DOIP_ROUT_ACTIV_STATE_ACTIVATED;                                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    }
    else
    {
      /* #80 Otherwise save state and send error response. */
      DoIP_RxTcpRout_RegisterTester(connectionTcpIdx, testerIdx, testerAddr, routActIdx, DOIP_ROUT_ACTIV_STATE_NONE);

      (void)DoIP_TxTcp_Transmit(connectionTcpIdx, DOIP_HDR_TYPE_ROUT_ACTIV_RES, testerAddr,                            /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        DOIP_ROUT_ACTIV_RES_CODE_CONFIRM_REJECTED, testerIdx, NULL_PTR, TRUE);
    }
  }

  return retVal;
} /* DoIP_RxTcpRout_PerformRoutingActivationConf() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleRetryRoutingActivationAuthAndConf()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleRetryRoutingActivationAuthAndConf(void)                          /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_GetConnectionTcpIdxOfRoutActivHandler(0u);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if routing activation but no alive check is pending. */
  if ( (connectionTcpIdx != DoIP_GetSizeOfConnectionTcp()) && (DoIP_GetAliveCheckCntOfRoutActivHandler(0u) == 0u) )
  {
    const uint16 testerAddr = DoIP_GetTesterAddrOfConnectionTcpDyn(connectionTcpIdx);
    const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfConnectionTcpDyn(connectionTcpIdx);
    const DoIP_RoutActivStateType lastState = DoIP_GetActivStateOfConnectionTcpDyn(connectionTcpIdx);
    const DoIP_SizeOfRoutingActivationType routActIdx =
      DoIP_GetRoutingActivationIdxOfConnectionTcpDyn(connectionTcpIdx);
    DoIP_RoutActivStateType nextState = DOIP_ROUT_ACTIV_STATE_NONE;

    /* #20 Perform authentication if state is pending. */
    if ( lastState == DOIP_ROUT_ACTIV_STATE_AUTH_PENDING )
    {
      (void)DoIP_RxTcpRout_PerformRoutingActivationAuth(&nextState);                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    }

    /* #25 Perform confirmation if state is pending or callback is configured. */
    if ( (lastState == DOIP_ROUT_ACTIV_STATE_CONF_PENDING) ||
        ((nextState == DOIP_ROUT_ACTIV_STATE_ACTIVATED) &&
          ((DoIP_GetConfFuncPtrOfRoutingActivation(routActIdx) != NULL_PTR) ||
           (DoIP_GetConfWithRemAddrFuncPtrOfRoutingActivation(routActIdx) != NULL_PTR))) )
    {
      (void)DoIP_RxTcpRout_PerformRoutingActivationConf(&nextState);                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    }

    /* #30 Check if authentification and confirmation are performed successfully. */
    if ( nextState == DOIP_ROUT_ACTIV_STATE_ACTIVATED )
    {
      DoIP_SetConnectionTcpIdxOfTesterDyn(testerIdx, connectionTcpIdx);                                                /* SBSW_DOIP_RegisterTester */

      DoIP_SetActivStateOfConnectionTcpDyn(connectionTcpIdx, DOIP_ROUT_ACTIV_STATE_ACTIVATED);                         /* SBSW_DOIP_RoutActivHandler_Data */

      if ( lastState != DOIP_ROUT_ACTIV_STATE_CONF_PENDING )
      {
        DoIP_SetInactivCntOfConnectionTcpDyn(connectionTcpIdx, 0u);                                                    /* SBSW_DOIP_RoutActivHandler_Data */

        /* #40 Send routing activation response if not activated after confirmation was pending. */
        (void)DoIP_TxTcp_Transmit(connectionTcpIdx, DOIP_HDR_TYPE_ROUT_ACTIV_RES, testerAddr,                          /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
          DOIP_ROUT_ACTIV_RES_CODE_SUCCESS, testerIdx, NULL_PTR, FALSE);
      }
      else
      {
        /* #50 Release routing activation handler if activated after confirmation was pending. */
        DoIP_SetConnectionTcpIdxOfRoutActivHandler(0u, DoIP_GetSizeOfConnectionTcp());                                 /* SBSW_DOIP_RoutActivHandler */
      }
    }
  }
} /* DoIP_RxTcpRout_HandleRetryRoutingActivationAuthAndConf() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleAliveCheckTimeouts()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleAliveCheckTimeouts(void)                                         /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_GetConnectionTcpIdxOfRoutActivHandler(0u);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if routing activation is pending. */
  if ( connectionTcpIdx != DoIP_GetSizeOfConnectionTcp() )
  {
    /* #20 Handle alive check timeout counter. */
    if ( DoIP_GetAliveCheckCntOfRoutActivHandler(0u) > 0u )
    {
      DoIP_DecAliveCheckCntOfRoutActivHandler(0u);                                                                     /* SBSW_DOIP_RoutActivHandler */
      if ( DoIP_GetAliveCheckCntOfRoutActivHandler(0u) == 0u )
      {
        /* #30 Clean up all timed-out socket connections. */
        DoIP_RxTcpRout_HandleAliveCheckTimeoutsSocketsClose();
        if ( DoIP_RxTcpRout_CheckConnectionAvailablility(connectionTcpIdx) == E_OK )
        {
          /* #40 Continue with received routing activation request if there is a free connection. */
          DoIP_RxTcpRout_PerformRoutingActivation();
        }
      }
    }
  }
} /* DoIP_RxTcpRout_HandleAliveCheckTimeouts() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleAliveCheckTimeoutsSocketsClose()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleAliveCheckTimeoutsSocketsClose(void)                             /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_AliveCheckListIterType aliveCheckListIdx;
  DoIP_SizeOfConnectionTcpType connectionTcpIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Close all timeouted socket connections. */
  for ( aliveCheckListIdx = 0u;
        aliveCheckListIdx < DoIP_GetSizeOfAliveCheckList();
        aliveCheckListIdx++ )
  {
    if ( DoIP_GetAliveCheckElemNumOfRoutActivHandler(0u) == 0u )
    { /* all sockets closed or Alive Check Response received */
      break;
    }

    connectionTcpIdx = DoIP_GetConnectionTcpIdxOfAliveCheckList(aliveCheckListIdx);

    if ( connectionTcpIdx != DoIP_GetSizeOfConnectionTcp() )
    { /* alive check timeout -> close socket connection */

      DoIP_Con_SoConClose(connectionTcpIdx);
      DoIP_RxTcpRout_RegisterTester(connectionTcpIdx, DoIP_GetSizeOfTester(), DOIP_ADDR_ANY,
        DoIP_GetSizeOfRoutingActivation(), DOIP_ROUT_ACTIV_STATE_NONE);

      DoIP_SetConnectionTcpIdxOfAliveCheckList(aliveCheckListIdx, DoIP_GetSizeOfConnectionTcp());                      /* SBSW_DOIP_CSL01 */
      DoIP_DecAliveCheckElemNumOfRoutActivHandler(0u);                                                                 /* SBSW_DOIP_RoutActivHandler */
    }
  }
} /* DoIP_RxTcpRout_HandleAliveCheckTimeoutsSocketsClose() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_CheckConnectionAvailablility()
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
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpRout_CheckConnectionAvailablility(                                /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if connection is still online. */
  if ( DoIP_GetSoConStateOfConnectionDyn(ConnectionTcpIdx) == SOAD_SOCON_ONLINE )
  {
    const DoIP_TesterAddrOfRoutActivHandlerType testerAddr = DoIP_GetTesterAddrOfRoutActivHandler(0u);
    DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_RxTcpRout_GetConnectionIdxOfTesterAddr(testerAddr);

    /* #20 Check if routing is (still) active on other socket. */
    if ( connectionTcpIdx != DoIP_GetSizeOfConnectionTcp() )
    {
      /* #30 Deny routing activation for active address on new socket connection. */
      (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_ROUT_ACTIV_RES, testerAddr,                            /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        DOIP_ROUT_ACTIV_RES_CODE_ALREADY_ACTIV, 0u, NULL_PTR, TRUE);
    }
    else
    {
      if ( DoIP_RxTcpRout_GetAvailableSockNum(DoIP_GetConnectionGroupIdxOfConnectionTcp(ConnectionTcpIdx)) == 0u )
      {
        /* #40 Deny routing activation if all sockets but max one are in use. */
        (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_ROUT_ACTIV_RES, testerAddr,                          /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
          DOIP_ROUT_ACTIV_RES_CODE_SOCKETS_IN_USE, 0u, NULL_PTR, TRUE);
      }
      else
      {
        /* #50 Otherwise accept routing activation. */
        retVal = E_OK;
      }
    }
  }

  return retVal;
} /* DoIP_RxTcpRout_CheckConnectionAvailablility() */

/**********************************************************************************************************************
 *  DoIP_RxTcpRout_HandleInactivityTimeouts()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpRout_HandleInactivityTimeouts(void)                                         /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_ConnectionTcpIterType connectionTcpIdx;

  /* ----- Implementation ----------------------------------------------- */
  for ( connectionTcpIdx = 0u;
        connectionTcpIdx < DoIP_GetSizeOfConnectionTcp();
        connectionTcpIdx++ )
  {
    if ( DoIP_GetSoConStateOfConnectionDyn(connectionTcpIdx) == SOAD_SOCON_ONLINE )
    {
      /* #10 Check for all online connections if routing is activated. */
      if ( DoIP_GetActivStateOfConnectionTcpDyn(connectionTcpIdx) != DOIP_ROUT_ACTIV_STATE_ACTIVATED )
      {
        if ( DoIP_GetInactivCntOfConnectionTcpDyn(connectionTcpIdx) == DOIP_INIT_INACTIV_WAIT )
        {
          /* #20 Close socket after inital timeout if no routing is activated. */
          DoIP_Con_SoConClose((DoIP_SizeOfConnectionType)connectionTcpIdx);
        }
      }
      else
      {
        if ( DoIP_GetInactivCntOfConnectionTcpDyn(connectionTcpIdx) == DOIP_GEN_INACTIV_WAIT )
        {
          /* #30 Close socket after general timeout if routing is activated. */
          DoIP_Con_SoConClose((DoIP_SizeOfConnectionType)connectionTcpIdx);
        }
      }
      DoIP_IncInactivCntOfConnectionTcpDyn(connectionTcpIdx);                                                          /* SBSW_DOIP_CSL02 */
    }
  }
} /* DoIP_RxTcpRout_HandleInactivityTimeouts() */

/**********************************************************************************************************************
 *  DoIP_RxTcpAlive_HandleAliveCheckRes()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpAlive_HandleAliveCheckRes(                                                  /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr)                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 bytesToCopy;
  uint32 hdrLen;

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT32(DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx)), 4u, hdrLen);      /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  /* #10 Check message lengths and send nack. */
  if ( hdrLen > DOIP_MAX_REQUEST_BYTES )
  {
    DoIP_SetSkipRxMsgOfConnectionTcpDyn(ConnectionTcpIdx, TRUE);                                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, 0u, 0u, NULL_PTR,       /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      FALSE);
  }
  else if ( hdrLen != DOIP_ADDR_LEN_BYTE )
  {
    (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, 0u, 0u, NULL_PTR, TRUE); /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  else
  {
    const uint64 msgLength = (uint64)hdrLen + DOIP_GEN_HDR_LEN_BYTE;
    bytesToCopy = (uint32)(msgLength - DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx));                       /* INTERNAL_NOTE_DOIP_CAST_HEADER_ALREADY_RECEIVED */

    /* #20 Otherwise copy data to header buffer. */
    DoIP_RxTcpGen_CopyDataToHeaderBuffer(ConnectionTcpIdx, PduInfoPtr, ReadDataLenPtr, bytesToCopy);                   /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */

    if ( DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx) == msgLength )
    {
      /* #30 Handle alive check response if message is now copied completely. */
      DoIP_RxTcpAlive_HandleCopiedAliveCheckRes(ConnectionTcpIdx);
    }
    else
    {
      /* #40 Otherwise set buffer size to length of pending message part. */
      uint32 bufSize = (uint32)(msgLength - DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx));                  /* INTERNAL_NOTE_DOIP_CAST_HEADER_ALREADY_RECEIVED */
      DoIP_Util_CheckBufferSizeAndModify(bufSize, BufferSizePtr);                                                      /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    }
  }
} /* DoIP_RxTcpAlive_HandleAliveCheckRes() */

/**********************************************************************************************************************
 *  DoIP_RxTcpAlive_HandleCopiedAliveCheckRes()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpAlive_HandleCopiedAliveCheckRes(                                            /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx);
  uint16 testerAddr;
  uint16 testerAddrTmp;

  /* ----- Implementation ----------------------------------------------- */
  if ( testerIdx != DoIP_GetSizeOfTester() )
  {
    testerAddr = DoIP_GetTesterAddrOfTester(testerIdx);

#if ( DOIP_DEFAULT_TESTER_ENABLED == STD_ON )
    /* #10 Look up current address if default tester is used (if enabled). */
    if ( testerAddr == DOIP_ADDR_ANY )
    {
      testerAddr = DoIP_GetTesterAddrOfConnectionTcpDyn(ConnectionTcpIdx);
    }
#endif /* DOIP_DEFAULT_TESTER_ENABLED == STD_ON */

    IPBASE_GET_UINT16(DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx)),                 /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
      DOIP_GEN_HDR_LEN_BYTE, testerAddrTmp);

    if ( testerAddrTmp == testerAddr )
    {
      /* #20 Remove alive check response if tester use expected address. */
      DoIP_RxTcpAlive_RemoveAliveCheckFromRoutActHandler(ConnectionTcpIdx);
    }
    else
    {
      /* #30 Otherwise close socket if tester use unexpected address. */
      DoIP_SetSoConClosingOfConnectionDyn(ConnectionTcpIdx, TRUE);                                                     /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
      DoIP_Con_SoConClose(ConnectionTcpIdx);
    }
  }

  /* finish message */
  DoIP_SetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                         /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
} /* DoIP_RxTcpAlive_HandleCopiedAliveCheckRes() */

/**********************************************************************************************************************
 *  DoIP_RxTcpAlive_RemoveAliveCheckFromRoutActHandler()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpAlive_RemoveAliveCheckFromRoutActHandler(                                   /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_AliveCheckListIterType aliveCheckListIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all alive check list elements. */
  for ( aliveCheckListIdx = 0u;
        aliveCheckListIdx < DoIP_GetSizeOfAliveCheckList();
        aliveCheckListIdx++ )
  {
    /* #20 Check if alive check list element belongs to the required connection. */
    if ( ConnectionTcpIdx == DoIP_GetConnectionTcpIdxOfAliveCheckList(aliveCheckListIdx) )
    {
      /* #30 Remove alive check from list. */
      DoIP_SetConnectionTcpIdxOfAliveCheckList(aliveCheckListIdx, DoIP_GetSizeOfConnectionTcp());                      /* SBSW_DOIP_CSL01 */
      DoIP_DecAliveCheckElemNumOfRoutActivHandler(0u);                                                                 /* SBSW_DOIP_RoutActivHandler */

      /* #40 Check if all expected alive check responses have been received. */
      if ( DoIP_GetAliveCheckElemNumOfRoutActivHandler(0u) == 0u )
      {
        /* #50 Trigger routing activation handling in next main function. */
        DoIP_SetAliveCheckCntOfRoutActivHandler(0u, DOIP_ALIVE_CHECK_WAIT_NEXT_MAIN);                                  /* SBSW_DOIP_RoutActivHandler */
      }

      break;
    }
  }
} /* DoIP_RxTcpAlive_RemoveAliveCheckFromRoutActHandler() */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleDiagnosticMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpDiag_HandleDiagnosticMessage(                                               /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr)                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 hdrLen;

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT32(DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx)), 4u, hdrLen);      /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  /* #10 Check message lengths and send nack. */
  if ( hdrLen > DOIP_MAX_REQUEST_BYTES )
  {
    DoIP_SetSkipRxMsgOfConnectionTcpDyn(ConnectionTcpIdx, TRUE);                                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, 0u, 0u, NULL_PTR,       /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      FALSE);
  }
  else if ( hdrLen <= DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE )
  {
    (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_INV_LEN, 0u, 0u, NULL_PTR, TRUE); /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
  }
  else
  {
    /* #20 Otherwise handle diagnostic message. */
    DoIP_RxTcpDiag_HandleValidDiagnosticMessage(ConnectionTcpIdx, PduInfoPtr, BufferSizePtr, ReadDataLenPtr);          /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }
} /* DoIP_RxTcpDiag_HandleDiagnosticMessage() */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleValidDiagnosticMessage()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpDiag_HandleValidDiagnosticMessage(                                          /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr)                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy logical address if not yet done. */
  retVal = DoIP_RxTcpDiag_CopyLogicalAddr(ConnectionTcpIdx, PduInfoPtr, BufferSizePtr, ReadDataLenPtr);                /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */

  /* #20 Check if logical address could be copied. */
  if ( retVal == E_OK )
  {
#if ( DOIP_NACK_APPEND_REQ == STD_ON )
    /* #30 Check if acknowledge message shall contain user data and append them (if enabled). */
    DoIP_RxTcpDiag_AppendNackData(ConnectionTcpIdx, PduInfoPtr, ReadDataLenPtr);                                       /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */

    /* #40 Verify Rx Pdu. */
    retVal = DoIP_RxTcpDiag_VerifyRxPdu(ConnectionTcpIdx, PduInfoPtr, BufferSizePtr, ReadDataLenPtr);                  /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */

    if ( retVal == E_OK )
    {
      /* #50 Copy user data on success. */
#if ( (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) )
      if ( DoIP_RxTcpDiag_CopyVerifiedUserData(ConnectionTcpIdx, BufferSizePtr, FALSE) == E_OK )                       /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
#endif /* (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) */
      {
        DoIP_RxTcpDiag_CopyUserData(ConnectionTcpIdx, PduInfoPtr, BufferSizePtr, ReadDataLenPtr);                      /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      }
    }
  }

  if ( retVal == E_NOT_OK )
  {
    /* #60 Skip message if copying of logical address of verification of Rx Pdu failed. */
    DoIP_SetSkipRxMsgOfConnectionTcpDyn(ConnectionTcpIdx, TRUE);                                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }
} /* DoIP_RxTcpDiag_HandleValidDiagnosticMessage() */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_CopyLogicalAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_CopyLogicalAddr(                                             /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr)                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  const DoIP_RxMsgOffsetOfConnectionTcpDynType rxMsgOffset = DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx);

  /* ----- Implementation ----------------------------------------------- */
  if ( rxMsgOffset < (DOIP_GEN_HDR_LEN_BYTE + DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE) )
  {
    const uint32 bytesToCopy = (uint32)((DOIP_GEN_HDR_LEN_BYTE + DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE) - rxMsgOffset);

    /* #10 Copy data to header buffer if there are bytes to copy. */
    DoIP_RxTcpGen_CopyDataToHeaderBuffer(ConnectionTcpIdx, PduInfoPtr, ReadDataLenPtr, bytesToCopy);                   /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */

    if ( DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx) ==
          (DOIP_GEN_HDR_LEN_BYTE + DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE) )
    {
      /* #20 Handle logical addresses if message header was copied completely. */
      retVal = DoIP_RxTcpDiag_HandleCopiedLogicalAddr(ConnectionTcpIdx);
    }
    else
    {
      /* #30 Otherwise set buffer size to length of pending message part. */
      uint32 bufSize = (uint32)((DOIP_GEN_HDR_LEN_BYTE + DOIP_DIAG_HDR_LEN_BYTE) -
        DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx));
      DoIP_Util_CheckBufferSizeAndModify(bufSize, BufferSizePtr);                                                      /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
      retVal = DOIP_E_PENDING;
    }
  }

  return retVal;
} /* DoIP_RxTcpDiag_CopyLogicalAddr() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleCopiedLogicalAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_HandleCopiedLogicalAddr(                                     /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const DoIP_RxHdrBufType *rxHdrBuf = DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx));
  uint16 srcAddr;
  uint16 tgtAddr;

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT16(rxHdrBuf, (DOIP_GEN_HDR_LEN_BYTE + 0u), srcAddr);                                                  /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  IPBASE_GET_UINT16(rxHdrBuf, (DOIP_GEN_HDR_LEN_BYTE + DOIP_ADDR_LEN_BYTE), tgtAddr);                                  /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  if ( DoIP_GetActivStateOfConnectionTcpDyn(ConnectionTcpIdx) != DOIP_ROUT_ACTIV_STATE_ACTIVATED )
  {
    /* #10 Prepare to send error if routing activation is missing. */
    DoIP_TxTcp_PrepareTransmit(ConnectionTcpIdx, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr,
      DOIP_DIAG_MSG_RES_CODE_INVALID_SRC_ADDR, TRUE);
  }
  else
#if ( DOIP_DEFAULT_TESTER_ENABLED == STD_ON )
  if ( (DoIP_GetTesterAddrOfTester(DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx)) == DOIP_ADDR_ANY) &&
       (DoIP_GetTesterAddrOfConnectionTcpDyn(ConnectionTcpIdx) != srcAddr) )
  {
    /* #20 Prepare to send error if default tester address is invalid (if enabled). */
    DoIP_TxTcp_PrepareTransmit(ConnectionTcpIdx, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr,
      DOIP_DIAG_MSG_RES_CODE_INVALID_SRC_ADDR, TRUE);
  }
  else if ( (DoIP_GetTesterAddrOfTester(DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx)) != DOIP_ADDR_ANY) &&
            (DoIP_GetTesterAddrOfTester(DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx)) != srcAddr) )
#else
  if ( DoIP_GetTesterAddrOfTester(DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx)) != srcAddr )
#endif /* DOIP_DEFAULT_TESTER_ENABLED == STD_ON */
  {
    /* #30 Prepare to send error if tester address is invalid. */
    DoIP_TxTcp_PrepareTransmit(ConnectionTcpIdx, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr,
      DOIP_DIAG_MSG_RES_CODE_INVALID_SRC_ADDR, TRUE);
  }
  else
  {
    /* #40 Otherwise handle target logical address. */
    retVal = DoIP_RxTcpDiag_HandleTargetLogicalAddress(ConnectionTcpIdx);
  }

  return retVal;
} /* DoIP_RxTcpDiag_HandleCopiedLogicalAddr() */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleTargetLogicalAddress()
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
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_HandleTargetLogicalAddress(                                  /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const DoIP_SizeOfRoutingActivationType routActIdx = DoIP_GetRoutingActivationIdxOfConnectionTcpDyn(ConnectionTcpIdx);
  const DoIP_RxHdrBufType *rxHdrBuf = DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx));
  DoIP_SizeOfChannelType channelIdx;
  uint32 diagMsgLength;
  uint32 hdrLen;
  uint16 srcAddr;
  uint16 tgtAddr;
#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
  /* use a local copy of the variable and pass them as function parameter so that they will not change during search */
  boolean pduSizeRouting = DoIP_IsPduSizeRoutingEnabled;
#else
  boolean pduSizeRouting = FALSE;
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT32(rxHdrBuf, 4u, hdrLen);                                                                             /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  IPBASE_GET_UINT16(rxHdrBuf, (DOIP_GEN_HDR_LEN_BYTE + 0u), srcAddr);                                                  /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  IPBASE_GET_UINT16(rxHdrBuf, (DOIP_GEN_HDR_LEN_BYTE + DOIP_ADDR_LEN_BYTE), tgtAddr);                                  /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  diagMsgLength = (uint32)(hdrLen - DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE);

  /* #10 Look up routing activation channel. */
  /* diagMsgLength was already checked for valid length within DoIP_RxTcpDiag_HandleDiagnosticMessage() */
  channelIdx = DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutAct(routActIdx, tgtAddr, diagMsgLength, pduSizeRouting);

  if ( channelIdx == DoIP_GetSizeOfChannel() )
  {
    channelIdx = DoIP_RxTcpDiag_GetChannelByTgtAddr(tgtAddr);

    /* #20 Prepare to send error depending on channel usage. */
    if ( channelIdx != DoIP_GetSizeOfChannel() )
    { /* target address is configured for an unreachable channel */
      DoIP_TxTcp_PrepareTransmit(ConnectionTcpIdx, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr,
        DOIP_DIAG_MSG_RES_CODE_TGT_UNREACHABLE, FALSE);
    }
    else
    {
      /* target address is not configured */
      DoIP_TxTcp_PrepareTransmit(ConnectionTcpIdx, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr,
        DOIP_DIAG_MSG_RES_CODE_UNKNOWN_TGT_ADDR, FALSE);
    }
  }
  else if ( DoIP_GetTpMaxLenOfChannel(channelIdx) < diagMsgLength )
  {
    /* #30 Prepare to send error if target protocol length exeeded. */
    DoIP_TxTcp_PrepareTransmit(ConnectionTcpIdx, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr,
      DOIP_DIAG_MSG_RES_CODE_MSG_TOO_LARGE, FALSE);
  }
#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
  else if ( (pduSizeRouting == TRUE) && (DoIP_GetMaxPduSizeOfChannel(channelIdx) < diagMsgLength) )
  {
    /* #40 Prepare to send error if Pdu length exeeded (if enabled). */
    DoIP_TxTcp_PrepareTransmit(ConnectionTcpIdx, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr,
      DOIP_DIAG_MSG_RES_CODE_MSG_TOO_LARGE, FALSE);
  }
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */
#if ( DOIP_VERIFY_TARGET_ADDR_ENABLED == STD_ON )
  else if ( DoIP_CallVerifyTargetAddrDirect(tgtAddr) != E_OK )                                                         /* SBSW_DOIP_FUNCTION_POINTER_CALL */
  {
    /* #50 Prepare to send error if target address is invalid (if enabled). */
    DoIP_TxTcp_PrepareTransmit(ConnectionTcpIdx, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr,
      DOIP_DIAG_MSG_RES_CODE_UNKNOWN_TGT_ADDR, FALSE);
  }
#endif /* DOIP_VERIFY_TARGET_ADDR_ENABLED == STD_ON */
  else
  {
    /* #60 Accept target address and message length. */
    DoIP_SetChannelRxLastIdxOfConnectionTcpDyn(ConnectionTcpIdx, channelIdx);                                          /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    DoIP_SetChannelRxActiveOfConnectionTcpDyn(ConnectionTcpIdx, TRUE);                                                 /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    /* #70 Reset Verify Rx Pdu offset for new diagnostic message. */
    DoIP_SetVerifyRxPduOffsetOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                 /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    retVal = E_OK;
  }

  return retVal;
} /* DoIP_RxTcpDiag_HandleTargetLogicalAddress() */

#if ( DOIP_NACK_APPEND_REQ == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_AppendNackData()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpDiag_AppendNackData(                                                        /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2CONST(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr)                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there are data to append. */
  if ( PduInfoPtr->SduLength > 0u )
  {
    const DoIP_SizeOfTesterType testerIdx = DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx);

    /* #20 Check if tester could be determined. */
    if ( testerIdx != DoIP_GetSizeOfTester() )
    {
      const DoIP_DiagNAckOffsetOfTesterDynType diagNAckOffset = DoIP_GetDiagNAckOffsetOfTesterDyn(testerIdx);
      const PduLengthType diagNAckNumByte = ((PduLengthType)DoIP_GetDiagNAckBufEndIdxOfTester(testerIdx) -
                                             (PduLengthType)DoIP_GetDiagNAckBufStartIdxOfTester(testerIdx));

      /* #30 Check if acknowledge message shall contain user data. */
      if ( diagNAckNumByte > 0u )
      {
        uint32 bytesToCopyTester = (diagNAckNumByte - diagNAckOffset);
        uint32 bytesToCopy = ((uint32)(PduInfoPtr->SduLength) - (uint32)(*ReadDataLenPtr));

        /* #40 Check and set max bytes to copy. */
        if ( bytesToCopy > bytesToCopyTester )
        {
          bytesToCopy = bytesToCopyTester;
        }

        /* #50 Copy data to ach/nack buffer if there are bytes to copy. */
        if ( bytesToCopy > 0u )
        {
          /* PRQA S 0310, 0314 2 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
          VStdLib_MemCpy(DOIP_A_P2VAR(void)DoIP_GetAddrDiagNAckBuf(DoIP_GetDiagNAckBufStartIdxOfTester(testerIdx) +    /* SBSW_DOIP_DiagNAckBuf_AND_CONST_POINTER_FORWARD */
            diagNAckOffset), DOIP_A_P2CONST(void)&PduInfoPtr->SduDataPtr[*ReadDataLenPtr], bytesToCopy);

          DoIP_SetDiagNAckOffsetOfTesterDyn(testerIdx, (diagNAckOffset + bytesToCopy));                                /* SBSW_DOIP_RegisterTester */
        }
      }
    }
  }
} /* DoIP_RxTcpDiag_AppendNackData() */
#endif /* DOIP_NACK_APPEND_REQ == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_VerifyRxPdu()
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
/* PRQA S 3206 5 */ /* MD_DoIP_3206 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_VerifyRxPdu(                                                 /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr) /* PRQA S 3673 */ /* MD_DoIP_16.7 */                  /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const uint32 msgReqMinLength = DOIP_GEN_HDR_LEN_BYTE + DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE;
  const uint32 msgVerMaxLength = msgReqMinLength + DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH;
  DoIP_RxMsgOffsetOfConnectionTcpDynType rxMsgOffset = DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx);
  boolean returnImmediately = FALSE;
  uint64 msgLength;
  uint32 hdrLen;

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT32(DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx)), 4u, hdrLen);      /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  msgLength = (uint64)hdrLen + DOIP_GEN_HDR_LEN_BYTE;

  /* #10 Check if all data are received to verify the Pdu. */
#if ( DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u )
  if ( (rxMsgOffset >= msgReqMinLength) &&
       (rxMsgOffset <  msgLength) &&
       (rxMsgOffset <  msgVerMaxLength) )
  {
    const uint32 bytesToCopy = (uint32)DOIP_MIN(((uint64)msgVerMaxLength - rxMsgOffset), (msgLength - rxMsgOffset));

    /* #20 Copy data to header buffer if there are bytes to copy (if enabled). */
    DoIP_RxTcpGen_CopyDataToHeaderBuffer(ConnectionTcpIdx, PduInfoPtr, ReadDataLenPtr, bytesToCopy);                   /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
    rxMsgOffset = DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx);

    if ( (rxMsgOffset == msgLength) ||
         (rxMsgOffset == msgVerMaxLength) )
    { /* message header copied completely */
#else
  DOIP_DUMMY_STATEMENT(PduInfoPtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  DOIP_DUMMY_STATEMENT(ReadDataLenPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

  if ( (rxMsgOffset == msgReqMinLength) && (DoIP_GetVerifyRxPduOffsetOfConnectionTcpDyn(ConnectionTcpIdx) == 0u) )
  {
    DoIP_SetVerifyRxPduOffsetOfConnectionTcpDyn(ConnectionTcpIdx, 1u);                                                 /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    { /* message header copied completely */
#endif /* DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u */

      /* #30 Verify Rx Pdu if message header is received completely. */
      retVal = DoIP_RxTcpDiag_HandleCopiedVerifyRxPdu(ConnectionTcpIdx, hdrLen, BufferSizePtr);                        /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    }
#if ( DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u )
    else
    {
      /* #40 Otherwise set buffer size to length of pending message part (if enabled). */
      uint32 bufSize = (uint32)DOIP_MIN(((uint64)msgVerMaxLength - rxMsgOffset), (msgLength - rxMsgOffset));           /* INTERNAL_NOTE_DOIP_CAST_HEADER_ALREADY_RECEIVED */
      DoIP_Util_CheckBufferSizeAndModify(bufSize, BufferSizePtr);                                                      /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
      retVal = DOIP_E_PENDING;
    }
#endif /* DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u */
    returnImmediately = TRUE;
  }

  /* #50 Check if message part is received completely. */
  if ( (returnImmediately == FALSE) &&
        ((rxMsgOffset >= msgVerMaxLength) ||
         (rxMsgOffset >= msgLength)) )
  {
    retVal = E_OK;
  }

  return retVal;
} /* DoIP_RxTcpDiag_VerifyRxPdu() */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleCopiedVerifyRxPdu()
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
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_HandleCopiedVerifyRxPdu(                                     /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint32 HdrLen,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_LENGTH */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr)                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const DoIP_RxHdrBufType *rxHdrBuf = DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx));
  DoIP_SizeOfChannelType channelIdx;
  uint16 srcAddr;
  uint16 tgtAddr;
#if ( DOIP_VERIFY_RX_PDU_ENABLED == STD_ON )
  const PduInfoType *pduInfoPtr;
# if ( DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u )
  PduInfoType pduInfo;
  pduInfo.SduDataPtr = DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx) +
    (DOIP_GEN_HDR_LEN_BYTE + DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE));
  pduInfo.SduLength =
    (PduLengthType)DOIP_MIN(DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH, (HdrLen - DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE));
  pduInfoPtr = &pduInfo;
# else
  pduInfoPtr = NULL_PTR;
# endif /* DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u */
#endif /* DOIP_VERIFY_RX_PDU_ENABLED == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT16(rxHdrBuf, (DOIP_GEN_HDR_LEN_BYTE + 0u), srcAddr);                                                  /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  IPBASE_GET_UINT16(rxHdrBuf, (DOIP_GEN_HDR_LEN_BYTE + DOIP_ADDR_LEN_BYTE), tgtAddr);                                  /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  /* #10 Get channel if channel is invalid. */
  if ( DoIP_IsChannelRxActiveOfConnectionTcpDyn(ConnectionTcpIdx) )
  {
    channelIdx = DoIP_GetChannelRxLastIdxOfConnectionTcpDyn(ConnectionTcpIdx);

#if ( DOIP_VERIFY_RX_PDU_ENABLED == STD_ON )
    /* #20 Verify Rx Pdu (if enabled). */
    /* PRQA S 0310 3 */ /* MD_DoIP_11.4 */
    if ( DoIP_CallVerifyRxPduDirect(                                                                                   /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
          (const SoAd_SockAddrType*)DoIP_GetAddrLocIpAddrOfConnectionTcpDyn(ConnectionTcpIdx),
          (const SoAd_SockAddrType*)DoIP_GetAddrRemIpAddrOfConnectionTcpDyn(ConnectionTcpIdx),
          srcAddr, tgtAddr, pduInfoPtr) == E_OK )
#endif /* DOIP_VERIFY_RX_PDU_ENABLED == STD_ON */
    {
      const uint32 bytesLeft = (HdrLen - DOIP_DIAG_HDR_LEN_BYTE);

      /* #30 Call start of reception at PduR. */
      if ( PduR_DoIPTpStartOfReception(DoIP_GetPduRRxPduIdOfChannel(channelIdx), NULL_PTR, (PduLengthType)bytesLeft,   /* SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER_FORWARD */
            BufferSizePtr) != BUFREQ_OK )
      {
        /* #40 Prepare to send error if no buffer obtained. */
        DoIP_TxTcp_PrepareTransmit(ConnectionTcpIdx, DOIP_HDR_TYPE_DIAG_NACK, tgtAddr, srcAddr,
          DOIP_DIAG_MSG_RES_CODE_OUT_OF_MEMORY, FALSE);
        retVal = E_NOT_OK;
      }
      else
      {
        PduInfoType pduInfoLocal = { NULL_PTR, 0u };

        /* #50 Otherwise set target address for this socket connection and copy data to PduR. */
        DoIP_SetLastRxTgtAddrOfConnectionTcpDyn(ConnectionTcpIdx, tgtAddr);                                            /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

        retVal = DoIP_RxTcpDiag_CopyDataToPduR(ConnectionTcpIdx, BufferSizePtr, &pduInfoLocal);                        /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */

        if ( retVal == E_OK )
        {
          if ( bytesLeft < *BufferSizePtr )
          { /* upper layer has more buffer than expected */
            *BufferSizePtr = (PduLengthType)bytesLeft;                                                                 /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
          }
          DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                   /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

#if ( DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH == 0u )
          retVal = DOIP_E_PENDING;
#endif /* DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH == 0u */
        }
      }
    }
#if ( DOIP_VERIFY_RX_PDU_ENABLED == STD_ON )
    else
    {
      /* #60 Prepare to send an ack message and reject the diagnostic message if Rx Pdu is discarded (if enabled). */
      /* For ack message srcAddr is not required. It is assigned when the message is added to the TxTcpQueue within the
       * DoIP_TxTcp_FinishTransmit() call. */
      DoIP_TxTcp_PrepareTransmit(ConnectionTcpIdx, DOIP_HDR_TYPE_DIAG_ACK, tgtAddr, 0u, 0u, FALSE);
      retVal = E_NOT_OK;
    }
#endif /* DOIP_VERIFY_RX_PDU_ENABLED == STD_ON */
  }

  return retVal;
} /* DoIP_RxTcpDiag_HandleCopiedVerifyRxPdu() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if ( (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_CopyVerifiedUserData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_CopyVerifiedUserData(                                        /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  boolean QueryBufSize)                                                                                                /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const uint32 msgReqMinLength = DOIP_GEN_HDR_LEN_BYTE + DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE;
  const uint32 msgVerMaxLength = msgReqMinLength + DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH;
  const DoIP_RxMsgOffsetOfConnectionTcpDynType rxMsgOffset = DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx);
  const DoIP_VerifyRxPduOffsetOfConnectionTcpDynType rxVerifyOffset =
    DoIP_GetVerifyRxPduOffsetOfConnectionTcpDyn(ConnectionTcpIdx);
  uint32 msgHdrLength;
  uint32 hdrLen;

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT32(DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx)), 4u, hdrLen);      /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  msgHdrLength = DOIP_GEN_HDR_LEN_BYTE + hdrLen;

  if ( /* less than Pdu-max-data-length */
       ( (rxMsgOffset == msgHdrLength) &&
         (rxVerifyOffset < ((DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE + DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH) - hdrLen)) )
       ||
       /* at least Pdu-max-data-length */
       ( (rxMsgOffset == msgVerMaxLength) &&
         (rxVerifyOffset < DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH) )
     )
  {
    /* #10 Copy verified user data from header buffer to PduR if there are data to copy. */
    retVal = DoIP_RxTcpDiag_HandleCopyVerifiedUserData(ConnectionTcpIdx, hdrLen, BufferSizePtr, QueryBufSize);         /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }

  if ( (retVal != DOIP_E_PENDING) &&
       ( /* less than Pdu-max-data-length */
         ( (rxMsgOffset == msgHdrLength) &&
           (rxVerifyOffset >= ((DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE + DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH) - hdrLen)) )
         ||
         /* at least Pdu-max-data-length */
         ( (rxMsgOffset >= msgVerMaxLength) &&
           (rxVerifyOffset >= DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH)
         )
       )
     )
  {
    /* #20 Check if all verified data are copied. */
    retVal = E_OK;
  }

  return retVal;
} /* DoIP_RxTcpDiag_CopyVerifiedUserData() */
#endif /* (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) */

#if ( (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleCopyVerifiedUserData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_HandleCopyVerifiedUserData(                                  /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint32 HdrLen,                                                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_LENGTH */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  boolean QueryBufSize)                                                                                                /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  PduInfoType pduInfo = { NULL_PTR, 0u };
  DoIP_VerifyRxPduOffsetOfConnectionTcpDynType rxVerifyOffset =
    DoIP_GetVerifyRxPduOffsetOfConnectionTcpDyn(ConnectionTcpIdx);

  /* ----- Implementation ----------------------------------------------- */
  pduInfo.SduDataPtr = DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx) +
    (DOIP_GEN_HDR_LEN_BYTE + DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE + rxVerifyOffset));

  if ( QueryBufSize == TRUE )
  {
    /* #10 Query buffer size if not yet done. */
    pduInfo.SduLength = 0u;
    retVal = DoIP_RxTcpDiag_CopyDataToPduR(ConnectionTcpIdx, BufferSizePtr, &pduInfo);                                 /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }

  if ( retVal == E_OK )
  {
    pduInfo.SduLength =
      (PduLengthType)DOIP_MIN(DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH, (HdrLen - DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE));
    if ( pduInfo.SduLength > *BufferSizePtr )
    {
      pduInfo.SduLength = *BufferSizePtr;
    }

    /* #20 Copy verified user data to PduR. */
    retVal = DoIP_RxTcpDiag_CopyDataToPduR(ConnectionTcpIdx, BufferSizePtr, &pduInfo);                                 /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }

  if ( retVal == E_OK )
  {
    /* #30 Set calculate buffer size of pending message part if data could be copied. */
    uint32 bytesLeft;

    rxVerifyOffset += pduInfo.SduLength;
    DoIP_SetVerifyRxPduOffsetOfConnectionTcpDyn(ConnectionTcpIdx, rxVerifyOffset);                                     /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

    if ( HdrLen < (DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE + DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH) )
    {
      bytesLeft = (HdrLen - rxVerifyOffset - DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE);
    }
    else if ( rxVerifyOffset < DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH )
    {
      bytesLeft = (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH - rxVerifyOffset);
    }
    else
    {
      bytesLeft = (HdrLen - (DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE + DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH));
    }

    if ( bytesLeft < *BufferSizePtr )
    { /* upper layer has more buffer than expected */
      *BufferSizePtr = (PduLengthType)bytesLeft;                                                                       /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    }
    DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                         /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

    if ( bytesLeft == 0u )
    {
      /* #40 Send diagnostic message positive acknowledge and finish message if entire message is processed. */
      (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_DIAG_ACK,                                              /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        DoIP_GetLastRxTgtAddrOfConnectionTcpDyn(ConnectionTcpIdx), 0u, 0u, NULL_PTR, FALSE);
      /* call PduR */
      PduR_DoIPTpRxIndication(DoIP_GetPduRRxPduIdOfChannel(
        DoIP_GetChannelRxLastIdxOfConnectionTcpDyn(ConnectionTcpIdx)), E_OK);
      /* finish message */
      DoIP_SetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                     /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
      DoIP_SetChannelRxLastIdxOfConnectionTcpDyn(ConnectionTcpIdx, DoIP_GetSizeOfChannel());                           /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
      DoIP_SetChannelRxActiveOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                              /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    }
    else
    {
      retVal = DOIP_E_PENDING;
    }
  }

  return retVal;
} /* DoIP_RxTcpDiag_HandleCopyVerifiedUserData() */
#endif /* (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_CopyUserData()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpDiag_CopyUserData(                                                          /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr)                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const DoIP_RxMsgOffsetOfConnectionTcpDynType rxMsgOffset = DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx);
  uint32 hdrLen;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there are bytes to copy. */
  if ( rxMsgOffset >= (DOIP_GEN_HDR_LEN_BYTE + DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE + DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH) )
  {
    IPBASE_GET_UINT32(DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx)), 4u, hdrLen);    /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

    if ( DoIP_IsChannelRxActiveOfConnectionTcpDyn(ConnectionTcpIdx) )
    {
      /* #20 Copy data to PduR if channel is still active. */
      retVal = DoIP_RxTcpDiag_CopyDataToPduR(ConnectionTcpIdx, BufferSizePtr, PduInfoPtr);                             /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    }

    if ( retVal == E_OK )
    {
      /* #30 Set calculate buffer size of pending message part if data could be copied. */
      const uint64 msgLength = (uint64)hdrLen + DOIP_GEN_HDR_LEN_BYTE;
      const uint32 bytesLeft = (uint32)(msgLength - (rxMsgOffset + (uint64)(PduInfoPtr->SduLength)));                  /* INTERNAL_NOTE_DOIP_CAST_HEADER_ALREADY_RECEIVED */

      if ( bytesLeft < *BufferSizePtr )
      { /* upper layer has more buffer than expected */
        *BufferSizePtr = (PduLengthType)bytesLeft;                                                                     /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
      }
      DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

      if ( bytesLeft == 0u )
      {
        /* #40 Send diagnostic message positive acknowledge and finish message if entire message is processed. */
        (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_DIAG_ACK,                                            /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
          DoIP_GetLastRxTgtAddrOfConnectionTcpDyn(ConnectionTcpIdx), 0u, 0u, NULL_PTR, FALSE);
        /* call PduR */
        PduR_DoIPTpRxIndication(DoIP_GetPduRRxPduIdOfChannel(
          DoIP_GetChannelRxLastIdxOfConnectionTcpDyn(ConnectionTcpIdx)), E_OK);
        /* finish message */
        DoIP_SetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                   /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
        DoIP_SetChannelRxLastIdxOfConnectionTcpDyn(ConnectionTcpIdx, DoIP_GetSizeOfChannel());                         /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
        DoIP_SetChannelRxActiveOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                            /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
      }
      else
      {
        /* #50 Otherwise another part of the message is received so increment offset. */
        DoIP_SetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx, (rxMsgOffset + PduInfoPtr->SduLength));                /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
      }
    }

    *ReadDataLenPtr += PduInfoPtr->SduLength;                                                                          /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  }
} /* DoIP_RxTcpDiag_CopyUserData() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_CopyDataToPduR()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_CopyDataToPduR(                                              /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) LocalPduInfoPtr)                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  const DoIP_PduRRxPduIdOfChannelType rxPduId =
    DoIP_GetPduRRxPduIdOfChannel(DoIP_GetChannelRxLastIdxOfConnectionTcpDyn(ConnectionTcpIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to copy data to PduR. */
  if ( PduR_DoIPTpCopyRxData(rxPduId, LocalPduInfoPtr, BufferSizePtr) != BUFREQ_OK )                                   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  {
    /* #20 Look up current tester adress. */
    const DoIP_LastRxTgtAddrOfConnectionTcpDynType entityAddr =
      DoIP_GetLastRxTgtAddrOfConnectionTcpDyn(ConnectionTcpIdx);
    DoIP_TesterAddrOfTesterType testerAddr =
      DoIP_GetTesterAddrOfTester(DoIP_GetTesterIdxOfConnectionTcpDyn(ConnectionTcpIdx));

#if ( DOIP_DEFAULT_TESTER_ENABLED == STD_ON )
    if ( testerAddr == DOIP_ADDR_ANY )
    {
      /* #30 Look up current address if default tester is used (if enabled). */
      testerAddr = DoIP_GetTesterAddrOfConnectionTcpDyn(ConnectionTcpIdx);
    }
#endif /* DOIP_DEFAULT_TESTER_ENABLED == STD_ON */

    /* #40 Prepare to send error and skip message. */
    DoIP_TxTcp_PrepareTransmit(ConnectionTcpIdx, DOIP_HDR_TYPE_DIAG_NACK, entityAddr, testerAddr,
      DOIP_DIAG_MSG_RES_CODE_NETWORK_TRANSPROT, FALSE);
    /* call PduR */
    PduR_DoIPTpRxIndication(rxPduId, E_NOT_OK);
    DoIP_SetSkipRxMsgOfConnectionTcpDyn(ConnectionTcpIdx, TRUE);                                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    DoIP_SetChannelRxLastIdxOfConnectionTcpDyn(ConnectionTcpIdx, DoIP_GetSizeOfChannel());                             /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    DoIP_SetChannelRxActiveOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                                /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */

    retVal = E_NOT_OK;
  }

  return retVal;
} /* DoIP_RxTcpDiag_CopyDataToPduR() */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutAct()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelType, DOIP_CODE) DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutAct(                       /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfRoutingActivationType RoutActIdx,                                                                         /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 TgtAddr,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint32 DataLen,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_LENGTH */
  boolean PduSizeRouting)                                                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( DOIP_IF_API_ENABLED == STD_ON )
  DoIP_SizeOfChannelType channelIdx = DoIP_GetSizeOfChannel();
#else
  DoIP_SizeOfChannelType channelIdx;
#endif /* DOIP_IF_API_ENABLED == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_IF_API_ENABLED == STD_ON )
  /* #10 Check if at least one channel is refered by the routing activation (if enabled). */
  if ( DoIP_IsChannelIndUsedOfRoutingActivation(RoutActIdx) )
#endif /* DOIP_IF_API_ENABLED == STD_ON */
  {
#if ( DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_ON )
    /* #20 If routing activation refer to at least one channel with bitmasking iterate to find correct channel. */
    if ( DoIP_IsBitmaskingUsedOfRoutingActivation(RoutActIdx) )
    {
      channelIdx = DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutActUseIteration(RoutActIdx, TgtAddr);
    }
    /* #30 Otherwise use binary search to find correct channel. */
    else
#endif /* DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_ON */
    {
      channelIdx = DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutActUseBinSearch(RoutActIdx, TgtAddr, DataLen,
        PduSizeRouting);
    }
  }

  return channelIdx;
} /* DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutAct() */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutActUseBinSearch()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelType, DOIP_CODE) DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutActUseBinSearch(           /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfRoutingActivationType RoutActIdx,                                                                         /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 TgtAddr,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint32 DataLen,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_LENGTH */
  boolean PduSizeRouting)                                                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfChannelType channelIdx = DoIP_GetSizeOfChannel();

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Search channel with matching target address. */
  const DoIP_SizeOfChannelIndType indIdxFound = DoIP_RxTcpDiag_SearchChannel(RoutActIdx, TgtAddr);

  if ( indIdxFound != DoIP_GetSizeOfChannelInd() )
  {
    /* #20 Check if there is an other better fitting channel. */
    DoIP_SizeOfChannelIndType channelIndIdx = DoIP_RxTcpDiag_CheckChannel(RoutActIdx, TgtAddr, DataLen, indIdxFound,
      PduSizeRouting);
    channelIdx = DoIP_GetChannelInd(channelIndIdx);
  }

  return channelIdx;
} /* DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutActUseBinSearch() */

#if ( DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutActUseIteration()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 3206 3 */ /* MD_DoIP_3206 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelType, DOIP_CODE) DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutActUseIteration(           /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfRoutingActivationType RoutActIdx,                                                                         /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 TgtAddr)                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfChannelType channelIdx = DoIP_GetSizeOfChannel();
  DoIP_SizeOfChannelIndType channelIndIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all channels of the routing activation. */
  for ( channelIndIdx = DoIP_GetChannelIndStartIdxOfRoutingActivation(RoutActIdx);
        channelIndIdx < DoIP_GetChannelIndEndIdxOfRoutingActivation(RoutActIdx);
        channelIndIdx++ )
  {
    DoIP_SizeOfChannelType channelIdxTmp = DoIP_GetChannelInd(channelIndIdx);
    const DoIP_EcuAddrOfChannelType ecuAddr = DoIP_GetEcuAddrOfChannel(channelIdxTmp);
    const DoIP_BitMaskOfChannelType bitMask = DoIP_GetBitMaskOfChannel(channelIdxTmp);

    /* #20 Check if bitmask match and choose matching channel. */
    if ( (ecuAddr & bitMask) == (TgtAddr & bitMask) )
    {
      channelIdx = channelIdxTmp;
      break;
    }
  }

  return channelIdx;
} /* DoIP_RxTcpDiag_GetChannelByTgtAddrForRoutActUseIteration() */
#endif /* DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_GetChannelByTgtAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelType, DOIP_CODE) DoIP_RxTcpDiag_GetChannelByTgtAddr(                                 /* INTERNAL_NOTE_SBSW_OK */
  uint16 TgtAddr)                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfChannelType channelIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get channel by target address. */
#if ( DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_ON )
  channelIdx = DoIP_RxTcpDiag_GetChannelByTgtAddrUseIteration(TgtAddr);
#else
  channelIdx = DoIP_RxTcpDiag_GetChannelByTgtAddrUseBinSearch(TgtAddr);
#endif /* DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_ON */

  return channelIdx;
} /* DoIP_RxTcpDiag_GetChannelByTgtAddr() */

#if ( DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_OFF )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_GetChannelByTgtAddrUseBinSearch()
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
DOIP_LOCAL FUNC(DoIP_SizeOfChannelType, DOIP_CODE) DoIP_RxTcpDiag_GetChannelByTgtAddrUseBinSearch(                     /* INTERNAL_NOTE_SBSW_OK */
  uint16 TgtAddr)                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfChannelType channelIdx = DoIP_GetSizeOfChannel();
  DoIP_SizeOfChannelType channelIdxLeft = 0u;
  DoIP_SizeOfChannelType channelIdxRight = (DoIP_SizeOfChannelType)(DoIP_GetSizeOfChannel() - 1u);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all channels (binary search) until matching channel was found. */
  while ( channelIdxLeft <= channelIdxRight )
  {
    /* #20 Calculate middle index. */
    boolean searchFinished = FALSE;
    const DoIP_SizeOfChannelType channelIdxMiddle =
      (DoIP_SizeOfChannelType)(channelIdxLeft + ((DoIP_SizeOfChannelType)(channelIdxRight - channelIdxLeft) / 2u));
    const DoIP_EcuAddrOfChannelType ecuAddr = DoIP_GetEcuAddrOfChannel(channelIdxMiddle);

    if ( ecuAddr == TgtAddr )
    {
      /* #30 Finish search if matching index was found. */
      channelIdx = channelIdxMiddle;
      searchFinished = TRUE;
    }
    else
    {
      /* #40 Otherwise recalculate indexes for next iteration. */
      if ( ecuAddr > TgtAddr )
      { /* target address of found channel is bigger */
        if ( channelIdxMiddle == 0u )
        {
          searchFinished = TRUE;
        }
        else
        {
          channelIdxRight = (DoIP_SizeOfChannelType)(channelIdxMiddle - 1u);
        }
      }
      else
      { /* target address of found channel is smaller */
        if ( channelIdxMiddle == (DoIP_GetSizeOfChannel() - 1u) )
        {
          searchFinished = TRUE;
        }
        else
        {
          channelIdxLeft = (DoIP_SizeOfChannelType)(channelIdxMiddle + 1u);
        }
      }
    }

    /* #50 Finish search if index found or whole range was checked. */
    if ( searchFinished == TRUE )
    {
      break;
    }
  }

  return channelIdx;
} /* DoIP_RxTcpDiag_GetChannelByTgtAddrUseBinSearch() */
#endif /* DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_OFF */

#if ( DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_GetChannelByTgtAddrUseIteration()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelType, DOIP_CODE) DoIP_RxTcpDiag_GetChannelByTgtAddrUseIteration(                     /* INTERNAL_NOTE_SBSW_OK */
  uint16 TgtAddr)                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfChannelType channelIdx = DoIP_GetSizeOfChannel();
  DoIP_ChannelIterType idx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all channels until matching channel was found. */
  for ( idx = 0;
        idx < DoIP_GetSizeOfChannel();
        idx++ )
  {
    const DoIP_EcuAddrOfChannelType ecuAddr = DoIP_GetEcuAddrOfChannel(idx);
    const DoIP_BitMaskOfChannelType bitMask = DoIP_GetBitMaskOfChannel(idx);

    if ( (ecuAddr & bitMask) == (TgtAddr & bitMask) )
    {
      channelIdx = (DoIP_SizeOfChannelType)idx;
      break;
    }
  }

  return channelIdx;
} /* DoIP_RxTcpDiag_GetChannelByTgtAddrUseIteration() */
#endif /* DOIP_TARGET_ADDR_BIT_MASK_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_SearchChannel()
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
DOIP_LOCAL FUNC(DoIP_SizeOfChannelIndType, DOIP_CODE) DoIP_RxTcpDiag_SearchChannel(                                    /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfRoutingActivationType RoutActIdx,                                                                         /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 TgtAddr)                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfChannelIndType indIdxFound = DoIP_GetSizeOfChannelInd();
  DoIP_SizeOfChannelIndType idxLeft = DoIP_GetChannelIndStartIdxOfRoutingActivation(RoutActIdx);
  DoIP_SizeOfChannelIndType idxRight =
    (DoIP_SizeOfChannelIndType)(DoIP_GetChannelIndEndIdxOfRoutingActivation(RoutActIdx) - 1u);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all channels (binary search) until matching channel was found. */
  while ( idxLeft <= idxRight )
  {
    /* #20 Calculate middle index to get corresponding channel. */
    boolean searchFinished = FALSE;
    const DoIP_SizeOfChannelIndType idxMiddle =
      (DoIP_SizeOfChannelIndType)(idxLeft + ((DoIP_SizeOfChannelIndType)(idxRight - idxLeft) / 2u));
    const DoIP_SizeOfChannelType channelIdx = DoIP_GetChannelInd(idxMiddle);
    const DoIP_EcuAddrOfChannelType ecuAddr = DoIP_GetEcuAddrOfChannel(channelIdx);

    if ( ecuAddr == TgtAddr )
    {
      /* #30 Finish search if matching index was found. */
      indIdxFound = idxMiddle;
      searchFinished = TRUE;
    }
    else
    {
      /* #40 Otherwise recalculate indexes for next iteration. */
      if ( ecuAddr > TgtAddr )
      { /* target address of found channel is bigger */
        if ( idxMiddle == 0u )
        {
          searchFinished = TRUE;
        }
        else
        {
          idxRight = (DoIP_SizeOfChannelIndType)(idxMiddle - 1u);
        }
      }
      else
      { /* target address of found channel is smaller */
        if ( idxMiddle == (DoIP_SizeOfChannelIndType)(DoIP_GetChannelIndEndIdxOfRoutingActivation(RoutActIdx) - 1u) )
        {
          searchFinished = TRUE;
        }
        else
        {
          idxLeft = (DoIP_SizeOfChannelIndType)(idxMiddle + 1u);
        }
      }
    }

    /* #50 Finish search if index found or whole range was checked. */
    if ( searchFinished == TRUE )
    {
      break;
    }
  }

  return indIdxFound;
} /* DoIP_RxTcpDiag_SearchChannel() */

/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_CheckChannel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 3206 5 */ /* MD_DoIP_3206 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelIndType, DOIP_CODE) DoIP_RxTcpDiag_CheckChannel(                                     /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfRoutingActivationType RoutActIdx,                                                                         /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 TgtAddr,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint32 DataLen,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_LENGTH */
  DoIP_SizeOfChannelIndType ChannelIndIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  boolean PduSizeRouting)                                                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfChannelIndType retChannelIndIdx = ChannelIndIdx;
#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
  DoIP_MaxPduSizeOfChannelType bestMaxPduSize = 0u;
  boolean bestChannelFound = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if current channel is best. */
  if ( (DoIP_RxTcpDiag_PduSizeRoutValidateChannel(DoIP_GetChannelInd(retChannelIndIdx), DataLen, &bestMaxPduSize,      /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    PduSizeRouting) == E_OK) && ((PduSizeRouting == FALSE) || (DataLen == (uint32)bestMaxPduSize)) )
  { /* channel is default channel and Pdu size dependent routing is disabled or exact match is found */
    bestChannelFound = TRUE;
  }

  /* #20 Otherwise search best channel from start index to the right. */
  if ( bestChannelFound == FALSE )
  {
    DoIP_SizeOfChannelIndType idxLeft =
      DoIP_RxTcpDiag_SearchPduSizeRoutingGroupStartIndex(RoutActIdx, TgtAddr, ChannelIndIdx);

    retChannelIndIdx = DoIP_RxTcpDiag_SearchPduSizeRoutingGroupBestIndex(RoutActIdx, TgtAddr, DataLen, idxLeft,
      PduSizeRouting);
  }
#else
  DOIP_DUMMY_STATEMENT(RoutActIdx);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  DOIP_DUMMY_STATEMENT(TgtAddr);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  DOIP_DUMMY_STATEMENT(DataLen);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  DOIP_DUMMY_STATEMENT(PduSizeRouting); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */

  return retChannelIndIdx;
} /* DoIP_RxTcpDiag_CheckChannel() */

#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_SearchPduSizeRoutingGroupStartIndex()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelIndType, DOIP_CODE) DoIP_RxTcpDiag_SearchPduSizeRoutingGroupStartIndex(              /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfRoutingActivationType RoutActIdx,                                                                         /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 TgtAddr,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  DoIP_SizeOfChannelIndType ChannelIndIdx)                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfChannelIndType retChannelIndIdx = ChannelIndIdx;
  DoIP_SizeOfChannelIndType idx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform a search to find left index of pdu size routing group. */
  for ( idx = 0u;
        idx <= (ChannelIndIdx - DoIP_GetChannelIndStartIdxOfRoutingActivation(RoutActIdx));
        idx++ )
  {
    const DoIP_SizeOfChannelIndType idxTmp = (ChannelIndIdx - idx);
    const DoIP_SizeOfChannelType channelIdx = DoIP_GetChannelInd(idxTmp);
    const DoIP_EcuAddrOfChannelType ecuAddr = DoIP_GetEcuAddrOfChannel(channelIdx);

    if ( ecuAddr == TgtAddr )
    {
      retChannelIndIdx = idxTmp;
    }
    else
    {
      /* #20 Stop search if ecu address does not match. */
      break;
    }
  }

  return retChannelIndIdx;
} /* DoIP_RxTcpDiag_SearchPduSizeRoutingGroupStartIndex() */
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */

#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_SearchPduSizeRoutingGroupBestIndex()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(DoIP_SizeOfChannelIndType, DOIP_CODE) DoIP_RxTcpDiag_SearchPduSizeRoutingGroupBestIndex(               /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfRoutingActivationType RoutActIdx,                                                                         /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint16 TgtAddr,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint32 DataLen,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_LENGTH */
  DoIP_SizeOfChannelIndType ChannelIndStartIdx,                                                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  boolean PduSizeRouting)                                                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfChannelIndType retChannelIndIdx = ChannelIndStartIdx;
  DoIP_SizeOfChannelIndType idx;
  DoIP_MaxPduSizeOfChannelType bestMaxPduSize = 0u;

  /* ----- Implementation ----------------------------------------------- */
  for ( idx = ChannelIndStartIdx;
        idx < DoIP_GetChannelIndEndIdxOfRoutingActivation(RoutActIdx);
        idx++ )
  {
    boolean searchFinishedRight = FALSE;
    const DoIP_SizeOfChannelType channelIdx = DoIP_GetChannelInd(idx);
    const DoIP_EcuAddrOfChannelType ecuAddr = DoIP_GetEcuAddrOfChannel(channelIdx);

    if ( ecuAddr == TgtAddr )
    {
      /* #10 Look for all match channels for the best fitting channel up to now. */
      if ( DoIP_RxTcpDiag_PduSizeRoutValidateChannel(channelIdx, DataLen, &bestMaxPduSize, PduSizeRouting) == E_OK )   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      {
        retChannelIndIdx = idx;
        if ( (PduSizeRouting == FALSE) || (DataLen == bestMaxPduSize) )
        {
          /* #20 Finish search if default channel or exact match is found. */
          searchFinishedRight = TRUE;
        }
      }
    }
    else
    {
      /* #30 Otherwise stop search if ecu address does not match. */
      searchFinishedRight = TRUE;
    }

    if ( searchFinishedRight == TRUE )
    {
      break;
    }
  }

  return retChannelIndIdx;
} /* DoIP_RxTcpDiag_SearchPduSizeRoutingGroupBestIndex() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */

#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_PduSizeRoutValidateChannel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_RxTcpDiag_PduSizeRoutValidateChannel(                                  /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfChannelType ChannelIdx,                                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  uint32 DataLen,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_LENGTH */
  P2VAR(DoIP_MaxPduSizeOfChannelType, AUTOMATIC, DOIP_APPL_VAR) BestMaxPduSize,                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  boolean PduSizeRouting)                                                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const DoIP_MaxPduSizeOfChannelType maxPduSize = DoIP_GetMaxPduSizeOfChannel(ChannelIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Pdu size depending routing is enabled. */
  if ( PduSizeRouting == TRUE )
  {
    if ( (maxPduSize >= DataLen) &&
          ((*BestMaxPduSize == 0u) ||
           (*BestMaxPduSize > maxPduSize)) )
    {
      /* #20 Check if max Pdu size is better fitting. */
      *BestMaxPduSize = maxPduSize;                                                                                    /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
      retVal = E_OK;
    }
  }
  else
  {
    /* #30 Ohterwise check if channel is the defaul channel. */
    if ( DoIP_IsDefaultChannelOfChannel(ChannelIdx) )
    {
      retVal = E_OK;
    }
  }

  return retVal;
} /* DoIP_RxTcpDiag_PduSizeRoutValidateChannel() */
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */

#if ( (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) )
/**********************************************************************************************************************
 *  DoIP_RxTcpDiag_HandleRetryCopyVerifiedUserData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpDiag_HandleRetryCopyVerifiedUserData(void)                                  /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_ConnectionTcpIterType connectionTcpIdx;
  uint16 hdrType;
  uint32 hdrLen;

  /* ----- Implementation ----------------------------------------------- */
  for ( connectionTcpIdx = 0u;
        connectionTcpIdx < DoIP_GetSizeOfConnectionTcp();
        connectionTcpIdx++ )
  {
    const DoIP_RxHdrBufType *rxHdrBuf = DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(connectionTcpIdx));

    IPBASE_GET_UINT16(rxHdrBuf, 2u, hdrType);                                                                          /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

    /* #10 Check for all activated TCP connection if there is a pending diagnostic request. */
    if ( (DoIP_GetActivStateOfConnectionTcpDyn(connectionTcpIdx) == DOIP_ROUT_ACTIV_STATE_ACTIVATED) &&
         (hdrType == DOIP_HDR_TYPE_DIAG_REQ) )
    {
      const DoIP_SkipRxMsgOfConnectionTcpDynType skipRxMsg =
        (DoIP_SkipRxMsgOfConnectionTcpDynType)DoIP_IsSkipRxMsgOfConnectionTcpDyn(connectionTcpIdx);
      const DoIP_RxMsgOffsetOfConnectionTcpDynType rxMsgOffset =
        DoIP_GetRxMsgOffsetOfConnectionTcpDyn(connectionTcpIdx);
      uint64 msgLength;

      IPBASE_GET_UINT32(rxHdrBuf, 4u, hdrLen);                                                                         /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

      msgLength = (uint64)hdrLen + DOIP_GEN_HDR_LEN_BYTE;

      if ( (skipRxMsg == FALSE) && (hdrLen >= DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE) )
      {
        /* #20 Copy verified user data if there are some data and message should not be skipped. */
        PduLengthType bufferSize = DoIP_GetLastRxBufSizeOfConnectionTcpDyn(connectionTcpIdx);
        (void)DoIP_RxTcpDiag_CopyVerifiedUserData((DoIP_SizeOfConnectionTcpType)connectionTcpIdx, &bufferSize, TRUE);  /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      }

      if ( /* skip message if all data are received */
           ( (skipRxMsg == TRUE) &&
             (rxMsgOffset >= msgLength) ) ||
           /* finish message if no user data present */
           ( (hdrLen <= (DOIP_DIAG_MSG_REQ_MIN_LEN_BYTE + DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH)) &&
             (rxMsgOffset == msgLength) ) )
      {
        /* #30 Finish message if no user data present or skipped message are fully received. */
        DoIP_TxTcp_FinishTransmit((DoIP_SizeOfConnectionTcpType)connectionTcpIdx);

        DoIP_SetLastRxBufSizeOfConnectionTcpDyn(connectionTcpIdx, 0u);                                                 /* SBSW_DOIP_CSL02 */
        DoIP_SetRxMsgOffsetOfConnectionTcpDyn(connectionTcpIdx, 0u);                                                   /* SBSW_DOIP_CSL02 */
        DoIP_SetSkipRxMsgOfConnectionTcpDyn(connectionTcpIdx, FALSE);                                                  /* SBSW_DOIP_CSL02 */
      }
    }
  }
} /* DoIP_RxTcpDiag_HandleRetryCopyVerifiedUserData() */
#endif /* (DOIP_VERIFY_RX_PDU_ENABLED == STD_ON) && (DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH != 0u) */

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_RxTcpOem_HandleOemPayloadTypes()
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
 *
 *
 *
 *
 *
 */
/* PRQA S 3206 5 */ /* MD_DoIP_3206 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpOem_HandleOemPayloadTypes(                                                  /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_CONST) PduInfoPtr,                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) BufferSizePtr,  /* PRQA S 3673 */ /* MD_DoIP_16.7 */                  /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) ReadDataLenPtr) /* PRQA S 3673 */ /* MD_DoIP_16.7 */                  /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 hdrLen;
# if ( DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u )
  uint32 bytesToCopy;
  const DoIP_OemPayloadTypeTcpBuf2ConType ConnectionIdxOem = DoIP_GetOemPayloadTypeTcpBuf2Con();
  DoIP_RxMsgOffsetOfConnectionTcpDynType rxMsgOffset = DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx);
# else
  uint16 txHdrType = DOIP_HDR_TYPE_INVALID;
  PduInfoType rxUserData = { NULL_PTR, 0u };
  PduInfoType txUserData = { NULL_PTR, 0u };
  uint16 hdrType;
  uint8 flags;
# endif /* DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u */

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT32(DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx)), 4u, hdrLen);      /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  if ( hdrLen > DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE )
  {
    /* #10 In case of unsupported header lengt transmit an error. */
    DoIP_SetSkipRxMsgOfConnectionTcpDyn(ConnectionTcpIdx, TRUE);                                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_MAX_LEN, 0u, 0u, NULL_PTR,       /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      FALSE);
  }
# if ( DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u )
  else if ( (ConnectionIdxOem != DoIP_GetSizeOfConnection()) &&
           ((ConnectionIdxOem != ConnectionTcpIdx) || DoIP_IsOemPayloadTypeTcpBufIsTx()))
  {
    /* #20 In case of an unavailable buffer wait until buffer is free again (if enabled). */
    *BufferSizePtr = 0u;                                                                                               /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                         /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
  }
# endif /* DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u */
  else
  {
    /* #30 Otherwise process message depending on configuration. */
# if ( DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u )
    const uint64 msgLength = (uint64)hdrLen + DOIP_GEN_HDR_LEN_BYTE;

    /* #130 OEM payload types TCP buffer enabled. */
    if ( ConnectionIdxOem == DoIP_GetSizeOfConnection() )
    {
      /* #140 Occupy free buffer. */
      DoIP_SetOemPayloadTypeTcpBuf2Con(ConnectionTcpIdx);                                                              /* SBSW_DOIP_OemPayloadType */
    }

    /* #150 Check and set max bytes to copy. */
    bytesToCopy = (uint32)(msgLength - rxMsgOffset);                                                                   /* INTERNAL_NOTE_DOIP_CAST_HEADER_ALREADY_RECEIVED */
    if ( bytesToCopy > ((uint32)(PduInfoPtr->SduLength) - (uint32)(*ReadDataLenPtr)) )
    {
      bytesToCopy = ((uint32)(PduInfoPtr->SduLength) - (uint32)(*ReadDataLenPtr));
    }

    if ( bytesToCopy > 0u )
    {
      /* #160 Copy data to buffer if there are bytes to copy. */
      /* PRQA S 0310, 0314 2 */ /* MD_DoIP_11.4, MD_MSR_VStdLibCopy */
      VStdLib_MemCpy(DOIP_A_P2VAR(void)DoIP_GetAddrOemPayloadTypeTcpBuf(rxMsgOffset - DOIP_GEN_HDR_LEN_BYTE),          /* SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD */
        DOIP_A_P2CONST(void)&PduInfoPtr->SduDataPtr[*ReadDataLenPtr], bytesToCopy);

      rxMsgOffset += bytesToCopy;
      *ReadDataLenPtr += (PduLengthType)bytesToCopy;                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
      DoIP_SetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx, rxMsgOffset);                                            /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    }

    if ( rxMsgOffset == msgLength )
    {
      /* #170 Handle message if message is now copied completely. */
      DoIP_RxTcpOem_HandleCopiedOemPayloadTypes(ConnectionTcpIdx);
    }
    else
    {
      /* #180 Otherwise set buffer size to length of pending message part. */
      uint32 bufSize = (uint32)(msgLength - rxMsgOffset);                                                              /* INTERNAL_NOTE_DOIP_CAST_HEADER_ALREADY_RECEIVED */
      DoIP_Util_CheckBufferSizeAndModify(bufSize, BufferSizePtr);                                                      /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      DoIP_SetLastRxBufSizeOfConnectionTcpDyn(ConnectionTcpIdx, *BufferSizePtr);                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    }
# else
    /* #230 OEM payload types TCP buffer disabled. */
    DOIP_DUMMY_STATEMENT(PduInfoPtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    DOIP_DUMMY_STATEMENT(BufferSizePtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    DOIP_DUMMY_STATEMENT(ReadDataLenPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

    IPBASE_GET_UINT16(DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx)), 2u, hdrType);   /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

    /* #240 Set flags for callback. */
    flags = DOIP_OEM_PAYLOAD_TYPE_FLAG_PROT_TCP;
    if ( DoIP_GetActivStateOfConnectionTcpDyn(ConnectionTcpIdx) == DOIP_ROUT_ACTIV_STATE_ACTIVATED )
    {
      flags |= DOIP_OEM_PAYLOAD_TYPE_FLAG_ROUT_ACTIV;
    }

    if ( DoIP_CallOemPayloadTypeDirect(hdrType, &rxUserData, flags, &txHdrType, &txUserData) == E_NOT_OK )             /* SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_AND_CONST_POINTER_FORWARD */
    {
      /* #250 Send error if payload type are unknown. */
      (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_TYPE, 0u, 0u, NULL_PTR, FALSE); /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
    }
    else
    {
      /* #260 Send response if payload and header type are known. */
      if ( txHdrType != DOIP_HDR_TYPE_INVALID )
      {
        (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_OEM_SPECIFIC, txHdrType, 0u, 0u, NULL_PTR, FALSE);   /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
      }
    }

    /* finish message */
    DoIP_SetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
# endif /* DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u */
  }
} /* DoIP_RxTcpOem_HandleOemPayloadTypes() */
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

#if ( DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON )
# if ( DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u )
/**********************************************************************************************************************
 *  DoIP_RxTcpOem_HandleCopiedOemPayloadTypes()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_RxTcpOem_HandleCopiedOemPayloadTypes(                                            /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 txHdrType = DOIP_HDR_TYPE_INVALID;
  DoIP_OemPayloadTypeTcpBufType *oemTcpBuf = DoIP_GetAddrOemPayloadTypeTcpBuf(0u);
  PduInfoType rxUserData;
  PduInfoType txUserData;
  uint16 hdrType;
  uint8 flags;

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT16(DoIP_GetAddrRxHdrBuf(DoIP_GetRxHdrBufStartIdxOfConnectionTcp(ConnectionTcpIdx)), 2u, hdrType);     /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */

  /* #10 Set flags for callback. */
  flags = DOIP_OEM_PAYLOAD_TYPE_FLAG_PROT_TCP;
  if ( DoIP_GetActivStateOfConnectionTcpDyn(ConnectionTcpIdx) == DOIP_ROUT_ACTIV_STATE_ACTIVATED )
  {
    flags |= DOIP_OEM_PAYLOAD_TYPE_FLAG_ROUT_ACTIV;
  }

  rxUserData.SduDataPtr = oemTcpBuf;
  rxUserData.SduLength = (PduLengthType)(DoIP_GetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx) -
    DOIP_GEN_HDR_LEN_BYTE);

  /* use Rx buffer as Tx buffer to save RAM */
  txUserData.SduDataPtr = oemTcpBuf;
  txUserData.SduLength = DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE;

  if ( DoIP_CallOemPayloadTypeDirect(hdrType, &rxUserData, flags, &txHdrType, &txUserData) == E_NOT_OK )               /* SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_AND_CONST_POINTER_FORWARD */
  {
    /* #20 Send error if payload type are unknown. */
    (void)DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_GEN_NACK, DOIP_GEN_NACK_TYPE, 0u, 0u, NULL_PTR, FALSE);  /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */

    DoIP_SetOemPayloadTypeTcpBuf2Con(DoIP_GetSizeOfConnection());                                                      /* SBSW_DOIP_OemPayloadType */
  }
  else
  {
    /* #30 Check if payload and header type are known. */
    if ( txHdrType != DOIP_HDR_TYPE_INVALID )
    {
      /* #40 Check response length. */
      if ( txUserData.SduLength <= DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE )
      {
        DoIP_SetOemPayloadTypeTcpBufLen((uint16)txUserData.SduLength);                                                 /* SBSW_DOIP_OemPayloadType */
        if ( txUserData.SduLength > 0u )
        {
          DoIP_SetOemPayloadTypeTcpBufIsTx(TRUE);                                                                      /* SBSW_DOIP_OemPayloadType */
        }
        /* #50 Send response if length is valid. */
        if ( DoIP_TxTcp_Transmit(ConnectionTcpIdx, DOIP_HDR_TYPE_OEM_SPECIFIC, txHdrType, 0u, 0u, NULL_PTR, FALSE) ==  /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
            E_NOT_OK)
        {
          DoIP_SetOemPayloadTypeTcpBuf2Con(DoIP_GetSizeOfConnection());                                                /* SBSW_DOIP_OemPayloadType */
        }
      }
      else
      {
        /* #60 Ignore response with invalid length. */
        DoIP_SetOemPayloadTypeTcpBuf2Con(DoIP_GetSizeOfConnection());                                                  /* SBSW_DOIP_OemPayloadType */
      }
    }
    else
    {
      DoIP_SetOemPayloadTypeTcpBuf2Con(DoIP_GetSizeOfConnection());                                                    /* SBSW_DOIP_OemPayloadType */
    }
  }

  /* finish message */
  DoIP_SetRxMsgOffsetOfConnectionTcpDyn(ConnectionTcpIdx, 0u);                                                         /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
} /* DoIP_RxTcpOem_HandleCopiedOemPayloadTypes() */
# endif /* DOIP_OEM_PAYLOAD_TYPE_TCP_BUF_SIZE > 0u */
#endif /* DOIP_OEM_PAYLOAD_TYPE_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_HandleTpTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_HandleTpTransmit(                                                      /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfPduRTxPduIdType DoIPPduRTxId,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) DoIPPduRTxInfoPtr)                                                    /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const DoIP_SizeOfChannelType channelIdx = DoIP_GetChannelIdxOfPduRTxPduId(DoIPPduRTxId);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if TP session is active or requested for this channel. */
  if ( DoIP_GetTxMsgLenOfChannelDyn(channelIdx) == 0u )
  {
    const DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_GetConnectionTcpIdxOfTesterDyn(
      DoIP_GetTesterIdxOfChannel(channelIdx));

    /* #20 Check if tester is connected to channel. */
    if ( connectionTcpIdx != DoIP_GetSizeOfConnectionTcp() )
    {
      DoIP_SetTxMsgLenOfChannelDyn(channelIdx, DoIPPduRTxInfoPtr->SduLength);                                          /* SBSW_DOIP_CSL03 */

      /* #30 Transmit request. */
      /* Param2 of the transmit can be casted to uint32 because PduLengthType date type is less or equal to uint32. */
      retVal = DoIP_TxTcp_Transmit(connectionTcpIdx, DOIP_HDR_TYPE_DIAG_REQ, channelIdx,                               /* SBSW_DOIP_PARAM_NULL_POINTER_FORWARD */
        (uint32)DoIPPduRTxInfoPtr->SduLength, 0u, NULL_PTR, FALSE);

      if ( retVal == E_NOT_OK )
      {
        /* #40 Reset channel information on error. */
        DoIP_SetTxMsgLenOfChannelDyn(channelIdx, 0u);                                                                  /* SBSW_DOIP_CSL03 */
      }
    }
  }

  return retVal;
} /* DoIP_HandleTpTransmit() */

#if ( DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON )
/**********************************************************************************************************************
 *  DoIP_HandleTpCancelTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_HandleTpCancelTransmit(                                                /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfPduRTxPduIdType DoIPPduRTxId)                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const DoIP_SizeOfChannelType channelIdx = DoIP_GetChannelIdxOfPduRTxPduId(DoIPPduRTxId);
  const DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_GetConnectionTcpIdxOfTesterDyn(                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX_INC_INV */
    DoIP_GetTesterIdxOfChannel(channelIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check connection index. */
  if ( connectionTcpIdx != DoIP_GetSizeOfConnectionTcp() )
  {
    /* #20 Check if session is active. */
    if ( DoIP_IsTxTpSessionActiveOfConnectionTcpDyn(connectionTcpIdx) )
    {
      /* #30 Check if transmission is pending. */
      if ( DoIP_GetTxMsgLenOfChannelDyn(channelIdx) != 0u )
      {
        /* #40 Cancel request if connection is active and if transmission is pending. */
        if ( SoAd_TpCancelTransmit(DoIP_GetSoAdTxPduIdOfConnection(connectionTcpIdx)) == E_OK )
        {
          DoIP_SetTxTpCancelRequestedOfConnectionTcpDyn(connectionTcpIdx, TRUE);                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
          retVal = E_OK;
        }
      }
    }
  }

  return retVal;
} /* DoIP_HandleTpCancelTransmit() */
#endif /* DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON */

#if ( DOIP_PROVIDE_CANCEL_RECEIVE_API == STD_ON )
/**********************************************************************************************************************
 *  DoIP_HandleTpCancelReceive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_HandleTpCancelReceive(                                                 /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfPduRRxCancelPduIdType DoIPPduRRxId)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const DoIP_SizeOfChannelType channelIdx = DoIP_GetChannelIdxOfPduRRxCancelPduId(DoIPPduRRxId);
  const DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_GetConnectionTcpIdxOfTesterDyn(                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX_INC_INV */
    DoIP_GetTesterIdxOfChannel(channelIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check connection index. */
  if ( connectionTcpIdx != DoIP_GetSizeOfConnectionTcp() )
  {
    /* #20 Check if session is active. */
    if ( DoIP_IsChannelRxActiveOfConnectionTcpDyn(connectionTcpIdx) )
    {
      /* #30 Cancel request if connection is active. */
      if ( SoAd_TpCancelReceive(DoIP_GetRxCancelPduIdOfConnection(connectionTcpIdx)) == E_OK )
      {
        DoIP_SetRxTpCancelRequestedOfConnectionTcpDyn(connectionTcpIdx, TRUE);                                         /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
        retVal = E_OK;
      }
    }
  }

  return retVal;
} /* DoIP_HandleTpCancelReceive() */
#endif /* DOIP_PROVIDE_CANCEL_RECEIVE_API == STD_ON */

#if ( DOIP_IF_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  DoIP_HandleIfTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_HandleIfTransmit(                                                      /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfPduRTxPduIdType PduRTxPduId,                                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr)                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const DoIP_SizeOfChannelType channelIdx = DoIP_GetChannelIdxOfPduRTxPduId(PduRTxPduId);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if transmission is pending. */
  if ( DoIP_GetTxMsgLenOfChannelDyn(channelIdx) == 0u )
  {
    const DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_GetConnectionTcpIdxOfTesterDyn(
      DoIP_GetTesterIdxOfChannel(channelIdx));

    /* #20 Check connection index of connected tester. */
    if ( connectionTcpIdx != DoIP_GetSizeOfConnectionTcp() )
    {
      DoIP_SetTxMsgLenOfChannelDyn(channelIdx, PduInfoPtr->SduLength);                                                 /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL03 */

      /* #30 Trigger transmit. */
      retVal = DoIP_TxTcp_Transmit(connectionTcpIdx, DOIP_HDR_TYPE_DIAG_REQ, channelIdx, (uint16)PduInfoPtr->SduLength, /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
        0u, PduInfoPtr->SduDataPtr, FALSE);

      if ( retVal == E_NOT_OK )
      {
        /* #40 Reset channel information on error. */
        DoIP_SetTxMsgLenOfChannelDyn(channelIdx, 0u);                                                                  /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL03 */
      }
    }
  }

  return retVal;
} /* DoIP_HandleIfTransmit() */
#endif /* DOIP_IF_API_ENABLED == STD_ON */

#if ( DOIP_IF_API_ENABLED == STD_ON )
# if ( DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON )
/**********************************************************************************************************************
 *  DoIP_HandleIfCancelTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_HandleIfCancelTransmit(                                                /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfPduRTxPduIdType PduRTxPduId)                                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const DoIP_SizeOfChannelType channelIdx = DoIP_GetChannelIdxOfPduRTxPduId(PduRTxPduId);
  const DoIP_SizeOfConnectionTcpType connectionTcpIdx = DoIP_GetConnectionTcpIdxOfTesterDyn(                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX_INC_INV */
    DoIP_GetTesterIdxOfChannel(channelIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check connection index of connected tester. */
  if ( connectionTcpIdx != DoIP_GetSizeOfConnectionTcp() )
  {
    /* #20 Check session state. */
    if ( DoIP_IsTxTpSessionActiveOfConnectionTcpDyn(connectionTcpIdx) )
    {
      /* #30 Check if transmission is pending. */
      if ( DoIP_GetTxMsgLenOfChannelDyn(channelIdx) != 0u )
      {
        /* #40 Cancel IF transmit. */
        if ( SoAd_TpCancelTransmit(DoIP_GetSoAdTxPduIdOfConnection(connectionTcpIdx)) == E_OK )
        {
          DoIP_SetTxTpCancelRequestedOfConnectionTcpDyn(connectionTcpIdx, TRUE);                                       /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
          retVal = E_OK;
        }
      }
    }
  }

  return retVal;
} /* DoIP_HandleIfCancelTransmit() */
# endif /* DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON */
#endif /* DOIP_IF_API_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  DoIP_HandleSoAdTpCopyTxData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_HandleSoAdTpCopyTxData(                                             /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr,                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) AvailableDataPtr)                                                     /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

/* ----- Implementation ----------------------------------------------- */
#if ( DOIP_SUPPORT_SHUTDOWN == STD_ON )
  /* Check initialization state (if enabled). */
  /* with respect to SHUTDOWN state check DET only against UNINIT state and check callbacks against INIT state */
  if ( DoIP_State != DOIP_STATE_INIT )
  { /* DoIP_State is not INIT (it could be SHUTDOWN) */
    /* #10 Continue if DoIP_State is shutdown (if enabled). */
    /* nothing to do here */
  }
  else
#endif /* DOIP_SUPPORT_SHUTDOWN == STD_ON */
  /* check socket connection state */
  if ( DoIP_GetSoConStateOfConnectionDyn(ConnectionTcpIdx) != SOAD_SOCON_ONLINE )
  { /* socket connection is not online */
    /* #20 Continue if socket connection is offline. */
    /* nothing to do here */
  }
  else
  {
    /* #30 Otherwise copy data if socket connection is online. */
    retVal = DoIP_TxTcpQueue_Copy(ConnectionTcpIdx, PduInfoPtr, AvailableDataPtr);                                     /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }

  return retVal;
} /* DoIP_HandleSoAdTpCopyTxData() */

/**********************************************************************************************************************
 *  DoIP_HandleSoAdTpTxConfirmation()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_HandleSoAdTpTxConfirmation(                                                      /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx,                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  Std_ReturnType Result)                                                                                               /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_SUPPORT_SHUTDOWN == STD_ON )
  /* Check initialization state (if enabled). */
  /* with respect to SHUTDOWN state check DET only against UNINIT state and check callbacks against INIT state */
  if ( DoIP_State != DOIP_STATE_INIT )
  { /* DoIP_State is not INIT (it could be SHUTDOWN) */
    /* #10 Continue if DoIP_State is shutdown (if enabled). */
    /* nothing to do here */
  }
  else
#endif /* DOIP_SUPPORT_SHUTDOWN == STD_ON */
  {
    /* #20 Otherwise remove element from queue. */
    DoIP_TxTcpQueue_RemoveElement(ConnectionTcpIdx, Result);

#if ( DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON )
    /* #30 Reset cancellation (if enabed). */
    if ( DoIP_IsTxTpCancelRequestedOfConnectionTcpDyn(ConnectionTcpIdx) )
    {
      DoIP_SetTxTpCancelRequestedOfConnectionTcpDyn(ConnectionTcpIdx, FALSE);                                          /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    }
#endif /* DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON */

    if ( DoIP_IsSoConClosingOfConnectionDyn(ConnectionTcpIdx) &&
         (DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(ConnectionTcpIdx) == 0u) )
    {
      /* #40 Close socket if queue is empty or socket is already closing. */
      DoIP_Con_SoConClose(ConnectionTcpIdx);
    }
    else
    {
#if ( DOIP_TP_OPTIMIZED_ENABLED == STD_OFF )
      if ( DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(ConnectionTcpIdx) > 0u )
      {
        /* #50 Otherwise transmit pending element (if enabled). */
        DoIP_TxTcpQueue_TransmitElement(ConnectionTcpIdx);
      }
#endif /* DOIP_TP_OPTIMIZED_ENABLED == STD_OFF */
    }
  }
} /* DoIP_HandleSoAdTpTxConfirmation() */

/**********************************************************************************************************************
 *  DoIP_HandleSoAdTpStartOfReception()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_HandleSoAdTpStartOfReception(                                       /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionTcpType ConnectionTcpIdx)                                                                       /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* Check plausibility of parameters and states. */
#if ( DOIP_SUPPORT_SHUTDOWN == STD_ON )
  /* Check initialization state */
  /* with respect to SHUTDOWN state check DET only against UNINIT state and check callbacks against INIT state */
  if ( DoIP_State != DOIP_STATE_INIT )
  { /* DoIP_State is not INIT (it could be SHUTDOWN) */
    /* #10 Continue if DoIP_State is shutdown (if enabled). */
    /* nothing to do here */
  }
  else
#endif /* DOIP_SUPPORT_SHUTDOWN == STD_ON */
  /* check socket connection state */
  if ( DoIP_GetSoConStateOfConnectionDyn(ConnectionTcpIdx) != SOAD_SOCON_ONLINE )
  { /* socket connection is not online */
    /* #20 Continue if socket connection is offline. */
    /* nothing to do here */
  }
  else if ( DoIP_IsRxTpSessionActiveOfConnectionTcpDyn(ConnectionTcpIdx) )
  { /* TP Routing is already active */
    /* #30 Continue if TP routing is already active. */
    /* nothing to do here */
  }
  else
  {
    /* #40 Otherwise activate TP session if TP routing is not active. */
    DoIP_SetRxTpSessionActiveOfConnectionTcpDyn(ConnectionTcpIdx, TRUE);                                               /* SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02 */
    retVal = BUFREQ_OK;
  }

  return retVal;
} /* DoIP_HandleSoAdTpStartOfReception() */

/**********************************************************************************************************************
 *  DoIP_HandleSoAdIfRxIndication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_HandleSoAdIfRxIndication(                                                        /* INTERNAL_NOTE_SBSW_OK */
  DoIP_SizeOfConnectionType ConnectionIdx,                                                                             /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr)                                                           /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER */
{
  /* ----- Implementation ----------------------------------------------- */
  /* Check plausibility of all input parameters and states (if enabled). */
#if ( DOIP_SUPPORT_SHUTDOWN == STD_ON )
  /* Check initialization state */
  /* with respect to SHUTDOWN state check DET only against UNINIT state and check callbacks against INIT state */
  if ( DoIP_State != DOIP_STATE_INIT )
  { /* DoIP_State is not INIT (it could be SHUTDOWN) */
    /* #10 Continue if DoIP_State is shutdown (if enabled). */
    /* nothing to do here */
  }
  else
#endif /* DOIP_SUPPORT_SHUTDOWN == STD_ON */
  if ( DoIP_GetIpAddrStateOfConnectionDyn(ConnectionIdx) != SOAD_IPADDR_STATE_ASSIGNED )
  { /* no IP is assigned */
    /* #20 Continue if ip address is not assigned. */
    /* nothing to do here */
  }
  else if ( (DoIP_GetSoConStateOfConnectionDyn(ConnectionIdx) != SOAD_SOCON_ONLINE) ||
            DoIP_IsSoConClosingOfConnectionDyn(ConnectionIdx) )
  { /* socket connection is not online or requested to be closed */
    /* #30 Continue if socket connection is offline or closing. */
    /* nothing to do here */
  }
  else
  {
    /* #40 Otherwise handle request. */
    DoIP_RxUdp_HandleRxIndication(ConnectionIdx, PduInfoPtr);                                                          /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  }
} /* DoIP_HandleSoAdIfRxIndication() */

#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
/**********************************************************************************************************************
 *  DoIP_HandleDhcpEvent()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_HandleDhcpEvent(                                                                 /* INTERNAL_NOTE_SBSW_OK */
  SoAd_LocalAddrIdType LocalIpAddrId,                                                                                  /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  SoAd_DhcpEventType Event)                                                                                            /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Local Variables ---------------------------------------------- */
  DoIP_SizeOfLocalAddrType localAddrIdx = DoIP_GetSizeOfLocalAddr();
  uint16 optionCode;
  uint16 optionBufferLength = DOIP_DHCPVX_OPT_VENDOR_BUF_MAX_LEN;
  uint8  optionBuffer[DOIP_DHCPVX_OPT_VENDOR_BUF_MAX_LEN] = { 0u };

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if LocalIpAddrId is used for DoIP assignment. */
  if ( DoIP_Dhcp_GetLocalAddrIdxOfDhcpAssignmentByLocalIpAddrId(LocalIpAddrId, &localAddrIdx) == E_OK )                /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  {
# if ( DOIP_IPV6_ENABLED == STD_ON )
#  if ( DOIP_IPV4_ENABLED == STD_ON )
    SoAd_DomainType domain = DoIP_GetDomainTypeOfLocalAddr(localAddrIdx);
#  endif /* DOIP_IPV4_ENABLED == STD_ON */
# endif /* DOIP_IPV6_ENABLED == STD_ON */

    switch(Event)
    {
      case SOAD_DHCP_EVENT_TX_DISCOVER_SOLICIT: /* fall through */
      case SOAD_DHCP_EVENT_TX_REQUEST:          /* fall through */
# if ( DOIP_IPV6_ENABLED == STD_ON )
      case SOAD_DHCP_EVENT_TX_V6_RENEW:         /* fall through */
      case SOAD_DHCP_EVENT_TX_V6_REBIND:
# endif /* DOIP_IPV6_ENABLED == STD_ON */
      {
# if ( DOIP_IPV6_ENABLED == STD_ON )
#  if ( DOIP_IPV4_ENABLED == STD_ON )
        if ( domain == SOAD_AF_INET6 )
#  endif /* DOIP_IPV4_ENABLED == STD_ON */
        {
          optionCode = DOIP_DHCPV6_OPT_VENDOR_CLASS_OPT_CODE;
        }
#  if ( DOIP_IPV4_ENABLED == STD_ON )
        else
#  endif /* DOIP_IPV4_ENABLED == STD_ON */
# endif /* DOIP_IPV6_ENABLED == STD_ON */
# if ( DOIP_IPV4_ENABLED == STD_ON )
        {
          optionCode = DOIP_DHCPV4_OPT_VENDOR_CLASS_OPT_CODE;
        }
# endif /* DOIP_IPV4_ENABLED == STD_ON */

        /* #20 Write the Vendor Class data in case of tx event type. */
        DoIP_Dhcp_PrepareVendorClassTxBuf(optionCode, &optionBufferLength, optionBuffer);                              /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */

        /* #30 Call the SoAd service function to write Vendor Option in case of tx event type. */
        (void)SoAd_WriteDhcpOption(LocalIpAddrId, optionCode, optionBufferLength, optionBuffer);                       /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */

        break;
      }
      case SOAD_DHCP_EVENT_RX_OFFER_ADVERTISE:
      {
        /* ignore SOAD_DHCP_EVENT_RX_OFFER_ADVERTISE and wait for SOAD_DHCP_EVENT_RX_ACK_REPLY */
        break;
      }
      case SOAD_DHCP_EVENT_RX_ACK_REPLY:
      {
# if ( DOIP_IPV6_ENABLED == STD_ON )
#  if ( DOIP_IPV4_ENABLED == STD_ON )
        if ( domain == SOAD_AF_INET6 )
#  endif /* DOIP_IPV4_ENABLED == STD_ON */
        {
          optionCode = DOIP_DHCPV6_OPT_VENDOR_OPTS_OPT_CODE;
        }
#  if ( DOIP_IPV4_ENABLED == STD_ON )
        else
#  endif /* DOIP_IPV4_ENABLED == STD_ON */
# endif /* DOIP_IPV6_ENABLED == STD_ON */
# if ( DOIP_IPV4_ENABLED == STD_ON )
        {
          optionCode = DOIP_DHCPV4_OPT_VENDOR_OPTS_OPT_CODE;
        }
# endif /* DOIP_IPV4_ENABLED == STD_ON */

        /* #40 Read the supplied Vendor Opts data from the DHCP message if rx event type is ACK/REPLY. */
        if ( SoAd_ReadDhcpOption(LocalIpAddrId, optionCode, &optionBufferLength, optionBuffer) == E_OK )               /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
        {
          /* #50 Handle Vender Opts. */
          DoIP_Dhcp_HandleVendorOptsOption(localAddrIdx, optionCode, optionBufferLength, optionBuffer);                /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
        }

        break;
      }
      default:
      {
        /* ignore event */
        /* nothing to do here */
        break;
      }
    }
  }
} /* DoIP_HandleDhcpEvent() */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Measure_InitDroppedPacketCounter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Measure_InitDroppedPacketCounter(void)                                           /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset the dropped packet counters to zero. */
  DoIP_Measure_DroppedTcpPacketsCounter = 0u;
  DoIP_Measure_DroppedUdpPacketsCounter = 0u;
} /* DoIP_Measure_InitDroppedPacketCounter() */
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Measure_IncDroppedPacketCounterTcp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed. *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Measure_IncDroppedPacketCounterTcp(void)                                         /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Implementation ----------------------------------------------- */
  DOIP_BEGIN_CRITICAL_SECTION();
  /* #10 Check if the dropped TCP packet counter has not overflowed. */
  if ( DoIP_Measure_DroppedTcpPacketsCounter < DOIP_MEASURE_DROPPED_PACKET_COUNTER_MAX_VALUE )
  {
    /* #20 Increment the counter. */
    DoIP_Measure_DroppedTcpPacketsCounter++;
  }
  DOIP_END_CRITICAL_SECTION();
} /* DoIP_Measure_IncDroppedPacketCounterTcp() */
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Measure_IncDroppedPacketCounterUdp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed. *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Measure_IncDroppedPacketCounterUdp(void)                                         /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Implementation ----------------------------------------------- */
  DOIP_BEGIN_CRITICAL_SECTION();
  /* #10 Check if the dropped UDP packet counter has not overflowed. */
  if ( DoIP_Measure_DroppedUdpPacketsCounter < DOIP_MEASURE_DROPPED_PACKET_COUNTER_MAX_VALUE )
  {
    /* #20 Increment the counter. */
    DoIP_Measure_DroppedUdpPacketsCounter++;
  }
  DOIP_END_CRITICAL_SECTION();
} /* DoIP_Measure_IncDroppedPacketCounterUdp() */
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Measure_IncDroppedPacketCounterType()
 *********************************************************************************************************************/
/*!
 * Internal comment removed. *
 *
 *
 *
 *
 *
 */
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Measure_IncDroppedPacketCounterType(                                             /* INTERNAL_NOTE_SBSW_OK */
  DoIP_Measure_DroppedPacketCounterType CounterType)                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the counter type to be incremented is TCP. */
  if ( CounterType == DOIP_MEASURE_DROPPED_PACKET_COUNTER_TCP )
  {
    /* #20 Increment the dropped TCP packet counter. */
    DoIP_Measure_IncDroppedPacketCounterTcp();
  }
  /* #30 The counter type to be incremented is UDP. */
  else
  {
    /* #40 Increment the dropped UDP packet counter. */
    DoIP_Measure_IncDroppedPacketCounterUdp();
  }
} /* DoIP_Measure_IncDroppedPacketCounterType() */
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Measure_IncDroppedPacketCounter()
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
DOIP_LOCAL FUNC(void, DOIP_CODE) DoIP_Measure_IncDroppedPacketCounter(                                                 /* INTERNAL_NOTE_SBSW_OK */
  DoIP_Measure_DroppedPacketCounterType CounterType,                                                                   /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE */
  uint16 HdrType,                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  uint8 NackType)                                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the header type is general NACK. */
  if ( HdrType == DOIP_HDR_TYPE_GEN_NACK )
  {
    switch(NackType)
    {
      /* #20 Check if the GEN NACK type is to be considered for incrementing the packet drop counter. */
      case DOIP_GEN_NACK_FORMAT:
      case DOIP_GEN_NACK_MAX_LEN:
      case DOIP_GEN_NACK_INV_LEN:
      case DOIP_GEN_NACK_LEN_BYTE:
      {
        /* #30 Increment the dropped packet counter. */
        DoIP_Measure_IncDroppedPacketCounterType(CounterType);
        break;
      }
      default:
      {
        /* Nothing to do. */
        break;
      }
    }
  }
  /* #40 Check if the header type is diagnostic NACK. */
  else if ( HdrType == DOIP_HDR_TYPE_DIAG_NACK )
  {
    switch(NackType)
    {
      /* #50 Check if the diagnostic NACK type is to be considered for incrementing the packet drop counter. */
      case DOIP_DIAG_MSG_RES_CODE_INVALID_SRC_ADDR:
      case DOIP_DIAG_MSG_RES_CODE_UNKNOWN_TGT_ADDR:
      case DOIP_DIAG_MSG_RES_CODE_MSG_TOO_LARGE:
      {
        /* #60 Increment the dropped packet counter. */
        DoIP_Measure_IncDroppedPacketCounterType(CounterType);
        break;
      }
      default:
      {
        /* Nothing to do. */
        break;
      }
    }
  }
  else
  {
    /* Nothing to do. */
  }
} /* DoIP_Measure_IncDroppedPacketCounter() */
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_Measure_GetAndResetDroppedPacketCounter()
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
 *
 */
DOIP_LOCAL FUNC(Std_ReturnType, DOIP_CODE) DoIP_Measure_GetAndResetDroppedPacketCounter(                               /* INTERNAL_NOTE_SBSW_OK */
  DoIP_MeasurementIdxType MeasurementIdx,                                                                              /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  boolean MeasurementResetNeeded,                                                                                      /* INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED */
  P2VAR(DoIP_MeasurementDataType, AUTOMATIC, DOIP_APPL_VAR) MeasurementDataPtr)                                        /* INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  switch(MeasurementIdx)
  {
    /* #10 Check if the measurement index is that of the TCP dropped packets counter. */
    case DOIP_MEAS_DROP_TCP:
    {
      DOIP_BEGIN_CRITICAL_SECTION();
      if ( MeasurementDataPtr != NULL_PTR )
      {
        /* #20 Copy the TCP dropped packets counter value to a buffer, if measurement data pointer is not NULL_PTR. */
        *MeasurementDataPtr = DoIP_Measure_DroppedTcpPacketsCounter;                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
      }

      if ( MeasurementResetNeeded == TRUE )
      {
        /* #30 Reset the TCP dropped packets counter to zero if the reset flag is set to true. */
        DoIP_Measure_DroppedTcpPacketsCounter = 0u;
      }
      DOIP_END_CRITICAL_SECTION();

      retVal = E_OK;
      break;
    }

    /* #40 Check if the measurement index is that of the UDP dropped packets counter. */
    case DOIP_MEAS_DROP_UDP:
    {
      DOIP_BEGIN_CRITICAL_SECTION();
      if ( MeasurementDataPtr != NULL_PTR )
      {
        /* #50 Copy the UDP dropped packets counter value to a buffer, if measurement data pointer is not NULL_PTR. */
        *MeasurementDataPtr = DoIP_Measure_DroppedUdpPacketsCounter;                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
      }

      if ( MeasurementResetNeeded == TRUE )
      {
        /* #60 Reset the UDP dropped packets counter to zero if the reset flag is set to true. */
        DoIP_Measure_DroppedUdpPacketsCounter = 0u;
      }
      DOIP_END_CRITICAL_SECTION();

      retVal = E_OK;
      break;
    }

    /* #70 Check if the measurement index is that of ALL. */
    case DOIP_MEAS_ALL:
    {
      if ( MeasurementResetNeeded == TRUE )
      {
        /* #80 Reset the TCP and UDP dropped packets counter to zero if the reset flag is set to true. */
        DOIP_BEGIN_CRITICAL_SECTION();
        DoIP_Measure_DroppedTcpPacketsCounter = 0u;
        DoIP_Measure_DroppedUdpPacketsCounter = 0u;
        DOIP_END_CRITICAL_SECTION();
      }

      retVal = E_OK;
      break;
    }

    default:
    {
      /* #90 E_NOT_OK returned as the requested measurement index is not supported. */
      break;
    }
  }

  return retVal;
} /* DoIP_Measure_GetAndResetDroppedPacketCounter() */
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  DoIP_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, DOIP_CODE) DoIP_InitMemory(void)                                                                            /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Implementation ----------------------------------------------- */
#if ( (DOIP_SUPPORT_SHUTDOWN == STD_ON) || (DOIP_DEV_ERROR_DETECT == STD_ON) ) /* COV_DOIP_SUPPORTED */
  /* #10 Initialize state variable (if enabled). */
  DoIP_State = DOIP_STATE_UNINIT;
#endif /* (DOIP_SUPPORT_SHUTDOWN == STD_ON) || (DOIP_DEV_ERROR_DETECT == STD_ON) */

  /* #20 Reset configuration pointer. */
  DoIP_ConfigDataPtr = NULL_PTR;
} /* DoIP_InitMemory() */

/**********************************************************************************************************************
 *  DoIP_Init()
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
FUNC(void, DOIP_CODE) DoIP_Init(                                                                                       /* INTERNAL_NOTE_SBSW_OK */
  P2CONST(DoIP_ConfigType, AUTOMATIC, DOIP_CONST) DoIPConfigPtr)                                                       /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters (if enabled). */
  /* Check parameter 'DoIPConfigPtr' */
  if ( DoIPConfigPtr == NULL_PTR )
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  else if ( DoIP_Util_ValidateConfig(DoIPConfigPtr) == E_NOT_OK )                                                      /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  else
#else
  DOIP_DUMMY_STATEMENT(DoIPConfigPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Initialize configuration pointer. */
    DoIP_ConfigDataPtr = DoIPConfigPtr;

    /* #30 Initialize the module data structures. */
    DoIP_Util_Init();

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
    /* #40 Initialize the packet drop counters. (if enabled.) */
    DoIP_Measure_InitDroppedPacketCounter();
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

    /* #50 Initialize activation line states (if enabled). */
#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
    DoIP_ActivationLineInactiveRequest = FALSE;
# if ( DOIP_ACTIV_LINE_DEFAULT_ACTIVE == STD_ON )
    DoIP_ActivationLineState = DOIP_ACTIVATION_LINE_ACTIVE;
# else
    DoIP_ActivationLineState = DOIP_ACTIVATION_LINE_INACTIVE;
# endif /* DOIP_ACTIV_LINE_DEFAULT_ACTIVE == STD_ON */
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */

    /* #60 Initialize Pdu size routing data (if enabled). */
#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
    DoIP_IsPduSizeRoutingEnabled = FALSE;
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */

    /* #70 Initialize GID sync state (if enabled). */
#if ( DOIP_GID_SYNC_ENABLED == STD_ON )
    DoIP_GidInSync = FALSE;
#endif /* DOIP_GID_SYNC_ENABLED == STD_ON */

#if ( (DOIP_SUPPORT_SHUTDOWN == STD_ON) || (DOIP_DEV_ERROR_DETECT == STD_ON) ) /* COV_DOIP_SUPPORTED */
    DoIP_State = DOIP_STATE_INIT;
#endif /* (DOIP_SUPPORT_SHUTDOWN == STD_ON) || (DOIP_DEV_ERROR_DETECT == STD_ON) */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_INIT, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_Init() */

#if ( DOIP_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  DoIP_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, DOIP_CODE) DoIP_GetVersionInfo(                                                                             /* INTERNAL_NOTE_SBSW_OK */
  P2VAR(Std_VersionInfoType, AUTOMATIC, DOIP_APPL_VAR) versioninfo)                                                    /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters (if enabled). */
  /* Check parameter 'versioninfo' */
  if ( versioninfo == NULL_PTR )
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  else
# endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Write component data to versioninfo. */
    versioninfo->vendorID = DOIP_VENDOR_ID;                                                                            /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    versioninfo->moduleID = DOIP_MODULE_ID;                                                                            /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    versioninfo->sw_major_version = DOIP_SW_MAJOR_VERSION;                                                             /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    versioninfo->sw_minor_version = DOIP_SW_MINOR_VERSION;                                                             /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
    versioninfo->sw_patch_version = DOIP_SW_PATCH_VERSION;                                                             /* SBSW_DOIP_PARAM_VALID_POINTER_WRITE */
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_GET_VERSION_INFO, errorId);
  }
# else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_GetVersionInfo() */
#endif /* DOIP_VERSION_INFO_API == STD_ON */

/**********************************************************************************************************************
 *  DoIP_TpTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, DOIP_CODE) DoIP_TpTransmit(                                                                       /* INTERNAL_NOTE_SBSW_OK */
  PduIdType DoIPPduRTxId,                                                                                              /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) DoIPPduRTxInfoPtr)                                                    /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retVal = E_NOT_OK;
#else
  Std_ReturnType retVal;
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State != DOIP_STATE_INIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check parameter 'DoIPPduRTxId' */
  else if ( DoIPPduRTxId >= DoIP_GetSizeOfPduRTxPduId() )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  /* Check parameter 'DoIPPduRTxInfoPtr' */
  else if ( DoIPPduRTxInfoPtr == NULL_PTR )
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  /* Check parameter 'DoIPPduRTxInfoPtr' */
  else if ( DoIPPduRTxInfoPtr->SduLength == 0u )
  {
    errorId = DOIP_E_INVALID_PARAMETER;
  }
  else
# if ( DOIP_IF_API_ENABLED == STD_ON )
  /* Check 'channel' */
  if ( DoIP_GetApiTypeOfChannel(DoIP_GetChannelIdxOfPduRTxPduId(DoIPPduRTxId)) != DOIP_API_TYPE_TP )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  else
# endif /* DOIP_IF_API_ENABLED == STD_ON */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Handle TP transmit. */
    retVal = DoIP_HandleTpTransmit((DoIP_SizeOfPduRTxPduIdType)DoIPPduRTxId, DoIPPduRTxInfoPtr);                       /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_TP_TRANSMIT, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* DoIP_TpTransmit() */ /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  DoIP_TpCancelTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, DOIP_CODE) DoIP_TpCancelTransmit(                                                                 /* INTERNAL_NOTE_SBSW_OK */
  PduIdType DoIPPduRTxId)                                                                                              /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retVal = E_NOT_OK;
#else
  Std_ReturnType retVal;
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State != DOIP_STATE_INIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check parameter 'DoIPPduRTxId' */
  else if ( DoIPPduRTxId >= DoIP_GetSizeOfPduRTxPduId() )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  else
# if ( DOIP_IF_API_ENABLED == STD_ON )
  /* Check 'channel' */
  if ( DoIP_GetApiTypeOfChannel(DoIP_GetChannelIdxOfPduRTxPduId(DoIPPduRTxId)) != DOIP_API_TYPE_TP )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  else
# endif /* DOIP_IF_API_ENABLED == STD_ON */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON )
    /* #20 Handle cancelation of TP transmit (if enabled). */
    retVal = DoIP_HandleTpCancelTransmit((DoIP_SizeOfPduRTxPduIdType)DoIPPduRTxId);
#else
    DOIP_DUMMY_STATEMENT(DoIPPduRTxId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    retVal = E_NOT_OK;
#endif /* DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_TP_CANCEL_TRANSMIT, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* DoIP_TpCancelTransmit() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  DoIP_TpCancelReceive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, DOIP_CODE) DoIP_TpCancelReceive(                                                                  /* INTERNAL_NOTE_SBSW_OK */
  PduIdType DoIPPduRRxId)                                                                                              /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retVal = E_NOT_OK;
#else
  Std_ReturnType retVal;
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State != DOIP_STATE_INIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check parameter 'DoIPPduRRxId' */
  else if ( DoIPPduRRxId >= DoIP_GetSizeOfPduRRxCancelPduId() )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  else
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_PROVIDE_CANCEL_RECEIVE_API == STD_ON )
    /* #20 Handle cancelation request (if enabled). */
    retVal = DoIP_HandleTpCancelReceive((DoIP_SizeOfPduRRxCancelPduIdType)DoIPPduRRxId);
#else
    DOIP_DUMMY_STATEMENT(DoIPPduRRxId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    retVal = E_NOT_OK;
#endif /* DOIP_PROVIDE_CANCEL_RECEIVE_API == STD_ON */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_TP_CANCEL_RECEIVE, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* DoIP_TpCancelReceive() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  DoIP_IfTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 3206 3 */ /* MD_DoIP_3206 */
FUNC(Std_ReturnType, DOIP_CODE) DoIP_IfTransmit(                                                                       /* INTERNAL_NOTE_SBSW_OK */
  PduIdType id,                                                                                                        /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) info)                                                                 /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retVal = E_NOT_OK;
#else
  Std_ReturnType retVal;
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State != DOIP_STATE_INIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check parameter 'id' */
  else if ( id >= DoIP_GetSizeOfPduRTxPduId() )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  /* Check parameter 'info' */
  else if ( info == NULL_PTR )
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  /* Check parameter 'info' */
  else if ( info->SduDataPtr == NULL_PTR )
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  /* Check parameter 'info' */
  else if ( info->SduLength == 0u )
  {
    errorId = DOIP_E_INVALID_PARAMETER;
  }
  else
# if ( DOIP_IF_API_ENABLED == STD_ON )
  /* Check 'channel' */
  if ( DoIP_GetApiTypeOfChannel(DoIP_GetChannelIdxOfPduRTxPduId(id)) != DOIP_API_TYPE_IF )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  /* Check 'channel' */
  else if ( info->SduLength > ((PduLengthType)DoIP_GetIfTxBufEndIdxOfChannel(DoIP_GetChannelIdxOfPduRTxPduId(id)) -
                               (PduLengthType)DoIP_GetIfTxBufStartIdxOfChannel(DoIP_GetChannelIdxOfPduRTxPduId(id))) )
  {
    errorId = DOIP_E_INVALID_PARAMETER;
  }
  else
# endif /* DOIP_IF_API_ENABLED == STD_ON */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_IF_API_ENABLED == STD_ON )
    /* #20 Handle IF transmit (if enabled). */
    retVal = DoIP_HandleIfTransmit((DoIP_SizeOfPduRTxPduIdType)id, info);                                              /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
#else
    DOIP_DUMMY_STATEMENT(id);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    DOIP_DUMMY_STATEMENT(info); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    retVal = E_NOT_OK;
#endif /* DOIP_IF_API_ENABLED == STD_ON */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_IF_TRANSMIT, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* DoIP_IfTransmit() */ /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  DoIP_IfCancelTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 3206 2 */ /* MD_DoIP_3206 */
FUNC(Std_ReturnType, DOIP_CODE) DoIP_IfCancelTransmit(                                                                 /* INTERNAL_NOTE_SBSW_OK */
  PduIdType id)                                                                                                        /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retVal = E_NOT_OK;
#else
  Std_ReturnType retVal;
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State != DOIP_STATE_INIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check parameter 'id' */
  else if ( id >= DoIP_GetSizeOfPduRTxPduId() )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
# if ( DOIP_IF_API_ENABLED == STD_ON )
  /* Check 'channel' */
  else if ( DoIP_GetApiTypeOfChannel(DoIP_GetChannelIdxOfPduRTxPduId(id)) != DOIP_API_TYPE_IF )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
# endif /* DOIP_IF_API_ENABLED == STD_ON */
  else
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( (DOIP_IF_API_ENABLED == STD_ON) && (DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON) )
    /* #20 Handle IF cancelation request. */
    retVal = DoIP_HandleIfCancelTransmit((DoIP_SizeOfPduRTxPduIdType)id);
#else
    DOIP_DUMMY_STATEMENT(id); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    retVal = E_NOT_OK;
#endif /* (DOIP_IF_API_ENABLED == STD_ON) && (DOIP_PROVIDE_CANCEL_TRANSMIT_API == STD_ON) */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_IF_CANCEL_TRANSMIT, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* DoIP_IfCancelTransmit() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  DoIP_EnablePduSizeRouting()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, DOIP_CODE) DoIP_EnablePduSizeRouting(void)                                                                  /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
  uint8 errorId = DOIP_E_NO_ERROR;
#else
  uint8 errorId = DOIP_E_PDU_SIZE_ROUTING; /* pdu size routing not supported */
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state (if enabled). */
  if ( DoIP_State != DOIP_STATE_INIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  else
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
    /* #20 Activate Pdu size routing (if enabled). */
    DoIP_IsPduSizeRoutingEnabled = TRUE;
#else
  /* API disabled */
  /* nothing to do here */
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
# if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
# endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_ENABLE_PDU_SIZE_ROUTING, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_EnablePduSizeRouting() */

/**********************************************************************************************************************
 *  DoIP_DisablePduSizeRouting()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, DOIP_CODE) DoIP_DisablePduSizeRouting(void)                                                                 /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
  uint8 errorId = DOIP_E_NO_ERROR;
#else
  uint8 errorId = DOIP_E_PDU_SIZE_ROUTING; /* pdu size routing not supported */
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state (if enabled). */
  if ( DoIP_State != DOIP_STATE_INIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  else
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
    /* #20 Disable Pdu size routing (if enabled). */
    DoIP_IsPduSizeRoutingEnabled = FALSE;
#else
  /* API disabled */
  /* nothing to do here */
#endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
# if ( DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
# endif /* DOIP_SUPPORT_PDU_SIZE_ROUTING == STD_ON */
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_DISABLE_PDU_SIZE_ROUTING, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_DisablePduSizeRouting() */

/**********************************************************************************************************************
 *  DoIP_Shutdown()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, DOIP_CODE) DoIP_Shutdown(void)                                                                    /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call SoAd_Shutdown() (if enabled). */
#if ( DOIP_SUPPORT_SHUTDOWN == STD_ON )
# if ( DOIP_SHUTDOWN_FINISHED_CBK_SUPPORT == STD_ON )
  retVal = SoAd_Shutdown();
# else
  DoIP_State = DOIP_STATE_SHUTDOWN;
  retVal = SoAd_Shutdown();
# endif /* DOIP_SHUTDOWN_FINISHED_CBK_SUPPORT == STD_ON */
#else
  /* API disabled */
  /* nothing to do here */
  retVal = E_NOT_OK;
#endif /* DOIP_SUPPORT_SHUTDOWN == STD_ON */

  return retVal;
} /* DoIP_Shutdown() */

#if ( DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON )
/**********************************************************************************************************************
 *  DoIP_GetAndResetMeasurementData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, DOIP_CODE) DoIP_GetAndResetMeasurementData(                                                       /* INTERNAL_NOTE_SBSW_OK */
  DoIP_MeasurementIdxType MeasurementIdx,                                                                              /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  boolean MeasurementResetNeeded,                                                                                      /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  P2VAR(DoIP_MeasurementDataType, AUTOMATIC, DOIP_APPL_VAR) MeasurementDataPtr)                                        /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;
# if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retVal = E_NOT_OK;
# else
  Std_ReturnType retVal;
# endif /* DOIP_DEV_ERROR_DETECT == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
# if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check if DoIP is initialized. */
  /* Do not check 'MeasurementDataPtr' since it can be NULL_PTR. */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  else
# endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Handle Measurement Data Get-Reset request. */
    retVal = DoIP_Measure_GetAndResetDroppedPacketCounter(MeasurementIdx, MeasurementResetNeeded,
      MeasurementDataPtr);                                                                                             /* SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER_FORWARD */
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_GET_RESET_MEASURE_DATA, errorId);
  }
# else
  DOIP_DUMMY_STATEMENT(errorId);
# endif /* DOIP_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* DoIP_GetAndResetMeasurementData() */
#endif /* DOIP_GET_RESET_MEASUREMENT_DATA == STD_ON */

/**********************************************************************************************************************
 *  DoIP_MainFunction()
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
FUNC(void, DOIP_CODE) DoIP_MainFunction(void)                                                                          /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state (if enabled). */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  else
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_SUPPORT_SHUTDOWN == STD_ON )
    /* Check initialization state (if enabled). */
    /* with respect to SHUTDOWN state check DET only against UNINIT state and check callbacks against INIT state */
    if ( DoIP_State != DOIP_STATE_INIT )
    { /* DoIP_State is not INIT (it could be SHUTDOWN) */
      /* #20 Continue if DoIP_State is shutdown (if enabled). */
      /* nothing to do here */
    }
    else
#endif /* DOIP_SUPPORT_SHUTDOWN == STD_ON */
    /* #30 Assume that module is initialized otherwise. */
    {
      /* #40 Initiates connections by extracting socket connection identifier from SoAd. */
      if ( DoIP_Con_SoConInitAll(&errorId) == E_OK )                                                                   /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
      {
        /* #50 Handle module depending on activation line state if socket connection identifier are extracted. */
        DoIP_Con_HandleActLineStates();
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_MAIN_FUNCTION, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_MainFunction() */

/**********************************************************************************************************************
 *  DoIP_SoAdTpCopyTxData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_SoAdTpCopyTxData(                                                              /* INTERNAL_NOTE_SBSW_OK */
  PduIdType id,                                                                                                        /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) info,                                                                   /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  P2VAR(RetryInfoType, AUTOMATIC, DOIP_APPL_VAR) retry, /* PRQA S 3673 */ /* MD_DoIP_16.7 */                           /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) availableDataPtr)                                                     /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
#else
  BufReq_ReturnType retVal;
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check parameter 'id' */
  else if ( id >= DoIP_GetSizeOfConnectionTcp() )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  /* Check parameter 'info' */
  else if ( info == NULL_PTR )
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  /* Check parameter 'info' */
  else if ( (info->SduLength != 0u) &&
            (info->SduDataPtr == NULL_PTR) )
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  /* Check parameter 'retry' */
  else if ( retry != NULL_PTR )
  {
    errorId = DOIP_E_INVALID_PARAMETER; /* AUTOSAR */
  }
  /* Check parameter 'availableDataPtr' */
  else if ( availableDataPtr == NULL_PTR )
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  else
#else
  DOIP_DUMMY_STATEMENT(retry); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Handle SoAd TP copy tx data call. */
    retVal = DoIP_HandleSoAdTpCopyTxData((DoIP_SizeOfConnectionTcpType)id, info, availableDataPtr);                    /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_TP_COPY_TX_DATA, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* DoIP_SoAdTpCopyTxData() */ /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  DoIP_SoAdTpTxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, DOIP_CODE) DoIP_SoAdTpTxConfirmation(                                                                       /* INTERNAL_NOTE_SBSW_OK */
  PduIdType id,                                                                                                        /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  Std_ReturnType result)                                                                                               /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check parameter 'id' */
  else if ( id >= DoIP_GetSizeOfConnectionTcp() )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  /* Check parameter 'result' */
  else if ( (result != E_OK) &&
            (result != E_NOT_OK) )
  {
    errorId = DOIP_E_INVALID_PARAMETER;
  }
  else
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Handle SoAd TP txconfirmation call. */
    DoIP_HandleSoAdTpTxConfirmation((DoIP_SizeOfConnectionTcpType)id, result);
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_TP_TX_CONFIRMATION, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_SoAdTpTxConfirmation() */ /* PRQA S 6010, 6080 */ /* MD_MSR_STPTH, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  DoIP_SoAdTpCopyRxData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_SoAdTpCopyRxData(                                                              /* INTERNAL_NOTE_SBSW_OK */
  PduIdType id,                                                                                                        /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) info,                                                                   /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) bufferSizePtr)                                                        /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
#else
  BufReq_ReturnType retVal;
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check parameter 'id' */
  else if ( id >= DoIP_GetSizeOfConnectionTcp() )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  /* Check parameter 'info' */
  else if ( info == NULL_PTR )
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  /* Check parameter 'bufferSizePtr' */
  else if ( bufferSizePtr == NULL_PTR )
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  else
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Handle request. */
    retVal = DoIP_RxTcp_HandleCopyRxData((DoIP_SizeOfConnectionTcpType)id, info, bufferSizePtr, &errorId);             /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_TP_COPY_RX_DATA, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* DoIP_SoAdTpCopyRxData() */

/**********************************************************************************************************************
 *  DoIP_SoAdTpStartOfReception()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 3206 5 */ /* MD_DoIP_3206 */
FUNC(BufReq_ReturnType, DOIP_CODE) DoIP_SoAdTpStartOfReception(                                                        /* INTERNAL_NOTE_SBSW_OK */
  PduIdType id,                                                                                                        /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  P2VAR(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) info,            /* PRQA S 3673 */ /* MD_DoIP_16.7 */                   /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  PduLengthType TpSduLength,                                                                                           /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  P2VAR(PduLengthType, AUTOMATIC, DOIP_APPL_VAR) bufferSizePtr) /* PRQA S 3673 */ /* MD_DoIP_16.7 */                   /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
#else
  BufReq_ReturnType retVal;
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check parameter 'id' */
  else if ( id >= DoIP_GetSizeOfConnectionTcp() )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  /* Check parameter 'bufferSizePtr' */
  else if ( bufferSizePtr == NULL_PTR )
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  /* Check parameter 'DoIPPduRTxInfoPtr' */
  else if ( TpSduLength != 0u )
  {
    errorId = DOIP_E_INVALID_PARAMETER;
  }
  else
#else
  DOIP_DUMMY_STATEMENT(TpSduLength);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  DOIP_DUMMY_STATEMENT(bufferSizePtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    DOIP_DUMMY_STATEMENT(info); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

    /* #20 Handle SoAd TP start of reception. */
    retVal = DoIP_HandleSoAdTpStartOfReception((DoIP_SizeOfConnectionTcpType)id);
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_TP_START_OF_RECEPTION, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* DoIP_SoAdTpStartOfReception() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  DoIP_SoAdTpRxIndication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DOIP_CODE) DoIP_SoAdTpRxIndication(                                                                         /* INTERNAL_NOTE_SBSW_OK */
  PduIdType id,                                                                                                        /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  Std_ReturnType result)                                                                                               /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check parameter 'id' */
  else if ( id >= DoIP_GetSizeOfConnectionTcp() )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  /* Check parameter 'result' */
  else if ( (result != E_OK) &&
            (result != E_NOT_OK) )
  {
    errorId = DOIP_E_INVALID_PARAMETER;
  }
  else
#else
  DOIP_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_SUPPORT_SHUTDOWN == STD_ON )
    /* Check initialization state (if enabled). */
    /* with respect to SHUTDOWN state check DET only against UNINIT state and check callbacks against INIT state */
    if ( DoIP_State != DOIP_STATE_INIT )
    { /* DoIP_State is not INIT (it could be SHUTDOWN) */
      /* #20 Continue if DoIP_State is shutdown (if enabled). */
      /* nothing to do here */
    }
    else
#endif /* DOIP_SUPPORT_SHUTDOWN == STD_ON */
    {
      /* #30 Otherwise deactivate TP session. */
      DoIP_SetRxTpSessionActiveOfConnectionTcpDyn((DoIP_SizeOfConnectionTcpType)id, FALSE);                            /* SBSW_DOIP_CSL02 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_TP_RX_INDICATION, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_SoAdTpRxIndication() */

/**********************************************************************************************************************
 *  DoIP_SoAdIfRxIndication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, DOIP_CODE) DoIP_SoAdIfRxIndication(                                                                         /* INTERNAL_NOTE_SBSW_OK */
  PduIdType RxPduId,                                                                                                   /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  P2CONST(PduInfoType, AUTOMATIC, DOIP_APPL_VAR) PduInfoPtr)                                                           /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check parameter 'RxPduId' */
  else if ( RxPduId >=  DoIP_GetSizeOfConnection() )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  /* Check parameter 'RxPduId' */
  else if ( (RxPduId <  DoIP_GetSizeOfConnectionTcp()) ||
            (RxPduId >= DOIP_CONNECTION_TCP_UDP_TOTAL) )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  /* Check parameter 'PduInfoPtr' */
  else if ( PduInfoPtr == NULL_PTR )
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  /* Check parameter 'PduInfoPtr' */
  else if ( PduInfoPtr->SduDataPtr == NULL_PTR )
  {
    errorId = DOIP_E_PARAM_POINTER;
  }
  else
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Handle SoAd IF rx indication call. */
    DoIP_HandleSoAdIfRxIndication((DoIP_SizeOfConnectionType)RxPduId, PduInfoPtr);                                     /* SBSW_DOIP_PARAM_CONST_POINTER_FORWARD */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_IF_RX_INDICATION, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_SoAdIfRxIndication() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  DoIP_SoAdIfTxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, DOIP_CODE) DoIP_SoAdIfTxConfirmation(                                                                       /* INTERNAL_NOTE_SBSW_OK */
  PduIdType TxPduId)                                                                                                   /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  const DoIP_SizeOfConnectionType connectionIdx = (DoIP_SizeOfConnectionType)TxPduId;
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check parameter 'connectionIdx' ake 'TxPduId' */
  else if ( (connectionIdx >= DoIP_GetSizeOfConnection()) ||
            (connectionIdx <  DoIP_GetSizeOfConnectionTcp()) )
  {
    errorId = DOIP_E_INVALID_PDU_SDU_ID;
  }
  else
#else
  DOIP_DUMMY_STATEMENT(TxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Do nothing. */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_IF_TX_CONFIRMATION, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_SoAdIfTxConfirmation() */

/**********************************************************************************************************************
 *  DoIP_SoConModeChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, DOIP_CODE) DoIP_SoConModeChg(                                                                               /* INTERNAL_NOTE_SBSW_OK */
  SoAd_SoConIdType SoConId,                                                                                            /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  SoAd_SoConModeType Mode)                                                                                             /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;
  DoIP_SizeOfConnectionType connectionIdx = 0u;

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check 'SoConId' */
  else if ( DoIP_Con_GetConnectionIdxBySoConId(SoConId, &connectionIdx) != E_OK )                                      /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  {
    errorId = DOIP_E_INVALID_PARAMETER;
  }
  /* Check 'Mode' */
  else if ( (Mode != SOAD_SOCON_ONLINE) &&
            (Mode != SOAD_SOCON_RECONNECT) &&
            (Mode != SOAD_SOCON_OFFLINE) )
  {
    errorId = DOIP_E_INVALID_PARAMETER;
  }
  else
#else
  /* Check 'SoConId' */
  if ( DoIP_Con_GetConnectionIdxBySoConId(SoConId, &connectionIdx) == E_OK )                                           /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_SUPPORT_SHUTDOWN == STD_ON )
    /* Check initialization state (if enabled). */
    /* with respect to SHUTDOWN state check DET only against UNINIT state and check callbacks against INIT state */
    if ( DoIP_State != DOIP_STATE_INIT )
    { /* DoIP_State is not INIT (it could be SHUTDOWN) */
      /* #20 Continue if DoIP_State is shutdown (if enabled). */
      /* nothing to do here */
    }
    else
#endif /* DOIP_SUPPORT_SHUTDOWN == STD_ON */
    {
      /* #30 Otherwise handle request. */
      DoIP_Con_HandleSoConModeChg(SoConId, Mode, connectionIdx, &errorId);                                             /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_SO_CON_MODE_CHG, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_SoConModeChg() */

/**********************************************************************************************************************
 *  DoIP_LocalIpAddrAssignmentChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, DOIP_CODE) DoIP_LocalIpAddrAssignmentChg(                                                                   /* INTERNAL_NOTE_SBSW_OK */
  SoAd_SoConIdType SoConId,                                                                                            /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  SoAd_IpAddrStateType State)                                                                                          /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = DOIP_E_NO_ERROR;
  DoIP_SizeOfConnectionType connectionIdx = 0u;

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of all input parameters and states (if enabled). */
  /* Check initialization state */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check 'State' */
  else if ( (State != SOAD_IPADDR_STATE_ASSIGNED) &&
            (State != SOAD_IPADDR_STATE_ONHOLD) &&
            (State != SOAD_IPADDR_STATE_UNASSIGNED) )
  {
    errorId = DOIP_E_INVALID_PARAMETER;
  }
  /* Check 'SoConId' */
  else if ( DoIP_Con_GetConnectionIdxBySoConId(SoConId, &connectionIdx) != E_OK )                                      /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
  {
    errorId = DOIP_E_INVALID_PARAMETER;
  }
  else
#else
  /* Check 'SoConId' */
  if ( DoIP_Con_GetConnectionIdxBySoConId(SoConId, &connectionIdx) == E_OK )                                           /* SBSW_DOIP_PARAM_VALID_POINTER_FORWARD */
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_SUPPORT_SHUTDOWN == STD_ON )
    /* Check initialization state (if enabled). */
    /* with respect to SHUTDOWN state check DET only against UNINIT state and check callbacks against INIT state */
    if ( DoIP_State != DOIP_STATE_INIT )
    { /* DoIP_State is not INIT (it could be SHUTDOWN) */
      /* #20 Continue if DoIP_State is shutdown (if enabled). */
      /* nothing to do here */
    }
    else
#endif /* DOIP_SUPPORT_SHUTDOWN == STD_ON */
    {
      /* #30 Otherwise handle request. */
      DoIP_Con_HandleLocalIpAddrAssignmentChg(connectionIdx, State);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_LOC_IP_ADDR_ASSIGN_CHG, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_LocalIpAddrAssignmentChg() */

/**********************************************************************************************************************
 *  DoIP_ActivationLineSwitch()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DOIP_CODE) DoIP_ActivationLineSwitch(void)                                                                  /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
  uint8 errorId = DOIP_E_NO_ERROR;
#else
  uint8 errorId = DOIP_E_ACTIVATION_LINE; /* activation line switch not supported since callback is not configured */
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state (if enabled). */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  else
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
# if ( DOIP_SUPPORT_SHUTDOWN == STD_ON )
    /* Check initialization state (if enabled). */
    /* with respect to SHUTDOWN state check DET only against UNINIT state and check callbacks against INIT state */
    if ( DoIP_State != DOIP_STATE_INIT )
    { /* DoIP_State is not INIT (it could be SHUTDOWN) */
      /* #20 Continue if DoIP_State is shutdown (if enabled). */
      /* nothing to do here */
    }
    else
# endif /* DOIP_SUPPORT_SHUTDOWN == STD_ON */
    {
      DoIP_ActivationLineType state = DOIP_ACTIVATION_LINE_INACTIVE;

      /* #30 Otherwise set activation line states (if enabled). */
      DoIP_CallActivationLineStateDirect(&state);                                                                      /* SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_FORWARD */
      if ( state == DOIP_ACTIVATION_LINE_INACTIVE )
      {
        DoIP_ActivationLineState = DOIP_ACTIVATION_LINE_INACTIVE;

        /* #40 Mark if activation line state changes to inactive. */
        /* This is used to prevent that an activation line state to inactive is not detected because of a rewoking call
         * to this function before activation line state is handled in main function. */
        DoIP_ActivationLineInactiveRequest = TRUE;
      }
      else
      {
        DoIP_ActivationLineState = DOIP_ACTIVATION_LINE_ACTIVE;
      }
    }
#else
    /* API disabled */
    /* nothing to do here */
#endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
# if ( DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
# endif /* DOIP_ACTIV_LINE_CALLBACK_ENABLED == STD_ON */
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_ACTIVATION_LINE_SWITCH, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_ActivationLineSwitch() */

/**********************************************************************************************************************
 *  DoIP_ShutdownFinished()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, DOIP_CODE) DoIP_ShutdownFinished(void)                                                                      /* INTERNAL_NOTE_SBSW_OK */
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( DOIP_SHUTDOWN_FINISHED_CBK_SUPPORT == STD_ON )
  uint8 errorId = DOIP_E_NO_ERROR;
#else
  uint8 errorId = DOIP_E_SHUTDOWN_FINISHED; /* shutdown finished not supported since callback is not configured */
#endif /* DOIP_SHUTDOWN_FINISHED_CBK_SUPPORT == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state (if enabled). */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  else
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_SHUTDOWN_FINISHED_CBK_SUPPORT == STD_ON )
    /* Check initialization state (if enabled). */
    /* with respect to SHUTDOWN state check DET only against UNINIT state and check callbacks against INIT state */
    if ( DoIP_State != DOIP_STATE_INIT )
    { /* DoIP_State is not INIT (it could be SHUTDOWN) */
      /* #20 Continue if DoIP_State is shutdown (if enabled). */
      /* nothing to do here */
    }
    else
    {
      /* #30 Handle shutdown finished (if enabled). */
      DoIP_State = DOIP_STATE_SHUTDOWN;
      DoIP_CallShutdownFinishedDirect();                                                                               /* SBSW_DOIP_FUNCTION_POINTER_CALL */
    }
#else
    /* API disabled */
    /* nothing to do here */
#endif /* DOIP_SHUTDOWN_FINISHED_CBK_SUPPORT == STD_ON */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
# if ( DOIP_SHUTDOWN_FINISHED_CBK_SUPPORT == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
# endif /* DOIP_SHUTDOWN_FINISHED_CBK_SUPPORT == STD_ON */
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_SHUTDOWN_FINISHED, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_ShutdownFinished() */

/**********************************************************************************************************************
 *  DoIP_DhcpEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, DOIP_CODE) DoIP_DhcpEvent(                                                                                  /* INTERNAL_NOTE_SBSW_OK */
  SoAd_LocalAddrIdType LocalIpAddrId,                                                                                  /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
  SoAd_DhcpEventType Event)                                                                                            /* INTERNAL_NOTE_SBSW_PUBLIC_API_DATA */
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
  uint8 errorId = DOIP_E_NO_ERROR;
#else
  uint8 errorId = DOIP_E_DHCP_EVENT; /* dhcp event not supported since callback is not configured */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( DOIP_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of input parameter 'Event' and states (if enabled). */
  /* Do not check 'LocalIpAddrId' since its range is not constrained. */
  if ( DoIP_State == DOIP_STATE_UNINIT )
  {
    errorId = DOIP_E_UNINIT;
  }
  /* Check 'Event' */
  else if ( Event > SOAD_DHCP_EVENT_TX_V6_DECLINE )
  {
    errorId = DOIP_E_INVALID_PARAMETER;
  }
  else
#endif /* DOIP_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
# if ( DOIP_SUPPORT_SHUTDOWN == STD_ON )
    /* Check initialization state (if enabled). */
    /* with respect to SHUTDOWN state check DET only against UNINIT state and check callbacks against INIT state */
    if ( DoIP_State != DOIP_STATE_INIT )
    { /* DoIP_State is not INIT (it could be SHUTDOWN) */
      /* #20 Continue if DoIP_State is shutdown (if enabled). */
      /* nothing to do here */
    }
    else
# endif /* DOIP_SUPPORT_SHUTDOWN == STD_ON */
    {
      /* #30 Handle DHCP Event. */
      DoIP_HandleDhcpEvent(LocalIpAddrId, Event);
    }
#else
    /* API disabled */
    /* nothing to do here */
    DOIP_DUMMY_STATEMENT(LocalIpAddrId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    DOIP_DUMMY_STATEMENT(Event);         /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( DOIP_DEV_ERROR_REPORT == STD_ON )
# if ( DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON )
  if ( errorId != DOIP_E_NO_ERROR )
# endif /* DOIP_DHCP_OPT_VENDOR_CLASS == STD_ON */
  {
    (void)Det_ReportError(DOIP_MODULE_ID, DOIP_INSTANCE_ID, DOIP_SID_DHCP_EVENT, errorId);
  }
#else
  DOIP_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* DOIP_DEV_ERROR_REPORT == STD_ON */
} /* DoIP_DhcpEvent() */

#define DOIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* module specific MISRA deviations:

  MD_DoIP_11.1:
      Reason:     Casting to different function pointer type
      Risk:       Misinterpretation of data.
      Prevention: Code inspection.

  MD_DoIP_11.4:
      Reason:     Casting to different object pointer type
      Risk:       Misinterpretation of data.
      Prevention: Code inspection.

  MD_DoIP_16.7:
      Reason:     No pointer to const due to modification in a called function (maybe only in special variants) or
                  required by specification.
      Risk:       None.
      Prevention: None.

  MD_DoIP_21.1_CFG:
      Reason:     Error does not apply since prevention is given in configuration.
      Risk:       None.
      Prevention: None.

  MD_DoIP_21.1_IDX:
      Reason:     Indexing out of bounds prevented by complex mechanism (misinterpreted by test tool).
      Risk:       None.
      Prevention: None.

  MD_DoIP_0686:
      Reason:     All not initialized elements are overwritten later.
      Risk:       Uninitialized elements may remain.
      Prevention: Code inspection.

  MD_DoIP_3206:
      Reason:     Unused parameter due to configuration constraints in some variants.
      Risk:       None.
      Prevention: None.

  MD_DoIP_ObjectOnlyAccessedOnce:
      Reason:     There are generated structures and arrays which are sometimes only accessed by one function, in
                  either the translation unit where they are defined or in another translation unit. We have generated
                  and manually written source code and separate code and data structures. Due to preprocessing variants
                  the above situation can occur.
      Risk:       It isn't clear which code and data structures belong together.
      Prevention: Code inspection.

  MD_DoIP_ImplicitCharCast:
      Reason:     An expression of 'essentially character' type (char) is being converted to unsigned type, 'unsigned
                  char' on assignment. There are chars who get implicit converted to uint8 data. For readability there
                  is no explicit cast.
      Risk:       Misinterpretation of data.
      Prevention: Code inspection.

  MD_DoIP_Rule2.2_2985_2986:
      Reason:     This operation is redundant. The value of the result is always that of the left/right-hand operand.
                  In some configurations there are a redundant operation to keep the coplexity low.
      Risk:       None.
      Prevention: None.

  MD_DoIP_Rule2.2_2987:
      Reason:     This function call produces no side effects and is redundant.
                  Global data is set inside the called function by using the ComStackLib. Therefore, the function call
                  is required.
      Risk:       None.
      Prevention: None.

*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_DOIP_CSL01
    \DESCRIPTION      Access of array element with index generated by ComStackLib.
    \COUNTERMEASURE   \N  Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_DOIP_CSL02
    \DESCRIPTION      Access of array element with index checked against size of different array.
                      (Arrays Xyz[] and XyzDyn[] depend on ComStackLib size relation.)
    \COUNTERMEASURE   \N  Qualified use-case CSL02 of ComStackLib.

  \ID SBSW_DOIP_CSL03
    \DESCRIPTION      Access of array element with index modeled by indirection generated by ComStackLib.
    \COUNTERMEASURE   \N  Qualified use-case CSL03 of ComStackLib.

  \ID SBSW_DOIP_CSL03_CSL01
    \DESCRIPTION      Access of array element with index modeled by indirection generated by ComStackLib. The index to
                      access the indirection is a index generated by ComStackLib.
    \COUNTERMEASURE   \N  Qualified use-cases CSL01 and CSL03 of ComStackLib.

  \ID SBSW_DOIP_CSL02_CSL03
    \DESCRIPTION      Access of array element with a index checked against the size of different array generated by
                      ComStackLib. Additionally the index is modeled by indirection generated by ComStackLib.
    \COUNTERMEASURE   \N  Qualified use-cases CSL02 and CSL03 of ComStackLib.

  \ID SBSW_DOIP_CSL02_CSL03_CSL01
    \DESCRIPTION      Access of array element with a index checked against the size of different array generated by
                      ComStackLib. Additionally the index is modeled by indirection generated by ComStackLib. The index
                      to access the indirection is a index generated by ComStackLib.
    \COUNTERMEASURE   \N  Qualified use-cases CSL02, CSL03 and CSL01 of ComStackLib.

  \ID SBSW_DOIP_ARRAY_WRITE
    \DESCRIPTION      Write access to array.
    \COUNTERMEASURE   \N  Array is a local variable/buffer which points to valid memory location and can be accessed
                          with index respecting write size and size of memory location. The array is either accessed
                          with static indexes within this range or with indexes checked against the variable/buffer
                          size.

  \ID SBSW_DOIP_OemPayloadType
    \DESCRIPTION      Access of global element.
    \COUNTERMEASURE   \N  A global variable is accessed (without index).

  \ID SBSW_DOIP_RoutActivHandler
    \DESCRIPTION      Access of array element with index 0.
    \COUNTERMEASURE   \N  Routing Activation Handler is an array with the fix size of 1 and is always accessed with the
                          index 0.

  \ID SBSW_DOIP_RoutActivHandler_Data
    \DESCRIPTION      Access of array element with index from Routing Activation Handler. The index is checked against
                      size of different array.
    \COUNTERMEASURE   \N  The indexes used from DoIP_GetConnectionTcpIdxOfRoutActivHandler(),
                          DoIP_GetRoutingActivationIdxOfRoutActivHandler() and DoIP_GetTesterIdxOfRoutActivHandler()
                          are after initialization always valid or equals to DoIP_GetSizeOfXyz() of an array with same
                          size (qualified use-case CSL02 of ComStackLib).
                          These indexes are set to valid values in one single location in
                          DoIP_RxTcpRout_HandleCopiedRoutingActivationReq(). Since all values are set consistently it
                          is possible to use DoIP_GetConnectionTcpIdxOfRoutActivHandler() to check if the other valeus
                          are valid, too.
                          These indexes are set to DoIP_GetSizeOfXyz() in context of DoIP_SoConModeChg() or if the
                          routing activation response could be activated and sent successfully in context of
                          DoIP_SoAdTpCopyTxData() (--> DoIP_TxTcpQueue_CopyHeader()) or if routing activation is
                          pending and during succssfully retry in DoIP_MainFunction()
                          (--> DoIP_RxTcpRout_HandleRetryRoutingActivationAuthAndConf()).

  \ID SBSW_DOIP_TxTcpMgt
    \DESCRIPTION      Access of array element with calculated index used for a different array with same size generated
                      by ComStackLib. The calculation is based on function parameter and index stored in
                      DoIP_ConnectionTcpDyn.
    \COUNTERMEASURE   \N  The validity of the index passed as function parameter is defined at the function declaration
                          and has to be ensured by the caller. The index is calculated based on qualified use-cases
                          CSL01 and CSL03 of ComStackLib. The access to the array of different size is qualified
                          use-case CSL02.
                          After calling DoIP_Init() the queue is empty and all queue management elements are valid. New
                          elements are added within the DoIP_TxTcp_Transmit() function. The index is the index to the
                          first element (indicated by level). The index is relative between start and end
                          index of the tcp connection. The index passed to DoIP_TxTcpQueue_AddXyz() as function
                          parameter is calculated in DoIP_TxTcpQueue_Add() and is the index to the next free slot where
                          the new element can be addded. The data within the queue are valid after they get added by
                          DoIP_TxTcp_Transmit() and copied by CopyTxData call until they get removed within the
                          TxConfirmation call or they are removed if socon mode changes to offline.

  \ID SBSW_DOIP_RegisterTester
    \DESCRIPTION      Access of array element with index stored in DoIP_ConnectionTcpDyn for a different array with
                      same size.
    \COUNTERMEASURE   \N  The access to the array of different size is qualified use-case CSL02.
                          The data set with DoIP_RxTcpRout_RegisterTester() are DoIP_SetTesterIdxOfConnectionTcpDyn(),
                          DoIP_SetTesterAddrOfConnectionTcpDyn(), DoIP_RoutingActivationIdxOfConnectionTcpDyn() and
                          DoIP_ActivStateOfConnectionTcpDyn(). They are set to valid values if a routing activation
                          response is sent for a routing activation request or if the authentification or confirmation
                          is pending and they are reset to DoIP_GetSizeOfXyz() with the alive check timeout for routing
                          activations and they are reset if socon mode change to offline. At initialization time the
                          value is set to DoIP_GetSizeOfXyz().

  \ID SBSW_DOIP_RxHdrBuf_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to RxHdrBuf as function parameter with an index which could be
                      used to write to the corresponding memory location and the function forwards a const pointer.
    \COUNTERMEASURE   \N  The RxHdrBuf is used to store parts of different messages and has at least the size of
                          (buffer offset + bytes to copy). The messages which are stored within the buffer are the
                          received routing activation request (size 19 bytes) and the received alive check response
                          (size 10 bytes). A received diagnostic message is only stored partly within the buffer.
                          From the diagnostic message the generic header, the logical addresses and the configured
                          VerifyRxPdu data (size VerifyRxPduMaxDataLength bytes) are stored in the RxHdrBuf. The
                          RxHdrBuf is generated respecting the largest required size. The offset and the bytes to copy
                          are checked against the received message type within DoIP_RxTcp_HandleCopyRxData(). The
                          offset is the length of the already received message parts. The bytes to copy is the length
                          of a message part which should be copied.
                          The const pointer which is forwarded can be used to read data, only.

  \ID SBSW_DOIP_OemPayloadTypeUdpBuf
    \DESCRIPTION      The function forwards pointer to OemPayloadTypeUdpBuf as function parameter which could be used
                      to write to the corresponding memory location.
    \COUNTERMEASURE   \N  It's a buffer generated by ComStackLib. The size depends on the configured size and
                          additional the size of the DoIP generic header. If the feature is enabled the buffer have at
                          least a size of 8 bytes - the size of the DoIP generic header. Pointers passed to function
                          are defined within the valid range at the function declaration and can be accessed with index
                          respecting write size and size of memory location. This is ensured by the caller.

  \ID SBSW_DOIP_TxHdrBuf
    \DESCRIPTION      Write access to pointer. The pointer may be accessed with an index.
    \COUNTERMEASURE   \N  It's a fixed size buffer of 21 bytes generated by ComStackLib. The array is accessed with
                          static indexes within this range.

  \ID SBSW_DOIP_TxHdrBuf_FORWARD
    \DESCRIPTION      The function forwards pointer as function parameter which could be used to write to the
                      corresponding memory location. The pointer may be forwarded with an offset.
    \COUNTERMEASURE   \N  Pointer passed as function parameter points to a fixed size buffer of 21 bytes and is
                          generated by ComStackLib. The offset is always within this range. The called function writes
                          a static number of data into this buffer or a separate function parameter is used to indicate
                          the range.

  \ID SBSW_DOIP_IfTxBuf_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer as function parameter which could be used to write to the
                      corresponding memory location and forwards a const pointer.
    \COUNTERMEASURE   \N  It's a buffer generated by ComStackLib. The size depends on the configured size. The size of
                          the buffer is checked previously within the function DoIP_IfTransmit().
                          The const pointer which is forwarded can be used to read data, only.

  \ID SBSW_DOIP_DiagNAckBuf_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer as function parameter which could be used to write to the
                      corresponding memory location and forwards a const pointer.
    \COUNTERMEASURE   \N  It's a buffer generated by ComStackLib. The size depends on the configured size. A separate
                          function parameter is used to indicate the range of the buffer. This parameter is set
                          according to the sizes provided by ComStackLib via indirection (qualified use-case CSL03 of
                          ComStackLib).
                          The const pointer which is forwarded can be used to read data, only.

  \ID SBSW_DOIP_AliveCheckList
    \DESCRIPTION      Access of array element with index.
    \COUNTERMEASURE   \N  Alive Check List is a array with a fix size of the maximum number of TCP connections per
                          local address and is accessed with an index. Index may be fixed size or the number of TCP
                          connections per local address is counted. The array contains at least one element because
                          there is always at least one connection configured.

  \ID SBSW_DOIP_PARAM_VALID_INDEX
    \DESCRIPTION      Access of array element with index passed as a function parameter.
    \COUNTERMEASURE   \N  The validity of the index passed as function parameter is defined at the function declaration
                          and has to be ensured by the caller. Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL02
    \DESCRIPTION      Access of array element with index passed as a function parameter. The index is specified for a
                      different array with same size generated by ComStackLib.
    \COUNTERMEASURE   \N  The validity of the index passed as function parameter is defined at the function declaration
                          and has to be ensured by the caller. Qualified use-case CSL01 of ComStackLib. To access with
                          an index of a different array with same size is qualified use-case CSL02 of ComStackLib.

  \ID SBSW_DOIP_PARAM_VALID_INDEX_AND_CSL03
    \DESCRIPTION      Access of array element with index modeled by indirection generated by ComStackLib. The index
                      which is used to access the indirection is passed as function parameter.
    \COUNTERMEASURE   \N  The validity of the index passed as function parameter is defined at the function declaration
                          and has to be ensured by the caller. Qualified use-case CSL01.
                          The index modeled by indirection is qualified use-case CSL03 of ComStackLib.

  \ID SBSW_DOIP_PARAM_VALID_POINTER_WRITE
    \DESCRIPTION      Write access to pointer. The pointer used to write may depend on a function parameter and may be
                      passed to other functions or is a reference to a local variable/buffer which could be used to
                      write to the corresponding memory location. The pointer may be accessed with an index.
    \COUNTERMEASURE   \N  Pointer passed as function parameter or pointer to a local variable/buffer points to valid
                          memory location. This includes struct members in case pointer points to a struct type.
                          Pointers passed to function are defined within the valid range at the function declaration
                          and can be accessed with index respecting write size and size of memory location. This is
                          ensured by the caller.

  \ID SBSW_DOIP_PARAM_VALID_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer as function parameter or a reference to a local variable/buffer
                      which could be used to write to the corresponding memory location. The pointer may be forwarded
                      with an offset.
    \COUNTERMEASURE   \N  Pointers passed to function point to a valid memory range considering type or an additional
                          function parameter is used to describe pointer validity. The validity of the local
                          variable/buffer is ensured due to the scope. Pointers passed to function is defined within
                          the valid range at the function declaration and can be accessed with index respecting write
                          size and size of memory location. This is ensured by the caller.

  \ID SBSW_DOIP_PARAM_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards const pointer as function parameter or a reference to a local
                      variable/buffer which could be used to read the corresponding memory location. The pointer may be
                      forwarded with an offset or may be accessed with an index.
    \COUNTERMEASURE   \N  Pointers passed to function as const pointers can be used to read data only.

  \ID SBSW_DOIP_PARAM_NULL_POINTER_FORWARD
    \DESCRIPTION      The function forwards NULL_PTR as function parameter.
    \COUNTERMEASURE   \N  NULL_PTR is within the valid range of the called function.

  \ID SBSW_DOIP_PARAM_VALID_POINTER_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer as function parameter or a reference to a local variable/buffer
                      which could be used to write to the corresponding memory location and the function forwards a
                      const pointer as function parameter. The pointer may be forwarded with an offset or may be
                      accessed with an index.
    \COUNTERMEASURE   \N  Pointers passed to function point to a valid memory range considering type or an additional
                          function parameter is used to describe pointer validity. The validity of the local
                          variable/buffer is ensured due to the scope. Pointers passed to function are defined within
                          the valid range at the function declaration and can be accessed with index respecting write
                          size and size of memory location. This is ensured by the caller. The const pointers can be
                          used to read data only.

  \ID SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer as function parameter or a reference to a local variable/buffer
                      which could be used to write to the corresponding memory location. The pointer may be forwarded
                      with an offset or may be accessed with an index. Additionally the function forwards NULL_PTR as
                      function parameter.
    \COUNTERMEASURE   \N  Pointers passed to function point to a valid memory range considering type or an additional
                          function parameter are used to describe pointer validity. The validity of the local
                          variable/buffer is ensured due to the scope. Pointers passed to function are defined within
                          the valid range at the function declaration and can be accessed with index respecting write
                          size and size of memory location. This is ensured by the caller.
                          NULL_PTR is within the valid range of the called function.

  \ID SBSW_DOIP_FUNCTION_POINTER_CALL
    \DESCRIPTION      Calling a function pointer generated by ComStackLib.
    \COUNTERMEASURE   \S  The user of MICROSAR Safe shall verify that a configurable callback exists if configured.
                          Verification can be performed by a review of the code of the corresponding user. SMI-209063.

  \ID SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_FORWARD
    \DESCRIPTION      Calling a function pointer generated by ComStackLib and forwards a pointer to a local
                      variable/buffer which could be used to write to the corresponding memory location. The pointer
                      may be forwarded with an offset.
    \COUNTERMEASURE   \S  The user of MICROSAR Safe shall verify that a configurable callback exists if configured.
                          Verification can be performed by a review of the code of the corresponding user. The user of
                          MICROSAR Safe must ensure that he writes only to the memory area mentioned in the
                          safety-manual respecting data type and size. SMI-209063.

  \ID SBSW_DOIP_FUNCTION_POINTER_CALL_AND_LOCAL_POINTER_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      Calling a function pointer generated by ComStackLib and forwards a pointer to a local
                      variable/buffer which could be used to write to the corresponding memory location and forwards a
                      const pointer to a local variable/buffer which could be used to read data. The pointer may be
                      forwarded with an offset.
    \COUNTERMEASURE   \S  The user of MICROSAR Safe shall verify that a configurable callback exists if configured.
                          Verification can be performed by a review of the code of the corresponding user. The user of
                          MICROSAR Safe must ensure that he writes only to the memory area mentioned in the
                          safety-manual respecting data type and size and use the const pointer only to read data
                          respecting data type and size. SMI-209063.

SBSW_JUSTIFICATION_END */

/* INTERNAL_NOTE_SBSW_JUSTIFICATION_BEGIN

  \ID INTERNAL_NOTE_SBSW_DOIP_RoutActivHandler_Data
    \DESCRIPTION  see SBSW_DOIP_RoutActivHandler_Data.

  \ID INTERNAL_NOTE_SBSW_DOIP_TxTcpMgt
    \DESCRIPTION  see SBSW_DOIP_TxTcpMgt.

  \ID INTERNAL_NOTE_SBSW_OK
    \DESCRIPTION  The function parameter satisfy the parameter declaration on all places the function is called.

  \ID INTERNAL_NOTE_SBSW_PUBLIC_API_DATA
    \DESCRIPTION  The function parameter of a public API have to be checked for valid values/ranges before usage.

  \ID INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_LENGTH
    \DESCRIPTION  The function parameter is within the valid length range on all places the function is called.

  \ID INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_ENUM_RANGE
    \DESCRIPTION  The function parameter is within the valid enum range on all places the function is called.

  \ID INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX
    \DESCRIPTION  The function parameter is within the valid index range on all places the function is called.

  \ID INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_INDEX_INC_INV
    \DESCRIPTION  The function parameter is within the valid index range on all places the function is called.
                  After initialization the indirection is never set to a value greater than DoIP_GetSizeOfXyz().

  \ID INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER
    \DESCRIPTION  The function pointer satisfy the parameter declaration on all places the function is called.
                  The pointer is not NULL_PTR.

  \ID INTERNAL_NOTE_SBSW_DOIP_PARAM_VALID_POINTER_AND_NULL_POINTER
    \DESCRIPTION  The function pointer satisfy the parameter declaration on all places the function is called.
                  The pointer may be NULL_PTR.

  \ID INTERNAL_NOTE_SBSW_DOIP_PARAM_SOCKADDR_STRUCT
    \DESCRIPTION  The function parameter satisfy the parameter declaration on all places the function is called.
                  The parameter is an socket IP address or a struct/pointer containing a socket IP address. This
                  justificatin is used in combination with the DHCP vendor option.

  \ID INTERNAL_NOTE_SBSW_DOIP_PARAM_UNDEFINED
    \DESCRIPTION  The function parameter satisfy the parameter declaration on all places the function is called.
                  The parameter has an unknown value (e.g. read data from a received message).

INTERNAL_NOTE_SBSW_JUSTIFICATION_END */

/* INTERNAL_NOTE_DOIP_JUSTIFICATION_BEGIN

  \ID INTERNAL_NOTE_DOIP_CAST_HEADER_ALREADY_RECEIVED
    \DESCRIPTION  The cast to uint32 can be done because the generic DoIP header is already fully received. Due to this
                  the remaining message size fits into uint32 data range. Note: the largest DoIP message has a size of
                  8 byte generic DoIP header and uint32.MAX_VALUE of payload bytes.

INTERNAL_NOTE_DOIP_JUSTIFICATION_END */

/* COV_JUSTIFICATION_BEGIN

  \ID COV_DOIP_COMPATIBILITY
    \ACCEPT   TX
    \REASON   [COV_MSR_COMPATIBILITY]

  \ID COV_DOIP_SUPPORTED
    \ACCEPT   TX tf tx
    \REASON   The feature is supported in SafeBSW. A MSSV Plugin enforces this configuration.

  \ID COV_DOIP_DEFAULT_CASE
    \ACCEPT   XX
    \REASON   The default case catchs the DOIP_IPADDR_ASSIGN_NONE assignment (link local address with IPv6 Router
              Advertisment assignment). In an IPv4 only configuration this case is not covered.

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: DoIP.c
 *********************************************************************************************************************/
