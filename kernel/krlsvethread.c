/**********************************************************
        LMOSEM内核服务文件krlsvethread.c
***********************************************************
                彭东 ＠ 2013.09.17.09.00
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

sysstus_t krlsvetabl_exel_thread(uint_t swinr,stkparame_t* stkparv)
{
    if(swinr!=SNR_TD_EXEL)
    {
        return SYSSTUSERR;
    }
    return krlsve_exel_thread((void*)stkparv->parmv1,(uint_t)stkparv->parmv2);
}

sysstus_t krlsvetabl_exit_thread(uint_t swinr,stkparame_t* stkparv)
{
    if(swinr!=SNR_TD_EXIT)
    {
        return SYSSTUSERR;
    }
    return krlsve_exit_thread();
}

sysstus_t krlsvetabl_retn_threadhand(uint_t swinr,stkparame_t* stkparv)
{
    if(swinr!=SNR_TD_HAND)
    {
        return SYSSTUSERR;
    }
    return (sysstus_t)krlsve_retn_threadhand((void*)stkparv->parmv1);
}

sysstus_t krlsvetabl_retn_threadstats(uint_t swinr,stkparame_t* stkparv)
{
    if(swinr!=SNR_TD_RSTATS)
    {
        return SYSSTUSERR;
    }
    return krlsve_retn_threadstats((hand_t)stkparv->parmv1,(uint_t)stkparv->parmv2,
    (uint_t)stkparv->parmv3,(buf_t)stkparv->parmv4);
}

sysstus_t krlsvetabl_set_threadstats(uint_t swinr,stkparame_t* stkparv)
{
    if(swinr!=SNR_TD_SSTATS)
    {
        return SYSSTUSERR;
    }
    return krlsve_set_threadstats((hand_t)stkparv->parmv1,(uint_t)stkparv->parmv2,
    (uint_t)stkparv->parmv3,(buf_t)stkparv->parmv4);
}


hand_t krlsve_exel_thread(void* file,uint_t flgs)
{
    return SYSSTUSERR;
}

sysstus_t krlsve_exit_thread()
{
    return SYSSTUSERR;
}


hand_t krlsve_retn_threadhand(void* tname)
{
    if(tname==NULL)
    {
        thread_t* tdp=krlsched_retn_currthread();
        return (hand_t)(tdp->td_id);
    }
    return SYSSTUSERR;
}

sysstus_t krlsve_retn_threadstats(hand_t thand,uint_t scode,uint_t data,buf_t buf)
{
    return SYSSTUSERR;
}

sysstus_t krlsve_set_threadstats(hand_t thand,uint_t scode,uint_t data,buf_t buf)
{

    return SYSSTUSERR;
}

hand_t krlsve_core_exel_thread(void* file,uint_t flgs)
{
    return SYSSTUSERR;
}

void krlsve_core_exit_thread()
{
    return;
}


hand_t krlsve_core_retn_threadhand(void* tname)
{
    return SYSSTUSERR;
}

sysstus_t krlsve_core_retn_threadstats(hand_t thand,uint_t scode,uint_t data,buf_t buf)
{
    return SYSSTUSERR;
}

sysstus_t krlsve_core_set_threadstats(hand_t thand,uint_t scode,uint_t data,buf_t buf)
{

    return SYSSTUSERR;
}
