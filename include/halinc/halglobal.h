/****************************************************************
        LMOSEM HAL全局数据结构头文件halglobal.h
*****************************************************************
                彭东 ＠ 2013.07.01.10.00
****************************************************************/
#ifndef _HALGLOBAL_H
#define _HALGLOBAL_H
#ifdef	HALGOBAL_HEAD
#undef	EXTERN
#define EXTERN
#endif
#ifdef CFG_S3C2440A_PLATFORM
HAL_DEFGLOB_VARIABLE(mach_t,osmach);
HAL_DEFGLOB_VARIABLE(phymem_t,osphymem);

HAL_DEFGLOB_VARIABLE(phyadrspce_t,machadrspce)[PLFM_ADRSPCE_NR];
HAL_DEFGLOB_VARIABLE(intfltdsc_t,machintflt)[IRQ_MAX];
#endif

#ifdef CFG_X86_PLATFORM
HAL_DEFGLOB_VARIABLE(DESCRIPTOR,GDT)[CPUCORE_MAX][GDTMAX];
HAL_DEFGLOB_VARIABLE(GATE,IDT)[IDTMAX];
HAL_DEFGLOB_VARIABLE(tss_t,tss)[CPUCORE_MAX]; 
HAL_DEFGLOB_VARIABLE(IGDTR,iGDT)[CPUCORE_MAX];
HAL_DEFGLOB_VARIABLE(IIDTR,iIDT);
HAL_DEFGLOB_VARIABLE(machbstart_t,kmachbsp);
HAL_DEFGLOB_VARIABLE(dftgraph_t,kdftgh);
HAL_DEFGLOB_VARIABLE(memmgrob_t,lmos_memmgrob);
HAL_DEFGLOB_VARIABLE(intfltdsc_t,machintflt)[IDTMAX];
#endif
void die(u32_t dt);
#endif // HALGLOBAL_H
