/****************************************************************
        LMOSEM kernel全局数据结构头文件krlglobal.h
*****************************************************************
                彭东 ＠ 2013.07.18.16.50
****************************************************************/
#ifndef _KRLGLOBAL_H
#define _KRLGLOBAL_H
#ifdef	KRLGOBAL_HEAD
#undef	KEXTERN
#define KEXTERN
#endif

KRL_DEFGLOB_VARIABLE(kmempool_t,oskmempool);
KRL_DEFGLOB_VARIABLE(schedclass_t,osschedcls);
KRL_DEFGLOB_VARIABLE(ktime_t,osktime);
KRL_DEFGLOB_VARIABLE(syscall_t,osscalltab)[SWINR_MAX];
KRL_DEFGLOB_VARIABLE(devtable_t,osdevtable);
KRL_DEFGLOB_VARIABLE(drventyexit_t,osdrvetytabl)[];
#endif // KRLGLOBAL_H
