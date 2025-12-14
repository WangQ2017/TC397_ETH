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
 *         File:  EthSM_Types.h
 *      Project:  MICROSAR ETH
 *       Module:  Ethernet State Manager
 *    Generator:  Ccl_AsrSmEth.jar
 *
 *  Description:  Types header file of MICROSAR Ethernet State Manager.
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

#if !defined( ETHSM_TYPES_H )
#define ETHSM_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthSM_Cfg.h"

/* adjacent module includes */
#if (( ETHSM_IS_LINK_DOWN_DEM_ENABLED == STD_ON ) || ( ETHSM_IS_ETHIF_TIMEOUT_DEM_ENABLED == STD_ON ))
# include "Dem.h"
#endif
#include "ComM.h"
#include "ComM_BusSM.h"
#include "EthIf.h"
#if ( ETHSM_IS_TCPIP_ENABLED == STD_ON )
# if ( ETHSM_IS_VECTOR_TCPIP == STD_ON )
#  include "TcpIp.h"
# else
#  include "TcpIp_EthSM.h"
# endif
#endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#if ( ( ETHSM_IS_TCPIP_ENABLED == STD_OFF ) || ( ETHSM_IS_VECTOR_TCPIP == STD_ON ) )
# define TCPIP_STATE_OFFLINE                 0U
# define TCPIP_STATE_ONHOLD                  1U
# define TCPIP_STATE_ONLINE                  2U
#endif

#define ETHSM_STACK_TYPE_TCPIP               0U
#define ETHSM_STACK_TYPE_AVB                 1U

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*
 * Data Types and Structures specified by AUTOSAR SWS
 */
#if ( ETHSM_IS_TCPIP_ENABLED == STD_OFF )
/*! Type used for the TcpIp state */
typedef uint8  TcpIp_StateType;
#endif /* ETHSM_IS_TCPIP_ENABLED */

/*! Type used for EthSM_GetCurrentInternalMode API */
typedef uint8  EthSM_NetworkModeStateType;

/*
 * Data Types and Structures used by EthSM internal
 */
/*! Type used internally for network indexes */
typedef uint8_least EthSM_NetworkIdxType;

#endif /* ETHSM_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: EthSM_Types.h
 *********************************************************************************************************************/
