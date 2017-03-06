/**********************************************************
		中断总分配器源文件intallocator.c
***********************************************************
				彭东 ＠ 2011.12.21.10.20
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"
void hal_run_intflthandle(uint_t ifdnr,void* sframe)
{
    intserdsc_t* isdscp;
    list_h_t* lst;
    intfltdsc_t* ifdscp=hal_retn_intfltdsc(ifdnr);
    if(ifdscp==NULL)
    {
        hal_sysdie("hal_run_intfdsc err");
        return;
    }

    list_for_each(lst,&ifdscp->i_serlist)
    {
        isdscp=list_entry(lst,intserdsc_t,s_list);
        isdscp->s_handle(ifdnr,isdscp->s_device,sframe);
    }
    
    return;
}

PUBLIC void lmosem_do_hwint(uint_t intnumb,void* krnlsframp)
{
	intfltdsc_t* ifdscp=NULL;
	cpuflg_t cpuflg;
	if(intnumb>IDTMAX||krnlsframp==NULL)
	{
		system_error("lmosem_do_hwint fail\n");
		return;
	}
	ifdscp=hal_retn_intfltdsc(intnumb);
	if(ifdscp==NULL)
	{
		system_error("lmosem_do_hwint ifdscp NULL\n");
		return;
	}
	hal_spinlock_saveflg_cli(&ifdscp->i_lock,&cpuflg);
	ifdscp->i_indx++;
	ifdscp->i_deep++;
	hal_run_intflthandle(intnumb,krnlsframp);
	//kprint("hwint run irq:%d prity:%d conut:%d\n",ifdscp->i_irqnr,ifdscp->i_prity,(uint_t)ifdscp->i_indx);
	ifdscp->i_deep--;
	hal_spinunlock_restflg_sti(&ifdscp->i_lock,&cpuflg);
	return;
}

PUBLIC FAUTCALL void lmosem_fault_allocator(uint_t faultnumb,void* krnlsframp) //eax,edx
{
	kprint("faultnumb:%x\n",faultnumb);
	for(;;);
	return;
}


PUBLIC SYSRCALL sysstus_t lmosem_syscl_allocator(uint_t sys_nr,void* msgp)
{
	return krlservice(sys_nr,msgp);
}

PUBLIC HINTCALL void lmosem_hwint_allocator(uint_t intnumb,void* krnlsframp) //eax,edx
{
	i8259_send_eoi();
	lmosem_do_hwint(intnumb,krnlsframp);
	krlsched_chkneed_pmptsched();
	//kprint("暂时无法向任何服务进程发送中断消息,直接丢弃......\n");
	return;
}



/*PUBLIC void save_interrupt(u32_t* intflags)
{
	//flags,
	u32_t intftmp;
	u8_t altmp  = in_u8(_INTM_CTLMASK);
	
	intftmp=altmp;
	altmp = in_u8(_INTS_CTLMASK);
	intftmp=(intftmp<<8)|altmp;
	*intflags=intftmp;
	return;
}

PUBLIC void restore_interrupt(u32_t* intflags)
{
	u32_t intftmp=*intflags;
	
	u8_t altmp=(intftmp&0xff);
	out_u8_p(_INTS_CTLMASK,altmp);
	altmp=(u8_t)(intftmp>>8); 
	out_u8_p(_INTM_CTLMASK,altmp);
	return;
}

PUBLIC void irq_mask(u8_t int_nr)
{
	u32_t flags;
	save_flags_cli(&flags);
        if(int_nr<8)
        {


                u8_t altmp  = in_u8(_INTM_CTLMASK);
            
                
                altmp|=(u8_t)(1<<int_nr);
                
                out_u8_p(_INTM_CTLMASK,altmp);
               // altmp=;
                out_u8_p(_INTM_CTL,_EOI);
        }
        else
        {
                u8_t astmp = in_u8(_INTS_CTLMASK);
                astmp|=(u8_t)(1<<(int_nr-8));
                out_u8_p(_INTS_CTLMASK,astmp);
                //astmp=_EOI;
                out_u8_p(_INTM_CTL,_EOI);
                out_u8_p(_INTS_CTL,_EOI);
        }
        restore_flags_sti(&flags);
        return;
}

PUBLIC void restore_irq_mask(u8_t int_nr)
{
	u32_t flags;
	save_flags_cli(&flags);
        if(int_nr<8)
        {
                u8_t amtmp=in_u8(_INTM_CTLMASK);
                amtmp&=(u8_t)(~(1<<int_nr));
                out_u8_p(_INTM_CTLMASK,amtmp);
        }
        else
        {
                u8_t astmp=in_u8(_INTS_CTLMASK);
                astmp&=(u8_t)(~(1<<(int_nr-8)));
                out_u8_p(_INTS_CTLMASK,astmp);
        }
        restore_flags_sti(&flags);
        return;
}*/
