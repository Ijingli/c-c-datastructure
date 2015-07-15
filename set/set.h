/*
 * set.h
 *
 *  Created on: 2015��7��14��
 *      Author: Administrator
 */

#ifndef SET_H_
#define SET_H_
#include <stdlib.h>
#include "list.h"
typedef List Set;//��List������ΪSet

void set_init(Set *set,int (*match)(const void *key1,const void *key2),
		void (*destroy)(void *data));
#define set_destroy list_destroy
//���ȵ���set_is_member��ȷ���ǲ����Ѿ�����data������Ƿ���1��������ǵ���list_ins_next
int set_insert(Set *set,const void *data);
//ͨ��list_next����������match������ָ���ĺ���ȷ��Ҫ�Ƴ��ĳ�Ա
int set_remove(Set *set,void **data);
//��set_init��ʼ��setu��Ȼ�����set1����set2�ж�set_is_member��������
int set_union(Set *setu,const Set *set1,const Set *set2);
//�ȵ���set_init��ʼ��seti������set1����set����set_is_member���ǵ�������
int set_intersection(Set *seti,const Set *set1,const Set *set2);
//�ص���set_init��ʼ��setd�����set1��ÿ����Ա����set_is_memberȷ����Ա�Ƿ���set2���ֹ���û���ֹ��ļ���setd
int set_difference(Set *setd,const Set *set1,const Set *set2);
//ͨ��list_next�������ϳ�Աֱ���ҵ���data�Ǻϵ�����
int set_is_member(const Set *set,const void *data);
//�����ж�set1��size�Ƿ�С��set2��size��Ȼ�����set1���ǲ���set_is_member set2
int set_is_subset(const Set *set1,const Set *set2);
//���ж�sizeһ����Ȼ���ٵ���set_is_subset
int set_is_equal(const Set *set1,const Set *set2);
#define set_size(set)  ((set)->size)
#endif /* SET_H_ */
