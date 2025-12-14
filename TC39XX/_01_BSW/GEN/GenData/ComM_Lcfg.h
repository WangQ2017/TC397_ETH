/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: ComM
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: ComM_Lcfg.h
 *   Generation Time: 2025-12-14 17:03:55
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined(COMM_LCFG_H)
#define COMM_LCFG_H

/* -----------------------------------------------------------------------------
    &&&~ INCLUDES
 ----------------------------------------------------------------------------- */

#include "ComM_Cfg.h"

/* -----------------------------------------------------------------------------
    &&&~ GLOBAL DATA
 ----------------------------------------------------------------------------- */

#define COMM_START_SEC_CONST_UNSPECIFIED
 /* PRQA S 5087 1 */ /* MD_MSR_MemMap */ 
#include "MemMap.h"

extern CONST(ComM_InhibitionStatusType, COMM_CONST) ComM_ECUGroupClassInit;

#define COMM_STOP_SEC_CONST_UNSPECIFIED
 /* PRQA S 5087 1 */ /* MD_MSR_MemMap */ 
#include "MemMap.h"

/* PRQA S 3451, 3449 EXTERNDECLARATIONS */ /* MD_ComM_3451_3449 */ 

/* PRQA L:EXTERNDECLARATIONS */

#define COMM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "MemMap.h"

/* -----------------------------------------------------------------------------
    &&&~ GLOBAL FUNCTION PROTOTYPES
 ----------------------------------------------------------------------------- */

 /* PRQA S 3451, 3449 EXTERNDECLARATIONS */ /* MD_ComM_3451_3449 */ 
/*********************************************************************************************************************
FUNCTION: ComM_MainFunction_0
*********************************************************************************************************************/
/*! \brief       Calls ComM_MainFunction() for the corresponding channel. This function is called by RTE with the 
 *               configured channel-specific Main Function Period
 *  \pre         ComM must be initialized
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
*********************************************************************************************************************/
extern FUNC(void, COMM_CODE) ComM_MainFunction_0(void);
/* PRQA L:EXTERNDECLARATIONS */

/* -----------------------------------------------------------------------------
    &&&~ INTERNAL GENERATED FUNCTION PROTOTYPES
 ----------------------------------------------------------------------------- */

/*********************************************************************************************************************
  FUNCTION: ComM_RequestBusSMMode
*********************************************************************************************************************/
/*! \brief       Requests a communication mode by BusSM
 *  \param[in]   Channel                 Handle of the ComM channel, can be found in ComM_Lcfg.h
 *  \param[out]  ComMode                 Mode to request by BusSM
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
*********************************************************************************************************************/
extern FUNC(void, COMM_CODE) ComM_RequestBusSMMode(NetworkHandleType Channel, ComM_ModeType ComMode);

/*********************************************************************************************************************
  FUNCTION: ComM_GetCurrentBusSMMode
*********************************************************************************************************************/
/*! \brief       Queries the current BusSM communication mode of the corresponding channel.
 *  \param[in]   Channel                 Handle of the ComM channel, can be found in ComM_Lcfg.h
 *  \param[out]  ComMode                 Pointer where the current BusSM mode shall be stored
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
*********************************************************************************************************************/
extern FUNC(void, COMM_CODE) ComM_GetCurrentBusSMMode(NetworkHandleType Channel, P2VAR(ComM_ModeType, AUTOMATIC, AUTOMATIC) ComMode);



#define COMM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "MemMap.h"


#endif /* COMM_LCFG_H */

