#ifndef _TREE_
#define _TREE_

#include<stdio.h>
enum step
{
    GO_LEFT,
    GO_RIGHT,
    GO_BACK
};

struct node
{
    void *data;
    struct node* left;
    struct node* right;
    int next_step;
};
struct tree
{
    struct node* root;
    struct node* current;
};
typedef struct node node;
typedef struct tree tree;

//node functions
node *node_create(void* data);
void node_destroy(node* n);
void node_destroy_and_destroy_descendants(node* n);
void node_destroy_and_destroy_data(node *n,void destroyer(void*));
void node_destroy_everything(node *n,void destroyer(void*));
// the son number is either 0 to left or 1 to right 
void node_attach(node* father,node* son,int son_number);
node* node_detach(node* father,int son_number);
void node_detach_and_destroy(node* father,int son_number);
void node_detach_destroy_self_and_descendants(node* father,int son_number);
void node_detach_and_destroy_data(node* father,int son_number,void destroyer(void*));
void node_detach_and_destroy_everything(node* father,int son_number,void destroyer(void*));
node* node_get_son(node *n,int son_number);

void node_set(node* n,void* data);
void* node_get(node* n);








#endif