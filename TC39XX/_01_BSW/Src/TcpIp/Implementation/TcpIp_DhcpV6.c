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
 *         \file  TcpIp_DhcpV6.c
 *        \brief  Implementation of Dynamic Host Configuration Protocol for IPv6 - Client (DHCPv6 Client)
 *
 *      \details  This file is part of the TcpIp IPv6 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv6 submodule. >> TcpIp_IpV6.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/


/* PRQA S 0828 EOF */ /* MD_MSR_1.1 */

#define TCPIP_DHCPV6_SOURCE

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "TcpIp.h"
#include "TcpIp_Priv.h"
#include "TcpIp_DhcpV6.h"
#include "TcpIp_DhcpV6_Cbk.h"
#include "TcpIp_Lcfg.h"
#include "IpBase.h"
#include "vstdlib.h"

#include "TcpIp_IpV6_Priv.h"

#if (TCPIP_SUPPORT_DNS == STD_ON)
# include "Dns.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined (STATIC)
# define STATIC static
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
# define TCPIP_DHCPV6_VENABLE_CANOE_WRITE_STRING  STD_OFF
# define TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS STD_ON
#else
# define TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS             STD_OFF
#endif

#define TCPIP_DHCPV6_MAX_TRANS_ID                             0x00FFFFFFU
#define TCPIP_DHCPV6_INV_TRANS_ID                             0xFF000000U

#define TCPIP_DHCPV6_USE_RAND_FUNCTION STD_ON

#define TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN                     3u
#define TCPIP_DHCPV6_OPT_REQ_OPT_LIST_EXTRA_OPT_OFS           1u

/* dhcp Iana options offset */
#define TCPIP_DHCPV6_IANA_OPT_OFF_IAIDNBO                     0u
#define TCPIP_DHCPV6_IANA_OPT_OFF_T1NBO                       4u
#define TCPIP_DHCPV6_IANA_OPT_OFF_T2NBO                       8u

/* dhcp Iana address option offset */
#define TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_ADDR                   0u
#define TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_PREFLIFENBO            16u
#define TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_VALDLIFENBO            20u

/* dhcp elapsed time option offset */
#define TCPIP_DHCPV6_ELAPSEDTIME_OPT_OFF_ELAPSEDTIMENBO       0u

/* dhcp elapsed time option offset */
#define TCPIP_DHCPV6_STATUSCODE_OPT_OFF_STATUSCODENBO         0u

/* dhcp duid type 1 option offset */
#define TCPIP_DHCPV6_DUID1_OPT_OFF_TYPENBO                    0u
#define TCPIP_DHCPV6_DUID1_OPT_OFF_HWTYPENBO                  2u
#define TCPIP_DHCPV6_DUID1_OPT_OFF_TIMENBO                    4u
#define TCPIP_DHCPV6_DUID1_OPT_OFF_PHYSADDR                   8u

/* dhcp user option for fqdn */
#define TCPIP_DHCPV6_OPT_ID_CLIENT_FQDN        39u
#define TCPIP_FQDN_OPT_FLAGS_DNLEN              2u

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/*  */
#define TCPIP_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
# if (TCPIP_DHCPV6_VENABLE_CANOE_WRITE_STRING == STD_ON)
STATIC sint8 VCanoeWriteStrBuffer[256];
# endif
#endif

#define TCPIP_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*  */
#define TCPIP_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define TCPIP_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*  */
#define TCPIP_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define TCPIP_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*  */
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
STATIC VAR(TcpIp_DhcpV6_IaAddrLeaseType, TCPIP_VAR_NOINIT) TcpIp_DhcpV6_IaAddrLeases[1];
#endif

#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
STATIC VAR(TcpIp_DhcpV6_OptIaAddrType,   TCPIP_VAR_NOINIT) TcpIp_DhcpV6_IaAddrBuf[1];
#endif

STATIC VAR(TcpIp_DhcpV6_TimeType, TCPIP_VAR_NOINIT) TcpIp_DhcpV6_Time;

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*  */
#define TCPIP_START_SEC_CONST_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

STATIC CONST(uint16, TCPIP_CONST) TcpIp_DhcpV6_OptionRequestList[TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN] =
              { TCPIP_DHCPV6_OPT_IA_NA, TCPIP_DHCPV6_OPT_DNS_SERVERS, TCPIP_DHCPV6_OPT_DOMAIN_LIST };

#define TCPIP_STOP_SEC_CONST_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*  */
#define TCPIP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*  */
#define TCPIP_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define TCPIP_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */




/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VGetNextOption()
 *********************************************************************************************************************/
/*! \brief          Obtain DhcpV6 option offset and option code from the payload
 *  \details        -
 *  \param[in]      DataPtr    DhcpV6 payload buffer
 *  \param[in]      DataLen    DhcpV6 packet length
 *  \param[in,out]  OptPosPtr  This structure stores information of the DhcpV6 option
 *  \return         TRUE       The Dhcpv6 option was processed and information stored in OptPosPtr
 *  \return         FALSE      The Dhcpv6 option could not be processed, OptPosPtr does not contain valid information
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *********************************************************************************************************************/
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV6_VGetNextOption(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen,
  P2VAR(TcpIp_DhcpV6_OptLocationType, AUTOMATIC, TCPIP_APPL_VAR) OptPosPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptIaNa()
 *********************************************************************************************************************/
/*! \brief          Decode the IaNa non temporary address options in dhcpv6 packet
 *  \details        -
 *  \param[in]      DataPtr   DhcpV6 payload buffer
 *  \param[in]      DataLen   DhcpV6 packet length
 *  \param[in,out]  IaNaPtr   IaNa option information is stored here
 *                            The information in IaNa is valid only if Valid flag is set in IaNa
 *  \return         E_OK      The IaNa option was processed successfully, IaNaPtr has valid information
 *  \return         E_NOT_OK  The IaNa option was not processed, IaNaPtr is not valid
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptIaNa(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                 DataPtr,
  uint16                                                     DataLen,
  P2VAR(TcpIp_DhcpV6_OptIaNaType, AUTOMATIC, TCPIP_APPL_VAR) IaNaPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddRawOpt()
 *********************************************************************************************************************/
/*! \brief        Add dhcpv6 user option into the message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    MsgPtr           Dhcpv6 message buffer, cannot be NULL_PTR
 *  \param[in]    OptType          Type of user option
 *  \param[out]   OptDataPtr       Option data buffer, cannot be NULL_PTR
 *  \param[out]   OptDataLen       Option data length
 *  \return       E_OK             Option added successfully
 *  \pre          Message buffer and option data buffers are valid pointers
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddRawOpt(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  uint16                                                 OptType,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)             OptDataPtr,
  uint16                                                 OptDataLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptStatusCode()
 *********************************************************************************************************************/
/*! \brief        Validate and process status code option in dhcpv6 messages
 *  \details      -
 *  \param[in]    DataPtr         DhcpV6 payload buffer
 *  \param[in]    DataLen         DhcpV6 packet length
 *  \param[out]   StatusCodePtr   Processed status code is stored here
 *  \return       E_OK            Status code processed successfully
 *  \return       E_NOT_OK        Invalid header length of status code
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptStatusCode(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       DataPtr,
  uint16                                                           DataLen,
  P2VAR(TcpIp_DhcpV6_OptStatusCodeType, AUTOMATIC, TCPIP_APPL_VAR) StatusCodePtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptIaAddr()
 *********************************************************************************************************************/
/*! \brief        Validate and process Iana Address option in dhcpv6 message
 *  \details      Process Iana address options (including Iana address status code)
 *  \param[in]    DataPtr           DhcpV6 payload buffer
 *  \param[in]    DataLen           DhcpV6 packet length
 *  \param[out]   DynIaAddrPtr      Dynamic Iana addresses is stored here
 *  \param[in]    DynIaAddrCount    Number of dynamic Iana addresses
 *  \param[out]   IaAddrPtr         Ia Address option values are stored here
 *  \return       E_OK              Ia Address processed successfully
 *  \return       E_NOT_OK          Invalid header length / error code in option
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptIaAddr(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                   DataPtr,
  uint16                                                       DataLen,
#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
  P2VAR(TcpIp_DhcpV6_OptIaAddrType, AUTOMATIC, TCPIP_APPL_VAR) DynIaAddrPtr,
  uint8                                                        DynIaAddrCount
#else
  P2VAR(TcpIp_DhcpV6_OptIaAddrType, AUTOMATIC, TCPIP_APPL_VAR) IaAddrPtr
#endif
);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxReply()
 *********************************************************************************************************************/
/*! \brief        Function to handle dhcpv6 replies
 *  \details      Invokes processing routines for different dhcpv6 reply messages
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DataPtr          DhcpV6 payload buffer
 *  \param[in]    DataLen          DhcpV6 packet length
 *  \pre          DhcpV6 must be configured for the controller index.
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRxReply(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRestartAddressAssignment()
 *********************************************************************************************************************/
/*! \brief        Restart address assignment for dhcpv6 configured address of Ip controller
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DelayMs          Idle time in millisecondss
 *  \pre          DhcpV6 must be configured for the controller index.
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRestartAddressAssignment(TcpIp_IpV6CtrlIterType IpCtrlIdx, uint32 DelayMs);

#if (TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddUserOptions()
 *********************************************************************************************************************/
/*! \brief        Add TX user options into the message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr           Message data buffer
 *  \return       E_OK             User option added successfully (always returns successful)
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddUserOptions(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);
#endif

/**********************************************************************************************************************
 * TcpIp_DhcpV6_VIsTxUserOption()
 *********************************************************************************************************************/
/*! \brief        Check if the User option is for TX or RX
 *  \details      -
 *  \param[in]    DhcpUserOptionIdx     DhcpV6 User option index
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \return       TRUE                  User option is configured for TX
 *  \return       FALSE                 User option is configured for RX
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV6_VIsTxUserOption(
  TcpIp_DhcpUserOptionIterType       DhcpUserOptionIdx);

/**********************************************************************************************************************
 * TcpIp_DhcpV6_VLookupUserOption()
 *********************************************************************************************************************/
/*! \brief        Retreive the user option index from the user option list
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    OptType          DhcpV6 User option type
 *  \return       OptionIdx        Index of the User option in the User option list
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(TcpIp_DhcpUserOptionIterType, TCPIP_CODE) TcpIp_DhcpV6_VLookupUserOption(
  TcpIp_IpV6CtrlIterType             IpCtrlIdx,
  uint16                             OptType);

/**********************************************************************************************************************
 * TcpIp_DhcpV6_VGetEventType()
 *********************************************************************************************************************/
/*! \brief        Determine which event shall be notified for the message
 *  \details      -
 *  \param[in]    MsgType          DhcpV6 message type
 *  \return       DhcpEvent        DhcpV6 event Type
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(TcpIp_DhcpEventType, TCPIP_CODE) TcpIp_DhcpV6_VGetEventType(
  uint8  MsgType);

/**********************************************************************************************************************
 * TcpIp_DhcpV6_VHandleRxUserOption()
 *********************************************************************************************************************/
/*! \brief        Process the DhcpV6 user option in the received messages
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    OptCode          User option code
 *  \param[in]    OptPtr           User option data buffer
 *  \param[in]    OptLen           Length of the user option code
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleRxUserOption(
  TcpIp_IpV6CtrlIterType                       IpCtrlIdx,
  uint16                                       OptCode,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)   OptPtr,
  uint16                                       OptLen
);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCompareBytes()
 *********************************************************************************************************************/
/*! \brief        Compare bytes of two buffers
 *  \details      -
 *  \param[in]    Data1Ptr          Buffer 1
 *  \param[in]    Data1Len          Buffer 1 length
 *  \param[in]    Data2Ptr          Buffer 2
 *  \param[in]    Data2Len          Buffer 2 length
 *  \return       TRUE              Buffers match
 *  \return       FALSE             Buffers are different
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV6_VCompareBytes(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) Data1Ptr,
  uint16                                     Data1Len,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) Data2Ptr,
  uint16                                     Data2Len);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VInitClientId()
 *********************************************************************************************************************/
/*! \brief        Initialize client identifier
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VInitClientId(TcpIp_IpV6CtrlIterType IpCtrlIdx);

#if (TCPIP_DHCPV6_USE_RAND_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VGetRandomValue()
 *********************************************************************************************************************/
/*! \brief        Generate random value within given range
 *  \details      -
 *  \param[in]    MinValue      Lower range
 *  \param[in]    MaxValue      Upper range
 *  \return       RndValue      Random value generated
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(uint32, TCPIP_CODE) TcpIp_DhcpV6_VGetRandomValue(
  uint32 MinValue,
  uint32 MaxValue);
#endif

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetEventTime()
 *********************************************************************************************************************/
/*! \brief             Configure the next event timestamp by adding value to the IpV6 time
 *  \details           -
 *  \param[in,out]     TimestampPtr    Time object to add to
 *  \param[in]         Milliseconds    Time to be added in milliseconds
 *  \pre               -
 *  \context           TASK|ISR
 *  \reentrant         FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) TcpIp_DhcpV6_VSetEventTime(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA)  TimestampPtr,
  uint32                                                    Milliseconds);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTimeAddMs()
 *********************************************************************************************************************/
/*! \brief             Add time in milliseconds to a given timestamp
 *  \details           -
 *  \param[in,out]     TimestampPtr    Time object to add to
 *  \param[in]         Milliseconds    Time to be added in milliseconds
 *  \pre               -
 *  \context           TASK|ISR
 *  \reentrant         FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VTimeAddMs(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA) TimestampPtr,
  uint32                                                   Milliseconds);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTimeSet()
 *********************************************************************************************************************/
/*! \brief        Set timestamp with given values
 *  \details      -
 *  \param[out]   TimestampPtr    Time variable to update
 *  \param[in]    Seconds         Seconds to add
 *  \param[in]    Milliseconds    Milliseconds to add
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) TcpIp_DhcpV6_VTimeSet(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA)  TimestampPtr,
  uint32                                                    Seconds,
  uint32                                                    Milliseconds);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTimeCompare()
 *********************************************************************************************************************/
/*! \brief        Compare two timestamps and return which is lower
 *  \details      -
 *  \param[in]    RefTimestamp      Reference time variable
 *  \param[in]    Timestamp         Time variable to check
 *  \return       TRUE              Reference time is lower
 *  \return       FALSE             Given time is lower
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(boolean, IPV6_CODE) TcpIp_DhcpV6_VTimeCompare(
  TcpIp_DhcpV6_TimeType  RefTimestamp,
  TcpIp_DhcpV6_TimeType  Timestamp);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetLifetimeS()
 *********************************************************************************************************************/
/*! \brief            Calculate and store lifetime into given time object
 *  \details          -
 *  \param[in]        TimestampPtr       Current time in dhcpv6
 *  \param[in]        LifetimeS          Lifetime to be updated
 *  \param[out]       NextEventTimePtr   Updated valid lifetime is stored in this
 *  \pre              -
 *  \context          TASK|ISR
 *  \reentrant        FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VSetLifetimeS(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_VAR) TimestampPtr,
  uint32                                                  LifetimeS,
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_VAR) NextEventTimePtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VChangeState()
 *********************************************************************************************************************/
/*! \brief            Update the state of DhcpV6
 *  \details          -
 *  \param[in]        DhcpV6DataIdx     Index of the DhcpV6 data structure
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Data()-1]
 *  \param[in]        NewState          New state to be updated
 *  \pre              -
 *  \context          TASK
 *  \reentrant        TRUE
 *********************************************************************************************************************/
STATIC INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VChangeState(
  TcpIp_SizeOfDhcpV6DataType    DhcpV6DataIdx,
  uint8                         NewState);


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VWriteOptionCode()
 *********************************************************************************************************************/
/*! \brief        Helper function to update option code into data buffer
 *  \details      -
 *  \param[out]   DataPtr          DhcpV6 payload buffer
 *  \param[in]    OptCode          Option code to write
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VWriteOptionCode(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) DataPtr,
  uint16                                  OptCode);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VWriteOptionLen()
 *********************************************************************************************************************/
/*! \brief        Helper function to write option length into data buffer
 *  \details      -
 *  \param[in]    DataPtr          DhcpV6 payload buffer
 *  \param[in]    OptLen           Option length to write
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VWriteOptionLen(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) DataPtr,
  uint16                                  OptLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VReadOptionCode()
 *********************************************************************************************************************/
/*! \brief        Helper function to read option code from dhcpv6 data buffer
 *  \details      -
 *  \param[in]    DataPtr          DhcpV6 payload buffer
 *  \return       optCode          Option code
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC INLINE FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV6_VReadOptionCode(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetRetransParams()
 *********************************************************************************************************************/
/*! \brief        Update retransmission parameters for dhcpv6 messages
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    IRT              Init Retransmission time
 *  \param[in]    MRT              Maximum retransmission time
 *  \param[in]    MRC              Maximumm retransmission count
 *  \param[in]    MRD              Maximum retransmission duration
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VSetRetransParams(
  TcpIp_IpV6CtrlIterType IpCtrlIdx,
  uint32                 IRT,
  uint32                 MRT,
  uint8                  MRC,
  uint32                 MRD);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCalcTimeout()
 *********************************************************************************************************************/
/*! \brief        Calculate and update timeout values for dhcpv6 message retransmission
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   TimePtr          Time object to store updated timeout value
 *  \param[in]    IsSolicit        Solicited request flag
 *  \return       E_OK             Timeout value has been updated successfully
 *  \return       E_NOT_OK         Maximum retries of dhcpv6 message has been reached or maximum retransmission
 *                                 duration expired
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VCalcTimeout(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_VAR) TimePtr,
  boolean                                                 IsSolicit);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VOptStackPushDataPos()
 *********************************************************************************************************************/
/*! \brief             Push dhcpv6 option offset value into options stack
 *  \details           -
 *  \param[in,out]     MsgPtr    Dhcpv6 message buffer
 *  \return            E_OK      Option offset pushed into stack successfully
 *  \return            E_NOT_OK  Stack full, push operation failed
 *  \pre               -
 *  \context           TASK|ISR
 *  \reentrant         FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VOptStackPushDataPos(
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VOptStackPopDataPos()
 *********************************************************************************************************************/
/*! \brief        Pop dhcpv6 option offset value from options stack
 *  \details      -
 *  \param[in]    MsgPtr       Dhcpv6 message buffer
 *  \param[out]   DataPosPtr   Option offset is stored here
 *  \return       E_OK         Offset popped successfully
 *  \return       E_NOT_OK     Stack empty, no data to pop
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VOptStackPopDataPos(
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_VAR)               DataPosPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBeginMessage()
 *********************************************************************************************************************/
/*! \brief        Update the dhcpv6 message buffer with the message parameters
 *  \details      Message type, transaction id are updated
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr           Message data buffer
 *  \param[in]    MsgType          Message type
 *  \return       E_OK             Message built successfully (always return success)
 *  \return       E_NOT_OK         Invalid Ip controller index (DhcpV6 not configured)
 *  \pre          Message data buffer is a valid pointer
 *                DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBeginMessage(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  uint8                                                  MsgType);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VEndMessage()
 *********************************************************************************************************************/
/*! \brief        Update the user options into the dhcpv6 message buffer
 *  \details      Add user into options if enabled
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr           Message data buffer
 *  \return       MsgBufPos        The end offset of the message buffer
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV6_VEndMessage(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_DATA) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptClientIdent()
 *********************************************************************************************************************/
/*! \brief        Update client identifier info into the message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx    Index of IP controller
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr       Message data buffer
 *  \return       E_OK         Client option added successfully
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptClientIdent(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptServerIdent()
 *********************************************************************************************************************/
/*! \brief        Update server identifier info into the message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx    Index of IP controller
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr       Message data buffer
 *  \return       E_OK         Server option added successfully
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptServerIdent(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBeginOptIaNa()
 *********************************************************************************************************************/
/*! \brief        Build Iana option header into the message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx    Index of IP controller
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr       Message data buffer
 *  \param[in]    IaId         Ia address Id
 *  \param[in]    T1           Timeout 1 value (in dhcpv6 Iana option)
 *  \param[in]    T2           Timeout 2 value (in dhcpv6 Iana option)
 *  \return       E_OK         Iana option header created successfully
 *  \return       E_NOT_OK     No space in message stack to store option values
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBeginOptIaNa(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  uint32                                                 IaId,
  uint32                                                 T1,
  uint32                                                 T2);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VEndOptIaNa()
 *********************************************************************************************************************/
/*! \brief        Update the Iana Option length into the iana header in message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx    Index of IP controller
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr       Message data buffer
 *  \return       E_OK         Iana option built successfully
 *  \return       E_NOT_OK     Iana option not built successfully
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VEndOptIaNa(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)  MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBeginOptIaAddr()
 *********************************************************************************************************************/
/*! \brief        Update the Ia address header information into message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx           Index of IP controller
 *                                    CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr              Message data buffer
 *  \param[in]    AddrPtr             Ia address
 *  \param[in]    PreferredLifetime   Preferred lifetime
 *  \param[in]    ValidLifetime       Valid lifetime
 *  \return       E_OK                Iana address header created successfully
 *  \return       E_NOT_OK            No space in message stack to store option values
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBeginOptIaAddr(
  TcpIp_IpV6CtrlIterType                                   IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)   MsgPtr,
  P2CONST(IpBase_AddrIn6Type, AUTOMATIC, TCPIP_APPL_DATA)  AddrPtr,
  uint32                                                   PreferredLifetime,
  uint32                                                   ValidLifetime);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VEndOptIaAddr()
 *********************************************************************************************************************/
/*! \brief        Update the Ia address option length into the Ia address option header
 *  \details      -
 *  \param[in]    IpCtrlIdx    Index of IP controller
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr       Message data buffer
 *  \return       E_OK         Iana address option added successfully
 *  \return       E_NOT_OK     Iana address option not built successfully
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VEndOptIaAddr(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)  MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptReqOpt()
 *********************************************************************************************************************/
/*! \brief        Add array of options into message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \param[in]    OptCodeArray   Array of options to add into message buffer
 *  \param[in]    OptCodeCount   Number of options in the array
 *  \return       E_OK           Option list added successfully
 *  \pre          OptCodeArray is valid
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptReqOpt(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)  MsgPtr,
  P2CONST(uint16, AUTOMATIC, TCPIP_APPL_DATA)             OptCodeArray,
  uint8                                                   OptCodeCount);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptElapsedTime()
 *********************************************************************************************************************/
/*! \brief        Add elapsed time option into dhcpv6 message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
  *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VAddOptElapsedTime(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildSolicit()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 solicit message
 *  \details      Invoke helper functions to build a solicit message (as per [RFC3315 17.1.1. Creation of Solicit Messages])
 *  \param[in]    IpCtrlIdx      Index of IP controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildSolicit(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildInfoRequest()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 info request message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildInfoRequest(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRelease()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 reelase message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRelease(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRenew()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 renew message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRenew(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRebind()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 rebind message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRebind(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildDecline()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 decline message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildDecline(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildConfirm()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 confirm message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildConfirm(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRequest()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 request message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \return       BUFREQ_E_BUSY
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRequest(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTriggerTx()
 *********************************************************************************************************************/
/*! \brief        Trigger tx for the dhcpv6 message
 *  \details      -
 *  \param[out]   MsgPtr         Message data buffer
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VTriggerTx(P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTxMessage()
 *********************************************************************************************************************/
/*! \brief        Transmit dhcpv6 message as Udp packet
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Packet transmission successful
 *  \return       E_NOT_OK       Packet not transmitted successfully
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VTxMessage(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptPreference()
 *********************************************************************************************************************/
/*! \brief        Validate and process the preference option
 *  \details      -
 *  \param[in]    DataPtr              Data buffer
 *  \param[in]    DataLen              Length of dhcpv6 message
 *  \param[out]   PreferenceValuePtr   Preference value is stored here . Valid if return is E_OK
 *  \return       E_OK                 Preference option processed successfully
 *  \return       E_NOT_OK             Preference option not obtained
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptPreference(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR)    PreferenceValuePtr);

#if (TCPIP_SUPPORT_DNS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptDnsServers()
 *********************************************************************************************************************/
/*! \brief        Decode dns server options
 *  \details      -
 *  \param[in]    DataPtr              Data buffer
 *  \param[in]    DataLen              Length of dhcpv6 message
 *  \param[in]    DnsServersOptPtr     Dns server values are stored here
 *  \return       E_OK                 Dns server option processed successfully
 *  \return       E_NOT_OK             Dns server option not obtained
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptDnsServers(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       DataPtr,
  uint16                                                           DataLen,
  P2VAR(TcpIp_DhcpV6_OptDnsServersType, AUTOMATIC, TCPIP_APPL_VAR) DnsServersOptPtr);
#endif

#if (TCPIP_SUPPORT_DNS == STD_ON)
/**********************************************************************************************************************
 *  ()
 *********************************************************************************************************************/
/*! \brief        Decode and obtain Dns domainlist from dhcpv6 reply
 *  \details      -
 *  \param[in]    DataPtr              Data buffer
 *  \param[in]    DataLen              Length of dhcpv6 message
 *  \param[in]    DomainListOptPtr     Domain list is stored here
 *  \return       E_OK                 Domain list processed successfully
 *  \return       E_NOT_OK             Domain list not obtained
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptDomainList(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       DataPtr,
  uint16                                                           DataLen,
  P2VAR(TcpIp_DhcpV6_OptDomainListType, AUTOMATIC, TCPIP_APPL_VAR) DomainListOptPtr);
#endif

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxAdvertise()
 *********************************************************************************************************************/
/*! \brief        Process dhcpv6 Rx advertise message
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DataPtr          Data buffer
 *  \param[in]    DataLen          Length of dhcpv6 message
 *  \return       E_OK             Rx advertise message processed successfully
 *  \return       E_NOT_OK         Rx advertise message not valid
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VRxAdvertise(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen);


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCalcRetransTimeout()
 *********************************************************************************************************************/
/*! \brief        Calculate and update retransmission time for dhcpv6 message
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    IsSolicit        Solicit Flag
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VCalcRetransTimeout(
  TcpIp_IpV6CtrlIterType   IpCtrlIdx,
  boolean                  IsSolicit);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VProcessValidateRxReplyOptions()
 *********************************************************************************************************************/
/*! \brief        Process the options in dhcpv6 reply messages
 *  \details      -
 *  \param[in]    IpCtrlIdx         Index of IP controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   OptStatusCodePtr  Status code of option is stored here
 *  \param[out]   OptDnsServersPtr  DNS server option is stored here
 *  \param[out]   OptDomainListPtr  Domain name option is stored here
 *  \param[in]    DataPtr           Dhcpv6 data buffer
 *  \param[in]    DataLen           Length of dhcpv6 message
 *  \return       E_OK              Reply message options processed successfully
 *  \return       E_NOT_OK          Reply message options has invalid client/server id/ error code
 *  \pre          DhcpV6 must be configured for the controller index.
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VProcessValidateRxReplyOptions(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  IPV6_P2V(TcpIp_DhcpV6_OptStatusCodeType)   OptStatusCodePtr,
#if (TCPIP_SUPPORT_DNS == STD_ON)
  IPV6_P2V(TcpIp_DhcpV6_OptDnsServersType)   OptDnsServersPtr,
  IPV6_P2V(TcpIp_DhcpV6_OptDomainListType)   OptDomainListPtr,
#endif
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VProcessRxReplyIanaOption()
 *********************************************************************************************************************/
/*! \brief        Process Iana options in dhcpv6 reply messages
 *  \details      -
 *  \param[in]    IpCtrlIdx         Index of IP controller
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VProcessRxReplyIanaOption(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx
);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCalcElapsedTime()
 *********************************************************************************************************************/
/*! \brief        This API calculates elapsed time since start of DHCPv6 address assignment.
 *  \details      -
 *  \param[in]    DhcpV6DataIdx    Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VCalcElapsedTime(
    TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTxPendingMessages()
 *********************************************************************************************************************/
/*! \brief        This API transmits pending DHCPv6 message.
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DhcpV6DataIdx    Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VTxPendingMessages(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateRenewMessage()
 *********************************************************************************************************************/
/*! \brief        This API sends RENEW message or switch to REBIND if number of retransmissions has been reached
 *                for Renew State
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DhcpV6DataIdx    Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateRenewMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateSolicitMessage()
 *********************************************************************************************************************/
/*! \brief        This API moves to state REQUEST if valid ADVERTISE message has been received from DHCPv6 server.
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DhcpV6DataIdx    Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateSolicitMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateReqDecRebMessage()
 *********************************************************************************************************************/
/*! \brief        This API (Re-)Transmit message or restart DHCPv6 address assignment if number of retransmissions
 *                has been reached for Request Decline or Rebind message
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DhcpV6DataIdx    Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateReqDecRebMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateReleaseMessage()
 *********************************************************************************************************************/
/*! \brief        This API (re-)transmit Release message if number of retransmissions has been reached
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DhcpV6DataIdx    Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateReleaseMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxHandleStateMsgAdv()
 *********************************************************************************************************************/
/*! \brief        This API handles Rx of DHCPv6 advertise messages
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DhcpV6DataIdx    Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \param[in]    DataPtr          Dhcpv6 data buffer
 *  \param[in]    DataLen          Length of dhcpv6 message
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRxHandleStateMsgAdv(
  TcpIp_IpV6CtrlIterType                      IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType                  DhcpV6DataIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)  DataPtr,
  uint16                                      DataLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxProcessMessage()
 *********************************************************************************************************************/
/*! \brief      This API handles Rx of DHCPv6 messages
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    MsgType          Dhcpv6 message type
 *  \param[in]    DhcpV6DataIdx    Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \param[in]    DataPtr          Dhcpv6 data buffer
 *  \param[in]    DataLen          Length of dhcpv6 message
 *  \pre          DhcpV6 must be configured for the controller index.
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRxProcessMessage(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  uint8                                      MsgType,
  TcpIp_SizeOfDhcpV6DataType                 DhcpV6DataIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VUpdateRxReplyDhcpState()
 *********************************************************************************************************************/
/*! \brief        Handle the dhcpv6 reply message based on the dhcpv6 state
 *  \details      -
 *  \param[in]    IpCtrlIdx          Index of IP controller
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   OptStatusCodePtr   Status code of the option is stored here
 *  \param[in]    OptDnsServersPtr   DNS server list option content
 *  \param[in]    OptDomainListPtr   DNS domain list option content
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VUpdateRxReplyDhcpState(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
#if (TCPIP_SUPPORT_DNS == STD_ON)
  IPV6_P2C(TcpIp_DhcpV6_OptDnsServersType)   OptDnsServersPtr,
  IPV6_P2C(TcpIp_DhcpV6_OptDomainListType)   OptDomainListPtr,
#endif
  IPV6_P2C(TcpIp_DhcpV6_OptStatusCodeType)   OptStatusCodePtr
  );

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VProcessRxReplyStatusCode()
 *********************************************************************************************************************/
/*! \brief        Process the status codes in dhcpv6 reply messages
 *  \details      -
 *  \param[in]    IpCtrlIdx          Index of IP controller
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VProcessRxReplyStatusCode(
  TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildIa()
 *********************************************************************************************************************/
/*! \brief        Build Iana option
 *  \details      -
 *  \param[in]    IpCtrlIdx          Index of IP controller
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr             Message buffer
 *  \return       E_OK               Iana option built successfully
 *  \return       E_NOT_OK           Iana option not built
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildIa(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildIaAddr()
 *********************************************************************************************************************/
/*! \brief        Build Ia address option
 *  \details      -
 *  \param[in]    IpCtrlIdx          Index of IP controller
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr             Message buffer
 *  \return       E_OK               Iana option built successfully
 *  \return       E_NOT_OK           Iana option not built
 *  \pre          DhcpV6 must be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildIaAddr(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/* PRQA S 3453 FctLikeMacros */ /* MD_MSR_FctLikeMacro */

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
# if (defined(TCPIP_PROCESSOR_CANOEEMU) && (TCPIP_DHCPV6_VENABLE_CANOE_WRITE_STRING == STD_ON))
#  include "stdio.h"

#  define CANOE_DBG_MODULE_NAME "DHCPv6"

#  define CANOE_WRITE_STRING0(Txt) \
  CANoeAPI_WriteString("[" CANOE_DBG_MODULE_NAME "] " Txt);

#  define CANOE_WRITE_STRINGF(Txt, ...) \
  _snprintf((char*)VCanoeWriteStrBuffer, sizeof(VCanoeWriteStrBuffer), \
  "[" CANOE_DBG_MODULE_NAME "] " Txt, __VA_ARGS__); \
  CANoeAPI_WriteString((const sint8 *)(VCanoeWriteStrBuffer));

#  define CANOE_WRITE_STRING1(txt, p1)                     CANOE_WRITE_STRINGF(txt, p1)
#  define CANOE_WRITE_STRING2(txt, p1, p2)                 CANOE_WRITE_STRINGF(txt, p1, p2)
#  define CANOE_WRITE_STRING3(txt, p1, p2, p3)             CANOE_WRITE_STRINGF(txt, p1, p2, p3)
#  define CANOE_WRITE_STRING4(txt, p1, p2, p3, p4)         CANOE_WRITE_STRINGF(txt, p1, p2, p3, p4)
#  define CANOE_WRITE_STRING5(txt, p1, p2, p3, p4, p5)     CANOE_WRITE_STRINGF(txt, p1, p2, p3, p4, p5)
#  define CANOE_WRITE_STRING6(txt, p1, p2, p3, p4, p5, p6) CANOE_WRITE_STRINGF(txt, p1, p2, p3, p4, p5, p6)
# else
#  define CANOE_WRITE_STRING0(txt)
#  define CANOE_WRITE_STRING1(txt, p1)
#  define CANOE_WRITE_STRING2(txt, p1, p2)
#  define CANOE_WRITE_STRING3(txt, p1, p2, p3)
#  define CANOE_WRITE_STRING4(txt, p1, p2, p3, p4)
#  define CANOE_WRITE_STRING5(txt, p1, p2, p3, p4, p5)
#  define CANOE_WRITE_STRING6(txt, p1, p2, p3, p4, p5, p6)
# endif /* (defined(TCPIP_PROCESSOR_CANOEEMU) && (TCPIP_DHCPV6_VENABLE_CANOE_WRITE_STRING == STD_ON)) */
#endif

#define TCPIP_DHCPV6_GET_MSG_TYPE(MsgPtr) ((MsgPtr)->BufPtr[0])

/* PRQA S 0342 1 */ /* MD_MSR_Rule20.10_0342 */
#define TCPIP_DHCPV6_CHANGE_STATE(DhcpV6DataIdx, NEW_STATE) TcpIp_DhcpV6_VChangeState((DhcpV6DataIdx), TCPIP_DHCPV6_STATE_##NEW_STATE)

/* PRQA S 0342, 0881 4 */ /* MD_MSR_Rule20.10_0342, MD_DHCPV6_Rule20.11_0881 */
#define TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpV6CtrlIdx, MSG) (TcpIp_DhcpV6_VSetRetransParams(IpV6CtrlIdx, \
                                              TCPIP_DHCPV6_##MSG##_TIMEOUT, TCPIP_DHCPV6_##MSG##_MAX_RT, \
                                              TCPIP_DHCPV6_##MSG##_MAX_RC, TCPIP_DHCPV6_##MSG##_MAX_RD))


#define TCPIP_DHCPV6_GENERATE_TRANS_ID(VAR)   ((VAR) = ((((VAR) + (uint32)(TcpIp_GetRandomNumber()) + 1u) & 0x00FFFFFFu) \
                                                        + ((uint32)IpCtrlIdx << 16)))

#define TCPIP_DHCPV6_RAND_FACTOR(BASE_VALUE)  (((BASE_VALUE) / 10u) - (2u * TCPIP_MAIN_FCT_PERIOD_MSEC))


/* PRQA L:FctLikeMacros */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCompareBytes()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV6_VCompareBytes(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) Data1Ptr,
  uint16                                     Data1Len,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) Data2Ptr,
  uint16                                     Data2Len)
{
  uint16 IdIdx;
  boolean result = TRUE;

  if (Data1Len != Data2Len)
  {
    result = FALSE;
  }
  else
  {
    IdIdx = Data1Len;
    /* #10 Compare the two buffers */
    while (0u < IdIdx)
    {
      IdIdx--;

      if (Data1Ptr[IdIdx] != Data2Ptr[IdIdx])
      {
        result = FALSE;
        break;
      }
    }
  }

  return result;
} /* End of TcpIp_DhcpV6_VCompareBytes() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VInitClientId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VInitClientId(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx     = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_SizeOfDhcpV6ConfigType dhcpV6ConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx != TCPIP_NO_DHCPV6DATAIDXOFIPV6CTRL); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->TypeNbo   = TCPIP_HTONS(0x01U);
  TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->HwTypeNbo = TCPIP_HTONS(0x01U);
  TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->TimeNbo   =
                       TCPIP_HTONL((uint32)TcpIp_GetDuidTimeOfDhcpV6Config(dhcpV6ConfigIdx));
  /* #10 Get physical address for client DUID */

  IpV6_GetPhysAddr(IpCtrlIdx, &(TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->PhysAddr[0]));

} /* End of TcpIp_DhcpV6_VInitClientId() */


#if (TCPIP_DHCPV6_USE_RAND_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VGetRandomValue()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(uint32, TCPIP_CODE) TcpIp_DhcpV6_VGetRandomValue(
  uint32 MinValue,
  uint32 MaxValue)
{
  uint32 ValueRange;
  uint32 RndValue;

  /* #10 Generate random value */
  if (MinValue < MaxValue)
  {
    ValueRange = (MaxValue - MinValue) + 1u;

    if (ValueRange <= 0xFFFFU)
    {
      /* 16bit random number [0..0xFFFF] is sufficient */
      RndValue = (uint32)(TcpIp_GetRandomNumber());
    }
    else
    {
      /* create 32bit random number [0..0xFFFFFFFF] by combining two 16bit random numbers */
      RndValue = (uint32)(((uint32)(TcpIp_GetRandomNumber()) << 16) | (uint32)(TcpIp_GetRandomNumber()));
    }

    RndValue %= ValueRange;
  }
  else
  {
    RndValue = 0;
  }

  return MinValue + RndValue;

} /* End of TcpIp_DhcpV6_VGetRandomValue() */
#endif


/* TIMESTAMP FUNCTIONS */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTimeCompare()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(boolean, IPV6_CODE) TcpIp_DhcpV6_VTimeCompare(
  TcpIp_DhcpV6_TimeType  RefTimestamp,
  TcpIp_DhcpV6_TimeType  Timestamp)
{
  boolean result = FALSE;
  /* #10 Compare two timestamps */
  if((RefTimestamp.S < Timestamp.S) || ((RefTimestamp.S == Timestamp.S) && (RefTimestamp.Ms < Timestamp.Ms)))
  {
    result = TRUE;
  }
  return result;
} /* End of TcpIp_DhcpV6_VTimeCompare() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTimeSet()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) TcpIp_DhcpV6_VTimeSet(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA)  TimestampPtr,
  uint32                                                    Seconds,
  uint32                                                    Milliseconds)
{
  /* #10 Set Time */
  TimestampPtr->S = Seconds;
  TimestampPtr->Ms = Milliseconds;
} /* End of TcpIp_DhcpV6_VTimeSet() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTimeAddMs()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VTimeAddMs(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA) TimestampPtr,
  uint32                                                   Milliseconds)
{
  TimestampPtr->Ms += Milliseconds;

  /* #10 Add miliseconds to a Timestamp */
  if (TimestampPtr->Ms >= 1000u)
  {
    TimestampPtr->S += (TimestampPtr->Ms / 1000u);
    TimestampPtr->Ms = (TimestampPtr->Ms % 1000u);
  }
} /* End of TcpIp_DhcpV6_VTimeAddMs() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetEventTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) TcpIp_DhcpV6_VSetEventTime(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA)  TimestampPtr,
  uint32                                                    Milliseconds)
{
  /* #10 Obtain absolute Event time by adding the relative event time (in ms) to a timestamp */
  *TimestampPtr = TcpIp_DhcpV6_Time;
  TcpIp_DhcpV6_VTimeAddMs(TimestampPtr, Milliseconds);
} /* End of TcpIp_DhcpV6_VSetEventTime() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetLifetimeS()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VSetLifetimeS(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_VAR) TimestampPtr,
  uint32                                                  LifetimeS,
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_VAR) NextEventTimePtr)
{
  /* #10 Obtain the absolute lifetime by adding lifetime (in seconds) to the current timestamp */
  if (TCPIP_DHCPV6_LIFETIME_UNLIMITED > LifetimeS)
  {
    TimestampPtr->S  = TcpIp_DhcpV6_Time.S + LifetimeS;
    TimestampPtr->Ms = TcpIp_DhcpV6_Time.Ms;
  }
  else
  {
    TimestampPtr->S  = TCPIP_DHCPV6_LIFETIME_UNLIMITED;
    TimestampPtr->Ms = 0;
  }

  if ((NULL_PTR != NextEventTimePtr) && (TCPIP_DHCPV6_TIME_IS_LOWER(*TimestampPtr, *NextEventTimePtr) == TRUE)) /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    *NextEventTimePtr = *TimestampPtr;
  }

} /* End of TcpIp_DhcpV6_VSetLifetimeS() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VChangeState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VChangeState(TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx, uint8 NewState)
{
  IPV6_BEGIN_CRITICAL_SECTION();

  /* #10 Change Dhcp state */
  TcpIp_SetLastStateOfDhcpV6Data(DhcpV6DataIdx, TcpIp_GetStateOfDhcpV6Data(DhcpV6DataIdx));
  TcpIp_SetStateOfDhcpV6Data(DhcpV6DataIdx, NewState);

  IPV6_END_CRITICAL_SECTION();

} /* End of TcpIp_DhcpV6_VChangeState() */

/* MISC FUNCTIONS */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VWriteOptionCode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VWriteOptionCode(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) DataPtr,
  uint16                                  OptCode)
{
  /* #10 Write option code into buffer */
  DataPtr[0] = (uint8)(OptCode >> 8);
  DataPtr[1] = (uint8)(OptCode);
}


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetRetransParams()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VWriteOptionLen(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) DataPtr,
  uint16                                  OptLen)
{
  /* #10 Write option length to buffer */
  DataPtr[2] = (uint8)(OptLen >> 8);
  DataPtr[3] = (uint8)(OptLen);
}


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetRetransParams()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC INLINE FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV6_VReadOptionCode(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr)
{
  /* #10 read option code from buffer */
  return (uint16)((uint16)DataPtr[0] << 8) | (DataPtr[1]);
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetRetransParams()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VSetRetransParams(
  TcpIp_IpV6CtrlIterType IpCtrlIdx,
  uint32                 IRT,
  uint32                 MRT,
  uint8                  MRC,
  uint32                 MRD
)
{
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Set retransmission parameters for the controller */
  TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->TxCount = 0;
  TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->InitRetransTimeout = IRT;
  TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->MaxRetransTime = MRT;
  TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->MaxRetransCount = MRC;

  if (MRD > 0u)
  {
    TCPIP_DHCPV6_SET_EVENT_TIME_MS(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->AbsRetransTimeout, MRD);
  }
  else
  {
    TCPIP_DHCPV6_SET_LIFETIME_S(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->AbsRetransTimeout,
                                TCPIP_DHCPV6_LIFETIME_UNLIMITED, (TcpIp_DhcpV6_TimeType*)NULL_PTR);
  }

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING4("Retrans Params: IRT: %dmsec, MRT: %dmsec, MRC: %d, MRD: %dmsec", IRT, MRT, MRC, MRD);
#endif
} /* End of TcpIp_DhcpV6_VSetRetransParams() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCalcRetransTimeout()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VCalcRetransTimeout(
  TcpIp_IpV6CtrlIterType   IpCtrlIdx,
  boolean                  IsSolicit)
{
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_SizeOfDhcpV6ConfigType dhcpV6ConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);
  uint32 RndOffset = 0;

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Check if retransmitting for the first time */
  if (TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->TxCount == 0u)
  {
    /* #20 Calculate first retransmission based on Initial Retransmission Timeout (IRT) */
    TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout =
                         TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->InitRetransTimeout;

    if (TcpIp_IsRandomizeTimeoutsOfDhcpV6Config(dhcpV6ConfigIdx) == TRUE)
    {
      RndOffset = TCPIP_DHCPV6_RAND_FACTOR(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->InitRetransTimeout);

      if (TRUE == IsSolicit)
      {
        TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout += TcpIp_DhcpV6_VGetRandomValue(0, RndOffset);
      }
      else
      {
        uint32 RndValue = TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout;

        RndValue += TcpIp_DhcpV6_VGetRandomValue(0u, RndOffset);
        TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout = RndValue;
      }
    }
  }
  else
  {
    /* #30 Calculate next retransmission based on previous retransmission timeout */

    if (TcpIp_IsRandomizeTimeoutsOfDhcpV6Config(dhcpV6ConfigIdx) == TRUE)
    {
      RndOffset = TCPIP_DHCPV6_RAND_FACTOR(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout);
    }

    TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout <<= TCPIP_DHCPV6_LSHIFT_MUL_2;

    if (TcpIp_IsRandomizeTimeoutsOfDhcpV6Config(dhcpV6ConfigIdx) == TRUE)
    {
      uint32 RndValue = TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout;

      RndValue += TcpIp_DhcpV6_VGetRandomValue(0u, RndOffset);

      TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout = RndValue;
    }
  }
}
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCalcTimeout()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VCalcTimeout(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_VAR) TimePtr,
  boolean                                                 IsSolicit)
{
  uint32 RndOffset = 0;
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_SizeOfDhcpV6ConfigType dhcpV6ConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);
  Std_ReturnType result = E_OK;

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  if (TCPIP_DHCPV6_TIME_EXPIRED(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->AbsRetransTimeout) == TRUE)
  {
    result = E_NOT_OK;
  }

  /* RT = [-(IRT/10)...(IRT/10)] */

  /* #10 Check if maximum number of retransmission reached */
  else if (   ((TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->MaxRetransCount) > 0u)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
           && (TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->TxCount > TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->MaxRetransCount))
  {

    result = E_NOT_OK;
  }
  else
  {
    /* #20 Calculate retransmission timeout */
    TcpIp_DhcpV6_VCalcRetransTimeout(IpCtrlIdx, IsSolicit);

    if (   (TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->MaxRetransTime > 0u)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout > TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->MaxRetransTime))
    {
      /* limit Maximum Retransmission Time */

      if (TcpIp_IsRandomizeTimeoutsOfDhcpV6Config(dhcpV6ConfigIdx) == TRUE)
      {
        RndOffset = TCPIP_DHCPV6_RAND_FACTOR(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->MaxRetransTime);
      }

      TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout =
          TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->MaxRetransTime;

      if (TcpIp_IsRandomizeTimeoutsOfDhcpV6Config(dhcpV6ConfigIdx) == TRUE)
      {
        uint32 RndValue = TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout;

        RndValue += TcpIp_DhcpV6_VGetRandomValue(0u, RndOffset);

        TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout = RndValue;
      }
    }

    *TimePtr = TcpIp_DhcpV6_Time;
    TcpIp_DhcpV6_VTimeAddMs(TimePtr, TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout);

    if (TCPIP_DHCPV6_TIME_IS_LOWER(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->AbsRetransTimeout, *TimePtr) == TRUE)
    {
      /* maximum retransmission duration reached */
      *TimePtr = TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->AbsRetransTimeout;
    }

    TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->TxCount += 1u;

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
    {
      uint32 AbsTimeout = 0;
      if (TCPIP_DHCPV6_LIFETIME_UNLIMITED > TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->AbsRetransTimeout.S)
      {

        AbsTimeout = TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->AbsRetransTimeout.S - TcpIp_DhcpV6_Time.S;
      }

      CANOE_WRITE_STRING5("Calculated retransmission timeout: %d/%d ms, transmission: %d/%d, abs timeout: %d",
        TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->Timeout,
        TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->MaxRetransTime,
        TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->TxCount,
        TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->MaxRetransCount, AbsTimeout);
    }
#endif
  }
  return result;
} /* End of TcpIp_DhcpV6_VCalcTimeout() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/* MESSAGE BUILDING FUNCTIONS */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VOptStackPushDataPos()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VOptStackPushDataPos(
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;
#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Push current option onto stack if stack is not full */
  if (MsgPtr->OptStackPos < TCPIP_DHCPV6_OPT_STACK_SIZE)
  {
    MsgPtr->OptStartPos[MsgPtr->OptStackPos] = MsgPtr->MsgBufPos;
    MsgPtr->OptStackPos++;
    Result = E_OK;
  }
  else
  {
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
    CANOE_WRITE_STRING0("TcpIp_DhcpV6_VOptStackPushDataPos() Option Stack overflow!");
#endif
    Result = E_NOT_OK;
  }

  return Result;
} /* End of TcpIp_DhcpV6_VOptStackPushDataPos() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VOptStackPopDataPos()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VOptStackPopDataPos(
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_VAR)               DataPosPtr)
{
  Std_ReturnType Result;

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Pop current option from stack if stack is not empty */
  if (0u < MsgPtr->OptStackPos)
  {
    MsgPtr->OptStackPos--;
    *DataPosPtr = MsgPtr->OptStartPos[MsgPtr->OptStackPos];
    Result = E_OK;
  }
  else
  {
    Result = E_NOT_OK;
  }

  return Result;
} /* End of TcpIp_DhcpV6_VOptStackPopDataPos() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VGetEventType()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(TcpIp_DhcpEventType, TCPIP_CODE) TcpIp_DhcpV6_VGetEventType(
  uint8  MsgType)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_DhcpEventType dhcpEvent;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Determine which event shall be notified for the message */
  switch (MsgType)
  {
  case TCPIP_DHCPV6_MSG_SOL:
    dhcpEvent = TCPIP_DHCP_EVENT_TX_DISCOVER_SOLICIT;
    break;
  case TCPIP_DHCPV6_MSG_ADV:
    dhcpEvent = TCPIP_DHCP_EVENT_RX_OFFER_ADVERTISE;
    break;
  case TCPIP_DHCPV6_MSG_REQ:
    dhcpEvent = TCPIP_DHCP_EVENT_TX_REQUEST;
    break;
  case TCPIP_DHCPV6_MSG_REP:
    dhcpEvent = TCPIP_DHCP_EVENT_RX_ACK_REPLY;
    break;
  case TCPIP_DHCPV6_MSG_CNF:
    dhcpEvent = TCPIP_DHCP_EVENT_TX_V6_CONFIRM;
    break;
  case TCPIP_DHCPV6_MSG_REN:
    dhcpEvent = TCPIP_DHCP_EVENT_TX_V6_RENEW;
    break;
  case TCPIP_DHCPV6_MSG_REB:
    dhcpEvent = TCPIP_DHCP_EVENT_TX_V6_REBIND;
    break;
  case TCPIP_DHCPV6_MSG_REL:
    dhcpEvent = TCPIP_DHCP_EVENT_TX_V6_RELEASE;
    break;
  case TCPIP_DHCPV6_MSG_DEC:
    dhcpEvent = TCPIP_DHCP_EVENT_TX_V6_DECLINE;
    break;
  default:
    dhcpEvent = TCPIP_DHCP_EVENT_INVALID;
    break;
  }

  return dhcpEvent;
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBeginMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBeginMessage(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  uint8                                                  MsgType)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketOwnerConfigIterType      socketOwnerCfgIdx;
  TcpIp_SizeOfDhcpV6DataType           dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_CurrentTransIdOfDhcpV6DataType currTransId   = TcpIp_GetCurrentTransIdOfDhcpV6Data(dhcpV6DataIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr->MsgBufPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(TCPIP_DHCPV6_MSG_HDR_LEN <= MsgPtr->MsgBufLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
#endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Traverse through the socket owners and invoke Dhcp event callout if present */
  for (socketOwnerCfgIdx = 0; socketOwnerCfgIdx < TcpIp_GetSizeOfSocketOwnerConfig(); socketOwnerCfgIdx++)
  {
    if (TcpIp_GetDhcpEventFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx) != NULL_PTR)
    {
      TcpIp_LocalAddrIdType localAddrId = TCPIP_LOCAL_ADDR_IDX_TO_ID(TCPIP_IPV6_TO_LOCAL_ADDR_IDX(TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(IpCtrlIdx))));
      TcpIp_DhcpEventType dhcpEvent = TcpIp_DhcpV6_VGetEventType(MsgType);

      if (dhcpEvent != TCPIP_DHCP_EVENT_INVALID)
      {
        TcpIp_GetDhcpEventFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx)(localAddrId, dhcpEvent);
      }
    }
  }

  MsgPtr->TxPending = FALSE;

  /* #20 Write message type code */
  MsgPtr->MsgBufPtr[0] = MsgType;

  MsgPtr->OptStackPos = 0;

  /* #30 Generate and write 24bit transaction id */
  TCPIP_DHCPV6_GENERATE_TRANS_ID(currTransId);
  MsgPtr->MsgBufPtr[1] = (uint8)(currTransId >> 16);
  MsgPtr->MsgBufPtr[2] = (uint8)(currTransId >> 8);
  MsgPtr->MsgBufPtr[3] = (uint8)(currTransId);

  TcpIp_SetCurrentTransIdOfDhcpV6Data(dhcpV6DataIdx, currTransId);

  TcpIp_SetElapsedTimeMsOfDhcpV6Data(dhcpV6DataIdx, 0);

  MsgPtr->MsgBufPos = 4;

  /* #40 Add client identifier option into the dhcpv6 message */
  (void)TcpIp_DhcpV6_VAddOptClientIdent(IpCtrlIdx, MsgPtr); /* ignore return value, option should always fit into dhcp message */

  return E_OK;
} /* End of TcpIp_DhcpV6_VBeginMessage() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VEndMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV6_VEndMessage(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_DATA) MsgPtr)
{
  /* #10 Add user options to the end of the message */
#if (TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON)
  (void)TcpIp_DhcpV6_VAddUserOptions(IpCtrlIdx, MsgPtr);
#endif

  return MsgPtr->MsgBufPos;
} /* End of TcpIp_DhcpV6_VEndMessage() */


/* OPTION ENCODING FUNCTIONS */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddRawOpt()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddRawOpt(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  uint16                                                 OptType,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)             OptDataPtr,
  uint16                                                 OptDataLen)
{
  TcpIp_SizeOfDhcpV6TxOption39InfoType dhcpV6TxOpt39InfoIdx = TcpIp_GetDhcpV6TxOption39InfoIdxOfIpV6Ctrl(IpCtrlIdx);

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != OptDataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0u < OptDataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
#endif
  /* #10 Add option code and length into the message buffer at the correct offset */
  TcpIp_DhcpV6_VWriteOptionCode(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], OptType);
  if (OptType == TCPIP_DHCPV6_OPT_ID_CLIENT_FQDN)
  {
    TcpIp_DhcpV6_VWriteOptionLen(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], (OptDataLen + TCPIP_FQDN_OPT_FLAGS_DNLEN));
  }
  else
  {
    TcpIp_DhcpV6_VWriteOptionLen(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], OptDataLen);
  }

  MsgPtr->MsgBufPos += TCPIP_DHCPV6_OPT_HDR_LEN;

  if (OptType == TCPIP_DHCPV6_OPT_ID_CLIENT_FQDN)
  {
    /* IPv6
        0 1 2 3 4 5 6 7
       +-+-+-+-+-+-+-+-+
       |  MBZ    |N|O|S|
       +-+-+-+-+-+-+-+-+
       S = 0   the server SHOULD NOT perform the A RR (FQDN-to-address) DNS updates
       O = 0   must be 0
       N = 1   the server SHOULD NOT perform any DNS updates
    */
    MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos] = 0x04;  /* set flag N */
    MsgPtr->MsgBufPos++;
    /* Domain name length must be less than 255 bytes. */
    MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos] = (uint8)(TcpIp_GetOptLenOfDhcpV6TxOption39Info(dhcpV6TxOpt39InfoIdx) & 0xFFu);
    MsgPtr->MsgBufPos++;
  }

  /* #20 Copy the option data into the message buffer */
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  VStdMemCpy(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], OptDataPtr, OptDataLen);

  MsgPtr->MsgBufPos += OptDataLen;

  return E_OK;
} /* End of TcpIp_DhcpV6_VAddRawOpt() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptClientIdent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptClientIdent(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  uint8 ClientDuidOfDhcpV6Data[sizeof(TcpIp_DhcpV6_DuIdType1)];

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Add client identifier option */
  TCPIP_PUT_UINT16_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_TYPENBO,   TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->TypeNbo);
  TCPIP_PUT_UINT16_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_HWTYPENBO, TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->HwTypeNbo);
  TCPIP_PUT_UINT32_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_TIMENBO,   TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->TimeNbo);
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_LL_ADDR_COPY(&ClientDuidOfDhcpV6Data[TCPIP_DHCPV6_DUID1_OPT_OFF_PHYSADDR], &(TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->PhysAddr[0]));

  return TcpIp_DhcpV6_VAddRawOpt(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_OPT_CLIENTID, ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_CLIENT_DUID_LEN);
} /* End of TcpIp_DhcpV6_VAddOptClientIdent() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptServerIdent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptServerIdent(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Add server identifier option */
  return TcpIp_DhcpV6_VAddRawOpt(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_OPT_SERVERID,
    (P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA))&(TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->ServerId[0]),
    TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->ServerIdLen);
} /* End of TcpIp_DhcpV6_VAddOptServerIdent() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBeginOptIaNa()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBeginOptIaNa(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  uint32                                                 IaId,
  uint32                                                 T1,
  uint32                                                 T2)
{
  Std_ReturnType result = E_OK;
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptIaNaHdrPtr;

  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  if (E_OK != TcpIp_DhcpV6_VOptStackPushDataPos(MsgPtr))
  {
    result = E_NOT_OK;
  }
  else
  {
    /* #10 Update option code and Iana header params */
    TcpIp_DhcpV6_VWriteOptionCode(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], TCPIP_DHCPV6_OPT_IA_NA);

    /* option length currently unknown, since it depends on the options contained in this option */
    MsgPtr->MsgBufPos += TCPIP_DHCPV6_OPT_HDR_LEN;

    OptIaNaHdrPtr = &MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos];

    TCPIP_PUT_UINT32(OptIaNaHdrPtr, TCPIP_DHCPV6_IANA_OPT_OFF_IAIDNBO, TCPIP_HTONL(IaId));
    TCPIP_PUT_UINT32(OptIaNaHdrPtr, TCPIP_DHCPV6_IANA_OPT_OFF_T1NBO, TCPIP_HTONL(T1));
    TCPIP_PUT_UINT32(OptIaNaHdrPtr, TCPIP_DHCPV6_IANA_OPT_OFF_T2NBO, TCPIP_HTONL(T2));

    MsgPtr->MsgBufPos += (uint16) sizeof(TcpIp_DhcpV6_OptIaNaHdrRawType);
  }

  return result;
} /* End of TcpIp_DhcpV6_VBeginOptIaNa() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VEndOptIaNa()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VEndOptIaNa(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  uint16 TmpOptStartPos;
  Std_ReturnType result = E_OK;

  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif
  /* #10 Validate if the iana option has been successfully constructed */
  if (E_OK != TcpIp_DhcpV6_VOptStackPopDataPos(MsgPtr, &TmpOptStartPos))
  {
    result = E_NOT_OK;
  }
  else if (TCPIP_DHCPV6_OPT_IA_NA != TcpIp_DhcpV6_VReadOptionCode(&MsgPtr->MsgBufPtr[TmpOptStartPos]))
  {
    result = E_NOT_OK;
  }
  else
  {
    /* #20 Write the option length value into the Iana option header */
    TcpIp_DhcpV6_VWriteOptionLen(&MsgPtr->MsgBufPtr[TmpOptStartPos],
      (uint16)(MsgPtr->MsgBufPos - TmpOptStartPos - TCPIP_DHCPV6_OPT_HDR_LEN));
  }

  return result;
} /* End of TcpIp_DhcpV6_VEndOptIaNa() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBeginOptIaAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBeginOptIaAddr(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)  MsgPtr,
  P2CONST(IpBase_AddrIn6Type, AUTOMATIC, TCPIP_APPL_DATA) AddrPtr,
  uint32                                                  PreferredLifetime,
  uint32                                                  ValidLifetime)
{
  Std_ReturnType result = E_OK;
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptIaAddrHdrPtr;

  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != AddrPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* push current option onto stack */
  if (E_OK != TcpIp_DhcpV6_VOptStackPushDataPos(MsgPtr))
  {
    result = E_NOT_OK;
  }
  else
  {
    /* #10 Update option code and Iana header params */
    TcpIp_DhcpV6_VWriteOptionCode(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], TCPIP_DHCPV6_OPT_IAADDR);

    /* option length currently unknown, since it depends on the options contined in this option */
    MsgPtr->MsgBufPos += TCPIP_DHCPV6_OPT_HDR_LEN;
    OptIaAddrHdrPtr = &MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos];
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(OptIaAddrHdrPtr[TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_ADDR], *AddrPtr);
    TCPIP_PUT_UINT32(OptIaAddrHdrPtr, TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_PREFLIFENBO, TCPIP_HTONL(PreferredLifetime));
    TCPIP_PUT_UINT32(OptIaAddrHdrPtr, TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_VALDLIFENBO, TCPIP_HTONL(ValidLifetime));

    MsgPtr->MsgBufPos += (uint16) sizeof(TcpIp_DhcpV6_OptIaAddrHdrRawType);
  }
  return result;
} /* End of TcpIp_DhcpV6_VBeginOptIaAddr() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VEndOptIaAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VEndOptIaAddr(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  uint16 TmpOptStartPos;
  Std_ReturnType result = E_OK;
  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Validate if the ia address option has been successfully constructed */
  if (E_OK != TcpIp_DhcpV6_VOptStackPopDataPos(MsgPtr, &TmpOptStartPos))
  {
    result = E_NOT_OK;
  }
  else if (TcpIp_DhcpV6_VReadOptionCode(&MsgPtr->MsgBufPtr[TmpOptStartPos]) != TCPIP_DHCPV6_OPT_IAADDR)
  {
    result = E_NOT_OK;
  }
  else
  {
    /* #20 Write the option length value into the Ia address option header */
    TcpIp_DhcpV6_VWriteOptionLen(&MsgPtr->MsgBufPtr[TmpOptStartPos],
      (uint16)(MsgPtr->MsgBufPos - TmpOptStartPos - TCPIP_DHCPV6_OPT_HDR_LEN));
  }
  return result;
} /* End of TcpIp_DhcpV6_VEndOptIaAddr() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptReqOpt()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptReqOpt(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  P2CONST(uint16, AUTOMATIC, TCPIP_APPL_DATA)            OptCodeArray,
  uint8                                                  OptCodeCount)
{
  uint8 OptCodeIdx;
  TcpIp_DhcpUserOptionIterType dhcpUserOptionIdx;
  TcpIp_SizeOfDhcpV6ConfigType dhcpV6ConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(((0u == OptCodeCount) || (NULL_PTR != OptCodeArray)), TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Write option code and length into message buffer */
  TcpIp_DhcpV6_VWriteOptionCode(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], TCPIP_DHCPV6_OPT_ORO);

  /* #20 Write the option length as sum of static option count and configured option count */
  TcpIp_DhcpV6_VWriteOptionLen(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], (((uint16) OptCodeCount + (uint16) TcpIp_GetRxReqOptionCntOfDhcpV6Config(dhcpV6ConfigIdx)) << TCPIP_DHCPV6_LSHIFT_MUL_2));

  MsgPtr->MsgBufPos += TCPIP_DHCPV6_OPT_HDR_LEN;

  /* #30 Add the options list into the message buffer */
  for (OptCodeIdx = 0; OptCodeIdx < OptCodeCount; OptCodeIdx++)
  {
    MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos]   = (uint8)(OptCodeArray[OptCodeIdx] >> 8);
    MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos + 1u] = (uint8)(OptCodeArray[OptCodeIdx]);
    MsgPtr->MsgBufPos += 2u;
  }

  /* #40 Traverse the list for Rx requested options and append options to the ORO option */
  for (dhcpUserOptionIdx = TcpIp_GetDhcpUserOptionStartIdxOfIpV6Ctrl(IpCtrlIdx); dhcpUserOptionIdx < TcpIp_GetDhcpUserOptionEndIdxOfIpV6Ctrl(IpCtrlIdx); dhcpUserOptionIdx++)
  {
    if (TcpIp_GetDirectionOfDhcpUserOption(dhcpUserOptionIdx) == TCPIP_DHCP_USER_OPTION_RX_REQUESTED)
    {
      TCPIP_PUT_UINT16(MsgPtr->MsgBufPtr, MsgPtr->MsgBufPos, TcpIp_GetCodeOfDhcpUserOption(dhcpUserOptionIdx));
      MsgPtr->MsgBufPos += 2u;
    }
  }


  return E_OK;
} /* End of TcpIp_DhcpV6_VAddOptReqOpt() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptElapsedTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VAddOptElapsedTime(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)  MsgPtr)
{
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  uint32 ElapsedTime;

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Insert the Elapsed Time option into the message */
  TcpIp_DhcpV6_VWriteOptionCode(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], TCPIP_DHCPV6_OPT_ELAPSED_TIME);
  TcpIp_DhcpV6_VWriteOptionLen( &MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], TCPIP_DHCPV6_OPT_ELAPSED_TIME_LEN);

  MsgPtr->MsgBufPos += TCPIP_DHCPV6_OPT_HDR_LEN;

  ElapsedTime = (TcpIp_GetElapsedTimeMsOfDhcpV6Data(dhcpV6DataIdx) / 10u);

  if (ElapsedTime > 0x0000FFFFu)
  {
    ElapsedTime = 0xFFFF;
  }

  TCPIP_PUT_UINT16(MsgPtr->MsgBufPtr, (MsgPtr->MsgBufPos /* + TCPIP_DHCPV6_ELAPSEDTIME_OPT_OFF_ELAPSEDTIMENBO */), (uint16)ElapsedTime);
  MsgPtr->MsgBufPos += (uint16) sizeof(TcpIp_DhcpV6_OptElapsedTimeRawType);

} /* End of TcpIp_DhcpV6_VAddOptElapsedTime() */

#if (TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddUserOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddUserOptions(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  TcpIp_SizeOfDhcpV6TxOption39InfoType dhcpV6TxOpt39InfoIdx = TcpIp_GetDhcpV6TxOption39InfoIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_DhcpUserOptionIterType dhcpUserOptionIdx;

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Insert the FQDN option if configured */
  if (0u < TcpIp_GetOptLenOfDhcpV6TxOption39Info(dhcpV6TxOpt39InfoIdx))
  {
    TcpIp_SizeOfDhcpV6TxOption39Type txOpt39Idx;
    IPV6_BEGIN_CRITICAL_SECTION();

    txOpt39Idx = TcpIp_GetDhcpV6TxOption39StartIdxOfIpV6Ctrl(IpCtrlIdx);
    (void)TcpIp_DhcpV6_VAddRawOpt(IpCtrlIdx, MsgPtr,
      TCPIP_DHCPV6_OPT_ID_CLIENT_FQDN, TcpIp_GetAddrDhcpV6TxOption39(txOpt39Idx),
      TcpIp_GetOptLenOfDhcpV6TxOption39Info(dhcpV6TxOpt39InfoIdx));

    IPV6_END_CRITICAL_SECTION();
  }

  /* #20 Traverse through the configured user option list and add all non-empty options to the message buffer */
  for (dhcpUserOptionIdx = TcpIp_GetDhcpUserOptionStartIdxOfIpV6Ctrl(IpCtrlIdx); dhcpUserOptionIdx < TcpIp_GetDhcpUserOptionEndIdxOfIpV6Ctrl(IpCtrlIdx); dhcpUserOptionIdx++)
  {
    if(   (TcpIp_GetDirectionOfDhcpUserOption(dhcpUserOptionIdx) == TCPIP_DHCP_USER_OPTION_TX)   /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TcpIp_GetLengthOfDhcpUserOptionDyn(dhcpUserOptionIdx) > 0u))
    {
      TcpIp_DhcpUserOptionBufferIterType dhcpUserBufferIdx;
      IPV6_BEGIN_CRITICAL_SECTION();

      dhcpUserBufferIdx = TcpIp_GetDhcpUserOptionBufferStartIdxOfDhcpUserOption(dhcpUserOptionIdx);

      (void)TcpIp_DhcpV6_VAddRawOpt(IpCtrlIdx, MsgPtr,
        TcpIp_GetCodeOfDhcpUserOption(dhcpUserOptionIdx), TcpIp_GetAddrDhcpUserOptionBuffer(dhcpUserBufferIdx),
        TcpIp_GetLengthOfDhcpUserOptionDyn(dhcpUserOptionIdx));

      IPV6_END_CRITICAL_SECTION();
    }
  }


  return E_OK;
} /* End of TcpIp_DhcpV6_VAddUserOptions() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
#endif


/******************************
 * MESSAGE ENCODING FUNCTIONS *
 ******************************/

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildSolicit()
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
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildSolicit(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VTxSolicit()");
#endif
  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_SOL);

  /* #20 Add option request option [RFC3315 17.1.1. Creation of Solicit Messages] */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptReqOpt(IpCtrlIdx, MsgPtr, &TcpIp_DhcpV6_OptionRequestList[0],
      TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN);
  }
  /* #30 Add Iana option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBeginOptIaNa(IpCtrlIdx, MsgPtr,
      TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->IaId, 0u, 0u);
  }
  /* #40 End Iana option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VEndOptIaNa(IpCtrlIdx, MsgPtr);
  }
  /* #50 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildSolicit() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildInfoRequest()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildInfoRequest(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VBuildInfoRequest()");
#endif
  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_INF);

  /* #20 Add option request option [RFC3315 18.1.5. Creation and Transmission of Information-request Messages] */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptReqOpt(IpCtrlIdx, MsgPtr,
      &TcpIp_DhcpV6_OptionRequestList[TCPIP_DHCPV6_OPT_REQ_OPT_LIST_EXTRA_OPT_OFS],
      TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN - TCPIP_DHCPV6_OPT_REQ_OPT_LIST_EXTRA_OPT_OFS);
  }
  /* #30 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildInfoRequest() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRelease()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRelease(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VBuildRelease()");
#endif
  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_REL);

  /* #20 Add server identifier */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptServerIdent(IpCtrlIdx, MsgPtr);
  }

  /* #30 Add Ia address option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBuildIa(IpCtrlIdx, MsgPtr);
  }

  /* #40 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildRelease() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildIaAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildIaAddr(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Invoke IA Address option build begin and end functions */
  Result = TcpIp_DhcpV6_VBeginOptIaAddr(IpCtrlIdx, MsgPtr,
    &(TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->AddrLease.Addr), 0u, 0u);

  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VEndOptIaAddr(IpCtrlIdx, MsgPtr);
  }
  return Result;
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildIa()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildIa(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 insert IaNa option */
  Result = TcpIp_DhcpV6_VBeginOptIaNa(IpCtrlIdx, MsgPtr, TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->IaId, 0u, 0u);

  if (E_OK == Result)
  {
    /* #20 If previous step was successful, insert Ia address */
    Result = TcpIp_DhcpV6_VBuildIaAddr(IpCtrlIdx, MsgPtr);
  }

  if (E_OK == Result)
  {
    /* #30 If previous step was successful, insert IaNa end option */
    Result = TcpIp_DhcpV6_VEndOptIaNa(IpCtrlIdx, MsgPtr);
  }
  return Result;
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRenew()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRenew(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VBuildRenew()");
#endif

  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_REN);

  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptServerIdent(IpCtrlIdx, MsgPtr);
  }

  /* #20 Add ia address option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBuildIa(IpCtrlIdx, MsgPtr);
  }

  /* #30 Add option request option [RFC3315 18.1.3. Creation and Transmission of Renew Messages] */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptReqOpt(IpCtrlIdx, MsgPtr, &TcpIp_DhcpV6_OptionRequestList[0],
      TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN);
  }

  /* #40 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildRenew() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRebind()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRebind(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */
#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VBuildRebind()");
#endif
  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_REB);

  /* #20 Add ia address option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBuildIa(IpCtrlIdx, MsgPtr);
  }

  /* #30 Add option request list */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptReqOpt(IpCtrlIdx, MsgPtr,
      &TcpIp_DhcpV6_OptionRequestList[0], TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN);
  }
  /* #40 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildRebind() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildDecline()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildDecline(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VBuildDecline()");
#endif
  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_DEC);

  /* #20 Add server identifier */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptServerIdent(IpCtrlIdx, MsgPtr);
  }

  /* #30 Add ia address option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBuildIa(IpCtrlIdx, MsgPtr);
  }

  /* #40 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildDecline() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildConfirm()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildConfirm(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr->MsgBufPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(TCPIP_DHCPV6_MSG_HDR_LEN <= MsgPtr->MsgBufLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VBuildConfirm()");
#endif
  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_CNF);

  /* #20 Add ia address option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBuildIa(IpCtrlIdx, MsgPtr);
  }

  /* #30 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildConfirm() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRequest()
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
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRequest(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_REQ);

  /* #20 Add server identifier */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptServerIdent(IpCtrlIdx, MsgPtr);
  }

  /* #30 Add option request option [RFC3315 18.1.1. Creation and Transmission of Request Messages ] */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptReqOpt(IpCtrlIdx, MsgPtr,
      &TcpIp_DhcpV6_OptionRequestList[0], TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN);
  }


  /* #40 Add IA_NA option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBeginOptIaNa(IpCtrlIdx, MsgPtr,
      TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->IaId, 0u, 0u);
  }

  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VEndOptIaNa(IpCtrlIdx, MsgPtr);
  }

  /* #50 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildRequest() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/* DHCPv6 MESSATE TX */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTriggerTx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VTriggerTx(P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
   /* #10 Set tx pending flag to true */
  MsgPtr->TxPending = TRUE;
} /* End of TcpIp_DhcpV6_VTriggerTx() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTxMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VTxMessage(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)  MsgPtr)
{
  Std_ReturnType                   result = E_NOT_OK;
  uint16                           oldBufPos;
  uint8                            *bufPtr;
  TcpIp_IpTxRequestDescriptorType  ipTxReqDesc;
  uint16                           bufLenByte;
  uint16                           lenByte;
  TcpIp_LocalAddrV6IterType        ipAddrIdx = TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(IpCtrlIdx);

  /* link-local multicast address for all DHCPv6 server and relay agents */
  /* PRQA S 0759 1 */  /* MD_CSL_Union */
  CONST(IpBase_AddrIn6Type, TCPIP_CONST) TcpIp_DhcpV6_Addr_All_DHCP_Relay_Agents_and_Servers =
  {
    {
      0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02
    }
  };

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Store current message length */
  oldBufPos = MsgPtr->MsgBufPos;

  TcpIp_DhcpV6_VAddOptElapsedTime(IpCtrlIdx, MsgPtr);

  lenByte = MsgPtr->MsgBufPos + (uint16) sizeof(TcpIp_Udp_HdrType);
  bufLenByte = lenByte;  /* Add UDP Header length */

  if (BUFREQ_OK == IpV6_ProvideTxBuffer(&ipAddrIdx, TcpIp_GetIpV6SocketDynDhcpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX), &TcpIp_DhcpV6_Addr_All_DHCP_Relay_Agents_and_Servers, &bufPtr, &bufLenByte, &ipTxReqDesc, FALSE))
  {
    /* #20 If tx buffer is provided, fill up UDP Header fields */
    TCPIP_PUT_UINT16(bufPtr, UDP_HDR_OFF_SRCPORT, TCPIP_DHCPV6_CLIENT_PORT);
    TCPIP_PUT_UINT16(bufPtr, UDP_HDR_OFF_TGTPORT, TCPIP_DHCPV6_SERVER_PORT);
    TCPIP_PUT_UINT16(bufPtr, UDP_HDR_OFF_LENBYTE, lenByte);
    TCPIP_PUT_UINT16(bufPtr, UDP_HDR_OFF_CHKSUM, 0u);
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IpBase_Copy((IpBase_CopyDataType*)&bufPtr[sizeof(TcpIp_Udp_HdrType)], (IpBase_CopyDataType*)&MsgPtr->MsgBufPtr[0], MsgPtr->MsgBufPos);

    /* #30 UDP checksum is claculated by lower layer (IPv6 or in hardware) */
    result = IpV6_Transmit(TcpIp_GetIpV6SocketDynDhcpIdxOfIpV6General(TCPIP_IPV6GENERAL_IDX), &ipTxReqDesc, TCPIP_PROTOCOL_UDP, lenByte, FALSE, 0, FALSE);
  }

  /* remove elapsed time option from message buffer */
  MsgPtr->MsgBufPos = oldBufPos;

  return result;
} /* End of TcpIp_DhcpV6_VTxMessage() */


/* OPTION DECODING */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VGetNextOption()
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
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV6_VGetNextOption(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                     DataPtr,
  uint16                                                         DataLen,
  P2VAR(TcpIp_DhcpV6_OptLocationType, AUTOMATIC, TCPIP_APPL_VAR) OptPosPtr)
{
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptPtr;
  boolean result = TRUE;
#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != OptPosPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  if (TCPIP_DHCPV6_GET_OPT_OK != OptPosPtr->ErrCode)
  {
    /* #10 Return False if the previous get option operation failed */
    result = FALSE;
    /* Clear parameters of the OptPos argument */
    OptPosPtr->OptCode = 0;
    OptPosPtr->OptOfs = (uint16) sizeof(TcpIp_DhcpV6_OptIaNaHdrRawType);
    OptPosPtr->OptLen = 0;
  }
  else
  {
    OptPosPtr->OptOfs += OptPosPtr->OptLen;

    if (OptPosPtr->OptOfs == DataLen)
    {
      /* #20 return False if all options have been read */
      result = FALSE;
      OptPosPtr->OptLen  = 0;
      OptPosPtr->OptCode = 0;
    }
    else  if ((OptPosPtr->OptOfs + TCPIP_DHCPV6_OPT_HDR_LEN) > DataLen)
    {
      /* #30 Return False if there is not enough space left in buffer for header of next option */
      result = FALSE;
      /* Update error code in the OptPos */
      OptPosPtr->ErrCode = TCPIP_DHCPV6_GET_OPT_INV_HDR_LENGTH;
      OptPosPtr->OptLen  = 0u;
      OptPosPtr->OptCode = 0u;
    }
    else
    {
      /* #40 Process next option in the data buffer and store in the OptPos */
      OptPtr = &DataPtr[OptPosPtr->OptOfs];

      OptPosPtr->OptCode = (uint16)(((uint16)OptPtr[0] << 8) | ((uint16)OptPtr[1]));
      OptPosPtr->OptLen  = (uint16)(((uint16)OptPtr[2] << 8) | ((uint16)OptPtr[3]));

      OptPosPtr->OptOfs += TCPIP_DHCPV6_OPT_HDR_LEN;

      if ((OptPosPtr->OptOfs + OptPosPtr->OptLen) > DataLen)
      {
        /* #50 Return False if the option data length exceeds data buffer length */
        OptPosPtr->ErrCode = TCPIP_DHCPV6_GET_OPT_INV_LENGTH;
        result = FALSE;
      }
    }
  }
  return result;
} /* End of TcpIp_DhcpV6_VGetNextOption() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptIaAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptIaAddr(    /* PRQA S 2889 */ /* MD_IPV6_Rule15.5_ComplexFunction */
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                   DataPtr,
  uint16                                                       DataLen,
#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
  P2VAR(TcpIp_DhcpV6_OptIaAddrType, AUTOMATIC, TCPIP_APPL_VAR) DynIaAddrPtr,
  uint8                                                        DynIaAddrCount
#else
  P2VAR(TcpIp_DhcpV6_OptIaAddrType, AUTOMATIC, TCPIP_APPL_VAR) IaAddrPtr
#endif
)
{
  TcpIp_DhcpV6_OptLocationType OptLoc;

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0u < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != IaAddrPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* check minimum length of IAADDR option */
  if (TCPIP_DHCPV6_OPT_IAADDR_HDR_LEN > DataLen)
  {
    return E_NOT_OK;
  }

  OptLoc.OptOfs = (uint16) sizeof(TcpIp_DhcpV6_OptIaAddrHdrRawType);
  OptLoc.OptLen = 0;
  OptLoc.ErrCode = TCPIP_DHCPV6_GET_OPT_OK;

#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
  {
    boolean IaAddrIdxValid = FALSE;

    for (IaAddrIdx = 0; IaAddrIdx < DynIaAddrCount; IaAddrIdx++)
    {
      if (FALSE == DynIaAddrPtr[IaAddrIdx].Valid)
      {
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_ADDR_COPY(DynIaAddrPtr[IaAddrIdx].Addr, DataPtr[TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_ADDR]);
        DynIaAddrPtr[IaAddrIdx].PreferredLifetime = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_PREFLIFENBO);
        DynIaAddrPtr[IaAddrIdx].ValidLifetime     = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_VALDLIFENBO);

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
        CANOE_WRITE_STRING3("Opt IA_NA, Addr: %s, PreferredLifetime: %d, ValidLifetime: %d",
          IpV6_VNetAddr2String(&DynIaAddrPtr[IaAddrIdx].Addr.addr), DynIaAddrPtr[IaAddrIdx].PreferredLifetime,
          DynIaAddrPtr[IaAddrIdx].ValidLifetime);
#endif

        IaAddrIdxValid = TRUE;
        break;
      }
    }

    if (FALSE == IaAddrIdxValid)
    {
      return E_NOT_OK;
    }
  }
#else
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  IPV6_ADDR_COPY(IaAddrPtr->Addr, DataPtr[TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_ADDR]);
  IaAddrPtr->PreferredLifetime = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_PREFLIFENBO);
  IaAddrPtr->ValidLifetime     = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_VALDLIFENBO);

  if (IaAddrPtr->PreferredLifetime <= IaAddrPtr->ValidLifetime)
  {
    IaAddrPtr->Valid = TRUE;
  }
  else
  {
    IaAddrPtr->Valid = FALSE;
  }
#endif

  IaAddrPtr->StatusCode.StatusCode = TCPIP_DHCPV6_STATUS_CODE_SUCCESS;
  IaAddrPtr->StatusCode.StatusTextLen = 0;

   /* #10 Traverse through the Ia address options and process the options */
  while (TRUE == TcpIp_DhcpV6_VGetNextOption(DataPtr, DataLen, &OptLoc))
  {
    switch (OptLoc.OptCode)
    {
    case TCPIP_DHCPV6_OPT_STATUS_CODE:
      if (E_OK == TcpIp_DhcpV6_VDecodeOptStatusCode(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, &IaAddrPtr->StatusCode))
      {

      }
      break;

    default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
      /* Default case left blank intentionally */
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
      CANOE_WRITE_STRING3("TcpIp_DhcpV6_VDecodeOptIaAddr() Skipping unknown option code %d, length %d at offset %d",
        OptLoc.OptCode, OptLoc.OptLen, OptLoc.OptOfs);
#endif
      break;
    }
  } /* option loop */

  if (TCPIP_DHCPV6_GET_OPT_OK != OptLoc.ErrCode)
  {
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
    CANOE_WRITE_STRING0("TcpIp_DhcpV6_VRxReply() Option parsing error!");
#endif
    return E_NOT_OK;
  }

  return E_OK;

} /* End of TcpIp_DhcpV6_VDecodeOptIaAddr() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptIaNa()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptIaNa(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                 DataPtr,
  uint16                                                     DataLen,
  P2VAR(TcpIp_DhcpV6_OptIaNaType, AUTOMATIC, TCPIP_APPL_VAR) IaNaPtr)
{
  Std_ReturnType               retVal;
  TcpIp_DhcpV6_OptLocationType optLoc;
  uint32                       recIaId;

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0u < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != IaNaPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* check minimum length of IA_NA option */
  if (TCPIP_DHCPV6_OPT_IA_NA_HDR_LEN > DataLen)
  {
    IaNaPtr->Valid = FALSE;
    retVal = E_NOT_OK;
  }
  else
  {
    recIaId = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_OPT_OFF_IAIDNBO);
    IaNaPtr->T1 = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_OPT_OFF_T1NBO);
    IaNaPtr->T2 = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_OPT_OFF_T2NBO);

    /* Check if received Ia Id is same as the stored IA NA option */
    if (   (recIaId != IaNaPtr->IaId)
        || ((IaNaPtr->T2 > 0u) && (IaNaPtr->T1 > IaNaPtr->T2)))
    {
      /* Ignore option with invalid lifetimes */
      IaNaPtr->Valid = FALSE;
      retVal = E_NOT_OK;
    }
    else
    {
      IaNaPtr->Valid = TRUE;
      retVal = E_OK;
    }
  }

  if(retVal == E_OK)
  {
    optLoc.OptOfs = (uint16) sizeof(TcpIp_DhcpV6_OptIaNaHdrRawType);
    optLoc.OptLen = 0;
    optLoc.ErrCode = TCPIP_DHCPV6_GET_OPT_OK;
    IaNaPtr->StatusCode.StatusCode = TCPIP_DHCPV6_STATUS_CODE_SUCCESS;
    IaNaPtr->StatusCode.StatusTextLen = 0;

#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
    for (IaAddrIdx = 0; IaAddrIdx < IaNaPtr->IaAddrCount; IaAddrIdx++)
    {
      IaNaPtr->IaAddrPtr[IaAddrIdx].Valid = FALSE;
    }
#endif

    /* #10 Iterate over all options and process the options */
    while (TRUE == TcpIp_DhcpV6_VGetNextOption(DataPtr, DataLen, &optLoc))
    {
      switch (optLoc.OptCode)
      {
      case TCPIP_DHCPV6_OPT_IAADDR:
        (void)TcpIp_DhcpV6_VDecodeOptIaAddr(&DataPtr[optLoc.OptOfs],
          optLoc.OptLen, &IaNaPtr->IaAddr);
        break;

      case TCPIP_DHCPV6_OPT_STATUS_CODE:
        (void)TcpIp_DhcpV6_VDecodeOptStatusCode(&DataPtr[optLoc.OptOfs], optLoc.OptLen, &IaNaPtr->StatusCode);
        break;

      default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
        /* Default case left blank intentionally */
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
        CANOE_WRITE_STRING3("TcpIp_DhcpV6_VDecodeOptIaNa() Skipping unknown option code %d, length %d at offset %d", optLoc.OptCode, optLoc.OptLen, optLoc.OptOfs);
#endif
        break;
      }
    } /* option loop */

    if (TCPIP_DHCPV6_GET_OPT_OK != optLoc.ErrCode)
    {
  #if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
      CANOE_WRITE_STRING0("TcpIp_DhcpV6_VRxReply() Option parsing error!");
  #endif
      IaNaPtr->Valid = FALSE;
      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* End of TcpIp_DhcpV6_VDecodeOptIaNa() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptStatusCode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptStatusCode(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       DataPtr,
  uint16                                                           DataLen,
  P2VAR(TcpIp_DhcpV6_OptStatusCodeType, AUTOMATIC, TCPIP_APPL_VAR) StatusCodePtr)
{
  Std_ReturnType result = E_OK;

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION,   TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0u < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION,   TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != StatusCodePtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Check minimum length of status code option */
  if (TCPIP_DHCPV6_OPT_STATUS_CODE_HDR_LEN > DataLen)
  {
    result = E_NOT_OK;
  }
  else
  {
    /* #20 Update status code options */
    StatusCodePtr->StatusCode = TCPIP_GET_UINT16(DataPtr, TCPIP_DHCPV6_STATUSCODE_OPT_OFF_STATUSCODENBO);
    StatusCodePtr->StatusTextPtr = &DataPtr[sizeof(TcpIp_DhcpV6_OptStatusCodeHdrRawType)];
    StatusCodePtr->StatusTextLen = (uint16)(DataLen - sizeof(TcpIp_DhcpV6_OptStatusCodeHdrRawType));
  }

  return result;
} /* End of TcpIp_DhcpV6_VDecodeOptStatusCode() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptPreference()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptPreference(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR)    PreferenceValuePtr)
{
  Std_ReturnType result = E_OK;
#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0u < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != PreferenceValuePtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Check minimum length of status code option */
  if (TCPIP_DHCPV6_OPT_PREFERENCE_LEN != DataLen)
  {
    result = E_NOT_OK;
  }
  else
  {
    /* #20 Update preference value */
    *PreferenceValuePtr = DataPtr[0];
  }

  return result;
} /* End of TcpIp_DhcpV6_VDecodeOptPreference() */


#if (TCPIP_SUPPORT_DNS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptDnsServers()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptDnsServers(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       DataPtr,
  uint16                                                           DataLen,
  P2VAR(TcpIp_DhcpV6_OptDnsServersType, AUTOMATIC, TCPIP_APPL_VAR) DnsServersOptPtr)
{
  Std_ReturnType retVal;

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0u < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DnsServersOptPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Check minimum length of dns servers option and parse the option */
  if (0u != (DataLen & TCPIP_DHCPV6_MASK_MOD_16))
  {
    /* "Length of the list of DNS recursive name servers in octets;
     *  must be a multiple of 16"
     *  [RFC3646 3. DNS Recursive Name Server option]
     */

    DnsServersOptPtr->Valid = FALSE;
    retVal = E_NOT_OK;
  }
  else
  {
    retVal = E_OK;
    DnsServersOptPtr->Valid = TRUE;
    DnsServersOptPtr->Addrs = (TCPIP_P2C(IpBase_AddrIn6Type))DataPtr;  /* PRQA S 0310, 3305 */ /* MD_TCPIP_Rule11.3_0310_3305_AddrList */
    DnsServersOptPtr->AddrCount = (uint8)(DataLen >> TCPIP_DHCPV6_RSHIFT_DIV_16);
  }

  return retVal;
} /* End of TcpIp_DhcpV6_VDecodeOptDnsServers() */
#endif


#if (TCPIP_SUPPORT_DNS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptDomainList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptDomainList(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       DataPtr,
  uint16                                                           DataLen,
  P2VAR(TcpIp_DhcpV6_OptDomainListType, AUTOMATIC, TCPIP_APPL_VAR) DomainListOptPtr)
{
  Std_ReturnType retVal = E_NOT_OK;
#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0u < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DomainListOptPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  if(   (DataLen > 0u)
     && (DomainListOptPtr != NULL_PTR)
     && (DataPtr != NULL_PTR))
  {
    /* #10 Parse Domain list option */
    DomainListOptPtr->Valid = TRUE;
    DomainListOptPtr->List = DataPtr;
    DomainListOptPtr->ListLength = DataLen;
    retVal = E_OK;
  }

  return retVal;
} /* End of TcpIp_DhcpV6_VDecodeOptDomainList() */
#endif

/* MESSAGE RECEPTION */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxAdvertise()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VRxAdvertise(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen)
{
  Std_ReturnType Result;
  TcpIp_DhcpV6_OptLocationType OptLoc;
  boolean ClientDuidValid = FALSE;
  boolean ServerDuidValid = FALSE;
  uint16  ServerDuidOfs = 0;
  uint16  ServerDuidLen = 0;
  TcpIp_DhcpV6_OptStatusCodeType OptStCode;
  uint8 ServerPreference = 0;
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0u < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* assume status success if no status code option present */
  OptStCode.StatusCode = TCPIP_DHCPV6_STATUS_CODE_SUCCESS;
  OptStCode.StatusTextLen = 0;

  TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->Valid = FALSE;

  OptLoc.OptOfs = 0;
  OptLoc.OptLen = 0;
  OptLoc.ErrCode = TCPIP_DHCPV6_GET_OPT_OK;

  /* #10 Obtain and parse options inside advertise message */
  while (TRUE == TcpIp_DhcpV6_VGetNextOption(DataPtr, DataLen, &OptLoc))
  {
    switch (OptLoc.OptCode)
    {
    case TCPIP_DHCPV6_OPT_CLIENTID:
      {
        uint8 ClientDuidOfDhcpV6Data[sizeof(TcpIp_DhcpV6_DuIdType1)];
      /* check client identifier */
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
        TcpIp_DhcpV6_VDbgPrintOptId(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen);
#endif
        TCPIP_PUT_UINT16_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_TYPENBO,   TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->TypeNbo);
        TCPIP_PUT_UINT16_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_HWTYPENBO, TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->HwTypeNbo);
        TCPIP_PUT_UINT32_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_TIMENBO,   TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->TimeNbo);
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_LL_ADDR_COPY(&ClientDuidOfDhcpV6Data[TCPIP_DHCPV6_DUID1_OPT_OFF_PHYSADDR], &(TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->PhysAddr[0]));

        if (TRUE == TcpIp_DhcpV6_VCompareBytes(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen,
          ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_CLIENT_DUID_LEN))
        {
          /* valid client identifier */
          ClientDuidValid = TRUE;
        }
        else
        {
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
          CANOE_WRITE_STRING0("TcpIp_DhcpV6_VRxAdvertise() invalid client identifier!");
#endif
        }
      }
      break;

    case TCPIP_DHCPV6_OPT_SERVERID:
      if ((0u < OptLoc.OptLen) && (TCPIP_DHCPV6_DUID_MAX_LEN >= OptLoc.OptLen))
      {
        ServerDuidValid = TRUE;
        ServerDuidOfs = OptLoc.OptOfs;
        ServerDuidLen = OptLoc.OptLen;
      }
      else
      {
        TcpIp_DhcpV6_DetReportError(TCPIP_DHCPV6_API_ID_RX_INDICATION,
          TCPIP_DHCPV6_E_SERVER_ID_OVFL);
      }
      break;

    case TCPIP_DHCPV6_OPT_STATUS_CODE:
      (void)TcpIp_DhcpV6_VDecodeOptStatusCode(&DataPtr[OptLoc.OptOfs],
        OptLoc.OptLen, &OptStCode);
      break;

    case TCPIP_DHCPV6_OPT_IA_NA:
      (void)TcpIp_DhcpV6_VDecodeOptIaNa(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen,
        TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx));

      break;

    case TCPIP_DHCPV6_OPT_PREFERENCE:
      (void)TcpIp_DhcpV6_VDecodeOptPreference(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, &ServerPreference);
      break;

    default:
      /* #20 If Dhcp user options are enabled, check if the received option is a user option */
      if(TcpIp_IsDhcpUserOptionUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE)
      {
        TcpIp_DhcpV6_VHandleRxUserOption(IpCtrlIdx, OptLoc.OptCode, &DataPtr[OptLoc.OptOfs], OptLoc.OptLen);
      }
      break;
    }
  } /* option loop */

  if (TCPIP_DHCPV6_GET_OPT_OK != OptLoc.ErrCode)
  {
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
    CANOE_WRITE_STRING0("TcpIp_DhcpV6_VRxReply() Option parsing error!");
#endif
    Result = E_NOT_OK;
  }
  else
  {
    /* #30 Validate received advertisement */
    if (   ((TRUE == ClientDuidValid) && (TRUE == ServerDuidValid) &&(TCPIP_DHCPV6_STATUS_CODE_SUCCESS == OptStCode.StatusCode))  /* PRQA S 3415 4 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && ((TRUE == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->Valid) && (TCPIP_DHCPV6_STATUS_CODE_SUCCESS == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->StatusCode.StatusCode))
        && ((TRUE == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->IaAddr.Valid) && (TCPIP_DHCPV6_STATUS_CODE_SUCCESS == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->IaAddr.StatusCode.StatusCode))
        && ((FALSE == TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->Valid) || (TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->Preference < ServerPreference)))
    {
        TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->Valid = TRUE;
        TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->Preference  = ServerPreference;
        TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->ServerIdLen = (uint8)ServerDuidLen;
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        VStdMemCpy(&TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->ServerId[0], &DataPtr[ServerDuidOfs],
          TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->ServerIdLen);
    }

    Result = (TRUE == TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->Valid) ? E_OK : E_NOT_OK;
  }
  return Result;

} /* End of TcpIp_DhcpV6_VRxAdvertise() */ /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleRxUserOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleRxUserOption(
  TcpIp_IpV6CtrlIterType                       IpCtrlIdx,
  uint16                                       OptCode,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)   OptPtr,
  uint16                                       OptLen
)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Lookup the user option in the user option list */
  TcpIp_DhcpUserOptionIterType dhcpUserOptionIdx = TcpIp_DhcpV6_VLookupUserOption(IpCtrlIdx, OptCode);

  /* ----- Implementation ----------------------------------------------- */
  /* #20 Check if the requested user option is supported and is configured for RX */
  if (   (dhcpUserOptionIdx < TcpIp_GetSizeOfDhcpUserOption()) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_DhcpV6_VIsTxUserOption(dhcpUserOptionIdx) == FALSE))
  {
    TcpIp_DhcpUserOptionBufferIterType dhcpUserBufferIdx = TcpIp_GetDhcpUserOptionBufferStartIdxOfDhcpUserOption(dhcpUserOptionIdx);

    /* Use critical section as the Dhcp User option buffer may be overwritten by DhcpWriteOption */
    IPV6_BEGIN_CRITICAL_SECTION_DOPT();

    /* If option is configured, proceed to handle the option */
    if (OptLen <= TcpIp_GetDhcpUserOptionBufferLengthOfDhcpUserOption(dhcpUserOptionIdx))
    {
      /* #30 If OptLen fits into the buffer, then copy the complete data from user to the user option buffer */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpBase_Copy(TcpIp_GetAddrDhcpUserOptionBuffer(dhcpUserBufferIdx), OptPtr, OptLen);
      TcpIp_SetLengthOfDhcpUserOptionDyn(dhcpUserOptionIdx, OptLen);
    }
    else
    {
      /* #40 If OptLen does not fit into the buffer, then copy only data that fits into the buffer from user to the user option buffer */
      /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
      IpBase_Copy(TcpIp_GetAddrDhcpUserOptionBuffer(dhcpUserBufferIdx), OptPtr, TcpIp_GetDhcpUserOptionBufferLengthOfDhcpUserOption(dhcpUserOptionIdx));
      TcpIp_SetLengthOfDhcpUserOptionDyn(dhcpUserOptionIdx, TcpIp_GetDhcpUserOptionBufferLengthOfDhcpUserOption(dhcpUserOptionIdx));
    }

    IPV6_END_CRITICAL_SECTION_DOPT();
  }
} /* TcpIp_DhcpV6_VHandleRxUserOption() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VProcessValidateRxReplyOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VProcessValidateRxReplyOptions(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  IPV6_P2V(TcpIp_DhcpV6_OptStatusCodeType)   OptStatusCodePtr,
#if (TCPIP_SUPPORT_DNS == STD_ON)
  IPV6_P2V(TcpIp_DhcpV6_OptDnsServersType)   OptDnsServersPtr,
  IPV6_P2V(TcpIp_DhcpV6_OptDomainListType)   OptDomainListPtr,
#endif
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen)
{
  Std_ReturnType Result = E_OK;
  TcpIp_DhcpV6_OptLocationType OptLoc;
  TcpIp_SizeOfDhcpV6DataType   dhcpV6DataIdx   = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
#if (TCPIP_SUPPORT_DNS == STD_ON)
  TcpIp_SizeOfDhcpV6ConfigType dhcpV6ConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);
#endif
  boolean ValidClientId = FALSE;
  boolean ValidServerId = FALSE;

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data());   /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  OptLoc.OptOfs = 0;
  OptLoc.OptLen = 0;
  OptLoc.ErrCode = TCPIP_DHCPV6_GET_OPT_OK;

  /* #10 Obtain and parse options in reply message */
  while (TRUE == TcpIp_DhcpV6_VGetNextOption(DataPtr, DataLen, &OptLoc))
  {
    switch (OptLoc.OptCode)
    {
    case TCPIP_DHCPV6_OPT_CLIENTID:
      {
        uint8 ClientDuidOfDhcpV6Data[sizeof(TcpIp_DhcpV6_DuIdType1)];
        TCPIP_PUT_UINT16_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_TYPENBO,   TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->TypeNbo);
        TCPIP_PUT_UINT16_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_HWTYPENBO, TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->HwTypeNbo);
        TCPIP_PUT_UINT32_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_TIMENBO,   TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->TimeNbo);
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_LL_ADDR_COPY(&ClientDuidOfDhcpV6Data[TCPIP_DHCPV6_DUID1_OPT_OFF_PHYSADDR], &(TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpV6DataIdx)->PhysAddr[0]));

        if (TRUE == TcpIp_DhcpV6_VCompareBytes(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_CLIENT_DUID_LEN))
        {
          ValidClientId = TRUE;
        }
      }
      break;

    case TCPIP_DHCPV6_OPT_SERVERID:
      if (TRUE == TcpIp_DhcpV6_VCompareBytes(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, &(TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->ServerId[0]), TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->ServerIdLen))
      {
        ValidServerId = TRUE;
      }
      break;

    case TCPIP_DHCPV6_OPT_STATUS_CODE:
      {
        (void)TcpIp_DhcpV6_VDecodeOptStatusCode(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, OptStatusCodePtr);
      }
      break;

    case TCPIP_DHCPV6_OPT_IA_NA:
      if (E_OK != TcpIp_DhcpV6_VDecodeOptIaNa(&DataPtr[OptLoc.OptOfs],
        OptLoc.OptLen, TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)))
      {
        /* invalid IA_NA option */
      }
      break;

#if (TCPIP_SUPPORT_DNS == STD_ON)
    case TCPIP_DHCPV6_OPT_DNS_SERVERS:
      if (TcpIp_IsEnableRdnssOptOfDhcpV6Config(dhcpV6ConfigIdx) == TRUE)
      {
        if (E_OK != TcpIp_DhcpV6_VDecodeOptDnsServers(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, OptDnsServersPtr))
        {
          /* invalid DNS_SERVERS option */
        }
      }
      break;

    case TCPIP_DHCPV6_OPT_DOMAIN_LIST:
      if (TcpIp_IsEnableDnsslOptOfDhcpV6Config(dhcpV6ConfigIdx) == TRUE)
      {
        if (E_OK != TcpIp_DhcpV6_VDecodeOptDomainList(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, OptDomainListPtr))
        {
          /* invalid DOMAIN_LIST option */
        }
      }
      break;
#endif

    default:
      /* If Dhcp user options are enabled, check if the received option is user option */
      if(TcpIp_IsDhcpUserOptionUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE)
      {
        TcpIp_DhcpV6_VHandleRxUserOption(IpCtrlIdx, OptLoc.OptCode, &DataPtr[OptLoc.OptOfs], OptLoc.OptLen);
      }
      break;
    }
  }

  if (   (TCPIP_DHCPV6_GET_OPT_OK != OptLoc.ErrCode)/* Opt code procesing failed */
      || (FALSE == ValidClientId)
      || (FALSE == ValidServerId))
  {
    /* #20 Ignore reply messages with invalid client or server identifier or error status code */
    Result = E_NOT_OK;
  }

  return Result;
} /* TcpIp_DhcpV6_VProcessValidateRxReplyOptions() */ /* PRQA S 6030, 6050, 6060 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess, MD_MSR_STPAR */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VProcessRxReplyIanaOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VProcessRxReplyIanaOption(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx)
{
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->Valid = TRUE;
  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->T1Timeout =
    (TcpIp_DhcpV6_Time.S + TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->T1);

  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->T2Timeout =
    (TcpIp_DhcpV6_Time.S + TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->T2);

  /* #10 Check if iana option contains valid address */
  if (   (TRUE == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->IaAddr.Valid)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TCPIP_DHCPV6_STATUS_CODE_SUCCESS == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->IaAddr.StatusCode.StatusCode))
  {
    TcpIp_SizeOfLocalAddrV6Type localAddrIdx =
      TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(IpCtrlIdx));
    /* IA_NA option contains valid address */

    /* #20 update address lease information and add to source address table */
    /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
    IPV6_ADDR_COPY(TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->AddrLease.Addr,
      TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->IaAddr.Addr);

    TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->AddrLease.PreferredUntil =
      (TcpIp_DhcpV6_Time.S + TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->IaAddr.PreferredLifetime);

    TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->AddrLease.ValidUntil     =
      (TcpIp_DhcpV6_Time.S + TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->IaAddr.ValidLifetime);

    if (E_OK == IpV6_SetAddress(localAddrIdx, &(TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->AddrLease.Addr),
      TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->IaAddr.PreferredLifetime,
      TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->IaAddr.ValidLifetime, FALSE))
    {
      TCPIP_DHCPV6_CHANGE_STATE(dhcpV6DataIdx, BOUND);

      /* wait until T1 has been expired */
      TCPIP_DHCPV6_TIME_SET(*TcpIp_GetAddrIdleTimeOfDhcpV6Data(dhcpV6DataIdx),
        TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->T1Timeout, 0u);
    }
    else
    {
      TCPIP_DHCPV6_CHANGE_STATE(dhcpV6DataIdx, FAIL);
    }
  }
} /* TcpIp_DhcpV6_VProcessRxReplyIanaOption() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VProcessRxReplyStatusCode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VProcessRxReplyStatusCode(
  TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  if (TCPIP_DHCPV6_STATUS_CODE_SUCCESS == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->StatusCode.StatusCode)
  {
    /* #10 Process iana option if it has positive status code */

    TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->Valid = TRUE;
    TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->T1Timeout =
      (TcpIp_DhcpV6_Time.S + TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->T1);

    TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->T2Timeout =
      (TcpIp_DhcpV6_Time.S + TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->T2);

    TcpIp_DhcpV6_VProcessRxReplyIanaOption(IpCtrlIdx);
  }
  else if (TCPIP_DHCPV6_STATUS_CODE_NOT_ON_LINK ==
    TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->StatusCode.StatusCode)
  {
    /* #20 If status code is Not on link, the requested address is not on-link and must not be used,
     * restart address assignment */

    TcpIp_DhcpV6_VRestartAddressAssignment(IpCtrlIdx, 0u);
  }
  else if (TCPIP_DHCPV6_STATUS_CODE_NO_BINDING ==
    TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->StatusCode.StatusCode)
  {
    /* #30 If status code is No binding, dhcpv6 server has no valid binding. request new address */

    (void)TcpIp_DhcpV6_VBuildRequest(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpV6DataIdx));
    TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, REQ);
    TCPIP_DHCPV6_CHANGE_STATE(dhcpV6DataIdx, TX_REQ);
    TCPIP_DHCPV6_SET_IDLE_TIME_ZERO(dhcpV6DataIdx);
  }
  else
  {
    /* Unknown status code in IA_NA option. Ignore the reply */
  }

} /* TcpIp_DhcpV6_VProcessRxReplyStatusCode() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VUpdateRxReplyDhcpState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VUpdateRxReplyDhcpState(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
#if (TCPIP_SUPPORT_DNS == STD_ON)
  IPV6_P2C(TcpIp_DhcpV6_OptDnsServersType)   OptDnsServersPtr,
  IPV6_P2C(TcpIp_DhcpV6_OptDomainListType)   OptDomainListPtr,
#endif
  IPV6_P2C(TcpIp_DhcpV6_OptStatusCodeType)   OptStatusCodePtr)
{
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx   = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
#if (TCPIP_SUPPORT_DNS == STD_ON)
  TcpIp_SizeOfDhcpV6ConfigType dhcpV6ConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);
#endif

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  switch (TcpIp_GetStateOfDhcpV6Data(dhcpV6DataIdx))
  {
  case TCPIP_DHCPV6_STATE_TX_REL: /* Release */
  case TCPIP_DHCPV6_STATE_TX_DEC: /* Decline */
    /* #10 Ignore reply received in response to release or decline message */
    TCPIP_DHCPV6_CHANGE_STATE(dhcpV6DataIdx, UNBOUND);
    break;

  case TCPIP_DHCPV6_STATE_TX_REQ: /* Request */
  case TCPIP_DHCPV6_STATE_TX_CNF: /* Confirm */
  case TCPIP_DHCPV6_STATE_TX_REB: /* Rebind */
  case TCPIP_DHCPV6_STATE_TX_REN: /* Renew */

    /* #20 Process reply received in response to request, confirm, rebind or renew message */

    if (TCPIP_DHCPV6_STATUS_CODE_SUCCESS == OptStatusCodePtr->StatusCode)
    {
#if (TCPIP_SUPPORT_DNS == STD_ON)
      if (TcpIp_IsEnableRdnssOptOfDhcpV6Config(dhcpV6ConfigIdx) == TRUE)
      {
        if (OptDnsServersPtr->Valid == TRUE)
        {
          Dns_UpdateIpV6Servers(OptDnsServersPtr->Addrs, OptDnsServersPtr->AddrCount, TCPIP_DHCPV6_LIFETIME_UNLIMITED, 0u);
        }
      }

      TCPIP_UNUSED_PARAMETER(OptDomainListPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
      if (TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx))->Valid == TRUE)
      {
        /* #30 Process matching IA_NA option if status code is success */
        TcpIp_DhcpV6_VProcessRxReplyStatusCode(IpCtrlIdx);
      }
      else
      {
        /* reply message does not contain matching IA_NA option. Ignore reply. */
      }
    }
    else if (   (TCPIP_DHCPV6_STATUS_CODE_NO_BINDING == OptStatusCodePtr->StatusCode)
             || (TCPIP_DHCPV6_STATUS_CODE_NOT_ON_LINK == OptStatusCodePtr->StatusCode))
    {
      /* #40 If reply message contains negative status code NO_BINDING or NOT_ON_LINK, restart address assignment procedure */

      TcpIp_DhcpV6_VRestartAddressAssignment(IpCtrlIdx, 0u);
    }
    else
    {
      /* reply message contains negative status code. Do not handle reply. */
    }

    break;


  default:
    /* ignore reply */
    break;
  }
}  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxReply()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRxReply(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen)
{
  TcpIp_DhcpV6_OptStatusCodeType OptStatusCode;
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

#if (TCPIP_SUPPORT_DNS == STD_ON)
  TcpIp_DhcpV6_OptDnsServersType OptDnsServers;
  TcpIp_DhcpV6_OptDomainListType OptDomainList;
#endif

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0u < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->Valid = FALSE;
  OptStatusCode.StatusCode = TCPIP_DHCPV6_STATUS_CODE_SUCCESS;
  OptStatusCode.StatusTextLen = 0;

#if (TCPIP_SUPPORT_DNS == STD_ON)
  OptDnsServers.Valid = FALSE;
  OptDomainList.Valid = FALSE;
#endif
   /* #10 Validate the options in the received reply */
  if (E_OK == TcpIp_DhcpV6_VProcessValidateRxReplyOptions(IpCtrlIdx, &OptStatusCode,
#if (TCPIP_SUPPORT_DNS == STD_ON)
    &OptDnsServers, &OptDomainList,
#endif
    DataPtr, DataLen))
  {
    /* #20 Process the options and update the dhcp state */
    TcpIp_DhcpV6_VUpdateRxReplyDhcpState(IpCtrlIdx,
#if (TCPIP_SUPPORT_DNS == STD_ON)
      &OptDnsServers, &OptDomainList,
#endif
    &OptStatusCode);
  }
  else
  {
    /* validation failed */
  }
} /* End of TcpIp_DhcpV6_VRxReply() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRestartAddressAssignment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRestartAddressAssignment(TcpIp_IpV6CtrlIterType IpCtrlIdx, uint32 DelayMs)
{
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->Valid = FALSE;
  TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpV6DataIdx)->ServerIdLen = 0;

  if (TRUE == TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->Valid)
  {
    /* #10 remove dhcpv6 assigned address from source address table */
    TcpIp_IpV6SourceAddressIterType ipV6SrcAddrIdx = TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(IpCtrlIdx);

    (void)IpV6_SetAddress(TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(ipV6SrcAddrIdx),
      &(TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->AddrLease.Addr), 0, 0, FALSE);

    TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->Valid = FALSE;
  }

  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->IaId = 0;

#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->AddrLeasePtr   = &TcpIp_DhcpV6_IaAddrLeases[0];
  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->AddrLeaseCount = 1;

  TcpIp_DhcpV6_IaAddrLeases[0].ValidUntil = 0;
  TcpIp_DhcpV6_IaAddrLeases[0].PreferredUntil = 0;
#endif

  TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->Valid = FALSE;
  TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpV6DataIdx)->IaId = TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->IaId;

#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
  TcpIp_DhcpV6_IaNaBuf.IaAddrPtr = &TcpIp_DhcpV6_IaAddrBuf[0];
  TcpIp_DhcpV6_IaNaBuf.IaAddrCount = 1;
#endif

  /* #20 Send dhcpv6 solicit message for address assignment */
  (void)TcpIp_DhcpV6_VBuildSolicit(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpV6DataIdx));
  TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, SOL);
  TCPIP_DHCPV6_CHANGE_STATE(dhcpV6DataIdx, TX_SOL);
  TCPIP_DHCPV6_SET_IDLE_TIME_MS(dhcpV6DataIdx, DelayMs);
} /* TcpIp_DhcpV6_VRestartAddressAssignment() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/* PUBLIC FUNCTIONS */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_IsActive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV6_IsActive(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  boolean result = TRUE;
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */
  /* #10 Check if Dhcp is in valid state */
  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  if (   (TCPIP_DHCPV6_STATE_INIT == TcpIp_GetStateOfDhcpV6Data(dhcpV6DataIdx))
      || (TCPIP_DHCPV6_STATE_FAIL == TcpIp_GetStateOfDhcpV6Data(dhcpV6DataIdx)))
  {
    result = FALSE;
  }

  return result;
} /* End of TcpIp_DhcpV6_IsActive() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_StartAddressAssignment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_StartAddressAssignment(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfDhcpV6ConfigType dhcpV6ConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6ConfigIdx < TcpIp_GetSizeOfDhcpV6Config()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */
  TCPIP_ASSERT(TCPIP_DHCPV6_IS_INITIALIZED(TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx)));

  TcpIp_DhcpV6_VInitClientId(IpCtrlIdx);

  /* #10 Check the configured delay values and delay sending of first solicit message */
  if (TcpIp_GetSolicitDelayMinOfDhcpV6Config(dhcpV6ConfigIdx) == TcpIp_GetSolicitDelayMaxOfDhcpV6Config(dhcpV6ConfigIdx))
  {
    TcpIp_DhcpV6_VRestartAddressAssignment(IpCtrlIdx, TcpIp_GetSolicitDelayMinOfDhcpV6Config(dhcpV6ConfigIdx));
  }
  else
  {
    TcpIp_DhcpV6_VRestartAddressAssignment(IpCtrlIdx,
       TcpIp_DhcpV6_VGetRandomValue(TcpIp_GetSolicitDelayMinOfDhcpV6Config(dhcpV6ConfigIdx), TcpIp_GetSolicitDelayMaxOfDhcpV6Config(dhcpV6ConfigIdx)));
  }

} /* End of TcpIp_DhcpV6_StartAddressAssignment() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_StartAddressAssignmentForAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_StartAddressAssignmentForAddr(TcpIp_SizeOfLocalAddrV6Type LocalAddrV6Idx)
{
  Std_ReturnType result = E_NOT_OK;
  TcpIp_IpV6CtrlIterType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);

  if (TcpIp_IsIpV6SourceAddressUsedOfLocalAddrV6(LocalAddrV6Idx) == TRUE)
  {
    TcpIp_IpV6SourceAddressIterType ipV6SrcAddrIdx = TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6(LocalAddrV6Idx);
    /* #10 Trigger address assignment only if the Ip address index is Dhcp configurable */
    if (TcpIp_GetAddressAssignVariantOfIpV6SourceAddress(ipV6SrcAddrIdx) == TCPIP_IPADDR_ASSIGNMENT_DHCP)
    {
      TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */
      TcpIp_DhcpV6_StartAddressAssignment(ipCtrlIdx);
      result = E_OK;
    }
  }

  return result;
}


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_RequestInformation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_RequestInformation(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_SizeOfDhcpV6ConfigType dhcpV6ConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */
  TCPIP_ASSERT(TCPIP_DHCPV6_IS_INITIALIZED(dhcpV6DataIdx));
  TcpIp_DhcpV6_VInitClientId(IpCtrlIdx);

  Result = TcpIp_DhcpV6_VBuildInfoRequest(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpV6DataIdx));

  if (E_OK == Result)
  {
    TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, INF);
    TCPIP_DHCPV6_CHANGE_STATE(dhcpV6DataIdx, TX_INF);
    TcpIp_DhcpV6_VTriggerTx(TcpIp_GetAddrMsgOfDhcpV6Data(dhcpV6DataIdx));

    /* #10 Check the configured delay sending of first info request message */
    if (TcpIp_GetInfoRequestDelayMinOfDhcpV6Config(dhcpV6ConfigIdx) == TcpIp_GetInfoRequestDelayMaxOfDhcpV6Config(dhcpV6ConfigIdx))
    {
      TCPIP_DHCPV6_SET_IDLE_TIME_MS(dhcpV6DataIdx, TcpIp_GetInfoRequestDelayMinOfDhcpV6Config(dhcpV6ConfigIdx));
    }
    else
    {
      TCPIP_DHCPV6_SET_IDLE_TIME_MS(dhcpV6DataIdx,
        TcpIp_DhcpV6_VGetRandomValue(TcpIp_GetInfoRequestDelayMinOfDhcpV6Config(dhcpV6ConfigIdx), TcpIp_GetInfoRequestDelayMaxOfDhcpV6Config(dhcpV6ConfigIdx)));
    }
  }

  return Result;
} /* End of TcpIp_DhcpV6_RequestInformation() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_Decline()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_Decline(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2CONST(IpBase_AddrIn6Type, AUTOMATIC, IPV6_APPL_DATA) AddrPtr)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */
  TCPIP_ASSERT(TCPIP_DHCPV6_IS_INITIALIZED(dhcpV6DataIdx));
  TCPIP_ASSERT(NULL_PTR != AddrPtr);

  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  if (   (TRUE == TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->Valid)
      && (TRUE == IpV6_CmpNetAddr(AddrPtr, &(TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->AddrLease.Addr))))
  {
    /* #10 Invoke routine to build a dhcpv6 decline message for the given Ip address */
    Result = TcpIp_DhcpV6_VBuildDecline(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpV6DataIdx));

    if (E_OK == Result)
    {
      /* #20 Update retransmission params and state for decline messages */
      TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, DEC);
      TCPIP_DHCPV6_CHANGE_STATE(dhcpV6DataIdx, TX_DEC);
      TCPIP_DHCPV6_SET_IDLE_TIME_ZERO(dhcpV6DataIdx);
    }
  }
  else
  {
    Result = E_NOT_OK;
  }

  return Result;
} /* End of TcpIp_DhcpV6_Decline() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_Confirm()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_Confirm(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_SizeOfDhcpV6ConfigType dhcpV6ConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data());  /* Assert that DhcpV6 is configured for the IpCtrlIdx */
  TCPIP_ASSERT(TCPIP_DHCPV6_IS_INITIALIZED(dhcpV6DataIdx));

  if (TRUE == TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->Valid)
  {
    /* #10 Build dhcpv6 confirm message for te assigned address */
    Result = TcpIp_DhcpV6_VBuildConfirm(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpV6DataIdx));

    if (E_OK == Result)
    {
      TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, CNF);
      TCPIP_DHCPV6_CHANGE_STATE(dhcpV6DataIdx, TX_CNF);

      /* #20 Generate random delay for resending confirm message */
      if (TcpIp_GetConfirmDelayMinOfDhcpV6Config(dhcpV6ConfigIdx) == TcpIp_GetConfirmDelayMaxOfDhcpV6Config(dhcpV6ConfigIdx))
      {
        /* delay sending of first confirm message */
        TCPIP_DHCPV6_SET_IDLE_TIME_MS(dhcpV6DataIdx, TcpIp_GetConfirmDelayMinOfDhcpV6Config(dhcpV6ConfigIdx));
      }
      else
      {
        TCPIP_DHCPV6_SET_IDLE_TIME_MS(dhcpV6DataIdx,
          TcpIp_DhcpV6_VGetRandomValue(TcpIp_GetConfirmDelayMinOfDhcpV6Config(dhcpV6ConfigIdx), TcpIp_GetConfirmDelayMaxOfDhcpV6Config(dhcpV6ConfigIdx)));
      }
    }
  }
  else
  {
    Result = E_NOT_OK;
  }

  return Result;
} /* End of TcpIp_DhcpV6_Confirm() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_ReleaseAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_ReleaseAddress(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */
  TCPIP_ASSERT(TCPIP_DHCPV6_IS_INITIALIZED(dhcpV6DataIdx));

  if (TRUE == TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->Valid)
  {
    /* #10 Build dhcpv6 release message for assigned address */
    Result = TcpIp_DhcpV6_VBuildRelease(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpV6DataIdx));

    if (E_OK == Result)
    {
      /* #20 Remove the released dhcpv6 address from source address table */
      TcpIp_IpV6SourceAddressIterType ipV6SrcAddrIdx = TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(IpCtrlIdx);

      (void)IpV6_SetAddress(TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(ipV6SrcAddrIdx),
        &(TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->AddrLease.Addr), 0, 0, FALSE);
      /* #30 Update retransmission params and state for release message */
      TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, REL);
      TCPIP_DHCPV6_CHANGE_STATE(dhcpV6DataIdx, TX_REL);
      TCPIP_DHCPV6_SET_IDLE_TIME_ZERO(dhcpV6DataIdx);
    }
  }
  else
  {
    Result = E_NOT_OK;
  }

  return Result;
} /* End of TcpIp_DhcpV6_ReleaseAddress() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_NotifyAddressReset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_NotifyAddressReset(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  /* Check if the dhcpv6 address was lost due to RELEASE message */
  if (TcpIp_GetStateOfDhcpV6Data(dhcpV6DataIdx) != TCPIP_DHCPV6_STATE_TX_REL)
  {
    /* #10 If adress has been unassigned, reset Dhcpv6 */
    (void)TcpIp_DhcpV6_Reset(IpCtrlIdx);
  }
  else
  {
    /* #20 If DhcpV6 in Release state, wait until release messages have been sent */
  }
} /* TcpIp_DhcpV6_NotifyAddressReset() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_Reset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_Reset(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_SizeOfDhcpV6MsgTxBufferType dhcpTxBufIdx = TcpIp_GetDhcpV6MsgTxBufferStartIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Reset all dhcpv6 configuration parameters */
  TcpIp_SetCurrentTransIdOfDhcpV6Data(dhcpV6DataIdx, TCPIP_DHCPV6_INV_TRANS_ID);
  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->Valid = FALSE;
  TCPIP_DHCPV6_SET_IDLE_TIME_MS(dhcpV6DataIdx, 1000u);
  TCPIP_DHCPV6_CHANGE_STATE(dhcpV6DataIdx, INIT);

  TcpIp_GetAddrMsgOfDhcpV6Data(dhcpV6DataIdx)->TxPending = FALSE;
  TcpIp_GetAddrMsgOfDhcpV6Data(dhcpV6DataIdx)->MsgBufPtr = TcpIp_GetAddrDhcpV6MsgTxBuffer(dhcpTxBufIdx);
  TcpIp_GetAddrMsgOfDhcpV6Data(dhcpV6DataIdx)->MsgBufLen = TcpIp_GetSizeOfDhcpV6MsgTxBuffer();

  /* #20 Clear all tx options */
#if (TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON)
  {
    TcpIp_DhcpUserOptionIterType dhcpUserOptionIdx;
    TcpIp_SizeOfDhcpV6TxOption39InfoType dhcpV6TxOpt39InfoIdx = TcpIp_GetDhcpV6TxOption39InfoIdxOfIpV6Ctrl(IpCtrlIdx);
    TcpIp_SetOptLenOfDhcpV6TxOption39Info(dhcpV6TxOpt39InfoIdx, 0);

    /* #30 Clear all the user option lengths */
    for (dhcpUserOptionIdx = TcpIp_GetDhcpUserOptionStartIdxOfIpV6Ctrl(IpCtrlIdx); dhcpUserOptionIdx < TcpIp_GetDhcpUserOptionEndIdxOfIpV6Ctrl(IpCtrlIdx); dhcpUserOptionIdx++)
    {
      TcpIp_SetLengthOfDhcpUserOptionDyn(dhcpUserOptionIdx, 0);
    }
  }
#endif
} /* End of TcpIp_DhcpV6_Reset() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


#if (TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VGetTxOption
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VGetTxOption(
    TcpIp_SizeOfLocalAddrV6Type               LocalAddrV6Idx,
    uint16                                    OptId,
    P2VAR(uint16, AUTOMATIC, TCPIP_APPL_DATA) OptLenPtr,
    P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)  OptPtr)
{
  Std_ReturnType            RetValue = E_NOT_OK;
  uint8                     errorId = TCPIP_DHCPV6_E_NO_ERROR;
  TcpIp_IpV6CtrlIterType    ipCtrlIdx;
  TcpIp_IpV6SourceAddressIterType srcAddrIdx;

  srcAddrIdx = TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6(LocalAddrV6Idx);
  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);
  if (TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(ipCtrlIdx) == srcAddrIdx)
  {
    /* #10 Check if the user has requested FQDN option */
    if ((OptId == TCPIP_DHCPV6_OPT_ID_CLIENT_FQDN) && (TcpIp_IsDhcpV6TxOption39InfoUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    {
      TcpIp_SizeOfDhcpV6TxOption39InfoType dhcpV6TxOpt39InfoIdx = TcpIp_GetDhcpV6TxOption39InfoIdxOfIpV6Ctrl(ipCtrlIdx);

      /* #20 Check if the data buffer provided by user has enough size */
      if (*OptLenPtr >= TcpIp_GetOptLenOfDhcpV6TxOption39Info(dhcpV6TxOpt39InfoIdx))
      {
        /* #30 If there is valid data, copy length and host name */
        *OptLenPtr = TcpIp_GetOptLenOfDhcpV6TxOption39Info(dhcpV6TxOpt39InfoIdx);
        if (*OptLenPtr > 0u)
        {
          TcpIp_SizeOfDhcpV6TxOption39Type txOpt39Idx = TcpIp_GetDhcpV6TxOption39StartIdxOfIpV6Ctrl(ipCtrlIdx);
          /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
          IpBase_Copy(OptPtr, TcpIp_GetAddrDhcpV6TxOption39(txOpt39Idx), *OptLenPtr);
        }

        RetValue = E_OK;
      }
      else
      {
        /* #40 If provided buffer length is invalid, raise DET error */
        errorId = TCPIP_DHCPV6_E_INV_PARAM;
      }
    }
    /* #50 Lookup the requested user option in the list of configured user option */
    else
    {
      TcpIp_DhcpUserOptionIterType dhcpUserOptionIdx = TcpIp_DhcpV6_VLookupUserOption(ipCtrlIdx, OptId);

      /* #60 Check if the requested user option is configured
          and the data buffer provided by the user is big enough */
      if (   (dhcpUserOptionIdx < TcpIp_GetSizeOfDhcpUserOption()) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          && (*OptLenPtr >= TcpIp_GetLengthOfDhcpUserOptionDyn(dhcpUserOptionIdx)))
      {
        *OptLenPtr = TcpIp_GetLengthOfDhcpUserOptionDyn(dhcpUserOptionIdx);

        /* #70 Check if there is valid data in the option data buffer */
        if (*OptLenPtr > 0u)
        {
          TcpIp_DhcpUserOptionBufferIterType dhcpUserBufferIdx = TcpIp_GetDhcpUserOptionBufferStartIdxOfDhcpUserOption(dhcpUserOptionIdx);

          /* #80 Copy the complete data from user option buffer to the upper layer buffer */
          /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
          IpBase_Copy(OptPtr, TcpIp_GetAddrDhcpUserOptionBuffer(dhcpUserBufferIdx), *OptLenPtr);
        }

        RetValue = E_OK;
      }
      else
      {
        /* #90 If option or buffer length is invalid, raise DET error */
        errorId = TCPIP_DHCPV6_E_INV_PARAM;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  if(errorId != TCPIP_DHCPV6_E_NO_ERROR)
  {
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
    (void)Det_ReportError(TCPIP_DHCPV6_MODULE_ID, TCPIP_DHCPV6_VINSTANCE_ID, TCPIP_DHCPV6_API_ID_GET_RX_OPT, errorId);
#endif
  }
  return RetValue;
} /* End of TcpIp_DhcpV6_VGetTxOption() */  /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VIsTxUserOption
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV6_VIsTxUserOption(
  TcpIp_DhcpUserOptionIterType       DhcpUserOptionIdx)
{
  boolean result = FALSE;

  /* #10 Lookup the direction of configured Dhcp User options */
  if (TCPIP_DHCP_USER_OPTION_TX == TcpIp_GetDirectionOfDhcpUserOption(DhcpUserOptionIdx))
  {
    result = TRUE;
  }

  return result;
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VLookupUserOption
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(TcpIp_DhcpUserOptionIterType, TCPIP_CODE) TcpIp_DhcpV6_VLookupUserOption(
  TcpIp_IpV6CtrlIterType             IpCtrlIdx,
  uint16                             OptType)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_DhcpUserOptionIterType dhcpUserOptionIdx;
  boolean flag = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Lookup the given option in the list of configured Dhcp User options */
  for (dhcpUserOptionIdx = TcpIp_GetDhcpUserOptionStartIdxOfIpV6Ctrl(IpCtrlIdx); dhcpUserOptionIdx < TcpIp_GetDhcpUserOptionEndIdxOfIpV6Ctrl(IpCtrlIdx); dhcpUserOptionIdx++)
  {
    if (OptType == TcpIp_GetCodeOfDhcpUserOption(dhcpUserOptionIdx))
    {
      flag = TRUE;
      break;
    }
  }

  /* ----- Error Check --------------------------------------- */
  if (flag == FALSE)
  {
    dhcpUserOptionIdx = TcpIp_GetSizeOfDhcpUserOption();
  }

  return dhcpUserOptionIdx;
} /* TcpIp_DhcpV6_VLookupUserOption() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetTxOption
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
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VSetTxOption(
    TcpIp_SizeOfLocalAddrV6Type                LocalAddrV6Idx,
    uint16                                     OptId,
    uint16                                     OptLen,
    P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptPtr,
    uint16                                     MsgTypes)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_IpV6CtrlIterType     ipCtrlIdx;
  Std_ReturnType             retValue = E_NOT_OK;
  uint8                      errorId  = TCPIP_DHCPV6_E_NO_ERROR;
  TcpIp_SizeOfDhcpV6TxOption39InfoType dhcpV6TxOpt39InfoIdx;
  TcpIp_IpV6SourceAddressIterType srcAddrIdx;

  /* ----- Implementation ----------------------------------------------- */
  srcAddrIdx = TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6(LocalAddrV6Idx);
  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(LocalAddrV6Idx);
  dhcpV6TxOpt39InfoIdx = TcpIp_GetDhcpV6TxOption39InfoIdxOfIpV6Ctrl(ipCtrlIdx);

  /* #10 Check if valid Dhcp Address Index has been passed */
  if (TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(ipCtrlIdx) == srcAddrIdx)
  {
    /* #20 Process request only if the address index is DHCPv6 configurable */
    if ((OptId == TCPIP_DHCPV6_OPT_ID_CLIENT_FQDN) && (TcpIp_IsDhcpV6TxOption39InfoUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE))  /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    {
      /* Process request only if Tx Option 39 Info is valid for the Controller index */
      TcpIp_SizeOfDhcpV6TxOption39Type txOption39_OptLen =
        TcpIp_GetDhcpV6TxOption39EndIdxOfIpV6Ctrl(ipCtrlIdx) - TcpIp_GetDhcpV6TxOption39StartIdxOfIpV6Ctrl(ipCtrlIdx);
      TcpIp_SizeOfDhcpV6TxOption39Type txOpt39Idx = TcpIp_GetDhcpV6TxOption39StartIdxOfIpV6Ctrl(ipCtrlIdx);

      retValue = E_OK;

      /* An old API for setting a host name was TcpIp_DhcpV6_SetHostName(). */
      if (OptLen == 0u)
      {
        /* #If user has given 0 option length, then clear the user option buffer */
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IpBase_Fill(TcpIp_GetAddrDhcpV6TxOption39(txOpt39Idx), 0, TcpIp_GetOptLenOfDhcpV6TxOption39Info(dhcpV6TxOpt39InfoIdx));
        TcpIp_SetOptLenOfDhcpV6TxOption39Info(dhcpV6TxOpt39InfoIdx, 0);
        TcpIp_SetMsgFlagsOfDhcpV6TxOption39Info(dhcpV6TxOpt39InfoIdx, 0);
      }
      else if (OptLen <= txOption39_OptLen)
      {
        /* #30 If the data provided by the user fits into the option buffer, Set tx option parameters */
        TcpIp_SetOptLenOfDhcpV6TxOption39Info(dhcpV6TxOpt39InfoIdx, OptLen);
        TcpIp_SetMsgFlagsOfDhcpV6TxOption39Info(dhcpV6TxOpt39InfoIdx, MsgTypes);
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IpBase_Copy(TcpIp_GetAddrDhcpV6TxOption39(txOpt39Idx), OptPtr, OptLen);
      }
      else
      {
        /* #40 If option length is invalid, DET error shall be triggered */
        errorId = TCPIP_DHCPV6_E_INV_PARAM;
        retValue = E_NOT_OK;
      }
    }
    else
    {
      TcpIp_DhcpUserOptionIterType dhcpUserOptionIdx;
      /* #50 Lookup the requested user option in the list of configured user option */
      dhcpUserOptionIdx = TcpIp_DhcpV6_VLookupUserOption(ipCtrlIdx, OptId);

      /* #60 If the requested user option is supported */
      if (dhcpUserOptionIdx < TcpIp_GetSizeOfDhcpUserOption())
      {
        TcpIp_DhcpUserOptionBufferIterType dhcpUserBufferIdx = TcpIp_GetDhcpUserOptionBufferStartIdxOfDhcpUserOption(dhcpUserOptionIdx);

        retValue = E_OK;

        /* Use critical section since buffer maybe overwritten by TcpIp_DhcpV6_VHandleRxUserOption */
        IPV6_BEGIN_CRITICAL_SECTION_DOPT();

        /* #70 If option is configured, proceed to handle the option */
        if (OptLen == 0u)
        {
          /* #80 If OptLen is 0, then clear the Dhcp User Option data length for this option */
          TcpIp_SetLengthOfDhcpUserOptionDyn(dhcpUserOptionIdx, (uint8) 0u);
        }
        else if (   (OptLen <= TcpIp_GetDhcpUserOptionBufferLengthOfDhcpUserOption(dhcpUserOptionIdx)) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
                 /* #90 User can only write TX option */
                 && (TcpIp_DhcpV6_VIsTxUserOption(dhcpUserOptionIdx) == TRUE))
        {
          /* #100 If OptLen fits into the buffer, then copy the complete data from user to the user option buffer */
          /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
          IpBase_Copy(TcpIp_GetAddrDhcpUserOptionBuffer(dhcpUserBufferIdx), OptPtr, OptLen);
          TcpIp_SetLengthOfDhcpUserOptionDyn(dhcpUserOptionIdx, (uint8) OptLen);
        }
        else
        {
          /* #110 If option length is invalid, DET error shall be triggered */
          errorId = TCPIP_DHCPV6_E_INV_PARAM;
          retValue = E_NOT_OK;
        }

        IPV6_END_CRITICAL_SECTION_DOPT();
      }
      else
      {
        /* #120 If requested user option is invalid, DET error shall be triggered */
        errorId = TCPIP_DHCPV6_E_INV_PARAM;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  if(errorId != TCPIP_DHCPV6_E_NO_ERROR)
  {
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
    (void)Det_ReportError(TCPIP_DHCPV6_MODULE_ID, TCPIP_DHCPV6_VINSTANCE_ID, TCPIP_DHCPV6_API_ID_SET_TX_OPT, errorId);
#endif
  }

  return retValue;
} /* End of TcpIp_DhcpV6_VSetTxOption() */ /* PRQA S 6050, 6080 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STMIF */
#endif


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_InitMemory(void)
{
  TcpIp_IpV6CtrlIterType ipCtrlIdx;

  /* #10 Initialize dhcp memory and states */
  for (ipCtrlIdx = 0; ipCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl(); ipCtrlIdx++)
  {
    if (TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE)
    {
      TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(ipCtrlIdx);

      TcpIp_SetStateOfDhcpV6Data(dhcpV6DataIdx, TCPIP_DHCPV6_STATE_UNINIT);
      TcpIp_SetLastStateOfDhcpV6Data(dhcpV6DataIdx, TCPIP_DHCPV6_STATE_UNINIT);
    }
  }
} /* End of TcpIp_DhcpV6_InitMemory() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_Init(
    P2CONST(TcpIp_DhcpV6_ConfigType, TCPIP_PBCFG, TCPIP_CONST) CfgPtr)
{
  TcpIp_IpV6CtrlIterType ipCtrlIdx;

  IPV6_UNUSED_PARAMETER(CfgPtr);  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  TCPIP_DHCPV6_TIME_SET(TcpIp_DhcpV6_Time, 0u, 0u);

  /* #10 Reset dhcp for all controllers */
  for (ipCtrlIdx = 0; ipCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl(); ipCtrlIdx++)
  {
    if (TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE)
    {
      TcpIp_DhcpV6_Reset(ipCtrlIdx);
    }
  }

} /* End of TcpIp_DhcpV6_Init() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCalcElapsedTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VCalcElapsedTime(
    TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx)
{
  TcpIp_ElapsedTimeMsOfDhcpV6DataType dhcpElapsedTimeMs = TcpIp_GetElapsedTimeMsOfDhcpV6Data(DhcpV6DataIdx);

  /* #10 Calculate elapsed time */
  if (0xFFFFFFFFU > dhcpElapsedTimeMs)
  {
    if ((0xFFFFFFFFU - dhcpElapsedTimeMs) > TCPIP_MAIN_FCT_PERIOD_MSEC)
    {
      TcpIp_SetElapsedTimeMsOfDhcpV6Data(DhcpV6DataIdx, dhcpElapsedTimeMs + TCPIP_MAIN_FCT_PERIOD_MSEC);
    }
    else
    {
      TcpIp_SetElapsedTimeMsOfDhcpV6Data(DhcpV6DataIdx, 0xFFFFFFFFU);
    }
  }
  else
  {
    /* do nothing */
  }
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTxPendingMessages()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VTxPendingMessages(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx)
{
  TCPIP_ASSERT(DhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Check for dhcpv6 messages pending transmission */
  if (TRUE == TcpIp_GetMsgOfDhcpV6Data(DhcpV6DataIdx).TxPending)
  {
    if (1u == TcpIp_GetAddrRetransParamsOfDhcpV6Data(DhcpV6DataIdx)->TxCount)
    {
      TcpIp_SetElapsedTimeMsOfDhcpV6Data(DhcpV6DataIdx, 0);
    }

    /* #20 Invoke transmit api to transmit pending message */
    if (E_OK == TcpIp_DhcpV6_VTxMessage(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(DhcpV6DataIdx)))
    {
      /* #30 set pending flag to false if transmit successful */
      TcpIp_GetAddrMsgOfDhcpV6Data(DhcpV6DataIdx)->TxPending = FALSE;
    }
  }
  else
  {
    /* Do nothing */
  }
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateRenewMessage()
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
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateRenewMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx)
{
  TCPIP_ASSERT(DhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Check if timeout for maximum retransmission has been reached */
  if (E_OK == TcpIp_DhcpV6_VCalcTimeout(IpCtrlIdx, TcpIp_GetAddrIdleTimeOfDhcpV6Data(DhcpV6DataIdx), FALSE))
  {
    /* #20 transmit/retransmit renew message if timeout not reached */
    TcpIp_DhcpV6_VTriggerTx(TcpIp_GetAddrMsgOfDhcpV6Data(DhcpV6DataIdx));
  }
  else
  {
    /* #30 If timeout expired and reply has been received to renew message,
     * switch to sending rebind messages */
    if (E_OK == TcpIp_DhcpV6_VBuildRebind(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(DhcpV6DataIdx)))
    {
      TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, REB);

      /* #40 Send rebind messages until valid lifetime expires */
      TCPIP_DHCPV6_TIME_SET(TcpIp_GetAddrRetransParamsOfDhcpV6Data(DhcpV6DataIdx)->AbsRetransTimeout,
        TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(DhcpV6DataIdx)->AddrLease.ValidUntil, 0u);

      TCPIP_DHCPV6_CHANGE_STATE(DhcpV6DataIdx, TX_REB);
    }
    else
    {
      TCPIP_DHCPV6_CHANGE_STATE(DhcpV6DataIdx, FAIL);
    }
  }
} /* TcpIp_DhcpV6_VHandleStateRenewMessage() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateSolicitMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateSolicitMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx)
{
  TCPIP_ASSERT(DhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 If valid advertisement received, build and send dhcpv6 request */
  if (TRUE == TcpIp_GetAddrAdvInfoOfDhcpV6Data(DhcpV6DataIdx)->Valid)
  {
    (void)TcpIp_DhcpV6_VBuildRequest(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(DhcpV6DataIdx));
    TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, REQ);
    TCPIP_DHCPV6_CHANGE_STATE(DhcpV6DataIdx, TX_REQ);
  }
  /* #20 Retransmit SOLICIT message if number of retransmits has not been reached yet */
  else if (E_OK == TcpIp_DhcpV6_VCalcTimeout(IpCtrlIdx, TcpIp_GetAddrIdleTimeOfDhcpV6Data(DhcpV6DataIdx), TRUE))
  {
    /* (re)transmit solicit message */
    TcpIp_DhcpV6_VTriggerTx(TcpIp_GetAddrMsgOfDhcpV6Data(DhcpV6DataIdx));
  }
  else
  {
    TCPIP_DHCPV6_CHANGE_STATE(DhcpV6DataIdx, FAIL);
  }
} /* TcpIp_DhcpV6_VHandleStateSolicitMessage() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateReqDecRebMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateReqDecRebMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx)
{
  TCPIP_ASSERT(DhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  if (E_OK == TcpIp_DhcpV6_VCalcTimeout(IpCtrlIdx, TcpIp_GetAddrIdleTimeOfDhcpV6Data(DhcpV6DataIdx), FALSE))
  {
    /* #10 Retransmit rebind message if maximum retransmissions not done */
    TcpIp_DhcpV6_VTriggerTx(TcpIp_GetAddrMsgOfDhcpV6Data(DhcpV6DataIdx));
  }
  else
  {
    /* #20 Restart dhcpv6 address assignment if maximum retries reached */
    TcpIp_DhcpV6_StartAddressAssignment(IpCtrlIdx);

    TCPIP_DHCPV6_CHANGE_STATE(DhcpV6DataIdx, FAIL);

  }
} /* TcpIp_DhcpV6_VHandleStateReqDecRebMessage() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateReleaseMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateReleaseMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx)
{
  TCPIP_ASSERT(DhcpV6DataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  if (E_OK == TcpIp_DhcpV6_VCalcTimeout(IpCtrlIdx, TcpIp_GetAddrIdleTimeOfDhcpV6Data(DhcpV6DataIdx), FALSE))
  {
    /* #10 Retransmit release message if maximum retransmissions not done */
    TcpIp_DhcpV6_VTriggerTx(TcpIp_GetAddrMsgOfDhcpV6Data(DhcpV6DataIdx));
  }
  else
  {
    /* #20 Change dhcpv6 state to fail if maximum retransmissions reached */
    TCPIP_DHCPV6_CHANGE_STATE(DhcpV6DataIdx, FAIL);
  }
}
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_MainFunction
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
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_MainFunction(void)
{
  /* #10 Iterate over all IPv6 controllers that have a local address with DHCPv6 address assignment method */
  TcpIp_IpV6CtrlIterType ipCtrlIdx;

  for (ipCtrlIdx = 0; ipCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl(); ipCtrlIdx++)
  {
    TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(ipCtrlIdx);

    /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    if ((TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE) && TCPIP_DHCPV6_IS_INITIALIZED(dhcpV6DataIdx))
    {
      TCPIP_DHCPV6_TIME_ADD_MS(TcpIp_DhcpV6_Time, TCPIP_MAIN_FCT_PERIOD_MSEC);

      /* #20 Calculate elapsed time since start of DHCPv6 address assignment */
      TcpIp_DhcpV6_VCalcElapsedTime(dhcpV6DataIdx);

      /* #30 Transmit pending DHCPv6 message */
      TcpIp_DhcpV6_VTxPendingMessages(ipCtrlIdx, dhcpV6DataIdx);

      /* #40 Check if action is required for the DCHPv6 instance depending on current state: */
      if (TCPIP_DHCPV6_TIME_EXPIRED(TcpIp_GetIdleTimeOfDhcpV6Data(dhcpV6DataIdx)) == TRUE)
      {
        switch (TcpIp_GetStateOfDhcpV6Data(dhcpV6DataIdx))
        {
        case TCPIP_DHCPV6_STATE_TX_REN: /* Renew */
          /* #50 [RENEW] Send RENEW message or switch to REBIND if number of retransmissions has been reached */
          TcpIp_DhcpV6_VHandleStateRenewMessage(ipCtrlIdx, dhcpV6DataIdx);
          break;

        case TCPIP_DHCPV6_STATE_TX_SOL: /* Solicit */
          /* #60 [SOLICIT] Move to state REQUEST if valid ADVERTISE message has been received from DHCPv6 server
           *     else retransmit SOLICIT message if number of retransmits has not been reached yet */
          TcpIp_DhcpV6_VHandleStateSolicitMessage(ipCtrlIdx, dhcpV6DataIdx);
          break;

        case TCPIP_DHCPV6_STATE_TX_CNF: /* Confirm */
          /* #70 [CONFIRM] (Re-)Transmit CONFIRM message */
          if (E_OK == TcpIp_DhcpV6_VCalcTimeout(ipCtrlIdx, TcpIp_GetAddrIdleTimeOfDhcpV6Data(dhcpV6DataIdx), FALSE))
          {
            /* (re)transmit message */
            TcpIp_DhcpV6_VTriggerTx(TcpIp_GetAddrMsgOfDhcpV6Data(dhcpV6DataIdx));
          }
          else
          {
            TCPIP_DHCPV6_CHANGE_STATE(dhcpV6DataIdx, FAIL);
          }
          break;

        case TCPIP_DHCPV6_STATE_TX_REQ: /* Request */
        case TCPIP_DHCPV6_STATE_TX_DEC: /* Decline */
        case TCPIP_DHCPV6_STATE_TX_REB: /* Rebind */
          /* #80 [REQUEST,DECLINE,REBIND] (Re-)Transmit message or restart DHCPv6 address assignment if
           * number of retransmissions has been reached */
          TcpIp_DhcpV6_VHandleStateReqDecRebMessage(ipCtrlIdx, dhcpV6DataIdx);
          break;

        case TCPIP_DHCPV6_STATE_TX_REL: /* Release */
          /* #90 [RELEASE] (Re-)Transmit Release message */
          TcpIp_DhcpV6_VHandleStateReleaseMessage(ipCtrlIdx, dhcpV6DataIdx);

          break;

        case TCPIP_DHCPV6_STATE_BOUND: /* Bound */
          /* #100 [BOUND] Schedule idle time until first Renew message must be sent and switch to state RENEW */
          (void)TcpIp_DhcpV6_VBuildRenew(ipCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpV6DataIdx));
          TCPIP_DHCPV6_INIT_RETRANS_PARAMS(ipCtrlIdx, REN);

          /* send renew messages until T2 is reached */
          TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->AbsRetransTimeout.S =
            TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpV6DataIdx)->T2Timeout;
          TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpV6DataIdx)->AbsRetransTimeout.Ms = 0;

          TCPIP_DHCPV6_CHANGE_STATE(dhcpV6DataIdx, TX_REN);
          break;

        default:
             /**/
          break;
        }
      }
      else
      {
        /* do nothing else until idle time has expired. e.g. message rx timeout has expired. */
      }
    }
  }
} /* End of TcpIp_DhcpV6_MainFunction() */ /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxHandleStateMsgAdv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRxHandleStateMsgAdv(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType                 DhcpV6DataIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen)
{
  uint16 PayloadPos = TCPIP_DHCPV6_MSG_HDR_LEN;
  TcpIp_SizeOfDhcpV6ConfigType dhcpV6ConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpV6ConfigIdx < TcpIp_GetSizeOfDhcpV6Config()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 If dhcpv6 is in solicit state, process packet and update state */
  if (   (TCPIP_DHCPV6_STATE_TX_SOL == TcpIp_GetStateOfDhcpV6Data(DhcpV6DataIdx))  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
      && (E_OK == TcpIp_DhcpV6_VRxAdvertise(IpCtrlIdx, &DataPtr[PayloadPos], (DataLen - PayloadPos))))
  {
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
    CANOE_WRITE_STRING0("TcpIp_DhcpV6_RxIndication() RxAdvertise");
#endif

    if (TcpIp_IsUseFirstValidAdvOfDhcpV6Config(dhcpV6ConfigIdx) == TRUE)
    {
      TCPIP_DHCPV6_SET_IDLE_TIME_ZERO(DhcpV6DataIdx);
    }
    else if (   (TCPIP_DHCPV6_MAX_PREFERENCE == TcpIp_GetAddrAdvInfoOfDhcpV6Data(DhcpV6DataIdx)->Preference)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
             || (1u < TcpIp_GetAddrRetransParamsOfDhcpV6Data(DhcpV6DataIdx)->TxCount))
    {
      /* #20 If valid advertisement with maximum preference received, move dhcpv6 state to request */
      TCPIP_DHCPV6_SET_IDLE_TIME_ZERO(DhcpV6DataIdx);
    }
    else
    {
      /* #30 If not advertisement with maximum preference, wait for more advertisements */
    }
  }
  else
  {
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
    CANOE_WRITE_STRING0("TcpIp_DhcpV6_RxIndication() RxAdvertise in WRONG STATE");
#endif
  }
} /* TcpIp_DhcpV6_VRxHandleStateMsgAdv() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxProcessMessage()
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
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRxProcessMessage(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  uint8                                      MsgType,
  TcpIp_SizeOfDhcpV6DataType                 DhcpV6DataIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen)
{
  uint16 PayloadPos = TCPIP_DHCPV6_MSG_HDR_LEN;
  TcpIp_SocketOwnerConfigIterType socketOwnerCfgIdx;

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Process the received dhcpv6 message based on the type */
  switch (MsgType)
  {
  case TCPIP_DHCPV6_MSG_ADV:
    /* #20 Process dhcpv6 advertisements if dhcpv6 is in solicit state */
    TcpIp_DhcpV6_VRxHandleStateMsgAdv(IpCtrlIdx, DhcpV6DataIdx, DataPtr, DataLen);
    break;

  case TCPIP_DHCPV6_MSG_REP:
    /* #30 Process dhcpv6 replies only if dhcpv6 is valid */
    if (   (TCPIP_DHCPV6_STATE_TX_SOL <= TcpIp_GetStateOfDhcpV6Data(DhcpV6DataIdx)) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TCPIP_DHCPV6_STATE_TX_REL >= TcpIp_GetStateOfDhcpV6Data(DhcpV6DataIdx)))
    {
      TcpIp_DhcpV6_VRxReply(IpCtrlIdx, &DataPtr[PayloadPos], (DataLen - PayloadPos));
    }
    break;

  case TCPIP_DHCPV6_MSG_REC:
    /* #40 Process dhcpv6 reconfiguration requests - not implemented yet */
    break;

  default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    /* Default case left blank intentionally */
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
      CANOE_WRITE_STRING1("Unkown Message Type: %d", MsgType);
#endif
      break;
  }
  /* #50 If options have been validated, traverse through the socket owners and invoke Dhcp Event callout if present */
  for (socketOwnerCfgIdx = 0; socketOwnerCfgIdx < TcpIp_GetSizeOfSocketOwnerConfig(); socketOwnerCfgIdx++)
  {
    if (TcpIp_GetDhcpEventFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx) != NULL_PTR)
    {
      TcpIp_LocalAddrIdType localAddrId = TCPIP_LOCAL_ADDR_IDX_TO_ID(TCPIP_IPV6_TO_LOCAL_ADDR_IDX(TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(IpCtrlIdx))));
      TcpIp_DhcpEventType dhcpEvent = TcpIp_DhcpV6_VGetEventType(MsgType);

      if (dhcpEvent != TCPIP_DHCP_EVENT_INVALID)
      {
        TcpIp_GetDhcpEventFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx)(localAddrId, dhcpEvent);
      }
    }
  }
} /* TcpIp_DhcpV6_VRxProcessMessage() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_RxIndication
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
FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_RxIndication(
  TcpIp_IpV6CtrlIterType        IpCtrlIdx,
  TCPIP_P2C(uint8)              DataPtr,
  uint16                        DataLen,
  boolean                       ChecksumCalculated,
  TCPIP_P2C(IpBase_AddrIn6Type) SourcePtr,
  TCPIP_P2C(IpBase_AddrIn6Type) DestinationPtr)
{
  Std_ReturnType result = E_OK;
  uint32 TransId, dhcpV6CurrTransId;
  uint8 MsgType;
  TcpIp_SizeOfDhcpV6DataType dhcpV6DataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(DataPtr   != NULL_PTR);
  TCPIP_ASSERT(SourcePtr != NULL_PTR);

  /* #10 Check if dhcp is enabled for the controller */
  if (   (TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == FALSE) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (!TCPIP_DHCPV6_IS_INITIALIZED(dhcpV6DataIdx)))
  {
    result = E_NOT_OK;
  }
  /* #20 Check if packet has minimum required length. */
  else if (DataLen < sizeof(TcpIp_Udp_HdrType))
  {
    result = E_NOT_OK;
  }
  else if (TCPIP_GET_UINT16(DataPtr, UDP_HDR_OFF_LENBYTE) > DataLen)
  {
    result = E_NOT_OK;
  }
  /* #30 Check if the source and destination ports in the udp header is valid */
  else if (   (TCPIP_GET_UINT16(DataPtr, UDP_HDR_OFF_SRCPORT) != TCPIP_DHCPV6_SERVER_PORT)
           || (TCPIP_GET_UINT16(DataPtr, UDP_HDR_OFF_TGTPORT) != TCPIP_DHCPV6_CLIENT_PORT))
  {
    result = E_NOT_OK;
  }
  /* #40 Validate the checksum of the received packet */
  else if (ChecksumCalculated == FALSE)
  {
    uint32 checksumTmp = TcpIp_VCalcIpV6PseudoHdrChecksum(SourcePtr, DestinationPtr, TCPIP_SOCK_PROT_UDP, DataLen);

    checksumTmp = IpBase_TcpIpChecksumAdd(DataPtr, DataLen, checksumTmp, TRUE);

    if (checksumTmp != 0u)
    {
      result = E_NOT_OK;
    }
  }
  else
  {
    /* no error */
  }

  if (result == E_OK)
  {
    /* skip UDP header */
    uint16            localDataLen = TCPIP_GET_UINT16(DataPtr, UDP_HDR_OFF_LENBYTE) - (uint16) sizeof(TcpIp_Udp_HdrType);
    TCPIP_P2C(uint8)  localDataPtr = &DataPtr[sizeof(TcpIp_Udp_HdrType)];

    MsgType = localDataPtr[0];
    TransId = ((uint32)localDataPtr[1] << 16) | ((uint32)localDataPtr[2] << 8) | ((uint32)localDataPtr[3]);

    dhcpV6CurrTransId = TcpIp_GetCurrentTransIdOfDhcpV6Data(dhcpV6DataIdx);
    /* #50 Check if dhcpv6 message received with valid transaction Id */
    if (TransId != dhcpV6CurrTransId)
    {
      /* drop message with unexpected transaction id */
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
      CANOE_WRITE_STRING2("TcpIp_DhcpV6_RxIndication() discarding message. Expected transaction id %d but received %d.",
        TcpIp_DhcpV6_CurrentTransId, TransId);
#endif
    }
    else
    {
      /* #60 Invoke function to process the validated dhcpv6 message */
      TcpIp_DhcpV6_VRxProcessMessage(IpCtrlIdx, MsgType, dhcpV6DataIdx, localDataPtr, localDataLen);
    }
  }

} /* End of TcpIp_DhcpV6_RxIndication() */ /* PRQA S 6060, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# endif /* (TCPIP_SUPPORT_DHCPV6 == STD_ON) */
#endif  /* (TCPIP_SUPPORT_IPV6 == STD_ON) */


/*
   MICROSAR global MISRA deviations:
   - see file 'WI_MISRA_Compliance_MSR.pdf'

   module specific MISRA deviations:

   MD_DHCPV6_Rule20.11_0881: There shall be at most one occurrence of the # or ## preprocessor operators in a single macro definition.
     Reason:     Multiple ## prepocessor operator is used to For efficient code.
     Risk:       Order of evaluation of the operator may be incorrect
     Prevention: Review of code wherever multiple glue operators are used

*/


/**********************************************************************************************************************
 *  END OF FILE: TcpIp_DhcpV6.c
 *********************************************************************************************************************/
