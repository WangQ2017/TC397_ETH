/******************************************************************************
 * 文件名: DualPrint_Cdd.h
 * 描述: 双通道打印CDD模块
 ******************************************************************************/
#ifndef DUALPRINT_CDD_H
#define DUALPRINT_CDD_H

#include "Std_Types.h"

/******************************************************************************
 * 枚举定义
 ******************************************************************************/
typedef enum
{
    PRINT_CHANNEL_UART = 0x01u,
    PRINT_CHANNEL_ETH  = 0x02u,
    PRINT_CHANNEL_BOTH = 0x03u
} PrintChannelType;

typedef enum
{
    PRINT_STATUS_OK = 0u,
    PRINT_STATUS_BUFFER_FULL,
    PRINT_STATUS_INVALID_CHANNEL,
    PRINT_STATUS_NOT_INITIALIZED,
    PRINT_STATUS_DRIVER_ERROR
} PrintStatusType;

/******************************************************************************
 * 模块配置参数
 ******************************************************************************/
#define UART_PRINT_RING_BUFFER_SIZE     2048u
#define ETH_PRINT_RING_BUFFER_SIZE      2048u
#define PRINT_MAX_FORMAT_BUFFER         512u    /* 增加缓冲区大小以容纳时间戳 */
#define ETH_MAX_CHUNK_SIZE              1500u
#define UART_MAX_CHUNK_SIZE             512u

#define PRINT_AUTO_NEWLINE_ENABLE       STD_ON  /* 自动添加换行符 */
#define PRINT_TIMESTAMP_ENABLE          STD_OFF  /* 启用StbM时间戳 */
#define PRINT_TIMESTAMP_FORMAT          "[%04d-%02d-%02d %02d:%02d:%02d.%03d] "

/******************************************************************************
 * 外部接口函数声明
 ******************************************************************************/
void DualPrint_Init(void);
void DualPrint_MainFunction(void);

PrintStatusType DualPrint_Printf(PrintChannelType channel, const char *format, ...);      /* 打印格式化数据 */
PrintStatusType DualPrint_PrintString(PrintChannelType channel, const char *str);       /* 打印字符串 */
PrintStatusType DualPrint_PrintData(PrintChannelType channel, const uint8* data, uint32 length);  /* 打印十六进制数据 */

uint32 DualPrint_GetPendingDataLength(PrintChannelType channel);
void DualPrint_ClearBuffer(PrintChannelType channel);

#endif /* DUALPRINT_CDD_H */