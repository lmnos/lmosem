/**********************************************************
		内核态虚拟/物理地址映射文件kvirtadrmap.h
***********************************************************
				彭东 ＠ 2013.03.05.11.00
**********************************************************/
#ifndef _KVIRTADRMAP_H
#define _KVIRTADRMAP_H

PUBLIC adr_t krnlvirtadr_to_phyadr(adr_t kviradr);
PUBLIC adr_t krnlphyiadr_to_viradr(adr_t kphyadr);

#endif
