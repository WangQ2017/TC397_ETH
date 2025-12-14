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
 *            Module: Nm
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Nm_Cfg.c
 *   Generation Time: 2025-12-14 17:03:56
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#define NM_CFG_SOURCE


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Nm_Cfg.h"


#include "ComM.h"
#include "UdpNm.h"
#include "BswM_Nm.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/
/* (NM_SYSTONMCHIND == STD_ON) If the number of system channels is not equal to the number of NM channels,
 * channel indirection is needed. Otherwise, the channel index is equals to the network handler. */
# if ( NM_SYSTONMCHIND == STD_ON )
#  define NM_CHANNEL_IDX                          Nm_GetSysToNmChInd(nmNetworkHandle)
# else
#  define NM_CHANNEL_IDX                          nmNetworkHandle
# endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  Nm_CarWakeUpCallbackFctPtr
**********************************************************************************************************************/
/** 
  \var    Nm_CarWakeUpCallbackFctPtr
  \brief  Car Wake Up Callback
*/ 
#define NM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Nm_CallbackFunction, NM_CONST) Nm_CarWakeUpCallbackFctPtr = NULL_PTR;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define NM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Nm_ChannelConfig
**********************************************************************************************************************/
/** 
  \var    Nm_ChannelConfig
  \brief  Structure for channel specific configuration parameters
  \details
  Element               Description
  NmChannelId       
  NmFunctionTableIdx    the index of the 1:1 relation pointing to Nm_NmFunctionTable
  PduRxIndication   
*/ 
#define NM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Nm_ChannelConfigType, NM_CONST) Nm_ChannelConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    NmChannelId                              NmFunctionTableIdx  PduRxIndication        Referable Keys */
  { /*     0 */ ComMConf_ComMChannel_ComMChannel_Vlan10,                 0u, NULL_PTR        }   /* [/ActiveEcuC/ComM/ComMConfigSet/ComMChannel_Vlan10] */
};
#define NM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Nm_NmFunctionTable
**********************************************************************************************************************/
/** 
  \var    Nm_NmFunctionTable
  \details
  Element                 Description
  GetState            
  DisableCommunication
  EnableCommunication 
  NetworkRelease      
  NetworkRequest      
  PassiveStartUp      
*/ 
#define NM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Nm_NmFunctionTableType, NM_CONST) Nm_NmFunctionTable[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    GetState        DisableCommunication        EnableCommunication        NetworkRelease        NetworkRequest        PassiveStartUp              Referable Keys */
  { /*     0 */ UdpNm_GetState, UdpNm_DisableCommunication, UdpNm_EnableCommunication, UdpNm_NetworkRelease, UdpNm_NetworkRequest, UdpNm_PassiveStartUp }   /* [UdpNm] */
};
#define NM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL DATA
**********************************************************************************************************************/



#if ( NM_USE_INIT_POINTER == STD_ON )
# define NM_START_SEC_VAR_INIT_UNSPECIFIED
# include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Pointer to Postbuild configuration */
P2CONST(Nm_ConfigType, NM_VAR_INIT, NM_CONST) Nm_ConfigPtr = NULL_PTR;

# define NM_STOP_SEC_VAR_INIT_UNSPECIFIED
# include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

 

/**********************************************************************************************************************
 *  END OF FILE: Nm_Cfg.c
 *********************************************************************************************************************/

