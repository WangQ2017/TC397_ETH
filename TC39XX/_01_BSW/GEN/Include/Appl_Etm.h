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
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Appl_Etm.h
 *        \brief  Etm header file
 *
 *      \details  Demo application of the Etm (Ethernet Testability Module) module. This module implements the
 *                AUTOSAR Testability Protocol and Service Primitives protocol for interaction with external testers.
 *
 *********************************************************************************************************************/

/* MISRA RULE 19.15 VIOLATION: The QAC-Tool states a violation of rule 19.15 with 
 * message 0883 below. Anyhow, there is a double include prevention and therefore,
 * the message is considered to be wrong. */
/* double include preventer */
#if ( !defined (APPL_ETM_H) ) /* PRQA S 0883 EOF */ /* see MISRA comment above */
# define APPL_ETM_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "Etm_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  ApplEtm_UndefinedServicePrimitive()
 *********************************************************************************************************************/
/*! \brief          Trigger Etm application to handle undefined service primitives.
 *  \details        -
 *  \param[in]      Gid             Service Group ID.
 *  \param[in]      Pid             Service Primitive ID.
 *  \param[in]      DataLength      Length of the received payload data.
 *  \param[in]      DataPtr         Pointer to the received payload data. If the payload contains other
 *                                  parameters the position and size of the parameter must be known.
 *  \param[in,out]  RespBufLength   Length of the response buffer.
 *                                  in: the max buffer length to use.
 *                                  out: the used buffer length.
 *  \param[out]     RespBufPtr      Pointer to write the response.
 *  \return         ETM_RID_E_OK    E_OK
 *  \return         ETM_RID_E_NOK   E_NOT_OK
 *  \return         ETM_RID_E_NTF   Service Primitive not found
 *  \return         ETM_RID_E_PEN   Service Primitive pending
 *  \return         ETM_RID_E_ISB   Insuffizient buffer size
 *  \return         ETM_RID_E_INV   Invalid input or parameter
 *  \pre            -
 *  \context        TASK|INTERRUPT
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
Etm_ResultIdType ApplEtm_UndefinedServicePrimitive(
  uint16 Gid,
  uint16 Pid,
  uint32 DataLength,
  uint8* DataPtr,
  uint16* RespBufLength,
  uint8* RespBufPtr);
# endif

# if (ETM_ENABLE_APPL_INIT_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  ApplEtm_InitFunction()
 *********************************************************************************************************************/
/*! \brief          Trigger Etm application to initialize there variables.
 *  \details        -
 *  \param          void none
 *  \return         none
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
void ApplEtm_InitFunction(void);
# endif

# if (ETM_ENABLE_APPL_MAIN_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  ApplEtm_MainFunction()
 *********************************************************************************************************************/
/*! \brief          Trigger Etm application cyclically.
 *  \details        -
 *  \param          void none
 *  \return         ETM_RID_E_OK    E_OK
 *  \return         ETM_RID_E_NOK   E_NOT_OK
 *  \return         ETM_RID_E_NTF   Service Primitive not found
 *  \return         ETM_RID_E_PEN   Service Primitive pending
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \note           As long as this function returns ETM_RID_E_PEN the Etm_MainFunction is paused
 *********************************************************************************************************************/
Etm_ResultIdType ApplEtm_MainFunction(void);
# endif

#endif /* !defined (APPL_ETM_H) */

/**********************************************************************************************************************
 *  END OF FILE: Appl_Etm.h
 *********************************************************************************************************************/
