#include "cmctl.h"
//extern curs;
void inithead_entry()
{
    init_curs();
    close_curs();
    clear_screen(VGADP_DFVL);
    //kprint("......IMG UNPACK RUN......\n");

    //GxH_strwrite("LMOSLDR RUN",&curs);
    write_realintsvefile();
    write_ldrkrlfile();
    //write_kernelfile();
    //write_shellfile();
    return;
}



void write_realintsvefile()
{

    fhdsc_t* fhdscstart=find_file("lmldrsve.bin");
    if(fhdscstart==NULL)
    {
        error("not file lmldrsve.bin");
    }
    m2mcopy((void*)((u32_t)(fhdscstart->fhd_intsfsoff)+LDRFILEADR),
            (void*)REALDRV_PHYADR,(sint_t)fhdscstart->fhd_frealsz);
    //kprint("IMG UNPACK file:%s to:%x filesz:%d\n",fhdscstart->fhd_name,REALDRV_PHYADR,(uint_t)fhdscstart->fhd_frealsz);
    return;
}

fhdsc_t* find_file(char_t* fname)
{
    //mlosrddsc_t* mrddadrs=is_imgheadmrddsc();
    mlosrddsc_t* mrddadrs=MRDDSC_ADR;
    if(mrddadrs->mdc_endgic!=MDC_ENDGIC||
            mrddadrs->mdc_rv!=MDC_RVGIC||
            mrddadrs->mdc_fhdnr<2||
            mrddadrs->mdc_filnr<2)
    {
        error("no mrddsc");
    }
    /*if(mrddadrs==NULL)
    {
        error("no mrddsc");
    }*/
    s64_t rethn=-1;
    fhdsc_t* fhdscstart=(fhdsc_t*)((u32_t)(mrddadrs->mdc_fhdbk_s)+LDRFILEADR);

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
        error("not find file");
    }
    return &fhdscstart[rethn];
}
void write_ldrkrlfile()
{
    fhdsc_t* fhdscstart=find_file("lmldrkrl.bin");
    if(fhdscstart==NULL)
    {
        error("not file lmldrkrl.bin");
    }
    m2mcopy((void*)((u32_t)(fhdscstart->fhd_intsfsoff)+LDRFILEADR),
            (void*)ILDRKRL_PHYADR,(sint_t)fhdscstart->fhd_frealsz);
    //kprint("IMG UNPACK file:%s to:%x filesz:%d\n",fhdscstart->fhd_name,ILDRKRL_PHYADR,(uint_t)fhdscstart->fhd_frealsz);
    return;
}
/*
mlosrddsc_t*  is_imgheadmrddsc()
{
    mlosrddsc_t* mrddadrs=MRDDSC_ADR;
    if(mrddadrs->mdc_endgic!=MDC_ENDGIC||
            mrddadrs->mdc_rv!=MDC_RVGIC||
            mrddadrs->mdc_fhdnr<2||
            mrddadrs->mdc_filnr<2)
    {
        return NULL;
    }
    return mrddadrs;
}*/

void error(char_t* estr)
{
    kprint("LMOSLDR DIE ERROR:%s\n",estr);
    for(;;);
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
