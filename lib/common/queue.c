/**********************************************************
    数据结构 - 队列
***********************************************************
     颜文泽 @ 2018.3.13.21.00
**********************************************************/

#include    "queue.h"

queue_t *
queue_new(void)
{
    queue_t    *queue;

    if(!(queue = (queue_t *)krlnew(sizeof(*queue))))
        goto err;
    queue_list(queue) = queue_node_list_empty;
    return queue;
err:
    return NULL;
}

int
queue_delete(queue_t *queue)
{
    krldelete(queue, sizeof(*queue));
    return 0;
}

int
queue_push_back(queue_t *queue, queue_node_t *node)
{
    if(list_node_isempty(node))
        return -1;
    queue_list(queue) = list_push_back(node, queue_list(queue));
    return 0;
}

int
queue_push_front(queue_t *queue, queue_node_t *node)
{
    if(list_node_isempty(node))
        return -1;
    queue_list(queue) = list_push_front(node, queue_list(queue));
    return 0;
}

int
queue_remove(queue_t *queue, queue_node_t *node)
{
    if(list_node_isempty(node))
        return -1;
    queue_list(queue) = list_separate(node);
    return 0;
}

int
queue_length(queue_t *queue)
{
    return list_length(queue_list(queue));
}

queue_node_t    *
queue_pop(queue_t *queue)
{
    queue_node_t    *n;

    n = queue_list(queue);
    if((queue_list(queue) = list_tail(queue_list(queue))) != NULL)
        list_prev(queue_list(queue)) = queue_node_list_empty;
    return n;
}

queue_node_t    *
queue_head(queue_t *queue)
{
    return list_head(queue_list(queue));
}

queue_node_t    *
queue_elem(queue_t *queue, void *data, queue_node_f f)
{
    return list_elem(queue_list(queue), data, f);
}

queue_node_t    *
queue_foldl(queue_t *queue, queue_node_t *init_list, queue_f f)
{
    return list_foldl(queue_list(queue), init_list, f);
}

queue_node_t    *
queue_foldr(queue_t *queue, queue_node_t *init_list, queue_f f)
{
    return list_foldr(queue_list(queue), init_list, f);
}
