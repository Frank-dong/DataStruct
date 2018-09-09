#ifndef __DSTYPEDEF_H__
#define __DSTYPEDEF_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------- maroc -------------------------
enum BOOL {
	FALSE = 0,
	TRUE  = 1,
};

#define RST_SUCCESS		(0)
#define RST_ERROR		(-1)
#define RST_PARAMERR	(-2)
#define RST_NOTFOUND	(-3)


#define RSTSQLIST_BASE	(-0x1000)
#define RSTSQLIST_FULL	(RSTSQLIST_BASE - 1)
#define RSTSQLIST_EMPTY	(RSTSQLIST_BASE - 2)

#define RSTLINKLIST_BASE	(-0x2000)
#define RSTLINKLIST_POSERR	(RSTLINKLIST_BASE - 1)	//插入位置参数太大


typedef struct {
	int data;
}data_type_t;

//------------------- Sequence Table ---------------
typedef struct {
	int data;
}SqlistDataType;

typedef struct {
	SqlistDataType* items;
	int capacity;	//顺序表的总长度
	int length;		//当前有效长度
} sqlist_t;

int sqlist_init(sqlist_t** list, int length);
int sqlist_deinit(sqlist_t* list);
int sqlist_getlength(sqlist_t* list);
int sqlist_insert(sqlist_t* list, int pos, SqlistDataType* data);
int sqlist_del(sqlist_t* list, int pos);
int sqlist_getitem(sqlist_t* list, int pos, SqlistDataType* data);
int sqlist_findpos(sqlist_t* list, SqlistDataType data);
int sqlist_isempty(sqlist_t* list);
int sqlist_clear(sqlist_t* list);
int sqlist_traverse(sqlist_t* list);


//-------------------- Linklist Table ----------------
//双向循环链表
typedef struct dlink{
	data_type_t	data;
	struct dlink* next;
	struct dlink* pre;
} dlink_t, *pdlinklist_t;

int d_linklist_init(pdlinklist_t* list);
int d_linklist_deinit(pdlinklist_t list);
int d_linklist_getlength(pdlinklist_t list);
int d_linklist_insert(pdlinklist_t list, int pos, data_type_t* item);
int d_linklist_del(pdlinklist_t list, int pos, data_type_t* item);
int d_linklist_getitem(pdlinklist_t list, int pos, data_type_t* item);
int d_linklist_find(pdlinklist_t list, data_type_t* data, pdlinklist_t* found);
int d_listlist_traverse(pdlinklist_t list);

#endif// __DSTYPEDEF_H__

