#ifndef _TREE_
#define _TREE_

#include"node.h"
struct tree
{
    struct node* root;
    struct node* current;
    struct node* previous;
};
typedef struct tree tree;

tree* tree_create(void* root);
tree* tree_destroy(tree *self,void destroyer(void*));
//it adds nodes from left to right
void tree_add(tree* self,void *data,bool leaf_recognizer(void*));
void* tree_next(tree* self);
bool tree_has_next(tree* self);
void tree_reset(tree *self);




#endif