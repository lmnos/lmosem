/**********************************************************
        内核层内存对象池管理头文件krlobjsmpol.h
***********************************************************
                彭东 ＠ 2013.07.18.15.00
**********************************************************/
#ifndef _KRLOBJSMPOL_H
#define _KRLOBJSMPOL_H
void init_krlobjsmpol();
void objmgrhead_t_init(objmgrhead_t* initp,objalst_t* alstp,size_t objsz,adr_t start,adr_t end);
void objalst_t_init(objalst_t* initp,olcfgdat_t* ocfgp);
void objmplctrl_t_init(objmplctrl_t* initp);
void test_objmpool();
void objs_align(objmgrhead_t* omghp,uint_t ali);
objmgrhead_t* retn_freeobjmgrh_onobjalst(objalst_t* alstp,adr_t fradr,size_t frsz);
objmgrhead_t* retn_alocobjmgrh_onobjalst(objalst_t* alstp);
objmgrhead_t* krlnew_objmpoolandinit(objalst_t* alstp, size_t msize);
objalst_t* retn_objalst_onmsize(objmplctrl_t* omctlp,size_t msz);
bool_t free_objsz_onobjmgrhead(objmgrhead_t* omghp,adr_t fradr,size_t frsz);
bool_t krlfre_objmpoolanddele(objalst_t* alstp,objmgrhead_t* omghp,size_t frsz);
bool_t krlobjmplfree_core_onobjalst(objalst_t *alstp,adr_t fradr, size_t frsz);
bool_t krlobjsmpol_free_core(adr_t fradr, size_t frsz);
bool_t krlobjsmpol_free(adr_t fradr,size_t frsz);
adr_t krlobjsmpol_alloc(size_t msize);
adr_t aloc_objsz_onobjmgrhead(objmgrhead_t* omghp);
adr_t krlobjmplalc_core_onobjalst(objalst_t* alstp, size_t msize);
adr_t krlobjsmpol_alloc_core(size_t msize);
#endif // KRLOBJSMPOL_H
