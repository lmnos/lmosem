###################################################################
#		krnlbuidcmd自动化编译配置文件 Makefile		  #
#				彭东  ＠ 2013.06.15.10.20	  #
###################################################################

#include "config.h"
#ifdef CFG_X86_PLATFORM
ASM 	= nasm
CC		= gcc
LD		= ld
DD		= dd
RM		= rm # -ld -lgcc  $(LIBPATH)-mcmodel=large
OYFLAGS		= -O binary
CFLAGS      = $(HEADFILE_PATH) -c -O2 -m32 -mtune=generic -mno-red-zone -std=c99 -Wall -Wshadow -save-temps  -W -Wconversion -Wno-sign-conversion -fno-stack-protector  -fomit-frame-pointer -fno-builtin -fno-common  -fno-ident -ffreestanding  -Wno-unused-parameter -Wunused-variable
LDFLAGS		= -s -static -T lmemknllink.lds -n -Map lmos_em.map
CPPFLGSLDS	= $(HEADFILE_PATH) -E -P 
ASMFLGS		= $(HEADFILE_PATH) -f elf
OBJCOPY = objcopy
OJCYFLAGS = -S -O binary

#else

CC		= arm-linux-gcc
LD		= arm-linux-ld

DD		= dd 
LIBPATH		= -L /opt/armtoolschain/4.4.3/lib/gcc/arm-none-linux-gnueabi/4.4.3/libgcc.a -pipe -g -fno-common 
RM		= rm # -ld -lgcc  $(LIBPATH)
OBJCOPY		= arm-linux-objcopy
OYFLAGS		= -O binary
CFLAGS          = $(HEADFILE_PATH) -c -O2 -fno-builtin -ffreestanding -std=c99 -save-temps  -march=armv4 -Wall -Wshadow -W -Wconversion -Wno-sign-conversion -fno-stack-protector -fomit-frame-pointer   -fno-ident  -Wno-unused-parameter -Wunused-variable -mtune=arm7tdmi
LDFLAGS		= -Bstatic -nostdlib -T lmemknllink.lds -Map lmos_em.map

CPPFLGSLDS	= $(HEADFILE_PATH) -E -P 

#endif