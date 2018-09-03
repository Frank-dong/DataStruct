#include "dstypedef.h"

int sqlist_init(sqlist_t** list, int length)
{
	sqlist_t* ptmp = NULL;

	if (!list || length <= 0)
		return RST_PARAMERR;

	ptmp = (sqlist_t*)calloc(1, sizeof(sqlist_t));
	ptmp->items = (SqlistDataType*)calloc(length, sizeof(SqlistDataType));
	ptmp->capacity = length;
	ptmp->length = 0;

	*list = ptmp;
	return RST_SUCCESS;
}

int sqlist_deinit(sqlist_t* list)
{
	if (!list)
		return RST_PARAMERR;

	free(list->items);
	list->capacity = 0;
	list->length = 0;
	free(list);

	return RST_SUCCESS;
}


int sqlist_getlength(sqlist_t* list)
{
	if (!list)
		return RST_PARAMERR;

	return list->length;
}

/**
 * 注意：可以插入的合法位置是[0, length]
 */
int sqlist_insert(sqlist_t* list, int pos, SqlistDataType* item)
{
	int i = 0;

	if (!list || pos < 0 || pos > list->length)
		return RST_PARAMERR;

	if (list->length >= list->capacity)
		return RSTSQLIST_FULL;
	
	for (i = 0; i < list->length - pos; ++i) {
		memcpy(&list->items[list->length - i], &list->items[list->length - i - 1], sizeof(SqlistDataType));
	}
	memcpy(&list->items[pos], item, sizeof(SqlistDataType));
	
	list->length += 1;

	return RST_SUCCESS;
}

/**
 * 注意：可以删除的合法位置是[0, length]
 */

int sqlist_del(sqlist_t* list, int pos)
{
	int i = 0;

	if (!list || pos < 0)	
		return RST_PARAMERR;
	
	if (list->length <= 0)
		return RSTSQLIST_EMPTY;
	else if (pos >= list->length)
		return RST_PARAMERR;

	for (i = 0; i < list->length - pos; ++i) {
		memcpy(&list->items[pos + i], &list->items[pos + i + 1], sizeof(SqlistDataType));
	}
	memset(&(list->items[pos + i]), 0, sizeof(SqlistDataType));
	list->length -= 1;
	
	return RST_SUCCESS;
}

int sqlist_getitem(sqlist_t* list, int pos, SqlistDataType* data)
{
	if (!list || pos < 0 || pos >= list->length || !data)
		return RST_PARAMERR;

	memcpy(data, &list->items[pos].data, sizeof(SqlistDataType));
	
	return RST_SUCCESS;
}

int sqlist_findpos(sqlist_t* list, SqlistDataType data)
{
	int i = 0;
	if (!list)
		return RST_PARAMERR;

	while (list->length - i++ > 0) {
		if (data.data == list->items[i].data)
			break;
	}
	return RST_SUCCESS;
}

int sqlist_isempty(sqlist_t* list)
{
	return RST_SUCCESS;
}

int sqlist_clear(sqlist_t* list)
{
	return RST_SUCCESS;
}

int sqlist_traverse(sqlist_t* list)
{
	int i = 0;

	if (!list)
		return RST_PARAMERR;

	for (i = 0; i < list->length; ++i) {
		printf("%d ", list->items[i].data);
	}

	printf("\r\n");
	
	return RST_SUCCESS;
}

