/**********************************************************
    数据结构 - 红黑树
***********************************************************
     颜文泽 @ 2018.3.13.21.00
**********************************************************/

#include    "rbtree.h"

static rbtree_t *rbtree_makeblack(rbtree_t *t);
static rbtree_t *rbtree_makeblack1(rbtree_t *t);

static rbtree_node_t    *rbtree_min(rbtree_t *t);

static void *rbtree_fold(rbtree_t *t, void *init, Rbtree_f f);
static void *rbtree_foldl(rbtree_t *t, void *init, Rbtree_f f);
static void *rbtree_foldr(rbtree_t *t, void *init, Rbtree_f f);

static rbtree_t *rbtree_fixdb(Color color, rbtree_t *l, rbtree_node_t *a, rbtree_t *r);
static rbtree_t *rbtree_balance(Color color, rbtree_t *l, rbtree_node_t *a, rbtree_t *r);

static rbtree_t *rbtree_elem(rbtree_t *t, rbtree_t *elem, rbtree_node_cmp_f cmp);
static rbtree_t *rbtree_ins(rbtree_node_t *a, rbtree_t *t, rbtree_node_cmp_f cmp);
static rbtree_t *rbtree_insert(rbtree_node_t *a, rbtree_t *t, rbtree_node_cmp_f cmp);
static rbtree_t *rbtree_del(rbtree_node_t *a, rbtree_t *t, rbtree_node_cmp_f cmp, rbtree_node_t **rp);
static rbtree_t *rbtree_delete(rbtree_node_t *a, rbtree_t *t, rbtree_node_cmp_f cmp, rbtree_node_t **rp);

Rbtree_t    *
Rbtree_new(rbtree_node_cmp_f cmp)
{
    Rbtree_t *t;

    if(!cmp || !(t = (Rbtree_t *)krlnew(sizeof(*t))))
        return NULL;
    t->cmp = cmp;
    t->tree = rbtree_empty;
    return t;
}

int
Rbtree_delete(Rbtree_t *t)
{
    krldelete(t, sizeof(*t));
    return 0;
}

Rbtree_node_t   *
Rbtree_remove(Rbtree_t *t, Rbtree_node_t *node)
{
    Rbtree_node_t   *r;

    r = NULL;
    t->tree = rbtree_delete(node, t->tree, t->cmp, &r);
    return r;
}

int
Rbtree_insert(Rbtree_t *t, Rbtree_node_t *node)
{
    t->tree = rbtree_insert(node, t->tree, t->cmp);
    return 0;
}

Rbtree_node_t    *
Rbtree_elem(Rbtree_t *t, Rbtree_node_t *elem)
{
    return rbtree_elem(t->tree, elem, t->cmp);
}

void    *
Rbtree_fold(Rbtree_t *t, void *init, Rbtree_f f)
{
    return rbtree_fold(t->tree, init, f);
}

void    *
Rbtree_foldl(Rbtree_t *t, void *init, Rbtree_f f)
{
    return rbtree_foldl(t->tree, init, f);
}

void    *
Rbtree_foldr(Rbtree_t *t, void *init, Rbtree_f f)
{
    return rbtree_foldr(t->tree, init, f);
}

static rbtree_node_t    *
rbtree_min(rbtree_t *t)
{
    if(rbtree_isempty(t) || rbtree_isempty(t->left))
        return t;
    return rbtree_min(t->left);
}

static rbtree_node_t    *
rbtree_elem(rbtree_t *t, rbtree_node_t *elem, rbtree_node_cmp_f cmp)
{
    if(!rbtree_isempty(t)){
        int r = cmp(elem, t);
        if(r == 0)
            return t;
        if(r < 0)
            return rbtree_elem(rbtree_left_branch(t), elem, cmp);
        if(r > 0)
            return rbtree_elem(rbtree_right_branch(t), elem, cmp);
    }
    return NULL;
}

static void *
rbtree_fold(rbtree_t *t, void *init, Rbtree_f f)
{
    if(!rbtree_isempty(t)){
        rbtree_t    *l, *r;
        l = rbtree_left_branch(t);
        r = rbtree_right_branch(t);
        f(t, init);
        rbtree_fold(l, init, f);
        rbtree_fold(r, init, f);
    }
    return init;
}

static void *
rbtree_foldl(rbtree_t *t, void *init, Rbtree_f f)
{
    if(!rbtree_isempty(t)){
        rbtree_t    *l, *r;
        l = rbtree_left_branch(t);
        r = rbtree_right_branch(t);
        rbtree_foldl(l, init, f);
        f(t, init);
        rbtree_foldl(r, init, f);
    }
    return init;
}

static void *
rbtree_foldr(rbtree_t *t, void *init, Rbtree_f f)
{
    if(!rbtree_isempty(t)){
        rbtree_t    *l, *r;
        l = rbtree_left_branch(t);
        r = rbtree_right_branch(t);
        rbtree_foldr(r, init, f);
        f(t, init);
        rbtree_foldr(l, init, f);
    }
    return init;
}

static rbtree_t *
rbtree_makeblack(rbtree_t *t)
{
    if(rbtree_isempty(t) || rbtree_isbbempty(t))
        return NULL;
    t->color = B;
    return t;
}

static rbtree_t *
rbtree_makeblack1(rbtree_t *t)
{
    if(rbtree_isempty(t))
        return rbtree_BBempty;
    t->color = (t->color == B) ? BB : B;
    return t;
}

static rbtree_t    *
rbtree_insert(rbtree_node_t *a, rbtree_t *t, rbtree_node_cmp_f cmp)
{
    return rbtree_makeblack(rbtree_ins(a, t, cmp));
}

static rbtree_t *
rbtree_ins(rbtree_node_t *a, rbtree_t *t, rbtree_node_cmp_f cmp)
{
    int r;

    if(rbtree_isempty(t))
        return rbtree_T(R, rbtree_empty, a, rbtree_empty);
    r = cmp(a, t);
    if(r < 0)
        return rbtree_balance(t->color, rbtree_ins(a, t->left, cmp), t, t->right);
    if(r > 0)
        return rbtree_balance(t->color, t->left, t, rbtree_ins(a, t->right, cmp));
    return t;
}

static rbtree_t *
rbtree_balance(Color color, rbtree_t *l, rbtree_node_t *a, rbtree_t *r)
{
    rbtree_t    *t;

    if(color == B){
        if(l && l->color == R && (t = l->left) && t->color == R)
            return rbtree_T(R, rbtree_makeblack(l->left), l, rbtree_T(B, l->right, a, r));
        if(l && l->color == R && (t = l->right) && t->color == R)
            return rbtree_T(R, rbtree_T(B, l->left, l, t->left), t, rbtree_T(B, t->right, a, r));
        if(r && r->color == R && (t = r->right) && t->color == R)
            return rbtree_T(R, rbtree_T(B, l, a, r->left), r, rbtree_makeblack(r->right));
        if(r && r->color == R && (t = r->left) && t->color == R)
            return rbtree_T(R, rbtree_T(B, l, a, t->left), t, rbtree_T(B, t->right, r, r->right));
    }
    return rbtree_T(color, l, a, r);
}

static rbtree_t    *
rbtree_delete(rbtree_node_t *a, rbtree_t *t, rbtree_node_cmp_f cmp, rbtree_node_t **rp)
{
    return rbtree_makeblack(rbtree_del(a, t, cmp, rp));
}

static rbtree_t    *
rbtree_del(rbtree_node_t *a, rbtree_t *t, rbtree_node_cmp_f cmp, rbtree_node_t **rp)
{
    int r;
    rbtree_node_t   *min;

    if(rbtree_isempty(t))
        return t;
    r = cmp(a, t);
    if(r < 0)
        return rbtree_fixdb(t->color, rbtree_del(a, t->left, cmp, rp), t, t->right);
    if(r > 0)
        return rbtree_fixdb(t->color, t->left, t, rbtree_del(a, t->right, cmp, rp));
    if(rp)
        *rp = t;
    if(rbtree_isempty(t->left))
        return t->color == B ? rbtree_makeblack1(t->right) : t->right;
    if(rbtree_isempty(t->right))
        return t->color == B ? rbtree_makeblack1(t->left) : t->left;
    min = rbtree_min(t->right);
    return rbtree_fixdb(t->color, t->left, min, rbtree_del(min, t->right, cmp, NULL));
}

static rbtree_t *
rbtree_fixdb(Color color, rbtree_t *l, rbtree_node_t *a, rbtree_t *r)
{
    rbtree_t    *t, *t1;

    if(rbtree_isbbempty(l) && rbtree_isempty(r))
        return rbtree_T(BB, rbtree_empty, a, rbtree_empty);
    if(rbtree_isempty(l) && rbtree_isbbempty(r))
        return rbtree_T(BB, rbtree_empty, a, rbtree_empty);
    if(rbtree_isbbempty(l))
        return rbtree_T(color, rbtree_empty, a, r);
    if(rbtree_isbbempty(r))
        return rbtree_T(color, l, a, rbtree_empty);
    if(l && l->color == BB && r && r->color == B && (t = r->left) && t->color == R)
        return rbtree_T(color, rbtree_T(B, rbtree_makeblack1(l), a, t->left), t, rbtree_T(B, t->right, r, r->right));
    if(l && l->color == BB && r && r->color == B && (t = r->right) && t->color == R)
        return rbtree_T(color, rbtree_T(B, rbtree_makeblack1(l), a, r->left), r, rbtree_T(B, t->left, t, t->right));
    if(r && r->color == BB && l && l->color == B && (t = l->right) && t->color == R)
        return rbtree_T(color, rbtree_T(B, l->left, l, t->left), t, rbtree_T(B, t->right, a, rbtree_makeblack1(r)));
    if(r && r->color == BB && l && l->color == B && (t = l->left) && t->color == R)
        return rbtree_T(color, rbtree_T(B, t->left, t, t->right), l, rbtree_T(B, l->right, a, rbtree_makeblack1(r)));
    if(l && l->color == BB && r && r->color == B && (t = r->left) && t->color == B && (t1 = r->right) && t1->color == B)
        return rbtree_makeblack1(rbtree_T(color, rbtree_makeblack1(l), a, rbtree_T(R, t, r, t1)));
    if(r && r->color == BB && l && l->color == B && (t = l->left) && t->color == B && (t1 = l->right) && t1->color == B)
        return rbtree_makeblack1(rbtree_T(color, rbtree_T(R, t, l, t1), a, rbtree_makeblack1(r)));
    if(color == B && l && l->color == BB && r && r->color == R)
        return rbtree_fixdb(B, rbtree_fixdb(R, l, a, r->left), r, r->right);
    if(color == B && r && r->color == BB && l && l->color == R)
        return rbtree_fixdb(B, l->left, l, rbtree_fixdb(R, l->right, a, r));
    return rbtree_T(color, l, a, r);
}
