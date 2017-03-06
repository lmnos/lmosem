/**********************************************************
		链表头文件list.h
***********************************************************
				彭东 ＠ 2011.12.13.14.30
**********************************************************/
#ifndef _LIST_T_H
#define _LIST_T_H

typedef struct s_LIST_H {
       struct s_LIST_H *prev,*next;
}list_h_t;

typedef struct s_TREE
{
	u16_t tr_type;
	u16_t tr_color;
	//spinlock_t tr_lock;
	u64_t tr_hight;
	struct s_TREE* tr_left;
	struct s_TREE* tr_right;
	struct s_TREE* tr_paret;
	struct s_TREE* tr_subs;
}tree_t;

#endif
