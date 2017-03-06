/**********************************************************
		全局／中断描述符头文件gdtidt.h
***********************************************************
				彭东 ＠ 2011.12.01.12.30
**********************************************************/
#ifndef _GDTIDT_H
#define _GDTIDT_H
//#ifdef	GLOBAL_QUANJU_HERE
//#undef	EXTERN
//#define EXTERN
//#endif


void	exc_divide_error();
void	exc_single_step_exception();
void	exc_nmi();
void	exc_breakpoint_exception();
void	exc_overflow();
void	exc_bounds_check();
void	exc_inval_opcode();
void	exc_copr_not_available();
void	exc_double_fault();
void	exc_copr_seg_overrun();
void	exc_inval_tss();
void	exc_segment_not_present();
void	exc_stack_exception();
void	exc_general_protection();
void	exc_page_fault();
void	exc_copr_error();
void	exc_alignment_check();
void	exc_machine_check();
void	exc_simd_fault();
void	hxi_exc_general_intpfault();
void	hxi_hwint00();
void	hxi_hwint01();
void	hxi_hwint02();
void	hxi_hwint03();
void	hxi_hwint04();
void	hxi_hwint05();
void	hxi_hwint06();
void	hxi_hwint07();
void	hxi_hwint08();
void	hxi_hwint09();
void	hxi_hwint10();
void	hxi_hwint11();
void	hxi_hwint12();
void	hxi_hwint13();
void	hxi_hwint14();
void	hxi_hwint15();
void	hxi_hwint16();
void	hxi_hwint17();
void	hxi_hwint18();
void	hxi_hwint19();
void	hxi_hwint20();
void	hxi_hwint21();
void	hxi_hwint22();
void	hxi_hwint23();
void	hxi_apic_svr();
void	hxi_apic_ipi_schedul();
void	hxi_apic_timer();
void	hxi_apic_thermal();
void	hxi_apic_performonitor();
void	hxi_apic_lint0();
void	hxi_apic_lint1();
void	hxi_apic_error();
void	exi_sys_call();
void	_ret_from_user_mode();

/*
EXTERN DESCRIPTOR GDT[CPU_MAX_NRS][GDTMAX];
EXTERN GATE IDT[IDTMAX];
EXTERN tss_t tss[CPU_MAX_NRS];
EXTERN IGDTR iGDT[CPU_MAX_NRS];
EXTERN IIDTR iIDT;
EXTERN syscall_t syscalls_table[2];
EXTERN sys_msg_oper_t sys_msg_op_table;
EXTERN irq_desc_t irq_desc[IRQMAX];
EXTERN struct s_TIME sys_clock;
EXTERN u32_t kernel_kesp;

EXTERN spinlock_t ap_boot_esp_lock;
EXTERN volatile u8_t xapic_to_cpuid[258];

EXTERN k_mmadr_t sys_kmadr;
EXTERN kmcache_t main_kmcache;
EXTERN iocachmtbl_t io_cach_tbl;
EXTERN u8_t kernel_stack[STACKMAX];
//EXTERN char str_buf[1024];
EXTERN smp_mach_t smp_mach_data;

EXTERN struct s_SCHED_MCHEAD sys_sched_mchead;//[CPU_MAX_NRS];
EXTERN gfs_t sys_gfs;
EXTERN dev_class_t devclasstbl[DEVCLASSMAX];
EXTERN intctrlop_t glob_pic_op;
EXTERN hd_reqb_t glob_hdreqb;
EXTERN setup_t sys_setup;
*/
PUBLIC void init_descriptor();
PUBLIC  void init_idt_descriptor();
//PUBLIC void die(u32_t dt);

PUBLIC void set_idt_desc(u8_t vector, u8_t desc_type, inthandler_t handler, u8_t privilege);

PUBLIC void set_igdtr(DESCRIPTOR* gdtptr);

PUBLIC void set_iidtr(GATE* idtptr);

PUBLIC void set_descriptor(DESCRIPTOR * p_desc, u32_t base, u32_t limit, u16_t attribute);

#endif
//90
