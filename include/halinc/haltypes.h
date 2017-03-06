/****************************************************************
        LMOSEM HAL类型头文件haltypes.h
*****************************************************************
                彭东 ＠ 2013.06.23.11.55
****************************************************************/
#ifndef _HALTYPES_H
#define _HALTYPES_H

#include "platform_t.h"
#include "cpu_t.h"
#include "cpuctrl_t.h"
#include "halmmu_t.h"
#include "haluart_t.h"
#include "halintupt_t.h"
#include "halmm_t.h"
#include "halmach_t.h"
#include "intabtdistr_t.h"
#ifdef CFG_X86_PLATFORM
#include "gdtidt_t.h"
#include "intallocator_t.h"
#include "pages64_t.h"
#include "kvirtadrmap_t.h"
#include "lmosimgfs_t.h"
#include "bdvideo_t.h"
#include "memmgrtypes.h"
#endif

#include "halglobal_t.h"
#include "halinit_t.h"
#include "printfk_t.h"



#endif // HALTYPES_H
