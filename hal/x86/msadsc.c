/**********************************************************
        物理内存空间数组文件msadsc.c
***********************************************************
                彭东 ＠ 2015.05.03.17.00
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"
// msadsc.c 12 line sem
// memarea.c 97 line sem\98 line waitlst 

PUBLIC void msadsc_t_init(msadsc_t* initp)
{
	list_init(&initp->md_list);
	//list_init(&initp->md_lscsmlist);
	knl_spinlock_init(&initp->md_lock);
	initp->md_indxflgs.mf_olkty=MF_OLKTY_INIT;
	initp->md_indxflgs.mf_lstty=MF_LSTTY_LIST;
	initp->md_indxflgs.mf_mocty=MF_MOCTY_FREE;
	initp->md_indxflgs.mf_marty=MF_MARTY_INIT;
	initp->md_indxflgs.mf_uindx=MF_UINDX_INIT;
	initp->md_phyadrs.paf_alloc=PAF_NO_ALLOC;
	initp->md_phyadrs.paf_shared=PAF_NO_SHARED;
	initp->md_phyadrs.paf_swap=PAF_NO_SWAP;
	initp->md_phyadrs.paf_cache=PAF_NO_CACHE;
	initp->md_phyadrs.paf_kmap=PAF_NO_KMAP;
	initp->md_phyadrs.paf_lock=PAF_NO_LOCK;
	initp->md_phyadrs.paf_dirty=PAF_NO_DIRTY;
	initp->md_phyadrs.paf_busy=PAF_NO_BUSY;
	initp->md_phyadrs.paf_rv2=PAF_RV2_VAL;
	initp->md_phyadrs.paf_padrs=PAF_INIT_PADRS;
	initp->md_odlink=NULL;
	return;
}


void disp_one_msadsc(msadsc_t* mp)
{
	//kprint("msadsc_t.md_indxflgs:mf_olkty[%x],mf_lstty[%x],mf_mrv1[%x],mf_uindx[%x]\n",
	//	(uint_t)mp->md_indxflgs.mf_olkty,(uint_t)mp->md_indxflgs.mf_lstty,(uint_t)mp->md_indxflgs.mf_mrv1,(uint_t)mp->md_indxflgs.mf_uindx);
	kprint("msadsc_t.md_f:_ux[%x],_my[%x],md_phyadrs:_alc[%x],_shd[%x],_swp[%x],_che[%x],_kmp[%x],_lck[%x],_dty[%x],_bsy[%x],_padrs[%x]\n",
		(uint_t)mp->md_indxflgs.mf_uindx,(uint_t)mp->md_indxflgs.mf_mocty,(uint_t)mp->md_phyadrs.paf_alloc,(uint_t)mp->md_phyadrs.paf_shared,(uint_t)mp->md_phyadrs.paf_swap,(uint_t)mp->md_phyadrs.paf_cache,(uint_t)mp->md_phyadrs.paf_kmap,(uint_t)mp->md_phyadrs.paf_lock,
		(uint_t)mp->md_phyadrs.paf_dirty,(uint_t)mp->md_phyadrs.paf_busy,(uint_t)(mp->md_phyadrs.paf_padrs<<12));
	return;
}

PUBLIC bool_t ret_msadsc_vadrandsz(machbstart_t* mbsp,msadsc_t** retmasvp,u64_t* retmasnr)
{
	if(NULL==mbsp||NULL==retmasvp||NULL==retmasnr)
	{
		return FALSE;
	}
	if(mbsp->mb_e820exnr<1||NULL==mbsp->mb_e820expadr||(mbsp->mb_e820exnr*sizeof(phymmarge_t))!=mbsp->mb_e820exsz)
	{
		*retmasvp=NULL;
		*retmasnr=0;
		return FALSE;
	}
	phymmarge_t* pmagep=(phymmarge_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_e820expadr);
	u64_t usrmemsz=0,msadnr=0;
	for(u64_t i=0;i<mbsp->mb_e820exnr;i++)
	{
		if(PMR_T_OSAPUSERRAM==pmagep[i].pmr_type)
		{
			usrmemsz+=pmagep[i].pmr_lsize;
			msadnr+=(pmagep[i].pmr_lsize>>12);
		}
	}
	if(0==usrmemsz||(usrmemsz>>12)<1||msadnr<1)
	{
		*retmasvp=NULL;
		*retmasnr=0;
		return FALSE;
	}
	//msadnr=usrmemsz>>12;
	if(0!=initchkadr_is_ok(mbsp,mbsp->mb_nextwtpadr,(msadnr*sizeof(msadsc_t))))
	{
		system_error("ret_msadsc_vadrandsz initchkadr_is_ok err\n");
	}

	*retmasvp=(msadsc_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_nextwtpadr);
	*retmasnr=msadnr;
	return TRUE;
}

PUBLIC void write_one_msadsc(msadsc_t* msap,u64_t phyadr)
{
	msadsc_t_init(msap);
	phyadrflgs_t* tmp=(phyadrflgs_t*)(&phyadr);
	msap->md_phyadrs.paf_padrs=tmp->paf_padrs;
	//(phyadrflgs_t)(phyadr>>12);

	return;
}

PUBLIC LKINIT u64_t init_msadsc_core(machbstart_t* mbsp,msadsc_t* msavstart,u64_t msanr)
{
	phymmarge_t* pmagep=(phymmarge_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_e820expadr);
	//u64_t usrmemsz=0,msadnr=0;
	u64_t mdindx=0;
	for(u64_t i=0;i<mbsp->mb_e820exnr;i++)
	{
		if(PMR_T_OSAPUSERRAM==pmagep[i].pmr_type)
		{

			for(u64_t start=pmagep[i].pmr_saddr;start<pmagep[i].pmr_end;start+=4096)
			{
				if((start+4096-1)<=pmagep[i].pmr_end)
				{
					/*if((start+4096-1)>=0x9f000)
					{
						kprint("(start+4096-1):%x\n",(start+4096-1));
						system_error("(start+4096-1)>0x9f000");
					}*/
					write_one_msadsc(&msavstart[mdindx],start);
					mdindx++;
				}
			}
		}
	}

	return mdindx;
}

PUBLIC LKINIT void init_msadsc()
{
	u64_t coremdnr=0,msadscnr=0;
	msadsc_t* msadscvp=NULL;
	machbstart_t* mbsp=&kmachbsp;
	if(ret_msadsc_vadrandsz(mbsp,&msadscvp,&msadscnr)==FALSE)
	{
		system_error("init_msadsc ret_msadsc_vadrandsz err\n");
	}
	coremdnr=init_msadsc_core(mbsp,msadscvp,msadscnr);
	if(coremdnr!=msadscnr)
	{
		system_error("init_msadsc init_msadsc_core err\n");
	}
	mbsp->mb_memmappadr=krnlvirtadr_to_phyadr((adr_t)msadscvp);
	mbsp->mb_memmapnr=coremdnr;
	mbsp->mb_memmapsz=coremdnr*sizeof(msadsc_t);
	mbsp->mb_nextwtpadr=PAGE_ALIGN(mbsp->mb_memmappadr+mbsp->mb_memmapsz);
	//kprint("msadscvp[%x],msadscnr[%x],inmemsz[%x]mb,coremdnr[%x]\n",(uint_t)msadscvp,msadscnr,(msadscnr*sizeof(msadsc_t))>>20,coremdnr);
	//disp_phymsadsc();
	//die(0);
	return;
}


void disp_phymsadsc()
{
	u64_t coremdnr=0;
	msadsc_t* msadscvp=NULL;
	machbstart_t* mbsp=&kmachbsp;

	msadscvp=(msadsc_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_memmappadr);
	coremdnr=mbsp->mb_memmapnr;

	for (int i = 0; i < 10; ++i)
	{
		disp_one_msadsc(&msadscvp[i]);
	}

	for (u64_t i = coremdnr/2; i < coremdnr/2+10; ++i)
	{
		disp_one_msadsc(&msadscvp[i]);
	}

	for (u64_t i = coremdnr-10; i < coremdnr; ++i)
	{
		disp_one_msadsc(&msadscvp[i]);
	}
	return;
}

PUBLIC u64_t search_segment_occupymsadsc(msadsc_t* msastart,u64_t msanr,u64_t ocpystat,u64_t ocpyend)
{
	u64_t mphyadr=0,fsmsnr=0;
	msadsc_t* fstatmp=NULL;
	for(u64_t mnr=0;mnr<msanr;mnr++)
	{
		if((msastart[mnr].md_phyadrs.paf_padrs<<PSHRSIZE)==ocpystat)
		{
			fstatmp=&msastart[mnr];
			goto step1;
		}
	}
step1:
	fsmsnr=0;
	if(NULL==fstatmp)
	{
		return 0;
	}
	for(u64_t tmpadr=ocpystat;tmpadr<ocpyend;tmpadr+=PAGESIZE,fsmsnr++)
	{
		mphyadr=fstatmp[fsmsnr].md_phyadrs.paf_padrs<<PSHRSIZE;
		if(mphyadr!=tmpadr)
		{
			return 0;
		}
		if(MF_MOCTY_FREE!=fstatmp[fsmsnr].md_indxflgs.mf_mocty||
			0!=fstatmp[fsmsnr].md_indxflgs.mf_uindx||
			PAF_NO_ALLOC!=fstatmp[fsmsnr].md_phyadrs.paf_alloc)
		{
			return 0;
		}
		fstatmp[fsmsnr].md_indxflgs.mf_mocty=MF_MOCTY_KRNL;
		fstatmp[fsmsnr].md_indxflgs.mf_uindx++;
		fstatmp[fsmsnr].md_phyadrs.paf_alloc=PAF_ALLOC;
	}
	u64_t ocpysz=ocpyend-ocpystat;
	if((ocpysz&0xfff)!=0)
	{
		if(((ocpysz>>PSHRSIZE)+1)!=fsmsnr)
		{
			return 0;
		}
		return fsmsnr;
	}
	if((ocpysz>>PSHRSIZE)!=fsmsnr)
	{
		return 0;
	}
	return fsmsnr;
}

void test_schkrloccuymm(machbstart_t* mbsp,u64_t ocpystat,u64_t sz)
{
	msadsc_t* msadstat=(msadsc_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_memmappadr);
	u64_t msanr=mbsp->mb_memmapnr;
	u64_t chkmnr=0;
	u64_t chkadr=ocpystat;
	if((sz&0xfff)!=0)
	{
		chkmnr=(sz>>PSHRSIZE)+1;
	}else
	{
		chkmnr=sz>>PSHRSIZE;
	}
	msadsc_t* fstatmp=NULL;
	for(u64_t mnr=0;mnr<msanr;mnr++)
	{
		if((msadstat[mnr].md_phyadrs.paf_padrs<<PSHRSIZE)==ocpystat)
		{
			fstatmp=&msadstat[mnr];
			goto step1;
		}
	}
step1:
	if(fstatmp==NULL)
	{
		system_error("fstatmp NULL\n");
	}

	for (u64_t i = 0; i < chkmnr; i++,chkadr+=PAGESIZE)
	{
		if(chkadr!=fstatmp[i].md_phyadrs.paf_padrs<<PSHRSIZE)
		{
			system_error("chkadr != err\n");
		}
		if(PAF_ALLOC!=fstatmp[i].md_phyadrs.paf_alloc)
		{
			system_error("PAF_ALLOC err\n");
		}
		if(1!=fstatmp[i].md_indxflgs.mf_uindx)
		{
			system_error("mf_uindx err\n");
		}
		if(MF_MOCTY_KRNL!=fstatmp[i].md_indxflgs.mf_mocty)
		{
			system_error("mf_olkty err\n");
		}
	}
	if(chkadr!=(ocpystat+(chkmnr*PAGESIZE)))
	{
		system_error("test_schkrloccuymm err\n");
	}
	return;
}



PUBLIC bool_t search_krloccupymsadsc_core(machbstart_t* mbsp)
{
	u64_t  retschmnr=0;
	msadsc_t* msadstat=(msadsc_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_memmappadr);
	u64_t msanr=mbsp->mb_memmapnr;
	retschmnr=search_segment_occupymsadsc(msadstat,msanr,0,0x1000);
	if(0==retschmnr)
	{
		return FALSE;
	}
	retschmnr=search_segment_occupymsadsc(msadstat, msanr, mbsp->mb_krlinitstack&(~(0xfffUL)), mbsp->mb_krlinitstack);
	if(0==retschmnr)
	{
		return FALSE;
	}
	retschmnr=search_segment_occupymsadsc(msadstat, msanr, mbsp->mb_krlimgpadr, mbsp->mb_nextwtpadr);
	if(0==retschmnr)
	{
		return FALSE;
	}
	retschmnr=search_segment_occupymsadsc(msadstat, msanr, mbsp->mb_lmosimgpadr, mbsp->mb_lmosimgpadr+mbsp->mb_lmosimgsz);
	if(0==retschmnr)
	{
		return FALSE;
	}
	return TRUE;
}

PUBLIC void init_search_krloccupymm(machbstart_t* mbsp)
{
	if(search_krloccupymsadsc_core(mbsp)==FALSE)
	{
		system_error("search_krloccupymsadsc_core fail\n");
	}
	//kprint("search_krloccupymsadsc_core OK!\n");
	test_schkrloccuymm(&kmachbsp, 0, 0x1000);
	test_schkrloccuymm(&kmachbsp, kmachbsp.mb_krlinitstack&(~(0xfffUL)),kmachbsp.mb_krlitstacksz);
	test_schkrloccuymm(&kmachbsp, kmachbsp.mb_krlimgpadr,kmachbsp.mb_nextwtpadr-kmachbsp.mb_krlimgpadr);
	test_schkrloccuymm(&kmachbsp, kmachbsp.mb_lmosimgpadr,kmachbsp.mb_lmosimgsz);
	//kprint("test_schkrloccuymm OK!\n");
	return;
}


		/*findok=0;
		for(u64_t tmpmnr=0;tmpmnr<msanr;tmpmnr++)
		{
			if(MF_MOCTY_FREE==msastart[tmpmnr].md_indxflgs.mf_mocty&&
				0==msastart[tmpmnr].md_indxflgs.mf_uindx&&
				0==msastart[tmpmnr].md_phyadrs.paf_alloc)
			{
				mphyadr=msastart[tmpmnr].md_phyadrs.paf_padrs<<PSHRSIZE;
				if(mphyadr==tmpadr)
				{
					if(findok>0)
					{
						system_error("search_segment_occupymsadsc finok>0 err\n");
					}
					msastart[tmpmnr].md_indxflgs.mf_mocty=MF_MOCTY_KRNL;
					msastart[tmpmnr].md_indxflgs.mf_uindx++;
					msastart[tmpmnr].md_phyadrs.paf_alloc=PAF_ALLOC;
					findok=1;
				}
			}
			
		}
		if(findok==1)
		{
			find++;
			//findok=0;
		}*/