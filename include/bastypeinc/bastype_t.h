/**********************************************************
        基本数据类型文件bastype_t.h
***********************************************************
                彭东 ＠ 2013.06.23.10.10
**********************************************************/
#ifndef _BASTYPE_T_H
#define _BASTYPE_T_H
typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;
typedef unsigned long long u64_t;
typedef char s8_t;
typedef short s16_t;
typedef int s32_t;
typedef long long  s64_t;
typedef long sint_t;
typedef unsigned long uint_t;
typedef u32_t cpuflg_t;
typedef unsigned long adr_t;

typedef sint_t bool_t;
typedef u32_t dev_t;
typedef const char* str_t;
typedef char char_t;
typedef unsigned long drv_t;
typedef unsigned long mrv_t;
typedef sint_t drvstus_t;
typedef sint_t sysstus_t;
typedef sint_t hand_t;
typedef void* buf_t;
typedef unsigned long size_t;
typedef u32_t reg_t;


typedef void (*inthandler_t)();
typedef drv_t (*i_handle_t)(uint_t int_nr);
typedef drv_t (*f_handle_t)(uint_t int_nr,void* sframe);
typedef drvstus_t (*intflthandle_t)(uint_t ift_nr,void* device,void* sframe);
typedef u64_t mmstus_t;

#define KLINE static inline
#define PUBLIC
#define private	static
#define EXTERN extern
#define KEXTERN extern
#define NULL	0
#define TRUE    1
#define	FALSE	0
#define DFCERRSTUS (-1)
#define DFCOKSTUS (0)
#define NO_HAND (-1)
#define ALIGN(x, a)     (((x) + (a) - 1) & ~((a) - 1))

#define LKHEAD_T __attribute__((section(".head.text")))
#define LKHEAD_D __attribute__((section(".head.data")))
#define LKINIT 
#endif
