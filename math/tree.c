#include "tree.h"

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