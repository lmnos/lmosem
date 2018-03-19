/**********************************************************
    c标准库 - 字符类别判断
***********************************************************
     颜文泽 @ 2018.3.19.21.00
**********************************************************/

#ifndef _CTYPE_T_H
#define _CTYPE_T_H

#define	T_U	    0x01 // 大写字母
#define	T_L     0x02 // 小写字母
#define	T_N     0x04 // 数字
#define	T_S	    0x08 // 空白符
#define T_P	    0x10 // 可打印字符
#define T_C	    0x20 // 控制字符
#define	T_X	    0x40 // 16进制字母
#define T_LIM   0xFF

char charList[] = {
    T_C, T_C, T_C, T_C, T_C, T_C, T_C, T_C,
    T_C, T_S, T_S, T_S, T_S, T_S, T_C, T_C,
    T_C, T_C, T_C, T_C, T_C, T_C, T_C, T_C,
    T_C, T_C, T_C, T_C, T_C, T_C, T_C, T_C,
    T_S, T_P, T_P, T_P, T_P, T_P, T_P, T_P,
    T_P, T_P, T_P, T_P, T_P, T_P, T_P, T_P,
    T_N, T_N, T_N, T_N, T_N, T_N, T_N, T_N,
    T_N, T_N, T_P, T_P, T_P, T_P, T_P, T_P,
    T_P, T_U|T_X, T_U|T_X, T_U|T_X, T_U|T_X, T_U|T_X, T_U|T_X, T_U,
    T_U, T_U, T_U, T_U, T_U, T_U, T_U, T_U,
    T_U, T_U, T_U, T_U, T_U, T_U, T_U, T_U,
    T_U, T_U, T_U, T_P, T_P, T_P, T_P, T_P,
    T_P, T_L|T_X, T_L|T_X, T_L|T_X, T_L|T_X, T_L|T_X, T_L|T_X, T_L,
    T_L, T_L, T_L, T_L, T_L, T_L, T_L, T_L,
    T_L, T_L, T_L, T_L, T_L, T_L, T_L, T_L,
    T_L, T_L, T_L, T_P, T_P, T_P, T_P, T_C,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
};

#define	isalpha(c)	(charList[(c) & T_LIM] & (T_U|T_L))
#define	isupper(c)	(charList[(c) & T_LIM] & T_U)
#define	islower(c)	(charList[(c) & T_LIM] & T_L)
#define	isdigit(c)	(charList[(c) & T_LIM] & T_N)
#define	isxdigit(c)	(charList[(c) & T_LIM] & (T_N|T_X))
#define	isspace(c)	(charList[(c) & T_LIM] & T_S)
#define ispunct(c)	(charList[(c) & T_LIM] & T_P)
#define isalnum(c)	(charList[(c) & T_LIM] & (T_U|T_L|T_N))
#define isprint(c)	(charList[(c) & T_LIM] & (T_P|T_U|T_L|T_N))
#define iscntrl(c)	(charList[(c) & T_LIM] & T_C)
#define toupper(c)  (islower(c) ? (c) - 'a' + 'A' : (c))
#define tolower(c)  (isupper(c) ? (c) - 'A' + 'a' : (c))

#endif
