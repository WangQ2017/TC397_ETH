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
 *         \file  TcpIp_IcmpV6.c
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


/* PRQA S 0828 EOF */ /* MD_MSR_1.1 */

#define TCPIP_ICMPV6_SOURCE

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIp.h"
#include "TcpIp_IpV6_Priv.h"
#include "TcpIp_IcmpV6.h"
#include "TcpIp_Ndp.h"

#include "IpBase_Sock.h"

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#if !defined (STATIC)
# define STATIC static
#endif

#define IPV6_ICMP_ENABLE_NDP                             STD_ON

/* "In order to achieve backwards compatibility, when the ICMP Extension Structure is
 *  appended to an ICMP message and that ICMP message contains an "original datagram"
 *  field, the "original datagram" field MUST contain at least 128 octets.
 *  If the original datagram did not contain 128 octets, the "original datagram"
 *  field MUST be zero padded to 128 octets.  (See Section 5.1 for rationale.)
 *  [RFC4884 4. ICMP Extensibility]
 */
#define IPV6_ICMP_MIN_ORIG_PKT_LEN                          128U


/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FctLikeMacros */ /* MD_MSR_FctLikeMacro */

/* PRQA L:FctLikeMacros */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if ((TCPIP_SUPPORT_ICMPV6_ERROR_MESSAGES == STD_ON) || (TCPIP_SUPPORT_ICMPV6_ECHO_REPLY == STD_ON))
typedef struct
{
  IpV6_AddrType    DstAddr;
  TcpIp_SizeOfLocalAddrV6Type IpAddrIdx;
  uint8            Type;
  uint8            Code;
  uint8            *PayloadPtr;
  uint16           PayloadLen;
  boolean          Pending;
} IpV6_Icmp_MsgInstanceType;
#endif


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define TCPIP_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

STATIC P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR) IpV6_Icmp_EthBufPtr;

#define TCPIP_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**/

#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (TCPIP_SUPPORT_ICMPV6_ERROR_MESSAGES == STD_ON)
STATIC VAR(IpV6_Icmp_MsgInstanceType, IPV6_VAR_NOINIT) IpV6_Icmp_PendingMsg;
#endif

#if (TCPIP_SUPPORT_ICMPV6_ECHO_REPLY == STD_ON)
STATIC VAR(IpV6_Icmp_MsgInstanceType, IPV6_VAR_NOINIT) IpV6_Icmp_PendingEchoReply;
#endif

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */



/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  IpV6_Icmp_VMultipartTimeExdMessage()
 *********************************************************************************************************************/
/*! \brief            Send an ICMP Time Exceeded Error for Multipart messages
 *  \details          The message will be copied into a buffer (including original packet data) and
 *                    sent later in main Function.
 *  \param[in]        MultiPartExtLen      Multipart extension heaedr length
 *  \param[in,out]    IcmpPayloadOfsPtr    Payload offset erraneous Icmpv6 packet
 *  \param[in]        MultiPartExtPtr      Multipart extension header buffer
 *  \param[out]       OrigPktDataPtr       Original Icmpv6 data buffer
 *  \param[out]       OrigPktDataLenPtr    Original Icmpv6 packet length
 *  \return           E_OK                 E_OK if message processed successfully
 *  \return           E_NOT_OK             E_NOT_OK if multipart message does not fit into ICMPv6 buffer
 *  \pre              -
 *  \context          TASK|ISR
 *  \reentrant        FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Icmp_VMultipartTimeExdMessage(
  uint16                                      MultiPartExtLen,
  IPV6_P2V(TcpIp_SizeOfIcmpV6TxMsgBufferType) IcmpPayloadOfsPtr,
  IPV6_P2C(uint8)                             MultiPartExtPtr,
  IPV6_P2V(uint8*)                            OrigPktDataPtr,
  IPV6_P2V(uint16)                            OrigPktDataLenPtr
);

/**********************************************************************************************************************
 *  IpV6_Icmp_VHandleMultipartPacket()
 *********************************************************************************************************************/
/*! \brief         Handle Multipart ICMP Packets for time Exceeded and Destination Unreachable Error
 *  \details       -
 *  \param[in]     IcmpPayloadPtr           Payload buffer of Icmpv6 packet
 *  \param[in]     IcmpPayloadLenPtr        Length of icmpv6 payload
 *  \param[out]    IcmpMultiPartDataOfsPtr  Icmpv6 multipart data buffer
 *  \param[out]    IcmpMultiPartDataLenPtr  Icmpv6 multipart data length
 *  \return        TRUE                     Message is corrupt and is not transferred to upper layer
 *  \return        FALSE                    Message will be handled by upper layer function
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(boolean, IPV6_CODE) IpV6_Icmp_VHandleMultipartPacket(
  IPV6_P2C(uint8)   IcmpPayloadPtr,
  IPV6_P2V(uint16)  IcmpPayloadLenPtr,
  IPV6_P2V(uint16)  IcmpMultiPartDataOfsPtr,
  IPV6_P2V(uint16)  IcmpMultiPartDataLenPtr);

#if (TCPIP_SUPPORT_ICMPV6_ECHO_REPLY == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Icmp_VRxEchoRequest()
 *********************************************************************************************************************/
/*! \brief        Handle Icmpv6 echo request
 *  \details      -
 *  \param[in]    IpAddrIdx    Ip address index
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]    SrcAddrPtr   Source addres of echo request
 *  \param[in]    DataPtr      Icmpv6 echo request data buffer
 *  \param[in]    LenByte      Length of Ichmpv6 echo request
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Icmp_VRxEchoRequest(
  TcpIp_SizeOfLocalAddrV6Type IpAddrIdx,
  IPV6_P2C(IpV6_AddrType)     SrcAddrPtr,
  IPV6_P2C(uint8)             DataPtr,
  uint16                      LenByte);
#endif

#if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Icmp_VRxErrPacketTooBig()
 *********************************************************************************************************************/
/*! \brief        Handle Icmpv6 packet too big error
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller
*                                CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    SrcAddrPtr     Source address of error packet
 *  \param[in]    DataPtr        Icmpv6 data buffer
 *  \param[in]    LenByte        Length of icmpv6 buffer
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Icmp_VRxErrPacketTooBig(
  TcpIp_SizeOfIpV6CtrlType    IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)     SrcAddrPtr,
  IPV6_P2C(uint8)             DataPtr,
  uint16                      LenByte);
#endif

/**********************************************************************************************************************
 *  IpV6_Icmp_VGetMultiPartData()
 *********************************************************************************************************************/
/*! \brief         Checks if an ICMPv6 message contains multi-part data according to [RFC4884].
 *  \details       This function may only be used for 'Destination Unreachable' and 'Time Exceeded' messages since
 *                 these are the only ICMPv6 messages which may contain multi-part data.
 *  \param[in]     icmpPayloadPtr       Payload of the ICMP message following the 'Type', 'Code' and 'Checksum' fields.
 *  \param[in]     icmpPayloadLen       Length of the payload in bytes.
 *  \param[out]    multiPartDataOfs     Offset of multi-part data inside 'icmpPayloadPtr'.
 *  \param[out]    multiPartDataLen     Length of multi-part data. (>0 if valid multi-part data was found.)
 *  \return        E_OK                 Message contains no or valid multi-part data an can be processed further.
 *  \return        E_NOT_OK             Message seems to contain invalid multi-part data and should be discarded.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Icmp_VGetMultiPartData(
  IPV6_P2C(uint8)  icmpPayloadPtr,
  uint16           icmpPayloadLen,
  IPV6_P2V(uint16) multiPartDataOfs,
  IPV6_P2V(uint16) multiPartDataLen);

#if ((TCPIP_SUPPORT_ICMPV6_ERROR_MESSAGES == STD_ON) || (TCPIP_SUPPORT_ICMPV6_ECHO_REPLY == STD_ON))
/**********************************************************************************************************************
 *  IpV6_Icmp_VTxPendingMessage()
 *********************************************************************************************************************/
/*! \brief        Transmit pending Icmpv6 messages
 *  \details      -
 *  \param[in]    PendingMsgPtr   Pending message data buffer
 *  \return       E_OK            Message was sent successfully
 *  \return       E_NOT_OK        Message not sent successfully
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Icmp_VTxPendingMessage(
  P2CONST(IpV6_Icmp_MsgInstanceType, AUTOMATIC, IPV6_APPL_DATA) PendingMsgPtr);
#endif

/**********************************************************************************************************************
 *  IpV6_Icmp_VHandlePacket()
 *********************************************************************************************************************/
/*! \brief         Handle a received ICMPv6 packet.
 *  \details       -
 *  \param[in]     LocalAddrV6Idx Ip address index
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     ethPayloadPtr  Payload of the whole ethernet packet. (including IPv6 and ICMPv6 headers)
 *  \param[in]     ethPayloadLen  Length of ethernet payload in bytes.
 *  \param[in]     physAddrPtr    Physical address of sender
 *  \param[in]     icmpHdrPos     Position of ICMPv6 header inside of 'ethPayloadPtr'
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) IpV6_Icmp_VHandlePacket(
  TcpIp_SizeOfLocalAddrV6Type   LocalAddrV6Idx,
  IPV6_P2V(uint8)               ethPayloadPtr,
  uint16                        ethPayloadLen,
  IPV6_P2C(uint8)               physAddrPtr,
  uint16                        icmpHdrPos);

/**********************************************************************************************************************
 *  IpV6_Icmp_VProcessMultiPartData()
 *********************************************************************************************************************/
/*! \brief         Process Icmpv6 messages with multipart data
 *  \details       -
 *  \param[in]     icmpPayloadPtr     Icmpv6 payload buffer
 *  \param[in]     icmpPayloadLen     Icmpv6 payload length
 *  \param[out]    multiPartDataOfs   Multipart data offset
 *  \param[out]    multiPartDataLen   Multipart data length
 *  \return        E_OK
 *  \return        E_NOT_OK
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Icmp_VProcessMultiPartData(
  IPV6_P2C(uint8)  icmpPayloadPtr,
  uint16           icmpPayloadLen,
  IPV6_P2V(uint16) multiPartDataOfs,
  IPV6_P2V(uint16) multiPartDataLen);

#if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Icmp_VUpdatePathMtu()
 *********************************************************************************************************************/
/*! \brief        Updat path Mtu in destination cache
 *  \details      -
 *  \param[in]    IpCtrlIdx       Index of IP controller
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DstAddrPtr      Destination for which path Mtu is changed
 *  \param[in]    MtuNbo          Updated Mtu value
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV6_CODE) IpV6_Icmp_VUpdatePathMtu(
  TcpIp_SizeOfIpV6CtrlType    IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)     DstAddrPtr,
  uint32                      MtuNbo);
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  IpV6_Icmp_VCalculateChecksumNbo()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(uint16, IPV6_CODE) IpV6_Icmp_VCalculateChecksumNbo(
  IPV6_P2C(IpV6_AddrType) SrcNetAddrPtr,
  IPV6_P2C(IpV6_AddrType) DstNetAddrPtr,
  IPV6_P2C(uint8)         DataPtr,
  uint16                  LenByte)
{
  uint32 checksum;
  uint32 PseudoHdrInfo;

  TCPIP_ASSERT(NULL_PTR != SrcNetAddrPtr);
  TCPIP_ASSERT(NULL_PTR != DstNetAddrPtr);
  TCPIP_ASSERT(NULL_PTR != DataPtr);

  /*         IPv6 Pseudo Header
   * [RFC2460 8.1 Upper-Layer Checksums]
   *  +-------+-------+-------+-------+
   *  +                               + \
   *  +         Source Address        +  } 16 bytes (128bit)
   *  +                               + /
   *  +-------+-------+-------+-------+
   *  +                               + \
   *  +      Destination Address      +  } 16 bytes (128bit)
   *  +                               + /
   *  +-------+-------+-------+-------+
   *  |   Upper-Layer Packet Length   |  }  4 bytes  (32bit)
   *  +-------+-------+-------+-------+
   *  |          zero         | NxtHdr|  }  4 bytes  (32bit)
   *  +-------+-------+-------+-------+
   *
   *            ICMPv6 Header
   *  +-------+-------+-------+-------+
   *  |  Type |  Code | Checksum == 0 |  }  4 bytes  (32bit)
   *  +-------+-------+-------+-------+
   */

  /* #10 Calculate checksum of ICMPv6 pseudo header */
  checksum = IpBase_TcpIpChecksumAdd(&SrcNetAddrPtr->addr[0], IPV6_ADDRESS_LEN_BYTE,        0, FALSE);
  checksum = IpBase_TcpIpChecksumAdd(&DstNetAddrPtr->addr[0], IPV6_ADDRESS_LEN_BYTE, checksum, FALSE);

  /* #20 Add Upper-Layer Packet Length and Next Header values */
  PseudoHdrInfo = (uint32) TCPIP_HTONS(LenByte) + (uint32) TCPIP_HTONS(IPV6_HDR_ID_ICMP);

  /* #30 Add Type and Code of ICMPv6 Header checksum */
  PseudoHdrInfo += TCPIP_HTONS(TCPIP_GET_UINT16(DataPtr, IPV6_ICMP_HEADER_OFS_TYPE));
  /* PRQA S 0310 1 */ /* MD_TCPIP_Rule11.3_0310_CastToUInt8 */
  checksum = IpBase_TcpIpChecksumAdd((IPV6_P2C(uint8))&PseudoHdrInfo, sizeof(PseudoHdrInfo), checksum, FALSE);

  /* #40 Add ICMPv6 payload checksum */
  checksum = IpBase_TcpIpChecksumAdd(&DataPtr[sizeof(IpV6_IcmpHeaderType)],
                   (LenByte - sizeof(IpV6_IcmpHeaderType)), checksum, TRUE);

  return (uint16)checksum;
} /* End of IpV6_Icmp_VCalculateChecksumNbo() */


#if (TCPIP_SUPPORT_ICMPV6_ECHO_REPLY == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Icmp_VRxEchoRequest()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Icmp_VRxEchoRequest(
  TcpIp_SizeOfLocalAddrV6Type IpAddrIdx,
  IPV6_P2C(IpV6_AddrType)     SrcAddrPtr,
  IPV6_P2C(uint8)             DataPtr,
  uint16                      LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16                               dataLen = LenByte;
  TcpIp_SizeOfIcmpV6EchoDataBufferType icmpEchoDataBufIdx;

  TCPIP_ASSERT(IpAddrIdx < TcpIp_GetSizeOfLocalAddrV6());
  TCPIP_ASSERT(NULL_PTR != DataPtr);

  /* The source address of an Echo Reply sent in response to a unicast
     Echo Request message MUST be the same as the destination address of that Echo Request message.
     [RFC4443 4.2.] */

  /* ----- Implementation ----------------------------------------------- */
  if (dataLen >= (uint16) sizeof(IpV6_IcmpEchoRequestType))
  {
    P2VAR(uint8, AUTOMATIC, IPV6_VAR_NOINIT) IcmpEchoReplyPtr = TcpIp_GetAddrIcmpV6EchoDataBuffer(0);
    IpV6_Icmp_PendingEchoReply.IpAddrIdx = IpAddrIdx;

    /* send echo reply to the sender of the request */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(IpV6_Icmp_PendingEchoReply.DstAddr, *SrcAddrPtr);

    /* #10 Copy message fields from request to reply buffer */
    TCPIP_PUT_UINT16(IcmpEchoReplyPtr, IPV6_ICMP_ECHO_MSG_OFF_IDNBO, (TCPIP_GET_UINT16(DataPtr, IPV6_ICMP_ECHO_MSG_OFF_IDNBO)));

    TCPIP_PUT_UINT16(IcmpEchoReplyPtr, IPV6_ICMP_ECHO_MSG_OFF_SEQNUMNBO, (TCPIP_GET_UINT16(DataPtr, IPV6_ICMP_ECHO_MSG_OFF_SEQNUMNBO)));

    IpV6_Icmp_PendingEchoReply.Type = IPV6_ICMP_MSG_TYPE_ECHO_REPLY;
    IpV6_Icmp_PendingEchoReply.Code = 0;

    if (dataLen > TcpIp_GetSizeOfIcmpV6EchoDataBuffer())
    {
      /* truncate echo request data to configured maximum size */
      dataLen = TcpIp_GetSizeOfIcmpV6EchoDataBuffer();
    }

    icmpEchoDataBufIdx = (uint16) sizeof(IpV6_IcmpEchoReplyType);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpV6_MemCpy(TcpIp_GetAddrIcmpV6EchoDataBuffer(icmpEchoDataBufIdx),
      &DataPtr[sizeof(IpV6_IcmpEchoRequestType)], (dataLen - sizeof(IpV6_IcmpEchoRequestType)));

    IpV6_Icmp_PendingEchoReply.PayloadPtr = TcpIp_GetAddrIcmpV6EchoDataBuffer(0);
    IpV6_Icmp_PendingEchoReply.PayloadLen = dataLen;
    IpV6_Icmp_PendingEchoReply.Pending    = TRUE;
  }
  else
  {
    /* Silently discard Echo Request with incomplete header */
  }
} /* End of IpV6_Icmp_VRxEchoRequest() */
#endif

#if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Icmp_VUpdatePathMtu()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Icmp_VUpdatePathMtu(
  TcpIp_SizeOfIpV6CtrlType    IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)     DstAddrPtr,
  uint32                      MtuNbo)
{
  TcpIp_SizeOfIpV6DestinationCacheEntryType dcEntryIdx;

  /* #10 Search destination cache for entry with requested destination */
  if (E_OK == IpV6_Ndp_VDCLookup(IpCtrlIdx, DstAddrPtr, &dcEntryIdx))
  {
    /* destination cache entry found */
    TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->MtuReported = (uint16)(TCPIP_NTOHL(MtuNbo));

    /* #20 Check that the reported Mtu is valid (greater than the Minimum Mtu) */
    if (   (IPV6_MINIMUM_MTU < TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->Mtu)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->MtuReported < TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->Mtu))
    {
      if (IPV6_MINIMUM_MTU <= TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->MtuReported)
      {
        TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->Mtu =
          TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->MtuReported;
      }
      else
      {
        TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->Mtu = IPV6_MINIMUM_MTU;
      }

      IPV6_SET_LIFETIME_S(TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->MtuTimeout,
        TcpIp_GetPathMtuTimeoutOfIpV6Ctrl(IpCtrlIdx), (IPV6_P2V(IpV6_TimeType))NULL_PTR);

      {
        uint16 UpperLayerPayloadLen = (uint16)(TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->Mtu - IPV6_HDR_LEN);
        TcpIp_SockAddrBaseType sockAddr; /* PRQA S 0759 */ /* MD_MSR_Union */

        if (TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->MtuReported < IPV6_MINIMUM_MTU)
        {
          /* See [RFC2460 5. Packet Size Issues] */
          UpperLayerPayloadLen -= IPV6_FRAGMENT_EXT_HDR_LEN;
        }

        sockAddr.SockAddrIn6.sin6_family = IPBASE_AF_INET6;
        sockAddr.SockAddrIn6.sin6_port   = 0;
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_ADDR_COPY(sockAddr.SockAddrIn6.sin6_addr.addr[0], TcpIp_GetAddrIpV6DestinationCacheEntry(dcEntryIdx)->DestinationAddress);

        /* #30 Invoke upper layer callback function to update path Mtu */
        TcpIp_Cbk_VPathMtuChg(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx), &sockAddr, UpperLayerPayloadLen);

# if (TCPIP_ICMPV6MAXPAYLOADLENCHGCBK == STD_ON)
        {
          TcpIp_IcmpV6MaxPayloadLenChgCbkIterType maxPayloadLenChgCbkIdx;

          for (maxPayloadLenChgCbkIdx = 0;
               maxPayloadLenChgCbkIdx < TcpIp_GetSizeOfIcmpV6MaxPayloadLenChgCbk();
               maxPayloadLenChgCbkIdx++)
          {
            TcpIp_GetIcmpV6MaxPayloadLenChgCbk(maxPayloadLenChgCbkIdx)(TcpIp_GetEthIfCtrlIdxOfIpV6Ctrl(IpCtrlIdx),
              &sockAddr.TcpIpSockAddr, UpperLayerPayloadLen);
          }
        }
# endif
      }
    }
  }
} /* IpV6_Icmp_VUpdatePathMtu() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV6_Icmp_VRxErrPacketTooBig()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, IPV6_CODE) IpV6_Icmp_VRxErrPacketTooBig(
  TcpIp_SizeOfIpV6CtrlType    IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)     SrcAddrPtr,
  IPV6_P2C(uint8)             DataPtr,
  uint16                      LenByte)
{
  Std_ReturnType result;

  TCPIP_ASSERT(NULL_PTR != DataPtr);

  IPV6_UNUSED_PARAMETER(SrcAddrPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  /* #10 Validate the error packet header */
  if (TcpIp_IsEnablePathMtuOfIpV6Ctrl(IpCtrlIdx) == FALSE)
  {
    result = E_NOT_OK;
  }
  else if ((LenByte < sizeof(IpV6_IcmpPacketTooBigMsgType)) || (IPV6_ICMP_ERR_MSG_MAX_PAYLOAD_SIZE < LenByte))
  {
    /* invalid message length */
    result = E_NOT_OK; /* silently ignore invalid packet */
  }
  else
  {
    /* packet is valid */
    result = E_OK;
  }

  /* #20 Uodate the path Mtu from the error message */
  if(result == E_OK)
  {
    IpV6_AddrType destAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
    uint32 mtuNbo = TCPIP_GET_UINT32_RAW(DataPtr, IPV6_ICMP_PKT_TOO_BIG_MSG_OFF_MTUNBO);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(destAddr, DataPtr[sizeof(IpV6_IcmpPacketTooBigMsgType) + IPV6_HDR_OFF_DSTADDR]);

    /* MTU available for upper layer = MTU - 40 (IPv6 header) - x (IPv6 extension headers) */
    IpV6_Icmp_VUpdatePathMtu(IpCtrlIdx, &destAddr, mtuNbo);
  }
} /* End of IpV6_Icmp_VRxErrPacketTooBig() */
#endif

/**********************************************************************************************************************
 *  IpV6_Icmp_VProcessMultiPartData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Icmp_VProcessMultiPartData(
  IPV6_P2C(uint8)  icmpPayloadPtr,
  uint16           icmpPayloadLen,
  IPV6_P2V(uint16) multiPartDataOfs,
  IPV6_P2V(uint16) multiPartDataLen)
{
  Std_ReturnType retVal = E_NOT_OK;
  /* process multi-part message */
  uint16 origPktLen = ((uint16) icmpPayloadPtr[0] * 8u); /* length is number of 64bit words */
  uint16 origPktEndOfs = IPV6_ICMP_HEADER_LEN_MULTIPART + origPktLen;

  /* #10 Check if original payload length is bigger than minimum payload length */
  /* original packet payload length must be at least 128 byte (zero-padded if necessary) */
  if ((origPktLen >= IPV6_ICMP_MIN_ORIG_PKT_LEN) &&
      (origPktEndOfs <= icmpPayloadLen))
  {
    /* #20 Locate multi-part extension structure */
    /* original packet payload length exceeds ICMP payload length. */
    uint16 multiPartExtLen = (icmpPayloadLen - origPktEndOfs);

    /* check for ICMP Extension Structure [RFC4884 7.] */
    if (multiPartExtLen >= (uint16) sizeof(IpV6_IcmpMultiPartExtHdr))
    {
      /* #30 Verify checksum of multi-part data */
      IpV6_IcmpMultiPartExtHdr multiPartExtHdr;
      multiPartExtHdr.VerReserved =
        TCPIP_GET_UINT8(icmpPayloadPtr, origPktEndOfs /* + IPV6_ICMP_MULTI_EXT_HDR_OFF_VERRESERVED */);

      multiPartExtHdr.ChecksumNbo =
        TCPIP_GET_UINT16_RAW(icmpPayloadPtr, origPktEndOfs + IPV6_ICMP_MULTI_EXT_HDR_OFF_CHECKSUMNBO);

      if (((multiPartExtHdr.VerReserved >> 4) == 2u) && (multiPartExtHdr.ChecksumNbo != 0u))
      {
        uint16 multiPartDataOfsTmp = (uint16)(origPktEndOfs   + sizeof(IpV6_IcmpMultiPartExtHdr));
        uint16 multiPartDataLenTmp = (uint16)(multiPartExtLen - sizeof(IpV6_IcmpMultiPartExtHdr));

        /* validate checksum */
        uint16 calculatedChecksumNbo = (uint16)IpBase_TcpIpChecksumAdd(&icmpPayloadPtr[multiPartDataOfsTmp],
                    multiPartDataLenTmp, (((uint32)multiPartExtHdr.VerReserved) << IPV6_BITS_IN_BYTE), TRUE);

        if (calculatedChecksumNbo == 0u)
        {
          calculatedChecksumNbo = 0xFFFFU; /* one's complement checksum has two values for zero */
        }

        /* #40 Return offset and length of multi-part data, if checksum is valid */
        if (multiPartExtHdr.ChecksumNbo == calculatedChecksumNbo)
        {
          *multiPartDataOfs = multiPartDataOfsTmp;
          *multiPartDataLen = multiPartDataLenTmp;
          retVal = E_OK;
        }
        /* An all-zero value means that no checksum was transmitted.
         * [RFC4884 7. The ICMP Extension Structure]
         */
      }
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  IpV6_Icmp_VGetMultiPartData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, IPV6_CODE) IpV6_Icmp_VGetMultiPartData(
  IPV6_P2C(uint8)  icmpPayloadPtr,
  uint16           icmpPayloadLen,
  IPV6_P2V(uint16) multiPartDataOfs,
  IPV6_P2V(uint16) multiPartDataLen)
{
  Std_ReturnType retVal = E_NOT_OK;

  TCPIP_ASSERT(icmpPayloadPtr != NULL_PTR);

  /* #10 Check minimum and maximum ICMP message length */
  if ((icmpPayloadLen >= IPV6_ICMP_HEADER_LEN_MULTIPART) && (icmpPayloadLen <= IPV6_ICMP_ERR_MSG_MAX_PAYLOAD_SIZE))
  {
    /* The Destination Unreachable/Time Exceeded message defined in [RFC4443 3.1./3.3] starts with 4 unused bytes.
     * [RFC4884 4.4.] maps a length field on the first byte and holds the
     * length of the original packet payload in 64-bit words.
     */

    uint8 icmpPayloadDataWords = icmpPayloadPtr[0];

    /* #20 Return if optional length field does not indicate presence of multi-part data */
    if (icmpPayloadDataWords == 0u)
    {
      /* [RFC4884 5.4. Compliant Application Receives ICMP Message with No Extensions] */
      *multiPartDataOfs = 0;
      *multiPartDataLen = 0;
      retVal = E_OK;
    }
    else
    {
      /* #30 Invoke routine to process multipart message */
      retVal = IpV6_Icmp_VProcessMultiPartData(icmpPayloadPtr, icmpPayloadLen, multiPartDataOfs, multiPartDataLen);
    }
  }

  return retVal;
} /* End of IpV6_Icmp_VGetMultiPartData() */




#if ((TCPIP_SUPPORT_ICMPV6_ERROR_MESSAGES == STD_ON) || (TCPIP_SUPPORT_ICMPV6_ECHO_REPLY == STD_ON))
/**********************************************************************************************************************
 *  IpV6_Icmp_VTxPendingMessage()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Icmp_VTxPendingMessage(
  P2CONST(IpV6_Icmp_MsgInstanceType, AUTOMATIC, IPV6_APPL_DATA) PendingMsgPtr)
{
  Std_ReturnType result;
  TcpIp_IpTxRequestDescriptorType IpTxReqDesc;
  IPV6_P2V(uint8)                 IcmpBufPtr;
  uint16                          IcmpBufLen;
  TcpIp_LocalAddrIterType         ipAddrIdx;
  IcmpBufLen = PendingMsgPtr->PayloadLen;

  ipAddrIdx = PendingMsgPtr->IpAddrIdx;

  /* #10 Request transmission buffer */
  if (BUFREQ_OK !=
    IpV6_Icmp_ProvideTxBuffer(&ipAddrIdx, TcpIp_GetIpV6SocketDynIcmpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX),
    &IpTxReqDesc, &PendingMsgPtr->DstAddr, &IcmpBufPtr, &IcmpBufLen))
  {
    result = E_NOT_OK;
  }
  else
  {
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpV6_MemCpy(&IcmpBufPtr[0], &PendingMsgPtr->PayloadPtr[0], PendingMsgPtr->PayloadLen);
    /* #20 Invoke transmit function */
    result = IpV6_Icmp_Transmit(TcpIp_GetIpV6SocketDynIcmpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX), &IpTxReqDesc,
      PendingMsgPtr->Type, PendingMsgPtr->Code, PendingMsgPtr->PayloadLen);
  }
  return result;
} /* End of IpV6_Icmp_VTxPendingMessage() */
#endif


#if (TCPIP_SUPPORT_ICMPV6_MSG_PARAM_PROBLEM == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Icmp_VTxErrParameterProblem()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Icmp_VTxErrParameterProblem(
  TcpIp_SizeOfLocalAddrV6Type                IpAddrIdx,
  uint8                                      Code,
  P2CONST(uint8, AUTOMATIC, IPV6_APPL_DATA)  IpV6PktDataPtr,
  uint16                                     IpV6PktDataLen,
  uint16                                     IpV6PktDataOffs)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16                                    pktDataLen = IpV6PktDataLen;
  uint16                                    MaxOrgPktLen;
  TcpIp_SizeOfIcmpV6TxMsgBufferType         icmpTxMsgBufIdx;
  P2VAR(uint8, AUTOMATIC, IPV6_VAR_NOINIT)  MsgPtr;
  IpV6_AddrType                             destAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
  IpV6_AddrType                             srcAddr; /* PRQA S 0759 */ /* MD_MSR_Union */

  /* #10 Validate the error message parameters */
  /* Total length of ICMP message MUST NOT exceed the minimum reassembly buffer size. */
  if (TcpIp_GetSizeOfIcmpV6TxMsgBuffer() > IPV6_ICMP_ERR_MSG_MAX_PAYLOAD_SIZE)  /*lint !e506 */ /* PRQA S 2991, 2995 */ /* MD_TCPIP_Rule14.3_2991_2995 */
  {
    MaxOrgPktLen = IPV6_ICMP_ERR_MSG_MAX_PAYLOAD_SIZE;
  }
  else
  {
    /* Size of message is limited by IcmpTxMsgBufferSize */
    MaxOrgPktLen = TcpIp_GetSizeOfIcmpV6TxMsgBuffer();
  }

  MaxOrgPktLen -= (uint16) sizeof(IpV6_IcmpParameterProblemErrMsgType);

  if (pktDataLen > MaxOrgPktLen)
  {
    pktDataLen = MaxOrgPktLen;
  }

  MsgPtr = TcpIp_GetAddrIcmpV6TxMsgBuffer(0);

  TCPIP_PUT_UINT32(MsgPtr, IPV6_ICMP_PARAM_PROB_MSG_OFF_POINTERNBO, IpV6PktDataOffs);

  icmpTxMsgBufIdx = (uint16) sizeof(IpV6_IcmpParameterProblemErrMsgType);

  /* PRQA S 0315 3 */ /* MD_MSR_VStdLibCopy */
  IpV6_MemCpy(TcpIp_GetAddrIcmpV6TxMsgBuffer(icmpTxMsgBufIdx), IpV6PktDataPtr, pktDataLen);
  IPV6_ADDR_COPY(destAddr, IpV6PktDataPtr[IPV6_HDR_OFF_DSTADDR]);
  IPV6_ADDR_COPY(srcAddr, IpV6PktDataPtr[IPV6_HDR_OFF_SRCADDR]);

  /* #20 Check if the destination or source of the packet is a multicast address */
  if (   (IPV6_ADDR_IS_MULTICAST(destAddr) && (Code != 2u)) /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (IPV6_ADDR_IS_MULTICAST(srcAddr))
      || (IPV6_ADDR_IS_UNSPECIFIED(srcAddr)))
  {
    /* [RFC4443 2.4. Message Processing Rules]
       "(e) An ICMPv6 error message MUST NOT be originated as a result of
           receiving the following:"
       "(e.3) A packet destined to an IPv6 multicast address.  (There are
              two exceptions to this rule: (1) the Packet Too Big Message
              (Section 3.2) to allow Path MTU discovery to work for IPv6
              multicast, and (2) the Parameter Problem Message, Code 2
              (Section 3.4) reporting an unrecognized IPv6 option (see
              Section 4.2 of [IPv6]) that has the Option Type highest-
              order two bits set to 10).
              [...]
        (e.6) A packet whose source address does not uniquely identify a
              single node -- e.g., the IPv6 Unspecified Address, an IPv6
              multicast address, or an address known by the ICMP message
              originator to be an IPv6 anycast address." */

    /* Abort sending ICMP error message */
  }
  else
  {
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(IpV6_Icmp_PendingMsg.DstAddr, srcAddr);

    /* If the original packet has been sent to a multicast address, IpAddrIdx will be an AutoSelect_Multicast id.
     * This id can be used for the response as well since the IpV6 will automatically select a suitable source address.
     */
    /* #30 Queue the Icmpv6 packet for transmission */
    IpV6_Icmp_PendingMsg.IpAddrIdx   = IpAddrIdx;
    IpV6_Icmp_PendingMsg.Type        = IPV6_ICMP_MSG_TYPE_PARAM_PROBLEM;
    IpV6_Icmp_PendingMsg.Code        = Code;
    IpV6_Icmp_PendingMsg.PayloadPtr  = TcpIp_GetAddrIcmpV6TxMsgBuffer(0);
    IpV6_Icmp_PendingMsg.PayloadLen  = (uint16) sizeof(IpV6_IcmpParameterProblemErrMsgType) + pktDataLen;
    IpV6_Icmp_PendingMsg.Pending     = TRUE;
  }
} /* End of IpV6_Icmp_VTxErrParameterProblem() */
#endif

/**********************************************************************************************************************
 *  IpV6_Icmp_VMultipartTimeExdMessage()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, IPV6_CODE) IpV6_Icmp_VMultipartTimeExdMessage(
  uint16                                      MultiPartExtLen,
  IPV6_P2V(TcpIp_SizeOfIcmpV6TxMsgBufferType) IcmpPayloadOfsPtr,
  IPV6_P2C(uint8)                             MultiPartExtPtr,
  IPV6_P2V(uint8*)                            OrigPktDataPtr,
  IPV6_P2V(uint16)                            OrigPktDataLenPtr
)
{
  uint16                                 maxOrigPktLen;
  uint8_least                            paddingByteCount = 0;
  uint8_least                            index;
  IPV6_P2V(uint8)                        TimeExceededMsgHdrPtr = TcpIp_GetAddrIcmpV6TxMsgBuffer(0);
  Std_ReturnType                         Result = E_OK;
  uint16                                 OrigPktDataLen = (*OrigPktDataLenPtr);
  /* "[...] the total length of the ICMP message, including extensions,
    *  MUST NOT exceed the minimum reassembly buffer size."
    *  [RFC4884 7. The ICMP Extension Structure]
    */
  /* #10 Validate the error message parameters */
  if (TcpIp_GetSizeOfIcmpV6TxMsgBuffer() > IPV6_ICMP_ERR_MSG_MAX_PAYLOAD_SIZE)  /*lint !e506 */ /* PRQA S 2991, 2995 */ /* MD_TCPIP_Rule14.3_2991_2995 */
  {
    maxOrigPktLen = IPV6_ICMP_ERR_MSG_MAX_PAYLOAD_SIZE;
  }
  else
  {
    /* Size of message is limited by IcmpTxMsgBufferSize */
    maxOrigPktLen = TcpIp_GetSizeOfIcmpV6TxMsgBuffer();
  }

  maxOrigPktLen -= (uint16) sizeof(IpV6_IcmpTimeExceededMsgType);

  /* #20 Check if original packet and multi-part data fit into ICMP message buffer,
   * in multi-part messages the original packet must be at least 128 bytes (zero-padded if necessary)
   */
  if (maxOrigPktLen < (IPV6_ICMP_MIN_ORIG_PKT_LEN + sizeof(IpV6_IcmpMultiPartExtHdr) + MultiPartExtLen))
  {
    /* too much payload */
    Result = E_NOT_OK;
  }
  else
  {

    TcpIp_SizeOfIcmpV6TxMsgBufferType MultiPartExtHdrOfs;
    IPV6_P2V(uint8) MultiPartExtHdrPtr;

    /* keep space for multi-part data after the original packet */
    maxOrigPktLen -= ((uint16) sizeof(IpV6_IcmpMultiPartExtHdr) + MultiPartExtLen);

    /* maximum original packet length must be a multiple of 8 byte (64 bit) */
    maxOrigPktLen -= (maxOrigPktLen % 8u);

    if (OrigPktDataLen > maxOrigPktLen)
    {
      /* truncate original packet */
      OrigPktDataLen = maxOrigPktLen;
    }

    /* according to [RFC4884 4.5. ICMPv6 Time Exceeded] we have to pad the original packet to a multiple of 8 octets. */
    if (OrigPktDataLen < IPV6_ICMP_MIN_ORIG_PKT_LEN)
    {
      paddingByteCount = (uint8_least)IPV6_ICMP_MIN_ORIG_PKT_LEN - (uint8_least)OrigPktDataLen;
    }
    else if (0u < (OrigPktDataLen % 8u))
    {
      paddingByteCount = (uint8_least)8 - (uint8_least)(OrigPktDataLen % 8u);
    }
    else
    {
      /* leave paddingByteCount zero */
    }

    /* write length of original packet data to first */
    TimeExceededMsgHdrPtr[IPV6_ICMP_TIME_EXCD_MSG_OFF_LENGTH] = (uint8)((OrigPktDataLen + paddingByteCount) / 8u);

    /* return buffer and length for original packet payload. Caller will copy data directly into the buffer */
    (*OrigPktDataPtr)    = TcpIp_GetAddrIcmpV6TxMsgBuffer((*IcmpPayloadOfsPtr));
    (*OrigPktDataLenPtr) = OrigPktDataLen;

    (*IcmpPayloadOfsPtr) += OrigPktDataLen;


    /* add padding bytes to original packet if necessary */
    for(index = 0; index < paddingByteCount; index++)
    {
      TcpIp_SetIcmpV6TxMsgBuffer((*IcmpPayloadOfsPtr), 0);
      (*IcmpPayloadOfsPtr)++;
    }

    MultiPartExtHdrOfs = (*IcmpPayloadOfsPtr);

    MultiPartExtHdrPtr = TcpIp_GetAddrIcmpV6TxMsgBuffer(MultiPartExtHdrOfs);

    MultiPartExtHdrPtr[IPV6_ICMP_MULTI_EXT_HDR_OFF_VERRESERVED] = 0x20; /* MSB nibble = 2, indicates version 2 */
    MultiPartExtHdrPtr[IPV6_ICMP_MULTI_EXT_HDR_OFF_RESERVED] = 0U;

    /* Set Checksum to zero for calculation. */
    TCPIP_PUT_UINT16(MultiPartExtHdrPtr, IPV6_ICMP_MULTI_EXT_HDR_OFF_CHECKSUMNBO, 0U);

    (*IcmpPayloadOfsPtr) += (uint16) sizeof(IpV6_IcmpMultiPartExtHdr);

    /* copy multi-part data into ICMP TX buffer */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpV6_MemCpy(TcpIp_GetAddrIcmpV6TxMsgBuffer((*IcmpPayloadOfsPtr)), MultiPartExtPtr, MultiPartExtLen);

    (*IcmpPayloadOfsPtr) += MultiPartExtLen;

    /* calculate checksum over multi-part data */
    TCPIP_PUT_UINT16_RAW(MultiPartExtHdrPtr, IPV6_ICMP_MULTI_EXT_HDR_OFF_CHECKSUMNBO,
      (uint16)IpBase_TcpIpChecksumAdd(TcpIp_GetAddrIcmpV6TxMsgBuffer(MultiPartExtHdrOfs),
      ((uint32)sizeof(IpV6_IcmpMultiPartExtHdr) + MultiPartExtLen), 0, TRUE));

    if (0u == TCPIP_GET_UINT16(MultiPartExtHdrPtr, IPV6_ICMP_MULTI_EXT_HDR_OFF_CHECKSUMNBO))
    {
      /* one's complement checksum has two values for zero.
        * An all-zero value would mean that no checksum was transmitted.
        * So we use 0xFFFF to indicate a valid zero checksum.
        * [RFC4884 7. The ICMP Extension Structure]
        */
      TCPIP_PUT_UINT16(MultiPartExtHdrPtr, IPV6_ICMP_MULTI_EXT_HDR_OFF_CHECKSUMNBO, 0xFFFFU);
    }
  }
  return Result;
}

#if (TCPIP_SUPPORT_IPV6_RX_FRAGMENTATION == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Icmp_VTxTimeExceeded()
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
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Icmp_VTxTimeExceeded(
  TcpIp_SizeOfLocalAddrV6Type  IpAddrIdx,
  IPV6_P2C(IpV6_AddrType)      SrcAddrPtr,
  uint8                        Code,
  IPV6_P2V(uint8*)             OrigPktDataPtr,
  IPV6_P2V(uint16)             OrigPktDataLenPtr,
  IPV6_P2C(uint8)              MultiPartExtPtr,
  uint16                       MultiPartExtLen)
{
  Std_ReturnType                         retVal = E_OK;
  uint16                                 MaxOrigPktLen;

  IPV6_P2V(uint8) TimeExceededMsgHdrPtr;
  TcpIp_SizeOfIcmpV6TxMsgBufferType      IcmpPayloadOfs;
  uint16                                 OrigPktDataLen = (*OrigPktDataLenPtr);

   /* "[...] the total length of the ICMP message, including extensions,
    *  MUST NOT exceed the minimum reassembly buffer size."
    *  [RFC4884 7. The ICMP Extension Structure]
    */
  /* #10 Validate the error message parameters */
  if (TcpIp_GetSizeOfIcmpV6TxMsgBuffer() > IPV6_ICMP_ERR_MSG_MAX_PAYLOAD_SIZE)  /*lint !e506 */ /* PRQA S 2991, 2995 */ /* MD_TCPIP_Rule14.3_2991_2995 */
  {
    MaxOrigPktLen = IPV6_ICMP_ERR_MSG_MAX_PAYLOAD_SIZE;
  }
  else
  {
    /* Size of message is limited by IcmpTxMsgBufferSize */
    MaxOrigPktLen = TcpIp_GetSizeOfIcmpV6TxMsgBuffer();
  }

  MaxOrigPktLen -= (uint16) sizeof(IpV6_IcmpTimeExceededMsgType);
  IcmpPayloadOfs = (uint16) sizeof(IpV6_IcmpTimeExceededMsgType);
  TimeExceededMsgHdrPtr = TcpIp_GetAddrIcmpV6TxMsgBuffer(0);

  /* #20 Check if the original packet has invalid packet length,
   * whether the sender is multicast or unspecified or if the
   * controller Ip address index is not valid
   */
  if (   (OrigPktDataLen < sizeof(IpV6_HdrType)) /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (TCPIP_LOCAL_ADDR_V6_IDX_ANY == IpAddrIdx)
      || (IPV6_ADDR_IS_MULTICAST(*SrcAddrPtr))
      || (IPV6_ADDR_IS_UNSPECIFIED(*SrcAddrPtr)))
  {
    /* [RFC4443 2.4. Message Processing Rules]
       "(e) An ICMPv6 error message MUST NOT be originated as a result of
           receiving the following:"
       "(e.3) A packet destined to an IPv6 multicast address. [...]
        (e.6) A packet whose source address does not uniquely identify a
              single node -- e.g., the IPv6 Unspecified Address, an IPv6
              multicast address, or an address known by the ICMP message
              originator to be an IPv6 anycast address." */
    retVal = E_NOT_OK; /* abort sending ICMP error message */
  }
  /* #30 Invoke multipart error message handling routine if message has multipart data */
  else if (0u < MultiPartExtLen) /* multipart message */
  {
    retVal = IpV6_Icmp_VMultipartTimeExdMessage(MultiPartExtLen, &IcmpPayloadOfs,
      MultiPartExtPtr, OrigPktDataPtr, OrigPktDataLenPtr);
  }
  /* #40 Process non multipart message */
  else
  {
    /* #50 If packet payload is more than buffer size
     * truncate the payload
     */
    if (OrigPktDataLen > MaxOrigPktLen)
    {
      /* truncate original packet */
      OrigPktDataLen = MaxOrigPktLen;
    }
    /* In non-multi-part messages the length field is unused */
    TimeExceededMsgHdrPtr[IPV6_ICMP_TIME_EXCD_MSG_OFF_LENGTH] = 0;

    /* return buffer and length for original packet payload. Caller will copy data directly into the buffer */
    (*OrigPktDataPtr)    = TcpIp_GetAddrIcmpV6TxMsgBuffer(IcmpPayloadOfs);
    (*OrigPktDataLenPtr) = OrigPktDataLen;

    IcmpPayloadOfs += OrigPktDataLen;
  }

  if(retVal == E_OK)
  {
    /* #60 Queue the Icmpv6 packet for transmission */
    TimeExceededMsgHdrPtr[IPV6_ICMP_TIME_EXCD_MSG_OFF_RESERVED] = 0;
    TCPIP_PUT_UINT16(TimeExceededMsgHdrPtr, IPV6_ICMP_TIME_EXCD_MSG_OFF_RESERVED16, 0U);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(IpV6_Icmp_PendingMsg.DstAddr, *SrcAddrPtr);

    IpV6_Icmp_PendingMsg.IpAddrIdx  = IpAddrIdx;
    IpV6_Icmp_PendingMsg.Type       = IPV6_ICMP_MSG_TYPE_TIME_EXCEEDED;
    IpV6_Icmp_PendingMsg.Code       = Code;
    IpV6_Icmp_PendingMsg.PayloadPtr = TcpIp_GetAddrIcmpV6TxMsgBuffer(0);
    IpV6_Icmp_PendingMsg.PayloadLen = IcmpPayloadOfs;
    IpV6_Icmp_PendingMsg.Pending    = TRUE;
  }

  return retVal;
} /* End of IpV6_Icmp_VTxTimeExceeded() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */
#endif

#if (TCPIP_SUPPORT_ICMPV6_ECHO_REPLY == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Icmp_Cbk_DestinationUnreachable()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Icmp_Cbk_DestinationUnreachable(
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) DstAddrPtr)
{
  if (TRUE == IpV6_Icmp_PendingEchoReply.Pending)
  {
    if (IPV6_ADDR_EQUALS(IpV6_Icmp_PendingEchoReply.DstAddr, *DstAddrPtr))
    {
      /* cancel sending of pending echo request, since the destination is unreachable */
      IpV6_Icmp_PendingEchoReply.Pending = FALSE;
    }
  }
} /* End of IpV6_Icmp_Cbk_DestinationUnreachable() */
#endif


/**********************************************************************************************************************
 *  IpV6_Icmp_RxIndication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Icmp_RxIndication(
  TcpIp_SizeOfLocalAddrV6Type  IpAddrIdx,
  IPV6_P2V(uint8)              ethPayloadPtr,
  uint16                       ethPayloadLen,
  IPV6_P2C(uint8)              physAddrPtr,
  uint16                       icmpHdrPos,
  boolean                      checksumCalculated)
{
  boolean chksumCal = checksumCalculated;

  TCPIP_ASSERT(TCPIP_LOCAL_ADDR_ID_IS_VALID(IpAddrIdx));
  TCPIP_ASSERT(ethPayloadPtr != NULL_PTR);
  TCPIP_ASSERT(ethPayloadLen  > icmpHdrPos);
  TCPIP_ASSERT(icmpHdrPos     > 0u);

  if (ethPayloadLen >= (icmpHdrPos + sizeof(IpV6_IcmpHeaderType)))
  {
    /* #10 Calculate and validate checksum with that of the recieved packet, if not already done by hardware */
    if (chksumCal == FALSE)
    {
      IpV6_AddrType srcAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
      IpV6_AddrType destAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
      uint16 calculatedChecksumNbo;
      uint16 receivedChecksumNbo;

      receivedChecksumNbo = TCPIP_GET_UINT16_RAW(ethPayloadPtr, icmpHdrPos + IPV6_ICMP_HEADER_OFS_CHECKSUM);
      /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
      IPV6_ADDR_COPY(destAddr, ethPayloadPtr[IPV6_HDR_OFF_DSTADDR]);
      IPV6_ADDR_COPY(srcAddr, ethPayloadPtr[IPV6_HDR_OFF_SRCADDR]);

      calculatedChecksumNbo = IpV6_Icmp_VCalculateChecksumNbo(&srcAddr, &destAddr, &ethPayloadPtr[icmpHdrPos], ethPayloadLen - icmpHdrPos);

      if (receivedChecksumNbo == calculatedChecksumNbo)
      {
        chksumCal = TRUE;
      }
    }
    /* #20 Invoke packet handling function for Icmpv6 packets */
    if (chksumCal == TRUE)
    {
      IpV6_Icmp_VHandlePacket(IpAddrIdx, ethPayloadPtr, ethPayloadLen, physAddrPtr, icmpHdrPos);
    }
  }
} /* End of IpV6_Icmp_RxIndication() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  IpV6_Icmp_VHandleMultipartPacket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(boolean, IPV6_CODE) IpV6_Icmp_VHandleMultipartPacket(
  IPV6_P2C(uint8)   IcmpPayloadPtr,
  IPV6_P2V(uint16)  IcmpPayloadLenPtr,
  IPV6_P2V(uint16)  IcmpMultiPartDataOfsPtr,
  IPV6_P2V(uint16)  IcmpMultiPartDataLenPtr
)
{
  boolean messageHandled =  FALSE;
  if (IpV6_Icmp_VGetMultiPartData(IcmpPayloadPtr, (*IcmpPayloadLenPtr), IcmpMultiPartDataOfsPtr, IcmpMultiPartDataLenPtr) == E_OK)
  {
    if ((*IcmpMultiPartDataOfsPtr) > 0u)
    {
      (*IcmpPayloadLenPtr) = (*IcmpMultiPartDataOfsPtr) - 4u;
    }
  }
  else
  {
    messageHandled = TRUE;
  }
  return messageHandled;
}

/**********************************************************************************************************************
 *  IpV6_Icmp_VHandlePacket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) IpV6_Icmp_VHandlePacket(
  TcpIp_SizeOfLocalAddrV6Type  LocalAddrV6Idx,
  IPV6_P2V(uint8)              ethPayloadPtr,
  uint16                       ethPayloadLen,
  IPV6_P2C(uint8)              physAddrPtr,
  uint16                       icmpHdrPos)
{
  boolean           messageHandled =  FALSE;
  uint16            icmpPayloadOfs =  icmpHdrPos + (uint16) sizeof(IpV6_IcmpHeaderType);
  uint16            icmpPayloadLen =  ethPayloadLen - icmpPayloadOfs;
  IPV6_P2V(uint8)   icmpPayloadPtr =  &ethPayloadPtr[icmpPayloadOfs];
  uint8             icmpType       =  ethPayloadPtr[icmpHdrPos /* + IPV6_ICMP_HEADER_OFS_TYPE */];
  uint8             icmpCode       =  ethPayloadPtr[icmpHdrPos + IPV6_ICMP_HEADER_OFS_CODE];
  TcpIp_SizeOfIpV6CtrlType    ipCtrlIdx;
  IpV6_HdrType    ipV6Hdr;

  uint16 icmpMultiPartDataOfs = 0;
  uint16 icmpMultiPartDataLen = 0;

  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  ipV6Hdr.HopLimit = TCPIP_GET_UINT8(ethPayloadPtr, IPV6_HDR_OFF_HOPLIMIT);
  /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(ipV6Hdr.DstAddr, ethPayloadPtr[IPV6_HDR_OFF_DSTADDR]);
  IPV6_ADDR_COPY(ipV6Hdr.SrcAddr, ethPayloadPtr[IPV6_HDR_OFF_SRCADDR]);

  /* 10 Handle ICMPv6 packet based on it's type. */
  switch (icmpType)
  {
  case IPV6_ICMP_MSG_TYPE_DEST_UNREACHABLE: /* Type 1 */
    /* fall through */
  case IPV6_ICMP_MSG_TYPE_TIME_EXCEEDED:    /* Type 3 */

    /* We support ICMPv6 multi-Part Messages according to [RFC4884].
     * Validate and retrieve location of multi-part data (if message contains multi-part data).
     * If multi-part data is corrupt, message is marked as handled and therefore
     * not forwarded to upper layers at end of function.
     */
    messageHandled = IpV6_Icmp_VHandleMultipartPacket(icmpPayloadPtr, &icmpPayloadLen,
      &icmpMultiPartDataOfs, &icmpMultiPartDataLen);

    break;

  /* Type 2 */
#if (TCPIP_SUPPORT_IPV6_PATH_MTU == STD_ON)
  case IPV6_ICMP_MSG_TYPE_PKT_TOO_BIG:      /* Type 2 */
    if (TcpIp_IsEnablePathMtuOfIpV6Ctrl(ipCtrlIdx) == TRUE)
    {
      IpV6_Icmp_VRxErrPacketTooBig(ipCtrlIdx, &ipV6Hdr.SrcAddr, icmpPayloadPtr, icmpPayloadLen);
      messageHandled = TRUE;
    }
    break;
#endif



#if (TCPIP_SUPPORT_ICMPV6_ECHO_REPLY == STD_ON)
  case IPV6_ICMP_MSG_TYPE_ECHO_REQ:         /* Type 128 */
    IpV6_Icmp_VRxEchoRequest(LocalAddrV6Idx, &ipV6Hdr.SrcAddr, icmpPayloadPtr, icmpPayloadLen);
    messageHandled = TRUE;
    break;
#endif

#if (IPV6_ICMP_ENABLE_NDP == STD_ON)

  case IPV6_ICMP_MSG_TYPE_NDP_RA:           /* Type 134 */

    /* perform basic validation of RA (RFC4861 6.1.2) */
    if (   (IPV6_NDP_MSG_HOP_LIMIT == ipV6Hdr.HopLimit)
        && (0u == icmpCode)
        && (IPV6_NDP_RA_MIN_PAYLOAD_LEN <= icmpPayloadLen))
    {
      IpV6_Ndp_VRxRouterAdvertisement(LocalAddrV6Idx, &ipV6Hdr.SrcAddr, icmpPayloadPtr, icmpPayloadLen);
      messageHandled = TRUE;
    }
    break;

  case IPV6_ICMP_MSG_TYPE_NDP_NS:           /* Type 135 */

    /* perform basic validation of NS (RFC4861 7.1.1) */
    if (   (IPV6_NDP_MSG_HOP_LIMIT == ipV6Hdr.HopLimit)
        && (0u == icmpCode)
        && (IPV6_NDP_NS_MIN_PAYLOAD_LEN <= icmpPayloadLen))
    {
      TCPIP_ASSERT(physAddrPtr   != NULL_PTR);
      (void)IpV6_Ndp_VRxNeighborSolicitation(LocalAddrV6Idx, &ipV6Hdr.SrcAddr, physAddrPtr, icmpPayloadPtr, icmpPayloadLen);
      messageHandled = TRUE;
    }
    break;

  case IPV6_ICMP_MSG_TYPE_NDP_NA:           /* Type 136 */

    /* perform basic validation of NA (RFC4861 7.1.2) */
    if (   (IPV6_NDP_MSG_HOP_LIMIT == ipV6Hdr.HopLimit)
        && (0u == icmpCode)
        && (IPV6_NDP_NA_MIN_PAYLOAD_LEN <= icmpPayloadLen))
    {
      TCPIP_ASSERT(physAddrPtr   != NULL_PTR);
      IpV6_Ndp_VRxNeighborAdvertisement(LocalAddrV6Idx, &ipV6Hdr.SrcAddr, physAddrPtr, icmpPayloadPtr, icmpPayloadLen);
      messageHandled = TRUE;
    }
    break;

  case IPV6_ICMP_MSG_TYPE_NDP_REDIR:        /* Type 137 */

    /* perform basic validation of Redirect (RFC4861 8.1) */
    if (   (IPV6_NDP_MSG_HOP_LIMIT == ipV6Hdr.HopLimit)
        && (0u == icmpCode)
        && (IPV6_NDP_REDIR_MIN_PAYLOAD_LEN <= icmpPayloadLen))
    {
      IpV6_Ndp_VRxRedirect(LocalAddrV6Idx, &ipV6Hdr.SrcAddr, icmpPayloadPtr, icmpPayloadLen);
      messageHandled = TRUE;
    }
    break;

#endif /* (IPV6_ICMP_ENABLE_NDP == STD_ON) */

#if (TCPIP_SUPPORT_NDP_INV_NA == STD_ON)

  case IPV6_ICMP_MSG_TYPE_NDP_INV_NS:          /* Type 141 */
    {
      TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(ipCtrlIdx);
      /* perform basic validation of IND Solicitation
       * [RFC3122 4.3.1 Validation of Inverse Neighbor Discovery Solicitations]
       */
      if (   (TcpIp_IsEnableNdpInvNaOfNdpConfig(ndpConfigIdx) == TRUE)
          && (IPV6_NDP_IS_MIN_PAYLOAD_LEN <= icmpPayloadLen)
          && (0u == icmpCode)
          && (IPV6_NDP_MSG_HOP_LIMIT == ipV6Hdr.HopLimit))
      {
        IpV6_Ndp_VRxInverseSolicitation(LocalAddrV6Idx, &ipV6Hdr.SrcAddr, icmpPayloadPtr, icmpPayloadLen);
        messageHandled = TRUE;
      }
      break;
    }
#endif

#if (TCPIP_SUPPORT_NDP_INV_NS == STD_ON)
  case IPV6_ICMP_MSG_TYPE_NDP_INV_NA:          /* Type 141 */
    {
      TcpIp_SizeOfNdpConfigType ndpConfigIdx = TcpIp_GetNdpConfigIdxOfIpV6Ctrl(ipCtrlIdx);
      /* perform basic validation of IND Advertisement
       * [RFC3122 4.3.2 Validation of Inverse Neighbor Discovery Advertisements]
       */
      if (   (TcpIp_IsEnableNdpInvNsOfNdpConfig(ndpConfigIdx) == TRUE)
          && (IPV6_NDP_IA_MIN_PAYLOAD_LEN <= icmpPayloadLen)
          && (0u == icmpCode)
          && (IPV6_NDP_MSG_HOP_LIMIT == ipV6Hdr.HopLimit))
      {
        IpV6_Ndp_VRxInverseAdvertisement(LocalAddrV6Idx, &ipV6Hdr.SrcAddr, icmpPayloadPtr, icmpPayloadLen);
        messageHandled = TRUE;
      }
      break;
    }
#endif

    default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    /* Default case left blank intentionally */
    break;
  }

  /* #20 If message was not handled by the ICMPv6, call user handler IcmpV6MsgHandlerCbkFct (if it is configured) */
  if (messageHandled == FALSE)
  {
    TcpIp_IcmpMultiPartMsgHandlerCbkType icmpMsgHandlerFuncPtr = TcpIp_GetIcmpV6MsgHandlerCbkFctPtr();

    /* Packet dropped due to invalid IcmpV6 type or code */
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
    TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER3_IPV6);
#endif

    if (icmpMsgHandlerFuncPtr != NULL_PTR)
    {
      TcpIp_SizeOfLocalAddrType localAddrIdx = TCPIP_IPV6_TO_LOCAL_ADDR_IDX(LocalAddrV6Idx);
      IPV6_P2V(uint8) multiPartPtr;
      TcpIp_SockAddrBaseType remoteSockAddr; /* PRQA S 0759 */ /* MD_MSR_Union */
      remoteSockAddr.SockAddrIn6.sin6_family = TCPIP_AF_INET6;
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IPV6_ADDR_COPY(remoteSockAddr.SockAddrIn6.sin6_addr.addr[0], ipV6Hdr.SrcAddr);
      remoteSockAddr.SockAddrIn6.sin6_port = 0;

      if (icmpMultiPartDataLen > 0u)
      {
        multiPartPtr = &icmpPayloadPtr[icmpMultiPartDataOfs];
      }
      else
      {
        multiPartPtr = NULL_PTR;
      }
      icmpMsgHandlerFuncPtr(TCPIP_LOCAL_ADDR_IDX_TO_ID(localAddrIdx), (TCPIP_P2C(TcpIp_SockAddrType)) &remoteSockAddr.TcpIpSockAddr,
          ipV6Hdr.HopLimit, icmpType, icmpCode, icmpPayloadLen, icmpPayloadPtr, icmpMultiPartDataLen, multiPartPtr);
      TCPIP_DUMMY_STATEMENT(remoteSockAddr.SockAddrIn6); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    }
  }
} /* IpV6_Icmp_VHandlePacket() */ /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  IpV6_Icmp_Init()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Icmp_Init(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

#if (TCPIP_SUPPORT_ICMPV6_ERROR_MESSAGES == STD_ON)
  IpV6_Icmp_PendingMsg.Pending = FALSE;
#endif

#if (TCPIP_SUPPORT_ICMPV6_ECHO_REPLY == STD_ON)
  IpV6_Icmp_PendingEchoReply.Pending = FALSE;
#endif

} /* End of IpV6_Icmp_Init() */


/**********************************************************************************************************************
 *  IpV6_Icmp_TxRawMessage
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(BufReq_ReturnType, TCPIP_CODE) IpV6_Icmp_TxRawMessage(
    TCPIP_P2V(TcpIp_LocalAddrIterType) IpAddrIdxPtr,
    TCPIP_P2C(IpV6_AddrType)           DestIpAddrPtr,
    uint8                              HopLimit,
    uint8                              Type,
    uint8                              Code,
    uint16                             DataLength,
    TCPIP_P2C(uint8)                   DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType                 retVal;
  TcpIp_IpTxRequestDescriptorType   ipTxReqDesc;
  TCPIP_P2V(uint8)                  icmpBufferPtr;
  uint16                            icmpBufferLen = DataLength;
  TcpIp_SizeOfSocketDynType         icmpDynIpV6SocketIdx = TcpIp_GetIpV6SocketDynIcmpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get ICMP TX buffer. */
  retVal = IpV6_Icmp_ProvideTxBuffer(IpAddrIdxPtr, icmpDynIpV6SocketIdx,
                                                          &ipTxReqDesc, DestIpAddrPtr, &icmpBufferPtr, &icmpBufferLen);

  if (retVal == BUFREQ_OK)
  {
    /* #20 Save current HopLimit of ICMP socket. */
    uint8 oldSocketHopLimit =
      TcpIp_GetHopLimitOfIpV6SocketDyn(icmpDynIpV6SocketIdx);

    uint8 oldSocketFlags =
      TcpIp_GetFlagsOfIpV6SocketDyn(icmpDynIpV6SocketIdx);

    TCPIP_ASSERT(icmpBufferLen >= DataLength);

    /* #30 Copy ICMP payload. */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpBase_Copy(icmpBufferPtr, DataPtr, DataLength);

    /* #40 Change HopLimit of ICMP socket. */
    IpV6_SetHopLimit(icmpDynIpV6SocketIdx, HopLimit);

    /* #50 Trigger transmission of ICMP packet. */
    if (IpV6_Icmp_Transmit(icmpDynIpV6SocketIdx, &ipTxReqDesc, Type, Code, DataLength) != E_OK)
    {
      retVal = BUFREQ_E_NOT_OK;
    }

    /* #60 Restore HopLimit of ICMP socket. */
    TcpIp_SetHopLimitOfIpV6SocketDyn(icmpDynIpV6SocketIdx, oldSocketHopLimit);

    TcpIp_SetFlagsOfIpV6SocketDyn(icmpDynIpV6SocketIdx, oldSocketFlags);
  }

  return retVal;
} /* IpV6_Icmp_TxRawMessage() */  /* PRQA S 6050, 6060 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STPAR */



/**********************************************************************************************************************
 *  IpV6_Icmp_Transmit()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Icmp_Transmit(
  TcpIp_SizeOfSocketDynType                 SocketIdx,
  IPV6_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr,
  uint8                                     Type,
  uint8                                     Code,
  uint16                                    PayloadLen)
{
  uint16                                 dataLen = PayloadLen;
  P2VAR(uint8, AUTOMATIC, IPV6_APPL_VAR) IcmpV6HdrPtr;


  TCPIP_ASSERT(IpV6_State != IPV6_STATE_UNINIT);
  TCPIP_ASSERT(IpTxReqDescPtr != NULL_PTR);

  /* #10 Update the IcmpV6 header information */
  IcmpV6HdrPtr = IpV6_Icmp_EthBufPtr;
  IcmpV6HdrPtr[IPV6_ICMP_HEADER_OFS_TYPE] = Type;
  IcmpV6HdrPtr[IPV6_ICMP_HEADER_OFS_CODE]= Code;
  TCPIP_PUT_UINT16(IcmpV6HdrPtr, IPV6_ICMP_HEADER_OFS_CHECKSUM, 0U);

  dataLen += (uint16) sizeof(IpV6_IcmpHeaderType);

  /* Checksum is calculated by lower layer or in hardware */
  /* #20 Invoke transmit function for Ipv6 */
  return IpV6_Transmit(SocketIdx, IpTxReqDescPtr, IPV6_HDR_ID_ICMP, dataLen, FALSE, 0, FALSE);
} /* End of IpV6_Icmp_Transmit() */


/**********************************************************************************************************************
 *  IpV6_Icmp_ProvideTxBuffer()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
FUNC(BufReq_ReturnType, TCPIP_CODE) IpV6_Icmp_ProvideTxBuffer(
    IPV6_P2V(TcpIp_LocalAddrV6IterType)       IpAddrIdxPtr,
    TcpIp_SizeOfSocketDynType                 SocketIdx,
    IPV6_P2V(TcpIp_IpTxRequestDescriptorType) TxReqDescPtr,
    IPV6_P2C(IpV6_AddrType)                   DstAddrPtr,
    IPV6_P2V(uint8*)                          BufPtr,
    IPV6_P2V(uint16)                          BufLenPtr)
{
  BufReq_ReturnType BufReqRes;

  TCPIP_ASSERT(IpV6_State != IPV6_STATE_UNINIT);
  TCPIP_ASSERT((SocketIdx == TcpIp_GetIpV6SocketDynNdpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX))||
    (SocketIdx == TcpIp_GetIpV6SocketDynIcmpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX)));
  TCPIP_ASSERT(NULL_PTR != IpAddrIdxPtr);
  TCPIP_ASSERT(NULL_PTR != TxReqDescPtr);
  TCPIP_ASSERT(NULL_PTR != BufPtr);
  TCPIP_ASSERT(NULL_PTR != BufLenPtr);
  TCPIP_ASSERT(NULL_PTR != DstAddrPtr);

  *BufLenPtr += (uint16) sizeof(IpV6_IcmpHeaderType);

  BufReqRes = IpV6_ProvideTxBuffer(IpAddrIdxPtr, SocketIdx, DstAddrPtr, BufPtr, BufLenPtr, TxReqDescPtr, FALSE);

  if (BUFREQ_OK == BufReqRes)
  {
    IpV6_Icmp_EthBufPtr = *BufPtr;

    *BufPtr = &(*BufPtr)[sizeof(IpV6_IcmpHeaderType)];
    *BufLenPtr -= (uint16) sizeof(IpV6_IcmpHeaderType);
  }
  else
  {
    /* do nothing */
  }
  return BufReqRes;
} /* End of IpV6_Icmp_ProvideTxBuffer() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  IpV6_Icmp_MainFunction()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Icmp_MainFunction(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  IPV6_BEGIN_CRITICAL_SECTION();

#if (TCPIP_SUPPORT_ICMPV6_ECHO_REPLY == STD_ON)
  /* #10 Send pending ICMPv6 Echo response. */
  if (TRUE == IpV6_Icmp_PendingEchoReply.Pending)
  {
    if (E_OK == IpV6_Icmp_VTxPendingMessage(&IpV6_Icmp_PendingEchoReply))
    {
      /* pending echo successfully transmitted */
      IpV6_Icmp_PendingEchoReply.Pending = FALSE;
    }
  }
#endif

  /* #20 Send pending ICMPv6 error message. */
#if (TCPIP_SUPPORT_ICMPV6_ERROR_MESSAGES == STD_ON)
  if (TRUE == IpV6_Icmp_PendingMsg.Pending)
  {
    if (E_OK == IpV6_Icmp_VTxPendingMessage(&IpV6_Icmp_PendingMsg))
    {
      /* pending ICMP message successfully transmitted. */
      IpV6_Icmp_PendingMsg.Pending = FALSE;
    }
  }
#endif

  IPV6_END_CRITICAL_SECTION();
} /* End of IpV6_Icmp_MainFunction() */


/**********************************************************************************************************************
 *  IpV6_Icmp_StoreChecksumInHeader
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV6_CODE) IpV6_Icmp_StoreChecksumInHeader(
    uint16          Checksum,
    IPV6_P2V(uint8) IcmpHdrPtr)
{
  uint8 *MsgPtr = IcmpHdrPtr;

  /* calculate checksum */
  TCPIP_PUT_UINT16_RAW(MsgPtr, IPV6_ICMP_HEADER_OFS_CHECKSUM, Checksum);

} /* IpV6_Icmp_StoreChecksumInHeader() */

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* (TCPIP_SUPPORT_IPV6 == STD_ON) */
/**********************************************************************************************************************
 *  END OF FILE: IpV6_Icmp.c
 *********************************************************************************************************************/
