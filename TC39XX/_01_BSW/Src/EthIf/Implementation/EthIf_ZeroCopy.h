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
/*!        \file  EthIf_ZeroCopy.h
 *        \brief  EthIf ZeroCopy public API header
 *
 *      \details  Provides access to the public API of the sub-module ZeroCopy of EthIf.
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

#if !defined (ETHIF_ZEROCOPY_H)
# define ETHIF_ZEROCOPY_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_ZeroCopy_Types.h"

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

# if ( ETHIF_ENABLE_ZERO_COPY_EXTENSIONS == STD_ON )                                                                    /* COV_ETHIF_QM_FEAT_CHECK_ON */
/***********************************************************************************************************************
 *  EthIf_ProvideExtTxBuffer
 **********************************************************************************************************************/
/*! \brief          Provides an external transmission buffer for an Ethernet frame
 *  \details        Function allows to provide an external buffer for an Ethernet frame transmission.
 *  \param[in]      CtrlIdx     EthIf controller index
 *  \param[in]      FrameType   EtherType to insert into the Ethernet frame header
 *  \param[in]      Priority    Priority of the Ethernet frame, which is coded into the PCP of the IEEE802.1Q
 *                              VLAN tag. If EthIf controller represents a physical data connection the
 *                              priority is ignored.
 *  \param[out]     BufIdxPtr   Index to identify the external buffer in context of EthIf
 *  \param[in,out]  BufPtr      Buffer pointer:
 *                              [in] - Location of the buffer provided externally
 *                              [out] - Location where payload can be written to
 *  \param[in,out]  LenBytePtr  Buffer length:
 *                              [in] - Length of the buffer in byte
 *                              [out] - Length of the buffer reduced by Ethernet header and, dependent on EthIf
 *                                      controller, by VLAN tag size
 *  \return         BUFREQ_OK - success
 *  \return         BUFREQ_E_NOT_OK - function has been called with invalid parameters
 *  \return         BUFREQ_E_BUSY - maximum amount of external buffers that can be handled reached
 *  \return         BUFREQ_E_OVFL - provided buffer is to small to hold the Ethernet header and, dependent on EthIf
 *                                  controller, the VLAN tag
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_ENABLE_ZERO_COPY_EXTENSIONS
 *  \trace          DSGN-EthIf22882
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, ETHIF_CODE) EthIf_ProvideExtTxBuffer(
        uint8                                                                       CtrlIdx,
        Eth_FrameType                                                               FrameType,
        uint8                                                                       Priority,
  P2VAR(uint8,                                          AUTOMATIC, ETHIF_APPL_VAR)  BufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR)  BufPtr,
  P2VAR(uint16,                                         AUTOMATIC, ETHIF_APPL_VAR)  LenBytePtr);

/***********************************************************************************************************************
 *  EthIf_ReleaseRxBuffer
 **********************************************************************************************************************/
/*! \brief          Releases an reception buffer
 *  \details        Function releases an reception buffer and allows the underlying Ethernet driver to reuse it for
 *                  further receptions.
 *  \param[in]      CtrlIdx  EthIf controller index
 *  \param[in]      BufPtr   Pointer to the buffer to be released
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_ENABLE_ZERO_COPY_EXTENSIONS
 *  \trace          DSGN-EthIf22881
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_ReleaseRxBuffer(
        uint8                                     CtrlIdx,
  P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR)  BufPtr);
# endif /* ETHIF_ENABLE_ZERO_COPY_EXTENSIONS */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_ZEROCOPY_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_ZeroCopy.h
 *********************************************************************************************************************/

