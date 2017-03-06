/**********************************************************
        LMOSEM内存管理API头文件lapimm.h
***********************************************************
                彭东 ＠ 2013.09.15.13.30
**********************************************************/
#ifndef _LAPIMM_H
#define _LAPIMM_H
void* api_mallocblk(size_t blksz);
sysstus_t api_mfreeblk(void* fradr,size_t blksz);
void test_api();
#endif // LAPIMM_H
