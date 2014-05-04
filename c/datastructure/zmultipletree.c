#include "zmultipletree.h"

zmultiple_tree_t* create_multiple_tree()
{
    zmultiple_tree_t* tree = (zmultiple_tree_t*)malloc(sizeof(zmultiple_tree_node_t));
    if(!tree) {
        perror("create multiple tree failed");
    } else {
        memset(tree, 0, sizeof(zmulitple_tree_t));
    }
    return tree;
}

void clear_multiple_tree(zmultiple_tree_t* tree)
{
    
}


bool insert_as_child(zmultiple_tree_node_t* node, void* data)
{
    zmultiple_tree_node_t* new_node = (zmultiple_tree_node_t*)malloc(sizeof(zmultiple_tree_node_t));
    if(!new_node) {
        perror("insert as child malloc failed");
        return false;
    } else {
        memset(new_node, 0, sizeof(zmultiple_tree_node_t));
        new_node->data = data;
            
        if(node->lchild) {
             
        } else {
            node->lchild = new_node; 
        }
        
    }

    return true;
}

bool insert_as_child(zmultiple_tree_node_t* node, zmultiple_tree_node_t* new_node)
{
    node->lchild = new_node;
}

bool insert_as_sibling(zmultiple_tree_node_t* node, void* data)
{

}

bool insert_as_sibling(zmultiple_tree_node_t* node, zmultiple_tree_node_t* new_node)
{

}


zmultiple_tree_node_t* remove_multiple_node(void* data)
{

}

zmultiple_tree_node_t* remove_multiple_node(zmultiple_tree_node_t* node)
{

}


zmultiple_tree_node_t* find_multiple_node(void* data)
{

}


void preorder_multiple_tree(zmultiple_tree_t* tree)
{

}

void postorder_multiple_tree(zmultiple_tree_t* tree)
{

}

void midorder_multiple_tree(zmultiple_tree_t* tree)
{

}

