#ifndef __DSTYPEDEF_H__
#define __DSTYPEDEF_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------- maroc -------------------------
#define RST_SUCCESS		(0)
#define RST_PARAMERR	(-1)

#define RSTSQLIST_BASE	(0x1000)
#define RSTSQLIST_FULL	(RSTSQLIST_BASE + 1)
#define RSTSQLIST_EMPTY	(RSTSQLIST_BASE + 2)


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
typedef int LinklistDataType;
#if 0
typedef struct s_linklist_node_t{
	LinklistDataType	data;
	s_linklist_node_t* next;
} s_linklist_node_t;
#endif

#endif// __DSTYPEDEF_H__

