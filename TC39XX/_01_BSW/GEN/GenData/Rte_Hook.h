/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  Rte_Hook.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Header file containing definitions for VFB tracing
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Names of available VFB-Trace-Hooks
 **********************************************************************************************************************
 *
 * Not configured:
 *
 *  Rte_ReadHook_BswM_Request_ESH_PostRunRequest_0_requestedMode_Return
 *  Rte_ReadHook_BswM_Request_ESH_PostRunRequest_0_requestedMode_Start
 *  Rte_ReadHook_BswM_Request_ESH_PostRunRequest_1_requestedMode_Return
 *  Rte_ReadHook_BswM_Request_ESH_PostRunRequest_1_requestedMode_Start
 *  Rte_ReadHook_BswM_Request_ESH_RunRequest_0_requestedMode_Return
 *  Rte_ReadHook_BswM_Request_ESH_RunRequest_0_requestedMode_Start
 *  Rte_ReadHook_BswM_Request_ESH_RunRequest_1_requestedMode_Return
 *  Rte_ReadHook_BswM_Request_ESH_RunRequest_1_requestedMode_Start
 *  Rte_Runnable_BswM_BswM_MainFunction_Return
 *  Rte_Runnable_BswM_BswM_MainFunction_Start
 *  Rte_Runnable_Cdd_Core0_Cdd_Core0_Init_Return
 *  Rte_Runnable_Cdd_Core0_Cdd_Core0_Init_Start
 *  Rte_Runnable_Cdd_Core0_Runnable_20_Return
 *  Rte_Runnable_Cdd_Core0_Runnable_20_Start
 *  Rte_Runnable_Cdd_Core0_Runnable_5ms_Return
 *  Rte_Runnable_Cdd_Core0_Runnable_5ms_Start
 *  Rte_Runnable_Cdd_Core1_Cdd_Core1_Init_Return
 *  Rte_Runnable_Cdd_Core1_Cdd_Core1_Init_Start
 *  Rte_Runnable_Cdd_Core1_Cdd_Core1_Runnable10ms_Return
 *  Rte_Runnable_Cdd_Core1_Cdd_Core1_Runnable10ms_Start
 *  Rte_Runnable_Cdd_Core2_Cdd_Core2_Init_Return
 *  Rte_Runnable_Cdd_Core2_Cdd_Core2_Init_Start
 *  Rte_Runnable_Cdd_Core2_Cdd_Core2_Runnable10ms_Return
 *  Rte_Runnable_Cdd_Core2_Cdd_Core2_Runnable10ms_Start
 *  Rte_Runnable_Cdd_Core3_Cdd_Core3_Init_Return
 *  Rte_Runnable_Cdd_Core3_Cdd_Core3_Init_Start
 *  Rte_Runnable_Cdd_Core3_Cdd_Core3_Runnable10ms_Return
 *  Rte_Runnable_Cdd_Core3_Cdd_Core3_Runnable10ms_Start
 *  Rte_Runnable_Cdd_Core4_Cdd_Core4_Init_Return
 *  Rte_Runnable_Cdd_Core4_Cdd_Core4_Init_Start
 *  Rte_Runnable_Cdd_Core4_Cdd_Core4_Runnable10ms_Return
 *  Rte_Runnable_Cdd_Core4_Cdd_Core4_Runnable10ms_Start
 *  Rte_Runnable_Cdd_Core5_Cdd_Core5_Init_Return
 *  Rte_Runnable_Cdd_Core5_Cdd_Core5_Init_Start
 *  Rte_Runnable_Cdd_Core5_Cdd_Core5_Runnable10ms_Return
 *  Rte_Runnable_Cdd_Core5_Cdd_Core5_Runnable10ms_Start
 *  Rte_Runnable_Cdd_Nm_Cdd_Nm_Init_Return
 *  Rte_Runnable_Cdd_Nm_Cdd_Nm_Init_Start
 *  Rte_Runnable_Cdd_Nm_Cdd_Nm_Runnable10ms_Return
 *  Rte_Runnable_Cdd_Nm_Cdd_Nm_Runnable10ms_Start
 *  Rte_Runnable_ComM_ComM_MainFunction_0_Return
 *  Rte_Runnable_ComM_ComM_MainFunction_0_Start
 *  Rte_Runnable_ComM_GetCurrentComMode_Return
 *  Rte_Runnable_ComM_GetCurrentComMode_Start
 *  Rte_Runnable_ComM_GetInhibitionStatus_Return
 *  Rte_Runnable_ComM_GetInhibitionStatus_Start
 *  Rte_Runnable_ComM_GetMaxComMode_Return
 *  Rte_Runnable_ComM_GetMaxComMode_Start
 *  Rte_Runnable_ComM_GetRequestedComMode_Return
 *  Rte_Runnable_ComM_GetRequestedComMode_Start
 *  Rte_Runnable_ComM_LimitChannelToNoComMode_Return
 *  Rte_Runnable_ComM_LimitChannelToNoComMode_Start
 *  Rte_Runnable_ComM_LimitECUToNoComMode_Return
 *  Rte_Runnable_ComM_LimitECUToNoComMode_Start
 *  Rte_Runnable_ComM_PreventWakeUp_Return
 *  Rte_Runnable_ComM_PreventWakeUp_Start
 *  Rte_Runnable_ComM_ReadInhibitCounter_Return
 *  Rte_Runnable_ComM_ReadInhibitCounter_Start
 *  Rte_Runnable_ComM_RequestComMode_Return
 *  Rte_Runnable_ComM_RequestComMode_Start
 *  Rte_Runnable_ComM_ResetInhibitCounter_Return
 *  Rte_Runnable_ComM_ResetInhibitCounter_Start
 *  Rte_Runnable_ComM_SetECUGroupClassification_Return
 *  Rte_Runnable_ComM_SetECUGroupClassification_Start
 *  Rte_Runnable_EcuM_EcuM_MainFunction_Return
 *  Rte_Runnable_EcuM_EcuM_MainFunction_Start
 *  Rte_Runnable_EcuM_GetBootTarget_Return
 *  Rte_Runnable_EcuM_GetBootTarget_Start
 *  Rte_Runnable_EcuM_GetLastShutdownTarget_Return
 *  Rte_Runnable_EcuM_GetLastShutdownTarget_Start
 *  Rte_Runnable_EcuM_GetShutdownCause_Return
 *  Rte_Runnable_EcuM_GetShutdownCause_Start
 *  Rte_Runnable_EcuM_GetShutdownTarget_Return
 *  Rte_Runnable_EcuM_GetShutdownTarget_Start
 *  Rte_Runnable_EcuM_SelectBootTarget_Return
 *  Rte_Runnable_EcuM_SelectBootTarget_Start
 *  Rte_Runnable_EcuM_SelectShutdownCause_Return
 *  Rte_Runnable_EcuM_SelectShutdownCause_Start
 *  Rte_Runnable_EcuM_SelectShutdownTarget_Return
 *  Rte_Runnable_EcuM_SelectShutdownTarget_Start
 *  Rte_Runnable_Os_OsCore0_swc_GetCounterValue_Return
 *  Rte_Runnable_Os_OsCore0_swc_GetCounterValue_Start
 *  Rte_Runnable_Os_OsCore0_swc_GetElapsedValue_Return
 *  Rte_Runnable_Os_OsCore0_swc_GetElapsedValue_Start
 *  Rte_Runnable_Os_OsCore1_swc_GetCounterValue_Return
 *  Rte_Runnable_Os_OsCore1_swc_GetCounterValue_Start
 *  Rte_Runnable_Os_OsCore1_swc_GetElapsedValue_Return
 *  Rte_Runnable_Os_OsCore1_swc_GetElapsedValue_Start
 *  Rte_Runnable_Os_OsCore2_swc_GetCounterValue_Return
 *  Rte_Runnable_Os_OsCore2_swc_GetCounterValue_Start
 *  Rte_Runnable_Os_OsCore2_swc_GetElapsedValue_Return
 *  Rte_Runnable_Os_OsCore2_swc_GetElapsedValue_Start
 *  Rte_Runnable_Os_OsCore3_swc_GetCounterValue_Return
 *  Rte_Runnable_Os_OsCore3_swc_GetCounterValue_Start
 *  Rte_Runnable_Os_OsCore3_swc_GetElapsedValue_Return
 *  Rte_Runnable_Os_OsCore3_swc_GetElapsedValue_Start
 *  Rte_Runnable_Os_OsCore4_swc_GetCounterValue_Return
 *  Rte_Runnable_Os_OsCore4_swc_GetCounterValue_Start
 *  Rte_Runnable_Os_OsCore4_swc_GetElapsedValue_Return
 *  Rte_Runnable_Os_OsCore4_swc_GetElapsedValue_Start
 *  Rte_Runnable_Os_OsCore5_swc_GetCounterValue_Return
 *  Rte_Runnable_Os_OsCore5_swc_GetCounterValue_Start
 *  Rte_Runnable_Os_OsCore5_swc_GetElapsedValue_Return
 *  Rte_Runnable_Os_OsCore5_swc_GetElapsedValue_Start
 *  Rte_Runnable_StbM_GetCurrentTime_Return
 *  Rte_Runnable_StbM_GetCurrentTime_Start
 *  Rte_Runnable_StbM_GetRateDeviation_Return
 *  Rte_Runnable_StbM_GetRateDeviation_Start
 *  Rte_Runnable_StbM_GetTimeBaseStatus_Return
 *  Rte_Runnable_StbM_GetTimeBaseStatus_Start
 *  Rte_Runnable_StbM_GetTimeLeap_Return
 *  Rte_Runnable_StbM_GetTimeLeap_Start
 *  Rte_Runnable_StbM_StbM_MainFunction_Return
 *  Rte_Runnable_StbM_StbM_MainFunction_Start
 *  Rte_Runnable_lock_control_Runnable_2ms_Return
 *  Rte_Runnable_lock_control_Runnable_2ms_Start
 *  Rte_Runnable_lock_control_lock_control_Init_Return
 *  Rte_Runnable_lock_control_lock_control_Init_Start
 *  Rte_Runnable_window_core1_Runnable_windows_2ms_Return
 *  Rte_Runnable_window_core1_Runnable_windows_2ms_Start
 *  Rte_Runnable_window_core1_window_core1_Init_Return
 *  Rte_Runnable_window_core1_window_core1_Init_Start
 *  Rte_SwitchHook_BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode_Return
 *  Rte_SwitchHook_BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode_Start
 *  Rte_Task_Activate
 *  Rte_Task_Dispatch
 *  Rte_Task_Terminate
 *  Rte_Task_WaitEvent
 *  Rte_Task_WaitEventRet
 *  Rte_WriteHook_Cdd_Nm_BswM_SRI_BswM_MSI_ESH_Mode_BswM_MDGP_ESH_Mode_requestedMode_Return
 *  Rte_WriteHook_Cdd_Nm_BswM_SRI_BswM_MSI_ESH_Mode_BswM_MDGP_ESH_Mode_requestedMode_Start
 *  Rte_WriteHook_Cdd_Nm_BswM_SRI_BswM_MSI_ESH_RunRequest_BswM_MDGP_ESH_RunRequest_requestedMode_Return
 *  Rte_WriteHook_Cdd_Nm_BswM_SRI_BswM_MSI_ESH_RunRequest_BswM_MDGP_ESH_RunRequest_requestedMode_Start
 *  SchM_EnterHook_BswM_BSWM_EXCLUSIVE_AREA_0_Return
 *  SchM_EnterHook_BswM_BSWM_EXCLUSIVE_AREA_0_Start
 *  SchM_EnterHook_ComM_COMM_EXCLUSIVE_AREA_0_Return
 *  SchM_EnterHook_ComM_COMM_EXCLUSIVE_AREA_0_Start
 *  SchM_EnterHook_ComM_COMM_EXCLUSIVE_AREA_1_Return
 *  SchM_EnterHook_ComM_COMM_EXCLUSIVE_AREA_1_Start
 *  SchM_EnterHook_Com_COM_EXCLUSIVE_AREA_BOTH_Return
 *  SchM_EnterHook_Com_COM_EXCLUSIVE_AREA_BOTH_Start
 *  SchM_EnterHook_Com_COM_EXCLUSIVE_AREA_RX_Return
 *  SchM_EnterHook_Com_COM_EXCLUSIVE_AREA_RX_Start
 *  SchM_EnterHook_Com_COM_EXCLUSIVE_AREA_TX_Return
 *  SchM_EnterHook_Com_COM_EXCLUSIVE_AREA_TX_Start
 *  SchM_EnterHook_Det_DET_EXCLUSIVE_AREA_0_Return
 *  SchM_EnterHook_Det_DET_EXCLUSIVE_AREA_0_Start
 *  SchM_EnterHook_EcuM_ECUM_EXCLUSIVE_AREA_0_Return
 *  SchM_EnterHook_EcuM_ECUM_EXCLUSIVE_AREA_0_Start
 *  SchM_EnterHook_EcuM_ECUM_EXCLUSIVE_AREA_1_Return
 *  SchM_EnterHook_EcuM_ECUM_EXCLUSIVE_AREA_1_Start
 *  SchM_EnterHook_EcuM_ECUM_EXCLUSIVE_AREA_2_Return
 *  SchM_EnterHook_EcuM_ECUM_EXCLUSIVE_AREA_2_Start
 *  SchM_EnterHook_EcuM_ECUM_EXCLUSIVE_AREA_3_Return
 *  SchM_EnterHook_EcuM_ECUM_EXCLUSIVE_AREA_3_Start
 *  SchM_EnterHook_EthIf_ETHIF_EXCLUSIVE_AREA_CTRL_INIT_Return
 *  SchM_EnterHook_EthIf_ETHIF_EXCLUSIVE_AREA_CTRL_INIT_Start
 *  SchM_EnterHook_EthIf_ETHIF_EXCLUSIVE_AREA_RXTX_STATS_Return
 *  SchM_EnterHook_EthIf_ETHIF_EXCLUSIVE_AREA_RXTX_STATS_Start
 *  SchM_EnterHook_EthIf_ETHIF_EXCLUSIVE_AREA_SET_CTRL_MODE_Return
 *  SchM_EnterHook_EthIf_ETHIF_EXCLUSIVE_AREA_SET_CTRL_MODE_Start
 *  SchM_EnterHook_EthIf_ETHIF_EXCLUSIVE_AREA_SIGNAL_QUALITY_Return
 *  SchM_EnterHook_EthIf_ETHIF_EXCLUSIVE_AREA_SIGNAL_QUALITY_Start
 *  SchM_EnterHook_EthIf_ETHIF_EXCLUSIVE_AREA_TX_MIRROR_ELEMENT_Return
 *  SchM_EnterHook_EthIf_ETHIF_EXCLUSIVE_AREA_TX_MIRROR_ELEMENT_Start
 *  SchM_EnterHook_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_0_Return
 *  SchM_EnterHook_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_0_Start
 *  SchM_EnterHook_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_GET_TS_Return
 *  SchM_EnterHook_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_GET_TS_Start
 *  SchM_EnterHook_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_TIME_VALID_Return
 *  SchM_EnterHook_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_TIME_VALID_Start
 *  SchM_EnterHook_EthTrcv_30_Tja1100_ETHTRCV_30_TJA1100_EXCLUSIVE_AREA_SEQUENCE_Return
 *  SchM_EnterHook_EthTrcv_30_Tja1100_ETHTRCV_30_TJA1100_EXCLUSIVE_AREA_SEQUENCE_Start
 *  SchM_EnterHook_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_DATA_Return
 *  SchM_EnterHook_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_DATA_Start
 *  SchM_EnterHook_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_DISABLE_MAC_Return
 *  SchM_EnterHook_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_DISABLE_MAC_Start
 *  SchM_EnterHook_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_MII_Return
 *  SchM_EnterHook_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_MII_Start
 *  SchM_EnterHook_McalLib_CpuEndInit_Return
 *  SchM_EnterHook_McalLib_CpuEndInit_Start
 *  SchM_EnterHook_McalLib_PeripheralEndInit_Return
 *  SchM_EnterHook_McalLib_PeripheralEndInit_Start
 *  SchM_EnterHook_McalLib_SafetyEndInit_Return
 *  SchM_EnterHook_McalLib_SafetyEndInit_Start
 *  SchM_EnterHook_McalLib_StmTimerResolution_Return
 *  SchM_EnterHook_McalLib_StmTimerResolution_Start
 *  SchM_EnterHook_Mcu_AtomAgcReg_Return
 *  SchM_EnterHook_Mcu_AtomAgcReg_Start
 *  SchM_EnterHook_Mcu_TomTgcReg_Return
 *  SchM_EnterHook_Mcu_TomTgcReg_Start
 *  SchM_EnterHook_Nm_NM_EXCLUSIVE_AREA_0_Return
 *  SchM_EnterHook_Nm_NM_EXCLUSIVE_AREA_0_Start
 *  SchM_EnterHook_Nm_NM_EXCLUSIVE_AREA_1_Return
 *  SchM_EnterHook_Nm_NM_EXCLUSIVE_AREA_1_Start
 *  SchM_EnterHook_PduR_PDUR_EXCLUSIVE_AREA_0_Return
 *  SchM_EnterHook_PduR_PDUR_EXCLUSIVE_AREA_0_Start
 *  SchM_EnterHook_SoAd_SOAD_EXCLUSIVE_AREA_0_Return
 *  SchM_EnterHook_SoAd_SOAD_EXCLUSIVE_AREA_0_Start
 *  SchM_EnterHook_SoAd_SOAD_EXCLUSIVE_AREA_1_Return
 *  SchM_EnterHook_SoAd_SOAD_EXCLUSIVE_AREA_1_Start
 *  SchM_EnterHook_StbM_STBM_EXCLUSIVE_AREA_0_Return
 *  SchM_EnterHook_StbM_STBM_EXCLUSIVE_AREA_0_Start
 *  SchM_EnterHook_TcpIp_TCPIP_EXCLUSIVE_AREA_0_Return
 *  SchM_EnterHook_TcpIp_TCPIP_EXCLUSIVE_AREA_0_Start
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_0_Return
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_0_Start
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_1_Return
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_1_Start
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_2_Return
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_2_Start
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_3_Return
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_3_Start
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_4_Return
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_4_Start
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_5_Return
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_5_Start
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_6_Return
 *  SchM_EnterHook_UdpNm_UDPNM_EXCLUSIVE_AREA_6_Start
 *  SchM_ExitHook_BswM_BSWM_EXCLUSIVE_AREA_0_Return
 *  SchM_ExitHook_BswM_BSWM_EXCLUSIVE_AREA_0_Start
 *  SchM_ExitHook_ComM_COMM_EXCLUSIVE_AREA_0_Return
 *  SchM_ExitHook_ComM_COMM_EXCLUSIVE_AREA_0_Start
 *  SchM_ExitHook_ComM_COMM_EXCLUSIVE_AREA_1_Return
 *  SchM_ExitHook_ComM_COMM_EXCLUSIVE_AREA_1_Start
 *  SchM_ExitHook_Com_COM_EXCLUSIVE_AREA_BOTH_Return
 *  SchM_ExitHook_Com_COM_EXCLUSIVE_AREA_BOTH_Start
 *  SchM_ExitHook_Com_COM_EXCLUSIVE_AREA_RX_Return
 *  SchM_ExitHook_Com_COM_EXCLUSIVE_AREA_RX_Start
 *  SchM_ExitHook_Com_COM_EXCLUSIVE_AREA_TX_Return
 *  SchM_ExitHook_Com_COM_EXCLUSIVE_AREA_TX_Start
 *  SchM_ExitHook_Det_DET_EXCLUSIVE_AREA_0_Return
 *  SchM_ExitHook_Det_DET_EXCLUSIVE_AREA_0_Start
 *  SchM_ExitHook_EcuM_ECUM_EXCLUSIVE_AREA_0_Return
 *  SchM_ExitHook_EcuM_ECUM_EXCLUSIVE_AREA_0_Start
 *  SchM_ExitHook_EcuM_ECUM_EXCLUSIVE_AREA_1_Return
 *  SchM_ExitHook_EcuM_ECUM_EXCLUSIVE_AREA_1_Start
 *  SchM_ExitHook_EcuM_ECUM_EXCLUSIVE_AREA_2_Return
 *  SchM_ExitHook_EcuM_ECUM_EXCLUSIVE_AREA_2_Start
 *  SchM_ExitHook_EcuM_ECUM_EXCLUSIVE_AREA_3_Return
 *  SchM_ExitHook_EcuM_ECUM_EXCLUSIVE_AREA_3_Start
 *  SchM_ExitHook_EthIf_ETHIF_EXCLUSIVE_AREA_CTRL_INIT_Return
 *  SchM_ExitHook_EthIf_ETHIF_EXCLUSIVE_AREA_CTRL_INIT_Start
 *  SchM_ExitHook_EthIf_ETHIF_EXCLUSIVE_AREA_RXTX_STATS_Return
 *  SchM_ExitHook_EthIf_ETHIF_EXCLUSIVE_AREA_RXTX_STATS_Start
 *  SchM_ExitHook_EthIf_ETHIF_EXCLUSIVE_AREA_SET_CTRL_MODE_Return
 *  SchM_ExitHook_EthIf_ETHIF_EXCLUSIVE_AREA_SET_CTRL_MODE_Start
 *  SchM_ExitHook_EthIf_ETHIF_EXCLUSIVE_AREA_SIGNAL_QUALITY_Return
 *  SchM_ExitHook_EthIf_ETHIF_EXCLUSIVE_AREA_SIGNAL_QUALITY_Start
 *  SchM_ExitHook_EthIf_ETHIF_EXCLUSIVE_AREA_TX_MIRROR_ELEMENT_Return
 *  SchM_ExitHook_EthIf_ETHIF_EXCLUSIVE_AREA_TX_MIRROR_ELEMENT_Start
 *  SchM_ExitHook_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_0_Return
 *  SchM_ExitHook_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_0_Start
 *  SchM_ExitHook_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_GET_TS_Return
 *  SchM_ExitHook_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_GET_TS_Start
 *  SchM_ExitHook_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_TIME_VALID_Return
 *  SchM_ExitHook_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_TIME_VALID_Start
 *  SchM_ExitHook_EthTrcv_30_Tja1100_ETHTRCV_30_TJA1100_EXCLUSIVE_AREA_SEQUENCE_Return
 *  SchM_ExitHook_EthTrcv_30_Tja1100_ETHTRCV_30_TJA1100_EXCLUSIVE_AREA_SEQUENCE_Start
 *  SchM_ExitHook_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_DATA_Return
 *  SchM_ExitHook_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_DATA_Start
 *  SchM_ExitHook_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_DISABLE_MAC_Return
 *  SchM_ExitHook_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_DISABLE_MAC_Start
 *  SchM_ExitHook_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_MII_Return
 *  SchM_ExitHook_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_MII_Start
 *  SchM_ExitHook_McalLib_CpuEndInit_Return
 *  SchM_ExitHook_McalLib_CpuEndInit_Start
 *  SchM_ExitHook_McalLib_PeripheralEndInit_Return
 *  SchM_ExitHook_McalLib_PeripheralEndInit_Start
 *  SchM_ExitHook_McalLib_SafetyEndInit_Return
 *  SchM_ExitHook_McalLib_SafetyEndInit_Start
 *  SchM_ExitHook_McalLib_StmTimerResolution_Return
 *  SchM_ExitHook_McalLib_StmTimerResolution_Start
 *  SchM_ExitHook_Mcu_AtomAgcReg_Return
 *  SchM_ExitHook_Mcu_AtomAgcReg_Start
 *  SchM_ExitHook_Mcu_TomTgcReg_Return
 *  SchM_ExitHook_Mcu_TomTgcReg_Start
 *  SchM_ExitHook_Nm_NM_EXCLUSIVE_AREA_0_Return
 *  SchM_ExitHook_Nm_NM_EXCLUSIVE_AREA_0_Start
 *  SchM_ExitHook_Nm_NM_EXCLUSIVE_AREA_1_Return
 *  SchM_ExitHook_Nm_NM_EXCLUSIVE_AREA_1_Start
 *  SchM_ExitHook_PduR_PDUR_EXCLUSIVE_AREA_0_Return
 *  SchM_ExitHook_PduR_PDUR_EXCLUSIVE_AREA_0_Start
 *  SchM_ExitHook_SoAd_SOAD_EXCLUSIVE_AREA_0_Return
 *  SchM_ExitHook_SoAd_SOAD_EXCLUSIVE_AREA_0_Start
 *  SchM_ExitHook_SoAd_SOAD_EXCLUSIVE_AREA_1_Return
 *  SchM_ExitHook_SoAd_SOAD_EXCLUSIVE_AREA_1_Start
 *  SchM_ExitHook_StbM_STBM_EXCLUSIVE_AREA_0_Return
 *  SchM_ExitHook_StbM_STBM_EXCLUSIVE_AREA_0_Start
 *  SchM_ExitHook_TcpIp_TCPIP_EXCLUSIVE_AREA_0_Return
 *  SchM_ExitHook_TcpIp_TCPIP_EXCLUSIVE_AREA_0_Start
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_0_Return
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_0_Start
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_1_Return
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_1_Start
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_2_Return
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_2_Start
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_3_Return
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_3_Start
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_4_Return
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_4_Start
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_5_Return
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_5_Start
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_6_Return
 *  SchM_ExitHook_UdpNm_UDPNM_EXCLUSIVE_AREA_6_Start
 *  SchM_Schedulable_BswM_BswM_MainFunction_Return
 *  SchM_Schedulable_BswM_BswM_MainFunction_Start
 *  SchM_Schedulable_ComM_ComM_MainFunction_0_Return
 *  SchM_Schedulable_ComM_ComM_MainFunction_0_Start
 *  SchM_Schedulable_Com_Com_MainFunctionRx_Return
 *  SchM_Schedulable_Com_Com_MainFunctionRx_Start
 *  SchM_Schedulable_Com_Com_MainFunctionTx_Return
 *  SchM_Schedulable_Com_Com_MainFunctionTx_Start
 *  SchM_Schedulable_EcuM_EcuM_MainFunction_Return
 *  SchM_Schedulable_EcuM_EcuM_MainFunction_Start
 *  SchM_Schedulable_EthIf_EthIf_MainFunctionRx_Return
 *  SchM_Schedulable_EthIf_EthIf_MainFunctionRx_Start
 *  SchM_Schedulable_EthIf_EthIf_MainFunctionState_Return
 *  SchM_Schedulable_EthIf_EthIf_MainFunctionState_Start
 *  SchM_Schedulable_EthIf_EthIf_MainFunctionTx_Return
 *  SchM_Schedulable_EthIf_EthIf_MainFunctionTx_Start
 *  SchM_Schedulable_EthSM_EthSM_MainFunction_Return
 *  SchM_Schedulable_EthSM_EthSM_MainFunction_Start
 *  SchM_Schedulable_EthTSyn_EthTSyn_MainFunction_Return
 *  SchM_Schedulable_EthTSyn_EthTSyn_MainFunction_Start
 *  SchM_Schedulable_EthTrcv_30_Tja1100_EthTrcv_30_Tja1100_MainFunctionLinkHandling_Return
 *  SchM_Schedulable_EthTrcv_30_Tja1100_EthTrcv_30_Tja1100_MainFunctionLinkHandling_Start
 *  SchM_Schedulable_EthTrcv_30_Tja1100_EthTrcv_30_Tja1100_MainFunction_Return
 *  SchM_Schedulable_EthTrcv_30_Tja1100_EthTrcv_30_Tja1100_MainFunction_Start
 *  SchM_Schedulable_Eth_30_Tc3xx_Eth_30_Tc3xx_MainFunction_Return
 *  SchM_Schedulable_Eth_30_Tc3xx_Eth_30_Tc3xx_MainFunction_Start
 *  SchM_Schedulable_Rte_Rte_ComSendSignalProxyPeriodic_Return
 *  SchM_Schedulable_Rte_Rte_ComSendSignalProxyPeriodic_Start
 *  SchM_Schedulable_SoAd_SoAd_MainFunction_Return
 *  SchM_Schedulable_SoAd_SoAd_MainFunction_Start
 *  SchM_Schedulable_StbM_StbM_MainFunction_Return
 *  SchM_Schedulable_StbM_StbM_MainFunction_Start
 *  SchM_Schedulable_TcpIp_TcpIp_MainFunction_Return
 *  SchM_Schedulable_TcpIp_TcpIp_MainFunction_Start
 *  SchM_Schedulable_Uart_Uart_MainFunction_Read_Return
 *  SchM_Schedulable_Uart_Uart_MainFunction_Read_Start
 *  SchM_Schedulable_Uart_Uart_MainFunction_Write_Return
 *  SchM_Schedulable_Uart_Uart_MainFunction_Write_Start
 *  SchM_Schedulable_UdpNm_UdpNm_MainFunction_0_Return
 *  SchM_Schedulable_UdpNm_UdpNm_MainFunction_0_Start
 *
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_HOOK_H
# define RTE_HOOK_H

# include "Os.h" /* PRQA S 0828, 0883 */ /* MD_MSR_Dir1.1, MD_Rte_Os */

# include "Rte_Type.h"
# include "Rte_Cfg.h"

# ifndef RTE_VFB_TRACE
#  define RTE_VFB_TRACE (0)
# endif

#endif /* RTE_HOOK_H */

/**********************************************************************************************************************
 MISRA 2012 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_Os:
     Reason:     This justification is used as summary justification for all deviations caused by the MICROSAR OS
                 which is for testing of the RTE. Those deviations are no issues in the RTE code.
     Risk:       No functional risk.
     Prevention: Not required.

*/
