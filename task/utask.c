#include "stdio.h"
void printfk(const char* fmt,...);
void usr_write_file()
{

    char* buf=(char*)mallocblk(0x1000);
    if(buf==NULL)
    {
        goto err;
    }
    for(int i=0;i<512;i++)
    {
        buf[i]=(char)0xff;
    }
    if(open("/file.bin",NF_FLG|FILE_TY_FILE,0)==-1)
    {

        goto err;
    }
    hand_t fd=open("/file.bin",RW_FLG|FILE_TY_FILE,0);
    if(fd==-1)
    {
        goto err;
    }
    if(write(fd,buf,512,0)==SYSSTUSERR)
    {
        goto err;
    }
    close(fd);
    if(mfreeblk(buf,0x1000)==SYSSTUSERR)
    {
        goto err;
    }
    return;
err:
    printf("usr_write_file err\n\r");
    for(;;);
    return;
}

void usr_read_file()
{

    char* buf=(char*)mallocblk(0x1000);
    if(buf==NULL)
    {
        goto err;
    }
    for(int i=0;i<0x1000;i++)
    {
        buf[i]=0;
    }

    hand_t fd=open("/file.bin",RW_FLG|FILE_TY_FILE,0);
    if(fd==-1)
    {
        goto err;
    }
    if(read(fd,buf,512,0)==SYSSTUSERR)
    {
        goto err;
    }
    for(int j=0;j<512;j++)
    {
        if(buf[j]!=(char)0xff)
        {
            goto err;
        }
    }
    close(fd);
    if(mfreeblk(buf,0x1000)==SYSSTUSERR)
    {
        goto err;
    }
    return;
err:
    printf("usr_read_file err\n\r");
    for(;;);
    return;
}

void task1_main()
{
    /*int i=0;
    
    times_t timet;

    usr_write_file();
    usr_read_file();

    for(;;)
    {
      i++;
      
      printf("task1 run %x task1ID:%x\n\r",i,pid(NULL));
      time(&timet);
      printf("year:%d mon:%d date:%d hour:%d min:%d sec:%d\n\r",
      timet.year,timet.mon,timet.date,timet.hour,timet.min,timet.sec);
    }*/
int i=0;
    for(;;)
    {
    i++;
    printfk("task1 run %x\n",i);
    //printf("task0 run %x task0ID:%x \n\r",i,pid(NULL));
    //gettime(&timet);
    //printf("year:%d mon:%d date:%d hour:%d min:%d sec:%d\n\r",
    //timet.year,timet.mon,timet.date,timet.hour,timet.min,timet.sec);
        ;
    }
    return;
}

void task0_main()
{
    //times_t timet;
    int i=0;
    for(;;)
    {
    i++;
    printfk("task0 run %x\n",i);
    //printf("task0 run %x task0ID:%x \n\r",i,pid(NULL));
    //gettime(&timet);
    //printf("year:%d mon:%d date:%d hour:%d min:%d sec:%d\n\r",
    //timet.year,timet.mon,timet.date,timet.hour,timet.min,timet.sec);
        ;
    }
    return;
}

void task2_main()
{
    /*times_t timet;
    timet.year=14;
    timet.mon=9;
    timet.day=4;

    timet.date=11;
    timet.hour=12;
    timet.min=30;
    timet.sec=00;*/

    //settime(&timet);
    int i=0;
    for(;;)
    {
    i++;
    printf("task2 run %x task2ID:%x \n\r",i,pid(NULL));
    //gettime(&timet);
    //printf("year:%d mon:%d date:%d hour:%d min:%d sec:%d\n\r",timet.year,timet.mon,timet.date,timet.hour,timet.min,timet.sec);
    }
    return;
}

void task3_main()
{

    int i=0;
    for(;;)
    {
    i++;
    printf("task3 run %x task3ID:%x \n\r",i,pid(NULL));
    }
    return;
}
void task4_main()
{

    int i=0;
    for(;;)
    {
    i++;
    printf("task4 run %x task4ID:%x \n\r",i,pid(NULL));
    }
    return;
}



void task5_main()
{
    int i=0;
    for(;;)
    {
    i++;
    printf("task5 run %x task5ID:%x \n\r",i,pid(NULL));
    }
    return;
}
