/****************************************************************
        LMOSEM HAL板级体系初始化头文件halmach.h
*****************************************************************
                彭东 ＠ 2013.07.06.15.50
****************************************************************/
#ifndef _HALMACH_H
#define _HALMACH_H
#ifdef CFG_S3C2440A_PLATFORM
void init_halmach();
void mach_t_init(mach_t* initp);
#endif
#endif // HALINIT_H
