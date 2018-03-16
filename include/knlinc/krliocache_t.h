/**********************************************************
        LMOSEM IO缓存块头文件krliocache_t.h
***********************************************************
                彭东 ＠ 2018.03.08.10.10
**********************************************************/
#ifndef _KRLIOCACHE_T_H
#define _KRLIOCACHE_T_H

#define ICBLK_SIZE (4096)

typedef struct s_IOCHEBLKDSC 
{
	spinlock_t icd_look;
	list_h_t icd_icblst;
	uint_t icd_flgs;
	uint_t icd_icblknr;
	//应该加入AVL树或者红黑树
	//以便加快查找性能
	void*  icd_priv;
	void*  icd_extp;
}iocheblkdsc_t;



typedef struct s_IOCHEBLK
{
	spinlock_t icb_look;
	list_h_t icb_list;
	uint_t icb_type;
	uint_t icb_flgs;
	//应该加入AVL树或者红黑树
	//以便加快查找性能
	uint_t icb_lblknr;
	void*  icb_buffer;
	uint_t icb_bufsz;
	void*  icb_priv;
	void*  icb_extp;
}iocheblk_t;




#endif // _KRLIOCACHE_T_H