/**********************************************************
        LMOSEM内核服务头文件krlsveioctrl.h
***********************************************************
                彭东 ＠ 2013.09.17.09.30
**********************************************************/
#ifndef _KRLSVEIOCTRL_H
#define _KRLSVEIOCTRL_H
sysstus_t krlsvetabl_ioctrl(uint_t swinr,stkparame_t* stkparv);
sysstus_t krlsve_ioctrl(hand_t fhand,buf_t buf,uint_t iocode,uint_t flgs);
sysstus_t krlsve_core_ioctrl(hand_t fhand,buf_t buf,uint_t iocode,uint_t flgs);
sysstus_t krlsve_ioctrl_device(objnode_t* ondep);
#endif // KRLSVEIOCTRL_H
