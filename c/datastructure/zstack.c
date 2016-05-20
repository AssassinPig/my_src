#include "zstack.h"

#include <stdio.h>
#include <stdlib.h>

zstack_t* create_stack(ptrFunDestroy ptrFun)
{
    zstack_t* stack = (zstack_t*)malloc(sizeof(zstack_t));	
    if(stack) {
        stack->top= NULL;
    	stack->ptrFun = ptrFun;
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
	
	stack->ptrFun(node->data);
        free(node); 		
    }	

    free(stack);
}


zstack_node_t* pop(zstack_t* stack)
{
    zstack_node_t* node = stack->top;
    if(node)
        stack->top = node->next;

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

int capacity(zstack_t* stack)
{
    int n=0;
    zstack_node_t* node = stack->top;
    while(node) {
        ++n;
        node = node->next;
    }

    return n;
}

//int empty(zstack_t* stack) 
//{
//    return top(stack) ? 0 : 1;
//}
