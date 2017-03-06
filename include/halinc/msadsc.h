/**********************************************************
        物理内存空间数组文件msadsc.h
***********************************************************
                彭东 ＠ 2015.05.03.17.00
**********************************************************/
#ifndef _MSADSC_H
#define _MSADSC_H
PUBLIC void msadsc_t_init(msadsc_t* initp);
PUBLIC void disp_one_msadsc(msadsc_t* mp);
PUBLIC bool_t ret_msadsc_vadrandsz(machbstart_t* mbsp,msadsc_t** retmasvp,u64_t* retmasnr);
PUBLIC void write_one_msadsc(msadsc_t* msap,u64_t phyadr);
PUBLIC LKINIT u64_t init_msadsc_core(machbstart_t* mbsp,msadsc_t* msavstart,u64_t msanr);
PUBLIC LKINIT void init_msadsc();
PUBLIC void disp_phymsadsc();
PUBLIC u64_t search_segment_occupymsadsc(msadsc_t* msastart,u64_t msanr,u64_t ocpystat,u64_t ocpyend);
PUBLIC bool_t search_krloccupymsadsc_core(machbstart_t* mbsp);
PUBLIC void init_search_krloccupymm(machbstart_t* mbsp);
#endif