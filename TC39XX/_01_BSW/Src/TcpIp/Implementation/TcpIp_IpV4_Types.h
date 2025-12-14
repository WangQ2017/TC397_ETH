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
 *         \file  TcpIp_IpV4_Types.h
 *        \brief  Implementation of Internet Protocol version 4 (IPv4) - Type Definitions
 *
 *      \details  This file is part of the TcpIp IPv4 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv4 submodule. >> TcpIp_IpV4.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/

#if !defined (IPV4_TYPES_H)
# define IPV4_TYPES_H

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "TcpIp_Cfg.h"


#include "Std_Types.h"
#include "TcpIp_Types.h"


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef uint8 IpV4_StateType;  /* module state */

typedef struct 
{
  IpBase_AddrInType NetAddr;   /*<!  */
  IpBase_AddrInType NetMask;   /*<!  */
  IpBase_AddrInType DefGwAddr; /*<!  */
} IpV4_IpAddrSetType;

typedef P2VAR(IpV4_IpAddrSetType, TYPEDEF, TCPIP_VAR_NOINIT) IpV4_IpAddrSetPtrType;

#endif  /* (TCPIP_SUPPORT_IPV4 == STD_ON) */
#endif  /* IPV4_TYPES_H */
/**********************************************************************************************************************
 *  END OF FILE: IpV4_Types.h
 *********************************************************************************************************************/
