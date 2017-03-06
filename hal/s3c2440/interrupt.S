/**********************************************************
        中断异常入口文件interrupt.s
***********************************************************
                彭东 ＠ 2013.06.10.16.55
**********************************************************/

.section .lmosem_hal.intvect,"ax"
.code 32
.align 4
.extern hal_undefins_distr
.extern hal_swi_distr
.extern hal_prefabt_distr
.extern hal_dataabt_distr
.extern hal_bugdie_distr
.extern hal_irq_distr
.extern hal_frq_distr
.extern hal_dbugint
.extern hal_dbugint2
.global hal_undefins
.global hal_swi
.global hal_prefabt
.global hal_dataabt
.global hal_bugdie
.global hal_irq
.global hal_frq

.equ ALLREGS_STKSZ,64
.equ STKOFFSET_PC,60
.equ NPCREGS_STKSZ,60
 
.equ CPUMODE_MASK,31
.equ CPUSVE_MODE,19
.equ MSTK_OFF,12
.equ NINT_SVEMODE,0xd3
.equ NINT_IRQMODE,0xd2
.equ NINT_FRQMODE,0xd1
.equ NINT_ABTMODE,0xd7
.equ NINT_UNDMODE,0xdb

        
hal_undefins:
        msr   cpsr_c,#NINT_SVEMODE
        sub   sp,sp,#ALLREGS_STKSZ
        stmia sp,{r0-lr}^
        msr   cpsr_c,#NINT_UNDMODE
        sub   r1,lr,#0
        mrs   r0,spsr
        msr   cpsr_c,#NINT_SVEMODE
        str   r1,[sp,#STKOFFSET_PC]
        stmfd sp!,{r0,lr}
        mov   r0,sp
        bl    hal_undefins_distr
        ldmfd sp!,{r0,lr}
        msr   spsr,r0
        ldmia sp,{r0-lr}^
	add   sp,sp,#NPCREGS_STKSZ
	ldmfd sp!,{pc}^
        
        
        
        
hal_swi:
	sub   sp,sp,#ALLREGS_STKSZ
        stmia sp,{r1-lr}^
        mrs   r1,spsr
        str   lr,[sp,#STKOFFSET_PC]
        stmfd sp!,{r1,lr}
        mov   r1,sp
        bl    hal_swi_distr
        ldmfd sp!,{r1,lr}
        msr   spsr,r1
        ldmia sp,{r1-lr}^
	add   sp,sp,#NPCREGS_STKSZ
	ldmfd sp!,{pc}^
       
hal_prefabt:
        msr   cpsr_c,#NINT_SVEMODE
        sub   sp,sp,#ALLREGS_STKSZ
        stmia sp,{r0-lr}^
        msr   cpsr_c,#NINT_ABTMODE
        sub   r1,lr,#4
        mrs   r0,spsr
        msr   cpsr_c,#NINT_SVEMODE
        str   r1,[sp,#STKOFFSET_PC]
        stmfd sp!,{r0,lr}
        mov   r0,sp
        bl    hal_prefabt_distr
        ldmfd sp!,{r0,lr}
        msr   spsr,r0
        ldmia sp,{r0-lr}^
	add   sp,sp,#NPCREGS_STKSZ
	ldmfd sp!,{pc}^
        
       
hal_dataabt:
	msr   cpsr_c,#NINT_SVEMODE
        sub   sp,sp,#ALLREGS_STKSZ
        stmia sp,{r0-lr}^
        msr   cpsr_c,#NINT_ABTMODE
        sub   r1,lr,#8
        mrs   r0,spsr
        msr   cpsr_c,#NINT_SVEMODE
        str   r1,[sp,#STKOFFSET_PC]
        stmfd sp!,{r0,lr}
        mov   r0,sp
        bl    hal_dataabt_distr
        ldmfd sp!,{r0,lr}
        msr   spsr,r0
        ldmia sp,{r0-lr}^
	add   sp,sp,#NPCREGS_STKSZ
	ldmfd sp!,{pc}^

        
hal_bugdie:
        b .
hal_irq:
	msr   cpsr_c,#NINT_SVEMODE
        sub   sp,sp,#ALLREGS_STKSZ
        stmia sp,{r0-lr}^
        msr   cpsr_c,#NINT_IRQMODE
        sub   r1,lr,#4
        mrs   r0,spsr
        msr   cpsr_c,#NINT_SVEMODE
        str   r1,[sp,#STKOFFSET_PC]
        stmfd sp!,{r0,lr}
        mov   r0,sp
        bl    hal_irq_distr
        ldmfd sp!,{r0,lr}
        msr   spsr,r0
        ldmia sp,{r0-lr}^
	add   sp,sp,#NPCREGS_STKSZ
	ldmfd sp!,{pc}^

        
hal_frq:
        msr   cpsr_c,#NINT_SVEMODE
        sub   sp,sp,#ALLREGS_STKSZ
        stmia sp,{r0-lr}^
        msr   cpsr_c,#NINT_FRQMODE
        sub   r1,lr,#4
        mrs   r0,spsr
        msr   cpsr_c,#NINT_SVEMODE
        str   r1,[sp,#STKOFFSET_PC]
        stmfd sp!,{r0,lr}
        mov   r0,sp
        bl    hal_frq_distr
        ldmfd sp!,{r0,lr}
        msr   spsr,r0
        ldmia sp,{r0-lr}^
	add   sp,sp,#NPCREGS_STKSZ
	ldmfd sp!,{pc}^

.end
