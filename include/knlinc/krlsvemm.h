#ifndef _KRLSVEMM_H
#define _KRLSVEMM_H
sysstus_t krlsvetabl_mallocblk(uint_t swinr,stkparame_t* stkparv);
sysstus_t krlsvetabl_mfreeblk(uint_t swinr,stkparame_t* stkparv);
void* krlsve_mallocblk(size_t blksz);
sysstus_t krlsve_mfreeblk(void* fradr,size_t blksz);
void* krlsve_core_mallocblk(size_t blksz);
sysstus_t krlsve_core_mfreeblk(void* fradr,size_t blksz);
#endif // KRLSVEMM_H
