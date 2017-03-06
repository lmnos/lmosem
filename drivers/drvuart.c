/**********************************************************
        LMOSEM串口驱动文件drvuart.c
***********************************************************
                彭东 ＠ 2013.09.22.11.00
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void uart_set_driver(driver_t* drvp)
{
    drvp->drv_dipfun[IOIF_CODE_OPEN]=uart_open;
    drvp->drv_dipfun[IOIF_CODE_CLOSE]=uart_close;
    drvp->drv_dipfun[IOIF_CODE_READ]=uart_read;
    drvp->drv_dipfun[IOIF_CODE_WRITE]=uart_write;
    drvp->drv_dipfun[IOIF_CODE_LSEEK]=uart_lseek;
    drvp->drv_dipfun[IOIF_CODE_IOCTRL]=uart_ioctrl;
    drvp->drv_dipfun[IOIF_CODE_DEV_START]=uart_dev_start;
    drvp->drv_dipfun[IOIF_CODE_DEV_STOP]=uart_dev_stop;
    drvp->drv_dipfun[IOIF_CODE_SET_POWERSTUS]=uart_set_powerstus;
    drvp->drv_dipfun[IOIF_CODE_ENUM_DEV]=uart_enum_dev;
    drvp->drv_dipfun[IOIF_CODE_FLUSH]=uart_flush;
    drvp->drv_dipfun[IOIF_CODE_SHUTDOWN]=uart_shutdown;
    drvp->drv_name="uartdrv";
    return;
}

void uart0_set_device(device_t* devp,driver_t* drvp)
{
    
    devp->dev_flgs=DEVFLG_SHARE;
    devp->dev_stus=DEVSTS_NORML;
    devp->dev_id.dev_mtype=UART_DEVICE;
    devp->dev_id.dev_stype=0;
    devp->dev_id.dev_nr=0;

    devp->dev_name="uart0";
    return;
}

void init_devuart0()
{
    hal_io32_write(ULCON0_R,3);
    hal_io32_write(UCON0_R,5);
    hal_io32_write(UFCON0_R,0);
    hal_io32_write(UMCON0_R,3);
    hal_io32_write(UBRDIV0_R,26);
    return;
}


drvstus_t uart_entry(driver_t* drvp,uint_t val,void* p)
{
    if(drvp==NULL)
    {
        return DFCERRSTUS;
    }
    device_t* devp=new_device_dsc();
    if(devp==NULL)
    {
        return DFCERRSTUS;
    }
    uart_set_driver(drvp);
    uart0_set_device(devp,drvp);
    if(krldev_add_driver(devp,drvp)==DFCERRSTUS)
    {
        if(del_device_dsc(devp)==DFCERRSTUS)//注意释放资源。
        {
            return DFCERRSTUS;
        }
        return DFCERRSTUS;
    }
    if(krlnew_device(devp)==DFCERRSTUS)
    {
        if(del_device_dsc(devp)==DFCERRSTUS)//注意释放资源
        {
            return DFCERRSTUS;
        }
        return DFCERRSTUS;
    }
    
    if(krlnew_devhandle(devp,uart0_rxd_handle,SINT_IFDNR(URXD0_INT_PHYLINE))==DFCERRSTUS)
    {
       
        return DFCERRSTUS;  //注意释放资源。
    }
    
    if(krlnew_devhandle(devp,uart0_txd_handle,SINT_IFDNR(UTXD0_INT_PHYLINE))==DFCERRSTUS)
    {
       
        return DFCERRSTUS;  //注意释放资源。
    }
    
    if(krlnew_devhandle(devp,uart0_err_handle,SINT_IFDNR(UERR0_INT_PHYLINE))==DFCERRSTUS)
    {
       
        return DFCERRSTUS;  //注意释放资源。
    }
    
    init_devuart0();
    return DFCOKSTUS;
}


drvstus_t uart_exit(driver_t* drvp,uint_t val,void* p)
{
    return DFCERRSTUS;
}

drvstus_t uart0_rxd_handle(uint_t ift_nr,void* devp,void* sframe)
{
   
    printfk("rxd_handle run\n\r");
    return DFCOKSTUS;
}

drvstus_t uart0_txd_handle(uint_t ift_nr,void* devp,void* sframe)
{
    printfk("txd_handle run\n\r");
    return DFCOKSTUS;
}

drvstus_t uart0_err_handle(uint_t ift_nr,void* devp,void* sframe)
{
   
    printfk("err_handle run\n\r");
    return DFCOKSTUS;
}


drvstus_t uart_open(device_t* devp,void* iopack)
{
    return krldev_inc_devcount(devp);
}

drvstus_t uart_close(device_t* devp,void* iopack)
{
    return krldev_dec_devcount(devp);
}

drvstus_t uart_read(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t uart_write(device_t* devp,void* iopack)
{

    uint_t devsn=devp->dev_id.dev_nr,len;
    buf_t retbuf;
    if(krldev_retn_rqueparm(iopack,&retbuf,NULL,&len,NULL,NULL,NULL)==DFCERRSTUS)
    {
        return DFCERRSTUS;
    }
    char_t* p=(char_t*)retbuf;
    for(uint_t bi=0;bi<=len;bi++)
    {
        if(uartdev_send_char(devsn,p[bi])==DFCERRSTUS)
        {
            return DFCERRSTUS;
        }
    }
    return DFCOKSTUS;
}

drvstus_t uart_lseek(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t uart_ioctrl(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t uart_dev_start(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t uart_dev_stop(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t uart_set_powerstus(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t uart_enum_dev(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t uart_flush(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t uart_shutdown(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t uartdev_send_char(uint_t uart,char_t ch)
{
    uint_t time=0;
    if(uart!=0)
    {
        return  DFCERRSTUS;
    }
    while(!(hal_io32_read(UTRSTAT0_R)&4))
    {
        if(time>0x100000)
        {
            return DFCERRSTUS;
        }
        time++;    
    }
    hal_io32_write(UTXH0_R,ch);
    
    return DFCOKSTUS;
}
