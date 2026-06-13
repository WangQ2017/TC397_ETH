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
 *         File:  Appl_Rand.h
 *      Project:  MICROSAR IP
 *       Module:  MICROSAR IP Base
 *    Generator:  None
 *
 *  Description:  demo random generator (integration support example providing random functions required by MICROSAR IP)
 *  
 *********************************************************************************************************************/
#if !defined (APPL_RAND_H)
# define APPL_RAND_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Platform_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void ApplRand_Init(void);
uint16 ApplRand_GetRandNo(void);
uint16 Appl_Crypto_GetRandNo(void); /* deprecated */
void ApplRand_GetRandArray(uint8 *TgtDataPtr, uint16 TgtLen);
void Appl_Crypto_GetRandArray(uint8* TgtDataPtr, uint16 TgtLen); /* deprecated */
void ApplRand_Deinit( void );

#endif 
  /* APPL_RAND_H */
/**********************************************************************************************************************
 *  END OF FILE: Appl_Rand.h
 *********************************************************************************************************************/
