#include "cmctl.h"
void testm2m()
{
    u8_t* s=(u8_t*)0x400000;
    u8_t* d=(u8_t*)(0x400000-1);
    for(u8_t i=0;i<10;i++)
    {
        s[i]=i;
    }
    for(u8_t j=0;j<10;j++)
    {
        kprint("s[%d]:%d\n",j,s[j]);
    }
    m2mcopy(s,d,10);
    for(u8_t k=0;k<10;k++)
    {
        kprint("d[%d]:%d\n",k,d[k]);
    }
    die(0);
    return;
}
void disp_mbsp(machbstart_t* mbsp)
{
    kprint("mbsp->mb_lmosimgpadr:%x\n",mbsp->mb_lmosimgpadr);
    kprint("mbsp->mb_lmosimgsz:%x\n",mbsp->mb_lmosimgsz);
    kprint("mbsp->mb_krlimgpadr:%x\n",mbsp->mb_krlimgpadr);
    kprint("mbsp->mb_krlimgsz:%x\n",mbsp->mb_krlsz);
    kprint("mbsp->mb_e820padr:%x\n",mbsp->mb_e820padr);
    kprint("mbsp->mb_e820nr:%x\n",mbsp->mb_e820nr);
    kprint("mbsp->mb_e820sz:%x\n",mbsp->mb_e820sz);
    kprint("mbsp->mb_nextwtpadr:%x\n",mbsp->mb_nextwtpadr);
    kprint("mbsp->mb_kalldendpadr:%x\n",mbsp->mb_kalldendpadr);
    kprint("mbsp->mb_pml4padr:%x\n",mbsp->mb_pml4padr);
    kprint("mbsp->mb_subpageslen:%x\n",mbsp->mb_subpageslen);
    kprint("mbsp->mb_kpmapphymemsz:%x\n",mbsp->mb_kpmapphymemsz);
    kprint("mbsp->mb_cpumode:%x\n",mbsp->mb_cpumode);
    kprint("mbsp->mb_memsz:%x\n",mbsp->mb_memsz);
    kprint("mbsp->mb_krlinitstack:%x\n",mbsp->mb_krlinitstack);
    kprint("mbsp->mb_krlitstacksz:%x\n",mbsp->mb_krlitstacksz);
    kprint("mbsp->mb_bfontpadr:%x\n",mbsp->mb_bfontpadr);
    kprint("mbsp->mb_bfontsz:%x\n",mbsp->mb_bfontsz);
    die(0);
    return;
}
void init_bstartparm()
{
    machbstart_t* mbsp=MBSPADR;
    machbstart_t_init(mbsp);
    init_chkcpu(mbsp);
    init_mem(mbsp);
    if(0==get_wt_lmosimgfilesz(mbsp))
    {
        kerror("lmosimgfilesz 0");
    }
    init_krlinitstack(mbsp);
    init_krlfile(mbsp);
    init_defutfont(mbsp);
    init_meme820(mbsp);
    init_bstartpages(mbsp);
    //disp_mbsp(mbsp);
    //init_kernel_pml4();
    init_graph(mbsp);
    //die(0);
    return;
}
void machbstart_t_init(machbstart_t* initp)
{
    memset(initp,0,sizeof(machbstart_t));
    initp->mb_migc=MBS_MIGC;
    return;
}

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

int chkadr_is_ok(machbstart_t* mbsp,u64_t chkadr,u64_t cksz)
{
    //u64_t len=chkadr+cksz;
    if(adrzone_is_ok((mbsp->mb_krlinitstack-mbsp->mb_krlitstacksz),mbsp->mb_krlitstacksz,chkadr,cksz)!=0)
    {
        return -1;
    }
    if(adrzone_is_ok(mbsp->mb_lmosimgpadr,mbsp->mb_lmosimgsz,chkadr,cksz)!=0)
    {
        return -2;
    }
    if(adrzone_is_ok(mbsp->mb_krlimgpadr,mbsp->mb_krlsz,chkadr,cksz)!=0)
    {
        return -3;
    }
    if(adrzone_is_ok(mbsp->mb_bfontpadr,mbsp->mb_bfontsz,chkadr,cksz)!=0)
    {
        return -4;
    }
    if(adrzone_is_ok(mbsp->mb_e820padr,mbsp->mb_e820sz,chkadr,cksz)!=0)
    {
        return -5;
    }
    if(adrzone_is_ok(mbsp->mb_memznpadr,mbsp->mb_memznsz,chkadr,cksz)!=0)
    {
        return -6;
    }
    if(adrzone_is_ok(mbsp->mb_memmappadr,mbsp->mb_memmapsz,chkadr,cksz)!=0)
    {
        return -7;
    }
    return 0;
}




/*
{
"show_output_panel": false,
"dont_prepend_clang_includes": false,
"inhibit_sublime_completions": true,

"options":
[
"-isystem", "/home/lmos/lmos-00.08/",
"-isystem", "/home/lmos/lmos-00.08/arch/x86_64/include/",
"-isystem", "/home/lmos/lmos-00.08/include/",
"-isystem", "/home/lmos/lmos-00.08/include/apiinc",
"-isystem", "/home/lmos/lmos-00.08/include/buildinc",
"-isystem", "/home/lmos/lmos-00.08/include/devmgrinc",
"-isystem", "/home/lmos/lmos-00.08/include/fsinc",
"-isystem", "/home/lmos/lmos-00.08/include/ifemgrinc",
"-isystem", "/home/lmos/lmos-00.08/include/intmgrinc",
"-isystem", "/home/lmos/lmos-00.08/include/kernelinc",
"-isystem", "/home/lmos/lmos-00.08/include/kobmgrinc",
"-isystem", "/home/lmos/lmos-00.08/include/libinc",
"-isystem", "/home/lmos/lmos-00.08/include/memmgrinc",
"-isystem", "/home/lmos/lmos-00.08/include/mminc",
"-isystem", "/home/lmos/lmos-00.08/arch/x86_64/kernel/",
"-isystem", "/home/lmos/lmos-00.08/drivers/",
"-isystem", "/home/lmos/lmos-00.08/drivers/drvinc/",
"-isystem", "/home/lmos/lmos-00.08/fs/",
"-isystem", "/home/lmos/lmos-00.08/ipc/",
"-isystem", "/home/lmos/lmos-00.08/kernel/",
"-isystem", "/home/lmos/lmos-00.08/lib/",
"-isystem", "/home/lmos/lmos-00.08/mm/",
]
}
*/