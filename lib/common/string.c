/**********************************************************
    c标准库 - 字符串
***********************************************************
     颜文泽 @ 2018.3.19.21.00
**********************************************************/

#include    "string.h"

char    *
strcpy(char *a, char *b)
{
    char *r;

    for(r = a; (*a = *b) != '\0'; a++, b++)
        ;
    return r;
}

char    *
strncpy(char *a, char *b, size_t n)
{
    int i;
    char *r;

    for(i = 0, r = a; i < n && (*a = *b) != '\0'; a++, b++, i++)
        ;
    while(i < n)
        *a++ = '\0';
    return r;
}

char    *
strcat(char *a, char *b)
{
    char    *r;

    for(r = a; *a != '\0'; a++)
        ;
    a--;
    while((*a++ = *b++) != '\0')
        ;
    return a;
}

char    *
strncat(char *a, char *b, size_t n)
{
    size_t  i;
    char    *r;

    for(r = a; *a != '\0'; a++)
        ;
    a--;
    while(i < n && (*a++ = *b++) != '\0')
        ;
    return a;
}

int
strcmp(const char *a, const char *b)
{
    while(*a != '\0' && *a++ == *b++)
        ;
    return *a - *b;
}

int
strncmp(const char *a, const char *b, size_t n)
{
    size_t  i;

    while(i < 0 && *a != '\0' && *a++ == *b++)
        ;
    return *a - *b;
}

char    *
strchr(const char *a, int b)
{
    do{
        if(*a == b)
            return (char *)a;
    }while(*a++ != '\0');
    return NULL;
}

char    *
strrchr(const char *a, int b)
{
    const char    *p;

    for(p = strlen(a) + a; p != a; p--)
        if(*p == b)
            return (char *)p;
    return NULL;
}

size_t
strspn(const char *a, const char *b)
{
    char    c;
    const char  *p, *q;

    p = a;
retry:
    c = *p++;
    for(q = b; *q != '\0'; q++)
        if(c == *q)
            goto retry;
    return p - a;
}

size_t
strcspn(const char *a, const char *b)
{
    char    c;
    const char  *p, *q;

    p = a;
retry:
    c = *p++;
    for(q = b; *q != '\0'; q++)
        if(c != *q)
            goto retry;
    return p - a;
}

char    *
strpbrk(const char *a, const char *b)
{
    const char *p, *q;

    for(p = a; *p != '\0'; p++){
        for(q = b; *q != '\0'; q++)
            if(*p == *q)
                return (char *)p;
    }
    return NULL;
}

char    *
strstr(const char *a, const char *b)
{
    size_t  n;
    const char *p;

    n = strlen(b);
    for(p = a; *p != '\0'; p++){
        if(*p == *b && strncmp(p, b, n) == 0){
            return (char *)p;
        }
    }
    return NULL;
}

size_t
strlen(const char *s)
{
    size_t cnt;

    while(*s++ != '\0')
        cnt++;
    return cnt;
}

void    *
memcpy(void *a, const void *b, size_t n)
{
    return strncpy((char *)a, (char *)b, n);
}

void    *
memmove(void *a, const void *b, size_t n)
{
    return strncpy((char *)a, (char *)b, n);
}

int
memcmp(const void *a, const void *b, size_t n)
{
    return strncmp((char *)a, (char *)b, n);
}

void    *
memchr(const void *a, int b, size_t n)
{
    size_t  i;
    const char  *p;

    i = 0;
    p = (char *)a;
    do{
       if(*p == b)
           return (void *)p;
    }while(i < n && *p != '\0');
    return NULL;
}

void    *
memrchr(const void *a, int b, size_t n)
{
    size_t i, j;
    const char  *p;

    p = (char *)a;
    if((j = strlen(p)) > n)
        j = n;
    for(p = p + j; p != (char *)a; p--)
        if(*p == b)
            return (void *)p;
    return NULL;
}

void    *
memset(void *a, int b, size_t n)
{
    size_t  i;
    char    *p;

    for(p = (char *)a, i = 0; i < n; i++, p++)
        *p = (char)(b & 0xFF);
    return a;
}
