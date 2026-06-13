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
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  TcpIp_IcmpV6.h
 *        \brief  Implementation of Internet Control Message Protocol for IPv6 (ICMPv6)
 *
 *      \details  This file is part of the TcpIp IPv6 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv6 submodule. >> TcpIp_IpV6.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/

/* configuration, interrupt handling and callback headers use different names
 * for the multiple inclusion protection define, shown in this example. The
 * appropriate names for these files can be taken from this list:
 *
 * IpV6_Icmp_Cfg.h:     IPV6_ICMP_CFG_H
 * IpV6_Icmp_Irq.h:     IPV6_ICMP_IRQ_H
 * IpV6_Icmp_Cbk.h:     IPV6_ICMP_CBK_H
 */
#if !defined(IPV6_ICMP_H)
#define IPV6_ICMP_H

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "TcpIp_IpV6.h"

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*  ICMPv6 error messages according to RFC 4443 */
#define IPV6_ICMP_MSG_TYPE_DEST_UNREACHABLE   1u
#define IPV6_ICMP_MSG_TYPE_PKT_TOO_BIG        2u
#define IPV6_ICMP_MSG_TYPE_TIME_EXCEEDED      3u
#define IPV6_ICMP_MSG_TYPE_PARAM_PROBLEM      4u

/* ICMPv6 informational messages according to RFC 4443 */
#define IPV6_ICMP_MSG_TYPE_ECHO_REQ         128u
#define IPV6_ICMP_MSG_TYPE_ECHO_REPLY       129u

/* ICMPv6 NDP messagges according to RFC 4861 */
#define IPV6_ICMP_MSG_TYPE_NDP_RS           133u
#define IPV6_ICMP_MSG_TYPE_NDP_RA           134u
#define IPV6_ICMP_MSG_TYPE_NDP_NS           135u
#define IPV6_ICMP_MSG_TYPE_NDP_NA           136u
#define IPV6_ICMP_MSG_TYPE_NDP_REDIR        137u

/* ICMPv6 IND message according to RFC 3122 */
#define IPV6_ICMP_MSG_TYPE_NDP_INV_NS       141u
#define IPV6_ICMP_MSG_TYPE_NDP_INV_NA       142u

/* ICMPv6 MLD messagges according to RFC 3810 */
#define IPV6_ICMP_MSG_TYPE_MLD_QUERY        130u
#define IPV6_ICMP_MSG_TYPE_MLD_REPORT       143u
#define IPV6_ICMP_MSG_TYPE_MLD_V1_REPORT    131u
#define IPV6_ICMP_MSG_TYPE_MLD_V1_DONE      132u

#define IPV6_ICMP_MSG_TIME_EXCEEDED_CODE_HOPS_EXCEEDED   0U /* 0 - Hop limit exceeded in transit     */
#define IPV6_ICMP_MSG_TIME_EXCEEDED_CODE_TIME_EXCEEDED   1U /* 1 - Fragment reassembly time exceeded */

#define IPV6_ICMP_MSG_PARAM_PROBLEM_CODE_ERR_HDR_FIELD   0U /* 0 - Erroneous header field encountered        */
#define IPV6_ICMP_MSG_PARAM_PROBLEM_CODE_UNKNOWN_NXT_HDR 1U /* 1 - Unrecognized Next Header type encountered */
#define IPV6_ICMP_MSG_PARAM_PROBLEM_CODE_UNKNOWN_OPTION  2U /* 2 - Unrecognized IPv6 option encountered      */

/* IPV6_ICMP_ERR_MSG_MAX_PAYLOAD_SIZE = IPV6_MINIMUM_MTU - IPV6_HDR_LEN - sizeof(IpV6_IcmpHeaderType) */
#define IPV6_ICMP_ERR_MSG_MAX_PAYLOAD_SIZE  (IPV6_MINIMUM_MTU - IPV6_HDR_LEN - 4U)

#define IPV6_NDP_RA_MIN_PAYLOAD_LEN         12U /* 16 - sizeof(IpV6_IcmpHeaderType) */
#define IPV6_NDP_NS_MIN_PAYLOAD_LEN         20U /* 24 - sizeof(IpV6_IcmpHeaderType) */
#define IPV6_NDP_NA_MIN_PAYLOAD_LEN         20U /* 24 - sizeof(IpV6_IcmpHeaderType) */
#define IPV6_NDP_REDIR_MIN_PAYLOAD_LEN      36U /* 40 - sizeof(IpV6_IcmpHeaderType) */
#define IPV6_NDP_IS_MIN_PAYLOAD_LEN         16U /* 24 - sizeof(IpV6_IcmpHeaderType) */
#define IPV6_NDP_IA_MIN_PAYLOAD_LEN         40U /* 48 - sizeof(IpV6_IcmpHeaderType) */


#define IPV6_ICMP_HEADER_OFS_TYPE            0U
#define IPV6_ICMP_HEADER_OFS_CODE            1U
#define IPV6_ICMP_HEADER_OFS_CHECKSUM        2U

#define IPV6_ICMP_HEADER_OFS_MULTIPART       4U
#define IPV6_ICMP_HEADER_LEN_MULTIPART       4U


/* icmp echo req/reply message offsets */
#define IPV6_ICMP_ECHO_MSG_OFF_IDNBO        0U
#define IPV6_ICMP_ECHO_MSG_OFF_SEQNUMNBO    2U

/* icmp packet too big message */
#define IPV6_ICMP_PKT_TOO_BIG_MSG_OFF_MTUNBO  0U

/* icmp multi packet ext header offsets */
#define IPV6_ICMP_MULTI_EXT_HDR_OFF_VERRESERVED   0U
#define IPV6_ICMP_MULTI_EXT_HDR_OFF_RESERVED      1u
#define IPV6_ICMP_MULTI_EXT_HDR_OFF_CHECKSUMNBO   2u

/* icmp parameter too big error message offset */
#define IPV6_ICMP_PARAM_PROB_MSG_OFF_POINTERNBO   0U

/* icmp time exceeded msg offsets */
#define IPV6_ICMP_TIME_EXCD_MSG_OFF_LENGTH        0U
#define IPV6_ICMP_TIME_EXCD_MSG_OFF_RESERVED      1u
#define IPV6_ICMP_TIME_EXCD_MSG_OFF_RESERVED16    2u

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FctLikeMacros */ /* MD_MSR_FctLikeMacro */
/* PRQA L:FctLikeMacros */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* example function pointer type definition */
typedef P2FUNC(void, IPV6_APPL_CODE, IpV6_Icmp_NotificationType) (void);

typedef struct
{
  uint8 Type;
  uint8 Code;
  uint16 ChecksumNbo;
} IpV6_IcmpHeaderType;

typedef struct
{
  uint16 IdentifierNbo;
  uint16 SequenceNumberNbo;
} IpV6_IcmpEchoRequestType;

typedef struct
{
  uint16 IdentifierNbo;
  uint16 SequenceNumberNbo;
} IpV6_IcmpEchoReplyType;

typedef struct
{
  uint32 PointerNbo; /* "Identifies the octet offset within the invoking packet where the error was detected." (stored in network byte order) */
} IpV6_IcmpParameterProblemErrMsgType;

typedef struct
{
  uint32 MtuNbo;
} IpV6_IcmpPacketTooBigMsgType;

typedef struct
{
  uint8  Length;
  uint8  Reserved;
  uint16 Reserved16;
} IpV6_IcmpTimeExceededMsgType;

typedef struct
{
  uint8  Length;
  uint8  Reserved;
  uint16 Reserved16;
} IpV6_IcmpDestUnreachableMsgType;

typedef struct
{
  uint8  VerReserved;
  uint8  Reserved;
  uint16 ChecksumNbo;
} IpV6_IcmpMultiPartExtHdr;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  IpV6_Icmp_Init()
 *********************************************************************************************************************/
/*! \brief         This function has to be called before any other function of this module.
 *  \details      -
 *  \pre           Interrupts must be disabled
 *  \synchronous   TRUE
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_Icmp_Init(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_Icmp_MainFunction()
 *********************************************************************************************************************/
/*! \brief         Main task function for Icmpv6
 *  \details       -
 *  \pre           Interrupts must be disabled
 *  \synchronous   TRUE
 *  \context       TASK
 *  \reentrant     TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_Icmp_MainFunction(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_Icmp_RxIndication()
 *********************************************************************************************************************/
/*! \brief         Receives an ICMPv6 packet.
 *  \details       -
 *  \param[in]     IpAddrIdx           Ip address index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     ethPayloadPtr       Payload of ethernet packet (starts with IPv6 header).
 *  \param[in]     ethPayloadLen       Length of ethernet payload in bytes.
 *  \param[in]     physAddrPtr         Physical address of the remote host.
 *  \param[in]     icmpHdrPos          Position of the ICMPv6 header inside of 'ethPayloadPtr'.
 *  \param[in]     checksumCalculated  Indicates if the ICMPv6 checksum was already verified by the hardware.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_Icmp_RxIndication(
  TcpIp_SizeOfLocalAddrV6Type   IpAddrIdx,
  IPV6_P2V(uint8)               ethPayloadPtr,
  uint16                        ethPayloadLen,
  IPV6_P2C(uint8)               physAddrPtr,
  uint16                        icmpHdrPos,
  boolean                       checksumCalculated);

/**********************************************************************************************************************
 *  IpV6_Icmp_Transmit()
 *********************************************************************************************************************/
/*! \brief         Transmission handling function for Icmpv6 packets
 *  \details       -
 *  \param[in]     IpAddrIdx            Ip address index
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     SocketIdx            IP Socket Index
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]     IpTxReqDescPtr       Tx buffer descriptor
 *  \param[in]     Type                 IcmpV6 packet type
 *  \param[in]     Code                 IcmpV6 code
 *  \param[out]    PayloadLen           Length of payload
 *  \return        E_OK                 Packet was queued for transmission
 *  \return        E_NOT_OK             Packet recieved from invalid source, error message wont be sent
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Icmp_Transmit(
  TcpIp_SizeOfSocketDynType                 SocketIdx,
  IPV6_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr,
  uint8                                     Type,
  uint8                                     Code,
  uint16                                    PayloadLen);

/**********************************************************************************************************************
 *  IpV6_Icmp_ProvideTxBuffer()
 *********************************************************************************************************************/
/*! \brief      This function is called by upper layer to get a transmit buffer.
 *              the function only succeeds if the destination specified via DstAddrPtr is reachable
 *  \details    -
 *  \param[in,out] IpAddrIdxPtr         IP address identifier
 *                                      if the identifier is an AutoSelect id, the selected source address
 *                                      id will be returned
 *  \param[in]     SocketIdx            socket index
 *  \param[out]    TxReqDescPtr         pointer to IP TX request descriptor (initialized by this function)
 *  \param[in]     DstAddrPtr           pointer to the address of the desired destination
 *  \param[out]    BufPtr               pointer to a variable which receives the pointer to the provided buffer
 *  \param[in,out] BufLenPtr            pointer to a variable which holds the minimum desired buffer size
 *                                      if the the function succeeds the available buffer size is stored here
 *  \return       BUFREQ_OK             buffer provided
 *  \return       BUFREQ_E_BUSY         currently no free buffer available, call again later
 *  \return       BUFREQ_E_NOT_OK       unknown error
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, TCPIP_CODE) IpV6_Icmp_ProvideTxBuffer(
    IPV6_P2V(TcpIp_LocalAddrV6IterType)       IpAddrIdxPtr,
    TcpIp_SizeOfSocketDynType                 SocketIdx,
    IPV6_P2V(TcpIp_IpTxRequestDescriptorType) TxReqDescPtr,
    IPV6_P2C(IpV6_AddrType)                   DstAddrPtr,
    IPV6_P2V(uint8*)                          BufPtr,
    IPV6_P2V(uint16)                          BufLenPtr);

/**********************************************************************************************************************
 *  IpV6_Icmp_TxRawMessage
 *********************************************************************************************************************/
/*! \brief         Send a raw ICMPv6 message of specified Type and Code.
 *  \details       -
 *  \param[in,out] IpAddrIdxPtr     IPv6 address identifier.
 *                                  If this is the ID of an AutoSelect or multicast address,
 *                                  the selected IP address id is returned.
 *  \param[in]     DestIpAddrPtr    Destination IPv6 address value.
 *  \param[in]     HopLimit         HopLimit value of the outgoing IPv6 packet.
 *  \param[in]     Type             Value of the Type field in the ICMPv6 message header.
 *  \param[in]     Code             Value of the Code field in the ICMPv6 message header.
 *  \param[in]     DataLength       Length of the message payload.
 *  \param[in]     DataPtr          Message payload.
 *  \return        BUFREQ_OK        Message was transmitted.
 *  \return        BUFREQ_E_BUSY    Message was not transmitted (link-layer address resolution pending or no ethernet buffer available).
 *  \return        BUFREQ_E_NOT_OK  Message was not transmitted (other error).
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        -
 *  \pre           -
 *  \trace         CREQ-115987
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, TCPIP_CODE) IpV6_Icmp_TxRawMessage(
    TCPIP_P2V(TcpIp_LocalAddrIterType)    IpAddrIdxPtr,
    TCPIP_P2C(IpV6_AddrType)              DestIpAddrPtr,
    uint8                                 HopLimit,
    uint8                                 Type,
    uint8                                 Code,
    uint16                                DataLength,
    TCPIP_P2C(uint8)                      DataPtr);

#if (TCPIP_SUPPORT_ICMPV6_MSG_PARAM_PROBLEM == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Icmp_VTxErrParameterProblem()
 *********************************************************************************************************************/
/*! \brief        Build and queue IcmpV6 parameter problem message for transmission
 *  \details      -
 *  \param[in]    IpAddrIdx            Ip address index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]    Code                 Icmpv6 code for time exceeded message
 *  \param[in]    IpV6PktDataPtr       IpV6 packet buffer with parameter error
 *  \param[in]    IpV6PktDataLen       IpV6 packet length
 *  \param[in]    IpV6PktDataOffs      IpV6 payload offset
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_Icmp_VTxErrParameterProblem(
  TcpIp_SizeOfLocalAddrV6Type                IpAddrIdx,
  uint8                                      Code,
  P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA)  IpV6PktDataPtr,
  uint16                                     IpV6PktDataLen,
  uint16                                     IpV6PktDataOffs);
#endif

#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Icmp_VTxTimeExceeded()
 *********************************************************************************************************************/
/*! \brief         Build and queue IcmpV6 time exceeded message for transmission
 *  \details       -
 *  \param[in]     IpAddrIdx            Ip address index
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     SrcAddrPtr           Source address from which erroneous packet was recieved
 *  \param[in]     Code                 Icmpv6 code for time exceeded message
 *  \param[in]     OrigPktDataPtr       Original packet data buffer
 *  \param[in]     OrigPktDataLenPtr    Original packet length
 *  \param[out]    MultiPartExtPtr      Multipart extension data buffer
 *  \param[out]    MultiPartExtLen      Multipart extension data length
 *  \return        E_OK                 Packet was queued for transmission
 *  \return        E_NOT_OK             Packet recieved from invalid source, error message wont be sent
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Icmp_VTxTimeExceeded(
  TcpIp_SizeOfLocalAddrV6Type IpAddrIdx,
  IPV6_P2C(IpV6_AddrType)     SrcAddrPtr,
  uint8                       Code,
  IPV6_P2V(uint8*)            OrigPktDataPtr,
  IPV6_P2V(uint16)            OrigPktDataLenPtr,
  IPV6_P2C(uint8)             MultiPartExtPtr,
  uint16                      MultiPartExtLen);
#endif


#if (TCPIP_SUPPORT_ICMPV6_ECHO_REPLY == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Icmp_Cbk_DestinationUnreachable()
 *********************************************************************************************************************/
/*! \brief        Callback for unreachable destination address
 *  \details      Cancel any pending messages to unreadcahble destination
 *  \param[in]    DstAddrPtr      Destination address which is unreachable
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_Icmp_Cbk_DestinationUnreachable(
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) DstAddrPtr);
#endif

/**********************************************************************************************************************
 *  IpV6_Icmp_VCalculateChecksumNbo()
 *********************************************************************************************************************/
/*! \brief        Calculate ICMPv6 checksum
 *  \details      Calculates the ICMPv6 checksum which is the 16-bit one's complement of the one's complement sum of the
 *                entire ICMPv6 message, starting with the ICMPv6 message type field, and prepended with a
 *                "pseudo-header" of IPv6 header fields, as specified in [IPv6, Section 8.1].
 *  \param[in]    SrcNetAddr    Pointer to the IPv6 source address
 *  \param[in]    DstNetAddr    Pointer to the IPv6 destination address
 *  \param[in]    DataPtr       Pointer to the entire ICMPv6 message beginning with the ICMPv6 header
 *  \param[in]    LenByte       Length the entire ICMPv6 message
 *  \return       Checksum      Calculated 16-bit checksum (in network byte order)
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(uint16, IPV6_CODE) IpV6_Icmp_VCalculateChecksumNbo(
  IPV6_P2C(IpV6_AddrType) SrcNetAddrPtr,
  IPV6_P2C(IpV6_AddrType) DstNetAddrPtr,
  IPV6_P2C(uint8)         DataPtr,
  uint16                  LenByte);

/**********************************************************************************************************************
 *  IpV6_Icmp_StoreChecksumInHeader
 *********************************************************************************************************************/
/*! \brief       Stores a calculated ICMPv6 checksum value at the correct position into the ICMPv6 header
 *  \details     -
 *  \param[in]   Checksum              Finalized checksum value.
 *  \param[in]   IcmpHdrPtr            Pointer the location of the ICMPv6 header.
 *  \context     TASK|ISR
 *  \pre         -
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, IPV6_CODE) IpV6_Icmp_StoreChecksumInHeader(
    uint16           Checksum,
    IPV6_P2V(uint8) IcmpHdrPtr);


#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* (TCPIP_SUPPORT_IPV6 == STD_ON) */
#endif  /* IPV6_ICMP_H */
/**********************************************************************************************************************
 *  END OF FILE: IpV6_Icmp.h
 *********************************************************************************************************************/
