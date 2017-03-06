/****************************************************************
        LMOSEM HAL内存初始化头文件halmm_t.h
*****************************************************************
                彭东 ＠ 2013.07.06.15.50
****************************************************************/
#ifndef _HALMM_T_H
#define _HALMM_T_H

#define DEV_TYPE_NOT 0xffffffff
#define ADRSPCE_NOT 0
#define ADRSPCE_IO 1
#define ADRSPCE_SDRAM 2
#define ADRSPCE_RAM 3
#define ADRSPCE_ROM 4
#define ADRSPCE_NORFLASH 5
#define ADRSPCE_NANDFLASH 6

#define MAPF_SZ_BIT 0
#define MAPF_ACSZ_BIT 4
#define MAPF_SZ_16KB (1<<MAPF_SZ_BIT)
#define MAPF_SZ_32KB (2<<MAPF_SZ_BIT)
#define MAPF_SZ_4MB (8<<MAPF_SZ_BIT)



#define MAPF_ACSZ_128KB (1<<MAPF_ACSZ_BIT)
#define MAPF_ACSZ_256KB (2<<MAPF_ACSZ_BIT)
#define MAPF_ACSZ_512KB (3<<MAPF_ACSZ_BIT)
#define MAPF_ACSZ_1MB (4<<MAPF_ACSZ_BIT)
#define MAPF_ACSZ_2MB (5<<MAPF_ACSZ_BIT)
#define MAPF_ACSZ_4MB (6<<MAPF_ACSZ_BIT)

#define MAPONE_SIZE (0x400000)
#define MAP_FLAGES_VAL(RV,SALLOCSZ,MSZ) (RV|SALLOCSZ|MSZ)

#define ADDT_EMTP_FLG 1
#define ADDT_FUEM_FLG 2
#define ADDT_FULL_FLG 3

#define BLK128KB_SIZE (0x20000)
#define BLK256KB_SIZE (0x40000)
#define BLK512KB_SIZE (0x80000)
#define BLK1MB_SIZE (0x100000)
#define BLK2MB_SIZE (0x200000)
#define BLK4MB_SIZE (0x400000)

#define BLK128KB_BITL (32)
#define BLK256KB_BITL (16)
#define BLK512KB_BITL (8)
#define BLK1MB_BITL (4)
#define BLK2MB_BITL (2)
#define BLK4MB_BITL (1)

#define BLK128KB_MASK (0xffffffff)
#define BLK256KB_MASK (0xffff)
#define BLK512KB_MASK (0xff)
#define BLK1MB_MASK (0xf)
#define BLK2MB_MASK (0x3)
#define BLK4MB_MASK (0x1)

#define BLKSZ_HEAD_MAX 6

#define ETYBAK_ADR 0x2000
#define PM32_EIP_OFF (ETYBAK_ADR)
#define PM32_ESP_OFF (ETYBAK_ADR+4)
#define RM16_EIP_OFF (ETYBAK_ADR+8)
#define RM16_ESP_OFF (ETYBAK_ADR+12)

#define RWHDPACK_ADR (ETYBAK_ADR+32)
#define E80MAP_NR (ETYBAK_ADR+64)
#define E80MAP_ADRADR (ETYBAK_ADR+68)
#define E80MAP_ADR (0x5000)

#define E820MAPBASS E80MAP_ADR
#define E820MAPNUMBASS E80MAP_NR

#define VGAADRS 0xa0000ULL
#define VGAADRD 0xc0000ULL

/*Type 1: Usable (normal) RAM
Type 2: Reserved - unusable
Type 3: ACPI reclaimable memory
Type 4: ACPI NVS memory
Type 5: Area containing bad memory
*/
#define RAM_USABLE 1
#define RAM_RESERV 2
#define RAM_ACPIREC 3
#define RAM_ACPINVS 4
#define RAM_AREACON 5

#define PMR_T_OSAPUSERRAM 1
#define PMR_T_RESERVRAM 2
#define PMR_T_HWUSERRAM 8
#define PMR_T_ARACONRAM 0xf
#define PMR_T_BUGRAM 0xff
#define PMR_F_X86_32 (1<<0)
#define PMR_F_X86_64 (1<<1)
#define PMR_F_ARM_32 (1<<2)
#define PMR_F_ARM_64 (1<<3)
#define PMR_F_HAL_MASK 0xff


typedef struct s_PHYMMARGE
{
    spinlock_t pmr_lock;
    u32_t pmr_type;
    u32_t pmr_stype;
    u32_t pmr_dtype;
    u32_t pmr_flgs;
    u32_t pmr_stus;
    u64_t pmr_saddr;
    u64_t pmr_lsize;
    u64_t pmr_end;
    u64_t pmr_rrvmsaddr;
    u64_t pmr_rrvmend;
    void* pmr_prip;
    void* pmr_extp;
}phymmarge_t;


typedef struct s_PHYADRSPCE
{
    u32_t ap_flgs;
    u32_t ap_devtype;
    adr_t ap_adrstart;
    adr_t ap_adrend;
}phyadrspce_t;

typedef struct s_MMAPDSC
{
    list_h_t map_list;
    spinlock_t map_lock;
    adr_t     map_phyadr;
    adr_t     map_phyadrend;
    u32_t     map_allcount;
    u32_t     map_flg;
    /*它管理4MB大小的内存块，在实际分配时，它所描述的4MB
     *可以被分割成128KB，256KB，512KB，1MB，2MB，4MB，只能
     *分成同一大小的等份，不支持内存共享了，嵌入式os不需要*/
}mmapdsc_t;
typedef struct s_ALCFRELST
{
    spinlock_t afl_lock;
    size_t     afl_sz;
    list_h_t   afl_fulllsth;
    list_h_t   afl_emtplsth;
    list_h_t   afl_fuemlsth;
    /*用于挂载同一种大小的mmapdsc队列，比如分割成128KB大小的
     *并对其分类，分配完的、分配一部分的、未分配的。*/
}alcfrelst_t;
typedef struct s_PHYMEM
{
    list_h_t pmm_list;
    spinlock_t pmm_lock;
    uint_t freeblks;
    uint_t allcblks;
    alcfrelst_t pmm_sz_lsth[BLKSZ_HEAD_MAX];
    /*alcfrelst数组，形成了128KB到4MB大小队列数组 [0]128KB 
     *[1]256KB [2]512KB [3]1MB [4]2MB [5]4MB*/
}phymem_t;

   
#endif // HALINIT_H
