/**********************************************************
        LMOSEM线程管理API头文件lapithread.h
***********************************************************
                彭东 ＠ 2013.09.15.13.30
**********************************************************/
#ifndef _LAPITHREAD_H
#define _LAPITHREAD_H
hand_t    api_exel_thread(void* file,uint_t flgs);
void      api_exit_thread();
hand_t    api_retn_threadhand(void* tname);
sysstus_t api_retn_threadstats(hand_t thand,uint_t scode,uint_t data,buf_t buf);
sysstus_t api_set_threadstats(hand_t thand,uint_t scode,uint_t data,buf_t buf);

#endif // LAPITHREAD_H
