/**********************************************************
        物理内存分割合并文件memdivmer.h
***********************************************************
                彭东 ＠ 2015.06.10.10.00
**********************************************************/
#ifndef _MEMDIVMER_H
#define _MEMDIVMER_H
PUBLIC void mm_update_memmgrob(uint_t realpnr,uint_t flgs);
PUBLIC void mm_update_memarea(memarea_t* malokp,uint_t pgnr,uint_t flgs);
PUBLIC memarea_t* onfrmsa_retn_marea(memmgrob_t* mmobjp,msadsc_t* freemsa,uint_t freepgs);
PUBLIC memarea_t* onmrtype_retn_marea(memmgrob_t* mmobjp,uint_t mrtype);
PUBLIC bafhlst_t* onma_retn_maxbafhlst(memarea_t* malckp);
PUBLIC msadsc_t* mm_divpages_opmsadsc(msadsc_t* msastat,uint_t mnr);
PUBLIC sint_t mm_merpages_opmsadsc(bafhlst_t* bafh,msadsc_t* freemsa,uint_t freepgs);
PUBLIC bool_t onmpgs_retn_bafhlst(memarea_t* malckp,uint_t pages,bafhlst_t** retrelbafh,bafhlst_t** retdivbafh);
PUBLIC bool_t onfpgs_retn_bafhlst(memarea_t* malckp,uint_t freepgs,bafhlst_t** retrelbf,bafhlst_t** retmerbf);
PUBLIC msadsc_t* mm_divipages_onbafhlst(bafhlst_t* bafhp);
PUBLIC bool_t mm_retnmsaob_onbafhlst(bafhlst_t* bafhp,msadsc_t** retmstat,msadsc_t** retmend);
PUBLIC bool_t scan_mapgsalloc_ok(memarea_t* malckp,uint_t pages);
PUBLIC msadsc_t* mm_maxdivpages_onmarea(memarea_t* malckp,uint_t* retrelpnr);
PUBLIC uint_t chek_divlenmsa(msadsc_t* msastat,msadsc_t* msaend,uint_t mnr);
PUBLIC bool_t mrdmb_add_msa_bafh(bafhlst_t* bafhp,msadsc_t* msastat,msadsc_t* msaend);
PUBLIC msadsc_t* mm_reldpgsdivmsa_bafhl(memarea_t *malckp, uint_t pages, uint_t *retrelpnr,bafhlst_t* relbfl,bafhlst_t* divbfl);
PUBLIC msadsc_t* mm_reldivpages_onmarea(memarea_t* malckp,uint_t pages,uint_t* retrelpnr);
PUBLIC msadsc_t* mm_prcdivpages_onmarea(memarea_t *malckp, uint_t pages, uint_t *retrelpnr);
PUBLIC msadsc_t* mm_divpages_core(memarea_t* mareap,uint_t pages,uint_t* retrealpnr,uint_t flgs);
PUBLIC msadsc_t* mm_divpages_fmwk(memmgrob_t* mmobjp,uint_t pages,uint_t* retrelpnr,uint_t mrtype,uint_t flgs);
PUBLIC msadsc_t* mm_division_pages(memmgrob_t* mmobjp,uint_t pages,uint_t*retrealpnr,uint_t mrtype,uint_t flgs);
PUBLIC memarea_t* retn_procmarea(memmgrob_t *mmobjp);
PUBLIC msadsc_t* divpages_procmarea_core(memmgrob_t *mmobjp, uint_t pages, uint_t *retrealpnr);
PUBLIC msadsc_t* mm_divpages_procmarea(memmgrob_t *mmobjp, uint_t pages, uint_t *retrealpnr);
PUBLIC bool_t scan_freemsa_isok(msadsc_t* freemsa,uint_t freepgs);
PUBLIC sint_t mm_cmsa1blk_isok(bafhlst_t* bafh,msadsc_t* _1ms,msadsc_t* _1me);
PUBLIC sint_t mm_cmsa2blk_isok(bafhlst_t* bafh,msadsc_t* _1ms,msadsc_t* _1me,msadsc_t* _2ms,msadsc_t* _2me);
PUBLIC bool_t chek_cl2molkflg(bafhlst_t* bafh,msadsc_t* _1ms,msadsc_t* _1me,msadsc_t* _2ms,msadsc_t* _2me);
PUBLIC bool_t mm_clear_2msaolflg(bafhlst_t* bafh,msadsc_t* _1ms,msadsc_t* _1me,msadsc_t* _2ms,msadsc_t* _2me);
PUBLIC sint_t mm_find_cmsa2blk(bafhlst_t* fbafh,msadsc_t** rfnms,msadsc_t** rfnme);
PUBLIC bool_t mpobf_add_msadsc(bafhlst_t* bafhp,msadsc_t* freemstat,msadsc_t* freemend);
PUBLIC bool_t mm_merpages_onbafhlst(msadsc_t* freemsa,uint_t freepgs,bafhlst_t* relbf,bafhlst_t* merbf);
PUBLIC bool_t mm_merpages_onmarea(memarea_t* malckp,msadsc_t* freemsa,uint_t freepgs);
PUBLIC bool_t mm_merpages_core(memarea_t* marea,msadsc_t* freemsa,uint_t freepgs);
PUBLIC bool_t mm_merpages_fmwk(memmgrob_t* mmobjp,msadsc_t* freemsa,uint_t freepgs);
PUBLIC bool_t mm_merge_pages(memmgrob_t* mmobjp,msadsc_t* freemsa,uint_t freepgs);
PUBLIC void mchkstuc_t_init(mchkstuc_t* initp);
PUBLIC void write_one_mchkstuc(msadsc_t* msa,uint_t pnr);
PUBLIC bool_t chek_one_mchks(mchkstuc_t* mchs);
PUBLIC void cmp_mchkstuc(mchkstuc_t* smchs,mchkstuc_t* dmchs);
PUBLIC void free_one_mchkstuc(mchkstuc_t* mchs);
PUBLIC void free_all_mchkstuc();
PUBLIC void chek_all_one_mchkstuc(mchkstuc_t* mchs);
PUBLIC void chek_all_mchkstuc();
PUBLIC uint_t retn_test_sec();
PUBLIC void test_proc_marea(memarea_t* mr);
PUBLIC void test_maxone_marea(memarea_t* mr);
PUBLIC void test_onedivmer_all(memarea_t* ma);
PUBLIC void test_maxdiv_all();
PUBLIC void test_divsion_pages();
#endif