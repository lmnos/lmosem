#ifndef LIBTIME_H
#define LIBTIME_H
sysstus_t time(times_t* ttime);
sysstus_t settime(times_t* ttime);
sysstus_t gettime(times_t* ttime);
sysstus_t synsecalarm(uint_t sec);
#define IOCTRCODE_SETTIME 1
#define IOCTRCODE_SETUPFREQ 2
#define IOCTRCODE_SET_SYNSECALM 3
#endif // LIBTIME_H
