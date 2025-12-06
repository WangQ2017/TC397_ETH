/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  McalLib_OsStub.h
 *        \brief  TODO
 *
 *      \details  TODO
 *
 *  \attention    Please note:
 *                The demo and example programs only show special aspects of the software. With regard to the fact
 *                that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
 *                expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  TODO                          virrro        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  YYYY-MM-DD  virrro TODO          TODO
 *********************************************************************************************************************/
#ifndef APPL_INCLUDEHW_MCALLIB_OSSTUB_H_
#define APPL_INCLUDEHW_MCALLIB_OSSTUB_H_

#include "Os.h"

#define MCAL_SFR_OS_WRITE32(Area, Address, Data)              Os_WritePeripheral32(OsPeripheralRegion_MCAL, (uint32*)Address, Data)
#define MCAL_LIB_WRITECPUENDINITPROTREG(Address, SetMask)     Os_ModifyPeripheral32(OsPeripheralRegion_MCAL, (uint32*)Address, 0xFFFFFFFF, SetMask)
#define MCAL_LIB_WRITECPUENDINITPROTREG(Address, SetMask)     Appl_UnlockEndinit()

#endif /* APPL_INCLUDEHW_MCALLIB_OSSTUB_H_ */
