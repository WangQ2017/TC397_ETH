/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**
 * \ingroup    Os_Hal
 * \addtogroup Os_Hal_Compiler
 * \brief      Compiler abstraction of the TASKING compiler
 *
 * \{
 *
 * \file       Os_Hal_Compiler_TaskingInt.h
 * \brief      This file contains the specific keyword definition for the TASKING compiler
 * \details
 * The definitions are based on the Tasking Compiler User Manuals
 * "TASKING VX-toolset for TriCore User Guide (MA 160-800 V4.2 May 22, 2013)"
 *
 *********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/


#ifndef OS_HAL_COMPILER_TASKINGINT_H
# define OS_HAL_COMPILER_TASKINGINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Std_Types.h"
# include "Os_CommonInt.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! \brief  Abstraction for compiler specific attributes, required by core */
# define OS_ALWAYS_INLINE            __attribute__((always_inline))
# define OS_NORETURN                 __attribute__((noreturn))
# define OS_FLATTEN                  __attribute__((flatten))
# define OS_PURE                     __attribute__((pure))
# define OS_LIKELY(x)                (x)
# define OS_UNLIKELY(x)              (x)

/*! \brief  Abstraction for HAL specific compiler attribute to prevent from inlining a function. */
# define OS_HAL_NOINLINE             __attribute__((noinline))

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/*! \brief      Declares a function with a compiler specific attribute.
 *  \details    The implementations prototype has to be created with OS_FUNC_ATTRIBUTE_DEFINITION.
 *  \param[in]  rettype       The return type of the function.
 *  \param[in]  memclass      The memory class of the function.
 *  \param[in]  attribute     The function attribute {OS_ALWAYS_INLINE; OS_PURE, ...}.
 *  \param[in]  functionName  The function name.
 *  \param[in]  arguments     The function arguments in brackets. E.g. (uint8 a, uint16 b) or (void).
 */
# define OS_FUNC_ATTRIBUTE_DECLARATION(rettype, memclass, attribute, functionName, arguments) \
         FUNC(rettype, memclass) functionName arguments attribute


/*! \brief      Provides a function prototype for function definitions with a compiler specific attribute.
 *  \details    The declaration has to be created with OS_FUNC_ATTRIBUTE_DECLARE.
 *  \param[in]  rettype       The return type of the function.
 *  \param[in]  memclass      The memory class of the function.
 *  \param[in]  attribute     The function attribute {OS_ALWAYS_INLINE; OS_PURE, ...}.
 *  \param[in]  functionName  The function name.
 *  \param[in]  arguments     The function arguments in brackets. E.g. (uint8 a, uint16 b) or (void).
 */
# define OS_FUNC_ATTRIBUTE_DEFINITION(rettype, memclass, attribute, functionName, arguments) \
         FUNC(rettype, memclass) functionName arguments attribute


/*! \brief      Compiler abstraction for preprocessor string concatenation.
 *  \details    The define is used, when a macro calls another macro with string concatenation.
 *  \param[in]  x       The called macro which needs sting concatenation.
 */
# define OS_HAL_EXPAND(x)  OS_HAL_EXPAND1(x)
# define OS_HAL_EXPAND1(x) #x


/*! \brief         Abstraction of disabling core local interrupt.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Disable()         __disable()


/*! \brief         Abstraction of enabling core local interrupt.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Enable()          __enable()


/*! \brief         Abstraction of reading core special function register.
 *  \param[in]     x       The address offset of CSFR that should be read. It must be a valid CSFR address.
 *  \return        The value of the CSFR.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Mfcr(x)           (uint32)__mfcr((sint32)(x))


/*! \brief         Abstraction of writing core special function register.
 *  \param[in]     x       The address offset of CSFR that should be written. It must be a valid CSFR address.
 *  \param[in]     y       The value that should be written.
 *  \context       Supervisor
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Mtcr(x, y)        __asm("mtcr  #"OS_HAL_EXPAND(x)", %0" ::"d"(y):)


/*! \brief         Abstraction of the ISYNC instruction.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Isync()           __isync()


/*! \brief         Abstraction of the DSYNC instruction.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Dsync()           __dsync()


/*! \brief         Abstraction of the SVLCX instruction.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Svlcx()           __svlcx()


/*! \brief         Abstraction of the RSLCX instruction.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Rslcx()           __rslcx()


/*! \brief         Abstraction of the CLZ instruction.
 *  \param[in]     x       The value, whose leading zero needs to be counted.
 *  \return        The number of leading zero.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Clz(x)            (uint32)__clz((sint32)(x))


/*! \brief         Abstraction of the CMPSWAP instruction.
 *  \param[in]     x       The address of the spinlock variable.
 *  \param[in]     y       The value that should be swapped.
 *  \param[in]     z.......The condition value. Only when *x == z, y is swapped
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_CmpSwap(x, y, z)   __cmpswapw((unsigned int *)x, y, z)


/*! \brief         Abstraction of the DEBUG instruction.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Debug()           __debug()


/*! \brief         Abstraction of the RFE instruction.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Rfe()             __asm("rfe")


/*! \brief         Abstraction of the NOP instruction.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Nop()             __asm("nop")


/*! \brief         Abstraction of the JI instruction to the A11 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_JumpToA11()       __asm("ji a11")


/*! \brief         Abstraction of setting the register a11.
 *  \param[in]     x       The variable which will be set to the a11 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Mta11(x)          __asm( "mov.a  a11, %0" ::"d"(x):"a11")


/*! \brief         Abstraction of setting the register a10.
 *  \param[in]     x       The variable which will be set to the a10 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Mta10(x)          __asm("mov.a  a10, %0" ::"d"(x):"a10")


/*! \brief         Abstraction of setting the register a8.
 *  \param[in]     x       The variable which will be set to the a8 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Mta8(x)           __asm("mov.a  a8, %0" ::"d"(x):"a8")


/*! \brief         Abstraction of setting the register a9.
 *  \param[in]     x       The variable which will be set to the a9 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Mta9(x)           __asm("mov.a  a9, %0" ::"d"(x):"a9")


/*! \brief         Abstraction of setting the register a0.
 *  \param[in]     x       The variable which will be set to the a0 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Mta0(x)           __asm("mov.a  a0, %0" ::"d"(x):"a0")


/*! \brief         Abstraction of setting the register a1.
 *  \param[in]     x       The variable which will be set to the a1 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Mta1(x)           __asm("mov.a  a1, %0" ::"d"(x):"a1")


/*! \brief         Abstraction of setting the register a2.
 *  \param[in]     x       The variable which will be set to the a2 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Mta2(x)           __asm("mov.a  a2, %0" ::"d"(x):"a2")


/*! \brief         Abstraction of setting the register a4.
 *  \param[in]     x       The variable which will be set to the a4 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Mta4(x)           __asm("mov.a  a4, %0" ::"d"(x):"a4")

# define Os_Hal_ExceptionSectionDeclaration(core) __asm ("  .SDECL  \".text.OS_EXCVEC_CORE"#core"_CODE\",code,PROTECT");
# define Os_Hal_InterruptSectionDeclaration(core) __asm ("  .SDECL  \".text.OS_INTVEC_CORE"#core"_CODE\",code,PROTECT");

/*! \brief         Abstraction of unhandled exception entry.
 *  \details       If a trap occurs, which is not configured, the default exception handler
 *                 Os_UnhandledExc is called with the trap class, the trap identification and instruction address
 *                 as parameters. The trap class is stored in the upper 16 bits and the trap
 *                 identification is stored in the lower 16 bits.
 *  \param[in]     core       On which core the exception entry is registered. It must be in range [0, 6].
 *  \param[in]     class      For which trap class the exception entry is registered. It must be in range [0, 7].
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 */

# define Os_Hal_UnhandledTrapEntry(core, class) \
  __asm ("  .SECT   \".text.OS_EXCVEC_CORE"#core"_CODE\""); \
  __asm ("  .ALIGN 32"); \
  __asm ("  .EXTERN Os_Hal_UnhandledExceptionHandler"); \
  __asm ("  .GLOBAL osTrap_" #class "_Core" #core); \
  __asm ("osTrap_" #class "_Core" #core ": svlcx");                   /* save lower context */ \
  __asm ("  movh d4, #" #class);                                      /* prepare parameters for C-Function; D4 = Exception class */ \
  __asm ("  or d4, d15");                                             /* prepare parameters for C-Function; D4 |= TIN (D15) */ \
  __asm ("  movh.a a14, #@his(Os_Hal_UnhandledExceptionHandler)");    /* load address of Os_Hal_UnhandledExceptionHandler */ \
  __asm ("  lea a14,[a14]@los(Os_Hal_UnhandledExceptionHandler)");    /* load address of Os_Hal_UnhandledExceptionHandler */ \
  __asm ("  ji a14 ");                                                /* jump to the handler */


/*! \brief         Abstraction of memory exception entry.
 *  \details       This is the entry for the memory access violation, which calls the core
 *                 function Os_MemFault to handle the exception.
 *  \param[in]     core       On which core the exception entry is registered. It must be in range [0, 6].
 *  \param[in]     class      For which trap class the exception entry is registered. It must be in range [0, 7].
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_MemoryTrapEntry(core, class) \
  __asm ("  .SECT   \".text.OS_EXCVEC_CORE"#core"_CODE\""); \
  __asm ("  .ALIGN 32"); \
  __asm ("  .EXTERN Os_Hal_MemFaultExceptionHandler"); \
  __asm ("  .GLOBAL osTrap_" #class "_Core" #core); \
  __asm ("osTrap_" #class "_Core" #core ": svlcx");                   /* save lower context */ \
  __asm ("  movh d4, #" #class);                                      /* prepare parameters for C-Function; D4 = Exception class */ \
  __asm ("  or d4, d15");                                             /* prepare parameters for C-Function; D4 |= TIN (D15) */ \
  __asm ("  movh.a a14, #@his(Os_Hal_MemFaultExceptionHandler)");     /* load address of Os_Hal_MemFaultExceptionHandler */ \
  __asm ("  lea a14,[a14]@los(Os_Hal_MemFaultExceptionHandler)");     /* load address of Os_Hal_MemFaultExceptionHandler */ \
  __asm ("  ji a14 ");                                                /* jump to the handler */


/*! \brief         Abstraction of system call exception entry.
 *  \details       This is the entry for system call, which is used for service functions.
 *                 The system call calls Os_Hal_SysCall to handle system call exceptions.
 *  \param[in]     core       On which core the entry is registered. It must be in range [0, 6].
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_SysCallTrapEntry(core) \
  __asm ("  .SECT   \".text.OS_EXCVEC_CORE"#core"_CODE\""); \
  __asm ("  .ALIGN 32"); \
  __asm ("  .EXTERN Os_Hal_SysCall"); \
  __asm ("  .GLOBAL osTrap_6_Core" #core); \
  __asm ("osTrap_6_Core" #core ": mov d4, d15"); \
  __asm ("  mfcr d5, #" OS_HAL_EXPAND(OS_HAL_PCXI_OFFSET)); \
  __asm ("  mov.aa a5, a11"); \
  __asm ("  call Os_Hal_SysCall"); \
  __asm ("  mtcr #" OS_HAL_EXPAND(OS_HAL_PCXI_OFFSET) ", d2"); \
  __asm ("  rfe");


/*! \brief         Abstraction of user defined exception entry.
 *  \details       This macro function is used for user configured exception.
 *                 It save a whole context and calls the user ISR.
 *  \param[in]     core       On which core the entry is registered.
 *  \param[in]     class      For which class the entry is registered.
 *  \param[in]     UserFunc   The user function, which is to be called.
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_UserTrapEntry(core, class, UserFunc) \
  __asm ("  .SECT   \".text.OS_EXCVEC_CORE"#core"_CODE\""); \
  __asm ("  .ALIGN 32"); \
  __asm ("  .EXTERN " #UserFunc); \
  __asm ("  .GLOBAL osTrap_" #class "_Core" #core); \
  __asm ("osTrap_" #class "_Core" #core ": svlcx"); \
  __asm ("  call " #UserFunc);\
  __asm ("  rslcx");\
  __asm ("  rfe");
  

/*! \brief         Abstraction of Cat2 interrupt entry.
 *  \details       This macro function is used for Cat2 interrupt entry. By entering this function, interrupts
 *                 are disabled globally. The core function Os_IsrRun is called to handle the Cat2 ISR with the
 *                 pointer to the interrupt configuration
 *                 data as parameter.
 *  \param[in]     core          On which core the entry is registered. It must be in range [0, 6].
 *  \param[in]     level         For which level the entry is registered. It must be in range [0, 255].
 *  \param[in]     systemlevel   The interrupt level, until which the interrupts are disabled.
 *  \param[in]     isrconfig     The pointer to the ISR configuration data, which should be handled.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Cat2InterruptEntry(core, level, systemlevel, isrconfig) \
  __asm ("  .SECT   \".text.OS_INTVEC_CORE"#core"_CODE\""); \
  __asm ("  .ALIGN 32"); \
  __asm ("  .EXTERN " #isrconfig); \
  __asm ("  .EXTERN Os_Hal_IsrRun"); \
  __asm ("  .GLOBAL osIsrLevel_" #level "_Core" #core); \
  __asm ("osIsrLevel_" #level "_Core" #core": svlcx"); \
  __asm ("  movh.a  a4, #@his("#isrconfig")"); \
  __asm ("  lea  a4, [a4]@los("#isrconfig")"); \
  __asm ("  call Os_Hal_IsrRun"); \
  __asm ("  rslcx"); \
  __asm ("  rfe");


/*! \brief         Abstraction of unhandled interrupt entry.
 *  \details       This macro function is used for interrupts, which are not configured by the user. The
 *                 default core function Os_UnhandledIrq is called with the current level as parameter.
 *  \param[in]     core          On which core the entry is registered. It must be in range [0, 6].
 *  \param[in]     level         For which level the entry is registered. It must be in range [0, 255].
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_UnhandledInterruptEntry(core, level) \
  __asm ("  .SECT   \".text.OS_INTVEC_CORE"#core"_CODE\""); \
  __asm ("  .ALIGN 32"); \
  __asm ("  .EXTERN Os_Hal_UnhandledIrq"); \
  __asm ("  .GLOBAL osIsrLevel_" #level "_Core" #core); \
  __asm ("osIsrLevel_" #level "_Core" #core": svlcx"); \
  __asm ("  mov d4, #" #level); \
  __asm ("  mfcr d5, #" OS_HAL_EXPAND(OS_HAL_PCXI_OFFSET)); \
  __asm ("  mov.aa a4, a11"); \
  __asm ("  call Os_Hal_UnhandledIrq"); \
  __asm ("  rslcx"); \
  __asm ("  rfe");\


/*! \brief         Abstraction of Cat0 interrupt entry.
 *  \details       This macro function is used for user configured Cat0 interrupt.
 *                 It save a whole context and calls the user ISR.
 *  \param[in]     core       On which core the entry is registered.
 *  \param[in]     level      For which level the entry is registered.
 *  \param[in]     func       The user function, which is to be called.
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Cat0InterruptEntry(core, level, function) \
  __asm ("  .SECT   \".text.OS_INTVEC_CORE"#core"_CODE\""); \
  __asm ("  .ALIGN 32"); \
  __asm ("  .EXTERN " #function); \
  __asm ("  .GLOBAL osIsrLevel_" #level "_Core" #core); \
  __asm ("osIsrLevel_" #level "_Core" #core": svlcx"); \
  __asm ("  call " #function);\
  __asm ("  rslcx");\
  __asm ("  rfe");\


/*! \brief         Abstraction of Cat1 interrupt entry.
 *  \details       This macro function is used for user configured Cat1 interrupt.
 *                 It save a whole context and calls the user ISR.
 *  \param[in]     core       On which core the entry is registered.
 *  \param[in]     level      For which level the entry is registered.
 *  \param[in]     func       The user function, which is to be called.
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_Cat1InterruptEntry(core, level, function) \
  __asm ("  .SECT   \".text.OS_INTVEC_CORE"#core"_CODE\""); \
  __asm ("  .ALIGN 32"); \
  __asm ("  .EXTERN " #function); \
  __asm ("  .GLOBAL osIsrLevel_" #level "_Core" #core); \
  __asm ("osIsrLevel_" #level "_Core" #core": svlcx"); \
  __asm ("  call " #function);\
  __asm ("  rslcx");\
  __asm ("  rfe");\


/*! \brief         Abstraction of function declaration to trigger system call.
 *  \details       This is the prototype of the function to trigger system call. In case of Tasking compiler, the
 *                 key word __syscallfunc() is used to tell the compiler that it should trigger the system call. An
 *                 implementation of such function is not required. Thus Os_Hal_DefineTrapFunction is defined as
 *                 empty.
 *  \param[in]     name       The function name.
 *  \param[in]     parameters The parameters
 *  \param[in]     id         The system call identifier (TIN in system call handler)
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */


 /*! \brief         Abstraction of function declaration to trigger system call.
  *  \param[in]     name       The function name.
  *  \param[in]     parameters The parameters
  *  \param[in]     id         The system call identifier (TIN in system call handler)
  *  \context       ANY
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *  \pre           -
  */
# define Os_Hal_DeclareTrapFunction(name, parameters, id)   \
         OS_FUNC_ATTRIBUTE_DECLARATION(void, OS_CODE, OS_HAL_NOINLINE, name, parameters)


 /*! \brief         Abstraction of function definition to trigger system call.
  *  \details       This is the implementation of the function to trigger system call. This function is defined as
  *                 a non-inline function, thus the parameters are already prepared previously. This function can just
  *                 simply call the intrinsic function (_syscall) provided by the compiler.
  *  \param[in]     name                  The function name.
  *  \param[in]     parametersAsArguments The parameters in form of the function arguments (with types)
  *  \param[in]     parameters            The pure name of the parameters
  *  \param[in]     id                    The system call identifier (TIN in system call handler)
  *  \context       ANY
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *  \pre           -
  */
# define Os_Hal_DefineTrapFunction(name, parametersAsArguments, parameters, id)   \
         OS_FUNC_ATTRIBUTE_DEFINITION(void, OS_CODE, OS_HAL_NOINLINE, name, parametersAsArguments) \
         { \
           (void)parameters; \
           __syscall(id); \
         }

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define OS_START_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! \brief         Abstraction of reading the register a10.
 *  \return        The value of a10 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfa10, (void));
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfa10, (void))
{
  uint32 ReturnValue;
  __asm( "mov.d  %0, a10" :"=d"(ReturnValue)::);
  return ReturnValue;
}


/*! \brief         Abstraction of reading the register a11.
 *  \return        The value of a11 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfa11, (void));
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfa11, (void))
{
  uint32 ReturnValue;
  __asm( "mov.d  %0, a11" :"=d"(ReturnValue)::);
  return ReturnValue;
}


/*! \brief         Abstraction of reading the register a8.
 *  \return        The value of a8 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfa8, (void));
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfa8, (void))
{
  uint32 ReturnValue;
  __asm( "mov.d  %0, a8" :"=d"(ReturnValue)::);
  return ReturnValue;
}

/*! \brief         Abstraction of reading the register a9.
 *  \return        The value of a9 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfa9, (void));
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfa9, (void))
{
  uint32 ReturnValue;
  __asm( "mov.d  %0, a9" :"=d"(ReturnValue)::);
  return ReturnValue;
}

/*! \brief         Abstraction of reading the register a0.
 *  \return        The value of a0 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfa0, (void));
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfa0, (void))
{
  uint32 ReturnValue;
  __asm( "mov.d  %0, a0" :"=d"(ReturnValue)::);
  return ReturnValue;
}

/*! \brief         Abstraction of reading the register a1.
 *  \return        The value of a1 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfa1, (void));
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfa1, (void))
{
  uint32 ReturnValue;
  __asm( "mov.d  %0, a1" :"=d"(ReturnValue)::);
  return ReturnValue;
}

/*! \brief         Abstraction of reading the register d15.
 *  \return        The value of d15 register.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfd15, (void));
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_Mfd15, (void))                   /* COV_OS_HAL_MFD15 */
{
  uint32 ReturnValue;
  __asm( "mov  %0, d15" :"=d"(ReturnValue)::);
  return ReturnValue;
}

# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* OS_HAL_COMPILER_TASKINGINT_H */

/*!
 * \}
 */
/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Compiler_TaskingInt.h
 *********************************************************************************************************************/
