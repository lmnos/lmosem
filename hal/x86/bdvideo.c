/**********************************************************
        引导调式屏幕上显示输出文件bdvideo.c
***********************************************************
                彭东 ＠ 2015.03.25.21.30
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

const char* lmos_version = "LMOSEM 32bits\n内核版本:00.01\n彭东 @ 构建于 "__DATE__" "__TIME__"\n";

PUBLIC LKINIT void init_dftgraph()
{
    dftgraph_t* kghp=&kdftgh;
    machbstart_t* kmbsp=&kmachbsp;
    memset(kghp,0,sizeof(dftgraph_t));
    kghp->gh_mode=kmbsp->mb_ghparm.gh_mode;
    kghp->gh_x=kmbsp->mb_ghparm.gh_x;
    kghp->gh_y=kmbsp->mb_ghparm.gh_y;
    kghp->gh_framphyadr=krnlphyiadr_to_viradr((adr_t)kmbsp->mb_ghparm.gh_framphyadr);
    kghp->gh_fvrmphyadr=krnlphyiadr_to_viradr((adr_t)kmbsp->mb_fvrmphyadr);
    kghp->gh_fvrmsz=kmbsp->mb_fvrmsz;
    kghp->gh_onepixbits=kmbsp->mb_ghparm.gh_onepixbits;
    kghp->gh_onepixbyte=kmbsp->mb_ghparm.gh_onepixbits/8;
    kghp->gh_vbemodenr=kmbsp->mb_ghparm.gh_vbemodenr;
    kghp->gh_bank=kmbsp->mb_ghparm.gh_bank;
    kghp->gh_curdipbnk=kmbsp->mb_ghparm.gh_curdipbnk;
    kghp->gh_nextbnk=kmbsp->mb_ghparm.gh_nextbnk;
    kghp->gh_banksz=kmbsp->mb_ghparm.gh_banksz;

    kghp->gh_fontadr=krnlphyiadr_to_viradr((adr_t)kmbsp->mb_bfontpadr);
    kghp->gh_fontsz=kmbsp->mb_bfontsz;
    kghp->gh_fnthight=16;
    kghp->gh_linesz=16+4;
    kghp->gh_deffontpx=BGRA(0xff,0xff,0xff);
    return;
}

pixl_t set_deffontpx(pixl_t setpx)
{
    dftgraph_t* kghp=&kdftgh;
    pixl_t bkpx=kghp->gh_deffontpx;
    kghp->gh_deffontpx=setpx;
    return bkpx;

}

void set_ncharsxy(u64_t x,u64_t y)
{
    dftgraph_t* kghp=&kdftgh;
    kghp->gh_nxtcharsx=x;
    kghp->gh_nxtcharsy=y;
    return;
}

void set_charsdxwflush(u64_t chardxw,u64_t flush)
{
    kdftgh.gh_chardxw=chardxw;
    kdftgh.gh_flush=flush;
    return;
}

void lmos_dspversion()
{
    pixl_t bkpx=set_deffontpx(BGRA(0xff,0,0));
    kprint(lmos_version);
    kprint("系统处理器工作模式:%d位 系统物理内存大小:%dMB\n",(uint_t)kmachbsp.mb_cpumode,(uint_t)(kmachbsp.mb_memsz>>20));
    set_deffontpx(bkpx);
    return;
}

void fill_rect(pixl_t pix,uint_t x,uint_t y,uint_t tx,uint_t ty)
{
    for(uint_t i=y;i<y+ty;i++)
    {
        for(uint_t j=x;j<x+tx;j++)
        {
            write_pixcolor(&kdftgh,(u32_t)j,(u32_t)i,pix);
        }
    }
    return;
}

void fill_fullbitmap(char_t* bmfname)
{
    dftgraph_t* kghp=&kdftgh;
    machbstart_t* kmbsp=&kmachbsp;
    u64_t fadr=0,fsz=0;
    get_file_rvadrandsz(bmfname, kmbsp,&fadr,&fsz);
    if(0==fadr||0==fsz)
    {
        system_error("not bitmap file err\n");
    }
    bmdbgr_t* bmdp;
    u64_t img=fadr+sizeof(bmfhead_t)+sizeof(bitminfo_t);
    bmdp=(bmdbgr_t*)((uint_t)img);
    pixl_t pix;
    int k=0,l=0;
    for(int j=768;j>=0;j--,l++)
    {
        for(int i=0;i<1024;i++)
        {
            pix=BGRA(bmdp[k].bmd_r,bmdp[k].bmd_g,bmdp[k].bmd_b);
            //drxw_pixcolor(kghp,i,j,pix);
            write_pixcolor(kghp,i,j,pix);
            k++;
        }
    }
    flush_videoram(kghp);
    return;
}


void slou_sreen(uint_t hy)
{
    uint_t x,y,ofx,ofy;
    dftgraph_t* kghp=&kdftgh;
    bga_get_xyoffset(kghp,&x,&y);
    bga_get_vwh(kghp,&ofx,&ofy);
    y+=hy;
    ofy+=hy;
    bga_set_vwh(kghp,ofx,ofy);
    bga_set_xyoffset(kghp,x,y);
    return;
//    kghp->gh_opfun.dgo_set_xy=bga_set_xy;
//    kghp->gh_opfun.dgo_set_vwh=bga_set_vwh;
//    kghp->gh_opfun.dgo_set_xyoffset=bga_set_xyoffset;
//    kghp->gh_opfun.dgo_get_xy=bga_get_xy;
//    kghp->gh_opfun.dgo_get_vwh=bga_get_vwh;
//    kghp->gh_opfun.dgo_get_xyoffset=bga_get_xyoffset;
}


void lmos_background()
{
    dftgraph_t* kghp=&kdftgh;
    machbstart_t* kmbsp=&kmachbsp;
    u64_t fadr=0,fsz=0;
    get_file_rvadrandsz("22.bmp", kmbsp,&fadr,&fsz);
    if(0==fadr||0==fsz)
    {
        system_error("lmosbkgderr");
    }
    bmdbgr_t* bmdp;
    u64_t img=fadr+sizeof(bmfhead_t)+sizeof(bitminfo_t);
    bmdp=(bmdbgr_t*)((uint_t)img);
    pixl_t pix;
    int k=0,l=0;
    for(int j=768;j>=0;j--,l++)
    {
        for(int i=0;i<1024;i++)
        {
            pix=BGRA(bmdp[k].bmd_r,bmdp[k].bmd_g,bmdp[k].bmd_b);
            drxw_pixcolor(kghp,i,j,pix);
            //write_pixcolor(kghp,i,j,pix);
            k++;
        }
//        if(l>205)
//        {
//            die(0x80);
//        }
    }
    lmos_dspversion();
    //flush_videoram(kghp);
    return;
}
void lmos_logo()
{
    dftgraph_t* kghp=&kdftgh;
    machbstart_t* kmbsp=&kmachbsp;
    u64_t fadr=0,fsz=0;
    get_file_rvadrandsz("LMOSLOGO.bmp", kmbsp,&fadr,&fsz);
    if(0==fadr||0==fsz)
    {
        system_error("lmoslogoerr");
    }
    bmdbgr_t* bmdp;
    u64_t img=fadr+sizeof(bmfhead_t)+sizeof(bitminfo_t);
    bmdp=(bmdbgr_t*)((uint_t)img);
    pixl_t pix;
    int k=0,l=0;
    for(int j=617;j>=153;j--,l++)
    {
        for(int i=402;i<622;i++)
        {
            pix=BGRA(bmdp[k].bmd_r,bmdp[k].bmd_g,bmdp[k].bmd_b);
            drxw_pixcolor(kghp,i,j,pix);
            //write_pixcolor(kghp,i,j,pix);
            k++;
        }
        if(l>205)
        {
            die(0x80);
        }
    }
    //flush_videoram(kghp);
    return;
}


PUBLIC LKINIT void init_bdvideo()
{
    dftgraph_t* kghp=&kdftgh;

    init_dftgraph();
    init_bga();
    init_vbe();
    //lmos_logo();
    die(0x200);
    fill_graph(kghp,BGRA(0,0,0));
//    disp_l();
//    fill_xggif();
//    fill_mngif();
//    fill_gif();
    set_charsdxwflush(0,0);
    //next_background();
    lmos_background();
//    for(;;)
//    {
//        fill_graph(kghp,BGRA(0x64,0x95,0xed));
//        die(0x300);
//        fill_graph(kghp,BGRA(0x0,0x0,0xff));
//        die(0x300);
//        fill_graph(kghp,BGRA(0x0,0xff,0x0));
//        die(0x300);
//        fill_graph(kghp,BGRA(0xff,0x0,0x0));
//        die(0x300);
//    }
    //lmos_dspversion();
    return;
}


void init_bga()
{
    dftgraph_t* kghp=&kdftgh;
    if(kghp->gh_mode!=BGAMODE)
    {
        return;
    }
    kghp->gh_opfun.dgo_read=bga_read;
    kghp->gh_opfun.dgo_write=bga_write;
    kghp->gh_opfun.dgo_ioctrl=bga_ioctrl;
    kghp->gh_opfun.dgo_flush=bga_flush;
    kghp->gh_opfun.dgo_set_bank=bga_set_bank;
    kghp->gh_opfun.dgo_readpix=bga_readpix;
    kghp->gh_opfun.dgo_writepix=bga_writepix;
    kghp->gh_opfun.dgo_dxreadpix=bga_dxreadpix;
    kghp->gh_opfun.dgo_dxwritepix=bga_dxwritepix;
    kghp->gh_opfun.dgo_set_xy=bga_set_xy;
    kghp->gh_opfun.dgo_set_vwh=bga_set_vwh;
    kghp->gh_opfun.dgo_set_xyoffset=bga_set_xyoffset;
    kghp->gh_opfun.dgo_get_xy=bga_get_xy;
    kghp->gh_opfun.dgo_get_vwh=bga_get_vwh;
    kghp->gh_opfun.dgo_get_xyoffset=bga_get_xyoffset;
    return;
}

void init_vbe()
{
    dftgraph_t* kghp=&kdftgh;
    if(kghp->gh_mode!=VBEMODE)
    {
        return;
    }
    kghp->gh_opfun.dgo_read=vbe_read;
    kghp->gh_opfun.dgo_write=vbe_write;
    kghp->gh_opfun.dgo_ioctrl=vbe_ioctrl;
    kghp->gh_opfun.dgo_flush=vbe_flush;
    kghp->gh_opfun.dgo_set_bank=vbe_set_bank;
    kghp->gh_opfun.dgo_readpix=vbe_readpix;
    kghp->gh_opfun.dgo_writepix=vbe_writepix;
    kghp->gh_opfun.dgo_dxreadpix=vbe_dxreadpix;
    kghp->gh_opfun.dgo_dxwritepix=vbe_dxwritepix;
    kghp->gh_opfun.dgo_set_xy=vbe_set_xy;
    kghp->gh_opfun.dgo_set_vwh=vbe_set_vwh;
    kghp->gh_opfun.dgo_set_xyoffset=vbe_set_xyoffset;
    kghp->gh_opfun.dgo_get_xy=vbe_get_xy;
    kghp->gh_opfun.dgo_get_vwh=vbe_get_vwh;
    kghp->gh_opfun.dgo_get_xyoffset=vbe_get_xyoffset;
    return;
}

void fill_graph(dftgraph_t* kghp,pixl_t pix)
{
    for(u64_t y=0;y<kghp->gh_y;y++)
    {
        for(u64_t x=0;x<kghp->gh_x;x++)
        {
             write_pixcolor(kghp,(u32_t)x,(u32_t)y,pix);
        }
    }
    flush_videoram(kghp);
    return;
}


void write_pixcolor(dftgraph_t* kghp,u32_t x,u32_t y,pixl_t pix)
{
//    u8_t* p24bas;//=(u8_t*)kghp->gh_framphyadr;
//    if(kghp->gh_onepixbits==24)
//    {
//            u64_t p24adr=(x+(y*kghp->gh_x))*3;
//            p24bas=(u8_t*)(p24adr+kghp->gh_fvrmphyadr);
//            p24bas[0]=(u8_t)(pix);
//            p24bas[1]=(u8_t)(pix>>8);//pvalptr->cl_g;
//            p24bas[2]=(u8_t)(pix>>16);//pvalptr->cl_r;
//            return;

//    }
//    u32_t* phybas=(u32_t*)kghp->gh_fvrmphyadr;
//    phybas[x+(y*kghp->gh_x)]=pix;
    kghp->gh_opfun.dgo_writepix(kghp,pix,x,y);
    return;
}
void drxw_pixcolor(dftgraph_t* kghp,u32_t x,u32_t y,pixl_t pix)
{
//    u8_t* p24bas;//=(u8_t*)kghp->gh_framphyadr;
//    if(kghp->gh_onepixbits==24)
//    {
//            u64_t p24adr=(x+(y*kghp->gh_x))*3;
//            p24bas=(u8_t*)(p24adr+kghp->gh_framphyadr);
//            p24bas[0]=(u8_t)(pix);
//            p24bas[1]=(u8_t)(pix>>8);//pvalptr->cl_g;
//            p24bas[2]=(u8_t)(pix>>16);//pvalptr->cl_r;
//            return;

//    }
//    u32_t* phybas=(u32_t*)kghp->gh_framphyadr;
//    phybas[x+(y*kghp->gh_x)]=pix;
    kghp->gh_opfun.dgo_dxwritepix(kghp,pix,x,y);
    return;
}
void flush_videoram(dftgraph_t* kghp)
{
//    u64_t* s=(u64_t*)kghp->gh_fvrmphyadr;
//    u64_t* d=(u64_t*)kghp->gh_framphyadr;
//    u64_t i=0,j=0;
//    u64_t e=kghp->gh_x*kghp->gh_y*kghp->gh_onepixbyte;
//    //u64_t k=e/8;
//    for(;i<e;i+=8)
//    {
////        if(d[j]==s[j])
////        {

////            d[j]=s[j];
////        }
//        d[j]=s[j];
//        j++;
//    }
    kghp->gh_opfun.dgo_flush(kghp);
    return;
}



u32_t utf8_to_unicode(utf8_t* utfp,int* retuib)
{
    u8_t uhd=utfp->utf_b1,ubyt=0;
    u32_t ucode=0,tmpuc=0;
    if(0x80>uhd)//0xbf&&uhd<=0xbf
    {
        ucode=utfp->utf_b1&0x7f;
        *retuib=1;
        return ucode;
    }
    if(0xc0<=uhd&&uhd<=0xdf)//0xdf
    {
        ubyt=utfp->utf_b1&0x1f;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b2&0x3f;
        ucode=(tmpuc<<6)|ubyt;
        *retuib=2;
        return ucode;
    }
    if(0xe0<=uhd&&uhd<=0xef)//0xef
    {
        ubyt=utfp->utf_b1&0x0f;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b2&0x3f;
        tmpuc<<=6;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b3&0x3f;
        ucode=(tmpuc<<6)|ubyt;
        *retuib=3;
        return ucode;
    }
    if(0xf0<=uhd&&uhd<=0xf7)//0xf7
    {
        ubyt=utfp->utf_b1&0x7;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b2&0x3f;
        tmpuc<<=6;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b3&0x3f;
        tmpuc<<=6;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b4&0x3f;
        ucode=(tmpuc<<6)|ubyt;
        *retuib=4;
        return ucode;
    }
    if(0xf8<=uhd&&uhd<=0xfb)//0xfb
    {
        ubyt=utfp->utf_b1&0x3;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b2&0x3f;
        tmpuc<<=6;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b3&0x3f;
        tmpuc<<=6;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b4&0x3f;
        tmpuc<<=6;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b5&0x3f;
        ucode=(tmpuc<<6)|ubyt;
        *retuib=5;
        return ucode;
    }
    if(0xfc<=uhd&&uhd<=0xfd)//0xfd
    {
        ubyt=utfp->utf_b1&0x1;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b2&0x3f;
        tmpuc<<=6;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b3&0x3f;
        tmpuc<<=6;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b4&0x3f;
        tmpuc<<=6;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b5&0x3f;
        tmpuc<<=6;
        tmpuc|=ubyt;
        ubyt=utfp->utf_b6&0x3f;
        ucode=(tmpuc<<6)|ubyt;
        *retuib=6;
        return ucode;
    }
    *retuib=0;
    return 0;
}



u8_t* ret_charsinfo(dftgraph_t* kghp,u32_t unicode,int* retchwx,int* retchhx,int* retlinb)
{
    fntdata_t* fntp=(fntdata_t*)((uint_t)kghp->gh_fontadr);
    *retchwx=fntp[unicode].fntwx;
    *retchhx=fntp[unicode].fnthx;
    *retlinb=fntp[unicode].fntwxbyte;

    return (u8_t*)(&(fntp[unicode].fntchmap[0]));
}

void put_pixonechar(dftgraph_t* kghp,u32_t unicode,pixl_t pix)
{
    int y=0,chwx=0,chhx=0,linb=0;
    u8_t* charyp=NULL;


    if(unicode==10)
    {
        kghp->gh_nxtcharsx=0;
        if((kghp->gh_nxtcharsy+kghp->gh_linesz)>(kghp->gh_y-kghp->gh_fnthight))
        {
            kghp->gh_nxtcharsy=0;
            lmos_background();
            return;
        }
        kghp->gh_nxtcharsy+=kghp->gh_linesz;
        return;
    }
    charyp=ret_charsinfo(kghp,unicode,&chwx,&chhx,&linb);
    if(charyp==NULL)
    {
        return;
    }
    if((kghp->gh_nxtcharsx+chwx)>(kghp->gh_x-chwx))
    {
        kghp->gh_nxtcharsx=0;
        if((kghp->gh_nxtcharsy+kghp->gh_linesz)>(kghp->gh_y-kghp->gh_fnthight))
        {
            kghp->gh_nxtcharsy=0;
        }
        else
        {
            kghp->gh_nxtcharsy+=kghp->gh_linesz;
        }

    }
    u32_t wpx=(u32_t)kghp->gh_nxtcharsx,wpy=(u32_t)kghp->gh_nxtcharsy;

    for(int hx=0;hx<chhx;hx++)
    {
        for(int btyi=0,x=0;btyi<linb;btyi++)
        {
            u8_t bitmap=charyp[hx*linb+btyi];
            if(bitmap==0)
            {
                x+=8;
                continue;
            }
            for(int bi=7;bi>=0;bi--)
            {
                if(x>=chwx)
                {
                    break;
                }
                if(((bitmap>>bi)&1)==1)
                {
                    write_pixcolor(kghp,wpx+x,wpy+y,pix);
                }
                x++;
            }
        }
        y++;
    }
    kghp->gh_nxtcharsx+=(u64_t)chwx;

    //kprint("X:%d Y:%d INEB:%d CHWX:%d CHHX:%d\n",x,y,linb,chwx,chhx);
    return;
}

void drxput_pixonechar(dftgraph_t* kghp,u32_t unicode,pixl_t pix)
{
    int y=0,chwx=0,chhx=0,linb=0;
    u8_t* charyp=NULL;


    if(unicode==10)
    {
        kghp->gh_nxtcharsx=0;
        if((kghp->gh_nxtcharsy+kghp->gh_linesz)>(kghp->gh_y-kghp->gh_fnthight))
        {
            kghp->gh_nxtcharsy=0;
            lmos_background();
            return;
        }
        kghp->gh_nxtcharsy+=kghp->gh_linesz;
        return;
    }
    charyp=ret_charsinfo(kghp,unicode,&chwx,&chhx,&linb);
    if(charyp==NULL)
    {
        return;
    }
    if((kghp->gh_nxtcharsx+chwx)>(kghp->gh_x-chwx))
    {
        kghp->gh_nxtcharsx=0;
        if((kghp->gh_nxtcharsy+kghp->gh_linesz)>(kghp->gh_y-kghp->gh_fnthight))
        {
            kghp->gh_nxtcharsy=0;
        }
        else
        {
            kghp->gh_nxtcharsy+=kghp->gh_linesz;
        }

    }
    u32_t wpx=(u32_t)kghp->gh_nxtcharsx,wpy=(u32_t)kghp->gh_nxtcharsy;

    for(int hx=0;hx<chhx;hx++)
    {
        for(int btyi=0,x=0;btyi<linb;btyi++)
        {
            u8_t bitmap=charyp[hx*linb+btyi];
            if(bitmap==0)
            {
                x+=8;
                continue;
            }
            for(int bi=7;bi>=0;bi--)
            {
                if(x>=chwx)
                {
                    break;
                }
                if(((bitmap>>bi)&1)==1)
                {
                    drxw_pixcolor(kghp,wpx+x,wpy+y,pix);
                }
                x++;
            }
        }
        y++;
    }
    kghp->gh_nxtcharsx+=(u64_t)chwx;

    //kprint("X:%d Y:%d INEB:%d CHWX:%d CHHX:%d\n",x,y,linb,chwx,chhx);
    return;
}


void gstr_write(dftgraph_t* kghp,char_t* buf)
{
    int chinx=0;
    int chretnext=0;
    u32_t uc=0;
    pixl_t pix=kghp->gh_deffontpx;
    while (buf[chinx]!=0)
    {
          uc=utf8_to_unicode((utf8_t*)(&buf[chinx]),&chretnext);
          chinx+=chretnext;
          if(kghp->gh_chardxw==1)
          {
              put_pixonechar(kghp,uc,pix);
          }else
          {
              drxput_pixonechar(kghp,uc,pix);
          }

    }
    if(kghp->gh_flush==1)
    {
        flush_videoram(kghp);
    }
    return;
}
void bga_write_reg(u16_t index, u16_t data)
{
    out_u16(VBE_DISPI_IOPORT_INDEX, index);
    out_u16(VBE_DISPI_IOPORT_DATA, data);
    return;
}

u16_t bga_read_reg(u16_t index)
{
    out_u16(VBE_DISPI_IOPORT_INDEX, index);
    return in_u16(VBE_DISPI_IOPORT_DATA);
}

size_t bga_read(void* ghpdev,void* outp,size_t rdsz)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    return rdsz;
}
size_t bga_write(void* ghpdev,void* inp,size_t wesz)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    return wesz;
}
sint_t bga_ioctrl(void* ghpdev,void* outp,uint_t iocode)
{
    return -1;
}

u64_t* ret_vramadr_inbnk(void* ghpdev)
{
    dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    u64_t* d=(u64_t*)((uint_t)(kghp->gh_framphyadr+(kghp->gh_x*kghp->gh_y*kghp->gh_onepixbyte*kghp->gh_nextbnk)));

    return d;
}


void   bga_disp_nxtbank(void* ghpdev)
{
    dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    u16_t h=(u16_t)(kghp->gh_y*kghp->gh_nextbnk+1);
    u16_t ofy=(u16_t)(kghp->gh_y*(kghp->gh_nextbnk));
    bga_write_reg(VBE_DISPI_INDEX_VIRT_HEIGHT,h);
    bga_write_reg(VBE_DISPI_INDEX_Y_OFFSET,ofy);
    kghp->gh_curdipbnk=kghp->gh_nextbnk;
    kghp->gh_nextbnk++;
    if(kghp->gh_nextbnk>kghp->gh_bank)
    {
        kghp->gh_nextbnk=0;
    }
    return;
}

void   bga_flush(void* ghpdev)
{
    dftgraph_t* kghp=(dftgraph_t*)ghpdev;

    u64_t* s=(u64_t*)((uint_t)kghp->gh_fvrmphyadr);
    u64_t* d=ret_vramadr_inbnk(kghp);//(u64_t*)kghp->gh_framphyadr;
    u64_t i=0,j=0;
    u64_t e=kghp->gh_x*kghp->gh_y*kghp->gh_onepixbyte;
    //u64_t k=e/8;
    for(;i<e;i+=8)
    {
        d[j]=s[j];
        j++;
    }
    bga_disp_nxtbank(kghp);
    return;
}
sint_t bga_set_bank(void* ghpdev, sint_t bnr)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    return -1;
}
pixl_t bga_readpix(void* ghpdev,uint_t x,uint_t y)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    return 0;
}
void   bga_writepix(void* ghpdev,pixl_t pix,uint_t x,uint_t y)
{
    dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    u8_t* p24bas;//=(u8_t*)kghp->gh_framphyadr;
    if(kghp->gh_onepixbits==24)
    {
            u64_t p24adr=(x+(y*kghp->gh_x))*3;
            p24bas=(u8_t*)((uint_t)(p24adr+kghp->gh_fvrmphyadr));
            p24bas[0]=(u8_t)(pix);
            p24bas[1]=(u8_t)(pix>>8);//pvalptr->cl_g;
            p24bas[2]=(u8_t)(pix>>16);//pvalptr->cl_r;
            return;

    }
    u32_t* phybas=(u32_t*)((uint_t)kghp->gh_fvrmphyadr);
    phybas[x+(y*kghp->gh_x)]=pix;
    return;
}
pixl_t bga_dxreadpix(void* ghpdev,uint_t x,uint_t y)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    return 0;
}
void   bga_dxwritepix(void* ghpdev,pixl_t pix,uint_t x,uint_t y)
{
    dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    u8_t* p24bas;//=(u8_t*)kghp->gh_framphyadr;
    if(kghp->gh_onepixbits==24)
    {
            u64_t p24adr=(x+(y*kghp->gh_x))*3*kghp->gh_curdipbnk;
            p24bas=(u8_t*)((uint_t)(p24adr+kghp->gh_framphyadr));
            p24bas[0]=(u8_t)(pix);
            p24bas[1]=(u8_t)(pix>>8);//pvalptr->cl_g;
            p24bas[2]=(u8_t)(pix>>16);//pvalptr->cl_r;
            return;

    }
    u32_t* phybas=(u32_t*)((uint_t)(kghp->gh_framphyadr+(kghp->gh_x*kghp->gh_y*kghp->gh_onepixbyte*kghp->gh_curdipbnk)));
    phybas[x+(y*kghp->gh_x)]=pix;
    return;
}
sint_t bga_set_xy(void* ghpdev,uint_t x,uint_t y)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    bga_write_reg(VBE_DISPI_INDEX_XRES,(u16_t)(x));
    bga_write_reg(VBE_DISPI_INDEX_YRES,(u16_t)(y));

    return 0;
}
sint_t bga_set_vwh(void* ghpdev,uint_t vwt,uint_t vhi)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    bga_write_reg(VBE_DISPI_INDEX_VIRT_WIDTH,(u16_t)vwt);
    bga_write_reg(VBE_DISPI_INDEX_VIRT_HEIGHT,(u16_t)vhi);
    return 0;
}
sint_t bga_set_xyoffset(void* ghpdev,uint_t xoff,uint_t yoff)
{
   // dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    bga_write_reg(VBE_DISPI_INDEX_X_OFFSET,(u16_t)(xoff));
    bga_write_reg(VBE_DISPI_INDEX_Y_OFFSET,(u16_t)(yoff));
    return 0;
}
sint_t bga_get_xy(void* ghpdev,uint_t* rx,uint_t* ry)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    if(rx==NULL||ry==NULL)
    {
        return -1;
    }
    u16_t retx,rety;
    retx=bga_read_reg(VBE_DISPI_INDEX_XRES);
    rety=bga_read_reg(VBE_DISPI_INDEX_YRES);
    *rx=(uint_t)retx;
    *ry=(uint_t)rety;
    return 0;
}

sint_t bga_get_vwh(void* ghpdev,uint_t* rvwt,uint_t* rvhi)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    if(rvwt==NULL||rvhi==NULL)
    {
        return -1;
    }
    u16_t retwt,rethi;
    retwt=bga_read_reg(VBE_DISPI_INDEX_VIRT_WIDTH);
    rethi=bga_read_reg(VBE_DISPI_INDEX_VIRT_HEIGHT);
    *rvwt=(uint_t)retwt;
    *rvhi=(uint_t)rethi;
    return 0;
}
sint_t bga_get_xyoffset(void* ghpdev,uint_t* rxoff,uint_t* ryoff)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    if(rxoff==NULL||ryoff==NULL)
    {
        return -1;
    }
    u16_t retxoff,retyoff;
    retxoff=bga_read_reg(VBE_DISPI_INDEX_X_OFFSET);
    retyoff=bga_read_reg(VBE_DISPI_INDEX_Y_OFFSET);
    *rxoff=(uint_t)retxoff;
    *ryoff=(uint_t)retyoff;
    return 0;
}


size_t vbe_read(void* ghpdev,void* outp,size_t rdsz)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    return rdsz;
}
size_t vbe_write(void* ghpdev,void* inp,size_t wesz)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    return wesz;
}
sint_t vbe_ioctrl(void* ghpdev,void* outp,uint_t iocode)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    return -1;
}
void   vbe_flush(void* ghpdev)
{
    dftgraph_t* kghp=(dftgraph_t*)ghpdev;

    u64_t* s=(u64_t*)((uint_t)kghp->gh_fvrmphyadr);
    u64_t* d=(u64_t*)((uint_t)kghp->gh_framphyadr);
    u64_t i=0,j=0;
    u64_t e=kghp->gh_x*kghp->gh_y*kghp->gh_onepixbyte;
    //u64_t k=e/8;
    for(;i<e;i+=8)
    {
//        if(d[j]==s[j])
//        {

//            d[j]=s[j];
//        }
        d[j]=s[j];
        j++;
    }
    return;
}
sint_t vbe_set_bank(void* ghpdev, sint_t bnr)
{
    return -1;
}
pixl_t vbe_readpix(void* ghpdev,uint_t x,uint_t y)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    return 0;
}
void   vbe_writepix(void* ghpdev,pixl_t pix,uint_t x,uint_t y)
{
    dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    u8_t* p24bas;//=(u8_t*)kghp->gh_framphyadr;
    if(kghp->gh_onepixbits==24)
    {
            u64_t p24adr=(x+(y*kghp->gh_x))*3;
            p24bas=(u8_t*)((uint_t)(p24adr+kghp->gh_fvrmphyadr));
            p24bas[0]=(u8_t)(pix);
            p24bas[1]=(u8_t)(pix>>8);//pvalptr->cl_g;
            p24bas[2]=(u8_t)(pix>>16);//pvalptr->cl_r;
            return;

    }
    u32_t* phybas=(u32_t*)((uint_t)kghp->gh_fvrmphyadr);
    phybas[x+(y*kghp->gh_x)]=pix;
    return;
}
pixl_t vbe_dxreadpix(void* ghpdev,uint_t x,uint_t y)
{
    //dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    return 0;
}
void   vbe_dxwritepix(void* ghpdev,pixl_t pix,uint_t x,uint_t y)
{
    dftgraph_t* kghp=(dftgraph_t*)ghpdev;
    u8_t* p24bas;//=(u8_t*)kghp->gh_framphyadr;
    if(kghp->gh_onepixbits==24)
    {
            u64_t p24adr=(x+(y*kghp->gh_x))*3;
            p24bas=(u8_t*)((uint_t)(p24adr+kghp->gh_framphyadr));
            p24bas[0]=(u8_t)(pix);
            p24bas[1]=(u8_t)(pix>>8);//pvalptr->cl_g;
            p24bas[2]=(u8_t)(pix>>16);//pvalptr->cl_r;
            return;

    }
    u32_t* phybas=(u32_t*)((uint_t)kghp->gh_framphyadr);
    phybas[x+(y*kghp->gh_x)]=pix;
    return;
}
sint_t vbe_set_xy(void* ghpdev,uint_t x,uint_t y)
{
    return -1;
}
sint_t vbe_set_vwh(void* ghpdev,uint_t vwt,uint_t vhi)
{
    return -1;
}
sint_t vbe_set_xyoffset(void* ghpdev,uint_t xoff,uint_t yoff)
{
    return -1;
}
sint_t vbe_get_xy(void* ghpdev,uint_t* rx,uint_t* ry)
{
    return -1;
}
sint_t vbe_get_vwh(void* ghpdev,uint_t* rvwt,uint_t* rvhi)
{
    return -1;
}
sint_t vbe_get_xyoffset(void* ghpdev,uint_t* rxoff,uint_t* ryoff)
{

    return -1;
}

