#include "EthTrcv_Callout.h"
#include "Cdd_Log.h"
#include "Dio.h"
#include "EthTrcv_GeneralTypes.h"

void EthTrcv_PreTrcvInitCallout(uint8 EthTrcvIdx)
{
    CDD_LOG_DEBUG("PHY configuration is Started!");
}

void EthTrcv_PostTrcvInitCallout(uint8 EthTrcvIdx)
{
    uint32  OrgUniqueId = 0;
    uint8  ModelNr = 0;
    uint8  RevisionNr = 0;
    uint16 regVal = 0;

    Std_ReturnType ret = EthTrcv_30_Tja1100_GetPhyIdentifier(0, &OrgUniqueId, &ModelNr, &RevisionNr);
    if (ret == E_OK)
    {
        CDD_LOG_DEBUG("Post:OrgUniqueId=0x%x, ModelNr=0x%x, RevisionNr=0x%x", OrgUniqueId, ModelNr, RevisionNr);
    }
    else
    {
        CDD_LOG_ERROR("Post:get phy id failed");
    }

    EthTrcv_BaudRateType BaudRate;
    ret = EthTrcv_30_Tja1100_GetBaudRate(0, &BaudRate);
    if (ret == E_OK)
    {
        CDD_LOG_DEBUG("Post:BaudRate=%d", BaudRate);
    }
    else
    {
        CDD_LOG_ERROR("Post:get Baud Rate failed");
    }

    EthTrcv_DuplexModeType DuplexMode;
    ret = EthTrcv_30_Tja1100_GetDuplexMode(0, &DuplexMode);
    if (ret == E_OK)
    {
        CDD_LOG_DEBUG("Post:DuplexMode=%d", DuplexMode);
    }
    else
    {
        CDD_LOG_ERROR("Post:get Duplex Mode failed");
    }

    (void)EthTrcv_30_Tja1100_Internal_ReadTrcvReg(0, 1, &regVal);
    if ((regVal != 0xffff) && ((regVal & 0x4) == 0x4))
    {
        CDD_LOG_DEBUG("PHY is link up!");
    }
    else
    {
        CDD_LOG_DEBUG("PHY is link down!");
    }

    CDD_LOG_DEBUG("PHY configuration is Finished!");
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