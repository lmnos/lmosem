/**********************************************************
        LMOSEM内核等待链头文件krlwaitlist.c
***********************************************************
                彭东 ＠ 2013.09.24.20.30
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void kwlst_t_init(kwlst_t* initp)
{
    hal_spinlock_init(&initp->wl_lock);
    initp->wl_tdnr=0;
    list_init(&initp->wl_list);
    return;
}
void krlwlst_wait(kwlst_t* wlst)
{
    krlsched_wait(wlst);
    return;
}
void krlwlst_up(kwlst_t* wlst)
{
    if(list_is_empty_careful(&wlst->wl_list)==TRUE)
    {
        return;
    }
    krlsched_up(wlst);
    
    return;
}

void krlwlst_allup(kwlst_t* wlst)
{
    while(list_is_empty_careful(&wlst->wl_list)==FALSE)
    {
        krlsched_up(wlst);

    }
    return;
}

void krlwlst_add_thread(kwlst_t* wlst,thread_t* tdp)
{
    cpuflg_t cufg;
    hal_spinlock_saveflg_cli(&wlst->wl_lock,&cufg);
    
    list_add(&tdp->td_list,&wlst->wl_list);
    wlst->wl_tdnr++;   
    hal_spinunlock_restflg_sti(&wlst->wl_lock,&cufg);
    return;
}

thread_t* krlwlst_del_thread(kwlst_t *wlst)
{

    thread_t* tdp=NULL;
    cpuflg_t cufg;
    list_h_t* list;
    hal_spinlock_saveflg_cli(&wlst->wl_lock,&cufg);
    list_for_each(list,&wlst->wl_list)
    {
        tdp=list_entry(list,thread_t,td_list);
        if(tdp==NULL||wlst->wl_tdnr<1)
        {
            tdp=NULL;
            goto return_step;
        }
        list_del(&tdp->td_list);
        wlst->wl_tdnr--;
        tdp=tdp;
        goto return_step;
        
    }
    tdp=NULL;
return_step:    
    hal_spinunlock_restflg_sti(&wlst->wl_lock,&cufg);
    return tdp;
}