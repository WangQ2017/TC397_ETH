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
/*!        \file  EthTSyn_Int.h
 *        \brief  EthTSyn internal header file
 *      \details  Contains internal definitions and declarations used by the EthTSyn only
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


#if !defined(ETHTSYN_INT_H)
# define ETHTSYN_INT_H

/* PRQA S 3219 EOF */ /* MD_MSR_Unreachable */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn.h"
# include "EthTSyn_Util_Int.h"
# include "SchM_EthTSyn.h"
# include "StbM.h"

# if ( (ETHTSYN_DEV_ERROR_REPORT == STD_ON) || (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) )
#  include "Det.h"
# endif /* ETHTSYN_DEV_ERROR_REPORT || ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION */

# include "IpBase.h"
# include "vstdlib.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ETHTSYN General */
# define ETHTSYN_SUPPORTED_PROTOCOL_VERSION                           (0x02u)
/* 10^9 nanoseconds per second */
# define ETHTSYN_NANOSECONDS_PER_SECOND                               (1000000000uL)

/* EthTSyn message offsets in bytes. */
# define ETHTSYN_MSG_HDR_LENGTH_FIELD_OFFSET                          (2u)

/* EthTSyn message header field lengths in byte */
# define ETHTSYN_MSG_HDR_MSG_LEN_SIZE                                 (2u)
# define ETHTSYN_MSG_HDR_SEQUENCE_ID_SIZE                             (2u)
# define ETHTSYN_MSG_HDR_SRC_PORT_IDENT_SIZE                          (10u)
# define ETHTSYN_MSG_HDR_CORR_FIELD_SIZE                              (8u)

# define ETHTSYN_HDR_COM_LENGTH                                       (34u)
# define ETHTSYN_HDR_COM_RESERVED_1_LENGTH                            (4u)
# define ETHTSYN_HDR_COM_CORRECTION_FIELD_LENGTH                      (8u)
# define ETHTSYN_HDR_COM_TRANSPORT_SPECIFIC                           (0x10u)
# define ETHTSYN_HDR_COM_CONTROL_SYNC                                 (0x00u)
# define ETHTSYN_HDR_COM_CONTROL_FOLLOW_UP                            (0x02u)
# define ETHTSYN_HDR_COM_CONTROL_ANNOUNCE                             (0x05u)
# define ETHTSYN_HDR_COM_CONTROL_PDELAY_REQ                           (0x05u)
# define ETHTSYN_HDR_COM_CONTROL_PDELAY_RESP                          (0x05u)
# define ETHTSYN_HDR_COM_CONTROL_PDELAY_RESP_FOLLOW_UP                (0x05u)

# define ETHTSYN_HDR_COM_LOG_MESSAGE_INTERVAL_DEFAULT                 (0x7F)

/* EthTSyn FollowUp message field lengths in byte. */
# define ETHTSYN_MSG_FUP_POT_SIZE                                     (10u)

/* EthTSyn FollowUp Ofs Sub-Tlv field lengths in byte. */
/* Total size of the Sub-Tlv fields used for Crc calculation. */
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_CRC_DATA_SIZE                 (16u)

/* EthTSyn FollowUp UserData Sub-Tlv field lenghts in byte. */
/* Total size of the Sub-Tlv fields used for Crc calculation. */
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_CRC_DATA_SIZE           (4u)

/* ETHTSYN Header Flags */
/*
 * Default value 'FALSE'==0
                     +
     Octet 0         |Octet 1
     +-------------------------------+  +----------------------------------------------------+
     |7|6|5|4|3|2|1|0|7|6|5|4|3|2|1|0|  |Flag name              |Used in message
  +----------------------------------+  +----------------------------------------------------+
  O  |7|                                |reserved               |
  c  +---------------------------------------------------------------------------------------+
  t    |6|                              |reserved               |
  e    +-------------------------------------------------------------------------------------+
  t      |5|                            |reserved               |
         +-----------------------------------------------------------------------------------+
  0        |4|                          |reserved               |
           +---------------------------------------------------------------------------------+
             |3|                        |reserved               |
             +-------------------------------------------------------------------------------+
               |2|                      |reserved               |
               +-----------------------------------------------------------------------------+
                 |1|                    |twoStepFlag            |Sync, Pdelay_Req
                 +---------------------------------------------------------------------------+
                   |0|                  |reserved               |
  +------------------------------------------------------------------------------------------+
  O                  |7|                |reserved               |
  c                  +-----------------------------------------------------------------------+
  t                    |6|              |reserved               |
  e                    +---------------------------------------------------------------------+
  t                      |5|            |frequencyTraceable     |Announce
                         +-------------------------------------------------------------------+
  1                        |4|          |timeTraceable          |Announce
                           +-----------------------------------------------------------------+
                             |3|        |ptpTimescale           |All
                             +---------------------------------------------------------------+
                               |2|      |currentUtsOffsetValid  |Announce
                               +-------------------------------------------------------------+
                                 |1|    |leap59                 |Announce
                                 +-----------------------------------------------------------+
                                   |0|  |leap61                 |Announce
  +------------------------------------------------------------------------------------------+
 */
# define ETHTSYN_FLAGS_OCTET_0_TWO_STEP                               (0x02u)
# define ETHTSYN_FLAGS_OCTET_1_LEAP61                                 (0x01u)
# define ETHTSYN_FLAGS_OCTET_1_LEAP59                                 (0x02u)
# define ETHTSYN_FLAGS_OCTET_1_UTC_OFFSET_VALID                       (0x04u)
# define ETHTSYN_FLAGS_OCTET_1_ETHTSYN_TIMESCALE                      (0x08u)
# define ETHTSYN_FLAGS_OCTET_1_TIME_TRACEABLE                         (0x10u)
# define ETHTSYN_FLAGS_OCTET_1_FREQUENCY_TRACEABLE                    (0x20u)

# define ETHTSYN_HDR_COM_MSG_TYPE(param)                              ((uint8)(param) & 0x0Fu)
# define ETHTSYN_HDR_COM_VERSION(param)                               ((uint8)(param) & 0x0Fu)

/* Message Pdelay values */
# define ETHTSYN_MSG_P_DELAY_PAYLOAD_LENGTH                           (20u)

/* Message PdelayReq values */
# define ETHTSYN_MSG_P_DELAY_REQ_LENGTH                               (ETHTSYN_MSG_P_DELAY_PAYLOAD_LENGTH \
                                                                      + ETHTSYN_HDR_COM_LENGTH)
# define ETHTSYN_MSG_P_DELAY_REQ_RESERVED_0_LENGTH                    (10u)
# define ETHTSYN_MSG_P_DELAY_REQ_RESERVED_1_LENGTH                    (10u)

/* Message PdelayResp values */
# define ETHTSYN_MSG_P_DELAY_RESP_LENGTH                              (ETHTSYN_MSG_P_DELAY_PAYLOAD_LENGTH \
                                                                      + ETHTSYN_HDR_COM_LENGTH)

/* Message PdelayRespFollowUp values */
# define ETHTSYN_MSG_P_DELAY_RESP_FOLLOW_UP_LENGTH                    (ETHTSYN_MSG_P_DELAY_PAYLOAD_LENGTH \
                                                                      + ETHTSYN_HDR_COM_LENGTH)

/* Message FollowUp values */
# define ETHTSYN_MSG_FOLLOW_UP_PAYLOAD_LENGTH                         (42u)
# define ETHTSYN_MSG_FOLLOW_UP_TX_LENGTH                              (ETHTSYN_MSG_FOLLOW_UP_PAYLOAD_LENGTH \
                                                                      + ETHTSYN_HDR_COM_LENGTH)
# define ETHTSYN_MSG_FOLLOW_UP_RX_MIN_LENGTH                          (ETHTSYN_MSG_FOLLOW_UP_PAYLOAD_LENGTH \
                                                                      + ETHTSYN_HDR_COM_LENGTH)
/* Precise Origin Timestamp length (10) + complete FollowUp IEEE Tlv length (32) */
# define ETHTSYN_FOLLOW_UP_AR_TLV_OFFSET                              (42u)
# define ETHTSYN_FOLLOW_UP_TLV_TYPE                                   (0x03u)
# define ETHTSYN_FOLLOW_UP_TLV_LENGTH_FIELD                           (28u)
# define ETHTSYN_FOLLOW_UP_ORGANISATION_ID                            (0x000080C2uL)
# define ETHTSYN_FOLLOW_UP_ORGANISATION_SUBTYPE                       (0x00000001uL)
# define ETHTSYN_MSG_FOLLOW_UP_PRECISE_ORIGIN_TS_SECONDS_LENGTH       (6u)
# define ETHTSYN_MSG_FOLLOW_UP_PRECISE_ORIGIN_TS_NANOSECONDS_LENGTH   (4u)
# define ETHTSYN_MSG_FOLLOW_UP_ORGANISATION_ID_LENGTH                 (3u)
# define ETHTSYN_MSG_FOLLOW_UP_ORGANISATION_SUB_TYPE_LENGTH           (3u)
# define ETHTSYN_MSG_FOLLOW_UP_LAST_GM_PHASE_CHANGE_LENGTH            (12u)
# define ETHTSYN_MSG_FOLLOW_UP_SCALED_LAST_GM_FREQ_CHANGE_LENGTH      (4u)
# define ETHTSYN_MSG_FOLLOW_UP_CORRECTION_FIELD_MULTIPLIER            (65536u)
# define ETHTSYN_MSG_FOLLOW_UP_CORRECTION_FIELD_SHIFT                 (16u)
# define ETHTSYN_MSG_FOLLOW_UP_CORRECTION_FIELD_LENGTH                (8u)

# define ETHTSYN_MSG_FOLLOW_UP_CORRECTION_FIELD_TO_NS(CorrectionField) ((uint64)((CorrectionField) >> 16u))
# define ETHTSYN_MSG_FOLLOW_UP_NS_TO_CORRECTION_FIELD(Nanoseconds)    ((uint64)((Nanoseconds) << 16u))

/* Message Sync values */
# define ETHTSYN_MSG_SYNC_PAYLOAD_LENGTH                              (10u)
# define ETHTSYN_MSG_SYNC_LENGTH                                      (ETHTSYN_MSG_SYNC_PAYLOAD_LENGTH \
                                                                      + ETHTSYN_HDR_COM_LENGTH)
# define ETHTSYN_MSG_SYNC_RESERVED_LENGTH                             (10u)

/* ETHTSYN Announce values */
# define ETHTSYN_MSG_ANNOUNCE_PAYLOAD_LENGTH                          (42u)
# define ETHTSYN_MSG_ANNOUNCE_LENGTH                                  (ETHTSYN_MSG_ANNOUNCE_PAYLOAD_LENGTH \
                                                                      + ETHTSYN_HDR_COM_LENGTH)
# define ETHTSYN_MSG_ANNOUNCE_PATH_SEQUENCE_ELEMENT_LENGTH            (8u)
# define ETHTSYN_ANNOUNCE_PRIORITY_1_NETWORK_INFRASTRUCTURE           (246u)
# define ETHTSYN_ANNOUNCE_PRIORITY_1_OTHER_SYSTEM                     (248u)
# define ETHTSYN_ANNOUNCE_PRIORITY_1_NOT_GM_CAPABLE                   (255u)

# define ETHTSYN_ANNOUNCE_PRIORITY_2_DEFAULT                          (248u)
# define ETHTSYN_ANNOUNCE_CLOCK_CLASS_UNKNOWN                         (248u)
# define ETHTSYN_ANNOUNCE_CLOCK_CLASS_NOT_GM_CAPABLE                  (255u)
# define ETHTSYN_ANNOUNCE_CLOCK_ACCURACY_UNKNOWN                      (254u)
# define ETHTSYN_ANNOUNCE_OFFSET_SCALED_LOG_UNKNOWN                   (0x4100u)
# define ETHTSYN_ANNOUNCE_TIME_SOURCE_INTERNAL_OSCILLATOR             (0xA0u)
# define ETHTSYN_ANNOUNCE_TLV_TYPE                                    (0x08u)
# define ETHTSYN_ANNOUNCE_TLV_LENGTH_FIELD                            (0x08u)

/* ETHTSYN Message Types */
# define ETHTSYN_MSG_TYPE_ANNOUNCE                                    (0x0Bu)
# define ETHTSYN_MSG_TYPE_SIGNALING                                   (0x0Cu)
# define ETHTSYN_MSG_TYPE_SYNC                                        (0x00u)
# define ETHTSYN_MSG_TYPE_PDELAY_REQ                                  (0x02u)
# define ETHTSYN_MSG_TYPE_PDELAY_RESP                                 (0x03u)
# define ETHTSYN_MSG_TYPE_FOLLOW_UP                                   (0x08u)
# define ETHTSYN_MSG_TYPE_PDELAY_RES_FOLLOW_UP                        (0x0Au)
# define ETHTSYN_MSG_TYPE_INVALID                                     (0xFFu)

/* TimeBaseStatus Masks */
# define ETHTSYN_TIME_BASE_STATUS_TIMEOUT_MASK                        (0x01u)
# define ETHTSYN_TIME_BASE_STATUS_SYNC_TO_GW_MASK                     (0x04u)
# define ETHTSYN_TIME_BASE_STATUS_SYNC_TO_GW_SHIFT                    (2u)
# define ETHTSYN_TIME_BASE_STATUS_GLOBAL_TIME_BASE_MASK               (0x08u)
# define ETHTSYN_TIME_BASE_STATUS_TIMELEAP_FUTURE_MASK                (0x10u)
# define ETHTSYN_TIME_BASE_STATUS_TIMELEAP_PAST_MASK                  (0x20u)

/* ETHTSYN Ar (Sub)-Tlv values */
# define ETHTSYN_AR_SUB_TLV_OFS_TIME_SEC_SECONDS_OFFSET               (2u)

# define ETHTSYN_UINT16_MAX_VALUE                                     (65535u)

/**********************************************************************************************************************
 *  MESSAGE LENGTH AND OFFSET CONSTANT MACROS
 *********************************************************************************************************************/
/* All offsets in Byte(s) and absolute (starting from Ethernet Frame Payload, i.e. Byte_0 of message header). */

/* EthTSyn common message header fields. */
/*
                                                Octets   Offset
  8                   4                   1
  +-------------------+-------------------+
  | transportSpecific |    messageType    |       1        0
  +---------------------------------------+
  |     reserved      |    versionPTP     |       1        1
  +-------------------+-------------------+
  |             messageLength             |       2        2
  +---------------------------------------+
  |             domainNumber              |       1        4
  +---------------------------------------+
  |               reserved                |       1        5
  +---------------------------------------+
  |                 flags                 |       2        6
  +---------------------------------------+
  |            correctionField            |       8        8
  +---------------------------------------+
  |               reserved                |       4       16
  +---------------------------------------+
  |           sourcePortIdentity          |      10       20
  +---------------------------------------+
  |               sequenceId              |       2       30
  +---------------------------------------+
  |                control                |       1       32
  +---------------------------------------+
  |           logMessageInterval          |       1       33
  +---------------------------------------+
 */
/* Source Port Identity:
                                                Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |            clockIdentity              |       8        0
  +---------------------------------------+
  |              portNumber               |       2        8
  +---------------------------------------+
 */
# define ETHTSYN_MSG_HDR_TRANSPORT_SPECIFIC_OFS                       (0u)
# define ETHTSYN_MSG_HDR_TRANSPORT_SPECIFIC_SHIFT                     (4u)
# define ETHTSYN_MSG_HDR_TRANSPORT_SPECIFIC_MASK                      (0xF0u)
# define ETHTSYN_MSG_HDR_MSG_TYPE_OFS                                 (0u)
# define ETHTSYN_MSG_HDR_MSG_TYPE_SHIFT                               (0u)
# define ETHTSYN_MSG_HDR_MSG_TYPE_MASK                                (0x0Fu)
# define ETHTSYN_MSG_HDR_RESERVED_0_OFS                               (1u)
# define ETHTSYN_MSG_HDR_RESERVED_0_SHIFT                             (4u)
# define ETHTSYN_MSG_HDR_RESERVED_0_MASK                              (0xF0u)
# define ETHTSYN_MSG_HDR_VERSION_PTP_OFS                              (1u)
# define ETHTSYN_MSG_HDR_VERSION_PTP_SHIFT                            (0u)
# define ETHTSYN_MSG_HDR_VERSION_PTP_MASK                             (0x0Fu)
# define ETHTSYN_MSG_HDR_MSG_LENGTH_OFS                               (2u)
# define ETHTSYN_MSG_HDR_DOMAIN_NUM_OFS                               (4u)
# define ETHTSYN_MSG_HDR_RESERVED_1_OFS                               (5u)
# define ETHTSYN_MSG_HDR_FLAGS_OFS                                    (6u)
# define ETHTSYN_MSG_HDR_FLAGS_0_OFS                                  (6u)
# define ETHTSYN_MSG_HDR_FLAGS_1_OFS                                  (7u)
# define ETHTSYN_MSG_HDR_CORR_FIELD_OFS                               (8u)
# define ETHTSYN_MSG_HDR_RESERVED_2_OFS                               (16u)
# define ETHTSYN_MSG_HDR_SRC_PORT_IDENTITY_OFS                        (20u)
# define ETHTSYN_MSG_HDR_SRC_PORT_IDENT_CLOCK_IDENT_OFS               (20u)
# define ETHTSYN_MSG_HDR_SRC_PORT_IDENT_PORT_NUM_OFS                  (28u)
# define ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS                              (30u)
# define ETHTSYN_MSG_HDR_CONTROL_OFS                                  (32u)
# define ETHTSYN_MSG_HDR_LOG_MSG_INTERVAL_OFS                         (33u)

/* EthTSyn Port Identity field (relative offsets) */
/* Message Port Identity:
  Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |            clockIdentity              |       8        0
  +---------------------------------------+
  |              portNumber               |       2        8
  +---------------------------------------+
*/
# define ETHTSYN_MSG_PORT_IDENT_CLOCK_IDENTY_OFS                      (0u)
# define ETHTSYN_MSG_PORT_IDENT_PORT_NUM_OFS                          (8u)
# define ETHTSYN_MSG_PORT_IDENT_SIZE                                  (10u)

/* EthTSyn Sync message fields. */
/*
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |                header                 |      34        0
  +---------------------------------------+
  |               reserved                |      10       34
  +---------------------------------------+
 */
# define ETHTSYN_MSG_SYNC_RESERVED_OFS                                (34u)

/* EthTSyn FollowUp message fields. */
/*
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |                header                 |      34        0
  +---------------------------------------+
  |        preciseOriginTimestamp         |      10       34
  +---------------------------------------+
  |       Follow_Up information TLV       |      32       44
  +---------------------------------------+
  |       Optional: Ar Tlv header         |      10       76
  +---------------------------------------+
  |       Optional: Ar Sub-Tlvs           |       X       86
  +---------------------------------------+
 */
/* Precise Origin Timestamp:
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |               secondsHi               |       2        0
  +---------------------------------------+
  |              secondsLow               |       4        2
  +---------------------------------------+
  |              nanoseconds              |       4        6
  +---------------------------------------+
 */
/* FollowUp Information TLV:
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |                tlvType                |       2        0
  +---------------------------------------+
  |              lengthField              |       2        2
  +---------------------------------------+
  |            organizationId             |       3        4
  +---------------------------------------+
  |          organizationSubType          |       3        7
  +---------------------------------------+
  |       cummulativeScaledRateOffset     |       4       10
  +---------------------------------------+
  |           gmTimeBaseIndicator         |       2       14
  +---------------------------------------+
  |            lastGmPhaseChange          |      12       16
  +---------------------------------------+
  |         scaledLastGmFreqChange        |       4       28
  +---------------------------------------+
 */
# define ETHTSYN_MSG_FUP_POT_OFS                                      (34u)
# define ETHTSYN_MSG_FUP_POT_SEC_HI_OFS                               (34u)
# define ETHTSYN_MSG_FUP_POT_SEC_LOW_OFS                              (36u)
# define ETHTSYN_MSG_FUP_POT_NSEC_OFS                                 (40u)
# define ETHTSYN_MSG_FUP_INFO_TLV_TYPE_OFS                            (44u)
# define ETHTSYN_MSG_FUP_INFO_TLV_LEN_OFS                             (46u)
# define ETHTSYN_MSG_FUP_INFO_TLV_ORGA_ID_OFS                         (48u)
# define ETHTSYN_MSG_FUP_INFO_TLV_ORGA_SUB_TYPE_OFS                   (51u)
# define ETHTSYN_MSG_FUP_INFO_TLV_CUM_SCALED_RATE_OFS_OFS             (54u)
# define ETHTSYN_MSG_FUP_INFO_TLV_GM_TIME_BASE_IND_OFS                (58u)
# define ETHTSYN_MSG_FUP_INFO_TLV_LAST_GM_PHASE_CHG_OFS               (60u)
# define ETHTSYN_MSG_FUP_INFO_TLV_SCALDE_LAST_GM_PHASE_CHG_OFS        (72u)
# define ETHTSYN_MSG_FUP_AR_TLV_HDR_OFS                               (76u)
# define ETHTSYN_MSG_FUP_FIRST_AR_SUB_TLV_OFS                         (86u)

 /* EthTSyn Timestamp fields (relative offsets) */
 /* Message Timestamp:
   Octets   Offset
   8                   4                   1
   +---------------------------------------+
   |               secondsHi               |       2        0
   +---------------------------------------+
   |              secondsLow               |       4        2
   +---------------------------------------+
   |              nanoseconds              |       4        6
   +---------------------------------------+
 */
# define ETHTSYN_MSG_TS_SEC_HI_OFS                                    (0u)
# define ETHTSYN_MSG_TS_SEC_LOW_OFS                                   (2u)
# define ETHTSYN_MSG_TS_NSEC_OFS                                      (6u)

/* The AUTOSAR FollowUp message format is an extension to the IEEE FollowUp format.
 * The AR format is supported when EthTSynMessageCompliance == STD_OFF.
 * In this case, the FollowUp is extended by the AR TLV header followed by N AR-Sub-TLVs.
 * The offsets for the AR-Sub-TLVs are relative to the start of the corresponding AR-Sub-TLV because
 * the order of the AR-Sub-TLV is not fixed and not every AR-Sub-TLV might be present in every message. */

/* FollowUp AUTOSAR TLV header */
/*
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |                tlvType                |       2        0
  +---------------------------------------+
  |              lengthField              |       2        2
  +---------------------------------------+
  |            organizationId             |       3        4
  +---------------------------------------+
  |          organizationSubType          |       3        7
  +---------------------------------------+
 */
# define ETHTSYN_MSG_FUP_AR_TLV_HDR_TYPE_OFS                          (76u)
# define ETHTSYN_MSG_FUP_AR_TLV_HDR_LEN_OFS                           (78u)
# define ETHTSYN_MSG_FUP_AR_TLV_HDR_ORGA_ID_OFS                       (80u)
# define ETHTSYN_MSG_FUP_AR_TLV_HDR_ORGA_SUB_TYPE_OFS                 (83u)

/* FollowUp AR-Sub-TLV abstract header. */
/*
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |                 Type                  |       1        0
  +---------------------------------------+
  |                Length                 |       1        1
  +---------------------------------------+
 */
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_TYPE_OFS                          (0u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_LEN_OFS                           (1u)

/* FollowUp AR-Sub-TLV Time secured. */
/*
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |           AR Sub TLV header           |       2        0
  +---------------------------------------+
  |            CRC_Time_Flags             |       1        2
  +---------------------------------------+
  |              CRC_Time_0               |       1        3
  +---------------------------------------+
  |              CRC Time 1               |       1        4
  +---------------------------------------+
 */
/* Time secured Flags:
  +----------------+  +-----------------------
  |7|6|5|4|3|2|1|0||  |Flag name
  +----------------+  +-----------------------
  |7|                 |reserved
  +-------------------------------------------
    |6|               |reserved
    +-----------------------------------------
      |5|             |preciseOriginTimestamp
      +---------------------------------------
        |4|           |sequenceId
        +-------------------------------------
          |3|         |sourcePortIdentity
          +-----------------------------------
            |2|       |correctionField
            +---------------------------------
              |1|     |domainNumber
              +-------------------------------
                |0|   |messageLength
                +-----------------------------
 */
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_TIME_SECURED_FLAGS_OFS            (2u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_TIME_SECURED_CRC_0_OFS            (3u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_TIME_SECURED_CRC_1_OFS            (4u)

/* FollowUp AR-Sub-TLV Status. */
/*
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |           AR Sub TLV header           |       2        0
  +---------------------------------------+
  |                 Status                |       1        2
  +---------------------------------------+
  |               CRC Status              |       1        3
  +---------------------------------------+
 */
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_STATUS_STATUS_OFS                 (2u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_STATUS_CRC_OFS                    (3u)

/* FollowUp AR-Sub-TLV UserData */
/*
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |           AR Sub TLV header           |       2        0
  +---------------------------------------+
  |            UserDataLength             |       1        2
  +---------------------------------------+
  |              UserByte 0               |       1        3
  +---------------------------------------+
  |              UserByte 1               |       1        4
  +---------------------------------------+
  |              UserByte 2               |       1        5
  +---------------------------------------+
  |             CRC UserData              |       1        6
  +---------------------------------------+
 */
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_UD_LEN_OFS              (2u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_UD_BYTE_0_OFS           (3u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_UD_BYTE_1_OFS           (4u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_UD_BYTE_2_OFS           (5u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_USER_DATA_CRC_OFS                 (6u)

/* FollowUp AR-Sub-TLV OFS */
/*
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |           AR Sub TLV header           |       2        0
  +---------------------------------------+
  |             OfsTimeDomain             |       1        2
  +---------------------------------------+
  |               OfsTimeSec              |       6        3
  +---------------------------------------+
  |               OfsTimeNSec             |       4        9
  +---------------------------------------+
  |                 Status                |       1       13
  +---------------------------------------+
  |              UserDataLength           |       1       14
  +---------------------------------------+
  |                UserByte 0             |       1       15
  +---------------------------------------+
  |                UserByte 1             |       1       16
  +---------------------------------------+
  |                UserByte 2             |       1       17
  +---------------------------------------+
  |                 CRC_OFS               |       1       18
  +---------------------------------------+
 */
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_OFS_DOMAIN_NUM_OFS            (2u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_OFS_TIME_SEC_HI_OFS           (3u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_OFS_TIME_SEC_LOW_OFS          (5u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_OFS_TIME_NSEC_OFS             (9u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_STATUS_OFS                    (13u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_USER_DATA_LEN_OFS             (14u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_USER_DATA_BYTE_0_OFS          (15u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_USER_DATA_BYTE_1_OFS          (16u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_USER_DATA_BYTE_2_OFS          (17u)
# define ETHTSYN_MSG_FUP_AR_SUB_TLV_OFS_CRC_OFS                       (18u)

/* EthTSyn Announce message fields. */
/*
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |                header                 |      34        0
  +---------------------------------------+
  |               reserved                |      10       34
  +---------------------------------------+
  |           currentUtcOffset            |       2       44
  +---------------------------------------+
  |               reserved                |       1       46
  +---------------------------------------+
  |          grandmasterPriority1         |       1       47
  +---------------------------------------+
  |         grandmasterClockQuality       |       4       48
  +---------------------------------------+
  |          grandmasterPriority2         |       1       52
  +---------------------------------------+
  |           grandmasterIdentity         |       8       53
  +---------------------------------------+
  |              stepsRemoved             |       2       61
  +---------------------------------------+
  |               timeSource              |       1       63
  +---------------------------------------+
  |             path trace TLV            |     4+8N      64
  +---------------------------------------+
 */
/* Grandmaster Clock Quality:
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |              clockClass               |       1        0
  +---------------------------------------+
  |            clockAccuracy              |       1        1
  +---------------------------------------+
  |         offsetScaledLogVariance       |       2        2
  +---------------------------------------+
 */
/* Path Trace TLV:
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |                tlvType                |       2        0
  +---------------------------------------+
  |              lengthField              |       2        2
  +---------------------------------------+
  |             pathSequence              |      8N        4
  +---------------------------------------+
 */
# define ETHTSYN_MSG_ANNOUNCE_RESERVED_0_OFS                          (34u)
# define ETHTSYN_MSG_ANNOUNCE_CURR_UTC_OFS_OFS                        (44u)
# define ETHTSYN_MSG_ANNOUNCE_RESERVED_1_OFS                          (46u)
# define ETHTSYN_MSG_ANNOUNCE_GM_PRIO_1_OFS                           (47u)
# define ETHTSYN_MSG_ANNOUNCE_GM_CLK_QUAL_CLK_CLASS_OFS               (48u)
# define ETHTSYN_MSG_ANNOUNCE_GM_CLK_QUAL_CLK_ACCURACY_OFS            (49u)
# define ETHTSYN_MSG_ANNOUNCE_GM_CLK_QUAL_OFS_SCALED_LOG_VAR_OFS      (50u)
# define ETHTSYN_MSG_ANNOUNCE_GM_PRIO_2_OFS                           (52u)
# define ETHTSYN_MSG_ANNOUNCE_GM_IDENTITY_OFS                         (53u)
# define ETHTSYN_MSG_ANNOUNCE_STEPS_REMOVED_OFS                       (61u)
# define ETHTSYN_MSG_ANNOUNCE_TIME_SRC_OFS                            (63u)
# define ETHTSYN_MSG_ANNOUNCE_PATH_TRACE_TLV_TYPE_OFS                 (64u)
# define ETHTSYN_MSG_ANNOUNCE_PATH_TRACE_TLV_LEN_OFS                  (66u)
# define ETHTSYN_MSG_ANNOUNCE_PATH_TRACE_TLV_PATH_SEQ_START_OFS       (68u)

/* EthTSyn Pdelay request message field. */
/*
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |                header                 |      34        0
  +---------------------------------------+
  |               reserved                |      10       34
  +---------------------------------------+
  |               reserved                |      10       44
  +---------------------------------------+
 */
# define ETHTSYN_MSG_PD_REQ_RESERVED_0_OFS                            (34u)
# define ETHTSYN_MSG_PD_REQ_RESERVED_1_OFS                            (44u)

/* EthTSyn Pdelay response message filed. */
/*
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |                header                 |      34        0
  +---------------------------------------+
  |       requestReceivedTimestamp        |      10       34
  +---------------------------------------+
  |        requestingPortIdentity         |      10       44
  +---------------------------------------+
 */
/* Request received Origin Timestamp:
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |               secondsHi               |       2        0
  +---------------------------------------+
  |              secondsLow               |       4        2
  +---------------------------------------+
  |              nanoseconds              |       4        6
  +---------------------------------------+
 */
/* Requesting Port Identity:
                                                Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |            clockIdentity              |       8        0
  +---------------------------------------+
  |              portNumber               |       2        8
  +---------------------------------------+
 */
# define ETHTSYN_MSG_PD_RESP_REQ_RCVD_TS_SEC_HI_OFS                   (34u)
# define ETHTSYN_MSG_PD_RESP_REQ_RCVD_TS_SEC_LOW_OFS                  (36u)
# define ETHTSYN_MSG_PD_RESP_REQ_RCVD_TS_NSEC_OFS                     (40u)
# define ETHTSYN_MSG_PD_RESP_REQ_PORT_IDENT_OFS                       (44u)
# define ETHTSYN_MSG_PD_RESP_REQ_CLOCK_IDENTITY_OFS                   (44u)
# define ETHTSYN_MSG_PD_RESP_REQ_PORT_NUM_OFS                         (52u)

/* EthTSyn Pdelay response follow up message filed. */
/*
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |                header                 |      34        0
  +---------------------------------------+
  |        responseOriginTimestamp        |      10       34
  +---------------------------------------+
  |        requestingPortIdentity         |      10       44
  +---------------------------------------+
 */
/* Response Origin Timestamp:
                                               Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |               secondsHi               |       2        0
  +---------------------------------------+
  |              secondsLow               |       4        2
  +---------------------------------------+
  |              nanoseconds              |       4        6
  +---------------------------------------+
 */
/* Requesting Port Identity:
                                                Octets   Offset
  8                   4                   1
  +---------------------------------------+
  |            clockIdentity              |       8        0
  +---------------------------------------+
  |              portNumber               |       2        8
  +---------------------------------------+
 */
# define ETHTSYN_MSG_PD_RESP_FUP_RESP_ORG_TS_SEC_HI_OFS               (34u)
# define ETHTSYN_MSG_PD_RESP_FUP_RESP_ORG_TS_SEC_LOW_OFS              (36u)
# define ETHTSYN_MSG_PD_RESP_FUP_RESP_ORG_TS_NSEC_OFS                 (40u)
# define ETHTSYN_MSG_PD_RESP_FUP_REQ_PORT_IDENT_OFS                   (44u)
# define ETHTSYN_MSG_PD_RESP_FUP_REQ_CLOCK_IDENTITY_OFS               (44u)
# define ETHTSYN_MSG_PD_RESP_FUP_REQ_PORT_NUM_OFS                     (52u)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
# define ETHTSYN_START_SEC_VAR_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(EthTSyn_StateEnumType, ETHTSYN_VAR_ZERO_INIT) EthTSyn_State;

# define ETHTSYN_STOP_SEC_VAR_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETHTSYN_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  GLOBAL INLINE FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_IsTxReady
 *********************************************************************************************************************/
/*! \brief      Checks if transmission on the passed Port is possible.
 *  \details    -
 *  \param[in]  PortIdx     Index of the EthTSyn port
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE  - Port is ready for transmission
 *  \return     FALSE - Port is not ready for transmission
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_IsTxReady(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# if !defined(ETHTSYN_UNIT_TEST) /* COV_ETHTSYN_TESTSUITE_INSTRUMENTATION */
/**********************************************************************************************************************
 *  EthTSyn_IsTxReady
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_IsTxReady(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean txReady = FALSE;
  const EthTSyn_CtrlIdxOfPortType ethTSynCtrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
  ETHTSYN_P2CONST(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ethTSynCtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* Check EthTSyn Ctrl State */
  if((ctrlStatePtr->TransmissionMode == ETHTSYN_TX_ON) &&
    (ctrlStatePtr->TrcvLinkState == ETHTRCV_LINK_STATE_ACTIVE))
  {
    txReady = TRUE;
  }

  return txReady;
} /* EthTSyn_IsTxReady() */
# endif /* ETHTSYN_UNIT_TEST */
# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* ETHTSYN_INT_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Int.h
 *********************************************************************************************************************/
