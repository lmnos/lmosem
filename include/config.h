/****************************************************************
        LMOSEM全局配置头文件config.h
*****************************************************************
                彭东 ＠ 2013.06.30.18.45
****************************************************************/
#ifndef _CONFIG_H
#define _CONFIG_H

#define CFG_S3C2440A_PLATFORM
//#define CFG_X86_PLATFORM

#if defined(CFG_S3C2440A_PLATFORM) || defined(CFG_X86_PLATFORM)
// do nothing
#else
#define CFG_S3C2440A_PLATFORM
#endif

#endif
