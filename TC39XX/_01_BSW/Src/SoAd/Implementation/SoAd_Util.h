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
/**        \file  SoAd_Util.h
 *        \brief  Socket Adaptor header file
 *
 *      \details  Vector static code header file for AUTOSAR Socket Adaptor sub-component Util.
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

#if !defined (SOAD_UTIL_H)
# define SOAD_UTIL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "SoAd.h"
# include "SoAd_Priv.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define SOAD_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/**********************************************************************************************************************
 *  SoAd_Util_CompareIpAddr()
 *********************************************************************************************************************/
/*! \brief        Compares two IP addresses.
 *  \details      -
 *  \param[in]    Domain          IP domain (IPv4/6).
 *  \param[in]    IpAddrAPtr      Pointer to first IP address.
 *  \param[in]    IpAddrBPtr      Pointer to second IP address.
 *  \param[in]    AllowWildcards  Flag to indicate if wildcards are allowed in first IP address.
 *  \return       E_OK            IP addresses are equal.
 *  \return       E_NOT_OK        IP addresses are not equal.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Util_CompareIpAddr(
  SoAd_DomainType Domain,
  SoAd_IpAddrConstPtrType IpAddrAPtr,
  SoAd_IpAddrConstPtrType IpAddrBPtr,
  boolean AllowWildcards);

# if ( SOAD_TX_DYN_LEN == STD_ON )
/**********************************************************************************************************************
 *  SoAd_Util_UpdatePduHdrLen
 *********************************************************************************************************************/
/*! \brief        Updates PDU header length field with a new length.
 *  \details      -
 *  \param[in]    PduHeaderLen    New length of PDU header.
 *  \param[in]    BufPtr          Pointer to first byte of PDU header.
 *                                [range: at least PDU header length]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \config       SOAD_TX_DYN_LEN
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Util_UpdatePduHdrLen(
  SoAd_PduHdrLenType PduHeaderLen,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr);
# endif /* SOAD_TX_DYN_LEN == STD_ON */

/**********************************************************************************************************************
 *  SoAd_Util_CheckForWildcards
 *********************************************************************************************************************/
/*! \brief        Checks socket address for containing wildcards.
 *  \details      -
 *  \param[in]    AddrCheck       Pointer to socket address to be checked.
 *  \param[out]   IpAddrIsAny     Pointer to indicate if IP address is any (wildcard).
 *  \param[out]   PortIsAny       Pointer to indicate if port is any (wildcard).
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Util_CheckForWildcards(
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) AddrCheck,
  P2VAR(boolean, AUTOMATIC, SOAD_APPL_DATA) IpAddrIsAny,
  P2VAR(boolean, AUTOMATIC, SOAD_APPL_DATA) PortIsAny);

/**********************************************************************************************************************
 *  SoAd_Util_CopySockAddr
 *********************************************************************************************************************/
/*! \brief        Copies a source socket address to a target socket address struct.
 *  \details      -
 *  \param[out]   TgtSockAddrPtr    Pointer to target socket address.
 *                                  [Points to one of the following structs depending on value of struct element domain
 *                                  of parameter SrcSockAddrPtr (expecting SoAd_SockAddrInet6Type >
 *                                  SoAd_SockAddrInetType so TgtSockAddrPtr may point to SoAd_SockAddrInet6Type even if
 *                                  domain of SrcSockAddrPtr indicates SoAd_SockAddrInetType):
 *                                    - SoAd_SockAddrInetType for IPv4
 *                                    - SoAd_SockAddrInet6Type for IPv6]
 *  \param[in]    SrcSockAddrPtr    Pointer to source socket address.
 *                                  [Points to one of the following structs depending on value of struct element
 *                                  domain:
 *                                    - SoAd_SockAddrInetType for IPv4
 *                                    - SoAd_SockAddrInet6Type for IPv6]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Util_CopySockAddr(
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) TgtSockAddrPtr,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) SrcSockAddrPtr);

/**********************************************************************************************************************
 *  SoAd_Util_CopyPduHdr2Buf
 *********************************************************************************************************************/
/*! \brief        Copies a PDU header to a buffer.
 *  \details      -
 *  \param[in]    PduHeaderId   PDU header identifier.
 *  \param[in]    PduHeaderLen  PDU header length.
 *  \param[out]   BufPtr        Pointer to buffer.
 *  \param[in]    Offset        Offset in PDU header.
 *                              [range: Offset < SOAD_PDU_HDR_SIZE]
 *  \param[in]    Length        Length of PDU header segment to be copied.
 *                              [range: Length <= (SOAD_PDU_HDR_SIZE - Offset)]
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Util_CopyPduHdr2Buf(
  SoAd_PduHdrIdType PduHeaderId,
  SoAd_PduHdrLenType PduHeaderLen,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  PduLengthType Offset,
  PduLengthType Length);

/**********************************************************************************************************************
 *  SoAd_Util_GetSupportedPduLength()
 *********************************************************************************************************************/
 /*! \brief        Returns a requested value if it fits into the PDU length type or returns the maximum PDU length.
  *  \details      -
  *  \param[in]    Length                  Length to be checked.
  *  \return       SupportedPduLength      Returns value of parameter Length or maximum PDU length.
  *  \pre          -
  *  \context      TASK
  *  \reentrant    TRUE
  *  \synchronous  TRUE
  *********************************************************************************************************************/
FUNC(PduLengthType, SOAD_CODE) SoAd_Util_GetSupportedPduLength(
  uint32 Length);

# define SOAD_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_Rule20.10_0342 */

#endif /* SOAD_UTIL_H */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_Util.h
 *********************************************************************************************************************/
