/**********************************************************
        LMOSEM内核服务文件krlsveclose.c
***********************************************************
                彭东 ＠ 2013.09.17.09.00
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

sysstus_t krlsvetabl_close(uint_t swinr,stkparame_t* stkparv)
{
    if(swinr!=SNR_FS_CLOSE)
    {
        return SYSSTUSERR;
    }
    return krlsve_close((hand_t)stkparv->parmv1);
}

sysstus_t krlsve_close(hand_t fhand)
{
    if(fhand<0||fhand>=TD_HAND_MAX)
    {
        return SYSSTUSERR;
    }
    return krlsve_core_close(fhand);
}

sysstus_t krlsve_core_close(hand_t fhand)
{
    thread_t* tdp=krlsched_retn_currthread();
    
    objnode_t* ondp=krlthd_retn_objnode(tdp,fhand);
    if(ondp==NULL)
    {
        return SYSSTUSERR;
    }
    if(ondp->on_objtype==OBJN_TY_DEV||ondp->on_objtype==OBJN_TY_FIL)
    {
        ondp->on_opercode=IOIF_CODE_CLOSE;
        goto cl_dev_step;
    }
    return SYSSTUSERR;
cl_dev_step:
    if(krlsve_close_device(ondp)==SYSSTUSERR)
    {
        return SYSSTUSERR;
    }
    
    if(krlthd_del_objnode(tdp,fhand)==NO_HAND)
    {
        hal_sysdie("close api td del objnode err");
    }
    
    if(krldel_objnode(ondp)==FALSE)
    {
        hal_sysdie("close api del objnode err");
    }
    
    return SYSSTUSOK;
}

sysstus_t krlsve_close_device(objnode_t* ondep)
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
