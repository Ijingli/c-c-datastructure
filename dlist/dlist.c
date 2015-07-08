/*
 * dlist.c
 *
 *  Created on: 2015��7��8��
 *      Author: Administrator
 */

#include "dlist.h"
#include <stdlib.h>
#include <string.h>

//��ʼ������
void dlist_init(DList *list,void (*destroy) (void *data))
{
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->destroy = destroy;
}
//ɾ�����нڵ㣬����init������destroy�����������ڴ�
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
//�ɹ�����1  ʧ�ܷ���-1

int  dlist_ins_next(DList *list,DListElmt *element,const void *data)
{
	DListElmt *new_element;
	//element�����ǿճ���list�ǿ�
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
	//��������NULLǰ�����Ԫ�أ������б�Ϊ��
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
//ɾ��element��ָ���Ľڵ㣬�ýڵ���������ŵ�data��
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
