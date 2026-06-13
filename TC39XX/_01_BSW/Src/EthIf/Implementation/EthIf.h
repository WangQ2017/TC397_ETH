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
/*!        \file  EthIf.h
 *        \brief  Ethernet Interface header file
 *
 *      \details  Component to abstract the underlying Ethernet hardware for the upper layers to provide a generic
 *                interface to be used for controlling and communicate with the help of the Ethernet hardware
 *                provided by an ECU (Ethernet controller, Ethernet transceiver, Ethernet switch).
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2008-08-04  visalr  -             created
 *  01.00.01  2008-11-20  visalr  -             bugfix: switch off transceiver
 *  01.00.02  2008-11-25  visalr  -             bugfix: tx confirmation without request
 *  01.00.03  2008-12-08  visalr  -             EthIf_Types.h introduced
 *  01.02.00  2009-01-14  visalr  -             version inconsistencies
 *  01.03.00  2009-01-15  visalr  -             separate MainFunctions for Rx and Tx
 *  01.04.00  2009-03-19  visalr  -             EthTrcv_GetLinkState param CtrlIdxPtr removed
 *  01.04.01  2009-03-26  visalr  -             SoAd: bugfix for DET error if ConfigVariant != 3
 *  01.04.02  2009-07-31  visalr  -             include Det.h only if configured
 *                                -             new DET macros
 *                                -             API optimization support (single channel API)
 *                                -             BRS Time Measurement support added
 *                                -             Config variant check for library build
 *                                -             optional separate MainFunction for state
 *  01.04.03  2009-09-15  visalr  -             bugfix: Eth_Transmit with more than one buffer
 *                                -             bugfix: reset stored transceiver mode in EthIf_SetTransceiverMode
 *                                -             Config version check
 *  01.04.04  2009-09-28  visalr  -             GENy release version
 *  01.04.05  2009-09-29  visalr  -             Memory Abstraction for stack local pointer
 *                                -             bugfix support all configuration variants
 *  01.04.06  2009-10-02  visalr  -             bugfix include files adapted
 *                                -             single module header introduced (single source)
 *  01.04.07  2009-10-05  visalr  -             no changes
 *  01.04.08  2009-10-05  visalr  -             no changes
 *  01.04.09  2009-10-08  visalr  -             bugfix missing ETHIF_STOP_SEC_CODE in EthIf_Lcfg.h
 *  02.00.00  2009-10-08  visalr  -             no changes
 *  02.00.01  2009-10-08  visalr  -             no changes
 *  02.00.02  2009-10-13  visalr  -             comment format updated
 *  02.01.00  2009-11-17  visalr  -             bugfix during optimization
 *                                -             VendorId added
 *                                -             bugfix DET checks without actual condition did not fire
 *                                -             validate post-build configuration
 *                                -             DET check bugfixing
 *                                -             support multiple calls of Eth_Init
 *  02.01.01  2010-01-12  visalr  ESCAN00040063 EthIf: Compiler Error without DET
 *  02.01.02  2010-02-11  visalr  ESCAN00040761 Wrong module id returned
 *  02.01.03  2010-09-16  visalr  ESCAN00045366 DET error by EthTrcv in EthIf_MainFunction if initial COM_REQUEST is
 *                                              missing
 *  02.01.04  2010-12-23  visalr  ESCAN00047335 Adapt MainFunction for usage with IdentityManagerConfig
 *            2011-02-11  visalr  ESCAN00048017 MemMap.h: Missing Start/Stop Sections (PBCFG_ROOT)
 *            2011-02-16  visalr  -             compiler abstraction adapted (use of AUTOMATIC)
 *  02.01.05  2011-03-04  visalr                missing comment within Eth_Compiler_Cfg.inc
 *  02.01.06  2011-03-18  visalr                wrong component version IF_ASRIFETH_VERSION,
 *                                              IF_ASRIFETH_RELEASE_VERSION
 *  02.01.07  2011-05-31  visalr  ESCAN00050530 Generate EthIf  EcuC Global Configuration Container Name
 *  02.01.08  2011-09-07  visalr  ESCAN00053407 Addtional preprocessor argument for macro without DEM has to be removed
 *  02.01.09  2011-09-23  visalr                GHS compiler warnings resolved (undefined preprocessing identifier)
 *  02.01.10  2011-11-07  visalr  ESCAN00054715 Vector coding rules compliance
 *  03.00.00  2011-12-07  visalr                Add IpV6 Frame Type support. GENy only, no code changes but version
 *                                              check adapted
 *  03.00.01  2011-12-07  visalr  ESCAN00055494 Wrong memory section mapping in Ethernet Interface
 *  03.00.02  2012-02-10  visalr  ESCAN00056744 Set Transceiver Mode does not trigger Transceiver Link State callback
 *                                              when switched off
 *            2012-02-13  visalr  ESCAN00056356 VAR_INIT / VAR_ZERO_INIT Memory Mapping sections
 *            2012-02-14  visalr  ESCAN00056357 Remove Macro support for Version Info API
 *            2012-02-14  visalr  ESCAN00056599 Compiler Abstractions are partly wrong
 *            2012-02-22  visalr  ESCAN00051712 Remove the AUTOSAR Release Version Check
 *  03.00.03  2012-04-23  visalr  ESCAN00056356 VAR_INIT / VAR_ZERO_INIT Memory Mapping sections
 *  03.01.00  2012-08-31  vishaw  -             Discard VLAN Tags within received Ethernet frames originated by PLC
 *                                              chips
 *  03.01.01  2012-10-02  visalr  ESCAN00061909 ASR4 Enhancement
 *            2012-10-02  visalr  ESCAN00058884 AR4-125: Remove support for v_cfg.h in Cfg5 systems
 *            2012-10-18  vishaw  ESCAN00062248 AR4-220: Remove STATIC
 *  04.00.00  2013-03-19  vishaw  ESCAN00066018 ASR4.1.1 extensions
 *                                ESCAN00068224 AR4-385: VLAN Support (multi home)
 *                                ESCAN00060125 Optimization of Transceiver Linke State Change Callback
 *  04.00.01  2013-11-05  vishaw  ESCAN00066018 Resubmitted: ASR4.1.1 extensions
 *  04.01.00  2014-01-23  vishaw  ESCAN00073154 Implemented zero-copy extensions
 *  04.01.01  2014-02-12  visfdn  ESCAN00073610 Usage of uninitialized variable 'VirtualCtrl' in EthIf_Transmit()
 *  04.02.00  2014-03-04  vishaw  ESCAN00074065 Ethernet transceiver is initialized multiple times in a row
 *                                ESCAN00074060 Introduced PTP support
 *  04.02.01  2014-03-28  vishaw  ESCAN00074620 Multiple transceiver configurations of one transceiver driver aren't
 *                                              initialized properly
 *                                ESCAN00074611 Ethernet Driver may throw a DET error in Eth_Receive when interrupts
 *                                              are disabled (polling mode)
 *                                ESCAN00074869 EthIf may return the wrong Ethernet Controller or Transceiver mode 
 *  04.02.02  2014-03-14  vishaw  ESCAN00074979 Some RAM variables aren't initialized. EthIf initialization may fail
 *                                              and communication does not take in place
 *                                ESCAN00074980 Avoid compiler faults by using pointers to ROM structures instead
 *                                              of loading the structures onto the stack
 *                                ESCAN00074981 PTP APIs may call the Ethernet controller driver with wrong
 *                                              Controller Indexes, causing DETS in the Ethernet controller driver
 *  04.02.03  2014-06-17  vishaw  ESCAN00075364 Compiler error in PTP submodule when API optimization is enabled
 *                                ESCAN00072342 Eth_ProvideTxBuffer succeeds although data length is too long
 *  04.02.04  2014-07-04  vishaw  ESCAN00076449 TrcvLinkStateChg callbacks of upper layer modules are called although
 *                                              Eth-Controller is not initialized
 *  04.04.00  2014-07-17  vishaw  ESCAN00073605 AR4-500: AUTOSAR CONC_600_SwitchConfiguration
 *  04.05.00  2014-09-19  vishaw  ESCAN00076708 AR4-897: Support overwriting of the Ethernet header during
 *                                              transmission and support reception of Ethernet header information for
 *                                              upper layers of the Ethernet Interface
 *                                ESCAN00069414 Transceiver link state is checked with too slow frequency in
 *                                              EthIf_MainFunctionState
 *                                ESCAN00069310 Vehicle Announcement messages are not sent after transceiver
 *                                              link state changes to active
 *                                ESCAN00069413 Improve MainFunctionState handling by performing reload handling not
 *                                              within the state function itself
 *            2015-02-03  vismha  ESCAN00079196 Compiler error: EthIf_MainFunctionRx undefined if API optimization
 *                                              and polling mode enabled
 *  04.06.00  2015-02-16  vismha  ESCAN00080072 FEAT-705: Ethernet wakeup based on Activation Line [AR4-1006]
 *            2015-03-02  vismha  ESCAN00078574 EthIf_SetCorrectionTime uses sint32 instead of Eth_TimeDiffType for
 *                                              parameter OffsetTimePtr
 *                                ESCAN00079195 EthIf polls the Eth_Receive method without using the RxStatus
 *                                              parameter as a stop criterion
 *  04.06.01  2015-03-26  vismha  ESCAN00078574 EthIf_SetCorrectionTime uses sint32 instead of Eth_TimeDiffType for
 *                                              parameter OffsetTimePtr
 *                                              (Re-Submitted due to wrong description of Ticket, type name should be
 *                                               Eth_TimediffType)
 *  04.07.00  2015-05-22  vismha  ESCAN00083137 Use AUTOSAR timestamp type instead of Vector proprietary type
 *  04.08.00  2015-06-15  vismha  ESCAN00082697 FEAT-1457: SRP module development
 *  04.09.00  2015-07-06  vismha  ESCAN00083818 Receive polling processes a high amount of time under high traffic
 *                                              situations
 *            2015-07-17  vismha  ESCAN00083367 Support of Mirroring/Gateway functionality
 *                                ESCAN00084076 Support multi derivative Eth controllers and Eth controller API
 *                                              infixing
 *  04.09.01  2015-10-29  vismha  ESCAN00086158 Destination/Source MAC address corrupt if VLAN tagged frame is routed
 *                                              by traffic gateway
 *                                ESCAN00086077 Compiler error: Unresolved symbol EthIf_VTransmit in
 *                                              EthIf_ExtndTrafficHndl.c
 *  05.00.00  2015-11-05  vismha  ESCAN00080843 Handling of data transmission and reception is inconsistent for VLAN
 *                                              and no VLAN virtual controllers
 *                                ESCAN00082029 Compiler warning: "no function prototype given: converting '()' to
 *                                              '(void)'
 *                                ESCAN00083601 Ethernet Tx Buffers for a VLAN EthIf controller aren't released by
 *                                              call to EthIf_Transmit()
 *                                ESCAN00083605 EthIf_GetRxHeaderPtr() returns wrong length when requesting for VLAN
 *                                              EthIf controller
 *                                ESCAN00084341 EthIf_GetTxHeaderPtr() returns wrong length when requesting for VLAN
 *                                              EthIf controller
 *            2015-11-25  vismha  ESCAN00086738 FEAT-1529: Support Ethernet Switches for Ethernet Time Sync
 *            2015-12-08  vismha  ESCAN00086980 Undesired TxConfirmation for a canceled Frame Transmission
 *  05.00.01  2016-01-15  vismha  ESCAN00087503 NULL_PTR access during EthIf_SetControllerMode()
 *            2016-03-02  vismha  ESCAN00087559 NULL_PTR access instead of DET error in EthIf_GetRxHeaderPtr()
 *  05.00.02  2016-05-04  vismha  ESCAN00089656 Compiler error: identifier "EthIf_TxBufferNum" is undefined when two
 *                                              Ethernet controllers are used
 *            2016-05-09  vismha  ESCAN00089912 Transmit fails although buffer was successfully acquired
 *  05.00.03  2016-06-07  vismha  ESCAN00089534 Semaphore IsLocked of EthIf_ControllerInit() and
 *                                              EthIf_SetControllerMode() shall be module local
 *  06.00.00  2016-06-15  vismha  ESCAN00089373 FEAT-1845: Processmigration: ETH Stack
 *                                ESCAN00089982 EthIf_Init DET Check
 *                                ESCAN00089983 EthIf_UpdatePhysAddrFilter DET Check
 *                                ESCAN00089984 EthIf_ProvideTxBuffer DET Check
 *                                ESCAN00089985 EthIf_Transmit DET Check
 *                                ESCAN00089986 EthIf_RxIndication DET Check
 *                                ESCAN00089991 EthIf_GetDropCount DET Check
 *                                ESCAN00089992 EthIf_StoreConfiguration DET Check
 *                                ESCAN00089993 EthIf_ResetConfiguration DET Check
 *                                ESCAN00089996 EthIf_ProvideExtTxBuffer DET Check
 *                                ESCAN00089998 EthIf_GetBandwidthLimit DET Check
 *                                ESCAN00090075 EthIf_SetControllerMode DET Check
 *            2016-06-23  vismha  ESCAN00089365 FEAT-1738: Ethernet Receive Buffer Segmentation
 *            2016-06-27  vismha  ESCAN00090679 EthIf_GetPortMacAddr() returns a wrong Switch Index
 *            2016-07-18  vismha  ESCAN00090397 Prohibit triggering of Frame Transmission without previous buffer
 *                                              provision
 *  06.00.01  2016-08-22  vismha  ESCAN00091244 Compiler error: 'EthIf_CfgAccess_TrcvLinkStateChgReload' undefined
 *                                ESCAN00091548 Correct findings of review of version 6.00.00
 *  07.00.00  2016-10-13  vismha  FEATC-249     FEAT-1998: Support of HW Time Stamping for Switch in EthIf
 *  07.01.00  2016-12-20  vismha  FEATC-914     FEAT-2119: Introduce API for SRP Server in EthIf
 *  07.01.01  2017-01-27  vismha  ESCAN00093756 Timestamp queue in switch driver can reach an inconsistent state,
 *                                              resulting in loss of egress timestamps due to wrong API design
 *                                ESCAN00093271 Missing include of BswM_EthIf.h
 *                                ESCAN00093282 Link State Change Indication to DOWN called although link wasn't UP
 *                                              before
 *            2017-02-03  vismha  ESCAN00093833 Misalignment exception during reception of a frame with odd length on
 *                                              RH850/V850 platform
 *  07.02.00  2017-01-30  vismha  FEATC-890     FEAT-2354: Firewall concept for Ethernet. Implementation of EthIf
 *                                              callout.
 *            2017-02-06  vismha  ESCAN00093876 Compiler error: Unresolved symbol EthIf_ExitExclusiveAre() in
 *                                              EthIf_ExtndTrafficHndl.c
 *                                ESCAN00093878 Compiler error: Unresolved symbol SrcFrameLen in
 *                                              EthIf_Mirroring_ProvideTxMirroringBuffer() of  EthIf_ExtndTrafficHndl.c
 *                                ESCAN00093713 Compiler error: EthIf_ExtndTrafficHndl.c: Cannot open include file:
 *                                              'Det.h': No such file or directory
 *  07.02.01  2017-02-16  vismha  ESCAN00093258 EthIf Switching Independent Port Groups (controlled by BswM) does not
 *                                              work correctly
 *                                ESCAN00094059 Integrated review findings of initial MSR4-R17 release
 *  08.00.00  2017-02-20  vismha  FEATC-1167    FEAT-2279: Time Synchronization acc. AR 4.3 for Eth_If
 *                                FEATC-713     FEAT-2151: EthIf - Extended Ethernet Bus Diagnostics
 *            2017-02-21  vismha  ESCAN00094071 EthIf Main-Function declarations provided by SchM
 *                                ESCAN00094070 Implement Dev error IDs according to ASR4.3
 *            2017-02-28  vismha  ESCAN00094199 EthIf allows transmission for same buffer multiple times
 *  08.00.01  2017-05-15  vismha  ESCAN00095136 Transmission of frames stops under high traffic conditions
 *  09.00.00  2017-11-16  vismha  STORYC-2926   FEAT-2521 [SAFE] SafeBSW for EthIf (ASIL B), S1ComStackLib
 *                                ESCAN00097916 Possibility of losing switch management/timestamp information
 *                                              indications
 *            2017-12-19  vismha  STORYC-417    FEAT-2521,S-451 [SAFE] SafeBSW for EthIf (ASIL B), S1IMP
 *                                ESCAN00095620 Compiler error: identifier "Eth_DataType" is undefined in
 *                                              EthIf_ExtndTrafficHndl.h
 *                                ESCAN00095626 Compiler error: expression must be an lvalue or a function designator
 *                                              EthIf_CfgAccess_VirtCtrl
 *  09.01.00  2017-12-20  vismha  STORYC-418    FEAT-2521,S-452 [SAFE] SafeBSW for EthIf (ASIL B), S1SIL - Review Helper
 *            2018-01-09  vismha  ESCAN00097907 Out of bounds access of array EthIf_OwnerSwtTsIdnsInfos under high
 *                                              traffic condition
 *  09.01.01  2018-03-28  vismha  ESCAN00098943 Invalid controller index is given to upper layer in Tx confirmation
 *                                              callback
 *  09.01.02  2018-04-09  vismha  ESCAN00099028 Managed frames aren't handled correctly
 *  10.00.00  2018-04-19  vismha  ESCAN00099161 Null pointer access during mirroring of a Tx-Frame
 *            2018-07-13  vismha  ESCAN00100026 DET check for EthIfCtrlIdx in EthIf_SwitchEnableEgressTimeStamp is
 *                                              incorrect
 *                                ESCAN00099785 Overflow detection for EthIf_GetRxStats()/EthIf_GetTxStats()
 *            2018-08-15  vismha  ESCAN00100405 Wrong source MAC used for frames in Mirroring/Gateway use-case
 *  11.00.00  2018-09-26  vismha  STORYC-4497   MISRA-C:2012 Compliance
 *            2018-10-23  vismha  STORYC-6414   [AVB] Implementation of 802.1Qbv extensions for EthIf
 *  11.01.00  2019-02-12  vismha  STORYC-7576   MISRA-C:2012 If_AsrIfEth - Boolean Rework
 *  11.01.01  2019-05-16  vismha  ESCAN00103166 MISRA deviation: MISRA-C:2012 Rule 2.2 and Rule 17.8
 *  12.00.00  2019-05-21  vismha  STORYC-7863   Remove Sub-Modules SwtMgmt and SwtTime and dependencies to other sub-modules
 *            2019-06-04  vismha  STORYC-7862   Migrate switch management  API still needed for ASR4.4.x to sub-module EthSwt
 *            2019-06-05  vismha  STORYC-7866   Migrate switch timestamping API still needed for ASR4.4.x to sub-module EthSwt
 *            2019-06-25  vismha  STORYC-7864   Introduce management object retrieval in reception path
 *                                STORYC-7865   Introduce management object retrieval in transmission path
 *  12.01.00  2019-08-20  visbgr  STORYC-8589   Release Ethernet Firewall functionality
 *                                ESCAN00102003 BETA version - the BSW module has a feature with BETA state (FEAT-2354)
 *                                ESCAN00096158 Ethernet firewall issues a transmission deny although EthIf shall just
 *                                              process a buffer release
 *                                ESCAN00104079 DET-Error ETHIF_E_INV_PARAM is triggered in EthIf_TxConfirmation in
 *                                              multi-Ethernet controller configurations
 *  12.02.00  2019-10-01  visdrr  ETH-606       Introduce driver abstraction API for the Ethernet switch enable/disable
 *                                              VLAN API
 *  12.03.00  2019-10-29  visbgr  ETH-47        Support ETM protocol according to AUTOSAR ATS 1.2.0 - incl.
 *                                              TC8 support - ETH/PHY primitives
 *  12.04.00  2020-02-03  visbgr  ETH-1195      Support EthIf_GetAndResetMeasurementData() incl. VAG-specific
 *                                              measurement point
 *  12.05.00  2020-04-07  vistoc  ETH-534       Polling of Signal Quality in EthIf_MainFunctionState()
 *                                ETH-1224      Introduce EthIf_GetSwitchPortSignalQuality() according to ASR4.4.x
 *                                ETH-1226      Allow clearing of min/max values measured for signal quality
 *  13.00.00  2020-04-22  visbmo  ETH-2143      Adapt implementation to changed EthIfController indices
 *  13.00.01  2020-06-19  visaay  ETH-2373      EthIf_SignalQualityResultType is not according AUTOSAR
 *  14.00.00  2020-07-02  virstl  ETH-1495      Fail Avoidance for EthIf including Ethernet Switches
 *            2020-11-04  visbgr  ESCAN00107178 Missing critical section for EthIf_CtrlLinkState
 *                                ESCAN00107186 Missing critical section for EthIf_PortGroupLinkState
 *                                ESCAN00107177 Missing critical section for EthSwtPortModeCnt
 *                                ESCAN00107175 Missing critical section for SignalQualityResult and
 *                                              PortSignalQualityResult
 *  14.01.00  2020-12-08  virstl  ETH-2104      Update CDD of EthIf_Init due to Safety Analysis results 
 *            2021-01-11  visbgr  ETH-2168      Support new configuration of EthIfTrcvLinkStateChgConfig
 *  15.00.00  2021-02-09  visaay  ETH-3568      EthIf - Report security events to IdsM
 *********************************************************************************************************************/

#if !defined (ETHIF_H)
# define ETHIF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1977
 *********************************************************************************************************/
# include "EthIf_Cbk.h"
/* Includes of EthIf_<Sub>.h */
# include "EthIf_EthCtrl.h"
# include "EthIf_EthSwt.h"
# include "EthIf_EthTrcv.h"
# include "EthIf_Gw.h"
# include "EthIf_Link.h"
# include "EthIf_Mirror.h"
# include "EthIf_Mode.h"
# include "EthIf_Rx.h"
# include "EthIf_Stats.h"
# include "EthIf_Tx.h"
# include "EthIf_Utils.h"
# include "EthIf_ZeroCopy.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Vendor and module identification */
# define ETHIF_VENDOR_ID                           (30u)
# define ETHIF_MODULE_ID                           (0x41u)  /* 65 decimal */

/* AUTOSAR Software specification version information */
/* \trace SPEC-2393556 */
# define ETHIF_AR_RELEASE_MAJOR_VERSION            (4u)
# define ETHIF_AR_RELEASE_MINOR_VERSION            (1u)
# define ETHIF_AR_RELEASE_REVISION_VERSION         (1u)

/* ----- Component version information (decimal version of ALM implementation package) ----- */
/* \trace SPEC-2393556 */
# define ETHIF_SW_MAJOR_VERSION                    (15u)
# define ETHIF_SW_MINOR_VERSION                    (0u)
# define ETHIF_SW_PATCH_VERSION                    (0u)

# define ETHIF_INSTANCE_ID_DET                     (0x00u)

/* ----- API service IDs ----- */
# define ETHIF_SID_INIT                                    (0x01u)
# define ETHIF_SID_CONTROLLER_INIT                         (0x02u)
# define ETHIF_SID_SET_CONTROLLER_MODE                     (0x03u)
# define ETHIF_SID_GET_CONTROLLER_MODE                     (0x04u)
# define ETHIF_SID_TRANSCEIVER_INIT                        (0x05u)
# define ETHIF_SID_SET_TRANSCEIVER_MODE                    (0x06u)
# define ETHIF_SID_GET_TRANSCEIVER_MODE                    (0x07u)
# define ETHIF_SID_GET_PHYS_ADDR                           (0x08u)
# define ETHIF_SID_PROVIDE_TX_BUFFER                       (0x09u)
# define ETHIF_SID_TRANSMIT                                (0x0Au)
# define ETHIF_SID_GET_VERSION_INFO                        (0x0Bu)
# define ETHIF_SID_UPDATE_PHYS_ADDR_FILTER                 (0x0Cu)
# define ETHIF_SID_SET_PHYS_ADDR                           (0x0Du)
# define ETHIF_SID_RELEASE_RX_BUFFER                       (0x0Eu)
# define ETHIF_SID_PROVIDE_EXT_TX_BUFFER                   (0x0Fu)
# define ETHIF_SID_RX_INDICATION                           (0x10u)
# define ETHIF_SID_TX_CONFIRMATION                         (0x11u)
# define ETHIF_SID_SET_PHY_TX_MODE                         (0x13u)
# define ETHIF_SID_GET_CABLE_DIAGNOSTICS_RESULT            (0x14u)
# define ETHIF_SID_SET_PHY_TEST_MODE                       (0x17u)
# define ETHIF_SID_GET_TRANSCEIVER_SIGNAL_QUALITY          (0x18u)
# define ETHIF_SID_CLEAR_TRANSCEIVER_SIGNAL_QUALITY        (0x19u)
# define ETHIF_SID_GET_SWITCH_PORT_SIGNAL_QUALITY          (0x1Au)
# define ETHIF_SID_CLEAR_SWITCH_PORT_SIGNAL_QUALITY        (0x1Bu)
# define ETHIF_SID_MAIN_FUNCTION_RX                        (0x20u)
# define ETHIF_SID_MAIN_FUNCTION_TX                        (0x21u)
# define ETHIF_SID_GET_CURRENT_TIME                        (0x22u)
# define ETHIF_SID_ENABLE_EGRESS_TIMESTAMP                 (0x23u)
# define ETHIF_SID_GET_EGRESS_TIMESTAMP                    (0x24u)
# define ETHIF_SID_GET_INGRESS_TIMESTAMP                   (0x25u)
# define ETHIF_SID_GET_PORT_MAC_ADDR                       (0x28u)
# define ETHIF_SID_GET_ARL_TABLE                           (0x29u)
# define ETHIF_SID_GET_BUFFER_LEVEL                        (0x2Au)
# define ETHIF_SID_GET_DROP_COUNT                          (0x2Bu)
# define ETHIF_SID_STORE_CONFIGURATION                     (0x2Cu)
# define ETHIF_SID_RESET_CONFIGURATION                     (0x2Du)
# define ETHIF_SID_SET_TRANSCEIVER_WAKEUP_MODE             (0x2Eu)
# define ETHIF_SID_GET_TRANSCEIVER_WAKEUP_MODE             (0x2Fu)
# define ETHIF_SID_CHECK_WAKEUP                            (0x30u)
# define ETHIF_SID_SET_SWITCH_MGMT_INFO                    (0x38u)
# define ETHIF_SID_SWITCH_ENABLE_TIME_STAMPING             (0x39u)
# define ETHIF_SID_GET_TX_HEADER_PTR                       (0x40u)
# define ETHIF_SID_GET_RX_HEADER_PTR                       (0x41u)
# define ETHIF_SID_GET_AND_RESET_MEASUREMENT_DATA          (0x45u)
# define ETHIF_SID_GET_RX_MGMT_OBJECT                      (0x47u)
# define ETHIF_SID_GET_TX_MGMT_OBJECT                      (0x48u)
# define ETHIF_SID_SET_BANDWIDTH_LIMIT                     (0x60u)
# define ETHIF_SID_GET_BANDWIDTH_LIMIT                     (0x61u)
# define ETHIF_SID_MIRRORING_GET_FREE_TX_TRAFFIC_INFO      (0x70u)
# define ETHIF_SID_MIRRORING_GET_RELATED_TX_TRAFFFIC_INFO  (0x71u)
# define ETHIF_SID_GATEWAY_MANIPULATE_PROMISCOUS_MODE      (0x72u)
# define ETHIF_SID_GATEWAY_GATEWAY_TRAFFIC                 (0x73u)
# define ETHIF_SID_SWITCH_PORT_GROUP_REQUEST_MODE          (0x90u)
# define ETHIF_SID_SWITCH_UPDATE_MCAST_PORT_ASSIGNMENT     (0xA0u)
# define ETHIF_SID_SWITCH_SET_CORRECTION_TIME              (0xA1u)
# define ETHIF_SID_START_SWITCH_QBV_SCHEDULE               (0xA2u)
# define ETHIF_SID_STOP_SWITCH_QBV_SCHEDULE                (0xA3u)
# define ETHIF_SID_GET_TX_STATS                            (0xB0u)
# define ETHIF_SID_GET_RX_STATS                            (0xB1u)
# define ETHIF_SID_SWITCH_ENABLE_VLAN                      (0xB2u)



/* ----- Error codes ----- */
/* \trace SPEC-2393570 */
# define ETHIF_E_NO_ERROR                                    (0x00u) /*!< no error occurred */
# define ETHIF_E_INV_CTRL_IDX                                (0x01u) /*!< Error code: API service was called with invalid controller index */
# define ETHIF_E_INV_TRCV_IDX                                (0x02u) /*!< Error code: API service was called with invalid transceiver index */
# define ETHIF_E_INV_PORT_GROUP_IDX                          (0x03u) /*!< Error code: API service was called with invalid port group index */
# define ETHIF_E_NOT_INITIALIZED                             (0x04u) /*!< Error code: API service used without module initialization */
# define ETHIF_E_INV_PARAM_POINTER                           (0x05u) /*!< Error code: API service used with invalid pointer parameter (NULL_PTR) */
# define ETHIF_E_INV_PARAM                                   (0x06u) /*!< Error code: API service used with invalid value for parameter */
# define ETHIF_E_INIT_FAILED                                 (0x07u) /*!< Error code: The service EthIf_Init() was called with an invalid configuration */
# define ETHIF_E_INV_SWITCH_IDX                              (0x08u) /*!< Error code: API service was called with invalid switch index */
# define ETHIF_E_INV_DRIVER_API_CALL                         (0x09u) /*!< Error code: API service can't be redirected to driver due to either configuration related lack or unsupported API */
# define ETHIF_E_INV_STATE                                   (0x0Au) /*!< Error code: API service processing leads to an invalid state of the module */
# define ETHIF_TRAFFIC_GATEWAY_E_MANIPULATE_PROMISCOUS_MODE  (0x10u) /*!< Error code: Promiscous mode couldn't be enabled on respective Ethernet controller */
# define ETHIF_TRAFFIC_GATEWAY_E_NO_BUFFER                   (0x11u) /*!< Error code: No Ethernet buffer could be acquired to gateway the traffic */
# define ETHIF_E_INTERNAL_ERROR                              (0xFFu) /*!< Error code: Internal error occurred */

/* ----- Modes ----- */
# define ETHIF_STATE_UNINIT                        (0x00u)
# define ETHIF_STATE_INIT                          (0x01u)

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

/**********************************************************************************************************************
 *  EthIf_InitMemory
 *********************************************************************************************************************/
/*! \brief          Function for *_INIT_*-variable initialization
 *  \details        Service to initialize module global variables at power up. This function initializes the
 *                  variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          CREQ-111162
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_InitMemory( void );

/**********************************************************************************************************************
 *  EthIf_Init
 *********************************************************************************************************************/
 /*! \brief         Initializes the EthIf module
  *  \details       Function initializes the module EthIf. It initializes all variables and sets the module state to
  *                 initialized. It must be called prior to using any other service except GetVersionInfo.
  *  \param[in]     CfgPtr  Configuration structure for initializing the module
  *  \pre           Interrupts are disabled.
  *  \pre           EthIf_InitMemory has been called unless EthIf_ModuleInitialized is initialized by start-up code.
  *  \pre           EthIf_Init has not been called yet. Re-Initialization of module is not possible.
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *  \trace         SPEC-2393574, SPEC-2393566
  *  \trace         CREQ-111162
  *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_Init(
  P2CONST(EthIf_ConfigType, AUTOMATIC, ETHIF_INIT_DATA) CfgPtr);

# if ( ETHIF_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  EthIf_GetVersionInfo
 *********************************************************************************************************************/
/*! \brief          Returns the version information
 *  \details        EthIf_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the
 *                  component.
 *  \param[out]     VersionInfoPtr  Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_VERSION_INFO_API
 *  \trace          SPEC-2393649
 *  \trace          CREQ-111173
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, ETHIF_APPL_VAR)  VersionInfoPtr);
# endif /* ETHIF_VERSION_INFO_API */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * \exclusivearea ETHIF_EXCLUSIVE_AREA_CTRL_INIT
 * Protects the allocation of the concurrent initialization protection semaphore.
 * \protects EthIf_InitLocked (read/write)
 * \usedin EthIf_ControllerInit
 * \exclude EthIf_ControllerInit (concurrent)
 * \length SHORT Check and allocation of semaphore.
 * \endexclusivearea
 *
 * \exclusivearea ETHIF_EXCLUSIVE_AREA_SET_CTRL_MODE
 * Protects the allocation of the recurrent mode change protection semaphore and processing of data needed for
 * link state information in switch and controller use case.
 * \protects EthIf_ModeChangeLocked (read/write), EthIf_EthSwtPortModeCnt (read/write),
 *           EthIf_CtrlLinkState (read/write), EthIf_PortGroupLinkState (read/write)
 * \usedin EthIf_SetControllerMode, EthIf_ProcessLinkStateChange, EthIf_ProcessSwtPortGroupLinkStateChange,
 *         EthIf_PollPortLinks, EthIf_DetectLinkStateChangesOnEthIfCtrls,
 *         EthIf_DetectLinkStateChangesOnEthIfSwtPortGroups, EthIf_IsModeRequestPossibleForEthIfSwtPortGroup,
 *         EthIf_UpdateEthIfCtrlStatesAfterDown, EthIf_SetEthIfSwtPortGroupMode,
 *         EthIf_AdjustEthIfSwtPortGroupModeCount, EthIf_TryTakeModeChangeSemaphore,
 *         EthIf_Internal_GetPortSignalQuality
 * \exclude Concurrent calls to the "usedin" functions.
 * \length SHORT Check and allocation of semaphore in EthIf_SetControllerMode;
 *         MEDIUM Query, allocation, setup and consistent processing of link state information, controller and switch
 *         port modes.
 * \endexclusivearea
 *
 * \exclusivearea ETHIF_EXCLUSIVE_AREA_TX_MIRROR_ELEMENT
 * Protects the allocation of data needed for TX frame mirroring.
 * \protects EthIf_MirrorTxInfo (read/write)
 * \usedin EthIf_ProvideTxBuffer, EthIf_ProvideExtTxBuffer
 * \exclude EthIf_ProvideTxBuffer (concurrent)
 * \length SHORT Query and allocation of a free element to process TX frame mirroring.
 * \endexclusivearea
 *
 * \exclusivearea ETHIF_EXCLUSIVE_AREA_RXTX_STATS
 * Protects the update of the TX and RX statistics.
 * \protects EthIf_EthIfCtrlRxStats (read/write), EthIf_EthIfCtrlTxStats (read/write)
 * \usedin EthIf_RxIndication, EthIf_Transmit, EthIf_VTransmit, EthIf_GetRxStats, EthIf_GetTxStats
 * \exclude Concurrent calls to the "usedin" functions.
 * \length SHORT Check for overruns, reading and writing of two counter values.
 * \endexclusivearea
 *
 * \exclusivearea ETHIF_EXCLUSIVE_AREA_SIGNAL_QUALITY
 * Protects the update of the signal quality statistics.
 * \protects EthIf_SignalQualityResult (read/write), EthIf_PortSignalQualityResult (read/write)
 * \usedin EthIf_Update_PortSignalQualityList, EthIf_Reset_PortSignalQualityList, EthIf_GetSwitchPortSignalQuality,
 *         EthIf_Update_TrcvSignalQualityList, EthIf_Reset_TrcvSignalQualityList, EthIf_GetTrcvSignalQuality
 * \exclude Concurrent calls to the "usedin" functions.
 * \length SHORT Check, reading and writing of signal quality counter values.
 * \endexclusivearea
 *
 */

#endif /* ETHIF_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf.h
 *********************************************************************************************************************/

