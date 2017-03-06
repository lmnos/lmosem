/**********************************************************
        LMOSEM设备管理头文件krldevice_t.h
***********************************************************
                彭东 ＠ 2013.08.16.15.30
**********************************************************/
#ifndef _KRLDEVICE_T_H
#define _KRLDEVICE_T_H



#define NOT_DEVICE 0
#define AMBABUS_DEVICE 1
#define AHBBUS_DEVICE 2
#define APBBUS_DEVICE 3
#define BRIDGE_DEVICE 4
#define CPUCORE_DEVICE 5
#define RAMCONTER_DEVICE 6
#define RAM_DEVICE 7
#define USBHOSTCONTER_DEVICE 8
#define INTUPTCONTER_DEVICE 9
#define DMA_DEVICE 10
#define CLOCKPOWER_DEVICE 11
#define LCDCONTER_DEVICE 12
#define NANDFLASH_DEVICE 13
#define CAMERA_DEVICE 14
#define UART_DEVICE 15
#define TIMER_DEVICE 16
#define USB_DEVICE 17
#define WATCHDOG_DEVICE 18
#define IIC_DEVICE 19
#define IIS_DEVICE 20
#define GPIO_DEVICE 21
#define RTC_DEVICE 22
#define A_DCONVER_DEVICE 23
#define SPI_DEVICE 24
#define SD_DEVICE 25
#define AUDIO_DEVICE 26
#define TOUCH_DEVICE 27
#define NETWORK_DEVICE 28
#define VIR_DEVICE 29
#define FILESYS_DEVICE 30
#define SYSTICK_DEVICE 31
#define UNKNOWN_DEVICE 32

#define DEVICE_MAX 33

#define IOIF_CODE_OPEN 0 //对应于open操作
#define IOIF_CODE_CLOSE 1 //对应于close操作
#define IOIF_CODE_READ 2 //对应于read操作
#define IOIF_CODE_WRITE 3 //对应于write操作
#define IOIF_CODE_LSEEK 4 //对应于lseek操作
#define IOIF_CODE_IOCTRL 5 //对应于ioctrl操作
#define IOIF_CODE_DEV_START 6 //对应于start操作
#define IOIF_CODE_DEV_STOP 7 //对应于stop操作
#define IOIF_CODE_SET_POWERSTUS 8 //对应于powerstus操作
#define IOIF_CODE_ENUM_DEV 9 //对应于enum操作
#define IOIF_CODE_FLUSH 10 //对应于flush操作
#define IOIF_CODE_SHUTDOWN 11 //对应于shutdown操作
#define IOIF_CODE_MAX 12 //最大功能码

#define DEVFLG_EXCLU (1<<0)
#define DEVFLG_SHARE (1<<1)
#define DEVSTS_NORML (1<<0)
#define DEVSTS_FAILU (1<<1)
#define DIDFIL_IDN 1
#define DIDFIL_FLN 2

#define FSDEV_IOCTRCD_DELFILE 5
#define FSDEV_OPENFLG_NEWFILE 1
#define FSDEV_OPENFLG_OPEFILE 2


typedef struct s_DEVID
{
    uint_t  dev_mtype;
    uint_t  dev_stype;
    uint_t  dev_nr;
}devid_t;

typedef struct s_DEVTLST
{
    uint_t dtl_type;
    uint_t dtl_nr;
    list_h_t dtl_list;
}devtlst_t;



typedef struct s_DEVTABLE
{
    list_h_t devt_list;
    spinlock_t devt_lock;
    list_h_t devt_devlist;
    list_h_t devt_drvlist;
    uint_t   devt_devnr;
    uint_t   devt_drvnr;
    devtlst_t devt_devclsl[DEVICE_MAX];
}devtable_t;



 
typedef struct s_DEVICE
{
    list_h_t    dev_list;
    list_h_t    dev_indrvlst;
    list_h_t    dev_intbllst;
    spinlock_t  dev_lock;
    uint_t      dev_count;
    sem_t       dev_sem;
    uint_t      dev_stus;
    uint_t      dev_flgs;
    devid_t      dev_id;
    uint_t      dev_intlnenr;
    list_h_t    dev_intserlst;
    list_h_t    dev_rqlist;
    uint_t      dev_rqlnr;
    sem_t       dev_waitints;
    struct s_DRIVER* dev_drv;
    void* dev_attrb; 
    void* dev_privdata;
    void* dev_userdata;
    void* dev_extdata;
    char_t* dev_name; 
}device_t;


typedef drvstus_t (*drivcallfun_t)(device_t*,void*);
typedef drvstus_t (*drventyexit_t)(struct s_DRIVER*,uint_t,void*);
typedef struct s_DRIVER
{
    spinlock_t drv_lock;
    list_h_t drv_list;
    uint_t drv_stuts;
    uint_t drv_flg;
    uint_t drv_id;
    uint_t drv_count; //驱动的计数。
    sem_t drv_sem; //驱动的信号量
    void* drv_safedsc; //驱动的安全体
    void* drv_attrb; //内核要求的驱动属性体，
    void* drv_privdata; //驱动私有数据的指针。
    drivcallfun_t drv_dipfun[IOIF_CODE_MAX]; //驱动程序分派函数指针数组。
    list_h_t drv_alldevlist; //驱动所管理的所有设备。
    drventyexit_t drv_entry;
    drventyexit_t drv_exit;
    void* drv_userdata;
    void* drv_extdata;
    char_t* drv_name; //驱动程序的名字。
}driver_t;



#endif // KRLDEVICE_T_H
