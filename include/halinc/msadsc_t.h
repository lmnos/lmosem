/**********************************************************
        物理内存空间数组文件msadsc_t.h
***********************************************************
                彭东 ＠ 2015.05.03.17.00
**********************************************************/
#ifndef _MSADSC_T_H
#define _MSADSC_T_H

#define MSAD_PAGE_MAX (8)
typedef struct s_PAGEFLGS
{
	u64_t pf_alloc:1;
	u64_t pf_shared:1;
	u64_t pf_swap:1;
	u64_t pf_cache:1;
	u64_t pf_kmap:1;
	u64_t pf_lock:1;
	u64_t pf_dirt:1;
	u64_t pf_bzy:1;
	u64_t pf_rv2:4;
}__attribute__((packed)) pageflgs_t;

#define MF_OLKTY_INIT (0)
#define MF_OLKTY_ODER (1)
#define MF_OLKTY_BAFH (2)
#define MF_OLKTY_TOBJ (3)

#define MF_LSTTY_LIST (0)
#define MF_MOCTY_FREE (0)
#define MF_MOCTY_KRNL (1)
#define MF_MOCTY_USER (2)
#define MF_MRV1_VAL (0)
#define MF_UINDX_INIT (0)
#define MF_UINDX_MAX (0xffffff)
#define MF_MARTY_INIT (0)
#define MF_MARTY_HWD (1)
#define MF_MARTY_KRL (2)
#define MF_MARTY_PRC (3)
#define MF_MARTY_SHD (4)
typedef struct s_MSADFLGS
{
	u32_t mf_olkty:2;
	u32_t mf_lstty:1;
	u32_t mf_mocty:2;
	u32_t mf_marty:3;
	u32_t mf_uindx:24;
}__attribute__((packed)) msadflgs_t; 


#define  PAF_NO_ALLOC (0)
#define  PAF_ALLOC (1)
#define  PAF_NO_SHARED (0)
#define  PAF_NO_SWAP (0)
#define  PAF_NO_CACHE (0)
#define  PAF_NO_KMAP (0)
#define  PAF_NO_LOCK (0)
#define  PAF_NO_DIRTY (0)
#define  PAF_NO_BUSY (0)
#define  PAF_RV2_VAL (0)
#define  PAF_INIT_PADRS (0)
typedef struct s_PHYADRFLGS
{
	u64_t paf_alloc:1;
	u64_t paf_shared:1;
	u64_t paf_swap:1;
	u64_t paf_cache:1;
	u64_t paf_kmap:1;
	u64_t paf_lock:1;
	u64_t paf_dirty:1;
	u64_t paf_busy:1;
	u64_t paf_rv2:4;
	u64_t paf_padrs:52;
}__attribute__((packed)) phyadrflgs_t;


typedef struct s_PAGE
{
	union
	{
		list_h_t p_lruchelst;
		struct s_PAGE* p_left;
		struct s_PAGE* p_right;
	}__attribute__((packed));
	union
	{
		pageflgs_t p_flgs;
		u64_t p_start;
	}__attribute__((packed));
	union
	{
		u64_t p_infileoff;
		void* p_data;
	}__attribute__((packed));
}__attribute__((packed)) page_t;//32

typedef struct s_MSADSC
{
	list_h_t md_list;//16
	/*union
	{
		struct s_MSADSC* md_left;
		struct s_MSADSC* md_right;
		list_h_t md_lscsmlist;
	}__attribute__((packed)); *///16
	spinlock_t md_lock; //4
	msadflgs_t md_indxflgs;//4
	phyadrflgs_t md_phyadrs;//8
	void* md_odlink;//8
}__attribute__((packed)) msadsc_t;//32+24



struct vm_objs
{
	long start;
	long end;
	long flg;
	tree_t tree;
	void* pdr;
	list_h_t msa_listl;
	
};


#endif