	.file	"fs.c"
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
	.globl	fs_entry
	.type	fs_entry, @function
fs_entry:
.LFB7:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE7:
	.size	fs_entry, .-fs_entry
	.globl	strcmpl
	.type	strcmpl, @function
strcmpl:
.LFB8:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	movl	8(%esp), %edx
	movl	12(%esp), %ecx
.L15:
	movsbl	(%ecx), %eax
	testb	%al, %al
	je	.L16
	movb	(%edx), %bl
	cmpb	%bl, %al
	jne	.L16
	testb	%bl, %bl
	je	.L16
	incl	%ecx
	incl	%edx
	jmp	.L15
.L16:
	movsbl	(%edx), %edx
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	subl	%edx, %eax
	ret
	.cfi_endproc
.LFE8:
	.size	strcmpl, .-strcmpl
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"no mrddsc"
.LC1:
	.string	"not find file"
	.text
	.globl	get_fileinfo
	.type	get_fileinfo, @function
get_fileinfo:
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
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$28, %esp
	.cfi_def_cfa_offset 48
	movl	52(%esp), %esi
	movl	32(%esi), %eax
	leal	4096(%eax), %edi
	cmpl	$-1426085121, 164(%edi)
	jne	.L27
	cmpl	$-1426085121, 160(%edi)
	jne	.L27
	cmpl	$-5570646, 172(%edi)
	jne	.L27
	cmpl	$-5570646, 168(%edi)
	jne	.L27
	cmpl	$0, 148(%edi)
	ja	.L39
	cmpl	$1, 144(%edi)
	jbe	.L27
.L39:
	cmpl	$0, 156(%edi)
	ja	.L31
	cmpl	$1, 152(%edi)
	ja	.L31
.L27:
	leal	.LC0@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	pushl	%eax
	.cfi_def_cfa_offset 64
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 48
.L31:
	movl	144(%edi), %eax
	movl	32(%esi), %esi
	addl	72(%edi), %esi
	movl	$0, (%esp)
	movl	$0, 4(%esp)
	movl	%eax, %ebp
	movl	148(%edi), %eax
	leal	64(%esi), %edx
	movl	%eax, %edi
.L33:
	cmpl	%edi, 4(%esp)
	je	.L41
.L37:
	pushl	%eax
	.cfi_def_cfa_offset 52
	pushl	%eax
	.cfi_def_cfa_offset 56
	pushl	%edx
	.cfi_def_cfa_offset 60
	movl	%edx, 24(%esp)
	pushl	60(%esp)
	.cfi_def_cfa_offset 64
	call	strcmpl
	addl	$16, %esp
	.cfi_def_cfa_offset 48
	movl	12(%esp), %edx
	addl	$256, %edx
	testl	%eax, %eax
	jne	.L34
	movl	4(%esp), %eax
	movl	(%esp), %edi
	testl	%eax, %eax
	jns	.L36
	jmp	.L35
.L34:
	addl	$1, (%esp)
	adcl	$0, 4(%esp)
	jmp	.L33
.L41:
	cmpl	%ebp, (%esp)
	jne	.L37
	orl	$-1, %edi
.L35:
	leal	.LC1@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	pushl	%eax
	.cfi_def_cfa_offset 64
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 48
.L36:
	addl	$28, %esp
	.cfi_def_cfa_offset 20
	sall	$8, %edi
	leal	(%esi,%edi), %eax
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
	.size	get_fileinfo, .-get_fileinfo
	.globl	move_krlimg
	.type	move_krlimg, @function
move_krlimg:
.LFB10:
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
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$28, %esp
	.cfi_def_cfa_offset 48
	movl	60(%esp), %eax
	movl	52(%esp), %edi
	movl	64(%esp), %edx
	movl	56(%esp), %ebp
	movl	48(%esp), %esi
	movl	%eax, (%esp)
	addl	%edi, %eax
	movl	%edx, 4(%esp)
	adcl	%ebp, %edx
	cmpl	$0, %edx
	ja	.L46
	cmpl	$-2, %eax
	ja	.L46
	movl	(%esp), %eax
	orl	4(%esp), %eax
	je	.L46
	movl	40(%esi), %eax
	movl	44(%esi), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	pushl	4(%esp)
	.cfi_def_cfa_offset 52
	pushl	4(%esp)
	.cfi_def_cfa_offset 56
	pushl	%ebp
	.cfi_def_cfa_offset 60
	pushl	%edi
	.cfi_def_cfa_offset 64
	pushl	28(%esp)
	.cfi_def_cfa_offset 68
	pushl	28(%esp)
	.cfi_def_cfa_offset 72
	pushl	36(%esi)
	.cfi_def_cfa_offset 76
	pushl	32(%esi)
	.cfi_def_cfa_offset 80
	call	adrzone_is_ok@PLT
	addl	$32, %esp
	.cfi_def_cfa_offset 48
	testl	%eax, %eax
	movl	$2, %ecx
	je	.L42
	movl	(%esp), %edx
	movl	8(%esp), %ecx
	xorl	%ebp, %ebp
	addl	$4095, %edx
	addl	%edi, %edx
	andl	$-4096, %edx
	movl	%edx, (%esp)
	movl	(%esp), %edi
	pushl	%eax
	.cfi_def_cfa_offset 52
	pushl	%eax
	.cfi_def_cfa_offset 56
	movl	%ecx, %eax
	cltd
	pushl	%edx
	.cfi_def_cfa_offset 60
	pushl	%ecx
	.cfi_def_cfa_offset 64
	pushl	%ebp
	.cfi_def_cfa_offset 68
	pushl	%edi
	.cfi_def_cfa_offset 72
	pushl	184(%esi)
	.cfi_def_cfa_offset 76
	pushl	176(%esi)
	.cfi_def_cfa_offset 80
	call	chk_memsize@PLT
	addl	$32, %esp
	.cfi_def_cfa_offset 48
	orl	$-1, %ecx
	testl	%eax, %eax
	je	.L42
	movl	8(%esp), %ecx
	movl	32(%esi), %eax
	movl	(%esp), %edx
	call	m2mcopy
	movl	%edi, 32(%esi)
	movl	%ebp, 36(%esi)
	movl	$1, %ecx
	jmp	.L42
.L46:
	xorl	%ecx, %ecx
.L42:
	addl	$28, %esp
	.cfi_def_cfa_offset 20
	movl	%ecx, %eax
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
.LFE10:
	.size	move_krlimg, .-move_krlimg
	.globl	get_file_rpadrandsz
	.type	get_file_rpadrandsz, @function
get_file_rpadrandsz:
.LFB13:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	pushl	%ecx
	.cfi_def_cfa_offset 16
	movl	16(%esp), %eax
	movl	20(%esp), %ebx
	movl	24(%esp), %esi
	testl	%eax, %eax
	je	.L57
	testl	%ebx, %ebx
	jne	.L54
.L57:
	movl	$0, (%esi)
	jmp	.L53
.L54:
	pushl	%edx
	.cfi_def_cfa_offset 20
	pushl	%edx
	.cfi_def_cfa_offset 24
	pushl	%ebx
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	get_fileinfo
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	testl	%eax, %eax
	je	.L57
	movl	32(%ebx), %ecx
	addl	32(%eax), %ecx
	movl	36(%ebx), %ebx
	adcl	36(%eax), %ebx
	cmpl	$0, %ebx
	ja	.L57
	movl	48(%eax), %edx
	movl	28(%esp), %eax
	movl	%ecx, (%esi)
	movl	%edx, (%eax)
.L53:
	popl	%eax
	.cfi_def_cfa_offset 12
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE13:
	.size	get_file_rpadrandsz, .-get_file_rpadrandsz
	.section	.rodata.str1.1
.LC2:
	.string	"lmos.fnt"
.LC3:
	.string	"if_getfilerpadrsz err"
.LC4:
	.string	"if_moveimg err"
	.text
	.globl	init_defutfont
	.type	init_defutfont, @function
init_defutfont:
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
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$28, %esp
	.cfi_def_cfa_offset 48
	movl	48(%esp), %esi
	leal	12(%esp), %eax
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	movl	120(%esi), %edi
	pushl	%eax
	.cfi_def_cfa_offset 52
	leal	12(%esp), %eax
	pushl	%eax
	.cfi_def_cfa_offset 56
	leal	.LC2@GOTOFF(%ebx), %eax
	pushl	%esi
	.cfi_def_cfa_offset 60
	pushl	%eax
	.cfi_def_cfa_offset 64
	call	get_file_rpadrandsz
	addl	$16, %esp
	.cfi_def_cfa_offset 48
	cmpl	$0, 8(%esp)
	jne	.L63
	leal	.LC3@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	pushl	%eax
	.cfi_def_cfa_offset 64
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 48
.L63:
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	xorl	%edx, %edx
	movl	24(%esp), %eax
	pushl	%edx
	.cfi_def_cfa_offset 64
	pushl	%eax
	.cfi_def_cfa_offset 68
	pushl	124(%esi)
	.cfi_def_cfa_offset 72
	pushl	120(%esi)
	.cfi_def_cfa_offset 76
	pushl	%esi
	.cfi_def_cfa_offset 80
	call	move_krlimg
	addl	$32, %esp
	.cfi_def_cfa_offset 48
	testl	%eax, %eax
	jg	.L64
	leal	.LC4@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	pushl	%eax
	.cfi_def_cfa_offset 64
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 48
.L64:
	movl	12(%esp), %ecx
	movl	8(%esp), %eax
	movl	%edi, %edx
	xorl	%ebx, %ebx
	call	m2mcopy
	movl	12(%esp), %ebp
	movl	%edi, 128(%esi)
	movl	%edi, %ecx
	xorl	%edx, %edx
	movl	%ebx, 132(%esi)
	movl	$0, 124(%esi)
	movl	%edx, 140(%esi)
	leal	4095(%ebp,%edi), %edi
	movl	%ebp, %eax
	movl	%ebp, 136(%esi)
	andl	$-4096, %edi
	addl	%ecx, %eax
	adcl	%ebx, %edx
	movl	%edi, 120(%esi)
	movl	%eax, 80(%esi)
	movl	%edx, 84(%esi)
	addl	$28, %esp
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
	.size	init_defutfont, .-init_defutfont
	.globl	get_filesz
	.type	get_filesz, @function
get_filesz:
.LFB14:
	.cfi_startproc
	subl	$12, %esp
	.cfi_def_cfa_offset 16
	movl	16(%esp), %eax
	movl	20(%esp), %edx
	testl	%eax, %eax
	je	.L70
	testl	%edx, %edx
	jne	.L67
.L70:
	xorl	%eax, %eax
	xorl	%edx, %edx
	jmp	.L66
.L67:
	pushl	%ecx
	.cfi_def_cfa_offset 20
	pushl	%ecx
	.cfi_def_cfa_offset 24
	pushl	%edx
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	get_fileinfo
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	testl	%eax, %eax
	je	.L70
	movl	52(%eax), %edx
	movl	48(%eax), %eax
.L66:
	addl	$12, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE14:
	.size	get_filesz, .-get_filesz
	.globl	get_wt_lmosimgfilesz
	.type	get_wt_lmosimgfilesz, @function
get_wt_lmosimgfilesz:
.LFB15:
	.cfi_startproc
	cmpl	$-1426085121, 67113124
	movl	4(%esp), %ecx
	jne	.L86
	cmpl	$-1426085121, 67113120
	jne	.L86
	cmpl	$-5570646, 67113132
	jne	.L86
	cmpl	$-5570646, 67113128
	jne	.L86
	cmpl	$0, 67113108
	ja	.L87
	cmpl	$1, 67113104
	jbe	.L86
.L87:
	cmpl	$0, 67113116
	ja	.L88
	cmpl	$1, 67113112
	jbe	.L86
.L88:
	movl	67113076, %edx
	movl	67113072, %eax
	cmpl	$0, %edx
	ja	.L89
	cmpl	$16383, %eax
	jbe	.L86
.L89:
	movl	$67108864, 32(%ecx)
	movl	$0, 36(%ecx)
	movl	%eax, 40(%ecx)
	movl	%edx, 44(%ecx)
	ret
.L86:
	xorl	%eax, %eax
	xorl	%edx, %edx
	ret
	.cfi_endproc
.LFE15:
	.size	get_wt_lmosimgfilesz, .-get_wt_lmosimgfilesz
	.globl	r_file_to_padr
	.type	r_file_to_padr, @function
r_file_to_padr:
.LFB16:
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
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$28, %esp
	.cfi_def_cfa_offset 48
	movl	56(%esp), %ecx
	movl	48(%esp), %ebp
	testl	%ecx, %ecx
	sete	%dl
	testl	%ebp, %ebp
	sete	%al
	orb	%al, %dl
	jne	.L95
	cmpl	$0, 52(%esp)
	je	.L95
	leal	12(%esp), %eax
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	pushl	%eax
	.cfi_def_cfa_offset 52
	leal	12(%esp), %eax
	pushl	%eax
	.cfi_def_cfa_offset 56
	pushl	%ebp
	.cfi_def_cfa_offset 60
	pushl	%ecx
	.cfi_def_cfa_offset 64
	call	get_file_rpadrandsz
	addl	$16, %esp
	.cfi_def_cfa_offset 48
	cmpl	$0, 8(%esp)
	je	.L95
	movl	12(%esp), %eax
	testl	%eax, %eax
	je	.L95
	movl	52(%esp), %esi
	xorl	%edi, %edi
	pushl	%edx
	.cfi_def_cfa_offset 52
	pushl	%edx
	.cfi_def_cfa_offset 56
	xorl	%edx, %edx
	pushl	%edx
	.cfi_def_cfa_offset 60
	pushl	%eax
	.cfi_def_cfa_offset 64
	pushl	%edi
	.cfi_def_cfa_offset 68
	pushl	%esi
	.cfi_def_cfa_offset 72
	pushl	184(%ebp)
	.cfi_def_cfa_offset 76
	pushl	176(%ebp)
	.cfi_def_cfa_offset 80
	call	chk_memsize@PLT
	addl	$32, %esp
	.cfi_def_cfa_offset 48
	testl	%eax, %eax
	je	.L95
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	xorl	%edx, %edx
	movl	24(%esp), %eax
	pushl	%edx
	.cfi_def_cfa_offset 64
	pushl	%eax
	.cfi_def_cfa_offset 68
	pushl	%edi
	.cfi_def_cfa_offset 72
	pushl	%esi
	.cfi_def_cfa_offset 76
	pushl	%ebp
	.cfi_def_cfa_offset 80
	call	chkadr_is_ok@PLT
	addl	$32, %esp
	.cfi_def_cfa_offset 48
	testl	%eax, %eax
	jne	.L95
	movl	12(%esp), %ecx
	movl	52(%esp), %edx
	movl	8(%esp), %eax
	call	m2mcopy
	movl	12(%esp), %eax
	jmp	.L103
.L95:
	xorl	%eax, %eax
.L103:
	addl	$28, %esp
	.cfi_def_cfa_offset 20
	xorl	%edx, %edx
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
.LFE16:
	.size	r_file_to_padr, .-r_file_to_padr
	.section	.rodata.str1.1
.LC5:
	.string	"lmosemkrnl.bin"
.LC6:
	.string	"ik_rfilepadr err"
	.text
	.globl	init_krlfile
	.type	init_krlfile, @function
init_krlfile:
.LFB11:
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
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$32, %esp
	.cfi_def_cfa_offset 52
	movl	52(%esp), %esi
	leal	.LC5@GOTOFF(%ebx), %eax
	pushl	%eax
	.cfi_def_cfa_offset 56
	pushl	$33554432
	.cfi_def_cfa_offset 60
	pushl	%esi
	.cfi_def_cfa_offset 64
	call	r_file_to_padr
	movl	%edx, %ecx
	addl	$16, %esp
	.cfi_def_cfa_offset 48
	orl	%eax, %ecx
	jne	.L105
	leal	.LC6@GOTOFF(%ebx), %ecx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	pushl	%ecx
	.cfi_def_cfa_offset 64
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 48
	movl	8(%esp), %eax
	movl	12(%esp), %edx
.L105:
	movl	%eax, %ecx
	movl	%edx, %ebx
	movl	%eax, 56(%esi)
	addl	$33558527, %ecx
	movl	%edx, 60(%esi)
	movl	$33554432, 48(%esi)
	adcl	$0, %ebx
	andl	$-4096, %ecx
	addl	$33554432, %eax
	adcl	$0, %edx
	movl	$0, 52(%esi)
	movl	%ecx, 120(%esi)
	movl	%ebx, 124(%esi)
	movl	%eax, 80(%esi)
	movl	%edx, 84(%esi)
	addl	$28, %esp
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
.LFE11:
	.size	init_krlfile, .-init_krlfile
	.globl	set_rwhdhdpack
	.type	set_rwhdhdpack, @function
set_rwhdhdpack:
.LFB17:
	.cfi_startproc
	movl	4(%esp), %eax
	movb	$16, (%eax)
	movb	$0, 1(%eax)
	movl	8(%esp), %edx
	movb	$0, 3(%eax)
	movb	%dl, 2(%eax)
	movl	12(%esp), %edx
	movw	%dx, 4(%eax)
	movl	16(%esp), %edx
	movw	%dx, 6(%eax)
	movl	20(%esp), %edx
	movl	%edx, 8(%eax)
	movl	24(%esp), %edx
	movl	%edx, 12(%eax)
	ret
	.cfi_endproc
.LFE17:
	.size	set_rwhdhdpack, .-set_rwhdhdpack
	.globl	read_sector
	.type	read_sector, @function
read_sector:
.LFB18:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	xorl	%ecx, %ecx
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$8, %esp
	.cfi_def_cfa_offset 16
	movl	16(%esp), %edx
	movl	20(%esp), %eax
	movb	$16, 8224
	movb	$0, 8225
	movb	$1, 8226
	movb	$0, 8227
	movl	%edx, 8232
	movl	%eax, 8236
	xorl	%edx, %edx
	movl	$2, %eax
	movw	$12288, 8228
	movw	$0, 8230
	call	realadr_call_entry@PLT
	addl	$8, %esp
	.cfi_def_cfa_offset 8
	movl	$12288, %eax
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE18:
	.size	read_sector, .-read_sector
	.globl	is_part
	.type	is_part, @function
is_part:
.LFB20:
	.cfi_startproc
	movl	4(%esp), %edx
	xorl	%eax, %eax
	cmpb	$0, 4(%edx)
	je	.L110
	cmpl	$0, 8(%edx)
	je	.L110
	xorl	%eax, %eax
	cmpl	$0, 12(%edx)
	setne	%al
.L110:
	ret
	.cfi_endproc
.LFE20:
	.size	is_part, .-is_part
	.section	.rodata.str1.1
.LC7:
	.string	"extpartition(%x): boot:%x type:%x startsector:%d sectorlen:%d\n"
.LC8:
	.string	"partition(%x): boot:%x type:%x startsector:%d sectorlen:%d\n"
	.text
	.globl	ret_mbr
	.type	ret_mbr, @function
ret_mbr:
.LFB19:
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
	xorl	%esi, %esi
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$52, %esp
	.cfi_def_cfa_offset 72
	pushl	$0
	.cfi_def_cfa_offset 76
	pushl	$0
	.cfi_def_cfa_offset 80
	call	read_sector
	leal	.LC7@GOTOFF(%ebx), %edx
	addl	$16, %esp
	.cfi_def_cfa_offset 64
	movl	$0, 24(%esp)
	movl	$0, 16(%esp)
	movl	$0, 20(%esp)
	movl	%edx, 28(%esp)
.L115:
	leal	446(%eax), %ebp
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
.L120:
	movb	4(%ebp), %al
	cmpb	$5, %al
	movb	%al, 7(%esp)
	je	.L122
	cmpb	$15, %al
	jne	.L116
.L122:
	xorl	%edi, %edi
	cmpl	$0, 24(%esp)
	movl	8(%ebp), %eax
	movl	%eax, %esi
	jne	.L118
	movl	%edi, 20(%esp)
	movl	%eax, 16(%esp)
	xorl	%esi, %esi
	xorl	%edi, %edi
.L118:
	addl	16(%esp), %esi
	adcl	20(%esp), %edi
	pushl	%ecx
	.cfi_def_cfa_offset 68
	pushl	%ecx
	.cfi_def_cfa_offset 72
	pushl	12(%ebp)
	.cfi_def_cfa_offset 76
	pushl	%eax
	.cfi_def_cfa_offset 80
	movzbl	23(%esp), %ecx
	pushl	%ecx
	.cfi_def_cfa_offset 84
	movzbl	0(%ebp), %eax
	pushl	%eax
	.cfi_def_cfa_offset 88
	pushl	32(%esp)
	.cfi_def_cfa_offset 92
	pushl	56(%esp)
	.cfi_def_cfa_offset 96
	call	kprint@PLT
	addl	$32, %esp
	.cfi_def_cfa_offset 64
	movl	$1, 24(%esp)
	movl	$1, 12(%esp)
	jmp	.L119
.L116:
	subl	$12, %esp
	.cfi_def_cfa_offset 76
	pushl	%ebp
	.cfi_def_cfa_offset 80
	call	is_part
	addl	$16, %esp
	.cfi_def_cfa_offset 64
	testl	%eax, %eax
	je	.L119
	pushl	%edx
	.cfi_def_cfa_offset 68
	pushl	%edx
	.cfi_def_cfa_offset 72
	pushl	12(%ebp)
	.cfi_def_cfa_offset 76
	pushl	8(%ebp)
	.cfi_def_cfa_offset 80
	movzbl	23(%esp), %ecx
	pushl	%ecx
	.cfi_def_cfa_offset 84
	movzbl	0(%ebp), %eax
	pushl	%eax
	.cfi_def_cfa_offset 88
	leal	.LC8@GOTOFF(%ebx), %eax
	pushl	32(%esp)
	.cfi_def_cfa_offset 92
	pushl	%eax
	.cfi_def_cfa_offset 96
	call	kprint@PLT
	addl	$32, %esp
	.cfi_def_cfa_offset 64
.L119:
	incl	8(%esp)
	addl	$16, %ebp
	cmpl	$4, 8(%esp)
	jne	.L120
	cmpl	$0, 12(%esp)
	je	.L114
	pushl	%eax
	.cfi_def_cfa_offset 68
	pushl	%eax
	.cfi_def_cfa_offset 72
	pushl	%edi
	.cfi_def_cfa_offset 76
	pushl	%esi
	.cfi_def_cfa_offset 80
	call	read_sector
	addl	$16, %esp
	.cfi_def_cfa_offset 64
	jmp	.L115
.L114:
	addl	$44, %esp
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
.LFE19:
	.size	ret_mbr, .-ret_mbr
	.section	.rodata.str1.1
.LC9:
	.string	"imgfile error"
	.text
	.globl	ret_imgfilesz
	.type	ret_imgfilesz, @function
ret_imgfilesz:
.LFB21:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$8, %esp
	.cfi_def_cfa_offset 16
	cmpl	$-1426085121, 67113124
	jne	.L129
	cmpl	$-1426085121, 67113120
	jne	.L129
	cmpl	$-5570646, 67113132
	jne	.L129
	cmpl	$-5570646, 67113128
	jne	.L129
	cmpl	$0, 67113108
	ja	.L137
	cmpl	$1, 67113104
	jbe	.L129
.L137:
	cmpl	$0, 67113116
	ja	.L133
	cmpl	$1, 67113112
	ja	.L133
.L129:
	leal	.LC0@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 16
.L133:
	cmpl	$0, 67113076
	ja	.L135
	cmpl	$16383, 67113072
	ja	.L135
	leal	.LC9@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 16
.L135:
	movl	67113072, %eax
	movl	67113076, %edx
	addl	$8, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE21:
	.size	ret_imgfilesz, .-ret_imgfilesz
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB27:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE27:
	.section	.note.GNU-stack,"",@progbits
