/*
 * chtbl.c
 *
 *  Created on: 2015Äê7ÔÂ21ÈÕ
 *      Author: Administrator
 */
#include "chtbl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/*
typedef struct CHTBL_
{
	int buckets;
	int (*h)(void *data);
	int (*match)(const void *key1,const void *key2);
	void (*destroy) (void *data);
	int size;
	List *table
}CHTBL;
#define chtbl_size(htbl)  ((htbl)->size)
*/

int chtbl_init(CHTBL *htbl,int buckets, int (*h)(void *data),
		int (*match)(const void *key1,const void *key2),void (*destroy)(void *data)){
	int i;
	if((htbl->table = (List*)malloc(buckets*sizeof(List)) )==NULL)
		return -1;
	htbl->buckets = buckets;
	for(i=0;i<buckets;i++){
		list_init(&htbl->table[i],destroy);
	}
	htbl->match = match;
	htbl->destroy = destroy;
	htbl->h = h;
	htbl->size = 0;
	return 0;
}

void chtbl_destroy(CHTBL *htbl){
	int i;
	for(i=0;i<htbl->buckets;i++){
		list_destroy(&htbl->table[i]);
	}
	free(htbl->table);
	memset(htbl,0,sizeof(CHTBL));
	return;
}

int chtbl_insert(CHTBL *htbl,void *data){
	void *temp;
	int bucket,retval;

	temp = (void*)data;
	if(chtbl_lookup(htbl,&temp)==0)
		return 1;
	bucket = htbl->h(data)/htbl->buckets;
	if((retval = list_ins_next(&htbl->table[bucket],NULL,data))==0)
		htbl->size++;
	return retval;

}

int chtbl_remove(CHTBL *htbl,void **data){
	ListElmt *element,
	         *prev;
	int bucket;
	bucket = htbl->h(*data)/htbl->buckets;
	prev = NULL;
	for(element = list_head(&htbl->table[bucket]);element!=NULL;element=list_next(element)){

		if(htbl->match(*data,list_data(element))){
			if(  list_rem_next(&htbl->table[bucket],prev,data) == 0 ){
				htbl->size--;
				return 0;
			}else{
				return -1;
			}
		}
		prev = element;
	}
	return -1;
}

int chtbl_lookup(const CHTBL *htbl,void **data){
	ListElmt *element;
	int bucket;
	bucket = htbl->h(*data)/htbl->buckets;
	for(element=list_head(&htbl->table[bucket]);element!=NULL;element=list_next(element)){
		if(htbl->match(*data,list_data(element))){
			*data = list_data(element);
			return 0;
		}
	}
	return -1;
}





