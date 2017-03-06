/**********************************************************
		转换显示字符串头文件vgastr.h
***********************************************************
				彭东 ＠ 2011.12.15.07.30
**********************************************************/

#ifndef _VGASTR_H
#define _VGASTR_H



PUBLIC void init_curs();
PUBLIC void set_curs(u32_t x, u32_t y);
PUBLIC void GxH_strwrite(char_t* str,cursor_t* cursptr);
//PUBLIC char * itoa(u32_t n, int base);
PUBLIC char* numberk(char_t* str,uint_t n, sint_t base);
PUBLIC void clear_screen(u16_t srrv);
PUBLIC void put_one_char(char_t cr,uint_t x,uint_t y);
PUBLIC void close_curs();
PUBLIC void vsprintfk(char_t* buf,const char_t* fmt,va_list_t args);
PUBLIC void kprint(const char_t* fmt,...);

KLINE void current_curs(cursor_t* cp,u32_t c_flg)
{
	//u32_t flags;
	
	if(c_flg==VGACHAR_LR_CFLG)
	{
		cp->y++;
		cp->x=0;
		if(cp->y>24)
		{
			cp->y=0;
			clear_screen(VGADP_DFVL);
		}
		
		return;
	}
	if(c_flg==VGACHAR_DF_CFLG)
	{
		cp->x+=2;
		if(cp->x>159)
		{
			cp->x=0;
			cp->y++;
			if(cp->y>24)
			{
				cp->y=0;
				clear_screen(VGADP_DFVL);
			}
			return;
		}
		
	}
	
	
/*out_set:	
	
	save_flags_cli(&flags);
	out_u8(VGACTRL_REG_ADR,VGASADH_REG_INX);
	out_u8(VGACTRL_REG_DAT,(u8_t)(((80*cp->cvmemadr)>>8)&0xff));
	out_u8(VGACTRL_REG_ADR,VGASADL_REG_INX);
	out_u8(VGACTRL_REG_DAT,(u8_t)((80*cp->cvmemadr)&0xff));	
	restore_flags_sti(&flags);    
	*/
	
	return;
	
}
#endif

