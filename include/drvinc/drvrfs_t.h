#ifndef DRVRFS_T_H
#define DRVRFS_T_H
#define DR_NM_MAX (128-(sizeof(uint_t)*3))
#define FBLKS_MAX 32
#define RDR_NUL_TYPE 0
#define RDR_DIR_TYPE 1
#define RDR_FIL_TYPE 2
#define RDR_DEL_TYPE 5

#define FMD_NUL_TYPE 0
#define FMD_DIR_TYPE 1
#define FMD_FIL_TYPE 2
#define FMD_DEL_TYPE 5
#define FSMM_BLK 0x400000
#define FSYS_ALCBLKSZ 0x1000

typedef struct s_RFSDEVEXT
{
    spinlock_t rde_lock;
    list_h_t rde_list;
    uint_t rde_flg;
    uint_t rde_stus;
    void* rde_mstart;
    size_t rde_msize;
    void* rde_ext;
}rfsdevext_t;


typedef struct s_RFSDIR
{
    uint_t rdr_stus;
    uint_t rdr_type;
    uint_t rdr_blknr;
    char_t rdr_name[DR_NM_MAX];
}rfsdir_t;

typedef struct s_FILBLKS
{
    uint_t fb_blkstart;
    uint_t fb_blknr;
}filblks_t;

typedef struct s_RFSSUBLK
{
    spinlock_t rsb_lock;
    uint_t rsb_mgic;
    uint_t rsb_vec;
    uint_t rsb_flg;
    uint_t rsb_stus;
    size_t rsb_sz;
    size_t rsb_sblksz;
    size_t rsb_dblksz;
    uint_t rsb_bmpbks;
    uint_t rsb_bmpbknr;
    uint_t rsb_fsysallblk;
    rfsdir_t rsb_rootdir;

}rfssublk_t;



typedef struct s_fimgrhd
{
    uint_t fmd_stus;
    uint_t fmd_type;
    uint_t fmd_flg;
    uint_t fmd_sfblk;
    uint_t fmd_acss;
    uint_t fmd_newtime;
    uint_t fmd_acstime;
    uint_t fmd_fileallbk;
    uint_t fmd_filesz;
    uint_t fmd_fileifstbkoff;
    uint_t fmd_fileiendbkoff;
    uint_t fmd_curfwritebk;
    uint_t fmd_curfinwbkoff;
    filblks_t fmd_fleblk[FBLKS_MAX];
    uint_t fmd_linkpblk;
    uint_t fmd_linknblk;
}fimgrhd_t;


#endif
