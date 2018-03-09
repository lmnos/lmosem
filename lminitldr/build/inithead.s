	.file	"inithead.c"
	.text
	.type	m2mcopy, @function
m2mcopy:
.LFB4:
	.cfi_startproc
	testl	%edx, %edx
	pushl	%edi
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	pushl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	sete	%bl
	testl	%ecx, %ecx
	movl	%eax, %edi
	movb	%bl, %al
	setle	%bl
	orb	%bl, %al
	jne	.L8
	testl	%edi, %edi
	je	.L8
	cmpl	%edx, %edi
	jnb	.L3
	leal	-1(%ecx), %esi
.L4:
	movb	(%edi,%esi), %bl
	movb	%bl, (%edx,%esi)
	decl	%esi
	cmpl	$-1, %esi
	jne	.L4
	jmp	.L2
.L3:
	jbe	.L5
	xorl	%esi, %esi
.L6:
	movb	(%edi,%esi), %bl
	movb	%bl, (%edx,%esi)
	incl	%esi
	cmpl	%esi, %ecx
	jg	.L6
	jmp	.L2
.L5:
	movl	$0, %eax
	cmovne	%eax, %ecx
	jmp	.L2
.L8:
	xorl	%ecx, %ecx
.L2:
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 12
	movl	%ecx, %eax
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE4:
	.size	m2mcopy, .-m2mcopy
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"LMOSLDR DIE ERROR:%s\n"
	.text
	.globl	error
	.type	error, @function
error:
.LFB11:
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
.L14:
	jmp	.L14
	.cfi_endproc
.LFE11:
	.size	error, .-error
	.globl	strcmpl
	.type	strcmpl, @function
strcmpl:
.LFB12:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	movl	8(%esp), %edx
	movl	12(%esp), %ecx
.L17:
	movsbl	(%ecx), %eax
	testb	%al, %al
	je	.L18
	movb	(%edx), %bl
	cmpb	%bl, %al
	jne	.L18
	testb	%bl, %bl
	je	.L18
	incl	%ecx
	incl	%edx
	jmp	.L17
.L18:
	movsbl	(%edx), %edx
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	subl	%edx, %eax
	ret
	.cfi_endproc
.LFE12:
	.size	strcmpl, .-strcmpl
	.section	.rodata.str1.1
.LC1:
	.string	"no mrddsc"
.LC2:
	.string	"not find file"
	.text
	.globl	find_file
	.type	find_file, @function
find_file:
.LFB9:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	call	__x86.get_pc_thunk.bp
	addl	$_GLOBAL_OFFSET_TABLE_, %ebp
	subl	$28, %esp
	.cfi_def_cfa_offset 48
	cmpl	$-1426085121, 67113124
	jne	.L29
	cmpl	$-1426085121, 67113120
	jne	.L29
	cmpl	$-5570646, 67113132
	jne	.L29
	cmpl	$-5570646, 67113128
	jne	.L29
	movl	67113108, %ecx
	movl	67113104, %edx
	cmpl	$0, %ecx
	ja	.L38
	cmpl	$1, %edx
	jbe	.L29
.L38:
	cmpl	$0, 67113116
	ja	.L33
	cmpl	$1, 67113112
	ja	.L33
.L29:
	subl	$12, %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 60
	leal	.LC1@GOTOFF(%ebp), %eax
	jmp	.L42
.L33:
	.cfi_restore_state
	movl	67113032, %eax
	xorl	%esi, %esi
	xorl	%edi, %edi
	leal	67108864(%eax), %ebx
.L39:
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	pushl	%eax
	.cfi_def_cfa_offset 52
	pushl	%eax
	.cfi_def_cfa_offset 56
	leal	64(%ebx), %eax
	pushl	%eax
	.cfi_def_cfa_offset 60
	pushl	60(%esp)
	.cfi_def_cfa_offset 64
	call	strcmpl
	addl	$16, %esp
	.cfi_def_cfa_offset 48
	testl	%eax, %eax
	je	.L40
	movl	12(%esp), %ecx
	addl	$1, %esi
	movl	8(%esp), %edx
	adcl	$0, %edi
	addl	$256, %ebx
	cmpl	%edi, %ecx
	jne	.L39
	cmpl	%esi, %edx
	jne	.L39
	leal	.LC2@GOTOFF(%ebp), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 60
.L42:
	pushl	%eax
	.cfi_def_cfa_offset 64
	call	error
.L40:
	.cfi_def_cfa_offset 48
	addl	$28, %esp
	.cfi_def_cfa_offset 20
	movl	%ebx, %eax
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 12
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 8
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE9:
	.size	find_file, .-find_file
	.section	.rodata.str1.1
.LC3:
	.string	"lmldrsve.bin"
.LC4:
	.string	"not file lmldrsve.bin"
	.text
	.globl	write_realintsvefile
	.type	write_realintsvefile, @function
write_realintsvefile:
.LFB8:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$20, %esp
	.cfi_def_cfa_offset 28
	leal	.LC3@GOTOFF(%ebx), %eax
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	find_file
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	testl	%eax, %eax
	jne	.L44
	leal	.LC4@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	error
.L44:
	.cfi_def_cfa_offset 16
	movl	48(%eax), %ecx
	movl	32(%eax), %eax
	addl	$8, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	movl	$4096, %edx
	addl	$67108864, %eax
	jmp	m2mcopy
	.cfi_endproc
.LFE8:
	.size	write_realintsvefile, .-write_realintsvefile
	.section	.rodata.str1.1
.LC5:
	.string	"lmldrkrl.bin"
.LC6:
	.string	"not file lmldrkrl.bin"
	.text
	.globl	write_ldrkrlfile
	.type	write_ldrkrlfile, @function
write_ldrkrlfile:
.LFB10:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$20, %esp
	.cfi_def_cfa_offset 28
	leal	.LC5@GOTOFF(%ebx), %eax
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	find_file
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	testl	%eax, %eax
	jne	.L47
	leal	.LC6@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	error
.L47:
	.cfi_def_cfa_offset 16
	movl	48(%eax), %ecx
	movl	32(%eax), %eax
	addl	$8, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	movl	$2097152, %edx
	addl	$67108864, %eax
	jmp	m2mcopy
	.cfi_endproc
.LFE10:
	.size	write_ldrkrlfile, .-write_ldrkrlfile
	.globl	inithead_entry
	.type	inithead_entry, @function
inithead_entry:
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
	call	write_realintsvefile
	addl	$24, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	jmp	write_ldrkrlfile
	.cfi_endproc
.LFE7:
	.size	inithead_entry, .-inithead_entry
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB14:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE14:
	.section	.text.__x86.get_pc_thunk.bp,"axG",@progbits,__x86.get_pc_thunk.bp,comdat
	.globl	__x86.get_pc_thunk.bp
	.hidden	__x86.get_pc_thunk.bp
	.type	__x86.get_pc_thunk.bp, @function
__x86.get_pc_thunk.bp:
.LFB15:
	.cfi_startproc
	movl	(%esp), %ebp
	ret
	.cfi_endproc
.LFE15:
	.section	.note.GNU-stack,"",@progbits
