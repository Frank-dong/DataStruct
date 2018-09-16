#include <stdio.h>
#include "dstypedef.h"

#define SQLIST	1
#define DLINKLIST 2
#define CONTAINEROF 3
#define LISTKERNEL	4


#define DEBUG_MODULE	LISTKERNEL

int main(int argc, char* argv[])
{
	int 		ret = 0;
	int			i = 0;
	int			a_test_data[8] = {5, 1, 6, 8, 10, 100, 65, 2};

#if DEBUG_MODULE == SQLIST
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

#elif DEBUG_MODULE == DLINKLIST

	pdlinklist_t	list;
	data_type_t		data;

	ret |= d_linklist_init(&list);
	ret |= d_listlist_traverse(list);

	data.data = 10;
	ret |= d_linklist_insert(list, 0, &data);

	data.data = 1232;
	ret |= d_linklist_insert(list, 0, &data);

	data.data = 129898;
	ret |= d_linklist_insert(list, 2, &data);

	ret |= d_listlist_traverse(list);

	data.data = 0;
	ret |= d_linklist_del(list, 2, &data);
	printf("deled %d. , ret = 0x%x\r\n", data.data, 0-ret);

	ret |= d_listlist_traverse(list);

	d_linklist_deinit(&list);

	ret |= d_listlist_traverse(list);
#elif DEBUG_MODULE == CONTAINEROF

	struct student {
		int age;
		char* name;
		int height;
	};

	struct student stu_a;
	struct student*	pstu = NULL;

	stu_a.age = 10;
	stu_a.name = "Lucy";
	stu_a.height = 100;

	pstu = container_of(&stu_a.name, struct student, name);

	printf("age = %d.\r\n", pstu->age);
	printf("name = %s.\r\n", pstu->name);
	printf("height = %d.\r\n", pstu->height);
#elif DEBUG_MODULE == LISTKERNEL

	struct student {
		int age;
		int height;
		char name[100];
		struct list_head list;
	};

	struct student *pstu = NULL;
	struct list_head* tmp = NULL;
	struct list_head* tmpnext = NULL;
	
	LIST_HEAD(stu);	//初始化一个链表


	for (i = 0; i < 8; ++i) {
		pstu = (struct student*) malloc (sizeof(struct student));
		pstu->age = a_test_data[i];
		strcpy(pstu->name, "Lily");
		list_add(&(pstu->list), &stu);
	}

	list_for_each(tmp, &stu) {
		pstu = list_entry(tmp, struct student, list);
		printf("age = %d, name = %s\r\n", pstu->age, pstu->name);
	}

	printf("\r\n");
	//删除第三个节点
	i = 0;
	list_for_each_safe(tmp, tmpnext, &stu) {
		if (i++ == 2) {
			pstu = list_entry(tmp, struct student, list);
			list_del(tmp);
			free(pstu);
			pstu = NULL;
		}
	}

	printf("After del node......\r\n");
	list_for_each(tmp, &stu) {
		pstu = list_entry(tmp, struct student, list);
		printf("age = %d, name = %s\r\n", pstu->age, pstu->name);
	}

#endif
	
	return 0;
}
