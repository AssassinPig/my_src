#include <stdio.h>

typedef struct list_node{
	int data;
	struct list_node* next;
};

typedef struct graph_node{
	struct graph_node* next;
	struct link_node* list;
};

typedef struct list_node link_list;
typedef struct graph_node graph;

graph* g;

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

int main()
{
	//must have one graph_node as head
	g = malloc(sizeof(struct graph_node));
	g->list = NULL;	
	g->next = NULL;

	for(int i=0; i < 10; ++i)
	{
		//must have one list_node as head
		struct list_node* list = malloc(sizeof(struct list_node));  	
		list->next = NULL;
		list->data = i*10;

		for(int j=1; j<10; ++j)
		{
			InsertNode(list, j+i*10);
		}

		InsertList(g, list);	
	}	

	struct graph_node* graph_list = g; 
	while(graph_list)
	{
		struct list_node* list = graph_list->list;
		while(list)
		{
			printf("%d ", list->data);
			list = list->next;
		}
		printf("\n");
		graph_list = graph_list->next;
	}
	
	return 0;
}
