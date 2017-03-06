#ifndef _BSTARTPARM_H
#define _BSTARTPARM_H
//#define CPUOEMSTR_MAX 128

//klfocpymblk_t* klfocymblkp;
//u64_t   mb_klfocymbnr;
//char_t   mb_cpuoem[CPUOEMSTR_MAX];


void init_bstartparm();
void machbstart_t_init(machbstart_t* initp);
int adrzone_is_ok(u64_t sadr,u64_t slen,u64_t kadr,u64_t klen);
int chkadr_is_ok(machbstart_t* mbsp,u64_t chkadr,u64_t cksz);
#endif // BSTARTPARM_H
