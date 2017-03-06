/****************************************************************
        LMOSEM HAL全局初始化文件halinit.c
*****************************************************************
                彭东 ＠ 2013.07.01.10.30
****************************************************************/

#include "lmosemtypes.h"
#include "lmosemmctrl.h"
void disp_mbsp(machbstart_t* mbsp)
{
    printfk("LMOS内核镜像地址:%x\n",mbsp->mb_lmosimgpadr);
    printfk("LMOS内核镜像大小:%x\n",mbsp->mb_lmosimgsz);
    printfk("LMOS内核地址:%x\n",mbsp->mb_krlimgpadr);
    printfk("LMOS内核大小:%x\n",mbsp->mb_krlsz);
    printfk("物理内存地址区间结构地址:%x\n",mbsp->mb_e820padr);
    printfk("物理内存地址区间结构个数:%x\n",mbsp->mb_e820nr);
    printfk("mbsp->mb_e820sz:%x\n",mbsp->mb_e820sz);
    printfk("mbsp->mb_nextwtpadr:%x\n",mbsp->mb_nextwtpadr);
    printfk("mbsp->mb_kalldendpadr:%x\n",mbsp->mb_kalldendpadr);
    printfk("内核初始化虚拟空间页表地址:%x\n",mbsp->mb_pml4padr);
    printfk("mbsp->mb_subpageslen:%x\n",mbsp->mb_subpageslen);
    printfk("内核初始化虚拟空间映射大小:%x\n",mbsp->mb_kpmapphymemsz);
    printfk("系统处理器工作模式:%x\n",mbsp->mb_cpumode);
    printfk("系统物理内存大小:%x\n",mbsp->mb_memsz);
    printfk("内核初始化栈地址:%x\n",mbsp->mb_krlinitstack);
    printfk("内核初始化栈大小:%x\n",mbsp->mb_krlitstacksz);
    printfk("内核默认字体地址:%x\n",mbsp->mb_bfontpadr);
    printfk("内核默认字体大小:%x\n",mbsp->mb_bfontsz);
    //flush_videoram(&kdftgh);
    //die(0);
    return;
}
void disp_mbspex(machbstart_t* mbsp)
{
//    kprint("mbsp->mb_migc %x\n",mbsp->mb_migc);
//    kprint("mbsp->mb_chksum %x\n",mbsp->mb_chksum);
    printfk("mbsp->mb_krlinitstack %x\n",mbsp->mb_krlinitstack);
    printfk("mbsp->mb_krlitstacksz %x\n",mbsp->mb_krlitstacksz);
    printfk("mbsp->mb_lmosimgpadr %x\n",mbsp->mb_lmosimgpadr);
    printfk("mbsp->mb_lmosimgsz %x\n",mbsp->mb_lmosimgsz);
    printfk("mbsp->mb_krlimgpadr %x\n",mbsp->mb_krlimgpadr);
    printfk("mbsp->mb_krlsz %x\n",mbsp->mb_krlsz);
//    kprint("mbsp->mb_krlvec %x\n",mbsp->mb_krlvec);
//    kprint("mbsp->mb_krlrunmode %x\n",mbsp->mb_krlrunmode);
    printfk("mbsp->mb_kalldendpadr %x\n",mbsp->mb_kalldendpadr);
//    kprint("mbsp->mb_ksepadrs %x\n",mbsp->mb_ksepadrs);
//    kprint("mbsp->mb_ksepadre %x\n",mbsp->mb_ksepadre);
//    kprint("mbsp->mb_kservadrs %x\n",mbsp->mb_kservadrs);
//    kprint("mbsp->mb_kservadre %x\n",mbsp->mb_kservadre);
    printfk("mbsp->mb_nextwtpadr %x\n",mbsp->mb_nextwtpadr);
    printfk("mbsp->mb_bfontpadr %x\n",mbsp->mb_bfontpadr);
    printfk("mbsp->mb_bfontsz %x\n",mbsp->mb_bfontsz);
    printfk("mbsp->mb_fvrmphyadr %x\n",mbsp->mb_fvrmphyadr);
    printfk("mbsp->mb_fvrmsz %x\n",mbsp->mb_fvrmsz);
    printfk("mbsp->mb_cpumode %x\n",mbsp->mb_cpumode);
    printfk("mbsp->mb_memsz %x\n",mbsp->mb_memsz);
    printfk("mbsp->mb_e820padr %x\n",mbsp->mb_e820padr);
    printfk("mbsp->mb_e820nr %x\n",mbsp->mb_e820nr);
    printfk("mbsp->mb_e820sz %x\n",mbsp->mb_e820sz);
    printfk("mbsp->mb_e820expadr %x\n",mbsp->mb_e820expadr);
    printfk("mbsp->mb_e820exnr %x\n",mbsp->mb_e820exnr);
    printfk("mbsp->mb_e820exsz %x\n",mbsp->mb_e820exsz);
    printfk("mbsp->mb_memznpadr %x\n",mbsp->mb_memznpadr);
    printfk("mbsp->mb_memznnr %x\n",mbsp->mb_memznnr);
    printfk("mbsp->mb_memznsz %x\n",mbsp->mb_memznsz);
    printfk("mbsp->mb_memznchksum %x\n",mbsp->mb_memznchksum);
    printfk("mbsp->mb_memmappadr %x\n",mbsp->mb_memmappadr);
    printfk("mbsp->mb_memmapnr %x\n",mbsp->mb_memmapnr);
    printfk("mbsp->mb_memmapsz %x\n",mbsp->mb_memmapsz);
    printfk("mbsp->mb_memmapchksum %x\n",mbsp->mb_memmapchksum);
    printfk("mbsp->mb_pml4padr %x\n",mbsp->mb_pml4padr);
    printfk("mbsp->mb_subpageslen %x\n",mbsp->mb_subpageslen);
    printfk("mbsp->mb_kpmapphymemsz %x\n",mbsp->mb_kpmapphymemsz);

    return;
}
LKHEAD_T void init_hal()
{

    init_paltform();
    move_lmosimg2maxpadr(&kmachbsp);
    //init_haluart();
    //init_halmach();
    init_halmm();
    init_halintupt();
    //print_mach(&osmach);
    //print_mmapdsc(&osmach);
    //disp_mbspex(&kmachbsp);
    //printfk("LMOSEM IS RUN\n");
    //init_8254();
    init_i8259();
    i8259_enabled_line(0);
    //STI();
    //for(;;);
    //test_blkmm();
    return;
}
