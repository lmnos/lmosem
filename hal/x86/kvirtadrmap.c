/**********************************************************
		内核态虚拟/物理地址映射文件kvirtadrmap.c
***********************************************************
				彭东 ＠ 2013.03.05.11.00
**********************************************************/

//#include "types.h"
//#include "mcontrol.h"

#include "lmosemtypes.h"
#include "lmosemmctrl.h"


adr_t krnlvirtadr_to_phyadr(adr_t kviradr)
{
	/*if(kviradr<KRNL_MAP_VIRTADDRESS_START||kviradr>KRNL_MAP_VIRTADDRESS_END)
	{
		system_error("krnlvirtadr_to_phyadr err\n");
		return KRNL_ADDR_ERROR;
	}
	return kviradr-KRNL_MAP_VIRTADDRESS_START;
	*/
	return kviradr;
} 

adr_t krnlphyiadr_to_viradr(adr_t kphyadr)
{
	/*if(kphyadr>=KRNL_MAP_PHYADDRESS_END)
	{
		system_error("krnlphyiadr_to_viradr err\n");
		return KRNL_ADDR_ERROR;
	}
	return kphyadr+KRNL_MAP_VIRTADDRESS_START;
	*/
	return kphyadr;
}
