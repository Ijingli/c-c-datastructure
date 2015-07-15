/*
 * list.h
 *
 *  Created on: 2015��7��14��
 *      Author: Administrator
 */

#ifndef LIST_H_
#define LIST_H_

#include<stdlib.h>
typedef struct ListElmt_
{
	void *data;
	struct ListElmt_ *next;
}ListElmt;

typedef struct List_
{
	int size;
	ListElmt *head;
	ListElmt *tail;
	void (*destroy)(void *data);
	int (*match)(const void *key1,const void *key2);
}List;

void list_init(List *list,void (*destroy)(void *data));
void list_destroy(List *list);
int  list_ins_next(List *list,ListElmt *element,const void *data);
int  list_rem_next(List *list,ListElmt *element,void **data);

#define list_size(list) ((list)->size)
#define list_head(list)  ((list)->head)
#define list_tail(list)  ((list)->tail)
#define list_is_head(list,element)  ((element)==list->head?1:0)
#define list_is_tail(list,element)  ((element)==list->tail?1:0)
#define list_data(element)  ((element)->data)
#define list_next(element)  ((element)->next)

#endif /* LIST_H_ */