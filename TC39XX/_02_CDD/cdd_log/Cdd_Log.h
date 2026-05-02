/******************************************************************************
 * 文件名: Cdd_Log.h
 * 描述: 双通道打印CDD模块 - 支持串口和网口输出
 ******************************************************************************/
#ifndef CDD_LOG_H
#define CDD_LOG_H

#include "DualPrint_Cdd.h"

#define CDD_LOG_ERROR(...)         DualPrint_Printf(PRINT_CHANNEL_BOTH, "ERROR: " __VA_ARGS__)
#define CDD_LOG_DEBUG(...)         DualPrint_Printf(PRINT_CHANNEL_BOTH, "DEBUG: " __VA_ARGS__)
#define CDD_LOG_DEBUG_INFO(...)    DualPrint_Printf(PRINT_CHANNEL_BOTH, __FILE__, __LINE__, __VA_ARGS__)

#endif /* CDD_LOG_H */