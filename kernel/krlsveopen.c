/**********************************************************
        LMOSEM内核服务文件krlsveopen.c
***********************************************************
                彭东 ＠ 2013.09.17.09.00
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

sysstus_t krlsvetabl_open(uint_t swinr,stkparame_t* stkparv)
{
    if(swinr!=SNR_FS_OPEN)
    {
        return SYSSTUSERR;
    }
    return (sysstus_t)krlsve_open((void*)stkparv->parmv1,(uint_t)stkparv->parmv2,
    (uint_t)stkparv->parmv3);
}


hand_t krlsve_open(void* file,uint_t flgs,uint_t stus)
{
    if(file==NULL)
    {
        return SYSSTUSERR;
    }
    return krlsve_core_open(file,flgs,stus);
}

hand_t krlsve_core_open(void* file,uint_t flgs,uint_t stus)
{
    devid_t devid={0,0,0};
    device_t* devp=NULL;
    objnode_t* ondp=NULL;
    hand_t rethd=NO_HAND;
    thread_t* tdp=krlsched_retn_currthread();
    if(((flgs&FILE_TY_MASK)==FILE_TY_DEV))
    {
        goto op_dev_step;       
    }
    if(((flgs&FILE_TY_MASK)==FILE_TY_FILE))
    {
        goto op_fil_step;
    }

    return NO_HAND;
op_dev_step:
    devid.dev_mtype=((devid_t*)file)->dev_mtype;
    devid.dev_stype=((devid_t*)file)->dev_stype;
    devid.dev_nr=((devid_t*)file)->dev_nr;
    devp=krlonidfl_retn_device((void*)(&devid),DIDFIL_IDN);
    if(devp==NULL)
    {
           return NO_HAND;
    }
    ondp=krlnew_objnode();
    if(ondp==NULL)
    {
           return NO_HAND;
    }
    ondp->on_opercode=IOIF_CODE_OPEN;
    ondp->on_objtype=OBJN_TY_DEV;
    ondp->on_objadr=devp;       
           
    rethd=krlthd_add_objnode(tdp,ondp);
    if(rethd==NO_HAND)
    {
        goto res_step;
    }    
    if(krlsve_open_device(ondp)==SYSSTUSERR)
    {

        goto res_step;
    }
    return rethd;

op_fil_step:
    devid.dev_mtype=FILESYS_DEVICE;
    devid.dev_stype=0;
    devid.dev_nr=0;
    devp=krlonidfl_retn_device((void*)(&devid),DIDFIL_IDN);
    if(devp==NULL)
    {
           return NO_HAND;
    }
    ondp=krlnew_objnode();
    if(ondp==NULL)
    {
           return NO_HAND;
    }

    ondp->on_opercode=IOIF_CODE_OPEN;
    ondp->on_objtype=OBJN_TY_FIL;
    ondp->on_objadr=devp;
    if(((flgs>>RWO_FLG_BITS)&RWO_FLG_MASK)==NF_FLG)
    {

        ondp->on_acsflgs=FSDEV_OPENFLG_NEWFILE;
        ondp->on_fname=file;
        if(krlsve_open_device(ondp)==SYSSTUSERR)
        {
            goto res_step;
        }
        if(krldel_objnode(ondp)==FALSE)
        {
            hal_sysdie("NEWFILE api del objnode err");
        }
        return 0;
    }
    else
    {
        ondp->on_acsflgs=FSDEV_OPENFLG_OPEFILE;
    }
    ondp->on_fname=file;

    rethd=krlthd_add_objnode(tdp,ondp);
    if(rethd==NO_HAND)
    {
        goto res_step;
    }
    if(krlsve_open_device(ondp)==SYSSTUSERR)
    {hal_sysdie("open sve die^^^^^^");
        goto res_step;
    }

    return rethd;
res_step:
    printfk("call open ok had%x \n\r",rethd);
    if(rethd!=NO_HAND)
    {
        if(krlthd_del_objnode(tdp,rethd)==NO_HAND)
        {
            hal_sysdie("open api td del objnode err");
        }
    }
    if(krldel_objnode(ondp)==FALSE)
    {
        hal_sysdie("open api del objnode err");
    }
    return NO_HAND;
        
}

sysstus_t krlsve_open_device(objnode_t* ondep)
{
    if(ondep->on_objadr==NULL)
    {
        return SYSSTUSERR;
    }
    if(krldev_io(ondep)==DFCERRSTUS)
    {
        return SYSSTUSERR;
    }
    return SYSSTUSOK;
}
