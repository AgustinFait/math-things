#ifndef _NODE_
#define _NODE_

#include<stdio.h>
#include<stdbool.h>

enum step
{
    GO_LEFT,
    GO_RIGHT,
    SELF,
    DONE
};

struct node
{
    void *data;
    struct node* left;
    struct node* right;
    int next_step;
};

typedef struct node node;


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

node* node_left(node* self);
node* node_right(node* self);

bool node_add_next(node* self,void *data,bool leaf_recognizer(void*));
node* node_next(node* self);
#endif