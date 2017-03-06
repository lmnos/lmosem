/**********************************************************
        开始入口文件lmosemhal_start.c
***********************************************************
                彭东 ＠ 2013.06.05.11.40
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

LKHEAD_T void lmosemhal_start()
{
   	init_hal();
    init_krl();
	//for(;;);
    return;
}
