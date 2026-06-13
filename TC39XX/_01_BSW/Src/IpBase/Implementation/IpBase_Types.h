/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IpBase_Types.h
 *      Project:  MICROSAR IP
 *       Module:  MICROSAR IP Base
 *    Generator:  None
 *
 *  Description:  Types header
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (IPBASE_TYPES_H)
# define IPBASE_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "IpBase_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define IPBASE_TCP_EVENT_RESET         0x01u       /*!< TCP event RESET encoding */
# define IPBASE_TCP_EVENT_CLOSED        0x02u       /*!< TCP event CLOSE encoding */
# define IPBASE_TCP_EVENT_FIN_RECEIVED  0x03u       /*!< TCP event FIN encoding */
# define IPBASE_STR_LEN_INVALID         0xFFFFFFFFu /*!< invalid string length indication */
# define IPBASE_PORT_LEN_BYTE           0x02u       /*!< number of bytes for socket port */
# define IPBASE_UCHAR_MAX               255u        /*!< as UCHAR_MAX in <limits.h> */
# define IPBASE_USHRT_MAX               65535u      /*!< as USHRT_MAX in <limits.h> */
# define IPBASE_ULONG_MAX               4294967295u /*!< as ULONG_MAX in <limits.h> */
# define IPBASE_SLONG_MAX               2147483647  /*!< as LONG_MAX in <limits.h> */
# define IPBASE_UCHAR_DEC_DIGITS_MAX    3u          /*!<  3 decimal digits */
# define IPBASE_USHRT_DEC_DIGITS_MAX    5u          /*!<  5 decimal digits */
# define IPBASE_ULONG_DEC_DIGITS_MAX    10u         /*!< 10 decimal digits */
# define IPBASE_UCHAR_HEX_DIGITS_MAX    2u          /*!<  2 hexadecimal digits */
# define IPBASE_USHRT_HEX_DIGITS_MAX    4u          /*!<  4 hexadecimal digits */
# define IPBASE_ULONG_HEX_DIGITS_MAX    8u          /*!<  8 hexadecimal digits */

# define IPBASE_AF_UNSPEC               0x0000u     /*!< address family not yet specified */
# define IPBASE_AF_INET                 0x0002u     /*!< address family for IPv4 */
# define IPBASE_AF_INET6                0x001Cu     /*!< address family for IPv6 (changed from 0x000Au) */
# define IPBASE_AF_INVALID              0xFFFFu     /*!< address family invalid */

# define IPBASE_ETH_PHYS_ADDR_LEN_BYTE  6u          /*!< number of bytes for MAC address */
# define IPBASE_END_OF_STRING           0           /*!< end of string pattern */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 9 */ /* MD_MSR_FctLikeMacro */
# define IPBASE_P2CONSTAPPLDATA(Type)      P2CONST(Type, AUTOMATIC, IPBASE_APPL_DATA)
# define IPBASE_PP2CONSTAPPLDATA(Type)     const Type AUTOMATIC ** IPBASE_APPL_DATA
# define IPBASE_CONSTP2CONSTAPPLDATA(Type) CONSTP2CONST(Type, AUTOMATIC, IPBASE_APPL_DATA)
# define IPBASE_CONSTP2VARAPPLDATA(Type)   CONSTP2VAR(Type, AUTOMATIC, IPBASE_APPL_DATA)
# define IPBASE_P2VARAPPLDATA(Type)        P2VAR(Type, AUTOMATIC, IPBASE_APPL_DATA)
# define IPBASE_PP2VARAPPLDATA(Type)       Type AUTOMATIC ** IPBASE_APPL_DATA
# define IPBASE_VARNOINIT(Type)            VAR(Type, IPBASE_VAR_NOINIT)
# define IPBASE_CONSTCONST(Type)           CONST(Type, IPBASE_CONST)
# define IPBASE_FUNCCODE(Type)             FUNC(Type, IPBASE_CODE)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint32    IpBase_AddrInType;     /*!< This type is used as generic internet protocol address. */
typedef uint32    IpBase_IPAddressType;  /*!< This type is used as internet protocol address for version 4 (IPv4). */
typedef uint16    IpBase_FamilyType;     /*!< This type is used to distinguish between IPv4 and IPv6. */
typedef uint16    IpBase_PortType;       /*!< This type is used to define the socket port (IPv4 and IPv6) */
typedef uint8     IpBase_EthPhysAddrType[IPBASE_ETH_PHYS_ADDR_LEN_BYTE]; /*!< This type is used to define MAC address */
typedef uint8     IpBase_CopyDataType;   /*!< This type is used as generic data type for memory copy routines */
typedef uint8     IpBase_SockIdxType;    /*!< This type is used as index data type for sockets */
typedef uint8     IpBase_ReturnType;     /*!< This type is used as generic return type */
typedef uint8     IpBase_TcpIpEventType; /*!< This type is used for TCP/IP state events like SYN, FIN, ... */

/*! This type is used as array with 1 to n buffer segments where sum of all segment lengths equals total length */
typedef struct
{
  uint8  *payload; /*!< Pointer to the payload data, i.e. buffer segment */
  uint32 totLen;   /*!< Total length in bytes of all buffer segments */
  uint16 len;      /*!< Length in bytes of buffer segment */
} IpBase_PbufType;

/*! This type is used as internet protocol socket address with IPv4 address, length and port number */
typedef struct
{
  uint16               port; /*!< Port number of internet protocol */
  uint8                len;  /*!< Length in bytes of address */
  IpBase_IPAddressType addr; /*!< IPv4 internet protocol address */
} IpBase_IpAddrPortType;

/*! This type is used as internet protocol socket address with family plus data */
typedef struct
{
  IpBase_FamilyType  sa_family; /*!< Internet protocol family (IPv4 or IPv6) */
  /* PRQA S 1039 1 */ /* MD_IpBase_1039 */
  uint8              sa_data[1]; /*!< Data with dummy length superseded with IPv4 or IPv6 address */
} IpBase_SockAddrType;

/*! This type is used as internet protocol socket address with family plus IPv4 or IPv6 address plus port number */
typedef struct
{
  IpBase_FamilyType  sin_family; /*!< Internet protocol family (IPv4 or IPv6) */
  IpBase_PortType    sin_port;   /*!< Internet protocol port number */
  IpBase_AddrInType  sin_addr;   /*!< Internet protocol address */
} IpBase_SockAddrInType;

/*! This type is used as internet protocol IPv4 or IPv6 address */
/* PRQA S 750 5 */ /* MD_MSR_Union */
typedef union
{
  uint8 addr[16];   /*!< Internet protocol address in bytes */
  uint32 addr32[4]; /*!< Internet protocol address in 4 byte words */
} IpBase_AddrIn6Type;

/*! This type is used as internet protocol socket address with family plus IPv6 address plus port number */
typedef struct
{
  IpBase_FamilyType  sin6_family; /*!< Internet protocol family (IPv4 or IPv6) */
  IpBase_PortType    sin6_port;   /*!< Internet protocol port number */
  IpBase_AddrIn6Type sin6_addr;   /*!< Internet protocol address (IPv6) */
} IpBase_SockAddrIn6Type;
#endif
  /* IPBASE_TYPES_H */
/**********************************************************************************************************************
 *  END OF FILE: IpBase_Types.h
 *********************************************************************************************************************/
