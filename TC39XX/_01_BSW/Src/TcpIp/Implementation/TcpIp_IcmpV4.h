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
 *         \file  TcpIp_IcmpV4.h
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

#if !defined (IPV4_ICMP_H)
# define IPV4_ICMP_H

#include "TcpIp_Cfg.h"
#include "TcpIp_Lcfg.h"
#if (TCPIP_SUPPORT_ICMPV4 == STD_ON)                                                                                    /* COV_TCPIP_ICMPV4_ALWAYS_ON */

/*
--- LIMITAIONS OF THIS IMPLEMENTATION ------------------------------------------
- only handling of echo and echo request is implemented
*/

/*
|0              |8              |16             |24             |
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|     Type      |     Code      |          Checksum             |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| ...                                                           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
Format of a ICMP message
*/


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIp_IpV4.h"
#include "TcpIp_IpV4.h"



#include "ComStack_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ICMP ApiIds */
#define IPV4_ICMP_API_ID_SEND_ECHO                   0x60u

#define IPV4_ICMP_API_ID_INIT                        0x70u
#define IPV4_ICMP_API_ID_MAIN_FUNCTION               0x71u
#define IPV4_ICMP_API_ID_RX_INDICATION               0x72u


/* ICMP types */
#define IPV4_ICMP_TYPE_ECHO_REPLY           0u
#define IPV4_ICMP_TYPE_DEST_UNRECHABLE      3u
#define IPV4_ICMP_TYPE_SOURCE_QUENCH        4u
#define IPV4_ICMP_TYPE_REDIRECT             5u
#define IPV4_ICMP_TYPE_ECHO                 8u
#define IPV4_ICMP_TYPE_TIME_EXCEEDED       11u
#define IPV4_ICMP_TYPE_PARAM_PROBLEM       12u
#define IPV4_ICMP_TYPE_TIMESTAMP           13u
#define IPV4_ICMP_TYPE_TIMESTAMP_REPLY     14u
#define IPV4_ICMP_TYPE_INFO_REQUEST        15u
#define IPV4_ICMP_TYPE_INFO_REOLY          16u

#define IPV4_ICMP_CODE_PROTOCOL_UNREACHABLE 2u
#define IPV4_ICMP_CODE_PORT_UNREACHABLE     3u

#define IPV4_ICMP_LENBYTE_ECHO_REPLY        8u  /* min length */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint16 IpV4_Icmp_TypeType;
typedef uint16 IpV4_Icmp_CodeType;
typedef uint8  IpV4_Icmp_StateType;

typedef void IpV4_Icmp_ConfigType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */
/**********************************************************************************************************************
 *  IpV4_Icmp_Init
 *********************************************************************************************************************/
/*! \brief        Intitializes the ICMPV4 Component.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, IPV4_CODE) IpV4_Icmp_Init(void);

/**********************************************************************************************************************
 *  IpV4_Icmp_MainFunction
 *********************************************************************************************************************/
/*! \brief        Handles the ICMP global status.
 *  \details      -
 *  \pre          PRE_TCPIP_ICMPV4_Init
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \note         This function is called every IPV4_MAIN_FCT_PERIOD_MSEC ms
 *********************************************************************************************************************/
FUNC(void, IPV4_CODE) IpV4_Icmp_MainFunction(void);

/**********************************************************************************************************************
 *  IpV4_Icmp_SendEcho
 *********************************************************************************************************************/
/*! \brief        Triggers transmission of a PING message.
 *  \details      -
 *  \param[in]    LocalAddrV4Idx        Local IP address identifier
 *  \param[in]    Dest                  Remote network address
 *  \param[in]    DataPtr               Pointer to the data
                                        CONSTRAINT: [Must point to the valid buffer of size LenByte.]
 *  \param[in]    LenByte               Length of transmitting data in bytes ,
 *  \return       E_OK                  Send request could be accepted
 *  \return       E_NOT_OK              Send request could not be accepted
 *  \pre          PRE_TCPIP_ICMPV4_Init
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Icmp_SendEcho(
  TcpIp_SizeOfLocalAddrV4Type LocalAddrV4Idx,
  IpBase_AddrInType           Dest,
  IPV4_P2C(uint8)             DataPtr,
  uint16                      LenByte );

# if (TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG == STD_ON)
/**********************************************************************************************************************
 *  IpV4_Icmp_SendDestUnreachable()
 *********************************************************************************************************************/
/*! \brief        Triggers transmission of a ICMP Destination Unreachable message message.
 *  \details      -
 *  \param[in]    LocalAddrV4Idx         Local IP address identifier
 *  \param[in]    DataPtr                Pointer to the IP packet received.
 *                                       CONSTRAINT: [Must point to a valid buffer which contains the serialized IPv4
 *                                                   header. The total length field has to be set and has to match
 *                                                   the buffer size.]
 *  \param[in]    IcmpCode               Value of Code field in ICMP message header.
 *  \pre          PRE_TCPIP_ICMPV4_Init
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, IPV4_CODE) IpV4_Icmp_SendDestUnreachable(
  TcpIp_LocalAddrV4IterType LocalAddrV4Idx,
  TCPIP_P2C(uint8)          DataPtr,
  uint8                     IcmpCode);
#endif

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

#endif  /* (TCPIP_SUPPORT_IPV4 == STD_ON) */
#endif  /* IPV4_ICMP_H */
/**********************************************************************************************************************
 *  END OF FILE: IpV4_Icmp.h
 *********************************************************************************************************************/
