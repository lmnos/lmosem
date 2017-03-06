/**********************************************************
        LMOSEM内核对象节点头文件krlobjnode.h
***********************************************************
                彭东 ＠ 2013.09.19.16.50
**********************************************************/
#ifndef _KRLOBJNODE_H
#define _KRLOBJNODE_H
void objnode_t_init(objnode_t* initp);
objnode_t* krlnew_objnode();
bool_t krldel_objnode(objnode_t* onodep);
#endif // KRLOBJNODE_H
