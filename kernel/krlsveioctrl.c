/**********************************************************
        LMOSEM内核服务文件krlsveioctrl.c
***********************************************************
                彭东 ＠ 2013.09.17.09.00
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"
sysstus_t krlsvetabl_ioctrl(uint_t swinr,stkparame_t* stkparv)
{
    if(swinr!=SNR_FS_IOCTRL)
    {
        return SYSSTUSERR;
    }
    return krlsve_ioctrl((hand_t)stkparv->parmv1,(buf_t)stkparv->parmv2,
    (uint_t)stkparv->parmv3,(uint_t)stkparv->parmv4);
}

sysstus_t krlsve_ioctrl(hand_t fhand,buf_t buf,uint_t iocode,uint_t flgs)
{
    if(fhand==NO_HAND)
    {
        return SYSSTUSERR;
    }
    return krlsve_core_ioctrl(fhand,buf,iocode,flgs);
}

sysstus_t krlsve_core_ioctrl(hand_t fhand,buf_t buf,uint_t iocode,uint_t flgs)
{

    thread_t* currtd=krlsched_retn_currthread();
    objnode_t* onp=krlthd_retn_objnode(currtd,fhand);
    if(onp==NULL)
    {
        return SYSSTUSERR;
    }
	if (onp->on_objtype == OBJN_TY_DEV || onp->on_objtype == OBJN_TY_FIL)
    {
        onp->on_opercode=IOIF_CODE_IOCTRL;
        onp->on_buf=buf;
        
        onp->on_ioctrd=iocode;
        onp->on_acsflgs=flgs;
        return krlsve_ioctrl_device(onp);
    }
    return SYSSTUSERR;
}


sysstus_t krlsve_ioctrl_device(objnode_t* ondep)
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