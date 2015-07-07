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
            //调用一个用户自定义的方法去释放内存
            list->destroy(data);
        }
    }
    memset(list,0,sizeof(List));
    return;
}

//插入，在element后插入
int list_ins_next(List *list,ListElmt *element,const void *data){
    ListElmt *newElement;
    //为新元素分配内存
    if((newElement=(ListElmt*)malloc(sizeof(ListElmt)))==NULL){
        return -1;
    }
    newElement->data = (void *)data;
    if(element == NULL){
    //表头
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
    if(element==NULL){//element是head前的元素，也就是移除head
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


















