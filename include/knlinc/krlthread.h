/**********************************************************
        LMOSEM线程管理头文件krlthread.h
***********************************************************
                彭东 ＠ 2013.08.03.16.00
**********************************************************/
#ifndef _KRLTHREAD_H
#define _KRLTHREAD_H
void micrstk_t_init(micrstk_t* initp);
void context_t_init(context_t* initp);
uint_t krlretn_thread_id(thread_t* tdp);
void thread_t_init(thread_t* initp);
thread_t* krlnew_thread_dsc();
void krlthd_inc_tick(thread_t* thdp);
hand_t krlthd_retn_nullhand(thread_t* thdp);
hand_t krlthd_add_objnode(thread_t* thdp,objnode_t* ondp);
hand_t krlthd_del_objnode(thread_t *thdp, hand_t hand);
objnode_t* krlthd_retn_objnode(thread_t *thdp, hand_t hand);
void krlthreadkrlsatck_init(thread_t* thdp,void* runadr,reg_t cpsr,reg_t spsr);
thread_t* krlnew_thread_core(void* filerun,uint_t flg,uint_t prilg,uint_t prity,size_t usrstksz,size_t krlstksz);
thread_t* krlnew_thread(void* filerun,uint_t flg,uint_t prilg,uint_t prity,size_t usrstksz,size_t krlstksz);

#endif // KRLTHREAD_H
