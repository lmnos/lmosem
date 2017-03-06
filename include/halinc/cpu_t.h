/**********************************************************
        CPU相关的宏定义文件cpu_t.h
***********************************************************
                彭东 ＠ 2013.06.23.10.50
**********************************************************/
#ifndef _CPU_T_H
#define _CPU_T_H


#ifdef CFG_S3C2440A_PLATFORM
#define JMP_ADDR(addr) \
 __asm__ __volatile__("mov pc,%[PCADR] \n\t"::[PCADR] "r" (addr):"cc","memory")


typedef struct s_ARMREGS
{
    reg_t r0;
    reg_t r1;
    reg_t r2;
    reg_t r3;
    reg_t r4;
    reg_t r5;
    reg_t r6;
    reg_t r7;
    reg_t r8;
    reg_t r9;
    reg_t r10;
    reg_t r11;
    reg_t r12;
    reg_t r13;
    reg_t r14;
}armregs_t;

typedef struct s_INTSTKREGS
{
    reg_t s_spsr;
	reg_t c_lr;
    reg_t r0;
    reg_t r1;
    reg_t r2;
    reg_t r3;
    reg_t r4;
    reg_t r5;
    reg_t r6;
    reg_t r7;
    reg_t r8;
    reg_t r9;
    reg_t r10;
    reg_t r11;
    reg_t r12;
    reg_t r13;
    reg_t r14;
    reg_t s_lr;
}intstkregs_t;
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
    pop     gs
    pop     fs
    pop     es
    pop     ds
    pop     edi
    pop     esi
    pop     ebp
    pop     ebx
    pop     edx
    pop     ecx
    pop     eax
    iretd

    u32_t r_gs;     //+0//pop gs            
    u32_t r_fs;     //+4     
    u32_t r_es;     //+8
    u32_t r_ds;     //+12
    u32_t r_edi;        //+16
    u32_t r_esi;        //+20
    u32_t r_ebp;        //+24
    u32_t r_temp;       //+28
    u32_t r_ebx;        //+32
    u32_t r_edx;        //+36
    u32_t r_ecx;        //+40
    u32_t r_eax;        //+44
    u32_t r_eip_old;    //+48
    u32_t r_cs_old;     //+52
    u32_t r_flags_old;  //+56
    u32_t r_esp_old;    //+60
    u32_t r_ss_old;     //+64
*/
typedef struct s_INTSTKREGS
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
    ///u32_t r_eip_old;
    //u32_t r_cs_old;
    //u32_t r_flags_old;
    //u32_t r_esp_old;
    //u32_t r_ss_old;
}intstkregs_t;

#endif

#endif // CPU_T_H
