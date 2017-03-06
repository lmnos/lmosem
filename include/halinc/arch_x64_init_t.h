/**********************************************************
        体系结构初始化文件arch_x64_init.h
***********************************************************
                彭东 ＠ 2011.12.16.08.30
**********************************************************/
#ifndef _ARCH_X64_INIT_T_H
#define _ARCH_X64_INIT_T_H

extern u64_t kernel_pml4;



#define MBS_MIGC (u64_t)((((u64_t)'L')<<56)|(((u64_t)'M')<<48)|(((u64_t)'O')<<40)|(((u64_t)'S')<<32)|(((u64_t)'M')<<24)|(((u64_t)'B')<<16)|(((u64_t)'S')<<8)|((u64_t)'P'))

typedef struct s_MRSDP
{
    u64_t rp_sign;
    u8_t rp_chksum;
    u8_t rp_oemid[6];
    u8_t rp_revn;
    u32_t rp_rsdtphyadr;
    u32_t rp_len;
    u64_t rp_xsdtphyadr;
    u8_t rp_echksum;
    u8_t rp_resv[3];
}__attribute__((packed)) mrsdp_t;

typedef struct s_MACHBSTART
{
    u64_t   mb_migc;          //LMOSMBSP//0
    u64_t   mb_chksum;//8
    u64_t   mb_krlinitstack;//16
    u64_t   mb_krlitstacksz;//24
    u64_t   mb_lmosimgpadr;
    u64_t   mb_lmosimgsz;
    u64_t   mb_krlimgpadr;
    u64_t   mb_krlsz;
    u64_t   mb_krlvec;
    u64_t   mb_krlrunmode;
    u64_t   mb_kalldendpadr;
    u64_t   mb_ksepadrs;
    u64_t   mb_ksepadre;
    u64_t   mb_kservadrs;
    u64_t   mb_kservadre;
    u64_t   mb_nextwtpadr;
    u64_t   mb_bfontpadr;
    u64_t   mb_bfontsz;
    u64_t   mb_fvrmphyadr;
    u64_t   mb_fvrmsz;
    u64_t   mb_cpumode;
    u64_t   mb_memsz;
    u64_t   mb_e820padr;
    u64_t   mb_e820nr;
    u64_t   mb_e820sz;
    u64_t   mb_e820expadr;
    u64_t   mb_e820exnr;
    u64_t   mb_e820exsz;
    u64_t   mb_memznpadr;
    u64_t   mb_memznnr;
    u64_t   mb_memznsz;
    u64_t   mb_memznchksum;
    u64_t   mb_memmappadr;
    u64_t   mb_memmapnr;
    u64_t   mb_memmapsz;
    u64_t   mb_memmapchksum;
    u64_t   mb_pml4padr;
    u64_t   mb_subpageslen;
    u64_t   mb_kpmapphymemsz;
    u64_t   mb_ebdaphyadr;
    mrsdp_t mb_mrsdp;
    graph_t mb_ghparm;
}__attribute__((packed)) machbstart_t;


#define MBSPADR ((machbstart_t*)(0x100000))



#endif
