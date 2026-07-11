#ifndef CDD_SOMEIP_H
#define CDD_SOMEIP_H

#include "ComStack_Types.h"


void Cdd_SomeIP_LdComRx_VechicleSpeed(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
void Cdd_SomeIP_LdComRx_VechicleStatus(P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
void Cdd_SomeIP_ComNotify_VechicleInfoRx(void);

#endif /* CDD_SOMEIP_H */