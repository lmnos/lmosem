/**********************************************************
		中断总分配器头文件intallocator.h
***********************************************************
				彭东 ＠ 2011.12.21.10.20
**********************************************************/
#ifndef _INTALLOCATOR_H
#define _INTALLOCATOR_H
PUBLIC FAUTCALL void lmosem_fault_allocator(uint_t faultnumb,void* krnlsframp);
PUBLIC SYSRCALL sysstus_t lmosem_syscl_allocator(uint_t sys_nr,void* msgp);
PUBLIC HINTCALL void lmosem_hwint_allocator(uint_t intnumb,void* krnlsframp);
PUBLIC void irq_mask(u8_t int_nr);
PUBLIC void kfm_test();
PUBLIC void restore_irq_mask(u8_t int_nr);
PUBLIC void save_interrupt(u32_t* intflags);
PUBLIC void restore_interrupt(u32_t* intflags);
#endif
