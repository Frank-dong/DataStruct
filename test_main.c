#include <stdio.h>
#include "dstypedef.h"


int main(int argc, char* argv[])
{
	sqlist_t*	sqlist;
	int 		ret = 0;

	ret = sqlist_init(&sqlist, 10);
	printf("ret = %d.\r\n", ret);
	
	
	return 0;
}
