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
/*!        \file  EthIf_EthSwt.h
 *        \brief  EthIf EthSwt public API header
 *
 *      \details  Provides access to the public API of the sub-module EthSwt of EthIf.
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

#if !defined (ETHIF_ETHSWT_H)
# define ETHIF_ETHSWT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_EthSwt_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETHIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# if ( ETHIF_GET_PORT_MAC_ADDR_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_GetPortMacAddr
 **********************************************************************************************************************/
/*! \brief          Retrieves the switch port a MAC address is assigned to.
 *  \details        Function allows to retrieve the switch port a Ethernet node with the given MAC address is connected
 *                  to.
 *  \param[in]      MacAddrPtr    MAC address to be queried for
 *  \param[out]     SwitchIdxPtr  Pointer to store the switch the port belongs to
 *  \param[out]     PortIdxPtr    Pointer to store the port
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters or no port information found
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         ETHIF_GET_PORT_MAC_ADDR_API
 *  \trace          SPEC-2393873, SPEC-2393874
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetPortMacAddr(
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA)  MacAddrPtr,
    P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)   SwitchIdxPtr,
    P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)   PortIdxPtr);
# endif /* ETHIF_GET_PORT_MAC_ADDR_API */

# if ( ETHIF_GET_ARL_TABLE_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_GetArlTable
 **********************************************************************************************************************/
/*! \brief         Retrieves the complete address resolution table.
 *  \details       Function allows to retrieve the valid entries of the address resolution table of a switch
 *                 instance.
 *  \param[in]     SwitchIdx    Switch the ARL table shall be retrieved for
 *  \param[in,out] LenPtr       Pointer to length of the buffer passed:
 *                              [in] - Size of the passed buffer the entries shall be written to
 *                              [out] - Number of entries written into buffer
 *  \param[out]    ArlTablePtr  Pointer to the buffer the data shall be written to
 *  \return        E_OK - success
 *  \return        E_NOT_OK - function has been called with invalid parameters
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ETHIF_GET_ARL_TABLE_API
 *  \trace         SPEC-2394045, SPEC-2393879
 *  \trace         DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetArlTable(
        uint8                                            SwitchIdx,
  P2VAR(uint32,              AUTOMATIC, ETHIF_APPL_VAR)  LenPtr,
  P2VAR(EthSwt_MacVlanType,  AUTOMATIC, ETHIF_APPL_VAR)  ArlTablePtr);
# endif /* ETHIF_GET_ARL_TABLE_API */

# if ( ETHIF_GET_BUFFER_LEVEL_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_GetBufferLevel
 **********************************************************************************************************************/
/*! \brief         Reads the buffer level of the currently used buffer of the switch
 *  \details       Function reads the buffer level of the currently used buffer of the switch.
 *  \param[in]     SwitchIdx             Switch the buffer level shall be retrieved for
 *  \param[out]    SwitchBufferLevelPtr  The interpretation of this value is switch dependent
 *  \return        E_OK - success
 *  \return        E_NOT_OK - function has been called with invalid parameters
 *  \pre           Module and drivers have been initialized
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ETHIF_GET_BUFFER_LEVEL_API
 *  \trace         SPEC-2394047, SPEC-2393884
 *  \trace         DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetBufferLevel(
        uint8                                               SwitchIdx,
  P2VAR(EthSwt_BufferLevelType, AUTOMATIC, ETHIF_APPL_VAR)  SwitchBufferLevelPtr);
# endif /* ETHIF_GET_BUFFER_LEVEL_API */

# if ( ETHIF_GET_DROP_COUNT_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_GetDropCount
 **********************************************************************************************************************/
/*! \brief         Retrieves the drop counts according to the AUTOSAR SWS.
 *  \details       Function allows to retrieve the drop counts specified by the AUTOSAR SWS. Each count is the sum
 *                 of the drop count of all ports.
 *  \param[in]     SwitchIdx       Switch the drop counts shall be retrieved for
 *  \param[in,out] LenPtr          Pointer to the length of the buffer passed:
 *                                 [in] - Size of the passed buffer the drop counts shall be written to
 *                                 [out] - Number of drop counts written into buffer
 *  \param[out]    DropCountPtr    Pointer to the buffer the data shall be written to
 *  \return        E_OK - success
 *  \return        E_NOT_OK - function has been called with invalid parameters
 *  \pre           Module and drivers have been initialized
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ETHIF_GET_DROP_COUNT_API
 *  \trace         SPEC-2394049, SPEC-2393889
 *  \trace         DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetDropCount(
        uint8                               SwitchIdx,
  P2VAR(uint16, AUTOMATIC, ETHIF_APPL_VAR)  LenPtr,
  P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR)  DropCountPtr);
# endif /* ETHIF_GET_DROP_COUNT_API */

# if ( ETHIF_STORE_CONFIG_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_StoreConfiguration
 **********************************************************************************************************************/
/*! \brief         Calls EthSwt_StoreConfiguration() API of the related EthSwt-driver.
 *  \details       Function calls the EthSwt_StoreConfiguration() API of the related EthSwt-driver. Behavior
 *                 depends on the implementation of the driver. Commonly the latest MAC/Port table retrieved out of
 *                 the address resolution table of the switch is stored in NV RAM.
 *  \param[in]     SwitchIdx  Switch the configuration shall be stored for
 *  \return        E_OK - success
 *  \return        E_NOT_OK - function has been called with invalid parameters
 *  \pre           Module and drivers have been initialized
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ETHIF_STORE_CONFIG_API
 *  \trace         SPEC-2394051, SPEC-2393894
 *  \trace         DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_StoreConfiguration(
  uint8  SwitchIdx);
# endif /* ETHIF_STORE_CONFIG_API */

# if ( ETHIF_RESET_CONFIG_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_ResetConfiguration
 **********************************************************************************************************************/
/*! \brief         Calls EthSwt_ResetConfiguration() API of the related EthSwt-driver.
 *  \details       Function calls the EthSwt_ResetConfiguration() API of the related EthSwt-driver. Behavior
 *                 depends on the implementation of the driver. Commonly the MAC/Port table previously stored in NV RAM
 *                 triggered by EthIf_StoreConfiguration() is invalidated and switching behavior with regard to MACs
 *                 and VLANs is reset to initial (as defined by static configuration) behavior.
 *  \param[in]     SwitchIdx  Switch the configuration shall be invalidated for
 *  \return        E_OK - success
 *  \return        E_NOT_OK - function has been called with invalid parameters
 *  \pre           Module and drivers have been initialized
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ETHIF_RESET_CONFIG_API
 *  \trace         SPEC-2394053, SPEC-2393898
 *  \trace         DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_ResetConfiguration(
  uint8  SwitchIdx);
# endif /* ETHIF_RESET_CONFIG_API */

# if ( ETHIF_SWITCH_UPDATE_MCAST_PORT_ASSIGN_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_SwitchUpdateMCastPortAssignment
 **********************************************************************************************************************/
/*! \brief         Updates the multicast assignment for a specific port.
 *  \details       Function updates the multicast assignment for a specific Ethernet switch port.
 *  \param[in]     SwitchIdx  Index of the EthIf switch
 *  \param[in]     PortIdx    Index of the Ethernet Switch Port
 *  \param[in]     MCastAddr  Pointer to the multicast address
 *  \param[in]     Action     Action that shall be applied:
 *                            ETHSWT_MCAST_PORT_ASSIGN_ACTION_ADD - Request passing of multicast on the port
 *                            ETHSWT_MCAST_PORT_ASSIGN_ACTION_REMOVE - Request removal of multicast on the port
 *  \return        E_OK - success
 *  \return        E_NOT_OK - function has been called with invalid parameters
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ETHIF_SWITCH_UPDATE_MCAST_PORT_ASSIGN_API
 *  \trace         DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchUpdateMCastPortAssignment(
          uint8                              SwitchIdx,
          uint8                              PortIdx,
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA) MCastAddr,
          EthSwt_MCastPortAssignActionType   Action);
# endif /* ETHIF_SWITCH_UPDATE_MCAST_PORT_ASSIGN_API */

# if ( ETHIF_SWITCH_ENABLE_VLAN_API == STD_ON )
/**********************************************************************************************************************
 * EthIf_SwitchEnableVlan
 **********************************************************************************************************************/
/*! \brief         Enables or disables a VLAN on a port.
 *  \details       Function enables or disables a VLAN on a specific switch port.
 *  \param[in]     SwitchIdx  Index of the EthIf switch
 *  \param[in]     PortIdx    Index of the Ethernet Switch Port
 *  \param[in]     VlanId     VLAN identifier for which the configuration shall be performed
 *  \param[in]     Enable     Configuration that shall be applied:
 *                            TRUE - VLAN-configuration enabled
 *                            FALSE - VLAN-configuration disabled
 *  \return        E_OK - success
 *  \return        E_NOT_OK - VLAN configuration could not be performed
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ETHIF_SWITCH_ENABLE_VLAN_API
 *  \trace         DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchEnableVlan(
  uint8   SwitchIdx,
  uint8   PortIdx,
  uint16  VlanId,
  boolean Enable);
# endif /* ETHIF_SWITCH_ENABLE_VLAN_API */

# if ( ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT == STD_ON )
/**********************************************************************************************************************
 * EthIf_SetSwitchMgmtInfo
 **********************************************************************************************************************/
/*! \brief          Sets management information for a frame identified by the EthIf controller and the
 *                  Ethernet buffer index.
 *  \details        Function allows to apply special treatment for an Ethernet frame. The frame is identified by
 *                  the EthIf controller and the Ethernet buffer index. This function can only be called between a
 *                  EthIf_ProvideTxBuffer() and EthIf_Transmit().
 *  \param[in]      CtrlIdx      Index of the EthIf controller
 *  \param[in]      BufIdx       Index of the Ethernet Tx buffer retrieved during EthIf_ProvideTxBuffer()
 *  \param[in]      MgmtInfoPtr  Switch Management information
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            Buffer has to be acquired with EthIf_ProvideTxBuffer()
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT
 *  \note           Further context restrictions:
 *                  Call only allowed between EthIf_ProvideTxBuffer()/EthIf_ProvideExtTxBuffer() and EthIf_Transmit()
 *                  for a specific frame
 *  \trace          DSGN-EthIf22903
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetSwitchMgmtInfo(
        uint8                                            CtrlIdx,
        Eth_BufIdxType                                   BufIdx,
  P2VAR(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_VAR)  MgmtInfoPtr); /* PRQA S 3673 */ /* MD_EthIf_3673 */

/***********************************************************************************************************************
 *  EthIf_GetRxMgmtObject
 **********************************************************************************************************************/
/*! \brief          Provides access to a reception switch management object
 *  \details        Function allows to gain access to the reception switch management object provided by the related
 *                  Ethernet switch driver. This function can only be called in context of <User>_RxIndication().
 *  \param[in]      CtrlIdx        EthIf controller the frame is assigned to
 *  \param[in]      DataPtr        Pointer to the frame payload for identifying the frame
 *  \param[out]     MgmtObjectPtr  Switch management object provided by the Ethernet switch driver
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function called with invalid parameters
 *  \pre            -
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT
 *  \note           Further restriction of context:
 *                  Call only allowed in <User>_RxIndication()
 *  \trace          SPEC-8002621
 *  \trace          DSGN-EthIf23123, DSGN-EthIf23124
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetRxMgmtObject(
        uint8                                                                               CtrlIdx,
  P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR)                                            DataPtr,
  P2VAR(P2VAR(EthSwt_MgmtObjectType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR) MgmtObjectPtr);

/**********************************************************************************************************************
 * EthIf_GetTxMgmtObject
 **********************************************************************************************************************/
/*! \brief          Provides access to a transmission switch management object
 *  \details        Function allows to gain access to the transmission switch management object provided by the
 *                  related Ethernet switch driver. This function can only be called between a EthIf_ProvideTxBuffer()
 *                  and EthIf_Transmit().
 *  \param[in]      CtrlIdx        Index of the EthIf controller
 *  \param[in]      BufIdx         Index of the Ethernet Tx buffer retrieved during EthIf_ProvideTxBuffer()
 *  \param[out]     MgmtObjectPtr  Switch management object provided by the Ethernet switch driver
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            Buffer has to be acquired with EthIf_ProvideTxBuffer()
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT
 *  \note           Further context restrictions:
 *                  Call only allowed between EthIf_ProvideTxBuffer()/EthIf_ProvideExtTxBuffer() and EthIf_Transmit()
 *                  for a specific frame
 *  \trace          SPEC-8002622
 *  \trace          DSGN-EthIf23123
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetTxMgmtObject(
        uint8                                                                               CtrlIdx,
        Eth_BufIdxType                                                                      BufIdx,
  P2VAR(P2VAR(EthSwt_MgmtObjectType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR) MgmtObjectPtr);
# endif /* ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT */

# if ( ETHIF_ETHSWT_TIME_STAMP_SUPPORT == STD_ON )
/**********************************************************************************************************************
 * EthIf_SwitchEnableTimeStamping
 **********************************************************************************************************************/
/*! \brief          Enables time stamping within the Ethernet switch for an Ethernet frame.
 *  \details        Function enables time stamping for an Ethernet frame identified by the buffer index on the
 *                  port described by the management information.
 *  \param[in]      CtrlIdx  Index of the EthIf controller
 *  \param[in]      BufIdx        Index of the Ethernet Tx buffer retrieved during EthIf_ProvideTxBuffer()
 *  \param[in]      MgmtInfo      Switch Management information
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            Buffer has to be acquired with EthIf_ProvideTxBuffer()
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         ETHIF_ETHSWT_TIME_STAMP_SUPPORT
 *  \note           Further context restriction:
 *                  Call only allowed between EthIf_ProvideTxBuffer()/EthIf_ProvideExtTxBuffer() and EthIf_Transmit()
 *                  for a specific frame
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchEnableTimeStamping(
          uint8                                          CtrlIdx,
          Eth_BufIdxType                                 BufIdx,
  P2VAR(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_VAR)  MgmtInfo); /* PRQA S 3673 */ /* MD_EthIf_3673 */

/**********************************************************************************************************************
 * EthIf_SwitchSetCorrectionTime
 **********************************************************************************************************************/
/*! \brief          Corrects the clock of the Ethernet switch.
 *  \details        Function triggers the correction of the clock of the Ethernet switch either by an offset or by
 *                  a rate or both.
 *  \param[in]      EthIfSwtIdx   Index of the EthIf switch
 *  \param[in]      OffsetPtr     Pointer to the offset the clock shall be corrected with. NULL_PTR if no offset
 *                                correction shall be done.
 *  \param[in]      RateRatioPtr  Pointer to the rate the clock shall be corrected with. NULL_PTR if no rate correction
 *                                shall be done.
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters or correction can't be applied because
 *                             it is not in a range the hardware is able to handle
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         ETHIF_ETHSWT_TIME_STAMP_SUPPORT
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchSetCorrectionTime(
          uint8                                             EthIfSwtIdx,
  P2CONST(Eth_TimeIntDiffType, AUTOMATIC, ETHIF_APPL_DATA)  OffsetPtr,
  P2CONST(float64,             AUTOMATIC, ETHIF_APPL_DATA)  RateRatioPtr);

/**********************************************************************************************************************
 * EthIf_StartSwitchQbvSchedule
 **********************************************************************************************************************/
/*! \brief          Starts the IEEE802.1Qbv schedule of the Ethernet switch.
 *  \details        Function triggers the start of the IEEE802.1Qbv schedule of the Ethernet switch.
 *  \param[in]      EthIfSwtIdx   Index of the EthIf switch
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters or Ethernet switch isn't in a state
 *                             allowing to start the schedule
 *  \pre            The Ethernet switch must have been synchronized to the global time.
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         ETHIF_ETHSWT_TIME_STAMP_SUPPORT
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_StartSwitchQbvSchedule(
  uint8  EthIfSwtIdx);

/**********************************************************************************************************************
 * EthIf_StopSwitchQbvSchedule
 **********************************************************************************************************************/
/*! \brief          Stops the IEEE802.1Qbv schedule of the Ethernet switch.
 *  \details        Function triggers the stop of the IEEE802.1Qbv schedule of the Ethernet switch.
 *  \param[in]      EthIfSwtIdx   Index of the EthIf switch
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters or Ethernet switch isn't in a state
 *                             allowing to stop the schedule
 *  \pre            The IEEE802.1Qbv schedule must have been started previously.
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         ETHIF_ETHSWT_TIME_STAMP_SUPPORT
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_StopSwitchQbvSchedule(
  uint8  EthIfSwtIdx);

# endif /* ETHIF_ETHSWT_TIME_STAMP_SUPPORT */

# if ( ETHIF_ENABLE_SIGNAL_QUALITY_API == STD_ON )
/**********************************************************************************************************************
*  EthIf_GetSwitchPortSignalQuality
*********************************************************************************************************************/
/*! \brief          Retrieves the signal quality of the link of the given Ethernet switch port and update the measured 
 *                  signal quality stored in EthIf.
 *  \details        Function allows to retrieve the signal quality of the link of the given Ethernet switch port by 
 *                  redirecting the call depending on the passed switch index and switch port index. 
 *                  The highest signal quality and the lowest signal quality will be updated depending on the 
 *                  currently retrieved signal quality. Function is reentrant for different Ethernet switch indexes 
 *                  and Ethernet Switch port indexes, non reentrant for the same SwitchPortIdx.
 *  \param[in]      SwitchIdx      Index of the Ethernet switch within the context of the Ethernet Interface
 *  \param[in]      SwitchPortIdx  Index of the port at the addressed switch
 *  \param[out]     ResultPtr      Pointer to the memory where the signal quality in percent shall be stored.
 *  \return         E_OK - success
 *  \return         E_NOT_OK - The signal quality not retrieved successfully
 *  \pre            EthIf is initialized
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-8002642
 *********************************************************************************************************************/
Std_ReturnType EthIf_GetSwitchPortSignalQuality(
        uint8 SwitchIdx,
        uint8 SwitchPortIdx,
  P2VAR(EthIf_SignalQualityResultType, AUTOMATIC, ETHIF_APPL_VAR) ResultPtr);

/**********************************************************************************************************************
*  EthIf_ClearSwitchPortSignalQuality
*********************************************************************************************************************/
/*! \brief          Clear the stored signal quality of the link of the given Ethernet switch port.
 *  \details        Function clears the in Ethernet interface stored signal quality of the link of the given Ethernet
 *                  switch port. Function is reentrant for different Ethernet switch indexes and Ethernet Switch port 
 *                  indexes, non reentrant for the same SwitchPortIdx.
 *  \param[in]      SwitchIdx      Index of the Ethernet switch within the context of the Ethernet Interface
 *  \param[in]      SwitchPortIdx  Index of the port at the addressed switch
 *  \return         E_OK - success
 *  \return         E_NOT_OK - The signal quality not cleared successfully
 *  \pre            EthIf is initialized
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-8002651
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_ClearSwitchPortSignalQuality(
  uint8 SwitchIdx,
  uint8 SwitchPortIdx);

/**********************************************************************************************************************
 *  EthIf_PollPortSignalQualities
 *********************************************************************************************************************/
/*! \brief          Poll the signal quality of Ethernet switch ports
 *  \details        This function polls the signal quality of the Ethernet switch ports by utilizing the respective
 *                  hardware driver.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_PollPortSignalQualities( void );

/**********************************************************************************************************************
 *  EthIf_PortSignalQualityList_Init
 *********************************************************************************************************************/
/*! \brief          Initialization of the signal quality of all switch ports
 *  \details        Initialization of the signal quality of all switch ports. The values of the signal qualities are
 *                  stored in the Ethernet interface as a list. The index of the list is the port index within the
 *                  context of Ethernet interface.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_PortSignalQualityList_Init( void );

/**********************************************************************************************************************
 *  EthIf_QueryForPortIndex
 *********************************************************************************************************************/
/*! \brief          Query the port index within the context of Ethernet interface
 *  \details        This function get the port index within the context of Ethernet interface using the switch index
 *                  within the context of Ethernet interface and the port index in the context of Ethernet switch.
 *  \param[in]      switchIdx      Index of the switch within the context of the Ethernet interface
 *  \param[in]      switchPortIdx  Index of the port within the context of the Ethernet switch
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(EthIf_EthSwtPortIterType, ETHIF_CODE) EthIf_QueryForPortIndex(
  uint8 switchIdx,
  uint8 switchPortIdx);

# endif /* ETHIF_ENABLE_SIGNAL_QUALITY_API */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_ETHSWT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_EthSwt.h
 *********************************************************************************************************************/

