/**********************************************************
        LMOSEM内核服务头文件krlsvethread.h
***********************************************************
                彭东 ＠ 2013.09.17.09.30
**********************************************************/
#ifndef _KRLSVETHREAD_H
#define _KRLSVETHREAD_H

sysstus_t krlsvetabl_exel_thread(uint_t swinr,stkparame_t* stkparv);
sysstus_t krlsvetabl_exit_thread(uint_t swinr,stkparame_t* stkparv);
sysstus_t krlsvetabl_retn_threadhand(uint_t swinr,stkparame_t* stkparv);
sysstus_t krlsvetabl_retn_threadstats(uint_t swinr,stkparame_t* stkparv);
sysstus_t krlsvetabl_set_threadstats(uint_t swinr,stkparame_t* stkparv);
hand_t krlsve_exel_thread(void* file,uint_t flgs);
sysstus_t krlsve_exit_thread();
hand_t krlsve_retn_threadhand(void* tname);
sysstus_t krlsve_retn_threadstats(hand_t thand,uint_t scode,uint_t data,buf_t buf);
sysstus_t krlsve_set_threadstats(hand_t thand,uint_t scode,uint_t data,buf_t buf);
hand_t krlsve_core_exel_thread(void* file,uint_t flgs);
void krlsve_core_exit_thread();
hand_t krlsve_core_retn_threadhand(void* tname);
sysstus_t krlsve_core_retn_threadstats(hand_t thand,uint_t scode,uint_t data,buf_t buf);
sysstus_t krlsve_core_set_threadstats(hand_t thand,uint_t scode,uint_t data,buf_t buf);
#endif // KRLSVETHREAD_H
