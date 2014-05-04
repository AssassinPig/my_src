#ifndef _ZTREE_H__
#define _ZTREE_H__
	
struct ztree_node{
	void* data;	
	struct ztree_node_t* lchild;
	struct ztree_node_t* rchild;
};

typedef struct ztree_node ztree_node_t;
typedef struct ztree_node_t ztree;

ztree* create_tree();
void clear_tree();

void build_tree(ztree* tree, int v);

void preorder(ztree* tree);
void midorder(ztree* tree);
void postorder(ztree* tree);

void preorder2(ztree* tree);
void midorder2(ztree* tree);
void postorder2(ztree* tree);

#endif //_ZTREE_H__
