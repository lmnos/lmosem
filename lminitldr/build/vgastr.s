	.file	"vgastr.c"
	.text
	.globl	init_curs
	.type	init_curs, @function
init_curs:
.LFB7:
	.cfi_startproc
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	$753664, curs@GOTOFF(%eax)
	movl	$786431, 4+curs@GOTOFF(%eax)
	movl	$0, 8+curs@GOTOFF(%eax)
	movl	$0, 12+curs@GOTOFF(%eax)
	movl	$0, 16+curs@GOTOFF(%eax)
	ret
	.cfi_endproc
.LFE7:
	.size	init_curs, .-init_curs
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"0123456789abcdef"
	.text
	.globl	numberk
	.type	numberk, @function
numberk:
.LFB9:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$48, %esp
	.cfi_def_cfa_offset 56
	movl	60(%esp), %eax
	movb	$0, 47(%esp)
	testl	%eax, %eax
	jne	.L3
	leal	46(%esp), %ecx
	movb	$48, 46(%esp)
.L6:
	movl	56(%esp), %eax
	jmp	.L4
.L3:
	leal	47(%esp), %ecx
.L5:
	xorl	%edx, %edx
	decl	%ecx
	divl	64(%esp)
	movb	.LC0@GOTOFF(%ebx,%edx), %dl
	testl	%eax, %eax
	movb	%dl, (%ecx)
	jne	.L5
	jmp	.L6
.L4:
	movb	(%ecx), %dl
	testb	%dl, %dl
	je	.L11
	incl	%eax
	incl	%ecx
	movb	%dl, -1(%eax)
	jmp	.L4
.L11:
	addl	$48, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE9:
	.size	numberk, .-numberk
	.globl	set_curs
	.type	set_curs, @function
set_curs:
.LFB10:
	.cfi_startproc
	movl	4(%esp), %edx
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	%edx, 12+curs@GOTOFF(%eax)
	movl	8(%esp), %edx
	movl	%edx, 16+curs@GOTOFF(%eax)
	ret
	.cfi_endproc
.LFE10:
	.size	set_curs, .-set_curs
	.globl	put_one_char
	.type	put_one_char, @function
put_one_char:
.LFB12:
	.cfi_startproc
	imull	$160, 12(%esp), %eax
	movl	4(%esp), %edx
	addl	8(%esp), %eax
	movb	%dl, 753664(%eax)
	ret
	.cfi_endproc
.LFE12:
	.size	put_one_char, .-put_one_char
	.globl	close_curs
	.type	close_curs, @function
close_curs:
.LFB13:
	.cfi_startproc
	movb	$10, %al
	movl	$980, %edx
#APP
# 11 "../include/io.h" 1
	outb  %al, %dx

# 0 "" 2
#NO_APP
	movb	$32, %al
	movl	$981, %edx
#APP
# 11 "../include/io.h" 1
	outb  %al, %dx

# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE13:
	.size	close_curs, .-close_curs
	.globl	clear_screen
	.type	clear_screen, @function
clear_screen:
.LFB11:
	.cfi_startproc
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	4(%esp), %edx
	movl	$0, 12+curs@GOTOFF(%eax)
	movl	$0, 16+curs@GOTOFF(%eax)
	movl	$753664, %eax
.L16:
	movw	%dx, (%eax)
	addl	$2, %eax
	cmpl	$757666, %eax
	jne	.L16
	jmp	close_curs
	.cfi_endproc
.LFE11:
	.size	clear_screen, .-clear_screen
	.globl	GxH_strwrite
	.type	GxH_strwrite, @function
GxH_strwrite:
.LFB8:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	xorl	%edi, %edi
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	movl	24(%esp), %ebp
	movl	20(%esp), %ebx
	imull	$160, 16(%ebp), %eax
	movl	0(%ebp), %esi
	addl	12(%ebp), %esi
	addl	%eax, %esi
.L19:
	movb	(%ebx), %al
	testb	%al, %al
	je	.L33
	cmpb	$10, %al
	jne	.L20
	cmpb	$0, 1(%ebx)
	leal	1(%ebx), %eax
	je	.L21
	movl	%eax, %ebx
	movl	$1, %edi
.L20:
	movl	12(%ebp), %eax
	addl	$2, %eax
	cmpl	$159, %eax
	ja	.L22
	movl	%eax, 12(%ebp)
	jmp	.L23
.L22:
	movl	16(%ebp), %eax
	movl	$0, 12(%ebp)
	incl	%eax
	cmpl	$24, %eax
	ja	.L24
	movl	%eax, 16(%ebp)
	jmp	.L23
.L24:
	movl	$0, 16(%ebp)
	pushl	$1792
	.cfi_def_cfa_offset 24
	call	clear_screen
	popl	%eax
	.cfi_def_cfa_offset 20
.L23:
	movb	(%ebx), %al
	addl	$2, %esi
	incl	%ebx
	movb	%al, -2(%esi)
	jmp	.L19
.L33:
	decl	%edi
	jne	.L18
.L21:
	movl	16(%ebp), %eax
	movl	$0, 12(%ebp)
	incl	%eax
	cmpl	$24, %eax
	movl	%eax, 16(%ebp)
	jbe	.L18
	movl	$0, 16(%ebp)
	movl	$1792, 20(%esp)
	popl	%ebx
	.cfi_remember_state
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
	jmp	clear_screen
.L18:
	.cfi_restore_state
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
.LFE8:
	.size	GxH_strwrite, .-GxH_strwrite
	.globl	strcopy
	.type	strcopy, @function
strcopy:
.LFB14:
	.cfi_startproc
	movl	8(%esp), %edx
	movl	4(%esp), %eax
.L35:
	movb	(%edx), %cl
	testb	%cl, %cl
	je	.L37
	movb	%cl, (%eax)
	incl	%edx
	incl	%eax
	jmp	.L35
.L37:
	ret
	.cfi_endproc
.LFE14:
	.size	strcopy, .-strcopy
	.globl	vsprintfk
	.type	vsprintfk, @function
vsprintfk:
.LFB15:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	movl	12(%esp), %eax
	movl	16(%esp), %ebx
	movl	20(%esp), %esi
.L39:
	movb	(%ebx), %dl
	testb	%dl, %dl
	je	.L49
	cmpb	$37, %dl
	je	.L40
	movb	%dl, (%eax)
	incl	%ebx
	incl	%eax
	jmp	.L39
.L40:
	movb	1(%ebx), %dl
	cmpb	$115, %dl
	je	.L43
	cmpb	$120, %dl
	je	.L44
	cmpb	$100, %dl
	je	.L45
	incl	%ebx
	jmp	.L39
.L44:
	pushl	$16
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	jmp	.L48
.L45:
	.cfi_restore_state
	pushl	$10
	.cfi_def_cfa_offset 16
.L48:
	pushl	(%esi)
	.cfi_def_cfa_offset 20
	pushl	%eax
	.cfi_def_cfa_offset 24
	addl	$4, %esi
	addl	$2, %ebx
	call	numberk
	addl	$12, %esp
	.cfi_def_cfa_offset 12
	jmp	.L39
.L43:
	pushl	(%esi)
	.cfi_def_cfa_offset 16
	pushl	%eax
	.cfi_def_cfa_offset 20
	addl	$4, %esi
	addl	$2, %ebx
	call	strcopy
	popl	%edx
	.cfi_def_cfa_offset 16
	popl	%ecx
	.cfi_def_cfa_offset 12
	jmp	.L39
.L49:
	movb	$0, (%eax)
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE15:
	.size	vsprintfk, .-vsprintfk
	.globl	kprint
	.type	kprint, @function
kprint:
.LFB16:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.si
	addl	$_GLOBAL_OFFSET_TABLE_, %esi
	subl	$512, %esp
	.cfi_def_cfa_offset 524
	leal	528(%esp), %eax
	pushl	%eax
	.cfi_def_cfa_offset 528
	pushl	528(%esp)
	.cfi_def_cfa_offset 532
	leal	8(%esp), %ebx
	pushl	%ebx
	.cfi_def_cfa_offset 536
	call	vsprintfk
	leal	curs@GOTOFF(%esi), %eax
	pushl	%eax
	.cfi_def_cfa_offset 540
	pushl	%ebx
	.cfi_def_cfa_offset 544
	call	GxH_strwrite
	addl	$532, %esp
	.cfi_def_cfa_offset 12
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE16:
	.size	kprint, .-kprint
	.globl	curs
	.section	.data,"aw",@progbits
	.align 4
	.type	curs, @object
	.size	curs, 20
curs:
	.zero	20
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB18:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE18:
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB19:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE19:
	.section	.text.__x86.get_pc_thunk.si,"axG",@progbits,__x86.get_pc_thunk.si,comdat
	.globl	__x86.get_pc_thunk.si
	.hidden	__x86.get_pc_thunk.si
	.type	__x86.get_pc_thunk.si, @function
__x86.get_pc_thunk.si:
.LFB20:
	.cfi_startproc
	movl	(%esp), %esi
	ret
	.cfi_endproc
.LFE20:
	.section	.note.GNU-stack,"",@progbits
