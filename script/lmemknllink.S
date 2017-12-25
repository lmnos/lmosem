/******************************************************************
*		ld自动化编译配置文件 Makefile			  *
*				彭东  ＠ 2013.06.16.10.00	  *
******************************************************************/

#include "config.h"

#ifdef CFG_X86_PLATFORM
#include "platform_t.h"
#include "buildfile.h"
ENTRY(_start)
OUTPUT_ARCH(i386)
OUTPUT_FORMAT(elf32-i386)
SECTIONS
{

        
        . = 0x2000000;
        __begin_kernel = .;
        __begin_lmosem_hal_head_text = .;
        .head.text ALIGN(4) : { *(.head.text) }
        __end_lmosem_hal_head_text = .;
        
        __begin_lmosem_hal_head_data = .;
        .head.data ALIGN(4) : { *(.head.data) }
        __end_lmosem_hal_head_data = .;
        
        __begin_lmosem_hal_init = .;
        .lmosem_hal.init ALIGN(4) : { *(.lmosem_hal.init) }
        __end_lmosem_hal_init = .;

        __begin_lmosem_hal_vector = .;
        .lmosem_hal.vector ALIGN(4) : { *(.lmosem_hal.vector) }
        __end_lmosem_hal_vector = .;
        
        __begin_lmosem_hal_intvect = .;
        .lmosem_hal.intvect ALIGN(4) : { *(.lmosem_hal.intvect) }
        __end_lmosem_hal_intvect = .;

        __begin_hwint_text = .;
        .text ALIGN(4) : { *(.hwint.text) }
        __end_hwint_text = .;

        __begin_text = .;
        .text ALIGN(4) : { *(.text) }
        __end_text = .;

        __begin_spinlock_text = .;
        .text ALIGN(4) : { *(.spinlock.text) }
        __end_spinlock_text = .;

        __begin_data = .;
        .data ALIGN(4) :{ *(.data) }
        __end_data = .;

        __begin_rodata = .;
        .rodata ALIGN(4) :{ *(.rodata) *(.rodata.*) }
        __end_rodata = .;

        __begin_kstrtab = .;
        .kstrtab ALIGN(4) : { *(.kstrtab) }
        __end_kstrtab = .;

        __begin_bss = .;
        .bss ALIGN(4) : { *(.bss) }
        __end_bss = .;
        __end_kernel = .;
        
         /DISCARD/ : { *(.dynstr*) }
         /DISCARD/ : { *(.dynamic*) }
         /DISCARD/ : { *(.plt*) }
         /DISCARD/ : { *(.interp*) }
         /DISCARD/ : { *(.gnu*) }
}

#else
INPUT(LINKR_IPUT_FILE)
OUTPUT(LINKR_OPUT_FILE)
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{

        
        . = 0x30008000;
        __begin_kernel = .;
        __begin_lmosem_hal_head_text = .;
        .head.text ALIGN(4) : { *(.head.text) }
        __end_lmosem_hal_head_text = .;
        
        __begin_lmosem_hal_head_data = .;
        .head.data ALIGN(4) : { *(.head.data) }
        __end_lmosem_hal_head_data = .;
        
        __begin_lmosem_hal_init = .;
        .lmosem_hal.init ALIGN(4) : { *(.lmosem_hal.init) }
        __end_lmosem_hal_init = .;

        __begin_lmosem_hal_vector = .;
        .lmosem_hal.vector ALIGN(4) : { *(.lmosem_hal.vector) }
        __end_lmosem_hal_vector = .;
        
        __begin_lmosem_hal_intvect = .;
        .lmosem_hal.intvect ALIGN(4) : { *(.lmosem_hal.intvect) }
        __end_lmosem_hal_intvect = .;

        __begin_text = .;
        .text ALIGN(4) : { *(.text) }
        __end_text = .;

        __begin_data = .;
        .data ALIGN(4) :{ *(.data) }
        __end_data = .;

        __begin_rodata = .;
        .rodata ALIGN(4) :{ *(.rodata) *(.rodata.*) }
        __end_rodata = .;

        __begin_kstrtab = .;
        .kstrtab ALIGN(4) : { *(.kstrtab) }
        __end_kstrtab = .;

        __begin_bss = .;
        .bss ALIGN(4) : { *(.bss) }
        __end_bss = .;
        __end_kernel = .;
        
         /DISCARD/ : { *(.dynstr*) }
         /DISCARD/ : { *(.dynamic*) }
         /DISCARD/ : { *(.plt*) }
         /DISCARD/ : { *(.interp*) }
         /DISCARD/ : { *(.gnu*) }
}
#endif