/**********************************************************
        cpu控制文件cpuctrl.c
***********************************************************
                彭东 ＠ 2013.06.24.11.40
**********************************************************/

#include "lmosemtypes.h"
#include "lmosemmctrl.h"

#ifdef CFG_S3C2440A_PLATFORM
void hal_disable_fiq()
{
    __asm__ __volatile__(
         "mrs r0,cpsr \n\t"
         "orr r0,r0,%[closefiq]\n\t"
         "msr cpsr,r0 \n\t"
         :
         : [closefiq] "I" (CFIQ)
         : "r0","cc","memory"
    );
    return;
}

void hal_enable_fiq()
{
    __asm__ __volatile__(
         "mrs r0,cpsr \n\t"
         "bic r0,r0,%[openfiq]\n\t"
         "msr cpsr,r0 \n\t"
         :
         : [openfiq] "I" (CFIQ)
         : "r0","cc","memory"
    );
    return;
}

void hal_disable_irq()
{
    __asm__ __volatile__(
         "mrs r0,cpsr \n\t"
         "orr r0,r0,%[closeirq]\n\t"
         "msr cpsr,r0 \n\t"
         :
         : [closeirq] "I" (CIRQ)
         : "r0","cc","memory"
    );
    return;
}
void hal_enable_irq()
{
    __asm__ __volatile__(
         "mrs r0,cpsr \n\t"
         "bic r0,r0,%[openirq]\n\t"
         "msr cpsr,r0 \n\t"
         :
         : [openirq] "I" (CIRQ)
         : "r0","cc","memory"
    );
    return;
}

void hal_disable_irqfiq()
{
    __asm__ __volatile__(
         "mrs r0,cpsr \n\t"
         "orr r0,r0,%[closeifiq]\n\t"
         "msr cpsr,r0 \n\t"
         :
         : [closeifiq] "I" (CIRQFIQ)
         : "r0","cc","memory"
    );
    return;
}
void hal_enable_irqfiq()
{
    __asm__ __volatile__(
         "mrs r0,cpsr \n\t"
         "bic r0,r0,%[openifiq]\n\t"
         "msr cpsr,r0 \n\t"
         :
         : [openifiq] "I" (CIRQFIQ)
         : "r0","cc","memory"
    );
    return;
}

void hal_disablefiq_savecpuflg(cpuflg_t* cpuflg)
{
    cpuflg_t tmpcpsr;

    __asm__ __volatile__(
         "mrs r7,cpsr \n\t"
         "mov %[tmpcpr],r7 \n\t"
         "orr r7,r7,%[closefiq] \n\t"
         "msr cpsr,r7 \n\t"
         : [tmpcpr] "=r" (tmpcpsr)
         : [closefiq] "I" (CFIQ)
         : "r7","cc","memory"
    );
    *cpuflg=tmpcpsr;
    return;
}

void hal_enablefiq_restcpuflg(cpuflg_t* cpuflg)
{
    __asm__ __volatile__(
         "msr cpsr,%[ordcpr] \n\t"
         :
         : [ordcpr] "r" (*cpuflg)
         : "cc","memory"
    );
    return;
}

void hal_disableirq_savecpuflg(cpuflg_t* cpuflg)
{
    cpuflg_t tmpcpsr;

    __asm__ __volatile__(
         "mrs r7,cpsr \n\t"
         "mov %[tmpcpr],r7 \n\t"
         "orr r7,r7,%[closeirq] \n\t"
         "msr cpsr,r7 \n\t"
         : [tmpcpr] "=r" (tmpcpsr)
         : [closeirq] "I" (CIRQ)
         : "r7","cc","memory"
    );
    *cpuflg=tmpcpsr;
    return;
}

void hal_enableirq_restcpuflg(cpuflg_t* cpuflg)
{
    __asm__ __volatile__(
         "msr cpsr,%[ordcpr] \n\t"
         :
         : [ordcpr] "r" (*cpuflg)
         : "cc","memory"
    );

    return;
}

void hal_disableirqfiq_savecpuflg(cpuflg_t* cpuflg)
{
    cpuflg_t tmpcpsr;

    __asm__ __volatile__(
         "mrs r7,cpsr \n\t"
         "mov %[tmpcpr],r7 \n\t"
         "orr r7,r7,%[closefirq] \n\t"
         "msr cpsr,r7 \n\t"
         : [tmpcpr] "=r" (tmpcpsr)
         : [closefirq] "I" (CIRQFIQ)
         : "r7","cc","memory"
    );
    *cpuflg=tmpcpsr;
    return;
}

void hal_enableirqfiq_restcpuflg(cpuflg_t* cpuflg)
{
    __asm__ __volatile__(
         "msr cpsr,%[ordcpr] \n\t"
         :
         : [ordcpr] "r" (*cpuflg)
         : "cc","memory"
    );
    return;
}

u32_t hal_read_currmodesp()
{
    u32_t tmpsp=0;
    __asm__ __volatile__(
         "mov %[retsp],sp \n\t"
         : [retsp] "=r" (tmpsp)
         :
         : "memory"
    );
    return tmpsp;
}

cpuflg_t hal_read_cpuflg()
{
    cpuflg_t cpuflg;
    __asm__ __volatile__(
         "mrs %[retcpr],cpsr \n\t"
         : [retcpr] "=r" (cpuflg)
         :
         : "cc","memory"
    );
    return cpuflg;
}

void hal_write_cpuflg(cpuflg_t cpuflg)
{
    __asm__ __volatile__(
         "msr cpsr,%[cpr] \n\t"
         :
         : [cpr] "r" (cpuflg)
         : "cc","memory"
    );
    return;
}

void hal_swhmodset_sp_rscurmod(uint_t cpumod,reg_t sp)
{
    cpuflg_t cufgtmp,cpufg=hal_read_cpuflg();
    cufgtmp=cpufg;
    cpufg&=(~0x1f);
    cpufg|=(cpuflg_t)cpumod;
    __asm__ __volatile__(
         "msr cpsr_c,%[cpr] \n\t"
         "mov sp,%[modsp] \n\t"
         "msr cpsr,%[odlmod] \n\t"
         :
         : [cpr] "r" (cpufg),[modsp] "r" (sp),[odlmod] "r" (cufgtmp)
         : "cc","memory"
    );
    
    
    return;
}

cpuflg_t hal_read_scpuflg()
{
    cpuflg_t scpuflg;
    __asm__ __volatile__(
         "mrs %[retscpr],spsr \n\t"
         : [retscpr] "=r" (scpuflg)
         :
         : "cc","memory"
    );
    return scpuflg;
}

void hal_write_scpuflg(cpuflg_t scpuflg)
{
    __asm__ __volatile__(
         "msr cpsr,%[cpr] \n\t"
         :
         : [cpr] "r" (scpuflg)
         : "cc","memory"
    );
    return;
}


void hal_cpumode_switch(uint_t mode)
{
    __asm__ __volatile__(
         "mrs r7,cpsr \n\t"
         "orr r7,r7,%[cmod] \n\t"
         "msr cpsr,r7 \n\t"
         :
         : [cmod] "r" (mode)
         : "r7","cc","memory"
    );
    return;
}

uint_t hal_cpumodeswitch_retoldmode(uint_t mode)
{
    uint_t oldmode;
    __asm__ __volatile__(
         "mrs r7,cpsr \n\t"
         "mov %[oldmod],r7 \n\t"
         "orr r7,r7,%[cmod] \n\t"
         "msr cpsr,r7 \n\t"
         : [oldmod] "=r"(oldmode)
         : [cmod] "r" (mode)
         : "r7","cc","memory"
    );
    return oldmode;
}

u8_t hal_io8_read(uint_t ioadr)
{
    u8_t retdata;

    __asm__ __volatile__(
         "ldrb %[retdta],[%[ioadrr]] \n\t"

         : [retdta] "=r"(retdata)
         : [ioadrr] "r" (ioadr)
         : "memory"
    );
    return retdata;
}

u16_t hal_io16_read(uint_t ioadr)
{
    u16_t retdata;

    __asm__ __volatile__(
         "ldrh %[retdta],[%[ioadrr]] \n\t"

         : [retdta] "=r"(retdata)
         : [ioadrr] "r" (ioadr)
         : "memory"
    );
    return retdata;
}

u32_t hal_io32_read(uint_t ioadr)
{
    u32_t retdata;

    __asm__ __volatile__(
         "ldr %[retdta],[%[ioadrr]] \n\t"

         : [retdta] "=r"(retdata)
         : [ioadrr] "r" (ioadr)
         : "memory"
    );
    return retdata;
}

void hal_io8_write(uint_t ioadr,u8_t val)
{

    __asm__ __volatile__(
         "strb %[valdta],[%[ioadrr]] \n\t"

         :
         : [valdta] "r"(val),[ioadrr] "r" (ioadr)
         : "memory"
    );

    return;
}

void hal_io16_write(uint_t ioadr,u16_t val)
{
    __asm__ __volatile__(
         "strh %[valdta],[%[ioadrr]] \n\t"

         :
         : [valdta] "r"(val),[ioadrr] "r" (ioadr)
         : "memory"
    );

    return;
}

void hal_io32_write(uint_t ioadr,u32_t val)
{
    __asm__ __volatile__(
         "str %[valdta],[%[ioadrr]] \n\t"

         :
         : [valdta] "r"(val),[ioadrr] "r" (ioadr)
         : "memory"
    );

    return;
}

void hal_spinlock_init(spinlock_t* lock)
{
    __asm__ __volatile__(
         "swp %[lockval],%[lockval],[%[lockadr]] \n\t"

         :
         : [lockval] "r"(0),[lockadr] "r" (&lock->lock)
         : "memory"
    );
    return;
}

void hal_spinlock_lock(spinlock_t* lock)
{
    __asm__ __volatile__(
         "mov r8,#1 \n\t"
         "1:swp r7,r8,[%[lockadr]] \n\t"
         "cmp r7,#0 \n\t"
         "bne 1b \n\t"
         :
         : [lockadr] "r" (&lock->lock)
         : "r7","r8","cc","memory"
    );
    return;
}

void hal_spinlock_unlock(spinlock_t* lock)
{
    __asm__ __volatile__(
         "swp %[lockval],%[lockval],[%[lockadr]] \n\t"

         :
         : [lockval] "r"(0),[lockadr] "r" (&lock->lock)
         : "memory"
    );
    return;
}

void hal_spinlock_saveflg_cli(spinlock_t* lock, cpuflg_t* cpuflg)
{
    cpuflg_t tmpcpsr;

    __asm__ __volatile__(
         "mrs r7,cpsr \n\t"
         "mov %[tmpcpr],r7 \n\t"
         "orr r7,r7,%[closefirq] \n\t"
         "msr cpsr,r7 \n\t"
         : [tmpcpr] "=r" (tmpcpsr)
         : [closefirq] "I" (CIRQFIQ)
         : "r7","cc","memory"
    );
    *cpuflg=tmpcpsr;
    __asm__ __volatile__(
         "mov r8,#1 \n\t"
         "1:swp r7,r8,[%[lockadr]] \n\t"
         "cmp r7,#0 \n\t"
         "bne 1b \n\t"
         :
         : [lockadr] "r" (&lock->lock)
         : "r7","r8","cc","memory"
    );
    return;
}

void hal_spinunlock_restflg_sti(spinlock_t* lock, cpuflg_t* cpuflg)
{
    __asm__ __volatile__(
         "swp %[lockval],%[lockval],[%[lockadr]] \n\t"

         :
         : [lockval] "r"(0),[lockadr] "r" (&lock->lock)
         : "memory"
    );

    __asm__ __volatile__(
         "msr cpsr,%[ordcpr] \n\t"
         :
         : [ordcpr] "r" (*cpuflg)
         : "cc","memory"
    );
    return;
}

#endif

void hal_spinlock_init(spinlock_t* lock)
{
    lock->lock = 0;
    return;
}

void hal_spinlock_lock(spinlock_t* lock)
{
    __asm__ __volatile__ (
    "1:         \n"
    "lock; xchg  %0, %1 \n"
    "cmpl   $0, %0      \n"
    "jnz    2f      \n"
    ".section .spinlock.text,""\"ax\"""\n"// 重新定义一个代码段所以jnz 2f下面并不是
    "2:         \n"     //cmpl $0,%1 事实上下面的代码不会常常执行,
    "cmpl   $0, %1      \n"     //这是为了不在cpu指令高速缓存中填充无用代码
    "jne    2b      \n"     //要知道那可是用每位6颗晶体管做的双极性静态
    "jmp    1b      \n"     //储存器,比内存条快几千个数量级
    ".previous      \n"
    :
    : "r"(1), "m"(*lock));
    return;
}

void hal_spinlock_unlock(spinlock_t* lock)
{
    __asm__ __volatile__(
    "movl   $0, %0\n"
    :
    : "m"(*lock));
    return;
}

void hal_spinlock_saveflg_cli(spinlock_t* lock, cpuflg_t* cpuflg)
{
    __asm__ __volatile__(
    "pushfl             \n\t"
    "cli                \n\t"
    "popl %0            \n\t"
    
    "1:                 \n\t"
    "lock; xchg  %1, %2 \n\t"
    "cmpl   $0,%1       \n\t"
    "jnz    2f          \n\t"
    ".section .spinlock.text,""\"ax\"""\n\t"//重新定义一个代码段所以jnz 2f下面并不是
    "2:                 \n\t"               //cmpl $0,%1 事实上下面的代码不会常常执行,
    "cmpl   $0,%2       \n\t"               //这是为了不在cpu指令高速缓存中填充无用代码
    "jne    2b          \n\t"       
    "jmp    1b          \n\t"     
    ".previous          \n\t"
    :"=m"(*cpuflg)
    : "r"(1), "m"(*lock));
    return;
}

void hal_spinunlock_restflg_sti(spinlock_t* lock, cpuflg_t* cpuflg)
{
    __asm__ __volatile__(
    "movl   $0, %0\n\t"
    "pushl %1 \n\t"
    "popfl \n\t"
    :
    : "m"(*lock), "m"(*cpuflg));
    return;
}



void knl_spinlock_init(spinlock_t* lock)
{
    lock->lock = 0;
    return;
}

void knl_spinlock_lock(spinlock_t* lock)
{
    __asm__ __volatile__ (
    "1:         \n"
    "lock; xchg  %0, %1 \n"
    "cmpl   $0, %0      \n"
    "jnz    2f      \n"
    ".section .spinlock.text,""\"ax\"""\n"// 重新定义一个代码段所以jnz 2f下面并不是
    "2:         \n"     //cmpl $0,%1 事实上下面的代码不会常常执行,
    "cmpl   $0, %1      \n"     //这是为了不在cpu指令高速缓存中填充无用代码
    "jne    2b      \n"     //要知道那可是用每位6颗晶体管做的双极性静态
    "jmp    1b      \n"     //储存器,比内存条快几千个数量级
    ".previous      \n"
    :
    : "r"(1), "m"(*lock));
    return;
}

void knl_spinlock_unlock(spinlock_t* lock)
{
    __asm__ __volatile__(
    "movl   $0, %0\n"
    :
    : "m"(*lock));
    return;
}

void knl_spinlock_cli(spinlock_t* lock, cpuflg_t* cpuflg)
{
    __asm__ __volatile__(
    "pushfl             \n\t"
    "cli                \n\t"
    "popl %0            \n\t"
    
    "1:                 \n\t"
    "lock; xchg  %1, %2 \n\t"
    "cmpl   $0,%1       \n\t"
    "jnz    2f          \n\t"
    ".section .spinlock.text,""\"ax\"""\n\t"//重新定义一个代码段所以jnz 2f下面并不是
    "2:                 \n\t"               //cmpl $0,%1 事实上下面的代码不会常常执行,
    "cmpl   $0,%2       \n\t"               //这是为了不在cpu指令高速缓存中填充无用代码
    "jne    2b          \n\t"       
    "jmp    1b          \n\t"     
    ".previous          \n\t"
    :"=m"(*cpuflg)
    : "r"(1), "m"(*lock));
    return;
}

void knl_spinunlock_sti(spinlock_t* lock, cpuflg_t* cpuflg)
{
    __asm__ __volatile__(
    "movl   $0, %0\n\t"
    "pushl %1 \n\t"
    "popfl \n\t"
    :
    : "m"(*lock), "m"(*cpuflg));
    return;
}


void hal_memset(void* setp,size_t n,u8_t setval)
{
    u8_t* _p=(u8_t*)setp;
    for(uint_t i=0;i<n;i++)
    {
        _p[i]=setval;
    }
    return;
}

void hal_memcpy(void* src,void* dst,size_t n)
{
    u8_t* _s=(u8_t*)src,*_d=(u8_t*)dst;
    for(uint_t i=0;i<n;i++)
    {
        _d[i]=_s[i];
    }
    return;
}

void hal_sysdie(char_t* errmsg)
{
    printfk("LMOSEM SYSTEM IS DIE %s",errmsg);
    for(;;);
    return;
}

void system_error(char_t* errmsg)
{
    hal_sysdie(errmsg);
    return;
}

uint_t hal_retn_cpuid()
{
    return 0;
}