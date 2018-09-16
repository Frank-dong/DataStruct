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
int d_linklist_deinit(pdlinklist_t* list);
int d_linklist_getlength(pdlinklist_t list);
int d_linklist_insert(pdlinklist_t list, int pos, data_type_t* item);
int d_linklist_del(pdlinklist_t list, int pos, data_type_t* item);
int d_linklist_getitem(pdlinklist_t list, int pos, data_type_t* item);
int d_linklist_find(pdlinklist_t list, data_type_t* data, pdlinklist_t* found);
int d_listlist_traverse(pdlinklist_t list);


#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
	
#define container_of(ptr, type, member) ({	\
		const typeof(((type* )0)->member) *__mptr = (ptr);	\
		(type*)((char*)__mptr - offsetof(type, member)) ;\
})

//------------------- linux kernel list -------------------
/*
include/linux/types.h
include/linux/list.h
*/

/********************************************
 Node       Node        Node        Node 
|----|     |----|      |----|      |----|
|    |     |    |      |    |      |    |
|    |     |    |      |    |      |    |
|----|     |----|      |----|      |----|
|list|<---->|list|<---->|list|<---->|list|
|----|     |----|      |----|      |----|

有示意图可以看出指针域只是节点的中的一个成员，
对链表中节点的指针域操作只用对其list成员做修改即可，
整个节点内存由调用者管理

********************************************/


struct list_head {
	struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) {&name, &name};	//初始化，next和prev都指向自己

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head* list)
{
	list->prev = list;
	list->next = list;
}

/**
 * __FUNC 开头是内部函数，供内部调用
 */
static inline void __list_add(struct list_head* new, struct list_head* prev, struct list_head* next)
{
	next->prev = new;
	new->next = next;
	prev->next = new;
	new->prev = prev;
}

static inline void list_add(struct list_head* new, struct list_head* head)
{
	__list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head* new, struct list_head* head)
{
	__list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head* prev, struct list_head* next)
{
	prev->next = next;
	next->prev = prev;
}

static inline void list_del(struct list_head* entry)
{
	__list_del(entry->prev, entry->next);
}

static inline void list_del_init(struct list_head* entry)
{
	__list_del(entry->prev, entry->next);
	INIT_LIST_HEAD(entry);
}

/**
 * 替换节点
 */
static inline void list_replace(struct list_head* old, struct list_head* new)
{
	new->next = old->next;
	new->prev = old->prev;
	new->next->prev = new;
	new->prev->next = new;
}

/**
 * 链表判空
 */
static inline int list_isempty(const struct list_head* head)
{
	return head->next == head;
}

/**
 * 获取节点  得到指向节点头的指针
 */
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * 遍历节点 
 * pos：指向每一个节点
 * head: 链表
 */
#define list_for_each(pos, head)	\
	for (pos = (head)->next; pos != head; pos = pos->next)

/**
 * 对比list_for_each 多了一个中间变量n，指向检索到的节点的next，
 * 此时如果删除遍历到的节点，则可以通过n继续遍历下去。所以在有删除节点的场景时，需要用此接口
 */
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != head; pos = n, n = pos->next)



#endif// __DSTYPEDEF_H__

