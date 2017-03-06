/**********************************************************
		屏幕上格式化输出头文件printf.h
***********************************************************
				彭东 ＠ 2011.12.11.14.30
**********************************************************/
#ifndef _PRINTFK_H
#define _PRINTFK_H
void printfk(const char* fmt,...);
void kprint(const char* fmt,...);
char_t* strcopyk(char_t* buf,char_t* str_s);
void vsprintfk(char* buf,const char* fmt,va_list args);
char_t* numberk(char_t* str,uint_t n, sint_t base);
void char_write_uart(char_t* buf);
#endif
