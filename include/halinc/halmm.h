/****************************************************************
        LMOSEM HAL内存初始化头文件halmm.h
*****************************************************************
                彭东 ＠ 2013.07.06.15.50
****************************************************************/
#ifndef _HALMM_H
#define _HALMM_H
#ifdef CFG_S3C2440A_PLATFORM

void init_halmm();
sint_t cheksum_phyadrspce(mach_t* mahp);
void init_mmapdsc(mach_t* mahp);
uint_t init_core_mmapdsc(adr_t adrs,adr_t adre,mmapdsc_t* gmmp,uint_t curmindx);
void mmapdsc_t_init(mmapdsc_t* mmp,adr_t phyadr,adr_t phyadre,u32_t allcount,u32_t flgs);
void alcfrelst_t_init(alcfrelst_t* initp,size_t bsz);
void phymem_t_init(phymem_t* initp);
void onmmapdsc_inkrlram(mach_t* mahp,phymem_t* pmp);
void init_phymem();
void pmmlist_init(mach_t* mahp,phymem_t* pmp);
void mapdsc_addto_memlst(alcfrelst_t* aflp,mmapdsc_t* mapp,uint_t atflg);
alcfrelst_t* hal_onblksz_findalcfrelst(alcfrelst_t** retalcfrl,size_t* retalcsz,size_t blksz);
mmapdsc_t* hal_onalfl_findmapdsc(alcfrelst_t* allclh);
adr_t hal_onmapdsc_allcblks(u32_t mflg, u32_t mask,u32_t bitls,alcfrelst_t* aflp,alcfrelst_t* mvtoaflp);
adr_t hal_onalcfrel_allocblks(alcfrelst_t* allclh,alcfrelst_t* relaclh,size_t relalcsz);
adr_t hal_memallocblks_core(size_t blksz);
adr_t hal_memallocblks(size_t blksz);
mmapdsc_t* hal_free_findmapdsc(adr_t frebadr,alcfrelst_t* allclh);
bool_t hal_onmapdsc_freeblks(adr_t frebadr,u32_t mflg, u32_t mask,alcfrelst_t* aflp,alcfrelst_t* mvtoaflp);
bool_t hal_onalcfrel_freeblks(adr_t frebadr,alcfrelst_t* allclh,alcfrelst_t* mvaflh,size_t relalcsz);
bool_t hal_memfreeblks_core(adr_t frebadr,size_t blksz);
bool_t hal_memfreeblks(adr_t frebadr,size_t blksz);
void test_halmm();
#endif
#endif // _HALINIT_H
