#include <stdio.h>
#include <string.h>
#include <signal.h>
//#include "stack.h"
#include "list.h"
#include "zmalloc.h"
#include "zstack.h"
#include "zstack02.h"
#include "ztree.h"
#include "zqueue.h"

#include "sort.h"

extern zpool_t* pool;
extern zpool_t* create_pool(int size);

void* mymemmove(char* des, char* src, size_t n)
{
	char* ret = des;
	while(n)
	{
		*des = *src;
		des++;
		src++;
		n--;
	}

	return ret;
}


int main(int nargc, char* argv[])
{
	//stack
//	stack_t* s;
//	s = malloc(sizeof(stack_t));
//	init(s);

//	zstack_t* stack = create_stack();
//	push(stack, "1");
//	push(stack, "2");
//	push(stack, "3");
//	
//	zstack_node_t* node = pop(stack);
//	node = pop(stack);
//	
//	clear_stack(stack);
//	printf("node->data %s\n", (const char*)node->data);
	
//	zstack02_t* stack02 = create_stack02(10);
//	push02(stack02, "1");
//	push02(stack02, "2");
//	push02(stack02, "3");
//	push02(stack02, "4");
//	zstack_node02_t* node = pop02(stack02);
//	printf("pop elem %s\n", (const char*)node->data);
	
	//list 
//	zlist_t* list = create_list();
//	if(!list)
//	{
//		perror("malloc failed\n");
//		return 1;
//	}
//
//	for(int i=0;i<384;++i)
//	{
//		int* data=(int*)malloc(sizeof(int));
//		*data = i;
//		addNode(list,data); 
//	}
//
//	printf("list.count=%d\n", CountNode(list));
//
//	if(list)
//	{
//		ClearList(list);		
//		list = NULL;
//	}
//
//	printf("list.count=%d\n", CountNode(list));

	//tree
	ztree* tree = create_tree();	
	srand(NULL);			
	for(int i=0; i<10; ++i) {
		int n = rand()%100;
		build_tree(tree, n);
		printf("%d\t", n);
	}
	printf("\n");

//	preorder(tree);
//	printf("\n");
//	preorder2(tree);
//	printf("\n");

//	midorder(tree);
//	printf("\n");
//	midorder2(tree);
//	printf("\n");

//	postorder(tree);
//	printf("\n");
//	postorder2(tree);
//	printf("\n");

	//queue
//	zqueue_t* queue = create_queue();	
//	int array_data[10];
//	for(int i=0; i<10; ++i) {
//		array_data[i] = i;
//		enqueue(queue, &array_data[i]);
//	}
//		
//	for(int i=0; i<10; ++i) {
//		zqueue_node_t* node = dequeue(queue);
//		printf("element[%d] in queue %d\n", i, *(int*)node->data);
//	}

	//malloc
//	pool = create_pool(64);
//
//	void* data = zmalloc(64);	
//	//void* data = zmalloc(72);	
//	if(data)
//	{
//		printf("zmalloc succ\n");
//	}
//	else
//	{
//		printf("zmalloc failed\n");
//	}

//	struct sigaction act;
//	act.sa_handler = SIG_IGN;
//	act.sa_flags &= ~SA_RESETHAND;
//	sigaction(SIGPIPE, act, NULL);

	//test memmove
//	char s1[10];
//	memset(s1, 0, 10);
//	sprintf(s1, "abcdefg");
//	char s2[10];
//	memset(s2, 0, 10);
//	//char* s3 = memmove(s2, s1, strlen(s1));
//	char* s3 = mymemmove(s2, s1, strlen(s1));
//
//	printf("s2=%s\n",s2);
//	printf("s3=%s\n",s3);
//	if(s2==s3) {
//		printf("s2 == s3\n");
//	} else {
//		printf("s2 != s3\n");
//	}

	//bubble_sort();

//	int a[] = {3, 4, 6, 1, 8, 2, 7, 9, 5, 0};
//	for(int i=0; i<10; ++i) {
//		printf("%d\t", a[i]);
//	}
//	printf("\n");
//	zsort(a, 0, 9);
//	for(int i=0; i<10; ++i) {
//		printf("%d\t", a[i]);
//	}
//	printf("\n");

	//insertion_sort();
	return 0;
}
