/**********************************************************
		i8259中断控制器头文件i8259.h
***********************************************************
				彭东 ＠ 2011.12.19.18.20
**********************************************************/

#ifndef _I8259_H
#define _I8259_H
PUBLIC void init_i8259();
PUBLIC void i8259_send_eoi();
PUBLIC void i8259_enabled_line(u32_t line);
PUBLIC void i8259_disable_line(u32_t line);
PUBLIC void i8259_save_disableline(u64_t* svline,u32_t line);
PUBLIC void i8259_rest_enabledline(u64_t* svline,u32_t line);
#endif
