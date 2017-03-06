/**********************************************************
		全局／中断描述符头文件gdtidt.h
***********************************************************
				彭东 ＠ 2011.12.01.12.30
**********************************************************/
#ifndef _GDTIDT_T_H
#define _GDTIDT_T_H
#ifdef	GLOBAL_QUANJU_HERE
#undef	EXTERN
#define EXTERN
#endif
#define DEVCLASSMAX 256
#define GDTMAX 10
#define IDTMAX 256
#define STACKMAX 0x400


#define K_CS_IDX	0x08
#define K_DS_IDX	0x10
#define U_CS_IDX	0x1b
#define U_DS_IDX	0x23
#define K_TAR_IDX	0x28
#define UMOD_EFLAGS	0x1202


/* 存储段描述符/系统段描述符 */
typedef struct s_descriptor		/* 共 8 个字节 */
{
	u16_t	limit_low;		/* Limit */
	u16_t	base_low;		/* Base */
	u8_t	base_mid;		/* Base */
	u8_t	attr1;			/* P(1) DPL(2) DT(1) TYPE(4) */
	u8_t	limit_high_attr2;	/* G(1) D(1) 0(1) AVL(1) LimitHigh(4) */
	u8_t	base_high;		/* Base */
}__attribute__((packed)) DESCRIPTOR;
/* 门描述符 */
typedef struct s_gate
{
	u16_t	offset_low;	/* Offset Low */
	u16_t	selector;	/* Selector */
	u8_t	dcount;		/* 该字段只在调用门描述符中有效。如果在利用
				   调用门调用子程序时引起特权级的转换和堆栈
				   的改变，需要将外层堆栈中的参数复制到内层
				   堆栈。该双字计数字段就是用于说明这种情况
				   发生时，要复制的双字参数的数量。*/
	u8_t	attr;		/* P(1) DPL(2) DT(1) TYPE(4) */
	u16_t	offset_high;	/* Offset High */
}__attribute__((packed)) GATE;

typedef struct s_gdtptr
{
	u16_t gdtLen;
	u32_t gdtbass;
}__attribute__((packed)) IGDTR;

typedef struct s_idtptr
{
	u16_t idtLen;
	u32_t idtbass;
}__attribute__((packed)) IIDTR;

typedef struct s_TSS{
	u32_t	backlink;
	u32_t	esp0;		/* stack pointer to use during interrupt */
	u32_t	ss0;		/*   "   segment  "  "    "        "     */
	u32_t	esp1;
	u32_t	ss1;
	u32_t	esp2;
	u32_t	ss2;
	u32_t	cr3;
	u32_t	eip;
	u32_t	flags;
	u32_t	eax;
	u32_t	ecx;
	u32_t	edx;
	u32_t	ebx;
	u32_t	esp;
	u32_t	ebp;
	u32_t	esi;
	u32_t	edi;
	u32_t	es;
	u32_t	cs;
	u32_t	ss;
	u32_t	ds;
	u32_t	fs;
	u32_t	gs;
	u32_t	ldt;
	u16_t	trap;
	u16_t	iobase;	/* I/O位图基址大于或等于TSS段界限，就表示没有I/O许可位图 */
	/*u8	iomap[2];*/
}__attribute__((packed)) tss_t;

typedef struct s_DEV_CLASS
{
	spinlock_t dvcs_lock;
	list_h_t dvcs_list;
	u32_t dvcs_flags;
	void* dvcs_devtbl;
	void* dvcs_otherdata;
}dev_class_t;



/* GDT */
/* 描述符索引 */
#define	PRIVILEGE_KRNL	0
#define	PRIVILEGE_TASK	1
#define	PRIVILEGE_USER	3
/* RPL */
#define	RPL_KRNL	SA_RPL0
#define	RPL_TASK	SA_RPL1
#define	RPL_USER	SA_RPL3

#define	INDEX_DUMMY		0	// ┓
#define	INDEX_FLAT_C		1	// ┣ LOADER 里面已经确定了的.
#define	INDEX_FLAT_RW		2	// ┃
#define	INDEX_VIDEO		3	// ┛
/* 选择子 */
#define	SELECTOR_DUMMY		   0		// ┓
#define	SELECTOR_FLAT_C	0x08		// ┣ LOADER 里面已经确定了的.
#define	SELECTOR_FLAT_RW	0x10		// ┃
#define	SELECTOR_VIDEO		(0x18+3)	// ┛<-- RPL=3

#define	SELECTOR_KERNEL_CS	SELECTOR_FLAT_C
#define	SELECTOR_KERNEL_DS	SELECTOR_FLAT_RW


/* 描述符类型值说明 */
#define	DA_32			0x4000	/* 32 位段				*/
#define	DA_LIMIT_4K		0x8000	/* 段界限粒度为 4K 字节			*/
#define	DA_DPL0			0x00	/* DPL = 0				*/
#define	DA_DPL1			0x20	/* DPL = 1				*/
#define	DA_DPL2			0x40	/* DPL = 2				*/
#define	DA_DPL3			0x60	/* DPL = 3				*/
/* 存储段描述符类型值说明 */
#define	DA_DR			0x90	/* 存在的只读数据段类型值		*/
#define	DA_DRW			0x92	/* 存在的可读写数据段属性值		*/
#define	DA_DRWA			0x93	/* 存在的已访问可读写数据段类型值	*/
#define	DA_C			0x98	/* 存在的只执行代码段属性值		*/
#define	DA_CR			0x9A	/* 存在的可执行可读代码段属性值		*/
#define	DA_CCO			0x9C	/* 存在的只执行一致代码段属性值		*/
#define	DA_CCOR			0x9E	/* 存在的可执行可读一致代码段属性值	*/
/* 系统段描述符类型值说明 */
#define	DA_LDT			0x82	/* 局部描述符表段类型值			*/
#define	DA_TaskGate		0x85	/* 任务门类型值				*/
#define	DA_386TSS		0x89	/* 可用 386 任务状态段类型值		*/
#define	DA_386CGate		0x8C	/* 386 调用门类型值			*/
#define	DA_386IGate		0x8E	/* 386 中断门类型值			*/
#define	DA_386TGate		0x8F	/* 386 陷阱门类型值			*/

/* 中断向量 */
#define	INT_VECTOR_DIVIDE		0x0
#define	INT_VECTOR_DEBUG		0x1
#define	INT_VECTOR_NMI			0x2
#define	INT_VECTOR_BREAKPOINT		0x3
#define	INT_VECTOR_OVERFLOW		0x4
#define	INT_VECTOR_BOUNDS		0x5
#define	INT_VECTOR_INVAL_OP		0x6
#define	INT_VECTOR_COPROC_NOT		0x7
#define	INT_VECTOR_DOUBLE_FAULT	0x8
#define	INT_VECTOR_COPROC_SEG		0x9
#define	INT_VECTOR_INVAL_TSS		0xA
#define	INT_VECTOR_SEG_NOT		0xB
#define	INT_VECTOR_STACK_FAULT		0xC
#define	INT_VECTOR_PROTECTION		0xD
#define	INT_VECTOR_PAGE_FAULT		0xE
#define	INT_VECTOR_COPROC_ERR		0x10
#define	INT_VECTOR_ALIGN_CHEK		0x11
#define	INT_VECTOR_MACHI_CHEK		0x12
#define	INT_VECTOR_SIMD_FAULT		0x13

/* 中断向量 */
#define	INT_VECTOR_IRQ0			0x20
#define	INT_VECTOR_IRQ8			0x28

#define INT_VECTOR_APIC_IPI_SCHEDUL     0xe0
#define	INT_VECTOR_APIC_SVR		0xef
#define INT_VECTOR_APIC_TIMER		0xf0
#define INT_VECTOR_APIC_THERMAL		0xf1
#define INT_VECTOR_APIC_PERFORM		0xf2
#define INT_VECTOR_APIC_LINTO		0xf3
#define INT_VECTOR_APIC_LINTI		0xf4
#define INT_VECTOR_APIC_ERROR		0xf5

#define INT_VECTOR_SYSCALL		0xFF

#endif
//90
