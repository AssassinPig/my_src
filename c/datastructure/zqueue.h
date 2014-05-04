#ifndef _ZQUEUE_H__ 
#define _ZQUEUE_H__

struct zqueue_node {
	void* data;
	struct zqueue_node_t* prenode;
};

typedef struct zqueue_node zqueue_node_t;

struct zqueue{
	struct zqueue_node_t* tail;
	struct zqueue_node_t* head;
};

typedef struct zqueue zqueue_t;

zqueue_t* create_queue();
void clear_queue(zqueue_t* queue);

void enqueue(zqueue_t* queue, void* data);
zqueue_node_t* dequeue(zqueue_t* queue);

#endif//_ZQUEUE_H__ 
