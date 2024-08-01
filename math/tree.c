#include "tree.h"


tree* tree_create(void* root)
{
    tree* new = malloc(sizeof(tree));
    new->root = node_create(root);
    new->current = new->root;
    new->previous =NULL;
    return new;

}

tree* tree_destroy(tree *self,void destroyer(void*))
{
    node_destroy_everything(self->root,destroyer);
}

void tree_add(tree* self,void *data,bool leaf_recognizer(void*))
{
    node_add_next(self->root,data,leaf_recognizer);
}


void* tree_next(tree* self)
{
    return node_next(self->root)->data;
}

bool tree_has_next(tree* self)
{
    return self->root->next_step == DONE;
}

void tree_reset(tree *self)
{

}