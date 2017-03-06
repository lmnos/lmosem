%include "ldrasm.inc"
global _start
[section .text]
[bits 16]
_start:
_16_mode:
	mov	bp,0x20
	mov	ds, bp
	mov	es, bp
	mov	ss, bp
	mov	ebp, cr0
	and	ebp, 0xfffffffe
	mov	cr0, ebp
	jmp	0:real_entry
real_entry:
	mov bp, cs
	mov ds, bp
	mov es, bp
	mov ss, bp
	mov sp, 08000h
	mov bp,func_table
	add bp,ax
	call [bp]
	cli
	call disable_nmi
	mov	ebp, cr0
	or	ebp, 1
	mov	cr0, ebp
	jmp dword 0x8 :_32bits_mode
[BITS 32]
_32bits_mode:
	mov bp, 0x10
	mov ds, bp
	mov ss, bp
	mov esi,[PM32_EIP_OFF]
	mov esp,[PM32_ESP_OFF]
	jmp esi

[BITS 16]
DispStr:
	mov bp,ax
	mov cx,23
	mov ax,01301h
	mov bx,000ch
	mov dh,10
	mov dl,25
	mov bl,15
	int 10h
	ret
cleardisp:
	mov ax,0600h     	;这段代码是为了清屏
	mov bx,0700h
	mov cx,0
	mov dx,0184fh
	int 10h			;调用的BOIS的10号
	ret

_getmmap:
	push ds
	push es
	push ss
	mov esi,0
	mov dword[E80MAP_NR],esi
	mov dword[E80MAP_ADRADR],E80MAP_ADR

	xor ebx,ebx
	mov edi,E80MAP_ADR
loop:
	mov eax,0e820h
	mov ecx,20
	mov edx,0534d4150h
	int 15h
	jc .1

	add edi,20
	cmp edi,E80MAP_ADR+0x1000
	jg .1

	inc esi

	cmp ebx,0
	jne loop

	jmp .2

.1:
	mov esi,0

.2:
	mov dword[E80MAP_NR],esi
	pop ss
	pop es
	pop ds
	ret
_read:
	push ds
	push es
	push ss
	xor eax,eax
	mov ah,0x42
	mov dl,0x80
	mov si,RWHDPACK_ADR
	int 0x13
	jc  .err
	pop ss
	pop es
	pop ds
	ret
.err:
	mov ax,int131errmsg
	call DispStr
	jmp $
	pop ss
	pop es
	pop ds
	ret

_getvbemode:
        push es
        push ax
        push di
        mov di,VBEINFO_ADR
        mov ax,0
        mov es,ax
        mov ax,0x4f00
        int 0x10
        cmp ax,0x004f
        jz .ok
        mov ax,getvbmodeerrmsg
        call DispStr
        jmp $
 .ok:
        pop di
        pop ax
        pop es
        ret
_getvbeonemodeinfo:
        push es
        push ax
        push di
        push cx
        mov di,VBEMINFO_ADR
        mov ax,0
        mov es,ax
        mov cx,0x118
        mov ax,0x4f01
        int 0x10
        cmp ax,0x004f
        jz .ok
        mov ax,getvbmodinfoeerrmsg
        call DispStr
        jmp $
 .ok:
        pop cx
        pop di
        pop ax
        pop es
        ret
_setvbemode:
        push ax
        push bx
        mov bx,0x4118
        mov ax,0x4f02
        int 0x10
        cmp ax,0x004f
        jz .ok
        mov ax,setvbmodeerrmsg
        call DispStr
        jmp $
 .ok:
        pop bx
        pop ax
        ret
disable_nmi:
	push ax
	in al, 0x70     ; port 0x70NMI_EN_PORT
	or al, 0x80	; disable all NMI source
	out 0x70,al	; NMI_EN_PORT
	pop ax
	ret

func_table:
	dw _getmmap
	dw _read
        dw _getvbemode
        dw _getvbeonemodeinfo
        dw _setvbemode

BootM:  db     "pengdong, OS is loading"
	db 0
int131errmsg: db     "int 13 read hdsk  error"
        db 0
getvbmodeerrmsg: db     "get vbemode err"
        db 0
getvbmodinfoeerrmsg: db     "get vbemodeinfo err"
                db 0
setvbmodeerrmsg: db     "set vbemode err"
        db 0
