/*
 * CList.h
 *
 *  Created on: 2015年7月9日
 *      Author: Administrator
 */
#include <stdlib.h>
#ifndef CLIST_H_
#define CLIST_H_
//循环链表

//节点
typedef struct CListElmt_
{
	void *data;
	struct CListElmt_ *next;
}CListElmt;
//链表
typedef struct CList_
{
	int size;
	CListElmt *head;
	void (*destroy)(void *data);
}CList;


void clist_init(CList *list,void (*destroy)(void *data));
void clist_destroy(CList *list);
int  clist_ins_next(CList *list,CListElmt *element,void *data);
int  clist_rem_next(CList *list,CListElmt *element,void **data);

#define clist_size(list)    ((list)->size)
#define clist_head(list)    ((list)->head)
#define clist_data(element) ((element)->data)
#define clist_next(element) ((element)->next)

#endif /* CLIST_H_ */
