#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void list_init(List *list,void(*destroy)(void *data)){
     list->size = 0;
     list->destroy = destroy;
     list->head  = NULL;
     list->tail = NULL;
     printf("list init OK\n");
     return;
}

void list_destroy(List *list){
    void *data;
    while(list_size(list)>0){
        if(list_rem_next(list,NULL,(void **)&data)==0 && list->destroy!=NULL){
            //����һ���û��Զ���ķ���ȥ�ͷ��ڴ�
            list->destroy(data);
        }
    }
    memset(list,0,sizeof(List));
    return;
}

//���룬��element�����
int list_ins_next(List *list,ListElmt *element,const void *data){
    ListElmt *newElement;
    //Ϊ��Ԫ�ط����ڴ�
    if((newElement=(ListElmt*)malloc(sizeof(ListElmt)))==NULL){
        return -1;
    }
    newElement->data = (void *)data;
    if(element == NULL){
    //��ͷ
        if(list_size(list)==0)
            list->tail = newElement;
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

int  list_rem_next(List *list,ListElmt *element,void **data){
    ListElmt *oldElement;
    if(list_size(list)==0)
        return -1;
    if(element==NULL){//element��headǰ��Ԫ�أ�Ҳ�����Ƴ�head
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
                list->tail =element;

    }
    free(oldElement);
    list->size--;
    return 0;
}


















