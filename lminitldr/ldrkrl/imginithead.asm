MBT_HDR_FLAGS	EQU 0x00010003
MBT_HDR_MAGIC	EQU 0x1BADB002
MBT2_MAGIC	EQU 0xe85250d6;0xe85250d6 ;
global _start
extern inithead_entry
[section .text]
[bits 32]
_start:
	jmp _entry
align 4
mbt_hdr:
	dd MBT_HDR_MAGIC
	dd MBT_HDR_FLAGS
	dd -(MBT_HDR_MAGIC+MBT_HDR_FLAGS)
	dd mbt_hdr
	dd _start
	dd 0
	dd 0
	dd _entry
	;
	; multiboot header
	;
ALIGN 8
MbHdr:
	; Magic
	DD	0xE85250D6
	; Architecture
	DD	0
	; Length
	DD	HdrEnd - MbHdr
	; Checksum
	DD	-(0xE85250D6 + 0 + (HdrEnd - MbHdr))

		;
	; Tags
		;

	; Sections override
	DW	2, 0
	DD	24
	DD	MbHdr
	DD	_start
	DD	0 ;_loadEnd
	DD	0 ;_bssEnd

	; Entry point override
	DW	3, 0
	DD	12
	DD	_entry ;EntryPoint
	DD      0           ; align next tag to 8 byte boundary

	; End Of Tags
	DW	0, 0
	DD	8

	; Hdr End Mark
HdrEnd:


_entry:
	cli
	;call disable_nmi

	in al, 0x70     ; port 0x70NMI_EN_PORT
	or al, 0x80	; disable all NMI source
	out 0x70,al	; NMI_EN_PORT

	lgdt [GDT_PTR]
	jmp dword 0x8 :_32bits_mode

_32bits_mode:
	mov ax, 0x10
	mov ds, ax
	mov ss, ax		; 视频段选择子(目的)
	mov es, ax
	mov fs, ax
	mov gs, ax
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx
	xor edi,edi
	xor esi,esi
	xor ebp,ebp
	xor esp,esp
	mov esp,0x7c00
	call inithead_entry
	jmp 0x200000

disable_nmi:
	push eax
	in al, 0x70     ; port 0x70NMI_EN_PORT
	or al, 0x80	; disable all NMI source
	out 0x70,al	; NMI_EN_PORT
	pop eax
	ret


GDT_START:
knull_dsc: dq 0
kcode_dsc: dq 0x00cf9e000000ffff
kdata_dsc: dq 0x00cf92000000ffff
k16cd_dsc: dq 0x00009e000000ffff
k16da_dsc: dq 0x000092000000ffff
GDT_END:

GDT_PTR:
GDTLEN	dw GDT_END-GDT_START-1	;GDT界限
GDTBASE	dd GDT_START
