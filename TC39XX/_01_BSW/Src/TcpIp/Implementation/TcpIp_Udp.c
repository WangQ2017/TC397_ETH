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
 *         \file  TcpIp_Udp.c
 *        \brief  Implementation of User Datagram Protocol (UDP)
 *
 *      \details  This file is part of the TcpIp module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/


/* PRQA S 0828 EOF */ /* MD_MSR_1.1 */

#define TCPIP_UDP_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIp_Cfg.h"
#include "TcpIp_Udp.h"
#include "TcpIp_Lcfg.h"
#include "TcpIp_Udp_Cbk.h"
#include "TcpIp.h"
#include "TcpIp_Priv.h"
#include "TcpIp_Cbk.h"
#include "IpBase.h"
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# include "TcpIp_IpV4.h"
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# include "TcpIp_IpV6.h"
#endif
#include "IpBase_Copy.h"
#include "IpBase_Sock.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#if !defined (STATIC)                                                                                                   /* COV_TCPIP_COMPATIBILITY */
# define STATIC static
#endif

#define TCPIP_UDP_EMPTY_PORT     0x0000u
#define TCPIP_UDP_EMPTY_CHKSUM   0x0000u

#define TCPIP_UDP_HDR_OFS_SRC_PORT  0u
#define TCPIP_UDP_HDR_OFS_DST_PORT (TCPIP_UDP_HDR_OFS_SRC_PORT + 2u)
#define TCPIP_UDP_HDR_OFS_LENGTH   (TCPIP_UDP_HDR_OFS_DST_PORT + 2u)
#define TCPIP_UDP_HDR_OFS_CHECKSUM (TCPIP_UDP_HDR_OFS_LENGTH   + 2u)
#define TCPIP_UDP_HDR_LENGTH       (TCPIP_UDP_HDR_OFS_CHECKSUM + 2u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
  TcpIp_Udp_RemoveTxReqElemFromReqElemList()
 *********************************************************************************************************************/
/*! \brief      Removes the element at the current read position from the UDP TX request list ring buffer.
 *  \details    -
 *  \param[in]  TxReqElemListIdx    Index of a UDP TX request list.
 *                                  [CONSTRAINT: 0..TcpIp_GetSizeOfTxReqElemList()-1]
 *  \note       -
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        There must be at least one element in the ring buffer.
 *              [CONSTRAINT: TcpIp_GetFillNumOfTxReqElemListDyn(TxReqElemListIdx) > 0]
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_Udp_RemoveTxReqElemFromReqElemList(TcpIp_SizeOfTxReqElemListDynType TxReqElemListIdx);

/**********************************************************************************************************************
 *  TcpIp_Udp_RemoveTxReqElemFromReqElemList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_Udp_RemoveTxReqElemFromReqElemList(TcpIp_SizeOfTxReqElemListDynType TxReqElemListIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TxReqElemListIdx < TcpIp_GetSizeOfTxReqElemList());
  TCPIP_ASSERT(TcpIp_GetReadPosOfTxReqElemListDyn(TxReqElemListIdx) >= TcpIp_GetTxReqElemStartIdxOfTxReqElemList(TxReqElemListIdx));
  TCPIP_ASSERT(TcpIp_GetReadPosOfTxReqElemListDyn(TxReqElemListIdx) <  TcpIp_GetTxReqElemEndIdxOfTxReqElemList(TxReqElemListIdx));
  TCPIP_ASSERT(TcpIp_GetFillNumOfTxReqElemListDyn(TxReqElemListIdx) >  0u);

  /* #10 Set read position to next element of ring buffer considering the wrap-around. */
  TcpIp_IncReadPosOfTxReqElemListDyn(TxReqElemListIdx);                                                                 /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */

  if (TcpIp_GetReadPosOfTxReqElemListDyn(TxReqElemListIdx) == TcpIp_GetTxReqElemEndIdxOfTxReqElemList(TxReqElemListIdx))
  {
    TcpIp_SetReadPosOfTxReqElemListDyn(TxReqElemListIdx, TcpIp_GetTxReqElemStartIdxOfTxReqElemList(TxReqElemListIdx));  /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
  }

  /* #20 Decrease fill level of ring buffer by one. */
  TcpIp_DecFillNumOfTxReqElemListDyn(TxReqElemListIdx);                                                                 /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
}

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if defined(TCPIP_ENABLE_INT_DEBUG_COUNTERS)                                                                            /* COV_TCPIP_CANOE_DEBUG */
STATIC VAR(uint32, TCPIP_VAR_NOINIT) TcpIp_Udp_RxIndCounter;
STATIC VAR(uint32, TCPIP_VAR_NOINIT) TcpIp_Udp_TransmitCounter;
#endif

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
  TcpIp_Udp_VTransmit()
 *********************************************************************************************************************/
/*! \brief      Transmits or queues the transmission of a UDP datagram.
 *  \details    -
 *  \param[in]  IpTxReqDescPtr  Pointer to IP TX descriptor that was provided by IpVX_ProvideTxBuffer().
 *  \param[in]  IpPayloadBufPtr Pointer to Buffer where the UDP header and payload will be written.
 *                              CONSTRAINT: Must point to TCPIP_UDP_HDR_LEN_BYTE + UdpPayloadLen bytes of memory.
 *  \param[in]  UdpPayloadLen   Length of the UDP payload. [bytes]
 *  \param[in]  DestSockAddrPtr Destination IP address and port.
 *  \param[in]  TxReqIdx        TX request index that is passed to the IP layer and will be returned in TX confirmation.
 *  \return     E_OK            UDP datagram transmitted or transmit queued.
 *  \return     E_NOT_OK        Transmit not possible.
 *  \note       The payload of the UDP packet must be written in the provided IP buffer before.
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different IpTxReqDescPtr->SockIdx.
 *  \pre        -
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_VTransmit(
  TCPIP_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr,
  TCPIP_P2V(uint8)                           IpPayloadBufPtr,
  uint16                                     UdpPayloadLen,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          DestSockAddrPtr,
  uint8                                      TxReqIdx);

/**********************************************************************************************************************
 *  TcpIp_Udp_VTxReqListHandleOverflow()
 *********************************************************************************************************************/
/*! \brief      Verifies that there is sufficient space in the TX request table of a socket.
 *  \details    -
 *  \param[in]  SocketUdpIdx Index of a UDP socket.
 *                           CONSTRAINT: [0...TcpIp_GetSizeOfSocketUdpDyn()-1]
 *  \return     E_OK         Appending element to TX request list is possible or no TX request list is required.
 *  \return     E_NOT_OK     TX request list is required and full.
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different SocketUdpIdx.
 *  \pre        -
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_VTxReqListHandleOverflow(
  TcpIp_SocketUdpDynIterType SocketUdpIdx);

/**********************************************************************************************************************
 *  TcpIp_Udp_VValidateChecksum()
 *********************************************************************************************************************/
/*! \brief      Validates the checksum of a received UDP datagram.
 *  \details    -
 *  \param[in]  ReceivedChecksum  Received checksum value that was stored inside the UDP header.
 *  \param[in]  RxSockLocAddrPtr  Destination IP address of the received UDP packet.
 *  \param[in]  RxSockRemAddrPtr  Source IP address of the received UDP packet.
 *  \param[in]  IpPayloadPtr      Payload of the received IP packet (starting with the UDP header).
 *  \param[in]  IpPayloadLen      Length of the IP payload in bytes.
 *  \return     E_OK              Checksum of received UDP datagram matches ReceivedChecksum.
 *  \return     E_NOT_OK          Checksum of received UDP datagram does not match ReceivedChecksum.
 *  \context    ANY
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_VValidateChecksum(
    uint16                            ReceivedChecksum,
    TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
    TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
    TCPIP_P2C(uint8)                  IpPayloadPtr,
    uint16                            IpPayloadLen);

/**********************************************************************************************************************
 *  TcpIp_Udp_VStoreRequestInRetryQueue()
 *********************************************************************************************************************/
/*! \brief          Binds a UDP or TCP socket to a local IP address and port.
 *  \details        -
 *  \param[in]      SocketUdpIdx        Index of a UDP socket.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketUdpDyn()-1]
 *  \param[in]      IpTxReqDescPtr      IP TX descriptor that was provided by IpVX_ProvideTxBuffer().
 *  \param[in]      UdpPayloadLen       Length of the UDP payload. [bytes]
 *  \param[in]      DestSockAddrPtr     IP address and port of the destination.
 *  \param[in]      TxReqIdx            TX request index that is passed to the IP layer and will be returned
 *                                      in TX confirmation.
 *  \return         E_OK                Request successfully stored in retry queue.
 *  \return         E_NOT_OK            Retry queue was full or no retry queue attached to the UDP socket.
 *  \pre            SocketUdpIdx was allocated by <Up>_GetSocket().
 *  \context        TASK
 *  \reentrant      TRUE for different socket IDs.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_VStoreRequestInRetryQueue(
  TcpIp_SocketUdpDynIterType                 SocketUdpIdx,
  TCPIP_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr,
  uint16                                     UdpPayloadLen,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          DestSockAddrPtr,
  uint8                                      TxReqIdx);

/**********************************************************************************************************************
 *  TcpIp_Udp_VMatchingElementInRetryQueue()
 *********************************************************************************************************************/
/*! \brief          Checks if there is already an matching element in the retry queue.
 *  \details        -
 *  \param[in]      SocketUdpIdx        Index of a UDP socket.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketUdpDyn()-1]
 *  \param[in]      DestSockAddrPtr     IP address and port of the destination.
 *  \return         TRUE                Matching element in retry queue.
 *  \return         FALSE               No matching element in retry queue.
 *  \pre            SocketUdpIdx was allocated by <Up>_GetSocket().
 *  \context        TASK
 *  \reentrant      TRUE for different socket IDs.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_Udp_VMatchingElementInRetryQueue(
  TcpIp_SocketUdpDynIterType                 SocketUdpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          DestSockAddrPtr);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_Udp_Init()
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
FUNC(void, TCPIP_CODE) TcpIp_Udp_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketUdpDynIterType  socketUdpIdx;
  TcpIp_TxReqElemListIterType txReqElemListIdx;

  /* ----- Implementation ----------------------------------------------- */
#if defined(TCPIP_ENABLE_INT_DEBUG_COUNTERS)                                                                            /* COV_TCPIP_CANOE_DEBUG */
  /* Debug variables: */
  TcpIp_Udp_RxIndCounter = 0;
  TcpIp_Udp_TransmitCounter = 0;
#endif

  /* #10 Reset UDP dynamic port counter. */
  TcpIp_Udp_DynamicPortCount = 0;

  /* #20 Iterate over all UDP request lists and clear them. */
  for (txReqElemListIdx = 0; txReqElemListIdx < TcpIp_GetSizeOfTxReqElemList(); txReqElemListIdx++)
  {
    TcpIp_SetFillNumOfTxReqElemListDyn(txReqElemListIdx, 0);                                                            /* SBSW_TCPIP_CslIteration */
    TcpIp_SetWritePosOfTxReqElemListDyn(txReqElemListIdx, TcpIp_GetTxReqElemStartIdxOfTxReqElemList(txReqElemListIdx)); /* SBSW_TCPIP_CslIteration */
    TcpIp_SetReadPosOfTxReqElemListDyn(txReqElemListIdx,  TcpIp_GetTxReqElemStartIdxOfTxReqElemList(txReqElemListIdx)); /* SBSW_TCPIP_CslIteration */
    TcpIp_SetSocketUdpDynIdxOfTxReqElemListDyn(txReqElemListIdx, TCPIP_NO_SOCKETUDPDYNIDXOFTXREQELEMLISTDYN);           /* SBSW_TCPIP_CslIteration */
  }

  /* #30 Clear retry queue. */
  if (TcpIp_GetSizeOfUdpTxRetryQueueElements() > 0u)
  {
    TCPIP_ASSERT(TcpIp_HasUdpTxRetryQueuePoolDesc());
    TCPIP_ASSERT(TcpIp_HasUdpTxRetryQueueElementChain());
    TcpIp_DListInitDesc(TcpIp_GetAddrUdpTxRetryQueuePoolDesc(TCPIP_UDP_TX_RETRY_QUEUE_POOL_IDX),                      /* SBSW_TCPIP_DListInitDesc */
      TcpIp_GetAddrUdpTxRetryQueueElementChain(0),
      TcpIp_GetSizeOfUdpTxRetryQueueElements());
  }
  else
  {
    TCPIP_ASSERT(!TcpIp_HasUdpTxRetryQueuePoolDesc());
    TCPIP_ASSERT(!TcpIp_HasUdpTxRetryQueueElementChain());
  }

  /* #40 Iterate over all UDP sockets. */
  for (socketUdpIdx = 0; socketUdpIdx < TcpIp_GetSizeOfSocketUdpDyn(); socketUdpIdx++)
  {
    /* #50 Unassign TX request list. */
    TcpIp_SetTxReqElemListIdxOfSocketUdpDyn(socketUdpIdx, TCPIP_NO_TXREQELEMLISTIDXOFSOCKETUDPDYN);                     /* SBSW_TCPIP_CslIteration */

    TcpIp_DListInit(TcpIp_GetAddrTxRetrQueueOfSocketUdpDyn(socketUdpIdx),                                               /* SBSW_TCPIP_DListInit */
      TcpIp_GetAddrUdpTxRetryQueuePoolDesc(TCPIP_UDP_TX_RETRY_QUEUE_POOL_IDX));

    /* By default a socket may use all available retry queue elements. The limit may be changed or disabled using TcpIp_ChangeParameter() later. */
    TcpIp_SetTxRetrQueueMaxNumOfSocketUdpDyn(socketUdpIdx, TcpIp_GetSizeOfUdpTxRetryQueueElements());                   /* SBSW_TCPIP_CslIteration */
  }
} /* TcpIp_Udp_Init() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_Udp_CloseSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Udp_CloseSocket(
  TcpIp_SocketUdpDynIterType SocketUdpIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TxReqElemListDynIterType txReqElemListIdx;
  TCPIP_P2V(TcpIp_DListType)     rxRetryQueuePtr;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketUdpIdx < TcpIp_GetSizeOfSocketUdpDyn());

  /* #10 Clear TX request list. */
  txReqElemListIdx = TcpIp_GetTxReqElemListIdxOfSocketUdpDyn(SocketUdpIdx);

  if (txReqElemListIdx < TcpIp_GetSizeOfTxReqElemList())  /* TxConfirmation is enabled */
  {
    /* reset variables */
    TcpIp_SetFillNumOfTxReqElemListDyn(txReqElemListIdx, 0);                                                            /* SBSW_TCPIP_CSL_IDX_CHECKED */
    TcpIp_SetWritePosOfTxReqElemListDyn(txReqElemListIdx, TcpIp_GetTxReqElemStartIdxOfTxReqElemList(txReqElemListIdx)); /* SBSW_TCPIP_CSL_IDX_CHECKED */
    TcpIp_SetReadPosOfTxReqElemListDyn(txReqElemListIdx,  TcpIp_GetTxReqElemStartIdxOfTxReqElemList(txReqElemListIdx)); /* SBSW_TCPIP_CSL_IDX_CHECKED */
    TcpIp_SetSocketUdpDynIdxOfTxReqElemListDyn(txReqElemListIdx, TCPIP_NO_SOCKETUDPDYNIDXOFTXREQELEMLISTDYN);           /* SBSW_TCPIP_CSL_IDX_CHECKED */

    TcpIp_SetTxReqElemListIdxOfSocketUdpDyn(SocketUdpIdx, TCPIP_NO_TXREQELEMLISTIDXOFSOCKETUDPDYN);                     /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
  }
  else
  {
    /* nothing to do */
    TCPIP_ASSERT(txReqElemListIdx == TCPIP_NO_TXREQELEMLISTIDXOFSOCKETUDPDYN);
  }

  /* #20 Clear TX retry queue. */
  rxRetryQueuePtr = TcpIp_GetAddrTxRetrQueueOfSocketUdpDyn(SocketUdpIdx);

  if (!TCPIP_DLIST_IS_EMPTY(*rxRetryQueuePtr))
  {
    /* cancel transmit of all retry elements for this socket (release ethernet buffers) */
    TcpIp_DListIdxType listIdx = rxRetryQueuePtr->FirstIdx;

    TCPIP_ASSERT(rxRetryQueuePtr->ElementCount > 0u);

    while (listIdx != TCPIP_DLIST_END_IDX)
    {
      TCPIP_ASSERT(TcpIp_GetAddrUdpTxRetryQueueElements(listIdx)->IpTxRequestDesc.AddressFamily ==
                   TcpIp_GetAddrUdpTxRetryQueueElements(listIdx)->Destination.sa_family);

      TCPIP_ASSERT(listIdx < TcpIp_GetSizeOfUdpTxRetryQueueElements());

      TcpIp_VIpTransmitCancel(&TcpIp_GetAddrUdpTxRetryQueueElements(listIdx)->IpTxRequestDesc, 0, TCPIP_PROTOCOL_UDP);  /* SBSW_TCPIP_ConstPtr */

      TCPIP_DLIST_SET_NEXT(listIdx, TcpIp_GetTxRetrQueueOfSocketUdpDyn(SocketUdpIdx));
    }

    TcpIp_DListClear(rxRetryQueuePtr);                                                                                  /* SBSW_TCPIP_DListClear */
  }
  else
  {
    TCPIP_ASSERT(rxRetryQueuePtr->ElementCount == 0u);
  }

  /* By default a socket may use all available retry queue elements. The limit may be changed or disabled using TcpIp_ChangeParameter() later. */
  TcpIp_SetTxRetrQueueMaxNumOfSocketUdpDyn(SocketUdpIdx, TcpIp_GetSizeOfUdpTxRetryQueueElements());                     /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
}  /* TcpIp_Udp_CloseSocket */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_Udp_RxIndication()
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
FUNC(TcpIp_Udp_ReturnType, TCPIP_CODE) TcpIp_Udp_RxIndication(
    TcpIp_LocalAddrIterType           LocalAddrIdx,
    TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
    TCPIP_P2V(uint8)                  IpPayloadPtr,
    uint16                            IpPayloadLen,
    boolean                           ChecksumValidated)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_Udp_ReturnType retVal = TCPIP_UDP_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrIdx     <  TcpIp_GetSizeOfLocalAddr());
  TCPIP_ASSERT(RxSockRemAddrPtr != NULL_PTR);
  TCPIP_ASSERT(IpPayloadPtr     != NULL_PTR);

#if defined(TCPIP_ENABLE_INT_DEBUG_COUNTERS)                                                                            /* COV_TCPIP_CANOE_DEBUG */
  /* Debug variable: */
  TcpIp_Udp_RxIndCounter++;
#endif

  /* #10 Check that UDP header is complete. */
  if (IpPayloadLen >= TCPIP_UDP_HDR_LEN_BYTE)
  {
    IpBase_PortType srcPort       = TCPIP_GET_UINT16(IpPayloadPtr, TCPIP_UDP_HDR_OFS_SRC_PORT);
    IpBase_PortType dstPort       = TCPIP_GET_UINT16(IpPayloadPtr, TCPIP_UDP_HDR_OFS_DST_PORT);
    uint16          udpHdrLenByte = TCPIP_GET_UINT16(IpPayloadPtr, TCPIP_UDP_HDR_OFS_LENGTH);
    uint16          checksum      = TCPIP_GET_UINT16(IpPayloadPtr, TCPIP_UDP_HDR_OFS_CHECKSUM);

    /* #20 Check that value of length field inside UDP header is valid. */
    if ((udpHdrLenByte >= TCPIP_UDP_HDR_LEN_BYTE) && (udpHdrLenByte <= IpPayloadLen))
    {
      TcpIp_SockAddrBaseType rxSockLocAddr;  /* PRQA S 0759 */ /* MD_MSR_Union */

      /* #30 Retrieve source IP address of UDP datagram from IP layer. */
      if (TcpIp_GetIpAddr(TCPIP_LOCAL_ADDR_IDX_TO_ID(LocalAddrIdx), &(rxSockLocAddr.TcpIpSockAddr), NULL_PTR, NULL_PTR) == E_OK) /* SBSW_TCPIP_GetIpAddr */
      {
        /* #40 Validate checksum of UDP header if not already done by lower layer (hardware). */
        if ((ChecksumValidated == TRUE) ||  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
            (TcpIp_Udp_VValidateChecksum(TCPIP_HTONS(checksum), &rxSockLocAddr, RxSockRemAddrPtr, IpPayloadPtr, udpHdrLenByte) == E_OK)) /* SBSW_TCPIP_Udp_VValidateChecksum */
        {
          TcpIp_SocketDynIterType socketIdx;
          TcpIp_SockAddrBaseType  rxSockRemAddr;  /* PRQA S 0759 */ /* MD_MSR_Union */

          (void)IpBase_CopySockAddr(&rxSockRemAddr.SockAddr, &RxSockRemAddrPtr->SockAddr);                              /* SBSW_TCPIP_IpBase_CopySockAddr_2 */
          rxSockRemAddr.DomainAndPort.port = TCPIP_HTONS(srcPort);
          rxSockLocAddr.DomainAndPort.port = TCPIP_HTONS(dstPort);

          /* #50 Identify matching socket based on destination IP address and port of datagram. */
          socketIdx = TcpIp_VRxUdpSockIdxIdent(&rxSockLocAddr, LocalAddrIdx);  /* Identify socket */                    /* SBSW_TCPIP_PtrToLocalVariable */

          /* #60 Pass datagram to owner of the identified socket. */
          if (socketIdx < TcpIp_GetSizeOfSocketDyn())
          {
            uint16 udpPayloadLen = (uint16)(IpPayloadLen - TCPIP_UDP_HDR_LEN_BYTE);

            TcpIp_RxIndicationFunctions(socketIdx, &rxSockRemAddr, &IpPayloadPtr[TCPIP_UDP_HDR_LENGTH], udpPayloadLen);  /* SBSW_TCPIP_RxIndicationFunctions */
            retVal = TCPIP_UDP_OK;
          }
          /* #70 Otherwise: Indicate (via retVal) that no matching socket was found. */
          else
          {
            /* there is no corresponding socket found -> drop message, or send ICMP message */
            /* Increment the measurement data counter for dropped UDP message (due not mapped valid LocalIp and Port) */
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
            TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_DROP_UDP);
#endif
            retVal = TCPIP_UDP_E_NO_MATCHING_SOCKET;
          }
        }
      }
    }
  }

#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
  if(retVal != TCPIP_UDP_OK)
  {
    /* Packet dropped due to invalid UDP packet format or invalid ports or invalid checksum */
    TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER4);
  }
#endif

  return retVal;
}  /* PRQA S 6080, 6050 */ /* MD_MSR_STMIF, MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_Udp_VTxReqListHandleOverflow()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_VTxReqListHandleOverflow(
  TcpIp_SocketUdpDynIterType SocketUdpIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if TX confirmation is enabled for the socket. */
  if (TcpIp_GetTxReqElemListIdxOfSocketUdpDyn(SocketUdpIdx) != TCPIP_NO_TXREQELEMLISTIDXOFSOCKETUDPDYN)
  {
    TcpIp_SizeOfTxReqElemListDynType txReqElemListIdx = TcpIp_GetTxReqElemListIdxOfSocketUdpDyn(SocketUdpIdx);

    /* #20 Check and if there is enough space in TX request list. */
    if (TcpIp_GetFillNumOfTxReqElemListDyn(txReqElemListIdx) == TcpIp_GetTxReqElemLengthOfTxReqElemList(txReqElemListIdx))
    {
      /* TcpIp_Udp_TxReqList is full */
      retVal = E_NOT_OK;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_Udp_RequestTxBuffer()
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
FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_Udp_RequestTxBuffer(
  TcpIp_SocketUdpDynIterType         SocketUdpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)  DestinationPtr,
  TCPIP_P2V(uint8)                  *BufPtr,
  TCPIP_P2V(uint16)                  BufLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType       bufRetValue;
  boolean                 forceProvidePuffer;
  TcpIp_SocketDynIterType socketIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TCPIP_SOCKET_IDX_IS_UDP(SocketUdpIdx));
  TCPIP_ASSERT(DestinationPtr != NULL_PTR);
  TCPIP_ASSERT(BufPtr    != NULL_PTR);
  TCPIP_ASSERT(BufLenPtr != NULL_PTR);

  socketIdx = TCPIP_UDP_IDX_TO_SOCKET_IDX(SocketUdpIdx);

  /* #10 Check if there is sufficient space in the TX request list, if TX confirmation is enabled for the socket.  */
  if (TcpIp_Udp_VTxReqListHandleOverflow(SocketUdpIdx) == E_OK)
  {
    /* there is a valid free request table element available */
    /* -> check if IP can provide a buffer / has already resolved the address */
    uint16           ipBufferLen = (*BufLenPtr) + TCPIP_UDP_HDR_LEN_BYTE;
    TCPIP_P2V(uint8) ipBufferPtr = NULL_PTR;

    /* #20 Notify IP layer that it shall provide a buffer even if link-layer address resolution is incomplete,
           if the socket uses a retry queue. */
    if (TcpIp_GetTxRetrQueueMaxNumOfSocketUdpDyn(SocketUdpIdx) > 0u)
    {
      forceProvidePuffer = TRUE;
    }
    else
    {
      forceProvidePuffer = FALSE;
    }

    /* #30 Get TX buffer from IP layer. */
    switch (DestinationPtr->sa_family)
    {
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
    case IPBASE_AF_INET:
      {
        TcpIp_LocalAddrV4IterType ipV4AddrIdx = TcpIp_GetTxIpAddrIdxOfSocketDyn(socketIdx);
# if (TCPIP_SUPPORT_IPSEC == STD_ON)
        /* Store the transport protocol information in the tx descriptor */
        TcpIp_GetAddrIpTxRequestDescriptorOfSocketUdpDyn(SocketUdpIdx)->XptProtocol = IPV4_IP_PROTOCOL_UDP;             /* SBSW_TCPIP_CSL_IDX_CHECKED */
# endif
        bufRetValue = IpV4_Ip_ProvideTxBuffer(&ipV4AddrIdx, socketIdx, &DestinationPtr->SockAddrIn,                     /* SBSW_TCPIP_Ip_ProvideTxBuffer */
                        &ipBufferPtr, &ipBufferLen,
                        TcpIp_GetAddrIpTxRequestDescriptorOfSocketUdpDyn(SocketUdpIdx), forceProvidePuffer);

        break;
      }
#endif

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
    case IPBASE_AF_INET6:
      {
        TcpIp_LocalAddrV6IterType ipV6AddrIdx = TcpIp_GetTxIpAddrIdxOfSocketDyn(socketIdx);

        bufRetValue = IpV6_ProvideTxBuffer(&ipV6AddrIdx, socketIdx, &DestinationPtr->SockAddrIn6.sin6_addr,             /* SBSW_TCPIP_Ip_ProvideTxBuffer */
                        &ipBufferPtr, &ipBufferLen,
                        TcpIp_GetAddrIpTxRequestDescriptorOfSocketUdpDyn(SocketUdpIdx), forceProvidePuffer);

        break;
      }
#endif

    default:
      {
        /* invalid address family */
        bufRetValue = BUFREQ_E_NOT_OK;
        break;
      }
    }

    /* #40 Update output parameters and socket variables. */
    if (ipBufferPtr != NULL_PTR)
    {
      (*BufPtr)     = &ipBufferPtr[TCPIP_UDP_HDR_LEN_BYTE];                                                             /* SBSW_TCPIP_NonNullPtrParameter */
      (*BufLenPtr)  = (uint16)(ipBufferLen - TCPIP_UDP_HDR_LEN_BYTE);                                                   /* SBSW_TCPIP_NonNullPtrParameter */

      TcpIp_SetTxReqIpBufPtrOfSocketUdpDyn(SocketUdpIdx, ipBufferPtr);                                                  /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
    }
  }
  else
  {
    bufRetValue = BUFREQ_E_BUSY;
  }

  return bufRetValue;
}  /* TcpIp_Udp_RequestTxBuffer */

/**********************************************************************************************************************
 *  TcpIp_Udp_FragmentRequestTxBuffer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_FragmentRequestTxBuffer(
  TcpIp_SocketUdpDynIterType  SocketUdpIdx,
  IpBase_FamilyType           AddrFamily,
  TCPIP_P2V(uint8)           *BufPtrPtr,
  TCPIP_P2V(uint16)           BufLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
  if (AddrFamily == IPBASE_AF_INET)
  {
    retVal = IpV4_Ip_FragmentProvideTxBuffer(TcpIp_GetAddrIpTxRequestDescriptorOfSocketUdpDyn(SocketUdpIdx),            /* SBSW_Ip_FragmentProvideTxBuffer */
      BufPtrPtr, BufLenPtr);
  }
  else
#else
  TCPIP_UNUSED_PARAMETER(AddrFamily);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
  {
    /* PRQA S 3112 3 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    TCPIP_UNUSED_PARAMETER(SocketUdpIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    TCPIP_UNUSED_PARAMETER(BufPtrPtr);     /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    TCPIP_UNUSED_PARAMETER(BufLenPtr);     /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

    /* Only IPv4 does provide multiple buffer fragments. */
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_Udp_FragmentRequestTxBuffer() */

/**********************************************************************************************************************
 *  TcpIp_Udp_TransmitCancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Udp_TransmitCancel(
  TcpIp_SocketUdpDynIterType SocketUdpIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_VIpTransmitCancel(TcpIp_GetAddrIpTxRequestDescriptorOfSocketUdpDyn(SocketUdpIdx), 0, TCPIP_PROTOCOL_UDP);       /* SBSW_TCPIP_GetAddrUsingCslIdxFromCaller */
}

/**********************************************************************************************************************
 *  TcpIp_Udp_Transmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_Transmit(
  TcpIp_SocketUdpDynIterType        SocketUdpIdx,
  uint16                            UdpPayloadLen,
  TCPIP_P2C(TcpIp_SockAddrBaseType) DestSockAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal;
  TcpIp_SizeOfTxReqElemType     txReqElemIdx;
  TcpIp_SizeOfTxReqElemListType txReqElemListIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TCPIP_SOCKET_IDX_IS_UDP(SocketUdpIdx));

#if defined(TCPIP_ENABLE_INT_DEBUG_COUNTERS)                                                                            /* COV_TCPIP_CANOE_DEBUG */
  TcpIp_Udp_TransmitCounter++;  /* for debugging purposes only */
#endif

  /* #10 Prepare entry in TX request list, if TxConfirmation is configured. */
  TCPIP_VENTER_CRITICAL_SECTION();

  txReqElemListIdx = TcpIp_GetTxReqElemListIdxOfSocketUdpDyn(SocketUdpIdx);

  if (txReqElemListIdx < TcpIp_GetSizeOfTxReqElemList())  /* TxConfirmation is enabled */
  {
    /* take free TcpIp_Udp_TxReqList element. */
    txReqElemIdx = TcpIp_GetWritePosOfTxReqElemListDyn(txReqElemListIdx);

    TCPIP_ASSERT(txReqElemIdx >= TcpIp_GetTxReqElemStartIdxOfTxReqElemList(txReqElemListIdx));
    TCPIP_ASSERT(txReqElemIdx  < TcpIp_GetTxReqElemEndIdxOfTxReqElemList(txReqElemListIdx));

    /* fill TxReqList element */
    TcpIp_SetTxReqElemDataLenByteOfTxReqElem(txReqElemIdx, UdpPayloadLen);                                              /* SBSW_TCPIP_WritePosOfTxReqElemListDyn */
    TcpIp_SetTxReqElemTransmittedOfTxReqElem(txReqElemIdx, FALSE);                                                      /* SBSW_TCPIP_WritePosOfTxReqElemListDyn */
  }
  else
  {
    TCPIP_ASSERT(txReqElemListIdx == TCPIP_NO_TXREQELEMLISTIDXOFSOCKETUDPDYN);
    txReqElemIdx = 0; /* avoid compiler warning about uninitialized variable. */
  }

  TCPIP_VLEAVE_CRITICAL_SECTION();

  /* #20 Send UDP message. */
  retVal = TcpIp_Udp_VTransmit(TcpIp_GetAddrIpTxRequestDescriptorOfSocketUdpDyn(SocketUdpIdx),                          /* SBSW_TCPIP_Udp_VTransmit */
    TcpIp_GetTxReqIpBufPtrOfSocketUdpDyn(SocketUdpIdx), UdpPayloadLen, DestSockAddrPtr, txReqElemIdx);

  /* #30 Update entry in TX request list, if TxConfirmation is configured. */
  if (txReqElemListIdx < TcpIp_GetSizeOfTxReqElemList())
  {
    if (retVal == E_OK)
    {
      TCPIP_VENTER_CRITICAL_SECTION();

      /* update list variables */
      TcpIp_IncWritePosOfTxReqElemListDyn(txReqElemListIdx);                                                            /* SBSW_TCPIP_CSL_IDX_CHECKED */

      if (TcpIp_GetWritePosOfTxReqElemListDyn(txReqElemListIdx) == TcpIp_GetTxReqElemEndIdxOfTxReqElemList(txReqElemListIdx))
      {
        TcpIp_SetWritePosOfTxReqElemListDyn(txReqElemListIdx, TcpIp_GetTxReqElemStartIdxOfTxReqElemList(txReqElemListIdx)); /* SBSW_TCPIP_CSL_IDX_CHECKED */
      }

      TcpIp_IncFillNumOfTxReqElemListDyn(txReqElemListIdx);                                                             /* SBSW_TCPIP_CSL_IDX_CHECKED */

      TCPIP_VLEAVE_CRITICAL_SECTION();
    }
    else
    {
      /* empty TxReqList element */
      TCPIP_ASSERT(txReqElemListIdx == TCPIP_NO_TXREQELEMLISTIDXOFSOCKETUDPDYN);
      TcpIp_SetTxReqElemDataLenByteOfTxReqElem(txReqElemIdx, 0);                                                        /* SBSW_TCPIP_CSL_IDX_CHECKED */
    }
  }

  return retVal;
}  /* TcpIp_Udp_Transmit() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_Udp_TxConfirmation()
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
FUNC(void, TCPIP_CODE) TcpIp_Udp_TxConfirmation(
  TcpIp_SocketUdpDynIterType SocketUdpIdx,
  uint8                      TxReqElemIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTxReqElemListDynType txReqElemListIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketUdpIdx < TcpIp_GetSizeOfSocketUdpDyn());

  txReqElemListIdx = TcpIp_GetTxReqElemListIdxOfSocketUdpDyn(SocketUdpIdx);

  /* #10 Check if a TX request list is assigned to the UDP socket. */
  if (txReqElemListIdx < TcpIp_GetSizeOfTxReqElemList())  /* TxConfirmation is enabled */
  {
    /* #20 Check if TxReqElemIdx is first element of TX request list. */
    if (TcpIp_GetReadPosOfTxReqElemListDyn(txReqElemListIdx) == TxReqElemIdx)
    {
      /* #30 Call TxConfirmation of the socket owner. */
      TcpIp_VSockTxConfirmation(SocketUdpIdx, TcpIp_GetTxReqElemDataLenByteOfTxReqElem(TxReqElemIdx));
      TcpIp_SetTxReqElemDataLenByteOfTxReqElem(TxReqElemIdx, 0);                                                        /* SBSW_TCPIP_CSL_IDX_CHECKED */

      TCPIP_VENTER_CRITICAL_SECTION();

      /* #40 Remove element from TX reqiest list. */
      TcpIp_Udp_RemoveTxReqElemFromReqElemList(txReqElemListIdx);

      TCPIP_VLEAVE_CRITICAL_SECTION();
    }
    /* #50 Otherwise: Mark element for later confirmation. */
    else
    {
      TcpIp_SetTxReqElemTransmittedOfTxReqElem(TxReqElemIdx, TRUE);                                                     /* SBSW_TCPIP_CSL_IDX_CHECKED */
    }
  }
  else
  {
    TCPIP_ASSERT(txReqElemListIdx == TCPIP_NO_TXREQELEMLISTIDXOFSOCKETUDPDYN);
  }
}  /* TcpIp_Udp_TxConfirmation() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_Udp_MainFunctionRx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Udp_MainFunctionRx(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketUdpDynIterType socketUdpIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all UDP sockets. */
  for (socketUdpIdx = 0; socketUdpIdx < TcpIp_GetSizeOfSocketUdpDyn(); socketUdpIdx++)
  {
    /* #20 Iterate over the entries in the TxReqList of the socket, if socket uses optional TxConfirmation feature. */
    TcpIp_SizeOfTxReqElemListType txReqElemListIdx = TcpIp_GetTxReqElemListIdxOfSocketUdpDyn(socketUdpIdx);

    boolean issueTxConf = (boolean)(txReqElemListIdx < TcpIp_GetSizeOfTxReqElemList());  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

    while (issueTxConf == TRUE)  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    {
      TCPIP_VENTER_CRITICAL_SECTION();

      /* #30 Remove entry from the ReqList, if transmission of request has been confirmed. */
      if (TcpIp_GetFillNumOfTxReqElemListDyn(txReqElemListIdx) > 0u)
      {
        TcpIp_SizeOfTxReqElemType txReqElemIdx = TcpIp_GetReadPosOfTxReqElemListDyn(txReqElemListIdx);
        uint16                    txConfLen    = TcpIp_GetTxReqElemDataLenByteOfTxReqElem(txReqElemIdx);

        if (TcpIp_IsTxReqElemTransmittedOfTxReqElem(txReqElemIdx) == TRUE)
        {
          /* inc ReadPos */
          TcpIp_Udp_RemoveTxReqElemFromReqElemList(txReqElemListIdx);
        }
        else
        {
          issueTxConf = FALSE;
        }

        if (issueTxConf == TRUE)
        {
          /* #40 Forward TxConfirmation to TcpIpSocketOwner. */
          TCPIP_VLEAVE_CRITICAL_SECTION(); /* upper layer must not be called within critical section. */
          TcpIp_VSockTxConfirmation(socketUdpIdx, txConfLen);
        }
        else
        {
          /* no pending element at the start of the list */
          issueTxConf = FALSE;
          TCPIP_VLEAVE_CRITICAL_SECTION();
        }
      }
      else
      {
        /* no list element available */
        issueTxConf = FALSE;
        TCPIP_VLEAVE_CRITICAL_SECTION();
      }
    }
  }
} /* TcpIp_Udp_MainFunctionRx() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 * TcpIp_Udp_MainFunctionTx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Udp_MainFunctionTx(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketUdpDynIterType socketUdpIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to send UDP packets that have been queued because link-layer address resolution was not completed. */
  for (socketUdpIdx = 0; socketUdpIdx < TcpIp_GetSizeOfSocketUdpDyn(); socketUdpIdx++)
  {
    TcpIp_Udp_SendRetryQueueIfPossible(socketUdpIdx);
  }
} /* TcpIp_Udp_MainFunctionTx() */

/**********************************************************************************************************************
 *  TcpIp_Udp_ResetSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Udp_ResetSocket(TcpIp_SocketUdpDynIterType SocketUdpIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketDynIterType         socketIdx = TCPIP_UDP_IDX_TO_SOCKET_IDX(SocketUdpIdx);
  TcpIp_SocketOwnerConfigIterType socketOwnerCfgIdx;

  /* ----- Implementation ----------------------------------------------- */
  socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(socketIdx);

  TCPIP_ASSERT(TCPIP_SOCKET_IDX_IS_UDP(socketIdx));
  TCPIP_ASSERT(socketOwnerCfgIdx < TcpIp_GetSizeOfSocketOwnerConfig());

  /* #10 Call TcpIp_Udp_CloseSocket(). */
  TcpIp_Udp_CloseSocket(SocketUdpIdx);

  /* #20 Call TcpIp_TcpIpEvent(TCPIP_UDP_CLOSED) of socket owner. */
  TcpIp_TcpIpEventFunctions(socketOwnerCfgIdx, socketIdx, TCPIP_UDP_CLOSED);
}

/**********************************************************************************************************************
 *  TcpIp_Udp_SetSockOpt()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_SetSockOpt(
  TcpIp_SocketUdpDynIterType                 SocketUdpIdx,
  TcpIp_ParamIdType                          ParameterId,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) ParameterValuePtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TCPIP_SOCKET_IDX_IS_UDP(SocketUdpIdx));

  switch(ParameterId)
  {
  case TCPIP_PARAMID_V_UDP_TXREQLISTSIZE:
    {
      uint8 RequestedListSize = *ParameterValuePtr;
      TcpIp_TxReqElemListDynIterType txReqElemListIdx;

      /* choose a matching rx buffer and assign it to the socket / TCP connection */
      for (txReqElemListIdx = 0; txReqElemListIdx < TcpIp_GetSizeOfTxReqElemList(); txReqElemListIdx++)
      {
        if (   (TcpIp_GetSocketUdpDynIdxOfTxReqElemListDyn(txReqElemListIdx) == TCPIP_NO_SOCKETUDPDYNIDXOFTXREQELEMLISTDYN)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
            && (RequestedListSize == TcpIp_GetTxReqElemLengthOfTxReqElemList(txReqElemListIdx)))
        {
          /* found a free and matching TxReqList */
          TcpIp_SetSocketUdpDynIdxOfTxReqElemListDyn(txReqElemListIdx, (TcpIp_SizeOfSocketDynType)SocketUdpIdx);        /* SBSW_TCPIP_CslIteration */
          TcpIp_SetTxReqElemListIdxOfSocketUdpDyn(SocketUdpIdx, (TcpIp_SizeOfTxReqElemListDynType)txReqElemListIdx);    /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
          retVal = E_OK;
          break;  /* stop the for-loop */
        }
      }
      break;
    }

  case TCPIP_PARAMID_V_UDP_TXRETRYLISTSIZE:
    {
      /* set the maximum number of Eth tx buffers used for buffering messages in case the remote address is not yet resolved */
      uint8 RetryListSizeMax = *ParameterValuePtr;
      if (RetryListSizeMax <= TcpIp_GetSizeOfUdpTxRetryQueueElements())
      {
        TcpIp_SetTxRetrQueueMaxNumOfSocketUdpDyn(SocketUdpIdx, RetryListSizeMax);                                       /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
        retVal = E_OK;
      }
      break;
    }

  default:
    {
      /* error, do nothing */
      TCPIP_UNUSED_PARAMETER(ParameterValuePtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      break;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_Udp_VTransmit()
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_VTransmit(
  TCPIP_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr,
  TCPIP_P2V(uint8)                           IpPayloadBufPtr,
  uint16                                     UdpPayloadLen,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          DestSockAddrPtr,
  uint8                                      TxReqIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16                            ipTransmitLength = UdpPayloadLen + TCPIP_UDP_HDR_LEN_BYTE;
  Std_ReturnType                    retVal;
  TcpIp_ReturnType                  transmitRetVal;
  TcpIp_SocketUdpDynIterType        socketUdpIdx;
  uint8                             ipTransmitFlags = 0;
  TCPIP_P2C(TcpIp_SockAddrBaseType) locSockAddrPtr;
  TcpIp_SocketDynIterType sockIdx = IpTxReqDescPtr->SockIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpTxReqDescPtr  != NULL_PTR);
  TCPIP_ASSERT(IpPayloadBufPtr != NULL_PTR);
  TCPIP_ASSERT(DestSockAddrPtr != NULL_PTR);
  TCPIP_ASSERT(TCPIP_SOCKET_IDX_IS_UDP(sockIdx));

  socketUdpIdx = TCPIP_SOCKET_IDX_TO_UDP_IDX(sockIdx);
  locSockAddrPtr = TcpIp_GetAddrLocSockOfSocketDyn(sockIdx);

  /* #10 Write UDP header. */
  TCPIP_PUT_UINT16_RAW(IpPayloadBufPtr, TCPIP_UDP_HDR_OFS_SRC_PORT, locSockAddrPtr->DomainAndPort.port);                /* SBSW_TCPIP_WriteUdpHeader */
  TCPIP_PUT_UINT16_RAW(IpPayloadBufPtr, TCPIP_UDP_HDR_OFS_DST_PORT, DestSockAddrPtr->DomainAndPort.port);               /* SBSW_TCPIP_WriteUdpHeader */
  TCPIP_PUT_UINT16(IpPayloadBufPtr,     TCPIP_UDP_HDR_OFS_LENGTH,   ipTransmitLength);                                  /* SBSW_TCPIP_WriteUdpHeader */
  TCPIP_PUT_UINT16(IpPayloadBufPtr,     TCPIP_UDP_HDR_OFS_CHECKSUM, TCPIP_UDP_EMPTY_CHKSUM);                            /* SBSW_TCPIP_WriteUdpHeader */

  if (TcpIp_GetTxReqElemListIdxOfSocketUdpDyn(socketUdpIdx) != TCPIP_NO_TXREQELEMLISTIDXOFSOCKETUDPDYN)
  {
    TCPIP_ASSERT(TcpIp_GetTxReqElemListIdxOfSocketUdpDyn(socketUdpIdx) < TcpIp_GetSizeOfTxReqElemList());
    ipTransmitFlags |= TCPIP_V_IP_TRANSMIT_FLAG_TX_CONFIRMATION;
  }

  ipTransmitFlags |= TCPIP_V_IP_TRANSMIT_FLAG_RETRY_ON_PHYS_ADDR_MISS;

  /* #20 Check if there are other elements already stored in the retry queue. */
  if (TcpIp_Udp_VMatchingElementInRetryQueue(socketUdpIdx, DestSockAddrPtr) == TRUE)                                    /* SBSW_TCPIP_ConstPtr */
  {
    /* #30 if so, trigger the saving of this element at the end of the queue to maintain the correct order. */
    transmitRetVal = TCPIP_E_PHYS_ADDR_MISS;
  }
  else
  {
    /* #40 otherwise, trigger transmission of UDP datagram via IP layer. */
    TCPIP_ASSERT(DestSockAddrPtr->sa_family == IpTxReqDescPtr->AddressFamily);

    transmitRetVal = TcpIp_VIpTransmit(IpTxReqDescPtr, ipTransmitLength, TCPIP_PROTOCOL_UDP, TxReqIdx, ipTransmitFlags);  /* SBSW_TCPIP_ConstPtr */
  }


  if (transmitRetVal == TCPIP_OK)
  {
    retVal = E_OK;
  }
  else if (transmitRetVal == TCPIP_E_PHYS_ADDR_MISS)
  {
    /* #50 Queue transmission of packet if IP layer could not send the packet due to physical address cache miss, if configured.
     *     Otherwise: Abort transmission. */
    /* add request to the retry list if possible */
    retVal = TcpIp_Udp_VStoreRequestInRetryQueue(socketUdpIdx, IpTxReqDescPtr, UdpPayloadLen, DestSockAddrPtr, TxReqIdx);  /* SBSW_TCPIP_ConstPtr */
  }
  else
  {
    /* Ethernet TX buffer was already released in TcpIp_VIpTransmit(). */
    retVal = E_NOT_OK;
  }

  return retVal;
}  /* TcpIp_Udp_VTransmit */

/**********************************************************************************************************************
 *  TcpIp_Udp_StoreChecksumInHeader()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Udp_StoreChecksumInHeader(
    uint16           ChecksumNbo,
    TCPIP_P2V(uint8) UdpHdrPtr)
{
  uint16           localChecksumNbo = ChecksumNbo;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Change checksum to 0xFFFF if it is zero (according to [IETF RFC1122 4.1.3.4  UDP Checksums]). */
  if (ChecksumNbo == 0u)
  {
    localChecksumNbo = 0xFFFF;
  }

  /* #20 Store checksum at correct offset inside to UDP header. */
  TCPIP_PUT_UINT16_RAW(UdpHdrPtr, TCPIP_UDP_HDR_OFS_CHECKSUM, localChecksumNbo);                                             /* SBSW_TCPIP_WriteUdpHeader */
} /* TcpIp_Udp_StoreChecksumInHeader() */

/**********************************************************************************************************************
 *  TcpIp_Udp_SendRetryQueueIfPossible()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Udp_SendRetryQueueIfPossible(
    TcpIp_SocketUdpDynIterType        SocketUdpIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_DListIdxType                    txRetryQElemIdx   = TcpIp_GetTxRetrQueueOfSocketUdpDyn(SocketUdpIdx).FirstIdx;
  TcpIp_UdpTxRetryQueueElementsIterType txRetryQElemCount = TcpIp_GetTxRetrQueueOfSocketUdpDyn(SocketUdpIdx).ElementCount;
  TcpIp_UdpTxRetryQueueElementsIterType txRetryQElemIterIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(   ((txRetryQElemCount == 0u) && (txRetryQElemIdx == TCPIP_DLIST_END_IDX))
               || ((txRetryQElemCount  > 0u) && (txRetryQElemIdx != TCPIP_DLIST_END_IDX)));

  /* #10 Iterate over all elements in the TX retry queue of the UDP socket. */
  for (txRetryQElemIterIdx = 0; txRetryQElemIterIdx < txRetryQElemCount; txRetryQElemIterIdx++)
  {
    TcpIp_DListIdxType txRetryQElemNextIdx;
    TCPIP_P2C(TcpIp_Udp_RetryQueueElementType) retryQueueElemPtr;
    uint8 ipTransmitFlags = TCPIP_V_IP_TRANSMIT_FLAG_RETRY_ON_PHYS_ADDR_MISS;

    TCPIP_ASSERT(txRetryQElemIdx < TcpIp_GetSizeOfUdpTxRetryQueueElements());

    retryQueueElemPtr   = TcpIp_GetAddrUdpTxRetryQueueElements(txRetryQElemIdx);
    txRetryQElemNextIdx = TcpIp_GetUdpTxRetryQueueElementChain(txRetryQElemIdx).NextIdx;

    /* #20 Request a TX confirmation for the UDP datagram, if a TX request list is attached to the socket. */
    if (TcpIp_GetTxReqElemListIdxOfSocketUdpDyn(SocketUdpIdx) < TcpIp_GetSizeOfTxReqElemList())
    {
      ipTransmitFlags |= TCPIP_V_IP_TRANSMIT_FLAG_TX_CONFIRMATION;
    }
    else
    {
      TCPIP_ASSERT(TcpIp_GetTxReqElemListIdxOfSocketUdpDyn(SocketUdpIdx) == TCPIP_NO_TXREQELEMLISTIDXOFSOCKETUDPDYN);
    }

    TCPIP_ASSERT(retryQueueElemPtr->Destination.sa_family == retryQueueElemPtr->IpTxRequestDesc.AddressFamily);

    /* #30 Call transmit function of IP layer and remove the element from the retry queue if the transmit was accepted. */
    if (TcpIp_VIpTransmit(&retryQueueElemPtr->IpTxRequestDesc,                                                        /* SBSW_TCPIP_VIpTransmit */
          retryQueueElemPtr->UdpPayloadLen + TCPIP_UDP_HDR_LEN_BYTE, TCPIP_PROTOCOL_UDP,
          retryQueueElemPtr->UdpTxReqTabIdx, ipTransmitFlags) != TCPIP_E_PHYS_ADDR_MISS)
    {
      TcpIp_DListRemoveElement(TcpIp_GetAddrTxRetrQueueOfSocketUdpDyn(SocketUdpIdx), txRetryQElemIdx);                /* SBSW_TCPIP_DListRemoveElement */
    }

    txRetryQElemIdx = txRetryQElemNextIdx;
  }

  TCPIP_ASSERT(txRetryQElemIdx == TCPIP_DLIST_END_IDX);

} /* TcpIp_Udp_SendRetryQueueIfPossible */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_Udp_CancelRetriesForDestination()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Udp_CancelRetriesForDestination(
  uint8                             CtrlIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketDynIterType socketUdpIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all UDP sockets. */
  for (socketUdpIdx = 0; socketUdpIdx < TcpIp_GetSizeOfSocketUdpDyn(); socketUdpIdx++)
  {
    TCPIP_P2V(TcpIp_DListType) txRetryQPtr = TcpIp_GetAddrTxRetrQueueOfSocketUdpDyn(socketUdpIdx);

    TcpIp_DListIdxType txRetryQElemIdx = txRetryQPtr->FirstIdx;

    /* #20 Iterate over TX retry queue elements of the socket. */
    while (txRetryQElemIdx < TcpIp_GetSizeOfUdpTxRetryQueueElements())
    {
      TcpIp_DListIdxType txRetryQElemNextIdx = TCPIP_DLIST_GET_NEXT(txRetryQElemIdx, *txRetryQPtr);
      TCPIP_P2C(TcpIp_Udp_RetryQueueElementType) retryQueueElemPtr = TcpIp_GetAddrUdpTxRetryQueueElements(txRetryQElemIdx);

      TCPIP_ASSERT(txRetryQPtr->ElementCount > 0u);

      /* #30 Check if the retry queue element uses the given CtrlIdx and remote IP address. */
      if (retryQueueElemPtr->IpTxRequestDesc.CtrlIdx == CtrlIdx)
      {
        if (TcpIp_VSockIpAddrIsEqual(&retryQueueElemPtr->Destination, RemoteAddrPtr) == TRUE)                           /* SBSW_TCPIP_Udp_CancelRetriesForDestination_TcpIp_VSockIpAddrIsEqual */
        {
          TCPIP_ASSERT(retryQueueElemPtr->IpTxRequestDesc.AddressFamily == RemoteAddrPtr->sa_family);

          /* #40 Cancel transmit at IP layer and remove element from the retry queue. */
          TcpIp_VIpTransmitCancel(&retryQueueElemPtr->IpTxRequestDesc, 0, TCPIP_PROTOCOL_UDP);                          /* SBSW_TCPIP_Udp_CancelRetriesForDestination_retryQueueElemPtr */
          TcpIp_DListRemoveElement(txRetryQPtr, txRetryQElemIdx);                                                       /* SBSW_TCPIP_Udp_CancelRetriesForDestination_retryQueueElemPtr */
        }
      }

      txRetryQElemIdx = txRetryQElemNextIdx;
    }
  }
} /* TcpIp_Udp_CancelRetriesForDestination() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_Udp_VValidateChecksum()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_VValidateChecksum(
    uint16                            ReceivedChecksum,
    TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
    TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
    TCPIP_P2C(uint8)                  IpPayloadPtr,
    uint16                            IpPayloadLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify that checksum of received packet is zero, if packet has a checksum. */
  if (ReceivedChecksum != 0u)
  {
    if (TcpIp_VCalcPseudoHdrAndChecksum(RxSockRemAddrPtr, RxSockLocAddrPtr, IpPayloadPtr, IpPayloadLen, TCPIP_SOCK_PROT_UDP) == 0u) /* SBSW_TCPIP_NonNullPtrParameter */
    {
      /* checksum is valid -> OK */
      retVal = E_OK;
    }
  }
  else
  {
    /* #20 Otherwise accept packet only if it is not an IPv6 packet. (Checksum is mandatory in case of IPv6). */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
    if (RxSockRemAddrPtr->sa_family != IPBASE_AF_INET6)
# endif
    {
      /* for IPv4 the checksum is optional. */
      retVal = E_OK;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_Udp_VStoreRequestInRetryQueue()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Udp_VStoreRequestInRetryQueue(
  TcpIp_SocketUdpDynIterType                 SocketUdpIdx,
  TCPIP_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr,
  uint16                                     UdpPayloadLen,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          DestSockAddrPtr,
  uint8                                      TxReqIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_SizeOfUdpTxRetryQueueElementsType txRetryQueueMaxNumForSocket = TcpIp_GetTxRetrQueueMaxNumOfSocketUdpDyn(SocketUdpIdx);

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpTxReqDescPtr->AddressFamily == DestSockAddrPtr->sa_family);

  /* #10 Check if retry queue of the socket has not reached the configured limit. */
  if (TcpIp_GetTxRetrQueueOfSocketUdpDyn(SocketUdpIdx).ElementCount < txRetryQueueMaxNumForSocket)
  {
    TcpIp_DListIdxType retryQueueEleIdx = TCPIP_DLIST_END_IDX;

    /* #20 Insert a new element into the retry queue or abort transmit of UDP datagram if all retry queue elements are in use. */
    if (TcpIp_DListAddElement(TcpIp_GetAddrTxRetrQueueOfSocketUdpDyn(SocketUdpIdx),                                     /* SBSW_TCPIP_DListAddElement */
          TcpIp_GetTxRetrQueueOfSocketUdpDyn(SocketUdpIdx).LastIdx, &retryQueueEleIdx) == E_OK)
    {
      /* a new element could be added */
      TCPIP_P2V(TcpIp_Udp_RetryQueueElementType) retryQueueElePtr = TcpIp_GetAddrUdpTxRetryQueueElements(retryQueueEleIdx);

      TCPIP_ASSERT(retryQueueEleIdx < TcpIp_GetSizeOfUdpTxRetryQueueElements());

      /* #30 Initialize content of the retry queue element. */
      (void)IpBase_CopySockAddr(&retryQueueElePtr->Destination.SockAddr, &DestSockAddrPtr->SockAddr);                   /* SBSW_TCPIP_IpBase_CopySockAddr_3 */
      retryQueueElePtr->UdpPayloadLen   =  UdpPayloadLen;                                                               /* SBSW_TCPIP_RetryQueueElePtr */
      retryQueueElePtr->UdpTxReqTabIdx  =  TxReqIdx;                                                                    /* SBSW_TCPIP_RetryQueueElePtr */
      retryQueueElePtr->IpTxRequestDesc = *IpTxReqDescPtr;                                                              /* SBSW_TCPIP_RetryQueueElePtr */

      /* accept this first send attempt */
      retVal = E_OK;
    }
    else
    {
      TCPIP_ASSERT(retryQueueEleIdx == TCPIP_DLIST_END_IDX);
    }
  }

  if (retVal == E_NOT_OK)
  {
    /* Configured limit of retry queue entries for this socket has been reached or retry queue is already full. */
    TcpIp_VIpTransmitCancel(IpTxReqDescPtr, TxReqIdx, TCPIP_PROTOCOL_UDP);                                              /* SBSW_TCPIP_ConstPtr */
  }

  return retVal;
} /* TcpIp_Udp_VStoreRequestInRetryQueue() */


/**********************************************************************************************************************
 *  TcpIp_Udp_VMatchingElementInRetryQueue()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_Udp_VMatchingElementInRetryQueue(
  TcpIp_SocketUdpDynIterType                 SocketUdpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          DestSockAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_DListIdxType                    txRetryQElemIdx = TcpIp_GetTxRetrQueueOfSocketUdpDyn(SocketUdpIdx).FirstIdx;
  TcpIp_UdpTxRetryQueueElementsIterType txRetryQElemCount = TcpIp_GetTxRetrQueueOfSocketUdpDyn(SocketUdpIdx).ElementCount;
  TcpIp_UdpTxRetryQueueElementsIterType txRetryQElemIterIdx;
  boolean matchFound = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(((txRetryQElemCount == 0u) && (txRetryQElemIdx == TCPIP_DLIST_END_IDX))
    || ((txRetryQElemCount > 0u) && (txRetryQElemIdx != TCPIP_DLIST_END_IDX)));

  /* #10 Iterate over all elements in the TX retry queue of the UDP socket. */
  for (txRetryQElemIterIdx = 0; txRetryQElemIterIdx < txRetryQElemCount; txRetryQElemIterIdx++)
  {
    TcpIp_DListIdxType txRetryQElemNextIdx;
    TCPIP_P2C(TcpIp_Udp_RetryQueueElementType) retryQueueElemPtr;

    TCPIP_ASSERT(txRetryQElemIdx < TcpIp_GetSizeOfUdpTxRetryQueueElements());

    retryQueueElemPtr = TcpIp_GetAddrUdpTxRetryQueueElements(txRetryQElemIdx);
    txRetryQElemNextIdx = TcpIp_GetUdpTxRetryQueueElementChain(txRetryQElemIdx).NextIdx;

    /* #20 Check if remote address of retry queue element matches the supplied remote address. */
    if (IpBase_SockIpAddrIsEqual(&DestSockAddrPtr->SockAddr, &retryQueueElemPtr->Destination.SockAddr) == TRUE)        /* SBSW_TCPIP_SockIpAddrIsEqual */
    {
      /* #30 if so, set return value to TRUE and leave the loop. */
      matchFound = TRUE;

      break;
    }

    txRetryQElemIdx = txRetryQElemNextIdx;
  }

  return matchFound;
} /* TcpIp_Udp_VMatchingElementInRetryQueue() */

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_TCPIP_DListInitDesc
    \DESCRIPTION       CONCEPT: A DList data structure describes one or more doubly-linked lists using elements with
                                the same datatype. The following sub structures are used by a DList:
                                - A descriptor structure that manages the free list. (TcpIp_DListDescType)
                                - An array (pool) containing list elements (TcpIp_DListNodeType[])
                                - An array (pool) containing data elements (User_DataType[])
                                - One or more DList instances share the same descriptor and the same data/list
                                  elements. (TcpIp_DListType)

                                The list element and data element arrays have equal size and are mapped 1:1 with the
                                same index. The reason for using two arrays is that list operations can be done
                                independently from the data elements. Therefore the DList modification functions can be
                                generic and the data elements can use different types.

                       1: Argument TcpIp_GetAddrUdpTxRetryQueuePoolDesc(TCPIP_UDP_TX_RETRY_QUEUE_POOL_IDX) is the
                          address to the first (and single) element of a ComStackLib array. The generator ensures that
                          this address points to valid memory if TcpIp_GetSizeOfUdpTxRetryQueueElements() > 0 and to
                          NULL_PTR otherwise.
                       2: Argument TcpIp_GetAddrUdpTxRetryQueueElementChain(0) is the address to the first element of
                          a ComStackLib array. The number of the chain elements is always equal to
                          TcpIp_GetSizeOfUdpTxRetryQueueElements().
    \COUNTERMEASURE \R TcpIp_GetSizeOfUdpTxRetryQueueElements() > 0 is checked before the addresses are used.

  \ID SBSW_TCPIP_DListInit
    \DESCRIPTION       1: Argument TcpIp_GetAddrTxRetrQueueOfSocketUdpDyn(socketUdpIdx) is the address of an element in
                          a ComStackLib array. The socketUdpIdx which is used to address the element is checked in the
                          surrounding loop.
                       2: Argument TcpIp_GetAddrUdpTxRetryQueuePoolDesc(TCPIP_UDP_TX_RETRY_QUEUE_POOL_IDX) may be
                          NULL_PTR if no UDP tx retry queue is configured. The TxRetrQueue of the UDP socket will not
                          be used and initialization could be avoided here. But for robustness reasons the
                          datastructure is initialized anyway.
    \COUNTERMEASURE \N 1: Qualified use-case CSL01 of ComStackLib.
                       2: Element will not be used.

  \ID SBSW_TCPIP_DListClear
    \DESCRIPTION       Argument rxRetryQueuePtr is passed to subroutine.
                       The pointer references an element in a ComStackLib array and is creted by
                       TcpIp_GetAddrTxRetrQueueOfSocketUdpDyn(SocketUdpIdx).
    \COUNTERMEASURE \N The caller ensures that SocketUdpIdx is within the valid range by using the TcpIp_GetSizeOf...()
                       function.
                       Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_GetIpAddr
    \DESCRIPTION       Argument &(rxSockLocAddr.TcpIpSockAddr) is a pointer to a local (stack) variable.
                       The parameters NetmaskPtr and DefaultRouterPtr are NULL_PTR which is allowed by the called subroutine.
    \COUNTERMEASURE \N The pointer points to valid memory (stack) or NULL_PTR.

  \ID SBSW_TCPIP_Udp_VValidateChecksum
    \DESCRIPTION       1: Argument &rxSockLocAddr is a pointer to a local (stack) variable.
                       2: Arguments RxSockRemAddrPtr and IpPayloadPtr ar passed unmodified to subroutine.
                          Additionally the pointers are qualified as const and the called function is not able to write
                          to the memory location.
    \COUNTERMEASURE \N 1: The pointer points to valid memory (stack) or NULL_PTR.
                       2: The caller ensures that RxSockRemAddrPtr and IpPayloadPtr point to valid memory.

  \ID SBSW_TCPIP_IpBase_CopySockAddr_2
    \DESCRIPTION       1: Argument &rxSockRemAddr.SockAddr is a pointer to a local (stack) variable.
                       2: Argument &RxSockRemAddrPtr->SockAddr is a const pointer.
    \COUNTERMEASURE \N 1: The pointer points to valid memory on the stack or NULL_PTR.
                       2: Pointer to const data that cannot be changed by subroutine.

  \ID SBSW_TCPIP_RxIndicationFunctions
    \DESCRIPTION       1: Argument &rxSockRemAddr.SockAddr is a pointer to a local (stack) variable.
                       2: Argument &IpPayloadPtr[TCPIP_UDP_HDR_LENGTH] and udpPayloadLen are derived from parameters
                          IpPayloadPtr and IpPayloadLen. Data at IpPayloadPtr is at least TCPIP_UDP_HDR_LENGTH bytes.
                          udpPayloadLen = IpPayloadLen - TCPIP_UDP_HDR_LEN_BYTE.
    \COUNTERMEASURE \N 1: The pointer points to valid memory on the stack or NULL_PTR.
                       2: A runtime check verifies that IpPayloadLen >= TCPIP_UDP_HDR_LEN_BYTE.

  \ID SBSW_TCPIP_GetAddrUsingCslIdxFromCaller
    \DESCRIPTION       ComStackLib function TcpIp_GetAddr...Of<Array>(Idx) is used which is the same as <Array>[Idx].
                       Idx is checked by the caller of the function.
    \COUNTERMEASURE \N The caller ensures that the index is within the valid range by using the TcpIp_GetSizeOf...() function.
                       Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_RetryQueueElePtr
    \DESCRIPTION       TcpIp_GetAddrUdpTxRetryQueueElements(retryQueueEleIdx) is used to get the address of an element
                       in the TX retry queue array. A valid index (retryQueueEleIdx) is returned by
                       TcpIp_DListAddElement() if the return code of the function is E_OK. The index is only used if
                       this is the case.
                       TcpIp_DListAddElement() obtains the index from the free list only if a free element exists.
                       If no free element exists the return value is negative and the value is not used.
    \COUNTERMEASURE \R Index/pointer is only used if TcpIp_DListAddElement() returned E_OK.

  \ID SBSW_TCPIP_IpBase_CopySockAddr_3
    \DESCRIPTION       1: Argument &retryQueueElePtr->Destination.SockAddr is valid due to SBSW_TCPIP_RetryQueueElePtr.
                       2: Argument &DestSockAddrPtr->SockAddr is a const pointer.
    \COUNTERMEASURE \N 1: See SBSW_TCPIP_RetryQueueElePtr.
                       2: The subroutine cannot write to a const pointer.

  \ID SBSW_TCPIP_Ip_ProvideTxBuffer
    \DESCRIPTION       1: Argument &ipV4AddrIdx, &ipBufferPtr, &ipBufferLen are pointers to local (stack) variables.
                       2: Argument &DestinationPtr->SockAddrIn points to data provided and checked by the caller.
                       3: Argument TcpIp_GetAddrIpTxRequestDescriptorOfSocketUdpDyn(SocketUdpIdx) is a pointer to
                          an element in a ComStackLib array.
    \COUNTERMEASURE \N 1: The pointer points to valid memory on the stack.
                       2: The caller ensures that DestinationPtr points to valid memory.
                       3: The caller ensures that the index is within the valid range by using the TcpIp_GetSizeOf...() function.
                          Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_Ip_FragmentProvideTxBuffer
    \DESCRIPTION       1: Argument TcpIp_GetAddrIpTxRequestDescriptorOfSocketUdpDyn(SocketUdpIdx) points to an element
                          in the ComStackLib array SocketUdpDyn which is accessed using index SocketUdpIdx.
                          The data of the element is initialized by the caller (via TcpIp_Udp_RequestTxBuffer()).
                       2: Arguments BufPtrPtr and BufLenPtr point to data provided and checked by the caller.
    \COUNTERMEASURE \N 1: The caller ensures that SocketUdpIdx is within the valid range by using the TcpIp_GetSizeOf...() function.
                          Qualified use-case CSL01 of ComStackLib.
                       2: The caller ensures that BufPtrPtr and BufLenPtr point to valid memory.

  \ID SBSW_TCPIP_WritePosOfTxReqElemListDyn
    \DESCRIPTION       ComStackLib array TxReqElem is accessed with txReqElemIdx.
                       The value of txReqElemIdx is read from TcpIp_GetWritePosOfTxReqElemListDyn(txReqElemListIdx).
                       The value txReqElemListIdx is checked to be valid. (txReqElemListIdx < TcpIp_GetSizeOfTxReqElemList())
                       The write position is updated in the following functions to a valid index in the range
                       [TcpIp_GetTxReqElemStartIdxOfTxReqElemList(txReqElemListIdx)..TcpIp_GetTxReqElemEndIdxOfTxReqElemList(txReqElemListIdx)].
                       - TcpIp_Udp_Init
                       - TcpIp_Udp_CloseSocket
                       - TcpIp_Udp_Transmit
    \COUNTERMEASURE \R A runtime check verifies that txReqElemListIdx is vaild.
                       Variable txReqElemIdx is read from TcpIp_GetWritePosOfTxReqElemListDyn(txReqElemListIdx) which is
                       always updated to valid values.

  \ID SBSW_TCPIP_Udp_VTransmit
    \DESCRIPTION       1: Argument TcpIp_GetAddrIpTxRequestDescriptorOfSocketUdpDyn(SocketUdpIdx) points to an element
                          in the ComStackLib array SocketUdpDyn which is accessed using index SocketUdpIdx.
                       2: Argument TcpIp_GetTxReqIpBufPtrOfSocketUdpDyn(SocketUdpIdx) is a pointer that is written in
                          TcpIp_Udp_RequestTxBuffer().
                          The functions TcpIp_Udp_RequestTxBuffer() and TcpIp_Udp_Transmit() are always called in
                          this order by TcpIp_UdpTransmitInternal() and TcpIp_Udp_Transmit() is only called if
                          TcpIp_Udp_RequestTxBuffer() returned a positive result and wrote a valid pointer via
                          TcpIp_SetTxReqIpBufPtrOfSocketUdpDyn(SocketUdpIdx).
                          TcpIp_Udp_RequestTxBuffer() ensures that the requested IP buffer is at least
                          TCPIP_UDP_HDR_LEN_BYTE + UdpPayloadLen bytes large.
                          Argument UdpPayloadLen is provided by TcpIp_UdpTransmitInternal() and consistent with
                          TcpIp_SetTxReqIpBufPtrOfSocketUdpDyn(SocketUdpIdx).
                       3: Argument DestSockAddrPtr points to data provided and checked by the caller.
    \COUNTERMEASURE \N 1: The caller ensures that SocketUdpIdx is within the valid range by using the TcpIp_GetSizeOf...() function.
                          Qualified use-case CSL01 of ComStackLib.
                       2: TcpIp_UdpTransmitInternal() ensures that TxReqIpBufPtrOfSocketUdpDyn(SocketUdpIdx) and
                          parameter UdpPayloadLen are valid.
                       3: The caller ensures that DestSockAddrPtr points to valid memory.

  \ID SBSW_TCPIP_TxRetryQueueElements
    \DESCRIPTION       CONCEPT: UDP TX Retry Queue.
                       Each UDP socket may have a TX retry queue (TxRetrQueueOfSocketUdpDyn).
                       The Queue is modelled as a linked list data structure.
                       The fields FirstIdx/LastIdx refence the index of the first/last element of the linked-list
                       inside the array UdpTxRetryQueueElements.
                       All elements of the list store the index of their predecessor and successor.
                       The field ElementCount indecates how many elements are in the list.
                       If an element has no predecessor/successor the index is set to TCPIP_DLIST_END_IDX.
                       If a list is empty FirstIdx and LastIdx are set to TCPIP_DLIST_END_IDX and ElementCount is 0.
                       It is possible to iterate forward and backward through the linked list by reading the
                       PrevIdx/NextIdx of the list element and comparing it against TCPIP_DLIST_END_IDX.
                       If the value is != TCPIP_DLIST_END_IDX the index indicates a valid predecessor/successor.
                       If the value is TCPIP_DLIST_END_IDX there is no predecessor/successor and the index must not be
                       used.
                       Modifications of the linked-list are only done using the DList modification functions which
                       ensure that the list remains consitent.
                       The retry queue of all sockets is initialized to an empty list in TcpIp_Udp_Init() via
                       TcpIp_DListInit().
                       If a socket is closed the retry queue of that socket is also cleared by TcpIp_Udp_CloseSocket().
                       Elements are inserted into the TX retry queue by TcpIp_Udp_VStoreRequestInRetryQueue() if a
                       transmission of a UDP datagram is not possible due to a pending link layer address resolution.
                       All members of the inserted element are initialized to valid values at this point.
                       An element is removed from the TX retry queue for one of the following two reasons:
                       1. The UDP datagram could be sent by TcpIp_Udp_SendRetryQueueIfPossible().
                       2. The link-layer address resolution for a destination has failed and therefore the datagrams to
                          this destination cannot be sent. -> TcpIp_Udp_CancelRetriesForDestination()
    \COUNTERMEASURE \N The described handling ensures that the link list remains consistent and elements are valid.

  \ID SBSW_TCPIP_SockIpAddrIsEqual
    \DESCRIPTION       1: Argument &RemoteAddrPtr->SockAddr points to data provided and checked by the caller.
                       2: &retryQueueElemPtr->Destination.SockAddr points to element at txRetryQElemIdx in the
                          ComStackLib array UdpTxRetryQueueElements.
                          Index txRetryQElemIdx is obtained via TcpIp_GetTxRetrQueueOfSocketUdpDyn(SocketUdpIdx).FirstIdx
                          or (in next iteretions) via TcpIp_GetUdpTxRetryQueueElementChain(txRetryQElemIdx).NextIdx.
                          (see SBSW_TCPIP_TxRetryQueueElements for concept of the UDP TX retry queue).
    \COUNTERMEASURE \R 1: The caller ensures that &RemoteAddrPtr->SockAddr points to valid memory.
                       2: The caller ensures that SocketUdpIdx is within the valid range by using the TcpIp_GetSizeOf...() function.
                          Qualified use-case CSL01 of ComStackLib.
                          A runtime check txRetryQElemIterIdx < txRetryQElemCount avoids that more entries are read than
                          there are in the list.

  \ID SBSW_TCPIP_VIpTransmit
    \DESCRIPTION       Argument &retryQueueElemPtr->IpTxRequestDesc references an IP TX request descriptor that is
                       stored in a TX retry queue element of a UDP socket.
    \COUNTERMEASURE \N See SBSW_TCPIP_SockIpAddrIsEqual for argumentation why retryQueueElemPtr is valid.

  \ID SBSW_TCPIP_DListRemoveElement
    \DESCRIPTION       Argument TcpIp_GetAddrTxRetrQueueOfSocketUdpDyn(SocketUdpIdx) references element at index
                       SocketUdpIdx in the ComStackLib array SocketUdpDyn.
    \COUNTERMEASURE \N The caller ensures that SocketUdpIdx is within the valid range by using the TcpIp_GetSizeOf...() function.
                       Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_Udp_CancelRetriesForDestination_retryQueueElemPtr
    \DESCRIPTION       retryQueueElemPtr points to element at txRetryQElemIdx in the ComStackLib array
                       UdpTxRetryQueueElements. Index txRetryQElemIdx is obtained via
                       TcpIp_GetTxRetrQueueOfSocketUdpDyn(socketUdpIdx).FirstIdx or (in next iteretions) via
                       TcpIp_GetUdpTxRetryQueueElementChain(txRetryQElemIdx).NextIdx.
                       (see SBSW_TCPIP_TxRetryQueueElements for concept of the UDP TX retry queue).
                       Variable socketUdpIdx is always in range [0...TcpIp_GetSizeOfSocketUdpDyn()].
    \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_Udp_CancelRetriesForDestination_TcpIp_VSockIpAddrIsEqual
    \DESCRIPTION       1: Address of member Destination of retryQueueElemPtr is passed to subroutine.
                       2: Unmodified pointer parameter RemoteAddrPtr is passed to subroutie.
    \COUNTERMEASURE \N 1: see SBSW_TCPIP_Udp_CancelRetriesForDestination_retryQueueElemPtr.
                       2: The caller ensures that the pointer parameter is not NULL_PTR and points to a valid memory location.

  \ID SBSW_TCPIP_DListAddElement
    \DESCRIPTION       Argument TcpIp_GetAddrTxRetrQueueOfSocketUdpDyn(SocketUdpIdx) points to element at index
                       SocketUdpIdx in the ComStackLib array SocketUdpDyn.
    \COUNTERMEASURE \N The caller ensures that SocketUdpIdx is within the valid range by using the TcpIp_GetSizeOf...() function.
                       Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_WriteUdpHeader
    \DESCRIPTION       The function assumes that it is safe to write up to TCPIP_UDP_HDR_LENGTH bytes at the memory
                       location referenced by a uint8 pointer parameter.
    \COUNTERMEASURE \N The caller ensures that the pointer references a memory segment of at least TCPIP_UDP_HDR_LENGTH
                       bytes length.

   SBSW_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: Udp.c
 *********************************************************************************************************************/
