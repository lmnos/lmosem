/**********************************************************
		体系结构初始化文件arch_x64_init.h
***********************************************************
				彭东 ＠ 2011.12.16.08.30
**********************************************************/
#ifndef _ARCH_X64_INIT_H
#define _ARCH_X64_INIT_H
PUBLIC LKETY64 void init_page64();
PUBLIC LKINIT void lmos_x86_64_arch_init_main(kinitrfun_t* kirfdata);
PUBLIC LKETY64 void set_cr3(u64_t pl4adr);
PUBLIC void run_keybd();
PUBLIC void run_mouse();
#endif
