	.file	"chkcpmm.c"
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
	.globl	acpi_get_bios_ebda
	.type	acpi_get_bios_ebda, @function
acpi_get_bios_ebda:
.LFB7:
	.cfi_startproc
	movzwl	1038, %eax
	sall	$4, %eax
	ret
	.cfi_endproc
.LFE7:
	.size	acpi_get_bios_ebda, .-acpi_get_bios_ebda
	.globl	acpi_checksum
	.type	acpi_checksum, @function
acpi_checksum:
.LFB8:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	movl	8(%esp), %ecx
	xorl	%edx, %edx
	xorl	%eax, %eax
.L15:
	cmpl	12(%esp), %edx
	je	.L18
	movzbl	(%ecx,%edx), %ebx
	incl	%edx
	addl	%ebx, %eax
	jmp	.L15
.L18:
	movzbl	%al, %eax
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE8:
	.size	acpi_checksum, .-acpi_checksum
	.globl	acpi_rsdp_isok
	.type	acpi_rsdp_isok, @function
acpi_rsdp_isok:
.LFB9:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	movl	8(%esp), %ebx
	movl	20(%ebx), %eax
	testl	%eax, %eax
	je	.L22
	cmpb	$0, 15(%ebx)
	je	.L22
	pushl	%eax
	.cfi_def_cfa_offset 12
	pushl	%ebx
	.cfi_def_cfa_offset 16
	call	acpi_checksum
	testl	%eax, %eax
	movl	$0, %eax
	popl	%edx
	.cfi_def_cfa_offset 12
	cmovne	%eax, %ebx
	popl	%ecx
	.cfi_def_cfa_offset 8
	jmp	.L20
.L22:
	xorl	%ebx, %ebx
.L20:
	movl	%ebx, %eax
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE9:
	.size	acpi_rsdp_isok, .-acpi_rsdp_isok
	.globl	findacpi_rsdp_core
	.type	findacpi_rsdp_core, @function
findacpi_rsdp_core:
.LFB10:
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
	movl	16(%esp), %ebx
	testl	%ebx, %ebx
	je	.L31
	cmpl	$1023, 20(%esp)
	jbe	.L31
	xorl	%esi, %esi
	xorl	%edi, %edi
.L27:
	cmpl	$0, %edi
	ja	.L31
	cmpl	20(%esp), %esi
	ja	.L31
	cmpb	$82, (%ebx)
	jne	.L28
	cmpb	$83, 1(%ebx)
	jne	.L28
	cmpb	$68, 2(%ebx)
	jne	.L28
	cmpb	$32, 3(%ebx)
	jne	.L28
	cmpb	$80, 4(%ebx)
	jne	.L28
	cmpb	$84, 5(%ebx)
	jne	.L28
	cmpb	$82, 6(%ebx)
	jne	.L28
	cmpb	$32, 7(%ebx)
	jne	.L28
	pushl	%ebx
	.cfi_def_cfa_offset 20
	call	acpi_rsdp_isok
	testl	%eax, %eax
	popl	%edx
	.cfi_def_cfa_offset 16
	jne	.L25
.L28:
	addl	$1, %esi
	adcl	$0, %edi
	incl	%ebx
	jmp	.L27
.L31:
	xorl	%eax, %eax
.L25:
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
.LFE10:
	.size	findacpi_rsdp_core, .-findacpi_rsdp_core
	.globl	find_acpi_rsdp
	.type	find_acpi_rsdp, @function
find_acpi_rsdp:
.LFB11:
	.cfi_startproc
	pushl	%ecx
	.cfi_def_cfa_offset 8
	movzwl	1038, %eax
	pushl	$1024
	.cfi_def_cfa_offset 12
	sall	$4, %eax
	pushl	%eax
	.cfi_def_cfa_offset 16
	call	findacpi_rsdp_core
	testl	%eax, %eax
	popl	%edx
	.cfi_def_cfa_offset 12
	popl	%ecx
	.cfi_def_cfa_offset 8
	jne	.L34
	pushl	$131071
	.cfi_def_cfa_offset 12
	pushl	$917504
	.cfi_def_cfa_offset 16
	call	findacpi_rsdp_core
	popl	%ecx
	.cfi_def_cfa_offset 12
	popl	%edx
	.cfi_def_cfa_offset 8
.L34:
	popl	%edx
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE11:
	.size	find_acpi_rsdp, .-find_acpi_rsdp
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Your computer is not support ACPI!!"
	.text
	.globl	init_acpi
	.type	init_acpi, @function
init_acpi:
.LFB12:
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
	call	find_acpi_rsdp
	testl	%eax, %eax
	jne	.L38
	leal	.LC0@GOTOFF(%ebx), %edx
	movl	%eax, 12(%esp)
	subl	$12, %esp
	.cfi_def_cfa_offset 44
	pushl	%edx
	.cfi_def_cfa_offset 48
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 32
	movl	12(%esp), %eax
.L38:
	movl	32(%esp), %ecx
	leal	320(%ecx), %esi
	movl	$36, %ecx
	movl	%esi, %edx
	call	m2mcopy
	subl	$12, %esp
	.cfi_def_cfa_offset 44
	pushl	%esi
	.cfi_def_cfa_offset 48
	call	acpi_rsdp_isok
	addl	$16, %esp
	.cfi_def_cfa_offset 32
	testl	%eax, %eax
	jne	.L37
	leal	.LC0@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 44
	pushl	%eax
	.cfi_def_cfa_offset 48
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 32
.L37:
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
.LFE12:
	.size	init_acpi, .-init_acpi
	.section	.rodata.str1.1
.LC1:
	.string	"iks_moveimg err"
	.text
	.globl	init_krlinitstack
	.type	init_krlinitstack, @function
init_krlinitstack:
.LFB15:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$16, %esp
	.cfi_def_cfa_offset 28
	movl	28(%esp), %esi
	pushl	$0
	.cfi_def_cfa_offset 32
	pushl	$4097
	.cfi_def_cfa_offset 36
	pushl	$0
	.cfi_def_cfa_offset 40
	pushl	$585728
	.cfi_def_cfa_offset 44
	pushl	%esi
	.cfi_def_cfa_offset 48
	call	move_krlimg@PLT
	addl	$32, %esp
	.cfi_def_cfa_offset 16
	testl	%eax, %eax
	jg	.L42
	leal	.LC1@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 16
.L42:
	movl	$589808, 16(%esi)
	movl	$0, 20(%esi)
	movl	$4096, 24(%esi)
	movl	$0, 28(%esi)
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
.LFE15:
	.size	init_krlinitstack, .-init_krlinitstack
	.section	.rodata.str1.1
.LC2:
	.string	"ip_moveimg err"
	.text
	.globl	init_bstartpages
	.type	init_bstartpages, @function
init_bstartpages:
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
	subl	$40, %esp
	.cfi_def_cfa_offset 60
	movl	60(%esp), %esi
	pushl	$0
	.cfi_def_cfa_offset 64
	pushl	$73728
	.cfi_def_cfa_offset 68
	pushl	$0
	.cfi_def_cfa_offset 72
	pushl	$16777216
	.cfi_def_cfa_offset 76
	pushl	%esi
	.cfi_def_cfa_offset 80
	call	move_krlimg@PLT
	addl	$32, %esp
	.cfi_def_cfa_offset 48
	testl	%eax, %eax
	jg	.L45
	leal	.LC2@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	pushl	%eax
	.cfi_def_cfa_offset 64
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 48
.L45:
	movl	$16777216, %eax
.L46:
	movl	$0, (%eax)
	movl	$0, 4(%eax)
	addl	$8, %eax
	movl	$0, 4088(%eax)
	movl	$0, 4092(%eax)
	cmpl	$16781312, %eax
	jne	.L46
	xorl	%ecx, %ecx
	xorl	%ebx, %ebx
	movl	$16785408, %edx
.L48:
	movl	%edx, %edi
	movl	$0, 4(%eax)
	orl	$3, %edi
	movl	%edi, (%eax)
	movl	%ecx, 8(%esp)
	xorl	%edi, %edi
	movl	%ebx, 12(%esp)
.L47:
	movl	8(%esp), %ebp
	orl	$131, %ebp
	addl	$2097152, 8(%esp)
	movl	%ebp, (%edx,%edi,8)
	movl	12(%esp), %ebp
	adcl	$0, 12(%esp)
	movl	%ebp, 4(%edx,%edi,8)
	incl	%edi
	cmpl	$512, %edi
	jne	.L47
	addl	$1073741824, %ecx
	adcl	$0, %ebx
	addl	$4096, %edx
	addl	$8, %eax
	cmpl	$16850944, %edx
	jne	.L48
	movl	$16781315, 16779264
	movl	$0, 16779268
	movl	$16781315, 16777216
	movl	$0, 16777220
	movl	$16777216, 288(%esi)
	movl	$0, 292(%esi)
	movl	$73728, 296(%esi)
	movl	$0, 300(%esi)
	movl	$0, 304(%esi)
	movl	$4, 308(%esi)
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
.LFE16:
	.size	init_bstartpages, .-init_bstartpages
	.section	.rodata.str1.1
.LC3:
	.string	"im_moveimg err"
	.text
	.globl	init_meme820
	.type	init_meme820, @function
init_meme820:
.LFB17:
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
	subl	$56, %esp
	.cfi_def_cfa_offset 76
	movl	76(%esp), %esi
	movl	$0, 24(%esp)
	movl	176(%esi), %eax
	movl	184(%esi), %edi
	imull	$20, 188(%esi), %ecx
	movl	120(%esi), %ebp
	movl	%eax, 40(%esp)
	movl	$20, %eax
	mull	%edi
	movl	%ebp, 20(%esp)
	movl	%edx, 32(%esp)
	addl	%ecx, 32(%esp)
	movl	%eax, 28(%esp)
	pushl	32(%esp)
	.cfi_def_cfa_offset 80
	pushl	32(%esp)
	.cfi_def_cfa_offset 84
	pushl	32(%esp)
	.cfi_def_cfa_offset 88
	pushl	32(%esp)
	.cfi_def_cfa_offset 92
	pushl	%esi
	.cfi_def_cfa_offset 96
	call	move_krlimg@PLT
	addl	$32, %esp
	.cfi_def_cfa_offset 64
	testl	%eax, %eax
	jg	.L54
	leal	.LC3@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 76
	pushl	%eax
	.cfi_def_cfa_offset 80
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 64
.L54:
	imull	$20, %edi, %edi
	movl	28(%esp), %eax
	movl	%ebp, %edx
	movl	%edi, %ecx
	call	m2mcopy
	movl	8(%esp), %eax
	movl	12(%esp), %edx
	movl	$0, 124(%esi)
	movl	%eax, 176(%esi)
	movl	16(%esp), %eax
	movl	%edx, 180(%esi)
	movl	20(%esp), %edx
	movl	%eax, 192(%esi)
	leal	4095(%edi,%ebp), %eax
	movl	%edx, 196(%esi)
	movl	20(%esp), %edx
	andl	$-4096, %eax
	movl	%eax, 120(%esi)
	movl	16(%esp), %eax
	addl	8(%esp), %eax
	adcl	12(%esp), %edx
	movl	%eax, 80(%esi)
	movl	%edx, 84(%esi)
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
.LFE17:
	.size	init_meme820, .-init_meme820
	.globl	mmap
	.type	mmap, @function
mmap:
.LFB18:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	xorl	%edx, %edx
	xorl	%eax, %eax
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$8, %esp
	.cfi_def_cfa_offset 16
	xorl	%ecx, %ecx
	call	realadr_call_entry@PLT
	movl	8256, %edx
	movl	20(%esp), %eax
	movl	%edx, (%eax)
	movl	16(%esp), %eax
	movl	8260, %edx
	movl	%edx, (%eax)
	addl	$8, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE18:
	.size	mmap, .-mmap
	.globl	chk_memsize
	.type	chk_memsize, @function
chk_memsize:
.LFB19:
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
	movl	40(%esp), %edi
	movl	44(%esp), %ebp
	movl	32(%esp), %edx
	movl	%edi, %ebx
	addl	48(%esp), %ebx
	movl	%ebp, %esi
	adcl	52(%esp), %esi
	cmpl	$0, 36(%esp)
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	je	.L64
	testl	%edx, %edx
	je	.L64
	xorl	%esi, %esi
.L63:
	cmpl	$1, 16(%edx)
	movl	%edx, %eax
	jne	.L60
	movl	4(%edx), %ebx
	movl	(%edx), %ecx
	cmpl	%ebx, %ebp
	jb	.L60
	ja	.L65
	cmpl	%ecx, %edi
	jb	.L60
.L65:
	addl	8(%edx), %ecx
	adcl	12(%edx), %ebx
	cmpl	%ebx, 4(%esp)
	jb	.L58
	ja	.L60
	cmpl	%ecx, (%esp)
	jb	.L58
.L60:
	incl	%esi
	addl	$20, %edx
	cmpl	%esi, 36(%esp)
	jne	.L63
.L64:
	xorl	%eax, %eax
.L58:
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
.LFE19:
	.size	chk_memsize, .-chk_memsize
	.globl	get_memsize
	.type	get_memsize, @function
get_memsize:
.LFB20:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	movl	16(%esp), %esi
	movl	12(%esp), %edx
	testl	%esi, %esi
	je	.L72
	testl	%edx, %edx
	je	.L72
	leal	8(%edx), %ebx
	xorl	%eax, %eax
	xorl	%edx, %edx
	xorl	%ecx, %ecx
.L71:
	cmpl	$1, 8(%ebx)
	jne	.L70
	addl	(%ebx), %eax
	adcl	4(%ebx), %edx
.L70:
	incl	%ecx
	addl	$20, %ebx
	cmpl	%ecx, %esi
	jne	.L71
	jmp	.L68
.L72:
	xorl	%eax, %eax
	xorl	%edx, %edx
.L68:
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE20:
	.size	get_memsize, .-get_memsize
	.section	.rodata.str1.1
.LC4:
	.string	"no e820map\n"
.LC5:
	.string	"Your computer is low on memory, the memory cannot be less than 128MB!"
	.text
	.globl	init_mem
	.type	init_mem, @function
init_mem:
.LFB13:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$28, %esp
	.cfi_def_cfa_offset 40
	movzwl	1038, %eax
	movl	40(%esp), %esi
	movl	$0, 20(%esp)
	sall	$4, %eax
	movl	$0, 316(%esi)
	movl	%eax, 312(%esi)
	leal	20(%esp), %eax
	pushl	%eax
	.cfi_def_cfa_offset 44
	leal	20(%esp), %eax
	pushl	%eax
	.cfi_def_cfa_offset 48
	call	mmap
	addl	$16, %esp
	.cfi_def_cfa_offset 32
	cmpl	$0, 12(%esp)
	jne	.L76
	leal	.LC4@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 44
	pushl	%eax
	.cfi_def_cfa_offset 48
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 32
.L76:
	pushl	%eax
	.cfi_def_cfa_offset 36
	pushl	%eax
	.cfi_def_cfa_offset 40
	pushl	$0
	.cfi_def_cfa_offset 44
	pushl	$134217728
	.cfi_def_cfa_offset 48
	pushl	$0
	.cfi_def_cfa_offset 52
	pushl	$1048576
	.cfi_def_cfa_offset 56
	pushl	36(%esp)
	.cfi_def_cfa_offset 60
	pushl	36(%esp)
	.cfi_def_cfa_offset 64
	call	chk_memsize
	addl	$32, %esp
	.cfi_def_cfa_offset 32
	testl	%eax, %eax
	jne	.L77
	leal	.LC5@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 44
	pushl	%eax
	.cfi_def_cfa_offset 48
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 32
.L77:
	movl	12(%esp), %eax
	movl	8(%esp), %edx
	movl	$0, 180(%esi)
	movl	$0, 188(%esi)
	movl	$0, 196(%esi)
	imull	$20, %eax, %ecx
	movl	%edx, 176(%esi)
	movl	%eax, 184(%esi)
	movl	%ecx, 192(%esi)
	pushl	%ecx
	.cfi_def_cfa_offset 36
	pushl	%ecx
	.cfi_def_cfa_offset 40
	pushl	%eax
	.cfi_def_cfa_offset 44
	pushl	%edx
	.cfi_def_cfa_offset 48
	call	get_memsize
	movl	%eax, 168(%esi)
	movl	%edx, 172(%esi)
	movl	%esi, (%esp)
	call	init_acpi
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
.LFE13:
	.size	init_mem, .-init_mem
	.globl	chk_cpuid
	.type	chk_cpuid, @function
chk_cpuid:
.LFB21:
	.cfi_startproc
#APP
# 267 "../ldrkrl/chkcpmm.c" 1
	pushfl 
	popl %eax 
	movl %eax,%ebx 
	xorl $0x0200000,%eax 
	pushl %eax 
	popfl 
	pushfl 
	popl %eax 
	xorl %ebx,%eax 
	jz 1f 
	movl $1,%ecx 
	jmp 2f 
	1: movl $0,%ecx 
	2: 
	
# 0 "" 2
#NO_APP
	movl	%ecx, %eax
	ret
	.cfi_endproc
.LFE21:
	.size	chk_cpuid, .-chk_cpuid
	.section	.rodata.str1.1
.LC6:
	.string	"Your CPU is not support CPUID sys is die!"
	.text
	.globl	init_chkcpu
	.type	init_chkcpu, @function
init_chkcpu:
.LFB14:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$8, %esp
	.cfi_def_cfa_offset 16
	call	chk_cpuid
	testl	%eax, %eax
	jne	.L81
	leal	.LC6@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kerror@PLT
#APP
# 136 "../ldrkrl/chkcpmm.c" 1
	cli; hlt
# 0 "" 2
#NO_APP
	addl	$16, %esp
	.cfi_def_cfa_offset 16
.L81:
	movl	16(%esp), %eax
	movl	$32, 160(%eax)
	movl	$0, 164(%eax)
	addl	$8, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE14:
	.size	init_chkcpu, .-init_chkcpu
	.globl	chk_cpu_longmode
	.type	chk_cpu_longmode, @function
chk_cpu_longmode:
.LFB22:
	.cfi_startproc
#APP
# 292 "../ldrkrl/chkcpmm.c" 1
	movl $0x80000000,%eax 
	cpuid 
	cmpl $0x80000001,%eax 
	setnb %al 
	jb 1f 
	movl $0x80000001,%eax 
	cpuid 
	bt $29,%edx  
	setcb %al 
	1: 
	movzx %al,%eax 
	
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE22:
	.size	chk_cpu_longmode, .-chk_cpu_longmode
	.globl	out_char
	.type	out_char, @function
out_char:
.LFB24:
	.cfi_startproc
	movl	4(%esp), %ecx
	xorl	%eax, %eax
.L85:
	incl	%eax
	movb	-1(%ecx,%eax), %dl
	testb	%dl, %dl
	je	.L87
	movb	%dl, 753662(%eax,%eax)
	jmp	.L85
.L87:
	ret
	.cfi_endproc
.LFE24:
	.size	out_char, .-out_char
	.globl	init_bstartpagesold
	.type	init_bstartpagesold, @function
init_bstartpagesold:
.LFB25:
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
	subl	$24, %esp
	.cfi_def_cfa_offset 44
	movl	44(%esp), %esi
	pushl	$0
	.cfi_def_cfa_offset 48
	pushl	$12288
	.cfi_def_cfa_offset 52
	pushl	$0
	.cfi_def_cfa_offset 56
	pushl	$131072
	.cfi_def_cfa_offset 60
	pushl	%esi
	.cfi_def_cfa_offset 64
	call	move_krlimg@PLT
	addl	$32, %esp
	.cfi_def_cfa_offset 32
	testl	%eax, %eax
	jg	.L89
	leal	.LC2@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 44
	pushl	%eax
	.cfi_def_cfa_offset 48
	call	kerror@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 32
.L89:
	movl	$131072, %eax
.L90:
	movl	$0, (%eax)
	movl	$0, 4(%eax)
	addl	$8, %eax
	movl	$0, 4088(%eax)
	movl	$0, 4092(%eax)
	movl	$0, 8184(%eax)
	movl	$0, 8188(%eax)
	cmpl	$135168, %eax
	jne	.L90
	movl	$135171, 131072
	movl	$0, 131076
	movl	$139264, %ecx
	movl	$139267, 135168
	movl	$0, 135172
	movl	$131, %edi
	movl	$135171, 133120
	movl	$0, 133124
	xorl	%ebx, %ebx
	xorl	%eax, %eax
	xorl	%edx, %edx
.L91:
	addl	$2097152, %eax
	movl	%edi, (%ecx)
	movl	%ebx, 4(%ecx)
	movl	%eax, %ebp
	adcl	$0, %edx
	movl	%eax, %edi
	xorl	$1073741824, %ebp
	orl	$131, %edi
	addl	$8, %ecx
	orl	%edx, %ebp
	movl	%edx, %ebx
	jne	.L91
	movl	$131072, 288(%esi)
	movl	$0, 292(%esi)
	movl	$12288, 296(%esi)
	movl	$0, 300(%esi)
	movl	$1073741824, 304(%esi)
	movl	$0, 308(%esi)
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
.LFE25:
	.size	init_bstartpagesold, .-init_bstartpagesold
	.globl	ldr_createpage_and_open
	.type	ldr_createpage_and_open, @function
ldr_createpage_and_open:
.LFB26:
	.cfi_startproc
	pushl	%edi
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	movl	$131072, %eax
	pushl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
.L96:
	movl	$0, (%eax)
	movl	$0, 4(%eax)
	addl	$8, %eax
	movl	$0, 4088(%eax)
	movl	$0, 4092(%eax)
	movl	$0, 8184(%eax)
	movl	$0, 8188(%eax)
	cmpl	$135168, %eax
	jne	.L96
	movl	$135171, 131072
	movl	$0, 131076
	movl	$139264, %ecx
	movl	$139267, 135168
	movl	$0, 135172
	movl	$131, %esi
	movl	$135171, 133120
	movl	$0, 133124
	xorl	%ebx, %ebx
	xorl	%eax, %eax
	xorl	%edx, %edx
.L97:
	addl	$2097152, %eax
	movl	%esi, (%ecx)
	movl	%ebx, 4(%ecx)
	movl	%eax, %edi
	adcl	$0, %edx
	movl	%eax, %esi
	xorl	$1073741824, %edi
	orl	$131, %esi
	addl	$8, %ecx
	orl	%edx, %edi
	movl	%edx, %ebx
	jne	.L97
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
.LFE26:
	.size	ldr_createpage_and_open, .-ldr_createpage_and_open
	.section	.rodata.str1.1
.LC7:
	.string	"Your computer is low on memory, the memory cannot be less than 64MB!"
.LC8:
	.string	"Your CPU is not support 64bits mode sys is die!"
	.text
	.globl	init_chkmm
	.type	init_chkmm, @function
init_chkmm:
.LFB23:
	.cfi_startproc
	pushl	%edi
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	xorl	%eax, %eax
	pushl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movzwl	8256, %edi
	xorl	%esi, %esi
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	xorl	%edx, %edx
	movl	$20480, %ecx
.L102:
	cmpl	%edi, %esi
	jge	.L111
	cmpl	$1, 16(%ecx)
	jne	.L103
	addl	8(%ecx), %eax
	adcl	12(%ecx), %edx
.L103:
	addl	$20, %ecx
	incl	%esi
	jmp	.L102
.L111:
	cmpl	$0, %edx
	ja	.L105
	cmpl	$66584575, %eax
	ja	.L105
	leal	.LC7@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
#APP
# 334 "../ldrkrl/chkcpmm.c" 1
	cli; hlt
# 0 "" 2
#NO_APP
	addl	$16, %esp
	.cfi_def_cfa_offset 16
.L105:
	call	chk_cpuid
	testl	%eax, %eax
	jne	.L107
	leal	.LC6@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
#APP
# 340 "../ldrkrl/chkcpmm.c" 1
	cli; hlt
# 0 "" 2
#NO_APP
	addl	$16, %esp
	.cfi_def_cfa_offset 16
.L107:
	call	chk_cpu_longmode
	testl	%eax, %eax
	jne	.L108
	leal	.LC8@GOTOFF(%ebx), %eax
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	kprint@PLT
#APP
# 346 "../ldrkrl/chkcpmm.c" 1
	cli; hlt
# 0 "" 2
#NO_APP
	addl	$16, %esp
	.cfi_def_cfa_offset 16
.L108:
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 12
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 4
	jmp	ldr_createpage_and_open
	.cfi_endproc
.LFE23:
	.size	init_chkmm, .-init_chkmm
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB30:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE30:
	.section	.note.GNU-stack,"",@progbits
