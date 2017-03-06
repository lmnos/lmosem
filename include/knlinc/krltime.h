/**********************************************************
        LMOSEM时间头文件krltime.h
***********************************************************
                彭东 ＠ 2013.09.30.16.30
**********************************************************/
#ifndef _KRLTIME_H
#define _KRLTIME_H
void ktime_t_init(ktime_t* initp);
void init_ktime();
void krlupdate_times(uint_t year,uint_t mon,uint_t day,uint_t date,uint_t hour,uint_t min,uint_t sec);
sysstus_t krlsvetabl_time(uint_t swinr,stkparame_t* stkparv);
sysstus_t krlsve_time(time_t* time);
#endif // KRLTIME_H
