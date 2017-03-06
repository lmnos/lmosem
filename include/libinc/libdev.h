#ifndef LIBDEV_H
#define LIBDEV_H
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

typedef struct s_DEVID
{
    uint_t  dev_mtype;
    uint_t  dev_stype;
    uint_t  dev_nr;
}devid_t;

#endif // LIBDEV_H
