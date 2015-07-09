/*
 * main.c
 *
 *  Created on: 2015��7��9��
 *      Author: Administrator
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "clist.h"

typedef struct Stu_
{
	int age;
	char *name;
}Stu;

void destroy(void *data){
	Stu *stu = (Stu*)(data);
	free(data);
	printf("free after:%d,%s\n",stu->age,stu->name);
}



Stu* createStu(int age,char* name){
	Stu *stu = (Stu*)malloc(sizeof(Stu));
    stu->age = age;
    stu->name = name;
    return stu;
}


int main()
{
    CList *list = (CList*)malloc(sizeof(CList));
	clist_init(list,destroy);
	Stu *stu = (Stu*)malloc(sizeof(Stu));
	stu->age = 11;
	stu->name ="HeXinyuan";
	clist_ins_next(list,NULL,(void *)stu);
	Stu *stu2 = (Stu*)malloc(sizeof(Stu));
	stu2->age = 22;
	stu2->name ="ZhangJingli";
    clist_ins_next(list,clist_head(list),(void *)stu2);
    Stu *newStu = createStu(33,"HeXiaoxiao");
    clist_ins_next(list,clist_head(list),(void *)newStu);
    printf("clist_size()= %d\n",clist_size(list));
    Stu *result = (Stu*)(clist_head(list)->data);
    CListElmt *head = clist_head(list);
    while(head!=NULL){
    	Stu* res = (Stu*)(head->data);
    	printf("res->age = %d,res->name=%s\n",res->age,res->name);
    	head = head->next;
    	if(clist_head(list) == head){
    		break;
    	}
    }
    void *dataStu;
    clist_rem_next(list,clist_head(list),&dataStu);
    printf("%d,%s\n",((Stu*)(dataStu))->age,((Stu*)(dataStu))->name);
    clist_destroy(list);
	return 0;
}

