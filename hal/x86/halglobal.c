/****************************************************************
        LMOSEM HAL全局数据结构文件halglobal.c
*****************************************************************
                彭东 ＠ 2013.07.01.10.00
****************************************************************/
#define	HALGOBAL_HEAD
#include "lmosemtypes.h"
#include "lmosemmctrl.h"
#ifdef CFG_S3C2440A_PLATFORM

HAL_DEFGLOB_VARIABLE(mach_t,osmach);
HAL_DEFGLOB_VARIABLE(phymem_t,osphymem);
HAL_DEFGLOB_VARIABLE(phyadrspce_t,machadrspce)[PLFM_ADRSPCE_NR]={
{ADRSPCE_NORFLASH,0,0,0x001fffff},
{ADRSPCE_IO,0,0x08000000,0x0800000f},
{ADRSPCE_IO,0,0x10000000,0x1000000f},
{ADRSPCE_IO,0,0x19000000,0x190fffff},
{ADRSPCE_IO,0,0x20000000,0x2000000f},
{ADRSPCE_IO,0,0x28000000,0x28000007},
{ADRSPCE_IO,0,0x29000000,0x29000007},
{ADRSPCE_SDRAM,0,0x30000000,0x33ffffff},
{ADRSPCE_IO,0,0x48000000,0x48000030},
{ADRSPCE_IO,0,0x49000000,0x49000058},
{ADRSPCE_IO,0,0x4a000000,0x4a00001c},
{ADRSPCE_IO,0,0x4b000000,0x4b0000e0},
{ADRSPCE_IO,0,0x4c000000,0x4c000018},
{ADRSPCE_IO,0,0x4d000000,0x4d000060},
{ADRSPCE_IO,0,0x4e000000,0x4e00003c},
{ADRSPCE_IO,0,0x4f000000,0x4f0000a0},
{ADRSPCE_IO,0,0x50000000,0x50008028},
{ADRSPCE_IO,0,0x51000000,0x51000040},
{ADRSPCE_IO,0,0x52000000,0x5200026f},
{ADRSPCE_IO,0,0x53000000,0x53000008},
{ADRSPCE_IO,0,0x54000000,0x54000010},
{ADRSPCE_IO,0,0x55000000,0x55000012},
{ADRSPCE_IO,0,0x56000000,0x560000cc},
{ADRSPCE_IO,0,0x57000040,0x5700008b},
{ADRSPCE_IO,0,0x58000000,0x58000014},
{ADRSPCE_IO,0,0x59000000,0x59000034},
{ADRSPCE_IO,0,0x5a000000,0x5a000043},
{ADRSPCE_IO,0,0x5b000000,0x5b00001c},
{ADRSPCE_NOT,DEV_TYPE_NOT,0,0}};
HAL_DEFGLOB_VARIABLE(intfltdsc_t,machintflt)[IRQ_MAX];
#endif

#ifdef CFG_X86_PLATFORM
HAL_DEFGLOB_VARIABLE(DESCRIPTOR,GDT)[CPUCORE_MAX][GDTMAX];
HAL_DEFGLOB_VARIABLE(GATE,IDT)[IDTMAX];
HAL_DEFGLOB_VARIABLE(tss_t,tss)[CPUCORE_MAX]; 
HAL_DEFGLOB_VARIABLE(IGDTR,iGDT)[CPUCORE_MAX];
HAL_DEFGLOB_VARIABLE(IIDTR,iIDT);
HAL_DEFGLOB_VARIABLE(machbstart_t,kmachbsp);
HAL_DEFGLOB_VARIABLE(dftgraph_t,kdftgh);
HAL_DEFGLOB_VARIABLE(memmgrob_t,lmos_memmgrob);
HAL_DEFGLOB_VARIABLE(intfltdsc_t,machintflt)[IDTMAX];
#endif

#pragma GCC push_options
#pragma GCC optimize ("O0")
void die(u32_t dt)
{

    u32_t dttt=dt,dtt=dt;
    if(dt==0)
    {
        for(;;);
    }

    for(u32_t i=0;i<dt;i++)
    {
        for(u32_t j=0;j<dtt;j++)
        {
            for(u32_t k=0;k<dttt;k++)
            {
                ;
            }
        }
    }



    return;
}

#pragma GCC pop_options