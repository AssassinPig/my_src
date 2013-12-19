#include "zlist.h"

#ifndef _ZMALLOC_H_
#define _ZMALLOC_H_

struct zdata_block{
	void* data;
	int max_size;
	int pos;	
};

typedef struct zdata_block zdata_block_t;

struct zpool{
	zlist_t* block_list;	
	zlist_t* large_list; 
	zlist_node_t* current_block;
	zlist_node_t* current_large;
	int max_size;
};

typedef struct zpool zpool_t;

zpool_t* create_pool(int size);

void clear_pool(zpool_t* pool);

void* zmalloc(int size);
#define zfree free

#endif //_ZMALLOC_H_ 
