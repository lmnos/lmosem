/**********************************************************
        hal层中断处理头文件halintupt.c
***********************************************************
                彭东 ＠ 2013.07.15.16.10
**********************************************************/

#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void intfltdsc_t_init(intfltdsc_t* initp,u32_t flg,u32_t sts,uint_t prity,uint_t irq)
{
    hal_spinlock_init(&initp->i_lock);
    initp->i_flg=flg;
    initp->i_stus=sts;
    initp->i_prity=prity;
    initp->i_irqnr=irq;
    initp->i_deep=0;
    initp->i_indx=0;
    list_init(&initp->i_serlist);
    initp->i_sernr=0;
    list_init(&initp->i_serthrdlst);
    initp->i_serthrdnr=0;
    initp->i_onethread=NULL;
    initp->i_rbtreeroot=NULL;
    list_init(&initp->i_serfisrlst);
    initp->i_serfisrnr=0;
    initp->i_msgmpool=NULL;
    initp->i_privp=NULL;
    initp->i_extp=NULL;  
    return;
}

void init_intfltdsc()
{
    for(uint_t i=0;i<IDTMAX;i++)
    {
        intfltdsc_t_init(&machintflt[i],0,0,i,i);
    }
    return;
}

PUBLIC void init_halintupt()
{
    init_descriptor();
    init_idt_descriptor();
    init_intfltdsc();
    return;
}

PUBLIC intfltdsc_t* hal_retn_intfltdsc(uint_t irqnr)
{
    if(irqnr>IDTMAX)
    {
        return NULL;
    }
    return &machintflt[irqnr];
}

void intserdsc_t_init(intserdsc_t* initp , u32_t flg,intfltdsc_t* intfltp,void* device,intflthandle_t handle)
{

    list_init(&initp->s_list);
    list_init(&initp->s_indevlst);
    initp->s_flg=flg;
    initp->s_intfltp=intfltp;
    initp->s_indx=0;
    initp->s_device=device;
    initp->s_handle=handle;
    return;
}

/*intfltdsc_t* hal_retn_intfltdsc(uint_t ifdnr)
{
    if(ifdnr>=osmach.mh_intfltnr)
    {
        return NULL;
    }
    
    return &osmach.mh_intfltdsc[ifdnr];
}

uint_t hal_retn_intnr()
{
    return (uint_t)hal_io32_read(INTOFFSET_R);
}*/

bool_t hal_add_ihandle(intfltdsc_t* intdscp,intserdsc_t* serdscp)
{
    if(intdscp==NULL||serdscp==NULL)
    {
        return FALSE;
    }
    cpuflg_t cpuflg;
    hal_spinlock_saveflg_cli(&intdscp->i_lock, &cpuflg);
    list_add(&serdscp->s_list,&intdscp->i_serlist);
    intdscp->i_sernr++;
    hal_spinunlock_restflg_sti(&intdscp->i_lock,&cpuflg);
    return TRUE;
       
}


drvstus_t hal_enable_intline(uint_t ifdnr)
{
    if(20>ifdnr||36<ifdnr)
    {
        return DFCERRSTUS;
    }
    i8259_enabled_line((u32_t)ifdnr);
    return DFCOKSTUS;
}

drvstus_t hal_disable_intline(uint_t ifdnr)
{

    if(20>ifdnr||36<ifdnr)
    {
        return DFCERRSTUS;
    }
    i8259_disable_line((u32_t)ifdnr);
    return DFCOKSTUS;
}


drvstus_t hal_intflt_default(uint_t ift_nr,void* sframe)
{
    if(ift_nr==0xffffffff||sframe==NULL)
    {
        return DFCERRSTUS;
    }
    return DFCOKSTUS;
}