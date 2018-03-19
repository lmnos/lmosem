/**********************************************************
    数据结构 - 红黑树
***********************************************************
     颜文泽 @ 2018.3.19.21.00
**********************************************************/

/*
 * traditional
 * ================================================
 * Color = Red | Black
 * rbtree a = {
 *          Color
 *          rbtree a
 *          a
 *          rbtree a
 *       } | LEAF
 * }
 */
#ifndef _RBTREE_T_H
#define _RBTREE_T_H

#include    "miscellaneous.h"

#define rbtree_leaf     (NULL)
#define rbtree_empty    (NULL)
#define rbtree_BBempty  ((void *)1)
#define rbtree_node_empty    (NULL)

#define rbtree_isempty(t)   (!(t))
#define rbtree_isbbempty(t) ((t) == (void *)1)
#define rbtree_node_isempty(b)    (!(b))

#define rbtree_left_branch(t)   ((t)->left)
#define rbtree_right_branch(t)  ((t)->right)

typedef struct rbtree rbtree_t;
typedef struct Rbtree Rbtree_t;
typedef struct rbtree Rbtree_node_t;
typedef struct rbtree rbtree_node_t;

typedef int (*Rbtree_f)(rbtree_t *, rbtree_t *);
typedef int (*rbtree_node_cmp_f)(rbtree_node_t *, void *);

typedef enum{
    R,
    B,
    BB
}Color;

struct rbtree{
    Color   color;
    rbtree_t    *left;
    rbtree_t    *right;
};

struct Rbtree{
    rbtree_t    *tree;
    rbtree_node_cmp_f   cmp;
};

static inline rbtree_t  *
rbtree_T(Color color, rbtree_t *left, rbtree_node_t *node, rbtree_t *right)
{
    node->color = color;
    node->left = left;
    node->right = right;
    return node;
}

int    Rbtree_delete(Rbtree_t *t);
Rbtree_t    *Rbtree_new(rbtree_node_cmp_f cmp);

int Rbtree_insert(Rbtree_t *t, Rbtree_node_t *node);
Rbtree_node_t   *Rbtree_elem(Rbtree_t *t, Rbtree_node_t *elem);
Rbtree_node_t   *Rbtree_remove(Rbtree_t *t, Rbtree_node_t *node);
void    *Rbtree_fold(Rbtree_t *t, void *init, Rbtree_f f);
void    *Rbtree_foldl(Rbtree_t *t, void *init, Rbtree_f f);
void    *Rbtree_foldr(Rbtree_t *t, void *init, Rbtree_f f);

#endif
