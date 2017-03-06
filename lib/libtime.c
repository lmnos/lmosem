#include "libc.h"
#include "libdev.h"
sysstus_t time(times_t* ttime)
{
    sysstus_t rets=api_time(ttime);
    return rets;
}

sysstus_t settime(times_t* ttime)
{

    if(ttime==NULL)
    {
        return SYSSTUSERR;
    }
    devid_t dev;
    dev.dev_mtype=RTC_DEVICE;
    dev.dev_stype=0;
    dev.dev_nr=0;
    hand_t fd=open(&dev,RW_FLG|FILE_TY_DEV,0);
    if(fd==-1)
    {   
        return SYSSTUSERR;
    }
    
    ioctrl(fd,ttime,IOCTRCODE_SETTIME,0);
    
    close(fd);
    
    return SYSSTUSOK;
}


sysstus_t gettime(times_t* ttime)
{
    if(ttime==NULL)
    {
        return SYSSTUSERR;
    }
    devid_t dev;
    dev.dev_mtype=RTC_DEVICE;
    dev.dev_stype=0;
    dev.dev_nr=0;
    hand_t fd=open(&dev,RW_FLG|FILE_TY_DEV,0);
    if(fd==-1)
    {   
        return SYSSTUSERR;
    }
    
    read(fd,ttime,sizeof(times_t),0);
    
    close(fd);
    
    return SYSSTUSOK;
}

sysstus_t synsecalarm(uint_t sec)
{
    uint_t tmpsec=sec;
    if(tmpsec>=60)
    {
        return SYSSTUSERR;
    }
    
    devid_t dev;
    dev.dev_mtype=RTC_DEVICE;
    dev.dev_stype=0;
    dev.dev_nr=0;
    hand_t fd=open(&dev,RW_FLG|FILE_TY_DEV,0);
    if(fd==-1)
    {   
        return SYSSTUSERR;
    }
    
    ioctrl(fd,&tmpsec,IOCTRCODE_SET_SYNSECALM,0);
    
    close(fd);
    return SYSSTUSOK;
}

