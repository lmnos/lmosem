;/**********************************************************
;       初始化入口文件init.s
;***********************************************************
;                彭东 ＠ 2013.06.01.10.30
;**********************************************************/
%define MBSP_ADR 0x100000
%define IA32_EFER 0C0000080H
%define PML4T_BADR 0x1000000      ;0x20000;0x5000
%define KRLVIRADR 0xffff800000000000
%define KINITSTACK_OFF 16
global _start
extern lmosemhal_start
[section .head.text]
[bits 32]
_start:
_entry:
        cli
        lgdt [GDT_PTR]
        lidt [IDT_PTR]
        jmp dword 0x8 :_32bits_mode

_32bits_mode:
        mov ax, 0x10    ; 数据段选择子(目的)
        mov ds, ax
        mov ss, ax
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
        mov ebx,MBSP_ADR
        mov ecx,[ebx+KINITSTACK_OFF]
        
        xor ebx,ebx
        mov esp,ecx
        xor ecx,ecx
        call lmosemhal_start        
        jmp $

GDT_START:
knull_dsc: dq 0
kcode_dsc: dq 0x00cf9a000000ffff ;a-e
kdata_dsc: dq 0x00cf92000000ffff
k16cd_dsc: dq 0x00009a000000ffff ;a-e
k16da_dsc: dq 0x000092000000ffff
GDT_END:

GDT_PTR:
GDTLEN  dw GDT_END-GDT_START-1  ;GDT界限
GDTBASE dd GDT_START

IDT_PTR:
IDTLEN  dw 0x3ff
IDTBAS  dd 0