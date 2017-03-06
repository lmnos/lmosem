/**********************************************************
		屏幕上格式化输出文件printf.c
***********************************************************
				彭东 ＠ 2011.12.11.14.30
**********************************************************/

#include "lmosemtypes.h"
#include "lmosemmctrl.h"
void printfk(const char_t* fmt,...)
{
	char_t buf[512];
    //cpuflg_t cpuflg;
    va_list ap; 
    va_start(ap,fmt);
    //hal_disableirq_savecpuflg(&cpuflg);

	vsprintfk(buf,fmt,ap);
    //hal_uart_write(0,buf,0);	
    //hal_enableirq_restcpuflg(&cpuflg);
    gstr_write(&kdftgh,buf);
    va_end(ap);
	return;
}

void kprint(const char_t* fmt,...)
{
	char_t buf[512];
    //cpuflg_t cpuflg;
    va_list ap; 
    va_start(ap,fmt);
    //hal_disableirq_savecpuflg(&cpuflg);

	vsprintfk(buf,fmt,ap);
    //hal_uart_write(0,buf,0);	
    //hal_enableirq_restcpuflg(&cpuflg);
    gstr_write(&kdftgh,buf);
    va_end(ap);
	return;
}

char_t* strcopyk(char_t* buf,char_t* str_s)
{
	while(*str_s)
	{
		*buf=*str_s;
		buf++;
		str_s++;
	}
	return buf;
}

void vsprintfk(char_t* buf,const char_t* fmt,va_list args)
{
	char_t* p =buf;
	va_list next_arg=args;
	while(*fmt)
	{
		if(*fmt != '%')
		{
			*p++ = *fmt++;
			continue;
		}
		fmt++;
		switch(*fmt)
		{
			case 'x':
				p=numberk(p,va_arg(next_arg,uint_t),16);
				fmt++;

				break;
			case 'd':
				p=numberk(p,va_arg(next_arg,uint_t),10);
				fmt++;
				break;
		        case 's':
			       p=strcopyk(p,(char_t*)va_arg(next_arg,uint_t));
			       fmt++;
			       break;
			default:
				break;
		}
	}
	*p=0;
	return;
}

char_t* numberk(char_t* str,uint_t n, sint_t base)
{
	register char_t *p;
	char_t strbuf[36];
    p = &strbuf[36];
    *--p = 0;  
	if(n == 0)
    {
           *--p = '0';
    }
    else
    {
         do
         {
               *--p = "0123456789abcdef"[n % base]; 
         }while( n /= base);
    }
    while(*p!=0)
    {
		*str++=*p++;
	}
    return str;
}

/*void char_write_uart(char_t* buf)
{
  
    char_t*p=buf;
    while(*p)
    {

          hal_uart0_putc(*p);
          p++;
    }
    return;
}*/