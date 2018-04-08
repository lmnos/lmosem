/**********************************************************
    数据结构 - 链表
***********************************************************
     颜文泽 @ 2018.3.13.21.00
**********************************************************/

#include    "list.h"

int
list_length(list_t *list)
{
    return list_isempty(list) ? 0 : 1 + list_length(list_next(list));
}

list_t  *
list_tail(list_t *list)
{
    return list_isempty(list) ? list : list_next(list_head(list));
}

list_t  *
list_push_back(list_node_t *node, list_t *list)
{
    return list_head(list_link(list, node, list_empty));
}

list_t  *
list_push_front(list_node_t *node, list_t *list)
{
    return list_head(list_link(list_empty, node, list));
}

list_node_t *
list_head(list_t *list)
{
    if(list_isempty(list))
        return list;
    if(list_isempty(list_prev(list)))
        return list;
    return list_head(list_prev(list));
}

list_node_t *
list_last(list_t *list)
{
    if(list_isempty(list))
        return list;
    if(list_isempty(list_next(list)))
        return list;
    return list_last(list_next(list));
}

list_node_t *
list_elem(list_t *list, void *data, node_f f)
{
    list_t  *next;
    list_node_t    *node;

    if(list_isempty(list))
        return list;
    next = list_next(list);
    if((node = f(data, list)) != NULL)
        return node;
    return list_elem(next, data, f);
}

list_t *
list_foldl(list_t *list, list_t *init_list, list_f f)
{
    list_t  *next = NULL;

    if(list_isempty(list))
        return init_list;
    next = list_next(list);
    return list_foldl(next, f(init_list, list), f);
}

list_t *
list_foldr(list_t *list, list_t *init_list, list_f f)
{
    list_t  *next = NULL;

    if(list_isempty(list))
        return init_list;
    next = list_next(list);
    return f(list_foldr(next, init_list, f), list);
}

list_t *
list_separate(list_node_t *node)
{
    list_t       *list;

    if(list_isempty(list = list_head(node)))
        return list;
    if(list_eq(list, node))
        list = list_next(list);
    if(!list_isempty(list_prev(node)))
        list_next(list_prev(node)) = list_next(node);
    if(!list_isempty(list_next(node)))
        list_prev(list_next(node)) = list_prev(node);
    list_prev(node) = list_next(node) = NULL;
    return list;
}

list_t *
list_new(list_node_t *node)
{
    list_prev(node) = list_next(node) = NULL;
    return node;
}

list_t  *
list_link(list_t *prev, list_node_t *node, list_t *next)
{
    list_next(node) = next;
    if(!list_isempty(next))
        list_prev(next) = node;
    if(!list_isempty(prev)){
        while(!list_isempty(list_next(prev)))
            prev = list_next(prev);
        list_next(prev) = node;
        list_prev(node) = prev;
    }else{
        list_prev(node) = prev;
    }
    return node;
}
