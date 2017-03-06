#include "libc.h"
sysstus_t read(hand_t fhand,buf_t buf,size_t len,uint_t flgs)
{
    sysstus_t rets=api_read(fhand,buf,len,flgs);
    return rets;
}
