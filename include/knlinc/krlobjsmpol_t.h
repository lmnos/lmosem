/**********************************************************
        内核层内存对象池管理头文件krlobjsmpol_t.h
***********************************************************
                彭东 ＠ 2013.07.18.15.00
**********************************************************/
#ifndef _KRLOBJSMPOL_T_H
#define _KRLOBJSMPOL_T_H

#define OBJALST_MAX 15
#define OBJALCSZ_MAX 2048


typedef struct s_OLCFGDAT
{
    size_t ocd_objsz;
    size_t ocd_nmpsz;
}olcfgdat_t;

typedef struct s_OBJMGRHEAD
{
    list_h_t    omh_list;
    struct s_OBJALST* omh_paralst;
    size_t      omh_objsz;
    size_t      omh_aligobjsz;
    size_t      omh_npinobjsz;
    uint_t      omh_objnr;
    uint_t      omh_alfrindx;
    adr_t       omh_start;
    adr_t       omh_end;
    adr_t       omh_freeobjp;
    
}objmgrhead_t;



typedef struct s_OBJALST
{
    list_h_t oal_list;
    list_h_t oal_emplist;
    olcfgdat_t* oal_cfgmsz;
    uint_t   oal_emplstnr;
    uint_t   oal_lstnr;
    objmgrhead_t* oal_omhcahe;
}objalst_t;

typedef struct s_OBJMPLCTRL
{
    spinlock_t  omc_lock;
    objalst_t*  omc_alstcahe;
    
    objalst_t   omc_alclst[OBJALST_MAX];
}objmplctrl_t;

#endif // KRLOBJSMPOL_T_H
