/****************************************************************
        LMOSEM kernel全局数据结构头文件krlglobal_t.h
*****************************************************************
                彭东 ＠ 2013.07.18.16.50
****************************************************************/
#ifndef _KRLGLOBAL_T_H
#define _KRLGLOBAL_T_H
#define KRL_DEFGLOB_VARIABLE(vartype,varname) \
KEXTERN  __attribute__((section(".data"))) vartype varname
#endif // KRLGLOBAL_T_H
