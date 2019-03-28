#ifndef BUILDFILE_H
#define BUILDFILE_H
#include "config.h"

#define BUILD_BOOT_OBJS //i8254.o

#ifdef CFG_X86_PLATFORM

#define BUILD_HALY_OBJS init.o kernel.o intallocator.o lmosemhal_start.o halinit.o halglobal.o halmm.o\
                        halintupt.o platform.o cpuctrl.o bdvideo.o lmosimgfs.o printfk.o kvirtadrmap.o\
                        memmgrinit.o msadsc.o memarea.o memdivmer.o kmsob.o sgdtidt.o  i8259.o
#define BUILD_KRNL_OBJS krlinit.o krlglobal.o krlintupt.o krlspinlock.o\
                        krlsem.o krlwaitlist.o krliocache.o\
                        krlmm.o krlpagempol.o krlobjsmpol.o\
                        krlsched.o krltime.o krlobjnode.o krlthread.o\
                        krldevice.o krlservice.o krlsvemm.o\
                        krlsvethread.o krlsveopen.o krlsveclose.o\
                        krlsveread.o krlsvewrite.o krlsveioctrl.o\
                        krlsvelseek.o krlcpuidle.o task.o
#define BUILD_MEMY_OBJS
#define BUILD_FSYS_OBJS
#define BUILD_DRIV_OBJS drvtick.o 
#define BUILD_LIBS_OBJS lapimm.o lapithread.o lapiopen.o lapiclose.o\
                        lapiread.o lapiwrite.o lapiioctrl.o lapilseek.o\
                        lapitime.o\
                        libmm.o libthread.o libopen.o libclose.o\
                        libread.o libwrite.o libioctrl.o liblseek.o\
                        libtime.o printf.o
#define BUILD_TASK_OBJS utask.o

#define BUILD_LINK_OBJS BUILD_HALY_OBJS\
                        BUILD_KRNL_OBJS BUILD_MEMY_OBJS\
                        BUILD_FSYS_OBJS BUILD_DRIV_OBJS\
                        BUILD_LIBS_OBJS BUILD_TASK_OBJS
#define LINKR_IPUT_FILE BUILD_LINK_OBJS
#define LINKR_OPUT_FILE lmosemkrnl.elf
#define KERNL_ELFF_FILE LINKR_OPUT_FILE
#define KERNL_BINF_FILE lmosemkrnl.bin


#endif
#ifdef CFG_S3C2440A_PLATFORM

#define BUILD_HALY_OBJS init.o lmosemhal_start.o interrupt.o\
                        intabtdistr.o\
                        halglobal.o halinit.o vector.o platform.o\
                        printfk.o div0.krnl _udivsi3.o _umodsi3.o\
                        _modsi3.o _divsi3.o cpuctrl.o halmmu.o\
                        halmach.o halmm.o halintupt.o haluart.o

#define BUILD_KRNL_OBJS krlinit.o krlglobal.o krlintupt.o\
                        krlsem.o krlwaitlist.o\
                        krlmm.o krlpagempol.o krlobjsmpol.o\
                        krlsched.o krltime.o krlobjnode.o krlthread.o\
                        krldevice.o krlservice.o krlsvemm.o\
                        krlsvethread.o krlsveopen.o krlsveclose.o\
                        krlsveread.o krlsvewrite.o krlsveioctrl.o\
                        krlsvelseek.o krlcpuidle.o task.o 
#define BUILD_MEMY_OBJS
#define BUILD_FSYS_OBJS
#define BUILD_DRIV_OBJS drvtick.o drvuart.o drvrtc.o drvrfs.o
#define BUILD_LIBS_OBJS lapimm.o lapithread.o lapiopen.o lapiclose.o\
                        lapiread.o lapiwrite.o lapiioctrl.o lapilseek.o\
                        lapitime.o\
                        libmm.o libthread.o libopen.o libclose.o\
                        libread.o libwrite.o libioctrl.o liblseek.o\
                        libtime.o printf.o
#define BUILD_TASK_OBJS utask.o

#define BUILD_LINK_OBJS BUILD_BOOT_OBJS BUILD_HALY_OBJS\
                        BUILD_KRNL_OBJS BUILD_MEMY_OBJS\
                        BUILD_FSYS_OBJS BUILD_DRIV_OBJS\
                        BUILD_LIBS_OBJS BUILD_TASK_OBJS
#define LINKR_IPUT_FILE BUILD_LINK_OBJS
#define LINKR_OPUT_FILE lmosemkrnl.elf
#define KERNL_ELFF_FILE LINKR_OPUT_FILE
#define KERNL_BINF_FILE lmosemkrnl.bin

#endif


                          
#endif // BUILDFILE_H
