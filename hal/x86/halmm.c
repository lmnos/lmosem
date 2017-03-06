/****************************************************************
        LMOSEM HAL内存初始化头文件halmm.c
*****************************************************************
                彭东 ＠ 2013.07.06.15.50
****************************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

PUBLIC void phymmarge_t_init(phymmarge_t* initp)
{
    if(NULL==initp)
    {
        return;
    }
    hal_spinlock_init(&initp->pmr_lock);
    initp->pmr_type=0;
    initp->pmr_stype=0;
    initp->pmr_dtype=0;
    initp->pmr_flgs=0;
    initp->pmr_stus=0;
    initp->pmr_saddr=0;
    initp->pmr_lsize=0;
    initp->pmr_end=0;
    initp->pmr_rrvmsaddr=0;
    initp->pmr_rrvmend=0;
    initp->pmr_prip=NULL;
    initp->pmr_extp=NULL;
    return;
}

PUBLIC void ret_phymmarge_adrandsz(machbstart_t* mbsp,phymmarge_t** retpmrvadr,u64_t* retpmrsz)
{
    if(NULL==mbsp||0==mbsp->mb_e820sz||NULL==mbsp->mb_e820padr||0==mbsp->mb_e820nr)
    {
        *retpmrsz=0;
        *retpmrvadr=NULL;
        return;
    }
    u64_t tmpsz=mbsp->mb_e820nr*sizeof(phymmarge_t);
    u64_t tmpphyadr=mbsp->mb_nextwtpadr;
    if(0!=initchkadr_is_ok(mbsp,tmpphyadr,tmpsz))
    {
        *retpmrsz=0;
        *retpmrvadr=NULL;
        return;
    }
    *retpmrsz=tmpsz;
    *retpmrvadr=(phymmarge_t*)((adr_t)tmpphyadr);
    return;
}

PUBLIC bool_t init_one_pmrge(e820map_t* e8p,phymmarge_t* pmargep)
{
    u32_t ptype=0,pstype=0;
    if(NULL==e8p||NULL==pmargep)
    {
        return FALSE;
    }
    phymmarge_t_init(pmargep);
    switch(e8p->type)
    {
        case RAM_USABLE:
            ptype=PMR_T_OSAPUSERRAM;
            pstype=RAM_USABLE;
            break;
        case RAM_RESERV:
            ptype=PMR_T_RESERVRAM;
            pstype=RAM_RESERV;
            break;
        case RAM_ACPIREC:
            ptype=PMR_T_HWUSERRAM;
            pstype=RAM_ACPIREC;
            break;
        case RAM_ACPINVS:
            ptype=PMR_T_HWUSERRAM;
            pstype=RAM_ACPINVS;
            break;
        case RAM_AREACON:
            ptype=PMR_T_BUGRAM;
            pstype=RAM_AREACON;
            break;
        default:
            break;
    }
    if(0==ptype)
    {
        return FALSE;
    }
    pmargep->pmr_type=ptype;
    pmargep->pmr_stype=pstype;
    pmargep->pmr_flgs=PMR_F_X86_64;
    pmargep->pmr_saddr=e8p->saddr;
    pmargep->pmr_lsize=e8p->lsize;
    pmargep->pmr_end=e8p->saddr+e8p->lsize-1;
    return TRUE;
}
// 4 5 6 2 3 8 1

// - + + - - + -

void phymmarge_swap(phymmarge_t* s,phymmarge_t* d)
{
    phymmarge_t tmp;
    phymmarge_t_init(&tmp);
    memcopy(s,&tmp,sizeof(phymmarge_t));
    memcopy(d,s,sizeof(phymmarge_t));
    memcopy(&tmp,d,sizeof(phymmarge_t));
    return;
}

void phymmarge_sort(phymmarge_t* argp,u64_t nr)
{
    u64_t i,j,k=nr-1;
    for(j=0;j<k;j++)
    {
        for(i=0;i<k-j;i++)
        {
            if(argp[i].pmr_saddr>argp[i+1].pmr_saddr)
            {
                phymmarge_swap(&argp[i],&argp[i+1]);
            }
        }
    }
    return;
}


PUBLIC u64_t initpmrge_core(e820map_t* e8sp,u64_t e8nr,phymmarge_t* pmargesp)
{
    u64_t retnr=0;
    if(NULL==e8sp||NULL==pmargesp||e8nr<1)
    {
        return 0;
    }
    for(u64_t i=0;i<e8nr;i++)
    {
        if(init_one_pmrge(&e8sp[i],&pmargesp[i])==FALSE)
        {
            return retnr;
        }
        retnr++;
    }
    return retnr;
}

PUBLIC void init_phymmarge()
{
    machbstart_t* mbsp=&kmachbsp;
    phymmarge_t* pmarge_adr=NULL;
    u64_t pmrgesz=0;
    ret_phymmarge_adrandsz(mbsp,&pmarge_adr,&pmrgesz);
    if(NULL==pmarge_adr||0==pmrgesz)
    {
        system_error("init_phymmarge->NULL==pmarge_adr||0==pmrgesz\n");
        return;
    }
    u64_t tmppmrphyadr=mbsp->mb_nextwtpadr;
    if((adr_t)tmppmrphyadr!=((adr_t)pmarge_adr))
    {
        system_error("init_phymmarge->tmppmrphyadr!=pmarge_adr2phyadr\n");
        return;
    }
    e820map_t* e8p=(e820map_t*)((adr_t)(mbsp->mb_e820padr));
    u64_t ipmgnr=initpmrge_core(e8p,mbsp->mb_e820nr,pmarge_adr);
    if(ipmgnr==0)
    {
        system_error("init_phymmarge->initpmrge_core ret 0\n");
        return;
    }
    if((ipmgnr*sizeof(phymmarge_t))!=pmrgesz)
    {
        system_error("init_phymmarge->ipmgnr*sizeof(phymmarge_t))!=pmrgesz\n");
        return;
    }
    mbsp->mb_e820expadr=tmppmrphyadr;
    mbsp->mb_e820exnr=ipmgnr;
    mbsp->mb_e820exsz=ipmgnr*sizeof(phymmarge_t);
    mbsp->mb_nextwtpadr=PAGE_ALIGN(mbsp->mb_e820expadr+mbsp->mb_e820exsz);
    phymmarge_sort(pmarge_adr,ipmgnr);
    return;
}

void init_halmm()
{
    init_phymmarge();
    init_memmgr();
    //init_mmapdsc(&osmach);
    //init_phymem();
    //!!下面这个函数要格外注意！！！
    //onmmapdsc_inkrlram(&osmach,&osphymem);   
    return;
}