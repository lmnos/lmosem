/**********************************************************
    c标准库 - 字符串
***********************************************************
     颜文泽 @ 2018.3.19.21.00
**********************************************************/


#ifndef _STRING_T_H
#define _STRING_T_H

#include    "bastype_t.h"

char    *strcpy(char *a, char *b);
char    *strncpy(char *a , char *b, size_t n);

char    *strcat(char *a, char *b);
char    *strncat(char *a, char *b, size_t n);

int     strcmp(const char *a, const char *b);
int     strncmp(const char *a, const char *b, size_t n);

char    *strchr(const char *a, int b);
char    *strrchr(const char *a, int b);

size_t  strspn(const char *a, const char *b);
size_t  strcspn(const char *a, const char *b);

char    *strpbrk(const char *a, const char *b);

char    *strstr(const char *a, const char *b);

size_t  strlen(const char *s);

char    *strtok(char *a, char *b);

void    *memcpy(void *a, const void *b, size_t n);
void    *memmove(void *a, const void *b, size_t n);

int     memcmp(const void *a, const void *b, size_t n);

void    *memchr(const void *a, int b, size_t n);
void    *memrchr(const void *a, int b, size_t n);

void    *memset(void *a, int b, size_t n);

#endif
