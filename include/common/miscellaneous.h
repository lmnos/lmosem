#ifndef _MISCELLANEOUS_T_H
#define _MISCELLANEOUS_T_H

#include    "krlmm.h"
#include    "bastype_t.h"

#ifndef offsetof
#define offsetof(TYPE, MEMBER)  ((size_t) &((TYPE *)0)->MEMBER)
#endif

#ifndef data_offset2
#define data_offset2(q, type, link) (type*)((void*)((char*)q - offsetof(type, link)))
#endif

#endif
