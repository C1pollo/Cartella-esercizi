

#include <iostream>
using namespace std;


#include "coda.h"
/*
elemento* nuovo_elem(node* n)
{
    elemento* c = new elemento;
    c->next = nullptr;
    c->prev = nullptr;
    c->nodo = n;
}



elemento* enqueue(elemento* c, node* n, punta* p)
{
    if(c == nullptr)
    {
        c = nuovo_elem(n);
        p->first = c;
        p->last = c;
    }
    else
    {
        elemento* tmp = c;
        while(tmp->next!=nullptr) //tmp non è mai null quindi non da segmentation fault
        {
            tmp = tmp->next;
        }
        elemento* elemento = nuovo_elem(n);
        elemento->prev = tmp;
        tmp->next = elemento; 
        //aggiorno il puntatore alla coda:
        p->last = elemento;
    }
    return c;
}



elemento* dequeue(elemento* c, punta* puntatore) //rimuovo il primo elemento dalla coda e lo restituisco.
{
    if(puntatore == nullptr)
    {
        cout<<endl<<"errore di inizializzazione del puntatore alla coda"<<endl;
        return nullptr;
    }
    if(puntatore->first == nullptr && puntatore->last == nullptr)
    {
        cout<<endl<<"LA CODA è VUOTA"<<endl;
        return nullptr;
    }
    else
    {
       elemento* del = puntatore->first;
       elemento* nuovo_primo = del->next;
       nuovo_primo->prev = nullptr;
       puntatore->first = nuovo_primo; 
       return del;
    }
}
*/


elemento* nuovo_elem(node* n)
{
    elemento* elem = new elemento;
    elem->nodo = n;
    elem->pun = nullptr;
    return elem;
}

coda* new_queue()
{
    coda* queue = new coda;
    queue->first = nullptr;
    queue->last = nullptr;
    return queue; 
}


void enqueue(node* n, coda* queue)
{
    elemento* e = new elemento;
    e = nuovo_elem(n);


    if(queue->first==nullptr) //coda vuota quindi aggiorno anche first, altrimenti aggiorno solo last.
    {
        queue->first = e;
        queue->last = e;
    }

    else //va inserito in fondo.
    {
        queue->last->pun = e; //inserisco nella "lista" (lista vista come coda)
        queue->last = e; //aggiorno il puntatore alla coda
    }
}

bool is_empty_queue(coda* queue)
{
    if(queue->first == nullptr)
    {
        return true;
    }
    return false;
}

node* dequeue(coda* queue)
{
    if(is_empty_queue(queue)==true)
    {
        cout<<endl<<"CODA VUOTA"<<endl;
        return nullptr;
    }
    elemento* elem = queue->first;
    //delete(queue->first);
    queue->first = elem->pun; //aggiorno la lista (i puntatori degli elementi che ne fanno parte)
    if(queue->first==nullptr) //lista svuotata
    {
        queue->last = nullptr;
    }
    //cout<<"dentro a dequeue sto rimuovendo:  "<< (elem->nodo)<< endl;
    return elem->nodo;
}
/*
void bfs_albero(tree t) //PRIMA TUTTI I FRATELLI POI I FIGLI CHE SONO GIà STATI MESSI IN CODA.
{

    lista list = new elemento; //lista da vedere come coda.
    coda* queue = new_queue();


    list = enqueue(t , queue);                            //inserisce la radice dell'albero nella coda
    while(is_empty_queue(queue) == false)                 //qui vediamo se la coda non è vuota 
    {
        node* nodo = dequeue(queue);                        //togliamo dalla coda un nodo e lo mettiamo sulla variabile nodo 
        //elemento* tmp->nodo = (e->nodo)->next_sibling;

        //controllo i fratelli:
        cout<<"elemento visitato: "<< get_info(nodo)<<endl;
        
        node* tmp = nodo->nextSibling;

        if(nodo->parent == nullptr || nodo->parent->firstChild == nodo){    //controllo se il nodo è la radice o il primo figlio del suo  genitore 
            while(tmp!=nullptr)                                             //aggiungo tutti i suoi fratelli nella coda una sola volta 
            {
                list = enqueue(tmp,queue);
                tmp = tmp->nextSibling;
            }
        }

        //controllo il figlio:
        if(nodo->firstChild!=nullptr)                                       //aggiungiamo il primo figlio del nodo scelto alla coda 
        {
            list = enqueue(nodo->firstChild, queue);
        }
        //a = a+1;
    }
    cout<<"sono fuori " <<endl;
}
*/
void bfs(tree t){

    coda* queue = new_queue();
    enqueue(t, queue);


    while (!(is_empty_queue(queue)))
    {

        node* n= dequeue(queue);
        cout << "visitato-" << get_info(n) << endl; 


        node* curr = n->firstChild;
        while (curr != NULL){
            enqueue(curr, queue);
            curr=curr->nextSibling;
        }
    }
}
