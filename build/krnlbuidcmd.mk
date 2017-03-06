###################################################################
# krnlbuidcmd自动化编译配置文件 Makefile #
# 彭东 ＠ 2013.06.15.10.20 #
###################################################################
ASM = nasm
CC = gcc
LD = ld
DD = dd
RM = rm # -ld -lgcc $(LIBPATH)-mcmodel=large
OBJCOPY = objcopy
OYFLAGS = -O binary
CFLAGS = $(HEADFILE_PATH) -c -O2 -m32 -mtune=generic -mno-red-zone -std=c99 -Wall -Wshadow -save-temps -W -Wconversion -Wno-sign-conversion -fno-stack-protector -fomit-frame-pointer -fno-builtin -fno-common -fno-ident -ffreestanding -Wno-unused-parameter -Wunused-variable
LDFLAGS = -s -static -T lmemknllink.lds -n -Map lmos_em.map --oformat binary
CPPFLGSLDS = $(HEADFILE_PATH) -E -P
ASMFLGS = $(HEADFILE_PATH) -f elf
