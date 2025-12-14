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
/**        \file  UdpNm_Cbk.h
 *        \brief  AUTOSAR UDP Network Management
 *
 *      \details  Callback Header of AUTOSAR UDP Network Management
 *                AUTOSAR Release 4.0
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

#if !defined (UDPNM_CBK_H)
#define UDPNM_CBK_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "UdpNm_Cfg.h"                                                               /* Include UDP NM Configuration */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Component Version Information (BCD coded) */
#define UDPNM_CBK_MAJOR_VERSION         (0x06u)
#define UDPNM_CBK_MINOR_VERSION         (0x00u)
#define UDPNM_CBK_PATCH_VERSION         (0x00u)

/* Definition of Callback API-Ids. */
#define UDPNM_SID_TXCONFIRMATION        (0x0Fu) /*!< Service ID: UdpNm_SoAdIfTxConfirmation() */
#define UDPNM_SID_RXINDICATION          (0x10u) /*!< Service ID: UdpNm_SoAdIfRxIndication() */
#define UDPNM_SID_TRIGGERTRANSMIT       (0x41u) /*!< Service ID: UdpNm_SoAdIfTriggerTransmit() */

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
#define UDPNM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
  UdpNm_SoAdIfRxIndication(()
 **********************************************************************************************************************/
/*! \brief       Indicates a successfully received NM message
 *  \details     -
 *  \param[in]   RxPduId                     ID of UDP NM PDU that has been received
 *  \param[in]   PduInfoPtr                  Pointer to UDP PDU related data containing DLC and pointer to UDP SDU buffer.
 *  \pre         -
 *  \note        Called by SoAd
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       CREQ-150132
 **********************************************************************************************************************/
extern FUNC( void, UDPNM_CODE ) UdpNm_SoAdIfRxIndication( VAR( PduIdType, AUTOMATIC ) RxPduId,
                                                    P2CONST( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR ) PduInfoPtr );

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
/***********************************************************************************************************************
  UdpNm_SoAdIfTxConfirmation()
 **********************************************************************************************************************/
/*! \brief       Confirms a successfully transmitted NM message
 *  \details     -
 *  \param[in]   TxPduId                     ID of UDP NM PDU that has been transmitted
 *  \pre         -
 *  \note        Called by SoAd
 *  \context     TASK|ISR1|ISR2
 *  \config      UDPNM_PASSIVE_MODE_ENABLED == STD_OFF
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       CREQ-150131
 **********************************************************************************************************************/
extern FUNC( void, UDPNM_CODE ) UdpNm_SoAdIfTxConfirmation( VAR( PduIdType, AUTOMATIC ) TxPduId );
#endif

#if ( UDPNM_PASSIVE_MODE_ENABLED == STD_OFF )
/***********************************************************************************************************************
 *  UdpNm_SoAdIfTriggerTransmit()
 **********************************************************************************************************************/
/*! \brief         Update of data to transmit.
 *  \details       -
 *  \param[in]     TxPduId                ID of the SDU that is requested to be transmitted.
 *  \param[in,out] PduInfoPtr             Pointer to the data and length that need to be checked
 *  \return        E_OK                   SDU has been copied and SduLength indicates the number of copied bytes
 *  \return        E_NOT_OK               No SDU data has been copied. Pointer may contain a NULL pointer or point to
 *                                        invalid data.
 *  \context       TASK|ISR2
 *  \config        UDPNM_PASSIVE_MODE_ENABLED == STD_OFF
 *  \reentrant     TRUE for different PduIds
 *  \synchronous   TRUE
 *  \pre           -
 *  \trace         CREQ-168610
 **********************************************************************************************************************/
extern FUNC(Std_ReturnType, UDPNM_CODE) UdpNm_SoAdIfTriggerTransmit( VAR( PduIdType, AUTOMATIC ) TxPduId, P2VAR( PduInfoType, AUTOMATIC, UDPNM_APPL_VAR ) PduInfoPtr );
#endif


#define UDPNM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif  /* UDPNM_CBK_H */

/********************************************7**************************************************************************
 *  END OF FILE: UdpNm_Cbk.h
 *********************************************************************************************************************/
