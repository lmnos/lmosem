/****************************************************************
        LMOSEM HAL内存初始化头文件halmm.c
*****************************************************************
                彭东 ＠ 2013.07.06.15.50
****************************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void init_halmm()
{
    if(cheksum_phyadrspce(&osmach)==FALSE)
    {
        hal_sysdie("cheksum_phyadrspce ret FALSE");
    }
    init_mmapdsc(&osmach);
    init_phymem();
    //!!下面这个函数要格外注意！！！
    onmmapdsc_inkrlram(&osmach,&osphymem);   
    return;
}
void print_mmapdsc(mach_t *mchp)
{
    mmapdsc_t* map=mchp->mh_mmapdscadr;
    uint_t mnr=mchp->mh_mmapdscnr;
    for(uint_t i=0;i<mnr;i++)
    {
        printfk("mmapdsc[%x].map_phyadr:%x,map_phyadrend:%x\n\r",i,(uint_t)map[i].map_phyadr,(uint_t)map[i].map_phyadrend);
    }
    return;
}

sint_t cheksum_phyadrspce(mach_t* mahp)
{
    sint_t sdramsts=FALSE,kerinmmsts=FALSE;
    phyadrspce_t* adsp=mahp->mh_spedsc;
    uint_t spnr=mahp->mh_spedscnr;
    if(adsp==NULL||spnr!=PLFM_ADRSPCE_NR)
    {
        return FALSE;
    }
    
    if(adsp[spnr-1].ap_flgs!=ADRSPCE_NOT||
       adsp[spnr-1].ap_devtype!=DEV_TYPE_NOT||
       adsp[spnr-1].ap_adrstart!=0||
       adsp[spnr-1].ap_adrend!=0)
    {
        return FALSE;
    }
       
    for(uint_t i=0;i<spnr;i++)
    {
        if(adsp[i].ap_adrend<adsp[i].ap_adrstart)
        {
            return FALSE;
        }
        if(adsp[i].ap_flgs==ADRSPCE_SDRAM)
        {
            sdramsts=TRUE;
            if(mahp->mh_kerinramstart>=adsp[i].ap_adrstart&&
               mahp->mh_kerinramend<adsp[i].ap_adrend)
            {
                kerinmmsts=TRUE;
            }   
        }
        
    }
    if(sdramsts==TRUE&&kerinmmsts==TRUE)
    {
        return TRUE;
    }
    return FALSE;
}

void init_mmapdsc(mach_t* mahp)
{
    phyadrspce_t* adsp=mahp->mh_spedsc;
    uint_t spnr=mahp->mh_spedscnr;
    uint_t mindx=0;
    for(uint_t i=0;i<spnr;i++)
    {
        if(adsp[i].ap_flgs==ADRSPCE_SDRAM)
        {
            mindx=init_core_mmapdsc(adsp[i].ap_adrstart,adsp[i].ap_adrend,mahp->mh_mmapdscadr,mindx);
        }
    }
    mahp->mh_mmapdscnr=mindx;
    mahp->mh_kerinramend=(adr_t)((uint_t)mahp->mh_mmapdscadr+((sizeof(mmapdsc_t))*mindx));
    return;
}

uint_t init_core_mmapdsc(adr_t adrs,adr_t adre,mmapdsc_t* gmmp,uint_t curmindx)
{
    uint_t mindx=curmindx;
    adr_t tmpadr=adre;
    for(;adrs<adre;adrs+=MAPONE_SIZE,mindx++)
    {
        if((adrs+MAPONE_SIZE)<adre)
        {
            tmpadr=(adrs+MAPONE_SIZE)-1;
        }else
        {
            tmpadr=adre;
        }
        
        mmapdsc_t_init(&gmmp[mindx],adrs,tmpadr,0,MAP_FLAGES_VAL(0,MAPF_ACSZ_4MB,MAPF_SZ_4MB));
    }
    return mindx;
}

void mmapdsc_t_init(mmapdsc_t* mmp,adr_t phyadr,adr_t phyadre,u32_t allcount,u32_t flgs)
{
    list_init(&mmp->map_list);
    hal_spinlock_init(&mmp->map_lock);
    mmp->map_phyadr=phyadr;
    mmp->map_phyadrend=phyadre;
    mmp->map_allcount=allcount;
    mmp->map_flg=flgs;
    return;
}



void alcfrelst_t_init(alcfrelst_t* initp,size_t bsz)
{
    hal_spinlock_init(&initp->afl_lock);
    initp->afl_sz=bsz;
    list_init(&initp->afl_fulllsth);
    list_init(&initp->afl_emtplsth);
    list_init(&initp->afl_fuemlsth);
    return;
}

void phymem_t_init(phymem_t* initp)
{
    list_init(&initp->pmm_list);
    hal_spinlock_init(&initp->pmm_lock);
    alcfrelst_t_init(&initp->pmm_sz_lsth[0],BLK128KB_SIZE);
    alcfrelst_t_init(&initp->pmm_sz_lsth[1],BLK256KB_SIZE);
    alcfrelst_t_init(&initp->pmm_sz_lsth[2],BLK512KB_SIZE);
    alcfrelst_t_init(&initp->pmm_sz_lsth[3],BLK1MB_SIZE);
    alcfrelst_t_init(&initp->pmm_sz_lsth[4],BLK2MB_SIZE);
    alcfrelst_t_init(&initp->pmm_sz_lsth[5],BLK4MB_SIZE);
    
    return;
}

void onmmapdsc_inkrlram(mach_t* mahp,phymem_t* pmp)
{
    mmapdsc_t* mapp=mahp->mh_mmapdscadr;
    adr_t ker_r_s=mahp->mh_kerinramstart,ker_r_e=mahp->mh_kerinramend;
    if((ker_r_e-ker_r_s)>BLK128KB_SIZE||ker_r_s<mapp[0].map_phyadr)
    {
        hal_sysdie("onmmapdsc_inkrlram err");
    }
    u32_t cut=1;
    u32_t flg=MAP_FLAGES_VAL(0,MAPF_ACSZ_128KB,MAPF_SZ_4MB);
    mapp[0].map_allcount=cut;
    mapp[0].map_flg=flg;
    mapdsc_addto_memlst(&pmp->pmm_sz_lsth[0],&mapp[0],ADDT_FUEM_FLG);
    return;
}

void init_phymem()
{
    phymem_t_init(&osphymem);
    pmmlist_init(&osmach,&osphymem);
    return;
}

void pmmlist_init(mach_t* mahp,phymem_t* pmp)
{
    mmapdsc_t* mapp=mahp->mh_mmapdscadr;
    uint_t mapnr=mahp->mh_mmapdscnr;
    for(uint_t mr=1;mr<mapnr;mr++)
    {
        mapdsc_addto_memlst(&pmp->pmm_sz_lsth[BLKSZ_HEAD_MAX-1],&mapp[mr],ADDT_EMTP_FLG);
        
    }
    return;
}

void mapdsc_addto_memlst(alcfrelst_t* aflp,mmapdsc_t* mapp,uint_t atflg)
{
    switch(atflg)
    {
        case ADDT_EMTP_FLG:
            list_add_tail(&mapp->map_list,&aflp->afl_emtplsth);
            break;
        case ADDT_FUEM_FLG:
            list_add_tail(&mapp->map_list,&aflp->afl_fuemlsth);
            break;
        case ADDT_FULL_FLG:
            list_add_tail(&mapp->map_list,&aflp->afl_fulllsth);
            break;
        default:
            break;
    }
    return; 
}

alcfrelst_t* hal_onblksz_findalcfrelst(alcfrelst_t** retalcfrl,size_t* retalcsz,size_t blksz)
{
    phymem_t* memp=&osphymem;
    alcfrelst_t* aftp=NULL,*aft4mbp=&memp->pmm_sz_lsth[BLKSZ_HEAD_MAX-1];
    for(uint_t bj=0;bj<BLKSZ_HEAD_MAX;bj++)
    {
        if(memp->pmm_sz_lsth[bj].afl_sz==blksz)
        {
            aftp=&memp->pmm_sz_lsth[bj];
            *retalcfrl=aftp;
            *retalcsz=memp->pmm_sz_lsth[bj].afl_sz;
            goto next_step;
        }
    
    }
   
    aftp=NULL;
    *retalcfrl=NULL;
    *retalcsz=0;
next_step:
    if(aftp==NULL)
    {
        return NULL;
    }
    if(list_is_empty_careful(&aftp->afl_emtplsth)==FALSE)
    {
        return aftp;
    }
    if(list_is_empty_careful(&aftp->afl_fuemlsth)==FALSE)
    {
        return aftp;
    }
    aftp=aft4mbp;

    if(list_is_empty_careful(&aftp->afl_emtplsth)==FALSE)
    {
        return aftp;
    }
    return NULL;
}

mmapdsc_t* hal_onalfl_findmapdsc(alcfrelst_t* allclh)
{
   
    mmapdsc_t* mp=NULL;
    if(list_is_empty_careful(&allclh->afl_fuemlsth)==FALSE)
    {
        mp=list_entry(allclh->afl_fuemlsth.next,mmapdsc_t,map_list);
        return mp;
    }
    
    if(list_is_empty_careful(&allclh->afl_emtplsth)==FALSE)
    {
        mp=list_entry(allclh->afl_emtplsth.next,mmapdsc_t,map_list);
        return mp;
    }
    return NULL;
}

adr_t hal_onmapdsc_allcblks(u32_t mflg, u32_t mask,u32_t bitls,alcfrelst_t* aflp,alcfrelst_t* mvtoaflp)
{
    adr_t retadr=NULL;
    mmapdsc_t* map=NULL;
    uint_t bi=0;
    u32_t fg=0xffffff0f;
    if(bitls>32)
    {
        return NULL;    
    }
    map=hal_onalfl_findmapdsc(aflp);
    if(map==NULL)
    {
        return NULL;
    }
    for(;bi<bitls;bi++)
    {
        if(((map->map_allcount>>bi)&1)==0)
        {
            goto next_step;
        }
    }
    bi=0xffffffff;
next_step:
    if(bi==0xffffffff)
    {
        return NULL;
    }
    
    retadr=map->map_phyadr+(mvtoaflp->afl_sz*bi);
    if(retadr<map->map_phyadr||retadr>=map->map_phyadrend)
    {
        return NULL;
    }
    map->map_allcount|=(1<<bi);
    map->map_flg&=fg;
    map->map_flg|=mflg;
    
    if((map->map_allcount&mask)==mask)
    {
        list_move_tail(&map->map_list,&mvtoaflp->afl_fulllsth);
        return retadr;
    }
    list_move_tail(&map->map_list,&mvtoaflp->afl_fuemlsth);
    return retadr;
}


adr_t hal_onalcfrel_allocblks(alcfrelst_t* allclh,alcfrelst_t* relaclh,size_t relalcsz)
{
    adr_t retadr=NULL;
    switch(relalcsz)
    {
        case BLK128KB_SIZE:
            retadr=hal_onmapdsc_allcblks(MAPF_ACSZ_128KB,BLK128KB_MASK,BLK128KB_BITL,allclh,relaclh);
            break;
        case BLK256KB_SIZE:
            retadr=hal_onmapdsc_allcblks(MAPF_ACSZ_256KB,BLK256KB_MASK,BLK256KB_BITL,allclh,relaclh);
            break;
        case BLK512KB_SIZE:
            retadr=hal_onmapdsc_allcblks(MAPF_ACSZ_512KB,BLK512KB_MASK,BLK512KB_BITL,allclh,relaclh);
            break;
        case BLK1MB_SIZE:
            retadr=hal_onmapdsc_allcblks(MAPF_ACSZ_1MB,BLK1MB_MASK,BLK1MB_BITL,allclh,relaclh);
            break;
        case BLK2MB_SIZE:
            retadr=hal_onmapdsc_allcblks(MAPF_ACSZ_2MB,BLK2MB_MASK,BLK2MB_BITL,allclh,relaclh);
            break;
        case BLK4MB_SIZE:
            retadr=hal_onmapdsc_allcblks(MAPF_ACSZ_4MB,BLK4MB_MASK,BLK4MB_BITL,allclh,relaclh);
            break;
        default:
            retadr=NULL;
            break;    
    
    }
    return retadr;
}

adr_t hal_memallocblks_core(size_t blksz)
{
    phymem_t* memp=&osphymem;
    size_t retbsz=0;
    cpuflg_t cpufg;
    adr_t retadr=NULL;
    alcfrelst_t* allcflp=NULL;
    alcfrelst_t* aftp=NULL;
    hal_spinlock_saveflg_cli(&memp->pmm_lock,&cpufg);
    aftp=hal_onblksz_findalcfrelst(&allcflp,&retbsz,blksz);
    if(aftp==NULL||allcflp==NULL||retbsz==0)
    {
        retadr=NULL;
        goto return_step;
    }
    if(aftp->afl_sz!=retbsz&&aftp->afl_sz!=BLK4MB_SIZE)
    {
        retadr=NULL;
        goto return_step;
    }
    
    retadr=hal_onalcfrel_allocblks(aftp,allcflp,retbsz);
return_step:
    hal_spinunlock_restflg_sti(&memp->pmm_lock,&cpufg);  
    return retadr;  
    
}

adr_t hal_memallocblks(size_t blksz)
{
    if(blksz<BLK128KB_SIZE||blksz>BLK4MB_SIZE)
    {
        return NULL;
    }
    
    return hal_memallocblks_core(blksz);
}

mmapdsc_t* hal_free_findmapdsc(adr_t frebadr,alcfrelst_t* allclh)
{
    mmapdsc_t* mp=NULL;
    list_h_t* tmplst=NULL;
    if(list_is_empty_careful(&allclh->afl_fuemlsth)==FALSE)
    {
        list_for_each(tmplst,&allclh->afl_fuemlsth)
        {
            mp=list_entry(tmplst,mmapdsc_t,map_list);
            if(frebadr<mp->map_phyadrend&&frebadr>=mp->map_phyadr)
            {
                return mp;
            }
        }
        
    }
    
    if(list_is_empty_careful(&allclh->afl_fulllsth)==FALSE)
    {
        list_for_each(tmplst,&allclh->afl_fulllsth)
        {
            mp=list_entry(tmplst,mmapdsc_t,map_list);
            if(frebadr<mp->map_phyadrend&&frebadr>=mp->map_phyadr)
            {
                return mp;
            }
        }
        
    }
    return NULL;
}

bool_t hal_onmapdsc_freeblks(adr_t frebadr,u32_t mflg, u32_t mask,alcfrelst_t* aflp,alcfrelst_t* mvtoaflp)
{
    mmapdsc_t* map=NULL;
    uint_t bitnr;
  
    u32_t fg=0xffffff0f;

    map=hal_free_findmapdsc(frebadr,aflp);
    if(map==NULL)
    {
        return FALSE;
    }
    bitnr=(uint_t)(frebadr-map->map_phyadr)/(uint_t)(aflp->afl_sz);
    if(bitnr>31)
    {
        return FALSE;
    }
    
    if(((map->map_allcount>>bitnr)&1)!=1)
    {
       return FALSE;
    }
    
    map->map_allcount&=(~(1<<bitnr));
    if((map->map_allcount&mask)==0)
    {
        map->map_flg&=fg;
        map->map_flg|=mflg;
        list_move(&map->map_list,&mvtoaflp->afl_emtplsth);
    }
    
    return TRUE;
}

bool_t hal_onalcfrel_freeblks(adr_t frebadr,alcfrelst_t* allclh,alcfrelst_t* mvaflh,size_t relalcsz)
{
    bool_t retstus=FALSE;
    switch(relalcsz)
    {
        case BLK128KB_SIZE:
            retstus=hal_onmapdsc_freeblks(frebadr,MAPF_ACSZ_4MB,BLK128KB_MASK,allclh,mvaflh);
            break;
        case BLK256KB_SIZE:
            retstus=hal_onmapdsc_freeblks(frebadr,MAPF_ACSZ_4MB,BLK256KB_MASK,allclh,mvaflh);
            break;
        case BLK512KB_SIZE:
            retstus=hal_onmapdsc_freeblks(frebadr,MAPF_ACSZ_4MB,BLK512KB_MASK,allclh,mvaflh);
            break;
        case BLK1MB_SIZE:
            retstus=hal_onmapdsc_freeblks(frebadr,MAPF_ACSZ_4MB,BLK1MB_MASK,allclh,mvaflh);
            break;
        case BLK2MB_SIZE:
            retstus=hal_onmapdsc_freeblks(frebadr,MAPF_ACSZ_4MB,BLK2MB_MASK,allclh,mvaflh);
            break;
        case BLK4MB_SIZE:
            retstus=hal_onmapdsc_freeblks(frebadr,MAPF_ACSZ_4MB,BLK4MB_MASK,allclh,mvaflh);
            break;
        default:
            retstus=FALSE;
            break;    
    
    }
    return retstus;
}

bool_t hal_memfreeblks_core(adr_t frebadr,size_t blksz)
{
    
    phymem_t* memp=&osphymem;
    bool_t retstus=FALSE;
    cpuflg_t cpufg;
 
    alcfrelst_t* aftp=NULL,*mvtoaftp=&memp->pmm_sz_lsth[BLKSZ_HEAD_MAX-1];
    hal_spinlock_saveflg_cli(&memp->pmm_lock,&cpufg);
    for(uint_t fi=0;fi<BLKSZ_HEAD_MAX;fi++)
    {
        if(memp->pmm_sz_lsth[fi].afl_sz==blksz)
        {
            aftp=&memp->pmm_sz_lsth[fi];
            goto next_step; 
        }
    }
    aftp=NULL;
next_step:    
    if(aftp==NULL)
    {
        retstus=FALSE;
        goto return_step;
    }
    retstus=hal_onalcfrel_freeblks(frebadr,aftp,mvtoaftp,blksz);
return_step:
    hal_spinunlock_restflg_sti(&memp->pmm_lock,&cpufg);  
    return retstus;
}

bool_t hal_memfreeblks(adr_t frebadr,size_t blksz)
{
    if(frebadr==NULL||blksz<BLK128KB_SIZE||blksz>BLK4MB_SIZE)
    {
        return FALSE;
    }
    return hal_memfreeblks_core(frebadr,blksz);
}

void testblkalloc()
{
    size_t ablksz=0;
    adr_t retadr=NULL;
    for(uint_t bli=0;bli<6;bli++)
    {
        ablksz=BLK128KB_SIZE<<bli;
        for(uint_t i=0;i<2;i++)
        {
            retadr=hal_memallocblks(ablksz);
            if(retadr==NULL)
            {
                hal_sysdie("NOT MEMBLK;return NULL");
            }
            printfk("allocblksz:%x return adrr:%x \n\r",ablksz,retadr);
        }
    }
    return;
}


void test_blkmm()
{
    adr_t retadra[14],retadr=0,retadrold=0,retadrend=0;
    size_t ablksz=0;bool_t retstus=FALSE;
    retadrold=hal_memallocblks(BLK128KB_SIZE);
    if(retadrold==NULL)
        hal_sysdie("NOT MEMALLOCBLKold;return NULL");
    if(hal_memfreeblks(retadrold,BLK128KB_SIZE)==FALSE)
        hal_sysdie("NOT MEMFREEBLKold;return FALSE");
    for(uint_t bli=0;bli<6;bli++)
    {
        ablksz=BLK128KB_SIZE<<bli;
        for(uint_t i=0;i<14;i++)
        {
            retadr=hal_memallocblks(ablksz);
            if(retadr==NULL)
                hal_sysdie("NOT MEMALLOCBLK;return NULL");
            printfk("allocblksz:%x return adrr:%x \n\r",ablksz,retadr);
            retadra[i]=retadr;
        }
        for(uint_t j=0;j<14;j++)
        {
            retstus=hal_memfreeblks(retadra[j],ablksz);
            if(retstus==FALSE)
                hal_sysdie("NOT MEMFREEBLK;return FALSE");
            printfk("freeblksz:%x free adrr:%x \n\r",ablksz,retadra[j]);
        }
    }
    retadrend=hal_memallocblks(BLK128KB_SIZE);
    if(retadrend==NULL)
        hal_sysdie("NOT MEMALLOCBLKend;return NULL");
    if(retadrend==retadrold)
        printfk("TEST BLKMM OK!!\n\r");
    return;
}