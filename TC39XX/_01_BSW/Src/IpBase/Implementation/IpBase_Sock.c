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
 *         File:  IpBase_Sock.c
 *      Project:  MICROSAR ETH
 *    Component:  SysService_IpBase
 *       Module:  MICROSAR IP Base
 *    Generator:  None
 *
 *  Description:  Socket API implementation
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/
#define IPBASE_SOCK_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "IpBase.h"           /* PRQA S 3453 3 */ /* MD_MSR_FctLikeMacro */
#include "IpBase_Priv.h"

/**********************************************************************************************************************
 *  CONSISTENCY CHECK
 *********************************************************************************************************************/
/* Check consistency of source and header file. */
#if ( (IPBASE_SW_MAJOR_VERSION != 04u) \
   || (IPBASE_SW_MINOR_VERSION != 00u) \
   || (IPBASE_SW_PATCH_VERSION != 07u) )
# error "Vendor specific version numbers of IpBase_Sock.c and IpBase.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define IPBASE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/***********************************************************************************************************************
 *  IpBase_SockIpAddrIsEqualHlp
 **********************************************************************************************************************/
/*! \brief         Check if IP address and family is equal helper
 *  \details       Check if IP address and family of sockets is equal actual comparison
 *  \param[in]     SockAPtr             first IP socket address
 *  \param[in]     SockBPtr             second IP socket address
 *  \return        TRUE                 IP address is equal
 *  \return        FALSE                IP address is not equal
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \trace         CREQ-120246
 **********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(boolean) IpBase_SockIpAddrIsEqualHlp(IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrType) SockAPtr,
                                                                  IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrType) SockBPtr);
/**********************************************************************************************************************
 *  IpBase_SockIpV6AddrIsEqualHlp
 *********************************************************************************************************************/
/*! \brief         Check if IPv6 address is equal helper
 *  \details       Check if IPv6 address is equal actual comparison
 *  \param[in]     SockAPtr             first IPv6 socket address
 *  \param[in]     SockBPtr             second IPv6 socket address
 *  \return        TRUE                 IPv6 address is equal
 *  \return        FALSE                IPv6 address is not equal
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \trace         CREQ-120246
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(boolean) IpBase_SockIpV6AddrIsEqualHlp(
                                        IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrIn6Type) SockAPtr,
                                        IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrIn6Type) SockBPtr);
/***********************************************************************************************************************
 *  IpBase_TcpIpChecksumAddHlp
 **********************************************************************************************************************/
/*! \brief         Adds to TCP/IP checksum helper
 *  \details       Adds a range to TcpIp checksum calculation
 *  \param[in]     DataPtr           pointer to the data
 *  \param[in]     LenByte           data length in bytes
 *  \param[in]     Checksum          current checksum. 0 to start a new checksum calculation
 *  \return        calculated checksum in network byte order
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \trace         CREQ-120246
 **********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(uint32) IpBase_TcpIpChecksumAddHlp(IPBASE_P2CONSTAPPLDATA(uint8) DataPtr, uint32 LenByte,
                                                                uint32 Checksum);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/***********************************************************************************************************************
 *  IpBase_DelSockAddr
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_DelSockAddr(IPBASE_P2VARAPPLDATA(IpBase_SockAddrType) SockPtr, uint16 Family)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal  = E_OK;
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check SockPtr for NULL pointer */
  if ( SockPtr == NULL_PTR )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8 lenByte = 0u;                                                                                                 /* PRQA S 2981 */ /* MD_IpBase_2981 */

    /* #20 Check address family */
    if(Family == IPBASE_AF_INET)
    {
      lenByte = sizeof(IpBase_SockAddrInType);
    }
    else if(Family == IPBASE_AF_INET6)
    {
      lenByte = sizeof(IpBase_SockAddrIn6Type);
    }
    else
    {
      retVal = E_NOT_OK;
    }

    /* #30 Reset all bytes of socket address */
    if(retVal == E_OK)
    {
      /* PRQA S 314 1 */ /* MD_MSR_VStdLibCopy */
      VStdMemSet((IPBASE_P2VARAPPLDATA(void))SockPtr, 0, lenByte); /* SBSW_IPBASE_PASSING_API_POINTER */
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #40 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_DEL_SOCK_ADDR, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_DelSockAddr() */
/***********************************************************************************************************************
 *  IpBase_CopySockAddr
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_CopySockAddr(IPBASE_P2VARAPPLDATA(IpBase_SockAddrType) TgtSockPtr,
                                                    IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrType) SrcSockPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal  = E_OK;
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check SockPtr for NULL pointer */
  if ( (TgtSockPtr == NULL_PTR) || (SrcSockPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8 lenByte = 0u;                                                                                                 /* PRQA S 2981 */ /* MD_IpBase_2981 */

    /* #20 Check address family */
    if(SrcSockPtr->sa_family == IPBASE_AF_INET)
    {
      lenByte = sizeof(IpBase_SockAddrInType);
    }
    else if(SrcSockPtr->sa_family == IPBASE_AF_INET6)
    {
      lenByte = sizeof(IpBase_SockAddrIn6Type);
    }
    else
    {
      retVal = E_NOT_OK;
    }

    /* #30 Copy all bytes of socket address */
    if(retVal == E_OK)
    { /* PRQA S 314 2 */ /* MD_MSR_VStdLibCopy  */
      VStdMemCpy((IPBASE_P2VARAPPLDATA(void))TgtSockPtr, /* SBSW_IPBASE_PASSING_API_POINTER */
                 (IPBASE_P2CONSTAPPLDATA(void))SrcSockPtr, lenByte);
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #40 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_COPY_SOCK_ADDR, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_CopySockAddr() */
/***********************************************************************************************************************
 *  IpBase_CopyIpV6Addr
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(Std_ReturnType) IpBase_CopyIpV6Addr(IPBASE_P2VARAPPLDATA(IpBase_AddrIn6Type) TgtIpAddrPtr,
                                                    IPBASE_P2CONSTAPPLDATA(IpBase_AddrIn6Type) SrcIpAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal  = E_OK;
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check IpAddrPtr for NULL pointer */
  if ( (TgtIpAddrPtr == NULL_PTR) || (SrcIpAddrPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Copy entire IPv6 address */
    /* PRQA S 314 2 */ /* MD_MSR_VStdLibCopy */
    VStdMemCpy((IPBASE_P2VARAPPLDATA(void))TgtIpAddrPtr, /* SBSW_IPBASE_PASSING_API_POINTER */
               (IPBASE_P2CONSTAPPLDATA(void))SrcIpAddrPtr, sizeof(IpBase_AddrIn6Type));
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #30 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_COPY_IPV6_ADDR, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_CopyIpV6Addr() */
/***********************************************************************************************************************
 *  IpBase_SockIpAddrIsEqual
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(boolean) IpBase_SockIpAddrIsEqual(IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrType) SockAPtr,
                                                  IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrType) SockBPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = TRUE;
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check SockPtr for NULL pointer */
  if ( (SockAPtr == NULL_PTR) || (SockBPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Check for equal address using helper function */
    retVal = IpBase_SockIpAddrIsEqualHlp(SockAPtr, SockBPtr); /* SBSW_IPBASE_PASSING_API_POINTER */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #30 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_SOCK_IP_ADDR_IS_EQUAL, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_SockIpAddrIsEqual() */

/***********************************************************************************************************************
 *  IpBase_SockPortIsEqual
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(boolean) IpBase_SockPortIsEqual(IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrType) SockAPtr,
                                                IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrType) SockBPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = TRUE;
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check SockPtr for NULL pointer */
  if ( (SockAPtr == NULL_PTR) || (SockBPtr == NULL_PTR) )
  {
    errorId = IPBASE_E_INV_POINTER;
    retVal  = FALSE;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Check for equal port */ /* PRQA S 310,3305 2 */ /* MD_IpBase_310_SockPtr */
    if( ((IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrInType))SockAPtr)->sin_port !=
        ((IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrInType))SockBPtr)->sin_port )
    {
      retVal = FALSE;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #30 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_SOCK_PORT_IS_EQUAL, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_SockPortIsEqual() */
/***********************************************************************************************************************
 *  IpBase_CalcTcpIpChecksum
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(uint16) IpBase_CalcTcpIpChecksum(IPBASE_P2CONSTAPPLDATA(uint8) DataPtr, uint32 LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 retVal = 0;
  uint8 errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check DataPtr for NULL pointer */
  if ( DataPtr == NULL_PTR )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Calculate checksum */
    retVal = IpBase_CalcTcpIpChecksum2(DataPtr, LenByte, (IPBASE_P2VARAPPLDATA(uint8))NULL_PTR, 0); /* SBSW_IPBASE_PASSING_API_POINTER */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #30 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CALC_TCPIP_CHCECKSUM, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_CalcTcpIpChecksum() */
/***********************************************************************************************************************
 *  IpBase_CalcTcpIpChecksum2
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(uint16) IpBase_CalcTcpIpChecksum2(IPBASE_P2CONSTAPPLDATA(uint8) DataPtr, uint32 LenByte,
                                                  IPBASE_P2CONSTAPPLDATA(uint8) PseudoHdrPtr,
                                                  uint32 PseudoHdrLenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 retVal = 0;
  uint8  errorId = IPBASE_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check DataPtr, PseudoHdrPtr for NULL pointer */
  if ( DataPtr == NULL_PTR )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint32_least idx      = LenByte>>1;  /* 16 bit LenByte, 8 bit idx -> divide by 2 */
    uint32       checksum = 0u;

    /* #20 Add checksum data */
    while ( idx != 0u )
    {
      idx--;
      checksum += (uint16)(((uint32)(DataPtr[(idx << 1)]) << 8)+DataPtr[(idx << 1) + 1u]);
    }
    /* #30 Add odd byte */
    if ( (LenByte & 0x00000001u) != 0u )
    {
      checksum += (uint16)(((uint32)(DataPtr[LenByte - 1u]) << 8));
    }
    /* #40 Add pseudo header checksum */
    if ( PseudoHdrPtr != NULL_PTR )
    {
      idx   = PseudoHdrLenByte >> 1;
      while ( idx != 0u )
      {
        idx--;
        checksum += (uint16)(((uint32)(PseudoHdrPtr[(idx << 1)]) << 8)+PseudoHdrPtr[(idx << 1) + 1u]);
      }
    }
    /* #50 Consider overflow */
    while ( (checksum>>16) != 0u )
    {
      checksum = (uint32)((checksum & 0xFFFFu) + (checksum >> 16));
    }
    /* #60 Build one's complement */
    retVal = (uint16) ~checksum;
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #70 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CALC_TCPIP_CHCECKSUM2, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retVal;
} /* IpBase_CalcTcpIpChecksum2() */
/***********************************************************************************************************************
 *  IpBase_TcpIpChecksumAdd
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_FUNCCODE(uint32) IpBase_TcpIpChecksumAdd(IPBASE_P2CONSTAPPLDATA(uint8) DataPtr, uint32 LenByte,
                                                uint32 Checksum, boolean Stop)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8  errorId = IPBASE_E_NO_ERROR;
  uint32 retChksum = Checksum;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check DataPtr for NULL pointer */
  if ( DataPtr == NULL_PTR )
  {
    errorId = IPBASE_E_INV_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    uint16 lower16bit;

    /* #20 Calculate additive checksum in helper function */
    retChksum = IpBase_TcpIpChecksumAddHlp(DataPtr, LenByte, retChksum); /* SBSW_IPBASE_PASSING_API_POINTER */

    if ( Stop == (boolean)TRUE )
    { /* #30 Consider overflow after last data chunk */
      lower16bit = (uint16)(retChksum);
      retChksum  = (uint16)(lower16bit + (uint16)(retChksum>>16));
      if ( retChksum < lower16bit )
      { /* overflow */
        retChksum++;
      }
      /* #40 Build one's complement after last data chunk */
      retChksum = (uint16) ~retChksum;
      /* #50 Checksum is expected in network byte order -> change byte order depending on host platform */
# if ( CPU_BYTE_ORDER == LOW_BYTE_FIRST )  /* COV_IPBASE_BYTE_ORDER */
      retChksum = IpBase_ByteSwap16((uint16)retChksum);
# endif
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (IPBASE_DEV_ERROR_REPORT == STD_ON)
  /* #60 Check ErrorId and report DET */
  if (errorId != IPBASE_E_NO_ERROR)
  {
    (void)Det_ReportError(IPBASE_MODULE_ID, IPBASE_INSTANCE_ID, IPBASE_API_SID_CALC_TCPIP_CHCECKSUMADD, errorId);
  }
# else
  IPBASE_DUMMY_STATEMENT(errorId);                                                                                      /* PRQA S 3112, 3199 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return retChksum;
} /* IpBase_TcpIpChecksumAdd() */
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  IpBase_SockIpAddrIsEqualHlp
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(boolean) IpBase_SockIpAddrIsEqualHlp(IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrType) SockAPtr,
                                                                  IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrType) SockBPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal  = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check for equal address family */
  if(SockAPtr->sa_family != SockBPtr->sa_family)
  {
    retVal = FALSE;
  }
  else if(SockAPtr->sa_family == IPBASE_AF_INET)
  { /* #20 Check for equal IPv4 address */ /* PRQA S 310,3305 2 */ /* MD_IpBase_310_SockPtr */
    if(((IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrInType))SockAPtr)->sin_addr !=
       ((IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrInType))SockBPtr)->sin_addr)
    {
      retVal = FALSE;
    }
  }
  else if(SockAPtr->sa_family == IPBASE_AF_INET6)
  { /* #30 Check for equal IPv6 address */
    /* PRQA S 310,3305 2 */ /* MD_IpBase_310_SockPtr */
    retVal = IpBase_SockIpV6AddrIsEqualHlp((IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrIn6Type))SockAPtr, /* SBSW_IPBASE_PASSING_API_POINTER */
                                           (IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrIn6Type))SockBPtr);
  }
  else
  { /* #40 Unknown address family */
    retVal = FALSE;
  }

  return retVal;
} /* IpBase_SockIpAddrIsEqualHlp() */
/**********************************************************************************************************************
 *  IpBase_SockIpV6AddrIsEqualHlp
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(boolean) IpBase_SockIpV6AddrIsEqualHlp(
                                        IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrIn6Type) SockAPtr,
                                        IPBASE_P2CONSTAPPLDATA(IpBase_SockAddrIn6Type) SockBPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal  = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check for equal IPv6 address */
  uint16_least i = sizeof(IpBase_AddrIn6Type);

  while(i != 0u)
  {
    i--;
    if( SockAPtr->sin6_addr.addr[i] != SockBPtr->sin6_addr.addr[i] )
    {
      retVal = FALSE;
      break;
    }
  }

  return retVal;
} /* IpBase_SockIpV6AddrIsEqualHlp() */
/***********************************************************************************************************************
 *  IpBase_TcpIpChecksumAddHlp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
IPBASE_LOCAL IPBASE_FUNCCODE(uint32) IpBase_TcpIpChecksumAddHlp(IPBASE_P2CONSTAPPLDATA(uint8) DataPtr, uint32 LenByte,
                                                                uint32 Checksum)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 dataIdx  = 0u;
  uint32 checksumRet  = Checksum;
  uint32 lenByteLoc = LenByte;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add Checksum */
  while ( lenByteLoc > 3u )
  { /* #20 Add 32 bit values */
    lenByteLoc -= 4u;
    checksumRet += IpBase_GetUint32(DataPtr, dataIdx); /* SBSW_IPBASE_PASSING_API_POINTER */
    if ( checksumRet < IpBase_GetUint32(DataPtr, dataIdx) ) /* SBSW_IPBASE_PASSING_API_POINTER */
    { /* overflow */
      checksumRet++;
    }
    dataIdx += 4u;
  }

  if ( lenByteLoc > 1u )
  { /* #30 Add two '32-odd' bytes */
    lenByteLoc -= 2u;
    checksumRet += IpBase_GetUint16(DataPtr, dataIdx); /* SBSW_IPBASE_PASSING_API_POINTER */
    if ( checksumRet < IpBase_GetUint16(DataPtr, dataIdx) ) /* SBSW_IPBASE_PASSING_API_POINTER */
    { /* overflow */
      checksumRet++;
    }
    dataIdx += 2u;
  }

  if ( lenByteLoc > 0u )
  { /* #40 Add one '32-odd' bytes */
    checksumRet += (uint32)(DataPtr[dataIdx]) << 8u;
    if ( checksumRet < ((uint32)(DataPtr[dataIdx]) << 8u) )
    { /* overflow */
      checksumRet++;
    }
  }

  return checksumRet;
} /* IpBase_TcpIpChecksumAddHlp() */
# define IPBASE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  END OF FILE: IpBase_Sock.c
 *********************************************************************************************************************/

