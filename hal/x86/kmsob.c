/**********************************************************
        内核内存空间对象分配释放文件kmsob.c
***********************************************************
                彭东 ＠ 2015.06.26.22.00
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

KLINE sint_t retn_mscidx(uint_t pages)
{
	sint_t pbits=search_32rlbits((uint_t)pages)-1;
 	if(pages&(pages-1))
    	{
        		pbits++;
    	}
    	return pbits;
}

PUBLIC void msclst_t_init(msclst_t* initp,uint_t pnr)
{
	initp->ml_msanr=0;
	initp->ml_ompnr=pnr;
	list_init(&initp->ml_list);
	return;
}

PUBLIC void msomdc_t_init(msomdc_t* initp)
{
	for(uint_t i=0;i<MSCLST_MAX;i++)
	{
		msclst_t_init(&initp->mc_lst[i],1UL<<i);
	}
	initp->mc_msanr=0;
	list_init(&initp->mc_list);
	list_init(&initp->mc_kmobinlst);
	initp->mc_kmobinpnr=0;
	return;
}

PUBLIC void freobjh_t_init(freobjh_t* initp,uint_t stus,void* stat)
{
	list_init(&initp->oh_list);
	initp->oh_stus=stus;
	initp->oh_stat=stat;
	return;
}

PUBLIC void kmsob_t_init(kmsob_t* initp)
{
	list_init(&initp->so_list);
	knl_spinlock_init(&initp->so_lock);
	initp->so_stus=0;
	initp->so_flgs=0;
	initp->so_vstat=NULL;
	initp->so_vend=NULL;
	initp->so_objsz=0;
	initp->so_objrelsz=0;
	initp->so_mobjnr=0;
	initp->so_fobjnr=0;
	list_init(&initp->so_frelst);
	list_init(&initp->so_alclst);
	list_init(&initp->so_mextlst);
	initp->so_mextnr=0;
	msomdc_t_init(&initp->so_mc);
	initp->so_privp=NULL;
	initp->so_extdp=NULL;
	return;
}

PUBLIC void kmbext_t_init(kmbext_t* initp,adr_t vstat,adr_t vend,kmsob_t*kmsp)
{
	list_init(&initp->mt_list);
	initp->mt_vstat=vstat;
	initp->mt_vend=vend;
	initp->mt_kmsb=kmsp;
	initp->mt_mobjnr=0;
	return;
}

PUBLIC void koblst_t_init(koblst_t* initp,size_t koblsz)
{
	//list_init(&initp->ol_fullst);
	list_init(&initp->ol_emplst);
	//list_init(&initp->ol_efulst);
	initp->ol_cahe=NULL;
	//initp->ol_funr=0;
	initp->ol_emnr=0;
	//initp->ol_efnr=0;
	initp->ol_sz=koblsz;
	return;
}

PUBLIC void kmsobmgrhed_t_init(kmsobmgrhed_t* initp)
{
	size_t koblsz=32;
	knl_spinlock_init(&initp->ks_lock);
	list_init(&initp->ks_tclst);
	initp->ks_tcnr=0;
	initp->ks_msobnr=0;
	initp->ks_msobche=NULL;
	for(uint_t i=0;i<KOBLST_MAX;i++)
	{
		koblst_t_init(&initp->ks_msoblst[i],koblsz);
		koblsz+=32;
	}
	return;
}

PUBLIC void disp_kmsobmgr()
{
	kmsobmgrhed_t* kmmp=&lmos_memmgrob.mo_kmsobmgr;
	for(uint_t i=0;i<KOBLST_MAX;i++)
	{
		kprint("koblst_t.ol_sz:%d\n",kmmp->ks_msoblst[i].ol_sz);
	}
	return;
} 

PUBLIC void disp_kmsob(kmsob_t* kmsp)
{
	kprint("kmsob_t so_vstat:%x so_vend:%x so_objsz:%d so_fobjnr:%d so_mobjnr:%d\n",
		kmsp->so_vstat,kmsp->so_vend,kmsp->so_objsz,
		kmsp->so_fobjnr,kmsp->so_mobjnr);
	return;
}

PUBLIC void init_kmsob()
{
	kmsobmgrhed_t_init(&lmos_memmgrob.mo_kmsobmgr);
	return;
}

PUBLIC void kmsob_updata_cache(kmsobmgrhed_t* kmobmgrp,koblst_t* koblp,kmsob_t* kmsp,uint_t flgs)
{
	if(KUC_NEWFLG==flgs)
	{
		kmobmgrp->ks_msobche=kmsp;
		koblp->ol_cahe=kmsp;
		return;
	}
	if(KUC_DELFLG==flgs)
	{
		kmobmgrp->ks_msobche=kmsp;
		koblp->ol_cahe=kmsp;
		return;
	}
	if(KUC_DSYFLG==flgs)
	{
		if(kmsp==kmobmgrp->ks_msobche)
		{
			kmobmgrp->ks_msobche=NULL;
		}
		if(kmsp==koblp->ol_cahe)
		{
			koblp->ol_cahe=NULL;
		}
		return;
	}
	return;
}

PUBLIC kmsob_t* scan_newkmsob_isok(kmsob_t* kmsp,size_t msz)
{
	if(NULL==kmsp||1>msz)
	{
		return NULL;
	}
	//if(0<kmsp->so_fobjnr)
	{
		if(msz<=kmsp->so_objsz)
		{
			return kmsp;
		}
	}
	return NULL;
}
PUBLIC kmsob_t* scan_delkmsob_isok(kmsob_t *kmsp,void* fadrs,size_t fsz)
{
	if(NULL==kmsp||NULL==fadrs||1>fsz)
	{
		return NULL;
	}
	if((adr_t)fadrs>=(kmsp->so_vstat+sizeof(kmsob_t))&&((adr_t)fadrs+(adr_t)fsz)<=kmsp->so_vend)
	{
		if(fsz<=kmsp->so_objsz)
		{
			return kmsp;
		}
	}
	if(1>kmsp->so_mextnr)
	{
		return NULL;
	}
	kmbext_t* bexp=NULL;
	list_h_t* tmplst=NULL;
	list_for_each(tmplst,&kmsp->so_mextlst)
	{
		bexp=list_entry(tmplst,kmbext_t,mt_list);
		if(bexp->mt_kmsb!=kmsp)
		{
			system_error("scan_delkmsob_isok err\n");
		}
		if((adr_t)fadrs>=(bexp->mt_vstat+sizeof(kmbext_t))&&((adr_t)fadrs+(adr_t)fsz)<=bexp->mt_vend)
		{
			if(fsz<=kmsp->so_objsz)
			{
				return kmsp;
			}
		}
	}

	return NULL;
}

PUBLIC bool_t scan_nmszkmsob_isok(kmsob_t* kmsp,size_t msz)
{
	if(NULL==kmsp||1>msz)
	{
		return FALSE;
	}
	if(1>kmsp->so_fobjnr||1>kmsp->so_mobjnr)
	{
		return FALSE;
	}
	if(msz>kmsp->so_objsz)
	{
		return FALSE;
	}
	if((kmsp->so_vend-kmsp->so_vstat+1)<PAGESIZE||
		(kmsp->so_vend-kmsp->so_vstat+1)<(adr_t)(sizeof(kmsob_t)+sizeof(freobjh_t)))
	{
		return FALSE;
	}
	if(list_is_empty_careful(&kmsp->so_frelst)==TRUE)
	{
		return FALSE;
	}
	return TRUE;
}

PUBLIC bool_t scan_fadrskmsob_isok(adr_t fostat,adr_t vend,void* fadrs,size_t objsz)
{
	/*if((vend-fostat+1)<PAGESIZE)
	{
		return FALSE;
	}*/
	if((adr_t)fadrs<fostat)
	{
		return FALSE;
	}
	//uint_t obnr=0;
	if((adr_t)fadrs>=fostat&&((adr_t)fadrs+(adr_t)objsz)<=vend)
	{
		if(0==(((adr_t)fadrs-fostat)%objsz))
		{
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

PUBLIC bool_t scan_dfszkmsob_isok(kmsob_t* kmsp,void* fadrs,size_t fsz)
{
	list_h_t* tmplst=NULL;
	kmbext_t* bextp=NULL;
	if(NULL==kmsp||NULL==fadrs||1>fsz)
	{
		return FALSE;
	}
	/*if(fsz<sizeof(freobjh_t))
	{
		return FALSE;
	}*/
	if((~0UL)<=kmsp->so_fobjnr)
	{
		return FALSE;
	}
	if((adr_t)fadrs>=kmsp->so_vstat&&((adr_t)fadrs+(adr_t)fsz-1)<=kmsp->so_vend)
	{
		if(FALSE==scan_fadrskmsob_isok((adr_t)(kmsp+1),kmsp->so_vend,fadrs,kmsp->so_objsz))
		{
			return FALSE;
		}
		return TRUE;
	}
	if(kmsp->so_mextnr>0)
	{
		list_for_each(tmplst,&kmsp->so_mextlst)
		{
			bextp=list_entry(tmplst,kmbext_t,mt_list);
			if((adr_t)fadrs>=bextp->mt_vstat&&((adr_t)fadrs+(adr_t)fsz-1)<=bextp->mt_vend)
			{
				if(FALSE==scan_fadrskmsob_isok((adr_t)(bextp+1),bextp->mt_vend,fadrs,kmsp->so_objsz))
				{
					return FALSE;
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

PUBLIC uint_t scan_kmsob_objnr(kmsob_t* kmsp)
{
	if(NULL==kmsp)
	{
		system_error("scan_kmsob_objnr err1\n");
	}
	if(1>kmsp->so_fobjnr&&list_is_empty_careful(&kmsp->so_frelst)==FALSE)
	{
		system_error("scan_kmsob_objnr err2\n");
	}
	if(0<kmsp->so_fobjnr)
	{
		return kmsp->so_fobjnr;
	}
	return 0;
}

PUBLIC kmsob_t* onkoblst_retn_newkmsob(koblst_t* koblp,size_t msz)
{
	kmsob_t* kmsp=NULL,*tkmsp=NULL;
	list_h_t* tmplst=NULL;
	if(NULL==koblp||1>msz)
	{
		return NULL;
	}
	kmsp=scan_newkmsob_isok(koblp->ol_cahe,msz);
	if(NULL!=kmsp)
	{
		return kmsp;
	}
	/*if(0<koblp->ol_efnr)
	{
		list_for_each(tmplst,&koblp->ol_efulst)
		{
			tkmsp=list_entry(tmplst,kmsob_t,so_list);
			kmsp=scan_newkmsob_isok(tkmsp,msz);
			if(NULL!=kmsp)
			{
				return kmsp;
			}
		}
	}*/
	if(0<koblp->ol_emnr)
	{
		list_for_each(tmplst,&koblp->ol_emplst)
		{
			tkmsp=list_entry(tmplst,kmsob_t,so_list);
			kmsp=scan_newkmsob_isok(tkmsp,msz);
			if(NULL!=kmsp)
			{
				return kmsp;
			}
		}
	}
	return NULL;
}

PUBLIC kmsob_t* onkoblst_retn_delkmsob(koblst_t *koblp,void* fadrs,size_t fsz)
{
	kmsob_t* kmsp=NULL,*tkmsp=NULL;
	list_h_t* tmplst=NULL;
	if(NULL==koblp||NULL==fadrs||1>fsz)
	{
		return NULL;
	}
	kmsp=scan_delkmsob_isok(koblp->ol_cahe,fadrs,fsz);
	if(NULL!=kmsp)
	{
		return kmsp;
	}
	/*if(0<koblp->ol_efnr)
	{
		list_for_each(tmplst,&koblp->ol_efulst)
		{
			tkmsp=list_entry(tmplst,kmsob_t,so_list);
			kmsp=scan_delkmsob_isok(tkmsp,fadrs,fsz);
			if(NULL!=kmsp)
			{
				return kmsp;
			}
		}
	}*/
	if(0<koblp->ol_emnr)
	{
		list_for_each(tmplst,&koblp->ol_emplst)
		{
			tkmsp=list_entry(tmplst,kmsob_t,so_list);
			kmsp=scan_delkmsob_isok(tkmsp,fadrs,fsz);
			if(NULL!=kmsp)
			{
				return kmsp;
			}
		}
	}
	return NULL;	
}

PUBLIC koblst_t* onmsz_retn_koblst(kmsobmgrhed_t* kmmgrhlokp,size_t msz)
{
	if(NULL==kmmgrhlokp||1>msz)
	{
		return NULL;
	}
	for(uint_t kli=0;kli<KOBLST_MAX;kli++)
	{
		if(kmmgrhlokp->ks_msoblst[kli].ol_sz>=msz)
		{
			return &kmmgrhlokp->ks_msoblst[kli];
		}
	}
	return NULL;
}

PUBLIC bool_t kmsob_add_koblst(koblst_t* koblp,kmsob_t* kmsp)
{
	if(NULL==koblp||NULL==kmsp)
	{
		return FALSE;
	}
	if(kmsp->so_objsz>koblp->ol_sz)
	{
		return FALSE;
	}
	list_add(&kmsp->so_list,&koblp->ol_emplst);
	koblp->ol_emnr++;
	return TRUE;
}

PUBLIC kmsob_t* _create_init_kmsob(kmsob_t* kmsp,size_t objsz,adr_t cvadrs,adr_t cvadre,msadsc_t* msa,uint_t relpnr)
{
	if(NULL==kmsp||1>objsz||NULL==cvadrs||NULL==cvadre||NULL==msa||1>relpnr)
	{
		return NULL;
	}
	if(objsz<sizeof(freobjh_t))
	{
		return NULL;
	}
	if((cvadre-cvadrs+1)<PAGESIZE)
	{
		return NULL;
	}
	if((cvadre-cvadrs+1)<=(sizeof(kmsob_t)+sizeof(freobjh_t)))
	{
		return NULL;
	}
	/*sint_t mscidx=retn_mscidx(relpnr);
	if(MSCLST_MAX<=mscidx||0>mscidx)
	{
		return NULL;
	}*/
	kmsob_t_init(kmsp);
	/*if(kmsp->so_mc.mc_lst[mscidx].ml_ompnr!=relpnr)
	{
		system_error("_create_init_kmsob ml_ompnr!=relpnr\n");
	}*/
	kmsp->so_vstat=cvadrs;
	kmsp->so_vend=cvadre;
	kmsp->so_objsz=objsz;

	list_add(&msa->md_list,&kmsp->so_mc.mc_kmobinlst);
	kmsp->so_mc.mc_kmobinpnr=(uint_t)relpnr;
	
	freobjh_t* fohstat=(freobjh_t*)(kmsp+1),*fohend=(freobjh_t*)cvadre;
	
	uint_t ap=(uint_t)((uint_t)fohstat);
	freobjh_t* tmpfoh=(freobjh_t*)((uint_t)ap);
	for(;tmpfoh<fohend;)
	{
		//ap+=(uint_t)kmsp->so_objsz;
		if((ap+(uint_t)kmsp->so_objsz)<=(uint_t)cvadre)
		{
			freobjh_t_init(tmpfoh,0,(void*)tmpfoh);
			list_add(&tmpfoh->oh_list,&kmsp->so_frelst);
			kmsp->so_mobjnr++;
			kmsp->so_fobjnr++;
		}
		ap+=(uint_t)kmsp->so_objsz;
		tmpfoh=(freobjh_t*)((uint_t)ap);
	}
	return kmsp;
}


PUBLIC kmsob_t* _create_kmsob(kmsobmgrhed_t* kmmgrlokp,koblst_t* koblp,size_t objsz)
{
	if(NULL==kmmgrlokp||NULL==koblp||1>objsz)
	{
		return NULL;
	}
	kmsob_t* kmsp=NULL;
	msadsc_t* msa=NULL;
	uint_t relpnr=0;
	uint_t pages=1;
	if(128<objsz)
	{
		pages=2;
	}
	if(512<objsz)
	{
		pages=4;
	}
	msa=mm_division_pages(&lmos_memmgrob,pages,&relpnr,MA_TYPE_KRNL,DMF_RELDIV);
	if(NULL==msa)
	{
		return NULL;
	}
	if(NULL!=msa&&0==relpnr)
	{
		system_error("_create_kmsob mm_division_pages fail\n");
		return NULL;
	}
	u64_t phyadr=msa->md_phyadrs.paf_padrs<<PSHRSIZE;
	u64_t phyade=phyadr+(relpnr<<PSHRSIZE)-1;
	adr_t vadrs=krnlphyiadr_to_viradr((adr_t)phyadr);
	adr_t vadre=krnlphyiadr_to_viradr((adr_t)phyade);
	kmsp=_create_init_kmsob((kmsob_t*)vadrs,koblp->ol_sz,vadrs,vadre,msa,relpnr);
	if(NULL==kmsp)
	{
		if(mm_merge_pages(&lmos_memmgrob,msa,relpnr)==FALSE)
		{
			system_error("_create_kmsob mm_merge_pages fail\n");
		}
		return NULL;
		//system_error("_create_kmsob _create_init_kmsob fail\n");
	}
	if(kmsob_add_koblst(koblp,kmsp)==FALSE)
	{
		system_error(" _create_kmsob kmsob_add_koblst FALSE\n");
	}
	kmmgrlokp->ks_msobnr++;
	//disp_kmsob(kmsp);
	return kmsp;
}

PUBLIC void* kmsob_new_opkmsob(kmsob_t* kmsp,size_t msz)
{
	if(NULL==kmsp||1>msz)
	{
		return NULL;
	}
	if(scan_nmszkmsob_isok(kmsp,msz)==FALSE)
	{
		return NULL;
	}
	freobjh_t* fobh=list_entry(kmsp->so_frelst.next,freobjh_t,oh_list);
	list_del(&fobh->oh_list);
	kmsp->so_fobjnr--;
	return (void*)(fobh);
}

PUBLIC bool_t kmsob_extn_pages(kmsob_t* kmsp)
{
	if(NULL==kmsp)
	{
		return FALSE;
	}
	if((~0UL)<=kmsp->so_mobjnr||(~0UL)<=kmsp->so_mextnr||(~0UL)<=kmsp->so_fobjnr)
	{
		return FALSE;
	}
	msadsc_t* msa=NULL;
	uint_t relpnr=0;
	uint_t pages=1;
	if(128<kmsp->so_objsz)
	{
		pages=2;
	}
	if(512<kmsp->so_objsz)
	{
		pages=4;
	}
	msa=mm_division_pages(&lmos_memmgrob,pages,&relpnr,MA_TYPE_KRNL,DMF_RELDIV);
	if(NULL==msa)
	{
		return FALSE;
	}
	if(NULL!=msa&&0==relpnr)
	{
		system_error("kmsob_extn_pages mm_division_pages fail\n");
		return FALSE;
	}
	u64_t phyadr=msa->md_phyadrs.paf_padrs<<PSHRSIZE;
	u64_t phyade=phyadr+(relpnr<<PSHRSIZE)-1;
	adr_t vadrs=krnlphyiadr_to_viradr((adr_t)phyadr);
	adr_t vadre=krnlphyiadr_to_viradr((adr_t)phyade);
	sint_t mscidx=retn_mscidx(relpnr);
	if(MSCLST_MAX<=mscidx||0>mscidx)
	{
		if(mm_merge_pages(&lmos_memmgrob,msa,relpnr)==FALSE)
		{
			system_error("kmsob_extn_pages mm_merge_pages fail\n");
		}
		return FALSE;
	}
	list_add(&msa->md_list,&kmsp->so_mc.mc_lst[mscidx].ml_list);
	kmsp->so_mc.mc_lst[mscidx].ml_msanr++;
	/*if(vadrs<kmsp->so_vstat)
	{
		kmsp->so_vstat=vadrs;
	}
	if(vadre>kmsp->so_vend)
	{
		kmsp->so_vend=vadre;
	}*/
	kmbext_t* bextp=(kmbext_t*)vadrs;
	kmbext_t_init(bextp,vadrs,vadre,kmsp);

	freobjh_t* fohstat=(freobjh_t*)(bextp+1),*fohend=(freobjh_t*)vadre;

	uint_t ap=(uint_t)((uint_t)fohstat);
	freobjh_t* tmpfoh=(freobjh_t*)((uint_t)ap);
	for(;tmpfoh<fohend;)
	{
		//ap+=(uint_t)kmsp->so_objsz;
		if((ap+(uint_t)kmsp->so_objsz)<=(uint_t)vadre)
		{
			freobjh_t_init(tmpfoh,0,(void*)tmpfoh);
			list_add(&tmpfoh->oh_list,&kmsp->so_frelst);
			kmsp->so_mobjnr++;
			kmsp->so_fobjnr++;
			bextp->mt_mobjnr++;
		}
		ap+=(uint_t)kmsp->so_objsz;
		tmpfoh=(freobjh_t*)((uint_t)ap);
	}
	list_add(&bextp->mt_list,&kmsp->so_mextlst);
	kmsp->so_mextnr++;
	return TRUE;
}

PUBLIC void* kmsob_new_onkmsob(kmsob_t* kmsp,size_t msz)
{
	if(NULL==kmsp||1>msz)
	{
		return NULL;
	}
	void* retptr=NULL;
	cpuflg_t cpuflg;
	knl_spinlock_cli(&kmsp->so_lock,&cpuflg);
	if(scan_kmsob_objnr(kmsp)<1)
	{
		//kprint("kmsob_extn_pages\n");
		if(kmsob_extn_pages(kmsp)==FALSE)
		{
			retptr=NULL;
			goto ret_step;
		}
	}
	retptr=kmsob_new_opkmsob(kmsp,msz);
	//disp_kmsob(kmsp);
ret_step:
	knl_spinunlock_sti(&kmsp->so_lock,&cpuflg);
	return retptr;
}

PUBLIC void* kmsob_new_core(size_t msz)
{
	kmsobmgrhed_t* kmobmgrp=&lmos_memmgrob.mo_kmsobmgr;
	void* retptr=NULL;
	koblst_t* koblp=NULL;
	kmsob_t* kmsp=NULL;
	cpuflg_t cpuflg;
	knl_spinlock_cli(&kmobmgrp->ks_lock,&cpuflg);
	koblp=onmsz_retn_koblst(kmobmgrp,msz);
	if(NULL==koblp)
	{
		retptr=NULL;
		goto ret_step;
	}
	kmsp=onkoblst_retn_newkmsob(koblp,msz);
	if(NULL==kmsp)
	{
		kmsp=_create_kmsob(kmobmgrp,koblp,koblp->ol_sz);
		if(NULL==kmsp)
		{
			retptr=NULL;
			goto ret_step;
		}
	}
	retptr=kmsob_new_onkmsob(kmsp,msz);
	if(NULL==retptr)
	{
		retptr=NULL;
		goto ret_step;
	}
	kmsob_updata_cache(kmobmgrp,koblp,kmsp,KUC_NEWFLG);
ret_step:
	knl_spinunlock_sti(&kmobmgrp->ks_lock,&cpuflg);
	return retptr;
}

PUBLIC void* kmsob_new(size_t msz)
{
	if(1>msz||2048<msz)
	{
		return NULL;
	}
	return kmsob_new_core(msz);
}

PUBLIC uint_t scan_freekmsob_isok(kmsob_t* kmsp)
{
	if(NULL==kmsp)
	{
		return 0;
	}
	if(kmsp->so_mobjnr<kmsp->so_fobjnr)
	{
		return 0;
	}
	if(kmsp->so_mobjnr==kmsp->so_fobjnr)
	{
		return 2;
	}
	return 1;
}

PUBLIC bool_t _destroy_kmsob_core(kmsobmgrhed_t* kmobmgrp,koblst_t* koblp,kmsob_t* kmsp)
{
	if(NULL==kmobmgrp||NULL==koblp||NULL==kmsp)
	{
		return FALSE;
	}
	if(1>kmsp->so_mc.mc_kmobinpnr||list_is_empty_careful(&kmsp->so_mc.mc_kmobinlst)==TRUE)
	{
		return FALSE;
	}
	list_h_t* tmplst=NULL;
	msadsc_t* msa=NULL;
	msclst_t* mscp=kmsp->so_mc.mc_lst;
	list_del(&kmsp->so_list);
	koblp->ol_emnr--;
	kmobmgrp->ks_msobnr--;

	kmsob_updata_cache(kmobmgrp,koblp,kmsp,KUC_DSYFLG);

	for (uint_t j = 0;j<MSCLST_MAX;j++)
	{
		if(0<mscp[j].ml_msanr)
		{
			list_for_each_head_dell(tmplst,&mscp[j].ml_list)
			{
				msa=list_entry(tmplst,msadsc_t,md_list);
				list_del(&msa->md_list);
				if(mm_merge_pages(&lmos_memmgrob,msa,(uint_t)mscp[j].ml_ompnr)==FALSE)
				{
					system_error("_destroy_kmsob_core mm_merge_pages FALSE2\n");
				}
			}
		}
	}
	list_for_each_head_dell(tmplst,&kmsp->so_mc.mc_kmobinlst)
	{
		msa=list_entry(tmplst,msadsc_t,md_list);
		list_del(&msa->md_list);
		if(mm_merge_pages(&lmos_memmgrob,msa,(uint_t)kmsp->so_mc.mc_kmobinpnr)==FALSE)
		{
			system_error("_destroy_kmsob_core mm_merge_pages FALSE2\n");
		}
	}
	return TRUE; 
}

PUBLIC bool_t _destroy_kmsob(kmsobmgrhed_t* kmobmgrp,koblst_t* koblp,kmsob_t* kmsp)
{
	if(NULL==kmobmgrp||NULL==koblp||NULL==kmsp)
	{
		return FALSE;
	}
	if(1>kmobmgrp->ks_msobnr||1>koblp->ol_emnr)
	{
		return FALSE;
	}
	uint_t screts=scan_freekmsob_isok(kmsp);
	if(0==screts)
	{
		system_error("_destroy_kmsob scan_freekmsob_isok rets 0\n");
	}
	if(1==screts)
	{
		kmsob_updata_cache(kmobmgrp,koblp,kmsp, KUC_DELFLG);
		return TRUE;
	}
	if(2==screts)
	{
		//kprint("_destroy_kmsob ok\n");
		return _destroy_kmsob_core(kmobmgrp,koblp,kmsp);
	}
	return FALSE;
}
PUBLIC bool_t kmsob_del_opkmsob(kmsob_t* kmsp,void* fadrs,size_t fsz)
{
	if(NULL==kmsp||NULL==fadrs||1>fsz)
	{
		return FALSE;
	}
	if((kmsp->so_fobjnr+1)>kmsp->so_mobjnr)
	{
		return FALSE;
	}
	if(scan_dfszkmsob_isok(kmsp,fadrs,fsz)==FALSE)
	{
		return FALSE;
	}

	freobjh_t* obhp=(freobjh_t*)fadrs;
	freobjh_t_init(obhp,0,obhp);
	list_add(&obhp->oh_list,&kmsp->so_frelst);
	kmsp->so_fobjnr++;
	return TRUE;
}

PUBLIC bool_t kmsob_delete_onkmsob(kmsob_t* kmsp,void* fadrs,size_t fsz)
{
	if(NULL==kmsp||NULL==fadrs||1>fsz)
	{
		return FALSE;
	}
	bool_t rets=FALSE;
	cpuflg_t cpuflg;
	knl_spinlock_cli(&kmsp->so_lock,&cpuflg);
	if(kmsob_del_opkmsob(kmsp,fadrs,fsz)==FALSE)
	{
		rets=FALSE;
		goto ret_step;
	}
	rets=TRUE;
ret_step:
	knl_spinunlock_sti(&kmsp->so_lock,&cpuflg);
	return rets;	
}

PUBLIC bool_t kmsob_delete_core(void* fadrs,size_t fsz)
{
	kmsobmgrhed_t* kmobmgrp=&lmos_memmgrob.mo_kmsobmgr;
	bool_t rets=FALSE;
	koblst_t* koblp=NULL;
	kmsob_t* kmsp=NULL;
	cpuflg_t cpuflg;
	knl_spinlock_cli(&kmobmgrp->ks_lock,&cpuflg);
	koblp=onmsz_retn_koblst(kmobmgrp,fsz);
	if(NULL==koblp)
	{
		rets=FALSE;
		goto ret_step;
	}
	kmsp=onkoblst_retn_delkmsob(koblp,fadrs,fsz);
	if(NULL==kmsp)
	{
		rets=FALSE;
		goto ret_step;
	}
	rets=kmsob_delete_onkmsob(kmsp,fadrs,fsz);
	if(FALSE==rets)
	{
		rets=FALSE;
		goto ret_step;
	}
	if(_destroy_kmsob(kmobmgrp,koblp,kmsp)==FALSE)
	{
		rets=FALSE;
		goto ret_step;
	}
	rets=TRUE;
ret_step:
	knl_spinunlock_sti(&kmobmgrp->ks_lock,&cpuflg);
	return rets;
}

PUBLIC bool_t kmsob_delete(void* fadrs,size_t fsz)
{
	if(NULL==fadrs||1>fsz||2048<fsz)
	{
		return FALSE;
	}
	return kmsob_delete_core(fadrs,fsz); 
}

PUBLIC bool_t chek_kmbext_findmsa(kmsob_t* kmsp,kmbext_t* cpbexp)
{
	uint_t pnr=(cpbexp->mt_vend-cpbexp->mt_vstat+1)>>PSHRSIZE;
	sint_t msci=retn_mscidx(pnr);
	if(0>msci||MSCLST_MAX<=msci)
	{
		return FALSE;
	}
	if(kmsp->so_mc.mc_lst[msci].ml_ompnr!=pnr)
	{
		return FALSE;
	}
	uint_t phyadr=(uint_t)krnlvirtadr_to_phyadr(cpbexp->mt_vstat);
	list_h_t* tmplst=NULL;
	msadsc_t* msa=NULL;
	list_for_each(tmplst,&kmsp->so_mc.mc_lst[msci].ml_list)
	{
		msa=list_entry(tmplst,msadsc_t,md_list);
		if((msa->md_phyadrs.paf_padrs<<PSHRSIZE)==phyadr)
		{
			return TRUE;
		}
	}
	return FALSE;
}

PUBLIC bool_t chek_one_kmbext(kmsob_t* kmsp,kmbext_t* cpbexp)
{
	list_h_t* tmplst=NULL;
	kmbext_t* bexp=NULL;
	list_for_each(tmplst,&kmsp->so_mextlst)
	{
		bexp=list_entry(tmplst,kmbext_t,mt_list);
		if(bexp!=cpbexp)
		{
			if((bexp->mt_vstat>=cpbexp->mt_vstat&&
				bexp->mt_vstat<=cpbexp->mt_vend))
			{
				return FALSE;
			}
			if(chek_kmbext_findmsa(kmsp,cpbexp)==FALSE)
			{
				return FALSE;
			}

		}
		if(chek_kmbext_findmsa(kmsp,bexp)==FALSE)
		{
			return FALSE;
		}
	}
	return TRUE;
}

PUBLIC bool_t chek_onekmsob_mbext(kmsob_t* kmsp)
{
	size_t mobsz=kmsp->so_mobjnr*kmsp->so_objsz;
	size_t kbsz=kmsp->so_vend-(adr_t)(kmsp+1)+1;
	if(mobsz>kbsz&&kmsp->so_mextnr<1)
	{
		system_error("chek_onekmsob_mbext err1\n");
	}
	if(kmsp->so_mextnr==0)
	{
		return TRUE;
	}
	list_h_t* tmplst=NULL;
	kmbext_t* bexp=NULL;
	list_for_each(tmplst,&kmsp->so_mextlst)
	{
		bexp=list_entry(tmplst,kmbext_t,mt_list);
		if(chek_one_kmbext(kmsp,bexp)==FALSE)
		{
			return FALSE;
		}
	}
	return TRUE;
}

PUBLIC void chek_one_kmsob(kmsob_t* kmsp,size_t objsz)
{
	if(NULL==kmsp)
	{
		system_error("chek_one_kmsob err1\n");
	}
	if(kmsp->so_objsz!=objsz)
	{
		system_error("chek_one_kmsob err2\n");
	}
	if(list_is_empty_careful(&kmsp->so_mc.mc_kmobinlst)==TRUE)
	{
		system_error("chek_one_kmsob err3\n");
	}
	msadsc_t* msa=list_entry(kmsp->so_mc.mc_kmobinlst.next,msadsc_t,md_list);
	if(kmsp->so_vstat!=krnlphyiadr_to_viradr((adr_t)(msa->md_phyadrs.paf_padrs<<PSHRSIZE)))
	{
		system_error("chek_one_kmsob err4\n");
	}
	if(((kmsp->so_vend-kmsp->so_vstat+1)>>PSHRSIZE)!=kmsp->so_mc.mc_kmobinpnr)
	{
		system_error("chek_one_kmsob err5\n");
	}
	if(chek_onekmsob_mbext(kmsp)==FALSE)
	{
		system_error("chek_one_kmsob err6\n");
	}
	return;
}

PUBLIC void chek_all_kmsobstruc()
{
	kmsob_t* kmsp=NULL;
	list_h_t* tmplst=NULL;
	uint_t nr=0;
	for(uint_t i=0;i<KOBLST_MAX;i++)
	{
		list_for_each(tmplst,&lmos_memmgrob.mo_kmsobmgr.ks_msoblst[i].ol_emplst)
		{
			kmsp=list_entry(tmplst,kmsob_t,so_list);
			chek_one_kmsob(kmsp,lmos_memmgrob.mo_kmsobmgr.ks_msoblst[i].ol_sz);
			kprint("chek_one_kmsob:%d\n",nr);
			nr++;
		}
	}
	return;
}

PUBLIC void kobcks_init(kobcks_t* initp,void* vadr,size_t sz)
{
	list_init(&initp->kk_list);
	initp->kk_vadr=vadr;
	initp->kk_sz=sz;
	return;
}
PUBLIC void write_kobcks(kmsobmgrhed_t* kmmgrp,void* ptr,size_t sz)
{
	if(NULL==kmmgrp||NULL==ptr||1>sz)
	{
		system_error("write_kobcks err\n");
	}
	kobcks_t* kkp=(kobcks_t*)ptr;
	kobcks_init(kkp,ptr,sz);
	list_add(&kkp->kk_list,&kmmgrp->ks_tclst);
	kmmgrp->ks_tcnr++;
	return;
}

PUBLIC void chek_one_kobcks(kobcks_t* kkp)
{
	list_h_t* tmplst=NULL;
	kobcks_t* tkkp=NULL;
	list_for_each(tmplst,&lmos_memmgrob.mo_kmsobmgr.ks_tclst)
	{
		tkkp=list_entry(tmplst,kobcks_t,kk_list);
		if(tkkp!=kkp)
		{
			if(tkkp->kk_vadr==kkp->kk_vadr)
			{
				system_error("chek_one_kobcks fail\n");
			}
		}
	}
	return;
}

PUBLIC void chek_all_kobcks()
{
	chek_all_kmsobstruc();
	die(0x600);
	list_h_t* tmplst=NULL;
	kobcks_t* kkp=NULL;
	uint_t i=0;
	list_for_each(tmplst,&lmos_memmgrob.mo_kmsobmgr.ks_tclst)
	{
		kkp=list_entry(tmplst,kobcks_t,kk_list);
		chek_one_kobcks(kkp);
		kprint("chek_one_kobcks isOK:%d\n",i);
		i++;
	}
	return;
}

PUBLIC void free_one_kobcks(kobcks_t* kkp)
{
	//kprint("free_one_kobcks kkp->kk_vadr:%x,kk_sz:%x\n",kkp->kk_vadr,kkp->kk_sz);
	if(1>lmos_memmgrob.mo_kmsobmgr.ks_tcnr)
	{
		system_error("free_one_kobcks err1\n");
	}
	list_del(&kkp->kk_list);

	if(kmsob_delete(kkp->kk_vadr,kkp->kk_sz)==FALSE)
	{
		kprint("kkp->kk_vadr:%x sz:%x\n",kkp->kk_vadr,kkp->kk_sz);
		system_error("free_one_kobcks fail\n");
	}
	
	lmos_memmgrob.mo_kmsobmgr.ks_tcnr--;
	return;
}

PUBLIC void free_all_kobcks()
{
	list_h_t* tmplst=NULL;
	kobcks_t* kkp=NULL;
	uint_t i=0;

	/*list_for_each(tmplst,&lmos_memmgrob.mo_kmsobmgr.ks_tclst)
	{
		kkp=list_entry(tmplst,kobcks_t,kk_list);
		//free_one_kobcks(kkp);
		
		break;	
	}*/
//rs_free:
	list_for_each_head_dell(tmplst,&lmos_memmgrob.mo_kmsobmgr.ks_tclst)
	{
		kkp=list_entry(tmplst,kobcks_t,kk_list);
		free_one_kobcks(kkp);
		kprint("free_one_kobcks isOK:%d\n",i);
		i++;
		//goto rs_free;
	}
	kprint("free_all_kobcks OK\n");
	return;
}

PUBLIC void  test_kmsob()
{
	void* ptr=NULL;
	u64_t stsc=0,etsc=0;
	size_t sz=1;
	kprint("我笃信优秀的操作系统,起始于精湛的内存管理......\n");
	for(uint_t n=0;n<2048;n++,sz++)
	{
	for(uint_t i=0;i<5;i++)
	{
		stsc=x86_rdtsc();
		ptr=kmsob_new(sz);
		etsc=x86_rdtsc();
		if(NULL==ptr)
		{
			kprint("FREEPAGES:%x ALLOCPAGES:%x MAXPAGES:%x KMSOBNR:%x OBJNR:%x\n",(uint_t)lmos_memmgrob.mo_freepages,(uint_t)lmos_memmgrob.mo_alocpages,
				(uint_t)lmos_memmgrob.mo_maxpages,(uint_t)lmos_memmgrob.mo_kmsobmgr.ks_msobnr,
				(uint_t)lmos_memmgrob.mo_kmsobmgr.ks_tcnr);
			system_error("test_kmsob kmsob_new ret NULL\n");
		}
		kprint("找不到对象就NEW一个: _new 对象大小:%x retnadrs:%x CPU时钟周期:%x\n",sz,(uint_t)ptr,etsc-stsc);
		write_kobcks(&lmos_memmgrob.mo_kmsobmgr,ptr,sz);
		//kprint("kmsob_delete is ok\n");
	}
	}
	return;
}

/*

if(kmsob_delete(ptr,sz)==FALSE)
		{
			system_error("kmsob_delete fail\n");
		}
*/