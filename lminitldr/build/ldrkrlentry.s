	.file	"ldrkrlentry.c"
	.text
	.globl	ldrkrl_entry
	.type	ldrkrl_entry, @function
ldrkrl_entry:
.LFB7:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$8, %esp
	.cfi_def_cfa_offset 16
	call	init_curs@PLT
	call	close_curs@PLT
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	$1792
	.cfi_def_cfa_offset 32
	call	clear_screen@PLT
	call	init_bstartparm@PLT
	addl	$24, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE7:
	.size	ldrkrl_entry, .-ldrkrl_entry
	.section	.rodata
.LC0:
	.string	"LMOSKLDR DIE ERROR:%s\n"
	.text
	.globl	kerror
	.type	kerror, @function
kerror:
.LFB8:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$16, %esp
	.cfi_def_cfa_offset 24
	leal	.LC0@GOTOFF(%ebx), %eax
	pushl	24(%esp)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 16
.L4:
	jmp	.L4
	.cfi_endproc
.LFE8:
	.size	kerror, .-kerror
	.p2align 4
	.globl	die
	.type	die, @function
die:
.LFB9:
	.cfi_startproc
	subl	$32, %esp
	.cfi_def_cfa_offset 36
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	36(%esp), %eax
	movl	%eax, 16(%esp)
	movl	36(%esp), %eax
	movl	%eax, 12(%esp)
	cmpl	$0, 36(%esp)
	jne	.L8
.L9:
	jmp	.L9
.L8:
	movl	$0, 28(%esp)
	jmp	.L10
.L15:
	movl	$0, 24(%esp)
	jmp	.L11
.L14:
	movl	$0, 20(%esp)
	jmp	.L12
.L13:
	addl	$1, 20(%esp)
.L12:
	movl	20(%esp), %eax
	cmpl	16(%esp), %eax
	jb	.L13
	addl	$1, 24(%esp)
.L11:
	movl	24(%esp), %eax
	cmpl	12(%esp), %eax
	jb	.L14
	addl	$1, 28(%esp)
.L10:
	movl	28(%esp), %eax
	cmpl	36(%esp), %eax
	jb	.L15
	nop
	addl	$32, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE9:
	.size	die, .-die
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB10:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE10:
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB11:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE11:
	.section	.note.GNU-stack,"",@progbits
