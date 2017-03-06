/**********************************************************
        物理内存地址区间文件me820kex_t.h
***********************************************************
                彭东 ＠ 2014.10.28.21.30
**********************************************************/
#ifndef _ME820KEX_T_H
#define _ME820KEX_T_H
typedef struct s_E820{
    u64_t saddr;
    u64_t lsize;
    u32_t type;
}__attribute__((packed)) e820_t;
typedef struct s_ME820KEX
{
    list_h_t   e8x_list;
    u64_t      e8x_flgs;
    spinlock_t e8x_lock;
    u32_t      e8x_type;
    u64_t      e8x_sadr;
    u64_t      e8x_lenz;
    u64_t      e8x_eadr;
    u64_t      e8x_rsdr;
    u64_t      e8x_rlen;
    u64_t      e8x_redr;
    void*      e8x_smap;
    void*      e8x_emap;
    u64_t      e8x_mapn;
    u64_t      e8x_omsz;
    void*      e8x_pzon;
    void*      e8x_prvp;
    void*      e8x_extp;
}me820kex_t;


#endif
