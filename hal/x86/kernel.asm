;*****************************************************************************
;*		底层核心文件Kernel.asm				    *
;*				彭东  ＠ 2011.12.01.10.00		     *
;*****************************************************************************

%include "../include/halinc/kernel.inc"
[section .hwint.text]
[BITS 32]

ALIGN	16
exc_divide_error:
	SRFTFAULT 0
ALIGN	16
exc_single_step_exception:
	SRFTFAULT 1
ALIGN	16
exc_nmi:
	SRFTFAULT 2
ALIGN	16
exc_breakpoint_exception:
	SRFTFAULT 3
ALIGN	16
exc_overflow:
	SRFTFAULT 4
ALIGN	16
exc_bounds_check:
	SRFTFAULT 5
ALIGN	16
exc_inval_opcode:
	SRFTFAULT 6
ALIGN	16
exc_copr_not_available:
	SRFTFAULT 7
ALIGN	16
exc_double_fault:
	SRFTFAULT_ECODE 8
ALIGN	16
exc_copr_seg_overrun:
	SRFTFAULT 9
ALIGN	16
exc_inval_tss:
	SRFTFAULT_ECODE 10
ALIGN	16
exc_segment_not_present:
	SRFTFAULT_ECODE 11
ALIGN	16
exc_stack_exception:
	SRFTFAULT_ECODE 12
ALIGN	16
exc_general_protection:
	SRFTFAULT_ECODE 13
ALIGN	16
exc_page_fault:
	SRFTFAULT_ECODE 14
ALIGN	16
exc_copr_error:
	SRFTFAULT 16
ALIGN	16
exc_alignment_check:
	SRFTFAULT_ECODE 17
ALIGN	16
exc_machine_check:
	SRFTFAULT 18
ALIGN	16
exc_simd_fault:
	SRFTFAULT 19
ALIGN	16
hxi_exc_general_intpfault:
	SRFTFAULT 256
	
	
ALIGN	16
hxi_hwint00:
	HARWINT	20
ALIGN	16
hxi_hwint01:
	HARWINT	21
ALIGN	16
hxi_hwint02:
	HARWINT	22
ALIGN	16
hxi_hwint03:
	HARWINT	23
ALIGN	16
hxi_hwint04:
	HARWINT	24
ALIGN	16
hxi_hwint05:
	HARWINT	25
ALIGN	16
hxi_hwint06:
	HARWINT	26
ALIGN	16
hxi_hwint07:
	HARWINT	27
ALIGN	16
hxi_hwint08:
	HARWINT	28
ALIGN	16
hxi_hwint09:
	HARWINT	29
ALIGN	16
hxi_hwint10:
	HARWINT	30
ALIGN	16
hxi_hwint11:
	HARWINT	31
ALIGN	16
hxi_hwint12:
	HARWINT	32

ALIGN	16
hxi_hwint13:
	HARWINT	33
ALIGN	16
hxi_hwint14:
	HARWINT	34
ALIGN	16
hxi_hwint15:
	HARWINT	35
ALIGN	16
hxi_hwint16:
	HARWINT	36
ALIGN	16
hxi_hwint17:
	HARWINT	37
	
ALIGN	16
hxi_hwint18:
	HARWINT	38
	
ALIGN	16
hxi_hwint19:
	HARWINT	39
	
ALIGN	16
hxi_hwint20:
	HARWINT	40			
	
ALIGN	16
hxi_hwint21:
	HARWINT	41

ALIGN	16
hxi_hwint22:
	HARWINT	42
ALIGN	16
hxi_hwint23:
	HARWINT	43
				
ALIGN	16
hxi_apic_ipi_schedul:
	HARWINT	INT_VECTOR_APIC_IPI_SCHEDUL		
ALIGN	16
hxi_apic_svr:
	HARWINT	INT_VECTOR_APIC_SVR	
ALIGN	16
hxi_apic_timer:
	HARWINT	INT_VECTOR_APIC_TIMER	
ALIGN	16
hxi_apic_thermal:
	HARWINT	INT_VECTOR_APIC_THERMAL	
ALIGN	16
hxi_apic_performonitor:
	HARWINT	INT_VECTOR_APIC_PERFORM	
ALIGN	16
hxi_apic_lint0:
	HARWINT	INT_VECTOR_APIC_LINTO	
ALIGN	16
hxi_apic_lint1:
	HARWINT	INT_VECTOR_APIC_LINTI	
ALIGN	16
hxi_apic_error:
	HARWINT	INT_VECTOR_APIC_ERROR

ALIGN	16
exi_sys_call:
	EXI_SCALL
ALIGN	16
_ret_from_user_mode:
	RECOVER_MASTER_CURRENINT	0
	RESTOREALL

;stack:
;	times 4096 dd 0
