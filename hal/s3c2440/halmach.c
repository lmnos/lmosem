/****************************************************************
        LMOSEM HAL板级体系初始化文件halmach.c
*****************************************************************
                彭东 ＠ 2013.07.06.15.50
****************************************************************/

#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void init_halmach()
{
    mach_t_init(&osmach);
    return;
}

void mach_t_init(mach_t* initp)
{
    hal_spinlock_init(&initp->mh_lock);
    list_init(&initp->mh_list);
    initp->mh_kerinramstart=KRNL_INRAM_START;
    initp->mh_kerinramend=(adr_t)(&__end_kernel);
    initp->mh_mmapdscadr=(mmapdsc_t*)(ALIGN(((uint_t)(&__end_kernel)),4096));
    initp->mh_mmapdscnr=0;
    initp->mh_spedscnr=PLFM_ADRSPCE_NR;
    initp->mh_spedsc=machadrspce;
  
    initp->mh_intfltdsc=machintflt;
    initp->mh_intfltnr=IRQ_MAX;
    return;
}

void print_mach(mach_t* mchp)
{
    printfk("mach.mh_kerinramstart:%x\n\r",(uint_t)mchp->mh_kerinramstart);
    printfk("mach.mh_kerinramend:%x\n\r",(uint_t)mchp->mh_kerinramend);
    printfk("mach.mh_mmapdscadr:%x\n\r",(uint_t)mchp->mh_mmapdscadr);
    printfk("mach.mh_mmapdscnr:%x\n\r",(uint_t)mchp->mh_mmapdscnr);
    printfk("mach.mh_intfltdsc:%x\n\r",(uint_t)mchp->mh_intfltdsc);
    printfk("mach.mh_intfltnr:%x\n\r",(uint_t)mchp->mh_intfltnr);
    return;
}

