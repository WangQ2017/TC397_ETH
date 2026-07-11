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
/**        \file  Sd_Cbk.h
 *        \brief  Service Discovery callback header file
 *
 *      \details  Callback declarations of Service Discovery (SD)
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (SD_CBK_H)
# define SD_CBK_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Sd_Cfg.h"
# include "SoAd.h"
# include "ComStack_Types.h"

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
# define SD_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Sd_RxIndication
 *********************************************************************************************************************/
/*! \brief          Message reception callback.
 *  \details        Indication of a received I-PDU from a lower layer communication interface module.
 *  \param[in]      RxPduId      ID of the received I-PDU.
 *  \param[in]      PduInfoPtr   Contains the length (SduLength) of the received I-PDU and a pointer to
 *                               a buffer (SduDataPtr) containing the I-PDU.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    FALSE
**********************************************************************************************************************/
FUNC(void, SD_CODE) Sd_RxIndication(
  PduIdType RxPduId,
  P2CONST(PduInfoType, AUTOMATIC, SD_APPL_DATA) PduInfoPtr);

/**********************************************************************************************************************
 *  Sd_LocalIpAddrAssignmentChg
 *********************************************************************************************************************/
/*! \brief          IP address assignment change callback.
 *  \details        Called by the SoAd if an IP address assignment related to a socket connection changes
  *                 (i.e. new address assigned or assigned address becomes invalid).
 *  \param[in]      SoConId   Socket connection ID specifying the socket connection where the IP address assignment
 *                            has changed.
 *  \param[in]      State     New state of IP address assignment.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \trace          CREQ-121002
 *********************************************************************************************************************/
FUNC(void, SD_CODE) Sd_LocalIpAddrAssignmentChg(
  SoAd_SoConIdType SoConId,
  SoAd_IpAddrStateType State);

/**********************************************************************************************************************
 *  Sd_SoConModeChg
 *********************************************************************************************************************/
/*! \brief          Socket connection mode change callback.
 *  \details        Called by the SoAd module if the socket connection state has changed.
 *  \param[in]      SoConId        Socket connection ID specifying the socket connection with the mode change.
 *  \param[in]      Mode           New socket connection mode.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \trace          CREQ-121003
 *********************************************************************************************************************/
FUNC(void, SD_CODE) Sd_SoConModeChg(
  SoAd_SoConIdType SoConId,
  SoAd_SoConModeType Mode);

# define SD_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* SD_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: Sd_Cbk.h
 *********************************************************************************************************************/
