/**********************************************************
        uart0驱动头文件haluart_t.h
***********************************************************
                彭东 ＠ 2013.09.03.11.00
**********************************************************/

#ifndef _HALUART_T_H
#define _HALUART_T_H

#define ULCON0_R 0x50000000
#define ULCON1_R 0x50004000
#define ULCON2_R 0x50008000

#define UCON0_R 0x50000004
#define UCON1_R 0x50004004
#define UCON2_R 0x50008004

#define UFCON0_R 0x50000008
#define UFCON1_R 0x50004008
#define UFCON2_R 0x50008008 

#define UMCON0_R 0x5000000C
#define UMCON1_R 0x5000400C

#define UTRSTAT0_R 0x50000010
#define UTRSTAT1_R 0x50004010
#define UTRSTAT2_R 0x50008010 

#define UERSTAT0_R 0x50000014
#define UERSTAT1_R 0x50004014
#define UERSTAT2_R 0x50008014 

#define UFSTAT0_R 0x50000018
#define UFSTAT1_R 0x50004018
#define UFSTAT2_R 0x50008018

#define UMSTAT0_R 0x5000001C
#define UMSTAT1_R 0x5000401C

#define UTXH0_R 0x50000020
#define UTXH1_R 0x50004020
#define UTXH2_R 0x50008020

#define URXH0_R 0x50000024
#define URXH1_R 0x50004024
#define URXH2_R 0x50008024

#define UBRDIV0_R 0x50000028
#define UBRDIV1_R 0x50004028
#define UBRDIV2_R 0x50008028


#endif // HALUART_T_H
