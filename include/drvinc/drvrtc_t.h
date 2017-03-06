/**********************************************************
        LMOSEMRTC驱动头文件drvrtc_t.h
***********************************************************
                彭东 ＠ 2013.09.30.12.10
**********************************************************/
#ifndef _DRVRTC_T_H
#define _DRVRTC_T_H

#define RTC_INT_PHYLINE 30
#define RTCTICK_INT_PHYLINE 8

#define RTCCON_R 0x57000040
#define TICNT_R 0x57000044
#define RTCALM_R 0x57000050
#define ALMSEC_R 0x57000054
#define ALMMIN_R 0x57000058
#define ALMHOR_R 0x5700005c
#define ALMDAT_R 0x57000060
#define ALMMON_R 0x57000064
#define ALMYER_R 0x57000068

#define BCDSEC_R 0x57000070
#define BCDMIN_R 0x57000074
#define BCDHOR_R 0x57000078
#define BCDDAT_R 0x5700007c
#define BCDDAY_R 0x57000080
#define BCDMON_R 0x57000084
#define BCDYER_R 0x57000088


#define RTCTICK_INT_EN (1<<7)
#define RTCALM_EN (1<<6)
#define RTCSECALM_EN (1<<0)

#define BCD2BIN(val)    (((val) & 0x0f) + ((val)>>4)*10)
#define BIN2BCD(val)    ((((val)/10)<<4) + (val)%10)

#define BCD_TO_BIN(val) ((val)=BCD2BIN(val))
#define BIN_TO_BCD(val) ((val)=BIN2BCD(val))

#define IOCTRCODE_SETTIME 1
#define IOCTRCODE_SETUPFREQ 2
#define IOCTRCODE_SET_SYNSECALM 3
#endif // DRVRTC_T_H
