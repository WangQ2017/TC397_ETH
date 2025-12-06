/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**
 * \addtogroup Os_Trace
 *
 * \{
 *
 * \file
 * \brief       The tracing inline implementation.
 *
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os.h.
 **********************************************************************************************************************/

#ifndef OS_TRACE_H
# define OS_TRACE_H
                                                                                                                         /* PRQA S 0388 EOF */ /* MD_MSR_Dir1.1 */
/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_TraceInt.h"
# include "Os_Trace_Cfg.h"


/* Os kernel module dependencies */
# include "Os_Cfg.h"
# include "Os_Task.h"
# include "Os_Common.h"
# include "Os_Core.h"

/* Os hal dependencies */
# include "Os_Hal_Compiler.h"

# if(OS_CFG_ORTI == STD_ON)
#   include "Os_Orti.h"
# endif


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

#if (OS_IS_DEFINED_OS_VTH_SCHEDULE == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_SCHEDULE()
 **********************************************************************************************************************/
/*! \brief          Trace thread-switches, where thread stands for task or ISR
 *  \details        This hook routine allows external tools to trace all context switches from task to ISR and back as
 *                  well as between tasks and between ISRs. So external tools may visualize the information or measure
 *                  the execution time of tasks and ISRs.
 *                  Mind that measured execution time values may not reflect the worst case, which would be necessary
 *                  for schedulability analysis.
 *
 *                  Callers:
 *                    - Os_TraceThreadSwitch()
 *                    - Os_TraceThreadResetAndResume()
 *                    - Os_TraceThreadCleanupAndResume()
 *                    - Os_TraceThreadSuspendAndStart()
 *
 *  \param[in]      FromThreadId     The ID of the thread which has run until the switch
 *  \param[in]      FromThreadReason Represents the reason why the thread is no longer running:
 *                                   - \ref OS_VTHP_TASK_TERMINATION
 *                                   - \ref OS_VTHP_ISR_END
 *                                   - \ref OS_VTHP_TASK_WAITEVENT
 *                                   - \ref OS_VTHP_TASK_WAITSEMA
 *                                   - \ref OS_VTHP_THREAD_PREEMPT
 *  \param[in]      ToThreadId       The ID of the thread which will run from now on
 *  \param[in]      ToThreadReason   Represents the reason why the thread runs from now on:
 *                                   - \ref OS_VTHP_TASK_ACTIVATION
 *                                   - \ref OS_VTHP_ISR_START
 *                                   - \ref OS_VTHP_TASK_SETEVENT
 *                                   - \ref OS_VTHP_TASK_GOTSEMA
 *                                   - \ref OS_VTHP_THREAD_RESUME
 *                                   - \ref OS_VTHP_THREAD_CLEANUP
 *  \param[in]      CallerCoreId     The ID of the core where the thread switch occurs
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *
 **********************************************************************************************************************/
# define OS_VTH_SCHEDULE(FromThreadId,FromThreadReason,ToThreadId,ToThreadReason,CallerCoreId) \
   OS_IGNORE_UNREF_PARAM(FromThreadId)     ;            \
   OS_IGNORE_UNREF_PARAM(FromThreadReason) ;            \
   OS_IGNORE_UNREF_PARAM(ToThreadId)       ;            \
   OS_IGNORE_UNREF_PARAM(ToThreadReason)   ;            \
   OS_IGNORE_UNREF_PARAM(CallerCoreId)     ;
#endif

#if (OS_IS_DEFINED_OS_VTH_FORCED_TERMINATION == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_FORCED_TERMINATION()
 **********************************************************************************************************************/
/*! \brief          Trace the forcible termination of a thread (task or ISR)
 *  \details        This hook routine allows external tools to trace the forcible termination of tasks and ISRs.
 *                  Forcible termination may take place as a reaction on a detected protection error or as result of
 *                  a call to the API function TerminateApplication.
 *                  Mind that forcibly terminated threads change their internal state without further notice. However,
 *                  in some situations a return to the thread is necessary for OS internal cleanup. In this case the
 *                  OS_VTH_SCHEDULE macro is called with ToThreadReason OS_VTHP_THREAD_CLEANUP. That cleanup will
 *                  not return to the application code of the thread but only be operating system internal.
 *
 *                  Callers:
 *                    - Os_TraceIsrKill()
 *                    - Os_TraceTaskKill()
 *
 *  \param[in]      ThreadId      The ID of the thread which is forcibly terminated
 *  \param[in]      CallerCoreId  The ID of the core where the forcible termination occurs
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 **********************************************************************************************************************/
# define OS_VTH_FORCED_TERMINATION(ThreadId,CallerCoreId) \
   OS_IGNORE_UNREF_PARAM(ThreadId)    ;            \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif

#if (OS_IS_DEFINED_OS_VTH_ACTIVATION == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_ACTIVATION()
 **********************************************************************************************************************/
/*! \brief          Trace the activation of a task.
 *  \details        This hook is called on the caller core when that core has successfully performed the activation of
 *                  TaskId on the destination core. As this OS implementation always performs task activation on the
 *                  destination core, DestCoreId and CallerCoreId are always identical.
 *
 *                  Callers:
 *                    - Os_TraceTaskActivate()
 *
 *  \param[in]      TaskId       The ID of the task which is activated
 *  \param[in]      DestCoreId   The ID of the core where the task will be executed
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 **********************************************************************************************************************/
# define OS_VTH_ACTIVATION(TaskId, DestCoreId, CallerCoreId) \
   OS_IGNORE_UNREF_PARAM(TaskId)      ;                      \
   OS_IGNORE_UNREF_PARAM(DestCoreId)  ;                      \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif

#if (OS_IS_DEFINED_OS_VTH_ACTIVATION_LIMIT == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_ACTIVATION_LIMIT()
 **********************************************************************************************************************/
/*! \brief          Trace the activation of a task.
 *  \details        This hook is called on the caller core when that core has failed to perform the activation of
 *                  TaskId on the destination core because number of activations has reached the limit.
 *                  As this OS implementation always performs task activation on the destination core, DestCoreId
 *                  and CallerCoreId are always identical.
 *
 *                  Callers:
 *                    - Os_TraceTaskActivateLimit()
 *
 *  \param[in]      TaskId       The ID of the task which is activated
 *  \param[in]      DestCoreId   The ID of the core where the task will be executed
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 **********************************************************************************************************************/
# define OS_VTH_ACTIVATION_LIMIT(TaskId, DestCoreId, CallerCoreId) \
   OS_IGNORE_UNREF_PARAM(TaskId)      ;                            \
   OS_IGNORE_UNREF_PARAM(DestCoreId)  ;                            \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif

#if (OS_IS_DEFINED_OS_VTH_SETEVENT == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_SETEVENT()
 **********************************************************************************************************************/
/*! \brief          Trace the event setting on a task.
 *  \details        This hook is called on the CallerCore when that core has successfully performed the event
 *                  setting on the destination core. As this OS implementation always performs event setting on the
 *                  destination core, DestCoreId and CallerCoreId are always identical.
 *
 *                  Callers:
 *                    - Os_TraceTaskSetEvent()
 *
 *  \param[in]      TaskId       The ID of the task which receives this event
 *  \param[in]      EventMask    A bit mask with the events which have been set
 *  \param[in]      StateChanged
 *                   - !0: The task state has changed from WAITING to READY
 *                   -  0: The task state has not changed
 *  \param[in]      DestCoreId   The ID of the core where the task will be executed
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 **********************************************************************************************************************/
# define OS_VTH_SETEVENT(TaskId, EventMask, StateChanged, DestCoreId, CallerCoreId) \
   OS_IGNORE_UNREF_PARAM(TaskId)      ;                                             \
   OS_IGNORE_UNREF_PARAM(EventMask)   ;                                             \
   OS_IGNORE_UNREF_PARAM(StateChanged);                                             \
   OS_IGNORE_UNREF_PARAM(DestCoreId)  ;                                             \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif


#if (OS_IS_DEFINED_OS_VTH_WAITEVENT_NOWAIT == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_WAITEVENT_NOWAIT()
 **********************************************************************************************************************/
/*! \brief          Trace the event waiting on a task.
 *  \details        This hook is called on the CallerCore when that core has successfully performed the wait event
 *                  on the destination core but the event is already set.
 *                  As this OS implementation always performs wait for event on the destination core, DestCoreId
 *                  and CallerCoreId are always identical.
 *
 *                  Callers:
 *                    - Os_TraceTaskWaitEventNoWait()
 *
 *  \param[in]      TaskId       The ID of the task which receives this event
 *  \param[in]      EventMask    A bit mask of the events for which the task is waiting for
 *  \param[in]      DestCoreId   The ID of the core where the task will be executed
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *
 **********************************************************************************************************************/
# define OS_VTH_WAITEVENT_NOWAIT(TaskId, EventMask, DestCoreId, CallerCoreId) \
   OS_IGNORE_UNREF_PARAM(TaskId)      ;                                       \
   OS_IGNORE_UNREF_PARAM(EventMask)   ;                                       \
   OS_IGNORE_UNREF_PARAM(DestCoreId)  ;                                       \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif


#if (OS_IS_DEFINED_OS_VTH_GOT_RES == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_GOT_RES()
 **********************************************************************************************************************/
/*! \brief          Trace resource occupation (get)
 *  \details        The OS calls this hook on a successful call of the API function GetResource. The priority of the
 *                  calling task or ISR has been increased so that other tasks and ISRs on the same core may need to
 *                  wait until they can be executed.
 *
 *                  Callers:
 *                    - Os_TraceResourceTaken()
 *
 *  \param[in]      ResId        The ID of the resource which has been taken
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *
 **********************************************************************************************************************/
# define OS_VTH_GOT_RES(ResId, CallerCoreId)\
   OS_IGNORE_UNREF_PARAM(ResId)       ;     \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif


#if (OS_IS_DEFINED_OS_VTH_REL_RES == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_REL_RES()
 **********************************************************************************************************************/
/*! \brief          Trace resource occupation (release)
 *  \details        The OS calls this hook on a successful call of the API function ReleaseResource. The priority of
 *                  the calling task or ISR has been decreased so that other tasks and ISRs on the same core may become
 *                  running as a result.
 *
 *                  Callers:
 *                    - Os_TraceResourceReleased()
 *
 *  \param[in]      ResId        The ID of the resource which has been released
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *
 **********************************************************************************************************************/
# define OS_VTH_REL_RES(ResId, CallerCoreId)\
   OS_IGNORE_UNREF_PARAM(ResId)       ;     \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif


#if (OS_IS_DEFINED_OS_VTH_REQ_SPINLOCK == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_REQ_SPINLOCK()
 **********************************************************************************************************************/
/*! \brief          Trace attempts to get a spinlock
 *  \details        The OS calls this hook before it enters a busy waiting loop on a spinlock. Tasks or ISRs of lower
 *                  priority have to wait until this task or ISR has taken and released the spinlock.
 *
 *                  Callers:
 *                    - Os_TraceSpinlockRequested()
 *
 *  \param[in]      SpinlockId   The ID of the spinlock, the caller is waiting for
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *
 **********************************************************************************************************************/
# define OS_VTH_REQ_SPINLOCK(SpinlockId, CallerCoreId)\
   OS_IGNORE_UNREF_PARAM(SpinlockId)  ;               \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif


#if (OS_IS_DEFINED_OS_VTH_GOT_SPINLOCK == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_GOT_SPINLOCK()
 **********************************************************************************************************************/
/*! \brief          Trace spinlock occupations (get)
 *  \details        The OS calls this hook whenever a spinlock has successfully been taken. If the task or ISR was not
 *                  successful immediately (entered busy waiting state), this hook means that it leaves the busy waiting
 *                  state. From now on no other task or ISR may get the spinlock until the current task or ISR has
 *                  released it.
 *
 *                  Callers:
 *                    - Os_TraceSpinlockTaken()
 *
 *  \param[in]      SpinlockId   The ID of the spinlock which was taken
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *
 **********************************************************************************************************************/
# define OS_VTH_GOT_SPINLOCK(SpinlockId, CallerCoreId)\
   OS_IGNORE_UNREF_PARAM(SpinlockId)  ;               \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif


#if (OS_IS_DEFINED_OS_VTH_REL_SPINLOCK == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_REL_SPINLOCK()
 **********************************************************************************************************************/
/*! \brief          Trace spinlock occupations (release)
 *  \details        The OS calls this hook on a release of a spinlock. Other tasks and ISR may take the spinlock now.
 *                  Callers:
 *                    - Os_TraceSpinlockReleased()
 *
 *  \param[in]      SpinlockId   The ID of the spinlock which was released
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *
 **********************************************************************************************************************/
# define OS_VTH_REL_SPINLOCK(SpinlockId, CallerCoreId)\
   OS_IGNORE_UNREF_PARAM(SpinlockId)  ;               \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif


#if (OS_IS_DEFINED_OS_VTH_REQ_ISPINLOCK == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_REQ_ISPINLOCK()
 **********************************************************************************************************************/
/*! \brief          Trace attempts to get an internal spinlock
 *  \details        The OS calls this hook before it enters a busy waiting loop on a spinlock. Tasks or ISRs of lower
 *                  priority have to wait until this task or ISR has taken and released the spinlock.
 *
 *                  Callers:
 *                    - Os_TraceSpinlockRequested()
 *
 *  \param[in]      SpinlockId   The ID of the spinlock, the caller is waiting for
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *
 **********************************************************************************************************************/
# define OS_VTH_REQ_ISPINLOCK(SpinlockId, CallerCoreId)\
   OS_IGNORE_UNREF_PARAM(SpinlockId)  ;               \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif


#if (OS_IS_DEFINED_OS_VTH_GOT_ISPINLOCK == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_GOT_ISPINLOCK()
 **********************************************************************************************************************/
/*! \brief          Trace internal spinlock occupations (get)
 *  \details        The OS calls this hook whenever a spinlock has successfully been taken. If the task or ISR was not
 *                  successful immediately (entered busy waiting state), this hook means that it leaves the busy waiting
 *                  state. From now on no other task or ISR may get the spinlock until the current task or ISR has
 *                  released it.
 *
 *                  Callers:
 *                    - Os_TraceSpinlockTaken()
 *
 *  \param[in]      SpinlockId   The ID of the spinlock which was taken
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *
 **********************************************************************************************************************/
# define OS_VTH_GOT_ISPINLOCK(SpinlockId, CallerCoreId)\
   OS_IGNORE_UNREF_PARAM(SpinlockId)  ;               \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif


#if (OS_IS_DEFINED_OS_VTH_REL_ISPINLOCK == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_REL_ISPINLOCK()
 **********************************************************************************************************************/
/*! \brief          Trace internal spinlock occupations (release)
 *  \details        The OS calls this hook on a release of a spinlock. Other tasks and ISR may take the spinlock now.
 *                  Callers:
 *                    - Os_TraceSpinlockReleased()
 *
 *  \param[in]      SpinlockId   The ID of the spinlock which was released
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *
 **********************************************************************************************************************/
# define OS_VTH_REL_ISPINLOCK(SpinlockId, CallerCoreId)\
   OS_IGNORE_UNREF_PARAM(SpinlockId)  ;               \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif


#if (OS_IS_DEFINED_OS_VTH_DISABLEDINT == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_DISABLEDINT()
 **********************************************************************************************************************/
/*! \brief          Trace interrupt locks (disable)
 *  \details        The OS calls this hook if the application has called an API function to disable interrupts. The
 *                  parameter IntLockId describes whether category 1 interrupts may still occur.
 *
 *                  Mind that the two types of interrupt locking (as described by the IntLockId) are independent from
 *                  each other so that the hook may be called twice before the hook OS_VTH_ENABLEDINT is called,
 *                  dependent on the application.
 *
 *
 *                  Callers:
 *                    - Os_TraceInterruptsGlobalDisabled()
 *                    - Os_TraceInterruptsLevelDisabled()
 *
 *  \param[in]      IntLockId:
 *                    - \ref OS_VTHP_CAT2INTERRUPTS
 *                    - \ref OS_VTHP_ALLINTERRUPTS
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *
 **********************************************************************************************************************/
# define OS_VTH_DISABLEDINT(IntLockId, CallerCoreId)\
   OS_IGNORE_UNREF_PARAM(IntLockId)   ;             \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif


#if (OS_IS_DEFINED_OS_VTH_ENABLEDINT == STD_OFF)
/***********************************************************************************************************************
 *  OS_VTH_ENABLEDINT()
 **********************************************************************************************************************/
/*! \brief          Trace interrupt locks (enable)
 *  \details        The OS calls this hook if the application has called an API function to enable interrupts.
 *                  Mind that the two types of interrupt locking (as described by the IntLockId) are independent from
 *                  each other so that interrupts may still be disabled by means of the other locking type after this
 *                  hook has returned.
 *
 *                  Callers:
 *                    - Os_TraceInterruptsGlobalEnabled()
 *                    - Os_TraceInterruptsLevelEnabled()
 *
 *  \param[in]      IntLockId:
 *                    - \ref OS_VTHP_CAT2INTERRUPTS
 *                    - \ref OS_VTHP_ALLINTERRUPTS
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *
 **********************************************************************************************************************/
# define OS_VTH_ENABLEDINT(IntLockId, CallerCoreId)\
   OS_IGNORE_UNREF_PARAM(IntLockId)   ;            \
   OS_IGNORE_UNREF_PARAM(CallerCoreId);
#endif

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

# define OS_START_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  Os_TraceIsTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)(OS_CFG_OSTIMINGHOOKS == STD_ON);                                                            /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsScheduleTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsScheduleTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)(OS_IS_DEFINED_OS_VTH_SCHEDULE == STD_ON);                                                   /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsForcedTerminationTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsForcedTerminationTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)(OS_IS_DEFINED_OS_VTH_FORCED_TERMINATION == STD_ON);                                         /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsActivationTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsActivationTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)(OS_IS_DEFINED_OS_VTH_ACTIVATION == STD_ON);                                                 /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsActivationLimitTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsActivationLimitTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)(OS_IS_DEFINED_OS_VTH_ACTIVATION_LIMIT == STD_ON);                                           /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsSetEventTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsSetEventTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)(OS_IS_DEFINED_OS_VTH_SETEVENT == STD_ON);                                                   /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsWaitEventTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsWaitEventTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)(OS_IS_DEFINED_OS_VTH_WAITEVENT_NOWAIT == STD_ON);                                           /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsGotResourceTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsGotResourceTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)(OS_IS_DEFINED_OS_VTH_GOT_RES == STD_ON);                                                    /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsRelResourceTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsRelResourceTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)(OS_IS_DEFINED_OS_VTH_REL_RES == STD_ON);                                                    /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsReqSpinlockTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsReqSpinlockTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)((OS_IS_DEFINED_OS_VTH_REQ_SPINLOCK == STD_ON) ||                                            /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
                            (OS_IS_DEFINED_OS_VTH_REQ_ISPINLOCK == STD_ON));                                            /* PRQA S 2996 */ /* MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsGotSpinlockTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsGotSpinlockTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)((OS_IS_DEFINED_OS_VTH_GOT_SPINLOCK == STD_ON) ||                                            /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
                            (OS_IS_DEFINED_OS_VTH_GOT_ISPINLOCK == STD_ON));                                            /* PRQA S 2996 */ /* MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsRelSpinlockTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsRelSpinlockTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)((OS_IS_DEFINED_OS_VTH_REL_SPINLOCK == STD_ON) ||                                            /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
                            (OS_IS_DEFINED_OS_VTH_REL_ISPINLOCK == STD_ON));                                            /* PRQA S 2996 */ /* MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsDisabledIntTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsDisabledIntTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)(OS_IS_DEFINED_OS_VTH_DISABLEDINT == STD_ON);                                                /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsEnabledIntTimingHookEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE, Os_TraceIsEnabledIntTimingHookEnabled,
( void ))
{
  return (Os_StdReturnType)(OS_IS_DEFINED_OS_VTH_ENABLEDINT == STD_ON);                                                 /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsOrtiServiceTracingEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,
Os_TraceIsOrtiServiceTracingEnabled,
( void ))
{
  return (Os_StdReturnType)(OS_CFG_ORTI_ADDITIONAL == STD_ON);                                                          /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceIsOrtiTaskIsrTracingEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,
Os_TraceIsOrtiTaskIsrTracingEnabled,
( void ))
{
  return (Os_StdReturnType)(OS_CFG_ORTI == STD_ON);                                                                     /* PRQA S 4304, 2996 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule2.2_2996 */
}


/***********************************************************************************************************************
 *  Os_TraceThreadInit()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_TraceThreadInit,
(
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Thread
))
{
  /* - #10 Check if timing hooks are enabled. */
  if(Os_TraceIsTimingHookEnabled() != 0u)                                                                               /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    /* - #20 Set the initial next run reason for the respective thread type. */
    switch(Thread->Type)
    {
    case OS_TRACE_THREAD_TYPE_TASK:
      Thread->Dyn->NextRunReason = OS_TRACE_TASK_ACTIVATION;                                                            /* SBSW_OS_TRACE_GETDYN_001 */
      break;
    case OS_TRACE_THREAD_TYPE_ISR:
      Thread->Dyn->NextRunReason = OS_TRACE_ISR_START;                                                                  /* SBSW_OS_TRACE_GETDYN_001 */
      break;
    default:
      Thread->Dyn->NextRunReason = OS_TRACE_THREAD_MISC;                                                                /* SBSW_OS_TRACE_GETDYN_001 */
      break;
    }
  }
}


/***********************************************************************************************************************
 *  Os_TraceThreadInitAndStart()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_TraceThreadInitAndStart,
(
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Task
))
{
  /* - #10 Check if timing hook for scheduling is enabled. */
  if(Os_TraceIsScheduleTimingHookEnabled() != 0u)                                                                       /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;

    core = Os_CoreGetCurrentCore();
    coreAsr = Os_Core2AsrCore(core);                                                                                    /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Assert that passed parameter is valid. */
    Os_Assert((Os_StdReturnType)(Task->Type == OS_TRACE_THREAD_TYPE_TASK));                                             /* PRQA S 4304 */ /* MD_Os_C90BooleanCompatibility */

    /* - #30 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #40 Call the Vector timing hook (user code) for scheduling: OS_VTH_SCHEDULE(). */
    /* variable values are casted in order to assure that they cannot be written in the hook */
    OS_VTH_SCHEDULE((OS_TRACE_INVALID_THREAD),                                                                          /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */
                    (OS_VTHP_THREAD_PREEMPT),
                    (Task->Id),
                    (OS_VTHP_TASK_ACTIVATION),
                    ((CoreIdType) Os_CoreGetId(core)))

    /* - #50 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */

    /* No initialization of NextRunReason necessary as it is anyhow setup when the task is left and
     * not needed before it gets active for the next time. */
  }
}

/***********************************************************************************************************************
 *  Os_TraceThreadSwitch()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceThreadSwitch,
(
  TaskStateType CurrentTaskState,
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Current,
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Next
))
{
  /* - #10 Check if timing hook for scheduling is enabled. */
  if(Os_TraceIsScheduleTimingHookEnabled() != 0u)                                                                       /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;

    core = Os_CoreGetCurrentCore();
    coreAsr = Os_Core2AsrCore(core);                                                                                    /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Set current tasks next run reason in accordance to its task state */
    if(CurrentTaskState == WAITING)
    {
      Current->Dyn->NextRunReason = OS_TRACE_TASK_SETEVENT;                                                             /* SBSW_OS_TRACE_GETDYN_001 */
    }
    else if(CurrentTaskState == READY)
    {
      Current->Dyn->NextRunReason = OS_TRACE_THREAD_RESUME;                                                             /* SBSW_OS_TRACE_GETDYN_001 */
    }
    else
    {
      Os_ErrKernelPanic(); /* called with no other task state */
    }

    /* - #30 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #40 Call the Vector timing hook (user code) for scheduling: OS_VTH_SCHEDULE(). */
    /* variable values are casted in order to assure that they cannot be written in the hook */
    OS_VTH_SCHEDULE( (Current->Id),                                                                                     /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */
                     ((uint8)(Current->Dyn->NextRunReason)),
                     (Next->Id),
                     ((uint8)(Next->Dyn->NextRunReason)),
                     ((CoreIdType) Os_CoreGetId(core)) )

    /* - #50 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }
  /* - #60 Store the currently running task if Orti task tracing is enabled. */
  if (Os_TraceIsOrtiTaskIsrTracingEnabled() != 0u)                                                                      /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    core = Os_CoreGetCurrentCore();
    Os_CoreGetTrace(core)->CurrentTask = Next;                                                                          /* SBSW_OS_TRACE_COREGETTRACE_001 */ /* SBSW_OS_TRACE_COREGETTRACE_002 */
  }
}                                                                                                                       /* PRQA S 6050 */ /* MD_MSR_STCAL */


/***********************************************************************************************************************
 *  Os_TraceThreadResetAndResume()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceThreadResetAndResume,
(
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Current,
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Next
))
{
  /* - #10 Check if timing hook for scheduling is enabled. */
  if(Os_TraceIsScheduleTimingHookEnabled() != 0u)                                                                       /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;

    core = Os_CoreGetCurrentCore();
    coreAsr = Os_Core2AsrCore(core);                                                                                    /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Set current tasks next run reason */
    Current->Dyn->NextRunReason = OS_TRACE_TASK_ACTIVATION;                                                             /* SBSW_OS_TRACE_GETDYN_001 */

    /* - #30 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #40 Call the Vector timing hook (user code) for scheduling: OS_VTH_SCHEDULE(). */
    /* variable values are casted in order to assure that they cannot be written in the hook */
    OS_VTH_SCHEDULE( (Current->Id),                                                                                     /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */
                     ((uint8)(Current->Dyn->NextRunReason)),
                     (Next->Id),
                     ((uint8)(Next->Dyn->NextRunReason)),
                     ((CoreIdType) Os_CoreGetId(core)) )

    /* - #50 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }
  /* - #60 Store the currently running task if Orti task tracing is enabled. */
  if (Os_TraceIsOrtiTaskIsrTracingEnabled() != 0u)                                                                      /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    core = Os_CoreGetCurrentCore();
    Os_CoreGetTrace(core)->CurrentTask = Next;                                                                          /* SBSW_OS_TRACE_COREGETTRACE_001 */ /* SBSW_OS_TRACE_COREGETTRACE_002 */
  }
}                                                                                                                       /* PRQA S 6050 */ /* MD_MSR_STCAL */


/***********************************************************************************************************************
 *  Os_TraceThreadCleanupAndResume()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceThreadCleanupAndResume,
(
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Current,
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Next
))
{
  /* - #10 Check if timing hook for scheduling is enabled. */
  if(Os_TraceIsScheduleTimingHookEnabled() != 0u)                                                                       /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    /* #20 If the current thead is a task or ISR (no hook) */
    /*     As ErrorHook and ProtectionHook may kill applications/tasks, they may schedule to other task */
    if(OS_LIKELY(Current->Type != OS_TRACE_THREAD_TYPE_MISC))
    {

      P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
      P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;

      core = Os_CoreGetCurrentCore();
      coreAsr = Os_Core2AsrCore(core);                                                                                  /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

      /* - #30 Set current tasks next run reason */
      Current->Dyn->NextRunReason = OS_TRACE_ISR_START;                                                                 /* SBSW_OS_TRACE_GETDYN_001 */

      /* - #40 Enter critical user section. */
      Os_CoreCriticalUserSectionEnter(coreAsr);                                                                         /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

      /* - #50 Call the Vector timing hook (user code) for scheduling: OS_VTH_SCHEDULE(). */
      /* variable values are casted in order to assure that they cannot be written in the hook */
      OS_VTH_SCHEDULE( (Current->Id),                                                                                   /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */
                       ((uint8)(Current->Dyn->NextRunReason)),
                       (Next->Id),
                       ((uint8)(Next->Dyn->NextRunReason)),
                       ((CoreIdType) Os_CoreGetId(core)) )

      /* - #60 Leave critical user section. */
      Os_CoreCriticalUserSectionLeave(coreAsr);                                                                         /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
    }
  }

  /* - #70 Store the currently running ISR if Orti ISR tracing is enabled. */
  if (Os_TraceIsOrtiTaskIsrTracingEnabled() != 0u)                                                                      /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    P2VAR(Os_TraceCoreType, TYPEDEF, OS_VAR_NOINIT) trace;

    core = Os_CoreGetCurrentCore();
    trace = Os_CoreGetTrace(core);                                                                                      /* SBSW_OS_TRACE_COREGETTRACE_002 */

    if (Next->Type == OS_TRACE_THREAD_TYPE_ISR)                                                                         /* COV_OS_HALPLATFORMISRNESTINGSUPPORT_XF */
    {
      trace->CurrentIsr = Next;                                                                                         /* SBSW_OS_TRACE_COREGETTRACE_001 */
    }
    else
    {
      trace->CurrentIsr = NULL_PTR;                                                                                     /* SBSW_OS_TRACE_COREGETTRACE_001 */
      trace->CurrentTask = Next;                                                                                        /* SBSW_OS_TRACE_COREGETTRACE_001 */
    }
  }
}                                                                                                                       /* PRQA S 6050 */ /* MD_MSR_STCAL */


/***********************************************************************************************************************
 *  Os_TraceThreadSuspendAndStart()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceThreadSuspendAndStart,
(
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Current,
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Next
))
{
  /* - #10 Check if timing hook for scheduling is enabled. */
  if(Os_TraceIsScheduleTimingHookEnabled() != 0u)                                                                       /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;

    core = Os_CoreGetCurrentCore();
    coreAsr = Os_Core2AsrCore(core);                                                                                    /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Set current tasks next run reason */
    Current->Dyn->NextRunReason = OS_TRACE_THREAD_RESUME;                                                               /* SBSW_OS_TRACE_GETDYN_001 */

    /* - #30 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #40 Call the Vector timing hook (user code) for scheduling: OS_VTH_SCHEDULE(). */
    /* variable values are casted in order to assure that they cannot be written in the hook */
    OS_VTH_SCHEDULE( (Current->Id),                                                                                     /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */
                     ((uint8)(Current->Dyn->NextRunReason)),
                     (Next->Id),
                     ((uint8)(Next->Dyn->NextRunReason)),
                     ((CoreIdType) Os_CoreGetId(core)) )

    /* - #50 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }

  /* - #60 Store the currently running task if Orti task tracing is enabled. */
  if (Os_TraceIsOrtiTaskIsrTracingEnabled() != 0u)                                                                      /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    core = Os_CoreGetCurrentCore();
    Os_CoreGetTrace(core)->CurrentIsr = Next;                                                                           /* SBSW_OS_TRACE_COREGETTRACE_001 */ /* SBSW_OS_TRACE_COREGETTRACE_002 */
  }
}                                                                                                                       /* PRQA S 6050 */ /* MD_MSR_STCAL */


/***********************************************************************************************************************
 *  Os_TraceIsrKill()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceIsrKill,
(
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) KilledIsr
))
{
  /* - #10 Check if timing hook for forcible termination is enabled. */
  if(Os_TraceIsForcedTerminationTimingHookEnabled() != 0u)                                                              /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;
    coreAsr = Os_Core2AsrCore(Os_CoreGetCurrentCore());                                                                 /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Set Isrs next run reason */
    KilledIsr->Dyn->NextRunReason = OS_TRACE_THREAD_CLEANUP;                                                            /* SBSW_OS_TRACE_GETDYN_001 */

    /* - #30 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #40 Call the Vector timing hook for killing: OS_VTH_FORCED_TERMINATION(). */
    OS_VTH_FORCED_TERMINATION((KilledIsr->Id), (Os_CoreGetId(Os_CoreGetCurrentCore())))                                 /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */

    /* - #50 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }
}


/***********************************************************************************************************************
 *  Os_TraceTaskKill()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceTaskKill,
(
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) KilledTask,
  Os_StdReturnType IsTaskSuspended
))
{
  /* - #10 Check if timing hook for forcible termination is enabled. */
  if(Os_TraceIsForcedTerminationTimingHookEnabled() != 0u)                                                              /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    /* - #20 Set tasks next run reason (dependent on currently running thread) */
    if(KilledTask == Os_ThreadGetTrace(Os_CoreGetThread()))                                                             /* SBSW_OS_TRACE_THREADGETTRACE_001 */ /* COMP_WARN_OS_CW_005 */
    {
      KilledTask->Dyn->NextRunReason = OS_TRACE_THREAD_CLEANUP;                                                         /* SBSW_OS_TRACE_GETDYN_001 */
    }
    else
    {
      KilledTask->Dyn->NextRunReason = OS_TRACE_TASK_ACTIVATION;                                                        /* SBSW_OS_TRACE_GETDYN_001 */
    }

    /* - #30 Check if task is not suspended */
    if(IsTaskSuspended == 0u)
    {
      P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;
      coreAsr = Os_Core2AsrCore(Os_CoreGetCurrentCore());                                                               /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

      /* - #40 Enter critical user section. */
      Os_CoreCriticalUserSectionEnter(coreAsr);                                                                         /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

      /* - #50 Call the Vector timing hook for killing OS_VTH_FORCED_TERMINATION() */
      OS_VTH_FORCED_TERMINATION((KilledTask->Id), (Os_CoreGetId(Os_CoreGetCurrentCore())))                              /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */

      /* - #60 Leave critical user section. */
      Os_CoreCriticalUserSectionLeave(coreAsr);                                                                         /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
    }
  }
}                                                                                                                       /* PRQA S 6050 */ /* MD_MSR_STCAL */


/***********************************************************************************************************************
 *  Os_TraceTaskActivate()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceTaskActivate,
(
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Task
))
{
  /* - #10 Check if timing hook for task activation is enabled. */
  if(Os_TraceIsActivationTimingHookEnabled() != 0u)                                                                     /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;

    core = Os_CoreGetCurrentCore();
    coreAsr = Os_Core2AsrCore(core);                                                                                    /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #30 Call the vector timing hook for task activation: OS_VTH_ACTIVATION(). */
    /* variable values are casted in order to assure that they cannot be written in the hook */
    OS_VTH_ACTIVATION((Task->Id), ((CoreIdType) Os_CoreGetId(core)), ((CoreIdType) Os_CoreGetId(core)))                 /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */ /* SBSW_OS_TRACE_COREGETID_001 */

    /* - #40 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }
}

/***********************************************************************************************************************
 *  Os_TraceTaskActivateLimit()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceTaskActivateLimit,
(
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Task
))
{
  /* - #10 Check if timing hook for a failed task activation is enabled. */
  if(Os_TraceIsActivationLimitTimingHookEnabled() != 0u)                                                                /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;

    core = Os_CoreGetCurrentCore();
    coreAsr = Os_Core2AsrCore(core);                                                                                    /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #30 Call the vector timing hook for failed task activation: OS_VTH_ACTIVATION_LIMIT(). */
    /* variable values are casted in order to assure that they cannot be written in the hook */
    OS_VTH_ACTIVATION_LIMIT((Task->Id), ((CoreIdType) Os_CoreGetId(core)), ((CoreIdType) Os_CoreGetId(core)))           /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */ /* SBSW_OS_TRACE_COREGETID_001 */

    /* - #40 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }
}


/***********************************************************************************************************************
 *  Os_TraceTaskSetEvent()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceTaskSetEvent,
(
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Task,
  EventMaskType EventMask,
  boolean StateChanged
))
{
  /* - #10 Check if timing hook for event setting is enabled. */
  if(Os_TraceIsSetEventTimingHookEnabled() != 0u)                                                                       /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;

    core = Os_CoreGetCurrentCore();
    coreAsr = Os_Core2AsrCore(core);                                                                                    /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #30 Call the vector timing hook for event setting: OS_VTH_SETEVENT(). */
    /* variable values are casted in order to assure that they cannot be written in the hook */
    OS_VTH_SETEVENT((Task->Id),                                                                                         /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */ /* SBSW_OS_TRACE_COREGETID_001 */
                   ((EventMaskType) EventMask),
                   ((boolean) StateChanged),
                   ((CoreIdType) Os_CoreGetId(core)),
                   ((CoreIdType) Os_CoreGetId(core)) )

    /* - #40 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }
}


/***********************************************************************************************************************
 *  Os_TraceTaskWaitEventNoWait()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceTaskWaitEventNoWait,
(
  P2CONST(Os_TraceThreadConfigType, AUTOMATIC, OS_CONST) Task,
  EventMaskType EventMask
))
{
  /* - #10 Check if timing hook for event waiting is enabled. */
  if(Os_TraceIsWaitEventTimingHookEnabled() != 0u)                                                                      /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;

    core = Os_CoreGetCurrentCore();
    coreAsr = Os_Core2AsrCore(core);                                                                                    /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #30 Call the vector timing hook for task not waiting: OS_VTH_WAITEVENT_NOWAIT() */
    /* variable values are casted in order to assure that they cannot be written in the hook */
    OS_VTH_WAITEVENT_NOWAIT((Task->Id),                                                                                 /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */ /* SBSW_OS_TRACE_COREGETID_001 */
                           ((EventMaskType) EventMask),
                           ((CoreIdType) Os_CoreGetId(core)),
                           ((CoreIdType) Os_CoreGetId(core)) )

    /* - #40 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }
}


/***********************************************************************************************************************
 * Os_TraceResourceTaken()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceResourceTaken,
(
    ResourceType ResId
))
{
  /* - #10 Check if timing hook for resource allocation is enabled. */
  if(Os_TraceIsGotResourceTimingHookEnabled() != 0u)                                                                    /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;
    coreAsr = Os_Core2AsrCore(Os_CoreGetCurrentCore());                                                                 /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #30 Call the vector timing hook for resource occupation: OS_VTH_GOT_RES(). */
    OS_VTH_GOT_RES((ResId), (Os_CoreGetId(Os_CoreGetCurrentCore())))                                                    /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */

    /* - #40 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }
}

/***********************************************************************************************************************
 * Os_TraceResourceReleased()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceResourceReleased,
(
    ResourceType ResId
))
{
  /* - #10 Check if timing hook for releasing a resource is enabled. */
  if(Os_TraceIsRelResourceTimingHookEnabled() != 0u)                                                                    /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;
    coreAsr = Os_Core2AsrCore(Os_CoreGetCurrentCore());                                                                 /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #30 Call the vector timing hook for resource occupation: OS_VTH_REL_RES(). */
    OS_VTH_REL_RES((ResId), (Os_CoreGetId(Os_CoreGetCurrentCore())))                                                    /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */

    /* - #40 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }
}


/***********************************************************************************************************************
 * Os_TraceSpinlockRequested()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceSpinlockRequested,
(
    P2CONST(Os_TraceSpinlockConfigType, AUTOMATIC, OS_CONST) Spinlock
))
{
  /* - #10 Check if timing hook for requesting a spinlock is enabled. */
  if(Os_TraceIsReqSpinlockTimingHookEnabled() != 0u)                                                                    /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;
    Os_IntStateType interruptState;
    coreAsr = Os_Core2AsrCore(Os_CoreGetCurrentCore());                                                                 /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* No NULL_PTR expected by this function */
    Os_Assert((Os_StdReturnType)(Spinlock != NULL_PTR));                                                                /* PRQA S 4304 */ /* MD_Os_C90BooleanCompatibility */

    /* - #20 Suspend interrupts. */
    Os_IntSuspend(&interruptState);                                                                                     /* SBSW_OS_FC_POINTER2LOCAL */

    /* - #30 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    if (Spinlock->SpinlockId < Os_TraceGetNumberOfConfiguredSpinlocks())                                                /* COV_OS_HALPLATFORMTESTEDASMULTICORE */ /* COMP_WARN_OS_CW_005 */
    {
      /* - #40 For configured spinlocks call: OS_VTH_REQ_SPINLOCK(). */
      OS_VTH_REQ_SPINLOCK((Spinlock->SpinlockId), (Os_CoreGetId(Os_CoreGetCurrentCore())))                              /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */
    }
    else
    {
      /* - #50 For internal spinlocks call: OS_VTH_REQ_ISPINLOCK(). */
      OS_VTH_REQ_ISPINLOCK((Spinlock->SpinlockId), (Os_CoreGetId(Os_CoreGetCurrentCore())))                             /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */
    }

    /* - #60 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */

    /* - #70 Resume interrupts. */
    Os_IntResume(&interruptState);                                                                                      /* SBSW_OS_FC_POINTER2LOCAL */
  }
}                                                                                                                       /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 * Os_TraceSpinlockTaken
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceSpinlockTaken,
(
    P2CONST(Os_TraceSpinlockConfigType, AUTOMATIC, OS_CONST) Spinlock
))
{
  /* - #10 Check if timing hook for allocating a spinlock is enabled. */
  if(Os_TraceIsGotSpinlockTimingHookEnabled() != 0u)                                                                    /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;
    Os_IntStateType interruptState;
    coreAsr = Os_Core2AsrCore(Os_CoreGetCurrentCore());                                                                 /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* No NULL_PTR expected by this function */
    Os_Assert((Os_StdReturnType)(Spinlock != NULL_PTR));                                                                /* PRQA S 4304 */ /* MD_Os_C90BooleanCompatibility */

    /* - #20 Suspend interrupts. */
    Os_IntSuspend(&interruptState);                                                                                     /* SBSW_OS_FC_POINTER2LOCAL */

    /* - #30 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    if (Spinlock->SpinlockId < Os_TraceGetNumberOfConfiguredSpinlocks())                                                /* COV_OS_HALPLATFORMTESTEDASMULTICORE */ /* COMP_WARN_OS_CW_005 */
    {
      /* - #40 For configured spinlocks call: OS_VTH_GOT_SPINLOCK(). */
      OS_VTH_GOT_SPINLOCK((Spinlock->SpinlockId), (Os_CoreGetId(Os_CoreGetCurrentCore())))                              /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */
    }
    else
    {
      /* - #50 For internal   spinlocks call: OS_VTH_IGOT_SPINLOCK(). */
      OS_VTH_GOT_ISPINLOCK((Spinlock->SpinlockId), (Os_CoreGetId(Os_CoreGetCurrentCore())))                             /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */
    }

    /* - #60 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */

    /* - #70 Resume interrupts. */
    Os_IntResume(&interruptState);                                                                                      /* SBSW_OS_FC_POINTER2LOCAL */
  }
}                                                                                                                       /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 * Os_TraceSpinlockReleased
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceSpinlockReleased,
(
    P2CONST(Os_TraceSpinlockConfigType, AUTOMATIC, OS_CONST) Spinlock
))
{
  /* - #10 Check if timing hook for releasing a spinlock is enabled. */
  if(Os_TraceIsRelSpinlockTimingHookEnabled() != 0u)                                                                    /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;
    Os_IntStateType interruptState;
    coreAsr = Os_Core2AsrCore(Os_CoreGetCurrentCore());                                                                 /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* No NULL_PTR expected by this function */
    Os_Assert((Os_StdReturnType)(Spinlock != NULL_PTR));                                                                /* PRQA S 4304 */ /* MD_Os_C90BooleanCompatibility */

    /* #20 Suspend interrupts. */
    Os_IntSuspend(&interruptState);                                                                                     /* SBSW_OS_FC_POINTER2LOCAL */

    /* - #30 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    if (Spinlock->SpinlockId < Os_TraceGetNumberOfConfiguredSpinlocks())                                                /* COV_OS_HALPLATFORMTESTEDASMULTICORE */ /* COMP_WARN_OS_CW_005 */
    {
      /* #40 For configured spinlocks call: OS_VTH_REL_SPINLOCK(). */
      OS_VTH_REL_SPINLOCK((Spinlock->SpinlockId), (Os_CoreGetId(Os_CoreGetCurrentCore())))                              /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */
    }
    else
    {
      /* #50 For internal   spinlocks call: OS_VTH_REL_ISPINLOCK(). */
      OS_VTH_REL_ISPINLOCK((Spinlock->SpinlockId), (Os_CoreGetId(Os_CoreGetCurrentCore())))                             /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */
    }

    /* - #60 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */

    /* #70 Resume interrupts. */
    Os_IntResume(&interruptState);                                                                                      /* SBSW_OS_FC_POINTER2LOCAL */
  }
}                                                                                                                       /* PRQA S 6050 */ /* MD_MSR_STCAL */


/***********************************************************************************************************************
 * Os_TraceInterruptsGlobalDisabled
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceInterruptsGlobalDisabled,
(
    void
))
{
  /* - #10 Check if timings hooks are enabled. */
  if(Os_TraceIsDisabledIntTimingHookEnabled() != 0u)                                                                    /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;
    coreAsr = Os_Core2AsrCore(Os_CoreGetCurrentCore());                                                                 /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #30 Call the vector timing hook for interrupt locks: OS_VTH_DISABLEDINT(). */
    OS_VTH_DISABLEDINT((OS_VTHP_ALLINTERRUPTS), (Os_CoreGetId(Os_CoreGetCurrentCore())))                                /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */

    /* - #40 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }
}

/***********************************************************************************************************************
 * Os_TraceInterruptsLevelDisabled
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceInterruptsLevelDisabled,
(
    void
))
{
  /* - #10 Check if timing hook for interrupt disabling is enabled. */
  if(Os_TraceIsDisabledIntTimingHookEnabled() != 0u)                                                                    /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;
    coreAsr = Os_Core2AsrCore(Os_CoreGetCurrentCore());                                                                 /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #30 Call the vector timing hook for interrupt locks: OS_VTH_DISABLEDINT(). */
    OS_VTH_DISABLEDINT((OS_VTHP_CAT2INTERRUPTS), (Os_CoreGetId(Os_CoreGetCurrentCore())))                               /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */

    /* - #40 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }
}

/***********************************************************************************************************************
 * Os_TraceInterruptsGlobalEnabled
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceInterruptsGlobalEnabled,
(
    void
))
{
  /* - #10 Check if timing hook for interrupt enabling is enabled. */
  if(Os_TraceIsEnabledIntTimingHookEnabled() != 0u)                                                                     /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;
    coreAsr = Os_Core2AsrCore(Os_CoreGetCurrentCore());                                                                 /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #30 Call the vector timing hook for interrupt locks: OS_VTH_ENABLEDINT(). */
    OS_VTH_ENABLEDINT((OS_VTHP_ALLINTERRUPTS), (Os_CoreGetId(Os_CoreGetCurrentCore())))                                 /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */

    /* - #40 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }
}

/***********************************************************************************************************************
 * Os_TraceInterruptsLevelEnabled
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceInterruptsLevelEnabled,
(
    void
))
{
  /* #10 Check if timing hooks are enabled: */
  if(Os_TraceIsEnabledIntTimingHookEnabled() != 0u)                                                                     /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreAsrConfigType, AUTOMATIC, OS_CONST) coreAsr;
    coreAsr = Os_Core2AsrCore(Os_CoreGetCurrentCore());                                                                 /* SBSW_OS_TRACE_CORE2ASRCORE_001 */

    /* - #20 Enter critical user section. */
    Os_CoreCriticalUserSectionEnter(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONENTER_001 */

    /* - #30 Call the vector timing hook for interrupt locks: OS_VTH_ENABLEDINT(). */
    OS_VTH_ENABLEDINT((OS_VTHP_CAT2INTERRUPTS), (Os_CoreGetId(Os_CoreGetCurrentCore())))                                /* PRQA S 3112 */ /* MD_Os_Rule2.2_3112_Hook */ /* SBSW_OS_TRACE_COREGETID_001 */

    /* - #40 Leave critical user section. */
    Os_CoreCriticalUserSectionLeave(coreAsr);                                                                           /* SBSW_OS_TRACE_CORECRITICALUSERSECTIONLEAVE_001 */
  }
}

/***********************************************************************************************************************
 * Os_TraceOrtiApiEntry
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceOrtiApiEntry,
(
    OsOrtiApiIdType ServiceId
))
{
  /* - #10 Log the start of the currently running OS Api if Orti is enabled. */
  if (Os_TraceIsOrtiServiceTracingEnabled() != 0u)                                                                      /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    core = Os_CoreGetCurrentCore();
    Os_CoreGetTrace(core)->OrtiCurrentServiceId = ((uint8) ServiceId) + (uint8)1;                                       /* SBSW_OS_TRACE_COREGETTRACE_001 */ /* SBSW_OS_TRACE_COREGETTRACE_002 */
  }
}

/***********************************************************************************************************************
 * Os_TraceOrtiApiExit
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceOrtiApiExit,
(
    OsOrtiApiIdType ServiceId
))
{
  /* - #10 Log the end of the currently running OS Api if Orti is enabled. */
  if (Os_TraceIsOrtiServiceTracingEnabled() != 0u)                                                                      /* PRQA S 2992, 2996 */ /* MD_Os_Rule14.3_2992, MD_Os_Rule2.2_2996 */
  {
    P2CONST(Os_CoreConfigType, AUTOMATIC, OS_CONST) core;
    core = Os_CoreGetCurrentCore();
    Os_CoreGetTrace(core)->OrtiCurrentServiceId = ((uint8) ServiceId);                                                  /* SBSW_OS_TRACE_COREGETTRACE_001 */ /* SBSW_OS_TRACE_COREGETTRACE_002 */
  }
}


/***********************************************************************************************************************
 *  Os_TraceGetNumberOfConfiguredSpinlocks()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_TraceSpinlockIdType, OS_CODE, OS_ALWAYS_INLINE,                         /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_TraceGetNumberOfConfiguredSpinlocks, ( void ))                                                                       /* COV_OS_HALPLATFORMTESTEDASMULTICORE */
{
  return OS_TRACE_NUMBER_OF_CONFIGURED_SPINLOCKS;
}


# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* OS_TRACE_H */

/* module specific MISRA deviations:
 */


/*!
 * \}
 */
/***********************************************************************************************************************
 *  END OF FILE: Os_Trace.h
 **********************************************************************************************************************/
