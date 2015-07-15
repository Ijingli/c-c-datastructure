/*
 * set.c
 *
 *  Created on: 2015��7��14��
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

//���ȵ���set_is_member��ȷ���ǲ����Ѿ�����data������Ƿ���1��������ǵ���list_ins_next
//���뷵��0���Ѿ����ڷ���1��ʧ�ܷ���-1
int set_insert(Set *set,const void *data){
	if(set_is_member(set,data)){
		return 1;
	}
	return list_ins_next(set,NULL,data);
}
//ͨ��list_next����������match������ָ���ĺ���ȷ��Ҫ�Ƴ��ĳ�Ա
//�ɹ�����0�����򷵻�-1
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
//��set_init��ʼ��setu��Ȼ�����set1����set2�ж�set_is_member���������
//�ɹ����㲢������0�����򷵻�-1
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
//�ȵ���set_init��ʼ��seti������set1����set2����set_is_member���ǵ��������
//�ɹ����㽻������0�����򷵻�-1
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
//�ص���set_init��ʼ��setd�����set1��ÿ����Ա����set_is_memberȷ����Ա�Ƿ���set2���ֹ���û���ֹ��ļ���setd
//�ɹ������ֵ����0�����򷵻�-1
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
//ͨ��list_next�������ϳ�Աֱ���ҵ���data�Ǻϵ�����
//�ҵ���Ա����1�����򷵻�0
int set_is_member(const Set *set,const void *data){
	ListElmt *element;
	for(element=list_head(set);element!=NULL;element=list_next(element)){
		if(set->match(element->data,data)){
			return 1;
		}
	}
	return 0;
}
//�������set1 size����set2 size ����ֱ���жϲ����Ӽ�
//����set1���ǲ���set_is_member set2
//set1��set2���Ӽ�����1�����򷵻�0
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
//���ж�sizeһ����Ȼ���ٵ���set_is_subset
//��ȷ���1�����򷵻�0
int set_is_equal(const Set *set1,const Set *set2){
	if(set_size(set1)!=set_size(set2))
		return 0;
	return set_is_subset(set1,set2);
}
