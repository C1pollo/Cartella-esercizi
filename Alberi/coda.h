

 
#include "tree.h"

struct elemento
{
    node* nodo;
    elemento* pun;
};

typedef elemento* lista;

typedef struct coda
{
    lista first;
    elemento* last;
}coda;

elemento* nuovo_elem(node*);
void enqueue(node*, coda*);

node* dequeue(coda*);

coda* new_queue();

bool is_empty_queue(coda*);

void bfs(tree t);
