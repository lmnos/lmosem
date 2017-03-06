#include "libc.h"
sysstus_t ioctrl(hand_t fhand,buf_t buf,uint_t iocode,uint_t flgs)
{
    sysstus_t rets=api_ioctrl(fhand,buf,iocode,flgs);
    return rets;
}