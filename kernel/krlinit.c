/****************************************************************
        LMOSEM kernel全局初始化文件krlinit.c
*****************************************************************
                彭东 ＠ 2013.07.18.16.40
****************************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void init_krl()
{
    init_krlmm();
	init_krldevice();
    init_krldriver();
	init_krlsched();
    init_krliocacheblk();
    init_ktime();
    init_task();
    init_krlcpuidle();
    hal_sysdie("LMOSEM KERNEL LAYER RUN!!");
    return;
}
