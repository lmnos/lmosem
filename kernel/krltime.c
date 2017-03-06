/**********************************************************
        LMOSEM时间文件krltime.c
***********************************************************
                彭东 ＠ 2013.09.30.16.30
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void ktime_t_init(ktime_t* initp)
{
    hal_spinlock_init(&initp->kt_lock);
    initp->kt_year=0;
    initp->kt_mon=0;
    initp->kt_day=0;
    initp->kt_date=0;
    initp->kt_hour=0;
    initp->kt_min=0;
    initp->kt_sec=0;
    initp->kt_datap=NULL;
    return;
}

void init_ktime()
{
    ktime_t_init(&osktime);
    return;
}


void krlupdate_times(uint_t year,uint_t mon,uint_t day,uint_t date,uint_t hour,uint_t min,uint_t sec)
{
    ktime_t* initp=&osktime;
    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&initp->kt_lock,&cpufg);
    initp->kt_year=year;
    initp->kt_mon=mon;
    initp->kt_day=day;
    initp->kt_date=date;
    initp->kt_hour=hour;
    initp->kt_min=min;
    initp->kt_sec=sec;
    hal_spinunlock_restflg_sti(&initp->kt_lock,&cpufg);
    return;
}


sysstus_t krlsvetabl_time(uint_t swinr,stkparame_t* stkparv)
{
    if(swinr!=SNR_TIME)
    {
        return SYSSTUSERR;
    }
    return krlsve_time((time_t*)stkparv->parmv1);
}

sysstus_t krlsve_time(time_t* time)
{
    if(time==NULL)
    {
        return SYSSTUSERR;
    }
    
    ktime_t* initp=&osktime;
    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&initp->kt_lock,&cpufg);
    time->year=initp->kt_year;
    time->mon=initp->kt_mon;
    time->day=initp->kt_day;
    time->date=initp->kt_date;
    time->hour=initp->kt_hour;
    time->min=initp->kt_min;
    time->sec=initp->kt_sec;
    hal_spinunlock_restflg_sti(&initp->kt_lock,&cpufg);

    
    return SYSSTUSOK;
}
