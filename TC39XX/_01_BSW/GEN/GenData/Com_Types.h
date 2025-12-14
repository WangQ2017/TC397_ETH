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
 *            Module: Com
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Com_Types.h
 *   Generation Time: 2025-12-14 17:03:57
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined (COM_TYPES_H)
# define COM_TYPES_H

/**********************************************************************************************************************
  MISRA / PClint JUSTIFICATIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "ComStack_Types.h"

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
typedef P2FUNC(void, COM_APPL_CODE, ComCbkTxAckDefType) (void);
typedef P2FUNC(void, COM_APPL_CODE, ComCbkRxTOutType) (void);
typedef P2FUNC(void, COM_APPL_CODE, ComCbkTxAckImType) (void);
typedef P2FUNC(void, COM_APPL_CODE, ComCbkTxTOutType) (void);
typedef P2FUNC(void, COM_APPL_CODE, ComRxCbkType) (void);
typedef P2FUNC(void, COM_APPL_CODE, ComCbkTxErrType) (void);
typedef P2FUNC(boolean, COM_APPL_CODE, ComTxPduCalloutType) (PduIdType PduId, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
typedef P2FUNC(boolean, COM_APPL_CODE, ComRxPduCalloutType) (PduIdType PduId, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);


/** AUTOSAR COM signal object identifier. */
typedef uint16 Com_SignalIdType;

/** AUTOSAR COM signal group object identifier. */
typedef uint16 Com_SignalGroupIdType;

/** AUTOSAR COM PDU group object identifier. */
typedef uint16 Com_IpduGroupIdType;

typedef uint8 Com_IpduGroupVector[1];  /* COM_LMGT_MAXIPDUGROUPVECTORBYTECNT */

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

#endif  /* COM_TYPES_H */
/**********************************************************************************************************************
  END OF FILE: Com_Types.h
**********************************************************************************************************************/

