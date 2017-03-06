###################################################################
# drv自动化编译配置文件 Makefile #
# 彭东 ＠ 2013.09.22.11.00 #
###################################################################
MAKEFLAGS = -s
KERNELCE_PATH = ../drivers/
HEADFILE_PATH = -I ../include -I ../include/bastypeinc -I ../include/halinc -I ../include/knlinc -I ../include/libinc -I ../include/drvinc
CCBUILDPATH = $(KERNELCE_PATH)
include krnlbuidcmd.mk
include krnlobjs.mk
.PHONY : all everything build_kernel
all: build_kernel
build_kernel:everything
everything :$(BUILD_MK_DRIV_OBJS)
include krnlbuidrule.mk
