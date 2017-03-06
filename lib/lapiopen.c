/**********************************************************
        LMOSEM文件管理API文件lapiopen.c
***********************************************************
                彭东 ＠ 2013.09.15.12.10
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"



hand_t api_open(void* file,uint_t flgs,uint_t stus)
{
    hand_t rethand;
    API_ENTRY_PARE3(SNR_FS_OPEN,rethand,file,flgs,stus);
    return rethand;
}