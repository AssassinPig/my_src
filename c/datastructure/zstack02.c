#include "zstack02.h"
#include <stdio.h>
zstack02_t* create_stack02(int max)
{
	if(max <=0) 
		max = 10;

	zstack02_t* stack = malloc(sizeof(zstack02_t));
	stack->top = 0;	
	stack->capacity = max;	
	stack->array = (zstack_node02_t*)calloc(max, sizeof(zstack_node02_t));
	
	return stack;
}

void crear_stack02(zstack02_t* stack)
{
}


void push02(zstack02_t* stack, void* data)
{	
	if(stack->top == stack->capacity) 
		return;

	zstack_node02_t* node = &(stack->array[stack->top++]);
	node->data = data;
}

zstack_node02_t* pop02(zstack02_t* stack)
{
	if(stack->top == 0) 
		return NULL;	
	
	return &(stack->array[--stack->top]);
}


int length(zstack02_t* stack)
{
	return stack->top;
}

int empty(zstack02_t* stack)
{
	return !length(stack);
}

