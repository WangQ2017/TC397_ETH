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
 *         \file  TcpIp_IpSec.h
 *        \brief  Implementation of Internet Protocol Security Features
 *
 *      \details  This file is part of the TcpIp submodule.
 *
 *********************************************************************************************************************/

#if !defined (TCPIP_IPSEC_H)
# define TCPIP_IPSEC_H


#include "TcpIp_Lcfg.h"
#if (TCPIP_SUPPORT_IPSEC == STD_ON)
/*
--- LIMITAIONS OF THIS IMPLEMENTATION ------------------------------------------
- no fragmentation supported (rx and tx)
- no support of service types
*/

/*
|0              |8              |16             |24             |
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Next Header   |  Payload Len  |          RESERVED             |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                 Security Parameters Index (SPI)               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Sequence Number Field                      |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                                               |
+                Integrity Check Value-ICV (variable)           |
|                                                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
Example IPv4 Authentication header
*/

/*
|0              |8              |16             |24             |
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Next Header   |  Payload Len  |          RESERVED             |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                 Security Parameters Index (SPI)               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Sequence Number Field                      |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                Initialization Vector (IV)                     |
+                                                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                                               |
+                Integrity Check Value-ICV (variable)           |
|                                                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
Example IPv4 Authentication header for GMAC
*/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIp_IpV4.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define TCPIP_IPSEC_ANTIREPLAYWINDOW       32u  /* Anti replay window is fixed to 32 bits */
#define TCPIP_IPSEC_ESN_LEN                4u   /* Size of the extended sequence number parameter */

#define TCPIP_IPSEC_AUTH_HDR_LEN_FIXED     12u   /* Length in bytes of the fixed part of AH */
#define TCPIP_IPSEC_GMAC_SALT_LEN          4u    /* Length in bytes of the salt value for IpSec Gmac algorithm */
#define TCPIP_IPSEC_GMAC_IV_LEN            8u    /* Length in bytes of the IV value for IpSec Gmac algorithm */

#define TCPIP_IPSEC_SAENTRY_IDLE           0u    /* The SA-entry is currently not in use */
#define TCPIP_IPSEC_SAENTRY_INUSE          1u    /* The SA entry is currently in use */

#define TCPIP_IPSEC_ESN_OVERFLOW_32BIT     0xFFFFFFFFu
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_19.1 */

/**********************************************************************************************************************
 *  TcpIp_IpSec_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the IpSec component.
 *  \details        This function has to be called after IpV4_Init() and before any other function of this module.
 *  \pre            -
 *  \context        TASK / System startup
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_IpSec_Init(void);

/**********************************************************************************************************************
 *  TcpIp_IpSec_PreparePacketforAuthentication
 *********************************************************************************************************************/
/*! \brief          Prepare the Ip packet for protected (or unprotected) transmission
 *  \details        If the packet is to be protected, look up the SA entry index to be used for the packet
 *                  or else proceed with normal processing of the packet
 *  \param[in]      IpV4CtrlIdx            Index of the affected IPv4 controller.
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                         CONSTRAINT: TcpIp_IsIpSecConfigSetUsedOfIpV4Ctrl(IpV4CtrlIdx) is valid
 *  \param[in]      SocketIdx              Socket Idx of the packet
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfIpV4SocketDyn() - 1]
 *  \param[in,out]  IpTxReqDescrPtr        Pointer to Tx request descriptor
 *                                         CONSTRAINT: MUST NOT be NULL_PTR
 *  \param[in]      RemSock                Remote address and port
 *  \return         E_OK                   Packet is ready for transmission
 *  \return         E_NOT_OK               Packet cannot be authenticated, cancel sending
 *  \pre            Only called if IpSecConfig exists for the controller
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_IpSec_PreparePacketforAuthentication(
  TcpIp_IpV4CtrlIterType                      IpV4CtrlIdx,
  TcpIp_SocketDynIterType                     SocketIdx,
  TCPIP_P2V(TcpIp_IpTxRequestDescriptorType)  IpTxReqDescrPtr,
  IpBase_SockAddrInType                       RemSock);


/**********************************************************************************************************************
 *  TcpIp_IpSec_ProcessTxPacket
 *********************************************************************************************************************/
/*! \brief          IpSec processing of Tx Ip packet
 *  \details        The function should only be invoked if valid IpConfigSet exists
 *  \param[in]      IpV4CtrlIdx      IP Controller Index
 *                                   CONSTRAINT: [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                   CONSTRAINT: TcpIp_IsIpSecConfigSetUsedOfIpV4Ctrl(IpV4CtrlIdx) is valid
 *  \param[in]      IpTxReqDescrPtr  Pointer to Tx request descriptor
 *  \param[in]      IpPacketPtr      Pointer to Ip packet buffer. ICV is inserted if return is E_OK
 *                                   CONSTRAINT: MUST NOT be NULL_PTR and MUST have sufficient space
 *                                               Enforced by SBSW_IPSEC_IP_PKT_PTR_CHECKED
 *  \param[in]      IpTotalLen       Number of bytes in Ip Packet
 *  \param[in]      IpNextHeader     Upper layer protocol header
 *  \return         E_OK             Packet secured successfully, transmit
 *  \return         E_NOT_OK         Packet was not secured successfully, do not transmit
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_IpSec_ProcessTxPacket(
  TcpIp_IpV4CtrlIterType                      IpV4CtrlIdx,
  TCPIP_P2C(TcpIp_IpTxRequestDescriptorType)  IpTxReqDescrPtr,
  TCPIP_P2V(uint8)                            IpPacketPtr,
  uint16                                      IpTotalLen,
  uint8                                       IpNextHeader
);

/**********************************************************************************************************************
 *  TcpIp_IpSec_ProcessRxPacket
 *********************************************************************************************************************/
/*! \brief          IpSec processing of received Ip packet before forwarding to upper layer
 *  \details        -
 *  \param[in]      IpV4CtrlIdx        IP Controller Index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                     CONSTRAINT: TcpIp_IsIpSecConfigSetUsedOfIpV4Ctrl(IpV4CtrlIdx) is valid
 *  \param[in]      IpPacketPtr        Pointer to the IP buffer.
 *  \param[in]      IpPayloadLen       Length of the IP paylaod in bytes.
 *  \param[out]     IpProtcolPtr       Pointer to the upper layer protocol value of the packet
 *                                     CONSTRAINT: MUST NOT be null
 *  \param[out]     IpSecHdrLenPtr     Pointer to the length of IpSec header(s) processed in packet
 *                                     CONSTRAINT: MUST NOT be null
 *  \return         E_OK               IpSec processing successful, packet can be forwarded
 *  \return         E_NOT_OK           IpSec unsuccessful, packet cannot be forwarded to upper layer
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_IpSec_ProcessRxPacket(
  TcpIp_IpV4CtrlIterType   IpV4CtrlIdx,
  TCPIP_P2C(uint8)         IpPacketPtr,
  uint16                   IpPayloadLen,
  TCPIP_P2V(uint8)         IpProtcolPtr,
  TCPIP_P2V(uint16)        IpSecHdrLenPtr);

/**********************************************************************************************************************
 * TcpIp_IpSec_AddSaEntryPair()
 *********************************************************************************************************************/
/*! \brief          Adds a pair of SA entries
 *  \details        This function first checks if there are Csm jobs configured for the algorithm
 *                  and then allocates a pair of SA entries
 *  \param[in]      LocalAddrIdx      Local Ip Address Idx
 *  \param[in]      SaInfoPtr         Struct of SA entry information
 *                                    CONSTRAINT: [SMI-540960]
 *  \return         E_OK              SA Entry Pair have been added successfully
 *  \return         E_NOT_OK          SA Entry Pair could not be added
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_IpSec_AddSaEntryPair(
  TcpIp_LocalAddrIterType           LocalAddrIdx,
  TCPIP_P2C(TcpIp_IpSecSaInfoType)  SaInfoPtr);

/**********************************************************************************************************************
 * TcpIp_IpSec_DelSaEntryPair()
 *********************************************************************************************************************/
/*! \brief          Remove an SA Pair from the SAD.
 *  \details        This API when invoked deletes an SA entry pair that was previously added by calling
 *                  TcpIp_IpSecSaEntryPairAdd.
 *  \param[in]      InSpi     SPI of the SA pair to be deleted. Outbound SA shall be determined from  inbound SA
 *  \return         E_OK      SA Entry pair have been removed successfully
 *  \return         E_NOT_OK  SA Entry pair could not be deleted
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_IpSec_DelSaEntryPair(
  uint32               InSpi);

#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
/**********************************************************************************************************************
 * TcpIp_IpSec_GetNumSaEntryPairs()
 *********************************************************************************************************************/
/*! \brief          Returns the number of valid Sa entry pairs
 *  \details        -
 *  \return         NumSaEntryPairs  Number of SA entry pairs
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(uint32, TCPIP_CODE) TcpIp_IpSec_GetNumSaEntryPairs(void);

/**********************************************************************************************************************
 * TcpIp_IpSec_GetSaEntryPairsStatus()
 *********************************************************************************************************************/
/*! \brief          Retrieves the statuses of valid SA entry pairs
 *  \details        This function fills the provided buffer with the IpSecStatus of valid
 *                  SA entry pairs
 *  \param[in]      SaEntryStatusPtr      Buffer to store retrieved Sa entry pair statuses
 *                                        CONSTRAINT: [SMI-540959]
 *                                        (NumSaEntryPairs * sizeof(TcpIp_IpSecSaStatusType)) bytes
 *  \param[in]      NumSaEntryPairs       Number of Sa entry pairs in SAD
 *  \return         E_OK                  Status of all Sa entry pairs retrieved successfully
 *  \return         E_NOT_OK              Status of Sa entry pairs NOT retrieved
 *  \pre            The TcpIp_IpSec_GetNumSaEntryPairs() must be invoked before this function
 *                  to get value of NumSaEntryPairs
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_IpSec_GetSaEntryPairsStatus(
  TCPIP_P2V(TcpIp_IpSecSaStatusType)  SaEntryStatusPtr,
  uint32                              NumSaEntryPairs);
#endif /* (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON) */

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* (TCPIP_SUPPORT_IPSEC == STD_ON) */
#endif  /* TCPIP_IPSEC_H */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_IpSec.h
 *********************************************************************************************************************/
