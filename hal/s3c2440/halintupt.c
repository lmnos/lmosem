/**********************************************************
        hal层中断处理头文件halintupt.c
***********************************************************
                彭东 ＠ 2013.07.15.16.10
**********************************************************/

#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void init_halintupt()
{
    init_intfltdsc(&osmach);
    return;
}



void init_intfltdsc(mach_t* machp)
{
    intfltdsc_t* ifdp=machp->mh_intfltdsc;
    uint_t ifdnr=machp->mh_intfltnr;
    if(ifdnr>IRQ_MAX)
    {
        hal_sysdie("init intflt err");
    }
    for(uint_t i=MINTNR_START; i<=MINTNR_END;i++)
    {
        intfltdsc_t_init(&ifdp[i],MINT_FLG,0,i-MINT_OFFSET,i);
    }

    for(uint_t i=SINTNR_START; i<=SINTNR_END;i++)
    {
        intfltdsc_t_init(&ifdp[i],SINT_FLG,0,i-SINT_OFFSET,i);
    }
    
    for(uint_t i=EINTNR_START; i<=EINTNR_END;i++)
    {
        intfltdsc_t_init(&ifdp[i],EINT_FLG,0,i-EINT_OFFSET,i);
    }



    return;
}



void intfltdsc_t_init(intfltdsc_t* initp,u32_t flg,u32_t stus,u32_t pbitnr,uint_t irqnr)
{
    hal_spinlock_init(&initp->i_lock);
    list_init(&initp->i_serlist);
    initp->i_sernr=0;
    initp->i_flg=flg;
    initp->i_stus=stus;
    initp->i_pndbitnr=pbitnr;
    initp->i_irqnr=irqnr;
    initp->i_deep=0;
    initp->i_indx=0;

    return;
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

intfltdsc_t* hal_retn_intfltdsc(uint_t ifdnr)
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
}

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

drvstus_t hal_clear_intpnd(uint_t bitnr)
{
     u32_t inttmp=(1<<bitnr);
     hal_io32_write(INTPND_R,inttmp);   
     return DFCOKSTUS;
}

drvstus_t hal_clear_srcpnd(uint_t ifdnr)
{
    u32_t inttmp;
    uint_t flg;
    uint_t phylinenr;
    intfltdsc_t* ifdp=hal_retn_intfltdsc(ifdnr);
    if(ifdp==NULL)
    {   
        
        return DFCERRSTUS;
    }
    
    flg=ifdp->i_flg&0xff;
    phylinenr=ifdp->i_pndbitnr;
    
    if(flg==MINT_FLG)
    {
        
        inttmp=(1<<phylinenr);
        hal_io32_write(SRCPND_R,inttmp);
        
        return DFCOKSTUS;
    }
    if(flg==SINT_FLG)
    {
       

        inttmp=(1<<phylinenr);
        hal_io32_write(SUBSRCPND_R,inttmp);
        return DFCOKSTUS;
    }
    
    if(flg==EINT_FLG)
    {
        
        inttmp=(1<<phylinenr);
        hal_io32_write(EINTPEND_R,inttmp);
        return DFCOKSTUS;
    }
    
    return DFCERRSTUS;
}

drvstus_t hal_enable_intline(uint_t ifdnr)
{
    u32_t inttmp;
    uint_t flg;
    uint_t phylinenr;
    intfltdsc_t* ifdp=hal_retn_intfltdsc(ifdnr);
    if(ifdp==NULL)
    {   
        
        return DFCERRSTUS;
    }
    
    flg=ifdp->i_flg&0xff;
    phylinenr=ifdp->i_pndbitnr;
    

    if(flg==MINT_FLG)
    {
        inttmp=hal_io32_read(INTMSK_R);
        inttmp&=(~(1<<phylinenr));
        hal_io32_write(INTMSK_R,inttmp);
        return DFCOKSTUS;
    }
    if(flg==SINT_FLG)
    {
       
        inttmp=hal_io32_read(INTSUBMSK_R);
        inttmp&=(~(1<<phylinenr));
        hal_io32_write(INTSUBMSK_R,inttmp);

        return DFCOKSTUS;
    }
    
    if(flg==EINT_FLG)
    {
        
        inttmp=hal_io32_read(EINTMASK_R);
        inttmp&=(~(1<<phylinenr));
        hal_io32_write(EINTMASK_R,inttmp);
        return DFCOKSTUS;
    }
    
    return DFCERRSTUS;
}

drvstus_t hal_disable_intline(uint_t ifdnr)
{

    u32_t inttmp;
    uint_t flg;
    uint_t phylinenr;
    intfltdsc_t* ifdp=hal_retn_intfltdsc(ifdnr);
    if(ifdp==NULL)
    {
        return DFCERRSTUS;
    }
    
    flg=ifdp->i_flg&0xff;
    phylinenr=ifdp->i_pndbitnr;
    

    if(flg==MINT_FLG)
    {
        inttmp=hal_io32_read(INTMSK_R);
        inttmp|=(1<<phylinenr);
        hal_io32_write(INTMSK_R,inttmp);
        return DFCOKSTUS;
    }
    if(flg==SINT_FLG)
    {
       
        inttmp=hal_io32_read(INTSUBMSK_R);
        inttmp|=(1<<phylinenr);
        hal_io32_write(INTSUBMSK_R,inttmp);
        return DFCOKSTUS;
    }
    
    if(flg==EINT_FLG)
    {
        
        inttmp=hal_io32_read(EINTMASK_R);
        inttmp|=(1<<phylinenr);
        hal_io32_write(EINTMASK_R,inttmp);
        return DFCOKSTUS;
    }
    return DFCERRSTUS;
}


drvstus_t hal_intflt_default(uint_t ift_nr,void* sframe)
{
    if(ift_nr==0xffffffff||sframe==NULL)
    {
        return DFCERRSTUS;
    }
    return DFCOKSTUS;
}