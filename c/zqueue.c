#include "zqueue.h"
#include <stdio.h>

zqueue_t* create_queue()
{
	zqueue_t* queue = (zqueue_t*)malloc(sizeof(zqueue_t));
	if(!queue) 
		return NULL;
	
	queue->tail = NULL;
	queue->head = NULL;
}

void clear_queue(zqueue_t* queue)
{

}

void enqueue(zqueue_t* queue, void* data)
{
	if(!queue->head) {
		queue->head = (zqueue_node_t*)malloc(sizeof(zqueue_node_t));	
		queue->tail = queue->head;
		zqueue_node_t* head = queue->head;
		head->data = data;
		head->prenode = NULL;
		return;
	}

	zqueue_node_t* node = (zqueue_node_t*)malloc(sizeof(zqueue_node_t));
	node->data = data;
	node->prenode = NULL;
	zqueue_node_t* head = queue->head;
	head->prenode = node;
	queue->head = node;
}

zqueue_node_t* dequeue(zqueue_t* queue)
{
	zqueue_node_t* node = queue->tail;
	if(!node->prenode) {
		queue->tail = NULL;
		queue->head = NULL;
	} else {
		queue->tail = node->prenode;	
	} 
	
	return node;	
}
