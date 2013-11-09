#include <stdio.h>
#include <string.h>
#include <signal.h>
//#include "stack.h"
#include "list.h"
#include "zmalloc.h"
#include "zstack.h"

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

	return 0;
}
