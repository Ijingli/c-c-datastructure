#ifndef LIST_H
#define LIST_H
#pragma once
#include <stdlib.h>
//节点定义
typedef struct ListElmt_
{
   void *data;//数据域
   struct ListElmt_ *next;//指针域，指向下一个节点
}ListElmt;
//链表定义
typedef struct List_
{
    int size;//链表大小
    int (*match)(const void *key1,const void *key2);
    int (*destroy)(void *data);
    ListElmt *head;//表头
    ListElmt *tail;//表尾
}List;

//public interface
void list_init(List *list,void(*destroy)(void *data));
void list_destroy(List *list);
int  list_ins_next(List *list,ListElmt *element,const void *data);
int  list_rem_next(List *list,ListElmt *element,void **data);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list)  ((list)->tail)
#define list_is_head(list,element) ((element)==(list)->head?1:0)
#define list_is_tail(list,element) ((element)==(list)->tail?1:0)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)

#endif // LIST_H
