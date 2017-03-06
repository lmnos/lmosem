#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void rfsdevext_t_init(rfsdevext_t* initp)
{
    hal_spinlock_init(&initp->rde_lock);
    list_init(&initp->rde_list);
    initp->rde_flg=0;
    initp->rde_stus=0;
    initp->rde_mstart=NULL;
    initp->rde_msize=0;
    initp->rde_ext=NULL;
    return;
}

void rfsdir_t_init(rfsdir_t* initp)
{
    initp->rdr_stus=0;
    initp->rdr_type=RDR_NUL_TYPE;
    initp->rdr_blknr=0;
    for(uint_t i=0;i<DR_NM_MAX;i++)
    {
        initp->rdr_name[i]=0;
    }
    return;
}

void filblks_t_init(filblks_t* initp)
{
    initp->fb_blkstart=0;
    initp->fb_blknr=0;
    return;
}

void rfssublk_t_init(rfssublk_t* initp)
{
    hal_spinlock_init(&initp->rsb_lock);
    initp->rsb_mgic=0x142422;
    initp->rsb_vec=1;
    initp->rsb_flg=0;
    initp->rsb_stus=0;
    initp->rsb_sz=sizeof(rfssublk_t);
    initp->rsb_sblksz=1;
    initp->rsb_dblksz=FSYS_ALCBLKSZ;
    initp->rsb_bmpbks=1;
    initp->rsb_bmpbknr=0;
    initp->rsb_fsysallblk=0;
    rfsdir_t_init(&initp->rsb_rootdir);
    return;
}
void fimgrhd_t_init(fimgrhd_t* initp)
{
    initp->fmd_stus=0;
    initp->fmd_type=FMD_NUL_TYPE;
    initp->fmd_flg=0;
    initp->fmd_sfblk=0;
    initp->fmd_acss=0;
    initp->fmd_newtime=0;
    initp->fmd_acstime=0;
    initp->fmd_fileallbk=0;
    initp->fmd_filesz=0;
    initp->fmd_fileifstbkoff=0x200;
    initp->fmd_fileiendbkoff=0;
    initp->fmd_curfwritebk=0;
    initp-> fmd_curfinwbkoff=0;
    for(uint_t i=0;i<FBLKS_MAX;i++)
    {
        filblks_t_init(&initp->fmd_fleblk[i]);
    }
    initp->fmd_linkpblk=0;
    initp->fmd_linknblk=0;
    return;
}

drvstus_t new_rfsdevext_mmblk(device_t* devp,size_t blksz)
{
    adr_t blkp= krlnew(blksz);
    rfsdevext_t* rfsexp=(rfsdevext_t*)krlnew(sizeof(rfsdevext_t));
    if(blkp==NULL||rfsexp==NULL)
    {
        return DFCERRSTUS;
    }
    rfsdevext_t_init(rfsexp);
    rfsexp->rde_mstart=(void*)blkp;
    rfsexp->rde_msize=blksz;
    devp->dev_extdata=(void*)rfsexp;
    return DFCOKSTUS;
}

rfsdevext_t* ret_rfsdevext(device_t* devp)
{
    return (rfsdevext_t*)devp->dev_extdata;
}

void* ret_rfsdevblk(device_t* devp,uint_t blknr)
{
    rfsdevext_t* rfsexp=ret_rfsdevext(devp);
    void* blkp=rfsexp->rde_mstart+(blknr*FSYS_ALCBLKSZ);
    if(blkp>=(void*)((size_t)rfsexp->rde_mstart+rfsexp->rde_msize))
    {
        return NULL;
    }
    return blkp;
}

uint_t ret_rfsdevmaxblknr(device_t *devp)
{
    rfsdevext_t* rfsexp=ret_rfsdevext(devp);
    return (uint_t)(((size_t)rfsexp->rde_msize)/FSYS_ALCBLKSZ);
}

drvstus_t read_rfsdevblk(device_t* devp,void* rdadr,uint_t blknr)
{
    void* p=ret_rfsdevblk(devp,blknr);
    if(p==NULL)
    {
        return DFCERRSTUS;
    }
    hal_memcpy(p,rdadr,FSYS_ALCBLKSZ);
    return DFCOKSTUS;
}

drvstus_t write_rfsdevblk(device_t* devp,void* weadr,uint_t blknr)
{
    void* p=ret_rfsdevblk(devp,blknr);
    if(p==NULL)
    {
        return DFCERRSTUS;
    }
    hal_memcpy(weadr,p,FSYS_ALCBLKSZ);
    return DFCOKSTUS;
}

void* new_buf(size_t bufsz)
{
    return (void*)krlnew(bufsz);
}

void del_buf(void* buf,size_t bufsz)
{
    if(krldelete((adr_t)buf,bufsz)==FALSE)
    {
        hal_sysdie("del buf err");
    }
    return;
}

void rfs_set_driver(driver_t* drvp)
{
    drvp->drv_dipfun[IOIF_CODE_OPEN]=rfs_open;
    drvp->drv_dipfun[IOIF_CODE_CLOSE]=rfs_close;
    drvp->drv_dipfun[IOIF_CODE_READ]=rfs_read;
    drvp->drv_dipfun[IOIF_CODE_WRITE]=rfs_write;
    drvp->drv_dipfun[IOIF_CODE_LSEEK]=rfs_lseek;
    drvp->drv_dipfun[IOIF_CODE_IOCTRL]=rfs_ioctrl;
    drvp->drv_dipfun[IOIF_CODE_DEV_START]=rfs_dev_start;
    drvp->drv_dipfun[IOIF_CODE_DEV_STOP]=rfs_dev_stop;
    drvp->drv_dipfun[IOIF_CODE_SET_POWERSTUS]=rfs_set_powerstus;
    drvp->drv_dipfun[IOIF_CODE_ENUM_DEV]=rfs_enum_dev;
    drvp->drv_dipfun[IOIF_CODE_FLUSH]=rfs_flush;
    drvp->drv_dipfun[IOIF_CODE_SHUTDOWN]=rfs_shutdown;
    drvp->drv_name="rfsdrv";
    return;
}

void rfs_set_device(device_t* devp,driver_t* drvp)
{

    devp->dev_flgs=DEVFLG_SHARE;
    devp->dev_stus=DEVSTS_NORML;
    devp->dev_id.dev_mtype=FILESYS_DEVICE;
    devp->dev_id.dev_stype=0;
    devp->dev_id.dev_nr=0;

    devp->dev_name="rfs";
    return;
}


drvstus_t rfs_entry(driver_t* drvp,uint_t val,void* p)
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
    rfs_set_driver(drvp);
    rfs_set_device(devp,drvp);
    if(new_rfsdevext_mmblk(devp,FSMM_BLK)==DFCERRSTUS)
    {
        if(del_device_dsc(devp)==DFCERRSTUS)//注意释放资源。
        {
            return DFCERRSTUS;
        }
        return DFCERRSTUS;
    }
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
    init_rfs(devp);
    return DFCOKSTUS;
}
drvstus_t rfs_exit(driver_t* drvp,uint_t val,void* p)
{
    return DFCERRSTUS;
}



drvstus_t rfs_open(device_t* devp,void* iopack)
{
    objnode_t* obp=(objnode_t*)iopack;

    if(obp->on_acsflgs==FSDEV_OPENFLG_OPEFILE)
    {
        return rfs_open_file(devp,iopack);
    }
    if(obp->on_acsflgs==FSDEV_OPENFLG_NEWFILE)
    {
        return rfs_new_file(devp,obp->on_fname,0);
    }

    return DFCERRSTUS;
}

drvstus_t rfs_close(device_t* devp,void* iopack)
{
    return rfs_close_file(devp,iopack);
}

drvstus_t rfs_read(device_t* devp,void* iopack)
{
    return rfs_read_file(devp,iopack);
}

drvstus_t rfs_write(device_t* devp,void* iopack)
{
    return rfs_write_file(devp,iopack);
}

drvstus_t rfs_lseek(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t rfs_ioctrl(device_t* devp,void* iopack)
{
    objnode_t* obp=(objnode_t*)iopack;
    if(obp->on_ioctrd==FSDEV_IOCTRCD_DELFILE)
    {

        return rfs_del_file(devp,obp->on_fname,0);
    }
    return DFCERRSTUS;
}

drvstus_t rfs_dev_start(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t rfs_dev_stop(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t rfs_set_powerstus(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t rfs_enum_dev(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t rfs_flush(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t rfs_shutdown(device_t* devp,void* iopack)
{
    return DFCERRSTUS;
}

drvstus_t rfs_new_file(device_t* devp,char_t* fname,uint_t flg)
{
    char_t fne[DR_NM_MAX];
    hal_memset((void*)fne,DR_NM_MAX,0);
    if(rfs_ret_fname(fne,fname)!=0)
    {
        return DFCERRSTUS;
    }
    if(rfs_chkfileisindev(devp,fne)!=0)
    {
        return DFCERRSTUS;
    }

    return rfs_new_dirfileblk(devp,fne,RDR_FIL_TYPE,0);
}

drvstus_t rfs_del_file(device_t* devp,char_t* fname,uint_t flg)
{
    if(flg!=0)
    {
        return DFCERRSTUS;
    }
    drvstus_t rets=rfs_del_dirfileblk(devp,fname,RDR_FIL_TYPE,0);
    return rets;
}

drvstus_t rfs_read_file(device_t* devp,void* iopack)
{
    objnode_t* obp=(objnode_t*)iopack;
    if(obp->on_finode==NULL||obp->on_buf==NULL||
            obp->on_bufsz!=FSYS_ALCBLKSZ)
    {
        return DFCERRSTUS;
    }
    return rfs_readfileblk(devp,(fimgrhd_t*)obp->on_finode,obp->on_buf,obp->on_len);

}

drvstus_t rfs_write_file(device_t* devp,void* iopack)
{
    objnode_t* obp=(objnode_t*)iopack;
    if(obp->on_finode==NULL||obp->on_buf==NULL||
            obp->on_bufsz!=FSYS_ALCBLKSZ)
    {
        return DFCERRSTUS;
    }
    return rfs_writefileblk(devp,(fimgrhd_t*)obp->on_finode,obp->on_buf,obp->on_len);
}

drvstus_t rfs_open_file(device_t* devp,void* iopack)
{
    objnode_t* obp=(objnode_t*)iopack;
    if(obp->on_fname==NULL)
    {
        return DFCERRSTUS;
    }
    void* fmdp=rfs_openfileblk(devp,(char_t*)obp->on_fname);
    if(fmdp==NULL)
    {

        return DFCERRSTUS;
    }
    obp->on_finode=fmdp;
    return DFCOKSTUS;
}

drvstus_t rfs_close_file(device_t* devp,void* iopack)
{
    objnode_t* obp=(objnode_t*)iopack;
    if(obp->on_finode==NULL)
    {
        return DFCERRSTUS;
    }

    return rfs_closefileblk(devp,obp->on_finode);
}

sint_t rfs_strcmp(char_t* str_s,char_t* str_d)
{
    for(;;)
    {
        if(*str_s!=*str_d)
        {
            return 0;
        }
        if(*str_s==0)
        {
            break;
        }
        str_s++;
        str_d++;
    }
    return 1;
}

sint_t rfs_strlen(char* str_s)
{
    sint_t chaidx=0;
    while(*str_s!=0)
    {
        str_s++;
        chaidx++;
    }
    return chaidx;
}

sint_t rfs_strcpy(char_t* str_s,char_t* str_d)
{
    sint_t chaidx=0;
    while(*str_s!=0)
    {
        *str_d=*str_s;
        str_s++;
        str_d++;
        chaidx++;

    }
    *str_d=*str_s;
    return chaidx;
}


void init_rfs(device_t* devp)
{
    rfs_fmat(devp);
    return;
}

void rfs_fmat(device_t* devp)
{
    if(create_superblk(devp)==FALSE)
    {
       hal_sysdie("create superblk err");
    }
    if(create_bitmap(devp)==FALSE)
    {
        hal_sysdie("create bitmap err");
    }
    if(create_rootdir(devp)==FALSE)
    {
        hal_sysdie("create rootdir err");
    }
    //test_rfs(devp);
    //test_dir(devp);
    //test_file(devp);
    return;
}

drvstus_t rfs_writefileblk(device_t* devp,fimgrhd_t* fmp,void* buf,uint_t len)
{
    if(fmp->fmd_sfblk!=fmp->fmd_curfwritebk||
            fmp->fmd_curfwritebk!=fmp->fmd_fleblk[0].fb_blkstart)
    {
        return DFCERRSTUS;
    }
    if((fmp->fmd_curfinwbkoff+len)>=FSYS_ALCBLKSZ)
    {
        return DFCERRSTUS;
    }
    void* wrp=(void*)((uint_t)fmp+fmp->fmd_curfinwbkoff);
    hal_memcpy(buf,wrp,len);
    fmp->fmd_filesz+=len;
    fmp->fmd_curfinwbkoff+=len;
    write_rfsdevblk(devp,(void*)fmp,fmp->fmd_curfwritebk);
    return DFCOKSTUS;
}

drvstus_t rfs_readfileblk(device_t* devp,fimgrhd_t* fmp,void* buf,uint_t len)
{
    if(fmp->fmd_sfblk!=fmp->fmd_curfwritebk||
            fmp->fmd_curfwritebk!=fmp->fmd_fleblk[0].fb_blkstart)
    {
        return DFCERRSTUS;
    }
    if(len>(FSYS_ALCBLKSZ-fmp->fmd_fileifstbkoff))
    {
        return DFCERRSTUS;
    }
    void* wrp=(void*)((uint_t)fmp+fmp->fmd_fileifstbkoff);
    hal_memcpy(wrp,buf,len);
    return DFCOKSTUS;
}


drvstus_t rfs_closefileblk(device_t *devp, void* fblkp)
{
    fimgrhd_t* fmp=(fimgrhd_t*)fblkp;
    write_rfsdevblk(devp,fblkp,fmp->fmd_sfblk);
    del_buf(fblkp,FSYS_ALCBLKSZ);
    return DFCOKSTUS;
}


void* rfs_openfileblk(device_t *devp, char_t* fname)
{
    char_t fne[DR_NM_MAX];
    void* rets=NULL,*buf=NULL;
    hal_memset((void*)fne,DR_NM_MAX,0);
    if(rfs_ret_fname(fne,fname)!=0)
    {
        return NULL;
    }

    void* rblkp=get_rootdirfile_blk(devp);
    if(rblkp==NULL)
    {

        return NULL;
    }
    fimgrhd_t* fmp=(fimgrhd_t*)rblkp;

    if(fmp->fmd_type!=FMD_DIR_TYPE)
    {
        rets=NULL;
        goto err;
    }
    if(fmp->fmd_curfwritebk==fmp->fmd_fleblk[0].fb_blkstart&&
            fmp->fmd_curfinwbkoff==fmp->fmd_fileifstbkoff)
    {
        rets=NULL;
        goto err;
    }
    rfsdir_t* dirp=(rfsdir_t*)((uint_t)(fmp)+fmp->fmd_fileifstbkoff);
    void* maxchkp=(void*)((uint_t)rblkp+FSYS_ALCBLKSZ-1);
    for(;(void*)dirp<maxchkp;)
    {
        if(dirp->rdr_type==RDR_FIL_TYPE)
        {

                if(rfs_strcmp(dirp->rdr_name,fne)==1)
                {
                    goto opfblk;
                }
        }
        dirp++;
    }

    rets=NULL;
    goto err;
opfblk:
    buf=new_buf(FSYS_ALCBLKSZ);
    if(buf==NULL)
    {
        rets=NULL;
        goto err;
    }
    if(read_rfsdevblk(devp,buf,dirp->rdr_blknr)==DFCERRSTUS)
    {
        rets=NULL;
        goto err1;
    }
    fimgrhd_t* ffmp=(fimgrhd_t*)buf;
    if(ffmp->fmd_type==FMD_NUL_TYPE||ffmp->fmd_fileifstbkoff!=0x200)
    {
        rets=NULL;
        goto err1;
    }
    rets=buf;
    goto err;

err1:
    del_buf(buf,FSYS_ALCBLKSZ);
err:
    del_rootdirfile_blk(devp,rblkp);
    return rets;

}

drvstus_t rfs_new_dirfileblk(device_t* devp,char_t* fname,uint_t flgtype,uint_t val)
{
    drvstus_t rets=DFCERRSTUS;
    if(flgtype!=RDR_FIL_TYPE)
    {
        return DFCERRSTUS;
    }
    void* buf=new_buf(FSYS_ALCBLKSZ);
    if(buf==NULL)
    {
        return DFCERRSTUS;
    }
    hal_memset(buf,FSYS_ALCBLKSZ,0);
    uint_t fblk=rfs_new_blk(devp);
    if(fblk==0)
    {
        rets=DFCERRSTUS;
        goto err1;
    }
    void* rdirblk=get_rootdirfile_blk(devp);
    if(rdirblk==NULL)
    {
        rets=DFCERRSTUS;
        goto err1;
    }
    fimgrhd_t* fmp=(fimgrhd_t*)rdirblk;
    rfsdir_t* wrdirp=(rfsdir_t*)((uint_t)rdirblk+fmp->fmd_curfinwbkoff);
    if(((uint_t)wrdirp)>=((uint_t)rdirblk+FSYS_ALCBLKSZ))
    {
        rets=DFCERRSTUS;
        goto err;
    }
    wrdirp->rdr_stus=0;
    wrdirp->rdr_type=flgtype;
    wrdirp->rdr_blknr=fblk;
    rfs_strcpy(fname,wrdirp->rdr_name);
    fmp->fmd_filesz+=(uint_t)(sizeof(rfsdir_t));
    fmp->fmd_curfinwbkoff+=(uint_t)(sizeof(rfsdir_t));
    fimgrhd_t* ffmp=(fimgrhd_t*)buf;
    fimgrhd_t_init(ffmp);
    ffmp->fmd_type=FMD_FIL_TYPE;
    ffmp->fmd_sfblk=fblk;
    ffmp->fmd_curfwritebk=fblk;
    ffmp->fmd_curfinwbkoff=0x200;
    ffmp->fmd_fleblk[0].fb_blkstart=fblk;
    ffmp->fmd_fleblk[0].fb_blknr=1;
    if(write_rfsdevblk(devp,buf,fblk)==DFCERRSTUS)
    {
        rets=DFCERRSTUS;
        goto err;
    }
    rets=DFCOKSTUS;
err:
    del_rootdirfile_blk(devp,rdirblk);
err1:
    del_buf(buf,FSYS_ALCBLKSZ);
    return rets;
}

drvstus_t rfs_del_dirfileblk(device_t* devp,char_t* fname,uint_t flgtype,uint_t val)
{
    if(flgtype!=RDR_FIL_TYPE||val!=0)
    {
        return DFCERRSTUS;
    }
    char_t fne[DR_NM_MAX];
    hal_memset((void*)fne,DR_NM_MAX,0);
    if(rfs_ret_fname(fne,fname)!=0)
    {
        return DFCERRSTUS;
    }
    if(del_dirfileblk_core(devp,fne)!=0)
    {
        return DFCERRSTUS;
    }
    return DFCOKSTUS;
}

sint_t del_dirfileblk_core(device_t* devp,char_t* fname)
{
    sint_t rets=6;
    void* rblkp=get_rootdirfile_blk(devp);
    if(rblkp==NULL)
    {

        return 5;
    }
    fimgrhd_t* fmp=(fimgrhd_t*)rblkp;

    if(fmp->fmd_type!=FMD_DIR_TYPE)
    {
        rets=4;
        goto err;
    }
    if(fmp->fmd_curfwritebk==fmp->fmd_fleblk[0].fb_blkstart&&
            fmp->fmd_curfinwbkoff==fmp->fmd_fileifstbkoff)
    {
        rets=3;
        goto err;
    }
    rfsdir_t* dirp=(rfsdir_t*)((uint_t)(fmp)+fmp->fmd_fileifstbkoff);
    void* maxchkp=(void*)((uint_t)rblkp+FSYS_ALCBLKSZ-1);
    for(;(void*)dirp<maxchkp;)
    {
        if(dirp->rdr_type==RDR_FIL_TYPE)
        {

                if(rfs_strcmp(dirp->rdr_name,fname)==1)
                {
                    rfs_del_blk(devp,dirp->rdr_blknr);
                    rfsdir_t_init(dirp);
                    dirp->rdr_type=RDR_DEL_TYPE;
                    rets=0;
                    goto err;
                }
        }
        dirp++;
    }
    rets=1;
err:
    del_rootdirfile_blk(devp,rblkp);
    return rets;
}

void* get_rootdirfile_blk(device_t* devp)
{
    void* retptr=NULL;
    rfsdir_t* rtdir=get_rootdir(devp);
    if(rtdir==NULL)
    {
        return NULL;
    }
    void* buf=new_buf(FSYS_ALCBLKSZ);
    if(buf==NULL)
    {
        retptr=NULL;
        goto errl1;
    }
    hal_memset(buf,FSYS_ALCBLKSZ,0);
    if(read_rfsdevblk(devp,buf,rtdir->rdr_blknr)==DFCERRSTUS)
    {
        retptr=NULL;
        goto errl;

    }
    retptr=buf;
    goto errl1;
errl:
    del_buf(buf,FSYS_ALCBLKSZ);
errl1:
    del_rootdir(devp,rtdir);

    return retptr;
}

void del_rootdirfile_blk(device_t* devp,void* blkp)
{
    fimgrhd_t* fmp=(fimgrhd_t*)blkp;
    if(write_rfsdevblk(devp,blkp,fmp->fmd_sfblk)==DFCERRSTUS)
    {
        hal_sysdie("del_rootfile_blk err");
    }
    del_buf(blkp,FSYS_ALCBLKSZ);
    return;
}

rfsdir_t* get_rootdir(device_t* devp)
{
    rfsdir_t* retptr=NULL;
    rfssublk_t* sbp=get_superblk(devp);
    if(sbp==NULL)
    {
        return NULL;
    }
    void* buf=new_buf(sizeof(rfsdir_t));
    if(buf==NULL)
    {
        retptr=NULL;
        goto errl;
    }
    hal_memcpy((void*)(&sbp->rsb_rootdir),buf,sizeof(rfsdir_t));
    retptr=(rfsdir_t*)buf;
errl:
    del_superblk(devp,sbp);
    return retptr;
}

void del_rootdir(device_t* devp,rfsdir_t* rdir)
{
    del_buf((void*)rdir,sizeof(rfsdir_t));
    return;
}

rfssublk_t* get_superblk(device_t* devp)
{
    void* buf=new_buf(FSYS_ALCBLKSZ);
    if(buf==NULL)
    {
        return NULL;
    }
    hal_memset(buf,FSYS_ALCBLKSZ,0);
    if(read_rfsdevblk(devp,buf,0)==DFCERRSTUS)
    {
        del_buf(buf,FSYS_ALCBLKSZ);
        return NULL;
    }
    return (rfssublk_t*)buf;
}

void del_superblk(device_t* devp,rfssublk_t* sbp)
{
    if(write_rfsdevblk(devp,(void*)sbp,0)==DFCERRSTUS)
    {
        hal_sysdie("del superblk err");
    }
    del_buf((void*)sbp,FSYS_ALCBLKSZ);
    return;
}

u8_t* get_bitmapblk(device_t* devp)
{
    rfssublk_t* sbp=get_superblk(devp);
    if(sbp==NULL)
    {
        return NULL;
    }
    void* buf=new_buf(FSYS_ALCBLKSZ);
    if(buf==NULL)
    {
        return NULL;
    }
    hal_memset(buf,FSYS_ALCBLKSZ,0);
    if(read_rfsdevblk(devp,buf,sbp->rsb_bmpbks)==DFCERRSTUS)
    {
        del_buf(buf,FSYS_ALCBLKSZ);
        del_superblk(devp,sbp);
        return NULL;
    }
    del_superblk(devp,sbp);
    return (u8_t*)buf;
}

void del_bitmapblk(device_t* devp,u8_t* bitmap)
{
    rfssublk_t* sbp=get_superblk(devp);
    if(sbp==NULL)
    {
        hal_sysdie("del superblk err");
        return;
    }
    if(write_rfsdevblk(devp,(void*)bitmap,sbp->rsb_bmpbks)==DFCERRSTUS)
    {
        del_superblk(devp,sbp);
        hal_sysdie("del superblk err1");
    }
    del_superblk(devp,sbp);
    del_buf((void*)bitmap,FSYS_ALCBLKSZ);
    return;
}

uint_t rfs_new_blk(device_t* devp)
{
    uint_t retblk=0;
    u8_t* bitmap=get_bitmapblk(devp);
    if(bitmap==NULL)
    {
        return 0;
    }
    for(uint_t blknr=2;blknr<FSYS_ALCBLKSZ;blknr++)
    {
        if(bitmap[blknr]==0)
        {
            bitmap[blknr]=1;
            retblk=blknr;
            goto retl;
        }
    }
    retblk=0;
retl:
    del_bitmapblk(devp,bitmap);
    return retblk;
}

void rfs_del_blk(device_t* devp,uint_t  blknr)
{
    if(blknr>FSYS_ALCBLKSZ)
    {
        hal_sysdie("rfs del blk err");
        return;
    }

    u8_t* bitmap=get_bitmapblk(devp);
    if(bitmap==NULL)
    {
        hal_sysdie("rfs del blk err1");
        return;
    }
    bitmap[blknr]=0;
    del_bitmapblk(devp,bitmap);
    return;
}

sint_t rfs_chkfilepath(char_t* fname)
{
    char_t* chp=fname;
    if(chp[0]!='/')
    {
        return 2;
    }
    for(uint_t i=1;;i++)
    {
        if(chp[i]=='/')
        {
            return 3;
        }
        if(i>=DR_NM_MAX)
        {
            return 4;
        }
        if(chp[i]==0&&i>1)
        {
            break;
        }
    }
    return 0;
}

sint_t rfs_ret_fname(char_t* buf,char_t* fpath)
{
    if(buf==NULL||fpath==NULL)
    {
        return 6;
    }
    sint_t stus=rfs_chkfilepath(fpath);
    if(stus!=0)
    {
        return stus;
    }
    rfs_strcpy(&fpath[1],buf);
    return 0;
}

sint_t rfs_chkfileisindev(device_t* devp,char_t* fname)
{
    sint_t rets=6;
    sint_t ch=rfs_strlen(fname);
    if(ch<1||ch>=(sint_t)DR_NM_MAX)
    {
        return 4;
    }
    void* rdblkp=get_rootdirfile_blk(devp);
    if(rdblkp==NULL)
    {
        return 2;
    }
    fimgrhd_t* fmp=(fimgrhd_t*)rdblkp;

    if(fmp->fmd_type!=FMD_DIR_TYPE)
    {
        rets=3;
        goto err;
    }
    if(fmp->fmd_curfwritebk==fmp->fmd_fleblk[0].fb_blkstart&&
            fmp->fmd_curfinwbkoff==fmp->fmd_fileifstbkoff)
    {
        rets=0;
        goto err;
    }
    rfsdir_t* dirp=(rfsdir_t*)((uint_t)(fmp)+fmp->fmd_fileifstbkoff);
    void* maxchkp=(void*)((uint_t)rdblkp+FSYS_ALCBLKSZ-1);
    for(;(void*)dirp<maxchkp;)
    {
        if(dirp->rdr_type==RDR_FIL_TYPE)
        {

                if(rfs_strcmp(dirp->rdr_name,fname)==1)
                {
                    rets=1;
                    goto err;
                }
        }
        dirp++;
    }
    rets=0;
err:
    del_rootdirfile_blk(devp,rdblkp);
    return rets;
}

bool_t create_superblk(device_t* devp)
{
    void* buf=new_buf(FSYS_ALCBLKSZ);
    if(buf==NULL)
    {
        return FALSE;
    }
    hal_memset(buf,FSYS_ALCBLKSZ,0);
    rfssublk_t* sbp=(rfssublk_t*)buf;
    rfssublk_t_init(sbp);
    sbp->rsb_fsysallblk=ret_rfsdevmaxblknr(devp);
    if(write_rfsdevblk(devp,buf,0)==DFCERRSTUS)
    {
        return FALSE;
    }
    del_buf(buf,FSYS_ALCBLKSZ);
    return TRUE;
}

bool_t create_bitmap(device_t* devp)
{
    bool_t rets=FALSE;
    rfssublk_t* sbp=get_superblk(devp);
    if(sbp==NULL)
    {
        return FALSE;
    }
    void* buf=new_buf(FSYS_ALCBLKSZ);
    if(buf==NULL)
    {
        return FALSE;
    }
    uint_t bitmapblk=sbp->rsb_bmpbks;
    uint_t devmaxblk=sbp->rsb_fsysallblk;
    if(devmaxblk>FSYS_ALCBLKSZ)
    {
        rets=FALSE;
        goto errlable;
    }

    hal_memset(buf,FSYS_ALCBLKSZ,1);
    u8_t* bitmap=(u8_t*)buf;
    for(uint_t bi=2;bi<devmaxblk;bi++)
    {
        bitmap[bi]=0;
    }
    if(write_rfsdevblk(devp,buf,bitmapblk)==DFCERRSTUS)
    {
        rets=FALSE;
        goto errlable;
    }
    rets=TRUE;
errlable:
    del_superblk(devp,sbp);
    del_buf(buf,FSYS_ALCBLKSZ);
    return rets;
}



bool_t create_rootdir(device_t* devp)
{
    bool_t rets=FALSE;
    rfssublk_t* sbp=get_superblk(devp);
    if(sbp==NULL)
    {
        return FALSE;
    }
    void* buf=new_buf(FSYS_ALCBLKSZ);
    if(buf==NULL)
    {
        rets=FALSE;
        goto errlable1;
    }
    hal_memset(buf,FSYS_ALCBLKSZ,0);
    uint_t blk=rfs_new_blk(devp);
    if(blk==0)
    {
        rets=FALSE;
        goto errlable;
    }
    sbp->rsb_rootdir.rdr_name[0]='/';
    sbp->rsb_rootdir.rdr_type=RDR_DIR_TYPE;
    sbp->rsb_rootdir.rdr_blknr=blk;
    fimgrhd_t* fmp=(fimgrhd_t*)buf;
    fimgrhd_t_init(fmp);
    fmp->fmd_type=FMD_DIR_TYPE;
    fmp->fmd_sfblk=blk;
    fmp->fmd_curfwritebk=blk;
    fmp->fmd_curfinwbkoff=0x200;
    fmp->fmd_fleblk[0].fb_blkstart=blk;
    fmp->fmd_fleblk[0].fb_blknr=1;
    if(write_rfsdevblk(devp,buf,blk)==DFCERRSTUS)
    {
        rets=FALSE;
        goto errlable;
    }
    rets=TRUE;
errlable:
    del_buf(buf,FSYS_ALCBLKSZ);
errlable1:
    del_superblk(devp,sbp);

    return rets;
}

void chk_rfsbitmap(device_t* devp)
{
    void* buf=new_buf(FSYS_ALCBLKSZ);
    if(buf==NULL)
    {
        hal_sysdie("chkbitmap err");
    }
    hal_memset(buf,FSYS_ALCBLKSZ,0);
    if(read_rfsdevblk(devp,buf,1)==DFCERRSTUS)
    {
        hal_sysdie("chkbitmap err1");
    }
    u8_t* bmp=(u8_t*)buf;
    uint_t b=0;
    for(uint_t i=0;i<FSYS_ALCBLKSZ;i++)
    {
        if(bmp[i]==0)
        {
            b++;
        }
    }
    printfk("chk bmpp b:%x\n\r",b);
    del_buf(buf,FSYS_ALCBLKSZ);
    return;
}

void test_allocblk(device_t* devp)
{
    uint_t ai[64];
    uint_t i=0,j=0;
    for(;;)
    {
    for(uint_t k=0;k<64;k++)
    {
        i=rfs_new_blk(devp);
        if(i==0)
            hal_sysdie("alloc blkk err");

        printfk("alloc blk:%x\n\r",i);
        ai[k]=i;
        j++;
    }
    for(uint_t m=0;m<64;m++)
    {
        rfs_del_blk(devp, ai[m]);
        printfk("free blk:%x\n\r",ai[m]);
    }
    }
    printfk("alloc indx:%x\n\r",j);
    return;
}
void test_dir(device_t* devp)
{
    rfsdir_t* dr=get_rootdir(devp);
    void* buf = new_buf(FSYS_ALCBLKSZ);
    if(buf==NULL)
    {
        hal_sysdie("testdir err");
    }
    hal_memset(buf,FSYS_ALCBLKSZ,0);
    if(read_rfsdevblk(devp,buf,dr->rdr_blknr)==DFCERRSTUS)
    {
        hal_sysdie("testdir1 err1");
    }
    fimgrhd_t* fmp=(fimgrhd_t*)buf;
    printfk("fmp-fmd_type:%x fmd_filesz:%x fmd_fileifstbkoff:%x fmd_fileiendbkoff:%x\n\r",
            fmp->fmd_type,fmp->fmd_filesz,fmp->fmd_fileifstbkoff,fmp->fmd_fileiendbkoff);
    printfk("fmd_fleblk:%x:%x\n\r",fmp->fmd_fleblk[0].fb_blkstart,fmp->fmd_fleblk[0].fb_blknr);
    del_buf(buf,FSYS_ALCBLKSZ);
    del_rootdir(devp,dr);
    return;
}

void test_rfs(device_t* devp)
{
    rfssublk_t* sbp=get_superblk(devp);
    printfk("rsb_mgic %x,vec %x\n\r",sbp->rsb_mgic,sbp->rsb_vec);
    printfk("rsb_sblksz %x,rsb_dblksz %x\n\r",sbp->rsb_sblksz,sbp->rsb_dblksz);
    printfk("rsb_bmpbks %x,rsb_bmpbknr %x,rsb_fsysallblk %x\n\r",sbp->rsb_bmpbks,sbp->rsb_bmpbknr,sbp->rsb_fsysallblk);
    printfk("rootdirblk:%x dirtype:%x\n\r",sbp->rsb_rootdir.rdr_blknr,sbp->rsb_rootdir.rdr_type);
    printfk("rootdir:%s\n\r",sbp->rsb_rootdir.rdr_name);
    del_superblk(devp,sbp);

    hal_sysdie("test rfs run");
    return;
}

void test_file(device_t* devp)
{
    //test_rfs(devp);
    //chk_rfsbitmap(devp);
    //test_dir(devp);
    test_fsys(devp);
    hal_sysdie("test file run");
    return;
}

void test_fsys(device_t* devp)
{
    void* rwbuf=new_buf(FSYS_ALCBLKSZ);
    if(rwbuf==NULL)
    {
        hal_sysdie("rwbuf is NULL");
    }
    hal_memset(rwbuf,FSYS_ALCBLKSZ,0xff);
    objnode_t* ondp=krlnew_objnode();
    if(ondp==NULL)
    {
        hal_sysdie("ondp is NULL");
    }

    ondp->on_acsflgs=FSDEV_OPENFLG_NEWFILE;
    ondp->on_fname="/testfile";
    ondp->on_buf=rwbuf;
    ondp->on_bufsz=FSYS_ALCBLKSZ;
    ondp->on_len=512;
    ondp->on_ioctrd=FSDEV_IOCTRCD_DELFILE;
    if(rfs_open(devp,ondp)==DFCERRSTUS)
    {
        hal_sysdie("new file is err");
    }

    ondp->on_acsflgs=FSDEV_OPENFLG_OPEFILE;

    if(rfs_open(devp,ondp)==DFCERRSTUS)
    {
        hal_sysdie("open file is err");
    }

    if(rfs_write(devp,ondp)==DFCERRSTUS)
    {
        hal_sysdie("write file is err");
    }
    hal_memset(rwbuf,FSYS_ALCBLKSZ,0);

    if(rfs_read(devp,ondp)==DFCERRSTUS)
    {
        hal_sysdie("read file is err");
    }

    if(rfs_close(devp,ondp)==DFCERRSTUS)
    {
        hal_sysdie("close file is err");
    }
    char_t* cb=(char_t*)rwbuf;
    for(uint_t i=0;i<512;i++)
    {
        if(cb[i]!=0xff)
        {
            hal_sysdie("chek rwbuf err");
        }
        printfk("rwblk[%x]:%x\n\r",i,(uint_t)cb[i]);
    }

    if(rfs_ioctrl(devp,ondp)==DFCERRSTUS)
    {
        hal_sysdie("del file is err");
    }
    ondp->on_acsflgs=FSDEV_OPENFLG_OPEFILE;

    if(rfs_open(devp,ondp)==DFCERRSTUS)
    {
        hal_sysdie("2open2 file is err");
    }
    hal_sysdie("test_fsys ok");
    return;
}
