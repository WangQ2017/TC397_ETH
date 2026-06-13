/**********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  --------------------------------------------------------------------------------------------------------------------
 *         \file  TcpIp_Tcp.c
 *        \brief  Implementation of Transmission Control Protocol (TCP)
 *
 *      \details  This file is part of the TcpIp module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/
/* PRQA S 0777, 0779 EOF */ /* MD_MSR_5.1 */ /* Identifiers (internal and external) shall not rely on the significance of more than 31 characters. */

/* PRQA S 0828 EOF */ /* MD_MSR_1.1 */

#define TCPIP_TCP_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_TCP == STD_ON)

#include "TcpIp_Tcp.h"
#include "TcpIp_Lcfg.h"
#include "TcpIp_Tcp_Cbk.h"
#include "TcpIp_Priv.h"
#include "TcpIp_Cbk.h"
#include "IpBase.h"

#include "TcpIp.h"

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# include "TcpIp_IpV4.h"
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# include "TcpIp_IpV6.h"
#endif
#include "IpBase_Copy.h"
#include "IpBase_Sock.h"

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
# include "Tls.h"
# include "Tls_Cbk.h"
#endif

#if defined(TCPIP_SPECIAL_TCP_ACC_INCLUDEFILE)                                                                          /* COV_TCPIP_RUNTIME_TEST */
/* This feature adds a user callback similar to the callback 'User_TcpAccepted'. This callback is called right after
   receiving a 'SYN' on a TCP listen socket and reports the listen socket ID and the ID of the socket that will accept
   the connection request. These sockets are the same ones that are reported in the offical call 'User_TcpAccepted'
   later on. The reported socket IDs may only be used for analysis purposes, the accepting socket may not be used in
   any way before it is fully connected (reported by call of User_TcpAccepted). */

#include TCPIP_SPECIAL_TCP_ACC_INCLUDEFILE

/*
The following 3 defines are needed in a UserCfg.h file (will be inserted at the end of TcpIp_Cfg.h):

#define TCPIP_SPECIAL_TCP_ACC_ENABLED       STD_ON
#define TCPIP_SPECIAL_TCP_ACC_INCLUDEFILE   "User_Cbk.h"
#define TCPIP_SPECIAL_TCP_ACCEPTING_FCT(a,b,c)     User_TcpPreAccepted(a,b,c)
*/
#endif


/**********************************************************************************************************************
 *  LOCAL CONSTANT CONFIGURABLE MACROS
 *********************************************************************************************************************/
/* these defines might be configurable in future  */
/* Using a minimum size of 48 bytes causes the problem that possibly not even the maximum TCP Header size (60 bytes)
   fits into the message. Therefore the minimum size is set some bytes bigger to avoid this special scenarios. */
#define TCPIP_TCP_IPV4_MIN_PATH_MTU                    100u   /* min size is  120 - IPv4-Header size */ /* 'A host MUST never reduce its estimate of the Path MTU below 68 octets.' [IETF RFC1191 3. Host specification] */
#define TCPIP_TCP_IPV6_MIN_PATH_MTU                    1240u  /* min size is 1280 - IPv6-Header size */ /* 'IPv6 requires that every link in the internet has an MTU of 1280 octets or greater.' [IETF RFC2460 5. Packet Size Issues] */

/* [RFC6691 TCP Options and Maximum Segment Size (MSS) */
#define TCPIP_TCP_DEFAULT_TX_MSS_IPV4                 (TCPIP_IPV4_MTU_MIN_BYTE - TCPIP_IPV4_HDR_LEN_BYTE - TCPIP_TCP_HDR_LEN_BYTE) /* =  536 bytes |  (default IPv4 Maximum Transmission Unit) - 20 (IPv4 fixed header size) - 20 (TCP fixed header size) =  536. */
#define TCPIP_TCP_DEFAULT_TX_MSS_IPV6                 (TCPIP_IPV6_MTU_MIN_BYTE - TCPIP_IPV6_HDR_LEN_BYTE - TCPIP_TCP_HDR_LEN_BYTE) /* = 1220 bytes |  (default IPv6 Maximum Transmission Unit) - 40 (IPv6 fixed header size) - 20 (TCP fixed header size) = 1220. */

#define TCPIP_TCP_TX_RETRY_INT_RESET_VALUE_CYCLES   (3000u / TCPIP_MAIN_FCT_PERIOD_MSEC)  /* RFC 6298: Reset the initial RTO (retransmission timeout) to 3 seconds in case of a retransmission of a SYN segment */



/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#define TCPIP_TCP_EMPTY_PORT                   0x0000u
#define TCPIP_TCP_EMPTY_CHKSUM                 0x0000u
#define TCPIP_TCP_EMPTY_URG_PTR                0x0000u

#define TCPIP_TCP_CODE_BIT_MASK_FSA            0x13u  /* FIN_SYN_ACK */
#define TCPIP_TCP_CODE_BIT_FIN                 0x01u
#define TCPIP_TCP_CODE_BIT_SYN                 0x02u
#define TCPIP_TCP_CODE_BIT_RST                 0x04u
#define TCPIP_TCP_CODE_BIT_PSH                 0x08u
#define TCPIP_TCP_CODE_BIT_ACK                 0x10u
#define TCPIP_TCP_CODE_BIT_URG                 0x20u
#define TCPIP_TCP_CODE_BIT_ECE                 0x40u
#define TCPIP_TCP_CODE_BIT_CWR                 0x80u

#define TCPIP_TCP_HDR_LEN_BYTE                   20u /* TCP header requires at least 20 bytes (without options) */
#define TCPIP_TCP_HDR_DEFAULT_DATA_OFFSET_BYTE_VALUE   0x50u
#define TCPIP_TCP_HDR_OPT_LEN_MAX_BYTE           40u /* Maximum total length of TCP options */
#define TCPIP_TCP_HDR_LEN_MAX_BYTE               (TCPIP_TCP_HDR_OPT_LEN_MAX_BYTE + TCPIP_TCP_HDR_LEN_BYTE) /* TCP header has 20 bytes and a maximum of 40 bytes options */
#define TCPIP_IPV4_HDR_LEN_BYTE                  20u /* IPv4 header requires at least 20 bytes (without options) */
#define TCPIP_IPV6_HDR_LEN_BYTE                  40u /* IPv6 fixed header requires 40 bytes */

#define TCPIP_IPV4_MTU_MIN_BYTE                 576u  /* Minimum supported MTU of IPv4 according to [RFC879 Page 25] */
#define TCPIP_IPV6_MTU_MIN_BYTE                1280u  /* Minimum supported MTU of IPv6 according to [RFC2460 5. Packet Size Issues] */

#define TCPIP_TCP_OPT_ID_END                   0u
#define TCPIP_TCP_OPT_ID_NOP                   1u
#define TCPIP_TCP_OPT_ID_MAX_SEG_SIZE          2u
#define TCPIP_TCP_OPT_LEN_MAX_SEG_SIZE         4u
#define TCPIP_TCP_OPT_ID_SACK_PERMIT           4u
#define TCPIP_TCP_OPT_LEN_SACK_PERMIT          2u
#define TCPIP_TCP_OPT_ID_SACK                  5u
#define TCPIP_TCP_OPT_LEN_SACK                 2u
#define TCPIP_TCP_OPT_ID_TIMESTAMP             8u
#define TCPIP_TCP_OPT_LEN_TIMESTAMP           10u
#define TCPIP_TCP_OPT_ID_USER_TIMEOUT         28u
#define TCPIP_TCP_OPT_LEN_USER_TIMEOUT         4u

#define TCPIP_TCP_OPT_OFS_KIND                 0u
#define TCPIP_TCP_OPT_OFS_LENGTH               1u
#define TCPIP_TCP_OPT_OFS_VALUE                2u

/* option flags used with TcpIp_GetTxOneTimeOptsOfSocketTcpDyn() */
#define TCPIP_TCP_OPT_FLAG_USER_TIMEOUT        0x01u
#define TCPIP_TCP_OPT_FLAG_SACK_PERMIT         0x02u

#define TCPIP_TCP_OPT_USER_TIMEOUT_FLAG_GRANULARITY_MINUTES   0x8000u
#define TCPIP_TCP_OPT_USER_TIMEOUT_VALUE_MASK                 0x7FFFu

#define TCPIP_TCP_TIMESTAMP_ELEMENT_LEN        4u
#define TCPIP_TCP_SACK_ELEMENT_LEN             8u
#define TCPIP_TCP_NOP_ELEMENT_LEN              1u

#define TCPIP_TCP_SEQU_NUM_LEN                 4u

/* defines used in variable TcpIp_Tcp_CongestionControlMode */
/* The state 'fast retransmit' is an instable state and therefore this mode value is never used. The processing is
continued and the mode is advanced to 'fast recover'. For details see RFC 5681 section 3.2. */
#define TCPIP_TCP_CONG_CTRL_MODE_SLOW_START             1u
#define TCPIP_TCP_CONG_CTRL_MODE_CONGESTION_AVOIDANCE   2u
#define TCPIP_TCP_CONG_CTRL_MODE_FAST_RETRANSMIT        3u
#define TCPIP_TCP_CONG_CTRL_MODE_FAST_RECOVER           4u

/* define used in variable RtoStateOfSocketTcpDyn */
#define TCPIP_TCP_RTO_STATE_DEFAULT                0u
#define TCPIP_TCP_RTO_STATE_FIRST_CALC_PROCEEDED   1u
#define TCPIP_TCP_RTO_STATE_ACTIVE                 2u

#define TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV          TcpIp_GetSizeOfTcpRetryQElement()


/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 9 */ /* MD_MSR_FctLikeMacro */
#define TCPIP_TCP_SEQ1_BIGGER_SEQ2(A, B)            ( ((A) - (B) - 1u) < 0x80000000u )
#define TCPIP_TCP_SEQ1_BIGGER_OR_EQUAL_SEQ2(A, B)   ( ((A) - (B)    ) < 0x80000000u )
#define TCPIP_TCP_SEQ1_SMALLER_SEQ2(A, B)           ( TCPIP_TCP_SEQ1_BIGGER_SEQ2((B), (A)) )
#define TCPIP_TCP_SEQ1_SMALLER_OR_EQUAL_SEQ2(A, B)  ( TCPIP_TCP_SEQ1_BIGGER_OR_EQUAL_SEQ2((B), (A)) )

/* Initial congestion window calculation according to [RFC5681 3.1. Slow Start and Congestion Avoidance].
   RFC 5681 defines an initial cwnd of 2*SMSS if (SMSS > 2190), but that will never be the case for our implementations
   of IPv4 and IPv6. */
#define TCPIP_TCP_DEFAULT_SEGMENT_LIMIT(SMSS)       ((1095u < (SMSS)) ? 3u : 4u)

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#define TCPIP_TCP_HDR_SEQ_NUM_OFFSET              4u
#define TCPIP_TCP_HDR_ACK_NUM_OFFSET              8u
#define TCPIP_TCP_HDR_DATA_OFFSET_OFFSET         12u
#define TCPIP_TCP_HDR_CODE_BITS_OFFSET           13u
#define TCPIP_TCP_HDR_WINDOW_OFFSET              14u
#define TCPIP_TCP_HDR_CHECKSUM_OFFSET            16u
#define TCPIP_TCP_HDR_URGENT_PTR_OFFSET          18u
#define TCPIP_TCP_HDR_OPTIONS_OFFSET             20u


/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Variables to handle the free elements of the TCP RetryQueue that are linked as one list. The variables denote the
   index of the first and last element of the list and the number of elements in this list. */
TCPIP_LOCAL VAR(TcpIp_SizeOfTcpRetryQElementType, TCPIP_VAR_NOINIT) TcpIp_Tcp_FirstFreeRetrQueueEle;
TCPIP_LOCAL VAR(TcpIp_SizeOfTcpRetryQElementType, TCPIP_VAR_NOINIT) TcpIp_Tcp_LastFreeRetrQueueEle;
TCPIP_LOCAL VAR(TcpIp_SizeOfTcpRetryQElementType, TCPIP_VAR_NOINIT) TcpIp_Tcp_NumFreeRetryQEle;

#if (TCPIP_SUPPORT_TCP_RX_OOO == STD_ON)
TCPIP_LOCAL VAR(TcpIp_SizeOfTcpOooQElementType, TCPIP_VAR_NOINIT) TcpIp_Tcp_OooNumFreeElements;
TCPIP_LOCAL VAR(TcpIp_SizeOfTcpOooQElementType, TCPIP_VAR_NOINIT) TcpIp_Tcp_OooFirstFreeEleIdx;
#endif

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define TCPIP_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

TCPIP_LOCAL VAR(uint32, TCPIP_VAR_NOINIT) TcpIp_Tcp_GlobalTimestamp;  /* MainFunction counter */

#define TCPIP_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define TCPIP_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define TCPIP_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define TCPIP_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

TCPIP_LOCAL VAR(uint8, TCPIP_VAR_NOINIT) TcpIp_Tcp_RstTxQueueReadPos;
TCPIP_LOCAL VAR(uint8, TCPIP_VAR_NOINIT) TcpIp_Tcp_RstTxQueueWritePos;
TCPIP_LOCAL VAR(uint8, TCPIP_VAR_NOINIT) TcpIp_Tcp_RstTxQueueFillNum;


#define TCPIP_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  TcpIp_Tcp_OpenActive()
 *********************************************************************************************************************/
/*! \brief         Active open of a TCP connection.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     Domain              Domain of the remote host
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_OpenActive(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  TcpIp_DomainType           Domain);

/**********************************************************************************************************************
 *  TcpIp_Tcp_OpenPassive()
 *********************************************************************************************************************/
/*! \brief         Passive open of a TCP connection.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_OpenPassive(
  TcpIp_SocketTcpDynIterType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleListenSocketClose
 *********************************************************************************************************************/
/*! \brief         Closes partly established connections and removes reference from accepted sockets to listen socket.
 *  \details       A server socket was closed. Now close all sockets that are about to establish a connection to this
 *                 server socket. These sockets are not yet known to the server socket owner.
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VHandleListenSocketClose(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VReleaseAssignedBuffers()
 *********************************************************************************************************************/
/*! \brief         Releases the rx and tx buffers assigned to a TCP socket.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VReleaseAssignedBuffers(
  TcpIp_SocketTcpDynIterType SocketTcpIdx);

#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VSetSockOpt_KeepAliveOptions
 *********************************************************************************************************************/
/*! \brief         Sets TCP socket option for the feature 'keep alive'.
 *  \details       -
 *  \param[in]     SocketTcpIdx           Index of a TCP socket
 *                                        CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     OptName                Option name. Valid option identifiers are:
 *                                          TCPIP_PARAMID_TCP_KEEPALIVE,
 *                                          TCPIP_PARAMID_TCP_KEEPALIVE_INTERVAL,
 *                                          TCPIP_PARAMID_TCP_KEEPALIVE_PROBES_MAX,
 *                                          TCPIP_PARAMID_TCP_KEEPALIVE_TIME
 *  \param[in]     OptValPtr              Option parameter
 *  \return        E_OK                   Socket option change
 *  \return        E_NOT_OK               Socket option change request failed
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VSetSockOpt_KeepAliveOptions(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8                        OptName,
  TCPIP_P2C(uint8)             OptValPtr);
#endif

#if (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VSetSockOpt_UserTimeoutOptions
 *********************************************************************************************************************/
/*! \brief         Sets TCP socket option for the feature 'user timeout'.
 *  \details       -
 *  \param[in]     SocketTcpIdx           Index of a TCP socket
 *                                        CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     OptName                Option name.  Valid option identifiers are:
 *                                          TCPIP_PARAMID_V_TCP_UTOUPDATE,
 *                                          TCPIP_PARAMID_V_TCP_UTOENABLED,
 *                                          TCPIP_PARAMID_V_TCP_UTOCHANGEABLE
 *  \param[in]     OptValPtr              Option parameter
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSetSockOpt_UserTimeoutOptions(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8                        OptName,
  TCPIP_P2C(uint8)             OptValPtr);
#endif

/**********************************************************************************************************************
 *  TcpIp_Tcp_VCheckRecChecksum
 *********************************************************************************************************************/
/*! \brief         Check received TCP checksum.
 *  \details       -
 *  \param[in]     RxSockRemAddrPtr      Pointer to the remote socket struct
 *  \param[in]     RxSockLocAddrPtr      Pointer to the local socket struct
 *  \param[in]     DataPtr               Pointer to the received data
 *  \param[in]     LenByte               Length of received data in bytes
 *  \return        E_OK                  Checksum was sucessfully validated or already validated by the lower layer
 *  \return        E_NOT_OK              Checksum is invalid
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VCheckRecChecksum(
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TCPIP_P2C(uint8)                  DataPtr,
  uint16                            LenByte);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmit
 *********************************************************************************************************************/
/*! \brief         Sends pending elements and updates transmission timings.
 *  \details       -
 *  \param[in]     SocketTcpIdx           Index of a TCP socket.
 *                                        CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \return        E_OK                   Transmission could be processed
 *  \return        E_NOT_OK               Socket was closed for user timeout reasons
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VTransmit(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VCloseConnectionIfNotAcked
 *********************************************************************************************************************/
/*! \brief         Closes a connection if user timeout has expired.
 *  \details       Checks user timeout of oldest element in retry queue and closes connection if timeout has exceeded.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket
 *                                       CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \return        E_OK                  connection is still open
 *  \return        E_NOT_OK              connection closed
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VCloseConnectionIfNotAcked(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VSendPendingElements
 *********************************************************************************************************************/
/*! \brief         Sends pending elements if they have to be (re-)transmitted.
 *  \details       Iterates over all elements in retry queue and sends them if necessary.
 *  \param[in]     SocketTcpIdx                Index of a TCP socket.
 *                                             CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in,out] DataSegmentSentPtr          Pointer to variable indicating if the segment has been sent
 *  \param[in,out] SetNewRtoPendingPtr         Pointer to variable indicating if a new RTO is pending
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSendPendingElements(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(boolean) DataSegmentSentPtr,
  TCPIP_P2V(boolean) SetNewRtoPendingPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VSendPendingElements_CheckIfSegmentFitsInWindow
 *********************************************************************************************************************/
/*! \brief         Checks if the current element fits into the send window
 *  \details       Eventually this function creates a zero-window probe if the window is closed.
 *  \param[in]     SocketTcpIdx                Index of a TCP socket.
 *                                             CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     TxRetrQueueElePtr          Pointer to the current retry queue element
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(boolean, TCPIP_CODE) TcpIp_Tcp_VSendPendingElements_CheckIfSegmentFitsInWindow(
  TcpIp_SizeOfSocketTcpDynType         SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_TxRetrQueueType) TxRetrQueueElePtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VSendPendingElements_UpdateRetransmitTiming
 *********************************************************************************************************************/
/*! \brief         Updates the retransmit timing.
 *  \details       If only one segment with no data is in the retry queue this element eventually can be removed.
 *  \param[in]     SocketTcpIdx                Index of a TCP socket.
 *                                             CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in,out] TxRetrQueueElePtr           Pointer to the current retry queue element
 *  \param[in,out] SetNewRtoPendingPtr         Pointer to a variable inidcating if a new value for RTO pending has been set
 *  \pre           -
 *  \context       TASK
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSendPendingElements_UpdateRetransmitTiming(
  TcpIp_SizeOfSocketTcpDynType         SocketTcpIdx,
  TCPIP_P2V(TcpIp_Tcp_TxRetrQueueType) TxRetrQueueElePtr,
  TCPIP_P2V(boolean)                   SetNewRtoPendingPtr);

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VUpdateCwndParamsForTransmission
 *********************************************************************************************************************/
/*! \brief         Updates cwnd parameters.
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     TxRetrQueueElePtr    Pointer to the relevant retry queue
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VUpdateCwndParamsForTransmission(
  TcpIp_SizeOfSocketTcpDynType         SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_TxRetrQueueType) TxRetrQueueElePtr);
#endif

/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegmentAndUpdateSndNxt
 *********************************************************************************************************************/
/*! \brief         Transmits a segment and updates SndNxt value.
 *  \details       It is considered if the sement already has been noted in a SACK option or not.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in,out] TxRetrQueueElePtr     Pointer to the relevant retry queue
 *  \param[in,out] DataSegmentSentPtr    Pointer to info if segment was sent
 *  \return        E_OK                  Segment could be sent, or SackFlag was already not equal to 0
 *  \return        E_NOT_OK              Segment could not be sent
 *  \pre           -
 *  \context       TASK
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VTransmitSegmentAndUpdateSndNxt(
  TcpIp_SizeOfSocketTcpDynType         SocketTcpIdx,
  TCPIP_P2V(TcpIp_Tcp_TxRetrQueueType) TxRetrQueueElePtr,
  TCPIP_P2V(boolean)                   DataSegmentSentPtr);

/**********************************************************************************************************************
*  TcpIp_Tcp_VCopyTxDataIndirect()
*********************************************************************************************************************/
/*! \brief         Call the socket owner's CopyTxData function, split the function call if the provided TCP buffer needs
 *                 a wraparound for its circular buffer.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     DstChunk1Ptr        Pointer to the first memory section inside the TCP TxBuffer
 *  \param[in]     DstChunk1Len        Length of the first memory section
 *  \param[in]     DstChunk2Ptr        Pointer to the second memory section inside the TCP TxBuffer (if needed).
 *                                     DstChunk2Ptr may be NULL_PTR if DstChunk1Len == *LengthPtr.
 *  \param[in]     LengthPtr           Total length of the data that shall be copied by the socket owner. This length can
 *                                     be reduced by the socket owner if the socket owner decides that less data shall be
 *                                     sent than requested earlier.
 *                                     CONSTRAINT:  *LengthPtr >= DstChunk1Len
 *  \return        E_OK                copying the data was successfull
 *  \return        E_NOT_OK            there was an error in the copy process
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VCopyTxDataIndirect(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8)             DstChunk1Ptr,
  uint16                       DstChunk1Len,
  TCPIP_P2V(uint8)             DstChunk2Ptr,
  TCPIP_P2V(uint32)            LengthPtr);

/**********************************************************************************************************************
*  TcpIp_Tcp_VCopyDataFromTcpUser()
*********************************************************************************************************************/
/*! \brief         Copy the tx data from the user either by directly copying the provided data or by calling the users
 *                 CopyTxData function.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     DataPtr             Pointer to the data provided by the socket owner
 *  \param[in]     LengthPtr           Length of the data that shall be transmitted
 *                                     CONSTRAINT: [0 < *LengthPtr <= TcpIp_GetTcpTxBufferLengthOfTcpTxBufferDesc(TcpTxBufferDescIdx)]
 *                                     BufIdx = TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx).
 *  \return        E_OK                copying the data was successfull
 *  \return        E_NOT_OK            there was an error in the copy process
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VCopyDataFromTcpUser(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(uint8)             DataPtr,
  TCPIP_P2V(uint32)            LengthPtr);


/**********************************************************************************************************************
 *  TcpIp_Tcp_VFinalizeTxSegment
 *********************************************************************************************************************/
/*! \brief         Finializes a TCP segment.
 *  \details       Checks if a TxRetryQueue element is available, and then uses / allocates it.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \return        E_OK                  Finalization succeeded
 *  \return        E_NOT_OK              Finalization failed
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \note          Finialize _one_ TCP segment in the TxRetrQueue for transmission. The buffer was filled before.
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VFinalizeTxSegment(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VFinalizeTxSegment_SetFlagsAndKeepAlive
 *********************************************************************************************************************/
/*! \brief         Sets send flags and triggers keep alive mechanism.
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in,out] SegmentFlagsPtr       Pointer to the send flags
 *                                       Flags value is updated if RST flag is set or for any segment of a TCP
 *                                         connection but the very first SYN segment
 *  \return        E_OK                  Finalization succeeded. There is at least one free retry queue element
 *                                         available.
 *  \return        E_NOT_OK              Finalization failed because no free retry queue element is available.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VFinalizeTxSegment_SetFlagsAndKeepAlive(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8) SegmentFlagsPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VFinalizeTxSegment_CreateRetryQElement
 *********************************************************************************************************************/
/*! \brief         Creates a new retry queue element and appends it to the queue.
 *  \details       -
 *  \param[in]     SocketTcpIdx            Index of a TCP socket
 *                                         CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[out]    AddedRetryQElementPtr   Pointer to the new retry queue element
 *  \param[in]     SegmentFlags            Send flags
 *  \pre           This function must not be called if TcpIp_Tcp_NumFreeRetryQEle is 0.
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VFinalizeTxSegment_CreateRetryQElement(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(TcpIp_Tcp_TxRetrQueueType) *AddedRetryQElementPtr,
  uint8 SegmentFlags);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VFinalizeTxSegment_QueueDataForSending
 *********************************************************************************************************************/
/*! \brief         Queues data for sending (marks data to be queued and reduces length of unqueued data)
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[out]    NewRetryQElementPtr   Pointer to the retry queue element
 *  \param[in]     SegmentFlags          Send flags
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VFinalizeTxSegment_QueueDataForSending(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(TcpIp_Tcp_TxRetrQueueType) NewRetryQElementPtr,
  uint8                                SegmentFlags);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment
 *********************************************************************************************************************/
/*! \brief         Sends a TCP segment with data previously stored in the Tcp TxBuffer.
 *  \details       Requests a buffer from the IP layer and fills it with TCP header and data.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     Flags                 Flags that shall be sent
 *  \param[in]     SeqNo                 Sequence number of the segment to be sent
 *  \param[in]     OneTimeOptions        Options that shall be sent only in this segment
 *  \param[in]     DataStartIdx          Start index of the data in the TxBuffer that shall be sent
 *  \param[in]     DataLenByte           Length of the data that shall be sent
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8                        Flags,
  uint32                       SeqNo,
  uint8                        OneTimeOptions,
  TcpIp_SizeOfTcpTxBufferType  DataStartIdx,
  TcpIp_SizeOfTcpTxBufferType  DataLenByte);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment_CalcHeaderLen
 *********************************************************************************************************************/
/*! \brief         Calculates the length of the TCP header and determines the number of selective acknowledgment
 *                 elements if enabled.
 *  \details       Calculate TCP header length (based on required options).
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     Flags                 Flags that shall be sent
 *  \param[in]     OneTimeOptions        Options that shall be sent only in this segment
 *  \param[out]    SackNumPtr            Pointer to the number of SACK elements that will be sent with this segment
 *  \param[out]    HeaderLenBytePtr      Pointer to the header length that will be sent in this segment
 *                                       CONSTRAINT:  *HeaderLenBytePtr = [20..60]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment_CalcHeaderLen(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8            Flags,
  uint8            OneTimeOptions,
  TCPIP_P2V(uint8) SackNumPtr,
  TCPIP_P2V(uint8) HeaderLenBytePtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment_RequestIpTxBuffer
 *********************************************************************************************************************/
/*! \brief         Requests a tx buffer from IpV4 or IpV6.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[out]    IpTxReqestDescrPtr  Pointer to the IP tx request descriptor (is needed for later transmit call)
 *  \param[in,out] TgtLenPtr           in: Pointer to the length of the data (TCP header and payload) that shall be sent
 *                                     out: length of the buffer provided by IP
 *  \param[out]    PayloadPtr          Start index of the data in the TxBuffer that shall be sent
 *  \return        E_OK                TxBuffer could be provided
 *  \return        E_NOT_OK            TxBuffer could not be provided
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment_RequestIpTxBuffer(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(TcpIp_IpTxRequestDescriptorType) IpTxReqestDescrPtr,
  TCPIP_P2V(uint16) TgtLenPtr,
  TCPIP_P2V(uint8) *PayloadPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment_CopyDataToIpTxBuffer
 *********************************************************************************************************************/
/*! \brief         Copies TCP payload to the IP buffer.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     DataStartIdx        Start index of the data in the TxBuffer that shall be sent
 *  \param[in]     DataLen             Length of the data that shall be sent
 *  \param[out]    IpPayloadPtr        Pointer to the IP tx buffer. At least (TcpHeaderLen + DataLen) bytes must be
 *                                       available at IpPayloadPtr.
 *  \param[in]     TcpHeaderLen        Length of the TCP header including options
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment_CopyDataToIpTxBuffer(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TcpIp_SizeOfTcpTxBufferType  DataStartIdx,
  TcpIp_SizeOfTcpTxBufferType  DataLen,
  TCPIP_P2V(uint8) IpPayloadPtr,
  uint8 TcpHeaderLen);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment_WriteHeaderElements
 *********************************************************************************************************************/
/*! \brief         Copies the TCP header to the IP buffer.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[out]    TcpHdrPtr           Pointer where the TCP header shall be written to, 20 bytes will be written.
 *  \param[in]     DataLen             Length of the TCP payload that shall be sent
 *  \param[in]     SeqNo               Sequence number of the segment to be sent
 *  \param[in]     Flags               Flags that shall be sent
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment_WriteHeaderElements(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8) TcpHdrPtr,
  TcpIp_SizeOfTcpTxBufferType DataLen,
  uint32 SeqNo,
  uint8 Flags);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment_WriteHeaderOptions
 *********************************************************************************************************************/
/*! \brief         Copies TCP header options to the target buffer.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[out]    TcpHdrPtr           Pointer where the TCP header shall be written to. Up to 40 bytes will be written
 *                                       starting at &TcpHdrPtr[20], the amount of option data depends on the options
 *                                       that shall be sent.
 *                                       'maximum segment size' option needs 6 bytes
 *                                       'timestamp' option needs 12 bytes
 *                                       'user timeout' option needs 4 bytes
 *                                       'selective acknowledgment permit' option needs 4 bytes
 *                                       'selective acknowledgment' option needs (4 + (SackNum * 8)) bytes
 *  \param[in]     OneTimeOptions      Options that shall be sent only in this segment
 *  \param[in]     SackNum             Number of SACK elements that will be sent with this segment
 *  \param[in]     Flags               Flags that shall be sent
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment_WriteHeaderOptions(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8) TcpHdrPtr,
  uint8 OneTimeOptions,
  uint8 SackNum,
  uint8 Flags);

#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment_WriteHeaderOptions_Sack
 *********************************************************************************************************************/
/*! \brief         Copies TCP header options 'selective ack permit' and 'selective ack' to the target buffer.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     TcpHdrOptPtr        Pointer where this TCP header option shall be written to.
 *                                       SACK_PERMIT: 4 bytes will be written
 *                                       SACK: (4 + (SackNum * 8)) bytes will be written
 *  \param[in]     OneTimeOptions      Options that shall be sent only in this segment
 *  \param[in]     SackNum             Number of SACK elements that will be sent with this segment
 *  \return        Length of the added SACK option
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(uint8, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment_WriteHeaderOptions_Sack(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8) TcpHdrOptPtr,
  uint8 OneTimeOptions,
  uint8 SackNum);
#endif

/**********************************************************************************************************************
 *  TcpIp_Tcp_VCloseSocketAndReleaseResources
 *********************************************************************************************************************/
/*! \brief         Closes a socket, relases resources and issues state change.
 *  \details       The callback is conducted for the given socket index and socket user.
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     State               New socket state
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VCloseSocketAndReleaseResources(
  TcpIp_SocketTcpDynIterType        SocketTcpIdx,
  TcpIp_StateType                   State);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRestartSock
 *********************************************************************************************************************/
/*! \brief         Sets socket state to CLOSED, releases assigned RX and TX buffers, clears the out of order queue and calls 'TcpIp_Tcp_VInitSock()'.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRestartSock(
  TcpIp_SocketTcpDynIterType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VInitSock
 *********************************************************************************************************************/
/*! \brief         Initializes variables for one socket
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VInitSock(
  TcpIp_SocketTcpDynIterType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VSendReset
 *********************************************************************************************************************/
/*! \brief         Requests sending a TCP reset and deletes not queued tx elements.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1] or TCPIP_TCP_INV_IDX
 *  \param[in]     IpAddrIdx           Local IP address identifier
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     RemSockPtr          Pointer to the remote socket address
 *  \param[in]     LocSockPtr          Pointer to the local socket address
 *  \param[in]     SeqNo               Sequence number
 *  \param[in]     AckNo               Acknowledge number
 *  \param[in]     Flags               Flags to be sent
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSendReset(
  TcpIp_SocketTcpDynIterType        SocketTcpIdx,
  TcpIp_LocalAddrIterType           IpAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RemSockPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) LocSockPtr,
  uint32                            SeqNo,
  uint32                            AckNo,
  uint8                             Flags);


/**********************************************************************************************************************
 *  TcpIp_Tcp_VDelTxQueue
 *********************************************************************************************************************/
/*! \brief         Deletes the tx queue of a socket.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VDelTxQueue(
  TcpIp_SocketTcpDynIterType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VSendFlags
 *********************************************************************************************************************/
/*! \brief         Triggers the transmission of TCP flags.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     Flags               TCP flags (fin, ack, ...)
 *                                     CONSTRAINT:  (Flags & TCPIP_TCP_CODE_BIT_RST) == 0
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSendFlags(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  uint8 Flags);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitResets
 *********************************************************************************************************************/
/*! \brief         Sends pending TCP resets.
 *  \details       Calling this function will send all queued reset messages.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VTransmitResets(void);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions
 *********************************************************************************************************************/
/*! \brief         Handles received TCP options.
 *  \details       The function is call in the context of the RxIndication.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     RxSockRemAddrPtr      Pointer to the remote socket address
 *  \param[in]     RxSockLocAddrPtr      Pointer to the local socket address
 *  \param[in]     SegmentDescriptorPtr  Pointer to the descriptor of the received message
 *  \pre           The calling function has to ensure that the TCP header contains TCP options.
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_MaxSegSize
 *********************************************************************************************************************/
/*! \brief         Handles received TCP option 'Maximum Message Size'.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *  \param[in]     OptPtr              Pointer to the received option
 *  \param[in]     OptLen              Length of the received option
 *  \return        E_NOT_OK            Reading the option caused an error
 *  \return        E_OK                The option was successfully read
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_MaxSegSize(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(uint8)             OptPtr,
  uint8                        OptLen);

#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_SackPermit
 *********************************************************************************************************************/
/*! \brief         Handles received TCP option 'Sack Permit'.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     OptLen              Length of the received option
 *  \return        E_NOT_OK            Reading the option caused an error
 *  \return        E_OK                The option was successfully read
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_SackPermit(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8 OptLen);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_Sack
 *********************************************************************************************************************/
/*! \brief         Handles received TCP option 'Selective Ack'.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     OptPtr              Pointer to the received option
 *  \param[in]     OptLen              Length of the received option
 *  \return        E_NOT_OK            Reading the option caused an error
 *  \return        E_OK                The option was successfully read
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_Sack(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(uint8)             OptPtr,
  uint8                        OptLen);
#endif

#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_Timestamp
 *********************************************************************************************************************/
/*! \brief         Handles received TCP option 'Timestamp'.
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the descriptor of the received message
 *  \param[in]     OptPtr                Pointer to the received option
 *  \param[in]     OptLen                Length of the received option
 *  \return        E_NOT_OK              Reading the option caused an error
 *  \return        E_OK                  The option was successfully read
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_Timestamp(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr,
  TCPIP_P2C(uint8)                           OptPtr,
  uint8                                      OptLen);
#endif

#if (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_UserTimeout
 *********************************************************************************************************************/
/*! \brief         Handles received TCP option 'UserTimeout'.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     OptPtr              Pointer to the received option
 *  \param[in]     OptLen              Length of the received option
 *  \return        E_NOT_OK            Reading the option caused an error
 *  \return        E_OK                The option was successfully read
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_UserTimeout(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(uint8)             OptPtr,
  uint8                        OptLen);
#endif

/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_Default
 *********************************************************************************************************************/
/*! \brief         Handles unknown received TCP options.
 *  \details       Ignores unknown options and fails if the general option format is wrong
 *  \param[in]     ByteIdx             Read postion for the current option
 *                                     CONSTRAINT: ByteIdx <= AllOptionsLen
 *  \param[in]     OptLen              Total length of the current option
 *  \param[in]     AllOptionsLen       Total length of all options in the TCP header
 *  \return        E_NOT_OK            Reading the option caused an error
 *  \return        E_OK                The unknown option was successfully read and ignored
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_Default(
  uint8 ByteIdx,
  uint8 OptLen,
  uint8 AllOptionsLen);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_ResetConnection
 *********************************************************************************************************************/
/*! \brief         Closes the connection after receiving an erroneous TCP option.
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     RxSockRemAddrPtr      pointer to the remote socket address
 *  \param[in]     RxSockLocAddrPtr      pointer to the local socket address
 *  \param[in]     SegmentDescriptorPtr  pointer to the descriptor of the received message
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_ResetConnection(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

#if ((TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON) || (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON))
/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_SetBlockedOptLen
 *********************************************************************************************************************/
/*! \brief         Reserves the blocked option length for later TCP option transmission.
 *  \details       If using the TCP timestamp option or the selctive acknowledgment option has been negotiated, the data
 *                 length that can be sent per segment is reduced.
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_SetBlockedOptLen(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);
#endif

/**********************************************************************************************************************
 *  TcpIp_Tcp_VFreeFirstRetrQueueEle
 *********************************************************************************************************************/
/*! \brief         Removes first element from socket's retransmit queue and adds element to free-list.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           Interrupts MUST be locked during call.
 *  \pre           RetryQueue must not be empty.
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VFreeFirstRetrQueueEle(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VFreeAckedReqAndRetrElements
 *********************************************************************************************************************/
/*! \brief         Removes acknowledged elements from the tx retry queue an calls TxConfirmation of the socket owner.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegAckNo            Latest ACK number
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VFreeAckedReqAndRetrElements(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint32                       SegAckNo);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VQueueRemReqData
 *********************************************************************************************************************/
/*! \brief         Creates new segments for sending.
 *  \details       The data was previously put into the TxBuffer by the transmit API TcpIp_TcpTransmit or by TLS using
 *                 the internal API TcpIp_TcpTransmitInternal.
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VQueueRemReqData(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);


/**********************************************************************************************************************
 *  TcpIp_Tcp_VDropEndEleInRetrQueue
 *********************************************************************************************************************/
/*! \brief         Drops elements at the end of the socket's TxRetrQueue.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     NumDropEle          Number of elements that shall be dropped
 *                                     CONSTRAINT: [0..TcpIp_GetRetryQFillNumOfSocketTcpDyn()]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VDropEndEleInRetrQueue(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  uint8 NumDropEle);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VUnqueueDataInTxReq
 *********************************************************************************************************************/
/*! \brief         Un-queues data from the socket's TxReqArray.
 *  \details       -
 *  \param[in]     SocketTcpIdx         Index of a TCP socket
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     UnqueueLen           Data Length that shall be un-queued
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VUnqueueDataInTxReq(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  TcpIp_SizeOfTcpTxBufferType UnqueueLen);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainStateHandling
 *********************************************************************************************************************/
/*! \brief         Sub-function of MainFunction, proceed the socket reset and state handling.
 *  \details       -
 *  \param[in]     SocketTcpIdx         Index of a TCP socket
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainStateHandling(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);


/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainStateHandling_Reset
 *********************************************************************************************************************/
/*! \brief         Proceed the handling of received RST flags.
 *  \details       Sub-function of TcpIp_Tcp_VMainStateHandling.
 *  \param[in]     SocketTcpIdx         Index of a TCP socket
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainStateHandling_Reset(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainStateHandling_Timewait
 *********************************************************************************************************************/
/*! \brief         Proceed the socket state handling in state TIMEWAIT.
 *  \details       Sub-function of TcpIp_Tcp_VMainStateHandling.
 *  \param[in]     SocketTcpIdx         Index of a TCP socket
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainStateHandling_Timewait(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainRxDataForwarding
 *********************************************************************************************************************/
/*! \brief         Forward received data to the socket owner, decoupled in the MainFunction.
 *  \details       -
 *  \param[in]     SocketTcpIdx         Index of a TCP socket
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     MaxLenToForward      Maximum length of data that shall be forwarded to the socket owner
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainRxDataForwarding(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint16 MaxLenToForward);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainIdleTimeoutHandling
 *********************************************************************************************************************/
/*! \brief         Proceed TCP keep alive and idle timeout handling.
 *  \details       -
 *  \param[in]     SocketTcpIdx         Index of a TCP socket
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainIdleTimeoutHandling(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VFinWait2TimeoutHandling
 *********************************************************************************************************************/
/*! \brief         Handle FINWAIT-2 timeout
 *  \details       If FINWAIT-2 timeout is configured to a non-zero value, handle expiry
 *                 If timeout has expired, abort Tcp connection
 *  \param[in]     SocketTcpIdx       Index of a TCP socket
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VFinWait2TimeoutHandling(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VSplitFirstRetrQueueEle
 *********************************************************************************************************************/
/*! \brief         Split the first RetrQueueEle to fit into the send window (prepare).
 *  \details       If there are spare retry queue elements, the first element of the connections retry queue is split
 *                 into two parts, otherwise the first element is reduced in its size and the remaining data is un-queued.
 *  \param[in]     SocketTcpIdx       Index of a TCP socket
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSplitFirstRetrQueueEle(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VSplitFirstRetrQueueEle_Split
 *********************************************************************************************************************/
/*! \brief         Split the first RetrQueueEle to fit into the send window.
 *  \details       If there are spare retry queue elements, the first element of the connections retry queue is split
 *                 into two parts, otherwise the first element is reduced in its size and the remaining data is un-queued.
 *  \param[in]     SocketTcpIdx       Index of a TCP socket
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     NewEleIdx          Index of the new retry queue element
 *  \param[in]     SizePartOne        Size if the first part of the splitted retry queue element
 *  \pre           Must not be called if retry queue of socket is empty.
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSplitFirstRetrQueueEle_Split(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TcpIp_SizeOfTcpRetryQElementType NewEleIdx,
  uint16 SizePartOne);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainTxDataHandling
 *********************************************************************************************************************/
/*! \brief         Performs the socket tx data handling.
 *  \details       -
 *  \param[in]     SocketTcpIdx       Index of a TCP socket
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainTxDataHandling(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

#if (TCPIP_SUPPORT_TCP_NAGLE_TIMEOUT == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainTxDataHandling_TxIfNagleEnabled
 *********************************************************************************************************************/
/*! \brief         Updates nagle parameters and send segments.
 *  \details       Called by TcpIp_Tcp_VMainTxDataHandling.
 *  \param[in]     SocketTcpIdx       Index of a TCP socket
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainTxDataHandling_TxIfNagleEnabled(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);
#endif

#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VUpdateRttVars
 *********************************************************************************************************************/
/*! \brief         Updates RTT (round-trip time) dependent variables.
 *  \details       Use the elements RTT to update SRTT (smoothed round-trip time), RTTVAR (RTT variation) and
 *                 RTO (retransmission timeout). Calculations according to RFC 2988. A counter increased in every call
 *                 of the TcpMainFunction is used as the time base for all round-trip time dependent variables. So the
 *                 clock granularity in milli-seconds is TCPIP_MAIN_FCT_PERIOD_MSEC.
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     ElementRtt          Round Trip Time of one element [cycles]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VUpdateRttVars(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint32 ElementRtt);
#endif  /* (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON) */

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VIncAckSumN
 *********************************************************************************************************************/
/*! \brief         Increases the sum of acknowledged bytes.
 *  \details       -
 *  \param[in]     SocketTcpIdx         Index of a TCP socket
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     IncSize              Size to add (acked bytes)
 *  \pre           The socket is in state 'congestion avoidance'
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different sockets
 *  \note          This function is only called while the socket is in state 'congestion avoidance'.
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VIncAckSumN(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint32 IncSize);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VIncCwnd
 *********************************************************************************************************************/
/*! \brief         Increase the congestion window.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     IncSize             Size to add (acked bytes)
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different sockets
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VIncCwnd(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  uint32                     IncSize);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VSetSsthreshEqu4
 *********************************************************************************************************************/
/*! \brief         Sets Ssthresh according to equation (4) in RFC5681.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different sockets
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSetSsthreshEqu4(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VCalcFlightSize
 *********************************************************************************************************************/
/*! \brief         Calculates the current fligth size according to RFC5681.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \return        returns the FligthSize
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE for different sockets
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(uint32, TCPIP_CODE) TcpIp_Tcp_VCalcFlightSize(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);
#endif  /* (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON) */

#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VKeepAliveTrigger
 *********************************************************************************************************************/
/*! \brief         Resets all Keep-Alive counters for a TCP connection.
 *                 Should be triggered everytime when data has been transferred over the connection.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of the TCP connection.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VKeepAliveTrigger(
  TcpIp_SocketTcpDynIterType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VKeepAliveReset
 *********************************************************************************************************************/
/*! \brief         Turns off the Keep-Alive mechanism for a TCP socket and resets all parameters to their default values.
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of the TCP connection.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VKeepAliveReset(
  TcpIp_SocketTcpDynIterType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VKeepAliveCopyParameters
 *********************************************************************************************************************/
/*! \brief         Copies TCP keep-alive socket parameters to another socket.
 *  \details       -
 *  \param[in]     SocketTcpSrcIdx     Index of the socket from which the parameters shall be copied.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SocketTcpDstIdx     Index of the socket to which the parameters shall be copied.
 *                                     CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VKeepAliveCopyParameters(
  TcpIp_SocketTcpDynIterType   SocketTcpSrcIdx,
  TcpIp_SizeOfSocketTcpDynType SocketTcpDstIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitKeepAliveProbe
 *********************************************************************************************************************/
/*! \brief         Transmits an ACK-only segment with current sequence number decremented by one. (TCP keep alive segment)
 *  \details       -
 *  \param[in]     SocketTcpIdx     Index of the TCP connection.
 *                                  CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \return        E_OK             Keep-alive segment transmitted.
 *  \return        E_OK             Keep-alive segment not transmitted.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VTransmitKeepAliveProbe(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);
#endif

/**********************************************************************************************************************
 *  TcpIp_Tcp_VDuplicateSocket
 *********************************************************************************************************************/
/*! \brief         Get a new socket for accepting an incoming connection request and duplicate the relevant parameters
 *                 from the listen socket.
 *  \details       -
 *  \param[in]     ListenSocketTcpIdx    Index of the TCP listen socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     LocalAddrIdx          Local address identifier
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     RxSockRemAddrPtr      Pointer to the remote socket address
 *  \return                              SocketTcpIdx of the new socket or TCPIP_TCP_INV_IDX if socket could not be duplicated
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(TcpIp_SizeOfSocketTcpDynType, TCPIP_CODE) TcpIp_Tcp_VDuplicateSocket(
  TcpIp_SizeOfSocketTcpDynType      ListenSocketTcpIdx,
  TcpIp_LocalAddrIterType           LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr);

/**********************************************************************************************************************
 *  TcpIp_AddWithWrapAround32
 *********************************************************************************************************************/
/*! \brief         Increments a 32-bit variable up to (valueCount-1) with wrap-around.
 *  \details       Administers a circular buffer where valueCount is the number of elements.
 *                 Index values are zero based thus the value valueCount is the first invalid value of the sum 'value+incValue'.
 *  \param[in]     Value            Value that shall be incremented.
 *  \param[in]     IncValue         Value that shall be added.
 *  \param[in]     ValueCount       Number of valid values. ([0...valueCount-1])
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(uint32, TCPIP_CODE) TcpIp_AddWithWrapAround32(
  uint32 Value,
  uint32 IncValue,
  uint32 ValueCount);

/**********************************************************************************************************************
 *  TcpIp_IncTxBufIdx
 *********************************************************************************************************************/
/*! \brief         Increments a buffer access index variable up to bufferSize with wrap-around.
 *  \details       Administers a circular buffer where bufferSize is the number of elements of this buffer.
 *  \param[in]     TcpTxBufferDescIdx    Index of the tx buffer
 *                                       CONSTRAINT:  [0..TcpIp_GetSizeOfTcpTxBufferDesc()-1]
 *  \param[in]     BufferIdx             Index of the buffer element, some value between BufferStartIdx and BufferEndIdx.
 *                                       A global index range is used for all tx buffers.
 *                                       CONSTRAINT: [TcpIp_GetTcpTxBufferStartIdxOfTcpTxBufferDesc(TcpTxBufferDescIdx) ..
 *                                                   (TcpIp_GetTcpTxBufferEndIdxOfTcpTxBufferDesc(TcpTxBufferDescIdx) -1)]
 *  \param[in]     IncValue              Value that shall be added to the BufferIdx.
 *                                       CONSTRAINT:  [0..TcpIp_GetTcpTxBufferLengthOfTcpTxBufferDesc(TcpTxBufferDescIdx)]
 *  \return        New buffer access position
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfTcpTxBufferType, TCPIP_CODE) TcpIp_IncTxBufIdx(
  TcpIp_SizeOfTcpTxBufferDescType TcpTxBufferDescIdx,
  TcpIp_SizeOfTcpTxBufferType     BufferIdx,
  TcpIp_SizeOfTcpTxBufferType     IncValue);

/**********************************************************************************************************************
*  TcpIp_IncRxBufIdx
**********************************************************************************************************************/
/*! \brief         Increments a buffer access index variable up to bufferSize with wrap-around.
 *  \details       Administers a circular buffer where bufferSize is the number of elements of this buffer.
 *  \param[in]     TcpRxBufferDescIdx    Index of the rx buffer
 *                                       CONSTRAINT:  [0..TcpIp_GetSizeOfTcpRxBufferDesc()-1]
 *  \param[in]     BufferIdx             Index of the buffer element, some value between BufferStartIdx and BufferEndIdx.
 *                                       A global index range is used for all rx buffers.
 *                                       CONSTRAINT: [TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx) ..
 *                                                   (TcpIp_GetTcpRxBufferEndIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx) -1)]
 *  \param[in]     IncValue              Value that shall be added to the BufferIdx.
 *                                       CONSTRAINT:  [0..TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(TcpRxBufferDescIdx)]
 *  \return        New buffer access position
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfTcpRxBufferType, TCPIP_CODE) TcpIp_IncRxBufIdx(
  TcpIp_SizeOfTcpRxBufferDescType TcpRxBufferDescIdx,
  TcpIp_SizeOfTcpRxBufferType     BufferIdx,
  TcpIp_SizeOfTcpRxBufferType     IncValue);

/**********************************************************************************************************************
*  TcpIp_Tcp_UpRxIndication
**********************************************************************************************************************/
/*! \brief         Call the upper layer rx indication
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     DataPtr             Pointer to the data
 *  \param[in]     DataLen             Length of the data
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_Tcp_UpRxIndication(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8) DataPtr,
  uint16           DataLen);


/**********************************************************************************************************************
 *  TcpIp_Tcp_VAssignBuffersToDuplicatedSocket
 *********************************************************************************************************************/
/*! \brief         Assings the buffers to the duplicated socket with the size that was requested for the ListenSocket.
 *  \details       -
 *  \param[in]     NewSocketTcpIdx       Index of the duplicated TCP socket
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     ListenSocketTcpIdx    Index of the TCP listen socket
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \return                              E_OK        Buffers could be assigned
 *  \return                              E_NOT_OK    Buffers could not be assigned
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VAssignBuffersToDuplicatedSocket(
  TcpIp_SizeOfSocketTcpDynType NewSocketTcpIdx,
  TcpIp_SizeOfSocketTcpDynType ListenSocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VInitVarsOfDuplicatedSocket
 *********************************************************************************************************************/
/*! \brief         Initializes variables for a duplicated socket.
 *  \details       Copy values from the ListenSocket or fill them with init values.
 *  \param[in]     NewSocketTcpIdx       Index of the duplicated TCP socket
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     ListenSocketTcpIdx    Index of the TCP listen socket
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     LocalAddrIdx          Local address identifier
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     RxSockRemAddrPtr      Pointer to the socket
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VInitVarsOfDuplicatedSocket(
  TcpIp_SizeOfSocketTcpDynType      NewSocketTcpIdx,
  TcpIp_SizeOfSocketTcpDynType      ListenSocketTcpIdx,
  TcpIp_LocalAddrIterType           LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VAcceptedSocketStateHandling()
 *********************************************************************************************************************/
/*! \brief         Advance socket state for duplicated socket.
 *  \details       -
 *  \param[in]     ListenSocketTcpIdx  Index of the listen TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     AcceptSocketTcpIdx  Index of the duplicated/accepted TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VAcceptedSocketStateHandling(
  TcpIp_SizeOfSocketTcpDynType ListenSocketTcpIdx,
  TcpIp_SizeOfSocketTcpDynType AcceptSocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VAssignRxBuffer
 *********************************************************************************************************************/
/*! \brief         Assign an rx buffer to the socket
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     RequestedBufferSize   Size of the buffer that shall be assigned
 *  \return        E_OK                  Buffer could be assigned
 *  \return        E_NOT_OK              Buffer could not be assigned
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VAssignRxBuffer(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint32                       RequestedBufferSize);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VAssignTxBuffer
 *********************************************************************************************************************/
/*! \brief         Assign a tx buffer to the socket
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     RequestedBufferSize   Size of the buffer that shall be assigned
 *  \return        E_OK                  Buffer could be assigned
 *  \return        E_NOT_OK              Buffer could not be assigned
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VAssignTxBuffer(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint32                       RequestedBufferSize);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VReadAndCheckTcpHeaderData
 *********************************************************************************************************************/
/*! \brief         Reads the information from the TCP header and checks them for consistency
 *  \details       -
 *  \param[in]     DataPtr               pointer to the received data
 *  \param[in]     LenByte               length of received data
 *  \param[out]    SegmentDescriptorPtr  pointer to the segment descriptor that shall be filled with information
 *  \return        E_OK                  Valid header data could be read from the input buffer
 *  \return        E_NOT_OK              Inconsistend header data found in the input buffer
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VReadAndCheckTcpHeaderData(
  TCPIP_P2V(uint8) DataPtr,
  uint16 LenByte,
  TCPIP_P2V(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRejectReceivedSegmentWithoutMatchingLocalSocket
 *********************************************************************************************************************/
/*! \brief         There is no local socket matching the received TCP segment, answer this segment with a RST.
 *  \details       -
 *  \param[in]     LocalAddrIdx          local address identifier
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     RxSockRemAddrPtr      pointer to the remote socket address
 *  \param[in]     RxSockLocAddrPtr      pointer to the local socket address
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor that shall be filled wiht information
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRejectReceivedSegmentWithoutMatchingLocalSocket(
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateListen
 *********************************************************************************************************************/
/*! \brief         Process the received message while being in socket state 'LISTEN'.
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     LocalAddrIdx          local address identifier
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     RxSockRemAddrPtr      pointer to remote socket address
 *  \param[in]     RxSockLocAddrPtr      pointer to local socket address
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateListen(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateSynSent
 *********************************************************************************************************************/
/*! \brief         Process the received message while being in socket state 'SYN_SENT'.
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     LocalAddrIdx          local address identifier
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     RxSockRemAddrPtr      pointer to remote socket address
 *  \param[in]     RxSockLocAddrPtr      pointer to local socket address
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \note          Markers 'first', 'second' ... are from TCP RFC
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateSynSent(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateSynSent_First
 *********************************************************************************************************************/
/*! \brief         Process the received message while being in socket state 'SYN_SENT', first part (according to RFC).
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     LocalAddrIdx          local address identifier
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     RxSockRemAddrPtr      pointer to remote socket address
 *  \param[in]     RxSockLocAddrPtr      pointer to local socket address
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \return        E_OK                  Message processing was successful
 *  \return        E_NOT_OK              Message processing resulted in an error, so the segment has to be dropped
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateSynSent_First(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateSynSent_Second
 *********************************************************************************************************************/
/*! \brief         Process the received message while being in socket state 'SYN_SENT', second part (according to RFC).
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \return        E_OK                  Message processing was successful
 *  \return        E_NOT_OK              A RST was received, so further processing of the segment has to be stopped
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateSynSent_Second(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateSynSent_Fourth
 *********************************************************************************************************************/
/*! \brief         Process the received message while being in socket state 'SYN_SENT', fourth part (according to RFC).
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     RxSockRemAddrPtr      pointer to remote socket address
 *  \param[in]     RxSockLocAddrPtr      pointer to local socket address
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateSynSent_Fourth(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers
 *********************************************************************************************************************/
/*! \brief         Process the received message while being in socket state 'SYNRCVD', 'ESTABLISHED' and higher.
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     LocalAddrIdx          local address identifier
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     RxSockRemAddrPtr      pointer to remote socket address
 *  \param[in]     RxSockLocAddrPtr      pointer to local socket address
 *  \param[in,out] SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2V(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_First
 *********************************************************************************************************************/
/*! \brief         Processing of received segments while being in states SYN_RCVD and higher, processing of first part
 *                 (according to RFC 793).
 *  \details       Called by TcpIp_Tcp_VRxIndicationStateOthers. Check if the segment is acceptable according to its
 *                 sequence number, otherwise drop the segment.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in,out] SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \return        E_OK                  message is acceptable
 *  \return        E_NOT_OK              message is not acceptable
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_First(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TCPIP_P2V(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Second
 *********************************************************************************************************************/
/*! \brief         Processing of received segments while being in states SYN_RCVD and higher, processing of second part
 *                 (according to RFC 793).
 *  \details       Called by TcpIp_Tcp_VRxIndicationStateOthers. Check if the RST bit is set.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \return        E_OK                  No RST flag was detected
 *  \return        E_NOT_OK              A RST flag was detected, so the socket gets closed
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Second(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fourth
 *********************************************************************************************************************/
/*! \brief         Processing of received segments while being in states SYN_RCVD and higher, processing of fourth part
 *                 (according to RFC 793).
 *  \details       Called by TcpIp_Tcp_VRxIndicationStateOthers. Close the socket if a SYN flag was received.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     LocalAddrIdx          local address identifier
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     RxSockRemAddrPtr      pointer to remote socket address
 *  \param[in]     RxSockLocAddrPtr      pointer to local socket address
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \return        E_OK                  No SYN flag was received, segment processing can be continued
 *  \return        E_NOT_OK              A SYN flag was received, so the socket gets closed
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fourth(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth
 *********************************************************************************************************************/
/*! \brief         Processing of received segments while being in states SYN_RCVD and higher, processing of fifth part
 *                 (according to RFC 793).
 *  \details       Check the ACK field and Enhance connection states and transmission timings.
 *                 Called by TcpIp_Tcp_VRxIndicationStateOthers.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     LocalAddrIdx          local address identifier
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     RxSockRemAddrPtr      pointer to remote socket address
 *  \param[in]     RxSockLocAddrPtr      pointer to local socket address
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_AckAndOpts
 *********************************************************************************************************************/
/*! \brief         Check the presence of the ACK flag and handle the TCP options.
 *  \details       Processing of received segments while being in states SYN_RCVD and higher.
 *                 Called by TcpIp_Tcp_VRxIndicationStateOthers_Fifth
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     RxSockRemAddrPtr      pointer to remote socket address
 *  \param[in]     RxSockLocAddrPtr      pointer to local socket address
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \return        E_OK                  no processing error occurred
 *  \return        E_NOT_OK              ACK flag is missing or error in the TCP header
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_AckAndOpts(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_SynRcvd
 *********************************************************************************************************************/
/*! \brief         Check if state can be enhanced to 'ESTABLISHED' and forward 'CONNECTED' event to the upper layer.
 *  \details       Processing of received segments while being in state SYN_RCVD.
 *                 Called by TcpIp_Tcp_VRxIndicationStateOthers_Fifth.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     LocalAddrIdx          local address identifier
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddr()-1]
 *  \param[in]     RxSockRemAddrPtr      pointer to remote socket address
 *  \param[in]     RxSockLocAddrPtr      pointer to local socket address
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \return        E_OK                  succeeded
 *  \return        E_NOT_OK              Socket has been closed
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_SynRcvd(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3
 *********************************************************************************************************************/
/*! \brief         Update timing and window values for the connection (including congestion control), and proceed the
 *                 closing of the socket if necessary.
 *  \details       Processing of received segments while being in states ESTABLISHED and higher.
 *                 Called by TcpIp_Tcp_VRxIndicationStateOthers_Fifth.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \return        E_OK                  Segment handling can be continued
 *  \return        E_NOT_OK              Segment is dropped, processing is stopped
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateRetransmitTimer1
 *********************************************************************************************************************/
/*! \brief         Update the retransmission timer acccording to the received segment.
 *  \details       Processing of received segments, sub-function of TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateRetransmitTimer1(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateCongestionControlNewData
 *********************************************************************************************************************/
/*! \brief         Upate congestion control parameters for new received data.
 *  \details       Processing of received segments, sub-function of TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateCongestionControlNewData(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateCongestionControlNoNewData
 *********************************************************************************************************************/
/*! \brief         Upate congestion control parameters without new received data.
 *  \details       Processing of received segments, sub-function of TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateCongestionControlNoNewData(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);
#endif

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateWindowAndKeepAlive
 *********************************************************************************************************************/
/*! \brief         Update send window and KeepAlive trigger, and eventually release retry queue elements.
 *  \details       Processing of received segments, sub-function of TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateWindowAndKeepAlive(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateRetransmitTimer2
 *********************************************************************************************************************/
/*! \brief         Update the retransmission timer acccording to the received segment.
 *  \details       Processing of received segments, sub-function of TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateRetransmitTimer2(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_AdvanceConnectionState
 *********************************************************************************************************************/
/*! \brief         Advance the TCP connection state.
 *  \details       Processing of received segments, sub-function of TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_AdvanceConnectionState(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_LastAck
 *********************************************************************************************************************/
/*! \brief         Finally close the socket if all conditions are fulfilled.
 *  \details       Processing of received segments while being in state LASTACK.
 *                 Called by TcpIp_Tcp_VRxIndicationStateOthers_Fifth.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_LastAck(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_TimeWait
 *********************************************************************************************************************/
/*! \brief         Handle received messages in state 'TIMEWAIT' even though no messages are expected. Just wait.
 *  \details       Processing of received segments while being in state TIMEWAIT.
 *                 Called by TcpIp_Tcp_VRxIndicationStateOthers_Fifth.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \return        E_OK                  Our FIN is acked
 *  \return        E_NOT_OK              Our FIN is not acked
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_TimeWait(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Sixth
 *********************************************************************************************************************/
/*! \brief         Checks that the 'urgent' bit is not set, otherwise drops the segment.
 *  \details       Processing of sixth part (according to RFC 793).
 *                 Called by TcpIp_Tcp_VRxIndicationStateOthers_Fifth.
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \return        E_OK                  No 'urgent' flag set in the segment
 *  \return        E_NOT_OK              'Urgent' flag set in the segment, so the segment will be dropped
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Sixth(
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh
 *********************************************************************************************************************/
/*! \brief         Process the data part of the received segment.
 *  \details       Processing of seventh part (according to RFC 793).
 *                 Called by TcpIp_Tcp_VRxIndicationStateOthers.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in,out] SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \return        E_OK                  Data could be copied to the receive buffer
 *  \return        E_NOT_OK              Data did not fully fit into the receive buffer
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CopyRxDataAndTriggerAck
 *********************************************************************************************************************/
/*! \brief         Copy received data to rx buffer and trigger sending an ACK.
 *  \details       Called by TcpIp_Tcp_VRxIndicationStateOthers_Seventh.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     TcpRxBufferDescIdx    Index of the RxBuffer descriptor.
 *                                       CONSTRAINT:  [0..TcpIp_GetSizeOfTcpRxBufferDesc()-1]
 *  \param[in]     SegmentDescriptorPtr  Pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CopyRxDataAndTriggerAck(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TcpIp_SizeOfTcpRxBufferDescType TcpRxBufferDescIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

#if (TCPIP_SUPPORT_TCP_RX_OOO == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh_ReceiveBufferedData
 *********************************************************************************************************************/
/*! \brief         Append pre-buffered data to RxData if available and matching.
 *  \details       Called by TcpIp_Tcp_VRxIndicationStateOthers_Seventh.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     TcpRxBufferDescIdx    Index of the RxBuffer descriptor.
 *                                       CONSTRAINT:  [0..TcpIp_GetSizeOfTcpRxBufferDesc()-1]
 *  \param[in,out] SegmentDescriptorPtr  Pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh_ReceiveBufferedData(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TcpIp_SizeOfTcpRxBufferDescType TcpRxBufferDescIdx,
  TCPIP_P2V(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CheckCombination
 *********************************************************************************************************************/
/*! \brief         Check if new segment can be combined with existing one (left or right side).
 *  \details       Called by TcpIp_Tcp_VRxIndicationStateOthers_Seventh.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  Pointer to the segment descriptor for the received message.
 *  \return        TRUE                  Combination of the received segement with a stored one is possible
 *  \return        FALSE                 No combination of the received segement with a stored one is possible
 *  \pre           This function expects that at least one element is in the queue.
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(boolean, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CheckCombination(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh_InsertNewOooElement
 *********************************************************************************************************************/
/*! \brief         The segment could not be combined with an existing one, so an extra element is needed. Create new
 *                 element if possible.
 *  \details       Called by TcpIp_Tcp_VRxIndicationStateOthers_Seventh.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  Pointer to the segment descriptor for the received message
 *  \return        TRUE                  Received segment could be stored
 *  \return        FALSE                 No free ooo element available, segment could not be stored
 *  \pre           Ooo queue of the socket must contain at least one entry! If the queue is empty
 *                   'TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CreateFirstOooElement' must be called.
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(boolean, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh_InsertNewOooElement(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CreateFirstOooElement
 *********************************************************************************************************************/
/*! \brief         The segment could not be combined with an existing one, so an extra element is needed. Create new
 *                 element if possible.
 *  \details       Called by TcpIp_Tcp_VRxIndicationStateOthers_Seventh.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \return        TRUE                  received segment could be stored
 *  \return        FALSE                 no free ooo element available, segment could not be stored
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(boolean, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CreateFirstOooElement(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VUpdateOooElementChangeOrder
 *********************************************************************************************************************/
/*! \brief         Update the time-wise linkage of the socket's ooo elements after one element has been changed or
 *                 removed.
 *  \details       Called in context of TcpIp_Tcp_VRxIndicationStateOthers_Seventh.
 *  \param[in]     SocketTcpIdx            Index of a TCP socket.
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     ChangedElementIdKnown   Indicates if the new last changed element is known
 *  \param[in]     ChangedEleIdx           Index of the changed ooo element. Parameter is only valid if parameter
 *                                         ChangedElementIdKnown is TRUE.
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTcpOooQElement()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VUpdateOooElementChangeOrder(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  boolean ChangedElementIdKnown,
  TcpIp_SizeOfTcpOooQElementType ChangedEleIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VUpdateOooElementChangeOrder_IdentifyLastChangedElement
 *********************************************************************************************************************/
/*! \brief         Identify the newest ooo element for this socket and store its index.
 *  \details       -
 *  \param[in]     SocketTcpIdx            Index of a TCP socket.
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     ChangedElementIdKnown   Indicates if the new last changed element is known
 *  \param[in]     ChangedEleIdx           Index of the changed ooo element. Parameter is only valid if parameter
 *                                         ChangedElementIdKnown is TRUE.
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTcpOooQElement()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VUpdateOooElementChangeOrder_IdentifyLastChangedElement(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  boolean ChangedElementIdKnown,
  TcpIp_SizeOfTcpOooQElementType ChangedEleIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VUpdateOooElementChangeOrder_LinkElements
 *********************************************************************************************************************/
/*! \brief         Renew the time-wise link between the socket's ooo elements.
 *  \details       -
 *  \param[in]     SocketTcpIdx            Index of a TCP socket.
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VUpdateOooElementChangeOrder_LinkElements(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);
#endif  /* TCPIP_SUPPORT_TCP_SELECTIVE_ACK */

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CopyDataToBuffer
 *********************************************************************************************************************/
/*! \brief         Copy data from the received segment to the TCP RxBuffer.
 *  \details       Called by TcpIp_Tcp_VRxIndicationStateOthers_Seventh.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CopyDataToBuffer(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);
#endif

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Eighth
 *********************************************************************************************************************/
/*! \brief         Process the FIN flag if received.
 *  \details       Processing of eighth part (according to RFC 793).
 *                 Called by TcpIp_Tcp_VRxIndicationStateOthers.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SegmentDescriptorPtr  pointer to the segment descriptor for the received message
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Eighth(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_SynrcvdEstablished
 *********************************************************************************************************************/
/*! \brief         Switch to state CLOSEWAIT and signal 'FIN received' to the upper layer.
 *  \details       Called by TcpIp_Tcp_VRxIndicationStateOthers_Eighth.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_SynrcvdEstablished(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_Finwait1
 *********************************************************************************************************************/
/*! \brief         Proceed to next connection state after receiving a FIN in state FINWAIT1.
 *  \details       Called by TcpIp_Tcp_VRxIndicationStateOthers_Eighth.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_Finwait1(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_Finwait2
 *********************************************************************************************************************/
/*! \brief         Switch from connection state FinWait2 to TimeWait and eventually signal the event to the upper layer.
 *  \details       Called by TcpIp_Tcp_VRxIndicationStateOthers_Eighth.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_Finwait2(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_ProcessOrStoreFin
 *********************************************************************************************************************/
/*! \brief         Switch to the next socket state or store the FIN_RECEIVED event for later state change.
 *  \details       -
 *  \param[in]     SocketTcpIdx          Index of a TCP socket.
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     State                 New state of the socket.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_ProcessOrStoreFin(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TcpIp_StateType State);

/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainPathMtuChg
 *********************************************************************************************************************/
/*! \brief         Changes the socket path MTU if the change has been triggered previously.
 *  \details       The function TcpIp_Tcp_CbkPathMtuChg() only stores the new requested PathMtu, but this function
 *                 applies the necessary changes. Changes the socket path MTU, adapts the CWND, and resizes the
 *                 RetryQueue elements.
 *  \param[in]     SocketTcpIdx       Index of a TCP socket
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainPathMtuChg(
  TcpIp_SocketTcpDynIterType SocketTcpIdx);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_Tcp_Init
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
FUNC(void, TCPIP_CODE) TcpIp_Tcp_Init(void)
{
  TcpIp_Tcp_GlobalTimestamp  = 0u;
  TcpIp_Tcp_DynamicPortCount = 0u;

  /* #10 Init the retry queue */
  TcpIp_Tcp_NumFreeRetryQEle      = TcpIp_GetSizeOfTcpRetryQElement();
  TcpIp_Tcp_FirstFreeRetrQueueEle = 0u;
  TcpIp_Tcp_LastFreeRetrQueueEle  = TcpIp_Tcp_NumFreeRetryQEle - 1u;
  {
    /* link all elements in the empty list */
    TcpIp_SizeOfTcpRetryQElementType tcpRetryQElementIdx;

    TcpIp_GetAddrTcpRetryQElement(TcpIp_Tcp_FirstFreeRetrQueueEle)->ElePrev = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;        /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    TcpIp_GetAddrTcpRetryQElement(TcpIp_Tcp_LastFreeRetrQueueEle )->EleNext = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;        /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */

    for (tcpRetryQElementIdx = 1; tcpRetryQElementIdx < TcpIp_Tcp_NumFreeRetryQEle; tcpRetryQElementIdx++)
    {
      TcpIp_GetAddrTcpRetryQElement(tcpRetryQElementIdx - 1u)->EleNext = tcpRetryQElementIdx;                            /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
      TcpIp_GetAddrTcpRetryQElement(tcpRetryQElementIdx    )->ElePrev = tcpRetryQElementIdx - 1u;                        /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    }
  }

  /* #20 Init the reset queue */
  TcpIp_Tcp_RstTxQueueReadPos  = 0;
  TcpIp_Tcp_RstTxQueueWritePos = 0;
  TcpIp_Tcp_RstTxQueueFillNum  = 0;

#if (TCPIP_SUPPORT_TCP_RX_OOO == STD_ON)
  /* #30 Init the queue for out of order received segments */
  TcpIp_Tcp_OooNumFreeElements = TcpIp_GetSizeOfTcpOooQElement();
  TcpIp_Tcp_OooFirstFreeEleIdx = 0;

  {
    TcpIp_SizeOfTcpOooQElementType tcpOooQElementIdx;

    /* link all free elments in one consecutive line */
    for (tcpOooQElementIdx = 0; tcpOooQElementIdx < TcpIp_GetSizeOfTcpOooQElement(); tcpOooQElementIdx++)
    {
      /* Set NextEleIdx to current idx + 1. This is also ok for the last element, since (last element index + 1) is the
      same as TcpIp_GetSizeOfTcpOooQElement used to mark the end of the ooo array. */
      TcpIp_GetAddrTcpOooQElement(tcpOooQElementIdx)->NextEleIdx = tcpOooQElementIdx + 1u;                               /* SBSW_TCPIP_AWA_CslIteration_Local */
    }
  }
#endif

  /* #40 Init the mapping of rx and tx buffers to the TCP sockets */
  {
    TcpIp_TcpRxBufferDescIterType tcpRxBufferDescIdx;
    TcpIp_TcpTxBufferDescIterType tcpTxBufferDescIdx;

    /* Reset rx buffer mappings */
    for (tcpRxBufferDescIdx = 0; tcpRxBufferDescIdx < TcpIp_GetSizeOfTcpRxBufferDesc(); tcpRxBufferDescIdx++)
    {
      TcpIp_SetFillLevelOfTcpRxBufferDescDyn(tcpRxBufferDescIdx, 0);                                                    /* SBSW_TCPIP_AWA_CslIteration_Local */
      TcpIp_SetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(tcpRxBufferDescIdx, TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(tcpRxBufferDescIdx)); /* SBSW_TCPIP_AWA_CslIteration_Local */
      TcpIp_SetSocketTcpDynIdxOfTcpRxBufferDescDyn(tcpRxBufferDescIdx, TcpIp_GetSizeOfSocketTcpDyn());                  /* SBSW_TCPIP_AWA_CslIteration_Local */
    }

    /* Reset tx buffer mappings */
    for (tcpTxBufferDescIdx = 0; tcpTxBufferDescIdx < TcpIp_GetSizeOfTcpTxBufferDesc(); tcpTxBufferDescIdx++)
    {
      TcpIp_SetFillLevelOfTcpTxBufferDescDyn(tcpTxBufferDescIdx, 0);                                                    /* SBSW_TCPIP_AWA_CslIteration_Local */
      TcpIp_SetTcpTxBufferWriteIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx, TcpIp_GetTcpTxBufferStartIdxOfTcpTxBufferDesc(tcpTxBufferDescIdx)); /* SBSW_TCPIP_AWA_CslIteration_Local */
      /* no read index for TX buffer requiered. */
      TcpIp_SetSocketTcpDynIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx, TcpIp_GetSizeOfSocketTcpDyn());                  /* SBSW_TCPIP_AWA_CslIteration_Local */
    }
  }

  /* #50 Init several variables for each TCP socket */
  {
    TcpIp_SocketTcpDynIterType socketTcpIdx;

    for (socketTcpIdx = 0; socketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn(); socketTcpIdx++)
    {
      /* #60 Init the tx retry queue */
      TcpIp_SetTcpRetryQElementFirstIdxOfSocketTcpDyn(socketTcpIdx, TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV);                 /* SBSW_TCPIP_AWA_CslIteration_Local */
      TcpIp_SetTcpRetryQElementLastIdxOfSocketTcpDyn( socketTcpIdx, TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV);                 /* SBSW_TCPIP_AWA_CslIteration_Local */
      TcpIp_SetRetryQFillNumOfSocketTcpDyn(socketTcpIdx, 0);                                                            /* SBSW_TCPIP_AWA_CslIteration_Local */

      /* #70 Init the out of order segment handling struct */
#if (TCPIP_SUPPORT_TCP_RX_OOO == STD_ON)
      TCPIP_ASSERT(TcpIp_HasSocketTcpOooDyn() == TRUE);
# if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
      TcpIp_SetTcpOooQElementLastChangedIdxOfSocketTcpOooDyn(socketTcpIdx, TcpIp_GetSizeOfTcpOooQElement());  /* invalid element index */ /* SBSW_TCPIP_AWA_CslIteration_Local */
# endif
      TcpIp_SetTcpOooQElementFirstIdxOfSocketTcpOooDyn(socketTcpIdx, TcpIp_GetSizeOfTcpOooQElement());        /* invalid element index */ /* SBSW_TCPIP_AWA_CslIteration_Local */
      TcpIp_SetTcpOooQFillNumOfSocketTcpOooDyn(socketTcpIdx, 0);                                                        /* SBSW_TCPIP_AWA_CslIteration_Local */
#endif

      /* #80 Reset the assignment of rx and tx buffers to the TCP socket */
      TcpIp_SetTcpRxBufferDescIdxOfSocketTcpDyn(socketTcpIdx, TcpIp_GetSizeOfTcpRxBufferDesc());                        /* SBSW_TCPIP_AWA_CslIteration_Local */
      TcpIp_SetTcpTxBufferDescIdxOfSocketTcpDyn(socketTcpIdx, TcpIp_GetSizeOfTcpTxBufferDesc());                        /* SBSW_TCPIP_AWA_CslIteration_Local */
      TcpIp_SetRequestedRxBufferSizeOfSocketTcpDyn(socketTcpIdx, 0);                                                    /* SBSW_TCPIP_AWA_CslIteration_Local */
      TcpIp_SetRequestedTxBufferSizeOfSocketTcpDyn(socketTcpIdx, 0);                                                    /* SBSW_TCPIP_AWA_CslIteration_Local */

      /*  */
      TcpIp_Tcp_VRestartSock(socketTcpIdx);
    }
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_RxIndication
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
FUNC(void, TCPIP_CODE) TcpIp_Tcp_RxIndication(
  TcpIp_LocalAddrIterType           LocalAddrIdx,
  TCPIP_P2V(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
  TCPIP_P2V(uint8)                  DataPtr,
  uint16                            LenByte,
  boolean                           ChecksumCalculated)
{
  Std_ReturnType                   retVal;
  TcpIp_SocketDynIterType          socketIdx;
  TcpIp_SockAddrBaseType           rxSockLocAddr;  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  TcpIp_Tcp_SegmentDescriptorType  segmentDescriptor;

  /* check input parameters */
  TCPIP_ASSERT(LocalAddrIdx     < TcpIp_GetSizeOfLocalAddr());
  TCPIP_ASSERT(RxSockRemAddrPtr != NULL_PTR);
  TCPIP_ASSERT(DataPtr          != NULL_PTR);

  /* #10 Read TCP header and validate checksum to check the validity of the received TCP segment. */

  /* get the local IP address used to received this segment */
  retVal = TcpIp_GetIpAddr(TCPIP_LOCAL_ADDR_IDX_TO_ID(LocalAddrIdx), &(rxSockLocAddr.TcpIpSockAddr), NULL_PTR, NULL_PTR); /* SBSW_TCPIP_FC_OutParamLocalVarRef */ /* SBSW_TCPIP_FC_NULL_PTR */ /* SBSW_TCPIP_FC_NULL_PTR */

  if (retVal == E_OK)  /* a valid local IP address could be read from the IP layer */
  {
    /* Check TCP header and read data into segment descriptor for further processing */
    retVal = TcpIp_Tcp_VReadAndCheckTcpHeaderData( DataPtr, LenByte, &segmentDescriptor);                               /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_OutParamLocalVarRef */

    if (retVal == E_OK)  /* TCP header contains valid data */
    {
      /* check the TCP header checksum if necessary */
      if (ChecksumCalculated == FALSE)
      {
        retVal = TcpIp_Tcp_VCheckRecChecksum(RxSockRemAddrPtr, &rxSockLocAddr, DataPtr, LenByte);                       /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_LocalAddressAvailable_GetIpAddr */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
      }

      if (retVal == E_OK)  /* the TCP header checksum is valid */
      {
        /* #20 Find the matching socket for the received segment */

        /* set port values in the socket address structs (incoming function parameters) */
        rxSockLocAddr.SockAddrIn.sin_port     = TCPIP_HTONS(segmentDescriptor.TgtPort);
        RxSockRemAddrPtr->SockAddrIn.sin_port = TCPIP_HTONS(segmentDescriptor.SrcPort);                                 /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */

        /* Identify socket: */
        socketIdx = TcpIp_VRxTcpSockIdxIdent(RxSockRemAddrPtr, &rxSockLocAddr, LocalAddrIdx);                           /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_LocalAddressAvailable_GetIpAddr */

        /* Drop the received segment and send RST segment if no matching local socket could be found */
        if (socketIdx == TCPIP_SOCKET_IDX_INV)  /* invalid socket index */
        {
          /* Packet dropped due to invalid socket */
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
          TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_DROP_TCP);
          TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER4);
#endif
          TcpIp_Tcp_VRejectReceivedSegmentWithoutMatchingLocalSocket(LocalAddrIdx, RxSockRemAddrPtr, &rxSockLocAddr, &segmentDescriptor); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_LocalAddressAvailable_GetIpAddr */ /* SBSW_TCPIP_FC_OutParamLocalVarRef */
          /* no further interpretation of this message */
        }
        else
        {
          /* #30 Process the received segment dependent on the socket state */
          TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx);

          TCPIP_ASSERT(TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) != TCPIP_TCP_SOCK_STATE_CLOSED);

          /* #40 Handle received RST */
          if (TcpIp_IsRstReceivedOfSocketTcpDyn(socketTcpIdx) == TRUE)
          {
            /* A RST flag was received in a previous message but the socket state was not yet reset. Reset is triggered,
              if any further segment is received. */
            TcpIp_Tcp_VRejectReceivedSegmentWithoutMatchingLocalSocket(LocalAddrIdx, RxSockRemAddrPtr, &rxSockLocAddr, &segmentDescriptor); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_LocalAddressAvailable_GetIpAddr */ /* SBSW_TCPIP_FC_OutParamLocalVarRef */

#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
            retVal = E_NOT_OK;  /* set negative retVal only if it will be evaluated later inside the current function */
#endif
          }
          else
          {
            /* #50 Else continue message handling */
            switch (TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx))
            {
              /* TCPIP_TCP_SOCK_STATE_CLOSED:
                 If the socket is in state CLOSED, an incoming segment will never be assigned to this socket by
                 TcpIp_VRxTcpSockIdxIdent(). This socket state is only mentioned here to make clear that it was not
                 forgotten. For the logic of 'switch' this would mean that the CLOSED state would be part of the 'default'
                 path, but in real operation this state will never appear here. */
            case TCPIP_TCP_SOCK_STATE_LISTEN:
              {
                /* #60 The socket is in state LISTEN, process the segment */
                TcpIp_Tcp_VRxIndicationStateListen(socketTcpIdx, LocalAddrIdx, RxSockRemAddrPtr, &rxSockLocAddr, &segmentDescriptor); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_LocalAddressAvailable_GetIpAddr */ /* SBSW_TCPIP_FC_REFERENCE_OF_VARIABLE */
                break;
              }
            case TCPIP_TCP_SOCK_STATE_SYNSENT:
              {
                /* #70 The socket is in state SYNSENT, process the segment */
                TcpIp_Tcp_VRxIndicationStateSynSent(socketTcpIdx, LocalAddrIdx, RxSockRemAddrPtr, &rxSockLocAddr, &segmentDescriptor); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_LocalAddressAvailable_GetIpAddr */ /* SBSW_TCPIP_FC_REFERENCE_OF_VARIABLE */
                break;
              }
            default:
              {
                /* #80 The socket is in state SYNRECEIVED or the connection is established, process the segment */
                TcpIp_Tcp_VRxIndicationStateOthers(socketTcpIdx, LocalAddrIdx, RxSockRemAddrPtr, &rxSockLocAddr, &segmentDescriptor); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_LocalAddressAvailable_GetIpAddr */ /* SBSW_TCPIP_FC_REFERENCE_OF_VARIABLE */
                break;
              }
            } /* end checking sock states */
          }
        }
      }
    }

#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
    if(retVal == E_NOT_OK)
    {
      /* Packet dropped due to invalid TCP header or checksum or previous RST flag */
      TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER4);
    }
#endif
  }
}  /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VReadAndCheckTcpHeaderData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VReadAndCheckTcpHeaderData(
  TCPIP_P2V(uint8) DataPtr,
  uint16 LenByte,
  TCPIP_P2V(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  Std_ReturnType retVal = E_OK;

  /* #10 Check the length to be at least the minimum TCP header size. */
  if (LenByte >= TCPIP_TCP_HDR_LEN_BYTE)
  {
    uint8 hdrLen;  /* TCP header length value according to the field 'DataOffset' */

    /* The payoad offset can be found in the upper nipple of one header byte, and it is given as multiple of 4 bytes */
    hdrLen = (uint8)(((DataPtr[TCPIP_TCP_HDR_DATA_OFFSET_OFFSET] & 0xF0u) >> 4) * 4u);

    /* #20 Check the header length value to be in a valid range. */
    if ((hdrLen >= TCPIP_TCP_HDR_LEN_BYTE) && (hdrLen <= LenByte))
    {
      /* #30 Read the TCP header elements and write them to the segment descriptor. */
      SegmentDescriptorPtr->HdrPtr     = DataPtr;                                                                       /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
      SegmentDescriptorPtr->HdrLen     = hdrLen;                                                                        /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
      SegmentDescriptorPtr->PayloadPtr = &DataPtr[hdrLen];                                                              /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */

      SegmentDescriptorPtr->SegSeq     = TCPIP_GET_UINT32(DataPtr, TCPIP_TCP_HDR_SEQ_NUM_OFFSET);                       /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
      SegmentDescriptorPtr->SegAck     = TCPIP_GET_UINT32(DataPtr, TCPIP_TCP_HDR_ACK_NUM_OFFSET);                       /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
      SegmentDescriptorPtr->SegLen     = LenByte - SegmentDescriptorPtr->HdrLen;  /* TCP payload length */              /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
      SegmentDescriptorPtr->SegWnd     = TCPIP_GET_UINT16(DataPtr, TCPIP_TCP_HDR_WINDOW_OFFSET);                        /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */

      SegmentDescriptorPtr->CodeBits   = TCPIP_GET_UINT8( DataPtr, TCPIP_TCP_HDR_CODE_BITS_OFFSET);                     /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
      SegmentDescriptorPtr->UrgentPtr  = TCPIP_GET_UINT16(DataPtr, TCPIP_TCP_HDR_URGENT_PTR_OFFSET);                    /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
      SegmentDescriptorPtr->SrcPort    = TCPIP_GET_UINT16(DataPtr, TCPIP_TCP_HDR_SOURCE_PORT_OFFSET);                   /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
      SegmentDescriptorPtr->TgtPort    = TCPIP_GET_UINT16(DataPtr, TCPIP_TCP_HDR_TARGET_PORT_OFFSET);                   /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */

      /* #40 Ignore incoming messages with invalid port. Invalid network addresses are already filtered in the IP layer. */
      if (SegmentDescriptorPtr->TgtPort == TCPIP_PORT_ANY)
      {
        /* drop invalid message immediately */
        retVal = E_NOT_OK;
      }
    }
    else
    {
      /* invalid length -> drop message immediately */
      retVal = E_NOT_OK;
    }
  }
  else
  {
    /* invalid length -> drop message immediately */
    retVal = E_NOT_OK;
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRejectReceivedSegmentWithoutMatchingLocalSocket
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRejectReceivedSegmentWithoutMatchingLocalSocket(
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* #10 Send a TCP RST if received message was not a RST segment as well. */
  if ((TCPIP_TCP_CODE_BIT_RST & SegmentDescriptorPtr->CodeBits) == 0u)
  {
    /* #20 Send a TCP.RST. */

    if ((TCPIP_TCP_CODE_BIT_ACK & SegmentDescriptorPtr->CodeBits) != 0u)
    {
      /* ACK */
      /* send reset <SEQ=SEG.ACK><CTL=RST> */
      TcpIp_Tcp_VSendReset(TCPIP_TCP_INV_IDX, TCPIP_LOCAL_ADDR_IDX_TO_IPVX(LocalAddrIdx), RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr->SegAck, 0, 0); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    }
    else
    {
      /* no ACK */
      /* send reset <ACK=SEG.SEQ+SEG.LEN><CTL=RST,ACK> */
      uint32 seqNo = SegmentDescriptorPtr->SegSeq;
      seqNo += SegmentDescriptorPtr->SegLen;
      if ((TCPIP_TCP_CODE_BIT_SYN & SegmentDescriptorPtr->CodeBits) != 0u)
      {
        seqNo++;
      }

      if ((TCPIP_TCP_CODE_BIT_FIN & SegmentDescriptorPtr->CodeBits) != 0u)
      {
        seqNo++;
      }
      TcpIp_Tcp_VSendReset(TCPIP_TCP_INV_IDX, TCPIP_LOCAL_ADDR_IDX_TO_IPVX(LocalAddrIdx), RxSockRemAddrPtr, RxSockLocAddrPtr, 0, seqNo, TCPIP_TCP_CODE_BIT_ACK); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    }
  }
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateListen
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateListen(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* #10 The socket is in state LISTEN, so only incoming connection requests are expected. */

  /* #20 RFC: first check for an RST */
  if ((TCPIP_TCP_CODE_BIT_RST & SegmentDescriptorPtr->CodeBits) != 0u)
  {
    /* The segment has the RST flag set -> ignore message */
  }
  /* #30 RFC: second check for an ACK */
  else if ((TCPIP_TCP_CODE_BIT_ACK & SegmentDescriptorPtr->CodeBits) != 0u)
  {
    /* There is an ACK included in this segment, this is not expected. */
    /* send reset <SEQ=SEG.ACK><CTL=RST> */
    TcpIp_Tcp_VSendReset(SocketTcpIdx, TCPIP_LOCAL_ADDR_IDX_TO_IPVX(LocalAddrIdx), RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr->SegAck, 0, 0); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }
  /* #40 RFC: third check for a SYN, otherwise drop the segment */
  else if ((TCPIP_TCP_CODE_BIT_SYN & SegmentDescriptorPtr->CodeBits) != 0u)
  {
    /* The RFC requests to check the security/compartment of the received segment compared to the socket's security.
    Security is an IP option. Since this is not implemented in this module, it will be continued without this check. */

    /* #50 Duplicate the socket, all further communication and state handling is done via this new socket. */
    TcpIp_SizeOfSocketTcpDynType newSocketTcpIdx = TcpIp_Tcp_VDuplicateSocket(SocketTcpIdx, LocalAddrIdx, RxSockRemAddrPtr);  /* SBSW_TCPIP_FC_PASSING_API_POINTER */

    if (newSocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn())
    {
      /* #60 Socket was successfully duplicated, proceed the segment analysis */
      Std_ReturnType retVal = E_OK;

      /* Increese the sequence number because the SYN flag also is counted as 1 byte */
      TcpIp_SetRcvNxtOfSocketTcpDyn(newSocketTcpIdx, (SegmentDescriptorPtr->SegSeq + 1u));                              /* SBSW_TCPIP_AWA_CslIteration_Local */
      TcpIp_SetSndWndOfSocketTcpDyn(newSocketTcpIdx,  SegmentDescriptorPtr->SegWnd);                                    /* SBSW_TCPIP_AWA_CslIteration_Local */

      if (SegmentDescriptorPtr->HdrLen > TCPIP_TCP_HDR_LEN_BYTE)
      {
        /* #70 Handle the received TCP options */
        if (TcpIp_Tcp_VHandleTcpOptions(newSocketTcpIdx, RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr) != E_OK)   /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
        {
          /* stop processing of this message and drop it. */
          /* switch to state CLOSED, delete/clear TCB element, and return */
          TcpIp_Tcp_VRestartSock(newSocketTcpIdx);
          TcpIp_VDelSockAddrMapping(TCPIP_TCP_IDX_TO_SOCKET_IDX(newSocketTcpIdx));
          retVal = E_NOT_OK;
        }
      }

      /* #80 Go to next socket state if duplicating the socket was successful */
      if (retVal == E_OK)
      {
        TcpIp_SetSockStateOfSocketTcpDyn(newSocketTcpIdx, TCPIP_TCP_SOCK_STATE_SYNRCVD);                                /* SBSW_TCPIP_AWA_CslIteration_Local */
        TcpIp_SetSockStateNextOfSocketTcpDyn(newSocketTcpIdx, TCPIP_TCP_SOCK_STATE_SYNRCVD);                            /* SBSW_TCPIP_AWA_CslIteration_Local */
      }
    }
    else
    {
      /* #90 Socket could not be duplicated, so reject connection request (send TCP.RST). */
      TcpIp_Tcp_VSendReset(SocketTcpIdx, TCPIP_LOCAL_ADDR_IDX_TO_IPVX(LocalAddrIdx), RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr->SegSeq, 0, 0); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    }
  }
  else
  {
    /* Only segments with SYN flag set are expected in this socket state */
  }

  /* RFC: fourth other text or control */
  /* nothing to do here */
}  /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateSynSent
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateSynSent(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  Std_ReturnType retVal;

  /* RFC: first check the ACK bit */
  /* #10 Check the received ACK number to be in the expected range, and check code bits */
  retVal = TcpIp_Tcp_VRxIndicationStateSynSent_First(SocketTcpIdx, LocalAddrIdx, RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */

  /* RFC: second check the RST bit */
  if (retVal == E_OK)
  {
    /* #20 Check if the RST bit is set and close the connection or just drop the segment. */
    retVal = TcpIp_Tcp_VRxIndicationStateSynSent_Second(SocketTcpIdx, SegmentDescriptorPtr);                            /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }

  /* RFC: third check the security and precedence */
  /* check security/compartment for exact match: fail -> send reset <SEQ=SEG.ACK><CTL=RST> */
  /* security handling not supported   -> do nothing */
  /* precedance handling not supported -> do nothing */

  if (retVal == E_OK)
  {
    /* RFC: fourth check the SYN bit */
    if ((TCPIP_TCP_CODE_BIT_SYN & SegmentDescriptorPtr->CodeBits) != 0u)
    {
      /* no security compartment or precedence handling implemented */

      /* #30 Update variables regarding the send window, read the TCP options and advance the connection state to
      ESTABLISHED (or in case of simultaneous opening to state SYNRCVD). */
      TcpIp_Tcp_VRxIndicationStateSynSent_Fourth(SocketTcpIdx, RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    }
  }

  /* RFC: fifth if neither of the SYN or RST bits is set then drop the segment and return. */
  /* do nothing since this is the last operation inside this function */
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateSynSent_First
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateSynSent_First(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* [SYNSENT] first: check the ACK bit */

  Std_ReturnType  retVal = E_OK;

  /* #10 Check the received ACK number to be in the expected range */
  if ((TCPIP_TCP_CODE_BIT_ACK & SegmentDescriptorPtr->CodeBits) != 0u)
  {
    if (   TCPIP_TCP_SEQ1_SMALLER_OR_EQUAL_SEQ2(SegmentDescriptorPtr->SegAck, TcpIp_GetIssOfSocketTcpDyn(SocketTcpIdx)) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        || TCPIP_TCP_SEQ1_BIGGER_SEQ2(SegmentDescriptorPtr->SegAck, TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx)))
    {
      /* ACK number is outside of the window. */

      /* #20 Send reset if received segment was no reset */
      if ((TCPIP_TCP_CODE_BIT_RST & SegmentDescriptorPtr->CodeBits) == 0u)
      {
        /* send reset <SEQ=SEG.ACK><CTL=RST> */
        TcpIp_Tcp_VSendReset(SocketTcpIdx, TCPIP_LOCAL_ADDR_IDX_TO_IPVX(LocalAddrIdx), RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr->SegAck, 0, 0); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
      }
      else
      {
        /* RST bit is set, just ignore this message */
      }
      retVal = E_NOT_OK;
    }
    else
    {
      /* Valid ACK received. */
#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
      TcpIp_Tcp_VKeepAliveTrigger(SocketTcpIdx);
#endif
    }

  }

  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateSynSent_Second
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateSynSent_Second(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  Std_ReturnType             retVal    = E_OK;

  /* #10 Check if the RST bit is set and close the connection or just drop the segment. */
  if ((TCPIP_TCP_CODE_BIT_RST & SegmentDescriptorPtr->CodeBits) != 0u)
  {
    if ((TCPIP_TCP_CODE_BIT_ACK & SegmentDescriptorPtr->CodeBits) != 0u)
    {
      /* set error: 'Connection reset by peer' */
      TcpIp_SetLastSockError(TCPIP_SOCK_ERR_10054);

      /* switch to state CLOSED, delete/clear TCB element, and return */
      TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_RESET);
    }

    /* drop message silently */
    retVal = E_NOT_OK;
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateSynSent_Fourth
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateSynSent_Fourth(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  Std_ReturnType             retVal    = E_OK;
  TcpIp_SizeOfSocketDynType  socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  /* #10 Update variables regarding the send window, read the TCP options and advance the connection state to ESTABLISHED
  (or in case of simultaneous opening to state SYNRCVD). */

  /* RFC: RCV.NXT is set to SEG.SEQ+1, IRS is set to SEG.SEQ. SND.UNA should be advanced
  to equal SEG.ACK (if there is an ACK), and any segments on the retransmission queue
  which are thereby acknowledged should be removed. */
  /* #20 Update RcvNxt and SndUna */
  TcpIp_SetRcvNxtOfSocketTcpDyn(SocketTcpIdx, (SegmentDescriptorPtr->SegSeq + 1u));                                      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  if ((TCPIP_TCP_CODE_BIT_ACK & SegmentDescriptorPtr->CodeBits) != 0u)
  {
    TcpIp_SetSndUnaOfSocketTcpDyn(SocketTcpIdx, SegmentDescriptorPtr->SegAck);                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }

  /* clear all segments in retransmission queue (usually there should not be any) */
  TcpIp_Tcp_VDelTxQueue(SocketTcpIdx);

  /* #30 Read and check the received TCP options (if available) */
  if (SegmentDescriptorPtr->HdrLen > TCPIP_TCP_HDR_LEN_BYTE)
  {
    if (TcpIp_Tcp_VHandleTcpOptions(SocketTcpIdx, RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr) != E_OK)    /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    {
      /* stop processing of this message. Sending a RST was already triggered by TcpIp_Tcp_VHandleTcpOptions() */
      retVal = E_NOT_OK;
    }
  }

  if (retVal == E_OK)
  {
    if (TCPIP_TCP_SEQ1_BIGGER_SEQ2(TcpIp_GetSndUnaOfSocketTcpDyn(SocketTcpIdx), TcpIp_GetIssOfSocketTcpDyn(SocketTcpIdx)))
    {
      /* #40 A SYN was received with the expected ACK number, so update the send window variables and advance connection state to
      ESTABLISHED */
      TcpIp_SizeOfSocketOwnerConfigType socketOwnerConfigIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(socketIdx);

      /* send ACK: <SEQ=SND.NXT><ACK=RCV.NXT><CTL=ACK> */
      TcpIp_Tcp_VSendFlags(SocketTcpIdx, TCPIP_TCP_CODE_BIT_ACK);

      /* set send window according to received segment */
      TcpIp_SetSndWndOfSocketTcpDyn(SocketTcpIdx, SegmentDescriptorPtr->SegWnd);                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetSndWl1OfSocketTcpDyn(SocketTcpIdx, SegmentDescriptorPtr->SegSeq);                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetSndWl2OfSocketTcpDyn(SocketTcpIdx, SegmentDescriptorPtr->SegAck);                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_ESTABLISHED);                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_INVALID);                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
      /* #50 Initialize the retransmission timing parameters. */
      if (TcpIp_IsRtoResetPendingOfSocketTcpTsOptDyn(SocketTcpIdx) == TRUE)
      {
        TcpIp_SetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx, TCPIP_TCP_TX_RETRY_INT_RESET_VALUE_CYCLES);                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        TcpIp_SetRtoOfSocketTcpTsOptDyn(     SocketTcpIdx, TCPIP_TCP_TX_RETRY_INT_RESET_VALUE_CYCLES);                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        TcpIp_SetRtoResetPendingOfSocketTcpTsOptDyn(SocketTcpIdx, FALSE);                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
#endif

      /* Set flag to indicate that the next ACK is the last ACK of the TCP handshake. */
      TcpIp_SetSendLastHsAckOfSocketTcpDyn(SocketTcpIdx, TRUE);                                                         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      /* #60 Forward the information about the connected socket to the socket owner. */
#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
      TcpIp_VSockTcpStateChg(socketIdx, socketOwnerConfigIdx, TCPIP_TCP_STATE_CONNECTED, TcpIp_IsUseTlsOfSocketTcpDyn(SocketTcpIdx));
#else
      TcpIp_VSockTcpStateChg(socketIdx, socketOwnerConfigIdx, TCPIP_TCP_STATE_CONNECTED, FALSE);
#endif
    }
    else
    {
      /* #70 A SYN was received but not with the expected ACK number, so go to connection state SYN_RCVD */
      /* send SYN/ACK: <SEQ=ISS><ACK=RCV.NXT><CTL=SYN,ACK> */
      TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_SYNRCVD);                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_SYNRCVD);                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetSndNxtOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetIssOfSocketTcpDyn(SocketTcpIdx));                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_Tcp_VSendFlags(SocketTcpIdx, (TCPIP_TCP_CODE_BIT_SYN | TCPIP_TCP_CODE_BIT_ACK));
    }

    /* #80 Reset the keep alive timing */
#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
    TcpIp_Tcp_VKeepAliveTrigger(SocketTcpIdx);
#endif
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2V(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /*
  States:
  TCPIP_TCP_SOCK_STATE_SYNRCVD
  TCPIP_TCP_SOCK_STATE_ESTABLISHED
  TCPIP_TCP_SOCK_STATE_CLOSEWAIT
  TCPIP_TCP_SOCK_STATE_LASTACK
  TCPIP_TCP_SOCK_STATE_FINWAIT1
  TCPIP_TCP_SOCK_STATE_FINWAIT2
  TCPIP_TCP_SOCK_STATE_CLOSING
  TCPIP_TCP_SOCK_STATE_TIMEWAIT
  */

  Std_ReturnType retVal;

  /* #10 RFC: first check sequence number */
  retVal = TcpIp_Tcp_VRxIndicationStateOthers_First(SocketTcpIdx, SegmentDescriptorPtr);                                /* SBSW_TCPIP_FC_PASSING_API_POINTER */

  /* From here on the segment is valid and accepted, and the text segment lies completely
     inside the receiving window. Special treatment for out of order packet is done later. */

  if (retVal == E_OK)
  {
#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
    TcpIp_SetIdleTimeoutShortOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx) + 2u));  /* reset the idle timer on each received segment */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif

    /* #20 RFC: second check the RST bit */
    retVal = TcpIp_Tcp_VRxIndicationStateOthers_Second(SocketTcpIdx, SegmentDescriptorPtr);                             /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }

  /* #30 RFC: third check security and precedence (nothing to do) */
  /* security compartment and precedence is not supported */

  /* #40 RFC: fourth check the SYN bit */
  if (retVal == E_OK)
  {
    retVal = TcpIp_Tcp_VRxIndicationStateOthers_Fourth(SocketTcpIdx, LocalAddrIdx, RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }

  /* #50 RFC: fifth enhance connection states and transmission timings */
  if (retVal == E_OK)
  {
    retVal = TcpIp_Tcp_VRxIndicationStateOthers_Fifth(SocketTcpIdx, LocalAddrIdx, RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }

  /* #60 RFC: sixth check the URG bit */
  if (retVal == E_OK)
  {
    retVal = TcpIp_Tcp_VRxIndicationStateOthers_Sixth(SegmentDescriptorPtr);                                            /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }

  /* #70 RFC: seventh process the segment text */
  if (retVal == E_OK)
  {
    retVal = TcpIp_Tcp_VRxIndicationStateOthers_Seventh(SocketTcpIdx, SegmentDescriptorPtr);                            /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }

  /* #80 RFC: eigth check the FIN bit */
  if (retVal == E_OK)
  {
    TcpIp_Tcp_VRxIndicationStateOthers_Eighth(SocketTcpIdx, SegmentDescriptorPtr);                                      /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_First
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_First(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* RFC: first check sequence number */

  Std_ReturnType  retVal;
  boolean         msgIsAcceptable = TRUE;

  /* #10 Check if any data can be received (receive window isn't of size 0). */
  if (TcpIp_GetRcvWndOfSocketTcpDyn(SocketTcpIdx) == 0u)
  {
    /* #20 Check if segment length is 0 (as expected) */
    if (SegmentDescriptorPtr->SegLen == 0u)
    {
      /* #30 Check if segment has exactly the next expected sequence number (as expected) */
      if (SegmentDescriptorPtr->SegSeq != TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx))
      {
        /* not accepted */
        msgIsAcceptable = FALSE;
      }
    }
    else
    {
      /* not accepted */
      /* the remote host ignored our transmitted window size */
      msgIsAcceptable = FALSE;

#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
      /* Increment the measurement data counter for dropped TCP message (due to insufficient Rx buffer) */
      TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_RX_BUFFER);
#endif
    }
  }
  else
  {
    /* Our receive window is not 0 */

    /* #40 Check if the segment starts inside our receive window */
    if (   TCPIP_TCP_SEQ1_BIGGER_SEQ2(TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx), SegmentDescriptorPtr->SegSeq)        /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        || TCPIP_TCP_SEQ1_BIGGER_OR_EQUAL_SEQ2(SegmentDescriptorPtr->SegSeq,
             (TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx) + TcpIp_GetRcvWndOfSocketTcpDyn(SocketTcpIdx))))
    {
      /* #50 The segment starts before or beyond (so not inside of) our receive window */

      if (SegmentDescriptorPtr->SegLen == 0u)
      {
        /* not accepted */
        msgIsAcceptable = FALSE;
      }
      else
      {
        /* #60 Check if the segment at least lies partly inside our receive window */
        if (   TCPIP_TCP_SEQ1_BIGGER_SEQ2(TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx),                                  /* PRQA S 3415 5 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          (SegmentDescriptorPtr->SegSeq + ((uint32)SegmentDescriptorPtr->SegLen - 1u)))
            || TCPIP_TCP_SEQ1_BIGGER_OR_EQUAL_SEQ2(SegmentDescriptorPtr->SegSeq,
                 (TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx) + TcpIp_GetRcvWndOfSocketTcpDyn(SocketTcpIdx))))
        {
          /* The segment is completly before our receive window (so this is old or retransmitted data),
             or the segment lies beyond our receive window */
          /* not accepted */
          msgIsAcceptable = FALSE;

          if ( TCPIP_TCP_SEQ1_BIGGER_OR_EQUAL_SEQ2(SegmentDescriptorPtr->SegSeq,
               (TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx) + TcpIp_GetRcvWndOfSocketTcpDyn(SocketTcpIdx))))
          {
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
            /* Increment the measurement data counter for dropped TCP message (due to insufficient Rx buffer) */
            TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_RX_BUFFER);
#endif
          }
        }
      }
    }
  }

  if (msgIsAcceptable == FALSE)
  {
    /* If the segment didn't contain a RST flag, send an ACK with the information of our current window */
    if ((TCPIP_TCP_CODE_BIT_RST & SegmentDescriptorPtr->CodeBits) == 0u)
    {
      /* send ACK: <SEQ=SND.NXT><ACK=RCV.NXT><CTL=ACK> */
      TcpIp_Tcp_VSendFlags(SocketTcpIdx, TCPIP_TCP_CODE_BIT_ACK);
    }
    /* drop message and return */
    retVal = E_NOT_OK;
     /* for all dropped messages */
  }
  else
  {
    uint32 rcvMax = TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx) + TcpIp_GetRcvWndOfSocketTcpDyn(SocketTcpIdx);  /* rigth border of the receive window */

    /* #70 Cut of segment parts that don't fit into the receive window. */
    if (TCPIP_TCP_SEQ1_SMALLER_SEQ2(SegmentDescriptorPtr->SegSeq, TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx)))
    {
      /* The segment starts before RcvNxt and ends after RcvNxt. Cut off first part of the segment, set new start to RcvNxt. */
      uint16 lenDiff = (uint16)(TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx) - SegmentDescriptorPtr->SegSeq);

      TCPIP_ASSERT(lenDiff <= SegmentDescriptorPtr->SegLen);

      SegmentDescriptorPtr->SegLen     = SegmentDescriptorPtr->SegLen  - lenDiff;                                       /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
      SegmentDescriptorPtr->SegSeq     = TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx);                                   /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
      SegmentDescriptorPtr->PayloadPtr = &((SegmentDescriptorPtr->PayloadPtr)[lenDiff]);                                /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
    }

    if (TCPIP_TCP_SEQ1_BIGGER_SEQ2((SegmentDescriptorPtr->SegSeq + SegmentDescriptorPtr->SegLen), rcvMax))
    {
      /* The segment ends after the receive window. Cut off last part of the segment, set new end to (RcvNxt+RcvWnd). */
      uint16 lenDiff = (uint16)((SegmentDescriptorPtr->SegSeq + SegmentDescriptorPtr->SegLen) - rcvMax);

      TCPIP_ASSERT(lenDiff <= SegmentDescriptorPtr->SegLen);

      SegmentDescriptorPtr->SegLen     = SegmentDescriptorPtr->SegLen - lenDiff;                                        /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */

#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
      /* Increment the measurement data counter for dropped TCP message (due to insufficient Rx buffer) */
      TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_RX_BUFFER);
#endif
    }

    retVal = E_OK;
  }

  return retVal;
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Second
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Second(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* RFC: second check the RST bit */

  /*
  States:
  TCPIP_TCP_SOCK_STATE_SYNRCVD
  TCPIP_TCP_SOCK_STATE_ESTABLISHED
  TCPIP_TCP_SOCK_STATE_CLOSEWAIT
  TCPIP_TCP_SOCK_STATE_LASTACK
  TCPIP_TCP_SOCK_STATE_FINWAIT1
  TCPIP_TCP_SOCK_STATE_FINWAIT2
  TCPIP_TCP_SOCK_STATE_CLOSING
  TCPIP_TCP_SOCK_STATE_TIMEWAIT
  */

  Std_ReturnType             retVal    = E_OK;

  /* #10 Handle a received RST flag */
  if ((TCPIP_TCP_CODE_BIT_RST & SegmentDescriptorPtr->CodeBits) != 0u)
  {
    /* RST flag was received */
    /* #20 Process RST flag handling in next MainFunction */
    TcpIp_SetRstReceivedOfSocketTcpDyn(SocketTcpIdx, TRUE);                                                              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

    retVal = E_NOT_OK;  /* a reset flag was received */
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fourth
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fourth(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* RFC: fourth check the SYN bit */

  /*
  States:
  TCPIP_TCP_SOCK_STATE_SYNRCVD
  TCPIP_TCP_SOCK_STATE_ESTABLISHED
  TCPIP_TCP_SOCK_STATE_CLOSEWAIT
  TCPIP_TCP_SOCK_STATE_LASTACK
  TCPIP_TCP_SOCK_STATE_FINWAIT1
  TCPIP_TCP_SOCK_STATE_FINWAIT2
  TCPIP_TCP_SOCK_STATE_CLOSING
  TCPIP_TCP_SOCK_STATE_TIMEWAIT
  */

  Std_ReturnType  retVal = E_OK;

  /* #10 Close the socket if a SYN flag was received. */
  if ((TCPIP_TCP_CODE_BIT_SYN & SegmentDescriptorPtr->CodeBits)  != 0u)
  {
    /* SYN flag was received */

    /* send reset <SEQ=SEG.ACK><CTL=RST> */
    TcpIp_Tcp_VSendReset(SocketTcpIdx, TCPIP_LOCAL_ADDR_IDX_TO_IPVX(LocalAddrIdx), RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr->SegAck, 0u, 0u); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */

    /* enter CLOSED state, delete/clear TCB */
    TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_RESET);

    TcpIp_SetLastSockError(TCPIP_SOCK_ERR_10054);  /* 'Connection reset by peer' */
    retVal = E_NOT_OK;  /* return from RxIndication, no SYN should be received in this state */
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* RFC: fifth check the ACK field */

  /*
  States:
  TCPIP_TCP_SOCK_STATE_SYNRCVD
  TCPIP_TCP_SOCK_STATE_ESTABLISHED
  TCPIP_TCP_SOCK_STATE_CLOSEWAIT
  TCPIP_TCP_SOCK_STATE_LASTACK
  TCPIP_TCP_SOCK_STATE_FINWAIT1
  TCPIP_TCP_SOCK_STATE_FINWAIT2
  TCPIP_TCP_SOCK_STATE_CLOSING
  TCPIP_TCP_SOCK_STATE_TIMEWAIT
  */

  Std_ReturnType retVal;

  /* #10 Check ACK to be present and evaluate TCP header options */
  retVal = TcpIp_Tcp_VRxIndicationStateOthers_Fifth_AckAndOpts(SocketTcpIdx, RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */

  if (retVal == E_OK)
  {
    if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_SYNRCVD)
    {
      /* #20 Check if state can be enhanced to 'ESTABLISHED' and forward 'CONNECTED' event to the upper layer */
      retVal = TcpIp_Tcp_VRxIndicationStateOthers_Fifth_SynRcvd(SocketTcpIdx, LocalAddrIdx, RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    }
  }

  if (retVal == E_OK)
  {
    /* #30 Proceed dependent on to the socket state */
    switch (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx))
    {
    case TCPIP_TCP_SOCK_STATE_ESTABLISHED:
    case TCPIP_TCP_SOCK_STATE_FINWAIT1:
    case TCPIP_TCP_SOCK_STATE_FINWAIT2:
    case TCPIP_TCP_SOCK_STATE_CLOSEWAIT:
    case TCPIP_TCP_SOCK_STATE_CLOSING:
      {
        /* #40 Update timing and window values for the connection (including congestion control), and proceed the closing of the socket if necessary */
        retVal = TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3(SocketTcpIdx, SegmentDescriptorPtr);                        /* SBSW_TCPIP_FC_PASSING_API_POINTER */
        break;
      }
    case TCPIP_TCP_SOCK_STATE_LASTACK:
      {
        /* #50 Finally close the socket if all conditions are fulfilled */
        TcpIp_Tcp_VRxIndicationStateOthers_Fifth_LastAck(SocketTcpIdx, SegmentDescriptorPtr);                           /* SBSW_TCPIP_FC_PASSING_API_POINTER */
        retVal = E_NOT_OK;
        break;
      }
    case TCPIP_TCP_SOCK_STATE_TIMEWAIT:
      {
        /* #60 Handle received messages in state 'TIMEWAIT' even though no messages are expected. Just wait. */
        retVal = TcpIp_Tcp_VRxIndicationStateOthers_Fifth_TimeWait(SocketTcpIdx, SegmentDescriptorPtr);                 /* SBSW_TCPIP_FC_PASSING_API_POINTER */
        break;
      }
    default:
      {
        /* nothing to do */
        break;
      }
    }
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_AckAndOpts
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_AckAndOpts(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* RFC: fifth check the ACK field */

  /*
  States:
  TCPIP_TCP_SOCK_STATE_SYNRCVD
  TCPIP_TCP_SOCK_STATE_ESTABLISHED
  TCPIP_TCP_SOCK_STATE_CLOSEWAIT
  TCPIP_TCP_SOCK_STATE_LASTACK
  TCPIP_TCP_SOCK_STATE_FINWAIT1
  TCPIP_TCP_SOCK_STATE_FINWAIT2
  TCPIP_TCP_SOCK_STATE_CLOSING
  TCPIP_TCP_SOCK_STATE_TIMEWAIT
  */

  Std_ReturnType  retVal = E_OK;

  /* #10 Check the ACK flag to be present */
  if ((TCPIP_TCP_CODE_BIT_ACK & SegmentDescriptorPtr->CodeBits) == 0u)
  {
    /* no segment without ACK may arrive in this TCP state
    -> drop segment */
    retVal = E_NOT_OK;
  }
  /* five.a: */
  else
  {
    if (SegmentDescriptorPtr->HdrLen > TCPIP_TCP_HDR_LEN_BYTE)
    {
      /* #20 Handle the TCP option that is included in the header */
      if (TcpIp_Tcp_VHandleTcpOptions(SocketTcpIdx, RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr) != E_OK)  /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
      {
        /* stop processing of this message. Sending a RST was already triggered by TcpIp_Tcp_VHandleTcpOptions() */
        retVal = E_NOT_OK;
      }
    }
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_SynRcvd
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_SynRcvd(
  TcpIp_SizeOfSocketTcpDynType               SocketTcpIdx,
  TcpIp_LocalAddrIterType                    LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType)          RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /*
  States:
  TCPIP_TCP_SOCK_STATE_SYNRCVD
  */

  Std_ReturnType             retVal    = E_OK;

  if (   TCPIP_TCP_SEQ1_SMALLER_OR_EQUAL_SEQ2(TcpIp_GetSndUnaOfSocketTcpDyn(SocketTcpIdx), SegmentDescriptorPtr->SegAck) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && TCPIP_TCP_SEQ1_SMALLER_OR_EQUAL_SEQ2(SegmentDescriptorPtr->SegAck, TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx)))
  {
    /* Our SYN has been acknowledged. */

    /* #10 Switch to connection state ESTABLISHED */

    TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_ESTABLISHED);                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_INVALID);                                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
    /* Temporary decrease the cwnd here by 1 (for the SYN), the cwnd will be increased by this 1 in the next state some lines further down */
    TcpIp_SetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx, (TcpIp_GetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx) - 1u));         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif

#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
    /* #20 Reset the keep alive trigger */
    TcpIp_Tcp_VKeepAliveTrigger(SocketTcpIdx);
#endif

#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
    /* #30 Reset the retransmission timeout */
    if (TcpIp_IsRtoResetPendingOfSocketTcpTsOptDyn(SocketTcpIdx) == TRUE)
    {
      TcpIp_SetRtoValidOfSocketTcpTsOptDyn(       SocketTcpIdx, TCPIP_TCP_TX_RETRY_INT_RESET_VALUE_CYCLES);             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetRtoOfSocketTcpTsOptDyn(            SocketTcpIdx, TCPIP_TCP_TX_RETRY_INT_RESET_VALUE_CYCLES);             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetRtoResetPendingOfSocketTcpTsOptDyn(SocketTcpIdx, FALSE);                                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
#endif

    /* #40 Propagate the connection state to the socket owner */
    if (TcpIp_VSockTcpStateChgAccepted(SocketTcpIdx) == E_OK)
    {
      /* Update send window according to received segment */
      TcpIp_SetSndWndOfSocketTcpDyn(SocketTcpIdx, SegmentDescriptorPtr->SegWnd);                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetSndWl1OfSocketTcpDyn(SocketTcpIdx, SegmentDescriptorPtr->SegSeq);                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetSndWl2OfSocketTcpDyn(SocketTcpIdx, SegmentDescriptorPtr->SegAck);                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
    else
    {
      /* #50 The socket owner refused the incoming connection -> Reset the TCP connection */
      (void)TcpIp_Close(TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx), TRUE);
      retVal = E_NOT_OK;  /* leave the RxIndication without further processing of the received message */
    }
  }
  else
  {
    /* send reset <SEQ=SEG.ACK><CTL=RST> */
    TcpIp_Tcp_VSendReset(SocketTcpIdx, TCPIP_LOCAL_ADDR_IDX_TO_IPVX(LocalAddrIdx), RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr->SegAck, 0u, 0u); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    retVal = E_NOT_OK;
  }

  return retVal;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /*
  States:
  TCPIP_TCP_SOCK_STATE_ESTABLISHED
  TCPIP_TCP_SOCK_STATE_CLOSEWAIT
  TCPIP_TCP_SOCK_STATE_FINWAIT1
  TCPIP_TCP_SOCK_STATE_FINWAIT2
  TCPIP_TCP_SOCK_STATE_CLOSING
  */

  Std_ReturnType  retVal = E_OK;

  if (   TCPIP_TCP_SEQ1_SMALLER_OR_EQUAL_SEQ2(TcpIp_GetSndUnaOfSocketTcpDyn(SocketTcpIdx), SegmentDescriptorPtr->SegAck) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && TCPIP_TCP_SEQ1_SMALLER_OR_EQUAL_SEQ2(SegmentDescriptorPtr->SegAck, TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx)))
  {
    /* The ACK lies inside (or on the border) of the current send window */
    /* #10 Update the retransmission timer acccording to the received segment */
    TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateRetransmitTimer1(SocketTcpIdx, SegmentDescriptorPtr);              /* SBSW_TCPIP_FC_PASSING_API_POINTER */

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
    if (TCPIP_TCP_SEQ1_SMALLER_SEQ2(TcpIp_GetSndUnaOfSocketTcpDyn(SocketTcpIdx), SegmentDescriptorPtr->SegAck))
    {
      /* #20 Upate congestion control parameters for new received data */
      TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateCongestionControlNewData(SocketTcpIdx, SegmentDescriptorPtr);    /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    }
    else
    {
      /* #30 Upate congestion control parameters without new received data */
      TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateCongestionControlNoNewData(SocketTcpIdx, SegmentDescriptorPtr);  /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    }
#endif  /* (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON) */

    /* #40 Update send window and KeepAlive trigger, and eventually release retry queue elements */
    TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateWindowAndKeepAlive(SocketTcpIdx, SegmentDescriptorPtr);            /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }
  else if (TCPIP_TCP_SEQ1_BIGGER_SEQ2(TcpIp_GetSndUnaOfSocketTcpDyn(SocketTcpIdx), SegmentDescriptorPtr->SegAck))
  {
    /* The ACK acknowledges data that already has been acked earlier. */
    /* #50 Update the retransmission timer acccording to the received segment */
    TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateRetransmitTimer2(SocketTcpIdx, SegmentDescriptorPtr);              /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }
  else /* else if (TCPIP_TCP_SEQ1_BIGGER_SEQ2(SegmentDescriptorPtr->SegAck, TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx))) */
  {
    /* The ACK acknowledges data that has not yet been sent. */
    /* #60 Send an ACK to inform the peer about the last byte that already has been acked, and drop the message. */
    TcpIp_Tcp_VSendFlags(SocketTcpIdx, TCPIP_TCP_CODE_BIT_ACK);
    retVal = E_NOT_OK;
  }

  if (retVal == E_OK)
  {
    /* #70 Enhance the TCP connection state */
    TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_AdvanceConnectionState(SocketTcpIdx, SegmentDescriptorPtr);              /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }

  return retVal;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateRetransmitTimer1
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateRetransmitTimer1(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  if (TCPIP_TCP_SEQ1_SMALLER_SEQ2(TcpIp_GetSndUnaOfSocketTcpDyn(SocketTcpIdx), SegmentDescriptorPtr->SegAck))
  {
    /* #10 New data is acknowledged, reset retransmit timings */
#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
    TcpIp_SetRetransmitTimeoutOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx));         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetRtoReloadValueOfSocketTcpDyn(   SocketTcpIdx, TcpIp_GetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx));         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#else
    TcpIp_SetRetransmitTimeoutOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetRetransTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX));    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetRtoReloadValueOfSocketTcpDyn(   SocketTcpIdx, TcpIp_GetRetransTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX));    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif
  }
  else
  {
    /* #20 No new data received, SegLen == 0 */
    if (TcpIp_GetSndWndOfSocketTcpDyn(SocketTcpIdx) == 0u)
    {
      /* #30 This is a Zero window probe ACK */

      uint32 reloadValue;
      /* #40 Reset retransmission timer / cwnd idle timer */
#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
      reloadValue = TcpIp_GetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx);
#else
      reloadValue = TcpIp_GetRetransTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX);
#endif
      TcpIp_SetIdleTimeoutShortOfSocketTcpDyn(SocketTcpIdx, (reloadValue + 2u));                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      /* #50 Reset retransmit timing of zero window probe element in retry queue (if available) */
      TcpIp_SetRetransmitTimeoutOfSocketTcpDyn(SocketTcpIdx, reloadValue);                                              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetRtoReloadValueOfSocketTcpDyn(   SocketTcpIdx, reloadValue);                                              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
  }
}


#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateCongestionControlNewData
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateCongestionControlNewData(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* new data is acknowledged */
  uint32 smss = TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx);  /* sender maximum segment size */
  uint32 ackedBytes = SegmentDescriptorPtr->SegAck - TcpIp_GetSndUnaOfSocketTcpDyn(SocketTcpIdx);
    /* The variable 'ackedBytes' is named 'N' in RFC 5681 section 3.1 equation (2). */
    /* Here, SegAck is always bigger than SndUna (regarding the comparison rule for sequence numbers). */

  TcpIp_SetCwndSegNumLimitOfSocketTcpCongCtrlDyn(SocketTcpIdx, 0);                                                      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* #10 Proceed dependent on CongestionControlMode */
  if (TcpIp_GetCongestionControlModeOfSocketTcpCongCtrlDyn(SocketTcpIdx) == TCPIP_TCP_CONG_CTRL_MODE_SLOW_START)
  {
    /* #20 Increment cwnd */
    CANOE_WRITE_STRING_2("TcpIp_Tcp_RxInd: SocketTcpIdx %d: inc cwnd in slow start, SegAck is %d", SocketTcpIdx, SegmentDescriptorPtr->SegAck);
    TcpIp_Tcp_VIncCwnd(SocketTcpIdx, ackedBytes);
  }
  else if (TcpIp_GetCongestionControlModeOfSocketTcpCongCtrlDyn(SocketTcpIdx) == TCPIP_TCP_CONG_CTRL_MODE_CONGESTION_AVOIDANCE)
  {
    /* #30 Summarize incoming ACKs */
    TcpIp_Tcp_VIncAckSumN(SocketTcpIdx, ackedBytes);
  }
  else   /* fast recover ('fast retransmit' is no 'stable' state) */
  {
    /* reset duplicate ACK counter */
    TcpIp_SetDupAckCntOfSocketTcpCongCtrlDyn(SocketTcpIdx, 0);                                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

    /* RFC 6582, 3.2 step 3 */
    if (TCPIP_TCP_SEQ1_BIGGER_SEQ2(SegmentDescriptorPtr->SegAck, TcpIp_GetRecoverOfSocketTcpCongCtrlDyn(SocketTcpIdx)))
    {
      /* #40 Full ack, calculate and update new value of cwnd, then go to congestion control mode CONGESTION_AVOIDANCE. */

      uint32 flightSize;  /* flightSize is the amount of outstanding data in the network */
      uint32 max1;
      uint32 min1;

      /* Calculate the FlightSize */
      flightSize = TcpIp_Tcp_VCalcFlightSize(SocketTcpIdx);

      /* cwnd = min (ssthresh, max(flightSize, SMSS) + SMSS) */
      if (flightSize > smss)
      {
        max1 = flightSize;
      }
      else
      {
        max1 = smss;
      }

      if (TcpIp_GetSsthreshOfSocketTcpCongCtrlDyn(SocketTcpIdx) < (max1 + smss))
      {
        min1 = TcpIp_GetSsthreshOfSocketTcpCongCtrlDyn(SocketTcpIdx);
      }
      else
      {
        min1 = max1 + smss;
      }
      TcpIp_SetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx, min1);                                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      CANOE_WRITE_STRING_2("TcpIp_Tcp_RxInd: SocketTcpIdx %d: cwnd set to %d after full ack", SocketTcpIdx, TcpIp_GetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx));

      /* exit fast recovery procedure */
      TcpIp_SetCongestionControlModeOfSocketTcpCongCtrlDyn(SocketTcpIdx, TCPIP_TCP_CONG_CTRL_MODE_CONGESTION_AVOIDANCE); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

    }
    else
    {
      /* #50 Partial ack, retransmit the first unacknowledged segment (fast retransmit) */
      /* -> set retransmit timeout of the first element to '0', then it will be sent in the next MainFunction */
      TcpIp_SetFastRetransmitPendingOfSocketTcpCongCtrlDyn(SocketTcpIdx, TRUE);                                         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      /* deflate cwnd */
      TcpIp_SetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx, (TcpIp_GetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx) - ackedBytes)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      if (ackedBytes >= smss)
      {
        TcpIp_SetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx, (TcpIp_GetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx) + smss));  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
      CANOE_WRITE_STRING_2("TcpIp_Tcp_RxInd: SocketTcpIdx %d: cwnd set to %d after partial ack", SocketTcpIdx, TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx));

      /* do not exit fast recovery procedure */
    }
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateCongestionControlNoNewData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateCongestionControlNoNewData(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* ACK with same value as in last message / no new data is ACKed */
  if (TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx) != TcpIp_GetSndUnaOfSocketTcpDyn(SocketTcpIdx))  /* data was sent, but no new data was ACKed */
  {
    /* #10 A duplicated ACK has been received, increase the count for ACKs. */
    if (TcpIp_GetDupAckCntOfSocketTcpCongCtrlDyn(SocketTcpIdx) < 255u)
    {
      TcpIp_IncDupAckCntOfSocketTcpCongCtrlDyn(SocketTcpIdx);                                                           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }

    /* #20 Proceed dependent on the number of received ACKs. */
    switch (TcpIp_GetDupAckCntOfSocketTcpCongCtrlDyn(SocketTcpIdx))
    {
    case 1:
    case 2:
      {
        /* send one new (previously unsent) packet with max SMSS (only a 'SHOULD' in the RFC) -> not implemented */
        break;
      }
    case 3:
      {
        /* this is the third received ACK */

        if (TCPIP_TCP_SEQ1_BIGGER_SEQ2((SegmentDescriptorPtr->SegAck - 1u), TcpIp_GetRecoverOfSocketTcpCongCtrlDyn(SocketTcpIdx)))
        {
          TcpIp_SizeOfTcpRetryQElementType eleIdx;
          TcpIp_SizeOfTcpRetryQElementType lastEleIdx;

          /* #30 Start 'fast retransmit' and 'fast recover' */

          /* check TransmitCounter of all retry queue elements for this socket */
          lastEleIdx = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;
          eleIdx = TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx);
          /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          while (   (eleIdx < TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV)
                 && (TcpIp_GetAddrTcpRetryQElement(eleIdx)->TransmitCounter > 0u))
          {
            lastEleIdx = eleIdx;
            eleIdx     = TcpIp_GetAddrTcpRetryQElement(eleIdx)->EleNext;
          }
          if (lastEleIdx != TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV)
          {
            TcpIp_SetRecoverOfSocketTcpCongCtrlDyn(SocketTcpIdx, ((TcpIp_GetAddrTcpRetryQElement(lastEleIdx)->SeqNo +   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
              TcpIp_GetAddrTcpRetryQElement(lastEleIdx)->SizeTotByte) - 1u));
          }

          /* enter fast retransmit (step 2 of Section 3.2 in RFC5681) */

          /* set ssthresh */
          TcpIp_Tcp_VSetSsthreshEqu4(SocketTcpIdx);

          /* retransmit the first element in the RetrQueue immediately */
          TcpIp_SetFastRetransmitPendingOfSocketTcpCongCtrlDyn(SocketTcpIdx, TRUE);                                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

          /* set cwnd */
          TcpIp_SetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx, (TcpIp_GetSsthreshOfSocketTcpCongCtrlDyn(SocketTcpIdx) +    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
            (3u * (uint32) TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx))));

          /* enter fast recover */
          TcpIp_SetCongestionControlModeOfSocketTcpCongCtrlDyn(SocketTcpIdx, TCPIP_TCP_CONG_CTRL_MODE_FAST_RECOVER);    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        }
        else
        {
          /* do not enter fast retransmit */
        }

        break;
      }
    default:
      {
        /* 4 or more duplicated ACKs */
        /* #40 Inc cwnd by SMSS */
        TcpIp_SetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx,                                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
          (TcpIp_GetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx) + TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx)));

        /* sending of additional available data (1*SMSS) is done in the MainFunction. No extra handling needed,
        since the MainFunction tries to send as much data as the cwnd allows, so this update is done automatically. */
        break;
      }
    }
  }
  else
  {
    /* no data was sent, but new data was received */
    /* do nothing */
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif  /* (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON) */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateWindowAndKeepAlive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateWindowAndKeepAlive(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  TcpIp_SetSndUnaOfSocketTcpDyn(SocketTcpIdx, SegmentDescriptorPtr->SegAck);                                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
  /* #10 Reset keep alive timer */
  TcpIp_Tcp_VKeepAliveTrigger(SocketTcpIdx);
#endif

  /* TcpIp_Tcp_VFreeAckedReqAndRetrElements() will be called in MainFunction. */

  /* #20 Adjust the receive window */
  if (   TCPIP_TCP_SEQ1_SMALLER_SEQ2(TcpIp_GetSndWl1OfSocketTcpDyn(SocketTcpIdx), SegmentDescriptorPtr->SegSeq)         /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (   (TcpIp_GetSndWl1OfSocketTcpDyn(SocketTcpIdx) == SegmentDescriptorPtr->SegSeq)
          && TCPIP_TCP_SEQ1_SMALLER_OR_EQUAL_SEQ2(TcpIp_GetSndWl2OfSocketTcpDyn(SocketTcpIdx), SegmentDescriptorPtr->SegAck)))
  {
    /* set send window according to received segment */
    if (TcpIp_GetSndWndOfSocketTcpDyn(SocketTcpIdx) != SegmentDescriptorPtr->SegWnd)
    {
      if (TcpIp_GetSndWndOfSocketTcpDyn(SocketTcpIdx) == 0u)
      {
        /* This is a window update. Zero window is opened again. */
        /* Reset retransmission timeout of zero window probes. */
        TcpIp_SetRetransmitTimeoutOfSocketTcpDyn(SocketTcpIdx, 0);                                                      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }

      TcpIp_SetSndWndOfSocketTcpDyn(SocketTcpIdx, SegmentDescriptorPtr->SegWnd);                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }

    TcpIp_SetSndWl1OfSocketTcpDyn(SocketTcpIdx, SegmentDescriptorPtr->SegSeq);                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetSndWl2OfSocketTcpDyn(SocketTcpIdx, SegmentDescriptorPtr->SegAck);                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateRetransmitTimer2
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_UpdateRetransmitTimer2(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  if (   (TcpIp_GetSndWndOfSocketTcpDyn(SocketTcpIdx) == 0u)                                                             /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_GetSndUnaOfSocketTcpDyn(SocketTcpIdx) == (SegmentDescriptorPtr->SegAck + 1u)))
  {
    /* send window is closed, and one single byte is in the send-queue */
    /* #10 Ignore this ACK,it is an answer to a zero-window-probe */
    TcpIp_SizeOfTcpRetryQElementType retryQFirstElementIdx = TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx);

    TCPIP_ASSERT(retryQFirstElementIdx < TcpIp_GetSizeOfTcpRetryQElement());

    /* #20 Reset user timeout */
#if (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON)
    TcpIp_GetAddrTcpRetryQElement(retryQFirstElementIdx)->UserTimeoutTs = TcpIp_Tcp_GlobalTimestamp + TcpIp_GetUtoOfSocketTcpUtoDyn(SocketTcpIdx); /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx_ValidFirstQueueElement */
#else
    TcpIp_GetAddrTcpRetryQElement(retryQFirstElementIdx)->UserTimeoutTs = TcpIp_Tcp_GlobalTimestamp + TcpIp_GetUserTimeoutDefCyclesOfTcpConfig(TCPIP_TCPCONFIG_IDX); /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx_ValidFirstQueueElement */
#endif
#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
    TcpIp_Tcp_VKeepAliveTrigger(SocketTcpIdx);
#endif
    /* #30 Reset retransmission timeout */
    {
      uint32 newTimeout;
      TcpIp_GetAddrTcpRetryQElement(retryQFirstElementIdx)->TransmitCounter = 1;                                        /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx_ValidFirstQueueElement */
#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
      newTimeout = TcpIp_GetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx);
#else
      newTimeout = TcpIp_GetRetransTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX);
#endif
      TcpIp_SetRetransmitTimeoutOfSocketTcpDyn(SocketTcpIdx, newTimeout);                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetRtoReloadValueOfSocketTcpDyn(   SocketTcpIdx, newTimeout);                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_AdvanceConnectionState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_3_AdvanceConnectionState(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* #10 Advance TCP connection state dependent on the current connection state. [IETF RFC793 Page 73] */

  if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_FINWAIT1)
  {
    if (   ((TcpIp_GetTxFlagsOfSocketTcpDyn(SocketTcpIdx) & TCPIP_TCP_CODE_BIT_FIN) == 0u)                               /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        &&  (TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx) == SegmentDescriptorPtr->SegAck))
    {
      /* our FIN is now acknowledged -> switch to state FINWAIT2 */
      TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_FINWAIT2);                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_INVALID);                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
  }

  if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_FINWAIT2)
  {
    /* the retransmission queue is empty now */

    /* acknowledge the user's close request ('ok') */

    /* Start the FINWAIT-2 timeout timer, value of 0 means the timeout is deactivated */
    /* FINWAIT-2 timeout is reset if any packet arrives in FINWAIT-2 state */
    TcpIp_SetFinWait2TimeoutOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetFinWait2TimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX));     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_CLOSEWAIT)
  {
    /* same as in state ESTABLISHED, nothing extra to do */
  }
  else if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_CLOSING)
  {
    if (   ((TcpIp_GetTxFlagsOfSocketTcpDyn(SocketTcpIdx) & TCPIP_TCP_CODE_BIT_FIN) == 0u)                               /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        &&  (TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx) == SegmentDescriptorPtr->SegAck))
    {
      /* our FIN is now acknowledged -> switch to state TIMEWAIT */
      TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_TIMEWAIT);                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_CLOSED);                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      TcpIp_SetMslTimeoutOfSocketTcpDyn(SocketTcpIdx, (uint32) (2u * (uint32) TcpIp_GetMslOfTcpConfig(TCPIP_TCPCONFIG_IDX)));             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
      TcpIp_Tcp_VKeepAliveReset(SocketTcpIdx);
#endif
    }
    else
    {
      /* ignore the segment */
    }
  }
  else
  {
    /* nothing to do (required by MISRA) */
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_LastAck
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_LastAck(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /*
  States:
  TCPIP_TCP_SOCK_STATE_LASTACK
  */

  /* Finally close the socket if all conditions are fulfilled */

  /* #10 Check if our FIN is acknowledged */
  if (   ((TcpIp_GetTxFlagsOfSocketTcpDyn(SocketTcpIdx) & TCPIP_TCP_CODE_BIT_FIN) == 0u)                                 /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      &&  (TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx) == SegmentDescriptorPtr->SegAck))
  {
    /* our FIN is now acknowledged */

    /* TcpIp_Tcp_VFreeAckedReqAndRetrElements() will be called in MainFunction. */

    /* All data sent is acked -> cancel idle timeout */
    /* #20 Our FIN is acked, switch to state CLOSED, delete/clear TCB element, and return. */
    TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_CLOSED);
  }
  else
  {

    /* #30 Our FIN is not acked. Send an ACK indicating the expected ACK number, or silently ignore the segment */
    /* The sequence number is already checked earlier in TcpIp_Tcp_VRxIndicationStateOthers_First() */
    if (TCPIP_TCP_SEQ1_SMALLER_OR_EQUAL_SEQ2(SegmentDescriptorPtr->SegAck, TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx)))
    {
      /* The ACK is acceptable. Silently ignore segment if the ACK is a duplicate (already known). */
    }
    else
    {
      /* The ACK is not acceptable. Send ACK to announce the currently expected sequence number. Only the very last ACK
      is expected to finally close the socket. */
      TcpIp_Tcp_VSendFlags(SocketTcpIdx, (TCPIP_TCP_CODE_BIT_ACK));
    }
  }
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Fifth_TimeWait
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Fifth_TimeWait(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /*
  States:
  TCPIP_TCP_SOCK_STATE_TIMEWAIT
  */

  Std_ReturnType  retVal = E_OK;

  /* #10 Reset MSL Timeout if our FIN is acked. */
  if (   ((TcpIp_GetTxFlagsOfSocketTcpDyn(SocketTcpIdx) & TCPIP_TCP_CODE_BIT_FIN) == 0u)                                 /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      &&  (TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx) == SegmentDescriptorPtr->SegAck))
  {
    /* Our FIN is now acknowledged (again, this is a duplicate) */
    /* sending ACK is already triggered earlier */

    /* reset MSL Timeout */
    TcpIp_SetMslTimeoutOfSocketTcpDyn(SocketTcpIdx, (2u * (uint32) TcpIp_GetMslOfTcpConfig(TCPIP_TCPCONFIG_IDX)));      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else
  {
    if ((TCPIP_TCP_CODE_BIT_URG & SegmentDescriptorPtr->CodeBits) == 0u)
    {
      /* send ACK */
      TcpIp_Tcp_VSendFlags(SocketTcpIdx, (TCPIP_TCP_CODE_BIT_ACK));
    }
    else
    {
      /* only the very last ACK is expected, do not respond to frames with not supported 'urgent' data */
    }
    retVal = E_NOT_OK;
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Sixth
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Sixth(
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* RFC: sixth check the URG bit */
  /*
  States:
  TCPIP_TCP_SOCK_STATE_SYNRCVD
  TCPIP_TCP_SOCK_STATE_ESTABLISHED
  TCPIP_TCP_SOCK_STATE_CLOSEWAIT
  TCPIP_TCP_SOCK_STATE_LASTACK
  TCPIP_TCP_SOCK_STATE_FINWAIT1
  TCPIP_TCP_SOCK_STATE_FINWAIT2
  TCPIP_TCP_SOCK_STATE_CLOSING
  TCPIP_TCP_SOCK_STATE_TIMEWAIT
  */

  Std_ReturnType  retVal = E_OK;

  /* #10 Check that the 'urgent' bit is not set, otherwise drop the segment */
  /* Since 'urgent data' is not supported by this implementation, any segment with the 'URG' flag set shall be dropped,
     regardless of the length of the urgent data. */
  if ((TCPIP_TCP_CODE_BIT_URG & SegmentDescriptorPtr->CodeBits) != 0u)
  {
    /* usage of urgend pointer/data is not supported by this implementation
       --> drop segment */
    retVal = E_NOT_OK;
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)  /* PRQA S 3673 */ /* MD_TCPIP_Rule8.13_CfgSpecific */
{
  /* RFC: seventh process the segment text */
  /*
  States:
  TCPIP_TCP_SOCK_STATE_SYNRCVD
  TCPIP_TCP_SOCK_STATE_ESTABLISHED
  TCPIP_TCP_SOCK_STATE_CLOSEWAIT
  TCPIP_TCP_SOCK_STATE_LASTACK
  TCPIP_TCP_SOCK_STATE_FINWAIT1
  TCPIP_TCP_SOCK_STATE_FINWAIT2
  TCPIP_TCP_SOCK_STATE_CLOSING
  TCPIP_TCP_SOCK_STATE_TIMEWAIT
  */

  Std_ReturnType  retVal = E_OK;

  /* #10 Process the text segment only in states ESATBLISHED, FINWAIT1 and FINWAIT2. */
  switch (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx))
  {
  case TCPIP_TCP_SOCK_STATE_ESTABLISHED:
  case TCPIP_TCP_SOCK_STATE_FINWAIT1:
  case TCPIP_TCP_SOCK_STATE_FINWAIT2:
    {
      /* Once the TCP takes responsibility for the data it advances RCV.NXT over the data
      accepted, and adjusts RCV.WND as apporopriate to the current buffer availability. The
      total of RCV.NXT and RCV.WND should not be reduced. */

      /* Check the segment length not to be 0. */
      if (SegmentDescriptorPtr->SegLen > 0u)
      {
        /* Check the start postion of the received segment. */
        if (SegmentDescriptorPtr->SegSeq == TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx))
        {
          /* #20 The segment starts right at the start of the receive window, so copy the payload into the rx buffer. */
          if (SegmentDescriptorPtr->SegLen <= TcpIp_GetRxMssOfTcpConfig(TCPIP_TCPCONFIG_IDX))
          {
            TcpIp_SizeOfTcpRxBufferDescType tcpRxBufferDescIdx = TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx);

            if ((TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(tcpRxBufferDescIdx) - TcpIp_GetFillLevelOfTcpRxBufferDescDyn(tcpRxBufferDescIdx)) >= SegmentDescriptorPtr->SegLen)
            {
              /* data fits into rx buffer */

              /* copy received data to rx buffer and trigger sending an ACK */
              TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CopyRxDataAndTriggerAck(SocketTcpIdx, tcpRxBufferDescIdx, SegmentDescriptorPtr); /* SBSW_TCPIP_FC_PASSING_API_POINTER */

              /* now check if elements from the PreBufArray follow this segment directly */
#if (TCPIP_SUPPORT_TCP_RX_OOO == STD_ON)
              /* Append pre-buffered data to RxData if available and matching */
              TcpIp_Tcp_VRxIndicationStateOthers_Seventh_ReceiveBufferedData(SocketTcpIdx, tcpRxBufferDescIdx, SegmentDescriptorPtr); /* SBSW_TCPIP_FC_PASSING_API_POINTER */
#endif
            }
            else
            {
              /* data doesn't fit into rx buffer */
              /* Discard message (maybe partly). Don't evaluate FIN flag! */
              retVal = E_NOT_OK;
            }
          }
          else
          {
            /* segmemt size larger than allowed */
            /* Discard message. Don't evaluate FIN flag! */
            retVal = E_NOT_OK;
          }
        }
        else
        {
          /* out of order message, previous message is missing */

          /* #30 The segment does not start at the start of the receive window, so queue this message if the feature is
          enabled and if enough control elements are available. */

#if (TCPIP_SUPPORT_TCP_RX_OOO == STD_ON)
          /* queue this message if possible (enough memory in buffer, control element available) */

          /*
          check if there are already elements in the queue.
          - if true, check if new segment can be combined with existing one (left or right side).
          ....If it could be combined, check if two elements can be merged to one, if yes do it and remove unneeded element by moving following elements forward.
          - if false, add segment to list (this will be the first element in the list)
          */

          boolean segCouldBeStored;  /* Indicates if the received segment could be stored and could be combined with
                                     an already existing one.  */

          TCPIP_ASSERT(TcpIp_HasSocketTcpOooDyn() == TRUE);

          /* #40 Check if ooo (out of order) list already contains elements */
          if (TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx) == 0u)
          {
            /* the ooo list for this socket is empty, so insert a new one */
            segCouldBeStored = TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CreateFirstOooElement(SocketTcpIdx, SegmentDescriptorPtr); /* SBSW_TCPIP_FC_PASSING_API_POINTER */
          }
          else
          {
            /* check if new segment can be combined with existing one (left or right side) */
            segCouldBeStored = TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CheckCombination(SocketTcpIdx, SegmentDescriptorPtr); /* SBSW_TCPIP_FC_PASSING_API_POINTER */

            if (segCouldBeStored == FALSE)
            {
              /* the segment could not be combined with an existing one, so an extra element is needed */
              segCouldBeStored = TcpIp_Tcp_VRxIndicationStateOthers_Seventh_InsertNewOooElement(SocketTcpIdx, SegmentDescriptorPtr); /* SBSW_TCPIP_FC_PASSING_API_POINTER */
            }
          }

          if (segCouldBeStored == TRUE)
          {
            /* #50 Copy data to rx buffer. */
            TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CopyDataToBuffer(SocketTcpIdx, SegmentDescriptorPtr);            /* SBSW_TCPIP_FC_PASSING_API_POINTER */
          }
          else
          {
            /* Packet will be dropped, beause no control element is free to process this data, even the rx window is not full.*/
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
            /* Increment the measurement data counter for dropped TCP message (due to insufficient Rx buffer) */
            TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_RX_BUFFER);
#endif
          }
#endif  /* (TCPIP_SUPPORT_TCP_RX_OOO == STD_ON) */
        }
      }
      break;
    }
  default:
    {
      /* TCPIP_TCP_SOCK_STATE_SYNRCVD:
         -> ignore segment because the connection is not yet fully established.

         OR:

         TCPIP_TCP_SOCK_STATE_CLOSEWAIT,
         TCPIP_TCP_SOCK_STATE_CLOSING,
         TCPIP_TCP_SOCK_STATE_LASTACK,
         TCPIP_TCP_SOCK_STATE_TIMEWAIT:
         -> ignore the segment text because the connection is already about to close since we already received a FIN */
    }
    break;
  }

  return retVal;
}  /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CopyRxDataAndTriggerAck
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CopyRxDataAndTriggerAck(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TcpIp_SizeOfTcpRxBufferDescType TcpRxBufferDescIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* RFC: seventh process the segment text */

  /*
  States:
  TCPIP_TCP_SOCK_STATE_ESTABLISHED
  TCPIP_TCP_SOCK_STATE_FINWAIT1
  TCPIP_TCP_SOCK_STATE_FINWAIT2
  */

  uint8 *tcpRxBufferWritePtr;

  TCPIP_ASSERT(TcpIp_GetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(TcpRxBufferDescIdx) >= TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx));
  TCPIP_ASSERT(TcpIp_GetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(TcpRxBufferDescIdx) <  TcpIp_GetTcpRxBufferEndIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx));

  tcpRxBufferWritePtr = TcpIp_GetAddrTcpRxBuffer(TcpIp_GetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(TcpRxBufferDescIdx));
  /* #10 Check if data exceeds the buffer boundaries and a wrap-around is needed. */
  if ((TcpIp_GetTcpRxBufferEndIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx) - SegmentDescriptorPtr->SegLen) < TcpIp_GetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(TcpRxBufferDescIdx))
    /* calculating '(WriteIdx + SegLen) > EndIdx' is not allowed since the sum could cause an integer overrun */
  {
    /* #20 Copy data with taking care of buffer wrap-around (two blocks). */
    TcpIp_SizeOfTcpRxBufferType copyLenByte;

    /* copy the first part: bytes 0..((TCPIP_TCP_MAX_WINDOW_SIZE - RxBufferWritePos[SocketTcpIdx]) - 1) */
    copyLenByte = TcpIp_GetTcpRxBufferEndIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx) - TcpIp_GetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(TcpRxBufferDescIdx);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpBase_Copy(tcpRxBufferWritePtr, SegmentDescriptorPtr->PayloadPtr, copyLenByte);                                    /* SBSW_TCPIP_CopyDataToRxBuffer */

    /* copy the second part: bytes (TCPIP_TCP_MAX_WINDOW_SIZE - RxBufferWritePos[SocketTcpIdx])..(SegmentDescriptorPtr->SegLen - 1) */
    tcpRxBufferWritePtr = TcpIp_GetAddrTcpRxBuffer(TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx));
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpBase_Copy(tcpRxBufferWritePtr,                                                                                    /* SBSW_TCPIP_CopyDataToRxBuffer */
      &(SegmentDescriptorPtr->PayloadPtr)[copyLenByte],
      (SegmentDescriptorPtr->SegLen  - copyLenByte));

    TCPIP_ASSERT(TcpIp_GetTcpRxBufferEndIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx) >
      (TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx) + (SegmentDescriptorPtr->SegLen  - copyLenByte)));

    TcpIp_SetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(TcpRxBufferDescIdx,                                                /* SBSW_TCPIP_AWA_CSL_Valid_BufferIdx_CALLER */
      TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx) + (SegmentDescriptorPtr->SegLen  - copyLenByte));
  }
  else
  {
    /* #30 Copy bytes 0..(SegmentDescriptorPtr->SegLen - 1). */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpBase_Copy(tcpRxBufferWritePtr, SegmentDescriptorPtr->PayloadPtr, SegmentDescriptorPtr->SegLen);                   /* SBSW_TCPIP_CopyDataToRxBuffer */

    TcpIp_SetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(TcpRxBufferDescIdx,                                                /* SBSW_TCPIP_AWA_CSL_Valid_BufferIdx_CALLER */
      TcpIp_IncRxBufIdx(TcpRxBufferDescIdx, TcpIp_GetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(TcpRxBufferDescIdx), SegmentDescriptorPtr->SegLen ));
  }

  TCPIP_VENTER_CRITICAL_SECTION();

  /* #40 Update rx buffer variables. */
  TcpIp_AddFillLevelOfTcpRxBufferDescDyn(TcpRxBufferDescIdx, SegmentDescriptorPtr->SegLen);                             /* SBSW_TCPIP_AWA_CSL_Valid_BufferIdx_CALLER */
  TcpIp_SetRxBufferRemIndLenOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetRxBufferRemIndLenOfSocketTcpDyn(SocketTcpIdx) + SegmentDescriptorPtr->SegLen)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* #50 Update receive window. */
  TcpIp_SetRcvWndOfSocketTcpDyn(SocketTcpIdx, (uint16)(TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(TcpRxBufferDescIdx) - /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_GetFillLevelOfTcpRxBufferDescDyn(TcpRxBufferDescIdx)));
  TcpIp_SetRcvNxtOfSocketTcpDyn(SocketTcpIdx, (SegmentDescriptorPtr->SegSeq + SegmentDescriptorPtr->SegLen));           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  TCPIP_VLEAVE_CRITICAL_SECTION();

  /* #60 Send ACK for the received data. */
  /* Send ACK: <SEQ=SND.NXT><ACK=RCV.NXT><CTL=ACK> */
  TcpIp_Tcp_VSendFlags(SocketTcpIdx, TCPIP_TCP_CODE_BIT_ACK);
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


#if (TCPIP_SUPPORT_TCP_RX_OOO == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh_ReceiveBufferedData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh_ReceiveBufferedData(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TcpIp_SizeOfTcpRxBufferDescType TcpRxBufferDescIdx,
  TCPIP_P2V(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* #10 Check if pre-buffered elements are available. */
  if (TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx) > 0u)
  {
    /* only the first element in the ooo list migth match (all following have missing segments in between) */
    if (TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx) == TcpIp_GetAddrTcpOooQElement(TcpIp_GetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx))->SeqNo)
    {
      /* this element fits -> trigger RxIndication */

      TCPIP_VENTER_CRITICAL_SECTION();

      /* The received segment adjoins the out of order stored element. So the length of the ooo element can be added to
      the received segment and make it one bigger segment for further processing. */
      SegmentDescriptorPtr->SegLen  = TcpIp_GetAddrTcpOooQElement(TcpIp_GetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx))->LenByte; /* SBSW_TCPIP_PWA_ValidSegmentDescPtr_CALLER */

      /* #20 Update rx buffer variables. */
      TCPIP_ASSERT(TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(TcpRxBufferDescIdx) < 0x0000FFFFu);
      /* increase buffer position, taking care of the wraparound */
      TcpIp_SetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(TcpRxBufferDescIdx, TcpIp_IncRxBufIdx(TcpRxBufferDescIdx,        /* SBSW_TCPIP_AWA_CSL_Valid_BufferIdx_CALLER */
        TcpIp_GetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(TcpRxBufferDescIdx), SegmentDescriptorPtr->SegLen));
      TcpIp_AddFillLevelOfTcpRxBufferDescDyn(TcpRxBufferDescIdx, SegmentDescriptorPtr->SegLen);                         /* SBSW_TCPIP_AWA_CSL_Valid_BufferIdx_CALLER */
      TcpIp_SetRxBufferRemIndLenOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetRxBufferRemIndLenOfSocketTcpDyn(SocketTcpIdx) + SegmentDescriptorPtr->SegLen)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      /* #30 Update receive window. */
      /* Update RcvNxt (for ACK) -> no extra trigger, ACK is already triggered */
      TcpIp_SetRcvWndOfSocketTcpDyn(SocketTcpIdx, (uint16)(TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(TcpRxBufferDescIdx) - TcpIp_GetFillLevelOfTcpRxBufferDescDyn(TcpRxBufferDescIdx))); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetRcvNxtOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx) + SegmentDescriptorPtr->SegLen)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      TCPIP_VLEAVE_CRITICAL_SECTION();

      /* #40 Remove the descriptor element from the queue. */
      {
        TcpIp_SizeOfTcpOooQElementType freeEleIdx = TcpIp_GetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx);
        if (TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx) > 1u)
        {
          TcpIp_SetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx, TcpIp_GetAddrTcpOooQElement(TcpIp_GetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx))->NextEleIdx); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        }
        else
        {
          TcpIp_SetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx, TcpIp_GetSizeOfTcpOooQElement());  /* invalid */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
          /* Reset the OooChangeCounter */
          TcpIp_SetTcpOooChangeCounterOfSocketTcpOooDyn(SocketTcpIdx, 0);                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif
        }
        TcpIp_GetAddrTcpOooQElement(freeEleIdx)->NextEleIdx = TcpIp_Tcp_OooFirstFreeEleIdx;                             /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx_FirstEle */
        TcpIp_Tcp_OooFirstFreeEleIdx = freeEleIdx;
        TcpIp_DecTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx);                                                         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        TcpIp_Tcp_OooNumFreeElements++;

#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
        if (TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx) > 1u)
        {
          /* Update the time-wise linkage of the ooo elements */
          TcpIp_Tcp_VUpdateOooElementChangeOrder(SocketTcpIdx, FALSE, 0);
        }
        else
        {
          /* Set the last remaining ooo element to be the last changed element */
          TcpIp_SetTcpOooQElementLastChangedIdxOfSocketTcpOooDyn(SocketTcpIdx, TcpIp_GetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx));   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        }
#endif
      }
    }
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CheckCombination
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
TCPIP_LOCAL FUNC(boolean, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CheckCombination(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  boolean combinationIsPossible = FALSE;

  TcpIp_SizeOfTcpOooQElementType currentOooEleIdx   = TcpIp_GetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx);
  TcpIp_TcpOooQElementIterType   numCheckedElements = 0;

  /* #10 Go through pre-buffered elements to find elements adjacent to the received segment. */
  while (numCheckedElements < TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx))  /* PRQA S 0771 */ /* MD_TCPIP_TCP_15.4_0771_a */
  {
    /* These checks for segment combination  are only done if there really are some ooo elements available. */
    TcpIp_Tcp_RxPreBufEleType *currentOooElementPtr = TcpIp_GetAddrTcpOooQElement(currentOooEleIdx);

    /* #20 Check for combination possibility. */
    if ((currentOooElementPtr->SeqNo + currentOooElementPtr->LenByte) == SegmentDescriptorPtr->SegSeq)
    {
      /* #30 Match found, received segment can be appended to existing one. -> Combine the segments. */

      currentOooElementPtr->LenByte += SegmentDescriptorPtr->SegLen;                                                    /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */

      if ((numCheckedElements + 1u) < TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx))
      {
        /* there is another ooo element in the queue */
        TcpIp_SizeOfTcpOooQElementType nextEleIdx        = currentOooElementPtr->NextEleIdx;
        TcpIp_Tcp_RxPreBufEleType     *nextOooElementPtr = TcpIp_GetAddrTcpOooQElement(nextEleIdx);

        if ((currentOooElementPtr->SeqNo + currentOooElementPtr->LenByte) == nextOooElementPtr->SeqNo)
        {
          /* current ooo element has 0 distance to the following ooo element */
          /* combine the two elements and delete the second one */

          currentOooElementPtr->LenByte   += nextOooElementPtr->LenByte;                                                /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
          currentOooElementPtr->NextEleIdx = nextOooElementPtr->NextEleIdx;                                             /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */

          /* prepend the now free element to the free elements list */
          TcpIp_DecTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx);                                                       /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
          nextOooElementPtr->NextEleIdx = TcpIp_Tcp_OooFirstFreeEleIdx;                                                 /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
          TcpIp_Tcp_OooFirstFreeEleIdx = nextEleIdx;
          TcpIp_Tcp_OooNumFreeElements++;
        }
        else
        {
          /* current ooo element does not have contact to the next element, so this element is only enlarged by the new
          received segment length */
        }
#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
        /* rescan the whole ooo list and update the 'next older element' relation */
        TcpIp_Tcp_VUpdateOooElementChangeOrder(SocketTcpIdx, TRUE, currentOooEleIdx);
#endif
      }

      combinationIsPossible = TRUE;
      break;  /* stop search for insert position */ /* PRQA S 0771 */ /* MD_TCPIP_TCP_15.4_0771_a */
    }
    else if ((SegmentDescriptorPtr->SegSeq + SegmentDescriptorPtr->SegLen) == currentOooElementPtr->SeqNo)
    {
      /* #40 Match found, received segment can be prepended to existing one. -> Combine the segments. */
      /* the segment won't get in contact with the previous one in the ooo list, because then it would have matched in an earlier check */
#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
      TcpIp_SetTcpOooQElementLastChangedIdxOfSocketTcpOooDyn(SocketTcpIdx, currentOooEleIdx);                           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      /* rescan the whole ooo list and update the 'next older element' relation */
      TcpIp_Tcp_VUpdateOooElementChangeOrder(SocketTcpIdx, TRUE, currentOooEleIdx);
#endif
      currentOooElementPtr->SeqNo    = SegmentDescriptorPtr->SegSeq;                                                    /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
      currentOooElementPtr->LenByte += SegmentDescriptorPtr->SegLen;                                                    /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */

      combinationIsPossible = TRUE;
      break;  /* stop search for insert position */  /* PRQA S 0771 */ /* MD_TCPIP_TCP_15.4_0771_a */
    }
    else
    {
      /* received element can not be combined with current ooo element */
    }

    /* #50 Go to next element. */
    currentOooEleIdx = currentOooElementPtr->NextEleIdx;
    numCheckedElements++;
  }

  return combinationIsPossible;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh_InsertNewOooElement
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
TCPIP_LOCAL FUNC(boolean, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh_InsertNewOooElement(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  boolean segCouldBeStored = FALSE;

  /* #10 Check if there are free ooo elements available. */
  if (TcpIp_Tcp_OooNumFreeElements > 0u)
  {
    TcpIp_SizeOfTcpOooQElementType currentOooEleIdx;
    TcpIp_TcpOooQElementIterType   numCheckedElements;
#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
    TcpIp_SizeOfTcpOooQElementType oldLastChangedElementIdx = TcpIp_GetTcpOooQElementLastChangedIdxOfSocketTcpOooDyn(SocketTcpIdx);
#endif

    /* #20 Take a new element. */
    TcpIp_SizeOfTcpOooQElementType newEleIdx = TcpIp_Tcp_OooFirstFreeEleIdx;
    TcpIp_SizeOfTcpOooQElementType lastValidEleIdx = 0;  /* Init this variable 'lastValidEleIdx' to prevent MISRA checkers to issue the warning message 3353. The variable will always be set to a valid value before it is used */

    TcpIp_Tcp_OooNumFreeElements--;
    if (TcpIp_Tcp_OooNumFreeElements > 0u)
    {
      TcpIp_Tcp_OooFirstFreeEleIdx = TcpIp_GetAddrTcpOooQElement(newEleIdx)->NextEleIdx;
    }
    TcpIp_GetAddrTcpOooQElement(newEleIdx)->SeqNo   = SegmentDescriptorPtr->SegSeq;                                     /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
    TcpIp_GetAddrTcpOooQElement(newEleIdx)->LenByte = SegmentDescriptorPtr->SegLen;                                     /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */

    /* #30 Find insert position for new element. Elements in queue are ordered by sequence number. */
    currentOooEleIdx = TcpIp_GetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx);
    numCheckedElements = 0;
#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
    TcpIp_SetTcpOooQElementLastChangedIdxOfSocketTcpOooDyn(SocketTcpIdx, newEleIdx);                                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif
    while (   (numCheckedElements < TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx))  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
           && (TCPIP_TCP_SEQ1_BIGGER_SEQ2(SegmentDescriptorPtr->SegSeq, TcpIp_GetAddrTcpOooQElement(currentOooEleIdx)->SeqNo)))
    {
      lastValidEleIdx = currentOooEleIdx;
      currentOooEleIdx = TcpIp_GetAddrTcpOooQElement(currentOooEleIdx)->NextEleIdx;
      numCheckedElements++;
    }

    /* #40 Check where to insert the new element into the existing list. */
    if (TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx) != numCheckedElements)
    {
      /* insert new element */
      TcpIp_GetAddrTcpOooQElement(newEleIdx)->NextEleIdx = currentOooEleIdx;                                            /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
      if (numCheckedElements == 0u)
      {
        /* #50 Prepend the element to the list. */
        TcpIp_SetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx, newEleIdx);                                      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
      else
      {
        /* #60 Insert the element somewhere inside the list. */
        TcpIp_GetAddrTcpOooQElement(lastValidEleIdx)->NextEleIdx = newEleIdx;  /* variable is always initialized ! */   /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
      }
      TcpIp_IncTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx);                                                           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
    else
    {
      /* #70 Append new element at the end of the list. */
      TcpIp_GetAddrTcpOooQElement(lastValidEleIdx)->NextEleIdx = newEleIdx;                                             /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
      TcpIp_IncTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx);                                                           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }

#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
    /* #80 Update the 'next older element' relation. */
    /* link the new element to the previous last changed element */
    TcpIp_GetAddrTcpOooQElement(newEleIdx)->OlderEleIdx = oldLastChangedElementIdx;                                     /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */

    /* set current element as the last changed one */
    TcpIp_IncTcpOooChangeCounterOfSocketTcpOooDyn(SocketTcpIdx);                                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_GetAddrTcpOooQElement(newEleIdx)->ChangeCounterValue = TcpIp_GetTcpOooChangeCounterOfSocketTcpOooDyn(SocketTcpIdx);  /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
#endif

    segCouldBeStored = TRUE;
  }
  else
  {
    /* no free element available, so just drop the received segment */
    /* do nothing */
  }

  return segCouldBeStored;
}  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CreateFirstOooElement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(boolean, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CreateFirstOooElement(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  boolean segCouldBeStored = FALSE;
  TcpIp_SizeOfTcpOooQElementType newEleIdx;

  /* The ooo list for this socket is empty, so insert a new one */

  /* #10 Take a free ooo element and insert it into the sockets list. */
  if (TcpIp_Tcp_OooNumFreeElements > 0u)
  {
    newEleIdx = TcpIp_Tcp_OooFirstFreeEleIdx;
#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
    TcpIp_SetTcpOooQElementLastChangedIdxOfSocketTcpOooDyn(SocketTcpIdx, newEleIdx);                                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    /* Set the ChangeCounterValue of the ooo element. There is no next older element it could be linked to. */
    TcpIp_IncTcpOooChangeCounterOfSocketTcpOooDyn(SocketTcpIdx);                                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_GetAddrTcpOooQElement(newEleIdx)->ChangeCounterValue = TcpIp_GetTcpOooChangeCounterOfSocketTcpOooDyn(SocketTcpIdx);  /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
    TcpIp_GetAddrTcpOooQElement(newEleIdx)->OlderEleIdx = TcpIp_GetSizeOfTcpOooQElement();                              /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
#endif
    TcpIp_Tcp_OooFirstFreeEleIdx = TcpIp_GetAddrTcpOooQElement(newEleIdx)->NextEleIdx;
    TcpIp_SetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx, newEleIdx);                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_GetAddrTcpOooQElement(newEleIdx)->SeqNo   = SegmentDescriptorPtr->SegSeq;                                     /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
    TcpIp_GetAddrTcpOooQElement(newEleIdx)->LenByte = SegmentDescriptorPtr->SegLen;                                     /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
    TcpIp_IncTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx);                                                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_Tcp_OooNumFreeElements--;
    segCouldBeStored = TRUE;
  }

  return segCouldBeStored;
}


#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VUpdateOooElementChangeOrder
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VUpdateOooElementChangeOrder(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  boolean ChangedElementIdKnown,
  TcpIp_SizeOfTcpOooQElementType ChangedEleIdx )
{
  /* Do a total re-scan of all elements and link them by their age (change history). */

  /* #10 Identify the last changed element. */
  TcpIp_Tcp_VUpdateOooElementChangeOrder_IdentifyLastChangedElement(SocketTcpIdx, ChangedElementIdKnown, ChangedEleIdx);

  /* #20 Link all ooo elements sorted by their change time. */
  TcpIp_Tcp_VUpdateOooElementChangeOrder_LinkElements(SocketTcpIdx);
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VUpdateOooElementChangeOrder_IdentifyLastChangedElement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VUpdateOooElementChangeOrder_IdentifyLastChangedElement(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  boolean ChangedElementIdKnown,
  TcpIp_SizeOfTcpOooQElementType ChangedEleIdx)
{
  /* #10 Identify the last changed element. */
  if (ChangedElementIdKnown == FALSE)
  {
    /* #20 If the changed element id is unknown, then search for the last changed ooo element. */
    /* No element of the ooo list was changed, but the ooo element with the smallest sequence number is removed (the gap
       between this element and the already ACKed data was filled). */

    uint32                         newestEleChangeCounterValue;
    TcpIp_SizeOfTcpOooQElementType newestEleIdx;
    TcpIp_TcpOooQElementIterType   oooElementIteratorLoopCount;  /* simple iteration variable */
    TcpIp_SizeOfTcpOooQElementType currentOooElementIdx;  /* ooo element index when iterating (by sequence number)
                                                          through the socket's ooo elements */

    /* take the first ooo element and set it as newest element */
    newestEleIdx                = TcpIp_GetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx);
    newestEleChangeCounterValue = TcpIp_GetAddrTcpOooQElement(newestEleIdx)->ChangeCounterValue;

    /* go through the rest of the ooo array (by sequence), and search for the oldest element */
    currentOooElementIdx = TcpIp_GetAddrTcpOooQElement(newestEleIdx)->NextEleIdx;
    /* The first element is already handled, so the other (OooQFillNum - 1) elements have to be handled */
    for (oooElementIteratorLoopCount = 0;
         oooElementIteratorLoopCount < (TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx) - 1u);
         oooElementIteratorLoopCount++)
    {
      TCPIP_P2C(TcpIp_Tcp_RxPreBufEleType) currentOooElePtr = TcpIp_GetAddrTcpOooQElement(currentOooElementIdx);

      if (currentOooElePtr->ChangeCounterValue > newestEleChangeCounterValue)
      {
        /* newer element found */
        newestEleChangeCounterValue = currentOooElePtr->ChangeCounterValue;
        newestEleIdx = currentOooElementIdx;
      }
      currentOooElementIdx = currentOooElePtr->NextEleIdx;
    }

    /* mark newestEleIdx as OooQElementLastChanged */
    TcpIp_SetTcpOooQElementLastChangedIdxOfSocketTcpOooDyn(SocketTcpIdx, newestEleIdx);                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else
  {
    /* #30 If the changed element id is known, set it as the last changed element. */
    /* There are two scenarios where the changed element is known:
       - One ooo element has been extended: An existing ooo element is extended (prepended or appended new data). This
           can also be the (so far) oldest ooo element.
       - Two ooo elements have been merged: The gap between two ooo elements is filled (first element is extended,
           second element is deleted)
    */

    /* mark changed element as OooQElementLastChanged and set ChangeCounterValue */
    TcpIp_SetTcpOooQElementLastChangedIdxOfSocketTcpOooDyn(SocketTcpIdx, ChangedEleIdx);                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_IncTcpOooChangeCounterOfSocketTcpOooDyn(SocketTcpIdx);                                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_GetAddrTcpOooQElement(ChangedEleIdx)->ChangeCounterValue = TcpIp_GetTcpOooChangeCounterOfSocketTcpOooDyn(SocketTcpIdx);  /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
  }
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VUpdateOooElementChangeOrder_LinkElements
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VUpdateOooElementChangeOrder_LinkElements(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /* Link all ooo elements sorted by their change time. */

  TcpIp_SizeOfTcpOooQElementType       currentOldestAlignedElementIdx;  /* current oldest element that is already new
                                                                        aligned. Start value is the LastChangedIdx. */
  TCPIP_P2V(TcpIp_Tcp_RxPreBufEleType) currentOldestAlignedElementPtr;
  TcpIp_TcpOooQElementIterType         numRounds;  /* iteration variable for outer for-loop */

  /* #10 Update the time-wise links between the ooo elements. */
  currentOldestAlignedElementIdx = TcpIp_GetTcpOooQElementLastChangedIdxOfSocketTcpOooDyn(SocketTcpIdx);
  /* For 'FillNum' elements (FillNum - 1) links have to be set */
  for (numRounds = 0;
       numRounds < (TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx) - 1u);
       numRounds++)
  {
    uint32                         newestNotYetAlignedEleChangeCounterValue = 0;  /* change counter value of the newest
                                     not yet aligned element. Set to oldest possible value. */
    TcpIp_SizeOfTcpOooQElementType newestNotYetAlignedEleIdx = 0;  /* Idx of the newest not yet aligned element. Init to
                                     prevent warning. Idx is always updated in each for-loop (assured by the number of
                                     rounds in the for-loop). */
    TcpIp_TcpOooQElementIterType   oooElementIteratorLoopCount;  /* iteration variable for inner for-loop */
    TcpIp_SizeOfTcpOooQElementType currentOooElementIdx;  /* ooo element index when iterating (by sequence number)
                                     through the socket's ooo elements */

    currentOldestAlignedElementPtr = TcpIp_GetAddrTcpOooQElement(currentOldestAlignedElementIdx);

    /* #20 Go through ooo array (by sequence), and search for the newest element that is older than the last aligned element. */
    currentOooElementIdx = TcpIp_GetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx);
    for (oooElementIteratorLoopCount = 0; oooElementIteratorLoopCount < TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx); oooElementIteratorLoopCount++)
    {
      TCPIP_P2C(TcpIp_Tcp_RxPreBufEleType) currentOooElePtr = TcpIp_GetAddrTcpOooQElement(currentOooElementIdx);
      if ((currentOooElePtr->ChangeCounterValue > newestNotYetAlignedEleChangeCounterValue)
        && (currentOooElePtr->ChangeCounterValue < currentOldestAlignedElementPtr->ChangeCounterValue))
      {
        /* newer element found */
        newestNotYetAlignedEleChangeCounterValue = currentOooElePtr->ChangeCounterValue;
        newestNotYetAlignedEleIdx = currentOooElementIdx;
      }
      currentOooElementIdx = currentOooElePtr->NextEleIdx;
    }

    /* link oldest aligned element with the newest not yet aligned element */
    currentOldestAlignedElementPtr->OlderEleIdx = newestNotYetAlignedEleIdx;                                            /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
    /* update the value for the oldest aligned element Idx */
    currentOldestAlignedElementIdx = newestNotYetAlignedEleIdx;
  }
}
#endif  /* TCPIP_SUPPORT_TCP_SELECTIVE_ACK */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CopyDataToBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CopyDataToBuffer(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  uint16 writePos;  /* write position relative to the start of the socket's RxBuffer */
  TcpIp_SizeOfTcpRxBufferDescType tcpRxBufferDescIdx = TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx);

  TCPIP_ASSERT(tcpRxBufferDescIdx < TcpIp_GetSizeOfTcpRxBufferDesc());

  /* #10 Determine the write position inside the RxBuffer for the received data. */
  {
    TcpIp_TcpRxBufferIterType segmentOffsetInRxWindow;  /* position of the received segment inside the rx window */
    TcpIp_TcpRxBufferIterType rxBufferRemain;  /* related to the current RxWritePos: remaining buffer amount before buffer wraparound */

    segmentOffsetInRxWindow  = (TcpIp_TcpRxBufferIterType)SegmentDescriptorPtr->SegSeq
                     - (TcpIp_TcpRxBufferIterType)TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx);
    TCPIP_ASSERT(TcpIp_GetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(tcpRxBufferDescIdx) >= TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(tcpRxBufferDescIdx));

    rxBufferRemain = (TcpIp_TcpRxBufferIterType)TcpIp_GetTcpRxBufferEndIdxOfTcpRxBufferDesc(tcpRxBufferDescIdx)
                     - (TcpIp_TcpRxBufferIterType)TcpIp_GetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(tcpRxBufferDescIdx);


    /* increase buffer position, taking care of the wraparound */
    if (segmentOffsetInRxWindow < rxBufferRemain)
    {
      writePos = (uint16)(  (TcpIp_GetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(tcpRxBufferDescIdx)
                             - TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(tcpRxBufferDescIdx))
                          + segmentOffsetInRxWindow);
    }
    else
    {
      writePos = (uint16)(segmentOffsetInRxWindow - rxBufferRemain);
    }

    TCPIP_ASSERT(writePos < TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(tcpRxBufferDescIdx));
  }

  /* #20 Check if wraparound is needed in the RxBuffer. */
  if ((TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(tcpRxBufferDescIdx) - SegmentDescriptorPtr->SegLen) < writePos)
  {
    /* #30 Copy data with taking care of buffer wraparound (two blocks). */
    uint8 *locBufPtr;
    uint16 copyLenByte;

    /* copy first part: bytes 0..((TCPIP_TCP_MAX_WINDOW_SIZE - writePos) - 1) */
    locBufPtr = TcpIp_GetAddrTcpRxBuffer(
      TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(tcpRxBufferDescIdx) + writePos);
    copyLenByte = (uint16)(TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(tcpRxBufferDescIdx) - writePos);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpBase_Copy(locBufPtr, SegmentDescriptorPtr->PayloadPtr, copyLenByte);                                              /* SBSW_TCPIP_CopyDataToRxBuffer */

    /* copy second part: bytes (TCPIP_TCP_MAX_WINDOW_SIZE - writePos)..(SegmentDescriptorPtr->SegLen - 1) */
    locBufPtr = TcpIp_GetAddrTcpRxBuffer( TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(tcpRxBufferDescIdx));
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpBase_Copy(locBufPtr, &(SegmentDescriptorPtr->PayloadPtr)[copyLenByte],                                            /* SBSW_TCPIP_CopyDataToRxBuffer */
       ((uint32) SegmentDescriptorPtr->SegLen - (uint32) copyLenByte));
  }
  else
  {
    /* #40 Copy data (one block). */
    uint8 *locBufPtr;
    /* copy bytes 0..(SegmentDescriptorPtr->SegLen - 1) */
    locBufPtr = TcpIp_GetAddrTcpRxBuffer(
      TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(tcpRxBufferDescIdx) + writePos);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpBase_Copy(locBufPtr, SegmentDescriptorPtr->PayloadPtr, SegmentDescriptorPtr->SegLen);                             /* SBSW_TCPIP_CopyDataToRxBuffer */
  }

  /* trigger sending of ACK (eventually including SACK) */
  TcpIp_Tcp_VSendFlags(SocketTcpIdx, TCPIP_TCP_CODE_BIT_ACK);

}  /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif  /* (TCPIP_SUPPORT_TCP_RX_OOO == STD_ON) */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_Eighth
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_Eighth(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  /* RFC: eigth check the FIN bit */

  /*
  States:
  TCPIP_TCP_SOCK_STATE_SYNRCVD
  TCPIP_TCP_SOCK_STATE_ESTABLISHED
  TCPIP_TCP_SOCK_STATE_CLOSEWAIT
  TCPIP_TCP_SOCK_STATE_LASTACK
  TCPIP_TCP_SOCK_STATE_FINWAIT1
  TCPIP_TCP_SOCK_STATE_FINWAIT2
  TCPIP_TCP_SOCK_STATE_CLOSING
  TCPIP_TCP_SOCK_STATE_TIMEWAIT
  */

  /* #10 Check if the FIN flag is set in the received segment. */
  if ((TCPIP_TCP_CODE_BIT_FIN & SegmentDescriptorPtr->CodeBits) != 0u)
  {
    /* cancel all send and receive calls
    -> nothing to be done for AUTOSAR API */

    /* #20 Update the receive window and acknowledge the FIN. */
    /* RCV.NXT = FIN + 1 */
    TcpIp_SetRcvNxtOfSocketTcpDyn(SocketTcpIdx, (SegmentDescriptorPtr->SegSeq + SegmentDescriptorPtr->SegLen + 1u));     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

    /* send ACK */
    TcpIp_Tcp_VSendFlags(SocketTcpIdx, TCPIP_TCP_CODE_BIT_ACK);

    /* #30 Proceed the FIN dependent on the current connection state. */
    switch (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx))
    {
    /* State TCPIP_TCP_SOCK_STATE_SYNRCVD is already updated to state TCPIP_TCP_SOCK_STATE_ESTABLISHED when the
       sequence number is evaluated in TcpIp_Tcp_VRxIndicationStateOthers_Fifth_SynRcvd. */
    case TCPIP_TCP_SOCK_STATE_ESTABLISHED:
      {
        /* Switch to state CLOSEWAIT and signal 'FIN received' to the upper layer */
        TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_SynrcvdEstablished(SocketTcpIdx);
        break;
      }
    case TCPIP_TCP_SOCK_STATE_FINWAIT1:
      {
        /* Proceed to next connection state */
        TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_Finwait1(SocketTcpIdx);                                     /* SBSW_TCPIP_FC_PASSING_API_POINTER */
        break;
      }
    case TCPIP_TCP_SOCK_STATE_FINWAIT2:
      {
        /* Switch connection state to TimeWait and eventually signal the event to the upper layer */
        TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_Finwait2(SocketTcpIdx);
        break;
      }
    case TCPIP_TCP_SOCK_STATE_TIMEWAIT:
      {
        /* remain in current state */

        /* restart time-wait timer (MSL) */
        TcpIp_SetMslTimeoutOfSocketTcpDyn(SocketTcpIdx, (2u * (uint32) TcpIp_GetMslOfTcpConfig(TCPIP_TCPCONFIG_IDX)));  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        break;
      }
    default:
      {
        /* TCPIP_TCP_SOCK_STATE_CLOSEWAIT,
           TCPIP_TCP_SOCK_STATE_CLOSING,
           TCPIP_TCP_SOCK_STATE_LASTACK:
           -> remain in current state */
        break;
      }
    }  /* end of switch */
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_SynrcvdEstablished
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_SynrcvdEstablished(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /*
  States:
  TCPIP_TCP_SOCK_STATE_SYNRCVD
  TCPIP_TCP_SOCK_STATE_ESTABLISHED
  */

  /* #10 Switch to state CLOSEWAIT. */
  TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_CLOSEWAIT);                                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_CLOSEWAIT);                                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
  TcpIp_Tcp_VKeepAliveTrigger(SocketTcpIdx);
#endif

  /* #20 Forward the closing event to the socket owner or store it for later forwarding. */
  TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_ProcessOrStoreFin(SocketTcpIdx, TCPIP_TCP_STATE_FIN_REC);
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_Finwait1
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_Finwait1(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /*
  States:
  TCPIP_TCP_SOCK_STATE_FINWAIT1
  */
  /* #10 Switch to state CLOSING. */
  TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_CLOSING);                                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_CLOSING); /* only for sending ACK */          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* #20 Forward the closing event to the socket owner or store it for later forwarding. */
  TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_ProcessOrStoreFin( SocketTcpIdx, TCPIP_TCP_STATE_CONN_CLOSING);
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_Finwait2
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_Finwait2(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /*
  States:
  TCPIP_TCP_SOCK_STATE_FINWAIT2
  */

  /* #10 Switch to state TCPIP_TCP_SOCK_STATE_TIMEWAIT */
  TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_TIMEWAIT);                                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_TIMEWAIT); /* only for sending ACK */         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* #20 Start time-wait timer (MSL), and turn off the other timers */
  TcpIp_SetMslTimeoutOfSocketTcpDyn(SocketTcpIdx, (2u * (uint32) TcpIp_GetMslOfTcpConfig(TCPIP_TCPCONFIG_IDX)));        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
  TcpIp_Tcp_VKeepAliveTrigger(SocketTcpIdx);
#endif

  /* #30 Close the FINWAIT-2 timeout as FIN has been received */
  TcpIp_SetFinWait2TimeoutOfSocketTcpDyn(SocketTcpIdx, 0u);                                                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* #40 Forward the closing event to the socket owner or store it for later forwarding. */
  TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_ProcessOrStoreFin( SocketTcpIdx, TCPIP_TCP_STATE_CONN_CLOSING);
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_ProcessOrStoreFin
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_ProcessOrStoreFin(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TcpIp_StateType State)
{
  TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  /* #10 Forward the closing event to the socket owner or store it for later forwarding, depending on remaining
  indication length. */
  if (TcpIp_GetRxBufferRemIndLenOfSocketTcpDyn(SocketTcpIdx) == 0u)
  {
    /* signal new socket state to the user */
    TcpIp_SizeOfSocketOwnerConfigType socketOwnerConfigIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(socketIdx);

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
    TcpIp_VSockTcpStateChg(socketIdx, socketOwnerConfigIdx, State, TcpIp_IsUseTlsOfSocketTcpDyn(SocketTcpIdx));
#else
    TcpIp_VSockTcpStateChg(socketIdx, socketOwnerConfigIdx, State, FALSE);
#endif
  }
  else
  {
    /* store event for later forwarding to the user */
    TcpIp_SetEventIndicationPendingOfSocketTcpDyn(SocketTcpIdx, IPBASE_TCP_EVENT_FIN_RECEIVED);                         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_Received
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_Received(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  uint16                     DataLenByte)
{
  TcpIp_SizeOfTcpRxBufferType locDataLen;

  TCPIP_ASSERT(TCPIP_COND_INIT);
  TCPIP_ASSERT(TCPIP_TCP_COND_VALID_TCPIDX(SocketTcpIdx));

  /* #10 Check that the function is only called for sockets with assigned buffer. */
  if (TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx) >= TcpIp_GetSizeOfTcpRxBufferDesc())
  {
    /* This function should not be called for connections where no buffer is assigned */
    /* nothing to do, just return */
    TCPIP_ASSERT(TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx) == TcpIp_GetSizeOfTcpRxBufferDesc());
  }
  else
  {
    TcpIp_SizeOfTcpRxBufferDescType tcpRxBufferDescIdx;
    TCPIP_VENTER_CRITICAL_SECTION();

    tcpRxBufferDescIdx = TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx);

    TCPIP_ASSERT(tcpRxBufferDescIdx < TcpIp_GetSizeOfTcpRxBufferDesc());

    /* #20 Check if more data than available shall be released. */
    if (DataLenByte <= TcpIp_GetFillLevelOfTcpRxBufferDescDyn(tcpRxBufferDescIdx))
    {
      locDataLen = DataLenByte;
    }
    else
    {
      /* error, appl confirms more data than it has received */
      locDataLen = TcpIp_GetFillLevelOfTcpRxBufferDescDyn(tcpRxBufferDescIdx);
    }

    /* #30 Reduce fill level, adapt receive window and trigger sending a window update. */
    TcpIp_SubFillLevelOfTcpRxBufferDescDyn(tcpRxBufferDescIdx, locDataLen);                                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetRcvWndOfSocketTcpDyn(SocketTcpIdx, (uint16)(TcpIp_GetRcvWndOfSocketTcpDyn(SocketTcpIdx) + locDataLen));    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_Tcp_VSendFlags(SocketTcpIdx, TCPIP_TCP_CODE_BIT_ACK);

    TCPIP_VLEAVE_CRITICAL_SECTION();
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_CbkPathMtuChg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_CbkPathMtuChg(
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockAddrPtr,
  uint16 PathMtuSize)
{

  TcpIp_SizeOfSocketTcpDynType socketTcpIdx;

  TCPIP_VENTER_CRITICAL_SECTION();

  /* #10 Go through all TCP connections an check if they use the given comunication partner address. If the address is
  used, the PathMtu value has to be adjusted, and queued send elements have to be resized if they are too big. */

  /* go through all TCP connections */
  for (socketTcpIdx = 0; socketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn(); socketTcpIdx++)
  {
    TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(socketTcpIdx);
    /* list of some checks: */
    if (/* check if socket is in an active state */
           (TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) >  TCPIP_TCP_SOCK_STATE_LISTEN)                              /* PRQA S 3415 4 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
        && (TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) != TCPIP_TCP_SOCK_STATE_CLOSED)
        /* compare IP address */
        && (TcpIp_VSockIpAddrIsEqual(TcpIp_GetAddrRemSockOfSocketDyn(socketIdx), SockAddrPtr) == TRUE))                 /* SBSW_TCPIP_FC_RemoteAddressAvailable */
    {
      uint16 socketMtuCurrent;  /* Current MTU (IP layer) for the current socket */

      socketMtuCurrent = TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(socketTcpIdx)
                         + TCPIP_TCP_HDR_LEN_BYTE + TcpIp_GetTxOptLenOfSocketTcpDyn(socketTcpIdx);

      /* #20 Set marker to change the path mtu in the MainFunction */
      if (PathMtuSize != socketMtuCurrent)
      {
        TcpIp_SetPathMtuNewSizeOfSocketTcpDyn(socketTcpIdx, PathMtuSize);                                               /* SBSW_TCPIP_AWA_CslIteration_Local */
        TcpIp_SetPathMtuChangedOfSocketTcpDyn(socketTcpIdx, TRUE);                                                      /* SBSW_TCPIP_AWA_CslIteration_Local */
      }
    }  /* check if socket is in an active state */
  }  /* for each TCP socket */

  TCPIP_VLEAVE_CRITICAL_SECTION();

}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainPathMtuChg
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainPathMtuChg(
  TcpIp_SocketTcpDynIterType SocketTcpIdx)
{
  TCPIP_VENTER_CRITICAL_SECTION();

  /* #10 Check if the PathMtu has changed for this socket. */

  if (TcpIp_IsPathMtuChangedOfSocketTcpDyn(SocketTcpIdx) == TRUE)
  {
    uint16 pathMtuSize = TcpIp_GetPathMtuNewSizeOfSocketTcpDyn(SocketTcpIdx);

    /* #20 Check if requested new MTU size is not smaller than the allowed minimum. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
    TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);
    if ((TcpIp_GetAddrLocSockOfSocketDyn(socketIdx))->sa_family == IPBASE_AF_INET)
# endif
    {
      /* min size is 68 - IP-Header size */
      if (pathMtuSize < TCPIP_TCP_IPV4_MIN_PATH_MTU)
      {
        /* if MTU is smaller than allowed, set to min value */
        pathMtuSize = TCPIP_TCP_IPV4_MIN_PATH_MTU;
      }
    }
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
    else
# endif
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
    {
      /* IPBASE_AF_INET6 */
      if (pathMtuSize < TCPIP_TCP_IPV6_MIN_PATH_MTU)
      {
        /* if MTU is smaller than allowed, set to min value */
        pathMtuSize = TCPIP_TCP_IPV6_MIN_PATH_MTU;
      }
    }
#endif

    /* PathMTU is now at least 100 byte for IPv4 and at least 1240 byte for IPv6, so IP and TCP header and some data
       should always fit into a segment. */

    {
      uint16 newMaxSegSize;
      newMaxSegSize = (uint16)(pathMtuSize - TCPIP_TCP_HDR_LEN_BYTE - TcpIp_GetTxOptLenOfSocketTcpDyn(SocketTcpIdx));

      /* list of some checks: */
      if ( /* check if socket is in an active state */
             (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) >  TCPIP_TCP_SOCK_STATE_LISTEN)                            /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
          && (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) != TCPIP_TCP_SOCK_STATE_CLOSED))
      {
        /* socket is in a relevant state, so eventually the segment size has to be adapted */


        /* #30 Check if the new maximum segment size is smaller than the currently used one */
        if (newMaxSegSize < TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx))
        {
          /* #40 The new maximum segment size is smaller than the currently used one, so resize the queue elements. */

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
          /* #50 Adapt the CWND if necessary since the new PathMtu is smaller than the old one. */
          /* -> cwnd is reduced by the ratio of old and new PathMTU. Take care of integer algorithmic !! */
          TcpIp_SetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx,                                                             /* SBSW_TCPIP_AWA_CslIteration_Local */
            ((TcpIp_GetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx) * newMaxSegSize) / TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx)));
#endif

          /* #60 Resize the elements in TxRetrQueue. */
          /* set new maximum segment size */
          TcpIp_SetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx, newMaxSegSize);                                          /* SBSW_TCPIP_AWA_CslIteration_Local */
          /* Drop all elements of the RetryQ */
          TcpIp_Tcp_VDropEndEleInRetrQueue(SocketTcpIdx, TcpIp_GetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx));
          /* The RetryQ will be filled again in the subsequently called funtion TcpIp_Tcp_VMainTxDataHandling() using
          TcpIp_Tcp_VQueueRemReqData(). */
        }
        /* #70 Otherwise: New maximum segment size is bigger than the currently used one. */
        else
        {
          TCPIP_ASSERT(newMaxSegSize > TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx));

          if (newMaxSegSize > TcpIp_GetTxMssAgreedOfSocketTcpDyn(SocketTcpIdx))
          {
            TcpIp_SetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetTxMssAgreedOfSocketTcpDyn(SocketTcpIdx));     /* SBSW_TCPIP_AWA_CslIteration_Local */
          }
          else
          {
            TcpIp_SetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx, newMaxSegSize);                                        /* SBSW_TCPIP_AWA_CslIteration_Local */
          }

          /* If possible, the RetryQ will be filled with further data in the subsequently called funtion
          TcpIp_Tcp_VMainTxDataHandling() using TcpIp_Tcp_VQueueRemReqData(). */
        }
      }
    }

    TcpIp_SetPathMtuChangedOfSocketTcpDyn(SocketTcpIdx, FALSE);  /* reset the marker for a changed path MTU */          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }  /* if PathMtu has changed */

  TCPIP_VLEAVE_CRITICAL_SECTION();

}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_InitSock
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_InitSock(
  TcpIp_SocketTcpDynIterType SocketTcpIdx)
{
  /* #10 Init the socket */
  TcpIp_Tcp_VInitSock(SocketTcpIdx);
}


/**********************************************************************************************************************
*  TcpIp_Tcp_VCopyTxDataIndirect()
*********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
*/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VCopyTxDataIndirect(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8)             DstChunk1Ptr,
  uint16                       DstChunk1Len,
  TCPIP_P2V(uint8)             DstChunk2Ptr,
  TCPIP_P2V(uint32)            LengthPtr)
{
  Std_ReturnType            retVal       = E_NOT_OK;
  uint16                    copyLen      = DstChunk1Len;
  uint16                    dstChunk2Len = (uint16)(*LengthPtr - DstChunk1Len);
  TcpIp_SizeOfSocketDynType socketIdx    = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  TCPIP_ASSERT(SocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn());

  /* #10 Copy first chunk of data at the end of buffer. */
  if (TcpIp_CopyTxDataFunctions(socketIdx, DstChunk1Ptr, &copyLen) == BUFREQ_OK)                                        /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_OutParamLocalVarRef */
  {
    /* #20 Update *LengthPtr if user provided less data. */
    if (copyLen < DstChunk1Len)
    {
      /* user provided less data than requested.
      -> data provision complete. */
      *LengthPtr = copyLen;                                                                                             /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
      retVal = E_OK;
    }
    /* #30 Copy second chunk at the beginning of buffer, if required. */
    else if (dstChunk2Len > 0u)
    {
      copyLen = dstChunk2Len;

      if (TcpIp_CopyTxDataFunctions(socketIdx, DstChunk2Ptr, &copyLen) == BUFREQ_OK)                                    /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_OutParamLocalVarRef */
      {
        /* #40 Update *LengthPtr if user provided less data. */
        if (copyLen < dstChunk2Len)
        {
          /* user provided less data than requested. */
          *LengthPtr -= ((uint32)dstChunk2Len - (uint32)copyLen);                                                       /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
        }
        /* else: Length bytes of data were provided. */

        retVal = E_OK;
      }
      /* else: user aboted transmit */
    }
    else
    {
      /* all data was provided in a single chunk. */
      retVal = E_OK;
    }
  }
  /* else: user aborted transmit */

  return retVal;
}  /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
*  TcpIp_Tcp_VCopyDataFromTcpUser()
*********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
*/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VCopyDataFromTcpUser(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(uint8)             DataPtr,
  TCPIP_P2V(uint32)            LengthPtr)
{
  Std_ReturnType                  retVal;
  TcpIp_SizeOfTcpTxBufferDescType tcpTxBufferDescIdx   = TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx);
  TcpIp_SizeOfTcpTxBufferType     remainingLengthAtEnd = TcpIp_GetTcpTxBufferEndIdxOfTcpTxBufferDesc(tcpTxBufferDescIdx) - TcpIp_GetTcpTxBufferWriteIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx);

  TCPIP_P2V(uint8) chunk1Ptr = TcpIp_GetAddrTcpTxBuffer(TcpIp_GetTcpTxBufferWriteIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx));
  TCPIP_P2V(uint8) chunk2Ptr;
  uint16 chunk1Len;

  /* #10 Calculate size of data chunks that need to be copied. */
  if (*LengthPtr <= remainingLengthAtEnd)
  {
    /* All data fits into the ring buffer without wrap-around. Only one chunk required. */
    chunk1Len = (uint16)*LengthPtr;
    chunk2Ptr = NULL_PTR;
  }
  else
  {
    /* Data does not fit into one linear buffer segment. Copy two chunks. */
    chunk1Len = (uint16)remainingLengthAtEnd;
    chunk2Ptr = TcpIp_GetAddrTcpTxBuffer(TcpIp_GetTcpTxBufferStartIdxOfTcpTxBufferDesc(tcpTxBufferDescIdx));
  }

  /* #20 Copy data chunks from user (directly or indirectly via CopyTxData) */
  if (DataPtr != NULL_PTR)
  {
    uint16 chunk2Len = (uint16)(*LengthPtr - chunk1Len);

    TCPIP_ASSERT(chunk1Len > 0u);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpBase_Copy(chunk1Ptr, DataPtr, chunk1Len);                                                                         /* SBSW_TCPIP_FC_CopyDataFromTcpSocketOwner */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */

    if (chunk2Len > 0u)
    {
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpBase_Copy(chunk2Ptr, &DataPtr[chunk1Len], chunk2Len);                                                           /* SBSW_TCPIP_FC_CopyDataFromTcpSocketOwner */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    }

    retVal = E_OK;
  }
  else
  {
    retVal = TcpIp_Tcp_VCopyTxDataIndirect(SocketTcpIdx, chunk1Ptr, chunk1Len, chunk2Ptr, LengthPtr);                   /* SBSW_TCPIP_FC_CopyDataFromTcpSocketOwner */ /* SBSW_TCPIP_FC_OutParamLocalVarRef */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }

  return retVal;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
*  TcpIp_TcpTransmitInternal()
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpTransmitInternal(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TCPIP_P2C(uint8)          DataPtr,
  uint32                    Length,
  boolean                   ForceRetrieve)
{
  uint32                       localLength = Length;
  Std_ReturnType               retVal = E_NOT_OK;
  TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);

  /* This implementation only accepts a transmit request if the whole data indicated by 'AvailableLength' can be stored into the TCP tx buffer.
  * Therefore the value of 'ForceRetrieve' == FALSE is ignored.
  */
  TCPIP_UNUSED_PARAMETER(ForceRetrieve);  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  TCPIP_ASSERT(TCPIP_SOCKET_IDX_IS_TCP(SocketIdx));

  /* #10 Check if the socket is in valid state for transmitting data. */
  if (   (TcpIp_GetListenActiveConnStatOfSocketDyn(SocketIdx) != TCPIP_SOCK_CONN_NONE)                                  /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (   (TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) == TCPIP_TCP_SOCK_STATE_ESTABLISHED)
          || (TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) == TCPIP_TCP_SOCK_STATE_CLOSEWAIT)))
  {
#ifdef COMMENT_VECTOR  /* ESCAN00104482 - next check, impl version 13.00.02 */
#endif
    /* #20 Varify if maximum segment size is bigger than Zero. */
    if (TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(socketTcpIdx) > 0u)
    {
      TcpIp_SizeOfTcpTxBufferDescType tcpTxBufferDescIdx = TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(socketTcpIdx);
      TcpIp_SizeOfTcpTxBufferType     tcpTxBufferSize;

      TCPIP_ASSERT(tcpTxBufferDescIdx < TcpIp_GetSizeOfTcpTxBufferDesc());

      tcpTxBufferSize = TcpIp_GetTcpTxBufferLengthOfTcpTxBufferDesc(tcpTxBufferDescIdx);

      TCPIP_ASSERT(tcpTxBufferSize >= TcpIp_GetFillLevelOfTcpTxBufferDescDyn(tcpTxBufferDescIdx));

      /* #30 Check that the desired amount of data fits into the remaining space in the ring buffer. */
      if (localLength <= (uint32)(tcpTxBufferSize - TcpIp_GetFillLevelOfTcpTxBufferDescDyn(tcpTxBufferDescIdx)))
      {
        TCPIP_ASSERT(tcpTxBufferSize >= localLength);

        /* #40 Store buffer position where the untransmitted data starts, if there is currently no data pending. */
        if (TcpIp_GetTxReqDataLenByteOfSocketTcpDyn(socketTcpIdx) == 0u)
        {
          TcpIp_SetTxReqDataBufStartIdxOfSocketTcpDyn(socketTcpIdx, TcpIp_GetTcpTxBufferWriteIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        }

        /* #50 Copy data from user. */
        /* If indirect data provision is used the user may provide less than 'Length' bytes.
         * In this case 'Length' is updated and only the provided number of bytes will be transmitted. */
        if (TcpIp_Tcp_VCopyDataFromTcpUser(socketTcpIdx, DataPtr, &localLength) == E_OK)                                /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_ReferencingFunctionParameter */
        {
          TcpIp_SizeOfTcpTxBufferType newTxBufferWriteIdx;
          TCPIP_VENTER_CRITICAL_SECTION();

          /* #60 Update the TX-buffer admin data and indicate that the request has been accepted. */
          newTxBufferWriteIdx = TcpIp_IncTxBufIdx(tcpTxBufferDescIdx,
            TcpIp_GetTcpTxBufferWriteIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx),
            (TcpIp_SizeOfTcpTxBufferType)localLength);

          TcpIp_SetTcpTxBufferWriteIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx, newTxBufferWriteIdx);                    /* SBSW_TCPIP_AWA_CSL_Valid_BufferIdx_local */

          TcpIp_AddFillLevelOfTcpTxBufferDescDyn(tcpTxBufferDescIdx, (TcpIp_SizeOfTcpTxBufferType)localLength);         /* SBSW_TCPIP_AWA_CSL_Valid_BufferIdx_local */

          TcpIp_SetTxReqDataLenByteOfSocketTcpDyn(socketTcpIdx, (TcpIp_GetTxReqDataLenByteOfSocketTcpDyn(socketTcpIdx) + (TcpIp_SizeOfTcpTxBufferType)localLength)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
          /* TxReqQueuedLen is not changed. If the retry-element already contained data then there already is a valid length, otherwise the length should already be '0' */
          TcpIp_SetTxReqFullyQueuedOfSocketTcpDyn(socketTcpIdx, FALSE);                                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
          TcpIp_SetTxTotNotQueuedLenOfSocketTcpDyn(socketTcpIdx, (TcpIp_GetTxTotNotQueuedLenOfSocketTcpDyn(socketTcpIdx) + (TcpIp_SizeOfTcpTxBufferType)localLength)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

          TCPIP_VLEAVE_CRITICAL_SECTION();

          retVal = E_OK;
        }
      }
      else
      {
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
        /* Increment the measurement data counter for dropped TCP message (due to insufficient Tx buffer) */
        TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_TX_BUFFER);
#endif

      }

    }
    /* #70 Otherwise, do not transmit, because MSS is Zero. */
    else
    {
      /* Trasmit is not possible, because MSS = 0 */
    }
  }
  return retVal;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_TcpTransmitTls()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpTransmitTls(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TCPIP_P2C(uint8)          DataPtr,
  uint32                    Length)
{
  uint32                        localLength = Length;
  Std_ReturnType                retVal;
  TCPIP_P2V(Tls_PbufType)       pbufPtr;
  TcpIp_SizeOfSocketTcpDynType  socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);

  TCPIP_ASSERT(TCPIP_SOCKET_IDX_IS_TCP(SocketIdx));
  TCPIP_ASSERT(TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx));

  /* #10 Request a TxBuffer from TLS. */
  /* In case of success Tls will always return a pbuf struct referncing a single linear buffer. */
  retVal = (Std_ReturnType) Tls_ProvideTxBuffer(SocketIdx, &pbufPtr, localLength);                                                            /* SBSW_TCPIP_FC_OutParamLocalVarRef */

  if (retVal == E_OK)
  {
    /* #20 Copy the data into the TLS buffer. */
    if (DataPtr != NULL_PTR)
    {
      /* Copy the data to the buffer (Pbuf) provided by Tls. */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      (void)IpBase_CopyString2PbufAt(DataPtr, (uint16)localLength, pbufPtr, 0u);                                              /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_ForwardTlsPbufRef */
      /* Return value of IpBase_CopyString2PbufAt() is ignored because return value is always E_OK. */
    }
    else
    {
      /* Call the socket owner to copy the data into the buffer */
      /* As the provided pbuf contains only one element, pbuf len and totalLen have the same value and there is no
         second buffer element. Therefore the second buffer pointer for the copy function is NULL. */
      retVal = TcpIp_Tcp_VCopyTxDataIndirect(socketTcpIdx, pbufPtr->payload, pbufPtr->len, NULL_PTR, &localLength);          /* SBSW_TCPIP_FC_ForwardTlsPbufRef */ /* SBSW_TCPIP_FC_NULL_PTR_SECOND_DATA_ELEMENT */ /* SBSW_TCPIP_FC_ReferencingFunctionParameter */
    }

    pbufPtr->totLen = localLength;

    /* #30 Trigger the TLS to send the data or release the buffer. */
    if (retVal == E_OK)
    {
      retVal = Tls_TransmitTo(SocketIdx, pbufPtr);                                                                      /* SBSW_TCPIP_FC_ForwardTlsPbufRef */
    }
    else
    {
      /* release the TLS buffer because copying the data failed */
      pbufPtr->totLen = 0;
      (void)Tls_TransmitTo(SocketIdx, pbufPtr);                                                                         /* SBSW_TCPIP_FC_ForwardTlsPbufRef */
    }
  }

  return retVal;
}
#endif


/**********************************************************************************************************************
 *  TcpIp_Tcp_GetSockIsConnected
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_Tcp_GetSockIsConnected(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  boolean socketIsConnected;

  TCPIP_ASSERT(TCPIP_COND_INIT);
  TCPIP_ASSERT(TCPIP_TCP_COND_VALID_TCPIDX(SocketTcpIdx));

  /* #10 Check if the socket is connected */
  if (   (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) >= TCPIP_TCP_SOCK_STATE_ESTABLISHED)                           /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) <  TCPIP_TCP_SOCK_STATE_CLOSED))
  {
    socketIsConnected = TRUE;
  }
  else
  {
    socketIsConnected = FALSE;
  }

  return socketIsConnected;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_MainFunctionRx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_MainFunctionRx(void)
{
  TcpIp_SizeOfSocketTcpDynType socketTcpIdx;

  /* #10 Iterate over all TCP sockets. */
  for (socketTcpIdx = 0; socketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn(); socketTcpIdx++)
  {
    if (TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) != TCPIP_TCP_SOCK_STATE_CLOSED)
    {
      /* #20 Remove ACKed segments from the retry queue. */
      uint16 tmpRemIndLen = (uint16)TcpIp_GetRxBufferRemIndLenOfSocketTcpDyn(socketTcpIdx);

      TcpIp_Tcp_VFreeAckedReqAndRetrElements(socketTcpIdx, TcpIp_GetSndUnaOfSocketTcpDyn(socketTcpIdx));

      /* #30 Forward newly received data to upper layer. */
      if (tmpRemIndLen > 0u)
      {
        TcpIp_Tcp_VMainRxDataForwarding(socketTcpIdx, tmpRemIndLen);
      }
    }
  }
}  /* TcpIp_Tcp_MainFunctionRx() */

/**********************************************************************************************************************
 *  TcpIp_Tcp_MainFunctionTx
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
FUNC(void, TCPIP_CODE) TcpIp_Tcp_MainFunctionTx(void)
{
  TcpIp_SocketTcpDynIterType socketTcpIdx;

  /* #10 Transmit pending resets. */

  if (TcpIp_Tcp_RstTxQueueFillNum > 0u)
  {
    TCPIP_VENTER_CRITICAL_SECTION();
    TcpIp_Tcp_VTransmitResets();  /* transmit resets from reset-queue */
    TCPIP_VLEAVE_CRITICAL_SECTION();
  }

  /* #20 Iterate over all TCP sockets. */

  for (socketTcpIdx = 0; socketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn(); socketTcpIdx++)
  {
    if (TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) != TCPIP_TCP_SOCK_STATE_CLOSED)
    {
      TCPIP_VENTER_CRITICAL_SECTION();

      /* #30 Adapt path MTU size if it was triggered before. */
      TcpIp_Tcp_VMainPathMtuChg(socketTcpIdx);

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
      /* #40 Increase CWND based on received ACKs during one round trip time. */
      if (TcpIp_GetCongestionControlModeOfSocketTcpCongCtrlDyn(socketTcpIdx) == TCPIP_TCP_CONG_CTRL_MODE_CONGESTION_AVOIDANCE)
      {
        /* If ACKs have to be summarized during one RTT, the timeout is handled here. */
        if (TcpIp_GetAckSumTimeoutOfSocketTcpCongCtrlDyn(socketTcpIdx) > 0u)
        {
          TcpIp_DecAckSumTimeoutOfSocketTcpCongCtrlDyn(socketTcpIdx);                                                     /* SBSW_TCPIP_AWA_CslIteration_Local */
          if (TcpIp_GetAckSumTimeoutOfSocketTcpCongCtrlDyn(socketTcpIdx) == 0u)
          {
            /* inc cwnd */
            CANOE_WRITE_STRING_2("TcpIp_Tcp_MainFunction: SocketTcpIdx %d: inc cwnd in congestion avoidance, AckSum is %d", SocketTcpIdx, TcpIp_GetAckSumNOfSocketTcpCongCtrlDyn(SocketTcpIdx));
            TcpIp_Tcp_VIncCwnd(socketTcpIdx, TcpIp_GetAckSumNOfSocketTcpCongCtrlDyn(socketTcpIdx));
          }
        }
      }
#endif  /* (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON) */

      /* #50 Send pending TX data. */
      TcpIp_Tcp_VMainTxDataHandling((TcpIp_SizeOfSocketTcpDynType)socketTcpIdx);
      TCPIP_VLEAVE_CRITICAL_SECTION();
    }
  }
}  /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/**********************************************************************************************************************
 *  TcpIp_Tcp_MainFunctionState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_MainFunctionState(void)
{
  TcpIp_SizeOfSocketTcpDynType socketTcpIdx;

  TcpIp_Tcp_GlobalTimestamp++;

  /* #10 Iterate over all TCP sockets. */

  for (socketTcpIdx = 0; socketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn(); socketTcpIdx++)
  {
    if (TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) != TCPIP_TCP_SOCK_STATE_CLOSED)
    {
      TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(socketTcpIdx);
      /* #20 Handle pending TCP socket state changes. */
      TcpIp_Tcp_VMainStateHandling(socketTcpIdx);

      /* #30 Notify upper layer about socket state changes. */
      if (TcpIp_GetEventIndicationPendingOfSocketTcpDyn(socketTcpIdx) != 0u)
      {
        /* In the current implementation only the event IPBASE_TCP_EVENT_FIN_RECEIVED can be pending, so no further
           differentiation for different events is necessary here. */
           /* In the current implementation there is only one single place in the function
              TcpIp_Tcp_VRxIndicationStateOthers_EighthProcessFin_ProcessOrStoreFin where a pending element FIN_RECEIVED is
              set. */
        TCPIP_ASSERT((TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) == TCPIP_TCP_SOCK_STATE_CLOSEWAIT)
          || (TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) == TCPIP_TCP_SOCK_STATE_TIMEWAIT));

        if (TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) == TCPIP_TCP_SOCK_STATE_CLOSEWAIT)
        {
          /* signal 'FIN received' to the user */
          TcpIp_SizeOfSocketOwnerConfigType socketOwnerConfigIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(socketIdx);

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
          TcpIp_VSockTcpStateChg(socketIdx, socketOwnerConfigIdx, TCPIP_TCP_STATE_FIN_REC, TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx));
#else
          TcpIp_VSockTcpStateChg(socketIdx, socketOwnerConfigIdx, TCPIP_TCP_STATE_FIN_REC, FALSE);
#endif
        }
        else  /* TCPIP_TCP_SOCK_STATE_TIMEWAIT */
        {
          /* signal 'connection closing' to the user */
          TcpIp_SizeOfSocketOwnerConfigType socketOwnerConfigIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(socketIdx);

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
          TcpIp_VSockTcpStateChg(socketIdx, socketOwnerConfigIdx, TCPIP_TCP_STATE_CONN_CLOSING, TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx));
#else
          TcpIp_VSockTcpStateChg(socketIdx, socketOwnerConfigIdx, TCPIP_TCP_STATE_CONN_CLOSING, FALSE);
#endif
        }
        /* all other possible values for SockState will not occurr here:

           TCPIP_TCP_SOCK_STATE_INVALID     -> this state is never used as SockState but only for SockStateNext

           TCPIP_TCP_SOCK_STATE_LISTEN,
           TCPIP_TCP_SOCK_STATE_SYNSENT,
           TCPIP_TCP_SOCK_STATE_LASTACK,
           TCPIP_TCP_SOCK_STATE_CLOSING,
           TCPIP_TCP_SOCK_STATE_CLOSED      -> in these states there is no path that could set a pending event

           TCPIP_TCP_SOCK_STATE_SYNRCVD,
           TCPIP_TCP_SOCK_STATE_ESTABLISHED -> these states are already enhanced to state TCPIP_TCP_SOCK_STATE_CLOSEWAIT
                                               in the context of the RxIndication.

           TCPIP_TCP_SOCK_STATE_FINWAIT1,
           TCPIP_TCP_SOCK_STATE_FINWAIT2    -> these states are already enhanced to state TCPIP_TCP_SOCK_STATE_TIMEWAIT
                                               in the context of the RxIndication.
        */

        TcpIp_SetEventIndicationPendingOfSocketTcpDyn(socketTcpIdx, 0);  /* delete the pending event */                   /* SBSW_TCPIP_AWA_CslIteration_Local */
      }

      /* #40 Handle TCP idle timeouts. */
      TcpIp_Tcp_VMainIdleTimeoutHandling(socketTcpIdx);
    }
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VDuplicateSocket
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
TCPIP_LOCAL FUNC(TcpIp_SizeOfSocketTcpDynType, TCPIP_CODE) TcpIp_Tcp_VDuplicateSocket(
  TcpIp_SizeOfSocketTcpDynType      ListenSocketTcpIdx,
  TcpIp_LocalAddrIterType           LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr)
{
  TcpIp_SizeOfSocketTcpDynType  newSocketTcpIdx = TCPIP_TCP_INV_IDX;
  TcpIp_SizeOfSocketDynType     listenSocketIdx;
  TcpIp_SocketTcpDynIterType    socketTcpIdx;
  TcpIp_SocketTcpDynIterType    derivedConnCnt = 0;  /* number of sockets that have already been derived from the listen socket */

  TCPIP_ASSERT(ListenSocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn());

  listenSocketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(ListenSocketTcpIdx);

  /* #10 Count TCP sockets that have the current listen socket as master. */
  for (socketTcpIdx = 0; socketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn(); socketTcpIdx++)
  {
    if (TcpIp_GetSocketTcpDynMasterListenSocketIdxOfSocketTcpDyn(socketTcpIdx) == ListenSocketTcpIdx)
    {
      derivedConnCnt++;
    }
  }

  /* #20 Check if the limit for listen sockets is already reached */
  if (derivedConnCnt < TcpIp_GetMaxNumListenSocketsOfSocketTcpDyn(ListenSocketTcpIdx))
  {
    /* The maximum number of sockets derived from the current listen socket is not yet reached */
    TcpIp_SocketIdType newSocketId;

    /* #30 Take a new TCP socket if available */
    if (TcpIp_GetSocketForUser(RxSockRemAddrPtr->DomainAndPort.domain, TCPIP_IPPROTO_TCP, &newSocketId, TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(listenSocketIdx)) == E_OK) /* SBSW_TCPIP_FC_OutParamLocalVarRef */
    {
      /* socket could be allocated */
      newSocketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(TCPIP_SOCKET_ID_TO_IDX(newSocketId));

      /* #40 Assign buffers and init/copy variables for the new derived socket */
      if (TcpIp_Tcp_VAssignBuffersToDuplicatedSocket(newSocketTcpIdx, ListenSocketTcpIdx) == E_OK)
      {
        TcpIp_SetSocketTcpDynMasterListenSocketIdxOfSocketTcpDyn(newSocketTcpIdx, ListenSocketTcpIdx);  /* set master socket index for this new socket */ /* SBSW_TCPIP_AWA_CSL_IDX_FROM_PREVIOUS_FUNCTION_CALL */

        TcpIp_Tcp_VInitVarsOfDuplicatedSocket(newSocketTcpIdx, ListenSocketTcpIdx, LocalAddrIdx, RxSockRemAddrPtr);     /* SBSW_TCPIP_FC_PASSING_API_POINTER */

        TcpIp_Tcp_VAcceptedSocketStateHandling(ListenSocketTcpIdx, newSocketTcpIdx);
      }
      else
      {
        /* #50 No matching buffer available -> release the new socket and cancel this attempt to accept a connection */
        (void)TcpIp_Close(newSocketId, FALSE);
        newSocketTcpIdx = TCPIP_TCP_INV_IDX;
      }
    }
    else
    {
      /* no free sockets available */
    }
  }
  else
  {
    /* no more connection may be accepted on this listen socket */
  }

  return newSocketTcpIdx;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VAssignBuffersToDuplicatedSocket
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VAssignBuffersToDuplicatedSocket(
  TcpIp_SizeOfSocketTcpDynType NewSocketTcpIdx,
  TcpIp_SizeOfSocketTcpDynType ListenSocketTcpIdx)
{
  Std_ReturnType retVal;

  /* #10 Assign an RxBuffer to the duplicated socket. */
  TCPIP_ASSERT(TcpIp_GetRequestedRxBufferSizeOfSocketTcpDyn(ListenSocketTcpIdx) > 0u);
  retVal = TcpIp_Tcp_VAssignRxBuffer(NewSocketTcpIdx, TcpIp_GetRequestedRxBufferSizeOfSocketTcpDyn(ListenSocketTcpIdx));

  /* #20 Assign a TxBuffer to the duplicated socket. */
  if (retVal == E_OK)
  {
    TCPIP_ASSERT(TcpIp_GetRequestedTxBufferSizeOfSocketTcpDyn(ListenSocketTcpIdx) > 0u);
    retVal = TcpIp_Tcp_VAssignTxBuffer(NewSocketTcpIdx, TcpIp_GetRequestedTxBufferSizeOfSocketTcpDyn(ListenSocketTcpIdx));
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VInitVarsOfDuplicatedSocket
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VInitVarsOfDuplicatedSocket(
  TcpIp_SizeOfSocketTcpDynType      NewSocketTcpIdx,
  TcpIp_SizeOfSocketTcpDynType      ListenSocketTcpIdx,
  TcpIp_LocalAddrIterType           LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr)
{
  TcpIp_SizeOfSocketDynType   newSocketIdx    = TCPIP_TCP_IDX_TO_SOCKET_IDX(NewSocketTcpIdx);
  TcpIp_SizeOfSocketDynType   listenSocketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(ListenSocketTcpIdx);

  /* Copy EthframePrio from Listen socket to new created socket. */
  TcpIp_VCopySocketSpecificFramePriority(newSocketIdx, listenSocketIdx);
  /* #10 Set rx- and tx-window related variables */
  TcpIp_SetRcvNxtOfSocketTcpDyn(NewSocketTcpIdx, TcpIp_GetRcvNxtOfSocketTcpDyn(ListenSocketTcpIdx));                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#if (TCPIP_SUPPORT_TCP_NAGLE_TIMEOUT == STD_ON)
  TCPIP_ASSERT(TcpIp_HasSocketTcpNagleDyn() == TRUE);
  TcpIp_SetEnabledOfSocketTcpNagleDyn(NewSocketTcpIdx, TcpIp_IsEnabledOfSocketTcpNagleDyn(ListenSocketTcpIdx));         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif

#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
  TcpIp_Tcp_VKeepAliveCopyParameters(ListenSocketTcpIdx, NewSocketTcpIdx);
#endif

  TcpIp_SetIssOfSocketTcpDyn(NewSocketTcpIdx, TcpIp_Tcp_GlobalTimestamp * (250u * TCPIP_MAIN_FCT_PERIOD_MSEC));  /* inc iss every 4 microseconds */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSndUnaOfSocketTcpDyn(NewSocketTcpIdx, TcpIp_GetIssOfSocketTcpDyn(NewSocketTcpIdx));  /* ISS */               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSndNxtOfSocketTcpDyn(NewSocketTcpIdx, TcpIp_GetIssOfSocketTcpDyn(NewSocketTcpIdx));  /* ISS */               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSndWl2OfSocketTcpDyn(NewSocketTcpIdx, TcpIp_GetIssOfSocketTcpDyn(NewSocketTcpIdx));  /* ISS */               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* #20 Set local family and port, other address related varibles and MSS. */
  TcpIp_GetAddrLocSockOfSocketDyn(newSocketIdx)->DomainAndPort.domain = RxSockRemAddrPtr->DomainAndPort.domain;         /* SBSW_TCPIP_PWA_SocketPointerDerivedFromValidSocketIdx */
  TcpIp_GetAddrLocSockOfSocketDyn(newSocketIdx)->DomainAndPort.port   = TcpIp_GetAddrLocSockOfSocketDyn(listenSocketIdx)->DomainAndPort.port; /* SBSW_TCPIP_PWA_SocketPointerDerivedFromValidSocketIdx */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
  if (TcpIp_GetAddrLocSockOfSocketDyn(newSocketIdx)->sa_family == IPBASE_AF_INET)
  {
    TcpIp_LocalAddrV4IterType  ipV4AddrIdx = TCPIP_LOCAL_ADDR_IDX_TO_IPV4(LocalAddrIdx);
    IpBase_AddrInType         *ipV4AddrPtr = &(TcpIp_GetAddrLocSockOfSocketDyn(newSocketIdx)->SockAddrIn.sin_addr);
    (void)IpV4_Ip_GetLocNetAddr(ipV4AddrIdx, ipV4AddrPtr);                                                              /* SBSW_TCPIP_FC_LocalAddressAvailable */
    TcpIp_SetTxMaxSegLenByteOfSocketTcpDyn(NewSocketTcpIdx, TCPIP_TCP_DEFAULT_TX_MSS_IPV4);                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  if (TcpIp_GetAddrLocSockOfSocketDyn(newSocketIdx)->sa_family == IPBASE_AF_INET6)
  {
    TcpIp_LocalAddrV6IterType  ipV6AddrIdx = TCPIP_LOCAL_ADDR_IDX_TO_IPV6(LocalAddrIdx);  /* PRQA S 2897 */ /* MD_TCPIP_2897 */
    IpBase_AddrIn6Type        *ipV6AddrPtr = &(TcpIp_GetAddrLocSockOfSocketDyn(newSocketIdx)->SockAddrIn6.sin6_addr);
    (void)IpV6_GetLocalAddress(ipV6AddrIdx, ipV6AddrPtr, NULL_PTR);                                                     /* SBSW_TCPIP_FC_LocalAddressAvailable */
    TcpIp_SetTxMaxSegLenByteOfSocketTcpDyn(NewSocketTcpIdx, TCPIP_TCP_DEFAULT_TX_MSS_IPV6);                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
#endif
  (void)IpBase_CopySockAddr(&TcpIp_GetAddrRemSockOfSocketDyn(newSocketIdx)->SockAddr, &RxSockRemAddrPtr->SockAddr);     /* SBSW_TCPIP_FC_RemoteAddressAvailable */

  TcpIp_SetSockIsServerOfSocketTcpDyn(NewSocketTcpIdx, TcpIp_IsSockIsServerOfSocketTcpDyn(ListenSocketTcpIdx));         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTxIpAddrIdxOfSocketDyn(newSocketIdx, (TcpIp_TxIpAddrIdxOfSocketDynType)TCPIP_LOCAL_ADDR_IDX_TO_IPVX(LocalAddrIdx)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetLocalAddrBindIdxOfSocketDyn(newSocketIdx, TcpIp_GetLocalAddrBindIdxOfSocketDyn(listenSocketIdx));            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* #30 Init TxMssAgreed with default value */
  /* The TCP header options are not yet evaluated for this received connection request, so default value is applied. */
  TcpIp_SetTxMssAgreedOfSocketTcpDyn(NewSocketTcpIdx, TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(NewSocketTcpIdx));         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
  /* #40 Set the default cwnd */
  TcpIp_SetCwndSegNumLimitOfSocketTcpCongCtrlDyn(NewSocketTcpIdx, TCPIP_TCP_DEFAULT_SEGMENT_LIMIT(TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(NewSocketTcpIdx))); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetCwndOfSocketTcpCongCtrlDyn(NewSocketTcpIdx,                                                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    ((uint32) TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(NewSocketTcpIdx) * (uint32) TcpIp_GetCwndSegNumLimitOfSocketTcpCongCtrlDyn(NewSocketTcpIdx)));
#endif

  /* #50 Set values for activated options. */
#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
  TcpIp_SetSackOptActiveOfSocketTcpDyn(NewSocketTcpIdx, FALSE);                                                         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif

#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
  TcpIp_SetTimestampOptActiveOfSocketTcpTsOptDyn(NewSocketTcpIdx, FALSE);                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTimestampReceivedOfSocketTcpTsOptDyn(NewSocketTcpIdx, 0);                                                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif

  /* #60 Reset one-time option values */
  TcpIp_SetTxOneTimeOptsOfSocketTcpDyn(NewSocketTcpIdx, 0);                                                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTxOneTimeOptsLenOfSocketTcpDyn(NewSocketTcpIdx, 0);                                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* #70 Copy socket state from the listen socket */
  TcpIp_SetSockStateOfSocketTcpDyn(    NewSocketTcpIdx, TcpIp_GetSockStateOfSocketTcpDyn(    ListenSocketTcpIdx));      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSockStateNextOfSocketTcpDyn(NewSocketTcpIdx, TcpIp_GetSockStateNextOfSocketTcpDyn(ListenSocketTcpIdx));      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VAcceptedSocketStateHandling
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VAcceptedSocketStateHandling(
  TcpIp_SizeOfSocketTcpDynType ListenSocketTcpIdx,
  TcpIp_SizeOfSocketTcpDynType AcceptSocketTcpIdx)
{
  TcpIp_SizeOfSocketDynType acceptSocketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(AcceptSocketTcpIdx);
  TcpIp_SizeOfSocketDynType listenSocketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(ListenSocketTcpIdx);
  TcpIp_SizeOfSocketOwnerConfigType socketOwnerConfigIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(listenSocketIdx);

  /* #10 Trigger sending of SYN and ACK (will be sent in MainFunction) */
  TcpIp_Tcp_VSendFlags(AcceptSocketTcpIdx, (TCPIP_TCP_CODE_BIT_SYN | TCPIP_TCP_CODE_BIT_ACK));

  /* #20 Set the socket to state 'active' */
  TcpIp_VSockTcpStateChg(acceptSocketIdx, socketOwnerConfigIdx, TCPIP_TCP_STATE_CONN_ESTAB, FALSE);  /* set socket to 'active' */

#if defined(TCPIP_SPECIAL_TCP_ACCEPTING_FCT)                                                                            /* COV_TCPIP_RUNTIME_TEST */
  /* #30 Inform the socket owner about an ongoing connection establishment, only if this feature is enabled. */
  /* It can be enabled that the listen socket owner is informed about an ongoing acceptance of an incoming connection
  request. Since the same callback function is used as for the final indication of the acceptance of an incoming
  connection, only the second call of this callback means that the new connection is really fully accepted. */
  {
    (void)TCPIP_SPECIAL_TCP_ACCEPTING_FCT(listenSocketIdx, acceptSocketIdx, &TcpIp_GetAddrRemSockOfSocketDyn(acceptSocketIdx)->TcpIpSockAddr); /* PRQA S 0310 */ /* MD_TCPIP_Rule11.3_0310_3305_SockAddrBaseType */ /* SBSW_TCPIP_FC_RemoteAddressAvailable */
  }
#endif
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_Open
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_Open(
  TcpIp_SocketTcpDynIterType        SocketTcpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockAddrPtr,
  boolean                           ActiveOpen)
{
  Std_ReturnType          retVal    = E_OK;
  TcpIp_SocketDynIterType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  TCPIP_ASSERT(SocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn());
  TCPIP_ASSERT(SockAddrPtr != NULL_PTR);

  /* #10 Check if socket is already open. */
  if (   (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) != TCPIP_TCP_SOCK_STATE_CLOSED)                                /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) != TCPIP_TCP_SOCK_STATE_LISTEN))
  {
    /* RFC: 'error: connection already exists' */
    /* Windows: WSAEISCONN - 10056 - 'Socket is already connected' */
    retVal = E_NOT_OK;
  }
  /* #20 Check if buffers are assigned to the socket. */
  else if (   (TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx) >= TcpIp_GetSizeOfTcpTxBufferDesc())             /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
           || (TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx) >= TcpIp_GetSizeOfTcpRxBufferDesc()))
  {
    /* one or both buffers assignments are missing, so it is not possible to open a connection */
    retVal = E_NOT_OK;
  }
  else
  {
    /* #30 Set the remote socket address */
    (void)IpBase_CopySockAddr(&TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)->SockAddr, &SockAddrPtr->SockAddr);           /* SBSW_TCPIP_FC_WriteRemoteAddress */

    /* init variables for this socket */
    TcpIp_SetRcvNxtOfSocketTcpDyn(SocketTcpIdx, 0);                                                                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

    /* #40 Open the TCP socket */
    if (ActiveOpen == TCPIP_TCP_ACTIVE_OPEN)
    {
      TcpIp_Tcp_OpenActive(SocketTcpIdx, SockAddrPtr->sa_family);
    }
    else
    {
      TcpIp_Tcp_OpenPassive(SocketTcpIdx);
    }
  }

  return retVal;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_OpenActive
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_OpenActive(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  TcpIp_DomainType           Domain)
{
  /* Socket is opened actively */
  /* Connect (active open) */
  /*
  RFC:
  - select an initial send sequence number (ISS)
  - send a SYN segment of the form <SEQ=ISS><CTL=SYN>
  - set SND.UNA to ISS, SND.NXT to ISS + 1, enter SYN-SENT state, and return.
  */
  /* #10 Trigger sending SYN and set socket state */
  TcpIp_Tcp_VSendFlags(SocketTcpIdx, TCPIP_TCP_CODE_BIT_SYN);

  TcpIp_SetSockIsServerOfSocketTcpDyn( SocketTcpIdx, FALSE);                                                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_SYNSENT);                                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_SYNSENT);                                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
  /* #20 Reset keep alive timer if feature is supported */
  TcpIp_Tcp_VKeepAliveTrigger(SocketTcpIdx);
#endif

#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
  /* #30 Activate 'selective ack' option if supported */
  TcpIp_SetTxOneTimeOptsOfSocketTcpDyn(   SocketTcpIdx, (TcpIp_GetTxOneTimeOptsOfSocketTcpDyn(SocketTcpIdx) | (TcpIp_TxOneTimeOptsOfSocketTcpDynType)TCPIP_TCP_OPT_FLAG_SACK_PERMIT)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTxOneTimeOptsLenOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetTxOneTimeOptsLenOfSocketTcpDyn(SocketTcpIdx) + (TCPIP_TCP_OPT_LEN_SACK_PERMIT + 2u)));  /* option + 2x NOP */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif

  /* #40 Set maximum segment length depending on used address family */
  if (Domain == IPBASE_AF_INET)
  {
    TcpIp_SetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_DEFAULT_TX_MSS_IPV4);                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else
  {
    TcpIp_SetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_DEFAULT_TX_MSS_IPV6);                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
  /* #50 Set default cwnd if supported */
  TcpIp_SetCwndSegNumLimitOfSocketTcpCongCtrlDyn(SocketTcpIdx, TCPIP_TCP_DEFAULT_SEGMENT_LIMIT(TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx))); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx, ((uint32) TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx) * (uint32) TcpIp_GetCwndSegNumLimitOfSocketTcpCongCtrlDyn(SocketTcpIdx))); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif
}  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_Tcp_OpenPassive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_OpenPassive(
  TcpIp_SocketTcpDynIterType SocketTcpIdx)
{
  /* Socket is opened passively */
  /* Listen (passive open) */
  TcpIp_SizeOfTcpTxBufferDescType tcpTxBufferDescIdx;
  TcpIp_SizeOfTcpRxBufferDescType tcpRxBufferDescIdx;

  /* #10 Set socket state */
  TcpIp_SetSockIsServerOfSocketTcpDyn( SocketTcpIdx, TRUE);                                                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_LISTEN);                                      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_INVALID);                                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* Buffers have been assinged to this listen socket before, release those buffers but remember the buffer sizes. */
  /* tx buffer */
  /* #20 remember TxBuffer size */
  tcpTxBufferDescIdx = TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx);
  TCPIP_ASSERT(tcpTxBufferDescIdx < TcpIp_GetSizeOfTcpTxBufferDesc());
  TcpIp_SetRequestedTxBufferSizeOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetTcpTxBufferLengthOfTcpTxBufferDesc(tcpTxBufferDescIdx)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* #30 remember RxBuffer size */
  tcpRxBufferDescIdx = TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx);
  TCPIP_ASSERT(tcpRxBufferDescIdx < TcpIp_GetSizeOfTcpRxBufferDesc());
  TcpIp_SetRequestedRxBufferSizeOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(tcpRxBufferDescIdx)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* #40 Release already assigned Tx- and RxBuffer. */
  TcpIp_Tcp_VReleaseAssignedBuffers(SocketTcpIdx);
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_Tcp_Close
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
FUNC(void, TCPIP_CODE) TcpIp_Tcp_Close(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
  TcpIp_SocketIdType socketIdx;
#endif

  TCPIP_ASSERT(TCPIP_TCP_COND_VALID_TCPIDX(SocketTcpIdx));

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
  socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  if (TcpIp_IsUseTlsOfSocketTcpDyn(SocketTcpIdx) == TRUE)
  {
    (void)Tls_Close(socketIdx, FALSE);
    /* Return value of Tls_Close() is ignored because this function will only return an error if called with
       an invalid socket id or if TLS is not initialized. -> A Det will be reported by TLS in that case. */
  }
#endif

  TCPIP_VENTER_CRITICAL_SECTION();

  /* #10 Proceed the socket closure dependent on the current socket state. */
  switch (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx))
  {
  case TCPIP_TCP_SOCK_STATE_CLOSED:
    {
      /* #20 Close socket in state CLOSED */
      /* This TCP socket was previously requested and buffers might have been assigned, but the socket is still in state
      CLOSED. -> Release all resources assigned to this socket. */
      TcpIp_Tcp_VReleaseAssignedBuffers(SocketTcpIdx);
      TcpIp_SetRequestedRxBufferSizeOfSocketTcpDyn(SocketTcpIdx, 0);                                                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetRequestedTxBufferSizeOfSocketTcpDyn(SocketTcpIdx, 0);                                                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      break;
    }
  case TCPIP_TCP_SOCK_STATE_LISTEN:
    {
      /* #30 Close socket in state LISTEN */
      /* RFC: Any outstanding RECEIVEs are returned with 'error: closing'
      responses. Delete TCB, enter CLOSED state, and return. */

      /* delete/clear TCB element */
      TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_CLOSED);
      /* only server sockets can be in state 'listen' */
      TcpIp_Tcp_VHandleListenSocketClose(SocketTcpIdx);

      break;
    }
  case TCPIP_TCP_SOCK_STATE_SYNRCVD:
    {
      /* #40 Close socket in state SYNRCVD */

      /* RFC: issue sending of FIN segment (eventually put this request in send queue) */

      /* send FIN */
      TcpIp_Tcp_VSendFlags(SocketTcpIdx, (TCPIP_TCP_CODE_BIT_FIN));

      TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_FINWAIT1);                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_FINWAIT1);                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      break;
    }
  case TCPIP_TCP_SOCK_STATE_SYNSENT:
    {
      /* #50 Close socket in state SYNSENT */
      /* RFC: Delete the TCB and return 'error: closing' responses to any
      queued SENDs, or RECEIVEs. */

      /* delete/clear TCB element */
      TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_CLOSED);

      break;
    }
  case TCPIP_TCP_SOCK_STATE_ESTABLISHED:
    {
      /* #60 Close socket in state ESTABLISHED */
      /* RFC: Queue this until all preceding SENDs have been segmentized, then
      form a FIN segment and send it. In any case, enter FIN-WAIT-1 state. */

      /* send FINACK */
      TcpIp_Tcp_VSendFlags(SocketTcpIdx, (TCPIP_TCP_CODE_BIT_FIN | TCPIP_TCP_CODE_BIT_ACK));

      TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_FINWAIT1);                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_FINWAIT1);                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      break;
    }
  case TCPIP_TCP_SOCK_STATE_FINWAIT1:
  case TCPIP_TCP_SOCK_STATE_FINWAIT2:
    {
      /* #70 Close socket in state FINWAIT1 or FINWAIT2 */
      /* RFC: 'error: connection closing' */
      /* An 'ok' response would be acceptable, too, as long as a second FIN is not emitted. */
      TcpIp_SetLastSockError(TCPIP_SOCK_ERR_10101);
      break;
    }
  case TCPIP_TCP_SOCK_STATE_CLOSEWAIT:
    {
      /* #80 Close socket in state CLOSEWAIT */
      /* send FIN */
      TcpIp_Tcp_VSendFlags(SocketTcpIdx, TCPIP_TCP_CODE_BIT_FIN);

      TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_LASTACK);                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_LASTACK);                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      break;
    }
  default:
    {
      /* #90 Close socket in all other states */
      /* states: TCPIP_TCP_SOCK_STATE_CLOSING, TCPIP_TCP_SOCK_STATE_LASTACK, TCPIP_TCP_SOCK_STATE_TIMEWAIT */
      /* RFC: 'error: connection closing' */
      TcpIp_SetLastSockError(TCPIP_SOCK_ERR_10101);

      /* ignore request silently, closing is already in progress or finished */
      break;
    }
  }

  TCPIP_VLEAVE_CRITICAL_SECTION();

} /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_Abort
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
FUNC(void, TCPIP_CODE) TcpIp_Tcp_Abort(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  TcpIp_SizeOfSocketDynType socketIdx;

  TCPIP_ASSERT(TCPIP_TCP_COND_VALID_TCPIDX(SocketTcpIdx));

  socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
  if (TcpIp_IsUseTlsOfSocketTcpDyn(SocketTcpIdx) == TRUE)
  {
    (void)Tls_Close(socketIdx, TRUE);
    /* Return value of Tls_Close() is ignored because this function will only return an error if called with
       an invalid socket id or if TLS is not initialized. -> A Det will be reported by TLS in that case. */
  }
#endif

  /* send RST, delete TCB, enter CLOSED state, and return */

  /* #10 Proceed the socket closure dependent on the current socket state. */
  switch (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx))
  {
  case TCPIP_TCP_SOCK_STATE_CLOSED:
    {
      /* #20 Nothing to do for sockets already in state 'CLOSED'. */
      break;
    }
  case TCPIP_TCP_SOCK_STATE_LISTEN:
    {
      /* #30 Only server sockets can be in state 'LISTEN'. -> close not yet fully accepted connections that are related
        to this server socket. */
      TcpIp_Tcp_VHandleListenSocketClose(SocketTcpIdx);
      break;
    }
  default:
    {
      /* #40 For all other socket states send a RST. */
      TcpIp_Tcp_VSendReset(SocketTcpIdx, TcpIp_GetTxIpAddrIdxOfSocketDyn(socketIdx),                                    /* SBSW_TCPIP_FC_RemoteAddressAvailable */ /* SBSW_TCPIP_FC_LocalAddressAvailable */
        (TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)),
        (TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)),
      TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx), 0u, 0u);
      break;
    }
  }
  /* #50 Close the socket and release all assigned resources. */
  TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_RESET);
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleListenSocketClose
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VHandleListenSocketClose(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /* #10 Search for all sockets that have this socket as master socket. */
  TcpIp_SizeOfSocketTcpDynType localSocketTcpIdx;
  for (localSocketTcpIdx = 0; localSocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn(); localSocketTcpIdx++)
  {
    if (TcpIp_GetSocketTcpDynMasterListenSocketIdxOfSocketTcpDyn(localSocketTcpIdx) == SocketTcpIdx)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    {
      /* #20 Close socket, if state is lower than established. */
      if (TcpIp_GetSockStateOfSocketTcpDyn(localSocketTcpIdx) < TCPIP_TCP_SOCK_STATE_ESTABLISHED)
      {
        /* abort the connection establishment */
        /* There won't be a recursion since partly accepted sockets switch from state 'listen' to 'syn_received' in the
        context of the received SYN. If the Abort interrupts this handling, TcpIp_Tcp_VHandleListenSocketClose will
        call TcpIp_Tcp_Abort and this again will call TcpIp_Tcp_VHandleListenSocketClose, but there won't be any
        matching sockets to close that have this partly accepted socket as their master listen socket. */
        TcpIp_Tcp_Abort(localSocketTcpIdx);
      }
      /* #30 Otherwise: Just delete reference to master listen socket. */
      else
      {
        /* Reset the referenced MasterListenSocketIdx since this would not be valid any more after closing this referenced listen socket. */
        TcpIp_SetSocketTcpDynMasterListenSocketIdxOfSocketTcpDyn(localSocketTcpIdx, TCPIP_NO_SOCKETTCPDYNMASTERLISTENSOCKETIDXOFSOCKETTCPDYN); /* SBSW_TCPIP_AWA_CslIteration_Local */
      }
    }
  }
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_ResetSocket
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_ResetSocket(
  TcpIp_SocketTcpDynIterType SocketTcpIdx)
{
  TcpIp_SocketDynIterType           socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  /* #10 Mark all reset queue elements related to the given socket as 'invalid'. */
  {
    uint8  currentRstQueueIdx;
    uint8  numCheckedRstElements;

    TCPIP_VENTER_CRITICAL_SECTION();

    currentRstQueueIdx     = TcpIp_Tcp_RstTxQueueReadPos;
    numCheckedRstElements  = 0;

    while (numCheckedRstElements < TcpIp_Tcp_RstTxQueueFillNum)
    {
      /* get the queue element */
      TCPIP_P2V(TcpIp_Tcp_RstTxQueueType) rstQueuePtr = TcpIp_GetAddrTcpResetQElement(currentRstQueueIdx);

      /* Mark queue element as invalid. The invalidated elements will be deleted in function TcpIp_Tcp_VTransmitResets. */
      if (TcpIp_VSockAddrIpAndPortIsEqual(&rstQueuePtr->LocSock, TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)) == TRUE)   /* SBSW_TCPIP_FC_PointerDerivedFromValidResetQEleIdx */ /* SBSW_TCPIP_FC_LocalAddressAvailable */
      {
        rstQueuePtr->RemSock.sa_family = IPBASE_AF_UNSPEC;                                                              /* SBSW_TCPIP_PWA_PointerDerivedFromValidResetQEleIdx */
      }

      TcpIp_Tcp_IncTxRstQueueIdx(currentRstQueueIdx);

      numCheckedRstElements++;
    }

    TCPIP_VLEAVE_CRITICAL_SECTION();
  }

  TCPIP_ASSERT(TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) != TCPIP_TCP_SOCK_STATE_CLOSED);

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
  /* #20 Reset the TLS connection if used for this socket */
  if (TcpIp_IsUseTlsOfSocketTcpDyn(SocketTcpIdx) == TRUE)
  {
    Tls_TcpIpEvent(TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx), IPBASE_TCP_EVENT_RESET);
  }
#endif

  /* #30 Close the socket and release all assigned resources */
  TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_RESET);
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VReleaseAssignedBuffers
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VReleaseAssignedBuffers(
  TcpIp_SocketTcpDynIterType SocketTcpIdx)
{
  TcpIp_TcpRxBufferDescIterType tcpRxBufferDescIdx = TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx);
  TcpIp_TcpTxBufferDescIterType tcpTxBufferDescIdx = TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx);

  /* #10 Release RX buffer */
  if (tcpRxBufferDescIdx < TcpIp_GetSizeOfTcpRxBufferDesc())
  {
    TCPIP_ASSERT(SocketTcpIdx == TcpIp_GetSocketTcpDynIdxOfTcpRxBufferDescDyn(tcpRxBufferDescIdx));

    TcpIp_SetFillLevelOfTcpRxBufferDescDyn(tcpRxBufferDescIdx, 0);                                                      /* SBSW_TCPIP_AWA_CslIteration_Local */
    TcpIp_SetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(tcpRxBufferDescIdx, TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(tcpRxBufferDescIdx)); /* SBSW_TCPIP_AWA_CslIteration_Local */

    TcpIp_SetSocketTcpDynIdxOfTcpRxBufferDescDyn(tcpRxBufferDescIdx, TcpIp_GetSizeOfSocketTcpDyn());  /* invalid socket index */ /* SBSW_TCPIP_AWA_CslIteration_Local */
    TcpIp_SetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetSizeOfTcpRxBufferDesc());  /* invalid buffer index */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else
  {
    TCPIP_ASSERT(tcpRxBufferDescIdx == TcpIp_GetSizeOfTcpRxBufferDesc());
  }

  /* #20 Release TX buffer */
  if (tcpTxBufferDescIdx < TcpIp_GetSizeOfTcpTxBufferDesc())  /* valid buffer index */
  {
    TCPIP_ASSERT(SocketTcpIdx == TcpIp_GetSocketTcpDynIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx));

    TcpIp_SetFillLevelOfTcpTxBufferDescDyn(tcpTxBufferDescIdx, 0);                                                      /* SBSW_TCPIP_AWA_CslIteration_Local */
    TcpIp_SetTcpTxBufferWriteIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx, TcpIp_GetTcpTxBufferStartIdxOfTcpTxBufferDesc(tcpTxBufferDescIdx)); /* SBSW_TCPIP_AWA_CslIteration_Local */
    /* no read position required for TX buffer */

    TcpIp_SetSocketTcpDynIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx, TcpIp_GetSizeOfSocketTcpDyn());  /* invalid socket index */ /* SBSW_TCPIP_AWA_CslIteration_Local */
    TcpIp_SetTcpTxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetSizeOfTcpTxBufferDesc());        /* invalid buffer index */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

    /* no assigned buffer variable */
  }
  else
  {
    TCPIP_ASSERT(tcpTxBufferDescIdx == TcpIp_GetSizeOfTcpTxBufferDesc());
  }

}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VAssignRxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VAssignRxBuffer(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint32                       RequestedBufferSize)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Check if there is already a buffer assigned to this socket. */
  if (TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx) >= TcpIp_GetSizeOfTcpRxBufferDesc())
  {
    TCPIP_ASSERT(TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx) == TcpIp_GetSizeOfTcpRxBufferDesc());

    /* #20 Check that the socket is in state CLOSED. */
    if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_CLOSED)
    {
      TcpIp_TcpRxBufferDescIterType tcpRxBufferDescIdx;
      /* #30 Choose a matching rx buffer and assign it to the socket. */
      for (tcpRxBufferDescIdx = 0; tcpRxBufferDescIdx < TcpIp_GetSizeOfTcpRxBufferDesc(); tcpRxBufferDescIdx++)
      {
        if (   (TcpIp_GetSocketTcpDynIdxOfTcpRxBufferDescDyn(tcpRxBufferDescIdx) == TcpIp_GetSizeOfSocketTcpDyn())  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
            && (RequestedBufferSize == TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(tcpRxBufferDescIdx)))
        {
          /* found a free and matching buffer */
          /* the buffer size is never '0', this is assuerd by the configuration */
          TcpIp_SetSocketTcpDynIdxOfTcpRxBufferDescDyn(tcpRxBufferDescIdx, SocketTcpIdx);                               /* SBSW_TCPIP_AWA_CslIteration_Local */
          TcpIp_SetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx, (TcpIp_SizeOfTcpRxBufferDescType)tcpRxBufferDescIdx); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

          TcpIp_SetRcvWndOfSocketTcpDyn(SocketTcpIdx, (uint16)RequestedBufferSize);                                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

          retVal = E_OK;
          break;  /* stop the for-loop */
        }
      }
    }
    else
    {
      /* buffer may only be assigned in state 'Closed' */
      /* -> nothing to do, return value already is negative */
    }
  }
  else
  {
    /* a buffer is already assigned, an updated assignment is not supported -> E_NOT_OK */
  }

  return retVal;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VAssignTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VAssignTxBuffer(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint32                       RequestedBufferSize)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Check if there is already a buffer assigned to this socket. */
  if (TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx) == TcpIp_GetSizeOfTcpTxBufferDesc())
  {
    /* The buffer is not yet assigned to a socket */
    TcpIp_TcpTxBufferDescIterType  tcpTxBufferDescIdx;

    /* #20 Check that the socket is in state CLOSED. */
    if (   (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_CLOSED)                              /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        || (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_ESTABLISHED))
    {
      /* #30 Choose a matching tx buffer and assign it to the socket. */
      for (tcpTxBufferDescIdx = 0; tcpTxBufferDescIdx < TcpIp_GetSizeOfTcpTxBufferDesc(); tcpTxBufferDescIdx++)
      {
        if (   (TcpIp_GetSocketTcpDynIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx) == TcpIp_GetSizeOfSocketTcpDyn())  /* invalid socket idx */  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
            && (RequestedBufferSize == TcpIp_GetTcpTxBufferLengthOfTcpTxBufferDesc(tcpTxBufferDescIdx)))
        {
          /* found a free and matching buffer */
          /* the buffer size is never '0', this is assuerd by the configuration */
          TcpIp_SetSocketTcpDynIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx, SocketTcpIdx);                               /* SBSW_TCPIP_AWA_CslIteration_Local */
          TcpIp_SetTcpTxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx, (TcpIp_SizeOfTcpTxBufferDescType)tcpTxBufferDescIdx); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
          TcpIp_SetTxReqDataBufStartIdxOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetTcpTxBufferStartIdxOfTcpTxBufferDesc(tcpTxBufferDescIdx)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
          TcpIp_SetSsthreshOfSocketTcpCongCtrlDyn(SocketTcpIdx, TcpIp_GetTcpTxBufferLengthOfTcpTxBufferDesc(tcpTxBufferDescIdx));  /* init to tx buffer size */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif
          retVal = E_OK;
          break;  /* stop the for-loop */
        }
      }
    }
  }
  else
  {
    /* a buffer is already assigned, an updated assignment is not supported -> E_NOT_OK */
  }

  return retVal;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_SetSockOpt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_SetSockOpt(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8                        OptName,
  TCPIP_P2C(uint8)             OptValPtr)
{
  Std_ReturnType retVal = E_NOT_OK;

  TCPIP_ASSERT(SocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn());

  /* #10 Set the chosen socket option */
  switch (OptName)
  {
  case TCPIP_PARAMID_TCP_RXWND_MAX:
    {
      uint32 requestedBufferSize = TCPIP_GET_UINT32_RAW(OptValPtr, 0u);
      retVal = TcpIp_Tcp_VAssignRxBuffer(SocketTcpIdx, requestedBufferSize);
      break;
    }

  case TCPIP_PARAMID_V_TCP_TXBUFSIZE:
    {
      uint32 requestedBufferSize = TCPIP_GET_UINT32_RAW(OptValPtr, 0u);
      retVal = TcpIp_Tcp_VAssignTxBuffer(SocketTcpIdx, requestedBufferSize);
      break;
    }

#if (TCPIP_SUPPORT_TCP_NAGLE_TIMEOUT == STD_ON)
  case TCPIP_PARAMID_TCP_NAGLE:
    {
      if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_CLOSED)
      {
        boolean enabled = (boolean)(OptValPtr[0] == 1u);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
        TCPIP_ASSERT(TcpIp_HasSocketTcpNagleDyn() == TRUE);
        TcpIp_SetEnabledOfSocketTcpNagleDyn(SocketTcpIdx, enabled);                                                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        retVal = E_OK;
      }
      break;
    }
#endif

#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
  case TCPIP_PARAMID_TCP_KEEPALIVE:
  case TCPIP_PARAMID_TCP_KEEPALIVE_INTERVAL:
  case TCPIP_PARAMID_TCP_KEEPALIVE_PROBES_MAX:
  case TCPIP_PARAMID_TCP_KEEPALIVE_TIME:
    {
      retVal = TcpIp_Tcp_VSetSockOpt_KeepAliveOptions(SocketTcpIdx, OptName, OptValPtr);                                /* SBSW_TCPIP_FC_PASSING_API_POINTER */
      break;
    }
#endif

#if (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON)
  case TCPIP_PARAMID_V_TCP_UTOUPDATE:
  case TCPIP_PARAMID_V_TCP_UTOENABLED:
  case TCPIP_PARAMID_V_TCP_UTOCHANGEABLE:
    {
      TcpIp_Tcp_VSetSockOpt_UserTimeoutOptions(SocketTcpIdx, OptName, OptValPtr);                                       /* SBSW_TCPIP_FC_PASSING_API_POINTER */
      retVal = E_OK;
      break;
    }
#endif  /* (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON) */

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
  /* #20 Pass all TLS-related parameter change requests to the related function of the TLS module in case it is enabled. */
  case TCPIP_PARAMID_V_USE_TLS:
    {
      retVal = Tls_GetSocket(TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx));  /* get a free connection map element */
      if (retVal == E_OK)
      {
        TcpIp_SetUseTlsOfSocketTcpDyn(SocketTcpIdx, TRUE);
      }
    }
    break;
  case TCPIP_PARAMID_V_TLS_TXBUFSIZE:
  case TCPIP_PARAMID_V_TLS_RXBUFSIZE:
  case TCPIP_PARAMID_V_TLS_SELECT_OCSP_REQEST:
  case TCPIP_PARAMID_V_TLS_HEARTBEAT_MODE:
  case TCPIP_PARAMID_V_TLS_HEARTBEAT_PERIOD_S:
    {
      retVal = Tls_ChangeParameter(TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx), OptName, OptValPtr);  /* forward change request to TLS */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    }
    break;
#endif

  default:
    {
      /* Unknown TCP socket option. Do nothing, return E_NOT_OK */
    }
    break;
  }

  return retVal;
}  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_SetSockOpt_VKeepAliveOptions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VSetSockOpt_KeepAliveOptions(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8                        OptName,
  TCPIP_P2C(uint8)             OptValPtr)
{
  Std_ReturnType retVal = E_NOT_OK;

  switch (OptName)
  {
  case TCPIP_PARAMID_TCP_KEEPALIVE:
    {
      /* #10 Enable the keep alive feature. */
      boolean enabled = (boolean)(OptValPtr[0] == 1u);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
      TcpIp_SetEnabledOfSocketTcpKeepAliveDyn(SocketTcpIdx, enabled);                                                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      retVal = E_OK;
      break;
    }
  case TCPIP_PARAMID_TCP_KEEPALIVE_INTERVAL:
    {
      /* #20 Set the keep alive interval. */
      uint32 requestedValue = TCPIP_GET_UINT32_RAW(OptValPtr, 0u);

      if (requestedValue <= TCPIP_MAX_SEC_IN_UINT32_CYCLE_VAR)
      {
        TcpIp_SetProbeIntervalOfSocketTcpKeepAliveDyn(SocketTcpIdx, requestedValue * TCPIP_CYCLES_PER_SECOND);          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        TcpIp_Tcp_VKeepAliveTrigger(SocketTcpIdx);
        retVal = E_OK;
      }
      break;
    }
  case TCPIP_PARAMID_TCP_KEEPALIVE_PROBES_MAX:
    {
      /* #30 Set the maximum number of keep alive probes that shall be sent. */
      uint16 requestedValue = TCPIP_GET_UINT16_RAW(OptValPtr, 0u);

      TcpIp_SetProbesMaxOfSocketTcpKeepAliveDyn(SocketTcpIdx, requestedValue);                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_Tcp_VKeepAliveTrigger(SocketTcpIdx);
      retVal = E_OK;
      break;
    }
  case TCPIP_PARAMID_TCP_KEEPALIVE_TIME:
    {
      /* #40 Set the maximum time keep alive probes shall be sent before the connection will be closed. */
      uint32 requestedValue = TCPIP_GET_UINT32_RAW(OptValPtr, 0u);

      if (requestedValue <= TCPIP_MAX_SEC_IN_UINT32_CYCLE_VAR)
      {
        TcpIp_SetTimeoutOfSocketTcpKeepAliveDyn(SocketTcpIdx, requestedValue * TCPIP_CYCLES_PER_SECOND);                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        TcpIp_Tcp_VKeepAliveTrigger(SocketTcpIdx);
        retVal = E_OK;
      }
      break;
    }
  default:                                                                                                              /* COV_TCPIP_MISRA */
    {
      /* Not supported value for 'OptName' used */
      break;
    }
  }

  return retVal;
}
#endif


#if (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VSetSockOpt_UserTimeoutOptions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSetSockOpt_UserTimeoutOptions(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8                        OptName,
  TCPIP_P2C(uint8)             OptValPtr)
{
  /* #10 Proceed dependent on the option name */
  switch (OptName)
  {
  case TCPIP_PARAMID_V_TCP_UTOUPDATE:
    {
      /* #20 Set the time used for the user timeout. */
      uint16 requestedValue = TCPIP_GET_UINT16_RAW(OptValPtr, 0u);

      TcpIp_SetUtoOfSocketTcpUtoDyn(SocketTcpIdx, ((((uint32) requestedValue & TCPIP_TCP_OPT_USER_TIMEOUT_VALUE_MASK)    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
                                                * 1000u) / TCPIP_MAIN_FCT_PERIOD_MSEC));  /* update timeout value */
      if ((requestedValue & TCPIP_TCP_OPT_USER_TIMEOUT_FLAG_GRANULARITY_MINUTES) != 0u)
      {
        /* user timeout value has granularity of minutes (60s per minute) */
        TcpIp_SetUtoOfSocketTcpUtoDyn(SocketTcpIdx, (TcpIp_GetUtoOfSocketTcpUtoDyn(SocketTcpIdx) * 60u));                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
      TcpIp_SetUtoAdvOfSocketTcpUtoDyn(SocketTcpIdx, requestedValue);                                                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetUtoChangeableOfSocketTcpUtoDyn(SocketTcpIdx, FALSE);  /* diable change by received option */             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetTxOneTimeOptsOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetTxOneTimeOptsOfSocketTcpDyn(SocketTcpIdx) | (TcpIp_TxOneTimeOptsOfSocketTcpDynType)TCPIP_TCP_OPT_FLAG_USER_TIMEOUT)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      break;
    }
  case TCPIP_PARAMID_V_TCP_UTOENABLED:
    {
      /* #30 Enable the sending of the user timeout option. */
      boolean enabled = (boolean)(OptValPtr[0] == 1u);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
      TcpIp_SetUtoEnabledOfSocketTcpUtoDyn(SocketTcpIdx, enabled);  /* enable or disable option handling */             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      if (enabled == FALSE)
      {
        TcpIp_SetUtoChangeableOfSocketTcpUtoDyn(SocketTcpIdx, TRUE);  /* set to default */                              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
      break;
    }
  case TCPIP_PARAMID_V_TCP_UTOCHANGEABLE:
    {
      /* #40 Enable user timeout update triggered by a received user timeout option. */
      boolean enabled = (boolean)(OptValPtr[0] == 1u);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
      TcpIp_SetUtoChangeableOfSocketTcpUtoDyn(SocketTcpIdx, enabled);  /* enable or disable timeout value update upon received timeout option */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      break;
    }
  default:                                                                                                              /* COV_TCPIP_MISRA */
    {
      /* Not supported value for 'OptName' used */
      break;
    }
  }
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
#endif


/**********************************************************************************************************************
 *  TcpIp_Tcp_VCheckRecChecksum
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VCheckRecChecksum(
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TCPIP_P2C(uint8)                  DataPtr,
  uint16                            LenByte)
{
  Std_ReturnType  retVal = E_OK;
  uint16_least    checksum;

  /* #10 Calc the TCP checksum */
  checksum = (uint16_least)TcpIp_VCalcPseudoHdrAndChecksum(RxSockRemAddrPtr, RxSockLocAddrPtr, DataPtr, LenByte, TCPIP_SOCK_PROT_TCP); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */

  /* #20 Check if the calculated checksum is 0 (=OK). */
  if (checksum == 0u)
  {
    /* checksum is valid -> OK */
  }
  else
  {
    /* checksum is invalid */
    retVal = E_NOT_OK;
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VSendFlags
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSendFlags(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  uint8                      Flags)
{
  /* #10 Add the requested flags to the already previously requested ones. */
  TcpIp_SetTxFlagsOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetTxFlagsOfSocketTcpDyn(SocketTcpIdx) | Flags));                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  TCPIP_ASSERT((Flags & TCPIP_TCP_CODE_BIT_RST) == 0u);

  /* #20 Set the next send sequence number in case a SYN flag shall be sent */
  if ((Flags & TCPIP_TCP_CODE_BIT_SYN) != 0u)
  {
    TcpIp_SetTxNextSendSeqNoOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx));                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }


  /* #30 Reset the nagle timeout, if nagle algorithm (with timeout) is enabled and one of the flags FIN, SYN or ACK is set. */
#if (TCPIP_SUPPORT_TCP_NAGLE_TIMEOUT == STD_ON)
  if (    (TcpIp_IsEnabledOfSocketTcpNagleDyn(SocketTcpIdx) == TRUE)
      && ((TcpIp_GetTxFlagsOfSocketTcpDyn(SocketTcpIdx) & TCPIP_TCP_CODE_BIT_MASK_FSA) != 0u))                           /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    TcpIp_SetTimeoutOfSocketTcpNagleDyn(SocketTcpIdx, 0);                                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
#endif
}

/**********************************************************************************************************************
 *  TcpIp_Tcp_VSendReset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSendReset(
  TcpIp_SocketTcpDynIterType        SocketTcpIdx,
  TcpIp_LocalAddrIterType           IpAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RemSockPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) LocSockPtr,
  uint32                            SeqNo,
  uint32                            AckNo,
  uint8                             Flags)
{
  /* #10 Delete the tx request for this socket if it is not in state LISTEN. */
  if (SocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn())
  {
    if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) != TCPIP_TCP_SOCK_STATE_LISTEN)
    {
      /* - reset length to send */
      TcpIp_SetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx, 0);                                                              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) != TCPIP_TCP_SOCK_STATE_SYNRCVD)
      {
        TcpIp_SetRcvNxtOfSocketTcpDyn(SocketTcpIdx, AckNo);                                                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
      TcpIp_SetTxFlagsOfSocketTcpDyn(SocketTcpIdx, 0);                                                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
  }

  /* #20 Add an element to the reset queue if the queue is not already full. */
  if (TcpIp_Tcp_RstTxQueueFillNum < TcpIp_GetSizeOfTcpResetQElement())
  {
    TcpIp_Tcp_RstTxQueueType *tcpResetQElementPtr = TcpIp_GetAddrTcpResetQElement(TcpIp_Tcp_RstTxQueueWritePos);

    tcpResetQElementPtr->SeqNo     = SeqNo;                                                                             /* SBSW_TCPIP_PWA_PointerDerivedFromValidResetQEleIdx */
    tcpResetQElementPtr->AckNo     = AckNo;                                                                             /* SBSW_TCPIP_PWA_PointerDerivedFromValidResetQEleIdx */
    tcpResetQElementPtr->Flags     = Flags;                                                                             /* SBSW_TCPIP_PWA_PointerDerivedFromValidResetQEleIdx */
    tcpResetQElementPtr->IpAddrIdx = (uint8) IpAddrIdx;                                                                         /* SBSW_TCPIP_PWA_PointerDerivedFromValidResetQEleIdx */
    (void)IpBase_CopySockAddr(&tcpResetQElementPtr->LocSock.SockAddr, &LocSockPtr->SockAddr);                           /* SBSW_TCPIP_FC_PointerDerivedFromValidResetQEleIdx */ /* SBSW_TCPIP_FC_PASSING_API_POINTER_CASTED */
    (void)IpBase_CopySockAddr(&tcpResetQElementPtr->RemSock.SockAddr, &RemSockPtr->SockAddr);                           /* SBSW_TCPIP_FC_PointerDerivedFromValidResetQEleIdx */ /* SBSW_TCPIP_FC_PASSING_API_POINTER_CASTED */

# if (TCPIP_SUPPORT_IPSEC == STD_ON)
    if (TCPIP_LOCAL_ADDR_IDX_IS_IPV4(IpAddrIdx))
    {
      /* Update the local socket adderss information in Tcp Reset socket, if it is Ipv4 */
      (void)IpV4_Ip_GetLocNetAddr(IpAddrIdx, &(TcpIp_GetAddrLocSockOfIpV4SocketDyn(TcpIp_GetIpV4SocketDynTcpRstIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX))->SockAddrIn.sin_addr));  /* SBSW_TCP_LOCSOCKADDR_PTR */
      TcpIp_GetAddrLocSockOfIpV4SocketDyn(TcpIp_GetIpV4SocketDynTcpRstIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX))->SockAddrIn.sin_port = LocSockPtr->SockAddrIn.sin_port;           /* SBSW_TCP_LOCSOCKADDR_PTR */
    }
#endif

    TcpIp_Tcp_IncTxRstQueueIdx(TcpIp_Tcp_RstTxQueueWritePos);
    TcpIp_Tcp_RstTxQueueFillNum++;
  }
  else
  {
    /* queue is too short, or there is a problem with sending the elements */
    /* do nothing but ignore this request */
  }
}  /* PRQA S 6050, 6060 */ /* MD_MSR_STCAL, MD_MSR_STPAR */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VFinalizeTxSegment
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VFinalizeTxSegment(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /* Accumulated DataLenByte may not exceed max payload length (minus TCP header length) of lower layer !! */

  uint8          segmentFlags;  /* TCP flags that shall be set in this segment. */
  Std_ReturnType retVal = E_OK;

  /* #10 Defer sending a FIN flag if pending TX data exceeds size of this segment. FIN flag must be set in last segment
  containing data. */
  if (TcpIp_GetTxTotNotQueuedLenOfSocketTcpDyn(SocketTcpIdx) > TcpIp_GetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx))
  {
    segmentFlags = (uint8)(TcpIp_GetTxFlagsOfSocketTcpDyn(SocketTcpIdx) & ~TCPIP_TCP_CODE_BIT_FIN);
  }
  else
  {
    segmentFlags = TcpIp_GetTxFlagsOfSocketTcpDyn(SocketTcpIdx);
  }

  TCPIP_ASSERT_MSG(TcpIp_GetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx) <= TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx), "segmenting is currently not supported."); /* this should never happen, this case is filtered in earlier steps */

  /* #20 Set flags and trigger the KeepAlive meachnism if there is something to send. */
  if (   (segmentFlags == 0u)                                                                                            /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_GetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx) == 0u))
  {
    /* neither data nor flags to send -> do nothing.
     * ACK-only segments will be sent later if required and are not managed in the retry queue.
     */
    /* return E_OK */
  }
  else
  {

    retVal = TcpIp_Tcp_VFinalizeTxSegment_SetFlagsAndKeepAlive(SocketTcpIdx, &segmentFlags);                            /* SBSW_TCPIP_FC_OutParamLocalVarRef */

    if (retVal == E_OK)
    {
      TCPIP_VENTER_CRITICAL_SECTION();

      /* #30 If data is available for sending, create a new tx element and trigger sending. */
      if (   (TcpIp_GetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx) == 0u)
          && (segmentFlags == TCPIP_TCP_CODE_BIT_ACK))
      {
        /* Only ACK segment shall be sent. This will be done at end of TcpIp_Tcp_VTransmit(). */
      }
      else
      {
        TcpIp_Tcp_TxRetrQueueType *newRetryQElementPtr;

        /* Create new retry queue element and append it the queue. */
        TcpIp_Tcp_VFinalizeTxSegment_CreateRetryQElement(SocketTcpIdx, &newRetryQElementPtr, segmentFlags);             /* SBSW_TCPIP_FC_OutParamLocalVarRef */

        /* Queue data for sending (mark data to be queued and reduce length of not queued data)  */
        TcpIp_Tcp_VFinalizeTxSegment_QueueDataForSending(SocketTcpIdx, newRetryQElementPtr, segmentFlags);              /* SBSW_TCPIP_FC_FinTxSeg_ValidPtrFromOtherFuncCall */
      }
      TCPIP_VLEAVE_CRITICAL_SECTION();
    }
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VFinalizeTxSegment_SetFlagsAndKeepAlive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VFinalizeTxSegment_SetFlagsAndKeepAlive(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8) SegmentFlagsPtr)
{
  Std_ReturnType retVal = E_OK;

  TCPIP_VENTER_CRITICAL_SECTION();
  if ((*SegmentFlagsPtr & TCPIP_TCP_CODE_BIT_RST) != 0u)
  {
    /* #10 If a reset is issued, RST shall be the only flag that is sent. */
    *SegmentFlagsPtr = TCPIP_TCP_CODE_BIT_RST;                                                                          /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
    TcpIp_SetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx, 0);                                                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else if (   (*SegmentFlagsPtr != TCPIP_TCP_CODE_BIT_SYN)                                                              /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
           && (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) != TCPIP_TCP_SOCK_STATE_CLOSED))
  {
    /* #20 An ACK flag is required in every segment except for SYN. */
    *SegmentFlagsPtr |= TCPIP_TCP_CODE_BIT_ACK;                                                                         /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
  }
  else
  {
    /* nothing to do */
  }
  TCPIP_VLEAVE_CRITICAL_SECTION();

  /* #30 If no free retry queue elements are available the function returns with an error. */
  if (TcpIp_Tcp_NumFreeRetryQEle == 0u)
  {
    retVal = E_NOT_OK;
  }
  else
  {
    /* since we only need one RetrQueue element, we can proceed this request */

#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
  /* #40 Trigger the keep alive timer to be reset. */
    TcpIp_Tcp_VKeepAliveTrigger(SocketTcpIdx);
#endif
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VFinalizeTxSegment_CreateRetryQElement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VFinalizeTxSegment_CreateRetryQElement(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(TcpIp_Tcp_TxRetrQueueType) *AddedRetryQElementPtr,
  uint8 SegmentFlags)
{
  TcpIp_SizeOfTcpRetryQElementType newRetrQueueEleIdx;
  TCPIP_P2V(TcpIp_Tcp_TxRetrQueueType) newRetryQElementPtr;

  /* #10 Take the frist element from the free-list. */
  newRetrQueueEleIdx      = TcpIp_Tcp_FirstFreeRetrQueueEle;
  newRetryQElementPtr     = TcpIp_GetAddrTcpRetryQElement(newRetrQueueEleIdx);
  *AddedRetryQElementPtr  = TcpIp_GetAddrTcpRetryQElement(newRetrQueueEleIdx);                                          /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
  if (TcpIp_Tcp_NumFreeRetryQEle > 1u)
  {
    TcpIp_GetAddrTcpRetryQElement(newRetryQElementPtr->EleNext)->ElePrev = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;           /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    TcpIp_Tcp_FirstFreeRetrQueueEle = newRetryQElementPtr->EleNext;
  }
  else
  {
    TcpIp_Tcp_FirstFreeRetrQueueEle = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;
    TcpIp_Tcp_LastFreeRetrQueueEle  = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;
  }
  TcpIp_Tcp_NumFreeRetryQEle--;

  /* #20 Append the (free) element to the sockets RetryQueue. */
  if (TcpIp_GetTcpRetryQElementLastIdxOfSocketTcpDyn(SocketTcpIdx) < TcpIp_GetSizeOfTcpRetryQElement())
  {
    /* there already is a retry list for this socket */
    TcpIp_GetAddrTcpRetryQElement(TcpIp_GetTcpRetryQElementLastIdxOfSocketTcpDyn(SocketTcpIdx))->EleNext = newRetrQueueEleIdx; /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->ElePrev           = TcpIp_GetTcpRetryQElementLastIdxOfSocketTcpDyn(SocketTcpIdx);              /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->EleNext           = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;                                         /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->SocketTcpIdx      = SocketTcpIdx;                                                              /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    TcpIp_SetTcpRetryQElementLastIdxOfSocketTcpDyn(SocketTcpIdx,  newRetrQueueEleIdx);                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else
  {
    /* there is no retry list for this socket, yet */
    newRetryQElementPtr->ElePrev           = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;                                         /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->EleNext           = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;                                         /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->SocketTcpIdx      = SocketTcpIdx;                                                              /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    TcpIp_SetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx, newRetrQueueEleIdx);                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetTcpRetryQElementLastIdxOfSocketTcpDyn(SocketTcpIdx, newRetrQueueEleIdx);                                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }

  /* #30 Set further struct elements of the RetryQElement */
  newRetryQElementPtr->SeqNo               = TcpIp_GetTxNextSendSeqNoOfSocketTcpDyn(SocketTcpIdx);                      /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
  newRetryQElementPtr->Flags               = SegmentFlags;                                                              /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */

#if (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON)
  newRetryQElementPtr->UserTimeoutTs       = TcpIp_Tcp_GlobalTimestamp + TcpIp_GetUtoOfSocketTcpUtoDyn(SocketTcpIdx);   /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
#else
  newRetryQElementPtr->UserTimeoutTs       = TcpIp_Tcp_GlobalTimestamp + TcpIp_GetUserTimeoutDefCyclesOfTcpConfig(TCPIP_TCPCONFIG_IDX);  /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
#endif

#if ((TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON) || (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON))
  /* Only two types of one time options are supported -
   * - User timeout
   * - Selective acknowledgment
   */
  if (   (TcpIp_GetTxOneTimeOptsOfSocketTcpDyn(SocketTcpIdx) != 0u)                                                       /* PRQA S 3415 5 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_GetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx) <=
         ((uint32) TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx) - (uint32) TcpIp_GetTxOneTimeOptsLenOfSocketTcpDyn(SocketTcpIdx))))
  {
    newRetryQElementPtr->OneTimeOptions    = TcpIp_GetTxOneTimeOptsOfSocketTcpDyn(SocketTcpIdx);                        /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->OneTimeOptionsLen = TcpIp_GetTxOneTimeOptsLenOfSocketTcpDyn(SocketTcpIdx);                     /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    TcpIp_SetTxOneTimeOptsOfSocketTcpDyn(SocketTcpIdx, 0);  /* clear global flags and len */                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetTxOneTimeOptsLenOfSocketTcpDyn(SocketTcpIdx, 0);                                                           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else
#endif
  {
    newRetryQElementPtr->OneTimeOptions    = 0;                                                                         /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->OneTimeOptionsLen = 0;                                                                         /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
  }

  newRetryQElementPtr->TransmitCounter     = 0;                                                                         /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
  newRetryQElementPtr->TimeStamp           = TcpIp_Tcp_GlobalTimestamp;                                                 /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
  newRetryQElementPtr->SizeTotByte         = TcpIp_GetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx);                          /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */

  newRetryQElementPtr->SackFlag            = 0;                                                                         /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
  /* The struct element newRetryQElementPtr->DataBufStartIdx does not have to be set since it is set in a subsequent function. */

}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VFinalizeTxSegment_QueueDataForSending
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VFinalizeTxSegment_QueueDataForSending(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(TcpIp_Tcp_TxRetrQueueType) NewRetryQElementPtr,
  uint8 SegmentFlags)
{
  TcpIp_SizeOfTcpTxBufferDescType tcpTxBufferDescIdx;
  uint32 unqueuedReqDataSize;

  tcpTxBufferDescIdx = TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx);

  TCPIP_ASSERT(tcpTxBufferDescIdx < TcpIp_GetSizeOfTcpTxBufferDesc());
  TCPIP_ASSERT(TcpIp_GetSocketTcpDynIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx) == SocketTcpIdx);
  TCPIP_ASSERT(TcpIp_GetTcpTxBufferLengthOfTcpTxBufferDesc(tcpTxBufferDescIdx) > 0u);

  /* #10 Advance the buffer start index (taking care of wraparound). */
  NewRetryQElementPtr->DataBufStartIdx = TcpIp_IncTxBufIdx(tcpTxBufferDescIdx,                                          /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
    TcpIp_GetTxReqDataBufStartIdxOfSocketTcpDyn(SocketTcpIdx), TcpIp_GetTxReqQueuedLenOfSocketTcpDyn(SocketTcpIdx));

  /* #20 Inc the queued len of the requested data. */
  unqueuedReqDataSize = (TcpIp_GetTxReqDataLenByteOfSocketTcpDyn(SocketTcpIdx) - TcpIp_GetTxReqQueuedLenOfSocketTcpDyn(SocketTcpIdx));

  TCPIP_ASSERT(TcpIp_GetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx)       <= unqueuedReqDataSize);
  TCPIP_ASSERT(TcpIp_GetTxTotNotQueuedLenOfSocketTcpDyn(SocketTcpIdx) == unqueuedReqDataSize);

  if (TcpIp_GetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx) == unqueuedReqDataSize)
  {
    TcpIp_SetTxReqFullyQueuedOfSocketTcpDyn(SocketTcpIdx, TRUE);                                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }

  TcpIp_SetTxReqQueuedLenOfSocketTcpDyn(SocketTcpIdx,                                                                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    (TcpIp_GetTxReqQueuedLenOfSocketTcpDyn(SocketTcpIdx) + TcpIp_GetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx)));
  TcpIp_SetTxTotNotQueuedLenOfSocketTcpDyn(SocketTcpIdx,                                                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    (TcpIp_GetTxTotNotQueuedLenOfSocketTcpDyn(SocketTcpIdx) - TcpIp_GetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx)));

  TcpIp_IncRetryQFillNumOfSocketTcpDyn(SocketTcpIdx);                                                                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* #30 Update TxNextSendSeqNo and reset flags and tx length. */
  TcpIp_SetTxNextSendSeqNoOfSocketTcpDyn(SocketTcpIdx,                                                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    (TcpIp_GetTxNextSendSeqNoOfSocketTcpDyn(SocketTcpIdx) + TcpIp_GetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx)));

  if ((TCPIP_TCP_CODE_BIT_SYN & SegmentFlags) != 0u)
  {
    TcpIp_IncTxNextSendSeqNoOfSocketTcpDyn(SocketTcpIdx);                                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }

  if ((TCPIP_TCP_CODE_BIT_FIN & SegmentFlags) != 0u)
  {
    TcpIp_IncTxNextSendSeqNoOfSocketTcpDyn(SocketTcpIdx);                                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }

  /* #40 Clear pending flags if they were set in this segment. The ACK flag will be handled later in VTransmit(). */
  TcpIp_SetTxFlagsOfSocketTcpDyn(SocketTcpIdx,                                                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    (TcpIp_GetTxFlagsOfSocketTcpDyn(SocketTcpIdx) & (uint8)~(SegmentFlags & ~TCPIP_TCP_CODE_BIT_ACK)));

  TcpIp_SetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx, 0);                                                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8                        Flags,
  uint32                       SeqNo,
  uint8                        OneTimeOptions,
  TcpIp_SizeOfTcpTxBufferType  DataStartIdx,
  TcpIp_SizeOfTcpTxBufferType  DataLenByte)
{
  Std_ReturnType                   retValue;
  uint8                            headerLenByte;
  /* Init the variable 'sackNum' to prevent MISRA checkers to issue the warning message 3353. The variable will always be set to a valid value before it is used */
  uint8                            sackNum = 0;  /* number of SACK elements to be sent */
  uint16                           ipPayloadLen;
  TcpIp_IpTxRequestDescriptorType  ipTxReqestDescr;
  uint8                           *ipPayloadPtr;
  TcpIp_SizeOfTcpTxBufferType      dataLenByteLocal = DataLenByte;
  /* #10 Calculate TCP header length (based on required options). */
  TcpIp_Tcp_VTransmitSegment_CalcHeaderLen(SocketTcpIdx, Flags, OneTimeOptions, &sackNum, &headerLenByte);              /* SBSW_TCPIP_FC_OutParamLocalVarRef */ /* SBSW_TCPIP_FC_OutParamLocalVarRef */

  ipPayloadLen = (uint16)dataLenByteLocal + headerLenByte;

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
  CANOE_WRITE_STRING_3("TcpIp_Tcp_VTransmitSegment: SocketTcpIdx %d: TcpIp_Tcp_Cwnd is now %d, call IP ProvTxBuffer with length %d", SocketTcpIdx, TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx), TgtLen);
#endif


  /* #20 Request a tx buffer from IP */
  retValue = TcpIp_Tcp_VTransmitSegment_RequestIpTxBuffer(SocketTcpIdx, &ipTxReqestDescr, &ipPayloadLen, &ipPayloadPtr); /* SBSW_TCPIP_FC_OutParamLocalVarRef */ /* SBSW_TCPIP_FC_OutParamLocalVarRef */ /* SBSW_TCPIP_FC_OutParamLocalVarRef */

  if (retValue == E_OK)
  {
    /* #30 Copy TCP payload to the ip buffer. */
    TcpIp_Tcp_VTransmitSegment_CopyDataToIpTxBuffer(SocketTcpIdx, DataStartIdx, dataLenByteLocal, ipPayloadPtr, headerLenByte); /* SBSW_TCPIP_FC_ForwardIpTxBufferRef */

    /* #40 Write the TCP header elements. */
    TcpIp_Tcp_VTransmitSegment_WriteHeaderElements(SocketTcpIdx, ipPayloadPtr, dataLenByteLocal, SeqNo, Flags);         /* SBSW_TCPIP_FC_ForwardIpTxBufferRef */

    /* #50 write the TCP header options. */
    TcpIp_Tcp_VTransmitSegment_WriteHeaderOptions(SocketTcpIdx, ipPayloadPtr, OneTimeOptions, sackNum, Flags);          /* SBSW_TCPIP_FC_ForwardIpTxBufferRef */

    dataLenByteLocal  += headerLenByte;

    /* checksum will be calculated by lower layer, value is already set to '0' */

    TCPIP_ASSERT(TcpIp_GetAddrRemSockOfSocketDyn(TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx))->sa_family == ipTxReqestDescr.AddressFamily);

    /* #60 Transmit the segment. */
    retValue = TcpIp_VIpTransmit(&ipTxReqestDescr, (uint16)dataLenByteLocal, TCPIP_PROTOCOL_TCP, 0u, 0u);               /* SBSW_TCPIP_FC_OutParamLocalVarRef */
  }

  return retValue;
}  /* PRQA S 6060 */ /* MD_MSR_STPAR */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment_CalcHeaderLen
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment_CalcHeaderLen(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8            Flags,
  uint8            OneTimeOptions,
  TCPIP_P2V(uint8) SackNumPtr,
  TCPIP_P2V(uint8) HeaderLenBytePtr
 )
{
  uint8 headerLenByte;

  /* Init this variable 'sackNum' to prevent MISRA checkers to issue the warning message 3353. The variable will always be set to a valid value before it is used */
  *SackNumPtr = 0;  /* number of SACK elements to be sent */                                                            /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */

#if ((TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_OFF)    && (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_OFF))
  TCPIP_UNUSED_PARAMETER(SocketTcpIdx);    /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
#if ((TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_OFF) && (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_OFF))
  TCPIP_UNUSED_PARAMETER(OneTimeOptions);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  /* #10 Calculate TCP header length. */
  headerLenByte = TCPIP_TCP_HDR_LEN_BYTE;
  if ((TCPIP_TCP_CODE_BIT_SYN & Flags) != 0u)
  {
    /* #20 For segment containing the SYN flag, add the length for the option 'max segment size'. */
    headerLenByte += TCPIP_TCP_OPT_LEN_MAX_SEG_SIZE;
  }

#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
  if (   (TcpIp_IsTimestampOptActiveOfSocketTcpTsOptDyn(SocketTcpIdx) == TRUE)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_SYNSENT))
  {
    /* #30 If the timestamp option is enabled for this socket, add the length for the option 'timestamp'. */
    headerLenByte += (TCPIP_TCP_OPT_LEN_TIMESTAMP + 2u);
  }
#endif

  /* #40 Add the length of options only sent in this segment if available. */
  /* Only two types of one time options are supported -
   * - User timeout
   * - Selective acknowledgment
   */
  /* there are additional options to send -> additional length */
#if (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON)
  if ((OneTimeOptions & TCPIP_TCP_OPT_FLAG_USER_TIMEOUT) != 0u)
  {
    /* #50 Add the length for the option 'user timeout'. */
    headerLenByte += TCPIP_TCP_OPT_LEN_USER_TIMEOUT;
  }
#endif
#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
  /* only allowed in the SYN messages */
  if ((OneTimeOptions & TCPIP_TCP_OPT_FLAG_SACK_PERMIT) != 0u)
  {
    /* #60 Add the length for the option 'selective acknowledgment permit'. */
    headerLenByte += (TCPIP_TCP_OPT_LEN_SACK_PERMIT + 2u);  /* including 2x NOP */
  }
#endif

#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
  /* #70 Add the length for the option 'selective acknowledgment'. */
  if (   (TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx) > 0u)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_IsSackOptActiveOfSocketTcpDyn(SocketTcpIdx) == TRUE))
  {
    uint8 headerRemaining;
    uint8 sackNumMax;
    uint8 oooNum;
    headerLenByte  += 4u;  /* 2* NOP + kind + len */
    headerRemaining = (uint8)(TCPIP_TCP_HDR_LEN_MAX_BYTE - headerLenByte);
    sackNumMax      = headerRemaining / TCPIP_TCP_SACK_ELEMENT_LEN;
    oooNum          = TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx);

    /* set currently number of used SACK elements */
    if (sackNumMax >= oooNum)
    {
      *SackNumPtr = oooNum;                                                                                             /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
    }
    else
    {
      *SackNumPtr = sackNumMax;                                                                                         /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
    }

    headerLenByte += (uint8)(*SackNumPtr * TCPIP_TCP_SACK_ELEMENT_LEN);  /* SACK elements */
  }
#endif

  *HeaderLenBytePtr = headerLenByte;                                                                                    /* SBSW_TCPIP_PWA_VALID_PTR_CALLER */
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment_RequestIpTxBuffer
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment_RequestIpTxBuffer(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(TcpIp_IpTxRequestDescriptorType) IpTxReqestDescrPtr,
  TCPIP_P2V(uint16) TgtLenPtr,
  TCPIP_P2V(uint8) *PayloadPtr)
{
  Std_ReturnType retVal = E_OK;
  TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  /* #10 Check which IP version is used. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  if (TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)->sa_family == IPBASE_AF_INET)
# endif
  {
    /* #20 Request a buffer from IpV4. */
    TcpIp_LocalAddrV4IterType ipV4AddrIdx = TcpIp_GetTxIpAddrIdxOfSocketDyn(socketIdx);
# if (TCPIP_SUPPORT_IPSEC == STD_ON)
    /* Store the transport protocol information in the tx descriptor */
    IpTxReqestDescrPtr->XptProtocol = IPV4_IP_PROTOCOL_TCP;                                                             /* SBSW_TCP_PTR_CALL_BY_REF_UPDATE */
# endif
    if (IpV4_Ip_ProvideTxBuffer(&ipV4AddrIdx, socketIdx, &TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)->SockAddrIn,       /* SBSW_TCPIP_FC_OutParamLocalVarRef */ /* SBSW_TCPIP_FC_RemoteAddressAvailable */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
        PayloadPtr, TgtLenPtr, IpTxReqestDescrPtr, FALSE) != BUFREQ_OK)
    {
      /* stop trying to get more buffers */
      retVal = E_NOT_OK;
    }
    else
    {
      /* #30 If this is a SYN segment, store the local source address used for this socket. */
      if (   (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_SYNSENT)                           /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          || (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_SYNRCVD))
      {
        /* Store source address used in received or sent SYN segment. The source address must noch change until the TCP
        connection is closed. Return value is ignored because IpV4_Ip_ProvideTxBuffer would have failed if no IP address
        is configured. */
        (void)IpV4_Ip_GetLocNetAddr(ipV4AddrIdx, &TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)->SockAddrIn.sin_addr);     /* SBSW_TCPIP_FC_LocalAddressAvailable */
        TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)->sa_family = IPBASE_AF_INET;                                         /* SBSW_TCPIP_PWA_SocketPointerDerivedFromValidSocketIdx */
      }
    }
  }
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  else
# endif
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  {
    /* #40 Request a buffer from IpV6. */
    TcpIp_LocalAddrV6IterType ipV6AddrIdx = TcpIp_GetTxIpAddrIdxOfSocketDyn(socketIdx);

    if (IpV6_ProvideTxBuffer(&ipV6AddrIdx, socketIdx,                                                                   /* SBSW_TCPIP_FC_OutParamLocalVarRef */ /* SBSW_TCPIP_FC_RemoteAddressAvailable */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
        &(TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)->SockAddrIn6.sin6_addr),
        PayloadPtr, TgtLenPtr, IpTxReqestDescrPtr, FALSE) != BUFREQ_OK )
    {
      /* stop trying to get more buffers */
      retVal = E_NOT_OK;
    }

    if (retVal == E_OK)
    {
      /* #50 If this is a SYN segment, store the local source address used for this socket. */
      if (   (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_SYNSENT)                           /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          || (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_SYNRCVD))
      {
        /* Determine the identifier of the ip address that has been selected by the IpV6.
        * If IpV6_ProvideTxBuffer has been called with an AutoSelect ip address identifier,
        * this address identifier will be replaced by an identifier for a specific source address.
        */
        TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)->sa_family = IPBASE_AF_INET6;                                        /* SBSW_TCPIP_PWA_SocketPointerDerivedFromValidSocketIdx */
        /* Return value is ignored because IpV6_ProvideTxBuffer would have failed if no IP address is configured. */
        (void)IpV6_GetLocalAddress(ipV6AddrIdx, &(TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)->SockAddrIn6.sin6_addr), NULL_PTR); /* SBSW_TCPIP_FC_LocalAddressAvailable' */
      }
    }
  }
#endif

  return retVal;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment_CopyDataToIpTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment_CopyDataToIpTxBuffer(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TcpIp_SizeOfTcpTxBufferType DataStartIdx,
  TcpIp_SizeOfTcpTxBufferType DataLen,
  TCPIP_P2V(uint8) IpPayloadPtr,
  uint8 TcpHeaderLen)
{
  /* #10 Check if there is data to send. */
  if (DataLen > 0u)
  {
    uint8  *tcpPayloadPtr;
    TcpIp_SizeOfTcpTxBufferDescType tcpTxBufferDescIdx = TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx);
    TcpIp_SizeOfTcpTxBufferType remLenAtEnd;

    TCPIP_ASSERT(tcpTxBufferDescIdx < TcpIp_GetSizeOfTcpTxBufferDesc());
    TCPIP_ASSERT(DataStartIdx >= TcpIp_GetTcpTxBufferStartIdxOfTcpTxBufferDesc(tcpTxBufferDescIdx));
    TCPIP_ASSERT(DataStartIdx <  TcpIp_GetTcpTxBufferEndIdxOfTcpTxBufferDesc(tcpTxBufferDescIdx));
    TCPIP_ASSERT(TcpIp_GetTcpTxBufferLengthOfTcpTxBufferDesc(tcpTxBufferDescIdx) > 0u);

    remLenAtEnd = TcpIp_GetTcpTxBufferEndIdxOfTcpTxBufferDesc(tcpTxBufferDescIdx) - DataStartIdx;

    tcpPayloadPtr = &IpPayloadPtr[TcpHeaderLen];  /* first byte following the TCP header */

    /* #20 Copy TCP payload to the ip buffer taking care of a wraparound in the TCP buffer. */
    if (DataLen > remLenAtEnd)
    {
      /* message is in end and start of circular buffer (splitted into two parts) */
      /* circular buffer: |DataPart2|xxxxxxxxxxx|DataPart1|  */
      TcpIp_SizeOfTcpTxBufferType len1;
      TcpIp_SizeOfTcpTxBufferType len2;
      TCPIP_P2C(uint8) src1Ptr;
      TCPIP_P2C(uint8) src2Ptr;

      len1    = remLenAtEnd;
      len2    = DataLen - len1;
      src1Ptr = TcpIp_GetAddrTcpTxBuffer(DataStartIdx);
      src2Ptr = TcpIp_GetAddrTcpTxBuffer(TcpIp_GetTcpTxBufferStartIdxOfTcpTxBufferDesc(tcpTxBufferDescIdx));

      /* copy the two data fragments */
      /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
      IpBase_Copy(tcpPayloadPtr, src1Ptr, len1);                                                                        /* SBSW_TCPIP_FC_CopyDataForTransmit */
      IpBase_Copy(&tcpPayloadPtr[len1], src2Ptr, len2);                                                                 /* SBSW_TCPIP_FC_CopyDataForTransmit */
    }
    else
    {
      /* message is in the circular buffer in one block (unsplitted) */
      TCPIP_P2C(uint8) srcPtr;

      srcPtr  = TcpIp_GetAddrTcpTxBuffer(DataStartIdx);

      /* copy this data (fragment) */
      /* since the data is in one block, no Pbuf copy mechanism is necessary */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpBase_Copy(tcpPayloadPtr, srcPtr, (uint16_least)DataLen);                                                        /* SBSW_TCPIP_FC_CopyDataForTransmit */
    }
  }  /* if (DataLenByte > 0) */
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment_WriteHeaderElements
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment_WriteHeaderElements(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8) TcpHdrPtr,
  TcpIp_SizeOfTcpTxBufferType DataLen,
  uint32 SeqNo,
  uint8 Flags)
{
  TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  /* #10 Write the TCP header elements */
  TCPIP_PUT_UINT16_RAW(TcpHdrPtr, TCPIP_TCP_HDR_SOURCE_PORT_OFFSET, TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)->DomainAndPort.port); /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
  TCPIP_PUT_UINT16_RAW(TcpHdrPtr, TCPIP_TCP_HDR_TARGET_PORT_OFFSET, TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)->DomainAndPort.port); /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */

  TCPIP_PUT_UINT32(TcpHdrPtr, TCPIP_TCP_HDR_SEQ_NUM_OFFSET, SeqNo);                                                     /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
  TCPIP_PUT_UINT32(TcpHdrPtr, TCPIP_TCP_HDR_ACK_NUM_OFFSET, TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx));  /* acknowledge received bytes */ /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */

  TcpHdrPtr[TCPIP_TCP_HDR_DATA_OFFSET_OFFSET] = TCPIP_TCP_HDR_DEFAULT_DATA_OFFSET_BYTE_VALUE;                           /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
  if (DataLen > 0u)
  {
    TcpHdrPtr[TCPIP_TCP_HDR_CODE_BITS_OFFSET] = (Flags | (uint8)TCPIP_TCP_CODE_BIT_PSH);                                /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
  }
  else
  {
    TcpHdrPtr[TCPIP_TCP_HDR_CODE_BITS_OFFSET] = Flags;                                                                  /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
  }
  TCPIP_PUT_UINT16(TcpHdrPtr, TCPIP_TCP_HDR_WINDOW_OFFSET,     TcpIp_GetRcvWndOfSocketTcpDyn(SocketTcpIdx));            /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
  TCPIP_PUT_UINT16(TcpHdrPtr, TCPIP_TCP_HDR_CHECKSUM_OFFSET,   TCPIP_TCP_EMPTY_CHKSUM);                                 /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
  TCPIP_PUT_UINT16(TcpHdrPtr, TCPIP_TCP_HDR_URGENT_PTR_OFFSET, TCPIP_TCP_EMPTY_URG_PTR);                                /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment_WriteHeaderOptions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment_WriteHeaderOptions(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8) TcpHdrPtr,
  uint8 OneTimeOptions,
  uint8 SackNum,
  uint8 Flags)
{
  uint8 *hdrOptPtr = &TcpHdrPtr[TCPIP_TCP_HDR_LEN_BYTE];
  uint8  hdrOptLen = 0;
#if ((TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_OFF) && (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_OFF))
  TCPIP_UNUSED_PARAMETER(OneTimeOptions);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  if ((TCPIP_TCP_CODE_BIT_SYN & Flags) != 0u)
  {
    /* #10 Append the 'maximum segment size' option to the header if this is a SYN message. */
    hdrOptPtr[TCPIP_TCP_OPT_OFS_KIND]   = TCPIP_TCP_OPT_ID_MAX_SEG_SIZE;                                                /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
    hdrOptPtr[TCPIP_TCP_OPT_OFS_LENGTH] = TCPIP_TCP_OPT_LEN_MAX_SEG_SIZE;                                               /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
    {
      TcpIp_SizeOfTcpRxBufferDescType tcpRxBufferDescIdx = TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx);

      /* max size depends on socket rx buffer size and ETH rx message size (minus header) */
      uint16 maxLen = TcpIp_GetRxMssOfTcpConfig(TCPIP_TCPCONFIG_IDX);

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
      TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);
      if (TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)->sa_family == IPBASE_AF_INET6)
      {
        /* Fixed IPv6 header requires 20 bytes more than already considered IPv4 header. So TCP MSS has to be reduced by 20 bytes. */
        maxLen -= (TCPIP_IPV6_HDR_LEN_BYTE - TCPIP_IPV4_HDR_LEN_BYTE);
      }
#endif

      if (maxLen > TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(tcpRxBufferDescIdx))
      {
        /* MSS is limited by small TCP RX buffer */
        maxLen = (uint16)TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(tcpRxBufferDescIdx);
      }
      TCPIP_PUT_UINT16(hdrOptPtr, TCPIP_TCP_OPT_OFS_VALUE, maxLen);  /* local max for this socket (for rx) */           /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
    }

    hdrOptLen += TCPIP_TCP_OPT_LEN_MAX_SEG_SIZE;
    hdrOptPtr  = &hdrOptPtr[hdrOptLen];
  }

#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
  if (   (TcpIp_IsTimestampOptActiveOfSocketTcpTsOptDyn(SocketTcpIdx) == TRUE)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_SYNSENT))
  {
    /* #20 Append the 'timestamp' option to the header if enabled */
    uint8 *tempHdrOptPtr;
    uint8 thisOptLen;
    /* add two NOP elements */
    hdrOptPtr[0] = TCPIP_TCP_OPT_ID_NOP;                                                                                /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
    hdrOptPtr[1] = TCPIP_TCP_OPT_ID_NOP;                                                                                /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */

    /* add timestamp header */
    tempHdrOptPtr = &hdrOptPtr[2u * TCPIP_TCP_NOP_ELEMENT_LEN];
    tempHdrOptPtr[TCPIP_TCP_OPT_OFS_KIND]   = TCPIP_TCP_OPT_ID_TIMESTAMP;  /* Kind */                                   /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
    tempHdrOptPtr[TCPIP_TCP_OPT_OFS_LENGTH] = TCPIP_TCP_OPT_LEN_TIMESTAMP;  /* OptLen */                                /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
    TCPIP_PUT_UINT32(tempHdrOptPtr,  TCPIP_TCP_OPT_OFS_VALUE, TcpIp_Tcp_GlobalTimestamp);                               /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
    TCPIP_PUT_UINT32(tempHdrOptPtr, (TCPIP_TCP_OPT_OFS_VALUE + TCPIP_TCP_TIMESTAMP_ELEMENT_LEN),                        /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
      TcpIp_GetTimestampReceivedOfSocketTcpTsOptDyn(SocketTcpIdx));

    thisOptLen = (TCPIP_TCP_OPT_LEN_TIMESTAMP + 2u);
    hdrOptLen += thisOptLen;
    hdrOptPtr  = &hdrOptPtr[thisOptLen];
  }
#endif

#if (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON)
  if ((OneTimeOptions & TCPIP_TCP_OPT_FLAG_USER_TIMEOUT) != 0u)
  {
    /* #30 Append the 'user timeout' option to the header if enabled */
    uint8  thisOptLen;

    hdrOptPtr[TCPIP_TCP_OPT_OFS_KIND]   = TCPIP_TCP_OPT_ID_USER_TIMEOUT;  /* Kind */                                    /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
    hdrOptPtr[TCPIP_TCP_OPT_OFS_LENGTH] = TCPIP_TCP_OPT_LEN_USER_TIMEOUT;  /* OptLen */                                 /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
    TCPIP_PUT_UINT16(hdrOptPtr, TCPIP_TCP_OPT_OFS_VALUE, TcpIp_GetUtoAdvOfSocketTcpUtoDyn(SocketTcpIdx));               /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */

    thisOptLen = (TCPIP_TCP_OPT_LEN_USER_TIMEOUT);
    hdrOptLen += thisOptLen;
    hdrOptPtr  = &hdrOptPtr[thisOptLen];
  }
#endif

#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
  {
    /* #40 Append the 'selective acknowledgment' option to the header if enabled */
    hdrOptLen += TcpIp_Tcp_VTransmitSegment_WriteHeaderOptions_Sack(SocketTcpIdx, hdrOptPtr, OneTimeOptions, SackNum);  /* SBSW_TCPIP_FC_TCP_HEADER_OPT_PTR */
  }
#else
  TCPIP_UNUSED_PARAMETER(SackNum);    /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  TCPIP_UNUSED_PARAMETER(hdrOptPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  if (hdrOptLen > 0u)
  {
    /* there were some options added */
    TCPIP_ASSERT_MSG((hdrOptLen % 4u) == 0, "Total option length must always be a multiple of 4.");
    TcpHdrPtr[TCPIP_TCP_HDR_DATA_OFFSET_OFFSET] += (uint8)((hdrOptLen / 4u) << 4);                                       /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegment_WriteHeaderOptions_Sack
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(uint8, TCPIP_CODE) TcpIp_Tcp_VTransmitSegment_WriteHeaderOptions_Sack(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8) TcpHdrOptPtr,
  uint8 OneTimeOptions,
  uint8 SackNum)
{
  uint8 hdrOptLen = 0;
  TCPIP_P2V(uint8) locHdrOptPtr = TcpHdrOptPtr;

  if ((OneTimeOptions & TCPIP_TCP_OPT_FLAG_SACK_PERMIT) != 0u)
  {
    /* #10 Append the 'selective acknowledgment permit' option to the header */
    uint8  thisOptLen;
    /* add SACK permit option */
    locHdrOptPtr[0] = TCPIP_TCP_OPT_ID_SACK_PERMIT;   /* Kind */                                                        /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
    locHdrOptPtr[1] = TCPIP_TCP_OPT_LEN_SACK_PERMIT;  /* OptLen */                                                      /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */

    locHdrOptPtr[2] = TCPIP_TCP_OPT_ID_NOP;                                                                             /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
    locHdrOptPtr[3] = TCPIP_TCP_OPT_ID_NOP;                                                                             /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */

    thisOptLen = (TCPIP_TCP_OPT_LEN_SACK_PERMIT + 2u);
    hdrOptLen += thisOptLen;
    locHdrOptPtr  = &locHdrOptPtr[thisOptLen];
  }

  if (   (TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx) > 0u)                                                   /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_IsSackOptActiveOfSocketTcpDyn(SocketTcpIdx) == TRUE))
  {
    /* #20 Append 'selective acknowledgment' option to the header */
    /* send list with SackNum (1..4) elements */
    uint8                         thisOptLen;
    uint8                        *seqPtr;
    TcpIp_TcpOooQElementIterType  oooEleIdx;
    uint8_least                   sackNumAdded = 0;

    /* add SACK option */
    locHdrOptPtr[0] = TCPIP_TCP_OPT_ID_NOP;                                                                             /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
    locHdrOptPtr[1] = TCPIP_TCP_OPT_ID_NOP;                                                                             /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */

    locHdrOptPtr[2] = TCPIP_TCP_OPT_ID_SACK;  /* Kind */                                                                /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
    locHdrOptPtr[3] = (uint8)(TCPIP_TCP_OPT_LEN_SACK + (SackNum * TCPIP_TCP_SACK_ELEMENT_LEN));  /* OptLen */ /* variable SackNum is always initialized ! */ /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */

    /* #30 Add SACK elements */
    /* Add elements with element order according to RFC 2018, section 4:
      'The first SACK block (...) MUST specify the contiguous block of data containing the segment which triggered this ACK, ...'
      'The SACK option SHOULD be filled out by repeating the most recently reported SACK blocks ...' */
    TCPIP_ASSERT(TcpIp_GetTcpOooQElementLastChangedIdxOfSocketTcpOooDyn(SocketTcpIdx) < TcpIp_GetSizeOfTcpOooQElement());
    oooEleIdx = TcpIp_GetTcpOooQElementLastChangedIdxOfSocketTcpOooDyn(SocketTcpIdx);

    seqPtr = &locHdrOptPtr[4];

    /* SackNum is already calculated in function TcpIp_Tcp_VTransmitSegment_CalcHeaderLen and considers the number of
       elements in the out of order queue. */
    while (sackNumAdded < SackNum)
    {
      TCPIP_PUT_UINT32(seqPtr, 0,  TcpIp_GetAddrTcpOooQElement(oooEleIdx)->SeqNo);                                      /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
      TCPIP_PUT_UINT32(seqPtr, 4, (TcpIp_GetAddrTcpOooQElement(oooEleIdx)->SeqNo + TcpIp_GetAddrTcpOooQElement(oooEleIdx)->LenByte)); /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
      seqPtr  = &seqPtr[TCPIP_TCP_SACK_ELEMENT_LEN];

      oooEleIdx = TcpIp_GetAddrTcpOooQElement(oooEleIdx)->OlderEleIdx;
      sackNumAdded++;
    }

    thisOptLen = (uint8)(TCPIP_TCP_OPT_LEN_SACK + 2u + (SackNum * TCPIP_TCP_SACK_ELEMENT_LEN));
    hdrOptLen += thisOptLen;
  }

  return hdrOptLen;
}
#endif


/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmit
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VTransmit(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  Std_ReturnType retValue = E_OK;

  /* #10 Check user timeout of oldest element in retry queue and close connection if timeout has exceeded. */
  if (TcpIp_Tcp_VCloseConnectionIfNotAcked(SocketTcpIdx) != E_OK)
  {
    /* Sent data has not been answered too long and therefore the connection has been closed */
    retValue = E_NOT_OK;
  }
  else
  {
    boolean setNewRtoPending = FALSE;
    boolean dataSegmentSent  = FALSE;

    /* #20 Iterate over all elements in retry queue and send them if necessary. */
    TcpIp_Tcp_VSendPendingElements(SocketTcpIdx, &dataSegmentSent, &setNewRtoPending);                                  /* SBSW_TCPIP_FC_OutParamLocalVarRef */ /* SBSW_TCPIP_FC_OutParamLocalVarRef */

    /* #30 Update retransmit timing. */
    if (setNewRtoPending == TRUE)
    {
      uint32 newTimeout;
      TcpIp_TcpRetryQElementIterType retrQueueEleIdx;

      /* only for the first RetrQueue element */
      retrQueueEleIdx = TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx);
      if ((retrQueueEleIdx == TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV) || (TcpIp_GetAddrTcpRetryQElement(retrQueueEleIdx)->TransmitCounter == 1u))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      {
        /* first setting of the retransmit timer */
#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
        newTimeout = TcpIp_GetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx);
#else
        newTimeout = TcpIp_GetRetransTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX);
#endif
      }
      else
      {
        /* there has been at least one retransmission already */
        /* #40 Exponentioal backoff, double the timeout each time until maximum value is reached. */
        newTimeout = (TcpIp_GetRtoReloadValueOfSocketTcpDyn(SocketTcpIdx) * 2u);
        if (newTimeout > TcpIp_GetRetransTimeoutMaxOfTcpConfig(TCPIP_TCPCONFIG_IDX))
        {
          newTimeout = TcpIp_GetRetransTimeoutMaxOfTcpConfig(TCPIP_TCPCONFIG_IDX);
        }
      }
      TcpIp_SetRetransmitTimeoutOfSocketTcpDyn(SocketTcpIdx, newTimeout);                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetRtoReloadValueOfSocketTcpDyn(SocketTcpIdx, newTimeout);                                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      /* setNewRtoPending = FALSE; */
    }

    if (TcpIp_GetRetransmitTimeoutOfSocketTcpDyn(SocketTcpIdx) > 0u)
    {
      TcpIp_SetRetransmitTimeoutOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetRetransmitTimeoutOfSocketTcpDyn(SocketTcpIdx) - 1u)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }

    /* #50 Send an ACK if no data has been sent but sending an ACK has been requested. */
    if (TcpIp_GetTxFlagsOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_CODE_BIT_ACK)
    {
      if (dataSegmentSent == FALSE)
      {
        /* an ACK shall be sent */
        if (TcpIp_Tcp_VTransmitSegment(SocketTcpIdx, TCPIP_TCP_CODE_BIT_ACK, TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx), 0u, 0u, 0u) == E_OK)
        {
          TcpIp_SetTxFlagsOfSocketTcpDyn(SocketTcpIdx, 0);                                                              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        }
      }
      else
      {
        /* ACK was already sent with data segment. */
        TcpIp_SetTxFlagsOfSocketTcpDyn(SocketTcpIdx, 0);                                                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
    }
  }

  return retValue;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VCloseConnectionIfNotAcked
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VCloseConnectionIfNotAcked(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  Std_ReturnType                 retValue  = E_OK;
  TcpIp_SizeOfSocketDynType      socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  TCPIP_VENTER_CRITICAL_SECTION();

  /* #10 Access the first RetryQueue element of the socket. */
  if (TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx) < TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV)
  {
    /* #20 Close the connection if timeout has expired */
    if (TcpIp_GetAddrTcpRetryQElement(TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx))->UserTimeoutTs == TcpIp_Tcp_GlobalTimestamp)
    {
      /* The first element in the RetryQueue has not been ACKed too long (UserTimeout), so cancel the connection */

      /* send reset */
      TcpIp_Tcp_VSendReset( SocketTcpIdx, TcpIp_GetTxIpAddrIdxOfSocketDyn(socketIdx), (TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)), /* SBSW_TCPIP_FC_RemoteAddressAvailable */ /* SBSW_TCPIP_FC_LocalAddressAvailable */
        (TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)),
        TcpIp_GetAddrTcpRetryQElement(TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx))->SeqNo, 0u, 0u);

      /* enter CLOSED state, delete/clear TCB */
      TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_RESET);

      retValue = E_NOT_OK;
    }
  }

  TCPIP_VLEAVE_CRITICAL_SECTION();

  return retValue;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VSendPendingElements
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSendPendingElements(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(boolean) DataSegmentSentPtr,
  TCPIP_P2V(boolean) SetNewRtoPendingPtr)
{
  TcpIp_TcpRetryQElementIterType txRetrQueueEleIdx;
#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
  uint16 retrQueueEleCount = 0;
#endif

  /* #10 Get RetryQueue element index */
  /* If the retry queue is not empty the first element index in the queue is taken, if it is empty the first element
     index equals TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV. */
  txRetrQueueEleIdx = TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx);

  /* #20 Iterate over all elements in retry queue and send them if necessary. */
  while (txRetrQueueEleIdx < TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV)  /* PRQA S 0771 */ /* MD_TCPIP_TCP_15.4_0771_b */
  {
    TcpIp_Tcp_TxRetrQueueType *txRetrQueueElePtr;

    txRetrQueueElePtr = TcpIp_GetAddrTcpRetryQElement(txRetrQueueEleIdx);
#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
    retrQueueEleCount++;
#endif

    /* Each segment in the queue must have payload data or be a SYN/FIN segment. */
    TCPIP_ASSERT((txRetrQueueElePtr->SizeTotByte > 0) || ((txRetrQueueElePtr->Flags & (TCPIP_TCP_CODE_BIT_SYN | TCPIP_TCP_CODE_BIT_FIN)) != 0u));


    /* #30 Check if the element should be (re-)transmitted */
    if (   (txRetrQueueElePtr->TransmitCounter == 0u)  /* counter is 0 (new un-sent element) */                          /* PRQA S 3415 4 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        || (TcpIp_GetRetransmitTimeoutOfSocketTcpDyn(SocketTcpIdx) == 0u)  /* global timeout expired */
#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
        || (TcpIp_IsFastRetransmitPendingOfSocketTcpCongCtrlDyn(SocketTcpIdx) == TRUE)  /* fast retransmit pending */
#endif
       )
    {
      /* Segment was not transmitted or has to be retransmitted due to a retransmit timeout or a fast retransmit condition. */

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
      /* #40 Udate cwnd parameters. */
      TcpIp_Tcp_VUpdateCwndParamsForTransmission(SocketTcpIdx, txRetrQueueElePtr);                                      /* SBSW_TCPIP_FC_PointerDerivedFromValidRetryQEleIdx */

      /* #50 Check if the segment can be sent according to cwnd conditions. */
      if (   (TcpIp_GetCwndSegNumLimitOfSocketTcpCongCtrlDyn(SocketTcpIdx) > 0u)                                                 /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          && (retrQueueEleCount > TcpIp_GetCwndSegNumLimitOfSocketTcpCongCtrlDyn(SocketTcpIdx)))
      {
        /* cwnd is set to an initial value, so only a limited number of segments may be sent */
        /* limit exceeded -> skip this element and the following ones */
        break;  /* PRQA S 0771 */ /* MD_TCPIP_TCP_15.4_0771_b */
      }

      if (TCPIP_TCP_SEQ1_BIGGER_SEQ2((txRetrQueueElePtr->SeqNo + txRetrQueueElePtr->SizeTotByte),
           (   TcpIp_GetAddrTcpRetryQElement(TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx))->SeqNo
            +  TcpIp_GetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx)
            + ((uint32) TcpIp_GetDupAckCntOfSocketTcpCongCtrlDyn(SocketTcpIdx) * (uint32) TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx)))))
          /* (current element end sequence number) > (first element sequence number + cwnd + (DupAckCnt * SMSS)) */
          /* cwnd is increased according to RFC 5681, section 3.2
          '4.  For each additional duplicate ACK received (after the third), cwnd MUST be incremented by SMSS.'. */
      {
        /* Element does not fit into cwnd, so it can't be sent. Stop sending elements following the current one, since they won't fit into cwnd, neither. */
        /* skip this element and the following ones */
        break;  /* PRQA S 0771 */ /* MD_TCPIP_TCP_15.4_0771_b */
      }
#endif
      {
        /* try to send the segment */

        /* #60 Stop checking further queue elements if the current one does not fit into the send window. */
        if (TcpIp_Tcp_VSendPendingElements_CheckIfSegmentFitsInWindow(SocketTcpIdx, txRetrQueueElePtr) == FALSE)        /* SBSW_TCPIP_FC_PointerDerivedFromValidRetryQEleIdx */
        {
          break;  /* PRQA S 0771 */ /* MD_TCPIP_TCP_15.4_0771_b */
        }

        /* #70 Transmit the segment and update SndNxt value */
        if (TcpIp_Tcp_VTransmitSegmentAndUpdateSndNxt(SocketTcpIdx, txRetrQueueElePtr, DataSegmentSentPtr) == E_OK)     /* SBSW_TCPIP_FC_REFERENCE_OF_ARRAY_ELEMENT */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
        {
          /* transmission was successful */

          /* #80 Update Retransmit Timing and eventually remove segment from RetryQueue */
          TcpIp_Tcp_VSendPendingElements_UpdateRetransmitTiming(SocketTcpIdx, txRetrQueueElePtr, SetNewRtoPendingPtr);  /* SBSW_TCPIP_FC_REFERENCE_OF_ARRAY_ELEMENT */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
        }
        else
        {
          /* This is an error condition, caused by the lower layer (IP, EthIf...).
             E.g. IP next hop is currently unreachable or no ethernet TX buffer is available.
             Stop trying to send following elements in retry queue because this might lead to out of order transmission.
             Retry transmission starting with this segment in next MainFunction. */
          break;  /* PRQA S 0771 */ /* MD_TCPIP_TCP_15.4_0771_b */
        }
      }
    }
    else
    {
      /* nothing to do, skip this element */
    }

    txRetrQueueEleIdx = txRetrQueueElePtr->EleNext;
  }  /* while ( all RetrQueue elements ) */
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VSendPendingElements_CheckIfSegmentFitsInWindow
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
TCPIP_LOCAL FUNC(boolean, TCPIP_CODE) TcpIp_Tcp_VSendPendingElements_CheckIfSegmentFitsInWindow(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_TxRetrQueueType) TxRetrQueueElePtr)
{
  uint32   dataLen             = TxRetrQueueElePtr->SizeTotByte;
  boolean  segmentFitsInWindow = TRUE;

  /* #10 Check that the length of the current retry queue element is not 0. */
  if (dataLen > 0u)
  {
    /* #20 Check if tx window is not 0. */
    if (TcpIp_GetSndWndOfSocketTcpDyn(SocketTcpIdx) > 0u)
    {
      /* #30 Check if tx window is big enough for the current element */
      if ((TCPIP_TCP_SEQ1_BIGGER_SEQ2((TxRetrQueueElePtr->SeqNo + dataLen),
        (TcpIp_GetSndWl2OfSocketTcpDyn(SocketTcpIdx) + TcpIp_GetSndWndOfSocketTcpDyn(SocketTcpIdx)))))
      {
        /* tx window is too small for sending this message */
        segmentFitsInWindow = FALSE;
      }
    }
    else
    {
      /* #40 The send window has size '0' (is closed), check if a zero window probe already exists, otherwise create one. */
      /* Hint: A zero window probe element (which always has size '1') always is the first element in the retry queue. */
      if (TxRetrQueueElePtr->ElePrev == TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV)
      {
        /* The current retry queue element is the first retry queue element of this socket */
        if (TxRetrQueueElePtr->SizeTotByte == 1u)
        {
          /* this is a zero window probe, just go ahead, so nothing here */
        }
        else if (TcpIp_GetRetransmitTimeoutOfSocketTcpDyn(SocketTcpIdx) == 0u)
        {
          /* The first element in the TxRetrQueue has to be split into 1 byte and the rest.
             It is importent here, that 'TcpIp_Tcp_VSplitFirstRetrQueueEle' does not remove the first element from
             the retry queue. Otherwise iteration in 'TcpIp_Tcp_VSendPendingElements' would continue iteration over the
             free list. */
          TcpIp_Tcp_VSplitFirstRetrQueueEle(SocketTcpIdx);
          dataLen = TxRetrQueueElePtr->SizeTotByte;
        }
        else
        {
          segmentFitsInWindow = FALSE;
        }
      }
      else
      {
        /* this is not a zero window probe element */
        segmentFitsInWindow = FALSE;
      }
    }

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
    /* #50 Check if segment fits in cwnd */
    if (TCPIP_TCP_SEQ1_BIGGER_SEQ2((TxRetrQueueElePtr->SeqNo + dataLen), (TcpIp_GetSndWl2OfSocketTcpDyn(SocketTcpIdx) + TcpIp_GetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx))))
    {
      /* cwnd does not allow to send this segment */
      /* This could prevent a zero window probe element from being sent if cwnd = 0. */
      segmentFitsInWindow = FALSE;
    }
#else
    TCPIP_DUMMY_STATEMENT(dataLen);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
  }

  return segmentFitsInWindow;
}  /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VSendPendingElements_UpdateRetransmitTiming
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSendPendingElements_UpdateRetransmitTiming(
  TcpIp_SizeOfSocketTcpDynType         SocketTcpIdx,
  TCPIP_P2V(TcpIp_Tcp_TxRetrQueueType) TxRetrQueueElePtr,
  TCPIP_P2V(boolean)                   SetNewRtoPendingPtr)
{
  /* #10 Update the idle timeout */

#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
  TcpIp_SetIdleTimeoutShortOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx) + 2u));  /* reset the idle timer on each sent segment */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#else
  TCPIP_UNUSED_PARAMETER(SocketTcpIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  TCPIP_VENTER_CRITICAL_SECTION();

  /* #20 Update the transmit counter */

  /* reload retransmission timeout only for retransmissions of the first element in the RetrQueue */
  if (TxRetrQueueElePtr->ElePrev == TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV)
  {
    /* trigger reset of RTO */
    *SetNewRtoPendingPtr = TRUE;                                                                                        /* SBSW_TCPIP_PWA_VALID_API_POINTER */
  }
  TxRetrQueueElePtr->TransmitCounter++;                                                                                 /* SBSW_TCPIP_PWA_VALID_API_POINTER */

  TCPIP_VLEAVE_CRITICAL_SECTION();
}


#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VUpdateCwndParamsForTransmission
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
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VUpdateCwndParamsForTransmission(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_TxRetrQueueType) TxRetrQueueElePtr)
{
  /* #10 Adjust congestion control parameters. */

  /* #20 Check if the current element has already been sent at least once. */
  if (TxRetrQueueElePtr->TransmitCounter > 0u)
  {
    /* Segment has to be retransmitted. */

    /* #30 Check if the 'fast retransmit' mechanism has to be applied. */
    if (TcpIp_IsFastRetransmitPendingOfSocketTcpCongCtrlDyn(SocketTcpIdx) == TRUE)
    {
      TcpIp_SetFastRetransmitPendingOfSocketTcpCongCtrlDyn(SocketTcpIdx, FALSE);  /* reset value */                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
    else
    {
      /* this is a re-transmit -> we probably have congestion */
      /* same handling for SYN and non-SYN messages */
      TcpIp_SetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx, TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx));   /* cwnd = LW = 1*SMSS */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      /* #40 Check if the segment has the SYN flag set */
      if ((TCPIP_TCP_CODE_BIT_SYN & TxRetrQueueElePtr->Flags) == 0u)
      {
        /* #50 Set the slow start threshold if the segment has been sent once. */
        if (1u == TxRetrQueueElePtr->TransmitCounter)
        {
          TcpIp_Tcp_VSetSsthreshEqu4(SocketTcpIdx);  /* ssthresh = max[FlightSize / 2, 2*SMSS] */
          CANOE_WRITE_STRING_1("TcpIp_Tcp_VUpdateCwndParamsForTransmission: ssthresh was set to %d", TcpIp_GetSsthreshOfSocketTcpCongCtrlDyn(SocketTcpIdx));
        }
      }
      else
      {
        /* SYN flag is set in this message */
        /* #60 Trigger reset of RTO for this connection on transition to state 'ESTABLISHED' (set to 3s). */
        TcpIp_SetRtoResetPendingOfSocketTcpTsOptDyn(SocketTcpIdx, TRUE);                                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

        /* #70 Set the segment number limit to '1'. */
        TcpIp_SetCwndSegNumLimitOfSocketTcpCongCtrlDyn(SocketTcpIdx, 1u);                                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }

      /* RFC 6582, 3.2 4) */
      {
        TcpIp_SizeOfTcpRetryQElementType eleIdx;
        TcpIp_SizeOfTcpRetryQElementType prevEleIdx;  /* index of the previous retry queue element */

        /* #80 Check TransmitCounter of all retry queue elements for this socket not to be '0'. */
        prevEleIdx = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;
        eleIdx = TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx);
        /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        while (   (eleIdx < TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV)
               && (TcpIp_GetAddrTcpRetryQElement(eleIdx)->TransmitCounter > 0u))
        {
          prevEleIdx = eleIdx;
          eleIdx     = TcpIp_GetAddrTcpRetryQElement(eleIdx)->EleNext;
        }
        /* #90 Set the RECOVER variable of the congestion control mechanism to the sequence number of the first element
        that has not yet been sent (or to the sequence number that follows the last segment that has been sent at least
        once). */
        TCPIP_ASSERT(prevEleIdx < TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV);
        /* This code section is only called if at least on element of the retry queue has been sent at least once.
        Elements in the retry queue are in the order of their sequence number, so it can not occur that an element in
        the retry queue has already been sent while one of its predecessors in the queue has never been sent before. */
        /* PRQA S 2843 1 */ /* MD_TCPIP_2843 */
        TcpIp_SetRecoverOfSocketTcpCongCtrlDyn(SocketTcpIdx, ((TcpIp_GetAddrTcpRetryQElement(prevEleIdx)->SeqNo + TcpIp_GetAddrTcpRetryQElement(prevEleIdx)->SizeTotByte) - 1u)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }

      /* #100 Eventually exit fast recovery procedure */
      TcpIp_SetCongestionControlModeOfSocketTcpCongCtrlDyn(SocketTcpIdx, TCPIP_TCP_CONG_CTRL_MODE_SLOW_START);          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
  }
  else
  {
    /* this is a new element that shall be sent */
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif  /* TCPIP_SUPPORT_TCP_CONGESTION_CONTROL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitSegmentAndUpdateSndNxt
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VTransmitSegmentAndUpdateSndNxt(
  TcpIp_SizeOfSocketTcpDynType         SocketTcpIdx,
  TCPIP_P2V(TcpIp_Tcp_TxRetrQueueType) TxRetrQueueElePtr,
  TCPIP_P2V(boolean)                   DataSegmentSentPtr)
{
  Std_ReturnType  retValue = E_NOT_OK;

  /* #10 If this is the first element of the retry queue, delete SACK-flag (always retransmit the first element in the RetrQueue). */
  if (TxRetrQueueElePtr->ElePrev == TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV)
  {
    TxRetrQueueElePtr->SackFlag = 0;  /* delete SACK-flag, always retransmit the first element in the RetrQueue */      /* SBSW_TCPIP_PWA_VALID_API_POINTER */
  }

#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
  /* #20 Check if this element has already been noted in a selective acknowledgment message. */
  if (TxRetrQueueElePtr->SackFlag == 0u)
#endif
  {
    /* #30 Transmit the segment. */
    if (TcpIp_Tcp_VTransmitSegment(SocketTcpIdx, TxRetrQueueElePtr->Flags, TxRetrQueueElePtr->SeqNo,
      TxRetrQueueElePtr->OneTimeOptions, TxRetrQueueElePtr->DataBufStartIdx, TxRetrQueueElePtr->SizeTotByte) == E_OK)
    {
      retValue = E_OK;
      *DataSegmentSentPtr = TRUE;                                                                                       /* SBSW_TCPIP_PWA_VALID_API_POINTER */

      /* #40 If the segment has never been sent before, update the SendNxt variable. */
      if (TxRetrQueueElePtr->TransmitCounter == 0u)
      {
        /* 'When the sender creates a segment and transmits it the sender advances SND.NXT.'
        * [RFC793 3.7. Data Communication]
        */
        uint32 sndNxt = TxRetrQueueElePtr->SeqNo + TxRetrQueueElePtr->SizeTotByte;

        if ((TxRetrQueueElePtr->Flags & TCPIP_TCP_CODE_BIT_SYN) != 0u)
        {
          sndNxt++;
        }

        if ((TxRetrQueueElePtr->Flags & TCPIP_TCP_CODE_BIT_FIN) != 0u)
        {
          sndNxt++;
        }

        if (TCPIP_TCP_SEQ1_BIGGER_SEQ2(sndNxt, TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx)))
        {
          TcpIp_SetSndNxtOfSocketTcpDyn(SocketTcpIdx, sndNxt);                                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        }
        else
        {
          /* Avoid setting Tcp_SndNxt to smaller value if segment was recerated due to PathMTU change (TransmitCounter is reset to 0 in that case). */
        }
      }
    }
  }
#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
  else
  {
    /* #50 This element has already been noted in a selective acknowledgment message, skip this retry once */
    TxRetrQueueElePtr->SackFlag = 0; /* clear the SACK flag so that the retry will be issued the next time the retransmit-timeout occures */ /* SBSW_TCPIP_PWA_VALID_API_POINTER */
    retValue = E_OK;
  }
#endif

  return retValue;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitResets
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VTransmitResets(void)
{
  Std_ReturnType                   retValue;
  TcpIp_Tcp_RstTxQueueType        *rstQueuePtr;


  /* #10 Check if there are any pending resets. */
  while (TcpIp_Tcp_RstTxQueueFillNum > 0u)  /* PRQA S 0771 */ /* MD_TCPIP_TCP_15.4_0771_c */
  {
    rstQueuePtr = TcpIp_GetAddrTcpResetQElement(TcpIp_Tcp_RstTxQueueReadPos);

    /* #20 Remove elements that have destination addresses marked as unreachable by TcpIp_Tcp_VAddrResTimeout(). */
    if (IPBASE_AF_UNSPEC == rstQueuePtr->RemSock.sa_family)
    {
      TcpIp_Tcp_RstTxQueueFillNum--;
      TcpIp_Tcp_IncTxRstQueueIdx(TcpIp_Tcp_RstTxQueueReadPos);
    }
    else
    {
      uint8                           *tcpHdrPtr;
      uint16                           tgtLen = TCPIP_TCP_HDR_LEN_BYTE;
      TcpIp_IpTxRequestDescriptorType  ipTxReqestDescr;

      /* #30 Request a tx buffer from the corresponding IP layer. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
      if (rstQueuePtr->RemSock.sa_family == IPBASE_AF_INET)
#endif
      {
        /* V4 */
        TcpIp_LocalAddrV4IterType ipV4AddrIdx = rstQueuePtr->IpAddrIdx; /* required because IpAddrIdx is uint8 */
# if (TCPIP_SUPPORT_IPSEC == STD_ON)
        /* Store the transport protocol information in the tx descriptor */
        ipTxReqestDescr.XptProtocol = IPV4_IP_PROTOCOL_TCP;
# endif
        if (IpV4_Ip_ProvideTxBuffer(&ipV4AddrIdx,                                                                       /* SBSW_TCPIP_FC_REFERENCE_OF_VARIABLE */
          TcpIp_GetIpV4SocketDynTcpRstIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX),
          &rstQueuePtr->RemSock.SockAddrIn, &tcpHdrPtr, &tgtLen, &ipTxReqestDescr, FALSE) != BUFREQ_OK)                 /* SBSW_TCPIP_FC_PointerDerivedFromValidResetQEleIdx */ /* SBSW_TCPIP_FC_REFERENCE_OF_LOC_POINTER_VAR */ /* SBSW_TCPIP_FC_REFERENCE_OF_VARIABLE */ /* SBSW_TCPIP_FC_REFERENCE_OF_VARIABLE */
        {
          break;  /* No buffer could be provided */ /* PRQA S 0771 */ /* MD_TCPIP_TCP_15.4_0771_c */
        }

        rstQueuePtr->IpAddrIdx = (TcpIp_SizeOfLocalAddrV4Type)ipV4AddrIdx;                                              /* SBSW_TCPIP_PWA_PointerDerivedFromValidResetQEleIdx */
      }
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
      else
#endif
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
      {
        /* V6 */
        TcpIp_LocalAddrV6IterType ipV6AddrIdx = rstQueuePtr->IpAddrIdx; /* required because IpAddrIdx is uint8 */

        if (IpV6_ProvideTxBuffer(&ipV6AddrIdx, TcpIp_GetIpV6SocketDynTcpRstIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX),     /* SBSW_TCPIP_FC_REFERENCE_OF_VARIABLE */
          &(rstQueuePtr->RemSock.SockAddrIn6.sin6_addr),                                                                /* SBSW_TCPIP_FC_PointerDerivedFromValidResetQEleIdx */
          &tcpHdrPtr, &tgtLen, &ipTxReqestDescr, FALSE) != BUFREQ_OK)                                                   /* SBSW_TCPIP_FC_REFERENCE_OF_VARIABLE */ /* SBSW_TCPIP_FC_REFERENCE_OF_VARIABLE */
        {
          break;  /* PRQA S 0771 */ /* MD_TCPIP_TCP_15.4_0771_c */
        }

        rstQueuePtr->IpAddrIdx = (TcpIp_SizeOfLocalAddrV6Type)ipV6AddrIdx;                                              /* SBSW_TCPIP_PWA_PointerDerivedFromValidResetQEleIdx */
      }
#endif

      /* #40 Fill the TCP header elements. */
      TCPIP_PUT_UINT16_RAW(tcpHdrPtr, TCPIP_TCP_HDR_SOURCE_PORT_OFFSET, rstQueuePtr->LocSock.DomainAndPort.port);       /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
      TCPIP_PUT_UINT16_RAW(tcpHdrPtr, TCPIP_TCP_HDR_TARGET_PORT_OFFSET, rstQueuePtr->RemSock.DomainAndPort.port);       /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
      TCPIP_PUT_UINT32(    tcpHdrPtr, TCPIP_TCP_HDR_SEQ_NUM_OFFSET,     rstQueuePtr->SeqNo);                            /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
      TCPIP_PUT_UINT32(    tcpHdrPtr, TCPIP_TCP_HDR_ACK_NUM_OFFSET,     rstQueuePtr->AckNo);                            /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */

      tcpHdrPtr[TCPIP_TCP_HDR_DATA_OFFSET_OFFSET] = TCPIP_TCP_HDR_DEFAULT_DATA_OFFSET_BYTE_VALUE;                       /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
      if (rstQueuePtr->Flags == 0u)
      {
        tcpHdrPtr[TCPIP_TCP_HDR_CODE_BITS_OFFSET] = TCPIP_TCP_CODE_BIT_RST;                                             /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
      }
      else
      {
        tcpHdrPtr[TCPIP_TCP_HDR_CODE_BITS_OFFSET] = (uint8)(TCPIP_TCP_CODE_BIT_RST | rstQueuePtr->Flags);               /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
      }
      TCPIP_PUT_UINT16(tcpHdrPtr, TCPIP_TCP_HDR_WINDOW_OFFSET, 0u); /* byte order has to be considered if this value is not 0 */ /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
      TCPIP_PUT_UINT16(tcpHdrPtr, TCPIP_TCP_HDR_CHECKSUM_OFFSET, TCPIP_TCP_EMPTY_CHKSUM); /* checksum will be set by IP layer or hardware later */ /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
      TCPIP_PUT_UINT16(tcpHdrPtr, TCPIP_TCP_HDR_URGENT_PTR_OFFSET, 0u);                                                  /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */

      /* checksum will be calculated by lower layer, value is already set to '0' */

      TCPIP_ASSERT(rstQueuePtr->RemSock.sa_family == ipTxReqestDescr.AddressFamily);

      /* #50 Transmit the reset. Remove the element from the queue if transmit was successful, otherwise stop processing
      the reset queue. */
      retValue = TcpIp_VIpTransmit(&ipTxReqestDescr, TCPIP_TCP_HDR_LEN_BYTE, TCPIP_PROTOCOL_TCP, 0u, 0u);                 /* SBSW_TCPIP_FC_REFERENCE_OF_VARIABLE */

      if (retValue == E_OK)
      {
        TcpIp_Tcp_RstTxQueueFillNum--;
        TcpIp_Tcp_IncTxRstQueueIdx(TcpIp_Tcp_RstTxQueueReadPos);
      }
      else
      {
        /* transmit failed
           Possible reasons are a missing address resolution or no available buffer */
        break;  /* PRQA S 0771 */ /* MD_TCPIP_TCP_15.4_0771_c */
      }
    }
  }  /* while */
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VCloseSocketAndReleaseResources
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VCloseSocketAndReleaseResources(
  TcpIp_SocketTcpDynIterType         SocketTcpIdx,
  TcpIp_StateType                    State)
{
  TcpIp_SocketDynIterType           socketIdx     = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);
#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
  boolean                           socketUsesTls = TcpIp_IsUseTlsOfSocketTcpDyn(SocketTcpIdx);
#endif
  /* Store socket owner index for notification before it is reset by TcpIp_VDelSockAddrMapping() below. */
  TcpIp_SizeOfSocketOwnerConfigType socketOwnerConfigIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(socketIdx);

  /* #10 Enter CLOSED state, delete/clear TCB */
  TcpIp_Tcp_VRestartSock(SocketTcpIdx);
  TcpIp_VDelSockAddrMapping(socketIdx);

  /* #20 Signal a 'connection reset' to the user */
#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
  TcpIp_VSockTcpStateChg(socketIdx, socketOwnerConfigIdx, State, socketUsesTls);
#else
  TcpIp_VSockTcpStateChg(socketIdx, socketOwnerConfigIdx, State, FALSE);
#endif
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VRestartSock
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VRestartSock(
  TcpIp_SocketTcpDynIterType SocketTcpIdx)
{
  TcpIp_SetSockStateOfSocketTcpDyn(    SocketTcpIdx, TCPIP_TCP_SOCK_STATE_CLOSED);                                      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_INVALID);                                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_TCP_RX_OOO == STD_ON)
  TCPIP_ASSERT(TcpIp_HasSocketTcpOooDyn() == TRUE);
  /* #10 Check if there are out of order elements queued for this socket. */
  if (TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx) > 0u)
  {
    /* #20 If there are free ooo elements in the global free elements list, link the last element of the sockets ooo list
    with the first elememt of the global free elements list. */
    if (TcpIp_Tcp_OooNumFreeElements > 0u)
    {
      TcpIp_TcpOooQElementIterType currentCount;
      TcpIp_TcpOooQElementIterType eleIdx;

      /*  goto last element of the socket's ooo-list */
      eleIdx = TcpIp_GetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx);
      for (currentCount = 0;
           currentCount < (TcpIp_TcpOooQElementIterType)(TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx) - 1u);
           currentCount++)
      {
        eleIdx = TcpIp_GetAddrTcpOooQElement(eleIdx)->NextEleIdx;
      }
      /* last element in socket ooo list reached, now link it to the free-list */
      TcpIp_GetAddrTcpOooQElement(eleIdx)->NextEleIdx = TcpIp_Tcp_OooFirstFreeEleIdx;                                   /* SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx */
    }

    /* #30 Integrate the sockets ooo list elements into the global list of free elements. */
    /* prepend ooo-list elements to the global list of free elements */
    TcpIp_Tcp_OooFirstFreeEleIdx  = TcpIp_GetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx);
    TcpIp_Tcp_OooNumFreeElements += TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx);

    /* reset size of socket's ooo-list */
    TcpIp_SetTcpOooQElementFirstIdxOfSocketTcpOooDyn(SocketTcpIdx, TcpIp_GetSizeOfTcpOooQElement());                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetTcpOooQFillNumOfSocketTcpOooDyn(SocketTcpIdx, 0);                                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
#endif

  /* #40 Release TCP assigned rx and tx buffer */
  TcpIp_Tcp_VReleaseAssignedBuffers(SocketTcpIdx);
  TcpIp_SetRequestedRxBufferSizeOfSocketTcpDyn(SocketTcpIdx, 0);                                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetRequestedTxBufferSizeOfSocketTcpDyn(SocketTcpIdx, 0);                                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* #50 Init the socket variables */
  TcpIp_Tcp_VInitSock(SocketTcpIdx);
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VInitSock
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VInitSock(
  TcpIp_SocketTcpDynIterType SocketTcpIdx)
{
  TCPIP_ASSERT(SocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn());

  /* #10 Init rx and tx window */
  TcpIp_SetIssOfSocketTcpDyn(SocketTcpIdx, TcpIp_Tcp_GlobalTimestamp * (250u * TCPIP_MAIN_FCT_PERIOD_MSEC));  /* inc iss every 4 microseconds */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSndUnaOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetIssOfSocketTcpDyn(SocketTcpIdx));  /* ISS */                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSndNxtOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetIssOfSocketTcpDyn(SocketTcpIdx));  /* ISS */                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetRcvWndOfSocketTcpDyn(SocketTcpIdx,  0);                                                                      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */


  /* init the tx request variables */
  TcpIp_SetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx, 0);                                                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTxFlagsOfSocketTcpDyn(SocketTcpIdx, 0);                                                                      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  TcpIp_SetTxReqDataLenByteOfSocketTcpDyn(SocketTcpIdx, 0);                                                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTxReqQueuedLenOfSocketTcpDyn(SocketTcpIdx, 0);                                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTxReqDataBufStartIdxOfSocketTcpDyn(SocketTcpIdx, 0);                                                         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTxReqFullyQueuedOfSocketTcpDyn(SocketTcpIdx, TRUE);                                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* Init rx buffer */
  TcpIp_SetRxBufferRemIndLenOfSocketTcpDyn(SocketTcpIdx, 0);                                                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetRxBufferIndPosOfSocketTcpDyn(SocketTcpIdx, 0);                                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  /* #20 Init/delete tx queue */
  TcpIp_Tcp_VDelTxQueue(SocketTcpIdx);

  TCPIP_ASSERT(TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx) == TcpIp_GetSizeOfTcpRxBufferDesc());
  TcpIp_SetTxTotNotQueuedLenOfSocketTcpDyn(SocketTcpIdx, 0);                                                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  TcpIp_SetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx, 0); /* set MSS to zero. This value will be overwritten by the MSS option of a received SYN or the default MSS for IPv4/IpV6 */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTxMssAgreedOfSocketTcpDyn(SocketTcpIdx, 0);                                                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  TcpIp_SetPathMtuNewSizeOfSocketTcpDyn(SocketTcpIdx, 0);                                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetPathMtuChangedOfSocketTcpDyn(SocketTcpIdx, FALSE);                                                           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_TCP_NAGLE_TIMEOUT == STD_ON)
  TCPIP_ASSERT(TcpIp_HasSocketTcpNagleDyn() == TRUE);
  TcpIp_SetEnabledOfSocketTcpNagleDyn(SocketTcpIdx, TRUE);                                                              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTimeoutOfSocketTcpNagleDyn(SocketTcpIdx, 0);                                                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif

  /* #30 Init variables for tx options */
  TcpIp_SetTxOptLenOfSocketTcpDyn(SocketTcpIdx, 0);                                                                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTxOneTimeOptsOfSocketTcpDyn(SocketTcpIdx, 0);                                                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTxOneTimeOptsLenOfSocketTcpDyn(SocketTcpIdx, 0);                                                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON)
  TcpIp_SetUtoEnabledOfSocketTcpUtoDyn(SocketTcpIdx, FALSE);  /* RFC 5482 defines default = FALSE */                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetUtoChangeableOfSocketTcpUtoDyn(SocketTcpIdx, TRUE);                                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif

#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
  TcpIp_Tcp_VKeepAliveReset(SocketTcpIdx);
#endif

  /* #40 Init retransmision timing values */
#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
  TcpIp_SetTimestampOptActiveOfSocketTcpTsOptDyn(SocketTcpIdx, FALSE);                                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTimestampReceivedOfSocketTcpTsOptDyn(SocketTcpIdx, 0);                                                       /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  TcpIp_SetRtoOfSocketTcpTsOptDyn(SocketTcpIdx, TcpIp_GetRetransTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX));  /* set to RTOMin (instead of 3s like in RFC 2988 or 1s in RFC 6298) */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx, TcpIp_GetRetransTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX));  /* set to RTOMin (instead of 3s like in RFC 2988 or 1s in RFC 6298) */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetSRttOfSocketTcpTsOptDyn(SocketTcpIdx, 0);                                                                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetRttVarOfSocketTcpTsOptDyn(SocketTcpIdx, 0);                                                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetRtoStateOfSocketTcpTsOptDyn(SocketTcpIdx, TCPIP_TCP_RTO_STATE_FIRST_CALC_PROCEEDED);                         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetRtoResetPendingOfSocketTcpTsOptDyn(SocketTcpIdx, FALSE);                                                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  TcpIp_SetRetransmitTimeoutOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx));           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetRtoReloadValueOfSocketTcpDyn(   SocketTcpIdx, TcpIp_GetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx));           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#else
  TcpIp_SetRetransmitTimeoutOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetRetransTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX));      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetRtoReloadValueOfSocketTcpDyn(   SocketTcpIdx, TcpIp_GetRetransTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX));      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif

  /* #50 Init user timeout values */
#if (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON)
  TcpIp_SetUtoOfSocketTcpUtoDyn(SocketTcpIdx, TcpIp_GetUserTimeoutDefCyclesOfTcpConfig(TCPIP_TCPCONFIG_IDX));           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetUtoAdvOfSocketTcpUtoDyn(SocketTcpIdx, 0);                                                                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetUtoRemoteOfSocketTcpUtoDyn(SocketTcpIdx, 0);                                                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif

  /* #60 Init selective ACK variables */
#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
  TcpIp_SetSackOptActiveOfSocketTcpDyn(SocketTcpIdx, FALSE);                                                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTcpOooChangeCounterOfSocketTcpOooDyn(SocketTcpIdx, 0);                                                       /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif

  /* #70 Init congestion control variables. */
#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
  /* Congestion control according to RFC 5681 and RFC 6582 */
  /* congestion window (CWND) will be set when socket is opened, because it depends on IP version. */
  TcpIp_SetAckSumNOfSocketTcpCongCtrlDyn(SocketTcpIdx, 0);                                                              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetAckSumTimeoutOfSocketTcpCongCtrlDyn(SocketTcpIdx, 0);                                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetDupAckCntOfSocketTcpCongCtrlDyn(SocketTcpIdx, 0);                                                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetCongestionControlModeOfSocketTcpCongCtrlDyn(SocketTcpIdx, TCPIP_TCP_CONG_CTRL_MODE_SLOW_START);              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetRecoverOfSocketTcpCongCtrlDyn(SocketTcpIdx, TcpIp_GetIssOfSocketTcpDyn(SocketTcpIdx));                       /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetFastRetransmitPendingOfSocketTcpCongCtrlDyn(SocketTcpIdx, FALSE);                                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif

  TcpIp_SetSendLastHsAckOfSocketTcpDyn(SocketTcpIdx, FALSE);                                                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  TcpIp_SetEventIndicationPendingOfSocketTcpDyn(SocketTcpIdx, 0);                                                       /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetRstReceivedOfSocketTcpDyn(SocketTcpIdx, FALSE);                                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
  TcpIp_SetUseTlsOfSocketTcpDyn(SocketTcpIdx, FALSE);                                                                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VDelTxQueue
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VDelTxQueue(
  TcpIp_SocketTcpDynIterType SocketTcpIdx)
{
  /* #10 Check if a buffer is assigned to the socket */
  if (TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx) < TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV)
  {
    /* The TxRetrQueue is not empty. The complete list shall be deleted in one block, so the first element already has
    the previous element index marked as invalid as well as the next element index of the last list element is marked
    as invalid. */
    TcpIp_SizeOfTcpRetryQElementType eleIdx;
    TcpIp_SizeOfTcpRetryQElementType locLastEleIdx;
    TcpIp_SizeOfTcpRetryQElementType eleNum;

    /* #20 Count the number of elements in the tx retry queue of this socket */
    eleNum = 1;
    eleIdx = TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx);
    while (TcpIp_GetAddrTcpRetryQElement(eleIdx)->EleNext < TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV)
    {
      eleIdx = TcpIp_GetAddrTcpRetryQElement(eleIdx)->EleNext;
      eleNum++;
    }
    locLastEleIdx = eleIdx;

    /* #30 Append the sockets retry queue elements to the global free elements list. */
    if (TcpIp_Tcp_LastFreeRetrQueueEle < TcpIp_GetSizeOfTcpRetryQElement())
    {
      /* free elements list is not emptry */
      /* link last element of the free elements list with the first element of the socket's RetrQueue */
      TcpIp_GetAddrTcpRetryQElement(TcpIp_Tcp_LastFreeRetrQueueEle)->EleNext = TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx); /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
      TcpIp_GetAddrTcpRetryQElement(TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx))->ElePrev = TcpIp_Tcp_LastFreeRetrQueueEle; /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    }
    else
    {
      /* Take the whole socket's list and use it as the new free elements list. */
      TcpIp_Tcp_FirstFreeRetrQueueEle = TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx);
    }

    /* mark the last element of the socket's RetrQueue as the global last element of the free elements list */
    TcpIp_GetAddrTcpRetryQElement(locLastEleIdx)->EleNext = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;                          /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    TcpIp_Tcp_LastFreeRetrQueueEle = locLastEleIdx;

    /* in-/decrease number of (global) free element counters */
    TcpIp_Tcp_NumFreeRetryQEle += eleNum;
    TcpIp_SetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx, 0);                                                              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

    TcpIp_SetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV);                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetTcpRetryQElementLastIdxOfSocketTcpDyn( SocketTcpIdx, TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV);                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else
  {
    /* no queue elements available -> do nothing */
  }

  /* #40 Delete data from the tx buffer if available */
  TcpIp_Tcp_VClearTxBuffer(SocketTcpIdx);
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  Std_ReturnType retVal      = E_OK;
  uint8          byteIdx     = 0;
  boolean        endOptFound = FALSE;
  uint8          hdrOptLen   = SegmentDescriptorPtr->HdrLen - (uint8)TCPIP_TCP_HDR_LEN_BYTE;
  TCPIP_P2C(uint8)  hdrOptPtr = &(SegmentDescriptorPtr->HdrPtr)[TCPIP_TCP_HDR_LEN_BYTE];

  /* #10 Go through header bytes to identify the contained options */
  while (   (byteIdx < hdrOptLen)
         && (endOptFound == FALSE)
         && (retVal == E_OK))
  {
    uint8          optKind = hdrOptPtr[byteIdx /* + TCPIP_TCP_OPT_OFS_KIND */];
    uint8          optLen;
    Std_ReturnType optStatus;  /* determines if the option could be processed (could be evaluated, or unknown option is syntactically valid) */

    /* #20 Handle END and NOP option. */
    if (optKind <= TCPIP_TCP_OPT_ID_NOP)
    {
      /* END or NOP */
      if (optKind == TCPIP_TCP_OPT_ID_NOP)
      {
        /* option 'No-Operation'
        -> skip this byte */
      }
      else  /* TCPIP_TCP_OPT_ID_END */
      {
        /* option 'End of Option List'
        -> stop evaluation of options */
        endOptFound = TRUE;
      }

      optLen = 1;
      optStatus = E_OK;
    }
    else
    {
      /* #30 Check if the remaining options length is at least 2 bytes */
      if ((uint8)(hdrOptLen - byteIdx) >= 2u)  /* value '0' is already excluded by the while-loop */
      {
        optLen = hdrOptPtr[byteIdx + TCPIP_TCP_OPT_OFS_LENGTH];

        /* #40 Check if the option fits into the overall options length */
        if ((byteIdx + optLen) <= hdrOptLen)
        {
          /* #50 Handle the various TCP options */
          switch (optKind)
          {
          case TCPIP_TCP_OPT_ID_MAX_SEG_SIZE:
            {
              /* option 'Maximum Segment Size', option length is 4 byte */
              optStatus = TcpIp_Tcp_VHandleTcpOptions_MaxSegSize(SocketTcpIdx, &hdrOptPtr[byteIdx], optLen);            /* SBSW_TCPIP_FC_READ_TCP_HEADER_OPT_PTR */
              break;
            }
#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
          case TCPIP_TCP_OPT_ID_SACK_PERMIT:
            {
              /* option 'SACK Permitted', option length is 2 byte */
              optStatus = TcpIp_Tcp_VHandleTcpOptions_SackPermit(SocketTcpIdx, optLen);
              break;
            }
          case TCPIP_TCP_OPT_ID_SACK:
            {
              /* option 'SACK', option length is 2 + n*8 byte */
              optStatus = TcpIp_Tcp_VHandleTcpOptions_Sack(SocketTcpIdx, &hdrOptPtr[byteIdx], optLen);                  /* SBSW_TCPIP_FC_READ_TCP_HEADER_OPT_PTR */
              break;
            }
#endif
#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
          case TCPIP_TCP_OPT_ID_TIMESTAMP:
            {
              /* option 'Timestamp', option length is 10 byte */
              optStatus = TcpIp_Tcp_VHandleTcpOptions_Timestamp(SocketTcpIdx, SegmentDescriptorPtr, &hdrOptPtr[byteIdx], optLen); /* SBSW_TCPIP_FC_READ_TCP_HEADER_OPT_PTR */
              break;
            }
#endif  /* (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON) */
#if (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON)
          case TCPIP_TCP_OPT_ID_USER_TIMEOUT:
            {
              /* option 'User Timeout' */
              optStatus = TcpIp_Tcp_VHandleTcpOptions_UserTimeout(SocketTcpIdx, &hdrOptPtr[byteIdx], optLen);           /* SBSW_TCPIP_FC_READ_TCP_HEADER_OPT_PTR */
              break;
            }
#endif  /* (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON) */
          default:
            {
              /* unknown option */
              optStatus = TcpIp_Tcp_VHandleTcpOptions_Default(byteIdx, optLen, hdrOptLen);
              break;
            }
          }  /* switch */
        }
        else
        {
          /* Error, according to optLen this option exceeds the overall options length. */
          optStatus = E_NOT_OK;
        }
      }
      else
      {
        /* Error, only 1 byte of remaining options length while at least 2 bytes are needed for a valid option. */
        optLen = 0;
        optStatus = E_NOT_OK;
      }
    }

    /* #60 Close the connection if reading the option resulted in an error, or advance the read position */
    if (optStatus == E_OK)
    {
      /* advance the read position to the start of the next option */
      byteIdx += optLen;
    }
    else
    {
      /* erroneous option */
      TCPIP_DUMMY_STATEMENT(optLen);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
      /* -> drop message and send RST */
      TcpIp_Tcp_VHandleTcpOptions_ResetConnection(SocketTcpIdx, RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */

      retVal = E_NOT_OK;
    }
  }  /* while */

  /* #70 Reserve a part of the tx length for options that are sent during an active communication. */
#if ((TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON) || (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON))
  if (retVal == E_OK)
  {
    /* timestamp option and SACK option both have to be negotiated during the handshake within the same message */
    TcpIp_Tcp_VHandleTcpOptions_SetBlockedOptLen(SocketTcpIdx);
  }
#endif

  return retVal;
}  /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_MaxSegSize
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_MaxSegSize(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(uint8) OptPtr,
  uint8 OptLen)
{
  Std_ReturnType optStatus = E_OK;
  /* option 'Maximum Segment Size', option length is 4 byte */

  /* #10 Check if the received option length matches the expected length */
  if (OptLen == TCPIP_TCP_OPT_LEN_MAX_SEG_SIZE)
  {
    /* #20 Check if the option is received only in the correct connection state */
    if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) < TCPIP_TCP_SOCK_STATE_SYNRCVD)
    {
      uint16 maxLen = TCPIP_GET_UINT16(OptPtr, TCPIP_TCP_OPT_OFS_VALUE);

      /* #30 Set largest possible segment size and reduce it if necessary. */
      TcpIp_SetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetTxMssOfTcpConfig(TCPIP_TCPCONFIG_IDX));             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
      {
        TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);
        if(TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)->sa_family == IPBASE_AF_INET6)
        {
          /* Fixed IPv6 header requires 20 bytes more than already considered IPv4 header. So TCP MSS has to be reduced by 20 bytes. */
          TcpIp_SetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx,                                                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
            (TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx)
              - (TcpIp_TxMaxSegLenByteOfSocketTcpDynType)(TCPIP_IPV6_HDR_LEN_BYTE - TCPIP_IPV4_HDR_LEN_BYTE)));
        }
      }
#endif

      if (maxLen < TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx))
      {
        /* Received MSS is smaller than largest possible segment size the ECU can send.
        * -> Use received MSS value.
        */
        TcpIp_SetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx, maxLen);                                                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }

      /* Init SockMtuSize with received MaxSegLen */
      TcpIp_SetTxMssAgreedOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx));           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
      /* resize cwnd */
      TcpIp_SetCwndSegNumLimitOfSocketTcpCongCtrlDyn(SocketTcpIdx, TCPIP_TCP_DEFAULT_SEGMENT_LIMIT(maxLen));            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx, ((uint32) maxLen * TcpIp_GetCwndSegNumLimitOfSocketTcpCongCtrlDyn(SocketTcpIdx))); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
#endif
    }
    else
    {
      /* this option may not be received or evaluated in this state -> ignore it */
    }
  }
  else
  {
    /* erroneous option */
    optStatus = E_NOT_OK;
  }

  return optStatus;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


#if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_SackPermit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_SackPermit(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8 OptLen)
{
  Std_ReturnType optStatus = E_OK;

  /* #10 Check if the received option length matches the expected length and is received only in the correct connection state */
  if (   (OptLen == TCPIP_TCP_OPT_LEN_SACK_PERMIT)                                                                      /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) < TCPIP_TCP_SOCK_STATE_SYNRCVD))
  {
    /* received the permission to use the SACK option */
    /* #20 Activate the usage of the SACK option. */
    TcpIp_SetSackOptActiveOfSocketTcpDyn(SocketTcpIdx, TRUE);                                                           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

    /* #30 Trigger sending of 'SACK PERMIT' option for passive open */
    if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_LISTEN)
    {
      TcpIp_SetTxOneTimeOptsOfSocketTcpDyn(   SocketTcpIdx, (TcpIp_GetTxOneTimeOptsOfSocketTcpDyn(SocketTcpIdx) | (TcpIp_TxOneTimeOptsOfSocketTcpDynType)TCPIP_TCP_OPT_FLAG_SACK_PERMIT)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_SetTxOneTimeOptsLenOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetTxOneTimeOptsLenOfSocketTcpDyn(SocketTcpIdx) + (TCPIP_TCP_OPT_LEN_SACK_PERMIT + 2u)));  /* option + 2x NOP */ /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
  }
  else
  {
    /* erroneous option or received in the wrong TCP socket state */
    optStatus = E_NOT_OK;
  }

  return optStatus;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_Sack
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_Sack(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(uint8) OptPtr,
  uint8 OptLen)
{
  /* option 'SACK', option length is 2 + n*8 byte */
  Std_ReturnType optStatus = E_OK;
  uint8          remOptLen = (uint8)(OptLen - TCPIP_TCP_OPT_LEN_SACK);

  /* #10 Check if the received option length matches the expected length and is received only in the correct connection state */
  if (   ((remOptLen % TCPIP_TCP_SACK_ELEMENT_LEN) == 0u)  /* remOptLen is a multiple of 8 bytes */                      /* PRQA S 3415 6 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) >= TCPIP_TCP_SOCK_STATE_ESTABLISHED))
  {
    /* (OptLen - 2) is a multiple of 8 (=TCPIP_TCP_SACK_ELEMENT_LEN), so the option has a valid length. */
    uint8 sackEleNum = (uint8)(remOptLen / TCPIP_TCP_SACK_ELEMENT_LEN);  /* Number of received sequence number pairs,
                                                                    an empty sack option is also handled to be valid. */

    CANOE_WRITE_STRING_1("TcpIp_Tcp_VHandleTcpOptions: Received SACK option with %d elements", sackEleNum);

    /* #20 Mark elements in TxRetrQueue as selective acknowledged (sACKed) */
    if (TcpIp_GetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx) > 0u)
    {
      uint16 seqNrPairOfs = TCPIP_TCP_OPT_OFS_VALUE;

      while (sackEleNum > 0u)
      {
        uint32                           leftEdge  = TCPIP_GET_UINT32(OptPtr, seqNrPairOfs);
        uint32                           rightEdge = TCPIP_GET_UINT32(OptPtr, seqNrPairOfs + TCPIP_TCP_SEQU_NUM_LEN);
        TcpIp_SizeOfTcpRetryQElementType eleIdx;

        for (eleIdx = TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx);
             eleIdx < TcpIp_GetSizeOfTcpRetryQElement();
             eleIdx = TcpIp_GetAddrTcpRetryQElement(eleIdx)->EleNext)
        {
          /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          if (   TCPIP_TCP_SEQ1_BIGGER_OR_EQUAL_SEQ2(  TcpIp_GetAddrTcpRetryQElement(eleIdx)->SeqNo, leftEdge)
              && TCPIP_TCP_SEQ1_SMALLER_OR_EQUAL_SEQ2((TcpIp_GetAddrTcpRetryQElement(eleIdx)->SeqNo + TcpIp_GetAddrTcpRetryQElement(eleIdx)->SizeTotByte), rightEdge))
          {
            /* element is in the sequence number range of this SACK element -> mark as 'sacked' */
            TcpIp_GetAddrTcpRetryQElement(eleIdx)->SackFlag = 1;                                                        /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
          }
        }

        sackEleNum--;
        seqNrPairOfs += TCPIP_TCP_SACK_ELEMENT_LEN;
      }
    }
  }
  else
  {
    /* erroneous option */
    optStatus = E_NOT_OK;
  }

  return optStatus;
}  /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif


#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_Timestamp
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_Timestamp(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr,
  TCPIP_P2C(uint8) OptPtr,
  uint8 OptLen)
{
  Std_ReturnType optStatus = E_OK;

  /* #10 Check if the received option length matches the expected length and is received only in the correct connection state */
  if (OptLen == TCPIP_TCP_OPT_LEN_TIMESTAMP)
  {
    /* #20 Read received timestamp value */
    uint32 tsVal = TCPIP_GET_UINT32(OptPtr, TCPIP_TCP_OPT_OFS_VALUE);

    if (   (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_LISTEN)                              /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        || (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_SYNSENT))
    {
      /* #30 Activate the usage of the timestamp option and take over the timestamp */
      TcpIp_SetTimestampOptActiveOfSocketTcpTsOptDyn(SocketTcpIdx, TRUE);                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      TcpIp_SetTimestampReceivedOfSocketTcpTsOptDyn(SocketTcpIdx, tsVal);                                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }

    if (TcpIp_IsTimestampOptActiveOfSocketTcpTsOptDyn(SocketTcpIdx) == TRUE)
    {
      if (SegmentDescriptorPtr->SegSeq == TcpIp_GetRcvNxtOfSocketTcpDyn(SocketTcpIdx))
      {
        /* only take over the timestamp from the most recent segment that advanced the window */
        TcpIp_SetTimestampReceivedOfSocketTcpTsOptDyn(SocketTcpIdx, tsVal);                                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }

      /* #40 Read received timestamp echo reply */
      /* This is the timestamp that was earlier sent by this ECU -> evaluate RTT */
      if (   (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) != TCPIP_TCP_SOCK_STATE_LISTEN)                            /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          && (TCPIP_TCP_SEQ1_SMALLER_SEQ2(TcpIp_GetSndUnaOfSocketTcpDyn(SocketTcpIdx), SegmentDescriptorPtr->SegAck)))
      {
        uint32                      tsEcr = TCPIP_GET_UINT32(OptPtr, TCPIP_TCP_OPT_OFS_VALUE + 4u);
        uint32                      elementRtt;
        TcpIp_SizeOfTcpRetryQElementType retrQueueIdx;

        elementRtt = TcpIp_Tcp_GlobalTimestamp - tsEcr;

        if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_SYNRCVD)
        {
          TcpIp_Tcp_VUpdateRttVars(SocketTcpIdx, elementRtt);
        }

        /* #50 Search for corresponing element in the TxRetrQueue. If element was already retransmitted, discard this timestamp echo reply. */
        for (retrQueueIdx = TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx); retrQueueIdx < TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV; retrQueueIdx = TcpIp_GetAddrTcpRetryQElement(retrQueueIdx)->EleNext)
        {
          if (tsEcr == TcpIp_GetAddrTcpRetryQElement(retrQueueIdx)->TimeStamp)
          {
            /* the element was not yet retransmitted, so the tsEcr may be used for the RRTM */
            CANOE_WRITE_STRING_3("TcpIp_Tcp_VHandleTcpOptions: RetrQueue element found with matching Timestamp %d, acknowleged data size is %d, current segment RTT is %d)", tsEcr, (*TcpSegAckPtr - TcpIp_GetSndUnaOfSocketTcpDyn(SocketTcpIdx)), elementRtt);

            /* use elementRtt for connection RTT calculation */
            TcpIp_Tcp_VUpdateRttVars(SocketTcpIdx, elementRtt);

            break;  /* don't search for further elements, there is no benefit in finding more matching elements */
          }
        }
      }
    }
  }
  else
  {
    /* erroneous option */
    optStatus = E_NOT_OK;
  }

  return optStatus;
}  /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif  /* (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON) */


#if (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_UserTimeout
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_UserTimeout(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(uint8) OptPtr,
  uint8 OptLen)
{
  /* option 'User Timeout' */
  Std_ReturnType optStatus = E_OK;

  /* #10 Check if the received option length matches the expected length. */
  if (OptLen == TCPIP_TCP_OPT_LEN_USER_TIMEOUT)
  {
    /* #20 Check if changeing the user timeout value is possible */
    if (   (TcpIp_IsUtoEnabledOfSocketTcpUtoDyn(SocketTcpIdx)    == TRUE)                                                  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TcpIp_IsUtoChangeableOfSocketTcpUtoDyn(SocketTcpIdx) == TRUE))
    {
      uint32 timeoutRecCycles;
      uint16 optVal = TCPIP_GET_UINT16(OptPtr, TCPIP_TCP_OPT_OFS_VALUE);

      TcpIp_SetUtoRemoteOfSocketTcpUtoDyn(SocketTcpIdx, optVal);                                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      /* #30 Determine the new user timeout value and set the Uto */
      if ((optVal & TCPIP_TCP_OPT_USER_TIMEOUT_FLAG_GRANULARITY_MINUTES) == 0u)
      {
        /* granularity is seconds (= 1000ms) */
        timeoutRecCycles = (((uint32) optVal) * 1000u) / TCPIP_MAIN_FCT_PERIOD_MSEC;
      }
      else
      {
        /* granularity is minutes (= 60000ms) */
        timeoutRecCycles = (((uint32) optVal & TCPIP_TCP_OPT_USER_TIMEOUT_VALUE_MASK) * 60000u) / TCPIP_MAIN_FCT_PERIOD_MSEC;
      }

      if (timeoutRecCycles > 0u)
      {
        if (timeoutRecCycles < TcpIp_GetUserTimeoutMinCyclesOfTcpConfig(TCPIP_TCPCONFIG_IDX))
        {
          TcpIp_SetUtoOfSocketTcpUtoDyn(SocketTcpIdx, TcpIp_GetUserTimeoutMinCyclesOfTcpConfig(TCPIP_TCPCONFIG_IDX));   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        }
        else if (timeoutRecCycles > TcpIp_GetUserTimeoutMaxCyclesOfTcpConfig(TCPIP_TCPCONFIG_IDX))
        {
          TcpIp_SetUtoOfSocketTcpUtoDyn(SocketTcpIdx, TcpIp_GetUserTimeoutMaxCyclesOfTcpConfig(TCPIP_TCPCONFIG_IDX));   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        }
        else
        {
          TcpIp_SetUtoOfSocketTcpUtoDyn(SocketTcpIdx, timeoutRecCycles);                                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        }
      }
      else
      {
        /* reserved for future usage -> ignore this option */
      }
    }
  }
  else
  {
    /* erroneous option */
    optStatus = E_NOT_OK;
  }

  return optStatus;
}  /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif  /* (TCPIP_SUPPORT_TCP_USER_TIMEOUT_OPTION == STD_ON) */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_Default
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_Default(
  uint8 ByteIdx,
  uint8 OptLen,
  uint8 AllOptionsLen)
{
  Std_ReturnType optStatus = E_OK;
  uint8 remLen = (uint8)(AllOptionsLen - ByteIdx);

  /* #10 Check if the general option format is ok, then ignore the option, otherwise indicate an error. */
  if ((remLen >= OptLen) && (OptLen >= 2u))
  {
    /* unknown options will be ignored */
  }
  else
  {
    /* error in option */
    optStatus = E_NOT_OK;
  }

  return optStatus;
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_ResetConnection
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_ResetConnection(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_Tcp_SegmentDescriptorType) SegmentDescriptorPtr)
{
  TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);
  /* An erroneous option has been received -> send RST and close connection */

  /* #10 Trigger sending a RST. */
  TcpIp_Tcp_VSendReset(SocketTcpIdx, TcpIp_GetTxIpAddrIdxOfSocketDyn(socketIdx),                                        /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    RxSockRemAddrPtr, RxSockLocAddrPtr, SegmentDescriptorPtr->SegAck, 0u, 0u);

  /* #20 Close the socket. */
  if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) != TCPIP_TCP_SOCK_STATE_LISTEN)
  {
    /* enter CLOSED state, delete/clear TCB */
    TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_RESET);
  }

}

#if ((TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON) || (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON))
/**********************************************************************************************************************
 *  TcpIp_Tcp_VHandleTcpOptions_SetBlockedOptLen
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VHandleTcpOptions_SetBlockedOptLen(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /* timestamp option and SACK option both have to be negotiated during the handshake within the same message */

  uint8 blockedOptLen = 0;

  /* #10 Check if we are in the a connection state bigger than SynRcvd */
  if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) < TCPIP_TCP_SOCK_STATE_SYNRCVD)
  {
    /* #20 Add the needed length per option */
# if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
    if (TcpIp_IsTimestampOptActiveOfSocketTcpTsOptDyn(SocketTcpIdx) == TRUE)
    {
      blockedOptLen = (TCPIP_TCP_OPT_LEN_TIMESTAMP + 2u);  /* including 2* NOP */
    }
# endif
# if (TCPIP_SUPPORT_TCP_SELECTIVE_ACK == STD_ON)
    if (TcpIp_IsSackOptActiveOfSocketTcpDyn(SocketTcpIdx) == TRUE)
    {
      blockedOptLen = TCPIP_TCP_HDR_OPT_LEN_MAX_BYTE;  /* maximum TCP option length */ /* overwrite len set for timestamp option */
    }
# endif

    if (blockedOptLen > 0u)
    {
      /* #30 Set the new maximum segment length */
      TcpIp_SetTxOptLenOfSocketTcpDyn(SocketTcpIdx, blockedOptLen);                                                     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      if ((blockedOptLen + TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx)) > TcpIp_GetTxMssOfTcpConfig(TCPIP_TCPCONFIG_IDX))
      {
        TcpIp_SetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetTxMssOfTcpConfig(TCPIP_TCPCONFIG_IDX) - blockedOptLen));  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
    }
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/**********************************************************************************************************************
 *  TcpIp_Tcp_VAddrResTimeout
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_VAddrResTimeout(
  TCPIP_P2C(TcpIp_SockAddrBaseType) DestAddrPtr)
{
  TcpIp_SizeOfSocketTcpDynType socketTcpIdx;
  TcpIp_SizeOfSocketDynType    socketIdx;

  CANOE_WRITE_STRING_1("TcpIp_Tcp_VAddrResTimeout: function called, AddrType = %d", DestAddrPtr->sa_family);

  /* #10 Check the socket state of all sockets */
  for (socketTcpIdx = 0; socketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn(); socketTcpIdx++)
  {
    socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(socketTcpIdx);

    if (   (TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) != TCPIP_TCP_SOCK_STATE_CLOSED)                             /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) != TCPIP_TCP_SOCK_STATE_LISTEN))
    {
      /* #20 Check the addr to find out if the socket is affected by the address resolution timeout, then stop the retry
         mechanism on the socket and indicate an error to the user. */
      if (TcpIp_VSockIpAddrIsEqual(DestAddrPtr, TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)) == TRUE)                    /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_RemoteAddressAvailable */
      {
        /* addr request timeout for this socket occured */

        CANOE_WRITE_STRING_1("TcpIp_Tcp_VAddrResTimeout: Addr match on socket %d", socketIdx);

        /* issue a RESET to the user and close tcp socket */
        TcpIp_Tcp_VCloseSocketAndReleaseResources(socketTcpIdx, TCPIP_TCP_STATE_RESET);
      }
    }
  }

  TCPIP_VENTER_CRITICAL_SECTION();

  /* #30 Remove elements from the reset queue if they are affected by the address resolution timeout. */
  if (0u < TcpIp_Tcp_RstTxQueueFillNum)
  {
    uint8_least rstTxQueueReadPos = TcpIp_Tcp_RstTxQueueReadPos;
    uint8_least rstTxQueueIdx;

    for (rstTxQueueIdx = 0; rstTxQueueIdx < TcpIp_Tcp_RstTxQueueFillNum; rstTxQueueIdx++)
    {
      TCPIP_P2V(TcpIp_SockAddrBaseType) remSockAddrPtr = &TcpIp_GetAddrTcpResetQElement(rstTxQueueReadPos)->RemSock;

      if (TcpIp_VSockIpAddrIsEqual(DestAddrPtr, remSockAddrPtr) == TRUE)                                                /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PointerDerivedFromValidResetQEleIdx */
      {
        /* mark entry in reset queue as invalid. This entry will be removed in TcpIp_Tcp_VTransmitResets() */
        remSockAddrPtr->sa_family = IPBASE_AF_UNSPEC;                                                                   /* SBSW_TCPIP_PWA_PointerDerivedFromValidResetQEleIdx */
      }

      TcpIp_Tcp_IncTxRstQueueIdx(rstTxQueueReadPos);
    }
  }

  TCPIP_VLEAVE_CRITICAL_SECTION();
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VFreeFirstRetrQueueEle
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VFreeFirstRetrQueueEle(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  TcpIp_SizeOfTcpRetryQElementType sockOldFirstEleIdx;  /* element that shall be removed / moved to free-list */
  TcpIp_SizeOfTcpRetryQElementType globNewLastFreeEleIdx;

  sockOldFirstEleIdx     = TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx);
  globNewLastFreeEleIdx  = sockOldFirstEleIdx;

  /* #10 Remove element from the socket's RetrQueue */
  if (TcpIp_GetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx) > 1u)
  {
    /* there is at least one element left in the socket's RetrQueue */
    TcpIp_SizeOfTcpRetryQElementType sockNewFirstEleIdx = TcpIp_GetAddrTcpRetryQElement(sockOldFirstEleIdx)->EleNext;

    TcpIp_SetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx, sockNewFirstEleIdx);                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_GetAddrTcpRetryQElement(sockNewFirstEleIdx)->ElePrev = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;                     /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    TcpIp_DecRetryQFillNumOfSocketTcpDyn(SocketTcpIdx);                                                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else
  {
    /* the socket's RetrQueue will be empty afterwards */

    TcpIp_SetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV);                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetTcpRetryQElementLastIdxOfSocketTcpDyn( SocketTcpIdx, TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV);                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx, 0);                                                              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }

  /* #20 Append the element to the free-list */
  if (TcpIp_Tcp_NumFreeRetryQEle > 0u)
  {
    TcpIp_SizeOfTcpRetryQElementType globOldLastFreeEleIdx = TcpIp_Tcp_LastFreeRetrQueueEle;
    /* there are some (at least one) elements in the free-list */

    /* link last element of the free-list with the (old) first element of the socket's RetrQueue */
    TcpIp_GetAddrTcpRetryQElement(globNewLastFreeEleIdx)->ElePrev = globOldLastFreeEleIdx;                              /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    TcpIp_GetAddrTcpRetryQElement(globOldLastFreeEleIdx)->EleNext = globNewLastFreeEleIdx;                              /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */

    /* mark the element of the socket's RetrQueue that shall be removed as the global last element of the free elements list */
    TcpIp_Tcp_LastFreeRetrQueueEle = globNewLastFreeEleIdx;
    TcpIp_GetAddrTcpRetryQElement(globNewLastFreeEleIdx)->EleNext = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;                  /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
  }
  else
  {
    /* the free-list is empty, so fill in the first element */

    /* set neighbor element indices to invalid */
    TcpIp_GetAddrTcpRetryQElement(globNewLastFreeEleIdx)->ElePrev = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;                  /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    TcpIp_GetAddrTcpRetryQElement(globNewLastFreeEleIdx)->EleNext = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;                  /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */

    /* mark the element as the global last and first element of the free elements list */
    TcpIp_Tcp_FirstFreeRetrQueueEle = globNewLastFreeEleIdx;
    TcpIp_Tcp_LastFreeRetrQueueEle  = globNewLastFreeEleIdx;
  }
  TcpIp_Tcp_NumFreeRetryQEle++;  /* inc free elements counter */
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VFreeAckedReqAndRetrElements
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VFreeAckedReqAndRetrElements(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint32 SegAckNo)
{
  boolean checkIfFirstSegInQueueIsAcked = TRUE;
  TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  /* #10 Repeat removing first segment from TX Retry Queue if queue is not empty or a not fully ACKed segment has been found before. */
  while (checkIfFirstSegInQueueIsAcked == TRUE)
  {
    uint32 acknowledgedPayloadBytes = 0;

    /* #20 Enter critical section to protect retry queue access. */
    TCPIP_VENTER_CRITICAL_SECTION();

    /* #30 Check first segment in retry queue or abort operation if queue is empty. */
    if (TcpIp_GetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx) > 0u)
    {
      TCPIP_P2C(TcpIp_Tcp_TxRetrQueueType) TxRetrQueueElePtr = TcpIp_GetAddrTcpRetryQElement(TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx));

      /* #40 Calculate sequence number of the following segment. */
      uint32 nextSegSeqNo = TxRetrQueueElePtr->SeqNo + TxRetrQueueElePtr->SizeTotByte;

      if ((TxRetrQueueElePtr->Flags & TCPIP_TCP_CODE_BIT_SYN) != 0u)
      {
        /* SYN flag counts as one byte. */
        nextSegSeqNo++;
      }

      if ((TxRetrQueueElePtr->Flags & TCPIP_TCP_CODE_BIT_FIN) != 0u)
      {
        /* FIN flag counts as one byte. */
        nextSegSeqNo++;
      }

      /* #50 Check if segment is completely acknowledged. */
      if (TCPIP_TCP_SEQ1_BIGGER_OR_EQUAL_SEQ2(SegAckNo, nextSegSeqNo))
      {
        /* #60 Remove acknowledged length from TX request element for this socket and store acknowledged payload length for call to TxConfirmation. */
        acknowledgedPayloadBytes = TxRetrQueueElePtr->SizeTotByte;

        if (acknowledgedPayloadBytes > 0u)
        {
          /* Remove acknowledged length from TX request element for this socket. */
          TCPIP_ASSERT(TcpIp_GetTxReqDataLenByteOfSocketTcpDyn(SocketTcpIdx) >= acknowledgedPayloadBytes);
          TcpIp_SetTxReqDataLenByteOfSocketTcpDyn(SocketTcpIdx,                                                         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
            (TcpIp_GetTxReqDataLenByteOfSocketTcpDyn(SocketTcpIdx) - (TcpIp_SizeOfTcpTxBufferType)acknowledgedPayloadBytes));  /* cast OK: acknowledged len is never bigger than the buffer */
          TCPIP_ASSERT(TcpIp_GetTxReqQueuedLenOfSocketTcpDyn(SocketTcpIdx) >= acknowledgedPayloadBytes);
          TcpIp_SetTxReqQueuedLenOfSocketTcpDyn(SocketTcpIdx,                                                           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
            (TcpIp_GetTxReqQueuedLenOfSocketTcpDyn(SocketTcpIdx) - (TcpIp_SizeOfTcpTxBufferType)acknowledgedPayloadBytes));  /* cast OK: acknowledged len is never bigger than the buffer */
          {
            TcpIp_SizeOfTcpTxBufferType currentIndex = TcpIp_GetTxReqDataBufStartIdxOfSocketTcpDyn(SocketTcpIdx);
            currentIndex = TcpIp_IncTxBufIdx(TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx), currentIndex,
              (TcpIp_SizeOfTcpTxBufferType)acknowledgedPayloadBytes);

            TcpIp_SetTxReqDataBufStartIdxOfSocketTcpDyn(SocketTcpIdx, currentIndex);                                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
          }
        }

        TcpIp_Tcp_VFreeFirstRetrQueueEle(SocketTcpIdx);
      }
      else
      {
        /* #70 ELSE: Stop searching for further segments. If this segment is not ACKed others with higher sequence numbers will not be ACKed as well. */
        checkIfFirstSegInQueueIsAcked = FALSE;
      }
    }
    else
    {
      /* Tx Retry Queue is empty. All segments are acknowledged. Stop searching for further segments. */
      checkIfFirstSegInQueueIsAcked = FALSE;
    }

    /* #80 Leave critical section because upper layer is called next. */
    TCPIP_VLEAVE_CRITICAL_SECTION();

    /* #90 Call TxConfirmation of upper layer if segment contained acknowledged payload bytes. */
    if (acknowledgedPayloadBytes > 0u)
    {
      TcpIp_VSockTxConfirmation(socketIdx, acknowledgedPayloadBytes);
    }
  }

/* (end) remove segments from tx (retransmission) queue */
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VQueueRemReqData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VQueueRemReqData(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /* #10 Check if there are free elements in the retry queue. */
  if (TcpIp_Tcp_NumFreeRetryQEle > 0u)
  {
    /* Add (part of) request to TxReqArray */
    TcpIp_SizeOfTcpTxBufferType remaniningSize;  /* size of data not yet queued in the TxRetrQueue */

    remaniningSize = TcpIp_GetTxReqDataLenByteOfSocketTcpDyn(SocketTcpIdx) - TcpIp_GetTxReqQueuedLenOfSocketTcpDyn(SocketTcpIdx);

    /* #20 Append new fully filled segments into the retry queue (if possible). */

    /* inc TxLen, or fill retry queue elements */
    while (   (TcpIp_Tcp_NumFreeRetryQEle > 0u)                                                                          /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
           && (remaniningSize >= TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx)))
    {
      /* add max size segment, and send */
      remaniningSize                -= TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx);
      TcpIp_SetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx));           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      (void)TcpIp_Tcp_VFinalizeTxSegment(SocketTcpIdx);
    }

    /* #30 Plan partially filled segment that will only be appended to the retry queue if nagle allows it. */

    if ((TcpIp_Tcp_NumFreeRetryQEle > 0u) && (remaniningSize > 0u))
    {
      if (TcpIp_GetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx) == 0u)
      {
        /* new RetrQueue element is needed */

#if (TCPIP_SUPPORT_TCP_NAGLE_TIMEOUT == STD_ON)
        /* set nagle algorithm timeout */
        if (TcpIp_IsEnabledOfSocketTcpNagleDyn(SocketTcpIdx) == TRUE)
        {
          TCPIP_ASSERT(TcpIp_HasSocketTcpNagleDyn() == TRUE);
          TcpIp_SetTimeoutOfSocketTcpNagleDyn(SocketTcpIdx, TcpIp_GetNagleTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX));     /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        }
        else
#endif
        {
          /* send new element even though it is not full */
          TcpIp_SetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx, remaniningSize);                                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

          if (TcpIp_Tcp_VFinalizeTxSegment(SocketTcpIdx) == E_OK)
          {
            remaniningSize = 0;
          }
        }
      }
      else
      {
        /* do nothing, this data will be part of a message that will be sent later */
      }
      /* add remaining size segment */
      TcpIp_SetTxLenByteTxOfSocketTcpDyn(SocketTcpIdx, remaniningSize);                                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      TcpIp_SetTxReqFullyQueuedOfSocketTcpDyn(SocketTcpIdx, TRUE);                                                      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
  }
}  /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VDropEndEleInRetrQueue
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VDropEndEleInRetrQueue(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  uint8 NumDropEle)
{
  /* #10 Check that elements shall be dropped */
  if (NumDropEle == 0u)
  {
    /* No element shall be dropped, so just return. */
  }
  else
  {
    TcpIp_SizeOfTcpRetryQElementType oldLastRetrQueueEleIdx;   /* last element of the socket's retry queue before removing some elements of this queue */
    TcpIp_SizeOfTcpRetryQElementType firstRemRetrQueueEleIdx;  /* first element of the socket's retry queue that shall be removed */
    TcpIp_SizeOfTcpRetryQElementType newLastRetrQueueEleIdx;
    TcpIp_SizeOfTcpTxBufferType      remLen;
    uint8                            lastElementFlags;

    TCPIP_VENTER_CRITICAL_SECTION();

    /* TcpIp_Tcp_VDropEndEleInRetrQueue is always invoked with NumDropEle <= TcpIp_GetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx) */
    TCPIP_ASSERT(NumDropEle <= TcpIp_GetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx));

    oldLastRetrQueueEleIdx  = TcpIp_GetTcpRetryQElementLastIdxOfSocketTcpDyn(SocketTcpIdx);
    firstRemRetrQueueEleIdx = TcpIp_GetTcpRetryQElementLastIdxOfSocketTcpDyn(SocketTcpIdx);
    newLastRetrQueueEleIdx  = TcpIp_GetAddrTcpRetryQElement(oldLastRetrQueueEleIdx)->ElePrev;
    remLen                  = TcpIp_GetAddrTcpRetryQElement(oldLastRetrQueueEleIdx)->SizeTotByte;
    lastElementFlags        = TcpIp_GetAddrTcpRetryQElement(oldLastRetrQueueEleIdx)->Flags;

    /* #20 Remove elements from the sockets retry queue */
    {
      uint8 numElementsRemoved = 1;

      /* Iterate backwards through the socket's retry queue to find the first element that shall be removed. */
      while (numElementsRemoved < NumDropEle)
      {
        /* get index of next removed element */
        firstRemRetrQueueEleIdx = newLastRetrQueueEleIdx;
        remLen += TcpIp_GetAddrTcpRetryQElement(newLastRetrQueueEleIdx)->SizeTotByte;
        /* Set the new last queue index. Index finally is 'invalid' index when all element are removed from the socket's queue. */
        newLastRetrQueueEleIdx  = TcpIp_GetAddrTcpRetryQElement(newLastRetrQueueEleIdx)->ElePrev;
        numElementsRemoved++;
      }

      /* Set index of socket's last element, set next index of the new last element to 'invalid' and reduce retry queue fill num. */
      TcpIp_SetTcpRetryQElementLastIdxOfSocketTcpDyn(SocketTcpIdx, newLastRetrQueueEleIdx);                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      if (NumDropEle < TcpIp_GetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx))
      {
        TcpIp_GetAddrTcpRetryQElement(newLastRetrQueueEleIdx)->EleNext  = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;            /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */

        TcpIp_SetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx) - NumDropEle)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
      else
      {
        TcpIp_SetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx, 0);                                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
    }


    /* #30 Append removed elements to the global list of free elements, or use the removed elements as the new global free elements list if there have not been free elements before. */
    if (TcpIp_Tcp_NumFreeRetryQEle == 0u)
    {
      /* FreeList has been empty */
      TcpIp_Tcp_FirstFreeRetrQueueEle    = firstRemRetrQueueEleIdx;

      /* Set predecessor of the first queue element to 'invalid'. */
      TcpIp_GetAddrTcpRetryQElement(firstRemRetrQueueEleIdx)->ElePrev = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;              /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    }
    else
    {
      /* Link the first element of the queue part that shall be appended with the old last element of the free list. */
      TcpIp_GetAddrTcpRetryQElement(TcpIp_Tcp_LastFreeRetrQueueEle)->EleNext = firstRemRetrQueueEleIdx;                 /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
      TcpIp_GetAddrTcpRetryQElement(firstRemRetrQueueEleIdx       )->ElePrev = TcpIp_Tcp_LastFreeRetrQueueEle;          /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */

    }

    /* Set successor of the last queue element to 'invalid', and increase the number of free elements. */
    TcpIp_Tcp_LastFreeRetrQueueEle     = oldLastRetrQueueEleIdx;
    TcpIp_Tcp_NumFreeRetryQEle        += NumDropEle;

    /* #40 Call function to un-queue the removed len 'remLen' */
    /* Set the FIN flag for later transmission if the flag was set in the last queue element that has been dropped. */
    if((lastElementFlags & TCPIP_TCP_CODE_BIT_FIN) != 0u)
    {
      /* trigger FIN */
      TcpIp_DecTxNextSendSeqNoOfSocketTcpDyn(SocketTcpIdx);                                                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_Tcp_VSendFlags(SocketTcpIdx, (TCPIP_TCP_CODE_BIT_FIN | TCPIP_TCP_CODE_BIT_ACK));
    }
    TcpIp_Tcp_VUnqueueDataInTxReq(SocketTcpIdx, remLen);

    TCPIP_VLEAVE_CRITICAL_SECTION();
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VUnqueueDataInTxReq
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VUnqueueDataInTxReq(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  TcpIp_SizeOfTcpTxBufferType UnqueueLen)
{
  TcpIp_SizeOfTcpTxBufferType lengthToBeUnqueued;

  /* #10 Limit the amount of data that shall be un-queued to the currently queued length. */
  if (UnqueueLen > TcpIp_GetTxReqQueuedLenOfSocketTcpDyn(SocketTcpIdx))
  {
    lengthToBeUnqueued = TcpIp_GetTxReqQueuedLenOfSocketTcpDyn(SocketTcpIdx);
  }
  else
  {
    lengthToBeUnqueued = UnqueueLen;
  }

  /* #20 Check that the length to remove is not 0. */
  if (lengthToBeUnqueued > 0u)
  {
    /* #30 Move lengthToBeUnqueued from TxReqQueuedLen to TxTotNotQueuedLen. */
    TcpIp_SetTxReqQueuedLenOfSocketTcpDyn(   SocketTcpIdx, (TcpIp_GetTxReqQueuedLenOfSocketTcpDyn(SocketTcpIdx)    - lengthToBeUnqueued)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetTxTotNotQueuedLenOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetTxTotNotQueuedLenOfSocketTcpDyn(SocketTcpIdx) + lengthToBeUnqueued)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetTxReqFullyQueuedOfSocketTcpDyn(SocketTcpIdx, FALSE);                                                       /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

    /* #40 Set next send sequence number. */
    TcpIp_SetTxNextSendSeqNoOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetTxNextSendSeqNoOfSocketTcpDyn(SocketTcpIdx) - lengthToBeUnqueued)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainStateHandling
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainStateHandling(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /* #10 Handle received RST */
  TcpIp_Tcp_VMainStateHandling_Reset(SocketTcpIdx);

  /* #20 Check if a state change is triggered. */
  if (TcpIp_GetSockStateNextOfSocketTcpDyn(SocketTcpIdx) != TCPIP_TCP_SOCK_STATE_INVALID)
  {
    TcpIp_SockStateOfSocketTcpDynType copyOfSockState = TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx);

    /* #30 Proceed the state handling dependent on the requested state. */
    switch (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx))
    {
    case TCPIP_TCP_SOCK_STATE_SYNSENT:
    case TCPIP_TCP_SOCK_STATE_SYNRCVD:
    /* case TCPIP_TCP_SOCK_STATE_ESTABLISHED: STORYC-6890 This state is not reachable since Next Socket state is always INVALID for state Established */
    case TCPIP_TCP_SOCK_STATE_LASTACK:
    case TCPIP_TCP_SOCK_STATE_FINWAIT1:
    case TCPIP_TCP_SOCK_STATE_CLOSING:
      {
        /* #40 Trigger sending if something to send is available */
        if (TcpIp_Tcp_VFinalizeTxSegment(SocketTcpIdx) == E_OK)
        {
          TCPIP_VENTER_CRITICAL_SECTION();  /* lock interrupts */
          /* Check if SockState has changed. This would mean that this function has been interrupted and the state has
          been changed in the interrupting context. */
          if (copyOfSockState == TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx))
          {
            /* #50 Message transmission succeeded, so switch to the next socket state. */
            TcpIp_SetSockStateOfSocketTcpDyn(SocketTcpIdx, TcpIp_GetSockStateNextOfSocketTcpDyn(SocketTcpIdx));         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
            TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_INVALID);                           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
          }
          else
          {
            /* This function was interrupted. Don't overwrite the SockState that was set in the interrupting context. */
          }
          TCPIP_VLEAVE_CRITICAL_SECTION();  /* unlock interrupts */
        }
        break;
      }
    case TCPIP_TCP_SOCK_STATE_TIMEWAIT:
    {
      TcpIp_Tcp_VMainStateHandling_Timewait(SocketTcpIdx);
      break;
    }
    case TCPIP_TCP_SOCK_STATE_CLOSEWAIT:
    {
      if (TcpIp_GetTxFlagsOfSocketTcpDyn(SocketTcpIdx) == 0u)
      {
        /* The ACK that was triggered when receiving the FIN is sent, so StateNext can be reset */
        TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_INVALID);                               /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
      break;
    }
    default:
      {
        /* TCPIP_TCP_SOCK_STATE_INVALID,
           TCPIP_TCP_SOCK_STATE_LISTEN,
           TCPIP_TCP_SOCK_STATE_FINWAIT2,
           TCPIP_TCP_SOCK_STATE_CLOSED:
           -> do nothing */
      }
      break;
    }  /* switch */
  }
}  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */



/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainStateHandling_Reset
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainStateHandling_Reset(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /* #10 Handle received RST */
  if (TcpIp_IsRstReceivedOfSocketTcpDyn(SocketTcpIdx) == TRUE)
  {
    /* #20 Proceed depended on the socket state */
    switch (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx))
    {
    case TCPIP_TCP_SOCK_STATE_SYNRCVD:
      {
        /* #30 Close the socket */
        if (TcpIp_IsSockIsServerOfSocketTcpDyn(SocketTcpIdx) == TRUE)
        {
          /* opened passively */
          /* connection was reset by peer */

          /* delete/clear this TCB (user has to call Sock_Connect() again later): */
          TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_RESET);
        }
        else
        {
          /* opened actively */
          /* connection was refused -> signal to the user 'connection refused' */
          TcpIp_SetLastSockError(TCPIP_SOCK_ERR_10061);  /* 'connection refused' */

          /* delete/clear this TCB (user has to call Sock_Connect() again later): */
          TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_CONN_REFUSED);
        }
        break;
      }
    case TCPIP_TCP_SOCK_STATE_ESTABLISHED:
    case TCPIP_TCP_SOCK_STATE_FINWAIT1:
    case TCPIP_TCP_SOCK_STATE_FINWAIT2:
    case TCPIP_TCP_SOCK_STATE_CLOSEWAIT:
      {
        /* #40 Close the socket */
        /* If the RST bit is set then, any outstanding RECEIVEs and SEND should receive 'reset'
        responses. All segment queues should be flushed. Users should also receive an
        unsolicited general 'connection reset' signal. Enter the CLOSED state, delete the TCB,
        and return. */
        /* cancel all send and receive calls
        -> nothing to be done for AUTOSAR API */

        /* remove all elements from tx-queue and rx-queue */
        /* enter CLOSED state, delete/clear TCB */
        TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_RESET);

        TcpIp_SetLastSockError(TCPIP_SOCK_ERR_10054);  /* 'Connection reset by peer' */
        break;
      }
    default:
      {
        /* TCPIP_TCP_SOCK_STATE_CLOSING, TCPIP_TCP_SOCK_STATE_LASTACK, TCPIP_TCP_SOCK_STATE_TIMEWAIT */
        /* #50 Close the socket */
        /* enter CLOSED state, delete/clear TCB */
        TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_CLOSED);
        break;
      }
    }
  }
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainStateHandling_Timewait
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainStateHandling_Timewait(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /* #10 State handling dependent on the next socket state */
  if (TcpIp_GetSockStateNextOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_TIMEWAIT)
  {
    /* #20 Trigger sending of final ACK if next socket state is TIMEWAIT */
    if (TcpIp_Tcp_VFinalizeTxSegment(SocketTcpIdx) == E_OK)
    {
      TcpIp_SetSockStateNextOfSocketTcpDyn(SocketTcpIdx, TCPIP_TCP_SOCK_STATE_CLOSED);                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
      TcpIp_Tcp_VKeepAliveReset(SocketTcpIdx);
#endif
    }
  }

  if (TcpIp_GetSockStateNextOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_CLOSED)
  {
    /* #30 If the next socket state is CLOSED, decrease Timeout timer (MSL) or finally close the socket */
    if (   (TcpIp_GetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx) == 0u)                                                    /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TcpIp_GetTxFlagsOfSocketTcpDyn(SocketTcpIdx) == 0u))  /* wait for the last ACK to be sent / removed from tx queue */
    {
      /* #40 Decrease Timeout timer (MSL) */
      if (TcpIp_GetMslTimeoutOfSocketTcpDyn(SocketTcpIdx) > 0u)
      {
        TcpIp_DecMslTimeoutOfSocketTcpDyn(SocketTcpIdx);                                                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
      else /* (Tcp_MslTimeout == 0), timeout expired */
      {
        /* #50 Close the socket because the timeout has expired */

        /* switch to state CLOSED, delete/clear TCB element */
        TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_CLOSED);
      }
    }
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainRxDataForwarding
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainRxDataForwarding(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint16 MaxLenToForward)
{
  TcpIp_SizeOfTcpRxBufferDescType tcpRxBufferDescIdx = TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx);
  uint16 remainingLengthAtEndOfBuffer;
  TCPIP_P2V(uint8) locBufPtr;        /* pointer to the start of the received data in the rx buffer */

  TCPIP_ASSERT(tcpRxBufferDescIdx                                  <  TcpIp_GetSizeOfTcpRxBufferDesc());
  TCPIP_ASSERT(MaxLenToForward                                     <= TcpIp_GetRxBufferRemIndLenOfSocketTcpDyn(SocketTcpIdx));
  TCPIP_ASSERT(TcpIp_GetRxBufferIndPosOfSocketTcpDyn(SocketTcpIdx) <  TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(tcpRxBufferDescIdx));

  /* Caching of 'MaxLenToForward' is required because 'RxBufferRemIndLenOfSocketTcpDyn' may be updated before the second
  critical section below. */
  /* #10 Get the start position of the data that shall be forwarded. */

  TCPIP_VENTER_CRITICAL_SECTION();  /* lock interrupts */

  remainingLengthAtEndOfBuffer = (uint16)(TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(tcpRxBufferDescIdx) - TcpIp_GetRxBufferIndPosOfSocketTcpDyn(SocketTcpIdx));
  locBufPtr = TcpIp_GetAddrTcpRxBuffer(
    TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(tcpRxBufferDescIdx) +
    TcpIp_GetRxBufferIndPosOfSocketTcpDyn(SocketTcpIdx));

  /* #20 Forward the data to the socket owner. */
  if (remainingLengthAtEndOfBuffer >= MaxLenToForward)
  {
    /* Data is in a linear buffer. */
    /* indicate bytes 0..((TCPIP_TCP_MAX_WINDOW_SIZE - Tcp_RxBufferWritePos[SocketTcpIdx]) - 1) */

    TCPIP_VLEAVE_CRITICAL_SECTION();  /* unlock interrupts */

    TcpIp_Tcp_UpRxIndication(SocketTcpIdx, locBufPtr, MaxLenToForward);                                                 /* SBSW_TCPIP_FC_RxBufferPtr_1 */
  }
  else
  {
    /* data buffer includes wrap around */
    /* indicate data with taking care of buffer wrap-around (two blocks) */

    TCPIP_P2V(uint8) locBufSecondPtr;  /* pointer to the start of the rx buffer in case the received data causes a buffer wrap around */
    locBufSecondPtr = TcpIp_GetAddrTcpRxBuffer(TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(tcpRxBufferDescIdx));

    TCPIP_VLEAVE_CRITICAL_SECTION();  /* unlock interrupts */

    /* indicate bytes 0..((TCPIP_TCP_MAX_WINDOW_SIZE - TcpIp_GetRxBufferIndPosOfSocketTcpDyn(SocketTcpIdx)) - 1) */
    TcpIp_Tcp_UpRxIndication(SocketTcpIdx, locBufPtr, remainingLengthAtEndOfBuffer);                                    /* SBSW_TCPIP_FC_RxBufferPtr_2 */

    /* indicate remaining bytes */
    TcpIp_Tcp_UpRxIndication(SocketTcpIdx, locBufSecondPtr, MaxLenToForward - remainingLengthAtEndOfBuffer);            /* SBSW_TCPIP_FC_RxBufferPtr_2 */
  }

  TCPIP_VENTER_CRITICAL_SECTION();  /* lock interrupts */

  /* #30 Increase the buffer start position, taking care of the wraparound. Check if socket was not reset in the meantime. */
  if (TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx) < TcpIp_GetSizeOfTcpRxBufferDesc())
  {
    TcpIp_SetRxBufferIndPosOfSocketTcpDyn(SocketTcpIdx, (TcpIp_SizeOfTcpRxBufferType)TcpIp_AddWithWrapAround32(         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_GetRxBufferIndPosOfSocketTcpDyn(SocketTcpIdx), MaxLenToForward,
      TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(tcpRxBufferDescIdx)));

    TcpIp_SetRxBufferRemIndLenOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetRxBufferRemIndLenOfSocketTcpDyn(SocketTcpIdx) - MaxLenToForward)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }

  TCPIP_VLEAVE_CRITICAL_SECTION();  /* unlock interrupts */
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainIdleTimeoutHandling
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainIdleTimeoutHandling(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
  /* #10 Check if TCP Keep-Alive is enabled for the socket. */
  if (   (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_ESTABLISHED)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_IsEnabledOfSocketTcpKeepAliveDyn(SocketTcpIdx) == TRUE))
  {
    /* Keep-alive is enabled for this connection. */
    uint32 keepAliveIdleTimeMax;

    /* #20 Check if timeout for first keep-alive segment or consecutive keep-alive segment has to be applied. */
    if (TcpIp_GetProbesOfSocketTcpKeepAliveDyn(SocketTcpIdx) == 0u)
    {
      /* No keep-alive probes sent so far. Wait for keep-alive timeout. */
      keepAliveIdleTimeMax = TcpIp_GetTimeoutOfSocketTcpKeepAliveDyn(SocketTcpIdx);
    }
    else
    {
      /* Keep-Alive timeout already expired and at least one probe has been sent. Wait for next probe interval. */
      keepAliveIdleTimeMax = TcpIp_GetProbeIntervalOfSocketTcpKeepAliveDyn(SocketTcpIdx);
    }

    /* #30 Increment idle time counter for the socket if timeout has not expired yet. */
    if (TcpIp_GetIdleTimeOfSocketTcpKeepAliveDyn(SocketTcpIdx) < keepAliveIdleTimeMax)
    {
      /* Timeout has not expired yet. */
      TcpIp_IncIdleTimeOfSocketTcpKeepAliveDyn(SocketTcpIdx);                                                           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
    /* #40 ELSE: Send keep-alive segment and reset idle time or close connection if configured number of keep-alive segments have been sent. */
    else
    {
      if (TcpIp_GetProbesOfSocketTcpKeepAliveDyn(SocketTcpIdx) < TcpIp_GetProbesMaxOfSocketTcpKeepAliveDyn(SocketTcpIdx))
      {
        if (TcpIp_Tcp_VTransmitKeepAliveProbe(SocketTcpIdx) == E_OK)
        {
          /* Reset idle time and wait for next timeout. */
          TcpIp_SetIdleTimeOfSocketTcpKeepAliveDyn(SocketTcpIdx, 0);                                                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
          TcpIp_IncProbesOfSocketTcpKeepAliveDyn(SocketTcpIdx);                                                         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        }
      }
      else
      {
        /* Maximum number of keep-alive probes have been sent and were not answered. Close connection. */

        TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

        /* timeout expired -> close / reset connection */
        /* sending a reset is an extension, there is no need for that according to the RFC */
        TcpIp_Tcp_VSendReset(SocketTcpIdx, TcpIp_GetTxIpAddrIdxOfSocketDyn(socketIdx),                                  /* SBSW_TCPIP_FC_RemoteAddressAvailable */ /* SBSW_TCPIP_FC_LocalAddressAvailable */
          (TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)), (TcpIp_GetAddrLocSockOfSocketDyn(socketIdx)),
          TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx), 0u, 0u);  /* seqNo, ackNo */

        /* flush all queues, signal the user 'error: connection aborted due to idle timeout' in
        general and for any outstanding calls, delete the TCB, enter the CLOSED state and
        return. */
        /* delete/clear TCB element */
        TcpIp_Tcp_VCloseSocketAndReleaseResources(SocketTcpIdx, TCPIP_TCP_STATE_RESET);
      }
    }
  }
#endif

  /* -------------------------------------------------------------------------------------------- */
  /* Handle Tcp_IdleTimeoutShort[] --------------------------------------------------------- */

  /* #50 Check if idle timeout for congestion window reset and zero window probe has been reached. */
  if (TcpIp_GetIdleTimeoutShortOfSocketTcpDyn(SocketTcpIdx) > 0u)
  {
    TcpIp_DecIdleTimeoutShortOfSocketTcpDyn(SocketTcpIdx);                                                              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    if (TcpIp_GetIdleTimeoutShortOfSocketTcpDyn(SocketTcpIdx) == 0u)
    {
      /* timeout has expired */

#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
      {
        /* reset the congestion window because the connection has been idle for too long */
        /* cwnd = RW = min(IW,cwnd) */
        uint32 iw = ((uint32) TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx) * TCPIP_TCP_DEFAULT_SEGMENT_LIMIT(TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx)));

        if (iw < TcpIp_GetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx))
        {
          TcpIp_SetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx, iw);                                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
        }

        TcpIp_SetCongestionControlModeOfSocketTcpCongCtrlDyn(SocketTcpIdx, TCPIP_TCP_CONG_CTRL_MODE_SLOW_START);        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
#endif

      /* Check if the socket has elements in its retry queue */
      if (TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx) < TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV)
      {
        /* handle Zero Window Probing or splitting of the first segment */
        TcpIp_Tcp_VSplitFirstRetrQueueEle(SocketTcpIdx);
      }
    }
  }

  /* #60 Handle FINWAIT-2 timeout */
  TcpIp_Tcp_VFinWait2TimeoutHandling(SocketTcpIdx);
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  TcpIp_Tcp_VFinWait2TimeoutHandling
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VFinWait2TimeoutHandling(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /* #10 Check if socket is in FINWAIT-2 state and whether FINWAIT-2 timeout has expired */
  if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_SOCK_STATE_FINWAIT2)
  {
    /* #20 Check if FINWAIT-2 timeout timer is running */
    if (TcpIp_GetFinWait2TimeoutOfSocketTcpDyn(SocketTcpIdx) > 0u)
    {
      /* #30 Update the FINWAIT-2 timeout */
      TcpIp_DecFinWait2TimeoutOfSocketTcpDyn(SocketTcpIdx);                                                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

      /* #40 Check If timeout has expired now */
      if (TcpIp_GetFinWait2TimeoutOfSocketTcpDyn(SocketTcpIdx) == 0u)
      {
        /* #50 FINWAIT-2 timeout expired and no FIN was received from remote peer. Abort connection. */
        TcpIp_Tcp_Abort(SocketTcpIdx);
      }
    }
  }
} /* TcpIp_Tcp_VFinWait2TimeoutHandling() */

/**********************************************************************************************************************
 *  TcpIp_Tcp_VSplitFirstRetrQueueEle
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSplitFirstRetrQueueEle(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  TCPIP_P2C(TcpIp_Tcp_TxRetrQueueType) firstQueueElePtr = TcpIp_GetAddrTcpRetryQElement(TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx));
  uint32 segLen  = firstQueueElePtr->SizeTotByte;
  uint16 winSize = TcpIp_GetSndWndOfSocketTcpDyn(SocketTcpIdx);
  /* #10 Split the first segment. The length of the first segment is never '0' in this situation. */
  if ((segLen > winSize) && (segLen != 1u))
  {
    TcpIp_SizeOfTcpRetryQElementType newEleIdx;
    uint16 sizePartOne;

    /* #20 Determine the size of the new first segment */
    if (winSize == 0u)
    {
      /* split 1 byte from the first segment */
      sizePartOne = 1;
    }
    else  /* (seglen > windowsize) */
    {
      /* The segment length of the first queue element is bigger than the current window size. */
      /* split a window-sized segment from the first queue element */
      sizePartOne = winSize;
    }

    TCPIP_VENTER_CRITICAL_SECTION();

    /* #30 check if a free retry queue element for the splitted segment is available, otherwise relaese the last retry
           queue element of this socket and re-use it for the splitted segment. */
    if (TcpIp_Tcp_NumFreeRetryQEle > 0u)
    {
      /* use one free element */
      newEleIdx = TcpIp_Tcp_FirstFreeRetrQueueEle;
      TcpIp_Tcp_NumFreeRetryQEle--;
      if (TcpIp_Tcp_NumFreeRetryQEle > 0u)
      {
        /* there has been more than one element in the free-list */
        TcpIp_Tcp_FirstFreeRetrQueueEle = TcpIp_GetAddrTcpRetryQElement(newEleIdx)->EleNext;
        TcpIp_GetAddrTcpRetryQElement(TcpIp_Tcp_FirstFreeRetrQueueEle)->ElePrev = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;    /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
      }
      else
      {
        TcpIp_Tcp_FirstFreeRetrQueueEle = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;
        TcpIp_Tcp_LastFreeRetrQueueEle  = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;
      }
    }
    else
    {
      /* one element of the retry queue has to be freed if possible */
      /* handling similar to PathMtu */
      if (TcpIp_GetRetryQFillNumOfSocketTcpDyn(SocketTcpIdx) > 1u)
      {
        /* there is more than one element in the connections retry queue -> drop the last element, and than split the first element in two parts */
        /* drop last retry queue element */
        TcpIp_Tcp_VDropEndEleInRetrQueue(SocketTcpIdx, 1u);
        /* use the one free element */
        newEleIdx = TcpIp_Tcp_FirstFreeRetrQueueEle;
        TcpIp_Tcp_NumFreeRetryQEle = 0;   /* size was '1', so size - 1 = 0 */
        TcpIp_Tcp_FirstFreeRetrQueueEle = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;
        TcpIp_Tcp_LastFreeRetrQueueEle  = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;

        /* splitting the segment / queue element is done in the next step */
      }
      else
      {
        /* there is only one single element in the connections retry queue, and there is no spare one available
        -> reduce the sice of the (first and only) queue element */
        newEleIdx = TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV;
      }
    }

    /* #40 Split the first element (content) into two parts */
    TcpIp_Tcp_VSplitFirstRetrQueueEle_Split(SocketTcpIdx, newEleIdx, sizePartOne);

    TCPIP_VLEAVE_CRITICAL_SECTION();
  }
  else
  {
    /* a) segment is smaller (or equal) than the window size, this should be handled by the normal retransmission mechanism
     * b) segment already has size '1', so no splitting possible. Segment will be sent in normal tx handling
     * -> do nothing
     */
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VSplitFirstRetrQueueEle_Split
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSplitFirstRetrQueueEle_Split(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TcpIp_SizeOfTcpRetryQElementType NewEleIdx,
  uint16 SizePartOne)
{
  if (NewEleIdx < TcpIp_GetSizeOfTcpRetryQElement())
  {
    /* #10 Append the new element to the first element */
    TcpIp_SizeOfTcpRetryQElementType firstEleIdx = TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx);
    TcpIp_Tcp_TxRetrQueueType *newRetryQElementPtr   = TcpIp_GetAddrTcpRetryQElement(NewEleIdx);
    TcpIp_Tcp_TxRetrQueueType *firstRetryQElementPtr = TcpIp_GetAddrTcpRetryQElement(firstEleIdx);

    newRetryQElementPtr->DataBufStartIdx    = firstRetryQElementPtr->DataBufStartIdx + SizePartOne;                     /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->SeqNo              = firstRetryQElementPtr->SeqNo           + SizePartOne;                     /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->SizeTotByte        = firstRetryQElementPtr->SizeTotByte     - SizePartOne;                     /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    firstRetryQElementPtr->SizeTotByte      = SizePartOne;                                                              /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->EleNext            = firstRetryQElementPtr->EleNext;                                           /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->ElePrev            = firstEleIdx;                                                              /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */

    if (firstRetryQElementPtr->EleNext < TcpIp_GetSizeOfTcpRetryQElement())
    {
      TcpIp_GetAddrTcpRetryQElement(firstRetryQElementPtr->EleNext)->ElePrev = NewEleIdx;                               /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    }
    else
    {
      TcpIp_SetTcpRetryQElementLastIdxOfSocketTcpDyn(SocketTcpIdx, NewEleIdx);                                          /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }

    firstRetryQElementPtr->EleNext          = NewEleIdx;                                                                /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    if ((firstRetryQElementPtr->Flags & TCPIP_TCP_CODE_BIT_FIN) != 0u)
    {
      newRetryQElementPtr->Flags            = TCPIP_TCP_CODE_BIT_ACK | TCPIP_TCP_CODE_BIT_PSH | TCPIP_TCP_CODE_BIT_FIN; /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
      firstRetryQElementPtr->Flags          = (uint8)(firstRetryQElementPtr->Flags - (uint8)TCPIP_TCP_CODE_BIT_FIN);    /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    }
    else
    {
      newRetryQElementPtr->Flags            = TCPIP_TCP_CODE_BIT_ACK | TCPIP_TCP_CODE_BIT_PSH;                          /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    }
    newRetryQElementPtr->SocketTcpIdx       = firstRetryQElementPtr->SocketTcpIdx;                                      /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->TimeStamp          = firstRetryQElementPtr->TimeStamp;                                         /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->UserTimeoutTs      = firstRetryQElementPtr->UserTimeoutTs;                                     /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->TransmitCounter    = 0;  /* reset the transmit counter for both parts */                       /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    firstRetryQElementPtr->TransmitCounter  = 0;  /* reset the transmit counter for both parts */                       /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->OneTimeOptions     = 0;  /* one-time options will stay with the first segment */               /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->OneTimeOptionsLen  = 0;                                                                        /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    newRetryQElementPtr->SackFlag           = 0;  /* reset the SACK-flag for both parts */                              /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    firstRetryQElementPtr->SackFlag         = 0;  /* reset the SACK-flag for both parts */                              /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */

    TcpIp_IncRetryQFillNumOfSocketTcpDyn(SocketTcpIdx);                                                                 /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else
  {
    /* #20 No new retry queue element available. So reduce the size of the first (and only) element of the socket's retry queue,
    and un-queue the removed length from the socket's txRequest. */
    TcpIp_Tcp_TxRetrQueueType  *elePtr  = TcpIp_GetAddrTcpRetryQElement(TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx));
    uint8 elementFlags                  = elePtr->Flags;
    TcpIp_SizeOfTcpTxBufferType oldSize = elePtr->SizeTotByte;
    TcpIp_SizeOfTcpTxBufferType newSize = SizePartOne;

    /* Set the FIN flag for later transmission if the flag was set in the current queue element that is shortened. */
    if((elementFlags & TCPIP_TCP_CODE_BIT_FIN) != 0u)
    {
      /* trigger FIN */
      TcpIp_DecTxNextSendSeqNoOfSocketTcpDyn(SocketTcpIdx);                                                             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      TcpIp_Tcp_VSendFlags(SocketTcpIdx, (TCPIP_TCP_CODE_BIT_FIN | TCPIP_TCP_CODE_BIT_ACK));
    }
    TcpIp_Tcp_VUnqueueDataInTxReq(SocketTcpIdx, (oldSize - newSize));

    elePtr->SizeTotByte        = newSize;                                                                               /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    if ((elementFlags & TCPIP_TCP_CODE_BIT_FIN) != 0u)
    {
      elePtr->Flags            = elementFlags - (uint8)TCPIP_TCP_CODE_BIT_FIN;                                          /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    }
    elePtr->TransmitCounter    = 0;  /* reset the transmit counter for both parts */                                    /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
    elePtr->SackFlag           = 0;  /* reset the SACK-flag for both parts */                                           /* SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx */
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainTxDataHandling
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainTxDataHandling(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  boolean continueTx = TRUE;
  /* #10 Trigger sending function, eventually this called function will send data onto the bus */
  if (TcpIp_GetSockStateOfSocketTcpDyn(SocketTcpIdx) != TCPIP_TCP_SOCK_STATE_LISTEN)                                    /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {

    /* #20 Trigger sending last ACK of the TCP handshake. */
    if (TcpIp_IsSendLastHsAckOfSocketTcpDyn(SocketTcpIdx) == TRUE)
    {
      /* Send last ACK of the TCP handshake. */
      if (TcpIp_Tcp_VTransmitSegment(SocketTcpIdx, TCPIP_TCP_CODE_BIT_ACK, TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx), 0u, 0u, 0u) == E_OK)
      {
        /* Reset ACK flag that was already set in the TcpIp_Tcp_VRxIndicationStateSynSent_Fourth(). */
        TcpIp_SetTxFlagsOfSocketTcpDyn(SocketTcpIdx, (TcpIp_GetTxFlagsOfSocketTcpDyn(SocketTcpIdx) & ~TCPIP_TCP_CODE_BIT_ACK)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

        /* Reset flag that is used to detect the last ACK of the handshake. */
        TcpIp_SetSendLastHsAckOfSocketTcpDyn(SocketTcpIdx, FALSE);                                                      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
      else
      {
        /* Stop transmission because TcpIp_Tcp_VTransmitSegment() failed. Retry in next main function cycle. */
        continueTx = FALSE;
      }
    }

    if (continueTx == TRUE)
    {
      /* #30 Trigger queueing data into TxRetrQueue if available */
      if (TcpIp_IsTxReqFullyQueuedOfSocketTcpDyn(SocketTcpIdx) == FALSE)
      {
        /* Queue as much remaining data as possible */
        TcpIp_Tcp_VQueueRemReqData(SocketTcpIdx);
      }

    /* #40 Trigger nagle algorithm handling or trigger creation of a new segment. */
#if (TCPIP_SUPPORT_TCP_NAGLE_TIMEOUT == STD_ON)
      if (TcpIp_IsEnabledOfSocketTcpNagleDyn(SocketTcpIdx) == TRUE)
      {
        TcpIp_Tcp_VMainTxDataHandling_TxIfNagleEnabled(SocketTcpIdx);
      }
      else
#endif
      {
        /* prepare packet for sending */
        /* The return value can be ignored since if finalizing the segment fails here it will be retried in the next call
        of the MainFunction. */
        (void) TcpIp_Tcp_VFinalizeTxSegment(SocketTcpIdx);
      }

      /* #50 Trigger sending the packet to the bus */
      /* The return value can be ignored since if transmitting the segment fails here it will be retried in the next call
      of the MainFunction. */
      (void) TcpIp_Tcp_VTransmit(SocketTcpIdx);
    }
  }
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (TCPIP_SUPPORT_TCP_NAGLE_TIMEOUT == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VMainTxDataHandling_TxIfNagleEnabled
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VMainTxDataHandling_TxIfNagleEnabled(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /* #10 Check if the nagle timeout is configured to be not 0. */
  if (TcpIp_GetNagleTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX) > 0u)
  {
    TCPIP_ASSERT(TcpIp_HasSocketTcpNagleDyn() == TRUE);
    /* #20 Decrease the nagle timeout */
    if (TcpIp_GetTimeoutOfSocketTcpNagleDyn(SocketTcpIdx) > 0u)
    {
      TcpIp_DecTimeoutOfSocketTcpNagleDyn(SocketTcpIdx);                                                                /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
  }

  /* #30 Finalize a not completely filled segment if all sent data is acknowledged or the timeout has expired. */
  if (TCPIP_TCP_SEQ1_BIGGER_OR_EQUAL_SEQ2(TcpIp_GetSndUnaOfSocketTcpDyn(SocketTcpIdx), TcpIp_GetTxNextSendSeqNoOfSocketTcpDyn(SocketTcpIdx)))
  {
    /* #40 Build a new TCP segment (even if not completely filled) only if all data has been ACKed so far. */
    /* The return value can be ignored since if finalizing the segment fails here it will be retried in the next call
    of the MainFunction. */
    (void) TcpIp_Tcp_VFinalizeTxSegment(SocketTcpIdx);
  }
  else
  {
     /* #50 Build a new TCP segment if the nagle timeout has expired. */
    if (TcpIp_GetNagleTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX) > 0u)
    {
      if (TcpIp_GetTimeoutOfSocketTcpNagleDyn(SocketTcpIdx) == 0u)
      {
        /* The return value can be ignored since if finalizing the segment fails here it will be retried in the next
        call of the MainFunction. */
        (void) TcpIp_Tcp_VFinalizeTxSegment(SocketTcpIdx);
      }
    }
  }
}
#endif

#if (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VUpdateRttVars
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VUpdateRttVars(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint32                       ElementRtt)
{
  CANOE_WRITE_STRING("TcpIp_Tcp_VUpdateRttVars: -------------------------------------------------");
  CANOE_WRITE_STRING_2("TcpIp_Tcp_VUpdateRttVars: TCP connection %d, new ElementRtt is %d)", SocketTcpIdx, ElementRtt);
  CANOE_WRITE_STRING_4("TcpIp_Tcp_VUpdateRttVars old: TcpIp_Tcp_Rto is %d, TcpIp_Tcp_RtoValid is %d, TcpIp_Tcp_SRtt is %dms, TcpIp_Tcp_RttVar is %d)", TcpIp_GetRtoOfSocketTcpTsOptDyn(SocketTcpIdx), TcpIp_GetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx), TcpIp_GetSRttOfSocketTcpTsOptDyn(SocketTcpIdx), TcpIp_GetRttVarOfSocketTcpTsOptDyn(SocketTcpIdx));

  /* #10 Calculate RTTVar and SRTT according to RFC 2988 */
  /* use variable names according to the RFC */

  /* #20 Check the state of the retransmission timing */
  if (TcpIp_GetRtoStateOfSocketTcpTsOptDyn(SocketTcpIdx) == TCPIP_TCP_RTO_STATE_ACTIVE)
  {
    /* normal operation */
    /*
      RTTVAR = (1 - beta) * RTTVAR + beta * |SRTT - R'|
      SRTT   = (1 - alpha) * SRTT + alpha * R'
      The above SHOULD be computed using alpha=1/8 and beta=1/4

      After the computation, a host MUST update
      RTO = SRTT + max (G, K*RTTVAR)

      Whenever RTO is computed, if it is less than 1 second then the RTO SHOULD be rounded up to 1 s.
    */
    uint32 diffSrttR;

    /* #30 Calculate RTTVar, SRTT and RTO for normal operation */
    if (TcpIp_GetSRttOfSocketTcpTsOptDyn(SocketTcpIdx) > ElementRtt)
    {
      diffSrttR = TcpIp_GetSRttOfSocketTcpTsOptDyn(SocketTcpIdx) - ElementRtt;
    }
    else
    {
      diffSrttR = ElementRtt - TcpIp_GetSRttOfSocketTcpTsOptDyn(SocketTcpIdx);
    }
    TcpIp_SetRttVarOfSocketTcpTsOptDyn(SocketTcpIdx, (((3u * TcpIp_GetRttVarOfSocketTcpTsOptDyn(SocketTcpIdx)) + diffSrttR)  / 4u)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetSRttOfSocketTcpTsOptDyn(  SocketTcpIdx, (((7u * TcpIp_GetSRttOfSocketTcpTsOptDyn(SocketTcpIdx))   + ElementRtt) / 8u)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    {
      uint32 x1;
      uint32 x2;
      /* RTO = SRTT + max (G, K*RTTVAR)    where K = 4 */
      x1 = 1u;  /* clock granularity */
      x2 = TcpIp_GetRttVarOfSocketTcpTsOptDyn(SocketTcpIdx) * 4u;  /* K * RTTVAR    where K = 4 */
      if (x1 > x2)
      {
        TcpIp_SetRtoOfSocketTcpTsOptDyn(SocketTcpIdx, (TcpIp_GetSRttOfSocketTcpTsOptDyn(SocketTcpIdx) + x1));           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
      else
      {
        TcpIp_SetRtoOfSocketTcpTsOptDyn(SocketTcpIdx, (TcpIp_GetSRttOfSocketTcpTsOptDyn(SocketTcpIdx) + x2));           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
    }
  }
  else
  {
    /* (TcpIp_GetRtoStateOfSocketTcpDyn(SocketTcpIdx) == TCPIP_TCP_RTO_STATE_FIRST_CALC_PROCEEDED) */
    /* This is the very first calculation ot the round-trip time depenedent variables for this connection */
    uint32 x1;
    uint32 x2;

    /* #40 Calculate RTTVar, SRTT and RTO for operation start */
    TcpIp_SetSRttOfSocketTcpTsOptDyn(SocketTcpIdx, ElementRtt);                                                         /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    TcpIp_SetRttVarOfSocketTcpTsOptDyn(SocketTcpIdx, (ElementRtt / 2u));  /* R/2 */                                      /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    {
      /* RTO = SRTT + max (G, K*RTTVAR)    where K = 4 */
      x1 = 1;  /* clock granularity */
      x2 = TcpIp_GetRttVarOfSocketTcpTsOptDyn(SocketTcpIdx) * 4u;  /* K * RTTVAR    where K = 4 */
      if (x1 > x2)
      {
        TcpIp_SetRtoOfSocketTcpTsOptDyn(SocketTcpIdx, (TcpIp_GetSRttOfSocketTcpTsOptDyn(SocketTcpIdx) + x1));           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
      else
      {
        TcpIp_SetRtoOfSocketTcpTsOptDyn(SocketTcpIdx, (TcpIp_GetSRttOfSocketTcpTsOptDyn(SocketTcpIdx) + x2));           /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
      }
    }

    TcpIp_SetRtoStateOfSocketTcpTsOptDyn(SocketTcpIdx, TCPIP_TCP_RTO_STATE_ACTIVE);  /* go to next state */             /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }

  /* #50 Set the valid state for the retransmission timeout */
  if (TcpIp_GetRtoOfSocketTcpTsOptDyn(SocketTcpIdx) < TcpIp_GetRetransTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX))
  {
    TcpIp_SetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx, TcpIp_GetRetransTimeoutOfTcpConfig(TCPIP_TCPCONFIG_IDX));       /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else
  {
    TcpIp_SetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx, TcpIp_GetRtoOfSocketTcpTsOptDyn(SocketTcpIdx));                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  CANOE_WRITE_STRING_4("TcpIp_Tcp_VUpdateRttVars new: TcpIp_Tcp_Rto is %d, TcpIp_Tcp_RtoValid is %d, TcpIp_Tcp_SRtt is %dms, TcpIp_Tcp_RttVar is %d)", TcpIp_GetRtoOfSocketTcpTsOptDyn(SocketTcpIdx), TcpIp_GetRtoValidOfSocketTcpTsOptDyn(SocketTcpIdx), TcpIp_GetSRttOfSocketTcpTsOptDyn(SocketTcpIdx), TcpIp_GetRttVarOfSocketTcpTsOptDyn(SocketTcpIdx));

}  /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif  /* (TCPIP_SUPPORT_TCP_TIMESTAMP_OPTION == STD_ON) */


#if (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VIncAckSumN
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VIncAckSumN(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint32                       IncSize)
{
  /* #10 Increase the AckSum */
  TcpIp_SetAckSumNOfSocketTcpCongCtrlDyn(SocketTcpIdx, (TcpIp_GetAckSumNOfSocketTcpCongCtrlDyn(SocketTcpIdx) + IncSize)); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  if (TcpIp_GetAckSumTimeoutOfSocketTcpCongCtrlDyn(SocketTcpIdx) == 0u)
  {
    /* #20 If the AckSum timeout has expired, set a new value for the timeout dependent on the SRTT. */
    if (TcpIp_GetSRttOfSocketTcpTsOptDyn(SocketTcpIdx) == 0u)
    {
      TcpIp_SetAckSumTimeoutOfSocketTcpCongCtrlDyn(SocketTcpIdx, 1);                                                    /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
    else
    {
      TcpIp_SetAckSumTimeoutOfSocketTcpCongCtrlDyn(SocketTcpIdx, TcpIp_GetSRttOfSocketTcpTsOptDyn(SocketTcpIdx));       /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    }
  }
  CANOE_WRITE_STRING_3("TcpIp_Tcp_VIncAckSumN: SocketTcpIdx %d: current AckSumTimeout is %d, TcpIp_Tcp_SRtt is %d", SocketTcpIdx, TcpIp_GetAckSumTimeoutOfSocketTcpCongCtrlDyn(SocketTcpIdx), TcpIp_GetSRttOfSocketTcpTsOptDyn(SocketTcpIdx));
  CANOE_WRITE_STRING_4("TcpIp_Tcp_VIncAckSumN: SocketTcpIdx %d: function called with IncSize %d, new AckSum is %d, current AckSumTimeout is %d", SocketTcpIdx, IncSize, TcpIp_GetAckSumNOfSocketTcpCongCtrlDyn(SocketTcpIdx), TcpIp_GetAckSumTimeoutOfSocketTcpCongCtrlDyn(SocketTcpIdx));
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VIncCwnd
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VIncCwnd(
  TcpIp_SocketTcpDynIterType SocketTcpIdx,
  uint32                     IncSize)
{
  CANOE_WRITE_STRING_3("TcpIp_Tcp_VIncCwnd: SocketTcpIdx %d: function called with IncSize %d, current cwnd is %d", SocketTcpIdx, IncSize, TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx));
  /* #10 Increase the congestion window */
  /* cwnd += min(N, SMSS) */
  if (IncSize > TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx))
  {
    TcpIp_SetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx, (TcpIp_GetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx) + TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx))); /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else
  {
    TcpIp_SetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx, (TcpIp_GetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx) + IncSize));   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }

  /* #20 Update the congestion control mode */
  if (TcpIp_GetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx) <= TcpIp_GetSsthreshOfSocketTcpCongCtrlDyn(SocketTcpIdx))
  {
    TcpIp_SetCongestionControlModeOfSocketTcpCongCtrlDyn(SocketTcpIdx, TCPIP_TCP_CONG_CTRL_MODE_SLOW_START);            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else
  {
    TcpIp_SetCongestionControlModeOfSocketTcpCongCtrlDyn(SocketTcpIdx, TCPIP_TCP_CONG_CTRL_MODE_CONGESTION_AVOIDANCE);  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  CANOE_WRITE_STRING_3("TcpIp_Tcp_VIncCwnd: SocketTcpIdx %d: TcpIp_Tcp_Cwnd is now %d, TcpIp_Tcp_CongestionControlMode is now %d", SocketTcpIdx, TcpIp_GetCwndOfSocketTcpCongCtrlDyn(SocketTcpIdx), TcpIp_GetCongestionControlModeOfSocketTcpCongCtrlDyn(SocketTcpIdx));
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VSetSsthreshEqu4
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VSetSsthreshEqu4(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /* ssthresh = max[flightSize / 2, 2*SMSS] */
  uint32 flightSize;  /* flightSize is the amount of outstanding data in the network */
  uint32 smss;  /* sender maximum segment size */
  smss = TcpIp_GetTxMaxSegLenByteOfSocketTcpDyn(SocketTcpIdx);

  /* #10 Calculate the current fligth size (size of all segments currently sent but not acked). */
  flightSize = TcpIp_Tcp_VCalcFlightSize(SocketTcpIdx);

  /* #20 Update slow start threshold. */
  if ((flightSize / 2u) > (smss * 2u))
  {
    TcpIp_SetSsthreshOfSocketTcpCongCtrlDyn(SocketTcpIdx, (flightSize / 2u));                                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  else
  {
    TcpIp_SetSsthreshOfSocketTcpCongCtrlDyn(SocketTcpIdx, (smss * 2u));                                                  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  }
  CANOE_WRITE_STRING_2("TcpIp_Tcp_VSetSsthreshEqu4: SocketTcpIdx %d: TcpIp_Tcp_Ssthresh is now %d", SocketTcpIdx, TcpIp_GetSsthreshOfSocketTcpCongCtrlDyn(SocketTcpIdx));
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_VCalcFlightSize
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(uint32, TCPIP_CODE) TcpIp_Tcp_VCalcFlightSize(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  uint32                           flightSize;  /* flightSize is the amount of outstanding data in the network */
  TcpIp_SizeOfTcpRetryQElementType eleIdx;

  /* #10 Calculate the current fligth size (size of all segments currently sent but not acked). */
  flightSize = 0;
  eleIdx     = TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(SocketTcpIdx);
  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  while (   (eleIdx < TCPIP_TCP_RETRY_QUEUE_ELE_IDX_INV)
         && (TcpIp_GetAddrTcpRetryQElement(eleIdx)->TransmitCounter > 0u))
  {
    flightSize += TcpIp_GetAddrTcpRetryQElement(eleIdx)->SizeTotByte;
    eleIdx      = TcpIp_GetAddrTcpRetryQElement(eleIdx)->EleNext;
  }

  return flightSize;
}
#endif  /* (TCPIP_SUPPORT_TCP_CONGESTION_CONTROL == STD_ON) */


#if (TCPIP_SUPPORT_TCP_KEEP_ALIVE == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tcp_VKeepAliveTrigger
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VKeepAliveTrigger(
  TcpIp_SocketTcpDynIterType SocketTcpIdx)
{
  /* #10 Reset the keep alive timing */
  TCPIP_ASSERT(TcpIp_HasSocketTcpKeepAliveDyn() == TRUE);
  TcpIp_SetIdleTimeOfSocketTcpKeepAliveDyn(SocketTcpIdx, 0);                                                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetProbesOfSocketTcpKeepAliveDyn(  SocketTcpIdx, 0);                                                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
} /* TcpIp_Tcp_VKeepAliveTrigger() */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VKeepAliveReset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VKeepAliveReset(
  TcpIp_SocketTcpDynIterType SocketTcpIdx)
{
  TCPIP_ASSERT(TcpIp_HasSocketTcpKeepAliveDyn() == TRUE);
  /* #10 Disable the keep alive mechanism for this socket */
  TcpIp_SetEnabledOfSocketTcpKeepAliveDyn(      SocketTcpIdx, FALSE);                                                   /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetTimeoutOfSocketTcpKeepAliveDyn(      SocketTcpIdx, TcpIp_GetKeepAliveTimeOfTcpConfig(TCPIP_TCPCONFIG_IDX));  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetProbeIntervalOfSocketTcpKeepAliveDyn(SocketTcpIdx, TcpIp_GetKeepAliveIntervalOfTcpConfig(TCPIP_TCPCONFIG_IDX));  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
  TcpIp_SetProbesMaxOfSocketTcpKeepAliveDyn(    SocketTcpIdx, TcpIp_GetKeepAliveProbesMaxOfTcpConfig(TCPIP_TCPCONFIG_IDX));  /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */

  TcpIp_Tcp_VKeepAliveTrigger(SocketTcpIdx);
} /* TcpIp_Tcp_VKeepAliveReset() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_Tcp_VKeepAliveCopyParameters
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_Tcp_VKeepAliveCopyParameters(
  TcpIp_SocketTcpDynIterType   SocketTcpSrcIdx,
  TcpIp_SizeOfSocketTcpDynType SocketTcpDstIdx)
{
  TCPIP_ASSERT(TcpIp_HasSocketTcpKeepAliveDyn() == TRUE);
  /* #10 Copy the keep alive parameters from one socket to an other one */
  TcpIp_SetEnabledOfSocketTcpKeepAliveDyn(                                                                              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    SocketTcpDstIdx, TcpIp_IsEnabledOfSocketTcpKeepAliveDyn(SocketTcpSrcIdx));
  TcpIp_SetTimeoutOfSocketTcpKeepAliveDyn(                                                                              /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    SocketTcpDstIdx, TcpIp_GetTimeoutOfSocketTcpKeepAliveDyn(SocketTcpSrcIdx));
  TcpIp_SetProbeIntervalOfSocketTcpKeepAliveDyn(                                                                        /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    SocketTcpDstIdx, TcpIp_GetProbeIntervalOfSocketTcpKeepAliveDyn(SocketTcpSrcIdx));
  TcpIp_SetProbesMaxOfSocketTcpKeepAliveDyn(                                                                            /* SBSW_TCPIP_AWA_CSL_IDX_CALLER */
    SocketTcpDstIdx, TcpIp_GetProbesMaxOfSocketTcpKeepAliveDyn(SocketTcpSrcIdx));

  /* #20 Reset the keep alive timer */
  TcpIp_Tcp_VKeepAliveTrigger(SocketTcpDstIdx);
} /* TcpIp_Tcp_VKeepAliveReset() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_Tcp_VTransmitKeepAliveProbe
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tcp_VTransmitKeepAliveProbe(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx)
{
  /* #10 Transmit a keep alive probe */
  return TcpIp_Tcp_VTransmitSegment(SocketTcpIdx, TCPIP_TCP_CODE_BIT_ACK, (TcpIp_GetSndNxtOfSocketTcpDyn(SocketTcpIdx) - 1u), 0u, 0u, 0u);
} /* TcpIp_Tcp_VTransmitKeepAliveProbe() */
#endif


/**********************************************************************************************************************
 *  TcpIp_Tcp_StoreChecksumInHeader
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_StoreChecksumInHeader(
  uint16           Checksum,
  TCPIP_P2V(uint8) TcpHdrPtr)
{
  /* #10 Write the calculated checksum into the TCP header */
  TCPIP_PUT_UINT16_RAW(TcpHdrPtr, TCPIP_TCP_HDR_CHECKSUM_OFFSET, Checksum);                                             /* SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte */
}

/**********************************************************************************************************************
 *  TcpIp_AddWithWrapAround32
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(uint32, TCPIP_CODE) TcpIp_AddWithWrapAround32(
  uint32 Value,
  uint32 IncValue,
  uint32 ValueCount)
{
  uint32 remLen;
  uint32 valueLocal = Value;

  TCPIP_ASSERT(valueLocal    <  ValueCount);
  TCPIP_ASSERT(IncValue <= ValueCount);

  remLen = ValueCount - valueLocal;

  /* #10 Increase the value, taking care of the wraparound */
  if (IncValue < remLen)
  {
    valueLocal += IncValue;
  }
  else
  {
    valueLocal = (IncValue - remLen);
  }

  TCPIP_ASSERT(valueLocal < ValueCount);

  return valueLocal;
}

/**********************************************************************************************************************
 *  TcpIp_IncTxBufIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfTcpTxBufferType, TCPIP_CODE) TcpIp_IncTxBufIdx(
  TcpIp_SizeOfTcpTxBufferDescType TcpTxBufferDescIdx,
  TcpIp_SizeOfTcpTxBufferType     BufferIdx,
  TcpIp_SizeOfTcpTxBufferType     IncValue)
{
  TcpIp_SizeOfTcpTxBufferType newIdx;
  TcpIp_SizeOfTcpTxBufferType remLenAtEnd;

  /* #10 Check some conditions for the function parameters. */
  TCPIP_ASSERT(TcpTxBufferDescIdx < TcpIp_GetSizeOfTcpTxBufferDesc());
  TCPIP_ASSERT(TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(TcpIp_GetSocketTcpDynIdxOfTcpTxBufferDescDyn(TcpTxBufferDescIdx)) == TcpTxBufferDescIdx);

  TCPIP_ASSERT(BufferIdx >= TcpIp_GetTcpTxBufferStartIdxOfTcpTxBufferDesc(TcpTxBufferDescIdx));
  TCPIP_ASSERT(BufferIdx <  TcpIp_GetTcpTxBufferEndIdxOfTcpTxBufferDesc(TcpTxBufferDescIdx));
  TCPIP_ASSERT(IncValue  <= TcpIp_GetTcpTxBufferLengthOfTcpTxBufferDesc(TcpTxBufferDescIdx));

  /* #20 Calculate the remaining lenght at the end of the buffer before the wraparound occurs. */
  remLenAtEnd = TcpIp_GetTcpTxBufferEndIdxOfTcpTxBufferDesc(TcpTxBufferDescIdx) - BufferIdx;

  /* #30 Calc the new buffer access position that shall be returned to the caller of the function. */
  if (IncValue < remLenAtEnd)
  {
    /* No buffer wrap around occurrs */
    newIdx = BufferIdx + IncValue;
  }
  else
  {
    /* A buffer wrap around occurrs */
    newIdx = TcpIp_GetTcpTxBufferStartIdxOfTcpTxBufferDesc(TcpTxBufferDescIdx) + (IncValue - remLenAtEnd);
  }

  TCPIP_ASSERT(newIdx >= TcpIp_GetTcpTxBufferStartIdxOfTcpTxBufferDesc(TcpTxBufferDescIdx));
  TCPIP_ASSERT(newIdx <  TcpIp_GetTcpTxBufferEndIdxOfTcpTxBufferDesc(TcpTxBufferDescIdx));

  return newIdx;
}


/**********************************************************************************************************************
*  TcpIp_IncRxBufIdx
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfTcpRxBufferType, TCPIP_CODE) TcpIp_IncRxBufIdx(
  TcpIp_SizeOfTcpRxBufferDescType TcpRxBufferDescIdx,
  TcpIp_SizeOfTcpRxBufferType     BufferIdx,
  TcpIp_SizeOfTcpRxBufferType     IncValue)
{
  TcpIp_SizeOfTcpRxBufferType newIdx;
  TcpIp_SizeOfTcpRxBufferType remLenAtEnd;

  /* #10 Check some conditions for the function parameters. */
  TCPIP_ASSERT(TcpRxBufferDescIdx < TcpIp_GetSizeOfTcpRxBufferDesc());
  TCPIP_ASSERT(TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn(TcpIp_GetSocketTcpDynIdxOfTcpRxBufferDescDyn(TcpRxBufferDescIdx)) == TcpRxBufferDescIdx);

  TCPIP_ASSERT(BufferIdx >= TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx));
  TCPIP_ASSERT(BufferIdx <  TcpIp_GetTcpRxBufferEndIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx));
  TCPIP_ASSERT(IncValue  <= TcpIp_GetTcpRxBufferLengthOfTcpRxBufferDesc(TcpRxBufferDescIdx));

  /* #20 Calculate the remaining lenght at the end of the buffer before the wraparound occurs. */
  remLenAtEnd = TcpIp_GetTcpRxBufferEndIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx) - BufferIdx;

  /* #30 Calc the new buffer access position that shall be returned to the caller of the function. */
  if (IncValue < remLenAtEnd)
  {
    newIdx = BufferIdx + IncValue;
  }
  else
  {
    newIdx = TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx) + (IncValue - remLenAtEnd);
  }

  TCPIP_ASSERT(newIdx >= TcpIp_GetTcpRxBufferStartIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx));
  TCPIP_ASSERT(newIdx <  TcpIp_GetTcpRxBufferEndIdxOfTcpRxBufferDesc(TcpRxBufferDescIdx));

  return newIdx;
}


/**********************************************************************************************************************
*  TcpIp_Tcp_UpRxIndication
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_Tcp_UpRxIndication(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8) DataPtr,
  uint16           DataLen)
{
  TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  /* #10 Call the upper layer rx indication */
#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
  if (TcpIp_IsUseTlsOfSocketTcpDyn(SocketTcpIdx) == TRUE)
  {
    /* forward to TLS */
    Tls_RxIndication(TCPIP_SOCKET_IDX_TO_ID(socketIdx), DataPtr, DataLen);                                              /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }
  else
#endif
  {
    TcpIp_RxIndicationFunctions(socketIdx, TcpIp_GetAddrRemSockOfSocketDyn(socketIdx), DataPtr, DataLen);               /* SBSW_TCPIP_FC_RemoteAddressAvailable */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
  }
}

/**********************************************************************************************************************
 *  TcpIp_Tcp_VClearTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_VClearTxBuffer(
  TcpIp_SocketTcpDynIterType SocketTcpIdx)
{
  TcpIp_SizeOfTcpTxBufferDescType tcpTxBufferDescIdx;

  TCPIP_ASSERT(SocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn());

  /* #10 Determine the tx buffer index */
  tcpTxBufferDescIdx = TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(SocketTcpIdx);

  /* #20 Clear the buffer if a buffer is assigned */
  if (tcpTxBufferDescIdx < TcpIp_GetSizeOfTcpTxBufferDesc())
  {
    TcpIp_SetFillLevelOfTcpTxBufferDescDyn(tcpTxBufferDescIdx, 0);                                                      /* SBSW_TCPIP_AWA_CslIteration_Local */
    TcpIp_SetTcpTxBufferWriteIdxOfTcpTxBufferDescDyn(tcpTxBufferDescIdx, TcpIp_GetTcpTxBufferStartIdxOfTcpTxBufferDesc(tcpTxBufferDescIdx)); /* SBSW_TCPIP_AWA_CslIteration_Local */
  }
  else
  {
    TCPIP_ASSERT(tcpTxBufferDescIdx == TcpIp_GetSizeOfTcpTxBufferDesc());
  }
}


#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_Tcp_TlsRxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_TlsRxIndication(
  TcpIp_SocketIdType                       SocketIdx,
  TCPIP_P2V(uint8) DataPtr,
  uint16           DataLen)
{
  /* #10 Check if the SocketIdx is in a valid range */
  if ((SocketIdx < TcpIp_GetSizeOfSocketDyn()) && TCPIP_SOCKET_IDX_IS_TCP(SocketIdx))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    TcpIp_SocketTcpDynIterType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);
    if (TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx) == TRUE)
    {
      /* #20 Forward the received data to the socket owner */
      TcpIp_RxIndicationFunctions(SocketIdx, TcpIp_GetAddrRemSockOfSocketDyn(SocketIdx), DataPtr, DataLen);             /* SBSW_TCPIP_FC_RemoteAddressAvailable */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    }
  }
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_TlsTxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_TlsTxConfirmation(
  TcpIp_SocketIdType SocketIdx,
  uint16             DataLen)
{
  /* #10 Check if the SocketIdx is in a valid range */
  if ((SocketIdx < TcpIp_GetSizeOfSocketDyn()) && TCPIP_SOCKET_IDX_IS_TCP(SocketIdx))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    TcpIp_SocketTcpDynIterType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);
    if (TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx) == TRUE)
    {
      /* #20 Forward the tx confirmation to the socket owner */
      TcpIp_TxConfirmationFunctions(SocketIdx, DataLen);
    }
  }
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_TlsConnected
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_TlsConnected(
  TcpIp_SocketIdType SocketIdx)
{
  if ((SocketIdx < TcpIp_GetSizeOfSocketDyn()) && TCPIP_SOCKET_IDX_IS_TCP(SocketIdx))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    TcpIp_SocketTcpDynIterType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);

    if (TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx) == TRUE)
    {
      /* #10 Forward the CONNECTED event to the socket owner */
      TcpIp_TcpConnectedFunctions(socketTcpIdx);
    }
  }
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_TlsEvent
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_TlsEvent(
  TcpIp_SocketIdType SocketIdx,
  TcpIp_EventType Event)
{
  /* #10 Check if the SocketIdx is in a valid range */
  if ((SocketIdx < TcpIp_GetSizeOfSocketDyn()) && TCPIP_SOCKET_IDX_IS_TCP(SocketIdx))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    TcpIp_SocketOwnerConfigIterType socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(SocketIdx);
    TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);

    if (TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx) == TRUE)
    {
      /* #20 Forward the event to the socket owner */
      TcpIp_TcpIpEventFunctions(socketOwnerCfgIdx, SocketIdx, Event);
    }
  }
}


/**********************************************************************************************************************
 *  TcpIp_Tcp_TlsValidationResult
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_TlsValidationResult(
  TcpIp_SocketIdType  SocketIdx,
  TCPIP_P2V(uint8)    ValidationResultPtr,
  TCPIP_P2C(uint8)    CertChainPtr,
  uint32              CertChainLen)
{
  /* #10 Check if the SocketIdx is in a valid range */
  if ((SocketIdx < TcpIp_GetSizeOfSocketDyn()) && TCPIP_SOCKET_IDX_IS_TCP(SocketIdx))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    TcpIp_SizeOfSocketOwnerConfigType socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(SocketIdx);
    TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);
    if (TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx) == TRUE)
    {
      /* #20 Forward the valdidation result to the user. */
      TcpIp_TlsValidationResultFunctions(socketOwnerCfgIdx, SocketIdx, ValidationResultPtr, CertChainPtr, CertChainLen); /* SBSW_TCPIP_FC_PASSING_API_POINTER */ /* SBSW_TCPIP_FC_PASSING_API_POINTER */
    }
  }
}

/**********************************************************************************************************************
 *  TcpIp_Tcp_TlsReceived
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tcp_TlsReceived(
  TcpIp_SocketIdType SocketIdx,
  uint32 DataLenByte)
{
  /* #10 Check if the SocketIdx is in a valid range */

  if ((SocketIdx < TcpIp_GetSizeOfSocketDyn()) && TCPIP_SOCKET_IDX_IS_TCP(SocketIdx))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);
    if (TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx) == TRUE)
    {
      /* #20 Call RECEIVED for this TCP socket. */
      TcpIp_Tcp_Received(socketTcpIdx, (uint16)DataLenByte);  /* TLS can not receive bigger parts than 16k */
    }
  }
}
#endif

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif
  /* (TCPIP_SUPPORT_TCP == STD_ON) */

/* module specific MISRA deviations:

   module global deviations -> see file TcpIp.c

   -TCPIP_TCP-specific deviations:
   MD_TCPIP_TCP_15.4_0771_a:
      Reason:     The break statement is used multiple (two) times in a do-until struct to find a condition match. This
                  seems to be the most efficient way to do that.
      Risk:       Unstructured code should be avoided.
      Prevention: Covered by code review.
   MD_TCPIP_TCP_15.4_0771_b:
      Reason:     The break statement is used multiple times to stop the function TcpIp_Tcp_VSendPendingElements from
                  sending queued elements. Once one element can't be sent, the following ones shouldn't be sent, neither.
      Risk:       Unstructured code should be avoided.
      Prevention: Covered by code review.
   MD_TCPIP_TCP_15.4_0771_c:
      Reason:     The break statement is used multiple times to stop the function TcpIp_Tcp_VTransmitResets from sending
                  queued reset elements. Once one element can't be sent, the following ones shouldn't be sent, neither.
      Risk:       Unstructured code should be avoided.
      Prevention: Covered by code review.

*/

/* COV_JUSTIFICATION_BEGIN

\ID COV_TCPIP_MISRA
\ACCEPT XX
\REASON [MSR_COV_MISRA]

COV_JUSTIFICATION_END */

/*
NOTE: For Tp_AsrTpTcpIp the following additional assumption is taken:
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
All TcpIp-internal callers guarantee the validity of index parameters
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

/*
  CSL01: ABCIdx < Msn_GetSizeOfABC();  ABCIdx = TcpIp_GetSizeOfABC;       SetABC(ABCIdx, value);
  CSL02: ABCIdx < Msn_GetSizeOfABC();  ABCIdx = TcpIp_GetSizeOfABC;       SetDEF(ABCIdx, value);   -- DEF has same array size as ABC
  CSL03: ABCIdx < Msn_GetSizeOfABC();  hdl = Msn_GetDEFIdxOfABC(ABCIdx);  Msn_SetDEF(hdl, value);  -- modelled indirections

  silent analysis finding categories:
  PWA: pointer write access
  AWA: array write access
  FC:  function call
*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_TCPIP_AWA_CSL_IDX_CALLER
    \DESCRIPTION        The function writes into the CSL array at a position that is given by the index parameter.
                        SocketIdx and SocketTcpIdx can be converted into each other without further need of range checks
                        if the index is valid.
                        Reference: SBSW_TCPIP_CONVERSION_SOCKETIDX_TCPSOCKETIDX
    \COUNTERMEASURE \N  The caller ensures that the index is within the valid range by using TcpIp_GetSizeOf...().
                        Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_AWA_CslIteration_Local
    \DESCRIPTION        Access of ComStackLib generated array with bounds check using TcpIp_GetSizeOf...() function inside the current function.
    \COUNTERMEASURE \N  Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_AWA_CSL_IDX_FROM_PREVIOUS_FUNCTION_CALL
    \DESCRIPTION        Access of ComStackLib generated array valid index provided by a previous function call. If the
                        called function returns OK the used index has a valid value.
                        Optional: Reference: SBSW_TCPIP_CONVERSION_SOCKETIDX_TCPSOCKETIDX
    \COUNTERMEASURE \N  Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_FC_AWA_TcpHeader_WriteUIntByte
    \DESCRIPTION        1/2/4 bytes are written beginning at the position in the buffer provided by the caller (&BufferPtr[BufferPos]).
                        TcpIp_SomeArray[Pos]: 1
                        TcpIp_WriteUInt16():  2
                        TcpIp_WriteUInt32():  4
                        Before writing data to the header or header option, a buffer with the necessary size has been requested.
    \COUNTERMEASURE \N  The caller ensures that there are 1/2/4 bytes available at &BufferPtr[BufferPos].

  \ID SBSW_TCPIP_FC_TCP_HEADER_OPT_PTR
    \DESCRIPTION        A function is called to write a TCP header option to a given position in a byte array. Before
                        writing data to the header or header option, in function TcpIp_Tcp_VTransmitSegment() the length
                        of all TCP header options that shall be sent is calculated in
                        TcpIp_Tcp_VTransmitSegment_CalcHeaderLen() and the resulting total length for the TCP segment is
                        requested of the IP layer by a call of TcpIp_Tcp_VTransmitSegment_RequestIpTxBuffer(). Only if
                        the requested length could be provided the header and payload data will be written to the
                        buffer. In TcpIp_Tcp_VTransmitSegment_WriteHeaderOptions() the same header options are written
                        that were previously checked in TcpIp_Tcp_VTransmitSegment_CalcHeaderLen().
    \COUNTERMEASURE \N  The caller ensures that there is enough space available at &BufferPtr[BufferPos].

  \ID SBSW_TCPIP_FC_READ_TCP_HEADER_OPT_PTR
    \DESCRIPTION        A function is called to read a TCP header option from a given position in a byte array. The byte
                        position of the header option is checked to be smaller than the total header options length.
    \COUNTERMEASURE \N  In the function TcpIp_Tcp_VHandleTcpOptions() all TCP options received in the current segment
                        are evaluated. First it is assured that the length field is available, and than it is checked
                        that at least this amount of data is available in the TCP options. This ensures that only
                        available memory will be read.

  \ID SBSW_TCPIP_PWA_VALID_PTR_CALLER
    \DESCRIPTION        A pointer that was checked to be valid by the caller of this function is dereferenced and written.
    \COUNTERMEASURE \N  The caller ensures the validity of the pointer.

  \ID SBSW_TCPIP_AWA_CSL_Valid_BufferIdx_CALLER
    \DESCRIPTION        The function writes into the CSL array at a position that is given by the index parameter.
    \COUNTERMEASURE \N  The caller ensures that the index is within the valid range for TCP buffer indices.
                        Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_AWA_CSL_Valid_BufferIdx_local
    \DESCRIPTION        The function writes into the CSL array at a position that is given by the index parameter. The
                        used buffer index is assumed to be always valid according to the following reference:
                        REFERENCE: ID_SBSW_TCPIP_VALID_TCP_BUFFER_DESCRIPTOR_INDEX
    \COUNTERMEASURE \N  The valid assignment of the buffer index is checked in TcpIp_Tcp_Open using
                        TcpIp_GetSizeOfTcpTxBufferDesc and TcpIp_GetSizeOfTcpRxBufferDesc. Qualified use-case CSL01 of
                        ComStackLib.

  \ID SBSW_TCPIP_FC_OutParamLocalVarRef
    \DESCRIPTION        A function is called referencing a local variable as an out parameter.
    \COUNTERMEASURE \N  A local variable can always be referenced to.

  \ID SBSW_TCPIP_FC_ForwardIpTxBufferRef
    \DESCRIPTION        A function is called referencing a local pointer variable that was filled in a previous call of
                        TcpIp_Tcp_VTransmitSegment_RequestIpTxBuffer. If _RequestIpTxBuffer returned with E_OK a buffer
                        of the requested size could be provided.
    \COUNTERMEASURE \N  A local variable can always be referenced to.

  \ID SBSW_TCPIP_FC_ForwardTlsPbufRef
    \DESCRIPTION        A function is called referencing a local variable that was filled in a previous call of
                        Tls_ProvideTxBuffer. Tls_ProvideTxBuffer will always provide a single pbuf struct with a valid
                        payload pointer and length if the function returns E_OK.
    \COUNTERMEASURE \N  A local variable can always be referenced to.

  \ID SBSW_TCPIP_FC_ReferencingFunctionParameter
    \DESCRIPTION        A function is called referencing a function parameter and forward it as a pointer.
    \COUNTERMEASURE \N  The referenced API parameter is always available and can be referenced.

  \ID SBSW_TCPIP_FC_RemoteAddressAvailable
    \DESCRIPTION        A function is called forwarding the pointer to the remote socket address.
                        - The SocketTcpIdx or SocketIdx is given by the calling function or
                        - The SocketTcpIdx or SocketIdx is locally checked to be in a valid range by using the
                          TcpIp_GetSizeOf...() function.
    \COUNTERMEASURE \N  When a TCP connection is established, the remote socket address always contains a valid content
                        (real remote address). The remote socket address is accessed using a valid SocketTcpIdx (given
                        as function parameter).

  \ID SBSW_TCPIP_FC_WriteRemoteAddress
    \DESCRIPTION        A function is called to store the remote socket address.
                        The new remote address shall be stored in RemSockOfSocketDyn(socketIdx)->SockAddr, and the
                        socketIdx to access this array is derived from the SocketTcpIdx that is given as a function
                        parameter and checked by the calling function.
    \COUNTERMEASURE \N  The remote socket address is accessed using a valid SocketTcpIdx (derived from a function
                        parameter).

  \ID SBSW_TCPIP_FC_LocalAddressAvailable
    \DESCRIPTION        A function is called forwarding the pointer to the local socket address.
    \COUNTERMEASURE \N  When a TCP connection is established, the remote socket address always contains a valid content
                        (real remote address). The remote socket address is accessed using a valid SocketTcpIdx (given
                        as function parameter).

  \ID SBSW_TCPIP_FC_LocalAddressAvailable_GetIpAddr
    \DESCRIPTION        A function is called forwarding the pointer to the local socket address.
    \COUNTERMEASURE \N  Pointer references a local variable on the stack and the value was obtained by TcpIp_GetIpAddr()
                        which will only return E_OK if the adress value was updated.

  \ID SBSW_TCPIP_FC_FinTxSeg_ValidPtrFromOtherFuncCall
    \DESCRIPTION        A function is called forwarding the pointer to a queue element.
                        The pointer is set by the preceding function call TcpIp_Tcp_VFinalizeTxSegment_CreateRetryQElement
                        that always returns a valid pointer since it assumes that a free element is available.
    \COUNTERMEASURE \N  This function is only called when a free retry queue element is available. This is checked by
                        the previous call of TcpIp_Tcp_VFinalizeTxSegment_SetFlagsAndKeepAlive which only returns E_OK
                        if a free element is available.

  \ID SBSW_TCPIP_FC_CopyDataForTransmit
    \DESCRIPTION        A function is called to copy data from a TCP buffer to an Ethernet buffer or vice versa.
                        - The source buffer pointer is given using a buffer index that is in a valid range
                        - The target buffer pointer is given by the calling function or enhanced by a certain length (within a valid range)
    \COUNTERMEASURE \N  The function is only called with valid parameters.

  \ID SBSW_TCPIP_FC_CopyDataFromTcpSocketOwner
    \DESCRIPTION        A function is called to copy data from a socket owner buffer to the TCP transmit buffer.
                        The target buffer pointer is derived from the BufferWriteIndex, and the copy length is checked
                        not to exceed the BufferEndIndex. The overall copy length may not exceed the socket's buffer
                        length, this is checked by the calling function.
    \COUNTERMEASURE \N  The function is only called with valid parameters.

  \ID SBSW_TCPIP_PWA_ValidSegmentDescPtr_CALLER
    \DESCRIPTION        A member of the segment descriptor is written.
                        The pointer to the segment descriptor given by the caller is forwarded through multiple
                        functions and points to a local variable of type TcpIp_Tcp_SegmentDescriptorType defined in
                        TcpIp_Tcp_VRxIndication.
    \COUNTERMEASURE \N  In the context of the RxIndication this pointer is always valid.

  \ID SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx
    \DESCRIPTION       A member of the tx out of order (ooo) queue is written.
                       The pointer to the ooo element is derived of a valid ooo element index. It is assumed that
                       the socket's ooo list is always a consistent list with correct values for their members,
                       especially the index for the next element.
                       Reference: SBSW_TCPIP_OOO_QUEUE
    \COUNTERMEASURE \N In the local function context the pointer is always valid.

  \ID SBSW_TCPIP_PWA_PointerDerivedFromValidOooEleIdx_FirstEle
    \DESCRIPTION       The first member of the tx out of order (ooo) queue is written.
                       The pointer to the ooo element is derived of a valid ooo element index, since it previously has
                       been checked that the socket's ooo queue is not empty by checking
                       TcpIp_GetTcpOooQFillNumOfSocketTcpOooDyn() not being 0.
                       Reference: SBSW_TCPIP_OOO_QUEUE
    \COUNTERMEASURE \N In the local function context the pointer is always valid.

  \ID SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx
    \DESCRIPTION        A member of the tx retry queue is written.
                        The pointer to the queue element is derived of a valid retry queue element index.
                        The index is either given as function parameter, or it is taken from the 'next' and 'prev'
                        members of the struct, or is locally checked/initialized using TcpIp_GetSizeOfTcpRetryQElement()
                        (Qualified use-case CSL01 of ComStackLib).
                        The elements in the queue are assumed to be consistent and valid.
                        Reference: SBSW_TCPIP_TCP_RETRY_QUEUE
    \COUNTERMEASURE \N  In the local function context the pointer is always valid.

  \ID SBSW_TCPIP_PWA_PointerDerivedFromValidRetryQEleIdx_ValidFirstQueueElement
    \DESCRIPTION        A member of the tx retry queue is written.
                        The pointer to the queue element is derived of a valid retry queue element index.
                        The index is taken from TcpIp_GetTcpRetryQElementFirstIdxOfSocketTcpDyn(). The enclosing
                        if-section checks that there is one byte in the RetryQ, so the queue is not empty and therefore
                        a first list element exists and can be accessed.
                        Reference: SBSW_TCPIP_TCP_RETRY_QUEUE
    \COUNTERMEASURE \N  In the local function context the pointer is always valid.

  \ID SBSW_TCPIP_FC_PointerDerivedFromValidRetryQEleIdx
    \DESCRIPTION        A function is called using a pointer derived from a retry queue index.
                        The index is checked using a GetSizeOf macro, so a pointer derived from this index points to a
                        valid element.
                        Reference: SBSW_TCPIP_TCP_RETRY_QUEUE
    \COUNTERMEASURE \N  Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_PWA_PointerDerivedFromValidResetQEleIdx
    \DESCRIPTION        A member of the reset queue is written.
                        The pointer to the queue element is derived of a valid reset queue element index.
                        The index is either given as function parameter, or it is taken from the global variable
                        TcpIp_Tcp_RstTxQueueReadPos or TcpIp_Tcp_RstTxQueueWritePos.
                        The elements in the queue are assumed to be consistent and valid.
                        REFERENCE: SBSW_TCPIP_TCP_RESET_QUEUE
    \COUNTERMEASURE \N  In the local function context the pointer is always valid.

  \ID SBSW_TCPIP_FC_PointerDerivedFromValidResetQEleIdx
    \DESCRIPTION        A function is called using a pointer derived from a reset queue element index. The pointer
                        points to the struct or one of its members. The index is taken from the global variable
                        TcpIp_Tcp_RstTxQueueReadPos or TcpIp_Tcp_RstTxQueueWritePos.
                        The elements in the queue are assumed to be consistent and valid.
                        REFERENCE: SBSW_TCPIP_TCP_RESET_QUEUE
    \COUNTERMEASURE \N  In the local function context the pointer is always valid.

  \ID SBSW_TCPIP_PWA_SocketPointerDerivedFromValidSocketIdx
    \DESCRIPTION        A member of the socket struct is written.
                        The pointer to the struct element is derived of a valid socket index.
                        The socket index is given by the function caller.
                        Reference: SBSW_TCPIP_CONVERSION_SOCKETIDX_TCPSOCKETIDX
    \COUNTERMEASURE \N  In the local function context the pointer is always valid.

  \ID SBSW_TCPIP_CopyDataToRxBuffer
    \DESCRIPTION         Data is copied from the (Ethernet) input buffer to the TCP rx buffer of the receiving socket.
                         Reference: SBSW_TCPIP_RxBufferUsage_via_BufferIdx
                         The target pointer (TcpRxBuffer) is derived from the TcpRxBufferWriteIdx
                         tcpRxBufferWritePtr = TcpIp_GetAddrTcpRxBuffer(TcpIp_GetTcpRxBufferWriteIdxOfTcpRxBufferDescDyn(TcpRxBufferDescIdx))
                         Before copying the data it is checked if the source data can be written into the rx buffer at
                         the current write position without exceeding the end of the buffer. If the buffer end is
                         exceeded only a part of the data is copied to the end of the buffer and the remaining data is
                         copied to the start of the rx buffer.
    \COUNTERMEASURE  \N  According to the referenced concept the target buffer is big enough to copy the data to.

  \ID SBSW_TCPIP_FC_RxBufferPtr_1
    \DESCRIPTION         A function is called to read data (BBB) from the RxBuffer and forward it to the socket owner.
                         Reference: SBSW_TCPIP_RxBufferUsage_via_BufferIdx
    \COUNTERMEASURE  \N  According to the length check the data may be accessed for reading.
                                             |<---------- RxBufferLength -------------------->|
                                             |             |<- remainingLengthAtEndOfBuffer ->|
                         buffer = xxxxxxxxxxx|000000|AAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBB|000000|yyyyyyyyyyyyyyy
                                              ^      ^      ^                           ^      ^
                                              |      |      |                           |      |
                                              |      |      |                           |      RxBufferEndIdx
                                              |      |      |                           RxBufferWriteIdx
                                              |      |      RxBufferIndPos
                                              |      (RxBufferReadIdx)
                                              RxBufferStartIdx

                         RxBufferIndPos is a position relative to RxBufferStartIdx
                         remainingLengthAtEndOfBuffer = RxBufferLength - RxBufferIndPos
                         locBufPtr = TcpIp_GetAddrTcpRxBuffer(RxBufferStartIdx + RxBufferIndPos)
                         --> There are remainingLengthAtEndOfBuffer available for reading starting at RxBufferIndPos
                         --> If the data that shall be forwarded to the socket owner is smaller or equal to
                             remainingLengthAtEndOfBuffer, the access to the buffer starting at RxBufferIndPos is valid.

  \ID SBSW_TCPIP_FC_RxBufferPtr_2
    \DESCRIPTION         A function is called to read data (BBB) from the RxBuffer and forward it to the socket owner.
                         Reference: SBSW_TCPIP_RxBufferUsage_via_BufferIdx
    \COUNTERMEASURE  \N  According to the length check the data may be accessed for reading.
                                             |<---------- RxBufferLength -------------------->|
                                             |                  --  |<- remLenAtEndOfBuffer ->|
                         buffer = xxxxxxxxxxx|BBBBBB|00000000|AAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBB|yyyyyyyyyyyyyyy
                                              ^      ^      ^      ^                           ^
                                              |      |      |      |                           |
                                              |      |      |      |                           RxBufferEndIdx
                                              |      |      |      RxBufferIndPos
                                              |      |      (RxBufferReadIdx)
                                              |      RxBufferWriteIdx
                                              RxBufferStartIdx

                         RxBufferIndPos is a position relative to RxBufferStartIdx
                         remLenAtEndOfBuffer = RxBufferLength - RxBufferIndPos
                         locBufPtr = TcpIp_GetAddrTcpRxBuffer(RxBufferStartIdx + RxBufferIndPos)
                         --> There are remLenAtEndOfBuffer available for reading starting at RxBufferIndPos
                         --> If the data that shall be forwarded to the socket owner is bigger than remLenAtEndOfBuffer,
                             the function can access 'remLenAtEndOfBuffer' bytes at position 'RxBufferIndPos' and
                             '(MaxLenToForward - remLenAtEndOfBuffer)' bytes at position 'RxBufferStartIdx'.

  \ID SBSW_TCPIP_FC_PASSING_API_POINTER
    \DESCRIPTION        Pointer is passed as function argument.
    \COUNTERMEASURE \N  Pointer was passed as function argument and is used to call sub-function. The validity of the
                        pointer is ensured by the caller. If not otherwise specified, each pointer has to point to
                        valid data != NULL_PTR.

  \ID SBSW_TCPIP_FC_PASSING_API_POINTER_CASTED
    \DESCRIPTION        An API pointer parameter is casted by using one of the union elements of the incoming pointer,
                        and is passed as function argument.
                        E.g. TcpIp_SockAddrBaseType has union member SockAddr with of type IpBase_SockAddrType.
    \COUNTERMEASURE \N  Pointer was passed as function argument and is used to call sub-function. The validity of the
                        pointer is ensured by the caller. If not otherwise specified, each pointer has to point to
                        valid data != NULL_PTR.

  \ID SBSW_TCPIP_FC_NULL_PTR
    \DESCRIPTION        NULL_PTR is passed as function argument.
    \COUNTERMEASURE \N  NULL_PTR is an allowed value to identify special use-case.
                        The pointer value is checked against NULL_PTR within the called function.

  \ID SBSW_TCPIP_FC_NULL_PTR_SECOND_DATA_ELEMENT
    \DESCRIPTION        NULL_PTR is passed as function argument. This is ok if it is used as a pointer to a second data
                        element if the second data element does not exist. The called function either evaluates the
                        NullPtr, or length information is passed that says that the second element has length '0' or
                        does not exist.
    \COUNTERMEASURE \N  NULL_PTR is an allowed value to identify special use-case.
                        The pointer value is checked against NULL_PTR within the called function, or given length values
                        are checked.

  \ID SBSW_TCPIP_FC_REFERENCE_OF_VARIABLE
    \DESCRIPTION        Pointer to variable is passed as function argument.
    \COUNTERMEASURE \N  Pointer is generated by referencing a variable respectively a struct member of a variable by
                        the address operator.

  \ID SBSW_TCPIP_FC_REFERENCE_OF_LOC_POINTER_VAR
    \DESCRIPTION        Pointer to pointer variable is passed as function argument.
    \COUNTERMEASURE \N  Pointer is generated by referencing a local pointer variable by the address operator. The
                        pointer is only used as an out parameter.

  \ID SBSW_TCPIP_FC_REFERENCE_OF_ARRAY_ELEMENT
    \DESCRIPTION        Pointer to array element is passed as function argument.
    \COUNTERMEASURE \N  Pointer is generated by referencing an array element which is obtained by qualified
                        use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_PWA_VALID_API_POINTER
    \DESCRIPTION        Write access to element which is passed as function argument.
    \COUNTERMEASURE \N  It is assumed, that the input pointer is valid and the function only writes members of the
                        pointed struct.

  \ID SBSW_TCPIP_CONVERSION_SOCKETIDX_TCPSOCKETIDX
    \DESCRIPTION        CONCEPT: The indices for SocketIdx and TcpSocketIdx can be converted into each other via a
                        simple offset calculation. The first values of SocketIdx are used for UDP, the following ones
                        for TCP. When using these converted indices to access socket or tcpSocket related arrays, no
                        further range check is necessary. If a SocketIdx is within the range of TCP sockets, the
                        conversion will always result in a valid TcpSocketIdx. The other way around is even simpler
                        since each valid TcpSocketIdx can be converted into a valid SocketIdx.
                        SocketIdx [0 .. (NumUdpSockets -1)] is used for UDP sockets
                        SocketIdx [NumUdpSockets .. (NumSockets -1)] is used for TCP sockets
                        SocketIdx 'NumSockets' is used to invalidate a SocketIdx variable
    \COUNTERMEASURE \N  Use the macros TCPIP_SOCKET_IDX_TO_TCP_IDX() and TCPIP_TCP_IDX_TO_SOCKET_IDX() to convert between
                        the two indices.

  \ID SBSW_TCPIP_RxBufferUsage_via_BufferIdx
    \DESCRIPTION        CONCEPT: The rx buffer is implemented as one big byte array, and the CSL generates start and end
                        indices for each configured buffer.
                        Furthermore there is a write index and a read index managed for each buffer. The write index is
                        only updated in the functions TcpIp_Tcp_VRxIndicationStateOthers_Seventh_CopyRxDataAndTriggerAck
                        and TcpIp_Tcp_VRxIndicationStateOthers_Seventh_ReceiveBufferedData, both in the context of the
                        RxIndication.
                                             |<---------- RxBufferLength ------------>|
                                             |      |<------ FillLevel ------->|      |
                                             |             |<- RemIndLength -->|      |
                         buffer = xxxxxxxxxxx|000000|AAAAAA|BBBBBBBBBBBBBBBBBBB|000000|yyyyyyyyyyyyyyy
                                              ^      ^      ^                   ^      ^
                                              |      |      |                   |      |
                                              |      |      |                   |      RxBufferEndIdx
                                              |      |      |                   RxBufferWriteIdx
                                              |      |      RxBufferIndPos
                                              |      (RxBufferReadIdx)
                                              RxBufferStartIdx

                        dynamic buffer description elements:
                        - RxBufferRemIndLenOfSocketTcpDyn
                        - RxBufferIndPosOfSocketTcpDyn
                        - RcvWndOfSocketTcpDyn = BufferLength - FillLevel
                        - FillLevelOfTcpRxBufferDescDyn = AAA + BBB
                        - TcpRxBufferWriteIdxOfTcpRxBufferDescDyn

                        static buffer description elements:
                        - TcpRxBufferStartIdxOfTcpRxBufferDesc
                        - TcpRxBufferEndIdxOfTcpRxBufferDesc
                        - TcpRxBufferLengthOfTcpRxBufferDesc

    \COUNTERMEASURE \N  The buffer is handled according to this concept, so the buffer can be accessed using this
                        mechanism.

  \ID SBSW_TCPIP_VALID_TCP_BUFFER_DESCRIPTOR_INDEX
    \DESCRIPTION        CONCEPT: When requesting a socket for TCP communication, the socket owner also requests rx and
                        tx buffers for the socket. Establishing a connection is not possible without this buffer
                        assignment, this is checked in TcpIp_Tcp_Open. Therefore it is not necessary to check the
                        validity of the rx and tx buffer indices assigned to the socket when further processing state
                        or data handling for this socket.
    \COUNTERMEASURE \N  Assure that buffer index is always taken from the variables
                        TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn and TcpIp_GetTcpRxBufferDescIdxOfSocketTcpDyn.

  \ID SBSW_TCPIP_TCP_RETRY_QUEUE
    \DESCRIPTION        CONCEPT: The TCP retry queue is used to manage the segments that shall be sent for each socket.
                        There is a global list of free elements, organised as a double-linked list. When data shall be
                        sent on a socket, the data is segmented according to the maximum segment size, and for each
                        segment one element is taken from the list of free elements and appended (and linked) to the
                        socket's list of retry elements. As soon as data is acknowledged by the peer, the first retry
                        queue elements are removed from the queue according to the acknowledged amount of data.
                        TcpIp_GetSizeOfTcpRetryQElement() is used as marker for not existing preceeding or following
                        elemnts and as FirstIdx and LastIdx if the queue contains no elements.
                        The list of free elements is initialized in TcpIp_Tcp_Init, as well as the start and end indices
                        and queue element number for each socket.
                        New elements are appended in TcpIp_Tcp_VFinalizeTxSegment_CreateRetryQElement, the first element
                        is removed in TcpIp_Tcp_VFreeFirstRetrQueueEle, and all elements are removed in
                        TcpIp_Tcp_VDelTxQueue. Each operation takes care of keeping the lists and their indices and
                        lengths in a consistant state.
    \COUNTERMEASURE \N  All queue manipulations take care that the list elements have valid values.
                        TcpIp_GetSizeOfTcpRetryQElement() is taken as index for the successor of the last element in a
                        queue as well as for the predecessor of the first queue element, and also in empty lists as
                        index for FirstIdx and LastIdx.

  \ID SBSW_TCPIP_OOO_QUEUE
    \DESCRIPTION       CONCEPT: The TCP Out Of Order (OOO) queue is used to manage received segments that fit into the
                       receive buffer / receive window but do not directly continue the stream of consecutive bytes. The
                       data is copied to the receive buffer and the ooo queue handles the meta data like byte position
                       in the stream and length of the received segment. For received segments it is checked if they
                       fill the gap between the consecutively received bytes and the first segment in the ooo queue, or
                       if they can be apended or prepended to an existing element in the ooo queue.
                       The ooo queue is a linked list of elements, and the TcpOooQFillNumOfSocketTcpOooDyn and
                       TcpOooQElementFirstIdxOfSocketTcpOooDyn are kept consistent during each manipulation of the queue.
                       OooQFillNum and OooQElementFirstIdx are reset in TcpIp_Tcp_Init() and TcpIp_Tcp_VRestartSock(),
                       increased in TcpIp_Tcp_VRxIndicationStateOthers_Seventh_InsertNewOooElement() and
                       _Seventh_CreateFirstOooElement() and decremented in _Seventh_ReceiveBufferedData() and
                       _Seventh_CheckCombination().
    \COUNTERMEASURE \N  When the pre-buffered segments are handled according to this concept, the segments can be
                        accessed via pointers derived from stored start indices and lengths.

  \ID SBSW_TCPIP_SACK
    \DESCRIPTION        CONCEPT: Selective Acknowledgment (SACK) uses the OOO concept and extends it. Received data
                        segments with a gap in the received data is stored in the rx buffer, and the the segments stored
                        in the OOO list are indicated to the peer using the SACK option. Elements acknowledged via the
                        SACK option are not garantied to be kept in the buffer, only the 'normal' ACK may cause the
                        sender to remove the data from its retransmission struct.
                        TcpOooQElementLastChangedIdxOfSocketTcpOooDyn is used to store the last modified element.
    \COUNTERMEASURE \N  The same rules as for concept SBSW_TCPIP_OOO_QUEUE apply here.

  \ID SBSW_TCPIP_TCP_RESET_QUEUE
    \DESCRIPTION        CONCEPT: TCP has a global reset queue (TcpResetQ) to handle all reset segments that shall be
                        sent. This is an array used as circular buffer and is initialized by TcpIp_Tcp_Init. The write
                        position and the fill level are updated when a new reset event shall be added to the queue in
                        TcpIp_Tcp_VSendReset. The read position marks the oldest element in the queue and is updated
                        (together with the fill level) when a reset segment could be sent in TcpIp_Tcp_VTransmitResets.
                        The write and read position are always increased by the macro TcpIp_Tcp_IncTxRstQueueIdx that
                        calculates the position modulo the size of the reset queue.
    \COUNTERMEASURE \N  TcpIp_Tcp_RstTxQueueWritePos and TcpIp_Tcp_RstTxQueueReadPos are always incremented taking care
                        of the warparound at TcpIp_GetSizeOfTcpResetQElement().

  \ID SBSW_TCP_PTR_CALL_BY_REF_UPDATE
    \DESCRIPTION       Pointer passed as call by reference is modified in the function without check.
    \COUNTERMEASURE \N The caller ensures that the pointers passed are pointing to valid memory location.

  \ID SBSW_TCP_LOCSOCKADDR_PTR
    \DESCRIPTION       AddrLocSock element of SocketDyn() is written or passed to subroutine with an index
                       parameter given by TcpIp_GetIpV4SocketDynTcpRstIdxOfIpV4General().
    \COUNTERMEASURE \M Verify that optional indirection
                         TcpIp_GetIpV4SocketDynTcpRstIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX)
                       is always valid if IPv4 and TCP are enabled.
                         TCPIP_SUPPORT_IPV4 == STD_ON
                         TCPIP_SUPPORT_TCP == STD_ON
                       This is ensure by CM_TCPIP_IPV4_TCP_RST_SOCKET.

SBSW_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  MSSV Checks
 *********************************************************************************************************************/

/* \CM CM_TCPIP_IPV4_TCP_RST_SOCKET   TcpIp_GetIpV4SocketDynTcpRstIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX) has to be
                                      valid if IPv4 and TCP is configured. */

/**********************************************************************************************************************
 *  END OF FILE: Tcp.c
 *********************************************************************************************************************/
