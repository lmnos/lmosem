/**********************************************************
    数据结构 - 列表
***********************************************************
     颜文泽 @ 2018.3.19.21.00
**********************************************************/


/*
 * strict
 * ================================================
 * List a = List{
 *        prev :: List a,
 *        next :: List a
 *        } | EmptyList
 */
#ifndef _LIST_T_H
#define _LIST_T_H

#include    "miscellaneous.h"

#define list_empty      (NULL)
#define list_node_empty (NULL)
#define list_isempty(list)      (!(list))
#define list_node_isempty(node) (!(node))
#define list_eq(list1, list2)   ((list1) == (list2))
#define list_next(list)         ((list)->next)
#define list_prev(list)         ((list)->prev)

typedef struct list list_t;
typedef struct list list_node_t;
typedef list_t      *(*list_f)(list_t *, list_t *);
typedef list_node_t *(*node_f)(void *usr_data, list_node_t *);

struct list{
    list_t    *prev;
    list_t    *next;
};

int     list_length(list_t *list);

list_t  *list_new(list_node_t *node);
list_t  *list_link(list_t *prev, list_node_t *node, list_t *next);

/*
 * act on whole list
 */
list_node_t     *list_head(list_t *list);
list_node_t     *list_last(list_t *list);
list_node_t     *list_elem(list_t *list, void *data, node_f f);

list_t  *list_tail(list_t *list);
list_t  *list_separate(list_node_t *node);
list_t  *list_push_back(list_node_t *node, list_t *list);
list_t  *list_push_front(list_node_t *node, list_t *list);

/*
 * act on list
 */
list_t  *list_foldl(list_t *list, list_t *init_list, list_f f);
list_t  *list_foldr(list_t *list, list_t *init_list, list_f f);

#endif
