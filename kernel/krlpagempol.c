/**********************************************************
        内核层内存页面池管理文件krlpagempol.c
***********************************************************
                彭东 ＠ 2013.07.18.15.00
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

typedef struct s_adrsz
{
    adr_t adr;
    size_t sz; 
}adrsz_t;


void testpgmpool()
{

    adrsz_t adsz[10];
    size_t alcsz=0x1000;
    adsz[0].sz=alcsz;
    adsz[0].adr=kmempool_new(alcsz);
    adsz[1].sz=alcsz;
    adsz[1].adr=kmempool_new(alcsz);
    alcsz=0x1500;
    adsz[2].sz=alcsz;
    adsz[2].adr=kmempool_new(alcsz);
    adsz[3].sz=alcsz;
    adsz[3].adr=kmempool_new(alcsz);
    alcsz=0x3000;
    adsz[4].sz=alcsz;
    adsz[4].adr=kmempool_new(alcsz);
    adsz[5].sz=alcsz;
    adsz[5].adr=kmempool_new(alcsz);
    alcsz=0x3200;
    adsz[6].sz=alcsz;
    adsz[6].adr=kmempool_new(alcsz);
    adsz[7].sz=alcsz;
    adsz[7].adr=kmempool_new(alcsz);
    alcsz=0x7000;
    adsz[8].sz=alcsz;
    adsz[8].adr=kmempool_new(alcsz);
    adsz[9].sz=alcsz;
    adsz[9].adr=kmempool_new(alcsz);
    for(int i=0;i<10;i++)
    {
        printfk("adsz[%x] sz:%x adr:%x\n\r",i,adsz[i].sz,adsz[i].adr);
    }
    mplhead_t* retmhp;
    list_h_t* list;

    list_for_each(list,&oskmempool.mp_pgmplmheadl)
    {
        retmhp=list_entry(list,mplhead_t,mh_list);
        printfk("mph_t_adr:%x mph_t.mh_end:%x mph_t.mh_objsz:%x mph_t.mh_objnr:%x\n\r",
                retmhp,retmhp->mh_end,retmhp->mh_objsz,retmhp->mh_objnr);
    }
    return;
}

void cmp_adrsz(adrsz_t* assp,uint_t nr)
{
    for(uint_t i=0;i<nr;i++)
    {
        for(uint_t j=0;j<nr;j++)
        {
            if(i!=j)
            {
                if(assp[i].adr==assp[j].adr)
                {
                    hal_sysdie("cmp adr start err");
                }
            }
        }
    }

    for(uint_t k=0;k<nr;k++)
    {
        for(uint_t h=0;h<nr;h++)
        {
            if(k!=h)
            {
                if((assp[k].adr+assp[k].sz)==(assp[h].adr+assp[h].sz))
                {
                    hal_sysdie("cmp adr end err");
                }
            }
        }
    }

    for(uint_t l=0;l<nr;l++)
    {
        for(uint_t m=0;m<nr;m++)
        {
            if(l!=m)
            {
                if((assp[l].adr>=(assp[m].adr))&&((assp[l].adr+assp[l].sz)<=(assp[m].adr+assp[m].sz)))
                {
                    hal_sysdie("cmp adr in err");
                }
            }
        }
    }
    u8_t* bytp=NULL,bytv=0;
    for(uint_t n=0;n<nr;n++)
    {
        bytp=(u8_t*)(assp[n].adr);
        bytv=(u8_t)(assp[n].adr&0xff);
        for(uint_t o=0;o<assp[n].sz;o++)
        {
            if(bytp[o]!=bytv)
            {
                hal_sysdie("cmp val err");
            }
        }
    }
    return;
}

void testobjsmgr()
{
    adrsz_t adsz[64];
    size_t alcsz=0x20;
    u8_t* adrbytp=NULL,bytval=0;
    for(;alcsz<0x800;alcsz+=0x10)
    {

        for(int i=0;i<64;i++)
        {
            adsz[i].sz=alcsz;
            adsz[i].adr=kmempool_new(alcsz);
            if(adsz[i].adr==NULL)
            {
                hal_sysdie("testobjsmgr kmempool_new err");
            }
            printfk("objs alloc adsz[%x] sz:%x adr:%x\n\r",i,adsz[i].sz,adsz[i].adr);
            adrbytp=(u8_t*)adsz[i].adr;
            bytval=(u8_t)(adsz[i].adr&0xff);
            for(size_t k=0;k<adsz[i].sz;k++)
            {
                adrbytp[k]=bytval;
            }
        }
        cmp_adrsz(adsz,64);
        for(int j=0;j<64;j++)
        {
            if(kmempool_delete(adsz[j].adr,adsz[j].sz)==FALSE)
            {
                hal_sysdie("testobjsmgr kmempool_delete err");
            }
            printfk("objs delete adsz[%x] sz:%x adr:%x\n\r",j,adsz[j].sz,adsz[j].adr);
        }
    }
    printfk("oskmempool.mp_obmplnr:%x\n\r",oskmempool.mp_obmplnr);
    return;
}

void testpagemgr()
{
    adrsz_t adsz[30];
    size_t alcsz=0x1000;
    for(;alcsz<0x19000;alcsz+=0x1000)
    {
        for(int i=0;i<30;i++)
        {
            adsz[i].sz=alcsz;
            adsz[i].adr=kmempool_new(alcsz);
            if(adsz[i].adr==NULL)
            {
                hal_sysdie("testpagemgr kmempool_new err");
            }
            printfk("adsz[%x] sz:%x adr:%x\n\r",i,adsz[i].sz,adsz[i].adr);
        }
        cmp_adrsz(adsz,30);
        for(int j=0;j<30;j++)
        {
            if(kmempool_delete(adsz[j].adr,adsz[j].sz)==FALSE)
            {
                hal_sysdie("testpagemgr kmempool_delete err");
            }
            printfk("delete adsz[%x] sz:%x adr:%x\n\r",j,adsz[j].sz,adsz[j].adr);
        }
    }
    printfk("oskmempool.mp_pgmplnr:%x\n\r",oskmempool.mp_pgmplnr);
    return;
}

void init_krlpagempol()
{
    kmempool_t_init(&oskmempool);
    //testobjsmgr();
    return;
}

void kmempool_t_init(kmempool_t* initp)
{
    hal_spinlock_init(&initp->mp_lock);
    list_init(&initp->mp_list);
    initp->mp_stus=0;
    initp->mp_flgs=0;
    hal_spinlock_init(&initp->mp_pglock);
    hal_spinlock_init(&initp->mp_oblock);
    initp->mp_pgmplnr=0;
    initp->mp_obmplnr=0;
    list_init(&initp->mp_pgmplmheadl);
    list_init(&initp->mp_obmplmheadl);
    initp->mp_pgmplmhcach=NULL;
    initp->mp_obmplmhcach=NULL;
#ifdef CFG_X86_PLATFORM
    for(uint_t i=0;i<PHYMSA_MAX;i++)
    {
        list_init(&initp->mp_msalsthead[i]);
    } 
#endif
    return;
}

#ifdef CFG_S3C2440A_PLATFORM
adr_t kmempool_page_new_callhalmm(size_t msize)
{
    if(msize<=BLK128KB_SIZE)
    {
        return hal_memallocblks(BLK128KB_SIZE);
    }
    if(msize<=BLK256KB_SIZE)
    {
        return hal_memallocblks(BLK256KB_SIZE);
    }
    if(msize<=BLK512KB_SIZE)
    {
        return hal_memallocblks(BLK512KB_SIZE);
    }
    if(msize<=BLK1MB_SIZE)
    {
        return hal_memallocblks(BLK1MB_SIZE);
    }
    if(msize<=BLK2MB_SIZE)
    {
        return hal_memallocblks(BLK2MB_SIZE);
    }
    if(msize<=BLK4MB_SIZE)
    {
        return hal_memallocblks(BLK4MB_SIZE);
    }
    return NULL;
}


bool_t kmempool_page_delete_callhalmm(adr_t fradr,size_t frze)
{
    if(frze<=BLK128KB_SIZE)
    {
        return hal_memfreeblks(fradr,BLK128KB_SIZE);
    }
    if(frze<=BLK256KB_SIZE)
    {
        return hal_memfreeblks(fradr,BLK256KB_SIZE);
    }
    if(frze<=BLK512KB_SIZE)
    {
        return hal_memfreeblks(fradr,BLK512KB_SIZE);
    }
    if(frze<=BLK1MB_SIZE)
    {
        return hal_memfreeblks(fradr,BLK1MB_SIZE);
    }
    if(frze<=BLK2MB_SIZE)
    {
        return hal_memfreeblks(fradr,BLK2MB_SIZE);
    }
    if(frze<=BLK4MB_SIZE)
    {
        return hal_memfreeblks(fradr,BLK4MB_SIZE);
    }
    return FALSE;

}

void mplhead_t_init(mplhead_t* initp)
{
    hal_spinlock_init(&initp->mh_lock);
    list_init(&initp->mh_list);
    initp->mh_hedty=0;
    initp->mh_start=0;
    initp->mh_end=0;
    initp->mh_firtfreadr=NULL;
    initp->mh_firtpmap=NULL;
    initp->mh_objnr=0;
    initp->mh_aliobsz=0;
    initp->mh_objsz=0;
    initp->mh_nxtpsz=0;
    initp->mh_afindx=0;
    initp->mh_pmnr=0;
    initp->mh_pmap=(pglmap_t*)(((uint_t)initp)+sizeof(mplhead_t));
    return;
}

bool_t objs_delete_on_mplhead(mplhead_t* mplhdp,adr_t fradr)
{
    if(mplhdp->mh_afindx<1||fradr<(mplhdp->mh_start+sizeof(mplhead_t))||
    (fradr+mplhdp->mh_aliobsz)>=mplhdp->mh_end)
    {
        return FALSE;
    }
    adr_t retadr=NULL,*nextp=NULL,adrsz=(adr_t)(mplhdp->mh_aliobsz);
    nextp=(adr_t*)(fradr+adrsz);
    
    if(*nextp!=NULL)
    {
        return FALSE;
    }
    
    retadr=mplhdp->mh_firtfreadr;
    mplhdp->mh_firtfreadr=fradr;
    *nextp=retadr;
    
    mplhdp->mh_afindx--;
    return TRUE;    
}

adr_t objs_new_on_mplhead(mplhead_t* mplhdp)
{
    if(mplhdp->mh_afindx>=mplhdp->mh_objnr||mplhdp->mh_firtfreadr==NULL)
    {
        return NULL;
    }
    adr_t retadr=NULL,*nextp=NULL,adrsz=(adr_t)(mplhdp->mh_aliobsz);
   
    retadr=mplhdp->mh_firtfreadr;
    nextp=(adr_t*)(retadr+adrsz);
    mplhdp->mh_firtfreadr=*nextp;
    *nextp=NULL;
    mplhdp->mh_afindx++;
    return retadr;
}



bool_t page_delete_on_mplhead(mplhead_t* mplhdp,adr_t fradr)
{
    pglmap_t* map;
    if(mplhdp->mh_afindx<1||mplhdp->mh_pmnr<1)
    {
        return FALSE;
    }
    for(uint_t i=0;i<mplhdp->mh_pmnr;i++)
    {
        if(fradr==mplhdp->mh_pmap[i].pgl_start)
        {
            map=&mplhdp->mh_pmap[i];
            if(map->pgl_next!=NULL)
            {
                return FALSE;
            }
            goto del_step;
        }
    }
    return FALSE;
del_step:
    map->pgl_next=mplhdp->mh_firtpmap;
    mplhdp->mh_firtpmap=map;
    mplhdp->mh_afindx--;
    return TRUE;    
}

adr_t page_new_on_mplhead(mplhead_t* mplhdp)
{
    pglmap_t* map;
    if(mplhdp->mh_afindx>=mplhdp->mh_objnr)
    {
        return NULL;
    }
    if(mplhdp->mh_firtpmap!=NULL)
    {
        map=mplhdp->mh_firtpmap;
        mplhdp->mh_firtpmap=map->pgl_next;
        map->pgl_next=NULL;
        
        mplhdp->mh_afindx++;
        return map->pgl_start;
        
    }
    return NULL;
}
mplhead_t* objs_mpool_init(kmempool_t* kmplockp,mplhead_t* initp,size_t msize,adr_t start,adr_t end)
{
    if(((start&0xfff)!=0)||((end-start)<(PAGE_SIZE-1)))
    {
        return NULL;
    }
    
    adr_t sadr=start+sizeof(mplhead_t);
    if((sadr&3)!=0)
    {
        hal_sysdie("objs_mpool_init:sadr not align dword");
        return NULL;
    }
    
    uint_t objnr=0;
    mplhead_t_init(initp);
    initp->mh_hedty=MPLHTY_OBJS;
    initp->mh_start=start;
    initp->mh_end=end;
    initp->mh_firtfreadr=sadr;
    initp->mh_aliobsz=msize;
    initp->mh_objsz=msize;
    initp->mh_nxtpsz=msize+sizeof(adr_t);
    adr_t* nexp=NULL;
    adr_t adrsz=msize;
    adr_t npsz=initp->mh_nxtpsz;
    
    if((initp->mh_nxtpsz&3)!=0)
    {
        hal_sysdie("objs_mpool_init:initp->mh_nxtpsz not align dword");
        return NULL;
    }
    
    for(;;)
    {
        if((sadr+npsz-1)>end)
        {
            break; 
        }
        nexp=(adr_t*)(sadr+adrsz);
        *nexp=(sadr+npsz);
       
        sadr+=npsz;
        
        objnr++;
    }
    
    if(objnr==0)
    {
        hal_sysdie("objs_mpool_init:objnr err");
        return NULL;
    } 
    sadr-=npsz;
    nexp=(adr_t*)(sadr+adrsz);
    *nexp=NULL;
    
    initp->mh_objnr=objnr;
    list_add(&initp->mh_list,&kmplockp->mp_obmplmheadl);
    kmplockp->mp_obmplnr++;
    return initp;
    
}


mplhead_t* page_mpool_init(kmempool_t* kmplockp,mplhead_t* initp,size_t msize,adr_t start,adr_t end)
{
    if(((start&0xfff)!=0)||((end-start)<((PAGE_SIZE*2)-1)))
    {
        return NULL;
    }
    adr_t sadr=start+PAGE_SIZE;
    uint_t pi=0,pnr=0;
    mplhead_t_init(initp);
    initp->mh_hedty=MPLHTY_PAGE;
    initp->mh_start=start;
    initp->mh_end=end;
    initp->mh_aliobsz=msize;
    initp->mh_objsz=msize;
    
    for(;;)
    {
        if((sadr+msize-1)>end)
        {
            break; 
        }
        initp->mh_pmap[pi].pgl_start=sadr;
        initp->mh_pmap[pi].pgl_next=&(initp->mh_pmap[pi+1]);
        sadr+=msize;
        pi++;
    }
    
    if(pi>0)
    {
        initp->mh_pmap[pi-1].pgl_next=NULL;
        pnr=pi;
        initp->mh_firtpmap=&(initp->mh_pmap[0]);
        goto add_step;
    }
    initp->mh_pmap[pi].pgl_next=NULL;
    initp->mh_pmap[pi].pgl_start=NULL;
    pnr=pi;
    
add_step:
    initp->mh_objnr=pnr;
    initp->mh_pmnr=pnr;
    list_add(&initp->mh_list,&kmplockp->mp_pgmplmheadl);
    kmplockp->mp_pgmplnr++;
    return initp;
}

bool_t del_objs_mpool(kmempool_t* kmplockp,mplhead_t* mphdp)
{
    if(mphdp->mh_afindx>0)
    {
        return TRUE;
    }
    size_t frsz=mphdp->mh_end-mphdp->mh_start+1;
    adr_t fradr=mphdp->mh_start;
    list_del(&mphdp->mh_list);
    if(kmplockp->mp_obmplnr<1)
    {
        hal_sysdie("del_objs_mpool kmplockp->mp_obmplnr<1");
    }
    kmplockp->mp_obmplnr--;
    if(kmplockp->mp_obmplmhcach==mphdp)
    {
        kmplockp->mp_obmplmhcach=NULL;
    }
    if(kmempool_pages_delete(fradr,frsz)==FALSE)
    {
        hal_sysdie("del_objs_mpool page delete err");
    }
    return TRUE;
}

bool_t del_page_mpool(kmempool_t* kmplockp,mplhead_t* mphdp)
{
    if(mphdp->mh_afindx>0)
    {
        return TRUE;
    }
    size_t frsz=mphdp->mh_end-mphdp->mh_start+1;
    adr_t fradr=mphdp->mh_start;
    list_del(&mphdp->mh_list);
    if(kmplockp->mp_pgmplnr<1)
    {
        hal_sysdie("del_page_mpool kmplockp->mp_pgmplnr<1");
    }
    kmplockp->mp_pgmplnr--;
    if(kmplockp->mp_pgmplmhcach==mphdp)
    {
        kmplockp->mp_pgmplmhcach=NULL;
    }
    if(hal_memfreeblks(fradr,frsz)==FALSE)
    {
        hal_sysdie("del_page_mpool hal_memfreeblks err");
    }
    return TRUE;
}


mplhead_t* new_objs_mpool(kmempool_t* kmplockp,size_t msize)
{
    mplhead_t* mphdp=NULL;
    adr_t pgadr=kmempool_pages_new(0x4000);
    if(pgadr==NULL)
    {
        return NULL;
    }
    mphdp=(mplhead_t*)pgadr;
    mphdp=objs_mpool_init(kmplockp,mphdp,msize,pgadr,(pgadr+0x4000-1));
    if(mphdp==NULL)
    {
        hal_sysdie("new objs mpool err");
    }
    return mphdp;
}



mplhead_t* new_page_mpool(kmempool_t* kmplockp,size_t msize)
{
    mplhead_t* mphdp=NULL;
    size_t pgnr=msize>>12;
    adr_t blkadr=NULL;
    if(pgnr<1)
    {
        return NULL;
    }
    
    if(pgnr<=2)
    {
        blkadr=hal_memallocblks(BLK128KB_SIZE);
        if(blkadr==NULL)
        {
            return NULL;
        }
        mphdp=page_mpool_init(kmplockp,(mplhead_t*)blkadr,msize,blkadr,(blkadr+BLK128KB_SIZE-1));
        if(mphdp==NULL)
        {
            hal_sysdie("new pg mpool err 1");
        }
        return mphdp;
    }
    
    if(pgnr<=4)
    {
        blkadr=hal_memallocblks(BLK256KB_SIZE);
        if(blkadr==NULL)
        {
            return NULL;
        }
        mphdp=page_mpool_init(kmplockp,(mplhead_t*)blkadr,msize,blkadr,(blkadr+BLK256KB_SIZE-1));
        if(mphdp==NULL)
        {
            hal_sysdie("new pg mpool err 2");
        }
        return mphdp;
    }
    
    if(pgnr<=8)
    {
        blkadr=hal_memallocblks(BLK256KB_SIZE);
        if(blkadr==NULL)
        {
            return NULL;
        }
        mphdp=page_mpool_init(kmplockp,(mplhead_t*)blkadr,msize,blkadr,(blkadr+BLK256KB_SIZE-1));
        if(mphdp==NULL)
        {
            hal_sysdie("new pg mpool err 3");
        }
        return mphdp;
    }
    
    if(pgnr<=16)
    {
        blkadr=hal_memallocblks(BLK256KB_SIZE);
        if(blkadr==NULL)
        {
            return NULL;
        }
        mphdp=page_mpool_init(kmplockp,(mplhead_t*)blkadr,msize,blkadr,(blkadr+BLK256KB_SIZE-1));
        if(mphdp==NULL)
        {
            hal_sysdie("new pg mpool err 4");
        }
        return mphdp;
    }
    
    if(pgnr<=31)
    {
        blkadr=hal_memallocblks(BLK128KB_SIZE);
        if(blkadr==NULL)
        {
            return NULL;
        }
        mphdp=page_mpool_init(kmplockp,(mplhead_t*)blkadr,msize,blkadr,(blkadr+BLK128KB_SIZE-1));
        if(mphdp==NULL)
        {
            hal_sysdie("new pg mpool err 5");
        }
        return mphdp;
    }
    
    return NULL;
}


mplhead_t* objsdel_mplhead_isok(mplhead_t* mhp,adr_t fradr,size_t msize)
{
    if(mhp->mh_hedty!=MPLHTY_OBJS)
    {
        return NULL;
    }
    if(mhp->mh_aliobsz!=msize)
    {
        return NULL;
    }
    if(mhp->mh_afindx==0)
    {
        return NULL;
    }
    if(fradr<(mhp->mh_start+sizeof(mplhead_t))||(fradr+msize-1)>mhp->mh_end)
    {
        return NULL;
    }
    return mhp;
}



mplhead_t* pagedel_mplhead_isok(mplhead_t* mhp,adr_t fradr,size_t msize)
{
    if(mhp->mh_hedty!=MPLHTY_PAGE)
    {
        return NULL;
    }
    if(mhp->mh_aliobsz!=msize)
    {
        return NULL;
    }
    if(mhp->mh_afindx==0)
    {
        return NULL;
    }
    if(fradr<(mhp->mh_start+PAGE_SIZE)||(fradr+msize-1)>mhp->mh_end)
    {
        return NULL;
    }
    return mhp;
}

mplhead_t* objsnew_mplhead_isok(mplhead_t* mhp,size_t msize)
{

    if(mhp->mh_firtfreadr==NULL)
    {
        return NULL;
    }
    if(mhp->mh_hedty!=MPLHTY_OBJS)
    {
        return NULL;
    }
    if(mhp->mh_aliobsz!=msize)
    {
        return NULL;
    }
    if(mhp->mh_afindx>=mhp->mh_objnr)
    {
        return NULL;
    }
    return mhp;
}

mplhead_t* pagenew_mplhead_isok(mplhead_t* mhp,size_t msize)
{
    if(mhp->mh_firtpmap==NULL)
    {
        return NULL;
    }
    if(mhp->mh_hedty!=MPLHTY_PAGE)
    {
        return NULL;
    }
    if(mhp->mh_aliobsz!=msize)
    {
        return NULL;
    }
    if(mhp->mh_afindx>=mhp->mh_objnr)
    {
        return NULL;
    }
    return mhp;
}

mplhead_t* kmemplob_retn_mplhead(kmempool_t* kmplockp,size_t msize)
{
    mplhead_t* retmhp;
    list_h_t* list;
    if(kmplockp->mp_obmplmhcach!=NULL)
    {
        retmhp=kmplockp->mp_obmplmhcach;
        retmhp=objsnew_mplhead_isok(retmhp,msize);
        if(retmhp!=NULL)
        {
            return retmhp;
        }
    }
    list_for_each(list,&kmplockp->mp_obmplmheadl)
    {
        retmhp=list_entry(list,mplhead_t,mh_list);
        retmhp=objsnew_mplhead_isok(retmhp,msize);
        if(retmhp!=NULL)
        {
            kmplockp->mp_obmplmhcach=retmhp;
            return retmhp;
        }
    }
    return NULL;
}

mplhead_t* kmempldelob_retn_mplhead(kmempool_t* kmplockp,adr_t fradr,size_t msize)
{
    mplhead_t* retmhp;
    list_h_t* list;
    if(kmplockp->mp_obmplmhcach!=NULL)
    {
        retmhp=kmplockp->mp_obmplmhcach;
        retmhp=objsdel_mplhead_isok(retmhp,fradr,msize);
        if(retmhp!=NULL)
        {
            return retmhp;
        }
    }
    list_for_each(list,&kmplockp->mp_obmplmheadl)
    {
        retmhp=list_entry(list,mplhead_t,mh_list);
        retmhp=objsdel_mplhead_isok(retmhp,fradr,msize);
        if(retmhp!=NULL)
        {
            return retmhp;
        }
    }
    return NULL;
}

mplhead_t* kmempldelpg_retn_mplhead(kmempool_t* kmplockp,adr_t fradr,size_t msize)
{
    mplhead_t* retmhp;
    list_h_t* list;
    if(kmplockp->mp_pgmplmhcach!=NULL)
    {
        retmhp=kmplockp->mp_pgmplmhcach;
        retmhp=pagedel_mplhead_isok(retmhp,fradr,msize);
        if(retmhp!=NULL)
        {
            return retmhp;
        }
    }
    list_for_each(list,&kmplockp->mp_pgmplmheadl)
    {
        retmhp=list_entry(list,mplhead_t,mh_list);
        retmhp=pagedel_mplhead_isok(retmhp,fradr,msize);
        if(retmhp!=NULL)
        {
            return retmhp;
        }
    }
    return NULL;
}

mplhead_t* kmemplpg_retn_mplhead(kmempool_t* kmplockp,size_t msize)
{
    mplhead_t* retmhp;
    list_h_t* list;
    if(kmplockp->mp_pgmplmhcach!=NULL)
    {
        retmhp=kmplockp->mp_pgmplmhcach;
        retmhp=pagenew_mplhead_isok(retmhp,msize);
        if(retmhp!=NULL)
        {
            return retmhp;
        }
    }
    list_for_each(list,&kmplockp->mp_pgmplmheadl)
    {
        retmhp=list_entry(list,mplhead_t,mh_list);
        retmhp=pagenew_mplhead_isok(retmhp,msize);
        if(retmhp!=NULL)
        {
            kmplockp->mp_pgmplmhcach=retmhp;
            return retmhp;
        }
    }
    return NULL;
}
#endif

void msadsc_add_kmempool(kmempool_t* kmplp,msadsc_t* msa,uint_t relpnr)
{
    if(NULL==kmplp||NULL==msa||1>relpnr)
    {
        system_error("msadsc_add_kmempool fail\n");
    }
    cpuflg_t cpuflg;
    hal_spinlock_saveflg_cli(&kmplp->mp_lock,&cpuflg);
    if((PHYMSA_MAX-1)<=relpnr)
    {
        list_add(&msa->md_list,&kmplp->mp_msalsthead[PHYMSA_MAX-1]);
    }
    else
    {
        list_add(&msa->md_list,&kmplp->mp_msalsthead[relpnr]);
    }
    hal_spinunlock_restflg_sti(&kmplp->mp_lock,&cpuflg);
    return;
}

msadsc_t* msadsc_del_kmempool(kmempool_t* kmplp,uint_t relpnr,adr_t fradr)
{
    if(NULL==kmplp||1>relpnr||NULL==fradr)
    {
        return NULL;
    }
    msadsc_t* tmpmsa=NULL,*retmsa=NULL;
    list_h_t* tmplst;
    cpuflg_t cpuflg;
    hal_spinlock_saveflg_cli(&kmplp->mp_lock,&cpuflg);
    if((PHYMSA_MAX-1)<=relpnr)
    {
        list_for_each(tmplst,&kmplp->mp_msalsthead[PHYMSA_MAX-1]);
        {
            tmpmsa=list_entry(tmplst,msadsc_t,md_list);
            if(fradr==(tmpmsa->md_phyadrs.paf_padrs<<12))
            {
                list_del(&tmpmsa->md_list);
                retmsa=tmpmsa;
                goto ret_step;
            }
        }
    }
    else
    {
        list_for_each(tmplst,&kmplp->mp_msalsthead[relpnr]);
        {
            tmpmsa=list_entry(tmplst,msadsc_t,md_list);
            if(fradr==(tmpmsa->md_phyadrs.paf_padrs<<12))
            {
                list_del(&tmpmsa->md_list);
                retmsa=tmpmsa;
                goto ret_step;
            }
        }
    }
    retmsa=NULL;
ret_step:
    hal_spinunlock_restflg_sti(&kmplp->mp_lock,&cpuflg);  
    return retmsa; 
}

adr_t kmempool_pages_core_new(size_t msize)
{
#ifdef CFG_S3C2440A_PLATFORM
    cpuflg_t cpufg;
    mplhead_t* mplhdp;
    adr_t retadr=NULL;
    kmempool_t* kmplp=&oskmempool;
    hal_spinlock_saveflg_cli(&kmplp->mp_pglock,&cpufg);
    mplhdp=kmemplpg_retn_mplhead(kmplp,msize);
    if(mplhdp==NULL)
    {
        mplhdp=new_page_mpool(kmplp,msize);
        if(mplhdp==NULL)
        {
            retadr=NULL;
            goto return_step;
        }
    }
    retadr=page_new_on_mplhead(mplhdp);
return_step:
    hal_spinunlock_restflg_sti(&kmplp->mp_pglock,&cpufg);
    return retadr;
#endif
#ifdef CFG_X86_PLATFORM
    kmempool_t* kmplp=&oskmempool;
    uint_t relpnr=0;
    msadsc_t* retmsa=NULL;
    retmsa=mm_division_pages(&lmos_memmgrob,msize>>12,&relpnr, MA_TYPE_KRNL,DMF_RELDIV);
    if(NULL==retmsa)
    {
        return NULL;
    }
    msadsc_add_kmempool(kmplp,retmsa,relpnr);
    return (adr_t)(retmsa->md_phyadrs.paf_padrs<<12);
#endif
}

bool_t kmempool_pages_core_delete(adr_t fradr,size_t frsz)
{
#ifdef CFG_S3C2440A_PLATFORM
    cpuflg_t cpufg;
    mplhead_t* mplhdp;
    bool_t rets=FALSE;
    kmempool_t* kmplp=&oskmempool;
    hal_spinlock_saveflg_cli(&kmplp->mp_pglock,&cpufg);
    mplhdp=kmempldelpg_retn_mplhead(kmplp,fradr,frsz);
    if(mplhdp==NULL)
    {
        rets=FALSE;
        goto return_step;
    }
    
    if(page_delete_on_mplhead(mplhdp,fradr)==FALSE)
    {
        rets=FALSE;
        goto return_step;
    }
    if(del_page_mpool(kmplp,mplhdp)==FALSE)
    {
        rets=FALSE;
        goto return_step;
    }
    rets=TRUE;
return_step:
    hal_spinunlock_restflg_sti(&kmplp->mp_pglock,&cpufg);
    return rets;
#endif

#ifdef CFG_X86_PLATFORM
    kmempool_t* kmplp=&oskmempool;
    uint_t relpnr=frsz>>12;
    msadsc_t* retmsa=NULL;
    retmsa=msadsc_del_kmempool(kmplp,relpnr,fradr);
    if(NULL==retmsa)
    {
        return FALSE;
    }
    return mm_merge_pages(&lmos_memmgrob,retmsa,relpnr);
#endif
}

adr_t kmempool_objsz_core_new(size_t msize)
{
#ifdef CFG_S3C2440A_PLATFORM
    adr_t retadr=NULL;
    cpuflg_t cpufg;
    mplhead_t* mplhdp;
    kmempool_t* kmplp=&oskmempool;
    hal_spinlock_saveflg_cli(&kmplp->mp_oblock,&cpufg);
    mplhdp=kmemplob_retn_mplhead(kmplp,msize);
    if(mplhdp==NULL)
    {
        mplhdp=new_objs_mpool(kmplp,msize);
        if(mplhdp==NULL)
        {
            retadr=NULL;
            goto return_step;
        }   
    }
    retadr=objs_new_on_mplhead(mplhdp);
return_step:
    hal_spinunlock_restflg_sti(&kmplp->mp_oblock,&cpufg);
    return retadr;
#endif
#ifdef CFG_X86_PLATFORM
    return (adr_t)kmsob_new(msize);
#endif
}

bool_t kmempool_objsz_core_delete(adr_t fradr,size_t frsz)
{
#ifdef CFG_S3C2440A_PLATFORM
    bool_t rets=FALSE;
    cpuflg_t cpufg;
    mplhead_t* mplhdp;
    kmempool_t* kmplp=&oskmempool;
    hal_spinlock_saveflg_cli(&kmplp->mp_oblock,&cpufg);
    mplhdp=kmempldelob_retn_mplhead(kmplp,fradr,frsz);
    if(mplhdp==NULL)
    {
        rets=FALSE;
        goto return_step;
    }
    if(objs_delete_on_mplhead(mplhdp,fradr)==FALSE)
    {
        rets=FALSE;
        goto return_step;
    }
    if(del_objs_mpool(kmplp,mplhdp)==FALSE)
    {
        rets=FALSE;
        goto return_step;
    }
    rets=TRUE;
return_step:
    hal_spinunlock_restflg_sti(&kmplp->mp_oblock,&cpufg);
    return rets;
#endif
#ifdef CFG_X86_PLATFORM
    return kmsob_delete((void*)fradr,frsz);
#endif
}

adr_t kmempool_objsz_new(size_t msize)
{
    size_t sz=OBJS_ALIGN(msize);
    if(sz>OBJSORPAGE)
    {
        return NULL;
    }
    return kmempool_objsz_core_new(sz);
}

bool_t kmempool_objsz_delete(adr_t fradr,size_t frsz)
{
    size_t fsz=OBJS_ALIGN(frsz);
    if(fsz>OBJSORPAGE)
    {
        return FALSE;
    }
    return kmempool_objsz_core_delete(fradr,fsz);
}

adr_t kmempool_pages_new(size_t msize)
{
    size_t sz=PAGE_ALIGN(msize);
#ifdef CFG_S3C2440A_PLATFORM
    if(sz>KPMPORHALM)
    {
        return kmempool_page_new_callhalmm(sz);
    }
#endif
    return kmempool_pages_core_new(sz);
}

bool_t kmempool_pages_delete(adr_t fradr,size_t frsz)
{
    size_t sz=PAGE_ALIGN(frsz);
#ifdef CFG_S3C2440A_PLATFORM
    if(sz>KPMPORHALM)
    {
        return kmempool_page_delete_callhalmm(fradr,sz);
    }
#endif
    return kmempool_pages_core_delete(fradr,sz);
}

adr_t kmempool_onsize_new(size_t msize)
{


    if(msize>OBJSORPAGE)
    {
        return kmempool_pages_new(msize);
    }
    return kmempool_objsz_new(msize);
}

bool_t kmempool_onsize_delete(adr_t fradr,size_t frsz)
{
    if(frsz>OBJSORPAGE)
    {
        return kmempool_pages_delete(fradr,frsz);
    }
    return kmempool_objsz_delete(fradr,frsz);
}

adr_t kmempool_new(size_t msize)
{
    if(msize<KMEMPALCSZ_MIN||msize>KMEMPALCSZ_MAX)
    {
        return NULL;
    }
    
    return kmempool_onsize_new(msize);
}

bool_t kmempool_delete(adr_t fradr,size_t frsz)
{
    if(fradr==NULL||frsz<KMEMPALCSZ_MIN||frsz>KMEMPALCSZ_MAX)
    {
        return FALSE;
    }
    return kmempool_onsize_delete(fradr,frsz);
}
