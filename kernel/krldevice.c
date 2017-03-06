/**********************************************************
        LMOSEM设备管理文件krldevice.c
***********************************************************
                彭东 ＠ 2013.08.16.15.30
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"
void devtlst_t_init(devtlst_t* initp,uint_t dtype)
{
    initp->dtl_type=dtype;
    initp->dtl_nr=0;
    list_init(&initp->dtl_list);
    
    return;
}
void devtable_t_init(devtable_t* initp)
{
    list_init(&initp->devt_list);
    hal_spinlock_init(&initp->devt_lock);
    list_init(&initp->devt_devlist);
    list_init(&initp->devt_drvlist);
    initp->devt_devnr=0;
    initp->devt_drvnr=0;
    for(uint_t t=0;t<DEVICE_MAX;t++)
    {
        devtlst_t_init(&initp->devt_devclsl[t],t);
    }
    return;
}

void devid_t_init(devid_t* initp,uint_t mty,uint_t sty,uint_t nr)
{
    initp->dev_mtype=mty;
    initp->dev_stype=sty;
    initp->dev_nr=nr;
    return;
}

void device_t_init(device_t* initp)
{
    list_init(&initp->dev_list);
    list_init(&initp->dev_indrvlst);
    list_init(&initp->dev_intbllst);
    hal_spinlock_init(&initp->dev_lock);
    initp->dev_count=0;
    krlsem_t_init(&initp->dev_sem);
    initp->dev_stus=0;
    initp->dev_flgs=0;
    devid_t_init(&initp->dev_id,0,0,0);
    initp->dev_intlnenr=0;
    list_init(&initp->dev_intserlst);
    list_init(&initp->dev_rqlist);
    initp->dev_rqlnr=0;
    krlsem_t_init(&initp->dev_waitints);
    initp->dev_drv=NULL;
    initp->dev_attrb=NULL;
    initp->dev_privdata=NULL;
    initp->dev_userdata=NULL;
    initp->dev_extdata=NULL;
    initp->dev_name=NULL;
    
    return;
}


void krlretn_driverid(driver_t* dverp)
{
    dverp->drv_id=(uint_t)dverp;
    return;
}

void driver_t_init(driver_t* initp)
{
    hal_spinlock_init(&initp->drv_lock);
    list_init(&initp->drv_list);
    initp->drv_stuts=0;
    initp->drv_flg=0;
    krlretn_driverid(initp);
    initp->drv_count=0;
    krlsem_t_init(&initp->drv_sem);
    initp->drv_safedsc=NULL;
    initp->drv_attrb=NULL;
    initp->drv_privdata=NULL;
    
    for(uint_t dsi=0;dsi<IOIF_CODE_MAX;dsi++)
    {
        initp->drv_dipfun[dsi]=drv_defalt_func;
    }
    list_init(&initp->drv_alldevlist);
    initp->drv_entry=NULL;
    initp->drv_exit=NULL;
    initp->drv_userdata=NULL;
    initp->drv_extdata=NULL;
    initp->drv_name=NULL;
    return;
}


void init_krldevice()
{
    devtable_t_init(&osdevtable);
    return;
}


drvstus_t krlrun_driverentry(drventyexit_t drventry)
{
    driver_t* drvp=new_driver_dsc();
    if(drvp==NULL)
    {
        return DFCERRSTUS;
    }
    if(drventry(drvp,0,NULL)==DFCERRSTUS)
    {
        return DFCERRSTUS;
    }
    if(krldriver_add_system(drvp)==DFCERRSTUS)
    {
        return DFCERRSTUS;
    }
    return DFCOKSTUS;
}

void init_krldriver()
{
    for(uint_t ei=0;osdrvetytabl[ei]!=NULL;ei++)
    {
        if(krlrun_driverentry(osdrvetytabl[ei])==DFCERRSTUS)
        {
            hal_sysdie("init driver err");
        }       
    }
    return;
}


drvstus_t del_driver_dsc(driver_t* drvp)
{
    if(krldelete((adr_t)drvp,sizeof(driver_t))==FALSE)
    {
        return DFCERRSTUS;
    }
    return DFCOKSTUS;
}

driver_t* new_driver_dsc()
{
    driver_t* dp=(driver_t*)krlnew(sizeof(driver_t));
    if(dp==NULL)
    {
        return NULL;
    }
    driver_t_init(dp);
    
    return dp;
}

drvstus_t del_device_dsc(device_t* devp)
{
    if(krldelete((adr_t)devp,sizeof(device_t))==FALSE)
    {
        return DFCERRSTUS;
    }
    return DFCOKSTUS;
}

device_t* new_device_dsc()
{
    device_t* dp=(device_t*)krlnew(sizeof(device_t));
    if(dp==NULL)
    {
        return NULL;
    }
    device_t_init(dp);
    
    return dp;
}





drvstus_t drv_defalt_func(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

bool_t krlcmp_devid(devid_t* sdidp,devid_t* cdidp)
{
    if(sdidp->dev_mtype!=cdidp->dev_mtype)
    {
        return FALSE;
    }
    if(sdidp->dev_stype!=cdidp->dev_stype)
    {
        return FALSE;
    }
    if(sdidp->dev_nr!=cdidp->dev_nr)
    {
        return FALSE;
    }
    return TRUE;
}

drvstus_t krldriver_add_system(driver_t* drvp)
{
    cpuflg_t cpufg;
    devtable_t* dtbp=&osdevtable;
    hal_spinlock_saveflg_cli(&dtbp->devt_lock,&cpufg);
    list_add(&drvp->drv_list,&dtbp->devt_drvlist);
    dtbp->devt_drvnr++;
    hal_spinunlock_restflg_sti(&dtbp->devt_lock,&cpufg);
    return DFCOKSTUS;
}

drvstus_t krldev_add_driver(device_t* devp,driver_t* drvp)
{
    list_h_t* lst;
    device_t* fdevp;
    if(devp==NULL||drvp==NULL)
    {
        return DFCERRSTUS;
    }
    list_for_each(lst,&drvp->drv_alldevlist)
    {
        fdevp=list_entry(lst,device_t,dev_indrvlst);
        if(krlcmp_devid(&devp->dev_id,&fdevp->dev_id)==TRUE)
        {
            return DFCERRSTUS;
        }
    }
    
    list_add(&devp->dev_indrvlst,&drvp->drv_alldevlist);
    devp->dev_drv=drvp;
    return DFCOKSTUS;
}



drvstus_t krlnew_device(device_t* devp)
{
    device_t* findevp;
    drvstus_t rets=DFCERRSTUS;
    cpuflg_t cpufg;
    list_h_t* lstp;
    devtable_t* dtbp=&osdevtable;
    uint_t devmty=devp->dev_id.dev_mtype;
    if(devp==NULL)
    {
        return DFCERRSTUS;
    }
    if(devp->dev_drv==NULL)
    {
        return DFCERRSTUS;
    }
    if(devmty>=DEVICE_MAX)
    {
        return DFCERRSTUS;
    }
   
    
    hal_spinlock_saveflg_cli(&dtbp->devt_lock,&cpufg);
    if(devmty!=dtbp->devt_devclsl[devmty].dtl_type)
    {
        rets=DFCERRSTUS;
        goto return_step;
    }
    list_for_each(lstp,&dtbp->devt_devclsl[devmty].dtl_list)
    {
        findevp=list_entry(lstp,device_t,dev_intbllst);
        if(krlcmp_devid(&devp->dev_id,&findevp->dev_id)==TRUE)
        {
            rets=DFCERRSTUS;
            goto return_step;
        }
    }
    
    list_add(&devp->dev_intbllst,&dtbp->devt_devclsl[devmty].dtl_list);
    list_add(&devp->dev_list,&dtbp->devt_devlist);
    dtbp->devt_devclsl[devmty].dtl_nr++;
    dtbp->devt_devnr++;
    rets=DFCOKSTUS;
return_step:
    hal_spinunlock_restflg_sti(&dtbp->devt_lock,&cpufg);
    return rets;
}

drvstus_t krldev_inc_devcount(device_t* devp)
{
    
    if(devp->dev_count>=(~0UL))
    {
        return DFCERRSTUS;
    }
    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&devp->dev_lock,&cpufg);
    devp->dev_count++;
    hal_spinunlock_restflg_sti(&devp->dev_lock,&cpufg);
    return DFCOKSTUS;
}


drvstus_t krldev_dec_devcount(device_t* devp)
{
    
    if(devp->dev_count<(1))
    {
        return DFCERRSTUS;
    }
    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&devp->dev_lock,&cpufg);
    devp->dev_count--;
    hal_spinunlock_restflg_sti(&devp->dev_lock,&cpufg);
    return DFCOKSTUS;
}


drvstus_t krldev_add_request(device_t *devp, objnode_t* request)
{
    cpuflg_t cpufg;
    objnode_t* np=(objnode_t*)request;
    hal_spinlock_saveflg_cli(&devp->dev_lock,&cpufg);
    list_add_tail(&np->on_list,&devp->dev_rqlist);
    devp->dev_rqlnr++;
    hal_spinunlock_restflg_sti(&devp->dev_lock,&cpufg);
    return DFCOKSTUS;
}

drvstus_t krldev_complete_request(device_t *devp, objnode_t* request)
{
    if(devp==NULL||request==NULL)
    {
        return DFCERRSTUS;
    }
    if(devp->dev_rqlnr<1)
    {
        hal_sysdie("krldev_complete_request err devp->dev_rqlnr<1");
    }
    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&devp->dev_lock,&cpufg);
    list_del(&request->on_list);
    devp->dev_rqlnr--;
    hal_spinunlock_restflg_sti(&devp->dev_lock,&cpufg);
    krlsem_up(&request->on_complesem);
    return DFCOKSTUS;
}

drvstus_t krldev_retn_request(device_t *devp,uint_t iocode,objnode_t** retreq)
{
    if(retreq==NULL||iocode>=IOIF_CODE_MAX)
    {
        return DFCERRSTUS;
    }
    cpuflg_t cpufg;
    objnode_t* np;
    list_h_t* list;
    drvstus_t rets=DFCERRSTUS;
    hal_spinlock_saveflg_cli(&devp->dev_lock,&cpufg);
    list_for_each(list,&devp->dev_rqlist)
    {
        np=list_entry(list,objnode_t,on_list);
        if(np->on_opercode==(sint_t)iocode)
        {
            *retreq=np;
            rets=DFCOKSTUS;
            goto return_step;
        }
    }
    rets=DFCERRSTUS;
    *retreq=NULL;
return_step:    
    hal_spinunlock_restflg_sti(&devp->dev_lock,&cpufg);
    return rets;
}


drvstus_t krldev_wait_request(device_t *devp, objnode_t* request)
{
    if(devp==NULL||request==NULL)
    {
        return DFCERRSTUS;
    }
    krlsem_down(&request->on_complesem);
    return DFCOKSTUS;
}

void krldev_wait_intupt(device_t *devp)
{
    return;   
}

void krldev_up_intupt(device_t *devp)
{
    return;   
}

drvstus_t krldev_retn_rqueparm(void* request,buf_t* retbuf,uint_t* retcops,uint_t* retlen,uint_t* retioclde,uint_t* retbufcops,size_t* retbufsz)
{
    objnode_t* ondep=(objnode_t*)request;
    if(ondep==NULL)
    {
        return DFCERRSTUS;
    }
    if(retbuf!=NULL)
    {
        *retbuf=ondep->on_buf;
    }
    if(retcops!=NULL)
    {
        *retcops=ondep->on_currops;
    }
    if(retlen!=NULL)
    {
        *retlen=ondep->on_len;
    }
    if(retioclde!=NULL)
    {
        *retioclde=ondep->on_ioctrd;
    }
    if(retbufcops!=NULL)
    {
        *retbufcops=ondep->on_bufcurops;
    }
    if(retbufsz!=NULL)
    {
        *retbufsz=ondep->on_bufsz;
    }
    return DFCOKSTUS;
}

device_t* krlonidfl_retn_device(void* dfname,uint_t flgs)
{
    device_t* findevp;
    cpuflg_t cpufg;
    list_h_t* lstp;
    devtable_t* dtbp=&osdevtable;
    
    if(dfname==NULL||flgs!=DIDFIL_IDN)
    {
        return NULL;
    }
    devid_t* didp=(devid_t*)dfname;
    uint_t devmty=didp->dev_mtype;
    if(devmty>=DEVICE_MAX)
    {
        return NULL;
    }
    hal_spinlock_saveflg_cli(&dtbp->devt_lock,&cpufg);
    if(devmty!=dtbp->devt_devclsl[devmty].dtl_type)
    {
        findevp=NULL;
        goto return_step;
    }
    list_for_each(lstp,&dtbp->devt_devclsl[devmty].dtl_list)
    {
        findevp=list_entry(lstp,device_t,dev_intbllst);
        if(krlcmp_devid(didp,&findevp->dev_id)==TRUE)
        {
            findevp=findevp;
            goto return_step;
        }
    }
   
    findevp=NULL;
return_step:
    hal_spinunlock_restflg_sti(&dtbp->devt_lock,&cpufg);
    return findevp;
}

drvstus_t krlnew_devhandle(device_t* devp,intflthandle_t handle,uint_t phyiline)
{
    intserdsc_t* sdp=krladd_irqhandle(devp,handle,phyiline);
    if(sdp==NULL)
    {
        
        return DFCERRSTUS;
    }
    cpuflg_t cpufg;
    hal_spinlock_saveflg_cli(&devp->dev_lock,&cpufg);
    
    list_add(&sdp->s_indevlst,&devp->dev_intserlst);
    devp->dev_intlnenr++;
    hal_spinunlock_restflg_sti(&devp->dev_lock,&cpufg);
    return DFCOKSTUS;
}

drvstus_t krldev_io(objnode_t* nodep)
{
    device_t* devp=(device_t*)(nodep->on_objadr);
    if((nodep->on_objtype!=OBJN_TY_DEV&&nodep->on_objtype!=OBJN_TY_FIL)||nodep->on_objadr==NULL)
    {
        return DFCERRSTUS;
    }
    if(nodep->on_opercode<0||nodep->on_opercode>=IOIF_CODE_MAX)
    {
        return DFCERRSTUS;
    }
    return krldev_call_driver(devp,nodep->on_opercode,0,0,NULL,nodep);
}

drvstus_t krldev_call_driver(device_t* devp,uint_t iocode,uint_t val1,uint_t val2,void* p1,void* p2)
{
    driver_t* drvp=NULL;
    if(devp==NULL||iocode>=IOIF_CODE_MAX)
    {
        return DFCERRSTUS;
    }
    drvp=devp->dev_drv;
    if(drvp==NULL)
    {
        return DFCERRSTUS;
    }
    return drvp->drv_dipfun[iocode](devp,p2);
}
