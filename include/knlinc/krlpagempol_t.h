/**********************************************************
        内核层内存页面池管理头文件krlpagempol_t.h
***********************************************************
                彭东 ＠ 2013.07.18.15.00
**********************************************************/
#ifndef _KRLPAGEMPOL_T_H
#define _KRLPAGEMPOL_T_H

#define MPALCLST_MAX 5

#define PMPLMAP_MAX 32
#define KMEMPALCSZ_MIN 1
#define KMEMPALCSZ_MAX 0x400000

#define OBJSORPAGE 2048
#define KPMPORHALM (PAGE_SIZE*31)

#define MPLHTY_PAGE 1
#define MPLHTY_OBJS 2

#define OBJS_ALIGN(x) ALIGN(x,4) 
#define PHYMSA_MAX 512
#define PAGE_SIZE 0x1000
#define PAGE_SZRBIT (12)
typedef struct s_PGLMAP
{
    adr_t            pgl_start;
    struct s_PGLMAP* pgl_next;
}pglmap_t;

typedef struct s_MPLHEAD
{
    spinlock_t      mh_lock;
    list_h_t        mh_list;
    uint_t          mh_hedty;
    adr_t           mh_start;
    adr_t           mh_end;
    adr_t           mh_firtfreadr;
    pglmap_t*       mh_firtpmap;
    uint_t          mh_objnr;
    uint_t          mh_aliobsz;
    uint_t          mh_objsz;
    uint_t          mh_nxtpsz;
    uint_t          mh_afindx;
    uint_t          mh_pmnr;
    pglmap_t*       mh_pmap;
}mplhead_t;

typedef struct s_KMEMPOOL
{
    spinlock_t      mp_lock;
    list_h_t        mp_list;
    uint_t          mp_stus;
    uint_t          mp_flgs;
    spinlock_t      mp_pglock;
    spinlock_t      mp_oblock;
    uint_t          mp_pgmplnr;
    uint_t          mp_obmplnr;
    list_h_t        mp_pgmplmheadl;
    list_h_t        mp_obmplmheadl;
    mplhead_t*      mp_pgmplmhcach;
    mplhead_t*      mp_obmplmhcach;
#ifdef CFG_X86_PLATFORM
    list_h_t        mp_msalsthead[PHYMSA_MAX]; 
#endif
}kmempool_t;




#endif // KRLPAGEMPOL_T_H
