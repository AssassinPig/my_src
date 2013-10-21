#ifndef _ZLIST_H_
#define _ZLIST_H_

struct zlist_node
{
	void* data;
	struct zlist_node* next;
};

typedef struct zlist_node zlist_node_t;
typedef zlist_node_t zlist_t;

zlist_t* create_list();
zlist_node_t* create_node();
void addNode(zlist_t* list, void* data);
void* DelNode(zlist_t* list, void* data);
int CountNode(zlist_t* list);
void ClearList(zlist_t* list);

#endif //_ZLIST_H_ 
