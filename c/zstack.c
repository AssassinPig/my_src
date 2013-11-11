#include "zstack.h"

#include <stdio.h>
#include <stdlib.h>

zstack_t* create_stack()
{
	zstack_t* stack = (zstack_t*)malloc(sizeof(zstack_t));	
	if(stack) {
		stack->top= NULL;
		return stack;
	}	

	return NULL;
}

void clear_stack(zstack_t* stack)
{
	while(1) {
		zstack_node_t* node = pop(stack);
		if(node == NULL) {
			break;
		}
		
		free(node); //may be memory leak		
	}	
	
	free(stack);
}


zstack_node_t* pop(zstack_t* stack)
{
	zstack_node_t* node = stack->top;
	if(node)
		stack->top = node->next;
	else 
		stack->top = NULL;

	return node;	
}

void push(zstack_t* stack, void* data)
{
	zstack_node_t* node = (zstack_node_t*)malloc(sizeof(zstack_node_t));	
	if(node) {
		node->data = data;
		node->next = stack->top;
	} else {
		perror("zstack push failed");
		return;
	}	
	
	stack->top = node;	
}

zstack_node_t* top(zstack_t* stack) 
{
	return stack->top;	
}
