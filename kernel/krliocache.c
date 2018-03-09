/**********************************************************
        LMOSEM IO缓存块文件krliocache.c
***********************************************************
                彭东 ＠ 2018.03.08.10.10
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void krliocheblkdsc_t_init(iocheblkdsc_t* initp)
{
	hal_spinlock_init(&initp->icd_look);
	list_init(&initp->icd_icblst);
	initp->icd_flgs = 0;
	initp->icd_icblknr = 0;
	initp->icd_priv = NULL;
	initp->icd_extp = NULL;
	return;
}

void iocheblk_t_init(iocheblk_t* initp)
{
	if (NULL == initp)
	{
		return;
	}
	hal_spinlock_init(&initp->icb_look);
	list_init(&initp->icb_list);
	initp->icb_type = 0;
	initp->icb_flgs = 0;
	initp->icb_lblknr = 0;
	initp->icb_buffer = NULL;
	initp->icb_bufsz = 0;
	initp->icb_priv = NULL;
	initp->icb_extp = NULL;
	return;
}

void init_krliocacheblk()
{
	krliocheblkdsc_t_init(&osiocheblk);
	krliocheblk_test();
	return;
}

iocheblk_t* krlnew_iocheblk()
{
    iocheblk_t* icblkp = (iocheblk_t*)krlnew((size_t)sizeof(iocheblk_t));
    if(NULL == icblkp)
    {
        return NULL;
    }
    iocheblk_t_init(icblkp);
    return icblkp;
}

bool_t krldel_iocheblk(iocheblk_t* icblkp)
{
    
    if(krldelete((adr_t)icblkp,(size_t)sizeof(iocheblk_t))==FALSE)
    {
        hal_sysdie("krldel_iocheblk err");
        return FALSE;
        
    }
    return TRUE;
}

iocheblk_t* krliocheblk_find_iocheblk(iocheblkdsc_t* icblkdsclokp, uint_t icblknr,uint_t icblksz)
{
	if(NULL == icblkdsclokp || 0 == icblknr)
	{
		return NULL;
	}
	if(1 > icblkdsclokp->icd_icblknr)
	{
		return NULL;
	}
	list_h_t* tmplst = NULL;
	iocheblk_t* reticbblk = NULL;
	list_for_each(tmplst,&icblkdsclokp->icd_icblst)
	{
		reticbblk = list_entry(tmplst,iocheblk_t,icb_list);
		if(icblknr == reticbblk->icb_lblknr)
		{
			return reticbblk;
		}
	}
	return NULL;
}

iocheblk_t* krliocheblk_alloc_core(iocheblkdsc_t* icblkdsc, uint_t icblknr,uint_t icblksz)
{
	if(NULL == icblkdsc || 0 == icblknr || ICBLK_SIZE > icblksz)
	{
		return NULL;
	}
	cpuflg_t cpuflg=0;
	iocheblk_t* reticblk = NULL;
	krlspinlock_cli(&icblkdsc->icd_look,&cpuflg);
	reticblk = krliocheblk_find_iocheblk(icblkdsc,icblknr,icblksz);
	if(NULL != reticblk)
	{
		//reticblk = reticblk;
		goto retn_step;
	}
	reticblk = krlnew_iocheblk();
	if(NULL == reticblk)
	{
		reticblk = NULL;
		goto retn_step;
	}
	adr_t buffer = krlnew(icblksz);
	if(NULL == buffer)
	{
		if(krldel_iocheblk(reticblk) == FALSE)
		{
			hal_sysdie("krliocheblk_alloc_core err!");
		}
		reticblk = NULL;
		goto retn_step;
	}
	reticblk->icb_lblknr = icblknr;
	reticblk->icb_buffer = (void*)buffer;
	reticblk->icb_bufsz = icblksz;
	list_add(&reticblk->icb_list,&icblkdsc->icd_icblst);
	icblkdsc->icd_icblknr++;
	//reticblk = reticblk;
retn_step:
	krlspinunlock_sti(&icblkdsc->icd_look,&cpuflg);
	return reticblk;
}

iocheblk_t* krliocheblk_alloc(iocheblkdsc_t* icblkdsc,uint_t icblknr,uint_t icblksz)
{
	if(NULL == icblkdsc || 0 == icblknr || ICBLK_SIZE > icblksz)
	{
		return  NULL;
	}
	return krliocheblk_alloc_core(icblkdsc,icblknr,icblksz);
}

bool_t krliocheblk_free_core(iocheblkdsc_t* icblkdsc, uint_t icblknr,uint_t icblksz)
{
	if(NULL == icblkdsc || 0 == icblknr || ICBLK_SIZE > icblksz)
	{
		return NULL;
	}
	cpuflg_t cpuflg=0;
	bool_t rets = FALSE;
	iocheblk_t* freeicblk = NULL;
	krlspinlock_cli(&icblkdsc->icd_look,&cpuflg);
	freeicblk = krliocheblk_find_iocheblk(icblkdsc,icblknr,icblksz);
	if(NULL == freeicblk)
	{
		rets = FALSE;
		goto retn_step;
	}
	if(krldelete((adr_t)freeicblk->icb_buffer,freeicblk->icb_bufsz) == FALSE)
	{
		kprint("keldelete icb_lblknr:%d icb_buffer:%x icb_bufsz:%d\n",freeicblk->icb_lblknr,freeicblk->icb_buffer,freeicblk->icb_bufsz);
		hal_sysdie("krliocheblk_free_core err");
		rets = FALSE;
		goto retn_step;
	}
	list_del(&freeicblk->icb_list);
	icblkdsc->icd_icblknr--;
	if(krldel_iocheblk(freeicblk) == FALSE)
	{
		rets = FALSE;
		goto retn_step;
	}
	rets = TRUE;
retn_step:
	krlspinunlock_sti(&icblkdsc->icd_look,&cpuflg);
	return rets;
}

bool_t krliocheblk_free(iocheblkdsc_t* icblkdsc,uint_t icblknr,uint_t icblksz)
{
	if(NULL == icblkdsc || 0 == icblknr || ICBLK_SIZE > icblksz)
	{
		return FALSE;
	}
	return krliocheblk_free_core(icblkdsc,icblknr,icblksz);
}


void krliocheblk_test()
{
	/*
	iocheblk_t* icb=NULL;
	for (int i = 1; i < 2; ++i)
	{
		icb = krliocheblk_alloc(&osiocheblk,i,ICBLK_SIZE*2);
		if(NULL == icb)
		{
			hal_sysdie("krliocheblk_test err");
		}
		kprint("icb_lblknr:%d icb_buffer:%x icb_bufsz:%d\n",icb->icb_lblknr,(uint_t)icb->icb_buffer,icb->icb_bufsz);
	}

	for (int i = 1; i < 2; ++i)
	{
		bool_t rets = krliocheblk_free(&osiocheblk,i,ICBLK_SIZE*2);
		if(FALSE == rets)
		{
			hal_sysdie("krliocheblk_test 2  err");
		}
		kprint("krliocheblk_free OK\n");
	}
	hal_sysdie("krliocheblk_test  ok");*/
	kprint("LMOSEM:\n");
	kprint("LMOSEM:\n");
	kprint("LMOSEM:\n");
	kprint("LMOSEM:\n");
	kprint("LMOSEM:\n");
	kprint("LMOSEM:\n");
	kprint("LMOSEM:\n");
	kprint("LMOSEM:\n");
	kprint("LMOSEM:\n");
	kprint("LMOSEM:\n");
	
	size_t msz=ICBLK_SIZE;
	adr_t adrr=krlnew(msz);
	kprint("adrr:%x\n",adrr);
	if(krldelete(adrr,msz)==FALSE)
	{
		hal_sysdie("krldelete  err");
	}
	hal_sysdie("krliocheblk_test  ok");
}