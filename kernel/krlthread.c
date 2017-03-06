/**********************************************************
        LMOSEM线程管理文件krlthread.c
***********************************************************
                彭东 ＠ 2013.08.03.16.00
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"
void micrstk_t_init(micrstk_t* initp)
{
    for(uint_t i=0;i<MICRSTK_MAX;i++)
    {
        initp->msk_val[i]=0;
    }
    return;
}
    
void context_t_init(context_t* initp)
{
    initp->ctx_usrsp=0;
    initp->ctx_svcsp=0;
    initp->ctx_svcspsr=0;
    initp->ctx_cpsr=0;
    initp->ctx_lr=0;
#ifdef CFG_X86_PLATFORM
    initp->ctx_nxteip=0;
    initp->ctx_nxtesp=0;
    initp->ctx_nxtcs=0;
    initp->ctx_nxtss=0;
    initp->ctx_nxttss=&tss[hal_retn_cpuid()];
#endif
    return;
}
uint_t krlretn_thread_id(thread_t* tdp)
{
	return (uint_t)tdp;
}
void thread_t_init(thread_t* initp)
{
    hal_spinlock_init(&initp->td_lock);
    list_init(&initp->td_list);
    initp->td_flgs=0;
    initp->td_stus=TDSTUS_NEW;
    initp->td_cpuid=hal_retn_cpuid();
    initp->td_id=krlretn_thread_id(initp);
    initp->td_tick=0;
    initp->td_privilege=PRILG_USR;
    initp->td_priority=PRITY_MIN;
    initp->td_runmode=0;
    initp->td_krlstktop=NULL;
    initp->td_krlstkstart=NULL;
    initp->td_usrstktop=NULL;
    initp->td_usrstkstart=NULL;
   
    initp->td_mmdsc=NULL;
    initp->td_resdsc=NULL;
    initp->td_privtep=NULL;
    initp->td_extdatap=NULL;
    context_t_init(&initp->td_context);
    for(uint_t hand=0;hand<TD_HAND_MAX;hand++)
    {
        initp->td_handtbl[hand]=NULL;
    }
    return;
}

thread_t* krlnew_thread_dsc()
{
    thread_t* rettdp=(thread_t*)(krlnew((size_t)(sizeof(thread_t))));
    if(rettdp==NULL)
    {
        return NULL;
    }
    thread_t_init(rettdp);
    return rettdp;
}

void krlthd_inc_tick(thread_t* thdp)
{
    
    cpuflg_t cpuflg;
    hal_spinlock_saveflg_cli(&thdp->td_lock,&cpuflg);
    thdp->td_tick++;
    if(thdp->td_tick>TDRUN_TICK)
    {
        thdp->td_tick=0;
        krlsched_set_schedflgs();
    }
    hal_spinunlock_restflg_sti(&thdp->td_lock,&cpuflg);
    return;
}

hand_t krlthd_retn_nullhand(thread_t* thdp)
{
    cpuflg_t cpuflg;
    hand_t rethd=NO_HAND;
    hal_spinlock_saveflg_cli(&thdp->td_lock,&cpuflg);
    for(uint_t hand=0;hand<TD_HAND_MAX;hand++)
    {
        if(thdp->td_handtbl[hand]==NULL)
        {
            rethd=(hand_t)hand;
            goto retn_step;
        }
    }
    rethd=NO_HAND;
retn_step:    
    hal_spinunlock_restflg_sti(&thdp->td_lock,&cpuflg);
    return rethd;
}

hand_t krlthd_add_objnode(thread_t* thdp,objnode_t* ondp)
{
    cpuflg_t cpuflg;
    hand_t rethd=NO_HAND;
    hal_spinlock_saveflg_cli(&thdp->td_lock,&cpuflg);
    for(uint_t hand=0;hand<TD_HAND_MAX;hand++)
    {
        if(thdp->td_handtbl[hand]==NULL)
        {
            rethd=(hand_t)hand;
            goto next_step;
        }
    }
    rethd=NO_HAND;
    goto retn_step;
    
next_step:
    thdp->td_handtbl[rethd]=ondp;    
retn_step:    
    hal_spinunlock_restflg_sti(&thdp->td_lock,&cpuflg);
    return rethd;
}

hand_t krlthd_del_objnode(thread_t *thdp, hand_t hand)
{
    if((hand>=TD_HAND_MAX)||(hand<=NO_HAND))
    {
        return NO_HAND;
    }
    
    cpuflg_t cpuflg;
    hand_t rethd=NO_HAND;
    hal_spinlock_saveflg_cli(&thdp->td_lock,&cpuflg);
    
    if(thdp->td_handtbl[hand]==NULL)
    {
        rethd=NO_HAND;
        goto retn_step;
    }
    thdp->td_handtbl[hand]=NULL;
    rethd=hand;
retn_step:    
    hal_spinunlock_restflg_sti(&thdp->td_lock,&cpuflg);
    return rethd;
}

objnode_t* krlthd_retn_objnode(thread_t *thdp, hand_t hand)
{
    if((hand>=TD_HAND_MAX)||(hand<=NO_HAND))
    {
        return NULL;
    }
    
    cpuflg_t cpuflg;
    objnode_t* retondp=NULL;
    hal_spinlock_saveflg_cli(&thdp->td_lock,&cpuflg);
    
    if(thdp->td_handtbl[hand]==NULL)
    {
        retondp=NULL;
        goto retn_step;
    }
    retondp=thdp->td_handtbl[hand];
retn_step:    
    hal_spinunlock_restflg_sti(&thdp->td_lock,&cpuflg);
    return retondp;
}
    /*reg_t rvsgs;    
    reg_t rvsfs;
    reg_t rvses;
    reg_t rvsds; 
    reg_t parmv7;//edi
    reg_t parmv6;//esi 
    reg_t parmv5;//ebp
    reg_t parmv4;//ebx
    reg_t parmv3;//edx 
    reg_t parmv2;//ecx  
    reg_t parmv1;//eax
    reg_t rvseip;    
    reg_t rvscs;
    reg_t rvseflags;
    reg_t rvsesp;
    reg_t rvsss;
    #define K_CS_IDX    0x08
#define K_DS_IDX    0x10
#define U_CS_IDX    0x1b
#define U_DS_IDX    0x23
#define K_TAR_IDX   0x28
#define UMOD_EFLAGS 0x1202*/
void krlthreadkrlsatck_init(thread_t* thdp,void* runadr,reg_t cpsr,reg_t spsr)
{
    thdp->td_krlstktop&=(~0xf);
    thdp->td_usrstktop&=(~0xf);
 #ifdef CFG_S3C2440A_PLATFORM  
    armregs_t* arp=(armregs_t*)(thdp->td_krlstktop-sizeof(armregs_t));
    arp->r0=0;
    arp->r1=0;
    arp->r2=0;
    arp->r3=0;
    arp->r4=0;
    arp->r5=0;
    arp->r6=0;
    arp->r7=0;
    arp->r8=0;
    arp->r9=0;
    arp->r10=0;
    arp->r11=0;
    arp->r12=0;
    arp->r13=(reg_t)(thdp->td_usrstktop);
    arp->r14=(reg_t)runadr;
    thdp->td_context.ctx_usrsp=(reg_t)(thdp->td_usrstktop);
    thdp->td_context.ctx_svcsp=(reg_t)(arp);
    thdp->td_context.ctx_svcspsr=spsr;
    thdp->td_context.ctx_cpsr=cpsr;
    thdp->td_context.ctx_lr=(reg_t)runadr;
#endif
#ifdef CFG_X86_PLATFORM
    intstkregs_t* arp=(intstkregs_t*)(thdp->td_krlstktop-sizeof(intstkregs_t));
    arp->rvsgs=U_DS_IDX;
    arp->rvsfs=U_DS_IDX;
    arp->rvses=U_DS_IDX;
    arp->rvsds=U_DS_IDX;
    arp->parmv7=0;
    arp->parmv6=0;
    arp->parmv5=0;
    arp->parmv4=0;
    arp->parmv3=0;
    arp->parmv2=0;
    arp->parmv1=0;
    arp->rvseip=(reg_t)runadr;
    arp->rvscs=U_CS_IDX;
    arp->rvseflags=cpsr;
    arp->rvsesp=(reg_t)(thdp->td_usrstktop);
    arp->rvsss=U_DS_IDX;
    thdp->td_context.ctx_svcspsr=spsr;
    thdp->td_context.ctx_cpsr=cpsr;
    thdp->td_context.ctx_nxtesp=((reg_t)arp);
#endif
    return;
}

thread_t* krlnew_thread_core(void* filerun,uint_t flg,uint_t prilg,uint_t prity,size_t usrstksz,size_t krlstksz)
{
    thread_t* ret_td=NULL;
    bool_t acs=FALSE;
    adr_t usrstkadr=NULL,krlstkadr=NULL;
    usrstkadr=krlnew(usrstksz);
    if(usrstkadr==NULL)
    {
        return NULL;
    }
    krlstkadr=krlnew(krlstksz);
    if(krlstkadr==NULL)
    {
        if(krldelete(usrstkadr,usrstksz)==FALSE)
        {
            return NULL;
        }
        return NULL;
    }
    ret_td=krlnew_thread_dsc();
    if(ret_td==NULL)
    {
        acs=krldelete(usrstkadr,usrstksz);
        acs=krldelete(krlstkadr,krlstksz);
        if(acs==FALSE)
        {
            return NULL;
        }
        return NULL;
    }
    
    ret_td->td_privilege=prilg;
    ret_td->td_priority=prity;

    ret_td->td_krlstktop=krlstkadr+(adr_t)(krlstksz-1);
    ret_td->td_krlstkstart=krlstkadr;
    ret_td->td_usrstktop=usrstkadr+(adr_t)(usrstksz-1);
    ret_td->td_usrstkstart=usrstkadr;
#ifdef CFG_S3C2440A_PLATFORM
    krlthreadkrlsatck_init(ret_td,filerun,DAFT_CPSR,DAFT_SPSR);
#endif
#ifdef CFG_X86_PLATFORM
    krlthreadkrlsatck_init(ret_td,filerun,UMOD_EFLAGS,UMOD_EFLAGS);
#endif
    krlschdclass_add_thread(ret_td);
    return ret_td;
}

thread_t* krlnew_thread(void* filerun,uint_t flg,uint_t prilg,uint_t prity,size_t usrstksz,size_t krlstksz)
{
    size_t tustksz=0,tkstksz=0;
    if((flg&0x1)!=0||filerun==NULL||usrstksz>DAFT_TDUSRSTKSZ||krlstksz>DAFT_TDKRLSTKSZ)
    {
        return NULL;
    }
    
    if((prilg!=PRILG_USR&&prilg!=PRILG_SYS)||(prity>PRITY_MAX))
    {
        return NULL;
    }
    if(usrstksz<DAFT_TDUSRSTKSZ)
    {
        tustksz=DAFT_TDUSRSTKSZ;    
    }
    if(krlstksz<DAFT_TDKRLSTKSZ)
    {
        tkstksz=DAFT_TDKRLSTKSZ;
    }
    
    
    return krlnew_thread_core(filerun,flg,prilg,prity,tustksz,tkstksz);
}

