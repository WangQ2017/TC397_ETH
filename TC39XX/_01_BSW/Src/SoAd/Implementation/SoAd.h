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
/**        \file  SoAd.h
 *        \brief  Socket Adaptor header file
 *
 *      \details  Vector static code header file for AUTOSAR Socket Adaptor module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author      Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *   1.00.00  2008-08-10  visalr      -             created
 *   1.00.01  2008-12-12  visalr      -             All:  TCPIP_INV_SOCK_IDX instead of TCPIP_INVALID_SOCKET_HND used
 *                                    -             DoIp: deny routing activation for last socket
 *                                    -             DoIp: use DoIp_UdpTgtPort for tx instead of configured local port
 *                                    -             DoIp: inconsistent AliveCheckRequest length with multiple sockets
 *                                    -             DoIp: keep socket open for new routing request on open socket from
 *                                                        new tester
 *                                    -             All:  TCPIP_INV_SOCK_IDX replaced by SOAD_INV_SOCK_IDXX
 *                                    -             SoAd: DET instead of tx with invalid SockHnd
 *   1.00.02  2009-03-16  visalr      -             DoIp: refuse DiagAck from Tester
 *                                    -             DoIp: do not close UDP socket after VehicleIdent with invalid
 *                                    -                   payload length
 *                                    -             DoIp: check max length (DOIP_VMAX_TX_BUF_LEN_BYTE_TOTAL)
 *                                    -             All:  peer review
 *                                    -             DoIp: multiple RxIndication per DoIp message
 *                                    -             DoIp: single alive check request
 *                                    -             SoAd: bugfix for DET error if ConfigVariant != 3
 *   1.00.03  2009-04-01  visalr      -             DoIp: new DoIP msg ids (functional groups)
 *                                    -             DoIp: Port 13400 configured (== ISO 13400)
 *   1.01.00  2009-04-16  visalr      -             SoAd: new DoIP msg ids (functional groups)
 *                                    -             SoAd: WinSock API support
 *                                    -             DoIp: TestAddr and GwAddr exchanged in DoIp_RoutActiveAckType
 *   1.02.00  2009-07-31  visalr      -             PduR: SoAdPduR_Transmit bugfix, provide tx buffer in PduInfoTgt
 *                                    -             SoAd: SoAd_RxIndication bugfix, wrong byte order hdr length with
 *                                                        multiple PDUs
 *                                    -             All:  ComIp renamed to SoAd_PduR, DoIp renamed to SoAd_DoIp
 *                                    -             DoIp: wrong length calculation in RxIndication
 *                                    -             DoIp: Routing Activation Ack Oem Extension support
 *                                    -             All:  new DET macros
 *                                    -             All:  BRS Time Measurement support added
 *                                    -             SoAd: Config variant check for library build
 *                                    -             DoIp: bugfix socket state change
 *                                    -             DoIp: removed tester addresses from configuration (change in Spec)
 *   1.02.01  2009-08-14  visalr      -             DoIP: new DoIP msg ids (functional groups)
 *                                    -             DoIp: RAM arrays from impelementation to Lcfg moved
 *   1.03.00  2009-09-15  visalr      -             DoIP: SoAdDoIp_Transmit() fixed for handling of Pbuf with two
 *                                                        elements
 *                                    -             SoAd: removed one DET check in SoAd_VTransmit()
 *                                    -             SoAd: Pbuf fix/patch in SoAd_VXxTransmit()
 *                                    -             DoIP: bugfix reset only DoIp sockets if socket gets closed
 *                                    -             SoAd: Config version check
 *                                    -             SoAd: bugfix compiler switches for SoAd_ShutdownFinishedCnt
 *                                                        inconsistent
 *                                    -             SoAd: bugfix decrement SoAd_OpenTcpSockets if RST rxd
 *                                    -             SoAd: bugfix issue SoAd_ShutdownFinishedFcts only if SoAd_Shutdown
 *                                                        was called
 *                                    -             All:  enlarge data type for some configuration variables for 1ms
 *                                                        cycles
 *                                    -             DoIP: bugfix for Pbuf with wrap around
 *                                    -             SoAd: bugfix do not accept connections after SoAd_Shutdown was
 *                                                        called
 *                                    -             DoIP: bugfix do not issue TxConfirmation for DiagAck; issue single
 *                                                        TxConfirmation only
 *                                    -             DoIP: enable tx before rx (FBL has to tx EcuResetAck after
 *                                                        EcuReset)
 *                                    -             SoAd: TcpIp_Shutdown added
 *                                    -             SoAd: DoIp_GetVersionInfo added
 *                                    -             SoAd: Pdu -> TxPdu renamed (PduR integration)
 *                                    -             SoAd: API_ID space >= 0x80 cleared (reserved for TcpIp)
 *   1.04.00  2009-09-28  visalr      -             SoAd: PduR integration
 *                                    -             SoAd: bugfix length check in SoAd_VCopy2Pbuf
 *   1.04.01  2009-09-29  visalr      -             SoAd: PrepareShutdown introduced
 *   1.04.02  2009-09-29  visalr      -             All:  Memory Abstraction for stack local pointer
 *                                    -             All:  bugfix support all configuration variants
 *   1.04.03  2009-10-02  visalr      -             All:  bugfix include files adapted
 *                                    -             All:  single module header introduced (single source)
 *   1.05.00  2009-10-05  visalr      -             no changes
 *   1.05.01  2009-10-05  visalr      -             no changes
 *   2.00.00  2009-10-08  visalr      -             no changes
 *   2.00.01  2009-10-09  visalr      -             SoAd: API for DETs within Lcfg added
 *   2.00.02  2009-10-15  visalr      -             All:  comment format updated
 *   2.00.03  2010-01-11  visalr      -             All:  bugfix during optimization
 *                                    -             All:  bugfix DET checks without actual condition did not fire
 *                                    -             DoIP: new version of Spec (file date 2009-11-12)
 *                                                        change: target port for Vehicle Announgement (13400 -> 13401,
 *                                                        cfg only)
 *                                                        rename: hardware id -> entity id (HWID -> EID)
 *                                                        extension: group id GID in Vehicle Announcement
 *                                    -             DoIP: DET checks extended (DETs if ProvideTxBuffer fails)
 *                                    -             All:  DET check bugfixing
 *                                    -             All:  support multiple calls of SoAd_Init
 *                                    -             DoIP: bugfix backwards compatibility for pre-compile+link time
 *                                                        config
 *   2.01.00  2010-02-11  visalr      ESCAN00040295 SoAd: Pdu Header: PduId and PduLength field are too small
 *                                    ESCAN00040760 Wrong module id returned
 *                                    ESCAN00041001 Access violation during data copy
 *                                    ESCAN00041033 Overwritten memory during TCP connection setup
 *   2.01.01  2010-06-25  visalr      -             E_PENDING removed (meanwhile defined by Std_Types.h)
 *                                    ESCAN00043588 DoIP: Behaviour after VehicleIdentification during Vehicle
 *                                                        Announcement is weird
 *                                    ESCAN00044554 SoAd: Compiler error using SoAd_Types.h without SoAd config
 *   2.01.02  2010-09-17  visalr      ESCAN00045481 DoIP: SoAd_GetVinFct causes access violation if no valid ptr is
 *                                                        returned
 *   2.02.00  2010-10-01  visalr      ESCAN00045750 Replace external reference to VCopy()
 *            2010-12-22  visalr      ESCAN00047347 Adapt MainFunction for usage with IdentityManagerConfig
 *            2011-01-20  visalr      -             ApplTp example for GM
 *   2.02.01  2011-01-24  visalr      -             Update GENy version check
 *   2.02.02  2011-01-27  visalr      -             ModHdr removed
 *   2.02.03  2011-02-07  visalr      ESCAN00046261 Adapt AUTOSAR version check
 *   2.02.04  2011-02-08  visalr      -             Bugfix: Adapt AUTOSAR version check
 *            2011-02-11  visalr      ESCAN00048016 MemMap.h: Missing Start/Stop Sections (PBCFG_ROOT)
 *   2.02.05  2011-03-04  visalr                    missing comment within SoAd_Compiler_Cfg.inc
 *   2.03.00  2011-05-31  visalr      ESCAN00050523 Generate SoAd  EcuC Global Configuration Container Name
 *            2011-05-31  visalr                    PduR interface changed
 *   2.03.01  2011-06-17  visalr                    PduR interface changed bugfix
 *   2.03.02  2011-06-17  visalr                    PduR interface changed bugfix
 *   2.03.03  2011-07-12  visalr      ESCAN00052122 SoAd copies wrong data (SoAd_TcpIpRxIndication: DataPtr should be
 *                                                  used)
 *   2.03.04  2011-07-12  visalr      ESCAN00052122 SoAd copies wrong data (SoAd_TcpIpRxIndication: DataPtr should be
 *                                                  used)
 *   2.03.05  2011-09-07  visalr      ESCAN00053390 Addtional preprocessor argument for macro without DEM has to be
 *                                                  removed
 *   2.03.06  2011-09-19  visalr      ESCAN00053696 Suport Snv prefix in Dem error codes (SOAD_E_IO -> Dem_SOAD_E_IO)
 *   2.03.07  2011-09-23  visalr                    GHS compiler warnings resolved (undefined preprocessing identifier)
 *   2.03.08  2011-09-26  visalr      ESCAN00052825 DET check on buffer size in SoAd.c not correct
 *   2.03.09  2011-10-21  visalr      ESCAN00053993 Compiler warning: ADD HERE A SHORT DESCRIPTION
 *   3.00.00  2011-12-08  visalr      ESCAN00055435 Extend functionality for IPv6
 *   3.00.01  2012-02-07  viswmc      ESCAN00056665 SoAd:      Compiler error: Argument of incompatible type
 *   3.01.00  2011-12-21  viswmc      ESCAN00055422 SoAd:      Support for UdpNm and other upper layer protocols added,
 *                                                             which do not use the PduR API
 *            2011-12-21  viswmc      ESCAN00055424 SoAd/DoIP: Evaluation of SoAdDoIp_Transmit() return value added
 *            2011-12-21  viswmc      ESCAN00055685 DoIP:      Adaptation to new Routing Activation Request header
 *                                                             format; element for activation type added
 *            2011-12-21  viswmc      ESCAN00055738 DoIP:      Adapted NACK codes for Routing Activation Response and
 *                                                             Diagnostic Message Negative Acknowledgment
 *            2011-12-22  viswmc      ESCAN00055767 SoAd:      Callback function SoAd_BusSM_ModeIndication() added
 *                                                             (called by EthSM)
 *            2012-01-18  viswmc      ESCAN00054711 SoAd/DoIP: Adapted call-back functions for GID, VIN and
 *                                                             DiagPowerMode to match the provided Appl_SoAd files
 *   3.02.00  2012-03-30  viswmc      ESCAN00057319 SoAd/DoIP: Component review: Compiler abstraction, DET checks,
 *                                                             unsigned identifier, improved PDU header option,
 *                                                             minor changes
 *            2012-03-30  viswmc      ESCAN00058039 DoIP:      DoIP, positive response on Diagnostic Message although
 *                                                             no Routing Activation Request was sent
 *            2012-03-30  viswmc      ESCAN00056359 SoAd/DoIP: VAR_INIT / VAR_ZERO_INIT Memory Mapping sections
 *            2012-03-30  viswmc      ESCAN00056360 SoAd/DoIP: Remove Macro support for Version Info API
 *   3.03.00  2012-05-08  viswmc      ESCAN00058792 SoAd:      New parameter in SoAd_Cbk_LocalIpAssignmentChg()
 *            2012-07-02  viswmc      ESCAN00058887 SoAd/DoIP: AR4-125: Remove support for v_cfg.h in Cfg5 systems
 *   3.04.00  2012-07-23  viswmc      ESCAN00060256 SoAd/DoIP: Renaming of SOAD_PDUR_API_ASR_30/40 to
 *                                                             SOAD_PDUR_API_ASR30/40
 *            2012-07-23  viswmc      ESCAN00060257 DoIP:      DoIP: Routing dependent on packet size
 *            2012-07-23  viswmc      ESCAN00060258 SoAd:      Add support for XCP routing
 *            2012-07-23  viswmc      ESCAN00055643 DoIP:      DoIP functional addressing not supported
 *            2012-07-23  viswmc      ESCAN00060271 DoIP:      DoIP: Out of order response messages
 *            2012-07-23  viswmc      ESCAN00060273 SoAd:      Send UDP response messages to the port from which the
 *                                                             request was sent
 *   3.05.00  2012-08-30  viswmc      ESCAN00060291 SoAd/DoIP: SoAd shall support IPv6
 *            2012-08-30  viswmc      ESCAN00060295 SoAd/DoIP: SoAd shall support PduR API according to AUTOSAR4 for
 *                                                             the DoIP use-case
 *            2012-08-30  viswmc      ESCAN00061096 SoAd/DoIP: DoIP performance optimization
 *            2012-08-30  viswmc      ESCAN00061101 SoAd/DoIP: SoAd/DoIP module clean-up
 *            2012-09-28  vismda      ESCAN00061275 SoAd:      Support BSW Scheduler AUTOSAR 4
 *            2012-09-28  vismda      ESCAN00061811 SoAd:      Update supported AUTOSAR version
 *            2012-10-16  vismda      ESCAN00062250 SoAd/DoIP: AR4-220: Remove STATIC
 *            2012-10-30  vismda      ESCAN00062571 SoAd/DoIP: Added SOAD_VAR_ZERO_INIT to compiler_cfg.h
 *            2012-10-30  vismda      ESCAN00062573 SoAd/DoIP: SoAdDoIp_VCfgEId undefined if EID disabled
 *            2012-10-30  vismda      ESCAN00061428 SoAd/DoIP: AR4-210: Support of MSR4 SoAD
 *   3.05.01  2012-11-06  vismda      ESCAN00062739 SoAd:      Compiler warning: PduOffset not referenced
 *            2012-11-06  vismda      ESCAN00062740 SoAd:      Compiler warning: PduInfoSrcPtr not referenced
 *            2012-11-06  vismda      ESCAN00062741 DoIP:      Compiler warning: cast truncates constant value
 *            2012-11-06  vismda      ESCAN00062742 DoIP:      Compiler warning: RxBufTcpIdx not referenced
 *            2012-11-09  vismda      ESCAN00062880 DoIP:      Wrong behavior when receiving diagnostic messages
 *            2012-11-09  vismda      ESCAN00062887 SoAd:      The ECU does not accept any incoming TCP connection
 *            2012-11-09  vismda      ESCAN00062889 DoIP:      The initial vehicle announcement messages of DoIP are
 *                                                             sent to the wrong destination port
 *            2012-11-09  vismda      ESCAN00062890 DoIP:      The initial vehicle announcement messages of DoIP are
 *                                                             sent to port 13400 instead of 13401
 *   3.05.02  2012-11-13  vismda      ESCAN00062893 DoIP:      Negative response message sent on a vehicle announcement
 *            2012-11-13  vismda      ESCAN00062908 DoIP:      Compiler error: Unresolved external symbol PBASE_SWAP16
 *            2012-11-13  vismda      ESCAN00061105 DoIP:      Support of DoIP specification version 2012
 *   3.05.03  2013-01-25  vismda      ESCAN00061105 DoIP:      Resubmitted: Support of DoIP specification version 2012
 *   3.06.00  2012-12-19  vismda      ESCAN00063796 SoAd:      Compatibility to PduR
 *            2012-12-20  vismda      ESCAN00063349 DoIP:      Usage of RTE for VIN, GID and PowerMode
 *            2013-01-10  vismda      ESCAN00063662 DoIP:      Macro to validate Routing Activation Response is
 *                                                             incorrect
 *            2013-01-10  vismda      ESCAN00063134 SoAd/DoIP: Delete selection of supported PduR API
 *            2013-02-21  vismda      ESCAN00061256 SoAd:      DEM Errors not reset
 *            2013-02-21  vismda      ESCAN00060258 SoAd:      Updated: Add support XCP routing
 *            2013-03-13  vismda      ESCAN00064980 DoIP:      DET error on IP assignment callback
 *            2013-03-21  vismda      ESCAN00065950 DoIP:      Issue in Diagnostic Message handling
 *            2013-03-27  vismda      ESCAN00065056 SoAd:      AR4-315: Support IF/TP CancelTransmit, TP CancelReceive,
 *                                                             TP ChangeParameter
 *            2013-04-09  vismda      ESCAN00066474 SoAd/DoIP: Process conformity for R7: MISRA
 *            2013-04-17  vismda      ESCAN00066917 DoIP:      AR3-2547: Decoupled confirmation after TCP transmit
 *            2013-05-08  vismda      ESCAN00067262 DoIP:      DoIP: Diagnostic Messages are replied too soon
 *   3.07.00  2013-07-09  vismda      ESCAN00064316 SoAd/DoIP: AR3-2521: Dhcp-Option DoIP-Server
 *            2013-07-09  vismda      ESCAN00068832 DoIP:      Ethernet DoIp to Lin TP Routing does not work
 *            2013-07-09  vismda      ESCAN00068561 DoIP:      Compiler error: unresolved external symbol
 *                                                             _SoAd_VXxTransmit
 *   4.00.00  2013-09-27  vismda      ESCAN00080600            Vehicle Identification Response sent before
 *                                                             A_DoIP_Announce_Wait
 *            2013-09-27  vismda      ESCAN00079050            Inconsistent storage class specification for
 *                                                             SoAdDoIp_VReSetVehicleAnnounce
 *            2013-09-27  vismda      ESCAN00074254            Support of BUFREQ_E_BUSY for <Ul>_SoAdCopyTxData()
 *            2013-09-27  vismda      ESCAN00072439            Transmission/Reception issue on multiple Diagnostic
 *                                                             Messages
 *            2013-09-27  vismda      ESCAN00063371            DoIP: Multiple testers on one DoIpRoute
 *            2013-09-27  vismda      ESCAN00059406            DoIP: DET error on Tester Present
 *            2013-09-27  vismda      ESCAN00068226            AR4-490: SoAd Support IF and TP API
 *            2013-09-27  vismda      ESCAN00068233            AR4-497: Support of PDU Header Option
 *            2013-09-27  vismda      ESCAN00069265            AR4-450: Usage of section PBCFG in PB files
 *            2013-09-27  vismda      ESCAN00068534            AR4-260: Remove SOAD_PROD_ERROR_DETECT switch define
 *   4.00.01  2013-11-07  vismda      ESCAN00071645            Remote Port not set for TCP socket (server)
 *            2013-11-07  vismda      ESCAN00071710            Issue: missing IpV6 packets
 *            2013-11-07  vismda      ESCAN00071738            Compiler error:  incompatible with object type
 *            2013-11-14  vismda      ESCAN00071713            Generation of a unspecified remote socket ROM array
 *            2013-11-15  vismda      ESCAN00071778            Issues in PduRouteDest handling
 *            2013-11-15  vismda      ESCAN00071787            Invalid socket configuration after receiving a message
 *   4.00.02  2013-11-26  vismda      ESCAN00072149            Change of link state
 *            2013-11-26  vismda      ESCAN00072221            Issue in function SoAd_VGetPbufSegment
 *            2014-01-07  vismda      ESCAN00072321            Issue in interpretation of TcpIp Pbuf
 *            2014-01-07  vismda      ESCAN00072595            No port in SoAd_GetLocalAddr()
 *            2014-01-08  vismda      ESCAN00072586            PDUs with configured HeaderId larger than 0 are not
 *                                                             received
 *   4.01.00  2014-01-31  vismda      ESCAN00071725            Additional API: SoAd_GetRcvRemoteAddr
 *            2014-01-31  vismda      ESCAN00072402            Issue with RxPduId for receive cancellation
 *            2014-01-31  vismda      ESCAN00072654            AR4-654: TxConfirmation() immediately for UDP
 *            2014-01-31  vismda      ESCAN00073294            GetRemoteAddr after tcp connect
 *            2014-01-31  vismda      ESCAN00073197            DoIP initialization over BswM
 *            2014-01-31  vismda      ESCAN00072922            Issues when socket shall be closed
 *            2014-02-03  vismda      ESCAN00073099            Header includes rework
 *            2014-02-03  vismda      ESCAN00073115            Unexpected socket connection reset
 *            2014-02-04  vismda      ESCAN00073141            Transmission via IF-API is confirmed (E_OK) although
 *                                                             socket
 *                                                             connection is offline
 *            2014-02-04  vismda      ESCAN00073418            Unexpected socket connection state SOAD_SOCON_RECONNECT
 *            2014-02-06  vismda      ESCAN00072131            AR4-635: SoAd Support TP API for UDP
 *            2014-02-06  vismda      ESCAN00072132            AR4-497: Support of PDU Header Option for UDP TP-API
 *   4.01.01  2014-02-18  vismda      ESCAN00071630            AR4-499: SoAd (ASR 4.1.1) extensions
 *            2014-02-18  vismda      ESCAN00073774            SoAd fails to handle PduRoute with Tcp and Udp
 *                                                             PduRouteDest
 *            2014-02-20  vismda      ESCAN00073839            SoAd tries to release a not requested TcpIp buffer
 *            2014-02-20  vismda      ESCAN00073832            Compiler error: undeclared 'SoAd_VNPduUdpTxBuf_[...]
 *            2014-02-21  vismda      ESCAN00073872            Issue in SoAd local TcpIp buffer struct
 *            2014-02-28  vismda      ESCAN00073984            Missing return when DET is disabled
 *   4.01.02  2014-03-14  vismda      ESCAN00074073            Support timeout according to RfC 58627
 *            2014-03-14  vismda      ESCAN00074077            Include PduHeaderId in Best Match Algorithm
 *            2014-03-14  vismda      ESCAN00074079            No UDP socket connection open if PDU cannot be received
 *            2014-03-20  vismda      ESCAN00073911            SoAd stucks in infinite loop after receiving Pdu with
 *                                                             invalid PduHeaderId
 *            2014-03-20  vismda      ESCAN00074403            Re-opening of a socket connection fails and connection
 *                                                             is closed by the ECU unexpectedly
 *            2014-03-20  vismda      ESCAN00074223            No TCP socket connection reopen after TCP Reset
 *   4.01.03  2014-04-24  vismda      ESCAN00074584            SoCon closed even if another user still requires
 *            2014-04-25  vismda      ESCAN00074559            TCP Listen socket cannot be closed by upper layer
 *            2014-05-05  vismda      ESCAN00074602            Missing state update if TxConfirmation is called
 *                                                             directly after transmission request
 *            2014-05-05  vismda      ESCAN00075372            Exception on reception and no socket connection found
 *            2014-05-06  vismda      ESCAN00074661            "Retry enabled" causes Exception
 *            2014-05-06  vismda      ESCAN00074863            SoAd gets stuck in endless-loop after reception of an
 *                                                             segmented PDU with PduHdrOpt
 *   4.02.00  2014-05-22  vismda      ESCAN00070318            AR4-581: SoAd shall support streaming-based
 *                                                             TxConfirmation()
 *            2014-05-22  vismda      ESCAN00072078            DET error codes have to be adapted to AUTOSAR 4.1.X
 *            2014-05-22  vismda      ESCAN00074687            Exception in reception: TCP to IF-UL without PDU Header
 *            2014-05-22  vismda      ESCAN00074688            Reception of data with length = 0
 *            2014-05-22  vismda      ESCAN00075380            Endless loop when PDU header length exceeds uint16 range
 *            2014-05-22  vismda      ESCAN00075561            Wrong RxPdu Length Check
 *            2014-05-22  vismda      ESCAN00075785            Support IpAddrAssignment services
 *            2014-05-22  vismda      ESCAN00076203            Local define for STATIC
 *            2014-05-22  vismda      ESCAN00076246            TCP connection can not be closed during establishment
 *                                                             of the connection
 *   4.03.00  2014-05-22  vismda      ESCAN00071913            AR4-619: Support the StartOfReception API (with the
 *                                                             PduInfoType), TxConfirmation/RxIndication according
 *                                                             ASR4.1.2
 *            2014-05-22  vismda      ESCAN00074456            AR4-650: Support ChangeParameter without Confirmation
 *   4.05.00  2014-07-25  vismda      ESCAN00076559            SoAd_GetLocalAddr() returns always static configured
 *                                                             port
 *            2014-07-25  vismda      ESCAN00073870            LocalIpAddrAssignmentChg of upperlayer is not called
 *            2014-07-25  vismda      ESCAN00076929            Additional SoConModeChg callback user
 *            2014-07-25  vismda      ESCAN00076808            Support remote address "not set" value
 *            2014-07-25  vismda      ESCAN00077157            TCP client connection with auto setup cannot be opened
 *            2014-07-25  vismda      ESCAN00077245            Socket connection not closed if done by SoAd itself
 *   4.05.01  2014-08-08  vislje      ESCAN00077715            Compiler error: SoAd.c,  C2039: 'FuncPtrChg' : is not a
 *                                                             member of 'SoAd_SocketConnectionType'
 *   4.05.02  2014-08-21  vismda      ESCAN00077011            Connection closed after Alive Supervision Timeout when
 *                                                             only transmission running
 *            2014-08-21  vismda      ESCAN00077942            TCP socket connection open when port is any
 *            2014-08-22  vismda      ESCAN00078002            SoAd sends messages to IP and port 0
 *            2014-09-01  vismda      ESCAN00078019            Access violation in SoAd.c
 *   4.07.00  2014-09-12  vismda      ESCAN00077944            SoAd_GetLocalAddr is not compatible with missing
 *                                                             StaticIpAddressConfig
 *            2014-09-12  vismda      ESCAN00076963            Dynamic assignment of Local Port
 *            2014-09-12  vismda      ESCAN00078251            Reset Open/Close Sequence counter in error case
 *            2014-09-12  vismda      ESCAN00077943            Do not reset remote address when socket closed by remote
 *                                                             entity
 *            2014-10-02  vismda      ESCAN00078745            Socket connection is not closed after transmission
 *            2014-10-13  vismda      ESCAN00075593            Misunderstanding Trigger Transmit
 *            2014-10-21  vismda      ESCAN00079019            SoAd_Shutdown() issues
 *            2014-10-24  vismda      ESCAN00079095            Alignment exception on reception of PDU
 *            2014-10-24  vismda      ESCAN00079100            SoAd stucks in infinite loop after receiving Pdu with
 *                                                             length 0
 *   5.00.00  2014-10-02  vismda      ESCAN00073339            Extract DoIP from SoAd
 *            2014-10-02  vismda      ESCAN00075480            Missing checks for out parameter in TriggerTransmit
 *            2014-10-13  vismda      ESCAN00078914            Reset Open/Close counter in case IP address get lost
 *   6.00.00  2015-02-18  vismda      ESCAN00081568            Transmission to remote port 0 and remote IP
 *                                                             address 0.0.0.0
 *            2015-02-18  vismda      ESCAN00071864            FEAT-261: API between SoAd and TcpIp according to
 *                                                             AR 4.2.1
 *            2015-02-18  vismda      ESCAN00080067            FEAT-1001: Sd Enhanced Config for Asr4.2.1
 *            2015-02-18  vismda      ESCAN00081325            FEAT-1348: Support socket-specific frame priority and
 *                                                             TTL
 *            2015-03-10  vismda      ESCAN00081711            <User>_[SoAd][Tp]StartOfReception() is called even if no
 *                                                             SocketRoute is configured
 *            2015-03-19  vismda      ESCAN00079896            Implement constant pointer parameter according to
 *                                                             ASR4.2.1
 *   6.00.01  2015-04-21  vismda      ESCAN00082540            Receive cancellation doesn't close socket connection
 *                                                             immediately
 *            2015-04-21  vismda      ESCAN00082542            Transmit cancellation doesn't close socket connection
 *            2015-04-23  vismda      ESCAN00082601            TCP socket cannot be closed at TCP connection
 *                                                             establishment
 *            2015-05-06  vismda      ESCAN00082574            SoAd requires Tx and Rx path
 *   6.00.02  2015-05-12  vismda      ESCAN00082945            Missing critical section end in SoAd_TpTransmit
 *            2015-05-22  vismda      ESCAN00083121            Bad pointer error if TcpNoDelay parameter is used
 *   6.00.03  2015-06-12  vismda      ESCAN00083384            Unexpected PDU Header
 *   7.00.00  2015-06-15  vismda      ESCAN00082890            Socket connection close after transmission not performed
 *                                                             correctly
 *            2015-06-15  vismda      ESCAN00083314            Parameter SoAdSocketSoConModeChgNotification and
 *                                                             SoAdSocketIpAddrAssignmentChgNotification not considered
 *            2015-06-15  vismda      ESCAN00083346            Shutdown always performed after timeout
 *            2015-06-15  vismda      ESCAN00082641            FEAT-1249: Optimized UDP retry behavior e.g. in case of
 *                                                             ARP miss
 *            2015-06-16  vismda      ESCAN00082971            PduR TxConfirmation is called with invalid PduId
 *            2015-07-08  vismda      ESCAN00083869            No reception possible caused by inconsistent socket
 *                                                             connection state
 *            2015-07-08  vismda      ESCAN00082644            FEAT-1410: Support BSD Socket API
 *   7.00.01  2015-08-14  vismda      ESCAN00084550            MISRA/PClint warnings
 *   7.00.02  2015-08-28  vismda      ESCAN00084870            Issues on merging TCP Rx buffer
 *   8.00.00  2015-09-25  vispcn      ESCAN00085173            FEAT-1505: Postbuild Loadable for Socket Adaptor and
 *                                                             Service Discovery
 *            2015-11-09  vismda      ESCAN00085018            Issues on merging TCP Rx buffer (PDU header option)
 *            2015-11-09  vismda      ESCAN00085563            Socket connection always closed on fast open/close
 *                                                             sequence
 *            2015-11-09  vismda      ESCAN00082903            RoutingGroup state check missing in TP transmission and
 *                                                             reception
 *            2015-11-09  vismda      ESCAN00083007            DET API codes in IfRoutingGroupTransmit and GetLocalAddr
 *            2015-11-09  vismda      ESCAN00082840            <Ul>_[SoAd][Tp]RxIndication is not called after
 *                                                             CopyRxData returned E_NOT_OK
 *            2015-11-09  vismda      ESCAN00082836            <Ul>_[SoAd][Tp]RxIndication returns E_OK when TCP
 *                                                             connection with PduHdrOpt = FALSE is closed from remote
 *            2015-11-09  vismda      ESCAN00082815            SoAdSocketUdpStrictHeaderLenCheckEnabled is configurable
 *                                                             per SoConGroup but implemented globally
 *            2015-11-09  vismda      ESCAN00085602            SoAd_SetUniqueRemoteAddr() does not check port for
 *                                                             wildcard
 *            2015-11-09  vismda      ESCAN00085615            Adaptations due to code review
 *            2015-11-09  vismda      ESCAN00085744            Remove obsolete header file SoAd_EthSM.h
 *            2015-11-09  vismda      ESCAN00085801            TcpTxQueue does not consider PDU Header
 *            2015-11-09  vismda      ESCAN00086200            Compiler error if no PduRoute exists
 *            2015-11-23  vismda      ESCAN00085171            FEAT-10: Implementation of DoIP according to AR 4.2.1
 *                                                             [AR4-507]
 *            2015-12-11  vismda      ESCAN00087129            TP receive cancellation on TCP socket does not reset rx
 *                                                             buffer
 *   8.01.00  2016-01-20  vismda      ESCAN00087593            Remote address cannot be set if no SocketRoute is
 *                                                             configured
 *            2016-01-21  vismda      ESCAN00087606            SoAd_TcpAccepted/Connected not available in case TCP is
 *                                                             disabled
 *            2016-02-25  vismda      ESCAN00087837            FEAT-1631: Trigger Transmit API with SduLength In/Out
 *                                                             according to ASR4.2.2
 *            2016-02-26  vismda      ESCAN00088592            Unexpected TxConfirmation if disabled on PduR route
 *            2016-02-27  vismda      ESCAN00087654            FEAT-1347: TLS as TcpIp plug-in
 *            2016-03-15  vismda      ESCAN00088924            TCP Rx buffer handling issue in case of PDU header
 *                                                             option
 *            2016-03-22  vismda      ESCAN00089027            Consider "abort" independent of open/close counter in
 *                                                             SoAd_CloseSoCon()
 *            2016-03-29  vismda      ESCAN00089103            UDP socket connection in reconnect state after close
 *                                                             request
 *   8.01.01  2016-04-05  vismda      ESCAN00089200            <Up>_[SoAd][Tp|If]TxConfirmation() is called in next
 *                                                             MainFunction instead of in SoAd_TxConfirmation()
 *            2016-04-18  vismda      ESCAN00088992            <User>_ShutdownFinished() called after timeout only
 *            2016-04-18  vismda      ESCAN00089370            FEAT-1760: Bugfixing of SoAd and TcpIp
 *   8.01.02  2016-04-19  vismda      ESCAN00089597            Shutdown not performed if TCP connection is half-closed
 *   8.01.03  2016-04-20  vismda      ESCAN00089631            Compiler error: undefined reference to 'TcpIp_Close'
 *   8.02.00  2016-04-25  vismda      ESCAN00089727            Only a few TCP transmissions possible
 *            2016-04-28  vismda      ESCAN00089361            FEAT-1910: Release of BSD-Socket API
 *            2016-04-28  vismda      ESCAN00088996            No reception of IP broadcast packets
 *   8.02.01  2016-05-02  vismda      ESCAN00089847            Reception of IPv4 broadcasts sent by ECU itself
 *            2016-05-02  vismda      ESCAN00089809            No reception nor TCP connection establishment possible
 *                                                             for IPv6
 *   8.02.02  2016-05-19  vismda      ESCAN00090046            Main function runtime improvement
 *   8.03.00  2016-05-31  vismda      ESCAN00089153            SoAd_Set[Unique]RemoteAddr() shall consider local
 *                                                             address
 *            2016-06-01  vismda      ESCAN00089845            IPv6 TCP server socket blocks
 *            2016-06-09  vismda      ESCAN00090402            Nested critical section leads to OS errors or data
 *                                                             inconsistency
 *            2016-06-09  vismda      ESCAN00089359            FEAT-1413: Extension of BSD Socket API to support
 *                                                             SOME/IP-SD under Linux
 *            2016-06-09  vismda      ESCAN00089844            No reception of IPv6 multicast packets
 *            2016-06-14  vismda      ESCAN00090461            Transmission over multiple SoAdPduRouteDests causes
 *                                                             invalid memory access
 *            2016-06-24  vismda      ESCAN00089738            Set limitation of UDP Tx retry queue elements per socket
 *            2016-06-24  vismda      ESCAN00089372            FEAT-1845: Prozessmigration: ETH Stack
 *            2016-07-12  vismda      ESCAN00090957            Call to SoAd_Enable/DisableSpecificRouting with invalid
 *                                                             SoConId enables/disables routing group
 *   8.03.01  2016-07-25  vispcn      ESCAN00091139            Incorrect PDU header in case of TCP transmission
 *   8.03.02  2016-08-10  vismda      ESCAN00091397            Header file 'linux/if_packet.h' not available in some
 *                                                             distributions
 *            2016-08-10  vismda      ESCAN00091402            Compiler error "expected '}' before 'else'"
 *   9.00.00  2016-09-26  vismda      FEATC-265                FEAT-972: SoAd shall implement an optimized buffer
 *                                                             handling for PDU fan-out on multiple socket connections
 *            2016-10-28  vismda      FEATC-257                FEAT-1816: Split MainFunctions to optimize gateway
 *                                                             use-case
 *            2016-10-28  vismda      ESCAN00092630            SoAd_IfTransmit function has high run time duration
 *            2016-11-16  vismda      ESCAN00092819            Socket connection open on reception with "not set"
 *                                                             remote address
 *            2016-11-17  vismda      ESCAN00092872            DET error SOAD_E_INV_PDUHEADER_ID on reception of
 *                                                             multiple PDUs on TCP
 *            2016-11-21  vismda      ESCAN00092900            SoAd_CloseSoCon() closes TcpIp UDP socket directly
 *   9.00.01  2016-11-29  vismda      ESCAN00093057            Set remote address to wildcard does not set socket
 *                                                             connection to SOAD_SOCON_RECONNECT
 *   9.01.00  2017-01-13  vismda      FEATC-886                FEAT-2385: Use Event Queues for SoAd MainFunction
 *                                                             handling
 *            2017-01-13  vismda      ESCAN00093482            Socket connection close/open sequence is not consistent
 *                                                             if "abort"-flag is set
 *   9.02.00  2017-02-02  vismda      FEATC-1142               FEAT-2778: Support Buffer Size up to 128kB for FBL
 *                                                             use case
 *            2017-02-23  vismda      ESCAN00094153            No transmission possible after transmission over TCP
 *                                                             socket fails
 *            2017-02-24  vismda      ESCAN00094165            SoAd_Init() call does not return
 *            2017-03-01  vismda      ESCAN00094207            TCP socket connections cannot be opened
 *            2017-03-20  vismda      ESCAN00094423            IP address assignment request fails unexpectedly
 *   10.00.00 2017-04-20  vismda      STORYC-370               P3 CAD
 *            2017-05-02  vismda      ESCAN00094976            Overwrite memory in case of nPduQueue and nPduBuffer
 *   10.01.00 2017-05-23  vismda      STORYC-371               P3 Implementation API Pattern
 *   10.01.01 2017-06-12  vismda      ESCAN00095510            Memory overwrite if IPv6 is disabled
 *   10.02.00 2017-06-21  vismda      STORYC-1202              SoAd: Callout for Diagnostic Firewall Use Case
 *            2017-06-22  vismda      STORYC-303               SoAd: Support optimized PDU handling for C/S calls
 *   10.03.00 2017-07-12  vismda      ESCAN00095848            No further transmission is possible
 *            2017-07-27  vismda      STORYC-372               P3 Code Refactoring / CDD Step 1
 *   10.04.00 2017-08-28  vismda      STORYC-1795              P3 Code Refactoring / CDD Step 2
 *   10.04.01 2017-09-29  vismda      ESCAN00096868            Unexpected DET error for routing group
 *            2017-09-29  vismda      ESCAN00096813            No reception on directed broadcast/link-local multicast
 *                                                             IP address
 *   11.00.00 2017-09-11  vismda      STORYC-2098              P3 Code Refactoring / CDD Step 3
 *            2017-11-22  vismda      STORYC-377               SAFE Code Refactoring
 *            2017-02-27  vismda      STORYC-4097              Support QNX
 *            2018-03-16  vismda      ESCAN00097145            TCP connection reconnect after socket connection close
 *            2018-03-16  vismda      ESCAN00097717            Compiler errors for declaration after executable
 *                                                             statement
 *            2018-03-16  vismda      ESCAN00097567            Missing TxConfirmation for IF-PDU after TCP socket
 *                                                             connection close
 *            2018-03-16  vismda      ESCAN00098100            Compiler error: undefined reference to
 *                                                             "SoAd_TcpIpBsd_RequestSocketTxBuffer"
 *            2018-03-16  vismda      ESCAN00098123            Transmission of invalid PDU header length
 *            2018-03-16  vismda      ESCAN00097396            Multicast UDP packets sent over wrong local address
 *            2018-03-16  vismda      ESCAN00098913            DET on reception on reestablished TCP socket connection
 *            2018-03-16  vismda      ESCAN00099674            Reception of unexpected data after rejection by PDU
 *                                                             verification
 *            2018-03-16  vismda      ESCAN00100404            A new interrupt lock may not be activated
 *   11.00.01 2018-04-12  vismda      ESCAN00099080            Runtime error: Infinite loop detected 'InitTask'
 *            2018-04-12  vismda      ESCAN00099083            Runtime error: Infinite loop detected when using nPdu
 *   11.00.02 2018-04-17  vismda      ESCAN00098610            Local IP address change is not detected
 *   12.00.00 2018-07-23  vismda      ESCAN00100135            Compiler warning: "ErrorIdPtr" unreferenced formal
 *                                                             parameter
 *            2018-07-26  vissem      STORYC-5228              SoAd Option BSD: Support Integrity
 *            2018-07-26  vismda      ESCAN00100303            <Up>_SoAdTpTxConfirmation is called before transmission
 *                                                             is finished
 *   12.00.01 2018-08-09  vissem      ESCAN00100208            BETA version - the BSW module has a feature with BETA
 *                                                             state (FEAT-2971 - only TCP connections)
 *   12.01.00 2018-08-21  vismda      STORYC-6033              [ETH] Support different VLAN priorities defined by the
 *                                                             data definition in SoAD with BSD option for Linux SoAd
 *   12.01.01 2018-09-27  vismda      ESCAN00100730            Memory corruption on reception of IF-PDU over TCP
 *            2018-09-27  vismda      ESCAN00100887            Unexpected number of TCP keep alive probes
 *   12.01.02 2018-11-16  vismda      ESCAN00101094            Null pointer exception on transmission of nPdu
 *            2018-11-16  vismda      ESCAN00101258            Infinite loop on reception of TP-PDU over TCP with PDU
 *                                                             header option
 *            2018-11-16  vismda      ESCAN00101234            Unexpected routing group transmission
 *            2018-11-16  vismda      ESCAN00100714            Socket connection is not handled properly if Abort-flag
 *                                                             is set to TRUE.
 *   12.01.03 2018-12-11  vismda      ESCAN00101430            Null pointer exception on reception of IF-PDU
 *            2018-12-13  vismda      ESCAN00101609            NPdu is sent with unexpected larger length
 *   13.00.00 2018-12-13  vismda      STORYC-6410              Review integration Silent Analysis
 *            2018-12-13  vismda      STORYC-6485              MISRA-C:2012: If_AsrIfSoAd
 *            2019-02-12  vismda      ESCAN00102097            Compiler warning: if statement does not affect control
 *                                                             flow
 *            2019-03-11  vismda      ESCAN00102432            Reception of valid IF-PDU over TCP is rejected
 *   14.00.00 2019-03-19  vismda      STORY-11153              Forward of TcpIp_DhcpRead/WriteOption APIs to
 *                                                             upper-layer
 *            2019-04-24  vismda      ESCAN00102953            IF TxConfirmation is called with locked interrupts
 *   14.01.00 2019-05-21  vismda      ESCAN00103203            Missing detection of unassigned local IP address
 *   14.01.01 2019-07-24  vismda      ESCAN00103810            No support for more than 255 parallel socket connection
 *                                                             open requests
 *   15.00.00 2019-08-16  vistia      TCPIP-833                Support SoAd_GetAndResetMeasurementData()
 *            2019-08-29  vismda      ESCAN00104175            Incoming TCP connection not detected
 *   15.00.01 2019-09-10  vismda      ESCAN00098754            Transmission via TriggerTransmit with IP fragmentation
 *                                                             fails
 *            2019-09-10  vismda      ESCAN00104251            Unexpected PDU data on IF-PDU transmission with IP
 *                                                             fragmentation
 *            2019-09-26  vismda      ESCAN00104453            Full TCP window on reception with disabled routing group
 *   15.00.02 2019-11-20  vismda      ESCAN00104948            No TCP connection can be established
 *            2019-11-20  vismda      ESCAN00104950            Access violation error on UDP reception
 *   15.00.03 2020-01-14  vismda      ESCAN00104957            Compiler warning: SoAd_Measure_Dropped* was declared but
 *                                                             never referenced
 *            2020-01-31  vismda      ESCAN00105321            TCP transmission in wrong order
 *   16.00.00 2020-02-10  visjsb      SAA-479                  Support critical sections for reentrant transmission
 *                                                             paths
 *            2020-02-27  vismda      SAA-302                  Support for AR RfC 92400: SOME/IP multi instance support
 *                                                             on client side using the same socket
 *   16.01.00 2020-05-08  visjsb      SAA-615                  Optimize runtime to find the reception path dependent on
 *                                                             PDU header
 *            2020-05-11  vismda      ESCAN00106126            Closing socket with invalid handle
 *            2020-05-11  vismda      ESCAN00106044            No unicast and multicast reception on the same port
 *            2020-05-19  vismda      ESCAN00106400            Unexpected socket connection close by alive supervision
 *                                                             timeout
 *            2020-05-29  vismda      SAA-640                  Optimized IF transmission
 *   16.02.00 2020-06-10  vismda      SAA-735                  SoAd PDU-Fanout for SomeIp-TP
 *   16.03.00 2020-07-14  vismda      SAA-798                  Finalize SoAd PDU-Fanout for SomeIp-TP
 *            2020-07-16  vismda      ESCAN00106870            No PDU transmission for routing group transmit
 *            2020-07-16  visjsb      SAA-684                  Support meta data for TriggerTransmit
 *            2020-07-22  vismda      ESCAN00106920            Shutdown leads to an endless loop
 *   16.04.00 2020-09-08  vismda      ESCAN00107301            Retrieved received remote address does not match
 *            2020-09-08  vismda      ESCAN00107293            UDP frame is dropped unexpectedly or received on an
 *                                                             unexpected socket connection
 *            2020-09-08  vismda      SAA-1087                 Increase robustness of SoAd_EnableSpecificRouting
 *            2020-09-08  vismda      SAA-1078                 Retrieve IP fragmentation buffer index in a critical
 *                                                             section
 *            2020-09-08  jelsaesser  SAA-716                  Make reception of broadcasts in SoAd configurable
 *   16.05.00 2021-01-04  jelsaesser  SAA-824                  Keep socket connection online after transmission on
 *                                                             automatic socket connection setup
 *   16.05.01 2021-02-16  vismda      ESCAN00107303            Not all routing group related PDUs are transmitted
 *                                    ESCAN00107306            Communication issues after socket event
 *********************************************************************************************************************/

#if !defined(SOAD_H)
# define SOAD_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "SoAd_Lcfg.h"
# include "SoAd_PBcfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Vendor and module identification */
# define SOAD_VENDOR_ID                                   (30u)
# define SOAD_MODULE_ID                                   (0x38u)

/* AUTOSAR Software specification version information */
# define SOAD_AR_RELEASE_MAJOR_VERSION                    (4u)
# define SOAD_AR_RELEASE_MINOR_VERSION                    (2u)
# define SOAD_AR_RELEASE_PATCH_VERSION                    (2u)

/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define SOAD_SW_MAJOR_VERSION                            (16u)
# define SOAD_SW_MINOR_VERSION                            (5u)
# define SOAD_SW_PATCH_VERSION                            (1u)

# define SOAD_INSTANCE_ID_DET                             (0x00u)

/* ----- API service IDs ----- */
# define SOAD_SID_INIT                                    (0x01u)
# define SOAD_SID_GET_VERSION_INFO                        (0x02u)
# define SOAD_SID_IF_TRANSMIT                             (0x03u)
# define SOAD_SID_TP_TRANSMIT                             (0x04u)
# define SOAD_SID_TP_CANCEL_TRANSMIT                      (0x05u)
# define SOAD_SID_TP_CANCEL_RECEIVE                       (0x06u)
# define SOAD_SID_GET_SO_CON_ID                           (0x07u)
# define SOAD_SID_OPEN_SO_CON                             (0x08u)
# define SOAD_SID_CLOSE_SO_CON                            (0x09u)
# define SOAD_SID_REQ_IP_ADDR_ASSIGN                      (0x0Au)
# define SOAD_SID_RLS_IP_ADDR_ASSIGN                      (0x0Bu)
# define SOAD_SID_GET_LOCAL_ADDR                          (0x0Cu)
# define SOAD_SID_GET_PHYS_ADDR                           (0x0Du)
# define SOAD_SID_ENABLE_ROUTING                          (0x0Eu)
# define SOAD_SID_DISABLE_ROUTING                         (0x0Fu)
# define SOAD_SID_SET_REMOTE_ADDR                         (0x10u)
# define SOAD_SID_TP_CHANGE_PARAMETER                     (0x11u)
# define SOAD_SID_RX_INDICATION                           (0x12u)
# define SOAD_SID_COPY_TX_DATA                            (0x13u)
# define SOAD_SID_TX_CONFIRMATION                         (0x14u)
# define SOAD_SID_TCP_ACCEPTED                            (0x15u)
# define SOAD_SID_TCP_CONNECTED                           (0x16u)
# define SOAD_SID_TCPIP_EVENT                             (0x17u)
# define SOAD_SID_LOCAL_IP_ADDR_ASSIGNMENT_CHG            (0x18u)
# define SOAD_SID_MAIN_FUNCTION                           (0x19u)
# define SOAD_SID_READ_DHCP_HOST_NAME_OPT                 (0x1Au)
# define SOAD_SID_WRITE_DHCP_HOST_NAME_OPT                (0x1Bu)
# define SOAD_SID_GET_REMOTE_ADDR                         (0x1Cu)
# define SOAD_SID_IF_ROUT_GROUP_TRANSMIT                  (0x1Du)
# define SOAD_SID_SET_UNI_REMOTE_ADDR                     (0x1Eu)
# define SOAD_SID_IF_SPEC_ROUT_GROUP_TRANSMIT             (0x1Fu)
# define SOAD_SID_ENABLE_SPECIFIC_ROUTING                 (0x20u)
# define SOAD_SID_DISABLE_SPECIFIC_ROUTING                (0x21u)
# define SOAD_SID_GET_RESET_MEASURE_DATA                  (0x45u)

/* ----- API service IDs Vector ----- */
# define SOAD_SID_MAIN_FUNCTION_RX                        (0xD0u)
# define SOAD_SID_MAIN_FUNCTION_STATE                     (0xD1u)
# define SOAD_SID_MAIN_FUNCTION_TX                        (0xD2u)
# define SOAD_SID_SHUTDOWN                                (0xD3u)
# define SOAD_SID_GET_RCV_REMOTE_ADDR                     (0xD4u)
# define SOAD_SID_GET_REMOTE_ADDR_STATE                   (0xD5u)
# define SOAD_SID_READ_DHCP_OPT                           (0xD6u)
# define SOAD_SID_WRITE_DHCP_OPT                          (0xD7u)
# define SOAD_SID_DHCP_EVENT                              (0xD8u)

/* ----- Error codes ----- */
# define SOAD_E_NO_ERROR                                  (0x00u)
# define SOAD_E_NOTINIT                                   (0x01u)
# define SOAD_E_PARAM_POINTER                             (0x02u)
# define SOAD_E_INV_ARG                                   (0x03u)
# define SOAD_E_NOBUFS                                    (0x04u)
# define SOAD_E_INV_PDUHEADER_ID                          (0x05u)
# define SOAD_E_INV_PDUID                                 (0x06u)
# define SOAD_E_INV_SOCKETID                              (0x07u)
# define SOAD_E_INIT_FAILED                               (0x08u)

/* ----- Module specific return values ----- */
# define SOAD_E_INPROGRESS                                (0x02u)

/* ----- Socket API service IDs ----- */
# define SOAD_SOCK_SID_TCPIP_READ_DHCP_HOST_NAME_OPTION   (0x00u)
# define SOAD_SOCK_SID_TCPIP_WRITE_DHCP_HOST_NAME_OPTION  (0x01u)
# define SOAD_SOCK_SID_TCPIP_BSD_TCP_CHECK_CONNECT        (0x02u)
# define SOAD_SOCK_SID_TCPIP_BSD_TCP_CHECK_ACCEPT         (0x03u)
# define SOAD_SOCK_SID_TCPIP_BSD_GET_SOCKET               (0x04u)
# define SOAD_SOCK_SID_TCPIP_BSD_BIND_SINGLE_SOCKET       (0x05u)
# define SOAD_SOCK_SID_TCPIP_TCP_LISTEN                   (0x06u)
# define SOAD_SOCK_SID_TCPIP_TCP_CONNECT                  (0x07u)
# define SOAD_SOCK_SID_TCPIP_CLOSE                        (0x08u)
# define SOAD_SOCK_SID_TCPIP_UDP_TRANSMIT                 (0x09u)
# define SOAD_SOCK_SID_TCPIP_BSD_CHANGE_PARAMETER         (0x0Au)
# define SOAD_SOCK_SID_TCPIP_CHANGE_PARAMETER             (0x0Bu)
# define SOAD_SOCK_SID_TCPIP_QNX_GET_PHYS_ADDR            (0x0Cu)
# define SOAD_SOCK_SID_TCPIP_QNX_JOIN_MCAST_GRP_V4        (0x0Du)
# define SOAD_SOCK_SID_TCPIP_BSD_BIND_SINGLE_SOCK_TO_IFC  (0x0Eu)
# define SOAD_SOCK_SID_TCPIP_INTEGRITY_GET_IF_ADDR        (0x0Fu)
# define SOAD_SOCK_SID_TCPIP_INTEGRITY_GET_SOCKET_FROM_OS (0x10u)
# define SOAD_SOCK_SID_TCPIP_INTEGRITY_BIND_SOCKET        (0x11u)
# define SOAD_SOCK_SID_TCPIP_INTEGRITY_GET_PORT_OF_SOCKET (0x12u)
# define SOAD_SOCK_SID_TCPIP_INTEGRITY_UPDATE_MULTICAST   (0x13u)
# define SOAD_SOCK_SID_TCPIP_INTEGRITY_GET_PHYS_ADDR      (0x14u)
# define SOAD_SOCK_SID_TCPIP_INTEGRITY_IS_LOC_ADDR_AVAIL  (0x15u)
# define SOAD_SOCK_SID_TCPIP_INTEGRITY_RECEIVE            (0x16u)
# define SOAD_SOCK_SID_TCPIP_INTEGRITY_EN_V6_BROADCAST    (0x17u)
# define SOAD_SOCK_SID_TCPIP_CHECK_AND_OVERWRITE_LOC_ADDR (0x18u)

/* ----- Socket BSD API service IDs ----- */
# define SOAD_SOCK_BSD_API_GET_HOST_NAME                  (0x00u)
# define SOAD_SOCK_BSD_API_SET_HOST_NAME                  (0x01u)
# define SOAD_SOCK_BSD_API_CONNECT                        (0x02u)
# define SOAD_SOCK_BSD_API_ACCEPT                         (0x03u)
# define SOAD_SOCK_BSD_API_SOCKET                         (0x04u)
# define SOAD_SOCK_BSD_API_BIND                           (0x05u)
# define SOAD_SOCK_BSD_API_LISTEN                         (0x06u)
# define SOAD_SOCK_BSD_API_CLOSE                          (0x07u)
# define SOAD_SOCK_BSD_API_SEND_TO                        (0x08u)
# define SOAD_SOCK_BSD_API_FCNTL                          (0x09u)
# define SOAD_SOCK_BSD_API_SET_SOCK_OPT                   (0x0Au)
# define SOAD_SOCK_BSD_API_GET_SOCK_NAME                  (0x0Bu)
# define SOAD_SOCK_BSD_API_GET_IF_ADDR                    (0x0Cu)
# define SOAD_SOCK_BSD_API_SELECT                         (0x0Du)
# define SOAD_SOCK_BSD_API_GET_SOCK_OPT                   (0x0Eu)
# define SOAD_SOCK_BSD_API_IOCTL                          (0x0Fu)
# define SOAD_SOCK_BSD_API_RECV_MSG                       (0x10u)

/* ----- Socket BSD API parameter IDs ----- */
# define SOAD_SOCK_BSD_PARAM_IP6ONLY                      (0x00u)
# define SOAD_SOCK_BSD_PARAM_REUSEADDR                    (0x01u)
# define SOAD_SOCK_BSD_PARAM_BROADCAST                    (0x02u)
# define SOAD_SOCK_BSD_PARAM_LINGER                       (0x03u)
# define SOAD_SOCK_BSD_PARAM_RCVBUF                       (0x04u)
# define SOAD_SOCK_BSD_PARAM_SNDBUF                       (0x05u)
# define SOAD_SOCK_BSD_PARAM_NODELAY                      (0x06u)
# define SOAD_SOCK_BSD_PARAM_SO_KEEPALIVE                 (0x07u)
# define SOAD_SOCK_BSD_PARAM_TCP_KEEPALIVE                (0x08u)
# define SOAD_SOCK_BSD_PARAM_TCP_KEEPALIVE_CNT            (0x09u)
# define SOAD_SOCK_BSD_PARAM_TCP_KEEPALIVE_INTV           (0x0Au)
# define SOAD_SOCK_BSD_PARAM_F_GETFL                      (0x10u)
# define SOAD_SOCK_BSD_PARAM_F_SETFL                      (0x11u)
# define SOAD_SOCK_BSD_PARAM_IPV6_JOIN_GROUP              (0x12u)
# define SOAD_SOCK_BSD_PARAM_IP_ADD_MEMBERSHIP            (0x13u)
# define SOAD_SOCK_BSD_PARAM_SO_BIND_TO_DEVICE            (0x14u)
# define SOAD_SOCK_BSD_PARAM_IP_RECVDSTADDR               (0x15u)
# define SOAD_SOCK_BSD_PARAM_SO_ERROR                     (0x16u)
# define SOAD_SOCK_BSD_PARAM_FD_SET                       (0x17u)
# define SOAD_SOCK_BSD_PARAM_IPV6_RECVPKTINFO             (0x18u)
# define SOAD_SOCK_BSD_PARAM_PRIORITY                     (0x19u)
# define SOAD_SOCK_BSD_PARAM_SIOCSIFVLAN                  (0x1Au)
# define SOAD_SOCK_BSD_PARAM_NONE                         (0xFFu)

/* ----- Socket BSD API parameter values ----- */
# define SOAD_SOCK_BSD_VALUE_NONE                         (-1)

/* ----- Modes ----- */
# define SOAD_STATE_UNINIT                                (0x00u)
# define SOAD_STATE_INIT                                  (0x01u)
# define SOAD_STATE_SHUTDOWN_IN_PROGRESSS                 (0x03u)
# define SOAD_STATE_SHUTDOWN                              (0x04u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

# define SOAD_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

extern P2CONST(SoAd_ConfigType, AUTOMATIC, SOAD_PBCFG) SoAd_ConfigDataPtr;

# define SOAD_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define SOAD_START_SEC_CODE
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/**********************************************************************************************************************
 *  SoAd_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Initializes *_INIT_*-variables.
 *  \details     Service to initialize module global variables at power up. This function initializes the
 *               variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \pre         Module is uninitialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_InitMemory(void);

/**********************************************************************************************************************
 *  SoAd_Init()
 *********************************************************************************************************************/
/*! \brief       Initializes module
 *  \details     This function initializes the module SoAd. It initializes all variables and sets the module state to
 *               initialized.
 *  \param[in]   SoAdConfigPtr            Configuration structure for initializing the module.
 *  \pre         Interrupts are disabled.
 *  \pre         SoAd_InitMemory has been called unless SoAd_ModuleInitialized is initialized by start-up code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Init(
  P2CONST(SoAd_ConfigType, AUTOMATIC, SOAD_CONST) SoAdConfigPtr);

/**********************************************************************************************************************
 *  SoAd_IfTransmit()
 *********************************************************************************************************************/
/*! \brief       Transmits an IF-PDU.
 *  \details     -
 *  \param[in]   SoAdSrcPduId       Tx PDU identifier.
 *  \param[in]   SoAdSrcPduInfoPtr  Pointer to PDU.
 *  \return      E_OK               Transmit request was accepted.
 *  \return      E_NOT_OK           Transmit request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different PDUs, FALSE for same PDU.
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_IfTransmit(
  PduIdType SoAdSrcPduId,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) SoAdSrcPduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_IfRoutingGroupTransmit()
 *********************************************************************************************************************/
/*! \brief       Triggers transmission of all IF-PDUs related to a routing group.
 *  \details     Triggers transmission via trigger transmit in main function context.
 *  \param[in]   id             Routing group identifier.
 *  \return      E_OK           Transmit request was accepted.
 *  \return      E_NOT_OK       Transmit request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_IfRoutingGroupTransmit(
  SoAd_RoutingGroupIdType id);

/**********************************************************************************************************************
 *  SoAd_IfSpecificRoutingGroupTransmit()
 *********************************************************************************************************************/
/*! \brief       Triggers transmission of all IF-PDUs related to a routing group and socket connection.
 *  \details     Triggers transmission via trigger transmit in main function context.
 *  \param[in]   id             Routing group identifier.
 *  \param[in]   SoConId        Socket connection identifier.
 *  \return      E_OK           Transmit request was accepted.
 *  \return      E_NOT_OK       Transmit request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_IfSpecificRoutingGroupTransmit(
  SoAd_RoutingGroupIdType id,
  SoAd_SoConIdType SoConId);

/**********************************************************************************************************************
 *  SoAd_TpTransmit()
 *********************************************************************************************************************/
/*! \brief       Transmits a TP-PDU.
 *  \details     -
 *  \param[in]   SoAdSrcPduId       Tx PDU identifier.
 *  \param[in]   SoAdSrcPduInfoPtr  Pointer to PDU (length is evaluated only).
 *  \return      E_OK               Transmit request was accepted.
 *  \return      E_NOT_OK           Transmit request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different PDUs, FALSE for same PDU
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TpTransmit(
  PduIdType SoAdSrcPduId,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) SoAdSrcPduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_Shutdown()
 *********************************************************************************************************************/
/*! \brief       Shuts down SoAd module.
 *  \details     Closes all open socket connections and disables transmission and reception.
 *  \return      E_OK               Shutdown request was accepted.
 *  \return      SOAD_E_INPROGRESS  Shutdown is in progress.
 *  \return      E_NOT_OK           Shutdown request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Shutdown(void);

/**********************************************************************************************************************
 *  SoAd_TpCancelTransmit()
 *********************************************************************************************************************/
/*! \brief       Requests transmission cancellation of a specific TP-PDU.
 *  \details     -
 *  \param[in]   PduId        Tx PDU identifier.
 *  \return      E_OK         Transmit cancellation request was accepted.
 *  \return      E_NOT_OK     Transmit cancellation request was not accepted.
 *  \pre         Transmission of PDU is requested via SoAd_TpTransmit.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TpCancelTransmit(
  PduIdType PduId);

/**********************************************************************************************************************
 *  SoAd_TpCancelReceive()
 *********************************************************************************************************************/
/*! \brief       Requests reception cancellation of a specific TP-PDU.
 *  \details     -
 *  \param[in]   PduId        Rx PDU identifier.
 *  \return      E_OK         Receive cancellation request was accepted.
 *  \return      E_NOT_OK     Receive cancellation request was not accepted.
 *  \pre         Reception of PDU is initiated via <Up>_[SoAd][Tp]StartOfReception.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TpCancelReceive(
  PduIdType PduId);

/**********************************************************************************************************************
 *  SoAd_GetSoConId()
 *********************************************************************************************************************/
/*! \brief       Returns the socket connection identifier of a specific Tx PDU identifier.
 *  \details     -
 *  \param[in]   TxPduId      Tx PDU identifier.
 *  \param[out]  SoConIdPtr   Pointer to the socket connection identifier.
 *  \return      E_OK         Socket connection identifier was found.
 *  \return      E_NOT_OK     Socket connection identifier was not found.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetSoConId(
  PduIdType TxPduId,
  P2VAR(SoAd_SoConIdType, AUTOMATIC, SOAD_APPL_VAR) SoConIdPtr);

/**********************************************************************************************************************
 *  SoAd_OpenSoCon()
 *********************************************************************************************************************/
/*! \brief       Opens a socket connection.
 *  \details     Opens the socket connection in context of main function.
 *  \param[in]   SoConId      Socket connection identifier.
 *  \return      E_OK         Open request was accepted.
 *  \return      E_NOT_OK     Open request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_OpenSoCon(
  SoAd_SoConIdType SoConId);

/**********************************************************************************************************************
 *  SoAd_CloseSoCon()
 *********************************************************************************************************************/
/*! \brief       Closes a socket connection.
 *  \details     Closes the socket connection in context of main function.
 *  \param[in]   SoConId      Socket connection identifier.
 *  \param[in]   Abort        Flag to close socket connection immediately.
 *                            [range: TRUE close immediately, FALSE close when open close sequence is 0]
 *  \return      E_OK         Close request was accepted.
 *  \return      E_NOT_OK     Close request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_CloseSoCon(
  SoAd_SoConIdType SoConId,
  boolean Abort);

/**********************************************************************************************************************
 *  SoAd_RequestIpAddrAssignment()
 *********************************************************************************************************************/
/*! \brief       Requests IP address assignment on a local address identified by a socket connection.
 *  \details     -
 *  \param[in]   SoConId          Socket connection identifier.
 *  \param[in]   Type             IP address type.
 *                                [range in case of SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR:
 *                                SOAD_IPADDR_ASSIGNMENT_STATIC .. SOAD_IPADDR_ASSIGNMENT_IPV6_ROUTER]
 *  \param[in]   LocalIpAddrPtr   Pointer to IP address which shall be assigned.
 *                                [Points to one of the following structs depending on value of struct element domain:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \param[in]   Netmask          Netmask in CIDR.
 *  \param[in]   DefaultRouterPtr Pointer to default router (gateway) address.
 *                                [Type == SOAD_IPADDR_ASSIGNMENT_STATIC:
 *                                  ->  DefaultRouterPtr != NULL_PTR
 *                                      Points to one of the following structs depending on configured IP address
 *                                      version of parameter SoConIdx:
 *                                        - SoAd_SockAddrInetType for IPv4
 *                                        - SoAd_SockAddrInet6Type for IPv6
 *                                Type != SOAD_IPADDR_ASSIGNMENT_STATIC:
 *                                  ->  DefaultRouterPtr == NULL_PTR]
 *  \return      E_OK             Assignment request was accepted.
 *  \return      E_NOT_OK         Assignment request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different local IP addresses, FALSE for same local IP address.
 *  \synchronous TRUE in case of TcpIp-API, FALSE in case of BSD-API.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_RequestIpAddrAssignment(
  SoAd_SoConIdType SoConId,
  SoAd_IpAddrAssignmentType Type,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalIpAddrPtr,
  uint8 Netmask,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr);

/**********************************************************************************************************************
 *  SoAd_ReleaseIpAddrAssignment()
 *********************************************************************************************************************/
/*! \brief       Releases IP address assignment on a local address identified by a socket connection.
 *  \details     -
 *  \param[in]   SoConId          Socket connection identifier.
 *  \return      E_OK             Release request was accepted.
 *  \return      E_NOT_OK         Release request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different local IP addresses, FALSE for same local IP address.
 *  \synchronous TRUE in case of TcpIp-API, FALSE in case of BSD-API
 *  \trace       CREQ-138021
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_ReleaseIpAddrAssignment(
  SoAd_SoConIdType SoConId);

/**********************************************************************************************************************
 *  SoAd_GetLocalAddr()
 *********************************************************************************************************************/
/*! \brief       Returns a local IP address identified by a socket connection.
 *  \details     -
 *  \param[in]   SoConId          Socket connection identifier.
 *  \param[out]  LocalAddrPtr     Pointer to local address (IP and Port).
 *                                [Points to one of the following structs depending on value of struct element domain:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \param[out]  NetmaskPtr       Pointer to network mask (CIDR Notation).
 *  \param[out]  DefaultRouterPtr Pointer to default router (gateway).
 *                                [Points to one of the following structs depending on configured IP address
 *                                version of parameter SoConId:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \return      E_OK             Request was accepted.
 *  \return      E_NOT_OK         Request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-123308
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetLocalAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalAddrPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) NetmaskPtr,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr);

/**********************************************************************************************************************
 *  SoAd_GetPhysAddr()
 *********************************************************************************************************************/
/*! \brief       Returns the physical address (MAC address) of a local interface identified by a socket connection.
 *  \details     -
 *  \param[in]   SoConId          Socket connection identifier.
 *  \param[out]  PhysAddrPtr      Pointer to physical address.
 *                                [Points to a uint8 array of length 6]
 *  \return      E_OK             Request was accepted.
 *  \return      E_NOT_OK         Request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetPhysAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) PhysAddrPtr);

/**********************************************************************************************************************
 *  SoAd_GetRemoteAddr()
 *********************************************************************************************************************/
/*! \brief       Returns the remote address of a socket connection.
 *  \details     -
 *  \param[in]   SoConId          Socket connection identifier.
 *  \param[out]  IpAddrPtr        Pointer to remote address.
 *                                [Points to one of the following structs depending on configured IP address version of
 *                                parameter SoConId:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \return      E_OK             Request was accepted.
 *  \return      E_NOT_OK         Request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetRemoteAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr);

/**********************************************************************************************************************
 *  SoAd_GetRemoteAddrState()
 *********************************************************************************************************************/
/*! \brief       Returns the remote address and remote address state of a socket connection.
 *  \details     -
 *  \param[in]   SoConId          Socket connection identifier.
 *  \param[out]  IpAddrPtr        Pointer to remote address.
 *                                [Points to one of the following structs depending on configured IP address version of
 *                                parameter SoConId:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \param[out]  RemAddrState     Pointer to remote address state.
 *  \return      E_OK             Request was accepted.
 *  \return      E_NOT_OK         Request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-123315
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetRemoteAddrState(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr,
  P2VAR(SoAd_RemAddrStateType, AUTOMATIC, SOAD_APPL_VAR) RemAddrState);

/**********************************************************************************************************************
 *  SoAd_GetRcvRemoteAddr()
 *********************************************************************************************************************/
/*! \brief       Returns the remote address of the last received message on a socket connection.
 *  \details     -
 *  \param[in]   SoConId          Socket connection identifier.
 *  \param[out]  IpAddrPtr        Pointer to remote address.
 *                                [Points to one of the following structs depending on configured IP address version of
 *                                parameter SoConId:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \return      E_OK             Request was accepted.
 *  \return      E_NOT_OK         Request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetRcvRemoteAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr);

/**********************************************************************************************************************
 *  SoAd_EnableRouting()
 *********************************************************************************************************************/
/*! \brief       Enables a routing group.
 *  \details     -
 *  \param[in]   id         Routing group identifier.
 *  \return      E_OK       Request was accepted.
 *  \return      E_NOT_OK   Request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_EnableRouting(
  SoAd_RoutingGroupIdType id);

/**********************************************************************************************************************
 *  SoAd_EnableSpecificRouting()
 *********************************************************************************************************************/
/*! \brief       Enables a routing group on a specific socket connection.
 *  \details     -
 *  \param[in]   id         Routing group identifier.
 *  \param[in]   SoConId    Socket connection identifier.
 *  \return      E_OK       Request was accepted.
 *  \return      E_NOT_OK   Request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_EnableSpecificRouting(
  SoAd_RoutingGroupIdType id,
  SoAd_SoConIdType SoConId);

/**********************************************************************************************************************
 *  SoAd_DisableRouting()
 *********************************************************************************************************************/
/*! \brief       Disables a routing group.
 *  \details     -
 *  \param[in]   id         Routing group identifier.
 *  \return      E_OK       Request was accepted.
 *  \return      E_NOT_OK   Request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_DisableRouting(
  SoAd_RoutingGroupIdType id);

/**********************************************************************************************************************
 *  SoAd_DisableSpecificRouting()
 *********************************************************************************************************************/
/*! \brief       Disables a routing group on a specific socket connection.
 *  \details     -
 *  \param[in]   id         Routing group identifier.
 *  \param[in]   SoConId    Socket connection identifier.
 *  \return      E_OK       Request was accepted.
 *  \return      E_NOT_OK   Request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_DisableSpecificRouting(
  SoAd_RoutingGroupIdType id,
  SoAd_SoConIdType SoConId);

/**********************************************************************************************************************
 *  SoAd_SetRemoteAddr()
 *********************************************************************************************************************/
/*! \brief       Sets the remote address of a socket connection.
 *  \details     -
 *  \param[in]   SoConId        Socket connection identifier.
 *  \param[in]   RemoteAddrPtr  Pointer to remote address.
 *                              [Points to one of the following structs depending on configured IP address version of
 *                              parameter SoConId:
 *                                - SoAd_SockAddrInetType for IPv4
 *                                - SoAd_SockAddrInet6Type for IPv6]
 *  \return      E_OK           Request was accepted.
 *  \return      E_NOT_OK       Request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SetRemoteAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr);

/**********************************************************************************************************************
 *  SoAd_SetUniqueRemoteAddr()
 *********************************************************************************************************************/
/*! \brief       Sets the remote address of a suitable socket connection in a socket connection group.
 *  \details     Considers the best match algorithm to select the socket connection.
 *  \param[in]   SoConId            Socket connection identifier (any socket connection in socket connection group).
 *  \param[in]   RemoteAddrPtr      Pointer to remote address.
 *                                  [Points to one of the following structs depending on configured IP address version
 *                                  of parameter SoConId:
 *                                    - SoAd_SockAddrInetType for IPv4
 *                                    - SoAd_SockAddrInet6Type for IPv6]
 *  \param[out]  AssignedSoConIdPtr Pointer to assigned socket connection identifier.
 *  \return      E_OK               Request was accepted.
 *  \return      E_NOT_OK           Request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SetUniqueRemoteAddr(
  SoAd_SoConIdType SoConId,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2VAR(SoAd_SoConIdType, AUTOMATIC, SOAD_APPL_VAR) AssignedSoConIdPtr);

/**********************************************************************************************************************
 *  SoAd_ReadDhcpHostNameOption()
 *********************************************************************************************************************/
/*! \brief          Returns the DHCP hostname option currently configured on a local interface identified by a
 *                  socket connection.
 *  \details        -
 *  \param[in]      SoConId   Socket connection identifier.
 *  \param[in,out]  length    Length of buffer for hostname (length of provided buffer, updated to length of hostname).
 *  \param[out]     data      Pointer to buffer for hostname.
 *  \return         E_OK      Request was accepted.
 *  \return         E_NOT_OK  Request was not accepted.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-123281
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_ReadDhcpHostNameOption(
  SoAd_SoConIdType SoConId,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) data);

/**********************************************************************************************************************
 *  SoAd_WriteDhcpHostNameOption()
 *********************************************************************************************************************/
/*! \brief        Sets the DHCP hostname option on a local interface identified by a socket connection.
 *  \details      -
 *  \param[in]    SoConId   Socket connection identifier.
 *  \param[in]    length    Length of buffer for hostname.
 *  \param[in]    data      Pointer to buffer for hostname.
 *  \return       E_OK      Request was accepted.
 *  \return       E_NOT_OK  Request was not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \trace        CREQ-138020
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_WriteDhcpHostNameOption(
  SoAd_SoConIdType SoConId,
  uint8 length,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) data);

/**********************************************************************************************************************
 *  SoAd_ReadDhcpOption()
 *********************************************************************************************************************/
/*! \brief          Returns a DHCP option on a local address.
 *  \details        -
 *  \param[in]      IpAddrId      IP address identifier.
 *  \param[in]      Option        DHCP option code.
 *  \param[in,out]  DataLengthPtr Pointer to length of option buffer (updated to length of option on return).
 *  \param[out]     DataPtr       Pointer to option buffer.
 *  \return         E_OK          Request was accepted.
 *  \return         E_NOT_OK      Request was not accepted.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-189730
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_ReadDhcpOption(
  SoAd_LocalAddrIdType IpAddrId,
  uint16 Option,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) DataLengthPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr);

/**********************************************************************************************************************
 *  SoAd_WriteDhcpOption()
 *********************************************************************************************************************/
/*! \brief       Sets a DHCP option on a local address.
 *  \details     -
 *  \param[in]   IpAddrId    IP address identifier.
 *  \param[in]   Option      DHCP option code.
 *  \param[in]   DataLength  Length of option buffer.
 *  \param[in]   DataPtr     Pointer to option buffer.
 *  \return      E_OK        Request was accepted.
 *  \return      E_NOT_OK    Request was not accepted.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-189731
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_WriteDhcpOption(
  SoAd_LocalAddrIdType IpAddrId,
  uint16 Option,
  uint16 DataLength,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr);

# if ( SOAD_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  SoAd_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information.
 *  \details     Returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo    Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      SOAD_VERSION_INFO_API
 *  \trace       CREQ-123294
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, SOAD_APPL_VAR) versioninfo);
# endif /* SOAD_VERSION_INFO_API == STD_ON */

# if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
/**********************************************************************************************************************
 *  SoAd_GetAndResetMeasurementData()
 *********************************************************************************************************************/
/*! \brief       Gets and Resets (if requested) the measurement data.
 *  \details     Gets and Resets (if requested) the value of the counter of dropped TCP/UDP packets, dropped TCP 
 *               connections and dropped UDP frames.
 *  \param[in]   MeasurementIdx          The index to select specific measurement data.
 *                                       [range: SOAD_MEAS_DROP_TCP, SOAD_MEAS_DROP_UDP, 
 *                                               SOAD_MEAS_DROP_TCP_CONNECTION, SOAD_MEAS_DROP_UDP_FRAME,
 *                                               SOAD_MEAS_ALL]
 *  \param[in]   MeasurementResetNeeded  Flag to indicate if the counter needs to be reset.
 *                                       [range: TRUE, FALSE]
 *  \param[out]  MeasurementDataPtr      Buffer where the value of the counter is to be copied into.
 *                                       [range: POINTER may be NULL_PTR]
 *  \return      E_OK                    The operations were successful.
 *  \return      E_NOT_OK                The operations failed.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      SOAD_GET_RESET_MEASUREMENT_DATA_API
 *  \trace       CREQ-212605
 *********************************************************************************************************************/
Std_ReturnType SoAd_GetAndResetMeasurementData(
  SoAd_MeasurementIdxType MeasurementIdx,
  boolean MeasurementResetNeeded,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) MeasurementDataPtr);
# endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API   == STD_ON */

# define SOAD_STOP_SEC_CODE
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

#endif /* !defined(SOAD_H) */

/**********************************************************************************************************************
 *  END OF FILE: SoAd.h
 *********************************************************************************************************************/
