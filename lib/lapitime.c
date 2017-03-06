/**********************************************************
        LMOSEM文件管理API文件lapitime.c
***********************************************************
                彭东 ＠ 2013.09.30.17.40
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

sysstus_t api_time(buf_t ttime)
{
    
    sysstus_t rets;
    API_ENTRY_PARE1(SNR_TIME,rets,ttime);
    return rets;
}