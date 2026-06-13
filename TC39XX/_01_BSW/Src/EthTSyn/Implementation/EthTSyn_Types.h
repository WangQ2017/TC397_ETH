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
/*!        \file  EthTSyn_Types.h
 *        \brief  EthTSyn Types header
 *      \details  Contains all type definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/


#if !defined(ETHTSYN_TYPES_H)
# define ETHTSYN_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_GeneratedSimpleTypes.h"
# include "EthIf.h"
# include "EthTSyn_Cfg.h"
# include "StbM_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define ETHTSYN_P2CONSTCFGROOT(Type)                                 P2CONST(Type, AUTOMATIC, ETHTSYN_CONST)
# define ETHTSYN_P2CONSTCFG(Type)                                     P2CONST(Type, AUTOMATIC, ETHTSYN_CONST)
# define ETHTSYN_CONSTP2CONSTCFG(Type)                                CONSTP2CONST(Type, AUTOMATIC, ETHTSYN_CONST)
# define ETHTSYN_P2CONST(Type)                                        P2CONST(Type, AUTOMATIC, ETHTSYN_APPL_DATA)
# define ETHTSYN_CONSTP2CONST(Type)                                   CONSTP2CONST(Type, AUTOMATIC, ETHTSYN_CONST)
# define ETHTSYN_P2VAR(Type)                                          P2VAR(Type, AUTOMATIC, ETHTSYN_APPL_VAR)
# define ETHTSYN_CONSTP2VAR(Type)                                     CONSTP2VAR(Type, AUTOMATIC, ETHTSYN_CONST)
# define ETHTSYN_P2FUNC(RType, Type)                                  P2FUNC(RType, ETHTSYN_CODE, Type)

/* Type sizes in Bytes */
# define ETHTSYN_PHYS_ADDR_LEN                                        (6u)
# define ETHTSYN_CLOCK_IDENTITY_SIZE                                  (8u)
# define ETHTSYN_CORRECTION_FIELD_SIZE                                (8u)
# define ETHTSYN_PORT_NUMBER_SIZE                                     (2u)
# define ETHTSYN_SEQUENCE_ID_SIZE                                     (2u)
# define ETHTSYN_TIMESTAMP_SECONDS_SIZE                               (6u)
# define ETHTSYN_TIMESTAMP_NANOSECONDS_SIZE                           (4u)

/* Message field lengths in Bytes */
# define ETHTSYN_ORGANISATION_ID_SIZE                                 (3u)
# define ETHTSYN_ORGANISATION_SUB_TYPE_SIZE                           (3u)
# define ETHTSYN_MSG_TLV_TYPE_FIELD_SIZE                              (2u)
# define ETHTSYN_MSG_TLV_LEN_FIELD_SIZE                               (2u)

# define ETHTSYN_COM_HDR_FLAGS_SIZE                                   (2u)
# define ETHTSYN_COM_HDR_MSG_LEN_SIZE                                 (2u)
# define ETHTSYN_COM_HDR_RESERVED_1_SIZE                              (4u)

# define ETHTSYN_ANNOUNCE_RESERVED_0_SIZE                             (10u)
# define ETHTSYN_ANNOUNCE_CURR_UTC_OFS_SIZE                           (2u)
# define ETHTSYN_ANNOUNCE_GM_CLK_QUAL_OFS_SCALED_LOG_VAR_SIZE         (2u)
# define ETHTSYN_ANNOUNCE_STEPS_REMOVED_SIZE                          (2u)

# define ETHTSYN_SYNC_RESERVED_SIZE                                   (10u)

# define ETHTSYN_FUP_CUM_SCALED_RATE_OFS_SIZE                         (4u)
# define ETHTSYN_FUP_GM_TIME_BASE_INDICATOR_SIZE                      (2u)
# define ETHTSYN_FUP_LAST_GM_PHASE_CHG_SIZE                           (12u)
# define ETHTSYN_FUP_SCALED_LAST_GM_FREQ_CHG_SIZE                     (4u)

# define ETHTSYN_PD_REQ_RESERVED_0_SIZE                               (10u)
# define ETHTSYN_PD_REQ_RESERVED_1_SIZE                               (10u)

/* Ar Tlv values */
# define ETHTSYN_AR_TLV_ORGANIZATION_ID                               (0x1A75FBu)
# define ETHTSYN_AR_TLV_ORGANIZATION_SUB_TYPE                         (0x605676u)

# define ETHTSYN_AR_TLV_TYPE                                          (0x0003u)
# define ETHTSYN_AR_SUB_TLV_TYPE_TIME_SECURED                         (0x28u)
# define ETHTSYN_AR_SUB_TLV_TYPE_STATUS_SECURED                       (0x50u)
# define ETHTSYN_AR_SUB_TLV_TYPE_STATUS_NOT_SECURED                   (0x51u)
# define ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_SECURED                    (0x60u)
# define ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_NOT_SECURED                (0x61u)
# define ETHTSYN_AR_SUB_TLV_TYPE_OFS_SECURED                          (0x44u)
# define ETHTSYN_AR_SUB_TLV_TYPE_OFS_NOT_SECURED                      (0x34u)

# define ETHTSYN_AR_TLV_HEADER_TYPE_LENGTH_FIELDS_LENGTH              (4u) /* Length in byte of tlvType and lengthField */
# define ETHTSYN_AR_TLV_HEADER_LENGTH_FIELD_VALUE                     (6u) /* Does not include the Sub-Tlvs length */
# define ETHTSYN_AR_SUB_TLV_TIME_LENGTH_FIELD_VALUE                   (3u)
# define ETHTSYN_AR_SUB_TLV_STATUS_LENGTH_FIELD_VALUE                 (2u)
# define ETHTSYN_AR_SUB_TLV_USER_DATA_LENGTH_FIELD_VALUE              (5u)
# define ETHTSYN_AR_SUB_TLV_OFS_LENGTH_FIELD_VALUE                    (17u)

/* The actual AR Tlv header length is the value of its length field (6) + the type (2) and length field itself (2) */
# define ETHTSYN_AR_TLV_HEADER_LENGTH                                 (10u)
/* The actual length of an Ar SubTlv is the value of its length field + the type (1) and the length field itself (1) */
# define ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH                       (2u)
# define ETHTSYN_AR_SUB_TLV_TIME_LENGTH                               (5u)
# define ETHTSYN_AR_SUB_TLV_STATUS_LENGTH                             (4u)
# define ETHTSYN_AR_SUB_TLV_USER_DATA_LENGTH                          (7u)
# define ETHTSYN_AR_SUB_TLV_OFS_LENGTH                                (19u)

/* EthTSyn Follow_Up AR Sub TLV Status Secured/Not Secured */
# define ETHTSYN_AR_SUB_TLV_STATUS_SGW_MASK                           (0x01u)
# define ETHTSYN_AR_SUB_TLV_STATUS_SGW_POS                            (0u)

# define ETHTSYN_AR_SUB_TLV_STATUS_SGW_SYNC_TO_GTM                    (0x00u)
# define ETHTSYN_AR_SUB_TLV_STATUS_SGW_SYNC_TO_SUB_DOMAIN             (0x01u)

/* Invalid values */
# define ETHTSYN_INVALID_SWITCH_PORT_IDX                              (0xFFu)
# define ETHTSYN_INVALID_ETHIF_SWITCH_IDX                             (0xFFu)
# define ETHTSYN_SWT_MGMT_MSG_BUFFER_INVALID_IDX                      (0xFFu)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * COM_STACK_LIB_RELATED (INDEX_TYPES)
 *
 * Note: These internal index types are based on the SizeOf-Types provided by ComStackLib and are big enough
 *       to store the highest possible index. Therefore there is now risk when casting the Iteration-Type (which might
 *       be a bigger base type) to the corresponding internal index type.
 *********************************************************************************************************************/
typedef EthTSyn_SizeOfCtrlType             EthTSyn_IntCtrlIdxType;
typedef EthTSyn_SizeOfTimeDomainType       EthTSyn_IntTimeDomainIdxType;
typedef EthTSyn_SizeOfOffsetTimeDomainType EthTSyn_IntOfsTimeDomainIdxType;
typedef EthTSyn_SizeOfPortType             EthTSyn_IntPortIdxType;
typedef EthTSyn_SizeOfMasterPortType       EthTSyn_IntMasterPortIdxType;
typedef EthTSyn_SizeOfSlavePortType        EthTSyn_IntSlavePortIdxType;
typedef EthTSyn_SizeOfPdelayConfigType     EthTSyn_IntPdelayIdxType;
typedef EthTSyn_SizeOfPdelayInitiatorType  EthTSyn_IntPdelayInitiatorIdxType;
typedef EthTSyn_SizeOfPdelayResponderType  EthTSyn_IntPdelayResponderIdxType;

typedef uint16                      EthTSyn_PortNumberType;
typedef uint8                       EthTSyn_DomainNumberType;
typedef StbM_SynchronizedTimeBaseType  EthTSyn_SynchronizedTimeBaseType;
typedef uint8                       EthTSyn_BufferIdxType;
typedef uint8                       EthTSyn_ClockIdentityBaseType;
typedef uint64                      EthTSyn_ClockIdentityType;
typedef uint8                       EthTSyn_CorrectionFieldType[ETHTSYN_CORRECTION_FIELD_SIZE];
typedef sint8                       EthTSyn_LogMessageIntervalType;
typedef sint64                      EthTSyn_TimediffType;
typedef uint64                      EthTSyn_UTimediffType;
typedef float64                     EthTSyn_RateCorrectedTimediffType;
typedef uint8                       EthTSyn_TimestampQualityType;
typedef uint32                      EthTSyn_PdelayType;

# if ( (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) || (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) )
typedef Eth_TimeStampType           EthTSyn_GlobalTimestampType;
# else
/*! Timestamp struct definition */
typedef struct EthTSyn_GlobalTimestampTypeStruct
{
  uint32 nanoseconds;
  uint32 seconds;
  uint16 secondsHi;
} EthTSyn_GlobalTimestampType;
# endif /* ( (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) || (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) ) */

typedef Eth_TimeIntDiffType EthTSyn_TimeIntDiffType;

typedef P2VAR(uint8, TYPEDEF, ETHTSYN_APPL_VAR)  EthTSyn_PhyAddrPtrType;

/* EthTSyn State Definitions */
typedef enum EthTSyn_StateEnum
{
  ETHTSYN_STATE_UNINIT = 0u,
  ETHTSYN_STATE_INIT
} EthTSyn_StateEnumType;

/* EthTSyn Sync State Definition */
typedef enum EthTSyn_SyncStateEnum
{
  ETHTSYN_SYNC = 0u,
  ETHTSYN_UNSYNC = 1u,
  ETHTSYN_UNCERTAIN = 2u,
  ETHTSYN_NEVERSYNC = 3u
} EthTSyn_SyncStateType;

/* EthTSyn Transmission Mode Definition */
typedef uint8 EthTSyn_TransmissionModeType;
# define ETHTSYN_TX_OFF                                               (0x00u)
# define ETHTSYN_TX_ON                                                (0x01u)

/* EthTSyn port type type */
typedef uint8 EthTSyn_PortTypeType;
/* Bit-Masks */
/*
 * +--------------------------------+
 * |R|R|R|R|R|Host|Switch|EndStation|
 * | | | | | |Port| Port |   Port   |
 * +--------------------------------+
 */
# define ETHTSYN_PORT_TYPE_INVALID                                    (0x00u)
# define ETHTSYN_PORT_TYPE_END_STATION_PORT                           (0x01u)
# define ETHTSYN_PORT_TYPE_SWITCH_PORT                                (0x02u)
# define ETHTSYN_PORT_TYPE_SWITCH_AND_END_STATION_PORT                (0x03u)
# define ETHTSYN_PORT_TYPE_SWITCH_HOST_PORT                           (0x04u)

 /*! Internally used virtual local time type. */
typedef uint64 EthTSyn_IntVltType;

typedef struct sEthTSyn_IntVltMgmtType
{
  EthTSyn_IntVltType IntVlt;      /*!< The virtual local time in internal representation. */
  boolean            IntVltValid; /*!< Validity indication of IntVlt. */
} EthTSyn_IntVltMgmtType;

typedef struct sEthTSyn_VltRefTimesType
{
  EthTSyn_IntVltType   HwRefTime;
  EthTSyn_IntVltType   SwRefTime;
} EthTSyn_VltRefTimesType;

typedef struct sEthTSyn_TimeTupleType
{
  EthTSyn_IntVltType          IntVlt;
  EthTSyn_GlobalTimestampType GlobalTime;
} EthTSyn_TimeTupleType;

typedef struct sEthTSyn_StbmBusGetCurrTimeInfoType
{
  EthTSyn_TimeTupleType    TimeTuple;
  StbM_TimeBaseStatusType  TimeBaseStatus;
  StbM_UserDataType        UserData;
} EthTSyn_StbmBusGetCurrTimeInfoType;

typedef struct sEthTSyn_PotInfoType
{
  EthTSyn_TimeTupleType  Pot;
  EthTSyn_IntVltMgmtType SyncEgressIntVltMgmt;
  EthTSyn_IntVltMgmtType EthRefIntVltMgmt;
  EthTSyn_IntVltMgmtType StbmRefIntVltMgmt;
} EthTSyn_PotInfoType;

/*! EthTSyn Timestamp Format struct definition */
typedef struct EthTSyn_TimestampTypeStruct
{
  uint8 Seconds[ETHTSYN_TIMESTAMP_SECONDS_SIZE];
  uint8 NanoSeconds[ETHTSYN_TIMESTAMP_NANOSECONDS_SIZE];
} EthTSyn_TimestampType;

/*! Internal timestamp struct definition (used for arithmetic) */
typedef struct EthTSyn_InternalTimestampTypeStruct
{
  uint64 seconds;
  uint32 nanoseconds;
} EthTSyn_InternalTimestampType;

typedef enum eEthTSyn_TsStateEnum
{
  ETHTSYN_TS_S_UNDEFINED,
  ETHTSYN_TS_S_NOT_REQUIRED,
  ETHTSYN_TS_S_PENDING,
  ETHTSYN_TS_S_AVAILABLE,
  ETHTSYN_TS_S_INVALID
} EthTSyn_TsStateEnumType;

typedef struct sEthTSyn_TsMgmtStruct
{
  EthTSyn_TsStateEnumType      State;
  EthTSyn_GlobalTimestampType  Ts;
} EthTSyn_TsMgmtStructType;

typedef P2VAR(EthTSyn_TsMgmtStructType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_TsMgmtStructPtrType;

/*! Port identity struct definition */
typedef struct EthTSyn_PortIdentityTypeStruct
{
  EthTSyn_ClockIdentityType ClockIdentity;
  EthTSyn_PortNumberType    PortNumber;
} EthTSyn_PortIdentityType;

/* Tx Call-backs */
typedef ETHTSYN_P2FUNC(void, EthTSyn_SyncSentCbkPtrType) (
                  EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2CONST(uint8)                  TxBufPtr);

typedef ETHTSYN_P2FUNC(void, EthTSyn_FollowUpSentCbkPtrType) (
                  EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2CONST(uint8)                  TxBufPtr);

/*! EthTSyn Pdelay Request state-machine struct definition */
typedef struct EthTSyn_PdelayReqSmReqTypeStruct
{
  EthTSyn_TsMgmtStructType        EgressTsMgmt;
  uint32                          TxIntervalCnt; /*!< Decremented in each Mf. Tx Pdelay Request when counter reaches '0' */
  uint16                          SequenceId;
} EthTSyn_PdelayReqSmReqType;

/*! EthTSyn Pdelay Response Request state-machine struct definition */
typedef struct EthTSyn_PdelayRespSmReqTypeStruct
{
  EthTSyn_TsMgmtStructType  IngressTsMgmt;
  EthTSyn_PortIdentityType  SourcePortIdentity; /*!< Source Port Identity of the requesting port */
  uint16                    SequenceId;
} EthTSyn_PdelayRespSmReqType;

/*! EthTSyn Pdelay Response state-machine struct definition */
typedef struct EthTSyn_PdelayRespSmRespTypeStruct
{
  EthTSyn_TsMgmtStructType        EgressTsMgmt;
  uint16                          SequenceId;
} EthTSyn_PdelayRespSmRespType;

/*! EthTSyn Pdelay Request Response state-machine struct definition */
typedef struct EthTSyn_PdelayReqSmRespTypeStruct
{
  EthTSyn_TsMgmtStructType        IngressTsMgmt;
  EthTSyn_GlobalTimestampType     RequestReceiptTimestamp;
  EthTSyn_PortIdentityType        SourcePortIdentity; /*!< Source Port Identity of the responding port  */
  uint16                          SequenceId;
} EthTSyn_PdelayReqSmRespType;

/*! EthTSyn Pdelay Request FollowUp state-machine struct definition */
typedef struct EthTSyn_PdelayReqSmRespFollowUpTypeStruct
{
  EthTSyn_GlobalTimestampType RespOrgTs;
} EthTSyn_PdelayReqSmRespFollowUpType;

typedef P2CONST(uint8, TYPEDEF, ETHTSYN_CONST) EthTSyn_Uint8PtrToConstType;

/*! EthTSyn Ethernet Tx buffer identification struct definition */
typedef struct EthTSyn_EthTxBufferIdentTypeStruct
{
  ETHTSYN_P2CONST(uint8)   Address; /*!< Pointer to the Payload of the Ethernet Tx Buffer */
  EthTSyn_BufferIdxType    Index; /*!< Index of the Ethernet Tx Buffer */
} EthTSyn_EthTxBufferIdentType;

typedef enum EthTSyn_PdelayReqSmStateEnum
{
  ETHTSYN_S_PD_REQ_SM_DISABLED = 0u,
  ETHTSYN_S_PD_REQ_SM_TX_REQ,
  ETHTSYN_S_PD_REQ_SM_WAIT_RESP,
  ETHTSYN_S_PD_REQ_SM_WAIT_RESP_TS,
  ETHTSYN_S_PD_REQ_SM_WAIT_RESP_FUP,
  ETHTSYN_S_PD_REQ_SM_COMPUTE_PDELAY,
  ETHTSYN_S_PD_REQ_SM_WAIT_TX_COUNTER
} EthTSyn_PdelayReqSmStateEnumType;

/*! EthTSyn Pdelay Request state-machine struct definition */
typedef struct EthTSyn_PdelayReqSmTypeStruct
{
  EthTSyn_PdelayReqSmRespType         PdelayResp;
  EthTSyn_PdelayReqSmReqType          PdelayReq;
  EthTSyn_PdelayReqSmRespFollowUpType PdelayRespFollowUp;
  EthTSyn_EthTxBufferIdentType        TxBuf;
  uint32                              PdelayRespRespFollowUpTimeout;
  uint16                              LostResponses;
  sint8                               TxConfirmationPending;
  /*!< Tx == +1, TxConf == -1 --> == 0: Transmit + TxConfirmation occurred */
  EthTSyn_PdelayReqSmStateEnumType    State;
} EthTSyn_PdelayReqSmType;

typedef enum EthTSyn_PdelayRespSmStateEnum
{
  ETHTSYN_S_PD_RESP_SM_DISABLED = 0u,
  ETHTSYN_S_PD_RESP_SM_WAIT_REQ,
  ETHTSYN_S_PD_RESP_SM_WAIT_REQ_TS,
  ETHTSYN_S_PD_RESP_SM_TX_RESP,
  ETHTSYN_S_PD_RESP_SM_WAIT_RESP_TS,
  ETHTSYN_S_PD_RESP_SM_TX_RESP_FUP

} EthTSyn_PdelayRespSmStateEnumType;

/*! EthTSyn Pdelay Response state-machine struct definition */
typedef struct EthTSyn_PdelayRespSmTypeStruct
{
  EthTSyn_PdelayRespSmRespType      PdelayResp;
  EthTSyn_PdelayRespSmReqType       PdelayReq;
  EthTSyn_EthTxBufferIdentType      TxBuf;
  sint8                             TxConfirmationPending;
  /*!< Tx == +1, TxConf == -1 --> == 0: Transmit + TxConfirmation occurred */
  EthTSyn_PdelayRespSmStateEnumType State;
} EthTSyn_PdelayRespSmType;

/*! EthTSyn Master identity struct definition */
typedef struct EthTSyn_MasterIdentityTypeStruct
{
  EthTSyn_PortIdentityType  MasterPortIdentity; /*!< The Port Identity of the valid time master */
  boolean                   IsValid;            /*!< Indicating if the MasterPortIdentity information is valid */
} EthTSyn_MasterIdentityType;

/*! EthTSyn Sync Receive state-machine Sync message struct definition */
typedef struct EthTSyn_SyncReceiveSmSyncTypeStruct
{
  EthTSyn_IntVltMgmtType           IngressTsVltMgmt;
  EthTSyn_PortIdentityType         SourcePortIdentity;
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
#  if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
  uint32                           SyncRxTimeoutCnt;
#  endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */
  EthTSyn_TimediffType             SwtResidenceTime;
#  if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
  EthTSyn_TsMgmtStructType         SwtIngressTsMgmt;
#  endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
  uint16                           SequenceId;
  EthTSyn_LogMessageIntervalType   LogMessageInterval;
} EthTSyn_SyncReceiveSmSyncType;

/*! EthTSyn Sync Receive state-machine FollowUp message struct definition */
typedef struct EthTSyn_SyncReceiveSmFollowUpTypeStruct
{
  uint32                      FollowUpRxTimeoutCnt;
  uint16                      SequenceId;
} EthTSyn_SyncReceiveSmFollowUpType;

typedef enum EthTSyn_SyncReceiveSmStateEnum
{
  ETHTSYN_S_SYNC_RCV_SM_DISCARD = 0u,
  ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC,
  ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC_TS,
  ETHTSYN_S_SYNC_RCV_SM_WAIT_FUP,
  ETHTSYN_S_SYNC_RCV_SM_SYNC_TIMEOUT
} EthTSyn_SyncReceiveSmStateEnumType;

/*! EthTSyn Sync Receive state-machine struct definition */
typedef struct EthTSyn_SyncReceiveSmTypeStruct
{
  EthTSyn_SyncReceiveSmSyncType      Sync;
  EthTSyn_SyncReceiveSmFollowUpType  FollowUp;
  EthTSyn_SyncReceiveSmStateEnumType State;
  uint16                             PrevSeqId;
  boolean                            PrevSeqIdValid;
} EthTSyn_SyncReceiveSmType;

/*! EthTSyn Announce Received state-machine struct definition */
typedef struct EthTSyn_AnnounceReceiveSmTypeStruct
{
  uint32 RxTimeoutCnt;
} EthTSyn_AnnounceReceiveSmType;

typedef enum EthTSyn_SyncSendSmStateEnum
{
  ETHTSYN_S_SYNC_SEND_SM_DISABLED = 0u,
  ETHTSYN_S_SYNC_SEND_SM_INITIALIZING,
  ETHTSYN_S_SYNC_SEND_SM_WAIT_TX_COUNTER,
  ETHTSYN_S_SYNC_SEND_SM_TX_SYNC,
  ETHTSYN_S_SYNC_SEND_SM_TX_IMMEDIATE_SYNC,
  ETHTSYN_S_SYNC_SEND_SM_WAIT_SYNC_EGR_TS,
  ETHTSYN_S_SYNC_SEND_SM_TX_FUP
} EthTSyn_SyncSendSmStateEnumType;

typedef struct sEthTSyn_SyncSwResTimeMgmtType
{
  EthTSyn_TimediffType SyncSwResTime;
  boolean              SyncSwResTimeValid;
} EthTSyn_SyncSwResTimeMgmtType;

/*! EthTSyn Sync Send state-machine struct definition */
typedef struct EthTSyn_SyncSendSmTypeStruct
{
  EthTSyn_TsMgmtStructType            FollowUpPreciseOriginTsMgmt; /*!< Precise origin timestamp */
  EthTSyn_StbmBusGetCurrTimeInfoType  SyncTxTimeInfo;
  uint32                              TxIntervalCnt; /*!< Decrement with each Mf. Tx Sync message when '0' is reached */
  uint16                              SequenceId;
  EthTSyn_LogMessageIntervalType      LogMessageInterval;
  EthTSyn_SyncSendSmStateEnumType     State;
} EthTSyn_SyncSendSmType;

/*! EthTSyn Ctrl State struct definition */
typedef struct EthTSyn_CtrlStateTypeStruct
{
  EthTSyn_TransmissionModeType TransmissionMode; /*!< Current TxMode of the EthTSyn controller */
  EthTrcv_LinkStateType        TrcvLinkState;    /*!< Current link state of the EthTSyn controller */
  EthTSyn_ClockIdentityType    ClockIdentity;    /*!< Clock identity of the EthTSyn controller */
} EthTSyn_CtrlStateType;

/*! EthTSyn Grand Master Priority struct definition */
typedef struct EthTSyn_GmPriorityTypeStruct
{
  EthTSyn_PortIdentityType PortIdentity; /*!< Port Identity of the Grand Master */
} EthTSyn_GmPriorityType;

/*! EthTSyn System State struct definition */
typedef struct EthTSyn_SystemTypeStruct
{
  EthTSyn_GmPriorityType GmPriority; /*!< The Priority of the valid Grand Master */
  boolean                GmPresent;
} EthTSyn_SystemType;


/***********************************************************************************************************************
 * ETHTSYN SWITCH MANAGEMENT TYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! EthTSyn Switch Management Info struct definition */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
typedef EthSwt_MgmtInfoType  EthTSyn_SwtMgmtInfoType;
# else
typedef struct EthTSyn_SwtMgmtInfoTypeStruct
{
  uint8                SwitchIdx; /*!< EthIf switch index */
  uint8                PortIdx;   /*!< EthSwt port index */
} EthTSyn_SwtMgmtInfoType;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

typedef struct sEthTSyn_SwtMgmt_MgmtInfoMgmtStruct
{
  EthTSyn_SwtMgmtInfoType MgmtInfo;
  boolean                 IsValid;
} EthTSyn_SwtMgmt_MgmtInfoMgmtStructType;

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
typedef P2VAR(EthSwt_MgmtObjectType, TYPEDEF, ETHTSYN_VAR_NOINIT) EthTSyn_SwtMgmt_EthSwtMgmtObjPtrType;

# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
typedef enum EthTSyn_SiteSyncSyncSmStateEnum
{
  ETHTSYN_S_SSS_SM_PENDING = 0u,
  ETHTSYN_S_SSS_SM_TX_SYNC,
  ETHTSYN_S_SSS_SM_TX_FUP,
  ETHTSYN_S_SSS_SM_SYNC_TIMEOUT,
  ETHTSYN_S_SSS_SM_RCVD_SYNC_AFTER_TIMEOUT
} EthTSyn_SiteSyncSyncSmStateEnumType;

typedef struct EthTSyn_SiteSyncSyncSmMsgBufStruct
{
  uint16  RcvdMsgSequenceId;
  uint16  TxPendingCnt;
  uint8   TxRetryCnt;
  uint8   RcvdMsg[ETHTSYN_SWT_MGMT_RX_MSG_BUFFER_SIZE];
} EthTSyn_SiteSyncSyncSmMsgBufStructType;

typedef struct sEthTSyn_SiteSyncSyncSmRcvdSyncMsgHndlType
{
  EthTSyn_SiteSyncSyncSmMsgBufStructType   MsgHndl;
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF)
  EthTSyn_IntVltMgmtType                   HostIngressIntVltMgmt;
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  EthTSyn_TsMgmtStructType                 SwtIngressTsMgmt;
  EthTSyn_TsMgmtStructType                 SwtHostPortEgressTsMgmt;
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
  EthTSyn_PdelayType                       SlavePortPdelay;
} EthTSyn_SiteSyncSyncSmRcvdSyncMsgHndlType;

typedef struct
{
  uint32                                     CycleCntStartVal;
  uint32                                     CycleCnt;
  uint16                                     SequenceId;
  EthTSyn_SiteSyncSyncSmRcvdSyncMsgHndlType  LastValidRcvdSync;
} EthTSyn_SiteSyncSyncSmSyncTimoutHndlType;

/*! EthTSyn Site Sync Sync state-machine struct definition */
typedef struct EthTSyn_SiteSyncSyncSmTypeStruct
{
  EthTSyn_SiteSyncSyncSmSyncTimoutHndlType   SyncTimeoutHndl;
  EthTSyn_SiteSyncSyncSmRcvdSyncMsgHndlType  RcvdSyncMsgHndl;
  EthTSyn_SiteSyncSyncSmMsgBufStructType     RcvdFupMsgHndl;
  EthTSyn_SiteSyncSyncSmStateEnumType        State;
  boolean                                    SyncRxTimeoutDetected;
} EthTSyn_SiteSyncSyncSmType;

/*! EthTSyn Switch Time Sync Timestamp Info struct definition. */
typedef struct EthTSyn_SwtTimeSync_TimestampInfoStruct
{
  EthTSyn_GlobalTimestampType  SyncIngressTimestamp;   /*!< Switch sync ingress timestamp of the sync event */
  EthTSyn_GlobalTimestampType  PreciseOriginTimestamp; /*!< Precise origin timestamp of the sync event */
  uint16                       SequenceId;             /*!< Sequence Id of the sync event */
} EthTSyn_SwtTimeSync_TimestampInfoStructType;

/*! Switch Sync State Change callback function pointer type definition */
typedef ETHTSYN_P2FUNC(void, EthTSyn_SwtTimeSync_SwtSyncStateChgFctPtrType) (
  uint8                 SwtTimeSyncIdx,
  EthTSyn_SyncStateType NewSyncState);

#endif /* ETHTSYN_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Types.h
 *********************************************************************************************************************/
