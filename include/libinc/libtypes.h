#ifndef _LIBTYPES_H
#define _LIBTYPES_H
typedef long sint_t;
typedef unsigned long uint_t;
typedef sint_t sysstus_t;
typedef sint_t hand_t;
typedef void* buf_t;
typedef unsigned long size_t;

typedef struct s_TIME
{
    
    uint_t      year;
    uint_t      mon;
    uint_t      day;
    uint_t      date;
    uint_t      hour;
    uint_t      min;
    uint_t      sec;
    
}times_t;


#define SYSSTUSERR (-1)
#define SYSSTUSOK (0)
#define NULL 0
#define FILE_TY_MASK 0xf
#define FILE_TY_FILE 0
#define FILE_TY_DEV 1
#define RWO_FLG_MASK 0xff
#define RWO_FLG_BITS 0x4
#define RW_FLG (0x3<<RWO_FLG_BITS)
#define RO_FLG (0x1<<RWO_FLG_BITS)
#define WO_FLG (0x2<<RWO_FLG_BITS)
#define NF_FLG (0x4<<RWO_FLG_BITS)

#endif // LIBTYPES_H
