#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void task1_main();
void task0_main();
void task2_main();
void task3_main();
void task4_main();
void task5_main();

void task0()
{
    thread_t* thp= krlnew_thread((void*)task0_main,0,PRILG_USR,PRITY_MIN,0,0);
    if(thp==NULL)
    {
        hal_sysdie("task0 err");
    }

    return;
}



void task1()
{

    thread_t* thp= krlnew_thread((void*)task1_main,0,PRILG_USR,PRITY_MIN,0,0);
    if(thp==NULL)
    {
        hal_sysdie("task1 err");
    }

    return;
}
void task2()
{
    thread_t* thp= krlnew_thread((void*)task2_main,0,PRILG_USR,PRITY_MIN,0,0);
    if(thp==NULL)
    {
        hal_sysdie("task2 err");
    }

    return;
}
void task3()
{
    thread_t* thp= krlnew_thread((void*)task3_main,0,PRILG_USR,PRITY_MIN,0,0);
    if(thp==NULL)
    {
        hal_sysdie("task3 err");
    }

    return;
}
void task4()
{
    thread_t* thp= krlnew_thread((void*)task4_main,0,PRILG_USR,PRITY_MIN,0,0);
    if(thp==NULL)
    {
        hal_sysdie("task4 err");
    }

    return;
}
void task5()
{
    thread_t* thp= krlnew_thread((void*)task5_main,0,PRILG_USR,PRITY_MIN,0,0);
    if(thp==NULL)
    {
        hal_sysdie("task5 err");
    }

    return;
}


void init_task()
{  
    task0();
    task1();
    /*task2();
    task3();
    task4();
    task5();
   */
    return;
}

