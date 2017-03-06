/****************************************************************
        LMOSEM HAL板级体系初始化头文件halmach_t.h
*****************************************************************
                彭东 ＠ 2013.07.06.15.50
****************************************************************/
#ifndef _HALMACH_T_H
#define _HALMACH_T_H
#ifdef CFG_S3C2440A_PLATFORM
typedef struct s_MACH
{
    spinlock_t mh_lock;
    list_h_t   mh_list;
    adr_t      mh_kerinramstart;
    adr_t      mh_kerinramend;
    mmapdsc_t* mh_mmapdscadr;
    uint_t     mh_mmapdscnr;
    
    uint_t     mh_spedscnr;
    phyadrspce_t *mh_spedsc;
    ilnedsc_t* mh_ilnedsc;
    uint_t     mh_ilnedscnr;
    intfltdsc_t* mh_intfltdsc;
    uint_t     mh_intfltnr;
}mach_t;
#endif
#endif // HALINIT_H
