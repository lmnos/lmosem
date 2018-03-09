/**********************************************************
        LMOSEM IO缓存块头文件krliocache.h
***********************************************************
                彭东 ＠ 2018.03.08.10.10
**********************************************************/
#ifndef _KRLIOCACHE_H
#define _KRLIOCACHE_H
void krliocheblkdsc_t_init(iocheblkdsc_t* initp);
void iocheblk_t_init(iocheblk_t* initp);
void init_krliocacheblk();
iocheblk_t* krlnew_iocheblk();
bool_t krldel_iocheblk(iocheblk_t* icblkp);
iocheblk_t* krliocheblk_find_iocheblk(iocheblkdsc_t* icblkdsclokp, uint_t icblknr,uint_t icblksz);
iocheblk_t* krliocheblk_alloc_core(iocheblkdsc_t* icblkdsc, uint_t icblknr,uint_t icblksz);
iocheblk_t* krliocheblk_alloc(iocheblkdsc_t* icblkdsc,uint_t icblknr,uint_t icblksz);
bool_t krliocheblk_free_core(iocheblkdsc_t* icblkdsc, uint_t icblknr,uint_t icblksz);
bool_t krliocheblk_free(iocheblkdsc_t* icblkdsc,uint_t icblknr,uint_t icblksz);
void krliocheblk_test();
#endif // _KRLIOCACHE_H