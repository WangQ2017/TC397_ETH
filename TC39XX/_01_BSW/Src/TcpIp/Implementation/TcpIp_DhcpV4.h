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
 *         \file  TcpIp_DhcpV4.h
 *        \brief  Implementation of Dynamic Host Configuration Protocol for IPv4 - Client (DHCPv4 Client)
 *
 *      \details  This file is part of the TcpIp IPv4 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv4 submodule. >> TcpIp_IpV4.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/

#if !defined (TCPIP_DHCPV4_H)
# define TCPIP_DHCPV4_H

#include "TcpIp_Cfg.h"

#if (TCPIP_SUPPORT_DHCPV4 == STD_ON)

/*
--- LIMITAIONS OF THIS IMPLEMENTATION ------------------------------------------
- According to the RFC 2131, the DHCP client SHOULD probe its address (received from a DHCP  server)
  before using it for IP module configuration. This implementation does not implement this  feature.
  This feature also is not implemented in standard MS-Windows environments, and it would increase
  runtime and memory consumption.
- The RFC 2131 specifies the different states a DHCP client runs through. This implementation won't
  implement the states INIT_REBOOT and REBOOTING. These states only make sense if a real-time-clock
  is available to decide if an old lease (received before the last reboot of the system) is still
  valid. Only in this case it would make sense to try to renew the old (but still valid) lease.
*/

/*
- RFC 2131: DHCP
  RFC 1533: DHCP Options

|0              |8              |16             |24             |
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|     op (1)    |   htype (1)   |   hlen (1)    |   hops (1)    |
+---------------+---------------+---------------+---------------+
|                            xid (4)                            |
+-------------------------------+-------------------------------+
|           secs (2)            |           flags (2)           |
+-------------------------------+-------------------------------+
|                          ciaddr (4)                           |
+---------------------------------------------------------------+
|                          yiaddr (4)                           |
+---------------------------------------------------------------+
|                          siaddr (4)                           |
+---------------------------------------------------------------+
|                          giaddr (4)                           |
+---------------------------------------------------------------+
|                                                               |
|                          chaddr (16)                          |
|                                                               |
|                                                               |
+---------------------------------------------------------------+
|                                                               |
|                          sname (64)                           |
|                                                               |
+---------------------------------------------------------------+
|                                                               |
|                          file (128)                           |
|                                                               |
+---------------------------------------------------------------+
|                          options (variable)                   |
+---------------------------------------------------------------+
Format of a DHCP message
*/

/*
FIELD      OCTETS       DESCRIPTION
-----      ------       -----------
op           1   Message op code / message type.
                 1 = BOOTREQUEST, 2 = BOOTREPLY
htype        1   Hardware address type, see ARP section in "Assigned
                 Numbers" RFC; e.g., '1' = 10mb ethernet.
hlen         1   Hardware address length (e.g. '6' for 10mb
                 ethernet).
hops         1   Client sets to zero, optionally used by relay agents
                 when booting via a relay agent.
xid          4   Transaction ID, a random number chosen by the
                 client, used by the client and server to associate
                 messages and responses between a client and a
                 server.
secs         2   Filled in by client, seconds elapsed since client
                 began address acquisition or renewal process.
flags        2   Flags
ciaddr       4   Client IP address; only filled in if client is in
                 BOUND, RENEW or REBINDING state and can respond
                 to ARP requests.
yiaddr       4   'your' (client) IP address.
siaddr       4   IP address of next server to use in bootstrap;
                 returned in DHCPOFFER, DHCPACK by server.
giaddr       4   Relay agent IP address, used in booting via a
                 relay agent.
chaddr      16   Client hardware address.
sname       64   Optional server host name, null terminated string.
file       128   Boot file name, null terminated string; "generic"
                 name or null in DHCPDISCOVER, fully qualified
                 directory-path name in DHCPOFFER.
options    var   Optional parameters field. See the options
                 documents for a list of defined options.
*/
/*
Flags (16 bit)
                     1 1 1 1 1 1
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|B|             MBZ             |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
B:   BROADCAST flag
MBZ: MUST BE ZERO (reserved for future use)

*/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "TcpIp.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* DHCP ApiIds */
#define TCPIP_DHCPV4_API_ID_INIT                        0xB0u
#define TCPIP_DHCPV4_API_ID_MAIN_FUNCTION               0xB1u
#define TCPIP_DHCPV4_API_ID_TX_CONFIRMATION             0xB2u
#define TCPIP_DHCPV4_API_ID_RX_INDICATION               0xB3u
#define TCPIP_DHCPV4_API_ID_IP_LINK_STATE_CHANGE        0xB4u
#define TCPIP_DHCPV4_API_ID_TRIGGER_ADDR_REQU           0xB5u
#define TCPIP_DHCPV4_API_ID_STOP_ADDR_REQU              0xB6u
#define TCPIP_DHCPV4_API_ID_RESET                       0xB7u
#define TCPIP_DHCPV4_API_ID_SET_HOST_NAME               0xB8u
#define TCPIP_DHCPV4_API_ID_V_SEND_DHCP_MSG             0xBBu
#define TCPIP_DHCPV4_API_ID_GET_STATUS                  0xBCu
#define TCPIP_DHCPV4_API_ID_SET_USER_OPTION          0xBDu
#define TCPIP_DHCPV4_API_ID_GET_USER_OPTION          0xBEu

/* DHCP specific DET errors */
/* none */

/* DHCP states per controller */
#define TCPIP_DHCPV4_OFFLINE                    0x0u
#define TCPIP_DHCPV4_ONLINE_PASSIVE             0x1u
#define TCPIP_DHCPV4_ONLINE_ACTIVE              0x2u
#define TCPIP_DHCPV4_OFFLINE_FAILURE            0x3u

#define TCPIP_DHCPV4_MIN_HEADER_LENGTH_BYTE    (240u)  /* DHCP header length + magic pattern, without options */


/* BIGENDIAN */
#define TCPIP_DHCPV4_MAGIC_PATTERN              0x63825363u



#define TCPIP_DHCPV4_FLAGS_BROADCAST    0x8000u
#define TCPIP_DHCPV4_FLAGS_NONE         0x0000u
#define TCPIP_DHCPV4_OPT_IDX_INVALID    TcpIp_GetSizeOfDhcpUserOption()
#define TCPIP_DHCPV4_DHCPINVALIDMSG     0u
#define TCPIP_DHCPV4_DHCPDISCOVER       TCPIP_DHCPV4_MSG_DISCOVER /* client */
#define TCPIP_DHCPV4_DHCPOFFER          TCPIP_DHCPV4_MSG_OFFER    /* server */
#define TCPIP_DHCPV4_DHCPREQUEST        TCPIP_DHCPV4_MSG_REQUEST  /* client */
#define TCPIP_DHCPV4_DHCPDECLINE        TCPIP_DHCPV4_MSG_DECLINE  /* client */
#define TCPIP_DHCPV4_DHCPACK            TCPIP_DHCPV4_MSG_ACK      /* server */
#define TCPIP_DHCPV4_DHCPNACK           TCPIP_DHCPV4_MSG_NACK     /* server */
#define TCPIP_DHCPV4_DHCPRELEASE        TCPIP_DHCPV4_MSG_RELEASE  /* client */
#define TCPIP_DHCPV4_DHCPINFORM         TCPIP_DHCPV4_MSG_INFORM   /* client */

#define TCPIP_DHCPV4_CTRL_STATE_OFF          0u
#define TCPIP_DHCPV4_CTRL_STATE_INIT         1u
#define TCPIP_DHCPV4_CTRL_STATE_SELECTING    2u
#define TCPIP_DHCPV4_CTRL_STATE_REQUESTING   3u
#define TCPIP_DHCPV4_CTRL_STATE_BOUND        4u  /* Address Lease valid. */
#define TCPIP_DHCPV4_CTRL_STATE_RENEWING     5u  /* Address Lease valid. */
#define TCPIP_DHCPV4_CTRL_STATE_REBINDING    6u  /* Address Lease valid. */
#define TCPIP_DHCPV4_CTRL_STATE_INITREBOOT   7u  /* mode not supported by this DHCP impl. */
#define TCPIP_DHCPV4_CTRL_STATE_REBOOTING    8u  /* mode not supported by this DHCP impl. */


/* Length of Dhcpv4 Message sections */
#define TCPIP_DHCPV4_MSG_LEN_OP                1U
#define TCPIP_DHCPV4_MSG_LEN_HTYPE             1U
#define TCPIP_DHCPV4_MSG_LEN_HLEN              1U
#define TCPIP_DHCPV4_MSG_LEN_HOPS              1U
#define TCPIP_DHCPV4_MSG_LEN_XID               4U
#define TCPIP_DHCPV4_MSG_LEN_SECS              2U
#define TCPIP_DHCPV4_MSG_LEN_FLAGS             2U
#define TCPIP_DHCPV4_MSG_LEN_CIADDR            4U
#define TCPIP_DHCPV4_MSG_LEN_YIADDR            4U
#define TCPIP_DHCPV4_MSG_LEN_SIADDR            4U
#define TCPIP_DHCPV4_MSG_LEN_GIAADR            4U
#define TCPIP_DHCPV4_MSG_LEN_CHADDR           16U
#define TCPIP_DHCPV4_MSG_LEN_SNAME            64U
#define TCPIP_DHCPV4_MSG_LEN_BOOTFILE        128U
#define TCPIP_DHCPV4_MSG_LEN_MAGIC_COOKIE      4U


/*  DHCPV4 frame Offsets */
#define TCPIP_DHCPV4_FRAME_OPCODE_OFS             0u
#define TCPIP_DHCPV4_FRAME_HWADDR_TYPE_OFS        (TCPIP_DHCPV4_FRAME_OPCODE_OFS + TCPIP_DHCPV4_MSG_LEN_OP)             /* 1 */
#define TCPIP_DHCPV4_FRAME_HWADDR_LEN_OFS         (TCPIP_DHCPV4_FRAME_HWADDR_TYPE_OFS + TCPIP_DHCPV4_MSG_LEN_HTYPE)     /* 2 */
#define TCPIP_DHCPV4_FRAME_HOPS_OFS               (TCPIP_DHCPV4_FRAME_HWADDR_LEN_OFS + TCPIP_DHCPV4_MSG_LEN_HLEN)       /* 3 */
#define TCPIP_DHCPV4_FRAME_XID_OFS                (TCPIP_DHCPV4_FRAME_HOPS_OFS + TCPIP_DHCPV4_MSG_LEN_HOPS)             /* 4 */
#define TCPIP_DHCPV4_FRAME_SECS_OFS               (TCPIP_DHCPV4_FRAME_XID_OFS + TCPIP_DHCPV4_MSG_LEN_XID)               /* 8 */
#define TCPIP_DHCPV4_FRAME_FLAGS_OFS              (TCPIP_DHCPV4_FRAME_SECS_OFS + TCPIP_DHCPV4_MSG_LEN_SECS)             /* 10 */
#define TCPIP_DHCPV4_FRAME_CIADDR_OFS             (TCPIP_DHCPV4_FRAME_FLAGS_OFS + TCPIP_DHCPV4_MSG_LEN_FLAGS)           /* 12 */
#define TCPIP_DHCPV4_FRAME_YIADDR_OFS             (TCPIP_DHCPV4_FRAME_CIADDR_OFS + TCPIP_DHCPV4_MSG_LEN_CIADDR)         /* 16 */
#define TCPIP_DHCPV4_FRAME_SIADDR_OFS             (TCPIP_DHCPV4_FRAME_YIADDR_OFS + TCPIP_DHCPV4_MSG_LEN_YIADDR)         /* 20 */
#define TCPIP_DHCPV4_FRAME_GIADDR_OFS             (TCPIP_DHCPV4_FRAME_SIADDR_OFS + TCPIP_DHCPV4_MSG_LEN_SIADDR)         /* 24 */
#define TCPIP_DHCPV4_FRAME_CLIENT_HW_ADDR_OFS     (TCPIP_DHCPV4_FRAME_GIADDR_OFS + TCPIP_DHCPV4_MSG_LEN_GIAADR)         /* 28 */
#define TCPIP_DHCPV4_FRAME_SERVER_HOSTNAME_OFS    (TCPIP_DHCPV4_FRAME_CLIENT_HW_ADDR_OFS + TCPIP_DHCPV4_MSG_LEN_CHADDR) /* 44 */
#define TCPIP_DHCPV4_FRAME_BOOT_FILE_OFS          (TCPIP_DHCPV4_FRAME_SERVER_HOSTNAME_OFS + TCPIP_DHCPV4_MSG_LEN_SNAME) /* 108 */
#define TCPIP_DHCPV4_FRAME_MAGICPATTERN_OFS       (TCPIP_DHCPV4_FRAME_BOOT_FILE_OFS + TCPIP_DHCPV4_MSG_LEN_BOOTFILE)    /* 236 */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint8  TcpIp_DhcpV4_GlobStateType;  /* global state */

typedef struct
{
  uint8  Op;                  /* op code: 1 = BOOTREQUEST, 2 = BOOTREPLY */
  uint8  Htype;               /* Hardware address type; e.g., '1' = 10mb ethernet */
  uint8  Hlen;                /* Hardware address length */
  uint8  Hops;
  uint32 Xid;                 /* Transaction ID */
  uint16 Secs;
  uint16 Flags;
  TcpIp_NetAddrType Ciaddr;   /* Client IP address */
  TcpIp_NetAddrType Yiaddr;   /* Your (client) IP address */
  TcpIp_NetAddrType Siaddr;   /* Server IP address */
  TcpIp_NetAddrType Giaddr;   /* GW (Relay agent) IP address */
  uint8  Chaddr[16];          /* Client hardware address */
  uint8  Sname[64];           /* Server host name (string)(optional) */
  uint8  File[128];           /* Boot file name */
  uint32 MagicPattern;
} TcpIp_DhcpV4_FrameType;

typedef void TcpIp_DhcpV4_ConfigType;

typedef struct
{
  TCPIP_P2C(IpBase_AddrInType) DnsServerAddrPtr;
  uint8                        DnsServerAddrCount;
} TcpIp_DhcpV4_DnsOptInfoType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  TcpIp_DhcpV4_Init
 *********************************************************************************************************************/
/*! \brief       Initializes the DHCPV4 component.
 *  \details     -
 *  \pre         TcpIp_VInitSockets()
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
extern FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_Init( void );

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_MainFunction
 *********************************************************************************************************************/
/*! \brief        Handles the DHCP global status
 *  \details      -
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \note         This function is called every TCPIP_MAIN_FCT_PERIOD_MSEC ms
 *********************************************************************************************************************/
extern FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_MainFunction(void);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_TriggerAddrRequest
 *********************************************************************************************************************/
/*! \brief        This function starts the address request process
 *  \details      -
 *  \param[in]    IpV4CtrlIdx        Ip Instance index.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                   CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                  1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                  2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
extern FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_TriggerAddrRequest(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_StopAddrRequest
 *********************************************************************************************************************/
/*! \brief        Stop the (ongoing) address request process
 *  \details      -
 *  \param[in]    IpV4CtrlIdx          controller index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
extern FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_StopAddrRequest(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_Reset
 *********************************************************************************************************************/
/*! \brief        Reset the controller.
 *  \details      -
 *  \param[in]    IpV4CtrlIdx          controller index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
extern FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_Reset(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_SetHostName
 *********************************************************************************************************************/
/*! \brief        Set DHCP host name
 *  \details      -
 *  \param[in]    IpV4CtrlIdx           Controller index
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    DataPtr               pointer to host name
 *  \param[in]    DataLen               Host name length in bytes
 *  \return       E_OK                  Host name set
 *  \return       E_NOT_OK              Setting host name failed
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_SetHostName(
  TcpIp_SizeOfIpV4CtrlType                   IpV4CtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint8                                      DataLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_GetDhcpTimeoutInfo
 *********************************************************************************************************************/
/*! \brief        Check if a DHCP address finding timeout occurred
 *  \details      -
 *  \param[in]    IpV4CtrlIdx           Controller index
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \return       TRUE                  There was a DHCP timeout
 *  \return       FALSE                 There was no DHCP timeout
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
extern FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV4_GetDhcpTimeoutInfo(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_GetActiveAddress
 *********************************************************************************************************************/
/*! \brief        Checks if the DHCP has an active IP address lease and returns the address if so.
 *  \details      -
 *  \param[in]    IpV4CtrlIdx   IP controller index.
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                              CONSTRAINT: [DHCP address assignment must be configured for the given Ip Controller]
 *  \param[out]   AddrInfoPtr   Active lease parameters: IP address, Netmask, Default router.
 *  \return       TRUE          DHCP has a valid IP address lease *addrInfoPtr data valid.
 *  \return       FALSE         DHCP does not have a valid IP address lease. (*addrInfoPtr unchanged).
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for diffrent controllers
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV4_GetActiveAddress(
  TcpIp_LocalAddrV4IterType                             IpV4CtrlIdx,
  P2VAR(IpV4_IpAddrSetType, AUTOMATIC, TCPIP_APPL_DATA) AddrInfoPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VGetTxOption
 *********************************************************************************************************************/
/*! \brief          Get user option data from incoming DHCPv4 messages.
 *  \details        By this API service the TCP/IP stack reads the DHCP option data identified by parameter option.
 *  \param[in]      LocalAddrV4Idx IP address identifier representing the local IP address and EthIf controller for which
 *                                 the DHCP option shall be read.
 *                                 CONSTRAINT [0..TcpIp_GetSizeOfLocalAddrV4()-1]
 *  \param[in]      OptCode        DHCP option, e.g. Host Name
 *  \param[in,out]  OptLenPtr      length of DHCP option data
 *  \param[out]     OptPtr         Pointer to memory containing DHCP option data
 *  \return         E_OK           no error occured.
 *  \return         E_NOT_OK       DHCP option data could not be read.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE

 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VGetTxOption(
  TcpIp_LocalAddrV4IterType                LocalAddrV4Idx,
  uint8                                    OptCode,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptLenPtr,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSetTxOption
 *********************************************************************************************************************/
/*! \brief      Set user option data for outgoing DHCPv4 messages.
 *  \details    By this API service the TCP/IP stack writes the DHCP option data identified by parameter option.
 *  \param[in]  LocalAddrV4Idx IP address identifier representing the local IP address and EthIf controller for which
 *                             the DHCP option shall be written.
 *                             CONSTRAINT [0..TcpIp_GetSizeOfLocalAddrV4()-1]
 *  \param[in]  OptCode        DHCP option, e.g. Host Name
 *  \param[in]  OptLen         length of DHCP option data
 *  \param[in]  OptPtr         Pointer to memory containing DHCP option data
 *  \param[in]  MsgTypes       Define for which DHCP message types the option shall be sent
 *  \return     E_OK           no error occured.
 *  \return     E_NOT_OK       DHCP option data could not be written.
 *  \pre        -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \note       Currently only the option 'TCPIP_DHCPV4_OPT_ID_CLIENT_FQDN' is supported.

 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VSetTxOption(
  TcpIp_LocalAddrV4IterType                  LocalAddrV4Idx,
  uint8                                      OptCode,
  uint8                                      OptLen,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptPtr,
  uint8                                      MsgTypes);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_GetStatus
 *********************************************************************************************************************/
/*! \brief Returns the current DCHP state of a given IP address that is configured for DHCP address assignment.
 *  \details      A state that is equivalent to TCPIP_DHCP_SIMPLIFIED_STATE_OFFER_RCVD_WITHOUT_REQ is not supported by this DHCP impl.
 *                because any unrequested message does not influence the DHCP ctrl. state.
 *  \param[in]    LocalAddrId   Identifies the internal Ip address for which the current DHCP status shall be retrieved.
 *  \param[out]   DhcpStatePtr      Current state of DCHP client for the requested interface:
 *                Type uint8, Range:
 *                0x00= DHCP client not active,                                   TCPIP_DHCP_SIMPLIFIED_STATE_NOT_ACTIVE
 *                0x01= no discover sent,                                         TCPIP_DHCP_SIMPLIFIED_STATE_NO_DISCVR_SENT
 *                0x02= discover sent but no answer received,                     TCPIP_DHCP_SIMPLIFIED_STATE_DISCVR_SENT_NO_ANSWR_RCVD_YET
 *                0x03= DHCP offer received, no request sent,                     TCPIP_DHCP_SIMPLIFIED_STATE_OFFER_RCVD_WITHOUT_REQ
 *                0x04= DHCP request sent, no ACK received,                       TCPIP_DHCP_SIMPLIFIED_STATE_REQ_SENT_NO_ACK_RCVD_YET
 *                0x05= ACK received, DHCP address assigned to current interface, TCPIP_DHCP_SIMPLIFIED_STATE_ACK_RCVD_DHCP_ADDR_ASSIGND
 *                all other internal states shall result in an invalid notification (return E_NOT_OK)
 *  \return       E_OK in case the parameters were valid and thus the DHCP status could be retrieved.
 *  \pre          -
 *  \context      TASK | ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_GetStatus(
  TcpIp_LocalAddrIdType                        LocalAddrId,
  CONSTP2VAR(uint8, AUTOMATIC, IPV4_APPL_DATA) DhcpStatePtr);

#define TCPIP_DHCP_SIMPLIFIED_STATE_NOT_ACTIVE                    0x00
#define TCPIP_DHCP_SIMPLIFIED_STATE_NO_DISCVR_SENT                0x01
#define TCPIP_DHCP_SIMPLIFIED_STATE_DISCVR_SENT_NO_ANSWR_RCVD_YET 0x02
#define TCPIP_DHCP_SIMPLIFIED_STATE_OFFER_RCVD_WITHOUT_REQ        0x03
#define TCPIP_DHCP_SIMPLIFIED_STATE_REQ_SENT_NO_ACK_RCVD_YET      0x04
#define TCPIP_DHCP_SIMPLIFIED_STATE_ACK_RCVD_DHCP_ADDR_ASSIGND    0x05

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* (TCPIP_SUPPORT_IPV4 == STD_ON) */
#endif  /* TCPIP_DHCPV4_H */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_Dhcp.h
 *********************************************************************************************************************/
