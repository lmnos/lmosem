/**********************************************************
        物理内存管理器初始化文件memmgrinit.c
***********************************************************
                彭东 ＠ 2014.02.09.18.00
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"


/*void test_bits()
 {
 	for(uint_t i=1;i<20;i++)
 	{
 		kprint("pgnr:%d retoder:%d\n",i,retn_oder(i));
 	}
 	return;
 }*/
PUBLIC LKINIT void init_memmgr()
{
	init_msadsc();
	init_memarea();
	init_copy_pagesfvm();
	init_search_krloccupymm(&kmachbsp);
	init_merlove_mem();
	init_memmgrob();
	init_kmsob();
	//test_divsion_pages();
	//test_kmsob();
	//free_all_mchkstuc();
    //free_all_kobcks();
	//disp_memmgrob();
	//kprint("init_memmgr OK!\n");
	//test_bits();
	//kirfdata->kirf_retstus=KIFR_OK;
	return;
}

void disp_memmgrob()
{
	/*msadsc_t* retmsa=NULL;
	uint_t pnr=0;
	uint_t stsc=0,etsc=0;
	stsc=x86_rdtsc();
	retmsa=mm_division_pages(&lmos_memmgrob,2,&pnr,MA_TYPE_KRNL,DMF_RELDIV);
	etsc=x86_rdtsc();
	if(NULL==retmsa)
	{
		system_error("mm_division_pages fail\n");
	}
	list_add(&retmsa->md_list,&lmos_memmgrob.mo_list);

	kprint("所分配连续物理内存页面的首地址:%x,连续物理内存页面数:%x,连续物理内存大小:%dMB,执行内存分配函数所用的CPU时钟周期:%d\n",
		retmsa->md_phyadrs.paf_padrs<<12,pnr,(pnr<<12)>>20,etsc-stsc);
	*/
	test_divsion_pages();
	/*kprint("系统物理内存总量:%d页面 :%d逼 :%d兆逼\n",lmos_memmgrob.mo_maxpages,lmos_memmgrob.mo_memsz,lmos_memmgrob.mo_memsz>>20);
	kprint("使用物理内存总量:%d页面 :%d逼 :%d兆逼\n",lmos_memmgrob.mo_alocpages,lmos_memmgrob.mo_alocpages<<PSHRSIZE,(lmos_memmgrob.mo_alocpages<<PSHRSIZE)>>20);
	kprint("剩余物理内存总量:%d页面 :%d逼 :%d兆逼\n",lmos_memmgrob.mo_freepages,lmos_memmgrob.mo_freepages<<PSHRSIZE,(lmos_memmgrob.mo_freepages<<PSHRSIZE)>>20);
	*/
	//kprint("其实还可以有G逼,这里没有逗逼,哈哈哈哈哈~~~~\n");
	return;
}

PUBLIC void init_memmgrob()
{
	machbstart_t* mbsp=&kmachbsp;
	memmgrob_t* mobp=&lmos_memmgrob;
	memmgrob_t_init(mobp);
	if(NULL==mbsp->mb_e820expadr||0==mbsp->mb_e820exnr)
	{
		system_error("mbsp->mb_e820expadr==NULL\n");
	}
	if(NULL==mbsp->mb_memmappadr||0==mbsp->mb_memmapnr)
	{
		system_error("mbsp->mb_memmappadr==NULL\n");
	}
	if(NULL==mbsp->mb_memznpadr||0==mbsp->mb_memznnr)
	{
		system_error("mbsp->mb_memznpadr==NULL\n");
	}
	mobp->mo_pmagestat=(phymmarge_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_e820expadr);
	mobp->mo_pmagenr=mbsp->mb_e820exnr;
	mobp->mo_msadscstat=(msadsc_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_memmappadr);
	mobp->mo_msanr=mbsp->mb_memmapnr;
	mobp->mo_mareastat=(memarea_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_memznpadr);
	mobp->mo_mareanr=mbsp->mb_memznnr;
	mobp->mo_memsz=mbsp->mb_memmapnr<<PSHRSIZE;
	mobp->mo_maxpages=mbsp->mb_memmapnr;
	uint_t aidx=0;
	for(uint_t i=0;i<mobp->mo_msanr;i++)
	{
		if(1==mobp->mo_msadscstat[i].md_indxflgs.mf_uindx&&
			MF_MOCTY_KRNL==mobp->mo_msadscstat[i].md_indxflgs.mf_mocty&&
			PAF_ALLOC==mobp->mo_msadscstat[i].md_phyadrs.paf_alloc)
		{
			aidx++;
		}
	}
	mobp->mo_alocpages=aidx;
	mobp->mo_freepages=mobp->mo_maxpages-mobp->mo_alocpages;
	return;

}

PUBLIC void memmgrob_t_init(memmgrob_t* initp)
{
	list_init(&initp->mo_list);
	knl_spinlock_init(&initp->mo_lock);
	initp->mo_stus=0;
	initp->mo_flgs=0;
	//knl_sem_init(&initp->mo_sem,SEM_MUTEX_ONE_LOCK,SEM_FLG_MUTEX);
	initp->mo_memsz=0;
	initp->mo_maxpages=0;
	initp->mo_freepages=0;
	initp->mo_alocpages=0;
	initp->mo_resvpages=0;
	initp->mo_horizline=0;
	initp->mo_pmagestat=NULL;
	initp->mo_pmagenr=0;
	initp->mo_msadscstat=NULL;
	initp->mo_msanr=0;
	initp->mo_mareastat=NULL;
	initp->mo_mareanr=0;
	initp->mo_privp=NULL;
	initp->mo_extp=NULL;
	return;
}


/*PUBLIC bool_t copy_pages_data(machbstart_t* mbsp)
{
	//uint_t tmppgadr=mbsp->mb_pml4padr;
	uint_t topgadr=mbsp->mb_nextwtpadr;
	//uint_t topgsdir=topgadr+0x1000;
	//uint_t* p=(uint_t*)krnlphyiadr_to_viradr((adr_t)topgadr);
	if(initchkadr_is_ok(mbsp, topgadr, mbsp->mb_subpageslen)!=0)
	{
		return FALSE;
	}
	//sint_t retcl=m2mcopy((void*)krnlphyiadr_to_viradr((adr_t)tmppgadr), (void*)krnlphyiadr_to_viradr((adr_t)topgadr),(sint_t)mbsp->mb_subpageslen);
	//if(retcl!=(sint_t)mbsp->mb_subpageslen)
	//{
	//	return FALSE;
	//}
	//p[((KRNL_VIRTUAL_ADDRESS_START)>>KPML4_SHIFT)&0x1ff]=(uint_t)((u32_t)topgsdir|KPML4_RW|KPML4_P);
    //	p[0]=(uint_t)((u32_t)topgsdir|KPML4_RW|KPML4_P);
	//

    	uint_t* p=(uint_t*)krnlphyiadr_to_viradr((adr_t)topgadr);
    	uint_t* pdpte=(uint_t*)(((uint_t)p)+0x1000);
    	uint_t* pde=(uint_t*)(((uint_t)p)+0x2000);
    	for(uint_t mi=0;mi<PGENTY_SIZE;mi++)
    	{
        		p[mi]=0;
        		pdpte[mi]=0;
    	}
    	uint_t adr=0;
    	uint_t pdepd=0;
    	for(uint_t pdei=0;pdei<16;pdei++)
    	{
    		pdepd=(uint_t)krnlvirtadr_to_phyadr((adr_t)pde);
       		pdpte[pdei]=(uint_t)(pdepd|KPDPTE_RW|KPDPTE_P);
        		for(uint_t pdeii=0;pdeii<PGENTY_SIZE;pdeii++)
        		{
           			pde[pdeii]=0|adr|KPDE_PS|KPDE_RW|KPDE_P;
            			adr+=0x200000;
        		}
        		pde=(uint_t*)((uint_t)pde+0x1000);
    	}
    	uint_t pdptepd=(uint_t)krnlvirtadr_to_phyadr((adr_t)pdpte);
    	p[((KRNL_VIRTUAL_ADDRESS_START)>>KPML4_SHIFT)&0x1ff]=(uint_t)(pdptepd|KPML4_RW|KPML4_P);
    	p[0]=(uint_t)(pdptepd|KPML4_RW|KPML4_P);
    	mbsp->mb_pml4padr=topgadr;
    	mbsp->mb_subpageslen=(uint_t)(0x1000*16+0x2000);
	mbsp->mb_kpmapphymemsz=(uint_t)(0x400000000);
	mbsp->mb_nextwtpadr=PAGE_ALIGN(mbsp->mb_pml4padr+mbsp->mb_subpageslen);
	return TRUE;
}*/

PUBLIC bool_t copy_fvm_data(machbstart_t* mbsp,dftgraph_t* dgp)
{
	u64_t tofvadr=mbsp->mb_nextwtpadr;
	if(initchkadr_is_ok(mbsp, tofvadr, dgp->gh_fvrmsz)!=0)
	{
		return FALSE;
	}
	sint_t retcl=m2mcopy((void*)((uint_t)dgp->gh_fvrmphyadr), (void*)krnlphyiadr_to_viradr((adr_t)(tofvadr)), (sint_t)dgp->gh_fvrmsz);
	if(retcl!=(sint_t)dgp->gh_fvrmsz)
	{
		return FALSE;
	}
	dgp->gh_fvrmphyadr=krnlphyiadr_to_viradr((adr_t)tofvadr);
	mbsp->mb_fvrmphyadr=tofvadr;
	mbsp->mb_nextwtpadr=PAGE_ALIGN(tofvadr+dgp->gh_fvrmsz);
	return TRUE;
}

/*PUBLIC  void memi_set_mmutabl(uint_t tblpadr,void* edatap)
{
	set_cr3(tblpadr);
	return;
}*/

PUBLIC void init_copy_pagesfvm()
{
	/*if(copy_pages_data(&kmachbsp)==FALSE)
	{
		system_error("copy_pages_data fail");
	}*/
	if(copy_fvm_data(&kmachbsp,&kdftgh)==FALSE)
	{
		system_error("copy_fvm_data fail");
	}
	//memi_set_mmutabl(kmachbsp.mb_pml4padr, NULL);
	return;
}

/*void disp_msa(msadsc_t* p)
{
	kprint("msadsc_t sz:%d mf_alcidx:%d mf_pgemax:%d mf_lstty:%d\n",sizeof(*p),p->md_flgs.mf_alcidx,
		p->md_flgs.mf_pgemax,p->md_flgs.mf_lstty);	
	return;
}*/