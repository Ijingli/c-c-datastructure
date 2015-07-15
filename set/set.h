/*
 * set.h
 *
 *  Created on: 2015年7月14日
 *      Author: Administrator
 */

#ifndef SET_H_
#define SET_H_
#include <stdlib.h>
#include "list.h"
typedef List Set;//将List重命名为Set

void set_init(Set *set,int (*match)(const void *key1,const void *key2),
		void (*destroy)(void *data));
#define set_destroy list_destroy
//首先调用set_is_member来确定是不是已经包含data，如果是返回1，如果不是调用list_ins_next
int set_insert(Set *set,const void *data);
//通过list_next遍历，根据match函数所指定的函数确定要移除的成员
int set_remove(Set *set,void **data);
//先set_init初始化setu，然后遍历set1，对set2判断set_is_member，逐个添加
int set_union(Set *setu,const Set *set1,const Set *set2);
//先调用set_init初始化seti，遍历set1，对set进行set_is_member，是的逐个添加
int set_intersection(Set *seti,const Set *set1,const Set *set2);
//县调用set_init初始化setd，针对set1的每个成员调用set_is_member确定成员是否在set2出现过，没出现过的加入setd
int set_difference(Set *setd,const Set *set1,const Set *set2);
//通过list_next遍历集合成员直到找到与data吻合的数据
int set_is_member(const Set *set,const void *data);
//首先判断set1的size是否小于set2的size，然后遍历set1，是不是set_is_member set2
int set_is_subset(const Set *set1,const Set *set2);
//先判断size一样，然后再调用set_is_subset
int set_is_equal(const Set *set1,const Set *set2);
#define set_size(set)  ((set)->size)
#endif /* SET_H_ */
