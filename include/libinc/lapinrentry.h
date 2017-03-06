#ifndef _LAPINRENTRY_H
#define _LAPINRENTRY_H

#ifdef CFG_S3C2440A_PLATFORM

#define API_ENTRY_PARE1(swinr,rets,pval1) \
__asm__ __volatile__(\
         "mov r0,%[snr] \n\t"\
         "mov r1,%[prv1] \n\t"\
         "swi 0 \n\t"\
         "mov %[retval],r0 \n\t"\
         :[retval] "=r" (rets)\
         :[snr] "r" (swinr),[prv1]"r" (pval1)\
         :"r0","r1","lr","cc","memory"\
    )

#define API_ENTRY_PARE2(swinr,rets,pval1,pval2) \
__asm__ __volatile__(\
         "mov r0,%[snr] \n\t"\
         "mov r1,%[prv1] \n\t"\
         "mov r2,%[prv2] \n\t"\
         "swi 0 \n\t"\
         "mov %[retval],r0 \n\t"\
         :[retval] "=r" (rets)\
         :[snr] "r" (swinr),[prv1]"r" (pval1),\
         [prv2] "r" (pval2)\
         :"r0","r1","r2","lr","cc","memory"\
    )
    
    
#define API_ENTRY_PARE3(swinr,rets,pval1,pval2,pval3) \
__asm__ __volatile__(\
         "mov r0,%[snr] \n\t"\
         "mov r1,%[prv1] \n\t"\
         "mov r2,%[prv2] \n\t"\
         "mov r3,%[prv3] \n\t"\
         "swi 0 \n\t"\
         "mov %[retval],r0 \n\t"\
         :[retval] "=r" (rets)\
         :[snr] "r" (swinr),[prv1]"r" (pval1),\
         [prv2] "r" (pval2),[prv3]"r" (pval3)\
         :"r0","r1","r2","r3","lr","cc","memory"\
    )

#define API_ENTRY_PARE4(swinr,rets,pval1,pval2,pval3,pval4) \
__asm__ __volatile__(\
         "mov r0,%[snr] \n\t"\
         "mov r1,%[prv1] \n\t"\
         "mov r2,%[prv2] \n\t"\
         "mov r3,%[prv3] \n\t"\
         "mov r4,%[prv4] \n\t"\
         "swi 0 \n\t"\
         "mov %[retval],r0 \n\t"\
         :[retval] "=r" (rets)\
         :[snr] "r" (swinr),[prv1]"r" (pval1),\
         [prv2] "r" (pval2),[prv3]"r" (pval3),\
         [prv4] "r" (pval4)\
         :"r0","r1","r2","r3","r4","lr","cc","memory"\
    )
#define API_ENTRY_PARE5(swinr,rets,pval1,pval2,pval3,pval4,pval5) \
__asm__ __volatile__(\
         "mov r0,%[snr] \n\t"\
         "mov r1,%[prv1] \n\t"\
         "mov r2,%[prv2] \n\t"\
         "mov r3,%[prv3] \n\t"\
         "mov r4,%[prv4] \n\t"\
         "mov r5,%[prv5] \n\t"\
         "swi 0 \n\t"\
         "mov %[retval],r0 \n\t"\
         :[retval] "=r" (rets)\
         :[snr] "r" (swinr),[prv1]"r" (pval1),\
         [prv2] "r" (pval2),[prv3]"r" (pval3),\
         [prv4] "r" (pval4),[prv5]"r" (pval4)\
         :"r0","r1","r2","r3","r4","r5","lr","cc","memory"\
    )
#endif


/*;Push(EAX);
;Push(ECX);
;Push(EDX);
;Push(EBX);
;Push(Temp);
;Push(EBP);
;Push(ESI);
;Push(EDI);
*/
#ifdef CFG_X86_PLATFORM

#define API_ENTRY_PARE1(swinr,rets,pval1) \
__asm__ __volatile__(\
         "movl %[snr],%%eax\n\t"\
         "movl %[prv1],%%ecx\n\t"\
         "int $255 \n\t"\
         "movl %%eax,%[retval] \n\t"\
         :[retval] "=r" (rets)\
         :[snr] "r" (swinr),[prv1]"r" (pval1)\
         :"eax","ecx","cc","memory"\
    )

#define API_ENTRY_PARE2(swinr,rets,pval1,pval2) \
__asm__ __volatile__(\
         "movl %[snr],%%eax \n\t"\
         "movl %[prv1],%%ecx \n\t"\
         "movl %[prv2],%%edx \n\t"\
         "int $255 \n\t"\
         "movl %%eax,%[retval] \n\t"\
         :[retval] "=r" (rets)\
         :[snr] "r" (swinr),[prv1]"r" (pval1),\
         [prv2] "r" (pval2)\
         :"eax","ecx","edx","cc","memory"\
    )
    
    
#define API_ENTRY_PARE3(swinr,rets,pval1,pval2,pval3) \
__asm__ __volatile__(\
         "movl %[snr],%%eax \n\t"\
         "movl %[prv1],%%ecx \n\t"\
         "movl %[prv2],%%edx \n\t"\
         "movl %[prv3],%%ebx \n\t"\
         "int $255 \n\t"\
         "movl %%eax,%[retval] \n\t"\
         :[retval] "=r" (rets)\
         :[snr] "r" (swinr),[prv1]"g" (pval1),\
         [prv2] "g" (pval2),[prv3]"g" (pval3)\
         :"eax","ecx","edx","ebx","cc","memory"\
    )

#define API_ENTRY_PARE4(swinr,rets,pval1,pval2,pval3,pval4) \
__asm__ __volatile__(\
         "movl %[snr],%%eax \n\t"\
         "movl %[prv1],%%ecx \n\t"\
         "movl %[prv2],%%edx \n\t"\
         "movl %[prv3],%%ebx \n\t"\
         "movl %[prv4],%%esi \n\t"\
         "int $255 \n\t"\
         "movl %%eax,%[retval] \n\t"\
         :[retval] "=r" (rets)\
         :[snr] "r" (swinr),[prv1]"g" (pval1),\
         [prv2] "g" (pval2),[prv3]"g" (pval3),\
         [prv4] "g" (pval4)\
         :"eax","ecx","edx","ebx","esi","cc","memory"\
    )

#endif

#endif // LAPINRENTRY_H
