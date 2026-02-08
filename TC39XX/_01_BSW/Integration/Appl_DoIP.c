/**********************************************************************************************************************
 *  FILE REQUIRES USER MODIFICATIONS
 *  Template Scope: whole file
 *  -------------------------------------------------------------------------------------------------------------------
 *  This file includes template code that must be completed and/or adapted during BSW integration. The template code is
 *  incomplete and only intended for providing a signature and an empty implementation. It is neither intended nor
 *  qualified for use in series production without applying suitable quality measures. The template code must be
 *  completed as described in the instructions given within this file and/or in the TechnicalReference. The completed
 *  implementation must be tested with diligent care and must comply with all quality requirements which are necessary
 *  according to the state of the art before its use.
 *********************************************************************************************************************/

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
/**        \file  Appl_DoIP.c
 *        \brief  Diagnostic over Internet Protocol
 *
 *      \details  Demo application for component
 *
 *********************************************************************************************************************/

#define APPLDOIP_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Appl_DoIP.h"

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/* EXAMPLE
 *  uint8 Appl_DoIP_Vin[17u]           = { 0x57u, 0x30u, 0x4Cu, 0x30u, 0x30u, 0x30u, 0x30u, 0x34u, 0x33u, 0x4Du, 0x42u, 0x35u, 0x34u, 0x31u, 0x33u, 0x32u, 0x36u };
 *  uint8 Appl_DoIP_Gid[6u]            = { 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu };
 *  uint8 Appl_DoIP_RoutActState       = DOIP_ACTIVATION_LINE_ACTIVE; // DOIP_ACTIVATION_LINE_ACTIVE/DOIP_ACTIVATION_LINE_INACTIVE
 *  uint8 Appl_DoIP_RoutActAuthReq[]   = { 0x00u, 0x01u };
 *  uint8 Appl_DoIP_RoutActAuthReqLen  = 2u;
 *  uint8 Appl_DoIP_RoutActConfReq[]   = { 0x02u, 0x03u };
 *  uint8 Appl_DoIP_RoutActConfReqLen  = 2u;
 *  uint8 Appl_DoIP_RoutActAuthRes[]   = { 0x04u, 0x05u };
 *  uint8 Appl_DoIP_RoutActAuthResLen  = 2u;
 *  uint8 Appl_DoIP_RoutActConfRes[]   = { 0x06u, 0x07u };
 *  uint8 Appl_DoIP_RoutActConfResLen  = 2u;
 *  uint8 Appl_DoIP_OemPayloadTypeSend = 0x01u;
 *  uint8 Appl_DoIP_DiagPowerMode      = 0x01u;
 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  ApplDoIP_DoesRemoteAddressMatch()
 *********************************************************************************************************************/
/* EXAMPLE
 *  Std_ReturnType ApplDoIP_DoesRemoteAddressMatch(
 *    SoAd_SockAddrType* RemoteAddress)
 *  {
 *    Std_ReturnType retVal = E_NOT_OK;
 *  
 *  #if !defined(DOIP_DEACTIVATE_ERROR_DIRECTIVE)
 *  # error "Appl_DoIP: ApplDoIP_DoesRemoteAddressMatch() needs to be implemented!"
 *  #endif
 *  
 *    return retVal;
 *  }
 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  ApplDoIP_GetVin()
 *********************************************************************************************************************/
Std_ReturnType ApplDoIP_GetVin(
  uint8* Vin)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* EXAMPLE
   *  uint8 idx;
   *
   *  for ( idx = 0u; idx < 17u; idx++ )
   *  {
   *    Vin[idx] = Appl_DoIP_Vin[idx];
   *  }
   *
   *  retVal = E_OK;
   */

   return retVal;
}

/**********************************************************************************************************************
 *  ApplDoIP_GetDiagPowerMode()
 *********************************************************************************************************************/
Std_ReturnType ApplDoIP_GetPowerMode(
  DoIP_PowerModeType* PowerStateReady)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* EXAMPLE
   *  *PowerStateReady = Appl_DoIP_DiagPowerMode;
   *
   *  retVal = E_OK;
   */

   return retVal;
}

/**********************************************************************************************************************
 *  END OF FILE: Appl_DoIP.c
 *********************************************************************************************************************/
