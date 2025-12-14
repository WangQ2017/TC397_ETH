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
/**        \file  SoAd_Rx.c
 *        \brief  Socket Adaptor source file
 *
 *      \details  Vector static code implementation for AUTOSAR Socket Adaptor sub-component Rx.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main source file.
 *********************************************************************************************************************/

/* PRQA S 1881 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA S 4304 EOF */ /* MD_MSR_AutosarBoolean */

#define SOAD_RX_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "SoAd_EventQueue.h"
#include "SoAd_TcpIp.h"
#include "SoAd_SoCon.h"
#include "SoAd_RouteGrp.h"
#include "SoAd_Rx.h"
#include "SoAd_Measure.h"

#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
#include "IpBase.h"
#include "vstdlib.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Length of meta data to store socket connection index. */
#define SOAD_RX_META_DATA_LEN 2u

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (SOAD_LOCAL) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL static
#endif

#if !defined (SOAD_LOCAL_INLINE) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define SOAD_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/**********************************************************************************************************************
 *  SoAd_Rx_RxIndicationProtocol()
 *********************************************************************************************************************/
/*! \brief       Receives data from socket for the different protocol types (TCP, UDP).
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \param[in]    BufPtr          Pointer to buffer of received data.
 *  \param[in]    Length          Length of received data.
 *  \param[out]   ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket connection index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_Rx_RxIndicationProtocol(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_Rx_CheckSocketParameter()
 *********************************************************************************************************************/
/*! \brief      Checks socket specific parameter for reception.
 *  \details    -
 *  \param[in]  SockIdx         Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \return     E_OK            Parameter for reception are valid.
 *  \return     E_NOT_OK        Parameter for reception are invalid.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_CheckSocketParameter(
  SoAd_SizeOfSocketType SockIdx);

/**********************************************************************************************************************
 *  SoAd_Rx_GetSoConIdx()
 *********************************************************************************************************************/
/*! \brief        Returns reception related socket connection on socket.
 *  \details      -
 *  \param[in]    SockIdx         Module internal socket index.
 *                                [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]    RemoteAddrPtr   Pointer to remote address.
 *                                [Points to one of the following structs depending on configured IP address version of
 *                                parameter SockIdx:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \param[in]    BufPtr          Pointer to buffer of received data.
 *  \param[in]    Length          Length of received data.
 *  \param[out]   SoConIdxPtr     Pointer to socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return       E_OK            Socket connection found and SoConIdxPtr is set.
 *  \return       E_NOT_OK        No socket connection found and SoConIdxPtr has not been modified.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket indexes, FALSE for same socket index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_GetSoConIdx(
  SoAd_SizeOfSocketType SockIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxPtr);

/**********************************************************************************************************************
 *  SoAd_Rx_CheckSoConParameter()
 *********************************************************************************************************************/
/*! \brief      Checks socket connection specific parameter for reception.
 *  \details    Additionally handles socket connection open on reception.
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  RemoteAddrPtr   Pointer to remote address.
 *                              [Points to one of the following structs depending on configured IP address version of
 *                              parameter SoConIdx:
 *                                - SoAd_SockAddrInetType for IPv4
 *                                - SoAd_SockAddrInet6Type for IPv6]
 *  \return     E_OK            Parameter for reception are valid.
 *  \return     E_NOT_OK        Parameter for reception are invalid.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_CheckSoConParameter(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr);

/**********************************************************************************************************************
 *  SoAd_Rx_GetSoConIdxByBestMatchAlg()
 *********************************************************************************************************************/
/*! \brief      Returns socket connection index with highest best match algorithm priority on a socket connection group
 *              and considers socket route existence or PDU header if configured.
 *  \details    Uses the parameter "SoConIdx" to identify the socket connection group on which the best match algorithm
 *              is performed.
 *  \param[in]  SoConIdx          Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  RemoteAddrPtr     Pointer to remote address.
 *                                [Points to one of the following structs depending on configured IP address version of
 *                                parameter SoConIdx:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \param[in]  BufPtr            Pointer to received PDU header.
 *  \param[in]  Length            Length of received data.
 *  \param[out] SoConIdxPtr       Pointer to best matching socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return     E_OK              Matching Socket connection found and SoConIdxPtr is set.
 *  \return     E_NOT_OK          No matching socket connection found and SoConIdxPtr has not been modified.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_GetSoConIdxByBestMatchAlg(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxPtr);

/**********************************************************************************************************************
 *  SoAd_Rx_GetSoConIdxByBestMatchAlgWithPduHdr()
 *********************************************************************************************************************/
/*! \brief      Returns socket connection index of first matching socket connection which has a socket route with
 *              corresponding PDU header ID and at least one enabled routing group.
 *  \details    -
 *  \param[in]  BufPtr                Pointer to received PDU header.
 *  \param[in]  SoConIdxListSize      Size of list of socket connection indexes.
 *                                    [range: SoConIdxListSize < SoAd_GetSizeOfBestMatchSoConIdxList()]
 *  \param[out] SoConIdxPtr           Pointer to best matching socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return     E_OK                  Matching Socket connection found and SoConIdxPtr is set.
 *  \return     E_NOT_OK              No matching socket connection found and SoConIdxPtr has not been modified.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
/* PRQA S 779 5 */ /* MD_MSR_Rule5.2 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_GetSoConIdxByBestMatchAlgWithPduHdr(
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  SoAd_SizeOfSoConType SoConIdxListSize,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxPtr);

/**********************************************************************************************************************
 *  SoAd_Rx_GetSoConIdxByBestMatchAlgWithSocketRoute()
 *********************************************************************************************************************/
/*! \brief      Returns socket connection index of first matching socket connection which has a socket route.
 *  \details    -
 *  \param[in]  SoConIdxListSize      Size of list of socket connection indexes.
 *                                    [range: SoConIdxListSize < SoAd_GetSizeOfBestMatchSoConIdxList()]
 *  \param[out] SoConIdxPtr           Pointer to best matching socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return     E_OK                  Matching Socket connection found and SoConIdxPtr is set.
 *  \return     E_NOT_OK              No matching socket connection found and SoConIdxPtr has not been modified.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
/* PRQA S 779 4 */ /* MD_MSR_Rule5.2 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_GetSoConIdxByBestMatchAlgWithSocketRoute(
  SoAd_SizeOfSoConType SoConIdxListSize,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxPtr);

/**********************************************************************************************************************
 *  SoAd_Rx_FindSocketRouteOnSoConByPduHdrId()
 *********************************************************************************************************************/
/*! \brief      Returns the socket route index of the socket connection which has the same PDU header ID.
 *  \details    -
 *  \param[in]  SoConIdx              Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PduHdrId              PDU header identifier.
 *  \param[out] SocketRouteIdxPtr     Pointer to socket route index.
 *  \param[out] ErrorIdPtr            Pointer to error identifier (set if error occurred).
 *  \return     E_OK                  Matching socket route found.
 *  \return     E_NOT_OK              No matching socket route found.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_FindSocketRouteOnSoConByPduHdrId(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PduHdrIdType PduHdrId,
  P2VAR(SoAd_SizeOfSocketRouteType, AUTOMATIC, SOAD_APPL_DATA) SocketRouteIdxPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxIf_TcpPduHdrReceiveHeader()
 *********************************************************************************************************************/
/*! \brief        Receives the PDU header for IF-PDUs and stores it in the IF reception buffer.
 *  \details      -
 *  \param[in]    SoConIdx          Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon(),
 *                                  SoAd_IsRxBufferConfigUsedOfSoCon(),
 *                                  SoAd_IsIfRxBufferUsedOfRxBufferConfig()]
 *  \param[in]    SockRouteDestIdx  Socket route destination index.
 *                                  [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in]    PduHdrBufPtr      Pointer to buffer where PDU header is stored.
 *                                  [range: PduHdrBufPtr points to 8 byte header]
 *  \param[out]   ErrorIdPtr        Pointer to error identifier (set if error occurred).
 *  \return       E_OK              PDU header stored successfully.
 *  \return       E_NOT_OK          PDU header could not be stored.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \config       SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxIf_TcpPduHdrReceiveHeader(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_DATA) PduHdrBufPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxIf_TcpPduHdrCopyData()
 *********************************************************************************************************************/
/*! \brief          Copies IF-PDU data to IF reception buffer in case PDU is not received in one TCP segment on TCP
 *                  socket connections with enabled PDU header.
 *  \details        -
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon(),
 *                                      SoAd_IsRxBufferConfigUsedOfSoCon(),
 *                                      SoAd_IsIfRxBufferUsedOfRxBufferConfig()]
 *  \param[in,out]  ReleaseBufLenPtr    Pointer to buffer length to be released.
 *  \param[in]      TotalLen            Total length of received data.
 *  \param[out]     PduInfoPtr          Pointer to PDU (either to IF reception buffer or TcpIp buffer).
 *  \return         E_OK                PDU copied completely or PDU is received in one TCP segment.
 *  \return         E_NOT_OK            PDU not copied completely.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxIf_TcpPduHdrCopyData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  uint32 TotalLen,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_RxIf_TcpPduHdrForwardPdu()
 *********************************************************************************************************************/
/*! \brief          Forwards a IF-PDU to user on TCP socket connections with enabled PDU header.
 *  \details        -
 *  \param[in]      SoConIdx        Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon(),
 *                                  SoAd_IsRxBufferConfigUsedOfSoCon(),
 *                                  SoAd_IsIfRxBufferUsedOfRxBufferConfig()]
 *  \param[in,out]  PduInfoPtr      Pointer to PDU.
 *  \param[out]     ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxIf_TcpPduHdrForwardPdu(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxIf_TcpReceivePdu()
 *********************************************************************************************************************/
/*! \brief        Forwards data received on a TCP socket connection via IF-API.
 *  \details      -
 *  \param[in]    SoConIdx          Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    SockRouteDestIdx  Socket route destination index.
 *                                  [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in]    BufPtr            Pointer to TCP segment.
 *  \param[in]    Length            Length of TCP segment.
 *  \param[out]   ErrorIdPtr        Pointer to error identifier (set if error occurred).
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \config       SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxIf_TcpReceivePdu(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_RxIf_UdpPduHdrForwardPdu()
 *********************************************************************************************************************/
/*! \brief        Forwards a IF-PDU to user on UDP socket connections with enabled PDU header.
 *  \details      -
 *  \param[in]    SoConIdx          Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    SockRouteDestIdx  Socket route destination index.
 *                                  [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in]    PduHdrLen         PDU header length.
 *  \param[in]    BufPtr            Pointer to received UDP frame with offset to current PDU header.
 *  \param[out]   ErrorIdPtr        Pointer to error identifier (set if error occurred).
 *  \pre          -
 *  \context      ISR2
 *  \reentrant    FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxIf_UdpPduHdrForwardPdu(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  SoAd_PduHdrLenType PduHdrLen,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxIf_UdpReceivePdu()
 *********************************************************************************************************************/
/*! \brief        Handles data received on a UDP socket connection and forwards it via IF-API.
 *  \details      -
 *  \param[in]    SockRouteDestIdx  Socket route destination index.
 *                                  [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in]    BufPtr            Pointer to received UDP frame.
 *  \param[in]    Length            Length of UDP frame.
 *  \param[out]   ErrorIdPtr        Pointer to error identifier (set if error occurred).
 *  \pre          -
 *  \context      ISR2
 *  \reentrant    FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxIf_UdpReceivePdu(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxIf_AddMetaDataToPdu()
 *********************************************************************************************************************/
/*! \brief          Adds meta data to a IF-PDU by copying PDU to a local buffer and copying meta data behind.
 *  \details        -
 *  \param[in]      SoConIdx        Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      SockRouteIdx    Socket route index.
 *                                  [range: SockRouteIdx < SoAd_GetSizeOfSocketRoute()]
 *  \param[in,out]  PduInfoPtr      Pointer to PDU.
 *  \param[out]     ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \return         E_OK            Adding meta data succeeded.
 *  \return         E_NOT_OK        Adding meta data failed since local buffer size is not sufficient.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \trace          DSGN-SoAdReceptionForwardsSocketConnection, DSGN-SoAdMetaData
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxIf_AddMetaDataToPdu(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteType SockRouteIdx,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_StartOfReception()
 *********************************************************************************************************************/
/*! \brief        Calls StartOfReception to begin a TP session in case PDU header is disabled.
 *  \details      -
 *  \param[in]    SoConIdx    Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return       E_OK        Call to StartOfReception succeeded or is not required.
 *  \return       E_NOT_OK    Call to StartOfReception failed.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_StartOfReception(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_RxTp_CallStartOfReception()
 *********************************************************************************************************************/
/*! \brief        Calls StartOfReception function of upper layer.
 *  \details      -
 *  \param[in]    SockRouteDestIdx  Socket route destination index.
 *                                  [range: SockRouteDestIdx < SoAd_GetSizeOfSocketDestRoute()]
 *  \param[in]    TpSduLength       Entire data length to be received.
 *  \param[out]   BufferSizePtr     Pointer to available data length.
 *  \return       BUFREQ_OK         Copy request accepted.
 *  \return       BUFREQ_E_NOT_OK   Copy request not accepted.
 *  \return       BUFREQ_E_BUSY     Temporarily no buffer available.
 *  \return       BUFREQ_E_OVFL     No Buffer of the required length can be provided.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_RxTp_CallStartOfReception(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  PduLengthType TpSduLength,
  CONSTP2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_DATA) BufferSizePtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_CallCopyRxData()
 *********************************************************************************************************************/
/*! \brief        Calls CopyRxData function of upper layer.
 *  \details      -
 *  \param[in]    SockRouteDestIdx  Socket route destination index.
 *                                  [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in]    PduInfoPtr        Pointer to PDU.
 *  \param[out]   BufferSizePtr     Pointer to available data length.
 *  \return       BUFREQ_OK         Copy request accepted.
 *  \return       BUFREQ_E_NOT_OK   Copy request not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_RxTp_CallCopyRxData(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  CONSTP2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr,
  CONSTP2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_DATA) BufferSizePtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_TerminateReceive()
 *********************************************************************************************************************/
/*! \brief        Terminates active Rx TP session on a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx    Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    NormalClose Indicates if termination is initiated by close request.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_TerminateReceive(
  SoAd_SizeOfSoConType SoConIdx,
  boolean NormalClose);

/**********************************************************************************************************************
 *  SoAd_RxTp_CancelReceive()
 *********************************************************************************************************************/
/*! \brief      Requests PDU reception cancellation which is handled later in main function context.
 *  \details    -
 *  \param[in]  SockRouteDestIdx  Socket route destination index.
 *                                [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \return     E_OK              Cancellation request succeeded.
 *  \return     E_NOT_OK          Cancellation request failed.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_CancelReceive(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrReceiveHeader()
 *********************************************************************************************************************/
/*! \brief        Receives the PDU header for TP-PDUs and stores it in the TP reception buffer.
 *  \details      -
 *  \param[in]    SoConIdx          Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon(),
 *                                  SoAd_IsRxBufferConfigUsedOfSoCon(),
 *                                  SoAd_IsTpRxBufferUsedOfRxBufferConfig()]
 *  \param[in]    SockRouteDestIdx  Socket route destination index.
 *                                  [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in]    PduHdrBufPtr      Pointer to buffer where PDU header is stored.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \config       SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_TcpPduHdrReceiveHeader(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_DATA) PduHdrBufPtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrForwardPdu()
 *********************************************************************************************************************/
/*! \brief          Forwards a TP-PDU to user on TCP socket connections with enabled PDU header.
 *  \details        -
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon(),
 *                                      SoAd_IsRxBufferConfigUsedOfSoCon(),
 *                                      SoAd_IsTpRxBufferUsedOfRxBufferConfig()]
 *  \param[in,out]  ReleaseBufLenPtr    Pointer to buffer length to be released.
 *  \param[in]      TotalLen            Total length of received data.
 *  \return         E_OK                PDU forwarded completely.
 *  \return         E_NOT_OK            PDU not forwarded completely.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_TcpPduHdrForwardPdu(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  uint32 TotalLen);

# if ( SOAD_VERIFYRXPDUCBK == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrVerifyRxPdu()
 *********************************************************************************************************************/
/*! \brief      Verifies PDU reception for TP-PDU received over TCP socket connection with enabled PDU header.
 *  \details    -
 *  \param[in]  SoConIdx            Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \param[in]  ReleaseBufLen       Buffer length to be released.
 *  \param[in]  TotalLen            Total length of received data.
 *  \param[in]  PduHdrId            PDU header identifier.
 *  \param[in]  PduHdrLen           PDU header length.
 *  \return     E_OK                PDU verification succeeded or verification is disabled.
 *  \return     E_NOT_OK            PDU verification failed or not enough data for verfication is received.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP & SOAD_VERIFYRXPDUCBK
 *  \trace      DSGN-SoAdReceptionVerification
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_TcpPduHdrVerifyRxPdu(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 ReleaseBufLen,
  uint32 TotalLen,
  SoAd_PduHdrIdType PduHdrId,
  SoAd_PduHdrLenType PduHdrLen);

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrVerifyRxPduCall()
 *********************************************************************************************************************/
/*! \brief      Verifies a received PDU by calling a callback with reception dependent information and PDU data.
 *  \details    -
 *  \param[in]  SoConIdx            Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  BufIdx              Index of segmented buffer struct.
 *  \param[in]  BufLen              Total length of data in buffer starting at "BufIdx".
 *  \param[in]  PduHdrId            PDU Header ID.
 *  \param[in]  PduHdrLen           PDU Header length.
 *  \return     SOAD_E_OK           Rx PDU verification was successful.
 *  \return     SOAD_E_NOT_OK       Rx PDU verification was not successful.
 *  \return     SOAD_E_PENDING      Rx PDU verification is pending since not enough data have been received yet.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \config     SOAD_TCP & SOAD_VERIFYRXPDUCBK
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_ReturnType, SOAD_CODE) SoAd_RxTp_TcpPduHdrVerifyRxPduCall(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 BufIdx,
  uint32 BufLen,
  SoAd_PduHdrIdType PduHdrId,
  SoAd_PduHdrLenType PduHdrLen);

#  if ( SOAD_VERIFYRXPDUBUF == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrVerifyRxPduRetrieveData()
 *********************************************************************************************************************/
/*! \brief      Retrieves data from reception buffer struct to verify a PDU.
 *  \details    -
 *  \param[in]  SoConIdx            Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  BufIdx              Index of segmented buffer struct.
 *  \param[in]  PduHdrLen           PDU Header length.
 *  \param[out] PduInfoPtr          Pointer to PDU.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \config     SOAD_TCP & SOAD_VERIFYRXPDUCBK & SOAD_VERIFYRXPDUBUF
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_TcpPduHdrVerifyRxPduRetrieveData(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 BufIdx,
  SoAd_PduHdrLenType PduHdrLen,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);
#  endif /* SOAD_VERIFYRXPDUBUF == STD_ON */
# endif /* SOAD_VERIFYRXPDUCBK == STD_ON */

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrStartOfReception()
 *********************************************************************************************************************/
/*! \brief      Handles StartOfReception for TP-PDU on TCP socket connection with enabled PDU header.
 *  \details    -
 *  \param[in]  SoConIdx            Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \param[in]  PduHdrLen           PDU header length.
 *  \return     E_OK                StartOfReception succeeded or TP reception is already active.
 *  \return     E_NOT_OK            StartOfReception failed.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_TcpPduHdrStartOfReception(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PduHdrLenType PduHdrLen);

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrCopyRxData()
 *********************************************************************************************************************/
/*! \brief          Handles forwarding received data via CopyRxData for TP-PDU on TCP socket connection with enabled
 *                  PDU header.
 *  \details        -
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \param[in,out]  ReleaseBufLenPtr    Pointer to buffer length to be released.
 *  \return         E_OK                PDU copied completely.
 *  \return         E_NOT_OK            PDU not copied completely or an error occurred.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_TcpPduHdrCopyRxData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrCopyRxDataCalculateLength()
 *********************************************************************************************************************/
/*! \brief          Calculates length of data to be copied with CopyRxData for TP-PDU on TCP socket connection with
 *                  enabled PDU header.
 *  \details        -
 *  \param[in]      SoConIdx        Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      BufSegLen       Current TCP buffer segment length.
 *  \param[in,out]  PduLengthPtr    Pointer to PDU segment length which can be copied.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
/* PRQA S 779 4 */ /* MD_MSR_Rule5.2 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_TcpPduHdrCopyRxDataCalculateLength(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 BufSegLen,
  P2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_VAR) PduLengthPtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrCopyRxDataCall()
 *********************************************************************************************************************/
/*! \brief          Calls CopyRxData to forward a received TP-PDU on TCP socket connection with enabled PDU header.
 *  \details        -
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \param[in,out]  ReleaseBufLenPtr    Pointer to buffer length to be released.
 *  \param[in]      PduInfoPtr          Pointer to PDU.
 *  \return         E_OK                PDU segment copied and new segment can be forwarded or PDU received completely.
 *  \return         E_NOT_OK            No new PDU segment can be forwarded or an error occurred.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
/* PRQA S 779 4 */ /* MD_MSR_Rule5.2 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_TcpPduHdrCopyRxDataCall(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpReceivePdu()
 *********************************************************************************************************************/
/*! \brief          Handles data received on a TCP socket connection and forwards it via TP-API.
 *  \details        -
 *  \param[in]      SoConIdx          Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon(),
 *                                    SoAd_IsRxBufStructMgtUsedOfSoCon()]
 *  \param[in]      BufPtr            Pointer to TCP segment.
 *  \param[in]      Length            Length of TCP segment.
 *  \param[in,out]  ReleaseBufLenPtr  Pointer to buffer length to be released.
 *  \param[out]     ErrorIdPtr        Pointer to error identifier (set if error occurred).
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_TcpReceivePdu(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_DATA) ReleaseBufLenPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpForwardPdu()
 *********************************************************************************************************************/
/*! \brief          Forwards data received on a TCP socket connection via TP-API.
 *  \details        -
 *  \param[in]      SoConIdx          Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon(),
 *                                    SoAd_IsRxBufStructMgtUsedOfSoCon()]
 *  \param[in,out]  ReleaseBufLenPtr  Pointer to buffer length to be released.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_TcpForwardPdu(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_DATA) ReleaseBufLenPtr);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpPduHdrStartOfReception()
 *********************************************************************************************************************/
/*! \brief      Handles StartOfReception for TP-PDU on UDP socket connection with enabled PDU header.
 *  \details    -
 *  \param[in]  SoConIdx          Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \param[in]  SockRouteDestIdx  Socket route destination index.
 *                                [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in]  PduHdrLen         PDU header length.
 *  \return     E_OK              StartOfReception succeeded.
 *  \return     E_NOT_OK          StartOfReception failed or TP reception is already active.
 *  \pre        -
 *  \context    ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_UdpPduHdrStartOfReception(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  SoAd_PduHdrLenType PduHdrLen);

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpPduHdrCopyRxData()
 *********************************************************************************************************************/
/*! \brief      Handles forwarding of received data via CopyRxData for TP-PDU on UDP socket connection with enabled PDU
 *              header.
 *  \details    -
 *  \param[in]  SoConIdx          Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \param[in]  SockRouteDestIdx  Socket route destination index.
 *                                [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in]  BufPtr            Pointer to received UDP frame with offset to current PDU data (without PDU header).
 *  \pre        -
 *  \context    ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_UdpPduHdrCopyRxData(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpPduHdrCopyRxDataCall()
 *********************************************************************************************************************/
/*! \brief          Calls CopyRxData to forward a received TP-PDU segment on UDP socket connection with enabled PDU
 *                  header.
 *  \details        Finishes TP-PDU reception in case of error or if PDU is received completely.
 *  \param[in]      SoConIdx          Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \param[in]      SockRouteDestIdx  Socket route destination index.
 *                                    [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in,out]  ReadDataLenPtr    Pointer to length of read data in UDP frame.
 *  \param[in,out]  PduInfoPtr        Pointer to PDU segment as input and to available buffer size of user on return.
 *  \return         E_OK              Call to CopyRxData succeeded and reception can be continued.
 *  \return         E_NOT_OK          Call to CopyRxData failed or user has no available buffer anymore.
 *  \pre            -
 *  \context        ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_UdpPduHdrCopyRxDataCall(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) ReadDataLenPtr,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpPduHdrCopyDataToBuffer()
 *********************************************************************************************************************/
/*! \brief      Copies pending TP-PDU data to TP reception buffer or finishes TP reception if buffer size is not
 *              sufficient.
 *  \details    -
 *  \param[in]  SoConIdx          Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon(),
 *                                SoAd_IsRxBufferConfigUsedOfSoCon(),
 *                                SoAd_IsTpRxBufferUsedOfRxBufferConfig()]
 *  \param[in]  SockRouteDestIdx  Socket route destination index.
 *                                [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in]  BufPtr            Pointer to received UDP frame with offset to current PDU data segmnent.
 *  \pre        -
 *  \context    ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_UdpPduHdrCopyDataToBuffer(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpReceivePdu()
 *********************************************************************************************************************/
/*! \brief      Handles data received on a UDP socket connection and forwards it via TP-API.
 *  \details    -
 *  \param[in]  SockRouteDestIdx  Socket route destination index.
 *                                [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest(),
 *                                SoAd_IsRxMgtUsedOfSoCon(), SoAd_IsRxBufferConfigUsedOfSoCon(),
 *                                SoAd_IsTpRxBufferUsedOfRxBufferConfig()]
 *  \param[in]  BufPtr            Pointer to received UDP frame.
 *  \param[in]  Length            Length of UDP frame.
 *  \pre        -
 *  \context    ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_UdpReceivePdu(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length);

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpCopyData()
 *********************************************************************************************************************/
/*! \brief      Copies TP-PDU data to TP reception buffer in case PDU is not forwarded completely to user.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxBufferConfigUsedOfSoCon(),
 *                              SoAd_IsTpRxBufferUsedOfRxBufferConfig()]
 *  \param[in]  BufPtr          Pointer to received UDP frame.
 *  \param[in]  Length          Length of UDP frame.
 *  \pre        -
 *  \context    ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_UdpCopyData(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length);

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpForwardPdu()
 *********************************************************************************************************************/
/*! \brief      Forwards a TP-PDU to user on UDP socket connections.
 *  \details    -
 *  \param[in]  SockRouteDestIdx  Socket route destination index.
 *                                [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in]  BufPtr            Pointer to received UDP frame.
 *  \param[in]  Length            Length of UDP frame.
 *  \pre        -
 *  \context    ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_UdpForwardPdu(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length);

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpForwardPduCopyRxData()
 *********************************************************************************************************************/
/*! \brief          Calls CopyRxData to forward a TP-PDU to user on UDP socket connections.
 *  \details        -
 *  \param[in]      SockRouteDestIdx    Socket route destination index.
 *                                      [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in]      BufPtr              Pointer to received UDP frame.
 *  \param[in]      Length              Length of UDP frame.
 *  \param[in,out]  PduInfoPtr          Pointer to PDU segment as input and to available buffer size of user on return.
 *  \return         ContinueReception   Indicates if reception can be continued.
 *  \pre            -
 *  \context        ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_RxTp_UdpForwardPduCopyRxData(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_HandleReception()
 *********************************************************************************************************************/
/*! \brief      Handles TP reception in main function context.
 *  \details    -
 *  \param[out] ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_HandleReception(
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_HandleReceptionOnSoCon()
 *********************************************************************************************************************/
/*! \brief      Handles TP reception in main function context on a specific socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \param[out] ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_HandleReceptionOnSoCon(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxTp_HandleCancellation()
 *********************************************************************************************************************/
/*! \brief      Handles TP reception cancellation in main function context.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_HandleCancellation(
  SoAd_SizeOfSoConType SoConIdx);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxTp_HandleReceptionOnSoConTcp()
 *********************************************************************************************************************/
/*! \brief      Handles TP reception in main function context on a specific TCP socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxBufStructMgtUsedOfSoCon()]
 *  \param[out] ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
/* PRQA S 779 3 */ /* MD_MSR_Rule5.2 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_HandleReceptionOnSoConTcp(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_RxTp_HandleReceptionOnSoConUdp()
 *********************************************************************************************************************/
/*! \brief      Handles TP reception in main function context on a specific UDP socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon(),
 *                              SoAd_IsRxBufferConfigUsedOfSoCon(),
 *                              SoAd_IsTpRxBufferUsedOfRxBufferConfig()]]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
/* PRQA S 779 2 */ /* MD_MSR_Rule5.2 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_HandleReceptionOnSoConUdp(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_RxTp_HandleReceptionOnSoConUdpCopyRxData()
 *********************************************************************************************************************/
/*! \brief          Forwards TP reception data in main function context on a specific UDP socket connection to upper
 *                  layer by calling CopyRxData.
 *  \details        -
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon(),
 *                                      SoAd_IsRxBufferConfigUsedOfSoCon(),
 *                                      SoAd_IsTpRxBufferUsedOfRxBufferConfig()]
 *  \param[in]      SockRouteDestIdx    Socket route destination index.
 *                                      [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in,out]  PduInfoPtr          Pointer to PDU segment as input and to available buffer size of user on return.
 *  \return         ContinueReception   Indicates if reception can be continued.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
/* PRQA S 779 4 */ /* MD_MSR_Rule5.2 */
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_RxTp_HandleReceptionOnSoConUdpCopyRxData(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxTcp_SkipData()
 *********************************************************************************************************************/
/*! \brief        Skips received TCP data which are marked to be skipped in a previous reception.
 *  \details      -
 *  \param[in]    SockIdx           Module internal socket index.
 *                                  [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]    Length            Length of received data.
 *  \param[out]   SkippedLengthPtr  Pointer to length of skipped data.
 *  \return       E_OK              All required data are skipped and reception can be continued.
 *  \return       E_NOT_OK          Data to be skipped are still pending.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE for different socket indexes, FALSE for same socket index.
 *  \config       SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_SkipData(
  SoAd_SizeOfSocketType SockIdx,
  uint16 Length,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) SkippedLengthPtr);

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrRxIndication()
 *********************************************************************************************************************/
/*! \brief        Receives data from TCP socket connection with enabled PDU header.
 *  \details      Use BufPtr as NULL_PTR and Length with 0 to indicate that no data received in case of TP-API.
 *  \param[in]    SoConIdx    Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon(),
 *                            SoAd_IsRxBufStructMgtUsedOfSoCon()]
 *  \param[in]    BufPtr      Pointer to received TCP segment
 *  \param[in]    Length      Length of received TCP segment.
 *  \param[out]   ErrorIdPtr  Pointer to error identifier (set if error occurred).
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \config       SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTcp_PduHdrRxIndication(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrReceivePdu()
 *********************************************************************************************************************/
/*! \brief          Tries to extract a PDU from data received on a TCP socket connection with enabled PDU header.
 *  \details        -
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \param[in,out]  ReleaseBufLenPtr    Pointer to buffer length to be released.
 *  \param[in]      TotalLen            Total length of received data.
 *  \param[out]     ErrorIdPtr          Pointer to error identifier (set if error occurred).
 *  \return         E_OK                PDU extracted and forwarded completely and successfully.
 *  \return         E_NOT_OK            PDU not extracted completely or an error occured.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_PduHdrReceivePdu(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  uint32 TotalLen,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrReceiveHeader()
 *********************************************************************************************************************/
/*! \brief          Tries to extract PDU header from data received on a TCP socket connection with enabled PDU header
 *                  and finds the corresponding socket route.
 *  \details        -
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in,out]  ReleaseBufLenPtr    Pointer to buffer length to be released.
 *  \param[in]      TotalLen            Total length of received data.
 *  \param[out]     ErrorIdPtr          Pointer to error identifier (set if error occurred).
 *  \return         E_OK                PDU header extracted completely and the corresponding socket route is found.
 *  \return         E_NOT_OK            PDU header not extracted completely or an error occured.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_PduHdrReceiveHeader(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  uint32 TotalLen,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrFindSocketRouteAndReceiveHeader()
 *********************************************************************************************************************/
/*! \brief          Tries to find a socket route for a received PDU header and processes them if one is found.
 *  \details        -
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      PduHdrBufPtr        Pointer to buffer where the PDU header is stored.
 *                                      [range: PduHdrBufPtr points to 8 byte header]
 *  \param[out]     ErrorIdPtr          Pointer to error identifier (set if error occurred).
 *  \return         E_OK                Socket route was found.
 *  \return         E_NOT_OK            Socket route was not found.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_PduHdrFindSocketRouteAndReceiveHeader(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_DATA) PduHdrBufPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrFindSocketRouteDestAndReceiveHeader()
 *********************************************************************************************************************/
/*! \brief          Tries to find a socket route destination for a received PDU header and processes them if one is
 *                  found.
 *  \details        -
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      SockRouteIdx        Socket route index.
 *                                      [range: SockRouteIdx < SoAd_GetSizeOfSocketRoute()]
 *  \param[in]      PduHdrBufPtr        Pointer to buffer where the PDU header is stored.
 *                                      [range: PduHdrBufPtr points to 8 byte header]
 *  \param[out]     ErrorIdPtr          Pointer to error identifier (set if error occurred).
 *  \return         E_OK                Socket route destination was found.
 *  \return         E_NOT_OK            Socket route destination was not found.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_PduHdrFindSocketRouteDestAndReceiveHeader(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteType SockRouteIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_DATA) PduHdrBufPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrSkipData()
 *********************************************************************************************************************/
/*! \brief          Skips received data in error case (e.g. a PDU which has no corresponding socket route).
 *  \details        -
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in,out]  ReleaseBufLenPtr    Pointer to buffer length to be released.
 *  \param[in]      TotalLen            Total length of received data.
 *  \return         E_OK                Data skipped so that reception can be continued.
 *  \return         E_NOT_OK            No data skipped or more data than received have to be skipped.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_PduHdrSkipData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  uint32 TotalLen);

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrReceiveData()
 *********************************************************************************************************************/
/*! \brief          Tries to extract and forward PDU data from data received on a TCP socket connection with enabled
 *                  PDU header.
 *  \details        -
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \param[in,out]  ReleaseBufLenPtr    Pointer to buffer length to be released.
 *  \param[in]      TotalLen            Total length of received data.
 *  \param[out]     ErrorIdPtr          Pointer to error identifier (set if error occurred).
 *  \return         E_OK                PDU forwarded completely.
 *  \return         E_NOT_OK            PDU forwarded not completely or an error occurred.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_PduHdrReceiveData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  uint32 TotalLen,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxTcp_RxIndication()
 *********************************************************************************************************************/
/*! \brief        Receives data from TCP socket connection.
 *  \details      Use BufPtr as NULL_PTR and Length with 0 to indicate that no data received in case of TP-API.
 *  \param[in]    SoConIdx    Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon(),
 *                            SoAd_IsRxBufStructMgtUsedOfSoCon()]
 *  \param[in]    BufPtr      Pointer to received TCP segment or oldest segment in case of call from main function.
 *  \param[in]    Length      Length of TCP segment.
 *  \param[out]   ErrorIdPtr  Pointer to error identifier (set if error occurred).
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \config       SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTcp_RxIndication(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_RxUdp_PduHdrRxIndication()
 *********************************************************************************************************************/
/*! \brief        Receives data from UDP socket connection with enabled PDU header.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \param[in]    BufPtr          Pointer to received UDP frame.
 *  \param[in]    Length          Length of UDP frame.
 *  \param[out]   ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \pre          -
 *  \context      ISR2
 *  \reentrant    FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxUdp_PduHdrRxIndication(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxUdp_PduHdrCheckAllHeaderLength()
 *********************************************************************************************************************/
/*! \brief      Checks all PDU header located in a UDP frame.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  BufPtr          Pointer to received UDP frame.
 *  \param[in]  Length          Length of UDP frame.
 *  \return     E_OK            All PDU header are valid.
 *  \return     E_NOT_OK        At least one PDU header is invalid.
 *  \pre        -
 *  \context    ISR2
 *  \reentrant  FALSE
 *  \trace      DSGN-SoAdReception
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxUdp_PduHdrCheckAllHeaderLength(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length);

/**********************************************************************************************************************
 *  SoAd_RxUdp_PduHdrCheckHeaderLength()
 *********************************************************************************************************************/
/*! \brief      Checks next PDU header located in a UDP frame.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  BufPtr          Pointer to received UDP frame.
 *  \param[in]  Length          Length of UDP frame.
 *  \param[in]  ReadDataLen     Length of read data in UDP frame.
 *  \param[out] PduHdrLenPtr    Pointer to extraced PDU header length.
 *  \return     E_OK            PDU header length is valid.
 *  \return     E_NOT_OK        PDU header length is invalid.
 *  \pre        -
 *  \context    ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxUdp_PduHdrCheckHeaderLength(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  uint16 ReadDataLen,
  P2VAR(SoAd_PduHdrLenType, AUTOMATIC, SOAD_APPL_VAR) PduHdrLenPtr);

/**********************************************************************************************************************
 *  SoAd_RxUdp_PduHdrReceiveHeader()
 *********************************************************************************************************************/
/*! \brief        Extracts PDU header from UDP frame and searches for the corresponding socket route destination.
 *  \details      -
 *  \param[in]    SoConIdx            Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    BufPtr              Pointer to received UDP frame with offset to current PDU header.
 *  \param[out]   SockRouteDestIdxPtr Pointer to socket route destination index.
 *  \param[out]   ErrorIdPtr          Pointer to error identifier (set if error occurred).
 *  \return       E_OK                Socket route destination for PDU header ID found.
 *  \return       E_NOT_OK            No socket route destination for PDU header ID found.
 *  \pre          -
 *  \context      ISR2
 *  \reentrant    FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxUdp_PduHdrReceiveHeader(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(SoAd_SizeOfSocketRouteDestType, AUTOMATIC, SOAD_APPL_VAR) SockRouteDestIdxPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxUdp_PduHdrFindSocketRouteDest()
 *********************************************************************************************************************/
/*! \brief        Tries to find a socket route destination for a received PDU header.
 *  \details      -
 *  \param[in]    SockRouteIdx        Socket route index.
 *                                    [range: SockRouteIdx < SoAd_GetSizeOfSocketRoute()]
 *  \param[out]   SockRouteDestIdxPtr Pointer to socket route destination index.
 *  \return       E_OK                Socket route destination found.
 *  \return       E_NOT_OK            No socket route destination found.
 *  \pre          -
 *  \context      ISR2
 *  \reentrant    FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxUdp_PduHdrFindSocketRouteDest(
  SoAd_SizeOfSocketRouteType SockRouteIdx,
  P2VAR(SoAd_SizeOfSocketRouteDestType, AUTOMATIC, SOAD_APPL_VAR) SockRouteDestIdxPtr);

/**********************************************************************************************************************
 *  SoAd_RxUdp_PduHdrReceiveData()
 *********************************************************************************************************************/
/*! \brief        Tries to forward PDU data of a PDU received in a UDP frame with enabled PDU header.
 *  \details      -
 *  \param[in]    SoConIdx          Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxMgtUsedOfSoCon()]
 *  \param[in]    SockRouteDestIdx  Socket route destination index.
 *                                  [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \param[in]    BufPtr            Pointer to received UDP frame with offset to current PDU header.
 *  \param[out]   ErrorIdPtr        Pointer to error identifier (set if error occurred).
 *  \pre          -
 *  \context      ISR2
 *  \reentrant    FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxUdp_PduHdrReceiveData(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RxUdp_RxIndication()
 *********************************************************************************************************************/
/*! \brief        Receives data from UDP socket connection.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    BufPtr          Pointer to received UDP frame.
 *  \param[in]    Length          Length of UDP frame.
 *  \param[out]   ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \pre          -
 *  \context      ISR2
 *  \reentrant    FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxUdp_RxIndication(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxBufStruct_Init()
 *********************************************************************************************************************/
/*! \brief      Initializes a rx buffer struct.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE for different rx buffer structs, FALSE for same rx buffer struct.
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxBufStruct_Init(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_WriteSegment()
 *********************************************************************************************************************/
/*! \brief      Writes segment to rx buffer struct to get a local image of the lower layer segmented TCP buffer.
 *  \details    Supports segments and merging if received data is located directly behind the previously received
 *              segment (i.e. ring buffer logic).
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxBufStructMgtUsedOfSoCon()]
 *  \param[in]  SrcBufPtr       Pointer to linear source buffer.
 *  \param[in]  SrcBufLen       Length of linear source buffer.
 *  \return     E_OK            Writing to rx buffer struct succeeded.
 *  \return     E_NOT_OK        Writing to rx buffer struct failed.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE for different rx buffer structs, FALSE for same rx buffer struct.
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxBufStruct_WriteSegment(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) SrcBufPtr,
  uint16 SrcBufLen);

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_WriteAdditionalSegment()
 *********************************************************************************************************************/
/*! \brief      Writes addtional segment to rx buffer struct.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxBufStructMgtUsedOfSoCon()]
 *  \param[in]  SrcBufPtr       Pointer to linear source buffer.
 *  \param[in]  SrcBufLen       Length of linear source buffer.
 *  \return     E_OK            Writing to rx buffer struct succeeded.
 *  \return     E_NOT_OK        Writing to rx buffer struct failed.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE for different rx buffer structs, FALSE for same rx buffer struct.
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxBufStruct_WriteAdditionalSegment(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) SrcBufPtr,
  uint16 SrcBufLen);

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_CalculateNextSegment()
 *********************************************************************************************************************/
/*! \brief      Calculates next segment depending on a segment index and level.
 *  \details    -
 *  \param[in]  SoConIdx          Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  SegmentIndex      Index of segment from which calculation starts.
 *  \param[in]  SegmentLvl        Fill level of rx buffer struct.
 *  \return     NextSegmentIndex  Calculated next index.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_SizeOfRxBufStructSegType, SOAD_CODE) SoAd_RxBufStruct_CalculateNextSegment(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfRxBufStructSegType SegmentIndex,
  SoAd_RxBufStructSegLvlOfRxBufStructMgtType SegmentLvl);

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_GetSegment()
 *********************************************************************************************************************/
/*! \brief      Gets segment of rx buffer struct depending on offset considering all segments.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  BufSegOffset    Offset in rx buffer struct considering all segments.
 *  \param[out] BufSegPtr       Pointer to buffer in segment.
 *  \param[out] BufSegLenPtr    Pointer to segment length.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE for different rx buffer structs, FALSE for same rx buffer struct.
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxBufStruct_GetSegment(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 BufSegOffset,
  P2VAR(uint8*, AUTOMATIC, SOAD_APPL_VAR) BufSegPtr,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) BufSegLenPtr);

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_GetTotLen()
 *********************************************************************************************************************/
/*! \brief      Gets length of all segments in rx buffer struct starting at specified offset.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  BufSegOffset    Offset in rx buffer struct considering all segments.
 *  \return     TotalLen        Total length of all segments starting at specified offset.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(uint32, SOAD_CODE) SoAd_RxBufStruct_GetTotLen(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 BufSegOffset);

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_Copy2Buf()
 *********************************************************************************************************************/
/*! \brief      Copies segments of rx buffer struct to a provided buffer.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  BufPtr          Pointer to provided buffer.
 *  \param[in]  BufLen          Length of data to be copied to provided buffer.
 *  \param[in]  BufSegOffset    Offset in rx buffer struct considering all segments.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxBufStruct_Copy2Buf(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, SOAD_APPL_DATA, SOAD_APPL_DATA) BufPtr,
  uint32 BufLen,
  uint32 BufSegOffset);

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_GetBufSegIdx()
 *********************************************************************************************************************/
/*! \brief          Gets the buffer segment index and segment offset of a rx buffer struct considering a total offset
 *                  of rx buffer struct.
 *  \details        -
 *  \param[in]      SoConIdx        Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in,out]  OffsetPtr       Pointer to offset considering all segments which is overwritten by segment offset.
 *  \param[out]     BufSegIdxPtr    Pointer to buffer segment index.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \config         SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxBufStruct_GetBufSegIdx(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) OffsetPtr,
  P2VAR(SoAd_SizeOfRxBufStructSegType, AUTOMATIC, SOAD_APPL_VAR) BufSegIdxPtr);

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_ReleaseSegment()
 *********************************************************************************************************************/
/*! \brief      Releases a specified length of rx buffer struct.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(), SoAd_IsRxBufStructMgtUsedOfSoCon()]
 *  \param[in]  Len             Length of data to be released.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxBufStruct_ReleaseSegment(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 Len);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_Rx_RxIndicationProtocol()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_Rx_RxIndicationProtocol(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  uint16 skippedLength = 0u;
#endif /* SOAD_TCP == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Handle reception for TCP socket connection (if enabled). */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
  {
    /* #100 Skip data if required by a previous erroneous reception. */
    if ( SoAd_RxTcp_SkipData(SoAd_GetSocketIdxOfSoCon(SoConIdx), Length, &skippedLength) == E_OK )                     /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      /* #1000 Handle reception for TCP socket connection with PDU header (if enabled). */
      if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
      {
        SoAd_RxTcp_PduHdrRxIndication(SoConIdx, &BufPtr[skippedLength], (uint16)(Length - skippedLength), ErrorIdPtr); /* SBSW_SOAD_POINTER_FORWARD */
      }
      /* #1001 Handle reception for TCP socket connection without PDU header. */
      else
      {
        SoAd_RxTcp_RxIndication(SoConIdx, &BufPtr[skippedLength], (uint16)(Length - skippedLength), ErrorIdPtr);       /* SBSW_SOAD_POINTER_FORWARD */
      }
    }
  }
  else
#endif /* SOAD_TCP == STD_ON */
  /* #11 Handle reception for UDP socket connection. */
  {
    /* #110 Handle reception for UDP socket connection with PDU header (if enabled). */
    if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
    {
      SoAd_RxUdp_PduHdrRxIndication(SoConIdx, BufPtr, Length, ErrorIdPtr);                                             /* SBSW_SOAD_POINTER_FORWARD */
    }
    /* #111 Handle reception for UDP socket connection without PDU header. */
    else
    {
      SoAd_RxUdp_RxIndication(SoConIdx, BufPtr, Length, ErrorIdPtr);                                                   /* SBSW_SOAD_POINTER_FORWARD */
    }
  }
} /* SoAd_Rx_RxIndicationProtocol() */

/**********************************************************************************************************************
 *  SoAd_Rx_CheckSocketParameter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_CheckSocketParameter(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType      soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx);
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx);
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if IP address is assigned. */
  if ( SoAd_GetIpAddrStateOfLocalAddrDyn(localAddrIdx) == SOAD_IPADDR_STATE_ASSIGNED )
  {
    /* #20 Check if socket is established. */
    if ( SoAd_GetStateOfSocketDyn(SockIdx) == SOAD_SOCK_STATE_ESTABLISHED )
    {
      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_Rx_CheckSocketParameter() */

/**********************************************************************************************************************
 *  SoAd_Rx_GetSoConIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_GetSoConIdx(
  SoAd_SizeOfSocketType SockIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx);
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Return first socket connection related to socket in case of TCP (if enabled). */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) )
  {
    *SoConIdxPtr = soConIdx;                                                                                           /* SBSW_SOAD_POINTER_WRITE */
    retVal = E_OK;
  }
  else
#endif /* SOAD_TCP == STD_ON */
  /* #20 Use best match algorithm to get socket connection in case message acceptance filter is enabled otherwise. */
  if ( SoAd_IsMsgAcceptFilterEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) )
  {
    if ( SoAd_Rx_GetSoConIdxByBestMatchAlg(soConIdx, RemoteAddrPtr, BufPtr, Length, &soConIdx) == E_OK )               /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    {
      *SoConIdxPtr = soConIdx;                                                                                         /* SBSW_SOAD_POINTER_WRITE */
      retVal = E_OK;
    }
  }
  /* #30 Return first and only socket connection otherwise. */
  else
  {
    *SoConIdxPtr = soConIdx;                                                                                           /* SBSW_SOAD_POINTER_WRITE */
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_Rx_GetSoConIdx() */

/**********************************************************************************************************************
 *  SoAd_Rx_CheckSoConParameter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_CheckSoConParameter(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if at least one socket route is configured. */
  if ( SoAd_IsSocketRouteUsedOfSoCon(SoConIdx) )
  {
    /* #20 Check if socket connection is not requested to be closed. */
    if ( SoAd_GetCloseModeOfSoConDyn(SoConIdx) == SOAD_CLOSE_NONE )
    {
      /* #30 Check if socket connection is online. */
      if ( SoAd_GetModeOfSoConDyn(SoConIdx) == SOAD_SOCON_ONLINE )
      {
        retVal = E_OK;
      }
      /* #31 Try to open socket connection on reception otherwise. */
      else
      {
        retVal = SoAd_SoCon_OpenSoConOnReception(SoConIdx, RemoteAddrPtr);                                             /* SBSW_SOAD_POINTER_FORWARD */
      }
    }
  }

  return retVal;
} /* SoAd_Rx_CheckSoConParameter() */

/**********************************************************************************************************************
 *  SoAd_Rx_GetSoConIdxByBestMatchAlg()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_GetSoConIdxByBestMatchAlg(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdxListSize = 0u;
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that the list of best matching socket connections becomes inconsistent. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Try to get list of all matching socket connection. */
  if ( SoAd_SoCon_GetSoConIdxListByBestMatchAlg(SoConIdx, SOAD_SOCON_FILTER_DISABLED, RemoteAddrPtr,
    &soConIdxListSize) == E_OK )                                                                                       /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
  {
    /* #30 Check if best match algorithm shall consider PDU header. */
    if ( SoAd_IsBestMatchWithPduHeaderEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
    {
      /* #300 Check if at least PDU header is received. */
      if ( Length >= SOAD_PDU_HDR_SIZE )
      {
        /* #3000 Return first matching socket connection which has a socket route with matching PDU header. */
        retVal = SoAd_Rx_GetSoConIdxByBestMatchAlgWithPduHdr(BufPtr, soConIdxListSize, SoConIdxPtr);                   /* SBSW_SOAD_POINTER_FORWARD */
      }
    }
    /* #40 Check if best match algorithm shall consider socket route existence. */
    else if ( SoAd_IsBestMatchWithSockRouteEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
    {
      /* #400 Return first matching socket connection which has a socket route configured. */
      retVal = SoAd_Rx_GetSoConIdxByBestMatchAlgWithSocketRoute(soConIdxListSize, SoConIdxPtr);                        /* SBSW_SOAD_POINTER_FORWARD */
    }
    /* #50 Handle best match algorithm as specified by AUTOSAR otherwise. */
    else
    {
      /* #500 Return first matching socket connection. */
      *SoConIdxPtr = SoAd_GetSoConIdxOfBestMatchSoConIdxList(0u);                                                      /* SBSW_SOAD_POINTER_WRITE */
      retVal = E_OK;
    }
  }
#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
  /* #60 Increment the dropped UDP frame counter, when no matching UDP socket connection could be found. */
  if ( retVal == E_NOT_OK )
  {
    SoAd_Measure_Inc(SOAD_MEAS_DROP_UDP_FRAME, 1);
  }
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

  /* #70 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_Rx_GetSoConIdxByBestMatchAlg() */

/**********************************************************************************************************************
 *  SoAd_Rx_GetSoConIdxByBestMatchAlgWithPduHdr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_GetSoConIdxByBestMatchAlgWithPduHdr(
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  SoAd_SizeOfSoConType SoConIdxListSize,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConIterType              soConIter;
  SoAd_SizeOfSoConType            soConIdx;
  SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx = 0u;
  uint8                           errorId = SOAD_E_NO_ERROR;
  Std_ReturnType                  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all matching socket connections. */
  for ( soConIter = 0u; soConIter < SoConIdxListSize; soConIter++ )
  {
    soConIdx = SoAd_GetSoConIdxOfBestMatchSoConIdxList(soConIter);

    /* #20 Check if a socket route with matching PDU header ID is configured. */
    if ( SoAd_RxUdp_PduHdrReceiveHeader(soConIdx, BufPtr, &sockRouteDestIdx, &errorId) == E_OK )                       /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    {
      /* #30 Return first matching socket connection. */
      *SoConIdxPtr = soConIdx;                                                                                         /* SBSW_SOAD_POINTER_WRITE */
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* SoAd_Rx_GetSoConIdxByBestMatchAlgWithPduHdr() */

/**********************************************************************************************************************
 *  SoAd_Rx_GetSoConIdxByBestMatchAlgWithSocketRoute()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_GetSoConIdxByBestMatchAlgWithSocketRoute(
  SoAd_SizeOfSoConType SoConIdxListSize,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConIterType    soConIter;
  SoAd_SizeOfSoConType  soConIdx;
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all matching socket connections. */
  for ( soConIter = 0u; soConIter < SoConIdxListSize; soConIter++ )
  {
    soConIdx = SoAd_GetSoConIdxOfBestMatchSoConIdxList(soConIter);

    /* #20 Check if at least one socket route is configured. */
    if ( SoAd_IsSocketRouteUsedOfSoCon(soConIdx) )
    {
      /* #30 Return first machting socket connection. */
      *SoConIdxPtr = soConIdx;                                                                                         /* SBSW_SOAD_POINTER_WRITE */
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* SoAd_Rx_GetSoConIdxByBestMatchAlgWithSocketRoute() */

/**********************************************************************************************************************
 *  SoAd_Rx_FindSocketRouteOnSoConByPduHdrId()
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
/* PRQA S 3673 5 */ /* MD_SoAd_ConstCausedByUnused */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_FindSocketRouteOnSoConByPduHdrId(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PduHdrIdType PduHdrId,
  P2VAR(SoAd_SizeOfSocketRouteType, AUTOMATIC, SOAD_APPL_DATA) SocketRouteIdxPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketRouteType  sockRouteIdxLeft = SoAd_GetSocketRouteStartIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketRouteType  sockRouteIdxRight =
    (SoAd_SizeOfSocketRouteType)(SoAd_GetSocketRouteEndIdxOfSoCon(SoConIdx) - 1u);
  SoAd_SizeOfSocketRouteType  sockRouteIdxMiddle;
  boolean                     stopSearch = FALSE;
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  *SocketRouteIdxPtr = SoAd_GetSizeOfSocketRoute();                                                                    /* SBSW_SOAD_POINTER_WRITE */

  /* #10 Do a binary search over all socket routes of the socket connection. */
  while ( sockRouteIdxLeft <= sockRouteIdxRight )
  {
    /* #20 Calculate middle index. */
    sockRouteIdxMiddle = sockRouteIdxLeft +
      (SoAd_SizeOfSocketRouteType)((SoAd_SizeOfSocketRouteType)(sockRouteIdxRight - sockRouteIdxLeft) / 2u);

    /* #30 Check if received PDU header ID equals the PDU header ID of the socket route. */
    if ( PduHdrId == SoAd_GetRxPduHdrIdOfSocketRoute(sockRouteIdxMiddle) )
    {
      *SocketRouteIdxPtr = sockRouteIdxMiddle;                                                                         /* SBSW_SOAD_POINTER_WRITE */
      stopSearch = TRUE;
      retVal = E_OK;
    }
    /* #31 Check if whole range was checked and stop search if no element was found otherwise. */
    else if ( sockRouteIdxLeft == sockRouteIdxRight )
    {
      stopSearch = TRUE;
    }
    /* #32 Calculate next indexes otherwise. */
    else
    {
      if ( SoAd_GetRxPduHdrIdOfSocketRoute(sockRouteIdxMiddle) > PduHdrId )
      {
        /* continue search on left side */
        sockRouteIdxRight = (sockRouteIdxMiddle == SoAd_GetSocketRouteStartIdxOfSoCon(SoConIdx)) ?
          sockRouteIdxMiddle : ((SoAd_SizeOfSocketRouteType)(sockRouteIdxMiddle - 1u));
      }
      else
      {
        /* continue search on right side */
        sockRouteIdxLeft = sockRouteIdxMiddle + 1u;
      }
    }

    if ( stopSearch == TRUE )
    {
      break;
    }
  }

#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #40 Set error if no socket route could be found (if error detection is enabled). */
  if ( (retVal == E_NOT_OK) && (*ErrorIdPtr == SOAD_E_NO_ERROR) )
  {
    *ErrorIdPtr = SOAD_E_INV_PDUHEADER_ID;                                                                             /* SBSW_SOAD_POINTER_WRITE */
  }
#else
  SOAD_DUMMY_STATEMENT(ErrorIdPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */

  return retVal;
} /* SoAd_Rx_FindSocketRouteOnSoConByPduHdrId() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxIf_TcpPduHdrReceiveHeader()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxIf_TcpPduHdrReceiveHeader(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_DATA) PduHdrBufPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduHdrLenType            pduHdrLen;
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxMgtType          rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxBufferConfigType rxBufCfgIdx = SoAd_GetRxBufferConfigIdxOfSoCon(SoConIdx);
  Std_ReturnType                retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT32(PduHdrBufPtr, SOAD_PDU_HDR_ID_SIZE, pduHdrLen);                                                    /* SBSW_SOAD_POINTER_FORWARD */

  /* #10 Check if IF reception buffer size is sufficient for received PDU. */
  /* PRQA S 4391 2 */ /* MD_SoAd_GenericWiderTypeCast */
  /* Optional indirection: Refer to parameter value range in function description. */
  if ( (pduHdrLen + SOAD_PDU_HDR_SIZE) <= (SoAd_PduHdrLenType)(SoAd_GetIfRxBufferEndIdxOfRxBufferConfig(rxBufCfgIdx) -
    SoAd_GetIfRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx)) )
  {
    /* #20 Set reception of PDU to active on socket connection. */
    SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SockRouteDestIdx);                                                     /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #30 Copy PDU header to IF reception buffer. */
    /* Optional indirection: Refer to parameter value range in function description. */
    /* PRQA S 314 4 */ /* MD_MSR_VStdLibCopy */
    VStdMemCpy(                                                                                                        /* SBSW_SOAD_CONST_POINTER_AND_OPTIONAL_POINTER_FORWARD_CSL03 */
      (P2VAR(void, AUTOMATIC, SOAD_APPL_VAR))
        SoAd_GetAddrIfRxBuffer(SoAd_GetIfRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx)),
      (P2CONST(void, AUTOMATIC, SOAD_APPL_DATA))PduHdrBufPtr,
      SOAD_PDU_HDR_SIZE);
    SoAd_SetIfRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx,                                                              /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_GetIfRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx) + SOAD_PDU_HDR_SIZE);

    retVal = E_OK;
  }
  /* #40 Drop PDU since reception buffer size is not sufficient. */
  else
  {
# if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
    /* #50 Increment the dropped TCP PDU counter (if GetResetMeasurementData API is enabled). */
    SoAd_Measure_Inc(SOAD_MEAS_DROP_TCP, 1);
# endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

# if ( SOAD_DEV_ERROR_DETECT == STD_ON )
    /* #60 Mark as error detected. (if error detection is enabled). */
    *ErrorIdPtr = SOAD_E_NOBUFS;                                                                                       /* SBSW_SOAD_POINTER_WRITE */
# else
    SOAD_DUMMY_STATEMENT(ErrorIdPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  }

  return retVal;
} /* SoAd_RxIf_TcpPduHdrReceiveHeader() */

/**********************************************************************************************************************
 *  SoAd_RxIf_TcpPduHdrCopyData()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxIf_TcpPduHdrCopyData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  uint32 TotalLen,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduHdrLenType            pduHdrLen;
  uint32                        bufSegLen = 0u;
  uint32                        releaseBufLen = *ReleaseBufLenPtr;
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxBufferConfigType rxBufCfgIdx = SoAd_GetRxBufferConfigIdxOfSoCon(SoConIdx);
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfIfRxBufferType     ifRxBufferStartIdx = SoAd_GetIfRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx);
  SoAd_SizeOfIfRxBufferType     ifRxBufferLength = SoAd_GetIfRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx) -
    ifRxBufferStartIdx;
  Std_ReturnType                retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT32(SoAd_GetAddrIfRxBuffer(ifRxBufferStartIdx), SOAD_PDU_HDR_ID_SIZE, pduHdrLen);                      /* SBSW_SOAD_OPTIONAL_CSL03 */

  /* #10 Get current buffer segment (sets data pointer to TcpIp buffer segment). */
  SoAd_RxBufStruct_GetSegment(SoConIdx, releaseBufLen, &PduInfoPtr->SduDataPtr, &bufSegLen);                           /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */

  /* #20 Check if PDU is received within one TCP segment. */
  if ( (pduHdrLen <= bufSegLen) && (ifRxBufferLength == SOAD_PDU_HDR_SIZE) )
  {
    /* #200 Release TcpIp buffer for PDU. */
    releaseBufLen += pduHdrLen;

    /* #201 Set data structure length (data pointer is already set in call to SoAd_RxBufStruct_GetSegment()). */
    PduInfoPtr->SduLength = (PduLengthType)pduHdrLen;                                                                  /* SBSW_SOAD_POINTER_WRITE */

    retVal = E_OK;
  }
  /* #30 Handle reception if PDU is received in multiple TCP segments. */
  else
  {
    uint32 bytesToCopy;

    /* #300 Calculate length of PDU segment to be copied to IF reception buffer. */
    bytesToCopy = (pduHdrLen + SOAD_PDU_HDR_SIZE) - ifRxBufferLength;
    if ( bytesToCopy > (TotalLen - releaseBufLen) )
    {
      bytesToCopy = TotalLen - releaseBufLen;
    }

    /* #301 Copy PDU segment to IF reception buffer. */
    SoAd_RxBufStruct_Copy2Buf(SoConIdx,                                                                                /* SBSW_SOAD_POINTER_FORWARD_IfRxBuffer */
      SoAd_GetAddrIfRxBuffer(SoAd_GetIfRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx)),
      bytesToCopy,
      releaseBufLen);

    ifRxBufferLength += (SoAd_SizeOfIfRxBufferType)bytesToCopy;
    SoAd_SetIfRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx, ifRxBufferStartIdx + ifRxBufferLength);                      /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #302 Release TcpIp buffer for PDU segment. */
    releaseBufLen += bytesToCopy;

    /* #303 Check if entire PDU is now copied to the IF reception buffer. */
    if ( ifRxBufferLength == (pduHdrLen + SOAD_PDU_HDR_SIZE) )
    {
      /* #304 Set data structure to start of PDU data in IF reception buffer. */
      PduInfoPtr->SduDataPtr = SoAd_GetAddrIfRxBuffer(ifRxBufferStartIdx + SOAD_PDU_HDR_SIZE);                         /* SBSW_SOAD_POINTER_WRITE */
      /* PRQA S 4391 1 */ /* MD_SoAd_GenericWiderTypeCast */
      PduInfoPtr->SduLength = (PduLengthType)(ifRxBufferLength - SOAD_PDU_HDR_SIZE);                                   /* SBSW_SOAD_POINTER_WRITE */
      retVal = E_OK;
    }
  }

  *ReleaseBufLenPtr = releaseBufLen;                                                                                   /* SBSW_SOAD_POINTER_WRITE */

  return retVal;
} /* SoAd_RxIf_TcpPduHdrCopyData() */

/**********************************************************************************************************************
 *  SoAd_RxIf_TcpPduHdrForwardPdu()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxIf_TcpPduHdrForwardPdu(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxBufferConfigType   rxBufCfgIdx = SoAd_GetRxBufferConfigIdxOfSoCon(SoConIdx);
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxMgtType            rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx = SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx);
  SoAd_SizeOfSocketRouteType      sockRouteIdx = SoAd_GetSocketRouteIdxOfSocketRouteDest(sockRouteDestIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add meta data to PDU (if enabled). */
  if ( SoAd_RxIf_AddMetaDataToPdu(SoConIdx, sockRouteIdx, PduInfoPtr, ErrorIdPtr) == E_OK )                            /* SBSW_SOAD_POINTER_FORWARD */
  {
    /* #20 Forward PDU to user. */
    SoAd_GetIfRxIndicationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfSocketRouteDest(sockRouteDestIdx))(                   /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetRxPduIdOfSocketRouteDest(sockRouteDestIdx),
      PduInfoPtr);
  }

  /* #30 Release IF reception buffer. */
  SoAd_SetIfRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx, SoAd_GetIfRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx));      /* SBSW_SOAD_OPTIONAL_CSL03 */

  /* #40 Finish reception of IF-PDU. */
  SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SoAd_GetSizeOfSocketRouteDest());                                        /* SBSW_SOAD_OPTIONAL_CSL03 */
} /* SoAd_RxIf_TcpPduHdrForwardPdu() */

/**********************************************************************************************************************
 *  SoAd_RxIf_TcpReceivePdu()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxIf_TcpReceivePdu(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType                 pduInfo;
  SoAd_SizeOfSocketRouteType  SockRouteIdx = SoAd_GetSocketRouteIdxOfSocketRouteDest(SockRouteDestIdx);

  /* ----- Implementation ----------------------------------------------- */
  pduInfo.SduDataPtr = BufPtr;
  pduInfo.SduLength = (PduLengthType)Length;

  /* #10 Add meta data to PDU (if enabled). */
  if ( SoAd_RxIf_AddMetaDataToPdu(SoConIdx, SockRouteIdx, &pduInfo, ErrorIdPtr) == E_OK )                              /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
  {
    /* #20 Forward PDU to user. */
    SoAd_GetIfRxIndicationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfSocketRouteDest(SockRouteDestIdx))(                   /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetRxPduIdOfSocketRouteDest(SockRouteDestIdx),
      &pduInfo);
  }
} /* SoAd_RxIf_TcpReceivePdu() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_RxIf_UdpPduHdrForwardPdu()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxIf_UdpPduHdrForwardPdu(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  SoAd_PduHdrLenType PduHdrLen,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType                 pduInfo;
  SoAd_SizeOfSocketRouteType  sockRouteIdx = SoAd_GetSocketRouteIdxOfSocketRouteDest(SockRouteDestIdx);

  /* ----- Implementation ----------------------------------------------- */
  pduInfo.SduDataPtr = &BufPtr[SOAD_PDU_HDR_SIZE];
  pduInfo.SduLength = (PduLengthType)PduHdrLen;

  /* #10 Add meta data to PDU (if enabled). */
  if ( SoAd_RxIf_AddMetaDataToPdu(SoConIdx, sockRouteIdx, &pduInfo, ErrorIdPtr) == E_OK )                              /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
  {
    /* #20 Forward PDU to user. */
    SoAd_GetIfRxIndicationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfSocketRouteDest(SockRouteDestIdx))(                   /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetRxPduIdOfSocketRouteDest(SockRouteDestIdx),
      &pduInfo);
  }
} /* SoAd_RxIf_UdpPduHdrForwardPdu() */

/**********************************************************************************************************************
 *  SoAd_RxIf_UdpReceivePdu()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxIf_UdpReceivePdu(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketRouteType  sockRouteIdx = SoAd_GetSocketRouteIdxOfSocketRouteDest(SockRouteDestIdx);
  SoAd_SizeOfSoConType        soConIdx = SoAd_GetSoConIdxOfSocketRoute(sockRouteIdx);
  PduInfoType                 pduInfo;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert whole UDP frame to a PDU. */
  pduInfo.SduDataPtr = &BufPtr[0];
  pduInfo.SduLength = (PduLengthType)Length;

  /* #20 Add meta data to PDU (if enabled). */
  if ( SoAd_RxIf_AddMetaDataToPdu(soConIdx, sockRouteIdx, &pduInfo, ErrorIdPtr) == E_OK )                              /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
  {
    /* #30 Forward PDU to user. */
    SoAd_GetIfRxIndicationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfSocketRouteDest(SockRouteDestIdx))(                   /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetRxPduIdOfSocketRouteDest(SockRouteDestIdx),
      &pduInfo);
  }
} /* SoAd_RxIf_UdpReceivePdu() */

/**********************************************************************************************************************
 *  SoAd_RxIf_AddMetaDataToPdu()
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
/* PRQA S 3673 5 */ /* MD_SoAd_ConstCausedByUnused */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxIf_AddMetaDataToPdu(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteType SockRouteIdx,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConIdType soConId = SoAd_GetSoConIdOfSoCon(SoConIdx);
  Std_ReturnType   retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if meta data are enabled for this RxPdu. */
  if ( SoAd_IsMetaDataRxEnabledOfSocketRoute(SockRouteIdx) )
  {
    /* #20 Check if buffer size is sufficient. */
    if ( (PduLengthType)(PduInfoPtr->SduLength + SOAD_RX_META_DATA_LEN) <= SoAd_GetSizeOfMetaDataRxBuf() )
    {
      /* #30 Copy PDU to meta data buffer. */
      /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(                                                                                                      /* SBSW_SOAD_POINTER_AND_POINTER_FORWARD_CSL01 */
        (SOAD_P2VAR(void))SoAd_GetAddrMetaDataRxBuf(0u),
        (SOAD_P2VAR(void))PduInfoPtr->SduDataPtr,
        PduInfoPtr->SduLength);

      /* #40 Copy meta data (i.e. SoConId) to meta data buffer. */
      SoAd_SetMetaDataRxBuf(PduInfoPtr->SduLength, (uint8)(soConId >> 8u));                                            /* SBSW_SOAD_CSL01 */
      SoAd_SetMetaDataRxBuf(PduInfoPtr->SduLength + 1u, (uint8)(soConId));                                             /* SBSW_SOAD_CSL01 */

      /* #50 Overwrite PDU info pointer. */
      PduInfoPtr->SduDataPtr = SoAd_GetAddrMetaDataRxBuf(0u);                                                          /* SBSW_SOAD_POINTER_WRITE */
      PduInfoPtr->SduLength += SOAD_RX_META_DATA_LEN;                                                                  /* SBSW_SOAD_POINTER_WRITE */
    }
    else
    {
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
      *ErrorIdPtr = SOAD_E_NOBUFS;                                                                                     /* SBSW_SOAD_POINTER_WRITE */
#else
      SOAD_DUMMY_STATEMENT(ErrorIdPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
      retVal = E_NOT_OK;
    }
  }

#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
  /* #21 Drop PDU if PDU size exceeds the meta data buffer size. */
  if ( retVal == E_NOT_OK )
  {
# if ( SOAD_TCP == STD_ON )
    if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) == TRUE )
    {
      /* #210 Increment the dropped TCP PDU counter for a TCP connection (if GetResetMeasurementData API is enabled). */
      SoAd_Measure_Inc(SOAD_MEAS_DROP_TCP, 1);
    }
    else
# endif /* SOAD_TCP == STD_ON */
    {
      /* #211 Increment the dropped UDP PDU counter for a UDP connection (if GetResetMeasurementData API is enabled). */
      SoAd_Measure_Inc(SOAD_MEAS_DROP_UDP, 1);
    }
  }
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

  return retVal;
} /* SoAd_RxIf_AddMetaDataToPdu() */

/**********************************************************************************************************************
 *  SoAd_RxTp_StartOfReception()
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
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_StartOfReception(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if PDU header is not configured (if disabled). */
  if ( !SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
  {
    /* #20 Check if a socket route is configured. */
    if ( SoAd_IsSocketRouteUsedOfSoCon(SoConIdx) )
    {
      SoAd_SizeOfSocketRouteType      sockRouteIdx = SoAd_GetSocketRouteStartIdxOfSoCon(SoConIdx);
      SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx = SoAd_GetSocketRouteDestStartIdxOfSocketRoute(sockRouteIdx);

      /* #30 Check if socket route has TP-API (there is only one socket route in case of TP and no PDU header). */
      if ( SoAd_GetUpperLayerApiOfSocketRoute(sockRouteIdx) == SOAD_UL_API_TP )
      {
        PduLengthType dummyLen = 0u;

        /* #40 Call StartOfReception for the first socket route destination (there is only one in case of TP). */
        if ( SoAd_RxTp_CallStartOfReception(sockRouteDestIdx, 0u, &dummyLen) == BUFREQ_OK )                            /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
        {
          /* #400 Set TP session to active if call succeeded. */
          /* Optional indirection: Refer to Safe BSW assumption SoCon -> RxMgt. */
          SoAd_SetSocketRouteDestIdxOfRxMgt(SoAd_GetRxMgtIdxOfSoCon(SoConIdx), sockRouteDestIdx);                      /* SBSW_SOAD_OPTIONAL_CSL03 */
        }
        else
        {
          /* #401 Set close mode and add event to the socket connection state queue otherwise. */
          SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_OFFLINE_RESET);                                             /* SBSW_SOAD_PARAMETER_IDX */
          SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);

          retVal = E_NOT_OK;
        }
      }
    }
  }

  return retVal;
} /* SoAd_RxTp_StartOfReception() */

/**********************************************************************************************************************
 *  SoAd_RxTp_CallStartOfReception()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_RxTp_CallStartOfReception(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  PduLengthType TpSduLength,
  CONSTP2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_DATA) BufferSizePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfUpperLayerType upperLayerIdx = SoAd_GetUpperLayerIdxOfSocketRouteDest(SockRouteDestIdx);
  BufReq_ReturnType         retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call StartOfReception function with non-constant pointer if configured. */
  if ( SoAd_GetTpStartOfReceptionCbkOfUpperLayer(upperLayerIdx) != NULL_PTR )
  {
    retVal = SoAd_GetTpStartOfReceptionCbkOfUpperLayer(upperLayerIdx)(                                                 /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetRxPduIdOfSocketRouteDest(SockRouteDestIdx),
      NULL_PTR,
      TpSduLength,
      BufferSizePtr);
  }
  /* #20 Call StartOfReception function with constant pointer otherwise. */
  else
  {
    retVal = SoAd_GetTpStartOfReceptionConstCbkOfUpperLayer(upperLayerIdx)(                                            /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetRxPduIdOfSocketRouteDest(SockRouteDestIdx),
      NULL_PTR,
      TpSduLength,
      BufferSizePtr);
  }

  return retVal;
} /* SoAd_RxTp_CallStartOfReception() */

/**********************************************************************************************************************
 *  SoAd_RxTp_CallCopyRxData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_RxTp_CallCopyRxData(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  CONSTP2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr,
  CONSTP2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_DATA) BufferSizePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfUpperLayerType upperLayerIdx = SoAd_GetUpperLayerIdxOfSocketRouteDest(SockRouteDestIdx);
  BufReq_ReturnType         retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call CopyRxData function with non-constant pointer if configured. */
  if ( SoAd_GetTpCopyRxDataCbkOfUpperLayer(upperLayerIdx) != NULL_PTR )
  {
    retVal = SoAd_GetTpCopyRxDataCbkOfUpperLayer(upperLayerIdx)(                                                       /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetRxPduIdOfSocketRouteDest(SockRouteDestIdx), PduInfoPtr, BufferSizePtr);
  }
  /* #20 Call CopyRxData function with constant pointer otherwise. */
  else
  {
    retVal = SoAd_GetTpCopyRxDataConstCbkOfUpperLayer(upperLayerIdx)(                                                  /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetRxPduIdOfSocketRouteDest(SockRouteDestIdx), PduInfoPtr, BufferSizePtr);
  }

  return retVal;
} /* SoAd_RxTp_CallCopyRxData() */

/**********************************************************************************************************************
 *  SoAd_RxTp_TerminateReceive()
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
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_TerminateReceive(
  SoAd_SizeOfSoConType SoConIdx,
  boolean NormalClose)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRxMgtType            rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx = SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx);
  Std_ReturnType                  retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if TP reception is active on socket connection. */
  if ( (sockRouteDestIdx != SoAd_GetSizeOfSocketRouteDest()) &&
    (SoAd_GetUpperLayerApiOfSocketRoute(SoAd_GetSocketRouteIdxOfSocketRouteDest(sockRouteDestIdx)) == SOAD_UL_API_TP) )
  {
    /* #20 Handle termination in case termination is initiated by close request. */
    if ( NormalClose == TRUE )
    {
      /* #200 Terminate TP reception on UDP socket connection if data to be received are pending. */
      if ( SoAd_IsSocketUdpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) &&
        (SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) != 0u) )
      {
        /* #2000 Set negative result for TpRxIndication. */
        retVal = E_NOT_OK;
      }
#if ( SOAD_TCP == STD_ON )
      /* #201 Terminate TP reception on TCP socket connection if data to be received are pending (if enabled). */
      else if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) &&
        (SoAd_GetRxBufStructSegLvlOfRxBufStructMgt(SoAd_GetRxBufStructMgtIdxOfSoCon(SoConIdx)) != 0u) )
      {
        /* #2010 Set negative result for TpRxIndication. */
        retVal = E_NOT_OK;
      }
#endif /* SOAD_TCP == STD_ON */
      /* #202 Terminate TP reception on socket connection if data received completely. */
      else
      {
        /* #2020 Set positive result for TpRxIndication. */
        retVal = E_OK;
      }
    }
    /* #21 Handle termination in all other cases. */
    else
    {
      /* #210 Set negative result for TpRxIndication. */
      retVal = E_NOT_OK;
    }

    /* #30 Call TpRxIndication with corresponding result. */
    SoAd_GetTpRxIndicationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfSocketRouteDest(sockRouteDestIdx))(                   /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetRxPduIdOfSocketRouteDest(sockRouteDestIdx),
      retVal);
  }
} /* SoAd_RxTp_TerminateReceive() */

/**********************************************************************************************************************
 *  SoAd_RxTp_CancelReceive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_CancelReceive(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketRouteType  sockRouteIdx = SoAd_GetSocketRouteIdxOfSocketRouteDest(SockRouteDestIdx);
  SoAd_SizeOfSoConType        soConIdx = SoAd_GetSoConIdxOfSocketRoute(sockRouteIdx);
  /* Optional indirection: Refer to Safe BSW assumption SoCon -> RxMgt. */
  SoAd_SizeOfRxMgtType        rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(soConIdx);
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if PDU reception is active on socket connection. */
  if ( SockRouteDestIdx == SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx) )
  {
    /* #20 Set flag to perform cancellation. */
    SoAd_SetCancelRequestedOfRxMgt(rxMgtIdx, TRUE);                                                                    /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #30 Set event to handle PDU (i.e. cancellation) in main function. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_TP_RX_SO_CON, soConIdx);

    retVal = E_OK;
  }

  return retVal;
} /* SoAd_RxTp_CancelReceive() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrReceiveHeader()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_TcpPduHdrReceiveHeader(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_DATA) PduHdrBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxMgtType          rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxBufferConfigType rxBufCfgIdx = SoAd_GetRxBufferConfigIdxOfSoCon(SoConIdx);
  /* Optional indirection: Refer to Safe BSW assumption RxBufferConfig -> TpRxBuffer. */
  SoAd_SizeOfTpRxBufferType     tpRxBufferIdx = SoAd_GetTpRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set reception of PDU to active on socket connection. */
  SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SockRouteDestIdx);                                                       /* SBSW_SOAD_OPTIONAL_CSL03 */

  /* #20 Copy PDU header to TP reception buffer. */
  /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
  VStdMemCpy(                                                                                                          /* SBSW_SOAD_CONST_POINTER_AND_OPTIONAL_POINTER_FORWARD_CSL03 */
    SOAD_A_P2VAR(void)SoAd_GetAddrTpRxBuffer(tpRxBufferIdx),
    SOAD_A_P2CONST(void)PduHdrBufPtr,
    SOAD_PDU_HDR_SIZE);
} /* SoAd_RxTp_TcpPduHdrReceiveHeader() */

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrForwardPdu()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_TcpPduHdrForwardPdu(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  uint32 TotalLen)
{
  /* ----- Local Variables ---------------------------------------------- */
# if ( SOAD_VERIFYRXPDUCBK == STD_ON )
  SoAd_PduHdrIdType             pduHdrId;
# endif /* SOAD_VERIFYRXPDUCBK == STD_ON */
  SoAd_PduHdrLenType            pduHdrLen;
  SoAd_SizeOfRxBufferConfigType rxBufCfgIdx = SoAd_GetRxBufferConfigIdxOfSoCon(SoConIdx);
  SoAd_SizeOfTpRxBufferType     tpRxBufferStartIdx = SoAd_GetTpRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx);
  Std_ReturnType                retVal = SOAD_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
# if ( SOAD_VERIFYRXPDUCBK == STD_ON )
  IPBASE_GET_UINT32(SoAd_GetAddrTpRxBuffer(tpRxBufferStartIdx), 0u, pduHdrId);                                         /* SBSW_SOAD_CONST_POINTER_FORWARD */
# endif /* SOAD_VERIFYRXPDUCBK == STD_ON */
  IPBASE_GET_UINT32(SoAd_GetAddrTpRxBuffer(tpRxBufferStartIdx), SOAD_PDU_HDR_ID_SIZE, pduHdrLen);                      /* SBSW_SOAD_CONST_POINTER_FORWARD */

  /* #10 Verify Rx PDU (if enabled). */
# if ( SOAD_VERIFYRXPDUCBK == STD_ON )
  if ( SoAd_RxTp_TcpPduHdrVerifyRxPdu(SoConIdx, *ReleaseBufLenPtr, TotalLen, pduHdrId, pduHdrLen) == E_OK )
# else
  SOAD_DUMMY_STATEMENT(TotalLen); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif /* SOAD_VERIFYRXPDUCBK == STD_ON */
  {
    /* #20 Call StartOfReception. */
    if ( SoAd_RxTp_TcpPduHdrStartOfReception(SoConIdx, pduHdrLen) == E_OK )
    {
      /* #30 Copy data by calling CopyRxData. */
      retVal = SoAd_RxTp_TcpPduHdrCopyRxData(SoConIdx, ReleaseBufLenPtr);                                              /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  return retVal;
} /* SoAd_RxTp_TcpPduHdrForwardPdu() */

# if ( SOAD_VERIFYRXPDUCBK == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrVerifyRxPdu()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_TcpPduHdrVerifyRxPdu(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 ReleaseBufLen,
  uint32 TotalLen,
  SoAd_PduHdrIdType PduHdrId,
  SoAd_PduHdrLenType PduHdrLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxMgtType  rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  Std_ReturnType        retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Rx PDU verification is enabled and reception has not been started yet. */
  if ( SoAd_IsVerifyRxPduEnabledOfSoCon(SoConIdx) && (SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) == 0u) )
  {
    /* #20 Verify Rx PDU. */
    retVal = SoAd_RxTp_TcpPduHdrVerifyRxPduCall(SoConIdx, ReleaseBufLen, (uint32)(TotalLen - ReleaseBufLen), PduHdrId,
      PduHdrLen);

#  if ( SOAD_VERIFYRXPDUBUF == STD_ON )
    /* #30 Wait for more data if not enough data were received to verify Rx PDU. */
    if ( retVal == SOAD_E_PENDING )
    {
      retVal = E_NOT_OK;
    }
    else
#  endif /* SOAD_VERIFYRXPDUBUF == STD_ON */
    /* #31 Skip PDU if verification failed. */
    if ( retVal == SOAD_E_NOT_OK )
    {
      SoAd_SetSkipBytesOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx), PduHdrLen);                                     /* SBSW_SOAD_CSL03_CSL02 */
      SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SoAd_GetSizeOfSocketRouteDest());                                    /* SBSW_SOAD_OPTIONAL_CSL03 */
    }
    /* #32 Continue reception if verification succeeded. */
    else
    {
      /* Nothing to do. */
    }
  }
  /* #11 Continue reception otherwise. */
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_RxTp_TcpPduHdrVerifyRxPdu() */

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrVerifyRxPduCall()
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
/* PRQA S 3206 6 */ /* MD_SoAd_UnusedParameter */
SOAD_LOCAL_INLINE FUNC(SoAd_ReturnType, SOAD_CODE) SoAd_RxTp_TcpPduHdrVerifyRxPduCall(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 BufIdx,
  uint32 BufLen,
  SoAd_PduHdrIdType PduHdrId,
  SoAd_PduHdrLenType PduHdrLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Use always IPv6 type to optimize precompile variants. */
  SoAd_SockAddrInet6Type  localSockAddr = { 0u, 0u, { 0u, 0u, 0u, 0u } };
  SoAd_SockAddrInet6Type  remSockAddr = { 0u, 0u, { 0u, 0u, 0u, 0u } };
#  if ( SOAD_VERIFYRXPDUBUF == STD_ON )
  PduInfoType             pduInfo = { NULL_PTR, 0u };
#  endif /* SOAD_VERIFYRXPDUBUF == STD_ON */
  SoAd_ReturnType         retVal = SOAD_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
#  if ( SOAD_VERIFYRXPDUBUF == STD_ON )
  /* #10 Indicate that data reception is pending if not enough data to verify is received (if buffer is enabled). */
  if ( (BufLen < SoAd_GetSizeOfVerifyRxPduBuf()) && (BufLen < PduHdrLen) )
  {
    retVal = SOAD_E_PENDING;
  }
  else
#  endif /* SOAD_VERIFYRXPDUBUF == STD_ON */
  /* #11 Continue verification otherwise. */
  {
    /* #110 Retrieve local socket address. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_SoCon_GetLocalSockAddr(SoConIdx, SOAD_A_P2VAR(SoAd_SockAddrType)&localSockAddr);                              /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

    /* #111 Retrieve remote socket address. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_SoCon_GetRemoteSockAddr(SoConIdx, SOAD_A_P2VAR(SoAd_SockAddrType)&remSockAddr);                               /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

#  if ( SOAD_VERIFYRXPDUBUF == STD_ON )
    /* #112 Retrieve data and call verification callback (if buffer is enabled). */
    SoAd_RxTp_TcpPduHdrVerifyRxPduRetrieveData(SoConIdx, BufIdx, PduHdrLen, &pduInfo);                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

    /* PRQA S 310 3 */ /* MD_SoAd_PointerCastOnStruct */
    if ( SoAd_GetVerifyRxPduCbk(0u)(                                                                                   /* SBSW_SOAD_FUNCTION_PTR */
      SOAD_A_P2CONST(SoAd_SockAddrType)&localSockAddr,
      SOAD_A_P2CONST(SoAd_SockAddrType)&remSockAddr,
      PduHdrId,
      SOAD_A_P2CONST(PduInfoType)&pduInfo) == E_OK )
    {
      retVal = SOAD_E_OK;
    }
#  else
    /* #113 Call verification callback directly (otherwise). */
    /* PRQA S 310 3 */ /* MD_SoAd_PointerCastOnStruct */
    if ( SoAd_GetVerifyRxPduCbk(0u)(                                                                                   /* SBSW_SOAD_FUNCTION_PTR */
      SOAD_A_P2CONST(SoAd_SockAddrType)&localSockAddr,
      SOAD_A_P2CONST(SoAd_SockAddrType)&remSockAddr,
      PduHdrId,
      NULL_PTR) == E_OK )
    {
      retVal = SOAD_E_OK;
    }

    SOAD_DUMMY_STATEMENT(BufIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    SOAD_DUMMY_STATEMENT(BufLen); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    SOAD_DUMMY_STATEMENT(PduHdrLen); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif /* SOAD_VERIFYRXPDUBUF == STD_ON */
  }

  return retVal;
} /* SoAd_RxTp_TcpPduHdrVerifyRxPduCall() */

#  if ( SOAD_VERIFYRXPDUBUF == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrVerifyRxPduRetrieveData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_TcpPduHdrVerifyRxPduRetrieveData(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 BufIdx,
  SoAd_PduHdrLenType PduHdrLen,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 bufSegLen = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate length of data to be retrieved from reception buffer struct. */
  if ( PduHdrLen > SoAd_GetSizeOfVerifyRxPduBuf() )
  {
    PduInfoPtr->SduLength = (PduLengthType)SoAd_GetSizeOfVerifyRxPduBuf();                                             /* SBSW_SOAD_POINTER_WRITE */
  }
  else
  {
    PduInfoPtr->SduLength = (PduLengthType)PduHdrLen;                                                                  /* SBSW_SOAD_POINTER_WRITE */
  }

  /* #20 Get buffer segment. */
  SoAd_RxBufStruct_GetSegment(SoConIdx, BufIdx, &PduInfoPtr->SduDataPtr, &bufSegLen);                                  /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */

  /* #30 Copy data to linearization buffer if data to be retrieved is segmented. */
  if ( bufSegLen < PduInfoPtr->SduLength )
  {
    SoAd_RxBufStruct_Copy2Buf(SoConIdx, SoAd_GetAddrVerifyRxPduBuf(0u), PduInfoPtr->SduLength, BufIdx);                /* SBSW_SOAD_VARIABLE_POINTER_FORWARD_CSL01 */
    PduInfoPtr->SduDataPtr = SoAd_GetAddrVerifyRxPduBuf(0u);                                                           /* SBSW_SOAD_POINTER_WRITE */
  }
} /* SoAd_RxTp_TcpPduHdrVerifyRxPduRetrieveData() */
#  endif /* SOAD_VERIFYRXPDUBUF == STD_ON */
# endif /* SOAD_VERIFYRXPDUCBK == STD_ON */

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrStartOfReception()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_TcpPduHdrStartOfReception(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PduHdrLenType PduHdrLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx;
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxMgtType            rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  PduLengthType                   bufferSize = 0u;
  Std_ReturnType                  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if reception has not been started yet. */
  if ( SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) == 0u )
  {
    sockRouteDestIdx = SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx);

    /* #20 Call StartOfReception. */
    if ( SoAd_RxTp_CallStartOfReception(sockRouteDestIdx, (PduLengthType)PduHdrLen, &bufferSize) == BUFREQ_OK )        /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      /* #200 Indicate that reception can be continued if StartOfReception succeeded. */
      SoAd_SetRxBytesPendingOfRxMgt(rxMgtIdx, (PduLengthType)PduHdrLen);                                               /* SBSW_SOAD_OPTIONAL_CSL03 */
      retVal = E_OK;
    }
    else
    {
      /* #201 Skip PDU if StartOfReception failed. */
      SoAd_SetSkipBytesOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx), PduHdrLen);                                     /* SBSW_SOAD_CSL03_CSL02 */
      SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SoAd_GetSizeOfSocketRouteDest());                                    /* SBSW_SOAD_OPTIONAL_CSL03 */
    }
  }
  /* #11 Continue reception otherwise. */
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_RxTp_TcpPduHdrStartOfReception() */

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrCopyRxData()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_TcpPduHdrCopyRxData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType           pduInfo = { NULL_PTR, 0u };
  uint32                bufSegLen = 0u;
  SoAd_SizeOfRxMgtType  rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate to handle segmented data. */
  while ( SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) > 0u )
  {
    /* #20 Check if cancellation is not requested. */
    if ( !SoAd_IsCancelRequestedOfRxMgt(rxMgtIdx) )
    {
      /* #30 Get next linear buffer segment. */
      SoAd_RxBufStruct_GetSegment(SoConIdx, *ReleaseBufLenPtr, &pduInfo.SduDataPtr, &bufSegLen);                       /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

      /* #40 Check if a buffer segment is left (i.e. buffer contains data for reception). */
      if ( bufSegLen > 0u )
      {
        /* #50 Calculate available length of data to be copied in next CopyRxData call. */
        SoAd_RxTp_TcpPduHdrCopyRxDataCalculateLength(SoConIdx, bufSegLen, &pduInfo.SduLength);                         /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

        /* #60 Call CopyRxData. */
        retVal = SoAd_RxTp_TcpPduHdrCopyRxDataCall(SoConIdx, ReleaseBufLenPtr, &pduInfo);                              /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
    else
    {
      retVal = E_NOT_OK;
    }

    /* #70 Stop iteration if no data can be forwarded anymore. */
    if ( retVal == E_NOT_OK )
    {
      break;
    }
  }

  return retVal;
} /* SoAd_RxTp_TcpPduHdrCopyRxData() */

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrCopyRxDataCalculateLength()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_TcpPduHdrCopyRxDataCalculateLength(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 BufSegLen,
  P2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_VAR) PduLengthPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if this CopyRxData call is a consecutive call (length would be set otherwise). */
  if ( *PduLengthPtr > 0u )
  {
    /* #20 Set length to buffer segment length if buffer segment is smaller than length provided by user. */
    if ( *PduLengthPtr > BufSegLen )
    {
      *PduLengthPtr = (PduLengthType)BufSegLen;                                                                        /* SBSW_SOAD_POINTER_WRITE */
    }
    /* #30 Set length to pending PDU length if user provides more buffer than required for the PDU. */
    if ( *PduLengthPtr > SoAd_GetRxBytesPendingOfRxMgt(SoAd_GetRxMgtIdxOfSoCon(SoConIdx)) )
    {
      *PduLengthPtr = SoAd_GetRxBytesPendingOfRxMgt(SoAd_GetRxMgtIdxOfSoCon(SoConIdx));                                /* SBSW_SOAD_POINTER_WRITE */
    }
  }
} /* SoAd_RxTp_TcpPduHdrCopyRxDataCalculateLength() */

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpPduHdrCopyRxDataCall()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_TcpPduHdrCopyRxDataCall(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxMgtType            rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx = SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx);
  SoAd_SizeOfUpperLayerType       upperLayerIdx = SoAd_GetUpperLayerIdxOfSocketRouteDest(sockRouteDestIdx);
  PduLengthType                   bufferSize = 0u;
  Std_ReturnType                  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call CopyRxData and check if call succeeds. */
  if ( SoAd_RxTp_CallCopyRxData(sockRouteDestIdx, PduInfoPtr, &bufferSize) == BUFREQ_OK )                              /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    /* #100 Release copied data and reduce number of pending data. */
    *ReleaseBufLenPtr += PduInfoPtr->SduLength;                                                                        /* SBSW_SOAD_POINTER_WRITE */
    SoAd_SetRxBytesPendingOfRxMgt(rxMgtIdx, SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) - PduInfoPtr->SduLength);          /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #101 Check if data for reception is pending. */
    if ( SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) > 0u )
    {
      /* #1010 Store length and indicate that CopyRxData can be called again if user can receive more data. */
      if ( bufferSize > 0u )
      {
        PduInfoPtr->SduLength = bufferSize;                                                                            /* SBSW_SOAD_POINTER_WRITE */

        retVal = E_OK;
      }
    }
    /* #102 Finish PDU reception and call RxIndication otherwise. */
    else
    {
      SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SoAd_GetSizeOfSocketRouteDest());                                    /* SBSW_SOAD_OPTIONAL_CSL03 */

      SoAd_GetTpRxIndicationCbkOfUpperLayer(upperLayerIdx)(SoAd_GetRxPduIdOfSocketRouteDest(sockRouteDestIdx), E_OK);  /* SBSW_SOAD_FUNCTION_PTR */

      retVal = E_OK;
    }
  }
  /* #11 Handle reception if call to CopyRxData fails. */
  else
  {
    /* #110 Skip pending PDU. */
    SoAd_SetSkipBytesOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx), SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx));         /* SBSW_SOAD_CSL03_CSL02 */

    /* #111 Finish PDU reception and call RxIndication with negative result. */
    SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SoAd_GetSizeOfSocketRouteDest());                                      /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetRxBytesPendingOfRxMgt(rxMgtIdx, 0u);                                                                       /* SBSW_SOAD_OPTIONAL_CSL03 */

    SoAd_GetTpRxIndicationCbkOfUpperLayer(upperLayerIdx)(SoAd_GetRxPduIdOfSocketRouteDest(sockRouteDestIdx), E_NOT_OK);/* SBSW_SOAD_FUNCTION_PTR */
  }

  return retVal;
} /* SoAd_RxTp_TcpPduHdrCopyRxDataCall() */

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpReceivePdu()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_TcpReceivePdu(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_DATA) ReleaseBufLenPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRxMgtType rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if TP session is active. */
  if ( SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx) != SoAd_GetSizeOfSocketRouteDest() )
  {
    /* #20 Check if cancellation is not requested. */
    if ( !SoAd_IsCancelRequestedOfRxMgt(rxMgtIdx) )
    {
      /* #30 Add TCP segment to buffer struct. */
      if ( SoAd_RxBufStruct_WriteSegment(SoConIdx, BufPtr, Length) == E_OK )                                           /* SBSW_SOAD_POINTER_FORWARD */
      {
        /* #40 Handle reception of streaming PDU. */
        SoAd_RxTp_TcpForwardPdu(SoConIdx, ReleaseBufLenPtr);                                                           /* SBSW_SOAD_POINTER_FORWARD */
      }
      /* #31 Handle case if buffer struct size is not sufficient. */
      else
      {
        /* #310 Close socket connection in next main function. */
        SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_OFFLINE_RESET);                                               /* SBSW_SOAD_PARAMETER_IDX */
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);

        /* #311 Set error. */
# if ( SOAD_DEV_ERROR_DETECT == STD_ON )
        *ErrorIdPtr = SOAD_E_NOBUFS;                                                                                   /* SBSW_SOAD_POINTER_WRITE */
# else
        SOAD_DUMMY_STATEMENT(ErrorIdPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
      }
    }
  }
} /* SoAd_RxTp_TcpReceivePdu() */

/**********************************************************************************************************************
 *  SoAd_RxTp_TcpForwardPdu()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_TcpForwardPdu(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_DATA) ReleaseBufLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType                     pduInfo;
  PduLengthType                   bufferSize = 0u;
  uint32                          bufSegLen = 0u;
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxMgtType            rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx = SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx);
  boolean                         continueReception = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Make sure that first CopyRxData call is called with length 0 to get the available buffer size. */
  pduInfo.SduDataPtr = NULL_PTR;
  pduInfo.SduLength = 0u;

  /* #20 Iterate to continue reception until no data can be forwarded to user anymore. */
  while ( continueReception == TRUE )
  {
    /* #30 Call CopyRxData and check if call succeeds. */
    if ( SoAd_RxTp_CallCopyRxData(sockRouteDestIdx, &pduInfo, &bufferSize) == BUFREQ_OK )                              /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      /* #300 Release copied data. */
      *ReleaseBufLenPtr += pduInfo.SduLength;                                                                          /* SBSW_SOAD_POINTER_WRITE */

      /* #301 Get next TCP segment. */
      SoAd_RxBufStruct_GetSegment(SoConIdx, *ReleaseBufLenPtr, &pduInfo.SduDataPtr, &bufSegLen);                       /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */

      /* #302 Calculate available length of data to be copied in next CopyRxData call. */
      pduInfo.SduLength = (PduLengthType)bufSegLen;
      if ( pduInfo.SduLength > bufferSize )
      {
        pduInfo.SduLength = bufferSize;
      }

      /* #303 Stop iteration if no data to be copied is left. */
      if ( bufSegLen == 0u )
      {
        continueReception = FALSE;
      }
      /* #304 Make sure that reception is continued in next main function if user currently cannot receive more. */
      else if ( bufferSize == 0u )
      {
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_TP_RX_SO_CON, SoConIdx);
        continueReception = FALSE;
      }
      /* #305 Continue reception otherwise. */
      else
      {
        /* Nothing to do. */
      }
    }
    /* #31 Handle reception if call to CopyRxData fails. */
    else
    {
      /* #310 Close socket connection in next main function. */
      SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_OFFLINE_RESET);                                                 /* SBSW_SOAD_PARAMETER_IDX */
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);
      continueReception = FALSE;
    }
  }
} /* SoAd_RxTp_TcpForwardPdu() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpPduHdrStartOfReception()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_UdpPduHdrStartOfReception(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  SoAd_PduHdrLenType PduHdrLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduLengthType         bufferSize = 0u;
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxMgtType  rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if TP session is inactive. */
  if ( SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx) == SoAd_GetSizeOfSocketRouteDest() )
  {
    /* #20 Check if call to StartOfReception succeeds. */
    if ( SoAd_RxTp_CallStartOfReception(SockRouteDestIdx, (PduLengthType)PduHdrLen, &bufferSize) == BUFREQ_OK )        /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      /* #30 Set TP session to active. */
      SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SockRouteDestIdx);                                                   /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_SetRxBytesPendingOfRxMgt(rxMgtIdx, (PduLengthType)PduHdrLen);                                               /* SBSW_SOAD_OPTIONAL_CSL03 */

      retVal = E_OK;
    }
  }
  /* #11 Discard PDU otherwise. */
  else
  {
    /* Nothing to do. */
  }

  return retVal;
} /* SoAd_RxTp_UdpPduHdrStartOfReception() */

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpPduHdrCopyRxData()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_UdpPduHdrCopyRxData(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType           pduInfo;
  uint16                readDataLen = 0u;
  SoAd_SizeOfRxMgtType  rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  Std_ReturnType        retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Make sure that first CopyRxData call is called with length 0 to get the available buffer size. */
  pduInfo.SduLength = 0u;

  /* #20 Iterate until entire PDU is forwarded to upper layer. */
  while ( SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) > 0u )
  {
    /* #30 Check if cancellation is not requested. */
    if ( !SoAd_IsCancelRequestedOfRxMgt(rxMgtIdx) )
    {
      /* #40 Set data pointer to next PDU segment. */
      pduInfo.SduDataPtr = &BufPtr[readDataLen];

      /* #50 Calculate available length of data to be copied in next CopyRxData call. */
      if ( pduInfo.SduLength > 0u )
      {
        /* #500 Set length to pending PDU length if user provides more buffer than required for the PDU. */
        if ( pduInfo.SduLength > SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) )
        {
          pduInfo.SduLength = SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx);
        }
      }

      /* #60 Call CopyRxData. */
      retVal = SoAd_RxTp_UdpPduHdrCopyRxDataCall(SoConIdx, SockRouteDestIdx, &readDataLen, &pduInfo);                  /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    }
    else
    {
      retVal = E_NOT_OK;
    }

    /* #70 Stop reception if no data can be forwarded anymore. */
    if ( retVal == E_NOT_OK )
    {
      break;
    }
  }
} /* SoAd_RxTp_UdpPduHdrCopyRxData() */

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpPduHdrCopyRxDataCall()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTp_UdpPduHdrCopyRxDataCall(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) ReadDataLenPtr,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduLengthType         bufferSize = 0u;
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxMgtType  rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call CopyRxData and check if call succeeds. */
  if ( SoAd_RxTp_CallCopyRxData(SockRouteDestIdx, PduInfoPtr, &bufferSize) == BUFREQ_OK )                              /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
  {
    /* #100 Increase number of read data and reduce number of pending data. */
    *ReadDataLenPtr += (uint16)PduInfoPtr->SduLength;                                                                  /* SBSW_SOAD_POINTER_WRITE */
    SoAd_SetRxBytesPendingOfRxMgt(rxMgtIdx, SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) - PduInfoPtr->SduLength);          /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #101 Check if data for reception is pending. */
    if ( SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) > 0u )
    {
      /* #1010 Store length and indicate that CopyRxData can be called again if user can receive more data. */
      if ( bufferSize > 0u )
      {
        PduInfoPtr->SduLength = bufferSize;                                                                            /* SBSW_SOAD_POINTER_WRITE */

        retVal = E_OK;
      }
      /* #1011 Copy to local buffer otherwise to retry in main function again. */
      else
      {
        SoAd_RxTp_UdpPduHdrCopyDataToBuffer(SoConIdx, SockRouteDestIdx,                                                /* SBSW_SOAD_CONST_POINTER_FORWARD */
          &PduInfoPtr->SduDataPtr[PduInfoPtr->SduLength]);
      }
    }
    /* #102 Finish PDU reception and call RxIndication otherwise. */
    else
    {
      SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SoAd_GetSizeOfSocketRouteDest());                                    /* SBSW_SOAD_OPTIONAL_CSL03 */

      SoAd_GetTpRxIndicationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfSocketRouteDest(SockRouteDestIdx))(                 /* SBSW_SOAD_FUNCTION_PTR */
        SoAd_GetRxPduIdOfSocketRouteDest(SockRouteDestIdx), E_OK);

      retVal = E_OK;
    }
  }
  /* #11 Handle reception if call to CopyRxData fails. */
  else
  {
    /* #111 Finish PDU reception and call RxIndication with negative result. */
    SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SoAd_GetSizeOfSocketRouteDest());                                      /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetRxBytesPendingOfRxMgt(rxMgtIdx, 0u);                                                                       /* SBSW_SOAD_OPTIONAL_CSL03 */

    SoAd_GetTpRxIndicationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfSocketRouteDest(SockRouteDestIdx))(                   /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetRxPduIdOfSocketRouteDest(SockRouteDestIdx), E_NOT_OK);
  }

  return retVal;
} /* SoAd_RxTp_UdpPduHdrCopyRxDataCall() */

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpPduHdrCopyDataToBuffer()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_UdpPduHdrCopyDataToBuffer(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxMgtType          rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxBufferConfigType rxBufCfgIdx = SoAd_GetRxBufferConfigIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if TP reception buffer size is sufficient to store the pending PDU data. */
  if ( SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) <=
    (SoAd_SizeOfTpRxBufferType)(SoAd_GetTpRxBufferEndIdxOfRxBufferConfig(rxBufCfgIdx) -
      SoAd_GetTpRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx)) )
  {
    /* #100 Copy pending PDU data to TP reception buffer. */
    /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
    VStdMemCpy(                                                                                                        /* SBSW_SOAD_CONST_POINTER_AND_OPTIONAL_POINTER_FORWARD_CSL03 */
      SOAD_A_P2VAR(void)SoAd_GetAddrTpRxBuffer(SoAd_GetTpRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx)),
      SOAD_A_P2CONST(void)BufPtr,
      SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx));
    SoAd_SetTpRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx,                                                              /* SBSW_SOAD_OPTIONAL_CSL03 */
      (SoAd_TpRxBufferIdxOfRxBufferConfigDynType)(SoAd_GetTpRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx) +
        SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx)));

    /* #101 Set event to continue reception in main function. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_TP_RX_SO_CON, SoConIdx);
  }
  /* #11 Abort reception otherwise. */
  else
  {
    /* #110 Finish PDU reception. */
    SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SoAd_GetSizeOfSocketRouteDest());                                      /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetRxBytesPendingOfRxMgt(rxMgtIdx, 0u);                                                                       /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #111 Call RxIndication with negative result. */
    SoAd_GetTpRxIndicationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfSocketRouteDest(SockRouteDestIdx))(                   /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetRxPduIdOfSocketRouteDest(SockRouteDestIdx), E_NOT_OK);

#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
    /* #112 Increment the dropped UDP PDU counter (if GetResetMeasurementData API is enabled). */
    SoAd_Measure_Inc(SOAD_MEAS_DROP_UDP, 1);
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */
  }
} /* SoAd_RxTp_UdpPduHdrCopyDataToBuffer() */

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpReceivePdu()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_UdpReceivePdu(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketRouteType    sockRouteIdx = SoAd_GetSocketRouteIdxOfSocketRouteDest(SockRouteDestIdx);
  SoAd_SizeOfSoConType          soConIdx = SoAd_GetSoConIdxOfSocketRoute(sockRouteIdx);
  SoAd_SizeOfRxMgtType          rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(soConIdx);
  SoAd_SizeOfRxBufferConfigType rxBufCfgIdx = SoAd_GetRxBufferConfigIdxOfSoCon(soConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if TP session is active. */
  if ( SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx) != SoAd_GetSizeOfSocketRouteDest() )
  {
    /* #20 Check if TP reception buffer contains already PDU data. */
    if ( SoAd_GetTpRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx) >
      SoAd_GetTpRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx) )
    {
      /* #200 Copy PDU to TP reception buffer. */
      SoAd_RxTp_UdpCopyData(soConIdx, BufPtr, Length);                                                                 /* SBSW_SOAD_CONST_POINTER_FORWARD */
    }
    /* #21 Handle TP reception if TP reception buffer is not used. */
    else
    {
      /* #210 Forward PDU to user. */
      SoAd_RxTp_UdpForwardPdu(SockRouteDestIdx, BufPtr, Length);                                                       /* SBSW_SOAD_CONST_POINTER_FORWARD */

      /* #211 Copy PDU to TP reception buffer if not all data has been copied to user. */
      if ( (SoAd_GetCloseModeOfSoConDyn(soConIdx) == SOAD_CLOSE_NONE) &&
        (SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) > 0u) )
      {
        PduLengthType bufferOffset = (PduLengthType)(Length - SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx));

        SoAd_RxTp_UdpCopyData(soConIdx, &BufPtr[bufferOffset], (uint16)SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx));       /* SBSW_SOAD_CONST_POINTER_FORWARD */

        /* #2110 Set event to handle PDU reception in main function. */
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_TP_RX_SO_CON, soConIdx);
      }
    }
  }
} /* SoAd_RxTp_UdpReceivePdu() */

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpCopyData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_UdpCopyData(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxBufferConfigType rxBufCfgIdx = SoAd_GetRxBufferConfigIdxOfSoCon(SoConIdx);
  SoAd_SizeOfTpRxBufferType     tpRxBufferOffset = SoAd_GetTpRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if buffer size is sufficient to store data. */
  if ( (tpRxBufferOffset + Length) <= SoAd_GetTpRxBufferEndIdxOfRxBufferConfig(rxBufCfgIdx) )
  {
    /* #20 Copy data to TP reception buffer. */
    /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
    VStdMemCpy(                                                                                                        /* SBSW_SOAD_CONST_POINTER_AND_OPTIONAL_POINTER_FORWARD_CSL03 */
      SOAD_A_P2VAR(void)SoAd_GetAddrTpRxBuffer(tpRxBufferOffset),
      SOAD_A_P2CONST(void)&BufPtr[0],
      Length);
    SoAd_SetTpRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx,                                                              /* SBSW_SOAD_OPTIONAL_CSL03 */
      (SoAd_TpRxBufferIdxOfRxBufferConfigDynType)(SoAd_GetTpRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx) + Length));
  }
  /* #11 Discard PDU otherwise. */
  else
  {
#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
    /* #110 Increment the dropped UDP PDU counter (if GetResetMeasurementData API is enabled). */
    SoAd_Measure_Inc(SOAD_MEAS_DROP_UDP, 1);
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */
  }
} /* SoAd_RxTp_UdpCopyData() */

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpForwardPdu()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_UdpForwardPdu(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType                 pduInfo = { NULL_PTR, 0u };
  SoAd_SizeOfSocketRouteType  sockRouteIdx = SoAd_GetSocketRouteIdxOfSocketRouteDest(SockRouteDestIdx);
  SoAd_SizeOfSoConType        soConIdx = SoAd_GetSoConIdxOfSocketRoute(sockRouteIdx);
  /* Optional indirection: Refer to Safe BSW assumption SoCon -> RxMgt. */
  SoAd_SizeOfRxMgtType        rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(soConIdx);
  boolean                     continueReception;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert whole UDP frame to a PDU. */
  SoAd_SetRxBytesPendingOfRxMgt(rxMgtIdx, (PduLengthType)Length);                                                      /* SBSW_SOAD_OPTIONAL_CSL03 */

  /* #20 Iterate until entire PDU is forwarded to upper layer or cancellation is requested. */
  while ( !SoAd_IsCancelRequestedOfRxMgt(rxMgtIdx) )
  {
    /* #30 Call CopyRxData to forward data to upper layer. */
    continueReception = SoAd_RxTp_UdpForwardPduCopyRxData(SockRouteDestIdx, BufPtr, Length, &pduInfo);                 /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */

    /* #40 Stop iteration if PDU is received completely, upper layer cannot receive more data or an error occurred. */
    if ( continueReception == FALSE )
    {
      break;
    }
  }
} /* SoAd_RxTp_UdpForwardPdu() */

/**********************************************************************************************************************
 *  SoAd_RxTp_UdpForwardPduCopyRxData()
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
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_RxTp_UdpForwardPduCopyRxData(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduLengthType               bufferSize = 0u;
  SoAd_SizeOfSocketRouteType  sockRouteIdx = SoAd_GetSocketRouteIdxOfSocketRouteDest(SockRouteDestIdx);
  SoAd_SizeOfSoConType        soConIdx = SoAd_GetSoConIdxOfSocketRoute(sockRouteIdx);
  /* Optional indirection: Refer to Safe BSW assumption SoCon -> RxMgt. */
  SoAd_SizeOfRxMgtType        rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(soConIdx);
  boolean                     continueReception = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call CopyRxData and check if call succeeds. */
  if ( SoAd_RxTp_CallCopyRxData(SockRouteDestIdx, PduInfoPtr, &bufferSize) == BUFREQ_OK )                              /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
  {
    /* #100 Decrement pending PDU data length. */
    SoAd_SetRxBytesPendingOfRxMgt(rxMgtIdx, SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) - PduInfoPtr->SduLength);          /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #101 Check if PDU is received completely. */
    if ( SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) == 0u )
    {
      continueReception = FALSE;
    }
    /* #102 Check if upper layer cannot receive more data otherwise. */
    else if ( bufferSize == 0u )
    {
      continueReception = FALSE;
    }
    /* #103 Calculate available length of data to be copied otherwise. */
    else
    {
      PduInfoPtr->SduLength = SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx);                                                 /* SBSW_SOAD_POINTER_WRITE */
      if ( PduInfoPtr->SduLength > bufferSize )
      {
        PduInfoPtr->SduLength = bufferSize;                                                                            /* SBSW_SOAD_POINTER_WRITE */
      }

      PduInfoPtr->SduDataPtr = &BufPtr[Length - SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx)];                              /* SBSW_SOAD_POINTER_WRITE */
    }
  }
  /* #11 Handle reception if call to CopyRxData fails. */
  else
  {
    /* #110 Close socket connection in next main function. */
    SoAd_SetCloseModeOfSoConDyn(soConIdx, SOAD_CLOSE_OFFLINE_RESET);                                                   /* SBSW_SOAD_CSL03_CSL02 */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, soConIdx);

    continueReception = FALSE;
  }

  return continueReception;
} /* SoAd_RxTp_UdpForwardPduCopyRxData() */

/**********************************************************************************************************************
 *  SoAd_RxTp_HandleReception()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_HandleReception(
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_EventQueueTpRxSoConIterType  eventQueueTpRxSoConIter;
  uint32                            handleIdx = 0u;
  uint32                            elementNumToHandle = SoAd_EventQueue_GetElementNumToHandle(
    SOAD_EVENT_QUEUE_TP_RX_SO_CON);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all queue elements which have to be handled in this context considering configured limit. */
  for ( eventQueueTpRxSoConIter = 0u;
    eventQueueTpRxSoConIter < elementNumToHandle;
    eventQueueTpRxSoConIter++ )
  {
    /* #20 Get next element. */
    if ( SoAd_EventQueue_GetNextElement(SOAD_EVENT_QUEUE_TP_RX_SO_CON, &handleIdx) == E_OK )                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      /* #30 Handle TP reception on this socket connection. */
      SoAd_RxTp_HandleReceptionOnSoCon((SoAd_SizeOfSoConType)handleIdx, ErrorIdPtr);                                   /* SBSW_SOAD_POINTER_FORWARD */
    }
    /* #21 Stop iteration if no element is left. */
    else
    {
      break;
    }
  }
} /* SoAd_RxTp_HandleReception() */

/**********************************************************************************************************************
 *  SoAd_RxTp_HandleReceptionOnSoCon()
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
/* PRQA S 3206, 3673 3 */ /* MD_SoAd_UnusedParameter, MD_SoAd_ConstCausedByUnused */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_HandleReceptionOnSoCon(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRxMgtType rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket connection is not requested to be closed. */
  if ( SoAd_GetCloseModeOfSoConDyn(SoConIdx) == SOAD_CLOSE_NONE )
  {
    /* #20 Handle receive cancellation if requested. */
    if ( SoAd_IsCancelRequestedOfRxMgt(rxMgtIdx) )
    {
      SoAd_RxTp_HandleCancellation(SoConIdx);
    }
    /* #21 Continue reception otherwise. */
    else
    {
#if ( SOAD_TCP == STD_ON )
      /* #210 Continue reception for TCP (if enabled). */
      if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
      {
        SoAd_RxTp_HandleReceptionOnSoConTcp(SoConIdx, ErrorIdPtr);                                                     /* SBSW_SOAD_POINTER_FORWARD */
      }
      else
#else
      SOAD_DUMMY_STATEMENT(ErrorIdPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_TCP == STD_ON */
      /* #211 Continue reception for UDP otherwise. */
      {
        SoAd_RxTp_HandleReceptionOnSoConUdp(SoConIdx);
      }
    }
  }
} /* SoAd_RxTp_HandleReceptionOnSoCon() */

/**********************************************************************************************************************
 *  SoAd_RxTp_HandleCancellation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_HandleCancellation(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxMgtType            rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx = SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx);
  SoAd_SizeOfRxBufferConfigType   rxBufCfgIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset TP reception buffer in case of UDP. */
#if ( SOAD_TCP == STD_ON )
  if ( SoAd_IsSocketUdpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
#endif /* SOAD_TCP == STD_ON */
  {
    /* Optional indirection: Refer to Safe BSW assumption SoCon -> RxBufferConfig. */
    rxBufCfgIdx = SoAd_GetRxBufferConfigIdxOfSoCon(SoConIdx);

    SoAd_SetTpRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx, SoAd_GetTpRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx));    /* SBSW_SOAD_OPTIONAL_CSL03 */
  }

  /* #20 Reset TP session. */
  SoAd_SetRxBytesPendingOfRxMgt(rxMgtIdx, 0u);                                                                         /* SBSW_SOAD_OPTIONAL_CSL03 */
  SoAd_SetCancelRequestedOfRxMgt(rxMgtIdx, FALSE);                                                                     /* SBSW_SOAD_OPTIONAL_CSL03 */
  SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SoAd_GetSizeOfSocketRouteDest());                                        /* SBSW_SOAD_OPTIONAL_CSL03 */

  /* #30 Indicate to close socket connection in next main function. */
  SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_OFFLINE_RESET);                                                     /* SBSW_SOAD_PARAMETER_IDX */
  SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);

  /* #40 Call TpRxIndication with negative result. */
  SoAd_GetTpRxIndicationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfSocketRouteDest(sockRouteDestIdx))(                     /* SBSW_SOAD_FUNCTION_PTR */
    SoAd_GetRxPduIdOfSocketRouteDest(sockRouteDestIdx), E_NOT_OK);
} /* SoAd_RxTp_HandleCancellation() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxTp_HandleReceptionOnSoConTcp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_HandleReceptionOnSoConTcp(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if received data is pending. */
  if ( SoAd_GetRxBufStructSegLvlOfRxBufStructMgt(SoAd_GetRxBufStructMgtIdxOfSoCon(SoConIdx)) > 0u )
  {
    /* #20 Handle reception for TCP socket connection with PDU header (if enabled). */
    if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
    {
      SoAd_RxTcp_PduHdrRxIndication(SoConIdx, NULL_PTR, 0u, ErrorIdPtr);                                               /* SBSW_SOAD_POINTER_FORWARD */
    }
    else
      /* #21 Handle reception for TCP socket connection without PDU header. */
    {
      SoAd_RxTcp_RxIndication(SoConIdx, NULL_PTR, 0u, ErrorIdPtr);                                                     /* SBSW_SOAD_POINTER_FORWARD */
    }
  }
} /* SoAd_RxTp_HandleReceptionOnSoConTcp() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_RxTp_HandleReceptionOnSoConUdp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTp_HandleReceptionOnSoConUdp(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType                     pduInfo = { NULL_PTR, 0u };
  SoAd_SizeOfRxMgtType            rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx = SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx);
  SoAd_SizeOfRxBufferConfigType   rxBufCfgIdx = SoAd_GetRxBufferConfigIdxOfSoCon(SoConIdx);
  boolean                         continueReception;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if TP reception buffer contains data. */
  if ( SoAd_GetTpRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx) >
    SoAd_GetTpRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx) )
  {
    /* #20 Iterate until entire PDU is forwarded to upper layer or cancellation is requested. */
    while ( (SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) > 0u) && !SoAd_IsCancelRequestedOfRxMgt(rxMgtIdx) )
    {
      /* #30 Continue TP reception of this data. */
      continueReception = SoAd_RxTp_HandleReceptionOnSoConUdpCopyRxData(SoConIdx, sockRouteDestIdx, &pduInfo);         /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

      /* #40 Stop iteration if PDU is received completely, upper layer cannot receive more data or error occurred. */
      if ( continueReception == FALSE )
      {
        break;
      }
    }
  }
} /* SoAd_RxTp_HandleReceptionOnSoConUdp() */

/**********************************************************************************************************************
 *  SoAd_RxTp_HandleReceptionOnSoConUdpCopyRxData()
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
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_RxTp_HandleReceptionOnSoConUdpCopyRxData(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduLengthType                 bufferSize = 0u;
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxMgtType          rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxBufferConfigType rxBufCfgIdx = SoAd_GetRxBufferConfigIdxOfSoCon(SoConIdx);
  boolean                       continueReception = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call CopyRxData and check if call succeeds. */
  if ( SoAd_RxTp_CallCopyRxData(SockRouteDestIdx, PduInfoPtr, &bufferSize) == BUFREQ_OK )                              /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
  {
    /* #100 Decrement pending PDU data length. */
    SoAd_SetRxBytesPendingOfRxMgt(rxMgtIdx, SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) - PduInfoPtr->SduLength);          /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #101 Check if PDU is received completely. */
    if ( SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx) == 0u )
    {
      /* #1010 Finish PDU reception. */
      SoAd_SetTpRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx, SoAd_GetTpRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx));  /* SBSW_SOAD_OPTIONAL_CSL03 */

      /* #1011 Call RxIndication with positive result if PDU header is enabled. */
      if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) )
      {
        SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SoAd_GetSizeOfSocketRouteDest());                                  /* SBSW_SOAD_OPTIONAL_CSL03 */

        SoAd_GetTpRxIndicationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfSocketRouteDest(SockRouteDestIdx))(               /* SBSW_SOAD_FUNCTION_PTR */
          SoAd_GetRxPduIdOfSocketRouteDest(SockRouteDestIdx), E_OK);
      }

      continueReception = FALSE;
    }
    /* #102 Check if upper layer cannot receive more data otherwise. */
    else if ( bufferSize == 0u )
    {
      continueReception = FALSE;
    }
    /* #103 Calculate available length of data to be copied otherwise. */
    else
    {
      PduInfoPtr->SduLength = SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx);                                                 /* SBSW_SOAD_POINTER_WRITE */
      if (PduInfoPtr->SduLength > bufferSize)
      {
        PduInfoPtr->SduLength = bufferSize;                                                                            /* SBSW_SOAD_POINTER_WRITE */
      }

      PduInfoPtr->SduDataPtr = SoAd_GetAddrTpRxBuffer(                                                                 /* SBSW_SOAD_POINTER_WRITE */
        SoAd_GetTpRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx) - SoAd_GetRxBytesPendingOfRxMgt(rxMgtIdx));
    }
  }
  /* #11 Handle reception if call to CopyRxData fails. */
  else
  {
    /* #110 Close socket connection in next main function. */
    SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_OFFLINE_RESET);                                                   /* SBSW_SOAD_PARAMETER_IDX */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);

    continueReception = FALSE;
  }

  return continueReception;
} /* SoAd_RxTp_HandleReceptionOnSoConUdpCopyRxData() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxTcp_SkipData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_SkipData(
  SoAd_SizeOfSocketType SockIdx,
  uint16 Length,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) SkippedLengthPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if data shall be skipped. */
  if ( SoAd_GetSkipBytesOfSocketDyn(SockIdx) > 0u )
  {
    /* #20 Skip data if data to be skipped is bigger than length of available data. */
    if ( SoAd_GetSkipBytesOfSocketDyn(SockIdx) > Length )
    {
      SoAd_SetSkipBytesOfSocketDyn(SockIdx, SoAd_GetSkipBytesOfSocketDyn(SockIdx) - Length);                           /* SBSW_SOAD_PARAMETER_IDX */
      SoAd_TcpIp_TcpReceived(SockIdx, Length);
    }
    /* #21 Skip available data and indicate to continue reception otherwise. */
    else
    {
      *SkippedLengthPtr = (uint16)(SoAd_GetSkipBytesOfSocketDyn(SockIdx));                                             /* SBSW_SOAD_POINTER_WRITE */
      SoAd_SetSkipBytesOfSocketDyn(SockIdx, 0u);                                                                       /* SBSW_SOAD_PARAMETER_IDX */

      retVal = E_OK;
    }
  }
  /* #11 Indicate to continue reception otherwise. */
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_RxTcp_SkipData() */

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrRxIndication()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTcp_PduHdrRxIndication(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                totalLen;
  uint32                releaseBufLen = 0u;
  SoAd_SizeOfSocketType sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  SoAd_SizeOfRxMgtType  rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add TCP segment to buffer struct. */
  if ( SoAd_RxBufStruct_WriteSegment(SoConIdx, BufPtr, Length) == E_OK )                                               /* SBSW_SOAD_POINTER_FORWARD */
  {
    /* #20 Get available buffer. */
    totalLen = SoAd_RxBufStruct_GetTotLen(SoConIdx, 0u);

    /* #30 Handle reception for available buffer. */
    while ( releaseBufLen < totalLen )
    {
      /* #300 Try to receive a PDU completely. */
      if ( SoAd_RxTcp_PduHdrReceivePdu(SoConIdx, &releaseBufLen, totalLen, ErrorIdPtr) == E_NOT_OK )                   /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
      {
        Std_ReturnType retVal;

        /* #3000 Skip PDU data if required (i.e. PDU discarded). */
        retVal = SoAd_RxTcp_PduHdrSkipData(SoConIdx, &releaseBufLen, totalLen);                                        /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

        /* #3001 Stop reception and add event to continue reception in main function context if required. */
        if ( (retVal == E_NOT_OK) && (releaseBufLen != totalLen) )
        {
          SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx = SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx);
          SoAd_SizeOfSocketRouteType      sockRouteIdx = SoAd_GetSocketRouteIdxOfSocketRouteDest(sockRouteDestIdx);

          if ( (sockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()) &&
            (SoAd_GetUpperLayerApiOfSocketRoute(sockRouteIdx) == SOAD_UL_API_TP) )
          {
            SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_TP_RX_SO_CON, SoConIdx);
          }
          break;
        }
      }
    }

    /* #40 Release buffer. */
    if ( releaseBufLen > 0u )
    {
      /* #400 Release buffer from buffer struct. */
      SoAd_RxBufStruct_ReleaseSegment(SoConIdx, releaseBufLen);
      /* #401 Release buffer in TcpIp. */
      SoAd_TcpIp_TcpReceived(sockIdx, releaseBufLen);
    }
  }
  /* #11 Handle case if buffer struct size is not sufficient. */
  else
  {
    /* #110 Close socket connection in next main function. */
    SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_OFFLINE_RESET);                                                   /* SBSW_SOAD_PARAMETER_IDX */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);

    /* #111 Set error. */
# if ( SOAD_DEV_ERROR_DETECT == STD_ON )
    *ErrorIdPtr = SOAD_E_NOBUFS;                                                                                       /* SBSW_SOAD_POINTER_WRITE */
# else
    SOAD_DUMMY_STATEMENT(ErrorIdPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  }
} /* SoAd_RxTcp_PduHdrRxIndication() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrReceivePdu()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_PduHdrReceivePdu(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  uint32 TotalLen,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Receive PDU header. */
  if ( SoAd_RxTcp_PduHdrReceiveHeader(SoConIdx, ReleaseBufLenPtr, TotalLen, ErrorIdPtr) == E_OK )                      /* SBSW_SOAD_POINTER_FORWARD */
  {
    /* #20 Receive PDU data. */
    retVal = SoAd_RxTcp_PduHdrReceiveData(SoConIdx, ReleaseBufLenPtr, TotalLen, ErrorIdPtr);                           /* SBSW_SOAD_POINTER_FORWARD */
  }

  return retVal;
} /* SoAd_RxTcp_PduHdrReceivePdu() */

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrReceiveHeader()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_PduHdrReceiveHeader(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  uint32 TotalLen,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduHdrLenType    pduHdrLen;
  SoAd_SizeOfRxMgtType  rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  Std_ReturnType        retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if PDU header is already evaluated. */
  if ( SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx) != SoAd_GetSizeOfSocketRouteDest() )
  {
    retVal = E_OK;
  }
  /* #20 Check if PDU header is no yet received completely otherwise. */
  else if ( (TotalLen - *ReleaseBufLenPtr) < SOAD_PDU_HDR_SIZE )
  {
    retVal = E_NOT_OK;
  }
  /* #30 Handle PDU header otherwise. */
  else
  {
    uint8 pduHdrBuf[SOAD_PDU_HDR_SIZE] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

    /* #300 Extract PDU header. */
    SoAd_RxBufStruct_Copy2Buf(SoConIdx, &pduHdrBuf[0], SOAD_PDU_HDR_SIZE, *ReleaseBufLenPtr);                          /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    IPBASE_GET_UINT32(pduHdrBuf, SOAD_PDU_HDR_ID_SIZE, pduHdrLen);                                                     /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

    /* #301 Validate PDU header. */
    if ( (pduHdrLen <= SOAD_MAX_PDU_LEN) && (pduHdrLen != 0u) )
    {
      /* #3010 Get socket route by PDU header and receive header if found. */
      retVal = SoAd_RxTcp_PduHdrFindSocketRouteAndReceiveHeader(SoConIdx, pduHdrBuf, ErrorIdPtr);                      /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    }
    /* #302 Increment the dropped TCP PDU counter if PDU length is invalid (if GetRestMeasurement API is enabled). */
    else
    {
# if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
      SoAd_Measure_Inc(SOAD_MEAS_DROP_TCP, 1);
# endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */
      retVal = E_NOT_OK;
    }

    /* #303 Release TcpIp buffer for PDU header. */
    *ReleaseBufLenPtr += SOAD_PDU_HDR_SIZE;                                                                            /* SBSW_SOAD_POINTER_WRITE */

    /* #304 Skip PDU if any error occurred. */
    if ( retVal == E_NOT_OK )
    {
      SoAd_SetSkipBytesOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx), pduHdrLen);                                     /* SBSW_SOAD_CSL03_CSL02 */
    }
  }

  return retVal;
} /* SoAd_RxTcp_PduHdrReceiveHeader() */

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrFindSocketRouteAndReceiveHeader()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_PduHdrFindSocketRouteAndReceiveHeader(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_DATA) PduHdrBufPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduHdrIdType           pduHdrId;
  SoAd_SizeOfSocketRouteType  sockRouteIdx = SoAd_GetSizeOfSocketRoute();
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT32(PduHdrBufPtr, 0u, pduHdrId);                                                                       /* SBSW_SOAD_POINTER_FORWARD */

  /* #10 Try to find the socket route by PDU header ID on the socket connection. */
  if ( SoAd_Rx_FindSocketRouteOnSoConByPduHdrId(SoConIdx, pduHdrId, &sockRouteIdx, ErrorIdPtr) == E_OK )               /* SBSW_SOAD_POINTER_FORWARD */
  {
    /* #100 Try to find the corresponding socket route destination and receive header if found. */
    retVal = SoAd_RxTcp_PduHdrFindSocketRouteDestAndReceiveHeader(SoConIdx, sockRouteIdx, PduHdrBufPtr, ErrorIdPtr);   /* SBSW_SOAD_POINTER_FORWARD */
  }
  /* #20 Discard the PDU otherwise. */
# if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON ) 
  else
  {
    /* #200 Increment the dropped TCP PDU counter (if GetResetMeasurementData API is enabled). */
    SoAd_Measure_Inc(SOAD_MEAS_DROP_TCP, 1);
  }
# endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

  return retVal;
} /* SoAd_RxTcp_PduHdrFindSocketRouteAndReceiveHeader() */

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrFindSocketRouteDestAndReceiveHeader()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_PduHdrFindSocketRouteDestAndReceiveHeader(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteType SockRouteIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_DATA) PduHdrBufPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketRouteDestIterType    sockRouteDestIter;
  SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx;
# if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
  boolean                         anyRoutingGroupEnabled = FALSE;
# endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */
  Std_ReturnType                  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket route uses IF-API. */
  if ( SoAd_GetUpperLayerApiOfSocketRoute(SockRouteIdx) == SOAD_UL_API_IF )
  {
    /* #100 Iterate over all socket route destinations. */
    for ( sockRouteDestIter = SoAd_GetSocketRouteDestStartIdxOfSocketRoute(SockRouteIdx);
      sockRouteDestIter < SoAd_GetSocketRouteDestEndIdxOfSocketRoute(SockRouteIdx);
      sockRouteDestIter++ )
    {
      /* #1000 Check if at least one routing group is enabled for this socket route destination. */
      if ( SoAd_RouteGrp_CheckAnyRoutGrpOnSockRouteDestEnabled((SoAd_SizeOfSocketRouteDestType)sockRouteDestIter) ==
        TRUE )
      {
        /* #10000 Receive header for IF-API over this socket route destination and stop iteration. */
        retVal = SoAd_RxIf_TcpPduHdrReceiveHeader(SoConIdx, (SoAd_SizeOfSocketRouteDestType)sockRouteDestIter,         /* SBSW_SOAD_POINTER_FORWARD */
          PduHdrBufPtr, ErrorIdPtr);

# if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
        anyRoutingGroupEnabled = TRUE;
# endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

        break;
      }
    }
  }
  /* #11 Assume socket route uses TP-API otherwise. */
  else
  {
    /* #110 Get the first socket route destination since exactly one destination exists for TP-API. */
    sockRouteDestIdx = SoAd_GetSocketRouteDestStartIdxOfSocketRoute(SockRouteIdx);

    /* #111 Check if at least one routing group is enabled for this socket route destination. */
    if ( SoAd_RouteGrp_CheckAnyRoutGrpOnSockRouteDestEnabled(sockRouteDestIdx) == TRUE )
    {
      /* #1110 Receive header for TP-API. */
      SoAd_RxTp_TcpPduHdrReceiveHeader(SoConIdx, sockRouteDestIdx, PduHdrBufPtr);                                      /* SBSW_SOAD_POINTER_FORWARD */

      retVal = E_OK;

# if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
      anyRoutingGroupEnabled = TRUE;
# endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */
    }
  }

# if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
  /* #20 Check if no socket route destination with at least one enabled routing group could be found (if
   *     GetResetMeasurementData API is enabled). */
  if ( anyRoutingGroupEnabled == FALSE )
  {
    /* #210 Increment the dropped TCP PDU counter. */
    SoAd_Measure_Inc(SOAD_MEAS_DROP_TCP, 1);
  }
# endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

  return retVal;
} /* SoAd_RxTcp_PduHdrFindSocketRouteDestAndReceiveHeader() */

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrSkipData()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_PduHdrSkipData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  uint32 TotalLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if data shall be skipped. */
  if ( SoAd_GetSkipBytesOfSocketDyn(sockIdx) > 0u )
  {
    /* #20 Check if data to be skipped is smaller than the available data. */
    if ( SoAd_GetSkipBytesOfSocketDyn(sockIdx) < (TotalLen - *ReleaseBufLenPtr) )
    {
      /* #200 Skip data and indicate that reception can be continued. */
      *ReleaseBufLenPtr += SoAd_GetSkipBytesOfSocketDyn(sockIdx);                                                      /* SBSW_SOAD_POINTER_WRITE */
      SoAd_SetSkipBytesOfSocketDyn(sockIdx, 0u);                                                                       /* SBSW_SOAD_CSL03_CSL02 */

      retVal = E_OK;
    }
    /* #21 Handle skippping data if data to be skipped is bigger than or equal to the available data. */
    else
    {
      /* #210 Skip as much data as possible and release all available data. */
      SoAd_SetSkipBytesOfSocketDyn(sockIdx, SoAd_GetSkipBytesOfSocketDyn(sockIdx) - (TotalLen - *ReleaseBufLenPtr));   /* SBSW_SOAD_CSL03_CSL02 */
      *ReleaseBufLenPtr = TotalLen;                                                                                    /* SBSW_SOAD_POINTER_WRITE */
    }
  }

  return retVal;
} /* SoAd_RxTcp_PduHdrSkipData() */

/**********************************************************************************************************************
 *  SoAd_RxTcp_PduHdrReceiveData()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxTcp_PduHdrReceiveData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ReleaseBufLenPtr,
  uint32 TotalLen,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRxMgtType            rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx = SoAd_GetSocketRouteDestIdxOfRxMgt(rxMgtIdx);
  SoAd_SizeOfSocketRouteType      sockRouteIdx = SoAd_GetSocketRouteIdxOfSocketRouteDest(sockRouteDestIdx);
  Std_ReturnType                  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle reception for IF-API. */
  if ( SoAd_GetUpperLayerApiOfSocketRoute(sockRouteIdx) == SOAD_UL_API_IF )
  {
    PduInfoType pduInfo = { NULL_PTR, 0u };

    /* #100 Check if PDU is copied completely to IF reception buffer or is located in one buffer segment. */
    if ( SoAd_RxIf_TcpPduHdrCopyData(SoConIdx, ReleaseBufLenPtr, TotalLen, &pduInfo) == E_OK )                         /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    {
      /* #1000 Forward PDU to user. */
      SoAd_RxIf_TcpPduHdrForwardPdu(SoConIdx, &pduInfo, ErrorIdPtr);                                                   /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
      retVal = E_OK;
    }
  }
  /* #20 Handle reception for TP-API. */
  else
  {
    /* #200 Forward PDU to user. */
    retVal = SoAd_RxTp_TcpPduHdrForwardPdu(SoConIdx, ReleaseBufLenPtr, TotalLen);                                      /* SBSW_SOAD_POINTER_FORWARD */
  }

  return retVal;
} /* SoAd_RxTcp_PduHdrReceiveData() */

/**********************************************************************************************************************
 *  SoAd_RxTcp_RxIndication()
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
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxTcp_RxIndication(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                          releaseBufLen = 0u;
  SoAd_SocketRouteIterType        sockRouteIter;
  SoAd_SocketRouteDestIterType    sockRouteDestIter;
  SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx;
  SoAd_SizeOfSocketType           sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  boolean                         pduDiscarded = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all socket routes to forward PDU to user. */
  /* In case of IF multiple socket routes are possible. In case of TP only one socket route exists. */
  for ( sockRouteIter = SoAd_GetSocketRouteStartIdxOfSoCon(SoConIdx);
    sockRouteIter < SoAd_GetSocketRouteEndIdxOfSoCon(SoConIdx);
    sockRouteIter++ )
  {
    /* #20 Check if socket route uses IF-API. */
    if ( SoAd_GetUpperLayerApiOfSocketRoute(sockRouteIter) == SOAD_UL_API_IF )
    {
      /* #200 Iterate over all socket route destinations. */
      for ( sockRouteDestIter = SoAd_GetSocketRouteDestStartIdxOfSocketRoute(sockRouteIter);
        sockRouteDestIter < SoAd_GetSocketRouteDestEndIdxOfSocketRoute(sockRouteIter);
        sockRouteDestIter++ )
      {
        /* #2000 Check if at least one routing group is enabled for this socket route destination. */
        if ( SoAd_RouteGrp_CheckAnyRoutGrpOnSockRouteDestEnabled((SoAd_SizeOfSocketRouteDestType)sockRouteDestIter) ==
          TRUE )
        {
          /* #20000 Forward received TCP segment as one PDU to user and stop iteration. */
          SoAd_RxIf_TcpReceivePdu(SoConIdx, (SoAd_SizeOfSocketRouteDestType)sockRouteDestIter, BufPtr, Length,         /* SBSW_SOAD_POINTER_FORWARD */
            ErrorIdPtr);

          /* #20001 Release whole TCP segment. */
          releaseBufLen = Length;

          pduDiscarded = FALSE;

          break;
        }
      }
    }
    /* #21 Assume socket route uses TP-API otherwise. */
    else
    {
      /* #210 Get the first socket route destination since exactly one destination exists for TP-API. */
      sockRouteDestIdx = SoAd_GetSocketRouteDestStartIdxOfSocketRoute(sockRouteIter);

      /* #211 Check if at least one routing group is enabled for this socket route destination. */
      if ( SoAd_RouteGrp_CheckAnyRoutGrpOnSockRouteDestEnabled(sockRouteDestIdx) == TRUE )
      {
        /* #2110 Forward received TCP segment as streaming PDU to user. */
        SoAd_RxTp_TcpReceivePdu(SoConIdx, BufPtr, Length, &releaseBufLen, ErrorIdPtr);                                 /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */

        pduDiscarded = FALSE;
      }
    }
  }

  /* #30 Discard PDU if PDU could not be forwarded to user. */
  if ( pduDiscarded == TRUE )
  {
    /* #300 Release whole TCP segment. */
    releaseBufLen = Length;

# if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
    /* #301 Increment the dropped TCP PDU counter (if GetResetMeasurementData API is enabled). */
    SoAd_Measure_Inc(SOAD_MEAS_DROP_TCP, 1);
# endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */
  }

  /* #40 Release buffer. */
  if ( releaseBufLen > 0u )
  {
    /* #400 Release buffer from buffer struct. */
    SoAd_RxBufStruct_ReleaseSegment(SoConIdx, releaseBufLen);
    /* #401 Release buffer in TcpIp. */
    SoAd_TcpIp_TcpReceived(sockIdx, releaseBufLen);
  }
} /* SoAd_RxTcp_RxIndication() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_RxUdp_PduHdrRxIndication()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxUdp_PduHdrRxIndication(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduHdrLenType              pduHdrLen = 0u;
  uint16                          readDataLen = 0u;
  SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if all PDU header length fields in frame are valid (if enabled). */
  if ( SoAd_RxUdp_PduHdrCheckAllHeaderLength(SoConIdx, BufPtr, Length) == E_OK )                                       /* SBSW_SOAD_CONST_POINTER_FORWARD */
  {
    /* #20 Iterate over whole frame to find and forward all PDUs. */
    while ( Length > readDataLen )
    {
      /* #30 Check PDU header length. */
      if ( SoAd_RxUdp_PduHdrCheckHeaderLength(SoConIdx, BufPtr, Length, readDataLen, &pduHdrLen) == E_OK )             /* SBSW_SOAD_VARIABLE_POINTER_AND_CONST_POINTER_FORWARD */
      {
        /* #40 Evaluate PDU header. */
        if ( SoAd_RxUdp_PduHdrReceiveHeader(SoConIdx, &BufPtr[readDataLen], &sockRouteDestIdx, ErrorIdPtr) == E_OK )   /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_AND_CONST_POINTER_FORWARD */
        {
          /* #50 Receive PDU data. */
          SoAd_RxUdp_PduHdrReceiveData(SoConIdx, sockRouteDestIdx, &BufPtr[readDataLen], ErrorIdPtr);                  /* SBSW_SOAD_POINTER_WITH_OFFSET_AND_POINTER_FORWARD */
        }
#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
        /* #41 Discard the PDU since the header length is invalid. */
        else
        {
          /* #410 Increment the dropped UDP PDU counter (if GetResetMeasurementData API is enabled). */
          SoAd_Measure_Inc(SOAD_MEAS_DROP_UDP, 1);
        }
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

        /* #70 Mark PDU processing as complete. */
        readDataLen += (uint16)(SOAD_PDU_HDR_SIZE + pduHdrLen);
      }
      /* #31 Stop reception of frame if PDU header length check failed. */
      else
      {
#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
        /* #310 Increment the dropped UDP PDU counter (if GetResetMeasurementData API is enabled). */
        SoAd_Measure_Inc(SOAD_MEAS_DROP_UDP, 1);
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */
        break;
      }
    }
  }
} /* SoAd_RxUdp_PduHdrRxIndication() */

/**********************************************************************************************************************
 *  SoAd_RxUdp_PduHdrCheckAllHeaderLength()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxUdp_PduHdrCheckAllHeaderLength(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduHdrLenType        pduHdrLen;
  uint16                    offset = 0u;
#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
  uint16                    numOfPdus = 0u;
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */
  SoAd_SizeOfSocketUdpType  socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx));
  boolean                   inconsistencyFound = FALSE;
  Std_ReturnType            retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if strict header length check is enabled for the socket connection. */
  if ( SoAd_IsUdpStrictHdrLenCheckEnabledOfSocketUdp(socketUdpIdx) )
  {
    /* #20 Iterate over whole frame to find and check all PDU header. */
    while ( offset < Length )
    {
#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
      /* Count the number of PDUs in the current frame. */
      numOfPdus++;
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

      /* #30 Check if pending length is sufficient to contain a complete PDU header. */
      if ( ((uint16)(Length - offset)) >= SOAD_PDU_HDR_SIZE )
      {
        /* #40 Retrieve PDU header length. */
        /* PRQA S 4391 1 */ /* MD_SoAd_GenericWiderTypeCast */
        IPBASE_GET_UINT32(BufPtr, (uint32_least)(offset + SOAD_PDU_HDR_ID_SIZE), pduHdrLen);                           /* SBSW_SOAD_POINTER_FORWARD */

        /* #50 Check if PDU header length is bigger than the pending data of the frame. */
        offset += SOAD_PDU_HDR_SIZE;
        if ( pduHdrLen > ((SoAd_PduHdrLenType)(Length - offset)) ) /* PRQA S 4391 */ /* MD_SoAd_GenericWiderTypeCast */
        {
          /* #500 Indicate that inconsistency has been found. */
          inconsistencyFound = TRUE;
        }
        else
        {
          /* #501 Set offset to continue with next PDU header otherwise. */
          offset += (uint16)pduHdrLen;
        }
      }
      /* #31 Indicate that inconsistency has been found. */
      else
      {
        inconsistencyFound = TRUE;
      }

      /* #60 Stop iteration if a inconsistency has been found. */
      if ( inconsistencyFound == TRUE )
      {
#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
        /* #600 Increment dropped UDP PDU counter by count of PDUs in frame(if GetResetMeasurementData API enabled). */
        SoAd_Measure_Inc(SOAD_MEAS_DROP_UDP, numOfPdus);
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */
        retVal = E_NOT_OK;
        break;
      }
    }
  }

  return retVal;
} /* SoAd_RxUdp_PduHdrCheckAllHeaderLength() */

/**********************************************************************************************************************
 *  SoAd_RxUdp_PduHdrCheckHeaderLength()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxUdp_PduHdrCheckHeaderLength(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  uint16 ReadDataLen,
  P2VAR(SoAd_PduHdrLenType, AUTOMATIC, SOAD_APPL_VAR) PduHdrLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduHdrLenType        pduHdrLen;
  SoAd_SizeOfSocketUdpType  socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx));
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check header length only in case strict header length check is disabled (if check is enabled). */
  if ( !SoAd_IsUdpStrictHdrLenCheckEnabledOfSocketUdp(socketUdpIdx) )
  {
    /* #20 Check if pending length is sufficient to contain a complete PDU header. */
    if ( (uint16)(Length - ReadDataLen) >= SOAD_PDU_HDR_SIZE )
    {
      /* #30 Retrieve PDU header length. */
      /* PRQA S 4391 1 */ /* MD_SoAd_GenericWiderTypeCast */
      IPBASE_GET_UINT32(BufPtr, (uint32_least)(ReadDataLen + SOAD_PDU_HDR_ID_SIZE), pduHdrLen);                        /* SBSW_SOAD_POINTER_FORWARD */

      /* #40 Check if PDU header length is supported and is not bigger than the pending data of the frame. */
      /* PRQA S 4391 2 */ /* MD_SoAd_GenericWiderTypeCast */
      if ( (pduHdrLen <= SOAD_MAX_PDU_LEN) &&
        (pduHdrLen <= (SoAd_PduHdrLenType)(Length - ReadDataLen - SOAD_PDU_HDR_SIZE)) )
      {
        *PduHdrLenPtr = pduHdrLen;                                                                                     /* SBSW_SOAD_POINTER_WRITE */

        retVal = E_OK;
      }
    }
  }
  /* #11 Do not check PDU header length again otherwise (if check is enabled). */
  else
  {
    /* PRQA S 4391 1 */ /* MD_SoAd_GenericWiderTypeCast */
    IPBASE_GET_UINT32(BufPtr, (uint32_least)(ReadDataLen + SOAD_PDU_HDR_ID_SIZE), *PduHdrLenPtr);                      /* SBSW_SOAD_POINTER_FORWARD */ /* SBSW_SOAD_POINTER_WRITE */

    retVal = E_OK;
  }

  return retVal;
} /* SoAd_RxUdp_PduHdrCheckHeaderLength() */

/**********************************************************************************************************************
 *  SoAd_RxUdp_PduHdrReceiveHeader()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 5 */ /* MD_SoAd_ConstCausedByUnused */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxUdp_PduHdrReceiveHeader(
  SoAd_SizeOfSoConType SoConIdx,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(SoAd_SizeOfSocketRouteDestType, AUTOMATIC, SOAD_APPL_VAR) SockRouteDestIdxPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduHdrIdType           pduHdrId;
  SoAd_PduHdrLenType          pduHdrLen;
  SoAd_SizeOfSocketRouteType  sockRouteIdx = SoAd_GetSizeOfSocketRoute();
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Retrieve PDU header. */
  IPBASE_GET_UINT32(BufPtr, 0u, pduHdrId);                                                                             /* SBSW_SOAD_POINTER_FORWARD */
  IPBASE_GET_UINT32(BufPtr, SOAD_PDU_HDR_ID_SIZE, pduHdrLen);                                                          /* SBSW_SOAD_POINTER_FORWARD */

  /* #20 Check if PDU header length is not 0. */
  if ( pduHdrLen != 0u )
  {
    /* #200 Try to find the corresponding socket route. */
    if ( SoAd_Rx_FindSocketRouteOnSoConByPduHdrId(SoConIdx, pduHdrId, &sockRouteIdx, ErrorIdPtr) == E_OK )             /* SBSW_SOAD_POINTER_FORWARD */
    {
      /* #2000 Try to find the corresponding socket route destination. */
      retVal = SoAd_RxUdp_PduHdrFindSocketRouteDest(sockRouteIdx, SockRouteDestIdxPtr);                                /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  return retVal;
} /* SoAd_RxUdp_PduHdrReceiveHeader() */

/**********************************************************************************************************************
 *  SoAd_RxUdp_PduHdrFindSocketRouteDest()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxUdp_PduHdrFindSocketRouteDest(
  SoAd_SizeOfSocketRouteType SockRouteIdx,
  P2VAR(SoAd_SizeOfSocketRouteDestType, AUTOMATIC, SOAD_APPL_VAR) SockRouteDestIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketRouteDestIterType  sockRouteDestIter;
  Std_ReturnType                retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all socket route destinations of the socket route. */
  for ( sockRouteDestIter = SoAd_GetSocketRouteDestStartIdxOfSocketRoute(SockRouteIdx);
    sockRouteDestIter < SoAd_GetSocketRouteDestEndIdxOfSocketRoute(SockRouteIdx);
    sockRouteDestIter++ )
  {
    /* #20 Check if at least one routing group is enabled for this socket route destination. */
    if ( SoAd_RouteGrp_CheckAnyRoutGrpOnSockRouteDestEnabled((SoAd_SizeOfSocketRouteDestType)sockRouteDestIter) ==
      TRUE )
    {
      /* #30 Return index of socket route destination and stop iteration. */
      *SockRouteDestIdxPtr = (SoAd_SizeOfSocketRouteDestType)sockRouteDestIter;                                        /* SBSW_SOAD_POINTER_WRITE */
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* SoAd_RxUdp_PduHdrFindSocketRouteDest() */

/**********************************************************************************************************************
 *  SoAd_RxUdp_PduHdrReceiveData()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxUdp_PduHdrReceiveData(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduHdrLenType          pduHdrLen;
  SoAd_SizeOfSocketRouteType  sockRouteIdx = SoAd_GetSocketRouteIdxOfSocketRouteDest(SockRouteDestIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Retrieve PDU header length. */
  IPBASE_GET_UINT32(BufPtr, SOAD_PDU_HDR_ID_SIZE, pduHdrLen);                                                          /* SBSW_SOAD_POINTER_FORWARD */

  /* #20 Handle reception for IF-API. */
  if ( SoAd_GetUpperLayerApiOfSocketRoute(sockRouteIdx) == SOAD_UL_API_IF )
  {
    /* #200 Forward PDU to user. */
    SoAd_RxIf_UdpPduHdrForwardPdu(SoConIdx, SockRouteDestIdx, pduHdrLen, BufPtr, ErrorIdPtr);                          /* SBSW_SOAD_POINTER_FORWARD */
  }
  /* #21 Handle reception for TP-API. */
  else
  {
    /* #210 Call StartOfReception. */
    if ( SoAd_RxTp_UdpPduHdrStartOfReception(SoConIdx, SockRouteDestIdx, pduHdrLen) == E_OK )
    {
      /* #211 Copy data by calling CopyRxData. */
      SoAd_RxTp_UdpPduHdrCopyRxData(SoConIdx, SockRouteDestIdx, &BufPtr[SOAD_PDU_HDR_SIZE]);                           /* SBSW_SOAD_POINTER_FORWARD */
    }
  }
} /* SoAd_RxUdp_PduHdrReceiveData() */

/**********************************************************************************************************************
 *  SoAd_RxUdp_RxIndication()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxUdp_RxIndication(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketRouteDestIterType    sockRouteDestIter;
  SoAd_SocketRouteIterType        sockRouteIter;
  SoAd_SizeOfSocketRouteDestType  sockRouteDestIdx;
#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
  boolean                         pduDiscarded = TRUE;
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all socket routes to receive data. */
  for ( sockRouteIter = SoAd_GetSocketRouteStartIdxOfSoCon(SoConIdx);
    sockRouteIter < SoAd_GetSocketRouteEndIdxOfSoCon(SoConIdx);
    sockRouteIter++ )
  {
    /* #20 Check if socket route uses IF-API. */
    if ( SoAd_GetUpperLayerApiOfSocketRoute(sockRouteIter) == SOAD_UL_API_IF )
    {
      /* #200 Iterate over all socket route destinations. */
      for ( sockRouteDestIter = SoAd_GetSocketRouteDestStartIdxOfSocketRoute(sockRouteIter);
        sockRouteDestIter < SoAd_GetSocketRouteDestEndIdxOfSocketRoute(sockRouteIter);
        sockRouteDestIter++ )
      {
        /* #2000 Check if at least one routing group is enabled for this socket route destination. */
        if ( SoAd_RouteGrp_CheckAnyRoutGrpOnSockRouteDestEnabled((SoAd_SizeOfSocketRouteDestType)sockRouteDestIter) ==
          TRUE )
        {
#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
          pduDiscarded = FALSE;
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

          /* #20000 Forward data to user and stop iteration. */
          SoAd_RxIf_UdpReceivePdu((SoAd_SizeOfSocketRouteDestType)sockRouteDestIter, BufPtr, Length, ErrorIdPtr);      /* SBSW_SOAD_POINTER_FORWARD */
          break;
        }
      }
    }
    /* #21 Assume socket route uses TP-API otherwise. */
    else
    {
      /* #210 Get the first socket route destination since exactly one destination exists for TP-API. */
      sockRouteDestIdx = SoAd_GetSocketRouteDestStartIdxOfSocketRoute(sockRouteIter);

      /* #211 Check if at least one routing group is enabled for this socket route destination. */
      if ( SoAd_RouteGrp_CheckAnyRoutGrpOnSockRouteDestEnabled(sockRouteDestIdx) == TRUE )
      {
#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
        pduDiscarded = FALSE;
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

        SoAd_RxTp_UdpReceivePdu(sockRouteDestIdx, BufPtr, Length);                                                     /* SBSW_SOAD_POINTER_FORWARD */
      }
    }
  }

#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
  /* #30 Check if all routing groups were disabled for this socket connection. */
  if ( pduDiscarded == TRUE )
  {
    /* #300 Increment the dropped UDP PDU counter (if GetResetMeasurementData API is enabled). */
    SoAd_Measure_Inc(SOAD_MEAS_DROP_UDP, 1);
  }
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */
} /* SoAd_RxUdp_RxIndication() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_RxBufStruct_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxBufStruct_Init(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRxBufStructMgtType bufMgtIdx = SoAd_GetRxBufStructMgtIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize buffer struct. */
  if ( SoAd_IsRxBufStructMgtUsedOfSoCon(SoConIdx) )
  {
    SoAd_SetRxBufStructSegIdxOfRxBufStructMgt(bufMgtIdx, SoAd_GetRxBufStructSegStartIdxOfSoCon(SoConIdx));             /* SBSW_SOAD_OPTIONAL_CHECKED_CSL03 */
    SoAd_SetRxBufStructSegLvlOfRxBufStructMgt(bufMgtIdx, 0u);                                                          /* SBSW_SOAD_OPTIONAL_CHECKED_CSL03 */
  }
} /* SoAd_RxBufStruct_Init() */

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_WriteSegment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxBufStruct_WriteSegment(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) SrcBufPtr,
  uint16 SrcBufLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxBufStructMgtType bufMgtIdx = SoAd_GetRxBufStructMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfRxBufStructSegType bufSegIdx = SoAd_GetRxBufStructSegIdxOfRxBufStructMgt(bufMgtIdx);
  Std_ReturnType                retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if new data is available. */
  if ( SrcBufLen > 0u )
  {
    /* #20 Write first buffer struct segment if struct is empty. */
    if ( SoAd_GetRxBufStructSegLvlOfRxBufStructMgt(bufMgtIdx) == 0u )
    {
      SoAd_SetLenOfRxBufStructSeg(bufSegIdx, SrcBufLen);                                                               /* SBSW_SOAD_CALCULATED_CSL03_RxBufStructSeg */
      SoAd_SetDataPtrOfRxBufStructSeg(bufSegIdx, SrcBufPtr);                                                           /* SBSW_SOAD_CALCULATED_CSL03_RxBufStructSeg */
      SoAd_IncRxBufStructSegLvlOfRxBufStructMgt(bufMgtIdx);                                                            /* SBSW_SOAD_OPTIONAL_CSL03 */

      retVal = E_OK;
    }
    /* #21 Write additional segment otherwise. */
    else
    {
      retVal = SoAd_RxBufStruct_WriteAdditionalSegment(SoConIdx, SrcBufPtr, SrcBufLen);                                /* SBSW_SOAD_POINTER_FORWARD */
    }
  }
  /* #11 Succeed call without any further action otherwise. */
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_RxBufStruct_WriteSegment() */

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_WriteAdditionalSegment()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxBufStruct_WriteAdditionalSegment(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) SrcBufPtr,
  uint16 SrcBufLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  SOAD_P2VAR(uint8)                           bufSegPtr;
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxBufStructMgtType               bufMgtIdx = SoAd_GetRxBufStructMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfRxBufStructSegType               lastIdx;
  SoAd_SizeOfRxBufStructSegType               writeIdx;
  SoAd_RxBufStructSegLvlOfRxBufStructMgtType  lastLvl;
  Std_ReturnType                              retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate index of last segment. */
  lastLvl = (SoAd_RxBufStructSegLvlOfRxBufStructMgtType)(SoAd_GetRxBufStructSegLvlOfRxBufStructMgt(bufMgtIdx) - 1u);
  lastIdx = SoAd_RxBufStruct_CalculateNextSegment(SoConIdx, SoAd_GetRxBufStructSegIdxOfRxBufStructMgt(bufMgtIdx),
    lastLvl);
  bufSegPtr = SoAd_GetDataPtrOfRxBufStructSeg(lastIdx);

  /* #20 Ignore adding segment if function is called with last segment (used to continue reception in main context). */
  if ( &SrcBufPtr[0] == &bufSegPtr[0u] )
  {
    retVal = E_OK;
  }
  /* #21 Check if new segment is in same memory segment like last segment otherwise. */
  else if ( &SrcBufPtr[0] == &bufSegPtr[SoAd_GetLenOfRxBufStructSeg(lastIdx)] )
  {
    /* #210 Update length of last segment. */
    SoAd_SetLenOfRxBufStructSeg(lastIdx, SoAd_GetLenOfRxBufStructSeg(lastIdx) + SrcBufLen);                            /* SBSW_SOAD_CALCULATED_CSL03_RxBufStructSeg */

    retVal = E_OK;
  }
  /* #22 Check if struct size is sufficient for new segment otherwise. */
  else if ( SOAD_RX_BUF_SEG_SIZE_TOTAL > SoAd_GetRxBufStructSegLvlOfRxBufStructMgt(bufMgtIdx) )
  {
    /* #220 Get next segment. */
    writeIdx = SoAd_RxBufStruct_CalculateNextSegment(SoConIdx,
      SoAd_GetRxBufStructSegIdxOfRxBufStructMgt(bufMgtIdx),
      SoAd_GetRxBufStructSegLvlOfRxBufStructMgt(bufMgtIdx));

    /* #221 Write new segment. */
    SoAd_SetLenOfRxBufStructSeg(writeIdx, SrcBufLen);                                                                  /* SBSW_SOAD_CALCULATED_CSL03_RxBufStructSeg */
    SoAd_SetDataPtrOfRxBufStructSeg(writeIdx, SrcBufPtr);                                                              /* SBSW_SOAD_CALCULATED_CSL03_RxBufStructSeg */
    SoAd_IncRxBufStructSegLvlOfRxBufStructMgt(bufMgtIdx);                                                              /* SBSW_SOAD_OPTIONAL_CSL03 */

    retVal = E_OK;
  }
  /* #23 Reject request otherwise. */
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /* SoAd_RxBufStruct_WriteAdditionalSegment() */

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_CalculateNextSegment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_SizeOfRxBufStructSegType, SOAD_CODE) SoAd_RxBufStruct_CalculateNextSegment(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfRxBufStructSegType SegmentIndex,
  SoAd_RxBufStructSegLvlOfRxBufStructMgtType SegmentLvl)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRxBufStructSegType NextSegmentIndex;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate next segment index if struct wraps around. */
  if ( (SegmentIndex + SegmentLvl) >= SoAd_GetRxBufStructSegEndIdxOfSoCon(SoConIdx) )
  {
    NextSegmentIndex = (SoAd_SizeOfRxBufStructSegType)(SoAd_GetRxBufStructSegStartIdxOfSoCon(SoConIdx) +
      (SegmentLvl - (SoAd_GetRxBufStructSegEndIdxOfSoCon(SoConIdx) - SegmentIndex)));
  }
  /* #11 Calculate next segment index if struct does not wrap around otherwise. */
  else
  {
    NextSegmentIndex = (SoAd_SizeOfRxBufStructSegType)(SegmentIndex + SegmentLvl);
  }

  return NextSegmentIndex;
} /* SoAd_RxBufStruct_CalculateNextSegment() */

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_GetSegment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxBufStruct_GetSegment(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 BufSegOffset,
  P2VAR(uint8*, AUTOMATIC, SOAD_APPL_VAR) BufSegPtr,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) BufSegLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SOAD_P2VAR(uint8)             tmpBufSegPtr;
  uint32                        localBufSegOffset = BufSegOffset;
  SoAd_SizeOfRxBufStructMgtType bufMgtIdx = SoAd_GetRxBufStructMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfRxBufStructSegType bufSegIdx = SoAd_GetRxBufStructSegIdxOfRxBufStructMgt(bufMgtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to get the segment of the specified offset. */
  if ( SoAd_RxBufStruct_GetBufSegIdx(SoConIdx, &localBufSegOffset, &bufSegIdx) == E_OK )                               /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    tmpBufSegPtr = SoAd_GetDataPtrOfRxBufStructSeg(bufSegIdx);
    *BufSegPtr = &tmpBufSegPtr[localBufSegOffset];                                                                     /* SBSW_SOAD_POINTER_WRITE */
    *BufSegLenPtr = (uint32)(SoAd_GetLenOfRxBufStructSeg(bufSegIdx) - localBufSegOffset);                              /* SBSW_SOAD_POINTER_WRITE */
  }
  /* #11 Indicate that no segment is available otherwise. */
  else
  {
    *BufSegPtr = SoAd_GetDataPtrOfRxBufStructSeg(bufSegIdx);                                                           /* SBSW_SOAD_POINTER_WRITE */
    *BufSegLenPtr = 0u;                                                                                                /* SBSW_SOAD_POINTER_WRITE */
  }
} /* SoAd_RxBufStruct_GetSegment() */

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_GetTotLen()
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
SOAD_LOCAL_INLINE FUNC(uint32, SOAD_CODE) SoAd_RxBufStruct_GetTotLen(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 BufSegOffset)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                        localBufSegOffset = BufSegOffset;
  uint32                        totalLen = 0u;
  SoAd_RxBufStructSegIterType   bufSegIter;
  SoAd_SizeOfRxBufStructMgtType bufMgtIdx = SoAd_GetRxBufStructMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfRxBufStructSegType bufSegIdx = SoAd_GetRxBufStructSegIdxOfRxBufStructMgt(bufMgtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all segments to get the segment of the specified offset. */
  for ( bufSegIter = 0u;
    bufSegIter < SoAd_GetRxBufStructSegLvlOfRxBufStructMgt(bufMgtIdx);
    bufSegIter++ )
  {
    /* #20 Check if offset is in next buffer segment. */
    if ( localBufSegOffset >= SoAd_GetLenOfRxBufStructSeg(bufSegIdx) )
    {
      /* #200 Decrement offset by length of current segment. */
      localBufSegOffset -= SoAd_GetLenOfRxBufStructSeg(bufSegIdx);
    }
    /* #21 Consider current buffer segment otherwise. */
    else
    {
      /* #210 Increment total length. */
      totalLen += (uint32)(SoAd_GetLenOfRxBufStructSeg(bufSegIdx) - localBufSegOffset);

      /* #211 Set offset to zero to increment total length by whole segment length of next segments. */
      localBufSegOffset = 0u;
    }

    /* #30 Calculate next segment index considering buffer struct wrap around. */
    if ( (bufSegIdx + 1u) == SoAd_GetRxBufStructSegEndIdxOfSoCon(SoConIdx) )
    {
      bufSegIdx = SoAd_GetRxBufStructSegStartIdxOfSoCon(SoConIdx);
    }
    else
    {
      bufSegIdx++;
    }
  }

  return totalLen;
} /* SoAd_RxBufStruct_GetTotLen() */

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_Copy2Buf()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxBufStruct_Copy2Buf(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, SOAD_APPL_DATA, SOAD_APPL_DATA) BufPtr,
  uint32 BufLen,
  uint32 BufSegOffset)
{
  /* ----- Local Variables ---------------------------------------------- */
  SOAD_P2VAR(uint8)             bufSegPtr;
  uint32                        localBufLen = BufLen;
  uint32                        localBufSegOffset = BufSegOffset;
  uint32                        bytesToCopy;
  uint32                        bytesCopied = 0u;
  uint32                        segOffset;
  SoAd_SizeOfRxBufStructSegType bufSegIdx = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate until all data is copied to provided buffer. */
  while ( localBufLen > 0u )
  {
    /* #20 Get index of segment from which shall be copied considering offset. */
    segOffset = localBufSegOffset;
    (void)SoAd_RxBufStruct_GetBufSegIdx(SoConIdx, &segOffset, &bufSegIdx);                                             /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

    /* #30 Calculate available data length of segment. */
    bytesToCopy = (uint32)(SoAd_GetLenOfRxBufStructSeg(bufSegIdx) - segOffset);

    /* #40 Calculate data length to be copied for this segment. */
    if ( localBufLen < bytesToCopy )
    {
      bytesToCopy = localBufLen;
    }

    /* #50 Copy data from current segment to provided buffer. */
    bufSegPtr = SoAd_GetDataPtrOfRxBufStructSeg(bufSegIdx);
    /* PRQA S 314 3 */ /* MD_MSR_VStdLibCopy */
    VStdMemCpy(                                                                                                        /* SBSW_SOAD_POINTER_WITH_OFFSET_AND_CONST_POINTER_FORWARD */
      SOAD_A_P2VAR(void)&BufPtr[bytesCopied],
      SOAD_A_P2CONST(void)&bufSegPtr[segOffset],
      bytesToCopy);
    localBufLen -= bytesToCopy;
    bytesCopied += bytesToCopy;
    localBufSegOffset += bytesToCopy;
  }
} /* SoAd_RxBufStruct_Copy2Buf() */

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_GetBufSegIdx()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RxBufStruct_GetBufSegIdx(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) OffsetPtr,
  P2VAR(SoAd_SizeOfRxBufStructSegType, AUTOMATIC, SOAD_APPL_VAR) BufSegIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                        offset = *OffsetPtr;
  SoAd_RxBufStructSegIterType   bufSegIter;
  SoAd_SizeOfRxBufStructMgtType bufMgtIdx = SoAd_GetRxBufStructMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfRxBufStructSegType bufSegIdx = SoAd_GetRxBufStructSegIdxOfRxBufStructMgt(bufMgtIdx);
  Std_ReturnType                retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all segments to get the segment of the specified offset. */
  for ( bufSegIter = 0u;
    bufSegIter < SoAd_GetRxBufStructSegLvlOfRxBufStructMgt(bufMgtIdx);
    bufSegIter++)
  {
    /* #20 Check if offset is in next buffer segment. */
    if ( offset >= SoAd_GetLenOfRxBufStructSeg(bufSegIdx) )
    {
      /* #30 Decrement offset by length of current segment. */
      offset -= SoAd_GetLenOfRxBufStructSeg(bufSegIdx);

      /* #40 Calculate next segment index considering buffer struct wrap around. */
      if ( (bufSegIdx + 1u) == SoAd_GetRxBufStructSegEndIdxOfSoCon(SoConIdx) )
      {
        bufSegIdx = SoAd_GetRxBufStructSegStartIdxOfSoCon(SoConIdx);
      }
      else
      {
        bufSegIdx++;
      }
    }
    /* #21 Return current index otherwise. */
    else
    {
      *BufSegIdxPtr = bufSegIdx;                                                                                       /* SBSW_SOAD_POINTER_WRITE */
      *OffsetPtr = offset;                                                                                             /* SBSW_SOAD_POINTER_WRITE */
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* SoAd_RxBufStruct_GetBufSegIdx() */

/**********************************************************************************************************************
 *  SoAd_RxBufStruct_ReleaseSegment()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RxBufStruct_ReleaseSegment(
  SoAd_SizeOfSoConType SoConIdx,
  uint32 Len)
{
  /* ----- Local Variables ---------------------------------------------- */
  SOAD_P2VAR(uint8)                           bufSegPtr;
  uint32                                      localLen = Len;
  SoAd_RxBufStructSegIterType                 bufSegIter;
  /* Optional indirection: Refer to parameter value range in function description. */
  SoAd_SizeOfRxBufStructMgtType               bufMgtIdx = SoAd_GetRxBufStructMgtIdxOfSoCon(SoConIdx);
  SoAd_RxBufStructSegLvlOfRxBufStructMgtType  bufSegLvl = SoAd_GetRxBufStructSegLvlOfRxBufStructMgt(bufMgtIdx);
  SoAd_SizeOfRxBufStructSegType               bufSegIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all segments. */
  for ( bufSegIter = 0u; bufSegIter < bufSegLvl; bufSegIter++ )
  {
    bufSegIdx = SoAd_GetRxBufStructSegIdxOfRxBufStructMgt(bufMgtIdx);
    bufSegPtr = SoAd_GetDataPtrOfRxBufStructSeg(bufSegIdx);

    /* #20 Release in current segment and stop iteration if segment length is bigger than length to be released. */
    if ( localLen < SoAd_GetLenOfRxBufStructSeg(bufSegIdx) )
    {
      SoAd_SetLenOfRxBufStructSeg(bufSegIdx, (SoAd_LenOfRxBufStructSegType)(                                           /* SBSW_SOAD_CALCULATED_CSL03_RxBufStructSeg */
        SoAd_GetLenOfRxBufStructSeg(bufSegIdx) - localLen));
      SoAd_SetDataPtrOfRxBufStructSeg(bufSegIdx, &bufSegPtr[localLen]);                                                /* SBSW_SOAD_CALCULATED_CSL03_RxBufStructSeg */

      break;
    }
    /* #21 Release segment completely otherwise. */
    else
    {
      /* #210 Reset segment length and decrement length to be released. */
      localLen -= SoAd_GetLenOfRxBufStructSeg(bufSegIdx);
      SoAd_SetLenOfRxBufStructSeg(bufSegIdx, 0u);                                                                      /* SBSW_SOAD_CALCULATED_CSL03_RxBufStructSeg */
      SoAd_DecRxBufStructSegLvlOfRxBufStructMgt(bufMgtIdx);                                                            /* SBSW_SOAD_OPTIONAL_CSL03 */

      /* #211 Calculate next segment index considering buffer struct wrap around. */
      if ( (bufSegIdx + 1u) == SoAd_GetRxBufStructSegEndIdxOfSoCon(SoConIdx) )
      {
        SoAd_SetRxBufStructSegIdxOfRxBufStructMgt(bufMgtIdx, SoAd_GetRxBufStructSegStartIdxOfSoCon(SoConIdx));         /* SBSW_SOAD_OPTIONAL_CSL03 */
      }
      else
      {
        SoAd_SetRxBufStructSegIdxOfRxBufStructMgt(bufMgtIdx, (SoAd_RxBufStructSegIdxOfRxBufStructMgtType)              /* SBSW_SOAD_OPTIONAL_CSL03 */
          (SoAd_GetRxBufStructSegIdxOfRxBufStructMgt(bufMgtIdx) + 1u));
      }
    }
  }
} /* SoAd_RxBufStruct_ReleaseSegment() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_Rx_InitSoCon()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_Rx_InitSoCon(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRxMgtType          rxMgtIdx = SoAd_GetRxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfRxBufferConfigType rxBufCfgIdx = SoAd_GetRxBufferConfigIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize rx struct elements. */
  if ( SoAd_IsRxMgtUsedOfSoCon(SoConIdx) )
  {
    SoAd_SetSocketRouteDestIdxOfRxMgt(rxMgtIdx, SoAd_GetSizeOfSocketRouteDest());                                      /* SBSW_SOAD_OPTIONAL_CHECKED_CSL03 */
    SoAd_SetRxBytesPendingOfRxMgt(rxMgtIdx, 0u);                                                                       /* SBSW_SOAD_OPTIONAL_CHECKED_CSL03 */
    SoAd_SetCancelRequestedOfRxMgt(rxMgtIdx, FALSE);                                                                   /* SBSW_SOAD_OPTIONAL_CHECKED_CSL03 */
  }

#if ( SOAD_TCP == STD_ON )
  /* #20 Initialize rx buffer struct (if TCP is enabled). */
  SoAd_RxBufStruct_Init(SoConIdx);
#endif /* SOAD_TCP == STD_ON */

  if ( SoAd_IsRxBufferConfigUsedOfSoCon(SoConIdx) )
  {
#if ( SOAD_TCP == STD_ON )
    /* #30 Initialize rx buffer for IF-API (if TCP is enabled). */
    if ( SoAd_IsIfRxBufferUsedOfRxBufferConfig(rxBufCfgIdx) )
    {
      SoAd_SetIfRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx, SoAd_GetIfRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx));  /* SBSW_SOAD_OPTIONAL_CHECKED_CSL03 */
    }
#endif /* SOAD_TCP == STD_ON */

    /* #40 Initialize rx buffer for TP-API. */
#if ( SOAD_TCP == STD_ON )
    if ( SoAd_IsTpRxBufferUsedOfRxBufferConfig(rxBufCfgIdx) )
#endif /* SOAD_TCP == STD_ON */
    {
      SoAd_SetTpRxBufferIdxOfRxBufferConfigDyn(rxBufCfgIdx, SoAd_GetTpRxBufferStartIdxOfRxBufferConfig(rxBufCfgIdx));  /* SBSW_SOAD_OPTIONAL_CHECKED_CSL03 */
    }
  }
} /* SoAd_Rx_InitSoCon() */

/**********************************************************************************************************************
 *  SoAd_Rx_RxIndication()
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
FUNC(void, SOAD_CODE) SoAd_Rx_RxIndication(
  SoAd_SizeOfSocketType SockIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx);
#if ( SOAD_TCP == STD_ON )
  Std_ReturnType        retVal = E_NOT_OK;
#endif /* SOAD_TCP == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check socket dependent parameter. */
  if ( SoAd_Rx_CheckSocketParameter(SockIdx) == E_OK )
  {
    /* #20 Get socket connection index. */
    if ( SoAd_Rx_GetSoConIdx(SockIdx, RemoteAddrPtr, BufPtr, Length, &soConIdx) == E_OK )                              /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    {
      /* #30 Check socket connection dependent parameter. */
      if ( SoAd_Rx_CheckSoConParameter(soConIdx, RemoteAddrPtr) == E_OK )                                              /* SBSW_SOAD_POINTER_FORWARD */
      {
        /* #40 Update alive timeout (if enabled). */
        SoAd_SoCon_UpdateUdpAliveTimeout(soConIdx);

        /* #50 Update received remote address (if enabled). */
        SoAd_SoCon_UpdateRcvRemoteAddress(soConIdx, RemoteAddrPtr);                                                    /* SBSW_SOAD_POINTER_FORWARD */

        /* #60 Forward received data dependent on protocol and PDU header configuration. */
        SoAd_Rx_RxIndicationProtocol(soConIdx, BufPtr, Length, ErrorIdPtr);                                            /* SBSW_SOAD_POINTER_FORWARD */

#if ( SOAD_TCP == STD_ON )
        retVal = E_OK;
#endif /* SOAD_TCP == STD_ON */
      }
    }
  }

#if ( SOAD_TCP == STD_ON )
  /* #70 Release TCP reception buffer if error occurred on TCP socket (if enabled). */
  if ( (retVal == E_NOT_OK) && SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) )
  {
    SoAd_TcpIp_TcpReceived(SockIdx, Length);
  }
#endif /* SOAD_TCP == STD_ON */
} /* SoAd_Rx_RxIndication() */

/**********************************************************************************************************************
 *  SoAd_Rx_TpStartOfReception()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_TpStartOfReception(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Forward call request to sub-component. */
  return SoAd_RxTp_StartOfReception(SoConIdx);
} /* SoAd_Rx_TpStartOfReception */

/**********************************************************************************************************************
 *  SoAd_Rx_TpCancelReceive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_TpCancelReceive(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Forward reception cancellation request to sub-component. */
  return SoAd_RxTp_CancelReceive(SockRouteDestIdx);
} /* SoAd_Rx_TpCancelReceive() */

/**********************************************************************************************************************
 *  SoAd_Rx_TerminateReceive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_Rx_TerminateReceive(
  SoAd_SizeOfSoConType SoConIdx,
  boolean NormalClose)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Terminate active TP session. */
  SoAd_RxTp_TerminateReceive(SoConIdx, NormalClose);

  /* #20 Initialize rx struct elements. */
  SoAd_Rx_InitSoCon(SoConIdx);
} /* SoAd_Rx_TerminateReceive() */

/**********************************************************************************************************************
 *  SoAd_Rx_HandleReception()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_Rx_HandleReception(
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle TP reception. */
  SoAd_RxTp_HandleReception(ErrorIdPtr);                                                                               /* SBSW_SOAD_POINTER_FORWARD */
} /* SoAd_Rx_HandleReception() */

#define SOAD_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/* Justification for module-specific MISRA deviations:
 * see file SoAd.c
 */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_Rx.c
 *********************************************************************************************************************/
