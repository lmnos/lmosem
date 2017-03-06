/**********************************************************
		i8259中断控制器源文件i8259.c
***********************************************************
				彭东 ＠ 2011.12.19.18.20
**********************************************************/
//#include "types.h"
//#include "mcontrol.h"

#include "lmosemtypes.h"
#include "lmosemmctrl.h"
PUBLIC LKINIT void init_i8259()
{
	

		out_u8_p(ZIOPT,ICW1);		
		out_u8_p(SIOPT,ICW1);
		out_u8_p(ZIOPT1,ZICW2);
		out_u8_p(SIOPT1,SICW2);
		out_u8_p(ZIOPT1,ZICW3);
		out_u8_p(SIOPT1,SICW3);
		out_u8_p(ZIOPT1,ICW4);
		out_u8_p(SIOPT1,ICW4);
		//system_error("8259dddddddddddddd");
	
	out_u8_p(ZIOPT1,0xff);
	out_u8_p(SIOPT1,0xff);
	//printf("  init i8259!!\n");
	return;
}

PUBLIC void i8259_send_eoi()
{
	 out_u8_p(_INTM_CTL,_EOI);
         out_u8_p(_INTS_CTL,_EOI);
	return;
}

PUBLIC void i8259_enabled_line(u32_t line)
{
	u32_t flags;
	save_flags_cli(&flags);
        if(line<8)
        {
                u8_t amtmp=in_u8(_INTM_CTLMASK);
                amtmp&=(u8_t)(~(1<<line));
                out_u8_p(_INTM_CTLMASK,amtmp);
        }
        else
        {
                u8_t astmp=in_u8(_INTM_CTLMASK);
                astmp&=(u8_t)(~(1<<2));
                out_u8_p(_INTM_CTLMASK,astmp);
		astmp=in_u8(_INTS_CTLMASK);
                astmp&=(u8_t)(~(1<<(line-8)));
                out_u8_p(_INTS_CTLMASK,astmp);
        }
        restore_flags_sti(&flags);
        return;
}

PUBLIC void i8259_disable_line(u32_t line)
{
	u32_t flags;
	save_flags_cli(&flags);
        if(line<8)
        {
                u8_t amtmp=in_u8(_INTM_CTLMASK);
                amtmp|=(u8_t)((1<<line));
                out_u8_p(_INTM_CTLMASK,amtmp);
        }
        else
        {
                u8_t astmp=in_u8(_INTM_CTLMASK);
                astmp|=(u8_t)((1<<2));
                out_u8_p(_INTM_CTLMASK,astmp);
				astmp=in_u8(_INTS_CTLMASK);
                astmp|=(u8_t)((1<<(line-8)));
                out_u8_p(_INTS_CTLMASK,astmp);
        }
        restore_flags_sti(&flags);
	return;
}

PUBLIC void i8259_save_disableline(u64_t* svline,u32_t line)
{
	u32_t intftmp;
	u32_t flags;
	save_flags_cli(&flags);
	u8_t altmp  = in_u8(_INTM_CTLMASK);
	intftmp=altmp;
	altmp = in_u8(_INTS_CTLMASK);
	intftmp=(intftmp<<8)|altmp;
	*svline=intftmp;
	i8259_disable_line(line);
	
	restore_flags_sti(&flags);
	return;
}

PUBLIC void i8259_rest_enabledline(u64_t* svline,u32_t line)
{
	u32_t flags;
	save_flags_cli(&flags);
	
	u32_t intftmp=(u32_t)(*svline);
	
	u8_t altmp=(intftmp&0xff);
	out_u8_p(_INTS_CTLMASK,altmp);
	altmp=(u8_t)(intftmp>>8); 
	out_u8_p(_INTM_CTLMASK,altmp);
	
	restore_flags_sti(&flags);
	
	return;
}
