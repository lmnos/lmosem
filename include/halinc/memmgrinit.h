/**********************************************************
        物理内存管理器初始化文件memmgrinit.h
***********************************************************
                彭东 ＠ 2014.02.09.18.00
**********************************************************/
#ifndef _MEMMGRINIT_H
#define _MEMMGRINIT_H
PUBLIC LKINIT void init_memmgr();
void disp_memmgrob();
PUBLIC void init_memmgrob();
PUBLIC void memmgrob_t_init(memmgrob_t* initp);
PUBLIC bool_t copy_pages_data(machbstart_t* mbsp);
PUBLIC bool_t copy_fvm_data(machbstart_t* mbsp,dftgraph_t* dgp);
PUBLIC void init_copy_pagesfvm();
#endif