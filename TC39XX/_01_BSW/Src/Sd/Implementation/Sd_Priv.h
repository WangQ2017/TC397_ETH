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
/**        \file  Sd_Priv.h
 *        \brief  Service Discovery source file
 *
 *      \details  Types definitions of Service Discovery (SD)
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (SD_PRIV_H)
# define SD_PRIV_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Sd.h"
# if (STD_ON == SD_DEM_EVENTS_CONFIGURED)
#  include "Dem.h"
# endif /* SD_DEM_EVENTS_CONFIGURED */
# include "SchM_Sd.h"

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
# define SD_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern P2CONST(Sd_ConfigType, SD_VAR_ZERO_INIT, SD_PBCFG) Sd_ConfigDataPtr;

# define SD_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
*  GLOBAL FUNCTION MACROS
*********************************************************************************************************************/
# define SD_BEGIN_CRITICAL_SECTION() SchM_Enter_Sd_SD_EXCLUSIVE_AREA_0()
# define SD_END_CRITICAL_SECTION() SchM_Exit_Sd_SD_EXCLUSIVE_AREA_0()

/* PRQA S 3453 FCT_MACROS */ /* MD_MSR_FctLikeMacroDir4.9 */

# define Sd_Copy(TgtDataPtr, SrcDataPtr, LenByte)    VStdMemCpy((SD_P2VAR(void))(TgtDataPtr), \
                                                                (SD_P2CONST(void))(SrcDataPtr), \
                                                                (LenByte))

/* GET macros */
# define SD_GET_UINT8(PduInfoPtr, Offset, Variable)      (Variable) =            ((uint8)((PduInfoPtr)->SduDataPtr)[(Offset)])

# define SD_GET_UINT16(PduInfoPtr, Offset, Variable)     (Variable) = ((uint16)(((uint16)(((PduInfoPtr)->SduDataPtr)[(Offset)     ]) << 8u) | \
                                                                                ((uint16)(((PduInfoPtr)->SduDataPtr)[(Offset) + 1u]))))

# define SD_GET_UINT24(PduInfoPtr, Offset, Variable)     ((Variable) = (uint32)(((uint32)(((PduInfoPtr)->SduDataPtr)[(Offset)     ]) << 16u) | \
                                                                                ((uint32)(((PduInfoPtr)->SduDataPtr)[(Offset) + 1u]) <<  8u) | \
                                                                                ((uint32)(((PduInfoPtr)->SduDataPtr)[(Offset) + 2u]))))

# define SD_GET_UINT32(PduInfoPtr, Offset, Variable)     (Variable) = ((uint32)(((uint32)(((PduInfoPtr)->SduDataPtr)[(Offset)     ]) << 24u) | \
                                                                                ((uint32)(((PduInfoPtr)->SduDataPtr)[(Offset) + 1u]) << 16u) | \
                                                                                ((uint32)(((PduInfoPtr)->SduDataPtr)[(Offset) + 2u]) <<  8u) | \
                                                                                ((uint32)(((PduInfoPtr)->SduDataPtr)[(Offset) + 3u]))))

# define SD_GET_OPTION_TYPE(PduInfoPtr, OptionOffset, Variable)  ((Variable) = (Sd_OptionType)(PduInfoPtr)->SduDataPtr[(OptionOffset) + SD_OPTION_LENGTH_SIZE])

# define SD_GET_ENTRY_TYPE(PduInfoPtr, EntryOffset, Variable)  ((Variable) = (Sd_EntryType)((PduInfoPtr)->SduDataPtr[(EntryOffset)]))

# define SD_GET_L4PROTOCOL_IPV4_TYPE(PduInfoPtr, EntryOffset, Variable)  ((Variable) = (Sd_L4ProtocolType)(PduInfoPtr)->SduDataPtr[(EntryOffset) + SD_OPTION_IPV4_L4PROTO_OFFSET])

# define SD_GET_L4PROTOCOL_IPV6_TYPE(PduInfoPtr, EntryOffset, Variable)  ((Variable) = (Sd_L4ProtocolType)(PduInfoPtr)->SduDataPtr[(EntryOffset) + SD_OPTION_IPV6_L4PROTO_OFFSET])

# define SD_GET_NROFOPT(PduInfoPtr, EntryOffset, Nr1stOptions, Nr2ndOptions) \
          { \
            uint8 nrOfOpt; \
            SD_GET_UINT8((PduInfoPtr), (EntryOffset) + SD_ENTRY_NROFOPTS_OFFSET, nrOfOpt); \
            (Nr1stOptions) = (uint8)(nrOfOpt >> 4u); \
            (Nr2ndOptions) = (uint8)(nrOfOpt & 0x0Fu); \
          }

# define Sd_CheckIfTimerIsInvalid(TIMER)                     ((SD_INV_TIMER_VALUE_32BIT == (TIMER).Seconds) && (SD_INV_TIMER_VALUE_16BIT == (TIMER).Milliseconds))
# define Sd_CheckIfTimerIsZero(TIMER)                        ((0u == (TIMER).Seconds) && (0u == (TIMER).Milliseconds))

# define Sd_EventHandlerUsesUdp(EVENTHANDLERIDX)             (Sd_GetEventHandlerUdpIdxOfEventHandler(EVENTHANDLERIDX) != SD_NO_EVENTHANDLERUDPIDXOFEVENTHANDLER)
# define Sd_EventHandlerUsesTcp(EVENTHANDLERIDX)             (Sd_GetEventHandlerTcpIdxOfEventHandler(EVENTHANDLERIDX) != SD_NO_EVENTHANDLERTCPIDXOFEVENTHANDLER)
# define Sd_EventHandlerUsesMulticast(EVENTHANDLERIDX)       (Sd_GetEventHandlerMulticastIdxOfEventHandler(EVENTHANDLERIDX) != SD_NO_EVENTHANDLERMULTICASTIDXOFEVENTHANDLER)

# define Sd_ConsumedEventGroupUsesUdp(EVENTGROUPIDX)         (Sd_GetRoutingGroupUdpActRefIdxOfConsumedEventgroup(EVENTGROUPIDX) != SD_NO_ROUTINGGROUPUDPACTREFIDXOFCONSUMEDEVENTGROUP)
# define Sd_ConsumedEventGroupUsesTcp(EVENTGROUPIDX)         (Sd_GetRoutingGroupTcpActRefIdxOfConsumedEventgroup(EVENTGROUPIDX) != SD_NO_ROUTINGGROUPTCPACTREFIDXOFCONSUMEDEVENTGROUP)
# define Sd_ConsumedEventGroupUsesMulticast(EVENTGROUPIDX)   (Sd_GetRoutingGroupMulticastActRefIdxOfConsumedEventgroup(EVENTGROUPIDX) != SD_NO_ROUTINGGROUPMULTICASTACTREFIDXOFCONSUMEDEVENTGROUP)

/* PRQA L:FCT_MACROS */
/* PRQA L:BRACED_MACROS */

/**********************************************************************************************************************
*  LOCAL DATA TYPES AND STRUCTURES
*********************************************************************************************************************/
/* This type defines the general function API which can be used to access values. */
typedef P2FUNC(uint16, SD_CODE, Sd_ServiceIdGetterFctType)  ( \
  uint16 Idx);

#endif /* SD_PRIV_H */

/**********************************************************************************************************************
 *  END OF FILE: Sd_Priv.h
 *********************************************************************************************************************/
