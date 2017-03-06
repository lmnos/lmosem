/****************************************************************
        LMOSEM HAL全局初始化文件halinit.c
*****************************************************************
                彭东 ＠ 2013.07.01.10.30
****************************************************************/

#include "lmosemtypes.h"
#include "lmosemmctrl.h"
LKHEAD_T void init_hal()
{
    init_paltform();
    init_haluart();
    init_halmach();
    init_halmm();
    init_halintupt();
    //print_mach(&osmach);
    //print_mmapdsc(&osmach);
    //for(;;);
    //test_blkmm();
    return;
}
