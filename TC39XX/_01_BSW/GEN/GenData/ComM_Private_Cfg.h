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
 *              File: ComM_Private_Cfg.h
 *   Generation Time: 2025-12-17 23:58:57
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined(COMM_PRIVATE_CFG_H)
#define COMM_PRIVATE_CFG_H
/* -----------------------------------------------------------------------------
    &&&~ INCLUDE
 ----------------------------------------------------------------------------- */
#include "ComM.h"
#include "Com.h"
#include "Appl_Cbk.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  ComMPCGetConstantDuplicatedRootDataMacros  ComM Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define ComM_GetActivePncComModeOfPCConfig()                          ComM_ActivePncComMode  /**< the pointer to ComM_ActivePncComMode */
#define ComM_GetBusPncComModeReqOfPCConfig()                          ComM_BusPncComModeReq  /**< the pointer to ComM_BusPncComModeReq */
#define ComM_GetChannelOfPCConfig()                                   ComM_Channel  /**< the pointer to ComM_Channel */
#define ComM_GetChannelPbOfPCConfig()                                 ComM_ChannelPb  /**< the pointer to ComM_ChannelPb */
#define ComM_GetPncChannelMappingOfPCConfig()                         ComM_PncChannelMapping  /**< the pointer to ComM_PncChannelMapping */
#define ComM_GetPncOfPCConfig()                                       ComM_Pnc  /**< the pointer to ComM_Pnc */
#define ComM_GetPncPSleepTimerOfPCConfig()                            ComM_PncPSleepTimer  /**< the pointer to ComM_PncPSleepTimer */
#define ComM_GetPncPbIndOfPCConfig()                                  ComM_PncPbInd  /**< the pointer to ComM_PncPbInd */
#define ComM_GetPncPbOfPCConfig()                                     ComM_PncPb  /**< the pointer to ComM_PncPb */
#define ComM_GetPncSignalIndOfPCConfig()                              ComM_PncSignalInd  /**< the pointer to ComM_PncSignalInd */
#define ComM_GetPncSignalOfPCConfig()                                 ComM_PncSignal  /**< the pointer to ComM_PncSignal */
#define ComM_GetPncSignalValuesOfPCConfig()                           ComM_PncSignalValues.raw  /**< the pointer to ComM_PncSignalValues */
#define ComM_GetSizeOfChannelOfPCConfig()                             1u  /**< the number of accomplishable value elements in ComM_Channel */
#define ComM_GetSizeOfChannelPbOfPCConfig()                           1u  /**< the number of accomplishable value elements in ComM_ChannelPb */
#define ComM_GetSizeOfPncChannelMappingOfPCConfig()                   1u  /**< the number of accomplishable value elements in ComM_PncChannelMapping */
#define ComM_GetSizeOfPncOfPCConfig()                                 1u  /**< the number of accomplishable value elements in ComM_Pnc */
#define ComM_GetSizeOfPncPbIndOfPCConfig()                            1u  /**< the number of accomplishable value elements in ComM_PncPbInd */
#define ComM_GetSizeOfPncPbOfPCConfig()                               1u  /**< the number of accomplishable value elements in ComM_PncPb */
#define ComM_GetSizeOfPncSignalIndOfPCConfig()                        1u  /**< the number of accomplishable value elements in ComM_PncSignalInd */
#define ComM_GetSizeOfPncSignalOfPCConfig()                           2u  /**< the number of accomplishable value elements in ComM_PncSignal */
#define ComM_GetSizeOfPncSignalValuesOfPCConfig()                     14u  /**< the number of accomplishable value elements in ComM_PncSignalValues */
#define ComM_GetSizeOfUserByteMaskOfPCConfig()                        2u  /**< the number of accomplishable value elements in ComM_UserByteMask */
#define ComM_GetSizeOfUserOfPCConfig()                                2u  /**< the number of accomplishable value elements in ComM_User */
#define ComM_GetSizeOfUserPncByteMaskOfPCConfig()                     1u  /**< the number of accomplishable value elements in ComM_UserPncByteMask */
#define ComM_GetSizeOfUserReqFullComOfPCConfig()                      1u  /**< the number of accomplishable value elements in ComM_UserReqFullCom */
#define ComM_GetSizeOfUserReqPncFullComOfPCConfig()                   1u  /**< the number of accomplishable value elements in ComM_UserReqPncFullCom */
#define ComM_GetUserByteMaskOfPCConfig()                              ComM_UserByteMask  /**< the pointer to ComM_UserByteMask */
#define ComM_GetUserOfPCConfig()                                      ComM_User  /**< the pointer to ComM_User */
#define ComM_GetUserPncByteMaskOfPCConfig()                           ComM_UserPncByteMask  /**< the pointer to ComM_UserPncByteMask */
#define ComM_GetUserReqFullComOfPCConfig()                            ComM_UserReqFullCom  /**< the pointer to ComM_UserReqFullCom */
#define ComM_GetUserReqPncFullComOfPCConfig()                         ComM_UserReqPncFullCom  /**< the pointer to ComM_UserReqPncFullCom */
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCGetDuplicatedRootDataMacros  ComM Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define ComM_GetSizeOfActivePncComModeOfPCConfig()                    ComM_GetSizeOfPncOfPCConfig()  /**< the number of accomplishable value elements in ComM_ActivePncComMode */
#define ComM_GetSizeOfBusPncComModeReqOfPCConfig()                    ComM_GetSizeOfPncOfPCConfig()  /**< the number of accomplishable value elements in ComM_BusPncComModeReq */
#define ComM_GetSizeOfPncPSleepTimerOfPCConfig()                      ComM_GetSizeOfPncOfPCConfig()  /**< the number of accomplishable value elements in ComM_PncPSleepTimer */
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCGetDataMacros  ComM Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define ComM_GetActivePncComMode(Index)                               (ComM_GetActivePncComModeOfPCConfig()[(Index)])
#define ComM_GetBusPncComModeReq(Index)                               (ComM_GetBusPncComModeReqOfPCConfig()[(Index)])
#define ComM_GetPncPSleepTimer(Index)                                 (ComM_GetPncPSleepTimerOfPCConfig()[(Index)])
#define ComM_GetChannelIdxOfPncSignal(Index)                          (ComM_GetPncSignalOfPCConfig()[(Index)].ChannelIdxOfPncSignal)
#define ComM_GetPncSignalValuesEndIdxOfPncSignal(Index)               (ComM_GetPncSignalOfPCConfig()[(Index)].PncSignalValuesEndIdxOfPncSignal)
#define ComM_GetPncSignalValuesStartIdxOfPncSignal(Index)             (ComM_GetPncSignalOfPCConfig()[(Index)].PncSignalValuesStartIdxOfPncSignal)
#define ComM_GetTypeOfPncSignal(Index)                                (ComM_GetPncSignalOfPCConfig()[(Index)].TypeOfPncSignal)
#define ComM_GetPncSignalValues(Index)                                (ComM_GetPncSignalValuesOfPCConfig()[(Index)])
#define ComM_IsPncUserOfUser(Index)                                   ((ComM_GetUserOfPCConfig()[(Index)].PncUserOfUser) != FALSE)
#define ComM_GetUserByteMaskEndIdxOfUser(Index)                       (ComM_GetUserOfPCConfig()[(Index)].UserByteMaskEndIdxOfUser)
#define ComM_GetUserByteMaskStartIdxOfUser(Index)                     (ComM_GetUserOfPCConfig()[(Index)].UserByteMaskStartIdxOfUser)
#define ComM_GetUserPncByteMaskEndIdxOfUser(Index)                    (ComM_GetUserOfPCConfig()[(Index)].UserPncByteMaskEndIdxOfUser)
#define ComM_GetUserPncByteMaskStartIdxOfUser(Index)                  (ComM_GetUserOfPCConfig()[(Index)].UserPncByteMaskStartIdxOfUser)
#define ComM_GetClearMaskOfUserByteMask(Index)                        (ComM_GetUserByteMaskOfPCConfig()[(Index)].ClearMaskOfUserByteMask)
#define ComM_GetSetMaskOfUserByteMask(Index)                          (ComM_GetUserByteMaskOfPCConfig()[(Index)].SetMaskOfUserByteMask)
#define ComM_GetUserReqFullCom(Index)                                 (ComM_GetUserReqFullComOfPCConfig()[(Index)])
#define ComM_GetUserReqPncFullCom(Index)                              (ComM_GetUserReqPncFullComOfPCConfig()[(Index)])
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCGetDeduplicatedDataMacros  ComM Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define ComM_GetBusTypeOfChannel(Index)                               COMM_BUS_TYPE_ETH  /**< The channel bus type */
#define ComM_GetGwTypeOfChannel(Index)                                COMM_GATEWAY_TYPE_NONE  /**< The partial network gateway type, relevant for channels attached to coordinated partial networks */
#define ComM_GetInhibitionInitValueOfChannel(Index)                   0x00u  /**< Initial value of the inhibition status of the channel */
#define ComM_IsNmSupportOfChannel(Index)                              (((TRUE)) != FALSE)  /**< Decides if the channel has NmType FULL or PASSIVE */
#define ComM_GetNmTypeOfChannel(Index)                                COMM_FULL_NMTYPEOFCHANNEL  /**< The Network Management type of the channel */
#define ComM_IsPncNmRequestOfChannel(Index)                           (((TRUE)) != FALSE)  /**< Decides if a Nm message shall be sent immediately after partial network state changes */
#define ComM_IsSilentSupportOfChannel(Index)                          (((TRUE)) != FALSE)  /**< Decides if the channel supports Silent mode (TRUE if ETH or CAN without J1939NM and Nm or NmLightSilentDuration) */
#define ComM_GetWakeupStateOfChannel(Index)                           COMM_FULL_COM_READY_SLEEP  /**< Target channel state after a Passive Wake-up */
#define ComM_GetPncPbIndEndIdxOfChannelPb(Index)                      1u  /**< the end index of the 0:n relation pointing to ComM_PncPbInd */
#define ComM_GetPncPbIndStartIdxOfChannelPb(Index)                    0u  /**< the start index of the 0:n relation pointing to ComM_PncPbInd */
#define ComM_IsPncPbIndUsedOfChannelPb(Index)                         (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to ComM_PncPbInd */
#define ComM_GetUserReqFullComEndIdxOfChannelPb(Index)                1u  /**< the end index of the 0:n relation pointing to ComM_UserReqFullCom */
#define ComM_GetUserReqFullComStartIdxOfChannelPb(Index)              0u  /**< the start index of the 0:n relation pointing to ComM_UserReqFullCom */
#define ComM_IsUserReqFullComUsedOfChannelPb(Index)                   (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to ComM_UserReqFullCom */
#define ComM_GetClearMaskOfPnc(Index)                                 0xFEu  /**< Clear mask for the partial network related signals (EIRA, ERA) */
#define ComM_GetPncIdOfPnc(Index)                                     0u  /**< System ID of the partial network */
#define ComM_GetSetMaskOfPnc(Index)                                   0x01u  /**< Set mask for the partial network related signals (EIRA, ERA) */
#define ComM_GetPncChannelMapping(Index)                              0u
#define ComM_GetPncChannelMappingEndIdxOfPncPb(Index)                 1u  /**< the end index of the 0:n relation pointing to ComM_PncChannelMapping */
#define ComM_GetPncChannelMappingStartIdxOfPncPb(Index)               0u  /**< the start index of the 0:n relation pointing to ComM_PncChannelMapping */
#define ComM_IsPncChannelMappingUsedOfPncPb(Index)                    (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to ComM_PncChannelMapping */
#define ComM_GetPncSignalIndEndIdxOfPncPb(Index)                      1u  /**< the end index of the 0:n relation pointing to ComM_PncSignalInd */
#define ComM_GetPncSignalIndStartIdxOfPncPb(Index)                    0u  /**< the start index of the 0:n relation pointing to ComM_PncSignalInd */
#define ComM_IsPncSignalIndUsedOfPncPb(Index)                         (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to ComM_PncSignalInd */
#define ComM_GetSignalByteIndexOfPncPb(Index)                         0u  /**< Byte index in the partial network related signals (EIRA, ERA) */
#define ComM_GetUserReqPncFullComEndIdxOfPncPb(Index)                 1u  /**< the end index of the 1:n relation pointing to ComM_UserReqPncFullCom */
#define ComM_GetUserReqPncFullComStartIdxOfPncPb(Index)               0u  /**< the start index of the 1:n relation pointing to ComM_UserReqPncFullCom */
#define ComM_GetPncPbInd(Index)                                       0u  /**< the indexes of the 1:1 sorted relation pointing to ComM_PncPb */
#define ComM_GetBusTypeIdOfPncSignal(Index)                           0u  /**< For EIRA RX Signals: An internal id for the BusType */
#define ComM_IsChannelUsedOfPncSignal(Index)                          (((boolean)(ComM_GetChannelIdxOfPncSignal(Index) != COMM_NO_CHANNELIDXOFPNCSIGNAL)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to ComM_Channel */
#define ComM_IsPncSignalValuesUsedOfPncSignal(Index)                  (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to ComM_PncSignalValues */
#define ComM_GetPncSignalInd(Index)                                   1u  /**< the indexes of the 1:1 sorted relation pointing to ComM_PncSignal */
#define ComM_GetSizeOfActivePncComMode()                              ComM_GetSizeOfActivePncComModeOfPCConfig()
#define ComM_GetSizeOfBusPncComModeReq()                              ComM_GetSizeOfBusPncComModeReqOfPCConfig()
#define ComM_GetSizeOfChannel()                                       ComM_GetSizeOfChannelOfPCConfig()
#define ComM_GetSizeOfChannelPb()                                     ComM_GetSizeOfChannelPbOfPCConfig()
#define ComM_GetSizeOfPnc()                                           ComM_GetSizeOfPncOfPCConfig()
#define ComM_GetSizeOfPncChannelMapping()                             ComM_GetSizeOfPncChannelMappingOfPCConfig()
#define ComM_GetSizeOfPncPSleepTimer()                                ComM_GetSizeOfPncPSleepTimerOfPCConfig()
#define ComM_GetSizeOfPncPb()                                         ComM_GetSizeOfPncPbOfPCConfig()
#define ComM_GetSizeOfPncPbInd()                                      ComM_GetSizeOfPncPbIndOfPCConfig()
#define ComM_GetSizeOfPncSignal()                                     ComM_GetSizeOfPncSignalOfPCConfig()
#define ComM_GetSizeOfPncSignalInd()                                  ComM_GetSizeOfPncSignalIndOfPCConfig()
#define ComM_GetSizeOfPncSignalValues()                               ComM_GetSizeOfPncSignalValuesOfPCConfig()
#define ComM_GetSizeOfUser()                                          ComM_GetSizeOfUserOfPCConfig()
#define ComM_GetSizeOfUserByteMask()                                  ComM_GetSizeOfUserByteMaskOfPCConfig()
#define ComM_GetSizeOfUserPncByteMask()                               ComM_GetSizeOfUserPncByteMaskOfPCConfig()
#define ComM_GetSizeOfUserReqFullCom()                                ComM_GetSizeOfUserReqFullComOfPCConfig()
#define ComM_GetSizeOfUserReqPncFullCom()                             ComM_GetSizeOfUserReqPncFullComOfPCConfig()
#define ComM_IsUserByteMaskUsedOfUser(Index)                          (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to ComM_UserByteMask */
#define ComM_IsUserPncByteMaskUsedOfUser(Index)                       (((boolean)(ComM_GetUserPncByteMaskStartIdxOfUser(Index) != COMM_NO_USERPNCBYTEMASKSTARTIDXOFUSER)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to ComM_UserPncByteMask */
#define ComM_GetChannelOfUserByteMask(Index)                          0u  /**< ID of the channel which is requested by this entry. */
#define ComM_GetUserReqFullComIdxOfUserByteMask(Index)                0u  /**< the index of the 1:1 relation pointing to ComM_UserReqFullCom */
#define ComM_GetClearMaskOfUserPncByteMask(Index)                     0xFEu  /**< Clear-mask for clearing the bit which corresponds to this user */
#define ComM_GetPncIDOfUserPncByteMask(Index)                         0u  /**< System Id of the partial network which is requested by this entry */
#define ComM_GetSetMaskOfUserPncByteMask(Index)                       0x01u  /**< Set-mask for setting the bit which corresponds to this user */
#define ComM_GetUserReqPncFullComIdxOfUserPncByteMask(Index)          0u  /**< the index of the 1:1 relation pointing to ComM_UserReqPncFullCom */
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCSetDataMacros  ComM Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define ComM_SetActivePncComMode(Index, Value)                        ComM_GetActivePncComModeOfPCConfig()[(Index)] = (Value)
#define ComM_SetBusPncComModeReq(Index, Value)                        ComM_GetBusPncComModeReqOfPCConfig()[(Index)] = (Value)
#define ComM_SetPncPSleepTimer(Index, Value)                          ComM_GetPncPSleepTimerOfPCConfig()[(Index)] = (Value)
#define ComM_SetPncSignalValues(Index, Value)                         ComM_GetPncSignalValuesOfPCConfig()[(Index)] = (Value)
#define ComM_SetUserReqFullCom(Index, Value)                          ComM_GetUserReqFullComOfPCConfig()[(Index)] = (Value)
#define ComM_SetUserReqPncFullCom(Index, Value)                       ComM_GetUserReqPncFullComOfPCConfig()[(Index)] = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCGetAddressOfDataMacros  ComM Get Address Of Data Macros (PRE_COMPILE)
  \brief  These macros can be used to get the data by the address operator.
  \{
*/ 
#define ComM_GetAddrPncSignalValues(Index)                            (&ComM_GetPncSignalValues(Index))
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCHasMacros  ComM Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define ComM_HasActivePncComMode()                                    (TRUE != FALSE)
#define ComM_HasBusPncComModeReq()                                    (TRUE != FALSE)
#define ComM_HasChannel()                                             (TRUE != FALSE)
#define ComM_HasBusTypeOfChannel()                                    (TRUE != FALSE)
#define ComM_HasGwTypeOfChannel()                                     (TRUE != FALSE)
#define ComM_HasInhibitionInitValueOfChannel()                        (TRUE != FALSE)
#define ComM_HasNmSupportOfChannel()                                  (TRUE != FALSE)
#define ComM_HasNmTypeOfChannel()                                     (TRUE != FALSE)
#define ComM_HasPncNmRequestOfChannel()                               (TRUE != FALSE)
#define ComM_HasSilentSupportOfChannel()                              (TRUE != FALSE)
#define ComM_HasWakeupStateOfChannel()                                (TRUE != FALSE)
#define ComM_HasChannelPb()                                           (TRUE != FALSE)
#define ComM_HasPncPbIndEndIdxOfChannelPb()                           (TRUE != FALSE)
#define ComM_HasPncPbIndStartIdxOfChannelPb()                         (TRUE != FALSE)
#define ComM_HasPncPbIndUsedOfChannelPb()                             (TRUE != FALSE)
#define ComM_HasUserReqFullComEndIdxOfChannelPb()                     (TRUE != FALSE)
#define ComM_HasUserReqFullComStartIdxOfChannelPb()                   (TRUE != FALSE)
#define ComM_HasUserReqFullComUsedOfChannelPb()                       (TRUE != FALSE)
#define ComM_HasPnc()                                                 (TRUE != FALSE)
#define ComM_HasClearMaskOfPnc()                                      (TRUE != FALSE)
#define ComM_HasPncIdOfPnc()                                          (TRUE != FALSE)
#define ComM_HasSetMaskOfPnc()                                        (TRUE != FALSE)
#define ComM_HasPncChannelMapping()                                   (TRUE != FALSE)
#define ComM_HasPncPSleepTimer()                                      (TRUE != FALSE)
#define ComM_HasPncPb()                                               (TRUE != FALSE)
#define ComM_HasPncChannelMappingEndIdxOfPncPb()                      (TRUE != FALSE)
#define ComM_HasPncChannelMappingStartIdxOfPncPb()                    (TRUE != FALSE)
#define ComM_HasPncChannelMappingUsedOfPncPb()                        (TRUE != FALSE)
#define ComM_HasPncSignalIndEndIdxOfPncPb()                           (TRUE != FALSE)
#define ComM_HasPncSignalIndStartIdxOfPncPb()                         (TRUE != FALSE)
#define ComM_HasPncSignalIndUsedOfPncPb()                             (TRUE != FALSE)
#define ComM_HasSignalByteIndexOfPncPb()                              (TRUE != FALSE)
#define ComM_HasUserReqPncFullComEndIdxOfPncPb()                      (TRUE != FALSE)
#define ComM_HasUserReqPncFullComStartIdxOfPncPb()                    (TRUE != FALSE)
#define ComM_HasPncPbInd()                                            (TRUE != FALSE)
#define ComM_HasPncSignal()                                           (TRUE != FALSE)
#define ComM_HasBusTypeIdOfPncSignal()                                (TRUE != FALSE)
#define ComM_HasChannelIdxOfPncSignal()                               (TRUE != FALSE)
#define ComM_HasChannelUsedOfPncSignal()                              (TRUE != FALSE)
#define ComM_HasPncSignalValuesEndIdxOfPncSignal()                    (TRUE != FALSE)
#define ComM_HasPncSignalValuesStartIdxOfPncSignal()                  (TRUE != FALSE)
#define ComM_HasPncSignalValuesUsedOfPncSignal()                      (TRUE != FALSE)
#define ComM_HasTypeOfPncSignal()                                     (TRUE != FALSE)
#define ComM_HasPncSignalInd()                                        (TRUE != FALSE)
#define ComM_HasPncSignalValues()                                     (TRUE != FALSE)
#define ComM_HasSizeOfActivePncComMode()                              (TRUE != FALSE)
#define ComM_HasSizeOfBusPncComModeReq()                              (TRUE != FALSE)
#define ComM_HasSizeOfChannel()                                       (TRUE != FALSE)
#define ComM_HasSizeOfChannelPb()                                     (TRUE != FALSE)
#define ComM_HasSizeOfPnc()                                           (TRUE != FALSE)
#define ComM_HasSizeOfPncChannelMapping()                             (TRUE != FALSE)
#define ComM_HasSizeOfPncPSleepTimer()                                (TRUE != FALSE)
#define ComM_HasSizeOfPncPb()                                         (TRUE != FALSE)
#define ComM_HasSizeOfPncPbInd()                                      (TRUE != FALSE)
#define ComM_HasSizeOfPncSignal()                                     (TRUE != FALSE)
#define ComM_HasSizeOfPncSignalInd()                                  (TRUE != FALSE)
#define ComM_HasSizeOfPncSignalValues()                               (TRUE != FALSE)
#define ComM_HasSizeOfUser()                                          (TRUE != FALSE)
#define ComM_HasSizeOfUserByteMask()                                  (TRUE != FALSE)
#define ComM_HasSizeOfUserPncByteMask()                               (TRUE != FALSE)
#define ComM_HasSizeOfUserReqFullCom()                                (TRUE != FALSE)
#define ComM_HasSizeOfUserReqPncFullCom()                             (TRUE != FALSE)
#define ComM_HasUser()                                                (TRUE != FALSE)
#define ComM_HasPncUserOfUser()                                       (TRUE != FALSE)
#define ComM_HasUserByteMaskEndIdxOfUser()                            (TRUE != FALSE)
#define ComM_HasUserByteMaskStartIdxOfUser()                          (TRUE != FALSE)
#define ComM_HasUserByteMaskUsedOfUser()                              (TRUE != FALSE)
#define ComM_HasUserPncByteMaskEndIdxOfUser()                         (TRUE != FALSE)
#define ComM_HasUserPncByteMaskStartIdxOfUser()                       (TRUE != FALSE)
#define ComM_HasUserPncByteMaskUsedOfUser()                           (TRUE != FALSE)
#define ComM_HasUserByteMask()                                        (TRUE != FALSE)
#define ComM_HasChannelOfUserByteMask()                               (TRUE != FALSE)
#define ComM_HasClearMaskOfUserByteMask()                             (TRUE != FALSE)
#define ComM_HasSetMaskOfUserByteMask()                               (TRUE != FALSE)
#define ComM_HasUserReqFullComIdxOfUserByteMask()                     (TRUE != FALSE)
#define ComM_HasUserPncByteMask()                                     (TRUE != FALSE)
#define ComM_HasClearMaskOfUserPncByteMask()                          (TRUE != FALSE)
#define ComM_HasPncIDOfUserPncByteMask()                              (TRUE != FALSE)
#define ComM_HasSetMaskOfUserPncByteMask()                            (TRUE != FALSE)
#define ComM_HasUserReqPncFullComIdxOfUserPncByteMask()               (TRUE != FALSE)
#define ComM_HasUserReqFullCom()                                      (TRUE != FALSE)
#define ComM_HasUserReqPncFullCom()                                   (TRUE != FALSE)
#define ComM_HasPCConfig()                                            (TRUE != FALSE)
#define ComM_HasActivePncComModeOfPCConfig()                          (TRUE != FALSE)
#define ComM_HasBusPncComModeReqOfPCConfig()                          (TRUE != FALSE)
#define ComM_HasChannelOfPCConfig()                                   (TRUE != FALSE)
#define ComM_HasChannelPbOfPCConfig()                                 (TRUE != FALSE)
#define ComM_HasPncChannelMappingOfPCConfig()                         (TRUE != FALSE)
#define ComM_HasPncOfPCConfig()                                       (TRUE != FALSE)
#define ComM_HasPncPSleepTimerOfPCConfig()                            (TRUE != FALSE)
#define ComM_HasPncPbIndOfPCConfig()                                  (TRUE != FALSE)
#define ComM_HasPncPbOfPCConfig()                                     (TRUE != FALSE)
#define ComM_HasPncSignalIndOfPCConfig()                              (TRUE != FALSE)
#define ComM_HasPncSignalOfPCConfig()                                 (TRUE != FALSE)
#define ComM_HasPncSignalValuesOfPCConfig()                           (TRUE != FALSE)
#define ComM_HasSizeOfActivePncComModeOfPCConfig()                    (TRUE != FALSE)
#define ComM_HasSizeOfBusPncComModeReqOfPCConfig()                    (TRUE != FALSE)
#define ComM_HasSizeOfChannelOfPCConfig()                             (TRUE != FALSE)
#define ComM_HasSizeOfChannelPbOfPCConfig()                           (TRUE != FALSE)
#define ComM_HasSizeOfPncChannelMappingOfPCConfig()                   (TRUE != FALSE)
#define ComM_HasSizeOfPncOfPCConfig()                                 (TRUE != FALSE)
#define ComM_HasSizeOfPncPSleepTimerOfPCConfig()                      (TRUE != FALSE)
#define ComM_HasSizeOfPncPbIndOfPCConfig()                            (TRUE != FALSE)
#define ComM_HasSizeOfPncPbOfPCConfig()                               (TRUE != FALSE)
#define ComM_HasSizeOfPncSignalIndOfPCConfig()                        (TRUE != FALSE)
#define ComM_HasSizeOfPncSignalOfPCConfig()                           (TRUE != FALSE)
#define ComM_HasSizeOfPncSignalValuesOfPCConfig()                     (TRUE != FALSE)
#define ComM_HasSizeOfUserByteMaskOfPCConfig()                        (TRUE != FALSE)
#define ComM_HasSizeOfUserOfPCConfig()                                (TRUE != FALSE)
#define ComM_HasSizeOfUserPncByteMaskOfPCConfig()                     (TRUE != FALSE)
#define ComM_HasSizeOfUserReqFullComOfPCConfig()                      (TRUE != FALSE)
#define ComM_HasSizeOfUserReqPncFullComOfPCConfig()                   (TRUE != FALSE)
#define ComM_HasUserByteMaskOfPCConfig()                              (TRUE != FALSE)
#define ComM_HasUserOfPCConfig()                                      (TRUE != FALSE)
#define ComM_HasUserPncByteMaskOfPCConfig()                           (TRUE != FALSE)
#define ComM_HasUserReqFullComOfPCConfig()                            (TRUE != FALSE)
#define ComM_HasUserReqPncFullComOfPCConfig()                         (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCIncrementDataMacros  ComM Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define ComM_IncActivePncComMode(Index)                               ComM_GetActivePncComMode(Index)++
#define ComM_IncBusPncComModeReq(Index)                               ComM_GetBusPncComModeReq(Index)++
#define ComM_IncPncPSleepTimer(Index)                                 ComM_GetPncPSleepTimer(Index)++
#define ComM_IncPncSignalValues(Index)                                ComM_GetPncSignalValues(Index)++
#define ComM_IncUserReqFullCom(Index)                                 ComM_GetUserReqFullCom(Index)++
#define ComM_IncUserReqPncFullCom(Index)                              ComM_GetUserReqPncFullCom(Index)++
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCDecrementDataMacros  ComM Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define ComM_DecActivePncComMode(Index)                               ComM_GetActivePncComMode(Index)--
#define ComM_DecBusPncComModeReq(Index)                               ComM_GetBusPncComModeReq(Index)--
#define ComM_DecPncPSleepTimer(Index)                                 ComM_GetPncPSleepTimer(Index)--
#define ComM_DecPncSignalValues(Index)                                ComM_GetPncSignalValues(Index)--
#define ComM_DecUserReqFullCom(Index)                                 ComM_GetUserReqFullCom(Index)--
#define ComM_DecUserReqPncFullCom(Index)                              ComM_GetUserReqPncFullCom(Index)--
/** 
  \}
*/ 

  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/* Postbuild */
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/* Macros for stored PNC signal data manipulation:*/

/* Evaluate if the bit for InternalPncId is set in the stored data for signal specified by InternalSignalId */
#define ComM_IsSignalStoredPncBitSet(InternalSignalId, InternalPncId) ((ComM_GetPncSignalValues(ComM_GetPncSignalValuesStartIdxOfPncSignal(InternalSignalId) + ComM_GetSignalByteIndexOfPncPb(InternalPncId)) & ComM_GetSetMaskOfPnc(InternalPncId)) > 0u) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/* PRQA S 3451 EXTERNDECLARATIONS */ /* MD_ComM_3451_3449 */ 
/* PRQA S 3449 EXTERNALDECLARATIONS_3449 */ /* MD_ComM_3451_3449 */ 
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  ComM_PncSignal
**********************************************************************************************************************/
/** 
  \var    ComM_PncSignal
  \brief  Information about partial network signals (EIRA, ERA)
  \details
  Element                    Description
  ChannelIdx                 the index of the 0:1 relation pointing to ComM_Channel
  PncSignalValuesEndIdx      the end index of the 0:n relation pointing to ComM_PncSignalValues
  PncSignalValuesStartIdx    the start index of the 0:n relation pointing to ComM_PncSignalValues
  Type                       Partial network signal type
*/ 
#define COMM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(ComM_PncSignalType, COMM_CONST) ComM_PncSignal[2];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_User
**********************************************************************************************************************/
/** 
  \var    ComM_User
  \brief  Information about ComM users
  \details
  Element                    Description
  PncUser                    decides if a user is a partial network user or a direct channel user
  UserByteMaskEndIdx         the end index of the 0:n relation pointing to ComM_UserByteMask
  UserByteMaskStartIdx       the start index of the 0:n relation pointing to ComM_UserByteMask
  UserPncByteMaskEndIdx      the end index of the 0:n relation pointing to ComM_UserPncByteMask
  UserPncByteMaskStartIdx    the start index of the 0:n relation pointing to ComM_UserPncByteMask
*/ 
#define COMM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(ComM_UserType, COMM_CONST) ComM_User[2];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_UserByteMask
**********************************************************************************************************************/
/** 
  \var    ComM_UserByteMask
  \brief  Each user has N entries in this array (N = # channels attached to this user, directly or through PNC). Each entry describes a Byte Position and a Mask for storing/clearing the user request in UserReqFullCom
  \details
  Element      Description
  ClearMask    Clear-mask for clearing the bit which corresponds to this user
  SetMask      Set-mask for setting the bit which corresponds to this user
*/ 
#define COMM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(ComM_UserByteMaskType, COMM_CONST) ComM_UserByteMask[2];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_ActivePncComMode
**********************************************************************************************************************/
/** 
  \var    ComM_ActivePncComMode
  \brief  stores the current partial network state
*/ 
#define COMM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(ComM_PncModeType, COMM_VAR_NOINIT) ComM_ActivePncComMode[1];
#define COMM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_BusPncComModeReq
**********************************************************************************************************************/
/** 
  \var    ComM_BusPncComModeReq
  \brief  Stores the partial network state requested by external requests
*/ 
#define COMM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(ComM_PncModeType, COMM_VAR_NOINIT) ComM_BusPncComModeReq[1];
#define COMM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_PncPSleepTimer
**********************************************************************************************************************/
/** 
  \var    ComM_PncPSleepTimer
  \brief  partial network prepare sleep timer
*/ 
#define COMM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(ComM_PncPSleepTimerType, COMM_VAR_NOINIT) ComM_PncPSleepTimer[1];
#define COMM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_PncSignalValues
**********************************************************************************************************************/
#define COMM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(ComM_PncSignalValuesUType, COMM_VAR_NOINIT) ComM_PncSignalValues;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define COMM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_UserReqFullCom
**********************************************************************************************************************/
/** 
  \var    ComM_UserReqFullCom
  \brief  RAM array used to store user requests for channels as bitmasks. Each channel 'owns' 1..n bytes in this array, depending on the number of users assigned to it.
*/ 
#define COMM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(ComM_UserReqFullComType, COMM_VAR_NOINIT) ComM_UserReqFullCom[1];
#define COMM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_UserReqPncFullCom
**********************************************************************************************************************/
/** 
  \var    ComM_UserReqPncFullCom
  \brief  RAM array used to store user requests for PNCs as bitmasks. Each PNC 'owns' 1..n bytes in this array, depending on the number of users assigned to it.
*/ 
#define COMM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(ComM_UserReqPncFullComType, COMM_VAR_NOINIT) ComM_UserReqPncFullCom[1];
#define COMM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/* PRQA L:EXTERNALDECLARATIONS_3449 */
/* PRQA L:EXTERNDECLARATIONS */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  INTERNAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define COMM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "MemMap.h"

# if (COMM_EXISTS_EIRA_TX_TYPEOFPNCSIGNAL == STD_ON)
/*********************************************************************************************************************
  FUNCTION: ComM_ExecuteComSendSignal
*********************************************************************************************************************/
/*! \brief       Function to execute EIRA_TX transmission requests.
 *  \param[in]   InternalSignalId       the internal ID of the signal, which is an index in the ComM_PncSignal table
 *  \param[in]   SignalDataTx           signal data to be sent
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
*********************************************************************************************************************/
extern FUNC(void, COMM_CODE) ComM_ExecuteComSendSignal(ComM_SizeOfPncSignalType InternalSignalId, const uint8 *SignalDataTx);
# endif

# if (COMM_EXISTS_EIRA_RX_TYPEOFPNCSIGNAL == STD_ON)
/*********************************************************************************************************************
  FUNCTION: ComM_PncProcessRxSignalEira
*********************************************************************************************************************/
/*! \brief       Function to process received EIRA_RX PNC states. It sets the bus-side requested Pnc state accordingly.
 *  \param[in]   InternalSignalId       the internal ID of the signal, which is an index in the ComM_PncSignal table
 *  \param[in]   SignalDataRx           signal data received from Com
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
*********************************************************************************************************************/
extern FUNC(void, COMM_CODE) ComM_PncProcessRxSignalEira(ComM_SizeOfPncSignalType InternalSignalId, const uint8 *SignalDataRx);
# endif

# if (COMM_PNC_ACTIVE_COORD == STD_ON)
/*********************************************************************************************************************
  FUNCTION: ComM_PncProcessRxSignalEra
*********************************************************************************************************************/
/*! \brief       Function to process received ERA PNC states and to request or release system users.
 *  \param[in]   InternalSignalId       the internal ID of the signal, which is an index in the ComM_PncSignal table
 *  \param[in]   SignalDataRx           signal data received from Com
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
*********************************************************************************************************************/
extern FUNC(void, COMM_CODE) ComM_PncProcessRxSignalEra(ComM_SizeOfPncSignalType InternalSignalId, const uint8 *SignalDataRx);
# endif

#define COMM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "MemMap.h"

/**********************************************************************************************************************
  CONFIG POINTER
**********************************************************************************************************************/
#if (COMM_USE_INIT_POINTER == STD_ON)
# define COMM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
# include "MemMap.h"

extern P2CONST(ComM_ConfigType, AUTOMATIC, COMM_INIT_DATA) ComM_ConfigPtr;

# define COMM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
# include "MemMap.h"
#endif

#endif /* COMM_PRIVATE_CFG_H */

