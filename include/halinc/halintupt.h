/**********************************************************
        hal层中断处理头文件halintupt.h
***********************************************************
                彭东 ＠ 2013.07.15.16.10
**********************************************************/
#ifndef _HALINTUPT_H
#define _HALINTUPT_H
#ifdef CFG_S3C2440A_PLATFORM
void init_halintupt();
void init_intfltdsc(mach_t* machp);
void intfltdsc_t_init(intfltdsc_t* initp,u32_t flg,u32_t stus,u32_t pbitnr,uint_t irqnr);
void intserdsc_t_init(intserdsc_t* initp,u32_t flg,intfltdsc_t* intfltp,void* device,intflthandle_t handle);
intfltdsc_t* hal_retn_intfltdsc(uint_t ifdnr);
uint_t hal_retn_intnr();
bool_t hal_add_ihandle(intfltdsc_t* intdscp,intserdsc_t* serdscp);
drvstus_t hal_clear_intpnd(uint_t bitnr);
drvstus_t hal_clear_srcpnd(uint_t ifdnr);
drvstus_t hal_enable_intline(uint_t ifdnr);
drvstus_t hal_disable_intline(uint_t ifdnr);
drvstus_t hal_intflt_default(uint_t ift_nr,void* sframe);
#endif
#ifdef CFG_X86_PLATFORM
void intfltdsc_t_init(intfltdsc_t* initp,u32_t flg,u32_t sts,uint_t prity,uint_t irq);
void init_intfltdsc();
PUBLIC void init_halintupt();
PUBLIC intfltdsc_t* hal_retn_intfltdsc(uint_t irqnr);
void intserdsc_t_init(intserdsc_t* initp , u32_t flg,intfltdsc_t* intfltp,void* device,intflthandle_t handle);
bool_t hal_add_ihandle(intfltdsc_t* intdscp,intserdsc_t* serdscp);
drvstus_t hal_enable_intline(uint_t ifdnr);
drvstus_t hal_disable_intline(uint_t ifdnr);
drvstus_t hal_intflt_default(uint_t ift_nr,void* sframe);
#endif
#endif // HALINTUPT_H
