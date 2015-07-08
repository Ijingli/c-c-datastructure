/*
 * dlist.h
 *
 *  Created on: 2015年7月8日
 *      Author: Administrator
 */

#ifndef DLIST_H_
#define DLIST_H_

//双向链表节点
typedef struct DListElmt_
{
	void *data;//数据域
	struct DListElmt_ *prev;//前驱指针
	struct DListElmt_ *next;//后继指针
}DListElmt;


typedef struct DList_
{
	int size;//链表大小
	DListElmt *head;//头
	DListElmt *tail;//尾
	//自定义函数
	void (*destroy) (void *data);
}DList;


//初始化函数
void dlist_init(DList *list,void (*destroy) (void *data));
//删除所有节点，利用init函数的destroy函数来清理内存
void dlist_destroy(DList* list);
//成功返回1  失败返回-1
int  dlist_ins_next(DList *list,DListElmt *element,const void *data);
int  dlist_ins_prev(DList *list,DListElmt *element,const void *data);
//删除element所指定的节点，该节点的数据域存放到data中
int  dlist_remove(DList *list,DListElmt *element,void **data);

#define dlist_size(list) ((list)->size)
#define dlist_head(list)  ((list)->head)
#define dlist_tail(list)  ((list)->tail)
#define dlist_is_head(element)  ((element)->prev==NULL?1:0)
#define dlist_is_tail(element)   ((element)->next==NULL?1:0)
#define dlist_data(element)  ((element)->data)
#define dlist_next(element)   ((element)->next)
#define dlist_prev(element)   ((element)->prev)



#endif /* DLIST_H_ */
