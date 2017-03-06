/**********************************************************
        LMOS内核映像文件系统头文件lmosimgfs.h
***********************************************************
                彭东 ＠ 2014.10.31.12.30
**********************************************************/
#ifndef _LMOSIMGFS_H
#define _LMOSIMGFS_H
int strcmpl(const char *a,const char *b);
fhdsc_t* get_fileinfo(char_t* fname,machbstart_t* mbsp);
void get_file_rvadrandsz(char_t *fname, machbstart_t* mbsp,u64_t* retadr,u64_t* retsz);
//e820map_t* get_maxmappadr_e820map(machbstart_t* mbsp,u64_t mappadr);
void move_lmosimg2maxpadr(machbstart_t* mbsp);
int adrzone_is_ok(u64_t sadr,u64_t slen,u64_t kadr,u64_t klen);
int initchkadr_is_ok(machbstart_t* mbsp,u64_t chkadr,u64_t cksz);
//e820map_t* chk_memsize(e820map_t* e8p,u64_t enr,u64_t sadr,u64_t size);
#endif
