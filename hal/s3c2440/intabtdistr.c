/**********************************************************
        中断异常分配器文件intabtdistr.c
***********************************************************
                彭东 ＠ 2013.06.23.16.55
**********************************************************/

#include "lmosemtypes.h"
#include "lmosemmctrl.h"
__attribute__((section(".data"))) uint_t gint_indx=0;

void hal_dbug_print_reg(intstkregs_t* intstkp)
{
    printfk("USR_REG r0:%x\n\r",intstkp->r0);
    printfk("USR_REG r1:%x\n\r",intstkp->r1);
    printfk("USR_REG r2:%x\n\r",intstkp->r2);
    printfk("USR_REG r3:%x\n\r",intstkp->r3);
    printfk("USR_REG r4:%x\n\r",intstkp->r4);
    printfk("USR_REG r5:%x\n\r",intstkp->r5);
    printfk("USR_REG r6:%x\n\r",intstkp->r6);
    printfk("USR_REG r7:%x\n\r",intstkp->r7);
    printfk("USR_REG r8:%x\n\r",intstkp->r8);
    printfk("USR_REG r9:%x\n\r",intstkp->r9);
    printfk("USR_REG r10:%x\n\r",intstkp->r10);
    printfk("USR_REG r11:%x\n\r",intstkp->r11);
    printfk("USR_REG r12:%x\n\r",intstkp->r12);
    printfk("USR_REG r13:%x\n\r",intstkp->r13);
    printfk("USR_REG r14:%x\n\r",intstkp->r14);
    printfk("SVE_REG lr:%x\n\r",intstkp->s_lr);
    printfk("SVE_REG spsr:%x\n\r",intstkp->s_spsr);
    printfk("CSP_REG sp:%x INTPND:%x\n\r", hal_read_currmodesp(),hal_io32_read(INTPND_R));
    printfk("CCR_REG cpsr:%x INTOFST:%x\n\r",hal_read_cpuflg(),hal_retn_intnr());
    thread_t* prev=krlsched_retn_currthread();
    
    printfk("CURR_THREAD:%x CURR_THREAD_KSTKTOP:%x\n\r",(uint_t)prev,(uint_t)prev->td_krlstktop);

    return;
}

void hal_undefins_distr(void* sframe)
{
	hal_sysdie("undefins runing!! ");
    return;
}

sysstus_t hal_swi_distr(uint_t swinr,void* sframe)
{
    return krlservice(swinr,sframe);
}

void hal_prefabt_distr(void* sframe)
{
    printfk("CP15 c5:%x c6:%x\n\r",
    hal_read_cp15regs(CP15_C5R),hal_read_cp15regs(CP15_C6R));
    hal_dbug_print_reg((intstkregs_t*)sframe);
    hal_sysdie("pref abt runing!! ");
    return;
}

void hal_dataabt_distr(void* sframe)
{
    printfk("CP15 c5:%x c6:%x\n\r",
    hal_read_cp15regs(CP15_C5R),hal_read_cp15regs(CP15_C6R));
    hal_dbug_print_reg((intstkregs_t*)sframe);
    
    hal_sysdie("data abt runing!! ");
    return;
}

void hal_bugdie_distr(void* sframe)
{
    hal_sysdie("bug die runing!! ");
    return;
}

void hal_dbugint(uint_t lr)
{
    printfk("idbug enter..%x \n\r",lr);
    printfk("idbug enter..%x \n\r",lr);
    return;
}

void hal_dbugint2(uint_t lr)
{
    printfk("idbug exit..%x \n\r",lr);
    printfk("idbug exit..%x \n\r",lr);
    return;
}

void hal_irq_distr(void* sframe)
{
    uint_t intoset=hal_retn_intnr();
  
    switch(intoset)
    {
    
        case EINT4_7:
            hal_eint_distr(sframe,intoset,EI4_7_PNDBTS,EI4_7_PNDBTE);
            break;
        case EINT8_23:
            hal_eint_distr(sframe,intoset,EI8_23_PNDBTS,EI8_23_PNDBTE);
            break;    
        case INT_CAM:
            hal_sint_distr(sframe,intoset,ICAM_PNDBTS,ICAM_PNDBTE);
            break;
        case INT_WDT_AC97:
            hal_sint_distr(sframe,intoset,IACWDT_PNDBTS,IACWDT_PNDBTE);
            break;
        case INT_UART2:
            hal_sint_distr(sframe,intoset,IUART2_PNDBTS,IUART2_PNDBTE);
            break;
        
        case INT_UART1:
            hal_sint_distr(sframe,intoset,IUART1_PNDBTS,IUART1_PNDBTE);
            break;
        case INT_UART0:
            hal_sint_distr(sframe,intoset,IUART0_PNDBTS,IUART0_PNDBTE);
            break;    
        case INT_ADC:
            hal_sint_distr(sframe,intoset,IADC_PNDBTS,IADC_PNDBTE);
            break;
        default:
            hal_int_distr(sframe,intoset);
            break;    

    }
    
    hal_clear_intpnd(intoset);

    krlsched_chkneed_pmptsched();
    return;
}




void hal_frq_distr(void* sframe)
{
    
    hal_sysdie("frq runing!! ");
    return;
    
}


void hal_eint_distr(void* sframe,uint_t mintnr,uint_t pndbts,uint_t pndbte)
{
    u32_t pnd=hal_io32_read(EINTPEND_R);
    pnd&=EINTPEND_BITS_MASK;

    for(uint_t bi=pndbts;bi<pndbte;bi++)
    {
        if(((pnd>>bi)&1)==1)
        {
            hal_run_intflthandle(EINT_IFDNR(bi),sframe);
            hal_clear_srcpnd(EINT_IFDNR(bi));
        }
    }
    return;
}

void hal_sint_distr(void* sframe,uint_t mintnr,uint_t pndbts,uint_t pndbte)
{
    u32_t pnd=hal_io32_read(SUBSRCPND_R);
    pnd&=SUBSRCPND_BITS_MASK;

    for(uint_t bi=pndbts;bi<pndbte;bi++)
    {
        if(((pnd>>bi)&1)==1)
        {
            hal_run_intflthandle(SINT_IFDNR(bi),sframe);
            hal_clear_srcpnd(SINT_IFDNR(bi));
        }
    }
    return;
}

void hal_lcdint_distr(void* sframe,uint_t mintnr,uint_t pndbts,uint_t pndbte)
{
    u32_t pnd=hal_io32_read(LCDINTPND_R);
    pnd&=LCDSRCPND_BITS_MASK;

    for(uint_t bi=pndbts;bi<pndbte;bi++)
    {
        if(((pnd>>bi)&1)==1)
        {
            hal_run_intflthandle(SINT_IFDNR(bi),sframe);
        }
    }
    return;
}

void hal_int_distr(void* sframe,uint_t mintnr)
{
    
    hal_run_intflthandle(MINT_IFDNR(mintnr),sframe);
    hal_clear_srcpnd(MINT_IFDNR(mintnr));
    return; 
}


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