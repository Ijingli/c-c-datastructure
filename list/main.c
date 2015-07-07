#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "list.h"
void destroy(void *data){
    free(data);
}

typedef struct Stu_
{
    int age;
    int score;
}Stu;

int main()
{


    Stu *stu = (Stu*)malloc(sizeof(Stu));
    stu->age = 11;
    stu->score = 22;
    List *list =(List*)malloc(sizeof(List));
    list_init(list,destroy);
    list_ins_next(list,NULL,(void*)stu);
    list_ins_next(list,NULL,(void*)stu);
    list_ins_next(list,NULL,(void*)stu);
    list_ins_next(list,NULL,(void*)stu);
    list_ins_next(list,NULL,(void*)stu);
    //printf("age is %d ,score is %d",((Stu*)(list_head(list)))->age,((Stu*)(list_head(list)))->score);
    printf("list size is %d\n",list_size(list));
    ListElmt *head = list_head(list);
    Stu *st = (Stu*)(head->data);
    printf("age is %d score is %d\n",st->age,st->score);
    return 0;
}
