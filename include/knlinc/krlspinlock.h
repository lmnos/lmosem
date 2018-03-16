/****************************************************************
        LMOSEM kernel自旋锁头文件krlspinlock.h
*****************************************************************
                彭东 ＠ 2018.03.09.10.50
****************************************************************/
#ifndef _KRLSPINLOCK_H
#define _KRLSPINLOCK_H
void krlspinlock_init(spinlock_t* lock);
void krlspinlock_lock(spinlock_t* lock);
void krlspinlock_unlock(spinlock_t* lock);
void krlspinlock_cli(spinlock_t* lock,cpuflg_t* cpuflg);
void krlspinunlock_sti(spinlock_t* lock,cpuflg_t* cpuflg);
#endif