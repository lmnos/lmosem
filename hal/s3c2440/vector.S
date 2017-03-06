/**********************************************************
        向量文件vector.s
***********************************************************
                彭东 ＠ 2013.06.01.10.20
**********************************************************/

.section .lmosem_hal.vector,"ax"
.code 32
.align 0

.extern hal_undefins
.extern hal_swi
.extern hal_prefabt
.extern hal_dataabt
.extern hal_bugdie
.extern hal_irq
.extern hal_frq
.extern _start

.global vector
vector:
        ldr pc,lmosem_restart_l
        ldr pc,lmosem_undefins_l
        ldr pc,lmosem_swi_l
        ldr pc,lmosem_prefabt_l
        ldr pc,lmosem_dataabt_l
        ldr pc,lmosem_bugdie_l
        ldr pc,lmosem_irq_l
        ldr pc,lmosem_frq_l
        nop
        nop
        nop
        nop
 _err:
        b   _start

.align 4
lmosem_restart_l:  .word _start
lmosem_undefins_l: .word hal_undefins
lmosem_swi_l:      .word hal_swi
lmosem_prefabt_l:  .word hal_prefabt
lmosem_dataabt_l:  .word hal_dataabt
lmosem_bugdie_l:   .word hal_bugdie
lmosem_irq_l:      .word hal_irq
lmosem_frq_l:      .word hal_frq


.end
