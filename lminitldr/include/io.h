/**********************************************************
		输入/输出头文件io.h
***********************************************************
				彭东 ＠ 2011.12.12.11.40
**********************************************************/
#ifndef _IO_H
#define _IO_H
KLINE void out_u8(const u16_t port, const u8_t val)
{

    __asm__ __volatile__("outb  %1, %0\n"
             :
             : "dN"(port), "a"(val));
}

/*KLINE void out_u8_p(const u16_t port, const u8_t val)
{

    __asm__ __volatile__("outb  %1, %0\n\t"
		"nop \n\t"
		"nop \n\t"


		:
             : "dN"(port), "a"(val));
}*/

KLINE u8_t in_u8(const u16_t port)
{
    u8_t tmp;
    /* GCC can optimize here if constant */
    __asm__ __volatile__("inb %1, %0\n"
             : "=a"(tmp)
             : "dN"(port));
    return tmp;
}


KLINE void out_u16(const u16_t port, const u16_t val)
{

    __asm__ __volatile__("outw  %1, %0\n"
             :
             : "dN"(port), "a"(val));
}


KLINE u16_t in_u16(const u16_t port)
{
    u16_t tmp;

    __asm__ __volatile__("inw %1, %0\n"
             : "=a"(tmp)
             : "dN"(port));
    return tmp;
};

/*KLINE void memcopy(void* src, void* dest,uint_t count)
{


    u8_t* ss=src,*sd=dest;
    for(uint_t i=0;i<count;i++)
    {
        sd[i]=ss[i];
    }
    return;
}*/
KLINE sint_t m2mcopy(void* sadr,void* dadr,sint_t len)
{
    if(NULL==sadr||NULL==dadr||1>len)
    {
        return 0;
    }
    u8_t* s=(u8_t*)sadr,*d=(u8_t*)dadr;
    if(s<d)
    {
        for(sint_t i=(len-1);i>=0;i--)
        {
            d[i]=s[i];
        }
        return len;
    }
    if(s>d)
    {
        for(sint_t j=0;j<len;j++)
        {
            d[j]=s[j];
        }
        return len;
    }
    if(s==d)
    {
        return len;
    }
    return 0;
}

KLINE void memset(void* src,u8_t val,uint_t count)
{

    u8_t* ss=src;
    for(uint_t i=0;i<count;i++)
    {
        ss[i]=val;
    }
    return;
}
/*KLINE void out_u32(const u16_t port, const u32_t val)
{

    __asm__ __volatile__("outl  %1, %0\n"
             :
             : "dN"(port), "a"(val));
}



KLINE u32_t in_u32(const u16_t port)
{
    u32_t tmp;

    __asm__ __volatile__("inl %1, %0\n"
             : "=a"(tmp)
             : "dN"(port));
    return tmp;
}

KLINE u64_t read_msr(const u32_t reg)
{
    u32_t eax, edx;

    __asm__ __volatile__ (
            "rdmsr"
            : "=a"(eax), "=d"(edx)
            : "c"(reg)
    );

    return (((u64_t)edx) << 32) | (u64_t)eax;
}


KLINE void write_msr(const u32_t reg, const u64_t val)
{
    __asm__ __volatile__ (
            "wrmsr"
            :
            : "a"( (u32_t) val), "d" ( (u32_t) (val >> 32)), "c" (reg));
}




KLINE void memset(void* s,u8_t c,uint_t count)
{
	u8_t* st=s;
	for(uint_t i=0;i<count;i++)
	{
		st[i]=c;
	}
	return;
}


KLINE void save_flags_cli(cpuflg_t* flags)
{
	 __asm__ __volatile__(
			"pushf \t\n"
			"cli    \t\n"
			"popq %0 \t\n"
	                
	 		: "=m"(*flags)
	                :
			: "memory"
	                      );
	return;
}

KLINE void restore_flags_sti(cpuflg_t* flagsres)
{
	__asm__ __volatile__(
	                     "pushq %0 \t\n"
	                     "popf \t\n"
	                      :
	                      : "m"(*flagsres)
			      : "memory"
	                      );
	return;
}*/

#endif
