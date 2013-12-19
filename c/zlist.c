#include <stdio.h>
#include <stdlib.h>
#include "zlist.h"

zlist_t* create_list()
{
	zlist_t* p = (zlist_t*)malloc(sizeof(zlist_node_t));
	if(p)
	{
		p->data = NULL;
		p->next = NULL;	
	}

	return p;
}

zlist_node_t* create_node()
{
	zlist_node_t* node = (zlist_node_t*)malloc(sizeof(zlist_node_t));
	node->data = NULL;
	node->next = NULL;
	return node;
}

void addNode(zlist_t* list, void* data){
	zlist_node_t* node = list;	
	
	while(node->next){
		node = node->next;		
	}
	
	zlist_node_t* new_node = create_node();		
	node->data = data;
	node->next = new_node;
}

void* DelNode(zlist_t* list, void* data)
{
	return NULL;
}

int CountNode(zlist_t* list)
{
	int count = 0;
	if(!list) 
		return count;

	while(list->next){
		++count;
		list = list->next;
	}

	return count;
}

void ClearList(zlist_t* list)
{
	while(list){
		zlist_node_t* node = list;
		list = list->next;
		free(node);	
	}	
}

