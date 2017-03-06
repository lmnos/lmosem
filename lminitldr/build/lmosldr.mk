###################################################################
#		x86_64boot自动化编译配置文件 Makefile		  #
#				彭东  ＠ 2013.02.20.16.30	  #
###################################################################

MAKEFLAGS = -s
HEADFILE_PATH = ../include/
KRNLBOOT_PATH = ../ldrkrl/
CCBUILDPATH	= $(KRNLBOOT_PATH)
include krnlbuidcmd.mh
include ldrobjs.mh

.PHONY : all everything  build_kernel
all: build_kernel 

build_kernel:everything
	
everything : $(LMOSLDRIMH_OBJS) $(LMOSLDRKRL_OBJS) $(LMOSLDRSVE_OBJS)

include krnlbuidrule.mh
