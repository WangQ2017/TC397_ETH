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
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Appl_Time.c
 *      Project:  MICROSAR IP
 *       Module:  MICROSAR IP Base
 *    Generator:  None
 *
 *  Description:  demo time generator (integration support example providing time functions required by MICROSAR IP)
 *  
 *********************************************************************************************************************/
#define APPL_TIME_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Appl_Time.h"
  /* C_COMP_ANSI_CANOE */

/***********************************************************************************************************************
 *  ApplTime_GetTime32
 **********************************************************************************************************************/
/*! \brief      get seconds since 1980
 *  \context    TLS
 **********************************************************************************************************************/
void Appl_TlsGetTime32(uint32 *TgtDataPtr)
{
  ApplTime_GetTime32(TgtDataPtr);
}
void ApplTime_GetTime32(uint32 *TgtDataPtr)
{
  #pragma error "To Integrator: replace the code below with valid time stamp returning the time in seconds since 1980"
  *TgtDataPtr = 1366379278; /* i.e. 2013-04-19 */
}
/**********************************************************************************************************************
 *  END OF FILE: Appl_Time.c
 *********************************************************************************************************************/
