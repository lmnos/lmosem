/****************************************************************
        LMOSEM HAL头文件halheads.h
*****************************************************************
                彭东 ＠ 2013.06.23.11.50
****************************************************************/
#ifndef _HALHEADS_H
#define _HALHEADS_H
#include "link.h"
#include "platform.h"
#include "cpu.h"
#include "cpuctrl.h"
#include "halmmu.h"
#include "haluart.h" 
#include "halintupt.h"
#include "halmm.h"
#include "halmach.h"
#include "intabtdistr.h"
#ifdef CFG_X86_PLATFORM
#include "io.h"
#include "gdtidt.h"
#include "intallocator.h"
#include "i8254.h"
#include "i8259.h"
#include "kvirtadrmap.h"
#include "lmosimgfs.h"
#include "bdvideo.h"
#include "memmgrmctrl.h"
#endif
#include "halglobal.h"
#include "halinit.h"
#include "printfk.h"
#endif // HALHEADS_H
