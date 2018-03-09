	.file	"bstartparm.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"s[%d]:%d\n"
.LC1:
	.string	"d[%d]:%d\n"
	.text
	.globl	testm2m
	.type	testm2m, @function
testm2m:
.LFB7:
	.cfi_startproc
	pushl	%edi
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	movl	$4194304, %eax
	pushl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
.L2:
	movb	%al, (%eax)
	incl	%eax
	cmpl	$4194314, %eax
	jne	.L2
	leal	.LC0@GOTOFF(%ebx), %edi
	xorl	%esi, %esi
.L3:
	pushl	%edx
	.cfi_def_cfa_offset 20
	movzbl	4194304(%esi), %eax
	pushl	%eax
	.cfi_def_cfa_offset 24
	pushl	%esi
	.cfi_def_cfa_offset 28
	incl	%esi
	pushl	%edi
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	cmpl	$10, %esi
	jne	.L3
	xorl	%eax, %eax
.L4:
	movb	4194304(%eax), %dl
	incl	%eax
	movb	%dl, 4194302(%eax)
	cmpl	$10, %eax
	jne	.L4
	leal	.LC1@GOTOFF(%ebx), %edi
	xorl	%esi, %esi
.L5:
	pushl	%eax
	.cfi_def_cfa_offset 20
	movzbl	4194303(%esi), %eax
	pushl	%eax
	.cfi_def_cfa_offset 24
	pushl	%esi
	.cfi_def_cfa_offset 28
	incl	%esi
	pushl	%edi
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	cmpl	$10, %esi
	jne	.L5
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	$0
	.cfi_def_cfa_offset 32
	call	die@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 12
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE7:
	.size	testm2m, .-testm2m
	.section	.rodata.str1.1
.LC2:
	.string	"mbsp->mb_lmosimgpadr:%x\n"
.LC3:
	.string	"mbsp->mb_lmosimgsz:%x\n"
.LC4:
	.string	"mbsp->mb_krlimgpadr:%x\n"
.LC5:
	.string	"mbsp->mb_krlimgsz:%x\n"
.LC6:
	.string	"mbsp->mb_e820padr:%x\n"
.LC7:
	.string	"mbsp->mb_e820nr:%x\n"
.LC8:
	.string	"mbsp->mb_e820sz:%x\n"
.LC9:
	.string	"mbsp->mb_nextwtpadr:%x\n"
.LC10:
	.string	"mbsp->mb_kalldendpadr:%x\n"
.LC11:
	.string	"mbsp->mb_pml4padr:%x\n"
.LC12:
	.string	"mbsp->mb_subpageslen:%x\n"
.LC13:
	.string	"mbsp->mb_kpmapphymemsz:%x\n"
.LC14:
	.string	"mbsp->mb_cpumode:%x\n"
.LC15:
	.string	"mbsp->mb_memsz:%x\n"
.LC16:
	.string	"mbsp->mb_krlinitstack:%x\n"
.LC17:
	.string	"mbsp->mb_krlitstacksz:%x\n"
.LC18:
	.string	"mbsp->mb_bfontpadr:%x\n"
.LC19:
	.string	"mbsp->mb_bfontsz:%x\n"
	.text
	.globl	disp_mbsp
	.type	disp_mbsp, @function
disp_mbsp:
.LFB8:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$8, %esp
	.cfi_def_cfa_offset 20
	movl	20(%esp), %esi
	leal	.LC2@GOTOFF(%ebx), %eax
	pushl	36(%esi)
	.cfi_def_cfa_offset 24
	pushl	32(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC3@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	44(%esi)
	.cfi_def_cfa_offset 24
	pushl	40(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC4@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	52(%esi)
	.cfi_def_cfa_offset 24
	pushl	48(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC5@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	60(%esi)
	.cfi_def_cfa_offset 24
	pushl	56(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC6@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	180(%esi)
	.cfi_def_cfa_offset 24
	pushl	176(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC7@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	188(%esi)
	.cfi_def_cfa_offset 24
	pushl	184(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC8@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	196(%esi)
	.cfi_def_cfa_offset 24
	pushl	192(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC9@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	124(%esi)
	.cfi_def_cfa_offset 24
	pushl	120(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC10@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	84(%esi)
	.cfi_def_cfa_offset 24
	pushl	80(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC11@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	292(%esi)
	.cfi_def_cfa_offset 24
	pushl	288(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC12@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	300(%esi)
	.cfi_def_cfa_offset 24
	pushl	296(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC13@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	308(%esi)
	.cfi_def_cfa_offset 24
	pushl	304(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC14@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	164(%esi)
	.cfi_def_cfa_offset 24
	pushl	160(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC15@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	172(%esi)
	.cfi_def_cfa_offset 24
	pushl	168(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC16@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	20(%esi)
	.cfi_def_cfa_offset 24
	pushl	16(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC17@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	28(%esi)
	.cfi_def_cfa_offset 24
	pushl	24(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC18@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	132(%esi)
	.cfi_def_cfa_offset 24
	pushl	128(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	leal	.LC19@GOTOFF(%ebx), %eax
	addl	$12, %esp
	.cfi_def_cfa_offset 20
	pushl	140(%esi)
	.cfi_def_cfa_offset 24
	pushl	136(%esi)
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
	movl	$0, (%esp)
	call	die@PLT
	addl	$20, %esp
	.cfi_def_cfa_offset 12
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE8:
	.size	disp_mbsp, .-disp_mbsp
	.globl	machbstart_t_init
	.type	machbstart_t_init, @function
machbstart_t_init:
.LFB10:
	.cfi_startproc
	movl	4(%esp), %edx
	xorl	%eax, %eax
.L15:
	movb	$0, (%edx,%eax)
	incl	%eax
	cmpl	$1207, %eax
	jne	.L15
	movl	$1296192336, (%edx)
	movl	$1280134995, 4(%edx)
	ret
	.cfi_endproc
.LFE10:
	.size	machbstart_t_init, .-machbstart_t_init
	.section	.rodata.str1.1
.LC20:
	.string	"lmosimgfilesz 0"
	.text
	.globl	init_bstartparm
	.type	init_bstartparm, @function
init_bstartparm:
.LFB9:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$8, %esp
	.cfi_def_cfa_offset 16
	pushl	$1048576
	.cfi_def_cfa_offset 20
	call	machbstart_t_init
	pushl	%edx
	.cfi_def_cfa_offset 24
	pushl	%edx
	.cfi_def_cfa_offset 28
	pushl	$1048576
	.cfi_def_cfa_offset 32
	call	init_chkcpu@PLT
	movl	$1048576, (%esp)
	call	init_mem@PLT
	movl	$1048576, (%esp)
	call	get_wt_lmosimgfilesz@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	orl	%eax, %edx
	jne	.L18
	leal	.LC20@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 16
.L18:
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	$1048576
	.cfi_def_cfa_offset 32
	call	init_krlinitstack@PLT
	movl	$1048576, (%esp)
	call	init_krlfile@PLT
	movl	$1048576, (%esp)
	call	init_defutfont@PLT
	movl	$1048576, (%esp)
	call	init_meme820@PLT
	movl	$1048576, (%esp)
	call	init_bstartpages@PLT
	movl	$1048576, (%esp)
	call	init_graph@PLT
	addl	$24, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE9:
	.size	init_bstartparm, .-init_bstartparm
	.globl	adrzone_is_ok
	.type	adrzone_is_ok, @function
adrzone_is_ok:
.LFB11:
	.cfi_startproc
	pushl	%edi
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	pushl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subl	$16, %esp
	.cfi_def_cfa_offset 32
	movl	44(%esp), %edx
	movl	36(%esp), %edi
	movl	40(%esp), %eax
	movl	56(%esp), %ecx
	movl	60(%esp), %ebx
	movl	32(%esp), %esi
	movl	%edx, 4(%esp)
	movl	52(%esp), %edx
	movl	%eax, (%esp)
	movl	%ecx, 8(%esp)
	movl	48(%esp), %eax
	movl	%ebx, 12(%esp)
	cmpl	%edi, %edx
	jb	.L21
	ja	.L30
	cmpl	%esi, %eax
	jb	.L21
.L30:
	movl	(%esp), %ecx
	movl	4(%esp), %ebx
	addl	%esi, %ecx
	adcl	%edi, %ebx
	cmpl	%ebx, %edx
	jb	.L27
	ja	.L31
	cmpl	%ecx, %eax
	jbe	.L27
.L31:
	cmpl	%edi, %edx
	ja	.L29
	jb	.L21
	cmpl	%esi, %eax
	ja	.L29
.L21:
	addl	8(%esp), %eax
	adcl	12(%esp), %edx
	cmpl	%edx, %edi
	ja	.L29
	jb	.L32
	cmpl	%eax, %esi
	ja	.L29
.L32:
	movl	$-2, %eax
	jmp	.L20
.L27:
	orl	$-1, %eax
	jmp	.L20
.L29:
	xorl	%eax, %eax
.L20:
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 12
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE11:
	.size	adrzone_is_ok, .-adrzone_is_ok
	.globl	chkadr_is_ok
	.type	chkadr_is_ok, @function
chkadr_is_ok:
.LFB12:
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
	subl	$12, %esp
	.cfi_def_cfa_offset 32
	movl	32(%esp), %ebp
	movl	44(%esp), %ebx
	movl	48(%esp), %esi
	movl	40(%esp), %edx
	movl	36(%esp), %eax
	movl	16(%ebp), %ecx
	movl	%ebx, (%esp)
	movl	20(%ebp), %ebx
	movl	%esi, 4(%esp)
	movl	%ecx, %esi
	subl	24(%ebp), %esi
	movl	%ebx, %edi
	sbbl	28(%ebp), %edi
	cmpl	%edx, %edi
	jb	.L110
	ja	.L100
	cmpl	%eax, %esi
	ja	.L100
.L110:
	cmpl	%edx, %ebx
	ja	.L86
	jb	.L100
	cmpl	%eax, %ecx
	jnb	.L86
.L100:
	cmpl	%edx, %edi
	jb	.L41
	ja	.L101
	cmpl	%eax, %esi
	jb	.L41
.L101:
	movl	(%esp), %ecx
	movl	4(%esp), %ebx
	addl	%eax, %ecx
	adcl	%edx, %ebx
	cmpl	%ebx, %edi
	jb	.L86
	ja	.L41
	cmpl	%ecx, %esi
	ja	.L41
.L86:
	orl	$-1, %eax
	jmp	.L34
.L41:
	movl	36(%ebp), %ebx
	movl	40(%ebp), %esi
	movl	44(%ebp), %edi
	movl	32(%ebp), %ecx
	cmpl	%ebx, %edx
	jbe	.L118
.L67:
	addl	%ecx, %esi
	adcl	%ebx, %edi
	cmpl	%edi, %edx
	jb	.L88
	ja	.L102
	cmpl	%esi, %eax
	jbe	.L88
.L102:
	cmpl	%ebx, %edx
	ja	.L45
	jb	.L69
	cmpl	%ecx, %eax
	ja	.L45
.L69:
	movl	(%esp), %esi
	movl	4(%esp), %edi
	addl	%eax, %esi
	adcl	%edx, %edi
	cmpl	%edi, %ebx
	jb	.L88
	ja	.L45
	cmpl	%esi, %ecx
	ja	.L45
.L88:
	movl	$-2, %eax
	jmp	.L34
.L118:
	jb	.L69
	cmpl	%ecx, %eax
	jnb	.L67
	jmp	.L69
.L45:
	movl	52(%ebp), %ebx
	movl	56(%ebp), %esi
	movl	60(%ebp), %edi
	movl	48(%ebp), %ecx
	cmpl	%ebx, %edx
	jbe	.L119
.L70:
	addl	%ecx, %esi
	adcl	%ebx, %edi
	cmpl	%edi, %edx
	jb	.L90
	ja	.L103
	cmpl	%esi, %eax
	jbe	.L90
.L103:
	cmpl	%ebx, %edx
	ja	.L49
	jb	.L72
	cmpl	%ecx, %eax
	ja	.L49
.L72:
	movl	(%esp), %esi
	movl	4(%esp), %edi
	addl	%eax, %esi
	adcl	%edx, %edi
	cmpl	%edi, %ebx
	jb	.L90
	ja	.L49
	cmpl	%esi, %ecx
	ja	.L49
.L90:
	movl	$-3, %eax
	jmp	.L34
.L119:
	jb	.L72
	cmpl	%ecx, %eax
	jnb	.L70
	jmp	.L72
.L49:
	movl	132(%ebp), %ebx
	movl	136(%ebp), %esi
	movl	140(%ebp), %edi
	movl	128(%ebp), %ecx
	cmpl	%ebx, %edx
	jbe	.L120
.L73:
	addl	%ecx, %esi
	adcl	%ebx, %edi
	cmpl	%edi, %edx
	jb	.L92
	ja	.L104
	cmpl	%esi, %eax
	jbe	.L92
.L104:
	cmpl	%ebx, %edx
	ja	.L53
	jb	.L75
	cmpl	%ecx, %eax
	ja	.L53
.L75:
	movl	(%esp), %esi
	movl	4(%esp), %edi
	addl	%eax, %esi
	adcl	%edx, %edi
	cmpl	%edi, %ebx
	jb	.L92
	ja	.L53
	cmpl	%esi, %ecx
	ja	.L53
.L92:
	movl	$-4, %eax
	jmp	.L34
.L120:
	jb	.L75
	cmpl	%ecx, %eax
	jnb	.L73
	jmp	.L75
.L53:
	movl	180(%ebp), %ebx
	movl	192(%ebp), %esi
	movl	196(%ebp), %edi
	movl	176(%ebp), %ecx
	cmpl	%ebx, %edx
	jbe	.L121
.L76:
	addl	%ecx, %esi
	adcl	%ebx, %edi
	cmpl	%edi, %edx
	jb	.L94
	ja	.L105
	cmpl	%esi, %eax
	jbe	.L94
.L105:
	cmpl	%ebx, %edx
	ja	.L57
	jb	.L78
	cmpl	%ecx, %eax
	ja	.L57
.L78:
	movl	(%esp), %esi
	movl	4(%esp), %edi
	addl	%eax, %esi
	adcl	%edx, %edi
	cmpl	%edi, %ebx
	jb	.L94
	ja	.L57
	cmpl	%esi, %ecx
	ja	.L57
.L94:
	movl	$-5, %eax
	jmp	.L34
.L121:
	jb	.L78
	cmpl	%ecx, %eax
	jnb	.L76
	jmp	.L78
.L57:
	movl	228(%ebp), %ebx
	movl	240(%ebp), %esi
	movl	244(%ebp), %edi
	movl	224(%ebp), %ecx
	cmpl	%ebx, %edx
	jbe	.L122
.L79:
	addl	%ecx, %esi
	adcl	%ebx, %edi
	cmpl	%edi, %edx
	jb	.L96
	ja	.L106
	cmpl	%esi, %eax
	jbe	.L96
.L106:
	cmpl	%ebx, %edx
	ja	.L61
	jb	.L81
	cmpl	%ecx, %eax
	ja	.L61
.L81:
	movl	(%esp), %esi
	movl	4(%esp), %edi
	addl	%eax, %esi
	adcl	%edx, %edi
	cmpl	%edi, %ebx
	jb	.L96
	ja	.L61
	cmpl	%esi, %ecx
	ja	.L61
.L96:
	movl	$-6, %eax
	jmp	.L34
.L122:
	jb	.L81
	cmpl	%ecx, %eax
	jnb	.L79
	jmp	.L81
.L61:
	movl	260(%ebp), %edi
	movl	272(%ebp), %ecx
	movl	276(%ebp), %ebx
	movl	256(%ebp), %esi
	cmpl	%edi, %edx
	jbe	.L123
.L82:
	addl	%esi, %ecx
	adcl	%edi, %ebx
	cmpl	%ebx, %edx
	jb	.L97
	ja	.L107
	cmpl	%ecx, %eax
	jbe	.L97
.L107:
	cmpl	%edi, %edx
	ja	.L99
	jb	.L84
	cmpl	%esi, %eax
	ja	.L99
.L84:
	addl	(%esp), %eax
	adcl	4(%esp), %edx
	cmpl	%edx, %edi
	ja	.L99
	jb	.L97
	cmpl	%eax, %esi
	ja	.L99
.L97:
	movl	$-7, %eax
	jmp	.L34
.L99:
	xorl	%eax, %eax
	jmp	.L34
.L123:
	jb	.L84
	cmpl	%esi, %eax
	jnb	.L82
	jmp	.L84
.L34:
	addl	$12, %esp
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
.LFE12:
	.size	chkadr_is_ok, .-chkadr_is_ok
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB15:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE15:
	.section	.note.GNU-stack,"",@progbits
