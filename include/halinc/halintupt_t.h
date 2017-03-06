/**********************************************************
        hal层中断处理头文件halintupt_t.h
***********************************************************
                彭东 ＠ 2013.07.15.16.10
**********************************************************/
#ifndef _HALINTUPT_T_H
#define _HALINTUPT_T_H

#ifdef CFG_S3C2440A_PLATFORM

#define IFLG_PRESENT (1<<0)
#define IFLG_INTINTP (1<<1)
#define IFLG_EXTINTP (1<<2)
#define IFLG_SUBINTP (1<<3)
#define IFLG_CLXINTP (1<<4)

#define CLXSUBINR(clxn,subn) (((clxn)<<16)|(subn))
#define INTPDEVID(mdn,sdn) (((mdn)<<16)|(sdn))

#define ONEHANDLE_FLG 0
#define MULHANDLE_FLG 1
#define INTSRC_FLG 1
#define SUBINTSRC_FLG 2

#define INTLINE_MAX 60
#define SUBINTLINE_MAX 14

#define INTMSK_R 0x4a000008
#define INTSUBMSK_R 0x4a00001c 
#define EINTMASK_R 0x560000a4
#define EINTPEND_R 0x560000a8 
#define LCDINTPND_R 0x4d000054



#define INTOFFSET_R 0x4a000014
#define INTPND_R 0x4a000010
#define SRCPND_R 0x4a000000
#define INTMOD_R 0x4a000004
#define SUBSRCPND_R 0x4a000018

#define SUBSRCPND_BITS_MASK 0x7fff
#define EINTPEND_BITS_MASK 0xffffff
#define LCDSRCPND_BITS_MASK 0x3

#define EINTPEND_R_BIT_S 4
#define EINTPEND_R_BIT_E 24
 
#define SUBSRCPND_R_BIT_S 0
#define SUBSRCPND_R_BIT_E 15

#define MINT_OFFSET 0
#define SINT_OFFSET 32
#define EINT_OFFSET 47
#define IRQ_MAX 71

#define MINTNR_START (0+MINT_OFFSET)
#define MINTNR_END (31+MINT_OFFSET)

#define SINTNR_START (0+SINT_OFFSET)
#define SINTNR_END (14+SINT_OFFSET)

#define EINTNR_START (0+EINT_OFFSET)
#define EINTNR_END (23+EINT_OFFSET)

#define MINT_FLG 1
#define SINT_FLG 2
#define EINT_FLG 3


#define MINT_IFDNR(x) (x+MINT_OFFSET)
#define SINT_IFDNR(x) (x+SINT_OFFSET)
#define EINT_IFDNR(x) (x+EINT_OFFSET)

#define EINT4_7 4
#define EINT8_23 5
#define INT_CAM 6
#define INT_WDT_AC97 9
#define INT_UART2 15
#define INT_LCD 16
#define INT_UART1 23
#define INT_UART0 28
#define INT_ADC 31

#define EI4_7_PNDBTS 4
#define EI4_7_PNDBTE 8

#define EI8_23_PNDBTS 8
#define EI8_23_PNDBTE 24

#define IUART0_PNDBTS 0
#define IUART0_PNDBTE 3

#define IUART1_PNDBTS 3
#define IUART1_PNDBTE 6

#define IUART2_PNDBTS 6
#define IUART2_PNDBTE 9

#define IADC_PNDBTS 9
#define IADC_PNDBTE 11

#define ICAM_PNDBTS 11
#define ICAM_PNDBTE 13

#define IACWDT_PNDBTS 13
#define IACWDT_PNDBTE 15

#define ILCD_PNDBTS 0
#define ILCD_PNDBTE 2


typedef struct s_ILNEDSC
{
    u32_t ild_modflg;
    u32_t ild_devid;
    u32_t ild_physid;
    u32_t ild_clxsubinr;
}ilnedsc_t;




typedef struct s_INTFLTDSC
{
    spinlock_t  i_lock;
    list_h_t    i_serlist;
    uint_t      i_sernr;
    u32_t       i_flg;
    u32_t       i_stus;
    u32_t       i_pndbitnr;
    uint_t      i_irqnr;
    uint_t      i_deep;
    uint_t      i_indx;
}intfltdsc_t;



typedef struct s_INTSERDSC
{
    list_h_t    s_list;
    list_h_t    s_indevlst;
    u32_t       s_flg;
    intfltdsc_t* s_intfltp;
    void*       s_device;
    uint_t      s_indx;
    intflthandle_t s_handle;
}intserdsc_t;
#endif 

#ifdef CFG_X86_PLATFORM

typedef struct s_ILNEDSC
{
    u32_t ild_modflg;
    u32_t ild_devid;
    u32_t ild_physid;
    u32_t ild_clxsubinr;
}ilnedsc_t;





typedef struct s_INTFLTDSC
{
    spinlock_t  i_lock;
    u32_t       i_flg;
    u32_t       i_stus;
    uint_t      i_prity;        //中断优先级
    uint_t      i_irqnr;        //中断号
    uint_t      i_deep;         //中断嵌套深度
    u64_t       i_indx;         //中断计数
    list_h_t    i_serlist;
    uint_t      i_sernr;
    list_h_t    i_serthrdlst;   //中断线程链表头
    uint_t      i_serthrdnr;    //中断线程个数
    void*       i_onethread;    //只有一个中断线程时直接用指针
    void*       i_rbtreeroot;   //如果中断线程太多则按优先级组成红黑树
    list_h_t    i_serfisrlst;   //也可以使用中断回调函数的方式
    uint_t      i_serfisrnr;    //中断回调函数个数
    void*       i_msgmpool;     //可能的中断消息池
    void*       i_privp;
    void*       i_extp;
}intfltdsc_t;

typedef struct s_INTSERDSC
{
    list_h_t    s_list;
    list_h_t    s_indevlst;
    u32_t       s_flg;
    intfltdsc_t* s_intfltp;
    void*       s_device;
    uint_t      s_indx;
    intflthandle_t s_handle;
}intserdsc_t;

typedef struct s_KITHREAD
{
    spinlock_t  kit_lock;
    list_h_t    kit_list; 
    u32_t       kit_flg;
    u32_t       kit_stus;
    uint_t      kit_prity;
    u64_t       kit_scdidx;
    uint_t      kit_runmode;
    uint_t      kit_cpuid;
    u16_t       kit_cs;
    u16_t       kit_ss;
    uint_t      kit_nxteip;
    uint_t      kit_nxtesp;
    void*       kit_stk;
    size_t      kit_stksz;
    void*       kit_runadr;
    void*       kit_binmodadr;
    void*       kit_mmdsc;
    void*       kit_privp;
    void*       kit_extp;
}kithread_t;

#endif


#endif // HALINTUPT_T_H
