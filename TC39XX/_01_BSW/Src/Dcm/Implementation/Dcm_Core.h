/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dcm_Core.h
 *        \brief  Public interface of DCM for other components
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
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
#if !defined(DCM_CORE_H)
# define DCM_CORE_H
/* ----------------------------------------------
 ~&&&   Versions
---------------------------------------------- */

/*! Implementation version */
# define DCM_CORE_MAJOR_VERSION                                      14u
# define DCM_CORE_MINOR_VERSION                                      5u
# define DCM_CORE_PATCH_VERSION                                      0u
/* ----------------------------------------------
 ~&&&   Defines
---------------------------------------------- */
/* DCM ErrorCode identifier used in the Det_ReportError call as ErrorId parameter value */
# define DCM_E_NO_ERROR                                              (Dcm_DetErrorCodeType)0x00u
/* Currently not used:
# define  DCM_E_INTERFACE_TIMEOUT                                    (Dcm_DetErrorCodeType)0x01u
 */
# define DCM_E_INTERFACE_RETURN_VALUE                                (Dcm_DetErrorCodeType)0x02u
# define DCM_E_INTERFACE_BUFFER_OVERFLOW                             (Dcm_DetErrorCodeType)0x03u
# define DCM_E_UNINIT                                                (Dcm_DetErrorCodeType)0x05u
# define DCM_E_PARAM                                                 (Dcm_DetErrorCodeType)0x06u
# define DCM_E_PARAM_POINTER                                         (Dcm_DetErrorCodeType)0x07u
/* Vendor DCM specific DET situations */
# define DCM_E_ILLEGAL_STATE                                         (Dcm_DetErrorCodeType)0x40u
# define DCM_E_INVALID_CONFIG                                        (Dcm_DetErrorCodeType)0x41u
# define DCM_E_CRITICAL_ERROR                                        (Dcm_DetErrorCodeType)0x42u

/* DCM API identifier used in the Det_ReportError call as "ApiId" (ServiceId) parameter value */
# define DCM_SID_STARTOFRECEPTION                                    (Dcm_DetApiIdType)0x00u
# define DCM_SID_INIT                                                (Dcm_DetApiIdType)0x01u
# define DCM_SID_COPYRXDATA                                          (Dcm_DetApiIdType)0x02u
# define DCM_SID_TPRXINDICATION                                      (Dcm_DetApiIdType)0x03u
# define DCM_SID_COPYTXDATA                                          (Dcm_DetApiIdType)0x04u
# define DCM_SID_TPTXCONFIRMATION                                    (Dcm_DetApiIdType)0x05u
# define DCM_SID_GETSESCTRLTYPE                                      (Dcm_DetApiIdType)0x06u
# define DCM_SID_GETSECLEVEL                                         (Dcm_DetApiIdType)0x0Du
# define DCM_SID_GETACTIVEPROTOCOL                                   (Dcm_DetApiIdType)0x0Fu

# define DCM_SID_COMMENTERNOCOMMODE                                  (Dcm_DetApiIdType)0x21u
# define DCM_SID_COMMENTERSILENTCOMMODE                              (Dcm_DetApiIdType)0x22u
# define DCM_SID_COMMENTERFULLCOMMODE                                (Dcm_DetApiIdType)0x23u
# define DCM_SID_GETVERSIONINFO                                      (Dcm_DetApiIdType)0x24u
# define DCM_SID_MAINFUNCTION                                        (Dcm_DetApiIdType)0x25u

# define DCM_SID_RESET2DEFAULTSESSION                                (Dcm_DetApiIdType)0x2Au
# define DCM_SID_DEMTRIGGERONDTCSTATUS                               (Dcm_DetApiIdType)0x2Bu
# define DCM_SID_TRIGGERONEVENT                                      (Dcm_DetApiIdType)0x2Du

# define DCM_SID_EXT_SETNEGRESPONSE                                  (Dcm_DetApiIdType)0x30u
# define DCM_SID_EXT_PROCESSINGDONE                                  (Dcm_DetApiIdType)0x31u
# define DCM_SID_EXT_DIAGSVC_PROCESSOR                               (Dcm_DetApiIdType)0x32u

/* Service ports */
# define DCM_SID_SVCPORT_DATASVCS_OP_READDATA_SYNC                   (Dcm_DetApiIdType)0x34u
# define DCM_SID_SVCPORT_DATASVCS_OP_READDATA_ASYNC                  (Dcm_DetApiIdType)0x3Bu
# define DCM_SID_SVCPORT_DATASVCS_OP_ISAVAILABLEDIDRANGE             (Dcm_DetApiIdType)0x3Fu
# define DCM_SID_SVCPORT_DATASVCS_OP_READDIDRANGE                    (Dcm_DetApiIdType)0x40u
# define DCM_SID_SVCPORT_DATASVCS_OP_WRITEDIDRANGE                   (Dcm_DetApiIdType)0x41u

# define DCM_SID_GETSEED                                             (Dcm_DetApiIdType)0x44u
# define DCM_SID_GETSEED_ACCESSDATA_RECORD                           (Dcm_DetApiIdType)0x45u
# define DCM_SID_COMPARE_KEY                                         (Dcm_DetApiIdType)0x47u

# define DCM_SID_SETACTIVEDIAGNOSTIC                                 (Dcm_DetApiIdType)0x56u
# define DCM_SID_GETSECURITYATTEMPTCOUNTER                           (Dcm_DetApiIdType)0x59u
# define DCM_SID_SETSECURITYATTEMPTCOUNTER                           (Dcm_DetApiIdType)0x5Au

# define DCM_SID_SVCPORT_DATASVCS_OP_READVID                         (Dcm_DetApiIdType)0x60u /* Specified in AR DCM SWS 4.3 */

# define DCM_SID_DCMSETDEAUTHENTICATEDROLE                           (Dcm_DetApiIdType)0x79u

/* Vendor specific DET service ids for more detailed analysis */
# define DCM_SID_TXCONFIRMATION                                      (Dcm_DetApiIdType)0xA1u /* AR DCM SWS 4.2.0 does not specify a SID -> using vendor specific one */
# define DCM_SID_TRIGGERTRANSMIT                                     (Dcm_DetApiIdType)0xA2u /* AR DCM SWS 4.2.0 does not specify a SID -> using vendor specific one */
# define DCM_SID_PROVIDERECOVERYSTATES                               (Dcm_DetApiIdType)0xA3u
# define DCM_SID_ONREQUESTDETECTION                                  (Dcm_DetApiIdType)0xA4u
# define DCM_SID_GETRECOVERYSTATES                                   (Dcm_DetApiIdType)0xA5u
# define DCM_SID_GETTESTERSOURCEADDRESS                              (Dcm_DetApiIdType)0xA6u
# define DCM_SID_GETSECLEVELFIXEDBYTES                               (Dcm_DetApiIdType)0xA7u
# define DCM_SID_PROCESSVIRTUALREQUEST                               (Dcm_DetApiIdType)0xA8u
# define DCM_SID_SETSECLEVEL                                         (Dcm_DetApiIdType)0xA9u
# define DCM_SID_SVCPORT_DATASVCS_OP_READPAGEDDID                    (Dcm_DetApiIdType)0xAAu
# define DCM_SID_GETREQUESTKIND                                      (Dcm_DetApiIdType)0xABu

# define DCM_SID_VSGSETSINGLE                                        (Dcm_DetApiIdType)0xACu
# define DCM_SID_VSGISACTIVE                                         (Dcm_DetApiIdType)0xADu
# define DCM_SID_VSGSETMULTIPLE                                      (Dcm_DetApiIdType)0xAEu
# define DCM_SID_VSGISACTIVEANY                                      (Dcm_DetApiIdType)0xAFu

# define DCM_SID_SVC_DISPATCHER                                      (Dcm_DetApiIdType)0xB0u

# define DCM_SID_KEYMASYNCCERTIFICATEVERIFYFINISHED                  (Dcm_DetApiIdType)0xB1u
# define DCM_SID_CSMASYNCJOBFINISHED                                 (Dcm_DetApiIdType)0xB2u

# define DCM_SID_SETSECURITYBYPASS                                   (Dcm_DetApiIdType)0xB3u

# define DCM_SID_INTERNAL                                            (Dcm_DetApiIdType)0xF0u
# define DCM_SID_SERVICE_PROCESSOR                                   DCM_SID_INTERNAL

# define DCM_EXT_SID_INTERNAL                                        (Dcm_ExtendedSidType)0x00
# define DCM_EXT_SID_CFGRIDMGROPINFOGETENTRY                         (Dcm_ExtendedSidType)0x01
# define DCM_EXT_SID_DIAGMSGCONTEXTVERIFYSIZE                        (Dcm_ExtendedSidType)0x02
# define DCM_EXT_SID_NETGETCOMMCONTEXT                               (Dcm_ExtendedSidType)0x03
# define DCM_EXT_SID_NETGETBUFFERCONTEXT                             (Dcm_ExtendedSidType)0x04
# define DCM_EXT_SID_NETGETTRANSPORTOBJECT                           (Dcm_ExtendedSidType)0x05
# define DCM_EXT_SID_NETSETCOMCONTROLCHANNELSTATE                    (Dcm_ExtendedSidType)0x06
# define DCM_EXT_SID_NETPUTTOCONN2TOBJMAP                            (Dcm_ExtendedSidType)0x07
# define DCM_EXT_SID_NETWRITEADDBUFFERU8AT                           (Dcm_ExtendedSidType)0x08
# define DCM_EXT_SID_NETGETBUFFERINFO                                (Dcm_ExtendedSidType)0x09
# define DCM_EXT_SID_CFGMODEMGRRULESGETENTRY                         (Dcm_ExtendedSidType)0x0A
# define DCM_EXT_SID_MODEMONITORCONTROLDTCSETTING                    (Dcm_ExtendedSidType)0x0C
# define DCM_EXT_SID_MODEMONITORCOMMUNICATIONCONTROL                 (Dcm_ExtendedSidType)0x0D
# define DCM_EXT_SID_TSKGETTASKINFO                                  (Dcm_ExtendedSidType)0x0E
# define DCM_EXT_SID_TSKGETTASKCONTEXT                               (Dcm_ExtendedSidType)0x0F
# define DCM_EXT_SID_TSKREGISTERACTIVETASK                           (Dcm_ExtendedSidType)0x10
# define DCM_EXT_SID_TSKUNREGISTERACTIVETASK                         (Dcm_ExtendedSidType)0x11
# define DCM_EXT_SID_TSKGETSCHEDULERCONTEXT                          (Dcm_ExtendedSidType)0x12
# define DCM_EXT_SID_TMRGETTIMERINFO                                 (Dcm_ExtendedSidType)0x13
# define DCM_EXT_SID_TMRGETTIMERCONTEXT                              (Dcm_ExtendedSidType)0x14
# define DCM_EXT_SID_DIAGGETPOSTPROCESSORFUNC                        (Dcm_ExtendedSidType)0x15
# define DCM_EXT_SID_DIAGGETUPDATEFUNC                               (Dcm_ExtendedSidType)0x16
# define DCM_EXT_SID_DIAGGETCANCELFUNC                               (Dcm_ExtendedSidType)0x17
# define DCM_EXT_SID_DIAGPUTSTARTUPFBLRESBUFFER                      (Dcm_ExtendedSidType)0x18
# define DCM_EXT_SID_DIAGCOMMITDATA                                  (Dcm_ExtendedSidType)0x19
# define DCM_EXT_SID_DIAGREVERTDATA                                  (Dcm_ExtendedSidType)0x1A
# define DCM_EXT_SID_DIAGPROVIDEDATAASU8                             (Dcm_ExtendedSidType)0x1B
# define DCM_EXT_SID_CFGSVC11SUBFUNCINFOGETENTRY                     (Dcm_ExtendedSidType)0x1C
# define DCM_EXT_SID_CFGSVC19SUBFUNCINFOGETENTRY                     (Dcm_ExtendedSidType)0x1D
# define DCM_EXT_SID_CFGSVC28SUBFUNCINFOGETENTRY                     (Dcm_ExtendedSidType)0x1F
# define DCM_EXT_SID_CFGSVC2CSUBFUNCINFOGETENTRY                     (Dcm_ExtendedSidType)0x20
# define DCM_EXT_SID_CFGSVC86SUBFUNCINFOGETENTRY                     (Dcm_ExtendedSidType)0x21
# define DCM_EXT_SID_NETALLOCATEORGETTRANSPOBJECT                    (Dcm_ExtendedSidType)0x22
# define DCM_EXT_SID_NETGETTRANSPOBJOFCONNECTION                     (Dcm_ExtendedSidType)0x23
# define DCM_EXT_SID_UTIMEMCOPYSAFE                                  (Dcm_ExtendedSidType)0x24
# define DCM_EXT_SID_NETRXINDINTERNAL                                (Dcm_ExtendedSidType)0x25
# define DCM_EXT_SID_DIAGSETREQDATAASU8AT                            (Dcm_ExtendedSidType)0x26
# define DCM_EXT_SID_DIAGSETRESDATAASU8AT                            (Dcm_ExtendedSidType)0x27
# define DCM_EXT_SID_DIAGSETDATAASU8AT                               (Dcm_ExtendedSidType)0x28
# define DCM_EXT_SID_DIAGGETRESDATAAT                                (Dcm_ExtendedSidType)0x29
# define DCM_EXT_SID_DIAGGETREAMINGRESLENWITHOFFSET                  (Dcm_ExtendedSidType)0x2A
# define DCM_EXT_SID_CFGSVC85SUBFUNCINFOGETENTRY                     (Dcm_ExtendedSidType)0x2B
# define DCM_EXT_SID_CFGDIAGSERVICEINFOGETENTRY                      (Dcm_ExtendedSidType)0x2C
# define DCM_EXT_SID_DIAGPROVIDERESDATA                              (Dcm_ExtendedSidType)0x2D
# define DCM_EXT_SID_DIAGUPDATERESLENGTH                             (Dcm_ExtendedSidType)0x2E
# define DCM_EXT_SID_DIAGSETNEWREQBASETOCURPROGRESS                  (Dcm_ExtendedSidType)0x2F
# define DCM_EXT_SID_DIAGSETNEWRESBASETOCURPROGRESS                  (Dcm_ExtendedSidType)0x30
# define DCM_EXT_SID_SVC22GETDIDINFOCONTEXT                          (Dcm_ExtendedSidType)0x31
# define DCM_EXT_SID_SVC27COUNTERSET                                 (Dcm_ExtendedSidType)0x32
# define DCM_EXT_SID_SVC27TIMERSET                                   (Dcm_ExtendedSidType)0x33
# define DCM_EXT_SID_CFGSVC27SECLEVELINFOGETENTRY                    (Dcm_ExtendedSidType)0x34
# define DCM_EXT_SID_CFGDIDMGRSIGNALOPCLASSINFOGETENTRY              (Dcm_ExtendedSidType)0x36
# define DCM_EXT_SID_DIAGDATACONTEXTVERIFYSIZE                       (Dcm_ExtendedSidType)0x37
# define DCM_EXT_SID_DIAGSETAVAILLEN                                 (Dcm_ExtendedSidType)0x38
# define DCM_EXT_SID_SVC2ASCHDGETENTRY                               (Dcm_ExtendedSidType)0x39
# define DCM_EXT_SID_NETDELAYTIMERSET                                (Dcm_ExtendedSidType)0x3A
# define DCM_EXT_SID_NETGETPERIODICTXOBJECT                          (Dcm_ExtendedSidType)0x3B
# define DCM_EXT_SID_NETPERIODICMSGTRANSMIT                          (Dcm_ExtendedSidType)0x3C
# define DCM_EXT_SID_CFGSVC08SERVICEINFOGETENTRY                     (Dcm_ExtendedSidType)0x3D
# define DCM_EXT_SID_SVC2CGETSRCITEM                                 (Dcm_ExtendedSidType)0x3E
# define DCM_EXT_SID_SVC2CGETDDDIDPROCESSCONTEXT                     (Dcm_ExtendedSidType)0x3F
# define DCM_EXT_SID_SVC2CGETITEM                                    (Dcm_ExtendedSidType)0x40
# define DCM_EXT_SID_CFGSVC09SERVICEINFOGETENTTRY                    (Dcm_ExtendedSidType)0x41
# define DCM_EXT_SID_CFGSVC01SERVICEINFOGETENTTRY                    (Dcm_ExtendedSidType)0x42
# define DCM_EXT_SID_CFGSVC06MIDTIDINFOGETENTTRY                     (Dcm_ExtendedSidType)0x43
# define DCM_EXT_SID_CFGDIDMGRDIDOPCLASSINFOGETENTRY                 (Dcm_ExtendedSidType)0x44
# define DCM_EXT_SID_SVC2FGETACTIVEIODIDS                            (Dcm_ExtendedSidType)0x45
# define DCM_EXT_SID_UTIBITSETGETROWIDXSAFE                          (Dcm_ExtendedSidType)0x46
# define DCM_EXT_SID_CFGDIDMGRIOCONTROLGETSENDERRECEIVERHANDLERS     (Dcm_ExtendedSidType)0x47
# define DCM_EXT_SID_MODESWITCHROE                                   (Dcm_ExtendedSidType)0x48
# define DCM_EXT_SID_DIAGGETRECOVERYINFOCOMMCHANNELSTATEITEM         (Dcm_ExtendedSidType)0x49
# define DCM_EXT_SID_DIAGGETRECOVERYINFOCOMMCONTROLSTATE             (Dcm_ExtendedSidType)0x50
# define DCM_EXT_SID_SETSPECIFICCAUSECODE                            (Dcm_ExtendedSidType)0x51
# define DCM_EXT_SID_GETTHREADCONTEXT                                (Dcm_ExtendedSidType)0x52
# define DCM_EXT_SID_AUTHMGRSETCONNAUTHSTATE                         (Dcm_ExtendedSidType)0x53
# define DCM_EXT_SID_CFGSVC29SUBFUNCINFOGETENTRY                     (Dcm_ExtendedSidType)0x54
# define DCM_EXT_SID_MODESWITCHSETAUTHENTICATIONSTATE                (Dcm_ExtendedSidType)0x55
# define DCM_EXT_SID_AUTHMGRGETWLCONTEXT                             (Dcm_ExtendedSidType)0x56
# define DCM_EXT_SID_AUTHMGRGETROLECONTEXT                           (Dcm_ExtendedSidType)0x57
# define DCM_EXT_SID_AUTHMGRUPDATEACTIVEROLE                         (Dcm_ExtendedSidType)0x58
# define DCM_EXT_SID_AUTHMGRREADROLE                                 (Dcm_ExtendedSidType)0x59
# define DCM_EXT_SID_AUTHMGRSERVICEWLREADLIST                        (Dcm_ExtendedSidType)0x5A
# define DCM_EXT_SID_AUTHMGRDIDWLREADLIST                            (Dcm_ExtendedSidType)0x5B
# define DCM_EXT_SID_AUTHMGRRIDWLREADLIST                            (Dcm_ExtendedSidType)0x5C
# define DCM_EXT_SID_AUTHMGRMEMWLREADLIST                            (Dcm_ExtendedSidType)0x5D
# define DCM_EXT_SID_AUTHMGRGETCERTWLELEMENT                         (Dcm_ExtendedSidType)0x5E
# define DCM_EXT_SID_AUTHMGRTIMERSET                                 (Dcm_ExtendedSidType)0x5F
# define DCM_EXT_SID_AUTHMGRSETPENDINGROLE                           (Dcm_ExtendedSidType)0x60
/* ----------------------------------------------
 ~&&&   Function-like macros
---------------------------------------------- */
/*! Compose a 16 bit value from bytes */
# define Dcm_UtiMake16Bit(hiByte,loByte)                             ((uint16)((((uint16)(hiByte))<<8)|                                              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */ \
                                                                     ((uint16)(loByte))))
/*! Compose a 32bit value from single bytes */
# define Dcm_UtiMake32Bit(hiHiByte,hiLoByte,loHiByte,loLoByte)       ((uint32)((((uint32)(hiHiByte))<<24)|                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */ \
                                                                     (((uint32)(hiLoByte))<<16)| \
                                                                     (((uint32)(loHiByte))<<8) | \
                                                                     ((uint32)(loLoByte))))
/*! Extract the MSB of a WORD value */
# define Dcm_UtiGetHiByte(data16)                                    ((uint8)(((uint16)(data16))>>8))                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract the LSB of a WORD value */
# define Dcm_UtiGetLoByte(data16)                                    ((uint8)(((uint16)(data16)) & 0xFFu))                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Extract the MSB of a DWORD value */
# define Dcm_UtiGetHiHiByte(data32)                                  ((uint8)(((uint32)(data32))>>24))                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract the byte next to the MSB of a DWORD value */
# define Dcm_UtiGetHiLoByte(data32)                                  ((uint8)(((uint32)(data32))>>16))                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract the byte next to the LSB of a DWORD value */
# define Dcm_UtiGetLoHiByte(data32)                                  ((uint8)(((uint32)(data32))>>8))                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract the LSB of a DWORD value */
# define Dcm_UtiGetLoLoByte(data32)                                  ((uint8)(((uint32)(data32)) & 0xFFu))                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Extract the MSW of a DWORD value */
# define Dcm_UtiGetHiWord(data32)                                    ((uint16)(((uint32)(data32))>>16))                                              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract the LSW of a DWORD value */
# define Dcm_UtiGetLoWord(data32)                                    ((uint16)(((uint32)(data32)) & 0xFFFFu))                                        /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Extract MSN of a BYTE value */
# define Dcm_UtiGetHiNibble(data8)                                   ((uint8)(((uint8)(data8))>>4))                                                  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract LSN of a BYTE value */
# define Dcm_UtiGetLoNibble(data8)                                   ((uint8)(((uint8)(data8)) & 0x0Fu))                                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Avoid warnings of unused API parameters */
# define DCM_IGNORE_UNREF_PARAM(param)                               ((void)(param))                                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/* ----------------------------------------------
 ~&&&   Module API function declarations
---------------------------------------------- */
# define DCM_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
# if (DCM_AUTHMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_AUTHMGR_SET_DEAUTH_ROLE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_SetDeauthenticatedRole()
 *********************************************************************************************************************/
/*! \brief          Overwrites the configured deauthentication role of a connection of the given index.
 *  \details        The time between the function call and the update of the deauthenticated role depends on the
 *                  current DCM state. The minimum time to be expected is one DCM task cycle. If this service is called
 *                  while the DCM is processing a diagnostic request, the update will be postponed till the end of
 *                  this service processing, to avoid unpredictable behavior.
 *  \param[in]      connectionId           The connection identifier (not the connection handle)
 *  \param[in]      deauthenticatedRole    New deauthenticated role
 *  \return         E_OK is always returned
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetDeauthenticatedRole(
  uint16 connectionId,
  P2CONST(uint8, AUTOMATIC, RTE_DCM_APPL_DATA) deauthenticatedRole
  );
#  endif
# endif /* (DCM_AUTHMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Dcm_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief          Reports component's version information.
 *  \details        Returns the version information of the used DCM implementation.
 *  \param[out]     versioninfo    pointer to the application structure
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_VERSION_INFO_API = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DCM_APPL_DATA) versioninfo
  );
# endif
/**********************************************************************************************************************
 *  Dcm_GetActiveProtocol()
 *********************************************************************************************************************/
/*! \brief          Returns the currently active protocol.
 *  \details        This function returns the active protocol Id.
 *  \param[out]     ActiveProtocol    Will contain the currently active protocol ID
 *  \return         DCM_E_OK          This value is always returned (also in error case)
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetActiveProtocol(
  P2VAR(Dcm_ProtocolType, AUTOMATIC, DCM_APPL_DATA) ActiveProtocol
  );

/**********************************************************************************************************************
 *  Dcm_GetTesterSourceAddress()
 *********************************************************************************************************************/
/*! \brief          Returns a DCM tester's SourceAddress.
 *  \details        Returns a DCM tester's SourceAddress for a given RxPduId.
 *  \param[in]      DcmRxPduId             The DCM RxPduId of the tester connection which SourceAddress will be read
 *  \param[out]     TesterSourceAddress    Will contain the corresponding tester's SourceAddress
 *  \return         DCM_E_OK               The TesterSourceAddress out parameter contains a valid value
 *  \return         DCM_E_NOT_OK           The TesterSourceAddress out parameter does not have a valid return value
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetTesterSourceAddress(
  PduIdType DcmRxPduId,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) TesterSourceAddress
  );

# if (DCM_DIAG_VIRTUAL_REQUEST_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ProcessVirtualRequest()
 *********************************************************************************************************************/
/*! \brief          Provides a means for internal (ROE) requests triggered by the application.
 *  \details        -
 *  \param[in]      RxPduId            The RxPDUID of the request
 *  \param[in]      Data               The data of the request. In case of generic connections, tester source address
 *                                     stored in the last byte.
 *  \param[in]      Length             The length of the request
 *  \return         DCM_E_OK           Reception was successful
 *  \return         DCM_E_NOT_OK       Reception was not successful
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            DCM_DIAG_VIRTUAL_REQUEST_ENABLED == STD_ON
 *  \trace          CREQ-113929
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessVirtualRequest(
  PduIdType RxPduId,
  Dcm_MsgType Data,
  PduLengthType Length
  );
# endif

/**********************************************************************************************************************
 *  Dcm_SetActiveDiagnostic()
 *********************************************************************************************************************/
/*! \brief          Notifies DCM to (not) keep ComM channels awake.
 *  \details        -
 *  \param[in]      active             The new DCM ComM interaction mode
 *  \return         DCM_E_OK           This value is always returned (also in error case)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetActiveDiagnostic(
  boolean active
  );

/**********************************************************************************************************************
 *  Dcm_GetRequestKind()
 *********************************************************************************************************************/
/*! \brief          Returns the request kind of a DCM tester SourceAddress.
 *  \details        Returns the request kind for a given diagnostic client.
 *  \param[in]      TesterSourceAddress    Will contain the corresponding tester's SourceAddress
 *  \param[out]     RequestKind            The request kind ([DCM_REQ_KIND]_NONE, _EXTERNAL and _ROE)
 *  \return         DCM_E_OK               The RequestKind out parameter contains a valid value
 *  \return         DCM_E_NOT_OK           The RequestKind out parameter does not have a valid return value
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetRequestKind(
  uint16 TesterSourceAddress,
  P2VAR(Dcm_RequestKindType, AUTOMATIC, DCM_APPL_DATA) RequestKind
  );
/**********************************************************************************************************************
 *  Dcm_ResetToDefaultSession()
 *********************************************************************************************************************/
/*! \brief          Provides a means for enforced resetting to the default session.
 *  \details        The call to this function allows the application to reset the current session to Default session.
 *                  Example: Automatic termination of an extended diagnostic session upon exceeding of a speed limit.
 *                  Note: The time between the function call and the termination of the session depends on the current
 *                        DCM state. The minimum time to be expected is one DCM task cycle. If this service is called
 *                        while the DCM is processing a diagnostic request, the session termination will be postponed
 *                        till the end of this service processing, to avoid unpredictable behavior.
 *  \return         E_OK    This value is always returned (also in error case)
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_ResetToDefaultSession(
  void
  );

/**********************************************************************************************************************
 *  Dcm_GetSesCtrlType()
 *********************************************************************************************************************/
/*! \brief          Provides read access to the DCM's diagnostic session register.
 *  \details        This function provides the active session control type value.
 *  \param[out]     SesCtrlType    Pointer to a RAM address where DCM will store the current session
 *  \return         E_OK           This value is always returned (also in error case)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \trace          CREQ-113936
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType(
  P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SesCtrlType
  );

# if (DCM_STATE_SECURITY_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_GetSecurityLevel()
 *********************************************************************************************************************/
/*! \brief          Provides read access to the DCM's security access register.
 *  \details        This function provides the active security level value.
 *  \param[out]     SecLevel    Pointer to a RAM address where DCM will store the current security level
 *  \return         E_OK        This value is always returned (also in error case)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_STATE_SECURITY_ENABLED = STD_ON.
 *  \pre            -
 *  \trace          CREQ-113940
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSecurityLevel(
  P2VAR(Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA) SecLevel
  );
# endif

# if (DCM_STATE_SECURITY_EXT_SETTER_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_SetSecurityLevel()
 *********************************************************************************************************************/
/*! \brief          Provides write access to the DCM's security access register.
 *  \details        This function performs security level transition.
 *  \param[in]      SecLevel    The new security level to switch into
 *  \return         E_OK        State change has been performed.
 *  \return         E_NOT_OK    State change failed. Possible reasons:
 *                              - wrong/invalid security level;
 *                              - called while DCM is busy with a diagnostic request;
 *                              - called from wrong task context (not from Dcm_MainFunctionWorker);
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_STATE_SECURITY_EXT_SETTER_ENABLED = STD_ON.
 *  \pre            -
 *  \trace          CREQ-129518
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetSecurityLevel(
  Dcm_SecLevelType SecLevel
  );
# endif

# if (DCM_STATE_SECURITY_FIXED_BYTES_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_GetSecurityLevelFixedBytes()
 *********************************************************************************************************************/
/*! \brief          Provides fixed bytes set up for a specific security level.
 *  \details        This function provides the fixed bytes for the requested security level.
 *                  A security level without configured fixed bytes will return E_OK and no bytes (bufferSize = 0)
 *  \param[in]      SecLevel              The requested security level
 *  \param[out]     FixedBytes            Buffer to receive the fixed byte values
 *  \param[in,out]  BufferSize
 *                  IN                    The provided buffer size
 *                  OUT                   The number of fixed bytes for the requested level
 *  \return         E_OK                  The security bytes were copied to the provided buffer
 *  \return         DCM_E_NOT_OK          The security level is not configured
 *  \return         DCM_E_BUFFERTOOLOW    The buffer was too small, BufferSize will contain the number of bytes needed
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_STATE_SECURITY_FIXED_BYTES_ENABLED = STD_ON
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSecurityLevelFixedBytes(
  Dcm_SecLevelType SecLevel,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) FixedBytes,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) BufferSize
  );
# endif

# if (DCM_STATE_SECURITY_BYPASS_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_SetSecurityBypass()
 *********************************************************************************************************************/
/*! \brief          Enables a bypass to security states of Dcm.
 *  \details        The call to this function allows the application to bypass the internal DCM security states.
 *  \param[in]      SecBypass       The new bypass mode.
 *  \return         DCM_E_OK        Security bypass mode has been performed.
 *  \return         DCM_E_NOT_OK    Some error has occurred. Possible reasons:
 *                                  - DCM is not yet initialized;
 *                                  - Wrong/invalid SecBypass parameter;
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_STATE_SECURITY_BYPASS_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetSecurityBypass(
  boolean SecBypass
  );
# endif
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_DIDMGR_EXTENDED_LOOKUP_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_FilterDidLookUpResult()
 *********************************************************************************************************************/
/*! \brief          Provides a means to get supported DID suppressed by the application.
 *  \details        -
 *  \param[in]      OpStatus                Current operation status.
 *  \param[in]      Did                     The requested DID the filtering shall be done.
 *  \param[in]      DidOperation            The requested DID operation the filtering shall be done.
 *  \return         DCM_E_OK                The DID is (still) active.
 *  \return         DCM_E_PENDING           The DID validation needs more time. Call me again.
 *  \return         DCM_E_NOT_OK            The DID is not active.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_DIDMGR_EXTENDED_LOOKUP_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_FilterDidLookUpResult(
  Dcm_OpStatusType OpStatus,
  uint16 Did,
  Dcm_DidOpType DidOperation
  );
#  endif
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_RIDMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_RIDMGR_EXTENDED_LOOKUP_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_FilterRidLookUpResult()
 *********************************************************************************************************************/
/*! \brief          Provides a means to get supported RID suppressed by the application.
 *  \details        -
 *  \param[in]      OpStatus                Current operation status.
 *  \param[in]      Rid                     The requested RID the filtering shall be done.
 *  \return         DCM_E_OK                The RID is (still) active.
 *  \return         DCM_E_PENDING           The RID validation needs more time. Call me again.
 *  \return         DCM_E_NOT_OK            The RID is not active.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_RIDMGR_EXTENDED_LOOKUP_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_FilterRidLookUpResult(
  Dcm_OpStatusType OpStatus,
  uint16 Rid
  );
#  endif
# endif /* (DCM_RIDMGR_SUPPORT_ENABLED == STD_ON) */
/**********************************************************************************************************************
 *  Dcm_Init()
 *********************************************************************************************************************/
/*! \brief          Modules initialization.
 *  \details        Service for basic initialization of DCM module.
 *                  In all cases where this API does expect a non-null pointer argument, a validation of the passed
 *                  argument is performed.
 *  \param[in]      configPtr    Pointer to a concrete configuration root - not used for now
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            Global interrupts shall be disabled.
 *  \trace          CREQ-113863
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_Init(
  Dcm_ConfigPtrType configPtr
  );

/**********************************************************************************************************************
 *  Dcm_InitMemory()
 *********************************************************************************************************************/
/*! \brief          Initialization function.
 *  \details        Module's memory initialization.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            Global interrupts shall be disabled. If used, then always prior calling Dcm_Init.
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_InitMemory(
  void
  );

# if (DCM_SPLIT_TASKS_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_MainFunctionTimer()
 *********************************************************************************************************************/
/*! \brief          Modules main timing scheduling.
 *  \details        This service is used for time critical tasks (high priority task).
 *                  Function will be called at high level task only for better timing accuracy.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_SPLIT_TASKS_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_MainFunctionTimer(
  void
  );
# endif

# if (DCM_SPLIT_TASKS_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_MainFunctionWorker()
 *********************************************************************************************************************/
/*! \brief          Modules main processing task.
 *  \details        This service is used for diagnostic service processing (low priority task).
 *                  Function will be called at low level task only, to allow long service execution times.
 *                  Note: All application call outs the DCM executes are performed only from within this task.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_SPLIT_TASKS_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_MainFunctionWorker(
  void
  );
# endif

# if (DCM_SPLIT_TASKS_ENABLED == STD_OFF)
/**********************************************************************************************************************
 *  Dcm_MainFunction()
 *********************************************************************************************************************/
/*! \brief          Modules main run-time scheduling.
 *  \details        This service is used for processing the tasks of the main loop.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_SPLIT_TASKS_ENABLED = STD_OFF.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_MainFunction(
  void
  );
# endif
/* --- Diagnostic service processing management -------------------------------------------------------------------- */
/**********************************************************************************************************************
 *  Dcm_ExternalProcessingDone()
 *********************************************************************************************************************/
/*! \brief          Finalizes the service processing task.
 *  \details        -
 *  \param[in,out]  pMsgContext  Current request context
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExternalProcessingDone(
  Dcm_MsgContextPtrType pMsgContext
  );

/**********************************************************************************************************************
 *  Dcm_ExternalSetNegResponse()
 *********************************************************************************************************************/
/*! \brief          Registers a NRC to the request in progress.
 *  \details        Only the very first registered NRC will be stored. Any further call of this API within the same
 *                  diagnostic request will have no effect.
 *  \param[in,out]  pMsgContext  Current request context
 *  \param[in]      errorCode    The error code to be registered
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExternalSetNegResponse(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode
  );

# if (DCM_DIAG_STATE_RECOVERY_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ProvideRecoveryStates()
 *********************************************************************************************************************/
/*! \brief          Returns the internal Dcm state.
 *  \details        This function can be used to gather the internal DCM states to be able to recover them after reset.
 *                  It shall be called by DCM application just before performing the reset operation.
 *  \param[out]     RecoveryInfo    Parameter to be written by the DCM with all the information to be recovered.
 *  \return         DCM_E_OK        Result is valid and shall be processed
 *  \return         DCM_E_NOT_OK    Some error has occurred e.g. DCM is not yet initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_DIAG_STATE_RECOVERY_ENABLED = STD_ON
 *  \pre            Once this API is called, the states may change due to external events (e.g. session timeout).
 *                  Therefore always perform this call right before executing the reset.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_ProvideRecoveryStates(
  P2VAR(Dcm_RecoveryInfoType, AUTOMATIC, DCM_APPL_DATA) RecoveryInfo
  );
# endif

# if (DCM_DIAG_SPECIFIC_CAUSE_CODE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_SetSpecificCauseCode()
 *********************************************************************************************************************/
/*! \brief          Registers a specific cause code to the request in progress.
 *  \details        Only the very first registered specific cause code will be stored. Any further call of this API
 *                  within the same diagnostic request will have no effect.
 *  \param[in]      specificCauseCode    The specific cause code to be registered
 *  \return         DCM_E_OK             Operation succeded. In case of first call, specific cause code is registered.
 *  \return         DCM_E_NOT_OK         Some error has occurred e.g. DCM is not yet initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_DIAG_SPECIFIC_CAUSE_CODE_ENABLED = STD_ON
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetSpecificCauseCode(
  Dcm_SpecificCauseCodeType specificCauseCode
  );
# endif
# if (DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_VsgSetSingle()
 *********************************************************************************************************************/
/*! \brief          Sets the status of a single VSG.
 *  \details        -
 *  \param[in]      VsgId         Unique handle of the VSG.
 *  \param[in]      State         DCM_VSG_ENABLED:  Set VSG to active
 *                                DCM_VSG_DISABLED: Set VSG to inactive
 *  \return         DCM_E_OK      New status is set succesfully
 *  \return         DCM_E_NOT_OK  Operation failed
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED = STD_ON.
*********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_VsgSetSingle(
  Dcm_VsgIdentifierType VsgId,
  Dcm_VsgStateType State
  );
# endif

# if (DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_VsgIsActive()
 *********************************************************************************************************************/
/*! \brief          Returns status of a single VSG.
 *  \details        -
 *  \param[in]      VsgId         Unique handle of the VSG.
 *  \param[out]     State         DCM_VSG_ENABLED:  VSG is active
 *                                DCM_VSG_DISABLED: VSG is inactive
 *  \return         DCM_E_OK      Operation succeeded, parameter isActive contains status of VSG
 *  \return         DCM_E_NOT_OK  Operation failed
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED = STD_ON.
*********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_VsgIsActive(
  Dcm_VsgIdentifierType VsgId,
  P2VAR(Dcm_VsgStateType, AUTOMATIC, DCM_APPL_DATA) State
  );
# endif

# if (DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_VsgSetMultiple()
 *********************************************************************************************************************/
/*! \brief          Sets the status of a set of VSGs.
 *  \details        -
 *  \param[in]      VsgIdList     List of VsgIds to be set
 *  \param[in]      VsgListSize   Number of VSGs
 *  \param[in]      State         DCM_VSG_ENABLED:  Set VSGs to active
 *                                DCM_VSG_DISABLED: Set VSGs to inactive
 *  \return         DCM_E_OK      New status is set succesfully
 *  \return         DCM_E_NOT_OK  Operation failed
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED = STD_ON.
*********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_VsgSetMultiple(
  P2CONST(Dcm_VsgIdentifierType, AUTOMATIC, DCM_APPL_DATA) VsgIdList,
  uint16 VsgListSize,
  Dcm_VsgStateType State
  );
# endif

# if (DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_VsgIsActiveAnyOf()
 *********************************************************************************************************************/
/*! \brief          Checks if at least one of the passed VSGs is active.
 *  \details        -
 *  \param[in]      VsgIdList     List of VsgIds to be set
 *  \param[in]      VsgListSize   Number of VSGs
 *  \param[out]     State         DCM_VSG_ENABLED:  At least one VSG is active
 *                                DCM_VSG_DISABLED: All VSGs are inactive
 *  \return         DCM_E_OK      Operation is executed successfully
 *  \return         DCM_E_NOT_OK  Operation failed
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED = STD_ON.
*********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_VsgIsActiveAnyOf(
  P2CONST(Dcm_VsgIdentifierType, AUTOMATIC, DCM_APPL_DATA) VsgIdList,
  uint16 VsgListSize,
  P2VAR(Dcm_VsgStateType, AUTOMATIC, DCM_APPL_DATA) State
  );
# endif
# define DCM_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   Call-back function declarations
---------------------------------------------- */
# define DCM_START_SEC_CALLOUT_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
# if (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_MEMMGR_MEMOP_WRITE_ENABLED == STD_ON)
#   if (DCM_DCM_AR_VERSION >= DCM_DCM_AR_VERSION_422)
/**********************************************************************************************************************
  Dcm_WriteMemory()
 *********************************************************************************************************************/
/*! \brief          Call-out to write to memory.
 *  \details        The Dcm_WriteMemory call-out is used to write memory data identified by the parameter memoryAddress
 *                  and memorySize.
 *                  This service is needed for the implementation of UDS services:
 *                      - WriteMemoryByAdress
 *                      - RequestDownload
 *  \param[in]      OpStatus                Operation status
 *  \param[in]      MemoryIdentifier        Identifier of the Memory Block
 *  \param[in]      MemoryAddress           Starting address of server memory from which data is to be written.
 *  \param[in]      MemorySize              Number of bytes in the MemoryData
 *  \param[in]      MemoryData              Data to be written (points to the diagnostic buffer in DCM).
 *  \param[out]     ErrorCode               If the operation Dcm_WriteMemory returns value
 *                                          DCM_WRITE_FAILED, the Dcm module shall
 *                                          send a negative response with NRC code equal to
 *                                          the parameter ErrorCode parameter value
 *  \return         DCM_WRITE_OK            Write was successful
 *  \return         DCM_WRITE_FAILED        Write was not successful
 *  \return         DCM_WRITE_PENDING       Write is not yet finished
 *  \return         DCM_WRITE_FORCE_RCRRP   Enforce RCR-RP transmission (vendor extension)
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_MEMMGR_MEMOP_WRITE_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_WriteMemory(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  Dcm_MsgType MemoryData,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
#   else
/**********************************************************************************************************************
  Dcm_WriteMemory()
 *********************************************************************************************************************/
/*! \brief          Call-out to write to memory.
 *  \details        The Dcm_WriteMemory call-out is used to write memory data identified by the parameter memoryAddress
 *                  and memorySize.
 *                  This service is needed for the implementation of UDS services:
 *                      - WriteMemoryByAdress
 *                      - RequestDownload
 *  \param[in]      OpStatus                Operation status
 *  \param[in]      MemoryIdentifier        Identifier of the Memory Block
 *  \param[in]      MemoryAddress           Starting address of server memory from which data is to be written.
 *  \param[in]      MemorySize              Number of bytes in the MemoryData
 *  \param[in]      MemoryData              Data to be written (points to the diagnostic buffer in DCM).
 *  \return         DCM_WRITE_OK            Write was successful
 *  \return         DCM_WRITE_FAILED        Write was not successful
 *  \return         DCM_WRITE_PENDING       Write is not yet finished
 *  \return         DCM_WRITE_FORCE_RCRRP   Enforce RCR-RP transmission (vendor extension)
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_MEMMGR_MEMOP_WRITE_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_WriteMemory(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  Dcm_MsgType MemoryData
  );
#   endif
#  endif

#  if (DCM_MEMMGR_MEMOP_READ_ENABLED == STD_ON)
#   if (DCM_DCM_AR_VERSION >= DCM_DCM_AR_VERSION_422)
/**********************************************************************************************************************
 *  Dcm_ReadMemory()
 *********************************************************************************************************************/
/*! \brief          Call-out to read from memory.
 *  \details        The Dcm_ReadMemory call-out is used to request memory data identified by the parameter
 *                  memoryAddress and memorySize from the UDS request message. This service is needed for the
 *                  implementation of UDS services:
 *                      - ReadMemoryByAdress
 *                      - RequestUpload
 *                      - ReadDataByIdentifier (in case of Dynamical DID defined by memory address)
 *  \param[in]      OpStatus                Operation status
 *  \param[in]      MemoryIdentifier        Identifier of the Memory Block
 *  \param[in]      MemoryAddress           Starting address of server memory from which data is to be retrieved
 *  \param[in]      MemorySize              Number of bytes in the MemoryData
 *  \param[out]     MemoryData              Data read (points to the diagnostic buffer in DCM)
 *  \param[out]     ErrorCode               If the operation Dcm_ReadMemory returns value
 *                                          DCM_READ_FAILED, the Dcm module shall send
 *                                          a negative response with NRC code equal to the
 *                                          parameter ErrorCode parameter value
 *  \return         DCM_READ_OK             Read was successful
 *  \return         DCM_READ_FAILED         Read was not successful
 *  \return         DCM_READ_PENDING        Read is not yet finished
 *  \return         DCM_READ_FORCE_RCRRP    Enforce RCR-RP transmission (vendor extension)
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_MEMMGR_MEMOP_READ_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_ReturnReadMemoryType, DCM_CALLOUT_CODE) Dcm_ReadMemory(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  Dcm_MsgType MemoryData,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
#   else
/**********************************************************************************************************************
 *  Dcm_ReadMemory()
 *********************************************************************************************************************/
/*! \brief          Call-out to read from memory.
 *  \details        The Dcm_ReadMemory call-out is used to request memory data identified by the parameter
 *                  memoryAddress and memorySize from the UDS request message. This service is needed for the
 *                  implementation of UDS services:
 *                      - ReadMemoryByAdress
 *                      - RequestUpload
 *                      - ReadDataByIdentifier (in case of Dynamical DID defined by memory address)
 *  \param[in]      OpStatus                Operation status
 *  \param[in]      MemoryIdentifier        Identifier of the Memory Block
 *  \param[in]      MemoryAddress           Starting address of server memory from which data is to be retrieved
 *  \param[in]      MemorySize              Number of bytes in the MemoryData
 *  \param[out]     MemoryData              Data read (points to the diagnostic buffer in DCM)
 *  \return         DCM_READ_OK             Read was successful
 *  \return         DCM_READ_FAILED         Read was not successful
 *  \return         DCM_READ_PENDING        Read is not yet finished
 *  \return         DCM_READ_FORCE_RCRRP    Enforce RCR-RP transmission (vendor extension)
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_MEMMGR_MEMOP_READ_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_ReturnReadMemoryType, DCM_CALLOUT_CODE) Dcm_ReadMemory(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  Dcm_MsgType MemoryData
  );
#   endif
#  endif
# endif /* (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_DEBUG_ERROR_DETECT == STD_ON)                                                                                                              /* COV_DCM_DEV_DEBUG TX */
/**********************************************************************************************************************
 *  Dcm_DebugAssertReport()
 *********************************************************************************************************************/
/*! \brief          Will be called on any detected DCM internal error.
 *  \details        -
 *  \param[in]      apiId         The DCM function ID that has detected/caused the problem. These are the same
 *                                DCM_SID_xxx macros used for DET reporting.
 *  \param[in]      errorId       The detected error type. These are the same DCM_E_xxx macros used for DET reporting.
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            This callback is available only during troubleshooting DCM by enabling DCM_DEBUG_ERROR_DETECT.
 *********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) Dcm_DebugAssertReport(
  uint8 apiId,
  uint8 errorId
  );
# endif
/**********************************************************************************************************************
 *  Dcm_Confirmation()
 *********************************************************************************************************************/
/*! \brief          Confirms the diagnostic job finalization.
 *  \details        This function confirms the successful transmission or a transmission error of a diagnostic
 *                  service. The idContext and the dcmRxPduId are required to identify the message which was processed.
 *                  If there was no response for this request, this call out is invoked at service processing finish.
 *                  Note: This call out is invoked only then when a DCM internal or external
 *                        <Module>_<DiagnosticService> service handler has been executed.
 *  \param[in]      idContext     Current context identifier which can be used to retrieve the relation between
 *                                request and confirmation. Within the confirmation, the Dcm_MsgContext is no more
 *                                available, so the idContext can be used to represent this relation.
 *                                The idContext is also part of the Dcm_MsgContext
 *  \param[in]      dcmRxPduId    DcmRxPduId on which the request was received. The source of the request
 *                                can have consequences for message processing.
 *  \param[in]      status        Status indication about confirmation
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) Dcm_Confirmation(
  Dcm_IdContextType idContext,
  PduIdType dcmRxPduId,
  Dcm_ConfirmationStatusType status
  );

# if (DCM_DIAG_JUMPTOFBL_ENABLED   == STD_ON) || \
     (DCM_DIAG_JUMPFROMFBL_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_SetProgConditions()
 *********************************************************************************************************************/
/*! \brief          Sets the programming conditions.
 *  \details        The Dcm_SetProgConditions call-out allows the integrator to store relevant information prior
 *                  jumping to boot loader. The context parameters are defined in Dcm_ProgConditionsType.
 *  \param[in]      progConditions    Conditions on which the jump to boot loader has been requested.
 *  \return         E_OK              Conditions have correctly been set
 *  \return         E_NOT_OK          Conditions cannot be set
 *  \return         DCM_E_PENDING     Conditions set is in progress, a further call to this API is needed to end the
                                      setting
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if (DCM_DIAG_JUMPTOFBL_ENABLED = STD_ON) ||
 *                  (DCM_DIAG_JUMPFROMFBL_ENABLED = STD_ON).
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SetProgConditions(
  Dcm_ProgConditionsPtrType progConditions
  );
# endif

# if (DCM_DIAG_JUMPFROMFBL_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_GetProgConditions()
 *********************************************************************************************************************/
/*! \brief          Returns the programming conditions.
 *  \details        The Dcm_GetProgConditions call-out is called upon DCM initialization and allows determining if a
 *                  response (0x50 or 0x51) has to be sent depending on request within the boot-loader.
 *                  The context parameters are defined in Dcm_ProgConditionsType.
 *  \param[in]      progConditions    Conditions on which the jump from the boot-loader has been requested.
 *  \return         DCM_COLD_START    The ECU starts normally
 *  \return         DCM_WARM_START    The ECU starts from a boot-loader jump
 *                                    The function parameter values will be evaluated for further processing.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_DIAG_JUMPFROMFBL_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_EcuStartModeType, DCM_CALLOUT_CODE) Dcm_GetProgConditions(
  Dcm_ProgConditionsPtrType progConditions
  );
# endif

# if (DCM_DIAG_STATE_RECOVERY_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_GetRecoveryStates()
 *********************************************************************************************************************/
/*! \brief          Collects the external stored internal Dcm state.
 *  \details        The Dcm_GetRecoveryStates() call-out is called upon DCM initialization and allows to restore the
 *                  previously via Dcm_ProvideRecoveryStates() stored internal Dcm state.
 *  \param[out]     RecoveryInfo     Parameter to be written by the DCM with all the information to be recovered.
 *  \return         DCM_E_OK         Result is valid and shall be processed
 *  \return         DCM_E_PENDING    Result is pending (e.g. NvM not yet ready)
 *  \return         DCM_E_NOT_OK     No information to be recovered or result reading failed
 *                                   DCM shall continue with the default initialized states.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \config         This function is only available if DCM_DIAG_STATE_RECOVERY_ENABLED = STD_ON
 *  \pre            Once this API is called, DCM will lock any external connection until the result is processed.
 *                  This is required in order to be able to switch into a consistent state without any influence from
 *                  outside.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_GetRecoveryStates(
  P2VAR(Dcm_RecoveryInfoType, AUTOMATIC, DCM_VAR_NOINIT) RecoveryInfo
  );
# endif

# if (DCM_DIAG_SERVICE_DISPATCHER_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_HandleServiceExtern()
 *********************************************************************************************************************/
/*! \brief         Returns the service implementation type for dispatching.
 *  \details        This call-out is used during service request processing, if the service is configured to be
 *                  dispatchable.
 *                  Note: This call-out is only invoked, if a DCM service handler has been configured accordingly.
 *  \param[in]      SID                   The service identifier of the request
 *  \param[in]      RequestData           The request data (behind SID byte)
 *  \param[in]      DataSize              The request data length
 *  \param[in]      ReqType               The request type (0 - physical, 1- functional)
 *  \param[in]      SourceAddress         The tester source address
 *  \return         TRUE              The service processing is done by the application
 *  \return         FALSE             The service processing is done by DCM
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_DIAG_SERVICE_DISPATCHER_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(boolean, DCM_CALLOUT_CODE) Dcm_HandleServiceExtern(
  uint8 SID,
  Dcm_ReadOnlyMsgType RequestData,
  uint16 DataSize,
  uint8 ReqType,
  uint16 SourceAddress
  );
# endif
# define DCM_STOP_SEC_CALLOUT_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   Uninitialized RAM of unspecified size
---------------------------------------------- */
# define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
# if (DCM_AUTHMGR_SUPPORT_ENABLED == STD_ON)
/*! Authentication manager data that can be read from and written to NvM (if NvM is configured) */
extern VAR(Dcm_AuthMgrNvMDataType, DCM_VAR_NOINIT) Dcm_AuthMgrNvMData[DCM_CFGAUTHMGRNETCONNINFO_SIZE];
# endif /* (DCM_AUTHMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON)
/*! Service 0x2C Data that can be read from and written to NvM (if NvM is configured) */
extern VAR(Dcm_Svc2CDynDidNvMDataType, DCM_VAR_NOINIT) Dcm_Svc2CNvMData;
# endif /* (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON) */
# define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   SafeBSW
---------------------------------------------- */
/*!
 * \exclusivearea DCM_EXCLUSIVE_AREA_0
 *                Ensures consistency of the Dcm global state variables.
 *
 * \protects      Dcm_PbRamNetConnHdl2TObjMap,
 *                Dcm_PbRamNetTransportObject,
 *                Dcm_PbRamNetBufferContext,
 *                Dcm_PbRamNetComMContext,
 *                Dcm_PbRamNetPeriodicTxObject[].Timer,
 *                Dcm_PbRamNetPeriodicTxObject[].State,
 *                Dcm_ThreadContext[].Diag.QueuedSet,
 *                Dcm_ThreadContext[].PagedBuffer.ReadIndex,
 *                Dcm_ThreadContext[].PagedBuffer.WriteIndex,
 *                Dcm_ThreadContext[].PagedBuffer.RemainingLen,
 *                Dcm_ThreadContext[].Diag.TObjHdl,
 *                Dcm_ThreadContext[].Diag.MsgContext.msgAddInfo.suppressPosResponse,
 *                Dcm_SingletonContext.Network.NumActiveConnections,
 *                Dcm_SingletonContext.TaskMgr.TaskContext,
 *                Dcm_SingletonContext.TimerMgr.Timer,
 *                Dcm_SingletonContext.Network.ActiveDiagnostic,
 *                Dcm_SingletonContext.TaskMgr.CurrentTaskPrioStack,
 *                Dcm_SingletonContext.TaskMgr.TaskScheduler[].SchdIsActive,
 *                Dcm_SingletonContext.StateMgr.Preconditions.Session,
 *                Dcm_SingletonContext.Diag.Services.Svc27.DelayTime[],
 *                Dcm_SingletonContext.Diag.Services.Svc27.SetAttCntrEventMask,
 *                Dcm_SingletonContext.Diag.Services.Svc2A.Scheduler.Table[].Rate,
 *                Dcm_SingletonContext.Diag.Services.Svc2A.Scheduler.Table[].Timer,
 *                Dcm_SingletonContext.Diag.Services.Svc2A.Scheduler.NumActiveEntries
 *                Dcm_SingletonContext.Diag.Services.Svc29.CbkProcessingState
 *                Dcm_SingletonContext.AuthMgr.PendingData
 *                Dcm_SingletonContext.AuthMgr.DelayTime[]
 *                Dcm_SingletonContext.AuthMgr.TimerExpiredMask
 *
 * \usedin        Dcm_ComM_FullComModeEntered,
 *                Dcm_ComM_NoComModeEntered,
 *                Dcm_ComM_SilentComModeEntered,
 *                Dcm_DiagFblResDoProcessTxConfirmation,
 *                Dcm_DiagHandleSuppressBit,
 *                Dcm_DiagRxIndication,
 *                Dcm_DiagSetP2Timings,
 *                Dcm_DiagSwitchProcessingContext,
 *                Dcm_DiagTaskGarbageCollector,
 *                Dcm_DiagTxFinalization,
 *                Dcm_DiagWorkerDoCancelProcessing_CancelOpen,
 *                Dcm_DiagWorkerDoCancelProcessing_ReviveKilledTasks,
 *                Dcm_DiagWorkerDoRepeat,
 *                Dcm_GetRequestKind,
 *                Dcm_NetLockConnectionOrNull,
 *                Dcm_NetOnRequestDetection,
 *                Dcm_NetProvideRxBuffer,
 *                Dcm_NetRegisterActiveConnection,
 *                Dcm_NetRegisterComMActivity,
 *                Dcm_NetRxIndInternal,
 *                Dcm_NetSetComModeEntered,
 *                Dcm_NetStartOfReception,
 *                Dcm_NetTaskTaMonitor,
 *                Dcm_NetUnRegisterActiveConnection,
 *                Dcm_NetUnRegisterAllComMActivity,
 *                Dcm_NetUnRegisterComMActivity,
 *                Dcm_OnTimeoutPeriodicTx,
 *                Dcm_PagedBufferDefragmentPage,
 *                Dcm_PagedBufferTask,
 *                Dcm_PagedBufferUpdatePage,
 *                Dcm_Service10PostProcessor,
 *                Dcm_SetActiveDiagnostic,
 *                Dcm_SetSecurityLevel,
 *                Dcm_StateSetSession,
 *                Dcm_Svc10_WaitForResetAck,
 *                Dcm_Svc27TimerSet,
 *                Dcm_Svc27UtiSetAttemptCntr,
 *                Dcm_Svc2ASchdCommit,
 *                Dcm_TmrSetTimerByThread,
 *                Dcm_TmrStartTimerByThread,
 *                Dcm_TmrStopTimerByThread,
 *                Dcm_TmrResumeTimerByThread,
 *                Dcm_TmrTaskTimer,
 *                Dcm_TskClrEvent,
 *                Dcm_TskKillAllTasks,
 *                Dcm_TskRegisterActiveTask,
 *                Dcm_TskSetEvent,
 *                Dcm_TskUnRegisterActiveTask,
 *                Dcm_NetPTxObjTimerSet,
 *                Dcm_Svc10CheckAccess,
 *                Dcm_KeyMAsyncCertificateVerifyFinished,
 *                Dcm_CsmAsyncJobFinished,
 *                Dcm_Svc29CancelOperation,
 *                Dcm_SetDeauthenticatedRole,
 *                Dcm_AuthMgrSetDeauthenticatedRole
 *                Dcm_OnTimeoutAuthentication
 *                Dcm_AuthMgrDeauthenticateIdleConn
 *
 * \exclude       Dcm_NetStartOfReception, Dcm_NetCopyTxBuffer, Dcm_NetProvideRxData, Dcm_MainFunction, Dcm_MainFunctionTimer, Dcm_MainFunctionWorker
 * \length        MEDIUM Typically the exclusive area is short, but there are cases, where function calls are performed.
 * \endexclusivearea
 */
#endif /* !defined(DCM_CORE_H) */
/* ********************************************************************************************************************
 * END OF FILE: Dcm_Core.h
 * ******************************************************************************************************************** */
