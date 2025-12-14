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
 *         \file  TcpIp_IpV4_Priv.h
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

#if !defined (IPV4_PRIV_H)
# define IPV4_PRIV_H

# if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                     /* COV_TCPIP_IPV4_ALWAYS_ON */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#  include "TcpIp_Cfg.h"
#  include "TcpIp_IpV4_Types.h"
#  include "TcpIp_Lcfg.h"


#  if (TCPIP_DEV_ERROR_REPORT == STD_ON)
#   include "Det.h"
#  endif
#  include "TcpIp_Cbk.h"
#  include "SchM_TcpIp.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#  define IPV4_INV_SOCK_IDX                                           255u /* TcpIp_GetSizeOfIpV4SocketDyn() */


#   define IPV4_DUMMY_ASM_NOP

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FunctionLikeMacros */ /* MD_MSR_FctLikeMacro */

#  define IPV4_VENTER_CRITICAL_SECTION()                              SchM_Enter_TcpIp_TCPIP_EXCLUSIVE_AREA_0()
#  define IPV4_VLEAVE_CRITICAL_SECTION()                              SchM_Exit_TcpIp_TCPIP_EXCLUSIVE_AREA_0()

/* Development Error Tracer */
#  if ( TCPIP_DEV_ERROR_REPORT == STD_ON )
#   define IpV4_CheckDetErrorReturnVoid(  CONDITION, API_ID, ERROR_CODE ) { if(!(CONDITION)) {    \
                                                                         (void)Det_ReportError( IPV4_MODULE_ID, IPV4_VINSTANCE_ID, (API_ID), (ERROR_CODE)); return; } }
#   define IpV4_CheckDetErrorReturnValue( CONDITION, API_ID, ERROR_CODE, RET_VAL ) { if(!(CONDITION)) {    \
                                                                                  (void)Det_ReportError( IPV4_MODULE_ID, IPV4_VINSTANCE_ID, (API_ID), (ERROR_CODE)); return (RET_VAL); } }
#   define IpV4_CheckDetErrorContinue(    CONDITION, API_ID, ERROR_CODE ) { if(!(CONDITION)) {    \
                                                                         (void)Det_ReportError( IPV4_MODULE_ID, IPV4_VINSTANCE_ID, (API_ID), (ERROR_CODE)); } }
#   define IpV4_ReportDetError( API_ID, ERROR_CODE )                  \
                                                                      (void)Det_ReportError( IPV4_MODULE_ID, IPV4_VINSTANCE_ID, (API_ID), (ERROR_CODE) )
#  else
#   define IpV4_CheckDetErrorReturnVoid(  CONDITION, API_ID, ERROR_CODE )
#   define IpV4_CheckDetErrorReturnValue( CONDITION, API_ID, ERROR_CODE, RET_VAL )
#   define IpV4_CheckDetErrorContinue(    CONDITION, API_ID, ERROR_CODE )
#   define IpV4_ReportDetError(                      API_ID, ERROR_CODE )
#  endif
/* TCPIP_DEV_ERROR_REPORT */

#  define IPV4_UNUSED_PARAMETER(Parameter)                            TCPIP_DUMMY_STATEMENT(Parameter)

#  define IPV4_SET_BIT_U8(VAR, BIT)                                   IPV4_SET_FLAG_U8((VAR), (1U << (BIT)))
#  define IPV4_CLR_BIT_U8(VAR, BIT)                                   IPV4_CLR_FLAG_U8((VAR), (1U << (BIT)))
#  define IPV4_CHK_BIT_U8(VAR, BIT)                                   IPV4_CHK_FLAG_U8((VAR), (1U << (BIT)))

#  define IPV4_SET_FLAG_U8(VAR, FLAG)                                 ((VAR) |= (uint8) (FLAG))
#  define IPV4_CLR_FLAG_U8(VAR, FLAG)                                 ((VAR) = ((uint8) ( (VAR) & ( (~(FLAG)) & 0xFFu ) ) ))
#  define IPV4_CHK_FLAG_U8(VAR, FLAG)                                 (((uint8)((VAR) & (FLAG))) != 0U)

/* Macros for IpV4 header handling */
#  define IPV4_HDR_FIELD_CREATE_VER_IHL(HDR_LEN_BYTE)                 ((((uint8)IPV4_IP_HEADER_VERSION_V4) << 4) | ((HDR_LEN_BYTE) >> 2))

/* Outdated macros for IpV4 header, working on a ptr to an instance of C-struct IpV4_Ip_HdrType */
#  define IPV4_HDR_FIELD_GET_IHL_BYTE(IP_HDR_PTR)                     (uint8)(((IP_HDR_PTR)->Ver_Ihl & 0x0FU) << 2)
#  define IPV4_HDR_FIELD_GET_TOTAL_LEN(IP_HDR_PTR)                    TCPIP_NTOHS((IP_HDR_PTR)->TotLen)

/* Topical macros for IpV4 header, working directly on the DataPtr from the EthIf */
/* IPv4 header format - refer to struct IpV4_IpHdrType */
#  define TCPIP_IPV4_HDR_OFS_VER_IHL      0U /* Ihl in dword */
#  define TCPIP_IPV4_HDR_OFS_TOS          1U
#  define TCPIP_IPV4_HDR_OFS_TOT_LEN      2U /* Length in byte */
#  define TCPIP_IPV4_HDR_OFS_IDENT        4U
#  define TCPIP_IPV4_HDR_OFS_FLAGS_OFFSET 6U
#  define TCPIP_IPV4_HDR_OFS_TTL          8U /* Time to live */
#  define TCPIP_IPV4_HDR_OFS_PROT         9U
#  define TCPIP_IPV4_HDR_OFS_CHECKSUM     10U
#  define TCPIP_IPV4_HDR_OFS_SRC_ADDR     12U
#  define TCPIP_IPV4_HDR_OFS_DEST_ADDR    16U

/* IpSec AH header offsets */
#  define TCPIP_IPSEC_AH_HDR_OFS_NEXTHDR         0u
#  define TCPIP_IPSEC_AH_HDR_OFS_PAYLOADLEN      (TCPIP_IPSEC_AH_HDR_OFS_NEXTHDR + 1u)
#  define TCPIP_IPSEC_AH_HDR_OFS_RSVD            (TCPIP_IPSEC_AH_HDR_OFS_PAYLOADLEN + 1u)
#  define TCPIP_IPSEC_AH_HDR_OFS_SPI             (TCPIP_IPSEC_AH_HDR_OFS_RSVD + 2u)
#  define TCPIP_IPSEC_AH_HDR_OFS_SEQNUM          (TCPIP_IPSEC_AH_HDR_OFS_SPI + 4u)
#  define TCPIP_IPSEC_AH_HDR_OFS_AUTHDATA        (TCPIP_IPSEC_AH_HDR_OFS_SEQNUM + 4u)

#  define TCPIP_IPV4_HDR_FIELD_GET_VERSION(DATAPTR)   (uint8)((TCPIP_GET_UINT8((DATAPTR), TCPIP_IPV4_HDR_OFS_VER_IHL) & 0xF0u) >> 4)
#  define TCPIP_IPV4_HDR_FIELD_GET_TOTAL_LEN(DATAPTR) TCPIP_GET_UINT16((DATAPTR), TCPIP_IPV4_HDR_OFS_TOT_LEN)
#  define TCPIP_IPV4_HDR_FIELD_GET_IHL_BYTE(DATAPTR)  (uint8)((TCPIP_GET_UINT8((DATAPTR), TCPIP_IPV4_HDR_OFS_VER_IHL) & 0x0FU) << 2)

#  define TCPIP_IPV4_ADDR_IDX_IS_ASBC(LocalAddrV4Idx)                ((TcpIp_IsUnicastAddrV4UsedOfLocalAddrV4(LocalAddrV4Idx) == FALSE) && (TcpIp_IsMulticastAddrV4UsedOfLocalAddrV4(LocalAddrV4Idx) == FALSE))

#  define TCPIP_LOCAL_ADDR_V4_IDX_ANY                                 0xFFu /* TcpIp_GetSizeOfLocalAddrV4() */

/* CHECK CONDITIONS: */
#  define IPV4_COND_VALID_IPADDR(IpAddr)                              ( (0u != (IpAddr)) )
#  define IPV4_COND_MIN_SIZE(Value, Ref)                              ( (Value) >= (Ref) )
#  define IPV4_COND_PBUF_LEN(PbufPtr)                                 ( (NULL_PTR != (PbufPtr)->payload) && \
                                                                      (0u != (PbufPtr)->totLen) && \
                                                                      ((PbufPtr)->totLen >= (PbufPtr)->len) )

/* implementation limit: max message length is 64kB */
#  define IPV4_COND_LEN_MAX_UINT16(Len)                               ( (uint32)(Len) <= (uint32)0xFFFF )

/* BSD API checks: */
#  define IPV4_COND_PROT_UDP(Prot)                                    ( IPV4_SOCK_PROT_UDP == (Prot) )
#  define IPV4_COND_PROT2(Prot)                                       ( (IPV4_SOCK_PROT_UDP == (Prot)) || \
                                                                      (IPV4_SOCK_PROT_TCP == (Prot)) )

/* Byte-Order conversion macros */

#  define IPV4_HTONS(UINT16_VALUE)                                    TCPIP_HTONS(UINT16_VALUE)
#  define IPV4_HTONL(UINT32_VALUE)                                    TCPIP_HTONL(UINT32_VALUE)
#  if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)                                                                               /* COV_TCPIP_BYTE_ORDER */
/* Host byte-order is big endian (network byte-order) */
#   define IPV4_UINT8_HTONS(UINT8_VALUE)                              (UINT8_VALUE)
#  else
/* Host byte-order is little endian */
#   define IPV4_UINT8_HTONS(UINT8_VALUE)                              ((uint16)(  ((uint16)(UINT8_VALUE) << 8)))
#  endif

#  define IPV4_GET_SOCKET_TIME_TO_LIVE(IpV4SocketIdx, IpV4CtrlIdx)        ((0u != (IPV4_IP_TRANSFER_BLOCK_FLAG_TIME_TO_LIVE     & TcpIp_GetTransferBlockOfIpV4SocketDyn(IpV4SocketIdx).Flags)) ? TcpIp_GetTransferBlockOfIpV4SocketDyn(IpV4SocketIdx).TimeToLive     : TcpIp_GetDefaultTtlOfIpV4Ctrl(IpV4CtrlIdx))
#  define IPV4_GET_SOCKET_TYPE_OF_SERVICE(IpV4SocketIdx, IpV4CtrlIdx)     ((0u != (IPV4_IP_TRANSFER_BLOCK_FLAG_TYPE_OF_SERVICE  & TcpIp_GetTransferBlockOfIpV4SocketDyn(IpV4SocketIdx).Flags)) ? TcpIp_GetTransferBlockOfIpV4SocketDyn(IpV4SocketIdx).TypeOfService  : TcpIp_GetTypeOfServiceDefaultOfIpV4Ctrl(IpV4CtrlIdx))
#  define IPV4_GET_SOCKET_ETHIF_FRAME_PRIO(IpV4SocketIdx, IpV4CtrlIdx)    ((0u != (IPV4_IP_TRANSFER_BLOCK_FLAG_ETHIF_FRAME_PRIO & TcpIp_GetTransferBlockOfIpV4SocketDyn(IpV4SocketIdx).Flags)) ? TcpIp_GetTransferBlockOfIpV4SocketDyn(IpV4SocketIdx).EthIfFramePrio : TcpIp_GetFramePrioDefaultOfIpV4Ctrl(IpV4CtrlIdx))
#  define IPV4_GET_SOCKET_FORCE_ZERO_SRC_ADDR(IpV4SocketIdx)              (0u != (IPV4_IP_TRANSFER_BLOCK_FLAG_ZERO_SRC_ADDR    & TcpIp_GetTransferBlockOfIpV4SocketDyn(IpV4SocketIdx).Flags))

#  define IPV4_LL_ADDR_IS_EQUAL(ADDR_A, ADDR_B)                       ( ((ADDR_A)[5] == (ADDR_B)[5]) && \
                                                                      ((ADDR_A)[4] == (ADDR_B)[4]) && \
                                                                      ((ADDR_A)[3] == (ADDR_B)[3]) && \
                                                                      ((ADDR_A)[2] == (ADDR_B)[2]) && \
                                                                      ((ADDR_A)[1] == (ADDR_B)[1]) && \
                                                                      ((ADDR_A)[0] == (ADDR_B)[0]) )

#  define IPV4_LL_ADDR_IS_GROUP(ADDR)                                 (0u != ((ADDR)[0] & 0x01u))
#  define IPV4_LL_ADDR_IS_EMPTY(ADDR)                                 ( (0x00u == (ADDR)[5]) && \
                                                                      (0x00u == (ADDR)[4]) && \
                                                                      (0x00u == (ADDR)[3]) && \
                                                                      (0x00u == (ADDR)[2]) && \
                                                                      (0x00u == (ADDR)[1]) && \
                                                                      (0x00u == (ADDR)[0]) )
#  define IPV4_LL_ADDR_IS_VALID(ADDR)                                 ( !( IPV4_LL_ADDR_IS_GROUP((ADDR)) || IPV4_LL_ADDR_IS_EMPTY((ADDR)) ) )


#  define IPV4_UINT32_TIMESTAMP_IS_OLDER(TS_A, TS_B)                  (((TS_B) - (TS_A) - 1u) < 0x80000000U)


#  define IPV4_IP_ADDR_ASSIGNMENT_MASK_METHOD                         0x03u
#  define IPV4_IP_ADDR_ASSIGNMENT_MASK_PRIO                           0x03u
#  define IPV4_IP_ADDR_ASSIGNMENT_PRIO_NONE                           0u

#  define IpV4_Ip_VCfgGetAddrAssignmentPrio(ipV4CtrlIdx, TYPE)        ((TcpIp_IpAddrAssignmentType)((TcpIp_GetAddrAssignmentPrioByTypeOfIpV4Ctrl(ipV4CtrlIdx) >> (2u * (TYPE))) & IPV4_IP_ADDR_ASSIGNMENT_MASK_PRIO))
#  define IpV4_Ip_VCfgIsAddrAssignmentEnabled(ipV4CtrlIdx, TYPE)      (IpV4_Ip_VCfgGetAddrAssignmentPrio((ipV4CtrlIdx), (TYPE)) != 0u)
#  define IpV4_Ip_VCfgGetAddrAssignmentCfgByPrio(ipV4CtrlIdx, PRIO)   (TcpIp_GetAssignmentCfgByPrioOfIpV4Ctrl(ipV4CtrlIdx)[(PRIO) - 1u])
#  define IpV4_Ip_VCfgGetAddrAssignmentMethodByCfg(CFG)               ((TcpIp_IpAddrAssignmentType)((CFG) & IPV4_IP_ADDR_ASSIGNMENT_MASK_METHOD))

/* PRQA L:FunctionLikeMacros */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* IP LL - states */
#  define IPV4_IP_LL_STATE_INACTIVE                                   0x0u
#  define IPV4_IP_LL_STATE_INIT                                       0x1u
#  define IPV4_IP_LL_STATE_WAIT                                       0x2u
#  define IPV4_IP_LL_STATE_PROBE                                      0x3u
#  define IPV4_IP_LL_STATE_CONFLICT                                   0x4u
#  define IPV4_IP_LL_STATE_ANNOUNCE                                   0x5u
#  define IPV4_IP_LL_STATE_READY                                      0x6u
/* IP LL Probe - substates */
#  define IPV4_IP_LL_PROBE_STATE_CHOOSE                               0x1u
#  define IPV4_IP_LL_PROBE_STATE_PROBE                                0x2u
#  define IPV4_IP_LL_PROBE_STATE_WAIT                                 0x3u
/* IP LL Announce - substates */
#  define IPV4_IP_LL_ANN_STATE_PROBE                                  0x1u
#  define IPV4_IP_LL_ANN_STATE_WAIT                                   0x2u

#  define IPV4_IP_TRANSFER_BLOCK_FLAG_TIME_TO_LIVE                    1u
#  define IPV4_IP_TRANSFER_BLOCK_FLAG_TYPE_OF_SERVICE                 2u
#  define IPV4_IP_TRANSFER_BLOCK_FLAG_ETHIF_FRAME_PRIO                4u
#  define IPV4_IP_TRANSFER_BLOCK_FLAG_PHYS_DEST_ADDR                  8u
#  define IPV4_IP_TRANSFER_BLOCK_FLAG_ZERO_SRC_ADDR                   16u

#  define IPV4_IP_REASSEMBLY_BUF_STATUS_UNUSED                        0u
#  define IPV4_IP_REASSEMBLY_BUF_STATUS_IN_PROGRESS                   1u
#  define IPV4_IP_REASSEMBLY_BUF_STATUS_FAILED                        2u
#  define IPV4_IP_REASSEMBLY_BUF_STATUS_COMPLETE                      3u

#  define IPV4_IP_REASSEMBLY_BUF_NO_NEXT_GAP_OFS                      0xFFFFu
#  define IPV4_IP_REASSEMBLY_BUF_NEXT_GAP_OFS                         0u
#  define IPV4_IP_REASSEMBLY_BUF_GAP_SIZE_OFS                         2u

#  define IPV4_IP_REASSEMBLY_BUF_DESC_IDX_INV                         TcpIp_GetSizeOfReassemblyBufferDesc()


#  define IPV4_IP_REASSEMBLY_FLAG_FIRST_FRAG_RECEIVED                 1u
#  define IPV4_IP_REASSEMBLY_FLAG_LAST_FRAG_RECEIVED                  2u

#  define IPV4_IP_TX_BUF_IDX_INV                                      0xFFu

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FunctionLikeMacros */ /* MD_MSR_FctLikeMacro */

#  define IPV4_P2V(TYPE)                                              P2VAR(TYPE,   AUTOMATIC, IPV4_APPL_VAR)
#  define IPV4_P2C(TYPE)                                              P2CONST(TYPE, AUTOMATIC, IPV4_APPL_DATA)

/* PRQA L:FunctionLikeMacros */ /* MD_MSR_FctLikeMacro    */
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  IpV4_Ip_VIpAddrAssignmentReadyNotification
 *********************************************************************************************************************/
/*! \brief          Checks if address of specified assignment method shall be stored into NvM.
 *  \details        Sets 'persist' flag, so address will be written into NvM in MainFunction.
 *  \param[in]      IpV4CtrlIdx          Index of the affected IPv4 controller.
 *                  CONSTRAINT           [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]      AddrAssignmentMethod Desired address assignment method.
 *                  CONSTRAINT           [TCPIP_IPADDR_ASSIGNMENT_STATIC,
 *                                        TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL,
 *                                        TCPIP_IPADDR_ASSIGNMENT_DHCP]
 *  \param[in]      AddrAssigned         Flag whether an address for the given IP controller has been assigned, before.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
FUNC(void, IPV4_CODE) IpV4_Ip_VIpAddrAssignmentReadyNotification(
  TcpIp_IpV4CtrlIterType  IpV4CtrlIdx,
  uint8                   AddrAssignmentMethod,
  boolean                 AddrAssigned);

# endif /* (TCPIP_SUPPORT_IPV4 == STD_ON) */
#endif /* IPV4_PRIV_H */
/**********************************************************************************************************************
 *  END OF FILE: IpV4_Priv.h
 *********************************************************************************************************************/
