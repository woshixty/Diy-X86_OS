#ifndef LIST_H
#define LIST_H

#include "comm/types.h"

typedef struct _list_node_t
{
    struct _list_node_t* pre;
    struct _list_node_t* next;
} list_node_t;

static inline void list_node_init(list_node_t* node) {
    node->pre = node->next = (list_node_t*)0;
}

static inline list_node_t* list_node_pre(list_node_t* node) {
    return node->pre;
}

static inline list_node_t* list_node_next(list_node_t* node) {
    return node->next;
}

typedef struct _list_t
{
    list_node_t* first;
    list_node_t* last;

    int count;
} list_t;

void list_init(list_t* list);

static inline int list_is_empty(list_t* list) {
    return list->count == 0;
}

static inline int list_count(list_t* list) {
    return list->count;
}

static inline list_node_t* list_first(list_t* list) {
    return list->first;
}

static inline list_node_t* list_last(list_t* list) {
    return list->last;
}

void list_insert_first(list_t* list, list_node_t* node);
void list_insert_last(list_t* list, list_node_t* node);

list_node_t* list_remove_first(list_t* list);
list_node_t* list_remove(list_t* list, list_node_t* node);

// 1.求结点在所在结构中的偏移:定义一个指向0的指针，用(struct aa *)&0->node，所得即为node字段在整个结构体的偏移
#define offset_in_parent(parent_type, node_name)    \
    ((uint32_t)&(((parent_type*)0)->node_name))

// 2.求node所在的结构体首址：node的地址 - node的偏移
// 即已知a->node的地址，求a的地址
#define offset_to_parent(node, parent_type, node_name)   \
    ((uint32_t)node - offset_in_parent(parent_type, node_name))

// 3. 进行转换: (struct aa *)addr
// list_node_parent(node_addr, struct aa, node_name)
#define list_node_parent(node, parent_type, node_name)   \
    ((parent_type *)(node ? offset_to_parent((node), parent_type, node_name) : 0))

#endif