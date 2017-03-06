/**********************************************************
        LMOSEM内核服务文件krlsveread.c
***********************************************************
                彭东 ＠ 2013.09.17.09.00
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

sysstus_t krlsvetabl_read(uint_t swinr,stkparame_t* stkparv)
{
    if(swinr!=SNR_FS_READ)
    {
        return SYSSTUSERR;
    }
    return krlsve_read((hand_t)stkparv->parmv1,(buf_t)stkparv->parmv2,
    (size_t)stkparv->parmv3,(uint_t)stkparv->parmv4);
}

sysstus_t krlsve_read(hand_t fhand,buf_t buf,size_t len,uint_t flgs)
{
    if(fhand==NO_HAND||buf==NULL||len<1)
    {
        return SYSSTUSERR;
    }
    
    return krlsve_core_read(fhand,buf,len,flgs);
}

sysstus_t krlsve_core_read(hand_t fhand,buf_t buf,size_t len,uint_t flgs)
{
    thread_t* currtd=krlsched_retn_currthread();
    objnode_t* onp=krlthd_retn_objnode(currtd,fhand);
    if(onp==NULL)
    {
        return SYSSTUSERR;
    }
    if(onp->on_objtype==OBJN_TY_DEV||onp->on_objtype==OBJN_TY_FIL)
    {
        onp->on_opercode=IOIF_CODE_READ;
        onp->on_buf=buf;
        onp->on_len=len;
        onp->on_bufsz=0x1000;
        onp->on_acsflgs=flgs;
        return krlsve_read_device(onp);
    }
    return SYSSTUSERR;
}

sysstus_t krlsve_read_device(objnode_t* ondep)
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
