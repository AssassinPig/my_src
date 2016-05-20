#include <stdio.h>
#include "link_graph.h"

//graph* g;

void InsertNode(struct link_node* list, int data)
{
	struct list_node* node = list;

	while(node->next != NULL)
	{
		node = node->next;
	}
	
	node->next = malloc(sizeof(struct list_node));	
	node = node->next;
	node->next = NULL;
	node->data = data;
} 

void InsertList(graph* graph, link_list *list)
{
	struct graph_node* node = graph;	
	
	while(node->next != NULL)	
	{
		node = node->next;
	}	

	node->next = malloc(sizeof(struct graph_node));	
	node = node->next;
	node->next = NULL;
	node->list = list;	
}
