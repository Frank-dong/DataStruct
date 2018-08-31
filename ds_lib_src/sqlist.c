#include "dstypedef.h"

int sqlist_init(sqlist_t** list, int length)
{
	sqlist_t *ptmp = NULL;

	if (!list || length <= 0)
		return RST_PARAMERR;

	ptmp->items = (SqlistDataType)calloc(length, sizeof(SqlistDataType));
	ptmp->length = length;
	ptmp->valid_length = 0;

	*list = ptmp;
	return RST_SUCCESS;
}

int sqlist_deinit(sqlist_t* list)
{
	if (!list)
		return RST_PARAMERR;

	free(list->items);
	list->length = 0;
	list->valid_length = 0;

	return RST_SUCCESS;
}


int sqlist_getlength(sqlist_t* list)
{
	if (!list)
		return RST_PARAMERR;

	return list->valid_length;
}

int sqlist_insert(sqlist_t* list, int pos, SqlistDataType data)
{
	if (!list || pos < 0)
		return RST_PARAMERR;

	return RST_SUCCESS;
}

int sqlist_del(sqlist_t* list, int pos)
{
	return RST_SUCCESS;
}

int sqlist_getitem(sqlist_t* list, int pos, SqlistDataType* data)
{
	return RST_SUCCESS;
}

int sqlist_getprior(sqlist_t* list, SqlistDataType data, SqlistDataType* data_prior)
{
	return RST_SUCCESS;
}

int sqlist_getnext(sqlist_t* list, SqlistDataType data, SqlistDataType* data_next)
{
	return RST_SUCCESS;
}

int sqlist_findpos(sqlist_t* list, SqlistDataType data)
{
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
	return RST_SUCCESS;
}

