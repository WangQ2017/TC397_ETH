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
 *            Module: Os
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_Link_Core2_Stacks.lsl
 *   Generation Time: 2025-09-02 11:14:44
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  STACK SECTIONS
 *********************************************************************************************************************/

#if defined ( OS_LINK_KERNEL_STACKS )
group OS_CORE2_STACKS_GROUP(ordered, contiguous, fill)
{

/* Stack: OsCore2_Error (1024 Byte) */
group OS_STACK_OSCORE2_ERROR_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select "[.]bss.OS_STACK_OSCORE2_ERROR_VAR_NOINIT";
}
"_OS_STACK_OSCORE2_ERROR_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE2_ERROR_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE2_ERROR_VAR_NOINIT_END" = "_lc_ge_OS_STACK_OSCORE2_ERROR_VAR_NOINIT_GROUP" - 1;
"_OS_STACK_OSCORE2_ERROR_VAR_NOINIT_LIMIT" = "_lc_ge_OS_STACK_OSCORE2_ERROR_VAR_NOINIT_GROUP";

/* Stack: OsCore2_Init (1024 Byte) */
group OS_STACK_OSCORE2_INIT_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select "[.]bss.OS_STACK_OSCORE2_INIT_VAR_NOINIT";
}
"_OS_STACK_OSCORE2_INIT_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE2_INIT_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE2_INIT_VAR_NOINIT_END" = "_lc_ge_OS_STACK_OSCORE2_INIT_VAR_NOINIT_GROUP" - 1;
"_OS_STACK_OSCORE2_INIT_VAR_NOINIT_LIMIT" = "_lc_ge_OS_STACK_OSCORE2_INIT_VAR_NOINIT_GROUP";

/* Stack: OsCore2_Isr_Core (1024 Byte) */
group OS_STACK_OSCORE2_ISR_CORE_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select "[.]bss.OS_STACK_OSCORE2_ISR_CORE_VAR_NOINIT";
}
"_OS_STACK_OSCORE2_ISR_CORE_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE2_ISR_CORE_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE2_ISR_CORE_VAR_NOINIT_END" = "_lc_ge_OS_STACK_OSCORE2_ISR_CORE_VAR_NOINIT_GROUP" - 1;
"_OS_STACK_OSCORE2_ISR_CORE_VAR_NOINIT_LIMIT" = "_lc_ge_OS_STACK_OSCORE2_ISR_CORE_VAR_NOINIT_GROUP";

/* Stack: OsCore2_Kernel (1024 Byte) */
group OS_STACK_OSCORE2_KERNEL_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select "[.]bss.OS_STACK_OSCORE2_KERNEL_VAR_NOINIT";
}
"_OS_STACK_OSCORE2_KERNEL_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE2_KERNEL_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE2_KERNEL_VAR_NOINIT_END" = "_lc_ge_OS_STACK_OSCORE2_KERNEL_VAR_NOINIT_GROUP" - 1;
"_OS_STACK_OSCORE2_KERNEL_VAR_NOINIT_LIMIT" = "_lc_ge_OS_STACK_OSCORE2_KERNEL_VAR_NOINIT_GROUP";

/* Stack: OsCore2_Shutdown (1024 Byte) */
group OS_STACK_OSCORE2_SHUTDOWN_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select "[.]bss.OS_STACK_OSCORE2_SHUTDOWN_VAR_NOINIT";
}
"_OS_STACK_OSCORE2_SHUTDOWN_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE2_SHUTDOWN_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE2_SHUTDOWN_VAR_NOINIT_END" = "_lc_ge_OS_STACK_OSCORE2_SHUTDOWN_VAR_NOINIT_GROUP" - 1;
"_OS_STACK_OSCORE2_SHUTDOWN_VAR_NOINIT_LIMIT" = "_lc_ge_OS_STACK_OSCORE2_SHUTDOWN_VAR_NOINIT_GROUP";

/* Stack: OsCore2_Startup (1024 Byte) */
group OS_STACK_OSCORE2_STARTUP_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select "[.]bss.OS_STACK_OSCORE2_STARTUP_VAR_NOINIT";
}
"_OS_STACK_OSCORE2_STARTUP_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE2_STARTUP_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE2_STARTUP_VAR_NOINIT_END" = "_lc_ge_OS_STACK_OSCORE2_STARTUP_VAR_NOINIT_GROUP" - 1;
"_OS_STACK_OSCORE2_STARTUP_VAR_NOINIT_LIMIT" = "_lc_ge_OS_STACK_OSCORE2_STARTUP_VAR_NOINIT_GROUP";

/* Stack: OsCore2_Task_Prio13 (1024 Byte) */
group OS_STACK_OSCORE2_TASK_PRIO13_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select "[.]bss.OS_STACK_OSCORE2_TASK_PRIO13_VAR_NOINIT";
}
"_OS_STACK_OSCORE2_TASK_PRIO13_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE2_TASK_PRIO13_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE2_TASK_PRIO13_VAR_NOINIT_END" = "_lc_ge_OS_STACK_OSCORE2_TASK_PRIO13_VAR_NOINIT_GROUP" - 1;
"_OS_STACK_OSCORE2_TASK_PRIO13_VAR_NOINIT_LIMIT" = "_lc_ge_OS_STACK_OSCORE2_TASK_PRIO13_VAR_NOINIT_GROUP";

/* Stack: OsCore2_Task_Prio33 (1024 Byte) */
group OS_STACK_OSCORE2_TASK_PRIO33_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select "[.]bss.OS_STACK_OSCORE2_TASK_PRIO33_VAR_NOINIT";
}
"_OS_STACK_OSCORE2_TASK_PRIO33_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE2_TASK_PRIO33_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE2_TASK_PRIO33_VAR_NOINIT_END" = "_lc_ge_OS_STACK_OSCORE2_TASK_PRIO33_VAR_NOINIT_GROUP" - 1;
"_OS_STACK_OSCORE2_TASK_PRIO33_VAR_NOINIT_LIMIT" = "_lc_ge_OS_STACK_OSCORE2_TASK_PRIO33_VAR_NOINIT_GROUP";

/* Stack: OsCore2_Task_Prio4294967295 (1024 Byte) */
group OS_STACK_OSCORE2_TASK_PRIO4294967295_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select "[.]bss.OS_STACK_OSCORE2_TASK_PRIO4294967295_VAR_NOINIT";
}
"_OS_STACK_OSCORE2_TASK_PRIO4294967295_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE2_TASK_PRIO4294967295_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE2_TASK_PRIO4294967295_VAR_NOINIT_END" = "_lc_ge_OS_STACK_OSCORE2_TASK_PRIO4294967295_VAR_NOINIT_GROUP" - 1;
"_OS_STACK_OSCORE2_TASK_PRIO4294967295_VAR_NOINIT_LIMIT" = "_lc_ge_OS_STACK_OSCORE2_TASK_PRIO4294967295_VAR_NOINIT_GROUP";

/* Stack: OsCore2_Task_Prio48 (1024 Byte) */
group OS_STACK_OSCORE2_TASK_PRIO48_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select "[.]bss.OS_STACK_OSCORE2_TASK_PRIO48_VAR_NOINIT";
}
"_OS_STACK_OSCORE2_TASK_PRIO48_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE2_TASK_PRIO48_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE2_TASK_PRIO48_VAR_NOINIT_END" = "_lc_ge_OS_STACK_OSCORE2_TASK_PRIO48_VAR_NOINIT_GROUP" - 1;
"_OS_STACK_OSCORE2_TASK_PRIO48_VAR_NOINIT_LIMIT" = "_lc_ge_OS_STACK_OSCORE2_TASK_PRIO48_VAR_NOINIT_GROUP";

/* Stack: OsCore2_Task_Prio49 (1024 Byte) */
group OS_STACK_OSCORE2_TASK_PRIO49_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select "[.]bss.OS_STACK_OSCORE2_TASK_PRIO49_VAR_NOINIT";
}
"_OS_STACK_OSCORE2_TASK_PRIO49_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE2_TASK_PRIO49_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE2_TASK_PRIO49_VAR_NOINIT_END" = "_lc_ge_OS_STACK_OSCORE2_TASK_PRIO49_VAR_NOINIT_GROUP" - 1;
"_OS_STACK_OSCORE2_TASK_PRIO49_VAR_NOINIT_LIMIT" = "_lc_ge_OS_STACK_OSCORE2_TASK_PRIO49_VAR_NOINIT_GROUP";

/* Stack: OsCore2_Task_Prio53 (1024 Byte) */
group OS_STACK_OSCORE2_TASK_PRIO53_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select "[.]bss.OS_STACK_OSCORE2_TASK_PRIO53_VAR_NOINIT";
}
"_OS_STACK_OSCORE2_TASK_PRIO53_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE2_TASK_PRIO53_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE2_TASK_PRIO53_VAR_NOINIT_END" = "_lc_ge_OS_STACK_OSCORE2_TASK_PRIO53_VAR_NOINIT_GROUP" - 1;
"_OS_STACK_OSCORE2_TASK_PRIO53_VAR_NOINIT_LIMIT" = "_lc_ge_OS_STACK_OSCORE2_TASK_PRIO53_VAR_NOINIT_GROUP";

} /* OS_CORE2_STACKS_GROUP */
"_OS_CORE2_STACKS_START" = "_lc_gb_OS_CORE2_STACKS_GROUP";
"_OS_CORE2_STACKS_END" = "_lc_ge_OS_CORE2_STACKS_GROUP" - 1;
"_OS_CORE2_STACKS_LIMIT" = "_lc_ge_OS_CORE2_STACKS_GROUP";
"_OS_CORE2_STACKS_END_ALIAS" = (("_lc_ge_OS_CORE2_STACKS_GROUP")&~0xF0000000)|0xD0000000;
"_OS_CORE2_STACKS_LIMIT_ALIAS" = (("_lc_ge_OS_CORE2_STACKS_GROUP")&~0xF0000000)|0xD0000000;

#endif

#ifdef OS_LINK_KERNEL_STACKS
# undef OS_LINK_KERNEL_STACKS
#endif


