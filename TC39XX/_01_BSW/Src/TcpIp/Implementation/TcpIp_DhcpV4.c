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
 *         \file  TcpIp_DhcpV4.c
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


/* PRQA S 0828 EOF */ /* MD_MSR_1.1 */

#define TCPIP_DHCPV4_SOURCE
#include "TcpIp_Cfg.h"



#if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIp_Lcfg.h"
#include "TcpIp_DhcpV4.h"
#include "TcpIp_DhcpV4_Cbk.h"
#include "TcpIp_Priv.h"
#include "TcpIp_Udp.h"

#include "TcpIp_IpV4.h"
#include "IpBase.h"
#include "IpBase_Types.h"
#include "IpBase_Copy.h"
#include "EthIf.h"

#if (TCPIP_SUPPORT_DNS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
# include "Dns.h"
#endif


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined (STATIC)                                                                                                   /* COV_TCPIP_COMPATIBILITY */
# define STATIC static
#endif

#define TCPIP_DHCPV4_TX_BUFFER_MIN_SIZE_BYTE  260u  /* size without "DHCP host name" */

#define TCPIP_DHCPV4_HW_TYPE_ETH            1u
#define TCPIP_DHCPV4_HW_LEN_ETH             6u

#define TCPIP_DHCPV4_OP_BOOTREQUEST         1u
#define TCPIP_DHCPV4_OP_BOOTREPLY           2u
#define TCPIP_DHCPV4_SERVER_PORT            67u
#define TCPIP_DHCPV4_CLIENT_PORT            68u
#define TCPIP_DHCPV4_EVENT_INVALID          255u

/* DHCP OPTIONS */
#define TCPIP_DHCPV4_OPTION_HDR_BYTE                    2u
#define TCPIP_DHCPV4_OPT_PAD_TYPE                       0u
#define TCPIP_DHCPV4_OPT_END_TYPE                     255u
#define TCPIP_DHCPV4_PARAM_SUBNET_ROUTER_DOMAIN_BYTE    3u

#define TCPIP_DHCPV4_OPT_SUBNET_MASK_TYPE               1u /* client subnet mask */
#define TCPIP_DHCPV4_OPT_ROUTER_TYPE                    3u /* Router = Default Gateway */
#define TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_TYPE        6u
#define TCPIP_DHCPV4_OPT_HOST_NAME_TYPE                12u
#define TCPIP_DHCPV4_OPT_REQ_IP_ADDR_TYPE              50u
#define TCPIP_DHCPV4_OPT_IP_ADDR_LEASE_TIME_TYPE       51u
#define TCPIP_DHCPV4_OPT_OVERLOAD_TYPE                 52u
#define TCPIP_DHCPV4_OPT_DHCPV4_MSG_TYPE               53u
#define TCPIP_DHCPV4_OPT_SERVER_ID_TYPE                54u /* IP address of DHCP server */
#define TCPIP_DHCPV4_OPT_PARAM_REQ_LIST_TYPE           55u /* requested DHCP options */
#define TCPIP_DHCPV4_OPT_MSG_TYPE                      56u /* text (e.g. error) message */
#define TCPIP_DHCPV4_OPT_MAX_DHCPV4_MSG_SIZE_TYPE      57u
#define TCPIP_DHCPV4_OPT_RENEWAL_TIME_T1_VAL_TYPE      58u
#define TCPIP_DHCPV4_OPT_REBINDING_TIME_T2_VAL_TYPE    59u
#define TCPIP_DHCPV4_OPT_ID_CLIENT_FQDN                81u

#define TCPIP_DHCPV4_OPT_SUBNET_MASK_LEN                4U
#define TCPIP_DHCPV4_OPT_ROUTER_LEN                     4U /* n times */
#define TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_LEN         4U  /* n times */
#define TCPIP_DHCPV4_OPT_REQ_IP_ADDR_LEN                4U
#define TCPIP_DHCPV4_OPT_IP_ADDR_LEASE_TIME_LEN         4U
#define TCPIP_DHCPV4_OPT_OVERLOAD_LEN                   1U
#define TCPIP_DHCPV4_OPT_DHCPV4_MSG_LEN                 1U
#define TCPIP_DHCPV4_OPT_SERVER_ID_LEN                  4U
#define TCPIP_DHCPV4_OPT_PARAM_REQ_LIST_ID_LEN          1U  /* min size */
#define TCPIP_DHCPV4_OPT_MSG_LEN                        1U  /* min size */
#define TCPIP_DHCPV4_OPT_MAX_DHCPV4_MSG_SIZE_LEN        2U
#define TCPIP_DHCPV4_OPT_RENEWAL_TIME_T1_VAL_LEN        4U
#define TCPIP_DHCPV4_OPT_REBINDING_TIME_T2_VAL_LEN      4U

/* User option header offsets */
#define TCPIP_DHCPV4_USER_OPT_CODE_OFS                  0U
#define TCPIP_DHCPV4_USER_OPT_LEN_OFS                   1U
#define TCPIP_DHCPV4_USER_OPT_DATA_OFS                  2U



/* FQDN Option field offset */
#define TCPIP_DHCPV4_OPT_FQDN_CODE                      0U
#define TCPIP_DHCPV4_OPT_FQDN_LEN                       1U
#define TCPIP_DHCPV4_OPT_FQDN_FLAGS                     2U
#define TCPIP_DHCPV4_OPT_FQDN_RCODE1                    3U
#define TCPIP_DHCPV4_OPT_FQDN_RCODE2                    4U
#define TCPIP_DHCPV4_OPT_FQDN_DOMAIN_NAME_LEN           5U
#define TCPIP_DHCPV4_OPT_FQDN_DOMAIN_NAME               6U

/* FQDN option length((except Domain name data)*/
#define TCPIP_DHCPV4_OPT_FQDN_CODE_RC1_RC2_DNLEN        4U

/* Dhcp Option Format */
#define TCPIP_DHCPV4_OPTION_FIELD_OFS_CODE              0U
#define TCPIP_DHCPV4_OPTION_FIELD_OFS_LEN               1U
#define TCPIP_DHCPV4_OPTION_FIELD_OFS_TYPE              2U
#define TCPIP_DHCPV4_OPTION_HEADER  (  TCPIP_DHCPV4_OPTION_FIELD_OFS_CODE \
                                     + TCPIP_DHCPV4_OPTION_FIELD_OFS_LEN  \
                                     + TCPIP_DHCPV4_OPTION_FIELD_OFS_TYPE)

#define TCPIP_DHCPV4_SECOND                             1u

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_GetDhcpMsgLength
 *********************************************************************************************************************/
/*! \brief           Update Dhcp Message Length.
 *  \details         -
 *  \param[in]       MsgType         Indicates which type of message contains received frame
 *  \param[in,out]   DhcpMsgLenPtr   Pointer to Message length.
 *  \param[in]       DhcpStatusIdx   Indicates Status index for a given Ip controller.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_GetDhcpMsgLength(
  uint8                                             MsgType,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_DATA)         DhcpMsgLenPtr,
  TcpIp_SizeOfDhcpStatusType                        DhcpStatusIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSetMsgFlags
 *********************************************************************************************************************/
/*! \brief           Update Message Flag.
 *  \details         -
 *  \param[in]       MsgType         Indicates which type of message contains received frame
 *  \param[in]       DhcpStatusIdx   Indicates Status index for a given Ip controller.
 * \param[in,out]    OptOfsPtr       Pointer to Option offset.
 *  \param[in]       OptPtr          Pointer to the message options.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VSetMsgFlags(
  uint8                                     MsgType,
  TcpIp_SizeOfDhcpStatusType                DhcpStatusIdx,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_DATA) OptOfsPtr,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)  OptPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VUpdateStatus
 *********************************************************************************************************************/
/*! \brief           Update DhcpState pointer.
 *  \details         Returns the current DCHP state of a given IP address that is configured for DHCP address assignment
 *  \param[in]       LocalAddrIdx    Local Ip Address Index.
 *  \param[in,out]   ErrorIdPtr      Pointer to the error Id.
 *  \param[out]      DhcpStatePtr    Pointer to Dhcp States.
 *  \return          E_OK            DhcpState  pointer is updated successfully.
 *  \return          E_NOT_OK        Ip instance is not active
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VUpdateStatus(
  TcpIp_SizeOfLocalAddrType                     LocalAddrIdx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)      ErrorIdPtr,
  CONSTP2VAR(uint8, AUTOMATIC, IPV4_APPL_DATA)  DhcpStatePtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VProcessCtrlState
 *********************************************************************************************************************/
/*! \brief           Starts DhcpV4 state transition process
 *  \details         -
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                   CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                   1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                   2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VProcessCtrlState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSelectingState
 *********************************************************************************************************************/
/*! \brief           Retransmit DHCPDISCOVER message.
 *  \details         This function transmists discover messages until timout has ocuured.
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                   CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                  1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                  2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VSelectingState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_RenewingState
 *********************************************************************************************************************/
/*! \brief           Transmit DHCPREQUEST (unicast).
 *  \details         This schedules the next transmission after first DHCPRequest has been sent.
 *                   After that it changes to rebinding state for the further processing.
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                   CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_RenewingState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_RebindingState
 *********************************************************************************************************************/
/*! \brief           Transmit DHCPREQUEST (broadcast).
 *  \details         This function transmits DHCPREQUEST (broadcast) and schedule next retransmission or
 *                   cancel DHCP assignment if number of retransmission has been reached.
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                   CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                 1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                 2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_RebindingState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_ProcessAckOrNak
 *********************************************************************************************************************/
/*! \brief           Process incoming acknowledge or refuse server messages.
 *  \details         Process Acks and Nacks messages received from server.
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                   CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                  1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                  2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \param[in]       Yiaddr          Client's Ip Address.
 *  \param[in]       MsgType         Indicates which type of message contains received frame
 *  \param[in]       LocConfigData   Pointer to the local configuration data.
 *  \param[in]       DnsServerOptPtr DNS server information contained in received message.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_ProcessAckOrNak(
  TcpIp_IpV4CtrlIterType                                           IpV4CtrlIdx,
  TcpIp_NetAddrType                                                Yiaddr,
  uint8                                                            MsgType,
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2CONST(TcpIp_DhcpV4_DnsOptInfoType, AUTOMATIC, TCPIP_APPL_DATA) DnsServerOptPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_ProcessOptions
 *********************************************************************************************************************/
/*! \brief           Navigate to the right option and update the relevant information.
 *  \details         -
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                   CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                  1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                  2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \param[in]       OptPtr          Pointer to the option field of received message.
 *  \param[out]      MsgTypePtr      Indicates which type of message contains received frame.
 *  \param[in]       LocConfigData   Pointer to the local configuration data.
 *  \param[out]      DnsServerOptPtr Position of the DNS server information in received message.
 *                                   If no valid DNS server option was found the member 'DnsServerAddrCount' is set to 0.
 *  \return          E_OK            If Option length is correct.
 *  \return          E_NOT_OK        If option length is not valid
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_ProcessOptions(
  TcpIp_IpV4CtrlIterType                                         IpV4CtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                     OptPtr,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       MsgTypePtr,
  P2VAR(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2VAR(TcpIp_DhcpV4_DnsOptInfoType, AUTOMATIC, TCPIP_APPL_DATA) DnsServerOptPtr);

/**********************************************************************************************************************
*  TcpIp_DhcpV4_VHandleRxUserOptions
*********************************************************************************************************************/
/*! \brief           Navigate to the configured user option and update the user configured buffer.
 *  \details         -
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]       OptPtr          Pointer to the option field of received message.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
*********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VHandleRxUserOptions(
  TcpIp_IpV4CtrlIterType                                         IpV4CtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                     OptPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VVerifyClientAddr
 *********************************************************************************************************************/
/*! \brief           Verify client Ip address and netmask.
 *  \details         This function checks whether a client ip address and netmask is correct and
 *                   accordingly updates MsgIsValid variable.
 *  \param[in]       LocConfigData   Pointer to the local configuration data.
 *  \param[out]      MsgIsValidPtr   Pointer to indicate whether the received message is valid or invalid.
 *  \param[in]       MsgType         Indicates which type of message contains received frame.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VVerifyClientAddr(
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2VAR(boolean, AUTOMATIC, TCPIP_APPL_DATA)                       MsgIsValidPtr,
  uint8                                                            MsgType);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VDataLengthAndPortCheck
 *********************************************************************************************************************/
/*! \brief           Verify received message data length and Port.
 *  \details         -
 *  \param[in]       DataLen         Contains data length of a received message in bytes.
 *  \param[in]       SrcPort         DhcpV4 Source port.
 *  \param[in]       TgtPort         DhcpV4 Target(Destination) port.
 *  \param[in]       LenByte         Length of the Udp Packet.
 *  \return          E_OK            Message data length is valid.
 *  \return          E_NOT_OK        Message data length is not valid.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VDataLengthAndPortCheck(
  uint16                                    DataLen,
  IpBase_PortType                           SrcPort,
  IpBase_PortType                           TgtPort,
  uint16                                    LenByte);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VProcessDhcpMsg
 *********************************************************************************************************************/
/*! \brief           Store Ip address and other required information provided by DHCPOFFER message.
 *  \details         It changes state to the DHCPREQUEST for further processing.
 *                   It also processes incoming ACKs and NAKs received from server.
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                   CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                  1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                   2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \param[in]       MsgType         Indicates which type of message contains received frame.
 *  \param[in]       LocConfigData   Pointer to the local configuration data.
 *  \param[in]       DnsServerOptPtr DNS server information contained in received message.
 *  \param[in]       Yiaddr          Client Ip Address.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VProcessDhcpMsg(
  TcpIp_IpV4CtrlIterType                                           IpV4CtrlIdx,
  uint8                                                            MsgType,
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2CONST(TcpIp_DhcpV4_DnsOptInfoType, AUTOMATIC, TCPIP_APPL_DATA) DnsServerOptPtr,
  TcpIp_NetAddrType                                                Yiaddr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VVerifyMsgType
 *********************************************************************************************************************/
/*! \brief           Verifys if message not corrupted.
 *  \details         This function invalidates the message if it is a corrupted packet.
 *                   It updates MsgIsValidPtr parameter in order to discard the corrupted message or process further the valid message.
 *  \param[in]       MsgType         Indicates which type of message contains received frame.
 *  \param[out]      MsgIsValidPtr   Indicates whether the received message is valid or invalid.
 *  \param[in]       EndOptFound     End option of a message.
 *  \param[in]       LocConfigData   Pointer to the local configuration data.
 *  \param[in]       DhcpStatusIdx   Contains Dhcp status index for a given Ip controller.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VVerifyMsgType(
  uint8                                                            MsgType,
  P2VAR(boolean, AUTOMATIC, TCPIP_APPL_DATA)                       MsgIsValidPtr,
  boolean                                                          EndOptFound,
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  TcpIp_SizeOfDhcpStatusType                                       DhcpStatusIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VEvaluateOptionsAndProcessMsg
 *********************************************************************************************************************/
/*! \brief           Evaluate all supported options.
 *  \details         -
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                   CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                  1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                  2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \param[in]       DataPtr         Pointer to the data of a  received Dhcp frame.
 *  \param[in]       DataLen         Contains data length of a received message.
 *  \param[in]       PhysAddr        Physical address(Pointer to the destination MAC address).
 *                                   CONSTRAINT : [Must contains 6 bytes of memory]
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VEvaluateOptionsAndProcessMsg(
  TcpIp_IpV4CtrlIterType                      IpV4CtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)  DataPtr,
  uint16                                      DataLen,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)    PhysAddr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSendDhcpMsg
 *********************************************************************************************************************/
/*! \brief           Sends an Dhcp message.
 *  \details         -
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]       MsgType         Indicates which type of message contains received frame.
 *  \param[in]       DestAddr        Destination Ip address.
 *  \return          E_OK            Message is sent successfully..
 *  \return          E_NOT_OK        Message is not sent successfully.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VSendDhcpMsg(
  TcpIp_SizeOfIpV4CtrlType IpV4CtrlIdx,
  uint8                    MsgType,
  TcpIp_NetAddrType        DestAddr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddReqIpAddrOption
 *********************************************************************************************************************/
/*! \brief           Get length of a requested Ip address option and also updates the message option buffer.
 *  \details         -
 *  \param[out]      OptPtr          Pointer to the message options
 *                                   [Pointer can be NULL_PTR.
 *                                    - NULL_PTR:- Update the total length of the Requested Ip address option.
 *                                    - Non NULL_PTR:- Copy Requested Ip address option to the buffer.]
 *                                   CONSTRAINT: CM_TCPIP_DHCPV4_OPT_BUF_VALID_ACCESS
 *  \param[in]       Yiaddr          Your (Client's)Ip address.
 *  \return                          Message length.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4_VAddReqIpAddrOption(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptPtr,
  IpBase_AddrInType                       Yiaddr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddServerIdOption
 *********************************************************************************************************************/
/*! \brief           Get length of server identifier option also updates the message option buffer.
 *  \details         -
 *  \param[out]      OptPtr          Pointer to the message options
 *                                   [Pointer can be NULL_PTR.
 *                                      - NULL_PTR:- Update the total length of the Server Id option.
 *                                      - Non NULL_PTR:- Copy Server Id Option to the buffer.]
 *                                   CONSTRAINT: CM_TCPIP_DHCPV4_OPT_BUF_VALID_ACCESS
 *  \param[in]       Siaddr          IP address of next server to use in bootstrap, returned in DHCPOFFER, DHCPACK by server.
 *  \return                          Message length.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4_VAddServerIdOption(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptPtr,
  IpBase_AddrInType                       Siaddr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddUserOptions
 *********************************************************************************************************************/
/*! \brief           Get length of all user options and also updates the message option buffer.
 *  \details         -
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]       MsgType         Indicates which type of message contains received frame.
 *  \param[in]       MsgDataPtr      Pointer to the message data.
 *                                   [Pointer can be NULL_PTR.
 *                                    - NULL_PTR:- Update the total length of the User options.
 *                                    - Non NULL_PTR:- Copy user options to the buffer.]
 *                                   CONSTRAINT: CM_TCPIP_DHCPV4_OPT_BUF_VALID_ACCESS
 *  \return                          Message length of all options.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
STATIC FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV4_VAddUserOptions(
  TcpIp_SizeOfIpV4CtrlType                 IpV4CtrlIdx,
  uint8                                    MsgType,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) MsgDataPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddParamReqListOpt
 *********************************************************************************************************************/
/*! \brief           Get length of parameter request option and also updates the message option buffer.
 *  \details         -
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[out]      OptPtr          Pointer to the message options.
 *                                   [Pointer can be NULL_PTR.
 *                                    - NULL_PTR:- Update the total length of the Parameter Request list option.
 *                                    - Non NULL_PTR:- Copy information regarding Parameter Request list option to the buffer.]
 *                                   CONSTRAINT: CM_TCPIP_DHCPV4_OPT_BUF_VALID_ACCESS
 *  \return                          Message length of parameter request option.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4_VAddParamReqListOpt(
  TcpIp_SizeOfIpV4CtrlType                IpV4CtrlIdx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSendEventType
 *********************************************************************************************************************/
/*! \brief           Notify upper layer about Transmission/Reception of message.
 *  \details         -
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]       MsgType         Type of message
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VSendEventType(
  TcpIp_IpV4CtrlIterType   IpV4CtrlIdx,
  uint8                    MsgType);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSetUserOptions
 *********************************************************************************************************************/
/*! \brief           Sets or clears configured DHCPv4 user option data.
 *  \details         Writes DHCP option data identified by parameter OptCode into the respective buffer or
 *                   clears them from the buffer.
 *                   If API is called with option length 0, option will be cleared.
 *  \param[in]       IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]       OptCode         DHCP option, e.g. Host Name or vendor class etc.
 *  \param[in]       OptLen          Length of DHCP option data to be written. if OptLen is 0, clear the option.
 *  \param[in]       OptPtr          Pointer to memory containing DHCP option data
 *  \return          E_OK            no error occured.
 *  \return          E_NOT_OK        DHCP option data could not be written.
 *  \pre             -
 *  \context         TASK|ISR2
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VSetUserOptions(
  TcpIp_SizeOfIpV4CtrlType                   IpV4CtrlIdx,
  uint8                                      OptCode,
  uint8                                      OptLen,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptPtr);

/**********************************************************************************************************************
*  TcpIp_DhcpV4_VGetUserOptions
*********************************************************************************************************************/
/*! \brief           Reads user option data for configured DHCPv4 user options.
 * \details          Retrieves DHCP option data identified by parameter OptCode for DHCP options.
 * \param[in]        IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 * \param[in]        OptCode         DHCP option code, e.g. Host Name or vendor class etc.
 * \param[in]        OptLenPtr       Length of DHCP option data to be read
 * \param[in]        OptPtr          Pointer to memory where DHCP option data should be written
 * \return           E_OK            no error occured.
 * \return           E_NOT_OK        DHCP option data could not be read.
 * \pre              -
 * \context          TASK|ISR2
 * \reentrant        FALSE
 * \synchronous      TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VGetUserOptions(
  TcpIp_SizeOfIpV4CtrlType                   IpV4CtrlIdx,
  uint8                                      OptCode,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)   OptLenPtr,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)   OptPtr);

/**********************************************************************************************************************
*  TcpIp_DhcpV4_VLookUpOptionIdx
*********************************************************************************************************************/
/*! \brief           Look for the User option index for the given Option Id.
 *   \details         -
 *   \param[in]      IpV4CtrlIdx     Index of the IP controller/instance.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *   \param[in]      OptCode         DHCP option, e.g. Host Name or vendor class etc.
 *   \return         UserOptIdx      User option index to access related buffer informations.
 *   \pre            -
 *   \context        TASK|ISR2
 *   \reentrant      FALSE
 *   \synchronous    TRUE
*********************************************************************************************************************/
STATIC FUNC(TcpIp_DhcpUserOptionIterType, TCPIP_CODE) TcpIp_DhcpV4_VLookUpOptionIdx(
  TcpIp_IpV4CtrlIterType                  IpV4CtrlIdx,
  uint8                                   OptCode);

/**********************************************************************************************************************
*  TcpIp_DhcpV4_Clear_UserOptions
*********************************************************************************************************************/
/*! \brief           Clear all user options.
 *   \details         -
 *   \param[in]      IpV4CtrlIdx     IpV4 Controller index
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *   \pre            -
 *   \context        TASK|ISR2
 *   \reentrant      FALSE
 *   \synchronous    TRUE
*********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_Clear_UserOptions(TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_Init( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_IpV4CtrlDynIterType ipV4CtrlIdx;/* ip controller index */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all IPv4 controllers that have DHCPv4 address assignment method.*/
  for (ipV4CtrlIdx = 0; ipV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl(); ipV4CtrlIdx++)
  {
    /* #20 Check if Dhcp is configured on Ip controller. */
    if (TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(ipV4CtrlIdx) == TRUE)
    {
      TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(ipV4CtrlIdx);
      /* Reset DhcpStatus structure parameters. */
      TcpIp_SetSecTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                  /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                   /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_SetSecElapsedOfDhcpStatus(dhcpStatusIdx, 0);                                                                /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_SetLastDiscoverSecsOfDhcpStatus(dhcpStatusIdx, 0);                                                          /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_OFF);                                       /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_SetHostNameLenOfDhcpStatus(dhcpStatusIdx, 0);                                                               /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr = 0;                                                   /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_SetTimeoutOccurredOfDhcpStatus(dhcpStatusIdx, FALSE);                                                       /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_DhcpV4_Clear_UserOptions(ipV4CtrlIdx);
    }
  }
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_MainFunction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_MainFunction(void)
{

  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_IpV4CtrlDynIterType ipV4CtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all IPv4 controllers that have a local address with DHCPv4 address assignment method. */
  for (ipV4CtrlIdx = 0; ipV4CtrlIdx < TcpIp_GetSizeOfIpV4CtrlDyn(); ipV4CtrlIdx++)
  {
    if (TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(ipV4CtrlIdx) == TRUE)                                                          /* SBSW_TCPIP_CM_R10 */
    {
      TcpIp_SizeOfDhcpConfigType dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(ipV4CtrlIdx);
      TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(ipV4CtrlIdx);

      /* #20 If configured, restart DHCPv4 address assignment if a failure has occurred. */
      if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_OFF)
      {
        if (   (TcpIp_IsRestartOnFailOfDhcpConfig(dhcpConfigIdx) == TRUE)  /* PRQA S 3415 2 */ /*  MD_TCPIP_Rule13.5_3415_CslReadOnly */
            && (TcpIp_IsTimeoutOccurredOfDhcpStatus(dhcpStatusIdx) == TRUE))
        {
          /* restart addr config */
          TcpIp_DhcpV4_TriggerAddrRequest((TcpIp_SizeOfIpV4CtrlType)ipV4CtrlIdx);
        }

        continue;  /* PRQA S 0770 */ /* MD_TCPIP_DHCPV4_14.5_0770 */
      }

      /* #30 Update time variable used for timeout handling. */
      TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, TcpIp_GetMsTimerOfDhcpStatus(dhcpStatusIdx) + TCPIP_MAIN_FCT_PERIOD_MSEC);/* SBSW_TCPIP_CSL03_IDX_CALLEE */

      TCPIP_VENTER_CRITICAL_SECTION();

      if (TcpIp_GetMsTimerOfDhcpStatus(dhcpStatusIdx) >= 1000u)
      {
        /* one second passed */
        TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, TcpIp_GetMsTimerOfDhcpStatus(dhcpStatusIdx) - 1000u);               /* SBSW_TCPIP_CSL03_IDX_CALLEE */
        TcpIp_IncSecTimerOfDhcpStatus(dhcpStatusIdx);                                                                   /* SBSW_TCPIP_CSL03_IDX_CALLEE */
        TcpIp_IncSecElapsedOfDhcpStatus(dhcpStatusIdx);                                                                 /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      }

      TCPIP_VLEAVE_CRITICAL_SECTION();

      /* #40 Perform actions based on current DHCP state is necessary. */
      if (TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) <= TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx))
      {
        /* -------------------------------------------------------------------- */
        /* start of STATE dependent processing -------------------------------- */
        TcpIp_DhcpV4_VProcessCtrlState( (TcpIp_SizeOfIpV4CtrlDynType)ipV4CtrlIdx);
      }
    }
  }
}  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_TriggerAddrRequest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_TriggerAddrRequest(TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
  TcpIp_SizeOfDhcpConfigType dhcpConfigIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE);
  TCPIP_ASSERT(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE);

  CANOE_WRITE_STRING("TcpIp_DhcpV4_TriggerAddrRequest: function was called")
  dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);

  TcpIp_SetRetryCounterOfDhcpStatus(dhcpStatusIdx, 0);                                                                  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  TcpIp_SetSecTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  TcpIp_SetSecElapsedOfDhcpStatus(dhcpStatusIdx, 0);                                                                    /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  TcpIp_SetLastDiscoverSecsOfDhcpStatus(dhcpStatusIdx, 0);                                                              /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  {
    /* #10 Set timer and event for initial wait. */
    uint16 randTimeMsec;
    randTimeMsec = ( TcpIp_GetRandomNumber()
                   % (TcpIp_GetInitWaitMaxOfDhcpConfig(dhcpConfigIdx)
                   - TcpIp_GetInitWaitMinOfDhcpConfig(dhcpConfigIdx)) )
                   + TcpIp_GetInitWaitMinOfDhcpConfig(dhcpConfigIdx);                                                   /* SBSW_TCPIP_RANDOM_NUMBER_FUNC */

    TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, (1000u - (randTimeMsec % 1000u)));                                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, (((uint32) randTimeMsec / 1000u) + 1u));                           /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  }
  /* #20 Set State to init */
  TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_INIT);                                          /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */

}  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_StopAddrRequest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_StopAddrRequest(
  TcpIp_IpV4CtrlIterType  IpV4CtrlIdx )
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset Dhcp module for this Ip Controller. */
    TcpIp_DhcpV4_Reset(IpV4CtrlIdx);

}

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_RxIndication
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
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_RxIndication(
    TcpIp_IpV4CtrlIterType                                     IpV4CtrlIdx,
    P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                 DataPtr,
    uint16                                                     DataLen,
    P2CONST(IpBase_SockAddrInType, AUTOMATIC, TCPIP_APPL_DATA) SourcePtr,
    P2CONST(IpBase_SockAddrInType, AUTOMATIC, TCPIP_APPL_DATA) DestinationPtr,
    boolean                                                    ChecksumCalculated)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 physAddr[TCPIP_PHYS_ADDR_LEN_BYTE];
  IpBase_PortType  srcPort;
  IpBase_PortType  tgtPort;
  uint16           lenByte;

  Std_ReturnType   retVal;
  /* ----- Implementation ----------------------------------------------- */
  /* In Vector's implementation of the TCPIP-Stack, receiving on UDP sockets always provides a
     linear buffer. So direct DHCP header access via a single struct is possible. */
  TCPIP_ASSERT(DataPtr != NULL_PTR);
  srcPort = TCPIP_GET_UINT16(DataPtr, DHCPV4_SRCPORT_OFS);
  tgtPort = TCPIP_GET_UINT16(DataPtr, DHCPV4_TGTPORT_OFS);
  lenByte = TCPIP_GET_UINT16(DataPtr, DHCPV4_LEN_BYTE_OFS);

  /* #10 Check if DHCP address assignment is enabled for this controller. */
  if (TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == FALSE)
  {
    /* DHCP not enabled for this controller */
    retVal = E_NOT_OK;
  }
  /* #20 Check if data length and ports are valid. */
  else
  {
    retVal = TcpIp_DhcpV4_VDataLengthAndPortCheck(DataLen, srcPort, tgtPort, lenByte);
  }

  if (retVal == E_OK)
  {
    /* #30 Verify if the checksum was already checked by the lower layer.*/
    if (ChecksumCalculated == TRUE)
    {
      /* The DHCP checksum was already checked by the lower layer / hardware. If the checksum was wrong the packet will not reach the DHCP at all, so no further check is necessary here. */
    }
    else
    {
      /* #40 Otherwise calculate checksum. */
      uint32 checksumTmp = TcpIp_VCalcIpV4PseudoHdrChecksum(SourcePtr->sin_addr, DestinationPtr->sin_addr, TCPIP_SOCK_PROT_UDP, DataLen);

      checksumTmp = (uint16)IpBase_TcpIpChecksumAdd(DataPtr, DataLen, checksumTmp, TRUE);                               /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */

      if (checksumTmp != 0u)
      {
        retVal = E_NOT_OK;
      }
    }
  }

  if (retVal == E_OK)
  {
    uint32 magicPattern;
    /* skip UDP header */
    TCPIP_P2C(uint8) localDataPtr = &DataPtr[TCPIP_UDP_HDR_LEN_BYTE];
    uint16           localDataLen = (uint16)(lenByte - TCPIP_UDP_HDR_LEN_BYTE);

    magicPattern = TCPIP_GET_UINT32(localDataPtr, TCPIP_DHCPV4_FRAME_MAGICPATTERN_OFS);
    /* #50 Verify the magic pattern. */
    /* Ignore this message if magic pattern at end of DHCP header is not set correctly. */
    if (magicPattern != TCPIP_DHCPV4_MAGIC_PATTERN)
    {
      retVal = E_NOT_OK;
    }
    /* find the corresponding controller */
    /* compare Msg-HW-Addr with own addr (future: compare to all controller addresses) */
    if (retVal == E_OK)
    { /* #60 If the magic pattern is correct, forward the message in order to get further processed. */
      TcpIp_DhcpV4_VEvaluateOptionsAndProcessMsg(IpV4CtrlIdx, localDataPtr, localDataLen, &physAddr[0]);                /* SBSW_TCPIP_DHCPV4_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */
    }
  }
}  /* PRQA S 6050, 6060 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STPAR */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_Reset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_Reset(TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset DHCP module for this controller. */
  if (TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
    dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
    TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_OFF);                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetSecTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                    /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                     /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr = 0;                                                     /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetReqIpAddrOfDhcpStatus(dhcpStatusIdx, IPV4_ADDR_ANY);                                                       /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetTimeoutOccurredOfDhcpStatus(dhcpStatusIdx, FALSE);                                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    /* #20 Clear all tx and Rx user options. */
    TcpIp_DhcpV4_Clear_UserOptions(IpV4CtrlIdx);
  }
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_SetHostName
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_SetHostName(
    TcpIp_SizeOfIpV4CtrlType                   IpV4CtrlIdx,
    P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
    uint8                                      DataLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
  TcpIp_SizeOfDhcpConfigType dhcpConfigIdx;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(DataPtr != NULL_PTR);
  /* Verify if DhcpStatus is configured for this Ip controller.*/
  if (TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
    dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
    /* #10 Report the DetError if Host name length is bigger than the maximum allowed length.*/
    if (DataLen > TcpIp_GetHostNameLenMaxOfDhcpConfig(dhcpConfigIdx))
    {
      TcpIp_CallDetReportError(TCPIP_DHCPV4_API_ID_SET_HOST_NAME, TCPIP_E_INV_ARG);
    }
    /* #20 Otherwise Set the Dhcp HostName and HostName Length. */
    else
    {
      /* set name length */
      TcpIp_SetHostNameLenOfDhcpStatus(dhcpStatusIdx, DataLen);                                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      /* copy name */
      {
        uint8_least                dataIdx;
        TcpIp_DhcpHostnameIterType hostnameByteOfs = TcpIp_GetDhcpHostnameStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
        for (dataIdx = 0; dataIdx < DataLen; dataIdx++)
        {
          TcpIp_SetDhcpHostname(hostnameByteOfs + dataIdx, DataPtr[dataIdx]);                                           /* SBSW_TCPIP_WRITE_DHCPHOSTNAME */
        }
      }
      retVal =  E_OK;
    }
  }
  return retVal;
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_GetDhcpTimeoutInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV4_GetDhcpTimeoutInfo(TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  boolean retVal = FALSE;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if address assignment is configured for a given Ip Instance. */
  if (TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    /* #20 Get Dhcp Status Index of a given Ip Instance. */
    TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
    retVal = (boolean)(TcpIp_IsTimeoutOccurredOfDhcpStatus(dhcpStatusIdx) == TRUE); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  }
  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_GetActiveAddress
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV4_GetActiveAddress(
    TcpIp_LocalAddrV4IterType                             IpV4CtrlIdx,
    P2VAR(IpV4_IpAddrSetType, AUTOMATIC, TCPIP_APPL_DATA) AddrInfoPtr)
{
  /* ----- Local Variables ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
  /* ----- Implementation ----------------------------------------------- */
  boolean retVal = FALSE;
  TCPIP_ASSERT(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE);
  dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  TCPIP_ASSERT(IpV4_Ip_VCfgGetAddrAssignmentPrio(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP) != 0u);
  /* #10 Check if DHCP instance has an active lease from a DHCP server. */
  if (   (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_BOUND)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_RENEWING)
      || (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REBINDING))
  {
    /* #20 Copy address information into provided output structure. */
    AddrInfoPtr->NetAddr   =  TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr;                               /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    AddrInfoPtr->NetMask   = TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->NetMask;                               /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    AddrInfoPtr->DefGwAddr = TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->DefGWiaddr;                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    retVal = TRUE;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VEvaluateOptionsAndProcessMsg
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VEvaluateOptionsAndProcessMsg(
  TcpIp_IpV4CtrlIterType                      IpV4CtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)  DataPtr,
  uint16                                      DataLen,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)    PhysAddr)
{
  /* ----- Local Variables ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
  uint8 opcode;                  /* op code: 1 = BOOTREQUEST, 2 = BOOTREPLY */
  uint8 hwType;
  uint8 hwLen;
  uint32 xid;                 /* Transaction ID */
  TcpIp_NetAddrType yiaddr;   /* Your (client) IP address */
  uint8 chaddr[16];          /* Client hardware address */

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_LL_GetPhysAddr(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), &PhysAddr[0]);                                     /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
  /* Read the opcode from the memory and save into the opcode variable */
  opcode = TCPIP_GET_UINT8(     DataPtr, TCPIP_DHCPV4_FRAME_OPCODE_OFS);
  hwType = TCPIP_GET_UINT8(     DataPtr, TCPIP_DHCPV4_FRAME_HWADDR_TYPE_OFS);
  hwLen  = TCPIP_GET_UINT8(     DataPtr, TCPIP_DHCPV4_FRAME_HWADDR_LEN_OFS);
  xid    = TCPIP_GET_UINT32_RAW(DataPtr, TCPIP_DHCPV4_FRAME_XID_OFS);
  yiaddr = TCPIP_GET_UINT32(    DataPtr, TCPIP_DHCPV4_FRAME_YIADDR_OFS);

  yiaddr = TCPIP_NTOHL(yiaddr);
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IpBase_Copy(&chaddr[0], &DataPtr[TCPIP_DHCPV4_FRAME_CLIENT_HW_ADDR_OFS], 16u);                                        /* SBSW_TCPIP_IPBASE_COPY_CALLEE */

  /* #10 Get Dhcp Status Index for a given Ip controller. */
  dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  /* #20 Verify if the message is for this node. */
  if (   (TcpIp_CmpLLAddr(&chaddr[0], &PhysAddr[0]) == TRUE)  /* PRQA S 3415 5 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (opcode == TCPIP_DHCPV4_OP_BOOTREPLY)  /* this message comes from a server */
      && (hwType == TCPIP_DHCPV4_HW_TYPE_ETH)
      && (hwLen  == TCPIP_DHCPV4_HW_LEN_ETH)
      && (xid    == TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Xid))/* this message corresponds to the current DHCP XID */ /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
  {
    TcpIp_DhcpV4_DataStructType locConfigData;
    uint8 msgType = TCPIP_DHCPV4_DHCPINVALIDMSG;
    uint16 overallOptLen = (uint16)(DataLen - TCPIP_DHCPV4_MIN_HEADER_LENGTH_BYTE);
    uint16 remainingOptLen = overallOptLen;
    const uint8 *optPtr = &DataPtr[TCPIP_DHCPV4_MIN_HEADER_LENGTH_BYTE]; /* set optPtr at starting of option field (code) */
    TcpIp_DhcpV4_DnsOptInfoType dnsServerOpt;
    boolean endOptFound = FALSE;
    boolean msgIsValid = TRUE;
    /* now evaluate DHCP options */
    locConfigData.T1          = 0;
    locConfigData.T2          = 0;
    locConfigData.Ciaddr      = yiaddr;
    locConfigData.NetMask     = 0;
    locConfigData.DefGWiaddr  = 0;
    locConfigData.DhcpSiaddr  = 0;
    locConfigData.LeaseTime   = 0;

    dnsServerOpt.DnsServerAddrCount = 0;
    dnsServerOpt.DnsServerAddrPtr   = NULL_PTR;

    /* #30 Iterate over all supported options. */
    while ((msgIsValid == TRUE) && (remainingOptLen > 0u))  /* PRQA S 0771 */ /* MD_TCPIP_DHCPV4_14.6_0771_a */
    {
      /* evaluate all supported options */
      if (*optPtr == TCPIP_DHCPV4_OPT_PAD_TYPE)
      {
        /* option Pad */
        optPtr = &optPtr[1];
        remainingOptLen--;
      }
      else if (*optPtr == TCPIP_DHCPV4_OPT_END_TYPE)
      {
        /* option End */
        endOptFound = TRUE;
        break;  /* PRQA S 0771 */ /* MD_TCPIP_DHCPV4_14.6_0771_a */
      }
      else
      { /* Option length is first 2 bytes(code + len) + the value stored at the 2nd byte(optPtr[1]) */
        uint8 optLen = TCPIP_DHCPV4_OPTION_HDR_BYTE + optPtr[1];
        /* #40 If the message length is invalid, discontineu the iteration. Do not forward the message for further process. */
        if ((remainingOptLen < TCPIP_DHCPV4_OPTION_HDR_BYTE) || (optLen > remainingOptLen))
        {
           msgIsValid = FALSE;
          /* ERROR:
          - options have at least option type and length fields
          - option length may not be greater than remaining data length */
          break;  /* PRQA S 0771 */ /* MD_TCPIP_DHCPV4_14.6_0771_a */
        }

        if (TcpIp_DhcpV4_ProcessOptions(IpV4CtrlIdx, optPtr, &msgType, &locConfigData, &dnsServerOpt) == E_OK)          /* SBSW_TCPIP_UPDATE_VARIABLE */ /* SBSW_TCPIP_FUNC_CALL_LOCAL_PTR_OPTION */
        {
          /* Update the option pointer and the remaining option length .*/
          optPtr = &optPtr[optLen];
          remainingOptLen -= optLen;
        }
        else
        {
          msgIsValid = FALSE;
        }
      }
    }  /* while(RemainingOptLen > 0u) */
    /* #50 If the Options are valid, verify the message type. */
    if (msgIsValid == TRUE)
    {
      TcpIp_DhcpV4_VVerifyMsgType(msgType, &msgIsValid, endOptFound, &locConfigData, dhcpStatusIdx);                    /* SBSW_TCPIP_UPDATE_VARIABLE */
    }
    /* #60 If the message type is valid, forward the message for the further process. */
    /* Forward the message for the further process.*/
    if (msgIsValid == TRUE)
    { /* #70 Send event to upper layer about recieved message. */
      TcpIp_DhcpV4_VSendEventType(IpV4CtrlIdx, msgType);
      TcpIp_DhcpV4_VProcessDhcpMsg(IpV4CtrlIdx, msgType, &locConfigData, &dnsServerOpt, yiaddr);                        /* SBSW_TCPIP_UPDATE_VARIABLE */
    }
  }
} /* PRQA S 6080, 6050 */ /* MD_MSR_STMIF, MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VVerifyMsgType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VVerifyMsgType(
  uint8                                                            MsgType,
  P2VAR(boolean, AUTOMATIC, TCPIP_APPL_DATA)                       MsgIsValidPtr,
  boolean                                                          EndOptFound,
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  TcpIp_SizeOfDhcpStatusType                                       DhcpStatusIdx)
 {
   /* #10 Check if message type has a valid value */
   if (   (MsgType == TCPIP_DHCPV4_DHCPINVALIDMSG)
       || (MsgType > TCPIP_DHCPV4_DHCPINFORM))
   {
     *MsgIsValidPtr = FALSE;                                                                                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
   }
   /* #20 Check if end option is missing.*/
   else if (EndOptFound != TRUE)
   {
     /* end option is missing */
     *MsgIsValidPtr = FALSE;                                                                                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
   }
   /* #30 Check if DHCP message is either DHCPOFFER or DHCPACK and lease time is not expired. */
   else if (( LocConfigData->LeaseTime == 0u) && ((MsgType == TCPIP_DHCPV4_DHCPACK) || (MsgType == TCPIP_DHCPV4_DHCPOFFER)))
   {
     /* invalid DHCP message type, or invalid lease time */
     *MsgIsValidPtr = FALSE;                                                                                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
   }
   else if (   (TcpIp_GetCtrlStateOfDhcpStatus(DhcpStatusIdx) != TCPIP_DHCPV4_CTRL_STATE_SELECTING)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
            && (TcpIp_GetAddrDataStructOfDhcpStatus(DhcpStatusIdx)->DhcpSiaddr != LocConfigData->DhcpSiaddr))
   {
     /* discard messages from other servers than the selected one */
     *MsgIsValidPtr = FALSE;                                                                                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
   }
   else
   {
     TcpIp_DhcpV4_VVerifyClientAddr(LocConfigData, MsgIsValidPtr, MsgType);                                             /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
   }
}
/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VProcessDhcpMsg
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VProcessDhcpMsg(
  TcpIp_IpV4CtrlIterType                                           IpV4CtrlIdx,
  uint8                                                            MsgType,
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2CONST(TcpIp_DhcpV4_DnsOptInfoType, AUTOMATIC, TCPIP_APPL_DATA) DnsServerOptPtr,
  TcpIp_NetAddrType                                                Yiaddr)
{
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType  dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  /* #10 Verify if the received Dhcp message is valid. */
  if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_SELECTING)
  {
    /* #20 Verify if the incoming message is DHCPOFFER. */
    if (MsgType == TCPIP_DHCPV4_DHCPOFFER)
    {
      /* incoming offer for IP address */

      /* Always take the first DHCPOFFER and use is for further processing. */
      /* #30 Store addresses of a incoming messages. */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr      = Yiaddr;                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->DhcpSiaddr  = LocConfigData->DhcpSiaddr;                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->NetMask     = LocConfigData->NetMask;                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->DefGWiaddr  = LocConfigData->DefGWiaddr;                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */

      /* switch mode to next state and set timeout (for transmission of request) */
      /* #40 Reset timer because lease times are stored relative to the DHCPREQUEST message. */
      TcpIp_SetSecTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                   /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, 0);                                                              /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_SetRetryCounterOfDhcpStatus(dhcpStatusIdx, 0);                                                              /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      /* Value of TcpIp_SetSecElapsedOfDhcpStatus is not reset here because this value
      * reflects the time since beginning of address acquisition process. [RFC2131 page 10]
      */
      TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_REQUESTING);                                /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    }
    else
    {
      /* #50 Ignore incoming ACK and NAK in this state. */
    }
  }
  else if (   (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REQUESTING)   /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
           || (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_RENEWING)
           || (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REBINDING))
  {
    TcpIp_DhcpV4_ProcessAckOrNak(IpV4CtrlIdx, Yiaddr, MsgType, LocConfigData, DnsServerOptPtr);                         /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
  }
  else
  {
    /* ignore messages in all other states */
  }
  /* end of DHCP message "switch" */
  /* end if(MsgIsValid) */
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VDataLengthAndPortCheck
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VDataLengthAndPortCheck(
  uint16                                    DataLen,
  IpBase_PortType                           SrcPort,
  IpBase_PortType                           TgtPort,
  uint16                                    LenByte)
{
  Std_ReturnType retVal = E_OK;
  /* #10 Verify that data length is bigger than UDP  header length. */
  if (DataLen < TCPIP_UDP_HDR_LEN_BYTE)
  {
    /* invalid length */
    retVal = E_NOT_OK;
  }
  else
  {
    /* #20 Verify that the server port and destination port are correct. */
    if ((SrcPort != TCPIP_DHCPV4_SERVER_PORT) || (TgtPort != TCPIP_DHCPV4_CLIENT_PORT))
    {
      retVal = E_NOT_OK;
    }
    else
    {
      /* #30 Verify if Udp Packet length is valid. */
      if ((LenByte > DataLen) || (LenByte < (TCPIP_UDP_HDR_LEN_BYTE + TCPIP_DHCPV4_MIN_HEADER_LENGTH_BYTE)))
      {
        retVal = E_NOT_OK;
      }
    }
  }
  return retVal;
}
/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VVerifyClientAddr
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VVerifyClientAddr(
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2VAR(boolean, AUTOMATIC, TCPIP_APPL_DATA)                       MsgIsValidPtr,
  uint8                                                            MsgType)
{
  /* #10 Verify if Ciaddr is not zero and Message is DHCPNACK. */
  if ((LocConfigData->Ciaddr == 0u) && (MsgType != TCPIP_DHCPV4_DHCPNACK))
  {
    *MsgIsValidPtr = FALSE;                                                                                             /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
  }
  /* #20 Check for invalid client address 'global broadcast. */
  else if (LocConfigData->Ciaddr == TCPIP_INADDR_BROADCAST)
  {
    *MsgIsValidPtr = FALSE;                                                                                             /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
  }
   /* #30 Check for invalid client address 'multicast'. */
  else if ((TCPIP_HTONL(LocConfigData->Ciaddr) & 0xF0000000u) == 0xE0000000u)
  {
    *MsgIsValidPtr = FALSE;                                                                                             /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
  }
   /* #40 Check for invalid network mask. */
  else if (LocConfigData->NetMask != 0u)
  {
    uint8_least shiftCnt = 0u;
    uint32 netmaskShifted = TCPIP_HTONL(LocConfigData->NetMask);
    while (((netmaskShifted & 0x01u) == 0u)) /* This condition will be false after a maximum of 31 iterations since at least one bit in NetmaskShifted is set. */
    {
      netmaskShifted = netmaskShifted >> 1;
      shiftCnt++;
    }

    while ((shiftCnt < 32u) && ((netmaskShifted & 0x01u) == 1u))
    {
      netmaskShifted = netmaskShifted >> 1;
      shiftCnt++;
    }

    if (shiftCnt != 32u)
    {
      /* #50 Discard messages, network mask is not a sequence of '1'-bits followed by a sequence of '0'-bits. */
      *MsgIsValidPtr = FALSE;                                                                                           /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    }
  }
  else
  {
  /* nothing to do */
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VHandleRxUserOptions
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VHandleRxUserOptions(
  TcpIp_IpV4CtrlIterType                                         IpV4CtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                     OptPtr)
{
  /* ----- Local Variables ----------------------------------------------- */
  uint8 optLen;
  uint8 optCode;
  TcpIp_DhcpUserOptionIterType dhcpUserOptIdx;
  TcpIp_DhcpUserOptionBufferIterType  userOptBufIdx;
  /* ----- Implementation ----------------------------------------------- */
  optCode = OptPtr[0];
  /* Read Option length */
  optLen = OptPtr[1];

  /* #10 Verify if user options are configured for given controller */
  if (TcpIp_IsDhcpUserOptionUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    /* #20 Look up for the right user option index to acess related buffer and buffer length. */
    dhcpUserOptIdx = TcpIp_DhcpV4_VLookUpOptionIdx(IpV4CtrlIdx, optCode);

    if (   (dhcpUserOptIdx < TCPIP_DHCPV4_OPT_IDX_INVALID) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (   (TcpIp_GetDirectionOfDhcpUserOption(dhcpUserOptIdx) == TCPIP_DHCP_USER_OPTION_RX)
            || (TcpIp_GetDirectionOfDhcpUserOption(dhcpUserOptIdx) == TCPIP_DHCP_USER_OPTION_RX_REQUESTED)))
    {
      /* Enter critical section */
      IPV4_VENTER_CRITICAL_SECTION();
      userOptBufIdx = TcpIp_GetDhcpUserOptionBufferStartIdxOfDhcpUserOption(dhcpUserOptIdx);
      /* #30 Verify if option length is smaller or same as configured buffer length. */
      if (optLen <= TcpIp_GetDhcpUserOptionBufferLengthOfDhcpUserOption(dhcpUserOptIdx))
      {
        /* #40 Copy option length and data to configured user option buffer. */
        TcpIp_SetLengthOfDhcpUserOptionDyn(dhcpUserOptIdx, optLen);                                                     /* SBSW_TCPIP_CSL03_USEROPTIDX_CALLEE */
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IpBase_Copy(TcpIp_GetAddrDhcpUserOptionBuffer(userOptBufIdx), (const IpBase_CopyDataType*)&OptPtr[2], optLen);  /* SBSW_TCPIP_CSL03_USEROPTIDX_CALLEE */ /* SBSW_TCPIP_IPBASE_COPY_CALLEE */
      }
      /* #50 if option length is bigger than the configured buffer than copy only configured ammount of data into the buffer. */
      else
      {
        TcpIp_SetLengthOfDhcpUserOptionDyn(dhcpUserOptIdx, TcpIp_GetDhcpUserOptionBufferLengthOfDhcpUserOption(dhcpUserOptIdx));/* SBSW_TCPIP_CSL03_USEROPTIDX_CALLEE */
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IpBase_Copy(TcpIp_GetAddrDhcpUserOptionBuffer(userOptBufIdx), (const IpBase_CopyDataType*)&OptPtr[2],           /* SBSW_TCPIP_CSL03_USEROPTIDX_CALLEE */ /* SBSW_TCPIP_IPBASE_COPY_CALLEE */
                    TcpIp_GetDhcpUserOptionBufferLengthOfDhcpUserOption(dhcpUserOptIdx));
      }
      /* Leave critical section */
      IPV4_VLEAVE_CRITICAL_SECTION();
    }
  }
} /* PRQA S  6050 */ /*  MD_TcpIp_STCAL_CslAccess */
/**********************************************************************************************************************
*  TcpIp_DhcpV4_VSendEventType
*********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
*/

TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VSendEventType(
  TcpIp_IpV4CtrlIterType   IpV4CtrlIdx,
  uint8                    MsgType)
{
  /* ----- Local Variables ----------------------------------------------- */
  TcpIp_SizeOfSocketOwnerConfigType socketOwnerCfgIdx;
  TcpIp_DhcpEventType dhcpEvent;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all socket owener configurations. */
  for (socketOwnerCfgIdx = 0; socketOwnerCfgIdx < TcpIp_GetSizeOfSocketOwnerConfig(); socketOwnerCfgIdx++)
  {
    /* #20 Check if callout is configured. */
    if (TcpIp_GetDhcpEventFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx) != NULL_PTR)
    {
      TcpIp_LocalAddrIdType localAddrId = TCPIP_LOCAL_ADDR_IDX_TO_ID(TcpIp_GetLocalAddrV4DhcpIdxOfIpV4Ctrl(IpV4CtrlIdx));
      /* #30 Select dhcp event to be sent. */
      switch (MsgType)
      {
      case TCPIP_DHCPV4_DHCPDISCOVER:
        dhcpEvent = TCPIP_DHCP_EVENT_TX_DISCOVER_SOLICIT;
        break;
      case TCPIP_DHCPV4_DHCPOFFER:
        dhcpEvent = TCPIP_DHCP_EVENT_RX_OFFER_ADVERTISE;
        break;
      case TCPIP_DHCPV4_DHCPREQUEST:
        dhcpEvent = TCPIP_DHCP_EVENT_TX_REQUEST;
        break;
      case TCPIP_DHCPV4_DHCPACK:
        dhcpEvent = TCPIP_DHCP_EVENT_RX_ACK_REPLY;
        break;
      default:
        dhcpEvent = TCPIP_DHCPV4_EVENT_INVALID;
        break;
      }
      /* #40 Send event to upper layer. */
      TcpIp_GetDhcpEventFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx)(localAddrId, dhcpEvent);                          /* SBSW_TCPIP_FUNC_PTR_CALL */
    }
  }
}

/**********************************************************************************************************************
*  TcpIp_DhcpV4_VSetUserOptions
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VSetUserOptions(
  TcpIp_SizeOfIpV4CtrlType                   IpV4CtrlIdx,
  uint8                                      OptCode,
  uint8                                      OptLen,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptPtr)
{
  /* ----- Local Variables ----------------------------------------------- */
  Std_ReturnType                      retVal;
  TcpIp_DhcpUserOptionIterType        dhcpUserOptIdx;
  TcpIp_DhcpUserOptionBufferIterType  userOptBufIdx;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Look up for the right user option index to acess related buffer and buffer length. */
  dhcpUserOptIdx = TcpIp_DhcpV4_VLookUpOptionIdx(IpV4CtrlIdx, OptCode);
  /* #20 Verify if option idx is valid. */
  if (dhcpUserOptIdx < TCPIP_DHCPV4_OPT_IDX_INVALID)
  {
    userOptBufIdx = TcpIp_GetDhcpUserOptionBufferStartIdxOfDhcpUserOption(dhcpUserOptIdx);
    /* #30 Enter critical section. */
    IPV4_VENTER_CRITICAL_SECTION();

    /* #40 If OptLen is 0, then clear the Dhcp User Option length for this OptCode. */
    if (OptLen == 0u)
    {
      TcpIp_SetLengthOfDhcpUserOptionDyn(dhcpUserOptIdx, 0);                                                            /* SBSW_TCPIP_CSL03_USEROPTIDX_CALLEE */
      retVal = E_OK;
    }
    /* #50 Copy option length and data to configured user option buffer if option length is smaller or same as configured buffer length. */
    else if (   (OptLen <= TcpIp_GetDhcpUserOptionBufferLengthOfDhcpUserOption(dhcpUserOptIdx)) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
              && (TcpIp_GetDirectionOfDhcpUserOption(dhcpUserOptIdx) == TCPIP_DHCP_USER_OPTION_TX))
    {
      TcpIp_SetLengthOfDhcpUserOptionDyn(dhcpUserOptIdx, OptLen);                                                       /* SBSW_TCPIP_CSL03_USEROPTIDX_CALLEE */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpBase_Copy(TcpIp_GetAddrDhcpUserOptionBuffer(userOptBufIdx), (const IpBase_CopyDataType*)OptPtr, OptLen);        /* SBSW_TCPIP_CSL03_USEROPTIDX_CALLEE */ /* SBSW_TCPIP_IPBASE_COPY_CALLEE */
      retVal = E_OK;
    }
    /* #60 if option length is bigger than the configured buffer than throw Det error. */
    else
    {
      TcpIp_CallDetReportError(TCPIP_DHCPV4_API_ID_SET_USER_OPTION, TCPIP_E_INV_ARG);
      retVal = E_NOT_OK;
    }
    /* #70 Leave critical section. */
    IPV4_VLEAVE_CRITICAL_SECTION();
  }
  /* #80 Option Code is not supported. Throw Det error.*/
  else
  {
    TcpIp_CallDetReportError(TCPIP_DHCPV4_API_ID_SET_USER_OPTION, TCPIP_E_INV_ARG);
    retVal = E_NOT_OK;
  }
  return retVal;
} /* End of TcpIp_DhcpV4_VSetUserOptions() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
*  TcpIp_DhcpV4_VGetUserOptions
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VGetUserOptions(
  TcpIp_SizeOfIpV4CtrlType                   IpV4CtrlIdx,
  uint8                                      OptCode,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)   OptLenPtr,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)   OptPtr)
{
  /* ----- Local Variables ----------------------------------------------- */
  Std_ReturnType                     retVal;
  TcpIp_DhcpUserOptionIterType       dhcpUserOptIdx;
  TcpIp_DhcpUserOptionBufferIterType userOptBufIdx;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Look up for the right user option index to acess related option buffer and buffer length. */
  dhcpUserOptIdx = TcpIp_DhcpV4_VLookUpOptionIdx(IpV4CtrlIdx, OptCode);

  /* #20 Verify if option code is valid. */
  if (dhcpUserOptIdx < TCPIP_DHCPV4_OPT_IDX_INVALID)
  {
    userOptBufIdx = TcpIp_GetDhcpUserOptionBufferStartIdxOfDhcpUserOption(dhcpUserOptIdx);
    /* #30 Update option length, if option length is bigger or same as configured user option buffer length. */
    if (*OptLenPtr >= TcpIp_GetLengthOfDhcpUserOptionDyn(dhcpUserOptIdx))
    {
      *OptLenPtr =(uint8)TcpIp_GetLengthOfDhcpUserOptionDyn(dhcpUserOptIdx);                                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      /* #40 Copy data to buffer provided by user(pointed by OptPtr). */
      if (*OptLenPtr > 0u)
      {
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IpBase_Copy((IpBase_CopyDataType*)OptPtr, (const IpBase_CopyDataType*)TcpIp_GetAddrDhcpUserOptionBuffer(userOptBufIdx), *OptLenPtr); /* SBSW_TCPIP_FUNC_CALL_IpBase_Copy */
      }
      retVal = E_OK;
    }
    /* #50 if option length is bigger than the configured buffer than throw Det error. */
    else
    {
      TcpIp_CallDetReportError(TCPIP_DHCPV4_API_ID_GET_USER_OPTION, TCPIP_E_INV_ARG);
      retVal = E_NOT_OK;
    }
  }
  /* #60 Option Code is not supported.*/
  else
  {
    TcpIp_CallDetReportError(TCPIP_DHCPV4_API_ID_GET_USER_OPTION, TCPIP_E_INV_ARG);
    retVal = E_NOT_OK;
  }
  return retVal;
} /* End of TcpIp_DhcpV4_VGetUserOptions() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_ProcessOptions
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_ProcessOptions(
  TcpIp_IpV4CtrlIterType                                         IpV4CtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                     OptPtr,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       MsgTypePtr,
  P2VAR(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2VAR(TcpIp_DhcpV4_DnsOptInfoType, AUTOMATIC, TCPIP_APPL_DATA) DnsServerOptPtr)
{
  /* ----- Local Variables ----------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 optLen;
  DnsServerOptPtr->DnsServerAddrCount = 0;                                                                              /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
  DnsServerOptPtr->DnsServerAddrPtr   = NULL_PTR;                                                                       /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */

  /* ----- Implementation ----------------------------------------------- */
  optLen = OptPtr[1];
  switch (*OptPtr)
  {
  case (TCPIP_DHCPV4_OPT_SUBNET_MASK_TYPE):
    {
      /* #10 Verify the length of SUBNET_MASK option.If its valid length then read the NetMask and store it in host byte order. */
      if(optLen == TCPIP_DHCPV4_OPT_SUBNET_MASK_LEN)
      {
        /* Address is stored in host byte-order */
        LocConfigData->NetMask = TCPIP_GET_UINT32_RAW(OptPtr, 2u);                                                      /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        /* If the server specifies a subnet mask it must not be zero. */
        if (LocConfigData->NetMask != 0u)
        {
          retVal = E_OK;
        }
      }
      break;
    }

  case (TCPIP_DHCPV4_OPT_ROUTER_TYPE):
    {
      /* #20 Verify the length of ROUTER option to get DefaultGateway address.*/
      if (((optLen % TCPIP_DHCPV4_OPT_ROUTER_LEN) == 0u) && (optLen >= TCPIP_DHCPV4_OPT_ROUTER_LEN))
      {
        /* Address is stored in host byte-order */
        LocConfigData->DefGWiaddr = TCPIP_GET_UINT32_RAW(OptPtr, 2u);                                                   /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        retVal = E_OK;
      }
      break;
    }

  case (TCPIP_DHCPV4_OPT_IP_ADDR_LEASE_TIME_TYPE):
    {
      /* #30 Verify the length of IP_ADDR_LEASE_TIME option to get the LeaseTime. */
      if(optLen == TCPIP_DHCPV4_OPT_IP_ADDR_LEASE_TIME_LEN)
      {

        LocConfigData->LeaseTime = TCPIP_GET_UINT32(OptPtr, 2u);                                                        /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        retVal = E_OK;
      }
      break;
    }

  case (TCPIP_DHCPV4_OPT_DHCPV4_MSG_TYPE):
    {
      if(optLen == TCPIP_DHCPV4_OPT_DHCPV4_MSG_LEN)
      {
        /* option TCPIP_DHCPV4_MSG -> message type (DHCPOFFER, DHCPACK, DHCPNAK) */

        *MsgTypePtr = OptPtr[2];                                                                                        /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        retVal = E_OK;
      }
      break;
    }

  case (TCPIP_DHCPV4_OPT_SERVER_ID_TYPE):
    {
      /* #40 Verify the length of SERVER ID option. */
      if(optLen == TCPIP_DHCPV4_OPT_SERVER_ID_LEN)
      {
        /* option SERVER_ID */

        /* Address is stored in host byte-order */
        LocConfigData->DhcpSiaddr = TCPIP_GET_UINT32_RAW(OptPtr, 2u);                                                   /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        retVal = E_OK;
      }
      break;
    }

  case (TCPIP_DHCPV4_OPT_RENEWAL_TIME_T1_VAL_TYPE):
    {
      /* #50 Verify the length of Renewal (T1) Time Value option. */
      if(optLen == TCPIP_DHCPV4_OPT_RENEWAL_TIME_T1_VAL_LEN)
      {
      /* option RENEWAL_TIME_T1 */

        LocConfigData->T1 = TCPIP_GET_UINT32(OptPtr, 2u);                                                               /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        retVal = E_OK;
      }
      break;
    }

  case (TCPIP_DHCPV4_OPT_REBINDING_TIME_T2_VAL_TYPE):
    {
      /* #60 Verify the length of Rebinding (T2) Time Value option. */
      if (optLen == TCPIP_DHCPV4_OPT_REBINDING_TIME_T2_VAL_LEN)
      {
        /* option RENEWAL_TIME_T2 */

        LocConfigData->T2 = TCPIP_GET_UINT32(OptPtr, 2u);                                                               /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        retVal = E_OK;
      }
      break;
    }

#if (TCPIP_SUPPORT_DNS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
  case (TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_TYPE):
    {
      /* #70 Verify the length of Domain Name Server option.*/
      /* option DOMAIN_NAME_SERVER */
      uint8 LocOptLen = OptPtr[1];
      if (((LocOptLen % TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_LEN) == 0u) && (LocOptLen >= TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_LEN))
      {
        DnsServerOptPtr->DnsServerAddrPtr   = (TCPIP_P2C(IpBase_AddrInType))(&OptPtr[2]);  /* PRQA S 0310, 3305 */ /* MD_TCPIP_Rule11.3_0310_3305_AddrList */
        DnsServerOptPtr->DnsServerAddrCount = (uint8)(LocOptLen / TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_LEN);
        retVal = E_OK;
      }
      break;
    }
#endif
  default:
    {
      /* Process recieved user options.*/
      TcpIp_DhcpV4_VHandleRxUserOptions(IpV4CtrlIdx, OptPtr);                                                           /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
      retVal = E_OK;
      break;
    }
  }
  return retVal;
} /* PRQA S 6030 */ /* MD_MSR_STCYC */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_ProcessAckOrNak
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_ProcessAckOrNak(
  TcpIp_IpV4CtrlIterType                                           IpV4CtrlIdx,
  TcpIp_NetAddrType                                                Yiaddr,
  uint8                                                            MsgType,
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2CONST(TcpIp_DhcpV4_DnsOptInfoType, AUTOMATIC, TCPIP_APPL_DATA) DnsServerOptPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);

  switch (MsgType)
  {
  case TCPIP_DHCPV4_DHCPACK:
    {
      uint32 ElapsedSecSinceFirstRequest;
      /* incoming ack for requested IP address */
      /* According to the RFC, the DHCP module SHOULD probe its address before using it for
      IP module configuration. This implementation does not implement this feature! */

      /* #10 Store addresses received from the server On reception of DHCPACK message. */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr      = Yiaddr;                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->DhcpSiaddr  = LocConfigData->DhcpSiaddr;                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->NetMask     = LocConfigData->NetMask;                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->DefGWiaddr  = LocConfigData->DefGWiaddr;                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime   = LocConfigData->LeaseTime;                       /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */

      if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REQUESTING)
      {
        /* Timer was reset before transmission of first DHCPREQUEST message. */
        ElapsedSecSinceFirstRequest = TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx);
      }
      else if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_RENEWING)
      {
        /* First DHCPREQUEST message in state RENEWING was send at T1. */
        ElapsedSecSinceFirstRequest = TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx) - TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T1;
      }
      else
      {
        /* First DHCPREQUEST message in state REBINDING was send at T2. */
        ElapsedSecSinceFirstRequest = TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx) - TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2;
      }

      /* #20 Set timeout T1, if T1 is not zero. */
      if (LocConfigData->T1 != 0u)
      {
        TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T1 = LocConfigData->T1;                                     /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
      else
      {
        /* T1 is 0.5 times the lease time */
        TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T1 = (TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime >> 1);      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
      /* #30 Set timeout T2, if T2 is not zero. */
      if (LocConfigData->T2 != 0u)
      {
       TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2 = LocConfigData->T2;                                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
      else
      {
        /* T2 is 0.875 times the lease time */
        TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2 = TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime
                                                  - (TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime >> 3);/* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }

#if (TCPIP_SUPPORT_DNS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
      /* set DNS server address */
      if (DnsServerOptPtr->DnsServerAddrCount != 0u)
      {
        Dns_UpdateIpV4Servers(DnsServerOptPtr->DnsServerAddrPtr, DnsServerOptPtr->DnsServerAddrCount);
      }
#else
      TCPIP_UNUSED_PARAMETER(DnsServerOptPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
      /* #40 Indicate valid address to IP-module. */
      if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REQUESTING)
      {
        IpV4_Ip_VIpAddrAssignmentReadyNotification(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP, TRUE);
      }

      /* #50 Reset Timer variable to time of first DHCPREQUEST message. (T1 and T2 are relative to this value) */
      TcpIp_SetSecTimerOfDhcpStatus(dhcpStatusIdx, ElapsedSecSinceFirstRequest);                                        /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                   /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      /* set event timer to T1 */
      TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T1);         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      CANOE_WRITE_STRING_2("TcpIp_DhcpV4_RxIndication: next event in %d seconds, last state was %d", TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx), TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx))
      CANOE_WRITE_STRING_2("TcpIp_DhcpV4_RxIndication: event timers are %d seconds and %d milliseconds", TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx), TcpIp_GetMsTimerOfDhcpStatus(dhcpStatusIdx))
      /* switch mode to next state */
      TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_BOUND);                                     /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      break;
    }

  case TCPIP_DHCPV4_DHCPNACK:
    {
      /* incoming NACK (for requested IP address) -> back to INIT */
      if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) != TCPIP_DHCPV4_CTRL_STATE_REQUESTING)
      {
        /* #60 On reception of DHCPNAK, indicate loss of IP address to IP-module. */
        IpV4_Ip_VIpAddrAssignmentReadyNotification(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP, FALSE);
      }
      /* #70 Restart the Address assignment process. */
      TcpIp_DhcpV4_TriggerAddrRequest(IpV4CtrlIdx);
      break;
    }
    /* #80 In case of Default : no other messages should arrive, Ignore them. */
  default:
    {
      /* no other messages should arrive, ignore them */
      break;
    }
  }
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VProcessCtrlState
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VProcessCtrlState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx)
{
  /* ----- Local Variables ----------------------------------------------- */
  IpBase_AddrInType requestedIpAddr;
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  TcpIp_SizeOfDhcpConfigType dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
  switch (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx))
  {
  case TCPIP_DHCPV4_CTRL_STATE_INIT:
    {
      IpV4_DhcpV4RequestedAddrCalloutFuncType RequestedAddrCalloutFuncPtr = TcpIp_GetReqAddrCalloutFuncOfDhcpConfig(dhcpConfigIdx);
      /* #10 [INIT] Send first DHCPDISCOVER message, schedule retransmission and switch to state SELECTING. */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr = IPV4_ADDR_ANY; /* unassign client ip address */      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */

      TcpIp_SetReqIpAddrOfDhcpStatus(dhcpStatusIdx, IPV4_ADDR_ANY);                                                     /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */

      TcpIp_SetSecTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_SetSecElapsedOfDhcpStatus(dhcpStatusIdx, 0);                                                                /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_SetLastDiscoverSecsOfDhcpStatus(dhcpStatusIdx, 0);                                                          /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */

      if (RequestedAddrCalloutFuncPtr != NULL_PTR)
      {
        TcpIp_SizeOfLocalAddrV4Type localAddrId;
        requestedIpAddr = TcpIp_GetReqIpAddrOfDhcpStatus(dhcpStatusIdx);
        /* Idx to Id Mapping */
        localAddrId = TCPIP_LOCAL_ADDR_IDX_TO_ID(TcpIp_GetLocalAddrV4DhcpIdxOfIpV4Ctrl(IpV4CtrlIdx));
        RequestedAddrCalloutFuncPtr(localAddrId, &requestedIpAddr);                                                     /* SBSW_TCPIP_FUNC_PTR_CALL */
        TcpIp_SetReqIpAddrOfDhcpStatus(dhcpStatusIdx, requestedIpAddr);                                                 /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }

      /* send first DISCOVER message */
      if (TcpIp_DhcpV4_VSendDhcpMsg(IpV4CtrlIdx, TCPIP_DHCPV4_MSG_DISCOVER, TCPIP_INADDR_BROADCAST) == E_OK )
      {
        /* TX successful. Switch to state SELECTING */

        TcpIp_SetSecNextIntervalOfDhcpStatus(dhcpStatusIdx, TcpIp_GetDiscoverIntervalMinOfDhcpConfig(dhcpConfigIdx));   /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextIntervalOfDhcpStatus(dhcpStatusIdx));          /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_SELECTING);                               /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
      else
      {
        /* TX failed. Stay in current state and retry in next MainFunction cycle */
      }
      break;
    }

  case TCPIP_DHCPV4_CTRL_STATE_SELECTING:
    {
      /* #20 [SELECTING] Retransmit DHCPDISCOVER message and schedule next retransmission or cancel DHCP assignment if number of retransmission has been reached. */
      /* check if event has to be triggered */
      /* check if another DISCOVER message may be sent */
      TcpIp_DhcpV4_VSelectingState(IpV4CtrlIdx);
      break;
    }

  case TCPIP_DHCPV4_CTRL_STATE_REQUESTING:
    {
      /* #30 [REQUESTING] Send DHCPREQUEST message and schedule next retransmission or cancel DHCP assignment if number of retransmission has been reached. */
      if ((TcpIp_GetRequestMaxNumOfDhcpConfig(dhcpConfigIdx)) > TcpIp_GetRetryCounterOfDhcpStatus(dhcpStatusIdx))
      {
        TcpIp_NetAddrType DhcpServAddr = TCPIP_INADDR_BROADCAST;
        /* send REQUEST message */
        if (TcpIp_DhcpV4_VSendDhcpMsg(IpV4CtrlIdx, TCPIP_DHCPV4_MSG_REQUEST, DhcpServAddr) == E_OK)
        {
          /* TX successful. Schedule next retry if no response is received. */
          TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) + TcpIp_GetRequestIntervalOfDhcpConfig(dhcpConfigIdx));  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
          TcpIp_IncRetryCounterOfDhcpStatus(dhcpStatusIdx);                                                             /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        }
        else
        {
          /* TX failed. Stay in current state and retry in next MainFunction cycle */
        }
      }
      else
      {
        /* cancel complete DHCP address request */
        TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_OFF);                                     /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        TcpIp_SetTimeoutOccurredOfDhcpStatus(dhcpStatusIdx, TRUE);                                                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
      break;
    }

  case TCPIP_DHCPV4_CTRL_STATE_BOUND:
    {
      /* #40 [BOUND] Switch to state RENEWING after T1 timeout has expired. */
      TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_RENEWING);                                  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      /* Value of 'secs' field in DHCP message shall restart at 0 when beginning address renewal process. [RFC2131 page 10] */
      TcpIp_SetSecElapsedOfDhcpStatus(dhcpStatusIdx, 0);                                                                /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_SetLastDiscoverSecsOfDhcpStatus(dhcpStatusIdx, 0);                                                          /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      break;
    }

  case TCPIP_DHCPV4_CTRL_STATE_RENEWING:
    {
      /* #50 [RENEWING] Transmit DHCPREQUEST (unicast) and schedule next retransmission or switch to state REBINDING if T2 timeout has expired. */
      TcpIp_DhcpV4_RenewingState( IpV4CtrlIdx);
      break;
    }

  case TCPIP_DHCPV4_CTRL_STATE_REBINDING:
    {
      TcpIp_DhcpV4_RebindingState( IpV4CtrlIdx);
      break;
    }

  default:
    {
      /* (currently) unhandled state, or nothing to do */
      break;
    }
    /* end of STATE dependend processing ---------------------------------- */
    /* -------------------------------------------------------------------- */
  }
}  /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSelectingState
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VSelectingState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx)
{

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  TcpIp_SizeOfDhcpConfigType dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
   /* #10 Verify if retry limit has reached. */
  if (   (TcpIp_GetDiscoverMaxNumOfDhcpConfig(dhcpConfigIdx) == 0u) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */ /* retry number is not limited */
      || ((TcpIp_GetDiscoverMaxNumOfDhcpConfig(dhcpConfigIdx) - 1u) > TcpIp_GetRetryCounterOfDhcpStatus(dhcpStatusIdx)))  /* retry limit not yet reached */
  {
    /* #20 Send another DISCOVER message. */
    if (TcpIp_DhcpV4_VSendDhcpMsg(IpV4CtrlIdx, TCPIP_DHCPV4_MSG_DISCOVER, TCPIP_INADDR_BROADCAST) == E_OK)
    {
      /* #30 TX is successful. Schedule next retry if no response is received. */
      uint32 nextSecInterval;

      /* #40 Calculate Next interval for DISCOVER message. */
      if (TcpIp_GetSecNextIntervalOfDhcpStatus(dhcpStatusIdx) < TcpIp_GetDiscoverIntervalMaxOfDhcpConfig(dhcpConfigIdx))
      {
        nextSecInterval = TcpIp_GetSecNextIntervalOfDhcpStatus(dhcpStatusIdx) * 2u;
        if (nextSecInterval > TcpIp_GetDiscoverIntervalMaxOfDhcpConfig(dhcpConfigIdx))
        {
          nextSecInterval = TcpIp_GetDiscoverIntervalMaxOfDhcpConfig(dhcpConfigIdx);
        }
        TcpIp_SetSecNextIntervalOfDhcpStatus(dhcpStatusIdx, nextSecInterval);                                           /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
      else
      {
        nextSecInterval = TcpIp_GetSecNextIntervalOfDhcpStatus(dhcpStatusIdx);
      }
      TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) + nextSecInterval);/* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_IncRetryCounterOfDhcpStatus(dhcpStatusIdx);                                                                 /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    }
    else
    {
      /* TX failed. Stay in current state and retry in next MainFunction cycle */
    }
  }
  /* #50 Cancel complete DHCP address request if retry time has reached. */
  else
  {
    TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_OFF);                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetTimeoutOccurredOfDhcpStatus(dhcpStatusIdx, TRUE);                                                          /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  }
}  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_RenewingState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_RenewingState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  TcpIp_SizeOfDhcpConfigType dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
  TCPIP_ASSERT(TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) <= TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2);

  if (TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx) < TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2)
  {
    /* #10 Send unicast DHCP REQUEST if T2 time has not yet expired.*/
    if (TcpIp_DhcpV4_VSendDhcpMsg(IpV4CtrlIdx, TCPIP_DHCPV4_MSG_REQUEST, TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->DhcpSiaddr) == E_OK)
    {
      /* RFC 2131 4.4.5 In RENEWING state, if the client receives no response to its DHCPREQUEST message,
         the client SHOULD wait one-half of the remaining time until T2 (in RENEWING state) down to a minimum of
         configured RenewIntervalMin seconds time, before retransmitting the DHCPREQUEST message.*/

      /* #20 Transmission is successful. Calculate the time for the next event and schedule next retransmission. */
      uint32 timeLeft = (TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2 - TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx));
      /* Verify if time left for retransmission is bigger than Renew interval time */
      if (timeLeft > (uint32)TcpIp_GetRenewIntervalMinOfDhcpConfig(dhcpConfigIdx))
      {
        /* Verify if time left for retransmission is one half of the configured RenewIntervalMin seconds. */
        if (timeLeft > ((uint32)TcpIp_GetRenewIntervalMinOfDhcpConfig(dhcpConfigIdx) * 2u))
        {
          /* Set next event at one half of the time left until T2. */
          TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) + (timeLeft >> 1));/* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        }
        else
        { /* if time left is smaller than half of the minimum configured RenewIntervalMin time, then set next event at RenewIntervalMin.*/
          TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) + TcpIp_GetRenewIntervalMinOfDhcpConfig(dhcpConfigIdx));/* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        }
      }
      else
      { /* When time left is smaller then minimum configured RenewIntervalMin time, then set next event at T2. */
        TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2);       /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
    }
    else
    {
      /* #30 TX failed. Retry in next mainfunction. Stay in current state. */

    }
  }
  else
  {
    /* #40 Switch state to REBINDING if T2 time has expired and update time for next event. */
    TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_REBINDING);                                   /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2);           /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  }
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
/**********************************************************************************************************************
 *  TcpIp_DhcpV4_RebindingState
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_RebindingState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  TcpIp_SizeOfDhcpConfigType dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);

  /* #10 [REBINDING] Check if lease time has not yet expired. */
  if (TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx) < TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime)
  {
    TcpIp_NetAddrType dhcpServAddr = TCPIP_INADDR_BROADCAST;
    /* #20 Send Brodcast DHCP REQUEST. */
    if (TcpIp_DhcpV4_VSendDhcpMsg(IpV4CtrlIdx, TCPIP_DHCPV4_MSG_REQUEST, dhcpServAddr) == E_OK)
    {
      /* #30 Transmission is successful. Schedule next retransmission. */
      uint32 timeLeft = (TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime - TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx));
      /* RFC 2131 4.4.5 In REBINDING state, if the client receives no response to its DHCPREQUEST message,
         the client SHOULD wait one-half of the remaining lease time (in REBINDING state),
         down to a minimum configured RebindIntervalMin seconds, before retransmitting the DHCPREQUEST message.*/
      if (TcpIp_GetRebindIntervalMinOfDhcpConfig(dhcpConfigIdx) < timeLeft)
      {
        if (timeLeft > ((uint32)TcpIp_GetRebindIntervalMinOfDhcpConfig(dhcpConfigIdx) * 2u))
        {
          TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) + (timeLeft >> 1));/* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        }
        else
        {
         TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) + TcpIp_GetRebindIntervalMinOfDhcpConfig(dhcpConfigIdx));  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        }
      }
      else
      {
        TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime);  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
    }
    else
    {
      /* #40 Transmission failed. Retry in next mainfunction. Stay in current state. */
    }
  }
  else
  {
    /* #50 Lease time has just expired. Change state to OFF and update time for next event. */
    CANOE_WRITE_STRING("TcpIp_DhcpV4_MainFunction: lease time has just expired")
    TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_OFF);                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime);    /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetTimeoutOccurredOfDhcpStatus(dhcpStatusIdx, TRUE);                                                          /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    /* #60 Indicate to IP-module about loss of IP address. */
    IpV4_Ip_VIpAddrAssignmentReadyNotification(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP, FALSE);
  }
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VUpdateStatus
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VUpdateStatus(
  TcpIp_SizeOfLocalAddrType                     LocalAddrIdx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)      ErrorIdPtr,
  CONSTP2VAR(uint8, AUTOMATIC, IPV4_APPL_DATA)  DhcpStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Verify that DHCP is configured for this IP controller. */
  TcpIp_SizeOfLocalAddrV4Type localAddrV4Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV4(LocalAddrIdx);
  TcpIp_SizeOfIpV4CtrlType ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(localAddrV4Idx);

  *DhcpStatePtr = 0;                                                                                                    /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
  if (localAddrV4Idx == TcpIp_GetLocalAddrV4DhcpIdxOfIpV4Ctrl(ipV4CtrlIdx))
  {
    TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(ipV4CtrlIdx);
    /* #20 Verify that IP instance is in state ONLINE. */
    if (TcpIp_GetStateOfIpV4CtrlDyn(ipV4CtrlIdx) >= IPV4_IP_ONLINE_PASSIVE)
    {
      retVal = E_OK;
      /* #30 Convert the internal IpV4CtrlIdx-specific status to the simplified status desired by the caller. */
      switch (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx))
      {
      case TCPIP_DHCPV4_CTRL_STATE_OFF:
        /* no break; */
      case TCPIP_DHCPV4_CTRL_STATE_INIT:
        *DhcpStatePtr = TCPIP_DHCP_SIMPLIFIED_STATE_NO_DISCVR_SENT;                                                     /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        break;

      case TCPIP_DHCPV4_CTRL_STATE_SELECTING:
        *DhcpStatePtr = TCPIP_DHCP_SIMPLIFIED_STATE_DISCVR_SENT_NO_ANSWR_RCVD_YET;                                      /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        break;

      case TCPIP_DHCPV4_CTRL_STATE_REQUESTING:
        *DhcpStatePtr = TCPIP_DHCP_SIMPLIFIED_STATE_REQ_SENT_NO_ACK_RCVD_YET;                                           /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        break;

      case TCPIP_DHCPV4_CTRL_STATE_BOUND: /* Address Lease valid. */
        /* no break; */
      case TCPIP_DHCPV4_CTRL_STATE_RENEWING: /* Address Lease valid. */
        /* no break; */
      case TCPIP_DHCPV4_CTRL_STATE_REBINDING: /* Address Lease valid. */
        *DhcpStatePtr = TCPIP_DHCP_SIMPLIFIED_STATE_ACK_RCVD_DHCP_ADDR_ASSIGND;                                         /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        break;

      case TCPIP_DHCPV4_CTRL_STATE_INITREBOOT: /* mode not supported by this DHCP impl. */
        /* no break; */
      case TCPIP_DHCPV4_CTRL_STATE_REBOOTING: /* mode not supported by this DHCP impl. */
        /* no break; */
      default:
        retVal = E_NOT_OK;
        *ErrorIdPtr = IPV4_E_INV_PARAM;                                                                                 /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        break;
      }
    }
    else
    {
      /* DHCP configured but controller not active, i.e. DHCP client must be inactive for sure. */
      *DhcpStatePtr = TCPIP_DHCP_SIMPLIFIED_STATE_NOT_ACTIVE;                                                           /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      retVal = E_OK;
    }
  }
  else
  {
    *ErrorIdPtr = IPV4_E_INV_PARAM;                                                                                     /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
  }
  return retVal;
}
/**********************************************************************************************************************
 *  TcpIp_DhcpV4_GetDhcpMsgLength
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_GetDhcpMsgLength(
  uint8                                     MsgType,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_DATA) DhcpMsgLenPtr,
  TcpIp_SizeOfDhcpStatusType                DhcpStatusIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  switch (MsgType)
  {
  case TCPIP_DHCPV4_MSG_DISCOVER:
    if (TcpIp_GetReqIpAddrOfDhcpStatus(DhcpStatusIdx) != IPV4_ADDR_ANY)
    {
      /* option 50, requested IP address option */
      *DhcpMsgLenPtr += TcpIp_DhcpV4_VAddReqIpAddrOption(NULL_PTR, 0u); /* get length of requested ip address option */  /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_NULL_PTR_ALLOWED */
    }
    break;

  case TCPIP_DHCPV4_MSG_REQUEST:
    if (   (TcpIp_GetCtrlStateOfDhcpStatus(DhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_SELECTING) /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        || (TcpIp_GetCtrlStateOfDhcpStatus(DhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REQUESTING)
      /*  (TCPIP_DHCPV4_CTRL_STATE_INITREBOOT == TcpIp_GetCtrlStateOfDhcpStatus(DhcpStatusIdx)) */ /* mode not supported */ )
    {
      /* #10 Get Length of requested Ip address option 50.*/
      *DhcpMsgLenPtr += TcpIp_DhcpV4_VAddReqIpAddrOption(NULL_PTR, 0u);                                                 /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_NULL_PTR_ALLOWED */
      /* #20 Get Length of Server identifier option 54. */
      *DhcpMsgLenPtr += TcpIp_DhcpV4_VAddServerIdOption(NULL_PTR, 0u);                                                  /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_NULL_PTR_ALLOWED */
    }
    else
    {
      /* TCPIP_DHCPV4_CTRL_STATE_BOUND, TCPIP_DHCPV4_CTRL_STATE_RENEWING */ /* TCPIP_DHCPV4_CTRL_STATE_REBINDING */
    }
    break;

  default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    /* Default case left blank intentionally */
  break;
  }
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSetMsgFlags
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VSetMsgFlags(
  uint8                                     MsgType,
  TcpIp_SizeOfDhcpStatusType                DhcpStatusIdx,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_DATA) OptOfsPtr,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)  OptPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  switch (MsgType)
  {
  case TCPIP_DHCPV4_MSG_DISCOVER:
    if (TcpIp_GetReqIpAddrOfDhcpStatus(DhcpStatusIdx) != IPV4_ADDR_ANY)
    {
      /* option 50, requested IP address option */
      *OptOfsPtr += TcpIp_DhcpV4_VAddReqIpAddrOption(&OptPtr[*OptOfsPtr], TcpIp_GetReqIpAddrOfDhcpStatus(DhcpStatusIdx));/* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_FUNC_CALL_PTR_OPTION */
    }
    break;

  default:  /* TCPIP_DHCPV4_MSG_REQUEST: */
    /* #10 Set the Flag if the message is DHCP request. */
    if (   (TcpIp_GetCtrlStateOfDhcpStatus(DhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_SELECTING)  /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        || (TcpIp_GetCtrlStateOfDhcpStatus(DhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REQUESTING)
      /*  (TCPIP_DHCPV4_CTRL_STATE_INITREBOOT == TcpIp_DhcpV4_RAM_CtrlState(IpV4CtrlIdx)) */ /* mode not supported */ )
    {
      /* option 50, requested IP address option */
      *OptOfsPtr += TcpIp_DhcpV4_VAddReqIpAddrOption(&OptPtr[*OptOfsPtr], TcpIp_GetAddrDataStructOfDhcpStatus(DhcpStatusIdx)->Ciaddr);   /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_FUNC_CALL_PTR_OPTION */
      /* option 54, server identifier option */
      *OptOfsPtr += TcpIp_DhcpV4_VAddServerIdOption(&OptPtr[*OptOfsPtr], TcpIp_GetAddrDataStructOfDhcpStatus(DhcpStatusIdx)->DhcpSiaddr);/* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_FUNC_CALL_PTR_OPTION */
    }
    else
    {
      /* TCPIP_DHCPV4_CTRL_STATE_BOUND, TCPIP_DHCPV4_CTRL_STATE_RENEWING */ /* TCPIP_DHCPV4_CTRL_STATE_REBINDING ?? */
    }
    break;
  }
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSendDhcpMsg
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
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VSendDhcpMsg(
  TcpIp_SizeOfIpV4CtrlType IpV4CtrlIdx,
  uint8                    MsgType,
  TcpIp_NetAddrType        DestAddr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_LocalAddrV4IterType ipV4AddrIdx;
  uint8                 *bufPtr;
  uint16                bufLenByte;
  uint16                udpLenByte;
  uint16                dhcpMsgLen;
  Std_ReturnType        result;
  TcpIp_IpTxRequestDescriptorType ipTxReqestDescr;
  /* UDP */
  IpBase_SockAddrInType dest;

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  dest.sin_family = IPBASE_AF_INET;
  dest.sin_port   = TCPIP_HTONS(TCPIP_DHCPV4_SERVER_PORT);
  dest.sin_addr   = DestAddr;
  /* #10 Send event to the upper layer before sending dhcp message.So that upper layer can write user options using TcpIp_DhcpWriteOption. */
  TcpIp_DhcpV4_VSendEventType(IpV4CtrlIdx, MsgType);

  /* #20 Calculate length of DHCP message. */
  dhcpMsgLen = TCPIP_DHCPV4_MIN_HEADER_LENGTH_BYTE + (TCPIP_DHCPV4_OPTION_HEADER + 1u); /* at least the DHCP header + 'message type' option + 'end' option must be sent. */
  dhcpMsgLen += TcpIp_DhcpV4_VAddParamReqListOpt(IpV4CtrlIdx, NULL_PTR); /* get length of parameter request option */   /* SBSW_TCPIP_NULL_PTR_ALLOWED */

  /* #30 Add message specific option lengths. */
  TcpIp_DhcpV4_GetDhcpMsgLength(MsgType, &dhcpMsgLen, dhcpStatusIdx);                                                   /* SBSW_TCPIP_UPDATE_VARIABLE */


  /* #40 Add user options lengths. */
  dhcpMsgLen += TcpIp_DhcpV4_VAddUserOptions(IpV4CtrlIdx, MsgType, NULL_PTR); /* get length of all user options */      /* SBSW_TCPIP_NULL_PTR_ALLOWED */
  udpLenByte = dhcpMsgLen + 8u;  /* Add UDP Header length */
  bufLenByte = udpLenByte;
  ipV4AddrIdx = TcpIp_GetLocalAddrV4DhcpIdxOfIpV4Ctrl(IpV4CtrlIdx);
# if (TCPIP_SUPPORT_IPSEC == STD_ON)
  /* Store the transport protocol information in the tx descriptor */
  ipTxReqestDescr.XptProtocol = IPV4_IP_PROTOCOL_UDP;

  /* Update the source socket information for IpSec */
  TcpIp_GetAddrLocSockOfIpV4SocketDyn(TcpIp_GetIpV4SocketDynDhcpIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX))->SockAddrIn.sin_family = IPBASE_AF_INET;                            /* SBSW_DHCPV4_LOCSOCKADDR_PTR */
  TcpIp_GetAddrLocSockOfIpV4SocketDyn(TcpIp_GetIpV4SocketDynDhcpIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX))->SockAddrIn.sin_port   = TCPIP_HTONS(TCPIP_DHCPV4_CLIENT_PORT);     /* SBSW_DHCPV4_LOCSOCKADDR_PTR */
  (void)IpV4_Ip_GetLocNetAddr(ipV4AddrIdx, &(TcpIp_GetAddrLocSockOfIpV4SocketDyn(TcpIp_GetIpV4SocketDynDhcpIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX))->SockAddrIn.sin_addr));  /* SBSW_DHCPV4_LOCSOCKADDR_PTR */
# endif
  /* #50 Request IP buffer. */
  if (IpV4_Ip_ProvideTxBuffer(&ipV4AddrIdx, TcpIp_GetIpV4SocketDynDhcpIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX), &dest, &bufPtr, &bufLenByte, &ipTxReqestDescr, FALSE)  == BUFREQ_OK) /* SBSW_TCPIP_UPDATE_VARIABLE */
  {
    /* #60 Build UDP Header. */
    uint8  chaddr[16];
    TCPIP_PUT_UINT16(bufPtr, DHCPV4_SRCPORT_OFS, TCPIP_DHCPV4_CLIENT_PORT);                                             /* SBSW_TCPIP_WRITE_UINT */
    TCPIP_PUT_UINT16(bufPtr, DHCPV4_TGTPORT_OFS, TCPIP_DHCPV4_SERVER_PORT);                                             /* SBSW_TCPIP_WRITE_UINT */
    TCPIP_PUT_UINT16(bufPtr, DHCPV4_LEN_BYTE_OFS, udpLenByte);                                                          /* SBSW_TCPIP_WRITE_UINT */
    TCPIP_PUT_UINT16(bufPtr, DHCPV4_CHECKSUM_OFS, 0u);                                                                  /* SBSW_TCPIP_WRITE_UINT */
    /* Checksum is calculated by lower layer (IPv4) or in hardware) */
    {
      /* Assemble DHCP message into provided tx buffer */
      bufPtr =  &bufPtr[TCPIP_UDP_HDR_LEN_BYTE];/* Skip the Udp Header */
      TCPIP_PUT_UINT8(bufPtr, TCPIP_DHCPV4_FRAME_OPCODE_OFS, TCPIP_DHCPV4_OP_BOOTREQUEST);                              /* SBSW_TCPIP_WRITE_UINT */
      TCPIP_PUT_UINT8(bufPtr, TCPIP_DHCPV4_FRAME_HWADDR_TYPE_OFS, TCPIP_DHCPV4_HW_TYPE_ETH);                            /* SBSW_TCPIP_WRITE_UINT */
      TCPIP_PUT_UINT8(bufPtr, TCPIP_DHCPV4_FRAME_HWADDR_LEN_OFS, TCPIP_PHYS_ADDR_LEN_BYTE);                             /* SBSW_TCPIP_WRITE_UINT */
      TCPIP_PUT_UINT8(bufPtr, TCPIP_DHCPV4_FRAME_HOPS_OFS, 0u);                                                         /* SBSW_TCPIP_WRITE_UINT */

      if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_INIT)
      {
        /* generate new Session ID */
        uint16 RandNo1 = TcpIp_GetRandomNumber();                                                                       /* SBSW_TCPIP_RANDOM_NUMBER_FUNC */
        uint16 RandNo2 = TcpIp_GetRandomNumber();                                                                       /* SBSW_TCPIP_RANDOM_NUMBER_FUNC */
        TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Xid = ((uint32)RandNo1) | (((uint32)RandNo2)<<16);          /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }

      TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_XID_OFS, TCPIP_HTONL(TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Xid));/* SBSW_TCPIP_WRITE_UINT */
      /* Same value should be sent in the 'secs' field of Request as in the last Discover(Before Offer)*/
      if (MsgType == TCPIP_DHCPV4_MSG_DISCOVER)
      {
        TCPIP_PUT_UINT16(bufPtr, TCPIP_DHCPV4_FRAME_SECS_OFS, TcpIp_GetSecElapsedOfDhcpStatus(dhcpStatusIdx));          /* SBSW_TCPIP_WRITE_UINT */
        TcpIp_SetLastDiscoverSecsOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecElapsedOfDhcpStatus(dhcpStatusIdx));           /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
      else
      {
        TCPIP_PUT_UINT16(bufPtr, TCPIP_DHCPV4_FRAME_SECS_OFS, TcpIp_GetLastDiscoverSecsOfDhcpStatus(dhcpStatusIdx));    /* SBSW_TCPIP_WRITE_UINT */
      }

      TCPIP_PUT_UINT16(bufPtr, TCPIP_DHCPV4_FRAME_FLAGS_OFS, 0u);/* message specific flags will be set below */         /* SBSW_TCPIP_WRITE_UINT */

      if (   (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_BOUND)  /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          || (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_RENEWING)
          || (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REBINDING))
      {
        TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_CIADDR_OFS, TCPIP_HTONL(TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr));  /* SBSW_TCPIP_WRITE_UINT */
        /* set client address */
      }
      else
      { /* msg DICOVER, and msg REQUEST in state SELECTING */
        TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_CIADDR_OFS, 0u);                                                    /* SBSW_TCPIP_WRITE_UINT */
      }
      TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_YIADDR_OFS, 0u);                                                      /* SBSW_TCPIP_WRITE_UINT */
      TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_SIADDR_OFS, 0u);                                                      /* SBSW_TCPIP_WRITE_UINT */
      TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_GIADDR_OFS, 0u);                                                      /* SBSW_TCPIP_WRITE_UINT */

      TCPIP_LL_GetPhysAddr(0, &chaddr[0]); /* add mac address to first 6 bytes of 16 byte hardware address field */     /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpBase_Fill(&chaddr[IPBASE_ETH_PHYS_ADDR_LEN_BYTE], 0, sizeof(chaddr) - IPBASE_ETH_PHYS_ADDR_LEN_BYTE); /* fill with 10 byte padding (zeroes) */         /* SBSW_TCPIP_IPBASE_COPY_CALLEE */

      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpBase_Copy(&bufPtr[TCPIP_DHCPV4_FRAME_CLIENT_HW_ADDR_OFS], &chaddr[0], TCPIP_DHCPV4_MSG_LEN_CHADDR);             /* SBSW_TCPIP_IPBASE_COPY_CALLEE */
       /* clear 'server name' field */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpBase_Fill(&bufPtr[TCPIP_DHCPV4_FRAME_SERVER_HOSTNAME_OFS], 0, TCPIP_DHCPV4_MSG_LEN_SNAME);                      /* SBSW_TCPIP_IPBASE_COPY_CALLEE */
      /* clear 'boot file' field */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpBase_Fill(&bufPtr[TCPIP_DHCPV4_FRAME_BOOT_FILE_OFS], 0, TCPIP_DHCPV4_MSG_LEN_BOOTFILE);                         /* SBSW_TCPIP_IPBASE_COPY_CALLEE */

      TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_MAGICPATTERN_OFS, TCPIP_DHCPV4_MAGIC_PATTERN);                        /* SBSW_TCPIP_WRITE_UINT */
      /* Append DHCP options */
      {
        uint8  optLen;
        uint8 *optPtr = &(bufPtr)[TCPIP_DHCPV4_MIN_HEADER_LENGTH_BYTE];
        uint16 optOfs = 0;
        TcpIp_SizeOfIpV4SocketDynType        dhcpIpV4SocketIdx    = TcpIp_GetIpV4SocketDynDhcpIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX);
        TCPIP_P2V(IpV4_Ip_TransferBlockType) ipV4TransferBlockPtr = TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(dhcpIpV4SocketIdx);

        /* option 53, DHCP message type option */
        optLen                                            = TCPIP_DHCPV4_OPT_DHCPV4_MSG_LEN + 2u;
        optPtr[optOfs+TCPIP_DHCPV4_OPTION_FIELD_OFS_CODE] = TCPIP_DHCPV4_OPT_DHCPV4_MSG_TYPE;                           /* SBSW_TCPIP_LOCAL_PTR_UPDATE */
        optPtr[optOfs+TCPIP_DHCPV4_OPTION_FIELD_OFS_LEN]  = TCPIP_DHCPV4_OPT_DHCPV4_MSG_LEN;                            /* SBSW_TCPIP_LOCAL_PTR_UPDATE */
        optPtr[optOfs+TCPIP_DHCPV4_OPTION_FIELD_OFS_TYPE] = MsgType;                                                    /* SBSW_TCPIP_LOCAL_PTR_UPDATE */
        optOfs           += optLen; /* Set Option pointer offset to the next option. */

        optOfs += TcpIp_DhcpV4_VAddParamReqListOpt(IpV4CtrlIdx, &optPtr[optOfs]);                                       /* SBSW_TCPIP_FUNC_CALL_LOCAL_PTR_OPTION */
        /* #70 Set message specific flags and options. */
        TcpIp_DhcpV4_VSetMsgFlags(MsgType, dhcpStatusIdx, &optOfs, optPtr);                                             /* SBSW_TCPIP_FUNC_CALL_LOCAL_PTR_OPTION */ /* SBSW_TCPIP_UPDATE_VARIABLE */
        TCPIP_PUT_UINT16(bufPtr, TCPIP_DHCPV4_FRAME_FLAGS_OFS, TCPIP_DHCPV4_FLAGS_BROADCAST);                           /* SBSW_TCPIP_WRITE_UINT */

        if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) < TCPIP_DHCPV4_CTRL_STATE_BOUND) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        {
          /* DHCP messages broadcast by a client prior to that client obtaining
             its IP address must have the source address field in the IP header
             set to 0. [RFC2131 4.1 Constructing and sending DHCP messages] */
          IPV4_SET_FLAG_U8(ipV4TransferBlockPtr->Flags, IPV4_IP_TRANSFER_BLOCK_FLAG_ZERO_SRC_ADDR);                     /* SBSW_TCPIP_LOCAL_PTR_UPDATE */
        }
        else
        {
          IPV4_CLR_FLAG_U8(ipV4TransferBlockPtr->Flags, IPV4_IP_TRANSFER_BLOCK_FLAG_ZERO_SRC_ADDR);                     /* SBSW_TCPIP_LOCAL_PTR_UPDATE */
        }
        /* add user options */
        optOfs += TcpIp_DhcpV4_VAddUserOptions(IpV4CtrlIdx, MsgType, &optPtr[optOfs]);                                  /* SBSW_TCPIP_FUNC_CALL_LOCAL_PTR_OPTION */
        /* option 255, end option */
        optPtr[optOfs]  = TCPIP_DHCPV4_OPT_END_TYPE;                                                                    /* SBSW_TCPIP_LOCAL_PTR_UPDATE */
        optOfs++;

#if ( TCPIP_DEV_ERROR_REPORT == STD_ON )
        /* #80 Check that created message is as long as calculated at beginning of this function. */
        if ((TCPIP_DHCPV4_MIN_HEADER_LENGTH_BYTE + optOfs) != dhcpMsgLen)
        {
          TcpIp_CallDetReportError(TCPIP_DHCPV4_API_ID_V_SEND_DHCP_MSG, TCPIP_E_INV_ARG);
        }
#else
        TCPIP_DUMMY_STATEMENT(optOfs);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
      }
    }
    /* #90 Transmit the data, if Ip buffer request is successful. */
    if (TCPIP_OK == IpV4_Ip_Transmit(&ipTxReqestDescr, udpLenByte, TCPIP_PROTOCOL_UDP, FALSE, 0, FALSE))                /* SBSW_TCPIP_UPDATE_VARIABLE */
    {
      CANOE_WRITE_STRING_1("TcpIp_DhcpV4_VSendDhcpMsg: DHCP message sent with %d byte", udpLenByte);
      result = E_OK;
    }
    else
    {
      result = E_NOT_OK;
      /* if TcpIp_ProvideTxBuffer(), TcpIp_TransmitTo() may not fail */
    }
  }
  else
  {
    result = E_NOT_OK;
  }
  return result;
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VGetTxOption
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VGetTxOption(
    TcpIp_LocalAddrV4IterType                LocalAddrV4Idx,
    uint8                                    OptCode,
    P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptLenPtr,
    P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_SizeOfIpV4CtrlType ipV4CtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());
  ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);

  if (TcpIp_GetLocalAddrV4DhcpIdxOfIpV4Ctrl(ipV4CtrlIdx) == LocalAddrV4Idx)
  {
    TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
    TcpIp_SizeOfDhcpHostnameType dhcpHostNameIndex;

    TCPIP_ASSERT(IpV4_Ip_VCfgGetAddrAssignmentPrio(ipV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP) != 0u);

    dhcpHostNameIndex = TcpIp_GetDhcpHostnameStartIdxOfIpV4Ctrl(ipV4CtrlIdx);
    dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(ipV4CtrlIdx);

    /* #10 Verify if Option Code is FQDN. */
    if ((OptCode == TCPIP_DHCPV4_OPT_ID_CLIENT_FQDN) && (TcpIp_IsDhcpHostnameUsedOfIpV4Ctrl(ipV4CtrlIdx) == TRUE)) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    {
      if (*OptLenPtr >= TcpIp_GetHostNameLenOfDhcpStatus(dhcpStatusIdx))
      {
        /* #20 Copy length and host name, if the Option Code is correct. */
        *OptLenPtr = TcpIp_GetHostNameLenOfDhcpStatus(dhcpStatusIdx);                                                   /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        if (*OptLenPtr > 0u)
        {
          /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
          IpBase_Copy((IpBase_CopyDataType*)OptPtr, (const IpBase_CopyDataType*)TcpIp_GetAddrDhcpHostname(dhcpHostNameIndex), *OptLenPtr); /* SBSW_TCPIP_FUNC_CALL_IpBase_Copy */
        }
        retVal = E_OK;
      }
    }
    /* #30 Read other user options. */
    else
    {
      retVal = TcpIp_DhcpV4_VGetUserOptions(ipV4CtrlIdx, OptCode, OptLenPtr, OptPtr);                                   /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
    }
  }
  return retVal;
} /* End of TcpIp_DhcpV4_VGetTxOption() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VLookUpOptionIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(TcpIp_DhcpUserOptionIterType, TCPIP_CODE) TcpIp_DhcpV4_VLookUpOptionIdx(
  TcpIp_IpV4CtrlIterType                  IpV4CtrlIdx,
  uint8                                   OptCode)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_DhcpUserOptionIterType dhcpUserOptIdx;
  boolean flag;
  /* ----- Implementation ----------------------------------------------- */
  flag = FALSE;
  /* #10 Iterate over all configured user options. */
  for (dhcpUserOptIdx = TcpIp_GetDhcpUserOptionStartIdxOfIpV4Ctrl(IpV4CtrlIdx); dhcpUserOptIdx < TcpIp_GetDhcpUserOptionEndIdxOfIpV4Ctrl(IpV4CtrlIdx); dhcpUserOptIdx++)
  {
    /* #20 Verify if Option code is valid. */
    if (OptCode == TcpIp_GetCodeOfDhcpUserOption(dhcpUserOptIdx))
    {
      flag = TRUE;
      /* #30 Return userOptIdx to caller function. */
      break;
    }
  }
  if (flag == FALSE)
  {
    dhcpUserOptIdx = TCPIP_DHCPV4_OPT_IDX_INVALID;
  }
  return dhcpUserOptIdx;
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSetTxOption
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VSetTxOption(
  TcpIp_LocalAddrV4IterType                  LocalAddrV4Idx,
  uint8                                      OptCode,
  uint8                                      OptLen,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptPtr,
  uint8                                      MsgTypes)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_SizeOfIpV4CtrlType ipV4CtrlIdx;
  /* ----- Implementation ----------------------------------------------- */
  /* Currently the implementation is limited to one option that is always sent, but the API is already prepared to do a more generic handling */
  IPV4_UNUSED_PARAMETER(MsgTypes);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());

  ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);

  if (TcpIp_GetLocalAddrV4DhcpIdxOfIpV4Ctrl(ipV4CtrlIdx) == LocalAddrV4Idx)
  {
    TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
    TcpIp_SizeOfDhcpConfigType dhcpConfigIdx;
    TcpIp_SizeOfDhcpHostnameType dhcpHostNameIndex;

    TCPIP_ASSERT(IpV4_Ip_VCfgGetAddrAssignmentPrio(ipV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP) != 0u);

    dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(ipV4CtrlIdx);
    dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(ipV4CtrlIdx);
    dhcpHostNameIndex = TcpIp_GetDhcpHostnameStartIdxOfIpV4Ctrl(ipV4CtrlIdx);

    if ((OptCode == TCPIP_DHCPV4_OPT_ID_CLIENT_FQDN) && (TcpIp_IsDhcpHostnameUsedOfIpV4Ctrl(ipV4CtrlIdx) == TRUE)) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    {
      /* An old API for setting a host name was TcpIp_DhcpV4_SetHostName(). */
      /* #10 Verify Host name length. */
      if (OptLen <= TcpIp_GetHostNameLenMaxOfDhcpConfig(dhcpConfigIdx))
      {
        /* #20 Copy length and host name, if Option Code and length are valid. */
        TcpIp_SetHostNameLenOfDhcpStatus(dhcpStatusIdx, OptLen);                                                        /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IpBase_Copy(TcpIp_GetAddrDhcpHostname(dhcpHostNameIndex), (const IpBase_CopyDataType*)OptPtr, OptLen);          /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */ /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        retVal = E_OK;
      }
    }
    else
    {
      retVal = TcpIp_DhcpV4_VSetUserOptions(ipV4CtrlIdx, OptCode, OptLen, OptPtr);                                      /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
    }
  }
  return retVal;
} /* End of TcpIp_DhcpV4_VSetTxOption() */  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddUserOptions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */

STATIC FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV4_VAddUserOptions(
  TcpIp_SizeOfIpV4CtrlType                 IpV4CtrlIdx,
  uint8                                    MsgType,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) MsgDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 msgDataOfs = 0;
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;

  /* ----- Implementation ----------------------------------------------- */
  dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);

  /* Check if FQDN-Option is supported, and this option is sent in all DHCP messages */
  if (TcpIp_GetHostNameLenOfDhcpStatus(dhcpStatusIdx) > 0u)
  {
    if (MsgDataPtr != NULL_PTR)
    {
      TcpIp_SizeOfDhcpHostnameType dhcpHostNameIndex = TcpIp_GetDhcpHostnameStartIdxOfIpV4Ctrl(IpV4CtrlIdx);

      /* #10 Copy the option to the buffer. */
      MsgDataPtr[TCPIP_DHCPV4_OPT_FQDN_CODE] = TCPIP_DHCPV4_OPT_ID_CLIENT_FQDN;  /* option id */                        /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      MsgDataPtr[TCPIP_DHCPV4_OPT_FQDN_LEN]  = TcpIp_GetHostNameLenOfDhcpStatus(dhcpStatusIdx) + TCPIP_DHCPV4_OPT_FQDN_CODE_RC1_RC2_DNLEN;  /* option length */ /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      /* IPv4
          0 1 2 3 4 5 6 7(LSB)
         +-+-+-+-+-+-+-+-+
         |  MBZ  |N|E|O|S|
         +-+-+-+-+-+-+-+-+
         S = 0   the server SHOULD NOT perform the A RR (FQDN-to-address) DNS updates (LSB)
         O = 0   must be 0
         E = 1   canonical wire format/ binary encoding represented as 8 bit ascii instead of 7 bit ascii.
         N = 1   the server SHOULD NOT perform any DNS updates
      */
      MsgDataPtr[TCPIP_DHCPV4_OPT_FQDN_FLAGS] = 0x0Cu;  /* set flags N and E */                                         /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      MsgDataPtr[TCPIP_DHCPV4_OPT_FQDN_RCODE1] = 0u;     /* RCODE1, is always 0 */                                      /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      MsgDataPtr[TCPIP_DHCPV4_OPT_FQDN_RCODE2] = 0u;     /* RCODE2, is always 0 */                                      /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */

      MsgDataPtr[TCPIP_DHCPV4_OPT_FQDN_DOMAIN_NAME_LEN] = TcpIp_GetHostNameLenOfDhcpStatus(dhcpStatusIdx); /* Length of label */  /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpBase_Copy((IpBase_CopyDataType*)&MsgDataPtr[TCPIP_DHCPV4_OPT_FQDN_DOMAIN_NAME],                                 /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
                  (const IpBase_CopyDataType*)TcpIp_GetAddrDhcpHostname(dhcpHostNameIndex),
                  TcpIp_GetHostNameLenOfDhcpStatus(dhcpStatusIdx));  /* option data */
    }
    /* #20 Update the total length of the user options. */
    msgDataOfs = TCPIP_DHCPV4_OPT_FQDN_DOMAIN_NAME + (uint16) TcpIp_GetHostNameLenOfDhcpStatus(dhcpStatusIdx);  /* update the offset */
  }

  /* Check if User options are configured for given IpV4 controller.*/
  if(TcpIp_IsDhcpUserOptionUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    TcpIp_DhcpUserOptionIterType dhcpUserOptIdx;
    TcpIp_DhcpUserOptionBufferIterType userOptBufIdx;
    /* Iterate over all configured User options.*/
    for (dhcpUserOptIdx = TcpIp_GetDhcpUserOptionStartIdxOfIpV4Ctrl(IpV4CtrlIdx); dhcpUserOptIdx < TcpIp_GetDhcpUserOptionEndIdxOfIpV4Ctrl(IpV4CtrlIdx); dhcpUserOptIdx++)
    {
      if ((TcpIp_GetLengthOfDhcpUserOptionDyn(dhcpUserOptIdx) > 0u) && (TcpIp_GetDirectionOfDhcpUserOption(dhcpUserOptIdx) == TCPIP_DHCP_USER_OPTION_TX)) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      {
        userOptBufIdx = TcpIp_GetDhcpUserOptionBufferStartIdxOfDhcpUserOption(dhcpUserOptIdx);
        if (MsgDataPtr != NULL_PTR)
        {
          /* For DHCPv4 the code and the length fields are limited to uint8. (In DHCPv6 it is a uint16 value). But Data structure is generated common for both as uint16 */
          MsgDataPtr[msgDataOfs /* + TCPIP_DHCPV4_USER_OPT_CODE_OFS */] = (uint8)TcpIp_GetCodeOfDhcpUserOption(dhcpUserOptIdx); /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
          MsgDataPtr[msgDataOfs + TCPIP_DHCPV4_USER_OPT_LEN_OFS] = (uint8)TcpIp_GetLengthOfDhcpUserOptionDyn(dhcpUserOptIdx);   /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
          /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
          IpBase_Copy((IpBase_CopyDataType*)&MsgDataPtr[msgDataOfs + TCPIP_DHCPV4_USER_OPT_DATA_OFS],                   /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
                      (const IpBase_CopyDataType*)TcpIp_GetAddrDhcpUserOptionBuffer(userOptBufIdx),
                      TcpIp_GetLengthOfDhcpUserOptionDyn(dhcpUserOptIdx));
        }
        msgDataOfs += TCPIP_DHCPV4_USER_OPT_DATA_OFS + TcpIp_GetLengthOfDhcpUserOptionDyn(dhcpUserOptIdx); /* increment the offset */
      }
    }
  }

  IPV4_UNUSED_PARAMETER(MsgType);  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  return msgDataOfs;
} /* End of TcpIp_DhcpV4_VAddUserOptions() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddReqIpAddrOption
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4_VAddReqIpAddrOption(
    P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptPtr,
    IpBase_AddrInType                       Yiaddr)
{
  /* ----- Implementation ----------------------------------------------- */
  if (OptPtr != NULL_PTR)
  { /* #10 Write your Ip address(Client address) to update option pointer. */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_CODE] = TCPIP_DHCPV4_OPT_REQ_IP_ADDR_TYPE;                                     /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_LEN]  = TCPIP_DHCPV4_OPT_REQ_IP_ADDR_LEN;                                      /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */

    TCPIP_PUT_UINT32(OptPtr, 2u, TCPIP_HTONL(Yiaddr));                                                                  /* SBSW_TCPIP_WRITE_UINT */
  }
  /* #20 Return the calculated length only. */
  return (2u + TCPIP_DHCPV4_OPT_REQ_IP_ADDR_LEN);
} /* End of TcpIp_DhcpV4_VAddReqIpAddrOption() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddServerIdOption
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */

STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4_VAddServerIdOption(
    P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptPtr,
    IpBase_AddrInType                       Siaddr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify if Option pointer is valid. */
  if (OptPtr != NULL_PTR)
  { /* #20 Update Option Pointer with server Id information. */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_CODE] = TCPIP_DHCPV4_OPT_SERVER_ID_TYPE;                                       /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_LEN]  = TCPIP_DHCPV4_OPT_SERVER_ID_LEN;                                        /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    TCPIP_PUT_UINT32(OptPtr,2, TCPIP_HTONL(Siaddr));                                                                    /* SBSW_TCPIP_WRITE_UINT */
  }
  /* #30 Return the calculated length only. */
  return (2u + TCPIP_DHCPV4_OPT_SERVER_ID_LEN);
} /* End of TcpIp_DhcpV4_VAddServerIdOption() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddParamReqListOpt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */

STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4_VAddParamReqListOpt(
  TcpIp_SizeOfIpV4CtrlType                IpV4CtrlIdx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_DhcpUserOptionIterType cnt_RqOpt = 0;
  uint8 OptLen;
  /* ----- Implementation ----------------------------------------------- */
  OptLen = TCPIP_DHCPV4_PARAM_SUBNET_ROUTER_DOMAIN_BYTE;
 /* #10 Verify if Option pointer is valid. */
  if (OptPtr != NULL_PTR)
  { /* #20 Update Option pointer with Parameter Request List Option informations. */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_CODE]   = TCPIP_DHCPV4_OPT_PARAM_REQ_LIST_TYPE;                                /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_LEN]    = OptLen; /* Update Option length */                                   /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_TYPE]   = TCPIP_DHCPV4_OPT_SUBNET_MASK_TYPE;                                   /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_TYPE + 1u] = TCPIP_DHCPV4_OPT_ROUTER_TYPE;                                     /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_TYPE + 2u] = TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_TYPE;                         /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
  }

  if (TcpIp_IsDhcpUserOptionUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    TcpIp_DhcpUserOptionIterType dhcpUserOptIdx;

    for (dhcpUserOptIdx = TcpIp_GetDhcpUserOptionStartIdxOfIpV4Ctrl(IpV4CtrlIdx); dhcpUserOptIdx < TcpIp_GetDhcpUserOptionEndIdxOfIpV4Ctrl(IpV4CtrlIdx); dhcpUserOptIdx++)
    {
      if (TcpIp_GetDirectionOfDhcpUserOption(dhcpUserOptIdx) == TCPIP_DHCP_USER_OPTION_RX_REQUESTED)
      {
        if (OptPtr != NULL_PTR)
        {
          OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_TYPE + OptLen + cnt_RqOpt] = (uint8)TcpIp_GetCodeOfDhcpUserOption(dhcpUserOptIdx); /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
          OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_LEN] = (uint8)(OptLen + 1u + cnt_RqOpt);                                 /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        }
        cnt_RqOpt++;
      }
    }
  }
  OptLen = (uint8)(TCPIP_DHCPV4_PARAM_SUBNET_ROUTER_DOMAIN_BYTE + cnt_RqOpt);
  /* #30 Return the calculated length only. */
  return (TCPIP_DHCPV4_OPTION_HDR_BYTE + OptLen);
} /* end of TcpIp_DhcpV4_VAddParamReqListOpt() */

  /**********************************************************************************************************************
  *  TcpIp_DhcpV4_Clear_UserOptions
  *********************************************************************************************************************/
  /*!
  * Internal comment removed.
 *
 *
  */
 STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_Clear_UserOptions(TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_DhcpUserOptionIterType dhcpUserOptIdx;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over user options and clear option length. */
    for (dhcpUserOptIdx = TcpIp_GetDhcpUserOptionStartIdxOfIpV4Ctrl(IpV4CtrlIdx); dhcpUserOptIdx < TcpIp_GetDhcpUserOptionEndIdxOfIpV4Ctrl(IpV4CtrlIdx); dhcpUserOptIdx++)
    {
      TcpIp_SetLengthOfDhcpUserOptionDyn(dhcpUserOptIdx, 0u);                                                           /* SBSW_TCPIP_DHCPV4_CLEAR_USEROPTIDX_CALLEE */
    }
} /* end of TcpIp_DhcpV4_Clear_UserOptions() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_GetStatus
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_GetStatus(
    TcpIp_LocalAddrIdType                        LocalAddrId,
    CONSTP2VAR(uint8, AUTOMATIC, IPV4_APPL_DATA) DhcpStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal = E_NOT_OK;
  uint8                   errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Verify that IpV4 is initialized. */
  if (IpV4_State != IPV4_STATE_INIT)
  {
    errorId = IPV4_E_NOT_INITIALIZED;
  }
  /* #20 Verify that DhcpStatePtr is a valid pointer. */
  else if (DhcpStatePtr == NULL_PTR)
  {
    errorId = IPV4_E_INV_POINTER;
  }
  /* #30 Verify if LocalAddrId is a valid parameter. */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId))
  {
    errorId = IPV4_E_INV_PARAM;
  }
  else
#endif
  {
    TcpIp_SizeOfLocalAddrType localAddrIdx = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId);

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
    if (!TCPIP_LOCAL_ADDR_IDX_IS_IPV4(localAddrIdx))
    {
      errorId = IPV4_E_INV_PARAM;
    }
    /* ----- Implementation ----------------------------------------------- */
    else
#endif
    {
      /* #40 If all Parameters are valid, Call the function to update the status. */
      retVal = TcpIp_DhcpV4_VUpdateStatus( localAddrIdx, &errorId, DhcpStatePtr);                                       /* SBSW_TCPIP_UPDATE_VARIABLE */ /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
    }
  } /* else: DHCP not configured, i.e. invalid condition to call this API: Leave retVal E_NOT_OK */

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(IPV4_MODULE_ID, IPV4_VINSTANCE_ID, TCPIP_DHCPV4_API_ID_GET_STATUS, errorId);
  }
#else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
  return retVal;
}

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*
   MICROSAR global MISRA deviations:
   - see file 'WI_MISRA_Compliance_MSR.pdf'

   Justification for module-specific MISRA deviations:

   module global deviations -> see file TcpIp.c

   DHCP-specific deviations:
   MD_TCPIP_DHCPV4_14.6_0771_a:
     Reason:     The break statement is used multiple (two) times because parsing a received DHCP message can have
                 multiple fail conditions that should cause stops.
                 Using breaks makes the code much easier to unterstand.
     Risk:       Unstructured code should be avoided.
     Prevention: Covered by code review.

   MD_TCPIP_DHCPV4_14.5_0770: A continue statement has been used.
     Reason:     Avoiding continue statement here would decrease the code readability.
     Risk:       None.
     Prevention: Covered by code review.

*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_TCPIP_DHCP_OPTIONS_OFFSET
    \DESCRIPTION        Dhcp Options are divided in 3 parts: Code,Length of Data and Data.
                                Code |  Len|    Data               |
                               +-----+-----+-----+-----+-----+-----+
                               |  1  |  4  |  m1 |  m2 |  m3 |  m4 |
                               +-----+-----+-----+-----+-----+-----+
                        optPtr is set to the first byte of Dhcp options,i.e. Code. Once the optPtr is set it is used as optPtr[0] = Code, optPtr[1] = Len,
                        optPtr[3] = first byte of Data.
                        Option length is calculated  as optLen = TCPIP_DHCPV4_OPTION_HDR_BYTE + optPtr[1]
                        i.e. first 2 bytes(code + len) + the value stored at 2nd byte (OptPtr[1]).
                        According to the calculated Optlen code, Length and following data bytes are valid to write (Value stored at Len field =  number of bytes are written into the optPtr at the position of optOfs follwing Len field).
                        Exactly that many number of bytes are written into the memory location reserved for dhcp options Data. Caller or Callee ensures that.
                        Ex. In above diagrame value stored at position Len is 4. That's why next 4 bytes of memory location after Len field is valid and can be written.
                        Thats why it is always a valid optOfs.
    \COUNTERMEASURE \N  OptPtr must set properly as described above. Local function or Caller must ensure that it is a valid pointer and points to the right memory location.

  \ID SBSW_TCPIP_DHCP_VSendDhcpMsg
    \DESCRIPTION        TcpIp_DhcpV4_VAddUserOptions and TcpIp_DhcpV4_VAddParamReqListOpt functions are called two times inside the VSendDhcpMsg
                        1. To calculate the option length.
                        2. To update the buffer.
                        After the first call the buffer and calculated option length + Udp Header length, first passed to the function IpV4_Ip_ProvideTxBuffer().
                        If this function retuns BUFREQ_OK then only the buffer will be updated othewise not.
    \COUNTERMEASURE \N  Validity of the parameters are ensured by the caller.

  \ID SBSW_TCPIP_FUNC_CALL_LOCAL_PTR_OPTION
    \DESCRIPTION        A Pointer is passed to the function as function argument
                        Local pointer is created inside this function and ensured that the pointer is valid and points to the valid memory location as described in
                        SBSW_TCPIP_DHCP_OPTIONS_OFFSET and SBSW_TCPIP_DHCP_VSendDhcpMsg.
    \COUNTERMEASURE \N  Validity of the pointer is ensured by the caller.

  \ID SBSW_TCPIP_FUNC_CALL_PTR_OPTION
    \DESCRIPTION        A Pointer is passed to the function as function argument
                        A function argument pointer is passed to this callee. Validity of this pointer is ensured by the caller as described in
                        SBSW_TCPIP_DHCP_OPTIONS_OFFSET
    \COUNTERMEASURE \N  The callee ensures that the pointer parameter is not NULL_PTR and points to a valid memory location.

  \ID SBSW_TCPIP_FUNC_CALL_IpBase_Copy
    \DESCRIPTION        A Pointer is passed to the function as function argument
                        A function argument pointer is passed to this callee. Validity of this pointer is ensured by the caller.
                        OptLenPtr is set to the HostNameLenOfDhcpStatus/ LengthOfDhcpUserOptionDyn using csl macro before passing it to the function to make sure that only that much of bytes are copied.
    \COUNTERMEASURE \N  The caller ensures that the pointer parameter are valid.

  \ID SBSW_TCPIP_DHCPSTATUS_DHCPCONFIG_IDX_INDIRECTION_CONSTRAINT
    \DESCRIPTION        Index  derivation to access DhcpConfig or DhcpStatus elements.
                        Validity of the index value(s) of the modelled indirection(s) [is|are] checked using one of the following functions:
                        1. TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx)
                        2. TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx)
                        If one of these checks indicates a valid indirection, both indirections can be used to access the corresponding arrays.
                        Both functions will always return the identical result. Thats why any of the above mentioned check is enough in order to access the DhcpConfig or DhcpStatus elements.
    \COUNTERMEASURE \M  Index is obtained by indirection (qualified use-case CSL03 of ComStackLib) and presence of one of the mentioned checks or corresponding CONSTRAINT at function declaration.
                        CM_TCPIP_DHCPV4_CONFIG_AND_STATUS

  \ID SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER
    \DESCRIPTION        A CSL modelled RAM array is written using an index that is determined using one (or more) modelled indirections according to CSL03.
                        The first index for the lookup(s) is provided and checked by the caller of the function to be within the valid range by using the associated TcpIp_GetSizeOf...() function.
                        Validity of the index value(s) of the modelled indirection(s) [is|are] checked according to SBSW_TCPIP_DHCPSTATUS_DHCPCONFIG_IDX_INDIRECTION_CONSTRAINT by the caller.
    \COUNTERMEASURE \N  Index is obtained by indirection (qualified use-case CSL03 of ComStackLib) of function
                        argument. The valid range of the function argument is defined at the function declaration and
                        has to be ensured by the calling function.

  \ID SBSW_TCPIP_CSL03_IDX_CALLEE
    \DESCRIPTION        A CSL modelled RAM array is written using an index that is determined using one (or more) modelled indirections according to CSL03.
                        The first index for the lookup(s) is created locally and checked inside the local function to be within the valid range by using the associated TcpIp_GetSizeOf...() function.
                        Validity of the index value(s) of the modelled indirection(s) [is|are] checked according to SBSW_TCPIP_DHCPSTATUS_DHCPCONFIG_IDX_INDIRECTION_CONSTRAINT.
                        Memory location accessed using this valid index is always valid
    \COUNTERMEASURE \N  Index is obtained by indirection (qualified use-case CSL03 of ComStackLib) of a local variable.

  \ID SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER
    \DESCRIPTION        Pointer is updated inside the local function without validity check.
                        In case of optPtr and offset, Update is carried out as explained in SBSW_TCPIP_DHCP_OPTIONS_OFFSET
    \COUNTERMEASURE \N  Pointer is passed as a function argument and is updated considering a valid pointer.
                        The validity of the pointer is ensured by the caller.

 \ID SBSW_TCPIP_FUNC_PARAM_PTR_CALLEE
    \DESCRIPTION        Pointer is updated inside the local function without validity check.
    \COUNTERMEASURE \N  Pointer is passed as a function argument to update it.
                        The validity of the pointer is ensured by the callee. Pointer parameter is checked against NULL_PTR within callee function and handled properly.

  \ID SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER
    \DESCRIPTION        Pointer is passed as a function argument in order to update it.
                        Pointer is a function argument and passed to the callee function considering a valid pointer.
    \COUNTERMEASURE \N  The validity of the pointer is ensured by the caller.

  \ID SBSW_TCPIP_WRITE_DHCPHOSTNAME
    \DESCRIPTION         A CSL modelled RAM array is written using an index that is determind as described below:
                         DataLen is checked against the maximum allowed length for the dhcp hostname.
                         hostnameByteOfs is set to the start index of the hostname using TcpIp_GetDhcpHostnameStartIdxOfIpV4Ctrl(IpV4CtrlIdx) csl macro.
                         dataIdx is iterated over for loop until (DataLen - 1). So the Index is (hostnameByteOfs + dataIdx). Thats why it is secured to write at the memory location using calculated index.
    \COUNTERMEASURE \R  Validity of the index is ensured by the local function.

  \ID SBSW_TCPIP_LOCAL_PTR_UPDATE
    \DESCRIPTION        Pointer is updated inside the local function.
                        As explained in SBSW_TCPIP_DHCP_OPTIONS_OFFSET optPtr is set at the beginning of options and only
                        that much of bytes are written into the optPtr at accordingly incremented offset as given in Length field of option format.
    \COUNTERMEASURE \N  A Local pointer is created inside a local function.

  \ID SBSW_TCPIP_WRITE_UINT
    \DESCRIPTION       The function writes 1/2/4 bytes beginning at the position in the buffer provided by the caller as stated in CM_TCPIP_DHCPV4_IPV4_IP_PROVIDETXBUFFER.
                       TcpIp_WriteUInt8(): 1
                       TcpIp_WriteUInt16(): 2
                       TcpIp_WriteUInt32(): 4
    \COUNTERMEASURE \N The caller ensures that there are 1/2/4 bytes available at &BufPtr[BufPos].

  \ID SBSW_TCPIP_IPBASE_COPY_CALLEE
    \DESCRIPTION        Array is passed to the function as argument to update it.
    \COUNTERMEASURE \N  The caller ensures that the Proper size of array is created and points to the valid memory location.
                        The size of array is passed to the callee function in order to make sure that the array is updated  only for the given size as stated in
                        CM_TCPIP_DHCPV4_IPV4_IP_PROVIDETXBUFFER.

  \ID SBSW_TCPIP_DHCPV4_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR
    \DESCRIPTION        Array is passed as a parameter to the function.
                        Local array  of TCPIP_PHYS_ADDR_LEN_BYTE length is created inside the caller function.
                        The validity of the parameter is ensured by the caller.
    \COUNTERMEASURE \N  Validity is ensured by the caller.

  \ID SBSW_TCPIP_DHCPV4_CLEAR_USEROPTIDX_CALLEE
    \DESCRIPTION        A CSL modelled RAM array is written using an index that is determined using one (or more) modelled indirections CSL03.
                        The first index "userOptIdx" for the lookup(s) is created locally and updated only if (TcpIp_IsDhcpUserOptionUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE).
                        userOptIdx is then validated using TcpIp_GetDhcpUserOptionStartIdxOfIpV4Ctrl(IpV4CtrlIdx) and TcpIp_GetDhcpUserOptionEndIdxOfIpV4Ctrl(IpV4CtrlIdx) before usage.
                        Memory location accessed using this valid index is always valid.
    \COUNTERMEASURE \N  Index is obtained by indirection (qualified use-case CSL03 of ComStackLib) of a function parameter.

  \ID SBSW_TCPIP_CSL03_USEROPTIDX_CALLEE
    \DESCRIPTION        A CSL modelled RAM array is written using an index that is determined using one (or more) modelled indirections according to CM_TCPIP_DHCPV4_VLOOKUPOPTIONIDX_CONSTRAINT.
                        The first index for the lookup(s) is created locally and updated as stated in CM_TCPIP_DHCPV4_VLOOKUPOPTIONIDX_CONSTRAINT.
                        Memory location accessed using this valid index is always valid.
    \COUNTERMEASURE \N  Index is obtained by indirection (qualified use-case CSL03 of ComStackLib) of a function parameter.The valid range of the function argument is defined at the function declaration and
                        has to be ensured by the calling function.

  \ID SBSW_DHCPV4_LOCSOCKADDR_PTR
    \DESCRIPTION       AddrLocSock element of SocketDyn() is written or passed to subroutine with an index
                       parameter given by TcpIp_GetIpV4SocketDynDhcpIdxOfIpV4General().
    \COUNTERMEASURE \M Verify that optional indirection
                         TcpIp_GetIpV4SocketDynDhcpIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX)
                       is always valid if IPv4 and DHCP are enabled.
                         TCPIP_SUPPORT_IPV4 == STD_ON
                         TCPIP_SUPPORT_DHCPV4 == STD_ON
                       This is ensure by CM_TCPIP_IPV4_DHCP_SOCKET.

   SBSW_JUSTIFICATION_END */

/************************************************************************************************************
*  MSSV Checks
***********************************************************************************************************/
/* \CM CM_TCPIP_DHCPV4_CONFIG_AND_STATUS                 Each IPv4Ctrl which references a valid DhcpConfig, must reference a valid DhcpStatus and vice versa. */

/* \CM CM_TCPIP_IPV4_DHCP_SOCKET                         TcpIp_GetIpV4SocketDynDhcpIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX) has to be valid if IPv4 and DHCPv4 is configured. */

/************************************************************************************************************
*  Runtime Checks
***********************************************************************************************************/
/*  \CM CM_TCPIP_DHCPV4_OPT_BUF_VALID_ACCESS
        Functions used for serialization of Dhcp options are called two times orderly with different buffer pointer values.
        1. In the first call, the buffer pointer is passed to the function as NULL_PTR. In this case, the function returns the calculated option Length.
        2. In the second call, the implementation passes a valid non NULL_PTR pointer. In this case, the function updates the buffer (of a size calculated in 1st step).
        The implementation ensures that the buffer used in the second call corresponds to the length calculated in the fist call.
        This ensures that the buffer is accessed and updated only within a valid range.

    \CM CM_TCPIP_DHCPV4_VLOOKUPOPTIONIDX_CONSTRAINT
        Index derivation to access DhcpUserOptions elements.
        Validity of the index value(s) of the modelled indirection(s) [is|are] checked using the function:
        TcpIp_IsDhcpUserOptionUsedOfIpV4Ctrl(IpV4CtrlIdx). IpV4CtrlIdx is derived by the caller using TcpIp_GetSizeOf..() CSL macro.
        The function TcpIp_DhcpV4_VLookUpOptionIdx is called  if TcpIp_IsDhcpUserOptionUsedOfIpV4Ctrl(IpV4CtrlIdx) is true and/or the userOptIdx obtained from that function is validated as dhcpUserOptIdx  <  TcpIp_GetSizeOfDhcpUserOption() (CSL01) before its usage.
        userOptIdx variable is then used to derive the user option buffer Index using TcpIp_GetDhcpUserOptionBufferLengthOfDhcpUserOption(dhcpUserOptIdx).

    \CM CM_TCPIP_DHCPV4_IPV4_IP_PROVIDETXBUFFER
        A local pointer is created inside the caller function and passed to TCPIP_LL_ProvideTxBuffer function in order to validate it.
        If TCPIP_LL_ProvideTxBuffer function retuns BUFREQ_OK and if bufLenByte is valid (means buffer pointer is valid) then only it is updated.

 */

#endif  /* (TCPIP_SUPPORT_IPV4 == STD_ON) && (TCPIP_SUPPORT_DHCPV4 == STD_ON) */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_DhcpV4.c
 *********************************************************************************************************************/
