/**********************************************************
        LMOSEM内存管理API文件lapimm.c
***********************************************************
                彭东 ＠ 2013.09.15.12.10
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void* api_mallocblk(size_t blksz)
{
    void* retadr;
    API_ENTRY_PARE1(SNR_MM_ALLOC,retadr,blksz);
    return retadr;
}

sysstus_t api_mfreeblk(void* fradr,size_t blksz)
{
    sysstus_t retstus;
    API_ENTRY_PARE2(SNR_MM_FREE,retstus,fradr,blksz);
    return retstus;
}