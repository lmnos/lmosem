/**********************************************************
        LMOSEMRTC驱动头文件drvrtc.h
***********************************************************
                彭东 ＠ 2013.09.30.12.10
**********************************************************/
#ifndef _DRVRTC_H
#define _DRVRTC_H
void rtc_set_driver(driver_t* drvp);
void rtc_set_device(device_t* devp,driver_t* drvp);
void init_rtc();
drvstus_t rtc_entry(driver_t* drvp,uint_t val,void* p);
drvstus_t rtc_exit(driver_t* drvp,uint_t val,void* p);
drvstus_t rtc_handle(uint_t ift_nr,void* devp,void* sframe);
drvstus_t rtc_tick_handle(uint_t ift_nr, void *devp, void *sframe);
drvstus_t rtc_open(device_t* devp,void* iopack);
drvstus_t rtc_close(device_t* devp,void* iopack);
drvstus_t rtc_read(device_t* devp,void* iopack);
drvstus_t rtc_write(device_t* devp,void* iopack);
drvstus_t rtc_lseek(device_t* devp,void* iopack);
drvstus_t rtc_ioctrl(device_t* devp,void* iopack);
drvstus_t rtc_dev_start(device_t* devp,void* iopack);
drvstus_t rtc_dev_stop(device_t* devp,void* iopack);
drvstus_t rtc_set_powerstus(device_t* devp,void* iopack);
drvstus_t rtc_enum_dev(device_t* devp,void* iopack);
drvstus_t rtc_flush(device_t* devp,void* iopack);
drvstus_t rtc_shutdown(device_t* devp,void* iopack);
#endif // DRVRTC_H
