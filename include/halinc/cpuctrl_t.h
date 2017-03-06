/**********************************************************
        cpu控制头文件cpuctrl_t.h
***********************************************************
                彭东 ＠ 2013.06.24.11.45
**********************************************************/
#ifndef _CPUCTRL_T_H
#define _CPUCTRL_T_H

#define CPU_USR_MODE 0x10
#define CPU_FIQ_MODE 0x11
#define CPU_IRQ_MODE 0x12
#define CPU_SVE_MODE 0x13
#define CPU_ABT_MODE 0x17
#define CPU_UND_MODE 0x1b
#define CPU_SYS_MODE 0x1f

#define CFIQ 0x40
#define CIRQ 0x80
#define CIRQFIQ 0xc0


#endif // CPUCTRL_T_H
