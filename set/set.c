/*
 * set.c
 *
 *  Created on: 2015年7月14日
 *      Author: Administrator
 */
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "set.h"

void set_init(Set *set,int (*match)(const void *key1,const void *key2),
		void (*destroy)(void *data)){
	list_init(set,destroy);
	set->match = match;
}

//首先调用set_is_member来确定是不是已经包含data，如果是返回1，如果不是调用list_ins_next
//插入返回0，已经存在返回1，失败返回-1
int set_insert(Set *set,const void *data){
	if(set_is_member(set,data)){
		return 1;
	}
	return list_ins_next(set,NULL,data);
}
//通过list_next遍历，根据match函数所指定的函数确定要移除的成员
//成功返回0，否则返回-1
int set_remove(Set *set,void **data){
	ListElmt *member,*prev;
	prev=NULL;
	for(member=list_head(set);member!=NULL;member=list_next(member)){
		if(set->match(*data,member->data))
			break;
		prev = member;
	}
	if(member == NULL)
		return -1;
    return list_rem_next(set,prev,data);
}
//先set_init初始化setu，然后遍历set1，对set2判断set_is_member，逐个添加
//成功计算并集返回0，否则返回-1
int set_union(Set *setu,const Set *set1,const Set *set2){
	ListElmt *member;
	void *data;
	set_init(setu,set1->match,NULL);
	for(member=list_head(set1);member!=NULL;member=list_next(member)){
		data = list_data(member);
		if(list_ins_next(setu,list_tail(setu),data)!=0){
			set_destroy(setu);
			return -1;
		}
	}
	for(member=list_head(set2);member!=NULL;member=list_next(member)){
		if(set_is_member(set1,list_data(member))){
			continue;
		}else{
			data = list_data(member);
			if(list_ins_next(setu,list_tail(setu),data)!=0){
				set_destroy(setu);
				return -1;
			}
		}
	}
	return 0;
}
//先调用set_init初始化seti，遍历set1，对set2进行set_is_member，是的逐个添加
//成功计算交集返回0，否则返回-1
int set_intersection(Set *seti,const Set *set1,const Set *set2){
	ListElmt *member;
	set_init(seti,set1->match,NULL);
	for(member=set1->head;member!=NULL;member=list_next(member)){
		if(set_is_member(set2,list_data(member))){
			if((list_ins_next(seti,list_tail(seti),list_data(member)))!=0){
				set_destroy(seti);
				return -1;
			}
		}
	}
	return 0;
}
//县调用set_init初始化setd，针对set1的每个成员调用set_is_member确定成员是否在set2出现过，没出现过的加入setd
//成功计算差值返回0，否则返回-1
int set_difference(Set *setd,const Set *set1,const Set *set2){
	ListElmt *member;
	void *data;
	set_init(setd,set1->match,NULL);
	for(member=list_head(set1);member!=NULL;member=list_next(member)){
		if(set_is_member(set2,data) == 0){
			data = list_data(member);
			if(list_ins_next(setd,list_tail(setd),data) == -1){
				set_destroy(setd);
				return -1;
			}
		}
	}
	return 0;
}
//通过list_next遍历集合成员直到找到与data吻合的数据
//找到成员返回1，否则返回0
int set_is_member(const Set *set,const void *data){
	ListElmt *element;
	for(element=list_head(set);element!=NULL;element=list_next(element)){
		if(set->match(element->data,data)){
			return 1;
		}
	}
	return 0;
}
//首先如果set1 size大于set2 size 可以直接判断不是子集
//遍历set1，是不是set_is_member set2
//set1是set2的子集返回1，否则返回0
int set_is_subset(const Set *set1,const Set *set2){
	ListElmt *member;
	if(set_size(set1)>set_size(set2))
		return 0;
	for(member = list_head(set1);member!=NULL;member=list_next(member)){
		if(set_is_member(set2,list_data(member))==0){
			return 0;
		}
	}

	return 1;
}
//先判断size一样，然后再调用set_is_subset
//相等返回1，否则返回0
int set_is_equal(const Set *set1,const Set *set2){
	if(set_size(set1)!=set_size(set2))
		return 0;
	return set_is_subset(set1,set2);
}

