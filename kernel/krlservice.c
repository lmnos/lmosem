/**********************************************************
        LMOSEM内核服务文件krlservice.c
***********************************************************
                彭东 ＠ 2013.09.17.11.30
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"
sysstus_t krlservice(uint_t swinr,void* sframe)
{
    return osscalltab[swinr](swinr,(stkparame_t*)sframe);
}