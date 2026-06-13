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
 *        \file  TcpIp_IpV4.c
 *        \brief  Implementation of Internet Protocol version 4 (IPv4)
 *
 *        \details  This file is part of the TcpIp IPv4 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv4 submodule. >> TcpIp_IpV4.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/


/* PRQA S 0828 EOF */ /* MD_MSR_1.1 */

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

#define TCPIP_IPV4_SOURCE

#include "TcpIp_Lcfg.h"
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "TcpIp_IpV4_Priv.h"

# if (TCPIP_SUPPORT_ICMPV4 == STD_ON)                                                                                   /* COV_TCPIP_ICMPV4_ALWAYS_ON */
#  include "TcpIp_IcmpV4.h"
#  include "TcpIp_IcmpV4_Cbk.h"
# endif
# include "TcpIp_Arp.h"
# include "TcpIp_Priv.h"

# include "IpBase.h"

# if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
#  include "TcpIp_DhcpV4.h"
#  include "TcpIp_DhcpV4_Cbk.h"
# endif

# if (TCPIP_SUPPORT_TCP == STD_ON)
#  include "TcpIp_Tcp_Cbk.h"
# endif

# if (TCPIP_SUPPORT_IPSEC == STD_ON)
# include "TcpIp_IpSec.h"
# endif

# include "TcpIp_Udp_Cbk.h"

# include "EthIf.h"

# include "EthSM.h"

# if (TCPIP_SUPPORT_IP_ADDR_NVM_STORAGE == STD_ON)
#  include "NvM.h"
# endif

# if (TCPIP_SUPPORT_DEM == STD_ON)
#  include "Dem.h"
# endif

# if !defined (STATIC)                                                                                                  /* COV_TCPIP_COMPATIBILITY */
#  define STATIC static
# endif

/*
Design:
- The function Ip_AddrConflictInd only indicates address conflicts for usage with IP-LL config.
  Since DHCP won't probe its addresses (design decision) no further differentiation is necessary.
*/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# define IPV4_IP_TXPROGR_FREE                                         0u
# define IPV4_IP_TXPROGR_REQU                                         1u
# define IPV4_IP_TXPROGR_PART_SENT                                    2u

# define IPV4_IP_TB_STATUS_READY                                      0u
# define IPV4_IP_TB_STATUS_NOT_OK                                     1u

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 5 */ /* MD_MSR_FctLikeMacro */
#  define ETHSM_TCPIP_MODE_INDICATION(CtrlIdx, IsIpAddrAssigned)      \
                                                                      (void)EthSM_VTcpIpModeIndication((CtrlIdx), (IsIpAddrAssigned))

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

# define TCPIP_START_SEC_VAR_NOINIT_32BIT
# include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

STATIC VAR(uint32, IPV4_VAR_NOINIT) IpV4_Ip_TimeMs;

# define TCPIP_STOP_SEC_VAR_NOINIT_32BIT
# include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

/* -------------------------------------------------------------------------- */

# define TCPIP_START_SEC_VAR_NOINIT_16BIT
# include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

STATIC VAR(uint16, IPV4_VAR_NOINIT) IpV4_Ip_Identification;

# define TCPIP_STOP_SEC_VAR_NOINIT_16BIT
# include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

/* -------------------------------------------------------------------------- */

# define TCPIP_START_SEC_VAR_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

# if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_TCPIP_DEV_ERROR_DETECT */
VAR(IpV4_StateType, IPV4_VAR_ZERO_INIT) IpV4_State = IPV4_STATE_UNINIT;
# endif

# define TCPIP_STOP_SEC_VAR_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define TCPIP_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

/**********************************************************************************************************************
 *  IpV4_Ip_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the Ip submodule of the IpV4 subcomponent.
 *  \details        -
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_Init(void);

# if (TCPIP_SUPPORT_IP_ADDR_NVM_STORAGE == STD_ON)
/**********************************************************************************************************************
 *  IpV4_Ip_NvmGetAddrSet
 *********************************************************************************************************************/
/*! \brief          Checks the valid access to the IpV4's NvM address storage and returns the pointer if possible.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx     Index of the affected IPv4 controller.
 *                  CONSTRAINT      [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[out]     IpAddrSetPtrPtr Pointer to C-struct of type IpV4_IpAddrSetPtrType in case access to NvM is possible.
 *                                  NULL_PTR in case access to NvM is not possible.
 *  \param[in]      WriteAccess     TRUE    Get NvM address set for Write Access
 *                                  FALSE   Get NvM address set for Read Access
 *  \return         E_OK            Access to IpV4's NvM RAM is possible.
 *  \return         E_NOT_OK        Access to IpV4's NvM RAM is NOT possible.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_NvmGetAddrSet(
  TcpIp_IpV4CtrlIterType          IpV4CtrlIdx,
  IPV4_P2V(IpV4_IpAddrSetPtrType) IpAddrSetPtrPtr,
  boolean                         WriteAccess);

/**********************************************************************************************************************
 *  IpV4_Ip_NvMBasedAddressHandling
 *********************************************************************************************************************/
/*! \brief          Conducts address handling of the main function in case address storage in NvM is configured.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx Index of the affected IPv4 controller.
 *                  CONSTRAINT  [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_NvMBasedAddressHandling(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx);
# endif

/**********************************************************************************************************************
 *  IpV4_Ip_StandardAddressHandling
 *********************************************************************************************************************/
/*! \brief          Conducts address handling of the main function in case address storage in NvM is NOT configured.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx Index of the affected IPv4 controller.
 *                  CONSTRAINT  [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_StandardAddressHandling(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_StoreRequestedAddress
 *********************************************************************************************************************/
/*! \brief          Stores the (given) requested address depending on the value of the given local IP address.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx      Index of the affected IPv4 controller.
 *                  CONSTRAINT       [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      UnicastAddrV4Idx Index of an IpV4 specific unicast address.
 *  \param[in]      LocalIpAddr      IP address which shall be assigned to the EthIf controller.
 *  \param[in]      NetmaskCidr      Network mask of IPv4 address in CIDR Notation.
 *  \param[in]      DefaultRouter    IP address of the default router (IPV4_ADDR_ANY specifies no default router).
 *  \return         E_OK in case the requested address was stored, E_NOT_OK otherwise (no default address configured).
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_StoreRequestedAddress(
  TcpIp_IpV4CtrlIterType      IpV4CtrlIdx,
  TcpIp_UnicastAddrV4IterType UnicastAddrV4Idx,
  IpBase_AddrInType           LocalIpAddr,
  uint8                       NetmaskCidr,
  IpBase_AddrInType           DefaultRouter);

/**********************************************************************************************************************
 *  IpV4_Ip_MainFunction
 *********************************************************************************************************************/
/*! \brief          Handles the IP global status.
 *  \details        Has to be called every IPV4_MAIN_FCT_PERIOD_MSEC ms.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_MainFunction(void);

/**********************************************************************************************************************
 *  IpV4_Ip_RxIsDuplicateDhcpAddr
 *********************************************************************************************************************/
/*! \brief          Checks whether a foreign packet addressed with an own DHCP address has been received.
 *  \details        In case of duplicate DHCP address and the related DEM error is configured then the DEM error is set.
 *  \param[in]      IpV4CtrlIdx Index of the affected IPv4 controller.
 *                  CONSTRAINT  [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      SrcAddr     Source address of the packet received.
 *  \param[in]      PhysAddrPtr Pointer to the physical address the IP packet was received of.
 *                  CONSTRAINT  Points to uint8 array of size IPBASE_ETH_PHYS_ADDR_LEN_BYTE (size 6)
 *  \return         TRUE: A foreign packet addressed with an own DHCP address has been received
 *  \return         FALSE: No duplicate DHCP address has been detected.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(boolean, IPV4_CODE) IpV4_Ip_RxIsDuplicateDhcpAddr(
  TcpIp_IpV4CtrlIterType    IpV4CtrlIdx,
  IpBase_AddrInType         SrcAddr,
  IPV4_P2C(uint8)           PhysAddrPtr);

/**********************************************************************************************************************
 *  IpV4_Ip_GetLocalAddrIdxMulticast
 *********************************************************************************************************************/
/*! \brief          Determines the localAddrV4Idx for a received multicast packet
 *  \details        -
 *  \param[in]      IpV4CtrlIdx Index of the affected IPv4 controller.
 *                  CONSTRAINT  [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      DestAddr    Destination address of the packet received.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(TcpIp_SizeOfLocalAddrV4Type, IPV4_CODE) IpV4_Ip_GetLocalAddrIdxMulticast(
  TcpIp_IpV4CtrlIterType    IpV4CtrlIdx,
  IpBase_AddrInType         DestAddr);

/**********************************************************************************************************************
 *  IpV4_Ip_ReassembleAndForwardToUpperLayer
 *********************************************************************************************************************/
/*! \brief          Reassemble the packet and forward it to the configured upper layer.
 *  \details        -
 *  \param[in]      DataPtr        Pointer to the IP packet received.
 *                  CONSTRAINT     [Must point to the valid buffer of valid length(IPV4_IP_DEF_HEADER_LENGTH_BYTE) and valid length byte information]
 *  \param[in]      IpV4CtrlIdx    Index of the affected IPv4 controller.
 *                  CONSTRAINT     [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      LocalAddrV4Idx Index of the affected IPv4 address.
 *                  CONSTRAINT     [0..TcpIp_GetSizeOfLocalAddrV4()-1]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_ReassembleAndForwardToUpperLayer(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  TcpIp_LocalAddrV4IterType                LocalAddrV4Idx);

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_GenerateIpAddr
 *********************************************************************************************************************/
/*! \brief          Generates a random link-local IP address according to IETF RFC3927.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx   Index of the affected IPv4 controller.
 *                  CONSTRAINT    [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      ConflictCount Number of link-local address configuration conflicts that occurred on this controller
 *                                since last restart of the address assignment method.
 *  \return         Generated IP address is in range 169.254.1.0 to 169.254.254.255 (inclusive).
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) IpV4_Ip_VLl_GenerateIpAddr(
  TcpIp_IpV4CtrlIterType              IpV4CtrlIdx,
  TcpIp_ConflictsNumOfLlAddrStateType ConflictCount);

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_Reset
 *********************************************************************************************************************/
/*! \brief          Resets variables for the dynamic IP address assignment
 *  \details        -
 *  \param[in]      LlAddrStateIdx of the affected IPv4 controller.
 *                  CONSTRAINT     Refer to the constraint of LlAddrStateIdx described for function IpV4_Ip_VLl_Main().
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_Reset(
  TcpIp_LlAddrStateIdxOfIpV4CtrlType LlAddrStateIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_Start
 *********************************************************************************************************************/
/*! \brief          Starts LINKLOCAL address assignment if not already started.
 *  \details        -
 *  \param[in]      LlAddrStateIdx of the affected IPv4 controller.
 *                  CONSTRAINT     Refer to the constraint of LlAddrStateIdx described for function IpV4_Ip_VLl_Main().
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_Start(
  TcpIp_LlAddrStateIdxOfIpV4CtrlType LlAddrStateIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_Main
 *********************************************************************************************************************/
/*! \brief          Handles the LINKLOCAL address handling.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx Index of the affected IPv4 controller.
 *                  CONSTRAINT  [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                  CONSTRAINT  LlAddrStateIdx of this IpV4CtrlIdx has to fulfill:
 *                              [0..TcpIp_GetSizeOfLlAddrState()-1]
 *                  CONSTRAINT  AutoIpConfigIdx of this IpV4CtrlIdx has to fulfill:
 *                              [0..TcpIp_GetSizeOfAutoIpConfig()-1]
 *                  The constraint of AutoIpConfigIdx is guaranteed by the generator when
 *                  the constraint of LlAddrStateIdx is fulfilled.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_Main(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_HandleStateProbe
 *********************************************************************************************************************/
/*! \brief          Handles the state PROBE of the LINKLOCAL address handling.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx     Index of the affected IPv4 controller.
 *                  CONSTRAINT      Refer to constraints of IpV4CtrlIdx described for function IpV4_Ip_VLl_Main().
 *  \param[in]      LlAddrStateIdx  Index of the address state admin data to be used for LINKLOCAL address handling.
 *                  CONSTRAINT      Refer to constraint of LlAddrStateIdx described for function IpV4_Ip_VLl_Main().
 *  \param[in]      AutoIpConfigIdx Index of the AutoIp configuration to be used for LINKLOCAL address handling.
 *                  CONSTRAINT      Refer to constraint of AutoIpConfigIdx described for function IpV4_Ip_VLl_Main().
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_HandleStateProbe(
  TcpIp_IpV4CtrlIterType              IpV4CtrlIdx,
  TcpIp_LlAddrStateIdxOfIpV4CtrlType  LlAddrStateIdx,
  TcpIp_AutoIpConfigIdxOfIpV4CtrlType AutoIpConfigIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_HandleStateConflict
 *********************************************************************************************************************/
/*! \brief          Handles the state CONFLICT of the LINKLOCAL address handling.
 *  \details        -
 *  \param[in]      LlAddrStateIdx  Index of the address state admin data to be used for LINKLOCAL address handling.
 *                  CONSTRAINT      Refer to constraint of LlAddrStateIdx described for function IpV4_Ip_VLl_Main().
 *  \param[in]      AutoIpConfigIdx Index of the AutoIp configuration to be used for LINKLOCAL address handling.
 *                  CONSTRAINT      Refer to constraint of AutoIpConfigIdx described for function IpV4_Ip_VLl_Main().
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_HandleStateConflict(
  TcpIp_LlAddrStateIdxOfIpV4CtrlType  LlAddrStateIdx,
  TcpIp_AutoIpConfigIdxOfIpV4CtrlType AutoIpConfigIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_HandleStateAnnounce
 *********************************************************************************************************************/
/*! \brief          Handles the state ANNOUNCE of the LINKLOCAL address handling.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx     Index of the affected IPv4 controller.
 *                  CONSTRAINT      Refer to constraints of IpV4CtrlIdx described for function IpV4_Ip_VLl_Main().
 *  \param[in]      LlAddrStateIdx  Index of the address state admin data to be used for LINKLOCAL address handling.
 *                  CONSTRAINT      Refer to constraint of LlAddrStateIdx described for function IpV4_Ip_VLl_Main().
 *  \param[in]      AutoIpConfigIdx Index of the AutoIp configuration to be used for LINKLOCAL address handling.
 *                  CONSTRAINT      Refer to constraint of AutoIpConfigIdx described for function IpV4_Ip_VLl_Main().
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_HandleStateAnnounce(
  TcpIp_IpV4CtrlIterType              IpV4CtrlIdx,
  TcpIp_LlAddrStateIdxOfIpV4CtrlType  LlAddrStateIdx,
  TcpIp_AutoIpConfigIdxOfIpV4CtrlType AutoIpConfigIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_FindAddr
 *********************************************************************************************************************/
/*! \brief          Searches for a LINKLOCAL address in the scope of the LINKLOCAL address handling.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx     Index of the affected IPv4 controller.
 *                  CONSTRAINT      Refer to the constraints of IpV4CtrlIdx described for function IpV4_Ip_VLl_Main().
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_FindAddr(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_VForwardPacketToUpperLayer()
 *********************************************************************************************************************/
/*! \brief          Forwards IP packet payload to the corresponding upper layer (TCP, UDP, ICMP) for the protocol.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx    Index of the affected IPv4 controller.
 *                  CONSTRAINT     [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      LocalAddrV4Idx Index of the affected IPv4 address
 *                  CONSTRAINT     [0..TcpIp_GetSizeOfLocalAddrV4()-1]
 *  \param[in]      DataPtr        Pointer to the IP packet received.
                    CONSTRAINT     [Must point to the valid buffer of size IpV4PayloadLen]
 *  \param[in]      IpV4PayloadPtr Pointer to the payload of the received IP packet.
 *                  CONSTRAINT     Memory are pointed to has to have the size of IpV4PayloadLen.
 *  \param[in]      IpV4PayloadLen Length of the received IP packet.
 *                  CONSTRAINT     <= sizeof( <memory pointed to IpV4PayloadPtr> )
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VForwardPacketToUpperLayer(
  TcpIp_IpV4CtrlIterType    IpV4CtrlIdx,
  TcpIp_LocalAddrV4IterType LocalAddrV4Idx,
  IPV4_P2C(uint8)           DataPtr,
  IPV4_P2V(uint8)           IpV4PayloadPtr,
  uint16                    IpV4PayloadLen);

/**********************************************************************************************************************
 *  IpV4_Ip_VReassemblyInitBuffers()
 *********************************************************************************************************************/
/*! \brief          Initializes all configured reassembly buffers.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VReassemblyInitBuffers(void);

/**********************************************************************************************************************
 *  IpV4_Ip_VReassemblyFindBufferDesc()
 *********************************************************************************************************************/
/*! \brief          Locates a matching, an unused or the least recently used reassembly buffer descriptor.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx      Index of the affected IPv4 controller.
 *                  CONSTRAINT       Refer to the CONSTRAINTs of this parameter given at the caller of this function:
 *                                   IpV4_Ip_VReassemblyRxIndication()
 *  \param[in]      DataPtr          Pointer to the IP packet received.
 *  \param[out]     UnusedDescIdxPtr Index of an unused reassembly buffer descriptor.
 *                                   This out-pointer is set to a valid value only in case no matching reassembly buffer
 *                                   descriptor was found. Otherwise the value is IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV.
 *  \param[out]     OldestDescIdxPtr Index of the oldest (least recently used) reassembly buffer descriptor.
 *                                   This out-pointer is set to a valid value only in case no matching reassembly buffer
 *                                   descriptor was found. Otherwise the value is IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV.
 *  \return                          Index of the reassembly buffer descriptor that fits to the IpV4 packet pointed to
 *                                   by the given DataPtr parameter.
 *  \return                          IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV if no matching descriptor was found that fits
 *                                   to the IpV4 packet pointed to by the given DataPtr parameter.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(TcpIp_SizeOfReassemblyBufferDescType, IPV4_CODE) IpV4_Ip_VReassemblyFindBufferDesc(
  TcpIp_IpV4CtrlIterType                         IpV4CtrlIdx,
  IPV4_P2C(uint8)                                DataPtr,
  IPV4_P2V(TcpIp_SizeOfReassemblyBufferDescType) UnusedDescIdxPtr);

/**********************************************************************************************************************
 *  IpV4_Ip_VReassemblyGetBufferDesc()
 *********************************************************************************************************************/
/*! \brief          Returns a matching or a newly initialized reassembly buffer descriptor.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx Index of the IP controller/instance.
 *                  CONSTRAINT  Refer to the CONSTRAINTs of this parameter given at the caller of this function:
 *                              IpV4_Ip_VReassemblyRxIndication()
 *  \param[in]      DataPtr     Pointer to the IP packet received.
 *  \return                     Index of a valid reassembly buffer descriptor.
 *  \return                     IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV: No reassembly buffer is currently available.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferDescIterType, IPV4_CODE) IpV4_Ip_VReassemblyGetBufferDesc(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IPV4_P2C(uint8)        DataPtr);

/**********************************************************************************************************************
 *  IpV4_Ip_VReassemblyGetBufferPtr()
 *********************************************************************************************************************/
/*! \brief          Returns the reassembly buffer that is currently assigned to the given reassembly buffer descriptor.
 *  \details        -
 *  \param[in]      ReassemblyBufDescPtr Pointer to the reassembly buffer descriptor to be used.
 *                  CONSTRAINT           ReassemblyBufDescPtr->Status must be:
 *                                       IPV4_IP_REASSEMBLY_BUF_STATUS_[IN_PROGRESS|COMPLETE].
 *  \return                              Pointer to the assigned reassembly buffer.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC_P2VAR(uint8, AUTOMATIC, IPV4_CODE) IpV4_Ip_VReassemblyGetBufferPtr(
  IPV4_P2C(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr);

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyAdaptGapBeginning()
 ***********************************************************************************************************/
/*! \brief          Reassembles fragmented IP datagrams.
 *  \details        Reassembles fragmented IP datagrams under these conditions:
 *                  EITHER: Fragment completely fits into gap.
 *                  OR: Fragment starts at beginning of gap but does not completely fill the gap.
 *  \param[in,out]  ReassemblyBufDescPtr Pointer to the reassembly buffer descriptor to be used.
 *                                       [Has to point to an element of the configured array
 *                                        of type IpV4_Ip_ReassemblyBufferDescType
 *                                        returned by TcpIp_GetReassemblyBufferDescDyn()]
 *  \param[in]      FragEndOfs           End offset of the fragment within the overall IP packet.
 *  \param[in]      ThisGapEndOfs        Offset of the end of the current gap within the overall IP packet.
 *  \param[in]      PrevGapOfs           Offset of the previous gap within the overall IP packet.
 *  \param[in]      NextGapOfs           Offset of the next gap within the overall IP packet.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VReassemblyAdaptGapBeginning(
  IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr,
  uint16                                     FragEndOfs,
  uint16                                     ThisGapEndOfs,
  uint16                                     PrevGapOfs,
  uint16                                     NextGapOfs);

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyAdaptGapNonBeginning()
 ***********************************************************************************************************/
/*! \brief          Reassembles fragmented IP datagrams.
 *  \details        Reassembles fragmented IP datagrams under these conditions:
 *                  EITHER fragment ends at end of gap but does not start at beginning of gap
 *                  OR: fragment fills some part in the middle of the gap but there will remain a gap
 *                  before and after the fragment.
 *  \param[in]      ReassemblyBufPtr Pointer to the reassembly buffer to be used.
 *  \param[in]      FragOfs          (Start) Offset of the fragment within the overall IP packet.
 *  \param[in]      FragEndOfs       End offset of the fragment within the overall IP packet.
 *  \param[in]      ThisGapOfs       Offset of the current gap within the overall IP packet.
 *  \param[in]      ThisGapEndOfs    Offset of the end of the current gap within the overall IP packet.
 *  \param[in]      NextGapOfs       Offset of the next gap within the overall IP packet.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VReassemblyAdaptGapNonBeginning(
  IPV4_P2V(uint8) ReassemblyBufPtr,
  uint16          FragOfs,
  uint16          FragEndOfs,
  uint16          ThisGapOfs,
  uint16          ThisGapEndOfs,
  uint16          NextGapOfs);

/**********************************************************************************************************************
 *  IpV4_Ip_VReassemblyAdaptGap()
 *********************************************************************************************************************/
/*! \brief          Adapts the linked list of 'gaps' (payload/fragments not received yet) based on a received fragment.
 *  \details        The gaps are managed as linked list inside the reassembly buffer as suggested in
 *                  [RFC815 4. Part Two: Managing the Hole Descriptor List].
 *  \param[in,out]  ReassemblyBufDescPtr IN: The reassembly buffer descriptor to be used
 *                                       OUT: Reassembly buffer descriptor to be used with updated values.
 *  \param[in]      FragOfs              Offset of the fragment payload. [bytes]
 *  \param[in]      FragEndOfs           Offset of the fragment payload end. [bytes]
 *  \param[in]      ThisGapOfs           Start offset of the gap that shall be adapted. [bytes]
 *  \param[in]      ThisGapEndOfs        End offset of the gap that shall be adapted. [bytes]
 *  \param[in]      PrevGapOfs           Start offset of the previous gap [bytes].
 *                                       Position and length of current gap are stored here.
 *  \param[in]      NextGapOfs           Start offset of the following gap. [bytes]
 *                                       Gap may be joined with the current gap.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VReassemblyAdaptGap(
  IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr,
  uint16                                     FragOfs,
  uint16                                     FragEndOfs,
  uint16                                     ThisGapOfs,
  uint16                                     ThisGapEndOfs,
  uint16                                     PrevGapOfs,
  uint16                                     NextGapOfs);

/**********************************************************************************************************************
 *  IpV4_Ip_VReassemblyHandleGaps()
 *********************************************************************************************************************/
/*! \brief          Returns the reassembly buffer index where the payload of a received fragment shall be stored.
 *  \details        Also updates the linked list of the payload fragments, not yet received.
 *                  The gaps are managed as linked list inside the reassembly buffer as suggested in
 *                  [RFC815 4. Part Two: Managing the Hole Descriptor List].
 *  \param[in,out]  ReassemblyBufDescPtr IN: The reassembly buffer descriptor to be used
 *                                       OUT: Reassembly buffer descriptor to be used with updated values.
 *  \param[in]      FragOfs              Offset of the fragment payload. [bytes]
 *  \param[in]      FragLen              Length of the fragment payload. [bytes]
 *  \param[in]      FragIsLast           TRUE if this is the last fragment, FALSE otherwise.
 *  \param[out]     GapOfsPtr            Reassembly buffer index where to payload of the fragment shall be copied to.
 *                                       IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS:
 *                                       In case reassembly buffer is too small to hold the fragment.
 *  \return         E_OK                 Fragment fits into a gap. Payload can be copied to *GapOfsPtr.
 *  \return         E_NOT_OK             Fragment does not fit into a gap.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_VReassemblyHandleGaps(
  IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr,
  uint16                                     FragOfs,
  uint16                                     FragLen,
  boolean                                    FragIsLast,
  IPV4_P2V(uint16)                           GapOfsPtr);

/**********************************************************************************************************************
 *  IpV4_Ip_VReassemblyRxFragment()
 *********************************************************************************************************************/
/*! \brief          Receives an IP fragment and returns the reassembled IP packet if all fragments were received.
 *  \details        Is able to handle reception of out-of-order fragments.
 *                  Result of the function is reflected by ReassemblyBufDescPtr->Status.
 *  \param[in,out]  ReassemblyBufDescPtr IN: The reassembly buffer descriptor to be used
 *                                       OUT: Reassembly buffer descriptor to be used with updated values.
 *  \param[in]      FragAbsByteOfs       Offset of the fragment payload. [bytes]
 *  \param[in]      FragPayloadPtr       Payload of the fragment.
 *  \param[in]      FragPayloadLen       Length of the fragment payload. [bytes]
 *  \param[in]      FragIsLast           TRUE if this is the last fragment, FALSE otherwise.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VReassemblyRxFragment(
  IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr,
  uint16                                     FragAbsByteOfs,
  IPV4_P2C(uint8)                            FragPayloadPtr,
  uint16                                     FragPayloadLen,
  boolean                                    FragIsLast);

/**********************************************************************************************************************
 *  IpV4_Ip_VReassemblyRxFragmentInOrder()
 *********************************************************************************************************************/
/*! \brief          Receives an IP fragment and yields the reassembled IP packet if all fragments were received.
 *  \details        Will abort reassembly if the fragment does directly follow the previous received fragment.
 *                  Result of the function is reflected by ReassemblyBufDescPtr->Status.
 *                  Reassembled IP packet is available in case: Status == IPV4_IP_REASSEMBLY_BUF_STATUS_COMPLETE.
 *  \param[in,out]  ReassemblyBufDescPtr   IN: The reassembly buffer descriptor to be used
 *                                         OUT: Reassembly buffer descriptor to be used with updated values.
 *  \param[in]      FragAbsByteOfs         Offset of the fragment payload. [bytes]
 *  \param[in]      FragPayloadPtr         Payload of the fragment.
 *  \param[in]      FragPayloadLen         Length of the fragment payload. [bytes]
 *  \param[in]      FragIsLast             TRUE if this is the last fragment, FALSE otherwise.
 *  \param[in]      FragmentationConfigIdx Index of the fragmentation config to be used.
 *                  CONSTRAINT             [0..TcpIp_GetSizeOfFragmentationConfig()-1]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VReassemblyRxFragmentInOrder(
  IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr,
  uint16                                     FragAbsByteOfs,
  IPV4_P2C(uint8)                            FragPayloadPtr,
  uint16                                     FragPayloadLen,
  boolean                                    FragIsLast,
  TcpIp_FragmentationConfigIdxOfIpV4CtrlType FragmentationConfigIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_VReassemblyCheckFragment()
 *********************************************************************************************************************/
/*! \brief          Verifies that the first and the last fragment are not received twice.
 *  \details        -
 *  \param[in,out]  ReassemblyBufDescPtr IN: The reassembly buffer descriptor to be used
 *                                       OUT: Reassembly buffer descriptor to be used with updated values.
 *  \param[in]      FragBlockOfs         Offset of the fragment payload. [bytes]
 *  \param[in]      FragIsLast           TRUE if this is the last fragment, FALSE otherwise.
 *  \return         TRUE                 Fragment is valid.
 *  \return         FALSE                Fragment is not valid. (first or last fragment received twice)
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(boolean, IPV4_CODE) IpV4_Ip_VReassemblyCheckFragment(
  IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr,
  uint16                                     FragBlockOfs,
  boolean                                    FragIsLast);

/**********************************************************************************************************************
 *  IpV4_Ip_VReassemblyRxIndication()
 *********************************************************************************************************************/
/*! \brief          Handles reception of a fragmented IP packet.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx       Index the IP controller/instance.
 *                  CONSTRAINT        [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                  CONSTRAINT        The IPv4 controller given by IpV4CtrlIdx has to have:
 *                                    1. a fragmentation config assigned i.e.
 *                                       TcpIp_GetFragmentationConfigIdxOfIpV4Ctrl(IpV4CtrlIdx) has to fulfill
 *                                       [0..TcpIp_GetSizeOfFragmentationConfig() - 1) AND
 *                                    2. at least one reassembly buffer descriptor assigned
 *                                       (the related start index in the fragmentation config has to be valid)
 *  \param[in]      DataPtr           Pointer to the IP packet received.
 *  \param[in,out]  FragPayloadPtrPtr In:  Payload of the received IPv4 packet.
 *                                    Out: Payload of the reassembled IPv4 packet. (if TRUE is returned)
 *                  CONSTRAINT        [FragPayloadPtrPtr != NULL, *FragPayloadPtrPtr != 0]
 *  \param[in,out]  FragPayloadLenPtr In:  Payload length of the received IPv4 packet. [bytes]
 *                                    Out: Payload length of the reassembled IPv4 packet. [bytes] (if TRUE is returned)
 *                  CONSTRAINT        [FragPayloadLenPtr != NULL, *FragPayloadLenPtr != 0]
 *  \return         TRUE              IPv4 packet reassembled. (*FragPayloadPtrPtr and *FragPayloadLenPtr updated)
 *  \return         FALSE             Packet was dropped or reassembly is still progress (other fragments missing).
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(boolean, IPV4_CODE) IpV4_Ip_VReassemblyRxIndication(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IPV4_P2C(uint8)        DataPtr,
  IPV4_P2V(uint8*)       FragPayloadPtrPtr,
  IPV4_P2V(uint16)       FragPayloadLenPtr);

/**********************************************************************************************************************
 *  IpV4_Ip_VFragmentProvideTxBuffers()
 *********************************************************************************************************************/
/*! \brief          Provides the required number of ethernet buffers for transmitting the (fragmented) IP packet.
 *  \details        Even though the parameter IpTxReqDescrPtr contains a member CtrlIdx, also,
 *                  the parameter IpV4CtrlIdx can NOT be removed!
 *  \param[in]      IpV4CtrlIdx     Index the IP controller/instance.
 *                  CONSTRAINT      [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      SocketIdx       Index of the upper layer socket.
 *  \param[in]      IpPayloadLen    Length of the IP payload. [bytes]
 *                                  If this length exceeds the IP MTU, multiple buffers are provided.
 *  \param[in,out]  IpTxReqDescrPtr IP TX request descriptor.
 *  \return         E_OK            Buffer(s) provided.
 *  \return         FALSE           No buffer provided.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(BufReq_ReturnType, IPV4_CODE) IpV4_Ip_VFragmentProvideTxBuffers(
  TcpIp_IpV4CtrlIterType                    IpV4CtrlIdx,
  TcpIp_SocketDynIterType                   SocketIdx,
  uint16                                    IpPayloadLen,
  IPV4_P2V(TcpIp_IpTxRequestDescriptorType) IpTxReqDescrPtr);

/**********************************************************************************************************************
 *  IpV4_Ip_VStoreProtocolChecksum
 *********************************************************************************************************************/
/*! \brief          Stores the protocol checksum value at the correct offset inside the protocol header.
 *  \details        -
 *  \param[in]      Protocol          Upper layer protocol.
 *                  CONSTRAINT        [TCPIP_PROTOCOL_TCP,  TCPIP_PROTOCOL_UDP, IPV4_IP_PROTOCOL_ICMP]
 *  \param[in]      ProtocolChecksum  Calculated Internet checksum value.
 *  \param[in,out]  ProtocolHeaderPtr Position of the beginning of the upper layer protocol header.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VStoreProtocolChecksum(
  uint8           Protocol,
  uint16          ProtocolChecksum,
  IPV4_P2V(uint8) ProtocolHeaderPtr);

/**********************************************************************************************************************
 *  IpV4_Ip_VTransmitFragments
 *********************************************************************************************************************/
/*! \brief          Transmits an IP packet or all fragments of an IP packet, if the packet is fragmented.
 *  \details        Even though the parameter IpTxReqDescrPtr contains a member CtrlIdx, also,
 *                  the parameter IpV4CtrlIdx can NOT be removed!
 *  \param[in]      IpV4CtrlIdx       Index the IP controller/instance.
 *                  CONSTRAINT        [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      IpTxReqDescrPtr   IP TX request descriptor.
 *                  CONSTRAINT        IpTxReqDescrPtr->SockIdx
 *                                      [0..TcpIp_GetSizeOfIpV4SocketDyn()-1]
 *                  CONSTRAINT        IpTxReqDescrPtr->BufIdx
 *                                      [0..(  TcpIp_GetBuf2TxReqMapEndIdxOfIpV4Ctrl(IpV4CtrlIdx)
 *                                           - TcpIp_GetBuf2TxReqStartIdxOfIpV4Ctrl (IpV4CtrlIdx))]
 *  \param[in]      IpProtocol        IP protocol type.
 *                  CONSTRAINT        [TCPIP_PROTOCOL_TCP,  TCPIP_PROTOCOL_UDP, IPV4_IP_PROTOCOL_ICMP]
 *  \param[in]      IpPayloadLen      Total length of the IP payload that shall be sent.
 *                                    Must not be bigger than the requested length in Ip_ProvideTxBuffer.
 *                                    If value is less than the requested length only the required number
 *                                    fragments is transmitted and the remaining fragment buffers are released.
 *  \param[in]      DestPhysAddrPtr   Physical address of the destination of the IP packet.
 *                  CONSTRAINT        Points to uint8 array of size IPBASE_ETH_PHYS_ADDR_LEN_BYTE (size 6)
 *  \param[in]      CalculateChecksum Calculate Internet checksum of upper layer protocol in software.
 *  \param[in]      ReqTxConfirmation Request a TX confirmation from lower layer (EthIf).
 *  \param[in]      UlReqIdx          Upper layer request index.
 *                                    User defined value that will be passed to to TxConfirmation callback.
 *  \param[in]      Identification    Identification field of the IP datagram.
 *  \return         E_OK              Transmit of all fragments accepted.
 *  \return         FALSE             Transmit failed.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_VTransmitFragments(
  TcpIp_IpV4CtrlIterType                    IpV4CtrlIdx,
  IPV4_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescrPtr,
  uint8                                     IpProtocol,
  uint16                                    IpPayloadLen,
  IPV4_P2V(uint8)                           DestPhysAddrPtr,
  boolean                                   CalculateChecksum,
  boolean                                   ReqTxConfirmation,
  uint8                                     UlReqIdx,
  uint16                                    Identification);

/**********************************************************************************************************************
 *  IpV4_Ip_VGetLocalAddrIdxAndCtrlIdx
 *********************************************************************************************************************/
/*! \brief          Returns the IP controller and local address index for the given destination address.
 *  \details        Returns the IP controller index of the given addrId or finds a suitable controller index and addrId
 *                  that matches best for the destAddr.
 *  \param[in,out]  LocalAddrV4IdxPtr In:   IP address idx for which the IP controller index shall be returned or
 *                                          TCPIP_LOCAL_ADDR_V4_IDX_ANY: In case IP address identifier and
 *                                          controller index shall be determined, using the address given via DestAddr.
 *                  CONSTRAINT              [0..TcpIp_GetSizeOfLocalAddrV4()-1] | TCPIP_LOCAL_ADDR_V4_IDX_ANY
 *                                    Out:  IP address identifier that belongs to returned IP controller.
 *  \param[in]      DestAddr          Destination IP address.
 *  \return         Index of the matching IP controller instance in case a matching controller exists.
 *                  TcpIp_GetSizeOfIpV4Ctrl() otherwise.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlIterType, IPV4_CODE) IpV4_Ip_VGetLocalAddrIdxAndCtrlIdx(
  IPV4_P2V(TcpIp_LocalAddrV4IterType) LocalAddrV4IdxPtr,
  IpBase_AddrInType                   DestAddr);

/**********************************************************************************************************************
 *  IpV4_Ip_VGetNextHopPhysAddr
 *********************************************************************************************************************/
/*! \brief          Returns the link layer (physical/MAC) address of the next hop that shall be used to reach DestAddr.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx        Index the IP controller/instance.
 *                  CONSTRAINT         [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      DestAddr           Destination IP address.
 *  \param[in]      SocketIdx          Upper layer socket index. (used for optimized/cached lookup)
 *  \param[out]     NextHopPhysAddrPtr Address of the next hop.
 *                  CONSTRAINT         [Must point to an array of 6 bytes of memory.]
 *  \return         E_OK               Next hop address returned.
 *  \return         E_NOT_OK           No next hop known. Destination not reachable.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(TcpIp_ReturnType, IPV4_CODE) IpV4_Ip_VGetNextHopPhysAddr(
  TcpIp_IpV4CtrlIterType  IpV4CtrlIdx,
  IpBase_AddrInType       DestAddr,
  TcpIp_SocketDynIterType SocketIdx,
  IPV4_P2V(uint8)         NextHopPhysAddrPtr);

#  if (TCPIP_SUPPORT_IP_ETHIF_ADDR_FILTER_API == STD_ON)
/**********************************************************************************************************************
 *  IpV4_Ip_VJoinMulticastGroup
 *********************************************************************************************************************/
/*! \brief          Lets the affected IPv4 controller join or leave the multicast group of the given multicast address.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx   Index of the affected IPv4 controller.
 *                  CONSTRAINT    [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      MulticastAddr Multicast address the group shall be joined or left of.
 *  \param[in]      Join          Flag whether the multicast group shall be joined or left.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VJoinMulticastGroup(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IpBase_AddrInType      MulticastAddr,
  boolean                Join);
#  endif

/**********************************************************************************************************************
 *  IpV4_Ip_VUpdateMulticastMemberships
 *********************************************************************************************************************/
/*! \brief          Initialize all configured multicast address assignments of the given IP controller
 *  \details        -
 *  \param[in]      IpV4CtrlIdx Index of the affected IPv4 controller.
 *                  CONSTRAINT  [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      Join        Flag whether multicast membership shall be stopped or started.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VUpdateMulticastMemberships(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  boolean                Join);

/**********************************************************************************************************************
 *  IpV4_Ip_VGetBestAvailableAddrAssignment()
 *********************************************************************************************************************/
/*! \brief          Find available IP address assignment method that has highest priority (STATIC, DHCP, LINKLOCAL).
 *  \details        -
 *  \param[in]      IpV4CtrlIdx Index of the affected IPv4 controller.
 *                  CONSTRAINT  [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[out]     AddrInfoPtr IP address information (IP address, Netmask, Default Router) tuple.
 *  \return         TCPIP_IPADDR_ASSIGNMENT_NONE      No IP address assignment ready.
 *  \return         TCPIP_IPADDR_ASSIGNMENT_STATIC    STATIC    has highest priority.
 *  \return         TCPIP_IPADDR_ASSIGNMENT_DHCP      DHCP      has highest priority.
 *  \return         TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL LINKLOCAL has highest priority.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(TcpIp_IpAddrAssignmentType, IPV4_CODE) IpV4_Ip_VGetBestAvailableAddrAssignment(
  TcpIp_IpV4CtrlIterType       IpV4CtrlIdx,
  IPV4_P2V(IpV4_IpAddrSetType) AddrInfoPtr);

/**********************************************************************************************************************
 *  IpV4_Ip_VGetActiveAddressOfAssignmentMethod()
 *********************************************************************************************************************/
/*! \brief          Checks whether an address assignment method is ready and returns the address parameters.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx          Index of the affected IPv4 controller.
 *                  CONSTRAINT           [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      AddrAssignmentMethod Address assignment method (DHCP, LINKLOCAL, STATIC).
 *  \param[out]     AddrInfoPtr          IP address information (IP address, Netmask, Default Router) tuple.
 *  \return         TRUE                 Address assignment method is ready.
 *  \return         FALSE                Address assignment method is not ready. (No address available)
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different controllers.
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(boolean, IPV4_CODE) IpV4_Ip_VGetActiveAddressOfAssignmentMethod(
  TcpIp_IpV4CtrlIterType       IpV4CtrlIdx,
  TcpIp_IpAddrAssignmentType   AddrAssignmentMethod,
  IPV4_P2V(IpV4_IpAddrSetType) AddrInfoPtr);

/**********************************************************************************************************************
 *  IpV4_Ip_VEnableAddrAssignmentMethod()
 *********************************************************************************************************************/
/*! \brief          Triggers address assignment in case the trigger value differs from the current value.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx          Index of the affected IPv4 controller.
 *                  CONSTRAINT           [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                  CONSTRAINT           In case AddrAssignmentMethod is TCPIP_IPADDR_ASSIGNMENT_DHCP:
 *                                         TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE
 *                                         TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE
 *                                       In case AddrAssignmentMethod is TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL:
 *                                         TcpIp_IsLlAddrStateUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE
 *                                       For both assignment methods, DHCP and LINKLOCAL:
 *                                         IpV4_Ip_VCfgIsAddrAssignmentEnabled(IpV4CtrlIdx, <Assignment Method>) == TRUE
 *  \param[in]      AddrAssignmentMethod Assignment method to enable.
 *  \param[in]      AddrAssignmentCfg    Assignment configuration to be used for enabling.
 *  \return         E_OK in case the given AddrAssignmentMethod is valid and active in the configuration,
 *  \return         E_NOT_OK otherwise.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_VEnableAddrAssignmentMethod(
  TcpIp_IpV4CtrlIterType            IpV4CtrlIdx,
  TcpIp_IpAddrAssignmentType        AddrAssignmentMethod,
  TcpIp_AddrAssignmentCfgByPrioType AddrAssignmentCfg);

/**********************************************************************************************************************
 *  IpV4_Ip_VDisableAddrAssignmentMethod()
 *********************************************************************************************************************/
/*! \brief          Disables address assignment for the given assignment method.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx Index of the affected IPv4 controller.
 *                  CONSTRAINT  [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      AddrAssignmentMethod  Assignment method to disable.
 *  \return         E_OK in case the disabling was successful (i.e. the assignment method was enabled, before).
 *  \return         E_NOT_OK in case the disabling was not successful.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_VDisableAddrAssignmentMethod(
  TcpIp_IpV4CtrlIterType     IpV4CtrlIdx,
  TcpIp_IpAddrAssignmentType AddrAssignmentMethod);

/**********************************************************************************************************************
 *  IpV4_Ip_VTriggerAddrAssignment()
 *********************************************************************************************************************/
/*! \brief          Set/Unset address assignment trigger. Start/stop dynamic (DHCP, LINKLOCAL) assignment if necessary.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx       Index of the affected IPv4 controller.
 *                  CONSTRAINT        [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      AddrAssignmentCfg IP address assignment configuration set.
 *  \param[in]      TriggerValue      Specifies whether the flag shall be set (TRUE) or unset (FALSE).
 *  \return         E_OK     Flag was changed.
 *  \return         E_NOT_OK Flag was already set/unset.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) IpV4_Ip_VTriggerAddrAssignment(
  TcpIp_IpV4CtrlIterType            IpV4CtrlIdx,
  TcpIp_AddrAssignmentCfgByPrioType AddrAssignmentCfg,
  boolean                           TriggerValue);

/**********************************************************************************************************************
 *  IpV4_Ip_VTriggerAutomaticAddrAssignments()
 *********************************************************************************************************************/
/*! \brief          Sets trigger flags for all configured unicast address assignments with trigger AUTOMATIC.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx Index of the affected IPv4 controller.
 *                  CONSTRAINT  [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VTriggerAutomaticAddrAssignments(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_VSetCtrlStateOffline()
 *********************************************************************************************************************/
/*! \brief          Sets IP controller into state OFFLINE and perform required operations based on current state.
 *  \details        In state OFFLINE the IP controller does not send any messages.
 *                  This state is entered based on the current state of the ethernet transceiver.
 *  \param[in]      IpV4CtrlIdx Index of the affected IPv4 controller.
 *                  CONSTRAINT  [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VSetCtrlStateOffline(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_VSetCtrlStateOnlinePassive()
 *********************************************************************************************************************/
/*! \brief          Sets IP controller into state ONLINE_PASSIVE and perform required operations based on current state.
 *  \details        In state ONLINE_PASSIVE the IP controller is online
 *                  but has not yet completed unicast address assignment.
 *  \param[in]      IpV4CtrlIdx Index of the affected IPv4 controller.
 *                  CONSTRAINT  [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VSetCtrlStateOnlinePassive(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_VSetCtrlStateOnlineActive()
 *********************************************************************************************************************/
/*! \brief          Sets IP controller into state ONLINE_ACTIVE and perform required operations based on current state.
 *  \details        In state ONLINE_ACTIVE the IP controller is online and has completed unicast address assignment.
 *  \param[in]      IpV4CtrlIdx Index of the affected IPv4 controller.
 *                  CONSTRAINT  [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VSetCtrlStateOnlineActive(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_VCtrlIsOnline
 *********************************************************************************************************************/
/*! \brief          Determines whether a IP instance/controller is ONLINE.
 *  \details        -
 *  \param[in]      IpV4CtrlIdx Index of the affected IPv4 controller.
 *                  CONSTRAINT  [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \return         TRUE in case the IP controller is ONLINE, FALSE otherwise.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(boolean, IPV4_CODE) IpV4_Ip_VCtrlIsOnline(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  IpV4_VLocalIpAddrAssignmentChange()
 *********************************************************************************************************************/
/*! \brief          Notifies upper layers about an IP address assignment change of a unicast or multicast address.
 *  \details        -
 *  \param[in]      LocalAddrV4Idx Index of the affected IPv4 address of the assignment change.
 *                  CONSTRAINT     [0..TcpIp_GetSizeOfLocalAddrV4()-1]
 *  \param[in]      State          New state of the affected IPv4 address.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_VLocalIpAddrAssignmentChange(
  TcpIp_LocalAddrV4IterType LocalAddrV4Idx,
  TcpIp_IpAddrStateType     State);

/**********************************************************************************************************************
 *  IpV4_Ip_VChangeMulticastAddrAssignment
 *********************************************************************************************************************/
/*! \brief          Changes value of a multicast address.
 *  \details        -
 *  \param[in]      LocalAddrV4Idx Index of the affected IPv4 address of the assignment change.
 *                  CONSTRAINT     [0..TcpIp_GetSizeOfLocalAddrV4()-1]
 *                  CONSTRAINT     TcpIp_IsMulticastAddrV4UsedOfLocalAddrV4(LocalAddrV4Idx) == TRUE
 *  \param[in]      NetAddr        Value that shall be assigned to the specified multicast address index.
 *  \return         E_OK           Address was changed.
 *  \return         E_NOT_OK       Address could not be changed.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different controllers.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) IpV4_Ip_VChangeMulticastAddrAssignment(
  TcpIp_LocalAddrV4IterType LocalAddrV4Idx,
  IpBase_AddrInType         NetAddr);

/**********************************************************************************************************************
 *  IpV4_Ip_VCtrlStateStartup()
 *********************************************************************************************************************/
/*! \brief            Control State startup routine
 *  \details          -
 *  \param[in]        IpV4CtrlIdx  IP Controller Index
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV4ctrl()-1]
 *  \pre              -
 *  \context          TASK
 *  \reentrant        FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Ip_VCtrlStateStartup(uint8 IpV4CtrlIdx);

/**********************************************************************************************************************
 *  IpV4_Ip_VCtrlStateShutdown()
 *********************************************************************************************************************/
/*! \brief            Control state shut down routine
 *  \details          -
 *  \param[in]        IpV4CtrlIdx  IP Controller Index
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV4ctrl()-1]
 *  \pre              -
 *  \context          TASK
 *  \reentrant        FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Ip_VCtrlStateShutdown(uint8 IpV4CtrlIdx);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  IpV4_InitMemory
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_InitMemory(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
# if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Set the initialization state to "not initialized */
  IpV4_State = IPV4_STATE_UNINIT;
# endif
} /* IpV4_InitMemory */

/**********************************************************************************************************************
 *  IpV4_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */

  /* #10 Initialize sub components (IP, ARP and ICMP). */
  IpV4_Ip_Init();
  IpV4_Arp_Init();

# if (TCPIP_SUPPORT_ICMPV4 == STD_ON)                                                                                   /* COV_TCPIP_ICMPV4_ALWAYS_ON */
  IpV4_Icmp_Init();
# endif

  IpV4_Ip_TimeMs = 0;

# if (TCPIP_SUPPORT_DEM == STD_ON)
  {
    /* Initialize array of last duplicated DHCP DID data */
    TcpIp_IpV4CtrlIterType ipV4CtrlIdx;
    const uint8 initPhysAddr[IPBASE_ETH_PHYS_ADDR_LEN_BYTE] = { 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U };
    for(ipV4CtrlIdx = 0; ipV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl(); ipV4CtrlIdx++)
    {
      /* #20 In case the ipV4Ctrl has DEM events configured:
             Reset the events' status at the DEM and reset their additional info in RAM. */
      if(TcpIp_IsDemEventUsedOfIpV4Ctrl(ipV4CtrlIdx) == TRUE)
      {
        /* Handle the DUPLICATE_DHCP_ADDR event (Get the index to determine whether the event is configured. */
        TcpIp_SizeOfDemEventType demEventIdx = TcpIp_GetDemEventIdxOfIpV4Ctrl(ipV4CtrlIdx);

        if(TcpIp_IsLastDuplicateDhcpAddrUsedOfDemEvent(demEventIdx) == TRUE)
        {
          TcpIp_SizeOfLastDuplicateDhcpAddrType lastDuplicateDhcpAddrIdx =
            TcpIp_GetLastDuplicateDhcpAddrIdxOfDemEvent(demEventIdx);
          Dem_EventIdType demEventSNV = TcpIp_GetE_DUPLICATE_DHCP_ADDROfDemEvent(demEventIdx);

          TCPIP_ASSERT(demEventSNV != TCPIP_INV_DEM_ID);
          Dem_ReportErrorStatus(demEventSNV, DEM_EVENT_STATUS_PREPASSED);

          TcpIp_VCopyPhysAddr(&TcpIp_GetAddrPhysAddrOfLastDuplicateDhcpAddr(lastDuplicateDhcpAddrIdx)->data[0],         /* SBSW_TCPIP_FUNC_CALL_COPY_PHYS_ADDR */
                              initPhysAddr);
          TcpIp_SetNetAddrOfLastDuplicateDhcpAddr(lastDuplicateDhcpAddrIdx, 0u);                                        /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_LOCAL */
        }
      }
    }
  }
# endif

# if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_TCPIP_DEV_ERROR_DETECT */
  IpV4_State = IPV4_STATE_INIT;
# endif

  /* #30 Initialize the DHCPv4 client submodule, if configured. */
# if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
  TcpIp_DhcpV4_Init();
# endif

} /* IpV4_Init */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_MainFunction
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
FUNC(void, IPV4_CODE) IpV4_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update time variable used for timeout handling. */
  IpV4_Ip_TimeMs += TCPIP_MAIN_FCT_PERIOD_MSEC;

  /* #20 Call ARP MainFunction. */
  IpV4_Arp_MainFunction();

  /* #30 Call IP MainFunction. */
  IpV4_Ip_MainFunction();

# if (TCPIP_SUPPORT_ICMPV4 == STD_ON)                                                                                   /* COV_TCPIP_ICMPV4_ALWAYS_ON */
  /* #40 Call ICMP MainFunction. */
  IpV4_Icmp_MainFunction();
# endif

# if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
  /* #50 Call DHCP MainFunction. */
  TcpIp_DhcpV4_MainFunction();
# endif
  /* TCPIP_SUPPORT_DHCPV4 == STD_ON */
} /* IpV4_MainFunction */

/**********************************************************************************************************************
 *  IpV4_Ip_Init
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
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_IpV4CtrlIterType        ipV4CtrlIdx;
  TcpIp_SocketDynIterType       socketIdx;   /* IpV4_Ip_TransferBlock / socket index */
  TcpIp_MulticastAddrV4IterType multicastAddrV4Idx;
  TcpIp_SizeOfBuf2TxReqMapType  buf2TxReqMapIdx;

  /* ----- Implementation ----------------------------------------------- */
  IpV4_Ip_Identification = 0;

  /* #10 Iterate all IP controller instances. */
  for (ipV4CtrlIdx = 0; ipV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl(); ipV4CtrlIdx++)
  {
    /* #20 Set IP controller instance to state OFFLINE. */
    TcpIp_SetStateOfIpV4CtrlDyn(ipV4CtrlIdx, IPV4_IP_OFFLINE);                                                          /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_LOCAL */
    TcpIp_SetPhysLinkActiveOfIpV4CtrlDyn(ipV4CtrlIdx, FALSE);                                                           /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_LOCAL */
    TcpIp_SetAddrAssignmentReadyChangedOfIpV4CtrlDyn(ipV4CtrlIdx, FALSE);                                               /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_LOCAL */
    TcpIp_SetActiveAddrAssignmentMethodOfIpV4CtrlDyn(ipV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_NONE);                        /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_LOCAL */
    TcpIp_SetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(ipV4CtrlIdx, 0);                                                 /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_LOCAL */
# if (TCPIP_SUPPORT_IP_ADDR_NVM_STORAGE == STD_ON)
    TcpIp_SetAddrAssignmentMethodPersistOfIpV4CtrlDyn(ipV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_NONE);                       /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_LOCAL */
# endif

    TcpIp_SetActiveNetAddrOfIpV4CtrlDyn(ipV4CtrlIdx, IPV4_ADDR_ANY);                                                    /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_LOCAL */
    TcpIp_SetActiveNetMaskOfIpV4CtrlDyn(ipV4CtrlIdx, 0);                                                                /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_LOCAL */
    TcpIp_SetActiveDefGwAddrOfIpV4CtrlDyn(ipV4CtrlIdx, IPV4_ADDR_ANY);                                                  /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_LOCAL */
    TcpIp_SetLastBcAddrOfIpV4CtrlDyn(ipV4CtrlIdx, IPV4_ADDR_ANY);                                                       /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_LOCAL */

    /* #30 Reset LinkLocal address assignment. */
    if (TcpIp_IsLlAddrStateUsedOfIpV4Ctrl(ipV4CtrlIdx) == TRUE)
    {
      TCPIP_ASSERT(IpV4_Ip_VCfgIsAddrAssignmentEnabled(ipV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL));

      IpV4_Ip_VLl_Reset(TcpIp_GetLlAddrStateIdxOfIpV4Ctrl(ipV4CtrlIdx));
    }
  } /* for each controller */

  /* #40 Reset Multicast address assignment of this controller to the defaults configured for this controller. */
  for(multicastAddrV4Idx = 0;
      multicastAddrV4Idx < TcpIp_GetSizeOfMulticastAddrV4();
      multicastAddrV4Idx++)
  {
    TcpIp_DefaultMulticastAddrV4IterType defaultMulticastAddrV4Idx =
      TcpIp_GetDefaultMulticastAddrV4IdxOfMulticastAddrV4(multicastAddrV4Idx);
    TcpIp_SetNetAddrOfMulticastAddrV4Requested(multicastAddrV4Idx,                                                      /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_LOCAL */
      TcpIp_GetNetAddrOfDefaultMulticastAddrV4(defaultMulticastAddrV4Idx));
  }

  /* #50 Reset socket specific information: Iterate all sockets and reset each of them. */
  for(socketIdx = 0; socketIdx < TcpIp_GetSizeOfIpV4SocketDyn(); socketIdx++)
  {
    IpV4_Ip_ResetSocket(socketIdx);
  }

  /* #60 Initialize packet reassembly buffers. */
  IpV4_Ip_VReassemblyInitBuffers();

  /* #70 Initialize the UL request index values. */
  for (buf2TxReqMapIdx = 0; buf2TxReqMapIdx < TcpIp_GetSizeOfBuf2TxReqMap(); buf2TxReqMapIdx++)
  {
    TcpIp_SetEthBufPtrOfBuf2TxReqMap (buf2TxReqMapIdx, NULL_PTR);                                                       /* SBSW_TCPIP_CSL01_IDX_LOCAL */
  }
} /* IpV4_Ip_Init */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

# if (TCPIP_SUPPORT_IP_ADDR_NVM_STORAGE == STD_ON)
/**********************************************************************************************************************
 *  IpV4_Ip_NvmGetAddrSet
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_NvmGetAddrSet(
  TcpIp_IpV4CtrlIterType          IpV4CtrlIdx,
  IPV4_P2V(IpV4_IpAddrSetPtrType) IpAddrSetPtrPtr,
  boolean                         WriteAccess
)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal    = E_NOT_OK;
  uint8          nvMStatus = NVM_REQ_PENDING;

  /* ----- Implementation ----------------------------------------------- */
  *IpAddrSetPtrPtr = NULL_PTR;                                                                                          /* SBSW_TCPIP_VALID_PTR_CALLER */

  TCPIP_ASSERT(TcpIp_IsNvmDataUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE);

  /* #10 Update the error status of the TcpIps NvM block */
  (void)NvM_GetErrorStatus((NvM_BlockIdType) TCPIP_NVM_BLOCK_ID, &nvMStatus);                                                             /* SBSW_TCPIP_CONSTANT_OR_LOCAL_INITIALIZED_VAR_BASED_POINTER_PARAM */

  if (WriteAccess == TRUE)
  {
    /* #20 For writing into NVM, check that NvM is not in pending state */
    if (nvMStatus != NVM_REQ_PENDING)
    {
      TcpIp_NvmDataIdxOfIpV4CtrlType nvmDataIdx = TcpIp_GetNvmDataIdxOfIpV4Ctrl(IpV4CtrlIdx);
      /* PRQA S 0310 2 */ /* MD_TCPIP_Rule11.3_0310_Uint8ToStruct */
      *IpAddrSetPtrPtr = (IPV4_P2V(IpV4_IpAddrSetType))TcpIp_GetAddrNvmData(nvmDataIdx);                                  /* SBSW_TCPIP_VALID_PTR_CALLER */
      retVal = E_OK;
    }
  }
  else
  {
    /* #30 For reading from NVM, check that NvM is in a successful state */
    if (   (nvMStatus == NVM_REQ_OK)
        || (nvMStatus == NVM_REQ_RESTORED_FROM_ROM))
    {
      TcpIp_NvmDataIdxOfIpV4CtrlType nvmDataIdx = TcpIp_GetNvmDataIdxOfIpV4Ctrl(IpV4CtrlIdx);
      /* PRQA S 0310 2 */ /* MD_TCPIP_Rule11.3_0310_Uint8ToStruct */
      *IpAddrSetPtrPtr = (IPV4_P2V(IpV4_IpAddrSetType))TcpIp_GetAddrNvmData(nvmDataIdx);                                  /* SBSW_TCPIP_VALID_PTR_CALLER */
      retVal = E_OK;
    }
  }
  return retVal;
} /* IpV4_Ip_NvmGetAddrSet */

/**********************************************************************************************************************
 *  IpV4_Ip_NvMBasedAddressHandling
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_NvMBasedAddressHandling(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  IPV4_P2V(IpV4_IpAddrSetType) ipAddrSetPtr = NULL_PTR;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Continue only in case the address set in NvM of this IpV4 controller can be accessed */
  if(IpV4_Ip_NvmGetAddrSet(IpV4CtrlIdx, &ipAddrSetPtr, TRUE) == E_OK)                                                   /* SBSW_TCPIP_FUNC_CALL_CSL01_IDX_CALLER_OUT_PTR_FROM_LOCAL_VAR */
  {
    /* #20 In case the address assignment method is suitable: Store the current address state into NvM. */
    /* PRQA S 0310 5 */ /* MD_TCPIP_Rule11.3_0310_Uint8ToStruct */
    if(IpV4_Ip_VGetActiveAddressOfAssignmentMethod( IpV4CtrlIdx,
                                                    TcpIp_GetAddrAssignmentMethodPersistOfIpV4CtrlDyn(IpV4CtrlIdx),
                                                    ipAddrSetPtr
                                                  ) == TRUE)                                                            /* SBSW_TCPIP_FUNC_CALL_ACTIVE_ADDR_OF_ASSIGNMENT_METHOD */
    {
      /* Set block Status to true */
      (void)NvM_SetRamBlockStatus((NvM_BlockIdType) TCPIP_NVM_BLOCK_ID, TRUE);
      TcpIp_SetAddrAssignmentMethodPersistOfIpV4CtrlDyn(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_NONE);                     /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
    }
  }
} /* IpV4_Ip_NvMBasedAddressHandling */
# endif

/**********************************************************************************************************************
 *  IpV4_Ip_StandardAddressHandling
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
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_StandardAddressHandling(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Check if there is a 'best available' address assignment method for the given IP controller. */
  IpV4_IpAddrSetType         bestAvailableAddr = {IPV4_ADDR_ANY, 0, IPV4_ADDR_ANY};
  TcpIp_IpAddrAssignmentType bestAvailableAddrAssignmentMethod =
    IpV4_Ip_VGetBestAvailableAddrAssignment(IpV4CtrlIdx, &bestAvailableAddr);                                           /* SBSW_TCPIP_FUNC_CALL_CSL01_IDX_CALLER_OUT_PTR_FROM_LOCAL_VAR */

  /* ----- Implementation ----------------------------------------------- */
  /* #20 In case no assignment method is active for the given IP controller
         check whether a 'best available' assignment method was determined, before and apply it. */
  if(TcpIp_GetActiveAddrAssignmentMethodOfIpV4CtrlDyn(IpV4CtrlIdx) == TCPIP_IPADDR_ASSIGNMENT_NONE)
  {
    /* #30 Set the IP controller to state ONLINE ACTIVE in case a 'best available' assignment method was found. */
    if(bestAvailableAddrAssignmentMethod != TCPIP_IPADDR_ASSIGNMENT_NONE)
    {
      /* IP address ready. */
      TcpIp_SetActiveDefGwAddrOfIpV4CtrlDyn(IpV4CtrlIdx, bestAvailableAddr.DefGwAddr);                                  /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
      TcpIp_SetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx, bestAvailableAddr.NetAddr);                                      /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
      TcpIp_SetActiveNetMaskOfIpV4CtrlDyn(IpV4CtrlIdx, bestAvailableAddr.NetMask);                                      /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
      TcpIp_SetActiveAddrAssignmentMethodOfIpV4CtrlDyn(IpV4CtrlIdx, bestAvailableAddrAssignmentMethod);                 /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */

      IpV4_Ip_VSetCtrlStateOnlineActive(IpV4CtrlIdx);
    }
    /* else: Still no IP address of any configured assignment method available. */
  }
  else
  /* #40 Otherwise an assignment method is active, already, for the given controller. */
  {
    /* #50 In case there is a 'best available' assignment method check the current IP address to be available, still.
           Otherwise the current IP address was lost and the IP controller has to be set to state ONLINE PASSIVE. */
    if(bestAvailableAddrAssignmentMethod != TCPIP_IPADDR_ASSIGNMENT_NONE)
    {
      /* #60 Inform the upper layer about a change of IP address if required */
      /* IP address still available. */
      if(TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx) != bestAvailableAddr.NetAddr)
      {
        /* IP address value has changed. Inform upper-layer. */
        IpV4_VLocalIpAddrAssignmentChange(TcpIp_GetLocalAddrV4UnicastIdxOfIpV4Ctrl(IpV4CtrlIdx),
                                          TCPIP_IPADDR_STATE_UNASSIGNED);

        TcpIp_SetActiveDefGwAddrOfIpV4CtrlDyn(IpV4CtrlIdx, bestAvailableAddr.DefGwAddr);                                /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
        TcpIp_SetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx, bestAvailableAddr.NetAddr);                                    /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
        TcpIp_SetActiveNetMaskOfIpV4CtrlDyn(IpV4CtrlIdx, bestAvailableAddr.NetMask);                                    /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
        TcpIp_SetActiveAddrAssignmentMethodOfIpV4CtrlDyn(IpV4CtrlIdx, bestAvailableAddrAssignmentMethod);               /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */

        IpV4_VLocalIpAddrAssignmentChange(TcpIp_GetLocalAddrV4UnicastIdxOfIpV4Ctrl(IpV4CtrlIdx),
                                          TCPIP_IPADDR_STATE_ASSIGNED);
      }
      else if (TcpIp_GetActiveAddrAssignmentMethodOfIpV4CtrlDyn(IpV4CtrlIdx) != bestAvailableAddrAssignmentMethod)
      {
        /* IP address assignment method has changed but IP address is the same. No need to inform upper-layer. */
        TcpIp_SetActiveAddrAssignmentMethodOfIpV4CtrlDyn(IpV4CtrlIdx, bestAvailableAddrAssignmentMethod);               /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
      }
      else
      {
        /* IP address and assignment method did not change. */
      }
    }
    else
    {
      /* IP address lost. */
      IpV4_Ip_VSetCtrlStateOnlinePassive(IpV4CtrlIdx);
    }
  }
} /* IpV4_Ip_StandardAddressHandling */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_MainFunction
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
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_IpV4CtrlIterType ipV4CtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all IP controller instances. */
  for (ipV4CtrlIdx = 0; ipV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl(); ipV4CtrlIdx++)
  {
    /* #20 Call LINKLOCAL address assignment MainFunction if configured. */
    if (TcpIp_IsLlAddrStateUsedOfIpV4Ctrl(ipV4CtrlIdx) == TRUE)                                                         /* SBSW_TCPIP_CM_R5 */
    {
      TCPIP_ASSERT(IpV4_Ip_VCfgIsAddrAssignmentEnabled(ipV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL));

      IpV4_Ip_VLl_Main(ipV4CtrlIdx);
    }
    /* #30 Perform IP instance state and address assignment handling. */
    if(TcpIp_GetStateOfIpV4CtrlDyn(ipV4CtrlIdx) == IPV4_IP_OFFLINE)
    {
      if(TcpIp_IsPhysLinkActiveOfIpV4CtrlDyn(ipV4CtrlIdx) == TRUE)
      {
        /* IP instance is OFFLINE and physical link has become active. */
        IpV4_Ip_VSetCtrlStateOnlinePassive(ipV4CtrlIdx);
      }
    }
    else
    {
      if(TcpIp_IsPhysLinkActiveOfIpV4CtrlDyn(ipV4CtrlIdx) == TRUE)
      {
# if (TCPIP_SUPPORT_IP_ADDR_NVM_STORAGE == STD_ON)
        /* #40 Store IP address into NvM if required. */
        if(TcpIp_GetAddrAssignmentMethodPersistOfIpV4CtrlDyn(ipV4CtrlIdx) != TCPIP_IPADDR_ASSIGNMENT_NONE)
        {
          IpV4_Ip_NvMBasedAddressHandling(ipV4CtrlIdx);
        }
        else
# endif
        /* #50 Conduct the standard address handling. */
        {
          IpV4_Ip_StandardAddressHandling(ipV4CtrlIdx);
        }
      }
      else
      {
        /* Physical link lost. */
        IpV4_Ip_VSetCtrlStateOffline(ipV4CtrlIdx);
      }
    }
  } /* for each controller */
} /* IpV4_Ip_MainFunction */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_RxIsDuplicateDhcpAddr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(boolean, IPV4_CODE) IpV4_Ip_RxIsDuplicateDhcpAddr(
  TcpIp_IpV4CtrlIterType    IpV4CtrlIdx,
  IpBase_AddrInType         SrcAddr,
  IPV4_P2C(uint8)           PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case the IP controller is online and it is a DHCP IP address, check for a duplicate DHCP address. */
  if (   (TcpIp_GetStateOfIpV4CtrlDyn(IpV4CtrlIdx) == IPV4_IP_ONLINE_ACTIVE)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx) == SrcAddr))
  {
    /* #20 In case this message uses the node's local IP address as source address:
           Issue the related DEM event in case it's a DHCP address */
# if (TCPIP_SUPPORT_DEM == STD_ON)
    if(TcpIp_IsDemEventUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
    {
      TcpIp_DemEventIdxOfIpV4CtrlType demEventIdx = TcpIp_GetDemEventIdxOfIpV4Ctrl(IpV4CtrlIdx);
      if (TcpIp_IsLastDuplicateDhcpAddrUsedOfDemEvent(demEventIdx) == TRUE)
      {
        Dem_EventIdType demEventSNV = TcpIp_GetE_DUPLICATE_DHCP_ADDROfDemEvent(demEventIdx);
        TcpIp_SizeOfLastDuplicateDhcpAddrType lastDuplicateDhcpAddrIdx =
          TcpIp_GetLastDuplicateDhcpAddrIdxOfDemEvent(demEventIdx);

        TcpIp_VCopyPhysAddr(&TcpIp_GetAddrPhysAddrOfLastDuplicateDhcpAddr(lastDuplicateDhcpAddrIdx)->data[0],           /* SBSW_TCPIP_FUNC_CALL_COPY_PHYS_ADDR */
                            PhysAddrPtr);
        TcpIp_SetNetAddrOfLastDuplicateDhcpAddr(lastDuplicateDhcpAddrIdx, SrcAddr);                                     /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
        Dem_ReportErrorStatus(demEventSNV, DEM_EVENT_STATUS_PREFAILED);
      }
    }
# else
    IPV4_UNUSED_PARAMETER(PhysAddrPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
    /* discard message immediately */
    retVal = TRUE;
  }
  return retVal;
} /* IpV4_Ip_RxIsDuplicateDhcpAddr */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_GetLocalAddrIdxMulticast
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(TcpIp_SizeOfLocalAddrV4Type, IPV4_CODE) IpV4_Ip_GetLocalAddrIdxMulticast(
  TcpIp_IpV4CtrlIterType    IpV4CtrlIdx,
  IpBase_AddrInType         DestAddr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfLocalAddrV4Type localAddrV4Idx = TCPIP_LOCAL_ADDR_V4_IDX_ANY;
  boolean multicastAddrV4IdxFound = FALSE;
  TcpIp_MulticastAddrV4IterType multicastAddrV4Idx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all multicast addresses configured for the given IP controller and
         compare each of them with the destination address of the given IP header. */
  for (multicastAddrV4Idx = TcpIp_GetMulticastAddrV4StartIdxOfIpV4Ctrl(IpV4CtrlIdx);
       multicastAddrV4Idx < TcpIp_GetMulticastAddrV4EndIdxOfIpV4Ctrl(IpV4CtrlIdx);
       multicastAddrV4Idx++)
  {
    if(DestAddr == TcpIp_GetNetAddrOfMulticastAddrV4Requested(multicastAddrV4Idx))
    {
      multicastAddrV4IdxFound = TRUE;
      break;
    }
  }

  /* #20 In case a configured multicast address matches the destination address of the given IP header
         or in case all multicast packets shall be received, determine and return the local address index. */
  if(multicastAddrV4IdxFound == TRUE)
  {
    /* accept packet and map to specific multicast address id */
    localAddrV4Idx = TcpIp_GetLocalAddrV4IdxOfMulticastAddrV4(multicastAddrV4Idx);
  }
  else if(TcpIp_IsReceiveAllMulticastsOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    /* accept packet and map to AutoSelectBroadcast address id */
    localAddrV4Idx = TcpIp_GetLocalAddrV4BroadcastIdxOfIpV4Ctrl(IpV4CtrlIdx);
    TcpIp_SetLastBcAddrOfIpV4CtrlDyn(IpV4CtrlIdx, DestAddr);                                                            /* SBSW_TCPIP_CSL01_IDX_CALLER */
  }
  else
  {
    /* Leave localAddrV4Idx at TCPIP_LOCAL_ADDR_V4_IDX_ANY */
    /* satisfy MISRA-C:2004 Rule 14.10: requires else for if-else-if statements */
  }

  return localAddrV4Idx;
} /* IpV4_Ip_GetLocalAddrIdxMulticast */

/**********************************************************************************************************************
 *  IpV4_Ip_ReassembleAndForwardToUpperLayer
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
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_ReassembleAndForwardToUpperLayer(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  TcpIp_IpV4CtrlIterType                   IpV4CtrlIdx,
  TcpIp_LocalAddrV4IterType                LocalAddrV4Idx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Prepare ignoring IP header options if available */
  uint16 flagsOffset      = TCPIP_GET_UINT16(DataPtr, TCPIP_IPV4_HDR_OFS_FLAGS_OFFSET);
  uint16 ipTotalLenByte   = TCPIP_IPV4_HDR_FIELD_GET_TOTAL_LEN(DataPtr);
  uint8  ipHdrLenByte     = TCPIP_IPV4_HDR_FIELD_GET_IHL_BYTE(DataPtr);
  uint16 ipPayloadLenByte = ipTotalLenByte - ipHdrLenByte;

  /* ----- Implementation ----------------------------------------------- */
  /* #20 In case IP datagram does contain payload:
         Defragment the packet if necessary and forward it to the next layer or protocol */
  if (ipPayloadLenByte > 0u)                                                                                             /* SBSW_TCPIP_CM_R1 */
  {
    boolean checksumOk;

    /* #30 Check header checksum in case the HW has not done so, already */
    if (TcpIp_IsHwChecksumIpOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
    {
      /* Set checksumOk TRUE because IP checksum was checked by HW, already */
      checksumOk = TRUE;
    }
    else
    {
      /* Checksum is calculated starting with Ver_Ihl byte in the IPv4 header structure (i.e. 1st byte in data array from EthIf) */
      checksumOk = (boolean)(IpBase_TcpIpChecksumAdd(DataPtr, ipHdrLenByte, 0, TRUE) == 0u);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */                           /* SBSW_TCPIP_FUNC_CALL_CHECKSUM_ADD_RX_IND_FWD_UL */
    }

    /* #40 In case the checksum was ok, submit the packet to defragmentation */
    if (checksumOk == TRUE)
    {
      uint16          fragmentOffset = (uint16)(flagsOffset & IPV4_IP_FRAGMENT_OFFSET_MASK);
      IPV4_P2V(uint8) ipPayloadPtr   = &DataPtr[ipHdrLenByte];

      /* #50 Treat this packet as fragment in case fragmentOffset is set or more fragments are expected */
      if((0u != fragmentOffset) || (0u != (flagsOffset & IPV4_IP_FLAGS_MORE_FRAGMENTS)))
      {
        /* #60 Only try to reassemble packets ("Rx-path") in case at least one reassembly-buffer is configured */
        if (   (TcpIp_IsFragmentationConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
            && (TcpIp_IsReassemblyBufferDescUsedOfFragmentationConfig(TcpIp_GetFragmentationConfigIdxOfIpV4Ctrl(IpV4CtrlIdx)) == TRUE))
        {
          if(FALSE == IpV4_Ip_VReassemblyRxIndication(IpV4CtrlIdx, DataPtr, &ipPayloadPtr, &ipPayloadLenByte))          /* SBSW_TCPIP_FUNC_CALL_REASSEMBLY_RX_IND */
          {
            ipPayloadPtr = NULL_PTR;
          }
        }
        else
        {
          ipPayloadPtr = NULL_PTR;
        }
      }
      /* if( packet was submitted to defragmentation ) else: Continue without defragmentation */

      /* #70 Forward packet to upper layer in case fragmentation is not required or
             fragmentation is enabled and reassembly succeeded */
      if(ipPayloadPtr != NULL_PTR)
      {
        IpV4_Ip_VForwardPacketToUpperLayer(IpV4CtrlIdx, LocalAddrV4Idx, DataPtr, ipPayloadPtr, ipPayloadLenByte);       /* SBSW_TCPIP_FUNC_CALL_FORWARD_TO_UL_RX_IND */
      }
      /* if(ipPayloadPtr != NULL_PTR) else: Drop packet */
    }
    /* if(checksumOk == TRUE) else: Drop packet */
  }
  /* if(0u > ipPayloadLenByte) else: Drop packet */
} /* IpV4_Ip_ReassembleAndForwardToUpperLayer */ /* PRQA S 6050, 6080 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV4_Ip_RxIndication
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
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Ip_RxIndication(
  uint8                                    EthIfCtrlIdx,
  Eth_FrameType                            FrameType,
  boolean                                  IsBroadcast,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) PhysAddrPtr, /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                   LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = TCPIP_E_NO_ERROR;

  IPV4_UNUSED_PARAMETER(IsBroadcast); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks ------------------------------------- */
# if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check component initialization state and input parameters. */
  if (IpV4_State != IPV4_STATE_INIT)
  {
    errorId = IPV4_E_NOT_INITIALIZED;
  }
  else
  /* Check parameter 'FrameType' */
  if (FrameType != IPV4_IP_FRAME_TYPE)
  {
    errorId = IPV4_E_INV_PARAM;
  }
  /* Check parameter 'EthIfCtrlIdx' */
  else if (EthIfCtrlIdx >= TcpIp_GetSizeOfEthIfCtrl())
  {
    errorId = IPV4_E_INV_PARAM;
  }
  /* Check parameter 'PhysAddrPtr' */
  else if (PhysAddrPtr == NULL_PTR)
  {
    errorId = IPV4_E_INV_POINTER;
  }
  /* Check parameter 'DataPtr' */
  else if (DataPtr == NULL_PTR)
  {
    errorId = IPV4_E_INV_POINTER;
  }
  else
# else
  TCPIP_UNUSED_PARAMETER(FrameType);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 IP is active on this EthIfCtrl: Map EthIfCtrlIdx to IpV4CtrlIdx */
    TcpIp_IpV4CtrlIterType ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfEthIfCtrl(EthIfCtrlIdx);

    /* #30 In case IP is configured on this EthIf controller */
    if (   (ipV4CtrlIdx != TCPIP_NO_IPV4CTRLIDXOFETHIFCTRL)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        /* #40 AND the IP controller is NOT offline  */
        && (TcpIp_GetStateOfIpV4CtrlDyn(ipV4CtrlIdx) != IPV4_IP_OFFLINE)
        /* #50 AND the given packet length is valid. */
        && (IPV4_IP_DEF_HEADER_LENGTH_BYTE <= LenByte))
    {
      /* #60 Extract the header and total packet length. */
      IpBase_AddrInType         srcAddr        = TCPIP_GET_UINT32_RAW(DataPtr, TCPIP_IPV4_HDR_OFS_SRC_ADDR);
      uint16                    ipTotalLenByte = TCPIP_IPV4_HDR_FIELD_GET_TOTAL_LEN(DataPtr);
      uint8                     ipHdrLenByte   = TCPIP_IPV4_HDR_FIELD_GET_IHL_BYTE(DataPtr);

      /* According to RFC 791, section 3.3 ("The internet module must check to see that the source address is one of the
          legal address for this host."), and RFC 1122, section 3.2.1.3, case c
          ("It MUST NOT be used as a source address."), the broadcast address may not be used as a source address.
          Therefore an incoming message with broadcast addr as the source addr must be discarded. */
      /* #70 In case the length of the given IP header is larger or equal then the minimum length */
      if (    (ipHdrLenByte >= IPV4_IP_DEF_HEADER_LENGTH_BYTE) /* PRQA S 3415 28 */ /* MD_IPV4_Rule12.4_3415 */
          /* #80 AND the IP version number is correct */
          && (TCPIP_IPV4_HDR_FIELD_GET_VERSION(DataPtr) == IPV4_IP_HEADER_VERSION_V4)
          /* #90 AND the length value in the IP header is consistent to the total length of the IP packet */
          && (LenByte >= ipTotalLenByte)
          /* #100 AND the length value of the IP header itself is consistent to the total length of the IP packet */
          && (ipHdrLenByte <= ipTotalLenByte)
          /* #110 AND EITHER checksum offloading in hardware is supported
                      OR the header checksum calculated in software is correct
                  (in case the hardware has detected a wrong checksum, this function is not called at all) */
          && (   (TcpIp_IsHwChecksumIpOfIpV4Ctrl(ipV4CtrlIdx) == TRUE)
              || (IpBase_TcpIpChecksumAdd(DataPtr, ipHdrLenByte, 0, TRUE) == 0u))                                        /* SBSW_TCPIP_FUNC_CALL_CHECKSUM_ADD_RX_IND */
          /* #120 AND the packets source address is not broadcast */
          && (TCPIP_INADDR_BROADCAST != srcAddr)
          /* #130 AND this message does NOT use the local broadcast address as source address
                 (Note: This check can only be conducted when the IP controller is in state ONLINE_ACTIVE) */
          && (   (TcpIp_GetStateOfIpV4CtrlDyn(ipV4CtrlIdx) != IPV4_IP_ONLINE_ACTIVE)
              || (!IPV4_ADDR_IS_DIRECTED_BROADCAST(ipV4CtrlIdx, srcAddr)))
          /* #140 AND the source address of this message is NOT multicast address */
          && (! IPV4_ADDR_IS_MULTICAST(srcAddr))
          /* #150 AND no duplicate DHCP assigned IP address has been detected */
          && (IpV4_Ip_RxIsDuplicateDhcpAddr(ipV4CtrlIdx, srcAddr, PhysAddrPtr) == FALSE)                                 /* SBSW_TCPIP_FUNC_CALL_IS_DUPL_DHCP_ADDR */
          /* UDP messages with source address 0.0.0.0 are accepted since a DHCPv4 server
           * and link-local address configuration must be able to receive UDP packets sent from 0.0.0.0. */
          /* #160 AND the IP address is not zero or the protocol is not TCP */
          && ((srcAddr != 0u) || (TCPIP_GET_UINT8(DataPtr, TCPIP_IPV4_HDR_OFS_PROT) != IPV4_IP_PROTOCOL_TCP))
          /* #170 AND this message does NOT use a localnet address as source address */
          && (!IPV4_ADDR_IN_SUBNET(srcAddr, IPV4_LOCALNET_PREFIX, IPV4_LOCALNET_PREFIX_MASK)))
      {
        /* #180 In case this is Ecu is a standard node:
                Check if IP packet is intended for this node (unicast, multicast, broadcast)
                In case of unicast: Check if IP address matches node address (dependent on CtrlIdx)
                In case of router: Drop the package because this is not a use case (not implemented). */
        TcpIp_SizeOfLocalAddrV4Type localAddrV4Idx = TCPIP_LOCAL_ADDR_V4_IDX_ANY;
        IpBase_AddrInType           destAddr       = TCPIP_GET_UINT32_RAW(DataPtr, TCPIP_IPV4_HDR_OFS_DEST_ADDR);
        if(TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(ipV4CtrlIdx) == destAddr) /* local IP address */
        {
          localAddrV4Idx = TcpIp_GetLocalAddrV4UnicastIdxOfIpV4Ctrl(ipV4CtrlIdx);
        }
        /* local or directed broadcast */
        else if (IPV4_ADDR_IS_BROADCAST(ipV4CtrlIdx, destAddr))
        {
          localAddrV4Idx = TcpIp_GetLocalAddrV4BroadcastIdxOfIpV4Ctrl(ipV4CtrlIdx);
          TcpIp_SetLastBcAddrOfIpV4CtrlDyn(ipV4CtrlIdx, destAddr);                                                      /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
        }
        else if (IPV4_ADDR_IS_MULTICAST(destAddr))
        {
          localAddrV4Idx = IpV4_Ip_GetLocalAddrIdxMulticast(ipV4CtrlIdx, destAddr);
        }
        else
        {
          /* Leave localAddrV4Idx at TCPIP_LOCAL_ADDR_V4_IDX_ANY */
          /* Satisfy MISRA-C:2004 Rule 14.10: requires else for if-else-if statements */
        }

        /* # In case a valid local address index configured for this Ecu has been found,
              reassemble the packet and forward it to the configured upper layer. */
        if(localAddrV4Idx != TCPIP_LOCAL_ADDR_V4_IDX_ANY)
        {
          IpV4_Ip_ReassembleAndForwardToUpperLayer(DataPtr, ipV4CtrlIdx, localAddrV4Idx);                               /* SBSW_TCPIP_FUNC_CALL_AFTER_ALL_CHECKS_RX_IND_LOC_ADDR_IDX */
        }
        /* else: incoming message not for this node */
        else
        {
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
          /* Increment the counter of dropped IpV4 packets. */
          TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_DROP_IPV4);
#endif
        }
      }
      /* else: IP header length error OR IP version number error OR header checksum error --> discard message */
    }
    /* if((ctrlIdx is valid) && (ctrl is not OFFLINE) && (LenByte is valid)) else */
  }

# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if(errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(IPV4_MODULE_ID, IPV4_VINSTANCE_ID, IPV4_IP_API_ID_GET_LAST_DUPLICATE_DHCP_ADDR_DID, errorId);
  }
# else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif
} /* IpV4_Ip_RxIndication */ /* PRQA S 6030, 6050, 6060, 6080 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess, MD_MSR_STPAR, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV4_Ip_ProvideTxBuffer
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
 */
FUNC(BufReq_ReturnType, IPV4_CODE) IpV4_Ip_ProvideTxBuffer(
  IPV4_P2V(TcpIp_LocalAddrV4IterType)       LocalAddrV4IdxPtr,
  TcpIp_SocketDynIterType                   IpV4SocketIdx,
  IPV4_P2C(IpBase_SockAddrInType)           DestAddrPtr,
  IPV4_P2V(uint8)                           *IpBufferPtr,
  IPV4_P2V(uint16)                          IpBufferLenPtr,
  IPV4_P2V(TcpIp_IpTxRequestDescriptorType) IpTxReqDescrPtr,
  boolean                                   ForceProvideBuffer)
{
  /* ----- Local Variables ---------------------------------------------- */
#if (TCPIP_SUPPORT_IPSEC == STD_ON)
  Std_ReturnType            retIpSec;
#endif
  TcpIp_IpV4CtrlIterType    ipV4CtrlIdx;
  TcpIp_ReturnType          arpRetVal;
  BufReq_ReturnType         retVal      = BUFREQ_E_NOT_OK;
  IpBase_AddrInType         destAddr    = DestAddrPtr->sin_addr;
  uint16                    ipTotHdrLenBytes = IPV4_IP_DEF_HEADER_LENGTH_BYTE;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpV4SocketIdx      < TcpIp_GetSizeOfIpV4SocketDyn());
  TCPIP_ASSERT(LocalAddrV4IdxPtr  != NULL_PTR);
  TCPIP_ASSERT(*LocalAddrV4IdxPtr <  TcpIp_GetSizeOfLocalAddrV4() || *LocalAddrV4IdxPtr == TCPIP_LOCAL_ADDR_V4_IDX_ANY);
  TCPIP_ASSERT(DestAddrPtr        != NULL_PTR);
  TCPIP_ASSERT(IpBufferPtr        != NULL_PTR);
  TCPIP_ASSERT(IpBufferLenPtr     != NULL_PTR);

  /* #10 Determine corresponding IP controller based on the IpAddrIdx. */
  ipV4CtrlIdx = IpV4_Ip_VGetLocalAddrIdxAndCtrlIdx(LocalAddrV4IdxPtr, destAddr);                                        /* SBSW_TCPIP_VALID_PTR_CALLER */


#if (TCPIP_SUPPORT_IPSEC == STD_ON)
  /* Remote socket information is available in the DestAddrPtr
   * Local socket information is extracted from the socket
   */
  /* #20 If valid IpSecConfigSet exists for controller, prepare for IpSec authentication of the outgoing packet */
  if (   (ipV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl())                                                                     /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_IsIpSecConfigSetUsedOfIpV4Ctrl(ipV4CtrlIdx) == TRUE))
  {
    /* Prepare the packet for authentication */
    retIpSec = TcpIp_IpSec_PreparePacketforAuthentication(ipV4CtrlIdx, IpV4SocketIdx, IpTxReqDescrPtr, *DestAddrPtr);   /* SBSW_TCPIP_VALID_PTR_CALLER */
  }
  /* #30 Otherwise, proceed with normal processing of the packet */
  else
  {
    retIpSec = E_OK;
    /* #40 Set tx buffer descriptor values to 0 incase no valid IpSecConfigSet exists */
    IpTxReqDescrPtr->SaEntryIdx = TcpIp_GetSizeOfSaEntry();                                                             /* SBSW_TCPIP_VALID_PTR_CALLER */
    IpTxReqDescrPtr->ExtHdrLenBytes = 0;                                                                                /* SBSW_TCPIP_VALID_PTR_CALLER */
  }

  /*#50 update the total header length with the length of the IpSec header */
  ipTotHdrLenBytes += IpTxReqDescrPtr->ExtHdrLenBytes;
#endif

  /* #60 Update the TX request descriptor in case a matching IP controller instance was found
         AND the requested IP payload size did fit into IP packet (including IpSec header if enabled) */
  if (   (ipV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl())  /* PRQA S 3415 5 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */                   /* SBSW_TCPIP_CM_R2 */
      && ((*IpBufferLenPtr) <= (TcpIp_GetMaxTxMsgSizeOfIpV4Ctrl(ipV4CtrlIdx) - ipTotHdrLenBytes))
#if (TCPIP_SUPPORT_IPSEC == STD_ON)
  /* #70 AND IpSec lookup did not result in discard.() */
      && (retIpSec == E_OK)
#endif
      )
  {
    IpTxReqDescrPtr->SrcAddrIdx    = (TcpIp_SizeOfLocalAddrV4Type)(*LocalAddrV4IdxPtr);                                 /* SBSW_TCPIP_VALID_PTR_CALLER */
    IpTxReqDescrPtr->CtrlIdx       = TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(ipV4CtrlIdx);                                      /* SBSW_TCPIP_VALID_PTR_CALLER */
    IpTxReqDescrPtr->SockIdx       = (TcpIp_SizeOfSocketDynType)IpV4SocketIdx;                                          /* SBSW_TCPIP_VALID_PTR_CALLER */
    IpTxReqDescrPtr->DestAddrV4    = destAddr;                                                                          /* SBSW_TCPIP_VALID_PTR_CALLER */
    IpTxReqDescrPtr->AddressFamily = TCPIP_AF_INET;                                                                     /* SBSW_TCPIP_VALID_PTR_CALLER */

    /* #80 Determine IP address that will be used as source address in transmitted packet. */
    /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    if (   ((*LocalAddrV4IdxPtr) == TcpIp_GetLocalAddrV4BroadcastIdxOfIpV4Ctrl(ipV4CtrlIdx))
        || (TcpIp_IsMulticastAddrV4UsedOfLocalAddrV4(*LocalAddrV4IdxPtr) == TRUE)
      )
    {
      /* automatically select source address for transmission */
      /* Only one address supported for IPv4 */
      /* SWS_TCPIP_00179 */
      *LocalAddrV4IdxPtr = TcpIp_GetLocalAddrV4UnicastIdxOfIpV4Ctrl(ipV4CtrlIdx);                                       /* SBSW_TCPIP_VALID_PTR_CALLER */
    }

    /* #90 Check if controller is online or passive and DHCP or LINKLOCAL address assignment is configured. */
    if (   (TcpIp_GetStateOfIpV4CtrlDyn(ipV4CtrlIdx) == IPV4_IP_OFFLINE)  /* PRQA S 3415 4 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        || (   (TcpIp_GetStateOfIpV4CtrlDyn(ipV4CtrlIdx) == IPV4_IP_ONLINE_PASSIVE)
            && (TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(ipV4CtrlIdx) == FALSE)
            && (TcpIp_IsLlAddrStateUsedOfIpV4Ctrl(ipV4CtrlIdx) == FALSE)))
    {
      /* ERROR: IP controller is offline or passive and neither DHCP not LINKLOCAL address assignment is active. */
    }
    /* Provide buffer only if destination address is not the address of this node. */
    else if (TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(ipV4CtrlIdx) == destAddr)
    {
      /* ERROR: It is not allowed to send packets to ourself. */
    }
    else
    {
      /* #100 Determine physical address of next hop:
             In case the physical destination address for the socket has been set manually,
             use this address and skip ARP. */
      if(IPV4_CHK_FLAG_U8(TcpIp_GetTransferBlockOfIpV4SocketDyn(IpV4SocketIdx).Flags,
                          IPV4_IP_TRANSFER_BLOCK_FLAG_PHYS_DEST_ADDR))
      {
        arpRetVal = TCPIP_OK;
      }
      else
      /* #110 Otherwise determine the physical destination address using ARP */
      {
        IpBase_EthPhysAddrType destMacAddr;
        arpRetVal = IpV4_Ip_VGetNextHopPhysAddr(ipV4CtrlIdx, destAddr, IpV4SocketIdx, &destMacAddr[0]);                 /* SBSW_TCPIP_FUNC_CALL_GET_NEXT_HOP */
      }

      /* #120 Provide TX buffer(s) in case ARP was successful or incomplete AR shall be ignored. */
      if ((arpRetVal == TCPIP_OK) || ((arpRetVal == TCPIP_E_PHYS_ADDR_MISS) && (ForceProvideBuffer == TRUE)))
      {
        /* Request for the Ip buffer should include the IpSec header length */
        retVal = IpV4_Ip_VFragmentProvideTxBuffers(ipV4CtrlIdx, IpV4SocketIdx, *IpBufferLenPtr
# if (TCPIP_SUPPORT_IPSEC == STD_ON)
          /* Request Tx buffer should also contain the IpSec extension header length */
          + IpTxReqDescrPtr->ExtHdrLenBytes
# endif
          , IpTxReqDescrPtr);                                                                                           /* SBSW_TCPIP_FUNC_CALL_FRAG_PROV_TX_BUFS */

        if(retVal == BUFREQ_OK)
        {
          *IpBufferPtr    = &IpTxReqDescrPtr->EthPayloadPtr[ipTotHdrLenBytes];                                          /* SBSW_TCPIP_VALID_PTR_CALLER */
          *IpBufferLenPtr = (uint16)(IpTxReqDescrPtr->EthPayloadLen - ipTotHdrLenBytes);                                /* SBSW_TCPIP_VALID_PTR_CALLER */
        }
      }
      else
      {
        /* Evaluate the ARP's return code in case it is not TCPIP_OK */
        if(arpRetVal == TCPIP_E_PHYS_ADDR_MISS)
        {
          /* Physical address could not be received from ARP module. Either address is not yet stored in
             ARP table (then an ARP request was triggered), or ARP is not able to allocate a Tx buffer.
             -> Try again later */
          retVal = BUFREQ_E_BUSY;
        }
        else
        {
          /* ARP's return code is not TCPIP_OK and not TCPIP_E_PHYS_ADDR_MISS, i.e. it is TCPIP_E_NOT_OK or invalid:
             Address resolution could not be started or the resolution is not desired
             (e.g. in case "ARP table full" mode is active) */
          retVal = BUFREQ_E_NOT_OK;
        }
      }
    }
  }

  return retVal;
} /* IpV4_Ip_ProvideTxBuffer */ /* PRQA S 6050, 6060, 6080 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STPAR, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV4_Ip_VCtrlIsOnline
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(boolean, IPV4_CODE) IpV4_Ip_VCtrlIsOnline(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return TRUE if and only if IP controller is ONLINE and an IP address has been assigned. */
  /* PRQA S 4304 3 */ /* MD_MSR_AutosarBoolean */
  return (boolean)(   (TcpIp_IsPhysLinkActiveOfIpV4CtrlDyn(IpV4CtrlIdx) == TRUE)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
                   && (TcpIp_GetStateOfIpV4CtrlDyn(IpV4CtrlIdx) == IPV4_IP_ONLINE_ACTIVE)
                   && (TcpIp_GetActiveAddrAssignmentMethodOfIpV4CtrlDyn(IpV4CtrlIdx) != TCPIP_IPADDR_ASSIGNMENT_NONE));
} /* IpV4_Ip_VCtrlIsOnline */

/**********************************************************************************************************************
 *  IpV4_Ip_VGetNextHopPhysAddr
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
IPV4_LOCAL_INLINE FUNC(TcpIp_ReturnType, IPV4_CODE) IpV4_Ip_VGetNextHopPhysAddr(
  TcpIp_IpV4CtrlIterType  IpV4CtrlIdx,
  IpBase_AddrInType       DestAddr,
  TcpIp_SocketDynIterType SocketIdx,
  IPV4_P2V(uint8)         NextHopPhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  IpBase_AddrInType       dstAddr = DestAddr;
  TcpIp_ReturnType        retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return destAddr as next hop address in case destAddr either is an address inside the local subnet. */
  if((TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx) & TcpIp_GetActiveNetMaskOfIpV4CtrlDyn(IpV4CtrlIdx)) ==
     (TcpIp_GetActiveNetMaskOfIpV4CtrlDyn(IpV4CtrlIdx) & dstAddr))
  {
    /* address is inside the local subnet */
    retVal = TCPIP_OK;
  }
  /* #20 Return destAddr as next hop address if destination address is a global brodcast address. */
  else if (dstAddr == TCPIP_INADDR_BROADCAST)
  {
    retVal = TCPIP_OK;
  }
  /* #30 Return destAddr as next hop address if destination address is a multicast address. */
  else if (IPV4_ADDR_IS_MULTICAST(dstAddr))
  {
    retVal = TCPIP_OK;
  }
  /* #40 Return address of the default gateway, if configured. */
  else if (TcpIp_GetActiveDefGwAddrOfIpV4CtrlDyn(IpV4CtrlIdx) != IPV4_ADDR_ANY)
  {
    dstAddr = TcpIp_GetActiveDefGwAddrOfIpV4CtrlDyn(IpV4CtrlIdx);
    retVal = TCPIP_OK;
  }
  /* #50 Trigger AR if destination or source address is linklocal address. */
  else if (   ((dstAddr & IPV4_IP_LL_NET_ADDR_MASK) == IPV4_IP_LL_NET_ADDR_NET)
           || ((TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx) & IPV4_IP_LL_NET_ADDR_MASK) == IPV4_IP_LL_NET_ADDR_NET))
  {
    retVal = TCPIP_OK;
  }
  /* #60 Otherwise discard the request, because destination is not on this link and no default router known -> No next hop existing. */
  else
  {
    retVal = TCPIP_E_NOT_OK;
  }

  if (retVal == TCPIP_OK)
  {
    retVal = IpV4_Arp_GetPhysicalAddress(IpV4CtrlIdx, (TcpIp_SizeOfSocketDynType)SocketIdx, dstAddr,                    /* SBSW_TCPIP_VALID_PTR_CALLER */
                                         NextHopPhysAddrPtr, TRUE);
  }

  return retVal;
} /* IpV4_Ip_VGetNextHopPhysAddr */  /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV4_Ip_VGetLocalAddrIdxAndCtrlIdx
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
IPV4_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlIterType, IPV4_CODE) IpV4_Ip_VGetLocalAddrIdxAndCtrlIdx(
  IPV4_P2V(TcpIp_LocalAddrV4IterType) LocalAddrV4IdxPtr,
  IpBase_AddrInType                   DestAddr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_IpV4CtrlIterType ipV4CtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  if(*LocalAddrV4IdxPtr != TCPIP_LOCAL_ADDR_V4_IDX_ANY)
  {
    /* #10 Return index of the IP controller that belongs to *AddrIdxPtr, if *addrPtr != IPV4_ADDR_ID_ANY. */
    ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(*LocalAddrV4IdxPtr);
  }
  else
  {
    /* #20 Iterate all IP controllers to determine the index and auto-select/broadcast address ID of
           the IP controller that has a unicast address which is in the same subnet as DestAddr. */
    TcpIp_IpV4CtrlIterType candidateIpV4CtrlIdx;

    for (candidateIpV4CtrlIdx = 0; candidateIpV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl(); candidateIpV4CtrlIdx++)
    {
      if(IpV4_Ip_VCtrlIsOnline(candidateIpV4CtrlIdx) == TRUE)
      {
        if(    (DestAddr & TcpIp_GetActiveNetMaskOfIpV4CtrlDyn(candidateIpV4CtrlIdx))
            == (   TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(candidateIpV4CtrlIdx)
                 & TcpIp_GetActiveNetMaskOfIpV4CtrlDyn(candidateIpV4CtrlIdx)
               )
          )
        {
          /* address is part of this subnet */
          break;
        }
      }
    }

    if(candidateIpV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl())
    {
      /* use selected controller */
      ipV4CtrlIdx = candidateIpV4CtrlIdx;
      /* set AddrIdx to AutoSelect_Broadcast address of the selected controller */
      *LocalAddrV4IdxPtr = TcpIp_GetLocalAddrV4BroadcastIdxOfIpV4Ctrl(ipV4CtrlIdx);                                     /* SBSW_TCPIP_VALID_PTR_CALLER */
    }
    /* #30 Otherwise return index and auto-select/broadcast address ID of the default controller, if configured. */
    else if (TcpIp_IsIpV4CtrlDefaultUsedOfIpV4General(TCPIP_IPV4GENERAL_IDX) == TRUE)
    {
      TcpIp_SizeOfIpV4CtrlType IpV4CtrlDefaultIdx = TcpIp_GetIpV4CtrlDefaultIdxOfIpV4General(TCPIP_IPV4GENERAL_IDX);

      if(IpV4_Ip_VCtrlIsOnline(IpV4CtrlDefaultIdx) == TRUE)
      {
        /* use default controller for all messages not directed to nodes in own subnet(s) */
        ipV4CtrlIdx = IpV4CtrlDefaultIdx;
        /* set AddrIdx to AutoSelect_Broadcast address of the selected controller */
        *LocalAddrV4IdxPtr = TcpIp_GetLocalAddrV4BroadcastIdxOfIpV4Ctrl(ipV4CtrlIdx);                                   /* SBSW_TCPIP_VALID_PTR_CALLER */
      }
      else
      {
        /* no suitable controller in active state found */
        ipV4CtrlIdx = TcpIp_GetSizeOfIpV4Ctrl();
      }
    }
    /* #40 Otherwise return negative result (TcpIp_GetSizeOfIpV4Ctrl()). */
    else
    {
      /* no suitable controller in active state found */
      ipV4CtrlIdx = TcpIp_GetSizeOfIpV4Ctrl();
    }
  }

  return ipV4CtrlIdx;
} /* IpV4_Ip_VGetLocalAddrIdxAndCtrlIdx */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_VFragmentProvideTxBuffers
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
IPV4_LOCAL_INLINE FUNC(BufReq_ReturnType, IPV4_CODE) IpV4_Ip_VFragmentProvideTxBuffers(
  TcpIp_IpV4CtrlIterType                    IpV4CtrlIdx,
  TcpIp_SocketDynIterType                   SocketIdx,
  uint16                                    IpPayloadLen,
  IPV4_P2V(TcpIp_IpTxRequestDescriptorType) IpTxReqDescrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal          = BUFREQ_E_NOT_OK;
  uint8             prevEthBufIdx   = IPV4_IP_TX_BUF_IDX_INV;
  uint16            payloadLenLocal = IpPayloadLen;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Loop: Request as many buffers from the lower-layer (EthIf) as required to store the complete IP payload.
     In case the IP payload exceeds the size of one EthIf buffer, multiple buffers will be requested and
     a fragmented IP packet will be sent. */
  while (payloadLenLocal > 0u)
  {
    IPV4_P2V(Eth_DataType) ethBufPtr;
    uint8 ethBufIdx;
    uint16 ethBufLen;
    uint16 fragPayloadLen = (uint16)(TcpIp_GetMtuTxOfIpV4Ctrl(IpV4CtrlIdx) - IPV4_IP_DEF_HEADER_LENGTH_BYTE);

    /* #20 In case the IP payload does not fit into one IP packet, multiple fragments have to be sent.
           Otherwise only one fragment is required */
    if (fragPayloadLen < payloadLenLocal)
    {
      /* IP payload does not fit into one IP packet -> IP packet has to be sent in multiple fragments. */
      /* #30 In case of multiple fragments, trim payload length of each fragment to be multiple of 8 octets */
      fragPayloadLen -= (fragPayloadLen % 8u);
      payloadLenLocal   -=  fragPayloadLen;
    }
    else
    {
      /* Complete IP payload fits into this fragment. */
      fragPayloadLen  = payloadLenLocal;
      payloadLenLocal    = 0;
    }

    /* #40 Calculate the required buffer length and request TX buffer from lower-layer (EthIf). */
    ethBufLen = (fragPayloadLen + IPV4_IP_DEF_HEADER_LENGTH_BYTE);                                                      /* SBSW_TCPIP_CM_R12 */

    retVal = TCPIP_LL_ProvideTxBuffer(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), IPV4_IP_FRAME_TYPE,                 /* SBSW_TCPIP_LL_PROVIDE_TX_BUF_FRAGM */
                                      IPV4_GET_SOCKET_ETHIF_FRAME_PRIO(SocketIdx, IpV4CtrlIdx), &ethBufIdx, &ethBufPtr,
                                      &ethBufLen);

    /* The lower layer may provide a buffer that is larger than requested.
       This is ok for unfragmented packets and for the last fragment but other fragments must have a length
       which is a multiple of 8. Therefore the provided buffer must be limited to the requested length. */
    if (payloadLenLocal > 0u)
    {
      ethBufLen = fragPayloadLen + IPV4_IP_DEF_HEADER_LENGTH_BYTE;
    }

    /* #50 In case the lower layer (EthIf) has indicated a suitable buffer, proceed only after the returned ethBufIdx is valid */
    if (BUFREQ_OK == retVal)                                                                                            /* SBSW_TCPIP_CM_R7 */
    {
      TcpIp_Buf2TxReqMapStartIdxOfIpV4CtrlType buf2TxReqMapStartIdx = TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
      TcpIp_Buf2TxReqMapIterType nextBuf2TxReqMapIdx;

      /* #60 In case the returned ethBufIdx is valid proceed by updating the TX descriptor depending on the fragment being a first one or not. */
      if ((buf2TxReqMapStartIdx + ethBufIdx) < TcpIp_GetBuf2TxReqMapEndIdxOfIpV4Ctrl(IpV4CtrlIdx))                      /* SBSW_TCPIP_CM_R8 */
      {
        /* #70 Store buffer index in TX descriptor or append buffer to previously requested buffer,
               if this is not the first fragment. */
        if (prevEthBufIdx == IPV4_IP_TX_BUF_IDX_INV)                                                                    /* SBSW_TCPIP_CM_R9 */
        {
          /* This is an ethernet buffer for the first (and maybe the only) fragment. */
          IpTxReqDescrPtr->BufIdx      = ethBufIdx;                                                                     /* SBSW_TCPIP_VALID_PTR_CALLER */
          IpTxReqDescrPtr->CurBufIdxV4 = ethBufIdx;                                                                     /* SBSW_TCPIP_VALID_PTR_CALLER */
        }
        else
        {
          /* This is an ethernet buffer for an additional IP fragment.
           * Link buffer of previous fragment with this fragment. */
          nextBuf2TxReqMapIdx = buf2TxReqMapStartIdx + prevEthBufIdx;
          TcpIp_SetEthBufIdxNextOfBuf2TxReqMap(nextBuf2TxReqMapIdx, ethBufIdx);                                         /* SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_PREPARATION */
        }

        nextBuf2TxReqMapIdx = buf2TxReqMapStartIdx + ethBufIdx;
        /* #80 Store data pointer and length of buffer. */
        /* PRQA S 0310 2 */ /* MD_IPV4_Rule11.4_0310_ethbuf */
        TcpIp_SetEthBufPtrOfBuf2TxReqMap(nextBuf2TxReqMapIdx, (IPV4_P2V(uint8))ethBufPtr);                              /* SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_PREPARATION */
        TcpIp_SetEthBufLenOfBuf2TxReqMap(nextBuf2TxReqMapIdx, ethBufLen);                                               /* SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_PREPARATION */
        TcpIp_SetEthBufIdxNextOfBuf2TxReqMap(nextBuf2TxReqMapIdx, IPV4_IP_TX_BUF_IDX_INV);                              /* SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_PREPARATION */
        prevEthBufIdx = ethBufIdx;                                                                                      /* SBSW_TCPIP_CM_R11 */
      }
      else
      {
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
        TcpIp_CallDetReportError(TCPIP_API_ID_V_INTERNAL_FUNCTION, TCPIP_E_INV_ARG);
# endif
      }
    }
    else
    /* #90 In case an EthIf buffer was not be provided, do a rollback, i.e.:
           Release already provided buffers for all previous fragments (if there are such). */
    {
      /* #100 Do a transmit cancellation in case there has been a previous fragment */
      if (IPV4_IP_TX_BUF_IDX_INV != prevEthBufIdx)
      {
        (void)IpV4_Ip_Transmit(IpTxReqDescrPtr, 0, 0, FALSE, 0, FALSE);                                                 /* SBSW_TCPIP_VALID_PTR_CALLER */
      }

      retVal = BUFREQ_E_NOT_OK;
      break;
    }
  } /* while (payloadLenLocal > 0) */

  /* #110 Update information in TX descriptor, if no error occurred. */
  if( BUFREQ_OK == retVal)
  {
    /* IpPayloadPtr points to payload of the first (and maybe the only) fragment of this IP packet */
    IpTxReqDescrPtr->EthPayloadPtr =                                                                                    /* SBSW_TCPIP_VALID_PTR_CALLER */
      TcpIp_GetEthBufPtrOfBuf2TxReqMap(TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(IpV4CtrlIdx) + IpTxReqDescrPtr->BufIdx);
    IpTxReqDescrPtr->EthPayloadLen =                                                                                    /* SBSW_TCPIP_VALID_PTR_CALLER */
      TcpIp_GetEthBufLenOfBuf2TxReqMap(TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(IpV4CtrlIdx) + IpTxReqDescrPtr->BufIdx);
    /* STORYC-5813 - update payload offset to account for AH external header */
#if (TCPIP_SUPPORT_IPSEC == STD_ON)
    IpTxReqDescrPtr->IpPayloadOfs  = IPV4_IP_DEF_HEADER_LENGTH_BYTE + IpTxReqDescrPtr->ExtHdrLenBytes;                  /* SBSW_TCPIP_VALID_PTR_CALLER */
#else
    IpTxReqDescrPtr->IpPayloadOfs  = IPV4_IP_DEF_HEADER_LENGTH_BYTE;                                                    /* SBSW_TCPIP_VALID_PTR_CALLER */
#endif
  }

  return retVal;
} /* IpV4_Ip_VFragmentProvideTxBuffers */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_FragmentProvideTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_FragmentProvideTxBuffer(
  IPV4_P2V(TcpIp_IpTxRequestDescriptorType)  IpTxReqDescrPtr,
  IPV4_P2V(uint8)                           *BufPtrPtr,
  IPV4_P2V(uint16)                           BufLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpTxReqDescrPtr != NULL_PTR);
  TCPIP_ASSERT(BufPtrPtr       != NULL_PTR);
  TCPIP_ASSERT(BufLenPtr       != NULL_PTR);

  /* #10 Check if there is another TX buffer fragment available. */
  if (IpTxReqDescrPtr->CurBufIdxV4 != IPV4_IP_TX_BUF_IDX_INV)
  {
    /* #20 Update output parameters. */
    TcpIp_LocalAddrV4IterType localAddrV4Idx = IpTxReqDescrPtr->SrcAddrIdx;
    TcpIp_IpV4CtrlIterType ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(localAddrV4Idx);
    TcpIp_Buf2TxReqMapIterType buf2TxReqMapIdx = (TcpIp_Buf2TxReqMapIterType)TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(ipV4CtrlIdx)
                                                 + (TcpIp_Buf2TxReqMapIterType)IpTxReqDescrPtr->CurBufIdxV4;

    uint8 nxtBufIdx = TcpIp_GetEthBufIdxNextOfBuf2TxReqMap(buf2TxReqMapIdx);

    TCPIP_ASSERT(buf2TxReqMapIdx < TcpIp_GetBuf2TxReqMapEndIdxOfIpV4Ctrl(ipV4CtrlIdx));

    /* #30 Move cursor to next TX buffer fragment. */
    if (nxtBufIdx != IPV4_IP_TX_BUF_IDX_INV)
    {
      buf2TxReqMapIdx = (TcpIp_Buf2TxReqMapIterType)TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(ipV4CtrlIdx) + (TcpIp_Buf2TxReqMapIterType)nxtBufIdx;

      TCPIP_ASSERT(buf2TxReqMapIdx < TcpIp_GetBuf2TxReqMapEndIdxOfIpV4Ctrl(ipV4CtrlIdx));

      (*BufPtrPtr) = &TcpIp_GetEthBufPtrOfBuf2TxReqMap(buf2TxReqMapIdx)[IPV4_IP_DEF_HEADER_LENGTH_BYTE];                /* SBSW_TCPIP_VALID_PTR_CALLER */
      (*BufLenPtr) =  TcpIp_GetEthBufLenOfBuf2TxReqMap(buf2TxReqMapIdx) - IPV4_IP_DEF_HEADER_LENGTH_BYTE;               /* SBSW_TCPIP_VALID_PTR_CALLER */

      retVal = E_OK;
    }

    IpTxReqDescrPtr->CurBufIdxV4 = nxtBufIdx;                                                                           /* SBSW_TCPIP_VALID_PTR_CALLER */
  }

  return retVal;
} /* IpV4_Ip_FragmentProvideTxBuffer */

/**********************************************************************************************************************
 *  IpV4_Ip_VStoreProtocolChecksum
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VStoreProtocolChecksum(
  uint8           Protocol,
  uint16          ProtocolChecksum,
  IPV4_P2V(uint8) ProtocolHeaderPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Store the checksum in the header, depending on the given protocol TCP, UDP or ICMP. */
  switch (Protocol)
  {
# if (TCPIP_SUPPORT_TCP == STD_ON)
  case TCPIP_PROTOCOL_TCP:
    TcpIp_Tcp_StoreChecksumInHeader(ProtocolChecksum, ProtocolHeaderPtr);                                               /* SBSW_TCPIP_VALID_PTR_CALLER */
    break;
# endif
  case TCPIP_PROTOCOL_UDP:
    TcpIp_Udp_StoreChecksumInHeader(ProtocolChecksum, ProtocolHeaderPtr);                                               /* SBSW_TCPIP_VALID_PTR_CALLER */
    break;

# if (TCPIP_SUPPORT_ICMPV4 == STD_ON)                                                                                   /* COV_TCPIP_ICMPV4_ALWAYS_ON */
  case IPV4_IP_PROTOCOL_ICMP:
    IpV4_Icmp_StoreChecksumInHeader(ProtocolChecksum, ProtocolHeaderPtr);                                               /* SBSW_TCPIP_VALID_PTR_CALLER */
    break;
# endif

  default:
    /* unsupported protocol -> do nothing */
    break;
  }  /* switch(Protocol) */
} /* IpV4_Ip_VStoreProtocolChecksum */

/**********************************************************************************************************************
 *  IpV4_Ip_VTransmitFragments
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
 *
 */
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_VTransmitFragments(
    TcpIp_IpV4CtrlIterType                    IpV4CtrlIdx,
    IPV4_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescrPtr,
    uint8                                     IpProtocol,
    uint16                                    IpPayloadLen,
    IPV4_P2V(uint8)                           DestPhysAddrPtr,
    boolean                                   CalculateChecksum,
    boolean                                   ReqTxConfirmation,
    uint8                                     UlReqIdx,
    uint16                                    Identification)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal             = E_OK;
  uint16         ipPayloadLenRemain = IpPayloadLen;
  uint8          ethBufIdx          = IpTxReqDescrPtr->BufIdx;
  uint16         nextFragBlockOfs   = 0;
  uint32         protocolChecksum   = TCPIP_CHECKSUM_UNSET;
  boolean        chkSumFlag         = CalculateChecksum;
#if (TCPIP_SUPPORT_IPSEC == STD_ON)
  uint16         extHdrLen          = IpTxReqDescrPtr->ExtHdrLenBytes;
#endif


  /* ----- Implementation ----------------------------------------------- */
  /* #10 Loop all IP fragments in 2 "Passes".
         Pass 1 is done only if checksum for each fragment shall be calculated in software.
         Pass 2, which actually transmits all fragments, is done always. */
  /* for( each provided ethernet buffer ) */
  while (ethBufIdx != IPV4_IP_TX_BUF_IDX_INV)                                                                           /* SBSW_TCPIP_CM_R13 */
  {
    /* #20 Initialize the current Eth buffer index with the value stored for the given IP controller */
    /* Store next ethernet buffer index before releasing current buffer
       because next pointer may be overwritten directly after releasing the buffer. */
    uint8 ethBufIdxNext =
      TcpIp_GetEthBufIdxNextOfBuf2TxReqMap(TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(IpV4CtrlIdx) + ethBufIdx);

    uint8 nextHdr = IpProtocol;

    /* #30 In the middle of Pass 1 or Pass 2 do the actions for that Pass.
           Otherwise end the particular Pass with no action (for Pass 1)
           or with transmit cancellation of the last (empty) fragment (for Pass 2). */
    if (ipPayloadLenRemain > 0u)
    {
      IpBase_AddrInType srcAddr;
      IPV4_P2V(uint8)   ethPayloadPtr  = TcpIp_GetEthBufPtrOfBuf2TxReqMap(
                                           TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(IpV4CtrlIdx) + ethBufIdx);
      uint16            ethPayloadLen  = TcpIp_GetEthBufLenOfBuf2TxReqMap(
                                           TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(IpV4CtrlIdx) + ethBufIdx);
      uint16            fragBlockOfs   = nextFragBlockOfs;
#if (TCPIP_SUPPORT_IPSEC == STD_ON)
      /* Subtract the IpSec header length from fragment payload length */
      uint16            fragPayloadLen = (uint16)(ethPayloadLen - IPV4_IP_DEF_HEADER_LENGTH_BYTE - extHdrLen);
#else
      uint16            fragPayloadLen = (uint16)(ethPayloadLen - IPV4_IP_DEF_HEADER_LENGTH_BYTE);
#endif
      boolean           fragIsFirst    = (boolean)(fragBlockOfs == 0u);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
      boolean           fragIsLast;

#if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
      /* If Dhcp is enabled, broadcast by a client prior to that client obtaining
         its IP address must have the source address field in the IP header
         set to 0. [RFC2131 4.1 Constructing and sending DHCP messages]
       */
      srcAddr = (IPV4_GET_SOCKET_FORCE_ZERO_SRC_ADDR(IpTxReqDescrPtr->SockIdx))? 0u :
                    TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx);
#else
      srcAddr = TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx);
#endif
      /* #40 Check if the remaining data fits into one IP packet or not
             and set remaining payload length to 0 in case this is the last packet. */
      if (ipPayloadLenRemain > fragPayloadLen)
      {
        /* remaining data does not fit into one IP packet */
        fragIsLast = FALSE;

        /* All fragment buffers except for the last should have a length that is a multiple of 8 octets. */
# if (TCPIP_SUPPORT_IPSEC == STD_ON)
        /* If IpSec is enabled, the IpSec header is part of the fragment payload */
        TCPIP_ASSERT(0u == ((fragPayloadLen + extHdrLen) % 8u));
# else
        TCPIP_ASSERT(0u == (fragPayloadLen % 8));
# endif
        nextFragBlockOfs   += (fragPayloadLen / 8u);
        ipPayloadLenRemain -=  fragPayloadLen;
      }
      else
      {
        /* this is the last fragment */
        fragIsLast = TRUE;

        fragPayloadLen = ipPayloadLenRemain;
        ipPayloadLenRemain  = 0;
      }

#if (TCPIP_SUPPORT_IPSEC == STD_ON)
      /* #50 if IpSec header is inserted, update payload length to include IpSec header length */
      if (   (fragIsFirst == TRUE) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          && (IpTxReqDescrPtr->SaEntryIdx < TcpIp_GetSizeOfSaEntry()))
      {
        nextHdr = IPV4_IP_PROTOCOL_AH;
      }
#endif

      /* #60 In case checksum shall be calculated do calculate both pseudo header and packet checksum */
      if (chkSumFlag == TRUE)
      {
        uint16 ipTotHdrLenBytes = IPV4_IP_DEF_HEADER_LENGTH_BYTE;
        IPV4_P2C(uint8) fragPayloadPtr;

#if (TCPIP_SUPPORT_IPSEC == STD_ON)
        /* #70 Update payload length to include IpSec header length */
        ipTotHdrLenBytes += extHdrLen;
#endif
        /* #80 In pass 1 of the iteration of all IP fragments, calculate checksum of each fragment */
        fragPayloadPtr = &ethPayloadPtr[ipTotHdrLenBytes];

        /* #90 Call the upper layer checksum calculation function
               in case its the first fragment and the protocol is TCP or UDP. */
        if ((fragIsFirst == TRUE) && ((IpProtocol == TCPIP_PROTOCOL_TCP) || (IpProtocol == TCPIP_PROTOCOL_UDP)))
        {
          /* Calculate pseudo header checksum (excluding the IpSec header) */
          protocolChecksum =
            TcpIp_VCalcIpV4PseudoHdrChecksum(IpTxReqDescrPtr->DestAddrV4, srcAddr, IpProtocol, IpPayloadLen);
        }

        /* #100 In case of a 'last' fragment, calculate payload checksum of last fragment
               and store finalized value in the upper layer header.
               Otherwise calculate payload checksum of a 'first' or 'intermediate' fragment */
        if (fragIsLast == TRUE)
        {
          IPV4_P2V(uint8) protocolHdrPtr =
              &TcpIp_GetEthBufPtrOfBuf2TxReqMap(TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(IpV4CtrlIdx)
            + IpTxReqDescrPtr->BufIdx)[ipTotHdrLenBytes];

          protocolChecksum = IpBase_TcpIpChecksumAdd(fragPayloadPtr, fragPayloadLen, protocolChecksum, TRUE);           /* SBSW_TCPIP_FUNC_CALL_CHECKSUM_ADD_TX_FRAGM */

          IpV4_Ip_VStoreProtocolChecksum(IpProtocol, (uint16)protocolChecksum, protocolHdrPtr);                         /* SBSW_TCPIP_FUNC_CALL_PROT_CHECKSUM */
        }
        else
        {
          protocolChecksum = IpBase_TcpIpChecksumAdd(fragPayloadPtr, fragPayloadLen, protocolChecksum, FALSE);          /* SBSW_TCPIP_FUNC_CALL_CHECKSUM_ADD_TX_FRAGM */
        }
      }
      else
      {
        /* #110 In pass 2 of the iteration of all IP fragments, trigger the transmission of each fragment. */
        uint16 flagsOffset;
        TcpIp_IpV4SocketDynIterType ipV4SocketIdx = IpTxReqDescrPtr->SockIdx;
#if (TCPIP_SUPPORT_IPSEC == STD_ON)
        Std_ReturnType ipSecRetVal;
        /* Total fragment length includes the extension header length (if inserted) */
        uint16 FragTotalLen = fragPayloadLen + IPV4_IP_DEF_HEADER_LENGTH_BYTE + extHdrLen;
#else
        uint16 FragTotalLen = fragPayloadLen + IPV4_IP_DEF_HEADER_LENGTH_BYTE;
#endif
        TcpIp_Buf2TxReqMapIterType buf2TxReqMapIdx = TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(IpV4CtrlIdx) + ethBufIdx;

        /* The packet has been built and queued for transmission
         * - The below code inserts the IP header fields and invokes the Link Layer transmission
         * - This is where the ICV will be calculated and Authentication header will be inserted
         */
        TCPIP_ASSERT(buf2TxReqMapIdx < TcpIp_GetBuf2TxReqMapEndIdxOfIpV4Ctrl(IpV4CtrlIdx));


        /* #120 Update the fields of IP header */
        TCPIP_PUT_UINT8(ethPayloadPtr, TCPIP_IPV4_HDR_OFS_VER_IHL, IPV4_HDR_FIELD_CREATE_VER_IHL(IPV4_IP_DEF_HEADER_LENGTH_BYTE));/* SBSW_TCPIP_WRITE_IPV4_HDR_ETH_PAYLOAD */
        TCPIP_PUT_UINT8(ethPayloadPtr, TCPIP_IPV4_HDR_OFS_PROT, nextHdr);                                               /* SBSW_TCPIP_WRITE_IPV4_HDR_ETH_PAYLOAD */
        TCPIP_PUT_UINT16(ethPayloadPtr, TCPIP_IPV4_HDR_OFS_TOT_LEN, FragTotalLen);                                      /* SBSW_TCPIP_WRITE_IPV4_HDR_ETH_PAYLOAD */
        TCPIP_PUT_UINT16(ethPayloadPtr, TCPIP_IPV4_HDR_OFS_IDENT, Identification);                                      /* SBSW_TCPIP_WRITE_IPV4_HDR_ETH_PAYLOAD */
        TCPIP_PUT_UINT32_RAW(ethPayloadPtr, TCPIP_IPV4_HDR_OFS_SRC_ADDR, srcAddr);                                      /* SBSW_TCPIP_WRITE_IPV4_HDR_ETH_PAYLOAD */
        TCPIP_PUT_UINT32_RAW(ethPayloadPtr, TCPIP_IPV4_HDR_OFS_DEST_ADDR, IpTxReqDescrPtr->DestAddrV4);                 /* SBSW_TCPIP_WRITE_IPV4_HDR_ETH_PAYLOAD */
        TCPIP_PUT_UINT8(ethPayloadPtr, TCPIP_IPV4_HDR_OFS_TOS, IPV4_GET_SOCKET_TYPE_OF_SERVICE(IpTxReqDescrPtr->SockIdx, IpV4CtrlIdx));/* SBSW_TCPIP_WRITE_IPV4_HDR_ETH_PAYLOAD */
        TCPIP_PUT_UINT8(ethPayloadPtr, TCPIP_IPV4_HDR_OFS_TTL, IPV4_GET_SOCKET_TIME_TO_LIVE(IpTxReqDescrPtr->SockIdx, IpV4CtrlIdx));/* SBSW_TCPIP_WRITE_IPV4_HDR_ETH_PAYLOAD */
        flagsOffset = (uint16)(IPV4_IP_FLAGS_DONT_FRAGMENT | fragBlockOfs);

        if (fragIsLast == FALSE)
        {
          flagsOffset |= IPV4_IP_FLAGS_MORE_FRAGMENTS;
        }

        /* Update the flag offset field */
        TCPIP_PUT_UINT16(ethPayloadPtr, TCPIP_IPV4_HDR_OFS_FLAGS_OFFSET, flagsOffset);                                  /* SBSW_TCPIP_WRITE_IPV4_HDR_ETH_PAYLOAD */

#if (TCPIP_SUPPORT_IPSEC == STD_ON)
        /* #130 If valid IpSecConfigset is present, perform IpSec processing of the packet */
        if (TcpIp_IsIpSecConfigSetUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
        {
          ipSecRetVal = TcpIp_IpSec_ProcessTxPacket(IpV4CtrlIdx, IpTxReqDescrPtr, ethPayloadPtr, FragTotalLen, IpProtocol);   /* SBSW_TCPIP_VALID_PTR_CALLER */
        }
        /* #140 Otherwise, proceed with packet Tx */
        else
        {
          ipSecRetVal = E_OK;
        }
#endif

        /* Zero is used for calculation. Correct checksum will be set later. */
        TCPIP_PUT_UINT16_RAW(ethPayloadPtr, TCPIP_IPV4_HDR_OFS_CHECKSUM, TCPIP_CHECKSUM_UNSET);                         /* SBSW_TCPIP_WRITE_IPV4_HDR_ETH_PAYLOAD */

        /* #150 In case HW based checksum is configured: Calculate IP header checksum and insert into header. */
        if (TcpIp_IsHwChecksumIpOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
        {
          /* Checksum already set to zero. Checksum will be calculated by lower layer. */
        }
        else
        {
          TCPIP_PUT_UINT16_RAW(ethPayloadPtr, TCPIP_IPV4_HDR_OFS_CHECKSUM, (uint16)IpBase_TcpIpChecksumAdd(ethPayloadPtr, IPV4_IP_DEF_HEADER_LENGTH_BYTE, 0, TRUE));/* SBSW_TCPIP_WRITE_IPV4_HDR_ETH_PAYLOAD */ /* SBSW_TCPIP_FUNC_CALL_CHECKSUM_ADD_TX_FRAGM */
        }

        /* #160 Store information that may be required for TX-confirmation */
        TcpIp_SetProtocolOfIpV4SocketDyn(ipV4SocketIdx, IpProtocol);                                         /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
        TcpIp_SetSocketDynIdxOfBuf2TxReqMap(buf2TxReqMapIdx, IpTxReqDescrPtr->SockIdx);                                 /* SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_USAGE */
        TcpIp_SetUlTxReqIdxOfBuf2TxReqMap(buf2TxReqMapIdx, UlReqIdx);                                                   /* SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_USAGE */

#if (TCPIP_SUPPORT_IPSEC == STD_ON)
        /* #170 Trigger transmission of packet if packet was authenticated successfully */
        if (ipSecRetVal == E_OK)
        {
#endif
          /* #180 Trigger the transmission of all fragments: Transmission of the last n fragments is aborted */
          /* Use macro TCPIP_LL_Transmit to transmit the frame. */
          if (E_OK == TCPIP_LL_Transmit(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), ethBufIdx, IPV4_IP_FRAME_TYPE,
            ReqTxConfirmation, FragTotalLen, DestPhysAddrPtr))                                                          /* SBSW_TCPIP_FUNC_CALL_ETHIF_TRANSMIT */
          {
            retVal = E_OK;
          }
          else
          {
            retVal = E_NOT_OK;
          }
#if (TCPIP_SUPPORT_IPSEC == STD_ON)
        }
        /* #190 Drop packet if packet not authenticated successfully */
        else
        {
          retVal = E_NOT_OK;
          /* #200 Cancel transmit to clear the buffer */
          (void)TCPIP_LL_Transmit(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), ethBufIdx, IPV4_IP_FRAME_TYPE, FALSE, 0,
                                  DestPhysAddrPtr);                                                                     /* SBSW_TCPIP_FUNC_CALL_ETHIF_TRANSMIT */
        }
#endif
      }
    }
    /* #210 In case there is no more data to send, cancel the transmission of this (last) fragment.
            DestMacAddr will be ignored in the called function in case the length to be transmitted is given as 0.
            Otherwise pass 1 (checksum calculation) is still active. */
    else if ((chkSumFlag == FALSE) || (IpPayloadLen == 0u))
    {
      (void)TCPIP_LL_Transmit(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), ethBufIdx, IPV4_IP_FRAME_TYPE, FALSE, 0,
                              DestPhysAddrPtr);                                                                         /* SBSW_TCPIP_FUNC_CALL_ETHIF_TRANSMIT */
    }
    else
    {
      /* This is pass 1/2 (checksum calculation) and transmit shall not be aborted (LenByte > 0).
         Transmit will be done in pass 2/2 (transmit). */
    }

    /* #220 In case the next Eth buffer index is still set, validly set this index with the next index to come.
           Otherwise check whether to start the second pass after the 1st Pass
           or whether to finalize the loop after the 2nd Pass. */
    if (ethBufIdxNext != IPV4_IP_TX_BUF_IDX_INV)
    {
      /* Continue with next fragment. */
      ethBufIdx = ethBufIdxNext;
#if (TCPIP_SUPPORT_IPSEC == STD_ON)
      /* Ext header is added only to the first fragment, other fragments will not have extension header */
      extHdrLen = 0;
#endif
    }
    else if ((retVal == E_OK) && (chkSumFlag == TRUE) && (IpPayloadLen > 0u))
    {
      /* Checksum calculation for all fragments complete -> Restart loop send packets. */
      ethBufIdx          = IpTxReqDescrPtr->BufIdx;
      chkSumFlag         = FALSE;
      ipPayloadLenRemain = IpPayloadLen;
      nextFragBlockOfs   = 0;
    }
    else
    {
      /* All done -> End the loop */
      ethBufIdx = IPV4_IP_TX_BUF_IDX_INV;
    }
  } /* while */

  return retVal;
} /* IpV4_Ip_VTransmitFragments */ /* PRQA S 6010, 6030, 6050, 6060, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPAR, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV4_Ip_Transmit
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
 */
FUNC(TcpIp_ReturnType, IPV4_CODE) IpV4_Ip_Transmit(
  IPV4_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescrPtr, /* PRQA S 3673 */ /* MD_IPV4_Rule8.3 */
  uint16                                    IpPayloadLen,
  uint8                                     IpProtocol,
  boolean                                   ReqTxConfirmation,
  uint8                                     UlTxReqIdx,
  boolean                                   RetryOnPhysAddrMiss)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_ReturnType       retVal = TCPIP_OK;
  /* Dummy value for call of TCPIP_LL_Transmit in case of 'cancel transmit': */
  IpBase_EthPhysAddrType destMacAddr = { 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U };
  TcpIp_SizeOfIpV4CtrlType ipV4CtrlIdx;
  /* Local variable containing length of the Ip payload and extension header length (if included) */
  uint16 ipExtPayloadLen = IpPayloadLen;
  uint16 payloadLenLocal = IpPayloadLen;
  TcpIp_LocalAddrV4IterType localAddrV4Idx = IpTxReqDescrPtr->SrcAddrIdx;
  TcpIp_IpV4SocketDynIterType ipV4SocketIdx = IpTxReqDescrPtr->SockIdx;
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpTxReqDescrPtr != NULL_PTR);
  TCPIP_ASSERT(IpTxReqDescrPtr->SockIdx < TcpIp_GetSizeOfIpV4SocketDyn());

  /* #10 From given the TX request descriptor, read the IP controller index
         that was chosen at the call to "Ip_ProvideTxBuffer": */
  ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(localAddrV4Idx);

  /* #20 Determine next hop link layer address. */
  /* #30 In case the transmission shall be aborted do no Next Hop Determination.
         Otherwise set the destination MAC according to the settings of the given socket index
         (manually or using the next hop calculation function). */
  if(payloadLenLocal == 0u)
  {
    /* Transmit will be aborted. Next Hop determination not required. */
  }
  else if (IPV4_CHK_FLAG_U8(TcpIp_GetTransferBlockOfIpV4SocketDyn(ipV4SocketIdx).Flags,
                                                                  IPV4_IP_TRANSFER_BLOCK_FLAG_PHYS_DEST_ADDR))
  {

    IPV4_P2C(IpV4_Ip_TransferBlockType) transferBlockPtr = TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(ipV4SocketIdx);

    /* Physical destination address for the socket has been set manually. Use this address and skip ARP. */
    TcpIp_VCopyPhysAddr(destMacAddr, transferBlockPtr->PhysDestAddr);                                                   /* SBSW_TCPIP_ARRAY_WRITE_TO_PHYS_ADDR_TYPE_COPY */
  }
  else
  {
    retVal = IpV4_Ip_VGetNextHopPhysAddr(ipV4CtrlIdx, IpTxReqDescrPtr->DestAddrV4, IpTxReqDescrPtr->SockIdx,
                                         &destMacAddr[0]);                                                              /* SBSW_TCPIP_FUNC_CALL_GET_NEXT_HOP */

    if (retVal != TCPIP_OK)
    {
      /* Setting length 0 here causes release of all ethernet buffers for this packet below. */
      payloadLenLocal = 0;
    }
  }

  /* #40 In case the destination MAC was determined or in case MAC determination failure shall be omitted:
         Transmit all fragments. */
  if ((retVal != TCPIP_E_PHYS_ADDR_MISS) || (RetryOnPhysAddrMiss == FALSE))
  {
    boolean calculateProtocolChecksum;
    uint16 identification;
    TcpIp_Buf2TxReqMapIterType buf2TxReqMapIdx = TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(ipV4CtrlIdx)
                                                 + IpTxReqDescrPtr->BufIdx;

    TCPIP_ASSERT(buf2TxReqMapIdx < TcpIp_GetBuf2TxReqMapEndIdxOfIpV4Ctrl(ipV4CtrlIdx));

    /* Increment and persist identification number of IP datagram. */
    IpV4_Ip_Identification++;
    identification = IpV4_Ip_Identification;

#if (TCPIP_SUPPORT_IPSEC == STD_ON)
    ipExtPayloadLen += IpTxReqDescrPtr->ExtHdrLenBytes;
#endif

    /* #50 In case hardware calculation of checksums is possible:
           Determine, if this can be done for the given protocol and set the calculation flag accordingly. */
    if (ipExtPayloadLen > (TcpIp_GetEthBufLenOfBuf2TxReqMap(buf2TxReqMapIdx) - IPV4_IP_DEF_HEADER_LENGTH_BYTE))
    {
      /* #60 This packet needs fragmentation: Checksum calculation for IP protocols by hardware is not supported
                                              for fragmented packets set the checksum calculation flag. */
      calculateProtocolChecksum = TRUE;
    }
    else
    {
      /* #70 According to the configuration, check if the checksum of the upper layer (TCP, UDP or ICMPv4)
             can be calculated by the lower layer (HW) or has to be calculated by the upper layer itself. */
      switch(IpProtocol)
      {
#  if (TCPIP_SUPPORT_TCP == STD_ON)
        case TCPIP_PROTOCOL_TCP:
          calculateProtocolChecksum = (boolean)(TcpIp_IsHwChecksumTcpOfIpV4Ctrl(ipV4CtrlIdx) == FALSE);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
          break;
#  endif
        case TCPIP_PROTOCOL_UDP:
          calculateProtocolChecksum = (boolean)(TcpIp_IsHwChecksumUdpOfIpV4Ctrl(ipV4CtrlIdx) == FALSE);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
          break;

        case IPV4_IP_PROTOCOL_ICMP:
          calculateProtocolChecksum = (boolean)(TcpIp_IsHwChecksumIcmpOfIpV4Ctrl(ipV4CtrlIdx) == FALSE);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
          break;

        default:
          calculateProtocolChecksum = TRUE;
          break;

      } /* switch(Protocol) */
    }

    /* #80 Trigger transmission of all fragments. */
    retVal |= IpV4_Ip_VTransmitFragments(ipV4CtrlIdx, IpTxReqDescrPtr, IpProtocol, payloadLenLocal, &destMacAddr[0],       /* SBSW_TCPIP_FUNC_CALL_TRANSMIT_FRAGS */
                                         calculateProtocolChecksum, ReqTxConfirmation, UlTxReqIdx, identification);
  }
  /* else: Skip sending the packet. */

  return retVal;
} /* IpV4_Ip_Transmit */ /* PRQA S 6050, 6060 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STPAR */

/**********************************************************************************************************************
 *  IpV4_Ip_GetPhysAddr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) IpV4_Ip_GetPhysAddr(
  TcpIp_LocalAddrV4IterType LocalAddrV4Idx,
  IPV4_P2V(uint8)           PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_IpV4CtrlIterType    ipV4CtrlIdx;
  TcpIp_SizeOfEthIfCtrlType ethIfCtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());

  /* #10 Retrieve the IP controller index of the given IP address index. */
  ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);

  /* #20 Retrieve the EthIf controller index of the IP controller index. */
  ethIfCtrlIdx = TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(ipV4CtrlIdx);

  /* #30 Retrieve the physical address for the given EthIf controller. */
  TCPIP_LL_GetPhysAddr(ethIfCtrlIdx, PhysAddrPtr);                                                                      /* SBSW_TCPIP_VALID_PTR_CALLER */
} /* IpV4_Ip_GetPhysAddr */

/**********************************************************************************************************************
 *  IpV4_Ip_GetRemotePhysAddr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(TcpIp_ReturnType, TCPIP_CODE) IpV4_Ip_GetRemotePhysAddr(
  uint8             EthIfCtrlIdx,
  IpBase_AddrInType IpAddr,
  IPV4_P2V(uint8)   PhysAddrPtr,
  boolean           InitRes)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_ReturnType retVal = TCPIP_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Retrieve the physical address in case the given EthIf controller index has an IP controller configured. */
  if (TcpIp_IsIpV4CtrlUsedOfEthIfCtrl(EthIfCtrlIdx) == TRUE)
  {
    retVal = IpV4_Arp_GetPhysicalAddress(TcpIp_GetIpV4CtrlIdxOfEthIfCtrl(EthIfCtrlIdx), IPV4_INV_SOCK_IDX, IpAddr,      /* SBSW_TCPIP_FUNC_CALL_IPV4_ARP_GETPHYSICALADDRESS */
                                         PhysAddrPtr, InitRes);
  }

  return retVal;
} /* IpV4_Ip_GetRemotePhysAddr */

/**********************************************************************************************************************
 *  IpV4_Ip_TxConfirmation
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
FUNC(void, IPV4_CODE) IpV4_Ip_TxConfirmation(
  uint8 EthIfCtrlIdx,
  uint8 EthBufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if (IpV4_State != IPV4_STATE_INIT)
  {
    errorId = IPV4_E_NOT_INITIALIZED;
  }
  /* Check parameter 'EthIfCtrlIdx' */
  else if (EthIfCtrlIdx >= TcpIp_GetSizeOfEthIfCtrl())
  {
    errorId = IPV4_E_INV_PARAM;
  }
  else if (TcpIp_IsIpV4CtrlUsedOfEthIfCtrl(EthIfCtrlIdx) == FALSE)
  {
    /* IP not active on this EthIf controller */
    errorId = IPV4_E_INV_PARAM;
  }
  else
# endif
  {
    /* #20 Map the EthIf controller index to the IP controller index
         and conduct the TX-confirmation in case IP is active on this EthIf controller. */
    TcpIp_IpV4CtrlIterType                   ipV4CtrlIdx          = TcpIp_GetIpV4CtrlIdxOfEthIfCtrl(EthIfCtrlIdx);
    TcpIp_Buf2TxReqMapStartIdxOfIpV4CtrlType buf2TxReqMapStartIdx = TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(ipV4CtrlIdx);

    if ((buf2TxReqMapStartIdx + EthBufIdx) >= TcpIp_GetBuf2TxReqMapEndIdxOfIpV4Ctrl(ipV4CtrlIdx))
    {
      /* Parameter EthBufIdx is invalid */
      errorId = IPV4_E_INV_PARAM;
    }

    if (errorId == TCPIP_E_NO_ERROR)
    {
      /* ----- Implementation ----------------------------------------------- */
      /* #30 In case all parameters are valid:
             Determine the socket index of the given IP controller index, the IP protocol of that socket
             and the index in the table of upper layer TX-requests. */
      TcpIp_Buf2TxReqMapIterType buf2TxReqMapIdx = (TcpIp_Buf2TxReqMapIterType)buf2TxReqMapStartIdx + (TcpIp_Buf2TxReqMapIterType)EthBufIdx;
      TcpIp_SocketDynIterType    ipV4SocketIdx       = TcpIp_GetSocketDynIdxOfBuf2TxReqMap(buf2TxReqMapIdx);

      if (ipV4SocketIdx < TcpIp_GetSizeOfSocketUdpDyn())
      {
        uint8 ipProtocol = TcpIp_GetProtocolOfIpV4SocketDyn(ipV4SocketIdx);

        /* #40 Conduct the TX-confirmation actions, depending on the determined IP protocol:
               Only TCP and UDP are possible and only UDP actually wants a TX-confirmation. */
        if (ipProtocol == IPV4_IP_PROTOCOL_UDP)
        {
          /* #50 Check whether there has been a preceeding ProvideTxBuffer call at the LL:
                 Only then the admin data item UlTxReqIdx has been set for sure and should be used for a callout: */
          if(TcpIp_GetEthBufPtrOfBuf2TxReqMap(buf2TxReqMapIdx) != NULL_PTR)
          {
            TcpIp_Udp_TxConfirmation(ipV4SocketIdx, TcpIp_GetUlTxReqIdxOfBuf2TxReqMap(buf2TxReqMapIdx));
          }
        }
        else
        {
          /* Invalid protocol: This should never happen -> Ignore txConfirmation */
        }
      }
    }
    /* if (errorId == TCPIP_E_NO_ERROR) */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_VINSTANCE_ID, TCPIP_API_ID_CBK_TX_CONFIRMATION, errorId);
  }
# else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif
} /* IpV4_Ip_TxConfirmation */ /* PRQA S 6050, 6080 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV4_Ip_Cbk_TrcvLinkStateChg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Ip_Cbk_TrcvLinkStateChg(
  uint8                 EthIfCtrlIdx,
  EthTrcv_LinkStateType TrcvLinkState)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Currently this function has no functionality, thus simply return. */
  TCPIP_DUMMY_STATEMENT(EthIfCtrlIdx);   /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  TCPIP_DUMMY_STATEMENT(TrcvLinkState);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

} /* IpV4_Ip_Cbk_TrcvLinkStateChg */

/**********************************************************************************************************************
 *  IpV4_Ip_TrcvLinkStateChgInternal
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Ip_TrcvLinkStateChgInternal(
  uint8                 EthIfCtrlIdx,
  EthTrcv_LinkStateType TrcvLinkState)
{

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if IP instance is configured for this controller */
  if (TcpIp_IsIpV4CtrlUsedOfEthIfCtrl(EthIfCtrlIdx) == TRUE)
  {
    TcpIp_IpV4CtrlIdxOfEthIfCtrlType ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfEthIfCtrl(EthIfCtrlIdx);

    if (ETHTRCV_LINK_STATE_ACTIVE != TrcvLinkState)
    {
      /* LINK DOWN */
      /* #20 Invoke shutdown routine if link state is down */
      IpV4_Ip_VCtrlStateShutdown(ipV4CtrlIdx);
    }
    else
    {
      /* LINK UP */
      /* #30 Invoke startup routine if link state is up */
      IpV4_Ip_VCtrlStateStartup(ipV4CtrlIdx);
    }
  }
} /* IpV4_Ip_TrcvLinkStateChgInternal() */


/**********************************************************************************************************************
 *  IpV4_Ip_VCtrlStateShutdown
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Ip_VCtrlStateShutdown(uint8 IpV4CtrlIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set physical link indication to FALSE. (State of IP instance will be changed in MainFunction) */
  TcpIp_SetPhysLinkActiveOfIpV4CtrlDyn(IpV4CtrlIdx, FALSE);                                                         /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_LOCAL */

} /* IpV4_Ip_VCtrlStateShutdown() */

/**********************************************************************************************************************
 *  IpV4_Ip_VCtrlStateStartup
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, IPV4_CODE) IpV4_Ip_VCtrlStateStartup(uint8 IpV4CtrlIdx)
{

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set physical link indication to TRUE. (State of IP instance will be changed in MainFunction) */
  TcpIp_SetPhysLinkActiveOfIpV4CtrlDyn(IpV4CtrlIdx, TRUE);                                                          /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_LOCAL */

# if (TCPIP_SUPPORT_DEM == STD_ON)
  /* #20 In case the link has been down for the current IP controller, before,
         the address-assignment was renewed and thus related DEM event is now being reset */
  if (TcpIp_IsDemEventUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    TcpIp_DemEventIdxOfIpV4CtrlType demEventIdx = TcpIp_GetDemEventIdxOfIpV4Ctrl(IpV4CtrlIdx);
    Dem_EventIdType demEventSNV = TcpIp_GetE_DUPLICATE_DHCP_ADDROfDemEvent(demEventIdx);
    if (demEventSNV != TCPIP_INV_DEM_ID)
    {
      Dem_ReportErrorStatus(demEventSNV, DEM_EVENT_STATUS_PREPASSED);
    }
  }
# endif
} /* IpV4_Ip_VCtrlStateStartup() */

/**********************************************************************************************************************
 *  IpV4_Ip_GetLocNetAddr
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
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_GetLocNetAddr(
  TcpIp_LocalAddrV4IterType                           LocalAddrV4Idx,
  P2VAR(IpBase_AddrInType, AUTOMATIC, IPV4_APPL_DATA) NetAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal = E_NOT_OK;
  TcpIp_IpV4CtrlIterType  ipV4CtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());

  /* #10 Determine the IP controller index of the given IP address index. */
  ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);

  /* #20 In case the given IP address index is NOT that of an AS broadcast address,
         check for multicast support or return a unicast address. */
  if (!TCPIP_IPV4_ADDR_IDX_IS_ASBC(LocalAddrV4Idx))  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    /* #30 In case dynamically requested multicast addresses are possible for this ip controller,
           read the currently requested address */
    if(TcpIp_IsMulticastAddrV4UsedOfLocalAddrV4(LocalAddrV4Idx) == TRUE)
    {
      TcpIp_SizeOfMulticastAddrV4Type multicastAddrV4Idx = TcpIp_GetMulticastAddrV4IdxOfLocalAddrV4(LocalAddrV4Idx);

      /* #40 In case it's no broadcast AND no UNICAST address:
             It's a multicast address for sure: Lookup and return multicast address if possible */
      if(IPV4_ADDR_ANY != TcpIp_GetNetAddrOfMulticastAddrV4Requested(multicastAddrV4Idx))
      {
        *NetAddrPtr = TcpIp_GetNetAddrOfMulticastAddrV4Requested(multicastAddrV4Idx);                                   /* SBSW_TCPIP_VALID_PTR_CALLER */
        retVal = E_OK;
      }
    }
    else
    {
      /* #50 Otherwise return the active unicast address if there is one. */
      *NetAddrPtr = TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(ipV4CtrlIdx);                                                   /* SBSW_TCPIP_VALID_PTR_CALLER */

      if(IPV4_ADDR_ANY != TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(ipV4CtrlIdx))
      {
        retVal = E_OK;
      }
    }
  }
  /* #60 Otherwise return the destination address of the last broadcast packet received. */
  else
  {
    *NetAddrPtr = TcpIp_GetLastBcAddrOfIpV4CtrlDyn(ipV4CtrlIdx);                                                        /* SBSW_TCPIP_VALID_PTR_CALLER */
    retVal = E_OK;
  }

  return retVal;
} /* IpV4_Ip_GetLocNetAddr */

/**********************************************************************************************************************
 *  IpV4_Ip_GetDefaultRouterNetAddr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Ip_GetDefaultRouterNetAddr(
  TcpIp_LocalAddrV4IterType                           LocalAddrV4Idx,
  P2VAR(IpBase_AddrInType, AUTOMATIC, IPV4_APPL_DATA) DefRouterNetAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfIpV4CtrlType ipV4CtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());
  TCPIP_ASSERT(DefRouterNetAddrPtr != NULL_PTR);

  /* #10 Derive IP controller index from the given IP address ID. */
  ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);
  /* #20 Read the value of default router and return. */
  *DefRouterNetAddrPtr = TcpIp_GetActiveDefGwAddrOfIpV4CtrlDyn(ipV4CtrlIdx);                                            /* SBSW_TCPIP_VALID_PTR_CALLER */
}

/**********************************************************************************************************************
 *  IpV4_Ip_GetLocNetMask
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_GetLocNetMask(
  TcpIp_LocalAddrV4IterType                           LocalAddrV4Idx,
  P2VAR(IpBase_AddrInType, AUTOMATIC, IPV4_APPL_DATA) NetMaskPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Set retValue to E_NOT_OK and initialize the value
         pointed to by NetMaskPtr with an invalid value, as default. */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_IpV4CtrlIterType ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);

  /* ----- Implementation ----------------------------------------------- */
  *NetMaskPtr = 0;                                                                                                      /* SBSW_TCPIP_VALID_PTR_CALLER */

  /* #20 In case there is a valid net mask for the given IP controller,
         copy it into the value pointed to by NetMaskPtr and indicate success. */
  if(TcpIp_GetActiveNetMaskOfIpV4CtrlDyn(ipV4CtrlIdx) != 0u)
  {
    *NetMaskPtr = TcpIp_GetActiveNetMaskOfIpV4CtrlDyn(ipV4CtrlIdx);                                                     /* SBSW_TCPIP_VALID_PTR_CALLER */
    retVal = E_OK;
  }

  return retVal;
} /* IpV4_Ip_GetLocNetMask */

/**********************************************************************************************************************
 *  IpV4_Ip_GetActiveAddrAssignmentMethod
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
FUNC(TcpIp_IpAddrAssignmentType, IPV4_CODE) IpV4_Ip_GetActiveAddrAssignmentMethod(
  TcpIp_LocalAddrV4IterType LocalAddrV4Idx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Determine the IP controller index of the given IP address index. */
  TcpIp_SizeOfIpV4CtrlType  ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);
  uint8                     retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #20 Determine address type (ANY, UNICAST, MULTICAST) specified by IpV4LocAddrIdx
         and return the assignment method. */
  if (TCPIP_IPV4_ADDR_IDX_IS_ASBC(LocalAddrV4Idx))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    /* #30 Broadcast address is assigned statically. */
    retVal = TCPIP_IPADDR_ASSIGNMENT_STATIC;
  }
  else if (TcpIp_IsUnicastAddrV4UsedOfLocalAddrV4(LocalAddrV4Idx) == TRUE)
  {
    /* 30 Unicast address assignment method is configuration and runtime dependent. */
    retVal = TcpIp_GetActiveAddrAssignmentMethodOfIpV4CtrlDyn(ipV4CtrlIdx);
  }
  else
  {
    /* #40 Multicast address assignment method is available only in case the multicast feature is configured */

    TcpIp_SizeOfMulticastAddrV4Type multicastAddrV4Idx = TcpIp_GetMulticastAddrV4IdxOfLocalAddrV4(LocalAddrV4Idx);

    TCPIP_ASSERT(TcpIp_IsMulticastAddrV4UsedOfLocalAddrV4(LocalAddrV4Idx) == TRUE);

    TCPIP_ASSERT(multicastAddrV4Idx >= TcpIp_GetMulticastAddrV4StartIdxOfIpV4Ctrl(ipV4CtrlIdx));
    TCPIP_ASSERT(multicastAddrV4Idx <  TcpIp_GetMulticastAddrV4EndIdxOfIpV4Ctrl(ipV4CtrlIdx));

    /* #50 Return the assignment method of the multicast address depending on the address being requested. */
    if(TcpIp_GetNetAddrOfMulticastAddrV4Requested(multicastAddrV4Idx) != IPV4_ADDR_ANY)
    {
      /* #60 Multicast addresses are assigned statically. */
      retVal = TCPIP_IPADDR_ASSIGNMENT_STATIC;
    }
    else
    {
      retVal = TCPIP_IPADDR_ASSIGNMENT_NONE;
    }
  }

  return retVal;
} /* IpV4_Ip_GetActiveAddrAssignmentMethod */

/**********************************************************************************************************************
 * IpV4_Ip_IsAddrIdxAcceptable()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(boolean, IPV4_CODE) IpV4_Ip_IsAddrIdxAcceptable(
  TcpIp_LocalAddrV4IterType BindLocalAddrV4Idx,
  TcpIp_LocalAddrV4IterType RecvLocalAddrV4Idx,
  IPV4_P2V(uint8)           MatchTypePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(BindLocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4() || BindLocalAddrV4Idx == TCPIP_LOCAL_ADDR_V4_IDX_ANY);
  TCPIP_ASSERT(RecvLocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());

  /* #10 Check, whether the given bind local address index is ANY which means a match, always. */
  if(BindLocalAddrV4Idx == TCPIP_LOCAL_ADDR_V4_IDX_ANY)
  {
    *MatchTypePtr = IPV4_ADDR_MATCH_EVER;                                                                               /* SBSW_TCPIP_VALID_PTR_CALLER */
    retVal = TRUE;
  }
  else
  {
    /* #20 Check, whether the address matches filter address (exact match) */
    if(RecvLocalAddrV4Idx == BindLocalAddrV4Idx)
    {
      *MatchTypePtr = IPV4_ADDR_MATCH_EXACT;                                                                            /* SBSW_TCPIP_VALID_PTR_CALLER */
      retVal = TRUE;
    }
    else
    {
      /* #30 Check, whether the bind or received address is an AutoSelect_Multicast address */
      if (TCPIP_IPV4_ADDR_IDX_IS_ASBC(BindLocalAddrV4Idx) || TCPIP_IPV4_ADDR_IDX_IS_ASBC(RecvLocalAddrV4Idx))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      {
        TcpIp_SizeOfIpV4CtrlType ipCtrlBindIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(BindLocalAddrV4Idx);
        TcpIp_SizeOfIpV4CtrlType ipCtrlRecvIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(RecvLocalAddrV4Idx);

        /* #40 Check, whether both addresses are on same controller If-match */
        if(ipCtrlBindIdx == ipCtrlRecvIdx)
        {
          *MatchTypePtr = IPV4_ADDR_MATCH_IF;                                                                           /* SBSW_TCPIP_VALID_PTR_CALLER */
          retVal = TRUE;
        }
        /* else: Leave retVal at FALSE */
      }
      /* else: Leave retVal at FALSE */
    }
  }
  return retVal;
} /* IpV4_Ip_IsAddrIdxAcceptable */

/**********************************************************************************************************************
 *  IpV4_Ip_StoreRequestedAddress
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
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_StoreRequestedAddress(
  TcpIp_IpV4CtrlIterType      IpV4CtrlIdx,
  TcpIp_UnicastAddrV4IterType UnicastAddrV4Idx,
  IpBase_AddrInType           LocalIpAddr,
  uint8                       NetmaskCidr,
  IpBase_AddrInType           DefaultRouter)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case the given IP address is ANY, check whether a default unicast address is configured
         and assign the complete set consisting of IP address, default router and netmask. */
  if (LocalIpAddr == IPV4_ADDR_ANY)
  {
    if (TcpIp_IsDefaultUnicastAddrV4UsedOfUnicastAddrV4(UnicastAddrV4Idx) == TRUE)
    {
      /* Assign configured default address. */
      TcpIp_SizeOfDefaultUnicastAddrV4Type defaultUnicastAddrV4Idx =
        TcpIp_GetDefaultUnicastAddrV4IdxOfUnicastAddrV4(UnicastAddrV4Idx);
      TcpIp_StaticUnicastAddrV4RequestedIdxOfUnicastAddrV4Type staticUnicastAddrV4RequestedIdx =
        TcpIp_GetStaticUnicastAddrV4RequestedIdxOfUnicastAddrV4(UnicastAddrV4Idx);
      TcpIp_SetNetAddrOfStaticUnicastAddrV4Requested(staticUnicastAddrV4RequestedIdx,                                   /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
                                                     TcpIp_GetNetAddrOfDefaultUnicastAddrV4(defaultUnicastAddrV4Idx));
      TcpIp_SetNetMaskOfStaticUnicastAddrV4Requested(staticUnicastAddrV4RequestedIdx,                                   /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
                                                     TcpIp_GetNetMaskOfDefaultUnicastAddrV4(defaultUnicastAddrV4Idx));
      TcpIp_SetDefGwAddrOfStaticUnicastAddrV4Requested(staticUnicastAddrV4RequestedIdx,                                 /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
                                                       TcpIp_GetDefGwAddrOfDefaultUnicastAddrV4(defaultUnicastAddrV4Idx)
                                                      );

      IpV4_Ip_VIpAddrAssignmentReadyNotification(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_STATIC, TRUE);
      retVal = E_OK;
    }
  }
  /* #20 In case the given IP address is BROADCAST, use the NVM stored data, if configured. */
  else if (LocalIpAddr == TCPIP_INADDR_BROADCAST)
  {
# if (TCPIP_SUPPORT_IP_ADDR_NVM_STORAGE == STD_ON)
    if (TcpIp_IsNvmDataUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
    {
      retVal = E_OK;
    }
# endif
  }
  /* #30 In case the given IP address is a valid UNICAST address
         store the complete set of IP address, default router and netmask. */
  else
  {
    if (!(IPV4_ADDR_IS_MULTICAST(LocalIpAddr) || IPV4_ADDR_IS_DIRECTED_BROADCAST(IpV4CtrlIdx, LocalIpAddr)))
    {
      TcpIp_StaticUnicastAddrV4RequestedIdxOfUnicastAddrV4Type staticUnicastAddrV4RequestedIdx =
        TcpIp_GetStaticUnicastAddrV4RequestedIdxOfUnicastAddrV4(UnicastAddrV4Idx);

      TcpIp_SetNetAddrOfStaticUnicastAddrV4Requested(staticUnicastAddrV4RequestedIdx, LocalIpAddr);                     /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
      TcpIp_SetNetMaskOfStaticUnicastAddrV4Requested(staticUnicastAddrV4RequestedIdx,                                   /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
                                                     TCPIP_HTONL(0xFFFFFFFFu << (32u - NetmaskCidr)));
      TcpIp_SetDefGwAddrOfStaticUnicastAddrV4Requested(staticUnicastAddrV4RequestedIdx, DefaultRouter);                 /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */

      IpV4_Ip_VIpAddrAssignmentReadyNotification(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_STATIC, TRUE);
      retVal = E_OK;
    }
  }

  return retVal;
} /* IpV4_Ip_StoreRequestedAddress */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_RequestIpAddrAssignment
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
FUNC(Std_ReturnType, TCPIP_CODE) IpV4_Ip_RequestIpAddrAssignment(
  TcpIp_LocalAddrV4IterType  LocalAddrV4Idx,
  TcpIp_IpAddrAssignmentType AddrAssignmentType,
  IpBase_AddrInType          LocalIpAddr,
  uint8                      NetmaskCidr,
  IpBase_AddrInType          DefaultRouter)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType              retVal = E_NOT_OK;
  TcpIp_SizeOfIpV4CtrlType    ipV4CtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Map TcpIp address assignment type to IPv4 address assignment method. */
  TcpIp_IpAddrAssignmentType addrAssignmentMethod = AddrAssignmentType;

  /* #20 Check input parameters. */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());

  ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);

  /* #30 Verify that IP instance is not in state OFFLINE. */
  if(TcpIp_GetStateOfIpV4CtrlDyn(ipV4CtrlIdx) != IPV4_IP_OFFLINE)
  {
    /* #40 Check if address type is UNICAST or MULTICAST. */
    if(TcpIp_IsUnicastAddrV4UsedOfLocalAddrV4(LocalAddrV4Idx) == TRUE)
    {
      /* #50 For a UNICAST address trigger address assignment if the configured assignment priority is not NONE. */
      uint8 addrAssignmentPrio = IpV4_Ip_VCfgGetAddrAssignmentPrio(ipV4CtrlIdx, addrAssignmentMethod);

      if(addrAssignmentPrio != IPV4_IP_ADDR_ASSIGNMENT_PRIO_NONE)
      {
        TcpIp_AddrAssignmentCfgByPrioStartIdxOfIpV4CtrlType addrAssignmentCfgByPrioStartIdx =
          TcpIp_GetAddrAssignmentCfgByPrioStartIdxOfIpV4Ctrl(ipV4CtrlIdx);
        TcpIp_AddrAssignmentCfgByPrioType addrAssignmentCfg;

        /* assignment priority N has N-1 offset to addrAssignmentCfgByPrioStartIdx */
        addrAssignmentPrio--;

        TCPIP_ASSERT(  (addrAssignmentCfgByPrioStartIdx + addrAssignmentPrio)
                     < TcpIp_GetAddrAssignmentCfgByPrioEndIdxOfIpV4Ctrl(ipV4CtrlIdx));

        addrAssignmentCfg = TcpIp_GetAddrAssignmentCfgByPrio(addrAssignmentCfgByPrioStartIdx + addrAssignmentPrio);

        /* #60 Do not allow address assignment if trigger is configured to AUTOMATIC. */
        if(!IPV4_CHK_FLAG_U8(addrAssignmentCfg, TCPIP_IPV4_ADDR_ASSIGNMENT_FLAG_AUTO_TRIGGER))
        {
          /* #70 Trigger address assignment method. */
          retVal = IpV4_Ip_VTriggerAddrAssignment(ipV4CtrlIdx, addrAssignmentCfg, TRUE);
          /* #80 Store requested address value if assignment method is STATIC. */
          if(addrAssignmentMethod == TCPIP_IPADDR_ASSIGNMENT_STATIC)
          {
            retVal = IpV4_Ip_StoreRequestedAddress(ipV4CtrlIdx, TcpIp_GetUnicastAddrV4IdxOfLocalAddrV4(LocalAddrV4Idx),
                                                   LocalIpAddr, NetmaskCidr, DefaultRouter);

            /* Reset address assignment trigger, if address was not stored because of invalid inputs. */
            if (retVal != E_OK)
            {
              (void)IpV4_Ip_VTriggerAddrAssignment(ipV4CtrlIdx, addrAssignmentCfg, FALSE);
            }
          }
        }
      }
    }
    else if (TcpIp_IsMulticastAddrV4UsedOfLocalAddrV4(LocalAddrV4Idx) == TRUE)
    {
      /* #90 Update MULTICAST address value. */
      retVal = IpV4_Ip_VChangeMulticastAddrAssignment(LocalAddrV4Idx, LocalIpAddr);
    }
    else
    {
      /* Not unicast, not multicast - ASBC address - leave retVal at E_NOT_OK */
    }
  }

  return retVal;
} /* IpV4_Ip_RequestIpAddrAssignment */ /* PRQA S 6050, 6080 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV4_Ip_ReleaseIpAddrAssignment
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
FUNC(Std_ReturnType, TCPIP_CODE) IpV4_Ip_ReleaseIpAddrAssignment(
  TcpIp_LocalAddrV4IterType  LocalAddrV4Idx,
  TcpIp_IpAddrAssignmentType AddrAssignmentType)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType             retVal = E_NOT_OK;
  TcpIp_SizeOfIpV4CtrlType   ipV4CtrlIdx;
  TcpIp_IpAddrAssignmentType addrAssignmentMethodToRelease = TCPIP_IPADDR_ASSIGNMENT_ANY;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());

  /* #10 Map TcpIp address assignment type to IPv4 address assignment method. */
  if(AddrAssignmentType < 0xFFu)
  {
    addrAssignmentMethodToRelease = AddrAssignmentType;
  }
  /* else leave addrAssignmentMethodToRelease at 0xFFu */

  ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);

  /* #20 In case address type is UNICAST handle the related address assignment release. */
  if(TcpIp_IsUnicastAddrV4UsedOfLocalAddrV4(LocalAddrV4Idx) == TRUE)
  {
    TcpIp_AddrAssignmentCfgByPrioStartIdxOfIpV4CtrlType addrAssignmentCfgByPrioIdx;

    /* #30 Iterate all configured address assignment methods (priority is not important here). */
    for (addrAssignmentCfgByPrioIdx = TcpIp_GetAddrAssignmentCfgByPrioStartIdxOfIpV4Ctrl(ipV4CtrlIdx);
         addrAssignmentCfgByPrioIdx < TcpIp_GetAddrAssignmentCfgByPrioEndIdxOfIpV4Ctrl(ipV4CtrlIdx);
         addrAssignmentCfgByPrioIdx++)
    {
      TcpIp_AddrAssignmentCfgByPrioType addrAssignmentCfg = TcpIp_GetAddrAssignmentCfgByPrio(addrAssignmentCfgByPrioIdx);
      TcpIp_IpAddrAssignmentType addrAssignmentMethod = IpV4_Ip_VCfgGetAddrAssignmentMethodByCfg(addrAssignmentCfg);

      /* #40 Only release address assignment if trigger is not configured to AUTOMATIC. */
      if(    (addrAssignmentMethod != TCPIP_IPADDR_ASSIGNMENT_NONE)
          && (!IPV4_CHK_FLAG_U8(addrAssignmentCfg, TCPIP_IPV4_ADDR_ASSIGNMENT_FLAG_AUTO_TRIGGER)))
      {
        /* #50 Release address assignment if method was explicitly specified or all assignments shall be released. */
        if(    (addrAssignmentMethodToRelease == TCPIP_IPADDR_ASSIGNMENT_ANY)
            || (addrAssignmentMethodToRelease == addrAssignmentMethod))
        {
          (void)IpV4_Ip_VTriggerAddrAssignment(ipV4CtrlIdx, addrAssignmentCfg, FALSE);
          retVal = E_OK;
        }
      }
    }
  }
  /* #60 In case MULTICAST RX is supported and address type is MULTICAST:
         Handle the related address assignment release. */
  else if (TcpIp_IsMulticastAddrV4UsedOfLocalAddrV4(LocalAddrV4Idx) == TRUE)
  {
    if (   (addrAssignmentMethodToRelease == TCPIP_IPADDR_ASSIGNMENT_ANY)
        || (addrAssignmentMethodToRelease == TCPIP_IPADDR_ASSIGNMENT_STATIC))
    {
      /* #70 Handle address release of type MULTICAST. */
      retVal = IpV4_Ip_VChangeMulticastAddrAssignment(LocalAddrV4Idx, IPV4_ADDR_ANY);
    }
  }
  else
  {
    /* Not unicast, not multicast - ASBC address - leave retVal at E_NOT_OK */
  }

  return retVal;
} /* IpV4_Ip_ReleaseIpAddrAssignment */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_ResetSocket
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Ip_ResetSocket(
  TcpIp_SocketDynIterType IpV4SocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_P2V(IpV4_Ip_TransferBlockType) transferBlockPtr;
  TCPIP_ASSERT(IpV4SocketIdx < TcpIp_GetSizeOfIpV4SocketDyn());

  /* #10 Retrieve the transfer block and initialize its values. */
  transferBlockPtr = TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(IpV4SocketIdx);

  transferBlockPtr->PhysDestAddr[0] = 0;                                                                                /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK_ETH_PHYS_ADDR */
  transferBlockPtr->PhysDestAddr[1] = 0;                                                                                /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK_ETH_PHYS_ADDR */
  transferBlockPtr->PhysDestAddr[2] = 0;                                                                                /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK_ETH_PHYS_ADDR */
  transferBlockPtr->PhysDestAddr[3] = 0;                                                                                /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK_ETH_PHYS_ADDR */
  transferBlockPtr->PhysDestAddr[4] = 0;                                                                                /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK_ETH_PHYS_ADDR */
  transferBlockPtr->PhysDestAddr[5] = 0;                                                                                /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK_ETH_PHYS_ADDR */
  transferBlockPtr->EthIfFramePrio  = 0;                                                                                /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK */
  transferBlockPtr->TimeToLive      = 0;                                                                                /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK */
  transferBlockPtr->TypeOfService   = 0;                                                                                /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK */
  transferBlockPtr->Flags           = 0;                                                                                /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK */
} /* IpV4_Ip_ResetSocket */

/**********************************************************************************************************************
 *  IpV4_Ip_SetTimeToLive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Ip_SetTimeToLive(
  TcpIp_SocketDynIterType IpV4SocketIdx,
  uint8                   Value)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the time to live for the given socket index */
  TCPIP_ASSERT(IpV4SocketIdx < TcpIp_GetSizeOfIpV4SocketDyn());

  TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(IpV4SocketIdx)->TimeToLive = Value;                                         /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK */
  TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(IpV4SocketIdx)->Flags |= IPV4_IP_TRANSFER_BLOCK_FLAG_TIME_TO_LIVE;          /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK */
} /* IpV4_Ip_SetTimeToLive */

/**********************************************************************************************************************
 *  IpV4_Ip_SetTypeOfService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Ip_SetTypeOfService(
  TcpIp_SocketDynIterType IpV4SocketIdx,
  uint8                   Value)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpV4SocketIdx < TcpIp_GetSizeOfIpV4SocketDyn());

  /* #10 Set the type of service for the given socket index */
  TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(IpV4SocketIdx)->TypeOfService = Value;                                      /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK */
  TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(IpV4SocketIdx)->Flags |= IPV4_IP_TRANSFER_BLOCK_FLAG_TYPE_OF_SERVICE;       /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK */
} /* IpV4_Ip_SetTypeOfService */

/**********************************************************************************************************************
 *  IpV4_Ip_SetPhysDestAddr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Ip_SetPhysDestAddr(
  TcpIp_SocketDynIterType IpV4SocketIdx,
  IPV4_P2C(uint8)         PhysDestAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TCPIP_P2V(IpV4_Ip_TransferBlockType) transferBlockPtr = TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(IpV4SocketIdx);

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpV4SocketIdx < TcpIp_GetSizeOfIpV4SocketDyn());

  /* #10 In case the given PhysDestAddrPtr is not a NULL_PTR:
         Store provided physical address in the socket data structure and set 'valid' flag. */
  if(PhysDestAddrPtr != NULL_PTR)
  {
    uint8_least physAddrByteIdx;

    for (physAddrByteIdx = 0; physAddrByteIdx < IPBASE_ETH_PHYS_ADDR_LEN_BYTE; physAddrByteIdx++)
    {
      transferBlockPtr->PhysDestAddr[physAddrByteIdx] = PhysDestAddrPtr[physAddrByteIdx];                               /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK_ETH_PHYS_ADDR */
    }

    IPV4_SET_FLAG_U8(transferBlockPtr->Flags, IPV4_IP_TRANSFER_BLOCK_FLAG_PHYS_DEST_ADDR);                              /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK */
  }
  else
  /* #20 Otherwise clear the 'valid' flag. */
  {
    IPV4_CLR_FLAG_U8(transferBlockPtr->Flags, IPV4_IP_TRANSFER_BLOCK_FLAG_PHYS_DEST_ADDR);                              /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK */
  }
} /* IpV4_Ip_SetPhysDestAddr */

/**********************************************************************************************************************
 *  IpV4_Ip_SetEthIfFramePrio
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_SetEthIfFramePrio(
  TcpIp_SocketDynIterType IpV4SocketIdx,
  uint8                   Value)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(IpV4SocketIdx < TcpIp_GetSizeOfIpV4SocketDyn());
  /* #10 In case the given frame priority value is valid, store the value and indicate that frame priority is used. */
  if(Value <= IPV4_IP_MAX_ETHIF_FRAME_PRIO)
  {
    TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(IpV4SocketIdx)->EthIfFramePrio = Value;                                   /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK */
    TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(IpV4SocketIdx)->Flags |= IPV4_IP_TRANSFER_BLOCK_FLAG_ETHIF_FRAME_PRIO;    /* SBSW_TCPIP_WRITE_TRANSFER_BLOCK */
    retVal = E_OK;
  }
  /* else: Leave retVal at E_NOT_OK */
  return retVal;
} /* IpV4_Ip_SetEthIfFramePrio */

/**********************************************************************************************************************
 *  IpV4_Ip_AddrConflictInd
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
FUNC(void, IPV4_CODE) IpV4_Ip_AddrConflictInd(
  TcpIp_LocalAddrV4IterType LocalAddrV4Idx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfIpV4CtrlType ipV4CtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());
  TCPIP_ASSERT(TcpIp_IsUnicastAddrV4UsedOfLocalAddrV4(LocalAddrV4Idx) == TRUE);
  ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);

  /* #10 In case LINKLOCAL address assignment is configured for the given IP controller,
         check for an address conflict timeout and inform the upper layer if required */
  if (TcpIp_IsLlAddrStateUsedOfIpV4Ctrl(ipV4CtrlIdx) == TRUE)
  {
    /* check address conflict timeout */
    TcpIp_LlAddrStateIdxOfIpV4CtrlType llAddrStateIdx = TcpIp_GetLlAddrStateIdxOfIpV4Ctrl(ipV4CtrlIdx);

    TCPIP_ASSERT(IpV4_Ip_VCfgIsAddrAssignmentEnabled(ipV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL));

    /* #20 In case this is not the first conflict, release current local IP address assignment.
           Otherwise repeat ARP announcement */
    if(0u != TcpIp_GetAddrConflictTimeoutOfLlAddrState(llAddrStateIdx))
    {
      TcpIp_SetStateOfLlAddrState(llAddrStateIdx, IPV4_IP_LL_STATE_CONFLICT);                                           /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
      IpV4_Ip_VIpAddrAssignmentReadyNotification(ipV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL, FALSE);
    }
    else
    /* #30 Otherwise its the first conflict: In case AUTO IP is used for the given IP controller:
           Set up the conflict timeout and send an ARP announcement. */
    {
      TcpIp_AutoIpConfigIdxOfIpV4CtrlType autoIpConfigIdx;

      /* AutoIpConfig of IpV4Ctrl always exists if LlAddrState is present which is checked above. */
      TCPIP_ASSERT(TcpIp_IsAutoIpConfigUsedOfIpV4Ctrl(ipV4CtrlIdx) == TRUE);

      autoIpConfigIdx = TcpIp_GetAutoIpConfigIdxOfIpV4Ctrl(ipV4CtrlIdx);
      TcpIp_SetAddrConflictTimeoutOfLlAddrState(llAddrStateIdx,                                                         /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
        (TcpIp_AddrConflictTimeoutOfLlAddrStateType)(TcpIp_GetDefendIntervalMsOfAutoIpConfig(autoIpConfigIdx)
                                                      / TCPIP_MAIN_FCT_PERIOD_MSEC));

      /* Send ARP announcement */
      (void)IpV4_Arp_SendArpAnnouncement(ipV4CtrlIdx, TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(ipV4CtrlIdx));
    }
  }
} /* IpV4_Ip_AddrConflictInd */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_LlAddrInUse
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, IPV4_CODE) IpV4_Ip_LlAddrInUse(
    TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
    IpBase_AddrInType      IpAddr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_LlAddrStateIdxOfIpV4CtrlType llAddrStateIdx = TcpIp_GetLlAddrStateIdxOfIpV4Ctrl(IpV4CtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  IPV4_UNUSED_PARAMETER(IpV4CtrlIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Check for an address conflict and inform the upper layer if required */
  TCPIP_ASSERT(IpV4_Ip_VCfgIsAddrAssignmentEnabled(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL));
  TCPIP_ASSERT(TcpIp_IsLlAddrStateUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE);

  if(TcpIp_GetStateOfLlAddrState(llAddrStateIdx) == IPV4_IP_LL_STATE_PROBE)
  {
    if ((IpAddr != IPV4_ADDR_ANY) && (TcpIp_GetNetAddrCandOfLlAddrState(llAddrStateIdx) == IpAddr)) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    {
      TcpIp_SetAddrConflictOfLlAddrState(llAddrStateIdx, TRUE);                                                            /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
    }
  }
} /* IpV4_Ip_LlAddrInUse */

# if (TCPIP_SUPPORT_DEM == STD_ON)
/**********************************************************************************************************************
 *  IpV4_GetLastDuplicateDhcpAddrDid
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
FUNC(Std_ReturnType, IPV4_CODE) IpV4_GetLastDuplicateDhcpAddrDid(
  TcpIp_IpV4CtrlIterType                                   IpV4CtrlIdx,
  CONSTP2VAR(IpBase_AddrInType, AUTOMATIC, IPV4_APPL_DATA) IpAddrPtr,
  IPV4_P2V(uint8)                                          PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#  if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Check component initialization state and input parameters. */
  if(IpV4_State != IPV4_STATE_INIT)
  {
    errorId = IPV4_E_NOT_INITIALIZED;
  }
  /* Check parameter 'IpAddrPtr' */
  else if(IpAddrPtr == NULL_PTR)
  {
    errorId = IPV4_E_INV_POINTER;
  }
  /* Check parameter 'PhysAddrPtr' */
  else if(PhysAddrPtr == NULL_PTR)
  {
    errorId = IPV4_E_INV_POINTER;
  }
  /* Check parameter 'IpV4CtrlIdx' */
  else if(IpV4CtrlIdx >= TcpIp_GetSizeOfIpV4Ctrl())
  {
    errorId = IPV4_E_INV_PARAM;
  }
  else
#  endif
  /* #20 Set errorId to exit in case the given IpV4 controller is NOT configured for DEM events. */
  if(TcpIp_IsDemEventUsedOfIpV4Ctrl(IpV4CtrlIdx) == FALSE)
  {
    errorId = IPV4_E_INV_CONFIG;
  }
  /* #30 Duplicate DHCP address of controller can be read in case DEM event are configured (indicated by errorId). */
  else
  {
    TcpIp_DemEventIdxOfIpV4CtrlType demEventIdx = TcpIp_GetDemEventIdxOfIpV4Ctrl(IpV4CtrlIdx);
    /* #40 Duplicate DHCP address of controller can be read in case the particular DEM event is configured. */
    if(TcpIp_GetE_DUPLICATE_DHCP_ADDROfDemEvent(demEventIdx) == TCPIP_INV_DEM_ID)
    {
      errorId = IPV4_E_INV_CONFIG;
    }
    else
    {
      /* ----- Implementation ----------------------------------------------- */
      /* #50 Assign the last duplicate DHCP address DID to the C-structs given as out-parameters. */
      TcpIp_SizeOfLastDuplicateDhcpAddrType lastDuplicateDhcpAddrIdx =
        TcpIp_GetLastDuplicateDhcpAddrIdxOfDemEvent(demEventIdx);

      TCPIP_ASSERT(TcpIp_IsLastDuplicateDhcpAddrUsedOfDemEvent(demEventIdx) == TRUE);

      TcpIp_VCopyPhysAddr(PhysAddrPtr,                                                                                  /* SBSW_TCPIP_VALID_PTR_DET_CHECKED */
                          &TcpIp_GetAddrPhysAddrOfLastDuplicateDhcpAddr(lastDuplicateDhcpAddrIdx)->data[0]);
      *IpAddrPtr = TcpIp_GetNetAddrOfLastDuplicateDhcpAddr(lastDuplicateDhcpAddrIdx);                                   /* SBSW_TCPIP_VALID_PTR_DET_CHECKED */
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if(errorId != TCPIP_E_NO_ERROR)
  {
    (void)Det_ReportError(IPV4_MODULE_ID, IPV4_VINSTANCE_ID, IPV4_IP_API_ID_GET_LAST_DUPLICATE_DHCP_ADDR_DID, errorId);
  }
#  else
  TCPIP_DUMMY_STATEMENT(errorId);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif

  return retVal;
} /* IpV4_GetLastDuplicateDhcpAddrDid */ /* PRQA S 6050, 6080 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */
# endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#  if (TCPIP_SUPPORT_IP_ETHIF_ADDR_FILTER_API == STD_ON)
/**********************************************************************************************************************
 *  IpV4_Ip_VJoinMulticastGroup
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VJoinMulticastGroup(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IpBase_AddrInType      MulticastAddr,
  boolean                Join)
{
  /* ----- Local Variables ---------------------------------------------- */
  IpBase_EthPhysAddrType physMulticastAddr;
  Eth_FilterActionType   ethFilterAction = (Eth_FilterActionType)(  (TRUE == Join)
                                                                  ? ETH_ADD_TO_FILTER
                                                                  : ETH_REMOVE_FROM_FILTER);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case the given multicast address is valid:
         Configure the physical address filter according to the given Join flag. */
  if(IPV4_ADDR_IS_MULTICAST(MulticastAddr))
  {
    IpV4_Arp_MapIpToPhysMulticastAddr(MulticastAddr, &physMulticastAddr[0]);                                            /* SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER_OUT_PTR_PHYS_ADDR */

    if(TCPIP_LL_UpdatePhysAddrFilter(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx),                                      /* SBSW_TCPIP_FUNC_CALL_CSL01_IDX_CALLER_OUT_PTR_FROM_LOCAL_VAR */
                                     &physMulticastAddr[0],
                                     ethFilterAction) != E_OK)
    {
      IpV4_ReportDetError(IPV4_IP_API_ID_V_INTERNAL_FUNCTION, IPV4_E_INV_PARAM);
    }
  }
} /* IpV4_Ip_VJoinMulticastGroup */
#  endif

/**********************************************************************************************************************
 *  IpV4_Ip_VUpdateMulticastMemberships
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VUpdateMulticastMemberships(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  boolean                Join)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case a multicast address is used for the given IP controller:
         Join the configured multicast address groups. */
  if(TcpIp_IsMulticastAddrV4UsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    /* There is at least one multicast address configured for the given controller. */
    TcpIp_SizeOfMulticastAddrV4Type multicastAddrV4Idx;
    for(multicastAddrV4Idx = TcpIp_GetMulticastAddrV4StartIdxOfIpV4Ctrl(IpV4CtrlIdx);
        multicastAddrV4Idx < TcpIp_GetMulticastAddrV4EndIdxOfIpV4Ctrl(IpV4CtrlIdx);
        multicastAddrV4Idx++)
    {
      /* The MulticastAddrV4Requested array is generated the same size as the number of all configured Multicast addresses
         of all IpV4 controllers. Thus this array can be accessed using an index of an IpV4 MulticastAddr */
      if(TcpIp_GetNetAddrOfMulticastAddrV4Requested(multicastAddrV4Idx) != IPV4_ADDR_ANY)
      {
        TcpIp_IpAddrStateType AddrState = (TcpIp_IpAddrStateType)(   (TRUE == Join)
                                                                   ? TCPIP_IPADDR_STATE_ASSIGNED
                                                                   : TCPIP_IPADDR_STATE_UNASSIGNED);

#  if (TCPIP_SUPPORT_IP_ETHIF_ADDR_FILTER_API == STD_ON)
        if (TcpIp_IsReceiveAllMulticastsOfIpV4Ctrl(IpV4CtrlIdx) == FALSE)
        {
          /* configure individual physical address filter */
          IpV4_Ip_VJoinMulticastGroup(IpV4CtrlIdx,
                                      TcpIp_GetNetAddrOfMulticastAddrV4Requested(multicastAddrV4Idx),
                                      Join);
        }
#  endif

        IpV4_VLocalIpAddrAssignmentChange(TcpIp_GetLocalAddrV4IdxOfMulticastAddrV4(multicastAddrV4Idx), AddrState);
      }
    }
  }

#  if (TCPIP_SUPPORT_IP_ETHIF_ADDR_FILTER_API == STD_ON)
  /* #20 Update the EthIf's address filter if configured. */
  if (TcpIp_IsReceiveAllMulticastsOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    const Eth_PhysAddrType physBroadcastAddr = { 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU };
    Eth_FilterActionType ethFilterAction = (Eth_FilterActionType)(   (TRUE == Join)
                                                                   ? ETH_ADD_TO_FILTER
                                                                   : ETH_REMOVE_FROM_FILTER);

    /* #30 Enable the promiscuous mode to receive multicast messages. */
    if (TCPIP_LL_UpdatePhysAddrFilter(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx),                                     /* SBSW_TCPIP_FUNC_CALL_CSL01_IDX_CALLER_OUT_PTR_FROM_LOCAL_VAR */
                                     &physBroadcastAddr[0], ethFilterAction) != E_OK)
    {
      IpV4_ReportDetError(IPV4_IP_API_ID_V_INTERNAL_FUNCTION, IPV4_E_INV_PARAM);
    }
  }
#  endif
} /* IpV4_Ip_VUpdateMulticastMemberships */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_VGetBestAvailableAddrAssignment
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
IPV4_LOCAL_INLINE FUNC(TcpIp_IpAddrAssignmentType, IPV4_CODE) IpV4_Ip_VGetBestAvailableAddrAssignment(
  TcpIp_IpV4CtrlIterType       IpV4CtrlIdx,
  IPV4_P2V(IpV4_IpAddrSetType) AddrInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_AddrAssignmentCfgByPrioIterType addrAssignmentCfgByPrioIdx;
  TcpIp_IpAddrAssignmentType            addrAssignmentMethodReady = TCPIP_IPADDR_ASSIGNMENT_NONE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate configured address assignments for current controller (ordered by high to low priority). */
  for (addrAssignmentCfgByPrioIdx = TcpIp_GetAddrAssignmentCfgByPrioStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
       addrAssignmentCfgByPrioIdx < TcpIp_GetAddrAssignmentCfgByPrioEndIdxOfIpV4Ctrl(IpV4CtrlIdx);
       addrAssignmentCfgByPrioIdx++)
  {
    TcpIp_AddrAssignmentCfgByPrioType addrAssignmentCfg    = TcpIp_GetAddrAssignmentCfgByPrio(addrAssignmentCfgByPrioIdx);
    TcpIp_IpAddrAssignmentType        addrAssignmentMethod = IpV4_Ip_VCfgGetAddrAssignmentMethodByCfg(addrAssignmentCfg);

    /* Stop iteration if address assignment in state 'ready' is found or no more address assignments are configured. */
    if (   (addrAssignmentMethodReady != TCPIP_IPADDR_ASSIGNMENT_NONE)
        || (addrAssignmentMethod      == TCPIP_IPADDR_ASSIGNMENT_NONE))
    {
      break;
    }

    /* #20 Check if address assignment is active. */
    if (IPV4_CHK_BIT_U8(TcpIp_GetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(IpV4CtrlIdx), addrAssignmentMethod))
    {
# if (TCPIP_SUPPORT_IP_ADDR_NVM_STORAGE == STD_ON)
      /* #30 Check if an address is stored into NvM for this assignment method. If so, use it. */
      if (IPV4_CHK_FLAG_U8(addrAssignmentCfg, TCPIP_IPV4_ADDR_ASSIGNMENT_FLAG_LIFETIME_STORE))
      {
        IPV4_P2V(IpV4_IpAddrSetType) ipAddrSetPtr = NULL_PTR;
        /* #40 Continue only in case the address set in NvM of this IpV4 controller can be accessed */
        if (IpV4_Ip_NvmGetAddrSet(IpV4CtrlIdx, &ipAddrSetPtr, FALSE) == E_OK)                                           /* SBSW_TCPIP_FUNC_CALL_CSL01_IDX_CALLER_OUT_PTR_FROM_LOCAL_VAR */
        {
          /* #50 In case the address stored in NvM is valid, return it to the caller */
          if (   (ipAddrSetPtr->NetAddr != IPV4_ADDR_ANY)
              && (ipAddrSetPtr->NetMask > 0u))
          {
            /* Use address stored in NvM. */
            addrAssignmentMethodReady = addrAssignmentMethod;
            *AddrInfoPtr = *ipAddrSetPtr;                                                                               /* SBSW_TCPIP_VALID_PTR_CALLER */
          }
        }
      }

      if (addrAssignmentMethodReady == TCPIP_IPADDR_ASSIGNMENT_NONE)
# endif
      {
        if (IpV4_Ip_VGetActiveAddressOfAssignmentMethod(IpV4CtrlIdx, addrAssignmentMethod, AddrInfoPtr) == TRUE)        /* SBSW_TCPIP_FUNC_CALL_VALID_PTR_CALLER */
        {
          addrAssignmentMethodReady = addrAssignmentMethod;
        }
      }
    }
  }

  return addrAssignmentMethodReady;
} /* IpV4_Ip_VGetBestAvailableAddrAssignment */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV4_Ip_VGetActiveAddressOfAssignmentMethod()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(boolean, IPV4_CODE) IpV4_Ip_VGetActiveAddressOfAssignmentMethod(
  TcpIp_IpV4CtrlIterType       IpV4CtrlIdx,
  TcpIp_IpAddrAssignmentType   AddrAssignmentMethod,
  IPV4_P2V(IpV4_IpAddrSetType) AddrInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if specified address assignment method has a valid address and store value in AddrInfoPtr. */
  switch(AddrAssignmentMethod)
  {
# if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
  case TCPIP_IPADDR_ASSIGNMENT_DHCP:
    if(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    {
      TCPIP_ASSERT(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE);
      TCPIP_ASSERT(IpV4_Ip_VCfgIsAddrAssignmentEnabled(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP));

      retVal = TcpIp_DhcpV4_GetActiveAddress(IpV4CtrlIdx, AddrInfoPtr);                                                 /* SBSW_TCPIP_FUNC_CALL_VALID_PTR_CALLER */
    }
    break;
# endif

  case TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL:
    {
      /* #20 For LINKLOCAL assignment only store the value in case the state is announce or ready. */
      TcpIp_LlAddrStateIdxOfIpV4CtrlType llAddrStateIdx = TcpIp_GetLlAddrStateIdxOfIpV4Ctrl(IpV4CtrlIdx);
      if (   (TcpIp_GetStateOfLlAddrState(llAddrStateIdx) == IPV4_IP_LL_STATE_ANNOUNCE) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          || (TcpIp_GetStateOfLlAddrState(llAddrStateIdx) == IPV4_IP_LL_STATE_READY))
      {
        AddrInfoPtr->NetAddr = TcpIp_GetAddrFoundOfLlAddrState(llAddrStateIdx);                                         /* SBSW_TCPIP_VALID_PTR_CALLER */
        AddrInfoPtr->NetMask = IPV4_IP_LL_NET_ADDR_MASK;                                                                /* SBSW_TCPIP_VALID_PTR_CALLER */
        AddrInfoPtr->DefGwAddr = TCPIP_INADDR_ANY;                                                                      /* SBSW_TCPIP_VALID_PTR_CALLER */
        retVal = TRUE;
      }
    }
    break;

  case TCPIP_IPADDR_ASSIGNMENT_STATIC:
  {
    TcpIp_SizeOfUnicastAddrV4Type unicastAddrV4Idx = TcpIp_GetUnicastAddrV4IdxOfIpV4Ctrl(IpV4CtrlIdx);
    TcpIp_SizeOfStaticUnicastAddrV4RequestedType staticUnicastAddrV4RequestedIdx;

    TCPIP_ASSERT(TcpIp_IsStaticUnicastAddrV4RequestedUsedOfUnicastAddrV4(unicastAddrV4Idx) == TRUE);

    staticUnicastAddrV4RequestedIdx = TcpIp_GetStaticUnicastAddrV4RequestedIdxOfUnicastAddrV4(unicastAddrV4Idx);

    TCPIP_ASSERT(IPV4_CHK_BIT_U8(TcpIp_GetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(IpV4CtrlIdx), TCPIP_IPADDR_ASSIGNMENT_STATIC));
    TCPIP_ASSERT(TcpIp_GetNetAddrOfStaticUnicastAddrV4Requested(staticUnicastAddrV4RequestedIdx) != IPV4_ADDR_ANY);

    /* #30 For static assignment only store the value in case the address is requested. */
    AddrInfoPtr->NetAddr   = TcpIp_GetNetAddrOfStaticUnicastAddrV4Requested(staticUnicastAddrV4RequestedIdx);           /* SBSW_TCPIP_VALID_PTR_CALLER */
    AddrInfoPtr->NetMask   = TcpIp_GetNetMaskOfStaticUnicastAddrV4Requested(staticUnicastAddrV4RequestedIdx);           /* SBSW_TCPIP_VALID_PTR_CALLER */
    AddrInfoPtr->DefGwAddr = TcpIp_GetDefGwAddrOfStaticUnicastAddrV4Requested(staticUnicastAddrV4RequestedIdx);         /* SBSW_TCPIP_VALID_PTR_CALLER */
    retVal = TRUE;
    break;
  }

  default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    /* Default case left blank intentionally */
    TCPIP_ASSERT_UNREACHABLE();
    break;
  }

  return retVal;
} /* IpV4_Ip_VGetActiveAddressOfAssignmentMethod */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_VEnableAddrAssignmentMethod()
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
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_VEnableAddrAssignmentMethod(
  TcpIp_IpV4CtrlIterType            IpV4CtrlIdx,
  TcpIp_IpAddrAssignmentType        AddrAssignmentMethod,
  TcpIp_AddrAssignmentCfgByPrioType AddrAssignmentCfg)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  if(!IPV4_CHK_BIT_U8(TcpIp_GetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(IpV4CtrlIdx), AddrAssignmentMethod))
  {
    TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDynType addrAssignmentTriggeredFlagsOfIpV4CtrlDyn =
      TcpIp_GetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(IpV4CtrlIdx);
    IPV4_SET_BIT_U8(addrAssignmentTriggeredFlagsOfIpV4CtrlDyn, AddrAssignmentMethod);
    TcpIp_SetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(IpV4CtrlIdx, addrAssignmentTriggeredFlagsOfIpV4CtrlDyn);         /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */

    {
# if (TCPIP_SUPPORT_IP_ADDR_NVM_STORAGE == STD_ON)
      /* #10 In case an address of this method was stored in the NvM before:
             Do not trigger dynamic address assignment (DHCP, LINKLOCAL). */
      boolean triggerAssignment = TRUE;

      if(IPV4_CHK_FLAG_U8(AddrAssignmentCfg, TCPIP_IPV4_ADDR_ASSIGNMENT_FLAG_LIFETIME_STORE))
      {
        IPV4_P2V(IpV4_IpAddrSetType) ipAddrSetPtr = NULL_PTR;

        /* #20 Continue only in case the address set in NvM of this IpV4 controller can be accessed */
        if(IpV4_Ip_NvmGetAddrSet(IpV4CtrlIdx, &ipAddrSetPtr, FALSE) == E_OK)                                            /* SBSW_TCPIP_FUNC_CALL_CSL01_IDX_CALLER_OUT_PTR_FROM_LOCAL_VAR */
        {
          /* #30 In case an address stored in NvM: Prevent start of dynamic address assignment, below. */
          if(ipAddrSetPtr->NetAddr != IPV4_ADDR_ANY)
          {
            triggerAssignment = FALSE;
            /* No need to trigger Address assignment if address is available in NvM */
            retVal = E_OK;
          }
        }
      }

      /* #40 Otherwise start dynamic address assignment method (explicit start only in case of DHCP or LINKLOCAL). */
      if(triggerAssignment == TRUE)
# else
      IPV4_UNUSED_PARAMETER(AddrAssignmentCfg);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
      {
        switch (AddrAssignmentMethod)
        {
# if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
        case TCPIP_IPADDR_ASSIGNMENT_DHCP:
          if (TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          {
            TCPIP_ASSERT(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE);
            TCPIP_ASSERT(IpV4_Ip_VCfgIsAddrAssignmentEnabled(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP));

            TcpIp_DhcpV4_TriggerAddrRequest(IpV4CtrlIdx);
            retVal = E_OK;
          }
          break;
# endif
        case TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL:
          if (TcpIp_IsLlAddrStateUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
          {
            IpV4_Ip_VLl_Start(TcpIp_GetLlAddrStateIdxOfIpV4Ctrl(IpV4CtrlIdx));
            retVal = E_OK;
          }
          break;

        case TCPIP_IPADDR_ASSIGNMENT_STATIC:
          retVal = E_OK;
          break;

        default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
          /* Default case left blank intentionally */
          /* No action required. */
          TCPIP_ASSERT_UNREACHABLE();
          break;
        }
      }
    }
  }
  /* else: Trigger already set. */
  return retVal;
} /* IpV4_Ip_VEnableAddrAssignmentMethod */ /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_VDisableAddrAssignmentMethod()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_VDisableAddrAssignmentMethod(
  TcpIp_IpV4CtrlIterType     IpV4CtrlIdx,
  TcpIp_IpAddrAssignmentType AddrAssignmentMethod)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  if(IPV4_CHK_BIT_U8(TcpIp_GetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(IpV4CtrlIdx), AddrAssignmentMethod))
  {
    TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDynType addrAssignmentTriggeredFlagsOfIpV4CtrlDyn =
      TcpIp_GetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(IpV4CtrlIdx);
    IPV4_CLR_BIT_U8(addrAssignmentTriggeredFlagsOfIpV4CtrlDyn, AddrAssignmentMethod);
    TcpIp_SetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(IpV4CtrlIdx, addrAssignmentTriggeredFlagsOfIpV4CtrlDyn);         /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */

    /* #10 Stop dynamic address assignment method (explicit stop only in case of DHCP or LINKLOCAL). */
    switch (AddrAssignmentMethod)
    {
# if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
    case TCPIP_IPADDR_ASSIGNMENT_DHCP:
      TcpIp_DhcpV4_StopAddrRequest(IpV4CtrlIdx);
      retVal = E_OK;
      break;
# endif

    case TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL:
      if (TcpIp_GetLlAddrStateIdxOfIpV4Ctrl(IpV4CtrlIdx) != TCPIP_NO_LLADDRSTATEIDXOFIPV4CTRL)
      {
        IpV4_Ip_VLl_Reset(TcpIp_GetLlAddrStateIdxOfIpV4Ctrl(IpV4CtrlIdx));
        retVal = E_OK;
      }
      break;

    case TCPIP_IPADDR_ASSIGNMENT_STATIC:
      retVal = E_OK;
      break;

    default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
      /* Default case left blank intentionally */
      /* No action required. */
      TCPIP_ASSERT_UNREACHABLE();
      break;
    }
  }
  else
  {
    /* Trigger already unset. */
  }
  return retVal;
} /* IpV4_Ip_VDisableAddrAssignmentMethod */

/**********************************************************************************************************************
 *  IpV4_Ip_VTriggerAddrAssignment
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) IpV4_Ip_VTriggerAddrAssignment(
  TcpIp_IpV4CtrlIterType            IpV4CtrlIdx,
  TcpIp_AddrAssignmentCfgByPrioType AddrAssignmentCfg,
  boolean                           TriggerValue)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  TcpIp_IpAddrAssignmentType addrAssignmentMethod = IpV4_Ip_VCfgGetAddrAssignmentMethodByCfg(AddrAssignmentCfg);

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT((addrAssignmentMethod == TCPIP_IPADDR_ASSIGNMENT_DHCP) ||
               (addrAssignmentMethod == TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL) ||
               (addrAssignmentMethod == TCPIP_IPADDR_ASSIGNMENT_STATIC));

  /* #10 Update enable state according to the given trigger value */
  if (TriggerValue == TRUE)
  {
    retVal = IpV4_Ip_VEnableAddrAssignmentMethod(IpV4CtrlIdx, addrAssignmentMethod, AddrAssignmentCfg);
  }
  else
  {
    retVal = IpV4_Ip_VDisableAddrAssignmentMethod(IpV4CtrlIdx, addrAssignmentMethod);
  }

  return retVal;
} /* IpV4_Ip_VTriggerAddrAssignment */

/**********************************************************************************************************************
 *  IpV4_Ip_VTriggerAutomaticAddrAssignments()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VTriggerAutomaticAddrAssignments(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_AddrAssignmentCfgByPrioStartIdxOfIpV4CtrlType addrAssignmentCfgByPrioIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate configured address assignments for current controller (ordered by high to low priority). */
  for (addrAssignmentCfgByPrioIdx = TcpIp_GetAddrAssignmentCfgByPrioStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
       addrAssignmentCfgByPrioIdx < TcpIp_GetAddrAssignmentCfgByPrioEndIdxOfIpV4Ctrl(IpV4CtrlIdx);
       addrAssignmentCfgByPrioIdx++)
  {
    TcpIp_AddrAssignmentCfgByPrioType addrAssignmentCfg    = TcpIp_GetAddrAssignmentCfgByPrio(addrAssignmentCfgByPrioIdx);
    TcpIp_IpAddrAssignmentType        addrAssignmentMethod = IpV4_Ip_VCfgGetAddrAssignmentMethodByCfg(addrAssignmentCfg);

    /* #20 If assignment method trigger is configured to AUTOMATIC set trigger flag. */
    if (   (addrAssignmentMethod != TCPIP_IPADDR_ASSIGNMENT_NONE)
        && ((addrAssignmentCfg & TCPIP_IPV4_ADDR_ASSIGNMENT_FLAG_AUTO_TRIGGER) != 0u))
    {
      Std_ReturnType triggerAddrAssignmentRetVal = IpV4_Ip_VTriggerAddrAssignment(IpV4CtrlIdx, addrAssignmentCfg, TRUE);

      TCPIP_ASSERT(triggerAddrAssignmentRetVal == E_OK);
      TCPIP_DUMMY_STATEMENT(triggerAddrAssignmentRetVal);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

      /* #30 In case assignment method is STATIC:
             Set active address of assignment to configured default address (if there is one). */
      if(addrAssignmentMethod == TCPIP_IPADDR_ASSIGNMENT_STATIC)
      {
        TcpIp_UnicastAddrV4IdxOfIpV4CtrlType             unicastAddrV4Idx;
        TcpIp_SizeOfStaticUnicastAddrV4RequestedType     staticUnicastAddrV4RequestedIdx;
        TcpIp_DefaultUnicastAddrV4IdxOfUnicastAddrV4Type defaultUnicastAddrV4Idx;

        unicastAddrV4Idx = TcpIp_GetUnicastAddrV4IdxOfIpV4Ctrl(IpV4CtrlIdx);

        /* A unicast address with Method == STATIC and Trigger == AUTOMATIC always has a requested and a default value. */

        staticUnicastAddrV4RequestedIdx = TcpIp_GetStaticUnicastAddrV4RequestedIdxOfUnicastAddrV4(unicastAddrV4Idx);
        TCPIP_ASSERT(staticUnicastAddrV4RequestedIdx < TcpIp_GetSizeOfStaticUnicastAddrV4Requested());

        defaultUnicastAddrV4Idx  = TcpIp_GetDefaultUnicastAddrV4IdxOfUnicastAddrV4(unicastAddrV4Idx);
        TCPIP_ASSERT(defaultUnicastAddrV4Idx < TcpIp_GetSizeOfDefaultUnicastAddrV4());

        TcpIp_SetNetAddrOfStaticUnicastAddrV4Requested(staticUnicastAddrV4RequestedIdx,                                 /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
          TcpIp_GetNetAddrOfDefaultUnicastAddrV4(defaultUnicastAddrV4Idx));
        TcpIp_SetNetMaskOfStaticUnicastAddrV4Requested(staticUnicastAddrV4RequestedIdx,                                 /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
          TcpIp_GetNetMaskOfDefaultUnicastAddrV4(defaultUnicastAddrV4Idx));
        TcpIp_SetDefGwAddrOfStaticUnicastAddrV4Requested(staticUnicastAddrV4RequestedIdx,                               /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
          TcpIp_GetDefGwAddrOfDefaultUnicastAddrV4(defaultUnicastAddrV4Idx));
      }
    }
  }
} /* IpV4_Ip_VTriggerAutomaticAddrAssignments */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_VSetCtrlStateOffline()
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
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VSetCtrlStateOffline(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If IP instance is in state ONLINE_ACTIVE move to ONLINE_PASSIVE first. */
  if(TcpIp_GetStateOfIpV4CtrlDyn(IpV4CtrlIdx) == IPV4_IP_ONLINE_ACTIVE)
  {
    IpV4_Ip_VSetCtrlStateOnlinePassive(IpV4CtrlIdx);
  }

  if(TcpIp_GetStateOfIpV4CtrlDyn(IpV4CtrlIdx) == IPV4_IP_ONLINE_PASSIVE)
  {
    /* #20 If IP instance is in state ONLINE_PASSIVE stop all dynamic address assignments. */
    (void)IpV4_Ip_VTriggerAddrAssignment(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP, FALSE);
    (void)IpV4_Ip_VTriggerAddrAssignment(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL, FALSE);

    /* #30 Clear address assignment trigger flags for all address assignment methods of the IP instance. */
    TcpIp_SetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(IpV4CtrlIdx, 0);                                                 /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */

    /* #40 Reset ARP submodule. */
    IpV4_Arp_Reset(IpV4CtrlIdx);

    /* #50 Reset all multicast addresses to default values. */
    if (TcpIp_IsMulticastAddrV4UsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
    {
      TcpIp_MulticastAddrV4IterType multicastAddrV4Idx;

      for (multicastAddrV4Idx = TcpIp_GetMulticastAddrV4StartIdxOfIpV4Ctrl(IpV4CtrlIdx);
           multicastAddrV4Idx < TcpIp_GetMulticastAddrV4EndIdxOfIpV4Ctrl(IpV4CtrlIdx);
           multicastAddrV4Idx++)
      {
        TcpIp_SizeOfDefaultMulticastAddrV4Type defaultMulticastAddrV4Idx =
          TcpIp_GetDefaultMulticastAddrV4IdxOfMulticastAddrV4(multicastAddrV4Idx);
        TcpIp_SetNetAddrOfMulticastAddrV4Requested(multicastAddrV4Idx,                                                  /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
          TcpIp_GetNetAddrOfDefaultMulticastAddrV4(defaultMulticastAddrV4Idx));
      }
    }

    /* #60 Set state to OFFLINE. */
    TcpIp_SetStateOfIpV4CtrlDyn(IpV4CtrlIdx, IPV4_IP_OFFLINE);                                                          /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
  }
  else
  {
    /* Invalid state transition. */
    TCPIP_ASSERT_UNREACHABLE();
  }
} /* IpV4_Ip_VSetCtrlStateOffline */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_VSetCtrlStateOnlinePassive()
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
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VSetCtrlStateOnlinePassive(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If IP instance is in state ONLINE_ACTIVE: */
  if(TcpIp_GetStateOfIpV4CtrlDyn(IpV4CtrlIdx) == IPV4_IP_ONLINE_ACTIVE)
  {
    /* #20 Leave all multicast groups (if reception of multicast packets is configured.) */
    if (   (TcpIp_GetMulticastAddrV4EndIdxOfIpV4Ctrl(IpV4CtrlIdx) != TCPIP_NO_MULTICASTADDRV4ENDIDXOFIPV4CTRL)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        || (TcpIp_IsReceiveAllMulticastsOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))
    {
      /* update physical address filters */
      IpV4_Ip_VUpdateMulticastMemberships(IpV4CtrlIdx, FALSE);
    }

    /* #30 Unassign broadcast address. */

    IpV4_VLocalIpAddrAssignmentChange(TcpIp_GetLocalAddrV4BroadcastIdxOfIpV4Ctrl(IpV4CtrlIdx),
                                        TCPIP_IPADDR_STATE_UNASSIGNED);

    TCPIP_ASSERT(TcpIp_GetActiveAddrAssignmentMethodOfIpV4CtrlDyn(IpV4CtrlIdx) != TCPIP_IPADDR_ASSIGNMENT_NONE);

    /* #40 Unassign unicast address. */
    IpV4_VLocalIpAddrAssignmentChange(TcpIp_GetLocalAddrV4UnicastIdxOfIpV4Ctrl(IpV4CtrlIdx),
                                      TCPIP_IPADDR_STATE_UNASSIGNED);

    /* #50 Set IP instance state to PASSIVE and active assignment method to NONE. */
    TcpIp_SetStateOfIpV4CtrlDyn(IpV4CtrlIdx, IPV4_IP_ONLINE_PASSIVE);                                                   /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
    TcpIp_SetActiveNetAddrOfIpV4CtrlDyn(IpV4CtrlIdx, IPV4_ADDR_ANY);                                                    /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
    TcpIp_SetActiveNetMaskOfIpV4CtrlDyn(IpV4CtrlIdx, 0);                                                                /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
    TcpIp_SetActiveDefGwAddrOfIpV4CtrlDyn(IpV4CtrlIdx, IPV4_ADDR_ANY);                                                  /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
    TcpIp_SetActiveAddrAssignmentMethodOfIpV4CtrlDyn(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_NONE);                        /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */

    /* #60 Notify TcpIp/EthSM. */
    ETHSM_TCPIP_MODE_INDICATION(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), FALSE);
  }
  /* #70 If IP instance is in state OFFLINE: */
  else if (TcpIp_GetStateOfIpV4CtrlDyn(IpV4CtrlIdx) == IPV4_IP_OFFLINE)
  {
    TCPIP_ASSERT(TcpIp_GetActiveAddrAssignmentMethodOfIpV4CtrlDyn(IpV4CtrlIdx) == TCPIP_IPADDR_ASSIGNMENT_NONE);

    /* #80 Trigger all configured address assignments with trigger AUTOMATIC. */
    IpV4_Ip_VTriggerAutomaticAddrAssignments(IpV4CtrlIdx);

    /* #90 Set IP instance state to ONLINE_PASSIVE. */
    TcpIp_SetStateOfIpV4CtrlDyn(IpV4CtrlIdx, IPV4_IP_ONLINE_PASSIVE);                                                   /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */
  }
  else
  {
    /* ERROR: Invalid state transition. */
    TCPIP_ASSERT_UNREACHABLE();
  }
} /* IpV4_Ip_VSetCtrlStateOnlinePassive */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_VSetCtrlStateOnlineActive()
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
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VSetCtrlStateOnlineActive(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If IP instance is in state ONLINE_PASSIVE. */
  if(TcpIp_GetStateOfIpV4CtrlDyn(IpV4CtrlIdx) == IPV4_IP_ONLINE_PASSIVE)
  {
    /* #20 Set IP instance state to ONLINE_ACTIVE. */
    TcpIp_SetStateOfIpV4CtrlDyn(IpV4CtrlIdx, IPV4_IP_ONLINE_ACTIVE);                                                    /* SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER */

    TCPIP_ASSERT(TcpIp_GetActiveAddrAssignmentMethodOfIpV4CtrlDyn(IpV4CtrlIdx) != TCPIP_IPADDR_ASSIGNMENT_NONE);

    /* #30 Notify upper layer about available unicast address. */
    IpV4_VLocalIpAddrAssignmentChange(TcpIp_GetLocalAddrV4UnicastIdxOfIpV4Ctrl(IpV4CtrlIdx),
                                      TCPIP_IPADDR_STATE_ASSIGNED);

    /* #40 Notify upper layer about available broadcast address. */

    IpV4_VLocalIpAddrAssignmentChange(TcpIp_GetLocalAddrV4BroadcastIdxOfIpV4Ctrl(IpV4CtrlIdx),
                                        TCPIP_IPADDR_STATE_ASSIGNED);

    /* #50 Join multicast groups. (if reception of multicast packets is configured.) */
    if (    (TcpIp_IsMulticastAddrV4UsedOfIpV4Ctrl(IpV4CtrlIdx)  == TRUE)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
         || (TcpIp_IsReceiveAllMulticastsOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))
    {
      /* update physical address filters */
      IpV4_Ip_VUpdateMulticastMemberships(IpV4CtrlIdx, TRUE);
    }

    /* #60 Notify TcpIp/EthSM. */
    ETHSM_TCPIP_MODE_INDICATION(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), TRUE);
  }
  else
  {
    /* ERROR: Invalid state transition. */
    TCPIP_ASSERT_UNREACHABLE();
  }
} /* IpV4_Ip_VSetCtrlStateOnlineActive */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_VLocalIpAddrAssignmentChange()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_VLocalIpAddrAssignmentChange(
  TcpIp_LocalAddrV4IterType LocalAddrV4Idx,
  TcpIp_IpAddrStateType     State)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
# if (TCPIP_SUPPORT_ICMPV4 == STD_ON)                                                                                   /* COV_TCPIP_ICMPV4_ALWAYS_ON */
  /* #10 Inform the ICMPv4 about the address assignment change in case it is configured. */
  IpV4_Icmp_VLocalIpAddrAssignmentChange((TcpIp_SizeOfLocalAddrV4Type)LocalAddrV4Idx, State);
# endif
  /* #20 Inform everybody else about the address assignment change. */
  TcpIp_Cbk_VLocalIpAssignmentChg((TcpIp_SizeOfLocalAddrType)TCPIP_IPV4_TO_LOCAL_ADDR_IDX(LocalAddrV4Idx), State);
} /* IpV4_VLocalIpAddrAssignmentChange */

/**********************************************************************************************************************
 *  IpV4_Ip_VChangeMulticastAddrAssignment
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
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) IpV4_Ip_VChangeMulticastAddrAssignment(
  TcpIp_LocalAddrV4IterType LocalAddrV4Idx,
  IpBase_AddrInType         NetAddr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  IpBase_AddrInType prevMcNetAddr;
  TcpIp_SizeOfMulticastAddrV4Type multicastAddrV4Idx;
  TcpIp_SizeOfIpV4CtrlType ipV4CtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());
  TCPIP_ASSERT(TcpIp_IsMulticastAddrV4UsedOfLocalAddrV4(LocalAddrV4Idx) == TRUE);

  ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);
  multicastAddrV4Idx = TcpIp_GetMulticastAddrV4IdxOfLocalAddrV4(LocalAddrV4Idx);

  /* #10 Check if address value differs from current value. */
  prevMcNetAddr = TcpIp_GetNetAddrOfMulticastAddrV4Requested(multicastAddrV4Idx);
  if(prevMcNetAddr != NetAddr)
  {
    /* #20 Check if address value is a valid multicast address or ANY (in order remove address assignment). */
    if(IPV4_ADDR_IS_MULTICAST(NetAddr) || IPV4_ADDR_IS_BROADCAST(ipV4CtrlIdx, NetAddr) || (NetAddr == IPV4_ADDR_ANY))
    {
      /* #30 Leave multicast group if an address is currently assigned. */
      if(prevMcNetAddr != IPV4_ADDR_ANY)
      {
#  if (TCPIP_SUPPORT_IP_ETHIF_ADDR_FILTER_API == STD_ON)
        /* leave current multicast group */
        if (TcpIp_IsReceiveAllMulticastsOfIpV4Ctrl(ipV4CtrlIdx) == FALSE)
        {
          IpV4_Ip_VJoinMulticastGroup(ipV4CtrlIdx, prevMcNetAddr, FALSE);
        }
#  endif
        IpV4_VLocalIpAddrAssignmentChange(LocalAddrV4Idx, TCPIP_IPADDR_STATE_UNASSIGNED);
      }

      /* #40 Update address value. */
      if(NetAddr != IPV4_ADDR_ANY)
      {
        /* update multicast address assignment */
        TcpIp_SetNetAddrOfMulticastAddrV4Requested(multicastAddrV4Idx, NetAddr);                                        /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
      }
      else
      {
        /* set configured default address value. */
        TcpIp_SizeOfDefaultMulticastAddrV4Type defaultMulticastAddrV4Idx =
          TcpIp_GetDefaultMulticastAddrV4IdxOfMulticastAddrV4(multicastAddrV4Idx);

        TcpIp_SetNetAddrOfMulticastAddrV4Requested(multicastAddrV4Idx,                                                  /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
                                                   TcpIp_GetNetAddrOfDefaultMulticastAddrV4(defaultMulticastAddrV4Idx));
      }

      /* #50 Join multicast group if a new address was assigned. */
      if(TcpIp_GetNetAddrOfMulticastAddrV4Requested(multicastAddrV4Idx) != IPV4_ADDR_ANY)
      {
#  if (TCPIP_SUPPORT_IP_ETHIF_ADDR_FILTER_API == STD_ON)
        /* join new multicast group */
        if (TcpIp_IsReceiveAllMulticastsOfIpV4Ctrl(ipV4CtrlIdx) == FALSE)
        {
          IpV4_Ip_VJoinMulticastGroup(ipV4CtrlIdx, TcpIp_GetNetAddrOfMulticastAddrV4Requested(multicastAddrV4Idx), TRUE);
        }
#  endif

        IpV4_VLocalIpAddrAssignmentChange(LocalAddrV4Idx, TCPIP_IPADDR_STATE_ASSIGNED);
      }

      retVal = E_OK;
    }
    else
    {
      /* address is not a valid multicast or broadcast */
    }
  }

  return retVal;
} /* IpV4_Ip_VChangeMulticastAddrAssignment */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_GenerateIpAddr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) IpV4_Ip_VLl_GenerateIpAddr(
  TcpIp_IpV4CtrlIterType              IpV4CtrlIdx,
  TcpIp_ConflictsNumOfLlAddrStateType ConflictCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Initialize IP address value to 0.0.0.0. */
  IpBase_AddrInType                         ipAddr                = IPV4_ADDR_ANY;
  IpV4_LinkLocalAddrCalloutFuncType         addrCalloutFunc       = NULL_PTR;
  TcpIp_LocalAddrV4UnicastIdxOfIpV4CtrlType localAddrV4UnicastIdx = TcpIp_GetLocalAddrV4UnicastIdxOfIpV4Ctrl(IpV4CtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  if(TcpIp_IsAutoIpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    TcpIp_AutoIpConfigIdxOfIpV4CtrlType autoIpConfigIdx = TcpIp_GetAutoIpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
    addrCalloutFunc = TcpIp_GetAddrCalloutFuncOfAutoIpConfig(autoIpConfigIdx);
  }

  /* #20 If configured, call user callout function for IP address generation. */
  if(addrCalloutFunc != NULL_PTR)
  {
    addrCalloutFunc(TCPIP_LOCAL_ADDR_IDX_TO_ID(localAddrV4UnicastIdx), (uint8)ConflictCount, &ipAddr);                  /* SBSW_TCPIP_FUNC_CALL_ADDR_CALLOUT */
  }

  /* #30 If callout does not specify IP address, generate random address in link-local subnet (169.254.1.0) */
  if(ipAddr == IPV4_ADDR_ANY)
  {
    ipAddr = IPV4_IP_LL_NET_ADDR_START_NBO + ((uint32) TcpIp_GetRandomNumber() % IPV4_IP_LL_NET_ADDR_COUNT);                     /* SBSW_TCPIP_RANDOM_NUMBER_FUNC */
  }

  return TCPIP_NTOHL(ipAddr);
} /* IpV4_Ip_VLl_GenerateIpAddr */

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_Reset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_Reset(
  TcpIp_LlAddrStateIdxOfIpV4CtrlType LlAddrStateIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset all link local address state specific variables. */
  TcpIp_SetAddrConflictOfLlAddrState(LlAddrStateIdx, FALSE);                                                            /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
  TcpIp_SetAddrFoundOfLlAddrState(LlAddrStateIdx, 0);                                                                   /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
  TcpIp_SetNetAddrCandOfLlAddrState(LlAddrStateIdx, 0);                                                                 /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
  TcpIp_SetMsecCntOfLlAddrState(LlAddrStateIdx, 0);                                                                     /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
  TcpIp_SetProbeNumSinceConfOfLlAddrState(LlAddrStateIdx, 0);                                                           /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
  TcpIp_SetAnnounceNumOfLlAddrState(LlAddrStateIdx, 0);                                                                 /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
  TcpIp_SetConflictsNumOfLlAddrState(LlAddrStateIdx, 0);                                                                /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */

  TcpIp_SetStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_STATE_INACTIVE);                                               /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
  TcpIp_SetProbeStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_PROBE_STATE_CHOOSE);                                      /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
  TcpIp_SetAnnStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_ANN_STATE_PROBE);                                           /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */

  TcpIp_SetWaitUntilTimeOfLlAddrState(LlAddrStateIdx, 0);                                                               /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
} /* IpV4_Ip_VLl_Reset */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_Start
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_Start(
  TcpIp_LlAddrStateIdxOfIpV4CtrlType LlAddrStateIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Start LINKLOCAL address assignment if not already started. */
  if(TcpIp_GetStateOfLlAddrState(LlAddrStateIdx) == IPV4_IP_LL_STATE_INACTIVE)
  {
    TcpIp_SetStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_STATE_INIT);                                                 /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
  }
  else
  {
    TCPIP_ASSERT_UNREACHABLE();
  }
} /* IpV4_Ip_VLl_Start */

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_Main
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_Main(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Retrieve the LINKLOCAL address index of the given IP controller and handle LINKLOCAL address assignment. */
  TcpIp_LlAddrStateIdxOfIpV4CtrlType llAddrStateIdx = TcpIp_GetLlAddrStateIdxOfIpV4Ctrl(IpV4CtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(llAddrStateIdx != TCPIP_NO_LLADDRSTATEIDXOFIPV4CTRL);

  if(TcpIp_GetStateOfLlAddrState(llAddrStateIdx) != IPV4_IP_LL_STATE_INACTIVE)
  {
    if(TcpIp_GetAddrConflictTimeoutOfLlAddrState(llAddrStateIdx) > 0u)
    {
      /* decrease address conflict timeout */
      TcpIp_DecAddrConflictTimeoutOfLlAddrState(llAddrStateIdx);                                                        /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
    }

    /* No address has been configured or there are pending announcements for a link-local address */
    IpV4_Ip_VLl_FindAddr(IpV4CtrlIdx);
  }
  else
  {
  }
} /* IpV4_Ip_VLl_Main */

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_HandleStateProbe
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
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_HandleStateProbe(
  TcpIp_IpV4CtrlIterType              IpV4CtrlIdx,
  TcpIp_LlAddrStateIdxOfIpV4CtrlType  LlAddrStateIdx,
  TcpIp_AutoIpConfigIdxOfIpV4CtrlType AutoIpConfigIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case conflicts have occurred in state PROBE, change state to CONFLICT. */
  if(TcpIp_IsAddrConflictOfLlAddrState(LlAddrStateIdx) == TRUE)
  {
    /* goto conflict */
    TcpIp_SetStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_STATE_CONFLICT);                                             /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
  }
  else
  /* #20 Otherwise process the sub-state related to the state PROBE. */
  {
    /* #30 Generate and set a new address candidate when substate is CHOOSE and then change to substate PROBE */
    if(TcpIp_GetProbeStateOfLlAddrState(LlAddrStateIdx) == IPV4_IP_LL_PROBE_STATE_CHOOSE)
    {
      TcpIp_SetNetAddrCandOfLlAddrState(LlAddrStateIdx,                                                                 /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
                                        IpV4_Ip_VLl_GenerateIpAddr(IpV4CtrlIdx,
                                                                   TcpIp_GetConflictsNumOfLlAddrState(LlAddrStateIdx)));
      TcpIp_SetProbeStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_PROBE_STATE_PROBE);                                   /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
    }

    /* #40 In case substate has changed to PROBE, send an ARP request to probe the newly generated (random) address. */
    if(TcpIp_GetProbeStateOfLlAddrState(LlAddrStateIdx) == IPV4_IP_LL_PROBE_STATE_PROBE)
    {
      if(IpV4_Arp_SendArpProbe(IpV4CtrlIdx, TcpIp_GetNetAddrCandOfLlAddrState(LlAddrStateIdx)) == E_OK)
      {
        TcpIp_IncProbeNumSinceConfOfLlAddrState(LlAddrStateIdx);                                                        /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
        TcpIp_SetProbeStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_PROBE_STATE_WAIT);                                  /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */

        if(TcpIp_GetProbeNumSinceConfOfLlAddrState(LlAddrStateIdx) == TcpIp_GetProbeNumOfAutoIpConfig(AutoIpConfigIdx))
        {
          /* wait IPV4_IP_ANNOUNCE_WAIT_MS ms */
          TcpIp_SetWaitUntilTimeOfLlAddrState(LlAddrStateIdx,                                                           /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
                                              TcpIp_GetMsecCntOfLlAddrState(LlAddrStateIdx) +
                                              TcpIp_GetAnnounceWaitMsOfAutoIpConfig(AutoIpConfigIdx));
        }
        else
        {
          /* Wait random time (IPV4_IP_PROBE_MIN_MS .. IPV4_IP_PROBE_MAX_MS) ms */
          TcpIp_SetWaitUntilTimeOfLlAddrState(LlAddrStateIdx,                                                           /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
                                              TcpIp_GetMsecCntOfLlAddrState(LlAddrStateIdx) +
                                              TcpIp_GetProbeMinMsOfAutoIpConfig(AutoIpConfigIdx));
          /* Choose random time between "IPV4_IP_PROBE_WAIT_MIN_MS" and "IPV4_IP_PROBE_WAIT_MAX_MS" */
          if(   TcpIp_GetProbeMaxMsOfAutoIpConfig(AutoIpConfigIdx)
              > TcpIp_GetProbeMinMsOfAutoIpConfig(AutoIpConfigIdx))
          {
            uint16 RandNo = TcpIp_GetRandomNumber();                                                                    /* SBSW_TCPIP_RANDOM_NUMBER_FUNC */
            TcpIp_SetWaitUntilTimeOfLlAddrState(LlAddrStateIdx,                                                         /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
                                                TcpIp_GetWaitUntilTimeOfLlAddrState(LlAddrStateIdx) +
                                                ((uint32) RandNo % ((uint32) TcpIp_GetProbeMaxMsOfAutoIpConfig(AutoIpConfigIdx)
                                                            - (uint32) TcpIp_GetProbeMinMsOfAutoIpConfig(AutoIpConfigIdx))));
          }
        }
      }
      /* else: ARP request could not be sent, so try again later */
    }
    /* #50 In case the substate is WAIT, check, if the waiting time is over. */
    else if(TcpIp_GetProbeStateOfLlAddrState(LlAddrStateIdx) == IPV4_IP_LL_PROBE_STATE_WAIT)
    {
      if(TcpIp_GetWaitUntilTimeOfLlAddrState(LlAddrStateIdx) < TcpIp_GetMsecCntOfLlAddrState(LlAddrStateIdx))
      {
        if(TcpIp_GetProbeNumSinceConfOfLlAddrState(LlAddrStateIdx) == TcpIp_GetProbeNumOfAutoIpConfig(AutoIpConfigIdx))
        {
          /* goto announce */
          TcpIp_SetStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_STATE_ANNOUNCE);                                       /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
          TcpIp_SetAnnStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_ANN_STATE_PROBE);                                   /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */

          /* "If, by ANNOUNCE_WAIT seconds after the transmission of the last ARP
            *  Probe no conflicting ARP Reply or ARP Probe has been received, then
            *  the host has successfully claimed the desired IPv4 Link-Local address."
            *                                           [RFC3927 2.2.1. Probe details]
            */

          /* valid addr found, so indicate it! */
          TcpIp_SetAddrFoundOfLlAddrState(LlAddrStateIdx, TcpIp_GetNetAddrCandOfLlAddrState(LlAddrStateIdx));           /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
          IpV4_Ip_VIpAddrAssignmentReadyNotification(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL, TRUE);
        }
        else
        {
          /* next probe */
          TcpIp_SetProbeStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_PROBE_STATE_PROBE);                               /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
        }
      }
      /* else: wait a little longer (do nothing) */
    }
    else
    {
      /* ERROR: invalid state: Do nothing */
      /* satisfy MISRA-C:2004 Rule 14.10: requires else for if-else-if statements */
    }
  }
} /* IpV4_Ip_VLl_HandleStateProbe */ /* PRQA S 6050, 6080 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_HandleStateConflict
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_HandleStateConflict(
  TcpIp_LlAddrStateIdxOfIpV4CtrlType  LlAddrStateIdx,
  TcpIp_AutoIpConfigIdxOfIpV4CtrlType AutoIpConfigIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset announcement number, conflict marker, probe counter  */
  TcpIp_SetAnnounceNumOfLlAddrState(LlAddrStateIdx, 0);                                                                 /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
  TcpIp_SetAddrConflictOfLlAddrState(LlAddrStateIdx, FALSE);                                                            /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
  TcpIp_SetProbeNumSinceConfOfLlAddrState(LlAddrStateIdx, 0);                                                           /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
  TcpIp_IncConflictsNumOfLlAddrState(LlAddrStateIdx);                                                                   /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */

  /* #20 In case the number of conflicts for the given LINKLOCAL address index has exceeded:
         At once try the next random network address. */
  if(TcpIp_GetMaxConflictsOfAutoIpConfig(AutoIpConfigIdx) > TcpIp_GetConflictsNumOfLlAddrState(LlAddrStateIdx))
  {
    /* no delay, try next random network address - now (or in the next call cycle)! */
    TcpIp_SetWaitUntilTimeOfLlAddrState(LlAddrStateIdx, TcpIp_GetMsecCntOfLlAddrState(LlAddrStateIdx));                 /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
  }
  else
  {
    /* (too) many conflicts occurred, so delay further address tests */
    TcpIp_SetWaitUntilTimeOfLlAddrState(LlAddrStateIdx,                                                                 /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
                                        TcpIp_GetMsecCntOfLlAddrState(LlAddrStateIdx) +
                                        TcpIp_GetRateLimitIntervalMsOfAutoIpConfig(AutoIpConfigIdx));
  }
  TcpIp_SetStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_STATE_WAIT);                                                   /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
} /* IpV4_Ip_VLl_HandleStateConflict */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_HandleStateAnnounce
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_HandleStateAnnounce(
  TcpIp_IpV4CtrlIterType              IpV4CtrlIdx,
  TcpIp_LlAddrStateIdxOfIpV4CtrlType  LlAddrStateIdx,
  TcpIp_AutoIpConfigIdxOfIpV4CtrlType AutoIpConfigIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Send an ARP announcement in case the state is PROBE. */
  if(TcpIp_GetAnnStateOfLlAddrState(LlAddrStateIdx) == IPV4_IP_LL_ANN_STATE_PROBE)
  {
    /* #20 Copy the old address, send with new candidate address, restore old address. */
    if(IpV4_Arp_SendArpAnnouncement(IpV4CtrlIdx, TcpIp_GetAddrFoundOfLlAddrState(LlAddrStateIdx)) == E_OK)
    {
      /* Increase the counter of announcements */
      TcpIp_IncAnnounceNumOfLlAddrState(LlAddrStateIdx);                                                                /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
      TcpIp_SetAnnStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_ANN_STATE_WAIT);                                        /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */

      /* wait IPV4_IP_ANNOUNCE_INTERVAL_MS ms */
      TcpIp_SetWaitUntilTimeOfLlAddrState(LlAddrStateIdx,                                                               /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
                                          TcpIp_GetMsecCntOfLlAddrState(LlAddrStateIdx) +
                                          TcpIp_GetAnnounceIntervalMsOfAutoIpConfig(AutoIpConfigIdx));
    }
  }
  /* #30 Wait a little longer or go to next state in case state is WAIT. */
  else if(TcpIp_GetAnnStateOfLlAddrState(LlAddrStateIdx) == IPV4_IP_LL_ANN_STATE_WAIT)
  {
    if(TcpIp_GetWaitUntilTimeOfLlAddrState(LlAddrStateIdx) < TcpIp_GetMsecCntOfLlAddrState(LlAddrStateIdx))
    {
      /* #40 In case the required number of announcements has ben sent, set state to READY */
      if(TcpIp_GetAnnounceNumOfLlAddrState(LlAddrStateIdx) >= TcpIp_GetAnnounceNumOfAutoIpConfig(AutoIpConfigIdx))
      {
        /* For the case that the CONFLICT state was touched:
           Reset the number of conflicts for the given LINKLOCAL address in order to restart the whole scenario */
        TcpIp_SetConflictsNumOfLlAddrState(LlAddrStateIdx, 0);                                                          /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
        /* Goto ready */
        TcpIp_SetStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_STATE_READY);                                            /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
      }
      else
      {
        /* next announcement */
        TcpIp_SetAnnStateOfLlAddrState(LlAddrStateIdx, IPV4_IP_LL_ANN_STATE_PROBE);                                     /* SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR */
      }
    }
    else
    {
      /* wait a little longer: Do nothing */
    }
  }
  else
  {
    /* ERROR: invalid state */
  }
} /* IpV4_Ip_VLl_HandleStateAnnounce */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  IpV4_Ip_VLl_FindAddr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VLl_FindAddr(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Retrieve llAddrStateIdx and autoIpConfigIdx whose presence and validity
     are checked by IpV4_Ip_VLl_Main() and validators in the generator of the TcpIp. */
  TcpIp_LlAddrStateIdxOfIpV4CtrlType  llAddrStateIdx  = TcpIp_GetLlAddrStateIdxOfIpV4Ctrl(IpV4CtrlIdx);                 /* SBSW_TCPIP_CM_R6 */
  TcpIp_AutoIpConfigIdxOfIpV4CtrlType autoIpConfigIdx = TcpIp_GetAutoIpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);                /* SBSW_TCPIP_CM_R6 */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle the main states of the LINKLOCAL address assignment mechanism. */
  switch (TcpIp_GetStateOfLlAddrState(llAddrStateIdx))
  {
  case IPV4_IP_LL_STATE_INIT:
    {

      TcpIp_SetWaitUntilTimeOfLlAddrState(llAddrStateIdx,                                                               /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
                                          TcpIp_GetMsecCntOfLlAddrState(llAddrStateIdx) +
                                          TcpIp_GetProbeWaitMinMsOfAutoIpConfig(autoIpConfigIdx));
      /* choose random time between "IPV4_IP_PROBE_WAIT_MIN_MS" and "IPV4_IP_PROBE_WAIT_MAX_MS" */
      if(   TcpIp_GetProbeWaitMaxMsOfAutoIpConfig(autoIpConfigIdx)
          > TcpIp_GetProbeWaitMinMsOfAutoIpConfig(autoIpConfigIdx))
      {
        uint16 RandNo = TcpIp_GetRandomNumber();                                                                        /* SBSW_TCPIP_RANDOM_NUMBER_FUNC */
        TcpIp_SetWaitUntilTimeOfLlAddrState(llAddrStateIdx,                                                             /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
                                            TcpIp_GetWaitUntilTimeOfLlAddrState(llAddrStateIdx) +
                                            ((uint32)RandNo % ((uint32) TcpIp_GetProbeWaitMaxMsOfAutoIpConfig(autoIpConfigIdx)
                                                        - (uint32) TcpIp_GetProbeWaitMinMsOfAutoIpConfig(autoIpConfigIdx))));
      }

      TcpIp_SetStateOfLlAddrState(llAddrStateIdx, IPV4_IP_LL_STATE_WAIT);                                               /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
    }
    break;

  case IPV4_IP_LL_STATE_WAIT:
    {
      /* #20 Issue the next probe cycle in case the waiting time (in state WAIT) has gone by. */
      if(TcpIp_GetWaitUntilTimeOfLlAddrState(llAddrStateIdx) <= TcpIp_GetMsecCntOfLlAddrState(llAddrStateIdx))
      {
        TcpIp_SetStateOfLlAddrState(     llAddrStateIdx, IPV4_IP_LL_STATE_PROBE);                                       /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
        TcpIp_SetProbeStateOfLlAddrState(llAddrStateIdx, IPV4_IP_LL_PROBE_STATE_CHOOSE);                                /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
      }
      else
      {
        /* Otherwise wait a little longer: Do nothing */
      }
    }
    break;

  case IPV4_IP_LL_STATE_PROBE:
    IpV4_Ip_VLl_HandleStateProbe(IpV4CtrlIdx, llAddrStateIdx, autoIpConfigIdx);
    break;

  case IPV4_IP_LL_STATE_CONFLICT:
    IpV4_Ip_VLl_HandleStateConflict(llAddrStateIdx, autoIpConfigIdx);
    break;

  case IPV4_IP_LL_STATE_ANNOUNCE:
    IpV4_Ip_VLl_HandleStateAnnounce(IpV4CtrlIdx, llAddrStateIdx, autoIpConfigIdx);
    break;

  case IPV4_IP_LL_STATE_READY:
    /* nothing to do. */
    break;

  default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    /* Default case left blank intentionally */
    /* ERROR: This state should not be reached. */
    TCPIP_ASSERT_UNREACHABLE();
    break;
  }

  TcpIp_SetMsecCntOfLlAddrState(llAddrStateIdx,                                                                         /* SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER */
                                TcpIp_GetMsecCntOfLlAddrState(llAddrStateIdx) + TCPIP_MAIN_FCT_PERIOD_MSEC);
  return;
} /* IpV4_Ip_VLl_FindAddr */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/************************************************************************************************************
 *  IpV4_Ip_VForwardPacketToUpperLayer()
 ***********************************************************************************************************/
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
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VForwardPacketToUpperLayer(
  TcpIp_IpV4CtrlIterType    IpV4CtrlIdx,
  TcpIp_LocalAddrV4IterType LocalAddrV4Idx,
  IPV4_P2C(uint8)           DataPtr,
  IPV4_P2V(uint8)           IpV4PayloadPtr,
  uint16                    IpV4PayloadLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SockAddrBaseType IpRxSockAddrRem; /* PRQA S 0759 */ /* MD_MSR_18.4 */
#if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
  TcpIp_SockAddrBaseType IpRxSockAddrLoc; /* PRQA S 0759 */ /* MD_MSR_18.4 */
#endif
  uint8                  ipProtocol;
#if (TCPIP_SUPPORT_IPSEC == STD_ON)
  Std_ReturnType         ipSecRetVal;
  uint16                 ipSecHdrLen;
  uint8*                 upperLayerPayloadPtr;
#else
  uint8*                 upperLayerPayloadPtr = IpV4PayloadPtr;
#endif
  uint16                 upperLayerPayloadLen = IpV4PayloadLen;


  /* ----- Implementation ----------------------------------------------- */
  IpBase_AddrInType srcAddr = TCPIP_GET_UINT32_RAW(DataPtr, TCPIP_IPV4_HDR_OFS_SRC_ADDR);
# if ((TCPIP_SUPPORT_DHCPV4 == STD_ON) || (TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG == STD_ON) || (TCPIP_SUPPORT_TCP == STD_ON))
  IpBase_AddrInType destAddr = TCPIP_GET_UINT32_RAW(DataPtr, TCPIP_IPV4_HDR_OFS_DEST_ADDR);
# endif

# if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
  IpRxSockAddrLoc.SockAddrIn.sin_family = IPBASE_AF_INET;
  IpRxSockAddrLoc.SockAddrIn.sin_addr   = destAddr;
  IpRxSockAddrLoc.SockAddrIn.sin_port   = 0;  /* undefined */
# endif
  /* Create socket addresses for source and destination */
  IpRxSockAddrRem.SockAddrIn.sin_family = IPBASE_AF_INET;
  IpRxSockAddrRem.SockAddrIn.sin_addr = srcAddr;
  IpRxSockAddrRem.SockAddrIn.sin_port = 0;  /* undefined */

  ipProtocol = TCPIP_GET_UINT8(DataPtr, TCPIP_IPV4_HDR_OFS_PROT);

#if (TCPIP_SUPPORT_IPSEC == STD_ON)
  /* #10 If valid IpSecConfigset is present, perform IpSec processing of the packet */
  if (TcpIp_IsIpSecConfigSetUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    ipSecRetVal = TcpIp_IpSec_ProcessRxPacket(IpV4CtrlIdx, DataPtr, upperLayerPayloadLen, &ipProtocol, &ipSecHdrLen);  /* SBSW_TCPIP_ConstPtr */ /* SBSW_TCPIP_PtrToLocalVariable */
  }
  /* #20 Otherwise, proceed with packet forwarding */
  else
  {
    ipSecRetVal = E_OK;
    ipSecHdrLen = 0;
  }

  /* #30 Proceed with further processing of packet only if process was successful */
  if (ipSecRetVal == E_OK)
  {
    /* Update the start of upper layer payload buffer to skip any IpSec header that has been processed */
    upperLayerPayloadPtr = &IpV4PayloadPtr[ipSecHdrLen];
    upperLayerPayloadLen -= ipSecHdrLen;
#endif
    /* #40 Depending on the protocol indicated by the IP header (DHCP, UDP, TCP, ICMP):
           Forward the IP packet to the related upper layer. */
    switch (ipProtocol)
    {
      case IPV4_IP_PROTOCOL_UDP:
      {
        boolean checksumValidated = (boolean)(TcpIp_IsHwChecksumUdpOfIpV4Ctrl(IpV4CtrlIdx) == TRUE);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  # if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
        /* #50 In case DHCPv4 is configured forward UDP packets to DHCP, also (in addition to forwarding it to UDP). */
        {
          TcpIp_DhcpV4_RxIndication(IpV4CtrlIdx, upperLayerPayloadPtr, upperLayerPayloadLen,                            /* SBSW_TCPIP_VALID_PTR_CALLER */
            &(IpRxSockAddrRem.SockAddrIn), &(IpRxSockAddrLoc.SockAddrIn),
            checksumValidated);
        }
  # endif
        /* forward message to upper layer (UDP) */
        /* #60 Send a "destination unreachable" message in case there is no matching UDP socket. */
        if(   TcpIp_Udp_RxIndication(TCPIP_IPV4_TO_LOCAL_ADDR_IDX(LocalAddrV4Idx), &IpRxSockAddrRem,                    /* SBSW_TCPIP_VALID_PTR_CALLER */
                                     upperLayerPayloadPtr, upperLayerPayloadLen, checksumValidated)
           == TCPIP_UDP_E_NO_MATCHING_SOCKET)
        {
  # if (TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG == STD_ON)
          TCPIP_ASSERT(TcpIp_HasIcmpConfig() == TRUE);

          if(!(IPV4_ADDR_IS_MULTICAST(destAddr) || IPV4_ADDR_IS_BROADCAST(IpV4CtrlIdx, destAddr)))
          {
            IpV4_Icmp_SendDestUnreachable(LocalAddrV4Idx, DataPtr, IPV4_ICMP_CODE_PORT_UNREACHABLE);                    /* SBSW_TCPIP_VALID_PTR_CALLER */
          }
  # endif
        }
      }
      break;

  # if (TCPIP_SUPPORT_TCP == STD_ON)
      /* #70 In case TCP is configured forward TCP packets to that upper layer. */
      case IPV4_IP_PROTOCOL_TCP:
      {
        boolean checksumValidated = (boolean)(TcpIp_IsHwChecksumTcpOfIpV4Ctrl(IpV4CtrlIdx) == TRUE);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

        /* #80 Only forward message to upper layer in case IP address of the ECU is configured, already. */
        if(IPV4_IP_ONLINE_ACTIVE == TcpIp_GetStateOfIpV4CtrlDyn(IpV4CtrlIdx))
        {
          /* #90 Only forward message to upper layer in case IP address is neither a multicast or broadcast address. */
          if (!(IPV4_ADDR_IS_MULTICAST(destAddr) || IPV4_ADDR_IS_BROADCAST(IpV4CtrlIdx, destAddr)))
          {
            /* forward message to upper layer (TCP) */
            TcpIp_Tcp_RxIndication((TcpIp_SizeOfLocalAddrType)LocalAddrV4Idx, &IpRxSockAddrRem, upperLayerPayloadPtr, upperLayerPayloadLen, checksumValidated);/* SBSW_TCPIP_VALID_PTR_CALLER */
          }
        }
      }
      break;
  # endif
  /* TCPIP_SUPPORT_TCP */

  # if (TCPIP_SUPPORT_ICMPV4 == STD_ON)                                                                                   /* COV_TCPIP_ICMPV4_ALWAYS_ON */
      /* #100 In case ICMPv4 is configured forward ICMP packets to that upper layer. */
      case IPV4_IP_PROTOCOL_ICMP:
      {
        /* forward message to upper layer (ICMP) */
        IpV4_Icmp_RxIndication((TcpIp_SizeOfLocalAddrType)LocalAddrV4Idx, srcAddr, TCPIP_GET_UINT8(DataPtr, TCPIP_IPV4_HDR_OFS_TTL), upperLayerPayloadPtr, upperLayerPayloadLen,/* SBSW_TCPIP_VALID_PTR_CALLER */

          TcpIp_IsHwChecksumIcmpOfIpV4Ctrl(IpV4CtrlIdx)
          );
      }
      break;
  # endif
    /* IPV4_SUPPORT_ICMP == STD_ON */

      default:
      /* #110 Discard all messages for unsupported protocols. */
  # if (TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG == STD_ON)
      TCPIP_ASSERT(TcpIp_HasIcmpConfig() == TRUE);

      if (!(IPV4_ADDR_IS_MULTICAST(destAddr) || IPV4_ADDR_IS_BROADCAST(IpV4CtrlIdx, destAddr)))
      {
        IpV4_Icmp_SendDestUnreachable((TcpIp_SizeOfLocalAddrType)LocalAddrV4Idx, DataPtr, IPV4_ICMP_CODE_PROTOCOL_UNREACHABLE);/* SBSW_TCPIP_VALID_PTR_CALLER */
      }
  # endif
      break;
    }
# if (TCPIP_SUPPORT_IPSEC == STD_ON)
  }
# endif
} /* IpV4_Ip_VForwardPacketToUpperLayer */ /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess */

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyInitBuffers()
 ***********************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VReassemblyInitBuffers(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_ReassemblyBufferDescStartIdxOfFragmentationConfigType reassemblyBufferDescIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all reassembly buffer descriptors. */
  for (reassemblyBufferDescIdx = 0;
       reassemblyBufferDescIdx < TcpIp_GetSizeOfReassemblyBufferDescDyn();
       reassemblyBufferDescIdx++)
  {
    IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) reassemblyBufDescPtr =
      TcpIp_GetAddrReassemblyBufferDescDyn(reassemblyBufferDescIdx);

    reassemblyBufDescPtr->Status = IPV4_IP_REASSEMBLY_BUF_STATUS_UNUSED;                                                /* SBSW_TCPIP_PTR_TO_ARRAY_ELEM_CSL01_IDX_LOCAL */

    /* #20 Store index of the descriptor in the descriptor struct in order to retrieve it back again
           in case the descriptor can only be accessed by pointer.
           (Configuration allows to have more descriptors than buffers in order
            to handle incomplete/failed packets without blocking a buffer) */
    reassemblyBufDescPtr->ReassemblyBufDescIdx = reassemblyBufferDescIdx;                                               /* SBSW_TCPIP_PTR_TO_ARRAY_ELEM_CSL01_IDX_LOCAL */
  }
} /* IpV4_Ip_VReassemblyInitBuffers */

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyFindBufferDesc()
 ***********************************************************************************************************/
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
IPV4_LOCAL_INLINE FUNC(TcpIp_SizeOfReassemblyBufferDescType, IPV4_CODE) IpV4_Ip_VReassemblyFindBufferDesc(
  TcpIp_IpV4CtrlIterType                         IpV4CtrlIdx,
  IPV4_P2C(uint8)                                DataPtr,
  IPV4_P2V(TcpIp_SizeOfReassemblyBufferDescType) UnusedDescIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_FragmentationConfigIdxOfIpV4CtrlType fragmentationConfigIdx =
    TcpIp_GetFragmentationConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
  TcpIp_ReassemblyBufferDescEndIdxOfFragmentationConfigType reassemblyBufferDescIdx;
  boolean matchFound = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  *UnusedDescIdxPtr = IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV; /* will be used if no matching descriptor is found */        /* SBSW_TCPIP_VALID_PTR_CALLER */
  TCPIP_ASSERT(fragmentationConfigIdx < TcpIp_GetSizeOfFragmentationConfig());

  /* #10 Iterate all reassembly buffer descriptors of the fragmentation config of the given IpV4 controller
         and locate matching, unused or oldest buffer. */
  for ( reassemblyBufferDescIdx = TcpIp_GetReassemblyBufferDescStartIdxOfFragmentationConfig(fragmentationConfigIdx);
        reassemblyBufferDescIdx < TcpIp_GetReassemblyBufferDescEndIdxOfFragmentationConfig(fragmentationConfigIdx);
        reassemblyBufferDescIdx++)
  {
    IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) reassemblyBufDescPtr =
      TcpIp_GetAddrReassemblyBufferDescDyn(reassemblyBufferDescIdx);
    uint32 ageMs = IpV4_Ip_TimeMs - reassemblyBufDescPtr->TimeMs;

    /* #20 In case the reassembly is complete, release the affected reassembly buffer descriptor. */
    if(IPV4_IP_REASSEMBLY_BUF_STATUS_COMPLETE == reassemblyBufDescPtr->Status)
    {
      reassemblyBufDescPtr->Status = IPV4_IP_REASSEMBLY_BUF_STATUS_UNUSED;                                              /* SBSW_TCPIP_PTR_TO_ARRAY_ELEM_CSL01_IDX_LOCAL */
    }
    /* #30 In case the reassembly is InProgress or failed and reassembly timeout has expired, release the affected reassembly buffer descriptor. */
    if (    ((IPV4_IP_REASSEMBLY_BUF_STATUS_IN_PROGRESS  == reassemblyBufDescPtr->Status) || (IPV4_IP_REASSEMBLY_BUF_STATUS_FAILED == reassemblyBufDescPtr->Status))
         && (ageMs >= TcpIp_GetReassemblyTimeoutMsOfFragmentationConfig(fragmentationConfigIdx)))
    {
      reassemblyBufDescPtr->Status = IPV4_IP_REASSEMBLY_BUF_STATUS_UNUSED;                                              /* SBSW_TCPIP_PTR_TO_ARRAY_ELEM_CSL01_IDX_LOCAL */
    }

    /* #40 In case the reassembly descriptor is in use:
           Check if it matches the content of the given IP header pointer and stop searching if it does.
           Otherwise continue searching. */
    if(reassemblyBufDescPtr->Status != IPV4_IP_REASSEMBLY_BUF_STATUS_UNUSED)
    {
      /* #50 Stop searching in case the reassembly descriptors data
             matches the content of the given IP header pointer. */
      /* Buffers are exclusively assigned to particular IP controllers, so matching IpV4CtrlIdx is not necessary. */
      if (   (reassemblyBufDescPtr->MatchIpSrcAddr      == TCPIP_GET_UINT32_RAW(DataPtr, TCPIP_IPV4_HDR_OFS_SRC_ADDR ))
          && (reassemblyBufDescPtr->MatchIpDstAddr      == TCPIP_GET_UINT32_RAW(DataPtr, TCPIP_IPV4_HDR_OFS_DEST_ADDR))
          && (reassemblyBufDescPtr->MatchIpProtocol     == TCPIP_GET_UINT8     (DataPtr, TCPIP_IPV4_HDR_OFS_PROT     ))
          && (reassemblyBufDescPtr->MatchIdentification == TCPIP_GET_UINT16_RAW(DataPtr, TCPIP_IPV4_HDR_OFS_IDENT    )))
      {
        /* matching reassembly buffer found */
        matchFound = TRUE;
        break;
      }
    }
    else if (*UnusedDescIdxPtr == IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV)
    {
      /* Store the index of the unused descriptor. */
      *UnusedDescIdxPtr = reassemblyBufferDescIdx;                                                                      /* SBSW_TCPIP_VALID_PTR_CALLER */
    }
    else
    {
      /* Skip this descriptor, because an unused descriptor has been found, before, already! */
    }
  }

  /* #60 Reset the loops iterator value in case no buffer descriptor has been found
         that matches the data of the given IP header pointer. */
  if(matchFound == FALSE)
  {
    reassemblyBufferDescIdx = IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV;
  }

  return (TcpIp_SizeOfReassemblyBufferDescType)reassemblyBufferDescIdx;
} /* IpV4_Ip_VReassemblyFindBufferDesc */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyGetBufferDesc()
 ***********************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferDescIterType, IPV4_CODE) IpV4_Ip_VReassemblyGetBufferDesc(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IPV4_P2C(uint8)        DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfReassemblyBufferDescType unusedDescIdx;
  /* #10 Iterate assembly buffers and locate matching, unused or oldest buffer. */
  TcpIp_SizeOfReassemblyBufferDescType usedDescIdx =
    IpV4_Ip_VReassemblyFindBufferDesc(IpV4CtrlIdx, DataPtr, &unusedDescIdx);                                            /* SBSW_TCPIP_FUNC_CALL_CSL01_IDX_CALLER_VALID_PTR_CALLER_OUT_PTR_FROM_LOCAL_VAR */
  TcpIp_FragmentationConfigIdxOfIpV4CtrlType fragmentationConfigIdx =
    TcpIp_GetFragmentationConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #20 Prepare unused assembly buffer descriptor if no matching reassembly buffer was found. */
  if(usedDescIdx == IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV)
  {
    /* #30 In case no matching reassembly buffer descriptor was found, try to use an old one. */
    if(unusedDescIdx != IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV)
    {
      IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) reassemblyBufDescPtr;
      IPV4_P2V(uint8) reassemblyBufPtr;
      uint16 firstGapOfs;
      uint16 firstGapSize;

      usedDescIdx = unusedDescIdx;
      /* #40 In case a free descriptor is available: Initialize its values with the info from the IP header pointer. */
      reassemblyBufDescPtr = TcpIp_GetAddrReassemblyBufferDescDyn(usedDescIdx);
      reassemblyBufPtr = IpV4_Ip_VReassemblyGetBufferPtr(reassemblyBufDescPtr);                                         /* SBSW_TCPIP_FUNC_CALL_GET_REASSEMBLY_BUF_PTR */

      firstGapOfs  = IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS;
      firstGapSize = TcpIp_GetMaxPacketSizeOfFragmentationConfig(fragmentationConfigIdx);

      reassemblyBufDescPtr->MatchIpSrcAddr       = TCPIP_GET_UINT32_RAW(DataPtr, TCPIP_IPV4_HDR_OFS_SRC_ADDR );         /* SBSW_TCPIP_REASSEMBLY_DESC_PTR_FROM_FOUND_IDX */
      reassemblyBufDescPtr->MatchIpDstAddr       = TCPIP_GET_UINT32_RAW(DataPtr, TCPIP_IPV4_HDR_OFS_DEST_ADDR);         /* SBSW_TCPIP_REASSEMBLY_DESC_PTR_FROM_FOUND_IDX */
      reassemblyBufDescPtr->MatchIpProtocol      = TCPIP_GET_UINT8     (DataPtr, TCPIP_IPV4_HDR_OFS_PROT     );         /* SBSW_TCPIP_REASSEMBLY_DESC_PTR_FROM_FOUND_IDX */
      reassemblyBufDescPtr->MatchIdentification  = TCPIP_GET_UINT16_RAW(DataPtr, TCPIP_IPV4_HDR_OFS_IDENT    );         /* SBSW_TCPIP_REASSEMBLY_DESC_PTR_FROM_FOUND_IDX */
      reassemblyBufDescPtr->NextGapOfs           = 0u;                                                                  /* SBSW_TCPIP_REASSEMBLY_DESC_PTR_FROM_FOUND_IDX */

      TCPIP_PUT_UINT16(reassemblyBufPtr, IPV4_IP_REASSEMBLY_BUF_NEXT_GAP_OFS, firstGapOfs);                             /* SBSW_TCPIP_FUNC_CALL_WRITE_REASSEMBLY_BUF_INFO */
      TCPIP_PUT_UINT16(reassemblyBufPtr, IPV4_IP_REASSEMBLY_BUF_GAP_SIZE_OFS, firstGapSize);                            /* SBSW_TCPIP_FUNC_CALL_WRITE_REASSEMBLY_BUF_INFO */

      reassemblyBufDescPtr->TimeMs            = IpV4_Ip_TimeMs;                                                         /* SBSW_TCPIP_REASSEMBLY_DESC_PTR_FROM_FOUND_IDX */
      reassemblyBufDescPtr->Status            = IPV4_IP_REASSEMBLY_BUF_STATUS_IN_PROGRESS;                              /* SBSW_TCPIP_REASSEMBLY_DESC_PTR_FROM_FOUND_IDX */
      reassemblyBufDescPtr->Flags             = 0;                                                                      /* SBSW_TCPIP_REASSEMBLY_DESC_PTR_FROM_FOUND_IDX */
      reassemblyBufDescPtr->FragmentLen       = 0;                                                                      /* SBSW_TCPIP_REASSEMBLY_DESC_PTR_FROM_FOUND_IDX */
    }
    else
    {
      usedDescIdx = IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV;
    }
    /* else: RESOURCE LIMIT: no free descriptor available */
  }

  return usedDescIdx;
} /* IpV4_Ip_VReassemblyGetBufferDesc */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyGetBufferPtr()
 ***********************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
IPV4_LOCAL_INLINE FUNC_P2VAR(uint8, AUTOMATIC, IPV4_CODE) IpV4_Ip_VReassemblyGetBufferPtr(
  IPV4_P2C(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr)
{
  TcpIp_ReassemblyBufferDescIterType reassemblyBufferDescIdx = ReassemblyBufDescPtr->ReassemblyBufDescIdx;
  /* #10 Return pointer to reassembly buffer that is attached to the reassembly buffer descriptor. */
  TcpIp_ReassemblyBufferStartIdxOfReassemblyBufferDescType reassemblyBufferStartIdxOfReassemblyBufferDesc =
    TcpIp_GetReassemblyBufferStartIdxOfReassemblyBufferDesc(reassemblyBufferDescIdx);
  return TcpIp_GetAddrReassemblyBuffer(reassemblyBufferStartIdxOfReassemblyBufferDesc);
}

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyAdaptGapBeginning()
 ***********************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VReassemblyAdaptGapBeginning(
  IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr,
  uint16                                     FragEndOfs,
  uint16                                     ThisGapEndOfs,
  uint16                                     PrevGapOfs,
  uint16                                     NextGapOfs)
{
  /* ----- Local Variables ---------------------------------------------- */
  IPV4_P2V(uint8) reassemblyBufPtr = IpV4_Ip_VReassemblyGetBufferPtr(ReassemblyBufDescPtr);                             /* SBSW_TCPIP_VALID_PTR_CALLER */

  /* ----- Implementation ----------------------------------------------- */
  if(FragEndOfs == ThisGapEndOfs)
  {
    /* |######| Case 1: Fragment completely fits into gap. */

    /* #10 If there is a previous gap, set next pointer to following gap (or INV). */
    if(IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS != PrevGapOfs)
    {
      TCPIP_PUT_UINT16(reassemblyBufPtr, PrevGapOfs, NextGapOfs);                                                       /* SBSW_TCPIP_FUNC_CALL_WRITE_REASSEMBLY_BUF_INFO */
    }
    else
    {
      /* Set the very first gap offset to next gap */
      ReassemblyBufDescPtr->NextGapOfs = NextGapOfs;                                                                    /* SBSW_TCPIP_VALID_PTR_CALLER */
    }
  }
  else
  {
    /* #20 |####__| Case 2: Fragment starts at beginning of gap but does not completely fill the gap. */

    /* #30 Create new gap (old one will be overwritten). */
    uint16 newGapOfs = FragEndOfs;
    TCPIP_PUT_UINT16(reassemblyBufPtr, newGapOfs + IPV4_IP_REASSEMBLY_BUF_GAP_SIZE_OFS, (ThisGapEndOfs - FragEndOfs));  /* SBSW_TCPIP_FUNC_CALL_WRITE_REASSEMBLY_BUF_INFO */

    /* If there is a previous gap, set next pointer to new gap */
    if(IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS != PrevGapOfs)
    {
      TCPIP_PUT_UINT16(reassemblyBufPtr, PrevGapOfs, newGapOfs);                                                        /* SBSW_TCPIP_FUNC_CALL_WRITE_REASSEMBLY_BUF_INFO */
    }
    else
    {
      ReassemblyBufDescPtr->NextGapOfs = newGapOfs;                                                                     /* SBSW_TCPIP_VALID_PTR_CALLER */
    }

    /* Set next pointer of new gap to next gap (or INV) */
    TCPIP_PUT_UINT16(reassemblyBufPtr, newGapOfs, NextGapOfs);                                                          /* SBSW_TCPIP_FUNC_CALL_WRITE_REASSEMBLY_BUF_INFO */
  }
} /* IpV4_Ip_VReassemblyAdaptGapBeginning */

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyAdaptGapNonBeginning()
 ***********************************************************************************************************/
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
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VReassemblyAdaptGapNonBeginning(
  IPV4_P2V(uint8) ReassemblyBufPtr,
  uint16          FragOfs,
  uint16          FragEndOfs,
  uint16          ThisGapOfs,
  uint16          ThisGapEndOfs,
  uint16          NextGapOfs)
{
  /* #10 In any case: Decrease size of this gap. */
  TCPIP_PUT_UINT16(ReassemblyBufPtr, ThisGapOfs + IPV4_IP_REASSEMBLY_BUF_GAP_SIZE_OFS, (FragOfs - ThisGapOfs));         /* SBSW_TCPIP_FUNC_CALL_WRITE_REASSEMBLY_BUF_INFO */

  if(FragEndOfs != ThisGapEndOfs)
  {
    /* #20 |__##__| Case 4: Fragment fills some part in the middle of the gap
                            but there will remain a gap before and after the fragment. */
    uint16 newGapOfs = FragEndOfs;

    /* #30 Decrease size of this gap. */
    TCPIP_PUT_UINT16(ReassemblyBufPtr, ThisGapOfs + IPV4_IP_REASSEMBLY_BUF_GAP_SIZE_OFS, (FragOfs - ThisGapOfs));       /* SBSW_TCPIP_FUNC_CALL_WRITE_REASSEMBLY_BUF_INFO */

    /* #40 Create new gap. */
    TCPIP_PUT_UINT16(ReassemblyBufPtr, newGapOfs + IPV4_IP_REASSEMBLY_BUF_GAP_SIZE_OFS, (ThisGapEndOfs - FragEndOfs));  /* SBSW_TCPIP_FUNC_CALL_WRITE_REASSEMBLY_BUF_INFO */

    /* Set next pointer of this gap to new gap */
    TCPIP_PUT_UINT16(ReassemblyBufPtr, ThisGapOfs, newGapOfs);                                                          /* SBSW_TCPIP_FUNC_CALL_WRITE_REASSEMBLY_BUF_INFO */

    /* Set next pointer of new gap to next gap (or INV) */
    TCPIP_PUT_UINT16(ReassemblyBufPtr, newGapOfs, NextGapOfs);                                                          /* SBSW_TCPIP_FUNC_CALL_WRITE_REASSEMBLY_BUF_INFO */
  }
  /* #50 Otherwise we have:
         |__####| Case 3: Fragment ends at end of gap but does not start at beginning of gap.
         I.e.: Decreasing the size of the gap has already been done, above: Nothing else to be done! */
} /* IpV4_Ip_VReassemblyAdaptGapNonBeginning */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyAdaptGap()
 ***********************************************************************************************************/
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
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VReassemblyAdaptGap(
  IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr,
  uint16                                     FragOfs,
  uint16                                     FragEndOfs,
  uint16                                     ThisGapOfs,
  uint16                                     ThisGapEndOfs,
  uint16                                     PrevGapOfs,
  uint16                                     NextGapOfs)
{
  /* ----- Local Variables ---------------------------------------------- */
  IPV4_P2V(uint8) reassemblyBufPtr = IpV4_Ip_VReassemblyGetBufferPtr(ReassemblyBufDescPtr);                             /* SBSW_TCPIP_VALID_PTR_CALLER */

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT_MSG((ThisGapOfs <= FragOfs) && (FragEndOfs <= ThisGapEndOfs), "Fragment must fit into gap.");

  /* #10 There are 4 cases how a fragment may fit into a gap in the reassembly buffer. */
  if(FragOfs == ThisGapOfs)
  {
    /* #20 |######| Case 1: Fragment completely fits into gap.
                            If there is a previous gap, set next pointer to following gap (or INV). */
    /* #30 |####__| Case 2: Fragment starts at beginning of gap but does not completely fill the gap.
                            Create new gap (old one will be overwritten). */
    IpV4_Ip_VReassemblyAdaptGapBeginning(ReassemblyBufDescPtr, FragEndOfs, ThisGapEndOfs, PrevGapOfs, NextGapOfs);      /* SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER_VALID_PTR_CALLER */
  }
  else
  {
    /* #40 |__####| Case 3: Fragment ends at end of gap but does not start at beginning of gap.
                            Decrease size of this gap. */
    /* #50 |__##__| Case 4: Fragment fills some part in the middle of the gap but there will remain
                            a gap before and after the fragment. Decrease size of this gap. Create new gap. */
    IpV4_Ip_VReassemblyAdaptGapNonBeginning(reassemblyBufPtr, FragOfs, FragEndOfs,                                      /* SBSW_TCPIP_FUNC_CALL_ADAPT_GAP_NON_BEGINNING */
                                            ThisGapOfs, ThisGapEndOfs, NextGapOfs);
  }
} /* IpV4_Ip_VReassemblyAdaptGap */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyHandleGaps()
 ***********************************************************************************************************/
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
 */
IPV4_LOCAL_INLINE FUNC(Std_ReturnType, IPV4_CODE) IpV4_Ip_VReassemblyHandleGaps(
  IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr,
  uint16                                     FragOfs,
  uint16                                     FragLen,
  boolean                                    FragIsLast,
  IPV4_P2V(uint16)                           GapOfsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal            = E_NOT_OK;
  boolean        searchMatchingGap = TRUE;
  uint16         gapOfs            = ReassemblyBufDescPtr->NextGapOfs;
  uint16         prevGapOfs        = IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS;
  uint16         fragEndOfs        = (FragOfs + FragLen);
  IPV4_P2V(uint8) reassemblyBufPtr = IpV4_Ip_VReassemblyGetBufferPtr(ReassemblyBufDescPtr);                             /* SBSW_TCPIP_VALID_PTR_CALLER */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate linked list of payload gaps until a gap is found the fragment fits into.
         Payload gaps are non overlapping and stored in ascending order.
         All gaps but the last gap will always have a size of at least 8 bytes,
         because all fragments except for the last fragment must be a multiple of 8 bytes long. */
  while ((TRUE == searchMatchingGap) && (gapOfs != IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS))
  {
    uint16 nextGapOfs;
    uint16 gapSize;
    uint16 gapEndOfs;

    TCPIP_ASSERT((gapOfs % IPV4_IP_FRAGMENT_BLOCK_SIZE) == 0u);
    /* Read the byte offset of the start of the next gap */
    nextGapOfs = TCPIP_GET_UINT16(reassemblyBufPtr, gapOfs /* + IPV4_IP_REASSEMBLY_BUF_NEXT_GAP_OFS */);
    /* The lengths of all fragments that are not 'last' have to be a multiple of IPV4_IP_FRAGMENT_BLOCK_SIZE,
       i.e. also the gaps lengths' have to follow this rule. */
    TCPIP_ASSERT(   (nextGapOfs == IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS) /* first received fragment is processed */
                 || ((nextGapOfs % IPV4_IP_FRAGMENT_BLOCK_SIZE) == 0u));    /* OR follow up fragment is processed */

    /* Calculate the end of the gap currently looked at, using the gapSize admin data stored at the gaps start: */
    gapSize = TCPIP_GET_UINT16(reassemblyBufPtr, gapOfs + IPV4_IP_REASSEMBLY_BUF_GAP_SIZE_OFS);
    TCPIP_ASSERT(gapSize > 0u);
    gapEndOfs = (gapOfs + gapSize);

    /* #20 Check, whether the new fragment starts in front of the start of the gap currently looked at:
           If yes it overlaps with the fragment located in front of to the current gap and thus is an INVALID FRAGMENT:
           Since all following gaps will have bigger GapOfs, they do not need to be checked.
           This is an invalid, overlapping or already received fragment:
           Ignore this fragment by resetting the search-flag. */
    if (FragOfs < gapOfs)
    {
      searchMatchingGap = FALSE;
    }
    /* #30 In case the fragment ends behind the end of the current gap: Leave searchMatchingGap at TRUE.
           Continue searching and checking if fragment might fit into one of the following gaps. */
    else if (fragEndOfs > gapEndOfs)
    {
      /* Fragments ends after end of this gap. Leave searchMatchingGap at TRUE.
         Continue searching and checking if fragment fits into one of the following gaps: */
    }
    else
    /* #40 In case this fragment fits into this gap: Check if it's the last fragment and if yes:
           Shrink the gap to end behind this very last fragment (if required). Adapt gap, if matching gap was found. */
    {
      /* OK: Fragment fits into this gap */
      if(TRUE == FragIsLast)
      {
        /* AND it's the last fragment. Thus ensure that there is no further upcoming gap: */
        TCPIP_ASSERT(nextGapOfs == IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS);

        /* #50 In case the fragment ends in front of the current end of the current gap: Adapt the end of that gap: */
        if(fragEndOfs < gapEndOfs)
        {
          /* Shrink gap so it ends after current and last fragment and write the new gap-admin info into the gap */
          gapSize   = FragLen;
          gapEndOfs = fragEndOfs;
          TCPIP_PUT_UINT16(reassemblyBufPtr, gapOfs + IPV4_IP_REASSEMBLY_BUF_GAP_SIZE_OFS, gapSize);                    /* SBSW_TCPIP_FUNC_CALL_WRITE_REASSEMBLY_BUF_INFO */
        }

        ReassemblyBufDescPtr->FragmentLen = gapEndOfs;                                                                  /* SBSW_TCPIP_VALID_PTR_CALLER */
      }

      /* Adapt gap, if matching gap was found. */
      IpV4_Ip_VReassemblyAdaptGap(ReassemblyBufDescPtr, FragOfs, fragEndOfs, gapOfs, gapEndOfs, prevGapOfs, nextGapOfs);/* SBSW_TCPIP_FUNC_CALL_ADAPT_GAP */

      retVal = E_OK;
      break;
    }

    prevGapOfs = gapOfs;

    /* move to next gap */
    gapOfs = nextGapOfs;
  } /* while(more gaps) */

  *GapOfsPtr = gapOfs;                                                                                                  /* SBSW_TCPIP_VALID_PTR_CALLER */

  return retVal;
} /* IpV4_Ip_VReassemblyHandleGaps */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyRxFragment()
 ***********************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VReassemblyRxFragment(
  IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr,
  uint16                                     FragAbsByteOfs,
  IPV4_P2C(uint8)                            FragPayloadPtr,
  uint16                                     FragPayloadLen,
  boolean                                    FragIsLast)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16          gapOfs;
  IPV4_P2V(uint8) reassemblyBufPtr = IpV4_Ip_VReassemblyGetBufferPtr(ReassemblyBufDescPtr);                             /* SBSW_TCPIP_VALID_PTR_CALLER */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if fragment fits into one of the existing gaps inside the reassembly buffer and update gap list. */
  if(IpV4_Ip_VReassemblyHandleGaps(ReassemblyBufDescPtr, FragAbsByteOfs, FragPayloadLen, FragIsLast, &gapOfs) == E_OK)  /* SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER_VALID_PTR_CALLER_OUT_PTR_FROM_LOCAL_VAR */
  {
    /* #20 Copy payload of fragment into the reassembly buffer. */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpBase_Copy((IpBase_CopyDataType*)&reassemblyBufPtr[FragAbsByteOfs],                                                /* SBSW_TCPIP_FUNC_CALL_COPY_INTO_REASSEMBLY_BUF */
                (const IpBase_CopyDataType*)&(FragPayloadPtr)[0], FragPayloadLen);
  }

  /* #30 Check if fragmentation is complete, has failed or if more fragments are expected. */
  if(ReassemblyBufDescPtr->NextGapOfs == IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS)
  {
    if(0u != (ReassemblyBufDescPtr->Flags & IPV4_IP_REASSEMBLY_FLAG_LAST_FRAG_RECEIVED))
    {
      /* No more gaps. All fragments received. Set reassembly status of this buffer descriptor to complete. */
      ReassemblyBufDescPtr->Status = IPV4_IP_REASSEMBLY_BUF_STATUS_COMPLETE;                                            /* SBSW_TCPIP_VALID_PTR_CALLER */
    }
    else
    {
      /* RESOURCE LIMIT: Reassembly buffer is full before last fragment has been received. -> Abort reassembly */
      ReassemblyBufDescPtr->Status = IPV4_IP_REASSEMBLY_BUF_STATUS_FAILED;                                              /* SBSW_TCPIP_VALID_PTR_CALLER */
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
      /* Increment the measurement data counter for dropped IPV4 message (due to insufficient reassembly buffer) */
      TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_IPV4_FRAGMENT_RX_BUFFER);
#endif
    }
  }
  else if (gapOfs == IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS)
  {
    /* RESOURCE LIMIT: fragment does not fit into any gap. Assembly buffer too small. -> Abort reassembly */
    ReassemblyBufDescPtr->Status = IPV4_IP_REASSEMBLY_BUF_STATUS_FAILED;                                                /* SBSW_TCPIP_VALID_PTR_CALLER */
    /* Descriptor will be released after the reassembly timeout has expired */
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
    /* Increment the measurement data counter for dropped IPV4 message (due to insufficient reassembly buffer) */
    TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_IPV4_FRAGMENT_RX_BUFFER);
#endif
  }
  else
  {
    /* there are still gaps in the buffer. Wait for further fragments... */
  }
} /* IpV4_Ip_VReassemblyRxFragment */

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyRxFragmentInOrder()
 ***********************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(void, IPV4_CODE) IpV4_Ip_VReassemblyRxFragmentInOrder(
  IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr,
  uint16                                     FragAbsByteOfs,
  IPV4_P2C(uint8)                            FragPayloadPtr,
  uint16                                     FragPayloadLen,
  boolean                                    FragIsLast,
  TcpIp_FragmentationConfigIdxOfIpV4CtrlType FragmentationConfigIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 "In Order Re-assembly" requires to only continue in case the fragment fits directly behind the previous one */
  if(FragAbsByteOfs == ReassemblyBufDescPtr->NextGapOfs)
  {
    /* #20 Abort reassembly in case FragPayloadLen is larger than the (calculated) remaining buffer length */
    if(FragPayloadLen > (TcpIp_GetMaxPacketSizeOfFragmentationConfig(FragmentationConfigIdx) - FragAbsByteOfs))
    {
      /* RESOURCE LIMIT: Assembly buffer too small. -> Abort reassembly */
      ReassemblyBufDescPtr->Status = IPV4_IP_REASSEMBLY_BUF_STATUS_UNUSED;                                              /* SBSW_TCPIP_VALID_PTR_CALLER */
      /* We do not expect segments out-of-order. So free reassembly buffer immediately. */
#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
      /* Increment the measurement data counter for dropped IPV4 message (due to insufficient reassembly buffer) */
      TcpIp_VIncMeasurementDataCounter(TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_IPV4_FRAGMENT_RX_BUFFER);
#endif
    }
    else
    {
      /* #30 In case remaining buffer length is large enough: Copy fragment payload. */
      IPV4_P2V(uint8) reassemblyBufPtr = IpV4_Ip_VReassemblyGetBufferPtr(ReassemblyBufDescPtr);                         /* SBSW_TCPIP_VALID_PTR_CALLER */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpBase_Copy((IpBase_CopyDataType*)&reassemblyBufPtr[FragAbsByteOfs],                                              /* SBSW_TCPIP_FUNC_CALL_COPY_INTO_REASSEMBLY_BUF */
                  (const IpBase_CopyDataType*)&(FragPayloadPtr)[0], FragPayloadLen);
      ReassemblyBufDescPtr->NextGapOfs = FragAbsByteOfs + FragPayloadLen;                                               /* SBSW_TCPIP_VALID_PTR_CALLER */

      /* #40 Update reassembly status to COMPLETE, if this was the last fragment. */
      if(FragIsLast == TRUE)
      {
        ReassemblyBufDescPtr->Status = IPV4_IP_REASSEMBLY_BUF_STATUS_COMPLETE;                                          /* SBSW_TCPIP_VALID_PTR_CALLER */
        ReassemblyBufDescPtr->FragmentLen = ReassemblyBufDescPtr->NextGapOfs;                                           /* SBSW_TCPIP_VALID_PTR_CALLER */
      }
    }
  }
  else
  /* #50 Otherwise: Set reassembly status to failed. */
  {
    /* Unexpected fragment offset. Out of order reassembly not supported -> Abort fragment reassembly */
    ReassemblyBufDescPtr->Status = IPV4_IP_REASSEMBLY_BUF_STATUS_UNUSED;                                                /* SBSW_TCPIP_VALID_PTR_CALLER */
    /* We do not expect segments out-of-order. So free reassembly buffer immediately. */
  }
} /* IpV4_Ip_VReassemblyRxFragmentInOrder */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyCheckFragment()
 ***********************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
IPV4_LOCAL_INLINE FUNC(boolean, IPV4_CODE) IpV4_Ip_VReassemblyCheckFragment(
  IPV4_P2V(IpV4_Ip_ReassemblyBufferDescType) ReassemblyBufDescPtr,
  uint16                                     FragBlockOfs,
  boolean                                    FragIsLast)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean acceptFragment = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set first fragment received flag, in case this is the first fragment and the flag is not already set.
         Leave the return value at FALSE, in case a first fragment was received before. */
  if(FragBlockOfs == 0u)
  {
    /* This is the first fragment. Note: it may arrive after other fragments. */
    if((ReassemblyBufDescPtr->Flags & IPV4_IP_REASSEMBLY_FLAG_FIRST_FRAG_RECEIVED) == 0u)
    {
      ReassemblyBufDescPtr->Flags |= IPV4_IP_REASSEMBLY_FLAG_FIRST_FRAG_RECEIVED;                                       /* SBSW_TCPIP_VALID_PTR_CALLER */
    }
    else
    {
      /* INVALID FRAGMENT: Received first fragment twice! -> Ignore this fragment */
      acceptFragment = FALSE;
    }
  }

  /* #20 Set last fragment received flag, in case this is the last fragment and the flag is not already set.
         Leave the return value at FALSE, in case a last fragment was received before. */
  if(acceptFragment == TRUE)
  {
    if(FragIsLast == TRUE)
    {
      if((ReassemblyBufDescPtr->Flags & IPV4_IP_REASSEMBLY_FLAG_LAST_FRAG_RECEIVED) == 0u)
      {
        ReassemblyBufDescPtr->Flags |= IPV4_IP_REASSEMBLY_FLAG_LAST_FRAG_RECEIVED;                                      /* SBSW_TCPIP_VALID_PTR_CALLER */
      }
      else
      {
        /* INVALID FRAGMENT: received last fragment twice! -> Ignore this fragment */
        acceptFragment = FALSE;
      }
    }
  }

  return acceptFragment;
} /* IpV4_Ip_VReassemblyCheckFragment */

/************************************************************************************************************
 *  IpV4_Ip_VReassemblyRxIndication()
 ***********************************************************************************************************/
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
IPV4_LOCAL_INLINE FUNC(boolean, IPV4_CODE) IpV4_Ip_VReassemblyRxIndication(
  TcpIp_IpV4CtrlIterType IpV4CtrlIdx,
  IPV4_P2C(uint8)        DataPtr,
  IPV4_P2V(uint8*)       FragPayloadPtrPtr,
  IPV4_P2V(uint16)       FragPayloadLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean                             reassemblyComplete = FALSE;
  TcpIp_ReassemblyBufferDescIterType  reassemblyBufDescIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(DataPtr != NULL_PTR);

  TCPIP_ASSERT(FragPayloadPtrPtr != NULL_PTR);
  TCPIP_ASSERT(FragPayloadPtrPtr[0] != NULL_PTR);

  TCPIP_ASSERT(FragPayloadLenPtr != NULL_PTR);
  TCPIP_ASSERT(FragPayloadLenPtr[0] != 0u);

  /* #10 Get (or create) reassembly buffer descriptor for this IP packet. */
  reassemblyBufDescIdx = IpV4_Ip_VReassemblyGetBufferDesc(IpV4CtrlIdx, DataPtr);                                        /* SBSW_TCPIP_FUNC_CALL_VALID_PTR_CALLER */

  if (reassemblyBufDescIdx == IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV)                                                      /* SBSW_TCPIP_CM_R4 */
  {
    /* RESOURCE LIMIT: No free reassembly buffer and descriptor -> Do not start reassembly.
                       Leave reassemblyComplete at FALSE */
  }
  else
  {
    IpV4_Ip_ReassemblyBufferDescType *reassemblyBufDescPtr = TcpIp_GetAddrReassemblyBufferDescDyn(reassemblyBufDescIdx);
    uint16                            flagsOffset          = TCPIP_GET_UINT16(DataPtr, TCPIP_IPV4_HDR_OFS_FLAGS_OFFSET);
    uint16                            fragBlockOfs         = (uint16)(flagsOffset & IPV4_IP_FRAGMENT_OFFSET_MASK);
    boolean                           fragIsLast           = (boolean)((flagsOffset & IPV4_IP_FLAGS_MORE_FRAGMENTS) == 0u);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    boolean                           acceptFragment;

    TCPIP_ASSERT(IPV4_IP_REASSEMBLY_BUF_STATUS_UNUSED != reassemblyBufDescPtr->Status);

    /* #20 In case the reassembly of this packet has failed or is complete, already: Ignore this fragment.
           Otherwise conduct further validity checks on the fragment. */
    if(reassemblyBufDescPtr->Status != IPV4_IP_REASSEMBLY_BUF_STATUS_IN_PROGRESS)
    {
      acceptFragment = FALSE;
    }
    else
    {
      acceptFragment = IpV4_Ip_VReassemblyCheckFragment(reassemblyBufDescPtr, fragBlockOfs, fragIsLast);                /* SBSW_TCPIP_BUF_DESC_PTR_BASED_CHECK_AND_REASSEMBLY */
    }

    /* #30 Continue processing in case fragmentation is running and the fragment received is consistent: */
    if(acceptFragment == TRUE)
    {
      /* #40 In case the size of the fragment is a multiple of IPv4 block size in the middle or arbitrary at the end:
             Reassemble the fragment. Otherwise abort reassembly */
      if((fragIsLast == TRUE) || (((*FragPayloadLenPtr) % IPV4_IP_FRAGMENT_BLOCK_SIZE) == 0u))
      {
        uint16 fragAbsByteOfs = fragBlockOfs * IPV4_IP_FRAGMENT_BLOCK_SIZE;
        TcpIp_FragmentationConfigIdxOfIpV4CtrlType fragmentationConfigIdx;

        TCPIP_ASSERT(TcpIp_IsFragmentationConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE);
        fragmentationConfigIdx = TcpIp_GetFragmentationConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
        TCPIP_ASSERT(   reassemblyBufDescPtr->ReassemblyBufDescIdx
                     >= TcpIp_GetReassemblyBufferDescStartIdxOfFragmentationConfig(fragmentationConfigIdx));
        TCPIP_ASSERT(  reassemblyBufDescPtr->ReassemblyBufDescIdx
                     < TcpIp_GetReassemblyBufferDescEndIdxOfFragmentationConfig(fragmentationConfigIdx));

        /* #50 In case the fragment fits into a gap inside the buffer:
               Copy payload of the fragment into the reassembly buffer. */
        if (TcpIp_IsInOrderReassemblyOfFragmentationConfig(fragmentationConfigIdx) == FALSE)
        {
          IpV4_Ip_VReassemblyRxFragment(reassemblyBufDescPtr, fragAbsByteOfs,                                           /* SBSW_TCPIP_BUF_DESC_PTR_BASED_CHECK_AND_REASSEMBLY */
                                        *FragPayloadPtrPtr, *FragPayloadLenPtr, fragIsLast);
        }
        else
        {
          IpV4_Ip_VReassemblyRxFragmentInOrder(reassemblyBufDescPtr, fragAbsByteOfs,                                    /* SBSW_TCPIP_BUF_DESC_PTR_BASED_CHECK_AND_REASSEMBLY */
                                               *FragPayloadPtrPtr, *FragPayloadLenPtr, fragIsLast,
                                               fragmentationConfigIdx);
        }

        /* #60 Update *FragPayloadPtrPtr and *FragPayloadLenPtr if reassembly is complete. */
        if(reassemblyBufDescPtr->Status == IPV4_IP_REASSEMBLY_BUF_STATUS_COMPLETE)
        {
          *FragPayloadPtrPtr = IpV4_Ip_VReassemblyGetBufferPtr(reassemblyBufDescPtr);                                   /* SBSW_TCPIP_FUNC_CALL_GET_REASSEMBLY_BUF_PTR */ /* SBSW_TCPIP_VALID_PTR_CALLER */
          *FragPayloadLenPtr = reassemblyBufDescPtr->FragmentLen;                                                       /* SBSW_TCPIP_VALID_PTR_CALLER */
        }
      }
      /* #70 A non-last fragment with a length that is not a multiple of 8 bytes has been found:
             Abort Reassembly of this packet. */
      else
      {
        /* INVALID FRAGMENT: Only the last fragment may have a length that is not a multiple of 8 bytes:
           Abort Reassembly of this packet. */
        reassemblyBufDescPtr->Status = IPV4_IP_REASSEMBLY_BUF_STATUS_FAILED;                                            /* SBSW_TCPIP_WRITE_REASSEMBLY_BUF_DESC_PTR */
      }
    }

    reassemblyComplete = (boolean)(reassemblyBufDescPtr->Status == IPV4_IP_REASSEMBLY_BUF_STATUS_COMPLETE);  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  }

  return reassemblyComplete;
} /* IpV4_Ip_VReassemblyRxIndication */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/************************************************************************************************************
 *  TcpIp_IpV4_GetCurrTimeMs()
 ***********************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(uint32, IPV4_CODE) TcpIp_IpV4_GetCurrTimeMs(void)
{
  /* #10 Return current IpV4 time in milliseconds */
  return IpV4_Ip_TimeMs;
} /* TcpIp_IpV4_GetCurrTimeMs() */

# define TCPIP_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

/*
   MICROSAR global MISRA deviations:
   - see file 'WI_MISRAC2004_PES.pdf'

   Justification for module-specific MISRA deviations:

   module global deviations -> see file TcpIp.c

   IPv4-specific deviations:
   MD_IPV4_Rule11.4_0310_ethbuf:
     Reason:     TcpIp_SetEthBufPtrOfBuf2TxReqMap stores the buffer pointer to
                 the provided tx buffer from the EthIf as uint8*.
                 However EthIf's buffers consist of datatype uint32.
                 So EthIf's buffers are solely better aligned and casting is possible.
     Risk:       Only casting from Eth_DataType* (i.e. uint32*) to uint8* is allowed.
     Prevention: Covered by code review.

   MD_IPV4_Rule12.4_3415:
     Reason:     A concatenation of conditions may break without checking the later conditions if a previous one
                 already failed.
     Risk:       The concatenation of conditions might have a different effect as expected.
     Prevention: Covered by code review.

  MD_IPV4_Rule8.3:
     Reason:     Reworking the code to use 'const' pointers more often would cause much effort.
     Risk:       none
     Prevention: not applicable module global deviations
*/

/*
NOTE: For Tp_AsrTpTcpIp the following additional assumption is taken:
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
All TcpIp-internal callers guarantee the validity of index parameters
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID               SBSW_TCPIP_VALID_PTR_DET_CHECKED
    \DESCRIPTION    A pointer that was checked to be valid by a prior DET check in this function is dereferenced and written or passed to a function in a function-call in order to be dereferenced and written.
    \COUNTERMEASURE \R The DET check executed prior the write action ensures the validity of the pointer

  \ID               SBSW_TCPIP_VALID_PTR_CALLER
    \DESCRIPTION    A pointer that was checked to be valid by the caller of this function is dereferenced and written or passed to a function in a function-call in order to be dereferenced and written.
    \COUNTERMEASURE \N The caller ensures the validity of the pointer-parameter(s).

  \ID               SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER
    \DESCRIPTION    One or more non-pointer parameter(s) that [was|were] checked to be valid by the caller of this function [is|are] used as parameter(s) for a function call.
    \COUNTERMEASURE \N The caller ensures the validity of the parameter(s).

  \ID               SBSW_TCPIP_FUNC_CALL_VALID_PTR_CALLER
    \DESCRIPTION    One or more pointer parameter(s) that [was|were] checked to be valid by the caller of this function [is|are] used as parameter(s) for a function call.
    \COUNTERMEASURE \N The caller ensures the validity of the pointer-parameter(s).

  \ID               SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER_VALID_PTR_CALLER
    \DESCRIPTION    This function-call is valid, because it takes parameters of 2 types, each of them being valid because it complies to one of the following justifications:
                    - SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER
                    - SBSW_TCPIP_VALID_PTR_CALLER
    \COUNTERMEASURE \N The caller ensures the validity of the parameters.

  \ID               SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER_CSL01_IDX_CALLER
    \DESCRIPTION    This function-call is valid, because it takes parameters of 2 types, each of them being valid because it complies to one of the following justifications:
                    - SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER
                    - SBSW_TCPIP_CSL01_IDX_CALLER
    \COUNTERMEASURE \N The caller ensures the validity of the parameters.

  \ID               SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER
    \DESCRIPTION    An index is provided and checked by the caller of the function to be within the valid range by using the associated TcpIp_GetSizeOf...() function.
                    That index is used to read or write an CSL-generated array of the same size.
    \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

  \ID               SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_LOCAL
    \DESCRIPTION    A local variable is used as an index and checked to be within the valid range by using the associated TcpIp_GetSizeOf...() function.
                    That index is used to read or write an CSL-generated array of the same size.
    \COUNTERMEASURE \R The local function code ensures that the index is within the valid range by using the associated TcpIp_GetSizeOf...() function.
                       Qualified use-case CSL02 of ComStackLib

  \ID               SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER
    \DESCRIPTION    A CSL modelled RAM array is written using an index that is determined using one (or more) modelled indirections according to CSL03.
                    The first index for the lookup(s) is provided and checked by the caller of the function to be within the valid range by using the associated TcpIp_GetSizeOf...() function.
                    The associated TcpIp_Is...() function(s) [is|are] used as applicable to check the validity of the index value(s) of the modelled indirection(s).
                    Thus this is a qualified use-case CSL03 of ComStackLib.
                    This scenario is also applicable in case the determined index value is used as parameter of a function-call, because the index has a valid value.
    \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib.

  \ID               SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_LOCAL
    \DESCRIPTION    A CSL modelled RAM array is written using an index that is determined using one (or more) modelled indirections according to CSL03.
                    A local variable is used as first index for the lookups and checked to be within the valid range by using the associated TcpIp_GetSizeOf...() function.
                    The associated TcpIp_Is...() function(s) [is|are] used as applicable to check the validity of the index value(s) of the modelled indirection(s).
                    Thus this is a qualified use-case CSL03 of ComStackLib.
    \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib.

  \ID               SBSW_TCPIP_CSL01_IDX_CALLER
    \DESCRIPTION    The function accesses CSL-generated config-arrays reading (ROM) OR writing (RAM) at a position that is given by the index parameter.
    \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib:
                       The caller ensures that the index is within the valid range by using the associated TcpIp_GetSizeOf...() function.

  \ID               SBSW_TCPIP_CSL01_IDX_LOCAL
    \DESCRIPTION    The function writes into the CSL array at a position that is given by the index parameter.
    \COUNTERMEASURE \R The local function code ensures that the index is within the valid range by using the associated TcpIp_GetSizeOf...() function.
                       Qualified use-case CSL01 of ComStackLib.

  \ID               SBSW_TCPIP_PTR_TO_ARRAY_ELEM_CSL01_IDX_LOCAL
    \DESCRIPTION    The pointer written to is initialized using the address of an CSL generated array element that is accessed CSL01 compliant.
    \COUNTERMEASURE \N The local function code ensures that the index is within the valid range by using the associated TcpIp_GetSizeOf...() function.
                       Qualified use-case CSL01 of ComStackLib.

  \ID               SBSW_TCPIP_FUNC_CALL_ACTIVE_ADDR_OF_ASSIGNMENT_METHOD
    \DESCRIPTION    This function-call is valid, because it takes parameters of 3 types, each of them being valid because it complies to one of the following justifications:
                    - IpV4CtrlIdx comes valid from caller as described in SBSW_TCPIP_CSL01_IDX_CALLER.
                    - AddrAssignmentMethod is retrieved from dynamic runtime data of the affected IPv4 controller using TcpIp_GetAddrAssignmentMethodPersistOfIpV4CtrlDyn(IpV4CtrlIdx)
                      The value is valid according to CM_TCPIP_ADDR_ASSIGMENT_METHOD.
                    - AddrInfoPtr is given by local pointer variable ipAddrSetPtr which is valid because the call to IpV4_Ip_VGetActiveAddressOfAssignmentMethod() is encapsuled by the
                      check that ipAddrSetPtr has been initialized validly by the preceeding function call to IpV4_Ip_NvmGetAddrSet() which has to return E_OK.
    \COUNTERMEASURE \R CM_TCPIP_ADDR_ASSIGMENT_METHOD

  \ID               SBSW_TCPIP_CONSTANT_OR_LOCAL_INITIALIZED_VAR_BASED_POINTER_PARAM
    \DESCRIPTION    This function either takes a constant and/or the address of a local variable (which has been initialized
                    suitably) as parameter.
    \COUNTERMEASURE \N This is valid C-code. The compiler takes care that the function is called with valid parameters.

  \ID               SBSW_TCPIP_FUNC_CALL_CSL01_IDX_CALLER_OUT_PTR_FROM_LOCAL_VAR
    \DESCRIPTION    This function-call is valid, because it takes 2 types of parameters that are valid because they comply to the following justifications:
                    SBSW_TCPIP_CSL01_IDX_CALLER
                    The pointer(s) passed to the function point(s) to local variables that do not have to be initialized because the parameter(s) [is|are] out parameters.
    \COUNTERMEASURE \N The parameters are valid because of these countermeasures:
                       Pointer to local variables are always valid.
                       The caller ensures that the index is within the valid range by using the associated TcpIp_GetSizeOf...() function.
                       Qualified use-case CSL01 of ComStackLib.

  \ID               SBSW_TCPIP_FUNC_CALL_CSL01_IDX_CALLER_VALID_PTR_CALLER_OUT_PTR_FROM_LOCAL_VAR
    \DESCRIPTION    This function-call is valid, because it takes 3 types of parameters that are valid because they comply to the following justifications:
                    Refer to SBSW_TCPIP_FUNC_CALL_CSL01_IDX_CALLER_OUT_PTR_FROM_LOCAL_VAR
                    Refer to SBSW_TCPIP_VALID_PTR_CALLER
    \COUNTERMEASURE \N The parameters are valid because of these countermeasures:
                       Refer to SBSW_TCPIP_FUNC_CALL_CSL01_IDX_CALLER_OUT_PTR_FROM_LOCAL_VAR
                       Refer to SBSW_TCPIP_VALID_PTR_CALLER
                       Qualified use-case CSL01 of ComStackLib.

  \ID               SBSW_TCPIP_CSL03_BASED_IDX_FOR_LL_ADDR
    \DESCRIPTION    A CSL modelled RAM array is written using an index that is determined using one (or more) modelled indirections according to CSL03.
                    In detail the runtime check SBSW_TCPIP_CM_R5 ensures that IpV4_Ip_VLl_Main() is called only in case all modelled indirections are validly present.
                    This fulfills the CONSTRAINTs given for IpV4_Ip_VLl_Main().
                    In addition the modelled, CSL03-compliant indirection lookup is done at SBSW_TCPIP_CM_R6 so the functions:
                    - IpV4_Ip_VLl_HandleStateConflict()
                    - IpV4_Ip_VLl_HandleStateAnnounce()
                    - IpV4_Ip_VLl_HandleStateProbe()
                    called by IpV4_Ip_VLl_Main() and its successors used.
    \COUNTERMEASURE \R Runtime check SBSW_TCPIP_CM_R5 ensures the qualified use-case CSL03 of ComStackLib at SBSW_TCPIP_CM_R6.

  \ID               SBSW_TCPIP_FUNC_CALL_COPY_PHYS_ADDR
    \DESCRIPTION    Function-call with valid parameters as described below:
                    - DstAddrPtr is:
                      - a 6-byte array of type IpBase_EthPhysAddrType which is looked up
                        - using CSL macro TcpIp_GetAddrPhysAddrOfLastDuplicateDhcpAddr()
                        - using an index that is valid as described in:
                          - SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_LOCAL for memory write access in IpV4_Ip_Init()
                          - SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER for memory write access in IpV4_Ip_RxIsDuplicateDhcpAddr()
                      - valid because passing the address of the first element is valid as described in SBSW_TCPIP_PHYS_ADDR_TYPE_ARRAY_AS_PTR_PARAM.
                    - SrcAddrPtr is given differently in these 2 contexts:
                      1. during initialization the parameter is given as the first element of the local variable initPhysAddr of type IpBase_EthPhysAddrType and thus is valid.
                      2. when storing a physical address associated to a DEM event the parameter is given by PhysAddrPtr coming valid from caller (Refer to SBSW_TCPIP_VALID_PTR_CALLER).
    \COUNTERMEASURE \N The parameters are valid because of these countermeasures:
                       The caller ensures the validity of the pointer.
                       The caller ensures that the index is within the valid range by using the associated TcpIp_GetSizeOf...() function.
                       Qualified use-case CSL03 of ComStackLib.

  \ID               SBSW_TCPIP_FUNC_CALL_CHECKSUM_ADD_RX_IND_FWD_UL
    \DESCRIPTION    Function-call with valid parameters as described below:
                    - Pointer parameter DataPtr comes valid from caller as described in SBSW_TCPIP_VALID_PTR_CALLER.
                      DataPtr points to an uint8 array that at least has size of an IPv4 packet's header structure (IPV4_IP_DEF_HEADER_LENGTH_BYTE).
                      This function is called in the context of IpV4_Ip_RxIndication() which checks the length value coded in the IPv4 header's IHL byte to be >= IPV4_IP_DEF_HEADER_LENGTH_BYTE.
                      Thus the IHL value, read into local variable ipHdrLenByte, using the macro TCPIP_IPV4_HDR_FIELD_GET_IHL_BYTE() is >= IPV4_IP_DEF_HEADER_LENGTH_BYTE.
                    - ipHdrLenByte is valid due to CM_TCPIP_IP_HDR_LEN_BYTE.
                    - All other parameters of this function-call are constants and thus valid.
                    In addition CM_TCPIP_IPV4_HDR_STRUCT_SIZE ensures that ipHdrLenByte, is read at the correct offset (IPV4_IP_DEF_HEADER_LENGTH_BYTE) and thus has a valid value.
    \COUNTERMEASURE \R CM_TCPIP_IPV4_HDR_STRUCT_SIZE

  \ID               SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER_OUT_PTR_PHYS_ADDR
    \DESCRIPTION    This function-call is valid, because it takes 2 types of parameters that are valid because they comply to the following justifications:
                    - One or more parameter(s) come(s) valid from caller as described in SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER.
                    - &physMulticastAddr[0] is valid as described in SBSW_TCPIP_PHYS_ADDR_TYPE_ARRAY_AS_PTR_PARAM.
    \COUNTERMEASURE \M CM_TCPIP_SIZE_OF_IPBASE_ETH_PHYS_ADDR_TYPE

  \ID               SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER_VALID_PTR_CALLER_OUT_PTR_FROM_LOCAL_VAR
    \DESCRIPTION    This function-call is valid, because it takes 2 types of parameters that are valid because they comply to the following justifications:
                    - SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER_VALID_PTR_CALLER
                    - One or more parameter(s) come(s) valid from caller as described in SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER.
                    - One or more parameter(s) are valid pointers [out] parameter i.e. the value does not have to be initialized locally.
    \COUNTERMEASURE \N The caller ensures the validity of the pointer.
                       The address of a local variable is passed to the function as a typed pointer which is correct C-code and thus leads to a valid pointer parameter.

  \ID               SBSW_TCPIP_FUNC_CALL_REASSEMBLY_RX_IND
    \DESCRIPTION    Function-call with valid parameters as described below:
                    - IpV4CtrlIdx: Valid as described in SBSW_TCPIP_CSL01_IDX_CALLER.
                    - DataPtr: Valid as described in SBSW_TCPIP_VALID_PTR_CALLER.
                    - &ipPayloadPtr: This local pointer variable is initialized by an array access to the array DataPtr[]
                                     which is valid from caller:
                                     - according to SBSW_TCPIP_VALID_PTR_CALLER and due
                                     - the runtime check in line containing token SBSW_TCPIP_CM_R1:
                                       if (ipPayloadLenByte > 0)
                                       ensures that at least one byte of payload is present beyond the IPv4 header structure at the beginning of the IPv4 packet received.
                      The array access to initialize ipPayloadPtr is valid because the array-position is local variable ipHdrLenByte which is valid due to CM_TCPIP_IP_HDR_LEN_BYTE .
                    - &ipPayloadLenByte is calculated as ipPayloadLenByte = ipTotalLenByte - ipHdrLenByte whereat:
                      - ipHdrLenByte is valid due to CM_TCPIP_IP_HDR_LEN_BYTE .
                      - ipTotalLenByte is valid and >= ipHdrLenByte due to CM_TCPIP_IP_TOTAL_LEN_BYTE.
                      This means ipPayloadLenByte is >= 0 which is mandatory for this unsigned variable.
    \COUNTERMEASURE \R CM_TCPIP_IP_HDR_LEN_BYTE
                    \R CM_TCPIP_IP_TOTAL_LEN_BYTE
                    \R Runtime check in line containing token SBSW_TCPIP_CM_R1: if (ipPayloadLenByte > 0)

  \ID               SBSW_TCPIP_FUNC_CALL_ADAPT_GAP_NON_BEGINNING
    \DESCRIPTION    This function-call is valid, because it takes parameters of 2 types, each of them being valid because it complies to one of the following justifications:
                    - SBSW_TCPIP_FUNC_CALL_VALID_PARAM_CALLER_VALID_PTR_CALLER
                    - reassemblyBufferPtr is validly initialized from ReassemblyBufDescPtr from caller
                      whereat caller initializes the buffer descriptor as described in SBSW_TCPIP_FUNC_CALL_GET_REASSEMBLY_BUF_PTR.
    \COUNTERMEASURE \R Refer to countermeasure of SBSW_TCPIP_FUNC_CALL_GET_REASSEMBLY_BUF_PTR

  \ID               SBSW_TCPIP_FUNC_CALL_FORWARD_TO_UL_RX_IND
    \DESCRIPTION    Function-call with valid parameters as described below:
                    - LocalAddrIdx: Valid as described in SBSW_TCPIP_CSL01_IDX_CALLER.
                    All other parameters are valid as described in SBSW_TCPIP_FUNC_CALL_REASSEMBLY_RX_IND (Countermeasures have been taken over from there).
    \COUNTERMEASURE \R CM_TCPIP_IP_HDR_LEN_BYTE
                    \R CM_TCPIP_IP_TOTAL_LEN_BYTE

  \ID               SBSW_TCPIP_FUNC_CALL_CHECKSUM_ADD_RX_IND
    \DESCRIPTION    Function-call with valid parameters as described below:
                    - Pointer variable DataPtr is valid as described in CM_TCPIP_IP_HDR_PTR_RX_IND.
                    - ipHdrLenByte is valid due to CM_TCPIP_IP_HDR_LEN_BYTE.
                    - All other parameters of this function-call are constants and thus valid or come valid from caller.
    \COUNTERMEASURE \R CM_TCPIP_IP_HDR_PTR_RX_IND
                    \R CM_TCPIP_IP_HDR_LEN_BYTE
                    \R The consistency between DataPtr and the length available in the memory(-array) (LenByte) it points to is ensured by these runtime checks:
                       - (ipHdrLenByte >= IPV4_IP_DEF_HEADER_LENGTH_BYTE)
                       - (ipHdrLenByte <= ipTotalLenByte)
                       IpBase_TcpIpChecksumAdd()'s parameter LenByte is given by the ipHdrLenByte which is thus valid.
                       The LenByte vs. DataPtr CONSTRAINT of TcpIp_IpV4_RxIndication() is checked by this runtime check:
                       - (LenByte >= ipTotalLenByte)
                       Thus the consistency of the complete received IPv4 packet (in the memory(-array) pointer to by DataPtr), including its 20-byte header structure is ensured.

  \ID               SBSW_TCPIP_FUNC_CALL_IS_DUPL_DHCP_ADDR
    \DESCRIPTION    Function-call with valid parameters as described below:
                    - ipV4CtrlIdx is valid as described in SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER
                      (I.e.: Look-up using CSL-macro TcpIp_GetIpV4CtrlIdxOfEthIfCtrl() using parameter EthIfCtrlIdx which comes valid from caller.)
                    - local array srcAddr is initialized with valid values from Pointer variable DataPtr which is valid as described in CM_TCPIP_IP_HDR_PTR_RX_IND
                    - PhysAddrPtr is valid as described in SBSW_TCPIP_VALID_PTR_DET_CHECKED
    \COUNTERMEASURE \R CM_TCPIP_IP_HDR_PTR_RX_IND

  \ID               SBSW_TCPIP_FUNC_CALL_AFTER_ALL_CHECKS_RX_IND_LOC_ADDR_IDX
    \DESCRIPTION    Function-call with valid parameters as described below:
                    - localAddrV4Idx is valid due to CM_TCPIP_IPV4_SPECIFIC_LOC_ADDR_IDX
                    - ipV4CtrlIdx is valid as described in SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER, i.e. using a:
                      - look-up using CSL-macro TcpIp_GetIpV4CtrlIdxOfEthIfCtrl() using parameter:
                      - EthIfCtrlIdx which comes valid from caller and is also DET-checked vs. TcpIp_GetSizeOfEthIfCtrl()
                    - DataPtr comes valid from caller as described in CM_TCPIP_IP_HDR_PTR_RX_IND and is DET-checked (CM_TCPIP_QMDEFINES).
    \COUNTERMEASURE \R CM_TCPIP_IP_HDR_PTR_RX_IND
                    \R CM_TCPIP_IPV4_SPECIFIC_LOC_ADDR_IDX
                    \R DET-check of EthIfCtrlIdx vs. TcpIp_GetSizeOfEthIfCtrl()
                    \M CM_TCPIP_QMDEFINES (DET)

  \ID               SBSW_TCPIP_PHYS_ADDR_TYPE_ARRAY_AS_PTR_PARAM
    \DESCRIPTION    A variable of type IpBase_EthPhysAddrType is an array of length IPBASE_ETH_PHYS_ADDR_LEN_BYTE (Should have value 6):
                    typedef uint8 IpBase_EthPhysAddrType[IPBASE_ETH_PHYS_ADDR_LEN_BYTE];
                    In case the first element of the IpBase_EthPhysAddrType is accessed and
                    the address of that element is used as a function call parameter of type uint8* and
                    IpBase_EthPhysAddrType is mentioned as CONSTRAINT in that parameters description then the parameter is valid for that call.
                    EXAMPLE: &destMacAddr[0] (whereat destMacAddr has to be a local variable of type IpBase_EthPhysAddrType)
                    The called function can then conduct writes to that array as described in SBSW_TCPIP_ARRAY_WRITE_TO_PHYS_ADDR_TYPE.
                    A typical use case is the call to function TcpIp_VCopyPhysAddr() which copies the complete 6-byte physical address.
    \COUNTERMEASURE \M CM_TCPIP_SIZE_OF_IPBASE_ETH_PHYS_ADDR_TYPE

  \ID               SBSW_TCPIP_ARRAY_WRITE_TO_PHYS_ADDR_TYPE
    \DESCRIPTION    A variable of type IpBase_EthPhysAddrType is an array of length IPBASE_ETH_PHYS_ADDR_LEN_BYTE (Should have value 6):
                    typedef uint8 IpBase_EthPhysAddrType[IPBASE_ETH_PHYS_ADDR_LEN_BYTE];
                    Thus all write accesses to variables of type IpBase_EthPhysAddrType are valid as soon as they do not exceed the index IPBASE_ETH_PHYS_ADDR_LEN_BYTE - 1
    \COUNTERMEASURE \M CM_TCPIP_SIZE_OF_IPBASE_ETH_PHYS_ADDR_TYPE

  \ID               SBSW_TCPIP_ARRAY_WRITE_TO_PHYS_ADDR_TYPE_COPY
    \DESCRIPTION    A local array of  of type IpBase_EthPhysAddrType is an array of length IPBASE_ETH_PHYS_ADDR_LEN_BYTE (Should have value 6):
                    typedef uint8 IpBase_EthPhysAddrType[IPBASE_ETH_PHYS_ADDR_LEN_BYTE], is passed to this function as a function argument.
                    Thus all write accesses to variables of type IpBase_EthPhysAddrType are valid as soon as they do not exceed the index IPBASE_ETH_PHYS_ADDR_LEN_BYTE - 1
    \COUNTERMEASURE \M CM_TCPIP_SIZE_OF_IPBASE_ETH_PHYS_ADDR_TYPE

  \ID               SBSW_TCPIP_FUNC_CALL_GET_NEXT_HOP
    \DESCRIPTION    There are two function calls to IpV4_Ip_VGetNextHopPhysAddr with valid parameters as described below:
                    - IpV4CtrlIdx: Local variable ipV4CtrlIdx is used and initialized with the return value of:
                      - IpV4_Ip_VGetLocalAddrIdxAndCtrlIdx(): The return value is checked as described in CM_TCPIP_IPV4_CTRL_IDX_CHECK.
                      - TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(): CSL-macro that gets a ipV4CtrlIdx that is checked vs. TcpIp_GetSizeOfIpV4Ctrl().
                                                             This scenario is equivalent to SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_LOCAL, i.e. no further CM is listed, here.
                    - DestAddr:
                      - Either Local variable destAddr is used which is initialized with the struct-member DestAddrPtr->sin_addr whereat DestAddrPtr comes valid from caller.
                      - Or member IpTxReqDescrPtr->DestAddrV4 is used, whereat IpTxReqDescrPtr comes valid from caller.
                    - SocketIdx:
                      - Either parameter SocketIdx is used which comes valid from caller.
                      - Or member IpTxReqDescrPtr->SockIdx is used, whereat IpTxReqDescrPtr comes valid from caller.
                    - NextHopPhysAddrPtr: Local variable destMacAddr is of type IpBase_EthPhysAddrType and thus is valid as described in:
                      - SBSW_TCPIP_ARRAY_WRITE_TO_PHYS_ADDR_TYPE and
                      - SBSW_TCPIP_PHYS_ADDR_TYPE_ARRAY_AS_PTR_PARAM.
    \COUNTERMEASURE \R CM_TCPIP_IPV4_CTRL_IDX_CHECK
                    \M CM_TCPIP_SIZE_OF_IPBASE_ETH_PHYS_ADDR_TYPE

  \ID               SBSW_TCPIP_FUNC_CALL_TRANSMIT_FRAGS
    \DESCRIPTION    Function-call with valid parameters as described below:
                    - ipV4CtrlIdx is a local variable that is initialized by IpTxReqDescrPtr->CtrlIdx which comes valid from caller.
                    - IpTxReqDescrPtr, IpProtocol, IpPayloadLen come valid from caller keeping the constraints of these parameter as follows:
                      - IpTxReqDescrPtr->BufIdx is valid as described in SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_PREPARATION (value comes from a checked ethBufIdx value from TCPIP_LL_ProvideTxBuffer())
                      - IpTxReqDescrPtr->SockIdx comes valid from these callers:
                        1. TcpIp_DhcpV4_VSendDhcpMsg() calls this function after letting its local variable ipTxReqDescrPtr being initialized by a call to IpV4_Ip_ProvideTxBuffer() whereat the SockIdx member
                           of the ipTxReqDescrPtr is initialized from the cfg. item TcpIp_IpV4General's member IpV4SocketDynDhcpIdx. Whether there is a DHCP socked configured is a 0:1 relation.
                           The following runtime check (SBSW_TCPIP_CM_R10) in TcpIp_DhcpV4_MainFunction():
                             TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(ipV4CtrlIdx) whereat ipV4CtrlIdx follows CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl[Dyn]()-1]
                           ensures that TcpIp_DhcpV4_VSendDhcpMsg() is called only in case DCHP is configured for at least one of the IPv4 controllers addresses.
                        2. IpV4_Icmp_VSendRawMessage() calls this function after letting its local variable ipTxReqDescrPtr being initialized by a call to IpV4_Ip_ProvideTxBuffer()
                           or IpV4_Ip_FragmentProvideTxBuffer() whereat the SockIdx member of the ipTxReqDescrPtr is initialized from the cfg. item TcpIp_IpV4General's member IpV4SocketDynIcmpIdx.
                        3. TcpIp_VIpTransmit() calls this function whereat parameter IpTxReqDescrPtr comes with valid from these callers:
                           - TcpIp_Udp_SendRetryQueueIfPossible() and TcpIp_Udp_VTransmit() whereat the UDP subcomponent uses IpV4_Ip_FragmentProvideTxBuffer() and IpV4_Ip_ProvideTxBuffer()
                             to initialize IpTxReqDescrPtr->SockIdx with a SockIdx from configuration which is looked up in UL calls to TcpIp_UdpTransmit() using the given, DET checked SockedId (SNV).
                    - &destMacAddr[0] is valid as described in SBSW_TCPIP_PHYS_ADDR_TYPE_ARRAY_AS_PTR_PARAM.
                    - calculateProtocolChecksum is a local variable that is properly initialized.
                    - ReqTxConfirmation, UlTxReqIdx come valid from caller.
                    This function is called from Tcp, Udp, DhcpV4 and IcmpV4.
                    At all these locations the parameter IpTxReqDescrPtr is given as the address of a local variable of type TcpIp_IpTxRequestDescriptorType and thus is valid.
    \COUNTERMEASURE \M CM_TCPIP_SIZE_OF_IPBASE_ETH_PHYS_ADDR_TYPE
                    \M CM_TCPIP_IPV4_GENERAL_DHCP_SOCKIDX

  \ID               SBSW_TCPIP_FUNC_CALL_FRAG_PROV_TX_BUFS
    \DESCRIPTION    Function-call with valid parameters as described below:
                    - ipV4CtrlIdx is checked as described in CM_TCPIP_IPV4_CTRL_IDX_CHECK.
                    - SocketIdx, *IpBufferLenPtr, IpTxReqDescrPtr: These parameters come valid from caller.
                    This function is called from Tcp, Udp, DhcpV4 and IcmpV4.
                    At all these locations the parameter IpTxReqDescrPtr is given as the address of a local variable of type TcpIp_IpTxRequestDescriptorType and thus is valid.
    \COUNTERMEASURE \R CM_TCPIP_IPV4_CTRL_IDX_CHECK

  \ID               SBSW_TCPIP_LL_PROVIDE_TX_BUF_FRAGM
    \DESCRIPTION    Function-call with valid parameters as described below:
                    - EthIfCtrlIdx: Parameter is looked up using CSL-macro TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx).
                      The macro parameter IpV4CtrlIdx is valid from caller (i.e. checked to be < TcpIp_GetSizeOfIpV4Ctrl())
                      The lookup results in a valid EthIfCtrlIdx as described in SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER.
                    - FrameType: IPV4_IP_FRAME_TYPE is a constant and thus valid.
                    - Priority: This parameter is calculated using the IPv4 macro IPV4_GET_SOCKET_ETHIF_FRAME_PRIO(SocketIdx, IpV4CtrlIdx)
                      - SocketIdx, IpV4CtrlIdx come valid from caller
                      - Depending on the value of TcpIp_GetTransferBlockOfIpV4SocketDyn(IpV4SocketIdx).flags one of the two following CSL-macros determines the value of Priority:
                        - TcpIp_GetTransferBlockOfIpV4SocketDyn(IpV4SocketIdx).EthIfFramePrio
                        - TcpIp_GetFramePrioDefaultOfIpV4Ctrl(IpV4CtrlIdx)
                      Accessing runtime data via TcpIp_GetTransferBlockOfIpV4SocketDyn(IpV4SocketIdx) fulfills SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER.
                      Accessing config data via TcpIp_GetFramePrioDefaultOfIpV4Ctrl fulfills SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER.
                    - &ethBufIdx, &ethBufPtr, &ethBufLen: These pointer parameters are initialized using the address of local variables and are thus valid.
                      The local variables used here do not have to be initialized, because all 3 parameters are [out] parameters.
    \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib.

  \ID               SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_PREPARATION
    \DESCRIPTION    Array write access using a CSL-indirection based index as basis but adding a local variable as index offset.
                    The CSL-macro TcpIp_SetEthBufIdxNextOfBuf2TxReqMap() is used to access a CSL-generated array of runtime-data structs in RAM.
                    The Buf2TxReqMap array models a linked list to administer Tx-buffers provided by EthIf. Linking is done only in case of fragmentation.
                    There is only one Buf2TxReqMap array for all Ip V4 controllers.
                    For each Ip V4 controller there is a start- and an end-index to track Buffers provided by EthIf for Tx-requests on that controller.
                    These indexes are read by the following CSL-macros that are accessed by IpV4CtrlIdx which comes valid from caller:
                    - TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(IpV4CtrlIdx) (called 'startIdx' in the subsequent paragraph)
                    - TcpIp_GetBuf2TxReqMapEndIdxOfIpV4Ctrl(IpV4CtrlIdx)
                    Thus reading start- and end-index values fulfills SBSW_TCPIP_CSL02_IDX_BASED_ON_CSL01_CALLER.
                    The buffer index value of the EthIf 'ethBufIdx' is used as offset in the section of the Buf2TxReqMap that is assigned to a particular IPv4 controller.
                    These local variables are used to administer and store the offsets:
                    - ethBufIdx and
                    - prevEthBufIdx
                    Variable prevEthBufIdx is only initialized with values of ethBufIdx. Variable prevEthBufIdx is only set and used after ethBufIdx has a valid value.
                    Variable ethBufIdx is used only after the call to TCPIP_LL_ProvideTxBuffer() has returned BUFREQ_OK.
                    --> This is checked by runtime check SBSW_TCPIP_CM_R7:
                        if (BUFREQ_OK == retVal)
                    The EthIf has to return a valid value for ethBufIdx.
                    --> This is checked by runtime check SBSW_TCPIP_CM_R8:
                        if ((startIdx + ethBufIdx) < TcpIp_GetBuf2TxReqMapEndIdxOfIpV4Ctrl(IpV4CtrlIdx))
                    The linking from the first Tx-buffer reserved at the EthIf can start only in case at least "the first fragment" has a provided Tx-buffer.
                    This fact is tracked by prevEthBufIdx being != IPV4_IP_TX_BUF_IDX_INV or not.
                    --> This is checked by runtime check SBSW_TCPIP_CM_R9:
                        if (prevEthBufIdx == IPV4_IP_TX_BUF_IDX_INV)
                    In case prevEthBufIdx == IPV4_IP_TX_BUF_IDX_INV prevEthBufIdx is not used to add it to startIdx and thus no invalid array access happens.
                    When prevEthBufIdx != IPV4_IP_TX_BUF_IDX_INV this means that a valid ethBufIdx (SBSW_TCPIP_CM_R7) has been assigned to prevEthBufIdx,
                    because there is only one assignment to prevEthBufIdx at SBSW_TCPIP_CM_R11.
    \COUNTERMEASURE \R The return value of TCPIP_LL_ProvideTxBuffer has to be BUFREQ_OK
                    \R The sum of startIdx and the returned ethBufIdx of TCPIP_LL_ProvideTxBuffer has to be <endIdx.
                    \R The value of prevEthBufIdx has to be != IPV4_IP_TX_BUF_IDX_INV

  \ID               SBSW_TCPIP_ETH_BUF_CONCAT_LIST_FOR_FRAGM
    \DESCRIPTION    CONCEPT: All over the code of TcpIp_IpV4.c the runtime admin data of particular IP packets to be transmitted (i.e. EthIf-buffers)
                    consist of a set of 5 values: BufPtr, BufLen, BufIdxNext, SocketDynIdx and UlTxReqIdx.
                    This set is fixedly associated together and stored by these CSL-macros (Get and Set - Set is listed, below):
                    - TcpIp_SetEthBufPtrOfBuf2TxReqMap()
                    - TcpIp_SetEthBufLenOfBuf2TxReqMap()
                    - TcpIp_SetEthBufIdxNextOfBuf2TxReqMap()
                    - TcpIp_SetSocketDynIdxOfBuf2TxReqMap()
                    - TcpIp_SetUlTxReqIdxOfBuf2TxReqMap()
                    (The last 2 items are written after valid initialization of at least one element of the (possibly concatenated)
                     IP packet administration data as described in SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_PREPARATION.)
                    The admin data related to one particular EthIf-buffer:
                    - is set in function IpV4_Ip_VFragmentProvideTxBuffers().
                    - follows the constraints described in the below concept:
                      - The lower layer offers memory to assemble / store IP packets to be transmitted (EthIf-buffers).
                      - When the lower layer answers the request for an EthIf-buffer positively by returning BUFREQ_OK, it is assumed that:
                        - The returned buffer pointer is not only != NULL_PTR but also valid.
                        - The memory the returned buffer pointer points to has at least the buffer size requested, before, i.e.:
                          ethBufLen = fragPayloadLen + IPV4_IP_DEF_HEADER_LENGTH_BYTE
                    Thus it is assumed that, when one item of the described 5-item-data-set is read out, it will fit to the other 2-items of the set.
                    All 5-item-data-sets are initialized in function IpV4_Ip_VFragmentProvideTxBuffers() where the validity of the conditions listed above is prepared like this:
                    1. ethBufLen being IPV4_IP_DEF_HEADER_LENGTH_BYTE larger than the payload to transfer:
                       SBSW_TCPIP_CM_R12: ethBufLen = (fragPayloadLen + IPV4_IP_DEF_HEADER_LENGTH_BYTE);
                    2. EthBufIdxNext + TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(IpV4CtrlIdx) will never exceed TcpIp_GetBuf2TxReqMapEndIdxOfIpV4Ctrl(IpV4CtrlIdx)
                       as described in SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_PREPARATION (Refer to runtime-check SBSW_TCPIP_CM_R8).
                    3. When looking at a valid element in the Buf2TxReqMap-RAM-array at index ethBufIdx then the EthBufIdxNext-member of that element is either
                       - IPV4_IP_TX_BUF_IDX_INV for a non fragmented transmission or
                       - a valid ethBufIdx for a fragmented transmission.
                       This is ensured in function IpV4_Ip_VFragmentProvideTxBuffers() as described in SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_PREPARATION.
    \COUNTERMEASURE \R IpV4_Ip_VFragmentProvideTxBuffers() which builds up the concatenated list of Tx-buffers requested from the EthIf has to be called prior to
                       IpV4_Ip_VTransmitFragments()        which actually uses the concatenated list of requested Tx-buffers.
                       IpV4_Ip_VTransmitFragments()        ensures this by rejecting calls whose parameters to not point to a valid entry point in the concatenated list of admin data.
                                                           This is done by check of the while-loop: (ethBufIdx != IPV4_IP_TX_BUF_IDX_INV) at marker SBSW_TCPIP_CM_R13.

  \ID               SBSW_TCPIP_FUNC_CALL_CHECKSUM_ADD_TX_FRAGM
    \DESCRIPTION    Function-calls with valid parameters as described below:
                    DataPtr (fragPayloadPtr) and LenByte (fragPayLoadLen) are read in lines 2481-2483 and are consistent to each other as described in SBSW_TCPIP_ETH_BUF_CONCAT_LIST_FOR_FRAGM.
                    - DataPtr: Local variable fragPayloadPtr is initialized from local variable ethPayloadPtr using an array access at position IPV4_IP_DEF_HEADER_LENGTH_BYTE.
                               Checksum calculation implies that at least one byte of payload is present, i.e.:
                               ethPayloadPtr has to be >= IPV4_IP_DEF_HEADER_LENGTH_BYTE + 1 (>IPV4_IP_DEF_HEADER_LENGTH_BYTE).
                               ethPayloadPtr is initialized validly in function IpV4_Ip_VFragmentProvideTxBuffers() as described in SBSW_TCPIP_ETH_BUF_CONCAT_LIST_FOR_FRAGM.
                    - LenByte: As described for the parameter DataPtr, above, the local variable fragPayloadLen is initialized assuming that there is >= 1 bytes payload present:
                               fragPayloadLen = ethPayloadLen - IPV4_IP_DEF_HEADER_LENGTH_BYTE
                               ethPayloadLen comes from a value calculated vice versa (i.e. fragPayloadLen + IPV4_IP_DEF_HEADER_LENGTH_BYTE)
                               in function IpV4_Ip_VFragmentProvideTxBuffers() as described in SBSW_TCPIP_ETH_BUF_CONCAT_LIST_FOR_FRAGM.
                    - Checksum: Local variable protocolChecksum is properly initialized - either:
                                - with '0' at its declaration or, depending on protocol needs, initialized
                                - with the return value of function TcpIp_VCalcIpV4PseudoHdrChecksum()
                    - Stop: This parameter is given as a constant (TRUE or FALSE) and thus is valid.
                    The ethBufIdx read from the parameter IpTxReqDescrPtr->BufIdx has to identify a valid entry point (ethBufIdx != IPV4_IP_TX_BUF_IDX_INV)
                    The caller ensures that IpTxReqDescrPtr->BufIdx has a valid value != IPV4_IP_TX_BUF_IDX_INV.
                    As the while-loop in IpV4_Ip_VTransmitFragments() processes the linked list of all EthIf-provided Tx-buffers the execution might come to a point when
                    the last element of the linked list has been processed and there are no further elements.
                    Thus the while-loop checks ethBufIdx to be != IPV4_IP_TX_BUF_IDX_INV, following the concept described in CM_TCPIP_ETH_TX_BUF_IDX.
    \COUNTERMEASURE \R CM_TCPIP_ETH_TX_BUF_IDX

  \ID               SBSW_TCPIP_FUNC_CALL_PROT_CHECKSUM
    \DESCRIPTION    Function-call with valid parameters as described below:
                    - IpProtocol comes valid from caller.
                    - protocolChecksum: Local variable that is properly initialized - either:
                      - with '0' at its declaration or, depending on protocol needs, initialized
                      - with the return value of function TcpIp_VCalcIpV4PseudoHdrChecksum() or
                      - with the return value of function IpBase_TcpIpChecksumAdd().
                    - protocolHdrPtr: Local pointer variable that points to the IPV4_IP_DEF_HEADER_LENGTH_BYTE-th position of the EthIf-buffer.
                                      The EthIf-buffer is a memory area that is at least IPV4_IP_DEF_HEADER_LENGTH_BYTE + 1 byte long as described in SBSW_TCPIP_ETH_BUF_CONCAT_LIST_FOR_FRAGM.
                                      The EthIf-buffer is read using CSL-macro:
                                      TcpIp_GetEthBufPtrOfBuf2TxReqMap(TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(IpV4CtrlIdx) + IpTxReqDescrPtr->BufIdx)
                                      This access is valid as described in SBSW_TCPIP_ETH_BUF_CONCAT_LIST_FOR_FRAGM because
                                      - IpV4CtrlIdx comes valid from caller (Qualified usecase CSL03 of the ComStackLib)
                                      - IpTxReqDescrPtr->BufIdx comes valid from caller.
    \COUNTERMEASURE \R CM_TCPIP_ETH_TX_BUF_IDX

  \ID               SBSW_TCPIP_WRITE_IPV4_HDR_ETH_PAYLOAD
    \DESCRIPTION    The payload of an ethernet packet is written into memory that is located in the EthIf.
                    The local pointer ethPayloadPtr and local length ethPayloadLen information have been retrieved from admin data for given IpV4CtrlIdx which comes valid from caller.
                    The values retrieved from the admin data are initialized with valid values as described in concept SBSW_TCPIP_ETH_BUF_CONCAT_LIST_FOR_FRAGM.
                    Thus the size of the array pointed to by ethPayloadPtr is at least the size of an IPv4 packet's header structure respectively IPV4_IP_DEF_HEADER_LENGTH_BYTE.
                    Due to CM_TCPIP_IPV4_HDR_STRUCT_SIZE the IPV4_IP_DEF_HEADER_LENGTH_BYTE is at least the size of an IPv4 header, 20 bytes.
                    The index values TCPIP_IPV4_HDR_OFS_* are used to write 1, 2 or 4 byte values into a RAM-array to form the C-struct IpV4_IpHdrType.
                    Thus they have to have values that are 1, 2 or 4 bytes less than IPV4_IP_DEF_HEADER_LENGTH_BYTE.
                    This is ensured by CM_TCPIP_IPV4_HDR_STRUCT_ACCESS and thus the array write is ok.
                    ethPayloadPtr is initialized validly in function IpV4_Ip_VFragmentProvideTxBuffers() as described in SBSW_TCPIP_ETH_BUF_CONCAT_LIST_FOR_FRAGM.
    \COUNTERMEASURE \R CM_TCPIP_IPV4_HDR_STRUCT_ACCESS
                    \R CM_TCPIP_IPV4_HDR_STRUCT_SIZE

  \ID               SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_USAGE
    \DESCRIPTION    Array write access using a CSL-indirection based index as basis but adding a local variable as index offset.
                    The CSL-macros TcpIp_SetUlTxReqIdxOfBuf2TxReqMap() and TcpIp_SetSocketDynIdxOfBuf2TxReqMap()
                    are used to access a CSL-generated array of runtime-data structs in RAM. As described in:
                    - SBSW_TCPIP_ETH_BUF_CONCAT_LIST_FOR_FRAGM and
                    - SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_PREPARATION
                    the 5 members of a logical element of the Buf2TxReqMap are valid as soon as that element has been initialized in IpV4_Ip_FragmentProvideTxBuffers().
                    The function IpV4_Ip_VTransmitFragments() does not access an element of the Buf2TxReqMap in case the particular element is uninitialized.
                    Thus the write access to the elements UlTxReqIdx and SocketDynIdx is valid, using
                    TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(IpV4CtrlIdx) with IpV4CtrlIdx coming valid from caller
                    and a valid value for ethBufIdx which is initialized from IpTxReqDescrPtr->BufIdx which comes valid from caller.
                    The value written is IpTxReqDescrPtr->SockIdx which comes valid from caller, also.
    \COUNTERMEASURE \R Refer to runtime checks of SBSW_TCPIP_ETH_BUF_CONCAT_LIST_FOR_FRAGM and SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_PREPARATION

  \ID               SBSW_TCPIP_FUNC_CALL_ETHIF_TRANSMIT
    \DESCRIPTION    Function-call with valid parameters as described below:
                    - CtrlIdx: TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx):
                      Parameter is looked up using CSL-macro TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx).
                      The macro parameter IpV4CtrlIdx is valid from caller (i.e. checked to be < TcpIp_GetSizeOfIpV4Ctrl())
                      The lookup results in a valid EthIfCtrlIdx as described in SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER.
                    - BufIdx: ethBufIdx is initialized from IpTxReqDescrPtr->BufIdx which comes valid from caller.
                    - FrameType: IPV4_IP_FRAME_TYPE is a constant and thus valid.
                    - TxConfirmation: ReqTxConfirmation either comes valid from caller or the constant FALSE is used and thus is valid.
                    - LenByte: FragTotalLen comes valid from caller.
                    - PhysAddrPtr: DestPhysAddrPtr comes valid from caller
    \COUNTERMEASURE \R Refer to runtime checks of SBSW_TCPIP_ETH_BUF_CONCAT_LIST_FOR_FRAGM and SBSW_TCPIP_BUF_TO_TX_REQ_MAP_FRAGM_PREPARATION

  \ID               SBSW_TCPIP_FUNC_CALL_IPV4_ARP_GETPHYSICALADDRESS
    \DESCRIPTION    Function call with valid parameters as described below:
                    - IpV4CtrlIdx: This index is looked up from CSL-generated data, following these steps:
                      - Parameter EthIfCtrlIdx that comes valid from caller and
                      - EthIfCtrlIdx is used to look up the related IpV4CtrlIdx using macro TcpIp_GetIpV4CtrlIdxOfEthIfCtrl() that uses a modelled indirection as described by CSL03
                    - SocketIdx: This index is initialized with the value IPV4_INV_SOCK_IDX with is valid for this parameter according to the CONSTRAINT of the called function.
                    - NetAddr: The parameter IpAddr which comes valid from caller is used as value for this parameter.
                    - PhysAddrPtr: The parameter PhysAddrPtr comes valid from caller is used as value for this parameter.
                    - InitRes: The parameter InitRes comes valid from caller is used as value for this parameter.
    \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib.

  \ID               SBSW_TCPIP_WRITE_TRANSFER_BLOCK
    \DESCRIPTION    A member of the C-struct TcpIp_TransferBlockOfIpV4SocketDynPtrType pointed to by transferBlockPtr is written, whereat:
                    - transferBlockPtr is a member of C-struct-member of the C-struct-array IpV4SocketDyn whereat:
                      - the element within that array is looked up from generated data using CSL macro TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(IpV4SocketIdx) whereat:
                      - SocketIdx comes valid from caller following the CSL01-compliant CONSTRAINT [0..TcpIp_GetSizeOfIpV4SocketDyn()-1]
                    Thus for the lookup of transferBlockPtr no countermeasure is required.
    \COUNTERMEASURE \N The transferBlockPtr is looked up CSL01 compliant as described in SBSW_TCPIP_CSL01_IDX_CALLER.

  \ID               SBSW_TCPIP_WRITE_TRANSFER_BLOCK_ETH_PHYS_ADDR
    \DESCRIPTION    The member PhysDestAddr[] of C-struct TcpIp_TransferBlockOfIpV4SocketDynPtrType is written in RAM.
                    As described in SBSW_TCPIP_WRITE_TRANSFER_BLOCK no countermeasure is required for looking up transferBlockPtr.
                    PhysDestAddr[] is written at positions 0-5, i.e. the array size has to be 6.
                    Countermeasure CM_TCPIP_SIZE_OF_IPBASE_ETH_PHYS_ADDR_TYPE ensures that the upper limit IPBASE_ETH_PHYS_ADDR_LEN_BYTE of loops accessing the array is 6.
    \COUNTERMEASURE \M CM_TCPIP_SIZE_OF_IPBASE_ETH_PHYS_ADDR_TYPE

  \ID               SBSW_TCPIP_FUNC_CALL_ADDR_CALLOUT
    \DESCRIPTION    The callout to involve the upper layer in IP address generation is called.
                    The presence of the function is optional. Thus the value of the pointer is checked to be non-NULL in implementation.
    \COUNTERMEASURE \R The value of the pointer is checked to be non-NULL in the if-statement encapsuling the function call.

  \ID               SBSW_TCPIP_FRAGM_REASSEMBLY_DESC_ARRAY_USAGE
    \DESCRIPTION    CONCEPT: All over the code of TcpIp_IpV4.c the runtime admin data for reassembly of received IP packets is stored in an array of type IpV4_Ip_ReassemblyBufferDescType.
                    The array contains buffer descriptor C-structs. The index to a position in that array is like a handle for a fragmentation-buffer that is in use.
                    The so called buffer descriptor itself is a structure storing the information about
                    - the current usage of the related reassembly buffer
                    - the information about the IPv4 packet that reassembly is currently done on.

                    The configuration C-struct of each IPv4 controller has a member FragmentationConfigIdx which has the value:
                    - TCPIP_NO_FRAGMENTATIONCONFIGIDXOFIPV4CTRL in case this IPv4 controller does not support fragmentation, or the value:
                    - [0..TcpIp_GetSizeOfFragmentationConfig()-1] in case the controller supports fragmentation and thus has a fragmentation config and thus may use buffer descriptors for reassembly.
                    Each fragmentation config referenced uses its members ReassemblyBufferDescStartIdx and ReassemblyBufferDescEndIdx to reference
                    a range of "buffer descriptors" of type IpV4_Ip_ReassemblyBufferDescType which are
                    - stored in an array of this type and are
                    - retrieved via CSL-macro:
                      - TcpIp_GetReassemblyBufferDescDyn() or
                      - TcpIp_GetAddrReassemblyBufferDescDyn()
                    Each reassembly buffer descriptor can be marked used or unused by its member variable 'Status' which has one of these values:
                    - IPV4_IP_REASSEMBLY_BUF_STATUS_UNUSED
                    - IPV4_IP_REASSEMBLY_BUF_STATUS_IN_PROGRESS
                    - IPV4_IP_REASSEMBLY_BUF_STATUS_FAILED
                    - IPV4_IP_REASSEMBLY_BUF_STATUS_COMPLETE
                    The buffer descriptors are initialized in function IpV4_Ip_VReassemblyInitBuffers() called in IpV4_Ip_Init().
                    From this array of buffer descriptors, each IPv4 controller may use the range it is associated with according to the IPv4 controllers configuration.
                    The actual buffer is:
                    - a part from one linear buffer that is
                    - divided into parts using start and end index values in the configuration array that has one C-struct of type TcpIp_ReassemblyBufferDescType that is related 1:1 to each
                    - buffer descriptor of the IpV4_Ip_ReassemblyBufferDescType, mentioned, above.
                    Reassembly buffers or reassembly buffer descriptors are arrays of the same size and thus these are CSL02-compliant lookups.
                    Any buffer descriptor is identified and accessed by the buffer descriptor index which is determined by function IpV4_Ip_VReassemblyFindBufferDesc().
                    in case no free buffer descriptor (and thus no free buffer for reassembly) is available, this is indicated by the value IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV in the particular index variable.
                    IpV4_Ip_VReassemblyFindBufferDesc() is able to properly find a free buffer descriptor (or not) and follow the above convention because:
                    - IpV4_Ip_RxIndication() calls IpV4_Ip_ReassembleAndForwardToUpperLayer() in any case (IPv4 controller supports fragmentation or not)
                    - IpV4_Ip_ReassembleAndForwardToUpperLayer() calls IpV4_Ip_VReassemblyRxIndication() only in case the affected IPv4 controller ACTUALLY supports Rx-fragmentation
                      (refer to CONSTRAINT of the given IpV4CtrlIdx).
                      This is done by:
                      - the following boolean check which is a CSL03-compliant check for the 0:1 relation expressing the presence (or absence) of fragmentation support for an IPv4 controller:
                        TcpIp_IsFragmentationConfigUsedOfIpV4Ctrl(IpV4CtrlIdx)
                      - the (defensive) number-check that at least one reassembly buffer descriptor is configured:
                        TcpIp_IsReassemblyBufferDescUsedOfFragmentationConfig(FragmentationConfigIdx)
                        Note: This defensive check might be removed in future when a validator in the CFG5-Gen-Tool checks the presence of at least one buffer (descriptor) when reassembly is configured.
                    - IpV4_Ip_VReassemblyRxIndication() and the functions called by it, later on, are then able to access:
                      - a valid reassembly buffer configuration for the given IPv4 controller with at least one reassembly buffer [descriptor] configured.
                      - a valid fragmentation config in a CSL03-compliant way for a given IpV4CtrlIdx which comes valid from caller following CSL01-compliant CONSTRAINT [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
                      - the sub-array of all reassembly buffer descriptors belonging to that fragmentation config. using the fragment the part of the array.
                      That sub-array is identified by IpV4_Ip_VReassemblyFindBufferDesc() by the CSL03-compliant 1:N indirection using these index values of the fragmentation config:
                      - TcpIp_GetReassemblyBufferDescStartIdxOfFragmentationConfig()
                      - TcpIp_GetReassemblyBufferDescEndIdxOfFragmentationConfig()
                      The modelled CSL03-compliant 1:N indirection points to the buffer descriptor which is accessed via TcpIp_GetAddrReassemblyBufferDescDyn() and the contained index is returned if
                      - the descriptor is unused or:
                      - fragmentation is finalized for an IPv4 fragmented transfer using this descriptor.
                      If no unused descriptor is found the function returns IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV.
                      The IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV-convention is used for the returned index values in [out] parameters:
                      - OldestDescIdxPtr and:
                      - UnusedDescIdxPtr.
                      These [out] parameters are used by the function IpV4_Ip_VReassemblyGetBufferDesc() which returns at least one reassembly buffer [descriptor] that is available for use or IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV, otherwise.
                      It uses a runtime-check descIdx != IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV and only if this is TRUE it reads the buffer descriptor CSL03-compliant using:
                      - TcpIp_GetAddrReassemblyBufferDescDyn( usedDescIdx )
                      The resulting pointer reassemblyBufDescPtr is valid thus.
    \COUNTERMEASURE \N The measures in implementation described in the CONCEPT in the DESCRIPTION-section, above, ensure that pointer reassemblyBufDescPtr is valid.

  \ID               SBSW_TCPIP_REASSEMBLY_DESC_PTR_FROM_FOUND_IDX
    \DESCRIPTION    The local pointer reassemblyBufDescPtr is initialized using CSL macro TcpIp_GetAddrReassemblyBufferDescDyn() on the array of buffer descriptors as described in CONCEPT SBSW_TCPIP_FRAGM_REASSEMBLY_DESC_ARRAY_USAGE.
                    The index in that array, 'usedDescIdx', is determined by function IpV4_Ip_VReassemblyFindBufferDesc().
                    from the IpV4_Ip_VReassemblyFindBufferDesc()
    \COUNTERMEASURE \N The pointer that is dereferenced and written is valid due to the CONCEPT descriped in SBSW_TCPIP_FRAGM_REASSEMBLY_DESC_ARRAY_USAGE.

  \ID               SBSW_TCPIP_REASSEMBLY_BUF_PARTITIONING
    \DESCRIPTION    CONCEPT: Every buffer descriptor of an IPv4 controller has assigned its own reassembly buffer.
                    This reassembly buffer is a segment of an one-piece, flat buffer, allocated for all reassembly activities.
                    The associated buffer segment is defined by a start- and an end-index which both are stored in the array of C-structs named:
                    - TcpIp_ReassemblyBufferDesc[] in the configuration. this array has the same size as the array of buffer descriptors,
                    - which, due to the same size, yields a CSL02-compliant lookup.
                    The start of the buffer segment to be used by a particular buffer descriptor is retrieved by an array access into the flat, overall buffer using the index:
                    - reassemblyBufferStartIdxOfReassemblyBufferDesc which is read from the config using macro:
                    - TcpIp_GetReassemblyBufferStartIdxOfReassemblyBufferDesc(usedReassemblyBufferDescIdx)
                    - Index usedDescIdx is returned by function IpV4_Ip_VReassemblyFindBufferDesc() and is valid as soon as it is != IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV
                      according to the CONCEPT described in SBSW_TCPIP_FRAGM_REASSEMBLY_DESC_ARRAY_USAGE
    \COUNTERMEASURE \R usedDescIdx != IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV

  \ID               SBSW_TCPIP_RX_FRAGMENT_ADMIN_DATA
    \DESCRIPTION    CONCEPT: The assembly of IPv4 packet fragments that come in out of order is done in a flat, linear buffer.
                    In the out of order case gaps remain inbetween the fragments. These gaps are used to store admin data regarding
                    1. the offset (i.e. the start position) of the next gap and
                    2. the size of the current gap.
                    Both values are 16-bit values because the max. length of an IPv4 packet is 16-bit.
                    As there is no gap in front of the first fragment (because the fragment starts at buffer position '0') the buffer descriptor as described in CONCEPTs
                    - SBSW_TCPIP_RX_FRAGMENT_REASSEMBLY and
                    - SBSW_TCPIP_REASSEMBLY_BUF_PARTITIONING
                    have gotten a member NextGapOfs that points to the first admin data couple of 16-bit values.
                    To write the 2 admin data values the following offset constants are used which are to be added to the start-position of the gap-area in the buffer-segment of a buffer descriptor:
                    - IPV4_IP_REASSEMBLY_BUF_NEXT_GAP_OFS (0) is valid to write the 16-bit offset of the next gap into the buffers gap-area or using
                    - IPV4_IP_REASSEMBLY_BUF_GAP_SIZE_OFS (2) is valid to write the size of the current gap into the buffers gap-area.
                    Writing 2 16-bit values into the buffer leads to the following constraint:
                    The minimum size of a buffer segment associated to a buffer descriptor has to be at least 4 bytes.
    \COUNTERMEASURE \N The minimum value in the description file of the configuration value related to MaxPacketSize of all FragmentationConfig is 4.
                       Thus the MaxPacketSize values of all FragmentationConfigs have the value of 4 at least.

  \ID               SBSW_TCPIP_RX_FRAGMENT_REASSEMBLY
    \DESCRIPTION    CONCEPT: Each IPv4 packet fragment has a fragment offset in the overall IPv4 packet.
                    It is stored in a flat buffer as described in CONCEPT SBSW_TCPIP_FRAGM_REASSEMBLY_DESC_ARRAY_USAGE.
                    Gaps occur in case packet fragments arrive out of order and are stored at their particular offset in a flat buffer.
                    The administration of these gaps is described in CONCEPT SBSW_TCPIP_RX_FRAGMENT_ADMIN_DATA.

                    As soon as the first IPv4 packet fragment has been received, 2 things are done:
                    1. in function IpV4_Ip_VReassemblyGetBufferDesc() a free buffer descriptor and a suitable buffer belonging to the descriptor is found using IpV4_Ip_VReassemblyFindBufferDesc().
                       After that in the first function:
                       - the offset of the first gap is set to IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS (65535, invalid value, because at the max. size of an IPv4 packet no gap can occur, anymore)
                         when variable firstGapOfs is written to the admin area of the assigned buffer segment.
                       - the size of the first gap is set to the size of the reassembly buffer of the descriptor (e.g. 10000) when variable firstGapSize is written to the admin area of the assigned buffer segment.
                      Writing these 2 admin values is done as described in CONCEPT SBSW_TCPIP_RX_FRAGMENT_ADMIN_DATA and thus valid.
                    2. in function IpV4_Ip_VReassemblyHandleGaps(), when handling the first fragment received
                       - the size of the reassembly buffer that is used for this reception read out again (as initially written by IpV4_Ip_VReassemblyGetBufferDesc())
                         and is used as initial value for the upper limit of all gaps that can be handled,
                       - so the reassembly buffers size can never be exceeded.

                    EXAMPLE: In case a 10000 byte reassembly buffer has been configured and the transfer consists of 2 fragmented IP packets
                    then after the first (e.g.) 16 byte packet the gap-size is calculated as
                    <gap size> = <buffer size> - <fragment size>
                    i.e.
                    9984       = 10000         - 16
                    The buffer size of 10000 is re-calculated (respectively "persists"), each time a new fragment of this reception was received because these items are stored:
                    - <next gap offset> (e.g. 16 as soon as the first 16-byte fragment has been received)
                    - <gap size> (e.g. 9984)
                    As the <next gap offset> of the very last gap is also the <end offset of uppermost fragment received> the IP payload length of
                    any newly received fragment can be used to calculate the buffer space that would be consumed to store the fragment, like this:
                    <possibly consumed len> = <end of set of uppermost fragment received> + <new fragment len>
                    i.e.
                    32378                   = 16                                          + 32362
                    The possibly consumed length (e.g. 32378) is always compared to the re-calculated (i.e. "persisted") value of 10000.
                    In case the possibly consumed length is larger than the buffer size the search for a matching gap in the reassembly buffer is ended
                    and thus the fragmentation process is ended by letting IpV4_Ip_VReassemblyHandleGaps() indicate:
                    - the value of gapOfs = IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS (65535) (the max size of an IP packet)
                    - AND a return value of the function of E_NOT_OK
                    to the caller IpV4_Ip_VReassemblyRxFragment() which will then end the re-assembly process for this reception with failure.
    \COUNTERMEASURE \N The described concept ensures that fragments that are larger than the buffer segment assigned to a buffer descriptor are detected and not stored in the buffer segment.

  \ID               SBSW_TCPIP_FUNC_CALL_WRITE_REASSEMBLY_BUF_INFO
    \DESCRIPTION    Function call with valid parameters as described below:
                    - Macro TCPIP_PUT_UINT16(Buffer, Offset, Value) maps to the function TcpIp_WriteUInt16() that writes an uint16 value to the given 'Buffer' memory location.
                    - The functions Buffer parameter is valid as described in CONCEPT SBSW_TCPIP_REASSEMBLY_BUF_PARTITIONING, for these cases:
                      - return value of TcpIp_GetAddrReassemblyBuffer() is directly used as parameter Buffer
                      - a local variable reassemblyBufPtr is initialized using the function TcpIp_GetAddrReassemblyBuffer() with a parameter that comes valid from caller.
                      - a parameter that comes valid from caller (and there has been initialized using TcpIp_GetAddrReassemblyBuffer()) is used
                    - Actually 2 calls to the function write two 16-bit values into the segments "admin area" which are described in CONCEPTs:
                      - SBSW_TCPIP_RX_FRAGMENT_ADMIN_DATA (because offsets IPV4_IP_REASSEMBLY_BUF_NEXT_GAP_OFS and IPV4_IP_REASSEMBLY_BUF_GAP_SIZE_OFS are used) and
                      - SBSW_TCPIP_RX_FRAGMENT_REASSEMBLY.
    \COUNTERMEASURE \N Refer to countermeasure of SBSW_TCPIP_RX_FRAGMENT_ADMIN_DATA

  \ID               SBSW_TCPIP_FUNC_CALL_GET_REASSEMBLY_BUF_PTR
    \DESCRIPTION    Function call with valid parameters as described below:
                    - IpV4_Ip_VReassemblyGetBufferPtr() is called to retrieve the buffer pointer of the buffer segment that is associated to the given buffer descriptor pointer.
                    - ReassemblyBufDescPtr is:
                      - Either given by local variable reassemblyBufDescPtr which is initialized:
                        - by the return value of the call to TcpIp_GetAddrReassemblyBufferDescDyn() which takes parameter
                        - reassemblyBufDescIdx (in one function also 'usedDescIdx') which is initialized:
                          - by the return value of the call to IpV4_Ip_VReassemblyGetBufferDesc() which takes parameters
                            - IpV4CtrlIdx and
                            - DataPtr which both come valid from caller.
                      - Or given by a parameter ReassemblyBufDescPtr from the caller which is initialized by the caller in the same way as described, above.
                        ReassemblyBufDescPtr might be passed far down along the callstack as there are many internal functions that handle the fragmentation/reassembly.
                      As described in CONCEPT SBSW_TCPIP_FRAGM_REASSEMBLY_DESC_ARRAY_USAGE:
                      - each IPv4 controller optionally has assigned an reassembly buffer.
                      - IpV4_Ip_VReassemblyRxIndication() is only called by caller IpV4_Ip_ReassembleAndForwardToUpperLayer() in case the affected IPv4 controller has assigned a buffer descriptor for reassembly.
                      Thus IpV4_Ip_VReassemblyGetBufferDesc() can either find:
                      1. the index of an unused buffer descriptor and assign it to the IPv4 packet given by DataPtr or
                      2. the index a buffer descriptor that was already assigned to an IPv4 reception fitting to the contents of the given DataPtr.
                      3. no index of a free buffer descriptor at all because all configured buffer descriptors of the fragmentation config of the given IPv4 controller are in use, already:
                         Then the invalid value IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV is returned as buffer descriptor.
                      The checks:
                        SBSW_TCPIP_CM_R3: if (usedDescIdx != IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV)
                        SBSW_TCPIP_CM_R4: if (reassemblyBufDescIdx == IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV)
                      prevent the index values from being used in case 3., above.
                      In the first 2 cases reassemblyBufDescIdx is valid and can be used to lookup the call-parameter ReassemblyBufDescPtr using CSL-macro TcpIp_GetAddrReassemblyBufferDescDyn() which
                      - returns the address of the related element of generated array of type IpV4_Ip_ReassemblyBufferDescType which is
                      - valid because the index used is result of a lookup using modelled indirection (CSL03 use case).
    \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib:
                       Only modelled indirections as described in CONCEPT SBSW_TCPIP_FRAGM_REASSEMBLY_DESC_ARRAY_USAGE are used to determine valid parameter 'reassemblyBufDescPtr' for the call to IpV4_Ip_VReassemblyGetBufferPtr()

  \ID               SBSW_TCPIP_WRITE_REASSEMBLY_BUF_DESC_PTR
    \DESCRIPTION    The member Status of the C-struct of type IpV4_Ip_ReassemblyBufferDescType pointed to by local variable reassemblyBufDescPtr is written.
                    The local variable is initialized validly using macro TcpIp_GetAddrReassemblyBufferDescDyn() as described in CONCEPT SBSW_TCPIP_FRAGM_REASSEMBLY_DESC_ARRAY_USAGE.
    \COUNTERMEASURE \R The countermeasures described in CONCEPT SBSW_TCPIP_FRAGM_REASSEMBLY_DESC_ARRAY_USAGE ensure that reassemblyBufDescPtr is valid..

  \ID               SBSW_TCPIP_FUNC_CALL_ADAPT_GAP
    \DESCRIPTION    Function call with valid parameters as described below:
                    - ReassemblyBufDescPtr is a pointer to a C-struct of type IpV4_Ip_ReassemblyBufferDescType which comes valid (as described in CONCEPT SBSW_TCPIP_RX_FRAGMENT_REASSEMBLY)
                      and non-NULL from caller of the function calling IpV4_Ip_VReassemblyHandleGaps().
                    - FragOfs comes valid from caller.
                    - FragEndOfs is calculated in local variable fragEndOfs as sum of the function parameters FragOfs and FragLen which both come valid from caller.
                    - ThisGapOfs is given by local variable gapOfs which is initially initialized from the member NextGapOfs of the ReassemblyBufDescPtr which comes valid from caller (including its members).
                      NextGapOfs contains the offset of the next gap.
                    - ThisGapEndOfs is given by local variable gapEndOfs which is calculated as gapOfs + gapSize from 2 local variables, whereat:
                      - gapOfs is valid as stated in the above description of parameter ThisGapOfs.
                      - gapSize is a local variable that is initialized by reading the admin data of the current gap using the buffer segment pointed to by local variable reassemblyBufPtr:
                        - the admin data is read by reading an uint16 at array offset <gap [start] offset> + IPV4_IP_REASSEMBLY_BUF_GAP_SIZE_OFS in the given reassemblyBufPtr, as described by CONCEPT SBSW_TCPIP_RX_FRAGMENT_ADMIN_DATA.
                        - reassemblyBufPtr is initialized by the return value of function call IpV4_Ip_VReassemblyGetBufferPtr() with argument ReassemblyBufDescPtr which comes valid from caller.
                    - PrevGapOfs is given by local variable prevGapOfs which is initialized:
                      - in the first run of the while-loop with IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS which stands for "no previous gap" and
                      - in all further runs of the while-loop with gapOfs which is valid as described for parameter ThisGapOfs, above.
                    - NextGapOfs is given by local variable nextGapOfs which is read from the admin data of the current gap using the buffer segment pointed to by local variable reassemblyBufPtr:
                      - the admin data is read by reading an uint16 at array offset <gap [start] offset> + IPV4_IP_REASSEMBLY_BUF_NEXT_GAP_OFS in the given reassemblyBufPtr, as described by CONCEPT SBSW_TCPIP_RX_FRAGMENT_ADMIN_DATA.
                      - reassemblyBufPtr is valid as described for parameter ThisGapEndOfs, above.
    \COUNTERMEASURE \N All parameters of the function call come directly or indirectly from caller.

  \ID               SBSW_TCPIP_FUNC_CALL_COPY_INTO_REASSEMBLY_BUF
    \DESCRIPTION    Function call with valid parameters as described below:
                    - TgtDataPtr is based on
                      - local variable reassemblyBufPtr which validly derived using a call to IpV4_Ip_VReassemblyGetBufferPtr() as described in SBSW_TCPIP_FUNC_CALL_GET_REASSEMBLY_BUF_PTR.
                      - the access index FragAbsByteOfs that is used to write to reassemblyBufPtr whereat FragAbsByteOfs comes valid from caller that derived them as described in SBSW_TCPIP_BUF_DESC_PTR_BASED_CHECK_AND_REASSEMBLY.
                    - SrcDataPtr and:
                    - LenByte both come valid from caller as described in SBSW_TCPIP_FUNC_CALL_REASSEMBLY_RX_IND.
                    Actually here the payload that belongs into the gap has been received and is now written into the gap to complete the IPv4 packet.
                    As described in concept SBSW_TCPIP_FUNC_CALL_ADAPT_GAP this overwrites the admin data for this gap after the admin data have been updated in a way that this gap is not referenced anymore (because it was possible to fill the gap).
    \COUNTERMEASURE \N All parameters of the function call come directly or indirectly from caller.

  \ID               SBSW_TCPIP_BUF_DESC_PTR_BASED_CHECK_AND_REASSEMBLY
    \DESCRIPTION    Function call with valid parameters as described below:
                    Functions:
                    - IpV4_Ip_VReassemblyCheckFragment() OR
                    - IpV4_Ip_VReassemblyRxFragment() OR
                    - IpV4_Ip_VReassemblyRxFragmentInOrder()
                    are called with some or all of the following valid parameters:
                    - ReassemblyBufDescPtr is given by local variable reassemblyBufDescPtr which is looked up from reassemblyBufDescIdx as described in SBSW_TCPIP_FUNC_CALL_GET_REASSEMBLY_BUF_PTR and thus valid.
                    - FragIsLast, FragAbsByteOfs are given by local variables fragIsLast and fragAbsByteOfs which are all
                      - initialized from local variable flagsOffset that is read as uint16 word at offset TCPIP_IPV4_HDR_OFS_FLAGS_OFFSET in the IPv4 packet that comes valid from caller via DataPtr whereat:
                        - DataPtr points to an IPv4 packet that has at least 20 bytes of length and
                        - TCPIP_IPV4_HDR_OFS_FLAGS_OFFSET is checked to be < 20 bytes by CM_TCPIP_IPV4_HDR_STRUCT_ACCESS
                      - calculated by masking the IPv4 protocol specific status bits/values from local variable flagsOffset by using the masks:
                        - IPV4_IP_FLAGS_MORE_FRAGMENTS
                        - IPV4_IP_FRAGMENT_OFFSET_MASK
                    - FragPayloadPtr is given by dereferencing the valid pointer FragPayloadPtrPtr that comes valid from caller.
                    - FragPayloadLen is given by dereferencing the valid pointer FragPayloadLenPtr that comes valid from caller.
                    - FragBlockOfs is given by local variable fragBlockOfs which is initialized from the local variable flagsOffset in the same way as fragIsLast, described in the section immediately above.
                      (using mask IPV4_IP_FRAGMENT_OFFSET_MASK instead of IPV4_IP_FLAGS_MORE_FRAGMENTS).
                    - FragmentationConfigIdx is given by local variable fragmentationConfigIdx which is:
                      - initialized as described in CONCEPT SBSW_TCPIP_FRAGM_REASSEMBLY_DESC_ARRAY_USAGE,
                      - using the IpV4CtrlIdx that comes valid from caller.
    \COUNTERMEASURE \R CM_TCPIP_IPV4_HDR_STRUCT_ACCESS
                    \R Callers of the 3 functions, listed above, provide CSL01 compliant index values as well as valid pointers as described above.
                    \R Countermeasures described in SBSW_TCPIP_FUNC_CALL_GET_REASSEMBLY_BUF_PTR lead to valid values of reassemblyBufDescIdx and reassemblyBufDescPtr.

  \ID SBSW_TCPIP_GET_ACTIVE_ADDR_OF_ASSIGNMENT_METHOD
    \DESCRIPTION    Function IpV4_Ip_VGetActiveAddressOfAssignmentMethod() is called in 2 configurative use cases:
                    1. In case NvM is configured, the function is called by IpV4_Ip_NvMBasedAddressHandling()
                    2. In case NvM is not configured, the function is called by IpV4_Ip_VGetBestAvailableAddrAssignment() which is called by IpV4_Ip_StandardAddressHandling()
                       (which is the non-NvM counterpart of function IpV4_Ip_NvMBasedAddressHandling()).
                    Both address handling functions (roots of call trees 1. and 2.)
    \COUNTERMEASURE \N -

SBSW_JUSTIFICATION_END */

/************************************************************************************************************
 *  MSSV Checks
 ***********************************************************************************************************/

/* \CM CM_TCPIP_QMDEFINES TCPIP_DEV_ERROR_DETECT                   has to be STD_ON
                          TCPIP_SUPPORT_IPV6                       has to be STD_OFF
                          TCPIP_SUPPORT_ICMPV4                     has to be STD_ON
                          TCPIP_SUPPORT_DHCPV4SERVER               has to be STD_OFF
                          TCPIP_CONFIGURATION_VARIANT              has to be TCPIP_CONFIGURATION_VARIANT_PRECOMPILE */

/* \CM CM_TCPIP_SIZE_OF_IPBASE_ETH_PHYS_ADDR_TYPE                  The size of the array in typedef IpBase_EthPhysAddrType has to be 6 (IPBASE_ETH_PHYS_ADDR_LEN_BYTE). */

/* \CM CM_TCPIP_LOC_ADDR_IDX_ANY                                   TcpIp_GetSizeOfLocalAddrV4() has to be smaller than TCPIP_LOCAL_ADDR_V4_IDX_ANY */


/************************************************************************************************************
 *  Runtime Checks
 ***********************************************************************************************************/

/* \CM CM_TCPIP_IPV4_HDR_STRUCT_SIZE        The define IPV4_IP_DEF_HEADER_LENGTH_BYTE is not generated but is a constant with value (20u) and thus complies to the length of an IPv4 packet header (20u). */

/* \CM CM_TCPIP_IPV4_HDR_STRUCT_ACCESS      The defines used to access arrays that contain an IPv4 packet header are least 4 bytes smaller than IPV4_IP_DEF_HEADER_LENGTH_BYTE
                                              (4 byte is the length of the last uint32 member value of C-struct IpV4_IpHdrType)
                                              TCPIP_IPV4_HDR_OFS_VER_IHL      is a constant with value < IPV4_IP_DEF_HEADER_LENGTH_BYTE - 4
                                              TCPIP_IPV4_HDR_OFS_TOS          is a constant with value < IPV4_IP_DEF_HEADER_LENGTH_BYTE - 4
                                              TCPIP_IPV4_HDR_OFS_TOT_LEN      is a constant with value < IPV4_IP_DEF_HEADER_LENGTH_BYTE - 4
                                              TCPIP_IPV4_HDR_OFS_IDENT        is a constant with value < IPV4_IP_DEF_HEADER_LENGTH_BYTE - 4
                                              TCPIP_IPV4_HDR_OFS_FLAGS_OFFSET is a constant with value < IPV4_IP_DEF_HEADER_LENGTH_BYTE - 4
                                              TCPIP_IPV4_HDR_OFS_TTL          is a constant with value < IPV4_IP_DEF_HEADER_LENGTH_BYTE - 4
                                              TCPIP_IPV4_HDR_OFS_PROT         is a constant with value < IPV4_IP_DEF_HEADER_LENGTH_BYTE - 4
                                              TCPIP_IPV4_HDR_OFS_CHECKSUM     is a constant with value < IPV4_IP_DEF_HEADER_LENGTH_BYTE - 4
                                              TCPIP_IPV4_HDR_OFS_SRC_ADDR     is a constant with value < IPV4_IP_DEF_HEADER_LENGTH_BYTE - 4
                                              TCPIP_IPV4_HDR_OFS_DEST_ADDR    is a constant with value < IPV4_IP_DEF_HEADER_LENGTH_BYTE - 4 */

/* \CM CM_TCPIP_IP_HDR_LEN_BYTE             The integer value ipHdrLenByte is read from the header of an IP packet pointed to by valid parameter IpHeaderPtr using macro IPV4_HDR_FIELD_GET_IHL_BYTE(IpHeaderPtr).
                                              The calling function IpV4_Ip_RxIndication only calls the function IpV4_Ip_ReassembleAndForwardToUpperLayer():
                                              - after it has checked the result of macro IPV4_HDR_FIELD_GET_IHL_BYTE(IpHeaderPtr) to contain a valid value. */

/* \CM CM_TCPIP_IP_TOTAL_LEN_BYTE           The integer value ipTotalLenByte is read from the header of an IP packet pointed to by valid parameter IpHeaderPtr using macro IPV4_HDR_FIELD_GET_TOTAL_LEN(IpHeaderPtr).
                                              The calling function IpV4_Ip_RxIndication only calls the function IpV4_Ip_ReassembleAndForwardToUpperLayer() after it has checked the result of macro IPV4_HDR_FIELD_GET_TOTAL_LEN(IpHeaderPtr) to contain a valid value.
                                              For ipTotalLenByte this means that its value fulfills: ipHdrLenByte <= ipTotalLenByte */

/* \CM CM_TCPIP_IP_HDR_PTR_RX_IND           The given pointer variable comes valid from caller as described in SBSW_TCPIP_VALID_PTR_CALLER.
                                              The pointer points to a data array that contains at least the size of the IPv4 header structure, i.e. IPV4_IP_DEF_HEADER_LENGTH_BYTE bytes.
                                              The caller guarantees that the length of the array is >= than the value of parameter LenByte.
                                              LenByte is checked to be >= IPV4_IP_DEF_HEADER_LENGTH_BYTE (value: 20) in the if statement this function-call is contained in.
                                              The value 20 guarantees that reading the elements of 20-byte struct ipHeaderPtr accesses valid memory, always.
                                              The check of LenByte in the C-code of the if-statement is listed (and thus executed) prior all function-calls in the if-statement that combines AND conditions, only.
                                              Thus accessing members of the IPv4 header structure using offset values [0..19] is valid. (Also refer to CM_TCPIP_IPV4_HDR_STRUCT_ACCESS for checks of the values of the offset defines used) */

/* \CM CM_TCPIP_ADDR_ASSIGMENT_METHOD       CONCEPT: All over the code of TcpIp_IpV4.c the value of the IPv4 controller specific runtime data item AddrAssignmentMethodPersist
                                              can be used by IPv4-internal service functions without an additional check, because:
                                              - this value is initialized with the valid value  for each IPv4 controller at the call to IpV4_Ip_Init() and
                                              - all internal IPv4-internal service functions are always called by external API of TcpIp which ensures that the TcpIp is initialized,
                                                i.e. IpV4_Ip_Init() has been called and AddrAssignmentMethodPersist of an IPv4 controller has a valid value. */

/* \CM CM_TCPIP_IPV4_SPECIFIC_LOC_ADDR_IDX  CONCEPT: All over the code of TcpIp_IpV4.c the values of variable localAddrV4Idx follow the following convention:
                                              If any IPv4-specific localAddrV4Idx variable or parameter is:
                                              - invalid, it is initialized with the value TCPIP_LOCAL_ADDR_V4_IDX_ANY.
                                                Note: The value of TCPIP_LOCAL_ADDR_V4_IDX_ANY is currently constantly defined as 0xFF. As TCPIP_LOCAL_ADDR_V4_IDX_ANY has a special meaning distinct from
                                                      other localAddrV4Idx values that range from [0..TcpIp_GetSizeOfLocalAddrV4()-1], TcpIp_GetSizeOfLocalAddrV4() needs to be <= TCPIP_LOCAL_ADDR_V4_IDX_ANY.
                                                      This check is done by CM_TCPIP_LOC_ADDR_IDX_ANY.
                                              - valid, it is initialized with a value that complies with the qualified use-case CSL03 of ComStackLib which complies to the following:
                                                CONSTRAINT [0..TcpIp_GetSizeOfLocalAddrV4()-1]
                                              Both the "invalid condition" and the "valid constraint" have been reviewed by searching TcpIp_IpV4.c for the RegEx: localAddr[V4]*[Idx]*[Ptr)]*\s*=\s+
                                              Result: All assignments do either use TCPIP_LOCAL_ADDR_V4_IDX_ANY or use the following CSL-macros that fulfill the CSL03 use-case:
                                              - TcpIp_GetLocalAddrV4IdxOfMulticastAddrV4(multicastAddrV4Idx): multicastAddrV4Idx is determined using the following CSL-macros:
                                                - TcpIp_GetMulticastAddrV4StartIdxOfIpV4Ctrl(IpV4CtrlIdx)
                                                - TcpIp_GetMulticastAddrV4EndIdxOfIpV4Ctrl(IpV4CtrlIdx)
                                                whereat IpV4CtrlIdx is checked by the caller to comply to CONSTRAINT [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
                                              - TcpIp_GetLocalAddrV4BroadcastIdxOfIpV4Ctrl(ipV4CtrlIdx)
                                              - TcpIp_GetLocalAddrV4UnicastIdxOfIpV4Ctrl(ipV4CtrlIdx)
                                                whereat these ipV4CtrlIdx values are valid as described in SBSW_TCPIP_CSL03_IDX_BASED_ON_CSL01_CALLER
                                                (I.e.: Look-up using CSL-macro TcpIp_GetIpV4CtrlIdxOfEthIfCtrl() using parameter EthIfCtrlIdx which comes valid from caller.) */

/* \CM CM_TCPIP_IPV4_CTRL_IDX_CHECK         The local variable ipV4CtrlIdx is initialized using the return value of one of these TcpIp-internal functions:
                                              - IpV4_Ip_VGetLocalAddrIdxAndCtrlIdx()
                                              Each of these functions either returns
                                              - a valid ipV4CtrlIdx value (i.e. < TcpIp_GetSizeOfIpV4Ctrl()) or
                                              - TcpIp_GetSizeOfIpV4Ctrl() to indicate an invalid value.
                                              After that assignment ipV4CtrlIdx a runtime check is conducted that checks that the value is < TcpIp_GetSizeOfIpV4Ctrl().
                                              Only then ipV4CtrlIdx is used as parameter for a succeeding function call. Refer to line containing token SBSW_TCPIP_CM_R2. */

/* \CM CM_TCPIP_ETH_TX_BUF_IDX             CONCEPT: All over the code of TcpIp_IpV4.c the values of variable ethBufIdx follow the following convention:
                                             If any IPv4-specific ethBufIdx variable or parameter is:
                                             - invalid, it is initialized with the value IPV4_IP_TX_BUF_IDX_INV.
                                             - valid, it is initialized with a value that complies with the qualified use-case CSL03 of ComStackLib which complies to the following:
                                               CONSTRAINT [0..TcpIp_GetSizeOfBuf2TxReqMap()-1]
                                             In case the ethBufIdx is looked up from an IP controllers' config data using macro:
                                               TcpIp_GetBuf2TxReqMapEndIdxOfIpV4Ctrl(IpV4CtrlIdx)
                                               then the IpV4CtrlIdx either
                                               - comes valid from caller or
                                               - is a local variable that is checked to be:
                                                 ipV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl()
                                             The following variables are used in contexts that comply to the above description:
                                             - ethBufIdx
                                             - prevEthBufIdx */

#endif /* (TCPIP_SUPPORT_IPV4 == STD_ON) */
/**********************************************************************************************************************
 *  END OF FILE: Ip.c
 *********************************************************************************************************************/
