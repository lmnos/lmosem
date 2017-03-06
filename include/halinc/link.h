/**********************************************************
		链接器输出头文件link.h
***********************************************************
				彭东 ＠ 2013.07.01.17.30
**********************************************************/
#ifndef _LINK_H
#define _LINK_H
extern char __begin_kernel;
extern char __begin_lmosem_hal_head_text;
extern char __end_lmosem_hal_head_text;
extern char __begin_lmosem_hal_head_data;
extern char __end_lmosem_hal_head_data;
extern char __begin_lmosem_hal_init;
extern char __end_lmosem_hal_init;
extern char __begin_lmosem_hal_vector;
extern char __end_lmosem_hal_vector;
extern char __begin_lmosem_hal_intvect;
extern char __end_lmosem_hal_intvect;
extern char __begin_text;
extern char __end_text;
extern char __begin_data;
extern char __end_data;
extern char __begin_rodata;
extern char __end_rodata;
extern char __begin_kstrtab;
extern char __end_kstrtab;
extern char __begin_bss;
extern char __end_bss;
extern char __end_kernel;

#endif // LINK_H







