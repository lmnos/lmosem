#include "stdio.h"
uint_t strlen(char* str_s)
{
	sint_t chaidx=0;
	while(*str_s!=0)
	{
		str_s++;
		chaidx++;
	}
	return chaidx;
}

int printf(const char* fmt,...)
{
    int rets=-1;
    va_list ap; 
    va_start(ap,fmt);
	char* buf=(char*)mallocblk(0x1000);
	if(buf==NULL)
	{
        return -1;
	}
    devid_t dev;
    dev.dev_mtype=UART_DEVICE;
    dev.dev_stype=0;
    dev.dev_nr=0;
    hand_t fd=open(&dev,RW_FLG|FILE_TY_DEV,0);
    if(fd==-1)
    {   
        rets=-1;
        goto res_step;
    }
	vsprintf(buf,fmt,ap);
	if(write(fd,buf,strlen(buf),0)==SYSSTUSERR)
	{
        rets=-1;
        goto res_step;   
	}
	close(fd);
	
	rets=0;
res_step:
    
    	
	if(mfreeblk(buf,0x1000)==SYSSTUSERR)
	{
        rets=-1;
	}
	
    va_end(ap);
	return rets;
}

char* strcopy(char* buf,char* str_s)
{
	while(*str_s)
	{
		*buf=*str_s;
		buf++;
		str_s++;
	}
	return buf;
}

void vsprintf(char* buf,const char* fmt,va_list args)
{
	char* p =buf;
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
				p=number(p,va_arg(next_arg,uint_t),16);
				fmt++;

				break;
			case 'd':
				p=number(p,va_arg(next_arg,uint_t),10);

				fmt++;
				break;
		        case 's':
			       p=strcopy(p,(char*)va_arg(next_arg,uint_t));

			       fmt++;
			       break;
			default:
				break;
		}
	}
	*p=0;
	return;
}

char* number(char* str,uint_t n, sint_t base)
{
	register char *p;
	char strbuf[36];
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