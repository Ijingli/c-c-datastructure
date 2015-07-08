/*
 * dlist.c
 *
 *  Created on: 2015年7月8日
 *      Author: Administrator
 */

#include "dlist.h"
#include <stdlib.h>
#include <string.h>

//初始化函数
void dlist_init(DList *list,void (*destroy) (void *data))
{
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->destroy = destroy;
}
//删除所有节点，利用init函数的destroy函数来清理内存
void dlist_destroy(DList* list)
{
	void *data;
	while((dlist_size(list))>0){
		if(dlist_remove(list,dlist_tail(list),(void **)&data)==0
				&& list->destroy != NULL){
			list->destroy(data);
		}
	}
}
//成功返回1  失败返回-1

int  dlist_ins_next(DList *list,DListElmt *element,const void *data)
{
	DListElmt *new_element;
	//element不能是空除非list是空
	if(element==NULL && dlist_size(list)==0)
		return -1;
	if((new_element=(DListElmt*)malloc(sizeof(DListElmt))) == NULL)
		return -1;
	new_element->data = (void *)data;
    if(dlist_size(list)==0){
    	list->head = new_element;
    	list->head->prev = NULL;
    	list->head->next = NULL;
    	list->tail = new_element;
    }else{
    	new_element->next = element->next;
    	new_element->prev = element;
    	if(element->next!=NULL)
    		element->next->prev = new_element;
    	else
    		list->tail = new_element;
    	element->next = new_element;
    }

	list->size++;
	return 1;
}
int  dlist_ins_prev(DList *list,DListElmt *element,const void *data)
{
	DListElmt *new_element;
	//不允许在NULL前面插入元素，除非列表为空
	if(element == NULL && dlist_size(list)==0)
		return -1;
	if((new_element = (DListElmt*)malloc(sizeof(DListElmt))) == NULL)
		return -1;
	new_element->data = data;
	if(dlist_size(list) == 0){
		list->head = new_element;
		new_element->prev = NULL;
		new_element->next = NULL;
		list->tail = new_element;
	}else{
		new_element->next = element;
		new_element->prev = element->prev;
		if(element->prev!=NULL)
			element->prev->next = new_element;
		else
			list->head = new_element;
		element->prev = new_element;
		list->size++;
		return 1;
	}



}
//删除element所指定的节点，该节点的数据域存放到data中
int  dlist_remove(DList *list,DListElmt *element,void **data)
{
	if(element==NULL || dlist_size(list)==0)
		return -1;
	*data = element->data;
	if(element== list->head){
		list->head = element->next;
		if(list->head == NULL)
			list->tail = NULL;
		else
			element->next->prev = NULL;
	}else{
		element->prev->next = element->next;
		if(element->next == NULL)
			list->tail = element->prev;
		else
			element->next->prev= element->prev;
	}
	free(element);
	list->size--;
	return 1;
}
