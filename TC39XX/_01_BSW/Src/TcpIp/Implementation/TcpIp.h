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
 *         \file  TcpIp.h
 *        \brief  Implementation of TcpIp Module
 *
 *      \details  This file is part of the TcpIp module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 *  Until version 7.xx.xx the following table lists the changes affecting the following files:
 *    TcpIp.*
 *    TcpIp_Cbk.h
 *    TcpIp_Types.h
 *    TcpIp_Priv.*
 *    TcpIp_Priv_Types.h
 *    TcpIp_Tcp.*
 *    TcpIp_Tcp_Cbk.h
 *    TcpIp_Udp.*
 *    TcpIp_Udp_Cbk.h
 *    (see files TcpIp_IpV4.h, TcpIp_IpV6.h and TcpIp_DhcpV4Server.h for changes in the submudules.)
 *
 *  Since version 8.00.00 all changes are documented in this file.
 *
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  This module is the successor of Tp_TcpIp[5.00.02].
 *  -
 *  01.00.00  2015-06-18  visfdn  -             TcpIp : New module Tp_AsrTpTcpIp (combination of TcpIp, IpV4 and IpV6)
 *            2015-07-09  visfdn  ESCAN00083590 TcpIp : FEAT-1248: Configuration of the TCP/IP stack according to AR 4.2.1
 *            2015-07-09  visal   ESCAN00082689 TcpIp : FEAT-1283: Use hardware-based checksum calculation (IPv4, IPv6,
 *                                                      TCP, UDP and ICMP) if it is supported by the microcontroller
 *            2015-07-09  visal   ESCAN00082684 TcpIp : FEAT-1249: Optimized UDP retry behavior e.g. in case of ARP miss
 *                                                      (TcpIp_GetRemotePhysAddr and TcpIp_GetCtrlIdx added)
 *            2015-07-09  visal   ESCAN00083909 TcpIp : Remove the APIs TcpIp_Htonl and TcpIp_Htons
 *            2015-07-09  visal   ESCAN00083911 TcpIp : Remove function TcpIp_PrepareShutdown, not needed any more
 *            2015-07-09  visal   ESCAN00083912 TcpIp : Remove TcpIp_GetLocNetAddr and TcpIp_GetLocNetMask, not needed any more
 *            2015-07-09  visal   -             TcpIp : Remove extern declaration of all declared TcpIp functions
 *            2015-07-09  visal   -             Tcp   : Remove parameter SockIdxPtr from the internal API TcpIp_Tcp_RxIndication
 *            2015-06-24  visal   ESCAN00083056 Tcp   : TCP causes DET in IP and tries to use a wrong address to answer
 *                                                      a SYN in LISTEN state
 *            2015-06-24  visal   ESCAN00083183 TcpIp : Network mask of IPv4 address has wrong byte order after
 *                                                      TcpIp_RequestIpAddrAssignment() is called
 *            2015-06-25  visal   ESCAN00083300 Tcp   : TCP Array index out of bounds
 *            2015-06-25  visal   ESCAN00082914 Udp   : UDP frame sent even if <Ul>_CopyTxData returns BUFREQ_NOT_OK
 *            2015-06-25  visal   ESCAN00082737 TcpIp : TcpIp_Bind() returns E_NOT_OK and reports Det Error if
 *                                                      LocalAddrId is TCPIP_LOCALADDRID_ANY
 *            2015-07-09  visal   ESCAN00083547 Tcp   : Buffers can be assigned to a socket several times, leading to inconsistency
 *            2015-07-20  visal   ESCAN00083690 TcpIp : TcpIp causes memory access violation or Det in IpV4/IpV6 in Dual Stack mode
 *            2015-07-20  visal   ESCAN00082912 Tcp   : <Ul>_TcpAccepted return value not handled
 *  01.00.01  2015-08-21  visfdn  ESCAN00084660 Udp   : Use of uninitialized pointer PbufPtr in TcpIp_UdpTransmit()
 *            2015-08-21  visfdn  ESCAN00084653 Tcp   : no SACK permit or TCP timestamp option at ECU passive open
 *  01.00.02  2015-09-11  visfdn  ESCAN00084728 Tcp   : TCP sends unnecessary DUP-ACKs
 *            2015-09-11  visfdn  ESCAN00084743 Tcp   : TCPIP_TCP_DEFAULT_TX_MSS for IPv6 sockets incorrect.
 *            2015-09-11  visfdn  ESCAN00084740 Tcp   : retransmission the last (n-1) bytes of n bytes-segment unnecessarily during zero window probing
 *            2015-09-11  visfdn  ESCAN00084742 Tcp   : TCP sends too big MSS for IPv6 connections
 *            2015-09-11  visfdn  ESCAN00084656 Tcp   : TCP SYN triggers infinite number of ARP/NDP requests
 *            2015-09-11  visfdn  ESCAN00084924 Tcp   : TcpIp_Bind() did not detect an already requested connection (port check fail due to wrong byte order)
 *            2015-09-11  visfdn  -             All   : Resolved PClint warnings
 *            2015-10-14  visal   ESCAN00085847 TcpIp : Adapt code to avoid MISRA and PClint deviations
 *            2015-10-14  visal   ESCAN00085566 Tcp   : MISRA deviation: MISRA-C:2004 Rule 15.2
 *            2015-10-14  visfdn  ESCAN00083547 Tcp   : Buffers can be assigned to a socket several times, leading to inconsistency (rework)
 *  02.00.00  2015-11-27  visfdn  ESCAN00086824 Udp   : Support of multiple IP buffer fragments in TcpIp_UdpTransmit()
 *            2015-11-27  visfdn  ESCAN00086825 All   : TX checksum calculation always performed by lower layer
 *            2015-11-27  visal   ESCAN00086795 TcpIp : FEAT-10: Send the FQDN option via DHCP to identify the ECU
 *            2015-11-27  visal   ESCAN00086797 TcpIp : FEAT-10: Support triggering of IP address assignment
 *            2015-11-27  visal   ESCAN00086798 TcpIp : FEAT-10: Implement API to read the local physical address
 *            2015-11-27  visal   ESCAN00086848 TcpIp : Adapt wrong define values in DHCPv4
 *            2015-12-03  visfdn  ESCAN00086099 Tcp   : TCP calculates wrong message length from MSS received in IPv6 TCP SYN
 *            2015-12-03  visfdn  ESCAN00086097 Tcp   : Socket resources not released after TCP SYN with illegal option length is received
 *            2016-01-07  visal   ESCAN00087306 Tcp   : TCP Nagle algorithm can not be enabled / disabled in state CLOSED
 *  02.00.01  2016-01-29  visal   ESCAN00087828 TcpIp : Compiler error: Missing function declaration for TcpIp_DhcpV6ReadOption and TcpIp_DhcpV6WriteOption
 *            2016-01-29  visal   ESCAN00087910 TcpIp : Missing checks for valid address IDs in DHCP option APIs may lead to NULL-Ptr exceptions
 *            2016-01-29  visal   ESCAN00087908 TcpIp : Minor code rework due to MISRA / Code Review findings
 *            2016-01-28  visfdn  ESCAN00087894 Tcp   : TCP client connection attempt (SYN) rejected with RST
 *            2016-01-28  visfdn  ESCAN00087897 Tcp   : TCP enters congestion avoidance too early/late or memory access violation (invalid read access)
 *  02.01.00  2016-01-19  visfdn  ESCAN00087557 TcpIp : Allow configuration of TcpIp lower layer other than EthIf
 *            2016-02-26  visal   ESCAN00087677 All   : FEAT-1347: TLS as TcpIp plug-in
 *            2016-02-26  visal   ESCAN00088589 All   : Remove XX defines for internal callback functions (events, and random number)
 *            2016-02-26  visal   ------------- Tcp   : Implement the same TCP interrupt locks as in version 3.10.11
 *            2016-02-26  visal   ------------- Tcp   : Code rework: replace if-else chain by switch-case construct
 *            2016-02-26  visal   ESCAN00088319 Udp   : Compiler error: TcpIp_Udp.c: TcpIp_DhcpV4_Cbk.h: No such file or directory
 *            2016-03-30  visal   ESCAN00088304 TcpIp : IpAddrAssignment is not indicated to the socket owners
 *  03.00.00  2016-05-12  visfdn  ESCAN00089974 TcpIp : TcpIp_GetIpAddr() does not provide values for IPv6 netmask and default router.
 *            2016-05-17  visfdn  ESCAN00090041 Tcp   : Improved internal TCP TX Retry Queue handling
 *            2016-05-17  visfdn  ESCAN00088736 TcpIp : TCP rejects SYN if listen socket is bound to all IP addresses of a controller
 *            2016-05-17  visfdn  ESCAN00084745 Tcp   : Usage of two different configuration parameters for Retransmission Timer
 *            2016-05-17  visfdn  ESCAN00084724 Tcp   : Nagle-Algorithm does not buffer data until outstanding data has been ACKed
 *            2016-05-17  visfdn  ESCAN00084726 Tcp   : TCP stops sending and does not ACK received data
 *            2016-05-18  visfdn  ESCAN00085683 Tcp   : Zero Window Probe is sent immediately and not after RTO seconds
 *            2016-06-13  visfdn  ESCAN00089368 TcpIp : FEAT-1516: Support IP address assignment methods according to AR 4.2.1 for IPv4
 *            2016-06-22  visfdn  ESCAN00088858 TcpIp : DHCPv4 server does not respond correctly to a client with broadcast flag set to 0
 *            2016-06-23  visal   ESCAN00089291 Tcp   : ECU ceases to transmit TCP data completely or partially
 *            2016-06-23  visal   ESCAN00089289 Tcp   : Reported TCP receive window size incorrect
 *            2016-06-23  visal   ESCAN00089388 Tcp   : ECU stops responding during TCP communication
 *            2016-07-12  visal   ESCAN00090966 TcpIp : Calling TcpIp_TcpReceived causes division by zero
 *  03.00.01  2016-08-11  visfdn  ESCAN00091009 Tcp   : MSL timer has an underflow if configured to 0s
 *  03.00.02  2016-08-29  visal   ESCAN00089031 Tcp   : [IETF] Close on listen socket did not close not established connections
 *            2016-08-29  visal   ESCAN00085278 Tcp   : ECU sends SYN/ACK with MSS = 0 if Listen socket has no assigned buffers
 *            2016-09-01  visal   ESCAN00091010 TcpIp : It is not possible to send less data than requested when using TLS
 *            2016-09-15  visal   ESCAN00084719 TcpIp : Compiler warning: Several warnings when the component is compiled with Visual Studio
 *  04.00.00  2016-10-04  visfdn  ESCAN00092165 TcpIp : FEAT-1953: Support of Dynamic Length in CopyTxData
 *            2016-10-14  visfdn  ESCAN00092054 TcpIp : Compiler warning: Inconsistent memory mapping for constant TcpIp_Ipv6NullAddr
 *            2016-10-14  visfdn  ESCAN00084737 Udp   : UDP packets not sent if socket is unbound
 *            2016-10-14  visfdn  ESCAN00092354 TcpIp : Use incrementing numbers for TCP/UDP ports in dynamic range.
 *            2016-10-14  visfdn  FEATC-258     TcpIp : FEAT-1816: Split MainFunctions to optimize gateway use-case
 *            2016-10-14  visfdn  FEATC-263     Tcp   : FEAT-1509: Support of the TCP Keep Alive Mechanism
 *            2016-10-14  visfdn  ESCAN00092353 Tcp   : TCP does not send last ACK segment during active close if MSL is 0
 *            2016-10-28  visal   FEATC-361     TcpIp : FEAT-1996: TLS Heartbeat Extension
 *  04.00.01  2017-01-02  visal   ESCAN00092609 Tcp   : TcpIp calls TxConfirmation of upper layer with locked interrupts
 *            2017-01-02  visal   ESCAN00093077 Tcp   : TCP connection initiated or accepted by SoAd is interrupted or cannot be established.
 *  04.00.02  2017-02-02  visfdn  ESCAN00093113 Tcp   : TCP closes connection via RST if reserved bits in TCP header are set
 *            2017-02-02  visfdn  ESCAN00093812 Tcp   : TcpIp calls <Up>_RxIndication() and <Up>_TxConfirmation() for TCP data in unexpected order
 *            2017-02-03  visfdn  ESCAN00093622 Udp   : Invalid UDP packet with length bigger than IP payload length is not dropped
 *            2017-02-13  visfdn  ESCAN00093149 Tcp   : TCP sends data after FIN
 *            2017-02-14  visfdn  ESCAN00093967 TcpIp : Inconsistent variable memory mapping causes triggering of OS Protection Hook
 *  05.00.00  2017-02-22  visfdn  ESCAN00094090 TcpIp : Compiler error: Missing definition of NvM_BlockIdType
 *  05.00.01  2017-04-26  visfdn  ESCAN00094737 Tcp   : TCP does not send keep-alive messages
 *  06.00.00  2017-04-28  visjsb  STORYC-676    TcpIp : Enhancements for ETM (TcpIp: add "Clear NDP Cache" API)
 *            2017-05-09  viswnk  STORYC-567    TcpIp : IPv6: Support Ethernet stack DEM events (TcpIp)
 *            2017-05-10  visfdn  STORYC-144    TcpIp : Release of FEAT-1481 (IPv4 Fragmentation)
 *  06.01.00  2017-05-15  visfdn  ESCAN00095154 Tcp   : TCP connection not accepted if TLS client exists in configuration
 *            2017-05-18  visjsb  STORYC-1044   TcpIp : FEAT-2844,S-618 [ETH] Support of ASR4.3 APIs TcpIp_GetArpCacheEntries and TcpIp_GetNdpCacheEntries
 *            2017-06-09  visal   ESCAN00092800 Tcp   : TCP sends wrong sequence number in a RST-message
 *            2017-06-09  visal   ESCAN00094682 TcpIp : TcpIp_TcpIpEvent callback is not called for FIN in case TLS is used
 *            2017-06-09  visal   ESCAN00084746 TcpIp : TCP socket is blocked if not closed by user via TcpIp_Close()
 *  06.02.00  2017-06-21  viswnk  STORYC-1676   TcpIp : TASK-40642: In TcpIp_GetLocSockAddr() the DET errorId for invalid sockIdx was changed from TCPIP_E_INV_ARG to TCPIP_E_INV_SOCK_ID.
 *                        viswnk  STORYC-1676   TcpIp : TASK-40648: In TcpIp_TcpTransmit() the DET API-Id was changed from TCPIP_API_ID_REL_IP_ADDR_ASSIGN to TCPIP_API_ID_TCP_TRANSMIT.
 *            2017-06-27  viswnk  STORYC-1676   TcpIp : TASK-41780: In TcpIp_GetArpCacheEntries the DET error code was changed from TCPIP_E_INV_ARG to TCPIP_E_PARAM_POINTER.
 *  06.03.00  2017-07-25  visfdn  STORYC-543    TcpIp : Support of AR4.3 API TcpIp_IcmpV6Transmit() and <Up_IcmpMsgHandler> callback for IPv6.
 *  06.04.00  2017-08-09  visal   STORYC-1060   TcpIp : FEAT-2948: TLS Server CertChain Callout in TLS Client
 *            2017-08-17  visfdn  -             TcpIp : Resolved review findings.
 *  07.00.00  2018-03-15  visfdn  STORYC-352    TcpIp : Usage of ComStackLib for generated data.
 *            2018-03-15  visfdn  STORYC-2204   TcpIp : Code Refactoring in order to improve code metrics.
 *            2017-10-05  visfdn  ESCAN00096277 Tcp   : Misalignment exception in TcpIp_Tcp_VHandleOptions() on RH850/V850 platform
 *            2017-12-18  visfdn  ESCAN00084723 Tcp   : TcpIp does not support simultaneous open of TCP connection
 *  07.00.01  2018-04-10  visal   STORYC-4950   All   : Integration of code inspection findings
 *            2018-04-10  visal   ESCAN00099044 Tcp   : TCP accepts more incoming connections than configured or no connection
 *            2018-04-10  visal   ESCAN00099047 Tcp   : TCP ignores too big segment data but accepts the FIN flag of an invalid segment
 *            2018-04-10  visal   ESCAN00099056 Tcp   : TCP reads unknown data due to erroneous TCP header content
 *            2018-04-11  visfdn  ESCAN00098815 Udp   : Ethernet TX buffer not released if limit of UDP retry elements for a socket is reached
 *  07.00.02  2018-04-20  visfdn  ESCAN00099170 Udp   : ECU does not transmit UDP packets
 *  07.00.03  2018-04-19  visfdn  ESCAN00092201 Tcp   : TCP close call in CLOSED state must indicate an error
 *            2018-05-17  visal   ESCAN00099436 Tcp   : The CONNECTED callback is issued for a wrong socket in case of TLS connections
 *            2018-05-17  visal   ESCAN00099437 Tcp   : TLS buffer is not released if indirect copy of data failed
 *            2018-06-06  visal   -             Tcp   : Review integration
 *  -------------------------------------------------------------------------------------------------------------------
 *            From here on this list contains all changes made to the TcpIp module.
 *  -------------------------------------------------------------------------------------------------------------------
 *  08.00.00  2018-05-30  vismjv  STORYC-2516   ARP   : Support ARP retry cycle time with less than 1 second (in Mainfunction cycles)
 *            2018-06-22  visfdn  ESCAN00099773 Icmp  : Outgoing ICMPv4 packets have TTL value of IP controller instead if ICMPv4 specific value
 *            2018-06-22  visfdn  ESCAN00099764 TcpIp : Compiler error: Type mismatch through missing type cast (TcpIp_Priv.h)
 *            2018-06-25  viswnk  ESCAN00099762 TcpIp : The DEM event E_DUPLICATE_DHCP_ADDR is not reset at TrcvLinkStateChg, instead wrong DEM event E_CONNREFUSED is reset at that time.
 *            2018-06-26  vismjv  ESCAN00099794 DhcpV*: TcpIp_Dhcp* Read/WriteOption may cause invalid memory access
 *            2018-07-02  visabn  ESCAN00099822 IpV6  : IPv6 unicast packets are not sent or link layer destination address is incorrect
 *            2018-07-03  visfdn  ESCAN00099780 IpV6  : Static IPv6 source address is not assigned automatically
 *            2018-07-03  visfdn  ESCAN00099881 Tcp   : Compiler error: "declaration may not appear after executable statement in block" in TcpIp_TcpTransmitTls()
 *            2018-07-03  visfdn  ESCAN00097582 Tcp   : TcpIp_TcpIpEvent callback is not called for FIN in case TLS is used
 *            2018-07-03  visfdn  ESCAN00099464 TcpIp : ECU stops sending packets because ethernet buffers are not released
 *  08.00.01  2018-07-16  vismjv  ESCAN00100044 ARP   : GetArpCacheEntries  function does not return any valid Arp cache entries
 *            2018-08-10  vismjv  -             TcpIp : ARP,IcmpV4,DhcpV4 Silent Review Integration
 *            2018-08-17  visal   ESCAN00100479 Tcp   : FIN flag is not sent after segment has been re-sized
 *            2018-08-23  visal   STORYC-355    Tcp   : SAFE Increase Test Depth
 *            2018-08-29  visfdn  ESCAN00100568 IpV4  : IpV4 does not call EthIf_UpdatePhysAddrFilter if default multicast address is assigned manually
 *            2018-09-06  viswnk  ESCAN00100004 IpV4  : IpV4 discards received packets with invalid checksum even if hardware checksum offloading is enabled.
 *  08.00.02  2018-08-07  vismjv  ESCAN00100674 ARP   : TcpIp_GetArpCacheEntries function returns ARP entry status always stale
 *            2018-09-09  visabn  ESCAN00100634 IPv6  : Upper layer checksum verification for received packet fails when HW checksum offloading is enabled and fragmentation header is present
 *            2018-09-09  visabn  ESCAN00100636 IPv6  : Transmitted Ip fragments may have corrupted header fields
 *            2018-09-28  visal   -             Tcp   : Comments added and internal function renamed
 *            2018-09-28  visfdn  -             TcpIp : Small refactorings to improve code coverage.
 *            2018-10-04  visal   ESCAN00100935 Tcp   : TCP closes connection without sending its FIN
 *  09.00.00  2018-10-23  visal   ESCAN00101123 Tcp   : Reset TCP SockStateNext after sending the ACK in state CloseWait
 *            2018-10-23  visal   ESCAN00101124 Tcp   : Reopening TCP cwnd fails after it has been set to 0 when detecting a too small PathMtu
 *            2018-10-25  visfdn  ESCAN00101125 IpV4  : IpV4_Ip_VJoinMulticastGroup() reports error IPV4_E_INV_PARAM to the Det
 *            2018-10-25  visfdn  ESCAN00101157 Tcp   : TCP sends segments out of order if ethernet TX buffers are busy
 *            2018-10-29  visfdn  ESCAN00100888 TcpIp : TCP/UDP always uses first source port from the dynamic port range after 16383 connections
 *            2018-10-31  vismjv  ESCAN00100917 TcpIp : TcpIp_GetRemotePhysAddr may cause invalid memory access when called with invalid input
 *            2018-10-31  vismjv  ESCAN00100915 TcpIp : TcpIp_GetArpCacheEntries may cause invalid memory access when called with invalid input
 *            2018-11-07  visfdn  ESCAN00101224 Tcp   : Unexpected behavior if TCP RST segment is sent over IPv6 in dual stack use case
 *            2018-11-16  vismjv  ESCAN00101358 TcpIp : TcpIp_DhcpV4_GetStatus does not return correct Dhcp State
 *            2018-12-17  visal   ESCAN00101375 Tcp   : Path Mtu Change is not handled correctly in TCP
 *            2018-12-17  visal   STORYC-7519   Tcp   : Move the TCP path MTU change handling to the MainFunction context
 *            2018-12-17  visal   ESCAN00101601 Tcp   : Memory access violation in TcpIp_Tcp_Init.
 *            2019-01-11  visfdn  ESCAN00101949 IpV6  : IPv6 Neighbor Solicitations are sent from unexpected IP address or controller/VLAN
 *            2019-01-29  visfdn  ESCAN00101816 TcpIp : Compiler error: In TcpIp_DhcpV*.c due to undeclared Dns variables
 *            2019-02-12  visal   ESCAN00101375 Tcp   : Path Mtu Change is not handled correctly in TCP
 *            2019-02-22  visfdn  ESCAN00102233 IpV6  : IPv6 always assumes minimum link MTU if a ICMPv6 Packet Too Big message is received
 *            2019-02-25  visfdn  ESCAN00101622 Tcp   : Processing of queued TCP segments is incorrect when Path Mtu is changed to a large value
 *  10.00.00  2019-03-25  visabn  STORYC-7952   TcpIp : TcpIp DHCP Option Extension IPv6
 *            2019-04-25  vismjv  STORYC-7951   TcpIp : TcpIp DHCP Option Extension IPv4
 *            2019-04-18  vispcn  ESCAN00102912 IpV4  : Compiler error: 'IpV4_State' uses conflicting section name
 *            2019-04-24  vismjv  ESCAN00102558 ARP   : Two ARP entries are created for the same destination address which leads to TCP_RST
 *  10.00.01  2019-04-26  visabn  ESCAN00102650 IpV6  : Invoking TcpIp_ReleaseIpAddrAssignment() for manual DhcpV6 address does not have any effect
 *            2019-04-26  visabn  ESCAN00102902 Ndp   : Compiler warning: C4242 possible loss of data in TcpIp_Ndp.c
 *            2019-05-23  visabn  ESCAN00103229 Ndp   : Compiler error: Multiple errors in TcpIp_Ndp.c if TcpIpNdpSlaacDadNumberOfTransmissions is set to 0
 *  10.00.02  2019-06-04  vismjv  ESCAN00101852 IcmpV4: IpV4_Icmp_SendDestUnreachable() includes 64 bytes of payload instead of 64 bits
 *            2019-06-07  visabn  ESCAN00101360 IpV6  : IPv6 does not use optimal source address for neighbor solicitations
 *            2019-06-07  visabn  ESCAN00091700 DhcpV6: DHCPv6 client does not send expected number of release messages
 *            2019-06-11  visabn  ESCAN00103202 TcpIp : NvM failure leads to undefined local IP address configuration.
 *  11.00.00  2019-06-17  visabn  FEAT-5752     Ndp   : Extend NDP with "Best Match" for Source IP Address in the Neighbor Solicitation Message
 *  12.00.00  2019-07-26  visabn  TCPIP-52      TcpIp : Merge of IPSec branch to main development trunk
 *            2019-08-07  visabn  TCPIP-516     TcpIp : [IPSEC] IpSec transform configuration shifted to TcpIp
 *            2019-08-09  vismjv  TCPIP-469     TcpIp : Support of AR4.3 API TcpIp_GetAndResetMeasurementData()
 *            2019-08-15  visabn  TCPIP-834     TcpIp : Extend TcpIp_GetAndResetMeasurementData() by vendor-specific measurement counters
 *  13.00.00  2019-09-02  visabn  TCPIP-69      TcpIp : MISRA-C:2012 TCP/IP
 *            2019-09-02  visabn  ESCAN00104212 IpV4  : IP identification number mismatch when a segmented transmission is interrupted by another task that also calls IpV4_Ip_Transmit.
 *            2019-09-09  vismjv  TCPIP-911     ARP   : Transmission of gratuitous ARPs on startup
 *            2019-09-16  visabn  ESCAN00104173 IpV6  : Compiler error: [TCPIP] [IPv6] In UDP only configuration for IpV6
 *            2019-09-25  vispcn  ESCAN00104424 DHCPv4: Server: Compiler error: 'EthIf_GetPortMacAddr' undefined; assuming extern returning int
 *  13.00.01  2019-10-01  visabn  ESCAN00104356 Tcp   : TCP FINWAIT-2 timeout is not implemented
 *            2019-10-01  vismjv  ESCAN00104324 DHCPV4: DHCPV4 'secs' field  does not match between the last sent Discover(before offer reception) and Request message
 *            2019-10-10  vismjv  ESCAN00103717 Tcp   : TLS Connection is not properly reset in case of closing the TCP Socket using Abort
 *            2019-10-18  visal   ESCAN00103972 Tcp   : Upper Layer of TCP is informed twice about closure of TCP connection
 *            2019-10-18  visal   ESCAN00104353 Tcp   : Rst receiption during MainFunction causes inconsistent socket state
 *            2019-10-18  visal   ESCAN00104625 Tcp   : TCP issues CLOSED event instead of RESET event
 *  13.00.02  2019-11-08  vispcn  ESCAN00104631 TcpIp : Same socket is returned if TcpIp_GetSocketForUser() is called reentrant.
 *            2019-11-12  vismjv  ESCAN00104482 Tcp   : Rceived MSS = 0 during TCP handshake leads to Infinite loop(Watchdog reset)
 *            2019-11-14  visabn: ESCAN00104670 Tcp   : TCP sent invalid RST after receiving option with invalid length.
 *  13.00.03  2020-01-02  vismjv  ESCAN00105222 ARP   : [IETF RFC Conformance] ARP is not triggered for linklocal source address and non-linklocal destination address and vice versa
 *            2020-01-20  vismjv  TCPIP-1218    IPV6  : Analyze and fix open IPv6 and NDP MISRA findings.
 *            2020-01-24  visabn  TCPIP-1072    TcpIp : [IPSEC] IpSec Diagnostic query
 *  13.00.04  2020-02-17  visabn  ESCAN00105607 IPV6  : [IPv6] [NDP] NUD probes do not use best match source address
 *            2020-02-18  visbdk  ESCAN00105361 Tcp   : [IETF RFC Conformance] TCP responds with RST segment on incoming SYN segment with invalid remote address.
 *            2020-02-19  vismjv  TCPIP-1120    TCPIP : Provide information about dropped frames due to insufficient Tx/Rx buffers
 *            2020-02-24  visbdk  ESCAN00105604 Tcp   : Invalid call to upper layer TcpIp_TcpIpEvent callback in case of closing the TCP Socket using Abort.
 *            2020-03-13  visbdk  ESCAN00097385 Tcp   : Invalid call to upper layer TcpIp_TcpIpEvent callback for the same event.
 *            2020-03-04  vistwe  TCPIP-1400    Tcp   : Ensure that last ACK of TCP handshake does not include application data.
 *            2020-03-06  vispcn  TCPIP-1459    TcpIp : Use ComStackLib Add/Sub functions for calculation of buffer descriptor FillLevel.
 *            2020-03-09  vistwe  ESCAN00105681 IpV6  : Initialize all IpV6 sockets.
 *            2020-03-09  vispcn  ESCAN00105776 TcpIp : Compiler warning: Variable is used before its value is set. (Internal function TcpIp_VSetSocketSpecificFramePriority)
 *            2020-03-09  vispcn  ESCAN00105739 TcpIp : [IPV6] TcpIp_ChangeParameter for changing TCPIP_PARAMID_FRAMEPRIO may fail in IpV6 only configuration
 *            2020-03-09  vispcn  ESCAN00105823 TcpIp : TCP transmits more data than would fit into its TxBuffer, retransmitted data is corrupted
 *            2020-03-11  vismjv  ESCAN00105851 Arp   : Invalid write access during IpV4 Arp init.
 *  13.00.05  2020-03-16  visbdk  ESCAN00105874 IPV4  : Compiler error: [IPv4] 'destAddr' : undeclared identifier.
 *  13.00.06  2020-03-19  vismjv  ESCAN00096364 Tcp   : Frame priority set for TCP listen sockets is not inherited to accepted sockets
 *            2020-03-19  visabn  ESCAN00105229 IPV6  : [IPV6] Packet sent from optimistic link local Address are sent with wrong destination address
 *            2020-03-23  visbdk  ESCAN00105190 Tcp   : Order inside close function changed to ensure that TLS can send a CLOSE_NOTIFY alert.
 *            2020-03-23  visabn  ESCAN00105856 TcpIp : [IPSEC] TcpIp_IpSec_AddSaEntryPair does not clear SA entry if adding fails
 *            2020-03-24  vistwe  ESCAN00100368 IpV6  : IPv6 calls IpAssignmentChange callback for other source address before link-local address is configured.
 *  13.00.07  2020-03-31  vismjv  ESCAN00105903 Tcp   : Discarding incoming packets during the processing of an RST.
 *  13.01.00  2020-04-24  visbdk  ESCAN00105479 TcpIp : Implement handling of TcpIp_RequestComMode.
 *            2020-04-24  visbdk  ESCAN00105479 IpV4  : Move functionality of IpV4_Ip_Cbk_TrcvLinkStateChg to IpV4_Ip_TrcvLinkStateChgInternal.
 *            2020-04-24  visbdk  ESCAN00105479 IpV6  : Move functionality of IpV6_Cbk_TrcvLinkStateChg to IpV6_TrcvLinkStateChgInternal.
 *  14.00.00  2020-04-27  vismjv  TCPIP-1451    Arp   : Support AUTOSAR parameter TcpIpArpRequestTimeout.
 *            2020-05-12  visbdk  ESCAN00106109 Tcp   : Remove incorrect transmit of ACK in state LAST-ACK.
 *  14.00.01  2020-07-21  visbdk  ESCAN00106785 Tcp   : Incorrect calculation of the Windows size when interrupting the TcpIp_RxIndication function.
 *            2020-07-21  visbdk  ESCAN00106795 Tcp   : Corruption of the Tx Data fill level leads to incorrect processing of the data.
 *            2020-07-28  visbdk  ESCAN00106757 Udp   : Invalid memory write access when UDP Tx retry queue is enabled.
 *            2020-08-04  vismjv  ESCAN00106651 IcmpV4: TcpIpIcmpEchoReplyMaxLen is not set correctly for Tx of Echo Reply.
 *            2020-08-11  vismjv  ESCAN00106790 DHCPV4: DHCP sends multiple REQUEST messages one after another when entering REBINDING state.
 *            2020-08-13  vismjv  ESCAN00106798 IcmpV4: ICMPv4 Destination Unreachable message is dropped during send if destination address is not cached.
 *            2020-08-18  visal   ESCAN00106863 Tcp   : TCP socket is not closed correctly after initiating to close the connection
              2020-08-18  vismjv  ESCAN00106998 UDP   : Invalid memory write access when UDP Tx Retry Queue is enabled after socket restart
 *            2020-08-18  vismjv  ESCAN00107050 ARP   : [IPv4][ARP] MAC address is still not found after received ARP response and TcpIpPhysAddrConfig is called
 *            2020-08-18  vismjv  ESCAN00107063 ARP   : Use of partial updated MAC address for IPv4 packet transmission or as result of TcpIp_GetRemotePhysAddr()
 *            2020-08-19  vismjv  ESCAN00107057 ARP   : [IPv4][ARP] An ARP entry can be overwritten when two messages are sent parallelly
 *  14.00.02  2020-09-03  vistbk  ESCAN00107065 TcpIp : Measurement data for packet counter can have a value that is by one to low
 *            2020-09-03  vistbk  ESCAN00106903 TcpIp : [IPSEC][IPV4] The ICV check or generate does not work
 *            2020-09-03  vistbk  ESCAN00106900 TcpIp : [IPSEC][IPv4] IPSec Packets may not be sent/received when TcpIp_IpSecSaEntryPairDelete is invoked
 *            2020-09-03  vistbk  ESCAN00106897 TcpIp : [IPSEC] [IPv4] IpSec packets may not be sent out or secured when multiple IpSec connections are created simultaneously
 *            2020-09-07  vismjv  ESCAN00106956 DHCPV4: [DHCPv4] Corrupted DHCP timeout with a premature DHCP rebind or renew
 *            2020-09-07  visal   ESCAN00107140 Tcp   : Incorrect handling of received data segments while in LAST-ACK state of TCP
 *            2020-09-08  vismjv  ESCAN00106919 DHCPV6: [DHCPv6][IPv6] DhcpV6 address assignment may fail
 *            2020-09-09  vismjv  ESCAN00106932 DHCPV6: [DHCPv6][IPv6] Configured DhcpV6 user options is not be sent out in messages
 *            2020-09-09  vismjv  ESCAN00106933 IPV6  : [IPv6] Fragmented IPv6 packets contains invalid fields or fragments are not sent out
 *            2020-09-10  visabn  ESCAN00106937 IPV6  : [IPv6] Packets to destinations with dynamically configured on-link prefix is not sent
 *            2020-09-14  visabn  ESCAN00107341 IPSEC : [IPSec][IPv4] Invalid Memory access when IPSec is enabled
 *  14.01.00  2020-09-16  visabn  MSR4-30627    IPSEC : SafeBSW for Tp_AsrTpTcpIp IPsec extension
 *            2020-10-01  vismjv  TCPIP-1894    Tcp   : Stop TCP MainFunction processing of an inactive socket as soon as possible
 *  14.01.01  2020-10-12  visbdk  TCPIP-2203    Tcp   : Remove name of authors of file history.
 *            2020-10-13  visbdk  ESCAN00106986 TcpIp : Implement additional check within TcpIp_Bind() for a valid SocketOwnerIndex.
 *            2020-10-14  vismjv  ESCAN00107516 DhcpV6: [IPv6] DhcpV6 messages transmitted with FQDN option is not according to RFC.
 *            2020-10-14  vismjv  ESCAN00107436 DhcpV4: [IPv4] DhcpV4 messages transmitted with FQDN option is not according to RFC.
 *  14.02.00  2020-10-26  vispcn  TCPIP-2120    TcpIp : Support PB-S variance in TcpIp module.
 *            2020-10-28  vismjv  ESCAN00107698 DHCPV4: DHCPV4 'secs' field of the last sent Discover message and renew request does not match
 *            2020-11-06  visbdk  ESCAN00107748 IpV4  : Compiler error: EthTrcv_LinkStateType not known in TcpIp_IpV4.h.
 *            2020-11-09  vistbk  ESCAN00107724 IPSEC : [IPSEC][IPv4] Use not IPsec protocol number for UDP/TCP checksum pseudo header
 *            2020-11-09  vismjv  ESCAN00106790 DHCPV4: DHCP sends multiple REQUEST messages one after another when entering REBINDING state.
 *            2020-11-11  visal   ESCAN00107146 Tcp   : Wrong order of the SACK blocks within TCP options while sending multiple segments
 *  14.02.01  2020-11-16  vistbk  TCPIP-2359    IPV6  : Remove unsupported TcpIp_Ipv6_Privacy_Extensions TcpIp_Ipv6_MLD, TcpIp_DList and IPv6_Debug-code
 *            2020-11-27  vismjv  TCPIP-2279    TcpIp : Fixed naming of indices to be compliant with coding guidelines.
 *            2020-12-04  vismjv  TCPIP-1923    TcpIp : Fix Helix QAC warnings
 *            2020-12-10  visabn  ESCAN00108044 IPSEC : [IPSEC][IPv4] Configuring Local IP Address in SPD causes the SPD entry to be ignored
 *            2020-12-22  vismjv  TCPIP-2466    TcpIp : Integrate CslCheckIndexes script to CIplus automation
 *  14.03.00  2021-01-20  vistbk  TCPIP-2370    IPV6  : Support Static Default Router for IPv6
 *            2021-01-26  vispcn  ESCAN00108384 IPV6  : Compiler error: Undeclared identifier "socketIdx" if IPv6 is enabled
 *            2021-01-26  vispcn  ESCAN00108392 IPV6  : Compiler error: Undeclared identifiers in case of IPv6-only configuration
 *            2021-01-26  vispcn  ESCAN00108391 IPV6  : Compiler error: Parse error in TcpIp_DhcpV6_VTxMessage() function
 *            2021-01-26  vispcn  ESCAN00084729 Tcp   : [IETF RFC Conformance] TCP does not echo timestamp option value of received SYN or SYN/ACK
 *  14.03.01  2021-02-01  vistbk  TCPIP-2530    IPV6  : [IPV6] Compiler error: "IPV6_LADDR_STATE_TENTATIVE" is not known in TcpIp_Ndp.c if DAD is disable.
 *            2021-02-02  vismjv  ESCAN00092106 IpV4  : [IETF RFC Conformance] ECU does not receive fragmented IPv4 packet if reassembly of packet with same identification value failed before
 *  14.03.02  2021-03-01  vistbk  ESCAN00108615 IPSEC : [IPSEC][IPv4] Call Csm_MacGenerate with output-pointer before finish
 *            2021-03-01  vispcn  ESCAN00108686 IpV4  : Compiler error: Parse error near 'IpV4_Ip_ReassemblyBufferDescType'
 *  14.03.03  2021-03-31  vispcn  ESCAN00108665 Tcp   : TCP does not close a socket properly when the socket is closed simultaneously on both sides
 *********************************************************************************************************************/
#if !defined TCPIP_H
# define TCPIP_H

/**************************************************************************************************
**************************************************************************************************/

/*
+---+         +--------+   +--------+   +--------+
|   |         |        |   |        |   |        |
|   | ------- |  SoAd  |   |  SCC   |   |  HTTP  |  ...
|   |         |        |   |        |   |        |
|   |         +--------+   +--------+   +--------+
|   |             |            |            |
|   |      +-------------------------------------------------+
| E |      |   +---------------------------+         (TcpIp) |
| t |      |   |                           |                 |
| h |      |   |           TCPIP           |                 |
| S |      |   |                           |                 |
| m |      |   +---------------------------+                 |
|   |      |         |               |                       |   +--------+
|   |      |   +-----------+   +-----------+                 |   |        |
|   |      |   |    UDP    |   |    TCP    |---------------------|  TLS   |
|   |      |   +-----------+   +-----------+                 |   |        |
|   |      +-------------------------------------------------+   +--------+
|   |                |                            |
|   |                |                            |
|   |      +-------------------+         +-------------------+
|   |      |            (IpV4) |         |            (IpV6) |
|   |      |                   |         |                   |
|   |      |       IPv4        |         |       IPv6        |
|   |      |      ICMPv4       |         |      ICMPv6       |
|   |      |      DHCPv4       |         |      DHCPv6       |
|   |      |       ARP         |         |       NDP         |
|   |      |                   |         |                   |
|   |      +-------------------+         +-------------------+
|   |                         |           |
|   |                         |           |
|   |                      +-----------------+
|   | -------------------- |      EthIf      |
+---+                      +-----------------+
                              |            \
                    +-----------------+     \  +-------------+
                    |       Eth       |      --|   EthTrcv   |
                    +-----------------+        +-------------+
*/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

#include "TcpIp_Cfg.h"
#include "TcpIp_Cbk.h"
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# include "TcpIp_Arp_Cbk.h"
# include "TcpIp_IpV4_Cbk.h"
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# include "TcpIp_IpV6_Cbk.h"
#endif

#include "TcpIp_Lcfg.h"

#include "TcpIp_Types.h"

#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
# include "NvM.h"
#endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* software module version */
#define TCPIP_SW_MAJOR_VERSION                     14u
#define TCPIP_SW_MINOR_VERSION                     3u
#define TCPIP_SW_PATCH_VERSION                     3u

#define TP_ASRTPTCPIP_VERSION                      (TCPIP_SW_MAJOR_VERSION << 8 | TCPIP_SW_MINOR_VERSION)

/* supported Autosar version */
#define TCPIP_AR_RELEASE_MAJOR_VERSION             4u
#define TCPIP_AR_RELEASE_MINOR_VERSION             2u
#define TCPIP_AR_RELEASE_REVISION_VERSION          1u

#define TCPIP_VENDOR_ID                           30u   /* Vector Informatik */
#define TCPIP_VINSTANCE_ID                         1u   /* 1=TcpIp, 2=IpV4, 3=IpV6, 4=DhcpV4Server */
#define TCPIP_MODULE_ID                          170u

/* TCPIP ApiIds */
/* ASR defined APIs */
#define TCPIP_API_ID_INIT                       0x01u  /* ASR4.2.1 value */
#define TCPIP_API_ID_GET_VERSION_INFO           0x02u  /* ASR4.2.1 value */
#define TCPIP_API_ID_GET_SOCKET                 0x03u  /* ASR4.2.1 value */
#define TCPIP_API_ID_CLOSE                      0x04u  /* ASR4.2.1 value */
#define TCPIP_API_ID_BIND                       0x05u  /* ASR4.2.1 value */
#define TCPIP_API_ID_TCP_CONNECT                0x06u  /* ASR4.2.1 value */
#define TCPIP_API_ID_TCP_LISTEN                 0x07u  /* ASR4.2.1 value */
#define TCPIP_API_ID_TCP_RECEIVED               0x08u  /* ASR4.2.1 value */
#define TCPIP_API_ID_TCP_REQUEST_COM_MODE       0x09u  /* ASR4.3.0 value */
#define TCPIP_API_ID_REQ_IP_ADDR_ASSIGN         0x0Au  /* ASR4.2.1 value */
#define TCPIP_API_ID_REL_IP_ADDR_ASSIGN         0x0Bu  /* ASR4.2.1 value */
#define TCPIP_API_ID_SET_DHCP_READ_OPT          0x0Du  /* ASR4.2.1 value */
#define TCPIP_API_ID_SET_DHCP_WRITE_OPT         0x0Eu  /* ASR4.2.1 value */
#define TCPIP_API_ID_CHANGE_PARAM               0x0Fu  /* ASR4.2.1 value */
#define TCPIP_API_ID_GET_PHYS_ADDR              0x11u  /* ASR4.2.1 value */
#define TCPIP_API_ID_UDP_TRANSMIT               0x12u  /* ASR4.2.1 value */
#define TCPIP_API_ID_TCP_TRANSMIT               0x13u  /* ASR4.2.1 value */
#define TCPIP_API_ID_RXINDICATION               0x14u  /* ASR4.2.1 value */
#define TCPIP_API_ID_MAIN_FUNCTION              0x15u  /* ASR4.2.1 value */
#define TCPIP_API_ID_GET_REMOTE_PHYS_ADDR       0x16u  /* ASR4.2.1 value */
#define TCPIP_API_ID_GET_CTRL_IDX               0x17u  /* ASR4.2.1 value */
#define TCPIP_API_ID_ICMPV6_TRANSMIT            0x18u  /* ASR4.3.0 value */
#define TCPIP_API_ID_SET_DHCP_V6_READ_OPT       0x19u  /* ASR4.2.1 value */
#define TCPIP_API_ID_SET_DHCP_V6_WRITE_OPT      0x1Au  /* ASR4.2.1 value */
#define TCPIP_API_ID_GET_NDP_CACHE_ENTRIES      0x1Cu  /* ASR4.3.0 value */
#define TCPIP_API_ID_GET_ARP_CACHE_ENTRIES      0x1Du  /* ASR4.3.0 value */
#define TCPIP_API_ID_GET_AND_RESET_MEAS_DATA    0x45u  /* ASR4.3.0 value */


/* Vector defined APIs */
#define TCPIP_API_ID_GET_LOC_NET_ADDR                   0x85u
#define TCPIP_API_ID_SET_CLIENT_CERT_INFO               0x88u
#define TCPIP_API_ID_GET_NVM_BLOCK_FOR_USED_ROOT_CERT   0x89u
#define TCPIP_API_ID_ROOT_CERT_WAS_MODIFIED             0x8Au
#define TCPIP_API_ID_CLEAR_AR_CACHE                     0x8Bu
#define TCPIP_API_ID_SEND_GRATUITOUS_ARP_REQ            0x8Cu
#define TCPIP_API_ID_IPSEC_ADD_SAENTRY_PAIR             0x8Du
#define TCPIP_API_ID_IPSEC_DEL_SAENTRY_PAIR             0x8Eu
#define TCPIP_API_ID_IPSEC_SPD_CALLOUT                  0x8Fu

/* stack internal APIs: */

#define TCPIP_API_ID_CBK_RX_INDICATION          0x90u
#define TCPIP_API_ID_CBK_TX_CONFIRMATION        0x91u
#define TCPIP_API_ID_CBK_TCP_ACCEPTED           0x92u
#define TCPIP_API_ID_CBK_TCP_CONNECTED          0x93u
#define TCPIP_API_ID_CBK_TCP_IP_EVENT           0x94u
#define TCPIP_API_ID_CBK_COPY_TX_DATA           0x95u

#define TCPIP_API_ID_RX_SOCK_IDENT              0x96u
#define TCPIP_API_ID_TRCV_LINK_STATE_CHG        0x9Au
#define TCPIP_API_ID_GET_IP_ADDR_CFG_SRC        0x9Fu
#define TCPIP_API_ID_GET_IP_ADDR                0xA0u
#define TCPIP_API_ID_GET_REM_NET_ADDR           0xA1u

/* Additional functions */
#define TCPIP_API_ID_GET_LOCAL_SOCK_ADDR        0xA9u
#define TCPIP_API_ID_DIAG_DATA_READ_ACCESS      0xAAu
#define TCPIP_API_ID_CBK_TLS_VALIDIATION_RESULT 0xABu
#define TCPIP_API_ID_GET_DHCP_TIMEOUT_INFO      0xACu

/* ------------------------------------------------------ */

/* TCPIP DET errors */
/* NEW ASR42x DET errors */
#define TCPIP_E_NO_ERROR       0x00u  /* No error occurred. */
#define TCPIP_E_NOTINIT        0x01u  /* API service called before initializing the module */
#define TCPIP_E_PARAM_POINTER  0x02u  /* API service called with NULL pointer */
#define TCPIP_E_INV_ARG        0x03u  /* API service called with invalid argument */
#define TCPIP_E_NOBUFS         0x04u  /* No buffer space available */
#define TCPIP_E_MSGSIZE        0x07u  /* Message too long */
#define TCPIP_E_PROTOTYPE      0x08u  /* Protocol wrong type for socket */
#define TCPIP_E_ADDRINUSE      0x09u  /* Address already in use */
#define TCPIP_E_ADDRNOTAVAIL   0x0Au  /* Can't assign requested address */
#define TCPIP_E_ISCONN         0x0Bu  /* Socket is already connected */
#define TCPIP_E_NOTCONN        0x0Cu  /* Socket is not connected */
#define TCPIP_E_NOPROTOOPT     0x0Du  /* Protocol not available */
#define TCPIP_E_AFNOSUPPORT    0x0Eu  /* Address family not supported by protocol family */
#define TCPIP_E_INIT_FAILED    0x0Fu  /* Invalid configuration set selection */

#define TCPIP_E_INV_SOCK_ID    0x20u  /* Vector Extension */ /* invalid socket index */
#define TCPIP_E_CBK_REQUIRED   0x21u  /* Callback function not configured but required due to socket owner runtime behavior.. */
#define TCPIP_E_NOT_SUPPORTED  0x22u  /* This operation is not supported */

/* TcpIp specific magic numbers: */
#define TCPIP_PROTOCOL_TCP                         6u
#define TCPIP_PROTOCOL_UDP                        17u
#define TCPIP_PROTOCOL_ICMP                        1u
#define TCPIP_PROTOCOL_ESP                        50u
#define TCPIP_PROTOCOL_AH                         51u
#define TCPIP_PROTOCOL_ANY                        255u  /* All protocols supported */

#define TCPIP_INADDR_BROADCAST            0xFFFFFFFFu
#define TCPIP_INADDR_ANY                  0x00000000u
#define TCPIP_PORT_ANY                        0x0000u

#define TCPIP_SOCK_ADDR_LEN_BYTE                (16u)

/* SOCK protocol */
#define TCPIP_SOCK_PROT_NONE                     (0u)
#define TCPIP_SOCK_PROT_UDP                     (17u)
#define TCPIP_SOCK_PROT_TCP                      (6u)

/* SOCKET states */
/* SOCKET states / state changes */
#define TCPIP_SOCK_STATES                        0x00u
#define TCPIP_SOCK_STATE_OK                      0x01u  /* connection established */
/* UDP states / state changes */
#define TCPIP_UDP_STATES                         0x10u
#define TCPIP_UDP_STATE_CONN_ESTAB               0x11u  /* connection established */
/* TCP states / state changes */
#define TCPIP_TCP_STATES                         0x20u
#define TCPIP_TCP_STATE_CONN_ESTAB               0x21u  /* connection established */
#define TCPIP_TCP_STATE_CONN_REQ_REC             0x22u  /* SYN received on listening socket */ /* Currently unused in this implementation. */
#define TCPIP_TCP_STATE_FIN_REC                  0x23u  /* FIN received */
#define TCPIP_TCP_STATE_RESET                    0x24u  /* Reset received or triggered */
#define TCPIP_TCP_STATE_CONN_REFUSED             0x25u  /* connection refused by peer */
#define TCPIP_TCP_STATE_CONN_CLOSING             0x26u  /* connection is about to close */ /* Currently used but never persisted in this implementation. */
#define TCPIP_TCP_STATE_CLOSED                   0x27u  /* connection is closed */
#define TCPIP_TCP_STATE_CONNECTED                0x28u  /* host connected to peer */
#define TCPIP_TCP_STATE_ACCEPTED                 0x29u  /* peer connected to host */ /* Currently unused in this implementation. */

/* Socket error codes (uint16 values) */
#define TCPIP_SOCK_ERR_00087     87u /* RFC: "error: xx", WinSock: WSA_INVALID_PARAMETER 87 - "One or more parameters are invalid" */
#define TCPIP_SOCK_ERR_10022  10022u /* RFC: "error: xx", WinSock: WSAEINVAL 10022 - "Invalid argument" */
#define TCPIP_SOCK_ERR_10035  10035u /* RFC: "error: xx", WinSock: WSAEWOULDBLOCK 10035 - "Resource temporarily unavailable" */
#define TCPIP_SOCK_ERR_10038  10038u /* RFC: "error: xx", WinSock: WSAENOTSOCK 10038 - "Socket operation on nonsocket" */
#define TCPIP_SOCK_ERR_10039  10039u /* RFC: "error: foreign socket unspecified", WinSock: WSAEDESTADDRREQ 10039 - "Destination address required" */
#define TCPIP_SOCK_ERR_10043  10043u /* RFC: "error: xx", WinSock: WSAEPROTONOSUPPORT 10043 - "Protocol not supported" */
#define TCPIP_SOCK_ERR_10044  10044u /* RFC: "error: xx", WinSock: WSAESOCKTNOSUPPORT 10044 - "Socket type not supported" */ /* e.g. RAW-Socket */
#define TCPIP_SOCK_ERR_10046  10046u /* RFC: "error: xx", WinSock: WSAEPFNOSUPPORT 10046 - "Protocol family not supported" */
#define TCPIP_SOCK_ERR_10047  10047u /* RFC: "error: xx", WinSock: WSAEAFNOSUPPORT 10047 - "Address family not supported by protocol family" */
#define TCPIP_SOCK_ERR_10048  10048u /* RFC: "error: xx", WinSock: WSAEADDRINUSE 10048 - "Address already in use" */
#define TCPIP_SOCK_ERR_10054  10054u /* RFC: "error: xx", WinSock: WSAECONNRESET 10054 - "Connection reset by peer" */
#define TCPIP_SOCK_ERR_10056  10056u /* RFC: "error: connection already exists", WinSock: WSAEISCONN 10056 - "Socket is already connected" */
#define TCPIP_SOCK_ERR_10057  10057u /* RFC: "error: xx", WinSock: WSAENOTCONN 10057 - "Socket is not connected" */
#define TCPIP_SOCK_ERR_10061  10061u /* RFC: "error: xx", WinSock: WSAECONNREFUSED 10061 - "Connection refused" */
#define TCPIP_SOCK_ERR_10101  10101u /* RFC: "error: connection closing", WinSock: WSAEDISCON 10101 - "Graceful shutdown in progress" */

#define TCPIP_SOCK_ERR_10013  10013u /* RFC: "error: xx", WinSock: WSAEACCES 10013 - "broadcast access not allowed" */
#define TCPIP_SOCK_ERR_10040  10040u /* RFC: "error: xx", WinSock: WSAEMSGSIZE 10040 - "Message too long" */

/* ------------------------------------------------------ */

/* TCPIP module state */
#define TCPIP_STATE_UNINIT                       0x00u
#define TCPIP_STATE_INIT                         0x01u

/* ------------------------------------------------------ */

#define TCPIP_INV_SOCK_HND                       (0xFF)

#define TCPIP_IP_PROT_VER_4                      0x04u
#define TCPIP_IP_PROT_VER_6                      0x06u

#define TCPIP_IPVX_ADDR_IDX_ANY                  0xFFu  /* ANY IP address id, either for IPv4 or IpV6 (IP local id)*/

/* DHCP Message Type defines */
#if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
# define TCPIP_DHCPV4_MSG_DISCOVER                  1U
# define TCPIP_DHCPV4_MSG_OFFER                     2U
# define TCPIP_DHCPV4_MSG_REQUEST                   3U
# define TCPIP_DHCPV4_MSG_DECLINE                   4U
# define TCPIP_DHCPV4_MSG_ACK                       5U
# define TCPIP_DHCPV4_MSG_NACK                      6U
# define TCPIP_DHCPV4_MSG_RELEASE                   7U
# define TCPIP_DHCPV4_MSG_INFORM                    8U
#  define TCPIP_DHCPV4_MSG_FLAG_ALWAYS             (0xFFu)
#endif

#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)                                                                                    /* COV_MSR_UNSUPPORTED */
# define TCPIP_DHCPV6_MSG_SOLICIT                   1U
# define TCPIP_DHCPV6_MSG_ADVERTISE                 2U
# define TCPIP_DHCPV6_MSG_REQUEST                   3U
# define TCPIP_DHCPV6_MSG_CONFIRM                   4U
# define TCPIP_DHCPV6_MSG_RENEW                     5U
# define TCPIP_DHCPV6_MSG_REBIND                    6U
# define TCPIP_DHCPV6_MSG_REPLY                     7U
# define TCPIP_DHCPV6_MSG_RELEASE                   8U
# define TCPIP_DHCPV6_MSG_DECLINE                   9U
# define TCPIP_DHCPV6_MSG_RECONFIGURE              10U
# define TCPIP_DHCPV6_MSG_INFORMATION_REQUEST      11U
# define TCPIP_DHCPV6_MSG_RELAY_FORWARD            12U
# define TCPIP_DHCPV6_MSG_RELAY_REPLY              13U
# if (TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON)
#  define TCPIP_DHCPV6_MSG_FLAG_SOLICIT             (1<<TCPIP_DHCPV6_MSG_SOLICIT)
#  define TCPIP_DHCPV6_MSG_FLAG_ADVERTISE           (1<<TCPIP_DHCPV6_MSG_ADVERTISE)
#  define TCPIP_DHCPV6_MSG_FLAG_REQUEST             (1<<TCPIP_DHCPV6_MSG_REQUEST)
#  define TCPIP_DHCPV6_MSG_FLAG_CONFIRM             (1<<TCPIP_DHCPV6_MSG_CONFIRM)
#  define TCPIP_DHCPV6_MSG_FLAG_RENEW               (1<<TCPIP_DHCPV6_MSG_RENEW)
#  define TCPIP_DHCPV6_MSG_FLAG_REBIND              (1<<TCPIP_DHCPV6_MSG_REBIND)
#  define TCPIP_DHCPV6_MSG_FLAG_REPLY               (1<<TCPIP_DHCPV6_MSG_REPLY)
#  define TCPIP_DHCPV6_MSG_FLAG_RELEASE             (1<<TCPIP_DHCPV6_MSG_RELEASE)
#  define TCPIP_DHCPV6_MSG_FLAG_DECLINE             (1<<TCPIP_DHCPV6_MSG_DECLINE)
#  define TCPIP_DHCPV6_MSG_FLAG_RECONFIGURE         (1<<TCPIP_DHCPV6_MSG_RECONFIGURE)
#  define TCPIP_DHCPV6_MSG_FLAG_INFORMATION_REQUEST (1<<TCPIP_DHCPV6_MSG_INFORMATION_REQUEST)
#  define TCPIP_DHCPV6_MSG_FLAG_RELAY_FORWARD       (1<<TCPIP_DHCPV6_MSG_RELAY_FORWARD)
#  define TCPIP_DHCPV6_MSG_FLAG_RELAY_REPLY         (1<<TCPIP_DHCPV6_MSG_RELAY_REPLY)
#  define TCPIP_DHCPV6_MSG_FLAG_ALLWAYS             (0xFFFFu)
# endif
#endif

/* Icmp Message type */
#if (TCPIP_SUPPORT_ICMPV4 == STD_ON)                                                                                    /* COV_TCPIP_ICMPV4_ALWAYS_ON */
# define TCPIP_IPV4_ICMP_TYPE_ECHO_REPLY            0U
# define TCPIP_IPV4_ICMP_TYPE_ECHO_REQ              8U
# define TCPIP_IPV4_ICMP_TYPE_RSVD                  255U
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define TCPIP_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(TcpIp_StateType, TCPIP_VAR_ZERO_INIT) TcpIp_State;

#define TCPIP_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  TcpIp_InitMemory()                                                                              (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief         Initializes the TcpIp-internal global module state variable.
 *  \details       Context is initialization of the ECU.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_InitMemory(void);

/**********************************************************************************************************************
 *  TcpIp_Init()
 *********************************************************************************************************************/
/*! \brief         Initializes the TcpIp module.
 *  \details       Calls all TcpIp internal init functions and sets state to 'initialized'.
 *                 Context is initialization of the ECU.
 *  \param[in]     ConfigPtr        Pointer to module configuration.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \trace         CREQ-111951
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Init(
  TCPIP_P2C(TcpIp_ConfigType) ConfigPtr);


/**********************************************************************************************************************
 *  TcpIp_GetSocketForUser()                                                                        (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Request allocation of a new socket (TCP or UDP).
 *  \details        Each accepted incoming TCP connection also allocates a socket resource. Server sockets are special,
 *                  because they do not need any rx and tx buffer and a lot less socket description parameters.
 *  \param[in]      Domain            Domain / address family that will be used with the socket.
 *                                    [TCPIP_AF_INET (IPv4) or TCPIP_AF_INET6 (IPv6)]
 *  \param[in]      Protocol          Transport layer protocol that will be used with the socket.
 *                                    [TCPIP_IPPROTO_TCP or TCPIP_IPPROTO_UDP]
 *  \param[out]     SocketIdPtr       Pointer to socket identifier representing the requested socket.
 *                                    This socket identifier must be provided for all further API calls which requires
 *                                    a SocketId. SocketIdPtr is only valid if return value is E_OK.
 *  \param[in]      SocketOwnerIdx    Index of a socket owner.
 *  \return         E_OK              The request has been accepted
 *  \return         E_NOT_OK          The request has not been accepted: no free socket
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketOwnerIdx.
 *  \synchronous    TRUE
 *  \trace          CREQ-115904
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetSocketForUser(
  TcpIp_DomainType                Domain,
  TcpIp_ProtocolType              Protocol,
  TCPIP_P2V(TcpIp_SocketIdType)   SocketIdPtr,
  TcpIp_SocketOwnerConfigIterType SocketOwnerIdx);

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TcpListen()
 *********************************************************************************************************************/
/*! \brief          Set TCP socket into listen mode.
 *  \details        Let TcpIp listen on the TCP socket specified by the socket identifier.
 *  \param[in]      SocketId           Socket identifier of the related local socket resource.
 *  \param[in]      MaxChannels        Maximum number of new parallel connections established on this listen connection.
 *  \return         E_OK               The request has been accepted.
 *  \return         E_NOT_OK           The request has not been accepted.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketId.
 *  \synchronous    FALSE
 *  \config         TCPIP_SUPPORT_TCP
 *  \trace          CREQ-115904
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpListen(
  TcpIp_SocketIdType SocketId,
  uint16             MaxChannels);

/**********************************************************************************************************************
 *  TcpIp_TcpConnect()
 *********************************************************************************************************************/
/*! \brief          Requests the establishment of a TCP connection to the configured peer.
 *  \details        -
 *  \param[in]      SocketId           Socket identifier of the related local socket resource.
 *  \param[in]      RemoteAddrPtr      Pointer to IP address and port of the remote host to connect to.
 *  \return         E_OK               Connect could be triggered.
 *  \return         E_NOT_OK           Connect could not be triggered.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketId.
 *  \synchronous    FALSE
 *  \config         TCPIP_SUPPORT_TCP
 *  \trace          CREQ-115904
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpConnect(
  TcpIp_SocketIdType            SocketId,
  TCPIP_P2C(TcpIp_SockAddrType) RemoteAddrPtr);

/**********************************************************************************************************************
 *  TcpIp_TcpTransmit()
 *********************************************************************************************************************/
/*! \brief          Requests the transmission of data to a remote node using TCP.
 *  \details        The transmission of the data is decoupled.
 *                  The TCP segment(s) are sent dependent on runtime factors (e.g. receive window) and configuration
 *                  parameters (e.g. Nagle algorithm).
 *  \param[in]      SocketId           socket index
 *  \param[in,out]  DataPtr            Pointer to a linear buffer of AvailableLength bytes containing the data to be
 *                                     transmitted. In case DataPtr is a NULL_PTR, TcpIp shall retrieve data from SoAd
 *                                     via callback SoAd_CopyTxData().
 *  \param[in]      AvailableLength    Available data for transmission in bytes
 *  \param[in]      ForceRetrieve      This parameter is only valid if DataPtr is a NULL_PTR. Indicates how the TCP/IP
 *                                     stack retrieves data from SoAd if DataPtr is a NULL_PTR.
 *                                     TRUE: the whole data indicated by availableLength shall be retrieved from the
 *                                     upper layer via one or multiple SoAd_CopyTxData() calls within the context of
 *                                     this transmit function.
 *                                     FALSE: TCP/IP stack may retrieve up to availableLength data from the upper layer.
 *                                     It is allowed to retrieve less than availableLength bytes.
 *                                     Note: Not retrieved data will be provided by SoAd with the next call to
 *                                     TcpIp_TcpTransmit (along with new data if available).
 *  \return         E_OK               The request has been accepted
 *  \return         E_NOT_OK           The request has not been accepted
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different SocketId.
 *  \synchronous    TRUE
 *  \config         TCPIP_SUPPORT_TCP
 *  \trace          CREQ-115955
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpTransmit(
  TcpIp_SocketIdType SocketId,
  TCPIP_P2V(uint8)   DataPtr,
  uint32             AvailableLength,
  boolean            ForceRetrieve);
#endif  /* (TCPIP_SUPPORT_TCP == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_UdpTransmit()
 *********************************************************************************************************************/
/*! \brief          Transmits a UDP message.
 *  \details        This service transmits data via UDP to a remote node. The transmission of the data is immediately
 *                  performed with this function call by forwarding it to EthIf.
 *  \param[in]      SocketId           socket index
 *  \param[in]      DataPtr            Pointer to a linear buffer of TotalLength bytes containing the data to be
 *                                     transmitted. In case DataPtr is a NULL_PTR, TcpIp shall retrieve data from
 *                                     SoAd via callback SoAd_CopyTxData().
 *  \param[in]      RemoteAddrPtr      Pointer to IP address and port of the remote host to transmit to.
 *  \param[in]      TotalLength        indicates the payload size of the UDP datagram.
 *  \return         E_OK               UDP message has been forwarded to EthIf for transmission.
 *  \return         E_NOT_OK           UDP message could not be sent because of a permanent error.
 *                                     (e.g. message is too long.)
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different SocketId.
 *  \synchronous    TRUE
 *  \trace          CREQ-115954
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_UdpTransmit(
  TcpIp_SocketIdType            SocketId,
  TCPIP_P2V(uint8)              DataPtr,
  TCPIP_P2V(TcpIp_SockAddrType) RemoteAddrPtr,
  uint16                        TotalLength);

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_IcmpV6Transmit()
 *********************************************************************************************************************/
/*! \brief         Send a raw ICMPv6 message of specified Type and Code.
 *  \details       -
 *  \param[in]     LocalIpAddrId    Local address identifier. (must reference an IPv6 address)
 *  \param[in]     RemoteAddrPtr    Pointer to Destination address. (must be an IPv6 address)
 *  \param[in]     HopLimit         HopLimit value of the outgoing IPv6 packet.
 *  \param[in]     Type             Value of the Type field in the ICMPv6 message header.
 *  \param[in]     Code             Value of the Code field in the ICMPv6 message header.
 *  \param[in]     DataLength       Length of the message payload. [bytes]
 *  \param[in]     DataPtr          Pointer to message payload.
 *  \return        E_OK             Message was transmitted.
 *  \return        E_NOT_OK         Message was not transmitted due to pending link-layer address resolution,
                                    occupied ethernet buffers or other error.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \trace         CREQ-115987
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_IcmpV6Transmit(
  TcpIp_LocalAddrIdType          LocalIpAddrId,
  TCPIP_P2C(TcpIp_SockAddrType)  RemoteAddrPtr,
  uint8                          HopLimit,
  uint8                          Type,
  uint8                          Code,
  uint16                         DataLength,
  TCPIP_P2C(uint8)               DataPtr);
#endif

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TcpReceived()
 *********************************************************************************************************************/
/*! \brief          Confirms the reception of socket data to the TCP/IP stack.
 *  \details        Increase the TCP receive window of the socket specified by SocketId considering the number of
 *                  finally consumed bytes specified by Length.
 *  \param[in]      SocketId              Socket identifier of the related local socket resource.
 *  \param[in]      Length                Number of bytes finally consumed by the upper layer.
 *  \return         E_OK                  The request has been accepted.
 *  \return         E_NOT_OK              The request has not been accepted.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different SocketId.
 *  \synchronous    TRUE
 *  \config         TCPIP_SUPPORT_TCP
 *  \trace          CREQ-115955
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpReceived(
  TcpIp_SocketIdType SocketId,
  uint32             Length);
#endif

/**********************************************************************************************************************
 *  TcpIp_Close()
 *********************************************************************************************************************/
/*! \brief          Requests to close the given socket connection and releases all related resources.
 *  \details        In case it is a TCP socket then the actions described at TcpIp_VCloseTcpSocket() are conducted.
 *                  In case it is a UDP socket then the actions are done directly here, i.e. without helper function.
 *  \param[in]      SocketId Socket handle identifying the local socket resource.
 *  \param[in]      Abort    TRUE: connection will immediately be terminated by sending a RST-Segment and releasing
 *                           all related resources.
 *                           FALSE: connection will be terminated after performing a regular connection termination
 *                           handshake and releasing all related resources.
 *  \return         E_OK     The request has been accepted.
 *  \return         E_NOT_OK The request has not been accepted.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketId.
 *  \synchronous    FALSE
 *  \trace          CREQ-115904
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Close(
  TcpIp_SocketIdType SocketId,
  boolean            Abort);

/**********************************************************************************************************************
 *  TcpIp_Bind()
 *********************************************************************************************************************/
/*! \brief          Binds a UDP or TCP socket to a local resource
 *  \details        Checks the validity of the given parameters and calls TcpIp_VBind() to do the actual binding.
 *  \param[in]      SocketId            Socket identifier of the related local socket resource.
 *  \param[in]      LocalAddrId         Identifier of an IP address representing the local IP address and EthIf
 *                                      controller to bind the socket to.
 *
 *                                      Note: to listen to all EthIf controller, TCPIP_LOCALADDRID_ANY
 *                                      has to be specified as LocalAddrId.
 *
 *                                      Note: to listen on any IP address of a EthIf controller, the
 *                                      configuration parameter TcpIpStaticIpAddress referenced by
 *                                      LocalAddrId must be set to 'ANY'. The remote IP address of an
 *                                      incoming packet has no effect then.
 *
 *                                      In case the socket shall be used as client socket, the IP address
 *                                      and EthIf controller represented by LocalAddrId is used for
 *                                      transmission.
 *
 *                                      Note: for an automatic selection of the Local IP address and EthIf
 *                                      Controller, TCPIP_LOCALADDRID_ANY has to be specified as
 *                                      LocalAddrId.
 *  \param[in,out]  PortPtr             Pointer to memory where the local port to which the socket shall
 *                                      be bound is specified. In case the parameter is specified as
 *                                      TCPIP_PORT_ANY, the TCP/IP stack shall choose the local port
 *                                      automatically from the range 49152 to 65535 and shall update the
 *                                      parameter to the chosen value.
 *  \return         E_OK                The request has been accepted
 *  \return         E_NOT_OK            The request has not been accepted (e.g. address in use)
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketId.
 *  \synchronous    TRUE
 *  \trace          CREQ-115904
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Bind(
  TcpIp_SocketIdType    SocketId,
  TcpIp_LocalAddrIdType LocalAddrId,
  TCPIP_P2V(uint16)     PortPtr);

/**********************************************************************************************************************
 *  TcpIp_RequestIpAddrAssignment()
 *********************************************************************************************************************/
/*! \brief          Initiates the local IP address assignment for the IP address specified by LocalAddrId.
 *  \details        -
 *  \param[in]      LocalAddrId         Identifier of IP address for which an assignment shall be initiated.
 *  \param[in]      Type                Type of IP address assignment which shall be initiated.
 *  \param[in]      LocalIpAddrPtr      Pointer to structure containing the IP address which shall be assigned to the
 *                                      EthIf controller indirectly specified via LocalAddrId.
 *                                      Note: Parameter is ignored (may be NULL_PTR) if Type is _not_ STATIC.
 *  \param[in]      Netmask             Network mask of IPv4 address or address prefix of IPv6 address in CIDR Notation.
 *                                      Note: Parameter is ignored if Type is _not_ STATIC.
 *                                      CONSTRAINT: [0..32] in case LocalAddrId refencres in IPv4 address.
 *                                                  [0..128] in case LocalAddrId refencres in IPv6 address.
 *  \param[in]      DefaultRouterPtr    Pointer to struct where the IP address of the default router
 *                                      (gateway) is stored (struct member 'port' is not used and of
 *                                      arbitrary value) (IPv4 only)
 *                                      Note: Parameter is ignored (may be NULL_PTR) if Type is not
 *                                      TCPIP_IPADDR_ASSIGNMENT_STATIC.
 *                                      If no default router shall be set this parameter may be NULL_PTR even in case
 *                                      Type is STATIC.
 *  \return         E_OK                The request has been accepted
 *  \return         E_NOT_OK            The request has not been accepted
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \trace          CREQ-111988
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_RequestIpAddrAssignment(
  TcpIp_LocalAddrIdType         LocalAddrId,
  TcpIp_IpAddrAssignmentType    Type,
  TCPIP_P2V(TcpIp_SockAddrType) LocalIpAddrPtr,
  uint8                         Netmask,
  TCPIP_P2V(TcpIp_SockAddrType) DefaultRouterPtr);

/**********************************************************************************************************************
 *  TcpIp_ReleaseIpAddrAssignment()
 *********************************************************************************************************************/
/*! \brief          Releases the local IP address assignment for the IP address specified by LocalAddrId.
 *  \details        -
 *  \param[in]      LocalAddrId         Identifier of an IP address for which an assignment shall be released.
 *  \return         E_OK                The request has been accepted.
 *  \return         E_NOT_OK            The request has not been accepted.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \trace          CREQ-111988
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_ReleaseIpAddrAssignment(
  TcpIp_LocalAddrIdType LocalAddrId);

/**********************************************************************************************************************
 *  TcpIp_ReleaseSpecificIpAddrAssignment()                                                         (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Releases the local IP address assignment of a specific type for an IP address.
 *  \details        This API is a Vector extension to the AUTOSAR API (TcpIp_ReleaseIpAddrAssignment).
 *  \param[in]      LocalAddrId         Identifier of an IP address for which the assignment shall be released.
 *  \param[in]      AssignmentType      Type of assignment that shall be released.
 *                                      (e.g.: STATIC, LINKLOCAL, DHCP, ROUTER)
 *  \return         E_OK                The assignment could be released.
 *  \return         E_NOT_OK            The assignment could not be released.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_ReleaseSpecificIpAddrAssignment (
  TcpIp_LocalAddrIdType      LocalAddrId,
  TcpIp_IpAddrAssignmentType AssignmentType);

/**********************************************************************************************************************
 *  TcpIp_GetPhysAddr()
 *********************************************************************************************************************/
/*! \brief          Obtains the physical source address used by the EthIf controller implicitly specified by LocalAddrId.
 *  \details        -
 *  \param[in]      LocalAddrId        Identifier of an IP address implicitly specifing the EthIf controller for which
 *                                     the physical address shall be obtained.
 *  \param[out]     PhysAddrPtr        Pointer to the memory where the physical source address (MAC address) in network
 *                                     byte order is stored
 *  \return         E_OK               The request was successful
 *  \return         E_NOT_OK           The request was not successful, e.g. no unique Ctrl specified via LocalAddrId.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-115906
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetPhysAddr(
  TcpIp_LocalAddrIdType LocalAddrId,
  TCPIP_P2V(uint8)      PhysAddrPtr);

/**********************************************************************************************************************
 *  TcpIp_GetRemotePhysAddr()
 *********************************************************************************************************************/
/*! \brief          Looks up the physical address for a remote network address.
 *  \details        Queries the IP/physical address translation table specified by CtrlIdx and
 *                  returns the physical address related to the IP address specified by IpAddrPtr. In case no physical
 *                  address can be retrieved and parameter initRes is TRUE, address resolution for the specified IP
 *                  address is initiated on the local network.
 *  \param[in]      CtrlIdx                EthIf controller index to identify the related ARP/NDP table.
 *  \param[in]      IpAddrPtr              Pointer to identifier of an IP address for which the physical address shall
 *                                         be retrieved.
 *  \param[out]     PhysAddrPtr            Pointer to the memory where the physical address (MAC address) related to the
 *                                         specified IP address is stored in network byte order.
 *  \param[in]      initRes                Specifies if the address resolution shall be initiated (TRUE) or not (FALSE)
 *                                         in case the physical address related to the specified IP address is currently
 *                                         unknown.
 *  \return         TCPIP_E_OK             Specified IP address resolved, physical address provided via PhysAddrPtr.
 *  \return         TCPIP_E_NOT_OK         Specified IP address could not be resolved.
 *                                         (e.g. Domain of IpAddrPtr is not supported)
 *  \return         TCPIP_E_PHYS_ADDR_MISS Physical address currently unknown.
 *                                         (address resolution initiated if initRes set to TRUE)
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different CtrlIdx.
 *  \synchronous    TRUE
 *  \trace          CREQ-115906
 *********************************************************************************************************************/
FUNC(TcpIp_ReturnType, TCPIP_CODE) TcpIp_GetRemotePhysAddr(
  uint8                         CtrlIdx,
  TCPIP_P2V(TcpIp_SockAddrType) IpAddrPtr,
  TCPIP_P2V(uint8)              PhysAddrPtr,
  boolean                       initRes);

/**********************************************************************************************************************
 *  TcpIp_GetArpCacheEntries()
 *********************************************************************************************************************/
/*! \brief          Copies physical address cache entries of the IpV4 instance, into the user defined buffer.
 *  \details        IpV4 instance has to be active on the given EthIf controller.
 *                  At first copies the static entries and then copies the dynamic entries into the user defined buffer.
 *  \param[in]      CtrlIdx             EthIf controller Index to identify the related ARP table.
 *  \param[in,out]  NumberOfElementsPtr Pointer to the maximum number of entries that can be stored.
 *  \param[out]     EntryListPtr        Pointer to the memory where the list of cache entries are stored.
 *  \return         E_OK                Physical address cache reading was successful.
 *  \return         E_NOT_OK            Unsuccessful (No IPV4 instance is active on this controller).
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different CtrlIdx.
 *  \synchronous    TRUE
 *  \trace          CREQ-115906
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetArpCacheEntries(
  uint8                              CtrlIdx,
  TCPIP_P2V(uint32)                  NumberOfElementsPtr,
  TCPIP_P2V(TcpIp_ArpCacheEntryType) EntryListPtr);

/**********************************************************************************************************************
 *  TcpIp_SendGratuitousArpReq()                                                                    (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Sends an gratuitous ARP request packet as specified in [RFC2002 4.6. second indentation].
 *  \details        -
 *  \param[in]      LocalAddrId  Local address identifier implicitly specifing the EthIf controller for which the
 *                               physical address shall be obtained.
 *  \return         E_OK         The request was successful.
 *  \return         E_NOT_OK     The request was not successful.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for LocalAddrId that reference different EthIf controllers.
 *  \synchronous    TRUE
 *  \trace          CREQ-119674
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_SendGratuitousArpReq(
  TcpIp_LocalAddrIdType LocalAddrId);

/**********************************************************************************************************************
 *  TcpIp_GetCtrlIdx()
 *********************************************************************************************************************/
/*! \brief          Returns the index of the EthIf controller related to LocalAddrId.
 *  \details        -
 *  \param[in]      LocalAddrId  Identifier of a local address that specifies the EthIf controller the index shall be
 *                               returned of.
 *  \param[out]     CtrlIdxPtr   Pointer to the memory where the index of the EthIf controller related to LocalAddrId
 *                               is stored.
 *  \return         E_OK         The request was successful.
 *  \return         E_NOT_OK     The request was not successful.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for LocalAddrId that reference different EthIf controllers.
 *  \synchronous    TRUE
 *  \trace          CREQ-111995
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetCtrlIdx(
  TcpIp_LocalAddrIdType LocalAddrId,
  TCPIP_P2V(uint8)      CtrlIdxPtr);

#ifdef TCPIP_DECLARE_OWN_MAINFUNCTION                                                                                   /* COV_TCPIP_COMPATIBILITY */
# if (TCPIP_SINGLE_MAIN_FUNCTION_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_MainFunction()
 *********************************************************************************************************************/
/*! \brief          Calls RX, State and TX MainFunctions of the module.
 *  \details        Wraps RX, TX and state specific MainFunctions of the module.
 *                  If this function is called, the specific RX, TX and State MainFunctions MUST NOT be called directly.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          SPEC-50950
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_MainFunction(void);

# else
/**********************************************************************************************************************
 *  TcpIp_MainFunctionRx()                                                                          (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Processes all received data and forwards information to upper layers.
 *  \details        In case this function is called, the TX and State MainFunctions HAVE TO BE called as well and
 +                  the MainFunction MUST NOT be called.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_MainFunctionRx(void);

/**********************************************************************************************************************
 *  TcpIp_MainFunctionTx()                                                                          (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Processes all pending transmit requests from the upper layers and transmits the data.
 *  \details        In case this function is called, the RX and State MainFunctions HAVE TO BE called as well and the
 *                  MainFunction MUST NOT be called.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_MainFunctionTx(void);

/**********************************************************************************************************************
 *  TcpIp_MainFunctionState()                                                                       (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Performs all state and timing specific actions.
 *  \details        If this function is called, the RX and TX MainFunctions HAVE TO BE called as well and
 *                  the MainFunction MUST not be called.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_MainFunctionState(void);
# endif
#endif

/**********************************************************************************************************************
 *  TcpIp_ChangeParameter()
 *********************************************************************************************************************/
/*! \brief          Changes the socket parameter configuration.
 *  \details        -
 *  \param[in]      SocketId              Identifier of a UDP or TCP socket.
 *  \param[in]      ParameterId           Identifier of the parameter that shall be changed.
 *  \param[in]      ParameterValue        Pointer to the value of the parameter.
 *                                        Note: Depending on ParameterId multiple bytes may be read from this location.
 *                                              If a multi-byte value is read it is interpreted in network byte order.
 *  \return         E_OK                  Parameter changed.
 *  \return         E_NOT_OK              Parameter change failed.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketId.
 *  \synchronous    TRUE
 *  \trace          CREQ-111994
 *  \note           Possible values for ParameterId are:
 *     value-----------------------------------+-size-----+-description-------------------------------------------------
 *     TCPIP_PARAMID_TCP_RXWND_MAX             | uint32   | Specifies the maximum TCP receive window for the socket.
 *     TCPIP_PARAMID_FRAMEPRIO                 | uint8    | Specifies the frame priority for outgoing frames on the socket.
 *     TCPIP_PARAMID_TCP_NAGLE                 | uint8    | Specifies if the Nagle Algorithm according to IETF RFC 896 is enabled or not.
 *     TCPIP_PARAMID_TCP_KEEPALIVE             | uint8    | Specifies if TCP Keep Alive Probes are sent on the socket connection. (default = false)
 *     TCPIP_PARAMID_TTL                       | uint8    | Specifies the time to live value for outgoing frames on the socket.
 *     TCPIP_PARAMID_TCP_KEEPALIVE_TIME        | uint32   | Specifies the time in [s] between the last data packet sent and the first keepalive probe. (0..INV, default = 7200)
 *     TCPIP_PARAMID_TCP_KEEPALIVE_PROBES_MAX  | uint16   | Specifies the maximum number of times that a keepalive probe is retransmitted. (0..65535)
 *     TCPIP_PARAMID_TCP_KEEPALIVE_INTERVAL    | uint32   | Specifies the interval in [s] between subsequent keepalive probes. (0..INV)
 *     TCPIP_PARAMID_V_TCP_UTOUPDATE           | uint16   | new value for user timerout
 *     TCPIP_PARAMID_V_TCP_UTOENABLED          | BOOL     | enable usage of user timerout option
 *     TCPIP_PARAMID_V_TCP_UTOCHANGEABLE       | BOOL     | allow change of user timerout by received option
 *     TCPIP_PARAMID_V_TCP_TXBUFSIZE           | uint32   | Specifies the TCP tx buffer size (to choose the matching buffer)
 *     TCPIP_PARAMID_V_IPV4_TYPE_OF_SERVICE    | uint8    | specify the 'type of service' value used for sending IPv4 messages
 *     TCPIP_PARAMID_V_IPV6_FLOW_LABEL         | uint32   | specify the 'flow label' value used for sending IPv6 messages
 *     TCPIP_PARAMID_V_IPV6_TRAFFIC_CLASS      | uint8    | specify the 'traffic class' value used for sending IPv6 messages
 *     TCPIP_PARAMID_V_UDP_TXREQLISTSIZE       | uint8    | choose the desired TxRequestList size
 *     TCPIP_PARAMID_V_UDP_TXRETRYLISTSIZE     | uint8    | set the number of Eth tx buffers used in case of PhysAddrMiss
 *     TCPIP_PARAMID_V_PHYS_DEST_ADDR          | uint8[6] | set physical destination address for outgoing packets (override ARP).
 *     TCPIP_PARAMID_V_USE_TLS                 | uint8    | Enable / disable the usage of TLS for the (TCP) socket
 *     TCPIP_PARAMID_V_TLS_TXBUFSIZE           | uint32   | Specifies the TLS tx buffer size
 *     TCPIP_PARAMID_V_TLS_RXBUFSIZE           | uint32   | Specifies the TLS rx buffer size
 *     TCPIP_PARAMID_V_TLS_SELECT_OCSP_REQEST  | uint8    | select OCSP requests for the connection
 *     TCPIP_PARAMID_V_TLS_HEARTBEAT_MODE      | uint8    | select heartbeat mode for the connection
 *     TCPIP_PARAMID_V_TLS_HEARTBEAT_PERIOD_S  | uint32   | specify heartbeat period for the connection
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_ChangeParameter(
  TcpIp_SocketIdType SocketId,
  TcpIp_ParamIdType  ParameterId,
  TCPIP_P2V(uint8)   ParameterValue);

#if (TCPIP_SUPPORT_TLS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_Tls_SetClientCertInfo()                                                                   (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Sets the client certificate and key block IDs for a TLS connection.
 *  \details        calling this function is necessary for client authentication.
 *  \param[in]      SocketId       Identifier of a TCP socket.
 *  \param[in]      CertPtr        Pointer to client certificate. (RAM block)
 *  \param[in]      KeyPtr         Pointer to client private key. (RAM block)
 *  \param[in]      CertLen        Length of client certificate.
 *  \param[in]      KeyLen         Length of client private key.
 *  \return         E_OK           Certificate info could be set.
 *  \return         E_NOT_OK       Certificate info could NOT be set.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketId.
 *  \synchronous    TRUE
 *  \config         TCPIP_SUPPORT_TLS
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_SetClientCertInfo(
  TcpIp_SocketIdType SocketId,
  TCPIP_P2V(uint8)   CertPtr,
  TCPIP_P2V(uint8)   KeyPtr,
  uint16             CertLen,
  uint16             KeyLen);

/**********************************************************************************************************************
 *  TcpIp_Tls_GetNvmBlockIdForUsedRootCert()                                                        (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Gets the NVM block ID of the root certificate used for a TLS connection.
 *  \details        -
 *  \param[in]      SocketId              Identifier of a TCP socket.
 *  \param[out]     RootCertBlockIdPtr    Pointer to the block ID.
 *  \return         E_OK                  Block ID provided.
 *  \return         E_NOT_OK              Request has failed.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketId.
 *  \synchronous    TRUE
 *  \config         TCPIP_SUPPORT_TLS
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_GetNvmBlockIdForUsedRootCert(
  TcpIp_SocketIdType         SocketId,
  TCPIP_P2V(NvM_BlockIdType) RootCertBlockIdPtr);

/**********************************************************************************************************************
 *  TcpIp_Tls_RootCertWasModified()                                                                 (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Informs the TLS that a root certificate has been updated in NVM.
 *  \details        -
 *  \param[in]      NvmBlockId            BlockId of the NVM block that has changed.
 *  \return         E_OK                  Block is used as a root certificate.
 *  \return         E_NOT_OK              Request failed, block is not used as a root certificate.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different NvmBlockId.
 *  \synchronous    TRUE
 *  \config         TCPIP_SUPPORT_TLS
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_RootCertWasModified(
  NvM_BlockIdType NvmBlockId );
#endif  /* (TCPIP_SUPPORT_TLS == STD_ON) */

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
/**********************************************************************************************************************
 *  TcpIp_GetLocNetAddr()                                                                       ( D E P R E C A T E D )
 *********************************************************************************************************************/
/*! \brief          Returns the current IP address for a given controller.
 *  \details        -
 *  \param[in]      LocalAddrId           Identifier of a local address.
 *  \param[out]     NetAddrPtr            Pointer to memory where the local network address is stored.
 *  \return         E_OK                  Local network address returned.
 *  \return         E_NOT_OK              Local network address access failed.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         TCPIP_SUPPORT_IPV4
 *  \note           This API is deprecated and will be removed in future releases.
 *                  Use TcpIp_GetIpAddr() APIs instead.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetLocNetAddr(
  TcpIp_LocalAddrIdType        LocalAddrId,
  TCPIP_P2V(TcpIp_NetAddrType) NetAddrPtr);

/**********************************************************************************************************************
 *  TcpIp_GetLocNetMask()                                                                       ( D E P R E C A T E D )
 *********************************************************************************************************************/
/*! \brief          Returns the current network mask for a given controller.
 *  \details        -
 *  \param[in]      LocalAddrId           Identifier of a local address.
 *  \param[out]     NetMaskPtr            Pointer to memory where the local network mask is stored.
 *  \return         E_OK                  Local network mask returned.
 *  \return         E_NOT_OK              Local network mask access failed.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         TCPIP_SUPPORT_IPV4
 *  \note           This API is deprecated and will be removed in future releases.
 *                  Use TcpIp_GetIpAddr() APIs instead.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetLocNetMask(
  TcpIp_LocalAddrIdType        LocalAddrId,
  TCPIP_P2V(TcpIp_NetAddrType) NetMaskPtr);
#endif

/**********************************************************************************************************************
 *  TcpIp_GetIpAddr()
 *********************************************************************************************************************/
/*! \brief          Obtains the local IP address actually used by LocalAddrId, the netmask and default router
 *  \details        -
 *  \param[in]      LocalAddrId           Identifier of a local address.
 *  \param[out]     IpAddrPtr             Pointer to a struct where the IP address is stored.
 *                                        (only struct members family and address will be updated)
 *                                        CONSTRAINT: [Destination structure must be >= sizeof(TcpIp_SockAddrInet6Type)
 *                                                     if TCPIP_SUPPORT_IPV6 is STD_ON and
 *                                                     >= sizeof(TcpIp_SockAddrInetType) otherwise.]
 *                                        May be NULL_PTR if IP address value is not required.
 *  \param[out]     NetmaskPtr            Pointer to memory where Network mask of IPv4 address or address prefix of IPv6
 *                                        address in CIDR notation is stored.
 *                                        May be NULL_PTR if netmask value is not required.
 *  \param[out]     DefaultRouterPtr      Pointer to struct where the IP address of the default router (gateway) is
 *                                        stored. (only struct members family and address will be updated)
 *                                        CONSTRAINT: [Destination structure must be >= sizeof(TcpIp_SockAddrInet6Type)
 *                                                     if TCPIP_SUPPORT_IPV6 is STD_ON and
 *                                                     >= sizeof(TcpIp_SockAddrInetType) otherwise.]
 *                                        May be NULL_PTR if default router address value is not required.
 *  \return         E_OK                  The request was successful.
 *  \return         E_NOT_OK              The request was not successful.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-111995
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetIpAddr(
  TcpIp_LocalAddrIdType         LocalAddrId,
  TCPIP_P2V(TcpIp_SockAddrType) IpAddrPtr,
  TCPIP_P2V(uint8)              NetmaskPtr,
  TCPIP_P2V(TcpIp_SockAddrType) DefaultRouterPtr);

/**********************************************************************************************************************
 *  TcpIp_GetRemNetAddr()                                                                           (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Provides the remote IP address and port of an established TCP socket connection.
 *  \details        SockAddrPtr is a pointer to a TcpIp memory area where the remote address is stored.
 *                  The pointer is valid until the socket is closed.
 *  \param[in]      SocketId              Handle of a TCP or UDP socket.
 *  \param[out]     SockAddrPtr           Pointer to a socket address element.
 *  \return         E_OK                  Reading the IP address and port was successful
 *  \return         E_NOT_OK              Remote IP address and port could not be obtained.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-115994
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetRemNetAddr(
  TcpIp_SocketIdType             SocketId,
  TCPIP_P2V(TcpIp_SockAddrType) *SockAddrPtr);

#if (TCPIP_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief          Returns the TcpIp version as decimal coded value.
 *  \details        -
 *  \param[in]      versioninfo           Pointer to version information struct.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         TCPIP_VERSION_INFO_API
 *  \trace          CREQ-111952
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_GetVersionInfo(TCPIP_P2V(Std_VersionInfoType) versioninfo);
#endif

#if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpReadOption()
 *********************************************************************************************************************/
/*! \brief          Reads user option data for configured DHCPv4 user options.
 *  \details        Retrieves DHCP option data identified by parameter option for DHCP options.
 *  \param[in]      LocalIpAddrId Identifier of a local address representing the local IP address and EthIf
 *                                controller for which the DHCP option shall be read.
 *                                CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddrV4()-1]
 *  \param[in]      Option        DHCP option, e.g. Host Name.
 *  \param[in,out]  DataLength    In: Pointer to length of buffer referenced by DataPtr. [bytes]
 *                                Out: Pointer to length of the read option. (less or equal to input value)
 *  \param[out]     DataPtr       Pointer to buffer where the option data shall be written to.
 *  \return         E_OK          DHCP option data retrieved successfully.
 *  \return         E_NOT_OK      DHCP option data could not be retrieved.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for LocalAddrId that reference different EthIf controllers.
 *  \synchronous    TRUE
 *  \config         TCPIP_SUPPORT_DHCPV4 and TCPIP_SUPPORT_DHCPV4_OPTIONS and TCPIP_DHCPV4_TX_OPTION_CNT > 0.
 *  \trace          CREQ-111990
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpReadOption(
  TcpIp_LocalAddrIdType LocalIpAddrId,
  uint8                 Option,
  TCPIP_P2V(uint8)      DataLength,
  TCPIP_P2V(uint8)      DataPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpWriteOption()
 *********************************************************************************************************************/
/*! \brief          Sets or clears configured DHCPv4 user option data.
 *  \details        Invoking with 0 data length will clear the option data.
 *                  User options configured as RX and RX_REQUESTED can only be cleared.
 *  \param[in]      LocalIpAddrId Identifier of a local address representing the local IP address and EthIf
 *                                controller for which the DHCP option shall be written.
 *                                CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddrV4()-1]
 *  \param[in]      Option        DHCP option, e.g. Host Name.
 *  \param[in]      DataLength    Length of DHCP option data.
 *  \param[in]      DataPtr       Pointer to memory containing DHCP option data.
 *  \return         E_OK          DHCP option was written successfully.
 *  \return         E_NOT_OK      DHCP option data could not be written.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for LocalAddrId that reference different EthIf controllers.
 *  \synchronous    TRUE
 *  \config         TCPIP_SUPPORT_DHCPV4 and TCPIP_SUPPORT_DHCPV4_OPTIONS and TCPIP_DHCPV4_TX_OPTION_CNT > 0.
 *  \trace          CREQ-111990
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpWriteOption(
  TcpIp_LocalAddrIdType LocalIpAddrId,
  uint8                 Option,
  uint8                 DataLength,
  TCPIP_P2C(uint8)      DataPtr);
#endif  /* TCPIP_SUPPORT_DHCPV4 == STD_ON */

#if (TCPIP_SUPPORT_DHCPV6 == STD_ON)                                                                                    /* COV_MSR_UNSUPPORTED */
# if (TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6ReadOption()
 *********************************************************************************************************************/
/*! \brief          Reads user option data for configured DHCPv6 user options.
 *  \details        Retrieves DHCP option data identified by parameter option for DHCP options.
 *  \param[in]      LocalIpAddrId Identifier of a local address representing the local IP address and EthIf
 *                                controller for which the DHCP option shall be read.
 *                                CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddrV6()-1]
 *  \param[in]      Option        DHCP option, e.g. Host Name.
 *  \param[in]      DataLength    Length of DHCP option data.
 *  \param[in,out]  DataPtr       In: Pointer to length of buffer referenced by DataPtr. [bytes]
 *                                Out: Pointer to length of the read option. (less or equal to input value)
 *  \return         E_OK          DHCP option data retrieved successfully.
 *  \return         E_NOT_OK      DHCP option data could not be retrieved.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for LocalAddrId that reference different EthIf controllers.
 *  \synchronous    TRUE
 *  \config         TCPIP_SUPPORT_DHCPV6 and TCPIP_SUPPORT_DHCPV6_OPTIONS
 *  \trace          CREQ-111990
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6ReadOption(
  TcpIp_LocalAddrIdType LocalIpAddrId,
  uint16                Option,
  TCPIP_P2V(uint16)     DataLength,
  TCPIP_P2V(uint8)      DataPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6WriteOption()
 *********************************************************************************************************************/
/*! \brief          Sets or clears configured DHCPv6 user option data.
 *  \details        Invoking with 0 data length will clear the option data.
 *                  User options configured as RX and RX_REQUESTED can only be cleared.
 *  \param[in]      LocalIpAddrId Identifier of a local address representing the local IP address and EthIf
 *                                controller for which the DHCPv6 option shall be written.
 *                                CONSTRAINT: [0..TcpIp_GetSizeOfLocalAddrV6()-1]
 *  \param[in]      Option        DHCP option, e.g. Host Name.
 *  \param[in]      DataLength    Length of DHCP option data. A value of 0 will clear the requested option data
 *  \param[in]      DataPtr       Pointer to memory containing DHCP option data.
 *  \return         E_OK          No error occured
 *  \return         E_NOT_OK      DHCP option data could not be written.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for LocalAddrId that reference different EthIf controllers.
 *  \synchronous    TRUE
 *  \config         TCPIP_SUPPORT_DHCPV6 and TCPIP_SUPPORT_DHCPV6_OPTIONS
 *  \trace          CREQ-111990
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6WriteOption(
  TcpIp_LocalAddrIdType LocalIpAddrId,
  uint16                Option,
  uint16                DataLength,
  TCPIP_P2C(uint8)      DataPtr);
# endif
#endif /* TCPIP_SUPPORT_DHCPV6 == STD_ON */

/**********************************************************************************************************************
 *  TcpIp_GetDhcpTimeoutInfo()                                                                      (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Checks whether a "DHCP address finding timeout" has occurred.
 *  \details        -
 *  \param[in]      EthIfCtrlIdx          Index of an EthIf controller.
 *  \param[in]      IpVer                 IP version.
 *  \return         TRUE                  There was a DHCP timeout.
 *  \return         FALSE                 There was no DHCP timeout.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-115958
 *********************************************************************************************************************/
FUNC(boolean, TCPIP_CODE) TcpIp_GetDhcpTimeoutInfo(
  uint8 EthIfCtrlIdx,
  uint8 IpVer);

/**********************************************************************************************************************
 *  TcpIp_GetIpAddrCfgSrc()                                                                         (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Returns the configuration source of an IP address.
 *  \details        -
 *  \param[in]      LocalAddrId           Identifier of a local IP address.
 *  \param[out]     CfgSrcPtr             Configuration source of the address.
 *  \return         E_OK                  Address is valid and *CfgSrcPtr has been set.
 *  \return         E_NOT_OK              Address invalid or not assigned to this node. *CfgSrcPtr not modified.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-111995
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetIpAddrCfgSrc(
  TcpIp_LocalAddrIdType LocalAddrId,
  TCPIP_P2V(uint8)      CfgSrcPtr);

/**********************************************************************************************************************
 *  TcpIp_RequestComMode()                                                                                       (Stub)
 *********************************************************************************************************************/
/*! \brief          Changes the TcpIp state of the communication network identified by EthIf controller index.
 *  \details        This functions is currently only a dummy function and does not perform any action.
 *  \param[in]      CtrlIdx               EthIf controller index to identify the communication network the TcpIp state
 *                                        is requested of.
 *  \param[in]      State                 Requested TcpIp state.
 *  \return         E_OK                  Request was accepted. (Returned if parameters are valid)
 *  \return         E_NOT_OK              Request was not accepted.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different CtrlIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_RequestComMode(
  uint8            CtrlIdx,
  TcpIp_StateType  State);

/**********************************************************************************************************************
 *  TcpIp_GetLocSockAddr()                                                                          (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Reads the local socket address of the given socket.
 *  \details        Vector extension.
 *  \param[in]      SocketId              Identifier of a UDP or TCP socket.
 *  \param[out]     SockPtr               Pointer were the local socket address shall be written to.
 *  \return         E_OK                  Socket address was successfully written.
 *  \return         E_NOT_OK              Error, socket address is not updated.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-115994
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetLocSockAddr(
  TcpIp_SocketIdType            SocketId,
  TCPIP_P2V(TcpIp_SockAddrType) SockPtr);

#if (TCPIP_SUPPORT_DIAG_ACCESS_EXTENSIONS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DiagDataReadAccess()                                                                      (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Reads miscellaneous TcpIp-related diagnostic data.
 *  \details        The memory fragment DataPtr points to should be aligned properly regarding the expected returned
 *                  type / struct. Data is only written if RetValue is E_OK.
 *                  This is a Vector extension.
 *  \param[in]      SocketId       Identifier of a UDP or TCP socket.
 *  \param[in]      DataID         Data identifier.
 *  \param[out]     DataPtr        Pointer for diagnostic data.
 *  \param[in,out]  DataLenPtr     Pointer for maximum / actual length of diagnostic data in bytes.
 *  \return         E_OK           Diagnostic data written.
 *  \return         E_NOT_OK       Invalid parameter. (data identifier not found, NULL_PTR parameter, invalid length)
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         TCPIP_SUPPORT_DIAG_ACCESS_EXTENSIONS
 *  \trace          CREQ-115994
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DiagDataReadAccess(
  TcpIp_SocketIdType   SocketId,
  TcpIp_DiagParamsType DataID,
  TCPIP_P2V(uint8)     DataPtr,
  TCPIP_P2V(uint16)    DataLenPtr);
#endif

/**********************************************************************************************************************
 *  TcpIp_ClearARCache()                                                                            (Vector Informatik)
 *********************************************************************************************************************/
/*! \brief          Clears the address resolution cache.
 *  \details        -
 *  \param[in]      LocalAddrId         Identifier of a local address implicitly specifing the IPv4/IPv6 controller that
 *                                      shall be cleared.
 *  \return         E_OK                The request was successful.
 *  \return         E_NOT_OK            The request was not successful.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for LocalAddrId that reference different EthIf controllers.
 *  \synchronous    TRUE
 *  \trace          CREQ-126879
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_ClearARCache(
  TcpIp_LocalAddrIdType LocalAddrId);

/**********************************************************************************************************************
 *  TcpIp_GetNdpCacheEntries()
 *********************************************************************************************************************/
/*! \brief          Returns entries that are currently stored in the IPv6 link layer address resolution cache.
 *  \details        Copies entries from the physical address cache of the IPv6 instance that is active on the EthIf
 *                  controller specified by ctrlIdx into a user provided buffer. The function will copy all or
 *                  NumberOfElementsPtr into the output list. If input value of NumberOfElementsPtr is 0 the function
 *                  will not copy any data but only return the number of valid entries in the cache.
 *                  EntryListPtr may be NULL_PTR in this case.
 *  \param[in]      CtrlIdx             Index of an EthIf controller to identify the related NDP table.
 *  \param[in,out]  NumberOfElementsPtr In: Pointer to maximum number of entries that can be stored at EntryListPtr.
 *                                      Out: Pointer to number of entries written to EntryListPtr.
 *                                      (Number of all entries in the cache if input value is 0).
 *  \param[out]     EntryListPtr        Pointer to memory where the list of cache entries shall be stored.
                                        May only be NULL_PTR if *NumberOfElementsPtr is 0.
 *  \return         E_OK                Physical address cache could be read.
 *  \return         E_NOT_OK            Physical address cache could not be read.
 *                                      (i.e. no IPv6 instance active on this controller)
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different CtrlIdx.
 *  \synchronous    TRUE
 *  \trace          CREQ-115906
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetNdpCacheEntries(
  uint8                              CtrlIdx,
  TCPIP_P2V(uint32)                  NumberOfElementsPtr,
  TCPIP_P2V(TcpIp_NdpCacheEntryType) EntryListPtr);

/**********************************************************************************************************************
 * TcpIp_IpSecSaEntryPairAdd()
 *********************************************************************************************************************/
/*! \brief          Adds a pair of  SA Entries
 *  \details        -
 *  \param[in]      LocalAddrId       Local Ip Address Id
 *  \param[in]      SaInfoPtr         Security association information struct
 *                                    Remote address is expected to be in Nbo
 *                                    All port numbers are expected to be in Hbo
 *                                    CONSTRAINT: [SMI-540960]
 *  \return         E_OK              A pair of SA entries has been added successfully for given SaInfo
 *                                    A valid Csm job pair has been allocated for the Sa entry pair
 *  \return         E_NOT_OK          No SA entry has been added. No Csm job allocated
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
*********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_IpSecSaEntryPairAdd(
  TcpIp_LocalAddrIdType             LocalAddrId,
  TCPIP_P2C(TcpIp_IpSecSaInfoType)  SaInfoPtr);

/**********************************************************************************************************************
 * TcpIp_IpSecSaEntryPairDelete()
 *********************************************************************************************************************/
/*! \brief          Delete the pair of inbound and outbound SA referred by the Spi
 *  \details        The matching SA and its outbound pair is removed.
 *  \param[in]      InboundSpi   SPI of the inbound SA.
 *                               CONSTRAINT: must not be 0
 *  \return         E_OK         SA Entry Pair has been deleted successfully
 *  \return         E_NOT_OK     SA Entry Pair could not be deleted
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
*********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_IpSecSaEntryPairDelete(
  uint32                       InboundSpi);

#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_GetAndResetMeasurementData()
 *********************************************************************************************************************/
/*! \brief          Read the corresponding measurement data counter and optionally reset it.
 *  \details        Measurement index TCPIP_MEAS_ALL may be used to reset all measurement data.
 *                  If IPsec is enabled, the indices TCPIP_MEAS_VENDOR_SPECIFIC_NR_SA_PAIRS
 *                  and TCPIP_MEAS_VENDOR_SPECIFIC_SA_PAIRS can be used to obtain SA entry pair statuses
 *  \param[in]      MeasurementIdx         Index of a measurement data.
 *                                         CONSTRAINT: [SMI-540959] if TCPIP_MEAS_VENDOR_SPECIFIC_SA_PAIRS
 *  \param[in]      MeasurementResetNeeded Flag for the measurement data to reset.
 *                                         TRUE  - Reset the measurement data.
 *                                         FALSE - Do not reset.
 *                                         CONSTRAINT: This flag is ignored if TCPIP_MEAS_VENDOR_SPECIFIC_NR_SA_PAIRS
 *                                         or TCPIP_MEAS_VENDOR_SPECIFIC_SA_PAIRS is passed
 *  \param[out]     MeasurementDataPtr     Returns the value of the measurement data count.
 *                                         CONSTRAINT: [May be NULL_PTR in combination with
 *                                                      MeasurementResetNeeded == TRUE.]
 *  \return         E_OK                   Measurement data is read and optionally reset successfully.
 *  \return         E_NOT_OK               Read or Reset is not sucessfull.
 *  \pre            Before the Api is called for TCPIP_MEAS_VENDOR_SPECIFIC_SA_PAIRS, the
 *                  Api MUST be called for TCPIP_MEAS_VENDOR_SPECIFIC_NR_SA_PAIRS
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_GetAndResetMeasurementData(
  TcpIp_MeasurementIdxType  MeasurementIdx,
  boolean                   MeasurementResetNeeded,
  TCPIP_P2V(uint32)         MeasurementDataPtr);
#endif

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif
/* TCPIP_H */

/*!
 * \exclusivearea TCPIP_EXCLUSIVE_AREA_0
 *                Ensures consistency of all runtime data of the TcpIp that cannot be accessed atomically and that is
 *                modified in TcpIp_MainFunction or TcpIp_*Transmit context.
 * \protects      All runtime data of the TcpIp that have non atomic data types.
 * \usedin        TcpIp_MainFunction()
 *                TcpIp_TcpTransmit() / TcpIp_TcpTransmitInternal()
 *                TcpIp_UdpTransmit() / TcpIp_UdpTransmitInternalVerify()
 *
 * \exclude       All functions provided by TcpIp.
 * \length        MEDIUM This exclusive area protects very short code blocks as well as some code block of medium
 *                length (e.g.: iteration over the TCP retry queue).
 * \endexclusivearea
 */

/**********************************************************************************************************************
 *  END OF FILE: TcpIp.h
 *********************************************************************************************************************/
