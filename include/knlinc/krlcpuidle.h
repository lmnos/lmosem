/**********************************************************
        LMOSEM idle线程头文件krlcpuidle.h
***********************************************************
                彭东 ＠ 2013.08.10.10.40
**********************************************************/
#ifndef _KRLCPUIDLE_H
#define _KRLCPUIDLE_H
void init_krlcpuidle();
void krlcpuidle_start();
thread_t* new_cpuidle_thread();
void new_cpuidle();
void krlcpuidle_main();
#endif // KRLCPUIDLE_H
