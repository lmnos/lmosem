/**********************************************************
        内核内存空间对象分配释放头文件kmsob.h
***********************************************************
                彭东 ＠ 2015.06.26.22.00
**********************************************************/
#ifndef _KMSOB_H
#define _KMSOB_H
PUBLIC void msclst_t_init(msclst_t* initp,uint_t pnr);
PUBLIC void msomdc_t_init(msomdc_t* initp);
PUBLIC void freobjh_t_init(freobjh_t* initp,uint_t stus,void* stat);
PUBLIC void kmsob_t_init(kmsob_t* initp);
PUBLIC void kmbext_t_init(kmbext_t* initp,adr_t vstat,adr_t vend,kmsob_t*kmsp);
PUBLIC void koblst_t_init(koblst_t* initp,size_t koblsz);
PUBLIC void kmsobmgrhed_t_init(kmsobmgrhed_t* initp);
PUBLIC void disp_kmsobmgr();
PUBLIC void disp_kmsob(kmsob_t* kmsp);
PUBLIC void init_kmsob();
PUBLIC void kmsob_updata_cache(kmsobmgrhed_t* kmobmgrp,koblst_t* koblp,kmsob_t* kmsp,uint_t flgs);
PUBLIC kmsob_t* scan_newkmsob_isok(kmsob_t* kmsp,size_t msz);
PUBLIC kmsob_t* scan_delkmsob_isok(kmsob_t *kmsp,void* fadrs,size_t fsz);
PUBLIC bool_t scan_nmszkmsob_isok(kmsob_t* kmsp,size_t msz);
PUBLIC bool_t scan_fadrskmsob_isok(adr_t fostat,adr_t vend,void* fadrs,size_t objsz);
PUBLIC bool_t scan_dfszkmsob_isok(kmsob_t* kmsp,void* fadrs,size_t fsz);
PUBLIC uint_t scan_kmsob_objnr(kmsob_t* kmsp);
PUBLIC kmsob_t* onkoblst_retn_newkmsob(koblst_t* koblp,size_t msz);
PUBLIC kmsob_t* onkoblst_retn_delkmsob(koblst_t *koblp,void* fadrs,size_t fsz);
PUBLIC koblst_t* onmsz_retn_koblst(kmsobmgrhed_t* kmmgrhlokp,size_t msz);
PUBLIC bool_t kmsob_add_koblst(koblst_t* koblp,kmsob_t* kmsp);
PUBLIC kmsob_t* _create_init_kmsob(kmsob_t* kmsp,size_t objsz,adr_t cvadrs,adr_t cvadre,msadsc_t* msa,uint_t relpnr);
PUBLIC kmsob_t* _create_kmsob(kmsobmgrhed_t* kmmgrlokp,koblst_t* koblp,size_t objsz);
PUBLIC void* kmsob_new_opkmsob(kmsob_t* kmsp,size_t msz);
PUBLIC bool_t kmsob_extn_pages(kmsob_t* kmsp);
PUBLIC void* kmsob_new_onkmsob(kmsob_t* kmsp,size_t msz);
PUBLIC void* kmsob_new_core(size_t msz);
PUBLIC void* kmsob_new(size_t msz);
PUBLIC uint_t scan_freekmsob_isok(kmsob_t* kmsp);
PUBLIC bool_t _destroy_kmsob_core(kmsobmgrhed_t* kmobmgrp,koblst_t* koblp,kmsob_t* kmsp);
PUBLIC bool_t _destroy_kmsob(kmsobmgrhed_t* kmobmgrp,koblst_t* koblp,kmsob_t* kmsp);
PUBLIC bool_t kmsob_del_opkmsob(kmsob_t* kmsp,void* fadrs,size_t fsz);
PUBLIC bool_t kmsob_delete_onkmsob(kmsob_t* kmsp,void* fadrs,size_t fsz);
PUBLIC bool_t kmsob_delete_core(void* fadrs,size_t fsz);
PUBLIC bool_t kmsob_delete(void* fadrs,size_t fsz);
PUBLIC bool_t chek_kmbext_findmsa(kmsob_t* kmsp,kmbext_t* cpbexp);
PUBLIC bool_t chek_one_kmbext(kmsob_t* kmsp,kmbext_t* cpbexp);
PUBLIC bool_t chek_onekmsob_mbext(kmsob_t* kmsp);
PUBLIC void chek_one_kmsob(kmsob_t* kmsp,size_t objsz);
PUBLIC void chek_all_kmsobstruc();
PUBLIC void kobcks_init(kobcks_t* initp,void* vadr,size_t sz);
PUBLIC void write_kobcks(kmsobmgrhed_t* kmmgrp,void* ptr,size_t sz);
PUBLIC void chek_one_kobcks(kobcks_t* kkp);
PUBLIC void chek_all_kobcks();
PUBLIC void free_one_kobcks(kobcks_t* kkp);
PUBLIC void free_all_kobcks();
PUBLIC void test_kmsob();
#endif