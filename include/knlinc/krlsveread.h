/**********************************************************
        LMOSEM内核服务头文件krlsveread.h
***********************************************************
                彭东 ＠ 2013.09.17.09.30
**********************************************************/
#ifndef _KRLSVEREAD_H
#define _KRLSVEREAD_H
sysstus_t krlsvetabl_read(uint_t swinr,stkparame_t* stkparv);
sysstus_t krlsve_read(hand_t fhand,buf_t buf,size_t len,uint_t flgs);
sysstus_t krlsve_core_read(hand_t fhand,buf_t buf,size_t len,uint_t flgs);
sysstus_t krlsve_read_device(objnode_t* ondep);
#endif // KRLSVEREAD_H
