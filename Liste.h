
//Header del Mmodulo Liste, contiene le dichiarazioni delle funzioni

/*HEADER MODULO LISTE*/

//in un file header.h si mettono solo le dichiarazioni delle funzioni
//e le definizioni di tipi di dato (strutture, typedef, enum...)
struct nodo{
    tipo_inf inf;
    struct nodo* next;
    struct nodo* prev;
};
typedef struct nodo* lista;

//primitive della lista
//le primtive sono funzioni che lavorano sulle liste e restituiscono un tipo lista
//in una lista le operazioni piu comuni in cui potremmmo imbatterci sono:

//restituire la coda del nodo in questione della lista
lista tail(lista);

//restituire il valore della testa della lista
tipo_inf testa(lista);

//restituire il precedente del nodo
lista prev(lista);

//inserire un elemento in testa alla lista
lista insert_elem(lista, nodo*);

//cancellare un elemento dalla lista
lista delete_elem(lista, nodo*);

//ricercare un elemento nella lista
nodo* search(lista, nodo*);

//creare un nuovo elemento della lista
nodo* new_elem(tipo_inf);


lista crealista(int n);

void stampalista(lista);

void eliminalista(lista);



