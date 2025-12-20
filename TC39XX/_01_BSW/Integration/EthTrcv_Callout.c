#include "EthTrcv_Callout.h"
#include "Dio.h"

void EthTrcv_PostTrcvInitCallout(uint8 EthTrcvIdx)
{

}
void EthTrcv_PreTrcvInitCallout(uint8 EthTrcvIdx)
{
    
}

volatile uint32 delayCnt = 0;
void EthTrcv_PhyReset()
{

    Dio_WriteChannel(DioConf_DioChannel_DioChannel_PHY_RESET,0);
    while (delayCnt < 10000000)
    {
        delayCnt++;
        __nop();
    }
    delayCnt = 0;
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_PHY_RESET,1);
    while (delayCnt < 10000000)
    {
        delayCnt++;
        __nop();
    }
}