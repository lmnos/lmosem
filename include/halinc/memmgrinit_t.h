/**********************************************************
        物理内存管理器初始化文件memmgrinit_t.h
***********************************************************
                彭东 ＠ 2014.02.09.18.00
**********************************************************/
#ifndef _MEMMGRINIT_T_H
#define _MEMMGRINIT_T_H

typedef struct s_MEMMGROB
{
	list_h_t mo_list;
	spinlock_t mo_lock;
	uint_t mo_stus;
	uint_t mo_flgs;
	sem_t mo_sem;
	u64_t mo_memsz;
	u64_t mo_maxpages;
	u64_t mo_freepages;
	u64_t mo_alocpages;
	u64_t mo_resvpages;
	u64_t mo_horizline;
	phymmarge_t* mo_pmagestat;
	u64_t mo_pmagenr;
	msadsc_t* mo_msadscstat;
	u64_t mo_msanr;
	memarea_t* mo_mareastat;
	u64_t mo_mareanr;
	kmsobmgrhed_t mo_kmsobmgr;
	void* mo_privp;
	void* mo_extp;
}memmgrob_t;
#endif