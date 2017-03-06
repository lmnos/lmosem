#include "cmctl.h"

void fs_entry()
{
    return;
}

int strcmpl(const char *a,const char *b)
{


      while (*b&& *a && (*b== *a))
      {

          b++;

          a++;

      }

    return *b - *a;
}

fhdsc_t* get_fileinfo(char_t* fname,machbstart_t* mbsp)
{
    //mlosrddsc_t* mrddadrs=is_imgheadmrddsc();
    mlosrddsc_t* mrddadrs=(mlosrddsc_t*)((u32_t)(mbsp->mb_lmosimgpadr+MLOSDSC_OFF));
    if(mrddadrs->mdc_endgic!=MDC_ENDGIC||
            mrddadrs->mdc_rv!=MDC_RVGIC||
            mrddadrs->mdc_fhdnr<2||
            mrddadrs->mdc_filnr<2)
    {
        kerror("no mrddsc");
    }
    /*if(mrddadrs==NULL)
    {
        error("no mrddsc");
    }*/
    s64_t rethn=-1;
    fhdsc_t* fhdscstart=(fhdsc_t*)((u32_t)(mrddadrs->mdc_fhdbk_s)+((u32_t)(mbsp->mb_lmosimgpadr)));

    for(u64_t i=0;i<mrddadrs->mdc_fhdnr;i++)
    {
        if(strcmpl(fname,fhdscstart[i].fhd_name)==0)
        {
            rethn=(s64_t)i;
            goto ok_l;
        }
    }
    rethn=-1;
ok_l:
    if(rethn<0)
    {
        kerror("not find file");
    }
    return &fhdscstart[rethn];
}

/*void write_shellfile()
{
    fhdsc_t* fhdscstart=find_file("lmosinitshell.bin");
    if(fhdscstart==NULL)
    {
        kerror("not file lmosinitshell");
    }
    memcopy((void*)((u32_t)(fhdscstart->fhd_intsfsoff)+LDRFILEADR),
            (void*)IMGSHEL_PHYADR,(uint_t)fhdscstart->fhd_frealsz);
    kprint("IMG UNPACK file:%s to:%x filesz:%d\n",fhdscstart->fhd_name,IMGSHEL_PHYADR,(uint_t)fhdscstart->fhd_frealsz);

    return;
}

void write_kernelfile()
{
    fhdsc_t* fhdscstart=find_file("lmoskrnl.bin");
    if(fhdscstart==NULL)
    {
        kerror("not file lmoskrnl");
    }
    memcopy((void*)((u32_t)(fhdscstart->fhd_intsfsoff)+LDRFILEADR),
            (void*)IMGKRNL_PHYADR,(uint_t)fhdscstart->fhd_frealsz);
    kprint("IMG UNPACK file:%s to:%x filesz:%d\n",fhdscstart->fhd_name,IMGKRNL_PHYADR,(uint_t)fhdscstart->fhd_frealsz);

    return;
}*/


int move_krlimg(machbstart_t* mbsp,u64_t cpyadr,u64_t cpysz)
{

    if(0xffffffff<=(cpyadr+cpysz)||1>cpysz)
    {
        return 0;
    }
    void* toadr=(void*)((u32_t)(P4K_ALIGN(cpyadr+cpysz)));
    sint_t tosz=(sint_t)mbsp->mb_lmosimgsz;
    if(0!=adrzone_is_ok(mbsp->mb_lmosimgpadr,mbsp->mb_lmosimgsz,cpyadr,cpysz))
    {
        if(NULL==chk_memsize((e820map_t*)((u32_t)(mbsp->mb_e820padr)),(u32_t)mbsp->mb_e820nr,(u64_t)((u32_t)toadr),(u64_t)tosz))
        {
            return -1;
        }
        m2mcopy((void*)((u32_t)mbsp->mb_lmosimgpadr),toadr,tosz);
        mbsp->mb_lmosimgpadr=(u64_t)((u32_t)toadr);
        return 1;
    }
    return 2;
}

void init_krlfile(machbstart_t* mbsp)
{
    u64_t sz=r_file_to_padr(mbsp,IMGKRNL_PHYADR,"lmosemkrnl.bin");
    if(0==sz)
    {
        kerror("ik_rfilepadr err");
    }
    mbsp->mb_krlimgpadr=IMGKRNL_PHYADR;
    mbsp->mb_krlsz=sz;
    mbsp->mb_nextwtpadr=P4K_ALIGN(mbsp->mb_krlimgpadr+mbsp->mb_krlsz);
    mbsp->mb_kalldendpadr=mbsp->mb_krlimgpadr+mbsp->mb_krlsz;
    return;
}

void init_defutfont(machbstart_t *mbsp)
{
    u32_t retadr=0,sz=0;
    u32_t dfadr=(u32_t)mbsp->mb_nextwtpadr;
    get_file_rpadrandsz("lmos.fnt",mbsp,&retadr,&sz);
    if(0==retadr)
    {
        kerror("if_getfilerpadrsz err");
    }
    if(1>move_krlimg(mbsp,mbsp->mb_nextwtpadr,sz))
    {
        kerror("if_moveimg err");
    }
    m2mcopy((void*)retadr,(void*)dfadr,(sint_t)sz);
    mbsp->mb_bfontpadr=(u64_t)(dfadr);
    mbsp->mb_bfontsz=sz;
    mbsp->mb_nextwtpadr=P4K_ALIGN((u32_t)(dfadr)+sz);
    mbsp->mb_kalldendpadr=mbsp->mb_bfontpadr+mbsp->mb_bfontsz;
    return;
}


void get_file_rpadrandsz(char_t *fname, machbstart_t* mbsp,u32_t* retadr,u32_t* retsz)
{
    u64_t padr=0,fsz=0;
    if(NULL==fname||NULL==mbsp)
    {
        *retadr=0;
        return;
    }
    fhdsc_t* fhdsc=get_fileinfo(fname,mbsp);
    if(fhdsc==NULL)
    {
        *retadr=0;
        return;
    }
    padr=fhdsc->fhd_intsfsoff+mbsp->mb_lmosimgpadr;
    if(padr>0xffffffff)
    {
        *retadr=0;
        return;
    }
    fsz=(u32_t)fhdsc->fhd_frealsz;
    if(fsz>0xffffffff)
    {
        *retadr=0;
        return;
    }
    *retadr=(u32_t)padr;
    *retsz=(u32_t)fsz;
    return;
}

u64_t get_filesz(char_t* filenm,machbstart_t* mbsp)
{
    if(filenm==NULL||mbsp==NULL)
    {
        return 0;
    }
    fhdsc_t* fhdscstart=get_fileinfo(filenm,mbsp);
    if(fhdscstart==NULL)
    {
        return 0;
    }
    return fhdscstart->fhd_frealsz;
}

u64_t get_wt_lmosimgfilesz(machbstart_t* mbsp)
{
    u64_t retsz=LDRFILEADR;
    mlosrddsc_t* mrddadrs=MRDDSC_ADR;
    if(mrddadrs->mdc_endgic!=MDC_ENDGIC||
            mrddadrs->mdc_rv!=MDC_RVGIC||
            mrddadrs->mdc_fhdnr<2||
            mrddadrs->mdc_filnr<2)
    {
        return 0;
    }
    if(mrddadrs->mdc_filbk_e<0x4000)
    {
        return 0;
    }
    retsz+=mrddadrs->mdc_filbk_e;
    retsz-=LDRFILEADR;
    mbsp->mb_lmosimgpadr=LDRFILEADR;
    mbsp->mb_lmosimgsz=retsz;
    return retsz;
}

u64_t r_file_to_padr(machbstart_t* mbsp,u32_t f2adr,char_t* fnm)
{
    if(NULL==f2adr||NULL==fnm||NULL==mbsp)
    {
        return 0;
    }
    u32_t fpadr=0,sz=0;
    get_file_rpadrandsz(fnm,mbsp,&fpadr,&sz);
    if(0==fpadr||0==sz)
    {
        return 0;
    }
    if(NULL==chk_memsize((e820map_t*)((u32_t)mbsp->mb_e820padr),(u32_t)(mbsp->mb_e820nr),f2adr,sz))
    {
        return 0;
    }
    if(0!=chkadr_is_ok(mbsp,f2adr,sz))
    {
        return 0;
    }
    m2mcopy((void*)fpadr,(void*)f2adr,(sint_t)sz);
    return sz;
}

void set_rwhdhdpack(rwhdpach_t* setp,u8_t sn,u16_t off,u16_t seg,u32_t lbal,u32_t lbah)
{
    setp->rwhpk_sz=0x10;
    setp->rwhpk_rv=0;
    setp->rwhpk_sn=sn;
    setp->rwhpk_rv1=0;
    setp->rwhpk_of=off;
    setp->rwhpk_se=seg;
    setp->rwhpk_ll=lbal;
    setp->rwhpk_lh=lbah;
    return;
}

void* read_sector(u64_t sector)
{
    set_rwhdhdpack((rwhdpach_t*)RWHDPACK_ADR,1,READHD_BUFADR,0,(((u32_t)sector)),(u32_t)(sector>>32));
    realadr_call_entry(RLINTNR(1),0,0);
    return (void*)READHD_BUFADR;
}

void ret_mbr()
{
    void*p=read_sector(0);
    mbr_t* mbrp=(mbr_t*)p;
    uint_t ebrs=0;
    u64_t exstor=0;
    u64_t mexts=0;
    int mnr=0;
rety:
    ebrs=0;
    for(uint_t i=0;i<4;i++)
    {
        if(mbrp->mb_part[i].dp_ptype==0x5||mbrp->mb_part[i].dp_ptype==0xf)
        {
            ebrs=1;
            exstor=mbrp->mb_part[i].dp_pslba;
            if(mnr==0)
            {   exstor=0;
                mexts=mbrp->mb_part[i].dp_pslba;
                mnr=1;
            }
            exstor+=mexts;
            kprint("extpartition(%x): boot:%x type:%x startsector:%d sectorlen:%d\n",i,
                   mbrp->mb_part[i].dp_bmgic,mbrp->mb_part[i].dp_ptype,
                   mbrp->mb_part[i].dp_pslba,mbrp->mb_part[i].dp_plbasz);
            continue;
        }
        if(is_part(&mbrp->mb_part[i]))
        kprint("partition(%x): boot:%x type:%x startsector:%d sectorlen:%d\n",i,
               mbrp->mb_part[i].dp_bmgic,mbrp->mb_part[i].dp_ptype,
               mbrp->mb_part[i].dp_pslba,mbrp->mb_part[i].dp_plbasz);
    }

    if(ebrs==0)
    {
        return;
    }
    p=read_sector(exstor);
    mbrp=(mbr_t*)p;
    goto rety;
    return;
}

int is_part(dpt_t* isp)
{

    if(isp->dp_ptype==0)
    {
        return 0;
    }
    if(isp->dp_pslba==0)
    {
        return 0;
    }
    if(isp->dp_plbasz==0)
    {
        return 0;
    }


    return 1;
}

u64_t ret_imgfilesz()
{
    u64_t retsz=LDRFILEADR;
    mlosrddsc_t* mrddadrs=MRDDSC_ADR;
    if(mrddadrs->mdc_endgic!=MDC_ENDGIC||
            mrddadrs->mdc_rv!=MDC_RVGIC||
            mrddadrs->mdc_fhdnr<2||
            mrddadrs->mdc_filnr<2)
    {
        kerror("no mrddsc");
    }
    if(mrddadrs->mdc_filbk_e<0x4000)
    {
        kerror("imgfile error");
    }
    retsz+=mrddadrs->mdc_filbk_e;
    retsz-=LDRFILEADR;
    return retsz;
}
