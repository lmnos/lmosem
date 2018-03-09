	.file	"graph.c"
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
	.globl	write_pixcolor
	.type	write_pixcolor, @function
write_pixcolor:
.LFB7:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	movl	12(%esp), %esi
	movl	16(%esp), %eax
	movl	20(%esp), %edx
	movl	24(%esp), %ecx
	cmpl	$24, 372(%esi)
	movl	368(%esi), %ebx
	jne	.L14
	imull	360(%esi), %edx
	addl	%edx, %eax
	movl	%ecx, %edx
	leal	(%eax,%eax,2), %eax
	shrl	$8, %edx
	addl	%ebx, %eax
	movb	%cl, (%eax)
	shrl	$16, %ecx
	movb	%dl, 1(%eax)
	movb	%cl, 2(%eax)
	jmp	.L13
.L14:
	imull	360(%esi), %edx
	addl	%eax, %edx
	movl	%ecx, (%ebx,%edx,4)
.L13:
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE7:
	.size	write_pixcolor, .-write_pixcolor
	.globl	bmp_print
	.type	bmp_print, @function
bmp_print:
.LFB8:
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
	subl	$8, %esp
	.cfi_def_cfa_offset 28
	movl	28(%esp), %eax
	testl	%eax, %eax
	je	.L17
	imull	$24, 18(%eax), %ebx
	movl	10(%eax), %edx
	movl	$639, %esi
	addl	%eax, %edx
	addl	$31, %ebx
	sarl	$5, %ebx
	sall	$2, %ebx
.L19:
	movl	$639, %eax
	movl	%edx, %edi
	movl	$322, %ebp
	subl	%esi, %eax
	movl	%eax, (%esp)
.L22:
	movzbl	2(%edi), %ecx
	movzbl	1(%edi), %eax
	sall	$16, %ecx
	sall	$8, %eax
	orl	%eax, %ecx
	movzbl	(%edi), %eax
	orl	%ecx, %eax
	cmpl	$50, (%esp)
	jle	.L20
	cmpl	$10066328, %eax
	movl	$0, %ecx
	cmovg	%ecx, %eax
.L20:
	movl	%edx, 4(%esp)
	pushl	%eax
	.cfi_def_cfa_offset 32
	addl	$3, %edi
	pushl	%esi
	.cfi_def_cfa_offset 36
	pushl	%ebp
	.cfi_def_cfa_offset 40
	incl	%ebp
	pushl	44(%esp)
	.cfi_def_cfa_offset 44
	call	write_pixcolor
	addl	$16, %esp
	.cfi_def_cfa_offset 28
	cmpl	$662, %ebp
	movl	4(%esp), %edx
	jne	.L22
	decl	%esi
	addl	%ebx, %edx
	cmpl	$128, %esi
	jne	.L19
.L17:
	addl	$8, %esp
	.cfi_def_cfa_offset 20
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
	.size	bmp_print, .-bmp_print
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"LMOSEMLOGOX.bmp"
.LC1:
	.string	"if_getfilerpadrsz err"
	.text
	.globl	logo
	.type	logo, @function
logo:
.LFB9:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$20, %esp
	.cfi_def_cfa_offset 32
	leal	12(%esp), %eax
	movl	32(%esp), %esi
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	pushl	%eax
	.cfi_def_cfa_offset 36
	leal	12(%esp), %eax
	pushl	%eax
	.cfi_def_cfa_offset 40
	leal	.LC0@GOTOFF(%ebx), %eax
	pushl	%esi
	.cfi_def_cfa_offset 44
	pushl	%eax
	.cfi_def_cfa_offset 48
	call	get_file_rpadrandsz@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 32
	cmpl	$0, 8(%esp)
	jne	.L36
	leal	.LC1@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 44
	pushl	%eax
	.cfi_def_cfa_offset 48
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 32
.L36:
	pushl	%eax
	.cfi_def_cfa_offset 36
	pushl	%eax
	.cfi_def_cfa_offset 40
	pushl	%esi
	.cfi_def_cfa_offset 44
	pushl	20(%esp)
	.cfi_def_cfa_offset 48
	call	bmp_print
	addl	$36, %esp
	.cfi_def_cfa_offset 12
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE9:
	.size	logo, .-logo
	.globl	graph_t_init
	.type	graph_t_init, @function
graph_t_init:
.LFB11:
	.cfi_startproc
	movl	4(%esp), %edx
	xorl	%eax, %eax
.L39:
	movb	$0, (%edx,%eax)
	incl	%eax
	cmpl	$851, %eax
	jne	.L39
	ret
	.cfi_endproc
.LFE11:
	.size	graph_t_init, .-graph_t_init
	.globl	init_kinitfvram
	.type	init_kinitfvram, @function
init_kinitfvram:
.LFB12:
	.cfi_startproc
	movl	4(%esp), %eax
	movl	$8388608, 144(%eax)
	movl	$0, 148(%eax)
	movl	$4194304, 152(%eax)
	movl	$0, 156(%eax)
	xorl	%eax, %eax
.L42:
	movb	$0, 8388608(%eax)
	incl	%eax
	cmpl	$4194304, %eax
	jne	.L42
	ret
	.cfi_endproc
.LFE12:
	.size	init_kinitfvram, .-init_kinitfvram
	.globl	vfartolineadr
	.type	vfartolineadr, @function
vfartolineadr:
.LFB13:
	.cfi_startproc
	movl	4(%esp), %edx
	movl	%edx, %eax
	movzwl	%dx, %edx
	shrl	$16, %eax
	sall	$4, %eax
	addl	%edx, %eax
	ret
	.cfi_endproc
.LFE13:
	.size	vfartolineadr, .-vfartolineadr
	.section	.rodata.str1.1
.LC2:
	.string	"vbe is not VESA"
.LC3:
	.string	"vbe vbever:%x\n"
.LC4:
	.string	"vbe version not vbe3"
.LC5:
	.string	"getvbemode not 118"
	.text
	.globl	get_vbemode
	.type	get_vbemode, @function
get_vbemode:
.LFB14:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	xorl	%ecx, %ecx
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	xorl	%edx, %edx
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$12, %esp
	.cfi_def_cfa_offset 32
	movl	$4, %eax
	movl	32(%esp), %esi
	call	realadr_call_entry@PLT
	cmpb	$86, 24576
	jne	.L46
	cmpb	$69, 24577
	jne	.L46
	cmpb	$83, 24578
	jne	.L46
	cmpb	$65, 24579
	je	.L47
.L46:
	leal	.LC2@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 44
	pushl	%eax
	.cfi_def_cfa_offset 48
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 32
.L47:
	pushl	%eax
	.cfi_def_cfa_offset 36
	pushl	%eax
	.cfi_def_cfa_offset 40
	movzwl	24580, %eax
	pushl	%eax
	.cfi_def_cfa_offset 44
	leal	.LC3@GOTOFF(%ebx), %eax
	pushl	%eax
	.cfi_def_cfa_offset 48
	call	kprint@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 32
	cmpw	$511, 24580
	ja	.L48
	leal	.LC4@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 44
	pushl	%eax
	.cfi_def_cfa_offset 48
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 32
.L48:
	movl	24590, %eax
	cmpl	$65535, %eax
	jbe	.L50
	subl	$12, %esp
	.cfi_def_cfa_offset 44
	pushl	%eax
	.cfi_def_cfa_offset 48
	call	vfartolineadr
	addl	$16, %esp
	.cfi_def_cfa_offset 32
.L50:
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	movl	$1, %ebp
.L51:
	movw	(%eax,%edx,2), %di
	cmpw	$-1, %di
	je	.L53
	cmpw	$280, %di
	cmove	%ebp, %ecx
	cmpl	$4097, %edx
	je	.L53
	incl	%edx
	jmp	.L51
.L53:
	testl	%ecx, %ecx
	jne	.L55
	leal	.LC5@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 44
	pushl	%eax
	.cfi_def_cfa_offset 48
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 32
.L55:
	movl	$1, 356(%esi)
	movl	$280, 376(%esi)
	leal	440(%esi), %edx
	movl	$24576, 380(%esi)
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	movl	$512, %ecx
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
	movl	$24576, %eax
	jmp	m2mcopy
	.cfi_endproc
.LFE14:
	.size	get_vbemode, .-get_vbemode
	.globl	bga_write_reg
	.type	bga_write_reg, @function
bga_write_reg:
.LFB15:
	.cfi_startproc
	movl	$462, %edx
	movl	4(%esp), %eax
#APP
# 42 "../include/io.h" 1
	outw  %ax, %dx

# 0 "" 2
#NO_APP
	movl	$463, %edx
	movl	8(%esp), %eax
#APP
# 42 "../include/io.h" 1
	outw  %ax, %dx

# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE15:
	.size	bga_write_reg, .-bga_write_reg
	.globl	bga_read_reg
	.type	bga_read_reg, @function
bga_read_reg:
.LFB16:
	.cfi_startproc
	movl	$462, %edx
	movl	4(%esp), %eax
#APP
# 42 "../include/io.h" 1
	outw  %ax, %dx

# 0 "" 2
#NO_APP
	movl	$463, %edx
#APP
# 52 "../include/io.h" 1
	inw %dx, %ax

# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE16:
	.size	bga_read_reg, .-bga_read_reg
	.globl	get_bgadevice
	.type	get_bgadevice, @function
get_bgadevice:
.LFB17:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	pushl	$0
	.cfi_def_cfa_offset 16
	call	bga_read_reg
	movl	%eax, %ebx
	leal	20288(%ebx), %eax
	popl	%edx
	.cfi_def_cfa_offset 12
	cmpw	$5, %ax
	jbe	.L63
.L65:
	xorl	%eax, %eax
	jmp	.L62
.L63:
	movzwl	%bx, %esi
	pushl	%esi
	.cfi_def_cfa_offset 16
	pushl	$0
	.cfi_def_cfa_offset 20
	call	bga_write_reg
	pushl	$0
	.cfi_def_cfa_offset 24
	call	bga_read_reg
	addl	$12, %esp
	.cfi_def_cfa_offset 12
	cmpw	%ax, %bx
	jne	.L65
	movl	%esi, %eax
.L62:
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE17:
	.size	get_bgadevice, .-get_bgadevice
	.globl	chk_bgamaxver
	.type	chk_bgamaxver, @function
chk_bgamaxver:
.LFB18:
	.cfi_startproc
	pushl	$45253
	.cfi_def_cfa_offset 8
	pushl	$0
	.cfi_def_cfa_offset 12
	call	bga_write_reg
	pushl	$0
	.cfi_def_cfa_offset 16
	call	bga_read_reg
	addl	$12, %esp
	.cfi_def_cfa_offset 4
	cmpw	$-20283, %ax
	movl	$45253, %edx
	je	.L67
	pushl	$45252
	.cfi_def_cfa_offset 8
	pushl	$0
	.cfi_def_cfa_offset 12
	call	bga_write_reg
	pushl	$0
	.cfi_def_cfa_offset 16
	call	bga_read_reg
	addl	$12, %esp
	.cfi_def_cfa_offset 4
	cmpw	$-20284, %ax
	movl	$45252, %edx
	je	.L67
	pushl	$45251
	.cfi_def_cfa_offset 8
	pushl	$0
	.cfi_def_cfa_offset 12
	call	bga_write_reg
	pushl	$0
	.cfi_def_cfa_offset 16
	call	bga_read_reg
	addl	$12, %esp
	.cfi_def_cfa_offset 4
	cmpw	$-20285, %ax
	movl	$45251, %edx
	je	.L67
	pushl	$45250
	.cfi_def_cfa_offset 8
	pushl	$0
	.cfi_def_cfa_offset 12
	call	bga_write_reg
	pushl	$0
	.cfi_def_cfa_offset 16
	call	bga_read_reg
	addl	$12, %esp
	.cfi_def_cfa_offset 4
	cmpw	$-20286, %ax
	movl	$45250, %edx
	je	.L67
	pushl	$45249
	.cfi_def_cfa_offset 8
	pushl	$0
	.cfi_def_cfa_offset 12
	call	bga_write_reg
	pushl	$0
	.cfi_def_cfa_offset 16
	call	bga_read_reg
	addl	$12, %esp
	.cfi_def_cfa_offset 4
	cmpw	$-20287, %ax
	movl	$45249, %edx
	je	.L67
	pushl	$45248
	.cfi_def_cfa_offset 8
	pushl	$0
	.cfi_def_cfa_offset 12
	call	bga_write_reg
	pushl	$0
	.cfi_def_cfa_offset 16
	call	bga_read_reg
	addl	$12, %esp
	.cfi_def_cfa_offset 4
	movl	$45248, %edx
	cmpw	$-20288, %ax
	movl	$0, %eax
	cmovne	%eax, %edx
.L67:
	movl	%edx, %eax
	ret
	.cfi_endproc
.LFE18:
	.size	chk_bgamaxver, .-chk_bgamaxver
	.globl	init_bgadevice
	.type	init_bgadevice, @function
init_bgadevice:
.LFB19:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	movl	12(%esp), %esi
	call	get_bgadevice
	testl	%eax, %eax
	je	.L80
	call	chk_bgamaxver
	testl	%eax, %eax
	movl	%eax, %ebx
	je	.L80
	pushl	$0
	.cfi_def_cfa_offset 16
	pushl	$4
	.cfi_def_cfa_offset 20
	call	bga_write_reg
	pushl	$1024
	.cfi_def_cfa_offset 24
	pushl	$1
	.cfi_def_cfa_offset 28
	call	bga_write_reg
	pushl	$768
	.cfi_def_cfa_offset 32
	pushl	$2
	.cfi_def_cfa_offset 36
	call	bga_write_reg
	pushl	$32
	.cfi_def_cfa_offset 40
	pushl	$3
	.cfi_def_cfa_offset 44
	call	bga_write_reg
	addl	$32, %esp
	.cfi_def_cfa_offset 12
	pushl	$65
	.cfi_def_cfa_offset 16
	pushl	$4
	.cfi_def_cfa_offset 20
	call	bga_write_reg
	movl	$3, 356(%esi)
	movl	%ebx, 376(%esi)
	movl	$1024, 360(%esi)
	movl	$768, 364(%esi)
	movl	$-536870912, 368(%esi)
	movl	$32, 372(%esi)
	movl	$4, 388(%esi)
	movl	$0, 392(%esi)
	movl	$0, 396(%esi)
	movl	$4194304, 400(%esi)
	popl	%eax
	.cfi_def_cfa_offset 16
	popl	%edx
	.cfi_def_cfa_offset 12
.L80:
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE19:
	.size	init_bgadevice, .-init_bgadevice
	.globl	test_bga
	.type	test_bga, @function
test_bga:
.LFB20:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	movl	$-533725184, %eax
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$8, %esp
	.cfi_def_cfa_offset 16
.L89:
	movl	$16711935, (%eax)
	addl	$4, %eax
	cmpl	$-530579456, %eax
	jne	.L89
	movl	$-536870912, %edx
.L90:
	movl	$65280, (%edx)
	addl	$4, %edx
	cmpl	$-533725184, %edx
	jne	.L90
.L91:
	movl	$16711680, (%eax)
	addl	$4, %eax
	cmpl	$-527433728, %eax
	jne	.L91
.L92:
	pushl	$0
	.cfi_def_cfa_offset 20
	pushl	$8
	.cfi_def_cfa_offset 24
	call	bga_write_reg
	pushl	$0
	.cfi_def_cfa_offset 28
	pushl	$9
	.cfi_def_cfa_offset 32
	call	bga_write_reg
	pushl	$1024
	.cfi_def_cfa_offset 36
	pushl	$6
	.cfi_def_cfa_offset 40
	call	bga_write_reg
	pushl	$768
	.cfi_def_cfa_offset 44
	pushl	$7
	.cfi_def_cfa_offset 48
	call	bga_write_reg
	addl	$20, %esp
	.cfi_def_cfa_offset 28
	pushl	$1024
	.cfi_def_cfa_offset 32
	call	die@PLT
	popl	%eax
	.cfi_def_cfa_offset 28
	popl	%edx
	.cfi_def_cfa_offset 24
	pushl	$0
	.cfi_def_cfa_offset 28
	pushl	$8
	.cfi_def_cfa_offset 32
	call	bga_write_reg
	popl	%ecx
	.cfi_def_cfa_offset 28
	popl	%eax
	.cfi_def_cfa_offset 24
	pushl	$768
	.cfi_def_cfa_offset 28
	pushl	$9
	.cfi_def_cfa_offset 32
	call	bga_write_reg
	popl	%eax
	.cfi_def_cfa_offset 28
	popl	%edx
	.cfi_def_cfa_offset 24
	pushl	$1024
	.cfi_def_cfa_offset 28
	pushl	$6
	.cfi_def_cfa_offset 32
	call	bga_write_reg
	popl	%ecx
	.cfi_def_cfa_offset 28
	popl	%eax
	.cfi_def_cfa_offset 24
	pushl	$1536
	.cfi_def_cfa_offset 28
	pushl	$7
	.cfi_def_cfa_offset 32
	call	bga_write_reg
	movl	$1024, (%esp)
	call	die@PLT
	popl	%eax
	.cfi_def_cfa_offset 28
	popl	%edx
	.cfi_def_cfa_offset 24
	pushl	$0
	.cfi_def_cfa_offset 28
	pushl	$8
	.cfi_def_cfa_offset 32
	call	bga_write_reg
	popl	%ecx
	.cfi_def_cfa_offset 28
	popl	%eax
	.cfi_def_cfa_offset 24
	pushl	$1536
	.cfi_def_cfa_offset 28
	pushl	$9
	.cfi_def_cfa_offset 32
	call	bga_write_reg
	popl	%eax
	.cfi_def_cfa_offset 28
	popl	%edx
	.cfi_def_cfa_offset 24
	pushl	$1024
	.cfi_def_cfa_offset 28
	pushl	$6
	.cfi_def_cfa_offset 32
	call	bga_write_reg
	popl	%ecx
	.cfi_def_cfa_offset 28
	popl	%eax
	.cfi_def_cfa_offset 24
	pushl	$2304
	.cfi_def_cfa_offset 28
	pushl	$7
	.cfi_def_cfa_offset 32
	call	bga_write_reg
	movl	$1024, (%esp)
	call	die@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	jmp	.L92
	.cfi_endproc
.LFE20:
	.size	test_bga, .-test_bga
	.section	.rodata.str1.1
.LC6:
	.string	"vomif->BitsPerPixel!=32"
.LC7:
	.string	"xy not"
.LC8:
	.string	"phybass not"
	.text
	.globl	get_vbemodeinfo
	.type	get_vbemodeinfo, @function
get_vbemodeinfo:
.LFB21:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	xorl	%ecx, %ecx
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	xorl	%edx, %edx
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$28, %esp
	.cfi_def_cfa_offset 48
	movl	$6, %eax
	movl	48(%esp), %esi
	call	realadr_call_entry@PLT
	movl	25640, %eax
	movw	25618, %bp
	movl	25620, %edi
	movl	%eax, 12(%esp)
	cmpb	$23, 25625
	ja	.L98
	leal	.LC6@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	pushl	%eax
	.cfi_def_cfa_offset 64
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 48
.L98:
	cmpw	$1024, %bp
	jne	.L102
	cmpw	$768, %di
	je	.L99
.L102:
	leal	.LC7@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	pushl	%eax
	.cfi_def_cfa_offset 64
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 48
.L99:
	cmpl	$1048575, 12(%esp)
	ja	.L101
	leal	.LC8@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	pushl	%eax
	.cfi_def_cfa_offset 64
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 48
.L101:
	movzwl	25618, %eax
	leal	952(%esi), %edx
	movl	$255, %ecx
	movl	%eax, 360(%esi)
	movzwl	25620, %eax
	movl	%eax, 364(%esi)
	movl	25640, %eax
	movl	%eax, 368(%esi)
	movzbl	25625, %eax
	movl	$25600, 384(%esi)
	movl	%eax, 372(%esi)
	addl	$28, %esp
	.cfi_def_cfa_offset 20
	movl	$25600, %eax
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
	jmp	m2mcopy
	.cfi_endproc
.LFE21:
	.size	get_vbemodeinfo, .-get_vbemodeinfo
	.globl	set_vbemodeinfo
	.type	set_vbemodeinfo, @function
set_vbemodeinfo:
.LFB22:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$8, %esp
	.cfi_def_cfa_offset 16
	movl	$8, %eax
	call	realadr_call_entry@PLT
	addl	$8, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE22:
	.size	set_vbemodeinfo, .-set_vbemodeinfo
	.globl	init_graph
	.type	init_graph, @function
init_graph:
.LFB10:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	subl	$8, %esp
	.cfi_def_cfa_offset 16
	movl	16(%esp), %ebx
	leal	356(%ebx), %eax
	pushl	%eax
	.cfi_def_cfa_offset 20
	call	graph_t_init
	pushl	%ebx
	.cfi_def_cfa_offset 24
	call	init_bgadevice
	cmpl	$3, 356(%ebx)
	popl	%edx
	.cfi_def_cfa_offset 20
	popl	%ecx
	.cfi_def_cfa_offset 16
	je	.L110
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	%ebx
	.cfi_def_cfa_offset 32
	call	get_vbemode
	movl	%ebx, (%esp)
	call	get_vbemodeinfo
	call	set_vbemodeinfo
	addl	$16, %esp
	.cfi_def_cfa_offset 16
.L110:
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	%ebx
	.cfi_def_cfa_offset 32
	call	init_kinitfvram
	movl	%ebx, 32(%esp)
	addl	$24, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	jmp	logo
	.cfi_endproc
.LFE10:
	.size	init_graph, .-init_graph
	.globl	utf8_to_unicode
	.type	utf8_to_unicode, @function
utf8_to_unicode:
.LFB23:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	movl	8(%esp), %ecx
	movl	12(%esp), %edx
	movzbl	(%ecx), %eax
	testb	%al, %al
	js	.L113
	movl	$1, (%edx)
	jmp	.L112
.L113:
	leal	64(%eax), %ebx
	cmpb	$31, %bl
	ja	.L115
	movb	1(%ecx), %cl
	andl	$31, %eax
	movl	$2, (%edx)
	sall	$6, %eax
	andl	$63, %ecx
	orl	%ecx, %eax
	jmp	.L112
.L115:
	leal	32(%eax), %ebx
	cmpb	$15, %bl
	ja	.L116
	andl	$15, %eax
	sall	$6, %eax
	movl	%eax, %ebx
	movb	1(%ecx), %al
	movb	2(%ecx), %cl
	movl	$3, (%edx)
	andl	$63, %eax
	andl	$63, %ecx
	orl	%ebx, %eax
	sall	$6, %eax
	orl	%ecx, %eax
	jmp	.L112
.L116:
	leal	16(%eax), %ebx
	cmpb	$7, %bl
	ja	.L117
	movb	1(%ecx), %bl
	andl	$7, %eax
	sall	$6, %eax
	andl	$63, %ebx
	orl	%ebx, %eax
	sall	$6, %eax
	movl	%eax, %ebx
	movb	2(%ecx), %al
	movb	3(%ecx), %cl
	movl	$4, (%edx)
	andl	$63, %eax
	andl	$63, %ecx
	orl	%ebx, %eax
	sall	$6, %eax
	orl	%ecx, %eax
	jmp	.L112
.L117:
	leal	8(%eax), %ebx
	cmpb	$3, %bl
	ja	.L118
	movb	1(%ecx), %bl
	andl	$3, %eax
	sall	$6, %eax
	andl	$63, %ebx
	orl	%ebx, %eax
	sall	$6, %eax
	movl	%eax, %ebx
	movb	2(%ecx), %al
	andl	$63, %eax
	orl	%ebx, %eax
	sall	$6, %eax
	movl	%eax, %ebx
	movb	3(%ecx), %al
	movb	4(%ecx), %cl
	movl	$5, (%edx)
	andl	$63, %eax
	andl	$63, %ecx
	orl	%ebx, %eax
	sall	$6, %eax
	orl	%ecx, %eax
	jmp	.L112
.L118:
	leal	4(%eax), %ebx
	cmpb	$1, %bl
	ja	.L119
	movb	1(%ecx), %bl
	andl	$1, %eax
	sall	$6, %eax
	andl	$63, %ebx
	orl	%ebx, %eax
	movb	2(%ecx), %bl
	sall	$6, %eax
	andl	$63, %ebx
	orl	%eax, %ebx
	movb	3(%ecx), %al
	sall	$6, %ebx
	andl	$63, %eax
	orl	%ebx, %eax
	sall	$6, %eax
	movl	%eax, %ebx
	movb	4(%ecx), %al
	movb	5(%ecx), %cl
	movl	$6, (%edx)
	andl	$63, %eax
	andl	$63, %ecx
	orl	%ebx, %eax
	sall	$6, %eax
	orl	%ecx, %eax
	jmp	.L112
.L119:
	movl	$0, (%edx)
	xorl	%eax, %eax
.L112:
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE23:
	.size	utf8_to_unicode, .-utf8_to_unicode
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB29:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE29:
	.section	.note.GNU-stack,"",@progbits
