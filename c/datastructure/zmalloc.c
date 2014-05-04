#include <stdio.h>
#include <string.h>
#include "zmalloc.h"

zpool_t* pool=NULL;

zpool_t* create_pool(int size)
{
	pool = (zpool_t*)malloc(sizeof(zpool_t));
	pool->max_size = size;

	int n = size;
	
	pool->block_list = create_list();
	pool->large_list = create_list();

	char* block_data = malloc(size*n);
	char* large_data = malloc(size*n);

	int block_size = sizeof(zdata_block_t);
	char* block = malloc(block_size*size);
	char* large = malloc(block_size*size);
	printf("malloc large : %d\n", block_size*size);

	for(int i=0; i<n; ++i)
	{
		zdata_block_t* block_tmp = (zdata_block_t*)(block+i*block_size);
		zdata_block_t* large_tmp = (zdata_block_t*)(large+i*block_size);
	
		block_tmp->data = block_data+i*size;
		block_tmp->max_size=size;
		block_tmp->pos = 0;

		large_tmp->data = large_data+i*size;
		large_tmp->max_size=size;
		large_tmp->pos = 0;

		addNode(pool->block_list, block_tmp);	
		addNode(pool->large_list, large_tmp);	
	}

	pool->current_block = (zdata_block_t*)pool->block_list;
	pool->current_large = (zdata_block_t*)pool->large_list;

	return pool;
}

void clear_pool(zpool_t* pool)
{
	//to do
	pool->block_list = NULL;
	pool->large_list = NULL;		
}

void* zmalloc(int size)
{
	if(size > pool->max_size)
	{
		zdata_block_t* large = (zdata_block_t*)pool->current_large->data;
		if(large->max_size >= size)
		{
			void* data = large->data;
			pool->current_large=pool->current_large->next;
			return data;									
		}
	    else
			return NULL; //to do 
	}	
	else
	{
		zdata_block_t* block = (zdata_block_t*)pool->current_block->data;
		if(size > block->max_size - block->pos)
		{
			pool->current_block = pool->current_block->next;		
			return zmalloc(size);
		}	
		else
		{
			void* data = ((int*)block->data)+block->pos;
			block->pos += size;
			return data;
		}
	}

	return NULL;	
}

