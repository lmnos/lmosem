/**********************************************************
		系统全局内存检查文件头chkcpmm_t.h
***********************************************************
				彭东 ＠ 2012.10.22.09.00
**********************************************************/
#ifndef _CHKCPMM_T_H
#define _CHKCPMM_T_H
#define EMAP_PTR E80MAP_ADR
#define EMAP_NR_PTR E80MAP_NR

#define BASE_MEM_SZ 0x3f80000

/*Type 1: Usable (normal) RAM
Type 2: Reserved - unusable
Type 3: ACPI reclaimable memory
Type 4: ACPI NVS memory
Type 5: Area containing bad memory

#define RAM_USABLE 1
#define RAM_RESERV 2
#define RAM_ACPIREC 3
#define RAM_ACPINVS 4
#define RAM_AREACON 5 
*/
#define PML4T_BADR 0x20000
#define PDPTE_BADR 0x21000
//#define PDPTE1_BADR 0x18000
//#define PTE1_BADR 0x17000
//#define PDE1_BADR 0x19000
//#define PDE2_BADR 0x16000
#define PDE_BADR 0x22000
#define PTE_BADR 0x23000

#define PG_SIZE 512

//			页面目录表及各种属性状态
/*___________________________________________________________
  |______________________|_|_|_|_|_|_|_|_|_|_|_|_|		   pagedirectorytble
			      | | | | | | | | | | | |		   BIT 	
			      | | | | | | | | | | | |_____________Bit0 P　0不存在/1存在
			      | | | | | | | | | | |_______________Bit1 R/W　0只读/1可读可写 
			      | | | | | | | | | |_________________Bit2 U/S　0管理特权/1用户特权 
			      | | | | | | | | |___________________Bit3 PWT　0回写/1直写  （页表）
			      | | | | | | | |_____________________Bit4 PCD　0高速缓存/1禁止高速缓存（页表）
			      | | | | | | |_______________________Bit5 A　0cpu未访问/1cpu访问置1但不清0 
			      | | | | | |_________________________Bit6 D　页目录中保留为０
			      | | | | |___________________________Bit7 PS　0页大小4KB/1页大小为４MB
			      | | | |_____________________________Bit8 G 全局页为1时tlb中的页目录不失效忽略
			      | | |_______________________________Bit9-----\
			      | |_________________________________Bit10     |可供系统软件自由使用
			      |___________________________________Bit11----/
*/
//			页表及各种属性状态
/*___________________________________________________________
  |______________________|_|_|_|_|_|_|_|_|_|_|_|_|		   pagetable
			      | | | | | | | | | | | |		   BIT 	
			      | | | | | | | | | | | |_____________Bit0 P　0不存在/1存在（页）
			      | | | | | | | | | | |_______________Bit1 R/W　0只读/1可读可写 （页）
			      | | | | | | | | | |_________________Bit2 U/S　0管理特权/1用户特权（页） 
			      | | | | | | | | |___________________Bit3 PWT　0回写/1直写  （页）
			      | | | | | | | |_____________________Bit4 PCD　0高速缓存/1禁止高速缓存（页）
			      | | | | | | |_______________________Bit5 A　0cpu未访问/1cpu访问置1但不清0 （页）
			      | | | | | |_________________________Bit6 D　页表中脏位cpu写入时会自动置位（页）
			      | | | | |___________________________Bit7 PTA　0　（页）页属性　奔腾3开始支持
			      | | | |_____________________________Bit8 G 全局页为1时tlb中的页不失效忽略（页）
			      | | |_______________________________Bit9-----\
			      | |_________________________________Bit10     |可供系统软件自由使用
			      |___________________________________Bit11----/
*/



#define PDT_S_PNT	0x1 
#define PDT_S_RW	0x2
#define PDT_S_US	0x4
#define PDT_S_PWT	0x8
#define PDT_S_PCD	0x10
#define PDT_S_ACC	0x20
#define PDT_S_DITYRE	0x40
#define PDT_S_SIZE	0x80
#define PDT_S_GLOP	0x100

#define PT_S_PNT	0x1 
#define PT_S_RW		0x2
#define PT_S_US		0x4
#define PT_S_PWT	0x8
#define PT_S_PCD	0x10
#define PT_S_ACC	0x20
#define PT_S_DITY	0x40
#define PT_S_PTARE	0x80
#define PT_S_GLOP	0x100

typedef unsigned long long pt64_t;

/*typedef struct s_e820{
    u64_t saddr;    //start of memory segment8
    u64_t lsize;    //size of memory segment8
    u32_t type;     //type of memory segment 4
}__attribute__((packed)) e820map_t;
*/
#endif 
