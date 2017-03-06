/**********************************************************
		数据类型文件type.h
***********************************************************
				彭东 ＠ 2010.10.31.09.32
**********************************************************/
#ifndef _TYPE_H
#define _TYPE_H


typedef unsigned char u8_t; //__attribute__((__mode__(__QI__))) u8_t;

typedef unsigned short u16_t; //__attribute__((__mode__(__HI__))) u16_t;

typedef unsigned int u32_t;//__attribute__((__mode__(__SI__))) u32_t;

typedef unsigned long long u64_t; //__attribute__((__mode__(__DI__))) u64_t;

typedef char s8_t; //__attribute__((__mode__(__QI__))) u8_t;

typedef short s16_t; //__attribute__((__mode__(__HI__))) u16_t;

typedef int s32_t;//__attribute__((__mode__(__SI__))) u32_t;

typedef long long s64_t;

typedef long sint_t;
typedef unsigned long uint_t;


typedef u64_t cpuflg_t;

typedef unsigned long adr_t;
typedef unsigned long size_t;

typedef u64_t bool_t;
typedef u64_t dev_t;
typedef const char* str_t;
typedef char char_t;
typedef unsigned long drv_t; 
typedef unsigned long mrv_t;
typedef sint_t drvstus_t;
#define KLINE static inline

typedef void (*inthandler_t)();
typedef drv_t (*i_handle_t)(uint_t int_nr);
typedef drv_t (*f_handle_t)(uint_t int_nr,void* sframe);
typedef void (*syscall_t)();
typedef drv_t (*dev_op_t)();
typedef mrv_t (*msg_op_t)();
typedef void* exception_t;
typedef char_t* va_list_t;



#define PUBLIC
#define private	static
#define EXTERN extern
#define KEXTERN extern
#define NULL	0
#define TRUE    1
#define	FALSE	0
#define REGCALL __attribute__((regparm(3)))
#define ALIGN(x, a)     (((x) + (a) - 1) & ~((a) - 1))


#define P4K_ALIGN(x) ALIGN(x,0x1000)
#endif
//20
