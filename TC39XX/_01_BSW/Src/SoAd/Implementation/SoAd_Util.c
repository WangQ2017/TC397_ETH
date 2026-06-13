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
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  SoAd_Util.c
 *        \brief  Socket Adaptor source file
 *
 *      \details  Vector static code implementation for AUTOSAR Socket Adaptor sub-component Util.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main source file.
 *********************************************************************************************************************/

/* PRQA S 1881 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA S 4304 EOF */ /* MD_MSR_AutosarBoolean */

#define SOAD_UTIL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "SoAd_Util.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (SOAD_LOCAL) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL static
#endif

#if !defined (SOAD_LOCAL_INLINE) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define SOAD_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_Util_CompareIpAddr()
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
/* PRQA S 3206 2 */ /* MD_SoAd_UnusedParameter */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Util_CompareIpAddr(
  SoAd_DomainType Domain,
  SoAd_IpAddrConstPtrType IpAddrAPtr,
  SoAd_IpAddrConstPtrType IpAddrBPtr,
  boolean AllowWildcards)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_IPV6 == STD_ON )
  /* #10 Compare IPv6 IP address (if enabled). */
  if ( Domain == SOAD_AF_INET6 )
  {
    /* #100 Compare both IP addresses. */
    if ( (IpAddrAPtr[0u] == IpAddrBPtr[0u]) &&
      (IpAddrAPtr[1u] == IpAddrBPtr[1u]) &&
      (IpAddrAPtr[2u] == IpAddrBPtr[2u]) &&
      (IpAddrAPtr[3u] == IpAddrBPtr[3u]) )
    {
      retVal = E_OK;
    }
    /* #101 Compare first IP address to wildcard if IP addresses are not equal. */
    else if ( (AllowWildcards == TRUE) &&
      ((IpAddrAPtr[0u] == SOAD_IP6ADDR_ANY) &&
      (IpAddrAPtr[1u] == SOAD_IP6ADDR_ANY) &&
      (IpAddrAPtr[2u] == SOAD_IP6ADDR_ANY) &&
      (IpAddrAPtr[3u] == SOAD_IP6ADDR_ANY)) )
    {
      retVal = E_OK;
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }
  else
#else
  SOAD_DUMMY_STATEMENT(Domain); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_IPV6 == STD_ON */
  /* #20 Compare IPv4 IP address otherwise. */
  {
    /* #200 Compare both IP addresses. */
    if ( IpAddrAPtr[0u] == IpAddrBPtr[0u] )
    {
      retVal = E_OK;
    }
    /* #201 Compare first IP address to wildcard if IP addresses are not equal. */
    else if ( (AllowWildcards == TRUE) && (IpAddrAPtr[0u] == SOAD_IPADDR_ANY) )
    {
      retVal = E_OK;
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* SoAd_Util_CompareIpAddr() */

#if ( SOAD_TX_DYN_LEN == STD_ON )
/**********************************************************************************************************************
 *  SoAd_Util_UpdatePduHdrLen()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_Util_UpdatePduHdrLen(
  SoAd_PduHdrLenType PduHeaderLen,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update PDU header length by overwriting the buffer with offset of PDU header ID. */
  BufPtr[SOAD_PDU_HDR_ID_SIZE]      = (uint8)(PduHeaderLen >> 24u);                                                    /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
  BufPtr[SOAD_PDU_HDR_ID_SIZE + 1u] = (uint8)(PduHeaderLen >> 16u);                                                    /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
  BufPtr[SOAD_PDU_HDR_ID_SIZE + 2u] = (uint8)(PduHeaderLen >> 8u);                                                     /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
  BufPtr[SOAD_PDU_HDR_ID_SIZE + 3u] = (uint8)(PduHeaderLen);                                                           /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
} /* SoAd_Util_UpdatePduHdrLen() */
#endif /* SOAD_TX_DYN_LEN == STD_ON */

/**********************************************************************************************************************
 *  SoAd_Util_CheckForWildcards()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_Util_CheckForWildcards(
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) AddrCheck,
  P2VAR(boolean, AUTOMATIC, SOAD_APPL_DATA) IpAddrIsAny,
  P2VAR(boolean, AUTOMATIC, SOAD_APPL_DATA) PortIsAny)
{
  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_IPV6 == STD_ON )
  /* #10 Check if IPv6 address is wildcard (if enabled). */
  if ( AddrCheck->domain == SOAD_AF_INET6 )
  {
    /* PRQA S 310, 3305 4 */ /* MD_SoAd_PointerCastOnStruct */
    if ( (((P2CONST(SoAd_SockAddrInet6Type, AUTOMATIC, AUTOMATIC))AddrCheck)->addr[0u] == SOAD_IP6ADDR_ANY) &&
      (((P2CONST(SoAd_SockAddrInet6Type, AUTOMATIC, AUTOMATIC))AddrCheck)->addr[1u] == SOAD_IP6ADDR_ANY) &&
      (((P2CONST(SoAd_SockAddrInet6Type, AUTOMATIC, AUTOMATIC))AddrCheck)->addr[2u] == SOAD_IP6ADDR_ANY) &&
      (((P2CONST(SoAd_SockAddrInet6Type, AUTOMATIC, AUTOMATIC))AddrCheck)->addr[3u] == SOAD_IP6ADDR_ANY) )
    {
      *IpAddrIsAny = TRUE;                                                                                             /* SBSW_SOAD_POINTER_WRITE */
    }
    else
    {
      *IpAddrIsAny = FALSE;                                                                                            /* SBSW_SOAD_POINTER_WRITE */
    }
  }
  else
#endif /* SOAD_IPV6 == STD_ON */
  /* #11 Check if IPv4 address is wildcard otherwise. */
  {
    /* PRQA S 310, 3305 1 */ /* MD_SoAd_PointerCastOnStruct */
    if ( ((P2CONST(SoAd_SockAddrInetType, AUTOMATIC, AUTOMATIC))AddrCheck)->addr[0u] == SOAD_IPADDR_ANY )
    {
      *IpAddrIsAny = TRUE;                                                                                             /* SBSW_SOAD_POINTER_WRITE */
    }
    else
    {
      *IpAddrIsAny = FALSE;                                                                                            /* SBSW_SOAD_POINTER_WRITE */
    }
  }

  /* #20 Check if port is wildcard. */
  /* PRQA S 310, 3305 1 */ /* MD_SoAd_PointerCastOnStruct */
  if ( ((P2CONST(SoAd_SockAddrInetXType, AUTOMATIC, AUTOMATIC))AddrCheck)->port == SOAD_PORT_ANY )
  {
    *PortIsAny = TRUE;                                                                                                 /* SBSW_SOAD_POINTER_WRITE */
  }
  else
  {
    *PortIsAny = FALSE;                                                                                                /* SBSW_SOAD_POINTER_WRITE */
  }
} /* SoAd_Util_CheckForWildcards() */

/**********************************************************************************************************************
 *  SoAd_Util_CopySockAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_Util_CopySockAddr(
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) TgtSockAddrPtr,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) SrcSockAddrPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy domain type. */
  TgtSockAddrPtr->domain = SrcSockAddrPtr->domain;                                                                     /* SBSW_SOAD_POINTER_WRITE */

  /* #20 Copy IP address depending on domain type (IPv4/6). */
#if ( SOAD_IPV6 == STD_ON )
  if ( SrcSockAddrPtr->domain == SOAD_AF_INET6 )
  {
    /* PRQA S 310, 3305 8 */ /* MD_SoAd_PointerCastOnStruct */
    (SOAD_A_P2VAR(SoAd_SockAddrInet6Type)TgtSockAddrPtr)->addr[0u] =                                                   /* SBSW_SOAD_SOCK_ADDR_CAST_POINTER_WRITE */
      (SOAD_A_P2CONST(SoAd_SockAddrInet6Type)SrcSockAddrPtr)->addr[0u];
    (SOAD_A_P2VAR(SoAd_SockAddrInet6Type)TgtSockAddrPtr)->addr[1u] =                                                   /* SBSW_SOAD_SOCK_ADDR_CAST_POINTER_WRITE */
      (SOAD_A_P2CONST(SoAd_SockAddrInet6Type)SrcSockAddrPtr)->addr[1u];
    (SOAD_A_P2VAR(SoAd_SockAddrInet6Type)TgtSockAddrPtr)->addr[2u] =                                                   /* SBSW_SOAD_SOCK_ADDR_CAST_POINTER_WRITE */
      (SOAD_A_P2CONST(SoAd_SockAddrInet6Type)SrcSockAddrPtr)->addr[2u];
    (SOAD_A_P2VAR(SoAd_SockAddrInet6Type)TgtSockAddrPtr)->addr[3u] =                                                   /* SBSW_SOAD_SOCK_ADDR_CAST_POINTER_WRITE */
      (SOAD_A_P2CONST(SoAd_SockAddrInet6Type)SrcSockAddrPtr)->addr[3u];
  }
  else
#endif /* SOAD_IPV6 == STD_ON */
  {
    /* PRQA S 310, 3305 2 */ /* MD_SoAd_PointerCastOnStruct */
    (SOAD_A_P2VAR(SoAd_SockAddrInetType)TgtSockAddrPtr)->addr[0u] =                                                    /* SBSW_SOAD_SOCK_ADDR_CAST_POINTER_WRITE */
      (SOAD_A_P2CONST(SoAd_SockAddrInetType)SrcSockAddrPtr)->addr[0u];
  }

  /* #30 Copy port. */
  /* PRQA S 310, 3305 2 */ /* MD_SoAd_PointerCastOnStruct */
  (SOAD_A_P2VAR(SoAd_SockAddrInetXType)TgtSockAddrPtr)->port =                                                         /* SBSW_SOAD_SOCK_ADDR_CAST_POINTER_WRITE */
    (SOAD_A_P2CONST(SoAd_SockAddrInetXType)SrcSockAddrPtr)->port;
} /* SoAd_Util_CopySockAddr() */

/**********************************************************************************************************************
 *  SoAd_Util_CopyPduHdr2Buf()
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
FUNC(void, SOAD_CODE) SoAd_Util_CopyPduHdr2Buf(
  SoAd_PduHdrIdType PduHeaderId,
  SoAd_PduHdrLenType PduHeaderLen,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  PduLengthType Offset,
  PduLengthType Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduLengthType pduHdrIdx;
  PduLengthType pduHdrEndIdx = Offset + Length;
  uint8         pduHdrBuf[SOAD_PDU_HDR_SIZE];

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if entire PDU header shall be copied. */
  if ( Length == SOAD_PDU_HDR_SIZE )
  {
    /* #100 Copy entire PDU header to provided buffer. */
    BufPtr[0u] = (uint8)(PduHeaderId >> 24u);                                                                          /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    BufPtr[1u] = (uint8)(PduHeaderId >> 16u);                                                                          /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    BufPtr[2u] = (uint8)(PduHeaderId >> 8u);                                                                           /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    BufPtr[3u] = (uint8)(PduHeaderId);                                                                                 /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    BufPtr[4u] = (uint8)(PduHeaderLen >> 24u);                                                                         /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    BufPtr[5u] = (uint8)(PduHeaderLen >> 16u);                                                                         /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    BufPtr[6u] = (uint8)(PduHeaderLen >> 8u);                                                                          /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    BufPtr[7u] = (uint8)(PduHeaderLen);                                                                                /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
  }
  /* #11 Handle PDU header segmentation otherwise. */
  else
  {
    /* #110 Fill local buffer with PDU header. */
    pduHdrBuf[0u] = (uint8)(PduHeaderId >> 24u);                                                                       /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    pduHdrBuf[1u] = (uint8)(PduHeaderId >> 16u);                                                                       /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    pduHdrBuf[2u] = (uint8)(PduHeaderId >> 8u);                                                                        /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    pduHdrBuf[3u] = (uint8)(PduHeaderId);                                                                              /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    pduHdrBuf[4u] = (uint8)(PduHeaderLen >> 24u);                                                                      /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    pduHdrBuf[5u] = (uint8)(PduHeaderLen >> 16u);                                                                      /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    pduHdrBuf[6u] = (uint8)(PduHeaderLen >> 8u);                                                                       /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    pduHdrBuf[7u] = (uint8)(PduHeaderLen);                                                                             /* SBSW_SOAD_EXPECTED_SIZE_WRITE */

    /* #111 Copy PDU header segment from local buffer to provided buffer. */
    for ( pduHdrIdx = Offset; pduHdrIdx < pduHdrEndIdx; pduHdrIdx++ )
    {
      BufPtr[pduHdrIdx - Offset] = pduHdrBuf[pduHdrIdx];                                                               /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    }
  }
} /* SoAd_Util_CopyPduHdr2Buf() */

/**********************************************************************************************************************
 *  SoAd_Util_GetSupportedPduLength()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(PduLengthType, SOAD_CODE) SoAd_Util_GetSupportedPduLength(
  uint32 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduLengthType supportedPduLength;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return maximum supported PDU length if requested length exceeds maximum supported PDU length. */
  if ( Length > SOAD_MAX_PDU_LEN )
  {
    supportedPduLength = (PduLengthType)SOAD_MAX_PDU_LEN;
  }
  else
  /* #11 Return requested PDU length otherwise. */
  {
    supportedPduLength = (PduLengthType)Length;
  }

  return supportedPduLength;
} /* SoAd_Util_GetSupportedPduLength() */

#define SOAD_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/* Justification for module-specific MISRA deviations:
 * see file SoAd.c
 */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_Util.c
 *********************************************************************************************************************/
