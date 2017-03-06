/**********************************************************
        物理内存区间文件memarea.c
***********************************************************
                彭东 ＠ 2015.05.13.21.10
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"


PUBLIC void arclst_t_init(arclst_t* initp)
{
	list_init(&initp->al_lru1);
	list_init(&initp->al_lru2);
	initp->al_lru1nr=0;
	initp->al_lru2nr=0;
	return;
}

PUBLIC mmstus_t mafo_deft_init(struct s_MEMAREA* memarea,void* valp,uint_t val)
{
	return MMSTUS_ERR;
}

PUBLIC mmstus_t mafo_deft_exit(struct s_MEMAREA* memarea)
{
	return MMSTUS_ERR;
}

PUBLIC mmstus_t mafo_deft_afry(struct s_MEMAREA* memarea,mmafrets_t* mafrspack,void* valp,uint_t val)
{
	return MMSTUS_ERR;
}


PUBLIC void mafuncobjs_t_init(mafuncobjs_t* initp)
{
	initp->mafo_init=mafo_deft_init;
	initp->mafo_exit=mafo_deft_exit;
	initp->mafo_aloc=mafo_deft_afry;
	initp->mafo_free=mafo_deft_afry;
	initp->mafo_recy=mafo_deft_afry;
	return;
}

PUBLIC void bafhlst_t_init(bafhlst_t* initp,u32_t stus,uint_t oder,uint_t oderpnr)
{
	knl_spinlock_init(&initp->af_lock);
	initp->af_stus=stus;
	initp->af_oder=oder;
	initp->af_oderpnr=oderpnr;
	initp->af_fobjnr=0;
	//initp->af_aobjnr=0;
	initp->af_mobjnr=0;
	initp->af_alcindx=0;
	initp->af_freindx=0;
	list_init(&initp->af_frelst);
	list_init(&initp->af_alclst);
	list_init(&initp->af_ovelst);
	return;
}

PUBLIC void memdivmer_t_init(memdivmer_t* initp)
{
	knl_spinlock_init(&initp->dm_lock);
	initp->dm_stus=0;
	initp->dm_dmmaxindx=0;
	initp->dm_phydmindx=0;
	initp->dm_predmindx=0;
	initp->dm_divnr=0;
	initp->dm_mernr=0;
	for(uint_t oi=0;oi<MDIVMER_ARR_OMAX;oi++)
	{
		bafhlst_t_init(&initp->dm_mdmonelst[oi],BAFH_STUS_ONEM,oi,oi+1);
	}
	/*for(uint_t bi=0;bi<MDIVMER_ARR_BMAX;bi++)
	{
		bafhlst_t_init(&initp->dm_mdmblklst[bi],BAFH_STUS_DIVP,bi,1UL<<bi);
	}*/
	for(uint_t li=0;li<MDIVMER_ARR_LMAX;li++)
	{
		bafhlst_t_init(&initp->dm_mdmlielst[li],BAFH_STUS_DIVM,li,(1UL<<li));
		//if(li<30) 1UL<<li <<10
		//	kprint("1<<li<<10:%x:%x\n",(1UL<<li)<<10,li);
	}
	//die(0);
	bafhlst_t_init(&initp->dm_onemsalst,BAFH_STUS_ONEM,0,1UL);
	return;
}

PUBLIC void memarea_t_init(memarea_t* initp)
{
	list_init(&initp->ma_list);
	knl_spinlock_init(&initp->ma_lock);
	initp->ma_stus=0;
	initp->ma_flgs=0;
	initp->ma_type=MA_TYPE_INIT;
	//knl_sem_init(&initp->ma_sem,SEM_MUTEX_ONE_LOCK,SEM_FLG_MUTEX);
	//init_wait_l_head(&initp->ma_waitlst,general_wait_wake_up);
	initp->ma_maxpages=0;
	initp->ma_allocpages=0;
	initp->ma_freepages=0;
	initp->ma_resvpages=0;
	initp->ma_horizline=0;
	initp->ma_logicstart=0;
	initp->ma_logicend=0;
	initp->ma_logicsz=0;
	initp->ma_effectstart=0;
	initp->ma_effectend=0;
	initp->ma_effectsz=0;
	list_init(&initp->ma_allmsadsclst);
	initp->ma_allmsadscnr=0;
	arclst_t_init(&initp->ma_arcpglst);
	mafuncobjs_t_init(&initp->ma_funcobj);
	memdivmer_t_init(&initp->ma_mdmdata);
	initp->ma_privp=NULL;
	return;
}

/*void disp_memarea(machbstart_t* mbsp)
{
	memarea_t* virmarea=(memarea_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_memznpadr);
	for(uint_t i=0;i<mbsp->mb_memznnr;i++)
	{
		kprint("memarea[%d]:ma_type:%x,ma_logicstart:%x,ma_logicend:%x,ma_logicsz:%x\n",i,
			virmarea[i].ma_type,virmarea[i].ma_logicstart,virmarea[i].ma_logicend,virmarea[i].ma_logicsz);
	}
	return;
}*/

PUBLIC LKINIT bool_t init_memarea_core(machbstart_t* mbsp)
{
	u64_t phymarea=mbsp->mb_nextwtpadr;
	if(initchkadr_is_ok(mbsp,phymarea,(sizeof(memarea_t)*MEMAREA_MAX))!=0)
	{
		return FALSE;
	}
	memarea_t* virmarea=(memarea_t*)krnlphyiadr_to_viradr((adr_t)phymarea);
	for(uint_t mai=0;mai<MEMAREA_MAX;mai++)
	{
		memarea_t_init(&virmarea[mai]);
	}
	virmarea[0].ma_type=MA_TYPE_HWAD;
	virmarea[0].ma_logicstart=MA_HWAD_LSTART;
	virmarea[0].ma_logicend=MA_HWAD_LEND;
	virmarea[0].ma_logicsz=MA_HWAD_LSZ;
	virmarea[1].ma_type=MA_TYPE_KRNL;
	virmarea[1].ma_logicstart=MA_KRNL_LSTART;
	virmarea[1].ma_logicend=MA_KRNL_LEND;
	virmarea[1].ma_logicsz=MA_KRNL_LSZ;
	virmarea[2].ma_type=MA_TYPE_PROC;
	virmarea[2].ma_logicstart=MA_PROC_LSTART;
	virmarea[2].ma_logicend=MA_PROC_LEND;
	virmarea[2].ma_logicsz=MA_PROC_LSZ;
	virmarea[3].ma_type=MA_TYPE_SHAR;
	mbsp->mb_memznpadr=phymarea;
	mbsp->mb_memznnr=MEMAREA_MAX;
	mbsp->mb_memznsz=sizeof(memarea_t)*MEMAREA_MAX;
	mbsp->mb_nextwtpadr=PAGE_ALIGN(phymarea+sizeof(memarea_t)*MEMAREA_MAX);
	//.......
	return TRUE;
}

PUBLIC LKINIT void init_memarea()
{
	//kprint("memarea_t is sz[%x]\n",sizeof(memarea_t));
	if(init_memarea_core(&kmachbsp)==FALSE)
	{
		system_error("init_memarea_core fail");
	}
	//kprint("memareaphy:%x,nr:%x,sz:%x,np:%x\n",kmachbsp.mb_memznpadr,kmachbsp.mb_memznnr,kmachbsp.mb_memznsz,kmachbsp.mb_nextwtpadr
	//	);
	//disp_memarea(&kmachbsp);
	//die(0);
	return;
}

PUBLIC bool_t find_inmarea_msadscsegmant(memarea_t* mareap,msadsc_t* fmstat,uint_t fmsanr,msadsc_t** retmsastatp,
	msadsc_t** retmsaendp,uint_t* retfmnr)
{
	if(NULL==mareap||NULL==fmstat||0==fmsanr||NULL==retmsastatp||
		NULL==retmsaendp||NULL==retfmnr)
	{
		return FALSE;
	}
	
	return TRUE;
}

PUBLIC uint_t continumsadsc_is_ok(msadsc_t* prevmsa,msadsc_t* nextmsa,msadflgs_t* cmpmdfp)
{
	if(NULL==prevmsa||NULL==cmpmdfp)
	{
		return (~0UL);
	}
	/*msastat[tmidx].md_indxflgs.mf_marty==mdfp->mf_marty&&
			0==msastat[tmidx].md_indxflgs.mf_uindx&&
			MF_MOCTY_FREE==msastat[tmidx].md_indxflgs.mf_mocty&&
			PAF_NO_ALLOC==msastat[tmidx].md_phyadrs.paf_alloc
	*/
	if(NULL!=prevmsa&&NULL!=nextmsa)
	{
		if(prevmsa->md_indxflgs.mf_marty==cmpmdfp->mf_marty&&
			0==prevmsa->md_indxflgs.mf_uindx&&
			MF_MOCTY_FREE==prevmsa->md_indxflgs.mf_mocty&&
			PAF_NO_ALLOC==prevmsa->md_phyadrs.paf_alloc)
		{
			if(nextmsa->md_indxflgs.mf_marty==cmpmdfp->mf_marty&&
				0==nextmsa->md_indxflgs.mf_uindx&&
				MF_MOCTY_FREE==nextmsa->md_indxflgs.mf_mocty&&
				PAF_NO_ALLOC==nextmsa->md_phyadrs.paf_alloc)
			{	
				if((nextmsa->md_phyadrs.paf_padrs<<PSHRSIZE)-(prevmsa->md_phyadrs.paf_padrs<<PSHRSIZE)==PAGESIZE)
				{
					return 2;
				}
				//kprint("not continumsadsc\n");	
				return 1;
			}
			//kprint("nextmsa not\n");
			return 1;
		}
		return 0;
	}

	return (~0UL);
}

PUBLIC bool_t scan_len_msadsc(msadsc_t* mstat,msadflgs_t* cmpmdfp,uint_t mnr,uint_t* retmnr)
{
	uint_t retclok=0;
	uint_t retnr=0;
	if(NULL==mstat||NULL==cmpmdfp||0==mnr||NULL==retmnr)
	{
		return FALSE;
	}
	for(uint_t tmdx=0;tmdx<mnr-1;tmdx++)
	{
		retclok=continumsadsc_is_ok(&mstat[tmdx], &mstat[tmdx+1],cmpmdfp);
		if((~0UL)==retclok)
		{
			*retmnr=0;
			return FALSE;
		}
		if(0==retclok)
		{
			//retnr+=retclok;
			*retmnr=0;
			return FALSE;
		}
		if(1==retclok)
		{
			//retnr++;
			//kprint("continumsadsc_is_ok retn 1:%x\n",retclok);
			*retmnr=retnr;
			return TRUE;
		}
		retnr++;
		
	}
	*retmnr=retnr;
	return TRUE;
}

PUBLIC uint_t check_continumsadsc(memarea_t* mareap,msadsc_t* stat,msadsc_t* end,uint_t fmnr)
{
	msadsc_t* ms=stat,*me=end;
	u32_t muindx=0;
	msadflgs_t* mdfp=NULL;
	if(NULL==ms||NULL==me||0==fmnr||ms>me)
	{
		return 0;
	}
	switch(mareap->ma_type)
	{
		case MA_TYPE_HWAD:
		{
			muindx=MF_MARTY_HWD<<5;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		case MA_TYPE_KRNL:
		{
			muindx=MF_MARTY_KRL<<5;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		case MA_TYPE_PROC:
		{
			muindx=MF_MARTY_PRC<<5;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		default:
		{
			muindx=0;
			mdfp=NULL;
			break;
		}
	}
	if(0==muindx||NULL==mdfp)
	{
		return 0;
	}
	uint_t ok=0;
	if(ms==me)
	{
		if(0!=ms->md_indxflgs.mf_uindx)
		{
			return 0;
		}
		if(ms->md_indxflgs.mf_marty!=mdfp->mf_marty)
		{
			return 0;
		}
		if(MF_MOCTY_FREE!=ms->md_indxflgs.mf_mocty)
		{
			return 0;
		}
		if(PAF_NO_ALLOC!=ms->md_phyadrs.paf_alloc)
		{
			return 0;
		}

		if((ok+1)!=fmnr)
		{
			return 0;
		}
		return ok+1;
	}
	for(;ms<me;ms++)
	{
		if(ms->md_indxflgs.mf_marty!=mdfp->mf_marty||
			(ms+1)->md_indxflgs.mf_marty!=mdfp->mf_marty)
		{
			return 0;
		}
		if(MF_MOCTY_FREE!=ms->md_indxflgs.mf_mocty||
			MF_MOCTY_FREE!=(ms+1)->md_indxflgs.mf_mocty)
		{
			return 0;
		}
		if(ms->md_indxflgs.mf_uindx!=0||
			(ms+1)->md_indxflgs.mf_uindx!=0)
		{
			return 0;
		}
		if(PAF_NO_ALLOC!=ms->md_phyadrs.paf_alloc||
			PAF_NO_ALLOC!=(ms+1)->md_phyadrs.paf_alloc)
		{
			return 0;
		}
		if(PAGESIZE!=(((ms+1)->md_phyadrs.paf_padrs<<PSHRSIZE)-(ms->md_phyadrs.paf_padrs<<PSHRSIZE)))
		
		{
			return 0;
		}
		ok++;
	}
	if(0==ok)
	{
		return 0;
	}
	if((ok+1)!=fmnr)
	{
		return 0;
	}
	return ok;
}


PUBLIC bool_t merlove_scan_continumsadsc(memarea_t* mareap,msadsc_t* fmstat,uint_t* fntmsanr,uint_t fmsanr,
	msadsc_t** retmsastatp,msadsc_t** retmsaendp,uint_t* retfmnr)
{
	if(NULL==mareap||NULL==fmstat||NULL==fntmsanr||
		0==fmsanr||NULL==retmsastatp||NULL==retmsaendp||NULL==retfmnr)
	{
		return FALSE;
	}
	if(*fntmsanr>=fmsanr)
	{
		//kprint("errrrrrrrrrr\n");
		return FALSE;
	}
	u32_t muindx=0;
	msadflgs_t* mdfp=NULL;
	switch(mareap->ma_type)
	{
		case MA_TYPE_HWAD:
		{
			muindx=MF_MARTY_HWD<<5;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		case MA_TYPE_KRNL:
		{
			muindx=MF_MARTY_KRL<<5;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		case MA_TYPE_PROC:
		{
			muindx=MF_MARTY_PRC<<5;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		default:
		{
			muindx=0;
			mdfp=NULL;
			break;
		}
	}
	if(0==muindx||NULL==mdfp)
	{
		return FALSE;
	}

	msadsc_t* msastat=fmstat;
	//msadsc_t* fstmsa=NULL;
	//uint_t fstmind=0;
	//uint_t retcok=0;
	uint_t retfindmnr=0;
	bool_t rets=FALSE;
	uint_t tmidx=*fntmsanr;
	for(;tmidx<fmsanr;tmidx++)
	{
		if(msastat[tmidx].md_indxflgs.mf_marty==mdfp->mf_marty&&
			0==msastat[tmidx].md_indxflgs.mf_uindx&&
			MF_MOCTY_FREE==msastat[tmidx].md_indxflgs.mf_mocty&&
			PAF_NO_ALLOC==msastat[tmidx].md_phyadrs.paf_alloc)
		{
			rets=scan_len_msadsc(&msastat[tmidx],mdfp,fmsanr,&retfindmnr);
			if(FALSE==rets)
			{
				system_error("scan_len_msadsc err\n");
			}	
			*fntmsanr=tmidx+retfindmnr+1;
			*retmsastatp=&msastat[tmidx];
			*retmsaendp=&msastat[tmidx+retfindmnr];
			*retfmnr=retfindmnr+1;
			return TRUE;
		}
	}
	if(tmidx>=fmsanr)
	{
		*fntmsanr=fmsanr;
		*retmsastatp=NULL;
		*retmsaendp=NULL;
		*retfmnr=0;
		return TRUE;
	}
	return FALSE;
}

/*PUBLIC uint_t merlove_clrflge_onmsadsc(msadsc_t* mstat,uint_t msanr)
{
	uint_t retn=0;
	if(NULL==mstat||msanr<1)
	{
		return 0;
	}
	for(uint_t mix=0;mix<msanr;mix++)
	{
		if(MF_MOCTY_FREE==mstat[mix].md_indxflgs.mf_mocty&&
			PAF_NO_ALLOC==mstat[mix].md_phyadrs.paf_alloc)
		{
			if(MF_UIXTY_THWD==mstat[mix].md_indxflgs.mf_uindx||
				MF_UIXTY_TKRL==mstat[mix].md_indxflgs.mf_uindx||
				MF_UIXTY_TPRC==mstat[mix].md_indxflgs.mf_uindx||
				MF_UIXTY_TSHD==mstat[mix].md_indxflgs.mf_uindx)
			{
				mstat[mix].md_indxflgs.mf_uindx=MF_UINDX_INIT;
				retn++;
			}
		}
	}
	return retn;
}*/


PUBLIC uint_t merlove_setallmarflgs_onmemarea(memarea_t* mareap,msadsc_t* mstat,uint_t msanr)
{
	if(NULL==mareap||NULL==mstat||0==msanr)
	{
		return ~0UL;
	}
	u32_t muindx=0;
	msadflgs_t* mdfp=NULL;
	switch(mareap->ma_type)
	{
		case MA_TYPE_HWAD:
		{
			muindx=MF_MARTY_HWD<<5;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		case MA_TYPE_KRNL:
		{
			muindx=MF_MARTY_KRL<<5;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		case MA_TYPE_PROC:
		{
			muindx=MF_MARTY_PRC<<5;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		case MA_TYPE_SHAR:
		{
			return 0;
		}
		default:
		{
			muindx=0;
			mdfp=NULL;
			break;
		}
	}
	if(0==muindx||NULL==mdfp)
	{
		return ~0UL;
	}
	u64_t phyadr=0;
	uint_t retnr=0;
	for(uint_t mix=0;mix<msanr;mix++)
	{
		if(MF_MARTY_INIT==mstat[mix].md_indxflgs.mf_marty)
		{
			phyadr=mstat[mix].md_phyadrs.paf_padrs<<PSHRSIZE;
			if(phyadr>=mareap->ma_logicstart&&((phyadr+PAGESIZE)-1)<=mareap->ma_logicend)
			{
				mstat[mix].md_indxflgs.mf_marty=mdfp->mf_marty;
				retnr++;
			}
		}
	}
	return retnr;	

}
/*PUBLIC uint_t merlove_setflgs_onmemarea(memarea_t* mareap,msadsc_t* mstat,uint_t msanr)
{
	u32_t muindx=0;
	msadflgs_t* mdfp=NULL;
	if(NULL==mareap||NULL==mstat||0==msanr)
	{
		return ~0UL;
	}
	switch(mareap->ma_type)
	{
		case MA_TYPE_HWAD:
		{
			muindx=MF_UIXTY_THWD<<8;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		case MA_TYPE_KRNL:
		{
			muindx=MF_UIXTY_TKRL<<8;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		case MA_TYPE_PROC:
		{
			muindx=MF_UIXTY_TPRC<<8;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		default:
		{
			muindx=0;
			mdfp=NULL;
			break;
		}
	}
	if(0==muindx||NULL==mdfp)
	{
		return ~0UL;
	}
	uint_t phyadr=0,retnr=0;
	for(uint_t mix=0;mix<msanr;mix++)
	{
		if(0==mstat[mix].md_indxflgs.mf_uindx&&MF_MOCTY_FREE==mstat[mix].md_indxflgs.mf_mocty&&
			PAF_NO_ALLOC==mstat[mix].md_phyadrs.paf_alloc)
		{
			phyadr=mstat[mix].md_phyadrs.paf_padrs<<PSHRSIZE;
			if(phyadr>=mareap->ma_logicstart&&((phyadr+PAGESIZE)-1)<=mareap->ma_logicend)
			{
				mstat[mix].md_indxflgs.mf_uindx=mdfp->mf_uindx;
				retnr++;
			}
		}
	}
	return retnr;
}
*/

PUBLIC uint_t test_setflgs(memarea_t* mareap,msadsc_t* mstat,uint_t msanr)
{
	u32_t muindx=0;
	msadflgs_t* mdfp=NULL;
	if(NULL==mareap||NULL==mstat||0==msanr)
	{
		return ~0UL;
	}
	switch(mareap->ma_type)
	{
		case MA_TYPE_HWAD:
		{
			muindx=MF_MARTY_HWD<<5;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		case MA_TYPE_KRNL:
		{
			muindx=MF_MARTY_KRL<<5;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		case MA_TYPE_PROC:
		{
			muindx=MF_MARTY_PRC<<5;
			mdfp=(msadflgs_t*)(&muindx);
			break;
		}
		case MA_TYPE_SHAR:
		{
			return 0;
		}
		default:
		{
			muindx=0;
			mdfp=NULL;
			break;
		}
	}
	if(0==muindx||NULL==mdfp)
	{
		return ~0UL;
	}
	u64_t phyadr=0;
	uint_t retnr=0;
	for(uint_t mix=0;mix<msanr;mix++)
	{
		/*if(MF_MOCTY_FREE==mstat[mix].md_indxflgs.mf_mocty&&
			PAF_NO_ALLOC==mstat[mix].md_phyadrs.paf_alloc&&
			0==mstat[mix].md_indxflgs.mf_uindx)*/
		{
			phyadr=mstat[mix].md_phyadrs.paf_padrs<<PSHRSIZE;
			if(phyadr>=mareap->ma_logicstart&&((phyadr+PAGESIZE)-1)<=mareap->ma_logicend)
			{
				if(mstat[mix].md_indxflgs.mf_marty==mdfp->mf_marty)
					retnr++;
			}
		}
	}
	return retnr;
}

PUBLIC bafhlst_t* find_continumsa_inbafhlst(memarea_t* mareap,uint_t fmnr)
{
	bafhlst_t* retbafhp=NULL;
	uint_t in=0;
	if(NULL==mareap||0==fmnr)
	{
		return NULL;
	}

	if(MA_TYPE_PROC==mareap->ma_type)
	{
		return &mareap->ma_mdmdata.dm_onemsalst;
	}
	if(MA_TYPE_SHAR==mareap->ma_type)
	{
		return NULL;
	}
	//not enlab blklst//
	/*if(fmnr<=(1<<0<<10))
	{
		for(uint_t pi=0;pi<MDIVMER_ARR_BMAX;pi++)
		{
			if(mareap->ma_mdmdata.dm_mdmblklst[pi].af_oderpnr<=fmnr)
			{
				//kprint("moderp:%x,oder:%x,fmnr:%x\n",mareap->ma_mdmdata.dm_mdmblklst[pi].af_oderpnr,
				//	mareap->ma_mdmdata.dm_mdmblklst[pi].af_oder,fmnr);
				retbafhp=&mareap->ma_mdmdata.dm_mdmblklst[pi];
				in++;
			}
		}
		if(MDIVMER_ARR_BMAX<=in||NULL==retbafhp)
		{
			return NULL;
		}
		return retbafhp;
	}*/
	in=0;
	retbafhp=NULL;
	for(uint_t li=0;li<MDIVMER_ARR_LMAX;li++)
	{
		if((mareap->ma_mdmdata.dm_mdmlielst[li].af_oderpnr)<=fmnr)
		{
			retbafhp=&mareap->ma_mdmdata.dm_mdmlielst[li];
			in++;
		}
	}
	if(MDIVMER_ARR_LMAX<=in||NULL==retbafhp)
	{
		return NULL;
	}
	return retbafhp;
}

PUBLIC bool_t continumsadsc_add_procmareabafh(memarea_t* mareap,bafhlst_t* bafhp,msadsc_t* fstat,msadsc_t* fend,uint_t fmnr)
{
	if(NULL==mareap||NULL==bafhp||NULL==fstat||NULL==fend||0==fmnr)
	{
		return FALSE;
	}
	if(BAFH_STUS_ONEM!=bafhp->af_stus||MA_TYPE_PROC!=mareap->ma_type)
	{
		return FALSE;
	}
	if(bafhp->af_oderpnr!=1)
	{
		return FALSE;
	}
	if((&fstat[fmnr-1])!=fend)
	{
		return FALSE;
	}
	for (uint_t tmpnr=0;tmpnr<fmnr;tmpnr++)
	{
		fstat[tmpnr].md_indxflgs.mf_olkty=MF_OLKTY_BAFH;
		fstat[tmpnr].md_odlink=bafhp;
		//fstat[tmpnr].md_indxflgs.mf_olkty=MF_OLKTY_ODER;
		//fstat[tmpnr].md_odlink=&fstat[tmpnr];
		// fstat==fend
		//fend->md_indxflgs.mf_olkty=MF_OLKTY_BAFH;
		//fend->md_odlink=bafhp;
		list_add(&fstat[tmpnr].md_list,&bafhp->af_frelst);
		bafhp->af_fobjnr++;
		bafhp->af_mobjnr++;
		mareap->ma_maxpages++;
		mareap->ma_freepages++;
		mareap->ma_allmsadscnr++;
	}
	return TRUE;

}

PUBLIC bool_t continumsadsc_add_bafhlst(memarea_t* mareap,bafhlst_t* bafhp,msadsc_t* fstat,msadsc_t* fend,uint_t fmnr)
{
	if(NULL==mareap||NULL==bafhp||NULL==fstat||NULL==fend||0==fmnr)
	{
		return FALSE;
	}
	if(bafhp->af_oderpnr!=fmnr)
	{
		return FALSE;
	}
	if((&fstat[fmnr-1])!=fend)
	{
		return FALSE;
	}
	fstat->md_indxflgs.mf_olkty=MF_OLKTY_ODER;
	fstat->md_odlink=fend;
	// fstat==fend
	fend->md_indxflgs.mf_olkty=MF_OLKTY_BAFH;
	fend->md_odlink=bafhp;
	list_add(&fstat->md_list,&bafhp->af_frelst);
	bafhp->af_fobjnr++;
	bafhp->af_mobjnr++;
	mareap->ma_maxpages+=fmnr;
	mareap->ma_freepages+=fmnr;
	mareap->ma_allmsadscnr+=fmnr;
	return TRUE;
}

PUBLIC bool_t continumsadsc_mareabafh_core(memarea_t* mareap,msadsc_t** rfstat,msadsc_t** rfend,uint_t* rfmnr)
{
	
	if(NULL==mareap||NULL==rfstat||NULL==rfend||NULL==rfmnr)
	{
		return FALSE;
	}
	uint_t retval=*rfmnr,tmpmnr=0;
	msadsc_t* mstat=*rfstat,*mend=*rfend;
	if(1>(retval))
	{
		return FALSE;
	}
	bafhlst_t* bafhp=find_continumsa_inbafhlst(mareap, retval);
	if(NULL==bafhp)
	{
		return FALSE;
	}
	if(retval<bafhp->af_oderpnr)
	{
		return FALSE;
	}
	if((BAFH_STUS_DIVP==bafhp->af_stus||BAFH_STUS_DIVM==bafhp->af_stus)&&MA_TYPE_PROC!=mareap->ma_type)
	{
		tmpmnr=retval-bafhp->af_oderpnr;
		if(continumsadsc_add_bafhlst(mareap,bafhp,mstat,&mstat[bafhp->af_oderpnr-1],bafhp->af_oderpnr)==FALSE)
		{
			return FALSE;
		}
		if(tmpmnr==0)
		{
			//kprint("bafhp.af_stus:%x,af_oder%x,af_oderpnr:%x,rfmnr:%x,tmpmnr:%x\n",bafhp->af_stus,bafhp->af_oder,bafhp->af_oderpnr,*rfmnr,tmpmnr);
			*rfmnr=tmpmnr;
			*rfend=NULL;
			return TRUE;
		}
		//kprint("bafhp.af_stus:%x,af_oder%x,af_oderpnr:%x,rfmnr:%x,tmpmnr:%x\n",bafhp->af_stus,bafhp->af_oder,bafhp->af_oderpnr,*rfmnr,tmpmnr);
		*rfstat=&mstat[bafhp->af_oderpnr];
		*rfmnr=tmpmnr;
		
		return TRUE;
	}
	if(BAFH_STUS_ONEM==bafhp->af_stus&&MA_TYPE_PROC==mareap->ma_type)
	{
		if(continumsadsc_add_procmareabafh(mareap,bafhp,mstat,mend,*rfmnr)==FALSE)
		{
			return FALSE;
		}
		//kprint("bafhp.af_stus:%x,af_oder%x,af_oderpnr:%x,rfmnr:%x\n",bafhp->af_stus,bafhp->af_oder,bafhp->af_oderpnr,*rfmnr);
		*rfmnr=0;
		*rfend=NULL;
		return TRUE;
	}
	/*if(BAFH_STUS_DIVM==bafhp->af_stus)
	{
		tmpmnr=retval-(bafhp->af_oderpnr<<PSHRSIZE);
		if(continumsadsc_add_bafhlst(mareap,bafhp,mstat,&mstat[(bafhp->af_oderpnr<<PSHRSIZE)-1],bafhp->af_oderpnr<<PSHRSIZE)==FALSE)
		{
			return FALSE;
		}
		if(tmpmnr==0)
		{
			*rfmnr=tmpmnr;
			*rfend=NULL;
			return TRUE;
		}
		*rfstat=&mstat[bafhp->af_oderpnr];
		*rfmnr=tmpmnr;
		kprint("bafhp.af_stus:%x,af_oder%x,af_oderpnr:%x,rfmnr:%x\n",bafhp->af_stus,bafhp->af_oder,bafhp->af_oderpnr,*rfmnr);
		return TRUE;
	}*/
	
	return FALSE;
}

PUBLIC bool_t merlove_continumsadsc_mareabafh(memarea_t* mareap,msadsc_t* mstat,msadsc_t* mend,uint_t mnr)
{
	if(NULL==mareap||NULL==mstat||NULL==mend||0==mnr)
	{
		return FALSE;
	}
	uint_t mnridx=mnr;
	msadsc_t* fstat=mstat,*fend=mend;
	for(;(mnridx>0&&NULL!=fend);)
	{
		if(continumsadsc_mareabafh_core(mareap,&fstat,&fend,&mnridx)==FALSE)
		{
			system_error("continumsadsc_mareabafh_core fail\n");
		}
	}
	return TRUE;
}


PUBLIC bool_t merlove_mem_onmemarea(memarea_t* mareap,msadsc_t* mstat,uint_t msanr)
{
	if(NULL==mareap||NULL==mstat||0==msanr)
	{
		return FALSE;
	}
	if(MA_TYPE_SHAR==mareap->ma_type)
	{
		//kprint("err1\n");
		return TRUE;
	}
	if(MA_TYPE_INIT==mareap->ma_type)
	{
		return FALSE;
	}
	msadsc_t* retstatmsap=NULL,*retendmsap=NULL,*fntmsap=mstat;
	uint_t retfindmnr=0;
	uint_t fntmnr=0;
	bool_t retscan=FALSE;
	
	//uint_t rettsef=test_setflgs(mareap,mstat,msanr);
	//kprint("retsetflgmnr:%x,rettsef:%x\n",retsetflgmnr,rettsef);

	for(;fntmnr<msanr;)
	{
		retscan=merlove_scan_continumsadsc(mareap,fntmsap,&fntmnr,msanr, &retstatmsap, &retendmsap, &retfindmnr);
		if(FALSE==retscan)
		{
			system_error("merlove_scan_continumsadsc fail\n");
		}
		if(NULL!=retstatmsap&&NULL!=retendmsap)
		{
			if(check_continumsadsc(mareap,retstatmsap,retendmsap, retfindmnr)==0)
			{
				system_error("check_continumsadsc fail\n");
			}
			if(merlove_continumsadsc_mareabafh(mareap,retstatmsap,retendmsap,retfindmnr)==FALSE)
			{
				system_error("merlove_continumsadsc_mareabafh fail\n");
			}
			/*kprint("retstatmsap:%x,retendmsap:%x,msadscnr:%x,m0m1:%x,retfindmnr:%x,fntmnr:%x,chadr:%x,sz:%x\n",
				retstatmsap->md_phyadrs.paf_padrs<<12, retendmsap->md_phyadrs.paf_padrs<<12 ,
				retendmsap-retstatmsap,(mstat+1)-mstat,retfindmnr,fntmnr,
				retstatmsap[retfindmnr].md_phyadrs.paf_padrs<<12,retfindmnr*PAGESIZE);*/
		}
		
	}
	//die(0);	
	return TRUE;
}

PUBLIC bool_t merlove_mem_core(machbstart_t* mbsp)
{
	msadsc_t* mstatp=(msadsc_t*)krnlphyiadr_to_viradr((adr_t) mbsp->mb_memmappadr);
	uint_t msanr=(uint_t)mbsp->mb_memmapnr,maxp=0;
	memarea_t* marea=(memarea_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_memznpadr);
	uint_t sretf=~0UL,tretf=~0UL;
	for(uint_t mi=0;mi<(uint_t)mbsp->mb_memznnr;mi++)
	{
		sretf=merlove_setallmarflgs_onmemarea(&marea[mi],mstatp,msanr);
		if((~0UL)==sretf)
		{
			//kprint("set_setflgs :%x\n",sretf);
			return FALSE;
		}
		tretf=test_setflgs(&marea[mi],mstatp,msanr);
		if((~0UL)==tretf)
		{
			//kprint("test_setflgs :%x\n",tretf);
			return FALSE;
		}
		if(sretf!=tretf)
		{
			//kprint("sretf!=tretf:%x:%x\n",sretf,tretf);
			//die(0);
			return FALSE;
		}
	}
	for(uint_t maidx=0;maidx<(uint_t)mbsp->mb_memznnr;maidx++)
	{
		if(merlove_mem_onmemarea(&marea[maidx],mstatp,msanr)==FALSE)
		{
			return FALSE;
		}
		maxp+=marea[maidx].ma_maxpages;
	}

	/*uint_t retsetflgmnr=merlove_setallmarflgs_onmemarea(mareap,mstat,msanr);
	if((~0UL)==retsetflgmnr)
	{
		return FALSE;
	}
	if(merlove_clrflge_onmsadsc(mstatp,msanr)!=maxp)
	{
		return FALSE;
	}*/
	return TRUE;
}

uint_t check_multi_msadsc(msadsc_t* mstat,bafhlst_t* bafhp,memarea_t* mareap)
{
	if(NULL==mstat||NULL==bafhp||NULL==mareap)
	{
		return 0;
	}
	if(MF_OLKTY_ODER!=mstat->md_indxflgs.mf_olkty&&
		MF_OLKTY_BAFH!=mstat->md_indxflgs.mf_olkty)
	{
		return 0;
	}
	if(NULL==mstat->md_odlink)
	{
		return 0;
	}

	msadsc_t* mend=NULL;//(msadsc_t*)mstat->md_odlink;
	if(MF_OLKTY_ODER==mstat->md_indxflgs.mf_olkty)
	{
		mend=(msadsc_t*)mstat->md_odlink;
	}
	if(MF_OLKTY_BAFH==mstat->md_indxflgs.mf_olkty)
	{
		mend=mstat;
	}
	if(NULL==mend)
	{
		return 0;
	}
	uint_t mnr=(mend-mstat)+1;
	if(mnr!=bafhp->af_oderpnr)
	{
		return 0;
	}
	if(MF_OLKTY_BAFH!=mend->md_indxflgs.mf_olkty)
	{
		return 0;
	}
	if((bafhlst_t*)(mend->md_odlink)!=bafhp)
	{
		return 0;
	}

	u64_t phyadr=(~0UL);
	if(mnr==1)
	{
		if(mstat->md_indxflgs.mf_marty!=(u32_t)mareap->ma_type)
		{
			return 0;
		}
		if(PAF_NO_ALLOC!=mstat->md_phyadrs.paf_alloc||
			0!=mstat->md_indxflgs.mf_uindx)
		{
			return 0;
		}
		phyadr=mstat->md_phyadrs.paf_padrs<<PSHRSIZE;
		if(phyadr<mareap->ma_logicstart||(phyadr+PAGESIZE-1)>mareap->ma_logicend)
		{
			return 0;
		}
		return 1;
	}	
	uint_t idx=0;
	for(uint_t mi=0;mi<mnr-1;mi++)
	{
		if(mstat[mi].md_indxflgs.mf_marty!=(u32_t)mareap->ma_type)
		{
			return 0;
		}
		if(PAF_NO_ALLOC!=mstat[mi].md_phyadrs.paf_alloc||
			0!=mstat[mi].md_indxflgs.mf_uindx)
		{
			return 0;
		}
		if(PAF_NO_ALLOC!=mstat[mi+1].md_phyadrs.paf_alloc||
			0!=mstat[mi+1].md_indxflgs.mf_uindx)
		{
			return 0;
		}
		if(((mstat[mi].md_phyadrs.paf_padrs<<PSHRSIZE)+PAGESIZE)!=(mstat[mi+1].md_phyadrs.paf_padrs<<PSHRSIZE))
		{
			return 0;
		}
		if((mstat[mi].md_phyadrs.paf_padrs<<PSHRSIZE)<mareap->ma_logicstart||
			(((mstat[mi+1].md_phyadrs.paf_padrs<<PSHRSIZE)+PAGESIZE)-1)>mareap->ma_logicend)
		{
			return 0;
		}
		idx++;
	}
	return idx+1;
}

bool_t check_one_bafhlst(bafhlst_t* bafhp,memarea_t* mareap)
{
	if(NULL==bafhp||NULL==mareap)
	{
		return FALSE;
	}
	if(1>bafhp->af_mobjnr&&1>bafhp->af_fobjnr)
	{
		return TRUE;
	}
	uint_t lindx=0;
	list_h_t* tmplst=NULL;
	msadsc_t* msap=NULL;
	list_for_each(tmplst,&bafhp->af_frelst)
	{
		msap=list_entry(tmplst,msadsc_t,md_list);
		if(bafhp->af_oderpnr!=check_multi_msadsc(msap,bafhp,mareap))
		{
			return FALSE;
		}
		lindx++;
	}
	if(lindx!=bafhp->af_fobjnr||lindx!=bafhp->af_mobjnr)
	{
		return FALSE;
	}
	return TRUE;
}

bool_t check_one_memarea(memarea_t* mareap)
{
	if(NULL==mareap)
	{
		return FALSE;
	}
	if(1>mareap->ma_maxpages)
	{
		return TRUE;
	}
	for(uint_t oi=0;oi<MDIVMER_ARR_OMAX;oi++)
	{
		if(check_one_bafhlst(&mareap->ma_mdmdata.dm_mdmonelst[oi],mareap)==FALSE)
		{
			return FALSE;
		}
	}
	/*for(uint_t bi=0;bi<MDIVMER_ARR_BMAX;bi++)
	{
		if(check_one_bafhlst(&mareap->ma_mdmdata.dm_mdmblklst[bi],mareap)==FALSE)
		{
			return FALSE;
		}
	}*/
	for(uint_t li=0;li<MDIVMER_ARR_LMAX;li++)
	{
		if(check_one_bafhlst(&mareap->ma_mdmdata.dm_mdmlielst[li],mareap)==FALSE)
		{
			return FALSE;
		}
	}
	if(check_one_bafhlst(&mareap->ma_mdmdata.dm_onemsalst,mareap)==FALSE)
	{
		return FALSE;
	}
	return TRUE;
}
void mem_check_mareadata(machbstart_t* mbsp)
{
	memarea_t* marea=(memarea_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_memznpadr);
	for(uint_t maidx=0;maidx<mbsp->mb_memznnr;maidx++)
	{
		if(check_one_memarea(&marea[maidx])==FALSE)
		{
			system_error("check_one_memarea fail\n");
		}
	}
	return;
}
PUBLIC void init_merlove_mem()
{
	if(merlove_mem_core(&kmachbsp)==FALSE)
	{
		system_error("merlove_mem_core fail\n");
	}
	mem_check_mareadata(&kmachbsp);
	//kprint("init_merlove_mem OK\n");
	//disp_memarea(&kmachbsp);
	//disp_memarea(&kmachbsp);
	//die(0);
	return;
}

void disp_bafhlst(bafhlst_t* bafhp)
{
	if(bafhp->af_mobjnr>0)
	{
		kprint("bafhlst_t.af_stus:%x,af_indx:%x,af_onebnr:%x,af_fobjnr:%x\n",
			bafhp->af_stus,bafhp->af_oder,bafhp->af_oderpnr,bafhp->af_fobjnr);
	}
	return;
}

void disp_memarea(machbstart_t* mbsp)
{
	memarea_t* marea=(memarea_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_memznpadr);
	for(uint_t i=0;i<mbsp->mb_memznnr;i++)
	{
		kprint("memarea.ma_type:%x,ma_maxpages:%x,ma_freepages:%x,ma_allmsadscnr:%x\n",
			marea[i].ma_type,marea[i].ma_maxpages,marea[i].ma_freepages,marea[i].ma_allmsadscnr);
		for(uint_t oi=0;oi<MDIVMER_ARR_OMAX;oi++)
		{
			disp_bafhlst(&marea[i].ma_mdmdata.dm_mdmonelst[oi]);
		}
		/*for(uint_t bi=0;bi<MDIVMER_ARR_BMAX;bi++)
		{
			disp_bafhlst(&marea[i].ma_mdmdata.dm_mdmblklst[bi]);
		}*/
		for(uint_t li=0;li<MDIVMER_ARR_LMAX;li++)
		{
			disp_bafhlst(&marea[i].ma_mdmdata.dm_mdmlielst[li]);
		//if(li<30)
		//	kprint("1<<li<<10:%x:%x\n",(1UL<<li)<<10,li);
		}
		disp_bafhlst(&marea[i].ma_mdmdata.dm_onemsalst);
	}
	return;	
}