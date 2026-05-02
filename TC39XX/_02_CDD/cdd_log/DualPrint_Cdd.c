/******************************************************************************
 * 文件名: DualPrint_Cdd.c
 * 描述: 双通道打印CDD模块实现
 ******************************************************************************/
#include "DualPrint_Cdd.h"
#include "Uart.h"
#include "Eth_30_Tc3xx.h"
#include "Os.h"
#include "string.h"
#include "stdarg.h"
#include "stdio.h"
#include "stdlib.h"
#if (PRINT_TIMESTAMP_ENABLE == STD_ON)
#include "StbM.h"
#endif

/* 全局中断控制宏 */
#define DUALPRINT_ENTER_CRITICAL_SECTION()      SuspendAllInterrupts()
#define DUALPRINT_EXIT_CRITICAL_SECTION()       ResumeAllInterrupts()

/******************************************************************************
 * 环形缓冲区数据结构
 ******************************************************************************/
typedef struct
{
    uint8*  buffer;          /* 缓冲区指针 */
    uint32  bufferSize;      /* 缓冲区大小 */
    uint32  writeIndex;      /* 写索引 */
    uint32  readIndex;       /* 读索引 */
    uint32  dataCount;       /* 待发送数据字节数 */
    uint32  maxChunkSize;    /* 单次最大发送长度 */
} RingBuffer_Type;

/******************************************************************************
 * 通道控制块
 ******************************************************************************/
typedef struct
{
    boolean         isInitialized;      /* 通道是否初始化 */
    RingBuffer_Type ringBuffer;         /* 环形缓冲区 */
    uint8           uartBuffer[UART_PRINT_RING_BUFFER_SIZE];
    uint8           ethBuffer[ETH_PRINT_RING_BUFFER_SIZE];
    
    /* 统计信息 */
    uint32          overflowCount;
    uint32          totalSentBytes;
} ChannelControl_Type;

static ChannelControl_Type UartChannel;
static ChannelControl_Type EthChannel;
static boolean DualPrint_Initialized = FALSE;

/******************************************************************************
 * 时间日期结构体
 ******************************************************************************/
typedef struct
{
    uint16 year;        /* 年份，如2024 */
    uint8  month;       /* 月份，1-12 */
    uint8  day;         /* 日期，1-31 */
    uint8  hour;        /* 小时，0-23 */
    uint8  minute;      /* 分钟，0-59 */
    uint8  second;      /* 秒，0-59 */
    uint16 millisecond; /* 毫秒，0-999 */
} DateTime_Type;

/******************************************************************************
 * 本地时间基准（本地基准时间戳）
 ******************************************************************************/
typedef struct
{
    uint64    systemTick;      /* 系统启动后的tick计数 */
    uint64    secCounter;      /* 秒计数器（从某个基准开始）*/
    uint16    msCounter;       /* 毫秒计数器（0-999）*/
    uint32    tickPerSecond;   /* 每秒tick数 */
    boolean   isInitialized;   /* 本地时间是否已初始化 */
} LocalTime_Type;

static LocalTime_Type LocalTime;
static uint64 SystemStartTick = 0u;
static boolean LocalTimeInitialized = FALSE;

/******************************************************************************
 * 本地时间初始化
 ******************************************************************************/
static void LocalTime_Init(void)
{
    LocalTime.systemTick = 0u;
    LocalTime.secCounter = 0u;
    LocalTime.msCounter = 0u;
    LocalTime.tickPerSecond = 1000u;  /* 假设1ms tick，实际根据系统时钟配置 */
    LocalTime.isInitialized = TRUE;
    
    /* 系统启动时的基准时间（可以从RTC读取，默认为2024-01-01 00:00:00）*/
    SystemStartTick = 0u;
}

/**
 * @brief   获取本地时间tick计数（微秒或毫秒级）
 * @return  当前系统tick值
 */
static uint64 LocalTime_GetTick(void)
{
    /* 注意：实际项目中需要根据硬件定时器实现
       以下为示例，使用递增计数器 */
    static uint64 mockTick = 0u;
    return mockTick++;
}

/**
 * @brief   更新本地时间
 * @note    在周期函数中调用，更新时间
 */
static void LocalTime_Update(void)
{
    uint64 currentTick;
    uint64 deltaTick;
    
    if(!LocalTime.isInitialized)
    {
        return;
    }
    
    currentTick = LocalTime_GetTick();
    
    if(LocalTime.systemTick == 0u)
    {
        LocalTime.systemTick = currentTick;
        return;
    }
    
    /* 计算tick差 */
    if(currentTick >= LocalTime.systemTick)
    {
        deltaTick = currentTick - LocalTime.systemTick;
    }
    else
    {
        /* 处理溢出（64位溢出概率极低）*/
        deltaTick = currentTick + (~LocalTime.systemTick + 1u);
    }
    
    /* 更新秒和毫秒 */
    if(deltaTick >= LocalTime.tickPerSecond)
    {
        uint64 deltaSec = deltaTick / LocalTime.tickPerSecond;
        uint32 remainingTick = (uint32)(deltaTick % LocalTime.tickPerSecond);
        
        LocalTime.secCounter += deltaSec;
        LocalTime.msCounter = (remainingTick * 1000u) / LocalTime.tickPerSecond;
        
        if(LocalTime.msCounter >= 1000u)
        {
            LocalTime.msCounter = 0u;
            LocalTime.secCounter++;
        }
        
        LocalTime.systemTick = currentTick;
    }
    else
    {
        /* 不足1秒，只更新毫秒 */
        LocalTime.msCounter = (uint32)((deltaTick * 1000u) / LocalTime.tickPerSecond);
    }
}

/**
 * @brief   获取当前UTC时间（从本地时间计算）
 * @param   dateTime 输出参数，存储时间信息
 * @return  TRUE: 成功获取; FALSE: 获取失败
 */
static boolean LocalTime_GetUTC(DateTime_Type* dateTime)
{
    uint64 totalSeconds;
    uint32 daysFromEpoch;
    uint32 secondsInDay;
    uint32 year;
    uint32 month;
    uint32 day;
    uint32 hour;
    uint32 minute;
    uint32 second;
    
    if((dateTime == NULL) || (!LocalTime.isInitialized))
    {
        return FALSE;
    }
    
    /* 获取当前总秒数（从起始基准开始计算）*/
    totalSeconds = LocalTime.secCounter;
    
    /* 计算从起始基准到现在的天数（起始基准假设为2024-01-01 00:00:00）*/
    daysFromEpoch = (uint32)(totalSeconds / 86400u);
    secondsInDay = (uint32)(totalSeconds % 86400u);
    
    /* 计算小时、分钟、秒 */
    hour = secondsInDay / 3600u;
    minute = (secondsInDay % 3600u) / 60u;
    second = secondsInDay % 60u;
    
    /* 计算年月日（简化算法，从2024-01-01开始）*/
    /* 实际项目中应使用准确的日期算法或使用RTC硬件 */
    year = 2024u;
    month = 1u;
    day = 1u + daysFromEpoch;
    
    /* 简单处理，实际需要闰年等计算 */
    while(day > 365u)
    {
        day -= 365u;
        year++;
        
        /* 闰年检查（实际需要完善）*/
        if((year % 4u) == 0u)
        {
            day--;
        }
    }
    
    /* 填充输出结构 */
    dateTime->year = (uint16)year;
    dateTime->month = (uint8)month;
    dateTime->day = (uint8)day;
    dateTime->hour = (uint8)hour;
    dateTime->minute = (uint8)minute;
    dateTime->second = (uint8)second;
    dateTime->millisecond = LocalTime.msCounter;
    
    return TRUE;
}

/******************************************************************************
 * 时间戳获取函数
 ******************************************************************************/

/**
 * @brief   获取当前UTC时间戳字符串
 * @param   buffer      缓冲区指针
 * @param   bufferSize  缓冲区大小
 * @return  实际写入的字符数
 */
static uint32 DualPrint_GetTimestamp(char* buffer, uint32 bufferSize)
{
    DateTime_Type dateTime;
    boolean timeValid = FALSE;
    
    if(buffer == NULL || bufferSize == 0u)
    {
        return 0u;
    }
    
    /* 尝试使用StbM模块获取UTC时间 */
#if (PRINT_TIMESTAMP_ENABLE == STD_ON)
    StbM_TimeValueType stbmTime;
    Std_ReturnType ret;
    
    ret = StbM_GetCurrentTime(0u, &stbmTime);  /* 0表示StbM模块实例ID */
    if(ret == STBM_E_OK)
    {
        /* 从StbM获取UTC时间成功 */
        dateTime.year = (uint16)(stbmTime.year);
        dateTime.month = (uint8)(stbmTime.month);
        dateTime.day = (uint8)(stbmTime.day);
        dateTime.hour = (uint8)(stbmTime.hour);
        dateTime.minute = (uint8)(stbmTime.minute);
        dateTime.second = (uint8)(stbmTime.second);
        dateTime.millisecond = (uint16)(stbmTime.millisecond);
        timeValid = TRUE;
    }
#endif
    
    /* 如果StbM不可用或获取失败，使用本地时间计算UTC */
    if(!timeValid)
    {
        /* 更新本地时间 */
        LocalTime_Update();
        
        /* 获取本地计算的UTC时间 */
        if(LocalTime_GetUTC(&dateTime))
        {
            timeValid = TRUE;
        }
    }
    
    /* 格式化时间戳字符串 */
    if(timeValid)
    {
        return (uint32)sprintf(buffer, PRINT_TIMESTAMP_FORMAT,
                               dateTime.year, dateTime.month, dateTime.day,
                               dateTime.hour, dateTime.minute, dateTime.second,
                               dateTime.millisecond);
    }
    else
    {
        /* 无法获取时间，返回空字符串 */
        buffer[0] = '\0';
        return 0u;
    }
}

/******************************************************************************
 * 环形缓冲区实现
 ******************************************************************************/
static void RingBuffer_Init(RingBuffer_Type* ring, uint8* buffer, uint32 size, uint32 maxChunk)
{
    ring->buffer = buffer;
    ring->bufferSize = size;
    ring->writeIndex = 0u;
    ring->readIndex = 0u;
    ring->dataCount = 0u;
    ring->maxChunkSize = maxChunk;
    (void)memset(buffer, 0, size);
}

static boolean RingBuffer_Write(RingBuffer_Type* ring, const uint8* data, uint32 length)
{
    uint32 i;
    uint32 currentWriteIdx;
    uint32 currentDataCount;
    
    if((ring == NULL) || (data == NULL) || (length == 0u))
    {
        return FALSE;
    }
    
    /* 检查剩余空间 */
    if((ring->dataCount + length) > ring->bufferSize)
    {
        return FALSE;
    }
    
    /* 写入数据 */
    for(i = 0; i < length; i++)
    {
        currentWriteIdx = ring->writeIndex;
        ring->buffer[currentWriteIdx] = data[i];
        
        currentWriteIdx++;
        if(currentWriteIdx >= ring->bufferSize)
        {
            currentWriteIdx = 0u;
        }
        ring->writeIndex = currentWriteIdx;
    }
    
    /* 更新数据计数 */
    currentDataCount = ring->dataCount;
    currentDataCount += length;
    ring->dataCount = currentDataCount;
    
    return TRUE;
}

static boolean RingBuffer_Read(RingBuffer_Type* ring, uint8* dest, uint32 length)
{
    uint32 i;
    uint32 currentReadIdx;
    uint32 currentDataCount;
    
    if((ring == NULL) || (dest == NULL) || (length == 0u))
    {
        return FALSE;
    }
    
    if(ring->dataCount < length)
    {
        return FALSE;
    }
    
    /* 读取数据 */
    for(i = 0; i < length; i++)
    {
        currentReadIdx = ring->readIndex;
        dest[i] = ring->buffer[currentReadIdx];
        
        currentReadIdx++;
        if(currentReadIdx >= ring->bufferSize)
        {
            currentReadIdx = 0u;
        }
        ring->readIndex = currentReadIdx;
    }
    
    /* 更新数据计数 */
    currentDataCount = ring->dataCount;
    currentDataCount -= length;
    ring->dataCount = currentDataCount;
    
    return TRUE;
}

static uint32 RingBuffer_GetPendingSize(RingBuffer_Type* ring)
{
    if(ring == NULL)
    {
        return 0u;
    }
    return ring->dataCount;
}

static void RingBuffer_Clear(RingBuffer_Type* ring)
{
    if(ring != NULL)
    {
        ring->writeIndex = 0u;
        ring->readIndex = 0u;
        ring->dataCount = 0u;
    }
}

/******************************************************************************
 * 辅助函数
 ******************************************************************************/

/**
 * @brief   检查字符串是否以换行符结尾
 * @param   str     字符串
 * @param   length  字符串长度
 * @return  TRUE: 有换行符; FALSE: 无换行符
 */
static boolean HasNewlineAtEnd(const char* str, uint32 length)
{
    if(length == 0u)
    {
        return FALSE;
    }
    
    /* 检查是否以\r\n或\n结尾 */
    if(length >= 2u)
    {
        if((str[length - 2u] == '\r') && (str[length - 1u] == '\n'))
        {
            return TRUE;
        }
    }
    
    if(str[length - 1u] == '\n')
    {
        return TRUE;
    }
    
    return FALSE;
}

/**
 * @brief   处理打印数据（添加时间戳和换行符）
 * @param   channel         打印通道
 * @param   userData        用户原始数据
 * @param   userDataLen     用户数据长度
 * @return  处理后的完整字符串（在静态缓冲区中）
 */
static const char* DualPrint_ProcessMessage(PrintChannelType channel, 
                                             const char* userData, 
                                             uint32 userDataLen,
                                             uint32* outLen)
{
    static char processedBuffer[PRINT_MAX_FORMAT_BUFFER];
    uint32 pos = 0u;
    char timestamp[64u];
    uint32 timestampLen;
    
    (void)channel;  /* 避免未使用警告，可用于区分不同通道的时间戳格式 */
    
    if(processedBuffer == NULL || outLen == NULL)
    {
        return NULL;
    }
    
    /* 清空缓冲区 */
    (void)memset(processedBuffer, 0, PRINT_MAX_FORMAT_BUFFER);
    
    /* 1. 添加时间戳 */
    timestampLen = DualPrint_GetTimestamp(timestamp, sizeof(timestamp));
    if(timestampLen > 0u)
    {
        (void)memcpy(processedBuffer + pos, timestamp, timestampLen);
        pos += timestampLen;
    }
    
    /* 2. 添加用户数据 */
    if((userData != NULL) && (userDataLen > 0u))
    {
        (void)memcpy(processedBuffer + pos, userData, userDataLen);
        pos += userDataLen;
    }
    
    /* 3. 自动添加换行符（如果用户数据没有以换行符结尾）*/
#if (PRINT_AUTO_NEWLINE_ENABLE == STD_ON)
    {
        if(!HasNewlineAtEnd(processedBuffer, pos))
        {
            processedBuffer[pos] = '\r';
            pos++;
            processedBuffer[pos] = '\n';
            pos++;
        }
    }
#endif
    
    /* 确保字符串以空字符结尾 */
    if(pos < PRINT_MAX_FORMAT_BUFFER)
    {
        processedBuffer[pos] = '\0';
    }
    else
    {
        processedBuffer[PRINT_MAX_FORMAT_BUFFER - 1u] = '\0';
        pos = PRINT_MAX_FORMAT_BUFFER - 1u;
    }
    
    *outLen = pos;
    return processedBuffer;
}

/******************************************************************************
 * ETH发送辅助函数
 ******************************************************************************/
static Std_ReturnType Eth_SendData(const uint8* data, uint32 length)
{
    /* 注意：实际项目中需要根据ETH驱动实现构建正确的以太网帧
       以下为示例代码，需要根据实际Eth驱动API调整 */
    
    // Eth_FrameType ethFrame;
    // uint8 dstMacAddr[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; /* 广播地址 */
    
    // if((data == NULL) || (length == 0u))
    // {
    //     return E_NOT_OK;
    // }
    
    /* 构建以太网帧（简化版，实际需要设置MAC地址、VLAN等）*/
    // ethFrame.length = length;
    // ethFrame.buffer = (uint8*)data;
    // ethFrame.hwAddrHndl = 0u;
    // ethFrame.swAddrHndl = 0u;
    // ethFrame.txBufId = 0u;
    
    /* 调用ETH发送接口
       参数：控制器ID(0), 帧指针 */
    // return Eth_Transmit(0u, &ethFrame);
}

/******************************************************************************
 * 发送函数 - 立即发送模式
 ******************************************************************************/

/**
 * @brief   发送UART数据（立即发送，不等待回调）
 */
static void DualPrint_SendUartData(void)
{
    uint32 pendingSize;
    uint32 sendLength;
    uint8 txBuffer[UART_MAX_CHUNK_SIZE];
    Std_ReturnType ret;
    
    if(!UartChannel.isInitialized)
    {
        return;
    }
    
    DUALPRINT_ENTER_CRITICAL_SECTION();
    
    pendingSize = RingBuffer_GetPendingSize(&UartChannel.ringBuffer);
    if(pendingSize == 0u)
    {
        DUALPRINT_EXIT_CRITICAL_SECTION();
        return;
    }
    
    /* 计算本次发送长度 */
    sendLength = pendingSize;
    if(sendLength > UartChannel.ringBuffer.maxChunkSize)
    {
        sendLength = UartChannel.ringBuffer.maxChunkSize;
    }
    
    /* 从缓冲区读取数据 */
    if(!RingBuffer_Read(&UartChannel.ringBuffer, txBuffer, sendLength))
    {
        DUALPRINT_EXIT_CRITICAL_SECTION();
        return;
    }
    
    DUALPRINT_EXIT_CRITICAL_SECTION();
    
    /* 调用UART驱动发送（立即发送，不等待回调）*/
    ret = Uart_Write(0u, txBuffer, sendLength);
    
    if(ret == UART_E_OK)
    {
        /* 发送成功，更新统计 */
        DUALPRINT_ENTER_CRITICAL_SECTION();
        UartChannel.totalSentBytes += sendLength;
        DUALPRINT_EXIT_CRITICAL_SECTION();
    }
    else
    {
        /* 发送失败，数据已丢失（实际项目中需要重试机制）*/
    }
}

/**
 * @brief   发送ETH数据（立即发送，不等待回调）
 */
static void DualPrint_SendEthData(void)
{
    uint32 pendingSize;
    uint32 sendLength;
    uint8 txBuffer[ETH_MAX_CHUNK_SIZE];
    Std_ReturnType ret;

    if(!EthChannel.isInitialized)
    {
        return;
    }
    
    DUALPRINT_ENTER_CRITICAL_SECTION();
    
    pendingSize = RingBuffer_GetPendingSize(&EthChannel.ringBuffer);
    if(pendingSize == 0u)
    {
        DUALPRINT_EXIT_CRITICAL_SECTION();
        return;
    }
    
    /* 计算本次发送长度（不超过MTU）*/
    sendLength = pendingSize;
    if(sendLength > EthChannel.ringBuffer.maxChunkSize)
    {
        sendLength = EthChannel.ringBuffer.maxChunkSize;
    }
    
    /* 从缓冲区读取数据 */
    if(!RingBuffer_Read(&EthChannel.ringBuffer, txBuffer, sendLength))
    {
        DUALPRINT_EXIT_CRITICAL_SECTION();
        return;
    }
    
    /* 退出临界区，准备发送 */
    DUALPRINT_EXIT_CRITICAL_SECTION();
    
    /* 调用ETH驱动发送 */
    ret = Eth_SendData(txBuffer, sendLength);
    if(ret == E_OK)
    {
        /* 发送成功，更新统计 */
        DUALPRINT_ENTER_CRITICAL_SECTION();
        EthChannel.totalSentBytes += sendLength;
        DUALPRINT_EXIT_CRITICAL_SECTION();
    }
    else
    {
        /* 发送失败，数据已丢失 */
    }
}

/******************************************************************************
 * 初始化
 ******************************************************************************/
void DualPrint_Init(void)
{
    /* 初始化本地时间 */
    LocalTime_Init();
    DUALPRINT_ENTER_CRITICAL_SECTION();
    /* 初始化UART通道 */
    RingBuffer_Init(&UartChannel.ringBuffer, 
                    UartChannel.uartBuffer, 
                    UART_PRINT_RING_BUFFER_SIZE,
                    UART_MAX_CHUNK_SIZE);  /* UART单次最大发送128字节 */
    
    /* 初始化ETH通道 */
    RingBuffer_Init(&EthChannel.ringBuffer,
                    EthChannel.ethBuffer,
                    ETH_PRINT_RING_BUFFER_SIZE,
                    ETH_MAX_CHUNK_SIZE); /* ETH单次最大发送1500字节 */
    
    /* 初始化统计数据 */
    UartChannel.overflowCount = 0u;
    UartChannel.totalSentBytes = 0u;
    EthChannel.overflowCount = 0u;
    EthChannel.totalSentBytes = 0u;
    
    UartChannel.isInitialized = TRUE;
    EthChannel.isInitialized = TRUE;
    DualPrint_Initialized = TRUE;

    DUALPRINT_EXIT_CRITICAL_SECTION();

    Uart_Init(&Uart_Config);
}

void DualPrint_MainFunction(void)
{
    if(!DualPrint_Initialized)
    {
        return;
    }
    
    /* 更新时间 */
    LocalTime_Update();
    
    /* 发送数据 */
    DualPrint_SendUartData();
    DualPrint_SendEthData();
}

/******************************************************************************
 * 核心打印函数
 ******************************************************************************/
static PrintStatusType DualPrint_InternalPrint(PrintChannelType channel, const char* str)
{
    uint32 length;
    boolean uartResult = TRUE;
    boolean ethResult = TRUE;
    const char* processedMsg;
    uint32 processedLen;
    
    if(!DualPrint_Initialized)
    {
        return PRINT_STATUS_NOT_INITIALIZED;
    }
    
    if((str == NULL) || (channel == 0u))
    {
        return PRINT_STATUS_INVALID_CHANNEL;
    }
    
    length = (uint32)strlen(str);
    
    /* 处理消息（添加时间戳和换行符）*/
    processedMsg = DualPrint_ProcessMessage(channel, str, length, &processedLen);
    if(processedMsg == NULL)
    {
        return PRINT_STATUS_DRIVER_ERROR;
    }
    
    /* 进入临界区，保护环形缓冲区写入 */
    DUALPRINT_ENTER_CRITICAL_SECTION();
    
    if(channel & PRINT_CHANNEL_UART)
    {
        if(!RingBuffer_Write(&UartChannel.ringBuffer, (const uint8*)processedMsg, processedLen))
        {
            uartResult = FALSE;
            UartChannel.overflowCount++;
        }
    }
    
    if(channel & PRINT_CHANNEL_ETH)
    {
        if(!RingBuffer_Write(&EthChannel.ringBuffer, (const uint8*)processedMsg, processedLen))
        {
            ethResult = FALSE;
            EthChannel.overflowCount++;
        }
    }
    
    /* 退出临界区 */
    DUALPRINT_EXIT_CRITICAL_SECTION();
    
    /* 返回结果 */
    if(channel == PRINT_CHANNEL_UART)
    {
        return uartResult ? PRINT_STATUS_OK : PRINT_STATUS_BUFFER_FULL;
    }
    else if(channel == PRINT_CHANNEL_ETH)
    {
        return ethResult ? PRINT_STATUS_OK : PRINT_STATUS_BUFFER_FULL;
    }
    
    return (uartResult && ethResult) ? PRINT_STATUS_OK : PRINT_STATUS_BUFFER_FULL;
}

/**
 * @brief   格式化打印接口
 */
PrintStatusType DualPrint_Printf(PrintChannelType channel, const char *format, ...)
{
    char localBuffer[PRINT_MAX_FORMAT_BUFFER];
    va_list args;
    
    if((format == NULL) || (!DualPrint_Initialized))
    {
        return PRINT_STATUS_INVALID_CHANNEL;
    }
    
    /* 格式化到局部缓冲区（无需临界区保护）*/
    va_start(args, format);
    (void)vsprintf(localBuffer, format, args);
    va_end(args);
    
    /* 调用内部打印（使用临界区保护）*/
    return DualPrint_InternalPrint(channel, localBuffer);
}

/**
 * @brief   字符串打印接口
 */
PrintStatusType DualPrint_PrintString(PrintChannelType channel, const char *str)
{
    return DualPrint_InternalPrint(channel, str);
}

/**
 * @brief   二进制数据打印接口
 */
PrintStatusType DualPrint_PrintData(PrintChannelType channel, const uint8* data, uint32 length)
{
    uint32 i;
    uint32 pos = 0;
    char localBuffer[PRINT_MAX_FORMAT_BUFFER];
    
    if((data == NULL) || (length == 0u) || (!DualPrint_Initialized))
    {
        return PRINT_STATUS_INVALID_CHANNEL;
    }
    
    /* 格式化到局部缓冲区 */
    for(i = 0; i < length; i++)
    {
        pos += (uint32)sprintf(&localBuffer[pos], "%02X ", data[i]);
        if(((i + 1) % 16) == 0)
        {
            pos += (uint32)sprintf(&localBuffer[pos], "\r\n");
        }
    }
    
    if((length % 16) != 0)
    {
        pos += (uint32)sprintf(&localBuffer[pos], "\r\n");
    }
    
    return DualPrint_InternalPrint(channel, localBuffer);
}

/******************************************************************************
 * 辅助接口
 ******************************************************************************/
uint32 DualPrint_GetPendingDataLength(PrintChannelType channel)
{
    uint32 length = 0u;
    
    if(!DualPrint_Initialized)
    {
        return 0u;
    }
    
    DUALPRINT_ENTER_CRITICAL_SECTION();
    
    if(channel & PRINT_CHANNEL_UART)
    {
        length += RingBuffer_GetPendingSize(&UartChannel.ringBuffer);
    }
    
    if(channel & PRINT_CHANNEL_ETH)
    {
        length += RingBuffer_GetPendingSize(&EthChannel.ringBuffer);
    }
    
    DUALPRINT_EXIT_CRITICAL_SECTION();
    
    return length;
}

void DualPrint_ClearBuffer(PrintChannelType channel)
{
    if(!DualPrint_Initialized)
    {
        return;
    }
    
    DUALPRINT_ENTER_CRITICAL_SECTION();
    
    if(channel & PRINT_CHANNEL_UART)
    {
        RingBuffer_Clear(&UartChannel.ringBuffer);
    }
    
    if(channel & PRINT_CHANNEL_ETH)
    {
        RingBuffer_Clear(&EthChannel.ringBuffer);
    }
    
    DUALPRINT_EXIT_CRITICAL_SECTION();
}