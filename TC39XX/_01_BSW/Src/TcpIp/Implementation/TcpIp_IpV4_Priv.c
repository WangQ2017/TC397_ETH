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
 *         \file  TcpIp_IpV4_Priv.c
 *        \brief  Implementation of Internet Protocol version 4 (IPv4) - Internal Functions
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

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

#define TCPIP_IPV4_PRIV_SOURCE

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIp_Priv.h"
#include "TcpIp_IpV4_Priv.h"
#include "TcpIp_IpV4.h"
#include "TcpIp_Arp.h"


#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#include "TcpIp.h"


/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/* ----- */
#define TCPIP_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */


#define TCPIP_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */


/**********************************************************************************************************************
 *  IpV4_Ip_VIpAddrAssignmentReadyNotification()
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
FUNC(void, IPV4_CODE) IpV4_Ip_VIpAddrAssignmentReadyNotification(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  uint8                  AddrAssignmentMethod,
  boolean                AddrAssigned)
{
#if (TCPIP_SUPPORT_IP_ADDR_NVM_STORAGE == STD_ON)
  /* #10 Calculate the assignment priority for the given assignment method of the given IP controller
         and read the related assignment configuration. */
  uint8 addrAssignmentPrio = IpV4_Ip_VCfgGetAddrAssignmentPrio(IpV4CtrlIdx, AddrAssignmentMethod);
  TcpIp_AddrAssignmentCfgByPrioStartIdxOfIpV4CtrlType addrAssignmentCfgByPrioStartIdx =
    TcpIp_GetAddrAssignmentCfgByPrioStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
  uint8 addrAssignmentCfg;

  TCPIP_ASSERT(addrAssignmentPrio > 0);
  addrAssignmentPrio--;

  TCPIP_ASSERT(  (addrAssignmentCfgByPrioStartIdx + addrAssignmentPrio)
               < TcpIp_GetAddrAssignmentCfgByPrioEndIdxOfIpV4Ctrl(IpV4CtrlIdx));

  addrAssignmentCfg = TcpIp_GetAddrAssignmentCfgByPrio(addrAssignmentCfgByPrioStartIdx + addrAssignmentPrio);

  /* #20 Check if address assignment of the specified assignment method has been triggered.
         If the assignment has taken place, and lifetime assignment is configured the address is stored in NvM. */
  TCPIP_ASSERT(AddrAssignmentMethod != TCPIP_IPADDR_ASSIGNMENT_NONE);
  TCPIP_ASSERT(IPV4_CHK_BIT_U8(TcpIp_GetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(IpV4CtrlIdx),
                                AddrAssignmentMethod));

  if(    (AddrAssigned == TRUE)
      && (IPV4_CHK_FLAG_U8(addrAssignmentCfg, TCPIP_IPV4_ADDR_ASSIGNMENT_FLAG_LIFETIME_STORE)))
  {
    TCPIP_ASSERT(    TcpIp_GetAddrAssignmentMethodPersistOfIpV4CtrlDyn(IpV4CtrlIdx)
                  == TCPIP_IPADDR_ASSIGNMENT_NONE);

    /* #30 Set 'persist' flag, so address will be written into NvM in MainFunction. */
    TcpIp_SetAddrAssignmentMethodPersistOfIpV4CtrlDyn(IpV4CtrlIdx, AddrAssignmentMethod);                               /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
  }
#else
  IPV4_UNUSED_PARAMETER(IpV4CtrlIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  IPV4_UNUSED_PARAMETER(AddrAssignmentMethod); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  IPV4_UNUSED_PARAMETER(AddrAssigned); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  TcpIp_SetAddrAssignmentReadyChangedOfIpV4CtrlDyn(IpV4CtrlIdx, TRUE);                                                  /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
} /* IpV4_Ip_VIpAddrAssignmentReadyNotification */


#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

#endif  /* (TCPIP_SUPPORT_IPV4 == STD_ON) */
/**********************************************************************************************************************
 *  END OF FILE: IpV4_Priv.c
 *********************************************************************************************************************/
