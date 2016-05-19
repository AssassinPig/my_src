#ifndef _ZMULTIPLE_TREE_H__
#define _ZMULTIPLE_TREE_H__
struct zmultiple_tree_node{
    void* data; 
    struct zmultiple_tree_node_t* lchild; 
    struct zmultiple_tree_node_t* sibling; 
};
/*
typedef struct zmultiple_tree_node zmultiple_tree_node_t;
typedef zmultiple_tree_node_t zmultiple_tree_t;

zmultiple_tree_t* create_multiple_tree();
void clear_multiple_tree(zmultiple_tree_t* tree);

bool insert_as_child(zmultiple_tree_node_t* node, void* data);
bool insert_as_child(zmultiple_tree_node_t* node, zmultiple_tree_node_t* new_node);
bool insert_as_sibling(zmultiple_tree_node_t* node, void* data);
bool insert_as_sibling(zmultiple_tree_node_t* node, zmultiple_tree_node_t* new_node);

zmultiple_tree_node_t* remove_multiple_node(void* data);
zmultiple_tree_node_t* remove_multiple_node(zmultiple_tree_node_t* node);

zmultiple_tree_node_t* find_multiple_node(void* data);

void preorder_multiple_tree(zmultiple_tree_t* tree);
void postorder_multiple_tree(zmultiple_tree_t* tree);
void midorder_multiple_tree(zmultiple_tree_t* tree);
*/
#endif//_ZMULTIPLE_TREE_H__
