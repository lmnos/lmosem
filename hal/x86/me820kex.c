/**********************************************************
        物理内存地址区间文件me820kex.c
***********************************************************
                彭东 ＠ 2014.10.28.21.30
**********************************************************/

#include "lmosemtypes.h"
#include "lmosemmctrl.h"

PUBLIC void me820kex_t_init(me820kex_t* initp)
{
    list_init(&initp->e8x_list);
    initp->e8x_flgs=0;
    knl_spinlock_init(&initp->e8x_lock);
    initp->e8x_type=0;
    initp->e8x_sadr=0;
    initp->e8x_lenz=0;
    initp->e8x_eadr=0;
    initp->e8x_rsdr=0;
    initp->e8x_rlen=0;
    initp->e8x_redr=0;
    initp->e8x_smap=NULL;
    initp->e8x_emap=NULL;
    initp->e8x_mapn=0;
    initp->e8x_omsz=0;
    initp->e8x_pzon=NULL;
    return;
}

void write_one_me820kex(me820kex_t* m8xp,e820_t* e8p)
{
    me820kex_t_init(m8xp);
    m8xp->e8x_sadr=e8p->saddr;
    m8xp->e8x_lenz=e8p->lsize;
    m8xp->e8x_type=e8p->type;
    //m8xp->e8x_eadr=m8xp->e8x_sadr+m8xp->e8x_lenz;
    m8xp->e8x_eadr=m8xp->e8x_sadr+m8xp->e8x_lenz;
    return;
}

PUBLIC void init_me820kex()
{
    machbstart_t* mbsp=&kmachbsp;
    u64_t m8kxsz=mbsp->mb_e820nr*sizeof(me820kex_t);
    if(0==m8kxsz)
    {
        system_error("init_me820kex m8kxsz 0");
    }
    u64_t m8kxpadr=mbsp->mb_nextwtpadr;
    me820kex_t* m8kp=(me820kex_t*)krnlphyiadr_to_viradr(m8kxpadr);
    if(initchkadr_is_ok(mbsp,m8kxpadr,m8kxsz)!=0)
    {
        system_error("init_me820kex chkadr not ok");
    }
    e820_t* e8p=(e820_t*)krnlphyiadr_to_viradr(mbsp->mb_e820padr);
    for(u64_t i=0;i<mbsp->mb_e820nr;i++)
    {
        write_one_me820kex(&m8kp[i],&e8p[i]);
    }
    mbsp->mb_nextwtpadr=PAGE_ALIGN(m8kxpadr+m8kxsz);
    return;
}
