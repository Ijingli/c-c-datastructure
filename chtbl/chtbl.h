/*
 * chtbl.h
 *
 *  Created on: 2015Äê7ÔÂ21ÈÕ
 *      Author: Administrator
 */

#ifndef CHTBL_H_
#define CHTBL_H_
#include<stdlib.h>
#include "list.h"

typedef struct CHTBL_
{
	int buckets;
	int (*h)(void *data);
	int (*match)(const void *key1,const void *key2);
	void (*destroy) (void *data);
	int size;
	List *table
}CHTBL;

int chtbl_init(CHTBL *htbl,int buckets, int (*h)(void *data),
		int (*match)(const void *key1,const void *key2),void (*destroy)(void *data));

void chtbl_destroy(CHTBL *htbl);

int chtbl_insert(CHTBL *htbl,void *data);

int chtbl_remove(CHTBL *htbl,void **data);

int chtbl_lookup(const CHTBL *htbl,void **data);

#define chtbl_size(htbl)  ((htbl)->size)



#endif /* CHTBL_H_ */
