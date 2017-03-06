/**********************************************************
        内核层内存管理头文件krlmm.h
***********************************************************
                彭东 ＠ 2013.07.18.15.00
**********************************************************/
#ifndef _KRLMM_H
#define _KRLMM_H
void init_krlmm();

adr_t krlnew(size_t mmsize);

bool_t krldelete(adr_t fradr,size_t frsz);
#endif // _KRLMM_H
