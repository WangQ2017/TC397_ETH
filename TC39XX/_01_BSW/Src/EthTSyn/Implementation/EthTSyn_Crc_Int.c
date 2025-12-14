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
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthTSyn_Crc_Int.c
 *        \brief  EthTSyn Crc source file - Internal Functions
 *      \details  EthTSyn Crc source file containing the EthTSyn Crc implementation of the EthTSyn module.
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

#define ETHTSYN_CRC_INT_SOURCE

/**********************************************************************************************************************
*  INCLUDES
*********************************************************************************************************************/
#include "EthTSyn_Crc_Int.h"

#if (ETHTSYN_CRC_SUPPORT == STD_ON)
# include "EthTSyn_Int.h" /* PRQA S 3219, 0883 */ /* MD_EthTSyn_3219, MD_EthTSyn_0883 */
# include "Crc.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthTSyn header file */
# if (  (ETHTSYN_SW_MAJOR_VERSION != (13u)) \
     || (ETHTSYN_SW_MINOR_VERSION != (2u)) \
     || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
#  error "Vendor specific version numbers of EthTSyn_Crc_Int.c and EthTSyn.h are inconsistent"
# endif

/* Check the version of the configuration header file */
# if (  (ETHTSYN_CFG_MAJOR_VERSION != (13u)) \
     || (ETHTSYN_CFG_MINOR_VERSION != (2u)) )
#  error "Version numbers of EthTSyn_Crc_Int.c and EthTSyn_Cfg.h are inconsistent!"
# endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# define ETHTSYN_CRC_FLAGS_MSG_LENGTH_MASK                            (0x01u)

# define ETHTSYN_CRC_FLAGS_DOMAIN_NUMBER_MASK                         (0x02u)

# define ETHTSYN_CRC_FLAGS_CORRECTION_FIELD_MASK                      (0x04u)

# define ETHTSYN_CRC_FLAGS_SRC_PORT_IDENTITY_MASK                     (0x08u)

# define ETHTSYN_CRC_FLAGS_SEQUENCE_ID_MASK                           (0x10u)

# define ETHTSYN_CRC_FLAGS_PRECISE_ORIGIN_TS_MASK                     (0x20u)

/* Size of the Crc Data for the different Sub-Tlvs including the DataId in byte. */
# define ETHTSYN_CRC_STATUS_CRC_DATA_SIZE                             (2u)
# define ETHTSYN_CRC_USER_DATA_CRC_DATA_SIZE                          (5u)
# define ETHTSYN_CRC_OFS_CRC_DATA_SIZE                                (17u)

 /* CRC_TIME_0 Max Size: TimeFlages (1) + DomainNumber (1) + SrcPortIdentity (10) + PreciseOriginTimestamp (10) +
 *                      DataId (1) = 22 */
# define ETHTSYN_CRC_TIME_0_MAX_DATA_SIZE                             (23u)
 /* CRC_TIME_1 Max Size: TimeFlages (1) + MsgLength (2) + CorrectionField (8) + SequenceId (2) + DataId (1) = 13 */
# define ETHTSYN_CRC_TIME_1_MAX_DATA_SIZE                             (14u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETHTSYN_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateTimeCrc
 *********************************************************************************************************************/
 /*! \brief      Validates the Crc (CRC_TIME_0 + CRC_TIME_1) for a TimeSecured FollowUp.
  *  \details    Computes the expected CrcTime0 and CrcTime1 of the provided TimeSecured Sub-Tlv and validates the Crc
  *              values carried in the Sub-Tlv itself.
 *   \param[in]  DataId             The DataId for the FollowUp
 *   \param[in]  RxBufPtr           Pointer to the Ethernet reception buffer of the received FollowUp message
 *   \param[in]  TimeSecuredTlvOfs  Offset of the Time Secured Sub-Tlv within the FollowUp message
 *   \return     TRUE - Crc is valid
 *   \return     False - Crc is invalid
 *   \pre        -
 *   \context    TASK|ISR2
 *   \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateTimeCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
                  uint32  TimeSecuredTlvOfs);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateStatusCrc
 *********************************************************************************************************************/
/*! \brief      Validates the Crc (CRC_Status) for a Status Secured FollowUp message.
 *  \details    Computes the expected Crc of the provided StatusSecured Sub-Tlv and validates the Crc value carried in
 *              the Sub-Tlv itself.
 *  \param[in]  DataId               The DataId for the FollowUp
 *  \param[in]  RxBufPtr             Pointer to the Ethernet reception buffer of the received FollowUp message
 *  \param[in]  StatusSecuredTlvOfs  Offset of the Status Secured Sub-Tlv within the FollowUp message
 *  \pre        -
 *  \return     TRUE - Crc is valid
 *  \return     False - Crc is invalid
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateStatusCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
                  uint32  StatusSecuredTlvOfs);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateUserDataCrc
 *********************************************************************************************************************/
/*! \brief      Validates the Crc (CRC_UserData) for a UserData Secured FollowUp message.
 *  \details    Computes the expected Crc of the provided UserDataSecured Sub-Tlv and validates the Crc value carried in
 *              the Sub-Tlv itself.
 *  \param[in]  DataId                 The DataId for the FollowUp
 *  \param[in]  RxBufPtr               Pointer to the Ethernet reception buffer of the received FollowUp message
 *  \param[in]  UserDataSecuredTlvOfs  Offset of the UserData Secured Sub-Tlv within the FollowUp message
 *  \pre        -
 *  \return     TRUE - Crc is valid
 *  \return     False - Crc is invalid
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateUserDataCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
                  uint32  UserDataSecuredTlvOfs);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateOfsCrc
 *********************************************************************************************************************/
/*! \brief      Validates the Crc (CRC_OFS) for a Ofs Secured FollowUp message.
 *  \details    Computes the expected Crc of the provided OfsSecured Sub-Tlv and validates the Crc value carried in
 *              the Sub-Tlv itself.
 *  \param[in]  DataId            The DataId for the FollowUp
 *  \param[in]  RxBufPtr          Pointer to the Ethernet reception buffer of the received FollowUp message
 *  \param[in]  OfsSecuredTlvOfs  Offset of the Ofs Secured Sub-Tlv within the FollowUp message
 *  \return     TRUE - Crc is valid
 *  \return     False - Crc is invalid
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateOfsCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
                  uint32  OfsSecuredTlvOfs);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateTimeCrc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateTimeCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
                  uint32  TimeSecuredTlvOfs)
{
  /* ----- Local Variables ---------------------------------------------- */
  const uint8 msgCrcTime0 =
    IpBase_GetUint8(RxBufPtr, (TimeSecuredTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_TIME_SECURED_CRC_0_OFS));                /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
  const uint8 msgCrcTime1 =
    IpBase_GetUint8(RxBufPtr, (TimeSecuredTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_TIME_SECURED_CRC_1_OFS));                /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
  const uint8 msgCrcTimeFlags =
    IpBase_GetUint8(RxBufPtr, (TimeSecuredTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_TIME_SECURED_FLAGS_OFS));                /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compute and validate the Crc Time0 and Time1 of the Time secured sub Tlv. */
  /* PRQA S 3415, 4304 5 */ /* MD_EthTSyn_3415_ReadOnly, MD_MSR_AutosarBoolean */
  return (boolean)(
    (msgCrcTime0 == EthTSyn_Crc_ComputeTime0Crc(DataId, msgCrcTimeFlags, RxBufPtr)) &&                                 /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD */
    (msgCrcTime1 == EthTSyn_Crc_ComputeTime1Crc(DataId, msgCrcTimeFlags, RxBufPtr))                                    /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD */
    );
} /* EthTSyn_Crc_ValidateTimeCrc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateStatusCrc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateStatusCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
                  uint32  StatusSecuredTlvOfs)
{
  /* ----- Local Variables ---------------------------------------------- */
  const uint8 msgCrc = IpBase_GetUint8(RxBufPtr, (StatusSecuredTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_STATUS_CRC_OFS));   /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compute and validate the Crc of the status secured sub Tlv. */
  return (boolean)(msgCrc == EthTSyn_Crc_ComputeStatusCrc(DataId, RxBufPtr, StatusSecuredTlvOfs)); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD */
} /* EthTSyn_Crc_ValidateStatusCrc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateUserDataCrc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateUserDataCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
                  uint32  UserDataSecuredTlvOfs)
{
  /* ----- Local Variables ---------------------------------------------- */
  const uint8 msgCrc =
    IpBase_GetUint8(RxBufPtr, (UserDataSecuredTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_CRC_OFS));                 /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compute and validate the Crc of the user data secured sub Tlv. */
  /* PRQA S 4304 1 */ /* MD_MSR_AutosarBoolean */
  return (boolean)(msgCrc == EthTSyn_Crc_ComputeUserDataCrc(DataId, RxBufPtr, UserDataSecuredTlvOfs));                 /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD */
} /* EthTSyn_Crc_ValidateUserDataCrc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateOfsCrc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateOfsCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
                  uint32  OfsSecuredTlvOfs)
{
  /* ----- Local Variables ---------------------------------------------- */
  const uint8 msgCrc = IpBase_GetUint8(RxBufPtr, (OfsSecuredTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_CRC_OFS));         /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compute and validate the Crc of the offset time domain (ofs) secured sub Tlv. */
  return (boolean)(msgCrc == EthTSyn_Crc_ComputeOfsCrc(DataId, RxBufPtr, OfsSecuredTlvOfs));  /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD */
} /* EthTSyn_Crc_ValidateOfsCrc() */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeTime0Crc
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
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeTime0Crc(
                  uint8   DataId,
                  uint8   Flags,
  ETHTSYN_P2CONST(uint8)  BufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 crcData[ETHTSYN_CRC_TIME_0_MAX_DATA_SIZE];
  uint32 crcDataLength = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add the Value of Flags to Crc data. */
  crcData[crcDataLength] = Flags;                                                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY */
  crcDataLength += 1u;

  /* #20 Add Domain Number to Crc data if applicable. */
  if ((Flags & ETHTSYN_CRC_FLAGS_DOMAIN_NUMBER_MASK) != 0u)
  {
    crcData[crcDataLength] = IpBase_GetUint8(BufPtr, ETHTSYN_MSG_HDR_DOMAIN_NUM_OFS);                                  /* SBSW_ETHTSYN_CRC_DATA_ARRAY */ /* SBSW_ETHTSYN_ETH_BUFFER_CRC_FWD */
    crcDataLength += 1u;
  }


  /* #30 Add Source Port Identity to Crc data if applicable. */
  if ((Flags & ETHTSYN_CRC_FLAGS_SRC_PORT_IDENTITY_MASK) != 0u)
  {
    /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
    VStdLib_MemCpy(&crcData[crcDataLength], &BufPtr[ETHTSYN_MSG_HDR_SRC_PORT_IDENT_CLOCK_IDENT_OFS],                   /* SBSW_ETHTSYN_ETH_BUFFER_OFS_CRC_DATA_CPY */
      ETHTSYN_MSG_HDR_SRC_PORT_IDENT_SIZE);
    crcDataLength += ETHTSYN_MSG_HDR_SRC_PORT_IDENT_SIZE;
  }

  /* #40 Add Precise Origin Timestamp to Crc data if applicable. */
  if ((Flags & ETHTSYN_CRC_FLAGS_PRECISE_ORIGIN_TS_MASK) != 0u)
  {
    VStdLib_MemCpy(&crcData[crcDataLength], &BufPtr[ETHTSYN_MSG_FUP_POT_SEC_HI_OFS], ETHTSYN_MSG_FUP_POT_SIZE); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_ETHTSYN_ETH_BUFFER_OFS_CRC_DATA_CPY */
    crcDataLength += ETHTSYN_MSG_FUP_POT_SIZE;
  }

  /* #50 Add DataId to Crc data. */
  crcData[crcDataLength] = DataId;                                                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY */
  crcDataLength += 1u;

  /* #60 Calculate and return the Crc value. */
  return Crc_CalculateCRC8H2F(crcData, crcDataLength, 0u, TRUE);                                                       /* SBSW_ETHTSYN_CRC_DATA_ARRAY_PASS */
} /* EthTSyn_Crc_ComputeTime0Crc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeTime1Crc
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
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeTime1Crc(
                  uint8   DataId,
                  uint8   Flags,
  ETHTSYN_P2CONST(uint8)  BufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 crcData[ETHTSYN_CRC_TIME_1_MAX_DATA_SIZE];
  uint32 crcDataLength = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add the Value of Flags to Crc data. */
  crcData[crcDataLength] = Flags;                                                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY */
  crcDataLength += 1u;

  /* #20 Add Message Length to Crc data if applicable. */
  if ((Flags & ETHTSYN_CRC_FLAGS_MSG_LENGTH_MASK) != 0u)
  {
    VStdLib_MemCpy(&crcData[crcDataLength], &BufPtr[ETHTSYN_MSG_HDR_MSG_LENGTH_OFS], ETHTSYN_MSG_HDR_MSG_LEN_SIZE); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_ETHTSYN_ETH_BUFFER_OFS_CRC_DATA_CPY */
    crcDataLength += ETHTSYN_MSG_HDR_MSG_LEN_SIZE;
  }

  /* #30 Add Correction field to Crc data if applicable. */
  if ((Flags & ETHTSYN_CRC_FLAGS_CORRECTION_FIELD_MASK) != 0u)
  {
    VStdLib_MemCpy(&crcData[crcDataLength], &BufPtr[ETHTSYN_MSG_HDR_CORR_FIELD_OFS], ETHTSYN_MSG_HDR_CORR_FIELD_SIZE); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_ETHTSYN_ETH_BUFFER_OFS_CRC_DATA_CPY */
    crcDataLength += ETHTSYN_MSG_HDR_CORR_FIELD_SIZE;
  }

  /* #40 Add Sequence Id to Crc data if applicable. */
  if ((Flags & ETHTSYN_CRC_FLAGS_SEQUENCE_ID_MASK) != 0u)
  {
    VStdLib_MemCpy(&crcData[crcDataLength], &BufPtr[ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS], ETHTSYN_MSG_HDR_SEQUENCE_ID_SIZE); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_ETHTSYN_ETH_BUFFER_OFS_CRC_DATA_CPY */
    crcDataLength += ETHTSYN_MSG_HDR_SEQUENCE_ID_SIZE;
  }

  /* #50 Add DataId to Crc data. */
  crcData[crcDataLength] = DataId;                                                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY */
  crcDataLength += 1u;

  /* #60 Calculate and return the Crc value. */
  return Crc_CalculateCRC8H2F(crcData, crcDataLength, 0, TRUE);                                                        /* SBSW_ETHTSYN_CRC_DATA_ARRAY_PASS */
} /* EthTSyn_Crc_ComputeTime1Crc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeStatusCrc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeStatusCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  BufPtr,
                  uint32  StatusSecuredTlvOfs)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 crcData[ETHTSYN_CRC_STATUS_CRC_DATA_SIZE];
  uint8 crcDataLength = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add Status to Crc data. */
  crcData[crcDataLength] =
    IpBase_GetUint8(BufPtr, (StatusSecuredTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_STATUS_STATUS_OFS));                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY */ /* SBSW_ETHTSYN_ETH_BUFFER_CRC_FWD */
  crcDataLength += 1u;

  /* #20 Add DataId to Crc data. */
  crcData[crcDataLength] = DataId;                                                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY */
  crcDataLength += 1u;

  /* #30 Calculate and return the Crc value. */
  return Crc_CalculateCRC8H2F(crcData, crcDataLength, 0, TRUE);                                                        /* SBSW_ETHTSYN_CRC_DATA_ARRAY_PASS */
} /* EthTSyn_Crc_ComputeStatusCrc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeUserDataCrc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeUserDataCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  BufPtr,
                  uint32  UserDataSecuredTlvOfs)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 crcData[ETHTSYN_CRC_USER_DATA_CRC_DATA_SIZE];
  uint8 crcDataLength = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add UserData to Crc data. */
  /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
  VStdLib_MemCpy(&crcData[crcDataLength],                                                                              /* SBSW_ETHTSYN_ETH_BUFFER_OFS_CRC_DATA_CPY */
    &BufPtr[UserDataSecuredTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_UD_LEN_OFS],
    ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_CRC_DATA_SIZE);
  crcDataLength += ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_CRC_DATA_SIZE;

  /* #20 Add DataId to Crc data. */
  crcData[crcDataLength] = DataId;                                                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY */
  crcDataLength += 1u;

  /* #30 Calculate and return the Crc value. */
  return Crc_CalculateCRC8H2F(crcData, crcDataLength, 0, TRUE);                                                        /* SBSW_ETHTSYN_CRC_DATA_ARRAY_PASS */
} /* EthTSyn_Crc_ComputeUserDataCrc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeOfsCrc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeOfsCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  BufPtr,
                  uint32  OfsSecuredTlvOfs)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 crcData[ETHTSYN_CRC_OFS_CRC_DATA_SIZE];
  uint8 crcDataLength = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy Ofs Secured Sub-Tlv data relevant for Crc calculation to Crc data.
         The relevant fields are: OfsTimeDomain, OfsTimeSec, OfsTimeNSec, Status, UserData. */
  /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
  VStdLib_MemCpy(&crcData[crcDataLength], &BufPtr[OfsSecuredTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_OFS_DOMAIN_NUM_OFS],   /* SBSW_ETHTSYN_ETH_BUFFER_OFS_CRC_DATA_CPY */
    ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_CRC_DATA_SIZE);
  crcDataLength += ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_CRC_DATA_SIZE;

  /* #20 Add DataId to Crc data. */
  crcData[crcDataLength] = DataId;                                                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY */
  crcDataLength += 1u;

  /* #30 Calculate and return the Crc value. */
  return Crc_CalculateCRC8H2F(crcData, crcDataLength, 0, TRUE);                                                        /* SBSW_ETHTSYN_CRC_DATA_ARRAY_PASS */
} /* EthTSyn_Crc_ComputeOfsCrc() */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateSubTlvCrc
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
FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateSubTlvCrc(
                  uint8   DataId,
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
                  uint32  ArSubTlvOfs)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean crcIsValid;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check Ar Sub Tlv type */
  /* The Ar Sub Tlv type is located ate ArSubTlvOfs + ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS.
   * ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS is there and therefore can be omitted. */
  switch (IpBase_GetUint8(RxBufPtr, ArSubTlvOfs))                                                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
  {
  case ETHTSYN_AR_SUB_TLV_TYPE_TIME_SECURED:
      {
        /* #100 Ar Sub Tlv type: Time Secured -> Validate Crc */
        crcIsValid = EthTSyn_Crc_ValidateTimeCrc(DataId, RxBufPtr, ArSubTlvOfs);                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
        break;
      }

  case ETHTSYN_AR_SUB_TLV_TYPE_OFS_SECURED:
    {
      /* #101 Ar Sub Tlv type: Ofs Secured -> Validate Crc */
      crcIsValid = EthTSyn_Crc_ValidateOfsCrc(DataId, RxBufPtr, ArSubTlvOfs);                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
      break;
    }

  case ETHTSYN_AR_SUB_TLV_TYPE_STATUS_SECURED:
    {
      /* #102 Ar Sub Tlv type: Status Secured -> Validate Crc */
      crcIsValid = EthTSyn_Crc_ValidateStatusCrc(DataId, RxBufPtr, ArSubTlvOfs);                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
      break;
    }

  case ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_SECURED:
    {
      /* #103 Ar Sub Tlv type: UserData Secured -> Validate Crc */
      crcIsValid = EthTSyn_Crc_ValidateUserDataCrc(DataId, RxBufPtr, ArSubTlvOfs);                                     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
      break;
    }

  default:
    {
      /* #104 Not secured or unknown Ar Sub Tlv type -> return with positive value */
      crcIsValid = TRUE;
      break;
    }

  }

  return crcIsValid;
} /* EthTSyn_Crc_ValidateSubTlvCrc() */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */

/* Justification for module-specific MISRA deviations:
* see file EthTSyn.c
*/

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Crc_Int.c
 *********************************************************************************************************************/
