/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  Rte_Type.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Header file containing user defined AUTOSAR types and RTE structures
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_TYPE_H
# define RTE_TYPE_H

# include "Rte.h"
# include "Rte_Cfg.h"
# include "ComStack_Types.h"

/* PRQA S 1039 EOF */ /* MD_Rte_1039 */

/**********************************************************************************************************************
 * Data type definitions
 *********************************************************************************************************************/

# define Rte_TypeDef_StbM_OffsetRecordTableHeadType
typedef struct
{
  uint8 OffsetTimeDomain;
} StbM_OffsetRecordTableHeadType;

# define Rte_TypeDef_StbM_PortIdType
typedef struct
{
  uint64 clockIdentity;
  uint16 portNumber;
} StbM_PortIdType;

# define Rte_TypeDef_StbM_SyncRecordTableHeadType
typedef struct
{
  uint8 SynchronizedTimeDomain;
  uint32 HWfrequency;
  uint32 HWprescaler;
} StbM_SyncRecordTableHeadType;

# define Rte_TypeDef_StbM_TimeStampShortType
typedef struct
{
  uint32 nanoseconds;
  uint32 seconds;
} StbM_TimeStampShortType;

# define Rte_TypeDef_StbM_UserDataType
typedef struct
{
  uint8 userDataLength;
  uint8 userByte0;
  uint8 userByte1;
  uint8 userByte2;
} StbM_UserDataType;

# define Rte_TypeDef_StbM_VirtualLocalTimeType
typedef struct
{
  uint32 nanosecondsLo;
  uint32 nanosecondsHi;
} StbM_VirtualLocalTimeType;

# define Rte_TypeDef_ComM_InhibitionStatusType
typedef uint8 ComM_InhibitionStatusType;

# define Rte_TypeDef_ComM_UserHandleType
typedef uint16 ComM_UserHandleType;

# define Rte_TypeDef_EcuM_TimeType
typedef uint32 EcuM_TimeType;

# define Rte_TypeDef_EcuM_UserType
typedef uint8 EcuM_UserType;

# define Rte_TypeDef_StbM_CustomerIdType
typedef uint16 StbM_CustomerIdType;

# define Rte_TypeDef_StbM_RateDeviationType
typedef sint16 StbM_RateDeviationType;

# define Rte_TypeDef_StbM_SynchronizedTimeBaseType
typedef uint16 StbM_SynchronizedTimeBaseType;

# define Rte_TypeDef_StbM_TimeDiffType
typedef sint32 StbM_TimeDiffType;

# define Rte_TypeDef_TimeInMicrosecondsType
typedef uint32 TimeInMicrosecondsType;

# define Rte_TypeDef_BswM_ESH_Mode
typedef uint8 BswM_ESH_Mode;

# define Rte_TypeDef_BswM_ESH_RunRequest
typedef uint8 BswM_ESH_RunRequest;

# define Rte_TypeDef_ComM_ModeType
typedef uint8 ComM_ModeType;

# define Rte_TypeDef_EcuM_BootTargetType
typedef uint8 EcuM_BootTargetType;

# define Rte_TypeDef_EcuM_ModeType
typedef uint8 EcuM_ModeType;

# define Rte_TypeDef_EcuM_ShutdownCauseType
typedef uint8 EcuM_ShutdownCauseType;

# define Rte_TypeDef_EcuM_StateType
typedef uint8 EcuM_StateType;

# define Rte_TypeDef_StbM_MasterConfigType
typedef uint8 StbM_MasterConfigType;

# define Rte_TypeDef_StbM_TimeBaseNotificationType
typedef uint32 StbM_TimeBaseNotificationType;

# define Rte_TypeDef_StbM_TimeBaseStatusType
typedef uint8 StbM_TimeBaseStatusType;

# define Rte_TypeDef_StbM_EthTimeMasterMeasurementType
typedef struct
{
  uint16 sequenceId;
  StbM_PortIdType sourcePortId;
  StbM_VirtualLocalTimeType syncEgressTimestamp;
  StbM_TimeStampShortType preciseOriginTimestamp;
  sint64 correctionField;
} StbM_EthTimeMasterMeasurementType;

# define Rte_TypeDef_StbM_EthTimeSlaveMeasurementType
typedef struct
{
  uint16 sequenceId;
  StbM_PortIdType sourcePortId;
  StbM_VirtualLocalTimeType syncIngressTimestamp;
  StbM_TimeStampShortType preciseOriginTimestamp;
  sint64 correctionField;
  uint32 pDelay;
  StbM_VirtualLocalTimeType referenceLocalTimestamp;
  StbM_TimeStampShortType referenceGlobalTimestamp;
} StbM_EthTimeSlaveMeasurementType;

# define Rte_TypeDef_StbM_OffsetRecordTableBlockType
typedef struct
{
  uint32 GlbSeconds;
  uint32 GlbNanoSeconds;
  StbM_TimeBaseStatusType TimeBaseStatus;
} StbM_OffsetRecordTableBlockType;

# define Rte_TypeDef_StbM_PdelayInitiatorMeasurementType
typedef struct
{
  uint16 sequenceId;
  StbM_PortIdType requestPortId;
  StbM_PortIdType responsePortId;
  StbM_VirtualLocalTimeType requestOriginTimestamp;
  StbM_VirtualLocalTimeType responseReceiptTimestamp;
  StbM_TimeStampShortType requestReceiptTimestamp;
  StbM_TimeStampShortType responseOriginTimestamp;
  StbM_VirtualLocalTimeType referenceLocalTimestamp;
  StbM_TimeStampShortType referenceGlobalTimestamp;
  uint32 pdelay;
} StbM_PdelayInitiatorMeasurementType;

# define Rte_TypeDef_StbM_PdelayResponderMeasurementType
typedef struct
{
  uint16 sequenceId;
  StbM_PortIdType requestPortId;
  StbM_PortIdType responsePortId;
  StbM_VirtualLocalTimeType requestReceiptTimestamp;
  StbM_VirtualLocalTimeType responseOriginTimestamp;
  StbM_VirtualLocalTimeType referenceLocalTimestamp;
  StbM_TimeStampShortType referenceGlobalTimestamp;
} StbM_PdelayResponderMeasurementType;

# define Rte_TypeDef_StbM_SyncRecordTableBlockType
typedef struct
{
  uint32 GlbSeconds;
  uint32 GlbNanoSeconds;
  StbM_TimeBaseStatusType TimeBaseStatus;
  uint32 VirtualLocalTimeLow;
  sint16 RateDeviation;
  uint32 LocSeconds;
  uint32 LocNanoSeconds;
  uint32 PathDelay;
} StbM_SyncRecordTableBlockType;

# define Rte_TypeDef_StbM_TimeStampType
typedef struct
{
  StbM_TimeBaseStatusType timeBaseStatus;
  uint32 nanoseconds;
  uint32 seconds;
  uint16 secondsHi;
} StbM_TimeStampType;


# ifndef RTE_SUPPRESS_UNUSED_DATATYPES
/**********************************************************************************************************************
 * Unused Data type definitions
 *********************************************************************************************************************/

#  define Rte_TypeDef_dtRef_VOID
typedef void * dtRef_VOID;

#  define Rte_TypeDef_dtRef_const_VOID
typedef const void * dtRef_const_VOID;

#  define Rte_TypeDef_Dem_UdsStatusByteType
typedef uint8 Dem_UdsStatusByteType;

#  define Rte_TypeDef_NvM_RequestResultType
typedef uint8 NvM_RequestResultType;

#  define Rte_TypeDef_NvM_ServiceIdType
typedef uint8 NvM_ServiceIdType;

# endif
# include "Rte_DataHandleType.h"

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef unsigned int Rte_BitType;
/**********************************************************************************************************************
 * type and extern declarations of RTE internal variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte Init State Variable
 *********************************************************************************************************************/

# define RTE_STATE_UNINIT    (0U)
# define RTE_STATE_SCHM_INIT (1U)
# define RTE_STATE_INIT      (2U)

# define RTE_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_InitState; /* PRQA S 3408 */ /* MD_Rte_3408 */
extern volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_StartTiming_InitState; /* PRQA S 0850, 3408 */ /* MD_MSR_MacroArgumentEmpty, MD_Rte_3408 */

# define RTE_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define RTE_START_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_InitState_1; /* PRQA S 3408 */ /* MD_Rte_3408 */

# define RTE_STOP_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define RTE_START_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_InitState_2; /* PRQA S 3408 */ /* MD_Rte_3408 */

# define RTE_STOP_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define RTE_START_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_InitState_3; /* PRQA S 3408 */ /* MD_Rte_3408 */

# define RTE_STOP_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define RTE_START_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_InitState_4; /* PRQA S 3408 */ /* MD_Rte_3408 */

# define RTE_STOP_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define RTE_START_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern volatile VAR(uint8, RTE_VAR_ZERO_INIT_NOCACHE) Rte_InitState_5; /* PRQA S 3408 */ /* MD_Rte_3408 */

# define RTE_STOP_SEC_VAR_GLOBALSHARED_NOCACHE_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# ifdef RTE_CORE

/**********************************************************************************************************************
 * Buffers for unqueued S/R
 *********************************************************************************************************************/

#  define RTE_START_SEC_VAR_INIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(BswM_ESH_RunRequest, RTE_VAR_INIT) Rte_Cdd_nm_BswM_SRI_BswM_MSI_ESH_RunRequest_BswM_MDGP_ESH_RunRequest_requestedMode; /* PRQA S 3408, 1504 */ /* MD_Rte_3408, MD_MSR_Rule8.7 */

#  define RTE_STOP_SEC_VAR_INIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 * Data structures for mode management
 *********************************************************************************************************************/


#  define RTE_START_SEC_VAR_INIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(BswM_ESH_Mode, RTE_VAR_INIT) Rte_ModeMachine_BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode;

#  define RTE_STOP_SEC_VAR_INIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# endif /* defined(RTE_CORE) */

#endif /* RTE_TYPE_H */

/**********************************************************************************************************************
 MISRA 2012 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_1039:  MISRA rule: Rule1.2
     Reason:     Same macro and function names are required to meet AUTOSAR spec.
     Risk:       No functional risk. Macro will be undefined before function definition.
     Prevention: Not required.

   MD_Rte_3408:  MISRA rule: Rule8.4
     Reason:     For the purpose of monitoring during calibration or debugging it is necessary to use non-static declarations.
                 This is covered in the MISRA C compliance section of the Rte specification.
     Risk:       No functional risk.
     Prevention: Not required.

*/
