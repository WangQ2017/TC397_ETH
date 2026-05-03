#if !defined(ETHIF_CBK_H)
# define ETHIF_CBK_H

#include "Eth_GeneralTypes.h"

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
void EthIf_RxIndication(
        uint8                                     CtrlIdx,
        Eth_FrameType                             FrameType,
        boolean                                   IsBroadcast,
        uint8 *                                   PhysAddrPtr,
        Eth_DataType*                             DataPtr,
        uint16                                    LenByte);

void EthIf_TxConfirmation(
  uint8  CtrlIdx,
  uint8  BufIdx);

#endif /* ETHIF_CBK_H */

