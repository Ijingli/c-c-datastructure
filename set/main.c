/*
 * main.c
 *
 *  Created on: 2015��7��15��
 *      Author: Administrator
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "set.h"
#include "list.h"
typedef struct Stu_{
	int age;
	char *name;
}Stu;

int match (const void *key1,const void *key2){
	if( key1== NULL || key2 == NULL){
		return 0;
	}
	Stu *stu1 = (Stu*)key1;
	Stu *stu2 = (Stu*)key2;
	if((stu1->age == stu2->age) && strcmp(stu1->name,stu2->name)==0){
		return 1;
	}
	return 0;
}

void destroy(void *data){
	Stu *stu = (Stu*)(data);
	free(stu);
}

int main()
{
   Stu *stu1 = (Stu*)malloc(sizeof(Stu));
   stu1->age = 11;
   stu1->name = "HeXinyuan";

   Stu *stu2 = (Stu*)malloc(sizeof(Stu));
   stu2->age = 22;
   stu2->name = "ZhangJingli";

   Set *set = (Set*)malloc(sizeof(Set));
   set_init(set,match,destroy);
   set_insert(set,(void *)stu1);
   set_insert(set,(void *)stu1);
   set_insert(set,(void *)stu2);
   set_destroy(set);

   ListElmt *head = list_head(set);
   Stu *s = (Stu*)(head->data);
   printf("set_size=%d\n",set_size(set));
   printf("hello world\n");
   return 1;
}
