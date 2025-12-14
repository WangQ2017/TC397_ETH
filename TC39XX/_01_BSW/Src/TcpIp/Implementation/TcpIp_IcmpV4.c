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
 *         \file  TcpIp_IcmpV4.c
 *        \brief  Implementation of Internet Control Message Protocol for IPv4 (ICMPv4)
 *
 *      \details  This file is part of the TcpIp IPv4 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv4 submodule. >> TcpIp_IpV4.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/


/* PRQA S 0828 EOF */ /* MD_MSR_1.1 */

#define TCPIP_ICMPV4_SOURCE

#include "TcpIp_Cfg.h"
#include "TcpIp_Lcfg.h"
#if (TCPIP_SUPPORT_ICMPV4  == STD_ON)                                                                                   /* COV_TCPIP_ICMPV4_ALWAYS_ON */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "ComStack_Types.h"


#include "TcpIp_IcmpV4.h"
#include "TcpIp_IcmpV4_Cbk.h"
#include "TcpIp_IpV4_Priv.h"


#include "TcpIp_IpV4.h"
#include "TcpIp_Priv.h"


#include "IpBase_Copy.h"
#include "IpBase.h"


#if !defined (STATIC)                                                                                                   /* COV_TCPIP_COMPATIBILITY */
# define STATIC static
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define IPV4_ICMP_TYPE_CODE_CHECKSUM_LEN      4u
#define IPV4_ICMP_IDENT_SEQNUM_LEN            4u
#define IPV4_ICMP_HEADER_LEN                  8u
#define IPV4_ICMP_MAX_ORIGINAL_PAYLOAD_LEN    8u
#define ICMPV4_REPLY_CODE                     0u

#define ICMPV4_HDR_START_TYPE_OFS             0u
#define ICMPV4_HDR_START_CODE_OFS             1u
#define ICMPV4_HDR_START_CHECKSUM_OFS         2u
#define ICMPV4_HDR_START_IDENTIFIER_OFS       4u
#define ICMPV4_HDR_START_SEQNUM_OFS           6u
#define ICMPV4_HDR_START_DATA_OFS             8u
/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


typedef struct
{
  uint8    Type;
  uint8    Code;
  uint16   Checksum;
  uint16   Identifier;
  uint16   SequNum;
} IpV4_Icmp_EchoMsgType; /* Echo or Echo Request */

typedef struct
{
  IpBase_AddrInType           Dest;
  uint16                      Identifier;
  uint16                      SequNum;
  TcpIp_SizeOfLocalAddrV4Type LocalAddrV4Idx;
  boolean                     IpV4_Icmp_EchoReplyIsPending;
  uint16                      IpV4_Icmp_EchoReplyDataLen;
} IpV4_Icmp_EcoReplyType; /* data to retry sending a PONG */

# if (TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG == STD_ON)
typedef struct
{
  IpBase_AddrInType           Dest;
  TcpIp_SizeOfLocalAddrV4Type LocalAddrV4Idx;
  boolean                     IpV4_Icmp_DestinationUnreachablePending;
  uint16                      IpV4_Icmp_DestUnreachMsgLen;
  uint8                       Code;
} IpV4_Icmp_DetinationUnreachableType; /* data to retry sending a Detination Unreachable Msg */
#endif

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

STATIC VAR(IpV4_Icmp_EcoReplyType, IPV4_VAR_NOINIT) IpV4_Icmp_EchoReplyPendingMsg;

# if (TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG == STD_ON)
STATIC VAR(IpV4_Icmp_DetinationUnreachableType, IPV4_VAR_NOINIT) IpV4_Icmp_DestinationUnrechablePendingMsg;
#endif

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */


#define TCPIP_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

STATIC VAR(uint16, IPV4_VAR_NOINIT) IpV4_Icmp_SeqNum;

#define TCPIP_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

/**********************************************************************************************************************
 *  IpV4_Icmp_VSendPendingEchoReply
 *********************************************************************************************************************/
/*! \brief        Tries to send a pending echo reply, if there is one.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, IPV4_CODE) IpV4_Icmp_VSendPendingEchoReply(void);

# if (TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG == STD_ON)
/**********************************************************************************************************************
*  IpV4_Icmp_VSendPendingDestinationUnreachableMsg
*********************************************************************************************************************/
/*! \brief        Tries to send a pending Destination Unreachable Message, if there is one.
*  \details      -
*  \pre          -
*  \context      TASK
*  \reentrant    FALSE
*  \synchronous  TRUE
*********************************************************************************************************************/
STATIC FUNC(void, IPV4_CODE) IpV4_Icmp_VSendPendingDestinationUnreachableMsg(void);
#endif

/**********************************************************************************************************************
 *  IpV4_Icmp_VRxEchoRequest
 *********************************************************************************************************************/
/*! \brief        Receives an ICMP Echo Request Message and sends an Echo Reply.
 *  \details      If the Echo reply cannot be sent directly because there is no ethernet buffer available or link-layer
 *                address resolution is still in progress, transmission of the
 *                Echo Reply will be scheduled for the MainFunction.
 *  \param[in]    LocalAddrV4Idx    Local IP address identifier.
 *  \param[in]    RemNetAddr        Remote IP address value.
 *  \param[in]    DataPtr           Payload of the ICMP message starting with the
                                    Echo Request Identifier and Sequence Number values.
 *  \param[in]    DataLen           Length of the Payload.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Icmp_VRxEchoRequest(
  TcpIp_SizeOfLocalAddrV4Type LocalAddrV4Idx,
  IpBase_AddrInType           RemNetAddr,
  IPV4_P2C(uint8)             DataPtr,
  uint16                      DataLen);

/**********************************************************************************************************************
 *  IpV4_Icmp_VSendRawMessage
 *********************************************************************************************************************/
/*! \brief        Sends an ICMP message with the specified Type, Code and payload.
 *  \details      This function will automatically send a fragmented IP packet if the payload exceeds the MTU and
 *                fragmentation is enabled.
 *  \param[in]    LocalAddrV4Idx    Local IP address identifier(source).
 *  \param[in]    DestIpAddr        Destination IP address value.
 *  \param[in]    Type              Type of the ICMP message.
 *  \param[in]    Code              Code of the ICMP message.
 *  \param[in]    VarHeaderBytesPtr Pointer to the 4 message dependent bytes that follow the Type, Code and Checksum
 *                                  fields in the ICMP header.
 *                                  Note: Exactly four bytes will be read from the pointer destination.
 *  \param[in]    PayloadPtr        Pointer to the payload of the ICMPv4 message.
 *  \param[in]    PayloadLen        Length of the payload in bytes.
 *  \return       BUFREQ_OK         Transmit triggered.
 *  \return       BUFREQ_E_BUSY     Transmit currently not possible. Retry later.
 *  \return       BUFREQ_E_NOT_OK   Transmit not possible due to unknown error.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV4_CODE) IpV4_Icmp_VSendRawMessage(
  TcpIp_LocalAddrV4IterType LocalAddrV4Idx,
  IpBase_AddrInType         DestIpAddr,
  uint8                     Type,
  uint8                     Code,
  IPV4_P2C(uint8)           VarHeaderBytesPtr,
  IPV4_P2C(uint8)           PayloadPtr,
  uint16                    PayloadLen);

/**********************************************************************************************************************
 *  IpV4_Icmp_SendEchoMessage
 *********************************************************************************************************************/
/*! \brief        Sends an ICMP Echo (Request/Reply) message.
 *  \details      -
 *  \param[in]    LocalAddrV4Idx  Local IP address identifier(Source).
 *  \param[in]    DestIpAddr      Destination IP address.
 *  \param[in]    IcmpType        Type of the ICMP message (ECHO_REQUEST, ECHO_REPLY).
 *  \param[in]    IcmpCode        Code of the ICMP message (usually 0).
 *  \param[in]    Identifier      Identifier of the Echo message
 *  \param[in]    SequenceNumber  Sequence Number of the ICMP message.
 *  \param[in]    DataPtr         Pointer to the payload of the Echo message.
 *  \param[in]    DataLenByte     Length of the payload in bytes.
 *  \return       BUFREQ_OK       Transmit triggered.
 *  \return       BUFREQ_E_BUSY   Transmit currently not possible. Retry later.
 *  \return       BUFREQ_E_NOT_OK Transmit not possible.
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(BufReq_ReturnType, IPV4_CODE) IpV4_Icmp_SendEchoMessage(
  TcpIp_SizeOfLocalAddrV4Type LocalAddrV4Idx,
  IpBase_AddrInType           DestIpAddr,
  uint8                       IcmpType,
  uint8                       IcmpCode,
  uint16                      Identifier,
  uint16                      SequenceNumber,
  IPV4_P2C(uint8)             DataPtr,
  uint16                      DataLenByte);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  IpV4_Icmp_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Icmp_Init(void)
{
  TcpIp_IpV4SocketDynIterType ipV4SocketIdx;
  /* #10 Initialize the ICMP module. */
  IpV4_Icmp_EchoReplyPendingMsg.IpV4_Icmp_EchoReplyIsPending = FALSE;
# if (TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG == STD_ON)
  IpV4_Icmp_DestinationUnrechablePendingMsg.IpV4_Icmp_DestinationUnreachablePending = FALSE;
#endif
  IpV4_Icmp_SeqNum = 0;

  ipV4SocketIdx = TcpIp_GetIpV4SocketDynIcmpIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX);

  /* #20 Set the time to live for the given socket index. */
  IpV4_Ip_SetTimeToLive(ipV4SocketIdx, TcpIp_GetTimeToLiveOfIcmpConfig(TCPIP_ICMPV4CONFIG_IDX));
} /* IpV4_Icmp_Init() */

/**********************************************************************************************************************
 *  IpV4_Icmp_MainFunction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Icmp_MainFunction(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Send pending ICMPv4 Echo Replies. */
  if (IpV4_Icmp_EchoReplyPendingMsg.IpV4_Icmp_EchoReplyIsPending == TRUE)
  {
    IpV4_Icmp_VSendPendingEchoReply();
  }
  /* #20 Send pending ICMPv4 Destination Unreachable Messages. */
# if (TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG == STD_ON)
  if (IpV4_Icmp_DestinationUnrechablePendingMsg.IpV4_Icmp_DestinationUnreachablePending == TRUE)
  {
    IpV4_Icmp_VSendPendingDestinationUnreachableMsg();
  }
#endif

} /* IpV4_Icmp_MainFunction() */

/**********************************************************************************************************************
 *  IpV4_Icmp_RxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Icmp_RxIndication(
  TcpIp_SizeOfLocalAddrV4Type LocalAddrV4Idx,
  IpBase_AddrInType           RemNetAddr,
  uint8                       Ttl,
  IPV4_P2V(uint8)             DataPtr,
  uint16                      DataLen,
  boolean                   ChecksumCalculated)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean chksumCal = ChecksumCalculated;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());
  TCPIP_ASSERT(DataPtr    != NULL_PTR);

  if (DataLen >= IPV4_ICMP_HEADER_LEN)
  {
    /* #10 Check if the checksum is calculated. */
    if (chksumCal == FALSE)
    {
      chksumCal = (boolean)(IpBase_TcpIpChecksumAdd(DataPtr, DataLen, 0, TRUE) == 0u);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */          /* SBSW_TCPIP_FUNC_CALL_RXINDICATION_CALLER */
    }

    if (chksumCal == TRUE)
    {
      uint8 type = TCPIP_GET_UINT8(DataPtr, ICMPV4_HDR_START_TYPE_OFS);
      uint8 code = TCPIP_GET_UINT8(DataPtr, ICMPV4_HDR_START_CODE_OFS);

      boolean messageHandled  = FALSE;

      if (type == IPV4_ICMP_TYPE_ECHO)
      {
        if (code == ICMPV4_REPLY_CODE)
        {
          /* #20 Send the Echo reply, if Echo Request is recieved.  */
          /* Pass datapointer at position identifier and and pass the updated datalength(subtracted  first 4 bytes of header) .*/
          IpV4_Icmp_VRxEchoRequest(LocalAddrV4Idx, RemNetAddr, &DataPtr[IPV4_ICMP_TYPE_CODE_CHECKSUM_LEN], DataLen - IPV4_ICMP_TYPE_CODE_CHECKSUM_LEN);                                       /* SBSW_TCPIP_FUNC_CALL_RXINDICATION_CALLER */
          messageHandled = TRUE;
        }
      }

      if ((messageHandled == FALSE) && (TcpIp_GetIcmpMsgHandlerCbkFctPtr() != NULL_PTR)) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      {
        TcpIp_LocalAddrIdType  localAddrId = TCPIP_LOCAL_ADDR_IDX_TO_ID(TCPIP_LOCAL_ADDR_IDX_TO_IPVX(LocalAddrV4Idx));
        TcpIp_SockAddrBaseType remoteSockAddr;  /* PRQA S 0759 */ /* MD_MSR_Union */
        remoteSockAddr.SockAddrIn.sin_family = TCPIP_AF_INET;
        remoteSockAddr.SockAddrIn.sin_port   = TCPIP_PORT_NOT_SET;
        remoteSockAddr.SockAddrIn.sin_addr   = RemNetAddr;

        /* #30 Discard the message, if IcmpMsgHandler is configured and if the recieved message is not Echo request. */
        /* ICMP type not supported -> silently discard message */
        TcpIp_GetIcmpMsgHandlerCbkFctPtr()(localAddrId, (TCPIP_P2C(TcpIp_SockAddrType)) &remoteSockAddr.TcpIpSockAddr, Ttl,  /* SBSW_TCPIP_FUNC_PTR_CALL */ /* SBSW_TCPIP_LOCAL_VARIABLE_PASSED */ /* SBSW_TCPIP_FUNC_CALL_RXINDICATION_CALLER */
          type, code, DataLen - ICMPV4_HDR_START_IDENTIFIER_OFS, &DataPtr[ICMPV4_HDR_START_IDENTIFIER_OFS]);
        TCPIP_DUMMY_STATEMENT(remoteSockAddr.SockAddrIn); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      }
    }
  }

}  /* IpV4_Icmp_RxIndication() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */


/**********************************************************************************************************************
 *  IpV4_Icmp_SendEcho
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Icmp_SendEcho(
  TcpIp_SizeOfLocalAddrV4Type LocalAddrV4Idx,
  IpBase_AddrInType           Dest,
  IPV4_P2C(uint8)             DataPtr,
  uint16                      LenByte )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

 /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4() || LocalAddrV4Idx == TCPIP_LOCAL_ADDR_V4_IDX_ANY);
  TCPIP_ASSERT(DataPtr    != NULL_PTR);

  /* #10 Increment the sequence number. */
  IpV4_Icmp_SeqNum++;
  /* #20 Check if echo message has been send successfully.*/
  if (IpV4_Icmp_SendEchoMessage(LocalAddrV4Idx, Dest, IPV4_ICMP_TYPE_ECHO, 0, 0, IpV4_Icmp_SeqNum, DataPtr, LenByte) == BUFREQ_OK) /* SBSW_TCPIP_FUNC_CALL_PTR_PASSING_CALLER */
  {
    retVal = E_OK;
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /* IpV4_Icmp_SendEcho() */

# if (TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG == STD_ON)
/**********************************************************************************************************************
 *  IpV4_Icmp_SendDestUnreachable()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Icmp_SendDestUnreachable(
  TcpIp_LocalAddrV4IterType LocalAddrV4Idx,
  TCPIP_P2C(uint8)          DataPtr,
  uint8                     IcmpCode)
{
  /* ----- Local Variables ---------------------------------------------- */
  const uint8 unusedHeaderBytes[4] = { 0, 0, 0, 0 };
  uint8  ipHdrLen     = TCPIP_IPV4_HDR_FIELD_GET_IHL_BYTE(DataPtr);
  uint16 ipPayloadLen = TCPIP_IPV4_HDR_FIELD_GET_TOTAL_LEN(DataPtr) - ipHdrLen;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Limit original IP packet payload to 64 bits according to IETF RFC 792. */
  if (ipPayloadLen > IPV4_ICMP_MAX_ORIGINAL_PAYLOAD_LEN)
  {
    ipPayloadLen = IPV4_ICMP_MAX_ORIGINAL_PAYLOAD_LEN;
  }

  /* #20 Send ICMP Destination Unreachable message. */
  if (IpV4_Icmp_VSendRawMessage(LocalAddrV4Idx, TCPIP_GET_UINT32_RAW(DataPtr, TCPIP_IPV4_HDR_OFS_SRC_ADDR),
                                IPV4_ICMP_TYPE_DEST_UNRECHABLE, IcmpCode, &unusedHeaderBytes[0],
                                DataPtr, ipHdrLen + ipPayloadLen) != BUFREQ_OK)                                         /* SBSW_TCPIP_FUNC_CALL_PTR_PASSING_CALLER */
  {
    IpV4_Icmp_DestinationUnrechablePendingMsg.LocalAddrV4Idx = (TcpIp_SizeOfLocalAddrV4Type)LocalAddrV4Idx;
    IpV4_Icmp_DestinationUnrechablePendingMsg.Dest = TCPIP_GET_UINT32_RAW(DataPtr, TCPIP_IPV4_HDR_OFS_SRC_ADDR);
    IpV4_Icmp_DestinationUnrechablePendingMsg.Code = IcmpCode;

    /* copy data that was received with incoming message */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpBase_Copy(TcpIp_GetAddrIcmpDestUnreachableMsg(0), &DataPtr[0], (uint16)(ipPayloadLen + ipHdrLen));                /* SBSW_TCPIP_ICMPV4_IPBASE_COPY_CALLEE */
    IpV4_Icmp_DestinationUnrechablePendingMsg.IpV4_Icmp_DestUnreachMsgLen = ipHdrLen + ipPayloadLen;
    IpV4_Icmp_DestinationUnrechablePendingMsg.IpV4_Icmp_DestinationUnreachablePending = TRUE;

  }

} /* IpV4_Icmp_SendDestUnreachable() */
#endif

/**********************************************************************************************************************
 *  IpV4_Icmp_SendEchoMessage
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(BufReq_ReturnType, IPV4_CODE) IpV4_Icmp_SendEchoMessage(
  TcpIp_SizeOfLocalAddrV4Type LocalAddrV4Idx,
  IpBase_AddrInType           DestIpAddr,
  uint8                       IcmpType,
  uint8                       IcmpCode,
  uint16                      Identifier,
  uint16                      SequenceNumber,
  IPV4_P2C(uint8)             DataPtr,
  uint16                      DataLenByte)
{
   /* ----- Local Variables ---------------------------------------------- */
  uint8 icmpHeaderBytes[IPV4_ICMP_HEADER_LEN - IPV4_ICMP_TYPE_CODE_CHECKSUM_LEN];

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy Identifier and Seq Number into the Icmp header buffer. */
  TCPIP_PUT_UINT16(&icmpHeaderBytes[0], ICMPV4_HDR_START_IDENTIFIER_OFS - IPV4_ICMP_TYPE_CODE_CHECKSUM_LEN, Identifier);        /* SBSW_TCPIP_WRITE_UINT16 */
  TCPIP_PUT_UINT16(&icmpHeaderBytes[0], ICMPV4_HDR_START_SEQNUM_OFS     - IPV4_ICMP_TYPE_CODE_CHECKSUM_LEN, SequenceNumber);    /* SBSW_TCPIP_WRITE_UINT16 */
  return IpV4_Icmp_VSendRawMessage(LocalAddrV4Idx, DestIpAddr, IcmpType, IcmpCode, &icmpHeaderBytes[0], DataPtr, DataLenByte);  /* SBSW_TCPIP_FUNC_CALL_PTR_PASSING_CALLER */ /* SBSW_TCPIP_LOCAL_VARIABLE_PASSED */
} /* IpV4_Icmp_SendEchoMessage() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  IpV4_Icmp_VRxEchoRequest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Icmp_VRxEchoRequest(
  TcpIp_SizeOfLocalAddrV4Type LocalAddrV4Idx,
  IpBase_AddrInType           RemNetAddr,
  IPV4_P2C(uint8)             DataPtr,
  uint16                      DataLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 echoIdentifier;
  uint16 echoSeqNum;
  uint16 echoDataLen;

  /* ----- Implementation ----------------------------------------------- */
  echoIdentifier = TCPIP_GET_UINT16(DataPtr, ICMPV4_HDR_START_IDENTIFIER_OFS - IPV4_ICMP_TYPE_CODE_CHECKSUM_LEN);
  echoSeqNum =     TCPIP_GET_UINT16(DataPtr, ICMPV4_HDR_START_SEQNUM_OFS - IPV4_ICMP_TYPE_CODE_CHECKSUM_LEN);
  /* Substract the rest 4 bytes of header from the data length. */
  echoDataLen = DataLen - (IPV4_ICMP_HEADER_LEN - IPV4_ICMP_TYPE_CODE_CHECKSUM_LEN);

  /* Truncate the data if it is bigger than configured.*/
  if (echoDataLen > TcpIp_GetSizeOfIcmpEchoReplyData())
  {
    echoDataLen = TcpIp_GetSizeOfIcmpEchoReplyData();
  }

  /* #10 Try to send Echo reply directly. */
  if (IpV4_Icmp_SendEchoMessage(LocalAddrV4Idx, RemNetAddr, IPV4_ICMP_TYPE_ECHO_REPLY, 0, echoIdentifier, echoSeqNum, &DataPtr[IPV4_ICMP_IDENT_SEQNUM_LEN], echoDataLen) == BUFREQ_E_BUSY) /* SBSW_TCPIP_FUNC_CALL_PTR_PASSING_CALLER */
  {
    /* #20 Schedule pending reply for next MainFunction, if message cannot be sent directly due to pending link-layer address resolution or because no ethernet buffer is available. */
    IpV4_Icmp_EchoReplyPendingMsg.LocalAddrV4Idx  = LocalAddrV4Idx;
    IpV4_Icmp_EchoReplyPendingMsg.Dest            = RemNetAddr;
    IpV4_Icmp_EchoReplyPendingMsg.Identifier      = echoIdentifier;
    IpV4_Icmp_EchoReplyPendingMsg.SequNum         = echoSeqNum;

    /* copy data that was received with incoming message */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpBase_Copy(TcpIp_GetAddrIcmpEchoReplyData(0), &DataPtr[IPV4_ICMP_IDENT_SEQNUM_LEN], echoDataLen);                  /* SBSW_TCPIP_ICMPV4_IPBASE_COPY_CALLEE */
    IpV4_Icmp_EchoReplyPendingMsg.IpV4_Icmp_EchoReplyDataLen = echoDataLen;
    IpV4_Icmp_EchoReplyPendingMsg.IpV4_Icmp_EchoReplyIsPending = TRUE;
  }
} /* IpV4_Icmp_VRxEchoRequest() */

/**********************************************************************************************************************
 *  IpV4_Icmp_VSendRawMessage
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
TCPIP_LOCAL FUNC(BufReq_ReturnType, IPV4_CODE) IpV4_Icmp_VSendRawMessage(
  TcpIp_LocalAddrV4IterType LocalAddrV4Idx,
  IpBase_AddrInType         DestIpAddr,
  uint8                     Type,
  uint8                     Code,
  IPV4_P2C(uint8)           VarHeaderBytesPtr,
  IPV4_P2C(uint8)           PayloadPtr,
  uint16                    PayloadLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType               retVal;
  TcpIp_IpTxRequestDescriptorType ipTxReqestDescr;
  uint16                          ipPayloadLen = IPV4_ICMP_HEADER_LEN + PayloadLen;
  IPV4_P2V(uint8)                 ipBufPtr;
  uint16                          ipBufLen = ipPayloadLen;
  IpBase_SockAddrInType           destSockAddr;
  TcpIp_LocalAddrV4IterType       localAddrIdx = LocalAddrV4Idx;

  /* ----- Implementation ----------------------------------------------- */
  destSockAddr.sin_family = IPBASE_AF_INET;
  destSockAddr.sin_addr   = DestIpAddr;
  destSockAddr.sin_port   = 0;
# if (TCPIP_SUPPORT_IPSEC == STD_ON)
  /* Store the transport protocol information in the tx descriptor */
  ipTxReqestDescr.XptProtocol = IPV4_IP_PROTOCOL_ICMP;
  ipTxReqestDescr.MessageType = Type;
# endif
  /* #10 Obtain TX buffer from IP.*/
  retVal = IpV4_Ip_ProvideTxBuffer(&localAddrIdx, TcpIp_GetIpV4SocketDynIcmpIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX),
                                   &destSockAddr, &ipBufPtr, &ipBufLen, &ipTxReqestDescr, FALSE);                       /* SBSW_TCPIP_FUNC_CALL_FUNC_PARAM_PASSED */ /* SBSW_TCPIP_LOCAL_VARIABLE_PASSED */

  if (retVal == BUFREQ_OK)
  {
    boolean copyTxData = TRUE;
    uint16  dataRemain = PayloadLen;
    uint16  dataPos    = 0;
    /* #20 Write ICMP message header. */
    /* IPv4 may provide multiple buffers if message exceeds link MTU,
     * but the first buffer will always be large enough for ICMP header.
     */

    /* Write ICMP type and code into message header. */
    ipBufPtr[0] = Type;                                                                                                 /* SBSW_TCPIP_UPDATE_PTR */
    ipBufPtr[1] = Code;                                                                                                 /* SBSW_TCPIP_UPDATE_PTR */

    /* Initialize checksum field. Value will be updated with calculated checksum later. */
    ipBufPtr[2] = 0;                                                                                                    /* SBSW_TCPIP_UPDATE_PTR */
    ipBufPtr[3] = 0;                                                                                                    /* SBSW_TCPIP_UPDATE_PTR */

    /* Write the four message dependent bytes in the ICMP header. */
    ipBufPtr[4] = VarHeaderBytesPtr[0];                                                                                 /* SBSW_TCPIP_UPDATE_PTR */
    ipBufPtr[5] = VarHeaderBytesPtr[1];                                                                                 /* SBSW_TCPIP_UPDATE_PTR */
    ipBufPtr[6] = VarHeaderBytesPtr[2];                                                                                 /* SBSW_TCPIP_UPDATE_PTR */
    ipBufPtr[7] = VarHeaderBytesPtr[3];                                                                                 /* SBSW_TCPIP_UPDATE_PTR */

    /* #30 Copy message payload into IP buffer.*/
    /* Copy message payload into IP buffer.
     * - Iterate over multiple IP buffer fragments if a fragmented IP packet needs to be sent.
     */
    ipBufPtr  = &ipBufPtr[sizeof(IpV4_Icmp_EchoMsgType)];
    ipBufLen -= (uint16) sizeof(IpV4_Icmp_EchoMsgType);
    /* #40 Iterate over multiple IP buffer fragments if a fragmented IP packet needs to be sent.*/
    while ((copyTxData == TRUE) && (dataRemain > 0u))
    {
      if (dataRemain < ipBufLen)
      {
        ipBufLen = dataRemain;
      }

      /* Copy payload. */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpBase_Copy(ipBufPtr, &PayloadPtr[dataPos], ipBufLen);                                                            /* SBSW_TCPIP_ICMPV4_IPBASE_COPY_CALLEE */

      dataRemain -= ipBufLen;
      dataPos    += ipBufLen;

      if (dataRemain > 0u)
      {
        /* #50 Request next buffer fragment. */
        if (IpV4_Ip_FragmentProvideTxBuffer(&ipTxReqestDescr, &ipBufPtr, &ipBufLen) != E_OK)                            /* SBSW_TCPIP_FUNC_CALL_LOCAL_VARIABLE_PTR_CALLER */
        {
          /* ERROR: This should not happen. If IpV4_Ip_ProvideTxBuffer() returns BUFREQ_OK there should be sufficient buffer space. */
          IpV4_ReportDetError(IPV4_IP_API_ID_V_INTERNAL_FUNCTION, IPV4_E_INV_PARAM);
          copyTxData = FALSE;
        }
      }
    }

    /* send message by IP: */
    /* #60 Trigger transmit of IP packet.*/
    if(IpV4_Ip_Transmit(&ipTxReqestDescr, ipPayloadLen, IPV4_IP_PROTOCOL_ICMP, FALSE, 0, FALSE) != E_OK)                /* SBSW_TCPIP_LOCAL_VARIABLE_PASSED */
    {
      /* transmit failed */
      retVal = BUFREQ_E_NOT_OK;
    }
  }

  return retVal;
} /* IpV4_Icmp_VSendRawMessage() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  IpV4_Icmp_VSendPendingEchoReply
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, IPV4_CODE) IpV4_Icmp_VSendPendingEchoReply(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if transmit is possible. If transmit is temporarily not possible, do not clear pending-flag and retry transmit later. */
  if (BUFREQ_E_BUSY != IpV4_Icmp_SendEchoMessage(IpV4_Icmp_EchoReplyPendingMsg.LocalAddrV4Idx,
                                                 IpV4_Icmp_EchoReplyPendingMsg.Dest,
                                                 IPV4_ICMP_TYPE_ECHO_REPLY,
                                                 ICMPV4_REPLY_CODE,
                                                 IpV4_Icmp_EchoReplyPendingMsg.Identifier,
                                                 IpV4_Icmp_EchoReplyPendingMsg.SequNum,
                                                 TcpIp_GetAddrIcmpEchoReplyData(0), /* There is only one IcmpEchoReplyData buffer and 0 is the first elemnet of this array */
                                                 IpV4_Icmp_EchoReplyPendingMsg.IpV4_Icmp_EchoReplyDataLen))             /* SBSW_TCPIP_CSL_TCPIP_GETADDR */
  {
    /* Echo Reply sent or error occurred. No retry required. */
    /* #20 Otherwise: Clear pending-flag. (Pending packet will be dropped if transmit failed due to permanent error. */
    IpV4_Icmp_EchoReplyPendingMsg.IpV4_Icmp_EchoReplyIsPending = FALSE;
  }
  else
  {
     /* Retry later */
  }
} /* IpV4_Icmp_VSendPendingEchoReply() */

# if (TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG == STD_ON)
  /**********************************************************************************************************************
  *  IpV4_Icmp_VSendPendingDestinationUnreachableMsg
  *********************************************************************************************************************/
  /*!
  * Internal comment removed.
 *
 *
 *
  */
STATIC FUNC(void, IPV4_CODE) IpV4_Icmp_VSendPendingDestinationUnreachableMsg(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  const uint8 unusedHeaderBytes[4] = { 0, 0, 0, 0 };

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if transmit is possible. If transmit is temporarily not possible, do not clear pending-flag and retry transmit later. */
  if (IpV4_Icmp_VSendRawMessage(IpV4_Icmp_DestinationUnrechablePendingMsg.LocalAddrV4Idx,
                                IpV4_Icmp_DestinationUnrechablePendingMsg.Dest,
                                IPV4_ICMP_TYPE_DEST_UNRECHABLE, IpV4_Icmp_DestinationUnrechablePendingMsg.Code, &unusedHeaderBytes[0],
                                TcpIp_GetAddrIcmpDestUnreachableMsg(0), /* There is only one IcmpDestUnreachableMsg buffer and 0 is the first elemnet of this array */
                                IpV4_Icmp_DestinationUnrechablePendingMsg.IpV4_Icmp_DestUnreachMsgLen) == BUFREQ_OK)    /* SBSW_TCPIP_CSL_TCPIP_DESTUNREACHABLE_GETADDR */
  {
    /* Destination Unreachable Message sent or error occurred. No retry required. */
    /* #20 Otherwise: Clear pending-flag. (Pending packet will be dropped if transmit failed due to permanent error. */
    IpV4_Icmp_DestinationUnrechablePendingMsg.IpV4_Icmp_DestinationUnreachablePending = FALSE;
  }
  else
  {
    /* Retry later */
  }
} /* IpV4_Icmp_VSendPendingDestinationUnreachableMsg() */
#endif

/**********************************************************************************************************************
 *  IpV4_Icmp_Cbk_VAddrResTimeout
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Icmp_Cbk_VAddrResTimeout(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IpBase_AddrInType      DestAddr)
{
  /* ----- Implementation ----------------------------------------------- */
  IPV4_UNUSED_PARAMETER(IpV4CtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
  /* #10 Verify the Destination address of the message. */
  if (IpV4_Icmp_EchoReplyPendingMsg.Dest == DestAddr)
  {
    /* #20 Cancel ICMP echo reply by reseting the Echo reply pending flag. */
    IpV4_Icmp_EchoReplyPendingMsg.IpV4_Icmp_EchoReplyIsPending = FALSE;
  }
# if (TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG == STD_ON)
  if (IpV4_Icmp_DestinationUnrechablePendingMsg.Dest == DestAddr)
  {
    /* #30 Cancel ICMP destination unreachable msg by reseting the destination unreachable msg pending flag. */
    IpV4_Icmp_DestinationUnrechablePendingMsg.IpV4_Icmp_DestinationUnreachablePending = FALSE;
  }
#endif
} /* IpV4_Icmp_Cbk_VAddrResTimeout() */


/**********************************************************************************************************************
 *  IpV4_Icmp_StoreChecksumInHeader
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Icmp_StoreChecksumInHeader(
  uint16          ChecksumNbo,
  IPV4_P2V(uint8) IcmpHdrPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Store checksum into IcmpHdr buffer. */
  TCPIP_PUT_UINT16_RAW(IcmpHdrPtr, ICMPV4_HDR_START_CHECKSUM_OFS, ChecksumNbo);                                         /* SBSW_TCPIP_WRITE_UINT16 */
} /* IpV4_Icmp_StoreChecksumInHeader() */

/**********************************************************************************************************************
 *  IpV4_Icmp_VLocalIpAddrAssignmentChange()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Icmp_VLocalIpAddrAssignmentChange(
  TcpIp_SizeOfLocalAddrV4Type LocalAddrV4Idx,
  TcpIp_IpAddrStateType       State)
{
  /* ----- Implementation ----------------------------------------------- */
  if (TCPIP_IPADDR_STATE_ASSIGNED != State)
  {
    if (IpV4_Icmp_EchoReplyPendingMsg.LocalAddrV4Idx == LocalAddrV4Idx)
    {
      /* #10 Cancel ICMP echo reply by reseting the Echo reply pending flag, if the Ip address state is not "assigned". */
      IpV4_Icmp_EchoReplyPendingMsg.IpV4_Icmp_EchoReplyIsPending = FALSE;
    }
# if (TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG == STD_ON)
    if (IpV4_Icmp_DestinationUnrechablePendingMsg.LocalAddrV4Idx == LocalAddrV4Idx)
    {
      /* #20 Cancel ICMP destination unreachable msg by reseting the destination unreachable msg pending flag, if the Ip address state is not "assigned". */
      IpV4_Icmp_DestinationUnrechablePendingMsg.IpV4_Icmp_DestinationUnreachablePending = FALSE;
    }
#endif
  }
} /* IpV4_Icmp_VLocalIpAddrAssignmentChange() */

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_TCPIP_LOCAL_VARIABLE_PASSED
    \DESCRIPTION       Variable is passed by reference as a function argument in order to update it.
    \COUNTERMEASURE \N A Local Variable is created inside the local function and passed to the callee function as function argument,

  \ID SBSW_TCPIP_UPDATE_PTR
    \DESCRIPTION       Pointer is updated inside the local function.
                       ipBufPtr is a local pointer and passed to IpV4_Ip_ProvideTxBuffer function in order to validate it.
                       IpV4_Ip_ProvideTxBuffer makes sure that buffer of valid length is provided.
                       If the function returns BUFREQ_OK (that means valid buffer is provided) then only ipBufPtr updated.
                       Thats why it is always valid to update a pointer here.
    \COUNTERMEASURE \N A Local pointer is created inside a local function.

  \ID SBSW_TCPIP_CSL_TCPIP_GETADDR
    \DESCRIPTION       A pointer to ComStackLib generated data is retrieved via TcpIp_GetAddr...() function and passed to the function as a function argument.
                       TcpIp_GetAddrIcmpEchoReplyData(0) references to the array TcpIp_IcmpEchoReplyData. By default there is only one array. It is CSL generated array.
                       IpV4_Icmp_EchoReplyDataLen which is an element of a global structure IpV4_Icmp_EchoReplyPendingMsg,
                       is set as a echoDataLen, after verification against TcpIp_GetSizeOfIcmpEchoReplyData() at a function IpV4_Icmp_VRxEchoRequest and also echo reply pending flag.
                       The function IpV4_Icmp_VSendPendingEchoReply is called only when IpV4_Icmp_EchoReplyIsPending is TRUE.
                       TcpIp_IcmpEchoReplyData buffer and echoDataLen  are related to each other and the buffer must be updated according to valid echoDataLen.
    \COUNTERMEASURE \N Pointer is accessed only if IcmpV4 is configured i.e. valid TcpIp_IcmpEchoReplyData buffer exists. Caller ensures that.

  \ID SBSW_TCPIP_CSL_TCPIP_DESTUNREACHABLE_GETADDR
    \DESCRIPTION       A pointer to ComStackLib generated data is retrieved via TcpIp_GetAddr...() function and passed to the function as a function argument.
                       TcpIp_GetAddrIcmpDestUnreachableMsg(0) references to the array TcpIp_IcmpDestUnreachableMsg. By default there is only one array. It is CSL generated array.
                       IpV4_Icmp_EchoReplyDataLen which is an element of a global structure IpV4_Icmp_DetinationUnreachableMsg,
                       is set as a tp fix value of ipPayloadLen(max 8 bytes + ipHdrLen(fix 20 bytes), after verification of ipPayloadLen against IPV4_ICMP_MAX_ORIGINAL_PAYLOAD_LEN (according to Rfc it must be maximum of 64 bits) at a function IpV4_Icmp_SendDestUnreachable and also Destination unreachable Msg pending flag.
                       The function IpV4_Icmp_VSendPendingDestinationUnreachableMsg is called only when IpV4_Icmp_DestinationUnreachablePending is TRUE.
                       TcpIp_IcmpDestUnreachableMsg buffer and ipPayloadLen are related to each other and the buffer must be updated according to valid ipPayloadLen.
    \COUNTERMEASURE \N Pointer is accessed only if IcmpV4 is configured i.e. valid TcpIp_IcmpDestUnreachableMsg buffer exists. Caller ensures that.

  \ID SBSW_TCPIP_WRITE_UINT16
    \DESCRIPTION       The function writes exactly 2 bytes at the valid offset position in the buffer.
    \COUNTERMEASURE \N Proper size of local array is created inside the local function.

  \ID SBSW_TCPIP_FUNC_CALL_PTR_PASSING_CALLER
    \DESCRIPTION       Pointer is passed as a function argument in order to update it.
                       Pointer is a function argument  and passed to the callee function considering a valid pointer.
                       Pointer is updated as stated in CM_TCPIP_DATAPTR_DATALENGTH
    \COUNTERMEASURE \N The validity of the pointer is ensured by the caller.

  \ID SBSW_TCPIP_FUNC_CALL_RXINDICATION_CALLER
    \DESCRIPTION       Pointer is passed as a function argument in order to update it.
                       Pointer is passed to the function only if the DataLen is valid, otherwise the function returns back to the caller.
                       DataLen must be at least IPV4_ICMP_HEADER_LEN inorder to validate the DataPtr. DataPtr is updated always regarding to the given Datalen.
    \COUNTERMEASURE \N The validity of the pointer is ensured by the caller.

  \ID SBSW_TCPIP_FUNC_CALL_LOCAL_VARIABLE_PTR_CALLER
    \DESCRIPTION       A Local pointers and variables are  passed as a function argument to the callee function.
                       A local pointer is valid as explained in SBSW_TCPIP_UPDATE_PTR
    \COUNTERMEASURE \N A Local pointers and variables are created validated inside the local function before passing to this callee function as function arguments.

  \ID SBSW_TCPIP_ICMPV4_IPBASE_COPY_CALLEE
    \DESCRIPTION       Array is passed to the function to update it.
                       The caller ensures that a valid array of proper size is passed to the callee function.
                       Number of bytes that should be written into the array is also passed to this IpBase_Copy function as one parameter (ipBufLen, (ipPayloadLen + ipHdrLen) or echoDataLen).
                       Length parameter is verified before passing it to the function.
    \COUNTERMEASURE \N The caller ensures that the Proper size of array which points to the valid memory location is passed to the function.

  \ID SBSW_TCPIP_FUNC_CALL_FUNC_PARAM_PASSED
    \DESCRIPTION       A Function argument is passed by reference to the callee function.
    \COUNTERMEASURE \N The caller ensures that variable is a valid parameter.

  \CM CM_TCPIP_DATAPTR_DATALENGTH
                       DataPtr is a pointer which is updated according to given Data length.
                       Data length is verified by the caller before using it or passing it to the callee function in order to update DataPtr.
                       Similarly ipPayloadLen without ipHdrLen is verified against IPV4_ICMP_MAX_ORIGINAL_PAYLOAD_LEN  to limit it according to IETF RFC 792 and then passed to callee function
                       (ipHdrLen + ipPayloadLen) is always less than or equal to data length.

SBSW_JUSTIFICATION_END */

#endif  /* (TCPIP_SUPPORT_ICMPV4 == STD_ON) */
/**********************************************************************************************************************
 *  END OF FILE: IpV4_Icmp.c
 *********************************************************************************************************************/
