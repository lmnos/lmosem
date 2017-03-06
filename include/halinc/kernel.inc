;extern GDT
;extern IDT
;extern iGDT
;extern iIDT
extern syscalls_table
;extern kernel_kesp
;extern init_descriptor

extern lmosem_hwint_allocator
extern lmosem_fault_allocator
extern lmosem_syscl_allocator

global	exc_divide_error
global	exc_single_step_exception
global	exc_nmi
global	exc_breakpoint_exception
global	exc_overflow
global	exc_bounds_check
global	exc_inval_opcode
global	exc_copr_not_available
global	exc_double_fault
global	exc_copr_seg_overrun
global	exc_inval_tss
global	exc_segment_not_present
global	exc_stack_exception
global	exc_general_protection
global	exc_page_fault
global	exc_copr_error
global	exc_alignment_check
global	exc_machine_check
global	exc_simd_fault
global	hxi_exc_general_intpfault
global	hxi_hwint00
global	hxi_hwint01
global	hxi_hwint02
global	hxi_hwint03
global	hxi_hwint04
global	hxi_hwint05
global	hxi_hwint06
global	hxi_hwint07
global	hxi_hwint08
global	hxi_hwint09
global	hxi_hwint10
global	hxi_hwint11
global	hxi_hwint12
global	hxi_hwint13
global	hxi_hwint14
global	hxi_hwint15
global	hxi_hwint16
global	hxi_hwint17
global	hxi_hwint18
global	hxi_hwint19
global	hxi_hwint20
global	hxi_hwint21
global	hxi_hwint22
global	hxi_hwint23
global  hxi_apic_ipi_schedul
global  hxi_apic_svr
global  hxi_apic_timer
global  hxi_apic_thermal
global  hxi_apic_performonitor
global  hxi_apic_lint0
global  hxi_apic_lint1
global  hxi_apic_error
global	exi_sys_call
global  _ret_from_user_mode

%define INT_VECTOR_APIC_IPI_SCHEDUL 0xe0
%define	INT_VECTOR_APIC_SVR 0xef
%define INT_VECTOR_APIC_TIMER	0xf0
%define INT_VECTOR_APIC_THERMAL	0xf1
%define INT_VECTOR_APIC_PERFORM	0xf2
%define INT_VECTOR_APIC_LINTO	0xf3
%define INT_VECTOR_APIC_LINTI	0xf4
%define INT_VECTOR_APIC_ERROR	0xf5

%define _KERNEL_DS 0x10
%define _NOERRO_CODE 0xffffffff

%define _INTM_CTL		0x20	; I/O port for interrupt controller         <Master>
%define _INTM_CTLMASK	0x21	; setting bits in this port disables ints   <Master>
%define _INTS_CTL		0xA0	; I/O port for second interrupt controller  <Slave>
%define _INTS_CTLMASK	0xA1	; setting bits in this port disables ints   <Slave>
%define _EOI			0x20

;IF OperandSize PUSHA/PUSHAD 32 (* PUSHAD instruction *)
;THEN
;Temp PUSHA/PUSHAD (ESP);
;Push(EAX);
;Push(ECX);
;Push(EDX);
;Push(EBX);
;Push(Temp);
;Push(EBP);
;Push(ESI);
;Push(EDI);
;ELSE (* OperandSize PUSHA/PUSHAD 16, PUSHA instruction *)
;Temp PUSHA/PUSHAD (SP);
;Push(AX);
;Push(CX);
;Push(DX);
;Push(BX);
;Push(Temp);
;Push(BP);
;Push(SI);
;Push(DI);
;FI;

%macro	MASK_MASTER_EIO	1
	in	al, _INTM_CTLMASK	; `.0x21
	or	al, (1 << %1)		;  | 屏蔽当前中断
	out	_INTM_CTLMASK, al	; /
	mov	al, _EOI			; `. 置EOI位
	out	_INTM_CTL, al		; /
%endmacro

%macro	MASK_SLAVE_EIO	1
	in	al, _INTS_CTLMASK	; `.0xa1
	or	al, (1 << (%1 - 8))	;  | 屏蔽当前中断
	out	_INTS_CTLMASK, al	; /
	mov	al, _EOI			; `. 置EOI位(master)
	out	_INTM_CTL, al		; /
	nop				; `. 置EOI位(slave)
	out	_INTS_CTL, al		; /  一定注意：slave和master都要置EOI
%endmacro
%macro	RECOVER_MASTER_CURRENINT	1
	in	al, _INTM_CTLMASK	; `.
	and	al, ~(1 << %1)		;  | 恢复接受当前中断
	out	_INTM_CTLMASK, al	; /
%endmacro
%macro	RECOVER_SLAVE_CURRENINT	1
	in	al, _INTS_CTLMASK	; `.
	and	al, ~(1 << (%1 - 8))	;  | 恢复接受当前中断
	out	_INTS_CTLMASK, al	; /
%endmacro

%macro	SAVEALL	0

	pushad
	push    ds
	push    es
	push    fs
	push    gs
	
%endmacro


%macro	RESTOREALL	0
   	pop	gs
	pop	fs
	pop	es
	pop	ds
	popad

	iretd
%endmacro

%macro	SAVEALLFAULT 0
	pushad
	push    ds
	push    es
	push    fs
	push    gs
	
	mov     di, ss
	mov     ds, di
	mov     es, di
	mov     gs, di
	mov	fs, di
%endmacro

%macro	RESTOREALLFAULT	0
   	pop	gs
	pop	fs
	pop	es
	pop	ds
	popad
	add	esp,4
	iretd
%endmacro

%macro  SAVE_FLAGS_STI 0
        pushf
        sti
%endmacro

%macro  RESTORE_FLAGS_CLI 0
        popf
%endmacro

%macro	SRFTFAULT 1
	push	  _NOERRO_CODE
	SAVEALLFAULT
	mov 	eax,%1
	mov 	edx,esp
	call 	lmosem_fault_allocator
	RESTOREALLFAULT
%endmacro

%macro	SRFTFAULT_ECODE 1
	SAVEALLFAULT
	mov 	eax,%1
	mov 	edx,esp
	call 	lmosem_fault_allocator
	RESTOREALLFAULT
%endmacro

%macro	HARWINT	1
	SAVEALL
	mov     di, ss
	mov     ds, di
	mov     es, di
	mov     gs, di
	mov		fs, di
	mov		eax, %1
	mov 	edx,esp
	call    lmosem_hwint_allocator
	RESTOREALL
%endmacro

%macro  EXI_SCALL  0
	push 	eax	
	push 	ecx
	push 	edx
	push 	ebx
	push 	ebp
	push 	esi 
	push 	edi
	push    ds
	push    es
	push    fs
	push    gs
	mov    	di, ss
	mov    	ds, di
	mov    	es, di
	mov    	gs, di
	mov    	fs, di
	mov		eax,eax
	mov		edx,esp	
	call   	lmosem_syscl_allocator
	pop		gs
	pop		fs
	pop		es
	pop		ds
	pop 	edi
	pop 	esi
	pop   	ebp
	pop     ebx
	pop 	edx
	pop     ecx
	add 	esp,4
	iretd
%endmacro
