/**********************************************************
        LMOSEM信号量头文件krlsem.h
***********************************************************
                彭东 ＠ 2013.08.18.18.00
**********************************************************/
#ifndef _KRLSEM_H
#define _KRLSEM_H
void krlsem_t_init(sem_t* initp);
void krlsem_set_sem(sem_t* setsem,uint_t flg,sint_t conut);
void krlsem_down(sem_t* sem);
void krlsem_up(sem_t* sem);
#endif // KRLSEM_H
