/**********************************************************
        平台相关的宏定义文件platform.h
***********************************************************
                彭东 ＠ 2013.06.30.18.00
**********************************************************/
#ifndef _PLATFORM_H
#define _PLATFORM_H
void init_paltform();

#ifdef CFG_S3C2440A_PLATFORM
LKHEAD_T void s3c2440mmu_init();
LKHEAD_T void s3c2440mmu_invalid_dicache();
LKHEAD_T void s3c2440mmu_set_domain(u32_t domain);
LKHEAD_T void s3c2440mmu_set_tblbass(u32_t tblbphyadr);
LKHEAD_T void s3c2440mmu_enable();
LKHEAD_T void s3c2440vector_init();
LKHEAD_T void s3c2440vector_copy();
extern void vector();
#endif

#endif // PLATFORM_S3C2440_H
