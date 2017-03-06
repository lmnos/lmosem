/**********************************************************
        物理内存区间文件memarea.h
***********************************************************
                彭东 ＠ 2015.05.13.21.10
**********************************************************/
#ifndef _MEMAREA_H
#define _MEMAREA_H
PUBLIC void arclst_t_init(arclst_t* initp);
PUBLIC mmstus_t mafo_deft_init(struct s_MEMAREA* memarea,void* valp,uint_t val);
PUBLIC mmstus_t mafo_deft_exit(struct s_MEMAREA* memarea);
PUBLIC mmstus_t mafo_deft_afry(struct s_MEMAREA* memarea,mmafrets_t* mafrspack,void* valp,uint_t val);
PUBLIC void mafuncobjs_t_init(mafuncobjs_t* initp);
PUBLIC void bafhlst_t_init(bafhlst_t* initp,u32_t stus,uint_t oder,uint_t oderpnr);
PUBLIC void memdivmer_t_init(memdivmer_t* initp);
PUBLIC void memarea_t_init(memarea_t* initp);
PUBLIC LKINIT bool_t init_memarea_core(machbstart_t* mbsp);
PUBLIC LKINIT void init_memarea();
PUBLIC bool_t find_inmarea_msadscsegmant(memarea_t* mareap,msadsc_t* fmstat,uint_t fmsanr,msadsc_t** retmsastatp,msadsc_t** retmsaendp,uint_t* retfmnr);
PUBLIC uint_t continumsadsc_is_ok(msadsc_t* prevmsa,msadsc_t* nextmsa,msadflgs_t* cmpmdfp);
PUBLIC bool_t scan_len_msadsc(msadsc_t* mstat,msadflgs_t* cmpmdfp,uint_t mnr,uint_t* retmnr);
PUBLIC uint_t check_continumsadsc(memarea_t* mareap,msadsc_t* stat,msadsc_t* end,uint_t fmnr);
PUBLIC bool_t merlove_scan_continumsadsc(memarea_t* mareap,msadsc_t* fmstat,uint_t* fntmsanr,uint_t fmsanr,msadsc_t** retmsastatp,msadsc_t** retmsaendp,uint_t* retfmnr);
PUBLIC uint_t merlove_clrflge_onmsadsc(msadsc_t* mstat,uint_t msanr);
PUBLIC uint_t merlove_setflgs_onmemarea(memarea_t* mareap,msadsc_t* mstat,uint_t msanr);
PUBLIC uint_t test_setflgs(memarea_t* mareap,msadsc_t* mstat,uint_t msanr);
PUBLIC bafhlst_t* find_continumsa_inbafhlst(memarea_t* mareap,uint_t fmnr);
PUBLIC bool_t continumsadsc_add_procmareabafh(memarea_t* mareap,bafhlst_t* bafhp,msadsc_t* fstat,msadsc_t* fend,uint_t fmnr);
PUBLIC bool_t continumsadsc_add_bafhlst(memarea_t* mareap,bafhlst_t* bafhp,msadsc_t* fstat,msadsc_t* fend,uint_t fmnr);
PUBLIC bool_t continumsadsc_mareabafh_core(memarea_t* mareap,msadsc_t** rfstat,msadsc_t** rfend,uint_t* rfmnr);
PUBLIC bool_t merlove_continumsadsc_mareabafh(memarea_t* mareap,msadsc_t* mstat,msadsc_t* mend,uint_t mnr);
PUBLIC bool_t merlove_mem_onmemarea(memarea_t* mareap,msadsc_t* mstat,uint_t msanr);
PUBLIC bool_t merlove_mem_core(machbstart_t* mbsp);
PUBLIC void init_merlove_mem();
void disp_bafhlst(bafhlst_t* bafhp);
void disp_memarea(machbstart_t* mbsp);

#endif