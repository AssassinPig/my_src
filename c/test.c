#include <stdio.h>
#include <string.h>
#include <signal.h>
//#include "stack.h"
#include "list.h"
#include "zmalloc.h"

extern zpool_t* pool;
extern zpool_t* create_pool(int size);

int main(int nargc, char* argv[])
{
	//stack
//	stack_t* s;
//	s = malloc(sizeof(stack_t));
//	init(s);
	
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
	return 0;
}
