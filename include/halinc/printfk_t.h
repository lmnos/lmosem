/**********************************************************
		屏幕上格式化输出头文件printfk_t.h
***********************************************************
				彭东 ＠ 2011.12.11.14.30
**********************************************************/
#ifndef _PRINTFK_T_H
#define _PRINTFK_T_H



typedef __builtin_va_list va_list;
#define va_start(ap,np) __builtin_va_start(ap,np)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap,ty) __builtin_va_arg(ap,ty)

#endif
