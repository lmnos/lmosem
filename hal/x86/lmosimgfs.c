/**********************************************************
        LMOS内核映像文件系统文件lmosimgfs.c
***********************************************************
                彭东 ＠ 2014.10.31.12.30
**********************************************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"


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
    mlosrddsc_t* mrddadrs=(mlosrddsc_t*)krnlphyiadr_to_viradr((adr_t)(mbsp->mb_lmosimgpadr+MLOSDSC_OFF));
    if(mrddadrs->mdc_endgic!=MDC_ENDGIC||
            mrddadrs->mdc_rv!=MDC_RVGIC||
            mrddadrs->mdc_fhdnr<2||
            mrddadrs->mdc_filnr<2)
    {
        system_error("no mrddsc");
    }
    /*if(mrddadrs==NULL)
    {
        error("no mrddsc");
    }*/
    s64_t rethn=-1;
    fhdsc_t* fhdscstart=(fhdsc_t*)((uint_t)((mrddadrs->mdc_fhdbk_s)+(krnlphyiadr_to_viradr((adr_t)mbsp->mb_lmosimgpadr))));

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
        system_error("not find file");
    }
    return &fhdscstart[rethn];
}



void get_file_rvadrandsz(char_t *fname, machbstart_t* mbsp,u64_t* retadr,u64_t* retsz)
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
    padr=fhdsc->fhd_intsfsoff+krnlphyiadr_to_viradr((adr_t)mbsp->mb_lmosimgpadr);
    fsz=fhdsc->fhd_frealsz;

    *retadr=padr;
    *retsz=fsz;
    return;
}

e820map_t* get_maxmappadr_e820map(machbstart_t* mbsp,u64_t mappadr)
{
    if(NULL==mbsp)
    {
        return NULL;
    }
    u64_t enr=mbsp->mb_e820nr;
    e820map_t* emp=(e820map_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_e820padr);
    e820map_t* retemp=NULL;
    u64_t maxadr=emp[0].saddr;
    for(u64_t i=0;i<enr;i++)
    {
        //kprint("内存区间开始地址:%x 大小:%x 类型:%x\n",
          //     emp[i].saddr,emp[i].lsize,emp[i].type);
        if(emp[i].type==RAM_USABLE)
        {
            if(emp[i].saddr>maxadr&&(mappadr>(emp[i].saddr+emp[i].lsize)))
            {
                maxadr=emp[i].saddr;
                retemp=&emp[i];
            }
        }
    }
    return retemp;
}
e820map_t* ret_kmaxmpadrcmpsz_e820map(machbstart_t* mbsp,u64_t mappadr,u64_t cpsz)
{
    if(NULL==mbsp)
    {
        return NULL;
    }
    u64_t enr=mbsp->mb_e820nr;
    e820map_t* emp=(e820map_t*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_e820padr);
    e820map_t* retemp=NULL;
    u64_t maxadr=emp[0].saddr;
    for(u64_t i=0;i<enr;i++)
    {
        //kprint("内存区间开始地址:%x 大小:%x 类型:%x\n",
          //     emp[i].saddr,emp[i].lsize,emp[i].type);
        if(emp[i].type==RAM_USABLE)
        {
            if(emp[i].saddr>=maxadr&&(mappadr>(emp[i].saddr+emp[i].lsize))&&
                    (emp[i].lsize>=cpsz))
            {
                maxadr=emp[i].saddr;
                retemp=&emp[i];
            }
        }
    }
    if((mappadr>(retemp->saddr+retemp->lsize))&&(retemp->lsize>=cpsz))
    {
        return retemp;
    }
    return NULL;
}

void move_lmosimg2maxpadr(machbstart_t* mbsp)
{
    u64_t kmapadrend=mbsp->mb_kpmapphymemsz;
    e820map_t* emp=ret_kmaxmpadrcmpsz_e820map(mbsp,kmapadrend,mbsp->mb_lmosimgsz);
    //get_maxmappadr_e820map(mbsp,kmapadrend);
    if(NULL==emp)
    {
        system_error("move_lmosimg2maxpadr1 emp not ok");
    }

    u64_t imgtoadr=(emp->saddr+(emp->lsize-mbsp->mb_lmosimgsz));
    imgtoadr&=~(0xfffUL);
    if(initchkadr_is_ok(mbsp,imgtoadr,mbsp->mb_lmosimgsz)!=0)
    {
        system_error("initchkadr_is_ok not ok\n");
    }
    void* sadr=(void*)krnlphyiadr_to_viradr((adr_t)mbsp->mb_lmosimgpadr);
    void* dadr=(void*)krnlphyiadr_to_viradr((adr_t)imgtoadr);
    if(m2mcopy(sadr,dadr,(sint_t)(mbsp->mb_lmosimgsz))!=((sint_t)(mbsp->mb_lmosimgsz)))
    {
        system_error("move_lmosimg2maxpadr1 m2mcopy not ok");
    }
    mbsp->mb_lmosimgpadr=imgtoadr;
    return;
}
//函数:move_lmosimg2maxpadr中检查相应的地址有问题
int adrzone_is_ok(u64_t sadr,u64_t slen,u64_t kadr,u64_t klen)
{
    if(kadr>=sadr&&kadr<=(sadr+slen))
    {
        return -1;
    }
    /*if(kadr<=sadr&&((kadr+klen)>=(sadr+slen)))
    {
        return -2;
    }*/
    if(kadr<=sadr&&((kadr+klen)>=sadr))
    {
        return -2;
    }

    return 0;
}
/*
typedef struct s_MACHBSTART
{
    u64_t   mb_migc;          //LMOSMBSP//0
    u64_t   mb_chksum;//8
    u64_t   mb_krlinitstack;//16
    u64_t   mb_krlitstacksz;//24
    u64_t   mb_lmosimgpadr;
    u64_t   mb_lmosimgsz;
    u64_t   mb_krlimgpadr;
    u64_t   mb_krlsz;
    u64_t   mb_krlvec;
    u64_t   mb_krlrunmode;
    u64_t   mb_kalldendpadr;
    u64_t   mb_ksepadrs;
    u64_t   mb_ksepadre;
    u64_t   mb_kservadrs;
    u64_t   mb_kservadre;
    u64_t   mb_nextwtpadr;
    u64_t   mb_bfontpadr;
    u64_t   mb_bfontsz;
    u64_t   mb_fvrmphyadr;
    u64_t   mb_fvrmsz;
    u64_t   mb_cpumode;
    u64_t   mb_memsz;
    u64_t   mb_e820padr;
    u64_t   mb_e820nr;
    u64_t   mb_e820sz;
    u64_t   mb_e820expadr;
    u64_t   mb_e820exnr;
    u64_t   mb_e820exsz;
    u64_t   mb_memznpadr;
    u64_t   mb_memznnr;
    u64_t   mb_memznsz;
    u64_t   mb_memznchksum;
    u64_t   mb_memmappadr;
    u64_t   mb_memmapnr;
    u64_t   mb_memmapsz;
    u64_t   mb_memmapchksum;
    u64_t   mb_pml4padr;
    u64_t   mb_subpageslen;
    u64_t   mb_kpmapphymemsz;
    graph_t mb_ghparm;
}__attribute__((packed)) machbstart_t;
*/
int initchkadr_is_ok(machbstart_t* mbsp,u64_t chkadr,u64_t cksz)
{
    //u64_t len=chkadr+cksz;
    if(adrzone_is_ok((mbsp->mb_krlinitstack-mbsp->mb_krlitstacksz),mbsp->mb_krlitstacksz,chkadr,cksz)!=0)
    {
        kprint("(mbsp->mb_krlinitstack-mbsp->mb_krlitstacksz):%x,mbsp->mb_krlitstacksz:%x,chkadr:%x,cksz:%x\n",
               (mbsp->mb_krlinitstack-mbsp->mb_krlitstacksz),mbsp->mb_krlitstacksz,chkadr,cksz);
        return -1;
    }
    if(adrzone_is_ok(mbsp->mb_lmosimgpadr,mbsp->mb_lmosimgsz,chkadr,cksz)!=0)
    {
        kprint("mbsp->mb_lmosimgpadr:%x,mbsp->mb_lmosimgsz:%x,chkadr:%x,cksz:%x\n",
               mbsp->mb_lmosimgpadr,mbsp->mb_lmosimgsz,chkadr,cksz);
        return -2;
    }
    if(adrzone_is_ok(mbsp->mb_krlimgpadr,mbsp->mb_krlsz,chkadr,cksz)!=0)
    {
        kprint("mbsp->mb_krlimgpadr:%x,mbsp->mb_krlsz:%x,chkadr:%x,cksz:%x\n",
               mbsp->mb_krlimgpadr,mbsp->mb_krlsz,chkadr,cksz);
        return -3;
    }
    if(adrzone_is_ok(mbsp->mb_bfontpadr,mbsp->mb_bfontsz,chkadr,cksz)!=0)
    {
        kprint("mbsp->mb_bfontpadr:%x,mbsp->mb_bfontsz:%x,chkadr:%x,cksz:%x\n",
               mbsp->mb_bfontpadr,mbsp->mb_bfontsz,chkadr,cksz);
        return -4;
    }
    if(adrzone_is_ok(mbsp->mb_e820padr,mbsp->mb_e820sz,chkadr,cksz)!=0)
    {
        kprint("mbsp->mb_e820padr:%x,mbsp->mb_e820sz:%x,chkadr:%x,cksz:%x\n",
               mbsp->mb_e820padr,mbsp->mb_e820sz,chkadr,cksz);
        return -5;
    }
    if(adrzone_is_ok(mbsp->mb_memznpadr,mbsp->mb_memznsz,chkadr,cksz)!=0)
    {
        kprint("mbsp->mb_memznpadr:%x,mbsp->mb_memznsz:%x,chkadr:%x,cksz:%x\n",
               mbsp->mb_memznpadr,mbsp->mb_memznsz,chkadr,cksz);
        return -6;
    }
    if(adrzone_is_ok(mbsp->mb_memmappadr,mbsp->mb_memmapsz,chkadr,cksz)!=0)
    {
        kprint("mbsp->mb_memmappadr:%x,mbsp->mb_memmapsz:%x,chkadr:%x,cksz:%x\n",
               mbsp->mb_memznpadr,mbsp->mb_memznsz,chkadr,cksz);
        return -7;
    }
    if(adrzone_is_ok(mbsp->mb_e820expadr,mbsp->mb_e820exsz,chkadr,cksz)!=0)
    {
        kprint("mbsp->mb_e820expadr:%x,mbsp->mb_e820exsz:%x,chkadr:%x,cksz:%x\n",
               mbsp->mb_e820expadr,mbsp->mb_e820exsz,chkadr,cksz);
        return -8;
    }
    if((chkadr+cksz)>=mbsp->mb_kpmapphymemsz)
    {
        kprint("mbsp->mb_kpmapphymemsz:%x,chkadr:%x,cksz:%x\n",
               mbsp->mb_kpmapphymemsz,chkadr,cksz);
        return -9;
    }
    /*e820map_t* emp=chk_memsize((e820map_t*)krnlphyiadr_to_viradr(mbsp->mb_e820padr),mbsp->mb_e820nr,chkadr,cksz);
    if(emp==NULL)
    {
        system_error("chk_memsize 252\n");
        return -10;
    }
    if((mbsp->mb_krlimgpadr<emp->saddr)&&
            ((mbsp->mb_krlimgpadr+mbsp->mb_krlsz)>(emp->saddr+emp->lsize)))
    {
        kprint("");
        system_error("258\n");
        return -11;
    }*/
    return 0;
}

e820map_t* chk_memsize(e820map_t* e8p,u64_t enr,u64_t sadr,u64_t size)
{
    u64_t len=sadr+size;
    if(enr==0||e8p==NULL)
    {
        system_error("279\n");
        return NULL;
    }
    for(u32_t i=0;i<enr;i++)
    {
        if(e8p[i].type==RAM_USABLE)
        {
            kprint("e8p[%x].saddr:%x ==== e8p[i].saddr+e8p[i].lsize:%x ==== csadr:%x ==== csize:%x ==== len:%x\n",
                   i,e8p[i].saddr,(e8p[i].saddr+e8p[i].lsize),sadr,size,len);
            if((sadr>=e8p[i].saddr)&&(len<=(e8p[i].saddr+e8p[i].lsize)))
            {
                return &e8p[i];
            }
        }
    }
    system_error("292\n");
    return NULL;
}

/*
int move_krlimg(machbstart_t* mbsp,u64_t cpyadr,u64_t cpysz)
{

    if(0xffffffff<=(cpyadr+cpysz)||1>cpysz)
    {
        return 0;
    }
    void* toadr=(void*)((P4K_ALIGN(cpyadr+cpysz)));
    sint_t tosz=(sint_t)mbsp->mb_lmosimgsz;
    if(0!=adrzone_is_ok(mbsp->mb_lmosimgpadr,mbsp->mb_lmosimgsz,cpyadr,cpysz))
    {
        if(0==chk_memsize((e820map_t*)((u32_t)(mbsp->mb_e820padr)),(u32_t)mbsp->mb_e820nr,(u64_t)((u32_t)toadr),(u64_t)tosz))
        {
            return -1;
        }
        m2mcopy((void*)((u32_t)mbsp->mb_lmosimgpadr),toadr,tosz);
        mbsp->mb_lmosimgpadr=(u64_t)(toadr);
        return 1;
    }
    return 2;
}*/




