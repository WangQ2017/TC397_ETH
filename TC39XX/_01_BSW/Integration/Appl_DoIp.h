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
/**        \file  Appl_DoIP.h
 *        \brief  Diagnostic over Internet Protocol
 *
 *      \details  Demo application for component
 *
 *********************************************************************************************************************/

#if ( !defined (APPL_DOIP_H) )
# define APPL_DOIP_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "Platform_Types.h"
# include "Compiler_Cfg.h"
# include "DoIP_Types.h"
# include "SoAd_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  ApplDoIP_GetVin()
 *********************************************************************************************************************/
/*! \brief          Retrieves VIN from application.
 *  \details        -
 *  \param[out]     Vin       Pointer to buffer where the VIN shall be stored.
 *  \return         E_OK      Request is accepted.
 *  \return         E_NOT_OK  Request is not accepted.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
Std_ReturnType ApplDoIP_GetVin(
  uint8* Vin);

/**********************************************************************************************************************
 *  ApplDoIP_GetDiagPowerMode()
 *********************************************************************************************************************/
/*! \brief          Retrieves power mode from application.
 *  \details        -
 *  \param[out]     PowerStateReady   Pointer to buffer where the power mode shall be stored.
 *  \return         E_OK              Request is accepted.
 *  \return         E_NOT_OK          Request is not accepted.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
Std_ReturnType ApplDoIP_GetPowerMode(
  DoIP_PowerModeType* PowerStateReady);


#endif
/**********************************************************************************************************************
 *  END OF FILE: Appl_DoIP.h
 *********************************************************************************************************************/
