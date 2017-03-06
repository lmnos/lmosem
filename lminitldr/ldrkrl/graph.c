#include "cmctl.h"


void write_pixcolor(machbstart_t* mbsp,u32_t x,u32_t y,pixl_t pix)
{

    u8_t* p24bas;//=(u8_t*)kghp->gh_framphyadr;
    if(mbsp->mb_ghparm.gh_onepixbits==24)
    {
            u32_t p24adr=(x+(y*mbsp->mb_ghparm.gh_x))*3;
            p24bas=(u8_t*)(p24adr+mbsp->mb_ghparm.gh_framphyadr);
            p24bas[0]=(u8_t)(pix);
            p24bas[1]=(u8_t)(pix>>8);//pvalptr->cl_g;
            p24bas[2]=(u8_t)(pix>>16);//pvalptr->cl_r;
            return;

    }
    u32_t* phybas=(u32_t*)mbsp->mb_ghparm.gh_framphyadr;
    phybas[x+(y*mbsp->mb_ghparm.gh_x)]=pix;
    //u32_t* phybas=(u32_t*)mbsp->mb_ghparm.gh_framphyadr;
    //phybas[x+(y*1024)]=*((u32_t*)pvalptr);
    return;
}

void bmp_print(void* bmfile,machbstart_t* mbsp)
{
    if(NULL==bmfile)
    {
        return;
    }
    pixl_t pix=0;
    bmdbgr_t* bpixp=NULL;
    bmfhead_t* bmphdp=(bmfhead_t*)bmfile;
    bitminfo_t* binfp= (bitminfo_t*)(bmphdp+1);
    u32_t img=(u32_t)bmfile+bmphdp->bf_off;
    bpixp=(bmdbgr_t*)img;
    int l=0;//binfp->bi_h;
    int k=0;
    int ilinebc = (((binfp->bi_w*24) + 31) >> 5) << 2;
    for(int y=639;y>=129;y--,l++)
    {
        k=0;
        for(int x=322;x<662;x++)
        {
            pix=BGRA(bpixp[k].bmd_r,bpixp[k].bmd_g,bpixp[k].bmd_b);
            if(50<l)
            {
                if(0x00ffffff<=pix||pix>=0x00999999)
            {
                pix=0;
            }
            }
            
            write_pixcolor(mbsp,x,y,pix);
            k++;
        }
        bpixp=(bmdbgr_t*)(((int)bpixp)+ilinebc);
    } 
    return;
}

void logo(machbstart_t* mbsp)
{
    u32_t retadr=0,sz=0;
    get_file_rpadrandsz("LMOSEMLOGOX.bmp",mbsp,&retadr,&sz);
    if(0==retadr)
    {
        kerror("if_getfilerpadrsz err");
    }
    bmp_print((void*)retadr,mbsp);

    return;
}


void init_graph(machbstart_t* mbsp)
{
    graph_t_init(&mbsp->mb_ghparm);
    init_bgadevice(mbsp);
    if(mbsp->mb_ghparm.gh_mode!=BGAMODE)
    {
        get_vbemode(mbsp);
        get_vbemodeinfo(mbsp);
        set_vbemodeinfo();
    }

    init_kinitfvram(mbsp);
    logo(mbsp);
    return;
}

void graph_t_init(graph_t* initp)
{
    memset(initp,0,sizeof(graph_t));
    return;
}

void init_kinitfvram(machbstart_t* mbsp)
{
    mbsp->mb_fvrmphyadr=KINITFRVM_PHYADR;
    mbsp->mb_fvrmsz=KINITFRVM_SZ;
    memset((void*)KINITFRVM_PHYADR,0,KINITFRVM_SZ);

    return;
}

u32_t vfartolineadr(u32_t vfar)
{
    u32_t tmps=0,sec=0,off=0;
    off=vfar&0xffff;
    tmps=(vfar>>16)&0xffff;
    sec=tmps<<4;
    return (sec+off);
}


void get_vbemode(machbstart_t* mbsp)
{
    realadr_call_entry(RLINTNR(2),0,0);
    vbeinfo_t* vbeinfoptr=(vbeinfo_t*)VBEINFO_ADR;
    u16_t* mnm;

    if(vbeinfoptr->vbesignature[0]!='V'||
            vbeinfoptr->vbesignature[1]!='E'||
            vbeinfoptr->vbesignature[2]!='S'||
            vbeinfoptr->vbesignature[3]!='A')
    {
        kerror("vbe is not VESA");
    }
    kprint("vbe vbever:%x\n",vbeinfoptr->vbeversion);
    if(vbeinfoptr->vbeversion<0x0200)
    {
        kerror("vbe version not vbe3");
    }

    if(vbeinfoptr->videomodeptr>0xffff)
    {
        mnm=(u16_t*)vfartolineadr(vbeinfoptr->videomodeptr);//
    }
    else
    {
        mnm=(u16_t*)(vbeinfoptr->videomodeptr);
    }

    int bm=0;
    for(int i=0;mnm[i]!=0xffff;i++)
    {
        if(mnm[i]==0x118)
        {
            bm=1;
        }
        if(i>0x1000)
        {
            break;
        }
        //kprint("vbemode:%x  ",mnm[i]);
    }

    if(bm==0)
    {
        kerror("getvbemode not 118");
    }
    mbsp->mb_ghparm.gh_mode=VBEMODE;
    mbsp->mb_ghparm.gh_vbemodenr=0x118;
    mbsp->mb_ghparm.gh_vifphyadr=VBEINFO_ADR;
    m2mcopy(vbeinfoptr,&mbsp->mb_ghparm.gh_vbeinfo,sizeof(vbeinfo_t));
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

u32_t get_bgadevice()
{
    u16_t bgaid=bga_read_reg(VBE_DISPI_INDEX_ID);
    if(BGA_DEV_ID0<=bgaid&&BGA_DEV_ID5>=bgaid)
    {
        bga_write_reg(VBE_DISPI_INDEX_ID,bgaid);
        if(bga_read_reg(VBE_DISPI_INDEX_ID)!=bgaid)
        {
            return 0;
        }
        return (u32_t)bgaid;
    }
    return 0;
}

u32_t chk_bgamaxver()
{
    bga_write_reg(VBE_DISPI_INDEX_ID,BGA_DEV_ID5);
    if(bga_read_reg(VBE_DISPI_INDEX_ID)==BGA_DEV_ID5)
    {
        return (u32_t)BGA_DEV_ID5;
    }
    bga_write_reg(VBE_DISPI_INDEX_ID,BGA_DEV_ID4);
    if(bga_read_reg(VBE_DISPI_INDEX_ID)==BGA_DEV_ID4)
    {
        return (u32_t)BGA_DEV_ID4;
    }
    bga_write_reg(VBE_DISPI_INDEX_ID,BGA_DEV_ID3);
    if(bga_read_reg(VBE_DISPI_INDEX_ID)==BGA_DEV_ID3)
    {
        return (u32_t)BGA_DEV_ID3;
    }
    bga_write_reg(VBE_DISPI_INDEX_ID,BGA_DEV_ID2);
    if(bga_read_reg(VBE_DISPI_INDEX_ID)==BGA_DEV_ID2)
    {
        return (u32_t)BGA_DEV_ID2;
    }
    bga_write_reg(VBE_DISPI_INDEX_ID,BGA_DEV_ID1);
    if(bga_read_reg(VBE_DISPI_INDEX_ID)==BGA_DEV_ID1)
    {
        return (u32_t)BGA_DEV_ID1;
    }
    bga_write_reg(VBE_DISPI_INDEX_ID,BGA_DEV_ID0);
    if(bga_read_reg(VBE_DISPI_INDEX_ID)==BGA_DEV_ID0)
    {
        return (u32_t)BGA_DEV_ID0;
    }
    return 0;
}



void init_bgadevice(machbstart_t* mbsp)
{
    u32_t retdevid=get_bgadevice();
    if(0==retdevid)
    {
        return;
    }
    retdevid=chk_bgamaxver();
    if(0==retdevid)
    {
        return;
    }
    bga_write_reg(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
    bga_write_reg(VBE_DISPI_INDEX_XRES, 1024);
    bga_write_reg(VBE_DISPI_INDEX_YRES, 768);
    bga_write_reg(VBE_DISPI_INDEX_BPP, 0x20);
    bga_write_reg(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED|(VBE_DISPI_LFB_ENABLED)); //|(ClearVideoMemory ? 0 : VBE_DISPI_NOCLEARMEM));
    mbsp->mb_ghparm.gh_mode=BGAMODE;
    mbsp->mb_ghparm.gh_vbemodenr=retdevid;
    mbsp->mb_ghparm.gh_x=1024;
    mbsp->mb_ghparm.gh_y=768;
    mbsp->mb_ghparm.gh_framphyadr=0xe0000000;
    mbsp->mb_ghparm.gh_onepixbits=0x20;
    mbsp->mb_ghparm.gh_bank=4;
    mbsp->mb_ghparm.gh_curdipbnk=0;
    mbsp->mb_ghparm.gh_nextbnk=0;
    mbsp->mb_ghparm.gh_banksz=(mbsp->mb_ghparm.gh_x*mbsp->mb_ghparm.gh_x*4);
    //test_bga();
    return;
}

void  test_bga()
{
    int* p=(int*)(0xe0000000);
    int* p2=(int*)(0xe0000000+(1024*768*4));
    int* p3=(int*)(0xe0000000+(1024*768*4)*2);

        for(int i=0;i<(1024*768);i++)
        {
            p2[i]=0x00ff00ff;
        }
        //die(0x200);VBE_DISPI_INDEX_VIRT_HEIGHT
        for(int i=0;i<(1024*768);i++)
        {
            p[i]=0x0000ff00;
        }
        for(int i=0;i<(1024*768);i++)
        {
            p3[i]=0x00ff0000;
        }
    for(;;)
    {
        bga_write_reg(VBE_DISPI_INDEX_X_OFFSET,0);
        bga_write_reg(VBE_DISPI_INDEX_Y_OFFSET,0);
        bga_write_reg(VBE_DISPI_INDEX_VIRT_WIDTH,1024);
        bga_write_reg(VBE_DISPI_INDEX_VIRT_HEIGHT,768);
        die(0x400);
        bga_write_reg(VBE_DISPI_INDEX_X_OFFSET,0);
        bga_write_reg(VBE_DISPI_INDEX_Y_OFFSET,768);
        bga_write_reg(VBE_DISPI_INDEX_VIRT_WIDTH,1024);
        bga_write_reg(VBE_DISPI_INDEX_VIRT_HEIGHT,768*2);
        die(0x400);
        bga_write_reg(VBE_DISPI_INDEX_X_OFFSET,0);
        bga_write_reg(VBE_DISPI_INDEX_Y_OFFSET,768*2);
        bga_write_reg(VBE_DISPI_INDEX_VIRT_WIDTH,1024);
        bga_write_reg(VBE_DISPI_INDEX_VIRT_HEIGHT,768*3);
        die(0x400);
    }

    for(;;);
    return;
}


void get_vbemodeinfo(machbstart_t* mbsp)
{
    realadr_call_entry(RLINTNR(3),0,0);
    vbeominfo_t* vomif=(vbeominfo_t*)VBEMINFO_ADR;
    u32_t x=vomif->XResolution,y=vomif->YResolution;
    u32_t* phybass=(u32_t*)(vomif->PhysBasePtr);
    if(vomif->BitsPerPixel<24)
    {
        kerror("vomif->BitsPerPixel!=32");
    }
    if(x!=1024||y!=768)
    {
        kerror("xy not");
    }
    if((u32_t)phybass<0x100000)
    {
        kerror("phybass not");
    }
    mbsp->mb_ghparm.gh_x=vomif->XResolution;
    mbsp->mb_ghparm.gh_y=vomif->YResolution;
    mbsp->mb_ghparm.gh_framphyadr=vomif->PhysBasePtr;
    mbsp->mb_ghparm.gh_onepixbits=vomif->BitsPerPixel;
    mbsp->mb_ghparm.gh_vmifphyadr=VBEMINFO_ADR;
    m2mcopy(vomif,&mbsp->mb_ghparm.gh_vminfo,sizeof(vbeominfo_t));

    return;
}

void set_vbemodeinfo()
{
    realadr_call_entry(RLINTNR(4),0,0);
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
