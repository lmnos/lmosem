/**********************************************************
        LMOSEM线程管理头文件krlthread_t.h
***********************************************************
                彭东 ＠ 2013.08.03.16.00
**********************************************************/
#ifndef _KRLTHREAD_T_H
#define _KRLTHREAD_T_H
#define TDSTUS_RUN 0
#define TDSTUS_SLEEP 3
#define TDSTUS_WAIT 4
#define TDSTUS_NEW 5
#define TDSTUS_ZOMB 6

#define TDRUN_TICK 20

#define PRITY_MAX 64
#define PRITY_MIN 0
#define PRILG_SYS 0
#define PRILG_USR 5

#define MICRSTK_MAX 4

#define DAFT_TDUSRSTKSZ 0x8000
#define DAFT_TDKRLSTKSZ 0x8000

#define DAFT_SPSR 0x10
#define DAFT_CPSR 0xd3
#define DAFT_CIDLESPSR 0x13

#define TD_HAND_MAX 8   

#define K_CS_IDX    0x08
#define K_DS_IDX    0x10
#define U_CS_IDX    0x1b
#define U_DS_IDX    0x23
#define K_TAR_IDX   0x28
#define UMOD_EFLAGS 0x1202

typedef struct s_MICRSTK
{
    uint_t msk_val[MICRSTK_MAX];
}micrstk_t;



typedef struct s_CONTEXT
{
    reg_t       ctx_usrsp;
    reg_t       ctx_svcsp;
    reg_t       ctx_svcspsr;
    reg_t       ctx_cpsr;
    reg_t       ctx_lr;
#ifdef CFG_X86_PLATFORM
    reg_t       ctx_nxteip;
    reg_t       ctx_nxtesp;
    reg_t       ctx_nxtss;
    reg_t       ctx_nxtcs;
    tss_t*      ctx_nxttss;
#endif    
}context_t;
typedef struct s_THREAD
{
    spinlock_t  td_lock;
    list_h_t    td_list;
    uint_t      td_flgs;
    uint_t      td_stus;
    uint_t      td_cpuid;
    uint_t      td_id;
    uint_t      td_tick;
    uint_t      td_privilege;
    uint_t      td_priority;
    uint_t      td_runmode;
    adr_t       td_krlstktop;
    adr_t       td_krlstkstart;
    adr_t       td_usrstktop;
    adr_t       td_usrstkstart;
    void*       td_mmdsc;
    void*       td_resdsc;
    void*       td_privtep;
    void*       td_extdatap;
    context_t   td_context;
    objnode_t*  td_handtbl[TD_HAND_MAX];
}thread_t;

#endif // KRLTHREAD_T_H
