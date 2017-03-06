/**********************************************************
        LMOSEM内核服务头文件krlsvewrite.h
***********************************************************
                彭东 ＠ 2013.09.17.09.30
**********************************************************/
#ifndef _KRLSVEWRITE_H
#define _KRLSVEWRITE_H
sysstus_t krlsvetabl_write(uint_t swinr,stkparame_t* stkparv);
sysstus_t krlsve_write(hand_t fhand,buf_t buf,size_t len,uint_t flgs);
sysstus_t krlsve_core_write(hand_t fhand,buf_t buf,size_t len,uint_t flgs);
sysstus_t krlsve_write_device(objnode_t* ondep);
#endif // KRLSVEWRITE_H
