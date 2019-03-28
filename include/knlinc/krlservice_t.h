/**********************************************************
        LMOSEM内核服务头文件krlservice_t.h
***********************************************************
                彭东 ＠ 2013.09.17.11.30
**********************************************************/
#ifndef KRLSERVICE_T_H
#define KRLSERVICE_T_H

#define SNR_MM_ALLOC 0x1
#define SNR_MM_FREE 0x2
#define SNR_TD_EXEL 0x3
#define SNR_TD_EXIT 0x4
#define SNR_TD_HAND 0x5
#define SNR_TD_RSTATS 0x6
#define SNR_TD_SSTATS 0x7
#define SNR_FS_OPEN 0x8
#define SNR_FS_CLOSE 0x9
#define SNR_FS_READ 0xa
#define SNR_FS_WRITE 0xb
#define SNR_FS_IOCTRL 0xc
#define SNR_FS_LSEEK 0xd
#define SNR_TIME 0xe

#define SWINR_MAX 0xf

#define SYSSTUSERR (-1)
#define SYSSTUSOK (0)
#define FILE_TY_MASK 0xf
#define FILE_TY_FILE 0
#define FILE_TY_DEV 1
#define RWO_FLG_MASK 0xff
#define RWO_FLG_BITS 0x4
#define RW_FLG 0x3
#define RO_FLG 0x1
#define WO_FLG 0x2
#define NF_FLG 0x4


#ifdef CFG_S3C2440A_PLATFORM
typedef struct s_STKPARAME
{
    reg_t rvs0;    
    reg_t rvs1;
    reg_t parmv1;
    reg_t parmv2; 
    reg_t parmv3; 
    reg_t parmv4; 
    reg_t parmv5; 
    reg_t parmv6; 
    reg_t parmv7;     
}stkparame_t;
#endif
#ifdef CFG_X86_PLATFORM
/*
Push(EAX);
Push(ECX);
Push(EDX);
Push(EBX);
Push(Temp);
Push(EBP);
Push(ESI);
Push(EDI);
push    ds
push    es
push    fs
push    gs
*/
typedef struct s_STKPARAME
{
    reg_t rvsgs;    
    reg_t rvsfs;
    reg_t rvses;
    reg_t rvsds; 
    reg_t parmv7;//edi
    reg_t parmv6;//esi 
    reg_t parmv5;//ebp
    reg_t parmv4;//ebx
    reg_t parmv3;//edx 
    reg_t parmv2;//ecx  
    reg_t parmv1;//eax
    reg_t rvseip;    
    reg_t rvscs;
    reg_t rvseflags;
    reg_t rvsesp;
    reg_t rvsss;
}stkparame_t;
#endif

typedef sysstus_t (*syscall_t)(uint_t swinr,stkparame_t* stkparm);
#endif // KRLSERVICE_T_H
