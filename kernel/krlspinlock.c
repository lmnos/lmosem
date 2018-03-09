/****************************************************************
        LMOSEM kernel自旋锁文件krlspinlock.c
*****************************************************************
                彭东 ＠ 2018.03.09.10.50
****************************************************************/

#include "lmosemtypes.h"
#include "lmosemmctrl.h"



void krlspinlock_init(spinlock_t* lock)
{
    knl_spinlock_init(lock);
    return;
}
void krlspinlock_lock(spinlock_t* lock)
{
    knl_spinlock_lock(lock);
    return;
}
void krlspinlock_unlock(spinlock_t* lock)
{
    knl_spinlock_unlock(lock);
    return;
}

void krlspinlock_cli(spinlock_t* lock,cpuflg_t* cpuflg)
{
    knl_spinlock_cli(lock,cpuflg);
    return;
}

void krlspinunlock_sti(spinlock_t* lock,cpuflg_t* cpuflg)
{
    knl_spinunlock_sti(lock,cpuflg);
    return;
}