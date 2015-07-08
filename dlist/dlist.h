/*
 * dlist.h
 *
 *  Created on: 2015��7��8��
 *      Author: Administrator
 */

#ifndef DLIST_H_
#define DLIST_H_

//˫������ڵ�
typedef struct DListElmt_
{
	void *data;//������
	struct DListElmt_ *prev;//ǰ��ָ��
	struct DListElmt_ *next;//���ָ��
}DListElmt;


typedef struct DList_
{
	int size;//�����С
	DListElmt *head;//ͷ
	DListElmt *tail;//β
	//�Զ��庯��
	void (*destroy) (void *data);
}DList;


//��ʼ������
void dlist_init(DList *list,void (*destroy) (void *data));
//ɾ�����нڵ㣬����init������destroy�����������ڴ�
void dlist_destroy(DList* list);
//�ɹ�����1  ʧ�ܷ���-1
int  dlist_ins_next(DList *list,DListElmt *element,const void *data);
int  dlist_ins_prev(DList *list,DListElmt *element,const void *data);
//ɾ��element��ָ���Ľڵ㣬�ýڵ���������ŵ�data��
int  dlist_remove(DList *list,DListElmt *element,void **data);

#define dlist_size(list) ((list)->size)
#define dlist_head(list)  ((list)->head)
#define dlist_tail(list)  ((list)->tail)
#define dlist_is_head(element)  ((element)->prev==NULL?1:0)
#define dlist_is_tail(element)   ((element)->next==NULL?1:0)
#define dlist_data(element)  ((element)->data)
#define dlist_next(element)   ((element)->next)
#define dlist_prev(element)   ((element)->prev)



#endif /* DLIST_H_ */
