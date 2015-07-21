/*
 * list.c
 *
 *  Created on: 2015Äê7ÔÂ14ÈÕ
 *      Author: Administrator
 */

#include<stdlib.h>
#include<string.h>
#include "list.h"



void list_init(List *list,void (*destroy)(void *data))
{
	list->head=NULL;
	list->tail=NULL;
	list->size=0;
	list->destroy = destroy;
}
void list_destroy(List *list)
{
	void *data;
	while(list_size(list)>0){
		if((list_rem_next(list,NULL,(void**)&data)==0) &&
				list->destroy!=NULL){
			list->destroy(data);
		}
	}
}


int  list_ins_next(List *list,ListElmt *element,const void *data)
{
   ListElmt *newElement;
   if((newElement = (ListElmt*)malloc(sizeof(ListElmt)))==NULL)
	   return -1;
   newElement->data = data;
   if(element==NULL){
	   if(list_size(list)==0){
		   list->tail  = newElement;
	   }
	   newElement->next = list->head;
	   list->head = newElement;
   }else{
	   if(element->next == NULL)
		   list->tail = newElement;
	   newElement->next = element->next;
	   element->next = newElement;
   }
   list->size++;
   return 0;
}


int  list_rem_next(List *list,ListElmt *element,void **data)
{
	ListElmt *oldElement;
	if(list_size(list) == 0){
		printf("list_size = %d,Error\n",list_size(list));
	    return -1;
	}
	if(list_is_tail(list,element)){
		printf("Err element == list->tail,can not remove next\n");
		return -1;
	}
	if(element == NULL){
		*data = list->head->data;
		oldElement = list->head;
		list->head = list->head->next;
		if(list_size(list)==1)
			list->tail = NULL;
	}else{
		if(element->next == NULL)
			return -1;
		*data = element->next->data;
		oldElement = element->next;
		element->next = element->next->next;
		if(element->next==NULL)
			list->tail = element;

	}
    free(oldElement);
	list->size--;
	return 0;
}
