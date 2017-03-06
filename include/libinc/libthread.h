#ifndef LIBTHREAD_H
#define LIBTHREAD_H
hand_t exel(void* file,uint_t flgs);
void exit();
hand_t pid(void* tname);
sysstus_t retn_threadstats(hand_t thand,uint_t scode,uint_t data,buf_t buf);
sysstus_t set_threadstats(hand_t thand,uint_t scode,uint_t data,buf_t buf);
#endif
