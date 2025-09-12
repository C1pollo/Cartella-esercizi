#include <iostream>
using namespace std;

#include "tipo.h"
#include "Liste.h"


/*******************************/
/* DEFINIZIONE MODULO "liste" */
/*******************************/

tipo_inf head(lista p){
    return p->inf;
}

nodo* search(lista l, tipo_inf v){
    while(l!=NULL)
		if(compare(head(l),v) == 0)
			return l;
		else
			l=tail(l);
	return NULL;}


nodo* new_elem(tipo_inf inf){
	    nodo* p = new nodo ;
	    copy(p->inf,inf);
	    p->next=p->prev=NULL;
		return p;

	}




lista tail(lista p){return p->next;}
lista prev(lista p){return p->prev;}

lista insert_elem(lista l, nodo* e){
	e->next=l;
	if(l!=NULL)
		l->prev=e;
	e->prev=NULL;
	return e;
}

lista delete_elem(lista l, nodo* e){

		if(l==e)
			l=e->next; // e è la testa della lista
		else // e non è la testa della lista
			(e->prev)->next = e->next;
		if(e->next!=NULL)
			(e->next)->prev=e->prev;
		delete e;
		return l;
}

lista crealista(int n){
    lista L = nullptr;  // Inizializza a nullptr, non a new nodo
	int c=0;

	for (int i=0;i<n;i++) {
			cout << "dammi un valore" << endl;
			cin >> c;
			nodo* p = new_elem(c);
            insert_elem(L,p);
	}
    return L;
}

void stampalista(lista L){
	if (L==NULL) {
		cout << "Lista vuota";
		return;}
    while (L!= NULL) {
        cout << head(L) << " ";
        L=tail(L);
    }
	cout << endl;
}

void eliminalista(lista L)
{
	lista current = L;
	while (current!=NULL){
		lista proc = current->next;
		delete(current);
		current= proc;
	}
}