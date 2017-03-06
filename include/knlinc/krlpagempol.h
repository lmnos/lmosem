/**********************************************************
        内核层内存页面池管理头文件krlpagempol.h
***********************************************************
                彭东 ＠ 2013.07.18.15.00
**********************************************************/
#ifndef _KRLPAGEMPOL_H
#define _KRLPAGEMPOL_H

void init_krlpagempol();
void kmempool_t_init(kmempool_t* initp);
adr_t kmempool_page_new_callhalmm(size_t msize);
bool_t kmempool_page_delete_callhalmm(adr_t fradr,size_t frze);
void mplhead_t_init(mplhead_t* initp);
bool_t objs_delete_on_mplhead(mplhead_t* mplhdp,adr_t fradr);
adr_t objs_new_on_mplhead(mplhead_t* mplhdp);
bool_t page_delete_on_mplhead(mplhead_t* mplhdp,adr_t fradr);
adr_t page_new_on_mplhead(mplhead_t* mplhdp);
mplhead_t* objs_mpool_init(kmempool_t* kmplockp,mplhead_t* initp,size_t msize,adr_t start,adr_t end);
mplhead_t* page_mpool_init(kmempool_t* kmplockp,mplhead_t* initp,size_t msize,adr_t start,adr_t end);
bool_t del_objs_mpool(kmempool_t* kmplockp,mplhead_t* mphdp);
bool_t del_page_mpool(kmempool_t* kmplockp,mplhead_t* mphdp);
mplhead_t* new_objs_mpool(kmempool_t* kmplockp,size_t msize);
mplhead_t* new_page_mpool(kmempool_t* kmplockp,size_t msize);
mplhead_t* objsdel_mplhead_isok(mplhead_t* mhp,adr_t fradr,size_t msize);
mplhead_t* pagedel_mplhead_isok(mplhead_t* mhp,adr_t fradr,size_t msize);
mplhead_t* objsnew_mplhead_isok(mplhead_t* mhp,size_t msize);
mplhead_t* pagenew_mplhead_isok(mplhead_t* mhp,size_t msize);
mplhead_t* kmemplob_retn_mplhead(kmempool_t* kmplockp,size_t msize);
mplhead_t* kmempldelpg_retn_mplhead(kmempool_t* kmplockp,adr_t fradr,size_t msize);
mplhead_t* kmemplpg_retn_mplhead(kmempool_t* kmplockp,size_t msize);
adr_t kmempool_pages_core_new(size_t msize);
bool_t kmempool_pages_core_delete(adr_t fradr,size_t frsz);
adr_t kmempool_objsz_core_new(size_t msize);
bool_t kmempool_objsz_core_delete(adr_t fradr,size_t frsz);
adr_t kmempool_objsz_new(size_t msize);
bool_t kmempool_objsz_delete(adr_t fradr,size_t frsz);
adr_t kmempool_pages_new(size_t msize);
bool_t kmempool_pages_delete(adr_t fradr,size_t frsz);
adr_t kmempool_onsize_new(size_t msize);
bool_t kmempool_onsize_delete(adr_t fradr,size_t frsz);
adr_t kmempool_new(size_t msize);
bool_t kmempool_delete(adr_t fradr,size_t frsz);
#endif // _KRLPAGEMPOL_H
