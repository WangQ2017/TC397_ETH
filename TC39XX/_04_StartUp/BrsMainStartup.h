
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  BrsMainStartup.h
      Project:  Vector Basic Runtime System
       Module:  BrsMain

  \brief Description:  Vector Basic Runtime System module header for startup routines.

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

#ifndef _BRSMAINSTARTUP_H_
#define _BRSMAINSTARTUP_H_

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
/*
 * Description: The vBrsCfg header provides all the necessary configuration switches of the BRS.
 *              It is either a template file or generated out of Configurator 5.
 */
#include "vBrsCfg.h"

/**********************************************************************************************************************
  MODULE VERSION
**********************************************************************************************************************/
/*
 * Description: This is the BrsHw main and bug fix version. The version numbers are BCD coded. 
 *              E.g. a main version of 1.23 is coded with 0x0123, a bug fix version of 9 is coded 0x09.
 */
#define BRSMAINSTARTUP_VERSION        0x0201u
#define BRSMAINSTARTUP_BUGFIX_VERSION 0x02u

/**********************************************************************************************************************
  GLOBAL TYPE DEFINITIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
void Brs_PreMainStartup(void);

#endif /*_BRSMAINSTARTUP_H_*/
