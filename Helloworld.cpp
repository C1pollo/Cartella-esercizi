#include <iostream>
#include <cstring>
using namespace std;


//#include "fun_liste.h"
#include "tipo.h"
#include "liste.h"

//il punto cruciale è che nelle funzioni in cui cìè scritto lista prima vuol dire che bisogna restituirla perchè all'interno potremmo aver cambiato la lista
// e il puntatore ha bisgono di sapere se la memoria a cui sta puntando è ancora legata alla testa o se invece non la sta piu puntando 



int main()
{
    
    lista L= NULL;

    //inizializzo i due nodi
    
    nodo* p= new nodo;
    p->inf=3;
    p->next=NULL;
    p->prev=NULL;
    L=insert_elem(L, p);
    
    nodo* c= new nodo;
    c->inf=7;
    c->next=NULL;
    c->prev=NULL;
    L=insert_elem(L, c);

    stampalista(L);
    eliminalista(L);
    L=NULL;
    stampalista(L);
    return 0;
}

