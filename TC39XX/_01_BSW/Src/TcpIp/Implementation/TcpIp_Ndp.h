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
 *         \file  TcpIp_Ndp.h
 *        \brief  Implementation of Neighbor Discovery Protocol (NDP) for IPv6
 *
 *      \details  This file is part of the TcpIp IPv6 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv6 submodule. >> TcpIp_IpV6.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/

/* configuration, interrupt handling and callback headers use different names
 * for the multiple inclusion protection define, shown in this example. The
 * appropriate names for these files can be taken from this list:
 *
 * IpV6_Icmp_Cfg.h:     IPV6_NDP_CFG_H
 * IpV6_Icmp_Irq.h:     IPV6_NDP_IRQ_H
 * IpV6_Icmp_Cbk.h:     IPV6_NDP_CBK_H
 */
#if !defined(IPV6_NDP_H)
#define IPV6_NDP_H

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "EthIf.h"
#include "Std_Types.h"

#include "TcpIp_IpV6.h"

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define IPV6_NDP_OPT_TYPE_SOURCE_LL_ADDR                    1u /* Source Link-Layer Address */
#define IPV6_NDP_OPT_TYPE_TARGET_LL_ADDR                    2u /* Target Link-Layer Address */
#define IPV6_NDP_OPT_TYPE_PREFIX_INFO                       3u /* Prefix Information */
#define IPV6_NDP_OPT_TYPE_REDIR_HEADER                      4u /* Redirected Header */
#define IPV6_NDP_OPT_TYPE_MTU                               5u /* MTU */

#define IPV6_NDP_OPT_TYPE_SOURCE_ADDR_LIST                  9u
#define IPV6_NDP_OPT_TYPE_TARGET_ADDR_LIST                  10u

#define IPV6_NDP_OPT_TYPE_RDNSS                             25u /* [RFC6106 5.1. Recursive DNS Server Option] */
#define IPV6_NDP_OPT_TYPE_DNSSL                             31u /* [RFC6106 5.2. DNS Search List Option] */

#define IPV6_NDP_RA_FLAG_MANAGED                            (1u << 7) /* managed address configuration flag */
#define IPV6_NDP_RA_FLAG_OTHER                              (1u << 6) /* other configuration flag */

#define IPV6_NDP_OPT_PREFIX_INFO_FLAG_ON_LINK               (1u << 7) /* indicates prefix can be used for on-link determination */
#define IPV6_NDP_OPT_PREFIX_INFO_FLAG_SLAAC                 (1u << 6) /* indicates prefix can be used for SLAAC */

#define IPV6_NDP_OPT_LL_ADDR_LEN_BYTE                       8u /* length of a (source/target)-link-layer address option in bytes */

#define IPV6_NDP_MSG_HOP_LIMIT                              255u /* mandatory hop limit value for all NDP messages */

/* NDP Link layer address option header offset */
#define IPV6_NDP_LL_ADDR_OPT_OFF_TYPE                       0u
#define IPV6_NDP_LL_ADDR_OPT_OFF_LEN                        1u
#define IPV6_NDP_LL_ADDR_OPT_OFF_ADDR                       2u

/* NDP router advertisement message offsets */
#define IPV6_NDP_RA_MSG_OFF_CURHOPLIMIT                     0u
#define IPV6_NDP_RA_MSG_OFF_MORESERVED                      1u
#define IPV6_NDP_RA_MSG_OFF_ROUTERLIFETIMENBO               2u
#define IPV6_NDP_RA_MSG_OFF_REACHABLETIMENBO                4u
#define IPV6_NDP_RA_MSG_OFF_RETRANSTIMERNBO                 8u

/* NDP router solicitation message offsets */
#define IPV6_NDP_RS_MSG_OFF_RESERVED32                      0u

/* NDP neighbor solicitation message offsets */
#define IPV6_NDP_NS_MSG_OFF_RESERVED32                      0u
#define IPV6_NDP_NS_MSG_OFF_TARGETADDRESS                   4u

/* NDP neighbor advertisement message offsets */
#define IPV6_NDP_NA_MSG_OFF_RSORESERVED                     0u
#define IPV6_NDP_NA_MSG_OFF_RESERVED8                       1u
#define IPV6_NDP_NA_MSG_OFF_TARGETADDRESS                   4u

/* NDP redirect message offsets */
#define IPV6_NDP_REDIR_MSG_OFF_RESERVED32NBO                0u
#define IPV6_NDP_REDIR_MSG_OFF_TARGETADDRESS                4u
#define IPV6_NDP_REDIR_MSG_OFF_DESTADDRESS                  20u

/* NDP inverse neighbor advertisement message offsets */
#define IPV6_NDP_INA_MSG_OFF_RESERVED32                     0u

/* NDP inverse neighbor solictitation message offsets */
#define IPV6_NDP_INS_MSG_OFF_RESERVED32                     0u

/* NDP prefix info option offsets */
#define IPV6_NDP_PREFIX_INFO_OPT_OFF_TYPE                   0u
#define IPV6_NDP_PREFIX_INFO_OPT_OFF_LENGTH                 1u
#define IPV6_NDP_PREFIX_INFO_OPT_OFF_PREFIXLENGTH           2u
#define IPV6_NDP_PREFIX_INFO_OPT_OFF_LARESERVED             3u
#define IPV6_NDP_PREFIX_INFO_OPT_OFF_VALIDLIFETIMENBO       4u
#define IPV6_NDP_PREFIX_INFO_OPT_OFF_PREFERREDLIFETIMENBO   8u
#define IPV6_NDP_PREFIX_INFO_OPT_OFF_RESERVED32NBO          12u
#define IPV6_NDP_PREFIX_INFO_OPT_OFF_PREFIX                 16u

#define IPV6_NDP_OPT_SOURCE_LL_ADDR_IDX                     0u
#define IPV6_NDP_OPT_TARGET_LL_ADDR_IDX                     1u
#define IPV6_NDP_OPT_SOURCE_ADDR_LIST_IDX                   2u
#define IPV6_NDP_OPT_TARGET_ADDR_LIST_IDX                   3u
#define IPV6_NDP_OPT_MTU_IDX                                4u

/* NDP MTU option offsets */
#define IPV6_NDP_MTU_OPT_OFF_TYPE                           0U
#define IPV6_NDP_MTU_OPT_OFF_LEN                            1u
#define IPV6_NDP_MTU_OPT_OFF_RSVD16NBO                      2u
#define IPV6_NDP_MTU_OPT_OFF_MTUNBO                         4u


/* Maxium supported options for different NDP messages */
#define IPV6_NDP_NANS_MAX_IDX                               2u
#define IPV6_NDP_IND_MAX_IDX                                5u

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FctLikeMacros */ /* MD_MSR_FctLikeMacro */
/* PRQA L:FctLikeMacros */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*  Router Solicitation Message Format (see RFC4861)
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
 *  |     Type      |     Code      |          Checksum             |  } ICMPv6 header
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ /
 *  |                            Reserved                           |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |   Options ...
 *  +-+-+-+-+-+-+-+-+-+-+-+-
 */
typedef struct
{
  uint32 Reserved32; /* must be set to 0 when sent and ignored when received */
  /* [...] TLV encoded options */
} IpV6_NdpRsType;

/*  Router Advertisement Message Format (see RFC4861)
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
 *  |  Type = 134   |   Code = 0    |          Checksum             |  } ICMPv6 header
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ /
 *  | Cur Hop Limit |M|O|  Reserved |       Router Lifetime         |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                         Reachable Time                        |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                          Retrans Timer                        |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |   Options ...
 *  +-+-+-+-+-+-+-+-+-+-+-+-
 */
typedef struct
{
  uint8  CurHopLimit;       /* Default Hop Count in IPv6 header of outgoing packets */
  uint8  MOReserved;        /* "(M)anaged address configuration" and "(O)ther configuration" flag. */
  uint16 RouterLifetimeNbo; /* lifetime of router in seconds */
  uint32 ReachableTimeNbo;  /* Time (ms) node assumes neighbor is reachable after reachability confirmation. (NUD) */
  uint32 RetransTimerNbo;   /* Time (ms) between retransmitted Neighbor Solicitation messages. (AR and NUD) */
  /* [...] TLV encoded options */
} IpV6_NdpRaType;

/*  Neighbor Solicitation Message Format (see RFC4861)
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
 *  |  Type = 135   |   Code = 0    |          Checksum             |  } ICMPv6 header
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ /
 *  |                           Reserved                            |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                                                               |
 *  +                                                               +
 *  |                                                               |
 *  +                       Target Address                          +
 *  |                                                               |
 *  +                                                               +
 *  |                                                               |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |   Options ...
 *  +-+-+-+-+-+-+-+-+-+-+-+-
 */
typedef struct
{
  uint32        Reserved32;
  IpV6_AddrType TargetAddress;
  /* [...] TLV encoded options */
} IpV6_NdpNsType;

/*  Neighbor Advertisement Message Format (see RFC4861)
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
 *  |  Type = 136   |   Code = 0    |          Checksum             |  } ICMPv6 header
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ /
 *  |R|S|O|Reserved |                 Reserved                      |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                                                               |
 *  +                                                               +
 *  |                                                               |
 *  +                       Target Address                          +
 *  |                                                               |
 *  +                                                               +
 *  |                                                               |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |   Options ...
 *  +-+-+-+-+-+-+-+-+-+-+-+-
 */
typedef struct
{
  uint8         RSOReserved;
  uint8         Reserved8[3];
  IpV6_AddrType TargetAddress;
  /* [...] TLV encoded options */
} IpV6_NdpNaType;

/*  Redirect Message Format (see RFC4861)
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
 *  |  Type = 137   |   Code = 0    |          Checksum             |  } ICMPv6 header
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ /
 *  |                           Reserved                            |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                                                               |
 *  +                                                               +
 *  |                                                               |
 *  +                       Target Address                          +
 *  |                                                               |
 *  +                                                               +
 *  |                                                               |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                                                               |
 *  +                                                               +
 *  |                                                               |
 *  +                     Destination Address                       +
 *  |                                                               |
 *  +                                                               +
 *  |                                                               |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |   Options ...
 *  +-+-+-+-+-+-+-+-+-+-+-+-
 */
typedef struct
{
  uint32        Reserved32Nbo;
  IpV6_AddrType TargetAddress;
  IpV6_AddrType DestinationAddress;
  /* [...] TLV encoded options */
} IpV6_NdpRedirType;

/*  [RFC3122 2.1 Inverse Neighbor Discovery Solicitation Message]
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
 *  |     Type      |     Code      |          Checksum             |  } ICMPv6 header
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ /
 *  |                            Reserved                           |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |   Options ...
 *  +-+-+-+-+-+-+-+-+-+-+-+-
 */
typedef struct
{
  uint32 Reserved32; /* must be set to 0 when sent and ignored when received */
  /* [...] TLV encoded options */
} IpV6_NdpIsType;

/*  [RFC3122 2.2 Inverse Neighbor Discovery Advertisement Message]
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
 *  |     Type      |     Code      |          Checksum             |  } ICMPv6 header
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ /
 *  |                            Reserved                           |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |   Options ...
 *  +-+-+-+-+-+-+-+-+-+-+-+-
 */
typedef struct
{
  uint32 Reserved32; /* must be set to 0 when sent and ignored when received */
  /* [...] TLV encoded options */
} IpV6_NdpIaType;

/* NDP OPTIONS */

/*  Source/Target Link-layer Address */
/*
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Type      |    Length     |    Link-Layer Address ...
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
typedef struct
{
  uint8 Type;   /* 1 for Source Link-layer Address, 2 for Target Link-layer Address */
  uint8 Length; /* length in units of 8 octets (1 for ethernet link-layer) */
  uint8 addr[IPBASE_ETH_PHYS_ADDR_LEN_BYTE];
} IpV6_NdpOptLLAddrType;

/*  Prefix Information
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Type      |    Length     | Prefix Length |L|A| Reserved1 |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                         Valid Lifetime                        |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                       Preferred Lifetime                      |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                           Reserved2                           |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                                                               |
 *  +                                                               +
 *  |                                                               |
 *  +                            Prefix                             +
 *  |                                                               |
 *  +                                                               +
 *  |                                                               |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
typedef struct
{
  uint8  Type;                 /* must be 3 */
  uint8  Length;               /* must be 4 (4 * 8 octests) */
  uint8  PrefixLength;         /* number of leading bits in the Prefix that are valid */
  uint8  LAReserved;           /* unused, must be set to zero by sender and ignored by receiver */
  uint32 ValidLifetimeNbo;     /* time in seconds the prefix is valid (network byte order) */
  uint32 PreferredLifetimeNbo; /* time in seconds addresses with this prefix are preferred (network byte order) */
  uint32 Reserved32Nbo;        /* unused, must be set to zero by sender and ignored by receiver (network byte order) */
  IpV6_AddrType  Prefix;       /* */
} IpV6_NdpOptPrefixInfoType;

/*  Redirected Header
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Type      |    Length     |            Reserved           |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                           Reserved                            |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                                                               |
 *  ~                       IP header + data                        ~
 *  |                                                               |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
typedef struct
{
  uint8  Type;          /* must be 4 */
  uint8  Length;        /* option length in units of 8 octets */
  uint16 Reserved16Nbo; /* unused, must be set to zero be sender and ignored by receiver */
  uint32 Reserved32Nbo; /* unused, must be set to zero be sender and ignored by receiver */
  /* IP header + data */
} IpV6_NdpOptRedirHeaderType;

/*  MTU
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Type      |    Length     |           Reserved            |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                              MTU                              |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
typedef struct
{
  uint8  Type;          /* must be 5 */
  uint8  Length;        /* must be 1 (1 * 8 octets) */
  uint16 Reserved16Nbo; /* unused, must be set to zero by sender and ignored by receiver */
  uint32 MTUNbo;        /* recommended MTU for the link */
} IpV6_NdpOptMtuType;

#if (TCPIP_SUPPORT_NDP_OPT_RFC6106_RDNSS == STD_ON)
/*  Recursive DNS Server (RDNSS) Option Format (see RFC6106 5.1.)
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Type      |     Length    |           Reserved            |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                           Lifetime                            |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                                                               |
 *  :            Addresses of IPv6 Recursive DNS Servers            :
 *  |                                                               |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
typedef struct
{
  uint8  Type;          /*!< "Identifier of the RDNSS option type as assigned by the IANA: 25" */
  uint8  Length;        /*!< "The length of the option (including the Type and Length fields) is in units of 8 octets." */
  uint16 Reserved16Nbo; /*!< Reserved field */
  uint32 LifetimeNbo;   /*!< "The maximum time, in seconds (relative to the time the packet is sent), over which this RDNSS address MAY be used for name resolution." */
} IpV6_NdpOptRdnssType;
#endif

#if (TCPIP_SUPPORT_NDP_OPT_RFC6106_DNSSL == STD_ON)
/*  DNS Search List (DNSSL) Option Format (see RFC6106 5.2.)
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Type      |     Length    |           Reserved            |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                           Lifetime                            |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                                                               |
 *  :                Domain Names of DNS Search List                :
 *  |                                                               |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
typedef struct
{
  uint8  Type;          /*!< "Identifier of the DNSSL option type as assigned by the IANA: 31" */
  uint8  Length;        /*!< "The length of the option (including the Type and Length fields) is in units of 8 octets." */
  uint16 Reserved16Nbo; /*!< Reserved filed */
  uint32 LifetimeNbo;   /*!< "The maximum time, in seconds (relative to the time the packet is sent), over which this DNSSL domain name MAY be used for name resolution." */
} IpV6_NdpOptDnsslType;
#endif

#if ((TCPIP_SUPPORT_NDP_INV_NA == STD_ON) || (TCPIP_SUPPORT_NDP_INV_NS == STD_ON))
/*  Source/Target Address List
 *
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Type      |    Length   |                                 |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+        -       -       -        +
 *  |                          Reserved                             |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                                                               |
 *  +                                                               +
 *  |                                                               |
 *  +                        IPv6 Address                           +
 *  |                                                               |
 *  +                                                               +
 *  |                                                               |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |
 *  ~
 *  |
 *  +-+-+-+-+...
 */
typedef struct
{
  uint8  Type;          /*!< 9 for Source Address List, 10 for Target Address List */
  uint8  Length;        /*!< 3 + (n - 1) for n Addresses */
  uint16 Reserved16Nbo; /*!< Reserved filed */
  uint32 Reserved32Nbo; /*!< Reserved filed */
} IpV6_NdpOptAddrListType;
#endif

typedef struct
{
  IpV6_AddrType addr;
} IpV6_Ndp_RouterEntryType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  IpV6_Ndp_VTxNeighborAdvertisement()
 *********************************************************************************************************************/
/*! \brief         Transmit neighbor advertisement
 *  \details       -
 *  \param[in]     LocalAddrV6IdxPtr   Ip address index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     DstAddrPtr          Destination address
 *  \param[in]     TargetAddrPtr       Target address to include in options
 *  \param[in]     RSOFlags            (R)erserved, (S)olicited, (O)verride flags
 *  \return        E_OK                Message queued for transmission
 *  \return        E_NOT_OK            Message transmission not successful
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VTxNeighborAdvertisement(
  IPV6_P2V(TcpIp_LocalAddrV6IterType)   LocalAddrV6IdxPtr,
  IPV6_P2C(IpV6_AddrType)               DstAddrPtr,
  IPV6_P2C(IpV6_AddrType)               TargetAddrPtr,
  uint8                                 RSOFlags);

/**********************************************************************************************************************
 *  IpV6_Ndp_VRxRouterAdvertisement()
 *********************************************************************************************************************/
/*! \brief         Rx handling function for router advertisement
 *  \details       -
 *  \param[in]     LocalAddrV6Idx    Ip address index
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     SrcAddrPtr        Source addresso of sender
 *  \param[in]     DataPtr           Message data buffer
 *  \param[in]     LenByte           Length of message data
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VRxRouterAdvertisement(
  TcpIp_LocalAddrV6IterType     LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)       SrcAddrPtr,
  IPV6_P2C(uint8)               DataPtr,
  uint16                        LenByte);

/**********************************************************************************************************************
 *  IpV6_Ndp_VRxNeighborSolicitation()
 *********************************************************************************************************************/
/*! \brief         Rx handling function for neighbor solicitation
 *  \details       This function is called by ICMP when a neighbor solicitation has been received.
 *  \param[in]     LocalAddrV6Idx    Ip address index
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     SrcAddrPtr        Source address of sender
 *  \param[in]     PhysAddrPtr       Physical address of sender
 *  \param[in]     DataPtr           Ndp packet payload buffer
 *  \param[in]     LenByte           Ndp packet payload length
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VRxNeighborSolicitation(
  TcpIp_LocalAddrV6IterType    LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)      SrcAddrPtr,
  IPV6_P2C(uint8)              PhysAddrPtr,
  IPV6_P2C(uint8)              DataPtr,
  uint16                       LenByte);

/**********************************************************************************************************************
 *  IpV6_Ndp_VRxNeighborAdvertisement()
 *********************************************************************************************************************/
/*! \brief         Rx handling function for neighbor advertisement
 *  \details       -
 *  \param[in]     LocalAddrV6Idx    Ip address index
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     SrcAddrPtr        Source address of sender
 *  \param[in]     PhysAddrPtr       Physical address of sender
 *  \param[in]     DataPtr           Ndp packet payload buffer
 *  \param[in]     LenByte           Ndp packet payload length
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VRxNeighborAdvertisement(
  TcpIp_LocalAddrV6IterType    LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)      SrcAddrPtr,
  IPV6_P2C(uint8)              PhysAddrPtr,
  IPV6_P2C(uint8)              DataPtr,
  uint16                       LenByte);

/**********************************************************************************************************************
 *  IpV6_Ndp_VRxRedirect()
 *********************************************************************************************************************/
/*! \brief         Rx handling function for redirect messages
 *  \details       -
 *  \param[in]     LocalAddrV6Idx  Ip address index
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     SrcAddrPtr      Source address of sender
 *  \param[in]     DataPtr         Ndp packet payload buffer
 *  \param[in]     LenByte         Ndp packet payload length
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VRxRedirect(
  TcpIp_LocalAddrV6IterType    LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)      SrcAddrPtr,
  IPV6_P2C(uint8)              DataPtr,
  uint16                       LenByte);

/**********************************************************************************************************************
 *  IpV6_Ndp_VTxNeighborSolicitation()
 *********************************************************************************************************************/
/*! \brief         Handle transmission of neighbor solicitation
 *  \details       -
 *  \param[in]     LocalAddrV6Idx      Ip address index
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     TargetAddrPtr       Target address
 *  \param[in]     Unicast             Whether unicast or multicast message
 *  \param[in]     ForceUnspecSrcAddr  Flag to specify to use unspecified source address
 *  \return        E_OK                Packet was queued for transmission
 *  \return        E_NOT_OK            Packet transmission unsuccessful
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VTxNeighborSolicitation(
  TcpIp_LocalAddrV6IterType    LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)      TargetAddrPtr,
  boolean                      Unicast,
  boolean                      ForceUnspecSrcAddr);

#if (TCPIP_SUPPORT_NDP_ROUTER_SOLICITATIONS == STD_ON)
/**********************************************************************************************************************
 *  IpV6_Ndp_VTxRouterSolicitation()
 *********************************************************************************************************************/
/*! \brief         Handle transmission of router solicitation
 *  \details       -
 *  \param[in]     LocalAddrV6Idx   Ip address index
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     IncludeSllaOpt   Flag to indicate if Slla options need to be included
 *  \return        E_OK             Packet was queued for transmission
 *  \return        E_NOT_OK         Packet transmission unsuccessful
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VTxRouterSolicitation(
  TcpIp_LocalAddrV6IterType    LocalAddrV6Idx,
  boolean                      IncludeSllaOpt);
#endif

/**********************************************************************************************************************
 *  IpV6_Ndp_VTxInverseAdvertisement()
 *********************************************************************************************************************/
/*! \brief         Handle transmission of inverse neighbor advertisement
 *  \details       -
 *  \param[in]     LocalAddrV6IdxPtr Ip address index
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     DstAddrPtr        Destination address
 *  \param[in]     TgtLLAddrPtr      Target link layer address
 *  \return        E_OK              Packet was queued for transmission
 *  \return        E_NOT_OK          Packet transmission unsuccessful
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VTxInverseAdvertisement(
  IPV6_P2C(TcpIp_LocalAddrV6IterType)  LocalAddrV6IdxPtr,
  IPV6_P2C(IpV6_AddrType)              DstAddrPtr,
  IPV6_P2C(uint8)                      TgtLLAddrPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VTxInverseSolicitation()
 *********************************************************************************************************************/
/*! \brief         Handle transmission of inverse neighbor solicitation
 *  \details       -
 *  \param[in]     LocalAddrV6Idx       Ip address index
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     TgtLLAddrPtr         Target link layer address
 *  \param[in]     IncludeSrcAddrList   Flag to indicate if source address list option need to be included
 *  \return        E_OK                 Packet was queued for transmission
 *  \return        E_NOT_OK             Packet transmission unsuccessful
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VTxInverseSolicitation(
  TcpIp_LocalAddrV6IterType    LocalAddrV6Idx,
  IPV6_P2C(uint8)              TgtLLAddrPtr,
  boolean                      IncludeSrcAddrList);

/**********************************************************************************************************************
 *  IpV6_Ndp_VRxInverseSolicitation()
 *********************************************************************************************************************/
/*! \brief         Handle Rx of inverse neighbor solicitation
 *  \details       -
 *  \param[in]     LocalAddrV6Idx   Ip address index
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     SrcAddrPtr       Source address
 *  \param[in]     DataPtr          Message data buffer
 *  \param[in]     LenByte          Length of the mesage
 *  \return        E_OK             Packet was queued for transmission
 *  \return        E_NOT_OK         Packet transmission unsuccessful
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VRxInverseSolicitation(
  TcpIp_SizeOfLocalAddrV6Type  LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)      SrcAddrPtr,
  IPV6_P2C(uint8)              DataPtr,
  uint16                       LenByte);

/**********************************************************************************************************************
 *  IpV6_Ndp_VRxInverseAdvertisement()
 *********************************************************************************************************************/
/*! \brief         Handle transmission of router solicitation
 *  \details       -
 *  \param[in]     LocalAddrV6Idx   Ip address index
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     SrcAddrPtr       Source address
 *  \param[in]     DataPtr          Message data buffer
 *  \param[in]     LenByte          Length of message
 *  \return        E_OK             Packet was queued for transmission
 *  \return        E_NOT_OK         Packet transmission unsuccessful
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VRxInverseAdvertisement(
  TcpIp_SizeOfLocalAddrV6Type  LocalAddrV6Idx,
  IPV6_P2C(IpV6_AddrType)      SrcAddrPtr,
  IPV6_P2C(uint8)              DataPtr,
  uint16                       LenByte);

/**********************************************************************************************************************
 *  IpV6_Ndp_SendInverseSolicitation()
 *********************************************************************************************************************/
/*! \brief         Handle transmission of router solicitation
 *  \details       -
 *  \param[in]     IpAddrIdx        Ip address index
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \param[in]     IncludeSllaOpt   Flag to indicate if Slla options need to be included
 *  \return        E_OK             Packet was queued for transmission
 *  \return        E_NOT_OK         Packet transmission unsuccessful
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_SendInverseSolicitation(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  IPV6_P2C(uint8)            TgtLLAddrPtr,
  boolean                    IncludeSrcAddrList);

/**********************************************************************************************************************
 *  IpV6_Ndp_VTxDad()
 *********************************************************************************************************************/
/*! \brief         Handle Dad transmission
 *  \details       -
 *  \param[in]     DstAddrPtr     Destination address
 *  \return        E_OK           Packet was queued for transmission
 *  \return        E_NOT_OK       Packet transmission unsuccessful
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VTxDad(
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA) DstAddrPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VAddSourceAddress()
 *********************************************************************************************************************/
/*! \brief         Add address to source address table
 *  \details       -
 *  \param[in]     IpV6SrcAddrIdx       Index of the source address getting added
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \param[in]     AddressPtr           Ip address of the source address
 *  \param[in]     PreferredLifetime    Preferred lifetime of the address
 *  \param[in]     ValidLifetime        valid lifetime of the address
 *  \param[out]    DelayMs              Next event expiry delay for Dad
 *  \param[out]    DadMode              IPV6_SRC_ADDR_DAD_MODE_NORMAL
 *                                      IPV6_SRC_ADDR_DAD_MODE_NONE
 *                                      IPV6_SRC_ADDR_DAD_MODE_OPTIMISTIC
 *  \return        E_OK                 Source address added to the table
 *  \return        E_NOT_OK             Source address was not added due to invalid lifetimes/multicast address
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VAddSourceAddress(
  TcpIp_IpV6SourceAddressIterType                    IpV6SrcAddrIdx,
  P2CONST(IpV6_AddrType, AUTOMATIC, IPV6_APPL_DATA)  AddressPtr,
  uint32                                             PreferredLifetime,
  uint32                                             ValidLifetime,
  uint32                                             DelayMs,
  uint8                                              DadMode);

/**********************************************************************************************************************
 *  IpV6_Ndp_VChangeLocalAddrState()
 *********************************************************************************************************************/
/*! \brief         Update the state of source address table entry
 *  \details       -
 *  \param[in]     IpV6SrcAddrIdx       Index of the source address getting added
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV6SourceAddress()-1]
 *  \param[in]     NewState             State of the source address
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VChangeLocalAddrState(
  TcpIp_SizeOfIpV6SourceAddressTableEntryType IpV6SrcAddrIdx,
  IpV6_LocAddrStateType                       NewState);

/* === PREFIX LIST FUNCTIONS === */

/**********************************************************************************************************************
 *  IpV6_Ndp_VPLLookup()
 *********************************************************************************************************************/
/*! \brief         Look up prefix in the prefix list
 *  \details       -
 *  \param[in]     AddrPrefixPtr  Pointer to the address
 *                                (only the first PrefixLength bits of this parameter will be used)
 *  \param[in]     PrefixLength   The number of bits of AddrPrefixPtr that are interpreted
 *  \param[out]    EntryIdxPtr    Pointer to a variable in which the index of the matching entry will be stored
 *  \return        E_OK           The given prefix is already contained in the list (at EntryIdxPtr)
 *  \return        E_NOT_OK       The given prefix is not contained in the list (EntryIdx will be unchanged)
 *  \note          This function must be called in a critical section.
 *                 The returned EntryIdxPtr is only valid within this critical section.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VPLLookup(
  TcpIp_IpV6CtrlIterType                         IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                        AddrPrefixPtr,
  uint8                                          PrefixLength,
  IPV6_P2V(TcpIp_SizeOfIpV6PrefixListEntryType)  EntryIdxPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VPLGetOrCreateEntry()
 *********************************************************************************************************************/
/*! \brief         Obtain or create entry in prefix list
 *  \details       -
 *  \param[in]     IpCtrlIdx        Index of Ip Controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     AddrPrefixPtr    Prefix to add to prefix list
 *  \param[in]     PrefixLength     Length of prefix
 *  \param[in]     EntryIdxPtr      Index of the prefix list entry (valid only if E_OK is returned)
 *  \return        E_OK             Entry was found or new entry added
 *  \return        E_NOT_OK         Entry was not found
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VPLGetOrCreateEntry(
  TcpIp_IpV6CtrlIterType                          IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                         AddrPrefixPtr,
  uint8                                           PrefixLength,
  IPV6_P2V(TcpIp_SizeOfIpV6PrefixListEntryType)   EntryIdxPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VPLRemoveEntry()
 *********************************************************************************************************************/
/*! \brief         Remove entry from prefix list
 *  \details       -
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     PlEntryIdx   prefix list entry index
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VPLRemoveEntry(
  TcpIp_IpV6CtrlIterType              IpCtrlIdx,
  TcpIp_SizeOfIpV6PrefixListEntryType PlEntryIdx);

/* === DESTINATION CACHE FUNCTIONS === */

/**********************************************************************************************************************
 *  IpV6_Ndp_VDCLookup()
 *********************************************************************************************************************/
/*! \brief         Look up given destination address in cache
 *  \details       -
 *  \param[in]     IpCtrlIdx     Index of Ip Controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     AddrPtr       Destinationa address
 *  \param[in]     EntryIdxPtr   Index of matching destination cache entry
 *  \return        E_OK          Matching entry found
 *  \return        E_NOT_OK      No matching entry found
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, AUTOMATIC) IpV6_Ndp_VDCLookup(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)    AddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6DestinationCacheEntryType) EntryIdxPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VDCGetOrCreateEntry()
 *********************************************************************************************************************/
/*! \brief         Remove entry from destination cache
 *  \details       -
 *  \param[in]     IpCtrlIdx         Index of Ip Controller
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     DstAddrPtr        Destination Address
 *  \param[in,out] EntryIdxPtr       Index of the Destination cache entry
 *  \param[in]     E_OK              Matching entry was found
 *  \param[in]     E_NOT_OK          No matching entry found
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, AUTOMATIC) IpV6_Ndp_VDCGetOrCreateEntry(
  TcpIp_IpV6CtrlIterType                               IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                              DstAddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6DestinationCacheEntryType)  EntryIdxPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VDCRemoveEntry()
 *********************************************************************************************************************/
/*! \brief         Remove entry from destination cache
 *  \details       -
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     DcEntryIdx   Entry to be removed
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VDCRemoveEntry(
  TcpIp_IpV6CtrlIterType                    IpCtrlIdx,
  TcpIp_SizeOfIpV6DestinationCacheEntryType DcEntryIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_VDCRemoveEntries()
 *********************************************************************************************************************/
/*! \brief         Remove all entries matching the given next hop address
 *  \details       -
 *  \param[in]     IpCtrlIdx        Index of Ip Controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     NextHopAddrPtr   Next hop address of destinations to be removed
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, AUTOMATIC) IpV6_Ndp_VDCRemoveEntries(
  TcpIp_IpV6CtrlIterType   IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)  NextHopAddrPtr);

/* === DEFAULT ROUTER LIST FUNCTIONS === */

/**********************************************************************************************************************
 *  IpV6_Ndp_VDRLCreateEntry()
 *********************************************************************************************************************/
/*! \brief         Create entry in default router list
 *  \details       -
 *  \param[in]     IpCtrlIdx         Index of Ip Controller
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     RouterAddrPtr     Address of router in default router list
 *  \param[in]     EntryIdxPtr       Index of created entry in default router list
 *  \param[in]     E_OK              Entry created successfully
 *  \param[in]     E_NOT_OK          Entry was created successfully
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VDRLCreateEntry(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                                 RouterAddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6DefaultRouterListEntryType)    EntryIdxPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VDRLLookup()
 *********************************************************************************************************************/
/*! \brief         Look up matching router address in default router list
 *  \details       -
 *  \param[in]     IpCtrlIdx         Index of Ip Controller
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     RouterAddrPtr     Router Ip address
 *  \param[in]     EntryIdxPtr       Index of matching entry (Valid only if E_OK is returned)
 *  \param[in]     LocalIpV6AddrIdx  Idx of the local IpV6 address
 *  \param[in]     E_OK              Matching entry was found
 *  \param[in]     E_NOT_OK          No matching entry found
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VDRLLookup(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                                 RouterAddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6DefaultRouterListEntryType)    EntryIdxPtr,
  TcpIp_LocalAddrV6IterType                               LocalIpV6AddrIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_VDRLRemoveEntry()
 *********************************************************************************************************************/
/*! \brief         Remove entry from default router list
 *  \details       -
 *  \param[in]     IpCtrlIdx      Index of Ip Controller
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     drlEntryIdx    Entry to remove
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VDRLRemoveEntry(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  TcpIp_SizeOfIpV6DefaultRouterListEntryType drlEntryIdx);

/* === NEIGHBOR CACHE FUNCTIONS === */

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCLookup()
 *********************************************************************************************************************/
/*! \brief         Lookup the given network address in neighbor cache
 *  \details       -
 *  \param[in]     IpCtrlIdx      Index of Ip Controller
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     NetAddrPtr     Network address for look up
 *  \param[in]     EntryIdxPtr    Index of matching neighbor cache entry (Valid only if E_OK is returned)
 *  \param[in]     E_OK           Matching entry was found
 *  \param[in]     E_NOT_OK       No matching entry found
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_VNCLookup(
  TcpIp_IpV6CtrlIterType                            IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                           NetAddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6NeighborCacheEntryType)  EntryIdxPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCGetOrCreateEntry()
 *********************************************************************************************************************/
/*! \brief           Get or create neighbor cache entry for given address
 *  \details         -
 *  \param[in]       IpCtrlIdx    Index of Ip Controller
 *                                CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]       AddrPtr      Ip address of neighbor
 *  \param[in,out]   EntryIdxPtr  Index of existing neighbor cache entry if exists or
                                  Index of newly created cache entry
 *  \pre             -
 *  \context         TASK|ISR
 *  \reentrant       FALSE
 *  \synchronous     TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VNCGetOrCreateEntry(
  TcpIp_IpV6CtrlIterType                            IpCtrlIdx,
  IPV6_P2C(IpV6_AddrType)                           AddrPtr,
  IPV6_P2V(TcpIp_SizeOfIpV6NeighborCacheEntryType)  EntryIdxPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCUpdateEntry()
 *********************************************************************************************************************/
/*! \brief         Update state of neighbor cache entry
 *  \details       -
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     NcEntryIdx   Index of neighbor cache entry
 *  \param[in]     NewState     Updated state
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VNCUpdateEntry(
  TcpIp_IpV6CtrlIterType                 IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType   NcEntryIdx,
  IpV6_ReachableStateType                  NewState);

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCRemoveEntry()
 *********************************************************************************************************************/
/*! \brief         Remove neighbor cache entry
 *  \details       -
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     NcEntryIdx   Index of neighbor cache entry to be removed
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VNCRemoveEntry(
  TcpIp_IpV6CtrlIterType                  IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType  NcEntryIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_VNCUpdateLinkLayerAddress()
 *********************************************************************************************************************/
/*! \brief         Update link layer address in neighbor cache
 *  \details       -
 *  \param[in]     IpCtrlIdx                Index of Ip Controller
 *                                          CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]     NcEntryIdx               Neighbor cache entry index
 *  \param[in]     NewLinkLayerAddressPtr   Link layer address to be added
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VNCUpdateLinkLayerAddress(
  TcpIp_IpV6CtrlIterType                      IpCtrlIdx,
  TcpIp_SizeOfIpV6NeighborCacheEntryType      NcEntryIdx,
  IPV6_P2C(uint8)                             NewLinkLayerAddressPtr);

/**********************************************************************************************************************
 *  IpV6_Ndp_VStart()
 *********************************************************************************************************************/
/*! \brief         Startup routine for Ndp
 *  \details       Invoked during Ip controller startup
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_VStart(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_Init()
 *********************************************************************************************************************/
/*! \brief         Init routine for Ndp
 *  \details       -
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_Init(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_MainFunction()
 *********************************************************************************************************************/
/*! \brief         Main handling function of Ndp
 *  \details       -
 *  \param[in]     IpCtrlIdx    Index of Ip Controller
 *                              CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(void, IPV6_CODE) IpV6_Ndp_MainFunction(TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  IpV6_Ndp_ClearCache
 *********************************************************************************************************************/
/*! \brief         IpV6_Ndp_ClearCache clears the address resolution cache
 *  \details       -
 *  \param[in]     LocalAddrV6Idx   Index of an IPv6 address specifing the IPv6 controller that shall be cleared
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1] or TCPIP_LOCAL_ADDR_V6_IDX_ANY
 *  \return        E_OK             The request was successful
 *                 E_NOT_OK         The request was not successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
extern FUNC(Std_ReturnType, IPV6_CODE) IpV6_Ndp_ClearCache(
  TcpIp_LocalAddrV6IterType LocalAddrV6Idx);

/**********************************************************************************************************************
 *  IpV6_Ndp_GetCacheEntries
 *********************************************************************************************************************/
/*! \brief          IpV6_Ndp_GetCacheEntries returns the address resolution cache
 *  \details        Copies entries from the physical address cache of the IPv6 instance that is active on the EthIf
 *                  controller specified by ctrlIdx into a user provided buffer. The function will copy all or
 *                  numberOfElements into the output list. If input value of numberOfElements is 0 the function will
 *                  not copy any data but only return the number of valid entries in the cache. EntryListPtr may be
 *                  NULL_PTR in this case.
 *  \param[in]      CtrlIdx             EthIf controller index to identify the related NDP table.
 *  \param[in,out]  NumberOfElementsPtr In: Maximum number of entries that can be stored in Parameters output entryListPtr.
 *                                      Out: Number of entries written to output entryListPtr
 *                                      (Number of all entries in the cache if input value is 0).
 *  \param[out]     EntryListPtr        Pointer to memory where the list of cache entries shall be stored.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          CREQ-115906
 *********************************************************************************************************************/
extern FUNC(void, TCPIP_CODE) IpV6_Ndp_GetCacheEntries(
    TcpIp_IpV6CtrlIterType             IpCtrlIdx,
    TCPIP_P2V(uint32)                  NumberOfElementsPtr,
    TCPIP_P2V(TcpIp_NdpCacheEntryType) EntryListPtr);

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* (TCPIP_SUPPORT_IPV6 == STD_ON) */
#endif  /* IPV6_NDP_H */

/**********************************************************************************************************************
 *  END OF FILE: IpV6_Ndp.h
 *********************************************************************************************************************/
