/**********************************************************
        中断异常分配器文件intabtdistr.h
***********************************************************
                彭东 ＠ 2013.06.23.17.10
**********************************************************/
#ifndef _INTABTDISTR_H
#define _INTABTDISTR_H

void hal_undefins_distr(void* sframe);
sysstus_t hal_swi_distr(uint_t swinr,void* sframe);
void hal_prefabt_distr(void* sframe);
void hal_dataabt_distr(void* sframe);
void hal_bugdie_distr(void* sframe);
void hal_irq_distr(void* sframe);
void hal_frq_distr(void* sframe);
void hal_eint_distr(void* sframe,uint_t mintnr,uint_t pndbts,uint_t pndbte);
void hal_sint_distr(void* sframe,uint_t mintnr,uint_t pndbts,uint_t pndbte);
void hal_lcdint_distr(void* sframe,uint_t mintnr,uint_t pndbts,uint_t pndbte);
void hal_int_distr(void* sframe,uint_t mintnr);
void hal_run_intflthandle(uint_t ifdnr,void* sframe);

#endif // INTABTDISTR_H
