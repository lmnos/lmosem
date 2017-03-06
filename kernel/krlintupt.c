/**********************************************************
        内核层中断处理文件krlintupt.c
***********************************************************
                彭东 ＠ 2013.07.18.15.10
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"



intserdsc_t* krladd_irqhandle(void* device,intflthandle_t handle,uint_t phyiline)
{
    if(device==NULL||handle==NULL)
    {
        return NULL;
    }
    
    intfltdsc_t* intp=hal_retn_intfltdsc(phyiline);
    if(intp==NULL)
    {
        return NULL;    
    }
    intserdsc_t* serdscp=(intserdsc_t*)krlnew(sizeof(intserdsc_t));
    if(serdscp==NULL)
    {
        return NULL;
    }
    
    intserdsc_t_init(serdscp,0,intp,device,handle);

    if(hal_add_ihandle(intp,serdscp)==FALSE)
    {
        
        if(krldelete((adr_t)serdscp,sizeof(intserdsc_t))==FALSE)
        {
            hal_sysdie("krladd_irqhandle ERR");
        }
        return NULL;
    }
    
    return serdscp;
}


drvstus_t krlenable_intline(uint_t ifdnr)
{
    
    return hal_enable_intline(ifdnr);
}

drvstus_t krldisable_intline(uint_t ifdnr)
{
 
    return hal_disable_intline(ifdnr);

}





