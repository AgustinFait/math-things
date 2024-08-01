#include "node.h"

node *node_create(void* data)
{
    node* new = malloc(sizeof(node));
    new->data =data;
    new->left = NULL;
    new->right = NULL;
    new->next_step = GO_LEFT;
    return new;
}

void node_destroy(node* n)
{
    free(n);
}

void node_destroy_and_destroy_descendants(node* n)
{
    if(n->left)node_destroy_and_destroy_descendants(n->left);
    if(n->right)node_destroy_and_destroy_descendants(n->right);
}

void node_destroy_and_destroy_data(node *n,void destroyer(void*))
{
    destroyer(n->data);
    node_destroy(n);
}

void node_destroy_everything(node *n,void destroyer(void*))
{
    if(n->left)node_destroy_everything(n->left,destroyer);
    if(n->right)node_destroy_everything(n->right,destroyer);

    destroyer(n->data);
    node_destroy(n);
}

void node_attach(node* father,node* son,int son_number)
{
    if(son_number)father->right = son;
    else father->left = son;
}

node* node_detach(node* father,int son_number)
{
    node* son;
    if(son_number)
    {
        son = father->right;
        father->right = NULL;
    }
    else 
    {
        son = father->left;
        father->left = NULL;
    }
    return son;
}

void node_detach_and_destroy(node* father,int son_number)
{
    node_destroy(node_detach(father,son_number));
}

void node_detach_destroy_self_and_descendants(node* father,int son_number)
{
    node_destroy_and_destroy_descendants(node_detach(father,son_number));
}

void node_detach_and_destroy_data(node* father,int son_number,void destroyer(void*))
{
    node_destroy_and_destroy_data(node_detach(father,son_number),destroyer);
}

void node_detach_and_destroy_everything(node* father,int son_number,void destroyer(void*))
{
    node_destroy_everything(node_detach(father,son_number),destroyer);
}

node* node_get_son(node *n,int son_number)
{
    if(son_number)return n->right;
    else return n->left;
}

void node_set(node* n,void* data)
{
    n->data = data;
}

void *node_get(node* n)
{
    return n->data;
}

node* node_left(node* self)
{
    return self->left;
}

node* node_right(node* self)
{
    return self->right;
}


bool node_add_next(node* self,void *data,bool leaf_recognizer(void*))
{
    if(!self)return false;
    if(leaf_recognizer(self->data))return false;
    if(node_add_next(self->left,data,leaf_recognizer))return true;
    if(node_add_next(self->right,data,leaf_recognizer))return true;
    if(!self->left)
    {
        self->left = node_create(data);
        if(leaf_recognizer(data))self->left->next_step = SELF;
        return true;
    }
    if(!self->right)
    {
        self->right = node_create(data);
        if(leaf_recognizer(data))self->right->next_step = SELF;
        return true;
    }
    return false;
}


node* node_next(node* self)
{
    if(!self)return NULL;
    node* to_return;
    switch (self->next_step)
    {
    case GO_LEFT:
        to_return = node_next(self->left);
        if(self->left->next_step == DONE)self->next_step = GO_RIGHT;
    break;
    case GO_RIGHT:
        to_return = node_next(self->right);
        if(self->right->next_step == DONE)self->next_step = SELF;
    break;
    case SELF:
        to_return = self;
        self->next_step = DONE;
    break;
    case DONE:
    break;
    default:
        break;
    }
    return to_return;
}

void reset(node* self)
{
    if(self && self->left)self->next_step = GO_LEFT;
}

void reset_self_and_children(node* self)
{
    if(!self)return;
    reset_self_and_children(self->left);
    reset_self_and_children(self->right);

    self->next_step = GO_LEFT;
}