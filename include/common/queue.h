/**********************************************************
    数据结构 - 队列
***********************************************************
     颜文泽 @ 2018.3.19.21.00
**********************************************************/

/*
 * traditional
 * ================================================
 * queue = {
 *    List a;
 * }
 */
#ifndef _QUEUE_T_H
#define _QUEUE_T_H

#include    "list.h"

#define queue_list(xxxx)   ((xxxx)->list)
#define queue_node_list_empty   list_empty
#define queue_node_list_isempty list_isempty

typedef list_f queue_f;
typedef node_f queue_node_f;
typedef list_t queue_node_t;
typedef struct queue queue_t;
struct queue{
    list_t    *list;
};

queue_t    *queue_new(void);
int    queue_delete(queue_t *queue);

int queue_length(queue_t *queue);

queue_node_t    *queue_head(queue_t *queue);

queue_node_t    *queue_pop(queue_t *queue);
queue_node_t    *queue_elem(queue_t *queue, void *usr_data, queue_node_f f);

int    queue_remove(queue_t *queue, queue_node_t *node);
int    queue_push_back(queue_t *queue, queue_node_t *node);
int    queue_push_front(queue_t *queue, queue_node_t *node);

queue_node_t    *queue_foldl(queue_t *queue, queue_node_t *init_list, queue_f f);
queue_node_t    *queue_foldr(queue_t *queue, queue_node_t *init_list, queue_f f);

#endif
