#ifndef _ZSTACK_H__ 
#define _ZSTACK_H__

typedef void (*ptrFunDestroy)(void* ptrElem); 

struct zstack_node
{
	void* data;	
	struct zstack_node* next;
};

typedef struct zstack_node zstack_node_t;

struct zstack
{
	zstack_node_t* top;
	ptrFunDestroy ptrFun;
};

typedef struct zstack zstack_t;

zstack_t* create_stack(ptrFunDestroy ptrFun);
void clear_stack(zstack_t* stack);

zstack_node_t* pop(zstack_t* stack);
void push(zstack_t* stack, void* data);
zstack_node_t* top(zstack_t* stack);

int capacity(zstack_t* stack);
//int empty(zstack_t* stack);

#endif //_ZSTACK_H__
