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
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Lin_GeneralTypes.h
 *        \brief  AUTOSAR LIN General types header
 *
 *      \details  AUTOSAR LIN General types header for the LIN stack
 *
 *********************************************************************************************************************/
 /**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Jan Gaukel                    visjgl        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *   1.00.00  2020-01-08  visjgl                create new Lin General Types
 *   1.00.01  2020-03-27  visjgl                rework Review findings
 *********************************************************************************************************************/

#if !defined (LIN_GENERALTYPES_H)
# define LIN_GENERALTYPES_H

/*!
  \name LIN General Types
  \{
*/

/**********************************************************************************************************************
 * LIN General Types
 *********************************************************************************************************************/

/*! LIN operation states for a LIN channel or frame, as returned by the API service Lin_GetStatus(). */
typedef enum Lin_StatusTypeTag
{
  /*! LIN frame operation return value.
      Development or production error occurred. */
  LIN_NOT_OK,

  /*! LIN frame operation return value.
      Successful transmission. */
  LIN_TX_OK,

  /*! LIN frame operation return value.
      Ongoing transmission (Header or Response). */
  LIN_TX_BUSY,

  /*! LIN frame operation return value.
      Erroneous header transmission such as:
       - Mismatch between sent and read back data
       - Identifier parity error or
       - Physical bus error */
  LIN_TX_HEADER_ERROR,

  /*! LIN frame operation return value.
      Erroneous response transmission such as:
       - Mismatch between sent and read back data
       - Physical bus error */
  LIN_TX_ERROR,

  /*! LIN frame operation return value.
      Successful frame response reception. */
  LIN_RX_OK,

  /*! LIN frame operation return value.
      Ongoing reception: at least one response byte has been received, but the checksum byte has not been received. */
  LIN_RX_BUSY,

  /*! LIN frame operation return value.
      Erroneous response reception such as:
       - Framing error
       - Overrun error
       - Checksum error or
       - Short response */
  LIN_RX_ERROR,

  /*! LIN frame operation return value.
      No response byte has been received. */
  LIN_RX_NO_RESPONSE,

  /*! LIN channel state return value.
      Normal operation; the related LIN channel is ready to transmit next header. No data from previous frame available
      (e.g. after initialization). */
  LIN_OPERATIONAL,

  /*! LIN channel state return value.
      Sleep state operation; in this state wake-up detection from slave nodes is enabled. */
  LIN_CH_SLEEP
}Lin_StatusType;

/*! This type represents the slave error types that are detected during header reception and response transmission / reception. */
typedef enum Lin_SlaveErrorTypeTag
{
  /*! Error in header. */
  LIN_ERR_HEADER,

  /*! Framing error in response. */
  LIN_ERR_RESP_STOPBIT,

  /*! Checksum error. */
  LIN_ERR_RESP_CHKSUM,

  /*! Monitoring error of transmitted data bit in response. */
  LIN_ERR_RESP_DATABIT,

  /*! No response. */
  LIN_ERR_NO_RESP,

  /*! Incomplete response. */
  LIN_ERR_INC_RESP
}Lin_SlaveErrorType;


/*! Pointer to pointer to a shadow buffer or memory mapped LIN hardware receive buffer where the current SDU is
    stored. */
typedef P2VAR(uint8, TYPEDEF, LIN_APPL_VAR) Lin_u8PtrType;


/*! Represents all valid protected identifier used by Lin_SendFrame(). */
typedef uint8 Lin_FramePidType;


/*! This type is used to specify the checksum model to be used for the LIN frame. */
typedef enum Lin_FrameCsModelTypeTag
{
  /*! Enhanced checksum model. */
  LIN_ENHANCED_CS,
  /*! Classic checksum model. */
  LIN_CLASSIC_CS
}Lin_FrameCsModelType;


/*! This type is used to specify whether the frame processor is required to transmit the
    response part of the LIN frame. */
typedef enum Lin_FrameResponseTypeTag
{
  /*! Response is generated by this node. */
  LIN_FRAMERESPONSE_TX,
  /*! Response is generated by an other node. */
  LIN_FRAMERESPONSE_RX,
  /*! Response is ignored by this node. */
  LIN_FRAMERESPONSE_IGNORE
}Lin_FrameResponseType;


/*! This type is used to specify the number of SDU data bytes to copy.
    Range: 1 - 8, data length of a LIN frame. */
typedef uint8 Lin_FrameDlType;


/*! This type is used to provide PID, checksum model, data length and SDU pointer of a LIN frame
    from the LIN Interface to the LIN driver.  */
typedef struct Lin_PduTypeTag
{
  /*! Valid protected identifier. */
  VAR(Lin_FramePidType, TYPEDEF)      Pid;
  /*! Specified Checksum model. */
  VAR(Lin_FrameCsModelType, TYPEDEF)  Cs;
  /*! Type of response part. */
  VAR(Lin_FrameResponseType, TYPEDEF) Drc;
  /*! Number of SDU data bytes to copy. */
  VAR(Lin_FrameDlType, TYPEDEF)       Dl;
  /*! Pointer to SDU data bytes. */
  P2VAR(uint8, TYPEDEF, LIN_APPL_VAR) SduPtr;
}Lin_PduType;

/*! \} */

/*!
  \name LIN Transceiver General Types
  \{
*/

/**********************************************************************************************************************
 * LIN Transceiver General Types
 *********************************************************************************************************************/

/*! This type is used to indicate and set the operation mode of the transceiver. */
typedef enum LinTrcv_TrcvModeTypeTag
{
  /*! Normal mode. */
  LINTRCV_TRCV_MODE_NORMAL,
  /*! Standby mode. */
  LINTRCV_TRCV_MODE_STANDBY,
  /*! Sleep mode. */
  LINTRCV_TRCV_MODE_SLEEP
} LinTrcv_TrcvModeType;

/*! This type is used to configure the wakeup setting of the transceiver. */
typedef enum LinTrcv_TrcvWakeupModeTypeTag
{
  /*! Enable wakeup reporting. */
  LINTRCV_WUMODE_ENABLE,
  /*! Disable wakeup reporting. */
  LINTRCV_WUMODE_DISABLE,
  /*! Clear the stored wakeup reason. */
  LINTRCV_WUMODE_CLEAR
} LinTrcv_TrcvWakeupModeType;

/*! This type is used to indicate the wakeup reason. */
typedef enum LinTrcv_TrcvWakeupReasonTypeTag
{
  /*! Error, wakeup reason was not detected. */
  LINTRCV_WU_ERROR,
  /*! Wakeup reporting is not supported. */
  LINTRCV_WU_NOT_SUPPORTED,
  /*! Wakeup caused by the network was detected. */
  LINTRCV_WU_BY_BUS,
  /*! Wakeup caused by a transceiver pin was detected. */
  LINTRCV_WU_BY_PIN,
  /*! Wakeup caused by a ECU request was detected. */
  LINTRCV_WU_INTERNALLY,
  /*! Wakeup caused by a ECU reset was detected. */
  LINTRCV_WU_RESET,
  /*! Wakeup caused by a ECU reset after power on was detected. */
  LINTRCV_WU_POWER_ON
} LinTrcv_TrcvWakeupReasonType;

/*! \} */

#endif /* LIN_GENERALTYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Lin_GeneralTypes.h
 *********************************************************************************************************************/

