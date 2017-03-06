/**********************************************************
        LMOSEM内核服务头文件krlsveopen.h
***********************************************************
                彭东 ＠ 2013.09.17.09.30
**********************************************************/
#ifndef _KRLSVEOPEN_H
#define _KRLSVEOPEN_H
sysstus_t krlsvetabl_open(uint_t swinr,stkparame_t* stkparv);
hand_t krlsve_open(void* file,uint_t flgs,uint_t stus);
hand_t krlsve_core_open(void* file,uint_t flgs,uint_t stus);
sysstus_t krlsve_open_device(objnode_t* ondep);
#endif // KRLSVEOPEN_H
