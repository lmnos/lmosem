#include "libc.h"

sysstus_t close(hand_t fhand)
{

    sysstus_t rets=api_close(fhand);
    return rets;
}
