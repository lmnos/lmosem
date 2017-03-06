/**********************************************************
        cpu控制头文件cpuctrl.h
***********************************************************
                彭东 ＠ 2013.06.24.11.45
**********************************************************/
#ifndef _CPUCTRL_H
#define _CPUCTRL_H

void hal_disable_fiq();
void hal_enable_fiq();
void hal_disable_irq();
void hal_enable_irq();
void hal_disable_irqfiq();
void hal_enable_irqfiq();
void hal_disablefiq_savecpuflg(cpuflg_t* cpuflg);
void hal_enablefiq_restcpuflg(cpuflg_t* cpuflg);
void hal_disableirq_savecpuflg(cpuflg_t* cpuflg);
void hal_enableirq_restcpuflg(cpuflg_t* cpuflg);
void hal_disableirqfiq_savecpuflg(cpuflg_t* cpuflg);
void hal_enableirqfiq_restcpuflg(cpuflg_t* cpuflg);
u32_t hal_read_currmodesp();
cpuflg_t hal_read_cpuflg();
void hal_write_cpuflg(cpuflg_t cpuflg);
void hal_swhmodset_sp_rscurmod(uint_t cpumod,reg_t sp);
cpuflg_t hal_read_scpuflg();
void hal_write_scpuflg(cpuflg_t scpuflg);
void hal_cpumode_switch(uint_t mode);
uint_t hal_cpumodeswitch_retoldmode(uint_t mode);
u8_t hal_io8_read(uint_t ioadr);
u16_t hal_io16_read(uint_t ioadr);
u32_t hal_io32_read(uint_t ioadr);
void hal_io8_write(uint_t ioadr,u8_t val);
void hal_io16_write(uint_t ioadr,u16_t val);
void hal_io32_write(uint_t ioadr,u32_t val);
void hal_spinlock_init(spinlock_t* lock);
void hal_spinlock_lock(spinlock_t* lock);
void hal_spinlock_unlock(spinlock_t* lock);
void hal_spinlock_saveflg_cli(spinlock_t* lock, cpuflg_t* cpuflg);
void hal_spinunlock_restflg_sti(spinlock_t* lock, cpuflg_t* cpuflg);
void knl_spinlock_init(spinlock_t* lock);
void knl_spinlock_lock(spinlock_t* lock);
void knl_spinlock_unlock(spinlock_t* lock);
void knl_spinlock_cli(spinlock_t* lock, cpuflg_t* cpuflg);
void knl_spinunlock_sti(spinlock_t* lock, cpuflg_t* cpuflg);
void hal_memset(void* setp,size_t n,u8_t setval);
void hal_memcpy(void* src,void* dst,size_t n);
void hal_sysdie(char_t* errmsg);
void system_error(char_t* errmsg);
uint_t hal_retn_cpuid();
#endif // CPUCTRL_H
