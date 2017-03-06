/**********************************************************
        内核层中断处理头文件krlintupt.h
***********************************************************
                彭东 ＠ 2013.07.18.15.10
**********************************************************/
#ifndef _KRLINTUPT_H
#define _KRLINTUPT_H
//#ifdef CFG_S3C2440A_PLATFORM
intserdsc_t* krladd_irqhandle(void* device,intflthandle_t handle,uint_t phyiline);
drvstus_t krlenable_intline(uint_t ifdnr);
drvstus_t krldisable_intline(uint_t ifdnr);
//#endif
#endif // KRLINTUPT_H
