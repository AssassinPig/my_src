#ifndef _ZSTACK02_H__ 
#define _ZSTACK02_H__

struct zstack_node02 {
	void* data;
};

typedef struct zstack_node02 zstack_node02_t;

struct zstack02
{
	int capacity;
	int top;
	zstack_node02_t* array;
};

typedef struct zstack02 zstack02_t;

zstack02_t* create_stack02(int max);
void crear_stack02(zstack02_t* stack);

void push02(zstack02_t* stack, void* data);
zstack_node02_t* pop02(zstack02_t* stack);

int length(zstack02_t* stack);
int empty(zstack02_t* stack);


#endif //_ZSTACK02_H__
