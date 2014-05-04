#include "ztree.h"
#include <stdio.h>

#include "zstack.h"
#include "zqueue.h"

ztree_node_t* new_node() 
{
    ztree_node_t* node = (ztree_node_t*)malloc(sizeof(ztree_node_t));
    if(!node)
        perror("malloc node failed");

    node->data = NULL;	
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

ztree* create_tree()
{
    ztree* tree = (ztree*)new_node();
    if(!tree)
        perror("malloc tree failed");

    return tree;
}

void clear_tree()
{

}

void build_tree(ztree* tree, int v)
{	
    ztree_node_t* node = (ztree_node_t*)tree;	
    if(!node->data) {
        node->data = malloc(sizeof(int));
        *(int*)node->data = v;
        return;
    } 

    if( *(int*)node->data > v) {
        if(!node->lchild) {
            node->lchild = new_node();					
        }

        build_tree(node->lchild, v);		
    } else {
        if(!node->rchild) {
            node->rchild = new_node();
        }

        build_tree(node->rchild, v);		
    }
}

void preorder(ztree* tree) 
{
    ztree_node_t* node = (ztree_node_t*)tree;
    if(!node) {
        return;
    } 

    printf("%d\t", *(int*)node->data);
    preorder(node->lchild);
    preorder(node->rchild);
}

void midorder(ztree* tree) 
{
    ztree_node_t* node = (ztree_node_t*)tree;
    if(!node) {
        return;
    } 

    midorder(node->lchild);
    printf("%d\t", *(int*)node->data);
    midorder(node->rchild);
}

void postorder(ztree* tree) 
{
    ztree_node_t* node = (ztree_node_t*)tree;
    if(!node) {
        return;
    } 

    postorder(node->lchild);
    postorder(node->rchild);
    printf("%d\t", *(int*)node->data);
}

void preorder2(ztree* tree)
{
    ztree_node_t* node = (ztree_node_t*)tree;
    if(!node) {
        return;
    } 

    zstack_t* stack = create_stack();
    while(1) {
        if(node) {
            printf("%d\t", *(int*)node->data);
        } else {
            zstack_node_t* stack_node = pop(stack);
            if(!stack_node) 	
                return;
            node = stack_node->data;
            continue;
        }		

        if(node->rchild)
            push(stack, node->rchild);
        node = node->lchild;	
    }
}

void midorder2(ztree* tree)
{
    ztree_node_t* node = (ztree_node_t*)tree;
    if(!node) {
        return;
    } 

    zstack_t* stack = create_stack();
    while(node || top(stack)) {
        while(node) {
            push(stack, node);
            node = node->lchild;	
        }

        if(top(stack)) {
            zstack_node_t* stack_node = pop(stack);
            node = stack_node->data;
            printf("%d\t", *(int*)node->data);
            node = node->rchild;
        }		
    }
}

void postorder2(ztree* tree) 
{
    ztree_node_t* node = (ztree_node_t*)tree;
    if(!node) {
        return;
    } 

    zstack_t* stack = create_stack();
    push(stack, node);
    while(top(stack)){
       while(node) {
            push(stack, node);
            node = node->lchild;
            //push(stack, node->rchild);
       }   
    
       zstack_node_t* stack_node = top(stack);
       node = stack_node->data;
       if(node->rchild) {
           node = node->rchild;
           while(node) {
               push(stack, node);
               node = node->rchild;
               //push(stack, node->rchild);
           }   
       }

       while(top(stack) && node->rchild) {
            zstack_node_t* stack_node = pop(stack); 
            //ztree_node_t* 
       } 
    }
}
