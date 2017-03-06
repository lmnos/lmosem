/**********************************************************
		转换显示字符串文件vgastr.c
***********************************************************
				彭东 ＠ 2011.12.15.07.30
**********************************************************/

#include "cmctl.h"
__attribute__((section(".data"))) cursor_t curs;

PUBLIC void init_curs()
{
    //knl_spinlock_init(&curs.c_lock);
    //knl_spinlock_init(&curs.p_lock);
	curs.vmem_s=VGASTR_RAM_BASE;
	curs.vmem_e=VGASTR_RAM_END;
	curs.cvmemadr=0;
	curs.x=0;
	curs.y=0;
	return;
}

PUBLIC void GxH_strwrite(char_t* str,cursor_t* cursptr)
{

	//u32_t flags;
	uint_t straddr =cursptr->x+cursptr->y*80*2;
	char_t* p_strdst=(char_t*)(cursptr->vmem_s+straddr);
	u32_t tfindx=FALSE;
	//u32_t sidx=0;
	while(*str)
	{
		
		if(*str==10)
		{
			tfindx=TRUE;
			str++;
			if(*str==0)
			{
				break;
			}
		}
		
		current_curs(cursptr,VGACHAR_DF_CFLG);
		
		*p_strdst=*str++;
		p_strdst+=2;
	}
		
	if(tfindx==TRUE)
	{
		current_curs(cursptr,VGACHAR_LR_CFLG);
	}

	return;
}


PUBLIC char_t* numberk(char_t* str,uint_t n, sint_t base)
{
	register char_t *p;
	char_t strbuf[36];
        p = &strbuf[36];
        *--p = 0;
      
	if (n == 0)
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

PUBLIC void set_curs(u32_t x, u32_t y)
{
	curs.x=x;
	curs.y=y;
	return;
}

PUBLIC void clear_screen(u16_t srrv)
{
	curs.x=0;
	curs.y=0;
	
	u16_t* p=(u16_t*)VGASTR_RAM_BASE;
	
	for(uint_t i=0;i<2001;i++)
	{
		p[i]=srrv;
	}
	
	/*__asm__ __volatile__(
		"cld\n\t"
		"rep\n\t"
		"stosw"
		::"a" (srrv),"D" (VGASTR_RAM_BASE),"c" (2001)
		:"memory");*/
		
	close_curs();
	return;
}

PUBLIC void put_one_char(char_t cr,uint_t x,uint_t y)
{
	
	char_t* p_strdst=(char_t*)(VGASTR_RAM_BASE+(x+(y*80*2)));
	*p_strdst=cr;
	return;
}

PUBLIC void close_curs()
{
	out_u8(VGACTRL_REG_ADR,VGACURS_REG_INX);
	out_u8(VGACTRL_REG_DAT,VGACURS_CLOSE);
	return;
}



PUBLIC char_t* strcopy(char_t* buf,char_t* str_s)
{
    while(*str_s)
    {
        *buf=*str_s;
        buf++;
        str_s++;
    }
    return buf;
}

PUBLIC void vsprintfk(char_t* buf,const char_t* fmt,va_list_t args)
{
    char_t* p =buf;
    va_list_t next_arg=args;
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
                p=numberk(p,*((long*)next_arg),16);
                next_arg+=sizeof(long);
                fmt++;

                break;
            case 'd':
                p=numberk(p,*((long*)next_arg),10);
                next_arg+=sizeof(long);
                fmt++;
                break;
                case 's':
                   p=strcopy(p,(char_t*)(*((long*)next_arg)));
                   next_arg+=sizeof(long);
                   fmt++;
                   break;
            default:
                break;
        }
    }
    *p=0;
    return;
}

PUBLIC void kprint(const char_t* fmt,...)
{
    char_t buf[512];
    //u32_t flags;
    //spin_lock_disable_irq(&curs.p_lock,&flags);
    //memset((void*)buf,0,512);
    va_list_t arg=(va_list_t)((char_t*)(&fmt)+sizeof(long));

    vsprintfk(buf,fmt,arg);
    GxH_strwrite(buf,&curs);
    //spin_unlock_enabled_irq(&curs.p_lock,&flags);
    return;
}
