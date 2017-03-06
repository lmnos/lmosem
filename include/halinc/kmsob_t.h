/**********************************************************
        内核内存空间对象分配释放头文件kmsob_t.h
***********************************************************
                彭东 ＠ 2015.06.26.22.00
**********************************************************/
#ifndef _KMSOB_T_H
#define _KMSOB_T_H

#define MSCLST_MAX (5)
#define KOBLST_MAX (64)
#define KUC_NEWFLG (1)
#define KUC_DELFLG (2)
#define KUC_DSYFLG (3)

typedef struct s_MSCLST
{
	uint_t ml_msanr;
	uint_t ml_ompnr;
	list_h_t ml_list;
}msclst_t;

typedef struct s_MSOMDC
{
	msclst_t mc_lst[MSCLST_MAX];
	uint_t mc_msanr;
	list_h_t mc_list;
	list_h_t mc_kmobinlst;
	uint_t mc_kmobinpnr;
}msomdc_t;

typedef struct s_FREOBJH
{
	list_h_t oh_list;
	uint_t oh_stus;
	void* oh_stat;
}freobjh_t;

typedef struct s_KMSOB
{
	list_h_t so_list;
	spinlock_t so_lock;
	uint_t so_stus;
	uint_t so_flgs;
	adr_t so_vstat;
	adr_t so_vend;
	size_t so_objsz;
	size_t so_objrelsz;
	uint_t so_mobjnr;
	uint_t so_fobjnr;
	list_h_t so_frelst;
	list_h_t so_alclst;
	list_h_t so_mextlst;
	uint_t so_mextnr; 
	msomdc_t so_mc;
	void* so_privp;
	void* so_extdp;
}kmsob_t;

typedef struct s_KMBEXT
{
	list_h_t mt_list;
	adr_t mt_vstat;
	adr_t mt_vend;
	kmsob_t* mt_kmsb;
	uint_t mt_mobjnr;	
}kmbext_t;



typedef struct s_KOBLST
{
	//list_h_t ol_fullst;
	list_h_t ol_emplst;
	//list_h_t ol_efulst;
	kmsob_t* ol_cahe;
	//uint_t ol_funr;
	uint_t ol_emnr;
	//uint_t ol_efnr;
	size_t ol_sz;
}koblst_t;

typedef struct s_KMSOBMGRHED
{
	spinlock_t ks_lock;
	list_h_t ks_tclst;
	uint_t ks_tcnr;
	uint_t ks_msobnr;
	kmsob_t* ks_msobche;
	koblst_t ks_msoblst[KOBLST_MAX];
}kmsobmgrhed_t;

typedef struct s_KOBCKS
{
	list_h_t kk_list;
	void* kk_vadr;
	size_t kk_sz;
}kobcks_t;



#endif
