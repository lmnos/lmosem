/**********************************************************
		内存页面头文件pages64_t.h
***********************************************************
				彭东 ＠ 2013.03.01.15.00
**********************************************************/
#ifndef _PAGES64_T_H
#define _PAGES64_T_H

#define KPML4_P (1<<0)
#define KPML4_RW (1<<1)
#define KPML4_US (1<<2)
#define KPML4_PWT (1<<3)
#define KPML4_PCD (1<<4)
#define KPML4_A (1<<5)

#define KPDPTE_P (1<<0)
#define KPDPTE_RW (1<<1)
#define KPDPTE_US (1<<2)
#define KPDPTE_PWT (1<<3)
#define KPDPTE_PCD (1<<4)
#define KPDPTE_A (1<<5)

#define KPDE_P (1<<0)
#define KPDE_RW (1<<1)
#define KPDE_US (1<<2)
#define KPDE_PWT (1<<3)
#define KPDE_PCD (1<<4)
#define KPDE_A (1<<5)
#define KPDE_D (1<<6)
#define KPDE_PS (1<<7)
#define KPDE_G (1<<8)
#define KPDE_PAT (1<<12)

#define KPML4_SHIFT 39
#define KPDPTTE_SHIFT 30
#define KPDP_SHIFT 21
#define PGENTY_SIZE 512

#define PAGEMAPBASS 0x100000
#define PSHRSIZE 12
#define PDENSHL  22
#define PTENSHL  12
#define PDTNSHR  10
#define PTENSHR  10
#define PDTNSIZE (1UL<<PDTNSHR)
#define PTENSIZE (1UL<<PTENSHR)
#define PAGESIZE (1UL<<PSHRSIZE)
#define PRMSIZEO (1UL<<PDENSHL)
#define PDTN_MASK	(~(PDTNSIZE-1))
#define PTEN_MASK	(~(PTENSIZE-1))
#define PAGE_MASK       (~(PAGESIZE-1))
#define PAGE_ALIGN(n) ALIGN(n,PAGESIZE)// (((n)+0xfff)&0xfffff000)// PAGE_ALIGN(x)((PAGESIZE-(x&(~(PAGE_MASK))))+x)
#define PTPNFUN(phyadr) (phyadr>>PSHRSIZE)
#define PNTPFUN(PN) (PN<<PSHRSIZE)
#define PDENFN(phyadr) ((phyadr>>PDENSHL))
#define PTENFN(phyadr) ((phyadr>>PTENSHL)&(~PTEN_MASK))
#define PDESIZE 1024


typedef struct s_KPML4
{
	u64_t p_val;
}__attribute__((packed)) kpml4_t;


typedef struct s_KPDPTE
{
	u64_t p_val;
}__attribute__((packed)) kpdpte_t;


typedef struct s_KPDE
{
	u64_t p_val;
}__attribute__((packed)) kpde_t;
#endif
