/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Crc_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2026-05-04, 15:21:14      !!!IGNORE-LINE!!!                   **
**                                                                            **
**  GENERATOR : Build b170330-0431          !!!IGNORE-LINE!!!                 **
**                                                                            **
**  BSW MODULE DECRIPTION : Crc.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : CRC configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of CRC Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef CRC_CFG_H
#define CRC_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

#define CRC_RUNTIME_MODE        (0x01u)
#define CRC_TABLE_MODE          (0x02u)
#define CRC_HARDWARE_MODE       (0x03u)

/*Macro for Initial Values of CRC*/
#define CRC_INITIAL_VALUE8      ((uint8)0xFFU)
#define CRC_INITIAL_VALUE8H2F   ((uint8)0xFFU)
#define CRC_INITIAL_VALUE16     ((uint16)0xFFFFU)
#define CRC_INITIAL_VALUE32     ((uint32)0xFFFFFFFFU)
#define CRC_INITIAL_VALUE32P4   ((uint32)0xFFFFFFFFU)

/*
Container : CRCGeneral
*/

/*Autosar specific information*/
#define CRC_AR_RELEASE_MAJOR_VERSION  (4U)
#define CRC_AR_RELEASE_MINOR_VERSION  (2U)
#define CRC_AR_RELEASE_REVISION_VERSION  (2U)

/*Release specific information*/
#define CRC_CFG_MAJOR_VERSION  (10U)
#define CRC_CFG_MINOR_VERSION  (40U)
#define CRC_CFG_PATCH_VERSION  (0U)
/*Macro for versioninfoapi*/
#define CRC_VERSION_INFO_API  (STD_OFF)

/*Macro for selection of 16 bit CRC method */
#define CRC_16_MODE (STD_OFF) 

/*Macro for selection of 32 bit CRC method */
#define CRC_32_MODE (STD_OFF) 
/*Macro for selection of 32 bit CRCP4 method */
#define CRC_32P4_MODE (STD_OFF) 
/*Macro for selection of 8 bit CRC method with 0x1D polynomial*/ 
#define CRC_8_MODE (STD_OFF) 
/*Macro for selection of 8 bit CRC method with 0x2F polynomial*/
#define CRC_8H2F_MODE (STD_OFF) 

/*Macro to enable /disable safety check*/
#define CRC_SAFETYENABLE              (STD_ON)

/*Macro for error return value for each polynomials*/
#define CRC_8_CONFIGERROR_VAL          (0)
#define CRC_8H2F_CONFIGERROR_VAL    (0)
#define CRC_16_CONFIGERROR_VAL      (0)
#define CRC_32_CONFIGERROR_VAL      (0)
#define CRC_32P4_CONFIGERROR_VAL      (0)

/*Macro for user/supervisory mode */
#define CRC_RUNTIME_API_MODE    (CRC_MCAL_SUPERVISOR)

#endif  /* CRC_CFG_H */

