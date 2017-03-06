/**********************************************************
        LMOSEM内核服务文件krlsvemm.c
***********************************************************
                彭东 ＠ 2013.09.17.09.00
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

sysstus_t krlsvetabl_mallocblk(uint_t swinr,stkparame_t* stkparv)
{

    if(swinr!=SNR_MM_ALLOC)
    {
        return SYSSTUSERR;
    }
    return (sysstus_t)krlsve_mallocblk((size_t)stkparv->parmv1);
}

sysstus_t krlsvetabl_mfreeblk(uint_t swinr,stkparame_t* stkparv)
{
    if(swinr!=SNR_MM_FREE)
    {
        return SYSSTUSERR;
    }
    return krlsve_mfreeblk((void*)stkparv->parmv1,(size_t)stkparv->parmv2);
}

void* krlsve_mallocblk(size_t blksz)
{
    if(blksz>=0x400000)
    {
        return NULL;
    }
    return krlsve_core_mallocblk(blksz);
}

sysstus_t krlsve_mfreeblk(void* fradr,size_t blksz)
{
    if(fradr==NULL||blksz>=0x400000)
    {
        return SYSSTUSERR;
    }
    return krlsve_core_mfreeblk(fradr,blksz);
}

void* krlsve_core_mallocblk(size_t blksz)
{
    return (void*)krlnew(blksz);
}

sysstus_t krlsve_core_mfreeblk(void* fradr,size_t blksz)
{
    if(krldelete((adr_t)fradr,blksz)==FALSE)
    {
        hal_sysdie("krlsve_core_mfreeblk err");
    }
    return SYSSTUSOK;
}