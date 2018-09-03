#include <stdio.h>
#include "dstypedef.h"


int main(int argc, char* argv[])
{
	int 		ret = 0;
	int			i = 0;
	int			a_test_data[8] = {5, 1, 6, 8, 10, 100, 65, 2};
	sqlist_t*	sqlist;
	SqlistDataType	item;


	ret = sqlist_init(&sqlist, 10);

	for (i = 0; i < 8; ++i) {
		item.data = a_test_data[i];
		sqlist_insert(sqlist, 0, &item);
	}

	printf("Traverse list:");
	sqlist_traverse(sqlist);
	printf("now clear the list.\r\n");
	sqlist_clear(sqlist);
	printf("Traverse list:");
	sqlist_traverse(sqlist);
	
	item.data = 1;
	sqlist_insert(sqlist, 0, &item);
	
	item.data = 5;
	sqlist_insert(sqlist, 1, &item);
	
	item.data = 4;
	sqlist_insert(sqlist, 0, &item);

	item.data = 10;
	sqlist_insert(sqlist, 2, &item);

	sqlist_traverse(sqlist);

	sqlist_del(sqlist, 1);
	sqlist_traverse(sqlist);

	sqlist_del(sqlist, 0);
	sqlist_traverse(sqlist);

	sqlist_del(sqlist, 0);
	sqlist_traverse(sqlist);

	sqlist_del(sqlist, 0);
	sqlist_traverse(sqlist);

	printf("length = %d.\r\n", sqlist_getlength(sqlist));
	ret = sqlist_del(sqlist, 0);
	printf("ret = -0x%x\r\n", 0-ret);
	sqlist_traverse(sqlist);
	
	sqlist_deinit(sqlist);
	
	return 0;
}
