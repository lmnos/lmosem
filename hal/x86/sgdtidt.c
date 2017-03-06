/**********************************************************
		设置全局／中断描述符文件sgdtidt.c　　　
***********************************************************
				彭东 ＠ 2011.12.04.17.30　
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"



PUBLIC LKINIT void set_idt_desc(u8_t vector, u8_t desc_type, inthandler_t handler, u8_t privilege)
{
	//if(vector>IDTMAX-1)
	//	error_set(&error,IDT_ERR);
	GATE *	p_gate	= &IDT[vector];
	u32_t	base	= (u32_t)handler;
	p_gate->offset_low	= base & 0xFFFF;
	p_gate->selector	= SELECTOR_KERNEL_CS;
	p_gate->dcount		= 0;
	p_gate->attr		= (u8_t)(desc_type | (privilege << 5));
	p_gate->offset_high	=(u16_t)((base >> 16) & 0xFFFF) ;
        return;
}


/*======================================================================*
                           seg2phys
 *----------------------------------------------------------------------*
 由段名求绝对地址
 *======================================================================*/
/*public u32_t seg2phys(u16_t seg)
{
	DESCRIPTOR* p_dest = &QuanJMSF[seg >> 3];

	return (p_dest->base_high << 24) | (p_dest->base_mid << 16) | (p_dest->base_low);
}

======================================================================*
                           init_descriptor
 *----------------------------------------------------------------------*
 初始化段描述符
 *======================================================================*/
PUBLIC LKINIT void set_igdtr(DESCRIPTOR* gdtptr)
{
	if(gdtptr==NULL)
		system_error("set_igtr gdtptr NULL\n");
        //iGDT.gdtbass = (u32_t)gdtptr;
      //  iGDT.gdtLen = sizeof(GDT)-1;
        return;
}

PUBLIC LKINIT void set_iidtr(GATE* idtptr)
{
	if(idtptr==NULL)
		system_error("set_iidtr idtptr NULL\n");
	iIDT.idtbass = (u32_t)idtptr;
	iIDT.idtLen  = sizeof(IDT)-1;
	return;
}

PUBLIC LKINIT void set_descriptor(DESCRIPTOR * p_desc, u32_t base, u32_t limit, u16_t attribute)
{
	//if(base !=0 && limit !=0xffffffff)
	//	error_set(&error,GDT_ERR);
	p_desc->limit_low		= limit & 0x0FFFF;		// 段界限 1(2 字节)
	p_desc->base_low		= base & 0x0FFFF;		// 段基址 1(2 字节)
	p_desc->base_mid		= (base >> 16) & 0x0FF;		// 段基址 2(1 字节)
	p_desc->attr1			= (u8_t)(attribute & 0xFF);		// 属性 1
	p_desc->limit_high_attr2	= (u8_t)(((limit >> 16) & 0x0F)|((attribute >> 8) & 0xF0));// 段界限 2 + 属性 2
	p_desc->base_high		= (u8_t)((base >> 24) & 0x0FF);		// 段基址 3\(1 字节)
        return;
}

PUBLIC LKINIT void init_descriptor()
{
	for(u32_t gdtindx=0;gdtindx<CPUCORE_MAX;gdtindx++)
	{
	
		set_descriptor(&GDT[gdtindx][0],0,0,0);//0
		set_descriptor(&GDT[gdtindx][1],0,0xffffffff,DA_CR|  DA_32|DA_LIMIT_4K);//0x8
		set_descriptor(&GDT[gdtindx][2],0,0xffffffff,DA_DRW | DA_32|DA_LIMIT_4K);//0x10
		set_descriptor(&GDT[gdtindx][3],0,0xffffffff,DA_CR | DA_32|DA_LIMIT_4K|DA_DPL3);//0x1b 0,0xffffffff,DA_DRW | DA_32|DA_LIMIT_4K);

		set_descriptor(&GDT[gdtindx][4],0,0xffffffff,DA_DRW | DA_32|DA_LIMIT_4K|DA_DPL3);//0x23

		set_descriptor(&GDT[gdtindx][5],(u32_t)&tss[gdtindx],sizeof(tss[gdtindx])-1,DA_386TSS);
		set_descriptor(&GDT[gdtindx][6],0,0xffff,DA_C);
		
		iGDT[gdtindx].gdtbass = (u32_t)GDT[gdtindx];
		iGDT[gdtindx].gdtLen = sizeof(GDT[gdtindx])-1;
	}

	//set_igdtr(GDT[0]);
	x86_lgdt(&iGDT[0]);
	x86_ltr(K_TAR_IDX);
	//printf("                       init GDT LTR descriptor!!");
	//printf("init IDT oooooooooGATE!!\n");	
	//for(;;);
	return;
}
PUBLIC LKINIT void init_idt_descriptor()
{
	for(u16_t intindx =0;intindx<=255;intindx++)
	{	
		//if(intindx==0x20)
	//		intindx=INT_VECTOR_IRQ8+8;
		set_idt_desc((u8_t)intindx,DA_386IGate,hxi_exc_general_intpfault,PRIVILEGE_KRNL);
	}
	set_idt_desc(INT_VECTOR_DIVIDE,DA_386IGate,exc_divide_error,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_DEBUG,DA_386IGate,exc_single_step_exception,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_NMI,DA_386IGate,exc_nmi,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_BREAKPOINT,DA_386IGate,exc_breakpoint_exception,PRIVILEGE_USER);

	set_idt_desc(INT_VECTOR_OVERFLOW,DA_386IGate,exc_overflow,PRIVILEGE_USER);

	set_idt_desc(INT_VECTOR_BOUNDS,DA_386IGate,exc_bounds_check,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_INVAL_OP,DA_386IGate,exc_inval_opcode,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_COPROC_NOT,DA_386IGate,exc_copr_not_available,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_DOUBLE_FAULT,DA_386IGate,exc_double_fault,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_COPROC_SEG,DA_386IGate,exc_copr_seg_overrun,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_INVAL_TSS,DA_386IGate,exc_inval_tss,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_SEG_NOT,DA_386IGate,exc_segment_not_present,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_STACK_FAULT,DA_386IGate,exc_stack_exception,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_PROTECTION,DA_386IGate,exc_general_protection,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_PAGE_FAULT,DA_386IGate,exc_page_fault,PRIVILEGE_KRNL);

	//set_idt_desc(15,DA_386IGate,hxi_exc_general_intpfault,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_COPROC_ERR,DA_386IGate,exc_copr_error,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_ALIGN_CHEK,DA_386IGate,exc_alignment_check,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_MACHI_CHEK,DA_386IGate,exc_machine_check,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_SIMD_FAULT,DA_386IGate,exc_simd_fault,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ0 + 0,DA_386IGate,hxi_hwint00,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ0 + 1,DA_386IGate,hxi_hwint01,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ0 + 2,DA_386IGate,hxi_hwint02,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ0 + 3,DA_386IGate,hxi_hwint03,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ0 + 4,DA_386IGate,hxi_hwint04,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ0 + 5,DA_386IGate,hxi_hwint05,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ0 + 6,DA_386IGate,hxi_hwint06,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ0 + 7,DA_386IGate,hxi_hwint07,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ8 + 0,DA_386IGate,hxi_hwint08,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ8 + 1,DA_386IGate,hxi_hwint09,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ8 + 2,DA_386IGate,hxi_hwint10,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ8 + 3,DA_386IGate,hxi_hwint11,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ8 + 4,DA_386IGate,hxi_hwint12,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ8 + 5,DA_386IGate,hxi_hwint13,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ8 + 6,DA_386IGate,hxi_hwint14,PRIVILEGE_KRNL);

	set_idt_desc(INT_VECTOR_IRQ8 + 7,DA_386IGate,hxi_hwint15,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_IRQ8 + 8,DA_386IGate,hxi_hwint16,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_IRQ8 + 9,DA_386IGate,hxi_hwint17,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_IRQ8 + 10,DA_386IGate,hxi_hwint18,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_IRQ8 + 11,DA_386IGate,hxi_hwint19,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_IRQ8 + 12,DA_386IGate,hxi_hwint20,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_IRQ8 + 13,DA_386IGate,hxi_hwint21,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_IRQ8 + 14,DA_386IGate,hxi_hwint22,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_IRQ8 + 15,DA_386IGate,hxi_hwint23,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_APIC_IPI_SCHEDUL,DA_386IGate,hxi_apic_ipi_schedul,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_APIC_SVR,DA_386IGate,hxi_apic_svr,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_APIC_TIMER,DA_386IGate,hxi_apic_timer,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_APIC_THERMAL,DA_386IGate,hxi_apic_thermal,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_APIC_PERFORM,DA_386IGate,hxi_apic_performonitor,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_APIC_LINTO,DA_386IGate,hxi_apic_lint0,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_APIC_LINTI,DA_386IGate,hxi_apic_lint1,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_APIC_ERROR,DA_386IGate,hxi_apic_error,PRIVILEGE_KRNL);
	
	set_idt_desc(INT_VECTOR_SYSCALL,DA_386IGate,exi_sys_call,PRIVILEGE_USER);
		
	set_iidtr(IDT);
	x86_lidt(&iIDT);
	//printf(" init IDT GATE!!\n");	
	return;
}


/*#pragma GCC push_options
#pragma GCC optimize ("O0")
PUBLIC  void die(u32_t dt) 
{
	
	u32_t dttt=dt,dtt=dt;
	if(dt==0)
	{
		for(;;);
	}
	
	for(u32_t i=0;i<dt;i++)
	{
		for(u32_t j=0;j<dtt;j++)
		{
			for(u32_t k=0;k<dttt;k++)
			{
				;
			}
		}
	}
	
	
	
	return;
}
#pragma GCC pop_options 
*/