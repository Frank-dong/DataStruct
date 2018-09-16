#include "dstypedef.h"

/**
 * 带头节点的双向循环链表
 */
int d_linklist_init(pdlinklist_t* head)
{
	*head = (pdlinklist_t)calloc(1, sizeof(dlink_t));
	if (*head == NULL) {
		return RST_ERROR;
	}

	(*head)->next = *head;
	(*head)->pre = *head;

	return RST_SUCCESS;
}

int d_linklist_deinit(pdlinklist_t* head)
{
	dlink_t*	tmp = NULL; 
	dlink_t*	freenode = NULL;
		
	if (!(*head))
		return RST_PARAMERR;

	tmp = (*head)->next;
	while(tmp != (*head)) {
		freenode = tmp;
		tmp = tmp->next;
		free(freenode);
	}
	free(tmp);
	*head = NULL;

	return RST_SUCCESS;
}

/**
 * 执行成功返回节点个数，失败返回负值
 */
int d_linklist_getlength(pdlinklist_t list)
{
	int			len = 0;
	dlink_t*	tmp = NULL;
	
	if (!list)
		return RST_ERROR;

	tmp = list->next;
	while (tmp != list) {
		++len;
		tmp = tmp->next;
	}

	return len;
}

/**
 * 插入的位置参数合法范围是[0~len]
 */
int d_linklist_insert(pdlinklist_t list, int pos, data_type_t* item)
{
	int			i = 0;
	dlink_t*	tmp = NULL;
	dlink_t*	newnode = NULL;

	if (!list || pos < 0 || !item)
		return RST_PARAMERR;

	tmp = list->next;
	for (i = 0; i < pos && tmp != list; ++i)
		tmp = tmp->next;

	if (tmp == list && i < pos)
		return RSTLINKLIST_POSERR;

	newnode = (dlink_t*)malloc(sizeof(dlink_t));
	memcpy(&newnode->data, item, sizeof(data_type_t));
	
	tmp->pre->next = newnode;
	newnode->next = tmp;
	newnode->pre = tmp->pre;
	tmp->pre = newnode;

	return RST_SUCCESS;	
}

/**
 * 删除的位置参数合法范围是[0~(len -1)]
 * item用来保存删除的数据
 */
int d_linklist_del(pdlinklist_t list, int pos, data_type_t* item)
{
	int			i = 0;
	dlink_t*	tmp = NULL;

	if (!list || pos < 0)
		return RST_PARAMERR;

	tmp = list->next;
	for (i = 0; i < pos && tmp->next != list; ++i)
		tmp = tmp->next;

	if (tmp->next == list && i < pos)
		return RSTLINKLIST_POSERR;

	tmp->pre->next = tmp->next;
	tmp->next->pre = tmp->pre;

	if (item)
		memcpy(item, &tmp->data, sizeof(data_type_t));

	free(tmp);

	return RST_SUCCESS;
}

/**
 * 查找的位置参数合法范围是[0~(len -1)]
 * item用来保存删除的数据
 */
int d_linklist_getitem(pdlinklist_t list, int pos, data_type_t* item)
{
	int			i = 0;
	dlink_t*	tmp = NULL;

	if (!list || pos < 0 || !item)
		return RST_PARAMERR;

	tmp = list->next;
	for (i = 0; i < pos && tmp->next != list; ++i)
		tmp = tmp->next;

	if (tmp->next == list && i < pos)
		return RSTLINKLIST_POSERR;

	memcpy(item, &tmp->data, sizeof(data_type_t));

	return RST_SUCCESS;
}

int d_linklist_find(pdlinklist_t list, data_type_t* data, pdlinklist_t* found)
{
	int 		i = 0;
	dlink_t*	tmp = NULL;

	if (!list || !data || !found)
		return RST_PARAMERR;

	tmp = list->next;
	while (tmp != list) {
		if (tmp->data.data == data->data)
			break;
		tmp = tmp->next;
	}

	if (tmp == list) {
		return RST_NOTFOUND;
	} else {
		*found = tmp;
		return RST_SUCCESS;
	}
}

int d_listlist_traverse(pdlinklist_t list)
{
	dlink_t*	tmp = NULL;

	if (!list)
		return RST_PARAMERR;

	printf("DLink list:");
	tmp = list->next;
	while (tmp != list) {
		printf("%d ", tmp->data.data);
		tmp = tmp->next;
	}
	printf("\r\n");

	return RST_SUCCESS;
}


/*-------------------------- 下面是linux内核中的实现方式 -----------------------------------*/





