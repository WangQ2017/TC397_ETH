/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Eth_30_Tc3xx.h
 *        \brief  Public header file of Ethernet controller driver
 *
 *      \details  Provides access to the Ethernet controller drivers API.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2016-10-04  visfer  -             Initial creation
 *  01.00.01  2016-11-28  visfer  ESCAN00093063 Transmission stops when upper layers request to free several 
 *                                              provided buffers
 *  01.00.01  2016-11-28  visfer  ESCAN00093163 Compiler error due to wrong API infixing in compiler_cfg.h and memmap.h
 *  02.00.00  2017-02-15  vismha  ESCAN00094012 Changes due to DrvEth_VttEthAsr migration
 *                        visfer  ESCAN00093414 Pre- and Post-ControllerInit Callouts are missing
 *                        visfer  ESCAN00093412 Review Integration and refacturing of code, comments and detailed design
 *                        visfer  ESCAN00093704 Compiler error: undeclared identifiers 
 *                                              Eth_30_Tc3xx_MulticastBucketCounters, Eth_30_Tc3xx_PromiscuousModeCounter
 *  03.00.00  2017-05-02  vismha  ESCAN00094983 Extend Core for support of FEC and ENET drivers with extended feature
 *                                              set
 *  03.00.01  2017-05-29  visfer  ESCAN00095318 Compiler error: Det.h referenced although Dev Error Report is switched
 *                                              off
 *  03.00.02  2017-06-29  visfer  ESCAN00095679 Add return value to Eth_30_Tc3xx_LL_TimeSync_SetHwTime()
 *  03.01.00  2017-07-04  visdrr  FEATC-1245    FEAT-2151: Extended Ethernet Bus Diagnostic
 *  03.02.00  2017-07-25  visbgr  ESCAN00095826 Changes due to DrvEth_S6J3xEthAsr migration
 *  03.02.01  2017-09-07  visfer  ESCAN00096586 MemMap.h template does not contain correct handling 
 *                                              ETH_30_TC3XX_STOP_SEC_APPL_CODE
 *  03.02.02  2017-09-11  visfer  ESCAN00096614 Compiler warning: Variable FrameId is possibly uinitialized
 *  03.02.03  2017-09-11  visfer  ESCAN00096760 Time synchronization using gPTP is not possible
 *  05.00.00  2018-03-01  visbgr  STORYC-422    FEAT-2876,S-456 [SAFE] SafeBSW for Eth(Core) (ASIL B), P3REQ,CAD,TST,REV
 *                        visbgr  STORYC-423    FEAT-2876,S-457 [SAFE] SafeBSW for Eth(Core) (ASIL B), S1 ComStackLib
 *                        visbgr  STORYC-424    FEAT-2876,S-458 [SAFE] SafeBSW for Eth(Core) (ASIL B), S1Tst
 *                        visbgr  ESCAN00097402 Init API uses incorrect API Id for DET reporting
 *                        visbgr  ESCAN00097133 Memory violation in case Eth_30_<derivative>_Pending[Rx|Tx]Events
 *                                              is not initialized with zero
 *                        visbgr  STORYC-5619   DrvEth__coreAsr: Improve include structure in the implementation
 *            2018-07-27  visdrr  ESCAN00100196 DET-Check in VTransmit missing: API call with NULL_PTR possible
 *  06.00.00  2018-08-08  visdrr  STORYC-428    FEAT-2876,S-463 [SAFE] SafeBSW for Eth(Core) (ASIL B), S1REV
 *                                ESCAN00098835 Missing DET check for parameter RxStatusPtr of Eth_Receive API
 *            2018-08-09  visdrr  STORYC-6235   FEAT-2876 [SAFE] SafeBSW for Eth(Core) SilentAnalysis Rework:
 *                                              Rework HL/LL-Interface
 *                                STORYC-6236   FEAT-2876 [SAFE] SafeBSW for Eth(Core) SilentAnalysis Rework:
 *                                              Add runtime checks at locations with Ethernet buffer access
 *  06.00.01  2019-04-24  viskob  ESCAN00103483 Compiler error: Eth_30_<MSN>_Ctrl2ProtectedAreaIdMap is undefined
 *                                ESCAN00103327 MISRA deviation: MISRA-C:2004 Rule 5.1 - ID 4:0779
 *  06.00.02  2019-08-08  viskob  ESCAN00103936 Counter measure tag spelling error causes traceability findings
 *            2019-08-19  viskob  ESCAN00104035 Out of bounds read-access possible: Incorrect source MAC address is
 *                                              written to the register and used for transmission, if [..].
 *  07.00.00  2019-04-29  visdrr  STORYC-7882   Interface between DrvEth__coreAsr and DrvEthSwitch__coreAsr according to
 *                                              ASR4.4.x (DrvEth__coreAsr)
 *  07.01.00  2019-08-28  visdrr  FEAT-4936     Support of MSTAR MSE102x
 *                                ESCAN00104035 Out of bounds read-access possible: Incorrect source MAC address is 
 *                                              written to the register and used for transmission, if more than one 
 *                                              Ethernet controller configuration or driver is used
 *            2019-09-27  visdrr  ESCAN00103936 Counter measure tag spelling error causes traceability findings
 *  07.01.01  2019-10-21  viskob  ETH-1047      Support of Mse102x - DrvEth QM
 *  07.02.00  2019-09-06  viskob  ETH-833       Merge branch 6.xx.xx into trunk.
 *  08.00.00  2019-11-11  viskob  ETH-1099      DrvEth__coreAsr - Merge 7.xx.xx into trunk.
 *  08.01.00  2020-03-27  visdep  ETH-1255      Provide information about dropped frames due to insufficient Tx/Rx
 *                                              software buffers
 *            2020-04-16  visdrr  PS-273        Introduce buffer warning level callout for the reception path
 *            2020-04-16  visdrr  ESCAN00106007 Access to buffer and descriptor variables of incorrect Ethernet
 *                                              controller/channel happens in multi-Ethernet controller configurations
 *  08.01.01  2020-07-09  vircnt  ETH-2145      Update MISRA justifications
 *                                ETH-2716      Support of DrvEth_Tc3xxEthAsr
 *  08.01.02  2020-07-13  visdrr  ESCAN00106470 Inconsistent descriptor state possible in transmission path:
 *                                              Memory barrier missing between setting up and triggering transmission
 *  08.01.03  2020-08-07  visdep  ESCAN00107011 Compiler error: Wrong memory class in 
 *                                              Eth_30_Tc3xx_Internal_ClearMeasurementData
 *  08.01.04  2020-08-10  visdrr  ESCAN00106987 Frame loss in higher priority queues under high bus load in polling mode
 *                                              with QoS enabled
 *            2020-08-10  visdrr  ESCAN00105184 Tx buffers get not freed on lower prior queues when QoS is used in
 *                                              polling mode and high amount of traffic is communicated on higher prior
 *                                              QoS queues
 *  08.01.05  2020-09-22  visdrr  ESCAN00107263 Tx buffer start offset is not correct in
 *                                              ProvideTxBuffer_HandleValidBuffer
 *            2020-09-22  visdrr  ESCAN00107236 Compiler error: Appl_Eth_30_Tc3xx_MemoryBarrier function is undefined
 *                                              when ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_ON
 *            2020-09-22  visdrr  ESCAN00106769 Invalid buffer- or descriptor alignment could be undetected in multi-
 *                                              channel configuration
 *  08.01.06  2020-10-07  vircnt  ESCAN00107156 Receiving and transmitting frames does not work in interrupt mode if 
 *                                              development error detection is disabled
 *  08.01.07  2020-10-27  virstl  ESCAN00107683 Untagged frames to a Tx queue mapping configuration has no efffect
 *  08.01.08  2021-01-22  visdrr  ESCAN00108359 Eth_30_Tc3xx_VTransmit fails due to a wrong buffer index check in multi-
 *                                              channel configurations
 *  08.02.00  2021-03-16  visdep  ETHCIF-138    Introduce assignment of Ethernet frames to queues based on VLAN ID
 *********************************************************************************************************************/

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#if !defined(ETH_30_TC3XX_H)
# define ETH_30_TC3XX_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_GenTypes.h"
# if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
#  include "Eth_30_Tc3xx_TimeSync.h"
# endif /* ETH_30_TC3XX_ENABLE_TIMESYNC */
# if (ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON)
#  include "Eth_30_Tc3xx_TrafficHandling.h"
# endif /* ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Vendor and module identification */
# define ETH_30_TC3XX_VENDOR_ID                                        (30u)
# define ETH_30_TC3XX_MODULE_ID                                        (88u)

/* AUTOSAR 4.x Software Specification Version Information */
# define ETH_30_TC3XX_AR_RELEASE_MAJOR_VERSION                         (0x04u)
# define ETH_30_TC3XX_AR_RELEASE_MINOR_VERSION                         (0x01u)
# define ETH_30_TC3XX_AR_RELEASE_REVISION_VERSION                      (0x01u)

/* ----- ETH API service IDs ----- */
/*!< Service ID: Eth_30_Tc3xx_Init() */
# define ETH_30_TC3XX_SID_INIT                                         (0x01u)
/*!< Service ID: Eth_30_Tc3xx_ControllerInit() */
# define ETH_30_TC3XX_SID_CONTROLLER_INIT                              (0x02u)
/*!< Service ID: Eth_30_Tc3xx_SetControllerMode() */
# define ETH_30_TC3XX_SID_SET_CONTROLLER_MODE                          (0x03u)
/*!< Service ID: Eth_30_Tc3xx_GetControllerMode() */
# define ETH_30_TC3XX_SID_GET_CONTROLLER_MODE                          (0x04u)
/*!< Service ID: Eth_30_Tc3xx_WriteMii() */
# define ETH_30_TC3XX_SID_WRITE_MII                                    (0x05u)
/*!< Service ID: Eth_30_Tc3xx_ReadMii() */
# define ETH_30_TC3XX_SID_READ_MII                                     (0x06u)
/*!< Service ID: Eth_30_Tc3xx_GetCounterState() */
# define ETH_30_TC3XX_SID_GET_COUNTER_STATE                            (0x07u)
/*!< Service ID: Eth_30_Tc3xx_GetPhysAddr() */
# define ETH_30_TC3XX_SID_GET_PHYS_ADDR                                (0x08u)
/*!< Service ID: Eth_30_Tc3xx_ProvideTxBuffer() */
# define ETH_30_TC3XX_SID_PROVIDE_TX_BUFFER                            (0x09u)
/*!< Service ID: Eth_30_Tc3xx_Transmit() */
# define ETH_30_TC3XX_SID_TRANSMIT                                     (0x0Au)
/*!< Service ID: Eth_30_Tc3xx_UpdatePhysAddrFilter() */
# define ETH_30_TC3XX_SID_UPDATE_PHYS_ADDR_FILTER                      (0x12u)
/*!< Service ID: Eth_30_Tc3xx_SetPhysAddr() */
# define ETH_30_TC3XX_SID_SET_PHYS_ADDR                                (0x13u)
/*!< Service ID: Eth_30_Tc3xx_Receive() */
# define ETH_30_TC3XX_SID_RECEIVE                                      (0x0Bu)
/*!< Service ID: Eth_30_Tc3xx_TxConfirmation() */
# define ETH_30_TC3XX_SID_TX_CONFIRMATION                              (0x0Cu)
/*!< Service ID: Eth_30_Tc3xx_GetVersionInfo() */
# define ETH_30_TC3XX_SID_GET_VERSION_INFO                             (0x0Du)
/*!< Service ID: Eth_30_Tc3xx_GetRxStats() */
# define ETH_30_TC3XX_SID_GET_RX_STATS                                 (0x0Eu)
/*!< Service ID: Eth_30_Tc3xx_GetTxStats() */
# define ETH_30_TC3XX_SID_GET_TX_STATS                                 (0x0Fu)
/*!< Service ID: Eth_30_Tc3xx_GetAndResetMeasurementData() */
# define ETH_30_TC3XX_SID_GET_AND_RESET_MEASUREMENT_DATA_API           (0x11u)

/* ----- ETH DET Error codes ----- */
/*!< used to check if no error occurred - use a value unequal to any error code */
# define ETH_30_TC3XX_E_NO_ERROR                                       (0x00u)
/*!< Error code: API called with wrong controller index */
# define ETH_30_TC3XX_E_INV_CTRL_IDX                                   (0x01u)
/*!< Error code: API called while module was not initialized correctly */
# define ETH_30_TC3XX_E_NOT_INITIALIZED                                (0x02u)
/*!< Error code: API called with wrong pointer parameter (NULL_PTR) */
# define ETH_30_TC3XX_E_INV_POINTER                                    (0x03u)
/*!< Error code: API called with invalid parameter */
# define ETH_30_TC3XX_E_INV_PARAM                                      (0x04u)
/*!< Error code: Initialization triggered for an unknown configuration */
# define ETH_30_TC3XX_E_INV_CONFIG                                     (0x05u)
/*!< Error code: API called while module was in an invalid mode */
# define ETH_30_TC3XX_E_INV_MODE                                       (0x06u)
/*!< Error code: Invalid alignment of buffer or descriptor */
# define ETH_30_TC3XX_E_INV_ALIGNMENT                                  (0x07u)

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_InitMemory
 **********************************************************************************************************************/
/*! \brief       Initializes *_INIT_*-variables
 *  \details     Service to initialize module global variables at power up. This function initializes the variables in
 *               *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is uninitialized
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_InitMemory( void );

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Init
 **********************************************************************************************************************/
/*! \brief       Initializes the module
 *  \details     Function initializes the module Eth_30_Tc3xx. It initializes all variables and sets the module state to
 *               initialized.
 *  \param[in]   CfgPtr  Pointer to post-build configuration or null pointer
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module's *_INIT*_-variables are initialized either by Eth_30_Tc3xx_InitMemory() or startup code
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Init(
  P2CONST(Eth_30_Tc3xx_ConfigType, ETH_30_TC3XX_CONST, ETH_30_TC3XX_CONST) CfgPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ControllerInit
 **********************************************************************************************************************/
/*! \brief       Initializes an Ethernet controller
 *  \details     Function initializes an Ethernet controller and the related variables so it is possible to set it in
 *               operation afterwards.
 *  \param[in]   CtrlIdx  Identifier of the Ethernet controller
 *  \param[in]   CfgIdx   Identifier of the configuration (only 0 allowed)
 *  \return      E_NOT_OK - Initialization of Ethernet controller failed
 *  \return      E_OK - Ethernet controller initialized
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Module is initialized
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ControllerInit(
  uint8 CtrlIdx,
  uint8 CfgIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_SetControllerMode
 **********************************************************************************************************************/
/*! \brief       Sets the operation mode of an Ethernet controller
 *  \details     Function sets the operation mode of the Ethernet controller so it is either turned off (no frame
 *               reception and transmission) or turned on (frames can be transmitted and received).
 *  \param[in]   CtrlIdx   Identifier of the Ethernet controller
 *  \param[in]   CtrlMode  Operation mode that shall be applied:
 *                         ETH_MODE_DOWN - Ethernet controller shall be turned off
 *                         ETH_MODE_ACTIVE - Ethernet controller shall be turned on
 *  \return      E_NOT_OK - Operation mode couldn't be applied
 *  \return      E_OK - Operation mode successfully applied
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetControllerMode(
  uint8        CtrlIdx,
  Eth_ModeType CtrlMode);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetControllerMode
 **********************************************************************************************************************/
/*! \brief       Retrieves the current operation mode of an Ethernet controller
 *  \details     -
 *  \param[in]   CtrlIdx      Identifier of the Ethernet controller
 *  \param[out]  CtrlModePtr  Operation mode retrieved
 *  \return      E_NOT_OK - Retrieval of operation mode failed
 *  \return      E_OK - Operation mode successfully retrieved
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetControllerMode(
        uint8                               CtrlIdx,
  P2VAR(Eth_ModeType, AUTOMATIC, AUTOMATIC) CtrlModePtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetPhysAddr
 **********************************************************************************************************************/
/*! \brief       Retrieves the currently active MAC address of an Ethernet controller
 *  \details     -
 *  \param[in]   CtrlIdx      Identifier of the Ethernet controller
 *  \param[out]  PhysAddrPtr  Buffer of at least 6 byte to pass the MAC address
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Module is initialized
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPhysAddr(
        uint8                        CtrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetPhysAddr
 *********************************************************************************************************************/
/*! \brief       Sets the MAC address of an Ethernet controller
 *  \details     Function sets the MAC address of an Ethernet controller. Dependent on the configuration of the "Write
 *               MAC address" feature the change is persisted in non-volatile RAM and also available after a power-
 *               cycle of the MCU.
 *  \param[in]   CtrlIdx      Identifier of the Ethernet controller
 *  \param[in]   PhysAddrPtr  Buffer holding the MAC address that shall be applied
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Module is initialized
 */
FUNC (void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetPhysAddr(
          uint8                        CtrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr);

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_UpdatePhysAddrFilter
 *********************************************************************************************************************/
/*! \brief        Updates the reception MAC address filter of an Ethernet controller
 *  \details      Function allows to add or remove MAC address from the reception filter of the Ethernet controller
 *                so Ethernet frames addressed to the respective MAC address can be received or will be blocked from
 *                reception.
 *  \param[in]    CtrlIdx               Identifier of the Ethernet controller
 *  \param[in]    PhysAddrPtr           Buffer holding the MAC address the filter shall be adapted for
 *  \param[in]    Eth_FilterActionType  Action that shall be applied for the filter:
 *                                      ETH_REMOVE_FROM_FILTER - MAC address shall be blocked
 *                                      ETH_ADD_TO_FILTER - MAC address shall be allowed
 *  \return      E_NOT_OK - Filter modification failed
 *  \return      E_OK - Filter successfully updated
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 *********************************************************************************************************************/
FUNC (Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_UpdatePhysAddrFilter(
          uint8                                      CtrlIdx,
  P2CONST(uint8,               AUTOMATIC, AUTOMATIC) PhysAddrPtr,
          Eth_FilterActionType                       Action);
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

# if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_WriteMii
 **********************************************************************************************************************/
/*! \brief       Triggers a write command on the MDIO interface of an Ethernet controller
 *  \details     Function triggers a write command on the MDIO interface according to clause 22 of the IEEE
 *               specification.
 *  \param[in]   CtrlIdx  Identifier of the Ethernet controller
 *  \param[in]   TrcvIdx  Address of the counter part on MDIO interface (MII address)
 *  \param[in]   RegIdx   Address of the register that shall be written
 *  \param[in]   RegVal   Value that shall be written to the register
 *  \return      ETH_E_NOT_OK - Service call failed due to invalid module state or function parameters
 *  \return      ETH_E_NO_ACCESS - Access to the MDIO interface timed out
 *  \return      ETH_OK - Write command was triggered successfully
 *  \context     ANY
 *  \reentrant   TRUE for different MDIO interfaces
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
 */
FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_WriteMii(
  uint8  CtrlIdx,
  uint8  TrcvIdx,
  uint8  RegIdx,
  uint16 RegVal);
# endif /* ETH_30_TC3XX_MII_INTERFACE */

# if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ReadMii
 **********************************************************************************************************************/
/*! \brief       Triggers a read command on the MDIO interface of an Ethernet controller and provides the result
 *  \details     Function triggers a read command on the MDIO interface according to clause 22 of the IEEE
 *               specification and provides the result of the read.
 *  \param[in]   CtrlIdx    Identifier of the Ethernet controller
 *  \param[in]   TrcvIdx    Address of the counter part on MDIO interface (MII address)
 *  \param[in]   RegIdx     Address of the register that shall be read
 *  \param[out]  RegValPtr  Buffer to store the result of the read command
 *  \return      ETH_E_NOT_OK - Service call failed due to invalid module state or function parameters
 *  \return      ETH_E_NO_ACCESS - Access to the MDIO interface timed out
 *  \return      ETH_OK -
 *  \context     ANY
 *  \reentrant   TRUE  for different MDIO interfaces
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
 */
FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ReadMii(
        uint8                         CtrlIdx,
        uint8                         TrcvIdx,
        uint8                         RegIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) RegValPtr);
# endif /* ETH_30_TC3XX_MII_INTERFACE */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetCounterState
 **********************************************************************************************************************/
/*! \brief       Retrieves the value of an Ethernet statistics counter
 *  \details     Function retrieves the value of an Ethernet statistics counter by addressing the counter with the help
 *               of an offset into the Ethernet statistics counter register space.
 *  \param[in]   CtrlIdx    Identifier of the Ethernet controller
 *  \param[in]   CtrOffs    Offset of the counter into the Ethernet statistics counter register space
 *  \param[out]  CtrValPtr  Buffer to store the counter value
 *  \return      E_NOT_OK - Counter retrieval failed
 *  \return      E_OK - Counter successfully retrieved
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 *  \trace       CREQ-137705
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetCounterState(
        uint8                         CtrlIdx,
        uint16                        CtrOffs,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) CtrValPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ProvideTxBuffer
 **********************************************************************************************************************/
/*! \brief          Provides a buffer that can be used to transmit an Ethernet frame
 *  \details        Function provides a buffer that can be used to transmit an Ethernet frame. The buffer is locked and
 *                  therefore protected against reuse until the transmission of the frame is confirmed after transmission
 *                  was triggered (Eth_Transmit() and consecutive Eth_TxConfirmation()) or buffer is intentionally released
 *                  by calling Eth_Transmit() with LenByte=0.
 *  \param[in]      CtrlIdx     Identifier of the Ethernet controller
 *  \param[out]     BufIdxPtr   Identifier of the buffer provided on successful buffer provision
 *  \param[out]     BufPtr      Pointer to the buffer provided on successful buffer provision
 *  \param[in,out]  LenBytePtr  Buffer used to determine the requested and the provide length of the buffer:
 *                              [in]  Length of the data the caller wants to transmit (Payload length)
 *                              [out] Actual length of the buffer provided
 *  \return         BUFREQ_E_NOT_OK - Service was called
 *  \return         BUFREQ_E_OVFL - No buffer with the requested length available by configuration
 *  \return         BUFREQ_E_BUSY - Any buffer able to hold the requested length is already in use
 *  \return         BUFREQ_OK - Buffer successfully provided
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            Ethernet controller is operational in mode ACTIVE
 */
FUNC(BufReq_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ProvideTxBuffer(
              uint8                                                      CtrlIdx,
        P2VAR(uint8,        AUTOMATIC, AUTOMATIC)                        BufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) BufPtr,
        P2VAR(uint16,       AUTOMATIC, AUTOMATIC)                        LenBytePtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Transmit
 **********************************************************************************************************************/
/*! \brief       Trigger the transmission of an Ethernet frame created from the passed buffer
 *  \details     Function takes the buffer previously provided by Eth_ProvideTxBuffer() enhances it with the Ethernet
 *               header and triggers the transmission of the Ethernet frame.
 *  \param[in]   CtrlIdx         Identifier of the Ethernet controller
 *  \param[in]   BufIdx          Identifier of the buffer provided by Eth_ProvideTxBuffer()
 *  \param[in]   FrameType       Ethernet type, according to type field of IEEE802.3
 *  \param[in]   TxConfirmation  Request for a transmission confirmation:
 *                               FALSE - No transmission confirmation desired
 *                               TRUE - Transmission confirmation desired
 *  \param[in]   LenByte         Length of the data to be transmitted (Payload length)
 *  \param[in]   PhysAddrPtr     MAC address the frame shall be sent to
 *  \return      E_NOT_OK - Triggering of frame transmission wasn't possible
 *  \return      E_OK - Frame transmission triggered
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
 *  \pre         Buffer was acquired by Eth_ProvideTxBuffer()
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Transmit(
          uint8                        CtrlIdx,
          uint8                        BufIdx,
          Eth_FrameType                FrameType,
          boolean                      TxConfirmation,
          uint16                       LenByte,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Receive
 **********************************************************************************************************************/
/*! \brief       Triggers the reception of an Ethernet frame
 *  \details     -
 *  \param[in]   CtrlIdx      Identifier of the Ethernet controller
 *  \param[out]  RxStatusPtr  Indicates the result of the reception trigger:
 *                            ETH_RECEIVED - Ethernet frame was received and no more frames are waiting to be received
 *                            ETH_NOT_RECEIVED - No Ethernet frame was received because non was waiting to be received
 *                            ETH_RECEIVED_MORE_DATA_AVAILABLE - Ethernet frame was received and at least one more
 *                                                               frame is waiting to be received
 *                            ETH_RECEIVED_FRAMES_LOST - will currently not reported
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Receive(
        uint8                                   CtrlIdx,
  P2VAR(Eth_RxStatusType, AUTOMATIC, AUTOMATIC) RxStatusPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_VTransmit
 **********************************************************************************************************************/
/*! \brief       Trigger the transmission of an Ethernet frame created from the passed buffer with a specific source MAC
 *  \details     Function takes the buffer previously provided by Eth_ProvideTxBuffer() enhances it with the Ethernet
 *               header (using a specific source MAC address instead of the Ethernet controllers one) and triggers the
 *               transmission of the Ethernet frame.
 *  \param[in]   CtrlIdx         Identifier of the Ethernet controller
 *  \param[in]   BufIdx          Identifier of the buffer provided by Eth_ProvideTxBuffer()
 *  \param[in]   FrameType       Ethernet type, according to type field of IEEE802.3
 *  \param[in]   TxConfirmation  Request for a transmission confirmation:
 *                               FALSE - No transmission confirmation desired
 *                               TRUE - Transmission confirmation desired
 *  \param[in]   LenByte         Length of the data to be transmitted (Payload length)
 *  \param[in]   PhysAddrDstPtr  Destination MAC address
 *  \param[in]   PhysAddrSrcPtr  Source MAC address
 *  \return      E_NOT_OK - Triggering of frame transmission wasn't possible
 *  \return      E_OK - Frame transmission triggered
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
 *  \pre         Buffer was acquired by Eth_ProvideTxBuffer()
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_VTransmit(
          uint8                               CtrlIdx,
          uint8                               BufIdx,
          Eth_FrameType                       FrameType,
          boolean                             TxConfirmation,
          uint16                              LenByte,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) PhysAddrDstPtr,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) PhysAddrSrcPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TxConfirmation
 **********************************************************************************************************************/
/*! \brief       Triggers the transmission confirmation of a previously Ethernet frame transmitted
 *  \details     Function triggers the transmission confirmation of a previously Ethernet frame transmitted and unlocks
 *               the buffer associated to the Ethernet frame so it is able to be used for frame transmission again.
 *  \param[in]   CtrlIdx  Identifier of the Ethernet controller
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TxConfirmation(
  uint8 CtrlIdx );

# if (ETH_30_TC3XX_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetVersionInfo
 **********************************************************************************************************************/
/*! \brief       Retrieves the version information of the component.
 *  \details     Function retrieves the Vendor ID, Module ID and software version of the component.
 *  \param[out]  VersionInfoPtr  Buffer to store the version information
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \trace       CREQ-137688
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, AUTOMATIC) VersionInfoPtr);
# endif /* ETH_30_TC3XX_VERSION_INFO_API */

# if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetRxStats()
 *********************************************************************************************************************/
/*! \brief       Returns list of reception statistics
 *  \details     Function returns the list of reception statistics from IETF RFC1213.
 *  \param[in]   CtrlIdx     Identifier of the Ethernet controller
 *  \param[out]  RxStatsPtr  List of read statistics values for reception
 *  \return      E_OK: success
 *               E_NOT_OK: RX-statistics could not be obtained
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \trace       CREQ-137827
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxStats(
        uint8                                  CtrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, AUTOMATIC) RxStatsPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetTxStats()
 *********************************************************************************************************************/
/*! \brief       Returns list of transmission statistics
 *  \details     Function returns the list of transmission statistics from IETF RFC1213.
 *  \param[in]   CtrlIdx     Identifier of the Ethernet controller
 *  \param[out]  TxStatsPtr  List of read statistics values for transmission
 *  \return      E_OK: success
 *               E_NOT_OK: TX-statistics could not be obtained
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \trace       CREQ-137827
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxStats(
        uint8                                  CtrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) TxStatsPtr);
# endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

# if (ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetAndResetMeasurementData
 **********************************************************************************************************************/
/*! \brief       To Get and/or Reset the Measurement statistics.
 *  \details     This function can be used to retrieve and/or reset the measurement data counter statistics that are
 *               supported.
 *  \param[in]   CtrlIdx         Identifier of the Ethernet controller
 *  \param[in]   MeasIdx         Identifier of the type of measurement data to be retrieved or reset
 *                ETH_MEAS_ALL - Only usable if ResetNeeded is TRUE, will reset all measured data
 *                ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TX_BUFFER - Reset and/or retrieve amount of denied Tx buffer
 *                  provision requests due to unavailable buffer resources
 *                ETH_MEAS_VENDOR_SPECIFIC_WARN_FULL_RX_BUFFER - Reset and/or retrieve amount of warning events which
 *                  indicate that all Rx buffers are blocked by the software
 *                ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_RX_BUFFER - Reset and/or retrieve a mount of Rx frames dropped
 *                  due to unavailable buffer resources
 *  \param[in]   ResetNeeded     Controls if the data determined by MeasIdx should be reset
 *                               FALSE - Reset of the data not requested
 *                               TRUE  - Reset of the data requested
 *  \param[out]  MeasurementData Pointer to store the retrieved measurement data
 *  \return      E_OK: Measurement data successfully retrieved or reset
 *               E_NOT_OK: Measurement data could not be retrieved or reset
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Module is initialized
 *  \trace       CREQ-242848
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAndResetMeasurementData(
        uint8                         CtrlIdx,
        Eth_MeasurementIdxType        MeasIdx,
        boolean                       ResetNeeded,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) MeasurementData);
# endif /* ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!
 * \exclusivearea ETH_30_TC3XX_EXCLUSIVE_AREA_DATA
 * Protects the consistency of data and sequences used in the Ethernet controller driver
 * \protects Global data consistency and sequences
 * \usedin   Eth_30_Tc3xx_SetFrameId, Eth_30_Tc3xx_Internal_ProvideTxBuffer, Eth_30_Tc3xx_Internal_VTransmit,
 *           Eth_30_Tc3xx_Internal_Receive, Eth_30_Tc3xx_Receive_ProcessValidFrame, Eth_30_Tc3xx_Internal_TxConfirmation
 * \exclude  Concurrent calls to the "usedin" functions.
 * \length LONG This exclusive area covers calls to several sub-functions.
 * \endexclusivearea
 *
 * \exclusivearea ETH_30_TC3XX_EXCLUSIVE_AREA_MII
 * Protects the consistency of the MII management access
 * \protects MII management read/write accesses that are performed asynchronously
 * \usedin   Eth_30_Tc3xx_Internal_WriteMii, Eth_30_Tc3xx_Internal_ReadMii
 * \exclude  Concurrent calls to the "usedin" functions.
 * \length MEDIUM This exclusive area covers the triggering of a MII management operation, the waiting for the operation
 *                to finish and the retrieval of the data
 * \endexclusivearea
 *
 */

#endif /* ETH_30_TC3XX_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx.h
 *********************************************************************************************************************/
