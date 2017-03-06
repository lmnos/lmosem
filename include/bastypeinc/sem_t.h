/**********************************************************
		信号量头文件sem_t.h
***********************************************************
				彭东 ＠ 2012.11.01.15.00
**********************************************************/
#ifndef _SEM_T_H
#define _SEM_T_H
#define SEM_FLG_MUTEX 0
#define SEM_FLG_MULTI 1
#define SEM_MUTEX_ONE_LOCK 1
#define SEM_MULTI_LOCK 0
typedef struct s_ATOMIC{
	volatile s32_t a_count;
}atomic_t;


typedef struct s_KWLST
{   
    spinlock_t wl_lock;
    uint_t   wl_tdnr;
    list_h_t wl_list;
}kwlst_t;

typedef struct s_SEM
{
	spinlock_t sem_lock;
	uint_t sem_flg;
	sint_t sem_count;
	kwlst_t sem_waitlst;
}sem_t;
typedef struct s_WAIT_L_HEAD
{
	list_h_t wlh_llist;
	spinlock_t wlh_lock;
	atomic_t wlh_count;
	void* wlh_privte;
	bool_t  (*wlh_upfun)(u32_t func,struct s_WAIT_L_HEAD* wlhp);//lh_upfun_t wlh_upfun; //void (*wlh_upfun)();wait_l_head_t
}wait_l_head_t;

typedef struct s_WAIT_L
{
	list_h_t wl_hlist;
	u32_t wl_flags;
	void* wl_thead;
}wait_l_t;
#endif
